## NEXT
DONE
(Both functions phased instruction-complete; both field tables written; delegate.py check passed with 0 verify mismatches on final run.)

# Unit U-Wth — Weather clone (0x5AD5800) and Weather ctor (0x668DD20)

Instruction-complete dossier. Input data (read fully, quoted verbatim; tags: [V] = seen in the listing lines quoted here, [I] = inferred from those instructions):
- docs/data/listings/lightgame_weather_clone_5ad5800_5ad5939.txt — 70 instructions, 0x5ad5800..0x5ad5934
- docs/data/listings/lightgame_weather_ctor_668dd20_668e0f6.txt — 185 instructions, 0x668dd20..0x668e0f5

## Function 1: Weather clone [I] (name from the unit/listing filename lightgame_weather_clone_*)

Signature guess [I]: `void wth_clone(void* self /*rcx*/, void* dst /*rdx*/)` — rcx is used as `this` of a virtual call, rdx (dst) is only packed into an argument struct.
Register/argument map [V]:
- rsi = rcx (arg1/self) at 0x5ad581e; rdi = rdx (arg2/dst) at 0x5ad581b — see also 0x5ad5870 `mov [rbp+0x10],rdi`.
- rbp = [rsp+0x80] at 0x5ad580b; rbx = &stack buffer [rbp+0x30] at 0x5ad5851.

### Phases (35 + 12 + 23 = 70 instructions, all covered)

#### 0x5ad5800..0x5ad5894 (35 instructions)
Prologue: frame rbp=[rsp+0x80] with MSVC EH stamp [rbp+0x40]=0xFFFFFFFFFFFFFFFE; rdi=arg2, rsi=arg1. Thread-static init check: eax = [0x129CFEA8], ecx = [0x128767C8] (TLS index), rdx = gs:[0x58] (TLS array [I]), rcx = [rdx+rcx*8] (TEB slot, indexed operand — no constant offset); if the global epoch is greater than the per-thread copy [rcx+4], jump to the slow path 0x5ad58ba. Fast path: rcx = &0x129CFD70 (global config-ish object [I]), flag byte [rbp+0x28] = 0, buffer rbx = &[rbp+0x30] with its header [rbp+0x38] = 0 and [rbp-0x18] = 0, then call 0x39A7D40(rcx=&0x129CFD70, rdx=rbx=&[rbp+0x30], r8=&[rbp-0x50]) whose bool result (al) lands in [rbp+0x28]; pack {dst, tag 9} at [rbp+0x10]/[rbp+0x18] and call self's vtable slot [[rsi]+0x370] through the CFG-style dispatch pointer [0xF99FFA0] [I] with rcx=self, rdx=&pack; after the nop, if flag != 1 continue at the epilogue 0x5ad58ae, else fall into 0x5ad5896.

```
0x5ad5800  push rbp
0x5ad5801  push rsi
0x5ad5802  push rdi
0x5ad5803  push rbx
0x5ad5804  sub rsp,0xC8
0x5ad580b  lea rbp,[rsp+0x80]
0x5ad5813  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE
0x5ad581b  mov rdi,rdx
0x5ad581e  mov rsi,rcx
0x5ad5821  mov eax,[0x129CFEA8]
0x5ad5827  mov ecx,[0x128767C8]
0x5ad582d  mov rdx,gs:[0x58]
0x5ad5836  mov rcx,[rdx+rcx*8]
0x5ad583a  cmp eax,[rcx+4]
0x5ad5840  jg short 0x5AD58BA
0x5ad5842  lea rcx,[0x129CFD70]
0x5ad5849  mov [rbp+0x20],rcx
0x5ad584d  mov byte ptr [rbp+0x28],0
0x5ad5851  lea rbx,[rbp+0x30]
0x5ad5855  mov qword ptr [rbp+0x38],0
0x5ad585d  mov byte ptr [rbp-0x18],0
0x5ad5861  lea r8,[rbp-0x50]
0x5ad5865  mov rdx,rbx
0x5ad5868  call 0x39A7D40
0x5ad586d  mov [rbp+0x28],al
0x5ad5870  mov [rbp+0x10],rdi
0x5ad5874  mov byte ptr [rbp+0x18],9
0x5ad5878  mov rax,[rsi]
0x5ad587b  mov rax,[rax+0x370]
0x5ad5882  lea rdx,[rbp+0x10]
0x5ad5886  mov rcx,rsi
0x5ad5889  call qword ptr [0xF99FFA0]
0x5ad588f  nop
0x5ad5890  cmp byte ptr [rbp+0x28],1
0x5ad5894  jne short 0x5AD58AE
```

#### 0x5ad5896..0x5ad58b9 (12 instructions)
If the boolean returned by 0x39A7D40 was 1, call 0x77A2500 with rcx=0x1244FD00 (constant [I]), rdx=&stack buffer rbx, r8 = [rbp+0x20] (=&0x129CFD70) + 0x60; then epilogue: add rsp,0xC8, pop rbx/rdi/rsi/rbp, ret.

```
0x5ad5896  mov r8,[rbp+0x20]
0x5ad589a  add r8,0x60
0x5ad589e  lea rcx,[0x1244FD00]
0x5ad58a5  mov rdx,rbx
0x5ad58a8  call 0x77A2500
0x5ad58ad  nop
0x5ad58ae  add rsp,0xC8
0x5ad58b5  pop rbx
0x5ad58b6  pop rdi
0x5ad58b7  pop rsi
0x5ad58b8  pop rbp
0x5ad58b9  ret
```

#### 0x5ad58ba..0x5ad5934 (23 instructions)
Slow path of the init-once guard: call 0xE938CB0(rcx=&0x129CFEA8), then rejoin the fast path at 0x5ad5842 if [0x129CFEA8] != 0xFFFFFFFF; otherwise build a message record ([rbp]=&0xF52E07A, [rbp+8]=0x15 length [I], [rbp-0x10] = 16-byte constant from 0xF0BCBF8) and call 0x2FE330(rcx=&0x129CFD70, rdx=&[rbp-0x10], r8b=1, r9=rbp, [rsp+0x20]=0, [rsp+0x28]=&0xF276938) [I], then call 0xE935740(rcx=0x5AF27D0) and 0xE938D70(rcx=&0x129CFEA8) [I] and jmp 0x5ad5842 to replay the fast path.

