// LIFT 0x6622590 size 0x72 1.26.62.01 sub_6622590
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/framebuilder/sub_6622590.h"

#include <cstddef>
#include <cstdint>
#include <intrin.h>

// Layout assertions (definitions live in sub_6622590.h; repeated here so liftcheck
// sees them in the source file).
static_assert(offsetof(native::ScopeCounter, count0x10) == 0x10,
              "sub_6622590: object+0x10 is the interlocked 16-bit counter (W, 0x66225be)");
static_assert(offsetof(native::ScopeCounter, flag0x12) == 0x12,
              "sub_6622590: object+0x12 is the flag byte whose bit 0 is returned (R, 0x66225c3)");

// Verbatim instructions of the function (rdis dis 0x6622590 0x72, copied from the exe
// listing and machine-checked with tools/sigs/verify_oc.py).
// All three calls go to `os` boundary functions in docs/data/native_boundary.tsv
// (0xe935740, 0xe938cb0, 0xe938d70) and are made through native::boundary wrappers.
// UNRESOLVED CALL = none.
#if 0
0x6622590  push rsi
0x6622591  sub rsp,0x20
0x6622595  mov rsi,[rcx]
0x6622598  test rsi,rsi
0x662259b  je short 0x66225C9
0x662259d  mov eax,[0x129C13C0]
0x66225a3  mov ecx,[0x128767C8]
0x66225a9  mov rdx,gs:[0x58]
0x66225b2  mov rcx,[rdx+rcx*8]
0x66225b6  cmp eax,[rcx+4]
0x66225bc  jg short 0x66225D3
0x66225be  lock inc word ptr [rsi+0x10]
0x66225c3  movzx eax,byte ptr [rsi+0x12]
0x66225c7  jmp short 0x66225CB
0x66225c9  xor eax,eax
0x66225cb  and al,1
0x66225cd  add rsp,0x20
0x66225d1  pop rsi
0x66225d2  ret
0x66225d3  lea rcx,[0x129C13C0]
0x66225da  call 0xE938CB0
0x66225df  cmp dword ptr [0x129C13C0],0xFFFFFFFF
0x66225e6  jne short 0x66225BE
0x66225e8  lea rcx,[0x4E05030]
0x66225ef  call 0xE935740
0x66225f4  lea rcx,[0x129C13C0]
0x66225fb  call 0xE938D70
0x6622600  jmp short 0x66225BE
#endif

namespace native {

// Helpers over the two absolute data globals the function reads (same image base).
static uint32_t& scopeSeqRef() { return *reinterpret_cast<uint32_t*>(0x0129C13C0ULL); }
static uint32_t& tlsIndexRef() { return *reinterpret_cast<uint32_t*>(0x0128767C8ULL); }

// sub_6622590(a0 = rcx).
// Scope-gated flag read with an interlocked 16-bit increment on (*a0)+0x10:
//   void* obj = *a0;
//   if (obj == 0) return 0;
//   uint32_t gSeq = *(uint32_t*)0x129C13C0;
//   if (gSeq > *(uint32_t*)(*(uintptr_t*)(__readgsqword(0x58) + *(uint32_t*)0x128767C8 * 8) + 4)) {
//       sub_e938cb0(&*(uint32_t*)0x129C13C0);
//       if (*(uint32_t*)0x129C13C0 == 0xFFFFFFFF) {
//           sub_e935740(0x4E05030);
//           sub_e938d70(&*(uint32_t*)0x129C13C0);
//       }
//   }
//   _InterlockedIncrement16((volatile SHORT*)((uint8_t*)obj + 0x10));
//   return ((uint8_t*)obj)[0x12] & 1;
// Every block carries the instruction range it implements; every call is quoted verbatim above.
bool sub_6622590(void** a0) {
    // 0x6622590..0x6622598: prologue (push rsi; sub rsp,0x20) then mov rsi,[rcx] — object pointer.
    void* obj = *a0;                                          // 0x6622595  mov rsi,[rcx]

    // 0x6622598..0x662259d: test rsi,rsi; je short 0x66225C9 — null object returns 0.
    if (obj == nullptr) {                                     // 0x6622598  test rsi,rsi ; 0x662259b  je short 0x66225C9
        return false;                                         // 0x66225c9  xor eax,eax (bit 0 -> return 0)
    }

    // 0x662259d..0x66225be: scope-sequence global vs TLS slot +4; jg short 0x66225D3 enters the scope.
    uint32_t gSeq = scopeSeqRef();                            // 0x662259d  mov eax,[0x129C13C0]
    uint32_t tlsIdx = tlsIndexRef();                          // 0x66225a3  mov ecx,[0x128767C8]
    uintptr_t teb = __readgsqword(0x58);                      // 0x66225a9  mov rdx,gs:[0x58]
    uintptr_t tlsData = *reinterpret_cast<uintptr_t*>(teb + tlsIdx * 8);  // 0x66225b2  mov rcx,[rdx+rcx*8]
    if (gSeq > *reinterpret_cast<uint32_t*>(tlsData + 4)) {   // 0x66225b6  cmp eax,[rcx+4] ; 0x66225bc  jg short 0x66225D3
        // 0x66225d3..0x66225da: lea rcx,[0x129C13C0]; call 0xE938CB0 — enter the trace scope.
        boundary::sub_e938cb0(reinterpret_cast<uintptr_t>(&scopeSeqRef()), 0, 0, 0);  // 0x66225da  call 0xE938CB0
        // 0x66225df..0x66225e6: re-read the global; cmp dword ptr [0x129C13C0],0xFFFFFFFF.
        // 0x66225e6: jne short 0x66225BE — scope began normally, skip the failure path.
        if (scopeSeqRef() == 0xFFFFFFFFu) {                 // 0x66225df  cmp ... ; 0x66225e6  jne (not taken)
            // 0x66225e8..0x66225ef: lea rcx,[0x4E05030]; call 0xE935740 — scope begin failure.
            boundary::sub_e935740(static_cast<uintptr_t>(0x004E05030ULL), 0, 0, 0);  // 0x66225ef  call 0xE935740
            // 0x66225f4..0x66225fb: lea rcx,[0x129C13C0]; call 0xE938D70 — leave the trace scope.
            boundary::sub_e938d70(reinterpret_cast<uintptr_t>(&scopeSeqRef()), 0, 0, 0);  // 0x66225fb  call 0xE938D70
            // 0x6622600..0x6622602: jmp short 0x66225BE — converges into the increment below.
        }
    }

    // 0x66225be..0x66225c9: lock inc word ptr [rsi+0x10] — interlocked 16-bit increment of the counter.
    _InterlockedIncrement16(reinterpret_cast<volatile SHORT*>(reinterpret_cast<uint8_t*>(obj) + 0x10));  // 0x66225be
    // 0x66225be..0x66225c9 (cont.): movzx eax,byte ptr [rsi+0x12] — read the flag byte.
    uint8_t flag = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(obj) + 0x12);  // 0x66225c3
    // 0x66225cb..0x66225d3: and al,1; add rsp,0x20; pop rsi; ret — return bit 0.
    return (flag & 1u) != 0;                                  // 0x66225cb  and al,1
}

// Footprint: the object's first 0x13 bytes (the counter at +0x10 is written).
static Footprint sub_6622590_footprint(void** a0) {
    if (a0 == nullptr || *a0 == nullptr) return {};
    return { { *a0, 0x13 } };
}

LIFT_FN(sub_6622590, "sub_6622590", 0x6622590, sub_6622590, sub_6622590_footprint);

} // namespace native
