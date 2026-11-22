## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): ...; Minecraft-side pack->GPU chain ... and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from tool output/structure, [?] unknown / not located, [V live] live-capture evidence (docs/data/live/*.txt, cite file).
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r2/r3 + verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks.
- r3 (not redone): texgroup_load 0x5421c90 calls the Minecraft texture cache directly at `0x54227af  call 0x18718D0`; texload 0x58a1310 / texload_task 0x541bf00 have EMPTY static callers; texgroup_load does not call them.

## Live captures read this session (not re-queued; all used as context only)

- docs/data/live/createtexture_callers.txt (1612 hits): ONE caller, ret=0xBC6A2C8 (call site just before it, 0xBC6A2C2); R8 = 0x1C-byte create descriptor ("TEX" tag at +0x18, width/height u16 near the end); RCX = renderer ctx. createTexture 0xe8143c0 is issued from the bgfx command-buffer dispatcher at 0xBC6A2C2, not from MC texture code.
- docs/data/live/bgfx_createtexture_producer.txt: command-byte-14 producer is sub_bc73770 [V r4]; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 reach it from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80; MC texture code calls none statically.
- docs/data/live/dragon_texture_entry_c296b50.txt: wrapper 0xbc73bf0 has ONE caller, ret=0xC296D7E inside dragon-layer entry 0xc296b50 [V live].
- docs/data/live/dragon_texture_caller_bc41420.txt: dragon entry 0xc296b50 has ONE caller, ret=0xBC41B3E (141 hits) [V live]; handle store [texture_obj+0x00] at 0xc296e26 [V], caller sub_bc41420 (call at 0xbc41b39) [V live]; sub_bc41420 has ONE caller, ret=0x4E05F7C (372 hits) = Minecraft-side code [V live].
- docs/data/live/mc_root_4e05e50_callers.txt (150 hits, 32 samples): CALLER ret=0x1289496 — the static call site of sub_4e05e50 is `0x1289490  call qword ptr [0xF99FFA0]` (ret lands at 0x1289496), verified verbatim below.
- docs/data/live/l8b_texcreate_record.txt (24 samples): context only; atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b).

## Table 1 — issuance chain: sub_4e05e50 ("mc_root", TexturePtr*) down to createTexture 0xe8143c0

