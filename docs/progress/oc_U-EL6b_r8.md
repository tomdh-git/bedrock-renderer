## NEXT
DONE

# U-EL6b: VV in/out resources per pass (builder 0x55f1450)

Item (L6b): "in/out resources per pass" for the passes declared inside the Vibrant Visuals frame-graph builder 0x55f1450 (size 0x4e144, 0x55f1450..0x563f594; BGFX_MAP.md 6ar: giant VV frame-graph function). The pass declaration functions (0x5698290 dominant, 15 call sites; 0x5684660 "Transparent" x1; 0x5667860 x4; 0x5693680 x7; 0x5694510 x2; 0x5695960; 0x5696540; 0x5697650; 0x56CB540; 0xBBBD7F0) each receive a 28-byte pass descriptor in r8 and copy it opaquely into an allocated pass object. Per BGFX_MAP.md 6o/6p, pass names are FNV-1 hashes with no input/output annotation anywhere.

Proven [V] in prior attempts (docs/progress/oc_U-EL6b_r1.md, _r2.md, _r3.md — not repeated here): the 28-byte descriptor layout {u16 +0x00, u16 +0x02, u32 +0x04, u64 +0x08, u64 +0x10, u32 +0x18}, every store instruction, pass-index immediates (0x2D/0x1A/0x29), u16 counts sourced from a config object, and the opaque full-copy by 0x5698290. Nothing in 0x55f1450 or its callees tags any descriptor field as input or output resource — that is the single blocking fact, still open (item parked in MIRROR_SKIP; per-pass in/out also tracked by oc_U-EM1e.md M1e).

## New angles tried in this unit (none — static analysis exhausted per 2026-11-22 r4 review)

