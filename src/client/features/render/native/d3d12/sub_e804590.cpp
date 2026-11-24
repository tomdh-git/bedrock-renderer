// LIFT 0xe804590 size 0x2a6 1.26.62.01 sub_e804590
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e804590.h"

#include <cstdint>
#include <intrin.h>

static_assert(sizeof(void*) == 8, "e804590: x64 target");

namespace native {

namespace boundary {
    // 0xE951550: __security_check_cookie (crt boundary, noreturn on failure) [V],
    // docs/data/native_boundary.tsv row 0xe951550 = crt. Called on /GS mismatch.
    native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");
} // namespace boundary

namespace {

inline std::uint32_t mul32(std::uint32_t a, std::uint32_t b) {
    return static_cast<std::uint32_t>(static_cast<std::uint64_t>(a) *
                                      static_cast<std::uint64_t>(b));
}

// ideal bucket for a stored hash: imul 0x5EBCA77 ; shr 0x13 ; imul 0x1B1 ; and 0x3FF  [V]
inline std::uint32_t idealBucket(std::uint32_t h) {
    std::uint32_t v = mul32(h, kIdealMul1);
    v >>= 19;
    v = mul32(v, kIdealMul2);
    v &= 0x3FFu;
    return v;
}

} // namespace

extern "C" std::uint16_t* sub_e804590(void* rcx, std::uint32_t edx, const char* r8) {
    // 0xe804590..0xe8045a9  prologue + /GS cookie store
    std::uintptr_t cookieSlot = 0;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<const std::uintptr_t*>(kGblCookie) ^
        reinterpret_cast<std::uintptr_t>(&cookieSlot);
    char* const rsi = static_cast<char*>(rcx);   // mov rsi,rcx  (self / map object)
    const std::uint32_t edi = edx;               // mov edi,edx
    const std::uint16_t di = static_cast<std::uint16_t>(edi);
    const char* const str = r8;                  // input string (rbx)

    // 0xe8045ae..0xe8045d3  select input string + length
    const char* rdx;
    std::uint32_t r8d;
    if (str != nullptr) {                        // test r8,r8 ; je e8045d5
        std::uint32_t eax = sub_ebce5e0(str, 0x7FFFFFFFu);  // call 0xEBCE5E0  (rcx=r8, edx=0x7FFFFFFF)
        r8d = eax;                               // mov r8d,eax
        rdx = (eax != 0u) ? str                  // cmovne rdx,rbx  (len!=0 -> use str)
                     : reinterpret_cast<const char*>(kDefaultString);
    } else {
        rdx = reinterpret_cast<const char*>(kDefaultString); // lea rdx,[0xF847A07]
        r8d = 0u;                                // xor r8d,r8d
    }

    // 0xe8045df..0xe8045ec  zero Murmur state (16 bytes) then call bx::HashMurmur2A::add
    std::uint32_t state[4] = {0u, 0u, 0u, 0u};   // xorps xmm0 ; movaps [rsp+0x20],xmm0
    // state[0]=m_hash +0x00, state[1]=m_tail +0x04, state[2]=m_nbytesInTail +0x08, state[3]=m_nbytes +0x0C
    sub_bc76610(state, rdx, r8d);                // call 0xBC76610  (rcx=&state, rdx=data, r8d=len)

    // 0xe8045f1..0xe804650  Murmur finalize -> eax=hashVal, ecx=bucket
    std::uint32_t eax = mul32(state[1], kMurmurMul);   // imul eax,[rsp+0x24],M   (m_tail*M)
    std::uint32_t ecx = eax;
    ecx >>= 24;                                        // shr ecx,0x18
    ecx ^= eax;                                        // xor ecx,eax
    eax = mul32(ecx, kMurmurMul);                      // imul eax,ecx,M
    ecx = mul32(state[0], kMurmurMul);                 // imul ecx,[rsp+0x20],M   (m_hash*M)
    std::uint32_t edx32 = mul32(state[3], kMurmurMul); // imul edx,[rsp+0x2C],M   (m_nbytes*M)
    ecx ^= eax;                                        // xor ecx,eax
    eax = edx32;                                       // mov eax,edx
    eax >>= 24;                                        // shr eax,0x18
    eax ^= edx32;                                      // xor eax,edx
    eax = mul32(eax, kMurmurMul);                      // imul eax,M
    ecx = mul32(ecx, kMurmurMul);                      // imul ecx,M
    ecx ^= eax;                                        // xor ecx,eax
    eax = ecx;                                         // mov eax,ecx
    eax >>= 13;                                        // shr eax,0xD
    eax ^= ecx;                                        // xor eax,ecx
    ecx = mul32(eax, kMurmurMul);                      // imul ecx,eax,M
    eax = ecx;                                         // mov eax,ecx
    eax >>= 15;                                        // shr eax,0xF
    eax ^= ecx;                                        // xor eax,ecx
    ecx = mul32(eax, kIdealMul1);                      // imul ecx,eax,0x5EBCA77
    ecx >>= 19;                                        // shr ecx,0x13
    ecx = mul32(ecx, kIdealMul2);                      // imul ecx,0x1B1
    ecx &= 0x3FFu;                                     // and ecx,0x3FF  -> bucket
    const std::uint32_t hashVal = eax;                 // full hash compared against stored hashes
    const std::uint32_t bucket = ecx;                  // initial probe bucket

    // 0xe804656  rdx = bitmap base (self+0x1008); 0xe80465d r9d = bucket
    std::uint32_t* const hashes = reinterpret_cast<std::uint32_t*>(rsi + kObjHashes);   // +0x08
    std::uint16_t* const bitmap = reinterpret_cast<std::uint16_t*>(rsi + kObjBitmap);   // +0x1008
    std::uint32_t& countRef = *reinterpret_cast<std::uint32_t*>(rsi + kObjCount);       // +0x04
    std::uint16_t* const slots = reinterpret_cast<std::uint16_t*>(rsi + kObjSlots);     // +0x1808

    std::uintptr_t r11 = 0;
    std::uint32_t r9d = bucket;
    std::uint32_t r8d = 0;
    std::uint32_t r10d = 0;
    std::uint32_t ebx = 0, ebp = 0, r14d = 0;
    std::uint32_t savedR8d = 0;

L_probe:  // 0xe804660  mov r9d,r9d
    if (bitmap[r9d] == kEmptyBitmap) goto L_notfound;                    // 0xe804663  cmp word ptr [rdx+r9*2],0xFFFF ; je e8047ad
    if (hashes[r9d] == hashVal) goto L_found;                            // 0xe80466f  cmp [rsi+r9*4+8],eax ; je e80468a
    r9d = (r9d + 1u) & kBucketMask;                                      // 0xe804676  inc r9d ; 0xe804679  and r9d,0x3FF
    if (r9d != bucket) goto L_probe;                                     // 0xe804680  cmp r9d,ecx ; jne e804660
    goto L_notfound;                                                     // 0xe804685  jmp e8047ad (table full)

L_notfound:  // 0xe8047ad  cmp di,0xFFFF
    if (di == kNoHandle) goto L_writeturn;                               // 0xe8047b1  je short e8047f4
    r8d = bucket;                                                        // 0xe8047b3  mov r8d,ecx
L_insert_probe:  // 0xe8047c0
    if (bitmap[r8d] == kEmptyBitmap) goto L_insert;                      // 0xe8047c3  cmp word ptr [rdx+r8*2],0xFFFF ; je e8047e3
    if (hashes[r8d] == hashVal) goto L_writeturn;                        // 0xe8047cb  cmp [rsi+r8*4+8],eax ; je e8047f4 (match)
    r8d = (r8d + 1u) & kBucketMask;                                      // 0xe8047d2  inc r8d ; 0xe8047d5  and r8d,0x3FF
    if (r8d != bucket) goto L_insert_probe;                              // 0xe8047dc  cmp r8d,ecx ; jne e8047c0
    goto L_writeturn;                                                    // 0xe8047e1  jmp e8047f4 (table full)
L_insert:  // 0xe8047e3
    hashes[r8d] = hashVal;                                               // 0xe8047e3  mov [rsi+r8*4+8],eax
    bitmap[r8d] = static_cast<std::uint16_t>(di);                        // 0xe8047e8  mov [rsi+r8*2+0x1008],di
    countRef += 1u;                                                      // 0xe8047f1  inc dword ptr [rsi+4]
    goto L_writeturn;

L_found:  // 0xe80468a
    bitmap[r9d] = kEmptyBitmap;                                          // 0xe80468a  mov word ptr [rsi+r9*2+0x1008],0xFFFF
    savedR8d = countRef;                                                 // 0xe804695  mov r8d,[rsi+4]
    savedR8d -= 1u;                                                      // 0xe804699  dec r8d
    countRef = savedR8d;                                                 // 0xe80469c  mov [rsi+4],r8d
    r9d = (r9d + 1u) & kBucketMask;                                      // 0xe8046a0  inc r9d ; 0xe8046a3  and r9d,0x3FF
    r11 = reinterpret_cast<std::uintptr_t>(bitmap + r9d);                // 0xe8046aa  lea r11d,[r9+r9] ; 0xe8046c2  add r11,rdx
    r10d = bitmap[r9d];                                                  // 0xe8046ae  movzx r10d,word ptr [rsi+r11+0x1008]
    if (r10d == kEmptyBitmap) goto L_notfound;                           // 0xe8046b7  cmp r10w,0xFFFF ; je e8047ad
    goto L_shift;                                                        // 0xe8046c5  jmp e804700

L_shift:  // 0xe804700
    ebx = hashes[r9d];                                                   // 0xe804700  mov ebx,[rsi+r9*4+8]
    ebp = idealBucket(ebx);                                              // 0xe804705  imul ebp,ebx,0x5EBCA77 ; shr 0x13 ; imul 0x1B1 ; and 0x3FF
    r14d = ebp;                                                          // 0xe80471a  mov r14d,ebp
L_shift_probe:  // 0xe804720
    if (bitmap[r14d] == kEmptyBitmap) goto L_place;                      // 0xe804723  cmp word ptr [rdx+r14*2],0xFFFF ; je short e804760
    if (hashes[r14d] == ebx) goto L_same;                                // 0xe80472b  cmp [rsi+r14*4+8],ebx ; je short e804750
    r14d = (r14d + 1u) & kBucketMask;                                    // 0xe804732  inc r14d ; 0xe804735  and r14d,0x3FF
    if (r14d != ebp) goto L_shift_probe;                                 // 0xe80473c  cmp r14d,ebp ; jne e804720
    goto L_place;                                                        // 0xe804741  jmp e804760 (full cycle)
L_same:  // 0xe804750
    if (r9d == r14d) goto L_aftershift;                                  // 0xe804750  cmp r9d,r14d ; je short e8046e2
    goto L_place;                                                        // 0xe804755  nop ; fall into e804760
L_place:  // 0xe804760
    *reinterpret_cast<std::uint16_t*>(r11) = kEmptyBitmap;               // 0xe804760  mov word ptr [r11],0xFFFF
    countRef = savedR8d - 1u;                                            // 0xe804766  lea r11d,[r8-1] ; 0xe80476a  mov [rsi+4],r11d
    r14d = ebp;                                                          // 0xe80476e  mov r14d,ebp
    goto L_shift_probe2;                                                 // fall into 0xe804780
L_shift_probe2:  // 0xe804780
    if (bitmap[r14d] == kEmptyBitmap) goto L_move;                       // 0xe804783  cmp word ptr [rdx+r14*2],0xFFFF ; je e8046d0
    if (hashes[r14d] == ebx) goto L_done;                                // 0xe80478f  cmp [rsi+r14*4+8],ebx ; je short e8047a5
    r14d = (r14d + 1u) & kBucketMask;                                    // 0xe804796  inc r14d ; 0xe804799  and r14d,0x3FF
    if (r14d != ebp) goto L_shift_probe2;                                // 0xe8047a0  cmp r14d,ebp ; jne e804780
    goto L_done;
L_done:  // 0xe8047a5
    savedR8d = savedR8d - 1u;                                            // 0xe8047a5  mov r8d,r11d (r11d = savedR8d-1)
    goto L_aftershift;                                                   // 0xe8047a8  jmp e8046e2
L_move:  // 0xe8046d0
    hashes[r14d] = ebx;                                                  // 0xe8046d0  mov [rsi+r14*4+8],ebx
    bitmap[r14d] = static_cast<std::uint16_t>(r10d);                     // 0xe8046d5  mov [rsi+r14*2+0x1008],r10w
    countRef = savedR8d;                                                 // 0xe8046de  mov [rsi+4],r8d
L_aftershift:  // 0xe8046e2
    r9d = (r9d + 1u) & kBucketMask;                                      // 0xe8046e2  inc r9d ; 0xe8046e5  and r9d,0x3FF
    r11 = reinterpret_cast<std::uintptr_t>(bitmap + r9d);                // 0xe8046ec  lea r11,[rdx+r9*2]
    r10d = bitmap[r9d];                                                  // 0xe8046f0  movzx r10d,word ptr [rdx+r9*2]
    if (r10d == kEmptyBitmap) goto L_notfound;                           // 0xe8046f5  cmp r10w,0xFFFF ; je e8047ad
    goto L_shift;                                                        // 0xe804700 (loop)

L_writeturn:  // 0xe8047f4
    slots[di] = static_cast<std::uint16_t>(di);                          // 0xe8047f4  movzx eax,di ; 0xe8047f7  mov [rsi+rax*2+0x1808],di

    // 0xe8047ff..0xe804827  /GS cookie check + epilogue + return
    if (*reinterpret_cast<const std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {  // 0xe8047ff  mov rcx,[rsp+0x38] ; xor rcx,rsp ; 0xe804807  mov rdx,[0x1230A0C0] ; cmp
        boundary::sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));  // 0xe804830  call 0xE951550 (noreturn)
        __assume(false);                                                 // 0xe804835  int3 (unreachable)
    }
    return slots + di;                                                   // 0xe804813  lea rax,[rsi+rax*2] ; 0xe804817  add rax,0x1808
}

