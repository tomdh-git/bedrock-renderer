// LIFT 0x19bbc0 size 0xce 1.26.62.01 sub_19bbc0
#include "sub_19bbc0.h"

#include "client/features/render/native/Lift.h"

static_assert(sizeof(void*) == 8, "sub_19bbc0: x64 ABI contract, pointer-sized address space");

namespace native {

// sub_19bbc0 (0x19bbc0, size 0xce, 1.26.62.01).
//
// Releases two refcounted string members and resets them to SSO state.
//
//   a0+0x40  proceed flag (must == 1, else return immediately)
//   a0+0x20  string 1 data pointer   a0+0x38  string 1 size   a0+0x30  string 1 cap
//   a0+0x00  string 2 data pointer   a0+0x18  string 2 size   a0+0x10  string 2 cap
//
// Each member: if size >= 0x10 (heap), release via sub_e935700 (argument = data pointer
// when size+1 < 0x1000, else argument = [data-8] refcount unless the data-8-refcount
// computation lands >= 0x20, which takes the slow path through data slot 0xF9A8C78 and
// does not return). Then reset: cap=0, size=0xF, data=nullptr.
//
// Verbatim instructions of the function (matches rdis dis 0x19bbc0 0xce):
#if 0
0x19bbc0  push rsi
0x19bbc1  sub rsp,0x30
0x19bbc5  cmp byte ptr [rcx+0x40],1
0x19bbc9  jne 0x19BC6E
0x19bbcf  mov rsi,rcx
0x19bbd2  mov rax,[rcx+0x38]
0x19bbd6  cmp rax,0x10
0x19bbda  jb short 0x19BC0D
0x19bbdc  mov rcx,[rsi+0x20]
0x19bbe0  lea rdx,[rax+1]
0x19bbe4  cmp rdx,0x1000
0x19bbeb  jb short 0x19BC08
0x19bbed  mov r8,[rcx-8]
0x19bbf1 add rcx,0xFFFFFFFFFFFFFFF8
0x19bbf5 sub rcx,r8
0x19bbf8 cmp rcx,0x20
0x19bbfc jae short 0x19BC74
0x19bbfe add rax,0x28
0x19bc02 mov rdx,rax
0x19bc05 mov rcx,r8
0x19bc08 call 0xE935700
0x19bc0d mov qword ptr [rsi+0x30],0
0x19bc15 mov qword ptr [rsi+0x38],0xF
0x19bc1d mov byte ptr [rsi+0x20],0
0x19bc21 mov rax,[rsi+0x18]
0x19bc25 cmp rax,0x10
0x19bc29 jb short 0x19BC5B
0x19bc2b mov rcx,[rsi]
0x19bc2e lea rdx,[rax+1]
0x19bc32 cmp rdx,0x1000
0x19bc39 jb short 0x19BC56
0x19bc3b mov r8,[rcx-8]
0x19bc3f add rcx,0xFFFFFFFFFFFFFFF8
0x19bc43 sub rcx,r8
0x19bc46 cmp rcx,0x20
0x19bc4a jae short 0x19BC74
0x19bc4c add rax,0x28
0x19bc50 mov rdx,rax
0x19bc53 mov rcx,r8
0x19bc56 call 0xE935700
0x19bc5b mov qword ptr [rsi+0x10],0
0x19bc63 mov qword ptr [rsi+0x18],0xF
0x19bc6b mov byte ptr [rsi],0
0x19bc6e add rsp,0x30
0x19bc72 pop rsi
0x19bc73 ret
0x19bc74 mov qword ptr [rsp+0x20],0
0x19bc7d xor ecx,ecx
0x19bc7f xor edx,edx
0x19bc81 xor r8d,r8d
0x19bc84 xor r9d,r9d
0x19bc87 call qword ptr [0xF9A8C78]
0x19bc8d int3
0x19bc8e int3
#endif

void sub_19bbc0(void* a0)
{
    // 0x19bbc5  cmp byte ptr [rcx+0x40],1
    // 0x19bbc9  jne 0x19BC6E          (skip everything when the proceed flag is not 1)
    if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kFlagOffset) != 1) {
        return;   // 0x19bbc9  jne 0x19BC6E  -> 0x19bc6e  add rsp,0x30; pop rsi; ret
    }

    // 0x19bbcf  mov rsi,rcx           (rsi = a0, base for all member accesses below)

    // ---------------- String 1 (a0+0x20 data, a0+0x38 size, a0+0x30 cap) ----------------
    // 0x19bbd2  mov rax,[rcx+0x38]    (size1)
    // 0x19bbd6  cmp rax,0x10
    // 0x19bbda  jb short 0x19BC0D     (SSO path: size1 < 0x10, skip the release call)
    uint64_t size1 = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString1SizeOffset);
    if (size1 >= 0x10) {
        // 0x19bbdc  mov rcx,[rsi+0x20]   (data1)
        void* data1 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString1DataOffset);

        // 0x19bbe0  lea rdx,[rax+1]      (size1 + 1)
        // 0x19bbe4  cmp rdx,0x1000
        // 0x19bbeb  jb short 0x19BC08    (size1 + 1 < 0x1000 -> direct release call)
        if (size1 + 1 < 0x1000) {
            // loc_19bc08:
            // 0x19bc08  call 0xE935700     sub_e935700(data1)
            sub_e935700(data1);   // 0x19bc08  call 0xE935700
        } else {
            // 0x19bbed  mov r8,[rcx-8]          (refcount1 = [data1-8])
            uint64_t refcount1 = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(data1) - 8);

            // 0x19bbf1  add rcx,0xFFFFFFFFFFFFFFF8   (rcx = data1 - 8)
            // 0x19bbf5  sub rcx,r8                   (rcx = data1 - 8 - refcount1)
            uint64_t rcx = reinterpret_cast<uint64_t>(data1) - 8 - refcount1;

            // 0x19bbf8  cmp rcx,0x20
            // 0x19bbfc  jae short 0x19BC74         (rcx >= 0x20 -> slow path via data slot)
            if (rcx >= 0x20) {
                // loc_19bc74:
                // 0x19bc74  mov qword ptr [rsp+0x20],0
                // 0x19bc7d  xor ecx,ecx
                // 0x19bc7f  xor edx,edx
                // 0x19bc81  xor r8d,r8d
                // 0x19bc84  xor r9d,r9d
                // 0x19bc87  call qword ptr [0xF9A8C78]   (indirect call through data slot 0xF9A8C78; all args zeroed)
                // 0x19bc8d  int3                         (noreturn)
                auto fn = reinterpret_cast<void(*)()>(*reinterpret_cast<void**>(0xF9A8C78ULL));
                fn();   // 0x19bc87  call qword ptr [0xF9A8C78]
                __assume(false);   // 0x19bc8d  int3  (noreturn)
            } else {
                // 0x19bbfe  add rax,0x28        (rdx = size1 + 0x28)
                // 0x19bc02  mov rdx,rax
                // 0x19bc05  mov rcx,r8         (rcx = refcount1)
                // loc_19bc08:
                // 0x19bc08  call 0xE935700     sub_e935700(refcount1)
                sub_e935700(reinterpret_cast<void*>(refcount1));   // 0x19bc08  call 0xE935700
            }
        }

        // loc_19bc0d:
        // 0x19bc0d  mov qword ptr [rsi+0x30],0   (cap1 = 0)
        // 0x19bc15  mov qword ptr [rsi+0x38],0xF (size1 = 0xF)
        // 0x19bc1d  mov byte ptr [rsi+0x20],0    (data1 = nullptr)
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString1CapOffset) = 0;
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString1SizeOffset) = 0xF;
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString1DataOffset) = nullptr;
    } else {
        // loc_19bc0d:
        // 0x19bc0d  mov qword ptr [rsi+0x30],0   (cap1 = 0)
        // 0x19bc15  mov qword ptr [rsi+0x38],0xF (size1 = 0xF)
        // 0x19bc1d  mov byte ptr [rsi+0x20],0    (data1 = nullptr)
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString1CapOffset) = 0;
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString1SizeOffset) = 0xF;
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString1DataOffset) = nullptr;
    }

    // ---------------- String 2 (a0+0x00 data, a0+0x18 size, a0+0x10 cap) ----------------
    // 0x19bc21  mov rax,[rsi+0x18]    (size2)
    // 0x19bc25  cmp rax,0x10
    // 0x19bc29  jb short 0x19BC5B     (SSO path: size2 < 0x10, skip the release call)
    uint64_t size2 = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString2SizeOffset);
    if (size2 >= 0x10) {
        // 0x19bc2b  mov rcx,[rsi]     (data2)
        void* data2 = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString2DataOffset);

        // 0x19bc2e  lea rdx,[rax+1]      (size2 + 1)
        // 0x19bc32  cmp rdx,0x1000
        // 0x19bc39  jb short 0x19BC56    (size2 + 1 < 0x1000 -> direct release call)
        if (size2 + 1 < 0x1000) {
            // loc_19bc56:
            // 0x19bc56  call 0xE935700   sub_e935700(data2)
            sub_e935700(data2);   // 0x19bc56  call 0xE935700
        } else {
            // 0x19bc3b  mov r8,[rcx-8]          (refcount2 = [data2-8])
            uint64_t refcount2 = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(data2) - 8);

            // 0x19bc3f  add rcx,0xFFFFFFFFFFFFFFF8   (rcx = data2 - 8)
            // 0x19bc43  sub rcx,r8                   (rcx = data2 - 8 - refcount2)
            uint64_t rcx = reinterpret_cast<uint64_t>(data2) - 8 - refcount2;

            // 0x19bc46  cmp rcx,0x20
            // 0x19bc4a  jae short 0x19BC74         (rcx >= 0x20 -> slow path via data slot)
            if (rcx >= 0x20) {
                // loc_19bc74: (shared slow path)
                auto fn = reinterpret_cast<void(*)()>(*reinterpret_cast<void**>(0xF9A8C78ULL));
                fn();   // 0x19bc87  call qword ptr [0xF9A8C78]
                __assume(false);   // 0x19bc8d  int3  (noreturn)
            } else {
                // loc_19bc56:
                // 0x19bc56  call 0xE935700   sub_e935700(refcount2)
                sub_e935700(reinterpret_cast<void*>(refcount2));   // 0x19bc56  call 0xE935700
            }
        }

        // loc_19bc5b:
        // 0x19bc5b  mov qword ptr [rsi+0x10],0   (cap2 = 0)
        // 0x19bc63  mov qword ptr [rsi+0x18],0xF (size2 = 0xF)
        // 0x19bc6b  mov byte ptr [rsi],0         (data2 = nullptr)
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString2CapOffset) = 0;
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString2SizeOffset) = 0xF;
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString2DataOffset) = nullptr;
    } else {
        // loc_19bc5b:
        // 0x19bc5b  mov qword ptr [rsi+0x10],0   (cap2 = 0)
        // 0x19bc63  mov qword ptr [rsi+0x18],0xF (size2 = 0xF)
        // 0x19bc6b  mov byte ptr [rsi],0         (data2 = nullptr)
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString2CapOffset) = 0;
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString2SizeOffset) = 0xF;
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(a0) + sub_19bbc0Layout::kString2DataOffset) = nullptr;
    }

    // 0x19bc6e  add rsp,0x30
    // 0x19bc72  pop rsi
    // 0x19bc73  ret
}

} // namespace native

LIFT_FN(sub_19bbc0, "sub_19bbc0", 0x19BBC0, native::sub_19bbc0, nullptr);
