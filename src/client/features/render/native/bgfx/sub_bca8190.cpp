// LIFT 0xbca8190 size 0x135 1.26.62.01 sub_bca8190
#include "client/features/render/native/bgfx/sub_bca8190.h"

#include <cstdint>
#include <intrin.h>

#include "client/features/render/native/Lift.h"

// Calls out of this function, verbatim from the disassembly of [0xbca8190, 0xbca82c5):
// 0xbca81d9  call 0xE935700                 ; native::sub_e935700 (lift-classified callee, jmp sub_392960)
// 0xbca8215  call qword ptr [0xF99FFA0]     ; native::Boundary sub_eea6040 via data slot 0xF99FFA0 (vendor)
// 0xbca823b  call qword ptr [0xF99FFA0]     ; same
// 0xbca8251  call qword ptr [0xF99FFA0]     ; same
// 0xbca828c  call 0xE935700                 ; native::sub_e935700
// 0xbca82be  call qword ptr [0xF9A8C78]     ; data slot 0xF9A8C78: target outside the lift set and native_boundary.tsv;
//                                        ; called through the pointer read from the slot with zeroed argument registers (data-slot rule)
// UNRESOLVED CALL = none

namespace {

// 0xeea6040 (vendor, docs/data/native_boundary.tsv): thunk through data slot 0xF99FFA0, loader-resolved.
// Called with the released object in rcx; the return value is unused (void).
native::Boundary<void, void*> sub_eea6040("sub_eea6040");

} // namespace

