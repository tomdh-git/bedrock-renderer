## NEXT
DONE

# U-EL6b: VV in/out resources per pass (builder 0x55f1450)

Pending item from checklist L6b: "in/out resources per pass" for VV passes declared inside builder 0x55f1450 (size 0x4e144, 0x55f1450..0x563f594).

Prior attempts (not redone): docs/progress/oc_U-EL6b_r1.md and oc_U-EL6b_r2.md. r1 scanned all 50 pass-declaration call sites; decl fns 0x5698290 (15), 0x5684660 ("Transparent", 1), 0x5667860 (4), 0x5693680 (7), 0x5694510 (2), 0x5695960 (1), 0x5696540 (1), 0x5697650 (1), 0x56CB540 (1), 0xBBBD7F0 (1); the 0x5689800 calls (18) are memmove loops, not pass declarations. r2 fully disassembled 0x5698290 (200 instr): allocates 0x28 bytes, stores one fixed vtable (lea rax,[0xF25C820]), copies ALL 28 descriptor bytes with two movups, appends allocated ptr to context+0x28, adds a 0x50-stride entry at context+0x40. No field tagged input/output. CLOSES? NO both times (blocking fact: no input/output split).

Descriptor struct (28 bytes, passed in r8 to the decl fns) — layout PROVEN [V] from store/read instructions (one row per distinct offset, all sites listed):

| name | offset | size | verbatim `0xRVA  instr` proof | read/store address | meaning | tag |
|------|--------|------|-------------------------------|--------------------|---------|-----|
| desc +0x00 u16 | +0x00 | 2B | `0x55f1f68  mov [rbp+0x2C00],ax` | [rbp+0x2C00] (= ax, ax=[rbp+0x27A0]=[rcx+0x10] at site 0x55f1fca) | count field A; source u16 at config+0x10 (`0x55f1f24  mov eax,[rcx+0x10]`) | [V] |
| desc +0x02 u16 | +0x02 | 2B | `0x55f1f76  mov [rbp+0x2C02],ax` | [rbp+0x2C02] (= ax=[rbp+0x27A2]=[rcx+0x14]) | count field B; source u16 at config+0x14 (`0x55f1f39  mov eax,[rcx+0x14]`) | [V] |
| desc +0x04 u32 | +0x04 | 4B | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | [rbp+0x2C04] (= 0x2D=45, overwrites eax=[rcx+0x18] `0x55f1f4e`) | per-pass index [I from immediate]; values 0x2D/0x1A/0x29 at distinct sites | [V] store / [I] index |
| desc +0x08 u64 | +0x08 | 8B | `0x55f1f90  mov [rbp+0x2C08],rax` | [rbp+0x2C08] (= rax=[rbp+0x27A8], a resource reference) | resource reference A; direction (input vs output) NOT proven | [V] store / [?] role |
| desc +0x10 u64 | +0x10 | 8B | `0x55f1f9e  mov [rbp+0x2C10],rax` | [rbp+0x2C10] (= rax=[rbp+0x27B0], a resource reference) | resource reference B; direction (input vs output) NOT proven | [V] store / [?] role |
| desc +0x18 u32 | +0x18 | 4B | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | [rbp+0x2C18] (= 0 at site 0x55f1fca; =3 via `0x55f1f57  mov dword ptr [rbp+0x27B8],3` at site 0x55f1fca second desc) | flags; 0 vs 3 seen at the two-descriptor site | [V] |

Descriptor full-copy (decl fn 0x5698290, verified [V] by full 200-instr disassembly):
- `0x56982dc  movups xmm0,[rbx]` — reads all 16 descriptor bytes at +0x00..+0x0F (rbx=desc ptr) | desc +0x00..+0x0F | [V]
- `0x56982df  movups xmm1,[rbx+0xC]` — reads remaining 16 descriptor bytes at +0x0C..+0x1B | desc +0x0C..+0x1B | [V]
- `0x56982e3  movups [rdi+8],xmm0` — writes descriptor bytes to allocated struct +0x08..+0x17 | alloc +0x08 | [V]
- `0x56982e7  movups [rdi+0x14],xmm1` — writes descriptor bytes to allocated struct +0x14..+0x23 | alloc +0x14 | [V]
No instruction distinguishes any field as input or output resource — all 28 bytes copied opaquely [V].

Other descriptor stores seen at additional call sites (same offsets, different stack bases) [V]:
- `0x562e4c8  mov dword ptr [rbp+0x2C04],0x1A` (+0x04 = pass index 26, site 0x562e4e3)
- `0x560b6a3  mov dword ptr [rbp+0x2444],0x29` (+0x04 = pass index 41, site 0x560b6be)
- `0x560b68c  mov qword ptr [rbp+0x2454],1` (+0x10 u64 low part = 1, site 0x560b6be); `0x560bcdb  mov qword ptr [rbp+0x1EB4],1` (site 0x560bd0d); `0x560bcd2  mov word ptr [rbp+0x1EA8],0` (+0x08 u64 low part = 0); `0x562e4a2  mov word ptr [rbp+0x2C08],0` (+0x08 = 0, site 0x562e4e3); `0x562e491  mov dword ptr [rbp+0x2C0C],0`, `0x562e49b  mov byte ptr [rbp+0x2C10],0`, `0x562e4ab  mov rax,0x300000001`, `0x562e4b5  mov [rbp+0x2C14],rax` (site 0x562e4e3).

