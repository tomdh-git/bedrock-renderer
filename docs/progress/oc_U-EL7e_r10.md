## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; orchestrator live captures read read-only (never touched the game). Capture mc_root_4e05e50_callers (rva 0x4E05E50) is QUEUED by the orchestrator (see tools/livecap/request.py list); result pending in docs/data/live/mc_root_4e05e50_callers.txt.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in an orchestrator live capture (file+line cited), [I] inferred from structure/BGFX_MAP/SDK headers, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (cited from oc_U-EL7e_r1..r8, NOT re-derived)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 of oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (slot 26), updateTexture 0xe814a70 (28), readTexture 0xe8150f0 (30), resizeTexture 0xe815840 (31), override/get/destroy 0xe815c30..0xe815fbf (32-34), destructor 0xe80f290, blit 0xe818bc0 (51), blitSetup 0xe819750 (52); BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- Static negatives (r2-r8, not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] (slot 26 = offset 0xD0); texload 0x58a1310 and texload_task 0x541bf00: xref EMPTY for both; texgroup_load does not call them (its only cache-bound call is `0x54227af call 0x18718d0` [V]); 0x18718d0 decoded as the texture cache (BST this+0x30, ready callback 0x873D0->jmp 0xEEC59D0 via 0x7705B0, async enqueue 0x71BC70 "resource dispatch"); texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10) only swaps live vtables 0xEFCA5A0/5D0/5F0, never calls createTexture [V r2]. Atlas stitchers remain open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.
- Command byte 0x0E producer (r6-r8, not redone): sub_bc73770 writes `0xbc73aaa mov byte ptr [rbp+0x2C],0xE` [V]; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 call it [V xref]; live capture bgfx_createtexture_producer: all 16 hits ret=0xBC73EAD at `0xbc73ea8 call 0xBC73770` in sub_bc73bf0 [V live: docs/data/live/bgfx_createtexture_producer.txt lines 3-35]. `imm 0x0E` scan found NO `mov byte ptr [mem], 0x0E`; command-buffer writers hardcode other opcodes; dispatch table at 0xF449638 obfuscated/indirect. Hint mapping (byte 14 -> 0xbc69487) accepted as verified, consistent with both live captures.
- Handle into dragon texture object (r7-r8, not redone): sub_c296b50 calls sub_bc73bf0 at `0xc296d79 call 0xBC73BF0` [V] and stores the createTexture handle at `0xc296e26 mov [rdi],ax` (dragon texture object +0x0) [V]; width/height at descriptor [r12+0x10] stored to object +0x18 via `0xc296e36 mov rdx,[r12+0x10]` / `0xc296e3b mov [rdi+0x18],rdx` [V]; descriptor block at [r12] via `0xc296e2d movups xmm0,[r12]` copied to object +0x8 via `0xc296e32 movups [rdi+8],xmm0` [V]. Live capture dragon_texture_entry_c296b50: CALLER ret=0xBC41B3E, 6 hits — sub_c296b50 has one static caller, sub_bc41420 at call site 0xbc41b39 [V live + V: docs/data/live/dragon_texture_entry_c296b50.txt line 3].

## Pending target (this unit)

Decode the MC-side pack->GPU root around 0x4E05F7C: sub_4e05e50 (rdis header: [0x4e05e50..0x4e07e50), size 0x2000, 0 xrefs in) passes arg1+0x58 as RCX of sub_bc41420 at `0x4e05f77 call 0xBC41420` (return address 0x4E05F7C = `0x4e05f7c nop`), then copies the dragon-created result into an out block via sub_4e061b0. Connect it to texgroup_load/texload (0x5421c90/0x58a1310) and check the sdk TexturePtr/ClientTexture/BedrockTexture headers. sub_4e05e50 has no static caller (rdis: "0 xrefs in"; xref.py callers EMPTY per r8; imm scan 0 hits) and is invoked only indirectly, so capture mc_root_4e05e50_callers (rva 0x4E05E50, pending) is required to name its caller.

