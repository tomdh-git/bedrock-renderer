## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r50; not re-decoded, not re-quoted here)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP.md lines 403/541/1524 confirm base/stride and live texture records); createTexture 0xe8143c0 (renderer-context vtable slot 26, BGFX_MAP.md line 403 `| 26 | 0xe8143c0 | createTexture |`), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30 (call 0xe81455B, ret site 0xe814560).
- createTexture issuance below sub_4e05e50 [V dis + V live]: sub_4e05e50 -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> command-byte-0x0E producer 0xbc73770 [V r4] -> bgfx dispatcher (vptr[slot 26] = 0xe8143c0) -> createTexture 0xe8143c0; returned 16-bit handle stored at texture_obj+0x00 [V]; sdk TexturePtr/ClientTexture headers [V file read: TexturePtr 32B, mClientTexture+0x00, mResourceLocationPtr+0x10].
- bgfx dispatcher bytes 0xBC6A2AE/0xBC6A2B1/0xBC6A2C2/0xBC6A2C8 verified verbatim this session (see table); handle store 0xC296E1A/0xC296E22/0xC296E26 verified verbatim this session (see table).

## This session — verification + new angle on the single blocking fact

Blocking fact carried from r1-r49: no static path texgroup_load(0x5421c90)/texload(0x58a1310) -> sub_4e05e50 exists; sub_4e05e50 has 0 static callers and is entered only at runtime through an indirect vtable[1] tail-call via trampoline [0xF99FFA0] = sub_eea6040.

New angle tried this session (resolves the indirect TARGET, not the path):

1. `rdis vt 0xF215838` (job-object vtable walked by sub_12893d0): slot `+0x000 sub_4e060b0`, slot `+0x008 sub_4e05e50 size 0x224 push rbp`, slot `+0x010 non-code 0x0`. So rax = vptr[1] of a job object IS statically sub_4e05e50 — the indirect target at the `0xEEA6040  jmp rax` trampoline is resolved statically on this path, not merely inferred. [V]
2. Full decode of sub_12893d0 [0x12893d0..0x128b3d0), size 0x2000, 13 xrefs in — the function containing the mc_root ret site 0x1289496: it walks a refcounted entry list ([obj+0x0]..[obj+0x8], stride 0x18, lock cmpxchg refcount acquire at 0x1289447), takes entry+0x10 as the target job object, loads vptr[1] at 0x1289489 and tail-calls it through [0xF99FFA0] at 0x1289490 (ret site 0x1289496). Every quoted line re-verified verbatim against a fresh rdis dis this session (table below). Its complete static caller set is {0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0} (`xref.py callers 0x12893d0` — exactly 4, [V]); none of the four is texgroup_load/texload/texload_task and their upward chains dead-end (prior reviews r24/r43) — so no static route from texgroup_load's chain into sub_4e05e50.
3. texgroup_load's static chain tail verified: `0x54227AF  call 0x18718D0` (texload_task 0x541bf00 -> sub_18718d0) [V]. sub_18718d0 [0x18718d0..0x18738d0) is a texture-cache lookup/release function: cache-object array base [rcx+0x30] (0x18718FE), binary-search walk over a stride-0x10 entry table comparing key at entry+0x20 (0x1871923/0x1871933), per-entry flag at +0x19 (0x1871906/0x1871937), located object saved at [rbp+0x70] (0x1871948), 16-byte zero output (0x1871951 movups), staged cache vtable 0xEFCA680 (0x1871A15/0x1871A1C) != job vtable 0xF215838, cache-object constructor via 0x1871A33 call 0x7705B0, and vptr[0] destructor dispatch through the same trampoline (0x1871960/0x1871964, 0x1871a4d/0x1871a57). It dispatches vptr[0], never vptr[1], so it never reaches sub_4e05e50 — texgroup_load's static chain ends at cache handling and does not enter the sub_4e05e50 tree.
4. [0xF99FFA0]: rdis annotates every `call qword ptr [0xF99FFA0]` site as `[data_f99ffa0] = sub_eea6040`; sub_eea6040 = `0xEEA6040  jmp rax`; .rdata is read-only (section flags 0x40000040) and a .text store scan for [0xF99FFA0] (mov [rip+disp32], reg / imm32) = 0 hits — no code writer, never rewritten, set once by the loader as PE initializer 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040. [V]
5. `xref.py callers 0x4E05E50` -> EMPTY: sub_4e05e50 (0x4E05E50..0x4E06074 per vt size 0x224) has zero static callers [V].

