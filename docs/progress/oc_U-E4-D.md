# Unit U-E4-D: ChunkGeometry extractor body D (0x66f4fcb..0x66f6e36)

## Status
BODY D COMPLETE — full range 0x66f4fcb..0x66f6e36 decoded instruction-complete.
- Body A = 0x66ec126..0x66ef28d (generic kinds)
- Body B = 0x66ef308..0x66f2817 (K==13 light_source, f16cf path)
- Body C = 0x66f2820..0x66f4f5a (f1658 set)
- Body D = 0x66f4fcb..0x66f6e36 (K==10 terrain_blend)

Source: static disassembly of 1.26.62.01 via `tools/rdis/target/release/rdis.exe` (dis cmd). Tags: [V] read in disassembly, [I] inferred, [?] unknown.
Task: decode body D instruction-complete where feasible; for each phase note differences from body A (docs/progress/oc_U-E4-A2.md phases 1-31).
EXE: C:\Users\Atomi\AppData/Local/LeviLauncher/Instances/1.26.62.01\Minecraft.Windows.exe 1.26.62.01. Static analysis only.
All 9 steps complete: 0x66f4fcb..0x66f557a (Step 1), 0x66f53a8..0x66f5a13 (Step 2), 0x66f5a14..0x66f60ab (Step 3), 0x66f60ab..0x66f6655 (Step 4), 0x66f6655..0x66f6b82 (Step 5), 0x66f6b82..0x66f6e36 (Step 6), plus sub_66f70a1 (Step 7), sub_66f77bc (Step 8), sub_66f7eba (Step 9 — separate property-registration functions reached from epilogue area).

## NEXT
None — unit complete. Body D fully decoded through 0x66f6e36.

## Disassembly log
### Step 1 (done): rdis dis 0x66f4fcb 300 -> 0x66f4fcb..~0x66f5577 (300 instr)
Prologue (matches body A/B skeleton):
- 0x66f4fcb mov rax,[rbp+0xEE8]; mov [rbp+0xC78],rax; lea rcx,[rbp+0xC80]; lea rdx,[rbp+0xEF0]; call 0xE86B370 (clone pass record); [rbp+0xCF8]=0 [V] (matches body B 0x66ef308 prologue; body A similar)
- 0x66f4fff mov rax,[rbx+0x48]; mov rdx,[rax] (K value) [V]
- fogA = ((K-5)&~4)==0 via `lea rax,[rdx-5]; test rax,0x...FB; sete r12b` [V] (matches body A/B)
- 0x66f5016 cmp rdx,0xA; je 0x66f5049 -> if K==0xA: [rbp+0x16D4]=2 [V]
- 0x66f501c mov byte ptr [rbp+0x16D4],9 (default v=9) [V]
- 0x66f5023 cmp rdx,0xC; je 0x66f5050 (K==0xC skips class compute) [V]
- 0x66f5029 lea rax,[rdx-7]; cmp rax,3; setb al -> (K-7)<3, K in {7,8,9} [V]
- 0x66f5034 lea rcx,[rdx-0xF]; cmp rcx,2; setb cl -> (K-0xF)<2, K in {0xF,0x10} [V]
- 0x66f503f or cl,al; 0x66f5041 mov [rbp+0x16D4],cl -> v = kind class [V]
- 0x66f5047 jmp 0x66f5050
loc_66f5049: 0x66f5049 mov byte ptr [rbp+0x16D4],2 [V]
loc_66f5050: 0x66f5050 mov [rbp+0x1698],rdx (rdx = K, saved) [V]
- 0x66f5057 xorps xmm0,xmm0; [rbp+0x1670]=0; [rbp+0x1680]=0 -> vec1670 vector init (shared_ptr{ptr,ctrl}+valid) [V] (matches body A/B vec1670)
- 0x66f506c mov rax,[rbx+0x38] = n (desc+0x38 count); [rbp+0x1440]=rax; test rax,rax; je 0x66f50a3 [V] (matches body A/B n=desc+0x38)
- 0x66f507c mov rcx,0xAAAAAAAAAAAAAAB; cmp rax,rcx; jae 0x66f942b (throw if n huge) [V] (matches body A/B)
- 0x66f508f lea rcx,[rbp+0x1670]; lea rdx,[rbp+0x1440]; call 0x678d170 (reserve n) [V] (matches body A/B)
loc_66f50a3: 0x66f50a3 lea rsi,[r13+0x2E8]; mov rcx,rsi; call 0xEEC59F0 (lock builder+0x2e8 mutex); test eax,eax; jne 0x66f9346 [V] (matches body A/B lock)
- 0x66f50ba mov [rbp+0x1690],rsi (mutex addr saved); cmp dword [r13+0x334],0x7FFFFFFF; je 0x66f9351 (recursion-limit throw) [V] (matches body A/B)
- 0x66f50d2 mov rax,[rbx+0x38] = draw-list begin; test rax,rax; je 0x66f5289 [V] (matches body A/B)
- 0x66f50df mov rcx,[rbp+0x16C0]; mov rsi,[rcx+0x40] (desc+0x40 = draw-list begin base); imul r13,rax,0x58; add r13,rsi -> end = begin + n*0x58 [V] (matches body A/B stride 0x58)
- 0x66f50f1 lea rbx,[rbp+0x1440]; lea r14,[rbp+0x1670]; xorps xmm6,xmm6; jmp 0x66f5111 -> pass-2 loop entry setup [V]

Pass-1 loop (rsi=entry ptr, r13=end):
- 0x66f5111 movzx eax,byte [rsi+0x28] (entry tag); test; je 0x66f5128 (tag==0 -> p=rsi+0x10); cmp eax,1; jne 0x66f8869 (throw); else p=rsi+0x18 [V] (matches body A/B tag 0->e+0x10, tag 1->e+0x18)
- mov rax,[rax]; test rax,rax; je 0x66f5104 skip (null pointer) [V]
- rcx=[rbp+0x16A0] (builder state); rdx=[rcx+0x2D8] (map header); r8=[rdx+8] (root); cmp byte [r8+0x19],0 (isnil) [V]
- rb-tree walk: r9=[rax]; cmp [r8+0x20],r9; setl r10b; cmovge rcx,r8; shl r10d,4; r8=[r8+r10]; loop until [r8+0x19]!=0 [V] (matches body A/B)
- cmp byte [rcx+0x19],0; jne skip; cmp rcx,rdx; je skip; rdx=[rcx+0x20] (node key); cmp [rax],rdx; jl skip; r12=[rcx+0x28] (node value); test r12,r12; je skip (!value) [V] (matches body A/B)
- rcx=[rbp+0x16C0] (desc); movzx eax,byte [rax+0x50] (desc+0x50 flag); r8=[rax+0x48] (desc+0x48 kind ptr); rdx=rbx; call 0xBB3CCC0 (&out, node.value+8, {K, flag50}) -> lookup (kind,flag50)->shared_ptr pair [V] (matches body A/B 0xbc090b0; body D uses 0xbb3ccc0)
- 0x66f51bf rdx=[rbp+0x1678]; cmp rdx,[rbp+0x1680]; je 0x66f51ff (vec1670 full) [V] (matches body A/B vec1670 push; stride 0x18, valid +0x10)
- if not full: byte [rdx+0x10]=0; cmp byte [rbp+0x1450],1; jne 0x66f5227; else movups [rdx],xmm6; rax=[rbp+0x1448]; if rax: lock inc [rax+8]; rcx=rax; rdx=[rbp+0x1678]; jmp 0x66f5212 [V] (matches body A/B shared_ptr copy path)
- loc_66f5212: r8=[rbp+0x1440]; [rdx]=r8 (ptr); [rdx+8]=rcx (ctrl); byte [rdx+0x10]=1 (valid); rdx=rax [V]
- loc_66f5227: rdx+=0x18; [rbp+0x1678]=rdx [V]
- cmp byte [rbp+0x1450],1; jne 0x66f5104 (skip dedupe/free if not condition); r15=[rbp+0x1448]; test r15,r15; je skip; lock dec [r15+8]; jne skip; dtor+dealloc via [0xF99FFA0] x2 [V] (matches body A/B shared release on dedupe)
- loop continue: 0x66f5104 add rsi,0x58; cmp rsi,r13; je 0x66f5289 [V]

loc_66f5289 (pass-2 setup):
- 0x66f5289 mov rax,[rbp+0x1698] (K saved); and rax,0x...FE (K&~1); [rbp+0x16A0]=rax [V] — DIFF vs body A: body A [rbp+0x1658]=&desc[+0x78]; body D = K&~1 (same as body B)
- 0x66f529b mov rcx,[rbp+0x1690]; call 0xEEC5A10 (unlock builder mutex) [V] (matches body A/B unlock)
- r14=[rbp+0x16C0] (desc); rsi=[r14+0x40] (draw-list begin); imul rax,[r14+0x38],0x58; add rax,rsi -> end; [rbp+0x1690]=end [V] (matches body A/B end=begin+n*0x58; body D uses rsi as iterator, [rbp+0x1690] as end)
- 0x66f52c1 lea rax,[r14+0x78]; [rbp+0x1658]=rax (&desc+0x78 material instance) [V] — DIFF vs body B ([rbp+0x1658]=K&~1); matches body A ([rbp+0x1658]=&desc[+0x78])
- 0x66f52cc xor eax,eax; movzx ecx,byte [rbp+0x16D4] (v=kind class); cmp cl,2; sete al; shl eax,0xB; cmp cl,9; mov ecx,0x2800; cmovne ecx,eax -> class word = v==9?0x2800 : v==2?0x800:0 [V] (matches body A/B exactly)
- 0x66f52e9 mov dil,r12b (dil=fogA); lea eax,[rcx+rdi*4+0x8101]; [rbp+0x16D0]=eax -> render-state word = 0x8101 + fogA*4 + classword [V] (matches body A/B exactly)
- 0x66f52f9 lea r15,[rbp+0x1140]; lea r12,[rbp+0x1050]; xorps xmm6,xmm6; constants xmm7=1.0f, xmm8=xmm11={0,0.0078125}, xmm9={-0,-0,0,0}, xmm10=1.0f, xmm13=8.0f, xmm14={8,8,0,0} [V] (matches body A/B loop constants exactly)
- jmp 0x66f5374 -> pass-2 loop entry