## Table 1 — sub_4e05e50, MC-side pack->GPU root (fresh rdis of the exe)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| function entry | 0x4e05e50 | - | E: | `0x4E05E50  push rbp` | sub_4e05e50 entry; rdis: size 0x2000, 0 xrefs in (no static caller) | [V] |
| arg2 saved | 0x4e05e6b | - | ALU: rsi = rdx | `0x4E05E6B  mov rsi,rdx` | out/release pointer copied to rsi | [V] |
| arg1 = MC object | 0x4e05e6e | - | ALU: rdi = rcx | `0x4E05E6E  mov rdi,rcx` | MC texture object (shared_ptr members at +0x8/+0x10) | [V] |
| source object = arg1 + 0x58 | 0x4e05f68 | - | ALU: rdi += 0x58 | `0x4E05F68  add rdi,0x58` | RCX argument computed for sub_bc41420 | [V] |
| sub_bc41420 RCX arg | 0x4e05f74 | - | ALU: rcx = rdi | `0x4E05F74  mov rcx,rdi` | source texture object passed to the bridge | [V] |
| bridge call | 0x4e05f77 | - | S: | `0x4E05F77  call 0xBC41420` | sub_4e05e50 -> sub_bc41420; live capture returns to 0x4E05F7C [V live] | [V] |
| after call | 0x4e05f7c | - | - | `0x4E05F7C  nop` | return address of the live capture (ret=0x4E05F7C) | [V] |
| out block (stack) | 0x4e05f7d | - | LEA: [rbp-8] | `0x4E05F7D  lea rcx,[rbp-8]` | destination block for the sub_4e061b0 copy | [V] |
| temp block (stack) | 0x4e05f81 | - | LEA: [rbp-0x50] | `0x4E05F81  lea rdx,[rbp-0x50]` | sub_bc41420 out block (handle+desc+w/h) | [V] |
| sub_4e061b0 call | 0x4e05f85 | - | S: | `0x4E05F85  call 0x4E061B0` | copy dragon-created result into out block | [V] |
| out pointer cleared | 0x4e06010 | - | W: [rsi] | `0x4E06010  mov qword ptr [rsi],0` | [arg2] nulled on exit | [V] |

## Table 2 — Live capture: caller of sub_bc41420 and its RCX (docs/data/live/dragon_texture_caller_bc41420.txt)

| name | rva or offset | size | read/store address | verbatim proof | meaning | tag |
|---|---|---|---|---|---|---|
| capture identity | rva=0xBC41420 kind=regs size=0x40 | - | - | docs/data/live/dragon_texture_caller_bc41420.txt line 3: `CALLER ret=0x4E05F7C first_hit=1` | sub_bc41420 called from sub_4e05e50 (`0x4e05f77 call 0xBC41420`; ret=0x4E05F7C = `0x4e05f7c nop`), hits=372 samples=17 (_status.txt DONE t=242) | [V live] |
| RCX = source texture object | RCX@entry | - | R: [rcx+0x00], [rcx+0x14], [rcx+0x18], [rcx+0x28] | docs/data/live/dragon_texture_caller_bc41420.txt line 4: `RCX=531A2FA4958 hit=1 ret=0x4E05F7C 80000000800000001C0000000100000001000000010000007465780000000000000000000000000003000000000000000F000000000000000000000000000000` | object at RCX: +0x00 qword 0x8000000080000000, +0x08 dword 0x1C, +0x14 dword 1 (mip count), +0x18 "tex\0", +0x28 qword 3 (non-null -> passes `0xbc41446 cmp qword ptr [rcx+0x28],0`) | [V live] |
| RCX = source texture object (hit 2) | RCX@entry | - | R: same layout | docs/data/live/dragon_texture_caller_bc41420.txt line 8: `RCX=531A2FA3458 hit=2 ret=0x4E05F7C ...` | same object layout at a different per-object address | [V live] |

Table 2 note: [rcx+0x28]=3 satisfies sub_bc41420's non-null guard; [rcx+0x14]=1 is the mip count read at `0xbc4149f mov eax,[rsi+0x14]` (rsi == rcx on entry per `0xbc4145a mov rsi,rcx`).

