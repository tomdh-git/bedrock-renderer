# Dossier: sub 0xbc5fce0 (Minecraft Bedrock 1.26.62.01)

Function: sub_bc5fce0, range [0xbc5fce0, 0xbc600fd), size 0x41d bytes, depth 2, milestone 1, region bgfx, status D0.
Name: "D3D12 submit RTX override" (root); callees_in_set: none; callees_outside_set: 0xe951550 (boundary, crt).
Source: src/client/features/render/native/bgfx/sub_bc5fce0.cpp (+ .h).
Header: src/client/features/render/native/bgfx/sub_bc5fce0.h (layout constants + static_asserts + signature).

## Contract (docs/RENDER_NATIVE_SPEC.md)
Lift = C++ that does exactly what the exe function does: same reads, same writes (value and order), same calls in the same order, same return, exact x64 ABI signature. No stubs, no skipped branches, no null guards/SEH the original lacks. Every call target must be a lifted function, a boundary wrapper (docs/data/native_boundary.tsv), or a compiler intrinsic (memcpy/memset).

## Signature (x64 Microsoft ABI) [V]
extern "C" void sub_bc5fce0(void* a1, void* a2, void* a3);   // rcx=a1, rdx=a2, r8=a3, r9 unused
Return: void (eax is never written before `ret`; the original returns garbage) [V].

Arguments:
- a1 (rcx): object with a vfptr at +0; vfptr[0x198] and vfptr[0x1A0] are read and invoked through the [0xF99FFA0] thunk cell.
- a2 (rdx): context block. [a2+0x08] = pointer P; [P] = destination base (r15). [a2+0x10] = pointer Q; [Q] = vertex buffer base (r12).
- a3 (r8/rsi): parameter block. [a3+0x00] = u16 element array (rc*cc elements); [a3+0x0C] = u16 cc (column count); [a3+0x0E] = u16 rc (row count); [a3+0x10] = u8 flag (constant select).

## Register/argument map [V]
rcx=a1, rdx=a2, r8=a3 (copied to rsi), r9 unused.
Locals (tracking names): ebx=row, edi=col, ebp=element counter (+6/elem, cap 0x1800), r14d=vertex counter (+4/elem), r12=vertex cursor (+0xC/elem), r15=dest cursor (+0x70/elem), slot34=[rsp+0x34]=ebx+1, xmm6..xmm15 temporaries.
Stack: sub rsp,0x158; cookie slot [rsp+0xB8]; block built at [rsp+0x40]..[rsp+0xAC] (0x70 bytes); [rsp+0x34] scratch.

## Phases (instruction-complete; ranges cite [bc5fce0, bc600fd)) [V]

