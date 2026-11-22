## NEXT
DONE

# oc U-EF1b — VV pass order from builder 0x55f1450 (checklist F1b, BGFX_MAP 6ar): in/out resources per pass

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only.
Builder range: 0x55f1450..0x563f594 (0x4E144 bytes) [V preflight fn header, oc_U-F1b.md].
Input data read in full: docs/progress/oc_U-F1b.md, docs/progress/oc_U-F1b2.md.

Pending part of checklist item F1b: "in/out resources per pass still pending".
Prior result (oc_U-EL6b.md, verify_oc 11/11): pass declaration fns copy a 28-byte descriptor struct opaquely [V]; nothing in 0x55f1450 or callees separates input from output resources statically, so in/out stays open.

## BGFX_MAP.md sections consulted
- 6aq (line 740): pass-declaration vocabulary — BindMaterialTexture/BindFramebufferDepth/BindFramebufferColor/BindShaderBuffer/BindAccelerationStructure are the only dependency kinds; passes declare inputs/outputs only through these binders [V string-count over .rdata].
- 6ar (line 747): VV builder 0x55f1450..0x563f594 pass declaration order [V addresses].

## Descriptor copy evidence — sub_5698290 (28-byte descriptor, opaque copy) [V]
`sub_5698290 [0x5698290..0x56983b3) size 0x123` [V rdis fn]
Argument map at call sites (e.g. 0x55f1fca): rcx=[rbp+0x3260]=context, rdx=context, r8=config pointer (28-byte descriptor).
Inside sub_5698290:
- `0x56982a7  mov rbx,r8` → rbx = config/source descriptor [V]
- `0x56982bb  mov edx,0x28` → alloc size imm 0x28=40 bytes passed to sub_eea6040 allocator [V]
- copies exactly 28 bytes (0x00-0x1B) from [rbx] to [rdi+8] via two overlapping movups, no field interpreted [V]
- appends result to context vector [rsi+0x28] and builds a 0x50-byte record at [rsi+0x40] using [rsi+0x38]/[rsi+0x40]/[rsi+0x48]/[rsi+0x50]; no field of the 28-byte descriptor is tagged input or output [V]

## Field map table: descriptor offsets accessed in pass declaration (28-byte descriptor copy, sub_5698290)
One row per distinct offset; meaning literal to the instruction, else '-'. No input/output tag exists on any field.
| offset | size | address (all sites) | instr | meaning | tag |
| 0x00 | 16 | [rbx+0x00] read → [rdi+0x08] write | `0x56982dc  movups xmm0,[rbx]` / `0x56982e3  movups [rdi+8],xmm0` | 16-byte read of descriptor +0x00, copied to new object +0x08 | [V] |
| 0x0C | 16 | [rbx+0x0C] read → [rdi+0x14] write | `0x56982df  movups xmm1,[rbx+0xC]` / `0x56982e7  movups [rdi+0x14],xmm1` | 16-byte read of descriptor +0x0C, copied to new object +0x14 | [V] |
| 0x18 | 4 | - | `0x56982bb  mov edx,0x28` | imm 0x28 = 40 (alloc size arg) | [V] |

## Other declaration helpers checked — none separate input from output [V]
- sub_5667860 [0x5667860..0x5667c44): field-by-field copy (`0x5667887  movups xmm0,[rdx]` → `0x566788a  movups [rcx],xmm0`) — no input/output tag on any field [V]
- sub_5693680 [0x5693680..0x5693914): allocates 0x2F0, copies [rsi+0x268]/[rsi+0x20]/[rsi+0x10]/[rsi+0x18] (`0x56936c7  lea rdx,[rsi+0x268]`) — no input/output tag [V]
- sub_5689800 [0x5689800..0x5689bfc): range sort/merge on [rsi+0x18]/[rsi+0x20] (`0x5689891  movups xmm0,[r14+0x20]`) — no input/output resource tag [V]
- sub_5684660 [0x5684660..0x5685b25): reads [rdx+0x10]/[rdx+0x18]/[rdx+0x28]/[rdx+0x60] (`0x56846a2  mov r12,[rdx+0x10]`) — no input/output tag [V]

## Answer: in/out resources per pass
No instruction in 0x55f1450 or any of its pass-declaration callees tags a resource as input or output. The 28-byte descriptor (and larger structs in the other helpers) is copied opaquely: fields are moved byte-for-byte with no semantic distinction between input and output. Which context vector a record lands in ([rsi+0x28] vs [rsi+0x40]) is not documented by any instruction or string, so it cannot be read as input vs output (at best [I]). Therefore in/out resources per pass cannot be separated statically.

## CLOSES?
NO — blocking fact: the pass-declaration helpers copy the descriptor struct opaquely without interpreting any field as input or output (sub_5698290 copies exactly 28 bytes via `0x56982dc  movups xmm0,[rbx]` / `0x56982df  movups xmm1,[rbx+0xC]` into `0x56982e3  movups [rdi+8],xmm0` / `0x56982e7  movups [rdi+0x14],xmm1` with no field tag), and nothing in 0x55f1450 or its callees separates input from output resources statically.

## TOOL REQUESTS
- None
