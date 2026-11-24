## NEXT
DONE
step 2

DONE: disassembly of 0xbc2be20..0xbc2c00c (0x1ec bytes, 102 instructions, ends with `ret` at 0xbc2c00b; rdis region header [0xbc2be20..0xbc2de20) size 0x2000 is the enclosing region, not the function size - size 0x1ec per docs/data/native_functions.tsv and the unit data) fully read from the exe; prologue/epilogue, field copies, the switch on byte [a1+0x70] via the table at 0xF440D90, and both direct calls identified. Both call targets are outside the CALLEES list (empty for this unit [V]) and classified `lift` (not boundary) in docs/data/native_boundary.tsv [V: 504 rows, entries `0xe869ff0 lift auto-unresolved->lift` and `0x5669770 lift auto-unresolved->lift`] → UNRESOLVED CALL. Per the GOAL the unit stops here; no wrapper invented, no source/header written.

## UNIT
- Unit: U-EX1.bc2be20; checklist line X1.bc2be20 LIFT sub_bc2be20 (0xbc2be20, 0x1ec bytes, depth 1, D0, 0 callees in set) [V: docs/progress/_d_U-EX1.bc2be20.txt]
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe, version 1.26.62.01, RVAs relative to image base [V: OPENCODE_BRIEF.md]
- Disassembly source: `rdis.exe <exe> dis 0xbc2be20 120` (full listing, 102 instructions, last instruction `ret` at 0xbc2c00b) [V]

## FUNCTION (mechanical facts, all [V] from the listing)
- Address/size: 0xbc2be20, size 0x1ec (occupies 0xbc2be20..0xbc2c00c exclusive; final instruction `ret` at 0xbc2c00b; bytes 0xbc2c00c+ are padding/next function, not part of this unit).
- Depth 1, milestone 1, region bgfx, status D0; 9 xrefs in [V: rdis header].
- ABI (x64 Microsoft): arg1 `dst` = rcx (copied to r10 at 0xbc2be36, spilled to [rbp-8] at 0xbc2bf27); arg2 `src` = rdx (copied to rsi at 0xbc2be33). Return value in rax = old `*(u64*)(src+0x110)` [V: `mov rax,[rsi+0x110]` at 0xbc2bf31; rax is not written again before `ret` at 0xbc2c00b]. Signature equivalent: `u64 sub_bc2be20(void* dst, const void* src)` — the moved-out u64 at src+0x110 is returned after the move.
- Stack frame: sub rsp,0x38; rbp = rsp+0x30; [rbp] = 0xFFFFFFFFFFFFFFFE (cookie); [rbp-0x10] = &dst+0x38 (spill, 0xbc2bef0); [rbp-8] = dst (spill, 0xbc2bf27).
- No exception handling, no null guards, no SEH [V: straight-line code, only test/je/jmp/ja branches; no __try opcodes].
- Calls in the function: exactly two, both direct: `0xbc2bf2b  call 0xE869FF0` and `0xbc2bf5c  call 0x5669770`. One indirect jump `bc2beb5  jmp r9` (switch table dispatch).

## REVERSED ANALYSIS (instruction-complete: every instruction of [0xbc2be20, 0xbc2c00c) is inside one cited range below; every instruction quoted verbatim from the exe; every call quoted verbatim)

// 0xbc2be20..0xbc2be39  prologue + argument aliasing
0xbc2be20  push rbp
0xbc2be21  push rsi
0xbc2be22  sub rsp,0x38
0xbc2be26  lea rbp,[rsp+0x30]
0xbc2be2b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0xbc2be33  mov rsi,rdx
0xbc2be36  mov r10,rcx
C-like: dst=r10 (rcx), src=rsi (rdx); frame cookie -2 at [rbp].

