## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; orchestrator live captures read read-only.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in an orchestrator live capture (file+line cited), [I] inferred from structure/BGFX_MAP/hint, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (cited from r1-r7, NOT re-derived here)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 of oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (slot 26), updateTexture 0xe814a70 (28), readTexture 0xe8150f0 (30), resizeTexture 0xe815840 (31), override/get/destroy 0xe815c30..0xe815fbf (32-34), destructor 0xe80f290, blit 0xe818bc0 (51), blitSetup 0xe819750 (52); BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- Static negatives (r2-r6, not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] (slot 26 = offset 0xD0); texload 0x58a1310 and texload_task 0x541bf00: xref EMPTY for both; texgroup_load does not call them (its only cache-bound call is `0x54227af call 0x18718d0` [V]); 0x18718d0 decoded as the texture cache (BST this+0x30, ready callback 0x873D0->jmp 0xEEC59D0 via 0x7705B0, async enqueue 0x71BC70 "resource dispatch"); texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10) only swaps live vtables 0xEFCA5A0/5D0/5F0, never calls createTexture [V r2]. Atlas stitchers remain open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.
- Command byte 0x0E producer (r6/r7, not redone): sub_bc73770 writes `0xbc73aaa mov byte ptr [rbp+0x2C],0xE` [V]; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 call it [V xref]; live capture bgfx_createtexture_producer: all 16 hits ret=0xBC73EAD at `0xbc73ea8 call 0xBC73770` in sub_bc73bf0 [V live]. `imm 0x0E` scan found NO `mov byte ptr [mem], 0x0E`; command-buffer writers hardcode other opcodes; dispatch table at 0xF449638 obfuscated/indirect. Hint mapping (byte 14 -> 0xbc69487) accepted as verified, consistent with both live captures.
- Handle into dragon texture object (r7): sub_c296b50 calls sub_bc73bf0 at `0xc296d79 call 0xBC73BF0` [V] and stores the createTexture handle at `0xc296e26 mov [rdi],ax` (texture object +0x0) [V]; width/height at descriptor [r12+0x10] stored to object +0x18 via `0xc296e36 mov rdx,[r12+0x10]` / `0xc296e3b mov [rdi+0x18],rdx` [V]; descriptor block at [r12] via `0xc296e2d movups xmm0,[r12]` copied to object +0x8 via `0xc296e32 movups [rdi+8],xmm0` [V]. Live capture dragon_texture_entry_c296b50: CALLER ret=0xBC41B3E, 6 hits — sub_c296b50 has one static caller, sub_bc41420 at call site 0xbc41b39 [V live + V].

## New findings this session (per orchestrator hint; NOT redoing r1-r7)

### (1) Function containing 0xBC41B3E — sub_bc41420 decoded [V]

sub_bc41420 [0xbc41420..0xbc43420), size 0x2000, 1 static xref in. It is the MC-side pack->GPU driver: it reads a source texture object (type/width at +0x0, height at +0x4, halved per mip level, mip count at +0x14, entry array at +0x40/+0x48 with 0x30-stride entries), calls the dragon texture-object init sub_c296b50 once per mip level at `0xbc41b39 call 0xC296B50`, and writes handle+descriptor+width/height+ready flag to its out pointer:

