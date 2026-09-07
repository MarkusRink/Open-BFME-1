"""A regression in an object-derived check has to say so out loud.

This exists because of a real incident, not a hypothesis. A ./build.sh killed
partway through left this tree holding objects compiled from a state that no
longer existed; multi_name compared those stale bytes and reported
multi_name.different regressions at 0x00042D1B and 0x002136E0. Both vanished
the moment the two translation units were rebuilt -- but by then the tree had
been reported upstream as red, and a translation unit had nearly been deleted
on the strength of it.

ctor_vtable reads retail's own bytes and the ledger, so no local build state
can spoil it. That difference is the whole point: the warning has to appear for
the checks it applies to and stay quiet for the ones it does not, or it just
becomes noise everybody learns to skip.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import identity_guard as G  # noqa: E402

WARNING = "COMPILED OBJECTS"


def _run(monkeypatch, capsys, found, baseline):
    monkeypatch.setattr(G, "measure", lambda: found)
    monkeypatch.setattr(G, "read_baseline", lambda: baseline)
    with pytest.raises(SystemExit) as exit:
        G.main()
    return exit.value.code, capsys.readouterr().err


def test_every_check_declares_where_its_evidence_comes_from():
    """An unclassified check would silently never warn, which is the failure mode."""
    assert set(G.SOURCE) == {label for label, *_ in G.CHECKS}
    assert G.SOURCE["multi_name.family"] == G.OBJECTS
    assert G.SOURCE["multi_name.different"] == G.OBJECTS
    assert G.SOURCE["ctor_vtable.contradicted"] == G.IMAGE
    assert G.SOURCE["ctor_vtable.unreadable"] == G.IMAGE
    assert G.SOURCE["size_outlier.indicted"] == G.IMAGE


def test_an_object_derived_regression_warns_about_a_poisoned_tree(monkeypatch, capsys):
    """The exact shape of the incident: multi_name.different goes 0 -> 1."""
    code, err = _run(monkeypatch, capsys,
                     {"multi_name.different": 1}, {"multi_name.different": 0})
    assert code == 1
    assert "multi_name.different: 0 -> 1" in err
    assert WARNING in err
    assert "Rebuild the sources" in err


def test_an_image_derived_regression_does_not_blame_the_build(monkeypatch, capsys):
    """ctor_vtable reads retail, so a rebuild would not change its answer.

    Emitting the warning here would teach the reader to ignore it in the one
    case where it matters.
    """
    code, err = _run(monkeypatch, capsys,
                     {"ctor_vtable.contradicted": 50}, {"ctor_vtable.contradicted": 49})
    assert code == 1
    assert "ctor_vtable.contradicted: 49 -> 50" in err
    assert WARNING not in err


def test_a_mixed_regression_names_only_the_object_derived_key(monkeypatch, capsys):
    """Both fail, but only one of them is worth rebuilding for."""
    code, err = _run(monkeypatch, capsys,
                     {"multi_name.family": 3, "ctor_vtable.contradicted": 50},
                     {"multi_name.family": 2, "ctor_vtable.contradicted": 49})
    assert code == 1
    assert "multi_name.family: 2 -> 3" in err
    assert "ctor_vtable.contradicted: 49 -> 50" in err
    # The warning line names the keys worth rebuilding for, and only those.
    warning_line = next(l for l in err.splitlines() if WARNING in l)
    assert "multi_name.family" in warning_line
    assert "ctor_vtable.contradicted" not in warning_line


def test_a_drop_still_fails_and_says_nothing_about_the_build(monkeypatch, capsys):
    """A fix must lower the baseline, and that is not a staleness question."""
    code, err = _run(monkeypatch, capsys,
                     {"multi_name.different": 0}, {"multi_name.different": 1})
    assert code == 1
    assert "FIXED" in err
    assert WARNING not in err