Pass-2 loop entry (rsi=entry, end=[rbp+0x1690], exit 0x66f6d9a):
- 0x66f5374 cmp rsi,[rbp+0x1690]; je 0x66f6d9a [V]
- 0x66f5381 movzx eax,byte [rsi+0x28] (tag); test; je 0x66f539e (tag0->p=rsi+0x10); cmp eax,1; jne 0x66f8788 (throw); else p=rsi+0x18; cmp [rax],0; jne process; je skip [V] (matches body A/B tag/null handling)
- loc_66f539e/loc_66f53a2: p=rsi+0x10; cmp [rax],0; je skip [V]

--max 300 (stopped at 0x66f53a6 je short 0x66f5370)

### Step 2 (done): rdis dis 0x66f53a8 300 -> 0x66f53a8..~0x66f5a13 (300 instr)
Transform + draw-list builder + per-entry branch:
- 0x66f53a8 movsd xmm15,[rsi+0x3C] (z); mov dword [rbp+0x1440],0x3F800000 (1.0f); zero [rbp+0x1444]/[rbp+0x1454] [V] (matches body A/B T-matrix build start)
- build translation T matrix via mulps/shufps/addps/unpcklps (xmm0..xmm3) = translate(a,b,z); [rbp+0x1468], [rbp+0x1478] store T [V]; movss xmm12,[rsi+0x44] (z) [V] (matches body A/B exactly)
- 0x66f5427 mov rcx,rbx (model=[rbp+0xE10]); mov rdx,[rbp+0x1658] (&desc+0x78); lea r8,[rbp+0x1440] (&T); call 0xAA6580 (model = descMat * T) [V] (matches body A/B 0xaa6580)
- 0x66f543e movss xmm0,[rsi+0x48] (scale); ucomiss xmm0,xmm10 (1.0f); jne 0x66f544f; jnp 0x66f54df [V]
- loc_66f544f (scale != 1): build scale matrix S; [rbp+0x1440]/[rbp+0x1444]/[rbp+0x1454]/[rbp+0x1458]/[rbp+0x1468]/[rbp+0x1478] = S [V]; 0x66f5490 lea rcx,[rbp+0xF70]; rdx=rbx; r8=[rbp+0x1440]; call 0xAA6580 (model = model * S) [V]; copy [rbp+0xF70..0xFA0] -> [rbp+0xE10..0xE40] (model back) [V]
- loc_66f54df: rax=[rbp+0x16A8] (ctx); rdx=[rax]; [rsp+0x20]=rsi; lea rcx,[rbp+0xDB8] (drawlist); r8=[rbp+0x1388]; lea r9,[rbp+0xEE8] (pass record); call 0x678C4C0 (draw-list builder) [V] (matches body A/B; body B used r8=[rbp+0x1698], body D uses r8=[rbp+0x1388]=&desc+0x78)
- 0x66f5509 lea rax,[rbp+0xC78]; [rbp+0x1650]=rax (rec_c78 cloned pass record) [V] (body A used [rbp+0x1120]; body B [rbp+0x1650]=rec_c78 — matches body B)
- 0x66f5517 cmp byte [rbp+0x16BE],1 (FogAlpha binding found); jne 0x66f557a skip [V] (matches body A/B)
- per-entry FogAlpha: movss xmm0,[rsi+0x4C]; xorps; ucomiss; jbe skip; shufps; [rbp+0x1440]=xmm0; [rbp+0xF70]=1; [rbp+0xF78]=&rbp+0x1440; lea rcx,[rbp+0xEF0]; lea rdx,[rbp+0x16BC]; lea r8,[rbp+0xF70]; call 0x5679DB0 (write FogAlpha) [V]; [rbp+0x1650]=[rbp+0xEE8] (rec_ee8) [V] (matches body A/B per-entry FogAlpha; body B used [rbp+0x1650]=&rbp+0xEE8, body A used [rbp+0x1120])

vec1670 fetch + class2/split:
- 0x66f557a lea rax,[rbp+0x1410]; [rbp+0xEA8]=rax (&rbp+0x1410); [rbp+0xEB0]=rbx (model); [rbp+0xEB8]=[rbp+0xDB8] (drawlist); [rbp+0xEC0]=[rbp+0x1650] (rec) — pack order {&1410, model, drawlist, rec} [V] — DIFF vs body A {&1650,model,drawlist,&1120} vs body B {&1370,model,drawlist,rec}
- 0x66f55ab rax=[rbp+0x1670] (vec1670 base); lea rcx,[rdi+rdi*2] (i*3); byte [rbp+0x1430]=0 (valid=0); movzx ebx,byte [rax+rcx*8+0x10] = valid byte (stride 0x18, +0x10) [V] (matches body A/B vec1670[i] valid +0x10)
- cmp bl,1; jne loc_66f55ff (if valid!=1 skip shared copy) [V]
- if valid: rax=[rax+rcx*8]; movaps [rbp+0x1420],xmm6 (zero); rcx=[rax+8] (ctrl); if rcx: lock inc [rcx+8]; rcx=[rax+8]; jmp; else ecx=0 [V]; mov rax,[rax] (ptr); [rbp+0x1420]=rax; [rbp+0x1428]=rcx; byte [rbp+0x1430]=1 (valid) [V] (matches body A/B shared_ptr copy into [rbp+0x1420..0x1430])

loc_66f55ff (split on ([rbp+0x16CF] & isAB)):
- cmp qword [rbp+0x16A0],2; sete cl -> cl = (K&~1 == 2) i.e. class2 flag [V]
- mov eax,ebx (valid); xor al,1 (!valid); or al,cl -> al = !valid || class2 [V]
- movzx ecx,byte [rbp+0x1368] (isAB); test [rbp+0x16CF],cl; je 0x66f5819 (if (isAB & [rbp+0x16CF])==0 goto alt branch) [V] — [rbp+0x16CF] meaning ?
- test al,al; je 0x66f593f (if al==0 i.e. valid&&!class2 goto no-shift path) [V]

SHIFT BLOCK ((isAB & [rbp+0x16CF])!=0 && al!=0):
- 0x66f562b addss xmm12,xmm13 (z+=8.0f); addps xmm15,xmm14 ({a,b}+=8) [V] — matches body A/B shift variant
- cmp qword [rbp+0x16A0],2; jne loc_66f59bf; test bl,bl; je loc_66f59bf -> if class2 && valid: matrix-copy path [V]
- loc_66f564a: movlps [rbp+0x1390],xmm15; movss [rbp+0x1398],xmm12 (store shifted vec2/float) [V]
- lea rcx,[rbp+0xEA8]; mov rdx,r13; call 0x67A75D0 (binder, same as body A 0x67a75d0) [V] — DIFF vs body B (body B used 0x678cf10 here)
- lea rbx,[rbp+0xF70]; lea rax,[rbp+0x1390]; [rsp+0x20]=rax; rcx=rbx; lea rdx,[rbp+0x1210]; lea r8,[rbp+0x11B8]; r9=r13; call 0x678e1d0 [V] (matches body A/B 0x678e1d0)
- copy descriptor tail: [r12+0x70]=[r15+0x130]; movups [r12+0x60]=[r15+0x120]; byte [rbp+0x10C4]=[rbp+0x1274]; movups [rbp+0x10C8]=[rbp+0x1278]; movups [r12+0x88]=[r15+0x148]; [r12+0x98]=[r15+0x158]; movups [r12+0xA7]=[r15+0x167] (unaligned 15 bytes) [V]; u16 [rbp+0x1108]=[rbp+0x12B8] [V] — matches body A copy into staging rbp+0x1578.. (body D staging base [rbp+0x1580] via r12=[rbp+0x1050])
- call 0x67e23f0(rcx=r13) release shared [V]; call 0x678e420(rcx=[rbp+0x1440]=model, rdx=[rbp+0x1060], r8=[rbp+0x1008], r9=[rbp+0xF80]) [V] (matches body A/B)
- copyback into staging [rbp+0x1580]: [r8+0x10]=[r12+0x70]; movups [r8]=[r12+0x60]; al=[rbp+0x10C4]->[rbp+0x1594]; movups [rbp+0x1598]=[rbp+0x10C8]; movups [rbp+0x15A0..]=[r12+0x88/0x98/0xA7]; u16 [rbp+0x15D8]=[rbp+0x1108] [V] — matches body A copy-back; staging base [rbp+0x1580] vs body A [rbp+0x1578]
- 0x66f57b8 rax=[rbp+0x16A8]; rcx=[rax+0x10] (ctx->+0x10); eax=0x9D0; add rcx,rax -> pass object [V]; stack args [rsp+0x30]=[rbp+0x1444], [rsp+0x28]=[rbp+0x1450], [rsp+0x20]=[rbp+0x14D8]; lea rdx,[rbp+0x15D8]; lea r9,[rbp+0x1530]; call 0x67b1a70 [V] — NEW callee vs body A (body A used 0x5aba5c0(frame)->+0x10+0x9d0 then flag vcall; here direct 0x67b1a70 with stack block) [? need to verify what 0x67b1a70 does]
- lea rcx,[rbp+0x1440]; call 0x67e1660 (destroy geometry) [V]; lea rcx,[rbp+0xF70]; call 0x67e1660 (destroy geometry) [V] — DIFF vs body A (body A called 0x678e020 destroy item + 0x67e1660 destroy geometry; here 0x67e1660 twice)
- jmp 0x66f6cc0 -> join point [V]

