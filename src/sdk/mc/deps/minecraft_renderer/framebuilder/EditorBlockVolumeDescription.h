#pragma once
// Editor block-volume extractor description, from extractEditorBlockVolume 0x66a1860 (1.26.62.01).
// docs/functions/66a1860.md. rcx = frame/builder ([+0x10] + 0x9d0 = pass base), rdx = this description. Offsets [V] (descscan + reads).
#include "WeatherDescription.h"

namespace bluey::editorvol {

struct EditorBlockVolumeDescription {
    float    min[3];        // +0x00 (x,y read as qword; z at +0x08)
    float    max[3];        // +0x0c (x,y qword; z at +0x14)
    float    cameraDir[3];  // +0x18 qword + +0x20 dword (hull CameraDirection uniform)
    uint8_t  flag24;        // +0x24 (hull)
    uint8_t  pad25[3];
    weather::Vec4 frameTime;// +0x28 (FrameTime uniform: lane 0 splat)
    uint8_t  objA[0x50];    // +0x38.. ; +0x30 ptr checked by 0x66a6060 for draw A (starts at +0x30)
};
// The layout above is only partially contiguous (0x30..0x87 is one object whose tail holds a ptr at +0x88), so only the read displacements
// are pinned, not a full struct:
constexpr size_t kOffMin = 0x00, kOffMax = 0x0c, kOffCamDir = 0x18, kOffFlag24 = 0x24, kOffFrameTime = 0x28,
                 kOffObjA = 0x30, kOffEnableA = 0x80, kOffObjHull = 0x88, kOffEnableHull = 0xd8, kOffObjB = 0xe0,
                 kOffEnableB = 0x130, kOffColorB = 0x138 /* qword + dword at +0x140 */, kOffColorA = 0x148 /* qword + dword at +0x150 */,
                 kOffColorHull = 0x158 /* float4 */, kOffSortKey = 0x168 /* u16 */, kOffSortBias = 0x16c /* i32 */, kOffFormSelect = 0x170 /* u8 */;
static_assert(offsetof(EditorBlockVolumeDescription, min) == kOffMin);
static_assert(offsetof(EditorBlockVolumeDescription, max) == kOffMax);
static_assert(offsetof(EditorBlockVolumeDescription, cameraDir) == kOffCamDir);
static_assert(offsetof(EditorBlockVolumeDescription, flag24) == kOffFlag24);
static_assert(offsetof(EditorBlockVolumeDescription, frameTime) == kOffFrameTime);
static_assert(offsetof(EditorBlockVolumeDescription, objA) == 0x38);

} // namespace bluey::editorvol
