# Git smudge filter: restores full signatures from BlueySenseV2 if available,
# otherwise passes through the git-stored (renderer-only) signatures.
[Console]::InputEncoding = [System.Text.Encoding]::UTF8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

$blueySigs = "C:\Users\Atomi\Desktop\BlueySenseV2\docs\Sigs.json"
if (Test-Path $blueySigs) {
    [System.IO.File]::ReadAllText($blueySigs, [System.Text.Encoding]::UTF8)
} else {
    [Console]::In.ReadToEnd()
}