## Table 3 — sub_bc41420, pack->GPU bridge (0xbc41420..0xbc43420, size 0x2000, 1 static xref in [V])

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| source+0x28 guard | 0xbc41446 | 8 | R: [rcx+0x28] | `0xBC41446  cmp qword ptr [rcx+0x28],0` | source+0x28 must be non-null, else error path | [V] |
| arg shuffle r15 | 0xbc41451 | - | ALU: r15 = r9 | `0xBC41451  mov r15,r9` | r15 = a3 (a0+0xE0 object) | [V] |
| arg shuffle rbx | 0xbc41454 | - | ALU: rbx = r8 | `0xBC41454  mov rbx,r8` | rbx = saved shared_ptr slot address | [V] |
| arg shuffle rdi | 0xbc41457 | - | ALU: rdi = rdx | `0xBC41457  mov rdi,rdx` | rdi = out block pointer | [V] |
| arg shuffle rsi | 0xbc4145a | - | ALU: rsi = rcx | `0xBC4145A  mov rsi,rcx` | rsi = source object | [V] |
| feature byte | 0xbc4145d | 1 | R: [rcx+0x78] | `0xBC4145D  movzx eax,byte ptr [rcx+0x78]` | source feature byte | [V] |
| second feature byte | 0xbc4146f | 1 | R: [rsi+0x80] | `0xBC4146F  cmp byte ptr [rsi+0x80],0` | second source feature byte | [V] |
| mip count | 0xbc4149f | 4 | R: [rsi+0x14] | `0xBC4149F  mov eax,[rsi+0x14]` | mip level count | [V] |
| entry array start | 0xbc414b3 | 8 | R: [rsi+0x40] | `0xBC414B3  mov rdx,[rsi+0x40]` | entry array start | [V] |
| entry array end | 0xbc414b7 | 8 | R: [rsi+0x48] | `0xBC414B7  mov rcx,[rsi+0x48]` | entry array end | [V] |
| entry count bytes | 0xbc414bb | - | ALU: rcx -= rdx | `0xBC414BB  sub rcx,rdx` | entry array byte length | [V] |
| entry count (stride 0x10 shown here; entries are 0x30 per r8 Table 1) | 0xbc414be | - | ALU: rcx /= 16 | `0xBC414BE  sar rcx,4` | entry count | [V] |
| texture type | 0xbc41559 | 4 | R: [rsi+0x0] | `0xBC41559  mov edx,[rsi]` | texture type dword | [V] |
| width | 0xbc41560 | 4 | R: [rsi+0x4] | `0xBC41560  mov r8d,[rsi+4]` | width dword | [V] |
| type halved per mip | 0xbc4156a | - | ALU: edx >>= 1 | `0xBC4156A  shr edx,1` | type halved for this mip level | [V] |
| type stored back | 0xbc4156c | 4 | W: [rsi+0x0] | `0xBC4156C  mov [rsi],edx` | type dword stored back | [V] |
| width halved per mip | 0xbc4156e | - | ALU: r8d >>= 1 | `0xBC4156E  shr r8d,1` | width halved for this mip level | [V] |
| width stored back | 0xbc41571 | 4 | W: [rsi+0x4] | `0xBC41571  mov [rsi+4],r8d` | width dword stored back | [V] |
| dragon init arg1 | 0xbc41b33 | - | ALU: rcx = rbx | `0xBC41B33  mov rcx,rbx` | sub_c296b50 arg1 = saved slot pointer | [V] |
| dragon texture-object init | 0xbc41b39 | - | S: | `0xBC41B39  call 0xC296B50` | per-mip dragon texture-object init; live capture returns to 0xBC41B3E [V live] | [V] |
| dragon object pointer | 0xbc41b52 | 8 | R: [rbp+0x180] | `0xBC41B52  mov r13,[rbp+0x180]` | dragon-created object pointer (out of sub_c296b50) | [V] |
| width/height from dragon object | 0xbc41b59 | 8 | R: [r13+0x18] | `0xBC41B59  mov rax,[r13+0x18]` | width/height qword read from dragon object | [V] |
| descriptor from dragon object | 0xbc41b61 | 16 | R: [r13+8] | `0xBC41B61  movups xmm0,[r13+8]` | 16-byte descriptor read from dragon object | [V] |
| dragon name field | 0xbc41b6a | 8 | R: [r13+0x30] | `0xBC41B6A  mov r12,[r13+0x30]` | dragon object name field (+0x38 size check vs 0x10) | [V] |
| name size threshold | 0xbc41b6e | - | ALU: cmp [r13+0x38],0x10 | `0xBC41B6E  cmp qword ptr [r13+0x38],0x10` | inline-vs-heap name threshold | [V] |
| handle+desc block at out +0x0 | 0xbc41cb9 | 16 | W: [rdi+0x0] | `0xBC41CB9  movdqu [rdi],xmm0` | 16-byte block (handle+descriptor image) at out ptr +0x0 | [V] |
| width/height at out +0x10 | 0xbc41cb5 | 8 | W: [rdi+0x10] | `0xBC41CB5  mov [rdi+0x10],rcx` | width/height qword at out ptr +0x10 | [V] |
| out ptr +0x18 store | 0xbc41cd9 | 8 | W: [rdi+0x18] | `0xBC41CD9  mov [rdi+0x18],rax` | out ptr +0x18 store | [V] |
| out ptr +0x20 store | 0xbc41cdd | 8 | W: [rdi+0x20] | `0xBC41CDD  mov [rdi+0x20],rcx` | out ptr +0x20 store | [V] |
| out ptr +0x28 store | 0xbc41ce1 | 8 | W: [rdi+0x28] | `0xBC41CE1  mov [rdi+0x28],rdx` | out ptr +0x28 store | [V] |
| out ptr +0x30 store | 0xbc41ce5 | 8 | W: [rdi+0x30] | `0xBC41CE5  mov [rdi+0x30],r8` | out ptr +0x30 store | [V] |
| out ptr +0x38 store | 0xbc41cef | 4 | W: [rdi+0x38] | `0xBC41CEF  mov [rdi+0x38],eax` | out ptr +0x38 store | [V] |
| out ptr +0x3C store | 0xbc41cf9 | 2 | W: [rdi+0x3C] | `0xBC41CF9  mov [rdi+0x3C],ax` | out ptr +0x3C store | [V] |
| ready flag at out +0x40 | 0xbc41cfd | 1 | W: [rdi+0x40] | `0xBC41CFD  mov byte ptr [rdi+0x40],1` | ready flag set at out ptr +0x40 | [V] |

