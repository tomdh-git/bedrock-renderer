#pragma once
// Read-views of the UI-group and Editor-group descriptions as the group visitors consume them (1.26.62.01). Checklist D8 / D10 (mirror L4t / L4x).
// Method: the exact listings in docs/data/listings (ui_visitor_6664a00_6668510.txt, editor_visitor_66742f0_667e290.txt, gameface_66ade80_66b0eb0.txt), per-case reachable sets
// from the jump-table heads, every displacement re-run with rdis. Documented in docs/functions/ui_editor_descriptions.md and BGFX_MAP 6uie.
// Rules: only displacements seen in a listing get a field; everything between them is explicit padding of the size to the next seen offset (so the true layout may hold more
// fields in the padding); sizeof is NOT asserted because the real size is not proven (the producers reuse one stack object for four gizmo types, see the doc). Meanings are
// [I] unless the field comment says [V]. Tags and group slots live in FrameBuilder.h; the already-typed layouts (UIMesh, HudIcon, Gameface, MeshFallback, Nametag) stay in
// Descriptions.h / GamefaceDescription.h and are only given the roles this pass found.
#include <cstddef>
#include <cstdint>

namespace bluey::uieditor {

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// UI group (visitor 0x6664a00, jump table 0xF2BF468, 5 cases)
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// UIMesh (UI tag 2, case 0x6664bd6). The case is inline: it reads the description (r9) and calls the UI draw function 0x674A3A0 with r8d = 0 (the non-text path, xor at 0x6664f47,
// call at 0x6664f4a [V]). Description displacements read by the case [V], with the argument slot each one feeds (stack slots are [rsp+N] at the call):
//   +0x00 qword -> [rsp+0x38]      +0x08 qword -> [rsp+0x20]      +0x10 qword -> [rsp+0x30]      +0x18 address of the inline ref array -> [rsp+0x40]
//   +0x28/+0x30 refs[1] {ptr, ctrl} (copied with a strong ref, `lock inc [ctrl+8]`) -> a local pair whose address is [rsp+0x48]; only when [+0x58] >= 2 (cmp at 0x6664c3f), else empty
//   +0x60 qword -> [rsp+0x58]      +0x68 qword -> [rsp+0x60]      +0x70 float -> [rsp+0x68]      +0x78 qword -> [rsp+0x28]
//   +0x80 byte -> [rsp+0x50]       +0x81 byte -> [rsp+0x70]       +0x82 byte -> [rsp+0x80]       +0x83 byte -> [rsp+0x78]       +0x85 byte -> [rsp+0x88]
//   +0x86 address (add r9,0x86) -> the r9 register argument      +0x88 address (lea rbx,[r9+0x88], the DescVariantRef) -> [rsp+0xA0]
//   mode (dword) -> [rsp+0x90], computed from three flag bytes (below).
// The struct itself is RenderUIMeshDescription in Descriptions.h (size 0xA8, every offset above is inside its asserted fields).
constexpr uintptr_t kUiMeshOffMode82 = 0x82, kUiMeshOffMode83 = 0x83, kUiMeshOffMode84 = 0x84, kUiMeshOffRefCount = 0x58, kUiMeshOffRefs = 0x18;
// mode = +0x83 ? 2 : (+0x82 ? 1 : +0x84)   [V 0x6664bde..0x6664c03: test cl(+0x82); r8d=1; cmove r8d,edx(+0x84); test r12b(+0x83); r10d=2; cmove r10d,r8d]
inline uint32_t uiMeshMode(const void* desc) {
    const uint8_t* d = static_cast<const uint8_t*>(desc);
    return d[kUiMeshOffMode83] ? 2u : (d[kUiMeshOffMode82] ? 1u : static_cast<uint32_t>(d[kUiMeshOffMode84]));
}

// HudIcon (UI tag 1, case 0x6664d51; the producer is 0xe9aed0). RenderUIHudIconDescription (Descriptions.h, 0x50 bytes) has {qword +0x00, 16 floats +0x08, u32 +0x48}. What the
// case does with them [V]: material "UI/Blit" (0xF539A95, length 7) through 0x675E440; +0x00 is NOT a mesh but a pointer to the source object below; the 4x4 at +0x08
// (lea rdi,[rcx+8] @0x666531b) is the B operand of one 0xAA6580 mat4 multiply per source vertex (loop @0x6665444..0x66654ee, stride 0xC, output stride 0x40); the word at +0x48
// (movzx esi,word ptr [rax+0x48] @0x6665561) is stored into the draw record at [rbp+0x328] (a 16-bit sort/key value) [I name].
struct HudIconSourceView {
    void* mMesh;              // +0x00 [V] `mov rsi,[r8]` @0x666524c: the mce::Mesh (its +0x58/+0x60 vector, +0x1B0/+0x1B8 shared pair, +0x1D0 count and +0x1D4 flag are read, = RenderControllerMesh in FrameBuilder.h)
    uint8_t mPad08[0x10];
    uint64_t mVertexCount;    // +0x18 [V] `mov rax,[r8+0x18]` @0x66652b0, scaled by 12 bytes at 0x66652fa
    const float* mVertices;   // +0x20 [V] `mov r15,[r8+0x20]` @0x666530d: vec3 records, stride 0xC
    float mOpacity;           // +0x28 [V read] `movss xmm0,[r8+0x28]` @0x66651ae, splatted into a vec4 uniform [I name]
};
static_assert(offsetof(HudIconSourceView, mMesh) == 0x00);
static_assert(offsetof(HudIconSourceView, mVertexCount) == 0x18);
static_assert(offsetof(HudIconSourceView, mVertices) == 0x20);
static_assert(offsetof(HudIconSourceView, mOpacity) == 0x28);

// Gameface (UI tag 0) keeps its typed header GamefaceDescription.h; this pass only corrects the record list: [desc+0x80] is a POINTER to a {begin, end} pair, not the list itself
// (`mov rax,[r14+0x80]; mov r15,[rax]; mov rax,[rax+8]` @0x66aecc2..0x66aecd0, step `add r15,0x1A0` @0x66aece0 [V]; r14 = the description spilled at [rbp+0x520]).
struct GamefaceRecordList {
    uint8_t* mBegin;
    uint8_t* mEnd;            // records of 0x1A0 bytes between mBegin and mEnd
};
static_assert(sizeof(GamefaceRecordList) == 0x10);
constexpr size_t kGamefaceRecordStride = 0x1A0;

// UIImGui (UI tag 4, case 0x6664aab) uses the material "Debug/ImGui" (literal 0xF5AD096, length 0xB); its description fields are not decoded here [?].

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Editor group (visitor 0x66742f0, jump table 0xF2BF520, 8 cases). rdi = the description in every case. Tag 0 (BlockVolumeBoundingBox) tail-jumps to the block-volume extractor
// 0x66a1860 (jmp at 0x66743ef [V]); its read-view is EditorBlockVolumeDescription.h. Materials per case (string literals read from the exe):
//   tags 1..4 gizmo handles: "EditorBlockVolumeHull"   tag 5 SelectionCursor: "EditorSelectionCursor"   tag 6 Outline: "EditorSelectionCursor" + "EditorBlockVolumeWireframe"
//   tag 7 RenderPlane: "EditorBlockVolumeWireframe"
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Gizmo handle Arrow (tag 1, case 0x667499f) and Cube (tag 2, case 0x6674518): identical read set. The three vec3 and the mat4 are contiguous (+0x00, +0x0C, +0x18, +0x24; the
// mat4 spans +0x24..+0x63 because it is the B operand `lea r8,[rdi+0x24]` of 0xAA6580 @0x6675530 [V] and the colour starts at +0x64).
struct GizmoHandleArrowCubeView {
    float mPosition[3];       // +0x00 qword @0x6675477 + dword @0x6675488 [V reads]; builds the translation matrix [I]
    float mVecB[3];           // +0x0C qword @0x66753c7 + dword +0x14 @0x66753f5 [V reads]; second input of the same matrix build [I]
    float mVecC[3];           // +0x18 qword @0x6676b7f + dword +0x20 @0x6676b7a [V reads]; used by the second draw form (0x66765cd.. region) [I]
    float mModel[16];         // +0x24 [V operand of 0xAA6580]
    float mColor[4];          // +0x64 movups @0x66758bd, used unless mUseDefaultColor [V]
    uint8_t mUseDefaultColor; // +0x74 [V] test @0x6675564: nonzero loads the constant at 0xF0A40C0 instead of mColor
    uint8_t mPad75[3];
    float mScale;             // +0x78 [V] movss @0x66754dd, builds a uniform-scale matrix [I]
    uint8_t mPad7C[4];
    uint8_t mObject80[0x50];  // +0x80 [V] address passed to 0x66A6060 (the draw-object validity check, @0x6675522); its inner layout is not read in the visitor [?]
    uint16_t mSortKey;        // +0xD0 [V] `mov r12w,[rdi+0xD0]` @0x6676c9b
    uint8_t mFlagD2;          // +0xD2 [V] compared with 1 for Arrow (@0x66758c1) and with 0 for Cube (@0x667589a): the two cases choose opposite forms [I]
};
static_assert(offsetof(GizmoHandleArrowCubeView, mPosition) == 0x00);
static_assert(offsetof(GizmoHandleArrowCubeView, mVecB) == 0x0C);
static_assert(offsetof(GizmoHandleArrowCubeView, mVecC) == 0x18);
static_assert(offsetof(GizmoHandleArrowCubeView, mModel) == 0x24);
static_assert(offsetof(GizmoHandleArrowCubeView, mColor) == 0x64);
static_assert(offsetof(GizmoHandleArrowCubeView, mUseDefaultColor) == 0x74);
static_assert(offsetof(GizmoHandleArrowCubeView, mScale) == 0x78);
static_assert(offsetof(GizmoHandleArrowCubeView, mObject80) == 0x80);
static_assert(offsetof(GizmoHandleArrowCubeView, mSortKey) == 0xD0);
static_assert(offsetof(GizmoHandleArrowCubeView, mFlagD2) == 0xD2);

// Gizmo handle Pane (tag 3, case 0x667463c): the same head through +0x80, then +0xD0 is the ADDRESS of a sub-object (`lea r14,[rdi+0xD0]` @0x66752ce), and the sort key moves to
// the word at +0x120 (@0x667696d, @0x6679f27, @0x667b6b8) with a flag byte +0x122 (@0x6679c65, compared with 1) [V].
struct GizmoHandlePaneView {
    float mPosition[3];       // +0x00
    float mVecB[3];           // +0x0C (the case reads +0x08 minus +0x14 @0x6675218..0x667521d)
    float mVecC[3];           // +0x18
    float mModel[16];         // +0x24
    float mColor[4];          // +0x64 (movups @0x6675dea)
    uint8_t mUseDefaultColor; // +0x74 (cmp @0x6675340)
    uint8_t mPad75[3];
    float mScale;             // +0x78 (@0x667529c)
    uint8_t mPad7C[4];
    uint8_t mObject80[0x50];  // +0x80
    uint8_t mObjectD0[0x50];  // +0xD0 address taken; extent up to +0x120 is an assumption [I]
    uint16_t mSortKey;        // +0x120
    uint8_t mPad122Flag;      // +0x122 flag byte compared with 1 [V read, meaning ?]
};
static_assert(offsetof(GizmoHandlePaneView, mColor) == 0x64);
static_assert(offsetof(GizmoHandlePaneView, mObject80) == 0x80);
static_assert(offsetof(GizmoHandlePaneView, mObjectD0) == 0xD0);
static_assert(offsetof(GizmoHandlePaneView, mSortKey) == 0x120);
static_assert(offsetof(GizmoHandlePaneView, mPad122Flag) == 0x122);

// Gizmo handle Ring (tag 4, case 0x66743f4): a different layout. The mat4 starts at +0x0C (four movups at +0x0C/+0x1C/+0x2C/+0x3C copy it, @0x6676456..0x6676477 [V]); the
// reads at +0x3C (qword) and +0x44 (dword) are its translation row (elements 12..14) [I]. Three draw objects are checked with 0x66A6060 (+0x60 @0x6674f54, +0xB8, +0x110 via lea)
// with enable bytes +0x80, +0xD8, +0x108 (each compared with 1) [V reads].
struct GizmoHandleRingView {
    float mPosition[3];       // +0x00 qword @0x66763c7 + dword @0x66763c2
    float mModel[16];         // +0x0C .. +0x4B
    float mVecA[2];           // +0x4C qword @0x6675866 (used when mUseDefault is 0)
    float mVecB[2];           // +0x54 qword @0x667586b
    uint8_t mUseDefault;      // +0x5C [V] movzx @0x6674fb3: nonzero loads constants (0xEFD32F0, 0xEFD3400) instead of mVecA/mVecB
    uint8_t mPad5D[3];
    uint8_t mObject60[0x1C];  // +0x60 address passed to 0x66A6060 (@0x6674f5b)
    uint32_t mDword7C;        // +0x7C [V] cmp @0x66764a0
    uint8_t mFlag80;          // +0x80 [V] cmp with 1 @0x6676497
    uint8_t mPad81[7];
    uint64_t mQword88;        // +0x88 [V read] @0x6677a3c
    uint8_t mPad90[0x10];
    uint64_t mQwordA0;        // +0xA0 [V read] @0x6677a27
    uint64_t mQwordA8;        // +0xA8 [V read] @0x66764b6
    uint32_t mDwordB0;        // +0xB0 [V read] @0x6676489
    uint8_t mPadB4[4];
    uint8_t mObjectB8[0x1C];  // +0xB8 address taken @0x667854d
};
// The ring view above is kept to the offsets that are cheap to prove; the remaining reads (+0xD4 dword, +0xD8 byte, +0xE0/+0xF8/+0x100 qwords, +0x108 byte, +0x110 address, +0x1E8 dword,
// +0x1EC word, +0x1EE byte) are given as constants instead of members:
constexpr uintptr_t kRingOffD4 = 0xD4, kRingOffFlagD8 = 0xD8, kRingOffE0 = 0xE0, kRingOffF8 = 0xF8, kRingOff100 = 0x100, kRingOffFlag108 = 0x108, kRingOffObject110 = 0x110,
                    kRingOff1E8 = 0x1E8, kRingOffSortKey1EC = 0x1EC, kRingOffFlag1EE = 0x1EE;
static_assert(offsetof(GizmoHandleRingView, mModel) == 0x0C);
static_assert(offsetof(GizmoHandleRingView, mVecA) == 0x4C);
static_assert(offsetof(GizmoHandleRingView, mVecB) == 0x54);
static_assert(offsetof(GizmoHandleRingView, mUseDefault) == 0x5C);
static_assert(offsetof(GizmoHandleRingView, mObject60) == 0x60);
static_assert(offsetof(GizmoHandleRingView, mDword7C) == 0x7C);
static_assert(offsetof(GizmoHandleRingView, mFlag80) == 0x80);
static_assert(offsetof(GizmoHandleRingView, mQword88) == 0x88);
static_assert(offsetof(GizmoHandleRingView, mQwordA0) == 0xA0);
static_assert(offsetof(GizmoHandleRingView, mQwordA8) == 0xA8);
static_assert(offsetof(GizmoHandleRingView, mDwordB0) == 0xB0);
static_assert(offsetof(GizmoHandleRingView, mObjectB8) == 0xB8);

// Tags 5 (SelectionCursor, case 0x6674ac3), 6 (BlockVolumeOutline, case 0x6674d02) and 7 (RenderPlane, case 0x6674760) share one prologue: gate `cmp byte ptr [rdi+0x3C],1`
// (@0x6674ac3 / 0x6674d02 / 0x6674760 [V]) then the box transform from +0x00 and +0x0C (the same matrix build as the gizmos, 0xAA6580 at the end of it).
struct EditorBoxHead {
    float mPosition[3];       // +0x00 [V reads @0x6674b87/0x6674b9b]
    float mExtent[3];         // +0x0C [V reads @0x6674ad7/0x6674b05]
};
static_assert(sizeof(EditorBoxHead) == 0x18);

// SelectionCursor (tag 5). Beyond the head: +0x18 and +0x28 are 16-byte loads (@0x6677686, @0x6675a36), +0x38 float (@0x667598b), +0x40 and +0x90 are addresses of draw objects
// (lea r8 @0x6677745, @0x6675af5) and the word +0xE0 (@0x6675b0c) is a sort key [V reads, I roles].
struct SelectionCursorView {
    EditorBoxHead mBox;       // +0x00
    float mBlock18[4];        // +0x18
    float mBlock28[4];        // +0x28
    float mValue38;           // +0x38
    uint8_t mEnable3C;        // +0x3C gate
    uint8_t mPad3D[3];
    uint8_t mObject40[0x50];  // +0x40 address taken
    uint8_t mObject90[0x50];  // +0x90 address taken
    uint16_t mSortKey;        // +0xE0
};
static_assert(offsetof(SelectionCursorView, mBlock18) == 0x18);
static_assert(offsetof(SelectionCursorView, mBlock28) == 0x28);
static_assert(offsetof(SelectionCursorView, mValue38) == 0x38);
static_assert(offsetof(SelectionCursorView, mEnable3C) == 0x3C);
static_assert(offsetof(SelectionCursorView, mObject40) == 0x40);
static_assert(offsetof(SelectionCursorView, mObject90) == 0x90);
static_assert(offsetof(SelectionCursorView, mSortKey) == 0xE0);

// BlockVolumeOutline (tag 6): the same shape as the cursor (it also builds the "EditorSelectionCursor" material) plus the enable bytes +0xE2 / +0xE3 and a float +0xE4, and a
// second draw with "EditorBlockVolumeWireframe" (@0x6675791). Reads: +0x18 qword (@0x667a933) / 16 B (@0x667c850), +0x20 dword (@0x667a926), +0x28 16 B (@0x667c2a9), +0x38 float
// (@0x667a87b), +0x40 / +0x90 addresses, +0xE0 word, +0xE2 byte (@0x6676eab), +0xE3 byte (@0x667c107), +0xE4 float (@0x667a92b) [V].
struct BlockVolumeOutlineView {
    EditorBoxHead mBox;       // +0x00
    float mBlock18[4];        // +0x18 (qword and dword reads fall inside)
    float mBlock28[4];        // +0x28
    float mValue38;           // +0x38
    uint8_t mEnable3C;        // +0x3C
    uint8_t mPad3D[3];
    uint8_t mObject40[0x50];  // +0x40 address taken
    uint8_t mObject90[0x50];  // +0x90 address taken
    uint16_t mSortKey;        // +0xE0
    uint8_t mEnableE2;        // +0xE2 (compared with 1)
    uint8_t mEnableE3;        // +0xE3 (compared with 1)
    float mValueE4;           // +0xE4
};
static_assert(offsetof(BlockVolumeOutlineView, mBlock18) == 0x18);
static_assert(offsetof(BlockVolumeOutlineView, mBlock28) == 0x28);
static_assert(offsetof(BlockVolumeOutlineView, mValue38) == 0x38);
static_assert(offsetof(BlockVolumeOutlineView, mEnable3C) == 0x3C);
static_assert(offsetof(BlockVolumeOutlineView, mObject40) == 0x40);
static_assert(offsetof(BlockVolumeOutlineView, mObject90) == 0x90);
static_assert(offsetof(BlockVolumeOutlineView, mSortKey) == 0xE0);
static_assert(offsetof(BlockVolumeOutlineView, mEnableE2) == 0xE2);
static_assert(offsetof(BlockVolumeOutlineView, mEnableE3) == 0xE3);
static_assert(offsetof(BlockVolumeOutlineView, mValueE4) == 0xE4);

// RenderPlane (tag 7): "EditorBlockVolumeWireframe" only. Reads: +0x18 16 B (@0x667aede), +0x28 16 B (@0x6677105), +0x34 float (@0x66755df, inside the +0x28 block), gate bytes
// +0x3C, +0x3D (@0x66755d5), +0x3E (@0x667ad48), +0x40 / +0x90 addresses, word +0xE0 (@0x66771db) [V reads]. Its producer's stores end at +0xE3 (docs/progress/descriptions.md),
// consistent with a size of 0xE8 [I, not asserted].
struct RenderPlaneView {
    EditorBoxHead mBox;       // +0x00
    float mBlock18[4];        // +0x18
    float mBlock28[3];        // +0x28 (16 B load; the first three lanes)
    float mValue34;           // +0x34 float read
    uint8_t mPad38[4];
    uint8_t mEnable3C;        // +0x3C gate
    uint8_t mEnable3D;        // +0x3D
    uint8_t mEnable3E;        // +0x3E
    uint8_t mPad3F;
    uint8_t mObject40[0x50];  // +0x40 address taken
    uint8_t mObject90[0x50];  // +0x90 address taken
    uint16_t mSortKey;        // +0xE0
};
static_assert(offsetof(RenderPlaneView, mBlock18) == 0x18);
static_assert(offsetof(RenderPlaneView, mBlock28) == 0x28);
static_assert(offsetof(RenderPlaneView, mValue34) == 0x34);
static_assert(offsetof(RenderPlaneView, mEnable3C) == 0x3C);
static_assert(offsetof(RenderPlaneView, mEnable3D) == 0x3D);
static_assert(offsetof(RenderPlaneView, mEnable3E) == 0x3E);
static_assert(offsetof(RenderPlaneView, mObject40) == 0x40);
static_assert(offsetof(RenderPlaneView, mObject90) == 0x90);
static_assert(offsetof(RenderPlaneView, mSortKey) == 0xE0);

} // namespace bluey::uieditor
