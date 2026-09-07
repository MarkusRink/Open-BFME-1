# Twelve-hour cleanup execution

Started: 2026-09-07 16:41:55 UTC (2026-09-08 01:41:55 JST).
Deadline: 2026-09-08 04:41:55 UTC (13:41:55 JST).
Execution base: `8fe7448503316d344fb623d467f3b107126cd9c5`.
Status: phase 3 ownership/cohesion work is active. The phase 2 batch is published
through `49dc6716e0`; the next full integration gate includes this cutoff. The initial
full baseline completed with pre-existing failures; isolated workers continue.
The full gate has not passed. See [README.md](README.md) for the standing runbook.

## Ownership

All worker roots are under ignored `build/cleanup-20260907/`, with separate
branches, indexes and build outputs. Coordinator alone publishes master.

| Worker/root suffix | Current exclusive responsibility |
|---|---|
| cleanup_metrics / metrics | TeamPrototype comment correction; LadderInfo and DataChunk commits queued |
| cleanup_placement / placement | LAN cohesion queued; independent hour 3 and TeamPrototype review |
| cleanup_evidence / evidence | Corrected block writer/helper queued; read-only NetPacket/Eva cohesion screen |

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

Forty-nine prerequisite/source commits are confirmed ancestors of origin/master
at 19:40 UTC: 48 source units and one prerequisite. Planning and review-only
commits are excluded. Worker and published identities are separate; this table
lists final published SHAs.

| Improvement | Published SHAs | Integrated verification |
|---|---|---|
| Empty-record guard; exact stray LF removal | c142e08ecb | 75 tests; independent byte-preservation audit |
| 75 WeaponTemplate fields / 225 uses | 3406b8eabc, 03748815ed, 65316044a3 | Same 1,185-byte assignment; 1/1 each |
| Five ownership markers | cc09850f21 | 5/5 |
| Timed operation filenames | 435e677296, e48c028bed, 85435d54df | 2/2, 1/1, 2/2 |
| Nine FESL identifiers | 4a49123237 | 2/2 and four literals |
| Bezier family placement | 344947accd | 75/75 |
| Sort and PSRequest/PSResponse deque placement | 17924caf0f, f183a6ff46, dabeba4b0f | 5/5, 1/1, 1/1 |
| GameState setter; stale GameSlot duplicate | 64547bf46d, 030c21d0b7 | 75-byte match; 2/2 surviving |
| Wide construction; ASCII range destruction | 411ccb6d11, 18493b9cc5 | Exact 66/33-byte bodies; caller/callee identity |
| Canonical XferSave source, 375 lines removed | 3d5c9a24f5 | 2/2; reference bodies preserved |
| Archive forwarding / Detailed pair | dfea7264bf | 43/43 |
| ClearNuggets callback | 39d20f0a2c | 132-byte match; retail table |
| Detailed construction and EH ownership | 7e528a2f37 | 45/45 |
| ArchivedFileInfo pair identities | 119cc727c7 | 172/172 across affected family |
| Six vector payload repairs and helpers | e9ab38ad66, ab278985a2, f8a7496214, df39e0b0d9, 780a03ae7c, f3e2f9d63a | 29/29 through 39/39; all 24 routes re-derived |
| Bezier difference-vector name | f96e28e852 | 7/7 |
| IP enumeration cohesion and opaque storage | 4b7e57c577, 82b6229606 | 6/6; one TU and 40 lines removed |
| Water array types, owner, paths and point fields | 61de60bf96, b215debf16, 6059ef5c6f, 94be7599a6 | 2/2 then 3/3; false pin removed; unknown original owner explicit |
| Honest 48-byte record; simpler archive pair | 98527989b3, f6ae151a4b | 2/2 and 1/1; archive pair removes three lines |
| Actual multiplayer color pair and STLport | 41d7fb7883 | 98/98 across six sources |
| LadderPref copy, pair/EH ownership and map placement | ac87dfbfd0, df88350659, 38603315c2, 904b626b31 | 3/3 through 6/6; map 1/1; 95 bytes converted to real C++ |
| STLport out-of-memory allocator identity | 15a90a0d51 | 3/3 family; 78 bytes converted; 95-line dump becomes 40 lines |
| Subsystem setter; retire false Player alias | fc22cf46e6, 577c439483 | 1/1 each; matched caller evidence |
| Wide pair; honest unknown narrow setter | e36a1744d7, 4bd89709c0 | 2/2 and 1/1 |
| LAN username and slot-lookup filenames/navigation | fac2890274, 49dc6716e0 | 15/15, then 20/20 across six affected sources |

