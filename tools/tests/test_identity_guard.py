"""An object-derived regression has to be answered, not just flagged.

This exists because of a real incident. A ./build.sh killed partway through left
this tree holding objects compiled from a state that no longer existed;
multi_name compared those stale bytes and reported multi_name.different
regressions at 0x00042D1B and 0x002136E0. Both vanished the moment the two
translation units were rebuilt -- but by then the tree had been reported
upstream as red, and a translation unit had nearly been deleted on the strength
of them.

The first fix said the number MIGHT be about the build. That is a warning, and a
warning leaves the reader guessing with "probably fine" as the cheap guess. So
the guard now asks tools/object_cache.py about the objects behind the flagged
rows and reports a verdict. These tests pin that it reaches the right one, and
that where it cannot reach one it says so rather than reporting the tree clean.

ctor_vtable reads retail's own bytes and the ledger, so no local build state can
spoil it. The distinction has to hold in both directions: a question that is
also asked where a rebuild could not change the answer is one people learn to
skip.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import identity_guard as G  # noqa: E402
import object_cache as OC  # noqa: E402

CONSULTED = "Asking tools/object_cache.py"


def _run(monkeypatch, capsys, found, baseline, outputs=None, answer=None):
    monkeypatch.setattr(G, "measure", lambda: (found, outputs or {}))
    monkeypatch.setattr(G, "read_baseline", lambda: baseline)
    if answer is not None:
        monkeypatch.setattr(G, "object_verdict", lambda worse, out: answer)
    with pytest.raises(SystemExit) as exit:
        G.main()
    return exit.value.code, capsys.readouterr().err


def test_every_check_declares_where_its_evidence_comes_from():
    """An unclassified check would silently never be questioned."""
    assert set(G.SOURCE) == {c[0] for c in G.CHECKS}
    assert G.SOURCE["multi_name.family"] == G.OBJECTS
    assert G.SOURCE["multi_name.different"] == G.OBJECTS
    assert G.SOURCE["ctor_vtable.contradicted"] == G.IMAGE
    assert G.SOURCE["ctor_vtable.unreadable"] == G.IMAGE
    assert G.SOURCE["size_outlier.indicted"] == G.IMAGE
    # Only object-derived checks can be scoped, so only they need detail text.
    for label, source in G.SOURCE.items():
        assert (G.DETAIL[label] is not None) == (source == G.OBJECTS)


def test_a_dirty_answer_says_the_finding_is_not_evidence(monkeypatch, capsys):
    """The incident's shape, and the sentence that would have stopped it."""
    code, err = _run(monkeypatch, capsys,
                     {"multi_name.different": 1}, {"multi_name.different": 0},
                     answer=(OC.DIRTY, ["a build here was interrupted"]))
    assert code == 1
    assert "multi_name.different: 0 -> 1" in err
    assert "-> DIRTY" in err
    assert "NOT evidence" in err


def test_a_clean_answer_says_the_finding_is_real(monkeypatch, capsys):
    """It must be able to confirm a regression too, or nothing can be believed."""
    code, err = _run(monkeypatch, capsys,
                     {"multi_name.different": 1}, {"multi_name.different": 0},
                     answer=(OC.CLEAN, ["every object present matches its inputs"]))
    assert code == 1
    assert "-> CLEAN" in err
    assert "real regression" in err


def test_an_unknown_answer_is_not_treated_as_clean(monkeypatch, capsys):
    code, err = _run(monkeypatch, capsys,
                     {"multi_name.family": 1}, {"multi_name.family": 0},
                     answer=(OC.UNKNOWN, ["a build is running now"]))
    assert code == 1
    assert "-> UNKNOWN" in err
    assert "unverified" in err


def test_an_image_derived_regression_is_never_questioned(monkeypatch, capsys):
    """A rebuild cannot change what ctor_vtable reads, so asking would be noise."""
    code, err = _run(monkeypatch, capsys,
                     {"ctor_vtable.contradicted": 50}, {"ctor_vtable.contradicted": 49})
    assert code == 1
    assert "ctor_vtable.contradicted: 49 -> 50" in err
    assert CONSULTED not in err


def test_a_failed_consultation_is_loud_and_not_reassuring(monkeypatch, capsys):
    """Bookkeeping that breaks must not read as "the objects are fine"."""
    def boom(worse, outputs):
        raise RuntimeError("object_cache is broken")

    monkeypatch.setattr(G, "object_verdict", boom)
    code, err = _run(monkeypatch, capsys,
                     {"multi_name.different": 1}, {"multi_name.different": 0})
    assert code == 1
    assert "could not answer" in err
    assert "UNVERIFIED" in err


def test_a_drop_still_fails_and_asks_nothing(monkeypatch, capsys):
    """A fix must lower the baseline, which is not a question about objects."""
    code, err = _run(monkeypatch, capsys,
                     {"multi_name.different": 0}, {"multi_name.different": 1})
    assert code == 1
    assert "FIXED" in err
    assert CONSULTED not in err


def test_an_interrupted_build_outranks_an_unparseable_report(monkeypatch):
    """Precedence: a killed run can have left ANY object half-written.

    Scoping to the flagged rows is what keeps the answer useful, but it must not
    be a precondition for noticing the tree is poisoned. The first version of
    this returned UNKNOWN here because it tried to parse before it looked.
    """
    monkeypatch.setattr(OC, "markers", lambda: ([999999], [], []))
    verdict, reasons = G.object_verdict({"multi_name.different": (1, 0)},
                                        {"multi_name.py": "no parseable rows here"})
    assert verdict == OC.DIRTY
    assert "interrupted" in " ".join(reasons)


def test_an_unparseable_report_alone_is_unknown(monkeypatch):
    """No names means the report's format moved. Widening to the whole tree
    answers a different question and would almost always say stale."""
    monkeypatch.setattr(OC, "markers", lambda: ([], [], []))
    verdict, reasons = G.object_verdict({"multi_name.different": (1, 0)},
                                        {"multi_name.py": "nothing here"})
    assert verdict == OC.UNKNOWN
    assert "could not read the flagged rows" in " ".join(reasons)


def test_only_rows_under_the_matching_verdict_are_taken():
    """Two verdicts share one report; the wrong one's rows must not leak in."""
    report = (
        "0x00000001    9B  rests on 1/9   DIFFERENT BODIES - cannot share an address\n"
        "      ?wanted@A@@QAEXXZ\n"
        "0x00000002    9B  rests on n/a   unreadable object - NOT a clean result\n"
        "      ?unwanted@B@@QAEXXZ\n"
    )
    assert G.flagged_names(report, "DIFFERENT BODIES - cannot share an address") == \
        ["?wanted@A@@QAEXXZ"]
