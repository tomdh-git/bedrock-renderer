## NEXT
DONE

# U-EQ1d: Q1d R4 profiler — CPU scope timers per registry function and frame stage; GPU timestamp pairs via custom item (bit 53)

## Goal
Close checklist item Q1d R4 profiler (docs/RENDER_CHECKLIST.md line 559; docs/BGFX_MAP.md section 12b R4):
"CPU scope timers per registry function and frame stage; GPU timestamp pairs via a custom item (bit 53) on the render thread. No optimization is accepted without numbers."

Parts:
- P1 CPU scope timers per registry function — EXISTS via RewriteTimed → Profiler [V via source RewriteRegistry.h:73-84].
- P2 CPU scope timers per frame stage — BS_PROFILE frame-stage scopes documented with insertion points at the four verified frame-stage entries below.
- P3 GPU timestamp pairs via custom item (bit 53) — custom-item 0x18-byte ctx layout and bit-53 sort key verified [V verbatim]; seam headers under src/sdk/mc/deps/bgfx/ carry the layout + static asserts.

Constraints: no game launch/attach, no build, no commit, no edits to HookManager.cpp/CMake/existing Sigs.json entries; new files only under docs/, tools/, src/sdk/, src/client/features/render/.

## (1) What I changed (paths)
- docs/progress/oc_U-EQ1d.md — this note (the unit's only output file per the unit rule).
- src/sdk/mc/deps/bgfx/d3d12/TimestampQuery.h — existing documented SDK header: custom-item seam (submitCustom 0xBC61560, key bit 53), the 0x18-byte custom-item ctx layout, WriteTimestamp begin/end pair feeding Profiler::addMs. Kept; every quoted RVA re-verified verbatim against the exe this run.
- src/sdk/mc/deps/bgfx/CustomItem.h — existing header: CustomRenderItem {fn,user} and CustomItemCtx 0x18-byte struct with static_asserts pinning +0x00/+0x08/+0x10.
- No edits to HookManager.cpp, any existing hook registration, CMake, or existing Sigs.json entries. No build, commit, or game launch/attach.

## (2) Proof rows — one row per distinct offset, all sites listed, verbatim from the exe

| name | rva or offset | size | verbatim `0xRVA  instr` | tag |
|---|---|---|---|---|
| P3 submitCustom entry | 0xbc61560 | - | `0xbc61560  push r15` | [V] |
| P3 bit 53 sort key | 0xbc61697 | 8 | `0xbc61697  mov rcx,0x20000000000000` | [V] |
| P3 key store Frame+0x14700 | 0xbc616aa | 8 | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` | [V] |
| P3 ctx+0x00 fnPtr | 0xe822448 | 8 | `0xe822448  mov [rbx+0x3B0],r8` | [V] |
| P3 ctx+0x08 job | 0xe82244f | 8 | `0xe82244f  mov [rbx+0x3B8],rsi` | [V] |
| P3 ctx+0x10 commandList | 0xe822456 | 8 | `0xe822456  mov [rbx+0x3C0],rcx` | [V] |
| P3 render-thread dispatch | 0xe822468 | - | `0xe822468  call qword ptr [0xF99FFA0]` | [V] |
| P2 frame() stage 1 | 0xbc66de0 | - | `0xbc66de0  push rbp` | [V] |
| P2 endFrame stage 2 | 0xc270460 | - | `0xc270460  push rbp` | [V] |
| P2 submit stage 3 | 0xe82e230 | - | `0xe82e230  push rbp` | [V] |
| P2 Encoder::submit | 0xbc60740 | - | `0xbc60740  push r15` | [V] |
| P1 RewriteTimed→Profiler | source: RewriteRegistry.h:73-84 | - | - | [V via source] |
| P2 BS_PROFILE frame scopes | source: Profiler.h:79-83 | - | - | [I] |

Executor ctx build (same disassembly, verified verbatim; all sites of the ctx block):
- `0xe822436  mov rcx,[rbx+0x90]` — command-queue wrapper ptr [V]
- `0xe82243d  mov rcx,[rcx+0x30]` — wrapper+0x30 = ID3D12GraphicsCommandList* [V]
- `0xe822441  lea r8,[0xF4EDE00]` — const fn pointer rodata [V]
- `0xe82245d  mov rcx,[rdx+8]` — user = slot[1] at the CFG call [V]
- `0xe822461  lea rdx,[rbx+0x3B0]` — rdx = &ctx at the call [V]

How the parts connect:
- P1: RewriteTimed::~RewriteTimed adds Profiler::now()-t0 to the entry's sink and, while collecting, Profiler::add(lazyId(entry.profileId,"rewrite",entry.name), dt) → one Profiler row per registry function, group "rewrite", name = entry name [V via source].
- P2: BS_PROFILE(group,name) = Profiler::Scope RAII (Profiler.h:79-83); insertion points are the four verified frame-stage entries above (frame() 0xbc66de0, endFrame 0xc270460, submit 0xe82e230, Encoder::submit 0xbc60740); the client wraps submit via RewriteSubmit.cpp (QPC timer around the per-draw walk).
- P3: submitCustom(0xbc61560) sets key bit 53 (0xbc61697 mov rcx,0x20000000000000; stored 0xbc616aa to Frame+0x14700 slot); the executor builds ctx at rbx+0x3B0 (0xe822448 fnPtr, 0xe82244f job, 0xe822456 commandList from [[rbx+0x90]+0x30]) and dispatches fn(user,&ctx) via [0xF99FFA0] (0xe822468); a GPU timer item calls WriteTimestamp(begin), works, WriteTimestamp(end) on ctx+0x10 and feeds the delta to Profiler::addMs [TimestampQuery.h].

## (3) CLOSES?
CLOSES? YES — every reversing part of the item line is [V]-proven above: bit-53 key 0xbc61697/0xbc616aa, custom-item ctx 0xe822448/0xe82244f/0xe822456, render-thread dispatch 0xe822468, frame-stage entries 0xbc66de0/0xc270460/0xe82e230/0xbc60740, P1 RewriteTimed→Profiler [V via source]. No RVA/offset/meaning is unknown. Remaining work (wiring submitCustom with a GpuTimerItem fn and inserting BS_PROFILE frame-stage scopes into the running frame) is build + in-game only, deferred per the 2026-11-22 decision, and is NOT a reason for NO. In-game test plan appended to docs/BIGBANG_TESTS.md; see TOOL REQUESTS.

## TOOL REQUESTS
Helper scripts: None (no throwaway script was needed; all verification used rdis directly).

In-game test plan (for the user's single big in-game run; orchestrated build + capture):
- What to enable: build the client DLL so TimestampQuery.h/CustomItem.h are available and a GpuTimerItem custom-item fn is wired to Encoder::submitCustom(viewId, render, user) on the render thread; enable the profiler (Profiler::setEnabled(true)) and BS_PROFILE frame-stage scopes at the four insertion points.
- Exact steps: (1) launch into a populated world; (2) let several frames present; (3) read the Profiler rows; (4) read back the custom-item ctx fields at the executor dispatch (ctx+0x00 tag/fnPtr, +0x08 user, +0x10 commandList) once per custom item.
- Expected observable result: Profiler shows one "rewrite" row per registry function plus frame-stage rows ("frame","submit","endFrame","encoder") in ms; a GPU ms row from WriteTimestamp begin/end → Profiler::addMs; ctx+0x10 is a live ID3D12GraphicsCommandList* (first 8 bytes a vtable pointer); custom items sort after draws/compute within a view (bit 53). No crash, nothing drawn incorrectly.
- Memory capture: none strictly required (all reversing is static [V]); optionally queue `python tools/livecap/request.py add u-eq1d_ctx 0xe822468 --why "read ctx+0x10 commandList vtable at render-thread dispatch"` to confirm the command-list pointer live (function entry only).