loc_66f5819 ((isAB & [rbp+0x16CF])==0 alt branch):
- test al,al; je 0x66f597f (al==0 -> seasons path) [V]
- cmp qword [rbp+0x16A0],2; lea rdx,[rbp+0xF70]; jne loc_66f5b8e; test bl,bl; je loc_66f5b8e -> if class2 && valid: 0x67a75d0(rcx=&EA8, rdx=rbx=[rbp+0xF70]) + 0x678f640(rcx=[rbp+0x1440], rdx=[rbp+0x1050], r8=[rbp+0xFF8], r9=rbx) + copy tail [r12+0x50..0x97]->staging [rbp+0x1578] + u16 [rbp+0x15D0]=[rbp+0x10F8] + call 0x67b3180(...) + 0x67e1840 + 0x67e23f0 + jmp 0x66f6cc0 [V] — matches body A 0x66ecb30 (kind==2 && valid: binder then 0x678f640) but binder=0x67a75d0 (matches body A here); staging base [rbp+0x1578]

loc_66f597f (al==0, valid&&!class2, alt branch):
- movaps [rbp+0x12E0],xmm6; movaps [rbp+0x1370],xmm6 (zero) [V]
- cmp qword [rbp+0x1698],9; je loc_66f59a5; cmp qword [rbp+0x1698],5; jne loc_66f67de -> if K==9 or K==5: seasons shared_ptr [r14+0x28] lock inc [V] (matches body A/B seasons kind 9/5 path) -> loc_66f67cc/0x66f67ca

loc_66f59bf (shift block, not (class2&&valid)):
- movlps [rbp+0x1390],xmm15; movss [rbp+0x1398],xmm12; call 0x67a75d0(rcx=&EA8, rdx=r13) binder (NO shift applied to stored values? actually shift already applied to xmm15/xmm12 above) [V]; lea r14,[rbp+0xF70]; ... call 0x678e1d0(...) [V] — continues at 0x66f5a0d

--max 300 (stopped at 0x66f5a0d mov eax,[r15+0x130])

### Step 3 (done): rdis dis 0x66f5a14 300 -> 0x66f5a14..~0x66f60ab (300 instr)
Continuation of loc_66f59bf path (shift applied, not class2&&valid) + loc_66f5cab seasons path:
- copy tail (same as loc_66f5698 path): [r12+0x70]=[r15+0x130]; movups [r12+0x60]=[r15+0x120]; byte [rbp+0x10C4]=[rbp+0x1274]; movups [rbp+0x10C8]=[rbp+0x1278]; movups [r12+0x88]=[r15+0x148]; [r12+0x98]=[r15+0x158]; movups [r12+0xA7]=[r15+0x167]; u16 [rbp+0x1108]=[rbp+0x12B8] [V]
- call 0x67e23f0(rcx=r13) release shared [V]; call 0x678e420(rcx=[rbp+0x1440]=model, rdx=[rbp+0x1060], r8=[rbp+0x1008], r9=[rbp+0xF80]) [V]
- copyback into staging [rbp+0x1580] (same layout) [V]
- 0x66f5b2d rax=[rbp+0x16A8]; rcx=[rax+0x10]; eax=0x9D0; add rcx,rax -> pass object; stack [rsp+0x30]=[rbp+0x1444], [rsp+0x28]=[rbp+0x1450], [rsp+0x20]=[rbp+0x14D8]; lea rdx,[rbp+0x15D8]; lea r9,[rbp+0x1530]; call 0x67b2260 [V] — NEW callee (shift path uses 0x67b2260; the class2&&valid alt path at 0x66f58e3 used 0x67b3180; the loc_66f5b8e alt-class2 path uses 0x67b3870) [?]
- lea rcx,[rbp+0x1440]; call 0x67e1660; lea rcx,[rbp+0xF70]; call 0x67e1660 (destroy geometry x2) [V]
- jmp loc_66f5c8a [V]

loc_66f5b8e (alt class2&&valid path from loc_66f5819):
- 0x67a75d0(rcx=&EA8, rdx=r14=[rbp+0xF70]) binder; 0x678f640(rcx=[rbp+0x1440], rdx=[rbp+0x1050], r8=[rbp+0xFF8], r9=r14) [V]; copy tail [r12+0x50..0x97]->staging [rbp+0x1578]; u16 [rbp+0x15D0]=[rbp+0x10F8]; call 0x67b3870(...) + 0x67e1840 + 0x67e23f0 -> loc_66f5c8a [V]

loc_66f5c8a (join from both alt paths):
- test bl,bl (valid); jne loc_66f6cc0; jmp loc_66f6cf7 [V]

loc_66f5c97 (seasons null path from loc_66f5965/0x66f59a5 when [r14+0x28]==0):
- xor eax,eax; rcx=[r14+0x20]; [rbp+0x1660]=rcx; [rbp+0x1668]=rax=0 [V]

loc_66f5cab (seasons path, al==0 valid&&!class2, K==9 or K==5):
- lea rax,[rbp+0x1370]; [rsp+0x38]=rax; lea rax,[rbp+0x1660]; [rsp+0x30]=rax; mov eax,[rbp+0x16D0]; [rsp+0x28]=ax (render-state word low); [rsp+0x20]=r14; [rsp+0x48]=0xFFFFFF00; [rsp+0x40]=0xFFFFFF00; lea rcx,[rbp+0x12E0] (out); lea rdx,[rbp+0x1420] (vec1670[i] shared_ptr); movzx r8d,byte [rbp+0x16D4] (fogA-found flag); r9=-1; call 0x673cc80 [V] — same 0x673cc80 as body A season path; r8d=byte16d4 (body D) vs body A r8d=K [V] (re-verify body A)
- 0x673cc80 result: 5 shared_ptr pairs lock-inc copied into [rbp+0x1390..0x13e8]: pair0 [rbp+0x12E8]->[rbp+0x1390]+[rbp+0x1398]; pair1 {u16,16-byte} [rbp+0x12F0]->[rbp+0x13A0] (word +0x10, 16 bytes +0x00, zero +0x18); pair2 [rbp+0x1310]->[rbp+0x13B8]+[rbp+0x13C0]; zero [rbp+0x13A0+0x28], [rbp+0x13A0+0x38]; pair3 [rbp+0x1320]->[rbp+0x13C8]+[rbp+0x13D0]; pair4 [rbp+0x1330]->[rbp+0x13D8]+[rbp+0x13E0], [rbp+0x13E8]=[rbp+0x1338] [V] — matches body A phases 2-4 exactly
- addss xmm12,xmm13 (z+=8.0f); addps xmm15,xmm14 ({a,b}+=8) SHIFT [V]; movlps [rbp+0x1120],xmm15; movss [rbp+0x1128],xmm12 [V]
- lea rcx,[rbp+0xEA8]; mov rdx,r13; call 0x67a75d0 (binder) [V]; lea rax,[rbp+0x1120]; [rsp+0x20]=rax; lea r14,[rbp+0xF70]; rcx=r14; rdx=[rbp+0x1210]; r8=[rbp+0x11B8]; r9=r13; call 0x678e1d0 [V]
- copy tail [r12+0x70]=[r15+0x130]; movups [r12+0x60]=[r15+0x120]; byte [rbp+0x10C4]=[rbp+0x1274]; movups [rbp+0x10C8]=[rbp+0x1278]; movups [r12+0x88]=[r15+0x148]; [r12+0x98]=[r15+0x158]; movups [r12+0xA7]=[r15+0x167]; u16 [rbp+0x1108]=[rbp+0x12B8] [V]
- call 0x67e23f0(rcx=r13) release shared [V]
- lea rax,[rbp+0x1390]; [rsp+0x28]=rax; [rsp+0x20]=r14; lea rcx,[rbp+0x1440]; rdx=[rbp+0x1060]; r8=[rbp+0x1008]; r9=[rbp+0xF80]; call 0x678dce0 (item assemble) [V] — body A used 0x678dce0 too
- copyback into staging [rbp+0x15E8]: [rcx+0x10]=[r12+0x70]; movups [rcx]=[r12+0x60]; byte [rbp+0x15FC]=[rbp+0x10C4]; movups [rbp+0x1600]=[rbp+0x10C8]; movups [rbp+0x15A8..]=[r12+0x88/0x98/0xA7]; u16 [rbp+0x1640]=[rbp+0x1108] [V] — staging base [rbp+0x15E8] vs body A [rbp+0x15f0]
- 0x66f5f91 rax=[rbp+0x16A8]; rcx=[rax+0x10]; eax=0x9D0; add rcx,rax -> pass object; call 0x5aba5c0 [V] (matches body A pass=0x5aba5c0(frame+0x10+0x9d0)); r13=rax (pass ptr)
- zero item [r15+0x08..0xA8] 12 xmm slots (0xa0 bytes) [V] — body A zeroed [rbp+0x11e0..0x1130] (0xc0, 12 slots); here [r15-8..r15+0xa0]
- feature flag 0x4a: mov rcx,[0x1233E1B0]; rax=[rcx]; rax=[rax+0x10]; dl=0x4A; call qword [0xF99FFA0]; [rbp+0x16B0]=al [V] — body A stored flag at [rbp+0x16d0]; body D [rbp+0x16b0] [V]
- u16 [rbp+0x1640] pushed to pass+0x8A8 u16 pool: rdx=[r13+0x8A8]; if rdx==[r13+0x8B0] goto loc_66f6033 (grow: lea rcx,[r13+0x8A0]; lea r8,[rbp+0x1640]; call 0x1ef6f90); else [rdx]=ax; [r13+0x8A8]+=2 [V] (matches body A pool 0x8a0 u16 push; slow path 0x1ef6f90 same as body B)
- feature flag 0x4a restore vcall [V]; [rbp+0x16b0]=al [V]
- [rbp+0x1130]=1 (kind-mask low word = 1) [V] (body A set [rbp+0x1130]=1 at phase 9)
- eax=[r13+0x8A8]-[r13+0x8A0]; shr eax,1; dec eax; [rbp+0x1140]=ax (item index=(end-begin)/2-1) [V] (matches body A)
- feature flag 0x4a vcall again [V]; [rbp+0x16b0]=al [V]
- mov rdx,[r13+0x758] (pool 0x750 cursor) — continues