## Table 4 — sub_c296b50, dragon-layer texture-object init (fresh rdis)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| wrapper ecx=6 flags arg | 0xc296d74 | - | ALU: ecx = 6 | `0xC296D74  mov ecx,6` | flags argument for the createTexture wrapper | [V] |
| wrapper call | 0xc296d79 | - | S: | `0xC296D79  call 0xBC73BF0` | sub_c296b50 -> sub_bc73bf0 (thin bgfx createTexture wrapper); live capture returns to 0xBC41B3E [V live: dragon_texture_entry_c296b50.txt line 3] | [V] |
| handle at dragon object +0x0 | 0xc296e26 | 2 | W: [rdi+0x0] | `0xC296E26  mov [rdi],ax` | createTexture handle (u16) stored at dragon texture object +0x0 | [V] |
| descriptor block load | 0xc296e2d | 16 | R: [r12+0x0] | `0xC296E2D  movups xmm0,[r12]` | 16-byte descriptor block loaded from [r12] | [V] |
| descriptor at dragon object +0x8 | 0xc296e32 | 16 | W: [rdi+8] | `0xC296E32  movups [rdi+8],xmm0` | descriptor block stored at dragon object +0x8 | [V] |
| width/height from descriptor | 0xc296e36 | 8 | R: [r12+0x10] | `0xC296E36  mov rdx,[r12+0x10]` | width/height qword at descriptor +0x10 | [V] |
| width/height at dragon object +0x18 | 0xc296e3b | 8 | W: [rdi+0x18] | `0xC296E3B  mov [rdi+0x18],rdx` | width/height stored at dragon object +0x18 | [V] |
| dragon object pointer return | 0xc296f44 | 8 | W: [rsi] | `0xC296F44  mov [rsi],rdi` | dragon object pointer returned via out parameter | [V] |
| success return | 0xc296f47 | - | ALU: eax = 0 | `0xC296F47  xor eax,eax` | returns 0 (success) | [V] |

