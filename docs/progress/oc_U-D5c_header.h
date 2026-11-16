// docs/progress/oc_U-D5c_header.h
// U-D5c: ChunkOccluders description (item tag 4)
// Reversed from Minecraft.Windows.exe 1.26.62.01 via static analysis only.
//
// Handler 0x6646a89 (item visitor 0x6646980) reads the description through rdi:
//   0x6647e73 mov r14,[rdi+0x40]   ; mce::Mesh* mMesh
//   0x6647edc movups xmm0,[rdi]    ; mTransform row 0  (+0x00..+0x0F)
//   0x6647ee6 movups xmm0,[rdi+0x10] ; mTransform row 1 (+0x10..+0x1F)
//   0x6647ef1 movups xmm0,[rdi+0x20] ; mTransform row 2 (+0x20..+0x2F)
//   0x6647efc movdqu xmm0,[rdi+0x30] ; mTransform row 3 (+0x30..+0x3F)
//   0x6647f10 movzx esi,word ptr [rdi+0x48] ; u16 mValue48 (+0x48)
// Last read ends at 0x4A => read VIEW SIZE = 0x4A. Bytes +0x4A..+0x4F are
// alignment padding, unread by the handler.
//
// Producer 0x53def00 builds the description on the stack (rbp+0x210..0x258)
// then copies it into the actual description via thin clone 0x5369920.
//
// Matches docs/BGFX_MAP.md section 6ig (tag-4 reads). Existing src struct
// (sizeof 0x50) is NOT edited by this unit.

#pragma once
#include <cstddef>
#include <cstdint>

struct RenderChunkOccludersDescription {
    float  mTransform[4][4];   // +0x00 .. +0x3F  (64 bytes, 4x4 row-major matrix)
    void*  mMesh;              // +0x40            (mce::Mesh* mesh pointer)
    uint16_t mValue48;         // +0x48            (u16 value)
    // +0x4A .. +0x4F: padding (unread; read view ends at 0x4A)
    // sizeof == 0x50 (pointer-padded to 8-byte boundary)
};

static_assert(offsetof(RenderChunkOccludersDescription, mMesh) == 0x40,
              "mMesh must be at offset 0x40");
static_assert(offsetof(RenderChunkOccludersDescription, mValue48) == 0x48,
              "mValue48 must be at offset 0x48");
static_assert(sizeof(RenderChunkOccludersDescription) == 0x50,
              "sizeof RenderChunkOccludersDescription must be 0x50");
