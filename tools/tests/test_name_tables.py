"""A run of string pointers is not automatically an enum.

The sweep exists because two hand-found tables settled width questions that had
defeated a merge, and there turned out to be 229 of them. The risk in
generalising is the opposite of the risk in finding them by hand: a scan that
calls every array of char* a name table will report locale strings and GPU model
names as enums, and a width checked against one of those is worse than a width
checked against nothing.

So the shape test and the contents test are separate, and what fails the
contents test is REPORTED as uncertain rather than dropped. A sweep that quietly
discards what it cannot classify is one whose silence means nothing.
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_tables as NT  # noqa: E402

BASE = NT.IMAGE_BASE
DATA_VA, DATA_RAW = 0x2000, 0x2000     # a fake .data whose VA and file offset agree


class FakeImage:
    """Only the four things sweep() asks of the retail file."""

    def __init__(self, strings, pointers):
        blob = bytearray(0x4000)
        self.offsets = {}
        cursor = 0x1000                      # a fake .rdata
        for text in strings:
            blob[cursor:cursor + len(text)] = text.encode()
            self.offsets[text] = BASE + cursor
            cursor += len(text) + 1
        for index, value in enumerate(pointers):
            struct.pack_into("<I", blob, DATA_RAW + index * 4, value)
        self.data = bytes(blob)
        self.sections = {".data": (DATA_VA, len(pointers) * 4 + 8, DATA_RAW,
                                   len(pointers) * 4 + 8)}

    def string_at(self, va):
        return NT.Image.string_at(self, va)

    def is_string_pointer(self, value):
        return 0x400000 + 0x1000 <= value < 0x400000 + 0x2000 and \
            self.string_at(value) is not None

    def va(self, text):
        return self.offsets[text]


def _sweep(names, tail=(0,)):
    image = FakeImage(names, [])
    pointers = [image.va(n) for n in names] + list(tail)
    image = FakeImage(names, pointers)
    return NT.sweep(image)


def test_msvc_template_numbers_decode():
    """$0HE@ is 0x74; the digit forms spell 1..10, which is a separate rule."""
    assert NT.decode_number("HE") == 116
    assert NT.decode_number("BDA") == 304
    assert NT.decode_number("CN") == 45
    assert NT.decode_number("0") == 1
    assert NT.decode_number("9") == 10
    assert NT.decode_number("Q") is None      # past P, not a hex digit here


def test_storage_is_whole_dwords():
    assert NT.dwords_needed(1) == 1
    assert NT.dwords_needed(32) == 1
    assert NT.dwords_needed(33) == 2
    assert NT.dwords_needed(304) == 10


def test_an_identifier_run_is_a_name_table():
    names = ["TOPPLED", "DAMAGED", "RUBBLE", "NIGHT", "SNOW", "PARACHUTING"]
    found = _sweep(names)
    assert len(found) == 1
    assert found[0]["verdict"] == NT.NAME_TABLE
    assert found[0]["entries"] == len(names)
    assert found[0]["names"] == names
    assert found[0]["nul_terminated"] is True


def test_a_run_of_prose_is_uncertain_not_a_name_table():
    """Locale strings and device names have exactly this shape in the real image.

    Reported, not dropped: the sweep must not be able to hide something it
    could not classify.
    """
    names = ["Unknown ATI Device", "some words here", "a b c", "x y z",
             "more prose", "and more"]
    found = _sweep(names)
    assert len(found) == 1
    assert found[0]["verdict"] == NT.UNCERTAIN
    assert found[0]["identifier_share"] < NT.IDENT_SHARE


def test_a_short_run_is_not_reported_at_all():
    """Below the floor these are mostly coincidence, and reporting them would
    bury the real tables."""
    assert _sweep(["A", "B", "C"]) == []


def test_runs_are_maximal_so_a_table_is_reported_once():
    """Every suffix of a table is itself a run of string pointers. If the scan
    restarted inside one, a 304-entry table would produce 299 findings."""
    names = [f"NAME_{i}" for i in range(12)]
    found = _sweep(names)
    assert len(found) == 1
    assert found[0]["entries"] == 12


def test_an_unterminated_run_is_recorded_as_such(monkeypatch):
    """A run ending at something other than NUL is still reported, and says so."""
    names = [f"NAME_{i}" for i in range(8)]
    found = _sweep(names, tail=(0xDEADBEEF,))
    assert len(found) == 1
    assert found[0]["nul_terminated"] is False


def test_a_string_with_control_bytes_is_not_a_string():
    image = FakeImage(["OK_NAME"], [])
    blob = bytearray(image.data)
    blob[0x1000] = 0x01                       # corrupt the first byte
    image.data = bytes(blob)
    assert image.string_at(BASE + 0x1000) is None


def test_bitflags_widths_come_off_the_decoration():
    rows = [{"name": "?f@C@@QAEXV?$BitFlags@$0HE@@@@Z"},
            {"name": "?g@D@@QAEXV?$BitFlags@$0BDA@@@@Z"},
            {"name": "?h@E@@QAEXH@Z"}]
    widths = NT.bitflags_widths(rows)
    assert sorted(widths) == [116, 304]
    assert widths[116] == ["?f@C@@QAEXV?$BitFlags@$0HE@@@@Z"]
