## NEXT
DONE

C5b drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies pending
- [V] 6aq (BGFX_MAP.md): pass declaration functions are templates over Declarator<RenderContext> in dragon::framerenderer::drawutils; 178 distinct signatures void drawutils::<fn>(Declarator<RenderContext>&, ...); Bind* vocabulary BindMaterialTexture x1110, BindFramebufferDepth x826, BindFramebufferColor x823, BindShaderBuffer x373, BindAccelerationStructure x49 (RTX only).
- PENDING (this unit): per-pass bodies. Each body is a template-instantiation function that copies pass configuration/render-state fields from a declaration source into the pass struct via Declarator<RenderContext>.

VV builder sub_55f1450 (0x55F1450..0x563F594) calls shared sub_567b570 x90 (registration/hash helper) plus per-pass bodies sub_566xxxx/sub_567xxxx/sub_568xxxx. RTX builder sub_bbe2d50 calls sub_567b570 x3.

## ANSWER TABLE (name | rva or offset | size | site read/store address | verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?])
One row per distinct field offset; all sites that read/store that offset are listed.

sub_5667860 — complete per-pass body: field-copy declaration source (rdx=rdi=a1) -> pass dest (rcx=rsi=a0):
| 0x0 | 16 | [rdx+0x0]->[rcx+0x0] (5667860); [r8+0x0] read (5668ac0) | `0x5667887  movups xmm0,[rdx]` `0x566788a  movups [rcx],xmm0` `0x5668acf  mov rax,[r8]` | copy 16-byte render-state block at +0x0; qword read +0x0 in hash helper | [V]
| 0x10 | 8 | [rdx+0x10]->[rcx+0x10] | `0x566787f  mov rax,[rdx+0x10]` `0x5667883  mov [rcx+0x10],rax` | copy qword field +0x10 | [V]
| 0x18 | 4 | [rdx+0x18]->[rcx+0x18] | `0x566788d  movss xmm0,[rdx+0x18]` `0x5667892  movss [rcx+0x18],xmm0` | copy float field +0x18 | [V]
| 0x1C | 4 | [rdx+0x1C]->[rcx+0x1C] | `0x5667897  movss xmm0,[rdx+0x1C]` `0x566789c  movss [rcx+0x1C],xmm0` | copy float field +0x1C | [V]
| 0x20 | 4 | [rdx+0x20]->[rcx+0x20] | `0x56678a1  movss xmm0,[rdx+0x20]` `0x56678a6  movss [rcx+0x20],xmm0` | copy float field +0x20 | [V]
| 0x24 | 4 | [rdx+0x24]->[rcx+0x24] | `0x56678ab  movss xmm0,[rdx+0x24]` `0x56678b0  movss [rcx+0x24],xmm0` | copy float field +0x24 | [V]
| 0x28 | 4 | [rdx+0x28]->[rcx+0x28] | `0x56678b5  movss xmm0,[rdx+0x28]` `0x56678ba  movss [rcx+0x28],xmm0` | copy float field +0x28 | [V]
| 0x2C | 4 | [rdx+0x2C]->[rcx+0x2C] | `0x56678bf  movss xmm0,[rdx+0x2C]` `0x56678c4  movss [rcx+0x2C],xmm0` | copy float field +0x2C | [V]
| 0x30 | 4 | [rdx+0x30]->[rcx+0x30] | `0x56678c9  movss xmm0,[rdx+0x30]` `0x56678ce  movss [rcx+0x30],xmm0` | copy float field +0x30 | [V]
| 0x34 | 4 | [rdx+0x34]->[rcx+0x34] | `0x56678d3  movss xmm0,[rdx+0x34]` `0x56678d8  movss [rcx+0x34],xmm0` | copy float field +0x34 | [V]
| 0x38 | 4 | [rdx+0x38]->[rcx+0x38] | `0x56678dd  movss xmm0,[rdx+0x38]` `0x56678e2  movss [rcx+0x38],xmm0` | copy float field +0x38 | [V]
| 0x3C | 4 | [rdx+0x3C]->[rcx+0x3C] | `0x56678e7  movss xmm0,[rdx+0x3C]` `0x56678ec  movss [rcx+0x3C],xmm0` | copy float field +0x3C | [V]
| 0x40 | 4 | [rdx+0x40]->[rcx+0x40] | `0x56678f1  movss xmm0,[rdx+0x40]` `0x56678f6  movss [rcx+0x40],xmm0` | copy float field +0x40 | [V]
| 0x44 | 4 | [rdx+0x44]->[rcx+0x44] | `0x56678fb  movss xmm0,[rdx+0x44]` `0x5667900  movss [rcx+0x44],xmm0` | copy float field +0x44 | [V]
| 0x48 | 4 | [rdx+0x48]->[rcx+0x48] | `0x5667905  movss xmm0,[rdx+0x48]` `0x566790a  movss [rcx+0x48],xmm0` | copy float field +0x48 | [V]
| 0x4C | 4 | [rdx+0x4C]->[rcx+0x4C] | `0x566790f  movss xmm0,[rdx+0x4C]` `0x5667914  movss [rcx+0x4C],xmm0` | copy float field +0x4C | [V]
| 0x50 | 4 | [rdx+0x50]->[rcx+0x50] | `0x5667919  movss xmm0,[rdx+0x50]` `0x566791e  movss [rcx+0x50],xmm0` | copy float field +0x50 | [V]
| 0x54 | 4 | [rdx+0x54]->[rcx+0x54] | `0x5667923  movss xmm0,[rdx+0x54]` `0x5667928  movss [rcx+0x54],xmm0` | copy float field +0x54 | [V]
| 0x58 | 4 | [rdx+0x58]->[rcx+0x58] | `0x566792d  movss xmm0,[rdx+0x58]` `0x5667932  movss [rcx+0x58],xmm0` | copy float field +0x58 | [V]
| 0x5C | 4 | [rdx+0x5C]->[rcx+0x5C] | `0x5667937  movss xmm0,[rdx+0x5C]` `0x566793c  movss [rcx+0x5C],xmm0` | copy float field +0x5C | [V]
| 0x60 | 4 | [rdx+0x60]->[rcx+0x60] | `0x5667941  movss xmm0,[rdx+0x60]` `0x5667946  movss [rcx+0x60],xmm0` | copy float field +0x60 | [V]
| 0x64 | 4 | [rdx+0x64]->[rcx+0x64] | `0x566794b  movss xmm0,[rdx+0x64]` `0x5667950  movss [rcx+0x64],xmm0` | copy float field +0x64 | [V]
| 0x68 | 4 | [rdx+0x68]->[rcx+0x68] | `0x5667955  movss xmm0,[rdx+0x68]` `0x566795a  movss [rcx+0x68],xmm0` | copy float field +0x68 | [V]
| 0x6C | 4 | [rdx+0x6C]->[rcx+0x6C] | `0x566795f  movss xmm0,[rdx+0x6C]` `0x5667964  movss [rcx+0x6C],xmm0` | copy float field +0x6C | [V]
| 0x70 | 4 | [rdx+0x70]->[rcx+0x70] | `0x5667969  movss xmm0,[rdx+0x70]` `0x566796e  movss [rcx+0x70],xmm0` | copy float field +0x70 | [V]
| 0x74 | 4 | [rdx+0x74]->[rcx+0x74] | `0x5667973  movss xmm0,[rdx+0x74]` `0x5667978  movss [rcx+0x74],xmm0` | copy float field +0x74 | [V]
| 0x78 | 4 | [rdx+0x78]->[rcx+0x78] | `0x566797d  movss xmm0,[rdx+0x78]` `0x5667982  movss [rcx+0x78],xmm0` | copy float field +0x78 | [V]
| 0x7C | 4 | [rdx+0x7C]->[rcx+0x7C] | `0x5667987  movss xmm0,[rdx+0x7C]` `0x566798c  movss [rcx+0x7C],xmm0` | copy float field +0x7C | [V]
| 0x80 | 4 | [rdx+0x80]->[rcx+0x80] | `0x5667991  movss xmm0,[rdx+0x80]` `0x5667999  movss [rcx+0x80],xmm0` | copy float field +0x80 | [V]
| 0x84 | 4 | [rdx+0x84]->[rcx+0x84] | `0x56679a1  movss xmm0,[rdx+0x84]` `0x56679a9  movss [rcx+0x84],xmm0` | copy float field +0x84 | [V]
| 0x88 | 4 | [rdx+0x88]->[rcx+0x88] | `0x56679b1  movss xmm0,[rdx+0x88]` `0x56679b9  movss [rcx+0x88],xmm0` | copy float field +0x88 | [V]
| 0x8C | 4 | [rdx+0x8C]->[rcx+0x8C] | `0x56679c1  movss xmm0,[rdx+0x8C]` `0x56679c9  movss [rcx+0x8C],xmm0` | copy float field +0x8C | [V]
| 0x90 | 4 | [rdx+0x90]->[rcx+0x90] | `0x56679d1  movss xmm0,[rdx+0x90]` `0x56679d9  movss [rcx+0x90],xmm0` | copy float field +0x90 | [V]
| 0x94 | 4 | [rdx+0x94]->[rcx+0x94] | `0x56679e1  movss xmm0,[rdx+0x94]` `0x56679e9  movss [rcx+0x94],xmm0` | copy float field +0x94 | [V]
| 0x98 | 4 | [rdx+0x98]->[rcx+0x98] | `0x56679f1  movss xmm0,[rdx+0x98]` `0x56679f9  movss [rcx+0x98],xmm0` | copy float field +0x98 | [V]
| 0x9C | 4 | [rdx+0x9C]->[rcx+0x9C] | `0x5667a01  movss xmm0,[rdx+0x9C]` `0x5667a09  movss [rcx+0x9C],xmm0` | copy float field +0x9C | [V]
| 0xA0 | 4 | [rdx+0xA0]->[rcx+0xA0] | `0x5667a11  movss xmm0,[rdx+0xA0]` `0x5667a19  movss [rcx+0xA0],xmm0` | copy float field +0xA0 | [V]
| 0xA4 | 4 | [rdx+0xA4]->[rcx+0xA4] | `0x5667a21  movss xmm0,[rdx+0xA4]` `0x5667a29  movss [rcx+0xA4],xmm0` | copy float field +0xA4 | [V]
| 0xA8 | 4 | [rdx+0xA8]->[rcx+0xA8] | `0x5667a31  movss xmm0,[rdx+0xA8]` `0x5667a39  movss [rcx+0xA8],xmm0` | copy float field +0xA8 | [V]
| 0xAC | 4 | [rdx+0xAC]->[rcx+0xAC] | `0x5667a41  movss xmm0,[rdx+0xAC]` `0x5667a49  movss [rcx+0xAC],xmm0` | copy float field +0xAC | [V]
| 0xB0 | 4 | [rdx+0xB0]->[rcx+0xB0] | `0x5667a51  movss xmm0,[rdx+0xB0]` `0x5667a59  movss [rcx+0xB0],xmm0` | copy float field +0xB0 | [V]
| 0xB4 | 4 | [rdx+0xB4]->[rcx+0xB4] | `0x5667a61  movss xmm0,[rdx+0xB4]` `0x5667a69  movss [rcx+0xB4],xmm0` | copy float field +0xB4 | [V]
| 0xB8 | 4 | [rdx+0xB8]->[rcx+0xB8] | `0x5667a71  movss xmm0,[rdx+0xB8]` `0x5667a79  movss [rcx+0xB8],xmm0` | copy float field +0xB8 | [V]
| 0xBC | 4 | [rdx+0xBC]->[rcx+0xBC] | `0x5667a81  movss xmm0,[rdx+0xBC]` `0x5667a89  movss [rcx+0xBC],xmm0` | copy float field +0xBC | [V]
| 0xC0 | 4 | [rdx+0xC0]->[rcx+0xC0] | `0x5667a91  movss xmm0,[rdx+0xC0]` `0x5667a99  movss [rcx+0xC0],xmm0` | copy float field +0xC0 | [V]
| 0xC4 | 4 | [rdx+0xC4]->[rcx+0xC4] | `0x5667aa1  movss xmm0,[rdx+0xC4]` `0x5667aa9  movss [rcx+0xC4],xmm0` | copy float field +0xC4 | [V]
| 0xD4 | 16 | [rdx+0xD4]->[rcx+0xD4] | `0x5667ae1  movups xmm0,[rdx+0xD4]` `0x5667ae8  movups [rcx+0xD4],xmm0` | copy 16-byte block at +0xD4 | [V]
| 0xE4 | 4 | [rdx+0xE4]->[rcx+0xE4] | `0x5667aef  mov eax,[rdx+0xE4]` `0x5667af5  mov [rcx+0xE4],eax` | copy dword field +0xE4 | [V]
| 0x100 | 1 | [rcx+0x100]=0; cmp [rdx+0x100]; [rsi+0x100]=1 | `0x5667afb  mov byte ptr [rcx+0x100],0` `0x5667b02  cmp byte ptr [rdx+0x100],1` `0x5667bed  mov byte ptr [rsi+0x100],1` | init flag byte +0x100=0; branch if src byte +0x100==1; set flag byte +0x100=1 | [V]
| 0xE8 | 16 | [rsi+0xE8] zero; [rsi+0xE8]=r14 | `0x5667b19  movups [rdx],xmm0` (rdx=rsi+0xE8) `0x5667baf  mov [rsi+0xE8],r14` | zero+init vector begin at +0xE8 | [V]
| 0xF0 | 8 | [rdi+0xF0] read; [rsi+0xF0]=r14 | `0x5667b24  mov rbx,[rdi+0xF0]` `0x5667bb6  mov [rsi+0xF0],r14` | copy vector begin | [V]
| 0xF8 | 8 | [rsi+0xF8]=0; [rsi+0xF8]=rbx | `0x5667b1c  mov qword ptr [rdx+0x10],0` (rdx=rsi+0xE8) `0x5667bc0  mov [rsi+0xF8],rbx` | zero/copy vector end at +0xF8 | [V]
| 0x108 | 8 | [rdi+0x108]->[rsi+0x108] | `0x5667c00  mov rax,[rdi+0x108]` `0x5667c07  mov [rsi+0x108],rax` | copy qword field +0x108 | [V]
| 0x110 | 4 | [rdi+0x110]->[rsi+0x110] | `0x5667bf4  mov eax,[rdi+0x110]` `0x5667bfa  mov [rsi+0x110],eax` | copy dword field +0x110 | [V]

