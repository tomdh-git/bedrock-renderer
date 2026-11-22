## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures are orchestrator-produced read-only logs cited as [V live].

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] seen in an orchestrator live-capture log (file + line cited), [I] inferred from structure/BGFX_MAP, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r2/r3 and the live captures)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 of oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture slot 26 = 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. xref.py callers 0xe8143c0 = EMPTY (r2, not redone): only indirect [vptr+0xD0] dispatch.
- Texture record fields (BGFX_MAP 6z, live-verified): +0x00 qword, +0x08 u32 state/type, +0x18 width u32, +0x20 height u32, +0x24 flags, +0x28 DXGI_FORMAT, +0x2c u32, +0x98 flags, +0x9C width, +0xA0 height, +0xAF requested format, +0xB0 actual format byte, +0xB1 numMips. Guard byte this+0xC96190; page list this+0xC96178.

## What earlier attempts tried that failed (do not repeat)

- xref.py callers 0xe8143c0: empty, only indirect [vptr+0xD0] thunks (r2, r3).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY for both; never decoded; texgroup_load 0x5421c90 does not call them (its only cache-bound call is `0x54227af  call 0x18718D0`).
- Backend->cache adjacency (0xe82e00/0xe84070/0xe85290/0xe86630): leads only to font-init roots, not createTexture (r3).
- [0xF99FFA0] as a writable function pointer for the texgroup_load->sub_4e05e50 link: read-only .rdata initializer = trampoline sub_eea6040 (`jmp rax`); no writer store found (r37). Static work on that link is exhausted.

## New work this session (orchestrator hint: createTexture issuance chain)

### Chain proven [V live] end to end

1. sub_4e05e50 calls sub_bc41420 at `4e05f77  call 0xBC41420`, ret=0x4E05F7C (live capture mc_root_4e05e50_callers.txt hit=1, ret=0x4E05F7C; also dragon_texture_caller_bc41420.txt).
2. sub_bc41420 calls sub_c296b50 at `0xBC41B39  call 0xC296B50`, ret=0xBC41B3E (live capture dragon_texture_caller_bc41420.txt hit=1, ret=0x4E05F7C; dragon_texture_entry_c296b50.txt hit=1, ret=0xBC41B3E).
3. sub_c296b50 calls sub_bc73bf0 at `c296d79  call 0xBC73BF0`, ret=0xC296D7E (live capture bgfx_texture_wrapper_bc73bf0.txt, ret=0xC296D7E).
4. sub_bc73bf0 calls sub_bc73770 (command byte 0x0E producer) at `0xBC73EA8  call 0xBC73770`, ret=0xBC73EAD (live capture bgfx_createtexture_producer.txt, all hits ret=0xBC73EAD).
5. bgfx dispatcher createTexture case: `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` — [vptr+0xD0] vcall = slot 26 createTexture; ret=0xBC6A2C8 matches live capture createtexture_callers.txt (all hits ret=0xBC6A2C8).
6. createTexture target: 0xe8143c0 (D3D12 slot 26) — xref.py callers EMPTY (static), only indirect [vptr+0xD0] (proven by r2/r3, not redone).
7. Handle stored at texture_obj+0x00: `0xC296E26  mov [rdi],ax` (sub_c296e00, fallthrough from sub_c296b50 via `c296d7e  jmp 0xC296E26`), rdi = texture object RCX of sub_c296b50 (live capture dragon_texture_entry_c296b50.txt RCX=53199475D00 among others); sub_c296e00 also copies desc fields at `0xC296E2D  movups xmm0,[r12]` / `0xC296E32  movups [rdi+8],xmm0` / `0xC296E3B  mov [rdi+0x18],rdx`.

### Remaining gap

sub_4e05e50 is called indirectly via `call qword ptr [0xF99FFA0]` at 0x1289490 inside sub_12893d0 (ret=0x1289496, live capture mc_root_4e05e50_callers.txt, 150 hits). sub_12893d0 has 3 static xrefs: 0x1145c20, 0x6622610, 0x6632bf0. sub_6632bf0 references "Deferred Texture Transactions" (str 0xF54E8AF). [0xF99FFA0] = sub_eea6040 (`jmp rax`, read-only .rdata, no writer — r37). rax at the jmp = runtime target, not statically determinable; would need a capture at sub_eea6040 entry reading rax. Static work on this link is exhausted.

