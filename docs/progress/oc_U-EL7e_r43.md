## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] (texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750); Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r41; not re-decoded, not re-quoted this session)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts (flag layout); called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP 6z/6z-2/6aj confirm base/stride and live texture records); createTexture 0xe8143c0 (vtable slot 26), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750.
- createTexture issuance below sub_4e05e50 [V dis + V live]: sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> command-byte-0x0E producer 0xbc73770 [V r4] -> bgfx dispatcher (renderer-context vptr[slot 26] = 0xe8143c0 [I BGFX_MAP]) -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30 (ret site 0xE814560 [V live docs/data/live/l8b_texcreate_record.txt]); returned 16-bit handle stored at texture_obj+0x00 [V]; sdk TexturePtr (32B: mClientTexture +0x00, mResourceLocationPtr +0x10 [V file read]) / ClientTexture headers.

## This session — new angle on the single blocking fact

Blocking fact carried from r1-r41: no static path texgroup_load(0x5421c90) -> sub_4e05e50 exists; sub_4e05e50 (entry 0x4E05E50) has 0 static callers and is entered only at runtime via sub_12893d0's indirect vtable[1] tail-call through trampoline [0xF99FFA0] = sub_eea6040 (`0xEEA6040  jmp rax`).

New angle tried this session: fully decode sub_12893d0 (the function containing ret site 0x1289496) and check every static caller of it, to see whether the job list it walks — or the vtable-0xF215838 job objects whose vptr[1] IS sub_4e05e50 — is populated from texgroup_load's static chain (texgroup_load -> texload 0x58a1310 -> texload_task 0x541bf00; texload_task's static chain ends at a call to 0x18718D0, cache object vtable 0xEFCA680 != the job-object vtable 0xF215838 [V r24]).

Result: sub_12893d0 walks an entry list ([obj+0x0]..[obj+0x8], stride 0x18); per entry it acquires the refcount at [[entry+0x8]+8] (lock cmpxchg), then tail-calls [entry+0x10]->vptr[1] through the [0xF99FFA0] trampoline (ret site 0x1289496). Its complete static caller set is {0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0}; all four upward chains dead-end at functions with 0 static callers (or are internal-only, sub_66232b0), and none is reachable from texgroup_load/texload/texload_task. The vtable-0xF215838 job objects are constructed by sub_4e05450 (16 static callers, none texgroup_load/texload/texload_task). The new angle therefore CONFIRMS the blocker but does not close it: the texgroup_load -> sub_4e05e50 bind is runtime-only (vtable dispatch), and static analysis is exhausted.

### Field map — sub_12893d0 dispatch (function containing ret site 0x1289496). Every line re-disassembled and matched verbatim this session (`rdis dis 0x12893d0 220`).

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| list-walk start cursor | [obj+0x0] | 8 | R: `0x1289406  mov r13,[rcx]` | r13 = [obj+0x0], walk cursor start of the entry list | [V] |
| list-walk end cursor | [obj+0x8] | 8 | R: `0x1289409  mov r14,[rcx+8]` | r14 = [obj+0x8], walk cursor end | [V] |
| entry refcount object | [entry+0x8] | 8 | R: `0x1289431  mov rcx,[r13+8]` / `0x1289447  lock cmpxchg [rcx+8],edx` | entry+0x8 = ptr to refcounted object; [rcx+8] refcount acquired (cmpxchg eax->eax+1) | [V] |
| target job object vptr[1] | [entry+0x10] | 8 | R: `0x128947d  mov rcx,[r13+0x10]` / `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` | entry+0x10 = target job object; rax = obj->vptr[1] = sub_4e05e50 at runtime | [V] [V live] |
| trampoline tail-call | [0xF99FFA0] | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call of vptr[n] (MC root: vptr[1]=sub_4e05e50; dispatcher: vptr[26]=createTexture); slot content = sub_eea6040 (PE read-only initializer, .text store scan 0 hits -> no code writer); callee held in RAX per call site; ret sites 0x1289496 / 0xBC6A2C8 | [V] [I] |
| indirect-call ret site (MC root) | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after `call [0xF99FFA0]`; = capture CALLER ret=0x1289496, all 32 samples (docs/data/live/mc_root_4e05e50_callers.txt:3) | [V live] |
| trampoline body | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax (the real indirect target) | [V] |

