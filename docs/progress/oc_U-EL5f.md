## NEXT
DONE

# Unit U-EL5f: general skinned clone 0x6b84e60 field map (L5f Tag 7 pending part)

## Scope

Checklist item L5f: "Tag 7 = skinned items incl. entity models (live: ender_dragon.skinning, 6cn) + block-entity overlays (6cj); general skinned clone 0x6b84e60 not decoded".
The live sub-parts (ender_dragon.skinning / 6cn) and the block-entity overlays (6cj) are the other parts of the line and are NOT re-opened here. The ONLY pending part decoded in this unit is: **general skinned clone 0x6b84e60 not decoded** — the field store map of the intermediate description object(s) this clone writes.

## Source data (read fully, not re-computed)

`docs/progress/clone_6b84e60.txt` — rdis listing of `sub_6b84e60` [0x6b84e60..0x6b86a50), size 0x1bf0, 5 xrefs in (callers sub_6b80870 x1, sub_6b80f00 x1, sub_6e8dff0 x3). Listing produced from Minecraft.Windows.exe 1.26.62.01; every `0xRVA  instr` quoted below is copied verbatim from that listing and is re-verified against the exe by `verify_oc.py` (see `python tools/delegate.py check` at the end).

## Argument / object setup (seen in the listing)

- `0x6b84e92  mov rsi,rdx` — rsi = arg2 = source data pointer.
- `0x6b84e95  mov r14,rcx` — r14 = arg1 rcx = frameBuilder this-pointer.
- Description object is allocated by `0x6b84f7c  call 0x6B86E80` (sub_6b86e80) and by `0x6b852df  call 0x6B86E80` (second build path); the description pointer is `rax+0x10`, held in `r13` (`0x6b84f97  mov r13,[rax+0x10]`) for build path 1 and in `r15` (`0x6b852fa  mov r15,[rax+0x10]`) for build path 2.
- Both paths write the IDENTICAL field set below; the listing contains no other memory store into [desc+off] (exhaustive scan of all memory-write instructions in the function).

## Field map: description written by clone 0x6b84e60 (both build paths)