r1-r3 already tried and failed to separate input from output: (a) xref.py callers / ripscan of 0x55f1450 (none; builder is entered indirectly, so no call-site context fixes field direction); (b) full builder listing scan (no rip-relative lea to .rdata, no binder-name string loads in 0x55f1450); (c) 0xBB93890 registrar (links two pass pointers into global [data_129C9628], no field semantics) and 0x567A7B0 consumer (copies vtable+qword into a 0x30-byte struct, generic); (d) undecoded resource-binding helpers 0x5690960/0x5690E10/0x56912D0 dispatched by 0x5684660 by resource index; (e) consumer 0xc273420 frame-graph generate (reads pass +0x228/+0x230 mode bytes via sub_a4c70 map inserts, not the descriptor's input/output fields); (f) binder-name search (BindFramebufferColor/Depth, BindMaterialTexture, BindShaderBuffer, BindAccelerationStructure — no .rdata strings, no locatable call sites); (g) livemem of global [data_129C9628] (reads back as encoded non-canonical qword 0x8BEB3C381FB2F1FE, not walkable; live values cannot establish field direction anyway). None of these separates input from output. Not repeated here; see r1-r3 for verbatim proofs.

## Live capture (pending — the only remaining evidence source)

Capture oc_u_el6b_desc was queued in docs/progress/capture_requests.json: rva 0x5698290 (decl fn entry; r8 = 28-byte pass descriptor ptr), size 0x100, max 6, why "L6b: dump desc bytes at entry to confirm field sizes/values and name caller chain via ret=". State: pending (4-per-batch limit reached alongside el10b_lighting_desc, oc_u_er2, oc_u_er1_producer). Result file docs/data/live/oc_u_el6b_desc.txt exists but has no data lines (hits=0 samples=0: 0x5698290 was not entered during the capture session — the game was not running in a VV world). No descriptor bytes and no ret= caller chain are available yet, so no live evidence for input vs output direction exists.

## Answer: 28-byte pass descriptor (passed in r8 to 0x5698290; every line verified verbatim against the exe with rdis)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| +0x00 | 2B | desc1 build at 0x55f1fca, [rbp+0x2C00] := ax (ax = [rbp+0x27A0] loaded by 0x55f1f61 movzx; desc2 +0x00 stored by 0x55f1f32 mov [rbp+0x27A0],ax) | `0x55f1f68  mov [rbp+0x2C00],ax` | count field A (u16); direction (input count vs output count) not distinguished by any instruction | [V] |
| +0x02 | 2B | desc1 build at 0x55f1fca, [rbp+0x2C02] := ax (ax = [rbp+0x27A2] loaded by 0x55f1f6f movzx) | `0x55f1f76  mov [rbp+0x2C02],ax` | count field B (u16); direction not distinguished | [V] |
| +0x04 | 4B | desc1 build at 0x55f1fca, [rbp+0x2C04] := eax ([rbp+0x27A4] at 0x55f1f83) then overwritten | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | per-pass index (0x2D=45 at this site; 0x1A and 0x29 seen at other sites per r3) [I] | [V] |
| +0x08 | 8B | desc1 build at 0x55f1fca, [rbp+0x2C08] := rax (rax = [rbp+0x27A8], a resource reference) | `0x55f1f90  mov [rbp+0x2C08],rax` | resource reference A; input vs output role NOT proven | [V] store / [?] role |
| +0x10 | 8B | desc1 build at 0x55f1fca, [rbp+0x2C10] := rax (rax = [rbp+0x27B0], a resource reference) | `0x55f1f9e  mov [rbp+0x2C10],rax` | resource reference B; input vs output role NOT proven | [V] store / [?] role |
| +0x18 | 4B | desc1 build at 0x55f1fca, [rbp+0x2C18] := 0; desc2 build sets =3 at 0x55f1f57 | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | flags u32 (0 vs 3 at the two-descriptor site) | [V] |
| desc +0x00..+0x0F | 16B | 0x5698290 entry, rbx = desc ptr | `0x56982dc  movups xmm0,[rbx]` | all 16 descriptor bytes read at entry, copied opaquely | [V] |
| desc +0x0C..+0x1B | 16B | 0x5698290 entry, rbx = desc ptr | `0x56982df  movups xmm1,[rbx+0xC]` | remaining 16 descriptor bytes read at entry, copied opaquely | [V] |
| alloc +0x08 | 16B | 0x5698290, rdi = allocated pass object | `0x56982e3  movups [rdi+8],xmm0` | descriptor bytes written to allocated pass object +0x08 | [V] |
| alloc +0x14 | 16B | 0x5698290 | `0x56982e7  movups [rdi+0x14],xmm1` | descriptor bytes written to allocated pass object +0x14 | [V] |

Every byte of the descriptor is read by the two movups at 0x56982dc and 0x56982df (all 28 bytes, [V]) and written by the two movups at 0x56982e3 and 0x56982e7 (all 28 bytes, [V]) into the allocated struct, which is then appended to the context list at context+0x28 (0x56982f9 mov [rdx],rdi / 0x56982fc add qword ptr [rsi+0x28],8) and a 0x50-stride entry added at context+0x40 (0x569833d mov [rbx],r8 / 0x5698340 mov [rbx+8],rdi). No instruction or string in 0x55f1450 or its callees labels any descriptor field as input or output resource. Same result at the multi-arg decl fn 0x5684660 ("Transparent"): it iterates an array of 0x290-byte resource records (base [rdx+0x10], end [rdx+0x18], stride 0x290) and dispatches to undecoded helpers 0x5690960 / 0x5690E10 / 0x56912D0 by resource counter (0x568487b cmp ecx,1 / 0x5684880 test ecx,ecx); none of them tags descriptor direction. The builder is entered indirectly (no direct callers per xref/ripscan), so no call-site context fixes direction either.

## CLOSES?
CLOSES? NO — single blocking fact: the input/output direction of the descriptor fields (u16 counts +0x00/+0x02; u64 resource references +0x08/+0x10) cannot be determined statically — all 28 bytes are copied opaquely by 0x5698290 [V] and nothing in 0x55f1450 or its callees separates input from output resources. Live capture oc_u_el6b_desc (0x5698290 entry) is pending with no hits yet; it needs the game running in a Vibrant Visuals world so the descriptor bytes and the ret= caller chain are dumped. When that capture yields data this unit can be re-opened to prove field direction and close the item.

## TOOL REQUESTS
CAPTURE REQUESTED oc_u_el6b_desc — already queued in docs/progress/capture_requests.json (rva 0x5698290, size 0x100, max 6, state pending); result file docs/data/live/oc_u_el6b_desc.txt has no data lines yet. No helper scripts written (all work with existing tools: rdis, xref.py; descscan2 not applicable — not a visitor function; livemem read of [data_129C9628] already done in r2). None otherwise.