```
0x5ad58ba  lea rcx,[0x129CFEA8]
0x5ad58c1  call 0xE938CB0
0x5ad58c6  cmp dword ptr [0x129CFEA8],0xFFFFFFFF
0x5ad58cd  jne 0x5AD5842
0x5ad58d3  lea rax,[0xF52E07A]
0x5ad58da  mov [rbp],rax
0x5ad58de  mov qword ptr [rbp+8],0x15
0x5ad58e6  movups xmm0,[0xF0BCBF8]
0x5ad58ed  movaps [rbp-0x10],xmm0
0x5ad58f1  lea rax,[0xF276938]
0x5ad58f8  mov [rsp+0x28],rax
0x5ad58fd  mov dword ptr [rsp+0x20],0
0x5ad5905  lea rcx,[0x129CFD70]
0x5ad590c  lea rdx,[rbp-0x10]
0x5ad5910  mov r9,rbp
0x5ad5913  mov r8b,1
0x5ad5916  call 0x2FE330
0x5ad591b  nop
0x5ad591c  lea rcx,[0x5AF27D0]
0x5ad5923  call 0xE935740
0x5ad5928  lea rcx,[0x129CFEA8]
0x5ad592f  call 0xE938D70
0x5ad5934  jmp 0x5AD5842
```

### Callees (function 1)
- 0x39A7D40 — called with rcx=&0x129CFD70, rdx=&[rbp+0x30], r8=&[rbp-0x50]; returns bool in al ([V] 0x5ad586d). Purpose not shown. [I]
- [0xF99FFA0] — indirect call target loaded from data; the surrounding pattern (rax = [[rsi]+0x370]) matches the MSVC Control Flow Guard dispatch import `__guard_dispatch_icall_fptr` [I].
- 0x77A2500 — called only when al==1, args (0x1244FD00, stack buffer, 0x129CFD70+0x60). [I]
- 0xE938CB0 — arg = &0x129CFEA8. [I] thread-safe-init "enter" style helper.
- 0x2FE330 — arg set: {0x129CFD70, &[rbp-0x10], r8b=1, r9=rbp, stack arg 0, stack arg &0xF276938}; message {ptr 0xF52E07A, len 0x15} built just before. [I]
- 0xE935740 — arg rcx=0x5AF27D0. [I]
- 0xE938D70 — arg rcx=&0x129CFEA8. [I]

### OPEN questions (function 1)
- What are globals 0x129CFD70, 0x129CFEA8, 0x128767C8, 0x5AF27D0 and the data at 0xF0BCBF8? [UNVERIFIED: 0x5ad5842 identity of the four globals/constants]
- What string is at 0xF52E07A (len 0x15 per [rbp+8]=0x15) and what is 0x1244FD00 / 0xF276938? [UNVERIFIED: 0x5ad58d3 string contents]
- Which virtual method is vtable slot 0x370? [UNVERIFIED: 0x5ad587b method identity]

## Function 2: Weather ctor [I] (name from the unit/listing filename lightgame_weather_ctor_*)

Signature guess [I, from register use + Win64 stack layout with rbp=[rsp+0x30] (stack args start at [rbp+0x30]=arg5)]:
`WeatherData* wth_ctor(WeatherData* this /*rcx*/, u64 a2 /*rdx*/, u32 a3 /*r8d*/, u32 a4 /*r9d*/, ..., /* [rbp+0x50] arg9 = ptr to 16 floats */ /* [rbp+0x58] arg10 = ptr {u64 count, ptr entries, stride 0x10} */ /* [rbp+0x60] arg11 dword -> +0x80 */ /* [rbp+0x68] arg12 dword -> +0x84 */ /* [rbp+0x70] arg13 = ptr component base */ /* [rbp+0x78] arg14 low word -> +0x128 */ /* [rbp+0x80] arg15 = ptr to 8 floats */)` — returns rax=this ([V] 0x668e0e4 `mov rax,rsi`).
Register/argument map [V]/[I]:
- rcx = object `this` at entry; rsi = same object from 0x668ddf1 on; rdi = [rbp+0x58] (arg10) at 0x668dd35; rax = [rbp+0x50] (arg9, float ptr) at 0x668dd39.
- rcx reloaded as [rbp+0x70] (arg13) at 0x668de52; rdx = [rbp+0x80] (arg15) at 0x668de47; later rdx/rcx are re-bound to descriptor pointers (see the `mov rdx,[rdx+0x40]` rows in the field table).

### Phases (20 + 24 + 24 + 39 + 18 + 40 + 20 = 185 instructions, all covered)

#### 0x668dd20..0x668dd6a (20 instructions)
Prologue: rbp=[rsp+0x30], EH stamp [rbp]=0xFFFFFFFFFFFFFFFE; rdi=[rbp+0x58] (arg10), rax=[rbp+0x50] (arg9). Store args into the object: [rcx]=rdx (qword), [rcx+8]=r8d (dword), [rcx+0xC]=r9d (dword); copy the first 4 floats [rax+0x00..0x0C] to [rcx+0x10..0x1C] (one movss each).

```
0x668dd20  push rbp
0x668dd21  push rsi
0x668dd22  push rdi
0x668dd23  push rbx
0x668dd24  sub rsp,0x38
0x668dd28  lea rbp,[rsp+0x30]
0x668dd2d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x668dd35  mov rdi,[rbp+0x58]
0x668dd39  mov rax,[rbp+0x50]
0x668dd3d  mov [rcx],rdx
0x668dd40  mov [rcx+8],r8d
0x668dd44  mov [rcx+0xC],r9d
0x668dd48  movss xmm0,[rax]
0x668dd4c  movss [rcx+0x10],xmm0
0x668dd51  movss xmm0,[rax+4]
0x668dd56  movss [rcx+0x14],xmm0
0x668dd5b  movss xmm0,[rax+8]
0x668dd60  movss [rcx+0x18],xmm0
0x668dd65  movss xmm0,[rax+0xC]
0x668dd6a  movss [rcx+0x1C],xmm0
```

#### 0x668dd6f..0x668dde2 (24 instructions)
Copy the remaining 12 floats straight from [rax+0x10..0x3C] (arg9 block) to [rcx+0x20..0x4C] (this+0x20..this+0x4C), one movss per field.

