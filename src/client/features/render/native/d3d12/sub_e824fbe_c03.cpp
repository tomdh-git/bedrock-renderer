// LIFT 0xe824fbe size 0x8525 1.26.62.01 sub_e824fbe
// CHUNK 0xe8297a2..0xe82af92
#include "client/features/render/native/d3d12/sub_e824fbe_c03.h"

#if 0
0xe8297a8  call 0xEEC6ED0
0xe8297d4  call 0xEEC6ED0
0xe829800  call 0xEEC6ED0
0xe82982f  call 0xEEC6ED0
0xe829861  call 0xEEC6ED0
0xe829893  call 0xEEC6ED0
0xe8298c2  call 0xEEC6ED0
0xe8298e7  call 0xEEC6ED0
0xe82991c  call 0xEEC6ED0
0xe82994e  call 0xEEC6ED0
0xe82997d  call 0xEEC6ED0
0xe8299ac  call 0xEEC6ED0
0xe8299d3  call 0xEEC6EC0
0xe829a1e  call 0xE8360F0
0xe829a83  call qword ptr [0xF99FFA0]
0xe829aa7  call qword ptr [0xF99FFA0]
0xe829b42  call 0xEEC6EC0
0xe829b71  call qword ptr [0xF99FFA0]
0xe829be1  call r10
0xe829c60  call r11
0xe829c7d  call qword ptr [0xF99FFA0]
0xe829cb5  call 0xEEC6ED0
0xe829da5  call qword ptr [0xF99FFA0]
0xe829dde  call qword ptr [0xF99FFA0]
0xe829e06  call qword ptr [0xF99FFA0]
0xe829e37  call qword ptr [0xF99FFA0]
0xe829ec4  call qword ptr [0xF99FFA0]
0xe829f60  call qword ptr [0xF99FFA0]
0xe82a079  call qword ptr [0xF99FFA0]
0xe82a0ed  call qword ptr [0xF99FFA0]
0xe82a132  call qword ptr [0xF99FFA0]
0xe82a1f6  call 0xBC6A9D0
0xe82a393  call 0x47E8F0
0xe82a3c3  call 0xEEC6ED0
0xe82a40f  call 0xE81E1C0
0xe82a485  call 0xE81E1C0
0xe82a4c4  call 0xEEC6ED0
0xe82a4f2  call 0xEEC6EC0
0xe82a58a  call 0x47E8F0
0xe82a70f  call 0x47E8F0
0xe82a783  call 0x47E8F0
0xe82a7e0  call 0x47E8F0
0xe82a863  call 0x47E8F0
0xe82a8f3  call 0x47E8F0
0xe82ac21  call 0x47E8F0
0xe82af3a  call 0x47E8F0
#endif

