#pragma once
// GPU timestamp pairs via the custom-item seam (bit 53), Q1d R4 profiler.
// Target: Minecraft.Windows.exe 1.26.62.01, image-base RVAs. Static documentation only;
// nothing here reads or writes game memory and nothing is installed by default.
//
// How a custom item runs GPU timestamps on the render thread (decoded [V], verbatim):
//
//   Encoder::submitCustom(view, fn, user) 0xBC61560 (EncoderRvas.kSubmitVariant2) builds the
//   sort key with bit 53 set and stores the two payload words at Encoder+0x100 (fn) and
//   +0x108 (user) [V: docs/progress/oc_U-A6c.md, 0xbc61645/0xbc6164c].
//
//   The D3D12 draw executor handles key bit 53 at 0xe822400 by building a 0x18-byte context
//   at rbx+0x3B0 and calling `fn(user, &ctx)` through the CFG thunk [0xF99FFA0]:
//
//     0xe822436  mov rcx,[rbx+0x90]          ; command-queue wrapper ptr
//     0xe82243d  mov rcx,[rcx+0x30]          ; wrapper+0x30 = ID3D12GraphicsCommandList*
//     0xe822448  mov [rbx+0x3B0],r8          ; ctx+0x00 = const fn pointer
//     0xe82244f  mov [rbx+0x3B8],rsi         ; ctx+0x08 = job field
//     0xe822456  mov [rbx+0x3C0],rcx         ; ctx+0x10 = ID3D12GraphicsCommandList*
//     0xe822468  call qword ptr [0xF99FFA0]  ; fn(user=ctx+0x00, &ctx=rbx+0x3B0)
//
//   So ctx is a 0x18-byte block laid out { const ptr +0x00, job field +0x08,
//   ID3D12GraphicsCommandList* +0x10 }. The fn runs on the bgfx render thread, in view order
//   (custom items sort after draws/compute inside a view), with the live D3D12 command list at
//   ctx+0x10. A GPU timestamp pair is therefore:
//
//     ID3D12GraphicsCommandList* list = *(ID3D12GraphicsCommandList**)(ctx + 0x10);
//     list->WriteTimestamp(D3D12_QUERY_TYPE_TIMESTAMP, beginQueryHeap, beginIndex);  // start
//     ... our measured work ...
//     list->WriteTimestamp(D3D12_QUERY_TYPE_TIMESTAMP, endQueryHeap, endIndex);        // end
//
//   The delta (end - begin) ticks / timestamp-frequency is fed to Profiler::addMs(id, ms),
//   producing a Profiler row with unit "ms" next to the CPU scope rows.
//
// Usage (not compiled into the DLL, not enabled by default):
//
//   struct GpuTimerItem {
//       static void __fastcall fn(void* user, void* ctx) {
//           auto* list = *reinterpret_cast<ID3D12GraphicsCommandList**>(
//               static_cast<uint8_t*>(ctx) + kCustomCtxCommandList);
//           list->WriteTimestamp(D3D12_QUERY_TYPE_TIMESTAMP, mBeginHeap, mBeginIdx);
//           list->WriteTimestamp(D3D12_QUERY_TYPE_TIMESTAMP, mEndHeap,   mEndIdx);
//       }
//   };
//   encoder->submitCustom(viewId, &GpuTimerItem::fn, &gpuTimerItem);
//
// Offsets (all [V] verbatim-decoded from 0xe822400 on 1.26.62.01):
namespace bgfx::d3d12 {

struct GpuTimestampCustomItem {
    // Custom-item context layout (0x18 bytes, executor builds it at rbx+0x3B0).
    static constexpr std::size_t kCustomCtxFnPtr = 0x00;   // const fn pointer (executor const)
    static constexpr std::size_t kCustomCtxJob = 0x08;     // job field
    static constexpr std::size_t kCustomCtxCommandList = 0x10; // ID3D12GraphicsCommandList*

    // submitCustom target (EncoderRvas.kSubmitVariant2), key bit 53.
    static constexpr uintptr_t kSubmitCustomRva = 0xBC61560;

    // Sort-key bits, from Encoder::submit / Frame::sort (docs/progress/oc_U-A6c.md).
    static constexpr uint64_t kCustomBit = 0x0020000000000000ull; // bit 53
    static constexpr uint64_t kViewShift = 54;

    // Encoder payload-word offsets written by submitCustom (docs/progress/oc_U-A6c.md).
    static constexpr std::size_t kEncoderFnPtr = 0x100;   // Encoder+0x100 = fn
    static constexpr std::size_t kEncoderUser = 0x108;    // Encoder+0x108 = user data
};

} // namespace bgfx::d3d12
