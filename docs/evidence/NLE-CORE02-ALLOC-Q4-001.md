# NLE-CORE02-ALLOC-Q4-001 — Physical Q4 attempt

**Status:** `BLOCKED FOR FULL Q4 MATRIX / WINDOWS PHYSICAL-INFERRED PARTIAL / NO ALLOCATOR SELECTION / REPORT_ONLY`. **Base:** `28b6105cb0d194e6dee81910e744093bb843324d`. **WO:** [NLE-CORE02-ALLOC-Q4-001](../work-orders/NLE-CORE02-ALLOC-Q4-001.md). **Parent:** [NLE-CORE02-ALLOC-001](NLE-CORE02-ALLOC-001.md). **Issue:** #19.

## 1. Source Check and authorization

- `main` verificado: `28b6105cb0d194e6dee81910e744093bb843324d`; árvore limpa; PRs #495/#496 integradas.
- Owner autorizou **somente** a etapa física Q4, mantendo Q1=A/Q2=B/Q3=A/Q4=B/Q7=A.
- CORE-02 permanece **NOT_QUALIFIED**; NLE-D009 `OPEN`; G3 `NOT_CLEARED`; nenhum allocator selecionado.

## 2. Host inventory (available hosts only)

| Item | Observado |
|---|---|
| OS | Microsoft Windows 11 Pro 10.0.26300 (build 26300), x64 |
| Board | ASUSTeK PRIME B450M-GAMING/BR, BIOS AMI 4645 |
| CPU | AMD Ryzen 3 4300GE, 4 cores / 8 logical processors |
| RAM | 15.1 GiB total; 2 × 8 GiB 2400 MHz |
| Virtualization | `HypervisorPresent=True`; VBS/Hyper-V em execução |
| Compiler | MSVC 14.44.35207, Release x64 |
| Harness SHA256 | `0DBFC13322DBE39AB5B69599B72BEC2E2C150393C49A80CFAD8DD6510C6EE6BF` |

**Physical status:** SMBIOS, placa-mãe ASUS, CPU desktop e dois módulos DIMM indicam **host físico local**, não runner CI. `HypervisorPresent=True` e VBS ativo impedem uma prova criptográfica de bare-metal; o estado é registrado como `PHYSICAL_INFERRED_NOT_CERTIFIED`. Nenhum ambiente virtualizado foi contado como máquina física.

**Outros hosts:** não há acesso autorizado ou disponível a host físico Ubuntu 24.04 x64 ou macOS 15 arm64. WSL, containers, VMs e runners CI não foram usados como evidência física. Nenhum software foi instalado em host externo.

## 3. Q4 coverage matrix

| OS required | Physical host | 2 vCPU / 4 GiB | 4 vCPU / 8 GiB | Status |
|---|---|---|---|---|
| Windows 11 x64 | ASUS B450M / Ryzen 3 4300GE / 15.1 GiB (inferred physical) | Affinity 2 CPUs; memory profile **not capped** (host 15.1 GiB) | Affinity 4 CPUs; memory profile **not capped** | **PARTIAL_CONSTRAINED** |
| Ubuntu 24.04 x64 | none available | — | — | **BLOCKED** |
| macOS 15 arm64 | none available | — | — | **BLOCKED** |

The Windows rows are **not** a 2 vCPU/4 GiB or 4 vCPU/8 GiB physical machine; they are logical CPU constraints on a larger physical host. The 4 GiB/8 GiB memory envelopes were not enforced, so these rows do not satisfy the exact Q4 profile requirement. Full Q4 is therefore **BLOCKED**.

## 4. Commands and profile reproduction

Build (already merged harness):

```powershell
cmake --preset core02-alloc-bench
cmake --build --preset core02-alloc-bench --target stormline_core02_allocator_bench
```

Execution helper committed in `benchmarks/core02/run_physical_profile.ps1`:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File benchmarks/core02/run_physical_profile.ps1 `
  -Profile win11_2vcpu_logical -CpuCount 2 -Runs 3 `
  -Executable build/core02-alloc-bench/stormline_core02_allocator_bench.exe

powershell -NoProfile -ExecutionPolicy Bypass -File benchmarks/core02/run_physical_profile.ps1 `
  -Profile win11_4vcpu_logical -CpuCount 4 -Runs 3 `
  -Executable build/core02-alloc-bench/stormline_core02_allocator_bench.exe

powershell -NoProfile -ExecutionPolicy Bypass -File benchmarks/core02/run_physical_profile.ps1 `
  -Profile win11_host_8c -CpuCount 8 -Runs 3 `
  -Executable build/core02-alloc-bench/stormline_core02_allocator_bench.exe
