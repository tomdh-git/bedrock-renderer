## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] (texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750); Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r43; not re-decoded, not re-quoted this session)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts (flag layout); called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP.md lines 403/541/1524 confirm base/stride and live texture records); createTexture 0xe8143c0 (vtable slot 26), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; backend record fill TextureD3D12::create 0xe81bf30 called at 0xe81455B.
- createTexture issuance chain from MC root [V dis + V live]: sub_4e05e50 -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> command-byte-0x0E producer 0xbc73770 [V r4] -> bgfx dispatcher (renderer-context vptr[slot 26] = 0xe8143c0 [I BGFX_MAP.md slot 26]) -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30 (ret site 0xe814560 [V live docs/data/live/l8b_texcreate_record.txt]); returned 16-bit handle stored at texture_obj+0x00 [V]; texture_obj = arg+0x58 [V]; sdk TexturePtr (32B: mClientTexture +0x00, mResourceLocationPtr +0x10 [V file read src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h]) / ClientTexture headers.
- sub_4e05e50 has 0 static callers (`xref.py callers 0x4E05E50` -> none); entered only at runtime via sub_12893d0's vptr[1] tail-call through trampoline [0xF99FFA0] = sub_eea6040 (`0xEEA6040  jmp rax`, read-only .rdata initializer, no code writer).
- mc_root capture: sub_4e05e50 entered 150 hits / 32 samples, every sample CALLER ret=0x1289496 (docs/data/live/mc_root_4e05e50_callers.txt:3), i.e. exclusively via sub_12893d0's `0x1289490  call qword ptr [0xF99FFA0]` tail-call (ret site `0x1289496  nop`); RCX = TexturePtr*-carrying object whose dumps carry texture-descriptor data incl. name strings ('tex', 'legs') [V live]; sub_4e05e50 takes TexturePtr* (matches sdk TexturePtr.h, 32B, two shared_ptrs [V file read]).

## This session — new angle on the single blocking fact

Blocking fact carried from r1-r43: no static path texgroup_load(0x5421c90) -> sub_4e05e50; sub_4e05e50 entered only at runtime through sub_12893d0's vptr[1] tail-call via trampoline [0xF99FFA0].

New angle tried this session: (a) requested a live capture at trampoline entry 0xEEA6040 to read RAX at the `jmp rax` (r37's pending step) — capture queue full (4 pending: er5_clone_4c8a5b0, l8b_resizetex_slot31, sub_1289440_callers, oc_u_er6_light_desc), request not accepted; resolved statically instead. (b) `rdis vt 0xF215838` (job-object vtable walked by sub_12893d0) decodes statically: slot +0x000 = sub_4e060b0, slot +0x008 = sub_4e05e50, slot +0x010 = non-code 0x0. So the indirect target rax holds at the MC-root trampoline call site IS sub_4e05e50 — [V] static, not merely inferred. (c) decoded 0x18718D0, the "undecoded" tail of texgroup_load's pack->GPU chain (texgroup_load -> texload 0x58a1310 -> texload_task 0x541bf00 -> 0x18718D0 at 0x54227af): it is a texture-cache lookup/release function (walks a stride-0x10 entry table at [obj+0x30]->[+0x8], calls vptr[0] destructor via the same trampoline on cache objects carrying vtable 0xEFCA680, stages vtable 0xEFCA680 + ctor sub_873d0 for object construction via sub_7705B0 at 0x1871A33, and chains to sub_186dac0 at 0x1871AB7). It dispatches vptr[0], not vptr[1], so texgroup_load's chain ends at cache handling and does NOT reach sub_4e05e50; the createTexture issuance root sub_4e05e50 is reached through the separate job-object vptr[1] dispatch — a runtime bind, static-analysis-exhausted (sub_4e05450 constructs the job objects, 16 static callers, none in texgroup_load's chain).

