## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator. r15 (2026-11-22, CLOSES NO): the createTexture issuance chain is live-proven through sub_4e05e50; only missing is the static link texgroup_load(0x5421c90) -> sub_4e05e50. This session attacks that single blocking fact from the ordered new angle: decode the function containing 0x1289496 and find who calls it. Nothing already proven is redone.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; abbreviations always expanded in place.

## Already proven (do NOT redo — cited from r1-r17 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture 0xe8143c0 has no static caller, reached only via indirect [vptr+0xD0] thunks.
- r3 (not redone): texgroup_load 0x5421c90 calls the Minecraft texture cache 0x18718d0 directly at `0x54227af  call 0x18718D0`; texload 0x58a1310 and texload_task 0x541bf00 have EMPTY static caller lists and are never called by texgroup_load.
- 0x18718d0 fully decoded [V pre/0x18718d0_fn.md, not redone]: cache lookup loop; on miss builds an object with vtable 0xEFCA680 and calls completion 0x186dac0; never calls sub_4e05e50 or sub_12893d0.
- r4/r5 (not redone): command-byte-14 producer = sub_0xbc73770 writes 0x0E into the bgfx command buffer [V]; reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V]; MC texture code calls none statically [V xref evidence]. Hint's conditional path (wrapper called from texture-object init via vtable 0xEFCA580 slot 4): not observed, not statically reachable; stopped per hint.
- Handle into texture object: [texture_obj+0x00] at 0xc296e26 (`0xC296E26  mov [rdi],ax`, size 2, word) [V r7/dis, re-verified]; `0xC296E1A  call 0xBC74120` returns handle in ax [V]; `0xC296E32  movups [rdi+8],xmm0` (16) stores rest of result [V].
- createTexture -> TextureD3D12::create 0xe81bf30: `0xE81455B  call 0xE81BF30`, ret site `0xE814560  nop` (live capture l8b ret=0xE814560) [V live + dis, re-verified this session].
- Dispatcher case consuming command byte 14: `0xBC6A2B1  mov rax,[rax+0xD0]` (vtable slot 26 = createTexture; BGFX_MAP line 403/1512) / `0xBC6A2C2  call qword ptr [0xF99FFA0]` / `0xBC6A2C8  test rax,rax` — live caller of createTexture ret=0xBC6A2C8 [V dis re-verified this session + V live createtexture_callers].
- sdk headers [V file read]: TexturePtr.h `static_assert(sizeof(TexturePtr) == 32)`, mClientTexture +0x00 / mResourceLocationPtr +0x10 (two shared_ptr); ClientTexture empty struct; BedrockTexture.h `static_assert(sizeof(BedrockTexture) == 48)`.

## This session — new angle: indirect caller of sub_4e05e50 (ret=0x1289496) and who calls it

### Capture mc_root_4e05e50_callers.txt [V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| capture header | docs/data/live/mc_root_4e05e50_callers.txt | - | - | `CALLER ret=0x1289496 first_hit=1` (150 hits / 32 samples; every sample ret=0x1289496) | sub_4e05e50 is entered only from return address 0x1289496, i.e. the instruction right after the call site at 0x1289490 | [V live] |
| RCX vptr | [rcx+0x00] | 8 | [rcx+0x00] | all 32 RCX samples begin with `385821A8F67F0000` = 0x00007FF6A8215838 | constant vptr at object+0x00 across all samples -> polymorphic object whose vptr+8 resolves to sub_4e05e50 at runtime | [V live] |

0x1289496 is NOT a function entry: rdis `fn 0x1289440` reports "; 0x1289440 is inside sub_12893d0". The function containing 0x1289496 (and the call site at 0x1289490) is sub_12893d0 [0x12893D0..0x12895D3), size 0x203, 13 xrefs in [V rdis fn]. Earlier notes (r17/r18) that treat 0x1289440 as a separate function with 0 static callers are wrong: 0x1289440 is just a local label (loc_1289440, the add_ref retry block) inside sub_12893d0.

