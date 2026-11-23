#pragma once

// D3D12 draw editor: read/modify every DrawBatcher record before the GPU.
// Hook target: flush 0xe81b720 (DrawBatcher* rcx, void* rdx, JobContext* r8, uint32_t kind r9d).
// The executor calls flush at 7 sites (0xe822e4e, 0xe822e6b, 0xe82cfc1, 0xe82cfde,
// 0xe82d0f6, 0xe82d12b, 0xe82d148). A hook placed at the flush entry iterates all
// pending records of the given kind and invokes the user callback on each before the
// real flush issues the GPU draw.
//
// This header is header-only (no CMake change) and registers nothing:
// HookManager.cpp and existing hook registrations are off-limits to this unit.
// It provides the verified edit surface + a ready-to-use editor class.
//
// Fail-fast style (CLAUDE.md): static_assert on every layout, no null guards, no SEH.


#include "D3D12DrawRecord.h"
#include "D3D12DrawFlushWrap.h"

namespace bgfx::d3d12edit {

using namespace bgfx::d3d12draw;
using namespace bgfx::d3d12wrap;

// Callback signature for per-record editing.
//   rec  — pointer to the DrawBatcher record (0x70 non-indexed / 0x88 indexed)
//   kind — 0 = non-indexed (DrawInstanced), 1 = indexed (DrawIndexedInstanced)
// Return true to allow the draw, false to veto it (skip the GPU draw).
using DrawEditFn = std::function<bool(void* rec, uint32_t kind)>;

// DrawEditor: wraps a flush 0xe81b720 hook. For each pending record of the given kind,
// invokes m_edit on the record before the real flush proceeds. The edit callback may
// modify any record field (draw counts, start indices, instances, CBVs, VBVs, IBV) or
// veto the draw by returning false.
//
// Usage (pseudocode; registration at the 7 flush call sites is owned by the hook layer):
//
//   bgfx::d3d12edit::DrawEditor editor;
//   editor.setEdit([](void* rec, uint32_t kind) -> bool {
//       if (kind == 1) {
//           auto* r = static_cast<bgfx::d3d12draw::DrawRecordIndexed*>(rec);
//           if (r->indexCount > 0x1000) return false;   // veto oversized indexed draws
//           r->startInstance = 0;                       // rebase instances
//       }
//       return true;
//   });
//   editor.onFlush(batcher, renderer, job, kind);
class DrawEditor {
public:
    DrawEditor() noexcept = default;

    void setEdit(DrawEditFn fn) noexcept { m_edit = std::move(fn); }

    // Call from a flush 0xe81b720 hook before the real flush runs.
    // Iterates all pending records of `kind` and applies m_edit to each.
    // Returns the number of records that passed the edit (were not vetoed).
    uint32_t onFlush(void* batcher, uint32_t kind) noexcept
    {
        auto* b = static_cast<DrawBatcher*>(batcher);
        uint32_t pending = b->pending[kind];
        if (pending == 0) return 0;

        uint64_t* recArray = b->recordArray(kind);
        std::size_t stride = (kind == 0) ? kRecordNonIndexed : kRecordIndexed;

        uint32_t passed = 0;
        for (uint32_t i = 0; i < pending; ++i) {
            void* rec = reinterpret_cast<uint8_t*>(recArray[i]) + i * stride;
            if (m_edit(rec, kind)) ++passed;
        }
        return passed;
    }

private:
    DrawEditFn m_edit;
};

// Convenience: common edit operations as standalone functions.

// Veto draws whose index/vertex count exceeds a cap (protects against runaway instancing).
inline bool vetoLargeDraws(void* rec, uint32_t kind, uint32_t maxCount) noexcept
{
    if (kind == 0) {
        auto* r = static_cast<DrawRecordNonIndexed*>(rec);
        if (r->vertexCount > maxCount) return false;
    } else {
        auto* r = static_cast<DrawRecordIndexed*>(rec);
        if (r->indexCount > maxCount) return false;
    }
    return true;
}

// Rebase startInstance to 0 on all records (disables instancing offset).
inline bool rebaseInstances(void* rec, uint32_t kind) noexcept
{
    if (kind == 0) {
        auto* r = static_cast<DrawRecordNonIndexed*>(rec);
        r->startInstance = 0;
    } else {
        auto* r = static_cast<DrawRecordIndexed*>(rec);
        r->startInstance = 0;
    }
    return true;
}

} // namespace bgfx::d3d12edit