--max 300 (stopped at 0x66f60a4 mov rdx,[r13+0x758])

### Step 4 (done): rdis dis 0x66f60ab 300 -> 0x66f60ab..~0x66f6655 (300 instr)
Item-emit tail (matches body A 0x66ed500.. recipe, different locals):
- pool 0x750 push (0x58-byte state entry): rdx=[r13+0x758]; if rdx==[r13+0x760] goto loc_66f613b (grow: lea rcx,[r13+0x750]; lea r8,[rbp+0x15E8]; call 0x6760a80); else fast path: [rdx+0x10]=[rbp+0x15E8+0x10] (u32); [rdx+0x00..0x10]=movups [rbp+0x15E8]; [rdx+0x14]=(u8)[rbp+0x15FC] (flag byte); [rdx+0x18]=float [rbp+0x1600]; [rdx+0x1c]=float [rbp+0x1604]; [rdx+0x20]=float [rbp+0x1608]; [rdx+0x24]=float [rbp+0x160c]; [rdx+0x28..0x38]=movups [rbp+0x1444+0x1cc]; [rdx+0x38..0x48]=movups [rbp+0x1444+0x1dc]; [rdx+0x47..0x58]=movups [rbp+0x1444+0x1eb] (15 bytes) [V]; [r13+0x758]+=0x58 [V]; jmp loc_66f614f [V] (matches body A pool 0x750 push; staging base [rbp+0x15e8] vs body A [rbp+0x15f0])
- feature 0x4a restore vcall [V]; [rbp+0x16b0]=al [V]
- eax=[r13+0x758]-[r13+0x750]; shr eax,3; imul eax,0xffff8ba3; dec eax; [rbp+0x115c]=ax (pool 0x750 item index) [V] (matches body A)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- u8 pool [r13+0x830..0x838]: rdx=[r13+0x830]; if rdx==[r13+0x838] goto loc_66f61c4 (grow: lea rcx,[r13+0x828]; call 0x6760e60); else rdx++; [r13+0x830]=rdx [V] (matches body A byte pool 0x858 push; body D pool base 0x828 vs body A 0x858)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- [rbp+0x1130]=0x4021 (kind-mask word) [V] — DIFF vs body A ([rbp+0x1130]=0x4001 at this point) [V]
- eax=[r13+0x828]; not eax; add eax,[r13+0x830]; [rbp+0x114a]=ax (item start index = ~begin + cursor) [V] (matches body A [rbp+0x1146])
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- 0x675fb30(rcx=[r13+0x648], rdx=[rbp+0x1598]) pool push [V]; eax=[r13+0x650]-[r13+0x648]; shr eax,3; imul 0xffff8e39; dec eax; [rbp+0x1172]=ax (pool 0x648 index) [V] (matches body A)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- 0x675f3b0(rcx=[r13+0x780], rdx=[rbp+0x1540]) pool push [V]; eax=[r13+0x788]-[r13+0x780]; shr eax,3; imul 0xffff8ba3; dec eax; [rbp+0x1158]=ax (pool 0x780 index) [V] (matches body A)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- pool588 at [r13+0x770] (0x88 stride): r14=[r13+0x770]; if r14==[r13+0x778] goto loc_66f631c (grow: lea rcx,[r13+0x768]; mov rdx,r14; lea r8,[rbp+0x14b8]; call 0x6760710); else fast: [r14]=[rbp+0x14b8]; 0xe869ff0(&r14+8,&rbp+0x14c0) copy 0x78 block [V]; [r14+0x80]=[rbp+0x1538]; [rbp+0x1538]=0; [r13+0x770]+=0x88 [V] (matches body A pool588 push; body D [rbp+0x14b8]/[rbp+0x14c0] vs body A [rbp+0x14a8]/[rbp+0x14c0])
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- [rbp+0x1130]=0x2007021 [V] (body A final-ish mask was 0x2007803 at similar point — DIFFERENT low bits)
- eax=[r13+0x770]-[r13+0x768]; shr eax,3; imul 0xfffff0f1; dec eax; [rbp+0x115a]=ax (pool 0x770 index) [V] (matches body A)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- pool0x680 push (0xC stride, 3 floats): rdx=[r13+0x680]; if rdx==[r13+0x688] goto loc_66f63d7 (grow: lea rcx,[r13+0x678]; lea r8,[rbp+0x14a8]; call 0x1770a70); else [rdx]=[rbp+0x14a8]; [rdx+4]=[rbp+0x14ac]; [rdx+8]=[rbp+0x14b0]; [r13+0x680]+=0xc [V] (matches body A; slow path 0x1770a70 same as body B)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- eax=[r13+0x680]-[r13+0x678]; shr eax,2; imul 0xfffaaab; dec eax; [rbp+0x116e]=ax (pool 0x680 index) [V] (matches body A)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- u8 pool [r13+0x2d8..0x2e0]: rdx=[r13+0x2d8]; if rdx==[r13+0x2e0] goto loc_66f6460 (grow: lea rcx,[r13+0x2d0]; call 0x6760e60); else rdx++; [r13+0x2d8]=rdx [V] (matches body A u16 pool 0x2d8 push; slow path 0x6760e60)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- eax=[r13+0x2d0]; not eax; add eax,[r13+0x2d8]; [rbp+0x11bc]=ax (item start index = ~begin + cursor) [V] (matches body A [rbp+0x11bc])
- 0x678d690(rcx=r13+0x5d0 (frame_pass+0x5d0), rdx=[rbp+0x1440] item) push item into pass pool [V] (matches body A)
- [rbp+0x1130]=0x4000000042807021 (final mask) [V] (body A final=0x4000000042807009 — DIFFERENCE in low bits: ...7021 vs ...7009)
- eax=[r13+0x5d8]-[r13+0x5d0]; shr eax,5; imul 0xfffaaab; dec eax; [rbp+0x117c]=ax (pool 0x5d0 index, /32) [V] (matches body A)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- item memcpy push: rdx=[r13+8] (item buffer cursor); if rdx==[r13+0x10] goto loc_66f652e (grow: mov rcx,r13; lea r8,[rbp+0x1130]; call 0x5aba6d0); else r8d=0xc8; rcx=rdx; lea rdx,[rbp+0x1130]; call 0xeec6ec0 (memcpy 0xc8 bytes); [r13+8]+=0xc8 [V] (matches body A pass.items.push)
- feature 0x4a restore [V]; [rbp+0x16b0]=al [V]
- conditional free: if byte [rbp+0x15d8]!=1 goto loc_66f65b5; rcx=[rbp+0x1598]; if rcx==0 goto loc_66f65b5; rdx=[rbp+0x15a8]-rcx (size); if rdx<0x1000 goto loc_66f659e (direct free); rax=[rcx-8] (heap header); rcx-=8; rcx-=rax; if rcx>=0x20 goto 0x66f82bb (out-of-range); rdx|=0x27; rcx=rax; call 0xe935700 (free) [V]; lea rax,[rbp+0x1598]; movups [rax],xmm6; [rax+0x10]=0 (clear) [V] (matches body A phase 27-28 release)
loc_66f65b5: lea rcx,[rbp+0x1440]; call 0x678e020 (destroy item) [V]; lea rcx,[rbp+0xf70]; call 0x67e1660 (destroy geometry) [V]
- test rbx,rbx; je loc_66f65fd; lock dec [rbx+8]; jne done; dtor+dealloc via [0xF99FFA0] x2 [V] (shared release, rbx = ?)
loc_66f65fd: rbx=[rbp+0x13d0]; test rbx,rbx; je loc_66f6634; lock dec [rbx+8]; ... dtor+dealloc [V] (release [rbp+0x13d0])
loc_66f6634: rbx=[rbp+0x13c0]; test rbx,rbx; je loc_66f666b; lock dec [rbx+8]; ... dtor+dealloc [V] (release [rbp+0x13c0])
--max 300 (stopped at 0x66f664f call qword ptr [0xF99FFA0])

### Step 5 (done): rdis dis 0x66f6655 300 -> 0x66f6655..~0x66f6b82 (300 instr)
Shared_ptr release sequence continues (releases [rbp+0x13c0], [rbp+0x1398], [rbp+0x1330], [rbp+0x1320], [rbp+0x1310], [rbp+0x12e8], [rbp+0x1668]) — matches body A phase 28 order but body D releases [rbp+0x13d0] FIRST (body A released [rbp+0x13d0] at 0x66ee150 too, then [rbp+0x13c0], [rbp+0x1398], [rbp+0x1330], [rbp+0x1320], [rbp+0x1310], [rbp+0x12e8], [rbp+0x1668]) [V]:
- loc_66f6634: rbx=[rbp+0x13c0] release [V]
- loc_66f666b: rbx=[rbp+0x1398] release [V]
- loc_66f66a2: rbx=[rbp+0x1330] release [V]
- loc_66f66d9: rbx=[rbp+0x1320] release [V]
- loc_66f6710: rbx=[rbp+0x1310] release [V]
- loc_66f6747: rbx=[rbp+0x12e8] release [V]
- loc_66f677e: rbx=[rbp+0x1668] release [V]
loc_66f67b5: rbx=[rbp+0x1378]; test rbx,rbx; jne loc_66f6c95 (if non-null jump to release at 0x66f6c95); jmp loc_66f6cc0 [V]

