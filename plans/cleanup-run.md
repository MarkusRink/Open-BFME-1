# Twelve-hour cleanup execution

Started: 2026-09-07 16:41:55 UTC (2026-09-08 01:41:55 JST).
Work deadline: 2026-09-08 04:41:55 UTC (13:41:55 JST).
Execution base after pull: `8fe7448503316d344fb623d467f3b107126cd9c5`.
Status: phase 1 active; required full baseline verification in progress.

## Ownership

All worker roots are under ignored `build/cleanup-20260907/`; each has a
separate branch, index and build output. Coordinator alone publishes master.

| Worker | Root/branch suffix | Current exclusive responsibility |
|---|---|---|
| cleanup_metrics | metrics | Measurement prerequisite ready; WeaponTemplate*.cpp field naming (exclude shared headers and Weapon.cpp) |
| cleanup_placement | placement | Timed-operation filenames ready; two Bezier moves and their two active reference-link comments |
| cleanup_evidence | evidence | FESL locals ready; three scalar-sort/deque filenames and independent reviews |

## Initial checks

- Pull/rebase completed; check_csv passes with 161,804 function rows and 85,625
  symbol rows (one known row-less source).
- No other full build was visible in the process inventory at startup.
- Full baseline command: `BUILD_POOL=4 ./build.sh`; output:
  `build/cleanup-20260907-baseline.log`. Existing session 75817 must be polled,
  not relaunched. Baseline covers the execution base above.
- The starting readability score remains unavailable pending the explicit
  malformed-record repair. No cleanup delta is claimed yet.
- Existing contributor worktrees are preserved. No new service, port, database,
  shared cache or external fleet configuration is required.

## Publications

No source cleanup published yet. Planning/checkpoint commit `8fdebe9dbe` is not
counted as source progress. Full baseline is still live, so isolated preparation
continues while the publication checkout remains unchanged.

| Worker commit ready for integration | Effect and evidence | Verification/review |
|---|---|---|
| 4267db480a | Reject empty function records; remove exactly one stray LF | 91 targeted tests; independent 10-case recheck and byte-preservation audit |
| 248a2b008f | Repair five ownership markers; preserve unknown tree-buffer owner | 5/5 matches; independent destination/source review |
| 4bcdd08115 | 38 WeaponTemplate field names/114 uses; PreferredTargetBone corrects misleading projectile name | 1/1 match; direct retail field table and independent review; raw storage types preserved |
| e913a5b2fa | TimedOperationNode constructor/destructor filenames | 2/2 matches; source hashes unchanged; retail caller/vtable chain |
| 5f2e2d38b6 | postTimedOp filename | 1/1 match; source hash unchanged |
| 5e62348ced | TimedOperations filename for node update and queue pump | 2/2 matches; source hash unchanged |
| 64bbeae6a3 | Nine FESL address buffer/octet/packed-value identifiers | 2/2 matches and four literals before/after |
| 3ba9404332 | 33 more WeaponTemplate scalar property names/99 uses; preserve the +0x509 width discrepancy | 1/1 match; all 33 retail records and eight parsers independently reviewed |
| fa4df1cbc4 | Four minimum/maximum timing-bound names/12 uses | Matched getters and retail low/high argument order independently reviewed; 1/1 copy assignment |
| 3d7c1ee1d0 | Two Bezier implementations placed beside their family; repair include/navigation and stale status | 75/75 matches across three sources; eight source-field ledger changes |
| 507f767acf | SignedScalarHeapSort filename | 5/5 matches; source unchanged |
| 38c1a042ce | PSRequest deque destroy helper moved to its persistent-storage-thread family | 1/1 match; source unchanged |
| f16f0f3e22 | PSResponse deque destroy helper placed beside PSRequest | 1/1 match; source unchanged |

These are worker SHAs, not published SHAs. Superseded unpublished WeaponTemplate
commits 9aaadda33a and its earlier form must not be integrated.

The initial source-preparation queue is now paused before further expansion.
Naming worker is investigating ClearNuggets callback/WeaponTemplate ownership
without edits; placement worker has a proven six-use W4Vec helper rename ready;
evidence worker is diagnosing the long initial full gate from live process/cache
evidence. Baseline PID is 1524113. Do not restart while it is live.

At roughly 24 minutes the baseline diagnostic counted 13,816 matched TUs,
9,697 dependency sidecars refreshed since startup, 3,736 older sidecars and 383
absent objects. Compiler children continue advancing; no stuck TU was observed.
This is a broad cache refresh under host contention, not a blocked build lock.
The initial half-hour setup estimate may extend until this required verdict.

Ready next, after publication clears: rename the six source-local W4Vec uses to
BezierDifferenceVector (algorithm and unclaimed-symbol scope proven), and review
WeaponTemplate::parseClearNuggets as a descriptive callback identity. The latter
has direct table/ILT/owner evidence but requires exact ledger replacement and
retired-name handling; original nugget helper class names remain unproven.

## Startup observations and next experiment

Worker cold readability scans spent approximately two minutes before reaching the
known empty-record failure; that failure prevents cache persistence. Centralize
staged metrics in the repaired coordinator checkout and stop repeating scans in
unrepaired workers. Check the saved worker time and coordinator overhead at hour
one before retaining this process change. All byte/identity gates remain active.

Redirected baseline Python output is buffered even while compiler children are
active. Use `PYTHONUNBUFFERED=1` for later logged builds; never restart this live
baseline merely to improve its output.

## Hourly reviews

First due: 2026-09-07 17:41:55 UTC. Subsequent reviews are due at each elapsed
hour through hour 12. Record actual review times and measured experiment outcomes;
do not prefill reviews or assume a process change helped.

## Resume

Poll the baseline handle or inspect its specific process/log before any restart.
Await and independently review the measurement and marker worker commits.
Publish only after required verification. Then capture the first valid metric
baseline SHA and release the phase 2 naming/filename work.
