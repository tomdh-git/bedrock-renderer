# Function dossier: sub_0xbc2be20 (lifted)

- RVA: 0xbc2be20, size 0x1ec ([0xbc2be20, 0xbc2c00c)), depth 1, milestone 1 (D0), region bgfx, root 0xbb6b350.
- Source: src/client/features/render/native/bgfx/sub_bc2be20.cpp (+ header sub_bc2be20.h).
- Exe: Minecraft Windows.exe 1.26.62.01. All facts below are [V] from `rdis dis 0xbc2be20` (full function listing) unless tagged otherwise.

## Signature
`sub_bc2be20_state* sub_0xbc2be20(sub_bc2be20_state* dst /*rcx*/, sub_bc2be20_state* src /*rdx*/) -> sub_bc2be20_state* (rax = dst)`

Return value: at epilogue `0xbc2bf68  mov rax,[rbp-8]` where `[rbp-8] = r10 = dst` (stored at `0xbc2bf27  mov [rbp-8],r10`); rax is then used as the store base through the tail block and no later instruction writes rax, so `ret` at `0xbc2c00b` returns the destination pointer.

## Register / argument map
- rcx = dst (copied to r10 at `0xbc2be36  mov r10,rcx`, spilled to [rbp-8] at `0xbc2bf27  mov [rbp-8],r10`)
- rdx = src (copied to rsi at `0xbc2be33  mov rsi,rdx`)
- rbp = frame pointer ([rbp-0x10] spill slot for &dst+0x38 at `0xbc2bef0  mov [rbp-0x10],rax`; dead store, never reloaded)
- xmm0 = zero constant (`0xbc2be3f  xorps xmm0,xmm0`), reused for the zero stores
- al = tag byte (`0xbc2be95  movzx eax,byte ptr [rdx+0x70]`), unchanged across the switch paths

## Reversed source (complete)

// 0xbc2be20..0xbc2be3c
`0xbc2be20  push rbp; 0xbc2be21  push rsi; 0xbc2be22  sub rsp,0x38; 0xbc2be26  lea rbp,[rsp+0x30]; 0xbc2be2b  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE; 0xbc2be33  mov rsi,rdx; 0xbc2be36  mov r10,rcx; 0xbc2be39  mov rax,[rdx]; 0xbc2be3c  mov [rcx],rax`
dst[0x00] = src[0x00] (qword copy).

// 0xbc2be3f..0xbc2be52
`0xbc2be3f  xorps xmm0,xmm0; 0xbc2be42  movups [rcx+8],xmm0; 0xbc2be46  mov rax,[rdx+8]; 0xbc2be4a  mov [rcx+8],rax; 0xbc2be4e  mov rax,[rdx+0x10]; 0xbc2be52  mov [rcx+0x10],rax`
dst[0x8] = 0 (xmm0), then dst[0x8] = src[0x8]; dst[0x10] = src[0x10].

// 0xbc2be56..0xbc2be5e
`0xbc2be56  movups [rdx+8],xmm0; 0xbc2be5a  movups [rcx+0x18],xmm0; 0xbc2be5e  mov qword ptr [rcx+0x28],0`
src[0x8] = 0 (src mutated), dst[0x18] = 0 (16 bytes), dst[0x28] = 0.

// 0xbc2be66..0xbc2be6a
`0xbc2be66  movzx eax,byte ptr [rdx+0x30]; 0xbc2be6a  mov [rcx+0x30],al`
dst[0x30] = src[0x30] (byte).

// 0xbc2be6d..0xbc2be8d
`0xbc2be6d  movups xmm1,[rdx+0x38]; 0xbc2be71  movups xmm2,[rdx+0x48]; 0xbc2be75  mov qword ptr [rdx+0x40],0; 0xbc2be7d  movups [rdx+0x48],xmm0; 0xbc2be81  movups [rcx+0x38],xmm1; 0xbc2be85  movups [rcx+0x48],xmm2; 0xbc2be89  mov rax,[rdx+0x58]; 0xbc2be8d  mov [rcx+0x58],rax`
dst[0x38] = src[0x38] (16 B); src[0x40] = 0 (src mutated); src[0x48] = 0 (src mutated); dst[0x48] = src[0x48] (16 B); dst[0x58] = src[0x58].

