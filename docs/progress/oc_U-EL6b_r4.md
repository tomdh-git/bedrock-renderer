## NEXT
DONE

# U-EL6b: VV in/out resources per pass (builder 0x55f1450)

Pending item from checklist L6b: "in/out resources per pass" for VV passes declared inside builder 0x55f1450 (size 0x4e144, 0x55f1450..0x563f594). Builder entered indirectly: 0 xrefs in (preflight docs/progress/pre/0x55f1450.md).

Prior attempts NOT redone: docs/progress/oc_U-EL6b_r1.md, oc_U-EL6b_r2.md, oc_U-EL6b_r3.md. All three end CLOSES? NO with the same blocking fact: declaration functions copy all 28 descriptor bytes opaquely and nothing separates input from output resources. Static angles already exhausted there (binder-name search, full 1.8 MB builder listing scan, consumer side 0xc273420, livemem of global [data_129C9628] = encoded non-canonical qword) — this retry adds ONLY the live capture below (per 2026-11-22 orchestrator hint).

Live capture requested (not yet run): `python tools/livecap/request.py add oc_u_el6b_desc 0x5698290 --size 0x100 --max 6 --why "L6b: decl fn 0x5698290 entry; r8 = 28-byte pass descriptor ptr. Dump desc bytes at entry to confirm field sizes/values at runtime (u16 counts +0x00/+0x02, u32 index +0x04, u64 resource refs +0x08/+0x10, u32 flags +0x18) and name caller chain via ret= (builder call sites e.g. 0x55f1fca/0x55f1fe7). Can the live bytes show which field is the input vs the output resource?"` — result pending in docs/data/live/oc_u_el6b_desc.txt (`python tools/livecap/request.py result oc_u_el6b_desc` -> "no result yet (orchestrator has not run it)"). docs/data/live/_status.txt has only one finished capture (dragon_texture_caller_bc41420); nothing for this item.

## DESCRIPTOR STRUCT (28 bytes, passed in R8 to the decl fns) — layout PROVEN [V]

One row per distinct offset, all store/read sites listed. Meaning column: '-' unless an instruction or string shows it. Role (input vs output resource) is NOT shown by any instruction — tagged [?].

| offset | size | site | instr | meaning | tag |
|--------|------|------|-------|---------|-----|
| +0x00 | 2B | 0x55f1f68 ([rbp+0x2C00]=ax; ax=movzx from [rbp+0x27A0]=[rcx+0x10] at 0x55f1f61/0x55f1f24); same offset at 0x55ff249/0x55ff299 ([rbp+0x1C42]); same offsets recur at further sites per r2 (e.g. [rbp+0x2440] base at 0x562cc0a/0x562e4e3/0x562e661/0x563281e/0x5632b0e/0x5633359) | `0x55f1f68  mov [rbp+0x2C00],ax` | - | [V] store; u16 field (input-count vs output-count not shown by any instr): [?] |
| +0x02 | 2B | 0x55f1f76 ([rbp+0x2C02]=ax=[rbp+0x27A2]=[rcx+0x14] at 0x55f1f6f/0x55f1f39); same offset at 0x55ff249/0x55ff299 | `0x55f1f76  mov [rbp+0x2C02],ax` | - | [V] store; u16 field (input-count vs output-count not shown): [?] |
| +0x04 | 4B | 0x55f1f83 (eax=[rcx+0x18] at 0x55f1f4e, then overwritten); 0x55f1fa5 (=0x2D=45); other sites 0x562e4c8 (=0x1A=26), 0x560b6a3 ([rbp+0x2444]=0x29=41) | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | - | [V] store; per-pass index [I from immediate 0x2D/0x1A/0x29 at distinct sites — not an instruction label]: [?] |
| +0x08 | 8B | 0x55f1f90 ([rbp+0x2C08]=rax=[rbp+0x27A8], a resource reference); word-size stores of this field at 0x55ff263/0x55ff271 and 0x562e4a2 (=0) at other sites | `0x55f1f90  mov [rbp+0x2C08],rax` | - | [V] store; u64 resource reference A (input vs output resource not shown): [?] |
| +0x10 | 8B | 0x55f1f9e ([rbp+0x2C10]=rax=[rbp+0x27B0], a resource reference); 0x55ff28b ([rbp+0x1C50]=[rbp+0x1F04]); byte store =0 at 0x562e49b | `0x55f1f9e  mov [rbp+0x2C10],rax` | - | [V] store; u64 resource reference B (input vs output resource not shown): [?] |
| +0x18 | 4B | 0x55f1faf (=0); 0x55ff2aa ([rbp+0x1C58]=0); flags 0 vs 3 at the two-descriptor site (0x55f1f57 sets [rbp+0x27B8]=3 for desc2) | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | - | [V] store; flags u32 (0 vs 3 seen at two-descriptor site; bit meanings not shown): [?] |

