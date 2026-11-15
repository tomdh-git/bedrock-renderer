# Dossier: the three sibling encoder submit forms (0xbc61140, 0xbc61560, 0xbc618e0)

1.26.62.01. Reversed by diffing each body against the fully reversed `EncoderImpl::submit` (docs/functions/bc60740.md): the prologue, the discard check, the saturating atomic allocation of the item index, the bind-hash block, the RenderBind copy (`ensure` 0xbc7a7c0 + memcpy 0x518), the side-table commit (0xbc60f10), the 65-binding clear and the side-table clear are instruction-for-instruction the same in all four functions. Only the parts below differ. Tags: [V] read, [I] inferred, [?] open.

Common facts [V]: none of the three takes a "preserve state" argument (they always clear); none checks `numIndices | numVertices`; all three use the SEQUENCE counter of the view (`lock xadd [s_ctx + view*4 + 0x1EAAC60]`) regardless of the view's sort mode, so these items keep submission order inside a view; all write `m_key.m_depth = 0`.

`m_compute` = the 0x24-byte block at encoder +0xC0 (stock bgfx RenderCompute, Mojang layout) [V]:
`+0xC0 u32 uniformBegin, +0xC4 u32 uniformEnd, +0xC8 u32 startMatrix, +0xCC u16 indirectBuffer (0xFFFF), +0xD0 u32 numX, +0xD4 u32 numY, +0xD8 u32 numZ, +0xDC u32, +0xE0 u16 numMatrices, +0xE2 u8 uniformIdx, +0xE3 u8 subtype`.
It is copied (0x24 bytes) to the same 0x80-byte Frame render-item slot a draw would use (`Frame+0xB4700 + idx*0x80`): the slot is a union of RenderDraw and RenderCompute. The D3D12 executor tells them apart by the sort key (bit 52 = draw).

## A. 0xbc61140 = `EncoderImpl::dispatch` (compute)

```cpp
void EncoderImpl::dispatch(uint16_t viewId /*dx*/, uint16_t program /*r8w*/, uint32_t numX /*r9d*/, uint32_t numY /*5th*/, uint32_t numZ /*6th*/) {
    if (m_discard == 1) { discard(); return; }
    idx = atomicFetchAndAddsat(&m_frame->m_numRenderItems, 1, 0xFFFF);
    if (idx >= 0xFFFE) { discard(); ++m_numDropped; return; }
    ++m_numSubmitted;
    m_uniformEnd = m_frame->m_uniformBuffer[m_uniformIdx]->pos;
    m_compute.m_startMatrix = m_draw.m_startMatrix;          // encoder +0x7C (draw +0x3C) -> +0xC8
    m_compute.m_numMatrices = m_draw.m_numMatrices;          // encoder +0x9E (draw +0x5E) -> +0xE0
    m_compute.m_numX = max(numX, 1);  m_compute.m_numY = max(numY, 1);  m_compute.m_numZ = max(numZ, 1);   // cmp 1 / adc 0
    m_key.m_program = program;  m_key.m_depth = 0;  m_key.m_view = viewId;
    m_key.m_seq = _InterlockedExchangeAdd(&s_ctx->m_seq[viewId], 1);
    uint64_t key = (uint64_t(uint8_t(viewId)) << 54)         // no draw bit, no type tag: a compute key
                 | (uint64_t(m_key.m_seq & 0xFFFFF) << 32)
                 | (uint32_t(m_key.m_program) << 21);        // 32-bit shift of the {program, view} dword: bits 21..36 hold the program
    m_frame->m_sortKeys[idx] = key;  m_frame->m_sortValues[idx] = uint16_t(idx);
    m_compute.m_uniformIdx = m_uniformIdx;                   // +0xE2
    m_compute.m_uniformBegin = m_uniformBegin;  m_compute.m_uniformEnd = m_uniformEnd;   // one 8-byte copy +0x694 -> +0xC0
    /* bind hash if dirty: same as submit */
    memcpy(&m_frame->m_renderItem[idx], &m_compute, 0x24);
    /* RenderBind copy + side table commit: same as submit */
    // m_compute.clear()
    *(uint64_t*)(this + 0xC0) = 0;  *(uint32_t*)(this + 0xC8) = 0;
    memcpy(this + 0xD0, kComputeDefaults16 /*rodata*/, 16);  // numX/numY/numZ/+0xDC defaults
    *(uint32_t*)(this + 0xE0) = 0x00FF0000;                  // numMatrices = 0, uniformIdx = 0xFF, subtype = 0
    *(uint16_t*)(this + 0xCC) = 0xFFFF;
    m_uniformBegin = m_uniformEnd;
    /* 65-binding clear, side table clear, m_bindDirty = 1: same as submit */
}
```
[V: body read end to end against submit.] The `(program << 21)` detail: the code shifts the 32-bit value at encoder +0x10 (program in the low word, view in the high word) left by 21 in a 32-bit register, so only program bits survive below bit 32.

## B. 0xbc61560 = Mojang custom item (two 64-bit payload words)

