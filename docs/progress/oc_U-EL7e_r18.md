## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] (texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750); Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator. A prior agent file (oc_U-EL7e_r17.md) claimed CLOSES YES but r15 reviewed CLOSES NO; this session attacks the single blocking fact (the static texgroup_load -> sub_4e05e50 link) from the new angle ordered by r15: decode the indirect caller of sub_4e05e50 (ret=0x1289496, docs/data/live/mc_root_4e05e50_callers.txt) and find who calls it. Nothing already proven is redone.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located / [CAPTURE REQUESTED] livecap queued, result not yet back.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movdqu 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1-r17 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture 0xe8143c0 has no static caller, reached only via indirect [vptr+0xD0] thunks.
- r3 (not redone): texgroup_load 0x5421c90 calls the Minecraft texture cache 0x18718d0 (xref.py callers 0x18718D0 lists caller 0x5421c90 size 0x190f); texload 0x58a1310 and texload_task 0x541bf00 have EMPTY static caller lists and are never called by texgroup_load — the item-line sub-chain texgroup_load->texload->texload_task->0x18718d0 is NOT statically supported as written.
- 0x18718d0 fully decoded [V pre/0x18718d0_fn.md, not redone]: cache lookup loop; on miss builds an object with vtable 0xEFCA680 and calls completion 0x186dac0; never calls sub_4e05e50 or sub_1289440.
- r4/r5 (not redone): command-byte-14 producer = sub_0xbc73770 [V]; reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V]; MC texture code calls none statically [V xref evidence]. Hint's conditional path (wrapper called from texture-object init via vtable 0xEFCA580 slot 4): not observed, not statically reachable; stated per hint and stopped.

## This session — new angle: indirect caller of sub_4e05e50 (ret=0x1289496) and who calls it

r15 (2026-11-22, CLOSES NO): the createTexture issuance chain is live-proven through sub_4e05e50; only missing is the static link texgroup_load(0x5421c90) -> sub_4e05e50 (both 0 xrefs; runtime function pointer [0xF99FFA0]). Ordered next step: decode the function containing 0x1289496 and who calls it; do not redo the createTexture chain. Read first: docs/data/live/mc_root_4e05e50_callers.txt and docs/data/live/l8b_texcreate_record.txt (done below).

### Capture mc_root_4e05e50_callers.txt — sub_1289440 calls sub_4e05e50, ret=0x1289496 [V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| capture header | docs/data/live/mc_root_4e05e50_callers.txt | - | - | `CALLER ret=0x1289496 first_hit=1` (150 hits / 32 samples; every sample ret=0x1289496) | sub_4e05e50 is entered only from one return address: 0x1289496, i.e. the instruction right after sub_1289440's call site at 0x1289490 | [V live] |
| RCX sample hit=1 | 0x3908FFDE900 | - | [rcx+0x00]/[rcx+0x08]/[rcx+0x10] | capture RCX bytes: two pointer pairs, then zeros; later samples contain "tex"/"legs"/"_spear" location strings | RCX at sub_4e05e50 entry matches sdk TexturePtr layout (two shared_ptr members, sizeof 32) | [V live] + [V file read src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h] |

### The indirect-call machine: [0xF99FFA0] = sub_eea6040 = jmp rax [V dis]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline entry | 0xEEA6040 | - | - | `0xEEA6040  jmp rax` | [0xF99FFA0] resolves to sub_eea6040; `call qword ptr [0xF99FFA0]` pushes the return address then tail-jumps to rax (rdis data comment `[data_f99ffa0] = sub_eea6040` on every such call site) | [V] |

### sub_1289440 — the function containing 0x1289496, indirect caller of sub_4e05e50 — full decode [V dis]

