## NEXT
DONE

# U-EQ5c — Q5c: own pass through submitCustom drawing with a native material/program

GOAL (this run, overrides prior notes): finish the three remaining placeholders that make passNativeFn non-functional, as [V] rows + code:
(1) vb/ib handle -> D3D12 buffer table (handle table base offset from context/rendererObj, entry stride, fields: GPU virtual address, size, stride) — reverse where the executor builds D3D12_VERTEX_BUFFER_VIEW / index view for a draw record (executor 0xe821120 region);
(2) programPipeline real context/executorState/state arguments derived from CustomItemCtx (ctx+0x08 job field = [executorState+0xB0]; executorState = ctx - 0x3B0; state = [executorState+0x1F0]);
(3) replace the zeroed vbv/ibv in passNativeFn with the resolved views (done in src/client/features/render/pass/PassNative.h).
CLOSES? YES only when passNativeFn issues a draw from [V] resolved pipeline + buffers with no zero placeholders and nullptr arguments.

## (1) vb/ib handle -> buffer table reversal [V static]

Renderer object base (live anchor): `rendererObj = [moduleBase + 0x12BB4910]` [V]. The executor's indexed-record append (0xe82cb08) reads the vb handle from the draw header (`header+0x76`), shifts by 7, and adds rendererObj to reach the vertex-buffer record; the index-buffer record is reached by adding 0x93A178 to the handle-derived address.

| row | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| rendererObj global base | rendererObj [0x12BB4910] | 8 | 0xe82cbb3 | `0xe82cbb3  add r15,[0x12BB4910]` | renderer object base read from the live global; vbHandle<<7 added to it | [V] |
| VB table base offset from rendererObj | VB table +0x9B2178 | 8 | 0xe82cbb3 | `0xe82cbb3  add r15,[0x12BB4910]` | vertex-buffer table at rendererObj+0x9B2178 (r15 = rendererObj + vbHandle*0x80 after 0xe82cbaf) | [V] |
| VB entry stride | VB stride 0x80 | - | 0xe82cbaf | `0xe82cbaf  shl r15d,7` | vbHandle << 7 = index * 0x80 into the 0x80-stride VB table | [V] |
| VB record m_gpuVA | VB rec +0x58 | 8 | 0xe82ccbe | `0xe82ccbe  add rcx,[r15+0x9B21D0]` | BufferLocation = [rendererObj+0x9B2178+vb*0x80 + 0x58] (= VB record m_gpuVA) + header+0x50 | [V] |
| header VB byte offset | header +0x50 | 4 | 0xe82ccbb | `0xe82ccbb  mov ecx,[rdx+0x50]` | header+0x50 = VB byte offset added to the buffer base | [V] |
| VBV StrideInBytes | VBV +0x0C | 2 | 0xe82cccc | `0xe82cccc  movzx ecx,word ptr [rdx+0x58]` | StrideInBytes = header+0x58 (u16 vertex stride) stored at VBV+0x0C | [V] |
| VBV SizeInBytes | VBV +0x08 | 4 | 0xe82ccd8 | `0xe82ccd8  imul ecx,[rdx+0x54]` | SizeInBytes = header+0x58 (stride) * header+0x54 (count), stored at VBV+0x08 | [V] |
| IB table base offset from rendererObj | IB table +0x93A178 | 8 | 0xe82caeb | `0xe82caeb  add rcx,0x93A178` | index-buffer record at rendererObj+0x93A178 + scaled ibHandle; stride 0x78 per entry [BGFX_MAP 1519 slot 11/18 destroyIndexBuffer `imul 0x78; add 0x93a178`] | [V] |
| IB record m_gpuVA | IB rec +0x58 | 8 | 0xe82cb4e | `0xe82cb4e  mov r8,[rcx+0x58]` | IBV.BufferLocation (+0x50) = [IB record+0x58] m_gpuVA | [V] |
| IB record size | IB rec +0x60 | 4 | 0xe82cb57 | `0xe82cb57  mov ecx,[rcx+0x60]` | IBV.SizeInBytes (+0x58) = [IB record+0x60] buffer size | [V] |
| IBV Format | IBV +0x5C | 4 | 0xe82cb5e | `0xe82cb5e  cmp dword ptr [r12+0x48],2` / `0xe82cb6f  cmove ecx,r8d` | Format (+0x5C) = 0x39 R16_UINT when header+0x48 indexStride==2, else 0x2A R32_UINT (0xe82cb64/0xe82cb69) | [V] |
| vb handle load | header +0x76 | 2 | 0xe82cb9b | `0xe82cb9b  movzx ecx,word ptr [rax+0x76]` | vbHandle (0xFFFF = none) read from draw header+0x76 before the <<7 table index | [V] |

Resulting view construction (mirrors the executor verbatim):
- VBV = { BufferLocation = [rendererObj+0x9B2178 + vb*0x80 + 0x58] + vbByteOffset, SizeInBytes = vbStride * vbCount, StrideInBytes = vbStride }  [V 0xe82ccbe  0xe82ccd8  0xe82ccd0]
- IBV = { BufferLocation = [rendererObj+0x93A178 + ib*0x78 + 0x58], SizeInBytes = [rendererObj+0x93A178 + ib*0x78 + 0x60], Format = indexStride==2 ? 0x39 : 0x2A }  [V 0xe82cb4e  0xe82cb57  0xe82cb5e]