// 0xbc2be91..0xbc2bea7
`0xbc2be91  mov byte ptr [rcx+0x70],0xFF; 0xbc2be95  movzx eax,byte ptr [rdx+0x70]; 0xbc2be99  cmp rax,3; 0xbc2be9d  ja short 0xBC2BEEC; 0xbc2be9f  lea rcx,[r10+0x60]; 0xbc2bea3  lea rdx,[rsi+0x60]; 0xbc2bea7  lea r8,[0xF440D90]`
dst[0x70] = 0xFF; tag = src[0x70]; if tag > 3 goto 0xbc2beec; else switch through table at 0xF440D90:
`0xbc2beae  movsxd r9,[r8+rax*4]; 0xbc2beb2  add r9,r8; 0xbc2beb5  jmp r9`
Jump table entries [V] (bytes reconstructed from two consistent `rdis dis` passes of 0xF440D90: `0xF440D90 pop rax`, `0xF440D91 mov cl,0x7E`, `0xF440D93 cld`, `0xF440D94 sub [rcx-0x4ECF0382],dh`, `0xF440D9A jle short 0xF440D98`, `0xF440D9C cmp [rcx-0x24470382],dh`; entry i = dword at 0xF440D90+4*i, target = 0xF440D90 + sign32(entry)):
- tag 0 -> 0xbc2bee8
- tag 1 -> 0xbc2beb8
- tag 2 -> 0xbc2bec0
- tag 3 -> 0xbc2bec8
All four targets are the case blocks following 0xbc2beb5 in the function disassembly.

// 0xbc2beb8..0xbc2bebe (tag 1)
`0xbc2beb8  mov rdx,[rdx]; 0xbc2bebb  mov [rcx],rdx; 0xbc2bebe  jmp short 0xBC2BEE8`
dst[0x60] = *(*(u64*)(src + 0x60)) (dereferenced pointer copy); then fall to 0xbc2bee8.

// 0xbc2bec0..0xbc2bec6 (tag 2)
`0xbc2bec0  movups xmm0,[rdx]; 0xbc2bec3  movups [rcx],xmm0; 0xbc2bec6  jmp short 0xBC2BEE8`
dst[0x60..0x6f] = src[0x60..0x6f] (16 B movups); then fall to 0xbc2bee8.

// 0xbc2bec8..0xbc2bee4 (tag 3)
`0xbc2bec8  movups [rcx],xmm0; 0xbc2becb  mov rcx,[rsi+0x68]; 0xbc2becf  test rcx,rcx; 0xbc2bed2  je short 0xBC2BED8; 0xbc2bed4  lock inc dword ptr [rcx+8]; 0xbc2bed8  mov rcx,[rsi+0x60]; 0xbc2bedc  mov [r10+0x60],rcx; 0xbc2bee0  mov rcx,[rsi+0x68]; 0xbc2bee4  mov [r10+0x68],rcx`
dst[0x60..0x6f] = 0 (xmm0 is 0; dead store, overwritten below); p = src[0x68]; if p != 0: lock inc dword ptr [p+8] (addref); dst[0x60] = src[0x60]; dst[0x68] = src[0x68].

// 0xbc2bee8
`0xbc2bee8  mov [r10+0x70],al`
dst[0x70] = tag (reached for tags 0..3; al still holds the tag).

// 0xbc2beec (tag > 3 default)
dst[0x70] keeps 0x91's 0xFF; nothing else written by the switch.