```
0x668dd6f  movss xmm0,[rax+0x10]
0x668dd74  movss [rcx+0x20],xmm0
0x668dd79  movss xmm0,[rax+0x14]
0x668dd7e  movss [rcx+0x24],xmm0
0x668dd83  movss xmm0,[rax+0x18]
0x668dd88  movss [rcx+0x28],xmm0
0x668dd8d  movss xmm0,[rax+0x1C]
0x668dd92  movss [rcx+0x2C],xmm0
0x668dd97  movss xmm0,[rax+0x20]
0x668dd9c  movss [rcx+0x30],xmm0
0x668dda1  movss xmm0,[rax+0x24]
0x668dda6  movss [rcx+0x34],xmm0
0x668ddab  movss xmm0,[rax+0x28]
0x668ddb0  movss [rcx+0x38],xmm0
0x668ddb5  movss xmm0,[rax+0x2C]
0x668ddba  movss [rcx+0x3C],xmm0
0x668ddbf  movss xmm0,[rax+0x30]
0x668ddc4  movss [rcx+0x40],xmm0
0x668ddc9  movss xmm0,[rax+0x34]
0x668ddce  movss [rcx+0x44],xmm0
0x668ddd3  movss xmm0,[rax+0x38]
0x668ddd8  movss [rcx+0x48],xmm0
0x668dddd  movss xmm0,[rax+0x3C]
0x668dde2  movss [rcx+0x4C],xmm0
```

#### 0x668dde7..0x668de46 (24 instructions)
Validate the count at [rdi] (arg10): fail to 0x668e0f0 if [rdi]==0, if [rdi]<=1, or if [rdi]<=2 — so at least 3 entries are required [I]; write the three 0x10-stride entries at [rdi+8]+0x00 / +0x10 / +0x20 into this+0x50, this+0x60, this+0x70 by three calls to 0x4DFB570 (rbx = destination each time; saved to [rbp-0x10] and [rbp-8] between calls).

```
0x668dde7  cmp qword ptr [rdi],0
0x668ddeb  je 0x668E0F0
0x668ddf1  mov rsi,rcx
0x668ddf4  lea rbx,[rcx+0x50]
0x668ddf8  mov rdx,[rdi+8]
0x668ddfc  mov rcx,rbx
0x668ddff  call 0x4DFB570
0x668de04  cmp qword ptr [rdi],1
0x668de08  jbe 0x668E0F0
0x668de0e  mov [rbp-0x10],rbx
0x668de12  lea rbx,[rsi+0x60]
0x668de16  mov rdx,[rdi+8]
0x668de1a  add rdx,0x10
0x668de1e  mov rcx,rbx
0x668de21  call 0x4DFB570
0x668de26  nop
0x668de27  cmp qword ptr [rdi],2
0x668de2b  jbe 0x668E0F0
0x668de31  mov [rbp-8],rbx
0x668de35  lea rcx,[rsi+0x70]
0x668de39  mov rdx,[rdi+8]
0x668de3d  add rdx,0x20
0x668de41  call 0x4DFB570
0x668de46  nop
```

#### 0x668de47..0x668df2a (39 instructions)
Reload the trailing stack args: rdx=[rbp+0x80] (arg15), eax=word [rbp+0x78] (arg14 low half, kept for the store at 0x668e0dd), rcx=[rbp+0x70] (arg13 component base); store dwords [rbp+0x60] -> [rsi+0x80] and [rbp+0x68] -> [rsi+0x84]; then copy floats out of component descriptors, each found as base=[rcx+N], data=[base+0x40]: 4 floats from [rcx+0x70] -> this+0x88..0x94; 2 floats from [rcx+0x78] -> this+0x98,0x9C; 1 float from [rcx+0x80] -> this+0xA0; 1 float from [rcx+0x88] -> this+0xA4; 4 floats from [rcx+0x190] -> this+0xA8,0xAC,0xB0 (4th of the block continues in the next phase).

```
0x668de47  mov rdx,[rbp+0x80]
0x668de4e  movzx eax,word ptr [rbp+0x78]
0x668de52  mov rcx,[rbp+0x70]
0x668de56  mov r8d,[rbp+0x68]
0x668de5a  mov r9d,[rbp+0x60]
0x668de5e  mov [rsi+0x80],r9d
0x668de65  mov [rsi+0x84],r8d
0x668de6c  mov r8,[rcx+0x70]
0x668de70  mov r8,[r8+0x40]
0x668de74  movss xmm0,[r8]
0x668de79  movss [rsi+0x88],xmm0
0x668de81  movss xmm0,[r8+4]
0x668de87  movss [rsi+0x8C],xmm0
0x668de8f  movss xmm0,[r8+8]
0x668de95  movss [rsi+0x90],xmm0
0x668de9d  movss xmm0,[r8+0xC]
0x668dea3  movss [rsi+0x94],xmm0
0x668deab  mov r8,[rcx+0x78]
0x668deaf  mov r8,[r8+0x40]
0x668deb3  movss xmm0,[r8]
0x668deb8  movss [rsi+0x98],xmm0
0x668dec0  movss xmm0,[r8+4]
0x668dec6  movss [rsi+0x9C],xmm0
0x668dece  mov r8,[rcx+0x80]
0x668ded5  mov r8,[r8+0x40]
0x668ded9  movss xmm0,[r8]
0x668dede  movss [rsi+0xA0],xmm0
0x668dee6  mov r8,[rcx+0x88]
0x668deed  mov r8,[r8+0x40]
0x668def1  movss xmm0,[r8]
0x668def6  movss [rsi+0xA4],xmm0
0x668defe  mov r8,[rcx+0x190]
0x668df05  mov r8,[r8+0x40]
0x668df09  movss xmm0,[r8]
0x668df0e  movss [rsi+0xA8],xmm0
0x668df16  movss xmm0,[r8+4]
0x668df1c  movss [rsi+0xAC],xmm0
0x668df24  movss xmm0,[r8+8]
0x668df2a  movss [rsi+0xB0],xmm0
```

#### 0x668df32..0x668df9f (18 instructions)
Finish the [rcx+0x190] block: float [r8+0xC] -> [rsi+0xB4]; then copy 8 floats from rdx (= [rbp+0x80], arg15): [rdx+0x10..0x1C] -> this+0xB8..0xC4, then [rdx+0x00..0xC] -> this+0xC8..0xD4.