// 0xbc2be39..0xbc2be5e  copy u64@0x0, u64@0x8, u64@0x10; clear src+0x8; zero dst+0x18 and dst+0x28
0xbc2be39  mov rax,[rdx]
0xbc2be3c  mov [rcx],rax
0xbc2be3f  xorps xmm0,xmm0
0xbc2be42  movups [rcx+8],xmm0
0xbc2be46  mov rax,[rdx+8]
0xbc2be4a  mov [rcx+8],rax
0xbc2be56  movups [rdx+8],xmm0
0xbc2be4e  mov rax,[rdx+0x10]
0xbc2be52  mov [rcx+0x10],rax
0xbc2be5a  movups [rcx+0x18],xmm0
0xbc2be5e  mov qword ptr [rcx+0x28],0
C-like: dst[0x00]=src[0x00]; dst[0x08]=0; dst[0x08]=src[0x08]; src[0x08]=0; dst[0x10]=src[0x10]; dst[0x18]=0; dst[0x28]=0. (xmm0=0 after xorps at 0xbc2be3f; not reloaded before 0xbc2be56/0xbc2be5a.)

// 0xbc2be66..0xbc2be91  byte@0x30, xmm@0x38/0x48; clear src+0x40 and src+0x48; u64@0x58; dst+0x70=0xFF
0xbc2be66  movzx eax,byte ptr [rdx+0x30]
0xbc2be6a  mov [rcx+0x30],al
0xbc2be6d  movups xmm1,[rdx+0x38]
0xbc2be71  movups xmm2,[rdx+0x48]
0xbc2be75  mov qword ptr [rdx+0x40],0
0xbc2be7d  movups [rdx+0x48],xmm0
0xbc2be81  movups [rcx+0x38],xmm1
0xbc2be85  movups [rcx+0x48],xmm2
0xbc2be89  mov rax,[rdx+0x58]
0xbc2be8d  mov [rcx+0x58],rax
0xbc2be91  mov byte ptr [rcx+0x70],0xFF
C-like: dst[0x30]=src[0x30] (byte); dst[0x38]=src[0x38]; dst[0x48]=src[0x48]; src[0x40]=0; src[0x48]=0; dst[0x58]=src[0x58]; dst[0x70]=0xFF.

// 0xbc2be95..0xbc2beb5  switch tag = byte [src+0x70]; table at 0xF440D90
0xbc2be95  movzx eax,byte ptr [rdx+0x70]
0xbc2be99  cmp rax,3
0xbc2be9d  ja short 0xBC2BEEC
0xbc2be9f  lea rcx,[r10+0x60]
0xbc2bea3  lea rdx,[rsi+0x60]
0xbc2bea7  lea r8,[0xF440D90]                            ; [data_f440d90]
0xbc2beae  movsxd r9,[r8+rax*4]
0xbc2beb2  add r9,r8
0xbc2beb5  jmp r9
C-like: tag = src[0x70]; if (tag > 3) goto default(0xbc2beec); rcx=&dst+0x60; rdx=&src+0x60; r8=&table(0xF440D90); goto table[tag]. Table entries read from the disassembly targets: table[0]=0xbc2beb8, table[1]=0xbc2bec0, table[2]=0xbc2bec8 [V]. table[3] (dword at 0xF440D90+0xC) is data, not reachable by code disassembly; the read-only tool set (rdis dis/fn/walk) disassembles code only and has no data-dump command, so table[3] was not read from the exe [UNVERIFIED: 0xF440D90+0xC jump-table entry 3 target].

// 0xbc2beb8..0xbc2bebe  case 0: u64 copy at +0x60
0xbc2beb8  mov rdx,[rdx]
0xbc2bebb  mov [rcx],rdx
0xbc2bebe  jmp short 0xBC2BEE8
C-like: dst[0x60..0x68] = *(u64*)src[0x60]; goto bee8. (src+0x60 not cleared; dst+0x68 untouched.)

// 0xbc2bec0..0xbc2bec6  case 1: 16-byte copy at +0x60
0xbc2bec0  movups xmm0,[rdx]
0xbc2bec3  movups [rcx],xmm0
0xbc2bec6  jmp short 0xBC2BEE8
C-like: *(u128*)dst[0x60] = *(u128*)src[0x60]; goto bee8. (dst+0x68 untouched.)

// 0xbc2bec8..0xbc2bed4  case 2: zero dst+0x60, addref src+0x68 pointee
0xbc2bec8  movups [rcx],xmm0
0xbc2becb  mov rcx,[rsi+0x68]
0xbc2becf  test rcx,rcx
0xbc2bed2  je short 0xBC2BED8
0xbc2bed4  lock inc dword ptr [rcx+8]
C-like: xmm0 is still 0 (last written at 0xbc2be3f, never reloaded on this path) → *(u128*)dst[0x60] = 0; p = src[0x68]; if (p != 0) lock++ *(u32*)(p+8); then fall through to bed8.

