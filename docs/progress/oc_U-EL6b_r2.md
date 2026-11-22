## NEXT
DONE

# U-EL6b: VV in/out resources per pass (builder 0x55f1450)

Pending item from checklist L6b: "in/out resources per pass" for VV passes declared inside builder 0x55f1450 (size 0x4e144, 0x55f1450..0x563f594).

Prior attempt: docs/progress/oc_U-EL6b_r1.md (not redone). It scanned all 50 pass-declaration call sites; decl functions 0x5698290 (15 sites), 0x5684660 ("Transparent"), 0x5667860 (4), 0x5693680 (7), 0x5694510 (2), 0x5695960 (1), 0x5696540 (1), 0x5697650 (1), 0x56CB540 (1), 0xBBBD7F0 (1). Descriptor = 28-byte struct copied opaquely; CLOSES? NO (blocking fact: no input/output split).

## TRIED — new angles (this retry)

- xref.py callers 0x55f1450: no callers (preflight: 0 xrefs in). ripscan 0x55f1450: no references. Builder is entered indirectly, so no call-site context fixes field direction. [I from tool output]
- Full disassembly of callee 0x5698290 (200 instr via rdis; supersedes r1's 80-instr partial view): it allocates 0x28 bytes (`0x56982bb  mov edx,0x28`), stores one fixed vtable for every pass (`0x56982d2  lea rax,[0xF25C820]` / `0x56982d9  mov [rdi],rax`), then copies ALL 28 descriptor bytes with two movups (`0x56982dc  movups xmm0,[rbx]`, `0x56982df  movups xmm1,[rbx+0xC]`) into `allocated+0x08`/`allocated+0x14`, appends the allocated ptr to the context list at context+0x28 (`0x56982ef  mov rdx,[rsi+0x28]` / `0x56982f9  mov [rdx],rdi` / `0x56982fc  add qword ptr [rsi+0x28],8`), and adds a 0x50-stride entry at context+0x40 (`0x569832f  mov rbx,[rsi+0x40]` / `0x569833d  mov [rbx],r8` / `0x5698340  mov [rbx+8],rdi` / `0x569834f  add qword ptr [rsi+0x40],0x50`). No field is tagged input or output. [V]
- 0xBB93890 (registrar; 2 xrefs in, both inside the builder at 0x55f2082 and 0x56330bc): builds two pass structs per site via 0x5698290, stores the two pointers at desc+0x00 and desc+0x08 (`0xBB9395f  mov [rsi],rax` / `0xBB93962  mov [rsi+8],rbx`), and links them into the structure at global [data_129C9628]. No field semantics. [V]
- 0x567A7B0: copies vtable plus one qword from the allocated struct into a 0x30-byte secondary struct. Generic. [V]
- descscan2: not applicable (visitor-case tool; this is not a visitor function).
- livemem: game running (pid 18956, base 0x7ff699000000). One read: base+0x129C9628 (global [data_129C9628]) = qword 0x8BEB3C381FB2F1FE, non-canonical/encoded — cannot be walked as an object. [V live] `python tools/sigs/livemem.py read @0x129C9628 8`. Direction is not readable from live values anyway. No further livemem calls.

## RESULTS — pass descriptor struct (28 bytes, passed in r8 to 0x5698290)

| offset | size | site | instr | meaning |
|--------|------|------|-------|---------|
| +0x00 | 2B | 0x55f1f68 ([rbp+0x2C00]=ax=[rcx+0x10]); 0x55ff23b/0x55ff292 ([rbp+0x1C40]=[rbp+0x2784]); 0x55ff2c5 r8=[rbp+0x1EF4] | `0x55f1f68  mov [rbp+0x2C00],ax` | - |
| +0x02 | 2B | 0x55f1f76 ([rbp+0x2C02]=ax=[rcx+0x14]); 0x55ff249/0x55ff299 ([rbp+0x1C42]=[rbp+0x2786]) | `0x55f1f76  mov [rbp+0x2C02],ax` | - |
| +0x04 | 4B | 0x55f1f83 ([rbp+0x2C04]=eax=[rcx+0x18], overwritten); 0x55f1fa5 (=0x2D); 0x55ff278 ([rbp+0x1EF8]=0x1A); 0x55ff2a0 ([rbp+0x1C44]=0x2D) | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | - |
| +0x08 | 8B | 0x55f1f90 ([rbp+0x2C08]=rax=[rbp+0x27A8]); 0x55ff263 ([rbp+0x1C48]=[rbp+0x1EFC] word); 0x55ff271 ([rbp+0x1C4A]=[rbp+0x1EFE] word) | `0x55f1f90  mov [rbp+0x2C08],rax` | - |
| +0x10 | 8B | 0x55f1f9e ([rbp+0x2C10]=rax=[rbp+0x27B0]); 0x55ff28b ([rbp+0x1C50]=[rbp+0x1F04]) | `0x55f1f9e  mov [rbp+0x2C10],rax` | - |
| +0x18 | 4B | 0x55f1faf (=0); 0x55ff2aa ([rbp+0x1C58]=0) | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | - |
| desc +0x00..+0x0F | 16B | 0x56982dc (callee entry, rbx=desc ptr) | `0x56982dc  movups xmm0,[rbx]` | all 16 descriptor bytes read, copied opaquely [V] |
| desc +0x0C..+0x1B | 16B | 0x56982df | `0x56982df  movups xmm1,[rbx+0xC]` | remaining descriptor bytes read, copied opaquely [V] |
| alloc +0x08..+0x17 | 16B | 0x56982e3 | `0x56982e3  movups [rdi+8],xmm0` | descriptor bytes written to allocated struct [V] |
| alloc +0x14..+0x23 | 16B | 0x56982e7 | `0x56982e7  movups [rdi+0x14],xmm1` | descriptor bytes written to allocated struct [V] |

## Interpretation

Struct: {u16 +0x00, u16 +0x02, u32 +0x04, u64 +0x08, u64 +0x10, u32 +0x18} = 28 bytes [V]. The +0x04 u32 holds different values at different sites (0x1A = 26 at site 0x55ff2c5; 0x2D = 45 at sites 0x55f1fca/0x55ff2f8/0x55ff31d) — consistent with a per-pass index [I from immediate values, not proven]. +0x00/+0x02 are u16 counts sourced from a pass-config object ([rcx+0x10]/[rcx+0x14] at site 0x55f1fca; [rbp+0x2784]/[rbp+0x2786] at 0x55ff2c5) [I]. +0x08/+0x10 are u64 resource pointers [V as qword stores, role not proven]. Every byte of the struct is copied by movups with no distinction between fields (full 0x5698290 disassembled above), and no instruction or string in 0x55f1450 or its callees labels which u16 is input-count vs output-count or which u64 is the input array vs the output array.

## CLOSES?

CLOSES? NO — blocking fact: the two u16 count fields (+0x00, +0x02) and the two u64 resource-pointer fields (+0x08, +0x10) of the 28-byte pass descriptor are copied opaquely by 0x5698290 (`0x56982dc  movups xmm0,[rbx]`, `0x56982df  movups xmm1,[rbx+0xC]`, `0x56982e3  movups [rdi+8],xmm0`, `0x56982e7  movups [rdi+0x14],xmm1` — all 28 bytes, no field tagged), and no instruction or string in 0x55f1450 or its callees separates input from output resources; 0x55f1450 is entered indirectly (no direct callers per xref/ripscan) so no call-site context fixes the direction; the one reachable live global [data_129C9628] reads back as an encoded non-canonical qword (0x8BEB3C381FB2F1FE at base+0x129C9628, `python tools/sigs/livemem.py read @0x129C9628 8`) and cannot be walked. Proven [V] instead: descriptor layout, pass-index values 0x1A/26 and 0x2D/45 at distinct sites, and the double 0x5698290 allocation + linkage into the [0x129C9628] structure. To close: resolve input/output direction at the consumer of the declared pass list (builder entered indirectly — not statically reachable) or via a live capture of the declared-pass objects with a decode of the encoded global pointer.

## TOOL REQUESTS

None