```

The helper sets `ProcessorAffinity` (`0x3`, `0xF`, `0xFF`), runs the merged harness in `full` mode three times, and logs exit/status. It does not install tools, change the default allocator or select a winner. Raw output: [NLE-CORE02-ALLOC-Q4-raw.txt](NLE-CORE02-ALLOC-Q4-raw.txt).

## 5. Results (report-only; 64-byte class)

All **9/9 runs** across the three Windows profiles exited 0 and reported `ALLOC_BENCH_CORRECTNESS=PASS` and `ALLOC_BENCH_OK`. Values are median (min–max) of 3 runs, ns per allocate/free pair; **no threshold, ranking or winner**.

### Windows profile 2 CPUs (`0x3`)

| Allocator | 1 thread | 4 threads |
|---|---:|---:|
| malloc | 34.035 (33.164–36.715) | 98.041 (96.974–146.395) |
| new | 40.214 (37.546–46.809) | 117.309 (113.688–164.644) |
| pmr | 43.036 (41.165–51.977) | 120.925 (114.773–155.482) |
| system | 47.250 (46.365–48.689) | 126.412 (115.886–141.326) |
| mimalloc | 6.691 (6.141–9.406) | 20.484 (13.691–25.044) |
| rpmalloc | 5.654 (5.599–5.825) | 20.100 (16.116–20.432) |

### Windows profile 4 CPUs (`0xF`)

| Allocator | 1 thread | 4 threads |
|---|---:|---:|
| malloc | 34.763 (32.886–38.698) | 81.184 (73.225–81.280) |
| new | 44.208 (36.713–44.789) | 80.819 (77.077–82.920) |
| pmr | 43.450 (40.125–44.282) | 83.503 (81.137–85.229) |
| system | 49.658 (49.240–92.329) | 85.299 (83.327–86.724) |
| mimalloc | 7.131 (6.805–10.300) | 32.661 (22.309–34.176) |
| rpmalloc | 5.817 (5.575–7.290) | 25.601 (15.619–28.116) |

### Windows host 8 logical CPUs (`0xFF`)

| Allocator | 1 thread | 4 threads |
|---|---:|---:|
| malloc | 36.983 (32.628–39.560) | 86.547 (86.543–89.766) |
| new | 37.831 (37.685–40.580) | 89.239 (64.528–90.234) |
| pmr | 41.384 (40.267–43.383) | 63.230 (60.570–88.924) |
| system | 44.471 (43.712–60.699) | 88.984 (88.070–93.614) |
| mimalloc | 6.752 (5.984–9.682) | 17.676 (16.996–31.292) |
| rpmalloc | 7.513 (5.640–8.807) | 26.744 (23.872–27.655) |

Higher 4-thread values under 2-CPU affinity are consistent with oversubscription; this is a workload observation, not a failure or ranking. Cross-run variance is visible, especially in system/pmr and 2-CPU runs. No p95/p99/RSS/fragmentation/thermal metric was established.

## 6. Stability and integrity

- 3 runs per profile; 9/9 exit 0; correctness PASS; `ALLOC_BENCH_OK`.
- No crash, null allocation, alignment failure, checksum mismatch or override (`override=none`).
- Timing is report-only. `peak_working_set_mib` is not reported because the process object did not expose a reliable post-exit peak; host RAM is recorded, and no memory-footprint claim is made.
- Executable SHA256 recorded above; binary built Release/MSVC from the merged harness.

## 7. Gaps and minimum unblock procedure

1. **Ubuntu 24.04 x64 physical host** — BLOCKED: provide/authorize access to a physical host (or approved remote access) with the required OS; install permission only if separately authorized.
2. **macOS 15 arm64 physical host** — BLOCKED: same requirement.
3. **Exact 2 vCPU/4 GiB and 4 vCPU/8 GiB machines** — BLOCKED: the current Windows host is 8 logical/15.1 GiB. Either provide exact physical profile machines, or have the owner ratify a constrained-profile methodology with explicit CPU affinity **and** a hard memory cap. The current runs do not satisfy the exact profile requirement.
4. **Bare-metal certification** — current host is `PHYSICAL_INFERRED_NOT_CERTIFIED` due VBS/hypervisor; if cryptographic/physical certification is required, provide a host with auditable bare-metal receipts.
5. After hosts exist, rerun the same harness/commands three times per OS/profile and record CPU/RAM/OS/compiler/SHA/exit/correctness.

## 8. Verdict and limits

- **BLOCKED** for the full Q4 matrix; Windows evidence is partial/constrained and does not qualify the module or satisfy exact Q4 profiles.
- No allocator selected, no threshold, no ranking/winner, no production default/integration, no telemetry/leak/ABI/release claim.
- CORE-02 remains **NOT_QUALIFIED**; CORE-03 remains blocked; manifest unchanged (721 blocked / 22 completed / 5 approved / 0 ready); registry byte-identical.
- The owner must provide/authorize the missing physical hosts and exact profiles, or expressly decide whether constrained-profile evidence is acceptable; numerical thresholds and any allocator selection require a separate ratification.