// Verbatim disassembly of [0xe804590, 0xe804836) (rdis dis output; two spaces after each address):
#if 0
0xe804590  push r14
0xe804592  push rsi
0xe804593  push rdi
0xe804594  push rbp
0xe804595  push rbx
0xe804596  sub rsp,0x40
0xe80459a  mov edi,edx
0xe80459c  mov rsi,rcx
0xe80459f  mov rax,[0x1230A0C0]
0xe8045a6  xor rax,rsp
0xe8045a9  mov [rsp+0x38],rax
0xe8045ae  test r8,r8
0xe8045b1  je short 0xE8045D5
0xe8045b3  mov rcx,r8
0xe8045b6  mov edx,0x7FFFFFFF
0xe8045bb  mov rbx,r8
0xe8045be  call 0xEBCE5E0
0xe8045c3  mov r8d,eax
0xe8045c6  test eax,eax
0xe8045c8  lea rdx,[0xF847A07]
0xe8045cf  cmovne rdx,rbx
0xe8045d3  jmp short 0xE8045DF
0xe8045d5  lea rdx,[0xF847A07]
0xe8045dc  xor r8d,r8d
0xe8045df  xorps xmm0,xmm0
0xe8045e2  movaps [rsp+0x20],xmm0
0xe8045e7  lea rcx,[rsp+0x20]
0xe8045ec  call 0xBC76610
0xe8045f1  imul eax,[rsp+0x24],0x5BD1E995
0xe8045f9  mov ecx,eax
0xe8045fb  shr ecx,0x18
0xe8045fe  xor ecx,eax
0xe804600  imul eax,ecx,0x5BD1E995
0xe804606  imul ecx,[rsp+0x20],0x5BD1E995
0xe80460e  imul edx,[rsp+0x2C],0x5BD1E995
0xe804616  xor ecx,eax
0xe804618  mov eax,edx
0xe80461a  shr eax,0x18
0xe80461d  xor eax,edx
0xe80461f  imul eax,0x5BD1E995
0xe804625  imul ecx,0x5BD1E995
0xe80462b  xor ecx,eax
0xe80462d  mov eax,ecx
0xe80462f  shr eax,0xD
0xe804632  xor eax,ecx
0xe804634  imul ecx,eax,0x5BD1E995
0xe80463a  mov eax,ecx
0xe80463c  shr eax,0xF
0xe80463f  xor eax,ecx
0xe804641  imul ecx,eax,0x5EBCA77
0xe804647  shr ecx,0x13
0xe80464a  imul ecx,0x1B1
0xe804650  and ecx,0x3FF
0xe804656  lea rdx,[rsi+0x1008]
0xe80465d  mov r9d,ecx
0xe804660  mov r9d,r9d
0xe804663  cmp word ptr [rdx+r9*2],0xFFFF
0xe804669  je 0xE8047AD
0xe80466f  cmp [rsi+r9*4+8],eax
0xe804674  je short 0xE80468A
0xe804676  inc r9d
0xe804679  and r9d,0x3FF
0xe804680  cmp r9d,ecx
0xe804683  jne short 0xE804660
0xe804685  jmp 0xE8047AD
0xe80468a  mov word ptr [rsi+r9*2+0x1008],0xFFFF
0xe804695  mov r8d,[rsi+4]
0xe804699  dec r8d
0xe80469c  mov [rsi+4],r8d
0xe8046a0  inc r9d
0xe8046a3  and r9d,0x3FF
0xe8046aa  lea r11d,[r9+r9]
0xe8046ae  movzx r10d,word ptr [rsi+r11+0x1008]
0xe8046b7  cmp r10w,0xFFFF
0xe8046bc  je 0xE8047AD
0xe8046c2  add r11,rdx
0xe8046c5  jmp short 0xE804700
0xe8046c7  nop [rax+rax]
0xe8046d0  mov [rsi+r14*4+8],ebx
0xe8046d5  mov [rsi+r14*2+0x1008],r10w
0xe8046de  mov [rsi+4],r8d
0xe8046e2  inc r9d
0xe8046e5  and r9d,0x3FF
0xe8046ec  lea r11,[rdx+r9*2]
0xe8046f0  movzx r10d,word ptr [rdx+r9*2]
0xe8046f5  cmp r10w,0xFFFF
0xe8046fa  je 0xE8047AD
0xe804700  mov ebx,[rsi+r9*4+8]
0xe804705  imul ebp,ebx,0x5EBCA77
0xe80470b  shr ebp,0x13
0xe80470e  imul ebp,0x1B1
0xe804714  and ebp,0x3FF
0xe80471a  mov r14d,ebp
0xe80471d  nop [rax]
0xe804720  mov r14d,r14d
0xe804723  cmp word ptr [rdx+r14*2],0xFFFF
0xe804729  je short 0xE804760
0xe80472b  cmp [rsi+r14*4+8],ebx
0xe804730  je short 0xE804750
0xe804732  inc r14d
0xe804735  and r14d,0x3FF
0xe80473c  cmp r14d,ebp
0xe80473f  jne short 0xE804720
0xe804741  jmp short 0xE804760
0xe804743  nop [rax+rax]
0xe804750  cmp r9d,r14d
0xe804753  je short 0xE8046E2
0xe804755  nop [rax+rax]
0xe804760  mov word ptr [r11],0xFFFF
0xe804766  lea r11d,[r8-1]
0xe80476a  mov [rsi+4],r11d
0xe80476e  mov r14d,ebp
0xe804771  nop [rax+rax]
0xe804780  mov r14d,r14d
0xe804783  cmp word ptr [rdx+r14*2],0xFFFF
0xe804789  je 0xE8046D0
0xe80478f  cmp [rsi+r14*4+8],ebx
0xe804794  je short 0xE8047A5
0xe804796  inc r14d
0xe804799  and r14d,0x3FF
0xe8047a0  cmp r14d,ebp
0xe8047a3  jne short 0xE804780
0xe8047a5  mov r8d,r11d
0xe8047a8  jmp 0xE8046E2
0xe8047ad  cmp di,0xFFFF
0xe8047b1  je short 0xE8047F4
0xe8047b3  mov r8d,ecx
0xe8047b6  nop [rax+rax]
0xe8047c0  mov r8d,r8d
0xe8047c3  cmp word ptr [rdx+r8*2],0xFFFF
0xe8047c9  je short 0xE8047E3
0xe8047cb  cmp [rsi+r8*4+8],eax
0xe8047d0  je short 0xE8047F4
0xe8047d2  inc r8d
0xe8047d5  and r8d,0x3FF
0xe8047dc  cmp r8d,ecx
0xe8047df  jne short 0xE8047C0
0xe8047e1  jmp short 0xE8047F4
0xe8047e3  mov [rsi+r8*4+8],eax
0xe8047e8  mov [rsi+r8*2+0x1008],di
0xe8047f1  inc dword ptr [rsi+4]
0xe8047f4  movzx eax,di
0xe8047f7  mov [rsi+rax*2+0x1808],di
0xe8047ff  mov rcx,[rsp+0x38]
0xe804804  xor rcx,rsp
0xe804807  mov rdx,[0x1230A0C0]
0xe80480e  cmp rdx,rcx
0xe804811  jne short 0xE804828
0xe804813  lea rax,[rsi+rax*2]
0xe804817  add rax,0x1808
0xe80481d  add rsp,0x40
0xe804821  pop rbx
0xe804822  pop rbp
0xe804823  pop rdi
0xe804824  pop rsi
0xe804825  pop r14
0xe804827  ret
0xe804828  mov rcx,[rsp+0x38]
0xe80482d  xor rcx,rsp
0xe804830  call 0xE951550
0xe804835  int3
#endif

LIFT_FN(e804590, "sub_e804590", 0xE804590, sub_e804590, nullptr);

} // namespace native

