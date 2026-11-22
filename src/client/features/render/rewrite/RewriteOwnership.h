#pragma once

// The ownership / threading table of every rewritten function (BGFX_MAP 12b R5). A rewrite must keep the row of the function it replaces. Sources: the dossiers named in each row
// and BGFX_MAP 6as/6ac/11d. Thread names: game = the thread that ticks the game and builds descriptions; task = RenderDragon task threads that run pass bodies and encoders; render = the
// bgfx render thread that runs Frame::sort and the D3D12 submit.
struct RewriteOwnership {
    const char* function;
    const char* thread;     // who calls it
    const char* owns;       // memory it writes and who owns that memory
    const char* lifetime;   // how long the written memory lives
    const char* sharing;    // what is shared with other threads and how it is protected
};

inline constexpr RewriteOwnership kRewriteOwnership[] = {
    {"Math::mat4Multiply 0xAA6580", "game and task threads (extractors, pass setup)", "out[16] supplied by the caller", "caller's", "none: pure, out may alias an input"},
    {"UniformBlock::setVec4Array 0x5679DB0", "game thread (extractors fill the material's uniform block before the description is inserted)", "block data area + slot dirty byte + running hash of one MaterialInstance holder", "until the description/material is released", "one writer at a time per block; no lock in the original"},
    {"ResourceCache::get 0x675E440", "game and task threads", "entry map, stale set, retired vector of the cache; the out shared_ptr of the caller", "cache lifetime; holders are shared_ptr (use count at control+8)", "recursive mutex at cache+0x98 (_Mtx_lock 0xEEC59F0); the rewrite takes the same lock through the game's own function"},
    {"Frame::sort 0xBC61E20", "render thread only", "Frame sort keys, sorted ids, blit keys; scratch of bx::radixSort in the bgfx context (original) or file statics (rewrite)", "one frame: the Frame is double buffered 0xE749C0 apart and the game thread fills the other one", "none: the render thread owns the consume frame between ctx+0x80 (ready) and ctx+0x100 (consumed)"},
    {"Encoder::submit 0xBC60740", "task threads, one encoder per thread", "the encoder's own state; one slot of the Frame (key, id, 0x80 header, 0x540 bind record)", "encoder: thread; Frame slot: the frame", "Frame item counter CAS at Frame+0xDC57E8 (shared by all encoders), view sequence counter ctx+0x1EAAC60 (lock xadd), bind array growth under its own mutex (0xBC7A7C0)"},
};
inline constexpr size_t kRewriteOwnershipCount = sizeof(kRewriteOwnership) / sizeof(kRewriteOwnership[0]);
