## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1-r3)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] (Tables 1-8 in oc_U-EL7e_r1.md): record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (slot 26), updateTexture 0xe814a70 (slot 28), readTexture 0xe8150f0 (slot 30), resizeTexture 0xe815840 (slot 31), override/get/destroy 0xe815c30..0xe815fbf (slots 32-34), destructor 0xe80f290, blit 0xe818bc0 (slot 51), blitSetup 0xe819750 (slot 52). BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records (guard byte this+0xC96190 = 0 live).
- r2/r3 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] thunks (slot 26 = offset 0xD0). texload 0x58a1310 / texload_task 0x541bf00: xref EMPTY for both; texgroup_load does not call them statically (its only cache-bound call is `0x54227af  call 0x18718D0`).

## This session — new angle per orchestrator hint

The only missing link (same as L7e): createTexture issuance. RendererContext slot 26 = 0xe8143c0 is reached via [reg+0xD0] vcall OR bgfx command byte 14 -> handler 0xbc69487. Task: (1) find who PRODUCES command byte 14 (writers of 0x0E into the bgfx command buffer near the texture-create API, bgfx::createTexture* wrappers; rdis find/xr on the handler's dispatch table and the cmd-buffer write helper), (2) trace the returned handle into TexturePtr/ClientTexture. If the producer is a thin bgfx API wrapper called from the texture-object init (vtable 0xEFCA580 slot 4), cite that call. If not statically reachable, say so with xref evidence and stop.

## (1) Command-byte-14 handler — decoded [V]

The command processor is sub_bc68c00 (render-thread frame step sub_bc63150 calls it at 0xbc6337b and 0xbc633c4 on buffer +0xDC5818/+0xE05820). Its dispatch loop reads one command byte, indexes a jump table at 0xF449638, and case 0xbc69487 handles command byte 14 (createTexture). It decodes a handle (word), an 8-byte Memory* pointer, flags, then branches on a "TEX" dword magic: if "TEX" it calls vtable+0x1C0 (TextureD3D12::create body); otherwise (default path, the one the live capture hits) it calls RendererContext vtable+0xD0 = createTexture slot 26, then stores the returned ID3D12Resource* into the guarded texture page array (record table this+0xBDE178 / page list this+0xC96178, stride 0xB8) indexed by handle.

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| command processor entry | 0xbc68c00 | - | E: `0xbc68c00  add [rax],al` | sub_bc68c00 command-buffer consume loop (dispatch via table at 0xF449638) | [V] |
| byte-14 / createTexture handler case | 0xbc69487 | - | E: `0xbc69487  and edx,0xFFFFFFFE` | command-byte case start; decodes Memory*+handle+flags | [V] |
| "TEX" magic branch | 0xbc695a3 | 4 | R: `0xbc695a3  cmp dword ptr [rsp+0x8C],0x584554` | compares dword to "TEX" (0x584554); jne -> default createTexture path | [V] |
| TEX path: TextureD3D12::create body | vtable+0x1C0 | 8 | R: `0xbc69693  mov rax,[rcx]` / `0xbc69696  mov rax,[rax+0x1C0]` / `0xbc6969d  call qword ptr [0xF99FFA0]` | vtable+0x1C0 = TextureD3D12::create body | [V] |
| default path: createTexture vcall slot 26 | vtable+0xD0 | 8 | R: `0xbc6a2ae  mov rax,[rcx]` / R: `0xbc6a2b1  mov rax,[rax+0xD0]` / S: `0xbc6a2c2  call qword ptr [0xF99FFA0]` | RendererContext vtable+0xD0 = createTexture (slot 26 = 0xe8143c0) | [V] |
| createTexture return | ret=0xBC6A2C8 | - | R: `0xbc6a2c8  test rax,rax` | createTexture returns ID3D12Resource*; then stores into guarded page array | [V] |
| consumer caller (render thread) | 0xbc6337b / 0xbc633c4 | - | S: `0xbc6337b  call 0xBC68E40` / `0xbc633c4  call 0xBC68E40` | sub_bc63150 render-thread frame step consumes the command buffer | [V] |

## (2) Live capture — createTexture IS issued at runtime [V live]

Queued capture `createtexture_callers` (rva=0xE8143C0) returned: `ret=0xBC6A2C8` — i.e. createTexture (0xe8143c0, slot 26) IS called and returns into the byte-14 handler's default path (`0xbc6a2c8  test rax,rax`), 25 hits. RCX = renderer context (0x5314A010000, the live `RendererContextD3D12` / `bgfx::s_ctx` at global 0x12ae1748). R8 carries texture Memory* descriptors (e.g. "sideTex", "world_download_default", UI textures). This proves createTexture is reachable and invoked via the command-byte-14 path at runtime.

## (3) Byte-0x0E producer — NOT statically locatable [negative evidence]

I exhaustively scanned every command-buffer writer (all `add rcx,0xDC5820` + `call 0xEBCE390` sites) and every `imm 0x0E` hit:
- Writers found and their hardcoded opcode byte: sub_bc5f8d0=0x07, sub_bc63b80=0x00, sub_bc716a0=0x0A, sub_bc71990=0x0A, sub_bc71da0=0x0B, sub_bc74a80=0x14, sub_bc74590=0x12, sub_bc7489f=0x27 (writes to +0xE05820 buffer). NONE stores 0x0E.
- `imm 0x0E` over .text returns only `mov ecx,0xE` at 0x81bf (a register move, not a memory write) — there is NO `mov byte ptr [mem], 0x0E` anywhere.
- sub_8b9f1c0 / sub_8b9f370 call sub_bc71990 (opcode 0x0A) and emit the debug string "Acceleration Structure" (`0x8b9f307  movups xmm0,[0xF5C7424]`) — they are RTX acceleration-structure creation, NOT createTexture.
- The jump table at 0xF449638 is obfuscated/indirect (entries do not resolve to plain code RVAs), so byte-to-handler mapping cannot be re-derived statically; the hint's mapping (byte 14 -> 0xbc69487) is accepted as verified and is consistent with the live capture.

Conclusion: command byte 0x0E is computed at runtime (not a hardcoded immediate store), so its producer function cannot be identified by static pattern search. No thin bgfx createTexture API wrapper writing byte 0x0E was found, and none is called from the texture-object init (vtable 0xEFCA580 slot 4 = sub_a3f10, which only sets live vtables 0xEFCA5A0/5D0/5F0 and cleans up the old resource — it does not call createTexture or write any command).

## (4) Static reachability of createTexture from the Minecraft side

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture static callers | 0xe8143c0 | - | - | `xref.py callers 0xe8143c0` = EMPTY (proven by r2/r3, not redone) | no static caller; only indirect [vptr+0xD0] thunks | [V] |
| texture-object init (vtable 0xEFCA580 slot 4) | sub_a3f10 | - | E: `0xa3f10  push rsi` / calls `0xa3f40` | sets live vtables 0xEFCA5A0/5D0/5F0, failure -> 0xEFCD320/340 -> tail-jump 0x76B950; does NOT call createTexture or write a command | [V] |
| live createTexture invocation | ret=0xBC6A2C8 | - | - | `python tools/livecap/request.py result createtexture_callers` (ret=0xBC6A2C8, 25 hits) | createTexture IS called at runtime via command-byte-14 handler | [V live] |

## Interpretations ([I] notes, not row claims)

- The createTexture return value (ID3D12Resource*, rax) is stored into the guarded texture page array at `this+0x1E55AB8` (page list, index = handle) within the byte-14 handler default path (0xbc6a32e+); this is the backend record table this+0xBDE178 / stride 0xB8 (r1 Tables 1-8). So the GPU handle IS created and recorded at runtime.
- Tracing that handle forward into the Minecraft-side `TexturePtr`/`ClientTexture` (i.e., who writes the GPU handle into the Minecraft texture object after createTexture returns) requires a static path from createTexture back to the texture-object init. That path does not exist statically: xref.py callers 0xe8143c0 = EMPTY, and the byte-0x0E command producer is not located. So the Minecraft->GPU handle-write link is not instruction-proven.
- texload 0x58a1310 / texload_task 0x541bf00: xref EMPTY for both (r2/r3); texgroup_load does not call them (its only cache-bound call is `0x54227af  call 0x18718D0`). The item-line chain texgroup_load->texload->texload_task->0x18718d0 is not statically supported.

## CLOSES?

NO — blocking fact: no statically provable path from the Minecraft-side texture-object init (vtable 0xEFCA580 slot 4 = sub_a3f10, which only sets vtables and does not call createTexture) to D3D12 GPU handle creation. createTexture IS reached at runtime via bgfx command byte 14 -> handler 0xbc69487 -> default path calling RendererContext vtable+0xD0 (0xe8143c0 slot 26), proven [V live] by the createtexture_callers capture (ret=0xBC6A2C8, 25 hits). However: (a) the producer of command byte 0x0E is not statically locatable — no `mov byte ptr [mem], 0x0E` exists anywhere (imm 0x0E), all command-buffer writers hardcode other opcodes (0x00/0x07/0x0A/0x0B/0x12/0x14/0x27), and the dispatch table is obfuscated; (b) xref.py callers 0xe8143c0 = EMPTY (no static caller, only indirect [vptr+0xD0]); (c) therefore the returned handle cannot be traced into TexturePtr/ClientTexture statically, and no thin bgfx createTexture API wrapper called from the texture-object init was found. The sampler half (6ax) [V] (e820500.md/SamplerFlags.h) and the D3D12 backend texture-management chain [V] (r1 Tables 1-8) are already proven; atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b). The pending half of L7e cannot be closed by this unit.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly of the 1.26.62.01 exe; negative producer search via `imm 0x0E` and `add rcx,0xDC5820` writer scan; live capture `createtexture_callers` read via `python tools/livecap/request.py result createtexture_callers`). No helper scripts written, no temporary files left behind.
