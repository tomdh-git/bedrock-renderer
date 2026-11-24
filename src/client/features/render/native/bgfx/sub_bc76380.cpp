// LIFT 0xbc76380 size 0x107 1.26.62.01 D3D12 submit RTX override
#include "client/features/render/native/bgfx/sub_bc76380.h"

#include <cstring>

namespace native::bgfx {

namespace {

// External calls of the original; none are in the lift set and
// docs/data/native_boundary.tsv does not exist:
//   0xbc763c5  call 0xEBCE5E0
//   0xbc763de  call 0xEBCE760
//   0xbc76411  call 0xEBCE5E0
//   0xbc76440  call 0xEBCE650
//   0xbc76448  call qword ptr [0xF9A90C8]
//   0xbc76481  call 0xE951550
// sub_ebce5e0 is strlen-like (ptr, 0x7FFFFFFF) -> u32 len: std::strlen.
// sub_ebce650 is a bounded copy (dest, 4, &record, diff with diff in 0..2): std::memcpy.
// sub_ebce760 is lifted inline as find_char_bounded below.
// sub_e951550 is noreturn: the original follows the call with int3 at 0xbc76486.

// Stack-cookie global the original reads at data_1230a0c0 ([V]): prologue stash
// (0xbc76390..0xbc7639a) and epilogue verify (0xbc76458..0xbc7646a).
extern "C" uintptr_t __security_cookie;

// sub_e951550: noreturn stack-cookie failure.
extern "C" __declspec(noreturn) void sub_e951550();

// sub_ebce760 lifted inline: bounded NUL-scan of record.ptr up to record.len,
// then first index where the byte equals ch; returns record.ptr + index or
// nullptr. Mirrors 0xebce760 exactly: same reads in the same order, no writes.
//   0xebce76b..0xebce76e  ptr == 0 -> ret 0
//   0xebce780..0xebce78e  scan for NUL within len -> n
//   0xebce790..0xebce7b2  n <= 0 -> ret 0
//   0xebce7a0..0xebce7ae  scan [ptr, ptr+n) for byte == ch -> ptr + index or ret 0
const char* find_char_bounded(const char* ptr, uint32_t len, uint8_t ch) {
    if (ptr == nullptr) {
        return nullptr;
    }
    const char* p = ptr;
    uint32_t n = 0;
    while (n < len && *p != '\0') {
        ++p;
        ++n;
    }
    if (n == 0) {
        return nullptr;
    }
    for (uint32_t i = 0; i < n; ++i) {
        if (ptr[i] == ch) {
            return ptr + i;
        }
    }
    return nullptr;
}

} // namespace

uint32_t sub_bc76380(uint64_t* slot, uint32_t ch, uint32_t flags, uint32_t /*unused*/) {
    // 0xbc76380..0xbc7639f: prologue and cookie stash
    //   0xbc76380  push r14
    //   0xbc76382  push rsi
    //   0xbc76383  push rdi
    //   0xbc76384  push rbp
    //   0xbc76385  push rbx
    //   0xbc76386  sub rsp,0x40
    //   0xbc7638a  mov edi,r8d
    //   0xbc7638d  mov rsi,rcx
    //   0xbc76390  mov rax,[0x1230A0C0]
    //   0xbc76397  xor rax,rsp
    //   0xbc7639a  mov [rsp+0x38],rax
    //   0xbc7639f  mov rbx,[rcx]
    uintptr_t cookie_slot = __security_cookie ^ reinterpret_cast<uintptr_t>(&cookie_slot);
    const uint64_t cursor = *slot;

    // 0xbc763a2..0xbc763d4: record = {0xF847A07, 0}; if cursor != 0:
    //   0xbc763a2  lea r14,[0xF847A07]
    //   0xbc763a9  mov [rsp+0x20],r14
    //   0xbc763ae  mov dword ptr [rsp+0x28],0
    //   0xbc763b6  test rbx,rbx
    //   0xbc763b9  je short 0xBC763D9
    //   0xbc763bb  mov rcx,rbx
    //   0xbc763be  mov ebp,edx
    //   0xbc763c0  mov edx,0x7FFFFFFF
    //   0xbc763c5  call 0xEBCE5E0
    //   0xbc763ca  mov edx,ebp
    //   0xbc763cc  test eax,eax
    //   0xbc763ce  je short 0xBC763D9
    //   0xbc763d0  mov [rsp+0x28],eax
    //   0xbc763d4  mov [rsp+0x20],rbx
    Bc76380Record record{reinterpret_cast<char*>(kBc76380DefaultPtr), 0};
    if (cursor != 0) {
        const uint32_t len1 = static_cast<uint32_t>(std::strlen(reinterpret_cast<const char*>(cursor)));
        if (len1 != 0) {
            record.ptr = reinterpret_cast<char*>(cursor);
            record.len = len1;
        }
    }

    // 0xbc763d9..0xbc763f2: found = find_char_bounded(&record, (uint8_t)ch);
    //   0xbc763d9  lea rcx,[rsp+0x20]
    //   0xbc763de  call 0xEBCE760
    //   0xbc763e3  test rax,rax
    //   0xbc763e6  je short 0xBC76458
    //   0xbc763e8  mov rbx,[rsi]
    //   0xbc763eb  sub rax,rbx
    //   0xbc763ee  cmp rax,2
    //   0xbc763f2  jg short 0xBC76458
    const char* const found = find_char_bounded(record.ptr, record.len, static_cast<uint8_t>(ch));
    int64_t diff = 0;
    bool accepted = false;
    if (found != nullptr) {
        diff = static_cast<int64_t>(found - reinterpret_cast<const char*>(cursor));
        if (diff <= static_cast<int64_t>(kBc76380MaxDiff)) {
            accepted = true;
        }
    }

    if (accepted) {
        // 0xbc763f4..0xbc76428: record = {0xF847A07, 0}; if cursor != 0:
        //   0xbc763f4  mov [rsp+0x20],r14
        //   0xbc763f9  mov dword ptr [rsp+0x28],0
        //   0xbc76401  test rbx,rbx
        //   0xbc76404  je short 0xBC76428
        //   0xbc76406  mov rcx,rbx
        //   0xbc76409  mov edx,0x7FFFFFFF
        //   0xbc7640e  mov rdi,rax
        //   0xbc76411  call 0xEBCE5E0
        //   0xbc76416  mov ecx,eax
        //   0xbc76418  mov rax,rdi
        //   0xbc7641b  test ecx,ecx
        //   0xbc7641d  je short 0xBC76428
        //   0xbc7641f  mov [rsp+0x28],ecx
        //   0xbc76423  mov [rsp+0x20],rbx
        record = Bc76380Record{reinterpret_cast<char*>(kBc76380DefaultPtr), 0};
        if (cursor != 0) {
            const uint32_t len2 = static_cast<uint32_t>(std::strlen(reinterpret_cast<const char*>(cursor)));
            if (len2 != 0) {
                record.ptr = reinterpret_cast<char*>(cursor);
                record.len = len2;
            }
        }

        // 0xbc76428..0xbc7644e: dest[4] = first diff bytes of record; flags = indirect(dest); slot += diff + 1
        //   0xbc76428  lea rdi,[rsp+0x34]
        //   0xbc7642d  lea r8,[rsp+0x20]
        //   0xbc76432  mov rcx,rdi
        //   0xbc76435  mov edx,4
        //   0xbc7643a  mov r9d,eax
        //   0xbc7643d  mov rbx,rax
        //   0xbc76440  call 0xEBCE650
        //   0xbc76445  mov rcx,rdi
        //   0xbc76448  call qword ptr [0xF9A90C8]
        //   0xbc7644e  mov edi,eax
        //   0xbc76450  inc ebx
        //   0xbc76452  movsxd rax,ebx
        //   0xbc76455  add [rsi],rax
        char dest[4];
        std::memcpy(dest, &record, static_cast<size_t>(diff));
        using IndirectFn = uint32_t (*)(char*);
        const IndirectFn indirect = reinterpret_cast<IndirectFn>(
            *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A90C8));
        flags = static_cast<uint32_t>(indirect(dest));
        *slot += static_cast<int64_t>(static_cast<uint32_t>(diff) + 1u);
    }