sub_5667c80 — per-pass body variant: calls sub_5667860 then clears +0x118/+0x128:
| 0x118 | 16 | [r14+0x118] write (5667c80); [rsi+0x118] read + zero (5667e70) | `0x5667ca5  movups [r14+0x118],xmm0` `0x5667e8e  mov rcx,[rsi+0x118]` `0x5667ed4  movups [rdi],xmm0` (rdi=rsi+0x118) | zero 16-byte block at +0x118; read qword +0x118 | [V]
| 0x128 | 8 | [r14+0x128] write (5667c80); zero (5667e70) | `0x5667cad  mov qword ptr [r14+0x128],0` `0x5667ed7  mov qword ptr [rdi+0x10],0` (rdi=rsi+0x118) | zero qword at +0x128 | [V]

sub_5667e70 — per-pass body variant: state check:
| 0x168 | 1 | [rcx+0x168] read | `0x5667e79  cmp byte ptr [rcx+0x168],1` | test pass byte +0x168 == 1 | [V]

sub_5668ac0 — per-pass body helper: FNV-1a style pass-name hash:
| 0x8 | 8 | [r8+0x8] read; [rdx+0x8] read | `0x5668ad2  mov r8,[r8+8]` `0x5668afd  mov rsi,[rdx+8]` | read qword a2+0x8; read qword a1+0x8 (hashed-string ptr) | [V]

## CLOSES?
NO — per-pass bodies not fully decoded. sub_5667860 is one complete per-pass body proven [V] (all field offsets 0x0..0xC4, 0xD4, 0xE4, 0x100, 0xE8, 0xF0, 0xF8, 0x108, 0x110), plus variant bodies sub_5667c80/sub_5667e70 and hash helper sub_5668ac0 [V]. The item requires the per-pass bodies for the 178 drawutils signatures; only a sample is decoded here, so the pending part is not completely proven. Blocking fact: remaining per-pass template bodies (sub_5667fe0, sub_56685c0 and the dozens of sub_566xxxx/sub_567xxxx/sub_568xxxx instantiations called from sub_55f1450 and sub_bbe2d50) are not yet decoded.

## TOOL REQUESTS
rdis.exe dis/callers | exe -> per-pass body listings | confirmed field-copy pattern and verbatim instr lines; no custom script needed.