The last vector push raced another contributor, then published after a clean
rebase; final published additions/deletions equal the reviewed worker patch.
The first 26 source units were published before 18:41:55; the final vector unit
published during the hour 2 review. Initial planning commits: 26e52f92a2,
72482bb98a, 577f32a077; hour 1 checkpoint: 81a06ec1cf; hour 2: b64e8e92db.
The next 21 source units were published after that review and before 19:40 UTC.

## Reviewed integration queue

Worker SHAs below are prepared, not delivered. Preserve each branch's order;
append-only union ledgers can silently import dependency rows out of order.
All units received independent review. Coordinator rechecks the integrated diff
and all affected surviving sources before normal commit/push.

| Lane | Worker SHAs in order | Improvement |
|---|---|---|
| placement | 4917a76344 | Three LAN runtime bodies in one TU; 71 lines removed, 16/16 |
| evidence | 1a75102a91, 65b1da9bca | Honest block-position helper and address-named block writer; 50/230 bytes, 2/2 |
| metrics | dfa629c80e, 4b680ca8db, 31613137b6 | LadderInfo placement 25/25; real DataChunk constructor 45/45; TeamPrototype comments 7/7 |

These wait until the full integration snapshot finishes. Metrics now uses branch
`cleanup-20260907-metrics-h3` from published `904b626b31`; its old branch is
preserved. Evidence's superseded helper `61ace767d7` is preserved only on
`cleanup-20260907-evidence-xfer-before-owner`; never integrate it.

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

### Hour 2: reviewed 18:42–18:45 UTC

- Delivered: the 27 source units above, plus the hour 1 prerequisite. All 28
  commit ancestries were checked. Prepared Water/IP/neutral-record/color work is
  excluded. Twenty-six source units landed before the second-hour boundary;
  the final vector unit landed during this review. This drew on work prepared
  during hour 1 and is not a steady-state throughput forecast.
- Independent sample: final vector overflow is exactly the previously reviewed
  blob c05c90e0ebb00d60e4959e15826a4735e15104f2. All old-object reads precede
  destruction; placement construction then initializes the same complete,
  nonconst vector from locals. A destroy-then-write draft was caught before
  publication. XferSave source preservation and the 172-claim archive integration
  were also checked. Unknown original payload names remain visibly unknown.
- Concrete outcomes include 75 evidenced field names, coherent filenames,
  removal of duplicate source and false aliases, and exact clean-C++ replacements
  for some generated claims. No generated source files were edited. Existing
  full-gate failures remain explicit; the row-less XferSave defect is repaired,
  but a fresh full gate is still pending.
- Readability: most naming/path units have no measurable delta. Three observed
  co-location increments were +0.01 pp each; the final truthful vector payload
  correction has SrcIdent -0.01 pp. Accuracy takes precedence over the score.
  Total byte coverage usually changed +0.00 pp; category reclassification is
  reported separately. Whole-repo movement from other contributors is excluded.
- Hour 1 experiment retained: the four later vector units used the target/route
  matrix with zero post-compilation route rejects and 2, 1, 1, 2 scoped compile
  rounds. The color-pair unit separately needed three drafts to emit its exact
  destructor; a successful matrix is not a universal one-pass guarantee.
- Timing: 19 fully recorded normal publication loops had median 67.03s and total
  1,263.40s. These omit manual units and push-retry delays, so they are not the
  complete hour's integration cost. Five warm metadata hooks averaged 16.887s
  with no duplicate compilation. No timed counterfactual proves a percentage
  speedup from centralized readability scans or avoiding probe/build duplication.
- Integration defect caught before commit: out-of-order ClearNuggets cherry-pick
  imported a dependency tombstone through the union merge driver. The hook
  rejected it. Restored only the three owned paths, integrated the dependency
  first, and verified success. Added an untracked publication check comparing
  exact patch additions/deletions; it reproduced rejection of the captured bad
  patch. Path whitelists alone did not protect append-only ledger contents.