Two-descriptor declaration pattern [V] (site 0x55f1fca -> 0x5698290 then 0x55f1fe7 -> 0x5698290):
- `0x55f1fb9  lea r8,[rbp+0x2C00]` / `0x55f1fca  call 0x5698290` — desc1: +0x04=0x2D, +0x18=0 -> result [rbp+0x1C10]
- `0x55f1fd6  lea r8,[rbp+0x27A0]` / `0x55f1fe7  call 0x5698290` — desc2: +0x04=[rcx+0x18], +0x18=3 -> result [rbp+0x1CE8]
Same +0x00/+0x02/+0x08/+0x10 in both descriptors; they differ only at +0x04 and +0x18. Registration of the two pointers follows via 0xBB93890 / global [data_129C9628] (r2).

## NEW ANGLES TRIED (this retry) — all failed to separate input from output

1. **Binder name search (6aq vocabulary):** `xref.py str` for `BindFramebufferColor`, `BindFramebufferDepth`, `BindMaterialTexture`, `BindShaderBuffer`, `BindAccelerationStructure` — **no results**: plain binder names are not present as strings in .rdata, so binder RVAs/call sites cannot be located by name. [I from tool output]

2. **Full builder listing scan:** `docs/progress/pre/0x55f1450_full.lst` (1.8 MB, 58,550 lines, full 0x55f1450..0x563f594) contains **zero `rip`-relative `lea`** — no `.rdata` string loads anywhere in the builder. Binders (which take resource/name strings) are therefore not called with `.rdata` string arguments inside 0x55f1450. [V]

3. **Multi-arg decl fn 0x5684660 ("Transparent"):** fully disassembled (0x2000 bytes, 800+ instr shown). It iterates an array of 0x290-byte resource records (`0x56846a2  mov r14,[rdx+0x10]` base, `0x56846a6  mov rax,[rdx+0x18]` end, `0x56846fb ... add r14,0x290` stride) and dispatches to `0x5690960` / `0x5690E10` / `0x56912D0` by resource counter (`0x5684875  mov ecx,[rbp+0x964]`, `0x568487b  cmp ecx,1`, `0x568487e  je short 0x56848b7`, `0x5684880  test ecx,ecx`, `0x5684882  jne short 0x56848ea`). Those three helpers are **undecoded** — no preflight (`docs/progress/pre/`) and no dossier (`docs/functions/`) exists for 0x5690960 / 0x5690E10 / 0x56912D0 (nor for 0x568B0D0 called at the end of 0x5684660), so input vs output cannot be assigned from them. [V for structure; ? for helper semantics]

4. **Consumer side (0xc273420 frame-graph generate):** dossier `docs/functions/0xc273420.md` and preflight `docs/progress/pre/0xc273420.md` describe per-pass map/record construction via `sub_a4c70` (map insert) and 0x38-byte records, but the per-pass object fields read are `+0x228`/`+0x230` mode bytes — not the descriptor's input/output fields; no instruction there proves which descriptor u64 is input vs output. [V structure; ? role]

5. **livemem:** r2 already read global [data_129C9628] = encoded non-canonical qword `0x8BEB3C381FB2F1FE` (not walkable); live values cannot establish field direction. No further livemem calls (12-call cap, last-resort only). [V live]

## Interpretation

Proven [V]: descriptor layout {u16 +0x00, u16 +0x02, u32 +0x04, u64 +0x08, u64 +0x10, u32 +0x18} = 28 bytes with every store/read instruction; pass-index immediates 0x2D (site 0x55f1fa5), 0x1A (site 0x562e4c8), 0x29 (site 0x560b6a3); u16 counts sourced from config object +0x10/+0x14; u64 resource references at +0x08/+0x10; flags u32 at +0x18 (0 vs 3 at the two-descriptor site); opaque full-copy by 0x5698290 (two movups).

**Not provable [?]:** which of the two u16 count fields (+0x00/+0x02) is input-count vs output-count, and which of the two u64 resource references (+0x08/+0x10) is the input resource vs the output resource. No instruction, string, or binder call site in 0x55f1450 or its callees tags any descriptor field as input or output.

## CLOSES?

CLOSES? NO — single blocking fact: the input/output resource direction of the 28-byte pass descriptor fields (u16 counts +0x00/+0x02; u64 resource references +0x08/+0x10) cannot be determined from static analysis. The declaration functions copy all 28 bytes opaquely (0x5698290 `0x56982dc  movups xmm0,[rbx]`, `0x56982df  movups xmm1,[rbx+0xC]`, `0x56982e3  movups [rdi+8],xmm0`, `0x56982e7  movups [rdi+0x14],xmm1`), no instruction or string in 0x55f1450 or its callees separates input from output resources, the six-binder vocabulary from 6aq (`BindMaterialTexture`/`BindFramebufferDepth`/`BindFramebufferColor`/`BindShaderBuffer`/`BindAccelerationStructure`) has no locatable call site in the builder (no `.rdata` string references in the full 1.8 MB listing; plain names absent from .rdata), and the resource-binding helpers dispatched by 0x5684660 (0x5690960 / 0x5690E10 / 0x56912D0 by resource index at `0x568487b  cmp ecx,1` / `0x5684880  test ecx,ecx`) are undecoded (no preflight or dossier). Resolving this would require decoding one of those helpers or the binder call sites, or live data of the declared pass objects — none available within this unit.

## TOOL REQUESTS

None — no helper script written; the binder-name search and full-listing scan were done with existing tools (xref.py str, the precomputed 0x55f1450_full.lst). A general "find mangled template function by substring" helper (beyond plain .rdata strings) would have helped locate the 6aq binders.