loc_66f67ca (seasons null path join from loc_66f5965/0x66f59a5 when [r14+0x28]==0 — reached here via fallthrough? actually this is a separate label):
- xor eax,eax; rcx=[r14+0x20]; [rbp+0x1370]=rcx; [rbp+0x1378]=rax=0 [V]

loc_66f67de (non-seasons K path from loc_66f599f):
- lea rax,[rbp+0x12e0]; [rsp+0x38]=rax; lea rax,[rbp+0x1370]; [rsp+0x30]=rax; mov eax,[rbp+0x16d0]; [rsp+0x28]=ax; [rsp+0x20]=r14; [rsp+0x48]=0xFFFFFF00; [rsp+0x40]=0xFFFFFF00; lea rcx,[rbp+0x1390] (out); lea rdx,[rbp+0x1420] (vec1670[i] shared_ptr); movzx r8d,byte [rbp+0x16d4]; r9=-1; call 0x673cc80 [V] — non-seasons shader-binding block (same 0x673cc80)
- movaps [rbp+0x1130],xmm6 (zero mask word) [V]
- pair0 copy: rax=[rbp+0x1398]; if rax lock inc [rax+8]; [rbp+0x1130]=[rbp+0x1390]; [rbp+0x1138]=rax [V]
- pair1: rcx=[rbp+0x13a0]; movzx eax,word [rcx+0x10]; [r15+0x10]=ax; movups [r15]=[rcx]; movups [r15+0x18]=xmm6 (zero) [V] — r15=[rbp+0x1140] (item index slot) set at prologue
- pair2: rax=[rbp+0x13c0]; lock inc; [rbp+0x1158]=[rbp+0x13b8]; [rbp+0x1160]=rax; movups [r15+0x28]=xmm6 (zero) [V]
- pair3: rax=[rbp+0x13d0]; lock inc; [rbp+0x1168]=[rbp+0x13c8]; [rbp+0x1170]=rax; movups [r15+0x38]=xmm6 (zero) [V]
- pair4: rax=[rbp+0x13e0]; lock inc; rbx=rax; [rbp+0x1178]=[rbp+0x13d8]; [rbp+0x1180]=rbx; [rbp+0x1188]=[rbp+0x13e8] [V]
- lea rcx,[rbp+0xea8]; lea r13,[rbp+0xf70]; mov rdx,r13; call 0x67a75d0 (binder) [V] — DIFF vs body A (body A called 0x67a75d0(&0xea8,&0xf70) here too? body A phase 5 called 0x67a75d0(&rbp+0xea8,&rbp+0xf70). Yes matches)
- lea rax,[rbp+0x1130]; [rsp+0x20]=rax; lea r14,[rbp+0x1440]; rcx=r14; rdx=r12; lea r8,[rbp+0xff8]; r9=r13; call 0x678ef40 (geometry+material fill) [V] — matches body A phase 5 0x678ef40(&rbp+0x1440, r13, &rbp+0xff8, &rbp+0xf70)
- copy staging block at [rbp+0x15d8]: [r8+0x10]=[r12+0x60] (u32); movups [r8]=[r12+0x50] (16 bytes); byte [rbp+0x15ec]=[rbp+0x10b4] (flag byte); movups [rbp+0x15f0]=[rbp+0x10b8] (16 bytes) [V] — matches body A phase 6-7 staging build; staging base [rbp+0x15d8] same as body A
- movups [r12+0x78]->[rbp+0x1444+0x1bc]; [r12+0x88]->[rbp+0x1444+0x1cc]; [r12+0x97]->[rbp+0x1444+0x1db] (unaligned 15 bytes) [V]; u16 [rbp+0x1630]=[rbp+0x10f8] [V] — matches body A phase 7 three movups entry->rsi (here rsi=[rbp+0x1444])
- 0x66f69ea rax=[rbp+0x16a8]; rcx=[rax+0x10]; eax=0x9d0; add rcx,rax -> pass object [V]; stack [rsp+0x30]=r14, [rsp+0x28]=[rbp+0x14a8], [rsp+0x20]=[rbp+0x1530]; lea rdx,[rbp+0x1630]; lea r9,[rbp+0x1588]; call 0x67b2a60 [V] — NEW callee (body A used flag vcall + u16 pool 0x8a8 push here; body D uses 0x67b2a60 with stack block) [?]
- cmp byte [rbp+0x15c8],1; jne loc_66f6a89; rcx=[rbp+0x1588]; if rcx==0 goto loc_66f6a89; rdx=[rbp+0x1598]-rcx; if rdx<0x1000 goto loc_66f6a72; rax=[rcx-8]; rcx-=8; rcx-=rax; if rcx>=0x20 goto 0x66f82bb; rdx|=0x27; rcx=rax; call 0xe935700 (free) [V]; lea rax,[rbp+0x1588]; movups [rax],xmm6; [rax+0x10]=0 (clear) [V] — matches body A phase 27 conditional free
loc_66f6a89: lea rcx,[rbp+0x1440]; call 0x678f260 (release draw item) [V]; lea rcx,[rbp+0xf70]; call 0x67e23f0 (release geometry) [V]
- test rbx,rbx; je loc_66f6ad1; lock dec [rbx+8]; ... dtor+dealloc [V] (release rbx — the shared ctrl from 0x678ef40 result? [?])
loc_66f6ad1: rbx=[rbp+0x1170] release; loc_66f6b08: rbx=[rbp+0x1160] release; loc_66f6b3f: rbx=[rbp+0x1138] release [V] — these release the shared_ptr pairs stored at [rbp+0x1130..0x1188] (the mask-word/control slots reused as release targets)
loc_66f6b76: rbx=[rbp+0x13e0]; test rbx,rbx; je loc_66f6bad — continues
--max 300 (stopped at 0x66f6b80 je short 0x66f6bad)

### Step 6 (done): rdis dis 0x66f6b82 200 -> 0x66f6b82..~0x66f6e36 (release sequence + cleanup loops + vec1670 free + epilogue start)
Release sequence continuation (matching body A phase 28 order):
- loc_66f6b82: rbx=[rbp+0x13c0] release — lock dec [rbx+8]; jne loc_66f6bad; dtor+dealloc via [0xF99FFA0] x2 [V]
- loc_66f6bad: rbx=[rbp+0x13D0] release [V]; loc_66f6be4: rbx=[rbp+0x13C0] release [V]; loc_66f6c1b: rbx=[rbp+0x1398] release [V]; loc_66f6c52: rbx=[rbp+0x1378] release [V]; loc_66f6c89: rbx=[rbp+0x12E8] release [V] — all via lock dec +8, dtor+dealloc via [0xF99FFA0] x2 [V]
- loc_66f6cc0: rbx=[rbp+0x1428] release [V] (matches body A phase 29 release [rbp+0x1428])
- loc_66f6cf7: cmp byte [rbp+0xDF0],3; jne loc_66f6d37; rbx=[rbp+0xDE8] release [V] (matches body A phase 29 conditional release [rbp+0xde8] when byte==3)

loc_66f6d37 (cleanup loop over [rbp+0xDC0]..[rbp+0xDC8] step 0x28 — matches body A phase 30):
- r14=[rbp+0xDC0]; test r14,r14; je 0x66f5358 (empty: jump to pass-2 loop increment) [V]
- r13=[rbp+0xDC8]; loop: cmp r14,r13; je 0x66f5358 (done: jump to pass-2 loop increment) [V]; cmp byte [r14+0x18],2; jne skip (only type-2 entries) [V]; rbx=[r14+8]; shared_ptr release [V]; skip: r14+=0x28; jmp loop [V]

loc_66f6d9a (pass-2 loop exit / vec1670 cleanup — matches body A phase 31):
- rsi=[rbp+0x1670] (vec1670 base); test rsi,rsi; je 0x66f6e3b (empty: jump to body D epilogue) [V]
- rbx=[rbp+0x1678] (vec1670 end); cmp rsi,rbx; jne loc_66f6dc1 (work remains) [V]; jmp 0x66f6e04 (no work: free vec1670 buffer) [V]

loc_66f6dc1 (cleanup loop over vec1670 step 0x18):
- cmp byte [rsi+0x10],1; jne skip (only valid entries) [V]; rdi=[rsi+8]; shared_ptr release [V]; skip: rsi+=0x18; cmp rsi,rbx; jne loop [V]

loc_66f6e04 (free vec1670 buffer):
- rdx=[rbp+0x1680]; sub rdx,rsi (size=end-base); cmp rdx,0x1000; jb loc_66f6e33 (small: skip free) [V]; rax=[rsi-8] (heap header); rsi-=8; rsi-=rax; cmp rsi,0x20; jae 0x66f82bb (out-of-range throw) [V]; rdx+=0x27 (combine size+flags); rsi=rax; call 0xE935700 (free) [V] — matches body A phase 28 free pattern

