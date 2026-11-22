## NEXT
DONE

UNIT U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"
Output file: docs/progress/oc_U-EL7e.md (only this file)
Source checklist line: docs/RENDER_CHECKLIST.md:338
Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.
Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred / [?] unknown or not located.
Row rule: one annotated row per distinct offset, all its read/store sites listed; name | rva or offset | size | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1, call 5, jmp 2, nop/push 1). No input data pasted as-is; no skipped offsets; no raw instruction dumps outside tables.

================================================================================
1. ANSWER TABLE — pending work resolved this session
================================================================================

The pending part was the createTexture issuance root and the indirect-call target: who produces bgfx
command byte 0x0E, how the returned handle reaches TexturePtr/ClientTexture, and what rax holds at
the [0xF99FFA0] trampoline jmp. Every quoted `0xRVA  instr` below is verified against a fresh rdis
disassembly of the 1.26.62.01 exe (verify_oc clean) or against the provided live capture logs.

| name | rva or offset | size | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| trampoline entry | 0xEEA6040 | 2 | `0xEEA6040  jmp rax` | CFG indirect-call trampoline; tail-calls the function pointer currently in rax | [V] |
| [0xF99FFA0] cell read | [0xF99FFA0] | 8 | `0x1289490  call qword ptr [0xF99FFA0]` | every indirect virtual call goes through this read-only cell; rdis labels it [data_f99ffa0] = sub_eea6040 | [V] |
| [0xF99FFA0] initializer | 0xF99FFA0 | 8 | - | PE .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040; cell holds the trampoline, NOT sub_4e05e50 | [V] |
| no cell writer | 0xF99FFA0 | 8 | - | .text store scan for stores to [0xF99FFA0] = 0 hits; .rdata section flags 0x40000040 (read-only), so it is never rewritten (r37) | [V] |
| sub_12893d0 array begin | 0x1289406 | 8 | `0x1289406  mov r13,[rcx]` | [this+0] = entry-array begin loaded as walk cursor r13 | [V] |
| sub_12893d0 array end | 0x1289409 | 8 | `0x1289409  mov r14,[rcx+8]` | [this+8] = entry-array end | [V] |
| sub_12893d0 entry load | 0x1289431 | 8 | `0x1289431  mov rcx,[r13+8]` | rcx = entry[+8] (refcounted object) | [V] |
| sub_12893d0 refcount inc | 0x1289447 | 4 | `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment of entry[+8] (retry loop at 0x1289440) | [V] |
| sub_12893d0 texture obj load | 0x128947d | 8 | `0x128947d  mov rcx,[r13+0x10]` | entry[+0x10] = texture object loaded as `this` for the indirect call | [V] |
| sub_12893d0 vptr load | 0x1289486 | 8 | `0x1289486  mov rax,[rcx]` | rax = vptr of entry[+0x10] | [V] |
| sub_12893d0 vtable[1] load | 0x1289489 | 8 | `0x1289489  mov rax,[rax+8]` | rax = vtable[1] = indirect-call target | [V] |
| sub_12893d0 indirect call | 0x1289490 | 5 | `0x1289490  call qword ptr [0xF99FFA0]` | tail-call through trampoline; push ret = 0x1289496; mc_root capture: 15/15 hits ret=0x1289496 => target = sub_4e05e50 | [V] [V live] |
| sub_12893d0 ret site | 0x1289496 | 1 | `0x1289496  nop` | instruction right after the indirect call = observed capture ret value | [V live] |
| sub_12893d0 NULL entry | 0x128949b | 8 | `0x128949b  mov qword ptr [r13+0x10],0` | NULLs entry[+0x10] after the call | [V] |
| sub_12893d0 release | 0x12894b3 | 5 | `0x12894b3  call qword ptr [0xF99FFA0]` | releases old object via vtable[0] | [V] |
| sub_4e05e50 entry | 0x4E05E50 | 1 | `0x4E05E50  push rbp` | sub_4e05e50 / mc_root entry; MC-side pack->GPU root; `xref.py callers 0x4E05E50` = EMPTY (0 static callers) | [V] |
| sub_4e05e50 this copy | 0x4E05E6E | 8 | `0x4E05E6E  mov rdi,rcx` | rdi = RCX = texture object / TexturePtr* argument | [V] |
| sub_4e05e50 +0x18 read | 0x4E05E71 | 8 | `0x4E05E71  mov rax,[rcx+0x18]` | reads texture_obj+0x18 (old texture object) | [V] |
| sub_4e05e50 old-release call | 0x4E05E86 | 5 | `0x4E05E86  call qword ptr [0xF99FFA0]` | releases old this+0x18 object via vtable[1] through trampoline | [V] |
| sub_4e05e50 sampler flags | 0x4E05F61 | 8 | `0x4E05F61  mov r9,[rdi+0xE0]` | this+0xE0 sampler/flag word (6ax sampler flag) passed as r9 | [V] |
| sub_4e05e50 descriptor addr | 0x4E05F68 | 4 | `0x4E05F68  add rdi,0x58` | rdi = &texture_obj+0x58 = texture creation descriptor | [V] |
| sub_4e05e50 -> sub_bc41420 | 0x4E05F77 | 5 | `0x4E05F77  call 0xBC41420` | issues createTexture via sub_bc41420 (rcx=&this+0x58); call end 0x4E05F7C = LIVE RESULT 5 ret | [V] [V live] |
| sub_4e05e50 call end | 0x4E05F7C | 1 | `0x4E05F7C  nop` | end of call 0xBC41420 = observed LIVE RESULT 5 ret=0x4E05F7C | [V live] |
| sub_4e05e50 skip path | 0x4E06010 | 8 | `0x4E06010  mov qword ptr [rsi],0` | output handle slot cleared to 0 when nothing to create | [V] |
| sub_bc41420 -> dragon entry | 0xBC41B39 | 5 | `0xBC41B39  call 0xC296B50` | sub_bc41420 -> dragon entry 0xc296b50; ret site 0xBC41B3E = LIVE RESULT 4 ret | [V] [V live] |
| bgfx dispatcher vtable load | 0xBC6A28F | 8 | `0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` | dispatcher: rcx = renderer-context vtable pointer | [V] |
| bgfx dispatcher vtable | 0xBC6A2AE | 8 | `0xBC6A2AE  mov rax,[rcx]` | rax = renderer-context vtable | [V] |
| bgfx dispatcher slot 26 | 0xBC6A2B1 | 8 | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = vptr[slot 26] = createTexture address 0xe8143c0 | [V] |
| bgfx dispatcher indirect call | 0xBC6A2C2 | 5 | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | indirect vcall -> createTexture 0xe8143c0 | [V] [V live] |
| createTexture entry | 0xE8143C0 | 1 | `0xE8143C0  push rbp` | slot-26 createTexture; no static caller (`xref.py callers 0xe8143c0` = EMPTY) | [V] |
| createTexture -> TextureD3D12::create | 0xE81455B | 5 | `0xE81455B  call 0xE81BF30` | createTexture -> backend TextureD3D12::create | [V] |
| backend ret site | 0xE814560 | 1 | `0xE814560  nop` | ret site after call 0xE81BF30 = l8b_texcreate_record capture CALLER ret=0xE814560 | [V live] |
| returned handle call | 0xC296E1A | 5 | `0xC296E1A  call 0xBC74120` | ax = returned u16 bgfx handle | [V] |
| handle store | 0xC296E26 | 2 | `0xC296E26  mov [rdi],ax` | returned u16 handle stored at [texture_obj+0x00] | [V] |
| descriptor copy 1 | 0xC296E2D | 16 | `0xC296E2D  movups xmm0,[r12]` | 0x1C create descriptor load (16 B movups) | [V] |
| descriptor copy 2 | 0xC296E32 | 16 | `0xC296E32  movups [rdi+8],xmm0` | descriptor copied to texture object +0x08 (16 B movups) | [V] |
| descriptor ptr store | 0xC296E3B | 8 | `0xC296E3B  mov [rdi+0x18],rdx` | descriptor pointer stored at texture object +0x18 | [V] |
| static caller sub_6632bf0 | 0x6632C55 | 5 | `0x6632C55  call 0x12893D0` | sub_6632bf0 "Deferred Texture Transactions" -> sub_12893d0 (deferred-txn queue dispatch) | [V] |
| static caller sub_1145c20 | 0x1145D5A | 5 | `0x1145D5A  call 0x12893D0` | sub_1145c20 -> sub_12893d0 | [V] |
| sub_66232b0 -> sub_6632bf0 | 0x66233AE | 5 | `0x66233AE  call 0x6632BF0` | sub_66232b0 (runtime root, 0 static callers) -> sub_6632bf0 | [V] |

================================================================================
2. CHAIN SUMMARY (cited from prior rounds, not redone)
================================================================================

Resolved pending parts:
- Indirect caller of sub_4e05e50 = sub_12893d0 (entry 0x12893D0), call site 0x1289490, fall-through 0x1289496. mc_root_4e05e50_callers.txt: 15/15 hits ret=0x1289496 => entry[+0x10]->vtable[1] = sub_4e05e50 at runtime [V live]. RCX = vptr-bearing ClientTexture-class heap objects (name fields "tex"/"legs"/"_spear"/"hud"/"mary") = TexturePtr::mClientTexture pointee, not the 32B TexturePtr stub [V live]. So rax at the [0xF99FFA0] trampoline jmp = sub_4e05e50 (0x4E05E50) [V live]. This resolves the r37 pending item (decode rax at the jmp); static work on [0xF99FFA0] is exhausted (read-only .rdata initializer, no writer).
- sub_4e05e50 fully decoded: releases old texture at this+0x10/+0x18 via vtable calls through [0xF99FFA0], then builds a GPU texture from the descriptor at this+0x58 with sampler/flags from this+0xE0 and issues it via `0x4E05F77  call 0xBC41420` (call ends 0x4E05F7C = LIVE RESULT 5 ret [V live]) -> sub_bc41420 -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> producer sub_bc73770 (writes bgfx command byte 0x0E) -> bgfx dispatcher (vptr[slot 26] = createTexture 0xe8143c0) -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30 [V live + dis].
- Handle trace into texture object / TexturePtr: returned u16 handle stored at [texture_obj+0x00] at 0xC296E26 [V]; descriptor copied to texture_obj+0x08/+0x18; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58` [V]); sdk TexturePtr/ClientTexture headers [V file read].

