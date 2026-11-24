# sub 0xbca7c80 — VV frame-graph builder (bgfx)

Range: [0xbca7c80, 0xbca8011) [V], size 0x391 bytes (docs/data/native_functions.tsv line 2).
Depth 2, milestone 1. Region: bgfx "VV frame-graph builder".

## ABI
- rcx = a0 (Str* — small-string object, reset by this function)
- rdx = a1 (Str* — small-string object, reset by this function)
- Returns via tail call to 0xE935700 (free) on the dealloc path, or ret with rax=0 (0xBCA7DCC xor eax,eax) on the small-string path [V].

## Callee table
- 0xEEC6EC0 = memcpy(dst,src,count) — class lift (native_boundary.tsv line 512, auto-unresolved->lift); called directly as sub_eec6ec0.
- 0xE935700 = free(ptr,size) — class lift (native_boundary.tsv line 505, auto-unresolved->lift); called directly as sub_e935700 (incl. tail call at 0xBCA7F9A).
- 0x9BC830  = alloc-failure handler — class alloc boundary (native_boundary.tsv line 149); via native::Boundary.
- 0x75720   = stl error path — class stl boundary (native_boundary.tsv line 3); via native::Boundary.
- [0xF99FFA0] = vendor allocator thunk slot (sub_eea6040, native_boundary.tsv line 506); read at call time (hard rule 69).
- [0xF9A8C78] = terminate slot; read at call time (hard rule 69), then int3.

## Globals / data slots
- 0x1233E1A8  allocator vtable pointer (rcx = *it before each slot alloc) [V].
- 0x12AE2210..0x12AE2270  published state block, 0x68 bytes [V]:
  +0x00 tag (rdx = 0xF or 0x1000000010), +0x08 dword 1, +0x10/+0x18 movups (desc q0/q1),
  +0x20/+0x28 movups (desc size/cap), +0x38 0x800000008, +0x40 dword 1,
  +0x48 final q0, +0x50 final q1, +0x58 a0.size, +0x60 final size.

## Operand layout (small-string object, size 0x20) [V]
- +0x00  char buf[0x10]  (inline buffer; holds a heap pointer in buf[0..7] when cap >= 0x10)
- +0x10  std::uint64_t size
- +0x18  std::uint64_t cap

## Reversed source (complete)

Whole-function instruction range: 0xBCA7C80..0xBCA8010 (every instruction in [0xbca7c80, 0xbca8011)).

Verbatim call log (two spaces after the address):
0xbca7d7e  call qword ptr [0xF99FFA0]
0xbca7daa  call qword ptr [0xF99FFA0]
0xbca7dc7  call 0xEEC6EC0
0xbca7e64  call qword ptr [0xF99FFA0]
0xbca7e8c  call qword ptr [0xF99FFA0]
0xbca7ea9  call 0xEEC6EC0
0xbca7f51  call 0xE935700
0xbca7fb6  call 0x9BC830
0xbca7fc4  call 0x9BC830
0xbca7fce  call 0x9BC830
0xbca7fdd  call 0x9BC830
0xbca7feb  call 0x75720
0xbca7ff1  call 0x75720
0xbca800a  call qword ptr [0xF9A8C78]
0xbca7f9a  jmp 0xE935700   ; tail call, reached via the dealloc epilogue

UNRESOLVED CALL = none
(0xEEC6EC0/0xE935700: class lift in native_boundary.tsv lines 512/505, forward-declared in sub_bca7c80.h and called directly; 0x9BC830/0x75720: boundary wrappers; [0xF99FFA0]/[0xF9A8C78]: slot reads per hard rule 69)

## Behaviour summary
1. Read and reset both operand objects (a0=rcx, a1=rdx): save a1's first 8 bytes/cap/size/xmm into the frame, save a0's buf[0]/buf[1]/buf[8]/size/cap; set both to empty (size=0, cap=0xF, buf[0]=0).
2. a1: if size < 0 -> error path (call 0x75720 twice, then [0xF9A8C78] terminate). If size <= 0xF -> small path (r14 = first 8 bytes of a1 data, rax = next 8, r12=0xF). If size > 0xF -> allocate via slot [0xF99FFA0] (size rsi|0xF, +0x28 if >=0x1000), memcpy rsi+1 bytes; on null alloc -> 0x9BC830 then crash.
3. a0: if size < 0 -> error path. If size <= 0xF -> small path (r14 = first 8 bytes of a0 data, rax = next 8, rsi=0xF). If size > 0xF -> allocate via slot, memcpy r15+1 bytes; on null alloc -> 0x9BC830 then crash.
4. Build descriptor at [rbp-0x58..] = {0x1000000010, 1, r14, rax, rsi_or_r15, r12} (a1's values).
5. Publish to globals [0x12AE2210..0x12AE2270]: tag=rdx, dword 1, movups desc q0/q1, movups size/cap, 0x800000008, dword 1, r14, rax, r15, rsi.
6. Free old buffers: a0's if cap>=0x10 (via 0xE935700, size cap+1 or cap+0x28 with [ptr-8] base check, else crash path at 0xBCA7FF7), then a1's if cap>=0x10 (tail call to 0xE935700 or ret).
7. Error/size-failure paths terminate via [0xF9A8C78] + int3.