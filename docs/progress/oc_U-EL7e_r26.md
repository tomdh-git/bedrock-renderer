## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): "- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending". Half 1 (sampler flag decode + sampler cache, 6ax) is closed [V] (docs/functions/e820500.md, SamplerFlags.h static_asserts). Half 2 (texture/atlas management) is the pending part — this unit's work is the single remaining blocker: the [0xF99FFA0] runtime function pointer.

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only. No re-runs of input data already computed by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [I] inferred, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from prior verified files / live captures)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750.
- createTexture issuance chain proven LIVE (captures already read, not re-queued): createtexture_callers (0xe8143c0) ONE caller ret=0xBC6A2C8 [V live]; bgfx_createtexture_producer (0xbc73770) writes cmd byte 0x0E [V r4]; bgfx_texture_wrapper_bc73bf0 ONE caller ret=0xC296D7E in dragon entry 0xc296b50 [V live]; dragon_texture_entry_c296b50 ONE caller ret=0xBC41B3E [V live]; handle store [texture_obj+0x00] at 0xc296e26, caller sub_bc41420 (call at 0xbc41b39) [V live]; dragon_texture_caller_bc41420 ONE caller ret=0x4E05F7C = Minecraft-side code [V live]. Full chain [V live]: 0x4E05F7C -> sub_bc41420 (call at 0xbc41b39) -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (writes cmd 0x0E) -> bgfx dispatcher -> createTexture 0xe8143c0. sub_4e05e50 takes a TexturePtr* (matches sdk TexturePtr.h) [V r15].
- r2 (not redone): xref.py callers 0xe8143c0 = EMPTY; createTexture only reachable via indirect [vptr+0xD0] / bgfx cmd byte 14.
- texgroup_load 0x5421c90 -> cache 0x18718d0 at `0x54227af  call 0x18718D0` [V] (r2); both texgroup_load and sub_4e05e50 have 0 static xrefs.

## This session — resolve [0xF99FFA0] (the only remaining work)

Question: does [0xF99FFA0] hold sub_4e05e50 (0x4E05E50), which would close the static texgroup_load -> sub_4e05e50 link? Result: NO — [0xF99FFA0] is a read-only `.rdata` static holding the `jmp rax` thunk sub_eea6040 (0xEEA6040), never written by code, and NOT sub_4e05e50. texgroup_load contains no reference to 0x4E05E50 at all.

## Table 1 — [0xF99FFA0] resolution

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| [0xF99FFA0] read as call target | 0xF99FFA0 | 8 | R: `0x5421d63  call qword ptr [0xF99FFA0]` | texgroup_load calls through the [0xF99FFA0] thunk (rdis data xref `[data_f99ffa0] = sub_eea6040`) | indirect-call thunk target | [V] |
| thunk body | 0xEEA6040 | 5 | E: `0xEEA6040  jmp rax` | [0xF99FFA0] holds sub_eea6040, a jmp-rax thunk | thunk jumps to rax | [V] |
| [0xF99FFA0] read as jmp target | 0xF99FFA0 | 8 | R: `0x9bc8cb  jmp qword ptr [0xF99FFA0]` | another code site reads [0xF99FFA0] as an indirect target | [0xF99FFA0] only ever read, never written | [V] |
| [0xF99FFA0] static bytes | 0xF99FFA0 | 8 | - | file bytes at offset 0xF99FFA0 = 0x14EEA6040 (= image base 0x140000000 + sub_eea6040 0xEEA6040) | statically holds sub_eea6040, NOT sub_4e05e50 | [V] |
| store hunt | .text | - | - | `xr 0xF99FFA0 --max 400000`: 400000 code refs, zero `mov [0xF99FFA0],...` store destinations (only reads and two `jmp [0xF99FFA0]`) | no code writer exists | [V] |
| section writability | .rdata | - | - | rdis `sec`: `.rdata rva 0xeec8000 vsize 0x3441284 flags 0x40000040` (MEM_READ, no MEM_WRITE) | [0xF99FFA0] in read-only .rdata, cannot be patched at runtime | [V] |

## Interpretation ([I] note, not a row claim)

- `call qword ptr [0xF99FFA0]` = `call sub_eea6040` = `jmp rax`: code materializes the real target in rax, so [0xF99FFA0] is a shared indirect-call thunk, not a per-function pointer. The actual runtime target (e.g. sub_4e05e50) would be loaded into rax from somewhere else; [0xF99FFA0] itself is constant sub_eea6040.
- [0xF99FFA0] is read-only (.rdata) and holds sub_eea6040 ≠ sub_4e05e50 (0x4E05E50). texgroup_load has no 0x4E05E50 reference. Therefore the theorized static link `texgroup_load -> [0xF99FFA0] -> sub_4e05e50` does NOT exist; [0xF99FFA0] is not the bridge to sub_4e05e50.

## CLOSES?

NO — blocking fact: [0xF99FFA0] is a read-only `.rdata` static holding sub_eea6040 (0xEEA6040), a `jmp rax` thunk; it is never written by code (xr: 400000 code refs, zero stores) and is NOT sub_4e05e50 (0x4E05E50), and texgroup_load (0x5421c90) references 0x4E05E50 nowhere. So the static pack->GPU link texgroup_load -> sub_4e05e50 via [0xF99FFA0] is invalid and the MC-side GPU handle write remains without a [V]-proven instruction path from texgroup_load. Half 1 (sampler, 6ax) [V] and the D3D12 backend chain [V] and the live issuance chain through sub_4e05e50 -> ... -> createTexture [V live] are proven, but the static texgroup_load->sub_4e05e50 hop is not, so the pending texture/atlas-management half of L7e is not closed by this unit.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly of the 1.26.62.01 exe; [0xF99FFA0] bytes read via a one-off python PE parse, no throwaway scripts left behind; no new helper scripts needed).