| offset | size | access | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x4e05e50 | - | E: | `0x4e05e50  push rbp` | MC-side texture create root | [V] |
| 0x4e05f77 | - | S: | `0x4e05f77 call 0xBC41420` | MC root calls sub_bc41420; live capture dragon_texture_caller_bc41420: CALLER ret=0x4E05F7C, hits=372 samples=17, every live call returns to this call site (+1 insn) | [V] [V live] |
| [rcx+0x28] | 8 | R: | `0xbc41446  cmp qword ptr [rcx+0x28],0` | source+0x28 pointer must be non-null, else error path | [V] |
| [rcx+0x78] | 1 | R: | `0xbc4145d  movzx eax,byte ptr [rcx+0x78]` | source feature byte read | [V] |
| [rsi+0x80] | 1 | R: | `0xbc4146f  cmp byte ptr [rsi+0x80],0` | second source feature byte read | [V] |
| [rsi+0x14] | 4 | R: | `0xbc4149f  mov eax,[rsi+0x14]` | mip level count | [V] |
| [rsi+0x40]/[rsi+0x48] | 8 | R: | `0xbc414b3  mov rdx,[rsi+0x40]` / `0xbc414b7  mov rcx,[rsi+0x48]` / `0xbc414bb  sub rcx,rdx` / `0xbc414be  sar rcx,4` | entry array [start,end); entries 0x30 bytes (rax*3<<4 stride seen in sub_5a4c4f0 copy calls) | [V] |
| [rsi+0x0] | 4 | R: | `0xbc41559  mov edx,[rsi]` | source+0x0 dword (texture type), halved per mip with +0x4 | [V] |
| [rsi+0x4] | 4 | R: | `0xbc41560  mov r8d,[rsi+4]` / `0xbc4156a  shr edx,1` / `0xbc4156e  shr r8d,1` | width and height shifted right 1 each mip level | [V] |
| 0xc296b50 | - | S: | `0xbc41b39  call 0xC296B50` | sub_bc41420 calls the dragon texture-object init once per mip level | [V] |
| [rbp+0x180] | 8 | R: | `0xbc41b52  mov r13,[rbp+0x180]` | dragon-created object pointer (out of sub_c296b50) | [V] |
| [r13+0x18] | 8 | R: | `0xbc41b59  mov rax,[r13+0x18]` | width/height qword read from dragon object | [V] |
| [r13+8] | 16 | R: | `0xbc41b61  movups xmm0,[r13+8]` | 16-byte descriptor read from dragon object | [V] |
| [r13+0x30]/[r13+0x38] | 8 | R: | `0xbc41b6a  mov r12,[r13+0x30]` / `0xbc41b6e  cmp qword ptr [r13+0x38],0x10` | name: inline if size < 0x10 at +0x20, else heap pointer at +0x20 | [V] |
| [rdi] | 16 | W: | `0xbc41cb9  movdqu [rdi],xmm0` | 16-byte block (handle+descriptor image) written at out ptr +0x0 | [V] |
| [rdi+0x10] | 8 | W: | `0xbc41cb5  mov [rdi+0x10],rcx` | qword traced back to dragon object [r13+0x18] (width/height) written at out ptr +0x10 | [V] |
| [rdi+0x40] | 1 | W: | `0xbc41cfd  mov byte ptr [rdi+0x40],1` | ready flag set at out ptr +0x40 | [V] |
| 0x4e05f85 | - | S: | `0x4e05f85  call 0x4E061B0` | MC root copies the dragon-created result into the MC-side texture object | [V] |
| [rdx+0x0] | 16 | R: | `0x4e061cb  movups xmm0,[rdx]` | 16 bytes (handle at +0x0 + descriptor) read from the dragon-created object | [V] |
| [rcx+0x0] | 16 | W: | `0x4e061ce  movups [rcx],xmm0` | handle at +0x0 written into the MC-side texture object | [V] |
| [rcx+0x10] | 8 | W: | `0x4e061c7  mov [rcx+0x10],r8` | width/height qword written to MC texture object +0x10 | [V] |
| [rcx+0x40] | 1 | W: | `0x4e062bb  mov byte ptr [rcx+0x40],1` | ready flag set at MC texture object +0x40 | [V] |

### (2) Handle trace into TexturePtr/ClientTexture — through dragon layer and backend [V + V live]

