## NEXT
DONE

# U-EG4a — G4a "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Scope: ONLY the pending part of the item line — texture/atlas management at the D3D12 backend. This unit decodes the createTexture slot (26) entry, the shared texture record-table lookup, and the TextureD3D12::create (0xe81bf30) body that fills the record fields. The sampler flag decode + sampler cache half is already closed on disk (docs/functions/e820500.md, BGFX_MAP 6ax) and is NOT redone here.

All `0xRVA  instr` lines are verbatim from rdis disassembly of C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (image-relative RVAs). Sizes come from the instruction (qword 8, dword/movss 4, word 2, byte 1). Meaning is written only where an instruction or string shows it, else '-'. Tags: [V] = seen in disassembly/string, [I] = inferred from instruction context, [?] = unknown/not proven.

## Table — texture record creation & lookup (createTexture slot 26 + TextureD3D12::create 0xe81bf30)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| texture record table base | 8 | rcx+0xBDE178 | `0xe8143f3  lea r12,[rcx+0xBDE178]` | inline table of 4096 records, stride 0xB8, ends 0xC5A178; site: createTexture 0xe8143f3 | [V] meaning [I 6z] |
| record stride | 4 | - | `0xe814ac3  imul r9,r15,0xB8` | record stride = dword immediate 0xB8; sites: createTexture 0xe814ac3, update/destroy/resize/override per input | [V] |
| overflow-page guard flag | 1 | rdi+0xC96190 | `0xe814410  cmp byte ptr [rdi+0xC96190],0` | guard enabled for handles >= 0x1000; sites: createTexture 0xe814410, update/destroy/resize/create | [V] meaning [I 6z] |
| page-list anchor (detached handles >=0x1000) | 8 | r14+0xC96178 | `0xe814ae7  mov rax,[r14+0xC96178]` | chained page-array anchor (+0xB8000 per page); sites: createTexture 0xe814ae7, update/destroy/resize/override | [V] |
| record-table bounds/guard check | - | 0xE83ABB0 | `0xe814403  call 0xE83ABB0` | bounds/guard check before lookup; sites: createTexture 0xe814403, update/destroy/resize/override/create | [V] |
| guard-violation error string | - | 0xF7F68E3 | `0xe814abe  call 0xBC5F110` | string 0xF7F68E3 "FAILED: accessing a guarded paged heap backed array out of b..." (preceded by `0xe814ab5  lea rdx,[0xF7F68E3]`) | [V] |
| record flags | 4 | rdi+0x98 | `0xe81bfdc  mov [rdi+0x98],esi` | low-32 flags from parsed bimg chunk | [V] |
| record width | 4 | rdi+0x9C | `0xe81bfe5  mov [rdi+0x9C],edx` | width | [V] |
| record height | 4 | rdi+0xA0 | `0xe81bfef  mov [rdi+0xA0],r8d` | height | [V] |
| record depth | 4 | rdi+0xA4 | `0xe81bffb  mov [rdi+0xA4],eax` | depth | [V] |
| record numLayers | 4 | rdi+0xA8 | `0xe81c004  mov [rdi+0xA8],ecx` | array layers | [V] |
| record type | 1 | rdi+0xAE | `0xe81c0a2  mov byte ptr [rdi+0xAE],2` | type: 0=2D,1=3D,2=cube (sites 0xe81c0a2=2, 0xe81c0b9=1, 0xe81c0c6=0) | [V] |
| record requested format | 1 | rdi+0xAF | `0xe81c00f  mov [rdi+0xAF],sil` | requested format byte | [V] |
| record actual format | 1 | rdi+0xB0 | `0xe81c077  mov [rdi+0xB0],r13b` | actual format (0x42 fallback when caps lack the type) | [V] |
| record numMips | 1 | rdi+0xB1 | `0xe81c0d1  mov [rdi+0xB1],dl` | numMips - skip | [V] |
| create notification entry store qword | 8 | rax+0x00 | `0xe814612  mov [rax],rcx` | entry = {id, id<<32} | [V] |
| create notification entry seen flag | 1 | rax+0x08 | `0xe81460e  mov byte ptr [rax+8],1` | entry "seen" flag; pre-existing path calls 0xe81464d `call 0xE83B0E0` | [V] meaning [?] |
| current command-list wrapper | 8 | rdi+0x19F58 | `0xe814652  mov rcx,[rdi+0x19F58]` | this+0x19F58 = open command-list wrapper | [V] |
| command-list object | 8 | rcx+0x30 | `0xe814659  mov rdx,[rcx+0x30]` | wrapper+0x30 command-list object | [V] |
| state-tracker block base | 8 | rcx+0x14458 | `0xe81465d  add rcx,0x14458` | state-tracker block at wrapper+0x14458 | [V] |
| post-create state-tracker call | - | 0xE82D960 | `0xe81466a  call 0xE82D960` | state write shared with updateTexture; sites: createTexture 0xe81466a, updateTexture | [V] |

## Texture record field summary (6hz cross-read)

The TextureD3D12::create body (0xe81bf30, called by createTexture at 0xe81455b and by resizeTexture at 0xe815b2a) writes the record fields above (+0x98 flags, +0x9C width, +0xA0 height, +0xA4 depth, +0xA8 numLayers, +0xAE type, +0xAF requested format, +0xB0 actual format, +0xB1 numMips) and the resource/SRV/UAV view block (+0x00..+0x90) seen live-verified at 6im (+0x00 ID3D12Resource*, +0x08..+0x40 D3D12_RESOURCE_DESC, +0x40..+0x68 SRV desc, +0x68..+0x90 UAV desc). The record handle lookup walks inline table this+0xBDE178 for handles <0x1000 and the chained overflow pages anchored at this+0xC96178 for handles >=0x1000 (4096 records = 0xB8000 bytes per page, next-page pointer after them), guarded by byte this+0xC96190.

## CLOSES?

NO — the D3D12 texture-management chain is [V]-proven by the rows above: createTexture slot 26 entry, the shared record-table lookup (this+0xBDE178 stride 0xB8, guard flag this+0xC96190, page anchor this+0xC96178, bounds check 0xE83ABB0), the TextureD3D12::create record-field writes (+0x98..+0xB1), and the post-create state-tracker call 0xE82D960. But the pending part "texture/atlas management" is not fully closed: the atlas texture-creation stitcher — the Minecraft-side code that builds the TerrainAtlas/ItemAtlas texture description and calls createTexture/resizeTexture with atlas parameters — is not located in this input or in the executable (no createTexture 0xe8143c0 / resizeTexture 0xe815840 call tied to either atlas; static analysis exhausted; tracked by L8a/L8b and needs live capture). Single blocking fact: atlas texture-creation stitcher not located.