loc_66f6e3b (body D epilogue, beyond body D boundary 0x66f6e36):
- r14=[rbp+0x12D8]; shared_ptr release [V]; cmp byte [rbp+0xD20],1; jne loc_66f6ec2; [0xD08],[0xD10],[0xD18] calls to 0xA784C0 x3 (deregister/deinit) [V]; loc_66f6ec2: restore xmm6-xmm15; add rsp,0x1808; pop rbx/rdi/rsi/r12/r13/r14/r15/rbp; ret [V]

--max 200 (stopped at 0x66f6e36 call 0xE935700 — body D end boundary reached)

### Step 7 (done): rdis dis 0x66f70a1 300 -> 0x66f70a1..~0x66f77bc (separate function sub_66f70a1 — string registration for pass record fields)
This is a separate function (sub_66f70a1, [0x66f70a1..0x66f90a1)) called from body D's epilogue area via jump targets. It registers string-keyed properties:
- 0x66f70a1 lea r12,[0x129F9450]; [rbp+0xE50]=r12; lea rcx,[rbp+0xD28]; call 0x670B260; [rbp+0x948]=&rbp+0xD28; lea rax,[rbp+0xD68]; [rbp+0x950]=rax; [rbp+0xE58]=r12; lea rdx,[rbp+0x948]; rcx=r12; call 0x7D7890 [V] — registers first property (key [rbp+0xD28]..0xD68, value data_129f9450)
- 0x66f70ef lea r12,[0x129F9490]; [rbp+0xE58]=r12; lea rdx,[0xF5B4A66] ("Dithering"); lea r8,[0xF598D3A]; lea rcx,[rbp+0xE10]; call 0xF2EA00; [rbp+0x958]=&rbp+0xE10; [rbp+0x960]=[rbp+0xE50]; [rbp+0xE60]=r12; lea rdx,[rbp+0x958]; rcx=r12; call 0x7D7890 [V] — registers "Dithering" with data_129f9490 at [rbp+0xE10]
- 0x66f714b lea rax,[0x129F94D0]; [rbp+0xE60]=rax; lea rdx,[0xF5B4A66] ("Dithering"); lea r8,[0xF598D3A]; lea rcx,[rbp+0x1130]; r12=rcx; call 0xF2EA00; [rbp+0x1178]=0; [rbp+0x1180]=7; [rbp+0x1188]=0xF [V] — registers "Dithering" with data_129f94d0 at [rbp+0x1130]
- 0x66f7198 mov eax,[0xF54D038] ("Seasons"); [rbp+0x1170]=eax; mov eax,[0xF54D03B] ("sons"); [rbp+0x1173]=eax; byte [rbp+0x1177]=0 [V] — string "Seasons"/"sons" at [rbp+0x1170]
- 0x66f71b7 xorps xmm0,xmm0; movups [rbp+0x1190],xmm0; [rbp+0x11A0]=2; [rbp+0x11A8]=0xF; word [rbp+0x1190]=0x6E4F; [rbp+0x968]=r12; lea rax,[rbp+0x11B0]; [rbp+0x970]=rax; lea rcx,[0x129F94D0]; [rbp+0xE68]=rcx; lea rdx,[rbp+0x968]; call 0x7D7890 [V] — registers key [rbp+0x1170..0x117F] at [rbp+0x1130] (second reg)
- 0x66f7210 lea rcx,[rbp+0xC78]; [rbp+0xDA0]=rcx; lea rdx,[0xF5B4A66] ("Dithering"); lea r8,[0xF598D3A]; call 0xF2EA00 [V]; lea rcx,[rbp+0xCB8]; [rbp+0xDA0]=rcx; call 0x670B260 [V]; lea rax,[rbp+0xC78]; [rbp+0x978]=rax; lea rax,[rbp+0xCF8]; [rbp+0x980]=rax; lea rcx,[0x129F9510]; [rbp+0xE70]=rcx; lea rdx,[rbp+0x978]; call 0x7D7890 [V] — registers [rbp+0xC78] and [rbp+0xCB8]
- 0x66f727d lea r12,[0x129F9550]; [rbp+0xE70]=r12; lea rdx,[0xF5B7E07] ("PointLightShading"); lea r8,[0xF598D3A]; lea rcx,[rbp+0xEA8]; call 0xF2EA00 [V]; [rbp+0x988]=&rbp+0xEA8; [rbp+0x990]=[rbp+0xEE8]; [rbp+0xE78]=r12; lea rdx,[rbp+0x988]; rcx=r12; call 0x7D7890 [V] — registers "PointLightShading" with data_129f9550 at [rbp+0xEA8]
- 0x66f72d9 lea r12,[0x129F9590]; [rbp+0xE78]=r12; lea rdx,[0xF5B7E07] ("PointLightShading"); lea r8,[0xF598D3A]; lea rcx,[rbp+0xEE8]; call 0xF2EA00 [V] — registers "PointLightShading" with data_129f9590 at [rbp+0xEE8]
- 0x66f7302 [rbp+0xF30]=0; [rbp+0xF38]=7; [rbp+0xF40]=0xF; mov eax,[0xF54D038] ("Seasons"); [rbp+0xF28]=eax; mov eax,[0xF54D03B] ("sons"); [rbp+0xF2B]=eax; byte [rbp+0xF2F]=0 [V] — string "Seasons"/"sons" at [rbp+0xF28]
- 0x66f7342 xorps xmm0,xmm0; movups [rbp+0xF48],xmm0; [rbp+0xF58]=2; [rbp+0xF60]=0xF; word [rbp+0xF48]=0x6E4F; lea rax,[rbp+0xEE8]; [rbp+0x998]=rax; lea rax,[rbp+0xF68]; [rbp+0x9A0]=rax; [rbp+0xE80]=r12; lea rdx,[rbp+0x998]; rcx=r12; call 0x7D7890 [V] — registers key [rbp+0xF28..0xF2F] at [rbp+0xEE8]
- 0x66f739e lea rcx,[rbp+0x1390]; [rbp+0xD98]=rcx; lea rdx,[0xF5B7E07] ("PointLightShading"); lea r8,[0xF598D3A]; call 0xF2EA00 [V]; lea rcx,[rbp+0x13D0]; [rbp+0xD98]=rcx; call 0x670B260 [V]; lea rax,[rbp+0x1390]; [rbp+0x9A8]=rax; lea rax,[rbp+0x1410]; [rbp+0x9B0]=rax; lea rcx,[0x129F95D0]; [rbp+0xE88]=rcx; lea rdx,[rbp+0x9A8]; call 0x7D7890 [V] — registers [rbp+0x1390] and [rbp+0x13D0]
- 0x66f740b lea rcx,[rbp+0x12E0]; [rbp+0xD90]=rcx; lea rdx,[0xF5B7E07] ("PointLightShading"); lea r8,[0xF598D3A]; call 0xF2EA00 [V]; lea rcx,[rbp+0x1320]; [rbp+0xD90]=rcx; lea rdx,[0xF5B4A66] ("Dithering"); lea r8,[0xF598D3A]; call 0xF2EA00 [V]; lea rax,[rbp+0x12E0]; [rbp+0x9B8]=rax; lea rax,[rbp+0x1360]; [rbp+0x9C0]=rax; lea rcx,[0x129F9610]; [rbp+0xE90]=rcx; lea rdx,[rbp+0x9B8]; call 0x7D7890 [V] — registers [rbp+0x12E0] and [rbp+0x1320]
- 0x66f7486 lea rcx,[rbp+0x1440]; [rbp+0xD88]=rcx; lea rdx,[0xF5B7E07] ("PointLightShading"); lea r8,[0xF598D3A]; call 0xF2EA00 [V]; lea rcx,[rbp+0x1480]; [rbp+0xD88]=rcx; lea rdx,[0xF5B4A66] ("Dithering"); lea r8,[0xF598D3A]; call 0xF2EA00 [V]
- 0x66f74ca [rbp+0x14C8]=0; [rbp+0x14D0]=7; [rbp+0x14D8]=0xF; mov eax,[0xF54D038] ("Seasons"); [rbp+0x14C0]=eax; mov eax,[0xF54D03B] ("sons"); [rbp+0x14C3]=eax; byte [rbp+0x14C7]=0 [V]; xorps xmm0,xmm0; movups [rbp+0x14E0],xmm0; [rbp+0x14F0]=2; [rbp+0x14F8]=0xF; word [rbp+0x14E0]=0x6E4F; lea rax,[rbp+0x1440]; [rbp+0x9C8]=rax; lea rax,[rbp+0x1500]; [rbp+0x9D0]=rax; lea rcx,[0x129F9650]; [rbp+0xE98]=rcx; lea rdx,[rbp+0x9C8]; call 0x7D7890 [V] — registers "Seasons"/"sons" key at [rbp+0x1440]
- 0x66f756a lea rcx,[rbp+0xF70]; [rbp+0xEA0]=rcx; lea rdx,[0xF5B7E07] ("PointLightShading"); lea r8,[0xF598D3A]; call 0xF2EA00 [V]; lea rcx,[rbp+0xFB0]; [rbp+0xEA0]=rcx; lea rdx,[0xF5B4A66] ("Dithering"); lea r8,[0xF598D3A]; call 0xF2EA00 [V]; lea rcx,[rbp+0xFF0]; [rbp+0xEA0]=rcx; call 0x670B260 [V]; lea rax,[rbp+0xF70]; [rbp+0x9D8]=rax; lea rax,[rbp+0x1030]; [rbp+0x9E0]=rax; lea rcx,[0x129F9690]; [rbp+0xE98]=rcx (overwrites); lea rdx,[rbp+0x9D8]; call 0x7D7890 [V]
- 0x66f75f2 lea rcx,[rbp+0xFF0]; call 0x9B250 [V]; lea rcx,[rbp+0xFB0]; call 0x9B250 [V]; lea rcx,[rbp+0xF70]; call 0x9B250 [V]; lea rcx,[rbp+0x14C0]; call 0x9B250 [V]; lea rcx,[rbp+0x1480]; call 0x9B250 [V]; lea rcx,[rbp+0x1440]; call 0x9B250 [V]; lea rcx,[rbp+0x1320]; call 0x9B250 [V]; lea rcx,[rbp+0x12E0]; call 0x9B250 [V]; lea rcx,[rbp+0x13D0]; call 0x9B250 [V]; lea rcx,[rbp+0x1390]; call 0x9B250 [V]; lea rcx,[rbp+0xF28]; call 0x9B250 [V]; lea rcx,[rbp+0xEE8]; call 0x9B250 [V]; lea rcx,[rbp+0xEA8]; call 0x9B250 [V]; lea rcx,[rbp+0xCB8]; call 0x9B250 [V]; lea rcx,[rbp+0xC78]; call 0x9B250 [V]; lea rcx,[rbp+0x1170]; call 0x9B250 [V]; lea rcx,[rbp+0x1130]; call 0x9B250 [V]; lea rcx,[rbp+0xE10]; call 0x9B250 [V]; lea rcx,[rbp+0xD28]; call 0x9B250 [V]; lea rcx,[rbp+0xDB8]; call 0x9B250 [V]
- 0x66f76e2 lea rcx,[0x670B300]; call 0xE935740 [V]; lea rcx,[0x129F96D0]; call 0xE938D70 [V]; mov r12,[rbp+0x16C0]; jmp 0x66EA751 [V] — end of sub_66f70a1, jumps out of body D