// 0xbc5fce0..0xbc5fd61
Prologue: push r15,r14,r13,r12,rsi,rdi,rbp,rbx; sub rsp,0x158; save xmm14..xmm7; spill rsi=r8 (a3), [rsp+0x28]=rdx (a2), [rsp+0x38]=rcx (a1); stack cookie [rsp+0xB8] = [0x1230A0C0] ^ rsp.
// 0xbc5fd62..0xbc5fd9b
Flag byte [a3+0x10]: if 0 -> xmm6=C0=[0xEF3F000], xmm7=C2=[0xEEC8060], xmm8=C1=[0xF085AA8]; else -> xmm6=0, xmm7=C0=[0xEF3F000], xmm8=C3=[0xEFC13A4].
// 0xbc5fd9b..0xbc5fdaf
Call #1: rax=vfptr[0x198] (dead read, same reads), then `call qword ptr [0xF99FFA0]`. The cell holds sub_eea6040, which is `jmp rax` (verified by disassembly of 0xEEA6040: `eea6040 jmp rax`), so this is the virtual call vfptr[0x198](a1, a2). Return value unused.
// 0xbc5fdb5..0xbc5fdbc
rc = u16[a3+0xE]; if rc == 0 -> jump to epilogue at 0xbc60072.
// 0xbc5fdc2..0xbc5fde9
Constants: xmm9=[0xEFC13A4] (C3), xmm10=[0xF2CC750], xmm11=[0xF441400], k12 = 4 u16 lanes from [0xF441410] (movq xmm12). ebx=0, edi=0.
// 0xbc5fde9..0xbc5fdf5 and 0xbc5fdf5..0xbc5fe0f
Call #2 site (per row, on row exhaustion): rax=vfptr[0x1A0] (dead read), then `call qword ptr [0xF99FFA0]` => vfptr[0x1A0](a1, a2, ebp=element counter).
// 0xbc5fe25..0xbc5fe6b
Row/col loop headers: row ebx in [0,rc), col edi in [0,cc), cmovae resets edi=0 at row entry; element body at 0xbc5fea0.
// 0xbc5fe6b..0xbc5fea0
Element fetch: v = u16 data[cc*ebx + edi] (data = [a3+0x00]); hi = [r13], lo = [r13-1] (little-endian u16). slot34=[rsp+0x34]=ebx+1.
// 0xbc5fea0..0xbc5fecd
Skip: if v == 0 -> next col; if (hi == 0x20 && lo < 0x10) -> next col.
// 0xbc5fecd..0xbc5ffe5
Build the 0x70-byte block at [rsp+0x40]:
  [+0x00] f32 = (float)edi * xmm9
  [+0x04] f32 = (float)ebx * xmm8
  [+0x08] u32 = 0
  [+0x0C] u32 = T[lo & 0xF]        (T = u32 table at [0xF441880])
  [+0x10] u32 = T[lo >> 4]
  [+0x14] f32 = (float)hi * xmm9 * xmm10 + xmm11
  [+0x18] f32 = xmm6 (0 or C0)
  [+0x1C] f32 = (float)(edi+1) * xmm9
  [+0x20] f32 = (float)ebx * xmm8
  [+0x24] u32 = 0
  [+0x28] u32 = T[lo & 0xF]
  [+0x2C] u32 = T[lo >> 4]
  [+0x30] f32 = (float)(hi*8+8) * xmm10 + xmm11   (xmm3; xmm13/xmm0/xmm3/xmm1 values re-used where identical)
  [+0x34] f32 = xmm6
  [+0x38] f32 = (float)(edi+1) * xmm9
  [+0x3C] f32 = (float)(ebx+1) * xmm8
  [+0x40] u32 = 0
  [+0x44] u32 = T[lo & 0xF]
  [+0x48] u32 = T[lo >> 4]
  [+0x4C] f32 = (float)(hi*8+8) * xmm10 + xmm11
  [+0x50] f32 = xmm7 (C2 or C0)
  [+0x54] f32 = (float)edi * xmm9
  [+0x58] f32 = (float)(ebx+1) * xmm8
  [+0x5C] u32 = 0
  [+0x60] u32 = T[lo & 0xF]
  [+0x64] u32 = T[lo >> 4]
  [+0x68] f32 = (float)hi * xmm9 * xmm10 + xmm11
  [+0x6C] f32 = xmm7
// 0xbc5ffe5..0xbc5fffc
`call 0xEBCE390` (rcx=r15, rdx=&block, r8d=0x70) => copies the 0x70-byte block to *r15.
// 0xbc60001..0xbc6002e
r15 += 0x70; [r12+0x00] = r14w; [r12+0x02..0x09] = 8 bytes = r14d lanes + k12 lanes (paddw wraparound); [r12+0x0A] = r14w; r14d += 4; r12 += 0xC; ebp += 6.
// 0xbc60031..0xbc6004e
Next col: edi++; if edi >= cc -> row transition; if ebp < 0x1800 -> next element.
// 0xbc6004e..0xbc6006d
Row transition: if ebp > 0x17FF -> cap path (0xbc60067); reload rc=[a3+0x0E]; ebx++; if slot34(ebx+1) >= rc -> final call; else next row (edi reset to 0).
// 0xbc6006d..0xbc5fe1f (final call)
Call #2: vfptr[0x1A0](a1, a2, ebp) via [0xF99FFA0]; ebx = r8d_at_entry; if ebx >= rc -> epilogue, else next row.
// 0xbc60067..0xbc6006d (cap path): r8d = ebx -> final call (no ebx increment).
// 0xbc60072..0xbc600eb
Epilogue: rax = [rsp+0xB8] ^ rsp; if [0x1230A0C0] != rax -> failure path; restore xmm6..xmm14, rsp, regs; ret.
// 0xbc600ec..0xbc600fc
Failure path: `mov rcx,[rsp+0xB8]; xor rcx,rsp; call 0xE951550; int3` (sub_e951550 = boundary crt, noreturn).

