## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables.

## Already proven (prior sessions r1-r22 — NOT redone, cited only; not re-quoted here)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture 0xe8143c0 has no static caller, reached only via indirect [vptr+0xD0] thunks.
- r3 (not redone): texload 0x58a1310 and texload_task 0x541bf00 have EMPTY static caller lists and are never called by texgroup_load — the item-line sub-chain texgroup_load->texload->texload_task->0x18718d0 is NOT statically supported as written.
- 0x18718d0 fully decoded [V pre/0x18718d0_fn.md, not redone]: cache lookup loop; on miss builds an object with vtable 0xEFCA680 and calls completion 0x186dac0; never calls sub_4e05e50 or sub_12893d0.
- r4/r5 (not redone): command-byte-14 producer = sub_0xbc73770 writes 0x0E into the bgfx command buffer [V]; reached only via thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V]; MC texture code calls none statically [V xref evidence].
- sdk headers [V file read]: TexturePtr.h `static_assert(sizeof(TexturePtr) == 32)`, mClientTexture +0x00 / mResourceLocationPtr +0x10 (two shared_ptr); ClientTexture empty struct; BedrockTexture.h `static_assert(sizeof(BedrockTexture) == 48)`.
- Full live chain [V live] (capture logs read-only inputs): sub_12893d0 tail-calls sub_4e05e50 (ret=0x1289496, all 32 samples in docs/data/live/mc_root_4e05e50_callers.txt); sub_4e05e50 -> sub_bc41420 (ret=0x4E05F7C, dragon_texture_caller_bc41420.txt); sub_bc41420 -> 0xc296b50 (ret=0xBC41B3E, dragon_texture_entry_c296b50.txt); 0xc296b50 -> wrapper 0xbc73bf0 (ret=0xC296D7E); wrapper -> producer 0xbc73770 (command-byte-0x0E); producer -> bgfx dispatcher case 0xBC6A2C2 -> createTexture 0xe8143c0 (ret=0xBC6A2C8, createtexture_callers.txt) -> 0xE81455B call 0xE81BF30 TextureD3D12::create (ret=0xE814560, l8b_texcreate_record.txt). Returned handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V dis]; texture_obj = TexturePtr+0x58 [V].

## Pending work this session (per 2026-11-22 r22: STOP re-proving the chain)

Resolve the pointer in [0xF99FFA0] (vtable/runtime fn ptr slot used by `0x1289490 call qword ptr [0xF99FFA0]` in sub_12893d0 and `0xBC6A2C2 call qword ptr [0xF99FFA0]` in the bgfx dispatcher): locate its writer (xref to 0xF99FFA0 as a store) and name the function it is set to; if that is sub_4e05e50 the static link texgroup_load(0x5421c90) -> sub_4e05e50 is closed.

## [0xF99FFA0] — data slot, readers and writer search (all instruction lines re-verified via rdis this session)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| [0xF99FFA0] slot contents | RVA 0xF99FFA0 (.rdata, file off 0xF99E9A0) | 8 | [0xF99FFA0] | - | file bytes read as u64 LE = 0x14EEA6040 = absolute VA of sub_eea6040; .rdata characteristics 0x40000040 = read-only initialized data, no IMAGE_SCN_MEM_WRITE, so no runtime store writer exists; the value is a link-time constant | [V] + [I no writer] |
| sub_12893d0 vtable[1] load into RAX | 0x1289489 | 8 | [rax+8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = the indirect-call target passed in RAX to the trampoline | [V] |
| sub_12893d0 indirect tail-call via slot | 0x1289490 | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | calls the [0xF99FFA0] trampoline slot (target in RAX); ret site 0x1289496 = live capture ret=0x1289496 (all 32 samples) | [V] + [V live] |
| sub_12893d0 release indirect call via slot | 0x12894B3 | 8 | [0xF99FFA0] | `0x12894B3  call qword ptr [0xF99FFA0]` | same trampoline slot used for the release vptr[0] call | [V] |
| bgfx dispatcher vtable[26] load | 0xBC6A2B1 | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = slot 26 = createTexture 0xe8143c0 (BGFX_MAP line 403) | [V] |
| bgfx dispatcher indirect call via slot | 0xBC6A2C2 | 8 | [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | calls the same trampoline slot (target in RAX = createTexture); ret site 0xBC6A2C8 = live capture ret=0xBC6A2C8 | [V] + [V live] |
| trampoline target of [0xF99FFA0] | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | [0xF99FFA0] content = this address; tail-jumps to whatever is in RAX | [V] |

## Finding

[0xF99FFA0] has NO code writer. It is a statically-initialized .rdata slot: its 8 bytes read as u64 LE 0x14EEA6040, which is exactly the absolute VA of sub_eea6040 (image base 0x140000000 + RVA 0xEEA6040), confirmed both by raw file bytes at file offset 0xF99E9A0 and by rdis dis of sub_eea6040 (`0xEEA6040  jmp rax`). .rdata characteristics 0x40000040 grant no write permission, so a runtime `mov [0xF99FFA0], ...` store cannot exist; every code reference to the slot is a load (`call qword ptr [0xF99FFA0]`), and the real callee is passed in RAX (obj->vptr[1] in sub_12893d0; vtable slot 26 in the dispatcher). Therefore [0xF99FFA0] is set to sub_eea6040, NOT sub_4e05e50.

## CLOSES?

NO — blocking fact: [0xF99FFA0] = sub_eea6040 (the `jmp rax` trampoline), not sub_4e05e50, and no store writer exists (.rdata read-only, link-time constant [V raw bytes + section characteristics]). Per the hint's own condition ("if that is sub_4e05e50 the static link is closed"), the static link texgroup_load(0x5421c90) -> sub_4e05e50 remains UNPROVEN: sub_4e05e50 has 0 static xrefs (`rdis callers 0x4E05E50` -> 0 calling functions, fn 0x4E05E50..0x4E06074 [V]); sub_12893d0 is reached only via its indirect vtable[1] tail-call `0x1289490 call qword ptr [0xF99FFA0]` (capture ret site 0x1289496 [V live]); sub_12893d0's 4 static callers (sub_1145c20, sub_6622610, sub_66232b0, sub_6632bf0 [V]) none is texgroup_load/texload/texload_task and all upward chains dead-end at 0-static-caller functions [V r19]; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` [V] and cache 0x18718d0 builds vtable-0xEFCA680 objects which never call sub_4e05e50 [V r19]. Everything else in the item is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0] -> createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2) [V], texture_obj = TexturePtr+0x58 [V], sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. All new evidence from rdis dis of 0x1289470-0x12894C0, 0xBC6A2A0-0xBC6A2D0 and 0xEEA6040 plus raw file bytes at RVA 0xF99FFA0 (file offset 0xF99E9A0); rdis and section-header parse via shell (tools.rtools.* banned). Live capture logs are read-only inputs; no capture requested because the slot is read-only data, so no runtime trace can add a writer.
