// LIFT 0xe81d850 size 0x1cd 1.26.62.01 sub_e81d850
#include "sub_e81d850.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>

static_assert(sizeof(void*) == 8, "ptr");

namespace {

// Global slot [0x12BB4910]: device/renderer context pointer.
constexpr uintptr_t kGlobalSlot = 0x1412BB4910ULL;

// CFG dispatch thunk: [0xF99FFA0] = sub_eea6040 (`jmp rax`), loader-resolved
// (docs/data/native_boundary.tsv, class vendor). Every `call qword ptr [0xF99FFA0]`
// in the original tail-jumps to the rax preloaded immediately before the call, so
// the net effect is an indirect call through that preloaded vtable entry.
//   0xe81d8ae: vtable[0x1A8/8]  0xe81d8f3: vtable[0x1B0/8]

} // namespace

// Verbatim log of every call instruction in [0xe81d850, 0xe81da1d) (rdis dis output,
// two spaces after the address; trailing "; ..." annotations omitted):
#if 0
0xe81d8ae  call qword ptr [0xF99FFA0]
0xe81d8f3  call qword ptr [0xF99FFA0]
0xe81d903  call 0xEEC59F0
0xe81da03  call 0xEEC5A00
0xe81da17  call 0xEEC5A00
#endif
// UNRESOLVED CALL = none: every call target is either the loader-resolved CFG thunk
// sub_eea6040 (vendor, data slot 0xF99FFA0) or a forward-declared IAT forwarder
// (sub_eec59f0/sub_eec5a00, hard rule 69) reached by direct call.

namespace native::d3d12 {

extern "C" void sub_e81d850(void* rcx, void* rdx, uint32_t r8d) {
    auto* self = reinterpret_cast<S81d850*>(rcx);   // rsi = this
    void* a1 = rdx;                                 // rdi = a1
    uint32_t idx = r8d;                             // eax = index

    // 0xe81d850..0xe81d868: push regs; rdi=a1; rsi=this; eax=idx; rax=3*idx;
    //   0xe81d868  mov byte ptr [rcx+rax*8+0x1830],1
    //   (rcx still = this here)
    {
        uint64_t off = static_cast<uint64_t>(idx) * 3ULL * 8ULL; // rax*8 = 24*idx
        reinterpret_cast<uint8_t*>(self)[0x1830 + static_cast<size_t>(idx) * 0x18] = 1; // byte @ meta[idx]+0x10
        (void)off;
    }
    // 0xe81d870..0xe81d882: G = *(0x12BB4910); G2 = *(G+0x3C563B0);
    //   this->meta[idx].stamp (meta[idx]+0x08) = *(G2+0x28)
    {
        void* g = *reinterpret_cast<void**>(kGlobalSlot);
        void* g2 = *reinterpret_cast<void**>(reinterpret_cast<char*>(g) + 0x3C563B0);
        uint64_t stamp = *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(g2) + 0x28);
        reinterpret_cast<MetaEntry*>(reinterpret_cast<char*>(&self->meta_ring) + static_cast<size_t>(idx) * 0x18)->stamp = stamp;
    }

    // 0xe81d88a..0xe81d8ae: dev = a1->[0x30]; ebx = 2*idx; r9d = 2*idx+1;
    //   rdx = self->p7828; rax = dev->vtable[0x1A8]; r8d = 2;
    //   0xe81d8ae  call qword ptr [0xF99FFA0]  -> vtable[0x1A8](dev, p7828, 2, 2*idx+1)
    {
        void* dev = *reinterpret_cast<void**>(reinterpret_cast<char*>(a1) + 0x30);
        uint32_t idx2 = idx + idx;                       // ebx = 2*idx
        void** vt = *reinterpret_cast<void***>(dev);
        using V1Fn = void (__fastcall*)(void*, void*, uint32_t, uint32_t);
        reinterpret_cast<V1Fn>(vt[0x1A8 / 8])(dev, self->p7828, 2u, idx2 + 1u);
    }

    // 0xe81d8b4..0xe81d8f3: dev = a1->[0x30]; r8 = idx2*8; r9 = self->p7820;
    //   rdx = self->p7828; rax = dev->vtable[0x1B0]; stack: arg5=2, arg6=p7820, arg7=idx2*8;
    //   r8d=2; r9d=idx2;
    //   0xe81d8f3  call qword ptr [0xF99FFA0]  -> vtable[0x1B0](dev, p7828, 2, idx2, 2, p7820, idx2*8)
    {
        void* dev = *reinterpret_cast<void**>(reinterpret_cast<char*>(a1) + 0x30);
        uint32_t idx2 = idx + idx;
        void** vt = *reinterpret_cast<void***>(dev);
        using V2Fn = void (__fastcall*)(void*, void*, uint32_t, uint32_t, uint32_t, void*, uint64_t);
        reinterpret_cast<V2Fn>(vt[0x1B0 / 8])(dev, self->p7828, 2u, idx2, 2u, self->p7820, static_cast<uint64_t>(idx2) * 8ULL);
    }

