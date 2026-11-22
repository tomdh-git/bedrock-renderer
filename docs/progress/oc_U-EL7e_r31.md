## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator inputs. The two live inputs for this session were read in full: docs/data/live/mc_root_4e05e50_callers.txt (CALLER ret=0x1289496, 32 samples) and docs/data/live/l8b_texcreate_record.txt (CALLER ret=0xE814560, 24 samples) — both recapitulate chains already proven in r1-r30; nothing in them is redone here.

Tags: [V] saw in disassembly (verbatim line quoted, RVA cited) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte/nop 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no catch-all or ellipsis rows.

## Already proven (cited from r1-r30; NOT re-decoded this session)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture has no static caller (`xref.py callers 0xe8143c0` EMPTY [V r2]); reached only via indirect RendererContext [vptr+0xD0] slot 26 = 0xe8143c0 (BGFX_MAP line 403).
- MC-side chain [V live + dis]: texture job object (vtable 0xF215838, slot 1 = sub_4e05e50) constructed by sub_4e05450 (`0x4E05654  mov [rbx],r8` stores vptr; `0x4E0573A  mov [rbx+0xE0],rax` stores renderer ctx; `0x4E05689  movups [rbx+0x58],xmm1` inits texture sub-object) -> sub_12893d0@`0x1289490  call qword ptr [0xF99FFA0]` (tail-call through trampoline [0xF99FFA0] = sub_eea6040 `jmp rax`; live ret site `0x1289496  nop` = ret=0x1289496 in all 32 samples [V live]) -> sub_4e05e50 (`0x4E05F77  call 0xBC41420`, return site `0x4E05F7C  nop` [V live]) -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> command-byte-0x0E producer 0xbc73770 [V r4] -> bgfx dispatcher case 0xBC6A2C2 -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (live ret site 0xE814560 [V live]). Returned handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V]; texture_obj = TexturePtr+0x58 via `0x4E05F68  add rdi,0x58` [V]; sdk TexturePtr/ClientTexture [V file read: sizeof(TexturePtr)==32, mClientTexture +0x00 / mResourceLocationPtr +0x10, ClientTexture empty, sizeof(BedrockTexture)==48].

## Directed work this session (r22 pending item): resolve the writer of [0xF99FFA0] — CLOSED NEGATIVE

Question: is [0xF99FFA0] written by code and set to sub_4e05e50 (0x4E05E50)? If yes, the static link texgroup_load(0x5421c90) -> sub_4e05e50 closes.

Findings (all re-verified verbatim via rdis this session unless cited [V r1-r30]):