```
0x668df32  movss xmm0,[r8+0xC]
0x668df38  movss [rsi+0xB4],xmm0
0x668df40  movss xmm0,[rdx+0x10]
0x668df45  movss [rsi+0xB8],xmm0
0x668df4d  movss xmm0,[rdx+0x14]
0x668df52  movss [rsi+0xBC],xmm0
0x668df5a  movss xmm0,[rdx+0x18]
0x668df5f  movss [rsi+0xC0],xmm0
0x668df67  movss xmm0,[rdx+0x1C]
0x668df6c  movss [rsi+0xC4],xmm0
0x668df74  movss xmm0,[rdx]
0x668df78  movss [rsi+0xC8],xmm0
0x668df80  movss xmm0,[rdx+4]
0x668df85  movss [rsi+0xCC],xmm0
0x668df8d  movss xmm0,[rdx+8]
0x668df92  movss [rsi+0xD0],xmm0
0x668df9a  movss xmm0,[rdx+0xC]
0x668df9f  movss [rsi+0xD4],xmm0
```

#### 0x668dfa7..0x668e097 (40 instructions)
Four more 4-float blocks, each selected in the arg13 base by `mov rdx,[rcx+N]` then `mov rdx,[rdx+0x40]`: [rcx+0x1B8] -> this+0xD8..0xE4; [rcx+0x1A8] -> this+0xE8..0xF4; [rcx+0x1C0] -> this+0xF8..0x104; [rcx+0x198] -> this+0x108..0x114.

```
0x668dfa7  mov rdx,[rcx+0x1B8]
0x668dfae  mov rdx,[rdx+0x40]
0x668dfb2  movss xmm0,[rdx]
0x668dfb6  movss [rsi+0xD8],xmm0
0x668dfbe  movss xmm0,[rdx+4]
0x668dfc3  movss [rsi+0xDC],xmm0
0x668dfcb  movss xmm0,[rdx+8]
0x668dfd0  movss [rsi+0xE0],xmm0
0x668dfd8  movss xmm0,[rdx+0xC]
0x668dfdd  movss [rsi+0xE4],xmm0
0x668dfe5  mov rdx,[rcx+0x1A8]
0x668dfec  mov rdx,[rdx+0x40]
0x668dff0  movss xmm0,[rdx]
0x668dff4  movss [rsi+0xE8],xmm0
0x668dffc  movss xmm0,[rdx+4]
0x668e001  movss [rsi+0xEC],xmm0
0x668e009  movss xmm0,[rdx+8]
0x668e00e  movss [rsi+0xF0],xmm0
0x668e016  movss xmm0,[rdx+0xC]
0x668e01b  movss [rsi+0xF4],xmm0
0x668e023  mov rdx,[rcx+0x1C0]
0x668e02a  mov rdx,[rdx+0x40]
0x668e02e  movss xmm0,[rdx]
0x668e032  movss [rsi+0xF8],xmm0
0x668e03a  movss xmm0,[rdx+4]
0x668e03f  movss [rsi+0xFC],xmm0
0x668e047  movss xmm0,[rdx+8]
0x668e04c  movss [rsi+0x100],xmm0
0x668e054  movss xmm0,[rdx+0xC]
0x668e059  movss [rsi+0x104],xmm0
0x668e061  mov rdx,[rcx+0x198]
0x668e068  mov rdx,[rdx+0x40]
0x668e06c  movss xmm0,[rdx]
0x668e070  movss [rsi+0x108],xmm0
0x668e078  movss xmm0,[rdx+4]
0x668e07d  movss [rsi+0x10C],xmm0
0x668e085  movss xmm0,[rdx+8]
0x668e08a  movss [rsi+0x110],xmm0
0x668e092  movss xmm0,[rdx+0xC]
0x668e097  movss [rsi+0x114],xmm0
```

#### 0x668e09f..0x668e0f5 (20 instructions)
Last descriptor block, carried in rcx: `mov rcx,[rcx+0x1B0]` then `mov rcx,[rcx+0x40]`, copy 4 floats [rcx+0x00..0xC] -> this+0x118..0x124; store the deferred stack word [rsi+0x128]=ax (loaded at 0x668de4e); return rax=rsi (this) with epilogue; the failure target 0x668e0f0 calls 0x78ED0 then int3 (trap/abort path [I]).

```
0x668e09f  mov rcx,[rcx+0x1B0]
0x668e0a6  mov rcx,[rcx+0x40]
0x668e0aa  movss xmm0,[rcx]
0x668e0ae  movss [rsi+0x118],xmm0
0x668e0b6  movss xmm0,[rcx+4]
0x668e0bb  movss [rsi+0x11C],xmm0
0x668e0c3  movss xmm0,[rcx+8]
0x668e0c8  movss [rsi+0x120],xmm0
0x668e0d0  movss xmm0,[rcx+0xC]
0x668e0d5  movss [rsi+0x124],xmm0
0x668e0dd  mov [rsi+0x128],ax
0x668e0e4  mov rax,rsi
0x668e0e7  add rsp,0x38
0x668e0eb  pop rbx
0x668e0ec  pop rdi
0x668e0ed  pop rsi
0x668e0ee  pop rbp
0x668e0ef  ret
0x668e0f0  call 0x78ED0
0x668e0f5  int3
```

### Callees (function 2)
- 0x4DFB570 x3 — copy-initializer for the 0x10-stride entries of arg10 into this+0x50/0x60/0x70 ([V] call sites 0x668ddff, 0x668de21, 0x668de41). Purpose beyond the copy not shown. [I]
- 0x78ED0 — reached only from the three failing count guards (0x668ddeb / 0x668de08 / 0x668de2b all target 0x668e0f0); followed by int3 — abort/trap style. [I]

### OPEN questions (function 2)
- Identity of copy helper 0x4DFB570 and trap 0x78ED0. [UNVERIFIED: 0x668ddff callee names]
- Which object/layout arg13 (=[rbp+0x70]) points to: its slots 0x70/0x78/0x80/0x88/0x190/0x198/0x1A8/0x1B0/0x1B8/0x1C0 all yield pointers whose +0x40 is a float-array base. [UNVERIFIED: 0x668de6c component type]
- Meaning of the qword [rcx]=rdx at entry (id? pointer?) and of the two dwords +8/+0xC. [UNVERIFIED: 0x668dd3d field semantics]

## Field tables

