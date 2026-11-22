## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; orchestrator live captures read read-only (never touched the game).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] saw in an orchestrator live capture (file+line cited), [I] inferred from structure/BGFX_MAP/SDK headers, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (cited from oc_U-EL7e_r1..r10, NOT re-derived)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts; called from blit 0xe818bc0 and executor 0xe821120. Not part of the pending half of this item.
- Half 2a — D3D12 backend texture-management chain: [V] oc_U-EL7e_r1.md Tables 1-8: record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 (slot 26), updateTexture 0xe814a70 (28), readTexture 0xe8150f0 (30), resizeTexture 0xe815840 (31), override/get/destroy 0xe815c30..0xe815fbf (32-34), destructor 0xe80f290, blit 0xe818bc0 (51), blitSetup 0xe819750 (52); BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records (guard byte this+0xC96190 = 0 live).
- Static negatives (r2-r10, not redone): xref.py callers 0xe8143c0 = EMPTY — createTexture has no static caller, only indirect [vptr+0xD0] (slot 26 = offset 0xD0); texload 0x58a1310 and texload_task 0x541bf00: xref EMPTY for both; texgroup_load does not call them (its only cache-bound call is `0x54227af call 0x18718d0` [V]); 0x18718d0 decoded as the texture cache (BST this+0x30, ready callback 0x873D0->jmp 0xEEC59D0 via 0x7705B0, async enqueue 0x71BC70 "resource dispatch"); texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10) only swaps live vtables 0xEFCA5A0/5D0/5F0, never calls createTexture [V r2]. Atlas stitchers remain open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.
- Command byte 0x0E producer (r6-r8, not redone): sub_bc73770 writes `0xbc73aaa mov byte ptr [rbp+0x2C],0xE` [V]; thin wrappers 0xbc73bf0/0xbc73ed0/0xbc74120 call it [V xref]; live capture bgfx_createtexture_producer: all 16 hits ret=0xBC73EAD at `0xbc73ea8 call 0xBC73770` in sub_bc73bf0 [V live: docs/data/live/bgfx_createtexture_producer.txt lines 3-35]. `imm 0x0E` scan found NO `mov byte ptr [mem], 0x0E`; command-buffer writers hardcode other opcodes; dispatch table at 0xF449638 obfuscated/indirect. BGFX_MAP 6dn now confirms the mapping statically [V]: handler 0xbc69487 reads `[u16 handle][u64 Memory* mem][u32 flags][u8 skip]`, requires magic 0x00584554 ('TEX',0), parses the 0x18-byte TextureCreate header and calls renderer vtable slot 26 (`[rax+0xd0]`) = createTexture(handle, mem, flags, skip, header*); after the call the returned pointer is stored in the Context's per-handle texture table at ctx+0x1e55ab8, element 0x28 bytes, texture object pointer at element+0x10. BGFX_MAP 6k anchors slot 26 = createTexture.
- Handle into dragon texture object (r7-r8, not redone): sub_c296b50 calls sub_bc73bf0 at `0xc296d79 call 0xBC73BF0` [V] and stores the createTexture handle at `0xc296e26 mov [rdi],ax` (dragon texture object +0x0) [V]; width/height at descriptor [r12+0x10] stored to object +0x18 via `0xc296e36 mov rdx,[r12+0x10]` / `0xc296e3b mov [rdi+0x18],rdx` [V]; descriptor block at [r12] via `0xc296e2d movups xmm0,[r12]` copied to object +0x8 via `0xc296e32 movups [rdi+8],xmm0` [V]. Live capture dragon_texture_entry_c296b50: CALLER ret=0xBC41B3E, 6 hits — sub_c296b50 has one static caller, sub_bc41420 at call site 0xbc41b39 [V live + V: docs/data/live/dragon_texture_entry_c296b50.txt line 3].
- sub_bc41420 pack->GPU bridge (r8-r10, not redone): sub_bc41420 [0xbc41420..0xbc43420), size 0x2000, 1 static xref in; reads source texture object (type/width at [rsi+0x0]/[rsi+0x4], halved per mip via `0xbc4156a shr edx,1` / `0xbc4156e shr r8d,1`; mip count at [rsi+0x14]; entry array at [rsi+0x40]/[rsi+0x48]), calls sub_c296b50 once per mip level at `0xbc41b39 call 0xC296B50`, writes handle+desc block+width/height+ready flag to its out pointer. Live capture dragon_texture_caller_bc41420: all calls return ret=0x4E05F7C at `0x4e05f77 call 0xBC41420` (+1 insn = `0x4e05f7c nop`), hits=372 samples=17 [V live: docs/data/live/dragon_texture_caller_bc41420.txt line 3].