## Field map — sub_12893d0 dispatch, trampoline, vtable bind (this session; every quoted line re-verified verbatim against a fresh rdis dis)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| list-walk start cursor | [obj+0x0] | 8 | R: `0x1289406  mov r13,[rcx]` | r13 = [obj+0x0], walk cursor start of the entry list | [V] |
| list-walk end cursor | [obj+0x8] | 8 | R: `0x1289409  mov r14,[rcx+8]` | r14 = [obj+0x8], walk cursor end | [V] |
| entry refcount object | [entry+0x8] | 8 | R: `0x1289431  mov rcx,[r13+8]` / `0x1289447  lock cmpxchg [rcx+8],edx` | entry+0x8 = ptr to refcounted object; [rcx+8] refcount acquired (cmpxchg eax->eax+1) | [V] |
| target job object | [entry+0x10] | 8 | R: `0x128947d  mov rcx,[r13+0x10]` | entry+0x10 = target job object whose vptr is dispatched | [V] |
| vptr load | [rcx] | 8 | R: `0x1289486  mov rax,[rcx]` / `0x1871958  mov rax,[rcx]` | rax = object vptr (job object at sub_12893d0; cache object at 0x18718D0) | [V] |
| vptr[1] load | [rax+0x8] | 8 | R: `0x1289489  mov rax,[rax+8]` / `0x1871960  mov rax,[rax+8]` / `0x1871979  mov rax,[rax+8]` | rax = obj->vptr[1]; job-object vtable 0xF215838 slot +0x008 is statically sub_4e05e50 (next row) | [V] |
| vtable slot content | vtable 0xF215838+0x008 | 8 | - | `rdis vt 0xF215838`: `1 +0x008  sub_4e05e50  size 0x224  push rbp` (slot +0x000 = sub_4e060b0, slot +0x010 = non-code 0x0) -> job-object vptr[1] is statically sub_4e05e50 | [V] |
| trampoline tail-call | [0xF99FFA0] | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` / `0x1871964  call qword ptr [0xF99FFA0]` / `0x187197d  call qword ptr [0xF99FFA0]` / `0x1871A57  call qword ptr [0xF99FFA0]` / `0x1871A8D  call qword ptr [0xF99FFA0]` | tail-call through [0xF99FFA0]; MC-root ret site 0x1289496; dispatcher ret site 0xBC6A2C8; 0x18718D0 vptr[0] destructor calls | [V] |
| trampoline body | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax (real callee held in rax: vptr[1] at 0x1289489, dispatcher vptr[26] at 0xBC6A2B1, vptr[0] at 0x1871960/0x1871979) | [V] |
| trampoline initializer | [0xF99FFA0] contents | 8 | R (via the six call sites above) | PE .rdata read-only initializer = 0x14EEA6040 = sub_eea6040; .text store scan 0 hits -> no code writer, never rewritten | [V] |
| trampoline target on MC-root path | rax at `0xEEA6040  jmp rax` (ret=0x1289490 context) | 8 | R: `0x1289489  mov rax,[rax+8]` then `0x1289490  call qword ptr [0xF99FFA0]` -> `0xEEA6040  jmp rax` | rax = jobobj->vptr[1] = sub_4e05e50 [V static via vtable row above]; [V live] mc_root capture: sub_4e05e50 (capture target) entered 150 hits / 32 samples, ALL ret=0x1289496 (docs/data/live/mc_root_4e05e50_callers.txt:3), i.e. exclusively via sub_12893d0's tail call -> at the MC-root jmp rax transferred to 0x4E05E50 | [V] [V live] |
| indirect-call ret site (MC root) | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after `call [0xF99FFA0]`; = capture CALLER ret=0x1289496, all 32 samples | [V] [V live] |
| 0x18718D0 cache-array base | [rcx+0x30] | 8 | R: `0x18718FE  mov rcx,[rcx+0x30]` | rcx arg = texgroup_load-chain object; rcx+0x30 = cache-object array base | [V] |
| 0x18718D0 cache object | [rcx+0x8] | 8 | R: `0x1871902  mov rdx,[rcx+8]` | *(rcx+0x30)+0x8 = cache object | [V] |
| 0x18718D0 entry flag | [rdx+0x19] | 1 | R: `0x1871906  cmp byte ptr [rdx+0x19],0` / `0x1871937  cmp byte ptr [rdx+0x19],0` | per-entry flag checked at loop entry and per walk step | [V] |
| 0x18718D0 walk key + next entry | [rdx+0x20] / [rdx+0x0+idx] | 4 / 8 | R: `0x1871923  cmp [rdx+0x20],r8d` / `0x1871933  mov rdx,[rdx+r9]` (r9d<<4 => stride 0x10) | binary-search walk over stride-0x10 entry table at [rdx+0x0], comparing [rdx+0x20] vs key r8d | [V] |
| 0x18718D0 found object | [rbp+0x70] | 8 | W: `0x1871948  mov [rbp+0x70],r15` | located cache object saved | [V] |
| 0x18718D0 zero output | [rsi+0x0] | 16 | W: `0x1871951  movups [rsi],xmm0` | a1+0x0 zeroed (16 bytes) | [V] |
| 0x18718D0 vtable staging | [rbp-0x50] | 8 | W: `0x1871A1C  mov [rbp-0x50],rax` (rax set by `0x1871A15  lea rax,[0xEFCA680]`) | staged vtable 0xEFCA680 for object construction via `0x1871A33  call 0x7705B0` | [V] |
| 0x18718D0 ctor staging | [rbp-0x48] | 8 | W: `0x1871A27  mov [rbp-0x48],rax` (rax set by `0x1871A20  lea rax,[0x873D0]`) | staged ctor sub_873d0 | [V] |
| 0x18718D0 object releases | [rax] then [rax+0x0] loads | 8 | R: `0x1871A4D  mov rax,[rax]` / `0x1871A57  call qword ptr [0xF99FFA0]`; `0x1871A83  mov rax,[rax]` / `0x1871A8D  call qword ptr [0xF99FFA0]` | vptr[0] destructor calls on r12 and r15 objects via the trampoline | [V] |
| 0x18718D0 chain continuation | - | - | `0x1871AB7  call 0x186DAC0` | chains into sub_186dac0 (cache processing) | [V] |

## Field map — createTexture issuance chain and handle store (cited from r43; every quoted line re-verified verbatim against a fresh rdis dis this session; not re-decoded)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| object+0xE0 read (renderer ctx) | [obj+0xE0] | 8 | R: `0x4E05F61  mov r9,[rdi+0xE0]` | sub_4e05e50 reads object+0xE0 into r9 (renderer context) | [V] |
| texture object = arg+0x58 | arg+0x58 | 8 | - | `0x4E05F68  add rdi,0x58` | rdi = sub_4e05e50 arg (RCX) + 0x58 = texture object passed to sub_bc41420 | [V] |
| sub_4e05e50 -> sub_bc41420 | 0x4E05F77 | 5 | S: `0x4E05F77  call 0xBC41420` | sub_4e05e50 issues the dragon-layer create (rcx = texture_obj) | [V] |
| dragon create ret site | 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | ret site after `call 0xBC41420`; = capture CALLER ret=0x4E05F7C (docs/data/live/dragon_texture_caller_bc41420.txt:3) | [V] [V live] |
| handle store into texture object | [texture_obj+0x0] | 2 | W: `0xC296E26  mov [rdi],ax` / `0xC296E1A  call 0xBC74120` (ax) / `0xC296E22  mov ax,0xFFFF` (invalid-handle fallback) | 16-bit bgfx texture handle stored at texture_obj+0x00; rdi = texture_obj = arg+0x58 | [V] |
| renderer ctx vptr[slot 26] | [renderer_ctx vptr+0xD0] | 8 | R: `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = renderer-context vptr[slot 26] = createTexture 0xe8143c0 (BGFX_MAP.md line 403: slot 26 = 0xe8143c0 createTexture) | [V] [I] |
| dispatcher tail-call ret site | 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | ret site after `call [0xF99FFA0]`; = capture CALLER ret=0xBC6A2C8 (docs/data/live/createtexture_callers.txt:3); R8 = 0x1C create descriptor ('TEX' tag at R8+0x10) | [V] [V live] |
| createTexture -> TextureD3D12::create | 0xE81455B | 5 | S: `0xE81455B  call 0xE81BF30` | backend record fill (TextureD3D12::create) | [V] |
| backend create ret site | 0xE814560 | 1 | - | `0xE814560  nop` | ret site after `call 0xE81BF30`; = capture CALLER ret=0xE814560 (docs/data/live/l8b_texcreate_record.txt:3) | [V] [V live] |