// 0xbc2beec..0xbc2bf30
`0xbc2beec  lea rax,[r10+0x38]; 0xbc2bef0  mov [rbp-0x10],rax; 0xbc2bef4  mov rax,[rsi+0x88]; 0xbc2befb  mov [r10+0x88],rax; 0xbc2bf02  movups xmm0,[rsi+0x78]; 0xbc2bf06  movups [r10+0x78],xmm0; 0xbc2bf0b  mov rax,[rsi+0x90]; 0xbc2bf12  mov [r10+0x90],rax; 0xbc2bf19  lea rcx,[r10+0x98]; 0xbc2bf20  lea rdx,[rsi+0x98]; 0xbc2bf27  mov [rbp-8],r10; 0xbc2bf2b  call 0xE869FF0; 0xbc2bf30  nop`
dst[0x88] = src[0x88]; dst[0x78] = src[0x78] (16 B); dst[0x90] = src[0x90]; `0xbc2bf2b  call 0xE869FF0` with rcx = &dst[0x98], rdx = &src[0x98]; return value unused. Spills of &dst+0x38 ([rbp-0x10]) and dst ([rbp-8]) have no observable effect.

// 0xbc2bf31..0xbc2bf61
`0xbc2bf31  mov rax,[rsi+0x110]; 0xbc2bf38  mov rcx,[rbp-8]; 0xbc2bf3c  mov [rcx+0x110],rax; 0xbc2bf43  mov qword ptr [rsi+0x110],0; 0xbc2bf4e  add rcx,0x118; 0xbc2bf55  lea rdx,[rsi+0x118]; 0xbc2bf5c  call 0x5669770; 0xbc2bf61  nop`
dst[0x110] = src[0x110]; src[0x110] = 0 (move, src mutated); `0xbc2bf5c  call 0x5669770` with rcx = &dst[0x118], rdx = &src[0x118]; return value unused.

// 0xbc2bf62..0xbc2bffe
`0xbc2bf62  mov ecx,[rsi+0x24C]; 0xbc2bf68  mov rax,[rbp-8]; 0xbc2bf6c  mov [rax+0x24C],ecx; 0xbc2bf72  movups xmm0,[rsi+0x23C]; 0xbc2bf79  movups [rax+0x23C],xmm0; 0xbc2bf80  movzx ecx,byte ptr [rsi+0x250]; 0xbc2bf87  mov [rax+0x250],cl; 0xbc2bf8d  movss xmm0,[rsi+0x254]; 0xbc2bf95  movss [rax+0x254],xmm0; 0xbc2bf9d  movss xmm0,[rsi+0x258]; 0xbc2bfa5  movss [rax+0x258],xmm0; 0xbc2bfad  movss xmm0,[rsi+0x25C]; 0xbc2bfb5  movss [rax+0x25C],xmm0; 0xbc2bfbd  movss xmm0,[rsi+0x260]; 0xbc2bfc5  movss [rax+0x260],xmm0; 0xbc2bfcd  movups xmm0,[rsi+0x264]; 0xbc2bfd4  movups xmm1,[rsi+0x274]; 0xbc2bfdb  movups xmm2,[rsi+0x283]; 0xbc2bfe2  movups [rax+0x264],xmm0; 0xbc2bfe9  movups [rax+0x274],xmm1; 0xbc2bff0  movups [rax+0x283],xmm2; 0xbc2bff7  mov rcx,[rsi+0x294]; 0xbc2bffe  mov [rax+0x294],rcx`
dst[0x24C] = src[0x24C] (dword); dst[0x23C] = src[0x23C] (16 B); dst[0x250] = src[0x250] (byte); dst[0x254/0x258/0x25C/0x260] = src[...] (movss floats); dst[0x264] = src[0x264], dst[0x274] = src[0x274], dst[0x283] = src[0x283] (16 B movups each; +0x274 and +0x283 reads overlap at byte 0x283); dst[0x294] = src[0x294]. All dst writes use the reloaded dst (rax = [rbp-8]).

// 0xbc2c005..0xbc2c00b
`0xbc2c005  add rsp,0x38; 0xbc2c009  pop rsi; 0xbc2c00a  pop rbp; 0xbc2c00b  ret`
Return dst (rax).

