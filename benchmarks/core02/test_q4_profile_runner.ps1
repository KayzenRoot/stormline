param(
    [Parameter(Mandatory = $true)][string]$RunnerExecutable,
    [Parameter(Mandatory = $true)][string]$FakeExecutable
)

$ErrorActionPreference = "Stop"
$runner = (Resolve-Path -LiteralPath $RunnerExecutable).Path
$fake = (Resolve-Path -LiteralPath $FakeExecutable).Path
$temp = Join-Path $env:TEMP ("stormline-q4-runner-tests-" + [guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $temp | Out-Null
$failures = 0

function Invoke-Runner([string[]]$extra) {
    $stdout = Join-Path $temp ("runner-" + [guid]::NewGuid().ToString("N") + ".out")
    $stderr = Join-Path $temp ("runner-" + [guid]::NewGuid().ToString("N") + ".err")
    $process = Start-Process -FilePath $runner -ArgumentList $extra -Wait -PassThru `
        -RedirectStandardOutput $stdout -RedirectStandardError $stderr
    return [pscustomobject]@{
        ExitCode = $process.ExitCode
        Output = (Get-Content -LiteralPath $stdout -Raw -ErrorAction SilentlyContinue)
        Error = (Get-Content -LiteralPath $stderr -Raw -ErrorAction SilentlyContinue)
    }
}

function Expect-Exit([string]$name, [int]$expected, [string[]]$extra) {
    $result = Invoke-Runner $extra
    if ($result.ExitCode -ne $expected) {
        Write-Output ("TEST_FAIL name={0} expected={1} actual={2} output={3} error={4}" -f `
            $name, $expected, $result.ExitCode, $result.Output, $result.Error)
        $script:failures++
        return $null
    }
    Write-Output ("TEST_PASS name={0} exit={1}" -f $name, $result.ExitCode)
    return $result
}

$base = @("--profile", "fake", "--cpus", "1", "--memory-mib", "1024", "--runs", "1",
          "--executable", $fake, "--arguments")
$successResult = Expect-Exit "success" 0 ($base + @("success"))
if ($null -ne $successResult) {
    if ($successResult.Output -notmatch "PROFILE_SUMMARY profile=fake runs=1 failures=0") {
        Write-Output "TEST_FAIL name=success_summary output=$($successResult.Output)"
        $failures++
    }
    if ($successResult.Output -notmatch "affinity_coverage=before_resume") {
        Write-Output "TEST_FAIL name=success_affinity output=$($successResult.Output)"
        $failures++
    }
    if ($successResult.Output -notmatch "memory_limit_mib=1024") {
        Write-Output "TEST_FAIL name=success_memory output=$($successResult.Output)"
        $failures++
    }
}

foreach ($mode in @("exit7", "missing_ok", "missing_correctness", "short_results")) {
    Expect-Exit $mode 1 ($base + @($mode)) | Out-Null
}

$invalidCpu = @("--profile", "fake", "--cpus", "0", "--memory-mib", "1024", "--runs", "1",
                "--executable", $fake, "--arguments", "success")
Expect-Exit "invalid_cpu" 2 $invalidCpu | Out-Null
$invalidMemory = @("--profile", "fake", "--cpus", "1", "--memory-mib", "512", "--runs", "1",
                   "--executable", $fake, "--arguments", "success")
Expect-Exit "invalid_memory" 2 $invalidMemory | Out-Null
$invalidRuns = @("--profile", "fake", "--cpus", "1", "--memory-mib", "1024", "--runs", "0",
                 "--executable", $fake, "--arguments", "success")
Expect-Exit "invalid_runs" 2 $invalidRuns | Out-Null
$missingExe = @("--profile", "fake", "--cpus", "1", "--memory-mib", "1024", "--runs", "1",
                "--executable", (Join-Path $temp "does-not-exist.exe"), "--arguments", "success")
Expect-Exit "missing_executable" 1 $missingExe | Out-Null

if ($failures -ne 0) {
    Write-Output ("Q4_RUNNER_TESTS_FAILED failures={0}" -f $failures)
    exit 1
}
Write-Output "Q4_RUNNER_TESTS_OK cases=9"
exit 0
