## NEXT
DONE

# U-EL6b: VV in/out resources per pass (builder 0x55f1450)

Goal: close checklist item L6b "in/out resources per pass" for VV passes declared inside builder 0x55f1450 (0x55f1450..0x563f594).

Prior attempts docs/progress/oc_U-EL6b_r1.md .. r5.md are NOT redone. They scanned all 50 pass-declaration call sites; decl fns 0x5698290 (15 sites), 0x5684660 ("Transparent"), 0x5667860 (4), 0x5693680 (7), 0x5694510 (2), 0x5695960 (1), 0x5696540 (1), 0x5697650 (1), 0x56CB540 (1), 0xBBBD7F0 (1); the 0x5689800 calls (18) are memmove loops, not pass declarations. All sessions end CLOSES? NO with the same blocking fact: no instruction or string in builder 0x55f1450 or its decl callees separates input from output resources — every decl fn copies all 28 descriptor bytes opaquely.

## NEW THIS SESSION: live capture at the proven decl entry

Per the 2026-11-22 orchestrator hint, static analysis is exhausted and the live-capture tool was used. Target oc_u_el6b_desc at decl fn 0x5698290 entry (r8 = 28-byte descriptor pointer), size 0x100, max 6 — already queued in earlier sessions. Result: `docs/data/live/oc_u_el6b_desc.txt` exists (capture DONE, t=120) but `oc_u_el6b_desc hits=0 samples=0` per `docs/data/live/_status.txt`; the file contains only header lines, no `REG=value hit=N ret=0xRVA <bytes>` data lines. The breakpoint at decl entry 0x5698290 was never hit during the capture window, so no descriptor bytes were dumped and no caller chain (ret=) was named. The live capture added nothing to input/output direction [V live: file present, 0 samples].

## Proven descriptor struct (28 bytes, passed in r8 to the decl fns) — layout [V], all sites listed

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|--------------------|------------------------|---------|-----|
| +0x00 | 2B | [rbp+0x2C00] (site 0x55f1fca) | `0x55f1f68  mov [rbp+0x2C00],ax` | - | [V] store; u16 field, source u16 at config+0x10 (`0x55f1f24 mov eax,[rcx+0x10]`); input-count vs output-count not shown: [?] |
| +0x02 | 2B | [rbp+0x2C02] (site 0x55f1fca) | `0x55f1f76  mov [rbp+0x2C02],ax` | - | [V] store; u16 field, source u16 at config+0x14 (`0x55f1f39 mov eax,[rcx+0x14]`); input-count vs output-count not shown: [?] |
| +0x04 | 4B | [rbp+0x2C04] (site 0x55f1fca) | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | - | [V] store; u32 field, source [rcx+0x18] then overwritten by site immediate; immediates 0x2D/0x1A/0x29 differ per site → per-pass index [I]: [?] |
| +0x08 | 8B | [rbp+0x2C08] (site 0x55f1fca) | `0x55f1f90  mov [rbp+0x2C08],rax` | - | [V] store; u64 qword field, source [rbp+0x27A8] (`0x55f1f89 mov rax,[rbp+0x27A8]`); input resource vs output resource not shown: [?] |
| +0x10 | 8B | [rbp+0x2C10] (site 0x55f1fca) | `0x55f1f9e  mov [rbp+0x2C10],rax` | - | [V] store; u64 qword field, source [rbp+0x27B0] (`0x55f1f97 mov rax,[rbp+0x27B0]`); input resource vs output resource not shown: [?] |
| +0x18 | 4B | [rbp+0x2C18] (site 0x55f1fca) | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | - | [V] store; u32 flags field; =0 at site 0x55f1fca, =3 via `0x55f1f57 mov dword ptr [rbp+0x27B8],3` at two-descriptor site; bit meanings not shown: [?] |
| desc +0x00..+0x0F | 16B | [rbx] (rbx = desc ptr at 0x5698290 entry) | `0x56982dc  movups xmm0,[rbx]` | all 16 descriptor bytes read at decl entry, copied opaquely | [V] |
| desc +0x0C..+0x1B | 16B | [rbx+0xC] | `0x56982df  movups xmm1,[rbx+0xC]` | remaining 16 descriptor bytes read at decl entry, copied opaquely | [V] |
| alloc +0x08..+0x17 | 16B | [rdi+8] (rdi = allocated 0x28-byte struct) | `0x56982e3  movups [rdi+8],xmm0` | descriptor bytes written to allocated struct | [V] |
| alloc +0x14..+0x23 | 16B | [rdi+0x14] | `0x56982e7  movups [rdi+0x14],xmm1` | descriptor bytes written to allocated struct | [V] |

