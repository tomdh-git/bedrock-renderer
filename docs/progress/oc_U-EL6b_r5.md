## NEXT
DONE

# U-EL6b: VV in/out resources per pass (builder 0x55f1450)

Goal: close checklist item L6b "in/out resources per pass" for VV passes declared inside builder 0x55f1450 (0x55f1450..0x563f594).

Prior attempts docs/progress/oc_U-EL6b_r1.md, oc_U-EL6b_r2.md, oc_U-EL6b_r3.md are NOT redone. They scanned all 50 pass-declaration call sites; decl fns 0x5698290 (15 sites), 0x5684660 ("Transparent"), 0x5667860 (4), 0x5693680 (7), 0x5694510 (2), 0x5695960 (1), 0x5696540 (1), 0x5697650 (1), 0x56CB540 (1), 0xBBBD7F0 (1); the 0x5689800 calls (18) are memmove loops, not pass declarations. This session re-verified verbatim instruction text at the main call site 0x55f1fca -> 0x5698290 and at decl fn 0x5698290 via rdis (every quoted line below matches the exe disassembly).

## Proven pass-descriptor field map (28 bytes, passed in r8 to the decl fns)

| offset | size | read/store address | verbatim `0xRVA instr` | meaning | tag |
|--------|------|--------------------|------------------------|---------|-----|
| +0x00 | 2B | [rbp+0x2C00] (site 0x55f1fca) | `0x55f1f68  mov [rbp+0x2C00],ax` | u16 count A; source u16 at config object +0x10 (`0x55f1f24 mov eax,[rcx+0x10]`) | [V] |
| +0x02 | 2B | [rbp+0x2C02] (site 0x55f1fca) | `0x55f1f76  mov [rbp+0x2C02],ax` | u16 count B; source u16 at config object +0x14 (`0x55f1f39 mov eax,[rcx+0x14]`) | [V] |
| +0x04 | 4B | [rbp+0x2C04] (site 0x55f1fca) | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | u32; source [rcx+0x18] then overwritten by site immediate; immediates 0x2D/0x1A/0x29 differ per site → per-pass index [I] | [V] store / [I] index |
| +0x08 | 8B | [rbp+0x2C08] (site 0x55f1fca) | `0x55f1f90  mov [rbp+0x2C08],rax` | u64 resource reference A; source [rbp+0x27A8] (`0x55f1f89 mov rax,[rbp+0x27A8]`); input vs output role not shown by any instruction | [V] store / [?] role |
| +0x10 | 8B | [rbp+0x2C10] (site 0x55f1fca) | `0x55f1f9e  mov [rbp+0x2C10],rax` | u64 resource reference B; source [rbp+0x27B0] (`0x55f1f97 mov rax,[rbp+0x27B0]`); input vs output role not shown by any instruction | [V] store / [?] role |
| +0x18 | 4B | [rbp+0x2C18] (site 0x55f1fca) | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | u32 flags; =0 at site 0x55f1fca; =3 via `0x55f1f57 mov dword ptr [rbp+0x27B8],3` at the two-descriptor site | [V] |
| desc +0x00..+0x0F | 16B | [rbx] (rbx = desc ptr at 0x5698290 entry) | `0x56982dc  movups xmm0,[rbx]` | all 16 descriptor bytes read at decl entry, copied opaquely | [V] |
| desc +0x0C..+0x1B | 16B | [rbx+0xC] | `0x56982df  movups xmm1,[rbx+0xC]` | remaining 16 descriptor bytes read, copied opaquely | [V] |

Other call sites use different stack bases ([rbp+0x1C40], [rbp+0x2440], ...) at the same offsets (inherited from r1/r3, not re-verified this session).

## Opaque full-copy in decl fn 0x5698290 (full disassembly verified this session)

- `0x56982d2  lea rax,[0xF25C820]` / `0x56982d9  mov [rdi],rax` — one fixed vtable stored at allocated+0x00.
- `0x56982dc  movups xmm0,[rbx]` / `0x56982df  movups xmm1,[rbx+0xC]` — all 28 descriptor bytes read.
- `0x56982e3  movups [rdi+8],xmm0` / `0x56982e7  movups [rdi+0x14],xmm1` — all 28 bytes written to allocated+0x08/+0x14; no field is split into input/output.
- `0x56982ef  mov rdx,[rsi+0x28]` / `0x56982f9  mov [rdx],rdi` / `0x56982fc  add qword ptr [rsi+0x28],8` — allocated ptr appended to the context+0x28 list.
- `0x569832f  mov rbx,[rsi+0x40]` / `0x569833d  mov [rbx],r8` / `0x5698340  mov [rbx+8],rdi` / `0x569834f  add qword ptr [rsi+0x40],0x50` — 0x50-stride entry added at context+0x40.
- Two-descriptor pattern at site 0x55f1fca/0x55f1fe7: `0x55f1fb9  lea r8,[rbp+0x2C00]` / `0x55f1fca  call 0x5698290`, then `0x55f1fd6  lea r8,[rbp+0x27A0]` / `0x55f1fe7  call 0x5698290`; the two descriptors share +0x00/+0x02/+0x08/+0x10 and differ only at +0x04/+0x18 (0x2D/0 and [rcx+0x18]/3).

No instruction or string in 0x55f1450 or its decl callees tags any descriptor field as input resource or output resource. Builder 0x55f1450 has no direct callers (xref/ripscan: entered indirectly), so no call-site context fixes field direction. Earlier static angles (binder-name search, full builder listing scan, 0x5684660 resource-binding helpers 0x5690960/0x5690E10/0x56912D0, consumer 0xc273420) all failed to separate input from output (see r2/r3).

## Pending evidence: live capture at the proven decl entry

Static analysis is exhausted for input/output direction (orchestrator hint 2026-11-22). The proven entry is decl fn 0x5698290: at entry r8 = 28-byte descriptor pointer. Capture request oc_u_el6b_desc (rva 0x5698290, size 0x100, max 6) is QUEUED with the orchestrator; docs/data/live/oc_u_el6b_desc.txt does not exist yet ("no result yet" from `python tools/livecap/request.py result oc_u_el6b_desc`). When it returns, the dumped desc bytes confirm field sizes/values at runtime and ret= names the caller chain; cite as [V live]. Until then, input/output direction cannot be established.

## CLOSES?

CLOSES? NO — single blocking fact: the input/output direction of the descriptor's u16 count fields (+0x00/+0x02) and u64 resource-reference fields (+0x08/+0x10) is not separated by any instruction or string in builder 0x55f1450 or its decl callees; all 28 bytes are copied opaquely by 0x5698290 (`0x56982dc  movups xmm0,[rbx]`, `0x56982df  movups xmm1,[rbx+0xC]`, `0x56982e3  movups [rdi+8],xmm0`, `0x56982e7  movups [rdi+0x14],xmm1`). The only evidence that can add direction is the pending live capture oc_u_el6b_desc at decl entry 0x5698290 (result not yet returned).

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_el6b_desc — decl entry 0x5698290, size 0x100, max 6, queued; awaiting docs/data/live/oc_u_el6b_desc.txt. No helper script written.
