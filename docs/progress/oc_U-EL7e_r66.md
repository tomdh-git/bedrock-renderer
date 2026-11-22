## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] confirmed by a live capture (file + value cited), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r2/r3 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks.
- Live issuance chain proven through captures (cited, not re-derived): createtexture_callers (1 caller, ret=0xBC6A2C8), bgfx_createtexture_producer sub_bc73770 writes cmd byte 0x0E, wrapper 0xbc73bf0 (one caller ret=0xC296D7E inside dragon entry 0xc296b50), dragon entry 0xc296b50 (one caller ret=0xBC41B3E), handle store [texture_obj+0x00] at 0xc296e26 [V] by sub_bc41420 (call at 0xbc41b39), sub_bc41420 (one caller ret=0x4E05F7C). Chain: 0x4E05F7C -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 -> dispatcher -> createTexture 0xe8143c0.
- r15: sub_4e05e50 takes a TexturePtr* (matches sdk TexturePtr.h); issuance chain proven live through sub_4e05e50 -> ... -> createTexture. Missing: static link texgroup_load(0x5421c90) -> sub_4e05e50 (both 0 static xrefs; runtime function pointer [0xF99FFA0]).

## Pending work this session (per r37, do NOT redo anything below sub_bc41420)

Decode sub_eea6040 (the trampoline that [0xF99FFA0] points at) to determine what rax holds at its `jmp rax`, resolving the indirect call target via [0xF99FFA0].

## Static evidence this session — [0xF99FFA0] trampoline and rax at the jmp

sub_eea6040 is a one-instruction trampoline. rdis data analysis labels the qword at 0xF99FFA0 as sub_eea6040 (`0xeea6060  jmp qword ptr [0xF99FFA0] ; [data_f99ffa0] = sub_eea6040`), so every `call qword ptr [0xF99FFA0]` enters sub_eea6040 (`jmp rax`) and tail-calls whatever rax holds. rax is loaded by the caller immediately before the indirect call. The cell is read-only .rdata with no writer (r37); it holds sub_eea6040, not sub_4e05e50.

## Table 1 — [0xF99FFA0] trampoline and rax at the jmp (pending part)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline entry | 0xEEA6040 | - | R: rax register holds the indirect target | `0xEEA6040  jmp rax` | sub_eea6040 tail-calls the function pointer currently in rax | [V] |
| indirect-call cell read | 0xF99FFA0 | 8 | R: `0xEEA6060  jmp qword ptr [0xF99FFA0]` | `0xEEA6060  jmp qword ptr [0xF99FFA0]` | stub reads the qword cell; rdis labels it [data_f99ffa0] = sub_eea6040; read-only .rdata, no writer, holds sub_eea6040 not sub_4e05e50 | [V] |
| sub_4e05e50 loads rax | 0x4E05E82 | 8 | R: `0x4E05E82  mov rax,[rax+0x10]` | `0x4E05E82  mov rax,[rax+0x10]` | sub_4e05e50 loads the vtable function pointer *(a0+0x18)+0x10 into rax before the indirect call | [V] |
| sub_4e05e50 indirect call | 0x4E05E86 | 8 | R: `0x4E05E86  call qword ptr [0xF99FFA0]` | `0x4E05E86  call qword ptr [0xF99FFA0]` | sub_4e05e50 issues the indirect call -> jmp rax | [V] |
| sub_1289470 loads rax | 0x1289489 | 8 | R: `0x1289489  mov rax,[rax+8]` | `0x1289489  mov rax,[rax+8]` | sub_1289470 loads vtable slot +8 into rax; its call at 0x1289490 returns to 0x1289496 (mc_root_4e05e50_callers) | [V] |
| sub_1289470 indirect call | 0x1289490 | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` | `0x1289490  call qword ptr [0xF99FFA0]` | dispatch to sub_4e05e50 confirmed live (CALLER ret=0x1289496 in mc_root_4e05e50_callers.txt); at this jmp rax = sub_4e05e50 (0x4E05E50) at runtime | [V live] |

## CLOSES?

NO — blocking fact: the static hop texgroup_load(0x5421c90) -> sub_4e05e50 (MC root of the createTexture chain, TexturePtr* per sdk TexturePtr.h) is not provable by [V] rows. texgroup_load has 0 static xrefs; sub_4e05e50 is reached only through the [0xF99FFA0] trampoline (`jmp rax`) vtable-style dispatch from sub_1289470 (0 static xrefs in), whose call at 0x1289490 dispatches to sub_4e05e50 at runtime (rax = 0x4E05E50 [V live] via mc_root_4e05e50_callers.txt ret=0x1289496). The concrete texgroup_load -> sub_1289470 path is not statically mappable; the r37-prescribed live capture at 0xEEA6040 entry reading rax would settle the target, but the 4 capture slots are full this unit so no new capture could be added.

## TOOL REQUESTS

- eea6040_rax_target (desired, not added — 4 capture slots already pending): live capture at function entry 0xEEA6040, read rax; would confirm rax = sub_4e05e50 (0x4E05E50) at the [0xF99FFA0] trampoline jmp and close the static link texgroup_load -> sub_4e05e50 -> ... -> createTexture 0xe8143c0. No helper scripts written, no temporary files left behind.
