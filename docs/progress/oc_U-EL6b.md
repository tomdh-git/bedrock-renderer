## NEXT
DONE

# U-EL6b: VV in/out resources per pass (builder 0x55f1450)

Goal: close checklist item L6b "in/out resources per pass" for the passes declared inside the Vibrant Visuals frame-graph builder 0x55f1450 (size 0x4e144, 0x55f1450..0x563f594; BGFX_MAP.md 6ar: giant VV frame-graph function; entered indirectly — no static callers per xref/ripscan [V]).

Prior attempts (NOT redone): docs/progress/oc_U-EL6b_r1.md .. r8.md. All end CLOSES? NO with the same blocking fact: declaration functions (0x5698290 dominant, 15 call sites; 0x5684660 "Transparent" x1; 0x5667860 x4; 0x5693680 x7; 0x5694510 x2; 0x5695960; 0x5696540; 0x5697650; 0x56CB540; 0xBBBD7F0) each receive a 28-byte pass descriptor in r8 and copy it opaquely; nothing in 0x55f1450 or its callees separates input from output resources. Static angles already exhausted: full builder listing scan (no rip-relative lea to .rdata, no binder-name string loads in 0x55f1450 [V]); binder-name search (BindFramebufferColor/Depth, BindMaterialTexture, BindShaderBuffer, BindAccelerationStructure — absent from .rdata, no locatable call sites [I from tool output]); 0xBB93890 registrar links two pass pointers into global [data_129C9628] with no field semantics [V]; decl fn 0x5698290 full disassembly — opaque movups copy [V]; resource-binding helpers 0x5690960/0x5690E10/0x56912D0 undecoded (no preflight/dossier) [V structure, ? semantics]; consumer 0xc273420 reads pass +0x228/+0x230 mode bytes via sub_a4c70 map inserts, not the descriptor's input/output fields [V structure, ? role]; livemem of global [data_129C9628] reads encoded non-canonical qword 0x8BEB3C381FB2F1FE, not walkable [V live]. See r1-r8 for verbatim proofs; not repeated here.

## New this session (live capture result)

- docs/data/live/oc_u_el6b_desc.txt exists (capture DONE t=120 per docs/data/live/_status.txt) but oc_u_el6b_desc hits=0 samples=0: the execute breakpoint at decl entry 0x5698290 was never hit — the game was not running in a Vibrant Visuals world during the capture window. No descriptor bytes dumped, no ret= caller chain named. [V live] cite docs/data/live/_status.txt line 3.
- The game IS running now: pid 13452, base 0x7ff7a59c0000, Minecraft.Windows.exe 1.26.62.01 [V live] `python tools/sigs/livemem.py status`. Capture oc_u_el6b_desc remains state "pending" in docs/progress/capture_requests.json (rva 0x5698290, size 0x100, max 6). The 4-pending batch limit (oc_u_el6b_desc, el10b_lighting_desc, oc_u_er2, oc_u_er1_producer) prevents re-queueing a duplicate. If the orchestrator re-runs the batch while the game is in a VV world, 0x5698290 executes per frame and the capture may hit; then this unit can be re-opened.
- No productive livemem read is available: the only located structure head, global [data_129C9628], reads back as an encoded non-canonical qword (r2) and pass-object addresses are unknown — reading them would require a range scan, which the brief forbids.

## Proven descriptor struct (28 bytes, passed in R8 to the decl fns) — layout [V]

One row per distinct offset, all read/store sites listed. Meaning column: only what an instruction or string shows, else '-'. Role (input vs output resource) is NOT shown by any instruction — tagged [?].

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|--------------------|-------------------------|---------|-----|
| +0x00 | 2B | desc1 build at 0x55f1fca, [rbp+0x2C00] := ax; ax loaded from [rbp+0x27A0] by 0x55f1f61 (movzx; u16 source at config object +0x10 via 0x55f1f24 `mov eax,[rcx+0x10]`) | `0x55f1f68  mov [rbp+0x2C00],ax` | u16 count field A; input-count vs output-count not distinguished by any instruction | [V] store / [?] role |
| +0x02 | 2B | same site, [rbp+0x2C02] := ax (ax=[rbp+0x27A2]=[rcx+0x14] via 0x55f1f39 `mov eax,[rcx+0x14]`) | `0x55f1f76  mov [rbp+0x2C02],ax` | u16 count field B; direction not distinguished | [V] store / [?] role |
| +0x04 | 4B | [rbp+0x2C04] := eax ([rcx+0x18] at 0x55f1f4e) then overwritten by site immediate | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | u32 per-pass index [I from immediate]: 0x2D=45 at 0x55f1fca; 0x1A=26 at 0x562e4c8 (`0x562e4c8  mov dword ptr [rbp+0x2C04],0x1A`); 0x29=41 at 0x560b6a3 (`0x560b6a3  mov dword ptr [rbp+0x2444],0x29`) | [V] store / [I] index |
| +0x08 | 8B | [rbp+0x2C08] := rax (rax=[rbp+0x27A8], loaded by 0x55f1f89 `mov rax,[rbp+0x27A8]`) | `0x55f1f90  mov [rbp+0x2C08],rax` | u64 resource reference A; input vs output resource role NOT proven | [V] store / [?] role |
| +0x10 | 8B | [rbp+0x2C10] := rax (rax=[rbp+0x27B0], loaded by 0x55f1f97 `mov rax,[rbp+0x27B0]`) | `0x55f1f9e  mov [rbp+0x2C10],rax` | u64 resource reference B; input vs output resource role NOT proven | [V] store / [?] role |
| +0x18 | 4B | [rbp+0x2C18] := 0 at site 0x55f1fca; =3 via 0x55f1f57 `mov dword ptr [rbp+0x27B8],3` at two-descriptor site | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | u32 flags; 0 vs 3 seen at the two-descriptor site; bit meanings not shown | [V] store / [?] role |
| desc +0x00..+0x0F | 16B | 0x5698290 entry (rbx = r8 = desc ptr) | `0x56982dc  movups xmm0,[rbx]` | all 16 descriptor bytes read at decl entry, copied opaquely | [V] |
| desc +0x0C..+0x1B | 16B | 0x5698290 entry | `0x56982df  movups xmm1,[rbx+0xC]` | remaining 16 descriptor bytes read, copied opaquely | [V] |
| alloc +0x08..+0x17 | 16B | 0x5698290 (rdi = allocated 0x28-byte pass object; alloc size via 0x56982bb `mov edx,0x28`) | `0x56982e3  movups [rdi+8],xmm0` | descriptor bytes written to allocated pass object +0x08 | [V] |
| alloc +0x14..+0x23 | 16B | 0x5698290 | `0x56982e7  movups [rdi+0x14],xmm1` | descriptor bytes written to allocated pass object +0x14 | [V] |

