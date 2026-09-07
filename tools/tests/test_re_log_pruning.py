"""A pathname-only historical sweep is not byte or identity evidence."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import re_log
import list_naked_candidates as queue

SYM = "?updateAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z"
RVA = 0x00497140
PRUNING = (
    "Superseded by the ledger: this symbol is matched from Code/Thunk.cpp, "
    "a real source, so the standing 'no-match' verdict is stale. "
    "Recorded by the tree-wide pruning pass that cross-referenced every logged "
    "symbol against its current ledger SOURCE PATH -- matched from a real .cpp "
    "means recovered, matched from gen_asm or gen_small means still open."
)


def row(status, evidence="measured evidence", rva=RVA, symbol=SYM):
    return f"{symbol}\t0x{rva:08X}\t233\t{status}\t{evidence}\r\n"


@pytest.fixture
def log(tmp_path, monkeypatch):
    path = tmp_path / "re_attempts.log"
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", path)
    re_log._reset()
    yield path
    re_log._reset()


@pytest.mark.parametrize("status", sorted(re_log.DEAD_END_STATUSES))
def test_pruning_does_not_release_a_measured_dead_end(log, status):
    log.write_text(row(status) + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == status
    assert re_log.latest_records()[RVA][3] == status
    assert re_log.is_dead_end(SYM, RVA)
    kept, suppressed = queue.drop_logged([{"symbol": SYM, "rva": hex(RVA)}])
    assert kept == [] and suppressed == 1


@pytest.mark.parametrize("status", sorted(re_log.DEFERRED_STATUSES))
def test_pruning_preserves_deferrals_and_banks(log, status):
    log.write_text(row(status) + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == status
    assert re_log.latest_records()[RVA][3] == status
    assert re_log.is_deferred(SYM, RVA)
    assert re_log.attempts(SYM) == 1
    items = [{"symbol": SYM, "rva": hex(RVA)}]
    assert queue.drop_logged(items) == (items, 0)


@pytest.mark.parametrize("status", ["converted", "solved", "landed", "partial"])
def test_later_actual_verdict_still_wins(log, status):
    log.write_text(row("no-boundary") + row("converted", PRUNING) + row(status))
    assert re_log.standing_status(SYM, RVA) == status
    assert re_log.latest_records()[RVA][3] == status
    assert not re_log.is_dead_end(SYM, RVA)


def test_pruning_alone_does_not_invent_a_verdict(log):
    log.write_text(row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) is None
    assert re_log.latest_records() == {}


def test_pruning_preserves_an_earlier_actual_conversion(log):
    log.write_text(row("no-match") + row("converted", "actual byte proof")
                   + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == "converted"
    assert re_log.latest_records()[RVA][4] == "actual byte proof"


def test_other_symbol_at_same_rva_keeps_its_own_verdict(log):
    other = "?independent@@YAXXZ"
    log.write_text(row("no-boundary") + row("landed", symbol=other)
                   + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == "no-boundary"
    assert re_log.standing_status(other, RVA) == "landed"
    assert re_log.latest_records()[RVA][0] == other


def test_three_field_boundary_finding_survives_pruning(log):
    log.write_text(f"{SYM}\tno-match\tmeasured extent\n" + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA, boundary_moved=True) == "no-match"
    assert re_log.latest_records() == {}


def test_new_boundary_remains_available(log):
    log.write_text(row("no-boundary") + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA + 16, boundary_moved=True) is None


def test_void_still_retracts_only_prior_exact_boundary(log):
    log.write_text(row("no-boundary") + row("converted", PRUNING)
                   + row("void") + row("partial", rva=RVA + 16))
    assert re_log.standing_status(SYM, RVA, boundary_moved=True) is None
    assert set(re_log.latest_records()) == {RVA + 16}


def test_later_refutation_can_close_an_actual_conversion(log):
    log.write_text(row("converted") + row("identity-suspect")
                   + row("converted", PRUNING))
    assert re_log.standing_status(SYM, RVA) == "identity-suspect"
    assert re_log.latest_records()[RVA][3] == "identity-suspect"


@pytest.mark.parametrize("evidence", [
    "clean C++ compiled and matched from Code/Thunk.cpp",
    "SOURCE PATH checked alongside actual compiled bytes",
    PRUNING.replace("Recorded by the tree-wide pruning pass", "Independently verified"),
    "Independent conversion supersedes the old attempt. " + PRUNING,
])
def test_only_the_specific_path_only_pass_is_reclassified(log, evidence):
    log.write_text(row("no-match") + row("converted", evidence))
    assert re_log.standing_status(SYM, RVA) == "converted"
    assert re_log.latest_records()[RVA][3] == "converted"