rdis header: `sub_1289440  [0x1289440..0x128b440)  size 0x2000  0 xrefs in`. Entry `0x1289440  test eax,eax`.

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| entry test | 0x1289440 | 4 | - | `0x1289440  test eax,eax` | function entry; eax==0 skips the increment | [V] |
| skip branch | 0x1289442 | - | - | `0x1289442  je short 0x1289470` | jump when nothing to add_ref | [V] |
| increment value | 0x1289444 | 4 | - | `0x1289444  lea edx,[rax+1]` | new count = old+1 | [V] |
| atomic add_ref | 0x1289447 | 4 | [rcx+8] | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment at [rcx+8] | [V] |
| cmpxchg retry | 0x128944c | - | - | `0x128944c  jne short 0x1289440` | cmpxchg failed, reload and retry | [V] |
| copy 16 bytes | 0x128944e | 16 | [r13] | `0x128944e  movups xmm0,[r13]` | copy 16 bytes at [r13] | [V] |
| load pointer | 0x1289453 | 8 | [r13] | `0x1289453  mov rax,[r13]` | pointer from [r13] | [V] |
| spill copy | 0x1289457 | 16 | [rbp-0x50] | `0x1289457  movaps [rbp-0x50],xmm0` | spill the 16-byte copy | [V] |
| null test | 0x128945b | 4 | - | `0x128945b  test rax,rax` | [r13] pointer null? | [V] |
| invoke branch | 0x128945e | - | - | `0x128945e  jne short 0x128947d` | non-null: take the virtual-call path | [V] |
| null exit | 0x1289460 | - | - | `0x1289460  jmp 0x1289508` | null: done | [V] |
| reload spill | 0x1289470 | 8 | [rbp-0x50] | `0x1289470  mov rax,[rbp-0x50]` | reload spilled pointer (skip path) | [V] |
| null test 2 | 0x1289474 | 4 | - | `0x1289474  test rax,rax` | null? | [V] |
| null exit 2 | 0x1289477 | - | - | `0x1289477  je 0x1289508` | null: done | [V] |
| object load | 0x128947d | 8 | [r13+0x10] | `0x128947d  mov rcx,[r13+0x10]` | object pointer = this for the virtual call | [V] |
| object null test | 0x1289481 | 4 | - | `0x1289481  test rcx,rcx` | object pointer null? | [V] |
| object null exit | 0x1289484 | - | - | `0x1289484  je short 0x1289505` | null: skip call | [V] |
| vptr load | 0x1289486 | 8 | [rcx] | `0x1289486  mov rax,[rcx]` | rax = object vptr | [V] |
| vptr+8 load | 0x1289489 | 8 | [rax+8] | `0x1289489  mov rax,[rax+8]` | rax = vtable slot 1 = call target; at capture time = 0x4e05e50 | [V] + [? runtime bind] |
| second arg | 0x128948d | 8 | - | `0x128948d  mov rdx,rbx` | rdx = rbx passed as the invoke argument | [V] |
| indirect tail-call | 0x1289490 | - | - | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline sub_eea6040 `jmp rax`: tail-calls rax; pushed return address = 0x1289496 | [V] + [V live ret=0x1289496] |
| return site | 0x1289496 | - | - | `0x1289496  nop` | return address observed in the live capture, all 32 samples | [V live] |
| detach reload | 0x1289497 | 8 | [r13+0x10] | `0x1289497  mov rcx,[r13+0x10]` | reload object pointer after the invoke | [V] |
| detach null-out | 0x128949b | 8 | [r13+0x10] | `0x128949b  mov qword ptr [r13+0x10],0` | null the object slot | [V] |
| detach null test | 0x12894a3 | 4 | - | `0x12894a3  test rcx,rcx` | object was null? | [V] |
| detach skip | 0x12894a6 | - | - | `0x12894a6  je short 0x12894B9` | skip release | [V] |
| release vptr load | 0x12894a8 | 8 | [rcx] | `0x12894a8  mov rax,[rcx]` | rax = object vptr | [V] |
| release slot 0 load | 0x12894ab | 8 | [rax] | `0x12894ab  mov rax,[rax]` | rax = vtable slot 0 = destructor/release | [V] |
| release flag | 0x12894ae | 4 | - | `0x12894ae  mov edx,1` | edx = 1 (release/dealloc flag) | [V] |
| release tail-call | 0x12894b3 | - | - | `0x12894b3  call qword ptr [0xF99FFA0]` | release the object through the same trampoline | [V] |
| epilogue load | 0x12894b9 | 8 | [rbp-0x20] | `0x12894b9  mov rax,[rbp-0x20]` | epilogue list handling | [V] |
| epilogue test | 0x12894bd | 4 | - | `0x12894bd  test rax,rax` | null? | [V] |
| epilogue skip | 0x12894c0 | - | - | `0x12894c0  je short 0x1289505` | skip | [V] |
| epilogue cursor | 0x12894c2 | 8 | [rbp-0x38] | `0x12894c2  mov rdx,[rbp-0x38]` | list cursor | [V] |
| epilogue cmp | 0x12894c6 | 8 | [rbp-0x30] | `0x12894c6  cmp rdx,[rbp-0x30]` | end of list? | [V] |
| epilogue skip2 | 0x12894ca | - | - | `0x12894ca  je short 0x12894DE` | done | [V] |
| epilogue clear | 0x12894cc | 8 | [rbp-0x20] | `0x12894cc  mov qword ptr [rbp-0x20],0` | clear saved pointer | [V] |
| epilogue store | 0x12894d4 | 8 | [rdx] | `0x12894d4  mov [rdx],rax` | store into list slot | [V] |
| epilogue advance | 0x12894d7 | 8 | [rbp-0x38] | `0x12894d7  add qword ptr [rbp-0x38],8` | advance cursor by 8 | [V] |