Struct: {u16 +0x00, u16 +0x02, u32 +0x04, u64 +0x08, u64 +0x10, u32 +0x18} = 28 bytes [V]. Every byte is read by the two movups at 0x56982dc and 0x56982df and written by the two movups at 0x56982e3 and 0x56982e7 — full opaque copy, no field split into input/output [V].

Decl fn 0x5698290 behavior beyond the copy [V]: stores one fixed vtable for every pass (0x56982d2 `lea rax,[0xF25C820]` / 0x56982d9 `mov [rdi],rax` at allocated+0x00 — identical for all passes, so vtable slots cannot distinguish per-field direction); appends the allocated ptr to the context list at context+0x28 (0x56982ef `mov rdx,[rsi+0x28]` / 0x56982f9 `mov [rdx],rdi` / 0x56982fc `add qword ptr [rsi+0x28],8`); adds a 0x50-stride entry at context+0x40 (0x569832f `mov rbx,[rsi+0x40]` / 0x569833d `mov [rbx],r8` / 0x5698340 `mov [rbx+8],rdi` / 0x569834f `add qword ptr [rsi+0x40],0x50`). Two-descriptor pattern at site 0x55f1fca/0x55f1fe7: desc1 +0x04=0x2D/+0x18=0 -> result [rbp+0x1C10]; desc2 shares +0x00/+0x02/+0x08/+0x10 and differs only at +0x04/+0x18 (+0x18=3) -> result [rbp+0x1CE8]; registration of both pointers follows via 0xBB93890 into global [data_129C9628] (r2, [V]).

## Blocking fact (unchanged, still open)

No instruction or string in builder 0x55f1450 or its decl callees tags any descriptor field as input resource or output resource: not the u16 counts (+0x00/+0x02), not the u64 resource references (+0x08/+0x10). All 28 bytes are copied opaquely by 0x5698290 (two movups in, two movups out) [V]. Builder entered indirectly (no callers) so no call-site context fixes direction [V]. The live capture at the proven decl entry returned no samples, so no runtime descriptor bytes or caller chain are available [V live].

## CLOSES?

CLOSES? NO — single blocking fact: the input/output direction of the descriptor fields (u16 counts +0x00/+0x02; u64 resource references +0x08/+0x10) cannot be determined statically (opaque full-copy by 0x5698290 [V]; nothing in 0x55f1450 or its callees separates input from output resources [V]) and the live capture oc_u_el6b_desc at decl entry 0x5698290 returned hits=0 samples=0 (docs/data/live/_status.txt) — no descriptor bytes dumped, no ret= caller chain, because the game was not running in a VV world during the capture window. The game is now running (pid 13452 [V live]) and the capture remains queued pending; if the orchestrator re-runs it while the game is in a VV world, the dumped desc bytes plus ret= caller chain can confirm field roles and this unit can be re-opened. Per-pass in/out is otherwise covered by oc_U-EM1e.md (M1e) and parked in MIRROR_SKIP; ticking this item requires M1e or live capture data, neither available within this unit.

## TOOL REQUESTS

CAPTURE REQUESTED oc_u_el6b_desc — already queued in docs/progress/capture_requests.json (rva 0x5698290, size 0x100, max 6, state pending; result file docs/data/live/oc_u_el6b_desc.txt has header lines only, hits=0 samples=0). No new capture requested (4-pending limit reached; same entry would re-hit the no-sample result unless the game is in a VV world at run time). No helper scripts written (all work with existing tools: rdis, xref.py, livemem.py; descscan2 not applicable — not a visitor function).