| offset | size | access | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| [rbp+0x2C] | 1 | W: | `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` | command byte 14 (createTexture) written into the command buffer | [V] |
| 0xc296d79 | - | S: | `0xc296d79  call 0xBC73BF0` | sub_c296b50 calls the thin bgfx createTexture wrapper | [V] |
| 0xc296e26 | 2 | W: | `0xc296e26  mov [rdi],ax` | createTexture handle (u16) stored at dragon texture object +0x0 | [V] |
| 0xc296e2d | 16 | R: | `0xc296e2d  movups xmm0,[r12]` | 16-byte descriptor read from descriptor block [r12] | [V] |
| 0xc296e32 | 16 | W: | `0xc296e32  movups [rdi+8],xmm0` | descriptor written to texture object +0x8 | [V] |
| [r12+0x10] -> [rdi+0x18] | 8 | R/W: | `0xc296e36  mov rdx,[r12+0x10]` / `0xc296e3b  mov [rdi+0x18],rdx` | width/height at descriptor+0x10 stored to object +0x18 | [V] |
| 0xbc6a2ae | 8 | R: | `0xbc6a2ae  mov rax,[rcx]` / `0xbc6a2b1  mov rax,[rax+0xD0]` | RendererContext vtable +0xD0 = slot 26 = createTexture 0xe8143c0 | [V] |
| 0xbc6a2c2 | - | S: | `0xbc6a2c2  call qword ptr [0xF99FFA0]` | slot-26 vcall issues createTexture | [V] |
| 0xbc6a2c8 | 8 | R: | `0xbc6a2c8  test rax,rax` / `0xbc6a2d1  mov r15,rax` | ID3D12Resource* returned; live capture createtexture_callers: ret=0xBC6A2C8, 25 hits | [V] [V live] |

Handle flow [V + I]: createTexture returns ID3D12Resource* (dispatcher stores it in the handle record) -> handle u16 -> sub_c296b50 stores it at dragon object +0x0 (`0xc296e26 mov [rdi],ax` [V]) -> sub_bc41420 copies the dragon object block to its out ptr (`0xbc41cb9 movdqu [rdi],xmm0` [V] ...) -> sub_4e061b0 copies the out ptr into the MC-side texture object (`0x4e061ce movups [rcx],xmm0` [V]) — handle at MC object +0x0, width/height at +0x10, ready flag at +0x40 [I field roles].

### (3) Static limits and SDK layout checks (new angles tried, this session)

| offset | size | access | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x4e05e50 (xref+imm) | - | - | - | xref.py callers 0x4e05e50 = EMPTY / imm 0x4e05e50 = 0 hits: no static call and no data-section reference to the chain entry | [V] |
| 0xbc41420 | - | - | - | xref.py callers 0xbc41420 = 0x4e05e50 (+0x224): one static caller, MC root 0x4e05e50 | [V] |
| capture dragon_texture_caller_bc41420 | - | - | - | CALLER ret=0x4E05F7C; hits=372, samples=17: every live call returns to `0x4e05f77 call 0xBC41420` (+1 insn) | [V live] |
| 0x4e061b0 | - | - | - | 9 static callers: 0x4e05e50, 0x4e06430, 0x4e067c0, 0x4e06a90, 0x56be030, 0x5aba280, 0x64f14f0, 0x67cb9a0, 0xc295880 (all at +0x221/+0x224): same MC-root family, none is texgroup_load/texload | [V] |
| src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h | 32 | - | - | two shared_ptr members (+0x0 mClientTexture, +0x10 mResourceLocationPtr); static_assert sizeof == 32; does NOT match the destination struct (handle+desc block +0x0, w/h +0x10, ready byte +0x40) | [I] |
| src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h | empty | - | - | struct ClientTexture {}; empty stub carrier, never built from game | [I] |
| src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h | 48 | - | - | three shared_ptr members (+0x0/+0x10/+0x20); static_assert sizeof == 48; does NOT match the destination struct | [I] |

## Interpretations ([I] notes, not row claims)

