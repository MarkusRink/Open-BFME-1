"""The detector has to be able to say it does not know.

A check that reports "clean" when it cannot tell is the failure this exists to
end, not a fix for it, so most of these tests are about the answer NOT being
clean: a build running right now, a marker that cannot be parsed, a source that
cannot be evaluated. Each of those is a question the detector cannot answer, and
answering it anyway would make this the third silent-success check in a row.

The two mechanisms are tested apart because they catch different things. A
killed build leaves an object that is half-written and perfectly fresh, which no
comparison of contents can see; an edited header leaves an object that is whole
and wrong, which no marker can see.
"""
import os
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import object_cache as OC  # noqa: E402

LIVE = os.getpid()
DEAD = 999999            # nothing this high is running; asserted below


def _isolate(monkeypatch, tmp_path, sources=None, current=None):
    """Point the detector at a scratch marker dir and a fake object set."""
    monkeypatch.setattr(OC, "INFLIGHT", tmp_path / ".inflight")
    rows = {name: {"name": name, "source": name} for name in (sources or {})}
    monkeypatch.setattr(OC, "claimed_sources", lambda: rows)
    present = sources or {}

    class FakeObj:
        def __init__(self, name):
            self.name = name

        def exists(self):
            return present[self.name]

    monkeypatch.setattr(OC.B, "row_object", lambda row: FakeObj(row["source"]))
    monkeypatch.setattr(OC.B, "compile_is_current",
                        lambda source, output: (current or {}).get(output.name, True))


def _marker(tmp_path, pid, text="x"):
    d = tmp_path / ".inflight"
    d.mkdir(parents=True, exist_ok=True)
    (d / str(pid)).write_text(text)


def test_the_dead_pid_is_actually_dead():
    """The whole DEAD case rests on this, so it is asserted rather than assumed."""
    assert OC.pid_alive(DEAD) is False
    assert OC.pid_alive(LIVE) is True


def test_an_interrupted_build_is_dirty(monkeypatch, tmp_path):
    """The incident: a killed ./build.sh leaves a marker its process cannot clear."""
    _isolate(monkeypatch, tmp_path)
    _marker(tmp_path, DEAD)
    verdict, reasons = OC.status()
    assert verdict == OC.DIRTY
    assert "interrupted" in " ".join(reasons)


def test_a_build_running_now_is_unknown_not_clean(monkeypatch, tmp_path):
    """Objects are being rewritten underneath the question; clean would be a lie."""
    _isolate(monkeypatch, tmp_path)
    _marker(tmp_path, LIVE)
    verdict, reasons = OC.status()
    assert verdict == OC.UNKNOWN
    assert "running now" in " ".join(reasons)


def test_a_marker_that_cannot_be_parsed_is_unknown(monkeypatch, tmp_path):
    """An unreadable marker is a question unanswered, not a tree vouched for."""
    _isolate(monkeypatch, tmp_path)
    _marker(tmp_path, "not-a-pid")
    assert OC.status()[0] == OC.UNKNOWN


def test_an_object_that_does_not_match_its_inputs_is_dirty(monkeypatch, tmp_path):
    """The wider class: a source or header edited with no rebuild behind it."""
    _isolate(monkeypatch, tmp_path, sources={"a.cpp": True, "b.cpp": True},
             current={"b.cpp": False})
    verdict, reasons = OC.status()
    assert verdict == OC.DIRTY
    assert "b.cpp" in " ".join(reasons)


def test_an_absent_object_is_not_stale(monkeypatch, tmp_path):
    """Nothing reads it, and the detectors already report unreadable as unreadable.

    Counting absent objects as stale would make a cold clone permanently dirty
    and the verdict worthless.
    """
    _isolate(monkeypatch, tmp_path, sources={"a.cpp": False},
             current={"a.cpp": False})
    assert OC.status()[0] == OC.CLEAN


def test_a_source_that_cannot_be_evaluated_is_unknown(monkeypatch, tmp_path):
    """Failing to answer must not read as an answer."""
    _isolate(monkeypatch, tmp_path, sources={"a.cpp": True})

    def boom(row):
        raise RuntimeError("no object path for this row")

    monkeypatch.setattr(OC.B, "row_object", boom)
    verdict, reasons = OC.status()
    assert verdict == OC.UNKNOWN
    assert "could not be evaluated" in " ".join(reasons)


def test_a_quiet_tree_with_matching_objects_is_clean(monkeypatch, tmp_path):
    """It also has to be able to say yes, or a real finding can never be believed."""
    _isolate(monkeypatch, tmp_path, sources={"a.cpp": True})
    verdict, reasons = OC.status()
    assert verdict == OC.CLEAN
    assert "no interrupted build" in " ".join(reasons)


def test_dirty_outranks_a_concurrent_build(monkeypatch, tmp_path):
    """A live build cannot downgrade proof that an earlier one died."""
    _isolate(monkeypatch, tmp_path)
    _marker(tmp_path, DEAD)
    _marker(tmp_path, LIVE)
    assert OC.status()[0] == OC.DIRTY


def test_clearing_removes_only_the_dead_marker(monkeypatch, tmp_path):
    """Clearing a live build's marker would hide a genuine unknown."""
    _isolate(monkeypatch, tmp_path)
    _marker(tmp_path, DEAD)
    _marker(tmp_path, LIVE)
    assert OC.clear_dead_markers() == [DEAD]
    assert OC.markers() == ([], [LIVE], [])


def test_names_from_a_report_are_matched_as_prefixes(monkeypatch, tmp_path):
    """Reports elide long manglings, so a printed name is a prefix of the row's."""
    rows = [{"name": "?longMangledName@Class@@QAEXH@Z", "status": "matched",
             "source": "owner.cpp"},
            {"name": "?other@Other@@QAEXXZ", "status": "matched", "source": "no.cpp"}]
    monkeypatch.setattr(OC.B, "load_all_function_rows", lambda: rows)
    assert OC.sources_for_names(["?longMangledName@Class@@QAE"]) == ["owner.cpp"]
