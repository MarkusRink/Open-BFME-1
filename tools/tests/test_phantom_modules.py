"""The two bugs that let a phantom pass screen and a real row get deleted.

Both are live defects, not hypotheticals. The row attribution used to match the
class only between two '@' separators, which cannot see `??0X@@` at all, so
three phantom ModuleData constructors survived a pass that was looking straight
at them. And `??0TechBuildingBehaviorModuleData@@QAE@XZ` cleared every
absence test there is and was still retracted wrongly, because ctor_vtable had
positive evidence -- read off the operand build.py masks -- that the body
installs that very class's vtable.

The blocker tests pin the four structural refusals as well, because each one
stands for bytes that would otherwise end up unclaimed or a source file left
with no rows.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import phantom_modules as P  # noqa: E402


def _row(name, rva="0x00100000", source="a.cpp"):
    return {"name": name, "export_rva": "", "target_rva": rva, "target_size": "26",
            "source": source, "status": "matched", "notes": ""}


def _blockers(candidates, rows=None, confirmed=(), classes=()):
    return P.blockers(candidates, rows if rows is not None else candidates,
                      set(confirmed), set(classes))


def test_a_leading_class_component_is_found():
    """`??0X@@` puts the class FIRST, where the old `@X@` pattern never looked.

    This is the whole miss: a constructor and a destructor name their class as
    the leading component, so a scan built around qualifiers sees a method row
    and is blind to the ctor/dtor rows sitting on the same class.
    """
    rows = [_row("??0CleanupHazardUpdateModuleData@@QAE@XZ"),
            _row("??1CleanupHazardUpdateModuleData@@UAE@XZ"),
            _row("??_GCleanupHazardUpdateModuleData@@UAEPAXI@Z"),
            _row("?getModuleNameKey@CleanupHazardUpdate@@UBE?AW4NameKeyType@@XZ")]
    found = P.rows_naming(rows, {"CleanupHazardUpdate"})
    assert [r["name"] for r in found["CleanupHazardUpdate"]] == [r["name"] for r in rows]


def test_a_module_data_row_is_attributed_to_its_module():
    """XModuleData registers under X, so its rows are X's rows."""
    rows = [_row("??0MinefieldBehaviorModuleData@@QAE@XZ")]
    assert P.rows_naming(rows, {"MinefieldBehavior"})["MinefieldBehavior"] == rows
    assert P.stem("MinefieldBehaviorModuleData") == "MinefieldBehavior"
    # 'ModuleData' alone is not somebody's suffix; it must survive whole.
    assert P.stem("ModuleData") == "ModuleData"


def test_a_nested_type_still_names_its_outer_class():
    """`vector<DetonatorInfo@MinefieldBehavior>` is a claim about MinefieldBehavior.

    These rows are the bulk of what an absent class holds, so missing them
    understates the lane badly.
    """
    row = _row("?begin@?$vector@UDetonatorInfo@MinefieldBehavior@@V?$allocator"
               "@UDetonatorInfo@MinefieldBehavior@@@_STL@@@_STL@@QAEPAU"
               "DetonatorInfo@MinefieldBehavior@@XZ")
    assert P.rows_naming([row], {"MinefieldBehavior"})["MinefieldBehavior"] == [row]


def test_a_row_is_attributed_to_a_class_once():
    """A name mentioning its class four times is still one row, not four."""
    row = _row("??$_Construct@UFlightDeckInfo@FlightDeckBehavior@@U12@@_STL@@YAXPAU"
               "FlightDeckInfo@FlightDeckBehavior@@ABU12@@Z")
    assert P.rows_naming([row], {"FlightDeckBehavior"})["FlightDeckBehavior"] == [row]


def test_vtable_evidence_about_this_body_blocks_the_retraction():
    """The TechBuildingBehaviorModuleData shape, which is why this screen exists.

    Every absence test passes and the address keeps another claimant, so the
    four structural rules all say go. ctor_vtable read the masked operand and
    says this body installs THIS class's vtable, and that outranks a missing
    string.
    """
    doomed = _row("??0TechBuildingBehaviorModuleData@@QAE@XZ")
    why = _blockers([doomed], rows=[doomed, _row("??0FontLibrary@@QAE@XZ", source="b.cpp")],
                    confirmed=[doomed["name"]])
    assert any(w.startswith("vtable-confirmed") for w in why[doomed["name"]])