## Struct fields touched (sub_bc2be20_state, src/client/features/render/native/bgfx/sub_bc2be20.h)
| offset | size | dir | meaning | tag |
| 0x00 | 8 | R src, W dst | qword copy | [V] |
| 0x08 | 8 | R/W both | qword copy dst; src zeroed | [V] |
| 0x10 | 8 | R/W both | qword copy | [V] |
| 0x18 | 16 | W dst | zeroed | [V] |
| 0x28 | 8 | W dst | zeroed | [V] |
| 0x30 | 1 | R/W both | byte copy | [V] |
| 0x38 | 16 | R/W both | movups copy | [V] |
| 0x40 | 8 | W src | zeroed | [V] |
| 0x48 | 16 | R/W both | movups copy; src zeroed | [V] |
| 0x58 | 8 | R/W both | qword copy | [V] |
| 0x60 | 8 | R/W both | pointer field, switch-dependent | [V] |
| 0x68 | 8 | R/W both | pointer field; addref of pointee+8 | [V] |
| 0x70 | 1 | R/W both | switch tag; dst = tag (<=3) else 0xFF | [V] |
| 0x78 | 16 | R/W both | movups copy | [V] |
| 0x88 | 8 | R/W both | qword copy | [V] |
| 0x90 | 8 | R/W both | qword copy | [V] |
| 0x98 | 24 | R/W both | sub_e869ff0(&dst+0x98, &src+0x98) | [V] |
| 0x110 | 8 | R/W both | move src->dst, src cleared | [V] |
| 0x118 | 0x124 | R/W both | sub_5669770(&dst+0x118, &src+0x118) | [V] |
| 0x23C | 16 | R/W both | movups copy | [V] |
| 0x24C | 4 | R/W both | dword copy | [V] |
| 0x250 | 1 | R/W both | byte copy | [V] |
| 0x254/0x258/0x25C/0x260 | 4 each | R/W both | movss float copies | [V] |
| 0x264 | 16 | R/W both | movups copy | [V] |
| 0x274 | 16 | R src | movups copy (reads [0x274,0x283)] | [V] |
| 0x283 | 16 | R/W both | movups copy (reads [0x283,0x293), overlaps +0x274 tail) | [V] |
| 0x294 | 8 | R/W both | qword copy | [V] |

## Callees
- `0xbc2bf2b  call 0xE869FF0` -> sub_e869ff0: class `lift` in docs/data/native_boundary.tsv (also native_functions.tsv, d3d12, size 0xd1, depth 0). Forward-declared in sub_bc2be20.h (namespace native), called by native symbol. [V]
- `0xbc2bf5c  call 0x5669770` -> sub_5669770: class `lift` in docs/data/native_boundary.tsv (pass-tasks, size 0x36a, depth 0). Forward-declared in sub_bc2be20.h (namespace native), called by native symbol. [V]
- No other calls. UNRESOLVED CALL = none.

## Jump table (0xF440D90)
Resolved statically [V] from two consistent rdis disassembly passes of the table region (see quoted lines above); all four entries target in-function case blocks, so no indirect-target gap remains.

## Ownership / threading
- Writes to `src` (fields 0x8, 0x40, 0x48 zeroed; 0x110 moved then cleared): src is caller-owned and mutated like the original; no private state kept.
- `lock inc dword ptr [p+8]` at 0xbc2bed4 is an atomic addref of the object at src[0x68] (pointee + 8 refcount). Lifted code mirrors it with `_InterlockedIncrement`.
- No null guards, SEH, or exception handling in the original; none added.
- No inter-thread visibility requirements beyond the atomic addref; V2 footprint applies to the dst/src regions declared by the caller.

## Version anchors
- Minecraft Windows 1.26.62.01; RVAs image-relative; struct layout asserted via static_assert in sub_bc2be20.h.

## Verification
- Static: liftcheck pending (see unit output file docs/progress/oc_U-EX1.bc2be20.md).
- No live verification yet (L1).

## Open questions
None. The jump table at 0xF440D90 was resolved statically; both callees are class `lift` and forward-declared.