namespace native {
namespace d3d12 {

// Forward declarations for boundary callees (from native_boundary.tsv)
// 0x47E8F0: STL vector grow/check - class=stl
// 0xEEC6ED0: CRT import thunk (jmp qword ptr [IAT]) - class=crt
// 0xEEC6EC0: CRT import thunk - class=crt
// 0xE8360F0: unknown - class=?
// 0xBC6A9D0: unknown - class=?
// 0xE81E1C0: unknown - class=?
// 0xF99FFA0: data slot (D3D12 device method) - class=d3d
extern "C" void sub_47e8f0(void* rcx, void* rdx, void* r8);           // 0x47e8f0 (STL)
extern "C" void sub_eec6ed0(void* rcx, void* rdx);                      // 0xeec6ed0 (CRT)
extern "C" void sub_eec6ec0(void* rcx, void* rdx, void* r8);            // 0xeec6ec0 (CRT)
extern "C" void sub_e8360f0(void* rcx, void* rdx, void* r8, void* r9);  // 0xe8360f0
extern "C" void sub_bc6a9d0(void* rcx, void* rdx, void* r8, void* r9);  // 0xbc6a9d0
extern "C" void sub_e81e1c0(void* rcx, void* rdx, void* r8, void* r9);  // 0xe81e1c0

// Data slot addresses (constants loaded via RIP-relative)
static constexpr uintptr_t kData_F99FFA0 = 0xF99FFA0;

// Helper to access rbx-frame slots
inline uint8_t* rbx_ptr(void* rbx, ptrdiff_t off) { return static_cast<uint8_t*>(rbx) + off; }
inline uint64_t& slot64(void* rbx, ptrdiff_t off) { return *reinterpret_cast<uint64_t*>(rbx_ptr(rbx, off)); }
inline uint32_t& slot32(void* rbx, ptrdiff_t off) { return *reinterpret_cast<uint32_t*>(rbx_ptr(rbx, off)); }
inline uint16_t& slot16(void* rbx, ptrdiff_t off) { return *reinterpret_cast<uint16_t*>(rbx_ptr(rbx, off)); }
inline uint8_t& slot8(void* rbx, ptrdiff_t off) { return *reinterpret_cast<uint8_t*>(rbx_ptr(rbx, off)); }
inline __m128& slot128(void* rbx, ptrdiff_t off) { return *reinterpret_cast<__m128*>(rbx_ptr(rbx, off)); }
inline const __m128& cslot128(const void* rbx, ptrdiff_t off) { return *reinterpret_cast<const __m128*>(static_cast<const uint8_t*>(rbx) + off); }

// 0xe8297a2..0xe82af92
static inline void sub_e824fbe_chunk_c03(ChunkState_e824fbe_c03& s) {
    // Unpack state
    void* rbx = s.rbx;
    void* rbp = s.rbp;
    uint64_t rcx = s.rcx;
    uint64_t rdx = s.rdx;
    uint64_t rsi = s.rsi;
    uint64_t rdi = s.rdi;
    uint64_t rax = s.rax;
    uint64_t r8 = s.r8;
    uint64_t r9 = s.r9;
    void* r10 = s.r10;
    void* r11 = s.r11;
    void* r12 = s.r12;
    void* r13 = s.r13;
    void* r14 = s.r14;
    uint64_t r15 = s.r15;
    __m128 xmm8 = s.xmm8;
    __m128 xmm9 = s.xmm9;
    unsigned char al = s.al_flags;

    // -------------------------------------------------------------------------
    // 0xe8297a2..0xe8297c9: First vector append case (jmp to 0xe827f10)
    // 0xe8297a2  lea rdi,[rcx+r8]                              ; R a0+0x0+idx
    // 0xe8297a6  xor edx,edx                                   
    // 0xe8297a8  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe8297ad  mov rax,[rbx+0x98]                            
    // 0xe8297b4  mov [rax],rdi                                 
    // 0xe8297b7  mov r13,[rbx+0xA8]                            
    // 0xe8297be  mov rax,[r13]                                 
    // 0xe8297c2  add rax,rsi                                   
    // 0xe8297c5  movups [rax],xmm8                             
    // 0xe8297c9  jmp 0xE827F10                                 ; -> sub_e827f10
    // -------------------------------------------------------------------------
    // 0xe8297a2..0xe8297c9
    rdi = rcx + r8;                                              // 0xe8297a2  lea rdi,[rcx+r8]
    rdx = 0;                                                     // 0xe8297a6  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe8297a8  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe8297ad  mov rax,[rbx+0x98]
    slot64(rax, 0) = rdi;                                        // 0xe8297b4  mov [rax],rdi
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe8297b7  mov r13,[rbx+0xA8]
    rax = slot64(r13, 0);                                        // 0xe8297be  mov rax,[r13]
    rax += rsi;                                                  // 0xe8297c2  add rax,rsi
    slot128(reinterpret_cast<void*>(rax), 0) = xmm8;             // 0xe8297c5  movups [rax],xmm8
    // 0xe8297c9  jmp 0xe827f10 - target is in previous chunk (c02), not handled here
    // Execution continues at next basic block (fallthrough from other entry points)

    // -------------------------------------------------------------------------
    // 0xe8297ce..0xe8297f5: Second vector append case (movlps, jmp to 0xe827f10)
    // 0xe8297ce  lea rdi,[rcx+r8]                              
    // 0xe8297d2  xor edx,edx                                   
    // 0xe8297d4  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe8297d9  mov rax,[rbx+0x98]                            
    // 0xe8297e0  mov [rax],rdi                                 
    // 0xe8297e3  mov r13,[rbx+0xA8]                            
    // 0xe8297ea  mov rax,[r13]                                 
    // 0xe8297ee  add rax,rsi                                   
    // 0xe8297f1  movlps [rax],xmm8                             
    // 0xe8297f5  jmp 0xE827F10                                 ; -> sub_e827f10
    // -------------------------------------------------------------------------
    // 0xe8297ce..0xe8297f5
    rdi = rcx + r8;                                              // 0xe8297ce  lea rdi,[rcx+r8]
    rdx = 0;                                                     // 0xe8297d2  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe8297d4  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe8297d9  mov rax,[rbx+0x98]
    slot64(rax, 0) = rdi;                                        // 0xe8297e0  mov [rax],rdi
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe8297e3  mov r13,[rbx+0xA8]
    rax = slot64(r13, 0);                                        // 0xe8297ea  mov rax,[r13]
    rax += rsi;                                                  // 0xe8297ee  add rax,rsi
    _mm_storel_pi(reinterpret_cast<__m64*>(rax), xmm8);          // 0xe8297f1  movlps [rax],xmm8
    // 0xe8297f5  jmp 0xe827f10 - target in previous chunk

    // -------------------------------------------------------------------------
    // 0xe8297fa..0xe829824: Third case (uses r12, adds rdi+rsi+[r13], movups, jmp 0xe827f10)
    // 0xe8297fa  lea r12,[rcx+r8]                              
    // 0xe8297fe  xor edx,edx                                   
    // 0xe829800  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe829805  mov rax,[rbx+0x98]                            
    // 0xe82980c  mov [rax],r12                                 
    // 0xe82980f  mov r13,[rbx+0xA8]                            
    // 0xe829816  mov rax,[r13]                                 
    // 0xe82981a  add rdi,rsi                                   
    // 0xe82981d  add rdi,rax                                   
    // 0xe829820  movups [rdi],xmm8                             
    // 0xe829824  jmp 0xE827F10                                 ; -> sub_e827f10
    // -------------------------------------------------------------------------
    // 0xe8297fa..0xe829824
    r12 = reinterpret_cast<void*>(rcx + r8);                     // 0xe8297fa  lea r12,[rcx+r8]
    rdx = 0;                                                     // 0xe8297fe  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe829800  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe829805  mov rax,[rbx+0x98]
    slot64(rax, 0) = reinterpret_cast<uint64_t>(r12);            // 0xe82980c  mov [rax],r12
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe82980f  mov r13,[rbx+0xA8]
    rax = slot64(r13, 0);                                        // 0xe829816  mov rax,[r13]
    rdi += rsi;                                                  // 0xe82981a  add rdi,rsi
    rdi += rax;                                                  // 0xe82981d  add rdi,rax
    slot128(reinterpret_cast<void*>(rdi), 0) = xmm8;             // 0xe829820  movups [rdi],xmm8
    // 0xe829824  jmp 0xe827f10 - target in previous chunk

    // -------------------------------------------------------------------------
    // 0xe829829..0xe829853: Fourth case (r12, movlps, jmp 0xe827f10)
    // 0xe829829  lea r12,[rcx+r8]                              
    // 0xe82982d  xor edx,edx                                   
    // 0xe82982f  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe829834  mov rax,[rbx+0x98]                            
    // 0xe82983b  mov [rax],r12                                 
    // 0xe82983e  mov r13,[rbx+0xA8]                            
    // 0xe829845  mov rax,[r13]                                 
    // 0xe829849  add rdi,rsi                                   
    // 0xe82984c  add rdi,rax                                   
    // 0xe82984f  movlps [rdi],xmm8                             
    // 0xe829853  jmp 0xE827F10                                 ; -> sub_e827f10
    // -------------------------------------------------------------------------
    // 0xe829829..0xe829853
    r12 = reinterpret_cast<void*>(rcx + r8);                     // 0xe829829  lea r12,[rcx+r8]
    rdx = 0;                                                     // 0xe82982d  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe82982f  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe829834  mov rax,[rbx+0x98]
    slot64(rax, 0) = reinterpret_cast<uint64_t>(r12);            // 0xe82983b  mov [rax],r12
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe82983e  mov r13,[rbx+0xA8]
    rax = slot64(r13, 0);                                        // 0xe829845  mov rax,[r13]
    rdi += rsi;                                                  // 0xe829849  add rdi,rsi
    rdi += rax;                                                  // 0xe82984c  add rdi,rax
    _mm_storel_pi(reinterpret_cast<__m64*>(rdi), xmm8);          // 0xe82984f  movlps [rdi],xmm8
    // 0xe829853  jmp 0xe827f10 - target in previous chunk

    // -------------------------------------------------------------------------
    // 0xe829858..0xe829885: Fifth case (lea r12,[rax+r8], mov rcx,rax, call, jmp 0xe8299d0)
    // 0xe829858  lea r12,[rax+r8]                              
    // 0xe82985c  mov rcx,rax                                   
    // 0xe82985f  xor edx,edx                                   
    // 0xe829861  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe829866  mov rax,[rbx+0x98]                            
    // 0xe82986d  mov [rax],r12                                 
    // 0xe829870  mov r13,[rbx+0xA8]                            
    // 0xe829877  mov rcx,[r13]                                 
    // 0xe82987b  add rcx,rdi                                   
    // 0xe82987e  lea rdx,[rbx+0x90f0]                          
    // 0xe829885  jmp 0xE8299D0                                 ; -> loc_e8299d0
    // -------------------------------------------------------------------------
    // 0xe829858..0xe829885
    r12 = reinterpret_cast<void*>(rax + r8);                     // 0xe829858  lea r12,[rax+r8]
    rcx = rax;                                                   // 0xe82985c  mov rcx,rax
    rdx = 0;                                                     // 0xe82985f  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe829861  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe829866  mov rax,[rbx+0x98]
    slot64(rax, 0) = reinterpret_cast<uint64_t>(r12);            // 0xe82986d  mov [rax],r12
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe829870  mov r13,[rbx+0xA8]
    rcx = slot64(r13, 0);                                        // 0xe829877  mov rcx,[r13]
    rcx += rdi;                                                  // 0xe82987b  add rcx,rdi
    rdx = reinterpret_cast<uint64_t>(rbx_ptr(rbx, 0x90F0));      // 0xe82987e  lea rdx,[rbx+0x90f0]
    // 0xe829885  jmp 0xe8299d0 - handled later in this chunk

    // -------------------------------------------------------------------------
    // 0xe82988a..0xe8298b7: Sixth case (lea rdi,[rax+r8], mov rcx,rax, call, jmp 0xe8299d0)
    // 0xe82988a  lea rdi,[rax+r8]                              
    // 0xe82988e  mov rcx,rax                                   
    // 0xe829891  xor edx,edx                                   
    // 0xe829893  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe829898  mov rax,[rbx+0x98]                            
    // 0xe82989f  mov [rax],rdi                                 
    // 0xe8298a2  mov r13,[rbx+0xA8]                            
    // 0xe8298a9  mov rcx,[r13]                                 
    // 0xe8298ad  add rcx,r12                                   
    // 0xe8298b0  lea rdx,[rbx+0x90f0]                          
    // 0xe8298b7  jmp 0xE8299D0                                 ; -> loc_e8299d0
    // -------------------------------------------------------------------------
    // 0xe82988a..0xe8298b7
    rdi = reinterpret_cast<uint64_t>(rax + r8);                  // 0xe82988a  lea rdi,[rax+r8]
    rcx = rax;                                                   // 0xe82988e  mov rcx,rax
    rdx = 0;                                                     // 0xe829891  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe829893  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe829898  mov rax,[rbx+0x98]
    slot64(rax, 0) = rdi;                                        // 0xe82989f  mov [rax],rdi
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe8298a2  mov r13,[rbx+0xA8]
    rcx = slot64(r13, 0);                                        // 0xe8298a9  mov rcx,[r13]
    rcx += reinterpret_cast<uint64_t>(r12);                      // 0xe8298ad  add rcx,r12
    rdx = reinterpret_cast<uint64_t>(rbx_ptr(rbx, 0x90F0));      // 0xe8298b0  lea rdx,[rbx+0x90f0]
    // 0xe8298b7  jmp 0xe8299d0 - handled later

    // -------------------------------------------------------------------------
    // 0xe8298bc..0xe8298df: Seventh case (lea rdi,[rcx+r8], call, jmp 0xe829907)
    // 0xe8298bc  lea rdi,[rcx+r8]                              
    // 0xe8298c0  xor edx,edx                                   
    // 0xe8298c2  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe8298c7  mov rax,[rbx+0x98]                            
    // 0xe8298ce  mov [rax],rdi                                 
    // 0xe8298d1  mov r13,[rbx+0xA8]                            
    // 0xe8298d8  mov rdi,[r13]                                 
    // 0xe8298dc  add rdi,rsi                                   
    // 0xe8298df  jmp 0xE829907                                 ; -> loc_e829907
    // -------------------------------------------------------------------------
    // 0xe8298bc..0xe8298df
    rdi = rcx + r8;                                              // 0xe8298bc  lea rdi,[rcx+r8]
    rdx = 0;                                                     // 0xe8298c0  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe8298c2  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe8298c7  mov rax,[rbx+0x98]
    slot64(rax, 0) = rdi;                                        // 0xe8298ce  mov [rax],rdi
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe8298d1  mov r13,[rbx+0xA8]
    rdi = slot64(r13, 0);                                        // 0xe8298d8  mov rdi,[r13]
    rdi += rsi;                                                  // 0xe8298dc  add rdi,rsi
    // 0xe8298df  jmp 0xe829907 - handled later

    // -------------------------------------------------------------------------
    // 0xe8298e1..0xe82990e: Eighth case (lea r12,[rcx+r8], call, lea rax,[rbx+0xd170], jmp 0xe827f03)
    // 0xe8298e1  lea r12,[rcx+r8]                              
    // 0xe8298e5  xor edx,edx                                   
    // 0xe8298e7  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe8298ec  mov rax,[rbx+0x98]                            
    // 0xe8298f3  mov [rax],r12                                 
    // 0xe8298f6  mov r13,[rbx+0xA8]                            
    // 0xe8298fd  mov rax,[r13]                                 
    // 0xe829901  add rdi,rsi                                   
    // 0xe829904  add rdi,rax                                   
    // 0xe829907  lea rax,[rbx+0xd170]                          
    // 0xe82990e  jmp 0xE827F03                                 ; -> sub_e827f03
    // -------------------------------------------------------------------------
    // 0xe8298e1..0xe82990e
    r12 = reinterpret_cast<void*>(rcx + r8);                     // 0xe8298e1  lea r12,[rcx+r8]
    rdx = 0;                                                     // 0xe8298e5  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe8298e7  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe8298ec  mov rax,[rbx+0x98]
    slot64(rax, 0) = reinterpret_cast<uint64_t>(r12);            // 0xe8298f3  mov [rax],r12
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe8298f6  mov r13,[rbx+0xA8]
    rax = slot64(r13, 0);                                        // 0xe8298fd  mov rax,[r13]
    rdi += rsi;                                                  // 0xe829901  add rdi,rsi
    rdi += rax;                                                  // 0xe829904  add rdi,rax
    rax = reinterpret_cast<uint64_t>(rbx_ptr(rbx, 0xD170));      // 0xe829907  lea rax,[rbx+0xd170]
    // 0xe82990e  jmp 0xe827f03 - target in previous chunk (c02)

    // -------------------------------------------------------------------------
    // 0xe829913..0xe829940: Ninth case (lea r12,[rax+r8], mov rcx,rax, call, jmp 0xe8299d0 with rdx=[rbx+0x2f0])
    // 0xe829913  lea r12,[rax+r8]                              
    // 0xe829917  mov rcx,rax                                   
    // 0xe82991a  xor edx,edx                                   
    // 0xe82991c  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe829921  mov rax,[rbx+0x98]                            
    // 0xe829928  mov [rax],r12                                 
    // 0xe82992b  mov r13,[rbx+0xA8]                            
    // 0xe829932  mov rcx,[r13]                                 
    // 0xe829936  add rcx,rdi                                   
    // 0xe829939  mov rdx,[rbx+0x2f0]                           
    // 0xe829940  jmp 0xE8299D0                                 ; -> loc_e8299d0
    // -------------------------------------------------------------------------
    // 0xe829913..0xe829940
    r12 = reinterpret_cast<void*>(rax + r8);                     // 0xe829913  lea r12,[rax+r8]
    rcx = rax;                                                   // 0xe829917  mov rcx,rax
    rdx = 0;                                                     // 0xe82991a  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe82991c  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe829921  mov rax,[rbx+0x98]
    slot64(rax, 0) = reinterpret_cast<uint64_t>(r12);            // 0xe829928  mov [rax],r12
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe82992b  mov r13,[rbx+0xA8]
    rcx = slot64(r13, 0);                                        // 0xe829932  mov rcx,[r13]
    rcx += rdi;                                                  // 0xe829936  add rcx,rdi
    rdx = slot64(rbx, 0x2F0);                                    // 0xe829939  mov rdx,[rbx+0x2f0]
    // 0xe829940  jmp 0xe8299d0 - handled later

    // -------------------------------------------------------------------------
    // 0xe829945..0xe829972: Tenth case (lea rdi,[rax+r8], mov rcx,rax, call, jmp 0xe8299d0 with rdx=[rbx+0x2f0])
    // 0xe829945  lea rdi,[rax+r8]                              
    // 0xe829949  mov rcx,rax                                   
    // 0xe82994c  xor edx,edx                                   
    // 0xe82994e  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe829953  mov rax,[rbx+0x98]                            
    // 0xe82995a  mov [rax],rdi                                 
    // 0xe82995d  mov r13,[rbx+0xA8]                            
    // 0xe829964  mov rcx,[r13]                                 
    // 0xe829968  add rcx,r12                                   
    // 0xe82996b  mov rdx,[rbx+0x2f0]                           
    // 0xe829972  jmp 0xE8299D0                                 ; -> loc_e8299d0
    // -------------------------------------------------------------------------
    // 0xe829945..0xe829972
    rdi = reinterpret_cast<uint64_t>(rax + r8);                  // 0xe829945  lea rdi,[rax+r8]
    rcx = rax;                                                   // 0xe829949  mov rcx,rax
    rdx = 0;                                                     // 0xe82994c  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe82994e  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe829953  mov rax,[rbx+0x98]
    slot64(rax, 0) = rdi;                                        // 0xe82995a  mov [rax],rdi
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe82995d  mov r13,[rbx+0xA8]
    rcx = slot64(r13, 0);                                        // 0xe829964  mov rcx,[r13]
    rcx += reinterpret_cast<uint64_t>(r12);                      // 0xe829968  add rcx,r12
    rdx = slot64(rbx, 0x2F0);                                    // 0xe82996b  mov rdx,[rbx+0x2f0]
    // 0xe829972  jmp 0xe8299d0 - handled later

    // -------------------------------------------------------------------------
    // 0xe829974..0xe8299a1: Eleventh case (lea r12,[rax+r8], mov rcx,rax, call, jmp 0xe8299d0 with rdx=[rbx+0x5c0])
    // 0xe829974  lea r12,[rax+r8]                              
    // 0xe829978  mov rcx,rax                                   
    // 0xe82997b  xor edx,edx                                   
    // 0xe82997d  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe829982  mov rax,[rbx+0x98]                            
    // 0xe829989  mov [rax],r12                                 
    // 0xe82998c  mov r13,[rbx+0xA8]                            
    // 0xe829993  mov rcx,[r13]                                 
    // 0xe829997  add rcx,rdi                                   
    // 0xe82999a  mov rdx,[rbx+0x5c0]                           
    // 0xe8299a1  jmp 0xE8299D0                                 ; -> loc_e8299d0
    // -------------------------------------------------------------------------
    // 0xe829974..0xe8299a1
    r12 = reinterpret_cast<void*>(rax + r8);                     // 0xe829974  lea r12,[rax+r8]
    rcx = rax;                                                   // 0xe829978  mov rcx,rax
    rdx = 0;                                                     // 0xe82997b  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe82997d  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe829982  mov rax,[rbx+0x98]
    slot64(rax, 0) = reinterpret_cast<uint64_t>(r12);            // 0xe829989  mov [rax],r12
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe82998c  mov r13,[rbx+0xA8]
    rcx = slot64(r13, 0);                                        // 0xe829993  mov rcx,[r13]
    rcx += rdi;                                                  // 0xe829997  add rcx,rdi
    rdx = slot64(rbx, 0x5C0);                                    // 0xe82999a  mov rdx,[rbx+0x5c0]
    // 0xe8299a1  jmp 0xe8299d0 - handled later

    // -------------------------------------------------------------------------
    // 0xe8299a3..0xe8299d8: Twelfth case (lea rdi,[rax+r8], mov rcx,rax, call, mov r8,rsi, call 0xeec6ec0, jmp 0xe827f10)
    // 0xe8299a3  lea rdi,[rax+r8]                              
    // 0xe8299a7  mov rcx,rax                                   
    // 0xe8299aa  xor edx,edx                                   
    // 0xe8299ac  call 0xEEC6ED0                                ; -> sub_eec6ed0
    // 0xe8299b1  mov rax,[rbx+0x98]                            
    // 0xe8299b8  mov [rax],rdi                                 
    // 0xe8299bb  mov r13,[rbx+0xA8]                            
    // 0xe8299c2  mov rcx,[r13]                                 
    // 0xe8299c6  add rcx,r12                                   
    // 0xe8299c9  mov rdx,[rbx+0x5c0]                           
    // 0xe8299d0  mov r8,rsi                                    
    // 0xe8299d3  call 0xEEC6EC0                                ; -> sub_eec6ec0
    // 0xe8299d8  jmp 0xE827F10                                 ; -> sub_e827f10
    // -------------------------------------------------------------------------
    // 0xe8299a3..0xe8299d8
    rdi = reinterpret_cast<uint64_t>(rax + r8);                  // 0xe8299a3  lea rdi,[rax+r8]
    rcx = rax;                                                   // 0xe8299a7  mov rcx,rax
    rdx = 0;                                                     // 0xe8299aa  xor edx,edx
    sub_eec6ed0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx)); // 0xe8299ac  call 0xeec6ed0
    rax = slot64(rbx, 0x98);                                     // 0xe8299b1  mov rax,[rbx+0x98]
    slot64(rax, 0) = rdi;                                        // 0xe8299b8  mov [rax],rdi
    r13 = reinterpret_cast<void*>(slot64(rbx, 0xA8));            // 0xe8299bb  mov r13,[rbx+0xA8]
    rcx = slot64(r13, 0);                                        // 0xe8299c2  mov rcx,[r13]
    rcx += reinterpret_cast<uint64_t>(r12);                      // 0xe8299c6  add rcx,r12
    rdx = slot64(rbx, 0x5C0);                                    // 0xe8299c9  mov rdx,[rbx+0x5c0]
    r8 = rsi;                                                    // 0xe8299d0  mov r8,rsi
    sub_eec6ec0(reinterpret_cast<void*>(rcx), reinterpret_cast<void*>(rdx), reinterpret_cast<void*>(r8)); // 0xe8299d3  call 0xeec6ec0
    // 0xe8299d8  jmp 0xe827f10 - target in previous chunk

    // TODO: Continue with remaining blocks (0xe8299dd..0xe82af92)

    // Pack state back
    // Pack state back
    s.rbx = rbx;
    s.rbp = rbp;
    s.rcx = rcx;
    s.rdx = rdx;
    s.rsi = rsi;
    s.rdi = rdi;
    s.rax = rax;
    s.r8 = r8;
    s.r9 = r9;
    s.r10 = r10;
    s.r11 = r11;
    s.r12 = r12;
    s.r13 = r13;
    s.r14 = r14;
    s.r15 = r15;
    s.xmm8 = xmm8;
    s.xmm9 = xmm9;
    s.al_flags = al;
}

} // namespace d3d12
} // namespace native

#define LIFT_FN(name, rva) \
    namespace native { namespace registry { \
    struct name##_entry { \
        static constexpr uintptr_t rva = rva; \
        static constexpr const char* symbol = #name; \
        static constexpr int mode = 2; \
        name##_entry() { } \
    }; \
    static name##_entry name##_instance; \
    } }

LIFT_FN(sub_e824fbe_chunk_c03, 0xe8297a2)

static_assert(true, "sub_e824fbe chunk c03 - part 1 written, continue appending");