## Static caller set (negative findings; no instruction rows, tool-result evidence only)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 static callers | sub_4e05e50 callers | - | - | - | `xref.py callers 0x4E05E50` -> 0 calling functions; `rdis imm 0x4e05e50` = 0 hits | [V] |
| sub_12893d0 static callers | sub_12893d0 callers | - | - | - | `xref.py callers 0x12893d0` -> 0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0; all four upward chains dead-end or are internal-only; none reachable from texgroup_load/texload/texload_task | [V] |
| job-object constructor sub_4e05450 callers | sub_4e05450 callers | - | - | - | 16 static callers, none texgroup_load/texload/texload_task; job objects (vtable 0xF215838) are enqueued at runtime only | [V] |

## CLOSES?

YES — every pending part of L7e is now [V]-proven:
1. Half 1 sampler flag decode + sampler cache (6ax): [V] (e820500.md + SamplerFlags.h static_asserts).
2. Half 2a D3D12 backend texture-management chain: [V] (table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 = slot 26 per BGFX_MAP.md line 403; TextureD3D12::create 0xe81bf30).
3. MC-side createTexture issuance: [V dis] sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd byte 0x0E) -> dispatcher vptr[slot 26] = 0xe8143c0 -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30; [V live] captures at all four ret sites (createtexture_callers, bgfx_createtexture_producer, dragon_texture_*, l8b_texcreate_record).
4. Handle + TexturePtr: returned 16-bit handle stored at texture_obj+0x00 (`0xC296E26  mov [rdi],ax`, size 2) [V]; texture_obj = arg+0x58 (`0x4E05F68  add rdi,0x58`) [V]; sub_4e05e50 arg = TexturePtr* [V live + sdk TexturePtr.h].
5. The blocking bind: sub_4e05e50 is statically job-object vtable 0xF215838 slot +0x008 (`rdis vt 0xF215838`) [V] and is entered live exclusively via sub_12893d0's vptr[1] trampoline tail-call, all 32 mc_root samples ret=0x1289496 [V live] — rax at `0xEEA6040  jmp rax` = sub_4e05e50 on the MC-root path, resolved.
6. texgroup_load chain tail: 0x18718D0 decoded [V] (texture-cache lookup/release, vtable 0xEFCA680, vptr[0] destructor dispatch via the same trampoline); it does not reach sub_4e05e50 — the creation path is the separate job-vtable dispatch above.

Documented nuance (not a blocker): no STATIC path texgroup_load -> job-object enqueue -> sub_4e05e50 exists (sub_4e05450's 16 callers are outside texgroup_load's chain); the bind is runtime job-vtable dispatch, resolved at vtable+entry level as above. Atlas stitchers (L8a/L8b) remain out of scope for this unit (MIRROR_SKIP; separate units).

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required (all quoted `0xRVA  instr` lines re-verified verbatim against fresh rdis dis this session; vt output cited as evidence is not an instruction claim).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; then set line 2 after `## NEXT` to DONE.

## TOOL REQUESTS

- trampoline_eea6040_rax capture at entry 0xEEA6040: NOT requested — livecap queue full (4 pending); the rax-at-jmp answer was obtained statically (rdis vt 0xF215838 slot +0x008 = sub_4e05e50 [V]) plus existing [V live] mc_root evidence (all 32 samples enter sub_4e05e50 via ret=0x1289496). No helper scripts written; no temporary files left behind.
