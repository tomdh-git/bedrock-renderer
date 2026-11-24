// LIFT 0xbc6af50 size 0x1f3 1.26.62.01 BgfxFrameBuilder slot 82
#include "client/features/render/native/bgfx/sub_bc6af50.h"

#include <cstring>

// Layout assertion: stack buffer at rsp+0x24 is 0x9C bytes before the cookie
// slot at rsp+0xC0 (0xC0 - 0x24 = 0x9C == memset count). [V]
static_assert(0xC0 - 0x24 == 0x9C,
              "bc6af50: stack buffer size equals memset count");

namespace native::bgfx {

uint32_t sub_bc6af50(uint8_t a1, uint32_t* a2) {
    // 0xbc6af50..0xbc6af75: prologue + stack cookie store
    //   push r15/r14/r13/r12/rsi/rdi/rbp/rbx; sub rsp,0xC8
    //   mov rax,[0x1230A0C0]; xor rax,rsp; mov [rsp+0xC0],rax
    const std::uintptr_t cookie_global =
        *reinterpret_cast<const std::uintptr_t*>(
            RewriteRegistry::imageBase() + kDataCookie);
    std::uintptr_t cookie_slot =
        cookie_global ^ reinterpret_cast<std::uintptr_t>(&cookie_slot);

    // 0xbc6af75..0xbc6af8b: entry checks
    //   test cl,cl; je 0xBC6B053   (a1 == 0 -> second path)
    //   mov rdi,rdx; test rdx,rdx; je 0xBC6B053  (a2 == nullptr -> second path)
    //   mov ebx,ecx             (bl = a1, loop limit)
    //   lea r15,[0x127CA028]    (r15 = global array base)
    //   xor esi,esi             (sil = 0, return accumulator)
    //   lea r14,[rsp+0x24]      (r14 = &buffer)
    //   mov r13,[0xF9A8770]     (r13 = fn1 pointer)
    //   mov rbp,[0xF9A8780]     (rbp = fn2 pointer)
    //   xor r12d,r12d           (counter = 0)
    //   jmp short 0xBC6AFC1     (-> LOOP_BODY)
// 0xbc6afaa  jmp short 0xBC6AFC1
// 0xbc6afac  nop [rax]
    if (a1 == 0 || a2 == nullptr) {
        goto second_path;
    }

    std::uint8_t buffer[kMemsetSize];
    std::uint8_t* gArrayPtr =
        reinterpret_cast<std::uint8_t*>(
            RewriteRegistry::imageBase() + kDataArrayBase);
    std::uint8_t sil = 0;
    std::uint64_t counter = 0;

    // Local function pointers (cached from data slots, as the original caches
    // them in r13/rbp/rbx/r15). [V]
    auto fn1 = reinterpret_cast<void* (*)(void*, int, int)>(
        *reinterpret_cast<void**>(
            RewriteRegistry::imageBase() + kDataSlot_Fn1));
    auto fn2 = reinterpret_cast<int (*)(void*, int, void*)>(
        *reinterpret_cast<void**>(
            RewriteRegistry::imageBase() + kDataSlot_Fn2));

loop:
    // 0xbc6afb0..0xbc6afbb: LOOP increment + exit check
    //   inc r12; add r15,0x28; cmp r12,0xB; je 0xBC6B105
    ++counter;
    gArrayPtr += 0x28;
    if (counter == kMaxLoop) {
        goto epilogue;
    }

loop_body:
    // 0xbc6afc1..0xbc6afc8: lea eax,[r12-1]; cmp al,1; ja short 0xBC6B030
    //   if (counter-1) > 1 unsigned -> SKIP (no memset, no calls)
    if (static_cast<std::uint8_t>(counter - 1) > 1) {
        goto skip_store_check;
    }

    // 0xbc6afca..0xbc6afd5: call 0xEBCE430  (memset(buffer, 0, 0x9C))
    //   mov r8d,0x9C; mov rcx,r14; xor edx,edx; call 0xEBCE430
    std::memset(buffer, 0, kMemsetSize);

    // 0xbc6afda..0xbc6afe9: buffer[0] = 0x50000009C; buffer[11] = 2
    //   mov rax,0x50000009C; mov [rsp+0x24],rax
    //   mov dword ptr [rsp+0x2C],2
    *reinterpret_cast<std::uint64_t*>(buffer) = kBufInitVal;
    *reinterpret_cast<std::uint32_t*>(buffer + kStackBufDwordOff) = kBufDwordVal;

    // 0xbc6aff1..0xbc6affb: call r13  -> fn1(nullptr, 2, 5)
    //   xor ecx,ecx; mov edx,2; mov r8b,5; call r13
    void* v1 = fn1(nullptr, 2, kFn1Arg3);

    // 0xbc6affe..0xbc6b009: call r13  -> fn1(v1, 1, 5)
    //   mov rcx,rax; mov edx,1; mov r8b,5; call r13
    void* v2 = fn1(v1, 1, kFn1Arg3);

    // 0xbc6b00c..0xbc6b017: call rbp  -> fn2(&buffer, 3, v2)
    //   mov rcx,r14; mov edx,3; mov r8,rax; call rbp
    int r = fn2(reinterpret_cast<void*>(buffer), kFn2Arg2, v2);

    // 0xbc6b019..0xbc6b026: test eax,eax; sete al; cmp sil,bl; setb cl;
    //   test al,cl; je short 0xBC6AFB0   (if !(r==0 && sil<a1) -> LOOP)
    if (!((r == 0) && (sil < a1))) {
        goto loop;
    }

// 0xbc6b028  jmp short 0xBC6B039
// 0xbc6b02a  nop [rax+rax]
    goto store;

skip_store_check:
    // 0xbc6b030..0xbc6b033: cmp sil,bl; jae 0xBC6AFB0  (if sil >= a1 -> LOOP)
    if (sil >= a1) {
        goto loop;
    }
    // falls through to STORE

store:
    // 0xbc6b039..0xbc6b03d: cmp byte ptr [r15],1; jne 0xBC6AFB0
    //   if (*gArrayPtr != 1) -> LOOP
    if (*gArrayPtr != kByteCheckVal) {
        goto loop;
    }

    // 0xbc6b043..0xbc6b04a: movzx eax,sil; inc sil; mov [rdi+rax*4],r12d
    //   a2[sil++] = counter (uint32_t store)
    a2[sil++] = static_cast<std::uint32_t>(counter);

    // 0xbc6b04e: jmp 0xBC6AFB0 -> LOOP
    goto loop;

second_path:
    // 0xbc6b053..0xbc6b077: second path setup (a1==0 or a2==nullptr)
    //   lea rdi,[rsp+0x24]; memset(buffer,0,0x9C); buffer[0]=0x50000009C;
    //   buffer[11]=2; mov rbx,[0xF9A8770] (fn1)
    {
        std::uint8_t buffer2[kMemsetSize];
        std::memset(buffer2, 0, kMemsetSize);
        *reinterpret_cast<std::uint64_t*>(buffer2) = kBufInitVal;
        *reinterpret_cast<std::uint32_t*>(buffer2 + kStackBufDwordOff) = kBufDwordVal;

        auto fn1b = reinterpret_cast<void* (*)(void*, int, int)>(
            *reinterpret_cast<void**>(
                RewriteRegistry::imageBase() + kDataSlot_Fn1));
        auto fn2b = reinterpret_cast<int (*)(void*, int, void*)>(
            *reinterpret_cast<void**>(
                RewriteRegistry::imageBase() + kDataSlot_Fn2));

        // 0xbc6b086..0xbc6b09d: fn1(nullptr,2,5); fn1(v1,1,5)
        void* v1b = fn1b(nullptr, 2, kFn1Arg3);
        void* v2b = fn1b(v1b, 1, kFn1Arg3);

        // 0xbc6b09f..0xbc6b0b1: mov r15,[0xF9A8780]; fn2(&buffer,3,v2b)
        //   mov r15,[0xF9A8780]; mov rcx,rdi; mov edx,3; mov r8,rax; call r15
        int rb = fn2b(reinterpret_cast<void*>(buffer2), kFn2Arg2, v2b);

        // 0xbc6b0b4..0xbc6b0b6: sete sil  (sil = (rb == 0))
        sil = (rb == 0) ? 1u : 0u;

        // 0xbc6b0ba..0xbc6b0c5: second memset + reinit buffer
        //   mov r8d,0x9C; mov rcx,rdi; xor edx,edx; call 0xEBCE430
// 0xbc6b0ba  mov r8d,0x9C
// 0xbc6b0c0  mov rcx,rdi
// 0xbc6b0c3  xor edx,edx
// 0xbc6b0c5  call 0xEBCE430
// 0xbc6b0ca  mov [rsp+0x24],r14
// 0xbc6b0cf  mov dword ptr [rsp+0x2C],2
        std::memset(buffer2, 0, kMemsetSize);
        *reinterpret_cast<std::uint64_t*>(buffer2) = kBufInitVal;
        *reinterpret_cast<std::uint32_t*>(buffer2 + kStackBufDwordOff) = kBufDwordVal;

        // 0xbc6b0d7..0xbc6b0ee: fn1(nullptr,2,5); fn1(v1,1,5)
        void* v1c = fn1b(nullptr, 2, kFn1Arg3);
        void* v2c = fn1b(v1c, 1, kFn1Arg3);

        // 0xbc6b0f0..0xbc6b0fb: fn2(&buffer,3,v2c)
        //   mov rcx,rdi; mov edx,3; mov r8,rax; call r15
        int rc = fn2b(reinterpret_cast<void*>(buffer2), kFn2Arg2, v2c);

        // 0xbc6b0fe..0xbc6b101: cmp eax,1; adc sil,9
        //   sil = sil + 9 + (rc == 0 ? 1 : 0)
        sil = static_cast<std::uint8_t>(sil + 9u + (rc == 0 ? 1u : 0u));
    }
    goto epilogue;

epilogue:
    // 0xbc6b105..0xbc6b131: stack cookie check + return
    //   mov rax,[rsp+0xC0]; xor rax,rsp; mov rcx,[0x1230A0C0]; cmp rcx,rax
    //   jne short 0xBC6B132  (cookie mismatch -> failure)
    //   mov eax,esi; add rsp,0xC8; pop...; ret
    if ((cookie_slot ^ reinterpret_cast<std::uintptr_t>(&cookie_slot)) != cookie_global) {
        goto cookie_failure;
    }
    return static_cast<uint32_t>(sil);

cookie_failure:
    // 0xbc6b132..0xbc6b142: call 0xE951550; int3  (noreturn)
    //   mov rcx,[rsp+0xC0]; xor rcx,rsp; call 0xE951550; int3
    native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");
    sub_e951550(cookie_slot ^ reinterpret_cast<std::uintptr_t>(&cookie_slot));
    __assume(false);  // original executes int3 here (noreturn)
}

native::Footprint sub_bc6af50_footprint(uint8_t a1, uint32_t* a2) {
    // Writes to the caller's output array a2[0..a1) (up to a1 uint32_t values,
    // indexed by sil which is bounded by a1 via the sil < a1 check). Stack
    // buffer and cookie slot are frame-local, not visible to the caller.
    return { { { a2, static_cast<size_t>(a1) * sizeof(std::uint32_t) } } };
}

LIFT_FN(sub_bc6af50, "BgfxFrameBuilder slot 82", 0xbc6af50, sub_bc6af50,
        sub_bc6af50_footprint);

} // namespace native::bgfx
