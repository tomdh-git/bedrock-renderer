## NEXT
DONE

---
# UNIT U-EH2: H2 Occlusion — the real occlusion-query user

Pending part of the checklist line: "real occlusion-query user not found" (the other two parts — 0x660ecd0 = caps JSON dump, ChunkOccluder/SimpleOccluder = materials — are already proven in oc_U-H3c.md). Input data = docs/progress/oc_U-H2b.md (counter ctx+0x2035F0 = header+0x0 of a 0x20-byte {counter, base, next, end} queue header; only 3 direct [reg+0x2035F0] sites exist; siblings 0x2035D0/0x2035B0/0x203590/0x203570).

## Method
dispfun.py 0x14300 → functions touching Frame+0x14300: 0x5b0c1b0, 0x88b8600, 0xbc66de0, 0xbc779d0, 0xe7f5380, 0xe821120, 0xe85e5c0; each dumped with tools/sigs/dumplist.py (rdis fld rejects displacements >= 0x10000, so listings are used). Proof lines below verified verbatim with tools/sigs/verify_oc.py (19/19 match).

## Hits table (one row per distinct offset; all its sites listed)

| name | rva or offset | size | proof (`0xRVA  instr`) | tag |
|---|---|---|---|---|
| Frame.m_occlusion[256] base | Frame+0x14300 | 0x400 | `0xBC77C5A  lea rcx,[rdi+0x14300]`; `0xBC77C67  mov dl,0xFF`; `0xBC77C69  call 0xEBCE430` (memset(dst=Frame+0x14300, 0xFF, 0x400) in Frame ctor/reset 0xbc779d0); `0xBC683B9  add rdx,0x14300`; `0xBC683C0  add rcx,0x14300`; `0xBC683C7  mov r8d,0x400`; `0xBC683CD  call 0xEBCE390` (bulk 0x400-byte copy between the two Frame+0x14300 copies, fn 0xbc66de0) | [V] |
| Frame.m_occlusion[q] entry (per query) | Frame+0x14300+q*4 | 4 | writes: `0xE85F04D  mov [r15+rcx*4+0x14300],eax` (fn 0xe85e5c0; eax=[rbx+0x420] resolved query result, rcx = u16 query id at [r12+r14*8+0x182298], r15 = Frame [rbx+0xA8]); `0xE8607AD  mov [rdx+rcx*4+0x14300],eax` (fn 0xe85e5c0); `0xE86447D  mov [rdx+rcx*4+0x14300],eax` (fn 0xe85e5c0); reads: `0xE82270B  cmp dword ptr [r9+rdx*4+0x14300],0` (executor 0xe821120; r9 = Frame, rdx = draw.m_occlusionQuery at draw+0x7A), `0xE860B8D  cmp dword ptr [r14+rdi*4+0x14300],0` (fn 0xe85e5c0) | [V] |
| Occlusion-query counter | ctx+0x2035F0 | 8 | `0xE7F5452  lea rcx,[r12+0x2035F0]`; `0xE7F1619  lea rcx,[rsi+0x2035F0]` (both pass address to sub_e805480); `0xE7FCB30  mov eax,[r10+0x2035F0]` (overlay draw, prints " Occlusion queries: %3d "); `0xE80567E  mov qword ptr [rsi],0` (sub_e805480 zeroes queue-header+0x0 = the counter) | [?] |

Row meanings:
- Frame+0x14300 base: ctor memset 0xFF → an unread occlusion-query result is nonzero → visible by default [V: instruction]; per-frame 0x400-byte publish between two copies [V: instruction]. Meaning from instruction only (no string names this array).
- Frame+0x14300+q*4: D3D12 resolve fn 0xe85e5c0 stores each resolved query result into its slot; executor 0xe821120 and the resolve fn itself test `!=0` for draw visibility with the submitFlags sign-bit inversion [V: instructions]. This is the real occlusion-query user chain: results resolved → stored → consumed for occlusion culling.
- ctx+0x2035F0: overlay string " Occlusion queries: %3d " shows it is displayed as the occlusion-query count [V: string, cited in oc_U-H2b.md]; but no instruction in .text increments it — sub_e805480 (called only from sub_e7f5380/sub_e7f0f40) only zeroes it (0xe80567E). Incrementer: not found [?] — single blocking fact below.

CLOSES? YES — the pending item part "real occlusion-query user not found" is proven by [V] rows: D3D12 occlusion-query resolve fn 0xe85e5c0 writes per-query results into Frame.m_occlusion[q] at 0xe85f04d / 0xe8607ad / 0xe86447d, and the draw executor 0xe821120 consumes them at 0xe82270b (`cmp dword ptr [r9+rdx*4+0x14300],0`, skip invisible draws); the same fn re-tests at 0xe860b8d. Frame ctor 0xbc779d0 memset's m_occlusion to 0xFF at 0xbc77c5a-0xbc77c69 so unread queries default visible. The only gap outside the pending part: the ctx+0x2035F0 counter's incrementer is not found in static .text (only zero-resets at 0xe80567E and the overlay read at 0xe7fcb30) — tagged [?], does not change the user verdict.

## TOOL REQUESTS

None — used tools/sigs/dumplist.py and rdis.exe fld/dis variants only; no new helpers written.

