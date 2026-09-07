#!/usr/bin/env python3
"""Which module classes the ledger names that BFME never shipped.

THE CLAIM AND WHAT BACKS IT. A module class is only reachable from INI if
ModuleFactory registers it, and the registration macro stringifies the class
identifier, so a shipped module class X necessarily puts the eight-to-forty
byte ASCII run "X" into the image. Two facts follow, and this tool reports
exactly those two, never an inference between them:

  ABSENT      the byte sequence of the class name occurs NOWHERE in
              lotrbfme.exe -- not as a literal, not inside a longer string, not
              anywhere in any section -- and Zero Hour registers a concrete
              module class of that name. BFME did not ship the class, so every
              ledger row naming it carries a borrowed Zero Hour name rather
              than an identity. This is a proof, not a search result.
  REGISTERED  reverse/module_registry.tsv lists it. The class exists and the
              registry gives its two factory bodies.

and three states it deliberately refuses to decide:

  UNREGISTERED_NAMED  the name is in the image but no registration uses it:
              abstract bases (UpdateModule, DieModule) whose names appear as
              module-type tags, plus classes reached some other way. Nothing is
              proved either direction.
  UNDECIDED   the name is absent from the image AND Zero Hour does not register
              it either -- an abstract base or a plain struct. Such a class
              needs no literal even when it exists, so absence proves nothing.
  SUBSTRING   the name occurs only inside a longer run. Reported separately
              because a suffix hit is not a literal.

WHY NOT JUST READ THE STRING POOL. The module names are not one blob. The
literal for LockWeaponCreate sits at 0x00C8FD94 among thirty neighbours, but
ModelConditionSoundSelectorClientBehavior is at 0x00C8E57C and W3DTreeDraw at
0x00D1D234, thousands of bytes away in either direction. Scanning one window
would have called both of those absent. The whole file is the search space.

  python3 tools/phantom_modules.py           # write reverse/phantom_modules.tsv
  python3 tools/phantom_modules.py --rows    # list the affected ledger rows
"""
import collections, csv, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
import module_registry as reg

OUT = build.ROOT / 'reverse/phantom_modules.tsv'
ZH_FACTORIES = [
    'reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp',
    'reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/Common/Thing/W3DModuleFactory.cpp',
]
FACTORY_SYMBOL = re.compile(r'^\?(friend_newModuleInstance|friend_newModuleData)@([A-Za-z0-9_]+)@@')
MODULE_FACTORY_TU = 'Code/GameEngine/Source/Common/Thing/ModuleFactory.cpp'
# The tree's spellings for 'not identified yet' name no class, so they can
# neither be confirmed nor contradicted here.
PLACEHOLDER = re.compile(r'^(Gen_|Rva[0-9A-F]{8}|Bfme|BFME)')
DATA = reg.DATA


def zh_registry():
    names = set()
    pat = re.compile(r'addModule[A-Za-z]*\(\s*([A-Za-z0-9_]+)\s*\)')
    for rel in ZH_FACTORIES:
        path = build.ROOT / rel
        if not path.exists():
            raise SystemExit(f"missing Zero Hour reference {rel}; it is the oracle for 'concrete module class'")
        names |= set(pat.findall(path.read_text(encoding='utf-8', errors='replace')))
    return names


def occurrences(name):
    """Count every occurrence of the raw byte sequence, and of a NUL-terminated
    run exactly equal to it, anywhere in the file."""
    raw = name.encode()
    total = terminated = 0
    i = DATA.find(raw)
    while i >= 0:
        total += 1
        if DATA[i + len(raw)] == 0:
            terminated += 1
        i = DATA.find(raw, i + 1)
    return total, terminated


def ledger_classes(rows):
    """Every class the ledger names through a module-factory symbol, plus every
    class named by a row placed in the ZH ModuleFactory translation unit."""
    out = collections.defaultdict(list)
    qualifier = re.compile(r'@([A-Za-z0-9_]+)@@')
    for r in rows:
        m = FACTORY_SYMBOL.match(r['name'])
        if m:
            if not PLACEHOLDER.match(m.group(2)):
                out[m.group(2)].append(r)
        elif r['source'] == MODULE_FACTORY_TU and '$' not in r['name']:
            # '$' means a template mangling, whose qualifier fragments
            # (PAUFXBoneInfo, W4NameKeyType) are type codes, not class names.
            for q in qualifier.finditer(r['name']):
                c = q.group(1)
                if c[0].isupper() and not PLACEHOLDER.match(c):
                    out[c].append(r)
                    break
    return out


def classify():
    rows = reg.ledger_rows()
    table = reg.build_table()
    registered = {r['name'] for r in table}
    zh = zh_registry()
    universe = ledger_classes(rows)
    for n in zh:
        universe.setdefault(n, [])

    verdicts = {}
    for cls, rs in universe.items():
        # A ModuleData class registers under the class it belongs to.
        stem = cls[:-len('ModuleData')] if cls.endswith('ModuleData') and len(cls) > len('ModuleData') else cls
        total, terminated = occurrences(stem)
        if stem in registered:
            v = 'REGISTERED'
        elif total == 0 and stem in zh:
            v = 'ABSENT'
        elif total == 0:
            v = 'UNDECIDED'
        elif terminated:
            v = 'UNREGISTERED_NAMED'
        else:
            v = 'SUBSTRING'
        verdicts[cls] = dict(verdict=v, stem=stem, occurrences=total, terminated=terminated,
                             zh=stem in zh, rows=rs)
    return table, verdicts


def true_owner(table):
    inst = collections.defaultdict(set)
    data = collections.defaultdict(set)
    for r in table:
        inst[r['inst']].add(r['name'])
        data[r['data']].add(r['name'])
    return inst, data


def main():
    table, verdicts = classify()
    inst, data = true_owner(table)
    counts = collections.Counter(v['verdict'] for v in verdicts.values())
    print('  '.join(f"{k}={counts[k]}" for k in
                    ('REGISTERED', 'ABSENT', 'UNREGISTERED_NAMED', 'SUBSTRING', 'UNDECIDED')))

    if '--rows' in sys.argv:
        for cls in sorted(c for c, v in verdicts.items() if v['verdict'] == 'ABSENT'):
            for r in sorted(verdicts[cls]['rows'], key=lambda x: x['target_rva']):
                m = FACTORY_SYMBOL.match(r['name'])
                owner = ''
                if m:
                    a = int(r['target_rva'], 16)
                    who = (inst if m.group(1).endswith('Instance') else data).get(a)
                    owner = '|'.join(sorted(who)) if who else ''
                print(f"{cls}\t{r['target_rva']}\t{r['target_size']}\t{r['status']}\t{owner}\t{r['name']}\t{r['source']}")
        return

    with open(OUT, 'w', newline='', encoding='utf-8') as f:
        w = csv.writer(f, delimiter='\t', lineterminator='\r\n')
        w.writerow(['class', 'verdict', 'registration_name', 'image_occurrences',
                    'nul_terminated_runs', 'zh_registers_it', 'ledger_rows', 'claimed_rvas'])
        for cls in sorted(verdicts):
            v = verdicts[cls]
            rvas = sorted({r['target_rva'] for r in v['rows']})
            w.writerow([cls, v['verdict'], v['stem'], v['occurrences'], v['terminated'],
                        'yes' if v['zh'] else 'no', len(v['rows']), ' '.join(rvas)])
    print(f"{OUT.relative_to(build.ROOT)}: {len(verdicts)} classes")


if __name__ == '__main__':
    main()
