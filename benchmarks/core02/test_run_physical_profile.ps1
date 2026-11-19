param(
    [Parameter(Mandatory = $true)][string]$FakeExecutable
)

$ErrorActionPreference = "Stop"

$helper = Join-Path $PSScriptRoot "run_physical_profile.ps1"
$powershell = (Get-Command powershell.exe).Source
$fake = (Resolve-Path -LiteralPath $FakeExecutable).Path
$temp = Join-Path $env:TEMP ("stormline-q4-helper-tests-" + [guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $temp | Out-Null
$failures = 0

function Invoke-Helper([string[]]$extra) {
    $stdout = Join-Path $temp ("helper-" + [guid]::NewGuid().ToString("N") + ".out")
    $stderr = Join-Path $temp ("helper-" + [guid]::NewGuid().ToString("N") + ".err")
    $arguments = @("-NoProfile", "-ExecutionPolicy", "Bypass", "-File", $helper) + $extra
    $process = Start-Process -FilePath $powershell -ArgumentList $arguments -Wait -PassThru `
        -RedirectStandardOutput $stdout -RedirectStandardError $stderr
    return [pscustomobject]@{
        ExitCode = $process.ExitCode
        Output = (Get-Content -LiteralPath $stdout -Raw -ErrorAction SilentlyContinue)
        Error = (Get-Content -LiteralPath $stderr -Raw -ErrorAction SilentlyContinue)
    }
}

function Expect-Exit([string]$name, [int]$expected, [string[]]$extra) {
    $result = Invoke-Helper $extra
    if ($result.ExitCode -ne $expected) {
        Write-Output ("TEST_FAIL name={0} expected={1} actual={2} output={3} error={4}" -f `
            $name, $expected, $result.ExitCode, $result.Output, $result.Error)
        $script:failures++
        return $null
    }
    Write-Output ("TEST_PASS name={0} exit={1}" -f $name, $result.ExitCode)
    return $result
}

$base = @("-Profile", "fake", "-CpuCount", "1", "-Runs", "1", "-Executable", $fake)
$successArgs = $base + @("-Arguments", "success")
$successResult = Expect-Exit "success" 0 $successArgs
if ($null -ne $successResult) {
    if ($successResult.Output -notmatch "PROFILE_SUMMARY profile=fake runs=1 failures=0") {
        Write-Output "TEST_FAIL name=success_summary output=$($successResult.Output)"
        $failures++
    }
    if ($successResult.Output -notmatch "affinity_effective=0x1") {
        Write-Output "TEST_FAIL name=success_affinity output=$($successResult.Output)"
        $failures++
    }
}

$exit7Args = $base + @("-Arguments", "exit7")
Expect-Exit "exit7" 1 $exit7Args | Out-Null
$missingOkArgs = $base + @("-Arguments", "missing_ok")
Expect-Exit "missing_ok" 1 $missingOkArgs | Out-Null
$missingCorrectnessArgs = $base + @("-Arguments", "missing_correctness")
Expect-Exit "missing_correctness" 1 $missingCorrectnessArgs | Out-Null
$shortResultsArgs = $base + @("-Arguments", "short_results")
Expect-Exit "short_results" 1 $shortResultsArgs | Out-Null

$cpuZeroArgs = @("-Profile", "fake", "-CpuCount", "0", "-Runs", "1",
                 "-Executable", $fake, "-Arguments", "success")
Expect-Exit "invalid_cpu" 1 $cpuZeroArgs | Out-Null
$runsZeroArgs = @("-Profile", "fake", "-CpuCount", "1", "-Runs", "0",
                  "-Executable", $fake, "-Arguments", "success")
Expect-Exit "invalid_runs" 1 $runsZeroArgs | Out-Null
$missingExeArgs = @("-Profile", "fake", "-CpuCount", "1", "-Runs", "1",
                    "-Executable", (Join-Path $temp "does-not-exist.exe"), "-Arguments", "success")
Expect-Exit "missing_executable" 1 $missingExeArgs | Out-Null

if ($failures -ne 0) {
    Write-Output ("Q4_HELPER_TESTS_FAILED failures={0}" -f $failures)
    exit 1
}
Write-Output "Q4_HELPER_TESTS_OK cases=8"
exit 0
