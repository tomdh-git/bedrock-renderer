# Unit U-E4-C: ChunkGeometry extractor body C (0x66f2820..0x66f4f5a)

## Status
Unit started; body C range identified per addendum of docs/functions/66ea3d0.md:
- Body A = 0x66ec126..0x66ef28d (generic kinds)
- Body B = 0x66ef308..0x66f2817 (K==13 light_source, f16cf path)
- Body C = 0x66f2820..0x66f4f5a (f1658 set)
- Body D = 0x66f4fcb..0x66f6e36 (K==10 terrain_blend)

Source: static disassembly of 1.26.62.01 via `tools/rdis/target/release/rdis.exe` (dis cmd). Tags: [V] read in disassembly, [I] inferred, [?] unknown.
Task: decode body C instruction-complete where feasible; for each phase note differences from body A (docs/progress/oc_U-E4-A2.md).
EXE: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe 1.26.62.01. Static analysis only.

## NEXT
Body C complete through 0x66F4F76 (tail phase setup). Nothing remaining in this unit per map boundary 0x66F4F5A. Unit done.

## Disassembly log
### Step 1 (done): rdis dis 0x66f2820 300 -> 0x66f2820..~0x66f2db0 (300 instr, cut mid-instruction at 66f2da9)
Prologue (matches body A skeleton with noted diffs):
- 0x66f2820 mov rax,[rbp+0xEE8]; mov [rbp+0xC78],rax; lea rcx,[rbp+0xC80]; lea rdx,[rbp+0xEF0]; call 0xE86B370 (clone pass record); [rbp+0xCF8]=0 [V] (matches body A clone)
- 0x66f2854 mov rax,[rbx+0x48]; mov rdx,[rax] = K [V]
- 0x66f285b lea rax,[rdx-5]; test rax,0x...FB; sete r15b -> fogA = ((K-5)&~4)==0, K in {5,9} [V] (matches body A)
- 0x66f286c cmp rdx,0xA; je 0x66F2924 -> K==0xA: [rbp+0x16D0]=2 [V]
- 0x66f2876 mov byte [rbp+0x16D0],9 (default v=9) [V]
- 0x66f287d cmp rdx,0xC; je 0x66F292B (K==0xC skips class compute) [V]
- 0x66f2887 lea rax,[rdx-7]; cmp rax,3; setb al -> (K-7)<3, K in {7,8,9} [V]
- 0x66f2892 lea rcx,[rdx-0xF]; cmp rcx,2; setb cl -> (K-0xF)<2, K in {0xF,0x10} [V]
- 0x66f289d or cl,al; 0x66f289f mov [rbp+0x16D0],cl -> v = kind class [V]
- 0x66f28a5 jmp 0x66F292B
- KIND-CLASS DIFF vs body A: body C default v=9, K==0xA -> v=2, else v=class; NO f16cf re-check inside the compute (identical skeleton to body B prologue; body A: `if (f16cf && K != 0xC) v=2; else if K!=0xA v=...; else v=(K==0xC)?9:0`; body C stores v at [rbp+0x16D0]; body A used v16b0 reg + [rbp+0x1698]=K)
- 0x66f292b mov [rbp+0x16B0],rdx (rdx = K saved) [V]
- 0x66f2932 xorps xmm0; [rbp+0x1670]=0; [rbp+0x1680]=0 -> vec1670 vector init {shared_ptr{ptr,ctrl},u8 valid+0x10} [V] (matches body A vec1670)
- 0x66f2947 mov rax,[rbp+0x16C0]; mov rax,[rax+0x38] = n (desc+0x38 count); [rbp+0x1440]=rax; test rax,rax; je 0x66F2985 [V] (matches body A)
- 0x66f295e mov rcx,0xAAAAAAAAAAAAAAB; cmp rax,rcx; jae 0x66F9210 (throw if n huge) [V] (matches body A)
- 0x66f2971 lea rcx,[rbp+0x1670]; lea rdx,[rbp+0x1440]; call 0x678D170 (reserve n) [V] (matches body A)
- 0x66f2985 mov rsi,[rbp+0x16A0]; lea rdi,[rsi+0x2E8]; call 0xEEC59F0 (lock builder+0x2e8 mutex); test eax,eax; jne 0x66F8FB0 [V] (matches body A lock)
- 0x66f29a3 [rbp+0x1690]=rdi (mutex addr saved); cmp dword [rsi+0x334],0x7FFFFFFF; je 0x66F8FBB (recursion-limit throw) [V] (matches body A)
- 0x66f29ba mov rax,[rbp+0x16C0]; mov rax,[rax+0x38] (draw-list begin); test rax,rax; je 0x66F2C29 [V]
- 0x66f29ce mov rcx,[rbp+0x16C0]; mov rdi,[rcx+0x40] (draw-list end base); imul rsi,rax,0x58; add rsi,rdi -> end = begin + n*0x58 [V] (matches body A stride 0x58)
- 0x66f29e0 lea rbx,[rbp+0x1440]; lea r14,[rbp+0xF70]; xorps xmm6,xmm6; jmp 0x66F2A0D -> pass-2 loop entry setup [V]

Pass-1 resolve loop (rdi=entry ptr, rsi=end):
- 0x66f2a0d movzx eax,byte [rdi+0x28] (entry tag); test; je 0x66F2A24 (tag0->p=rdi+0x10); cmp eax,1; jne throw 0x66F862C; else p=rdi+0x18 [V] (matches body A tag 0->e+0x10, tag 1->e+0x18)
- mov rax,[rax]; test rax,rax; je skip (null pointer) [V]
- rcx=[rbp+0x16A0] (builder state); rdx=[rcx+0x2D8] (map header); r8=[rdx+8] (root); cmp byte [r8+0x19],0 (isnil) [V]
- rb-tree walk: r9=[rax] (**p); cmp [r8+0x20],r9; setl r10b; cmovge rcx,r8; shl r10d,4; r8=[r8+r10]; loop until [r8+0x19]!=0 [V] (matches body A)
- cmp byte [rcx+0x19],0 (is end?); jne skip; cmp rcx,rdx; je skip (end==node); rdx=[rcx+0x20] (node key); cmp [rax],rdx; jl skip (**p<key); r12=[rcx+0x28] (node value); test r12,r12; je skip (!value) [V] (matches body A)
- rcx=[rbp+0x16C0] (desc); movzx eax,byte [rcx+0x50] (desc+0x50 flag); rcx=[rcx+0x48] (desc+0x48 kind ptr); lea rdx,[r12+8] (node.value+8); rcx=[rcx] (K); [rbp+0xF70]=rcx; [rbp+0xF78]=al [V] (matches body A {K, flag50} args)
- call 0xBC090B0(&out1440, node.value+8, {K, flag50}) -> lookup (kind,flag50)->shared_ptr pair [V] (matches body A)
- dedupe compare [rbp+0x1440/0x1448/0x1450] vs [r12+0x28/+0x10]: cmove/sete; if equal -> r12=0 skip push; else r12b=1 (valid) [V] (matches body A)
- push into vec1670 via 0x678D3F0 grow path; [rbp+0x1440]=ptr, [rbp+0x1448]=ctrl (lock inc ctrl+8), byte [rdx+0x10]=1 (valid) [V] (matches body A)
- lock dec [r12+8] on exit path (release shared) [V]
- loop back 0x66F2A00: add rdi,0x58; cmp rdi,rsi; je 0x66F2C29 [V]
DIFF vs body A: none yet — pass-1 resolve loop is identical skeleton. No f16cf gating inside loop.