## Table A — sub_4e05e50, MC-side pack->GPU root around 0x4E05F7C (0x4e05e50..0x4e07e50, size 0x2000, 0 xrefs in [V])

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| function entry | 0x4e05e50 | 8 | E: | `0x4E05E50  push rbp` | sub_4e05e50 entry; rdis header: size 0x2000, 0 xrefs in — indirect entry only | [V] |
| out/release ptr saved | 0x4e05e6b | 8 | ALU: rsi = rdx | `0x4E05E6B  mov rsi,rdx` | arg2 (release/out pointer slot) copied to rsi | [V] |
| MC object = arg1 | 0x4e05e6e | 8 | ALU: rdi = rcx | `0x4E05E6E  mov rdi,rcx` | arg1 = MC texture object (shared_ptr members at +0x8/+0x10, released via sub_eea6040) | [V] |
| source object = arg1 + 0x58 | 0x4e05f68 | 8 | ALU: rdi += 0x58 | `0x4E05F68  add rdi,0x58` | source texture object address computed for sub_bc41420 | [V] |
| sub_bc41420 RCX arg | 0x4e05f74 | 8 | ALU: rcx = rdi | `0x4E05F74  mov rcx,rdi` | source texture object passed as RCX to the bridge | [V] |
| bridge call | 0x4e05f77 | - | S: | `0x4E05F77  call 0xBC41420` | sub_4e05e50 -> sub_bc41420; live capture ret=0x4E05F7C [V live] | [V] [V live] |
| return address | 0x4e05f7c | - | - | `0x4E05F7C  nop` | instruction after the call; equals the live capture's ret=0x4E05F7C | [V] |
| out block (stack) | 0x4e05f7d | 8 | LEA: [rbp-8] | `0x4E05F7D  lea rcx,[rbp-8]` | destination block for the sub_4e061b0 copy | [V] |
| temp block (stack) | 0x4e05f81 | 8 | LEA: [rbp-0x50] | `0x4E05F81  lea rdx,[rbp-0x50]` | sub_bc41420 out block (handle+desc+w/h+ready) | [V] |
| copy into out block | 0x4e05f85 | - | S: | `0x4E05F85  call 0x4E061B0` | copy dragon-created result into out block | [V] |
| out pointer cleared | 0x4e06010 | 8 | W: [rsi] | `0x4E06010  mov qword ptr [rsi],0` | [arg2] nulled on exit | [V] |

## Table B — static evidence that the hop into this chain is indirect-only (all new this session, none redone)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| static references to sub_4e05e50 | 0x4e05e50 (xref/imm/ripscan) | - | - | `rdis header: sub_4e05e50 [0x4e05e50..0x4e07e50) size 0x2000 0 xrefs in` / `xref.py callers 0x4e05e50 = EMPTY` / `imm 0x4e05e50 = 0 hits` / `ripscan.py 0x4e05e50`: no hits | no `call`, no data-section reference, no rip-relative reference in .text — the root is reachable only indirectly | [V] |
| capture mc_root_4e05e50_callers | rva 0x4E05E50 | - | - | `python tools/livecap/request.py result mc_root_4e05e50_callers` -> "no result yet (orchestrator has not run it)" | capture queued by the orchestrator (r10), result not yet returned; the ret= caller is the single missing link to texgroup_load/texload | [V] |

## Table C — source texture object = RCX of sub_bc41420 (docs/data/live/dragon_texture_caller_bc41420.txt)

| name | rva or offset | size | read/store address | verbatim proof | meaning | tag |
|---|---|---|---|---|---|---|
| capture identity | rva=0xBC41420 kind=regs size=0x40 | - | - | docs/data/live/dragon_texture_caller_bc41420.txt line 3: `CALLER ret=0x4E05F7C first_hit=1` (hits=372, samples=17) | sub_bc41420 is called from sub_4e05e50 (`0x4e05f77 call 0xBC41420`); every live call returns to `0x4e05f7c nop` (+1 insn) | [V live] |
| RCX@entry hit 1 | RCX=531A2FA4958 | - | R: [rcx+0x00], [rcx+0x14], [rcx+0x18], [rcx+0x28] | line 4: `RCX=531A2FA4958 hit=1 ret=0x4E05F7C 80000000800000001C0000000100000001000000010000007465780000000000000000000000000003000000000000000F000000000000000000000000000000` | source object at RCX: +0x00 qword 0x8000000080000000, +0x08 dword 0x1C, +0x14 dword 1 (= mip count read at `0xbc4149f mov eax,[rsi+0x14]`; rsi == rcx on entry per `0xbc4145a mov rsi,rcx`), +0x18 "tex\0", +0x28 qword 3 (non-null -> passes guard `0xbc41446 cmp qword ptr [rcx+0x28],0`) | [V live] |
| RCX@entry hit 2 | RCX=531A2FA3458 | - | R: same layout | line 8: `RCX=531A2FA3458 hit=2 ret=0x4E05F7C ...` | same source-object layout at a second object address | [V live] |