## (2) programPipeline context / executorState / state from CustomItemCtx [V]

The executor's custom-item path (0xe822400) builds the 0x18-byte CustomItemCtx at executorState+0x3B0 and invokes fn(user, &ctx). Everything programPipeline needs is therefore recoverable from ctx alone — no plumbing at a wiring site.

| row | offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| ctx build site | CustomItemCtx at exeState+0x3B0 | - | 0xe822448 | `0xe822448  mov [rbx+0x3B0],r8` | ctx+0x00 = fnPtr stored at executorState+0x3B0 (rbx = executorState) | [V] |
| ctx+0x08 job field | ctx +0x08 | 8 | 0xe82244f | `0xe82244f  mov [rbx+0x3B8],rsi` | ctx+0x08 = rsi = [executorState+0xB0], the job field (reloaded each loop iteration at 0xe822130/0xe822474) | [V] |
| ctx+0x10 commandList | ctx +0x10 | 8 | 0xe822456 | `0xe822456  mov [rbx+0x3C0],rcx` | ctx+0x10 = [[executorState+0x90]+0x30] = live ID3D12GraphicsCommandList* | [V] |
| fn invocation | fn(user, &ctx) | - | 0xe822461 | `0xe822461  lea rdx,[rbx+0x3B0]` then `0xe822468  call qword ptr [0xF99FFA0]` | &ctx = executorState+0x3B0; fn called with rcx = [header+8] (user), rdx = &ctx via CFG thunk | [V] |
| executorState derivation | exeState = ctx - 0x3B0 | - | 0xe822461 | `0xe822461  lea rdx,[rbx+0x3B0]` | ctx is built at executorState+0x3B0, so executorState = ctx - 0x3B0 [V] | [V] |
| state word | state [exeState+0x1F0] | 8 | 0xe8223bf | `0xe8223bf  mov [rbx+0x1F0],r12` | executor stores the draw state u64 at executorState+0x1F0; passNativeFn reads [ctx-0x3B0+0x1F0] ([V] offset, [I] meaning for a custom item with no header) | [V] |
| program table base | program table [exeState+0x5E0] | 8 | 0xe82249a | `0xe82249a  mov rcx,[rbx+0x5E0]` | program table = [executorState+0x5E0], stride 0xF8 per record (0xe822493 `imul rax,0xF8`) | [V] |
| program object / signature | program object +0xA8 | 4 | 0xe8224ac | `0xe8224ac  mov rax,[rcx+rax]` then `0xe8224b0  mov esi,[rax+0xA8]` | program object = [program record], variant signature u32 = [program object+0xA8] | [V] |
| PSO cache block | block [exeState+0xA0] | 8 | 0xe8224b6 | `0xe8224b6  mov rcx,[rbx+0xA0]` | PSO block = [executorState+0xA0]; bucket table [block+0x48, block+0x50) (0xe8224bd/0xe8224c1) | [V] |
| SetPipelineState bind | cmdlist vtbl +0xC8 | - | 0xe822a78 | `0xe822a78  call qword ptr [0xF99FFA0]` | command-list vtable slot +0xC8 = SetPipelineState, called via CFG thunk [0xF99FFA0] (0xe822a7f stores the PSO at [rbx+0x1A0]) | [V] |

programPipeline(ctx, program, state) therefore uses: context = ctx (executorState = ctx - 0x3B0), program table = [exeState+0x5E0], signature = [programObject+0xA8], PSO key = state & 0x0707007FFFFFF0FF, block = [exeState+0xA0], all [V] verbatim.

## (3) PassNative.h — resolved vbv/ibv (no zero placeholders)

Replaced the zero-initialized vbv/ibv in passNativeFn with views resolved from the vb/ib handles through the verified tables above:
- vbv.BufferLocation = [rendererObj+0x9B2178 + vb*0x80 + 0x58] (+ vb byte offset), vbv.SizeInBytes = vbStride*vbCount, vbv.StrideInBytes = vbStride [V section (1)]
- ibv.BufferLocation = [rendererObj+0x93A178 + ib*0x78 + 0x58], ibv.SizeInBytes = [rendererObj+0x93A178 + ib*0x78 + 0x60], ibv.Format = indexStride==2 ? DXGI_FORMAT_R16_UINT (0x39) : DXGI_FORMAT_R32_UINT (0x2A) [V section (1)]
- programPipeline(ctx, pass->program, state) with state = [ctx-0x3B0+0x1F0] [V section (2)]
- list->SetPipelineState(pso) [V 0xe822a78], then DrawIndexedInstanced(pass->numIndices, 1, pass->startIndex, 0, 0).

No nullptr arguments remain; no zero placeholders. Static-only verification (no build): `python tools/delegate.py check docs/progress/oc_U-EQ5c.md` exits 0.
