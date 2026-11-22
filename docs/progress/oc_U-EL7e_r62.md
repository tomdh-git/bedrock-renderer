## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (rdis.exe / xref.py / descscan2.py); no game launch, no builds, no rtools.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset; all its read/store sites listed; every `0xRVA  instr` line verbatim from rdis disassembly of the 1.26.62.01 exe (two spaces after the address); meaning only if an instruction/string shows it else '-'; tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Texture/atlas management — issuance chain to createTexture handle-write

The sampler half (6ax) is [V] (e820500.md / SamplerFlags.h). The D3D12 backend texture-management chain (createTexture 0xe8143c0 slot 26, record table this+0xBDE178 stride 0xB8) is [V] from prior rounds.

This unit adds the Minecraft-side texture-issuance chain that reaches the createTexture handle write. Live captures prove the chain end-to-end with real texture data flowing (createtexture_callers.txt: createTexture 0xe8143c0 entered with ret=0xBC6A2C8, R8 carrying texture descriptors — "sideTEX\0"/"enderTEX\0"/"ayerTEX\0" tags, dimensions, formats, and texture paths such as textures/ui/world_download_default; bgfx_createtexture_producer.txt: sub_bc73770 receives RDX descriptor objects with "TEX\0" magic). sub_4e05e50 is itself entered live (mc_root_4e05e50_callers.txt: ONE caller, ret=0x1289496, RCX = texture object with "tex" tag at +0x14).

| offset | size | site (read/store address) | instr | meaning | tag |
|--------|------|---------------------------|-------|---------|-----|
| 0x4e05f77 | 5 B | sub_4e05e50 passes RCX=rdi+0x58 (texture object) | `0x4e05f77  call 0xBC41420` | Minecraft-side texture object handed to bgfx issuance path | [V] |
| 0x4e05f7c | 1 B | return address of sub_4e05e50's call | `0x4e05f7c  nop` | caller return addr = 0x4e05f7c; live capture confirms sub_4e05e50->sub_bc41420 | [V] |
| 0xbc41b39 | 5 B | sub_bc41420 builds texture descriptor | `0xbc41b39  call 0xC296B50` | texture descriptor built for the createTexture command | [V] |
| 0xc296e26 | 2 B | store to texture_obj+0x00 | `0xc296e26  mov [rdi],ax` | D3D12 handle (ax) written into the texture object | [V] |
| 0xbc73aaa | 1 B | cmd byte store [rbp+0x2C] | `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` | bgfx command byte 0x0E (texture create) written | [V] |
| 0xbc6a2b1 | 8 B | vtable load [rax+0xD0] | `0xbc6a2b1  mov rax,[rax+0xD0]` | vtable+0xD0 slot loaded = createTexture entry point | [V] |
| 0xbc6a2c2 | 6 B | indirect call [0xF99FFA0] | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | indirect call -> createTexture; live ret=0xBC6A2C8 | [V] |
| 0xe8143c0 | 1 B | createTexture entry (D3D12 slot 26) | `0xe8143c0  push rbp` | createTexture target (D3D12 backend texture creation) | [V] |

Live issuance chain (proven by capture): sub_4e05e50 -> sub_bc41420 -> sub_c296b50 -> sub_bc73bf0 -> sub_bc73770(cmd 0x0E) -> bgfx dispatcher -> sub_bc69487 -> createTexture 0xe8143c0.

Remaining static gap (blocker): texgroup_load 0x5421c90 and texload 0x58a1310 have NO static callers (xref EMPTY), and sub_4e05e50 has 0 static xrefs in — it is reached only through the [0xF99FFA0] trampoline (read-only .rdata = sub_eea6040 `jmp rax`, no writer) from sub_12893d0 at `0x1289490 call qword ptr [0xF99FFA0]`/`0x1289496 nop`, where rax must = 0x4e05e50 at call time (not static-provable). sub_12893d0 is itself reached via sub_1145c20 (`0x1145d5a call 0x12893D0`, 1 xref from 0x882ee0). The Minecraft pack->GPU root connection texgroup_load/texload -> ... -> sub_4e05e50 is therefore NOT statically provable.

CLOSES? = NO — single blocking fact: the static link texgroup_load/texload (0x5421c90/0x58a1310) -> sub_4e05e50 is missing (texgroup_load/texload have no static callers; sub_4e05e50 reached only via indirect [0xF99FFA0] trampoline, rax = 0x4e05e50 not static-provable). The GPU-side issuance chain to the createTexture handle write IS live-proven ([V] rows above), but the Minecraft pack->GPU root connection is not statically proven, so texture/atlas management is not fully closed.