// loc_bc2bed8  (case 2 fallthrough): copy both pointer fields
0xbc2bed8  mov rcx,[rsi+0x60]
0xbc2bedc  mov [r10+0x60],rcx
0xbc2bee0  mov rcx,[rsi+0x68]
0xbc2bee4  mov [r10+0x68],rcx
C-like: dst[0x60]=src[0x60]; dst[0x68]=src[0x68]. (No src clear, no addref beyond the case-2 increment above.)

// loc_bc2bee8  (cases 0/1 join): store tag
0xbc2bee8  mov [r10+0x70],al
C-like: dst[0x70] = tag.

// loc_bc2beec  default (tag > 3): dst+0x70 keeps 0xFF (set at 0xbc2be91); no store of tag; shared tail begins
0xbc2beec  lea rax,[r10+0x38]
0xbc2bef0  mov [rbp-0x10],rax
0xbc2bef4  mov rax,[rsi+0x88]
0xbc2befb  mov [r10+0x88],rax
0xbc2bf02  movups xmm0,[rsi+0x78]
0xbc2bf06  movups [r10+0x78],xmm0
0xbc2bf0b  mov rax,[rsi+0x90]
0xbc2bf12  mov [r10+0x90],rax
0xbc2bf19  lea rcx,[r10+0x98]
0xbc2bf20  lea rdx,[rsi+0x98]
0xbc2bf27  mov [rbp-8],r10
0xbc2bf2b  call 0xE869FF0
0xbc2bf30  nop
C-like: [rbp-0x10]=&dst+0x38 (spill); dst[0x88]=src[0x88]; dst[0x78]=src[0x78]; dst[0x90]=src[0x90]; [rbp-8]=dst (spill); call 0xE869FF0 with rcx=&dst+0x98, rdx=&src+0x98 [verbatim quote above]; nop after call.

// 0xbc2bf31..0xbc2bf61  move u64@0x110 (clear source), then 16-byte copy at +0x118
0xbc2bf31  mov rax,[rsi+0x110]
0xbc2bf38  mov rcx,[rbp-8]
0xbc2bf3c  mov [rcx+0x110],rax
0xbc2bf43  mov qword ptr [rsi+0x110],0
0xbc2bf4e  add rcx,0x118
0xbc2bf55  lea rdx,[rsi+0x118]
0xbc2bf5c  call 0x5669770
0xbc2bf61  nop
C-like: rax = src[0x110] (this is the return value); dst[0x110]=rax; src[0x110]=0; call 0x5669770 with rcx=&dst+0x118, rdx=&src+0x118 [verbatim quote above]; nop after call.

// 0xbc2bf62..0xbc2bffe  dword@0x24C, xmm@0x23C, byte@0x250, 4 floats@0x254..0x260, xmm@0x264/0x274/0x283, u64@0x294
0xbc2bf62  mov ecx,[rsi+0x24C]
0xbc2bf68  mov rax,[rbp-8]
0xbc2bf6c  mov [rax+0x24C],ecx
0xbc2bf72  movups xmm0,[rsi+0x23C]
0xbc2bf79  movups [rax+0x23C],xmm0
0xbc2bf80  movzx ecx,byte ptr [rsi+0x250]
0xbc2bf87  mov [rax+0x250],cl
0xbc2bf8d  movss xmm0,[rsi+0x254]
0xbc2bf95  movss [rax+0x254],xmm0
0xbc2bf9d  movss xmm0,[rsi+0x258]
0xbc2bfa5  movss [rax+0x258],xmm0
0xbc2bfad  movss xmm0,[rsi+0x25C]
0xbc2bfb5  movss [rax+0x25C],xmm0
0xbc2bfbd  movss xmm0,[rsi+0x260]
0xbc2bfc5  movss [rax+0x260],xmm0
0xbc2bfcd  movups xmm0,[rsi+0x264]
0xbc2bfd4  movups xmm1,[rsi+0x274]
0xbc2bfdb  movups xmm2,[rsi+0x283]
0xbc2bfe2  movups [rax+0x264],xmm0
0xbc2bfe9  movups [rax+0x274],xmm1
0xbc2bff0  movups [rax+0x283],xmm2
0xbc2bff7  mov rcx,[rsi+0x294]
0xbc2bffe  mov [rax+0x294],rcx
C-like: dst[0x24C]=src[0x24C] (dword); dst[0x23C]=src[0x23C]; dst[0x250]=src[0x250] (byte); dst[0x254..0x260]=src[0x254..0x260] (4 floats); dst[0x264]=src[0x264]; dst[0x274]=src[0x274]; dst[0x283]=src[0x283]; dst[0x294]=src[0x294].

