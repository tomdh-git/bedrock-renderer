# UNIT U-EN1d — N1d PSO builder (replacement route / equivalent key)

## NEXT
DONE

GOAL: Close checklist item N1d: "PSO builder 0xe81dc60: replacement draws route through it or rebuild equivalent key — BGFX_MAP 8c; B4" (docs/RENDER_CHECKLIST.md line 482, [ ] open).

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base. Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

VERSION NOTE (read first): 0xe81dc60 on the item line is the **1.26.60.05 RVA** of the PSO builder. In 1.26.62.01 the builder moved +0xC00 to **0xe81e860** (size 0x1c9a) [BGFX_MAP 6cw/6ct, docs/data/function_anchors.tsv, Sigs.json D3D12Context::psoBuilder, port_check_render_sigs.tsv]. 0xe81dc60 in 62.01 is mid-function inside 0xe81da20, NOT a function entry. All proof below is for 0xe81e860 in 62.01.

Existing on disk (read in full, treated as hypothesis to re-verify verbatim against the exe):
- docs/functions/e81e860.md (D2 dossier, end-to-end transcription of the builder)
- docs/BGFX_MAP.md 6ct (state-word bit map), 6cu (enum tables), 6fr/6fs/6ft (key, desc build, cache insert)
- docs/data/function_anchors.tsv, docs/data/functions.tsv, docs/data/layout_asserts.json (D3D12Context::psoBuilder asserts), src/sdk/Sigs.json (psoBuilder sig)

Method: every instruction line below was taken from `rdis.exe <exe> dis 0x<RVA> <n>` on the 1.26.62.01 exe and copied verbatim (two spaces after the address). The file is checked with `python tools/sigs/verify_oc.py` before closing.

## (1) PSO builder location in 1.26.62.01 (item line's 0xe81dc60 is the stale 1.26.60.05 RVA)

| name | rva or offset | size | address (read/store site) | `0xRVA  instr` | meaning | tag |
| PSO builder entry | 0xE81E860 | 8 | – | `0xE81E860  push r15` | function entry prologue (full frame `sub rsp,0x768` follows at 0xE81E86C) | [V] |
| PSO builder end | 0xE8204D4 | – | – | `0xE8204D4  ret` | success-path return; extent 0xE81E860..0xE820500 = 0x1CA0 bytes, int3 padding 0xE8204F9..0xE8204FE, next function at 0xE820500 | [V] |
| stale RVA check | 0xE81DC60 | 1 | – | `0xE81DC60  nop` | 0xe81dc60 lies inside function 0xe81da20 (next real instruction `0xE81DC61  lea rcx,[rsi+0xAF8]`; calls destructor helper 0xe80ef60 at 0xE81DC68) — not a function entry in 62.01 | [V] |

## (2) PSO key and pipeline build — verbatim proof (BGFX_MAP 6ct/6fs/6ft, current map sections for the item's "BGFX_MAP 8c")

| name | rva or offset | size | address (read/store site) | `0xRVA  instr` | meaning | tag |
| key mask 1 constant | 0xE81E8EC | 8 | – | `0xE81E8EC  mov rsi,0x707007FFFFFF0FF` | first PSO key mask | [V] |
| key mask 1 applied | 0xE81E8F6 | 8 | reg r13 = state argument S | `0xE81E8F6  and rsi,r13` | key.S = S & 0x0707007FFFFFF0FF (keeps bits 0-7, 12-38, 48-50, 56-58 of the state word) [I bit map per 6ct] | [V] |
| key mask 2 constant | 0xE81E8F9 | 8 | – | `0xE81E8F9  mov r14,0xFFFFFF00FFFFFF00` | second PSO key mask | [V] |
| key mask 2 applied | 0xE81E908 | 8 | reg r9 = state2 (stencil) argument | `0xE81E908  and r14,r9` | key.stencil = state2 & 0xFFFFFF00FFFFFF00 (stencil ref/mask low bytes removed — dynamic state) | [V] |
| program table base | 0xE81E8E5 | 8 (qword) | renderer+0xB62178 | `0xE81E8D7  imul rax,0xF8` / `0xE81E8E1  lea rbx,[rdx+rax]` / `0xE81E8E5  add rbx,0xB62178` | program record at renderer+0xB62178 + progIndex*0xF8, stride 0xF8 | [V] |
| program record fetch | 0xE81E934 | 8 (qword) | program record +0x00 | `0xE81E934  mov rax,[rbx]` | program object pointer from record +0x00 | [V] |
| root signature field | 0xE81F00C | 8 (qword) | renderer+0x1248 | `0xE81F00C  mov rax,[r12+0x1248]` | desc.pRootSignature = renderer->m_rootSignature | [V] |
| Murmur2A mix | 0xE81EA1F | – | – | `0xE81EA1F  call 0xBC76610` | bx::HashMurmur2A::add, used 15 times over the 13 key inputs (shader hashes, attribute masks, layouts, draw params, framebuffer, instance count, sample desc) | [V] |
| TEXCOORD semantic | 0xE81FDC5 | – | – | `0xE81FDC5  lea r15,[0xF7CCFBB]` | rdata string "TEXCOORD" at 0xF7CCFBB — input-layout semantic used for instance-data elements | [V] |
| device pointer | 0xE8203AF | 8 (qword) | renderer+0x400 | `0xE8203AF  mov rcx,[rdi+0x400]` | ID3D12Device* from renderer object | [V] |
| device vtable slot 10 | 0xE8203B9 | 8 (qword) | device vtable +0x50 | `0xE8203B9  mov rax,[rax+0x50]` | ID3D12Device vtable slot 10 (0x50/8) = CreateGraphicsPipelineState | [V] |
| CreateGraphicsPipelineState call | 0xE8203D1 | – | – | `0xE8203D1  call qword ptr [0xF99FFA0]` | desc at [rsp+0x3C8], IID data at 0xF4EDD64, out pipeline at [rsp+0x68]; HRESULT tested with `0xE8203D7  test eax,eax` | [V] |
| device-lost state store | 0xE82043F | 4 (dword) | renderer+0x19F88 | `0xE82043F  mov [rdi+0x19F88],ecx` | on PSO create failure: renderer device state set (>= 5 guard checked at `0xE8203DB  cmp dword ptr [rdi+0x19F88],5`) | [V] |
| device-lost HR store | 0xE820445 | 4 (dword) | renderer+0x19F8C | `0xE820445  mov [rdi+0x19F8C],eax` | device-lost HRESULT stored | [V] |
| PSO cache erase | 0xE820464 | – | – | `0xE820464  call 0xE83BBF0` | erase existing cache entry by hash before re-insert | [V] |
| PSO cache emplace | 0xE82048C | – | – | `0xE82048C  call 0xE83BDD0` | emplace {pso, vsh attribute-mask copy} keyed by the Murmur2A hash | [V] |
| texture overflow page chain | 0xE820368 | 8 (qword) | page+0xB8000 | `0xE820368  mov rcx,[rax+0xB8000]` | texture handles >= 4096 walk chained overflow pages via next-page pointer at page+0xB8000 | [V] |
| texture format byte | 0xE820380 | 1 (byte) | texture record +0xB0 | `0xE820380  movzx eax,byte ptr [rsi+0xB0]` | texture actual format at record +0xB0 (format-key hashing for render targets) | [V] |
| attribute mask fixup | 0xE81E9AA | 4 (dword) | shader record +0xA0 | `0xE81E9AA  and ecx,[rax+0xA0]` | vertex shader attribute mask word fixup (mask array at shader record +0x80, 19 entries per dossier) | [V] |
| attribute mask fixup 2 | 0xE81E9D5 | 2 (word) | shader record +0xA4 | `0xE81E9D5  and cx,[rax+0xA4]` | word fixup at shader record +0xA4 | [V] |

