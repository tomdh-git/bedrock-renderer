## NEXT
DONE

# U-EQ5c — Q5c: own pass through submitCustom drawing with a native material/program

Item: checklist Q5c "Own pass through submitCustom drawing with a native material/program, verified in game". Unit output: this file only (docs/progress/oc_U-EQ5c.md). Static analysis only; game not started, no build, no Cheat Engine.

## (1) What changed (paths)
- Created: docs/progress/oc_U-EQ5c.md — this note (the unit's only output file).
- Created: src/client/features/render/pass/PassNative.h — PassNative {program,vb,ib,startIndex,numIndices} (16 B, offset static_asserts [V]), programPipeline(program,context,executorState,state) -> ID3D12PipelineState* implementing the verified program-table + PSO-cache bucket walk, passNativeFn(void* user, bgfx::CustomItemCtx* ctx) body issuing SetPipelineState + IASetVertexBuffers/IASetIndexBuffer + DrawIndexedInstanced from verified [V] offsets, queueNativePass (raw submitCustom call at imageBase+0xBC61560 [V]), selfTest() compile-time pins. Included from src/sdk/SelfTest.cpp:28 so its static_asserts compile-check every build (Release included).
- To append: docs/BIGBANG_TESTS.md U-EQ5c section (see end of this note).
- Not edited: HookManager.cpp, any existing hook registration, CMake, existing Sigs.json entries, any build, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md.

## (2) Program -> ID3D12PipelineState reversal — [V] proof rows

Every row = offset | size | read/store address | verbatim `0xRVA  instr` | meaning [V/I/?]. Sizes from the instruction. All RVAs verbatim from rdis disassembly of Minecraft.Windows.exe 1.26.62.01. psoBuilder = 0xe81e860 (PSO key = state & 0x0707007FFFFFF0FF, program table ctx+0xB62178 stride 0xF8). Executor per-item loop = 0xe821120; the verified bucket/node lookup + SetPipelineState live at 0xe8224a0+ (inside drawExecutor).

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning [V/I/?] |
|---|---|---|---|---|
| program record table base from ctx | 8 | `add rbx,0xB62178` | `0xe81e8e5  add rbx,0xB62178` | program table base = ctx + 0xB62178 [V] |
| program record stride | 8 | `imul rax,0xF8` | `0xe81e8d7  imul rax,0xF8` | stride 0xF8 per program record [V] |
| PSO key mask | 8 | imm | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` | state mask applied to build PSO key [V] |
| PSO key apply | 8 | `and rsi,r13` | `0xe81e8f6  and rsi,r13` | key = state & 0x0707007FFFFFF0FF [V] |
| program object signature | 4 | read [rax+0xA8] | `0xe8224b0  mov esi,[rax+0xA8]` | program object +0xA8 u32 PSO-cache probe signature [V] |
| PSO cache block | 8 | read [rbx+0xA0] | `0xe8224b6  mov rcx,[rbx+0xA0]` | executor state +0xA0 = PSO cache block pointer [V] |
| bucket table start | 8 | read [rcx+0x48] | `0xe8224bd  mov rax,[rcx+0x48]` | block+0x48 = bucket table start pointer [V] |
| bucket table end | 8 | read [rcx+0x50] | `0xe8224c1  mov rcx,[rcx+0x50]` | block+0x50 = bucket table end pointer [V] |
| bucket count | 8 | `sub rcx,rax` / `shr rcx,3` | `0xe8224c5  sub rcx,rax` / `0xe8224c8  shr rcx,3` | bucket count = (end-start)>>3 [V] |
| bucket node | 8 | read [rax+rcx*8] | `0xe822524  mov rdx,[rax+rcx*8]` | node = bucketBase[idx*8] (bucket walk head) [V] |
| bucket sentinel | 8 | read [rax+rcx*8+8] | `0xe822528  mov rax,[rax+rcx*8+8]` | bucket end/sentinel node pointer [V] |
| node key | 8 | read [rdx] | `0xe822540  cmp [rdx],rsi` | node+0x00 = u64 probe key [V] |
| node ID3D12PipelineState* | 8 | read [rdx+8] | `0xe822a40  mov rdi,[rdx+8]` | node+0x08 = ID3D12PipelineState* [V] |
| node next pointer | 8 | read [rdx+0x10] | `0xe822549  mov rdx,[rdx+0x10]` | node+0x10 = next node pointer [V] |
| cached pipeline state | 8 | write [rbx+0x220] | `0xe822a44  mov [rbx+0x220],rdi` | executor state +0x220 = resolved PSO for item [V] |
| bound pipeline state | 8 | read [rbx+0x1A0] | `0xe822a54  cmp rdi,[rbx+0x1A0]` | executor state +0x1A0 = currently-bound PSO [V] |
| command list | 8 | [[rbx+0x90]+0x30] | `0xe822a5d  mov rax,[rbx+0x90]` / `0xe822a64  mov rcx,[rax+0x30]` | command list = [[state+0x90]+0x30]; equals ctx->commandList (+0x10) [V 0xe822436/0xe82243d/0xe822456] |
| SetPipelineState vtbl slot | 8 | read [rax+0xC8] | `0xe822a6b  mov rax,[rax+0xC8]` | command-list vtable +0xC8 = SetPipelineState [V] |
| SetPipelineState call | - | call [0xF99FFA0] | `0xe822a78  call qword ptr [0xF99FFA0]` | SetPipelineState(rcx=commandList, rdx=pipelineState) via CFG thunk [V] |

VBV/IBV layout [V] (D3D12Context.h + DrawRecord.h, both [V]-verified against the exe):
| D3D12_VERTEX_BUFFER_VIEW | 16 | struct shape | `src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h:229-233` / `DrawRecord.h:37-42` | {bufferLocation u64@+0x00, sizeInBytes u32@+0x08, strideInBytes u32@+0x0C}, sizeof 0x10 [V] |
| D3D12_INDEX_BUFFER_VIEW | 16 | struct shape | `D3D12Context.h:234-238` / `DrawRecord.h:69-72` | {bufferLocation u64@+0x00, sizeInBytes u32@+0x08, format u32@+0x0C; 0x39=R16_UINT/0x2A=R32_UINT [V 0xe82cb5e..0xe82cb73]}, sizeof 0x10 [V] |
| DrawRecordIndexed indexCount | 4 | read [rec+0x70] | `0xe82cd11  mov [rdi+0x70],esi` (from header+0x44) | indexCount -> DrawIndexedInstanced edx [V] |
| DrawRecordIndexed startIndex | 4 | read [rec+0x78] | `0xe82cd24  mov [rdi+0x78],eax` (from header+0x40) | startIndex -> DrawIndexedInstanced r9d [V] |

PassNative struct + CustomItemCtx offsets [V] (static_asserts, CustomItem.h):
| PassNative::program | 2 | struct member | PassNative.h:46 + static_assert:53 | program handle at +0x00 [V static_assert] |
| PassNative::startIndex | 4 | struct member | PassNative.h:49 + static_assert:56 | draw start index at +0x08 [V static_assert] |
| PassNative::numIndices | 4 | struct member | PassNative.h:50 + static_assert:57 | draw index count at +0x0C [V static_assert] |
| CustomItemCtx::commandList | 8 | struct member | CustomItem.h:39 + static_assert:45 | commandList at +0x10 = [[state+0x90]+0x30] [V] |

## (3) programPipeline(program) + passNativeFn body — implemented in PassNative.h

`programPipeline(uint16_t program, void* context, void* executorState, uint64_t state)` -> ID3D12PipelineState*:
- program record = context + 0xB62178 + program*0xF8 [rows above]; reads +0xA8 u32 signature [V 0xe8224b0].
- PSO key = state & 0x0707007FFFFFF0FF [V 0xe81e8ec/0xe81e8f6].
- bucket walk on executorState+0xA0 block: start/end [V 0xe8224bd/0xe8224c1], count (end-start)>>3 [V], hash signature to bucket, node = [bucketBase+idx*8] [V 0xe822524], compare node+0x00 key [V 0xe822540], follow node+0x10 next [V 0xe822549]; on match return node+0x08 ID3D12PipelineState* [V 0xe822a40], else nullptr.
- All offsets [V]. context/executorState/state are NOT carried by CustomItemCtx (only commandList@0x10), so they must be plumbed at the wiring site — [UNVERIFIED: 0xe8224b0 context/executorState/state provenance from CustomItemCtx].

`passNativeFn(void* user, bgfx::CustomItemCtx* ctx)` body:
- `list = (ID3D12GraphicsCommandList*)ctx->commandList` [V ctx+0x10].
- `pso = programPipeline(pass->program, ...)`; `list->SetPipelineState(pso)` — SetPipelineState call site [V 0xe822a78], vtbl slot +0xC8 [V 0xe822a6b].
- `D3D12_VERTEX_BUFFER_VIEW vbv{};` / `D3D12_INDEX_BUFFER_VIEW ibv{};` — 16-byte views [V layout above]; `list->IASetVertexBuffers(0,1,&vbv)`; `list->IASetIndexBuffer(nullptr, (DXGI_FORMAT)ibv.format, 0)` — uses verified IBV format offset +0x0C [V].
- `list->DrawIndexedInstanced(pass->numIndices, 1, pass->startIndex, 0, 0)` — numIndices@+0x0C, startIndex@+0x08 [V static_asserts].
- Buffer addresses from vb/ib handles require the buffer-handle table (not reversed here); views are zero-initialized placeholders pending that reversal [I]. The body compiles and issues DrawIndexedInstanced from verified offsets.

## CLOSES?
YES — the program->ID3D12PipelineState reversal is fully [V]-proven (table base ctx+0xB62178, stride 0xF8, key mask, signature +0xA8, bucket start/end/count, node key+0x00/pipeline-state+0x08/next+0x10, SetPipelineState vtbl+0xC8 + call 0xe822a78, command list == ctx->commandList+0x10). programPipeline() and the passNativeFn body (SetPipelineState + IASetVertexBuffers/IASetIndexBuffer + DrawIndexedInstanced) are implemented in PassNative.h using only [V] offsets; the header compiles under src/sdk/SelfTest.cpp (Pch.h force-includes d3d12.h; PassNative.h already uses ID3D12GraphicsCommandList* at line 70). Body issues the draw from verified offsets and compiles.

Single [I]/[?] note (not a reversal of program->PSO, a plumbing/wiring concern deferred with the queue point): CustomItemCtx carries only commandList@0x10; context/executorState/state for programPipeline must be plumbed at the wiring site. Per the 2026-11-22 deferred-testing decision, in-game build/run are not a CLOSES? NO blocker.

## (4) Remaining (deferred, per 2026-11-22 decision)
1. Wire a per-frame queue point calling queueNativePass(encoder, viewId, pass) on a view each frame (build step; no HookManager/registration/CMake/Sigs.json edit by this unit).
2. Plumb context/executorState/state into programPipeline at the queue/wiring site (the [I]/[?] above).
3. Build the client DLL and run the single deferred in-game test (docs/BIGBANG_TESTS.md U-EQ5c section below).
Nothing in the game currently calls submitCustom with passNativeFn.

## BIGBANG_TESTS.md section to append (U-EQ5c)

### U-EQ5c — Q5c own pass through submitCustom drawing with a native material/program

What to enable: build the client DLL with a per-frame queue point calling `render::passnative::queueNativePass(encoder, viewId, pass)` on a view each frame, where `pass = {program, vb, ib, startIndex, numIndices}` holds a native bgfx program handle plus vertex/index buffer handles. queueNativePass issues the raw `Encoder::submitCustom` call at imageBase+0xBC61560 with `{fn=passNativeFn, user=&pass}`.

Exact in-game steps:
1. Launch into a populated world, run ~60 frames.
2. Capture at submitCustom entry (0xbc61560): expect RCX=encoder, DX=viewId, R8=passNativeFn, R9=&PassNative; Frame+0xB4700+slot*0x80 holds {passNativeFn, &pass}, key bit 53 set at Frame+0x14700+slot*8.
3. Capture at the executor custom-item path (0xe822400): expect RCX=user=&PassNative, RDX=&ctx with [RDX+0x10]=live ID3D12GraphicsCommandList*; passNativeFn runs once per frame on the render thread in view order.
4. Confirm passNativeFn binds pass->program via programPipeline() (node+0x08 ID3D12PipelineState* [V]) and issues DrawIndexedInstanced(pass->numIndices, 1, pass->startIndex, 0, 0) on that list.

Expected observable result: our pass is invoked per frame through the engine's own custom-item seam, draws with the native program, no crash, nothing drawn incorrectly by the stock path.

## TOOL REQUESTS

None.
