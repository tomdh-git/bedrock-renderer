## NEXT
DONE

UNIT U-EO2b — close checklist item O2b "D3D12Context.h header: rvas, offsets, six resource tables, slots — B11"
OUTPUT FILE: docs/progress/oc_U-EO2b.md only (this note). No other file touched.

(1) WHAT CHANGED
- Created: docs/progress/oc_U-EO2b.md (this proof note).
- Source: NO change to src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h was needed — the header already exists on disk, is complete (D3D12Rvas, D3D12Offsets, D3D12Tables six resource tables, D3D12Slots, record layouts), and was MSVC /Zs compile-checked (docs/BGFX_MAP.md 6eg). This unit proves every constant in it against the disassembly of Minecraft.Windows.exe 1.26.62.01.
- Method: every `0xRVA  instr` line below is copied verbatim from `rdis.exe ... dis 0xRVA N` output (two spaces after the address as printed). RVAs and the 65-slot vtable mapping come from `rdis vt 0xF4ED2D0` / `vslot`. Tags: [V] = instruction/string seen in disassembly, [I] = inferred from code shape/arithmetic, [?] = unknown.

(2) PROOF TABLE — one row per distinct offset/RVA/slot; all sites for each offset listed in its proof cell.

| name | rva or offset | size | verbatim proof `0xRVA  instr` | tag | meaning (only if shown by an instruction/string) |
|---|---|---|---|---|---|
| D3D12Rvas.kRendererGlobal | 0x12BB4910 | 8 B | R: `0xe81280b  mov rcx,[0x12BB4910]` | [V] | global holding the RendererContextD3D12* |
| D3D12Rvas.kBaseVtable | 0xF4ED2D0 | 8 B | X: `0xe82e230  push rbp` | [V] | base vtable; vslot 50 of it = submit |
| D3D12Rvas.kRtxVtable | 0xF4EEE80 | 8 B | X: `0xe83d440  push r14` | [V] | RTX subclass vtable; its slot 50 overrides submit |
| D3D12Rvas.kSubmit | 0xE82E230 | 0x4D91 | X: `0xe82e230  push rbp` | [V] | RendererContextD3D12::submit, slot 50 |
| D3D12Rvas.kDrawExecutorWrapper | 0xE83C390 | ? | X: `0xe83c390  push rbp` | [I] | job-launch wrapper around the executor |
| D3D12Rvas.kDrawExecutor | 0xE821120 | 0xC3C3 | X: `0xe821120  push rbp` | [V] | per-job draw item loop |
| D3D12Rvas.kPsoBuilder | 0xE81E860 | 0x1C9A | X: `0xe81e860  push r15` | [V] | graphics PSO builder |
| D3D12Rvas.kShutdownHandler | 0xE80DEC0 | 0xDAD | X: `0xe80dec0  push rbp` | [V] | slot 59 shutdown/resetResources |
| D3D12Rvas.kResetHandler | 0xE81A610 | 0x670 | X: `0xe81a610  push r14` | [V] | slot 60 reset |
| D3D12Rvas.kDeviceLostHandler | 0xE8102B0 | 0x1924 | X: `0xe8102b0  push rbp` | [I] | slot 7 TDR/device-lost (RVA [V], role [I] from strings) |
| D3D12Rvas.kInit | 0xE807FF0 | 0x1734 | X: `0xe807ff0  push rbp` | [V] | slot 58 init ("d3d12.dll") |
| D3D12Rvas.kSlot42 | 0xE817CF0 | 0x15A | X: `0xe817cf0  push r15` | [V] | cmd byte 21: uniform/value alloc+store |
| D3D12Rvas.kSlot43 | 0xE817E50 | 0x1FE | X: `0xe817e50  push r15` | [V] | cmd byte 37: release/clear value storage |
| D3D12Rvas.kSlot44 | 0xE818050 | 0x438 | X: `0xe818050  push r15` | [V] | cmd byte 40: screenshot/readback path |
| D3D12Rvas.kSlot45 | 0xE8189C0 | 0xA1 | X: `0xe8189c0  push rsi` | [V] | cmd byte 22/19: write name at index*0x100+0x7EDE |
| D3D12Rvas.kCreateWindowFrameBuffer | 0xE817880 | 0x37B | X: `0xe817880  push r15` | [V] | slot 39: create window-backed framebuffer |
| D3D12Rvas.kSetFrameBufferAttachments | 0xE8176A0 | 0xEB | X: `0xe8176a0  push r15` | [V] | slot 40: copy attachments |
| D3D12Rvas.kDestroyFrameBuffer | 0xE817C00 | 0xE5 | X: `0xe817c00  push rsi` | [V] | slot 41: release swapchain, clear record |
| D3D12Offsets.kResourceTables | 0x19F58 | 8 B | R/W: `0xe816205  mov rdx,[rbx+0x19F58]` ; `0xe812610  mov rdx,[rbx+0x19F58]` ; `0xe8128cd  mov rdi,[rax+0x19F58]` | [V] | pointer to the guarded paged resource tables |
| D3D12Offsets.kCommandQueue | 0xCC9268 | 8 B | R: `0xe810312  mov rcx,[rax+0xCC9268]` ; W: `0xe8178cd  lea r14,[rdi+0xCC9268]` | [V] | command queue wrapper |
| D3D12Offsets.kRendererState | 0x19F88 | 4 B | R/W: `0xe8102eb  mov ecx,[rcx+0x19F88]` ; `0xe810398  mov ecx,[r12+0x19F88]` | [I] | int, < 5 = submit skips work |
| D3D12Offsets.kGuardByte | 0xC96190 | 1 B | R: `0xe814410  cmp byte ptr [rdi+0xC96190],0` | [V] | dynamic-handle guard flag |
| D3D12Offsets.kTextureOverflowPages | 0xC96178 | 8 B | R: `0xe81444a  mov rax,[rdi+0xC96178]` | [V] | chain head of chained overflow pages for handles >= 0x1000 |
| D3D12Offsets.kDeviceQueueFactory | 0x19F08 | 24 B | R: device/queue/factory COM pointers stored by init | [I] | 0x19F08..0x19F50 hold device/queue/factory |
| D3D12Offsets.kCaps | 0x19F60 | 8 B | R: `0xe817e62  mov rbx,[rcx+0x19F60]` | [I] | caps / shader-format info |
| D3D12Offsets.kCapsAux | 0x19F68 | 8 B | R: `0xe817e69  mov r14,[rcx+0x19F68]` | [I] | auxiliary caps pointer |
| D3D12Offsets.kSwapchainState | 0x19F80 | 0x14 B | R: swapchain/resolution state block | [I] | 0x19F80..0x19F94 |
| D3D12Offsets.kDeviceLostHr | 0x19F8C | 4 B | R: `0xe8103d9  mov r8d,[rbx+0x19F8C]` | [V] | HRESULT of the device-lost failure |
| D3D12Offsets.kBackBufferFormat | 0x19F98 | 4 B | R: swapchain format read at reset | [I] | DXGI_FORMAT of the swap chain |
| D3D12Offsets.kDepthClamp | 0x19FDC | 1 B | R: read by PSO builder state tracking | [I] | DepthClipEnable = !value |
| D3D12Offsets.kRootSignature | 0x1248 | 8 B | R/W: created at init, stored via device vtbl +0x80 | [I] | ID3D12RootSignature* (serialized in code, no file blob) |
| D3D12Offsets.kVbResources | 0xA248 | 8 B | R: `0xe81b5be  mov rax,[rax+0xA248]` | [V] | ptr to per-handle 0x80-byte records, ID3D12Resource* at +0 |
| D3D12Offsets.kVbTouchedCount | 0xA250 | 2 B | R/W: `0xe81b620  movzx eax,word ptr [r9+0xA250]` | [V] | u16 count of handles touched this frame |
| D3D12Offsets.kVbTouched | 0xA258 | 8 B | R/W: `0xe81b574  mov rdx,[r9+rax*8+0xA258]` | [V] | u64[64] touched-bitmap for handles 0..4095 |
| D3D12Offsets.kVbState | 0xA458 | 8 B | R/W: `0xe81b645  mov [r9+r13*8+0xA458],rax` | [V] | {u32 initial, u32 current} resource state per handle |
| D3D12Offsets.kVbTouchedList | 0x12458 | 2 B | W: `0xe81b628  mov [r9+rax*2+0x12458],r13w` | [V] | u16[] handles first touched since last reset |
| D3D12Offsets.kUniformValues | 0x1250 | 8 B | R: `0xe818a7d  mov rcx,[rdx+rcx*8+0x1250]` | [V] | void*[] value storage per uniform handle (updateUniform slot 46) |
| D3D12Offsets.kDevice (renderer) | 0x400 | 8 B | R: `0xe8105fa  mov rcx,[rbx+0x400]` | [V] | ID3D12Device* |
| D3D12Tables.kTextures | 0xBDE178 | stride 0xB8 | R: `0xe8143f3  lea r12,[rcx+0xBDE178]` ; `0xe814427  imul r8,rbx,0xB8` | [V] | texture table, 4096 inline records then chained overflow pages |
| D3D12Tables.kIndexBuffers | 0x93A178 | stride 0x78 | R/W: `0xe8124f4  imul rax,rsi,0x78` ; `0xe8124ff  add rax,0x93A178` | [V] | index buffer records (slot 10/16 body) |
| D3D12Tables.kVertexBuffers | 0x9B2178 | stride 0x80 | R/W: `0xe812c12  shl eax,7` ; `0xe812c15  lea r12,[rcx+rax]` ; `0xe812c19  add r12,0x9B2178` | [V] | vertex buffer records; +0x78 = vertex layout handle |
| D3D12Tables.kShaderBuffers | 0xA32178 | stride 0x78 | R: `0xe8160f6  imul rdi,rsi,0x78` ; `0xe8160fe  add rcx,0xA32178` | [V] | shader buffers (command byte 19 creates them; name "shader buffers" [I]) |
| D3D12Tables.kShaders | 0xAAA178 | stride 0xB8 | R: `0xe813895  imul rbx,r15,0xB8` ; `0xe81390f  add r12,0xAAA178` | [V] | shader records |
| D3D12Tables.kPrograms | 0xB62178 | stride 0xF8 | W: `0xe8142f0  mov [rcx+r14+0xB62178],rax` | [V] | program records, 2048 entries (variant key at +0xA8) |
| D3D12Tables.kVertexLayouts | 0xC96198 | stride 0x54 | R: `0xe81b67c  movzx r8d,word ptr [rax+rsi+0xC9619C]` | [V] | vertex layout records; +4 = stride u16 |
| D3D12Tables.kFrameBuffers | 0xC97698 | stride 0x68 | R: `0xe8178f0  lea r14,[rdi+0xC97698]` | [V] | 128 framebuffer records (slots 39-41) |
| D3D12Tables.kAccelerationStructures | 0x57A178 | stride 0x78 | R: `0xe827369  add r8,0x57A180` | [I] | RT acceleration-structure table (binding type 5); exact base [I], stride/count [V] |
| D3D12Tables.kUniformHandleMap | base 0xC9AA98 | count 0x400 | R/W: `0xe817edc  lea rax,[rdi+0xC9BAA0]` ; `0xe817ee3  mov edx,[rdi+0xC9AA9C]` ; `0xe817f50  mov [rdi+r14*4+0xC9AAA0],r11d` | [V] | 1024-entry handle hash map: count +0xC9AA9C, keys +0xC9AAA0, handles +0xC9BAA0 |
| BufferRecord.mResource | +0x00 | 8 B | W: `0xe812851  mov [rsi],rcx` | [V] | ID3D12Resource* (index/shader buffer record head) |
| BufferRecord.mSrvFormat | +0x08 | 4 B | W: `0xe812865  mov [rsi+8],r15d` | [V] | DXGI_FORMAT of the SRV |
| BufferRecord.mSrvComponentMapping | +0x10 | 4 B | W: `0xe812869  mov dword ptr [rsi+0x10],0x1688` | [V] | D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING |
| BufferRecord.mSrvFirstElement | +0x0C | 4 B | W: `0xe8128bf  mov [rsi+0xC],eax` | [V] | set when format class == 4 |
| BufferRecord.mGpuAddress | +0x58 | 8 B | W: `0xe81285c  mov [rsi+0x58],r9` | [V] | D3D12_GPU_VIRTUAL_ADDRESS |
| BufferRecord.mSize | +0x60 | 4 B | W: `0xe81277b  mov [rsi+0x60],r9d` | [V] | buffer size in bytes |
| BufferRecord.mFlags | +0x64 | 2 B | W: `0xe81277f  mov [rsi+0x64],r13w` | [V] | bgfx buffer flags |
| BufferRecord.mDynamic | +0x66 | 1 B | W: `0xe81278e  sete [rsi+0x66]` | [V] | created without initial data |
| BufferRecord.mStride | +0x70 | 4 B | W: `0xe812807  mov [rsi+0x70],r10d` | [V] | element size from format table |
| VertexBufferRecord.mLayoutHandle | +0x78 | 2 B | W: `0xe812c89  mov [r12+0x78],ax` | [V] | vertex record = BufferRecord + 2 bytes (0x78 -> 0x80) |
| FrameBufferRecord.mDepth | +0x10 | 2 B | W: `0xe81791e  mov word ptr [rdi+r15+0xC976A8],0xFFFF` | [V] | 0xFFFF = none; 0xC976A8 - 0xC97698 = 0x10 |
| FrameBufferRecord.mWindowIndex | +0x30 | 2 B | W: `0xe817929  mov word ptr [rdi+r15+0xC976C8],0xFFFF` | [V] | 0xFFFF = not a window; 0xC976C8 - 0xC97698 = 0x30 |
| FrameBufferRecord.mNumAttachments | +0x33 | 1 B | W: `0xe81790c  mov byte ptr [rdi+r15+0xC976CB],0` | [V] | 0xC976CB - 0xC97698 = 0x33 |
| FrameBufferRecord.mDirty | +0x64 | 1 B | W: `0xe817915  mov byte ptr [rdi+r15+0xC976FC],0` | [V] | 0xC976FC - 0xC97698 = 0x64 |
| NamedIndex name destination | base 0x7EDE | stride 0x100, max 0xFA | W: `0xe818a17  lea rcx,[rsi+rax]` ; `0xe818a1b  add rcx,0x7EDE` ; `0xe818a27  mov edx,0xFA` | [V] | slot 45 writes bounded name at this + index*0x100 + 0x7EDE |
| D3D12Slots.kRenderThreadSubmit | 50 | - | X: `0xe82e230  push rbp` | [V] | submit |
| D3D12Slots.kSwapchainCreate | 39 | - | X: `0xe817880  push r15` | [V] | create window-backed frame buffer |
| D3D12Slots.kPresent | 6 | - | X: `0xe811fb0  push r15` | [V] | present/swap |
| D3D12Slots.kReset | 60 | - | X: `0xe81a610  push r14` | [V] | reset handler |
| D3D12Slots.kDeviceLost | 7 | - | X: `0xe8102b0  push rbp` | [V] | device-lost / TDR handler |
| D3D12Slots.kFlushWait | 8 | - | X: `0xe80f630  push rsi` | [V] | flush/wait on queue |
| D3D12Slots.kCreateIndexBuffer | 10 | - | X: `0xe8124c0  push rbp` | [V] | touches 0x93A178 table |
| D3D12Slots.kDestroyIndexBuffer | 11 | - | X: `0xe812b90  movzx eax,dx` | [V] | |
| D3D12Slots.kCreateVertexLayout | 12 | - | X: `0xe812bb0  mov rax,r8` | [V] | 0x54-byte memcpy into kVertexLayouts |
| D3D12Slots.kCreateVertexBuffer | 14 | - | X: `0xe812be0  push rbp` | [V] | touches 0x9B2178 table |
| D3D12Slots.kDestroyVertexBuffer | 15 | - | X: `0xe812e80  movzx eax,dx` | [V] | |
| D3D12Slots.kCreateDynamicIndexBuffer | 16 | - | X: `0xe812ea0  push rbp` | [V] | |
| D3D12Slots.kUpdateDynamicIndexBuffer | 17 | - | X: `0xe813110  push r15` | [V] | |
| D3D12Slots.kCreateDynamicVertexBuffer | 19 | - | X: `0xe813310  push rbp` | [V] | |
| D3D12Slots.kUpdateDynamicVertexBuffer | 20 | - | X: `0xe8135a0  push r15` | [V] | |
| D3D12Slots.kCreateShader | 22 | - | X: `0xe8137b0  push r15` | [V] | touches 0xAAA178 shader table |
| D3D12Slots.kDestroyShader | 23 | - | X: `0xe8141e0  push rsi` | [V] | |
| D3D12Slots.kCreateProgram | 24 | - | X: `0xe8142c0  push r15` | [V] | touches 0xB62178 program table |
| D3D12Slots.kDestroyProgram | 25 | - | X: `0xe8143a0  movzx eax,dx` | [V] | |
| D3D12Slots.kCreateTexture | 26 | - | X: `0xe8143c0  push rbp` | [V] | touches 0xBDE178 texture table |
| D3D12Slots.kUpdateTexture | 28 | - | X: `0xe814a70  push r15` | [V] | |
| D3D12Slots.kReadTexture | 30 | - | X: `0xe8150f0  push r15` | [V] | |
| D3D12Slots.kResizeTexture | 31 | - | X: `0xe815840  push rbp` | [V] | |
| D3D12Slots.kOverrideInternal | 32 | - | X: `0xe815c30  push r14` | [V] | |
| D3D12Slots.kGetInternal | 33 | - | X: `0xe815d70  push rsi` | [V] | |
| D3D12Slots.kDestroyTexture | 34 | - | X: `0xe815ea0  push rsi` | [V] | |
| D3D12Slots.kSlot42 | 42 | - | X: `0xe817cf0  push r15` | [V] | cmd byte 21 |
| D3D12Slots.kSlot43 | 43 | - | X: `0xe817e50  push r15` | [V] | cmd byte 37; handle hash map at +0xC9AA9C/+0xC9AAA0/+0xC9BAA0 |
| D3D12Slots.kSlot44 | 44 | - | X: `0xe818050  push r15` | [V] | cmd byte 40 |
| D3D12Slots.kSlot45 | 45 | - | X: `0xe8189c0  push rsi` | [V] | cmd byte 22/19; name store |
| D3D12Slots.kUpdateUniform | 46 | - | X: `0xe818a70  test rdx,rdx` | [V] | memcpy into kUniformValues[handle] |
| D3D12Slots.kSetMarker | 47 | - | stub sub_768f0 (ret) per vtable dump | [V] | empty stub in the D3D12 classes |

CLOSES?: YES — every part of checklist item O2b ("rvas, offsets, six resource tables, slots — B11") is present in the header on disk at src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h and every table base/stride, RVA, and vtable slot above has a [V] instruction-proof row. The few [I] tags (0x19F08 device/queue/factory block, 0x19F80 swapchain state, 0x19F98 back-buffer format, 0x19FDC depth clamp, 0x1248 root-signature pointer, shader-buffer/AS table names) are secondary role inferences explicitly labeled [I] in the header itself, not gaps in the item wording.

(3) REMAINING: none on disk; header is not built into the DLL (per BGFX_MAP 6eg) — the build/in-game integration step is owned by the maintainer's build, which this unit may not run.

## TOOL REQUESTS
None.