| offset | size | field / write sites | `0xRVA  instr` proof | meaning | tag |
| desc+0x0 | 8B | desc ptr in r13 (path 1): 0x6b84fac; desc ptr in r15 (path 2): 0x6b8530f | `0x6b84fac  mov [r13],r14`<br>`0x6b8530f  mov [r15],r14` | desc+0x0 = r14; r14 = arg1 rcx = BgfxFrameBuilder this-pointer (`mov r14,rcx` at 0x6b84e95): back-pointer to the frame builder | [V] |
| desc+0x8 | 1B | path 1: 0x6b84fb0; path 2: 0x6b85312 | `0x6b84fb0  mov byte ptr [r13+8],1`<br>`0x6b85312  mov byte ptr [r15+8],1` | byte store = 1 (type/enable byte) | [V] |
| desc+0x10 | 8B | path 1: 0x6b84fb5; path 2: 0x6b85317 | `0x6b84fb5  mov [r13+0x10],rax`<br>`0x6b85317  mov [r15+0x10],rax` | qword store = rax; rax = movsxd dword [frameBuilder+0x528] (`movsxd rax,[r14+0x528]` at 0x6b84fa5 path 1, 0x6b85308 path 2) | [V] |
| desc+0x18 | 16B | path 1: 0x6b84fc7; path 2: 0x6b85329 | `0x6b84fc7  movups [r13+0x18],xmm0`<br>`0x6b85329  movups [r15+0x18],xmm0` | movups 16-byte store; loaded from [[rsi+0x30]+0x0..0xF] (`mov rax,[rsi+0x30]` at 0x6b84fb9 path 1, 0x6b8531b path 2; `movups xmm0,[rax]` at 0x6b84fc4 / 0x6b85326) | [V] |
| desc+0x28 | 4B | path 1: 0x6b84fc0; path 2: 0x6b85322 | `0x6b84fc0  mov [r13+0x28],ecx`<br>`0x6b85322  mov [r15+0x28],ecx` | dword store = ecx = [[rsi+0x30]+0x10] | [V] |
| desc+0x2C | 16B | path 1: 0x6b84fdb; path 2: 0x6b8533d | `0x6b84fdb  movdqu [r13+0x2C],xmm0`<br>`0x6b8533d  movdqu [r15+0x2C],xmm0` | movdqu 16-byte store; loaded from [[rsi+0x38]+0x0..0xF] (`mov rax,[rsi+0x38]` at 0x6b84fcc path 1, 0x6b8532e path 2; `movdqu xmm0,[rax]` at 0x6b84fd7 / 0x6b85339) | [V] |
| desc+0x3C | 4B | path 1: 0x6b84fd3; path 2: 0x6b85335 | `0x6b84fd3  mov [r13+0x3C],ecx`<br>`0x6b85335  mov [r15+0x3C],ecx` | dword store = ecx = [[rsi+0x38]+0x10] | [V] |
| desc+0x40 | - | address taken only, no store: path 1 0x6b84fe1; path 2 0x6b85343 | `0x6b84fe1  lea rcx,[r13+0x40]`<br>`0x6b84fe8  call 0x6B87E00`<br>`0x6b85343  lea rcx,[r15+0x40]`<br>`0x6b8534a  call 0x6B87E00` | desc+0x40 address passed to sub_6b87e00; this clone performs NO store at +0x40 (size comes from an instruction; none exists here) | [V] |
| desc+0x190 | 16B | path 1: 0x6b84ff8; path 2: 0x6b8535a | `0x6b84ff8  movdqu [r13+0x190],xmm0`<br>`0x6b8535a  movdqu [r15+0x190],xmm0` | movdqu 16-byte store = zeroed (`pxor xmm0,xmm0` at 0x6b84ff4 path 1, 0x6b85356 path 2) | [V] |
| desc+0x1A0 | 8B | path 1: 0x6b85001; path 2: 0x6b85363 | `0x6b85001  mov qword ptr [r13+0x1A0],0`<br>`0x6b85363  mov qword ptr [r15+0x1A0],0` | qword store = 0 | [V] |

Field semantics beyond what an instruction shows (e.g. a "matrix" or "count" name) are not stated: no string or symbolic info names these fields in this clone; meaning column lists only what the instruction itself shows.

## Context for Tag 7

- `0x6b86693  mov byte ptr [rbp+0x318],7` — insert variant tag = 7 stored on the stack at the end of the clone. Per docs/BGFX_MAP.md §3 (Item group variants), Item index 7 = SkinnedMesh: this clone is the Item-group tag-7 ("general skinned") insert path ([V] for the store; [I] for the map association). No description-field store carries the tag; the tag lives on the stack.
- `0x6b86616  call 0x668D350` — sub_668d350 builder consumes the intermediate description to produce the final 0x1D0 RenderSkinnedMeshDescription; that builder's field store table is unit D5f, not this clone, and is not decoded here.
- `0x6b869de  lea rax,[0xF52E07A]` references the "FrameBuilder - Insert" string (profiler scope); error strings "Quad material doesn't exist" (0x6b85272), "Tri material doesn't exist" (0x6b8539d), "Mesh material doesn't exist" (0x6b85b6f/0x6b866e4) guard the material selection.

## Verification

`python tools/delegate.py check docs/progress/oc_U-EL5f.md` — verify_oc re-checks every quoted `0xRVA  instr` against rdis disassembly of the exe; shape checks require >=3 table rows, no duplicate offset rows, instruction-size agreement, no raw instruction dumps, no placeholder entries.

CLOSES? YES — the pending part "general skinned clone 0x6b84e60 not decoded" is proven by [V] rows: complete store map of every distinct description offset (+0x0, +0x8, +0x10, +0x18, +0x28, +0x2C, +0x3C, +0x40 address-taken-only, +0x190, +0x1A0) across both build paths, all sites quoted verbatim from the listing, no store offset skipped, every quoted instruction verified against the exe.
