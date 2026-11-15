# Dossier: queue idle wait / frame-context submit helper (0xe80ecb0)

Static decode from rdis `sum` on `Minecraft.Windows.exe` (1.26.62.01).

## Mechanical facts

- [V] RVA 0xe80ecb0, ~0x1c6 bytes, 17 blocks. Stack cookie `[0x1230A0C0]`.
- [V] Callers (from existing notes): slot 8 path / submit/shutdown/reset flows (used as "wait for queue idle", 6av). In this build: called as `wait(queueMgr, timeout?)` and also coordinates frame-context ring retirement.
- [V] Direct callees: 0xe81b3b0 (poll fence), 0xe818490 (frame retire/deferred-release drain), 0xeec59e0, 0xe951550. Indirect: queue/command vtbl slot 10 `ExecuteCommandLists` (+0x50) and slot 14 `Signal` (+0x70) on `*(mgr)`.

## Signature (real argument list and calling convention)

- [V] `void waitIdle(QueueManager* mgr /*rcx/a0*/, uint32_t timeoutMs /*rdx/a1*/)`. Returns result of retire helper in rax on success path [V sum].
- [V] `mgr` layout (offsets relative to mgr): `+0x0` queue COM object; `+0x2F8C020` pending-submit count/index; `+0x2F8B7A0` array of command-list pointers (indexed by pending count); `+0x2F8C8A8/+0x2F8C8B0` ring head/count (0x110 sentinel/free-pool management, shared with 0xe81ac80/0xe818490); `+0x2F8D148` fence/sync object.

## Pseudocode

```cpp
// [V] 0xe80ecb0
void waitIdle(QueueManager* mgr, uint32_t timeoutMs) {
    if (mgr->pendingSubmitCount /*+0x2F8C020*/ != 0) {          // 0xe80ecde
        // publish a frame context into in-flight ring and ExecuteCommandLists
        FrameCtx* ctx = ringAllocSlot(mgr);                      // uses +0x2F8C8A8/B0 -> +0x2F8C028 entries
        ctx->fenceValue /*+0x2CBD0*/ = mgr->fence->value /*+0x28*/; // 0xe80ed15
        ctx->inFlight  /*+0x2CBD8*/ = 1;                         // 0xe80ed20
        enqueueInflight(mgr, ctx);                               // ring arrays +0x2F8C8B8/heads
        (*mgr->queue)->ExecuteCommandLists(n, &mgr->cmdLists[0]); // vtbl +0x50, 0xe80eda5
        mgr->pendingSubmitCount = 0;
        mgr->fence->value++;                                     // [fence+0x28]
        (*mgr->queue)->Signal(fence, value);                     // vtbl +0x70, 0xe80edcf
        waitFenceObject(fence);                                  // 0xe80ee0c indirect
    }
    pollFence(mgr->fenceObj);                                    // 0xe81b3b0
    retire(mgr, mgr->fence->value - 1, timeoutMs);               // 0xe818490: drain completed frame contexts/releases
}
```

## Structs / storage touched

- [V] Frame context record fields: `+0x2CBD0` fence value, `+0x2CBD8` in-flight byte (matches 0xe818490 retire checks). In-flight ring/pool uses 0x110 slots at `+0x2F8C028` / `+0x2F8C8B8` with heads/counts at `+0x2F8C8A8/+0x2F8C8B0/+0x2F8D138/+0x2F8D140` (shared machinery with 0xe81ac80/0xe81af20/slot 62).
- [V] Fence wrapper: `+0x18` ID3D12Fence*, `+0x28` current/completed value counter manipulated here.

## Version-stable anchors

- [V] Coupling of ExecuteCommandLists (queue vtbl +0x50), Signal (+0x70), fence increment, and retire call 0xe818490; 0x110 ring sentinel; offsets `+0x2F8C020`, `+0x2F8B7A0`, `+0x2F8D148`, frame-ctx `+0x2CBD0/+0x2CBD8`.

## Verification

- [V] Static sum decode on 62.01. Exact queue/fence COM types inferred from vtable slot usage and surrounding code [I]. D2.

## Audit / contradictions

- [V] Extends 6av: gives concrete helper behavior behind "wait for queue idle" (0xe80ecb0) including command-list execution+signal and retirement via 0xe818490. Confirms 0xe818490 is retire/drain (called here to retire completed contexts), contradicting labels that call 0xe818490 "per-view setup".