Rules applied: every `[reg+off]` operand of both listings gets a row, one row per distinct base+offset, with ALL of its sites listed (two spaces after the address, copied verbatim from the input data). Size comes from the instruction (movups/movaps 16, qword 8, dword/movss 4, word 2, byte 1; "a/b" = sizes of the listed sites). Meaning only where an instruction sequence shows it ([I], inferred from those instructions), else '-'. Plain `[reg]` is counted as offset 0x00. Operands without a constant offset are excluded from the table and noted here: `[rdx+rcx*8]` at 0x5ad5836 (indexed TLS array element).

### Function 1 (clone, 0x5ad5800) — 16 rows

| offset | size | R/W | verbatim instruction line(s) | meaning |
|---|---|---|---|---|
| rbp+0x40 | 8 | W | `0x5ad5813  mov qword ptr [rbp+0x40],0xFFFFFFFFFFFFFFFE` | [I] MSVC EH/security stamp init (-2) |
| gs+0x58 | 8 | R | `0x5ad582d  mov rdx,gs:[0x58]` | [I] Win64 TEB _tls_array, indexed by the TLS index from [0x128767C8] (0x5ad5827, used at 0x5ad5836) |
| rcx+4 | 4 | R | `0x5ad583a  cmp eax,[rcx+4]` | [I] per-thread copy of the epoch global 0x129CFEA8, checked against it (0x5ad5821) in the init-once test |
| rbp+0x20 | 8 | W,R | `0x5ad5849  mov [rbp+0x20],rcx`<br>`0x5ad5896  mov r8,[rbp+0x20]` | [I] holds &0x129CFD70 (stored at 0x5ad5842/0x5ad5905) for the r8 base +0x60 |
| rbp+0x28 | 1 | W,R | `0x5ad584d  mov byte ptr [rbp+0x28],0`<br>`0x5ad586d  mov [rbp+0x28],al`<br>`0x5ad5890  cmp byte ptr [rbp+0x28],1` | [I] bool result of 0x39A7D40; gates the 0x77A2500 call |
| rbp+0x38 | 8 | W | `0x5ad5855  mov qword ptr [rbp+0x38],0` | [I] header of the stack buffer rbx=[rbp+0x30] passed to 0x39A7D40 |
| rbp-0x18 | 1 | W | `0x5ad585d  mov byte ptr [rbp-0x18],0` | - |
| rbp+0x10 | 8 | W | `0x5ad5870  mov [rbp+0x10],rdi` | [I] field 0 of the arg pack {dst=rdx} passed to vtable slot 0x370 |
| rbp+0x18 | 1 | W | `0x5ad5874  mov byte ptr [rbp+0x18],9` | [I] field 8 of the same pack = 9 |
| rsi+0x00 | 8 | R | `0x5ad5878  mov rax,[rsi]` | [I] vtable pointer of arg1 (self) |
| rax+0x370 | 8 | R | `0x5ad587b  mov rax,[rax+0x370]` | [I] vtable slot 0x370, invoked via [0xF99FFA0] (0x5ad5889) |
| rbp+0x08 | 8 | W | `0x5ad58de  mov qword ptr [rbp+8],0x15` | [I] message length 0x15 |
| rsp+0x28 | 8 | W | `0x5ad58f8  mov [rsp+0x28],rax` | [I] stack arg = &0xF276938 for 0x2FE330 |
| rsp+0x20 | 4 | W | `0x5ad58fd  mov dword ptr [rsp+0x20],0` | [I] stack arg = 0 for 0x2FE330 |

### Function 2 (ctor, 0x668dd20) — 116 rows

Note: rsi = rcx = the object being constructed from 0x668ddf1 on; rcx is reloaded as [rbp+0x70] (arg13) at 0x668de52; rcx/rdx are re-bound to descriptor pointers mid-function (rows below combine both uses and say so).

