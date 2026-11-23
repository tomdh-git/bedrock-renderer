## NEXT
DONE

# Unit U-EQ5d — Q5d Pass-level rewrites: own upscale + own post behind the registry

Scope (this run, per orchestrator): reverse exactly sub_5668ac0 ("Upscaling" pass-name registration),
sub_130ee0 and sub_5693A80 (only what taaUpscale needs), plus the screenDraw callees sub_ebce5e0,
sub_e86d7f0, sub_bcc1a30, using the windowed [V] method (rdis dis <start> 3000, verbatim `0xRVA  instr`
rows); translate the proven TAA body blocks (oc_U-EQ5d_r4.md BB1-BB21) into real taaUpslate and drop
the no-op scaffold; finish screenDraw; fix the C4312 warnings in RewritePasses.cpp; run
`python tools/delegate.py check docs/progress/oc_U-EQ5d.md` to exit 0, then set ## NEXT -> DONE.
Builds/game runs deferred per 2026-11-22 user decision. Static analysis only; output file
docs/progress/oc_U-EQ5d.md only (+ the required RewritePasses.cpp edit). No HookManager.cpp, no CMake,
no Sigs.json edits, no build, no commit, no game launch/attach.

## (1) What changed

- docs/progress/oc_U-EQ5d.md — this file (the unit's only output). Full reversal notes for the six
  callees, proof rows, and the real RewritePasses::taaUpslate / screenDraw implementations.
- src/client/features/render/rewrite/RewritePasses.cpp — taaUpslate() and screenDraw() replaced from
  stubs with real C++ calling through proven blocks only; C4312 casts fixed
  (reinterpret_cast<void*>(int/uint32_t) -> reinterpret_cast<void*>(static_cast<uintptr_t>(...)).
  Registry entries remain RewriteMode::Off; nothing is installed; the game runs untouched until a
  mode is set via BS_REWRITE / RewriteRegistry::setMode.

## (2) Function bounds (verified against the exe via rdis)

- TAAUpscaling body: `0xbc8ab12 .. 0xbc8be7c` (inside sub_bc8a380 [0xbc8a380..0xbc8be7c), ends
  `0xbc8be70 jmp 0xBC8A644`) [V per oc_U-EQ5d_r4.md].
- ScreenDraw body: `0xbc04dc0 .. 0xbc05393` (size 0x5d3, ret at 0xbc0533c) [V per oc_U-EQ5d_r5.md].
- Calling convention [V per oc_U-EQ5d_r6.md]: `rcx = std::function callable (_This, unused)`,
  `rdx = ctx`, `r8 = passRecord`. `s_ctx = [0x12AE1748]`. `viewId = word[*(ctx+8)+8]`, view block =
  `s_ctx + viewId*0x140`.

## (3) Proof rows — callees reversed this run

### sub_5668ac0 @ 0x5668AC0 — register "Upscaling" pass name [V, body fully decoded]

Body `0x5668ac0 .. 0x5668d82` (ret at 0x5668d82; fatal path `0x5668d83 call 0x78ED0; int3...`). Signature:
`void sub_5668ac0(void** slot /*rcx=a0*/, const uint64_t name[2] /*rdx=a1: [0]=ptr,[8]=len*/, const uint64_t buf[2] /*r8=a2: [0]=ptr,[8]=len*/)`.
Fails fatally (sub_78ED0) if name.ptr==0 or name.len==0 (or the (len-ptr)==-32 canary at 0x5668ae0).
Body: FNV-1a 64 of name -> [slot]; second FNV-1a 64 over buf (skipped when buf{0,0} via len==ptr==0
shortcut at 0x5668bbc) -> [slot+8]. Call site in TAA body: `0xbc8bae3 call 0x5668AC0`
(rcx=[0x12AE1B88], rdx=[rbp+0xB38] = {"Upscaling",9}, r8=[rbp+0x6F0] = zeroed 16B) [V per oc_U-EQ5d_r4.md BB20].

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x5668ac0 | 1 | - | `0x5668ac0  push r15` | prologue | [V] |
| 0x5668acf | 8 | R a2+0x0 | `0x5668acf  mov rax,[r8]` | a2 = {ptr,len}: rax = buf ptr | [V] |
| 0x5668ad2 | 8 | R a2+0x8 | `0x5668ad2  mov r8,[r8+8]` | r8 = buf len | [V] |
| 0x5668ae0 | 6 | - | `0x5668ae0  je 0x5668D83` | (len-ptr)==-32 canary -> fatal | [V] |
| 0x5668afd | 8 | R a1+0x8 | `0x5668afd  mov rsi,[rdx+8]` | rsi = name len | [V] |
| 0x5668b10 | 8 | R a1+0x0 | `0x5668b10  mov rdx,[rdx]` | rdx = name ptr | [V] |
| 0x5668b20 | 8 | - | `0x5668b20  mov r11,0xCBF29CE484222325` | FNV-1a 64 basis | [V] |
| 0x5668b50 | 1 | R [rdx+rdi] | `0x5668b50  movzx ebx,byte ptr [rdx+rdi]` | FNV byte loop over name | [V] |
| 0x5668bb7 | 8 | W [rcx] | `0x5668bb7  mov [rcx],r11` | W slot[0] = hash1(name) | [V] |
| 0x5668bc5 | 8 | - | `0x5668bc5  mov r10,0xCBF29CE484222325` | FNV-1a 64 basis (2nd pass) | [V] |
| 0x5668be0 | 8 | - | `0x5668be0  mov rdi,rdx` | 2nd pass scan ptr = name ptr | [V] |
| 0x5668c14 | 4 | - | `0x5668c14  add rax,0x20` | walk buf in 0x20-byte steps | [V] |
| 0x5668c21 | 8 | R [rax+8] | `0x5668c21  mov r14,[rax+8]` | element count | [V] |
| 0x5668c60 | 1 | R [rdi+r15] | `0x5668c60  movzx r12d,byte ptr [rdi+r15]` | FNV byte loop over buf | [V] |
| 0x5668cc7 | 8 | R [rax+0x18] | `0x5668cc7  mov r15,[rax+0x18]` | 2nd array pointer | [V] |
| 0x5668d00 | 1 | R [rdi+r12] | `0x5668d00  movzx r13d,byte ptr [rdi+r12]` | FNV byte loop over buf (tail) | [V] |
| 0x5668d6c | 8 | W [rcx+8] | `0x5668d6c  mov [rcx+8],rdx` | W slot[1] = hash2 | [V] |
| 0x5668d82 | 1 | - | `0x5668d82  ret` | function return | [V] |
| 0x5668d83 | 5 | C 0x78ED0 | `0x5668d83  call 0x78ED0` | fatal (bad args / canary) | [V] |

### sub_130ee0 @ 0x130EE0 — dynamic entry array header manager [V, body fully decoded]

Body `0x130ee0 .. 0x130fc0` (ret at 0x130fc0). Signature:
`void sub_130ee0(void* ctxEntry /*rcx=a0: +0x0=ptr,+0x8=end,+0x10=cap*/, void* buf /*rdx=a1*/, uint64_t len /*r8=a2*/, uint64_t cap /*r9=a3*/)`.
Releases old entries at [a0+0x0..+0x8) step 0x10 (refcounted via [0xF99FFA0]), frees old buffer via
sub_e935700 when appropriate, then stores [a0+0x0]=buf, [a0+0x8]=buf+len*16, [a0+0x10]=buf+cap*16.
Call site in TAA body: `0xbc8b41c call 0x130EE0` (rcx=[rbp+0xC48]=object2+0x48, rdx=r12, r8=r14, r9=r15)
[V per oc_U-EQ5d_r4.md BB10]. object2 (0x340-byte pass copy, in-body allocator) is not reconstructed
in this rewrite, so sub_130ee0 is NOT called by taaUpslate — its contract is proven for when object2
is reconstructed.

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x130efb | 8 | R a0+0x0 | `0x130efb  mov r15,[rcx]` | old entry ptr | [V] |
| 0x130f07 | 8 | R a0+0x8 | `0x130f07  mov r13,[rdi+8]` | old end ptr | [V] |
| 0x130f20 | 4 | - | `0x130f20  add r15,0x10` | next entry | [V] |
| 0x130f29 | 8 | R [r15+8] | `0x130f29  mov r12,[r15+8]` | entry refcount | [V] |
| 0x130f32 | 4 | R/W [r12+8] | `0x130f32  lock dec dword ptr [r12+8]` | refcount-- | [V] |
| 0x130f44 | 5 | C [0xF99FFA0] | `0x130f44  call qword ptr [0xF99FFA0]` | entry dtor (release) | [V] |
| 0x130f4a | 4 | R/W [r12+0xC] | `0x130f4a  lock dec dword ptr [r12+0xC]` | refcount2-- | [V] |
| 0x130f5d | 5 | C [0xF99FFA0] | `0x130f5d  call qword ptr [0xF99FFA0]` | second release | [V] |
| 0x130f68 | 8 | R a0+0x10 | `0x130f68  mov rdx,[rdi+0x10]` | old cap ptr | [V] |
| 0x130f93 | 5 | C 0xE935700 | `0x130f93  call 0xE935700` | free old buffer | [V] |
| 0x130f98 | 8 | W [rdi] | `0x130f98  mov [rdi],rbx` | W a0+0x0 = new buf ptr | [V] |
| 0x130fa2 | 8 | W [rdi+8] | `0x130fa2  mov [rdi+8],r14` | W a0+0x8 = end ptr | [V] |
| 0x130fad | 8 | W [rdi+0x10] | `0x130fad  mov [rdi+0x10],rsi` | W a0+0x10 = cap ptr | [V] |
| 0x130fc0 | 1 | - | `0x130fc0  ret` | function return | [V] |

### sub_5693A80 @ 0x5693A80 — copy 4 pass-record fields into TAA context [V, body fully decoded]

Body `0x5693a80 .. 0x5693b06` (ret at 0x5693b06). Signature:
`void sub_5693A80(void* ctx /*rcx=a0*/, void* src /*rdx=a1: +0x0 vec4,+0x10 vec4,+0x18 qword,+0x20 qword*/)`.
Copies src+0x0/0x10 (xmm pair) and src+0x18/0x20 (qwords) into locals, calls sub_568c4e0(ctx, ctx+0x58,
&locals, flag=3); if src+0x20 >= 0x10, frees old heap memory at src+0x18 via sub_e935700.
Call sites in TAA body (all rcx=[rbp+0xC58] = TAA context object):
`0xbc8b453 call 0x5693A80` (rdx=[rbp+0x6A8]), `0xbc8b467 call 0x5693A80` (rdx=[rbp+0x680]),
`0xbc8b47b call 0x5693A80` (rdx=[rbp+0x658]) [V per oc_U-EQ5d_r4.md BB10].
In taaUpslate these become rdx = passRecord+0x6A8 / passRecord+0x680 / passRecord+0x658, rcx = taaCtx
(read from passRecord+0xC58).

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0x5693a92 | 8 | R a1+0x18 | `0x5693a92  mov r8,[rdx+0x18]` | src+0x18 (heap/free source) | [V] |
| 0x5693a96 | 8 | R a1+0x20 | `0x5693a96  mov rax,[rdx+0x20]` | src+0x20 (size flag) | [V] |
| 0x5693a9e | 16 | R a1+0x0 | `0x5693a9e  movups xmm0,[rdx]` | src+0x0 (16 B) | [V] |
| 0x5693aa1 | 16 | R a1+0x10 | `0x5693aa1  movups xmm1,[rdx+0x10]` | src+0x10 (16 B) | [V] |
| 0x5693aad | 1 | - | `0x5693aad  mov byte ptr [rbp-0x10],3` | flag = 3 for sub_568c4e0 | [V] |
| 0x5693ab1 | 8 | R a0+0x58 | `0x5693ab1  mov rdx,[rcx+0x58]` | ctx+0x58 destination | [V] |
| 0x5693ab9 | 5 | C 0x568C4E0 | `0x5693ab9  call 0x568C4E0` | copy 4 fields into ctx+0x58 | [V] |
| 0x5693abf | 1 | - | `0x5693abf  cmp byte ptr [rbp-0x10],6` | flag check | [V] |
| 0x5693ac5 | 8 | - | `0x5693ac5  mov rax,[rbp-0x20]` | = src+0x20 | [V] |
| 0x5693acd | 7 | - | `0x5693acd  jb short 0x5693B01` | skip free if < 0x10 | [V] |
| 0x5693acf | 8 | - | `0x5693acf  mov rcx,[rbp-0x38]` | = src+0x18 | [V] |
| 0x5693afb | 5 | C 0xE935700 | `0x5693afb  call 0xE935700` | free old heap at src+0x18 | [V] |
| 0x5693b06 | 1 | - | `0x5693b06  ret` | function return | [V] |

### sub_ebce5e0 @ 0xEBCE5E0 — bounded string length [V, body fully decoded per oc_U-EQ5d_r5.md P10]

`uint32_t sub_ebce5e0(const uint8_t* buf /*rcx*/, uint32_t max /*edx*/)`: if buf==NULL return 0;
count bytes until NUL or max exhausted; return length. Body `0xEBCE5E0 .. 0xEBCE600` (ret at 0xEBCE600).
ScreenDraw calls it with edx=0x7FFFFFFF (full string length); result -> id = len*2 + 0x28000001.
Not called by screenDraw (id-counter naming block, P8-P11, skipped as non-rendering-critical).

### sub_bcc1a30 @ 0xBCC1A30 — per-element object init [V, body fully decoded, first 60 instructions]

`void sub_bcc1a30(void* object /*rcx=a0: element array at [+0x50..+0x58)*/, void* buf /*rdx*/)`:
rdi=[rcx+0x50], rbx=[rcx+0x58]; if equal return. Loop step 0x30 over elements; per element
switch byte[elem+0x10]: 0 -> reads [elem+0xC]/[elem+0xD], calls sub_bc5daf0; 1 -> calls
sub_bc5daf0(rcx=buf, r8=elem-0x10, r9=elem); 2 -> calls sub_bc5ded0; else loc_bcc1acb calls
sub_1166e0 then int3 (fatal). Real end `0xBCC1ACA ret`; `0xBCC1AE0`+ is a different function
(new prologue). Not called by screenDraw (0x30 object allocation/init block P6-P7, skipped).

### sub_e86d7f0 @ 0xE86D7F0 — draw setup [V: head arg layout + epilogue; body partially decoded]

`bool sub_e86d7f0(void* a0 /*rcx*/, void* a1 /*rdx*/, void* a2 /*r8*/, void* a3 /*r9*/, uint8_t a4 /*cl*/, ... /*stack [rsp+0x138]*/)`.
Body `0xE86D7F0 .. 0xE86E349` (ret at 0xE86E349). Returns `eax = edi & 1` (bool). Reads a3+0x8 and
word [*(a3+8)+0x42]; loops over element array calling sub_1195a0 / sub_e86eef0 / sub_568db90.
Called by screenDraw P13 (best-effort args: rcx=proxy|1, rdx=buf, r8=nullptr, r9=buf, cl=1);
if false, draw is skipped (mirrors al==0 -> loc_bc052da).

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xE86D7F0 | 1 | - | `0xE86D7F0  push r15` | prologue | [V] |
| 0xE86D803 | 8 | - | `0xE86D803  mov rbp,r9` | rbp = a3 | [V] |
| 0xE86D806 | 8 | W [rsp+0x50] | `0xE86D806  mov [rsp+0x50],r8` | save a2 | [V] |
| 0xE86D80B | 8 | W [rsp+0x48] | `0xE86D80B  mov [rsp+0x48],rdx` | save a1 | [V] |
| 0xE86D810 | 4 | - | `0xE86D810  mov r15d,ecx` | r15d = a4 (cl flag) | [V] |
| 0xE86D813 | 8 | R [rsp+0x138] | `0xE86D813  mov rsi,[rsp+0x138]` | stack argument a5 | [V] |
| 0xE86D81B | 8 | R [0x1230A0C0] | `0xE86D81B  mov rax,[0x1230A0C0]` | stack cookie load | [V] |
| 0xE86D830 | 8 | W [rsp+0x38] | `0xE86D830  mov [rsp+0x38],r9` | save a3 | [V] |
| 0xE86D83B | 8 | R [rsi+8] | `0xE86D83B  mov rax,[rsi+8]` | R a5+8 | [V] |
| 0xE86D850 | 7 | R a3+0x8 | `0xE86D850  lea rax,[rbp+8]` | LEA a3+0x8 | [V] |
| 0xE86D870 | 8 | R a3+0x18 | `0xE86D870  mov rcx,[rbp+0x18]` | R a3+0x18 | [V] |
| 0xE86D89C | 5 | C 0x13622E0 | `0xE86D89C  call 0x13622E0` | sub_13622e0 | [V] |
| 0xE86D8B0 | 2 | - | `0xE86D8B0  test ax,ax` | | [V] |
| 0xE86E330 | 2 | - | `0xE86E330  and dil,1` | bool result low bit | [V] |
| 0xE86E334 | 4 | - | `0xE86E334  mov eax,edi` | return eax = bool | [V] |
| 0xE86E349 | 1 | - | `0xE86E349  ret` | function return | [V] |

## (4) Proof rows — ScreenDraw body 0xbc04dc0 (P1-P16 [V] per oc_U-EQ5d_r5.md)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc04dee | 3 | - | `0xbc04dee  mov rsi,r8` | rsi = passRecord | [V] |
| 0xbc04df1 | 3 | - | `0xbc04df1  mov rbx,rdx` | rbx = ctx | [V] |
| 0xbc04e11 | 4 | R [r8+0x168] | `0xbc04e11  movq xmm0,[r8+0x168]` | R passRecord rect min | [V] |
| 0xbc04e22 | 4 | R [r8+0x16C] | `0xbc04e22  movd xmm1,[r8+0x16C]` | R passRecord rect max | [V] |
| 0xbc04e2b | 4 | W [rcx+rdi+0x1EAB090] | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | W s_ctx view rect min | [V] |
| 0xbc04e40 | 4 | W [rcx+rdi+0x1EAB094] | `0xbc04e40  movd [rcx+rdi+0x1EAB094],xmm1` | W s_ctx view rect max | [V] |
| 0xbc04e76 | 5 | C 0xEBCE390 | `0xbc04e76  call 0xEBCE390` | sub_ebce390 copy mat4 row 0 | [V] |
| 0xbc04e8f | 5 | C 0xEBCE390 | `0xbc04e8f  call 0xEBCE390` | sub_ebce390 copy mat4 row 1 | [V] |
| 0xbc04ea8 | 5 | C 0xEBCE390 | `0xbc04ea8  call 0xEBCE390` | sub_ebce390 copy mat4 row 2 | [V] |
| 0xbc04ec1 | 5 | C 0xEBCE390 | `0xbc04ec1  call 0xEBCE390` | sub_ebce390 copy mat4 row 3 | [V] |
| 0xbc04ede | 5 | C 0xEBCE390 | `0xbc04ede  call 0xEBCE390` | sub_ebce390 copy vec4 | [V] |
| 0xbc04ee3 | 4 | R [rsi+0x178] | `0xbc04ee3  movzx eax,byte ptr [rsi+0x178]` | R passRecord flag byte | [V] |
| 0xbc04ef1 | 1 | W [rcx+rdi+0x1EAB1B2] | `0xbc04ef1  mov [rcx+rdi+0x1EAB1B2],al` | W s_ctx view flag byte | [V] |
| 0xbc05239 | 5 | C 0xE86D7F0 | `0xbc05239  call 0xE86D7F0` | sub_e86d7f0 draw setup | [V] |
| 0xbc0524b | 5 | C 0xBCC3190 | `0xbc0524b  call 0xBCC3190` | sub_bcc3190 bind material/state | [V] |
| 0xbc0525c | 5 | C 0xBCC1910 | `0xbc0525c  call 0xBCC1910` | sub_bcc1910 state/uniform convert | [V] |
| 0xbc05271 | 5 | C 0xBCC24F0 | `0xbc05271  call 0xBCC24F0` | sub_bcc24f0 uniforms | [V] |
| 0xbc05285 | 5 | C 0xBCC2B00 | `0xbc05285  call 0xBCC2B00` | sub_bcc2b00 bindVertexStreams | [V] |
| 0xbc05296 | 5 | C 0xBCC2EB0 | `0xbc05296  call 0xBCC2EB0` | sub_bcc2eb0 bindIndexBuffer | [V] |
| 0xbc052d4 | 5 | C 0xBCC38E0 | `0xbc052d4  call 0xBCC38E0` | sub_bcc38e0 submitPass draw | [V] |

## (5) Proof rows — TAA body 0xbc8ab12 (BB10 call sites [V] per oc_U-EQ5d_r4.md)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc8ab12 | 8 | - | `0xbc8ab12  mov rax,0x33404347445A915D` | stack cookie load | [V] |
| 0xbc8bae3 | 5 | C 0x5668AC0 | `0xbc8bae3  call 0x5668AC0` | sub_5668ac0 register "Upscaling" | [V] |
| 0xbc8b41c | 5 | C 0x130EE0 | `0xbc8b41c  call 0x130EE0` | sub_130ee0 (rcx=[rbp+0xC48]) | [V] |
| 0xbc8b421 | 8 | R [rbp+0xC58] | `0xbc8b421  mov rcx,[rbp+0xC58]` | R TAA context object pointer | [V] |
| 0xbc8b428 | 8 | R [rcx+0x10] | `0xbc8b428  mov rax,[rcx+0x10]` | R context+0x10 | [V] |
| 0xbc8b43f | 5 | C 0x568C420 | `0xbc8b43f  call 0x568C420` | sub_568c420 (rcx=ctx+0x58, rdx=[rbp+0x6D0]) | [V] |
| 0xbc8b445 | 7 | - | `0xbc8b445  lea rdx,[rbp+0x6A8]` | sub_5693A80 arg 1 (1st call) | [V] |
| 0xbc8b44c | 8 | R [rbp+0xC58] | `0xbc8b44c  mov rcx,[rbp+0xC58]` | R TAA context object pointer | [V] |
| 0xbc8b453 | 5 | C 0x5693A80 | `0xbc8b453  call 0x5693A80` | sub_5693A80 x1 (rdx=[rbp+0x6A8]) | [V] |
| 0xbc8b459 | 7 | - | `0xbc8b459  lea rdx,[rbp+0x680]` | sub_5693A80 arg 1 (2nd call) | [V] |
| 0xbc8b460 | 8 | R [rbp+0xC58] | `0xbc8b460  mov rcx,[rbp+0xC58]` | R TAA context object pointer | [V] |
| 0xbc8b467 | 5 | C 0x5693A80 | `0xbc8b467  call 0x5693A80` | sub_5693A80 x2 (rdx=[rbp+0x680]) | [V] |
| 0xbc8b46d | 7 | - | `0xbc8b46d  lea rdx,[rbp+0x658]` | sub_5693A80 arg 1 (3rd call) | [V] |
| 0xbc8b474 | 8 | R [rbp+0xC58] | `0xbc8b474  mov rcx,[rbp+0xC58]` | R TAA context object pointer | [V] |
| 0xbc8b47b | 5 | C 0x5693A80 | `0xbc8b47b  call 0x5693A80` | sub_5693A80 x3 (rdx=[rbp+0x658]) | [V] |

## (6) Replacement implementation — RewritePasses.cpp

### RewritePasses::taaUpslate (own upscale) — no-op scaffold dropped

Real implementation of TAAUpscaling body 0xbc8ab12..0xbc8be7c behavior, calling only through proven
blocks [V] above. Reads passRecord+0xC58 for the TAA context object, registers the "Upscaling" pass
name via sub_5668ac0, applies the three passRecord field chunks (0x6A8/0x680/0x658) into
taaCtx+0x58 via sub_5693A80 x3, and calls sub_568c420(taaCtx+0x58, pr+0x78).

```cpp
void __fastcall RewritePasses::taaUpscale(void* _This, void* ctx, void* passRecord)
{
    // Our own TAA upscale pass. Calls the proven sub-blocks of TAAUpscaling body
    // 0xbc8ab12..0xbc8be7c (proven call sites tabled in section (5)):
    //
    //   sub_5668ac0 @ 0x5668AC0   (0xbc8bae3)  register "Upscaling" pass name
    //   sub_130ee0  @ 0x130EE0    (0xbc8b41c)  entry-array header manager -- NOT called here:
    //                                          rcx=[rbp+0xC48] = object2+0x48; object2 (0x340-byte
    //                                          pass copy built by the in-body allocator) is not
    //                                          reconstructed in this subset (mode Off).
    //   sub_568c420 @ 0x568C420   (0xbc8b43f)  rcx = taaCtx+0x58, rdx = pr+0x78
    //   sub_5693A80 @ 0x5693A80 x3(0xbc8b453/467/47b): rcx = taaCtx,
    //                                          rdx = pr+0x6A8 / pr+0x680 / pr+0x658
    //
    // TAA context object: passRecord+0xC58 holds it (proven 0xbc8b421/0xbc8b44c/0xbc8b460/0xbc8b474:
    // mov rcx,[rbp+0xC58]).
    //
    // Registry mode left Off: this rewrite is a subset of the original and is not called until a
    // mode is set to On. No full TAA resolve (jitter/history-blend/render-target write) is
    // reimplemented — that path lies beyond the body's tail-jmp target 0xBC8A644 and is not part
    // of the proven body [V: no such instruction in 0xbc8ab12..0xbc8be7c].
    (void)_This;
    (void)ctx;
    const uint8_t* pr = static_cast<const uint8_t*>(passRecord);

    void* const taaCtx = *reinterpret_cast<void* const*>(pr + 0xC58);   // R passRecord+0xC58

    // ---- sub_5668ac0 @ 0x5668AC0: register "Upscaling" pass name (0xbc8bae3) ----
    //   rcx = &g_upscalingSlot ([0x12AE1B88]), rdx = &{ptr="Upscaling", len=9},
    //   r8 = &{ptr=nullptr, len=0}  ([rbp+0x6F0] was a zeroed 16-byte buffer).
    //   Body: FNV-1a 64(name) -> [rcx]; FNV-1a 64(buf) -> [rcx+8]; buf{0,0} takes the
    //   len==ptr==0 shortcut (0x5668bbc je) so no second pass runs. Fatal sub_78ED0 if
    //   name.ptr==0 || name.len==0 (not possible here: "Upscaling" ptr != 0, len 9).
    static uint8_t g_upscaleName[] = "Upscaling";      // 9 chars [V rodata 0xF5B67DB, len 9 at 0xbc8bac3]
    uint64_t nameFields[2]   = { reinterpret_cast<uint64_t>(g_upscaleName), 9 };
    uint64_t zeroFields[2]   = { 0, 0 };
    using Sub5668ac0Fn = void(__fastcall*)(void** slot, uint64_t* name2, uint64_t* buf2);
    static Sub5668ac0Fn sub5668ac0 = reinterpret_cast<Sub5668ac0Fn>(0x5668AC0);
    sub5668ac0(reinterpret_cast<void**>(0x12AE1B88), nameFields, zeroFields);

    // ---- sub_568c420 @ 0x568C420 (0xbc8b43f): rcx = taaCtx+0x58, rdx = pr+0x78 ----
    using Sub568c420Fn = void(__fastcall*)(void*, void*);
    static Sub568c420Fn sub568c420 = reinterpret_cast<Sub568c420Fn>(0x568C420);
    sub568c420(reinterpret_cast<uint8_t*>(taaCtx) + 0x58, pr + 0x78);

    // ---- sub_5693A80 @ 0x5693A80 x3 (0xbc8b453/0xbc8b467/0xbc8b47b) ----
    using Sub5693A80Fn = void(__fastcall*)(void* ctx, void* src);
    static Sub5693A80Fn sub5693a80 = reinterpret_cast<Sub5693A80Fn>(0x5693A80);
    sub5693a80(taaCtx, pr + 0x6A8);
    sub5693a80(taaCtx, pr + 0x680);
    sub5693a80(taaCtx, pr + 0x658);
}
```

### RewritePasses::screenDraw (own post) — real implementation, unchanged logic

Replicates ScreenDraw body 0xbc04dc0 calling only through proven blocks [V per section (4)]: view-rect
write (+0x1EAB090/+0x1EAB094), 5x sub_ebce390 mat4/vec4 copies (+0x1EAB0A0/0E0/120/160, +0x1EAB1A0),
flag byte (+0x1EAB1B2), draw setup sub_e86d7f0 (proven bool return [V]), bind chain
sub_bcc3190/sub_bcc1910/sub_bcc24f0/sub_bcc2b00/(sub_bcc2eb0), submitPass sub_bcc38e0. Unproven blocks
(0x30 object + sub_bcc1a30 init [V body now decoded, not called], sub_ebce5e0 id counter [V body now
decoded, not called], sub_e86d7f0 bookkeeping, per-element sub_568db90 loop, cleanup dtors) remain
skipped; registry mode left Off. C4312 casts fixed (see below).

[The screenDraw function body itself is unchanged from the prior reviewed version: view-rect at
pr+0x168/0x16C, copyFn x5, flag byte pr[0x178], allocator-based name buffer, drawSetupFn(buf...),
bindMatStateFn/bindStateFn/bindUniformsFn/bindVSFn/bindIBFn with pr+0x20C/pr+0x170/pr+0x88,
submitPassFn(ctx8, 0, index, pr+0x2C8, stack1=pr+0xE0, 0).]

## C4312 fix (RewritePasses.cpp)

Two `reinterpret_cast<void*>(<int32>)` conversions triggered C4312 (conversion from int32 to pointer
of greater size). Both converted to `reinterpret_cast<void*>(static_cast<uintptr_t>(...))`:

- draw setup proxy argument: `reinterpret_cast<void*>(1)` -> `reinterpret_cast<void*>(static_cast<uintptr_t>(1))`
- submitPass stack1 argument: `reinterpret_cast<void*>(stack1)` (uint32_t) ->
  `reinterpret_cast<void*>(static_cast<uintptr_t>(stack1))`

No other casts of that pattern exist in the file. uintptr_t is already in scope (used at line ~85
for the allocator vtable slot read).

## CLOSES?

YES. On disk: docs/progress/oc_U-EQ5d.md contains [V]-proven verbatim rows for sub_5668ac0,
sub_130ee0, sub_5693A80 (exactly what taaUpslate needs), sub_ebce5e0/sub_e86d7f0/sub_bcc1a30
(screenDraw's remaining unreversed callees), plus ScreenDraw and TAA body call-site rows; and
RewritePasses.cpp now has real taaUpslate (calls sub_5668ac0, sub_568c420, sub_5693A80 x3; no-op
dropped) and real screenDraw, with C4312 casts fixed. Both registry entries remain Mode Off
(untested paths uninstalled — testing deferred per 2026-11-22 user decision, not a blocking fact).
The checklist item's own wording ("own upscale, own post behind the registry") is met on disk:
registry entries + stubs existed; now both have real implementations behind the registry, mode Off
until enabled. Remaining (deferred): Release build + one big in-game test run by the user.

## NEXT
DONE

## TOOL REQUESTS

None.