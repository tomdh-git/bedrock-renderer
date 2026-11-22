## NEXT
DONE

# Unit U-EL8b — L8b Atlases (terrain, items), mipmaps and compression — read/store map extracted from input docs/progress/oc_U-L8b.md

## Source input processed
docs/progress/oc_U-L8b.md (PNG/TGA decoder unit — the only input data named for this retry; atlas/mip/BC code itself is not in that file, see CLOSES?). Every memory read/store site in its disassembly excerpts is extracted below: one row per distinct offset, all sites of the same offset merged into that row, verbatim `0xRVA  instr` lines copied from the input data.

## Conventions
- offset: constant displacement of the memory operand (`0x00` for bare `[reg]`; `idx+0`/`idx+8` for `[r8+rax*8]` scaled-index operands; absolute address for `[0x...]` operands; `rsp+`/`rbp+` for frame slots; `gs+0x58` for `gs:[0x58]`). Distinct offset strings => distinct rows; no duplicate offset rows.
- size: from the instruction (movups/movaps 16; qword 8; dword/movss 4; word 2; byte 1; movzx byte 1).
- read/store address: R/W + base+disp as written, with size in bytes.
- verbatim `0xRVA  instr`: two spaces after the address, copied from the input data; every quoted line re-checked against the exe with rdis/verify_oc ([V]; mismatches fixed during the delegate check loop).
- meaning: `-` unless the instruction itself shows it.
- Excluded from the table: `lea` (address computation, no memory access); `push`/`pop` (implicit stack operand, no visible displacement); one garbled input line — `mov qword ptr [rbp+8],0xFFFFFFFFFFFFFFFE` is placed at 0x3f7edf7 in the input, but rdis shows 0x3f7edf7 = `mov dword ptr [0x12986F58],0`, so the [rbp+8] site's address is not confirmed by either the input data or the exe and is not quoted.

