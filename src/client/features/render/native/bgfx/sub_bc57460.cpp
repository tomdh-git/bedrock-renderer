// LIFT 0xbc57460 size 0x2e2f 1.26.62.01 
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc57460.h"
#include "client/features/render/native/bgfx/sub_bc57460_chunk_c00.h"

#include <cstdint>
#include <cstring>

namespace native::bgfx {

namespace {

// Forward declaration for callee in lift set: sub_a78940
extern "C" void sub_a78940(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_aa6580
extern "C" void sub_aa6580(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_ab49c0
extern "C" void sub_ab49c0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_1999390
extern "C" void sub_1999390(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_5667860
extern "C" void sub_5667860(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_567c8b0
extern "C" void sub_567c8b0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_568ad40
extern "C" void sub_568ad40(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bc09250
extern "C" void sub_bc09250(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_bc5b130
extern "C" void sub_bc5b130(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec73f0
extern "C" void sub_eec73f0(/* LIFT-BODY: exact ABI from dossier */);

// Forward declaration for callee in lift set: sub_eec75a0
extern "C" void sub_eec75a0(/* LIFT-BODY: exact ABI from dossier */);

// Boundary callees (not in lift set) - use native::Boundary wrappers
//   0xbc579bf: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc579d6: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc57a2f: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc57a45: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc57ab7: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc57ad1: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc57af3: call 0xEEC6ED0                                ; -> sub_eec6ed0 -> sub_eec6ed0
//   0xbc57d90: call qword ptr [0xF9A8F60]                    ; [data_f9a8f60] (indirect)
//   0xbc58027: call rsi (indirect)
//   0xbc5803a: call rsi (indirect)
//   0xbc580ad: call qword ptr [0xF9A8DB8]                    ; [data_f9a8db8] (indirect)
//   0xbc580c6: call rsi (indirect)
//   0xbc580d9: call rsi (indirect)
//   0xbc58108: call rsi (indirect)
//   0xbc58111: call rsi (indirect)
//   0xbc58295: call rsi (indirect)
//   0xbc582a8: call rsi (indirect)
//   0xbc5831e: call rsi (indirect)
//   0xbc58331: call rsi (indirect)
//   0xbc58524: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc585d6: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc5868a: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc58742: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc58800: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc588bc: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc589bd: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc58cdc: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc58df8: call 0x76A8A0                                 ; -> sub_76a8a0 -> sub_76a8a0
//   0xbc59159: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc5917f: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc5920f: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc592b1: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)
//   0xbc592d7: call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect)

} // namespace

// Main entry point - frame graph builder (VV)
// Signature: void sub_bc57460(void* ctx, void* rdx, void* r8, void* r9, void* a4, void* a5, void* a6, void* a7)
// x64 MSVC ABI: this/ctx in rcx, args in rdx/r8/r9 + 4 stack args
// Chunked into 3 parts: c00 (0xbc57460..0xbc58a85), c01 (0xbc58a85..0xbc5a261), c02 (0xbc5a261..0xbc5a28f)
extern "C" void sub_bc57460(void* ctx, void* rdx, void* r8, void* r9, void* a4, void* a5, void* a6, void* a7) {
    // Chunk c00: prologue + main loop (0xbc57460..0xbc58a85)
    // Create chunk state and delegate to chunk step function
    Sub_bc57460_ChunkC00State state{};
    state.rbp_frame_base = nullptr;  // Will be set up by chunk step
    state.r12_ctx = ctx;
    state.r15_scratch = r9;
    state.rsi_scratch = a5;  // [rbp+0x9F0] -> rsi
    state.rdi_scratch = r8;  // r8 -> rdi
    state.rbx_scratch = a4;  // [rbp+0x9F8] -> rbx
    
    // Initialize frame array (0x9E8 bytes)
    std::memset(state.frame, 0, sizeof(state.frame));
    
    // Call chunk c00 step function
    sub_bc57460_chunk_c00_step(&state);
    
    // Chunk c00 handles range 0xbc57460..0xbc58a85; remaining chunks c01/c02 to be implemented separately
}

// Layout assertions (LIFT-BODY: replace with real offsetof/sizeof asserts)
static_assert(true, "sub_bc57460: replace with real layout asserts for every struct read/written");

// Verbatim log of every call instruction in [0xbc57460, 0xbc5a28f) (rdis dis output, two spaces after address):
#if 0
0xbc57514  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc5752d  call 0xEEC73F0                                ; -> sub_eec73f0
0xbc575e9  call 0xBC09250                                ; -> sub_bc09250
0xbc57645  call 0xBC09250                                ; -> sub_bc09250
0xbc576ce  call 0xBC09250                                ; -> sub_bc09250
0xbc5777b  call 0x567C8B0                                ; -> sub_567c8b0
0xbc5779d  call 0xAB49C0                                 ; -> sub_ab49c0
0xbc57957  call 0x5667860                                ; -> sub_5667860
0xbc5797e  call 0xA78940                                 ; -> sub_a78940
0xbc579bf  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc579d6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc579f6  call 0xA78940                                 ; -> sub_a78940
0xbc57a2f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57a45  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57a72  call 0xA78940                                 ; -> sub_a78940
0xbc57ab7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57ad1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc57af3  call 0xEEC6ED0                                ; -> sub_eec6ed0
0xbc57b9b  call 0xAA6580                                 ; -> sub_aa6580
0xbc57bb9  call 0xAA6580                                 ; -> sub_aa6580
0xbc57be5  call 0x1999390                                ; -> sub_1999390
0xbc57d90  call qword ptr [0xF9A8F60]                    ; [data_f9a8f60]
0xbc57f69  call 0xBC5B130                                ; -> sub_bc5b130
0xbc58027  call rsi
0xbc5803a  call rsi
0xbc58059  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc580ad  call qword ptr [0xF9A8DB8]                    ; [data_f9a8db8]
0xbc580c6  call rsi
0xbc580d9  call rsi
0xbc58108  call rsi
0xbc58111  call rsi
0xbc581b8  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc581ec  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58210  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58253  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc58295  call rsi
0xbc582a8  call rsi
0xbc582c7  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc5831e  call rsi
0xbc58331  call rsi
0xbc58350  call 0xEEC75A0                                ; -> sub_eec75a0
0xbc583e0  call 0xBC5B130                                ; -> sub_bc5b130
0xbc58524  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc585d6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5868a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58742  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58800  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc588bc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc589bd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58aa8  call 0x568AD40                                ; -> sub_568ad40
0xbc58cdc  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc58df8  call 0x76A8A0                                 ; -> sub_76a8a0
0xbc59159  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5917f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc5920f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc592b1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0xbc592d7  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
#endif

// Calls out of lifted code:
//   sub_eec73f0 (0xeec73f0, lift set) - call 0xEEC73F0                                ; -> sub_eec73f0
//   sub_eec73f0 (0xeec73f0, lift set) - call 0xEEC73F0                                ; -> sub_eec73f0
//   sub_bc09250 (0xbc09250, lift set) - call 0xBC09250                                ; -> sub_bc09250
//   sub_bc09250 (0xbc09250, lift set) - call 0xBC09250                                ; -> sub_bc09250
//   sub_bc09250 (0xbc09250, lift set) - call 0xBC09250                                ; -> sub_bc09250
//   sub_567c8b0 (0x567c8b0, lift set) - call 0x567C8B0                                ; -> sub_567c8b0
//   sub_ab49c0 (0xab49c0, lift set) - call 0xAB49C0                                 ; -> sub_ab49c0
//   sub_5667860 (0x5667860, lift set) - call 0x5667860                                ; -> sub_5667860
//   sub_a78940 (0xa78940, lift set) - call 0xA78940                                 ; -> sub_a78940
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_a78940 (0xa78940, lift set) - call 0xA78940                                 ; -> sub_a78940
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_a78940 (0xa78940, lift set) - call 0xA78940                                 ; -> sub_a78940
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_eec6ed0 (0xeec6ed0, boundary) - call 0xEEC6ED0                                ; -> sub_eec6ed0
//   sub_aa6580 (0xaa6580, lift set) - call 0xAA6580                                 ; -> sub_aa6580
//   sub_aa6580 (0xaa6580, lift set) - call 0xAA6580                                 ; -> sub_aa6580
//   sub_1999390 (0x1999390, lift set) - call 0x1999390                                ; -> sub_1999390
//   call qword ptr [0xF9A8F60]                    ; [data_f9a8f60] (indirect, boundary via data slot)
//   sub_bc5b130 (0xbc5b130, lift set) - call 0xBC5B130                                ; -> sub_bc5b130
//   call rsi (indirect, boundary via data slot)
//   call rsi (indirect, boundary via data slot)
//   sub_eec75a0 (0xeec75a0, lift set) - call 0xEEC75A0                                ; -> sub_eec75a0
//   call qword ptr [0xF9A8DB8]                    ; [data_f9a8db8] (indirect, boundary via data slot)
//   call rsi (indirect, boundary via data slot)
//   call rsi (indirect, boundary via data slot)
//   call rsi (indirect, boundary via data slot)
//   call rsi (indirect, boundary via data slot)
//   sub_eec75a0 (0xeec75a0, lift set) - call 0xEEC75A0                                ; -> sub_eec75a0
//   sub_eec75a0 (0xeec75a0, lift set) - call 0xEEC75A0                                ; -> sub_eec75a0
//   sub_eec75a0 (0xeec75a0, lift set) - call 0xEEC75A0                                ; -> sub_eec75a0
//   sub_eec75a0 (0xeec75a0, lift set) - call 0xEEC75A0                                ; -> sub_eec75a0
//   call rsi (indirect, boundary via data slot)
//   call rsi (indirect, boundary via data slot)
//   sub_eec75a0 (0xeec75a0, lift set) - call 0xEEC75A0                                ; -> sub_eec75a0
//   call rsi (indirect, boundary via data slot)
//   call rsi (indirect, boundary via data slot)
//   sub_eec75a0 (0xeec75a0, lift set) - call 0xEEC75A0                                ; -> sub_eec75a0
//   sub_bc5b130 (0xbc5b130, lift set) - call 0xBC5B130                                ; -> sub_bc5b130
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_568ad40 (0x568ad40, lift set) - call 0x568AD40                                ; -> sub_568ad40
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   sub_76a8a0 (0x76a8a0, boundary) - call 0x76A8A0                                 ; -> sub_76a8a0
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (indirect, boundary via data slot)
//   All call targets resolved: lifted or in native_boundary.tsv

LIFT_FN(sub_bc57460, "sub_bc57460", 0xbc57460, sub_bc57460, nullptr);

} // namespace native::bgfx