// LIFT 0xbc5e400 size 0x2f1 1.26.62.01 sub_bc5e400

#include "client/features/render/native/bgfx/sub_bc5e400.h"

#include "client/features/render/native/Lift.h"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <intrin.h>

namespace native {

namespace {

using Elem = Bc5e400Elem;

// Maximum element count for 16-byte elements: 2^64 / 16 = 0xFFFFFFFFFFFFFFF [V].

static constexpr std::uintptr_t kMaxElemCount = 0xFFFFFFFFFFFFFFFui64;

// Data slots read at call time (the original does call qword ptr [slot], not an import call):

//   [0x1233E1A8]  0xbc5e494  mov rcx,[0x1233E1A8]   ; [data_1233e1a8] allocator interface (VA = imageBase + 0x1233E1A8)

//   [0xF99FFA0]   0xbc5e4a5  call qword ptr [0xF99FFA0]   ; loader-resolved entry, rcx = iface, rdx = size -> buffer

//   [0xF9A8C78]   0xbc5e6ea  call qword ptr [0xF9A8C78]   ; dead fail handler, rcx = rdx = r8 = r9 = 0

inline std::uint8_t* image_base() {
    return reinterpret_cast<std::uint8_t*>(RewriteRegistry::imageBase());
}

inline void* slot_f99ffa0() {
    return *reinterpret_cast<void** volatile*>(image_base() + 0xF99FFA0);
}

inline void* slot_f9a8c78() {
    return *reinterpret_cast<void** volatile*>(image_base() + 0xF9A8C78);
}

using AllocFn = void* (__cdecl*)(void* iface, std::uintptr_t size);
using ObjFn   = void     (__cdecl*)(void* object);
using FailFn  = void     (__cdecl*)(void* a0, void* a1, void* a2, void* a3);

// lock inc dword ptr [object + 8]  (strong refcount) [V]

inline void inc_strong(void* object) {
    auto& rc = *reinterpret_cast<std::atomic<std::uint32_t>*>(
        reinterpret_cast<std::uint8_t*>(object) + 8);
    rc.fetch_add(1u, std::memory_order_seq_cst);
}

// lock dec dword ptr [...]; true when the count reached 0 [V]

inline bool dec_to_zero(std::atomic<std::uint32_t>& rc) {
    return rc.fetch_sub(1u, std::memory_order_seq_cst) == 1u;
}

} // namespace


std::uint32_t sub_bc5e400_footprint(Bc5e400Array* self, void*, const void*) {
    // [V] the function rewrites the array header: begin/end/cap_end at +0x0/+0x8/+0x10.

    return native::Footprint{ { { reinterpret_cast<void*>(self), 0x18ull } } };
}

// Elem* sub_bc5e400(Bc5e400Array* self /*rcx*/, Bc5e400Elem* position /*rdx*/,

//                   const Bc5e400Elem* element /*r8*/);  return = iterator to inserted element (rax).

Bc5e400Elem* sub_bc5e400(Bc5e400Array* self, Bc5e400Elem* position, const Bc5e400Elem* element) {
    // 0xbc5e400..0xbc5e462: prologue, element count and grown capacity

    //   0xbc5e400  push r15

    //   0xbc5e402  push r14

    //   0xbc5e404  push r13

    //   0xbc5e406  push r12

    //   0xbc5e408  push rsi

    //   0xbc5e409  push rdi

    //   0xbc5e40a  push rbp

    //   0xbc5e40b  push rbx

    //   0xbc5e40c  sub rsp,0x28

    //   0xbc5e410  mov rsi,rcx                                   ; self

    //   0xbc5e413  mov r14,[rcx]                                 ; begin   R self+0x0

    //   0xbc5e416  mov r13,[rcx+8]                               ; end     R self+0x8

    //   0xbc5e41a  sub r13,r14

    //   0xbc5e41d  sar r13,4

    //   0xbc5e421  inc r13                                        ; count1 = (end - begin) / 16 + 1

    //   0xbc5e424  mov rcx,[rcx+0x10]                             ; cap_end R self+0x10

    //   0xbc5e428  sub rcx,r14

    //   0xbc5e42b  sar rcx,4                                       ; cap_count

    //   0xbc5e42f  mov rax,rcx

    //   0xbc5e432  shr rax,1                                       ; half

    //   0xbc5e435  mov r9,0xFFFFFFFFFFFFFFF                        ; kMaxElemCount

    //   0xbc5e43f  mov r10,r9

    //   0xbc5e442  sub r10,rax                                     ; kMaxElemCount - half

    //   0xbc5e445  add rax,rcx                                     ; cap_count + half

    //   0xbc5e448  cmp rax,r13

    //   0xbc5e44b  cmovbe rax,r13                                  ; if (newcap <= count1) newcap = count1

    //   0xbc5e44f  cmp rcx,r10

    //   0xbc5e452  cmova rax,r9                                    ; if (cap_count > max - half) newcap = max

    //   0xbc5e456  mov rcx,rax

    //   0xbc5e459  shr rcx,0x3C

    //   0xbc5e45d  jne 0xBC5E6D2                                   ; newcap >> 60 != 0 -> call 0x75740 (noreturn)

    Elem* const begin = self->begin;
    Elem* const end = self->end;
    Elem* const cap_end = self->cap_end;
    const std::uintptr_t count1 = static_cast<std::uintptr_t>(end - begin) + 1u;
    const std::uintptr_t cap_count = static_cast<std::uintptr_t>(cap_end - begin);
    const std::uintptr_t half = cap_count >> 1;
    std::uintptr_t newcap = cap_count + half;
    if (newcap <= count1) {
        newcap = count1;                                         // 0xbc5e44b  cmovbe rax,r13

    }
    if (cap_count > kMaxElemCount - half) {
        newcap = kMaxElemCount;                                  // 0xbc5e452  cmova rax,r9

    }
    if ((newcap >> 60) != 0) {                                   // 0xbc5e459  shr rcx,0x3C / 0xbc5e45d  jne 0xBC5E6D2

        sub_75740(newcap >> 60);                                 // 0xbc5e6d2  call 0x75740   (dead: noreturn)

        __assume(false);
    }
    const std::uintptr_t newcap_bytes = newcap << 4;             // 0xbc5e469  mov rdi,rax / 0xbc5e46c  shl rdi,4


    // 0xbc5e463..0xbc5e474: arguments copied to registers, newcap == 0 test (dead: count1 >= 1)

    //   0xbc5e463  mov r12,r8                                     ; element

    //   0xbc5e466  mov r15,rdx                                     ; position

    //   0xbc5e469  mov rdi,rax

    //   0xbc5e46c  shl rdi,4

    //   0xbc5e470  test rax,rax

    //   0xbc5e473  je short 0xBC5E4EC                             ; newcap == 0 -> buf = 0

    void* buf = nullptr;
    if (newcap != 0) {
        // 0xbc5e475..0xbc5e493: size-class guard

        //   0xbc5e475  cmp rax,0x100

        //   0xbc5e47b  jb short 0xBC5E4C5                         ; newcap < 0x100 -> fast path

        //   0xbc5e47d  mov rcx,0xFFFFFFFFFFFFFFE

        //   0xbc5e487  cmp rax,rcx

        //   0xbc5e48a  jae 0xBC5E6D2                              ; newcap >= max - 1 -> call 0x75740 (dead)

        //   0xbc5e490  lea rbx,[rdi+0x27]                         ; slow path: size = newcap_bytes + 0x27

        if (newcap >= kMaxElemCount - 1) {                       // 0xbc5e48a  jae 0xBC5E6D2

            sub_75740(kMaxElemCount - 1);                        // 0xbc5e6d2  call 0x75740   (dead: noreturn)

            __assume(false);
        }
        void* const iface = *reinterpret_cast<void** volatile*>(image_base() + 0x1233E1A8); // 0xbc5e494  mov rcx,[0x1233E1A8]

        void* const vtable = *reinterpret_cast<void** volatile*>(iface);                    // 0xbc5e49b  mov rax,[rcx]

        (void*)*reinterpret_cast<void** volatile*>(reinterpret_cast<std::uint8_t*>(vtable) + 8); // 0xbc5e49e  mov rax,[rax+8] (read, unused by the slot call)

        if (newcap < 0x100ui64) {                                // 0xbc5e475  cmp rax,0x100 / 0xbc5e47b  jb short 0xBC5E4C5

            // 0xbc5e4c5..0xbc5e4d5: fast-path alloc setup

            //   0xbc5e4c5  mov rcx,[0x1233E1A8]

            //   0xbc5e4cc  mov rax,[rcx]

            //   0xbc5e4cf  mov rax,[rax+8]

            //   0xbc5e4d3  mov rdx,rdi                           ; rdx = newcap_bytes

            //   0xbc5e4d6  call qword ptr [0xF99FFA0]            ; [data_f99ffa0]

            buf = reinterpret_cast<AllocFn>(slot_f99ffa0())(iface, newcap_bytes);  // 0xbc5e4d6  call qword ptr [0xF99FFA0]

            // 0xbc5e4dc..0xbc5e4e3: fast-path result

            //   0xbc5e4dc  mov rbx,rax

            //   0xbc5e4df  test rax,rax

            //   0xbc5e4e2  jne short 0xBC5E4EE

        } else {
            // 0xbc5e494..0xbc5e4ab: slow-path alloc setup and call

            //   0xbc5e494  mov rcx,[0x1233E1A8]

            //   0xbc5e49b  mov rax,[rcx]

            //   0xbc5e49e  mov rax,[rax+8]

            //   0xbc5e4a2  mov rdx,rbx                           ; rdx = newcap_bytes + 0x27

            //   0xbc5e4a5  call qword ptr [0xF99FFA0]            ; [data_f99ffa0]

            buf = reinterpret_cast<AllocFn>(slot_f99ffa0())(iface, newcap_bytes + 0x27); // 0xbc5e4a5  call qword ptr [0xF99FFA0]

            // 0xbc5e4ab..0xbc5e4b3: slow-path result

            //   0xbc5e4ab  test rax,rax

            //   0xbc5e4ae  je 0xBC5E6BF                           ; alloc failed -> 0xbc5e6bf  mov rcx,rbx / 0xbc5e6c5  call 0x9BC830 (rcx = 0)

            // 0xbc5e4b4..0xbc5e4c4: slow-path success (dead unless allocation succeeded)

            //   0xbc5e4b4  mov rbx,rax

            //   0xbc5e4b7  add rbx,0x27

            //   0xbc5e4bb  and rbx,0xFFFFFFFFFFFFFFE0

            //   0xbc5e4bf  mov [rbx-8],rax                        ; store the unaligned base at [aligned_buf - 8]

            //   0xbc5e4c3  jmp short 0xBC5E4EE

        }
        if (buf == nullptr) {
            if (newcap < 0x100ui64) {                            // 0xbc5e4e4  mov rcx,rdi / 0xbc5e4e7  call 0x9BC830 (rcx = newcap_bytes)

                sub_9bc830(newcap_bytes);                        // 0xbc5e4e7  call 0x9BC830   (dead: noreturn)

            } else {                                             // 0xbc5e6bf..0xbc5e6c4: slow-path allocation failure (dead: sub_9bc830 is noreturn)

                //   0xbc5e6bf  mov rcx,rbx                      ; rbx = 0 (alloc returned null)

                //   0xbc5e6c2  mov rbx,rax

                //   0xbc5e6c5  call 0x9BC830                    ; rcx = 0

                //   0xbc5e6ca  mov rax,rbx

                //   0xbc5e6cd  jmp 0xBC5E4B4                    ; into the slow-success block (dead)

                sub_9bc830(0);                                   // 0xbc5e6c5  call 0x9BC830   (dead: noreturn)

            }
            __assume(false);                                     // dead: allocation failure paths never return

        }
    }

    // 0xbc5e4ec..0xbc5e50c: insert slot = buf + (position - begin); zero it; strong +1 on element->field1; store element

    //   0xbc5e4ec  xor ebx,ebx                                    ; buf = 0 (dead path: newcap >= count1 >= 1)

    //   0xbc5e4ee  mov rax,r15

    //   0xbc5e4f1  sub rax,r14                                    ; rax = position - begin (bytes)

    //   0xbc5e4f4  lea r14,[rbx+rax]                              ; insert slot

    //   0xbc5e4f8  xorps xmm0,xmm0

    //   0xbc5e4fb  movups [rbx+rax],xmm0                          ; zero 16 bytes at insert slot

    //   0xbc5e4ff  mov rcx,[r12+8]                                ; element->field1

    //   0xbc5e504  test rcx,rcx

    //   0xbc5e509  lock inc dword ptr [rcx+8]                     ; strong refcount +1

    std::uint8_t* const buf8 = reinterpret_cast<std::uint8_t*>(buf);
    const std::ptrdiff_t insert_off =
        reinterpret_cast<const std::uint8_t*>(position) -
        reinterpret_cast<const std::uint8_t*>(begin);
    Elem* const insert_slot = reinterpret_cast<Elem*>(buf8 + insert_off);
    insert_slot->field0 = nullptr;                               // 0xbc5e4fb  movups [rbx+rax],xmm0

    insert_slot->field1 = nullptr;
    if (element->field1 != nullptr) {                            // 0xbc5e504  test rcx,rcx / je short 0xBC5E50D

        inc_strong(element->field1);                             // 0xbc5e509  lock inc dword ptr [rcx+8]

    }
    insert_slot->field0 = element->field0;                       // 0xbc5e50d  mov rcx,[r12] / 0xbc5e511  mov [r14],rcx

    insert_slot->field1 = element->field1;                       // 0xbc5e514  mov rcx,[r12+8] / 0xbc5e519  mov [r14+8],rcx


    // 0xbc5e51d..0xbc5e539: copy cursors and branch checks

    //   0xbc5e51d  mov r12,[rsi]                                  ; src = begin   R self+0x0

    //   0xbc5e520  mov rcx,[rsi+8]                                ; rcx = end     R self+0x8

    //   0xbc5e524  cmp r15,rcx                                    ; position == end -> nothing before insert

    //   0xbc5e527  je 0xBC5E5BD

    //   0xbc5e52d  cmp r12,r15                                    ; begin == position -> insert at front

    //   0xbc5e530  je short 0xBC5E574

    //   0xbc5e532  mov rcx,rbx                                    ; dst = buf

    //   0xbc5e535  jmp short 0xBC5E55D

    //   0xbc5e537  nop [rax+rax]

    Elem* src = begin;
    const Elem* const old_end = end;
    Elem* dst = reinterpret_cast<Elem*>(buf8);
    if (position != old_end) {                                   // 0xbc5e524  cmp r15,rcx / je 0xBC5E5BD

        if (src != position) {                                   // 0xbc5e52d  cmp r12,r15 / je short 0xBC5E574

            // 0xbc5e53a..0xbc5e56f: loop A - copy one element [begin, position): zero dst, strong +1, copy, advance

            //   0xbc5e540  mov rdx,[r12]

            //   0xbc5e544  mov [rcx],rdx

            //   0xbc5e547  mov rdx,[r12+8]

            //   0xbc5e54c  mov [rcx+8],rdx

            //   0xbc5e550  add rcx,0x10

            //   0xbc5e554  add r12,0x10

            //   0xbc5e558  cmp r12,r15

            //   0xbc5e55b  je short 0xBC5E570

            //   0xbc5e55d  movups [rcx],xmm0

            //   0xbc5e560  mov rdx,[r12+8]

            //   0xbc5e565  test rdx,rdx

            //   0xbc5e568  je short 0xBC5E540

            //   0xbc5e56a  lock inc dword ptr [rdx+8]

            //   0xbc5e56e  jmp short 0xBC5E540

            do {
                dst->field0 = nullptr; dst->field1 = nullptr;    // 0xbc5e55d  movups [rcx],xmm0

                if (src->field1 != nullptr) {                    // 0xbc5e560  mov rdx,[r12+8] / test / je short 0xBC5E540

                    inc_strong(src->field1);                     // 0xbc5e56a  lock inc dword ptr [rdx+8]

                }
                dst->field0 = src->field0;                       // 0xbc5e540  mov rdx,[r12] / mov [rcx],rdx

                dst->field1 = src->field1;                       // 0xbc5e547  mov rdx,[r12+8] / mov [rcx+8],rdx

                ++dst; ++src;                                    // 0xbc5e550  add rcx,0x10 / 0xbc5e554  add r12,0x10

            } while (src != position);                           // 0xbc5e558  cmp r12,r15 / je short 0xBC5E570

        }
        // 0xbc5e570..0xbc5e5ab: loop B setup: end reload, dst = insert slot + 1, src = position

        //   0xbc5e570  mov rcx,[rsi+8]                            ; end

        //   0xbc5e574  cmp r15,rcx

        //   0xbc5e577  je 0xBC5E600

        //   0xbc5e57d  add rax,rbx                                ; rax = insert slot

        //   0xbc5e580  add rax,0x10                               ; dst = insert slot + 1

        //   0xbc5e584  xorps xmm0,xmm0

        //   0xbc5e587  jmp short 0xBC5E5AB

        //   0xbc5e589  nop [rax]

        dst = insert_slot + 1;
        src = position;
    }

    // 0xbc5e5ac..0xbc5e5bc: loop B - copy one element [position, end): zero dst, strong +1, copy, advance

    //   0xbc5e5ae  mov rdx,[r15+8]

    //   0xbc5e5b2  test rdx,rdx

    //   0xbc5e5b7  lock inc dword ptr [rdx+8]

    //   0xbc5e590  mov rdx,[r15]

    //   0xbc5e593  mov [rax],rdx

    //   0xbc5e596  mov rdx,[r15+8]

    //   0xbc5e59a  mov [rax+8],rdx

    //   0xbc5e59e  add r15,0x10

    //   0xbc5e5a2  add rax,0x10

    //   0xbc5e5a6  cmp r15,rcx

    //   0xbc5e5a9  je short 0xBC5E600

    while (src != old_end) {                                     // 0xbc5e574  cmp r15,rcx / je 0xBC5E600

        dst->field0 = nullptr; dst->field1 = nullptr;            // 0xbc5e5ab  movups [rax],xmm0

        if (src->field1 != nullptr) {                            // 0xbc5e5ae  mov rdx,[r15+8] / test

            inc_strong(src->field1);                             // 0xbc5e5b7  lock inc dword ptr [rdx+8]

        }
        dst->field0 = src->field0;                               // 0xbc5e590  mov rdx,[r15] / mov [rax],rdx

        dst->field1 = src->field1;                               // 0xbc5e596  mov rdx,[r15+8] / mov [rax+8],rdx

        ++dst; ++src;                                            // 0xbc5e59e  add r15,0x10 / 0xbc5e5a2  add rax,0x10

    }                                                            // 0xbc5e5a6  cmp r15,rcx / je short 0xBC5E600


    // 0xbc5e5bd..0xbc5e5cf: position == end - copy the whole old array [begin, end) to the new buffer

    //   0xbc5e5bd  cmp r12,r15                                    ; begin == end -> nothing to copy

    //   0xbc5e5c0  je short 0xBC5E603

    //   0xbc5e5c2  mov rax,rbx                                    ; dst = buf

    //   0xbc5e5c5  jmp short 0xBC5E5ED

    //   0xbc5e5c7  nop [rax+rax]

    //   0xbc5e5d0  mov rcx,[r12]

    //   0xbc5e5d4  mov [rax],rcx

    //   0xbc5e5d7  mov rcx,[r12+8]

    //   0xbc5e5dc  mov [rax+8],rcx

    //   0xbc5e5e0  add rax,0x10

    //   0xbc5e5e4  add r12,0x10

    //   0xbc5e5e8  cmp r12,r15

    //   0xbc5e5eb  je short 0xBC5E600

    //   0xbc5e5ed  movups [rax],xmm0                              ; zero dst first (loop entry)

    //   0xbc5e5f0  mov rcx,[r12+8]

    //   0xbc5e5f5  test rcx,rcx

    //   0xbc5e5f8  je short 0xBC5E5D0

    //   0xbc5e5fa  lock inc dword ptr [rcx+8]

    //   0xbc5e5fe  jmp short 0xBC5E5D0

    if (position == old_end && begin != old_end) {               // 0xbc5e5bd  cmp r12,r15 / je short 0xBC5E603

        dst = reinterpret_cast<Elem*>(buf8);
        src = begin;
        do {
            dst->field0 = nullptr; dst->field1 = nullptr;        // 0xbc5e5ed  movups [rax],xmm0

            if (src->field1 != nullptr) {                        // 0xbc5e5f0  mov rcx,[r12+8] / test / je short 0xBC5E5D0

                inc_strong(src->field1);                         // 0xbc5e5fa  lock inc dword ptr [rcx+8]

            }
            dst->field0 = src->field0;                           // 0xbc5e5d0  mov rcx,[r12] / mov [rax],rcx

            dst->field1 = src->field1;                           // 0xbc5e5d7  mov rcx,[r12+8] / mov [rax+8],rcx

            ++dst; ++src;                                        // 0xbc5e5e0  add rax,0x10 / 0xbc5e5e4  add r12,0x10

        } while (src != old_end);                                // 0xbc5e5e8  cmp r12,r15 / je short 0xBC5E600

    }

    // 0xbc5e600..0xbc5e632: destroy old elements [begin, end): strong/weak lock dec, destroy object, free control block

    //   0xbc5e600  mov r12,[rsi]                                  ; old = begin   R self+0x0

    //   0xbc5e603  test r12,r12

    //   0xbc5e606  je 0xBC5E696                                   ; no old elements

    //   0xbc5e60c  mov rbp,[rsi+8]                                ; old_end     R self+0x8

    //   0xbc5e610  cmp r12,rbp

    //   0xbc5e613  jne short 0xBC5E629

    //   0xbc5e615  jmp short 0xBC5E665

    //   0xbc5e617  nop [rax+rax]

    //   0xbc5e620  add r12,0x10

    //   0xbc5e624  cmp r12,rbp

    //   0xbc5e627  je short 0xBC5E662

    //   0xbc5e629  mov r15,[r12+8]                                ; object = old->field1

    //   0xbc5e62e  test r15,r15

    //   0xbc5e631  je short 0xBC5E620

    //   0xbc5e633  lock dec dword ptr [r15+8]                     ; strong--

    //   0xbc5e638  jne short 0xBC5E620

    //   0xbc5e63a  mov rax,[r15]                                  ; vtable[0] read (unused by the slot call)

    //   0xbc5e63d  mov rax,[rax]

    //   0xbc5e640  mov rcx,r15

    //   0xbc5e643  call qword ptr [0xF99FFA0]                     ; [data_f99ffa0] destroy object

    //   0xbc5e649  lock dec dword ptr [r15+0xC]                   ; weak--

    //   0xbc5e64e  jne short 0xBC5E620

    //   0xbc5e650  mov rax,[r15]                                  ; vtable[8] read (unused by the slot call)

    //   0xbc5e653  mov rax,[rax+8]

    //   0xbc5e657  mov rcx,r15

    //   0xbc5e65a  call qword ptr [0xF99FFA0]                     ; [data_f99ffa0] free control block

    //   0xbc5e660  jmp short 0xBC5E620

    if (begin != nullptr && begin != old_end) {
        Elem* old = begin;
        for (;;) {
            void* const object = old->field1;                    // 0xbc5e629  mov r15,[r12+8]

            if (object != nullptr) {                             // 0xbc5e62e  test r15,r15 / je short 0xBC5E620

                auto& strong = *reinterpret_cast<std::atomic<std::uint32_t>*>(
                    reinterpret_cast<std::uint8_t*>(object) + 8);
                if (dec_to_zero(strong)) {                       // 0xbc5e633  lock dec dword ptr [r15+8] / jne short 0xBC5E620

                    (void*)*reinterpret_cast<void* volatile*>(object); // 0xbc5e63a  mov rax,[r15] / 0xbc5e63d  mov rax,[rax]

                    reinterpret_cast<ObjFn>(slot_f99ffa0())(object);   // 0xbc5e643  call qword ptr [0xF99FFA0]

                    auto& weak = *reinterpret_cast<std::atomic<std::uint32_t>*>(
                        reinterpret_cast<std::uint8_t*>(object) + 0xC);
                    if (dec_to_zero(weak)) {                     // 0xbc5e649  lock dec dword ptr [r15+0xC] / jne short 0xBC5E620

                        (void*)*reinterpret_cast<void* volatile*>(reinterpret_cast<std::uint8_t*>(object) + 8); // 0xbc5e650  mov rax,[r15] / 0xbc5e653  mov rax,[rax+8]

                        reinterpret_cast<ObjFn>(slot_f99ffa0())(object); // 0xbc5e65a  call qword ptr [0xF99FFA0]

                    }
                }
            }
            ++old;                                               // 0xbc5e620  add r12,0x10

            if (old == old_end) break;                           // 0xbc5e624  cmp r12,rbp / je short 0xBC5E662

        }
    }

    // 0xbc5e662..0xbc5e695: free the old buffer, then deallocate its base

    //   0xbc5e662  mov r12,[rsi]                                  ; r12 = begin (reloaded)   R self+0x0

    //   0xbc5e665  mov rdx,[rsi+0x10]                             ; rdx = cap_end            R self+0x10

    //   0xbc5e669  sub rdx,r12                                    ; rdx = old capacity bytes

    //   0xbc5e66c  cmp rdx,0x1000

    //   0xbc5e673  jb short 0xBC5E68E                             ; small buffer -> dealloc begin directly

    //   0xbc5e675  mov rax,[r12-8]                                ; old_base = [begin - 8]

    //   0xbc5e67a  add r12,0xFFFFFFFFFFFFFFF8                     ; r12 = begin - 8

    //   0xbc5e67e  sub r12,rax                                    ; probe = begin - 8 - old_base

    //   0xbc5e681  cmp r12,0x20

    //   0xbc5e685  jae short 0xBC5E6D7                            ; probe >= 0x20 -> dead fail path: call [0xF9A8C78] + int3

    //   0xbc5e687  add rdx,0x27                                   ; size (ignored by the callee)

    //   0xbc5e68b  mov r12,rax                                    ; r12 = old_base

    //   0xbc5e68e  mov rcx,r12

    //   0xbc5e691  call 0xE935700                                 ; deallocates the buffer base (class lift)

    const std::uintptr_t old_cap_bytes =
        reinterpret_cast<const std::uint8_t*>(cap_end) -
        reinterpret_cast<const std::uint8_t*>(begin);
    if (old_cap_bytes < 0x1000ui64) {
        sub_e935700(begin);                                       // 0xbc5e68e  mov rcx,r12(=begin) / 0xbc5e691  call 0xE935700

    } else {
        void* const old_base = *reinterpret_cast<void** volatile*>(
            reinterpret_cast<std::uint8_t*>(begin) - 8);          // 0xbc5e675  mov rax,[r12-8]

        const std::uint8_t* const probe =
            reinterpret_cast<const std::uint8_t*>(begin) - 8 -
            reinterpret_cast<const std::uint8_t*>(old_base);      // 0xbc5e67a  add r12,... / 0xbc5e67e  sub r12,rax

        if (probe >= 0x20ui64) {                                  // 0xbc5e681  cmp r12,0x20 / jae short 0xBC5E6D7

            // 0xbc5e6d7..0xbc5e6f0: dead fail handler (int3 padding through 0xbc5e6ff, outside the function)

            //   0xbc5e6d7  mov qword ptr [rsp+0x20],0

            //   0xbc5e6e0  xor ecx,ecx

            //   0xbc5e6e2  xor edx,edx

            //   0xbc5e6e4  xor r8d,r8d

            //   0xbc5e6e7  xor r9d,r9d

            //   0xbc5e6ea  call qword ptr [0xF9A8C78]

            //   0xbc5e6f0  int3

            reinterpret_cast<FailFn>(slot_f9a8c78())(nullptr, nullptr, nullptr, nullptr); // 0xbc5e6ea  call qword ptr [0xF9A8C78] (dead: noreturn)

            __assume(false);
        }
        sub_e935700(old_base);                                    // 0xbc5e68b  mov r12,rax / 0xbc5e68e  mov rcx,r12 / 0xbc5e691  call 0xE935700

    }

    // 0xbc5e696..0xbc5e6be: install the new array, return iterator to the inserted element

    //   0xbc5e696  mov [rsi],rbx                                  ; self->begin = buf   W self+0x0

    //   0xbc5e699  shl r13,4

    //   0xbc5e69d  add r13,rbx                                    ; new end = buf + count1 * 16

    //   0xbc5e6a0  mov [rsi+8],r13                                ; self->end           W self+0x8

    //   0xbc5e6a4  add rdi,rbx                                    ; new cap_end = buf + newcap_bytes

    //   0xbc5e6a7  mov [rsi+0x10],rdi                             ; self->cap_end       W self+0x10

    //   0xbc5e6ab  mov rax,r14                                    ; return insert slot

    //   0xbc5e6ae  add rsp,0x28

    //   0xbc5e6b2  pop rbx ; 0xbc5e6b3  pop rbp ; 0xbc5e6b4  pop rdi ; 0xbc5e6b5  pop rsi

    //   0xbc5e6b6  pop r12 ; 0xbc5e6b8  pop r13 ; 0xbc5e6ba  pop r14 ; 0xbc5e6bc  pop r15

    //   0xbc5e6be  ret

    self->begin = reinterpret_cast<Elem*>(buf8);
    self->end = reinterpret_cast<Elem*>(buf8 + count1 * 16u);
    self->cap_end = reinterpret_cast<Elem*>(buf8 + newcap_bytes);
    return insert_slot;
}

static_assert(offsetof(Bc5e400Array, begin) == 0x00, "bc5e400: array begin at +0x0");
static_assert(offsetof(Bc5e400Array, end) == 0x08, "bc5e400: array end at +0x8");
static_assert(offsetof(Bc5e400Array, cap_end) == 0x10, "bc5e400: array cap_end at +0x10");
static_assert(sizeof(Bc5e400Array) == 0x18, "bc5e400: array size 0x18");

LIFT_FN(bc5e400, "VV frame-graph builder", 0xBC5E400, sub_bc5e400, sub_bc5e400_footprint);

} // namespace native

