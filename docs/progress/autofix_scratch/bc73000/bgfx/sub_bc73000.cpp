// LIFT 0xbc73000 size 0x285 1.26.62.01 bgfx::createProgram(ShaderHandle, destroy)

#include "client/features/render/native/bgfx/sub_bc73000.h"

#include <cstdint>
#include <cstring>
#include "client/features/render/native/Lift.h"

namespace native::bgfx {

// 0xbc73000..0xbc7305e

// 0xbc73035  call 0xEBDBF10                                ; -> sub_ebdbf10

std::uint16_t sub_bc73000(void* ctx, std::uint16_t* out, std::uint16_t shader, bool destroy) {
    std::uint8_t* self = static_cast<std::uint8_t*>(ctx);
    std::uint16_t* rsi = out;
    std::uint16_t r14w = shader;
    std::uint8_t bl = destroy ? 1 : 0;

    // 0xbc73000..0xbc7305e

    // Enter critical section at self+0x1C0

    sub_ebdbf10(self + bc73000_ctx::kCS);

    // 0xbc7303a..0xbc7305e: if (shader != 0xFFFF) compute hash index

    std::uint32_t ecx_hash;
    if (r14w != 0xFFFF) {
        // 0xbc73045..0xbc73058: hash = (shader * 0x5EBCA77) >> 19 * 0x9B1 & 0xFFF

        std::uint32_t eax = r14w;
        std::uint32_t ecx = (eax * 0x5EBCA77) >> 19;
        ecx = (ecx * 0x9B1) & 0xFFF;
        ecx_hash = ecx;
    } else {
        ecx_hash = 0; // unused in this path

    }

    // 0xbc73060..0xbc7308d: linear probe hash table for shader

    // 0xbc73060  mov r9d,edx

    // 0xbc73063  movzx r8d,word ptr [rdi+r9*2+0x1E50AB8]       ; R a0+0x1E50AB8+idx

    // 0xbc7306c  cmp r8,0xFFFF

    // 0xbc73073  je short 0xBC7308F                            ; -> loc_bc7308f

    // 0xbc73075  cmp [rdi+r9*4+0x1E4CAB8],eax                  ; R a0+0x1E4CAB8+idx

    // 0xbc7307d  je 0xBC73160                                  ; -> loc_bc73160

    // 0xbc73083  inc edx

    // 0xbc73085  and edx,0xFFF

    // 0xbc7308b  cmp edx,ecx

    // 0xbc7308d  jne short 0xBC73060                           ; -> loc_bc73060

    if (r14w != 0xFFFF) {
        std::uint32_t edx = ecx_hash;
        while (true) {
            std::uint16_t r8 = *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kHashIdx + edx * 2);
            if (r8 == 0xFFFF) break; // empty slot -> go to free list allocation

            std::uint32_t key = *reinterpret_cast<std::uint32_t*>(self + bc73000_ctx::kHashKeys + edx * 4);
            if (key == r14w) {
                // found existing entry

                *rsi = r8;
                goto loc_bc73160;
            }
            edx = (edx + 1) & 0xFFF;
            if (edx == ecx_hash) break; // full circle

        }
    }

    // 0xbc7308f..0xbc73112: allocate from free list

    // 0xbc7308f  movzx r8d,word ptr [rdi+0x1DF145C]            ; R a0+0x1DF145C

    // 0xbc73097  movzx r9d,word ptr [rdi+0x1DF145E]            ; R a0+0x1DF145E

    // 0xbc7309f  cmp r8w,r9w

    // 0xbc730a3  jae 0xBC73155                                 ; -> loc_bc73155 (free list empty)

    // 0xbc730a9  movzx edx,r8w

    // 0xbc730ad  lea r10d,[r8+1]

    // 0xbc730b1  mov [rdi+0x1DF145C],r10w                      ; W a0+0x1DF145C

    // 0xbc730b9  movzx edx,word ptr [rdi+rdx*2+0x1DF1460]      ; R a0+0x1DF1460+idx

