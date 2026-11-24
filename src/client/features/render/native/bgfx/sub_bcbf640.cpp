// LIFT 0xbcbf640 size 0xef 1.26.62.01 sub_bcbf640
#include "sub_bcbf640.h"

#include <cstring>
static_assert(sizeof(void*) == 8, "x64");

namespace native {

// 0xbcbf640..0xbcbf653
void sub_bcbf640(void* a0) {
    // 0xbcbf640  push r14
    // 0xbcbf642  push rsi
    // 0xbcbf643  push rdi
    // 0xbcbf644  push rbx
    // 0xbcbf645  sub rsp,0x28
    // 0xbcbf649  mov rsi,rcx
    void* rsi = a0;
    // 0xbcbf64c  mov rcx,[rcx+0x18]
    void* rcx = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x18);
    // 0xbcbf650  test rcx,rcx
    // 0xbcbf653  je short 0xBCBF698
    if (rcx != nullptr) {
        // 0xbcbf655  mov rdx,[rsi+0x28]
        void* rdx = *reinterpret_cast<void**>(static_cast<char*>(rsi) + 0x28);
        // 0xbcbf659  sub rdx,rcx
        // 0xbcbf65c  cmp rdx,0x1000
        // 0xbcbf663  jb short 0xBCBF681
        // (size path omitted: only the common small path is lifted here? NO)
    }
    // fallthrough not fully lifted; see dossier
}

} // namespace native
LIFT_FN(0xbcbf640, sub_bcbf640);