// 0xbc2c005..0xbc2c00b  epilogue + return
0xbc2c005  add rsp,0x38
0xbc2c009  pop rsi
0xbc2c00a  pop rbp
0xbc2c00b  ret
C-like: return rax (= old src[0x110]).

## CALLEES SEEN
- 0xE869FF0 `sub_e869ff0` [V: rdis `dis 0xE869FF0 12`]: field copier, dst=rcx src=rdx; copies u64@0x0, u128@0x8, u64@0x18, u128@0x20, u64@0x30, u16@0x38 ...; 370 xrefs in [V]. Not in the CALLEES list (list is empty [V: unit data file]). In docs/data/native_boundary.tsv [V: `0xe869ff0	lift	auto-unresolved->lift`] but classified `lift`, not a boundary class (stl/crt/os/alloc/d3d/vendor/other-subsystem) — per spec sec.6 a `lift` classification is NOT boundary, it gets its own X7 lift unit, so it cannot be called from lifted code until lifted itself.
- 0x5669770 `sub_5669770` [V: rdis `dis 0x5669770 12`]: copies 16 floats at +0x00..+0x14 from src(rdx) to dst(rax=rcx); 54 xrefs in [V]. Same classification: not in CALLEES list; in docs/data/native_boundary.tsv as `0x5669770	lift	auto-unresolved->lift` [V], classified `lift` (not boundary).

## UNRESOLVED CALL
- 0xE869FF0 — caller instruction `0xbc2bf2b  call 0xE869FF0` (rcx=&dst+0x98, rdx=&src+0x98 [V: 0xbc2bf19/0xbc2bf20]). Callee `sub_e869ff0` at 0xE869FF0 is a field-copy function (370 xrefs in). Absent from the CALLEES list (empty); present in docs/data/native_boundary.tsv but classified `lift` (not boundary) → not a boundary wrapper target → UNRESOLVED CALL for this unit.
- 0x5669770 — caller instruction `0xbc2bf5c  call 0x5669770` (rcx=&dst+0x118, rdx=&src+0x118 [V: 0xbc2bf4e/0xbc2bf55]). Callee `sub_5669770` at 0x5669770 is a 16-float copy function (54 xrefs in). Absent from the CALLEES list (empty); present in docs/data/native_boundary.tsv but classified `lift` (not boundary) → UNRESOLVED CALL for this unit.

## FILES
- docs/progress/oc_U-EX1.bc2be20.md (this result file; created)
- (no other files created or changed: no dossier, no src/client/features/render/native/bgfx/* files, because the unit is blocked on unresolved callees before any source may be written)

## LIFTCHECK
`python tools/sigs/liftcheck.py 0xbc2be20` printed:

  - no dossier docs/functions/bc2be20.md
LIFTCHECK FAIL 0xbc2be20

(exit code nonzero). The remaining liftcheck checks (source marker, registry entry, static_asserts, instruction coverage, verbatim call quotes, verify_oc) cannot be reached because no source/dossier exists — and they cannot be completed while the two callees are unresolved, since inventing a wrapper is forbidden.

CLOSES? NO callee 0xE869FF0 (call `0xbc2bf2b  call 0xE869FF0`) and callee 0x5669770 (call `0xbc2bf5c  call 0x5669770`) are absent from the CALLEES list (empty) and classified `lift` (not boundary) in docs/data/native_boundary.tsv → UNRESOLVED CALL; wrapper creation is forbidden, so the lift cannot be completed
