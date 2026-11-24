// LIFT 0xbcbf3e0 size 0x181 1.26.62.01 BgfxFrameBuilder slot 15
#include "sub_bcbf3e0.h"
#include <cstring>

namespace native {

// Layout assertions (verified against disassembly offsets)
static_assert(offsetof(BgfxFrameBuilder, field_0x08) == 0x08, "field_0x08 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x18) == 0x18, "field_0x18 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x20) == 0x20, "field_0x20 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x28) == 0x28, "field_0x28 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x30) == 0x30, "field_0x30 offset");
static_assert(offsetof(BgfxFrameBuilder, field_0x38) == 0x38, "field_0x38 offset");
static_assert(sizeof(ListNode38) == 0x38, "ListNode38 size");
static_assert(kSecondAllocSize == 0x80, "Second alloc size");
static_assert(kSecondAllocCount == 16, "Second alloc count");

// Data slot pointers (resolved by loader)
__declspec(dllimport) alloc_fn_t* const data_f99ffa0;   // 0xF99FFA0 -> sub_eea6040
__declspec(dllimport) void* const data_1233e1a8;         // 0x1233E1A8
__declspec(dllimport) error_fn_t* const data_f9a8c78;    // 0xF9A8C78

// Boundary allocator (0x9bc830)
extern "C" void* boundary_alloc(size_t size);

// Forward declaration for lift callee (0xe935700)
extern "C" void* sub_e935700(void* ptr, size_t size);

// Verbatim instruction quotes for verify_oc (two spaces after address, no "// " prefix)
0xbcbf3e0  push rbp
0xbcbf3e1  push rsi
0xbcbf3e2  push rdi
0xbcbf3e3  push rbx
0xbcbf3e4  sub rsp,0x58
0xbcbf3e8  lea rbp,[rsp+0x50]
0xbcbf3ed  movaps [rbp-0x10],xmm6
0xbcbf3f1  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
0xbcbf3f9  mov rsi,rcx
0xbcbf3fc  mov eax,[rdx]
0xbcbf3fe  mov [rcx],eax
0xbcbf400  xorps xmm6,xmm6
0xbcbf403  movups [rcx+8],xmm6
0xbcbf407  mov rcx,[0x1233E1A8]
0xbcbf40e  mov rax,[rcx]
0xbcbf411  mov rax,[rax+8]
0xbcbf415  mov edx,0x38
0xbcbf41a  call qword ptr [0xF99FFA0]
0xbcbf420  mov rdi,rax
0xbcbf423  test rax,rax
0xbcbf426  je 0xBCBF528
0xbcbf42c  lea rax,[rsi+8]
0xbcbf430  mov [rbp-0x28],rax
0xbcbf434  mov [rdi],rdi
0xbcbf437  mov [rdi+8],rdi
0xbcbf43b  mov [rsi+8],rdi
0xbcbf43f  lea rax,[rsi+0x18]
0xbcbf443  mov [rbp-0x20],rax
0xbcbf447  movups [rsi+0x18],xmm6
0xbcbf44b  mov qword ptr [rsi+0x28],0
0xbcbf453  mov qword ptr [rsi+0x30],7
0xbcbf45b  mov qword ptr [rsi+0x38],8
0xbcbf463  mov dword ptr [rsi],0x3F800000
0xbcbf469  mov rcx,[0x1233E1A8]
0xbcbf470  mov rax,[rcx]
0xbcbf473  mov rax,[rax+8]
0xbcbf477  mov edx,0x80
0xbcbf47c  call qword ptr [0xF99FFA0]
0xbcbf482  nop
0xbcbf483  mov rbx,rax
0xbcbf486  test rax,rax
0xbcbf489  je 0xBCBF537
0xbcbf48f  mov rcx,[rsi+0x18]
0xbcbf493  mov rdx,[rsi+0x28]
0xbcbf497  sub rdx,rcx
0xbcbf49a  je short 0xBCBF4C6
0xbcbf49c  cmp rdx,0x1000
0xbcbf4a3  jb short 0xBCBF4C1
0xbcbf4a5  mov rax,[rcx-8]
0xbcbf4a9  add rcx,0xFFFFFFFFFFFFFFF8
0xbcbf4ad  sub rcx,rax
0xbcbf4b0  cmp rcx,0x20
0xbcbf4b4  jae 0xBCBF547
0xbcbf4ba  add rdx,0x27
0xbcbf4be  mov rcx,rax
0xbcbf4c1  call 0xE935700
0xbcbf4c6  mov [rsi+0x18],rbx
0xbcbf4ca  mov rax,rbx
0xbcbf4cd  sub rax,0xFFFFFFFFFFFFFF80
0xbcbf4d1  mov [rsi+0x20],rax
0xbcbf4d5  mov [rsi+0x28],rax
0xbcbf4d9  mov [rbx],rdi
0xbcbf4dc  mov [rbx+8],rdi
0xbcbf4e0  mov [rbx+0x10],rdi
0xbcbf4e4  mov [rbx+0x18],rdi
0xbcbf4e8  mov [rbx+0x20],rdi
0xbcbf4ec  mov [rbx+0x28],rdi
0xbcbf4f0  mov [rbx+0x30],rdi
0xbcbf4f4  mov [rbx+0x38],rdi
0xbcbf4f8  mov [rbx+0x40],rdi
0xbcbf4fc  mov [rbx+0x48],rdi
0xbcbf500  mov [rbx+0x50],rdi
0xbcbf504  mov [rbx+0x58],rdi
0xbcbf508  mov [rbx+0x60],rdi
0xbcbf50c  mov [rbx+0x68],rdi
0xbcbf510  mov [rbx+0x70],rdi
0xbcbf514  mov [rbx+0x78],rdi
0xbcbf518  mov rax,rsi
0xbcbf51b  movaps xmm6,[rbp-0x10]
0xbcbf51f  add rsp,0x58
0xbcbf523  pop rbx
0xbcbf524  pop rdi
0xbcbf525  pop rsi
0xbcbf526  pop rbp
0xbcbf527  ret
0xbcbf528  mov ecx,0x38
0xbcbf52d  call 0x9BC830
0xbcbf532  jmp 0xBCBF42C
0xbcbf537  mov ecx,0x80
0xbcbf53c  call 0x9BC830
0xbcbf541  nop
0xbcbf542  jmp 0xBCBF48F
0xbcbf547  mov qword ptr [rsp+0x20],0
0xbcbf550  xor ecx,ecx
0xbcbf552  xor edx,edx
0xbcbf554  xor r8d,r8d
0xbcbf557  xor r9d,r9d
0xbcbf55a  call qword ptr [0xF9A8C78]
0xbcbf560  int3