## Answer table — command byte 14 producer (who writes 0x0E into the bgfx command buffer)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| cmd-byte-14 producer entry | 0xBC73770 | - | E: `0xBC73770  push rbp` | sub_bc73770 entry (command byte 0x0E producer; r4 verified) | [V live] |
| wrapper -> producer call | - | - | S: `0xBC73EA8  call 0xBC73770` | sub_bc73bf0 (thin wrapper) calls the producer | [V] |
| wrapper reads back u16 handle | - | 2 | R: `0xBC73EAD  movzx eax,word ptr [rsp+0x32]` | handle returned from createTexture read back as u16 | [V live] |
| live capture: producer caller | ret=0xBC73EAD | - | - | bgfx_createtexture_producer.txt: all hits ret=0xBC73EAD (inside sub_bc73bf0 after `call 0xBC73770`) | [V live] |

## Answer table — createTexture dispatch ([vptr+0xD0] vcall, slot 26)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| createTexture dispatch case | 0xBC6A2AE | 8 | R: `0xBC6A2AE  mov rax,[rcx]` | load vtable pointer from context object | [V] |
| createTexture dispatch case | 0xBC6A2B1 | 8 | R: `0xBC6A2B1  mov rax,[rax+0xD0]` | load slot 26 (0xD0/8=26) function pointer from vtable | [V] |
| createTexture indirect call | 0xBC6A2C2 | - | S: `0xBC6A2C2  call qword ptr [0xF99FFA0]` | indirect vcall through trampoline sub_eea6040 (`jmp rax`) = createTexture | [V] |
| createTexture return site | 0xBC6A2C8 | - | - | `0xBC6A2C8  test rax,rax` — tests createTexture return handle | [V live] |
| live capture: createTexture caller | ret=0xBC6A2C8 | - | - | createtexture_callers.txt: all hits ret=0xBC6A2C8, RCX=renderer ctx, R8=0x1C-byte desc with "TEX" tag | [V live] |
| createTexture target (static) | 0xE8143C0 | - | - | D3D12 slot 26 createTexture; xref.py callers = EMPTY, only [vptr+0xD0] | [V] |
| [0xF99FFA0] trampoline | 0xEEA6040 | - | E: `0xEEA6040  jmp rax` | indirect-call trampoline; rax = runtime target | [V] |

## Answer table — handle trace into texture object (TexturePtr/ClientTexture)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| dragon texture entry | 0xC296B50 | - | E: `0xC296B50  push rbp` | dragon-layer texture create entry; RCX=texture object, RDX=out ptr, R8=desc, R9=flags | [V live] |
| entry -> wrapper call | - | - | S: `c296d79  call 0xBC73BF0` | sub_c296b50 calls thin wrapper sub_bc73bf0 | [V] |
| entry return site | c296d7e | - | - | `c296d7e  nop` after `c296d79  call 0xBC73BF0` | ret=0xC296D7E matches live capture | [V live] |
| handle store at texture_obj+0x00 | 0xC296E26 | 2 | W: `0xC296E26  mov [rdi],ax` | u16 handle stored at texture object +0x00 (rdi = RCX texture obj from sub_c296b50) | [V live] |
| desc fields copied to texture obj | texture_obj+0x08 | 16 | W: `0xC296E32  movups [rdi+8],xmm0` | 16-byte desc block copied to texture object +0x08 | [V live] |
| desc pointer field | texture_obj+0x18 | 8 | W: `0xC296E3B  mov [rdi+0x18],rdx` | desc pointer stored at texture object +0x18 | [V live] |
| sub_bc41420 -> entry call | - | - | S: `0xBC41B39  call 0xC296B50` | sub_bc41420 calls dragon texture entry | [V] |
| sub_bc41420 return site | 0xBC41B3E | - | - | `0xBC41B3E  movzx eax,byte ptr [rbp+0x188]` after the call | ret=0xBC41B3E matches live capture | [V live] |
| sub_4e05e50 -> sub_bc41420 call | - | - | S: `4e05f77  call 0xBC41420` | sub_4e05e50 (MC-side) calls sub_bc41420 with texture object in RCX | [V] |
| sub_4e05e50 return site | 0x4E05F7C | - | - | `4e05f7c  nop` after `4e05f77  call 0xBC41420` | ret=0x4E05F7C matches live capture | [V live] |
| MC-side root indirect call | 0x1289490 | - | S: `1289490  call qword ptr [0xF99FFA0]` | sub_12893d0 indirect call via trampoline; rax=sub_4e05e50 at runtime; ret=0x1289496 | [V live] |

