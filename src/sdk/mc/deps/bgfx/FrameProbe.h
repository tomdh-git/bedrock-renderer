#pragma once
// Read-only frame-probe declarations for docs/progress/oc_U-EQ1c.md (Q1c R3 frame probe:
// per-frame dump of typed descriptions, pass list, draw records + RenderDraw +
// material/program/PSO key, actor attribution).
//
// Every offset below is pinned by a verbatim instruction from the exe
// (C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe,
// version 1.26.62.01). [V] = the instruction read/store is shown verbatim in the
// progress file; [I] = role inferred from structure/order. This header documents
// seams and layouts only: it registers no hooks, patches nothing, and performs no
// reads or writes at runtime. It is safe to include from a read-only dump tool.
//
// Frame (two buffers alternate, 0xE749C0 bytes apart; see docs/BGFX_MAP.md 6e)
//   kDrawHeaders      = 0xB4700   RenderDrawHeader[], stride 0x80   [V] executor 0xe82269e
//   kSortedItems      = 0x94700   uint16_t[65536] draw order        [V] executor 0xe822673
//   kRenderDraws      = 0x8B4700  RenderDraw array object, stride 0x540  [V] executor 0xe8226e9
//   kItemCount        = 0xDC57E8  u32 atomic draw-slot counter, cap 0xFFFE [V]
//   kFrameCounter     = 0xE746D8  u32, +1 per frame                 [V] submit 0xe82e34c
//
// The 0x80-byte draw header (bgfx RenderDraw, Mojang layout). Fields read by the
// D3D12 draw executor 0xe821120:
//   +0x20 u64 stateFlags                 bit 62 tested               [V] 0xe8226bf
//   +0x28 u64 stencil
//   +0x34 u32 uniformBegin / +0x38 u32 uniformEnd                    [V] 0xe8224b0 probe key
//   +0x40 u32 startIndex / +0x44 u32 numIndices (0xFFFFFFFF = whole)
//   +0x48 u32 indexStride (2 or 4)
//   +0x4C u32 numVertices / +0x50 u32 instanceDataOffset
//   +0x54 u32 numInstances / +0x58 u16 instanceDataStride
//   +0x5A u16 startIndirect (x32) / +0x5C u16 numIndirect (0xFFFF = whole)
//   +0x5E u16 numMatrices / +0x60 u16 scissor rect index (0xFFFF = none)
//   +0x62 u8 submitFlags sign bit inverts occlusion visibility test
//   +0x63 u8 streamMask / +0x64 u8 uniformIdx
//   +0x68 i32 depthBias / +0x6C float slopeScaledDepthBias / +0x70 float depthBiasClamp  (Mojang; part of PSO key)
//   +0x74 u16 indexBuffer (0xFFFF = non-indexed)
//   +0x76 u16 instanceDataBuffer (0xFFFF = none)
//   +0x78 u16 indirectBuffer (0xFFFF = normal draw)
//   +0x7A u16 occlusionQuery (0xFFFF = none)

// Per-item 0x540-byte RenderDraw block (executor 0xe82267c/0xe8226e9):
//   +0x514 u32 bind hash / bind block                              [V] read verbatim

// Program / PSO key path (executor 0xe822483..0xe822549):
//   programIndex = (sortKey >> 0x15) & 0x7FF                       [V] 0xe822483/0xe82248e
//   programRecord = renderer + 0xB62178 + programIndex * 0xF8      [V] 0xe822493
//   psoProbeKey  = u32 at programRecord + 0xA8 (4 signed bytes)    [V] 0xe8224b0
//   hash         = ((((b0*0x1003F+b1)*0x1003F+b2)*0x1003F+b3) * 0xFC5D1543EC5F01)
//   bucketCount  = (bgfxBlock[0x50] - bgfxBlock[0x48]) >> 3        [V] 0xe8224c5/0xe8224c8
//   node walk: key=[node+0], next=[node+0x10]                      [V] 0xe822524/0xe822540/0xe822549
//   root signature has >=6 params; CreateGraphicsPipelineState via [bgfx ctx+0x400 vtbl+0x58]

// Actor attribution [I]: actors are entt registry entities. bodyActor (0x66D0A00) reads
// body+0x150/0x151 flags and follows the body+0x140 chain, pushing one 0xC8-byte item
// record per actor; passLookup (0x5ABA5C0) returns the pass whose +0xA0 item vector holds
// it; a 56-bit item hash matches task to actor. BatchActor instances carry NO actor id or
// world position (an instance = model/draw record only), so identity routes through
// bodyActor S+0xC8 / the registry components (SceneObjectActors), not through the batch
// instance. BatchActor binds uniforms TintedAlphaTestEnabled..MatTexture2 (strings at
// 0x66df637..0x66dff25, 0x66e0587) and uses XXH64 0x19932c0 for material keys.


namespace bgfx {

struct DrawHeaderFields {
    // offset, size, role (mirrors the verbatim rows in docs/progress/oc_U-EQ1c.md)
};

} // namespace bgfx