## Table 5 — bgfx createTexture wrapper and command-byte-14 producer (fresh rdis)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| wrapper &handle out-param | 0xbc73e9d | - | LEA: [rsp+0x32] | `0xBC73E9D  lea rdx,[rsp+0x32]` | &handle passed to producer | [V] |
| wrapper descriptor arg | 0xbc73ea2 | - | ALU: r8 = r14 | `0xBC73EA2  mov r8,r14` | descriptor block passed to producer | [V] |
| wrapper r9d=esi flags arg | 0xbc73ea5 | - | ALU: r9d = esi | `0xBC73EA5  mov r9d,esi` | flags passed to producer | [V] |
| wrapper -> producer call | 0xbc73ea8 | - | S: | `0xBC73EA8  call 0xBC73770` | sub_bc73bf0 -> sub_bc73770 (the live-call site) | [V] |
| wrapper handle read back | 0xbc73ead | 2 | R: [rsp+0x32] | `0xBC73EAD  movzx eax,word ptr [rsp+0x32]` | handle read back as the wrapper's return | [V] |
| wrapper epilogue | 0xbc73ecd | - | - | `0xBC73ECD  ret` | handle returned to dragon-entry caller | [V] |
| producer command byte 0x0E | 0xbc73aaa | 1 | W: [rbp+0x2C] | `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` | command byte 14 (createTexture) written into the command buffer | [V] |

Table 5 live evidence: docs/data/live/bgfx_texture_wrapper_bc73bf0.txt line 3: `CALLER ret=0xC296D7E first_hit=1` — sub_c296b50 calls sub_bc73bf0 at `0xc296d79 call 0xBC73BF0` [V live]. docs/data/live/bgfx_createtexture_producer.txt: all 16 hits `ret=0xBC73EAD`, i.e. the instruction after `0xbc73ea8 call 0xBC73770` in sub_bc73bf0 [V live: lines 3-35]; RDX = descriptor block (e.g. hit 1: `140054455800...` = size 0x14, "TEX\0" magic, width/height u16s), R8 = descriptor pointer.

