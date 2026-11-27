// LIFT 0xbc04530 size 0xc4 1.26.62.01 sub_bc04530
#include "client/features/render/native/framebuilder/sub_bc04530.h"
#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <intrin.h>

namespace native {

// sub_bc04530 (0xbc04530, size 0xc4, 1.26.62.01, "pass task render-thread body (class D)").
//
// Exact x64 Microsoft ABI: RCX = a0 (PassBodyD*, class D render-thread body object),
// RDX = a1 (u64 stored at *(a0+0x3B0)+0x18 then cleared to 0). Returns void (ends in ret).
//
// Same reads, same writes (value and order), same calls in the same order, same return.
// No null guard or SEH (the original has none; none added here). [V] every instruction
// line below, from the exe disassembly of [0xbc04530, 0xbc045f4).
//
// Phase 1: 0xbc04530..0xbc04573  prologue, save a0+0x3A8, addref a0+0x3B8, load obj1 & old_ref
// Phase 2: 0xbc04573..0xbc0458d  store a1 to obj1+0x18, load obj2, branch if obj2 == 0
// Phase 3: 0xbc0458d..0xbc045f4  obj2 == 0 path: call sub_eec59e0 (noreturn), int3 unreachable
// Phase 4: 0xbc0458f..0xbc045a5  callback via sub_eea6040 thunk (obj2->vtable[0x10](obj2, &saved_3a8))
// Phase 5: 0xbc045a5..0xbc045e6  clear obj1+0x18, release old_ref (strong + destructor + weak + deleter)
// Phase 6: 0xbc045e6..0xbc045ec  epilogue, ret

void sub_bc04530(PassBodyD* a0, std::uint64_t a1) {
    // 0xbc04530  push rbp                                   ; prologue
    // 0xbc04531  push rsi                                   ; prologue
    // 0xbc04532  sub rsp,0x48                               ; prologue
    // 0xbc04536  lea rbp,[rsp+0x40]                         ; prologue
    // 0xbc0453b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE    ; stack cookie / frame marker
    // 0xbc04543  mov r8,rcx                                 ; r8 = a0 (copy of RCX)
    PassBodyD* const self = a0;                            // 0xbc04543  mov r8,rcx

    // 0xbc04546  mov rax,[rcx+0x3A8]                       ; R a0+0x3A8
    // 0xbc0454d  mov [rbp-0x18],rax                         ; W [rbp-0x18] = saved_3a8
    std::uint64_t saved_3a8 = self->field_0x3A8;     // 0xbc04546 mov rax,[rcx+0x3A8] ; 0xbc0454d mov [rbp-0x18],rax

    // 0xbc04551  xorps xmm0,xmm0                            ; zero [rbp-0x10] (16 bytes)
    // 0xbc04554  movups [rbp-0x10],xmm0                     ; (local zeroing, handled by declaration)
    void* obj1 = nullptr;                                  // [rbp-0x10] zero-initialized, then written below

    // 0xbc04558  mov rax,[rcx+0x3B8]                       ; R a0+0x3B8
    // 0xbc0455f  test rax,rax
    // 0xbc04562  je short 0xBC04571                         ; taken when a0+0x3B8 == 0 (nothing added)
    // 0xbc04564  lock inc dword ptr [rax+8]                ; W (a0+0x3B8)+0x8  addref
    // 0xbc04568  mov rax,[r8+0x3B8]                        ; R a0+0x3B8 (reload)
    // 0xbc0456f  jmp short 0xBC04573
    RefCounted* old_ref = self->field_0x3B8;               // 0xbc04558 mov rax,[rcx+0x3B8] ; 0xbc0455f test rax,rax ; 0xbc04562 je short 0xBC04571
    if (old_ref != nullptr) {                              // 0xbc04562 je not taken -> addref path
        old_ref->strong.fetch_add(1u, std::memory_order_seq_cst);  // 0xbc04564 lock inc dword ptr [rax+8]
        old_ref = self->field_0x3B8;                       // 0xbc04568 mov rax,[r8+0x3B8]  (reload)
    } else {                                               // 0xbc04571  xor eax,eax  (fail path: rax = 0)
        old_ref = nullptr;                                 // 0xbc04571 xor eax,eax
    }
    // 0xbc04573  mov rcx,[r8+0x3B0]                        ; R a0+0x3B0
    // 0xbc0457a  mov [rbp-0x10],rcx                         ; W [rbp-0x10] = obj1
    // 0xbc0457e  mov [rbp-8],rax                            ; W [rbp-8] = old_ref (rax == old_ref or 0)
    obj1 = self->field_0x3B0;                              // 0xbc04573 mov rcx,[r8+0x3B0] ; 0xbc0457a mov [rbp-0x10],rcx
    // [rbp-8] = old_ref (already in variable)

    // 0xbc04582  mov [rcx+0x18],rdx                         ; W obj1+0x18 = a1 (RDX)
    static_cast<PassObj*>(obj1)->field_0x18 = a1;          // 0xbc04582 mov [rcx+0x18],rdx

    // 0xbc04586  mov rcx,[r8+0x70]                          ; R a0+0x70
    // 0xbc0458a  test rcx,rcx
    // 0xbc0458d  je short 0xBC045ED                         ; taken when a0+0x70 == 0
    void* const obj2 = self->field_0x70;                   // 0xbc04586 mov rcx,[r8+0x70] ; 0xbc0458a test rcx,rcx ; 0xbc0458d je short 0xBC045ED
    if (obj2 == nullptr) {                                 // 0xbc0458d je taken -> loc_bc045ed
        // 0xbc045ed  call 0xEEC59E0                          ; -> sub_eec59e0 (noreturn: std::_Xbad_function_call)
        // 0xbc045f2  nop                                     ; unreachable
        // 0xbc045f3  int3                                   ; unreachable
        sub_eec59e0();                                     // 0xbc045ed call 0xEEC59E0  (noreturn)
        __assume(false);                                   // 0xbc045f2 nop / 0xbc045f3 int3  (unreachable: sub_eec59e0 never returns)
    }

    // 0xbc0458f  add r8,0x78                                ; r8 = a0 + 0x78 (dead: r8 not read after this point)

    // 0xbc04593  mov rax,[rcx]                              ; R obj2+0x0 (vtable pointer)
    // 0xbc04596  mov rax,[rax+0x10]                         ; R vtable+0x10 -> rax (target funcptr, out-of-ABI for sub_eea6040)
    // 0xbc0459a  lea rdx,[rbp-0x18]                         ; RDX = &saved_3a8 (context for callback)
    // 0xbc0459e  call qword ptr [0xF99FFA0]                ; [data_f99ffa0] = sub_eea6040; body `jmp rax` -> target(obj2, &saved_3a8)
    void** const obj2_vtable = *reinterpret_cast<void***>(obj2);  // 0xbc04593 mov rax,[rcx]
    void* const target1 = obj2_vtable[2];                  // 0xbc04596 mov rax,[rax+0x10]  (vtable[0x10/8=2])
    (void)target1;  // keep RAX = target1 for sub_eea6040's `jmp rax`
    // 0xbc0459a  lea rdx,[rbp-0x18]                         ; RDX = &saved_3a8
    // 0xbc0459e  call qword ptr [0xF99FFA0]                ; -> sub_eea6040: jmp rax -> target1(obj2)
    boundary::g_eea6040_thunk(obj2, reinterpret_cast<void*>(&saved_3a8));           // 0xbc0459e call qword ptr [0xF99FFA0]

    // 0xbc045a4  nop                                        ; (padding after call, no semantic effect)
    // 0xbc045a5  mov rax,[rbp-0x10]                         ; R obj1
    // 0xbc045a9  mov qword ptr [rax+0x18],0                 ; W obj1+0x18 = 0
    static_cast<PassObj*>(obj1)->field_0x18 = 0;           // 0xbc045a5 mov rax,[rbp-0x10] ; 0xbc045a9 mov qword ptr [rax+0x18],0

    // 0xbc045b1  mov rsi,[rbp-8]                            ; R old_ref
    // 0xbc045b5  test rsi,rsi
    // 0xbc045b8  je short 0xBC045E6                         ; taken when old_ref == 0 (nothing released)
    if (old_ref != nullptr) {                              // 0xbc045b8 je not taken -> release path
        // 0xbc045ba  lock dec dword ptr [rsi+8]            ; W old_ref+0x8  strong release
        // 0xbc045be  jne short 0xBC045E6                   ; not taken when strong reached 0
        if (old_ref->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {  // 0xbc045ba..0xbc045be
            // strong reached 0: virtual destructor vtable[0](old_ref)
            // 0xbc045c0  mov rax,[rsi]                      ; R old_ref+0x0 (vtable)
            // 0xbc045c3  mov rax,[rax]                      ; R vtable+0x0 (destructor slot) -> rax
            // 0xbc045c6  mov rcx,rsi                        ; RCX = old_ref
            // 0xbc045c9  call qword ptr [0xF99FFA0]        ; [data_f99ffa0] = sub_eea6040; jmp rax -> destructor(old_ref)
            void** const old_vtable = *reinterpret_cast<void***>(old_ref);  // 0xbc045c0 mov rax,[rsi]
            void* const destructor = old_vtable[0];        // 0xbc045c3 mov rax,[rax]  (vtable[0])
            (void)destructor;  // keep RAX = destructor for sub_eea6040's `jmp rax`
            // 0xbc045c6  mov rcx,rsi                        ; RCX = old_ref
            // 0xbc045c9  call qword ptr [0xF99FFA0]        ; -> sub_eea6040: jmp rax -> destructor(old_ref)
            boundary::g_eea6040_thunk(old_ref, nullptr);   // 0xbc045c9 call qword ptr [0xF99FFA0]

            // 0xbc045cf  lock dec dword ptr [rsi+0xC]      ; W old_ref+0xC  weak release
            // 0xbc045d3  jne short 0xBC045E6               ; not taken when weak reached 0
            if (old_ref->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {  // 0xbc045cf..0xbc045d3
                // weak reached 0: virtual deleter vtable[8](old_ref)
                // 0xbc045d5  mov rax,[rsi]                  ; R old_ref+0x0 (vtable)
                // 0xbc045d8  mov rax,[rax+8]                ; R vtable+0x8 (deleter slot) -> rax
                // 0xbc045dc  mov rcx,rsi                    ; RCX = old_ref
                // 0xbc045df  call qword ptr [0xF99FFA0]    ; [data_f99ffa0] = sub_eea6040; jmp rax -> deleter(old_ref)
                void* const deleter = old_vtable[1];       // 0xbc045d5 mov rax,[rsi] ; 0xbc045d8 mov rax,[rax+8]  (vtable[8/8=1])
                (void)deleter;  // keep RAX = deleter for sub_eea6040's `jmp rax`
                // 0xbc045dc  mov rcx,rsi                    ; RCX = old_ref
                // 0xbc045df  call qword ptr [0xF99FFA0]    ; -> sub_eea6040: jmp rax -> deleter(old_ref)
                boundary::g_eea6040_thunk(old_ref, nullptr);  // 0xbc045df call qword ptr [0xF99FFA0]
            }
        }
    }
    // 0xbc045e6  add rsp,0x48                               ; epilogue
    // 0xbc045ea  pop rsi                                    ; epilogue
    // 0xbc045eb  pop rbp                                    ; epilogue
    // 0xbc045ec  ret                                        ; epilogue
    return;
}

// Verbatim instructions of the function (matches `rdis dis 0xbc04530 0xc4` from the exe,
// machine-checked with tools/sigs/verify_oc.py):
#if 0
0xbc04530  push rbp
0xbc04531  push rsi
0xbc04532  sub rsp,0x48
0xbc04536  lea rbp,[rsp+0x40]
0xbc0453b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0xbc04543  mov r8,rcx
0xbc04546  mov rax,[rcx+0x3A8]
0xbc0454d  mov [rbp-0x18],rax
0xbc04551  xorps xmm0,xmm0
0xbc04554  movups [rbp-0x10],xmm0
0xbc04558  mov rax,[rcx+0x3B8]
0xbc0455f  test rax,rax
0xbc04562  je short 0xBC04571
0xbc04564  lock inc dword ptr [rax+8]
0xbc04568  mov rax,[r8+0x3B8]
0xbc0456f  jmp short 0xBC04573
0xbc04571  xor eax,eax
0xbc04573  mov rcx,[r8+0x3B0]
0xbc0457a  mov [rbp-0x10],rcx
0xbc0457e  mov [rbp-8],rax
0xbc04582  mov [rcx+0x18],rdx
0xbc04586  mov rcx,[r8+0x70]
0xbc0458a  test rcx,rcx
0xbc0458d  je short 0xBC045ED
0xbc0458f  add r8,0x78
0xbc04593  mov rax,[rcx]
0xbc04596  mov rax,[rax+0x10]
0xbc0459a  lea rdx,[rbp-0x18]
0xbc0459e  call qword ptr [0xF99FFA0]
0xbc045a4  nop
0xbc045a5  mov rax,[rbp-0x10]
0xbc045a9  mov qword ptr [rax+0x18],0
0xbc045b1  mov rsi,[rbp-8]
0xbc045b5  test rsi,rsi
0xbc045b8  je short 0xBC045E6
0xbc045ba  lock dec dword ptr [rsi+8]
0xbc045be  jne short 0xBC045E6
0xbc045c0  mov rax,[rsi]
0xbc045c3  mov rax,[rax]
0xbc045c6  mov rcx,rsi
0xbc045c9  call qword ptr [0xF99FFA0]
0xbc045cf  lock dec dword ptr [rsi+0xC]
0xbc045d3  jne short 0xBC045E6
0xbc045d5  mov rax,[rsi]
0xbc045d8  mov rax,[rax+8]
0xbc045dc  mov rcx,rsi
0xbc045df  call qword ptr [0xF99FFA0]
0xbc045e5  nop
0xbc045e6  add rsp,0x48
0xbc045ea  pop rsi
0xbc045eb  pop rbp
0xbc045ec  ret
#endif

static native::Footprint sub_bc04530Footprint(PassBodyD* /*a0*/, std::uint64_t /*a1*/) {
    // All writes go through run-time pointers (obj1 = a0+0x3B0, old_ref = a0+0x3B8)
    // read from a0; no fixed-offset writes to a0 itself. Footprint is empty.
    return native::Footprint();
}

LIFT_FN(sub_bc04530, "sub_bc04530", 0xbc04530, sub_bc04530, sub_bc04530Footprint);

} // namespace native