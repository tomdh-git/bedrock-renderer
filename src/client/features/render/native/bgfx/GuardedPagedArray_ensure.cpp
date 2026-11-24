// LIFT 0xbc7a7c0 size 0x1dc 1.26.62.01 GuardedPagedArray_ensure
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/GuardedPagedArray_ensure.h"

#include <cstdint>
#include <intrin.h>

namespace {

// [0x12322E58] holds the platform-memory interface object pointer (VA = imageBase + 0x12322E58).
constexpr uintptr_t kPlatformMemoryGlobal = 0x1412322E58ULL;

// CFG-thunk data slot: [0xF99FFA0] = sub_eea6040, a `jmp rax` forwarder (VA 0x14F99FFA0).
// The caller preloads rax with [g_iface + 0x28] (query) or [g_iface + 0x8] (commit), so the
// net effect of each `call qword ptr [0xF99FFA0]` is an indirect interface call through that
// preloaded entry; the slot itself only validates the indirect target.
constexpr uintptr_t kCfgThunkSlot = 0x14F99FFA0ULL;

// Fail-fast import via data slot [0xF9A8CB0] (`call qword ptr [0xF9A8CB0]` at 0xbc7a97a).
constexpr uintptr_t kFailFastSlot = 0x14F9A8CB0ULL;

inline void* platformMemory() {  // 0xbc7a858  mov rax,[0x12322E58]
    return *reinterpret_cast<void**>(kPlatformMemoryGlobal);
}

// Report block modelled on the stack frame at rbp-0x48 .. rbp+0x77 (0x78 bytes).
// sub_3afbe0 reads [report + 0x40] (result byte), [report + 0x68] and [report + 0x70]
// (the two callback pointers) [V: sub_3afbe0 disassembly].
struct EnsureReport {
    uint8_t  commitScratch[0x40];   // +0x00  commit out-scratch (opaque, written by commit)
    uint8_t  assertResult;          // +0x40  sub_3afbe0 result byte (0 = failure)
    uint8_t  pad_0x41[0x48 - 0x41];
    uint64_t assertId;              // +0x48  = 0x235B04BE0011DCAA
    const char* assertMsg;          // +0x50  = [data_f81edf7]
    uint64_t assertU64;             // +0x58  = 1
    uint32_t assertLine;            // +0x60  = 0x71
    uint32_t pad_0x64;
    void* callbackA;                // +0x68  = sub_aa6d0
    void* callbackB;                // +0x70  = sub_3afcb0
};
static_assert(offsetof(EnsureReport, commitScratch) == 0x00, "GuardedPagedArray_ensure: report commitScratch at +0x00");
static_assert(offsetof(EnsureReport, assertResult) == 0x40, "GuardedPagedArray_ensure: report assertResult at +0x40");
static_assert(offsetof(EnsureReport, assertId) == 0x48, "GuardedPagedArray_ensure: report assertId at +0x48");
static_assert(offsetof(EnsureReport, assertMsg) == 0x50, "GuardedPagedArray_ensure: report assertMsg at +0x50");
static_assert(offsetof(EnsureReport, assertU64) == 0x58, "GuardedPagedArray_ensure: report assertU64 at +0x58");
static_assert(offsetof(EnsureReport, assertLine) == 0x60, "GuardedPagedArray_ensure: report assertLine at +0x60");
static_assert(offsetof(EnsureReport, callbackA) == 0x68, "GuardedPagedArray_ensure: report callbackA at +0x68");
static_assert(offsetof(EnsureReport, callbackB) == 0x70, "GuardedPagedArray_ensure: report callbackB at +0x70");
static_assert(sizeof(EnsureReport) == 0x78, "GuardedPagedArray_ensure: report size 0x78");

// Boundary callees (docs/data/native_boundary.tsv): sub_3afbe0 = stl, sub_eec6ed0 = crt IAT thunk.
native::Boundary<uint8_t, void*, uint64_t, uint32_t, void*, void*> sub_3afbe0("sub_3afbe0");
native::Boundary<void*, void*, int, uint64_t> sub_eec6ed0("sub_eec6ed0");

#if 0
// Verbatim log of every call instruction in [0xbc7a7c0, 0xbc7a99c) (rdis dis output,
// two spaces after the address; trailing "; ..." annotations omitted):
0xbc7a80c  call 0xEEC59F0
0xbc7a867  call qword ptr [0xF99FFA0]
0xbc7a8b1  call r10
0xbc7a90e  call 0x3AFBE0
0xbc7a954  call 0xEEC6ED0
0xbc7a964  call 0xEEC5A10
0xbc7a97a  call qword ptr [0xF9A8CB0]
0xbc7a985  call 0xEEC5A00
0xbc7a996  call 0xEEC5A00
#endif
// UNRESOLVED CALL = none: every call target is either a forward-declared IAT forwarder
// (sub_eec59f0/sub_eec5a10/sub_eec5a00, hard rule 69) or a native::Boundary wrapper
// (sub_3afbe0 stl, sub_eec6ed0 crt; docs/data/native_boundary.tsv).

} // namespace

