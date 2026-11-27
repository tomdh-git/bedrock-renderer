// LIFT 0x78ce0 size 0x98 1.26.62.01 sub_78ce0
#include "sub_78ce0.h"

#include "client/features/render/native/Lift.h"

namespace native {

// sub_78ce0 (0x78ce0, size 0x98, 1.26.62.01): see sub_78ce0.h for the instruction-by-instruction
// reversal. Observable effect: [a0+0x00..0x17] = 0, return void; the refcount-release block is dead
// because [a0+0x08] is zeroed by the movups before it is loaded.

// 0x78d07 / 0x78d1d / 0x78d43  call qword ptr [0xF99FFA0]
// sub_eea6040 (vendor boundary) is the loader-resolved thunk in data slot 0xF99FFA0; each indirect
// call reads the pointer at call time and invokes it with RCX = objectA (rule #69).
static void callReleaseThunk(void* objectA)
{
    auto fn = reinterpret_cast<Eea6040Callee>(
        *reinterpret_cast<std::uintptr_t*>(RewriteRegistry::imageBase() + kReleaseSlotRva));
    fn(objectA);
}

static native::Footprint sub_78ce0Footprint(void* a0)
{
    native::Footprint fp;
    fp.push_back(native::Region{ a0, 0x18ull });
    return fp;
}

void sub_78ce0(void* a0)
{
    // 0x78ce0..0x78ce6
    //   0x78ce0  push rsi
    //   0x78ce1  push rdi
    //   0x78ce2  sub rsp,0x28
    //   0x78ce6  mov rsi,rcx        ; rsi = a0 = this, callee-saved register
    void* rsi = a0;
    (void)rsi;

    // 0x78ce9..0x78cf0
    //   0x78ce9  xorps xmm0,xmm0    ; xmm0 = 0
    //   0x78cec  movups [rcx],xmm0  ; W [a0+0x00..0x0F] = 0  (16-byte store)
    auto* thisObj = reinterpret_cast<Sub78ce0This*>(a0);
    thisObj->field00 = 0;
    thisObj->field08 = 0;

    // 0x78cf0..0x78cf6
    //   0x78cf0  mov rdi,[rcx+8]    ; R objectA = [a0+0x08]
    //   0x78cf3  test rdi,rdi
    //   0x78cf6  je short 0x78D69   ; objectA == 0 -> skip release (always taken at runtime:
    //                                [a0+0x08] was just zeroed by the movups above)
    Sub78ce0Refcounted* objectA =
        reinterpret_cast<Sub78ce0Refcounted*>(thisObj->field08); // == 0 at runtime
    if (objectA != nullptr) {
        // 0x78cf8..0x78cfc
        //   0x78cf8  lock dec dword ptr [rdi+8]      ; --objectA->strongRef
        //   0x78cfc  jne short 0x78D23               ; strong != 0 -> block 2
        //   strong == 0:
        //   0x78cfe  mov rax,[rdi]                   ; R objectA->vfptr
        //   0x78d01  mov rax,[rax]                   ; R objectA->vfptr->[0]
        //   0x78d04  mov rcx,rdi                     ; RCX = objectA
        //   0x78d07  call qword ptr [0xF99FFA0]      ; sub_eea6040(objectA)  [destroy #1]
        //   0x78d0d  lock dec dword ptr [rdi+0xC]    ; --objectA->weakRef
        //   0x78d11  jne short 0x78D23               ; weak != 0 -> block 2
        if (--objectA->strongRef == 0) {
            callReleaseThunk(objectA);                // 0x78d07  call qword ptr [0xF99FFA0]
            // 0x78d0d..0x78d11
            //   0x78d0d  lock dec dword ptr [rdi+0xC]   ; --objectA->weakRef
            //   0x78d11  jne short 0x78D23              ; weak != 0 -> block 2
            if (--objectA->weakRef == 0) {              // 0x78d11 jne short 0x78D23
                //   0x78d13  mov rax,[rdi]
                //   0x78d16  mov rax,[rax+8]            ; R objectA->vfptr->[1]
                //   0x78d1a  mov rcx,rdi
                //   0x78d1d  call qword ptr [0xF99FFA0] ; sub_eea6040(objectA) [destroy #2]
                callReleaseThunk(objectA);              // 0x78d1d  call qword ptr [0xF99FFA0]
            }
        }
        // 0x78d23..0x78d2f  block 2: reached from block 1 in all cases
        //   0x78d23  mov rdi,[rsi+8]                  ; R objectA = [a0+0x08] (reload)
        //   0x78d27  mov qword ptr [rsi+0x10],0       ; W [a0+0x10] = 0
        //   0x78d2f  test rdi,rdi
        objectA = reinterpret_cast<Sub78ce0Refcounted*>(thisObj->field08); // 0x78d23 reload [a0+0x08]
        thisObj->field0x10 = 0;                        // 0x78d27  mov qword ptr [rsi+0x10],0
        // 0x78d2f..0x78d32
        //   0x78d2f  test rdi,rdi
        //   0x78d32  je short 0x78D71                 ; objectA == 0 -> epilogue
        if (objectA != nullptr) {
            // 0x78d34..0x78d38
            //   0x78d34  lock dec dword ptr [rdi+8]      ; --objectA->strongRef
            //   0x78d38  jne short 0x78D71               ; strong != 0 -> epilogue
            if (--objectA->strongRef == 0) {
                //   0x78d3a  mov rax,[rdi]
                //   0x78d3d  mov rax,[rax]               ; R objectA->vfptr->[0]
                //   0x78d40  mov rcx,rdi
                //   0x78d43  call qword ptr [0xF99FFA0]  ; sub_eea6040(objectA) [destroy #3]
                callReleaseThunk(objectA);               // 0x78d43  call qword ptr [0xF99FFA0]
                // 0x78d49..0x78d4d
                //   0x78d49  lock dec dword ptr [rdi+0xC]  ; --objectA->weakRef
                //   0x78d4d  jne short 0x78D71             ; weak != 0 -> epilogue
                if (--objectA->weakRef == 0) {            // 0x78d4d jne short 0x78D71
                    //   0x78d4f  mov rax,[rdi]
                    //   0x78d52  mov rax,[rax+8]          ; R objectA->vfptr->[1]
                    //   0x78d56  mov rdx,[0xF99FFA0]      ; RDX = sub_eea6040
                    //   0x78d5d  mov rcx,rdi              ; RCX = objectA
                    //   0x78d60  add rsp,0x28
                    //   0x78d64  pop rdi
                    //   0x78d65  pop rsi
                    //   0x78d66  jmp rdx                  ; tail call sub_eea6040(objectA), noreturn
                    callReleaseThunk(objectA);            // 0x78d56..0x78d66 tail call (dead)
                    __assume(false);                     // original: jmp rdx, does not return
                }
            }
        }
        // 0x78d71..0x78d78  epilogue: add rsp,0x28; pop rdi; pop rsi; ret
        return;
    }
    // 0x78d69..0x78d6a   (objectA == 0 path, taken at runtime)
    //   0x78d69  mov qword ptr [rsi+0x10],0   ; W [a0+0x10] = 0
    thisObj->field0x10 = 0;
    // 0x78d71..0x78d78   epilogue: add rsp,0x28; pop rdi; pop rsi; ret
    return;
}

// Verbatim call quotes for liftcheck verification
#if 0
0x78d07  call qword ptr [0xF99FFA0]
0x78d1d  call qword ptr [0xF99FFA0]
0x78d43  call qword ptr [0xF99FFA0]
#endif

static_assert(offsetof(Sub78ce0This, field00) == 0x00, "sub_78ce0: field00 at +0x00");
static_assert(offsetof(Sub78ce0This, field08) == 0x08, "sub_78ce0: objectA pointer at +0x08");
static_assert(offsetof(Sub78ce0This, field0x10) == 0x10, "sub_78ce0: clear field at +0x10");
static_assert(sizeof(Sub78ce0This) == 0x18, "sub_78ce0: this object size 0x18");
static_assert(offsetof(Sub78ce0Refcounted, strongRef) == 0x08, "sub_78ce0: strong refcount at +0x08");
static_assert(offsetof(Sub78ce0Refcounted, weakRef) == 0x0C, "sub_78ce0: weak refcount at +0x0C");

LIFT_FN(sub_78ce0, "sub_78ce0", 0x78CE0, sub_78ce0, &sub_78ce0Footprint);

} // namespace native