Already proven in prior rounds (cited, not re-derived):
- sampler flag decode + sampler cache (6ax): docs/functions/e820500.md + src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h [V].
- D3D12 backend texture-management chain: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (slot 26), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750 [V].
- createTexture issuance end-to-end below sub_4e05e50 [V live]: producer sub_bc73770 writes cmd byte 0x0E; dispatcher case -> createTexture 0xe8143c0; createtexture_callers.txt ONE caller ret=0xBC6A2C8 [V live].

Angles tried that FAILED (do not redo):
- [0xF99FFA0] code-writer search: 0 hits; cell is a read-only .rdata PE initializer holding sub_eea6040, never rewritten.
- xref.py callers 0x4E05E50 = EMPTY; callers 0x5421C90 (texgroup_load) reach only texture-cache/resource calls (sub_18718d0 at 0x54227AF, sub_5424000, sub_5424130); none enters sub_4e05e50.
- sub_66232b0 (the deferred-txn root that calls sub_6632bf0 -> sub_12893d0) has 0 static code callers; its only reference is the .rdata vtable pointer at 0xF2BDF40 (virtual dispatch target, class not named). It is the runtime job-system root, not statically reachable from texgroup_load.
- rdis immediate scan for vtable 0xF215838 (slot 1 = sub_4e05e50) = 0 hits; no static store of that vptr.