## Calls [V]
| Address | Instruction | Target | Class | Disposition |
|---|---|---|---|---|
| 0xbc5fdaf | `call qword ptr [0xF99FFA0]` | cell -> sub_eea6040 (`jmp rax`) => vfptr[0x198](a1,a2) | not in CALLEES set, not in native_boundary.tsv | UNRESOLVED CALL (expressed as vtable-slot invocation) |
| 0xbc5fe0f | `call qword ptr [0xF99FFA0]` | cell -> sub_eea6040 => vfptr[0x1A0](a1,a2,ebp) | not in CALLEES set, not in native_boundary.tsv | UNRESOLVED CALL (expressed as vtable-slot invocation) |
| 0xbc5fffc | `call 0xEBCE390` | sub_ebce390 -> jmp 0xEEC6EC0 -> jmp [0xF9A8A98]; real target only known at runtime | not in CALLEES set, not in native_boundary.tsv | UNRESOLVED CALL (direct call with observed args) |
| 0xbc600f7 | `call 0xE951550` | sub_e951550 | boundary, crt (native_boundary.tsv line 467) | native::Boundary<void,std::uintptr_t> sub_e951550("sub_e951550") |

Reachability of sub_eea6040/sub_ebce390: sub_eea6040 at 0xEEA6040 is `jmp rax` (verified by disassembly); sub_ebce390 at 0xEBCE390 is `jmp 0xEEC6EC0`, and sub_eec6ec0 at 0xEEC6EC0 is `jmp qword ptr [0xF9A8A98]`. Neither address appears in docs/data/native_functions.tsv or docs/data/native_boundary.tsv.

## Struct fields touched [V]
- a1+0x00 vfptr (read), vfptr+0x198 / +0x1A0 (read, dead values): Bc5fce0Params/Bc5fce0Ctx not game structs; modeled in sub_bc5fce0.h with static_asserts.
- a2+0x08 (read pointer), a2+0x10 (read pointer): static_asserts offset 0x08 / 0x10.
- a3+0x00..0x10 (reads): static_asserts offset 0x0C / 0x0E / 0x10.
- Writes: *r15 block copy (0x70 bytes/elem), *r12 vertex records (0xC bytes/elem), stack block at [rsp+0x40..0xAC], cookie slot [rsp+0xB8] (written in prologue, read in epilogue).
- Data reads: [0x1230A0C0] cookie, [0xEF3F000], [0xEEC8060], [0xF085AA8], [0xEFC13A4]x2, [0xF2CC750], [0xF441400], [0xF441410] (8 bytes), [0xF441880] table.

## Ownership / threading
No allocations, no handles, no cross-thread visibility within the function; writes go to caller-owned buffers. Pure-differential V2 not applicable (memory writes through runtime-derived pointers with extent depending on input counts; no static footprint declared).

## Reversed source (complete)
See src/client/features/render/native/bgfx/sub_bc5fce0.cpp (first line `// LIFT 0xbc5fce0 size 0x41d 1.26.62.01 sub_bc5fce0`). Every instruction of [0xbc5fce0, 0xbc600fd) is inside a cited `// 0xA..0xB` range or is a verbatim quoted `call`; every `call` is quoted verbatim as `0xRVA  call ...`. The translation is instruction-faithful: gotos mirror the original control flow, register locals keep their names, all reads/writes/calls/return match.

Blocking: the three calls above target functions outside the CALLEES set and outside native_boundary.tsv, so per the GOAL the unit cannot be closed as lifted; they are documented here as UNRESOLVED CALLs and no wrapper was invented.