def test_a_real_class_makes_its_other_rows_misplaced_not_phantom():
    """The FlightDeckBehavior shape: the ROW has no evidence, the CLASS does.

    A constructor elsewhere installs a vtable naming the class, so the class
    exists whatever its name does in the image. A row of a real class on the
    wrong bytes is a misplacement, and the fix for that is to move the row --
    deleting it throws away a true identity.
    """
    doomed = _row("?getClassMemoryPool@FlightDeckBehavior@@CAPAVMemoryPool@@XZ")
    why = _blockers([doomed],
                    rows=[doomed, _row("?getClassMemoryPool@AIUpdateInterface@@CAPAVMemoryPool@@XZ",
                                       source="b.cpp")],
                    classes=["FlightDeckBehavior"])
    assert any(w.startswith("real-class") for w in why[doomed["name"]])


def test_the_last_claimant_on_an_address_is_never_dropped():
    """Retracting it would leave the bytes unclaimed, which is not an improvement."""
    doomed = _row("?friend_newModuleData@BaseRegenerateUpdate@@SAPAVModuleData@@PAVINI@@@Z")
    why = _blockers([doomed])
    assert any(w.startswith("sole-claimant") for w in why[doomed["name"]])


def test_a_batch_may_not_empty_an_address_between_them():
    """Two rows that each look safe alone still unclaim the address together.

    0x00123180 is the live case: all four buildFieldParse rows on it name an
    absent class, so a per-row screen clears every one and the batch leaves
    nothing behind.
    """
    a = _row("?buildFieldParse@SpyVisionUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z")
    b = _row("?buildFieldParse@GenerateMinefieldBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z",
             source="b.cpp")
    why = _blockers([a, b])
    assert any(w.startswith("all-claimants-picked") for w in why[a["name"]])
    assert any(w.startswith("all-claimants-picked") for w in why[b["name"]])


def test_a_source_file_is_never_left_with_no_rows():
    """A TU whose every row goes is a TU whose real identity was never found."""
    doomed = _row("?buildFieldParse@DamDieModuleData@@SAXAAVMultiIniFieldParse@@@Z",
                  source="DamDie.cpp")
    keeps = _row("?buildFieldParse@DieModuleData@@SAXAAVMultiIniFieldParse@@@Z",
                 source="DieModule.cpp")
    why = _blockers([doomed], rows=[doomed, keeps])
    assert any(w.startswith("empties-source") for w in why[doomed["name"]])


def test_the_only_symbol_naming_a_vtable_is_kept():
    """Retracting the address's one attester unnames it for every other row.

    ctor_vtable resolves a vtable slot through the ledger, so dropping the last
    ??_G / getClassMemoryPool / ??_7 name at an address does not just lose this
    row -- it moves other rows' verdicts.
    """
    doomed = _row("??_GHiveStructureBodyModuleData@@UAEPAXI@Z")
    plain = _row("?update@HiveStructureBody@@UAEXXZ", source="b.cpp")
    why = _blockers([doomed], rows=[doomed, plain])
    assert any(w.startswith("sole-attester") for w in why[doomed["name"]])


def test_a_row_clearing_every_screen_reports_no_blockers():
    """The screen has to be able to say yes, or it is not a screen."""
    doomed = _row("?getCommandOption@SpectreGunshipUpdate@@UBE?AW4CommandOption@@XZ")
    peer = _row("?Get_Sort_Level@RenderObjClass@@UBEHXZ", source="b.cpp")
    sibling = _row("?setLogicalStatus@SpectreGunshipUpdate@@IAEXW4GunshipStatus@@@Z",
                   rva="0x00200000")
    assert _blockers([doomed], rows=[doomed, peer, sibling])[doomed["name"]] == []
