#pragma once

// Custom item seam: Encoder::submitCustom(viewId, fn, user) stores {fn, user} as a 16-byte payload
// at Frame+0xB4700 + idx*0x80 (key bit 53 = 0x0020000000000000), and the executor invokes
// fn(user, &ctx) on the render thread in view order, with ctx a 0x18-byte struct:
//   ctx+0x00 FnPtr (const rip-relative pointer, 0xF4EDE00 in 1.26.62.01)
//   ctx+0x08 job (the PassTask/render state, rsi at the call)
//   ctx+0x10 commandList ([[rbx+0x90]+0x30] at the call)
// All offsets from verbatim disassembly of 0xbc61560 (submit) and 0xe822400 (executor custom path).
//
// NOTE: an earlier draft (TimestampQuery.h) mislabeled ctx+0x00 as "user". Verbatim disassembly
// shows rcx = [rdx+8] = slot[1] = user at the call, while ctx+0x00 = FnPtr. The FnPtr field is
// the const function pointer loaded by `lea r8,[0xF4EDE00]` at 0xe822441.
//
// [V] = verbatim from rdis disassembly of 1.26.62.01; [I] = inferred.

namespace bgfx {

static constexpr uint64_t kCustomBit = 0x0020000000000000ull; // bit 53 of the sort key [V 0xbc61697]
static constexpr size_t kCustomItemSize = 16;                   // two payload words {fn, user} [V movaps]

// The 16-byte custom item stored by submitCustom at encoder+0x100 (fn) and +0x108 (user),
// then copied verbatim (movaps) to Frame+0xB4700 + idx*0x80.
#pragma pack(push, 1)
struct CustomRenderItem {
    void* fn;   // +0x00 callback, invoked on the render thread [V 0xbc61645 / 0xe822426]
    void* user; // +0x08 user data (the PassTask object for pass-task callers) [V 0xbc6164c / 0xe82245d]
};
#pragma pack(pop)
static_assert(sizeof(CustomRenderItem) == kCustomItemSize);
static_assert(offsetof(CustomRenderItem, fn) == 0x00);
static_assert(offsetof(CustomRenderItem, user) == 0x08);

// The 0x18-byte context built by the executor before calling fn(user, &ctx).
#pragma pack(push, 1)
struct CustomItemCtx {
    void* fnPtr;        // +0x00 const function pointer (rip-relative 0xF4EDE00) [V 0xe822441/0xe822448]
    void* job;          // +0x08 job/render state (rsi at the call) [V 0xe82244f]
    void* commandList;  // +0x10 [[rbx+0x90]+0x30] [V 0xe822436/0xe82243d/0xe822456]
};
#pragma pack(pop)
static_assert(sizeof(CustomItemCtx) == 0x18);
static_assert(offsetof(CustomItemCtx, fnPtr) == 0x00);
static_assert(offsetof(CustomItemCtx, job) == 0x08);
static_assert(offsetof(CustomItemCtx, commandList) == 0x10);

// Callback signature: fn(user, &ctx) runs on the render thread in view order.
// rcx = user (= slot[1] = CustomRenderItem::user), rdx = &ctx at the CFG-thunk call [V 0xe82245d/0xe822461/0xe822468].
using CustomItemFn = void (*)(void* user, CustomItemCtx* ctx);

} // namespace bgfx
