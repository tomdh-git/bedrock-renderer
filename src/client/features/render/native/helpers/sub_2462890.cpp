// LIFT 0x2462890 size 0xc5 1.26.62.01 sub_2462890
#include "sub_2462890.h"
#include "client/features/render/native/Lift.h"
namespace native {
static_assert(sizeof(void*) == 8, "sub_2462890: x64 pointer-sized ABI");
// Verbatim instructions of the function (matches rdis dis 0x2462890 0xc5):
#if 0
0x2462890  push r14                                      
0x2462892  push rsi                                      
0x2462893  push rdi                                      
0x2462894  push rbx                                      
0x2462895  sub rsp,0x48                                  
0x2462899  movaps [rsp+0x30],xmm6                        
0x246289e  mov rsi,rcx                                   
0x24628a1  mov rax,[rcx]                                 
0x24628a4  mov rcx,[rax+8]                               
0x24628a8  mov qword ptr [rcx],0                         
0x24628af  mov rdi,[rax]                                 
0x24628b2  test rdi,rdi                                  
0x24628b5  je short 0x2462920                            
0x24628b7  xorps xmm6,xmm6                               
0x24628ba  jmp short 0x24628EA                           
0x24628bc  nop [rax]                                     
0x24628c0  lea r14,[rdi+0x18]                            
0x24628c4  call 0xE935700                                
0x24628c9  movups [r14],xmm6                             
0x24628cd  mov qword ptr [r14+0x10],0                    
0x24628d5  mov edx,0x30                                  
0x24628da  mov rcx,rdi                                   
0x24628dd  call 0xE935700                                
0x24628e2  mov rdi,rbx                                   
0x24628e5  test rbx,rbx                                  
0x24628e8  je short 0x2462920                            
0x24628ea  mov rbx,[rdi]                                 
0x24628ed  mov rcx,[rdi+0x18]                            
0x24628f1  test rcx,rcx                                  
0x24628f4  je short 0x24628D5                            
0x24628f6  mov rdx,[rdi+0x28]                            
0x24628fa  sub rdx,rcx                                   
0x24628fd  cmp rdx,0x1000                                
0x2462904  jb short 0x24628C0                            
0x2462906  mov rax,[rcx-8]                               
0x246290a  add rcx,0xFFFFFFFFFFFFFFF8                    
0x246290e  sub rcx,rax                                   
0x2462911  cmp rcx,0x20                                  
0x2462915  jae short 0x246293B                           
0x2462917  add rdx,0x27                                  
0x246291b  mov rcx,rax                                   
0x246291e  jmp short 0x24628C0                           
0x2462920  mov rcx,[rsi]                                 
0x2462923  mov edx,0x30                                  
0x2462928  movaps xmm6,[rsp+0x30]                        
0x246292d  add rsp,0x48                                  
0x2462931  pop rbx                                       
0x2462932  pop rdi                                       
0x2462933  pop rsi                                       
0x2462934  pop r14                                       
0x2462936  jmp 0xE935700                                 
0x246293b  mov qword ptr [rsp+0x20],0                    
0x2462944  xor ecx,ecx                                   
0x2462946  xor edx,edx                                   
0x2462948  xor r8d,r8d                                   
0x246294b  xor r9d,r9d                                   
0x246294e  call qword ptr [0xF9A8C78]                    
0x2462954  int3                                          
#endif
void* sub_2462890(void* a0)
{
    void* const thisPtr = a0;
    void* const objVtable = *reinterpret_cast<void* const volatile*>(thisPtr);
    void* const statePtr = *reinterpret_cast<void* const volatile*>(reinterpret_cast<uint8_t*>(objVtable) + sub_2462890Layout::vtable_statePtr);
    *reinterpret_cast<void* volatile*>(statePtr) = nullptr;
    void* const head = *reinterpret_cast<void* const volatile*>(objVtable);
    if (head == nullptr) goto tail;
    void* node;
    node = head;
    for (;;) {
        void* const next = *reinterpret_cast<void* const volatile*>(node);
        void* const start = *reinterpret_cast<void* const volatile*>(reinterpret_cast<uint8_t*>(node) + sub_2462890Layout::node_start);
        if (start == nullptr) {
            sub_e935700(node);
            node = next;
            if (node == nullptr) goto tail;
            continue;
        }
        void* const end = *reinterpret_cast<void* const volatile*>(reinterpret_cast<uint8_t*>(node) + sub_2462890Layout::node_end);
        const uintptr_t remaining = reinterpret_cast<uintptr_t>(end) - reinterpret_cast<uintptr_t>(start);
        void* chunkArg = start;
        if (remaining < 0x1000) {
        } else {
            const uintptr_t before = *reinterpret_cast<uintptr_t const volatile*>(reinterpret_cast<uint8_t*>(start) - 8);
            const uintptr_t delta = (reinterpret_cast<uintptr_t>(start) - 8) - before;
            if (delta >= 0x20) goto fail;
            chunkArg = reinterpret_cast<void*>(before);
        }
        sub_e935700(chunkArg);
        *reinterpret_cast<uint64_t volatile*>(start) = 0;
        *reinterpret_cast<uint64_t volatile*>(reinterpret_cast<uint8_t*>(start) + 8) = 0;
        *reinterpret_cast<uint64_t volatile*>(reinterpret_cast<uint8_t*>(start) + 0x10) = 0;
        sub_e935700(node);
        node = next;
        if (node == nullptr) goto tail;
    }
    __assume(false);
tail:
    return sub_e935700(objVtable);
fail:
    {
        void* const home5 = nullptr;
        (void)home5;
        using FailFn = void (__cdecl)(void*, void*, void*, void*);
        FailFn* const failFn = reinterpret_cast<FailFn*>(*reinterpret_cast<uintptr_t const volatile*>(0x14F9A8C78ULL));
        failFn(nullptr, nullptr, nullptr, nullptr);
        __debugbreak();
        return nullptr;
    }
}
LIFT_FN(sub_2462890, "sub_2462890", 0x2462890, native::sub_2462890, nullptr);
}