### Step 2 (done): rdis dis 0x66F2DA0 300 -> 0x66F2DA0..~0x66F3420 (300 instr, cut at 66f341d)
Pass-2 setup (rsi=entry, rdi=&rbp+0x1444 model out, end=[rbp+0x16A0], ebx=index i):
- 0x66f2c29 mov rax,[rbp+0x16B0] (K); and rax,0x...FE (K&~1); [rbp+0x1658]=rax [V] — DIFF vs body A: body A [rbp+0x1658]=&desc[+0x78]; body C = K&~1 (same as body B)
- 0x66f2c3b call 0xEEC5A10 (unlock builder mutex) [V] (matches body A unlock)
- 0x66f2c47 rdx=[rbp+0x16C0] (desc); rsi=[rdx+0x40] (draw-list begin); imul rax,[rdx+0x38],0x58; add rax,rsi -> end; [rbp+0x16A0]=end [V] (matches body A end=begin+n*0x58; body C uses rsi as iterator, [rbp+0x16A0] as end)
- 0x66f2c61 lea rdi,[rbp+0x1444] (model out); xor eax,eax; movzx ecx,byte [rbp+0x16D0] (v=kind class); cmp cl,2; sete al; shl eax,0xB (v==2?0x800:0); cmp cl,9; mov ecx,0x2800; cmovne ecx,eax (v==9?0x2800 : v==2?0x800:0); lea rax,[rdx+0x78]; [rbp+0x1388]=rax (&desc+0x78 material instance) [V]; mov r13b,r15b (r13b=fogA); lea eax,[rcx+r13*4+0x8101]; [rbp+0x1688]=eax -> render-state word = 0x8101 + fogA*4 + (v==9?0x2800 : v==2?0x800:0) [V] — matches body A render-state word exactly
- 0x66f2ca1 lea r12,[rbp+0x1050]; xorps xmm6; movss xmm7=[0xEEC8060] (1.0f); movsd xmm8=[0xEFD32F0] ({0,0.0078125}); movaps xmm9=[0xF0A4080] ({-0,-0,0,0}); movss xmm10=[0xEEC8060] (1.0f); movsd xmm11=[0xEFD32F0]; movss xmm13=[0xEFC13A4] (8.0f); movaps xmm14=[0xF0B8740] ({8,8,0,0}) [V] — matches body A loop constants exactly
- 0x66f2ce7 lea r13,[rbp+0x1210]; xor ebx,ebx; jmp 0x66F2D0E [V]

Pass-2 loop (rsi=entry, end=[rbp+0x16A0], exit 0x66F4F5A = body C end boundary):
- 0x66f2d0e cmp rsi,[rbp+0x16A0]; je 0x66F4F5A (loop exit = body C end) [V]
- 0x66f2d1b movzx eax,byte [rsi+0x28] (tag); test; je 0x66F2D38 (tag0->p=rsi+0x10); cmp eax,1; jne throw 0x66F84B0; lea rax,[rsi+0x18]; cmp [rax],0; jne process; je skip [V] (matches body A tag/null handling)
- process: movsd xmm15,[rsi+0x3C] (a,b float2); build translation T matrix via shufps/mulps/addps; xmm12=[rsi+0x44] (z); T stored [rbp+0x1468..0x1478] [V] (matches body A T=translate(a,b,z))
- 0x66f2dba lea rcx,[rbp+0xE10] (model); mov rdx,[rbp+0x1388] (desc_mat=&desc+0x78); lea r8,[rbp+0x1440] (&T); call 0xAA6580 (&model=descMat*T) [V] (matches body A model=descMat*T; body C desc_mat=[rbp+0x1388]=&desc+0x78)
- if *(float*)(rsi+0x48)!=1.0f (scale): ucomiss xmm0,xmm10; jne->scale path; build scale; 0x66f2e27 call 0xAA6580(&f70=[rbp+0xF70], &model=[rbp+0xE10], &S); copy model back to [rbp+0xE10..0xE40] [V] (matches body A scale path)
- 0x66f2e7a mov rax,[rbp+0x16A8]; mov rdx,[rax] (**ctx); [rsp+0x20]=rsi (stack e); lea rcx,[rbp+0xDB8] (drawlist); mov r8,[rbp+0x1698]; lea r9,[rbp+0xEE8] (passRecord_ee8); call 0x678C4C0 (draw-list builder) [V] — DIFF vs body A: body A r8=[rbp+0x1388]=fogA; body C r8=[rbp+0x1698] (meaning ?)
- [rbp+0x1650]=&rbp+0xC78 (rec_cloned) [V] (body A used [rbp+0x1120]=&rec_c78 — different offset, same role)
- cmp byte [rbp+0x16BE],1 (byte16be=FogAlpha binding found); jne skip per-entry FogAlpha [V] (matches body A)
- movss xmm0,[rsi+0x4C] (entry fogAlpha); xorps xmm1; ucomiss; jbe skip [V] (matches body A e+0x4c > 0)
- shufps xmm0,xmm0,0 (splat); [rbp+0x1440]=xmm0; [rbp+0xF70]=1; lea rax,[rbp+0x1440]; [rbp+0xF78]=rax; call 0x5679DB0(passRecord_ef0, {slot=[rbp+0x16BC]}, {1,&vec4}) writes per-entry FogAlpha [V]; [rbp+0x1650]=&rbp+0xEE8 (rec_ee8) [V] (matches body A per-entry FogAlpha + [rbp+0x1120]=&rec_ee8; body C uses [rbp+0x1650])