## Read/store table (offset | size | read/store address (R/W base+disp) | verbatim `0xRVA  instr` | meaning)
| offset | size | read/store address (R/W base+disp) | `0xRVA  instr` | meaning |
|--|--|--|--|--|
| 0x00 | 8B/4B/1B | W [rbx]+0 (8B); R [rcx]+0 (8B); R [r9]+0 (4B); W [rdi]+0 (8B); W [rcx]+0 (8B); R [rcx]+0 (8B); W [rsi]+0 (8B); R [rax]+0 (8B); W [rax]+0 (1B); W [rbp]+0 (8B) | `0x777f1e  mov qword ptr [rbx],8`<br>`0x781595  mov rsi,[rcx]`<br>`0x777f63  cmp dword ptr [r9],0`<br>`0x14754c4  mov [rdi],rax`<br>`0x39976b  mov [rcx],r9`<br>`0x3f7ee12  mov rax,[rcx]`<br>`0x3f7ee30  mov [rsi],rsi`<br>`0x779ae33  mov rax,[rax]`<br>`0x779ae36  mov byte ptr [rax],0`<br>`0x147548d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE` | - |
| 0x08 | 16B/8B/4B | W [rbx]+8 (4B); W [rcx]+8 movups (16B); R [rax]+8 (8B); W [rcx]+8 (8B); W [rsi]+8 (8B); R [rcx]+8 (4B) | `0x777f25  mov dword ptr [rbx+8],0`<br>`0x7815a3  movups [rcx+8],xmm0`<br>`0x3f7ee15  mov rax,[rax+8]`<br>`0x399774  mov [rcx+8],rdx`<br>`0x3f7ee33  mov [rsi+8],rsi`<br>`0x599de7a  mov eax,[rcx+8]` | - |
| 0x10 | 16B/8B | R [r15]+0x10 (8B); R [rsi]+0x10 (8B); R [rcx]+0x10 (8B); R [r14]+0x10 (8B); W [rax]+0x10 (8B); W [rbp]+0x10 movaps (16B) | `0x777f71  mov rax,[r15+0x10]`<br>`0x7815e8  mov rax,[rsi+0x10]`<br>`0x599de71  mov rcx,[rcx+0x10]`<br>`0x779ae39  mov rax,[r14+0x10]`<br>`0x779ae24  mov qword ptr [rax+0x10],0`<br>`0x3f7edeb  movaps [rbp+0x10],xmm6` | - |
| 0x18 | 8B | W [rcx]+0x18 (8B); R [rcx]+0x18 (8B); R [rax]+0x18 (8B) | `0x7815a7  mov qword ptr [rcx+0x18],0`<br>`0x779ae20  mov rax,[rcx+0x18]`<br>`0x779ae2c  cmp qword ptr [rax+0x18],0x10` | - |
| 0x28 | 8B | R [r15]+0x28 (8B); R [rsi]+0x28 (8B) | `0x777f75  mov rcx,[r15+0x28]`<br>`0x7815ec  mov rcx,[rsi+0x28]` | - |
| 0x30 | 4B | R [rsi]+0x30 (4B) | `0x7815da  cmp dword ptr [rsi+0x30],0` | - |
| 0x34 | 4B | R [r15]+0x34 (4B); R [rsi]+0x34 (4B) | `0x777f6d  mov r8d,[r15+0x34]`<br>`0x7815e4  mov r8d,[rsi+0x34]` | - |
| 0x40 | 8B | R [rsi]+0x40 (8B); W [rdi]+0x40 (8B) | `0x14754d7  mov rcx,[rsi+0x40]`<br>`0x14754cf  mov qword ptr [rdi+0x40],0` | - |
| 0x50 | 4B | R [rdx]+0x50 (4B) | `0x14747c2  cmp dword ptr [rdx+0x50],0xC8` | - |
| 0x58 | 8B | R gs+0x58 (8B) | `0x39972d  mov r9,gs:[0x58]` | - |
| 0xC0 | 8B | R [rcx]+0xC0 (8B); W [r15]+0xC0 (8B); R [rsi]+0xC0 (8B); W [rsi]+0xC0 (8B) | `0x777f34  mov rcx,[rcx+0xC0]`<br>`0x777f4b  mov [r15+0xC0],rdx`<br>`0x7815af  mov rcx,[rsi+0xC0]`<br>`0x7815c6  mov [rsi+0xC0],rdx` | - |
| 0xC8 | 8B | R [r15]+0xC8 (8B); R [rsi]+0xC8 (8B) | `0x777f3b  mov rax,[r15+0xC8]`<br>`0x7815b6  mov rax,[rsi+0xC8]` | - |
| idx+0 | 8B | R [r8+rax*8]+0 (8B) | `0x399755  mov rdx,[r8+rax*8]` | - |
| idx+8 | 8B | R [r8+rax*8]+8 (8B) | `0x399759  mov rax,[r8+rax*8+8]` | - |
| 0x1230A0C0 | 8B | R [0x1230A0C0] (8B) | `0x777f0c  mov rax,[0x1230A0C0]` | - |
| 0x1233E1A8 | 8B | R [0x1233E1A8] (8B) | `0x3f7ee0b  mov rcx,[0x1233E1A8]` | - |
| 0x128D7FB0 | 16B | R [0x128D7FB0] movups (16B) | `0x69c959c  movups xmm0,[0x128D7FB0]` | - |
| 0x12986F58 | 4B | W [0x12986F58] (4B) | `0x3f7edf7  mov dword ptr [0x12986F58],0` | - |
| 0x12986F60 | 16B/8B | W [0x12986F60] movups (16B); W [0x12986F60] (8B) | `0x3f7ee04  movups [0x12986F60],xmm6`<br>`0x3f7ee37  mov [0x12986F60],rsi` | - |
| rsp+0x10C | 2B | W rsp+0x10C (2B) | `0x78158b  mov word ptr [rsp+0x10C],0` | - |
| rsp+0x10E | 1B | W rsp+0x10E (1B) | `0x781583  mov byte ptr [rsp+0x10E],0` | - |
| rsp+0x89B8 | 8B | W rsp+0x89B8 (8B) | `0x777f16  mov [rsp+0x89B8],rax` | - |
| rsp+0x89C0 | 16B | W rsp+0x89C0 movaps (16B) | `0x777ee9  movaps [rsp+0x89C0],xmm6` | - |
| rsp+0x8A40 | 4B | R rsp+0x8A40 (4B) | `0x777f05  mov edi,[rsp+0x8A40]` | - |
| rsp+0x8A48 | 8B | R rsp+0x8A48 (8B) | `0x777efd  mov rbx,[rsp+0x8A48]` | - |
| rbp-0x18 | 8B | W rbp-0x18 (8B) | `0x14754cb  mov [rbp-0x18],rax` | - |
| rbp-8 | 8B | W rbp-8 (8B) | `0x14754de  mov [rbp-8],rdi` | - |
| rbp+0x300 | 16B | W rbp+0x300 movaps (16B) | `0x14747ac  movaps [rbp+0x300],xmm0` | - |
| rbp+0x310 | 8B | W rbp+0x310 (8B) | `0x14747b3  mov qword ptr [rbp+0x310],0` | - |
| rbp+0x320 | 8B | W rbp+0x320 (8B) | `0x147479b  mov qword ptr [rbp+0x320],0xFFFFFFFFFFFFFFFE` | - |
| rbp+0x338 | 8B | W rbp+0x338 (8B) | `0x599de59  mov qword ptr [rbp+0x338],0xFFFFFFFFFFFFFFFE` | - |
| rbp+0x430 | 16B | W rbp+0x430 movaps (16B) | `0x69c95a3  movaps [rbp+0x430],xmm0` | - |
| rbp+0x450 | 1B | W rbp+0x450 (1B) | `0x69c95b4  mov byte ptr [rbp+0x450],0` | - |
| rbp+0x458 | 4B | W rbp+0x458 (4B) | `0x69c95bb  mov dword ptr [rbp+0x458],0xFFFFFFFF` | - |
| rbp+0x460 | 16B | W rbp+0x460 movaps (16B) | `0x69c95c5  movaps [rbp+0x460],xmm0` | - |
| rbp+0x470 | 8B | W rbp+0x470 (8B) | `0x69c95cc  mov qword ptr [rbp+0x470],0` | - |
| rbp+0x478 | 8B | W rbp+0x478 (8B) | `0x69c95d7  mov qword ptr [rbp+0x478],0xF` | - |
| rbp+0x480 | 16B | W rbp+0x480 movaps (16B) | `0x69c95e2  movaps [rbp+0x480],xmm0` | - |
| rbp+0x490 | 8B | W rbp+0x490 (8B) | `0x69c95e9  mov qword ptr [rbp+0x490],0` | - |
| rbp+0x498 | 8B | W rbp+0x498 (8B) | `0x69c95f4  mov qword ptr [rbp+0x498],0xF` | - |