Semantics: sub_1289440(rcx, rax=old count, r13, rbx) add_refs [rcx+8], copies 16 bytes at [r13], then if the object at [r13+0x10] is non-null it tail-calls the object's vtable slot 1 through trampoline [0xF99FFA0] (sub_eea6040 = `jmp rax`), detaches [r13+0x10] and releases via vtable slot 0. It is exactly the "invoke one virtual method on a refcounted object" helper — the object's vptr+8 resolves to sub_4e05e50 at runtime.

### Negative static evidence: sub_1289440 has no static caller; sub_4e05e50 has no static caller [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| xrefs to sub_1289440 | - | - | - | `sub_1289440  [0x1289440..0x128b440)  size 0x2000  0 xrefs in` (rdis fn header) | zero static callers of the indirect caller of sub_4e05e50 | [V] |
| imm refs to sub_1289440 | - | - | - | `rdis imm 0x1289440` -> `-- 0 hit(s)` | the address 0x1289440 never appears as an immediate anywhere in code | [V] |
| imm refs to sub_4e05e50 | - | - | - | `rdis imm 0x4E05E50` -> `-- 0 hit(s)` | the address 0x4e05e50 never appears as an immediate anywhere in code | [V] |
| ripscan for sub_1289440 | 0x12893b4 (func 0x1288c40) | - | - | ripscan reports one hit at 0x12893b4 inside the 0x1289200 release-loop region; inspection of that region shows movups/lock-dec/virtual-call loop code only, no operand referencing 0x1289440 | the single ripscan hit is not a usable static reference to sub_1289440 | [?] |
| xrefs to sub_4e05e50 | - | - | - | `sub_4e05e50  [0x4e05e50..0x4e07e50)  size 0x2000  0 xrefs in` (rdis fn header) | zero static callers of sub_4e05e50 | [V] |
| texgroup_load static end | 0x18718d0 | - | - | xref.py callers 0x18718D0 lists caller 0x5421c90 size 0x190f | texgroup_load's static chain ends at the cache 0x18718d0, whose decoded miss path (vtable 0xEFCA680 object + completion 0x186dac0) never calls sub_4e05e50 or sub_1289440 | [V] + [V r3, not redone] |

Conclusion of static evidence: there is NO static path texgroup_load(0x5421c90) -> sub_4e05e50 -> sub_1289440. Both endpoints have 0 static xrefs and 0 imm refs; sub_1289440 has 0 static callers; the only hit (ripscan 0x12893b4) is invalid. The bind exists only at runtime.

### sub_4e05e50 — MC-side texture creation entry, TexturePtr* in RCX — full decode [V dis + V live]