What failed this session: none of the static angles produces a path texgroup_load -> sub_4e05e50. The [0xF99FFA0] writer scan (r37) = 0 hits (.rdata read-only); sub_4e05e50 has 0 static xrefs; sub_12893d0's 4 callers are outside texgroup_load's chain; texload_task ends at the 0xEFCA680 cache function (0x18718d0), not the 0xF215838 job vtable that carries sub_4e05e50 at slot 1. The bind texgroup_load -> sub_4e05e50 is runtime-only (job objects enqueued at runtime, e.g. via sub_4e05450 whose 16 callers are outside texgroup_load's chain [prior r22/r44]).

## Field map — sub_4e05e50 root, dispatch site, trampoline, texgroup_load chain end, issuance + handle store

Every quoted line re-verified verbatim against a fresh rdis dis this session; all sizes come from the instruction.

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | sub_eea6040 CFG-thunk trampoline body: tail-call rax (the real indirect target held in rax) | [V] |
| [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call; rdis resolves `[data_f99ffa0] = sub_eea6040` at every site; PE .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040; .text store scan for [0xF99FFA0] = 0 hits -> no code writer, never rewritten | [V] |
| 0xBC6A2AE | 8 | [rcx+0x0] | `0xBC6A2AE  mov rax,[rcx]` | bgfx dispatcher: rax = renderer-context vptr | [V] |
| 0xBC6A2B1 | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = renderer-context vptr[slot 26] = createTexture 0xe8143c0 (BGFX_MAP.md line 403) | [V] |
| 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | ret site after dispatcher tail-call `0xBC6A2C2 call [0xF99FFA0]`; = capture CALLER ret=0xBC6A2C8 | [V] [V live] |
| vtable 0xF215838+0x008 | 8 | - | - | `rdis vt 0xF215838`: `1 +0x008 sub_4e05e50 size 0x224 push rbp` (slot +0x000 = sub_4e060b0, slot +0x010 = non-code 0x0) -> job-object vptr[1] is statically sub_4e05e50 | [V] |
| 0x1289406 | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | sub_12893d0 list-walk: r13 = [obj+0x0] start cursor; r14 = [obj+0x8] end (next row) | [V] |
| 0x1289409 | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | end cursor of the entry list | [V] |
| 0x1289431 | 8 | [r13+0x8] | `0x1289431  mov rcx,[r13+8]` / `0x1289447  lock cmpxchg [rcx+8],edx` | entry+0x8 = refcounted object; refcount acquire via lock cmpxchg (eax -> eax+1) | [V] |
| 0x128947d | 8 | [r13+0x10] | `0x128947d  mov rcx,[r13+0x10]` | entry+0x10 = target job object whose vptr is dispatched | [V] |
| 0x1289486 | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = job object vptr | [V] |
| 0x1289489 | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = the real indirect target (sub_4e05e50 via the vtable row above) | [V] |
| 0x1289490 | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 tail-calls vptr[1] through the trampoline; ret site = 0x1289496 | [V] [V live] |
| 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the indirect call; = mc_root capture CALLER ret=0x1289496 in all 32 samples | [V] [V live] |
| 0x4E05E50 | 1 | - | `0x4E05E50  push rbp` | sub_4e05e50 entry: MC-side pack->GPU root, takes TexturePtr*-carrying object in RCX; `xref.py callers 0x4E05E50` -> EMPTY (0 static callers) | [V] |
| 0x4E05F61 | 8 | [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | sub_4e05e50 reads renderer context from object+0xE0 | [V] |
| 0x4E05F68 | 8 | - | `0x4E05F68  add rdi,0x58` | texture_obj = sub_4e05e50 arg + 0x58 | [V] |
| 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 -> dragon-layer create (rcx = texture_obj); ret site 0x4E05F7C | [V] [V live] |
| 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | ret site after `call 0xBC41420`; = dragon_texture_caller_bc41420 capture CALLER ret=0x4E05F7C | [V live] |
| 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texload_task (0x541bf00) static chain ends here: sub_18718d0 cache/lookup function | [V] |
| 0x18718FE | 8 | [rcx+0x30] | `0x18718FE  mov rcx,[rcx+0x30]` | sub_18718d0: cache-object array base at [rcx+0x30] | [V] |
| 0x1871902 | 8 | [rcx+0x8] | `0x1871902  mov rdx,[rcx+8]` | cache object = [array base]+0x8 | [V] |
| 0x1871906 | 1 | [rdx+0x19] | `0x1871906  cmp byte ptr [rdx+0x19],0` | per-entry flag (re-checked at 0x1871937) | [V] |
| 0x1871923 | 4 | [rdx+0x20] | `0x1871923  cmp [rdx+0x20],r8d` / `0x1871933  mov rdx,[rdx+r9]` (r9d<<4 => stride 0x10) | binary-search walk over stride-0x10 entry table comparing key at entry+0x20 | [V] |
| 0x1871948 | 8 | [rbp+0x70] | `0x1871948  mov [rbp+0x70],r15` | located cache object saved | [V] |
| 0x1871951 | 16 | [rsi+0x0] | `0x1871951  movups [rsi],xmm0` | a1+0x0 zeroed, 16 bytes | [V] |
| 0x1871A15 | 8 | - | `0x1871A15  lea rax,[0xEFCA680]` / `0x1871A1C  mov [rbp-0x50],rax` | staged cache-object vtable 0xEFCA680 (!= job vtable 0xF215838) | [V] |
| 0x1871A20 | 8 | - | `0x1871A20  lea rax,[0x873D0]` / `0x1871A27  mov [rbp-0x48],rax` | staged ctor sub_873d0; object built via `0x1871A33 call 0x7705B0` | [V] |
| 0x1871960 | 8 | [rax+0x8] | `0x1871960  mov rax,[rax+8]` / `0x1871964  call qword ptr [0xF99FFA0]` | cache-object vptr[0] destructor dispatch through the same trampoline — vptr[0], never vptr[1], so sub_18718d0 never reaches sub_4e05e50 | [V] |
| 0x1871A33 | 5 | - | `0x1871A33  call 0x7705B0` | cache-object construction entry (chains from 0x18718d0) | [V] |
| 0xC296E1A | 5 | - | `0xC296E1A  call 0xBC74120` | ax = returned 16-bit bgfx texture handle | [V] |
| [rdi+0x0] | 2 | [rdi+0x0] | `0xC296E22  mov ax,0xFFFF` / `0xC296E26  mov [rdi],ax` | invalid-handle fallback (ax=0xFFFF); 16-bit handle stored at texture_obj+0x00; texture_obj = arg+0x58 | [V] |
| 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | createTexture 0xe8143c0 -> TextureD3D12::create | [V] |
| 0xE814560 | 1 | - | `0xE814560  nop` | ret site after `call 0xE81BF30`; = l8b_texcreate_record capture CALLER ret=0xE814560 | [V live] |

## Static caller sets (negative findings)

| name | offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 static callers | - | - | - | `xref.py callers 0x4E05E50` -> EMPTY | sub_4e05e50 (0x4E05E50..0x4E06074) has no static caller; entered only at runtime | [V] |
| sub_12893d0 static callers | - | - | - | `xref.py callers 0x12893d0` -> 0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0 | complete static caller set of the dispatch site; none is texgroup_load(0x5421c90)/texload(0x58a1310)/texload_task(0x541bf00); upward chains dead-end (r24/r43) | [V] |

## Live evidence (orchestrator capture logs, read-only inputs)

- mc_root_4e05e50_callers.txt (_status.txt line 2: hits=150 samples=32): capture at 0x4E05E50; line 3 `CALLER ret=0x1289496 first_hit=1`; every one of the 32 samples has CALLER ret=0x1289496 — sub_4e05e50 is entered exclusively through sub_12893d0's vptr[1] trampoline tail-call at runtime. RCX = sub_4e05e50's first arg (TexturePtr*-carrying MC object); RCX dumps carry texture-descriptor data including name strings ('tex', 'legs') [V live]. This names the indirect caller of sub_4e05e50: sub_12893d0, ret site 0x1289496.
- dragon_texture_caller_bc41420.txt: sub_bc41420 capture CALLER ret=0x4E05F7C — the call site `0x4E05F77  call 0xBC41420` inside sub_4e05e50 [V live].
- l8b_texcreate_record.txt (_status.txt line 4: hits=150 samples=24): capture at TextureD3D12::create 0xe81bf30; `CALLER ret=0xE814560` matching `0xE814560  nop` after `0xE81455B  call 0xE81BF30`; R8 dumps carry UTF-16 texture names ('Texture: 2815', 'Texture: 2799') tying creations to named textures [V live].
- createtexture_callers.txt: `CALLER ret=0xBC6A2C8` — createTexture issued from the bgfx command-byte-14 dispatcher at `0xBC6A2C2  call qword ptr [0xF99FFA0]`, not from MC texture code directly [V live].

## CLOSES?

NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90)/texload(0x58a1310) -> sub_4e05e50 exists, and one provably cannot be built from static evidence: sub_4e05e50 has 0 static callers (xref EMPTY); sub_12893d0's 4 static callers (0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0) are outside texgroup_load's chain; texgroup_load's static chain ends at `0x54227AF  call 0x18718D0`, a 0xEFCA680 cache-object function (vptr[0] destructor dispatch only) that never reaches sub_4e05e50 (job vtable 0xF215838, slot 1). sub_4e05e50 is entered only at runtime via sub_12893d0's tail-call `0x1289490  call qword ptr [0xF99FFA0]` (trampoline sub_eea6040, `0xEEA6040  jmp rax`; rax = job-object vptr[1] = sub_4e05e50, resolved statically via `rdis vt 0xF215838` slot +0x008 [V]) — observed live: 150 hits / 32 samples, every sample ret=0x1289496 [V live docs/data/live/mc_root_4e05e50_callers.txt:3].

Everything else in L7e IS [V]-proven: Half 1 sampler flag decode + sampler cache (6ax); Half 2a D3D12 backend texture-management chain (slot 26 = createTexture 0xe8143c0 per BGFX_MAP.md line 403; TextureD3D12::create 0xe81bf30); MC-side createTexture issuance chain sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (command byte 0x0E) -> dispatcher -> createTexture -> TextureD3D12::create, proven at all ret sites by dis + live captures; returned handle stored at texture_obj+0x00 (`0xC296E26  mov [rdi],ax`, size 2 [V]); texture_obj = arg+0x58 (`0x4E05F68  add rdi,0x58` [V]); sub_4e05e50 arg = TexturePtr*-carrying object matching sdk TexturePtr.h [V live + V file read]. Atlas stitchers (L8a/L8b) remain separate open items (MIRROR_SKIP; oc_U-EL8a/oc_U-EL8b).

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required; every quoted `0xRVA  instr` line above was re-matched verbatim against a fresh rdis dis this session.
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; then line 2 after `## NEXT` is set to DONE.

## TOOL REQUESTS

- None. Static analysis is exhausted for the texgroup_load -> sub_4e05e50 bind: the indirect target is resolved statically (job vtable 0xF215838[1] = sub_4e05e50 [V vt output]), caller sets are enumerated (xref [V]), and the texload_task chain end is verified (`0x54227AF  call 0x18718D0` [V]). A live capture at trampoline entry 0xEEA6040 to read RAX was considered (r37's pending step) but is unnecessary: rax at the jmp is provable from the vtable row plus the existing mc_root live evidence (all 32 samples enter sub_4e05e50 via ret=0x1289496). No helper scripts written; no temporary files left behind.