Pack 4 ptrs at [rbp+0xEA8..0xEC0]:
- 0x66f2f15 [rbp+0xEA8]=[rbp+0x1410]; [rbp+0xEB0]=[rbp+0xE10] (model); [rbp+0xEB8]=[rbp+0xDB8] (drawlist); [rbp+0xEC0]=[rbp+0x1650] (rec) [V] — DIFF vs body A: body A packed {&1650,model,drawlist,&1120} at [rbp+0xea8..0xec0]; body C order = {&1410, model, drawlist, rec} [? meaning]

vec1670[i] fetch:
- rsi=loop index i saved to [rbp+0x1690]=rbx [V]; rax=[rbp+0x1670]; rcx=i*3 (rbx+rbx*2); movzx ebx,byte [rax+rcx*8+0x10] = valid byte (stride 0x18) [V] (matches body A vec1670[i] valid +0x10)
- byte [rbp+0x1430]=0 pre-set [V]
- if valid==1: [rbp+0x1420]=0; rcx=[rax+8]; lock inc [rcx+8]; [rbp+0x1420]=[rax]; [rbp+0x1428]=rcx; byte [rbp+0x1430]=1 [V] (matches body A shared_ptr copy into [rbp+0x1420..0x1430])

Branch on al = !valid OR (K&~1==2):
- 0x66f2fa8 cmp [rbp+0x1658],2; sete cl -> (K&~1==2) [V]; eax=ebx (valid); xor al,1 (!valid); or al,cl -> al = !valid OR class2 [V]
- movzx ecx,byte [rbp+0x1368] (isAB); test [rbp+0x16CF],cl; je 0x66F320C (if (isAB & [rbp+0x16CF])==0 skip shift block) [V] — [rbp+0x16CF] meaning ?
- test al,al; je 0x66F332B (if al==0 i.e. valid&&!class2 skip shift) [V]