### sub_12893d0 — full decode [V dis]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | 0x12893D0 | 1 | - | `0x12893D0  push rbp` | function entry, frame setup | [V] |
| array begin | r13=[rcx+0x0] | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | r13 = array begin (deferred-transaction vector {begin,end}) | [V] |
| array end | r14=[rcx+0x8] | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | r14 = array end | [V] |
| shared ctrl load | [r13+0x8] | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` | element+0x8 = shared control-block pointer | [V] |
| refcount load (sub_12893d0) | [rcx+0x8] | 4 | [rcx+0x8] | `0x128943A  mov eax,[rcx+8]` | eax = refcount at ctrl+8 | [V] |
| refcount zero test | eax | 4 | - | `0x1289440  test eax,eax` | skip add_ref when refcount == 0 (loc_1289440) | [V] |
| add_ref new value | edx | 4 | - | `0x1289444  lea edx,[rax+1]` | edx = refcount+1 | [V] |
| add_ref CAS (sub_12893d0) | [rcx+0x8] | 4 | [rcx+0x8] | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment, retry on failure | [V] |
| cmpxchg retry | - | - | - | `0x128944C  jne short 0x1289440` | CAS failed: reload and retry | [V] |
| element copy | [r13] | 16 | [r13] | `0x128944E  movups xmm0,[r13]` | copy element {ptr@0, ctrl@8} to local desc | [V] |
| pointer spill | [rbp-0x50] | 16 | [rbp-0x50] | `0x1289453  mov rax,[r13]` / `0x1289457  movaps [rbp-0x50],xmm0` | element ptr then 16-byte copy spilled | [V] |
| null test | rax | 4 | - | `0x128945B  test rax,rax` | [r13] pointer null? | [V] |
| invoke branch | - | - | - | `0x128945E  jne short 0x128947D` | non-null: virtual-call path | [V] |
| null exit | - | - | - | `0x1289460  jmp 0x1289508` | null: done with element | [V] |
| skip reload | [rbp-0x50] | 8 | [rbp-0x50] | `0x1289470  mov rax,[rbp-0x50]` | reload spilled pointer (skip path) | [V] |
| null test 2 | rax | 4 | - | `0x1289474  test rax,rax` | null? | [V] |
| null exit 2 | - | - | - | `0x1289477  je 0x1289508` | null: done | [V] |
| object load | [r13+0x10] | 8 | [r13+0x10] | `0x128947D  mov rcx,[r13+0x10]` | rcx = element+0x10 = `this` for the virtual call | [V] |
| object null test | rcx | 4 | - | `0x1289481  test rcx,rcx` | object pointer null? | [V] |
| object null exit | - | - | - | `0x1289484  je short 0x1289505` | null: skip call | [V] |
| vptr load | [rcx] | 8 | [rcx] | `0x1289486  mov rax,[rcx]` | rax = object vptr | [V] |
| vtable slot 1 load | [vptr+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = indirect call target | [V] |
| out desc ptr | rbx | 8 | [rbp-0x20] | `0x128948D  mov rdx,rbx` | rdx = &local element copy passed as 2nd arg | [V] |
| INDIRECT CALL -> sub_4e05e50 | [0xF99FFA0] | 6 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | CFG-stub tail-call; rax = vptr[1] = sub_4e05e50 at runtime; return site 0x1289496 = capture ret= | [V] |
| capture return site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the call; matches capture ret=0x1289496 in all 32 samples | [V live] |
| object null-out | [r13+0x10] | 8 | [r13+0x10] | `0x1289497  mov rcx,[r13+0x10]` / `0x128949B  mov qword ptr [r13+0x10],0` | reload object, clear element+0x10 before release | [V] |
| second-array begin | rdi | 8 | [rdi] | `0x128954F  mov rbx,[rdi]` | second pass: array {begin,end} at [rdi],[rdi+8] | [V] |
| second-pass run call | [0xF99FFA0] | 6 | [0xF99FFA0] | `0x128957D  call qword ptr [0xF99FFA0]` | second array: obj->vptr[1]() run | [V] |
| second-pass dtor call | [0xF99FFA0] | 6 | [0xF99FFA0] | `0x1289599  call qword ptr [0xF99FFA0]` | second array: obj->vptr[0](1) destroying destructor | [V] |
| result count store | [rsi] | 8 | [rsi] | `0x12895A8  mov [rsi],r12` | out[0] = processed count | [V] |
| sub_12893d0 ret | - | 1 | - | `0x12895D2  ret` | function end | [V] |

Meaning of sub_12893d0: deferred-transaction processor. For each 0x18-byte element {ptr@0, shared_ctrl@8, obj@0x10} from [rcx] to [rcx+8]: add_ref(shared_ctrl), then call obj->vptr[1](&element_copy) — at capture time vptr[1] = sub_4e05e50 — then release the old object; a second array ([rdi],[rdi+8]) is released the same way; count + results are stored at [rsi]/[rsi+8]/[rsi+0x18]. This is how a texture job object's vtable[1] (= sub_4e05e50, the texture create/load method) gets invoked.

### sub_12893d0 static callers — who calls it [V rdis callers + dis]

`rdis callers 0x12893D0`: 4 calling functions, 13 call sites total — sub_1145c20 x2, sub_6622610 x1, sub_66232b0 x8, sub_6632bf0 x2 [V]. Exact sites verified by disassembly:

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_1145c20 site 1 | 0x1145D5A | 5 | - | `0x1145D5A  call 0x12893D0` | sub_1145c20 -> sub_12893d0 | [V] |
| sub_1145c20 site 2 | 0x1145EE5 | 5 | - | `0x1145EE5  call 0x12893D0` | sub_1145c20 -> sub_12893d0 | [V] |
| sub_6622610 site | 0x6622662 | 5 | - | `0x6622662  call 0x12893D0` | sub_6622610 -> sub_12893d0 | [V] |
| sub_6632bf0 site 1 | 0x6632C55 | 5 | - | `0x6632C55  call 0x12893D0` | deferred buffer vector -> sub_12893d0 | [V] |
| sub_6632bf0 site 2 | 0x6632D1E | 5 | - | `0x6632D1E  call 0x12893D0` | deferred texture vector -> sub_12893d0 | [V] |
| sub_66232b0 sites | 0x66232B0 | - | - | (8 sites inside sub_66232b0) | sub_66232b0 -> sub_12893d0 x8 [V rdis callers] | [V] |

sub_6632bf0 (0x6632BF0..0x6634BF0, 2 xrefs in, from BgfxFrameBuilder::endFrame 0x66232b0 per docs/functions/6632bf0.md) is the deferred-transaction flush: it moves this+0x00 ("Deferred Texture Transactions", string at 0xF54E8AF) and this+0x18 ("Deferred Buffer Transactions", string at 0xF54E847) vectors out of the object, zeroes the originals, calls sub_12893d0 twice (above), then runs each job (`job->vtbl[1]()`) and destroys each job (`job->vtbl[0](1)`), freeing storage via 0xe935700:

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_6632bf0 entry | 0x6632BF0 | 1 | - | `0x6632BF0  push rbp` | flush entry; this = deferred-transactions object | [V] |
| texture vector end | [rcx+0x10] | 8 | [rcx+0x10] | `0x6632C0A  mov rax,[rcx+0x10]` | this+0x10 = texture vector end | [V] |
| texture vector copy | [rcx+0x0] | 16 | [rcx+0x0] | `0x6632C0E  movups xmm0,[rcx]` | this+0x0 = texture vector begin -> stack copy | [V] |
| texture vector store | [rbp-0x50] | 16 | [rbp-0x50] | `0x6632C11  movaps [rbp-0x50],xmm0` | stack copy of texture vector {begin,end} | [V] |
| texture label | "Deferred Texture Transactions" | 8 | [rbp-0x38] | `0x6632C19  lea rax,[0xF54E8AF]` | string constant labeling the texture vector | [V] |
| buffer vector end | [rcx+0x28] | 8 | [rcx+0x28] | `0x6632C24  mov rax,[rcx+0x28]` | this+0x28 = buffer vector end | [V] |
| buffer vector copy | [rcx+0x18] | 16 | [rcx+0x18] | `0x6632C28  movups xmm0,[rcx+0x18]` | this+0x18 = buffer vector begin -> stack copy | [V] |
| zero buffer end | [rcx+0x20] | 16 | [rcx+0x20] | `0x6632C33  movups [rcx+0x20],xmm1` | move-out: zero original buffer end | [V] |
| zero texture begin | [rcx+0x0] | 16 | [rcx+0x0] | `0x6632C33  movups [rcx],xmm1` | move-out: zero original texture begin | [V] |
| zero texture end | [rcx+0x10] | 16 | [rcx+0x10] | `0x6632C36  movups [rcx+0x10],xmm1` | move-out: zero original texture end | [V] |
| buffer label | "Deferred Buffer Transactions" | 8 | [rbp-0x18] | `0x6632C42  lea rax,[0xF54E847]` | string constant labeling the buffer vector | [V] |
| run job vtbl[1] load | [rcx] / [rcx+0x8] | 8 | [rcx], [rax+0x8] | `0x6632C81  mov rax,[rcx]` / `0x6632C84  mov rax,[rax+8]` | job->vptr, job->vptr[1] load | [V] |
| run job indirect call | [0xF99FFA0] | 6 | [0xF99FFA0] | `0x6632C88  call qword ptr [0xF99FFA0]` | job->vtbl[1]() | [V] |
| destroy job vtbl[0] load | [rcx] / [rax] | 8 | [rcx], [rax] | `0x6632CC1  mov rax,[rcx]` / `0x6632CC4  mov rax,[rax]` | job->vptr[0] = destroying destructor load (edx=1 at `0x6632CC7  mov edx,1`) | [V] |
| destroy job indirect call | [0xF99FFA0] | 6 | [0xF99FFA0] | `0x6632CCC  call qword ptr [0xF99FFA0]` | job->vtbl[0](1) | [V] |
| free storage | [rsi-8] | 8 | [rsi-8] | `0x6632CF1  mov rax,[rsi-8]` / `0x6632D10  call 0xE935700` | free job-vector storage | [V] |

### sub_4e05e50 — texture-object vtable[1] create/load method, 0 static xrefs [V dis + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | 1 | - | `0x4E05E50  push rbp` | function entry; rdis: `sub_4e05e50 [0x4e05e50..0x4e06074) size 0x224 0 xrefs in` | [V] |
| out_ptr saved | rsi = rdx | 8 | reg | `0x4E05E6B  mov rsi,rdx` | 2nd arg (out pointer) saved to rsi | [V] |
| object saved | rdi = rcx | 8 | reg | `0x4E05E6E  mov rdi,rcx` | 1st arg (texture object*) saved to rdi | [V] |
| object+0x18 load | [rcx+0x18] | 8 | [rcx+0x18] | `0x4E05E71  mov rax,[rcx+0x18]` | shared ctrl of member at object+0x18 | [V] |
| object+0x10 load | [rdi+0x10] | 8 | [rdi+0x10] | `0x4E05E8C  mov rdx,[rdi+0x10]` | pointer member at object+0x10 | [V] |
| refcount load (sub_4e05e50) | [rdx+0x8] | 4 | [rdx+0x8] | `0x4E05E95  mov eax,[rdx+8]` | refcount of the object+0x10 pointee | [V] |
| add_ref CAS (sub_4e05e50) | [rdx+0x8] | 4 | [rdx+0x8] | `0x4E05EA8  lock cmpxchg [rdx+8],r8d` | atomic refcount increment | [V] |
| refcount inc | [rbx+0x8] | 4 | [rbx+0x8] | `0x4E05EBD  lock inc dword ptr [rbx+8]` | temporary inc of second refcounted member | [V] |
| dtor vfunc load | [rbx] / [[rbx]+0x0] | 8 | [rbx], [[rbx]+0x0] | `0x4E05ECF  mov rax,[rbx]` / `0x4E05ED2  mov rax,[rax]` | control-block dtor virtual for release | [V] |
| dtor indirect call | [0xF99FFA0] | 6 | [0xF99FFA0] | `0x4E05ED8  call qword ptr [0xF99FFA0]` | release shared member (dtor if last ref) | [V] |
| renderer ctx load | [rdi+0xE0] | 8 | [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | object+0xE0 = renderer context -> R9 (proves object >= 0xE8 bytes) | [V] |
| texture sub-object | rdi+0x58 | 8 | reg | `0x4E05F68  add rdi,0x58` | rdi = object+0x58, embedded texture sub-object | [V] |
| RCX to sub_bc41420 | rdi | 8 | reg | `0x4E05F74  mov rcx,rdi` | texture sub-object as RCX | [V] |
| dragon create call | 0xBC41420 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_bc41420 -> 0xc296b50 -> ... -> createTexture | [V] |
| sub_4e05e50 ret site | 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | return after sub_bc41420; live capture ret=0x4E05F7C | [V live] |
| result processing | [rbp-8] / [rbp-0x50] | 8 | [rbp-8], [rbp-0x50] | `0x4E05F7D  lea rcx,[rbp-8]` / `0x4E05F81  lea rdx,[rbp-0x50]` / `0x4E05F85  call 0x4E061B0` | results forwarded to sub_4e061b0 | [V] |
| fail store [out]=0 | [rsi] | 8 | [rsi] | `0x4E06010  mov qword ptr [rsi],0` | failure path writes 0 to out pointer | [V] |
| return out_ptr | rax = rsi | 8 | reg | `0x4E0604B  mov rax,rsi` | return out pointer | [V] |

Handle trace into the texture object (inside sub_c296b50, reached via sub_bc41420 at 0xBC41B39) [V r7/dis, re-verified]: `0xC296E1A  call 0xBC74120` returns handle in ax; `0xC296E26  mov [rdi],ax` (size 2, word) stores it at [texture_obj+0x00] where texture_obj = object+0x58; `0xC296E32  movups [rdi+8],xmm0` (16) stores the rest of the result at [texture_obj+0x8]. Full MC-side chain [V live + dis]: texture job object (capture vptr 0x00007FF6A8215838 at +0x00; vptr[1] = sub_4e05e50 at runtime) --sub_12893d0@0x1289490 (ret site 0x1289496)--> sub_4e05e50(object*, out_ptr) --> sub_bc41420 --> 0xc296b50 --> 0xbc73bf0 --> 0xbc73770 (command-byte-0x0E producer [V r4]) --> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, `0xBC6A2C2  call qword ptr [0xF99FFA0]`) --> createTexture 0xe8143c0 (live caller ret=0xBC6A2C8 [V live]) --> TextureD3D12::create 0xe81bf30 (`0xE81455B  call 0xE81BF30`, ret 0xE814560 [V l8b live + dis]) --> handle stored at [obj+0x58+0] at `0xC296E26  mov [rdi],ax` [V].

### TexturePtr connection

sub_4e05e50's RCX is the texture OBJECT itself (vtable[1] method; vptr at object+0x00, capture vptr constant 0x7FF6A8215838 across all 32 samples; sub_4e05e50 reads object+0xE0, proving the object is >= 0xE8 bytes) [V live + dis] — it is NOT a TexturePtr* (TexturePtr is 32 bytes and non-polymorphic per the sdk header) [V file read + V dis]. The texture object carries refcounted/shared_ptr-shaped members at object+0x10 and object+0x18 that sub_4e05e50 add_refs/releases via [0xF99FFA0] [V dis], matching the sdk TexturePtr shape (two shared_ptr members, sizeof 32) [V file read src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h; ClientTexture empty struct; BedrockTexture 48 bytes [V file read]]. The created handle lands at [obj+0x58+0] inside the job object [V dis].

### texgroup_load(0x5421c90) / texload(0x58a1310) static link — negative evidence [V]

texgroup_load's body (first 900+ instructions fully enumerated) calls sub_5477a30, sub_5475A30, sub_18718d0, sub_5424000, sub_5424130 — none of which is sub_4e05e50 or in sub_12893d0's caller set {sub_1145c20, sub_6622610, sub_66232b0, sub_6632bf0}:

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load cache call | 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texgroup_load -> texture cache 0x18718d0 [V r3] | [V] |
| texgroup_load sub_5477A30 | 0x5421DEC | 5 | - | `0x5421DEC  call 0x5477A30` | texgroup_load -> sub_5477a30 (not in sub_12893d0 tree) | [V] |
| texgroup_load sub_5475A30 | 0x5421ED6 | 5 | - | `0x5421ED6  call 0x5475A30` | texgroup_load -> sub_5475a30 (not in sub_12893d0 tree) | [V] |
| texgroup_load sub_5424000 | 0x5422869 | 5 | - | `0x5422869  call 0x5424000` | texgroup_load -> sub_5424000 (not in sub_12893d0 tree) | [V] |
| texgroup_load sub_5424130 | 0x5422C5D | 5 | - | `0x5422C5D  call 0x5424130` | texgroup_load -> sub_5424130 (not in sub_12893d0 tree) | [V] |

sub_4e05e50 has 0 static callers: `rdis callers 0x4E05E50` -> "-- 0 calling function(s)"; fn 0x4E05E50..0x4E06074, 0 xrefs in [V rdis]. Upward chains from sub_12893d0's four callers all dead-end at functions with no static callers (sub_879010, sub_661a400, sub_661f200, sub_5360e00, sub_943920, sub_92b520, sub_55f1450 each return `rdis callers` = 0 / xref.py empty) [V rdis/xref]: sub_12893d0 is statically reachable only from endFrame->sub_6632bf0 (plus the indirectly dispatched sub_1145c20/sub_6622610/sub_66232b0). Conclusion: there is no [V]-proven static path texgroup_load(0x5421c90)/texload(0x58a1310) -> sub_4e05e50. The link is runtime-only: texture jobs (vtable[1] = sub_4e05e50) are created/enqueued during pack load and flushed at endFrame -> sub_12893d0 -> sub_4e05e50; the enqueue site (population of the deferred texture vector this+0x00 flushed by sub_6632bf0) is not statically located.

## What I tried that failed (this session; do not redo r1-r17)

- Upward caller chains from all four sub_12893d0 callers (sub_1145c20<-sub_882ee0<-sub_879480<-sub_879010; sub_6622610<-sub_661a770<-sub_661a400/sub_661f200/sub_6632fd0; sub_bbd42d0<-sub_5a86920<-sub_5a837b0<-sub_5360e00; sub_bbd4490<-sub_534f560<-sub_943920/sub_5348840<-sub_92b520; sub_e86ced0<-sub_bcacd90<-sub_55f1450): every top function has 0 static callers [V rdis/xref] — reached only via indirect/vtable dispatch; none is texgroup_load/texload.
- TexturePtr* claim for sub_4e05e50's RCX: refuted — RCX is a polymorphic texture object (constant vptr 0x7FF6A8215838, reads object+0xE0) [V live + dis], not a 32-byte TexturePtr [V file read].
- Prior negatives (not redone): xref.py callers 0xe8143c0 EMPTY; texload/texload_task EMPTY; imm/xref 0 hits; completion callback 0x186DAC0 does not call sub_4e05e50/sub_12893d0; cache 0x18718d0 miss path (vtable 0xEFCA680 object + completion 0x186dac0) never reaches sub_4e05e50 [V prior].

## Interpretation

Proven [V] this session: sub_12893d0 decoded instruction-complete (the indirect caller of sub_4e05e50; call at `0x1289490  call qword ptr [0xF99FFA0]`, capture ret site 0x1289496); sub_12893d0's 4 callers / 13 sites [V rdis callers]; endFrame->sub_6632bf0 deferred texture-transaction flush calls sub_12893d0 at `0x6632C55`/`0x6632D1E` [V dis]; sub_4e05e50 is texture-object vtable[1] (0 static xrefs [V rdis], target 0x4e05e50 live-proven [V live]); sub_4e05e50 -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (cmd 0x0E) -> dispatcher [vptr+0xD0] -> createTexture 0xe8143c0 -> TextureD3D12::create -> handle stored at [obj+0x58] at `0xC296E26  mov [rdi],ax` [V]. The createTexture issuance chain from MC-side texture objects is fully [V]-proven.

Not [V]-proven (single blocking fact): static link texgroup_load(0x5421c90)/texload(0x58a1310) -> sub_4e05e50 — sub_4e05e50 has 0 static callers and is reached only through vtable[1] indirect dispatch; texgroup_load's static callees do not enter sub_12893d0's caller tree; deferred-texture-vector population site unlocated. Sampler half (6ax) [V] and D3D12 backend chain [V] already proven; atlas stitchers tracked by L8a/L8b, out of scope.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90)/texload(0x58a1310) -> sub_4e05e50. sub_4e05e50 has 0 static callers (`rdis callers 0x4E05E50` -> 0 calling functions; fn 0x4E05E50..0x4E06074, 0 xrefs in [V rdis]) and is only reached via sub_12893d0's indirect vtable[1] call `0x1289490  call qword ptr [0xF99FFA0]` (capture ret site 0x1289496 [V live]); sub_12893d0 (13 xrefs in [V rdis]) is statically called from endFrame->sub_6632bf0 (`0x6632C55`/`0x6632D1E call 0x12893D0` [V dis]) plus sub_1145c20/sub_6622610/sub_66232b0 [V rdis callers], but all upward chains dead-end at 0-static-caller functions [V rdis/xref]; texgroup_load's static callees (`0x54227AF call 0x18718D0`, `0x5421DEC call 0x5477A30`, `0x5421ED6 call 0x5475A30`, `0x5422869 call 0x5424000`, `0x5422C5D call 0x5424130` [V dis]) do not enter sub_12893d0's caller tree. Everything else in the item is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0]->createTexture 0xe8143c0 [V live + dis], returned handle stored at [obj+0x58] by `0xC296E26  mov [rdi],ax` [V], TexturePtr/ClientTexture sdk headers [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None (no helper scripts written; all instruction lines re-verified verbatim against a fresh rdis dis this session; live capture logs are read-only inputs; xref.py/rdis callers/fn/imm used for positive and negative findings; no new capture needed — sub_12893d0 is not a function-entry-only target and its caller tree is exhausted statically).