1. Static slot contents: the on-disk qword at RVA 0xF99FFA0 = 0x14EEA6040 = imagebase 0x140000000 + RVA 0xEEA6040 = the absolute address of sub_eea6040 [V: PE section parse; RVA lies in section .rdata (vaddr 0xEEC8000), section chars 0x40000040 = read-only, NO MEM_WRITE (0x80000000), so the slot cannot be patched at runtime]. Every rdis disassembly of a load site annotates `; [data_f99ffa0] = sub_eea6040` [V: dis at 0xBC6A2C2, 0x1289490, 0x5421D63]. The slot is NOT sub_4e05e50 (0x4E05E50).
2. `rdis imm 0xF99FFA0` -> 0 hit(s): no instruction materializes the immediate 0xF99FFA0 (no `mov`/`lea` setup of the address that could precede a store) [V].
3. ripscan of .text for 0xF99FFA0 yields hundreds of sites; every disassembled site is a read (`call qword ptr [0xF99FFA0]` or `jmp qword ptr [0xF99FFA0]`); zero store destinations [V]. Spot-verified read sites:
   - `0xEEA6060  jmp qword ptr [0xF99FFA0]` (trampoline second entry)
   - `0xBC6A2C2  call qword ptr [0xF99FFA0]` (dispatcher vcall; rax = [vptr+0xD0] loaded by `0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0)
   - `0x1289490  call qword ptr [0xF99FFA0]` (sub_12893d0 obj->vptr[1] tail-call; live ret site `0x1289496  nop` [V live])
   - `0x12894B3  call qword ptr [0xF99FFA0]` (object release through the same trampoline)
   - `0x5421D63  call qword ptr [0xF99FFA0]` (texgroup_load: rax = [0x1233E1A8]->vptr[1] via `0x5421D45  mov rcx,[0x1233E1A8]` / `0x5421D4C  mov rax,[rcx]` / `0x5421D4F  mov rax,[rax+8]`, then `0x5421D72  mov rcx,rax`; this is the GLOBAL ALLOCATOR's vtable[1] = allocate(size), NOT sub_4e05e50) [V]
4. Trampoline body: `0xEEA6040  jmp rax` — it jumps to whatever rax holds; [0xF99FFA0] itself is never the target value [V].

Conclusion: [0xF99FFA0] has NO writer; it is read-only .rdata, statically holds the sub_eea6040 trampoline, is never set to sub_4e05e50, and texgroup_load's use of it is an allocator allocate(size) call via [0x1233E1A8] vtable+8 — not a texture create. The r22 closure condition (slot set to sub_4e05e50) is NOT met. Static issuance of createTexture from MC texture code remains unreachable (0 static callers of 0xe8143c0; reached only through the indirect [vptr+0xD0] vcall). No further static angle exists; the bind texgroup_load -> sub_4e05e50 is runtime-only (object vptr+8 = sub_4e05e50 via vtable 0xF215838 slot 1, tail-called through trampoline [0xF99FFA0]), observed live [V live].

## Table — [0xF99FFA0] resolution: trampoline, read sites, section (verified verbatim via rdis this session)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| [0xF99FFA0] read sites (merged) | 0xF99FFA0 | 8 | [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` / `0x1289490  call qword ptr [0xF99FFA0]` / `0x12894B3  call qword ptr [0xF99FFA0]` / `0x5421D63  call qword ptr [0xF99FFA0]` | four read sites: dispatcher vcall, sub_12893d0 tail-call, release, texgroup_load allocator call — all through the shared trampoline; no store site exists | [V] + [V live] |
| dispatcher slot-26 load | [rax+0xD0] | 8 | [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | loads vtable slot 26 into rax = createTexture address (0xe8143c0 per BGFX_MAP line 403) | [V] |
| dispatcher result test | 0xBC6A2C8 | 4 | - | `0xBC6A2C8  test rax,rax` | tests createTexture result/handle | [V] |
| trampoline entry | 0xEEA6040 | 2 | E | `0xEEA6040  jmp rax` | trampoline: jumps to rax; real target materialized by caller | [V] |
| trampoline second entry | 0xEEA6060 | 8 | [0xF99FFA0] | `0xEEA6060  jmp qword ptr [0xF99FFA0]` | second entry jumps through same global slot | [V] |
| texgroup_load global object load | [0x1233E1A8] | 8 | [0x1233E1A8] | `0x5421D45  mov rcx,[0x1233E1A8]` | rcx = global object pointer at [0x1233E1A8] | [V] |
| texgroup_load vptr load | [rcx] | 8 | [rcx] | `0x5421D4C  mov rax,[rcx]` | rax = object vptr | [V] |
| texgroup_load vtable[1] load | [rax+8] | 8 | [rax+8] | `0x5421D4F  mov rax,[rax+8]` | rax = object->vtable[1] = global allocator allocate(size) target | [V] |

## What I tried that failed (this session)

- Writer hunt for [0xF99FFA0]: `rdis imm 0xF99FFA0` -> 0 hits; ripscan .text for 0xF99FFA0 -> only read sites, zero stores; section .rdata read-only; on-disk qword = sub_eea6040 absolute address. Negative — no writer, slot never = sub_4e05e50.
- Not redone (already exhausted in r1-r30): sub_4e05e50 has 0 static xrefs; sub_12893d0's 4 static callers (sub_6632bf0, sub_1145c20, sub_6622610, sub_66232b0) all dead-end at 0-static-caller functions; sub_4e05450's 16 static callers none is texgroup_load/texload/texload_task; texgroup_load's static chain ends at `0x54227AF  call 0x18718D0` (cache 0x18718d0, vtable 0xEFCA680 objects which never call sub_4e05e50/sub_12893d0); `rdis imm 0x4E05E50` -> 0 hits; TexturePtr* claim for sub_4e05e50's RCX refuted (polymorphic object, constant vptr, reads object+0xE0 [V live + dis]; TexturePtr is 32 bytes non-polymorphic [V file read]).

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 (and therefore none into the createTexture issuance chain). sub_4e05e50 has 0 static xrefs ([V rdis: fn [0x4E05E50..0x4E06074) size 0x224]) and is reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` through the read-only trampoline [0xF99FFA0] = sub_eea6040 `jmp rax` (never written, never = sub_4e05e50 [V this session]); the runtime bind vptr[1]=sub_4e05e50 is live-observed only (ret site `0x1289496  nop` = ret=0x1289496, all 32 samples [V live]). texgroup_load's static chain ends at `0x54227AF  call 0x18718D0` [V] and its [0xF99FFA0] calls are allocator allocate(size) via [0x1233E1A8] vtable+8 [V], not sub_4e05e50; all upward static caller chains dead-end [V rdis/xref]. Everything else in the item IS [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, command-byte-14 producer sub_bc73770 [V r4], dispatcher [vptr+0xD0] -> createTexture 0xe8143c0 [V live + dis], returned handle stored at [texture_obj+0x00] (`0xC296E26  mov [rdi],ax`, size 2, word) [V] with texture_obj = TexturePtr+0x58 [V], sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) remain out of scope (MIRROR_SKIP).

## TOOL REQUESTS

- None. All verification done with rdis dis/imm and ripscan.py (already in tools/sigs); no helper scripts written; no temporary files left behind (ripscan output in %TEMP% only).
