param(
    [Parameter(Mandatory = $true)][string]$Profile,
    [Parameter(Mandatory = $true)][int]$CpuCount,
    [Parameter(Mandatory = $true)][int]$Runs,
    [Parameter(Mandatory = $true)][string]$Executable,
    [string]$Arguments = "full"
)

# Physical/constrained Q4 helper. It does not install software, change the
# allocator default or select a winner. It applies processor affinity to the
# benchmark process, validates every run fail-closed and prints report-only
# results for the 64-byte class.
#
# Affinity limitation: the process is created by .NET and affinity is applied
# immediately after Start(). The effective mask is read back and logged, but
# the first process-startup instructions may execute before the assignment.
# Measurements are therefore labeled affinity=post_start_readback and are
# approximations, not proof of affinity from the first instruction.
$ErrorActionPreference = "Stop"

function Fail([string]$reason) {
    Write-Output ("PROFILE_FAIL profile={0} reason={1}" -f $Profile, $reason)
    exit 1
}

if ([string]::IsNullOrWhiteSpace($Profile)) { Fail "empty_profile" }
if ($CpuCount -lt 1 -or $CpuCount -gt 32) { Fail "invalid_cpu_count" }
if ($Runs -lt 1 -or $Runs -gt 100) { Fail "invalid_runs" }
if ([string]::IsNullOrWhiteSpace($Arguments)) { Fail "empty_arguments" }
if (-not (Test-Path -LiteralPath $Executable -PathType Leaf)) { Fail "missing_executable" }

$mask = (1 -shl $CpuCount) - 1
$exe = (Resolve-Path -LiteralPath $Executable).Path
$resolved = Get-CimInstance Win32_ComputerSystem
$os = Get-CimInstance Win32_OperatingSystem
$cpu = Get-CimInstance Win32_Processor
Write-Output ("HOST_PROFILE profile={0} cpu_count={1} affinity_mask=0x{2} host_logical={3} host_ram_gib={4} os={5} build={6} cpu={7}" -f `
    $Profile, $CpuCount, $mask.ToString("X"), $cpu.NumberOfLogicalProcessors, `
    [math]::Round($resolved.TotalPhysicalMemory / 1GB, 1), $os.Caption, $os.BuildNumber, $cpu.Name)

$completed = 0
for ($run = 1; $run -le $Runs; $run++) {
    $psi = New-Object System.Diagnostics.ProcessStartInfo
    $psi.FileName = $exe
    $psi.Arguments = $Arguments
    $psi.UseShellExecute = $false
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true
    $process = [System.Diagnostics.Process]::Start($psi)
    try {
        $process.ProcessorAffinity = [IntPtr]$mask
    } catch {
        Fail ("affinity_assignment_failed run={0}" -f $run)
    }
    $effective = [int64]$process.ProcessorAffinity
    if ($effective -ne [int64]$mask) {
        Fail ("affinity_readback_mismatch run={0} expected=0x{1} actual=0x{2}" -f `
            $run, $mask.ToString("X"), $effective.ToString("X"))
    }

    $stdout = $process.StandardOutput.ReadToEnd()
    $stderr = $process.StandardError.ReadToEnd()
    $process.WaitForExit()

    if ($process.ExitCode -ne 0) {
        Fail ("exit_code={0} run={1}" -f $process.ExitCode, $run)
    }
    if ($stderr.Trim()) {
        Fail ("stderr run={0}" -f $run)
    }
    $configCount = ([regex]::Matches($stdout, "ALLOC_BENCH_CONFIG")).Count
    $passCount = ([regex]::Matches($stdout, "ALLOC_BENCH_CORRECTNESS=PASS")).Count
    $okCount = ([regex]::Matches($stdout, "ALLOC_BENCH_OK")).Count
    $resultCount = ([regex]::Matches($stdout, "ALLOC_BENCH allocator=")).Count
    if ($configCount -ne 1 -or $passCount -ne 2 -or $okCount -ne 1 -or $resultCount -lt 84) {
        Fail ("markers run={0} config={1} pass={2} ok={3} results={4}" -f `
            $run, $configCount, $passCount, $okCount, $resultCount)
    }

    $completed++
    Write-Output ("PROFILE_RUN profile={0} run={1} exit={2} affinity=0x{3} affinity_effective=0x{4} affinity_coverage=post_start_readback correctness=PASS ok=True results={5}" -f `
        $Profile, $run, $process.ExitCode, $mask.ToString("X"), $effective.ToString("X"), $resultCount)
    $stdout -split "`n" | Where-Object { $_ -match "ALLOC_BENCH_CONFIG|ALLOC_BENCH_CORRECTNESS|ALLOC_BENCH allocator=(malloc|new|pmr|system|mimalloc|rpmalloc) size=64 " }
}

if ($completed -ne $Runs) {
    Fail ("run_count expected={0} completed={1}" -f $Runs, $completed)
}
Write-Output ("PROFILE_SUMMARY profile={0} runs={1} failures=0 affinity=0x{2} affinity_coverage=post_start_readback" -f `
    $Profile, $completed, $mask.ToString("X"))
exit 0