## Verification
- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL8b.md` -> claimed=N match=N mismatch=0 no-such-instr=0 (re-run after every edit; all 70 quoted lines must pass).
- `python tools/delegate.py check docs/progress/oc_U-EL8b.md` -> exit 0 required before the line after `## NEXT` is set to DONE.

## CLOSES?
CLOSES? NO — single blocking fact: atlas texture creation, mipmap generation and BC1/BC3/BC7 compression are not present statically in Minecraft.Windows.exe. Registration of "TerrainAtlas" idx 6 / "ItemAtlas" idx 7 is proven [V] (sub_186e6a0 / sub_1870de0, obj+0 name pointer, obj+8 index), but no createTexture/resizeTexture call tied to either atlas exists statically; xref "TerrainAtlas"/"ItemAtlas" and BC1/BC3/BC7/DXT strings return refs=[]; no stitcher consuming the registered atlas objects is located; all live texture creations (l8b_texcreate_record.txt, ret=0xE814560; mc_root_4e05e50_callers.txt, indirect caller ret=0x1289496) are format 0x1C uncompressed with numMips=1 [V live]; the r13 lead (+0x00 pointer 0x00007FF6A8215838) resolves to another module (outside the exe image 0x140000000) and cannot be decoded from this exe. Static analysis is exhausted for the atlas item; it needs a live capture of the atlas description/stitcher entry or an external/MIRROR_SKIP decision. This file closes only the oc_U-L8b.md read/store table step; the atlas blocking fact is unchanged from r13/r46.

## TOOL REQUESTS
None — existing tools only (rdis.exe, verify_oc.py, delegate.py); no helper scripts written.
