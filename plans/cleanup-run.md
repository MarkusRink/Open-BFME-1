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
| cleanup_metrics | metrics | Empty ledger record/checker discrepancy and related regression; metric baseline |
| cleanup_placement | placement | Five malformed source ownership markers; source verification |
| cleanup_evidence | evidence | Independent field/local-name evidence; scoped root verification |

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

No source cleanup published yet. Planning/checkpoint commits are not counted as
source progress. Each accepted unit will record its final SHA, concrete effect,
identity evidence and verification here.

## Hourly reviews

First due: 2026-09-07 17:41:55 UTC. Subsequent reviews are due at each elapsed
hour through hour 12. Record actual review times and measured experiment outcomes;
do not prefill reviews or assume a process change helped.

## Resume

Poll the baseline handle or inspect its specific process/log before any restart.
Await and independently review the measurement and marker worker commits.
Publish only after required verification. Then capture the first valid metric
baseline SHA and release the phase 2 naming/filename work.
