# Twelve-hour cleanup execution

Started: 2026-09-07 16:41:55 UTC (2026-09-08 01:41:55 JST).
Deadline: 2026-09-08 04:41:55 UTC (13:41:55 JST).
Execution base: `8fe7448503316d344fb623d467f3b107126cd9c5`.
Status: phase 2 integration active. Full baseline completed with pre-existing
failures; verified units are being published while isolated identity repairs run.
The full gate has not passed. See [README.md](README.md) for the standing runbook.

## Ownership

All worker roots are under ignored `build/cleanup-20260907/`, with separate
branches, indexes and build outputs. Coordinator alone publishes master.

| Worker/root suffix | Current exclusive responsibility |
|---|---|
| cleanup_metrics / metrics | Archive/Money alias evidence; reviewed WeaponTemplate and archive repairs ready |
| cleanup_placement / placement | Six vector payload identities and exact construction/overflow helpers |
| cleanup_evidence / evidence | AsciiString destruction identity; independent helper reviews |

Existing contributor worktrees are preserved. No new service, port, database,
shared writable cache or external fleet configuration is required.

## Baseline

Initial check_csv: 161,804 function rows, 85,625 symbol rows, one known row-less
source. `BUILD_POOL=4 ./build.sh` covered the execution base above; log:
`build/cleanup-20260907-baseline.log`. Session 75817 ended with exit 1 around
17:27 UTC and must not be polled or restarted by accident.

- 214/161,804 function comparisons failed.
- 98 new DIR32 inconsistencies; XferSave.cpp has zero matched rows.
- Null-relocation count is 65 versus baseline 66; attribution is needed before
  lowering it. Never raise baselines or restore false pins to hide failures.
- No-op patch unavailable because function verification produced no patchset.
- All 19,403 string literals and 1,111 empty-string references passed.
- The drive-map dependency fingerprint migration invalidated almost the entire
  old cache: 13,632/13,816 TUs compiled. This explained the roughly 45-minute
  gate; compiler children kept advancing. Source/pin history predates migration.

First valid readability snapshot: `9eb87c82a0` (before clean rebase to
`c142e08ecb`), log `build/cleanup-20260907-readability-baseline.log`.
Rounded ALL: Body 71, Ident 19, Types 79, Iface 50, Local 28, SSoT 21,
SrcIdent 60, BRI 47. There are 13,999 tracked sources, 298 outside measured
areas. The malformed parent has no valid score; no repair delta is invented.

## Publications

First publication: `c142e08ecb`, rejecting empty function records and removing
exactly one stray LF, plus planning commits `26e52f92a2`, `72482bb98a`,
`577f32a077`. Normal hooks/push passed; final pull confirmed published ancestry.
Progress versus remote: +0 bytes, +0.00 pp, expected for this prerequisite.
Planning commits are not source progress.

Source integration began with `ed7c33e0ac`: 38 WeaponTemplate field names/114
uses; 1/1 match, unchanged readability score. Not yet published at hour 1 review.

## Reviewed integration queue

These are worker SHAs, not final published SHAs. Preserve dependency order within
families. Superseded WeaponTemplate commit `9aaadda33a` must not be integrated.

| Worker commit | Concrete improvement | Evidence/checks |
|---|---|---|
| 4267db480a | Empty-record guard and exact stray-record removal | Integrated/published above; 75 local tests and independent byte audit |
| 248a2b008f | Five ownership markers repaired | 5/5 matches; destination review |
| 4bcdd08115 | 38 WeaponTemplate names, including PreferredTargetBone | Integrated as ed7c33e0ac; retail table and independent review |
| 3ba9404332 | 33 more WeaponTemplate names/99 uses | 1/1; all records/parsers independently decoded |
| fa4df1cbc4 | Four min/max timing fields/12 uses | Matched getters and argument order; 1/1 |
| e913a5b2fa | TimedOperationNode ctor/dtor filenames | 2/2; source bytes unchanged |
| 5f2e2d38b6 | postTimedOp filename | 1/1; source unchanged |
| 5e62348ced | TimedOperations filename | 2/2; caller/vtable ownership |
| 64bbeae6a3 | Nine FESL buffer/octet/value identifiers | 2/2, four literals |
| 3d7c1ee1d0 | Two Bezier sources moved beside their family | 75/75; include/navigation/status corrected |
| 507f767acf | SignedScalarHeapSort filename | 5/5; source unchanged |
| 38c1a042ce | PSRequest deque helper placed beside its owner | 1/1; source unchanged |
| f16f0f3e22 | PSResponse deque helper placed beside its owner | 1/1; source unchanged |
| 6f4fcf32b8 | GameState map setter replaces false network/Unicode alias | 75-byte match; matched caller and char-string callees |
| b3bed5173b | Retire stale duplicate GameSlot range | 2/2 surviving source; range already correctly owned |
| 53f8b841b4 | Real Unicode placement construction source | 66-byte match; wide callee/caller independently reviewed |
| 0fcbc89619 | Correct archive forwarding and Detailed pair identity | 43/43; independent type/callee review |
| 0cd7d17b51 | WeaponTemplate ClearNuggets callback ownership | 132-byte match; direct field-table/caller evidence |
| 914fa35d0b | Correct vector payload at 0035BA20 | 29/29; exact named target routes |
| 40f2ed6d2a | Correct vector payload at 0035BA70 | 30/30; exact named target routes |

## Hourly reviews

Reviews due at each elapsed hour through hour 12. Record actual times and
observed results; do not prefill reviews or claim unmeasured speedups.

### Hour 1: reviewed 17:41–17:46 UTC

- Delivered: prerequisite and planning publication above. Prepared source work
  is not delivery; other agents' changes on master are not this team's progress.
- Independent sample: empty-record guard and mixed-terminator tests; highest-risk
  pending GameState setter and vector route repairs. Setter caller, char-string
  callee and field offset support its name. Vector payload keeps an honest
  address name because original identity remains unresolved; equal size did not
  justify the old coordinate-pair identity.
- Prepared results include 75 evidenced WeaponTemplate names, coherent family
  moves and false-identity corrections. Names preserve unknown storage/types
  where retail evidence ends. Aggregate readability did not move for these
  member names; that metric does not measure local naming quality.
- Bottleneck: approximately 45 minutes in initial full verification. No accurate
  edit/review/rebase time split was captured, so none is estimated. Placement
  restored one byte-green draft after route-name validation rejected it.
- Prior experiment: stop repeated cold worker readability scans. This prevented
  known duplicate scans, but no timed before/after comparison proves a speedup.
  Retain provisionally; coordinator metrics are now warm (557 remaining cold
  blobs on the first successful snapshot).
- Next adjustment: make a target-identity/route matrix before editing identities
  with relocations. Hypothesis: zero post-compilation route rejects, at most two
  scoped compilations per unit. Review at hour 2. Cache observations remain
  measurements, not extra workflow changes: ClearNuggets used 2.832s scoped
  verification plus 17.546s normal commit; hook compiled 0/1 with current cache.
- Next owners are above; coordinator drains the reviewed queue and keeps the
  pre-existing full-build debt explicit. Next review: 18:41:55 UTC.

## Resume

Integrate one worker commit at a time with no-commit cherry-pick, review staged
paths, byte-verify affected surviving sources, measure staged readability, and
commit normally. Pull/rebase, check_csv, progress, normal push, final pull and
published-ancestry confirmation. Never weaken gates for pre-existing failures.
Use PYTHONUNBUFFERED=1 for subsequent logged builds to expose live output.
