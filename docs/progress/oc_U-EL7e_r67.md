## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). Static analysis only.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r2/r3 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks / bgfx command byte 14 -> handler 0xbc69487.

## This session — TexturePtr -> createTexture issuance chain (the missing link)

Trampoline sub_eea6040 [0xeea6040..0xeea8040), 0 xrefs in:
- `0xeea6040  jmp rax` — trampoline. rdis data annotation `[data_f99ffa0] = sub_eea6040`, so [0xF99FFA0] holds address sub_eea6040 (read-only .rdata, no writer, per r37). Static work on that pointer exhausted; rax holds the real dynamic indirect-call target at jmp time. [V]

mc_root / sub_4e05e50 [0x4e05e50..0x4e07e50), 0 xrefs in (called indirectly via trampoline); r15 review: takes a TexturePtr* (matches sdk TexturePtr.h). Decoded head [V]:
- `0x4e05e6e  mov rdi,rcx` — rdi = RCX = texture object / TexturePtr* argument. [V]
- `0x4e05e71  mov rax,[rcx+0x18]` / `0x4e05e82  mov rax,[rax+0x10]` / `0x4e05e86  call qword ptr [0xF99FFA0]` — refcount/destructor path via trampoline. [V]
- `0x4e05f68  add rdi,0x58` / `0x4e05f74  mov rcx,rdi` / `0x4e05f77  call 0xBC41420` — DIRECT call to sub_bc41420 with RCX = texture_obj+0x58. [V] Return site `0x4e05f7c  nop` matches live capture ret=0x4E05F7C [V live]. LINK mc_root -> sub_bc41420 CLOSED [V]+[V live].

mc_root's caller (live capture mc_root_4e05e50_callers.txt, ret=0x1289496):
- Function sub_1289400 [0x1289400..0x128b400), 0 xrefs in (called indirectly).
- `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` / `0x1289490  call qword ptr [0xF99FFA0]` / `0x1289496  nop` — VIRTUAL call through trampoline: rax = vtable slot +8 (= mc_root), return address 0x1289496 = live capture ret=0x1289496 [V + V live]. mc_root is a virtual texture-object method (vtable+8).

Issuance chain (LIVE RESULTS 1-5, not redone; now anchored [V] at mc_root):
- mc_root (0x4E05E50) -> sub_bc41420 (0x4e05f77 direct) [V] -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (writes cmd byte 0x0E) -> bgfx command-buffer dispatcher case 0xBC6A2C3 -> createTexture 0xe8143c0 [V live].
- Handle store [texture_obj+0x00] at 0xc296e26 [V live] (r7); caller sub_bc41420 at 0xbc41b39 [V live].
- Return address 0xBC6A2C8 at createTexture entry (createtexture_callers.txt): R8 = 0x1C-byte create descriptor ("TEX" tag at +0x18), RCX = renderer ctx. Issued from dispatcher, not MC texture code [V live].

SDK TexturePtr header [V — file read]:
- src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h: `class mce::TexturePtr { std::shared_ptr<void> mClientTexture; // +0x0 (16B); std::shared_ptr<void> mResourceLocationPtr; // +0x10 (16B); }` ; `static_assert(sizeof(TexturePtr) == 32);` (stub-only carrier per header comment; binary texture object is larger — live data shows descriptor at texture_obj+0x58). [V]

texgroup_load / texload / texload_task (item-line chain) status [?]:
- texgroup_load 0x5421c90 -> texture cache 0x18718d0 at `0x54227af  call 0x18718D0` [V] (r2/r3). texload 0x58a1310 and texload_task 0x541bf00: xref.py callers EMPTY for both; texgroup_load does NOT call them statically (its only cache-bound call is 0x54227af). Item-line chain texgroup_load->texload->texload_task->0x18718d0 NOT statically supported.
- mc_root (sub_4e05e50) is reached via sub_1289400 virtual call (vtable+8) at 0x1289490 [V]; sub_1289400 itself has 0 static xrefs (called indirectly). Static link texgroup_load -> mc_root NOT provable by static analysis (indirect/virtual dispatch).