### Field map — createTexture issuance chain and handle store. Every line re-disassembled and matched verbatim this session.

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| object+0xE0 read (renderer ctx) | [obj+0xE0] | 8 | R: `0x4E05F61  mov r9,[rdi+0xE0]` | sub_4e05e50 reads object+0xE0 into r9 (renderer context) | [V] |
| texture object = arg+0x58 | arg+0x58 | 8 | - | `0x4E05F68  add rdi,0x58` | rdi = sub_4e05e50 arg (RCX) + 0x58 = texture object passed to sub_bc41420 | [V] |
| sub_4e05e50 -> sub_bc41420 | 0x4E05F77 | 5 | S: `0x4E05F77  call 0xBC41420` | sub_4e05e50 issues the dragon-layer create (rcx = texture_obj) | [V] |
| dragon create ret site | 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | ret site after `call 0xBC41420`; = capture CALLER ret=0x4E05F7C (docs/data/live/dragon_texture_caller_bc41420.txt:3) | [V] [V live] |
| handle store into texture object | [texture_obj+0x0] | 2 | W: `0xC296E26  mov [rdi],ax` / `0xC296E1A  call 0xBC74120` (ax) / `0xC296E22  mov ax,0xFFFF` (invalid-handle fallback) | 16-bit bgfx texture handle stored at texture_obj+0x00; rdi = texture_obj = arg+0x58 | [V] |
| renderer ctx vptr[slot 26] | [renderer_ctx vptr+0xD0] | 8 | R: `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = renderer-context vptr[slot 26] = createTexture 0xe8143c0 (BGFX_MAP.md line 403/541: slot 26 = 0xe8143c0 createTexture) | [V] [I] |
| dispatcher tail-call ret site | 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | ret site after `call [0xF99FFA0]`; = capture CALLER ret=0xBC6A2C8 (docs/data/live/createtexture_callers.txt:3) | [V] [V live] |
| createTexture -> TextureD3D12::create | 0xE81455B | 5 | S: `0xE81455B  call 0xE81BF30` | backend record fill (TextureD3D12::create) | [V] |
| backend create ret site | 0xE814560 | 1 | - | `0xE814560  nop` | ret site after `call 0xE81BF30`; = capture CALLER ret=0xE814560 (docs/data/live/l8b_texcreate_record.txt:3) | [V] [V live] |

### Static caller set (negative findings)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 callers | sub_4e05e50 callers | - | - | `xref.py callers 0x4E05E50` -> 0 calling functions | sub_4e05e50 has no static caller at all | [V] |
| sub_12893d0 callers | sub_12893d0 callers | - | - | `xref.py callers 0x12893d0` -> 0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0 | complete static caller set of the dispatch | [V] |
| endFrame drain call site | 0x6632c55 | 5 | S: `0x6632c55  call 0x12893D0` | sub_6632bf0 (RCX = [rbp-0x30]) -> sub_12893d0 -> sub_4e05e50 | [V] |
| object-buffer drain call site | 0x6622662 | 5 | S: `0x6622662  call 0x12893D0` | sub_6622610 (RCX = [rbp-0x40]) -> sub_12893d0 -> sub_4e05e50 | [V] |

Verified call sites (`rdis dis 0x6632c40 40`, `rdis dis 0x6622650 40`): both `call 0x12893D0` sites pass a locally-built object in RCX ([rbp-0x30] / [rbp-0x40]), not a texgroup_load texture object; sub_6632bf0 also references the "Deferred Buffer Transactions" string at 0x6632c43. None of the four callers or their callers connects to texgroup_load(0x5421c90)/texload(0x58a1310)/texload_task(0x541bf00).

## CLOSES?

NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. sub_4e05e50 (0x4E05E50) has 0 static xrefs (`xref.py callers 0x4E05E50` -> none) and is entered only at runtime via sub_12893d0's vtable[1] tail-call (`0x1289489  mov rax,[rax+8]` then `0x1289490  call qword ptr [0xF99FFA0]`) through trampoline [0xF99FFA0] = sub_eea6040 (`0xEEA6040  jmp rax`, read-only PE initializer, no code writer; the callee sub_4e05e50 is held in RAX = obj->vptr[1] at the call site). sub_12893d0's static callers (0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0) are not reachable from texgroup_load/texload/texload_task (texgroup_load's static chain ends at a call to 0x18718D0, cache object vtable 0xEFCA680 != the job-object vtable 0xF215838 whose slot 1 is sub_4e05e50). Everything else in L7e IS proven: sampler flag decode + cache (6ax) [V]; D3D12 backend texture-management chain [V]; createTexture issuance via bgfx command byte 14 (producer sub_bc73770 -> dispatcher slot 26 = 0xe8143c0 -> TextureD3D12::create) [V dis] + [V live]; returned handle stored at texture_obj+0x00 (`0xC296E26  mov [rdi],ax`, size 2) [V]; texture_obj = arg+0x58 (`0x4E05F68  add rdi,0x58`) [V]; sdk TexturePtr/ClientTexture headers [V file read]. MC-side root sub_4e05e50 and TextureD3D12::create are both entered live ([V live] captures cited above). Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP). Static analysis for the texgroup_load -> sub_4e05e50 bind is exhausted.

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0 no-such-instr=0 required (all quoted `0xRVA  instr` lines re-verified verbatim against fresh rdis dis this session).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; then set line 2 after `## NEXT` to DONE.

## TOOL REQUESTS

- None (no helper scripts written, no temporary files left behind; all instruction lines re-verified with rdis.exe this session; live capture logs are read-only inputs read first-hand).