### Step 8 (done): rdis dis 0x66f77bc 300 -> 0x66f77bc..~0x66f7eba (continuation of string registration via sub_66f77bc)
This is a separate function (sub_66f77bc, [0x66f77bc..0x66f97bc)) — continuation of property registration with many AA710/66A02D0 string-keyed registrations:
- 0x66f77bc call 0xAA710 [V]; [rbp+0xA08]=r12; [rbp+0xA10]=0xB; lea rcx,[0x129F96F8]; lea rdx,[rbp+0xA08]; lea r8,[rbp+0x60]; call 0x66A02D0 [V] — registers at [rbp+0x60] with string data_129f96f8
- 0x66f77ec lea rdx,[0x129F9490]; lea rcx,[rbp+0xA0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA18]=r12; [rbp+0xA20]=0xB; lea rcx,[0x129F9708]; lea rdx,[rbp+0xA18]; lea r8,[rbp+0xA0]; call 0x66A02D0 [V] — registers at [rbp+0xA0] with string data_129f9708
- 0x66f7834 lea rdx,[0x129F94D0]; lea rcx,[rbp+0xE0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA28]=r12; [rbp+0xA30]=0xB; lea rcx,[0x129F9718]; lea rdx,[rbp+0xA28]; lea r8,[rbp+0xE0]; call 0x66A02D0 [V] — registers at [rbp+0xE0] with string data_129f9718
- 0x66f787c lea rdx,[0x129F9510]; lea rcx,[rbp+0x120]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA38]=r12; [rbp+0xA40]=0xB; lea rcx,[0x129F9728]; lea rdx,[rbp+0xA38]; lea r8,[rbp+0x120]; call 0x66A02D0 [V] — registers at [rbp+0x120] with string data_129f9728
- 0x66f78c4 lea rdx,[0x129F9550]; lea rcx,[rbp+0x160]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA48]=r12; [rbp+0xA50]=0xB; lea rcx,[0x129F9738]; lea rdx,[rbp+0xA48]; lea r8,[rbp+0x160]; call 0x66A02D0 [V] — registers at [rbp+0x160] with string data_129f9738
- 0x66f790c lea rdx,[0x129F9590]; lea rcx,[rbp+0x1A0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA58]=r12; [rbp+0xA60]=0xB; lea rcx,[0x129F9748]; lea rdx,[rbp+0xA58]; lea r8,[rbp+0x1A0]; call 0x66A02D0 [V] — registers at [rbp+0x1A0] with string data_129f9748
- 0x66f7954 lea rdx,[0x129F95D0]; lea rcx,[rbp+0x1E0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA68]=r12; [rbp+0xA70]=0xB; lea rcx,[0x129F9758]; lea rdx,[rbp+0xA68]; lea r8,[rbp+0x1E0]; call 0x66A02D0 [V] — registers at [rbp+0x1E0] with string data_129f9758
- 0x66f799c lea rdx,[0x129F9610]; lea rcx,[rbp+0x220]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA78]=r12; [rbp+0xA80]=0xB; lea rcx,[0x129F9768]; lea rdx,[rbp+0xA78]; lea r8,[rbp+0x220]; call 0x66A02D0 [V] — registers at [rbp+0x220] with string data_129f9768
- 0x66f79e4 lea rdx,[0x129F9650]; lea rcx,[rbp+0x260]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA88]=r12; [rbp+0xA90]=0xB; lea rcx,[0x129F9778]; lea rdx,[rbp+0xA88]; lea r8,[rbp+0x260]; call 0x66A02D0 [V] — registers at [rbp+0x260] with string data_129f9778
- 0x66f7a2c lea rdx,[0x129F9690]; lea rcx,[rbp+0x2A0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xA98]=r12; [rbp+0xAA0]=0xB; lea rcx,[0x129F9788]; lea rdx,[rbp+0xA98]; lea r8,[rbp+0x2A0]; call 0x66A02D0 [V] — registers at [rbp+0x2A0] with string data_129f9788
- 0x66f7a74 lea rdx,[0x129F93D0]; lea rcx,[rbp+0x2E0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; lea r12,[0xF549126] ("RenderChunkPrepass"); [rbp+0xAA8]=r12; [rbp+0xAB0]=0x12; lea rcx,[0x129F9798]; lea rdx,[rbp+0xAA8]; lea r8,[rbp+0x2E0]; call 0x66A02D0 [V] — registers "RenderChunkPrepass" at [rbp+0x2E0]
- 0x66f7ac3 lea rdx,[0x129F9410]; lea rcx,[rbp+0x320]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xAB8]=r12; [rbp+0xAC0]=0x12; lea rcx,[0x129F97A8]; lea rdx,[rbp+0xAB8]; lea r8,[rbp+0x320]; call 0x66A02D0 [V] — registers at [rbp+0x320] with string data_129f97a8
- 0x66f7ade lea rdx,[0x129F9450]; lea rcx,[rbp+0x360]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xAC8]=r12; [rbp+0xAD0]=0x12; lea rcx,[0x129F97B8]; lea rdx,[rbp+0xAC8]; lea r8,[rbp+0x360]; call 0x66A02D0 [V] — registers at [rbp+0x360] with string data_129f97b8
- 0x66f7b26 lea rdx,[0x129F9490]; lea rcx,[rbp+0x3A0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xAD8]=r12; [rbp+0xAE0]=0x12; lea rcx,[0x129F97C8]; lea rdx,[rbp+0xAD8]; lea r8,[rbp+0x3A0]; call 0x66A02D0 [V] — registers at [rbp+0x3A0] with string data_129f97c8
- 0x66f7b6e lea rdx,[0x129F94D0]; lea rcx,[rbp+0x3E0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xAE8]=r12; [rbp+0xAF0]=0x12; lea rcx,[0x129F97D8]; lea rdx,[rbp+0xAE8]; lea r8,[rbp+0x3E0]; call 0x66A02D0 [V] — registers at [rbp+0x3E0] with string data_129f97d8
- 0x66f7bb6 lea rdx,[0x129F9510]; lea rcx,[rbp+0x420]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xAF8]=r12; [rbp+0xB00]=0x12; lea rcx,[0x129F97E8]; lea rdx,[rbp+0xAF8]; lea r8,[rbp+0x420]; call 0x66A02D0 [V] — registers at [rbp+0x420] with string data_129f97e8
- 0x66f7bfe lea rdx,[0x129F9550]; lea rcx,[rbp+0x460]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB08]=r12; [rbp+0xB10]=0x12; lea rcx,[0x129F97F8]; lea rdx,[rbp+0xB08]; lea r8,[rbp+0x460]; call 0x66A02D0 [V] — registers at [rbp+0x460] with string data_129f97f8
- 0x66f7c2b lea rdx,[0x129F9590]; lea rcx,[rbp+0x4A0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB18]=r12; [rbp+0xB20]=0x12; lea rcx,[0x129F9808]; lea rdx,[rbp+0xB18]; lea r8,[rbp+0x4A0]; call 0x66A02D0 [V] — registers at [rbp+0x4A0] with string data_129f9808
- 0x66f7cbb lea rdx,[0x129F95D0]; lea rcx,[rbp+0x4E0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB28]=r12; [rbp+0xB30]=0x12; lea rcx,[0x129F9818]; lea rdx,[rbp+0xB28]; lea r8,[rbp+0x4E0]; call 0x66A02D0 [V] — registers at [rbp+0x4E0] with string data_129f9818
- 0x66f7d03 lea rdx,[0x129F9610]; lea rcx,[rbp+0x520]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB38]=r12; [rbp+0xB40]=0x12; lea rcx,[0x129F9828]; lea rdx,[rbp+0xB38]; lea r8,[rbp+0x520]; call 0x66A02D0 [V] — registers at [rbp+0x520] with string data_129f9828
- 0x66f7d4b lea rdx,[0x129F9650]; lea rcx,[rbp+0x560]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB48]=r12; [rbp+0xB50]=0x12; lea rcx,[0x129F9838]; lea rdx,[rbp+0xB48]; lea r8,[rbp+0x560]; call 0x66A02D0 [V] — registers at [rbp+0x560] with string data_129f9838
- 0x66f7d93 lea rdx,[0x129F9690]; lea rcx,[rbp+0x5A0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB58]=r12; [rbp+0xB60]=0x12; lea rcx,[0x129F9848]; lea rdx,[rbp+0xB58]; lea r8,[rbp+0x5A0]; call 0x66A02D0 [V] — registers at [rbp+0x5A0] with string data_129f9848
- 0x66f7ddb lea rdx,[0x129F93D0]; lea rcx,[rbp+0x5E0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; lea r12,[0xF7CA262] ("RenderChunkForwardPBR"); [rbp+0xB68]=r12; [rbp+0xB70]=0x15; lea rcx,[0x129F9858]; lea rdx,[rbp+0xB68]; lea r8,[rbp+0x5E0]; call 0x66A02D0 [V] — registers "RenderChunkForwardPBR" at [rbp+0x5E0]
- 0x66f7e2a lea rdx,[0x129F9410]; lea rcx,[rbp+0x620]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB78]=r12; [rbp+0xB80]=0x15; lea rcx,[0x129F9868]; lea rdx,[rbp+0xB78]; lea r8,[rbp+0x620]; call 0x66A02D0 [V] — registers at [rbp+0x620] with string data_129f9868
- 0x66f7e72 lea rdx,[0x129F9450]; lea rcx,[rbp+0x660]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB88]=r12; [rbp+0xB90]=0x15; lea rcx,[0x129F9878]; lea rdx,[rbp+0xB88]; lea r8,[rbp+0x660]; call 0x66A02D0 [V] — registers at [rbp+0x660] with string data_129f9878

