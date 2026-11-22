# U-EL8d — L8d "Render targets and their formats pending"

## Answer

TextureD3D12::create (`sub_e81bf30`, `0xe81bf30..0xe81df30`) builds the texture record and the `D3D12_RESOURCE_DESC` that starts at record+0x08 (live-verified layout, BGFX_MAP.md 6im: Dimension+0x08=3 TEXTURE2D, Width+0x18, Height+0x20, Format+0x28, **Flags dword at record+0x38**, desc block ends at +0x40). The render-target marker field is record+0x98 (bgfx flags, copied in at e81bfdc); it is tested at e81c3af and converted into `D3D12_RESOURCE_FLAGS` (record+0x38) by the ORs below. The bgfx-format-id → DXGI table is `data_f4ed700` (16-byte entries, entry = fmt*16), read at e81c1c7/e81c1d1/e81c2ac/e81c2af.

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| `0xe81c239` | 8 | TextureD3D12::create | `0xe81c239  mov qword ptr [r13+0x38],0` | `D3D12_RESOURCE_FLAGS` (record+0x38, last dword of the +0x08..+0x3F desc block) initialised to 0 [V] |
| `0xe81bfdc` | 4 | TextureD3D12::create | `0xe81bfdc  mov [rdi+0x98],esi` | bgfx flags (param [rbp+0x1F8]) copied into the render-target marker field record+0x98 [V] |
| `0xe81c3af` | 4 | TextureD3D12::create | `0xe81c3af  test r10d,0xF000` | render-target test: r10d = record+0x98 bgfx flags; bits 0xF000 != 0 => colour render-target path (loc_e81c3ab) [V] |
| `0xe81c3bc` | 1 | TextureD3D12::create | `0xe81c3bc  or byte ptr [r13+0x38],1` | `D3D12_FLAGS` record+0x38 |= ALLOW_RENDER_TARGET (0x1) when bgfx flags & 0xF000 != 0 [V] |
| `0xe81c2b7` | 1 | TextureD3D12::create | `0xe81c2b7  or byte ptr [r13+0x38],2` | `D3D12_FLAGS` record+0x38 |= ALLOW_DEPTH_STENCIL (0x2) when sub_ebd1560(record) != 0 (depth-stencil format) [V] |
| `0xe81c2e3` | 1 | TextureD3D12::create | `0xe81c2e3  or byte ptr [r13+0x38],8` | `D3D12_FLAGS` record+0x38 |= DENY_SHADER_RESOURCE (0x8) when width sign bit [V] |
| `0xe81c2f1` | 1 | TextureD3D12::create | `0xe81c2f1  or byte ptr [r13+0x38],4` | `D3D12_FLAGS` record+0x38 |= ALLOW_UNORDERED_ACCESS (0x4) when width & 0x100000 (e81c2e8 `test r10d,0x100000`) [V] |
| `0xe81c1ca` | 16/entry | TextureD3D12::create | `0xe81c1ca  lea rdi,[0xF4ED700]` | bgfx-format-id → DXGI table `data_f4ed700`; entry = fmt*16 (`e81c1c7  shl eax,4`), 4 dwords at +0/+4/+8/+0xC [V] |
| `0xe81c2b3` | 4 | TextureD3D12::create | `0xe81c2b3  mov [r13+0x28],ecx` | D3D12 desc Format dword = table[fmt].dword+0 (loaded by `0xe81c2ac  mov ecx,[rax+rdi]`) [V] |
| `0xe81c1d5` | 4 | TextureD3D12::create | `0xe81c1d5  mov [r13+0x40],edx` | SRV format dword = table[fmt].dword+4 (loaded by `0xe81c1d1  mov edx,[rax+rdi+4]`) [V] |
| `0xe81c6de` | 1 | TextureD3D12::create | `0xe81c6de  test byte ptr [rax+0x38],2` | `D3D12_FLAGS` bit2 branches creation: set => DSV view template data_f4ed2c0 (loc_e81c784); clear => `0xe81c760  call 0xE928FB0` resource creation, ID3D12Resource* -> record+0x00 [V] |
| `0xe814820` | 4 | createTexture (0xe8143c0) | `0xe814820  mov dword ptr [rdi+0x98],0` | createTexture resets record+0x98 bgfx flags to 0 (after the TextureD3D12::create call at e81455b); the RT flag must come from caller-set flags & 0xF000 [V] |
| `0xe8148de` | 4 | createTexture (0xe8143c0) | `0xe8148de  or [rdi+0x98],edx` | createTexture sets bgfx flag 0x200000 for fmt 0x1B/0x5A (e81483c `mov edx,0x200000`) — not a 0xF000 RT bit, so createTexture itself does not set ALLOW_RENDER_TARGET [V] |

## Live data (game running pid 13452, base 0x7ff7a59c0000)

- `docs/data/live/l8b_texcreate_record.txt`: 7 `TextureD3D12::create` captures (ret=0xE814560), all format 0x1C. The only capture exposing the record is RCX hit=1 (record 0x3905AC6C8C0): record+0x98 dword = 0 ⇒ **NOT a render target** per e81c3af; +0x9C=0x40 w, +0xA0=0x40 h, +0xA4=0, +0xA8=1 layers, +0xB0 byte=0x43 (bgfx fmt id), +0xB1=1 mip. [V live]
- Live texture record h=0x56A (BGFX_MAP.md 6im): desc Format+0x28 = 0x1C = `DXGI_FORMAT_R8G8B8A8_UNORM`; bgfx +0xB0=0x43 maps via `data_f4ed700` to DXGI 0x1C. [V live]
- livemem of `data_f4ed700` (VA base+0xF4ED700 = 0x7ff7b54ed700): 16-byte entries confirmed; observed DXGI values 0x1C/0x1B/0x5A/0x43; entries repeat from offset 0x30. [V live]

## Which creations set the RT flag

Only capture hit=1 exposes record+0x98 (= 0 ⇒ not RT). The other six creations' bgfx flags are not in the capture. Static analysis: createTexture resets +0x98 to 0 (e814820) then ORs 0x200000 for fmt 0x1B/0x5A (e8148de) — neither sets a 0xF000 RT bit — so the RT flag requires a caller that sets bgfx flags & 0xF000 on record+0x98 before `TextureD3D12::create`; the other two callers (0xe815840 RTX override, 0xe8403d0) were not checked for +0x98 setup. Therefore which of the 7 live creations set `D3D12_FLAGS`|1 (RT) is **not [V]-proven** by static analysis or the capture.

CLOSES?: NO — the render-target flag mechanism (record+0x98 bgfx flags marker tested at `0xe81c3af  test r10d,0xF000`, `D3D12_FLAGS` record+0x38, |=1 at `0xe81c3bc  or byte ptr [r13+0x38],1`, |=2 at `0xe81c2b7  or byte ptr [r13+0x38],2`) and the bgfx→DXGI format table `data_f4ed700` are proven [V], and all 7 live creations use format 0x1C (`DXGI_FORMAT_R8G8B8A8_UNORM`), but per-creation bgfx flags (record+0x98) for the 7 live creations are captured only for hit=1 (+0x98=0 ⇒ NOT RT); static analysis cannot determine which callers set bgfx flags & 0xF000, so which of the 7 creations set `D3D12_FLAGS`|1 is the single blocking fact. [V per row; blocking fact noted above]

## NEXT
DONE