    // 0xbc730c1  lea r9,[rdi+r9*2]                             ; R a0+0x0+idx

    // 0xbc730c5  add r9,0x1DF1460

    // 0xbc730cc  mov [r9+rdx*2],r8w

    // 0xbc730d1  mov [rsi],dx                                  ; W a1+0x0

    // 0xbc730d4  cmp edx,0xFFFF

    // 0xbc730da  je 0xBC73183                                  ; -> loc_bc73183

    // 0xbc730e0  mov r8d,eax

    // 0xbc730e3  shl r8d,5

    // 0xbc730e7  inc word ptr [rdi+r8+0x1E2CACC]               ; W a0+0x1E2CACC+idx

    // 0xbc730f0  lea r8,[rdx+rdx*2]

    // 0xbc730f4  mov [rdi+r8*2+0x1E52AB8],r14w                 ; W a0+0x1E52AB8+idx

    // 0xbc730fd  mov word ptr [rbp-6],0xFFFF

    // 0xbc73103  mov dword ptr [rdi+r8*2+0x1E52ABA],0x1FFFF

    // 0xbc7310f  mov r8d,ecx

    // 0xbc73112  nop [rax+rax]

    {
        std::uint16_t freeCount = *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kFreeCount);
        std::uint16_t freeCap = *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kFreeCap);
        if (freeCount < freeCap) {
            std::uint16_t edx = freeCount;
            *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kFreeCount) = freeCount + 1;
            std::uint16_t handle = *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kFreeArr + edx * 2);
            *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kFreeArr + handle * 2) = edx; // unclear mapping, but replicate

            *rsi = handle;
            if (handle != 0xFFFF) {
                // increment shader use count at index handle<<5

                std::uint32_t r8d = r14w << 5;
                (*reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kShaderUse + r8d))++;
                // program arrays

                std::uint32_t r8 = handle * 3;
                *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kProgIdx + r8 * 2) = r14w;
                *reinterpret_cast<std::uint32_t*>(self + bc73000_ctx::kProgFlags + r8 * 2) = 0x1FFFF;
                *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kProgUse + r8 * 2) = 0xFFFF; // [rbp-6]

            }
        }
    }

    // 0xbc73120..0xbc7314c: insert into hash table

    // 0xbc73120  mov r9d,r8d

    // 0xbc73123  cmp word ptr [rdi+r9*2+0x1E50AB8],0xFFFF      ; R a0+0x1E50AB8+idx

    // 0xbc7312d  je short 0xBC731AE                            ; -> loc_bc731ae

    // 0xbc7312f  cmp [rdi+r9*4+0x1E4CAB8],eax                  ; R a0+0x1E4CAB8+idx

    // 0xbc73137  je 0xBC731C5                                  ; -> loc_bc731c5

    // 0xbc7313d  inc r8d

    // 0xbc73140  and r8d,0xFFF

    // 0xbc73147  cmp r8d,ecx

    // 0xbc7314a  jne short 0xBC73120                           ; -> loc_bc73120

    // 0xbc7314c  jmp short 0xBC731C5                           ; -> loc_bc731c5

    if (r14w != 0xFFFF && *rsi != 0xFFFF) {
        std::uint32_t r8d = ecx_hash;
        while (true) {
            std::uint16_t slotIdx = *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kHashIdx + r8d * 2);
            if (slotIdx == 0xFFFF) {
                // empty slot found

                *reinterpret_cast<std::uint32_t*>(self + bc73000_ctx::kHashKeys + r8d * 4) = r14w;
                *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kHashIdx + r8d * 2) = *rsi;
                (*reinterpret_cast<std::uint32_t*>(self + bc73000_ctx::kHashCount))++;
                break;
            }
            std::uint32_t key = *reinterpret_cast<std::uint32_t*>(self + bc73000_ctx::kHashKeys + r8d * 4);
            if (key == r14w) {
                goto loc_bc731c5;
            }
            r8d = (r8d + 1) & 0xFFF;
            if (r8d == ecx_hash) {
                goto loc_bc731c5;
            }
        }
    }

