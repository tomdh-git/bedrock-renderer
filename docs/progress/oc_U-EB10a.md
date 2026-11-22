## NEXT
DONE

UNIT U-EB10a — close checklist item B10a: "RTX GPU skinning (slot 63 = 0xe83f1d0, 0x107b) anchor — 6al, 6bc (P3) — RTX, low priority unless RTX hardware".
Output file: docs/progress/oc_U-EB10a.md only. Cited sections read in full: 6al (RTX renderer context overrides, vtable 0xF4EEE80 vs base 0xF4ED2D0) and 6bc (RTX-context DLSS/NGX surface; slot 63 single string) of docs/BGFX_MAP.md.

Method: disassembled sub_e83f1d0 end-to-end (0xe83f1d0..0xe84024b = size 0x107b), xref'd both strings (single xref each, both inside 0xe83f1d0), verified the vtable slot 63 entry (docs/progress/_vtable_rtx.txt) and the slot-63 dispatch inside submit (0xe82e230).

## Answer table

| name | rva / offset | size | proof `0xRVA  instr` | tag | meaning |
| RTX vtable slot 63 entry | 0xF4EEE80+0x1F8 -> 0xe83f1d0 | 0x107b | `0xe83f1d0  push rbp` | [V] | slot 63 of RTX RendererContextD3D12 vtable (base 0xF4ED2D0): entry = sub_e83f1d0, size 0x107b, first instr push rbp — vtable dump docs/progress/_vtable_rtx.txt + entry disassembly [V]; base keeps shared stub 0x768f0 here (6al), so slot 63 is RTX-only |
| GPU skinning vertex-format mismatch string | 0xf5602ad | 71 | `0xe83fafe  lea rdx,[0xF5602AD]` | [V] | "Type Mismatch in Vertex format used for GPU skinning Vertices of Actor" (70 chars + NUL); sole string xref in the function, loaded at 0xe83fafe and passed to `0xe83fb05  call 0xBC5F110` (error log) — actor vertex layout vs skinning compute layout mismatch (6bc) |
| RTX skinning enable byte | RTX ctx +0x3C5646C | 1 | `0xe83f206  cmp byte ptr [rcx+0x3C5646C],1` | [V] | gate byte; != 1 → early return 0xe8401b7 |
| Skinning record array bounds | RTX ctx +0x3C964B8 / +0x3C964C0 | 8 | `0xe83f216  mov rax,[rcx+0x3C964B8]`; `0xe83f21d  cmp rax,[rcx+0x3C964C0]` | [V] | begin/end of per-actor skinning record array, 0x30 stride; equal → nothing to skin |
| Per-handle allocation bitmap | RTX ctx +0xA258 | 8 | `0xe83f7e4  mov rdx,[r9+rax*8+0xA258]` | [V] | guarded-page bitmap; bt/bts test-and-set per handle at 0xe83f7f8-0xe83f84c |
| Per-handle state dword | RTX ctx +0xA45C | 4 | `0xe83f802  mov eax,[r9+r14*8+0xA45C]` + `cmp eax,8`; `0xe83f883  mov dword ptr [r9+r14*8+0xA45C],8` | [V] | state dword, 8 = allocated/in-use; read 0xe83f802/0xe83ff7a, stored 0xe83f883/0xe83fa53 |
| Vertex element format word | element +0x3C (element stride 0x54) | 2 | `0xe83faea  mov rax,[rbp+0x18]`; `0xe83faee  movzx eax,word ptr [rax+rbx+0x3C]`; `0xe83faf3  and eax,0x38`; `0xe83faf6  cmp ax,0x18` | [V] | element pointer then element format field of each 0x54-byte vertex element; bits 3-5 must equal 0x18 or mismatch error fires (0xe83fafc path) |
| Skinning buffer range-overrun string | 0xf7f9f9d | 94 | `0xe83fbb0  lea rdx,[0xF7F9F9D]` | [V] | "Our skinning vertex buffer is asking for a range that will extend past the end of the buffer." (93 chars + NUL), logged via `0xe83fbb7  call 0xBC5F110` |
| Per-record skinning stride | immediate 0x230 | - | `0xe83f2c7  imul rdi,rax,0x230` (sites also 0xe83f5da, 0xe83fe0a) | [V] | 0x230 immediate multiplier for per-record skinning buffer space; "per-record stride" reading is [I] |
| Slot-63 dispatch from submit | submit 0xe82e230 @ 0xe82eb09 | - | `0xe82eb09  mov rax,[rax+0x1F8]` | [V] | submit (this = RTX context, vtable 0xF4EEE80 [V live 6b]) loads vtable slot 63 (0x1F8 = 63*8), then `0xe82eb10  mov rcx,r12` / `0xe82eb13  call qword ptr [0xF99FFA0]` indirect-call thunk → sub_e83f1d0 |
| Undecoded record pointer | skinning record +0x20 | 8 | `0xe840080  lea r15,[0xF847A07]`; `0xe840090  mov [rsi+0x20],r15` | [?] | pointer stored into each processed record at +0x20; referent at 0xf847a07 not decoded (no string-by-address tool available) |