namespace native::bgfx {

void GuardedPagedArray_ensure(GuardedPagedArray* self, uint32_t idx) {
    EnsureReport report;  // rbp-0x48 stack block; fields are stored below before sub_3afbe0 reads them

    // 0xbc7a7c0..0xbc7a80c: prologue; bounds check idx < maxCount
    //   0xbc7a7df  cmp edx,[rcx+8]
    //   0xbc7a7e2  jae 0xBC7A97A
    if (idx >= self->maxCount) {
        // 0xbc7a97a  call qword ptr [0xF9A8CB0]
        reinterpret_cast<void(__fastcall*)()>(*reinterpret_cast<uintptr_t*>(kFailFastSlot))();
        // original falls through here if the slot call returns:
        // 0xbc7a980  mov ecx,5
        // 0xbc7a985  call 0xEEC5A00
        sub_eec5a00(5u);
        // 0xbc7a98a  mov dword ptr [rsi+0x74],0x7FFFFFFE
        // 0xbc7a991  mov ecx,6
        // 0xbc7a996  call 0xEEC5A00
        // 0xbc7a99b  int3
        self->commitGuard = 0x7FFFFFFEu;
        sub_eec5a00(6u);
        __debugbreak();
        __assume(false);
    }

    // 0xbc7a7e8..0xbc7a809: rsi = self; need = (uint32_t)(idx * 0x540) + 0x540
    //   0xbc7a7e8  mov rsi,rcx
    //   0xbc7a7eb  imul ebx,edx,0x540
    //   0xbc7a7f1  lea rdi,[rbx+0x540]
    uint64_t need = static_cast<uint64_t>(static_cast<uint32_t>(static_cast<uint64_t>(idx) * 0x540ULL)) + 0x540ULL;

    // 0xbc7a7f8..0xbc7a805: fast path - need <= committedBytes -> return (no lock)
    //   0xbc7a7f8  mov rax,[rcx+0x20]
    //   0xbc7a7fc  cmp rdi,rax
    //   0xbc7a7ff  jbe 0xBC7A96A
    if (need <= self->committedBytes) {
        return;  // 0xbc7a96a..0xbc7a979 epilogue
    }

    // 0xbc7a805..0xbc7a813: lock(self->lock); lock failure -> eec5a00(5), eec5a00(6), int3
    //   0xbc7a805  lea r15,[rsi+0x28]
    //   0xbc7a809  mov rcx,r15
    //   0xbc7a80c  call 0xEEC59F0
    //   0xbc7a811  test eax,eax
    //   0xbc7a813  jne 0xBC7A980
    if (sub_eec59f0(self->lock) != 0) {
        // 0xbc7a980  mov ecx,5
        // 0xbc7a985  call 0xEEC5A00
        sub_eec5a00(5u);
        // 0xbc7a98a  mov dword ptr [rsi+0x74],0x7FFFFFFE
        // 0xbc7a991  mov ecx,6
        // 0xbc7a996  call 0xEEC5A00
        // 0xbc7a99b  int3
        self->commitGuard = 0x7FFFFFFEu;
        sub_eec5a00(6u);
        __debugbreak();
        __assume(false);
    }

    // 0xbc7a819..0xbc7a820: double-commit guard
    //   0xbc7a819  cmp dword ptr [rsi+0x74],0x7FFFFFFF
    //   0xbc7a820  je 0xBC7A98A
    if (self->commitGuard == 0x7FFFFFFFu) {
        // 0xbc7a98a  mov dword ptr [rsi+0x74],0x7FFFFFFE
        // 0xbc7a991  mov ecx,6
        // 0xbc7a996  call 0xEEC5A00
        // 0xbc7a99b  int3
        self->commitGuard = 0x7FFFFFFEu;
        sub_eec5a00(6u);
        __debugbreak();
        __assume(false);
    }

    // 0xbc7a826..0xbc7a82d: re-check need <= committedBytes under the lock
    //   0xbc7a826  mov r14,[rsi+0x20]
    //   0xbc7a82a  cmp rdi,r14
    //   0xbc7a82d  jbe 0xBC7A961
    uint64_t committed = self->committedBytes;
    if (need <= committed) {
        // 0xbc7a961  mov rcx,r15   (r15 = &self->lock, reloaded at 0xbc7a93b)
        // 0xbc7a964  call 0xEEC5A10   (unlock)
        sub_eec5a10(self->lock);
        return;  // 0xbc7a969..0xbc7a979 epilogue
    }

    // 0xbc7a833..0xbc7a84a: newCommit = round64k(need); clamp to reservedBytes
    //   0xbc7a837  add ebx,0x1053F
    //   0xbc7a83d  and ebx,0xFFF0000
    //   0xbc7a843  mov rax,[rsi+0x10]
    //   0xbc7a847  cmp rax,rbx
    //   0xbc7a84a  cmovb rbx,rax
    uint32_t newCommit32 = (static_cast<uint32_t>(need) + 0x1053Fu) & 0xFFF0000u;
    uint64_t newCommit = newCommit32;
    if (self->reservedBytes < newCommit) {
        newCommit = self->reservedBytes;
    }

    // 0xbc7a84e..0xbc7a867: query(g_iface, &oldProtect) via [g_iface + 0x28] and CFG thunk [0xF99FFA0]
    //   0xbc7a84e  mov rdi,[rsi]
    //   0xbc7a851  lea rcx,[0x12322E58]
    //   0xbc7a858  mov rax,[0x12322E58]
    //   0xbc7a85f  mov rax,[rax+0x28]
    //   0xbc7a863  lea rdx,[rbp+0x3C]
    //   0xbc7a867  call qword ptr [0xF99FFA0]   ; sub_eea6040 = `jmp rax`
    //   0xbc7a86d  nop
    void* g_iface = platformMemory();
    using QueryFn = uint32_t (__fastcall*)(void*, uint32_t*);
    QueryFn query = reinterpret_cast<QueryFn>(*reinterpret_cast<uintptr_t*>(
        reinterpret_cast<uint8_t*>(g_iface) + 0x28));
    uint32_t oldProtect = 0;
    static_cast<void>(query(g_iface, &oldProtect));  // return value not observed by original

    // 0xbc7a86e..0xbc7a8b1: commit(g_iface, &report.commitScratch, oldProtect, base + committed,
    //                              newCommit - committed, 0, 2) via [g_iface + 8]
    //   0xbc7a86e  add rdi,r14
    //   0xbc7a871  mov rdx,rbx
    //   0xbc7a874  sub rdx,r14
    //   0xbc7a877  mov r8d,[rbp+0x3C]
    //   0xbc7a87b  lea rcx,[0x12322E58]
    //   0xbc7a882  mov rax,[0x12322E58]
    //   0xbc7a889  mov rax,[rax+8]
    //   0xbc7a88d  mov r10,[0xF99FFA0]
    //   0xbc7a894  mov [rsp+0x20],rdx
    //   0xbc7a899  mov dword ptr [rsp+0x30],2
    //   0xbc7a8a1  mov qword ptr [rsp+0x28],0
    //   0xbc7a8aa  lea rdx,[rbp-0x48]
    //   0xbc7a8ae  mov r9,rdi
    //   0xbc7a8b1  call r10
    //   0xbc7a8b4  nop
    void* dest = self->base + committed;
    uint64_t commitSize = newCommit - committed;
    using CommitFn = void (__fastcall*)(void*, void*, uint32_t, void*, uint64_t, uint32_t, uint32_t);
    CommitFn commit = reinterpret_cast<CommitFn>(*reinterpret_cast<uintptr_t*>(
        reinterpret_cast<uint8_t*>(g_iface) + 8));
    commit(g_iface, report.commitScratch, oldProtect, dest, commitSize, 0u, 2u);

    // 0xbc7a8b5..0xbc7a90e: build the assert report block
    //   0xbc7a8b5  mov rax,0x235B04BE0011DCAA
    //   0xbc7a8bf  mov [rbp],rax
    //   0xbc7a8c3  lea rax,[0xF81EDF7]
    //   0xbc7a8ca  mov [rbp+8],rax
    //   0xbc7a8ce  mov qword ptr [rbp+0x10],1
    //   0xbc7a8d6  mov dword ptr [rbp+0x18],0x71
    //   0xbc7a8dd  lea rax,[0xAA6D0]
    //   0xbc7a8e4  mov [rbp+0x20],rax
    //   0xbc7a8e8  lea rax,[0x3AFCB0]
    //   0xbc7a8ef  mov [rbp+0x28],rax
    //   0xbc7a8f3  mov rax,rbp
    //   0xbc7a8f6  mov [rsp+0x20],rax   ; 5th home argument = frame pointer rbp
    //   0xbc7a8fb  lea rcx,[rbp-0x48]
    //   0xbc7a8ff  lea r9,[rbp+0x20]
    //   0xbc7a903  mov edx,0x1010008
    //   0xbc7a908  mov r8d,0x2D
    //   0xbc7a90e  call 0x3AFBE0
    report.assertId = 0x235B04BE0011DCAALL;
    report.assertMsg = reinterpret_cast<const char*>(0x140F81EDF7ULL);
    report.assertU64 = 1;
    report.assertLine = 0x71u;
    report.callbackA = reinterpret_cast<void*>(0x1400AA6D0ULL);   // sub_aa6d0
    report.callbackB = reinterpret_cast<void*>(0x14003AFCB0ULL);   // sub_3afcb0
    // 0xbc7a90e  call 0x3AFBE0   (sub_3afbe0 stl boundary; writes report.assertResult at +0x40)
    sub_3afbe0(&report, 0x1010008ULL, 0x2Du, report.callbackA, &report);

    // 0xbc7a913..0xbc7a917: assert failure -> fail-fast path
    //   0xbc7a913  cmp byte ptr [rbp-8],0
    //   0xbc7a917  je short 0xBC7A97A
    if (report.assertResult == 0) {
        // 0xbc7a97a  call qword ptr [0xF9A8CB0]
        reinterpret_cast<void(__fastcall*)()>(*reinterpret_cast<uintptr_t*>(kFailFastSlot))();
        sub_eec5a00(5u);
        self->commitGuard = 0x7FFFFFFEu;
        sub_eec5a00(6u);
        __debugbreak();
        __assume(false);
    }

    // 0xbc7a919..0xbc7a93f: count = min(newCommit / 0x540, maxCount)
    //   0xbc7a919  mov edi,[rsi+8]
    //   0xbc7a91c  mov eax,ebx
    //   0xbc7a91e  shr eax,6
    //   0xbc7a921  imul rax,0xC30C30D
    //   0xbc7a928  shr rax,0x20
    //   0xbc7a92c  cmp eax,edi
    //   0xbc7a92e  cmovb edi,eax
    //   0xbc7a931  mov rcx,[rsi+0x18]
    //   0xbc7a935  mov rax,rdi
    //   0xbc7a938  sub rax,rcx
    //   0xbc7a93b  lea r15,[rsi+0x28]
    //   0xbc7a93f  je short 0xBC7A959
    uint32_t count = static_cast<uint32_t>(
        (static_cast<uint64_t>(static_cast<uint32_t>(newCommit)) >> 6) * 0x0C30C30DULL >> 32);
    if (count > self->maxCount) {
        count = self->maxCount;
    }

    // 0xbc7a941..0xbc7a954: zero newly committed records (count - zeroedCount) * 0x540 bytes
    //   0xbc7a941  imul rcx,0x540
    //   0xbc7a948  add rcx,[rsi]        ; dest = base + zeroedCount * 0x540
    //   0xbc7a94b  imul r8,rax,0x540    ; size = (count - zeroedCount) * 0x540
    //   0xbc7a952  xor edx,edx
    //   0xbc7a954  call 0xEEC6ED0       ; memset(dest, 0, size)
    if (static_cast<uint64_t>(count) != self->zeroedCount) {
        void* zeroDst = self->base + self->zeroedCount * 0x540ULL;
        uint64_t zeroBytes = (static_cast<uint64_t>(count) - self->zeroedCount) * 0x540ULL;
        sub_eec6ed0(zeroDst, 0, zeroBytes);
    }

    // 0xbc7a959..0xbc7a95d: commit the new state
    //   0xbc7a959  mov [rsi+0x18],rdi
    //   0xbc7a95d  mov [rsi+0x20],rbx
    self->zeroedCount = count;
    self->committedBytes = newCommit;

    // 0xbc7a961..0xbc7a979: unlock and epilogue
    //   0xbc7a961  mov rcx,r15   (r15 = &self->lock)
    //   0xbc7a964  call 0xEEC5A10   (unlock)
    //   0xbc7a969..0xbc7a979  add rsp,0xC8; pop rbx/rdi/rsi/r14/r15/rbp; ret
    sub_eec5a10(self->lock);
}

LIFT_FN(GuardedPagedArray_ensure, "GuardedPagedArray<0x540>::ensure", 0xbc7a7c0,
        GuardedPagedArray_ensure, nullptr);

} // namespace native::bgfx