loc_bc7314e:
    // 0xbc7314e..0xbc73153: shader == 0xFFFF path

    // 0xbc7314e  mov word ptr [rsi],0xFFFF

    // 0xbc73153  jmp short 0xBC73194                           ; -> loc_bc73194

    if (r14w == 0xFFFF) {
        *rsi = 0xFFFF;
        goto loc_bc73194;
    }

loc_bc73155:
    // 0xbc73155..0xbc7315e: free list empty

    // 0xbc73155  mov word ptr [rsi],0xFFFF

    // 0xbc7315a  test bl,bl

    // 0xbc7315c  jne short 0xBC73187                           ; -> loc_bc73187

    // 0xbc7315e  jmp short 0xBC73194                           ; -> loc_bc73194

    *rsi = 0xFFFF;
    if (bl) {
        goto loc_bc73187;
    }
    goto loc_bc73194;

loc_bc73160:
    // 0xbc73160..0xbc7317b: found existing entry in hash probe

    // 0xbc73160  mov [rsi],r8w

    // 0xbc73164  lea rax,[r8+r8*2]

    // 0xbc73168  inc word ptr [rdi+rax*2+0x1E52ABC]             ; W a0+0x1E52ABC+idx

    // 0xbc73170  movzx eax,word ptr [rdi+rax*2+0x1E52AB8]       ; R a0+0x1E52AB8+idx

    // 0xbc73178  shl eax,5

    // 0xbc7317b  inc word ptr [rdi+rax+0x1E2CACC]               ; W a0+0x1E2CACC+idx

    {
        std::uint16_t handle = *rsi;
        std::uint32_t rax = handle * 3;
        (*reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kProgUse + rax * 2))++;
        std::uint16_t progShader = *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kProgIdx + rax * 2);
        std::uint32_t shaderUseIdx = progShader << 5;
        (*reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kShaderUse + shaderUseIdx))++;
    }

loc_bc73183:
    // 0xbc73183..0xbc73185

    // 0xbc73183  test bl,bl

    // 0xbc73185  je short 0xBC73194                            ; -> loc_bc73194

    if (!bl) {
        goto loc_bc73194;
    }

loc_bc73187:
    // 0xbc73187..0xbc73193: destroy path

    // 0xbc73187  movzx edx,word ptr [rbp-4]                     ; destroy flag saved at [rbp-4]

    // 0xbc7318b  mov rcx,rdi

    // 0xbc7318e  call 0xBC79790                                ; -> sub_bc79790

    // 0xbc73193  nop

    {
        std::uint16_t destroyFlag = *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kCS - 0x1C0); // [rbp-4] = r8w saved at entry

        sub_bc79790(ctx, *rsi, destroyFlag);
    }

loc_bc73194:
    // 0xbc73194..0xbc731ad: leave critical section and return

    // 0xbc73194  mov rcx,[rbp-0x10]                             ; saved CS pointer

    // 0xbc73198  call 0xEBDBF20                                ; -> sub_ebdbf20

    // 0xbc7319d  nop

    // 0xbc7319e  mov rax,rsi

    // 0xbc731a1  add rsp,0x38

    // 0xbc731a5  pop rbx

    // 0xbc731a6  pop rdi

    // 0xbc731a7  pop rsi

    // 0xbc731a8  pop r14

    // 0xbc731aa  pop r15

    // 0xbc731ac  pop rbp

    // 0xbc731ad  ret

    sub_ebdbf20(self + bc73000_ctx::kCS);
    return *rsi;

