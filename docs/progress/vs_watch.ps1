# logs every Visual Studio launch (devenv / VSLauncher) with the full ancestry chain, plus any process whose command line opens a .cpp/.h/.sln via start/explorer/Invoke-Item
$log = "C:\Users\Atomi\Desktop\BlueySenseV2\docs\progress\vs_watch.log"
$seen = @{}
function Chain($procId) {
    $out = @()
    for ($i = 0; $i -lt 8 -and $procId; $i++) {
        $p = Get-CimInstance Win32_Process -Filter "ProcessId=$procId" -ErrorAction SilentlyContinue
        if (-not $p) { break }
        $cmd = if ($p.CommandLine) { $p.CommandLine.Substring(0, [Math]::Min(260, $p.CommandLine.Length)) } else { "" }
        $out += "    [$($p.ProcessId)] $($p.Name) :: $cmd"
        $procId = $p.ParentProcessId
    }
    $out -join "`n"
}
while ($true) {
    $procs = Get-CimInstance Win32_Process -ErrorAction SilentlyContinue | Where-Object { $_.Name -match '^(devenv|VSLauncher|VsDebugConsole)\.exe$' }
    foreach ($p in $procs) {
        if ($seen.ContainsKey($p.ProcessId)) { continue }
        $seen[$p.ProcessId] = 1
        Add-Content $log ("{0} NEW {1} pid {2}`n{3}`n" -f (Get-Date -Format "HH:mm:ss.fff"), $p.Name, $p.ProcessId, (Chain $p.ProcessId))
    }
    Start-Sleep -Milliseconds 200
}