## Table 6 — command-buffer dispatcher default path (createTexture issuance) and backend entry (fresh rdis)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vtable load | 0xbc6a2ae | 8 | R: [rcx+0x0] | `0xBC6A2AE  mov rax,[rcx]` | RendererContext vtable load | [V] |
| vtable slot 26 | 0xbc6a2b1 | 8 | R: [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | vtable+0xD0 = RendererContext slot 26 = createTexture 0xe8143c0 | [V] |
| slot-26 vcall | 0xbc6a2c2 | - | S: | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | createTexture issued (args rdx=handle, r8=desc ptr, r9d=flags) | [V] |
| createTexture return tested | 0xbc6a2c8 | - | - | `0xBC6A2C8  test rax,rax` | ID3D12Resource* return tested; live capture ret=0xBC6A2C8 | [V] |
| return kept | 0xbc6a2d1 | 8 | W: r15 | `0xBC6A2D1  mov r15,rax` | ID3D12Resource* kept in r15 | [V] |
| createTexture entry | 0xe8143c0 | - | E: | `0xE8143C0  push rbp` | createTexture entry, RendererContext slot 26 | [V] |

Table 6 live evidence: docs/data/live/createtexture_callers.txt — `ret=0xBC6A2C8`, 25 hits; RCX = renderer context (0x5314A010000); R8 = 0x1C descriptor beginning "TEX\0" with texture name pointers ("sideTex", "world_download_default", textures/ui/...). So createTexture slot 26 (0xe8143c0) IS issued at runtime via command byte 14 -> handler 0xbc69487 -> default path -> vtable+0xD0 vcall [V + V live].

## Table 7 — sub_4e061b0, copy dragon result into the MC-side out block (fresh rdis)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| w/h loaded from src block | 0x4e061c3 | 8 | R: [rdx+0x10] | `0x4E061C3  mov r8,[rdx+0x10]` | width/height qword loaded from src block +0x10 | [V] |
| w/h stored at dst +0x10 | 0x4e061c7 | 8 | W: [rcx+0x10] | `0x4E061C7  mov [rcx+0x10],r8` | width/height stored at dst +0x10 | [V] |
| handle+desc loaded | 0x4e061cb | 16 | R: [rdx+0x0] | `0x4E061CB  movups xmm0,[rdx]` | 16-byte handle+desc block loaded from src block +0x0 | [V] |
| handle+desc stored at dst +0x0 | 0x4e061ce | 16 | W: [rcx+0x0] | `0x4E061CE  movups [rcx],xmm0` | handle (at +0x0) + descriptor stored at dst +0x0 | [V] |
| ready flag at dst +0x40 | 0x4e062bb | 1 | W: [rcx+0x40] | `0x4E062BB  mov byte ptr [rcx+0x40],1` | ready flag set at dst +0x40 | [V] |

Table 7 note: sub_4e05e50 calls sub_4e061b0 with rcx = its stack block [rbp-8] (`0x4e05f7d lea rcx,[rbp-8]`, Table 1) and rdx = sub_bc41420's out block [rbp-0x50]. The handle therefore lands at dst+0x0, width/height at dst+0x10, ready byte at dst+0x40. The block's installation into the MC TexturePtr/ClientTexture object is performed by the indirect caller of sub_4e05e50 (capture pending — see Table 9).

## Table 8 — static evidence and SDK header layout check (no instruction quotes; tool results and header contents)

| name | rva or offset | size | read/store address | verbatim proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 xrefs | 0x4e05e50 | - | - | rdis header: `sub_4e05e50 [0x4e05e50..0x4e07e50) size 0x2000 0 xrefs in` | no static caller; indirect/vtable only | [V] |
| sub_4e05e50 xref/imm | 0x4e05e50 | - | - | xref.py callers 0x4e05e50 = EMPTY; imm 0x4e05e50 = 0 hits (oc_U-EL7e_r8, cited) | no data-section reference to the chain entry either | [V] |
| createTexture callers | 0xe8143c0 | - | - | xref.py callers 0xe8143c0 = EMPTY (oc_U-EL7e_r2..r8, cited) | only indirect [vptr+0xD0] thunks; no static path from MC texture code | [V] |
| SDK TexturePtr.h | src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h | - | - | two shared_ptr members (+0x0 mClientTexture, +0x10 mResourceLocationPtr); `static_assert(sizeof(TexturePtr) == 32)` | does NOT match dst block (handle+desc 16B at +0x0, w/h qword at +0x10, ready byte at +0x40, size >= 0x41) | [I] |
| SDK ClientTexture.h | src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h | - | - | `struct ClientTexture {};` empty stub carrier, never built from game | no match | [I] |
| SDK BedrockTexture.h | src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h | - | - | three shared_ptr members (+0x0/+0x10/+0x20); `static_assert(sizeof(BedrockTexture) == 48)` | no match | [I] |
| SDK ServerTexture.h | src/sdk/mc/deps/minecraft_renderer/resources/ServerTexture.h | - | - | `struct ServerTexture {};` empty stub carrier, never built from game | no match | [I] |

## Interpretations ([I] notes, not row claims)

- Handle flow (end to end): createTexture returns ID3D12Resource* (dispatcher default path `0xbc6a2ae mov rax,[rcx]` / `0xbc6a2b1 mov rax,[rax+0xD0]` / `0xbc6a2c2 call qword ptr [0xF99FFA0]`, live ret=0xBC6A2C8 [V live]) -> handle u16 via wrapper (`0xbc73ead movzx eax,word ptr [rsp+0x32]`) -> sub_c296b50 stores it at dragon object +0x0 (`0xc296e26 mov [rdi],ax` [V]) -> sub_bc41420 copies handle+desc block to out ptr +0x0 (`0xbc41cb9 movdqu [rdi],xmm0` [V]) and width/height to +0x10 (`0xbc41cb5 mov [rdi+0x10],rcx` [V], traced back to dragon object [r13+0x18]) and ready flag to +0x40 (`0xbc41cfd mov byte ptr [rdi+0x40],1` [V]) -> sub_4e061b0 copies [rdx+0x0] handle+desc (16B) to [rcx+0x0] and [rdx+0x10] w/h to [rcx+0x10], sets [rcx+0x40]=1 (`0x4e061cb movups xmm0,[rdx]` / `0x4e061ce movups [rcx],xmm0` / `0x4e061c7 mov [rcx+0x10],r8` / `0x4e062bb mov byte ptr [rcx+0x40],1` [V]). dst [rcx] = sub_4e05e50's stack block [rbp-8]; installing it into the MC TexturePtr/ClientTexture object is the indirect caller's job (capture pending).
- RCX of sub_bc41420 = sub_4e05e50's arg1 + 0x58 (`0x4e05e6e mov rdi,rcx` / `0x4e05f68 add rdi,0x58` / `0x4e05f74 mov rcx,rdi` [V]) = the source texture object. Live RCX values at sub_bc41420 entry: 531A2FA4958, 531A2FA3458, ...; the object at RCX shows +0x18 "tex\0", +0x14 dword 1 (mip count), +0x28 qword 3 non-null [V live: dragon_texture_caller_bc41420.txt lines 4 and 8].
- The receiving object's class name is not instruction-visible: none of the SDK stubs matches the dst block layout (TexturePtr 32B two shared_ptrs; ClientTexture empty; BedrockTexture 48B three shared_ptrs; ServerTexture empty) [Table 8]. sub_4e05e50's arg1 has shared_ptr members at +0x8/+0x10 released via sub_eea6040, and the texture object lives at arg1+0x58 — consistent with an internal MC texture object, not provably TexturePtr/ClientTexture [I].

## What I tried that failed (new angles, not redone)

- xref.py callers 0x4e05e50 = EMPTY and imm 0x4e05e50 = 0 hits (r8); re-confirmed fresh: rdis reports "0 xrefs in" for sub_4e05e50 — the hop from Minecraft texgroup_load/texload into this chain is indirect-only and cannot be closed statically.
- SDK header layout match: TexturePtr/ClientTexture/BedrockTexture/ServerTexture checked against the dst block — none matches, so "TexturePtr/ClientTexture" for the receiving object is [I], not [V].
- All previously failed angles (r2-r7): `imm 0x0E` scan found no `mov byte ptr [mem], 0x0E`; command-buffer writers hardcode other opcodes; dispatch table at 0xF449638 obfuscated/indirect; texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10) never calls createTexture or any wrapper; texload 0x58a1310 / texload_task 0x541bf00 have no static callers; texgroup_load does not call them. Not redone per the no-redo rule.

