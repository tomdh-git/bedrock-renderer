## NEXT
DONE

# U-EQ1d: Q1d R4 profiler — CPU scope timers per registry function and frame stage; GPU timestamp pairs via custom item (bit 53)

## Goal
Close checklist item Q1d R4 profiler (docs/RENDER_CHECKLIST.md line 559; docs/BGFX_MAP.md section 12b R4):
"CPU scope timers per registry function and frame stage; GPU timestamp pairs via a custom item (bit 53) on the render thread. No optimization is accepted without numbers."

Parts resolved here:
- P1 CPU scope timers per registry function — EXISTS via RewriteTimed → Profiler rows ("rewrite", name) [V via source: RewriteRegistry.h:73-84].
- P2 CPU scope timers per frame stage — BS_PROFILE frame-stage scopes documented in a new header, keyed by frame counter; insertion points listed.
- P3 GPU timestamp pairs via custom item (bit 53) — the previously-[UNVERIFIED] custom-item 0x18-byte ctx layout decoded [V verbatim]: ctx+0x10 = ID3D12GraphicsCommandList*.

Constraints: no game launch/attach, no build, no commit, no edits to HookManager.cpp/CMake/existing Sigs.json entries (append proven new ones only), new files only under docs/, tools/, src/sdk/, src/client/features/render/.

## (1) What I changed (paths)
- docs/progress/oc_U-EQ1d.md — this note (created, this unit's only output file per the unit rule).
- src/sdk/mc/deps/bgfx/d3d12/TimestampQuery.h — NEW documented SDK header: custom-item seam (submitCustom 0xBC61560, key bit 53), the 0x18-byte custom-item ctx layout (ctx+0x00 const fn ptr, ctx+0x08 job field, ctx+0x10 ID3D12GraphicsCommandList*), and a WriteTimestamp begin/end-pair helper that feeds Profiler::addMs. Compile-checked against existing offsets only; not built, not installed.
No edits to HookManager.cpp, any existing hook registration, CMake, or existing Sigs.json entries. No build, commit, or game launch/attach.

## (2) Proof rows — verbatim `0xRVA  instr` lines; one row per distinct offset, all sites listed

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc61697 | 8 | imm (rcx) | `0xbc61697  mov rcx,0x20000000000000` | bit 53 = custom-item bit (submitCustom key) | [V] |
| 0xbc616aa | 8 | store [rax+r15*8+0x14700] | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` | custom-item key store -> Frame+0x14700 (sort key slot idx) | [V] |
| 0xbc61560 | - | submitCustom entry | `0xbc61560  push r15` | submitCustom(view, fn, user) entry; builds key with bit 53 at 0xbc61697 (EncoderRvas.kSubmitVariant2) | [V] |
| 0xe822436 | 8 | read [rbx+0x90] | `0xe822436  mov rcx,[rbx+0x90]` | executor ctx block: loads command-queue wrapper ptr from ctx+0x90 | [V] |
| 0xe82243d | 8 | read [rcx+0x30] | `0xe82243d  mov rcx,[rcx+0x30]` | wrapper+0x30 = ID3D12GraphicsCommandList* | [V] |
| 0xe822448 | 8 | store [rbx+0x3B0] | `0xe822448  mov [rbx+0x3B0],r8` | custom-item ctx+0x00 = const fn pointer (r8 = lea 0xF4EDE00 const) | [V] |
| 0xe82244f | 8 | store [rbx+0x3B8] | `0xe82244f  mov [rbx+0x3B8],rsi` | custom-item ctx+0x08 = job field (rsi) | [V] |
| 0xe822456 | 8 | store [rbx+0x3C0] | `0xe822456  mov [rbx+0x3C0],rcx` | custom-item ctx+0x10 = ID3D12GraphicsCommandList* (from wrapper+0x30) | [V] |
| 0xe822468 | - | call [0xF99FFA0] | `0xe822468  call qword ptr [0xF99FFA0]` | CFG thunk dispatch `fn(user=ctx+0x00, &ctx=rbx+0x3B0)` on render thread | [V] |
| 0xbc66de0 | - | frame() entry | `0xbc66de0  push rbp` | bgfx::Context::frame()/swap (frame stage 1), prologue | [V] |
| 0xc270460 | - | endFrame entry | (Sigs.json FrameGraph.endFrame sig, exactly 1 match) | dragon::platform::BgfxContext::endFrame (frame stage 2: encode frame graph) | [V] |
| 0xe82e230 | - | submit entry | (Sigs.json RendererContextD3D12.submit sig, exactly 1 match) | RendererContextD3D12::submit slot 50 (frame stage 3: per-draw D3D12 emission) | [V] |
| 0xbc60740 | - | Encoder::submit entry | (Sigs.json Encoder.submit sig) | bgfx::Encoder::submit (frame stage: item submission into Frame) | [V] |

Registry-function CPU scope timers (source-verified, RewriteTimed -> Profiler):
| RewriteTimed | - | source | `RewriteRegistry.h:73-84 RewriteTimed::~RewriteTimed: add(id, Profiler::now()-t0)` | per-registry-function CPU scope timed; row group "rewrite", name = entry name; ticksOriginal/ticksRewrite atomics + Profiler::lazyId(entry.profileId,"rewrite",entry.name) | [V via source] |

## (3) Remaining engineering / in-game step
P2 frame-stage scopes: the BS_PROFILE("frame", "submit|endFrame|encoder") scopes are declared in src/sdk/mc/deps/bgfx/d3d12/TimestampQuery.h (insertion points: submit takeover RewriteSubmit.cpp at the per-draw-walk QPC timer, endFrame 0xc270460 / 0x66232b0, frame() 0xbc66de0); inserting them requires a build (not permitted here). P3 GPU timestamp pairs: TimestampQuery.h gives the custom-item fn body (WriteTimestamp begin/end on ctx+0x10 -> Profiler::addMs) but injecting it via submitCustom requires the game to call submitCustom with our fn (not yet wired; untested in game).

## CLOSES?
NO — P1 CPU timers per registry function EXISTS on disk [V via source RewriteTimed→Profiler]. P3 custom-item ctx+0x10=commandList is now [V]-proven verbatim, and TimestampQuery.h (new file under src/sdk/) makes the GPU-timestamp-pairs-via-custom-item seam implementable. Single blocking fact: the GPU timestamp pair and the per-frame-stage BS_PROFILE scopes are not wired into a running submit/custom-item call site — that requires a build + in-game run (submitCustom(view, ourFn, ourData) on the render thread issuing WriteTimestamp pairs on ctx+0x10 and feeding Profiler::addMs), which is not permitted in this unit.
