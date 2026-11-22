## NEXT
DONE

Unit U-EL7e — texture/atlas management (L7e). MC-side pack->GPU root sub_4e05e50 -> createTexture + handle store.

CLOSES? NO
Blocking fact: no static path texgroup_load(0x5421c90)/texload(0x58a1310) -> sub_4e05e50 exists. sub_4e05e50 has 0 static xrefs (xref.py EMPTY, imm/ripscan 0 hits, rdis "0 xrefs in") and is entered only at runtime via sub_12893d0's vptr[1] tail-call through CFG trampoline [0xF99FFA0] = sub_eea6040 (`0xEEA6040  jmp rax`, read-only .rdata initializer, no code writer), confirmed live (mc_root_4e05e50_callers.txt: CALLER ret=0x1289496, 150 hits/32 samples, RCX objects carry texture names). sub_12893d0's 4 static callers do not reach texgroup_load/texload/texload_task. Static analysis exhausted (r37/r42). Everything else in the item IS [V]-proven: sampler half (6ax), D3D12 backend texture-management chain, createTexture issuance (sub_bc73770 command byte 0x0E -> bgfx dispatcher -> createTexture 0xe8143c0), and handle stored at texture_obj+0x00.

[V]-proven this session — static link resolution (the [0xF99FFA0] trampoline bind):
- sub_eea6040 = `0xEEA6040  jmp rax` [V dis]; [data_f99ffa0] = sub_eea6040; [0xF99FFA0] read-only .rdata CFG thunk, no writer [V dis]. Pattern (BGFX_MAP.md line 176): set rax=real target, `call qword ptr [0xF99FFA0]`, sub_eea6040 jmps to rax.
- Dispatch site sub_12893d0 (0x12893d0..0x12895d3): rcx=[r13+0x10], rax=vptr[1] of that object, tail-call `call qword ptr [0xF99FFA0]` at 0x1289490 (ret=0x1289496) dispatches sub_4e05e50 [V dis + V live mc_root_4e05e50_callers.txt line 3].
- Full issuance chain to createTexture + handle store already [V live] (prior iterations, not redone): sub_4e05e50 -> sub_bc41420 (`0x4E05F77  call 0xBC41420`, live ret=0x4E05F7C) -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 (cmd byte 0x0E) -> bgfx dispatcher -> createTexture 0xe8143c0; handle at [texture_obj+0x00] via `0xC296E26  mov [rdi],ax` [V live r7].

sdk TexturePtr.h [V file read]: mce::TexturePtr = 32B, mClientTexture+0x00, mResourceLocationPtr+0x10, NO vptr — plain shared_ptr carrier. So the vptr[1]=sub_4e05e50 dispatch target sits on the MC texture object passed as RCX ([r13+0x10], carries 'tex' name + width/height), not on TexturePtr itself; whether RCX is literally TexturePtr vs. an MC object containing TexturePtr is not instruction-provable [I].

## Table 1 — [0xF99FFA0] trampoline bind: static dispatch site for sub_4e05e50 (MC-side pack->GPU root)

| offset | size | site | instr | meaning |
| 0xeea6040 | 2 | sub_eea6040 | `0xEEA6040  jmp rax` | CFG-thunk trampoline target = jmp rax; [data_f99ffa0] = sub_eea6040; read-only .rdata initializer, no code writer [V dis] |
| 0x128947d | 8 | sub_12893d0 | `0x128947d  mov rcx,[r13+0x10]` | rcx = object at [r13+0x10] passed as this (TexturePtr*-like MC texture object); guard-tested non-null [V dis] |
| 0x1289489 | 8 | sub_12893d0 | `0x1289489  mov rax,[rax+8]` | rax = vptr[1] of [r13+0x10]; the virtual method tail-called at 0x1289490 [V dis] |
| 0x1289490 | 8 | sub_12893d0 | `0x1289490  call qword ptr [0xF99FFA0]` | tail-call through CFG trampoline [0xF99FFA0]=sub_eea6040 (jmp rax); ret=0x1289496 dispatches sub_4e05e50 (150 hits/32 samples) [V dis + V live] |
| 0x4e05e50 | 1 | sub_4e05e50 | `0x4E05E50  push rbp` | MC-side pack->GPU root entry; takes TexturePtr* in RCX [V dis + V live] |
| 0xc296e26 | 2 | sub_c296b50 | `0xC296E26  mov [rdi],ax` | returned 16-bit handle stored at texture_obj+0x00 [V dis + V live r7] |

Atlas stitchers remain separate open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit (MIRROR_SKIP).
