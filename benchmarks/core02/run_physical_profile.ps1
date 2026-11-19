param(
    [Parameter(Mandatory = $true)][string]$Profile,
    [Parameter(Mandatory = $true)][int]$CpuCount,
    [Parameter(Mandatory = $true)][int]$Runs,
    [Parameter(Mandatory = $true)][string]$Executable
)

# Physical/constrained Q4 helper. It does not install software, change the
# allocator default or select a winner. It sets processor affinity on the
# benchmark process and prints report-only results for the 64-byte class.
$ErrorActionPreference = "Stop"
$mask = (1 -shl $CpuCount) - 1
$exe = (Resolve-Path $Executable).Path
$resolved = Get-CimInstance Win32_ComputerSystem
$os = Get-CimInstance Win32_OperatingSystem
$cpu = Get-CimInstance Win32_Processor
Write-Output ("HOST_PROFILE profile={0} cpu_count={1} affinity_mask=0x{2} host_logical={3} host_ram_gib={4} os={5} build={6} cpu={7}" -f `
    $Profile, $CpuCount, $mask.ToString("X"), $cpu.NumberOfLogicalProcessors, `
    [math]::Round($resolved.TotalPhysicalMemory / 1GB, 1), $os.Caption, $os.BuildNumber, $cpu.Name)

for ($run = 1; $run -le $Runs; $run++) {
    $psi = New-Object System.Diagnostics.ProcessStartInfo
    $psi.FileName = $exe
    $psi.Arguments = "full"
    $psi.UseShellExecute = $false
    $psi.RedirectStandardOutput = $true
    $psi.RedirectStandardError = $true
    $process = [System.Diagnostics.Process]::Start($psi)
    $process.ProcessorAffinity = [IntPtr]$mask
    $stdout = $process.StandardOutput.ReadToEnd()
    $stderr = $process.StandardError.ReadToEnd()
    $process.WaitForExit()
    $ok = $stdout -match "ALLOC_BENCH_OK"
    Write-Output ("PROFILE_RUN profile={0} run={1} exit={2} affinity=0x{3} ok={4}" -f `
        $Profile, $run, $process.ExitCode, $mask.ToString("X"), $ok)
    $stdout -split "`n" | Where-Object { $_ -match "ALLOC_BENCH_CONFIG|ALLOC_BENCH_CORRECTNESS|ALLOC_BENCH allocator=(malloc|new|pmr|system|mimalloc|rpmalloc) size=64 " }
    if ($stderr.Trim()) {
        Write-Output ("PROFILE_STDERR " + ($stderr.Trim() -replace "`n", " | "))
    }
}