## CLOSES?

NO — blocking fact: the connection from Minecraft texgroup_load/texload (0x5421c90/0x58a1310) into sub_4e05e50 is not statically provable (0 static xrefs, no data-section reference; sub_4e05e50 is called only indirectly). Capture mc_root_4e05e50_callers (rva 0x4E05E50, size 0x100, max 8) is already QUEUED (pending); its ret= caller is the single missing fact needed to close L7e/L8a. Everything else in the item is [V]-proven: sampler half (6ax) [V] (e820500.md/SamplerFlags.h); D3D12 backend texture-management chain [V] (r1 Tables 1-8); createTexture issuance [V + V live] (producer sub_bc73770 writes command byte 0x0E `0xbc73aaa mov byte ptr [rbp+0x2C],0xE`, wrappers call it at `0xbc73ea8 call 0xBC73770`, dispatcher default path `0xbc6a2ae mov rax,[rcx]` / `0xbc6a2b1 mov rax,[rax+0xD0]` / `0xbc6a2c2 call qword ptr [0xF99FFA0]`, live ret=0xBC6A2C8 [V live], createTexture entry 0xe8143c0); handle traced into the texture object (dragon object +0x0 `0xc296e26 mov [rdi],ax` [V], bridge out block +0x0 `0xbc41cb9 movdqu [rdi],xmm0` [V], MC block +0x0 `0x4e061ce movups [rcx],xmm0` [V]); sub_4e05e50 passes arg1+0x58 as RCX of sub_bc41420 (`0x4e05f68 add rdi,0x58` / `0x4e05f74 mov rcx,rdi` [V]) with live RCX = source texture object [V live]. On capture return: if ret= names texgroup_load/texload/texload_task, flip CLOSES? to YES; else report the actual caller. Atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## TOOL REQUESTS

- capture mc_root_4e05e50_callers (rva=0x4E05E50): ALREADY QUEUED (pending; `python tools/livecap/request.py list` shows it, same RVA rejected my duplicate add as "already queued"). Result expected in docs/data/live/mc_root_4e05e50_callers.txt; needed to name the indirect caller of sub_4e05e50 (texgroup_load/texload expected) and close L7e/L8a. No new request added.

## Verification

- python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md — every quoted `0xRVA  instr` line re-checked verbatim against the exe via rdis; must report mismatch=0 no-such-instr=0.
- python tools/delegate.py check docs/progress/oc_U-EL7e.md — run after line 2 is set to DONE; fix every failure.