Table C note: sub_4e05e50 passes its arg1+0x58 as RCX of sub_bc41420 (`0x4E05E6E  mov rdi,rcx` / `0x4E05F68  add rdi,0x58` / `0x4E05F74  mov rcx,rdi` [V]); live RCX values are source texture objects [V live]. The destination object of sub_4e061b0 (sub_4e05e50's stack block [rbp-8]) receives handle at +0x0, width/height at +0x10, ready byte at +0x40; installing that block into the MC TexturePtr/ClientTexture object is the indirect caller of sub_4e05e50's job — see Table B (capture pending).

## Table D — command byte 14 producer and createTexture issuance [V + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| command byte 14 written | [rbp+0x2C] | 1 | W: | `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` | command byte 14 (createTexture) written into the command buffer [V]; mapping byte 14 -> handler 0xbc69487 -> vtable slot 26 createTexture confirmed statically by BGFX_MAP 6dn [V] | [V] |
| producer call site (live) | 0xbc73ea8 | - | S: | `0xBC73EA8  call 0xBC73770` | sub_bc73bf0 -> sub_bc73770; all 16 live hits ret=0xBC73EAD (instruction right after this call) [V live: docs/data/live/bgfx_createtexture_producer.txt lines 3-35] | [V] [V live] |
| dragon -> wrapper call | 0xc296d79 | - | S: | `0xC296D79  call 0xBC73BF0` | sub_c296b50 calls the thin bgfx createTexture wrapper; live capture ret=0xBC41B3E [V live: docs/data/live/dragon_texture_entry_c296b50.txt line 3] | [V] [V live] |
| dispatcher case head (byte 14) | 0xbc69487 | 4 | - | `0xBC69487  and edx,0xFFFFFFFE` | command-byte-14 case head (cursor advance, [rsi] = cursor var) [V]; BGFX_MAP 6dn: handler 0xbc69487 decodes handle/Memory*/flags, requires 'TEX' magic, calls slot 26 | [V] |
| vtable load | 0xbc6a2ae | 8 | R: [rcx+0x0] | `0xBC6A2AE  mov rax,[rcx]` | RendererContext vtable load (receiver object at [rdi+0x1EBF2D0]) | [V] |
| vtable slot 26 | 0xbc6a2b1 | 8 | R: [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | vtable+0xD0 = RendererContext slot 26 = createTexture 0xe8143c0 [V: BGFX_MAP 6dn/6k] | [V] |
| slot-26 vcall | 0xbc6a2c2 | - | S: | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | createTexture issued; args rdx=handle, r8=desc ptr, r9d=flags | [V] |
| createTexture return tested | 0xbc6a2c8 | 8 | - | `0xBC6A2C8  test rax,rax` | ID3D12Resource* return tested; live capture createtexture_callers: ret=0xBC6A2C8, 25 hits [V live: docs/data/live/createtexture_callers.txt line 3] | [V] [V live] |
| return kept | 0xbc6a2d1 | 8 | W: r15 | `0xBC6A2D1  mov r15,rax` | ID3D12Resource* kept in r15 | [V] |
| created resource stored in handle record | [r8+0x10] / [rcx+0x10] | 8 | W: | `0xBC6A49B  mov [r8+0x10],r15` / `0xBC6A58D  mov [r8+0x10],r15` / `0xBC6A577  mov [rcx+0x10],r15` | ID3D12Resource* stored into the per-handle texture record at element+0x10 (inline and paged paths) — matches BGFX_MAP 6dn (ctx+0x1e55ab8, element+0x10) [I address role] | [V] |

## Table E — handle trace into the texture object [V + V live]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| handle at dragon object +0x0 | 0xc296e26 | 2 | W: [rdi+0x0] | `0xC296E26  mov [rdi],ax` | createTexture handle (u16) stored at dragon texture object +0x0 | [V] |
| descriptor block load | 0xc296e2d | 16 | R: [r12+0x0] | `0xC296E2D  movups xmm0,[r12]` | 16-byte descriptor block loaded from [r12] | [V] |
| descriptor at dragon object +0x8 | 0xc296e32 | 16 | W: [rdi+8] | `0xC296E32  movups [rdi+8],xmm0` | descriptor block stored at dragon object +0x8 | [V] |
| width/height from descriptor | 0xc296e36 | 8 | R: [r12+0x10] | `0xC296E36  mov rdx,[r12+0x10]` | width/height qword at descriptor +0x10 | [V] |
| width/height at dragon object +0x18 | 0xc296e3b | 8 | W: [rdi+0x18] | `0xC296E3B  mov [rdi+0x18],rdx` | width/height stored at dragon object +0x18 | [V] |
| dragon texture-object init call | 0xbc41b39 | - | S: | `0xBC41B39  call 0xC296B50` | sub_bc41420 calls the dragon texture-object init once per mip level; live capture ret=0xBC41B3E [V live] | [V] [V live] |
| dragon object pointer | 0xbc41b52 | 8 | R: [rbp+0x180] | `0xBC41B52  mov r13,[rbp+0x180]` | dragon-created object pointer out of sub_c296b50 | [V] |
| width/height from dragon object | 0xbc41b59 | 8 | R: [r13+0x18] | `0xBC41B59  mov rax,[r13+0x18]` | width/height qword read from dragon object | [V] |
| descriptor from dragon object | 0xbc41b61 | 16 | R: [r13+8] | `0xBC41B61  movups xmm0,[r13+8]` | 16-byte descriptor read from dragon object | [V] |
| handle+desc block at out +0x0 | 0xbc41cb9 | 16 | W: [rdi+0x0] | `0xBC41CB9  movdqu [rdi],xmm0` | 16-byte block (handle+descriptor image) at out ptr +0x0 | [V] |
| width/height at out +0x10 | 0xbc41cb5 | 8 | W: [rdi+0x10] | `0xBC41CB5  mov [rdi+0x10],rcx` | width/height qword at out ptr +0x10 (traced back to dragon object [r13+0x18]) | [V] |
| out ptr +0x18 store | 0xbc41cd9 | 8 | W: [rdi+0x18] | `0xBC41CD9  mov [rdi+0x18],rax` | out ptr +0x18 store | [V] |
| out ptr +0x20 store | 0xbc41cdd | 8 | W: [rdi+0x20] | `0xBC41CDD  mov [rdi+0x20],rcx` | out ptr +0x20 store | [V] |
| out ptr +0x28 store | 0xbc41ce1 | 8 | W: [rdi+0x28] | `0xBC41CE1  mov [rdi+0x28],rdx` | out ptr +0x28 store | [V] |
| out ptr +0x30 store | 0xbc41ce5 | 8 | W: [rdi+0x30] | `0xBC41CE5  mov [rdi+0x30],r8` | out ptr +0x30 store | [V] |
| out ptr +0x38 store | 0xbc41cef | 4 | W: [rdi+0x38] | `0xBC41CEF  mov [rdi+0x38],eax` | out ptr +0x38 store | [V] |
| out ptr +0x3C store | 0xbc41cf9 | 2 | W: [rdi+0x3C] | `0xBC41CF9  mov [rdi+0x3C],ax` | out ptr +0x3C store | [V] |
| ready flag at out +0x40 | 0xbc41cfd | 1 | W: [rdi+0x40] | `0xBC41CFD  mov byte ptr [rdi+0x40],1` | ready flag set at out ptr +0x40 | [V] |

## Table F — sub_4e061b0, copy dragon result into the MC-side out block [V]

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| w/h loaded from src block | 0x4e061c3 | 8 | R: [rdx+0x10] | `0x4E061C3  mov r8,[rdx+0x10]` | width/height qword loaded from src block +0x10 | [V] |
| w/h stored at dst +0x10 | 0x4e061c7 | 8 | W: [rcx+0x10] | `0x4E061C7  mov [rcx+0x10],r8` | width/height stored at dst +0x10 | [V] |
| handle+desc loaded | 0x4e061cb | 16 | R: [rdx+0x0] | `0x4E061CB  movups xmm0,[rdx]` | 16-byte handle+desc block loaded from src block +0x0 | [V] |
| handle+desc stored at dst +0x0 | 0x4e061ce | 16 | W: [rcx+0x0] | `0x4E061CE  movups [rcx],xmm0` | handle (at +0x0) + descriptor stored at dst +0x0 | [V] |
| ready flag at dst +0x40 | 0x4e062bb | 1 | W: [rcx+0x40] | `0x4E062BB  mov byte ptr [rcx+0x40],1` | ready flag set at dst +0x40 | [V] |

Table F note: sub_4e05e50 calls sub_4e061b0 with rcx = its stack block [rbp-8] (`0x4E05F7D  lea rcx,[rbp-8]`, Table A) and rdx = sub_bc41420's out block [rbp-0x50] (`0x4E05F81  lea rdx,[rbp-0x50]`). The handle therefore lands at dst+0x0, width/height at dst+0x10, ready byte at dst+0x40 [V].

## Table G — SDK header layout check ([I]: layout only, no instruction quotes)

| name | rva or offset | size | read/store address | verbatim proof | meaning | tag |
|---|---|---|---|---|---|---|
| SDK TexturePtr.h | src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h | - | - | two shared_ptr members (+0x0 mClientTexture, +0x10 mResourceLocationPtr); `static_assert(sizeof(TexturePtr) == 32)` | does NOT match the dst block (handle+desc 16B at +0x0, w/h qword at +0x10, ready byte at +0x40, size >= 0x41) | [I] |
| SDK ClientTexture.h | src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h | - | - | `struct ClientTexture {};` empty stub carrier, never built from game | no match | [I] |
| SDK BedrockTexture.h | src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h | - | - | three shared_ptr members (+0x0/+0x10/+0x20); `static_assert(sizeof(BedrockTexture) == 48)` | no match | [I] |
| SDK ServerTexture.h | src/sdk/mc/deps/minecraft_renderer/resources/ServerTexture.h | - | - | `struct ServerTexture {};` empty stub carrier, never built from game | no match | [I] |

## Interpretations ([I] notes, not row claims)

- Handle flow (end to end): createTexture returns ID3D12Resource* (dispatcher default path `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]`, live ret=0xBC6A2C8 [V live]) -> handle u16 via the thin wrapper -> sub_c296b50 stores it at dragon object +0x0 (`0xC296E26  mov [rdi],ax` [V]) -> sub_bc41420 copies handle+desc block to out ptr +0x0 (`0xBC41CB9  movdqu [rdi],xmm0` [V]) and width/height to +0x10 (`0xBC41CB5  mov [rdi+0x10],rcx`, traced to dragon object [r13+0x18] [V]) and ready flag to +0x40 (`0xBC41CFD  mov byte ptr [rdi+0x40],1` [V]) -> sub_4e061b0 copies [rdx+0x0] handle+desc (16B) to [rcx+0x0] and [rdx+0x10] w/h to [rcx+0x10], sets [rcx+0x40]=1 (`0x4E061CB  movups xmm0,[rdx]` / `0x4E061CE  movups [rcx],xmm0` / `0x4E061C7  mov [rcx+0x10],r8` / `0x4E062BB  mov byte ptr [rcx+0x40],1` [V]). The full chain `MC root sub_4e05e50 -> sub_bc41420 (0x4e05f77 call 0xBC41420) -> sub_c296b50 (0xbc41b39 call 0xC296B50) -> sub_bc73bf0 (0xc296d79 call 0xBC73BF0) -> sub_bc73770 (0xbc73ea8 call 0xBC73770, writes command byte 0x0E at 0xbc73aaa) -> dispatcher 0xbc69487 -> createTexture vcall 0xbc6a2c2 -> createTexture 0xe8143c0` is live-proven [V live: ret=0x4E05F7C, ret=0xBC41B3E, ret=0xBC73EAD, ret=0xBC6A2C8].
- The MC-side root sub_4e05e50 passes its arg1+0x58 as RCX (source texture object) of sub_bc41420 [V]; live RCX = source texture object at 531A2FA4958 / 531A2FA3458 with +0x18 "tex\0", +0x14 dword 1 (mip count), +0x28 qword 3 (passes the non-null guard) [V live: docs/data/live/dragon_texture_caller_bc41420.txt lines 4 and 8].
- The receiving object's class name is not instruction-visible: none of the SDK stubs matches the dst block layout (Table G) [I]; sub_4e05e50's arg1 has shared_ptr members at +0x8/+0x10 and the texture object lives at arg1+0x58 — consistent with an internal MC texture object, not provably TexturePtr/ClientTexture [I].
- The item-line chain texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> 0x18718d0 is NOT statically supported (r2/r3): texgroup_load's only cache-bound call is `0x54227af call 0x18718d0`, and texload/texload_task have no static callers. The proven pack->GPU path instead runs through sub_4e05e50 (MC root, indirect entry). Whether texgroup_load/texload/texload_task is the indirect caller of sub_4e05e50 is exactly what capture mc_root_4e05e50_callers (Table B) will answer.

## What I tried that failed (new angles, not redone)

- xref.py callers 0xe8143c0 = EMPTY (r2-r10): createTexture has no static caller, only indirect [vptr+0xD0] thunks.
- `imm 0x0E` scan over .text: only `mov ecx,0xE` at 0x81bf; NO `mov byte ptr [mem], 0x0E` anywhere — command byte 0x0E is computed at runtime.
- Command-buffer writer scan: writers hardcode opcodes 0x00/0x07/0x0A/0x0B/0x12/0x14/0x27; none stores 0x0E (r6); dispatch table at 0xF449638 obfuscated — byte->handler mapping now [V] solely via BGFX_MAP 6dn.
- texture-object init vtable 0xEFCA580 slot 4 (sub_a3f10): sets live vtables 0xEFCA5A0/5D0/5F0, never calls createTexture or any wrapper [V r2].
- NEW this session: xref.py callers 0x4e05e50 = EMPTY [V]; imm 0x4e05e50 = 0 hits [V]; ripscan.py 0x4e05e50 = no hits [V]; rdis reports 0 xrefs into sub_4e05e50 [V] — the hop from Minecraft texgroup_load/texload (0x5421c90/0x58a1310) into sub_4e05e50 is indirect-only and cannot be closed statically.
- NEW this session: sub_4e061b0 has 9 static callers (0x4e05e50, 0x4e06430, 0x4e067c0, 0x4e06a90, 0x56be030, 0x5aba280, 0x64f14f0, 0x67cb9a0, 0xc295880), all in the same MC-root family, none is texgroup_load/texload [V r10].
- SDK header layout match: TexturePtr/ClientTexture/BedrockTexture/ServerTexture all fail to match the dst block [I r10 Table G].

## CLOSES?

NO — blocking fact: the caller of MC-side pack->GPU root sub_4e05e50 (the function at 0x4e05e50 whose live call returns to 0x4E05F7C, i.e. `0x4e05f77 call 0xBC41420`, and which passes arg1+0x58 as the source texture object RCX of sub_bc41420) is not statically identifiable: xref.py callers EMPTY, imm scan 0 hits, ripscan 0 hits, rdis reports 0 xrefs in (Table B). The capture mc_root_4e05e50_callers (rva 0x4E05E50) is already QUEUED by the orchestrator but its result has not been returned ("no result yet"). If its ret= names texgroup_load 0x5421c90 / texload 0x58a1310 / texload_task 0x541bf00, the hop closes and CLOSES? flips to YES; otherwise report the actual caller. Everything else in the item is [V]-proven: sampler half (6ax) [V] (e820500.md/SamplerFlags.h); D3D12 backend texture-management chain [V] (r1 Tables 1-8); command-byte-14 producer sub_bc73770 (`0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` [V], wrappers call it at `0xBC73EA8  call 0xBC73770` [V], dispatcher `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` [V], live ret=0xBC6A2C8 [V live], createTexture entry 0xe8143c0); handle traced into the texture object end to end (dragon object +0x0 `0xC296E26  mov [rdi],ax` [V], bridge out block +0x0 `0xBC41CB9  movdqu [rdi],xmm0` [V], MC block +0x0 `0x4E061CE  movups [rcx],xmm0` [V]); sub_4e05e50 -> sub_bc41420 at `0x4E05F77  call 0xBC41420` [V] with live ret=0x4E05F7C [V live]; sub_4e061b0 copy [V]. Atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## TOOL REQUESTS

- capture mc_root_4e05e50_callers (rva=0x4E05E50): ALREADY QUEUED (pending; `python tools/livecap/request.py result mc_root_4e05e50_callers` returns "no result yet"). No new request added (pending-limit respected). No helper scripts written, no temporary files left behind.

## Verification

- python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md — every quoted `0xRVA  instr` line re-checked verbatim against the exe via rdis; must report mismatch=0 no-such-instr=0.
- python tools/delegate.py check docs/progress/oc_U-EL7e.md — run once line 2 is DONE; fix every failure.
