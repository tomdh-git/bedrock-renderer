# mirror_sync.ps1 - keeps the professional repo (tomdh-git/bedrock-renderer) showing the same render docs and client renderer source as BlueySenseV2.
#
#   powershell -File tools\mirror_sync.ps1            create what is missing (hardlinks for files, junctions for directories), report what has diverged
#   powershell -File tools\mirror_sync.ps1 -Fix       also re-link a diverged file (an editor that saves by replacing the file breaks a hardlink): BlueySenseV2 is the truth
#
# Hardlinks: docs\*.md render docs, the two native tools. Junctions: docs\data, docs\functions, docs\progress (already there) and src\client\features\render\native (the native renderer source).
# BlueySenseV2 stays the place where work happens; commit and push from the mirror repo.
param([switch]$Fix)
$bs = "C:\Users\Atomi\Desktop\BlueySenseV2"
$br = "C:\Users\Atomi\Desktop\tomdh-git\bedrock-renderer"
if (-not (Test-Path $br)) { throw "mirror repo not found: $br" }

function Link-File($rel) {
    $src = Join-Path $bs $rel; $dst = Join-Path $br $rel
    if (-not (Test-Path $src)) { return }
    New-Item -ItemType Directory -Force (Split-Path $dst) | Out-Null
    if (-not (Test-Path $dst)) { New-Item -ItemType HardLink -Path $dst -Target $src | Out-Null; Write-Host "linked   $rel"; return }
    if ((Get-FileHash $src).Hash -ne (Get-FileHash $dst).Hash) {
        if ($Fix) { Remove-Item $dst -Force; New-Item -ItemType HardLink -Path $dst -Target $src | Out-Null; Write-Host "relinked $rel" }
        else { Write-Host "DIVERGED $rel (run with -Fix to relink from BlueySenseV2)" }
    }
}
function Link-Dir($rel) {
    $src = Join-Path $bs $rel; $dst = Join-Path $br $rel
    New-Item -ItemType Directory -Force $src | Out-Null
    if (Test-Path $dst) { return }
    New-Item -ItemType Directory -Force (Split-Path $dst) | Out-Null
    New-Item -ItemType Junction -Path $dst -Target $src | Out-Null
    Write-Host "junction $rel"
}

$docs = @("BGFX_MAP.md","FRAME_CALLGRAPH.md","BEHAVIOR_NOTES.md","BIGBANG_TESTS.md","OPENCODE_BRIEF.md","OPENCODE_PLAN.md","README.md") + (Get-ChildItem (Join-Path $bs "docs") -Filter "RENDER_*.md" | ForEach-Object Name) + (Get-ChildItem (Join-Path $bs "docs") -Filter "NATIVE_*.md" | ForEach-Object Name)
$docs | Sort-Object -Unique | ForEach-Object { Link-File "docs\$_" }
Link-File "tools\native_checklist_gen.py"
Link-File "tools\sigs\liftcheck.py"
Link-File "tools\mirror_sync.ps1"
foreach ($d in @("docs\data","docs\functions","docs\progress","src\client\features\render\native")) { Link-Dir $d }
Write-Host "mirror in sync; commit and push from $br"
