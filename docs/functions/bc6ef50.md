# sub_bc6ef50 (0xbc6ef50, size 0xf1) - lift dossier

Minecraft Windows 1.26.62.01. Region bgfx, milestone D0, depth 2. Name: BgfxFrameBuilder::endFrame.
Range [0xbc6ef50, 0xbc6f041), ret at 0xbc6f040. Source: src/client/features/render/native/bgfx/sub_bc6ef50.cpp + .h.

## Signature

int sub_bc6ef50(void* a0, int a2, void* a3);   // x64 Microsoft ABI: rcx = a0, rdx = a2, r8 = a3, return eax = esi

## Register / argument map

- rcx = a0: this / object base. Reads uint16_t count at a0+0x4E8; block array base at a0+0x4F0. Lock address at a0+0x3D0. [V]
- rdx = a2: count cap (arg2), unsigned; low 16 bits compared against the count from a0+0x4E8. [V]
- r8 = a3: destination block base. Must be non-null; each block receives 0x138 bytes via memcpy plus a bounded string copy at its start. [V]
- r9: unused. [V]
- rdi = a3 (dst base), copied at entry; walked by 0x138 per iteration. [V]
- r14d = a2 (cap), low 16 bits used in the unsigned compare. [V]
- rbx = a0 at entry; then rbx += 0x4F0 to reach the source block array base; walked by 0x138 per iteration. [V]
- r15 = a0 + 0x3D0 (lock address); saved to [rbp-0x10] during the loop and restored for the unlock call. [V]
- esi = return value: number of blocks processed, or 0 if effective count == 0, or the raw count from a0+0x4E8 if a3 == 0. [V]

## Reversed source (complete)

0xbc6ef50..0xbc6ef7d: prologue — push rbp/r15/r14/r12/rsi/rdi/rbx; sub rsp,0x40; lea rbp,[rsp+0x40];
[rbp-8] = -2 (EH state slot, never read).
   void* rdi = a3;                          // dst base
   int   r14d = a2;                         // cap
   uint8_t* rbx = a0;                       // object base
   void* r15 = a0 + 0x3D0;                  // lock address
   // 0xbc6ef50  push rbp / push r15 / push r14 / push r12 / push rsi / push rdi / push rbx
   // 0xbc6ef5e  sub rsp,0x40
   // 0xbc6ef62  lea rbp,[rsp+0x40]
   // 0xbc6ef66  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE

0xbc6ef7e: sub_ebdbf10(r15);  // lock a0+0x3D0; return value dead
   ::native::sub_ebdbf10(lockAddr);
   // 0xbc6ef7e  mov rcx,r15 / call 0xEBDBF10

0xbc6ef83: esi = movzx word [rbx+0x4E8];  // raw count (uint16_t) from a0+0x4E8
   uint16_t rawCount = *(uint16_t*)(a0 + 0x4E8);
   int esi = rawCount;
   // 0xbc6ef83  movzx esi,word ptr [rbx+0x4E8]

0xbc6ef8d: test rdi,rdi; je loc_bc6f027;  // dst==0: skip to unlock, return raw count uncapped
   if (a3 == nullptr) { return rawCount; }

0xbc6ef8a: cmp r14w, si; 0xbc6ef90: cmovb esi, r14d;
   // esi = min((uint16_t)cap, (uint16_t)rawCount)  [unsigned 16-bit compare]
   if ((uint16_t)cap < (uint16_t)rawCount) esi = (int)(uint16_t)cap;

0xbc6ef9b: test si, si; je loc_bc6f025;  // effective count == 0: return 0
   if (esi == 0) { esi = 0; goto unlock; }

0xbc6efa4..0xbc6efbf: loop setup — [rbp-0x10] = lockAddr; rbx += 0x4F0 (src block array base);
   r15d = movzx esi (loop counter = effective count); r12 = &data_f847a07 (default empty string);
   r14 = &[rbp-0x20] (SrcDesc scratch slot on stack).
   FrameBlock* srcBlocks = (FrameBlock*)(a0 + 0x4F0);
   FrameBlock* dstBlocks = (FrameBlock*)a3;
   int count = esi;

