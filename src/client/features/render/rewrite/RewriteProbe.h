#pragma once
#include "client/features/render/rewrite/RewriteDescriptions.h"
#include "sdk/mc/deps/minecraft_renderer/dragon/Tasks.h"

// The frame probe (BGFX_MAP 12b R3), read-only: what one frame of the game contains, keyed by the frame counter. Two feeds:
//   captureFrame(frame)  the bgfx Frame (render thread, after Frame::sort, when the game thread cannot touch it): counters, per-view draw counts, and for the first draws in sorted order
//                        the sort key, view, program (decoded from the key's sort type), PSO state key, buffers, the RenderMark actor mark of the header, and the program's variant key read
//                        from the renderer's program table.
//   noteInsert(group, variant)  every description handed to FrameBuilder::insert (game thread): group, tag, name and size from RewriteDescriptions, an FNV-1a hash of the bytes and the first 0x20
//                        bytes. The three groups the FrameFilterHook slots already see (Item 0x378, Sky 0x370, Ui 0x368) are fed from there by one call each; Effect (0x360), Light (0x380) and
//                        Editor (0x358) get detours of the probe's own, installed on the first endFrame (onEndFrame, a FrameBuilderHook::EndFrameListener).
//   notePassList(list)   the frame-graph task list (TaskDispatchHook listener, game thread): the pass names in dispatch order.
// Armed with BS_PROBE_FRAMES=N (the next N frames are logged in full), or armFrames(N). Nothing is written to the game.
struct RewriteProbe {
    static constexpr uint32_t kMaxDrawLines = 64;
    static void armFrames(uint32_t frames);
    static void initFromEnvironment();
    static bool armed() { return sArmed.load(std::memory_order_relaxed) > 0; }
    static void captureFrame(const uint8_t* frame);        // render thread
    static void notePassList(dragon::TaskList& list);      // TaskDispatchHook::Listener, game thread
    static void noteInsert(RewriteGroup group, const void* variant); // game thread, variant = {description*, tag}; no-op unless armed
    static void onEndFrame(void* frameBuilder);            // FrameBuilderHook::EndFrameListener: installs the probe's insert detours once, closes the frame's description list

    // The program id a sort key carries: sort type is bits 50..51 (0 default, 1 depth, 2 sequence), see bgfx::SortKey.
    static uint32_t programOfKey(uint64_t key);

    static inline std::atomic<uint32_t> sArmed{0};
};