```cpp
void EncoderImpl::submitCustom(uint16_t viewId /*dx*/, uint64_t a /*r8*/, uint64_t b /*r9*/) {
    /* discard check, index allocation, ++m_numSubmitted, m_uniformEnd: same */
    *(uint64_t*)(this + 0x100) = a;  *(uint64_t*)(this + 0x108) = b;      // a 16-byte item block at encoder +0x100
    m_key.m_program = 0;  m_key.m_depth = 0;  m_key.m_view = viewId;
    m_key.m_seq = _InterlockedExchangeAdd(&s_ctx->m_seq[viewId], 1);
    uint64_t key = 0x0020000000000000ull                                    // bit 53: the tag of this item class
                 | (uint64_t(uint8_t(viewId)) << 54)
                 | (uint64_t(m_key.m_seq & 0xFFFFF) << 32);
    m_frame->m_sortKeys[idx] = key;  m_frame->m_sortValues[idx] = uint16_t(idx);
    /* bind hash if dirty */
    memcpy(&m_frame->m_renderItem[idx], this + 0x100, 16);                   // only 16 bytes of the 0x80 slot
    /* RenderBind copy + side table commit */
    memset(this + 0x100, 0, 16);
    /* m_uniformBegin = m_uniformEnd?, binding clear, side table clear, m_bindDirty = 1 [tail not re-read line by line: I] */
}
```
[V for everything before the final clears.] **Resolved (BGFX_MAP 6fg/6fh): `a` is a function pointer and `b` its user data.** The D3D12 executor handles key bit 53 by calling `a(b, &ctx)` on the render thread with a small context that carries the command list; the game's callers are the frame-graph pass tasks, which pass a static per-class function and the task object. The earlier notes called this "dispatch-style": it is not a compute dispatch, A is.

## C. 0xbc618e0 = Mojang compute item with frame parameter blocks (ray-tracing / post-process settings)

```cpp
void EncoderImpl::submitFrameParams(uint16_t viewId /*dx*/, const ParamsA* a /*r8, 0x1E8 bytes*/, const ParamsB* b /*r9, 0x38 bytes + shared_ptr at +0x38/+0x40*/,
                                    uint32_t numX /*5th*/, uint32_t numY /*6th*/) {
    /* discard check, index allocation, ++m_numSubmitted, m_uniformEnd: same */
    m_compute.m_startMatrix = m_draw.m_startMatrix;  m_compute.m_numMatrices = m_draw.m_numMatrices;
    m_compute.m_subtype = 1;                                                  // +0xE3: marks this compute item
    m_compute.m_numX = max(numX, 1);  m_compute.m_numY = max(numY, 1);
    m_key.m_program = 0xFFFF;  m_key.m_depth = 0;  m_key.m_view = viewId;
    m_key.m_seq = _InterlockedExchangeAdd(&s_ctx->m_seq[viewId], 1);
    uint64_t key = (uint64_t(uint8_t(viewId)) << 54) | (uint64_t(m_key.m_seq & 0xFFFFF) << 32) | (uint32_t(0xFFFF) << 21);
    m_frame->m_sortKeys[idx] = key;  m_frame->m_sortValues[idx] = uint16_t(idx);
    /* uniform fields, bind hash, memcpy(&m_frame->m_renderItem[idx], &m_compute, 0x24), RenderBind copy, side table commit: same as A */
    memcpy((uint8_t*)m_frame + 0xE746DC, a, 0x1E8);                          // per-frame parameter block A
    memcpy((uint8_t*)m_frame + 0xE748C8, b, 0x38);                           // per-frame parameter block B (0x30 + the qword at +0x30)
    *(void**)((uint8_t*)m_frame + 0xE74900) = b->sharedPtr;                  // shared_ptr copy: element pointer (+0x38)
    std::swap-in of the control block at Frame+0xE74908 (lock inc new [ctrl+8]; lock dec old, dispose/destroy when it hits zero)   // +0x40
    /* then the compute clear and the common tail [not re-read line by line: I] */
}
```
[V up to and including the shared_ptr assignment.] `Frame+0xE746DC..0xE74910` is therefore **one frame-global parameter record set by this call**, which is the "0x230 bytes of float parameters (fog, exposure, tonemap-like values)" seen in the live Frame dump (BGFX_MAP 6e). The subtype byte is what the executor tests as "item kind 1" before calling the command-list path with the extra arguments (6cs). Only one such record exists per Frame, so the last call of a frame wins [I].

## Structs touched

EncoderOffsets: kCompute 0xC0 (0x24 bytes), kCustomItem 0x100 (16 bytes) added to Encoder.h. FrameOffsets: kFrameParamsA 0xE746DC (0x1E8), kFrameParamsB 0xE748C8 (0x38 + shared_ptr at +0x38) added to Frame.h.

## Sort-key classes (all four submit forms together) [V]

| item | bit 53 | bit 52 | bits 50..51 | other fields |
|---|---|---|---|---|
| draw, program sort | 0 | 1 | 0 | depth << 5, program << 37, trans << 48 |
| draw, depth sort | 0 | 1 | 1 | depth << 18, program << 5, trans << 16 |
| draw, sequence sort | 0 | 1 | 2 | seq << 30, program << 17, trans << 28 |
| compute (A, C) | 0 | 0 | 0 | seq << 32, program << 21 |
| custom (B) | 1 | 0 | 0 | seq << 32 |
View is always bits 54..61. Inside a view the unsigned key order is therefore: compute items, then draws (program, depth, sequence classes), then custom items.

## Verification

Static diff against the fully reversed submit, 62.01. Tails of B and C after their specific blocks were compared by diff only (they show the same clear/side-table code as A) and not transcribed. No live check. Status: A D2 (fully reversed), B and C D2-partial (argument meaning open).