    // 0xe81d8f9..0xe81d91a: rdi = &self->lock; lock = sub_eec59f0(lock);
    //   if (lock != 0) -> error path (0xe81d9fe): sub_eec5a00(5); fall through to 0xe81da08;
    //   if (self->guard == 0x7FFFFFFF) -> error path (0xe81da08): guard=0x7FFFFFFE; sub_eec5a00(6); int3
    {
        void* lock = &self->lock;
        int32_t lockResult = native::sub_eec59f0(lock);
        if (lockResult != 0) {
            // 0xe81d9fe..0xe81da03
            native::sub_eec5a00(5u);
            // 0xe81da08..0xe81da1c
            // fall through into the shared error tail below (0xe81da08)
            self->guard = 0x7FFFFFFEu;
            native::sub_eec5a00(6u);
            __debugbreak();
            __assume(false);
        }
        if (self->guard == 0x7FFFFFFFu) {
            // 0xe81da08..0xe81da1c
            self->guard = 0x7FFFFFFEu;
            native::sub_eec5a00(6u);
            __debugbreak();
            __assume(false);
        }
    }

    // 0xe81d920..0xe81d93d: ebx=M; edx=A; ecx=c; eax = (A-c) + (((A-c)>>31)&M);
    //   if (eax == 0) -> end (unlock)
    uint32_t M = self->capacity;      // ebx = [rsi+0x7838]
    uint32_t A = self->writeIdx;      // edx = [rsi+0x783C]
    uint32_t c = self->cursor;        // ecx = [rsi+0x7844]
    uint32_t d = A - c;              // sub edx,ecx
    uint32_t eax = d + (static_cast<uint32_t>(static_cast<int32_t>(d) >> 31) & M); // sar/and/add
    if (eax == 0) {
        // 0xe81d9eb..0xe81d9f9: mov rcx,rdi (lock); ...; jmp sub_eec5a10
        native::sub_eec5a10(&self->lock);
        return;
    }

    // 0xe81d943..0xe81d95b: r8=&meta; r9=*(0x12BB4910); r10=this+8; r11=1
    void* g = *reinterpret_cast<void**>(kGlobalSlot);   // r9 = [0x12BB4910]
    OutEntry* outRing = reinterpret_cast<OutEntry*>(&self->out_ring); // r10 = this+8
    MetaEntry* metaRing = reinterpret_cast<MetaEntry*>(&self->meta_ring); // r8 = this+0x1820

    // 0xe81d960..0xe81d9e5: loop body; runs while recomputed eax != 0
    do {
        uint32_t oldCursor = c;   // ecx at loop entry (0xe81d960)

        // 0xe81d960..0xe81d96c: edx=oldCursor; rdx=3*oldCursor; if (meta[oldCursor].flag != 1) -> end
        MetaEntry* e = &metaRing[oldCursor];
        if (e->flag != 1) {
            break;
        }
        // 0xe81d96e..0xe81d981: r14=&meta[oldCursor]; rdx=*(g+0x3C563B0); r15=e->stamp;
        //   if (r15 > *(rdx+0x30)) -> end
        void* g2 = *reinterpret_cast<void**>(reinterpret_cast<char*>(g) + 0x3C563B0);
        uint64_t limit = *reinterpret_cast<uint64_t*>(reinterpret_cast<char*>(g2) + 0x30);
        if (e->stamp > limit) {
            break;
        }
        // 0xe81d983..0xe81d992: eax=count; edx=eax-2; if (edx>=0) eax=1; eax+=oldCursor; div M -> cursor = eax % M
        {
            uint32_t t = eax;
            uint32_t td = t + 0xFFFFFFFEu;   // edx = eax - 2
            if (static_cast<int32_t>(td) >= 0) {
                t = 1u;                        // cmovns eax, r11d (1)
            }
            t += oldCursor;                    // add eax,ecx (old cursor)
            c = t % M;                         // div ebx -> remainder
            self->cursor = c;                  // mov [rsi+0x7844],edx
        }
        // 0xe81d998..0xe81d9a8: eax=meta[oldCursor].sub; rax=3*sub;
        //   --out[sub].count; out[sub].val = meta[oldCursor].val
        uint32_t sub = e->sub;                 // mov eax,[r14]
        (void)(static_cast<uint64_t>(sub) * 3ULL); // lea rax,[rax+rax*2]
        outRing[sub].count--;                  // dec [r10+rax*8+0x10]
        outRing[sub].val = e->val;             // mov [r10+rax*8+0x14],edx
        // 0xe81d9ad..0xe81d9c3: ecx=oldCursor*2; rdx=*(self->p7830); src=rdx+ecx*8 (16-byte stride);
        //   out[sub].a = src[0]; out[sub].b = src[1]
        SrcEntry* srcBase = self->p7830;
        uint32_t srcIdx = oldCursor;           // rdx+rcx*8 with rcx=oldCursor*2 -> srcBase[oldCursor]
        outRing[sub].a = srcBase[srcIdx].a;    // mov [r10+rax*8],rbx
        outRing[sub].b = srcBase[srcIdx].b;    // mov [r10+rax*8+8],rcx

        // 0xe81d9c8..0xe81d9e3: reload M,A,cursor; eax = (A-cursor) mod-adjusted
        M = self->capacity;                    // mov ebx,[rsi+0x7838]
        A = self->writeIdx;                    // mov edx,[rsi+0x783C]
        c = self->cursor;                      // mov ecx,[rsi+0x7844]  (new cursor)
        uint32_t d2 = A - c;
        eax = d2 + (static_cast<uint32_t>(static_cast<int32_t>(d2) >> 31) & M);
    } while (eax != 0);

    // 0xe81d9eb..0xe81d9f9: end: mov rcx,rdi (lock); ...; jmp sub_eec5a10
    native::sub_eec5a10(&self->lock);
}

} // namespace native::d3d12

namespace native::d3d12 {
LIFT_FN(sub_e81d850, "sub_e81d850", 0xe81d850, sub_e81d850, nullptr);
} // namespace native::d3d12