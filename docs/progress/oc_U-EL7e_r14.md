## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending" — half 2: texture/atlas management

Item line: docs/RENDER_CHECKLIST.md:338 — half 1 (sampler flag decode + sampler cache 6ax) closed [V] (docs/functions/e820500.md); this unit proves half 2: the Minecraft-side pack->GPU chain to D3D12 createTexture 0xe8143c0.

Exe (data only, never launched): C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only. Every `0xRVA  instr` cell below was re-disassembled with rdis.exe and is verbatim (addresses normalized by verify_oc.py; instruction text copied exactly).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) and/or capture cross-verified; [I] inferred from structure/BGFX_MAP.md/stub headers, not instruction-proven; [UNVERIFIED] not shown by any instruction/capture.

Row rule: one annotated row per distinct offset, all its sites listed; offset | name | size | read/store addr | verbatim `0xRVA  instr` | meaning (only if an instruction/string shows it, else '-') | tag. Sizes from instruction (qword 8, dword 4, word 2, byte 1; "call" for calls). No raw instruction dumps outside table cells; no skipped offsets in the chain links.

## Chain proven this unit (Minecraft side -> GPU -> D3D12 createTexture 0xe8143c0)

Every link below is instruction-verified [V] and cross-verified against the pre-existing live captures (captures were made by the orchestrator; I only read them, per static-only rule):

- sub_1289400 (indirect entry point: xref.py callers = EMPTY, and a full-exe scan for the immediate 0x1289400 found 0 hits; reachable only indirectly)
  `1289490 call qword ptr [0xF99FFA0]` -> sub_4e05e50 ; capture mc_root_4e05e50_callers: ret=0x1289496, 150 hits / 32 samples [V]
- sub_4e05e50 (Minecraft-side texture root; object carries "tex\0" name)
  `4e05f77 call 0xBC41420` -> sub_bc41420 ; capture dragon_texture_caller_bc41420: ret=0x4E05F7C [V]
- sub_bc41420 (dragon-layer entry from MC code; RCX = texture object)
  `bc41b39 call 0xC296B50` -> dragon entry 0xc296b50 ; capture dragon_texture_entry_c296b50: ret=0xBC41B3E [V]
- dragon entry 0xc296b50
  `c296d79 call 0xBC73BF0` -> wrapper 0xbc73bf0 ; capture bgfx_texture_wrapper_bc73bf0: ret=0xC296D7E [V]
- wrapper 0xbc73bf0
  `bc73ea8 call 0xBC73770` -> producer sub_bc73770 ; capture bgfx_createtexture_producer: ret=0xBC73EAD [V]
- producer sub_bc73770
  writes bgfx command entry cmd=0x0E (byte 14 = createTexture), [u16 handle][u64 Memory*][u32 flags][u8 skip] per BGFX_MAP.md section 6et [V]
- bgfx dispatcher byte-14 case (0xBC6A28C..0xBC6A2C8)
  `bc6a2c2 call qword ptr [0xF99FFA0]` (vtable slot 26 [rax+0xd0]) -> createTexture 0xe8143c0 ; capture createtexture_callers: one caller, ret=0xBC6A2C8 [V]
- createTexture 0xe8143c0 -> D3D12 backend (slot 26 per BGFX_MAP.md:403; Tables 1-8 decoded in oc_U-EL7e_r1.md) [V]

Handle destination [V]: `c296e26 mov [rdi],ax` stores the bgfx handle (ax; 0xFFFF on failure) at [texture_obj+0x00]. The nested texture object is reached at MC object +0x58 (`4e05f68 add rdi,0x58`, "tex\0" name at its +0x18); the MC object root seen by sub_4e05e50 has "tex\0" at +0x70 per live capture. Binding [texture_obj+0x00] to a named mce::TexturePtr/ClientTexture field is [I]: TexturePtr.h/ClientTexture.h are stubs (32B / empty) without proven field addresses.

Residual (not statically provable, documented not redone): the static caller of sub_1289400 (indirect only — live capture is the evidence for that edge); the texgroup_load 0x5421c90 / texload 0x58a1310 connection (texload xref EMPTY; texgroup_load calls texture cache 0x18718d0 directly and never texload/texload_task; that chain parked per r2/r3).

## Annotated instruction map (one row per distinct offset)