rdis header: `sub_4e05e50  [0x4e05e50..0x4e07e50)  size 0x2000  0 xrefs in`. Entry `0x4E05E50  push rbp`. Live capture: all 32 samples enter with RCX = a TexturePtr* (see capture row above) and return address ret=0x1289496.

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| 0x4E05E50 | 0x4E05E50 | 8 | - | `0x4E05E50  push rbp` | function prologue | [V] |
| 0x4E05E6E | 0x4E05E6E | 8 | - | `0x4E05E6E  mov rdi,rcx` | rdi = TexturePtr* | [V] |
| TexturePtr+0x18 read | 0x4E05E71 | 8 | [rcx+0x18] | `0x4E05E71  mov rax,[rcx+0x18]` | field read | [V] |
| null branch | 0x4E05E78 | - | - | `0x4E05E78  je short 0x4E05E8C` | skip if null | [V] |
| inner load | 0x4E05E82 | 8 | [rax+0x10] | `0x4E05E82  mov rax,[rax+0x10]` | *(a0+0x18)+0x10 | [V] |
| inner tail-call | 0x4E05E86 | - | - | `0x4E05E86  call qword ptr [0xF99FFA0]` | trampoline tail-call with rcx=[rdi+0x18], rdx=[rdi+0x58] | [V] |
| TexturePtr+0x10 read | 0x4E05E8C | 8 | [rdi+0x10] | `0x4E05E8C  mov rdx,[rdi+0x10]` | shared_ptr member read | [V] |
| refcount test | 0x4E05E90 | 4 | - | `0x4E05E90  test rdx,rdx` | null? | [V] |
| refcount load | 0x4E05E95 | 4 | [rdx+8] | `0x4E05E95  mov eax,[rdx+8]` | load use count | [V] |
| refcount CAS | 0x4E05EA8 | 4 | [rdx+8] | `0x4E05EA8  lock cmpxchg [rdx+8],r8d` | atomic use-count increment (loop at 0x4E05EA0) | [V] |
| acquire members | 0x4E05EB0 | 8 | [rdi+8] | `0x4E05EB0  mov rcx,[rdi+8]` / `0x4E05EB4  mov rbx,[rdi+0x10]` | grab the two shared_ptr members | [V] |
| release branch | 0x4E05EBD | 4 | [rbx+8] | `0x4E05EBD  lock inc dword ptr [rbx+8]` | temporary inc | [V] |
| save members | 0x4E05EC1 | 8 | [rbp+0x40] | `0x4E05EC1  mov [rbp+0x40],rcx` / `0x4E05EC5  mov [rbp+0x48],rbx` | spill members | [V] |
| release dec | 0x4E05EC9 | 4 | [rbx+8] | `0x4E05EC9  lock dec dword ptr [rbx+8]` | | [V] |
| destructor path | 0x4E05ECF | 8 | [rbx] | `0x4E05ECF  mov rax,[rbx]` / `0x4E05ED2  mov rax,[rax]` / `0x4E05ED8  call qword ptr [0xF99FFA0]` | release via vtable slot 0 through trampoline | [V] |
| second release path | 0x4E05F04 | 8 | [rdi+0x10] | `0x4E05F04  mov rcx,[rdi+0x10]` ... `0x4E05F36  call qword ptr [0xF99FFA0]` / `0x4E05F42  mov rax,[rbx]` / `0x4E05F45  mov rax,[rax+8]` / `0x4E05F4C  call qword ptr [0xF99FFA0]` | shared_ptr release of the members | [V] |
| 0x4E05F61 | 0x4E05F61 | 8 | [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | renderer-context pointer loaded into R9 | [V] + [? role beyond 32-byte TexturePtr stub header] |
| texture object | 0x4E05F68 | 8 | - | `0x4E05F68  add rdi,0x58` | texture object pointer = TexturePtr+0x58 | [V] |
| call create helper | 0x4E05F74 | 8 | - | `0x4E05F74  mov rcx,rdi` / `0x4E05F77  call 0xBC41420` | pass texture object to sub_bc41420 | [V] |
| 0x4E05F7C | 0x4E05F7C | - | - | `0x4E05F7C  nop` | return address observed live as ret=0x4E05F7C | [V live] |
| result processing | 0x4E05F7D | 8 | [rbp-8] | `0x4E05F7D  lea rcx,[rbp-8]` / `0x4E05F81  lea rdx,[rbp-0x50]` / `0x4E05F85  call 0x4E061B0` | results handed to sub_4e061b0 | [V] |

Note on TexturePtr size: sdk header src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h declares two shared_ptr members and `static_assert(sizeof(TexturePtr) == 32)` [V file read]. The capture RCX dumps show exactly two pointer pairs at +0x00/+0x08/+0x10 (+0x18 null in samples) and location-name strings ("tex", "legs", "_spear") in the object [V live]. sub_4e05e50 additionally reads [rdi+0xE0] and addresses an object at +0x58, which lie beyond the 32-byte stub header; their meaning is not shown by any instruction or string [?].

### Handle trace into TexturePtr/ClientTexture [V dis + V live + V file read]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| wrapper returns handle | 0xC296E1A | 2 | - | `0xC296E1A  call 0xBC74120` | wrapper 0xbc74120 returns the 16-bit texture handle in ax (inside dragon entry 0xc296b50, called from sub_bc41420 at 0xBC41B39) | [V] |
| invalid handle | 0xC296E22 | 2 | - | `0xC296E22  mov ax,0xFFFF` | 0xFFFF = invalid handle fallback | [V] |
| handle store | 0xC296E26 | 2 | [rdi+0x00] | `0xC296E26  mov [rdi],ax` | 16-bit handle stored at texture object +0x00 | [V] |
| rest of result | 0xC296E32 | 16 | [rdi+0x08] | `0xC296E32  movups [rdi+8],xmm0` | 16 result bytes at texture object +0x08 | [V] |
| texture object base | 0xC296E2D | 16 | [r12] | `0xC296E2D  movups xmm0,[r12]` | source of the 16 result bytes | [V] |
| texture object = TexturePtr+0x58 | 0x4E05F68 | 8 | - | `0x4E05F68  add rdi,0x58` | the handle lands in the TexturePtr's embedded texture object | [V] |
| sdk TexturePtr | src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h | 32 | - | `static_assert(sizeof(TexturePtr) == 32)` / `mClientTexture` +0x00 / `mResourceLocationPtr` +0x10 (two shared_ptr) | sdk header | [V file read] |
| sdk ClientTexture | src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h | - | - | `struct ClientTexture {}` | empty carrier struct | [V file read] |
| sdk BedrockTexture | src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h | 48 | - | `static_assert(sizeof(BedrockTexture) == 48)` | sdk header | [V file read] |

### Dispatcher consumption of command byte 14 and createTexture issuance [V dis + V live] (recap, not redone)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| 0xBC6A28F | 0xBC6A28F | 8 | [rdi+0x1EBF2D0] | `0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` / `0xBC6A2AE  mov rax,[rcx]` | renderer context and its vptr | [V] |
| vtable slot 26 load | 0xBC6A2B1 | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | slot 26 (0xD0/8) = createTexture address; BGFX_MAP 403: slot 26 = 0xe8143c0 | [V] + [V BGFX_MAP] |
| command fields | 0xBC6A296/0xBC6A2A4/0xBC6A2A9/0xBC6A29C | 1/8/2/4 | [rsp+0x6A]/[rsp+0x60]/[rsp+0x6E]/[rsp+0x90] | `0xBC6A296  movzx r10d,byte ptr [rsp+0x6A]` / `0xBC6A2A4  mov r8,[rsp+0x60]` / `0xBC6A2A9  movzx edx,word ptr [rsp+0x6E]` / `0xBC6A29C  mov r9d,[rsp+0x90]` | descriptor fields consumed from the command buffer (command 0x0E) | [V] + [I role] |
| vcall createTexture | 0xBC6A2C2 | - | - | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call; rax = [vptr+0xD0] = createTexture 0xe8143c0 | [V] + [V live ret=0xBC6A2C8] |
| 0xBC6A2C8 | 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | handle/result tested; return site of the live createTexture caller | [V] |

### l8b_texcreate_record.txt — createTexture -> TextureD3D12::create 0xe81bf30 [V live + V dis]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| create call | 0xE81455B | - | - | `0xE81455B  call 0xE81BF30` | call site just before ret=0xE814560; TextureD3D12::create fills the record (record +0x98 flags, +0x9C/+0xA0 w/h, +0xA4 depth, +0xA8 layers, +0xAE type, +0xAF/+0xB0 format, +0x00..+0x1F block, resource pointer first) | [V live + dis] |
| live texture names | R8 samples | - | - | "Texture: 2815", "Texture: 2799" (UTF-16) at R8 | default debug names in the record | [V live] |

### Full live chain [V live] (MC side, not redone, recapitulated from the capture logs)

| name | source | ret= | meaning | tag |
|---|---|---|---|---|
| sub_4e05e50 caller | docs/data/live/mc_root_4e05e50_callers.txt | 0x1289496 | sub_1289440 calls sub_4e05e50; all 32 samples | [V live] |
| sub_bc41420 caller | docs/data/live/dragon_texture_caller_bc41420.txt | 0x4E05F7C | sub_4e05e50 calls sub_bc41420 (return site 0x4E05F7C nop) | [V live] |
| dragon entry caller | docs/data/live/dragon_texture_entry_c296b50.txt | 0xBC41B3E | sub_bc41420 calls 0xc296b50 | [V live] |
| wrapper caller | docs/data/live/bgfx_texture_wrapper_bc73bf0.txt | 0xC296D7E | 0xc296b50 calls 0xbc73bf0 | [V live] |
| createTexture caller | docs/data/live/createtexture_callers.txt | 0xBC6A2C8 | dispatcher case 0xBC6A2C2 vcall [vptr+0xD0] -> createTexture 0xe8143c0 | [V live] |

Chain (MC end proven [V live]): MC object (vptr+8 = sub_4e05e50 at runtime) -> sub_1289440 (tail-call via trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`, return address 0x1289496) -> sub_4e05e50 (TexturePtr*; `0x4E05F77  call 0xBC41420`, return site `0x4E05F7C  nop`) -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (writes command byte 0x0E [V r4]) -> bgfx command-buffer dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> tail-call `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (record fill, ret 0xe814560) [V live + dis]. Returned handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V dis]; texture_obj = TexturePtr+0x58 [V]; sdk TexturePtr/ClientTexture [V file read].

## What I tried that failed (new angles, do not redo)

- xref.py callers 0xe8143c0 (createTexture slot 26): EMPTY — no static caller, only indirect [vptr+0xD0] thunks (r2; not redone).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY for both; never called by texgroup_load; item-line sub-chain not statically supported (r3; not redone).
- xref.py callers 0x4E05E50 / 0x1289440: no output (0 static callers, verified by rdis fn headers this session). rdis imm 0x4E05E50 / imm 0x1289440: 0 hits each — neither address appears as an immediate anywhere in code (this session).
- ripscan 0x1289440: one reported hit at 0x12893b4 inside func 0x1288c40, but that region shows no operand referencing 0x1289440; no usable static reference [?].
- 0x18718d0 cache path (texgroup_load's direct callee): fully decoded [V pre/0x18718d0_fn.md]; miss path builds vtable-0xEFCA680 object and calls 0x186dac0, never sub_4e05e50 or sub_1289440 [V]. Not the route to sub_4e05e50.
- Hint's conditional path (wrapper from texture-object init via vtable 0xEFCA580 slot 4): wrappers reached only from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V r4 xref evidence]; not statically reachable from MC texture code; stopped per hint.

## CAPTURE REQUESTED

sub_1289440_callers | request.py add sub_1289440_callers 0x1289440 --size 0x100 --max 8 | queued (tool returned "queued"; result will appear in docs/data/live/sub_1289440_callers.txt). Purpose: name sub_1289440's runtime caller(s) — the ret=0x1289496 indirect caller of sub_4e05e50 — and connect it to texgroup_load 0x5421c90 / texload 0x58a1310. Static xrefs and imm refs to sub_1289440 are both 0, so this capture is the only remaining angle for the texgroup_load connection.

## Interpretation

The createTexture issuance from Minecraft-side code IS proven [V]:
- Producer of command byte 14: sub_0xbc73770 [V r4], via thin wrappers (0xbc74120 returns the handle in ax at 0xc296e1a).
- Dispatcher consumer: case 0xBC6A2C2 loads vtable slot 26 (`0xBC6A2B1  mov rax,[rax+0xD0]`; BGFX_MAP 403: slot 26 = 0xe8143c0 createTexture) and tail-calls it `0xBC6A2C2  call qword ptr [0xF99FFA0]`; return site 0xBC6A2C8 = live caller of createTexture [V live].
- MC entry sub_4e05e50(TexturePtr* in RCX) [V dis + V live capture layout match] reads [rcx+0x18]/[rdi+0x10]/[rdi+0xE0], computes texture object TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`), passes it to sub_bc41420 (`0x4E05F77  call 0xBC41420`; return site `0x4E05F7C  nop` = live ret=0x4E05F7C) and reaches createTexture through the full live chain above.
- Returned handle stored [texture_obj+0x00] at `0xC296E26  mov [rdi],ax` (size 2, word) [V dis] with texture_obj = TexturePtr+0x58 [V]; TexturePtr/ClientTexture/BedrockTexture per sdk headers [V file read].

Residual (the single blocking fact, documented above): no static path texgroup_load(0x5421c90) -> sub_4e05e50 exists — 0 xrefs and 0 imm refs on both ends, sub_1289440 has 0 static callers, the bind is a runtime vptr+8 resolution tail-called through trampoline [0xF99FFA0] = sub_eea6040 (`jmp rax`), observed live [V live]. Capture sub_1289440_callers is queued to name sub_1289440's runtime caller; if that caller is in the texgroup_load/texload domain, this item closes YES. Atlas stitchers remain open under L8a/L8b (parked in MIRROR_SKIP) and are not part of this unit's close.

## CLOSES?

NO — not every pending part of the item line is proven by [V] rows. Proven [V]: sampler flag decode + cache (6ax); D3D12 backend texture-management chain; command-byte-14 producer sub_0xbc73770; dispatcher vcall [vptr+0xD0] -> createTexture 0xe8143c0 (`0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]`, ret site 0xBC6A2C8 [V live]); MC entry sub_4e05e50(TexturePtr*) invoked live via sub_1289440 tail-call (ret=0x1289496, all 32 samples); full live chain to createTexture and TextureD3D12::create (`0xE81455B  call 0xE81BF30`, ret 0xe814560); returned handle stored [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V] with texture_obj = TexturePtr+0x58 [V], sdk TexturePtr/ClientTexture [V file read]. Single blocking fact: the static bind texgroup_load(0x5421c90) -> sub_4e05e50 -> sub_1289440 does not exist statically (xref.py callers empty for both 0x4e05e50 and 0x1289440; rdis imm 0 hits; ripscan hit invalid; texgroup_load's static chain ends at cache 0x18718d0 which never calls sub_4e05e50). The bind is runtime-only (object vptr+8 = sub_4e05e50, tail-call trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`) and is observed live [V live]. Capture sub_1289440_callers is queued to name sub_1289440's runtime caller — if it lands in the texgroup_load/texload domain, flip to YES.

## TOOL REQUESTS

- sub_1289440 capture | python tools/livecap/request.py add sub_1289440_callers 0x1289440 --size 0x100 --max 8 --why "..." | queued; result -> docs/data/live/sub_1289440_callers.txt; needed to name sub_1289440's runtime caller and close the texgroup_load/texload connection (static analysis exhausted: 0 xrefs, 0 imm refs, invalid ripscan hit).
- No helper scripts written; all instruction lines re-verified verbatim against fresh rdis dis this session; live capture logs are read-only inputs; xref.py/ripscan.py/rdis imm used for negative findings.
