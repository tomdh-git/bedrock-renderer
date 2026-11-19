# Git clean filter: keeps only renderer-relevant sig categories
# Used by .gitattributes to filter Sigs.json on staging
[Console]::InputEncoding = [System.Text.Encoding]::UTF8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

$raw = [Console]::In.ReadToEnd()
if ([string]::IsNullOrWhiteSpace($raw)) {
    exit 0
}

try {
    $obj = $raw | ConvertFrom-Json
    if ($obj.mc) {
        $keep = @('client', 'common', 'deps')
        $filtered = [ordered]@{}
        foreach ($cat in $keep) {
            if ($obj.mc.PSObject.Properties[$cat]) {
                $filtered[$cat] = $obj.mc.$cat
            }
        }
        $obj.mc = $filtered
        $obj | ConvertTo-Json -Depth 20
        exit 0
    }
} catch {
    # If parsing fails, fall back to raw input
}

Write-Output $raw