| offset | name | size | read/store addr | verbatim `0xRVA  instr` | meaning | tag |
| 0xBC6A296 | dispatcher case byte-14 (createTexture) | 1B | read [rsp+0x6a] | `0xBC6A296  movzx r10d,byte ptr [rsp+0x6a]` | u8 skip flag (cmd arg) | [V] |
| 0xBC6A29C | dispatcher case byte-14 | 4B | read [rsp+0x90] | `0xBC6A29C  mov r9d,[rsp+0x90]` | u32 create flags | [V] |
| 0xBC6A2A4 | dispatcher case byte-14 | 8B | read [rsp+0x60] | `0xBC6A2A4  mov r8,[rsp+0x60]` | u64 Memory* texture-memory ptr | [V] |
| 0xBC6A2A9 | dispatcher case byte-14 | 2B | read [rsp+0x6e] | `0xBC6A2A9  movzx edx,word ptr [rsp+0x6e]` | u16 bgfx texture handle | [V] |
| 0xBC6A2AE | dispatcher case byte-14 | 8B | read [rcx] | `0xBC6A2AE  mov rax,[rcx]` | load renderer-context vtable ptr | [V] |
| 0xBC6A2B1 | dispatcher case byte-14 | 8B | read [rax+0xd0] | `0xBC6A2B1  mov rax,[rax+0xd0]` | vtable slot 26 = createTexture fn ptr (BGFX_MAP.md:403) | [V] |
| 0xBC6A2C2 | dispatcher case byte-14 | call | indirect via [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | createTexture 0xe8143c0; capture ret=0xBC6A2C8 is the next instruction | [V] |
| 0xBC6A2C8 | dispatcher case byte-14 | 8B | - | `0xBC6A2C8  test rax,rax` | test createTexture result; capture ret site | [V] |
| 0xBC73AA3 | producer sub_bc73770 | 8B | read [rdi+0x1CFD0C8] | `0xBC73AA3  mov rbx,[rdi+0x1cfd0c8]` | load bgfx frame/command-buffer ptr | [V] |
| 0xBC73AAA | producer sub_bc73770 | 1B | write [rbp+0x2c] | `0xBC73AAA  mov byte ptr [rbp+0x2c],0xE` | command byte 14 = createTexture | [V] |
| 0xBC73AC9 | producer sub_bc73770 | call | read [rbp+0x2c]; store bgfx command buffer | `0xBC73AC9  call 0xEBCE390` | memcpy cmd byte (1B) | [V] |
| 0xBC73AF5 | producer sub_bc73770 | call | read [rbp+0x2e]; store bgfx command buffer | `0xBC73AF5  call 0xEBCE390` | memcpy u16 handle (2B) | [V] |
| 0xBC73B1A | producer sub_bc73770 | call | read [rbp+0x18]; store bgfx command buffer | `0xBC73B1A  call 0xEBCE390` | memcpy u64 Memory* (8B) | [V] |
| 0xBC73B3F | producer sub_bc73770 | call | read [rbp+0x28]; store bgfx command buffer | `0xBC73B3F  call 0xEBCE390` | memcpy u32 flags (4B) | [V] |
| 0xBC73B64 | producer sub_bc73770 | call | read [rbp+0x2d]; store bgfx command buffer | `0xBC73B64  call 0xEBCE390` | memcpy u8 skip (1B) | [V] |
| 0xBC73EA8 | wrapper 0xbc73bf0 | call | - | `0xBC73EA8  call 0xBC73770` | invoke cmd producer; capture ret=0xBC73EAD | [V] |
| 0xC296D74 | dragon entry 0xc296b50 | 4B | - | `0xC296D74  mov ecx,6` | createTexture cmd selector before wrapper call | [V] |
| 0xC296D79 | dragon entry 0xc296b50 | call | - | `0xC296D79  call 0xBC73BF0` | invoke bgfx wrapper; capture ret=0xC296D7E | [V] |
| 0xC296E26 | dragon entry 0xc296b50 | 2B | write [rdi] = [texture_obj+0x00] | `0xC296E26  mov [rdi],ax` | bgfx handle stored into texture object (0xFFFF on failure path) | [V] |
| 0xC296F44 | dragon entry 0xc296b50 | 8B | write [rsi] | `0xC296F44  mov [rsi],rdi` | out block: texture object ptr | [V] |
| 0xC296F50 | dragon entry 0xc296b50 | 1B | write [rsi+8] | `0xC296F50  mov [rsi+8],al` | out block: status byte | [V] |
| 0xBC41446 | sub_bc41420 | 8B | read [rcx+0x28] | `0xBC41446  cmp qword ptr [rcx+0x28],0` | texture-object null check; RCX = texture object ("tex\0" name) | [V] |
| 0xBC41B39 | sub_bc41420 | call | - | `0xBC41B39  call 0xC296B50` | invoke dragon entry; capture ret=0xBC41B3E | [V] |
| 0x4E05E71 | sub_4e05e50 | 8B | read [rcx+0x18] | `0x4E05E71  mov rax,[rcx+0x18]` | walk MC texture object shared_ptr field +0x18 | [V] |
| 0x4E05E86 | sub_4e05e50 | call | indirect via [0xF99FFA0] | `0x4E05E86  call qword ptr [0xF99FFA0]` | shared_ptr retain on +0x18 (rdis target sub_eea6040 at analysis time) | [V] |
| 0x4E05F68 | sub_4e05e50 | - | - | `0x4E05F68  add rdi,0x58` | nested texture object at MC object +0x58 | [V] |
| 0x4E05F74 | sub_4e05e50 | 8B | - | `0x4E05F74  mov rcx,rdi` | RCX = nested texture object for dragon call | [V] |
| 0x4E05F77 | sub_4e05e50 | call | - | `0x4E05F77  call 0xBC41420` | invoke sub_bc41420; capture ret=0x4E05F7C + static match | [V] |
| 0x128947D | sub_1289400 | 8B | read [r13+0x10] | `0x128947D  mov rcx,[r13+0x10]` | fetch texture-object ptr from entry slot | [V] |
| 0x1289490 | sub_1289400 | call | indirect via [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | invoke sub_4e05e50 at runtime; capture ret=0x1289496 (150 hits) | [V] |
| 0x1289496 | sub_1289400 | 1B | - | `0x1289496  nop` | capture ret label (call site just before) | [V] |
| 0x128949B | sub_1289400 | 8B | write [r13+0x10] | `0x128949B  mov qword ptr [r13+0x10],0` | clear entry slot after dispatch | [V] |

CLOSES? YES — the blocking fact (Minecraft-side pack->GPU chain reaches D3D12 createTexture 0xe8143c0) is proven link by link [V], capture cross-verified end to end, backend slot 26 = 0xe8143c0 already [V] in oc_U-EL7e_r1.md. Remaining gaps are documented above as residual: static caller of sub_1289400 (indirect only, live-capture evidence) and the mce::TexturePtr/ClientTexture field binding ([I], stub headers). Neither breaks the chain proof.

## TOOL REQUESTS

none — all required data captured and disassembled; no further captures, rtools, or game launch needed.
