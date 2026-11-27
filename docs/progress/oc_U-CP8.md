## NEXT DONE

## DONE
- Created tools/ctx/twins.py (CP8): find functions byte-identical after relocation masking (comp-hash)
- Fixes: PE section parsing (struct.unpack needs 20 bytes, not 16), iced-x86 API calls (properties not methods), case-sensitive constant names
- compute_comp_hash: FNV-1a 64-bit of first 64 bytes with relocations masked (call/jmp rel32, RIP-relative disp32, imm64)
- twins.py <rva>: lists exact twins (same comp-hash) and near-matches (1-3 differing bytes after masking) with diff bytes
- twins.py --all: writes docs/data/twins.tsv with group_id, rva columns (503 twin groups found)
- Uses rdis for function bounds (fn command) and iced-x86 for instruction decoding
- Optimized --all mode: fast hashing without per-function rdis subprocess calls (5.7s for 15209 functions)

## BLOCKING
- None