loc_bc731ae:
    // 0xbc731ae..0xbc731bf: hash insert (empty slot)

    // 0xbc731ae  mov [rdi+r9*4+0x1E4CAB8],eax

    // 0xbc731b6  mov [rdi+r9*2+0x1E50AB8],dx

    // 0xbc731bf  inc dword ptr [rdi+0x1E4CAB4]

    *reinterpret_cast<std::uint32_t*>(self + bc73000_ctx::kHashKeys + r8d * 4) = r14w;
    *reinterpret_cast<std::uint16_t*>(self + bc73000_ctx::kHashIdx + r8d * 2) = *rsi;
    (*reinterpret_cast<std::uint32_t*>(self + bc73000_ctx::kHashCount))++;

loc_bc731c5:
    // 0xbc731c5..0xbc73280: logger writes (4 memcpy calls to logger ring buffer)

    // 0xbc731c5  mov r15,[rdi+0x1CFD0C8]                        ; logger ptr

    // 0xbc731cc  mov byte ptr [rbp-1],0xD                       ; tag 0xD

    // 0xbc731d0  mov eax,[r15+0xDC5818]                         ; writeIdx

    // 0xbc731d7  lea rcx,[r15+rax]                              ; dst = logger + writeIdx

    // 0xbc731db  add rcx,0xDC5820                               ; +buf

    // 0xbc731e2  lea rdx,[rbp-1]                                ; src = &tag

    // 0xbc731e6  mov r8d,1                                      ; size=1

    // 0xbc731ec  call 0xEBCE390                                ; -> sub_ebce390 (memcpy)

    // 0xbc731f1  nop

    // 0xbc731f2  lea r14,[r15+0xDC5820]                         ; buf base

    // 0xbc731f9  mov ecx,[r15+0xDC5818]                         ; writeIdx

    // 0xbc73200  and ecx,0xFFFFFFFE                             ; align down to even

    // 0xbc73203  add ecx,2                                      ; +2

    // 0xbc73206  mov [r15+0xDC5818],ecx                         ; update writeIdx

    // 0xbc7320d  add rcx,r14                                    ; dst = buf + writeIdx

    // 0xbc73210  mov r8d,2                                      ; size=2

    // 0xbc73216  mov rdx,rsi                                    ; src = out handle

    // 0xbc73219  call 0xEBCE390                                ; -> sub_ebce390

    // 0xbc7321e  nop

    // 0xbc7321f  mov ecx,[r15+0xDC5818]                         ; writeIdx

    // 0xbc73226  add ecx,3                                      ; +3

    // 0xbc73229  and ecx,0xFFFFFFFE                             ; align down

    // 0xbc7322c  mov [r15+0xDC5818],ecx                         ; update

    // 0xbc73233  add rcx,r14                                    ; dst

    // 0xbc73236  lea rdx,[rbp-4]                                ; src = &shader

    // 0xbc7323a  mov r8d,2                                      ; size=2

    // 0xbc73240  call 0xEBCE390                                ; -> sub_ebce390

    // 0xbc73245  nop

    // 0xbc73246  mov eax,[r15+0xDC5818]                         ; writeIdx

    // 0xbc7324d  add eax,3                                      ; +3

    // 0xbc73250  and eax,0xFFFFFFFE                             ; align

    // 0xbc73253  mov [r15+0xDC5818],eax                         ; update

    // 0xbc7325a  add r14,rax                                    ; dst

    // 0xbc7325d  lea rdx,[rbp-6]                                ; src = &[rbp-6] (0xFFFF)

    // 0xbc73261  mov r8d,2                                      ; size=2

    // 0xbc73267  mov rcx,r14                                    ; dst

    // 0xbc7326a  call 0xEBCE390                                ; -> sub_ebce390

    // 0xbc7326f  nop

    // 0xbc73270  add dword ptr [r15+0xDC5818],2                 ; writeIdx += 2

    // 0xbc73278  test bl,bl

    // 0xbc7327a  jne 0xBC73187                                 ; -> loc_bc73187 (if destroy, call destroy again?)

    // 0xbc73280  jmp 0xBC73194                                 ; -> loc_bc73194

    {
        std::uint8_t* logger = *reinterpret_cast<std::uint8_t**>(self + bc73000_ctx::kLogger);
        if (logger) {
            std::uint32_t* writeIdx = reinterpret_cast<std::uint32_t*>(logger + bc73000_ctx::kLogWriteIdx);
            std::uint8_t* buf = logger + bc73000_ctx::kLogBuf;

            // write tag 0xD (1 byte)

            sub_ebce390(buf + *writeIdx, "\xD", 1);
            *writeIdx = (*writeIdx + 1 + 1) & ~1u; // align up to even? original: and ecx,0xFFFFFFFE; add ecx,2

            *writeIdx += 2;

            // write out handle (2 bytes)

            sub_ebce390(buf + *writeIdx, rsi, 2);
            *writeIdx = (*writeIdx + 3) & ~1u;
            *writeIdx += 2;

            // write shader handle (2 bytes)

            sub_ebce390(buf + *writeIdx, &r14w, 2);
            *writeIdx = (*writeIdx + 3) & ~1u;
            *writeIdx += 2;

            // write 0xFFFF (2 bytes)

            std::uint16_t neg1 = 0xFFFF;
            sub_ebce390(buf + *writeIdx, &neg1, 2);
            *writeIdx += 2;

            if (bl) {
                goto loc_bc73187;
            }
        }
    }
    goto loc_bc73194;
}