Other call sites use different stack bases ([rbp+0x1C40], [rbp+0x2440], ...) at the same offsets (inherited from r1/r3, not re-verified this session). Struct: {u16 +0x00, u16 +0x02, u32 +0x04, u64 +0x08, u64 +0x10, u32 +0x18} = 28 bytes [V].

## Decl fn 0x5698290 — opaque full copy, PROVEN [V]

Re-verified this session (rdis 0x56982c0..0x5698356):
- `0x56982d2  lea rax,[0xF25C820]` / `0x56982d9  mov [rdi],rax` — one fixed vtable (data global data_f25c820) stored at allocated+0x00; identical for every pass, so vtable slots cannot distinguish per-field input/output direction.
- `0x56982dc  movups xmm0,[rbx]` / `0x56982df  movups xmm1,[rbx+0xC]` — all 28 descriptor bytes read at decl entry (rbx=r8=desc ptr).
- `0x56982e3  movups [rdi+8],xmm0` / `0x56982e7  movups [rdi+0x14],xmm1` — all 28 bytes written to allocated+0x08/+0x14; no field is split into input/output.
- `0x56982ef  mov rdx,[rsi+0x28]` / `0x56982f9  mov [rdx],rdi` / `0x56982fc  add qword ptr [rsi+0x28],8` — allocated ptr appended to context+0x28 list.
- `0x569832f  mov rbx,[rsi+0x40]` / `0x569833d  mov [rbx],r8` / `0x5698340  mov [rbx+8],rdi` / `0x569834f  add qword ptr [rsi+0x40],0x50` — 0x50-stride entry added at context+0x40.
- Virtual call sequence `0x569831a  mov rax,[rcx]` / `0x569831d  mov rax,[rax]` reads the vtable first slot but then calls via global [data_f99ffa0] (sub_eea6040) — generic registration, no field direction.

Two-descriptor declaration pattern [V] (site 0x55f1fca -> 0x5698290 then 0x55f1fe7 -> 0x5698290): desc1 +0x04=0x2D, +0x18=0 -> result [rbp+0x1C10]; desc2 +0x04=[rcx+0x18], +0x18=3 -> result [rbp+0x1CE8]; both share +0x00/+0x02/+0x08/+0x10 and differ only at +0x04/+0x18. Flags 0 vs 3 at +0x18 is not assigned an input/output meaning by any instruction.

## Blocking fact

No instruction or string in 0x55f1450 or its decl callees tags any descriptor field as input resource or output resource. All 28 bytes are copied opaquely by 0x5698290 (two movups). Builder 0x55f1450 has no direct callers (xref/ripscan: entered indirectly), so no call-site context fixes field direction. Earlier static angles (binder-name search, full builder listing scan, 0x5684660 resource-binding helpers 0x5690960/0x5690E10/0x56912D0, consumer 0xc273420, vtable data_f25c820) all failed to separate input from output (see r1-r4). The live capture oc_u_el6b_desc at decl entry 0x5698290 returned hits=0 samples=0 (no descriptor bytes dumped, no ret= caller chain), so it added no direction evidence.

## CLOSES?

CLOSES? NO — single blocking fact: the input/output resource direction of the descriptor's u16 count fields (+0x00/+0x02) and u64 resource-reference fields (+0x08/+0x10) is not separated by any instruction or string in builder 0x55f1450 or its decl callees; all 28 bytes are copied opaquely by 0x5698290 (`0x56982dc  movups xmm0,[rbx]`, `0x56982df  movups xmm1,[rbx+0xC]`, `0x56982e3  movups [rdi+8],xmm0`, `0x56982e7  movups [rdi+0x14],xmm1`), and the live capture oc_u_el6b_desc at decl entry 0x5698290 returned hits=0 samples=0 so no runtime descriptor bytes or caller chain were obtained. Per-pass in/out is covered by oc_U-EM1e.md (M1e) and parked in MIRROR_SKIP; ticking this item requires M1e or live data of the declared-pass objects, neither available within this unit.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_el6b_desc — already queued and run; docs/data/live/oc_u_el6b_desc.txt exists with hits=0 samples=0 (no descriptor bytes dumped). No new capture requested (same entry would re-hit the same no-sample result). No helper script written.