================================================================================
3. CLOSES?
================================================================================

NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. texgroup_load's static callees terminate at the async texture cache / ResourceLoadManager enqueue (0x71BC70); the hop into the GPU-upload root is the runtime-only deferred-txn chain sub_66232b0 (0 static callers) -> sub_6632bf0 -> sub_12893d0 -> indirect vptr[1] call through [0xF99FFA0] -> sub_4e05e50, which IS observed live [V live] (mc_root_4e05e50_callers.txt 15/15 hits ret=0x1289496) but is not a static call edge and cannot be closed by static analysis. Everything else in L7e is [V]-[V live]-proven: Half 1 sampler flag decode + cache (6ax), Half 2a D3D12 backend texture-management chain, createTexture issuance below sub_4e05e50, handle trace into TexturePtr/ClientTexture. Atlas stitchers (L8a/L8b) remain separate open units (oc_U-EL8a/oc_U-EL8b), not this unit.

================================================================================
4. TOOL REQUESTS
================================================================================

None — all instruction lines taken verbatim from fresh rdis disassembly of the 1.26.62.01 exe and verified with tools/sigs/verify_oc.py; live captures read from docs/data/live/*.txt; TexturePtr headers read from src tree; no helper scripts written; scratch dis_*.txt files removed.

## NEXT
step 2