// Layout assertions

static_assert(bc73000_ctx::kCS == 0x1C0);
static_assert(bc73000_ctx::kHashKeys == 0x1E4CAB8);
static_assert(bc73000_ctx::kHashIdx == 0x1E50AB8);
static_assert(bc73000_ctx::kHashCount == 0x1E4CAB4);
static_assert(bc73000_ctx::kFreeCount == 0x1DF145C);
static_assert(bc73000_ctx::kFreeCap == 0x1DF145E);
static_assert(bc73000_ctx::kFreeArr == 0x1DF1460);
static_assert(bc73000_ctx::kShaderUse == 0x1E2CACC);
static_assert(bc73000_ctx::kProgIdx == 0x1E52AB8);
static_assert(bc73000_ctx::kProgFlags == 0x1E52ABA);
static_assert(bc73000_ctx::kProgUse == 0x1E52ABC);
static_assert(bc73000_ctx::kLogger == 0x1CFD0C8);
static_assert(bc73000_ctx::kLogWriteIdx == 0xDC5818);
static_assert(bc73000_ctx::kLogBuf == 0xDC5820);

// Verbatim log of every call instruction in [0xbc73000, 0xbc73285) (rdis dis output, two spaces after address):

#if 0
0xbc73035  call 0xEBDBF10                                ; -> sub_ebdbf10
0xbc7318e  call 0xBC79790                                ; -> sub_bc79790
0xbc73198  call 0xEBDBF20                                ; -> sub_ebdbf20
0xbc731ec  call 0xEBCE390                                ; -> sub_ebce390
0xbc73219  call 0xEBCE390                                ; -> sub_ebce390
0xbc73240  call 0xEBCE390                                ; -> sub_ebce390
0xbc7326a  call 0xEBCE390                                ; -> sub_ebce390
#endif

// Calls out of lifted code:

//   sub_ebdbf10 (0xebdbf10, lift set) - call 0xEBDBF10                                ; -> sub_ebdbf10

//   sub_bc79790 (0xbc79790, lift set) - call 0xBC79790                                ; -> sub_bc79790

//   sub_ebdbf20 (0xebdbf20, lift set) - call 0xEBDBF20                                ; -> sub_ebdbf20

//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390

//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390

//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390

//   sub_ebce390 (0xebce390, lift set) - call 0xEBCE390                                ; -> sub_ebce390

//   UNRESOLVED CALL = none: every call target is either lifted or in native_boundary.tsv


LIFT_FN(sub_bc73000, "sub_bc73000", 0xbc73000, sub_bc73000, nullptr);

} // namespace native::bgfx