## Decoded behavior of sub_e83f1d0 (slot 63) [V by disassembly]

rcx = RTX context; gate byte [ctx+0x3C5646C] must be 1, else early return 0xe8401b7. Bounds [ctx+0x3C964B8]..[ctx+0x3C964C0] define the 0x30-stride skinning record array; equal → early return. For each record the function hashes the 0x54-byte vertex element's format word (+0x3C) through an FNV-1a-style bucket chain (basis 0xBF29CE484222325, prime 0x100000001B3, mix 0x8A97B0004E7FEAB, mask 7 at [rbp-8]); element format must satisfy `(word & 0x38) == 0x18`, otherwise `0xe83fafe  lea rdx,[0xF5602AD]` / `0xe83fb05  call 0xBC5F110` logs the mismatch error. Matching elements are written into a 0x230-byte-per-record skinning vertex buffer (memcpy 0x200 bytes via sub_eec6ec0) with range checks; overrun → `0xe83fbb0  lea rdx,[0xF7F9F9D]` / `0xe83fbb7  call 0xBC5F110`. Per-handle guarded tables updated: +0xA258 bitmap (bt/bts), +0xA45C state dword (=8), +0xA458 record ptr, +0x12458 handle list, +0xA250 count. Second pass (0xe840004) re-writes each record ([rsi+0x20] = ptr from 0xf847a07 [?], [rsi+0x28] = 0) and resets [ctx+0x3C964C0] = [ctx+0x3C964B8] at `0xe8400f3  mov [rcx+0x3C964C0],rax`. Allocator traffic via sub_eea6040 ([data_f99ffa0]) / sub_9bc830 / sub_e935700. This is the GPU skinning vertex-update ahead of BLAS skinning: PreBlasSkinDispatch is a separate pass body (0xbbe4399, not inside slot 63) and there is no BuildRaytracingAccelerationStructure call in sub_e83f1d0 [V per oc_U-B10c].

## CLOSES?
CLOSES?: YES — every part of B10a (slot 63 = 0xe83f1d0, size 0x107b; RTX GPU skinning anchor; 6al/6bc claims) is proven by [V] rows above: vtable slot entry [V], full function disassembly [V], both skinning strings [V] incl. the vertex-format mismatch check at element +0x3C, per-handle guarded-table state [V], and the slot-63 dispatch from submit [V]. Nothing in the item line remains pending. (The +0x20 record-pointer referent 0xf847a07 is deliberately [?] — outside the item line.)

## Verification
All quoted `0xRVA  instr` lines checked against `rdis` dis output. Run `python tools/sigs/verify_oc.py docs/progress/oc_U-EB10a.md` then `python tools/delegate.py check docs/progress/oc_U-EB10a.md`.

## TOOL REQUESTS
- `straddr <rva>`: print the NUL-terminated string at an rva — would have decoded the 0xe840080 target 0xf847a07 (stored at skinning-record +0x20) instead of leaving it [?].