- Next single adjustment: send stable caller/type evidence during implementation
  so the independent final review focuses on the completed delta. Pilot readiness
  to approval was 42.772s; semantic review had already finished. Measure the next
  two readiness-to-approval intervals and record findings at hour 3. The pilot's
  13.256s hook also skipped pin checks, so its speed is not credited to overlap.
- Next: drain the reviewed queue in dependency order, then run the full gate on
  a frozen integration SHA using the warm cache. Workers continue in isolated
  roots. No full gate currently runs. Next review: 19:41:55 UTC.

### Hour 3: reviewed 19:42–19:43 UTC

- Delivered: 49 source/prerequisite commits, all ancestry-confirmed; 48 are
  source units. Twenty-one source units landed since the hour 2 review, plus
  the final vector unit during that review: 22 in the elapsed third hour, or
  7.3 per nominal worker-hour across three lanes. This includes carried-over
  preparation and is not a measurement of editing effort. Prepared queue work
  above is excluded.
- Independent landed sample found no material regression. Water's constructor
  allocation/initializer and bounding-box call establish the small object's
  point storage, count and validity fields; its original class name remains
  explicitly unknown. Ladder copy/destruction now uses real string lifetimes
  and the vendor pair; retail callback routes and both unwind maps were checked.
  Repeated ledger names and unmatched reference callers were not counted as
  independent identity witnesses. No unchanged green source was rebuilt by the
  reviewer.
- The highest-risk pending block writer was byte-green but lacked evidence for
  the original XferSave class spelling. Review caught that before publication.
  The corrected queue uses Rva009D8630BlockWriter, a descriptive position-stack
  helper and RTTI-backed XferException metadata. The old helper commit is kept
  on an explicit branch, not published. A normal member call also resolved all
  16 register differences in the banked body in one roughly 0.8s probe: verify
  callee ABI/visibility before trying speculative register shapes.
- Concrete outcomes include the 40-line IP reduction, coherent Water ownership,
  truthful LAN string identities, and 173 bytes of naked code replaced by real
  LadderPref/allocator C++. Most naming/path metrics remain unchanged. Local
  moves included +0.01 pp and -0.01 pp results; honest unknown Water ownership
  reduced SrcIdent by 0.01 pp. These are not reasons to restore false claims.
  Whole-repository coverage movement from other contributors is excluded.
- Hour 2 experiment: early evidence packets remain useful, but no overall
  speedup is established. Two later review waits were 93s and 307.277s. Across
  13 recorded packets the median was 120s, range 42–307.277s. Fifteen complete
  normal publication loops had median
  63.65s and total 888.20s; this omits retries/manual paths and is not total
  integration time. Push races were a separate recurring delay.
- Two stale-branch union merges imported unrelated ledger changes. Exact patch
  checks caught both before compilation/commit; restored only owned paths and
  reapplied the reviewed original patch without a merge. The guard now compares
  additions/deletions both before commit and after rebase. One worker's broad
  ledger byte replacement was also caught and narrowed before commit. Baselines
  were never increased. Metrics was refreshed at a clean, drained boundary;
  whether that reduces coordinator merge rejection is still unmeasured.
- Next single experiment: assign one named final reviewer upfront, retaining
  early evidence sharing. Target readiness-to-approval under 120s for three
  packets; also record when the author resumes to expose delivery/handling
  delay. TeamPrototype pilot: approval 116.702s, author resume 182.863s, so the
  first threshold passed but end-to-end speedup is not established. Placement
  reviews that unit; metrics reviews the next approved evidence-lane unit.
  Explicit original-owner evidence or an unknown-owner statement is now part
  of ordinary identity review after the block-writer finding.
- Next: publish this checkpoint, freeze the coordinator tree and run one full
  gate with BUILD_POOL=4 and unbuffered logging. The cold baseline still has
  five red categories. Its complete failure census is 214; an earlier narrow
  parser omitted 32 reference-path failures, now retained in the ignored
  baseline-failures.json. Compare exact failure identities, not just totals.
  Workers keep isolated reviewed commits and bounded read-only investigations.
  Next review: 20:41:55 UTC.

## Resume

Integrate one worker commit at a time with no-commit cherry-pick, review staged
paths, byte-verify affected surviving sources, measure staged readability, and
commit normally. Pull/rebase, check_csv, progress, normal push, final pull and
published-ancestry confirmation. Never weaken gates for pre-existing failures.
Use PYTHONUNBUFFERED=1 for subsequent logged builds to expose live output.