## Table — TexturePtr -> createTexture issuance (this unit's new rows)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline entry | 0xeea6040 | - | E: `0xeea6040  jmp rax` | trampoline; indirect-call target placeholder | [V] |
| trampoline data annotation | [0xF99FFA0] | 8 | R: `0xeea6040  jmp rax` (rdis: `[data_f99ffa0] = sub_eea6040`) | [0xF99FFA0] holds sub_eea6040 address | [V] |
| mc_root entry | 0x4e05e50 | - | E: `0x4e05e50  push rbp` | sub_4e05e50 / mc_root; TexturePtr* in RCX (r15) | [V] |
| mc_root arg copy | rdi | 8 | `0x4e05e6e  mov rdi,rcx` | texture object / TexturePtr* copied to rdi | [V] |
| mc_root +0x18 read | texture_obj+0x18 | 8 | `0x4e05e71  mov rax,[rcx+0x18]` | reads texture_obj+0x18 | [V] |
| mc_root trampoline call (destroy) | [0xF99FFA0] | 8 | `0x4e05e86  call qword ptr [0xF99FFA0]` | indirect destructor call via trampoline | [V] |
| mc_root -> sub_bc41420 | texture_obj+0x58 | 8 | `0x4e05f68  add rdi,0x58` / `0x4e05f74  mov rcx,rdi` / `0x4e05f77  call 0xBC41420` | DIRECT call to sub_bc41420, RCX=texture_obj+0x58; ret site 0x4e05f7c = live ret=0x4E05F7C | [V] |
| mc_root virtual call site | vtable+8 | 8 | `0x1289486  mov rax,[rcx]` / `0x1289489  mov rax,[rax+8]` / `0x1289490  call qword ptr [0xF99FFA0]` / `0x1289496  nop` | virtual call rax=vtable[+8]=mc_root; return addr 0x1289496 = live capture ret=0x1289496 | [V] |
| sub_bc41420 handle store | texture_obj+0x00 | 8 | W: `0xc296e26  ...` (capture: store [texture_obj+0x00]) | returned handle stored into texture_obj+0x00 | [V live] |
| createTexture descriptor | R8 = 0x1C-byte desc | 0x1C | R8 at capture ret=0xBC6A2C8 (createtexture_callers.txt; call to createTexture at 0xBC6A2C3, return address 0xBC6A2C8): "TEX" tag at +0x18 | create descriptor passed to createTexture | [V live] |
| createTexture entry | 0xe8143c0 | - | E: `0xe8143c0  push rbp` | slot-26 createTexture; no static caller (xref EMPTY) | [V] |

## Interpretations ([I] notes, not row claims)

- mc_root is a texture-object virtual method (vtable slot +8) that, as part of texture object setup/release, invokes sub_bc41420 to issue createTexture. RCX of sub_bc41420 = texture_obj+0x58 which holds the texture creation descriptor ("TEX" tag, width/height/format) per live capture.
- The TexturePtr->createTexture issuance link (the core missing link per the orchestrator hint) IS proven [V]+[V live]: mc_root -> sub_bc41420 -> ... -> createTexture 0xe8143c0, handle stored [texture_obj+0x00].
- The static link texgroup_load(0x5421c90) -> mc_root is NOT provable by static analysis: mc_root is called virtually (vtable+8 via trampoline) from sub_1289400, which itself has 0 static xrefs. texload/texload_task have no static callers; the item-line chain texgroup_load->texload->texload_task->0x18718d0 is not statically supported (texgroup_load calls 0x18718d0 directly at 0x54227af).
- Atlas stitchers (terrain/item) + mip/compression builders are separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## CLOSES?

NO — blocking fact: the createTexture issuance from the TexturePtr/texture-object side IS proven [V]+[V live] (mc_root 0x4E05E50 vtable+8 -> sub_bc41420 at 0x4e05f77 -> ... -> createTexture 0xe8143c0, handle store [texture_obj+0x00] at 0xc296e26), but the static link from the Minecraft-side pack->GPU root texgroup_load(0x5421c90) to mc_root/sub_4e05e50 is NOT provable by static analysis: mc_root is reached only through an indirect/virtual call (sub_1289400 vtable+8 via trampoline [0xF99FFA0], sub_1289400 has 0 static xrefs; texload 0x58a1310 and texload_task 0x541bf00 have no static callers). Per r15 this single static link is the remaining blocker. Sampler half (6ax) [V] and D3D12 backend texture-management chain [V] are already proven; atlas stitchers tracked by L8a/L8b.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly of the 1.26.62.01 exe; live captures read from docs/data/live/*.txt; TexturePtr.h read from src tree; no helper scripts written, no temporary files left behind).