namespace native::bgfx {

static native::Footprint sub_bca8190_footprint(VvFrameGraphBuilderState* /*self*/) {
    return { { { self, 0xA0ull } } };
}

void sub_bca8190(VvFrameGraphBuilderState* self) {
    // 0xbca8190..0xbca819a : prologue. rcx = self; rsi = working copy of self.
    // 0xbca8190  push rsi
    // 0xbca8191  push rdi
    // 0xbca8192  sub rsp,0x28
    // 0xbca8196  mov rsi,rcx

    // 0xbca8199..0xbca81da : slot B (+0x80/+0x90/+0x98). Heap deallocation when mCapB >= 0x10.
    // 0xbca8199  mov rax,[rcx+0x98]          ; R self->mCapB
    // 0xbca81a0  cmp rax,0x10
    // 0xbca81a4  jb short 0xBCA81DE
    // 0xbca81a6  mov rcx,[rsi+0x80]          ; R self->mPtrB (rcx is reused; self stays in rsi)
    // 0xbca81ad  lea rdx,[rax+1]             ; rdx = mCapB + 1, dead at the call (sub_392960 overwrites rdx with rcx)
    // 0xbca81b1  cmp rdx,0x1000
    // 0xbca81b8  jb short 0xBCA81D9
    // 0xbca81ba  mov r8,[rcx-8]              ; R *(ptrB - 8) heap block size
    // 0xbca81be  add rcx,0xFFFFFFFFFFFFFFF8  ; rcx = ptrB - 8
    // 0xbca81c2  sub rcx,r8                  ; rcx = (ptrB - 8) - blockSize
    // 0xbca81c5  cmp rcx,0x20
    // 0xbca81c9  jae 0xBCA82AB               ; heap-guard failure -> fatal path
    // 0xbca81cf  add rax,0x28                ; rdx = mCapB + 1 + 0x28, dead at the call
    // 0xbca81d3  mov rdx,rax
    // 0xbca81d6  mov rcx,r8                  ; rcx = blockSize
    // 0xbca81d9  call 0xE935700
    using FatalFn = void (*)(void*, void*, void*, void*);
    if (self->mCapB >= 0x10ULL) {
        void* ptrB = self->mPtrB;
        if (self->mCapB + 1ULL >= 0x1000ULL) {
            uint64_t blockSize = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptrB) - 8);
            uint8_t* blockBase = reinterpret_cast<uint8_t*>(ptrB) - 8;
            if (reinterpret_cast<uintptr_t>(blockBase) - blockSize >= 0x20ULL) {
                // 0xbca82ab..0xbca82c5 : fatal path. The argument registers are zeroed, then the pointer
                // stored in data slot 0xF9A8C78 is read and called; unreachable afterwards (original pads with int3).
                // 0xbca82ab  mov qword ptr [rsp+0x20],0
                // 0xbca82b4  xor ecx,ecx
                // 0xbca82b6  xor edx,edx
                // 0xbca82b8  xor r8d,r8d
                // 0xbca82bb  xor r9d,r9d
                // 0xbca82be  call qword ptr [0xF9A8C78]
                //     bca82c4  int3
                // 0xF9A8C78 is an RVA into .rdata holding a loader-resolved function pointer (data-slot rule);
                // read the pointer at call time, exactly as the instruction does, then call it.
                void** fatalSlot = reinterpret_cast<void**>(RewriteRegistry::imageBase() + 0xF9A8C78ull);
                FatalFn fatal = reinterpret_cast<FatalFn>(*fatalSlot);
                fatal(nullptr, nullptr, nullptr, nullptr);
            } else {
                native::sub_e935700(reinterpret_cast<void*>(blockSize));
            }
        } else {
            native::sub_e935700(ptrB);
        }
    }

    // 0xbca81de..0xbca81fc : reset slot B to inline (small) state.
    // 0xbca81de  mov qword ptr [rsi+0x90],0   ; W self->mSizeB = 0
    // 0xbca81e9  mov qword ptr [rsi+0x98],0xF ; W self->mCapB = 0xF
    // 0xbca81f4  mov byte ptr [rsi+0x80],0    ; W self->mInlineB[0] = 0
    self->mSizeB = 0;
    self->mCapB = 0xFULL;
    self->mInlineB[0] = 0;

    // 0xbca81fb..0xbca821c : release mObject (+0x70).
    // 0xbca81fb  mov rcx,[rsi+0x70]           ; R self->mObject
    // 0xbca81ff  test rcx,rcx
    // 0xbca8202  je short 0xBCA8223
    // 0xbca8204  lea rax,[rsi+0x38]           ; address of &self->mInlineObject
    // 0xbca8208  cmp rcx,rax
    // 0xbca820b  setne dl                     ; result unused
    // 0xbca820e  mov rax,[rcx]                ; R *mObject (vptr), unused
    // 0xbca8211  mov rax,[rax+0x20]           ; R *(mObject->vtable + 0x20), unused
    // 0xbca8215  call qword ptr [0xF99FFA0]   ; sub_eea6040(mObject)
    // 0xbca821b  mov qword ptr [rsi+0x70],0   ; W self->mObject = nullptr
    if (void* obj = self->mObject) {
        (void)(obj != reinterpret_cast<void*>(&self->mInlineObject));
        uintptr_t vptr = *reinterpret_cast<uintptr_t*>(obj);
        uintptr_t vslot4 = *reinterpret_cast<uintptr_t*>(vptr + 0x20);
        (void)vptr;
        (void)vslot4;
        sub_eea6040(obj);
        self->mObject = nullptr;
    }

    // 0xbca8223..0xbca8258 : release mRefObject (+0x28). Decrement the refcount at +8; when it
    // reaches zero call sub_eea6040(mRefObject), then decrement the weak count at +0xC; when it
    // reaches zero call sub_eea6040(mRefObject) again. The field itself is not cleared.
    // 0xbca8223  mov rdi,[rsi+0x28]           ; R self->mRefObject
    // 0xbca8227  test rdi,rdi
    // 0xbca822a  je short 0xBCA8257
    // 0xbca822c  lock dec dword ptr [rdi+8]   ; W *(mRefObject + 8)
    // 0xbca8230  jne short 0xBCA8257
    // 0xbca8232  mov rax,[rdi]                ; R *mRefObject (vptr), unused
    // 0xbca8235  mov rax,[rax]                ; R *(mRefObject->vtable + 0), unused
    // 0xbca8238  mov rcx,rdi
    // 0xbca823b  call qword ptr [0xF99FFA0]   ; sub_eea6040(mRefObject)
    // 0xbca8241  lock dec dword ptr [rdi+0xC] ; W *(mRefObject + 0xC)
    // 0xbca8245  jne short 0xBCA8257
    // 0xbca8247  mov rax,[rdi]
    // 0xbca824a  mov rax,[rax+8]              ; R *(mRefObject->vtable + 8), unused
    // 0xbca824e  mov rcx,rdi
    // 0xbca8251  call qword ptr [0xF99FFA0]   ; sub_eea6040(mRefObject)
    if (void* refObj = self->mRefObject) {
        if (_InterlockedDecrement(reinterpret_cast<volatile long*>(reinterpret_cast<uint8_t*>(refObj) + 8)) == 0) {
            uintptr_t rvptr = *reinterpret_cast<uintptr_t*>(refObj);
            rvptr = *reinterpret_cast<uintptr_t*>(rvptr + 0);
            (void)rvptr;
            sub_eea6040(refObj);
            if (_InterlockedDecrement(reinterpret_cast<volatile long*>(reinterpret_cast<uint8_t*>(refObj) + 0xC)) == 0) {
                uintptr_t rwptr = *reinterpret_cast<uintptr_t*>(refObj);
                rwptr = *reinterpret_cast<uintptr_t*>(rwptr + 8);
                (void)rwptr;
                sub_eea6040(refObj);
            }
        }
    }

    // 0xbca8257..0xbca82ab : slot A (+0x00/+0x10/+0x18). Heap deallocation when mCapA >= 0x10.
    // 0xbca8257  mov rax,[rsi+0x18]           ; R self->mCapA
    // 0xbca825b  cmp rax,0x10
    // 0xbca825f  jb short 0xBCA8291
    // 0xbca8261  mov rcx,[rsi]                ; R self->mPtrA
    // 0xbca8264  lea rdx,[rax+1]
    // 0xbca8268  cmp rdx,0x1000
    // 0xbca826f  jb short 0xBCA828C
    // 0xbca8271  mov r8,[rcx-8]               ; R *(ptrA - 8) heap block size
    // 0xbca8275  add rcx,0xFFFFFFFFFFFFFFF8  ; rcx = ptrA - 8
    // 0xbca8279  sub rcx,r8                  ; rcx = (ptrA - 8) - blockSize
    // 0xbca827c  cmp rcx,0x20
    // 0xbca8280  jae short 0xBCA82AB          ; heap-guard failure -> fatal path
    // 0xbca8282  add rax,0x28                ; rdx = mCapA + 1 + 0x28, dead at the call
    // 0xbca8286  mov rdx,rax
    // 0xbca8289  mov rcx,r8                  ; rcx = blockSize
    // 0xbca828c  call 0xE935700
    if (self->mCapA >= 0x10ULL) {
        void* ptrA = self->mPtrA;
        if (self->mCapA + 1ULL >= 0x1000ULL) {
            uint64_t blockSize = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(ptrA) - 8);
            uint8_t* blockBase = reinterpret_cast<uint8_t*>(ptrA) - 8;
            if (reinterpret_cast<uintptr_t>(blockBase) - blockSize >= 0x20ULL) {
                FatalFn fatal = reinterpret_cast<FatalFn>(RewriteRegistry::imageBase() + 0xF9A8C78ull);
                fatal(nullptr, nullptr, nullptr, nullptr);
            } else {
                native::sub_e935700(reinterpret_cast<void*>(blockSize));
            }
        } else {
            native::sub_e935700(ptrA);
        }
    }

    // 0xbca8291..0xbca82ac : reset slot A to inline state and epilogue.
    // 0xbca8291  mov qword ptr [rsi+0x10],0   ; W self->mSizeA = 0
    // 0xbca8299  mov qword ptr [rsi+0x18],0xF ; W self->mCapA = 0xF
    // 0xbca82a1  mov byte ptr [rsi],0         ; W self->mInlineA[0] = 0
    // 0xbca82a4  add rsp,0x28
    // 0xbca82a8  pop rdi
    // 0xbca82a9  pop rsi
    // 0xbca82aa  ret
    self->mSizeA = 0;
    self->mCapA = 0xFULL;
    self->mInlineA[0] = 0;
}

static_assert(sizeof(VvFrameGraphBuilderState) >= 0xA0, "sub_bca8190 touches up to +0x9F");

LIFT_FN(sub_bca8190, "sub_bca8190", 0xbca8190, sub_bca8190, &sub_bca8190_footprint);

} // namespace native::bgfx