### Step 9 (done): rdis dis 0x66f7eba 300 -> 0x66f7eba..~0x66f82bb (remaining string registration + error handler start)
- 0x66f7eba lea rdx,[0x129F9490]; lea rcx,[rbp+0x6A0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xB98]=r12; [rbp+0xBA0]=0x15; lea rcx,[0x129F9888]; lea rdx,[rbp+0xB98]; lea r8,[rbp+0x6A0]; call 0x66A02D0 [V] — registers at [rbp+0x6A0] with string data_129f9888
- 0x66f7f02 lea rdx,[0x129F94D0]; lea rcx,[rbp+0x6E0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xBA8]=r12; [rbp+0xBB0]=0x15; lea rcx,[0x129F9898]; lea rdx,[rbp+0xBA8]; lea r8,[rbp+0x6E0]; call 0x66A02D0 [V] — registers at [rbp+0x6E0] with string data_129f9898
- 0x66f7f4a lea rdx,[0x129F9510]; lea rcx,[rbp+0x720]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xBB8]=r12; [rbp+0xBC0]=0x15; lea rcx,[0x129F98A8]; lea rdx,[rbp+0xBB8]; lea r8,[rbp+0x720]; call 0x66A02D0 [V] — registers at [rbp+0x720] with string data_129f98a8
- 0x66f7f92 lea rdx,[0x129F9550]; lea rcx,[rbp+0x760]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xBC8]=r12; [rbp+0xBD0]=0x15; lea rcx,[0x129F98B8]; lea rdx,[rbp+0xBC8]; lea r8,[rbp+0x760]; call 0x66A02D0 [V] — registers at [rbp+0x760] with string data_129f98b8
- 0x66f7fda lea rdx,[0x129F9590]; lea rcx,[rbp+0x7A0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xBD8]=r12; [rbp+0xBE0]=0x15; lea rcx,[0x129F98C8]; lea rdx,[rbp+0xBD8]; lea r8,[rbp+0x7A0]; call 0x66A02D0 [V] — registers at [rbp+0x7A0] with string data_129f98c8
- 0x66f8022 lea rdx,[0x129F95D0]; lea rcx,[rbp+0x7E0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xBE8]=r12; [rbp+0xBF0]=0x15; lea rcx,[0x129F98D8]; lea rdx,[rbp+0xBE8]; lea r8,[rbp+0x7E0]; call 0x66A02D0 [V] — registers at [rbp+0x7E0] with string data_129f98d8
- 0x66f806a lea rdx,[0x129F9610]; lea rcx,[rbp+0x820]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xBF8]=r12; [rbp+0xC00]=0x15; lea rcx,[0x129F98E8]; lea rdx,[rbp+0xBF8]; lea r8,[rbp+0x820]; call 0x66A02D0 [V] — registers at [rbp+0x820] with string data_129f98e8
- 0x66f80b2 lea rdx,[0x129F9650]; lea rcx,[rbp+0x860]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xC08]=r12; [rbp+0xC10]=0x15; lea rcx,[0x129F98F8]; lea rdx,[rbp+0xC08]; lea r8,[rbp+0x860]; call 0x66A02D0 [V] — registers at [rbp+0x860] with string data_129f98f8
- 0x66f80fa lea rdx,[0x129F9690]; lea rcx,[rbp+0x8A0]; lea r8,[rbp+0x1440]; call 0xAA710 [V]; [rbp+0xC18]=r12; [rbp+0xC20]=0x15; lea rcx,[0x129F9908]; lea rdx,[rbp+0xC18]; lea r8,[rbp+0x8A0]; call 0x66A02D0 [V] — registers at [rbp+0x8A0] with string data_129f9908
- 0x66f8142 lea rcx,[0x129F9918]; call 0xE938D70 [V]; mov r12,[rbp+0x16C0]; jmp 0x66EA7D1 [V] — jumps out
- Error handler at 0x66f82bb (reached from body D out-of-range check at 0x66f6e26): zeroes rsp+0x20..r9d; call qword [0xF9A8C78]; then lea rcx,[0x129F9A98]; call 0xE938CB0; cmp [0x129F9A98],0xFFFFFFFF; jne 0x66EB5A6; lea rdx,[0xF5D0B1B] ("ViewPositionAndTime"); ... calls 0x79580 then continues into hash/map lookup

--max 300 (stopped at 0x66f831c loc_66f831c)

## Differences body D vs body A (summary)
| # | Aspect | Body A | Body D | Source |
|---|--------|--------|--------|--------|
| 1 | [rbp+0x1658] | &=desc+0x78 (material instance ptr) | =&desc+0x78 (same as A) | [V] Step 1 |
| 2 | Binder in matrix-copy paths | 0x67a75d0 | 0x67a75d0 (same as A; DIFF vs B=0x678cf10) | [V] Steps 2-3 |
| 3 | Feature flag 0x4a local | [rbp+0x16d0] | [rbp+0x16b0] | [V] Steps 3-6 |
| 4 | Staging base (varies by path) | [rbp+0x1578]/[rbp+0x15f0] | [rbp+0x1580]/[rbp+0x15e8]/[rbp+0x15d8] | [V] Steps 2-5 |
| 5 | Pack order [rbp+0xea8..0xec0] | {&1650,model,drawlist,&1120} | {&1410,model,drawlist,rec} | [V] Step 2 |
| 6 | 0x673cc80 r8d arg | K=[rbp+0x16b0] | byte [rbp+0x16d4] (fogA-found flag) | [V] Steps 3, 6 |
| 7 | NEW callees replacing flag vcall+pool push | (none) | 0x67b1a70 (shift+class2), 0x67b2260 (shift only), 0x67b3180 (alt class2), 0x67b3870 (alt class2), 0x67b2a60 (non-seasons K path) | [V] Steps 2-6 |
| 8 | Destroy calls | 0x678e020(item)+0x67e1660(geometry) | 0x67e1660(geometry) x2 | [V] Step 2 |
| 9 | Final kind-mask [rbp+0x1130] | 0x4000000042807009 | 0x4000000042807021 | [V] Step 4 |
| 10 | Mid kind-mask [rbp+0x1130] | 0x4001 | 0x4021 | [V] Step 4 |
| 11 | Pool u8 base | 0x858 | 0x828 | [V] Step 4 |
| 12 | Pool588 src | [rbp+0x14a8]/[rbp+0x14c0] | [rbp+0x14b8]/[rbp+0x14c0] | [V] Step 4 |
| 13 | vec1670 free size threshold | 0x1000 | 0x1000 (same) | [V] Step 6 |
| 14 | vec1670 loop step | 0x18 | 0x18 (same) | [V] Step 6 |
| 15 | Cleanup loop step | 0x28 | 0x28 (same) | [V] Step 6 |

## Open questions
- [rbp+0x16CF]: compared against isAB=[rbp+0x1368] to split shift vs no-shift paths; meaning unknown [?]
- [rbp+0x1370]: set from [r14+0x20] in seasons null path; used as pack field 0 at [rbp+0xea8]; meaning unknown [?]
- [rbp+0x1698]: saved K value; also used as K==9/5 check for seasons; meaning beyond "K saved" unknown [?]
- 0x67b1a70/0x67b2260/0x67b3180/0x67b3870/0x67b2A60: replace body A's flag-0x4a vcall + u16 pool 0x8a8 push sequence in body D's item emit; exact function unknown [?]
- Body D calls 0x67e1660 twice (destroy geometry) where body A calls 0x678e020 (destroy item) + 0x67e1660 (destroy geometry); reason unknown [?]

## Verification
- All disassembly lines copied exactly from rdis output as `0xRVA instruction`.
- Body D range 0x66f4fcb..0x66f6e36 fully covered (Steps 1-6).
- Separate property-registration functions sub_66f70a1/sub_66f77bc/sub_66f7eba documented (Steps 7-9) — reached from epilogue area, outside body D boundary.
- Tags: [V]=seen in disassembly at cited RVA; [I]=inferred; [?]=unknown.
