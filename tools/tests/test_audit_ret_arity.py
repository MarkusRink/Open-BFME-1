"""Focused tests for decorated-name stack cleanup parsing."""

import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import audit_ret_arity as arity  # noqa: E402


SCRIPT_LIST = (
    "?ParseScriptListDataChunk@ScriptList@@SA_NAAVDataChunkInput@@"
    "PAUDataChunkInfo@@PAX@Z"
)


def test_script_list_is_a_known_cdecl_even_with_reference_and_pointer_args():
    assert arity.expected_ret(SCRIPT_LIST) == (0, "__cdecl")
    assert arity.actual_ret(b"\x55\x8b\xec\xc2\x10\x00") == 16


@pytest.mark.parametrize(
    "body",
    [
        bytes.fromhex("e9 00 c2 10 00"),  # jmp rel32, not ret 16
        bytes.fromhex("b8 01 00 00 c3"),  # mov eax, imm32 ending in c3
        bytes.fromhex("b8 01 c2 10 00"),  # mov eax, imm32 ending in c2 10 00
    ],
)
def test_decoded_tail_does_not_read_return_like_bytes_from_other_instructions(body):
    assert arity.decoded_actual_ret(body) is None


def test_decoded_tail_accepts_complete_cdecl_returns_only():
    assert arity.decoded_actual_ret(bytes.fromhex("55 8b ec c3")) == 0
    assert arity.decoded_actual_ret(bytes.fromhex("55 8b ec c2 10 00")) == 16


@pytest.mark.parametrize(
    "symbol",
    [
        "?scalar@@YAHH@Z",                         # int(int)
        "?flag@@YA_NPAX@Z",                       # bool(void *)
        "?void@@YAXH@Z",                          # void(int)
        "?ptr@@YAPAVRecord@@PAVRecord@@@Z",       # Record *(Record *)
        "?ref@@YAAAVRecord@@AAVRecord@@@Z",       # Record &(Record &)
    ],
)
def test_fixed_scalar_pointer_reference_cdecl_returns_pop_zero(symbol):
    assert arity.expected_ret(symbol) == (0, "__cdecl")


@pytest.mark.parametrize(
    "symbol",
    [
        "?make@@YA?AVRecord@@XZ",                 # hidden sret return
        "?make@@YAVRecord@@XZ",                   # by-value record return
        "?printf@@YAXPBDZZ",                      # varargs marker
        "??$make@H@@YAHH@Z",                     # template name
        "??0Record@@YAXXZ",                       # constructor, no return ABI
        "?incomplete@@YAHH",                      # no terminal encoding
        "?takes_record@@YAHVRecord@@@Z",          # unknown by-value argument
    ],
)
def test_unproven_cdecl_abis_remain_unknown(symbol):
    assert arity.expected_ret(symbol) == (None, None)


def test_existing_callee_cleaned_conventions_keep_their_original_rules():
    assert arity.expected_ret("?g@C@@QAEXHH@Z") == (8, "__thiscall")
    assert arity.expected_ret("?s@@YGHH@Z") == (4, "__stdcall")
    assert arity.expected_ret("?f@@YIH@Z") == (0, "__fastcall")