| offset | size | R/W | verbatim instruction line(s) | meaning |
|---|---|---|---|---|
| rbp-0x08 | 8 | W | `0x668de31  mov [rbp-8],rbx` | [I] saves rbx (= rsi+0x70, shown by 0x668de35) across the guard |
| rbp+0x50 | 8 | R | `0x668dd39  mov rax,[rbp+0x50]` | [I] stack arg 9: ptr to the 16-float block copied to this+0x10..0x4C |
| rbp+0x58 | 8 | R | `0x668dd35  mov rdi,[rbp+0x58]` | [I] stack arg 10: {u64 count, ptr to 0x10-stride entries} |
| rbp+0x60 | 4 | R | `0x668de5a  mov r9d,[rbp+0x60]` | [I] stack arg 11 dword, stored to this+0x80 |
| rbp+0x68 | 4 | R | `0x668de56  mov r8d,[rbp+0x68]` | [I] stack arg 12 dword, stored to this+0x84 |
| rbp+0x70 | 8 | R | `0x668de52  mov rcx,[rbp+0x70]` | [I] stack arg 13: descriptor base, its slots 0x70..0x1C0 are dereferenced |
| rbp+0x78 | 2 | R | `0x668de4e  movzx eax,word ptr [rbp+0x78]` | [I] stack arg 14 low word, kept in ax until [rsi+0x128] |
| rbp+0x80 | 8 | R | `0x668de47  mov rdx,[rbp+0x80]` | [I] stack arg 15: ptr to 8 floats (rdx+0x10..0x1C and rdx+0x00..0xC) |
| rcx+0x00 | 8 | W | `0x668dd3d  mov [rcx],rdx` | [I] object field from arg2 (qword store) |
| rcx+0x00 (descriptor data) | 4 | R | `0x668e0aa  movss xmm0,[rcx]` | [I] float 0 of the last descriptor block; rcx here = the [rcx+0x1B0]+0x40 chain (see 0x668e09f / 0x668e0a6 row) |
| rcx+0x04 | 4 | R | `0x668e0b6  movss xmm0,[rcx+4]` | [I] float 1 of the last descriptor block |
| rcx+0x08 | 4 | W,R | `0x668dd40  mov [rcx+8],r8d`<br>`0x668e0c3  movss xmm0,[rcx+8]` | [I] W: object field from arg3; R: float 2 of the last descriptor block |
| rcx+0x0C | 4 | W,R | `0x668dd44  mov [rcx+0xC],r9d`<br>`0x668e0d0  movss xmm0,[rcx+0xC]` | [I] W: object field from arg4; R: float 3 of the last descriptor block |
| rcx+0x10 | 4 | W | `0x668dd4c  movss [rcx+0x10],xmm0` | [I] float 0 of block from [rax+0x00] (arg9) |
| rcx+0x14 | 4 | W | `0x668dd56  movss [rcx+0x14],xmm0` | [I] float 1 from [rax+0x04] |
| rcx+0x18 | 4 | W | `0x668dd60  movss [rcx+0x18],xmm0` | [I] float 2 from [rax+0x08] |
| rcx+0x1C | 4 | W | `0x668dd6a  movss [rcx+0x1C],xmm0` | [I] float 3 from [rax+0x0C] |
| rcx+0x20 | 4 | W | `0x668dd74  movss [rcx+0x20],xmm0` | [I] float 4 from [rax+0x10] |
| rcx+0x24 | 4 | W | `0x668dd7e  movss [rcx+0x24],xmm0` | [I] float 5 from [rax+0x14] |
| rcx+0x28 | 4 | W | `0x668dd88  movss [rcx+0x28],xmm0` | [I] float 6 from [rax+0x18] |
| rcx+0x2C | 4 | W | `0x668dd92  movss [rcx+0x2C],xmm0` | [I] float 7 from [rax+0x1C] |
| rcx+0x30 | 4 | W | `0x668dd9c  movss [rcx+0x30],xmm0` | [I] float 8 from [rax+0x20] |
| rcx+0x34 | 4 | W | `0x668dda6  movss [rcx+0x34],xmm0` | [I] float 9 from [rax+0x24] |
| rcx+0x38 | 4 | W | `0x668ddb0  movss [rcx+0x38],xmm0` | [I] float 10 from [rax+0x28] |
| rcx+0x3C | 4 | W | `0x668ddba  movss [rcx+0x3C],xmm0` | [I] float 11 from [rax+0x2C] |
| rcx+0x40 | 4/8 | W,R | `0x668ddc4  movss [rcx+0x40],xmm0`<br>`0x668e0a6  mov rcx,[rcx+0x40]` | [I] W: float 12 from [rax+0x30]; R: descriptor data pointer of [[rcx+0x1B0]] (re-bound base) |
| rcx+0x44 | 4 | W | `0x668ddce  movss [rcx+0x44],xmm0` | [I] float 13 from [rax+0x34] |
| rcx+0x48 | 4 | W | `0x668ddd8  movss [rcx+0x48],xmm0` | [I] float 14 from [rax+0x38] |
| rcx+0x4C | 4 | W | `0x668dde2  movss [rcx+0x4C],xmm0` | [I] float 15 from [rax+0x3C] |
| rcx+0x70 | 8 | R | `0x668de6c  mov r8,[rcx+0x70]` | [I] descriptor slot of arg13 base (deref +0x40 next) |
| rcx+0x78 | 8 | R | `0x668deab  mov r8,[rcx+0x78]` | [I] descriptor slot of arg13 base |
| rcx+0x80 | 8 | R | `0x668dece  mov r8,[rcx+0x80]` | [I] descriptor slot of arg13 base |
| rcx+0x88 | 8 | R | `0x668dee6  mov r8,[rcx+0x88]` | [I] descriptor slot of arg13 base |
| rcx+0x190 | 8 | R | `0x668defe  mov r8,[rcx+0x190]` | [I] descriptor slot of arg13 base |
| rcx+0x198 | 8 | R | `0x668e061  mov rdx,[rcx+0x198]` | [I] descriptor slot of arg13 base |
| rcx+0x1A8 | 8 | R | `0x668dfe5  mov rdx,[rcx+0x1A8]` | [I] descriptor slot of arg13 base |
| rcx+0x1B0 | 8 | R | `0x668e09f  mov rcx,[rcx+0x1B0]` | [I] descriptor slot of arg13 base (loaded into rcx itself) |
| rcx+0x1B8 | 8 | R | `0x668dfa7  mov rdx,[rcx+0x1B8]` | [I] descriptor slot of arg13 base |
| rcx+0x1C0 | 8 | R | `0x668e023  mov rdx,[rcx+0x1C0]` | [I] descriptor slot of arg13 base |
| rsi+0x80 | 4 | W | `0x668de5e  mov [rsi+0x80],r9d` | [I] = dword [rbp+0x60] (arg11) |
| rsi+0x84 | 4 | W | `0x668de65  mov [rsi+0x84],r8d` | [I] = dword [rbp+0x68] (arg12) |
| rsi+0x88 | 4 | W | `0x668de79  movss [rsi+0x88],xmm0` | [I] = float [[[rcx+0x70]+0x40]+0x00] |
| rsi+0x8C | 4 | W | `0x668de87  movss [rsi+0x8C],xmm0` | [I] = float [[[rcx+0x70]+0x40]+0x04] |
| rsi+0x90 | 4 | W | `0x668de95  movss [rsi+0x90],xmm0` | [I] = float [[[rcx+0x70]+0x40]+0x08] |
| rsi+0x94 | 4 | W | `0x668dea3  movss [rsi+0x94],xmm0` | [I] = float [[[rcx+0x70]+0x40]+0x0C] |
| rsi+0x98 | 4 | W | `0x668deb8  movss [rsi+0x98],xmm0` | [I] = float [[[rcx+0x78]+0x40]+0x00] |
| rsi+0x9C | 4 | W | `0x668dec6  movss [rsi+0x9C],xmm0` | [I] = float [[[rcx+0x78]+0x40]+0x04] |
| rsi+0xA0 | 4 | W | `0x668dede  movss [rsi+0xA0],xmm0` | [I] = float [[[rcx+0x80]+0x40]+0x00] |
| rsi+0xA4 | 4 | W | `0x668def6  movss [rsi+0xA4],xmm0` | [I] = float [[[rcx+0x88]+0x40]+0x00] |
| rsi+0xA8 | 4 | W | `0x668df0e  movss [rsi+0xA8],xmm0` | [I] = float [[[rcx+0x190]+0x40]+0x00] |
| rsi+0xAC | 4 | W | `0x668df1c  movss [rsi+0xAC],xmm0` | [I] = float [[[rcx+0x190]+0x40]+0x04] |
| rsi+0xB0 | 4 | W | `0x668df2a  movss [rsi+0xB0],xmm0` | [I] = float [[[rcx+0x190]+0x40]+0x08] |
| rsi+0xB4 | 4 | W | `0x668df38  movss [rsi+0xB4],xmm0` | [I] = float [[[rcx+0x190]+0x40]+0x0C] |
| rsi+0xB8 | 4 | W | `0x668df45  movss [rsi+0xB8],xmm0` | [I] = float [[rbp+0x80]+0x10] (arg15) |
| rsi+0xBC | 4 | W | `0x668df52  movss [rsi+0xBC],xmm0` | [I] = float [[rbp+0x80]+0x14] |
| rsi+0xC0 | 4 | W | `0x668df5f  movss [rsi+0xC0],xmm0` | [I] = float [[rbp+0x80]+0x18] |
| rsi+0xC4 | 4 | W | `0x668df6c  movss [rsi+0xC4],xmm0` | [I] = float [[rbp+0x80]+0x1C] |
| rsi+0xC8 | 4 | W | `0x668df78  movss [rsi+0xC8],xmm0` | [I] = float [[rbp+0x80]+0x00] |
| rsi+0xCC | 4 | W | `0x668df85  movss [rsi+0xCC],xmm0` | [I] = float [[rbp+0x80]+0x04] |
| rsi+0xD0 | 4 | W | `0x668df92  movss [rsi+0xD0],xmm0` | [I] = float [[rbp+0x80]+0x08] |
| rsi+0xD4 | 4 | W | `0x668df9f  movss [rsi+0xD4],xmm0` | [I] = float [[rbp+0x80]+0x0C] |
| rsi+0xD8 | 4 | W | `0x668dfb6  movss [rsi+0xD8],xmm0` | [I] = float [[[rcx+0x1B8]+0x40]+0x00] |
| rsi+0xDC | 4 | W | `0x668dfc3  movss [rsi+0xDC],xmm0` | [I] = float [[[rcx+0x1B8]+0x40]+0x04] |
| rsi+0xE0 | 4 | W | `0x668dfd0  movss [rsi+0xE0],xmm0` | [I] = float [[[rcx+0x1B8]+0x40]+0x08] |
| rsi+0xE4 | 4 | W | `0x668dfdd  movss [rsi+0xE4],xmm0` | [I] = float [[[rcx+0x1B8]+0x40]+0x0C] |
| rsi+0xE8 | 4 | W | `0x668dff4  movss [rsi+0xE8],xmm0` | [I] = float [[[rcx+0x1A8]+0x40]+0x00] |
| rsi+0xEC | 4 | W | `0x668e001  movss [rsi+0xEC],xmm0` | [I] = float [[[rcx+0x1A8]+0x40]+0x04] |
| rsi+0xF0 | 4 | W | `0x668e00e  movss [rsi+0xF0],xmm0` | [I] = float [[[rcx+0x1A8]+0x40]+0x08] |
| rsi+0xF4 | 4 | W | `0x668e01b  movss [rsi+0xF4],xmm0` | [I] = float [[[rcx+0x1A8]+0x40]+0x0C] |
| rsi+0xF8 | 4 | W | `0x668e032  movss [rsi+0xF8],xmm0` | [I] = float [[[rcx+0x1C0]+0x40]+0x00] |
| rsi+0xFC | 4 | W | `0x668e03f  movss [rsi+0xFC],xmm0` | [I] = float [[[rcx+0x1C0]+0x40]+0x04] |
| rsi+0x100 | 4 | W | `0x668e04c  movss [rsi+0x100],xmm0` | [I] = float [[[rcx+0x1C0]+0x40]+0x08] |
| rsi+0x104 | 4 | W | `0x668e059  movss [rsi+0x104],xmm0` | [I] = float [[[rcx+0x1C0]+0x40]+0x0C] |
| rsi+0x108 | 4 | W | `0x668e070  movss [rsi+0x108],xmm0` | [I] = float [[[rcx+0x198]+0x40]+0x00] |
| rsi+0x10C | 4 | W | `0x668e07d  movss [rsi+0x10C],xmm0` | [I] = float [[[rcx+0x198]+0x40]+0x04] |
| rsi+0x110 | 4 | W | `0x668e08a  movss [rsi+0x110],xmm0` | [I] = float [[[rcx+0x198]+0x40]+0x08] |
| rsi+0x114 | 4 | W | `0x668e097  movss [rsi+0x114],xmm0` | [I] = float [[[rcx+0x198]+0x40]+0x0C] |
| rsi+0x118 | 4 | W | `0x668e0ae  movss [rsi+0x118],xmm0` | [I] = float [rcx+0x00] of the [[rcx+0x1B0]+0x40] block |
| rsi+0x11C | 4 | W | `0x668e0bb  movss [rsi+0x11C],xmm0` | [I] = float [rcx+0x04] of that block |
| rsi+0x120 | 4 | W | `0x668e0c8  movss [rsi+0x120],xmm0` | [I] = float [rcx+0x08] of that block |
| rsi+0x124 | 4 | W | `0x668e0d5  movss [rsi+0x124],xmm0` | [I] = float [rcx+0x0C] of that block |
| rsi+0x128 | 2 | W | `0x668e0dd  mov [rsi+0x128],ax` | [I] = word [rbp+0x78] (arg14, kept in ax since 0x668de4e) |
| rax+0x00 | 4 | R | `0x668dd48  movss xmm0,[rax]` | [I] arg9 float block ([rbp+0x50]) |
| rax+0x04 | 4 | R | `0x668dd51  movss xmm0,[rax+4]` | [I] arg9 float block |
| rax+0x08 | 4 | R | `0x668dd5b  movss xmm0,[rax+8]` | [I] arg9 float block |
| rax+0x0C | 4 | R | `0x668dd65  movss xmm0,[rax+0xC]` | [I] arg9 float block |
| rax+0x10 | 4 | R | `0x668dd6f  movss xmm0,[rax+0x10]` | [I] arg9 float block |
| rax+0x14 | 4 | R | `0x668dd79  movss xmm0,[rax+0x14]` | [I] arg9 float block |
| rax+0x18 | 4 | R | `0x668dd83  movss xmm0,[rax+0x18]` | [I] arg9 float block |
| rax+0x1C | 4 | R | `0x668dd8d  movss xmm0,[rax+0x1C]` | [I] arg9 float block |
| rax+0x20 | 4 | R | `0x668dd97  movss xmm0,[rax+0x20]` | [I] arg9 float block |
| rax+0x24 | 4 | R | `0x668dda1  movss xmm0,[rax+0x24]` | [I] arg9 float block |
| rax+0x28 | 4 | R | `0x668ddab  movss xmm0,[rax+0x28]` | [I] arg9 float block |
| rax+0x2C | 4 | R | `0x668ddb5  movss xmm0,[rax+0x2C]` | [I] arg9 float block |
| rax+0x30 | 4 | R | `0x668ddbf  movss xmm0,[rax+0x30]` | [I] arg9 float block |
| rax+0x34 | 4 | R | `0x668ddc9  movss xmm0,[rax+0x34]` | [I] arg9 float block |
| rax+0x38 | 4 | R | `0x668ddd3  movss xmm0,[rax+0x38]` | [I] arg9 float block |
| rax+0x3C | 4 | R | `0x668dddd  movss xmm0,[rax+0x3C]` | [I] arg9 float block |
| rdi+0x00 | 8 | R | `0x668dde7  cmp qword ptr [rdi],0`<br>`0x668de04  cmp qword ptr [rdi],1`<br>`0x668de27  cmp qword ptr [rdi],2` | [I] count field of arg10; all three guards must pass (>= 3 entries) else 0x668e0f0 |
| rdi+0x08 | 8 | R | `0x668ddf8  mov rdx,[rdi+8]`<br>`0x668de16  mov rdx,[rdi+8]`<br>`0x668de39  mov rdx,[rdi+8]` | [I] entries base pointer of arg10; copies taken at +0x00 / +0x10 / +0x20 (0x668de1a, 0x668de3d) |
| r8+0x40 | 8 | R | `0x668de70  mov r8,[r8+0x40]`<br>`0x668deaf  mov r8,[r8+0x40]`<br>`0x668ded5  mov r8,[r8+0x40]`<br>`0x668deed  mov r8,[r8+0x40]`<br>`0x668df05  mov r8,[r8+0x40]` | [I] float-data pointer inside each descriptor (same +0x40 pattern as the rdx rows below) |
| r8+0x00 | 4 | R | `0x668de74  movss xmm0,[r8]`<br>`0x668deb3  movss xmm0,[r8]`<br>`0x668ded9  movss xmm0,[r8]`<br>`0x668def1  movss xmm0,[r8]`<br>`0x668df09  movss xmm0,[r8]` | [I] float 0 of the current descriptor data |
| r8+0x04 | 4 | R | `0x668de81  movss xmm0,[r8+4]`<br>`0x668dec0  movss xmm0,[r8+4]`<br>`0x668df16  movss xmm0,[r8+4]` | [I] float 1 of the current descriptor data |
| r8+0x08 | 4 | R | `0x668de8f  movss xmm0,[r8+8]`<br>`0x668df24  movss xmm0,[r8+8]` | [I] float 2 of the current descriptor data |
| r8+0x0C | 4 | R | `0x668de9d  movss xmm0,[r8+0xC]`<br>`0x668df32  movss xmm0,[r8+0xC]` | [I] float 3 of the current descriptor data |
| rdx+0x00 | 4 | R | `0x668df74  movss xmm0,[rdx]`<br>`0x668dfb2  movss xmm0,[rdx]`<br>`0x668dff0  movss xmm0,[rdx]`<br>`0x668e02e  movss xmm0,[rdx]`<br>`0x668e06c  movss xmm0,[rdx]` | [I] float 0; rdx = [rbp+0x80] (arg15) at 0x668df74, re-bound descriptor data at the other four sites |
| rdx+0x04 | 4 | R | `0x668df80  movss xmm0,[rdx+4]`<br>`0x668dfbe  movss xmm0,[rdx+4]`<br>`0x668dffc  movss xmm0,[rdx+4]`<br>`0x668e03a  movss xmm0,[rdx+4]`<br>`0x668e078  movss xmm0,[rdx+4]` | [I] float 1 (same dual base as rdx+0x00) |
| rdx+0x08 | 4 | R | `0x668df8d  movss xmm0,[rdx+8]`<br>`0x668dfcb  movss xmm0,[rdx+8]`<br>`0x668e009  movss xmm0,[rdx+8]`<br>`0x668e047  movss xmm0,[rdx+8]`<br>`0x668e085  movss xmm0,[rdx+8]` | [I] float 2 (same dual base as rdx+0x00) |
| rdx+0x0C | 4 | R | `0x668df9a  movss xmm0,[rdx+0xC]`<br>`0x668dfd8  movss xmm0,[rdx+0xC]`<br>`0x668e016  movss xmm0,[rdx+0xC]`<br>`0x668e054  movss xmm0,[rdx+0xC]`<br>`0x668e092  movss xmm0,[rdx+0xC]` | [I] float 3 (same dual base as rdx+0x00) |
| rdx+0x10 | 4 | R | `0x668df40  movss xmm0,[rdx+0x10]` | [I] float of the arg15 block ([rbp+0x80]) |
| rdx+0x14 | 4 | R | `0x668df4d  movss xmm0,[rdx+0x14]` | [I] float of the arg15 block |
| rdx+0x18 | 4 | R | `0x668df5a  movss xmm0,[rdx+0x18]` | [I] float of the arg15 block |
| rdx+0x1C | 4 | R | `0x668df67  movss xmm0,[rdx+0x1C]` | [I] float of the arg15 block |
| rdx+0x40 | 8 | R | `0x668dfae  mov rdx,[rdx+0x40]`<br>`0x668dfec  mov rdx,[rdx+0x40]`<br>`0x668e02a  mov rdx,[rdx+0x40]`<br>`0x668e068  mov rdx,[rdx+0x40]` | [I] descriptor data pointer (rdx re-bound from [rcx+0x1B8]/[rcx+0x1A8]/[rcx+0x1C0]/[rcx+0x198]) |

### Offsets present in BOTH functions (merged single row per offset)

| offset | size | R/W | verbatim instruction line(s) | meaning |
|---|---|---|---|---|
| rbp+0x00 | 8 | W | `0x5ad58da  mov [rbp],rax`<br>`0x668dd2d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE` | [I] clone: low qword of the {ptr 0xF52E07A, len 0x15} message record for 0x2FE330; ctor: MSVC EH/security stamp init (-2) |
| rbp-0x10 | 16/8 | W | `0x5ad58ed  movaps [rbp-0x10],xmm0`<br>`0x668de0e  mov [rbp-0x10],rbx` | [I] clone: 16-byte constant loaded from 0xF0BCBF8 (rdx arg frame of 0x2FE330); ctor: saved rbx (= rsi+0x60, shown by 0x668de12) |

## TOOL REQUESTS

None.