Every link below sub_4e05e50 is [V]-[V live] proven and is NOT re-decoded here; only the static resolution of the `[0xF99FFA0]` hop is new work (Table 2).

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry ("mc_root") | 0x4e05e50 | - | E: `0x4e05e50  push rbp` | mc_root entry; 0 xrefs in; takes TexturePtr* in RCX (reads [rcx+0x18] at 0x4e05e71); matches sdk TexturePtr.h [V live r15] | [V] |
| TexturePtr+0x18 read | 0x4e05e71 | 8 | R: `0x4e05e71  mov rax,[rcx+0x18]` | first field read of the TexturePtr argument | [V] |
| mc_root -> sub_bc41420 | 0x4e05f77 | - | S: `0x4e05f77  call 0xBC41420` / `0x4e05f7c  nop` | call to sub_bc41420; ret lands at 0x4e05f7c = live capture CALLER ret=0x4E05F7C [V live docs/data/live/dragon_texture_caller_bc41420.txt] | [V] [V live] |
| sub_bc41420 -> 0xc296b50 | 0xbc41b39 | - | S: `0xbc41b39  call 0xC296B50` / `0xbc41b3e  movzx eax,byte ptr [rbp+0x188]` | call to dragon entry 0xc296b50; ret lands at 0xbc41b3e = live capture CALLER ret=0xBC41B3E [V live docs/data/live/dragon_texture_entry_c296b50.txt] | [V] [V live] |
| handle store into texture object | 0xc296e26 | 2 | W: `0xc296e26  mov [rdi],ax` | 16-bit handle stored at [texture_obj+0x00] (rdi = texture obj) = live [V] handle store | [V] [V live] |
| bgfx createTexture wrapper | 0xbc73bf0 | - | E: `0xbc73bf0  push r15` | thin wrapper called from dragon layer; writer of cmd byte 0x0E is sub_bc73770 [V r4] | [V] |
| dispatcher issues createTexture | 0xbc6a2c2 | 8 | R: `0xbc6a2c2  call qword ptr [0xF99FFA0]` / `0xbc6a2c8  test rax,rax` | bgfx command-byte-14 handler calls [0xF99FFA0]; ret lands at 0xbc6a2c8 = live capture CALLER ret=0xBC6A2C8 [V live docs/data/live/createtexture_callers.txt] | [V] [V live] |
| createTexture entry (backend slot 26) | 0xe8143c0 | - | E: `0xe8143c0  push rbp` | slot-26 entry; issued via the dispatcher call above | [V] |
| MC-side caller of [0xF99FFA0] | 0x1289490 | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` / `0x1289496  nop` | sub_1289470 calls [0xF99FFA0]; ret lands at 0x1289496 = live capture CALLER ret=0x1289496 [V live docs/data/live/mc_root_4e05e50_callers.txt] | [V] [V live] |

Chain [V live]: 0x4E05F7C -> sub_bc41420 (0xbc41b39) -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd 0x0E) -> bgfx dispatcher -> `call [0xF99FFA0]` @ 0xbc6a2c2 -> createTexture 0xe8143c0; handle stored at [texture_obj+0x00] @ 0xc296e26.

## Table 2 — pending fact: static writer of [0xF99FFA0] (r22's only remaining open work)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` / tool proof | meaning | tag |
|---|---|---|---|---|---|---|
| [0xF99FFA0] slot location | 0x0F99FFA0 | 8 | - | `rdis sec`: `.rdata rva 0xeec8000 vsize 0x3441284 flags 0x40000040` (READ only, not writeable); slot lies inside .rdata | read-only global function-pointer slot | [V] |
| slot initial contents | 0x0F99FFA0 | 8 | - | qword at file offset for RVA 0x0F99FFA0 reads `0x14E2A1A90`, not `0x04E05E50` | not statically initialized to sub_4e05e50 | [I] |
| static readers of the slot | 0x1289490 / 0xbc6a2c2 | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` / `0xbc6a2c2  call qword ptr [0xF99FFA0]` | both `call qword ptr [0xF99FFA0]` sites resolve by RIP-relative arithmetic to RVA 0x0F99FFA0 (verified from instruction bytes) | slot is read at the MC call site and at the bgfx dispatcher | [V] |
| static writer search — all store forms | 0x0F99FFA0 | - | - | exhaustive .text scan for stores targeting 0x0F99FFA0: `C7 05` / `48 C7 05` / `89 XX 25` / `41 89 XX 25` / `44 89 XX 25` / `49 89 XX 25` / `C6 05` / `48 89 XX 25` / `xchg` / `cmpxchg` / `cmpxchg8b` / `movdqa` / `movdqu` — 0 hits | no instruction in .text stores to [0xF99FFA0] | [I] |
| slot-address materialization | 0x0F99FFA0 | - | - | `imm 0xF99FFA0` → 0 hit(s); `48/49 B8+r` / `48/49 C7 C0+r` imm = slot address → 0 hits; `48 8D XX 25 lea -> 0x0F99FFA0` → 0 hits | no code loads the slot address as an immediate or RIP-relative lea | [I] |
| stored-value materialization | 0x04E05E50 | - | - | `imm 0x4E05E50` → 0 hit(s); `xr 0x4E05E50` → 0 xref(s); `xr 0xEEA6040` (rdis tracks slot as sub_eea6040 = `jmp rax` thunk) → 0 xref(s); `sub_eea6040` has 0 xrefs in | the value sub_4e05e50 never appears as an immediate or RIP reference | [I] |
| sub_1289470 (function holding the MC call site) | 0x1289470 | - | - | `fn 0x1289470`: `[0x1289470..0x128b470) size 0x2000 0 xrefs in` | reached only indirectly itself | [V] |
| runtime value of the slot | 0x0F99FFA0 | 8 | - | live captures: at `0x1289490` ret=0x1289496 the callee is sub_4e05e50; at `0xbc6a2c2` ret=0xBC6A2C8 the callee is createTexture 0xe8143c0 — same slot, different values at different call times | mutable thunk slot, written by non-static means (outside the exe's static image) | [V live] |

## CLOSES?

NO — blocking fact: `[0xF99FFA0]` (a read-only .rdata global function-pointer slot) has NO static writer in Minecraft.Windows.exe: exhaustive scans found zero store instructions targeting it, no code loads its address, and the value `0x04E05E50` (sub_4e05e50) never appears as an immediate or RIP reference. At runtime the slot holds sub_4e05e50 when called from `0x1289490` [V live] and createTexture 0xe8143c0 when called from the dispatcher at `0xbc6a2c2` [V live], so the texgroup_load(0x5421c90) -> sub_4e05e50 link (both 0 xrefs, joined only at runtime through [0xF99FFA0]) cannot be closed by static analysis of the exe. Everything below sub_4e05e50 is [V]-[V live] proven (Table 1); the sampler half (6ax) [V] and the D3D12 backend texture-management chain [V] are already closed (r1); atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b). This unit is exhausted: no further static angle remains for the [0xF99FFA0] writer.

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — every backticked `0xRVA  instr` line in Tables 1-2 matches rdis dis output of the 1.26.62.01 exe.
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0 before line 2 of `## NEXT` is set to DONE.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from `rdis.exe dis` of the 1.26.62.01 exe; negative store scan done with a throwaway byte scanner over a file copy in C:\Users\Atomi\AppData\Local\Temp\opencode, no helper scripts left in the repo, no temporary files left behind).