- sub_bc41420 = per-mip-level GPU upload driver: reads the source texture object (type/width at [rsi+0x0], height at [rsi+0x4], halved each level via `0xbc4156a shr edx,1` / `0xbc4156e shr r8d,1`; mip count at [rsi+0x14]; entry array at [rsi+0x40]/[rsi+0x48] with 0x30-stride entries), calls the dragon texture-object init per level (`0xbc41b39 call 0xC296B50`), writes handle+desc block + width/height + ready flag to its out pointer.
- The destination object of sub_4e061b0 is an internal texture object (handle+desc block at +0x0, width/height qword at +0x10, ready byte at +0x40; name string at +0x18 seen in its release path). Its class name is not instruction-visible: it matches none of the SDK stubs (TexturePtr 32B two shared_ptrs; ClientTexture empty; BedrockTexture 48B three shared_ptrs), so "TexturePtr/ClientTexture" specifically is [I], not [V].
- MC root 0x4e05e50, the entry of the now-[V]-proven pack->GPU chain, is reached only via indirect call/vtable from Minecraft texture code: xref.py callers EMPTY and imm 0 hits (tried as the new angle, failed). The link texgroup_load 0x5421c90 / texload 0x58a1310 -> 0x4e05e50 is not statically provable.

## What I tried that failed (new angles, not redone)

- xref.py callers 0x4e05e50 = EMPTY [V]; imm 0x4e05e50 = 0 hits [V]: no static caller, no data-section reference to the MC-side chain entry.
- xref.py callers of sub_4e061b0 -> 9 static callers, all in the same MC-root family (0x4e05e50, 0x4e06430, 0x4e067c0, 0x4e06a90, 0x56be030, 0x5aba280, 0x64f14f0, 0x67cb9a0, 0xc295880), none is texgroup_load/texload [V].
- SDK layout check: TexturePtr/ClientTexture/BedrockTexture stubs do not match the destination struct layout, so the receiving object's class name cannot be confirmed from the disassembly [I].
- All previously failed angles (r2-r6): xref.py callers 0xe8143c0 EMPTY; `imm 0x0E` scan found no `mov byte ptr [mem], 0x0E`; command-buffer writers hardcode other opcodes; texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10) never calls createTexture or any wrapper; texload 0x58a1310 / texload_task 0x541bf00 have no static callers; texgroup_load does not call them.

## CLOSES?

NO — blocking fact: the createTexture issuance and the GPU-handle write into the texture object are now [V]-proven end to end (producer sub_bc73770 writes command byte 0x0E `0xbc73aaa mov byte ptr [rbp+0x2C],0xE`; wrappers 0xbc73bf0/0xbc73ed0/0xbc74120; dispatcher default path `0xbc6a2ae mov rax,[rcx]` / `0xbc6a2b1 mov rax,[rax+0xD0]` / `0xbc6a2c2 call qword ptr [0xF99FFA0]`; live ret=0xBC6A2C8 [V live]; sub_c296b50 stores the handle at [obj+0x0] `0xc296e26 mov [rdi],ax` [V]; sub_bc41420 copies the dragon result to its out ptr `0xbc41cb9 movdqu [rdi],xmm0` / `0xbc41cd9 mov [rdi+0x18],rax` / `0xbc41cfd mov byte ptr [rdi+0x40],1` [V]; sub_4e061b0 copies it into the MC-side texture object `0x4e061cb movups xmm0,[rdx]` / `0x4e061ce movups [rcx],xmm0` (handle at +0x0) / `0x4e061c7 mov [rcx+0x10],r8` (width/height) / `0x4e062bb mov byte ptr [rcx+0x40],1` (ready) [V]; MC root calls sub_bc41420 at `0x4e05f77 call 0xBC41420`, live capture ret=0x4E05F7C [V live]). BUT the chain entry 0x4e05e50 has no static caller and no data-section reference (xref.py callers EMPTY [V], imm 0 hits [V]), so the hop from Minecraft texgroup_load 0x5421c90 / texload 0x58a1310 into this chain cannot be proven statically, and the destination object of sub_4e061b0 cannot be identified as TexturePtr/ClientTexture from the disassembly (SDK stubs checked [I]). The sampler half (6ax) [V] and the D3D12 backend texture-management chain [V] are already proven (r1 Tables 1-8); atlas stitchers remain open items L8a/L8b (oc_U-EL8a/oc_U-EL8b). The pending half of L7e therefore cannot be closed by this unit.

## TOOL REQUESTS

- capture dragon_texture_caller_bc41420 (rva=0xBC41420): completed by the orchestrator (17 samples, all CALLER ret=0x4E05F7C) [V live]; cited above. No further requests.
