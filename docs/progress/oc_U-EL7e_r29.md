## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): "- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)"

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r2/r3 / verified live captures)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks.
- Texture cache 0x18718d0 decoded [V] (r2/r3): texgroup_load 0x5421c90 calls it at `0x54227af  call 0x18718D0`; BST at this+0x30; ready callback 0x873D0 -> jmp 0xEEC59D0; completion 0x186DAC0; desc builder 0x58CA10; enqueue 0x71BC70.
- Live capture chain (createTexture issuance) proven [V live] across captures 1-5: createTexture 0xe8143c0 <- dispatcher case ~0xBC6A2C3 (cmd byte 0x0E, 0x1C desc "TEX"+0x18) <- sub_bc73770 (cmd 0x0E producer) <- wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 <- dragon entry 0xc296b50 <- 0xBC41B3E (in sub_bc41420, call at 0xbc41b39) <- handle store [texture_obj+0x00] at 0xc296e26 <- sub_bc41420 <- 0x4E05F7C (Minecraft-side) [V live]. LIVE RESULT 5: "This closes L8a (and L7e)." sub_4e05e50 (entry 0x4E05E50) takes a TexturePtr* (matches sdk TexturePtr.h) [V live, mc_root_4e05e50_callers.txt ret=0x1289496].

## Work this session (r22 task: resolve [0xF99FFA0])

r22 (56/56, CLOSES NO) assigned the only remaining work: resolve the pointer in [0xF99FFA0] by locating its writer (xref to 0xF99FFA0 as a store) and name the function it is set to; if that is sub_4e05e50 (0x4E05E50) the static link texgroup_load(0x5421c90) -> sub_4e05e50 is closed.

## Table 9 — [0xF99FFA0] global resolution (r22 task)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| [0xF99FFA0] read — allocator indirect call (texgroup_load) | 0xF99FFA0 | 8 | R: `0x5421d63  call qword ptr [0xF99FFA0]` / R: `0x5421d8a  call qword ptr [0xF99FFA0]` / R: `0x5421e43  call qword ptr [0xF99FFA0]` / R: `0x5421e63  call qword ptr [0xF99FFA0]` / R: `0x5421e8e  call qword ptr [0xF99FFA0]` / R: `0x5421ea4  call qword ptr [0xF99FFA0]` / R: `0x5421f31  call qword ptr [0xF99FFA0]` | global read as indirect-call target (allocator calls, size in edx -> ptr in rax); rdis resolves `[data_f99ffa0] = sub_eea6040` at every site | [V] |
| [0xF99FFA0] target — sub_eea6040 body | 0xEEA6040 | - | E: `0xeea6040  jmp rax` | sub_eea6040 (0xEEA6040) is a tail-call thunk `jmp rax`, 0 xrefs in; NOT sub_4e05e50 (0x4E05E50) | [V] |
| [0xF99FFA0] dead-code reference (inside sub_eea6040 padded range) | 0xF99FFA0 | 8 | R: `0xeea6060  jmp qword ptr [0xF99FFA0]` | dead `jmp [0xF99FFA0]` at 0xeea6060; resolves to sub_eea6040 itself | [V] |

## Interpretation of the r22 task ([0xF99FFA0])

- [0xF99FFA0] holds sub_eea6040 (0xEEA6040), verified verbatim at all 7 texgroup_load call sites above (`call qword ptr [0xF99FFA0]`, rdis annotation `[data_f99ffa0] = sub_eea6040`).
- `sub_eea6040` body at `0xeea6040` is `jmp rax` — a tail-call thunk. It is used by texgroup_load as the allocator indirect call (size in edx, result pointer in rax).
- `xr 0xF99FFA0` (rdis): every reference to 0xF99FFA0 in .text is a READ (`call qword ptr [0xF99FFA0]` or `mov rdx/r8,[0xF99FFA0]`). NO store/write reference to 0xF99FFA0 exists in .text (no `mov [0xF99FFA0],...`). So [0xF99FFA0] is never written by .text code; it holds sub_eea6040 constantly.
- DECISIVE: [0xF99FFA0] = sub_eea6040 (0xEEA6040) ≠ sub_4e05e50 (0x4E05E50). These are different functions (a tail-call thunk vs the TexturePtr* texture-create function). The r22 theory that [0xF99FFA0] is set to sub_4e05e50 is CONTRADICTED by the disassembly. Per the brief rule "treat as a verified fact unless the disassembly contradicts it," the disassembly contradicts it.

## CLOSES?

NO — blocking fact: the static link texgroup_load(0x5421c90) -> sub_4e05e50(0x4E05E50) via [0xF99FFA0] is disproven. [0xF99FFA0] = sub_eea6040 (tail-call thunk `jmp rax`), NOT sub_4e05e50; xr 0xF99FFA0 shows only reads, no stores in .text. Both texgroup_load and sub_4e05e50 have 0 static xrefs, so the static pack->GPU link has no [V] static instruction row. (The createTexture issuance chain itself is independently [V live] proven via captures 1-5 — LIVE RESULT 5 — but that is dynamic/live evidence, not the static link r22 blocked on.)

## TOOL REQUESTS

- None (all instruction lines taken verbatim from `rdis.exe dis`/`xr` output of the 1.26.62.01 exe; no helper scripts written, no temporary files left behind).
