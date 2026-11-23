#pragma once
// RendererContextD3D12 lifecycle vtable slots (Minecraft.Windows.exe 1.26.62.01, image-base RVAs).
// Source of truth for the offsets/RVAs/sizes: static disassembly of the exe (docs/BGFX_MAP.md
// sections 6f, 6ak, 6ay, 6aw; rows re-verified with rdis for unit U-EN2a, all [V]).
// Constants only: nothing here casts to the game, nothing is included by a game TU yet.
// The live object is the "Direct3D 12 RTX" subclass (vtable 0xF4EEE80) over the base D3D12
// vtable (0xF4ED2D0); slot N lives at vtable + N*8.
//
// Related checklist item: N2a — "Slot 6 Present, slot 60 reset, slot 59 shutdown, slot 7 TDR
// handled by replacement without breaking device-lost — BGFX_MAP 10; 6f; B8a/B8b".


namespace bgfx::d3d12::lifecycle {

static constexpr uintptr_t kVtableBaseD3D12 = 0xF4ED2D0;  // [V] base D3D12 context vtable
static constexpr uintptr_t kVtableRtx = 0xF4EEE80;        // [V] live object's vtable (RTX subclass)

// Slot 50 submit — the seam a replacement wraps (not itself a lifecycle slot; listed for context).
// Base 0xe82e230 (0x4d91 bytes); RTX override 0xe83d440 wraps it. [V]
static constexpr uintptr_t kSubmitBase = 0xE82E230;
static constexpr uintptr_t kSubmitRtxOverride = 0xE83D440;

// Slot 6 Present (+0x30): 0xe811fb0, 0x504 bytes. [V]
//   Guards: [this+0x2D8] swapchain != 0 and [this+0x19F88] init level >= 5, else skips.
//   SyncInterval = bit 7 of [this+0x19F80]; Flags = 0 vsync else DXGI_PRESENT_ALLOW_TEARING (4).
//   Extra windows: u16 count [this+0x2F8], 0x68-stride records at [this+0xC97698], dirty byte +0x64.
//   Present: extra windows via [rec]->vtbl+0x40; main swapchain via [[this+0x2D8]]->vtbl+0x40;
//   GetLastPresentCount via vtbl+0x88.
static constexpr uintptr_t kPresentFn = 0xE811FB0;   // [V] slot 6 entry
static constexpr size_t kPresentSize = 0x504;        // [V] rdis fn size

// Slot 7 TDR / device-lost (+0x38): 0xe8102b0, 0x1924 bytes. [V]
//   Reads [this+0x2D8], [this+0x19F88], [this+0xC9C6D0], queue [this+0xCC9268], state [this+0x19F88..8C];
//   DRED dispatch via [obj+0x70] slot 14; sets device-lost byte [this+0x19F85]=1;
//   final "Device Lost FAILED 0x%08x %s (%s)" via 0xbc5f110.
//   HRESULT name table covers DXGI_ERROR_DEVICE_REMOVED/RESET/HUNG/DRIVER_INTERNAL_ERROR/NOT_CURRENTLY_AVAILABLE.
static constexpr uintptr_t kDeviceLostFn = 0xE8102B0;  // [V] slot 7 entry
static constexpr size_t kDeviceLostSize = 0x1924;      // [V] rdis fn size

// Slot 59 shutdown / resetResources (+0x1D8): 0xe80dec0, 0xdad bytes; RTX override 0xe83e980. [V]
//   Null-guards [this+0x400] device; drains queue [this+0xCC9268] via 0xe80ecb0 (INFINITE);
//   releases the 0x19F08 block via 0xe81ac80; zeroes extra-window records (0x68 stride at 0xC97698).
static constexpr uintptr_t kShutdownFn = 0xE80DEC0;    // [V] slot 59 entry, base
static constexpr size_t kShutdownSize = 0xDAD;         // [V] rdis fn size
static constexpr uintptr_t kShutdownRtxOverride = 0xE83E980;  // [V] per BGFX_MAP 6al

// Slot 60 reset (+0x1E0): 0xe81a610, 0x670 bytes; RTX override 0xe83ec70 (0x55e, DLSS mode select)
//   delegates to base at 0xe83ed53 (`call 0xe81a610`). [V]
//   Applies reset flags (Frame+0xDC5810): bit 0x100 -> [this+0x19FD8] = 0x10 else 1; bit 17 -> byte
//   [this+0x19FDC]; stores backbuffer u16 width/height at [this+0xC9C6C4]/[this+0xC9C6C6] and pixel
//   count dword at [this+0xC9C6C0]; flushes the deferred-release ring via 0xebce430; device-side
//   recreation via 0xe80ee80. Failure (0x887A0004, device-removed family) funnels into slot 7 TDR
//   when [this+0x19F88] >= 5.
static constexpr uintptr_t kResetFn = 0xE81A610;       // [V] slot 60 entry, base
static constexpr size_t kResetSize = 0x670;            // [V] rdis fn size
static constexpr uintptr_t kResetRtxOverride = 0xE83EC70;   // [V] RTX override entry
static constexpr uintptr_t kResetRtxDelegatesToBase = 0xE83ED53;  // [V] `call 0xe81a610` inside the override

// Slot field offsets within the vtable (slot * 8).
static constexpr size_t kSlotPresent = 6;     // vtable +0x30
static constexpr size_t kSlotDeviceLost = 7;  // vtable +0x38
static constexpr size_t kSlotShutdown = 59;   // vtable +0x1D8
static constexpr size_t kSlotReset = 60;      // vtable +0x1E0
static constexpr size_t kSlotSubmit = 50;     // vtable +0x190 (the seam being replaced)
static_assert(kSlotPresent * 8 == 0x30 && kSlotDeviceLost * 8 == 0x38 && kSlotShutdown * 8 == 0x1D8 &&
              kSlotReset * 8 == 0x1E0 && kSlotSubmit * 8 == 0x190);

// Replacement contract (N2a / B8a / B8b). A replacement of slot 50 submit must preserve all four
// lifecycle slots so device-lost handling is not broken:
//   1. Delegate slots 6, 59 and 60 to the original context vtable, or reimplement equivalent
//      DXGI/D3D12 behavior (swapchain present, ordered resource release, reset/resize with the
//      same flag handling).
//   2. Never swallow DXGI_ERROR_DEVICE_REMOVED / _HUNG / _RESET (device-removed family HRESULTs,
//      incl. 0x887A0004 seen at 0xe81a610's reset failure path) from the replacement's own calls;
//      funnel them to slot 7 so its DRED report still fires and device-lost byte [this+0x19F85]
//      is still set.
//   3. Slot 7 itself must remain the original TDR handler (0xe8102b0) or a reimplementation that
//      keeps the DRED dispatch ([obj+0x70] slot 14) and the final "Device Lost FAILED 0x%08x %s (%s)"
//      via 0xbc5f110 verbatim.

} // namespace bgfx::d3d12::lifecycle