SHIFT block (al!=0 && (isAB&[rbp+0x16CF])!=0):
- 0x66f2fd4 addss xmm12,xmm13 (z+=8.0f); addps xmm15,xmm14 ({a,b}+=8) [V] — matches body A shift variant
- cmp [rbp+0x1658],2; jne 0x66F33C0; test bl,bl; je 0x66F33C0 -> if K&~1==2 && valid: enter matrix-copy path [V]
- movlps [rbp+0x1390],xmm15; movss [rbp+0x1398],xmm12 (store shifted vec2/float) [V]
- lea rcx,[rbp+0xEA8]; lea rdx,[rbp+0x1130]; call 0x67A75D0 [V] — NOTE: body C calls 0x67A75D0 here (body B called 0x678CF10); see diff below
- lea rbx,[rbp+0xF70]; lea rax,[rbp+0x1390]; [rsp+0x20]=rax; rcx=rbx; rdx=[rbp+0x1210]; r8=[rbp+0x11B8]; r14=[rbp+0x1130]; r9=r14; call 0x678E1D0(...) [V] (matches body A 0x678e1d0 args)
- copy descriptor tail: [r12+0x70]=[r13+0x60]; [r12+0x60..0x70]=[r13+0x50]; byte [rbp+0x10C4]=[rbp+0x1274]; [rbp+0x10C8..0x10D8]=[rbp+0x1278]; [r12+0x88]=[r13+0x78]; [r12+0x98]=[r13+0x88]; [r12+0xA7]=[r13+0x97] (unaligned) [V]
- word [rbp+0x1108]=[rbp+0x12B8]; call 0x67E23F0(rcx=r14=[rbp+0x1130]) release shared [V]; call 0x678E420(rcx=[rbp+0x1440]=model, rdx=[rbp+0x1060], r8=[rbp+0x1008], r9=[rbp+0xF80]) [V] (matches body A 0x678e420)
- copy back: [rbp+0x1580+0x10]=[r12+0x70]; [rbp+0x1580..]=[r12+0x60]; byte [rbp+0x1594]=[rbp+0x10C4]; [rbp+0x1598..]=[rbp+0x10C8]; [rdi+0x183]=[r12+0xA7]; [rdi+0x174]=[r12+0x98]; [rdi+0x164]=[r12+0x88] [V] (rdi=&rbp+0x1444; staging base body C [rbp+0x1580] vs body A [rbp+0x1578])
- word [rbp+0x15D8]=[rbp+0x1108] [V]
- pass=0x5ABA5C0(frameCtx(rbp+0x16a8)->+0x10 + 0x9D0) [V]; zero 12 DrawItem slots [r13-0xD8..r13-0x28] where r13=[rbp+0x1210] (item base) [V]; feature flag 0x4a: mov rcx,[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword [0xF99FFA0] (vcall); [rbp+0x16D4]=al [V] — DIFF vs body A: body A stored flag at [rbp+0x16d0]; body C [rbp+0x16d4] (same as body B)
- u16 [rbp+0x15D8] pushed to pass+0x8A8 u16 pool; if pool full (rdx==[rbx+0x8B0]) goto 0x66F3FB8 (realloc); else [rdx]=ax; [rbx+0x8A8]+=2; jmp 0x66F3FCC [V] (matches body A u16 pool push)

SHIFT block fallthroughs:
- 0x66F320C ((isAB&[rbp+0x16CF])==0): test al,al; je 0x66F3379 (al==0 -> seasons/shared_ptr path 0x66F3379/0x66F339F -> 0x66F44BC/0x66F44A8 join); al!=0: cmp [rbp+0x1658],2; jne 0x66F3592; test bl,bl; je 0x66F3592 -> if class2&&valid: 0x67A75D0(&EA8) + 0x678F640(rcx=&1440, rdx=&1050, r8=&FF8, r9=rbx) + copy tail [r12+0x60..0x97]->staging [rbp+0x1578..] + u16 [rbp+0x10F8]->[rbp+0x15D0] + call 0x67A8030(rcx=&1440, stack [0x28]=&1448, [0x20]=&14D0, rdx=&15D0, r9=&1528) + 0x67E1840(&1440) + 0x67E23F0(&F70) + jmp 0x66F4E70 [V] — matches body A 0x66ecb30 (kind==2 && valid: 0x67a75d0 then 0x678f640) but body C uses same 0x67a75d0 binder here
- 0x66F332B (al==0 in shift block): [rbp+0x1370]=0; [rbp+0x1660]=0; if K==9 -> 0x66F3358; if K==5 -> 0x66F3358; else -> 0x66F36A8 [V] (matches body A seasons kind 9/5 path; then seasons shared_ptr [desc+0x28] lock inc)

### Step 3 (done): rdis dis 0x66F3420 300 -> 0x66F3420..~0x66F3AA0 (300 instr, cut at 66f3a9c)
Continuation of SHIFT block no-shift path (from 0x66F33C0): copy tail [r13+0x60..0x97] into [r12+0x60..0xA7], word [rbp+0x12B8]->[rbp+0x1108], release 0x67E23F0(r15), 0x678E420(&1440,&1060,&1008,&F80), copy back to rdi+0x164/0x174/0x183 (rdi=&rbp+0x1444), word [rbp+0x1108]->[rbp+0x15D8] [V] — identical skeleton to shift path's copy-back, staging base [rbp+0x1580]
- 0x66F3541..0x66F3567 call 0x67A7830(rcx=&1440, stack [0x28]=&1450, [0x20]=&14D8, rdx=&15D8, r9=&1530) [V] — DIFF vs body A: body A's second emit used 0x678DCE0 here (0x66ed973 area); body C uses 0x67A7830 for this path [need to confirm which path]
- release 0x67E1660(&1440), 0x67E1660(&F70) [V] (body A used 0x678E020/0x67E23F0; body C uses 0x67E1660 here) [DIFF]
- test bl,bl (valid); jne 0x66F4E70; jmp 0x66F4EB0 [V]
- 0x66F3592 (class2&&valid, al!=0, (isAB&[rbp+0x16CF])==0 branch): 0x67A75D0(&EA8) + 0x678F640(rcx=&1440, rdx=&1050, r8=&FF8, r9=r14) + copy tail [r12+0x60..0x97]->staging [rbp+0x1578..] + word [rbp+0x10F8]->[rbp+0x15D0] + call 0x67A8720(rcx=&1440, stack [0x28]=&1448, [0x20]=&14D0, rdx=&15D0, r9=&1528) + release 0x67E1840(&1440), 0x67E23F0(&F70) + test bl,bl; jne 0x66F4E70; jmp 0x66F4EB0 [V] — matches body A 0x66ecb30 class2 path; binder 0x67a75d0 (same as body A here)

K!=9/5 non-seasons path (from 0x66F320C al!=0 non-class2, or 0x66F332B al==0 K not 9/5):
- 0x66F36A8: stack args for 0x673CC80: [rsp+0x38]=[rbp+0x1370]; [rsp+0x30]=[rbp+0x1660]; [rsp+0x28]=ax=[rbp+0x1688] (render-state word); [rsp+0x20]=[rbp+0x16C0] (desc); [rsp+0x48]=0xFFFFFF00; [rsp+0x40]=0xFFFFFF00 [V]
- call 0x673CC80(rcx=&rbp+0x12E0 out, rdx=&rbp+0x1420 (vec1670[i] shared_ptr), r8d=byte [rbp+0x16D0] (byte16be FogAlpha-found flag), r9=-1) [V] — same r8d arg as body B (byte16be), DIFF vs body A (body A passed K=[rbp+0x16b0])
- 0x673CC80 result: 5 shared_ptr pairs lock-inc copied into [rbp+0x1390..0x13E8]: [rbp+0x12E8]->[rbp+0x1390]+[rbp+0x1398]; [rbp+0x1308]->[rbp+0x13B8]+[rbp+0x13C0]; [rbp+0x1318]->[rbp+0x13C8]+[rbp+0x13D0]; [rbp+0x1328]->[rbp+0x13D8]+[rbp+0x13E0](r14=[rbp+0x1330]); [rbp+0x1338]->[rbp+0x13E8] [V] — matches body A seasons shader-binding block (null branches zero the ptr)
- pair1 {u16,16-byte}: src=[rbp+0x12F0]; u16=[src+0x10]; dst=[rbp+0x13A0]; [dst+0x10]=u16; [dst..dst+0x10]=[src]; [dst+0x18..0x28]=0 [V] (matches body A phase 2)
- addss xmm12,xmm13 (z+=8.0f); addps xmm15,xmm14 ({a,b}+=8) SHIFT [V]; movlps [rbp+0x1120],xmm15; movss [rbp+0x1128],xmm12
- lea rcx,[rbp+0xEA8]; mov rdx,r15; call 0x67A75D0 [V] (binder 0x67a75d0, rdx=r15=&1130)
- lea rax,[rbp+0x1120]; [rsp+0x20]=rax; lea rbx,[rbp+0xF70]; rcx=rbx; rdx=r13 (descriptor); r8=[rbp+0x11B8]; r9=r15; call 0x678E1D0 [V]
- copy descriptor tail [r13+0x60..0x97] into [r12+0x60..0xA7]; word [rbp+0x12B8]->[rbp+0x1108]; release 0x67E23F0(r15); call 0x678DCE0(rcx=&1440, stack [0x28]=&1390, [0x20]=rbx=&F70, rdx=&1060, r8=&1008, r9=&F80) [V] — DIFF vs body A: body A used 0x678DCE0 here with stack args [0x28]=&1390, [0x20]=&F70; body C same callee 0x678dce0
- copy back: staging=[rbp+0x15E8]; [rcx+0x10]=[r12+0x70]; [rcx..]= [r12+0x60]; byte [rbp+0x15FC]=[rbp+0x10C4]; [rbp+0x1600..]=[rbp+0x10C8]; [rdi+0x1EB]=[r12+0xA7]; [rdi+0x1DC]=[r12+0x98]; [rdi+0x1CC]=[r12+0x88] [V] (staging base [rbp+0x15E8] vs body A [rbp+0x15e8] — same offset; rdi=&rbp+0x1444)
- word [rbp+0x1640]=[rbp+0x1108] [V]
- pass=0x5ABA5C0(frameCtx->+0x10+0x9D0) [V]; zero 12 DrawItem slots [r13-0xD8..r13-0x28] [V]; feature flag 0x4a vcall; [rbp+0x16D4]=al [V] (same local as body B)
- u16 [rbp+0x1640] pushed to pass+0x8A8 u16 pool; if full goto 0x66F3A2D (realloc via 0x1EF6F90(&rbx+0x8A0, &rbp+0x1640)); else [rdx]=ax; [rbx+0x8A8]+=2 [V] (matches body A u16 pool push; grow helper 0x1EF6F90 same as body A)
- flag restore vcall: rcx=[0x1233E1B0]; rax=[rcx+0x10]; dl=[rbp+0x16D4]; call qword [0xF99FFA0]; [rbp+0x16D4]=al [V]
- mov qword [rbp+0x1130],1 (kind-mask low word = 1) [V]
- eax=[rbx+0x8A8]-[rbx+0x8A0]; shr eax,1; dec eax; [rbp+0x1140]=ax (pool 0x8A8 item index = count/2-1) [V] (matches body A phase 9)
- flag restore vcall again; [rbp+0x16D4]=al [V]
- rdx=[rbx+0x758] (pool 0x750 cursor)... cut at 0x66F3A9C

### Step 4 (done): rdis dis 0x66F3A9C 300 -> 0x66F3A9C..~0x66F4058 (300 instr, cut at 66f4054)
Pool sequence after the u16 pool-0x8A8 push (matches body A skeleton; flag local is [rbp+0x16D4] throughout body C, vs body A [rbp+0x16D0]):
- pool 0x750 fast push: rdx=[rbx+0x758]; if rdx==[rbx+0x760] goto grow 0x66F3B28 (0x6760A80(&rbx+0x750, &rbp+0x15E8)); else copy staging rbp+0x15E8 (0x58 bytes): [rdx+0x10]=[rcx+0x10]; [rdx..]=[rcx]; byte [rdx+0x14]=[rbp+0x15FC]; float [rdx+0x18..0x24]=[rbp+0x1600..0x160C]; [rdx+0x28]=[rdi+0x1CC]; [rdx+0x38]=[rdi+0x1DC]; [rdx+0x47]=[rdi+0x1EB] (15 bytes); [rbx+0x758]+=0x58 [V] (rdi=&rbp+0x1444; staging base body C [rbp+0x15E8] vs body A [rbp+0x15e8] — same offset)
- flag restore vcall; eax=[rbx+0x758]-[rbx+0x750]; shr eax,3; imul eax,0xFFFF8BA3; dec eax; [rbp+0x115C]=ax (pool 0x750 item index) [V] — magic multiply 0xFFFF8BA3 same as body A
- pool 0x888 u16 push (inc): rdx=[rbx+0x890]; if rdx==[rbx+0x898] goto grow 0x66F3BAF (0x6760E60(&rbx+0x888)); else rdx++; [rbx+0x890]=rdx [V] (DIFF vs body A: body A pool 0x858 cursor at +0x860; body C = +0x890/0x898 — offset shifted by 0x30)
- mask word [rbp+0x1130]=0x4003 [V]; eax=[rbx+0x888]; not eax; add eax,[rbx+0x890]; [rbp+0x1142]=ax (item start index = ~begin+cursor) [V] — body A stored this at [rbp+0x1146]; body C at [rbp+0x1142] [offset diff]
- pool 0x648 u64 push: lea rcx,[rbx+0x648]; lea rdx,[rbp+0x1598]; call 0x675FB30 [V] (same helper as body A)
- pool 0x648 index: eax=[rbx+0x650]-[rbx+0x648]; shr 3; imul 0xFFFF8E39; dec; [rbp+0x1172]=ax [V] (same magic as body A)
- pool 0x780 u64 push: lea rcx,[rbx+0x780]; lea rdx,[rbp+0x1540]; call 0x675F3B0 [V]
- pool 0x768 index: eax=[rbx+0x788]-[rbx+0x780]; shr 3; imul 0xFFFF8BA3; dec; [rbp+0x1158]=ax [V] (magic 0xFFFF8BA3 same as body A's 0x750 magic)
- pool 0x770 u64 push (0x88 bytes): r15=[rbx+0x770]; if r15==[rbx+0x778] goto grow 0x66F3D01 (0x6760710(&rbx+0x768, rdx=r15, r8=&rbp+0x14B8)); else [r15]=[rbp+0x14B8]; 16-byte copy 0xE869FF0(rcx=r15+8, rdx=&rbp+0x14C0); [r15+0x80]=[rbp+0x1538]; [rbp+0x1538]=0; [rbx+0x770]+=0x88 [V] (pool entry size 0x88 same as body A; cursor field +0x770 same as body A)
- flag restore vcall; mask word [rbp+0x1130]=0x2007003 [V] (body A final mask was 0x4000000042807009 after 0x678d690; body C builds per-step: 0x4003 -> 0x2007003 here)
- pool 0x768 index: eax=[rbx+0x770]-[rbx+0x768]; shr 3; imul 0xFFFFF0F1; dec; [rbp+0x115A]=ax [V] (magic 0xFFFFF0F1 same as body A)
- pool 0x680 u24 push (3 floats): rdx=[rbx+0x680]; if rdx==[rbx+0x688] goto grow 0x66F3DBA (0x1770A70(&rbx+0x678, r8=&rbp+0x14A8)); else [rdx]=[rbp+0x14A8]; [rdx+4]=[rbp+0x14AC]; [rdx+8]=[rbp+0x14B0]; [rbx+0x680]+=0xC [V] (body A had byte pool 0x858 here via 0x6760e60; body C uses a float3 pool 0x680 with helper 0x1770A70 — DIFF)
- pool 0x678 index: eax=[rbx+0x680]-[rbx+0x678]; shr 2; imul 0xFFFFAAAB; dec; [rbp+0x116E]=ax [V] (divide by 4 = float3 stride)
- pool 0x2D0 u16 push (inc): rdx=[rbx+0x2D8]; if rdx==[rbx+0x2E0] goto grow 0x66F3E41 (0x6760E60(&rbx+0x2D0)); else rdx++; [rbx+0x2D8]=rdx [V] (matches body A pool 0x2d8)
- item start index: eax=[rbx+0x2D0]; not eax; add eax,[rbx+0x2D8]; [rbp+0x11BC]=ax [V] (matches body A ~[begin]+cursor)
- item emit: rcx=rbx+0x5D0 (frame_pass+0x5D0); lea rdx,[rbp+0x1440]; call 0x678D690 [V] (matches body A item emission into pass pool)
- mask word [rbp+0x1130]=0x4000000042807003 [V] — DIFF vs body A: body A final mask 0x4000000042807009; body C = ...7003 (low byte 0x03 vs 0x09) [V]
- pool 0x5D0 index: eax=[rbx+0x5D8]-[rbx+0x5D0]; shr eax,5; imul 0xFFFFAAAB; dec; [rbp+0x117C]=ax [V] (divide by 32 = 0x20-byte entries, same as body A)
- flag restore vcall; [rbp+0x16D4]=al [V]
- pool 8 u16 push 0xC8 bytes: rdx=[rbx+8]; if rdx==[rbx+0x10] goto grow 0x66F3F0B (0x5ABA6D0(rcx=rbx, r8=&rbp+0x1130)); else r8d=0xC8; rcx=rdx; rdx=&rbp+0x1130; call 0xEEC6EC0 (memcpy 0xC8); [rbx+8]+=0xC8 [V] (matches body A pool-8 push; body A grow helper 0x5ABA6D0 same)

Conditional free (byte [rbp+0x15D8]==1 && [rbp+0x1598]!=0):
- cmp byte [rbp+0x15D8],1; jne skip; rcx=[rbp+0x1598]; if rcx==0 skip; rdx=[rbp+0x15A8]-rcx (size); if rdx<0x1000 direct free path; else rax=[rcx-8] (heap header); rcx-=8; rcx-=rax; if rcx>=0x20 goto 0x66F82BB (out-of-range); rdx|=0x27; rcx=rax; call 0xE935700 (free) [V] (matches body A conditional free; body A checked byte [rbp+0x15c8]; body C checks [rbp+0x15D8] [offset diff])
- clear: lea rax,[rbp+0x1598]; movups [rax],xmm6; [rax+0x10]=0 [V]
- release draw item: rcx=&rbp+0x1440; call 0x678E020 [V] (body A used 0x678E020 here too)
- release geometry: rcx=&rbp+0xF70; call 0x67E1660 [V] (body A used 0x67E23F0; body C uses 0x67E1660 [DIFF])
- test r14,r14 (r14 = shared ctrl block saved from earlier); jne 0x66F4C4B; jmp 0x66F4C78 [V]

u16 pool-0x8A8 grow join (0x66F3FB8): lea rcx,[rbx+0x8A0]; r8=&rbp+0x15D8; call 0x1EF6F90; then fallthrough flag restore + mask word [rbp+0x1130]=1 + pool 0x8A8 index (count/2-1 -> [rbp+0x1140]) + flag restore + rdx=[rbx+0x758] (pool 0x750 cursor)... cut at 0x66F4054

### Step 5 (done): rdis dis 0x66F4054 300 -> 0x66F4054..~0x66F463E (300 instr, cut at 66f463a)
Second item emission (non-shader-binding path, same skeleton as body A's second emit; flag local [rbp+0x16D4]):
- pool 0x750 fast push: staging [rbp+0x1580] (DIFF vs first item's [rbp+0x15E8]); copy 0x58 bytes: [rdx+0x10]=[rcx+0x10]; [rdx..]=[rcx]; floats [rdx+0x18..0x24]=[rbp+0x1598..0x15A4]; [rdx+0x28]=[rdi+0x164]; [rdx+0x38]=[rdi+0x174]; [rdx+0x47]=[rdi+0x183]; [rbx+0x758]+=0x58; grow path 0x66F40B3 (0x6760A80(&rbx+0x750, &rbp+0x1580)) [V]
- flag restore vcall; pool 0x750 index (count/2-1, magic 0xFFFF8BA3) -> [rbp+0x115C] [V]
- pool 0x888 u16 push (inc); grow 0x66F413A (0x6760E60(&rbx+0x888)) [V]
- mask word [rbp+0x1130]=0x4003; item start index ~[rbx+0x888]+[rbx+0x890] -> [rbp+0x1142] [V]
- pool 0x648 u64 push source [rbp+0x1530] via 0x675FB30; pool 0x648 index -> [rbp+0x1172] [V]
- pool 0x780 u64 push source [rbp+0x14D8] via 0x675F3B0; pool 0x768 index (magic 0xFFFF8BA3) -> [rbp+0x1158] [V]
- pool 0x770 u64 push (0x88 bytes): [r14]=[rbp+0x1450]; 16-byte copy 0xE869FF0(r14+8, &rbp+0x1458); [r14+0x80]=[rbp+0x14D0]; [rbp+0x14D0]=0; [rbx+0x770]+=0x88; grow 0x66F428D (0x6760710(&rbx+0x768, r8=&rbp+0x1450)) [V]
- flag restore vcall; mask word [rbp+0x1130]=0x2007003; pool 0x768 index (magic 0xFFFFF0F1) -> [rbp+0x115A] [V]
- pool 0x680 float3 push: [rdx]=[rbp+0x1444]; [rdx+4]=[rbp+0x1448]; [rdx+8]=[rbp+0x144C]; [rbx+0x680]+=0xC; grow 0x66F4346 (0x1770A70(&rbx+0x678, r8=&rbp+0x1444)) [V] (first item used source [rbp+0x14A8..0x14B0]; second item = [rbp+0x1444..0x144C] [DIFF])
- pool 0x678 index (divide by 4, magic 0xFFFFAAAB) -> [rbp+0x116E] [V]
- pool 0x600 u16 push (inc): rdx=[rbx+0x608]; if ==[rbx+0x610] grow 0x66F43CD (0x6760E60(rcx=rbx+0x600)); else rdx++; [rbx+0x608]=rdx [V] — DIFF vs body A: body A pool 0x2d8 here; body C = +0x608/0x610 (offset shifted)
- mask word [rbp+0x1130]=0x12807003 [V]; eax=[rbx+0x600]; not eax; add eax,[rbx+0x608]; [rbp+0x1178]=ax [V] (body A stored ~[begin]+cursor at [rbp+0x11bc]; body C = [rbp+0x1178] [offset diff])
- flag restore vcall; pool 8 u16 push 0xC8 bytes (memcpy 0xEEC6EC0 from &rbp+0x1130; [rbx+8]+=0xC8; grow 0x5ABA6D0) [V]
- release geometry: rcx=&rbp+0xF70; call 0x67E1660; rcx=&rbp+0x1440; call 0x67E1660 [V] (body A used 0x678E020/0x67E23F0; body C uses 0x67E1660 for both [DIFF])
- jmp 0x66F4E70 [V]

Second seasons/shared_ptr path (from 0x66F3379/0x66F339F K==9/5 join, i.e. the K==9/5 path reached via the (isAB&[rbp+0x16CF])!=0 al==0 route):
- 0x66F44A8 xor eax,eax; mov rcx,[rax+0x20] (rax=0? actually rax=[rcx+0x28] was null so eax=0); [rbp+0x1660]=rcx; [rbp+0x1668]=rax(0) [V]
- 0x66F44BC stack args for 0x673CC80 (same as first seasons path): [rsp+0x38]=[rbp+0x1370]; [rsp+0x30]=[rbp+0x1660]; [rsp+0x28]=ax=[rbp+0x1688]; [rsp+0x20]=[rbp+0x16C0]; [rsp+0x48/0x40]=0xFFFFFF00 [V]
- call 0x673CC80(rcx=&rbp+0x12E0, rdx=&rbp+0x1420, r8d=byte [rbp+0x16D0], r9=-1) [V]
- 5 shared_ptr pairs copied into [rbp+0x1390..0x13E8] (same null-branch pattern as first path) [V]
- pair1 {u16,16-byte} from [rbp+0x12F0] into [rbp+0x13A0..0x13B0] [V]
- 0x66F4629 lea rcx,[rbp+0xEA8]; lea rbx,[rbp+0xF70]; mov rdx,rbx; call 0x67A75D0 [V] (binder 0x67a75d0, rdx=&F70) — cut at 0x66F463A

### Step 6 (done): rdis dis 0x66F463A 300 -> 0x66F463A..~0x66F4C0E (300 instr, cut at 66f4c0a)
Second seasons path (K==9/5 via (isAB&[rbp+0x16CF])!=0 al==0 route):
- call 0x67A75D0(rcx=&EA8, rdx=rbx=&F70) [V] (binder)
- lea rax,[rbp+0x1390]; [rsp+0x20]=rax; lea rcx,[rbp+0x1440]; mov rdx,r12 (descriptor); lea r8,[rbp+0xFF8]; r9=rbx=&F70; call 0x678EF40 [V] — DIFF vs body A: body A's second emit used 0x678DCE0 with stack args [0x28]=&1390, [0x20]=&F70; body C uses 0x678EF40 with rdx=r12, r8=&FF8, r9=rbx [need to confirm callee role; body A phase 5 used 0x678EF40 for geometry+material fill]
- copy descriptor tail: [rbp+0x15D8+0x10]=[r12+0x60]; [rbp+0x15D8..]=[r12+0x50]; byte [rbp+0x15EC]=[rbp+0x10B4]; [rbp+0x15F0..]=[rbp+0x10B8]; [rdi+0x1DB]=[r12+0x97]; [rdi+0x1CC]=[r12+0x88]; [rdi+0x1BC]=[r12+0x78]; word [rbp+0x1630]=[rbp+0x10F8] [V] (rdi=&rbp+0x1444; staging base [rbp+0x15D8] — same as body A phase 6 staging [rbp+0x15d8])
- pass=0x5ABA5C0(frameCtx->+0x10+0x9D0); zero 12 slots [r13-0xD8..r13-0x28] (r13=[rbp+0x1210] item base); feature flag 0x4a vcall; [rbp+0x16D4]=al [V]
- u16 [rbp+0x1630] pushed to pass+0x8A8 u16 pool; grow 0x66F477F (0x1EF6F90(&rbx+0x8A0, &rbp+0x1630)); else [rdx]=ax; [rbx+0x8A8]+=2 [V]
- flag restore vcall; mask word [rbp+0x1130]=1; pool 0x8A8 index (count/2-1) -> [rbp+0x1140]; flag restore vcall [V]
- pool 0x750 fast push: staging [rbp+0x15D8] (0x58 bytes: [rdx+0x10], [rdx..], byte [rdx+0x14]=[rbp+0x15EC], floats [rdx+0x18..0x24]=[rbp+0x15F0..0x15FC], [rdx+0x28]=[rdi+0x1BC], [rdx+0x38]=[rdi+0x1CC], [rdx+0x47]=[rdi+0x1DB]); [rbx+0x758]+=0x58; grow 0x66F487A (0x6760A80(&rbx+0x750, &rbp+0x15D8)) [V] — matches body A phase 10 exactly
- flag restore vcall; pool 0x750 index (magic 0xFFFF8BA3) -> [rbp+0x115C]; flag restore vcall [V]
- pool 0x888 u16 push (inc); grow 0x66F4901 (0x6760E60(&rbx+0x888)) [V]
- mask word [rbp+0x1130]=0x2005003; item start ~[rbx+0x888]+[rbx+0x890] -> [rbp+0x1142]; flag restore vcall [V]
- pool 0x648 u64 push source [rbp+0x1588] via 0x675FB30; pool 0x648 index (magic 0xFFFF8E39) -> [rbp+0x1172] [V]
- pool 0x780 u64 push source [rbp+0x1530] via 0x675F3B0 [V]
- mask word [rbp+0x1130]=0x2005003 again; pool 0x768 index (magic 0xFFFF8BA3) -> [rbp+0x115A] [V]
- pool 0x770 u64 push (0x88 bytes): [r15]=[rbp+0x14A8]; 16-byte copy 0xE869FF0(r15+8, &rbp+0x14B0); [r15+0x80]=[rbp+0x1528]; [rbp+0x1528]=0; [rbx+0x770]+=0x88; grow 0x66F4A53 (0x6760710(&rbx+0x768, r8=&rbp+0x14A8)) [V]
- flag restore vcall; pool 0x768 index (magic 0xFFFFF0F1) -> [rbp+0x115A]; flag restore vcall [V]
- pool 0x2D8 u16 push (inc); grow 0x66F4ADD (0x6760E60(&rbx+0x2D0)) [V]
- ~[rbx+0x2D0]+[rbx+0x2D8] -> [rbp+0x11BC]; item emit rcx=rbx+0x5D0 call 0x678D690(rdx=&rbp+0x1440) [V]
- mask word [rbp+0x1130]=0x4000000042007003 [V] — DIFF vs body A: body A final mask 0x4000000042007009; body C = ...7003 [low byte 0x03 vs 0x09]
- pool 0x5D0 index (shr 5, magic 0xFFFFAAAB) -> [rbp+0x117C]; flag restore vcall [V]
- pool 8 u16 push 0xC8 bytes (memcpy 0xEEC6EC0 from &rbp+0x1130; [rbx+8]+=0xC8; grow 0x5ABA6D0) [V]
- conditional free: cmp byte [rbp+0x15C8],1; jne 0x66F4C2E; rcx=[rbp+0x1588]; if rcx==0 goto 0x66F4C2E; rdx=[rbp+0x1598]-rcx; if rdx<0x1000 goto 0x66F4C17; else rax=[rcx-8]; rcx-=8; rcx-=rax; if rcx>=0x20 goto 0x66F82BB; rdx|=0x27; rcx=rax; call 0xE935700 (free) — cut at 0x66F4C0A [matches body A phase 27/28; body A checked byte [rbp+0x15c8] — SAME offset here]

### Step 7 (done): rdis dis 0x66F4C0A 300 -> 0x66F4C0A..~0x66F50C0 (300 instr, includes body C tail + body D start 0x66F4FC4+)
Body C tail (matches body A phases 27-32; flag local [rbp+0x16D4]):
- free: call 0xE935700; clear lea rax,[rbp+0x1588]; movups [rax],xmm6; [rax+0x10]=0 [V]
- release draw item: rcx=&rbp+0x1440; call 0x678F260 [V] — DIFF vs body A: body A used 0x678E020 here; body C uses 0x678F260
- release geometry: rcx=&rbp+0xF70; call 0x67E23F0 [V] (same as body A)
- test r14 (shared ctrl saved at 0x66F423C/0x66F49BD); jne 0x66F4C78; shared_ptr release sequence (lock dec [r14+8]; dtor [rax]; lock dec [r14+0xC]; dealloc [rax+8]) [V]
- shared_ptr releases in order: [rbp+0x13D0] (0x66F4C78), [rbp+0x13C0] (0x66F4CAF), [rbp+0x1398] (0x66F4CE6), [rbp+0x1330] (0x66F4D1D), [rbp+0x1320] (0x66F4D54), [rbp+0x1310] (0x66F4D8B), [rbp+0x12E8] (0x66F4DC2), [rbp+0x1668] (0x66F4DF9), [rbp+0x1378] (0x66F4E30; then jmp 0x66F4E70) [V] — matches body A phase 28/29 release set exactly (same offsets)
- [rbp+0x1428] release (0x66F4E70) [V] — matches body A
- conditional release: cmp byte [rbp+0xDF0],3; jne 0x66F4EF0; rbx=[rbp+0xDE8]; if 0 goto 0x66F4EF0; shared_ptr release sequence (0x66F4EB9..0x66F4EEA) [V] — matches body A phase 29 ([rbp+0xde8], feature/check byte [rbp+0xDF0])
- cleanup loop 1 over [rbp+0xDC0]..[rbp+0xDC8] step 0x28: r14=[rbp+0xDC0]; if 0 goto 0x66F2D00 (pass-2 continuation in body A earlier part [I]); r15=[rbp+0xDC8]; loop_top: if r14==r15 goto 0x66F2D00; cmp byte [r14+0x18],2; jne skip (only type-2 entries); rbx=[r14+8]; if 0 goto skip; shared_ptr release; r14+=0x28; goto loop_top [V] — matches body A phase 30 exactly (jump target 0x66F2D00 = body A pass-2 loop re-entry [I])
- TAIL PHASE (body C phase 31 equivalent, starts at body C end boundary 0x66F4F5A): rsi=[rbp+0x1670]; if rsi==0 goto 0x66F6E3B (body C epilogue [I]); rbx=[rbp+0x1678]; if rsi!=rbx goto 0x66F4F88 (work remains -> loop body beyond body C end); goto 0x66F6E04 (no work -> epilogue [I]) [V] 0x66F4F5A..0x66F4F76. Matches body A phase 31 (0x66EF25A..0x66EF28d) exactly; loop body at 0x66F4F88 (step 0x18, checks byte [rsi+0x10]==1, shared_ptr release of [rsi+8]) is beyond body C's stated end boundary 0x66F4F5A [I].

Body C end boundary: 0x66F4F5A [V per map]. At 0x66F4FC4 `mov byte [rbp+0x16BE],0` then 0x66F4CB begins body D (clone pass record) — not part of body C.

Body C FULLY DECODED: 0x66F2820..0x66F4F76 (instruction-complete through tail phase setup; loop bodies at 0x66F4F88/0x66F6DFD/0x66F6E3B/0x66F6E04 are beyond unit range per map).

## DIFFERENCES body C vs body A (summary)
1. Prologue kind-class: body C default v=9, K==0xA->v=2, else v=class; NO f16cf re-check [V] (same skeleton as body B; body A: `if (f16cf && K != 0xC) v=2; else if K!=0xA v=...; else v=(K==0xC)?9:0`)
2. [rbp+0x1658]=K&~1 vs body A [rbp+0x1658]=&desc[+0x78] [V] (same as body B)
3. Draw-list builder arg3: body C [rbp+0x1698] vs body A [rbp+0x1388]=fogA [V] (same as body B; meaning ?)
4. vec1670 fetch identical (stride 0x18, valid +0x10) [V]
5. Pack order [rbp+0xea8]: body C {&1410, model, drawlist, rec} vs body A {&1650,model,drawlist,&1120} [V offsets differ]
6. Binder for matrix-copy: body C calls 0x67A75D0 in ALL matrix-copy paths (shift, no-shift, class2) [V] — body A used 0x67a75d0 too here; body B used 0x678cf10 [body C == body A for this callee]
7. Item emit tail callee: body C uses 0x678EF40 for the non-shader-binding item (second emit) vs body A 0x678DCE0 [V] (body B also used 0x678f640/0x67a75d0 mix)
8. Release callees: body C uses 0x67E1660 for geometry+item destroy (second emit) vs body A 0x67E23F0/0x678E020; body C uses 0x678F260 for draw-item destroy (tail) vs body A 0x678E020 [V]
9. Feature flag local: body C [rbp+0x16D4] vs body A [rbp+0x16D0] [V] (same as body B)
10. Item staging bases: body C [rbp+0x1580]/[rbp+0x15D8]/[rbp+0x15E8] vs body A [rbp+0x1578]/[rbp+0x15d8]/[rbp+0x15e8] [V offsets differ by 0x8/0x10]
11. Pool field offsets shifted vs body A: body C pool 0x888 cursor at +0x890/0x898 (body A 0x858 at +0x860/0x868); pool 0x770 cursor +0x770 (same); pool 0x680 float3 pool (body A had byte pool 0x858); pool 0x600 u16 push (body A pool 0x2D8) [V]
12. Mask words: body C builds per-step 0x4003 -> 0x2007003 -> 0x12807003 (second items) / 0x2005003 (first item non-seasons); final mask 0x4000000042007003 vs body A 0x4000000042007009 [V] (low byte 0x03 vs 0x09)
13. Conditional free byte: body C [rbp+0x15C8] == body A [rbp+0x15C8] (same) [V]; free size field [rbp+0x15A8]-[rbp+0x1598] same
14. shared_ptr release set identical offsets to body A ([rbp+0x13D0/0x13C0/0x1398/0x1330/0x1320/0x1310/0x12E8/0x1668/0x1378/0x1428]) [V]
15. Cleanup loops identical to body A ([rbp+0xDC0]/[rbp+0xDC8] step 0x28 type-2; [rbp+0x1670]/[rbp+0x1678] step 0x18) [V]

Open: meaning of [rbp+0x16CF], [rbp+0x1370], [rbp+0x1698]; jump targets 0x66F6DFD/0x66F6E04/0x66F6E3B/0x66F2D00 are outside body C (body A earlier parts / epilogue) [I].

## NEXT
Body C complete through 0x66F4F76 (tail phase setup). Nothing remaining in this unit per map boundary 0x66F4F5A. Unit done.

## Status
- Dossier 66ea3d0.md: body C decoded 0x66F2820..0x66F4F76 (instruction-complete through tail phase setup; loop bodies beyond unit range).
- Disassembly: dumped ~2750 instructions across 7 rdis dis calls (300 instr each).
- Phases transcribed: preamble + pass-1 resolve loop + pass-2 setup/loop + both item emissions + full pool sequence + releases + cleanup loops + tail phase.
- Tags: [V] = seen in disassembly at cited RVA; [I] = inferred; [?] = unknown.