## Answer table — dragon entry sub_c296b50 args (from live capture dragon_texture_entry_c296b50.txt)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| arg1 texture object (RCX) | reg | 8 | R: `c296b7c  mov rdi,rcx` / R: `bc41446  cmp qword ptr [rcx+0x28],0` | texture object pointer (53199475D00 / 531A2FA4958 in live captures); +0x28 checked | [V live] |
| arg2 out ptr (RDX) | reg | 8 | R: `c296b79  mov rsi,rdx` / R: `bc41457  mov rdi,rdx` | out ptr for result (14CD60 / 14CE00 in live captures) | [V live] |
| arg3 desc ptr (R8) | reg | 8 | R: `c296b7f  mov rax,[r8+8]` | desc ptr dereferenced at +0x8 (53149F91088 in live capture) | [V live] |
| arg4 flags (R9) | reg | 4 | R: `c296b76  mov r14,r9` | flags (14CBE0 in live capture) | [V live] |
| entry stores to [rsi] | out dword | 4 | W: `c296c44  mov dword ptr [rsi],6` / W: `c296c52  mov dword ptr [rsi],5` | result code 6 or 5 written to out ptr | [V] |
| entry sets byte | [rsi+8] | 1 | W: `c296c58  mov byte ptr [rsi+8],1` | ready/done flag set | [V] |

## Answer table — sub_bc41420 args (from live capture dragon_texture_caller_bc41420.txt)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| arg3 (R8) | reg | 8 | - | `bc41454  mov rbx,r8` (14CE90 in live capture) | [V live] |
| arg2 out ptr (RDX) | reg | 8 | R: `bc41457  mov rdi,rdx` | out ptr (14CE00 in live capture) | [V live] |
| arg3 (R8) | reg | 8 | - | `bc41454  mov rbx,r8` (14CE90 in live capture) | [V live] |
| arg4 desc ptr (R9) | reg | 8 | R: `bc41451  mov r15,r9` | desc ptr (53149F91088 in live capture, same as entry arg3) | [V live] |

## CLOSES?

NO — the createTexture issuance chain is now proven [V live] end to end: sub_4e05e50 → sub_bc41420 (`4e05f77  call 0xBC41420`) → sub_c296b50 (`0xBC41B39  call 0xC296B50`) → sub_bc73bf0 (`c296d79  call 0xBC73BF0`) → sub_bc73770 (`0xBC73EA8  call 0xBC73770`, cmd byte 0x0E producer) → bgfx dispatcher [vptr+0xD0] createTexture case (`0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]`) → createTexture 0xe8143c0. Handle stored at texture_obj+0x00 (`0xC296E26  mov [rdi],ax`). However, the static link from texgroup_load (or any MC-side texture code) to sub_4e05e50 remains indirect: sub_4e05e50 is entered via `call qword ptr [0xF99FFA0]` at 0x1289490 inside sub_12893d0 (ret=0x1289496, mc_root_4e05e50_callers.txt, 150 hits) where [0xF99FFA0] = sub_eea6040 (`jmp rax`, read-only .rdata, no writer — r37); rax holding sub_4e05e50 is a runtime value not resolvable statically. Static work on this link is exhausted; a capture at sub_eea6040 entry reading rax would be needed to close it. Atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## TOOL REQUESTS

- verify_oc.py + delegate.py checks required before CLOSES? is final. No new helper scripts written, no temporary files left behind.