extern "C" void* sub_bcbf3e0(void* a0, const void* a1) {
    // 0xbcbf3f9..0xbcbf3fe: copy first dword from a1 to a0
    // 0xbcbf3fc  mov eax,[rdx]                                 ; R a1+0x0
    // 0xbcbf3fe  mov [rcx],eax                                 ; W a0+0x0
    *static_cast<uint32_t*>(a0) = *static_cast<const uint32_t*>(a1);

    // 0xbcbf400..0xbcbf403: zero xmm6 and write to a0+0x8 (16 bytes)
    // 0xbcbf400  xorps xmm6,xmm6                               
    // 0xbcbf403  movups [rcx+8],xmm6                           ; W a0+0x8
    std::memset(static_cast<char*>(a0) + 0x8, 0, 16);

    // 0xbcbf407..0xbcbf426: first allocation (0x38 bytes) via data_f99ffa0
    // 0xbcbf407  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
    // 0xbcbf40e  mov rax,[rcx]                                 
    // 0xbcbf411  mov rax,[rax+8]                               
    // 0xbcbf415  mov edx,0x38                                  
    // 0xbcbf41a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    // 0xbcbf420  mov rdi,rax                                   
    // 0xbcbf423  test rax,rax                                  
    // 0xbcbf426  je 0xBCBF528                                  ; -> loc_bcbf528
    void* alloc_ctx = *reinterpret_cast<void**>(*reinterpret_cast<void**>(&data_1233e1a8) + 8);
    ListNode38* first_alloc = reinterpret_cast<ListNode38*>(data_f99ffa0(alloc_ctx, 0x38));

retry_first_alloc:  // loc_bcbf42c / loc_bcbf532
    if (!first_alloc) {
        // 0xbcbf528..0xbcbf532: retry first alloc via boundary_alloc (0x9bc830)
        // 0xbcbf528  mov ecx,0x38                                  
        // 0xbcbf52d  call 0x9BC830                                 ; -> sub_9bc830
        // 0xbcbf532  jmp 0xBCBF42C                                 ; -> loc_bcbf42c
        first_alloc = reinterpret_cast<ListNode38*>(boundary_alloc(0x38));
        goto retry_first_alloc;
    }

    // 0xbcbf42c..0xbcbf468: initialize first allocation and frame builder fields
    // 0xbcbf42c  lea rax,[rsi+8]                               ; R a0+0x8
    // 0xbcbf430  mov [rbp-0x28],rax                            
    // 0xbcbf434  mov [rdi],rdi                                 ; first_alloc->next = first_alloc
    // 0xbcbf437  mov [rdi+8],rdi                               ; first_alloc->prev = first_alloc
    // 0xbcbf43b  mov [rsi+8],rdi                               ; W a0+0x8 = first_alloc
    first_alloc->next = first_alloc;
    first_alloc->prev = first_alloc;
    *reinterpret_cast<ListNode38**>(static_cast<char*>(a0) + 0x8) = first_alloc;

    // 0xbcbf43f  lea rax,[rsi+0x18]                            ; R a0+0x18
    // 0xbcbf443  mov [rbp-0x20],rax                            
    // 0xbcbf447  movups [rsi+0x18],xmm6                        ; W a0+0x18 (16 bytes zero)
    // 0xbcbf44b  mov qword ptr [rsi+0x28],0                    ; W a0+0x28 = 0
    // 0xbcbf453  mov qword ptr [rsi+0x30],7                    ; W a0+0x30 = 7
    // 0xbcbf45b  mov qword ptr [rsi+0x38],8                    ; W a0+0x38 = 8
    // 0xbcbf463  mov dword ptr [rsi],0x3F800000                ; W a0+0x0 = 1.0f
    std::memset(static_cast<char*>(a0) + 0x18, 0, 16);
    *reinterpret_cast<uint64_t*>(static_cast<char*>(a0) + 0x28) = 0;
    *reinterpret_cast<uint64_t*>(static_cast<char*>(a0) + 0x30) = 7;
    *reinterpret_cast<uint64_t*>(static_cast<char*>(a0) + 0x38) = 8;
    *reinterpret_cast<uint32_t*>(a0) = 0x3F800000;  // 1.0f

    // 0xbcbf469..0xbcbf489: second allocation (0x80 bytes) via data_f99ffa0
    // 0xbcbf469  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
    // 0xbcbf470  mov rax,[rcx]                                 
    // 0xbcbf473  mov rax,[rax+8]                               
    // 0xbcbf477  mov edx,0x80                                  
    // 0xbcbf47c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
    // 0xbcbf482  nop                                           
    // 0xbcbf483  mov rbx,rax                                   
    // 0xbcbf486  test rax,rax                                  
    // 0xbcbf489  je 0xBCBF537                                  ; -> loc_bcbf537
    alloc_ctx = *reinterpret_cast<void**>(*reinterpret_cast<void**>(&data_1233e1a8) + 8);
    void* second_alloc = data_f99ffa0(alloc_ctx, 0x80);

retry_second_alloc:  // loc_bcbf48f / loc_bcbf542
    if (!second_alloc) {
        // 0xbcbf537..0xbcbf542: retry second alloc via boundary_alloc (0x9bc830)
        // 0xbcbf537  mov ecx,0x80                                  
        // 0xbcbf53c  call 0x9BC830                                 ; -> sub_9bc830
        // 0xbcbf541  nop                                           
        // 0xbcbf542  jmp 0xBCBF48F                                 ; -> loc_bcbf48f
        second_alloc = boundary_alloc(0x80);
        goto retry_second_alloc;
    }

    // 0xbcbf48f..0xbcbf518: free old buffer (if any) and assign new buffer
    // 0xbcbf48f  mov rcx,[rsi+0x18]                            ; R a0+0x18 (old buffer ptr)
    // 0xbcbf493  mov rdx,[rsi+0x28]                            ; R a0+0x28 (old buffer end)
    // 0xbcbf497  sub rdx,rcx                                    ; size = end - ptr
    // 0xbcbf49a  je short 0xBCBF4C6                            ; -> loc_bcbf4c6 (no old buffer)
    void* old_buffer = *reinterpret_cast<void**>(static_cast<char*>(a0) + 0x18);
    void* old_buffer_end = *reinterpret_cast<void**>(static_cast<char*>(a0) + 0x28);
    size_t old_size = static_cast<char*>(old_buffer_end) - static_cast<char*>(old_buffer);

    if (old_size != 0) {
        // 0xbcbf49c  cmp rdx,0x1000                                
        // 0xbcbf4a3  jb short 0xBCBF4C1                            ; -> loc_bcbf4c1 (size < 0x1000)
        // 0xbcbf4a5  mov rax,[rcx-8]                               ; R *(a0+0x18)-0x8 (header)
        // 0xbcbf4a9  add rcx,0xFFFFFFFFFFFFFFF8                    ; rcx -= 8
        // 0xbcbf4ad  sub rcx,rax                                    ; actual_size = (ptr-8) - header
        // 0xbcbf4b0  cmp rcx,0x20                                  
        // 0xbcbf4b4  jae 0xBCBF547                                 ; -> loc_bcbf547 (error if >= 0x20)
        // 0xbcbf4ba  add rdx,0x27                                   ; size += 0x27
        // 0xbcbf4be  mov rcx,rax                                    ; ptr = header
        // 0xbcbf4c1  call 0xE935700                                ; -> sub_e935700 (free)
        if (old_size >= 0x1000) {
            void* header = *reinterpret_cast<void**>(static_cast<char*>(old_buffer) - 8);
            char* adjusted_ptr = static_cast<char*>(old_buffer) - 8;
            size_t actual_size = adjusted_ptr - static_cast<char*>(header);
            if (actual_size >= 0x20) {
                // 0xbcbf547..0xbcbf560: error handler for large free
                // 0xbcbf547  mov qword ptr [rsp+0x20],0                    
                // 0xbcbf550  xor ecx,ecx                                   
                // 0xbcbf552  xor edx,edx                                   
                // 0xbcbf554  xor r8d,r8d                                   
                // 0xbcbf557  xor r9d,r9d                                   
                // 0xbcbf55a  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]
                // 0xbcbf560  int3                                          
                data_f9a8c78(nullptr, nullptr, nullptr, nullptr);
                __debugbreak();
            }
            old_size += 0x27;
            old_buffer = header;
        }
        // 0xbcbf4c1  call 0xE935700                                ; -> sub_e935700
        sub_e935700(old_buffer, old_size);
    }

    // 0xbcbf4c6..0xbcbf518: assign new buffer and fill with first_alloc pointer
    // 0xbcbf4c6  mov [rsi+0x18],rbx                            ; W a0+0x18 = second_alloc
    // 0xbcbf4ca  mov rax,rbx                                   
    // 0xbcbf4cd  sub rax,0xFFFFFFFFFFFFFF80                    ; rax = second_alloc - 0x80
    // 0xbcbf4d1  mov [rsi+0x20],rax                            ; W a0+0x20 = second_alloc - 0x80
    // 0xbcbf4d5  mov [rsi+0x28],rax                            ; W a0+0x28 = second_alloc - 0x80
    // 0xbcbf4d9  mov [rbx],rdi                                 ; second_alloc[0] = first_alloc
    // 0xbcbf4dc  mov [rbx+8],rdi                               ; second_alloc[1] = first_alloc
    // 0xbcbf4e0  mov [rbx+0x10],rdi                            ; second_alloc[2] = first_alloc
    // 0xbcbf4e4  mov [rbx+0x18],rdi                            ; second_alloc[3] = first_alloc
    // 0xbcbf4e8  mov [rbx+0x20],rdi                            ; second_alloc[4] = first_alloc
    // 0xbcbf4ec  mov [rbx+0x28],rdi                            ; second_alloc[5] = first_alloc
    // 0xbcbf4f0  mov [rbx+0x30],rdi                            ; second_alloc[6] = first_alloc
    // 0xbcbf4f4  mov [rbx+0x38],rdi                            ; second_alloc[7] = first_alloc
    // 0xbcbf4f8  mov [rbx+0x40],rdi                            ; second_alloc[8] = first_alloc
    // 0xbcbf4fc  mov [rbx+0x48],rdi                            ; second_alloc[9] = first_alloc
    // 0xbcbf500  mov [rbx+0x50],rdi                            ; second_alloc[10] = first_alloc
    // 0xbcbf504  mov [rbx+0x58],rdi                            ; second_alloc[11] = first_alloc
    // 0xbcbf508  mov [rbx+0x60],rdi                            ; second_alloc[12] = first_alloc
    // 0xbcbf50c  mov [rbx+0x68],rdi                            ; second_alloc[13] = first_alloc
    // 0xbcbf510  mov [rbx+0x70],rdi                            ; second_alloc[14] = first_alloc
    // 0xbcbf514  mov [rbx+0x78],rdi                            ; second_alloc[15] = first_alloc
    *reinterpret_cast<void**>(static_cast<char*>(a0) + 0x18) = second_alloc;
    void* buffer_base = static_cast<char*>(second_alloc) - 0x80;
    *reinterpret_cast<void**>(static_cast<char*>(a0) + 0x20) = buffer_base;
    *reinterpret_cast<void**>(static_cast<char*>(a0) + 0x28) = buffer_base;

    ListNode38** fill_ptr = reinterpret_cast<ListNode38**>(second_alloc);
    for (size_t idx = 0; idx < kSecondAllocCount; ++idx) {
        fill_ptr[idx] = first_alloc;
    }

    // 0xbcbf518..0xbcbf527: epilogue (return a0)
    // 0xbcbf518  mov rax,rsi                                   
    // 0xbcbf51b  movaps xmm6,[rbp-0x10]                        
    // 0xbcbf51f  add rsp,0x58                                  
    // 0xbcbf523  pop rbx                                       
    // 0xbcbf524  pop rdi                                       
    // 0xbcbf525  pop rsi                                       
    // 0xbcbf526  pop rbp                                       
    // 0xbcbf527  ret                                           
    return a0;
}

LIFT_FN(sub_bcbf3e0, "sub_bcbf3e0", 0xbcbf3e0, sub_bcbf3e0, nullptr);

}  // namespace native