0xbc6efc0: loop head (repeats `count` times):
   0xbc6efcc: r8d = 0x138; rcx = rdi; rdx = rbx; call sub_eec6ec0(rdi, rbx, 0x138)
       // memcpy 312 bytes from src block to dst block
       memcpy(dst.data, src.data, 0x138);
   [rbp-0x20] = &data_f847a07; [rbp-0x18] = 0;   // default SrcDesc: ptr=empty string, maxlen=0
   native::SrcDesc desc{}; desc.ptr = data_f847a07; desc.maxlen = 0;
   0xbc6efe4: rcx = rbx; edx = 0x7FFFFFFF; call sub_ebce5e0(rbx, 0x7FFFFFFF)
       // bounded strlen of string at start of src block -> eax
       int len = sub_ebce5e0(src.data, 0x7FFFFFFF);
   0xbc6efec: test eax,eax; je loc_bc6eff5;   // len==0: keep default SrcDesc
   if (len != 0) {
       [rbp-0x18] = eax; [rbp-0x20] = rbx;    // SrcDesc: ptr=src.data, maxlen=len
       desc.ptr = src.data; desc.maxlen = len;
   }
loc_bc6eff5:
   0xbc6f006: rcx = rdi; edx = 0x100; r8 = &[rbp-0x20]; r9d = 0x7FFFFFFF;
       call sub_ebce650(rdi, 0x100, &SrcDesc, 0x7FFFFFFF)
       // bounded string copy into dst.data (min(strlen, maxlen, 0x100-1) bytes + NUL)
       sub_ebce650(dst.data, 0x100, &desc, 0x7FFFFFFF);
   rdi += 0x138; rbx += 0x138; dec r15; jne loc_bc6efc0;   // advance to next block

After loop: r15 = [rbp-0x10] (restore lockAddr); jmp loc_bc6f027.
loc_bc6f025: xor esi, esi.   // (only reached when effective count == 0)
loc_bc6f027: rcx = r15; call sub_ebdbf20(r15);  // unlock a0+0x3D0
   ::native::sub_ebdbf20(lockAddr);
   mov eax, esi;  // return value
   // 0xbc6f02a  mov rcx,r15 / call 0xEBDBF20
   // 0xbc6f02f  mov eax,esi
   // epilogue: add rsp,0x40; pop rbx/rdi/rsi/r12/r14/r15/rbp; ret

## Call claims verified against the exe

The five call instructions, verbatim from the disassembly:

| address | callee | purpose | class |
|---|---|---|---|
| 0xbc6ef7e | call 0xEBDBF10 | sub_ebdbf10(lockAddr) — lock spinlock | lift — helpers/sub_ebdbf10.h |
| 0xbc6efcc | call 0xEEC6EC0 | sub_eec6ec0(dst, src, 0x138) — memcpy 312 bytes | lift — helpers/sub_eec6ec0.h |
| 0xbc6efe4 | call 0xEBCE5E0 | sub_ebce5e0(src.data, 0x7FFFFFFF) — bounded strlen | lift — helpers/sub_ebce5e0.h |
| 0xbc6f006 | call 0xEBCE650 | sub_ebce650(dst.data, 0x100, &SrcDesc, 0x7FFFFFFF) — bounded copy | lift — helpers/sub_ebce650.h |
| 0xbc6f02a | call 0xEBDBF20 | sub_ebdbf20(lockAddr) — unlock spinlock | lift — helpers/sub_ebdbf20.h |

No indirect calls, no data slots, no UNRESOLVED calls. All 5 callees are `lift`-classified.

## Struct fields touched

| object | offset | size | dir | meaning | tag |
|---|---|---|---|---|---|
| a0 | 0x3D0 | 8 | RW | lock address (passed to sub_ebdbf10 / sub_ebdbf20) | [V] |
| a0 | 0x4E8 | 2 | R | uint16_t raw element count | [V] |
| a0+0x4F0 + i*0x138 | 0x00 | 0x138 | R | source block i (memcpy source; data[0..] is a NUL string) | [V] |
| a3 + i*0x138 | 0x00 | 0x138 | W | destination block i (memcpy dest + bounded string copy) | [V] |

## Stack slots

| offset | size | purpose |
|---|---|---|
| [rbp-8] | 8 | EH state slot = -2 (never read) |
| [rbp-0x10] | 8 | saved lock address during the loop |
| [rbp-0x20] | 8 | SrcDesc.ptr (scratch: &data_f847a07 or src block pointer) |
| [rbp-0x18] | 4 | SrcDesc.maxlen (scratch: 0 or measured string length) |

## Return value

- a3 == nullptr → returns the raw uint16_t count from a0+0x4E8 (uncapped), 0 blocks processed.
- effective count == 0 (count==0 or cap==0) → returns 0.
- Otherwise → returns min((uint16_t)cap, (uint16_t)count) = number of blocks processed.

## OPEN questions

None. All five callees are `lift`-classified in docs/data/native_boundary.tsv and are called directly through the namespace-native forward declarations in sub_bc6ef50.h; no wrapper, no unresolved call, nothing blocks the lift.