    // 0xbc76458..0xbc76486: cookie verify and return flags (all paths)
    //   0xbc76458  mov rax,[rsp+0x38]
    //   0xbc7645d  xor rax,rsp
    //   0xbc76460  mov rcx,[0x1230A0C0]
    //   0xbc76467  cmp rcx,rax
    //   0xbc7646a  jne short 0xBC76479
    //   0xbc7646c  mov eax,edi
    //   0xbc7646e  add rsp,0x40
    //   0xbc76472  pop rbx
    //   0xbc76473  pop rbp
    //   0xbc76474  pop rdi
    //   0xbc76475  pop rsi
    //   0xbc76476  pop r14
    //   0xbc76478  ret
    // failure:
    //   0xbc76479  mov rcx,[rsp+0x38]
    //   0xbc7647e  xor rcx,rsp
    //   0xbc76481  call 0xE951550
    //   0xbc76486  int3
    if ((__security_cookie ^ reinterpret_cast<uintptr_t>(&cookie_slot)) != cookie_slot) {
        sub_e951550();
        __assume(false);
    }
    return flags;
}

static_assert(offsetof(Bc76380Record, ptr) == 0x00, "bc76380: record pointer offset");

LIFT_FN(sub_bc76380, "D3D12 submit RTX override", 0xbc76380, sub_bc76380, nullptr);

} // namespace native::bgfx