Struct: {u16 +0x00, u16 +0x02, u32 +0x04, u64 +0x08, u64 +0x10, u32 +0x18} = 28 bytes [V]. Two-descriptor declaration pattern [V] (site 0x55f1fca -> 0x5698290 then 0x55f1fe7 -> 0x5698290): desc1 +0x04=0x2D, +0x18=0 -> result [rbp+0x1C10]; desc2 +0x04=[rcx+0x18], +0x18=3 -> result [rbp+0x1CE8]; same +0x00/+0x02/+0x08/+0x10 in both, differ only at +0x04/+0x18. Registration via 0xBB93890 into global [data_129C9628] (r2, [V]).

## DECL FN 0x5698290 (15 xrefs in per preflight) — opaque full copy, PROVEN [V]

Full 200-instr disassembly re-verified just now (rdis 0x5698290): allocates 0x28 bytes (`0x56982bb  mov edx,0x28`), stores one fixed vtable for every pass (`0x56982d2  lea rax,[0xF25C820]` / `0x56982d9  mov [rdi],rax`), rbx=r8=desc ptr (`0x56982a7  mov rbx,r8`), then copies ALL 28 descriptor bytes with two movups and writes them to allocated+0x08/allocated+0x14:

| offset | size | site | instr | meaning | tag |
|--------|------|------|-------|---------|-----|
| desc +0x00..+0x0F | 16B | 0x56982dc (decl fn 0x5698290 entry; rbx=r8=desc ptr) | `0x56982dc  movups xmm0,[rbx]` | all 16 descriptor bytes read, copied opaquely, no field distinguished | [V] |
| desc +0x0C..+0x1B | 16B | 0x56982df | `0x56982df  movups xmm1,[rbx+0xC]` | remaining 16 descriptor bytes read, copied opaquely | [V] |
| alloc +0x08..+0x17 | 16B | 0x56982e3 (rdi=allocated 0x28-byte struct) | `0x56982e3  movups [rdi+8],xmm0` | descriptor bytes written to allocated struct | [V] |
| alloc +0x14..+0x23 | 16B | 0x56982e7 | `0x56982e7  movups [rdi+0x14],xmm1` | descriptor bytes written to allocated struct | [V] |

No instruction in 0x5698290 or any other callee of 0x55f1450 tags any descriptor field as input or output resource — all 28 bytes copied opaquely [V].

## WHAT THE LIVE CAPTURE CAN / CANNOT ADD [V live when it runs]

At entry of 0x5698290 the capture logs REG=R8 (the pass-descriptor pointer), dumps 0x100 bytes at [R8] (the actual 28-byte descriptor values at runtime across hits: counts, index 0x2D/0x1A/0x29, resource refs, flags 0/3), and ret= names the caller chain (builder call sites, e.g. 0x55f1fca desc1 +0x04=0x2D/+0x18=0; 0x55f1fe7 desc2 +0x18=3). That confirms field sizes and real field values [V live] and names caller/callee chain [V live]. It CANNOT establish input vs output direction: descriptor bytes carry no direction tag, and direction is decided by the consumer (which declared pass is bound as input vs output resource) — outside this unit's static scope; per-pass in/out is covered by oc_U-EM1e.md (M1e), to be ticked together with M1e.

## CLOSES?

CLOSES? NO — single blocking fact: which of +0x00/+0x02 is input-count vs output-count and which of +0x08/+0x10 is the input resource vs the output resource cannot be determined: all 28 bytes are copied opaquely by 0x5698290 (`0x56982dc  movups xmm0,[rbx]`, `0x56982df  movups xmm1,[rbx+0xC]`, `0x56982e3  movups [rdi+8],xmm0`, `0x56982e7  movups [rdi+0x14],xmm1`), no instruction/string in 0x55f1450 or its callees separates input from output resources, and even live descriptor bytes at 0x5698290 entry (capture oc_u_el6b_desc requested, pending) carry no direction tag — consumer/binding-side semantics needed, covered by M1e (oc_U-EM1e.md).

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_el6b_desc — live capture at decl fn 0x5698290 entry (r8 = 28-byte pass descriptor ptr), size 0x100, max 6, queued via `python tools/livecap/request.py add oc_u_el6b_desc 0x5698290 --size 0x100 --max 6 --why "L6b: ..."`; result pending in docs/data/live/oc_u_el6b_desc.txt. Expected to add [V live]: real desc field values at runtime and ret= caller chain; NOT expected to resolve input vs output direction (blocking fact above).