## (3) Who calls the builder — replacement draws route through it (both callers in 62.01)

| name | rva or offset | size | address (read/store site) | `0xRVA  instr` | meaning | tag |
| caller: blit submit form | 0xE818D2D | – | – | `0xE818D2D  call 0xE81E860` | 0xe818bc0 (blit/custom submit form) calls the builder with rcx=r14, rdx=r15, r8d=0x8F, r9d=0; returned PSO bound through `0xE818D4F  call qword ptr [0xF99FFA0]` (device vtable +0xC8 = SetPipelineState) and `0xE818D6A  call qword ptr [0xF99FFA0]` (+0xF0 = SetGraphicsRootSignature, root sig from [r14+0x1248]) | [V] |
| caller: draw executor | 0xE822D3F | – | – | `0xE822D3F  call 0xE81E860` | executor 0xe821120 per-draw call: rcx = [rbx+0xA0] (PsoCache*), stack args {dword, float, float, byte, layouts ptr, u16 program, byte, u16 frameBuffer, passKey ptr}; result stored `0xE822D44  mov [rbx+0x580],rax` (ID3D12PipelineState* for the draw) | [V] |

## (4) What exists on disk for this item

- docs/progress/oc_U-EN1d.md — this unit (proof table above)
- docs/functions/e81e860.md — D2 dossier: full end-to-end transcription of the builder (key, desc build with input layout/topology/targets/sample desc, CreateGraphicsPipelineState, cache insert); status D2-partial per the dossier (attribute format table contents not dumped — outside this item's wording)
- docs/BGFX_MAP.md 6ct/6cu/6fr/6fs/6ft — state-word bit map, enum tables (compare 0xF4ECBD0, blend 0xF4ECC00/0xF4ECC70, cull 0xF4ECCB0, stencil op 0xF4ECC90), key and description build
- src/sdk/Sigs.json — `D3D12Context::psoBuilder` sig (unique match in 62.01 .text)
- docs/data/layout_asserts.json + src/sdk/mc/deps/bgfx/D3D12Context.h — kPsoBuilder = 0xE81E860 with asserts

## CLOSES?
CLOSES?: YES — every pending part of item N1d ("PSO builder: replacement draws route through it or rebuild equivalent key") is proven by [V] rows on disk now: the builder's 62.01 entry is 0xE81E860 (size 0x1CA0; the item's 0xe81dc60 is the stale 1.26.60.05 RVA and is mid-function of 0xe81da20 here, not an entry), the key recipe is S & 0x0707007FFFFFF0FF / state2 & 0xFFFFFF00FFFFFF00 hashed with Murmur2A over the 13 inputs, the builder is called per-draw by the executor at 0xE822D3F (PSO returned in rax, stored to [rbx+0x580]) and by the blit form at 0xE818D2D, and on a cache miss it builds the D3D12_GRAPHICS_PIPELINE_STATE_DESC and creates it via device vtable slot 10 (CreateGraphicsPipelineState) then inserts it into the PSO cache (0xe83bbf0 erase, 0xe83bdd0 emplace). A replacement can therefore route draws through 0xE81E860 or rebuild an equivalent key from these verified inputs. The item's "BGFX_MAP 8c" citation corresponds to the current-map sections 6ct/6fs/6ft (sections renumbered; content present and verified).
