// CHUNK 0xe8292b7..0xe82aaab
#include "client/features/render/native/d3d12/sub_e824ab7_chunk_c03.h"

#include <cstdint>
#include <cstring>

namespace native::d3d12 {

// Entry: 0xe8292b7  (sub_e8292b7 listing; body continues through 0xe82aaab)
// Lifted chunk state is passed by pointer; r13/r14/r15/rsi/rdi/rcx/rdx/r8/r9
// are carried in/out via ChunkState_e824ab7_c03.
void sub_e824ab7_chunk_c03(ChunkState_e824ab7_c03* st) {
    // Range 0xe8292b7..0xe829314: matrix/SIMD store paths via sub_47e8f0 grow + sub_eec6ed0 memcpy.
    // Range 0xe829315..0xe829530: continuation store paths (sub_eec6ed0, sub_eec6ec0).
    // Range 0xe829531..0xe8299d8: jump-dispatched matrix paths (sub_47e8f0 grow, sub_eec6ed0, sub_eec6ec0).
    // Range 0xe8299dd..0xe829c90: texture/buffer upload path (vendor alloc via [0xF99FFA0]).
    // Range 0xe829c90..0xe829e3e: index/vertex setup path.
    // Range 0xe829e3e..0xe82a3e2: render-state path (sub_e81e1c0 lift at 0xe82a40f/0xe82a485).
    // Range 0xe82a3e3..0xe82a49e: sub_e81e1c0 calls + state writes.
    // Range 0xe82a49e..0xe82a4f7: loop setup over r14 byte array; jump table at 0xF4EE7F8.
    // Range 0xe82a4f7..0xe82aaab: SIMD matrix math (two blocks) writing 0x90B0/0x90C0/0x90D0/0x90E0
    //   and 0x9130/0x9140/0x9150/0x9160; final vector store via sub_eec6ec0.
    (void)st;
}


#if 0
0xe82930a  call 0x47E8F0                                 ; -> sub_47e8f0
0xe829364  call 0x47E8F0                                 ; -> sub_47e8f0
0xe8293be  call 0x47E8F0                                 ; -> sub_47e8f0
0xe829418  call 0x47E8F0                                 ; -> sub_47e8f0
0xe829472  call 0x47E8F0                                 ; -> sub_47e8f0
0xe8294cc  call 0x47E8F0                                 ; -> sub_47e8f0
0xe829526  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82953a  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829562  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829594  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8295c6  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8295f5  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829627  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe82964f  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe82968e  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8296b6  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8296ed  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829715  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829747  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829779  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8297a8  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8297d4  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829800  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe82982f  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829861  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829893  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8298c2  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8298e7  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe82991c  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe82994e  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe82997d  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8299ac  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe8299d3  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xe829a1e  call 0xE8360F0                                ; -> sub_e8360f0
0xe829a83  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829aa7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829b42  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xe829b71  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829be1  call r10                                      
0xe829c60  call r11                                      
0xe829c7d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829cb5  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe829da5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829dde  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829e06  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829e37  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829ec4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe829f60  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe82a079  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe82a0ed  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe82a132  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xe82a1f6  call 0xBC6A9D0                                ; -> sub_bc6a9d0
0xe82a393  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82a3c3  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe82a40f  call 0xE81E1C0                                ; -> sub_e81e1c0
0xe82a485  call 0xE81E1C0                                ; -> sub_e81e1c0
0xe82a4c4  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xe82a4f2  call 0xEEC6EC0                                ; -> sub_eec6ec0
0xe82a58a  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82a70f  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82a783  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82a7e0  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82a863  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82a8f3  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82ac21  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82af3a  call 0x47E8F0                                 ; -> sub_47e8f0
0xe82afb3  call 0x47E8F0                                 ; -> sub_47e8f0
#endif

} // namespace native::d3d12
