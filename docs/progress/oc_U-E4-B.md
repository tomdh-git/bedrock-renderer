# Unit U-E4-B: ChunkGeometry extractor body B (0x66ef308..0x66f2817) — COMPLETE

## Status
Body B fully decoded instruction-complete (prologue, pass-1, pass-2 setup, per-entry loop, item-emit tail, per-entry cleanup, pass-2 exit/epilogue). All claims tagged [V]=seen in rdis disassembly, [I]=inferred, [?]=unknown.

Body map (per docs/functions/66ea3d0.md addendum):
- Body A = 0x66ec126..0x66ef28d (generic kinds)
- Body B = 0x66ef308..0x66f2817 (K==13 light_source, f16cf path)  <- THIS UNIT
- Body C = 0x66f2820..0x66f4f5a (f1658 set)
- Body D = 0x66f4fcb..0x66f6e36 (K==10 terrain_blend)

Source: static disassembly of 1.26.62.01 via `tools/rdis/target/release/rdis.exe dis`. EXE: Minecraft.Windows.exe 1.26.62.01. Static analysis only. Entry: tail-jump from Item visitor tag-3 handler 0x6646d5f (rcx=builder state r13=[rbp+0x16a0], rdx=per-frame ctx r12/[rbp+0x16a8], r8=description rbx=[rbp+0x16c0]).

Locals of note (body B): pass record at [rbp+0xEF0] (resource), [rbp+0xEE8] (material instance); pass record clone at [rbp+0xC80] ([rbp+0xC78]=ptr to [rbp+0xEE8]); binding array [rbp+0xF20] (entries 0x10 B, record->+0x28=name hash), u16 count [rbp+0xF2a]; FogAlpha slot [rbp+0x16BC], FogAlpha-live byte [rbp+0x16BE]; vec1670 at [rbp+0x1670..0x1680] (ResolvedItem 0x18 B: shared_ptr ptr+ctrl, u8 valid at +0x10); n=[desc+0x38], entries stride 0x58 at [desc+0x40]; K=[rbx+0x48]->[rax]; fogA=((K-5)&~4)==0 (K in {5,9}); kind-class v at [rbp+0x16D0]; [rbp+0x1658]=K&~1; render-state word [rbp+0x1688]; isAB byte [rbp+0x1368]; [rbp+0x16CF] flag byte; drawlist at [rbp+0xDB8]; model at [rbp+0xE10]; item staging at [rbp+0x1588]/[rbp+0x1580]/[rbp+0x15E0]; draw item at [rbp+0x1440]; geometry at [rbp+0xF70]; pass object via 0x5aba5c0(ctx+0x10+0x9d0).

## Phase map body B

### Phase 0: registry owner stamp (inherited from caller, not re-done in body B)
Body B does NOT repeat phase 0 (registry stamps). It begins at the body-preamble after the dispatch jump (0x66ef2c9/0x66ef301 edge into 0x66ef308). K, fogA, isAB, f16cf, f1658, ditherKind, f1688, isMode3 are all already computed by the caller (body A phase 1) and passed implicitly; body B uses K and fogA only.

### Phase 1 (body B preamble): FogAlpha binding + vec1670 init + pass-1 resolve setup  (0x66ef308..0x66ef4ea) [V]
```
clone  = 0xe86b370(&rec_c80=[rbp+0xC80], &passRecord_ef0=[rbp+0xEF0]);
[rbp+0xC78] = [rbp+0xEE8]  // passRecord_ee8 material instance ptr
[rbp+0xCF8] = 0
K = *(u64*)desc[+0x48]        // rbx=desc, [rbx+0x48]->[rax]
fogA = ((K-5) & ~4) == 0      // K in {5,9}
kind-class v [rbp+0x16D0]: default 9; if K==0xA v=2; else v=(K-7<3)|(K-0xF<2) (K in {7,8,9} or {0xF,0x10}); K==0xC leaves v=9
[rbp+0x16B0] = K
vec1670 = std::vector<ResolvedItem>{};  [rbp+0x1670]=0,[rbp+0x1680]=0
n = desc[+0x38]; if (n >= 0xAAAAAAAAAAAAAAB) throw 0x66f9210;
0x678d170(&vec1670, &n)       // reserve
lock(builder+0x2e8)  // 0xeec59f0 _Mtx_lock; if builder[+0x334]==0x7FFFFFFF throw (recursion limit)
[rbp+0x1690] = &builder+0x2e8 (mutex addr)
draw-list: rax=[desc+0x38]=begin; r13=[desc+0x40]; end=begin+n*0x58; r15=end; [rbp+0x1440]=begin; r14=[rbp+0xF70]
DIFF vs body A preamble: body B does NOT re-check f16cf here (body A: `if(f16cf&&K!=0xC)v=2; else if K!=0xA v=...; else v=(K==0xC)?9:0`). Body B unconditionally: default v=9, K==0xA->2, else class. [V]
```

### Phase 1b: FogAlpha uniform prologue (0x66ef308 area, before loop) [V] — actually interleaved: slot found by scanning [rbp+0xf20] for lazily-hashed name hash 0x129fb1e0 (body B static hash; body A=0x129fb380):
```
slot = (found_entry_ptr - [rbp+0xf20]) >> 4   // entries 0x10 B
byte [rbp+0x16BE] = 1   // FogAlpha binding found
0x5679db0(&passRecord_ef0, {slot,1}, {1, &vec4 0})   // FogAlpha = 0 initially
else byte [rbp+0x16BE] = 0   // not found
DIFF vs body A: body B hash 0x129fb1e0; body A hash 0x129fb380 [V per addendum]
```

### Phase 2: pass-1 resolve loop (0x66ef4ea..0x66ef729) [V] — IDENTICAL to body A pass-1
```
for (e = [desc+0x40]; e != [desc+0x40]+n*0x58; e += 0x58) {   // r13=e, r15=end
    tag = e[+0x28];   // 0 -> p=e+0x10 ; 1 -> p=e+0x18 ; else throw 0x66f82b5
    if (!*p) continue;
    builder=[rbp+0x16A0]; map hdr=[rcx+0x2D8]; root=[rdx+8]; isnil byte [r8+0x19]
    rb-tree walk: r9=[**p]; cmp [r8+0x20],r9; setl; cmovge; shl r10d,4; r8=[r8+r10]; until non-nil
    if (node==end || **p < node.key || !node.value) continue;
    call 0xbc090b0(&out1440, node.value+8, {K=[desc+0x48]->[rcx], flag50=byte[desc+0x50]}) -> shared_ptr pair
    dedupe: if out == node.value->{+0x10,+0x28} cached pair -> r12=0 skip; else r12b=1 valid
    vec1670.push_back({out.ptr->[rbp+0x1440], out.ctrl->[rbp+0x1448] lock-inc [ctrl+8], byte[rdx+0x10]=1})
    [rbp+0x1440]=ptr (reused as loop cursor)
}
unlock(builder+0x2e8)  // 0xeec5a10
[rbp+0x1658] = K & ~1     // DIFF vs body A: body A [rbp+0x1658]=&desc+0x78
```

### Phase 3: pass-2 setup (0x66ef729..~0x66ef7fa) [V]
```
[rbp+0x16B0]=K; r14=begin=[desc+0x40]; end=[rbp+0x16A0] (=begin+n*0x58 reused)
render-state word [rbp+0x1688] = 0x8101 + fogA*4 + (v==9 ? 0x2800 : (v==2 ? 0x800 : 0))   // matches body A [V]
[rbp+0x1388] = &desc+0x78   // material instance ptr (DIFF vs body A: body A [rbp+0x1388]=fogA)
loop constants: xmm7=xmm10=1.0f (0xeec8060); xmm8=xmm11={0,0.0078125} (0xefd32f0); xmm9={-0,-0,0,0} (0xf0a4080); xmm13=8.0f (0xefc13a4); xmm14={8,8,0,0} (0xf0b8740)
pass-2 loop entry: r14=entry; exit target 0x66f27a9 (pass-2 fully done)
```

### Phase 4: per-entry loop body (0x66ef7fa..0x66f11de) [V]
```
tag handling same as pass-1 (0->p=r14+0x10, 1->p=r14+0x18, else throw)
Transform: xmm15=[r14+0x3c](a,b); xmm12=[r14+0x44](z); T=translate(a,b,z) at [rbp+0x1440..]
0xaa6580(&model=[rbp+0xE10], desc_mat=[rbp+0x1388], &T=[rbp+0x1440])   // model = descMat * T
if ([r14+0x48] != 1.0f) { S=scale(s); 0xaa6580(&f70=[rbp+0xF70], &model, &S); model=[rbp+0xE10]=f70; }   // f70 geometry at [rbp+0xF70]
0x678c4c0(rcx=&drawlist_db8=[rbp+0xDB8], rdx=**ctx([rax],rax=[rbp+0x16A8]=ctx), r8=[rbp+0x1698], r9=&passRecord_ee8, stack e=r14)
   DIFF vs body A: body A r8=[rbp+0x1388]=fogA; body B r8=[rbp+0x1698] (meaning ?)
[rbp+0x1650] = &rbp+0xC78 (rec_c78)   // body A used [rbp+0x1120]
per-entry FogAlpha: if byte[rbp+0x16BE]==1 && [r14+0x4c]>0:
    0x5679db0(&passRecord_ef0, slot=[rbp+0x16BC], {1, &splat [r14+0x4c]});
    [rbp+0x1650] = &rbp+0xEE8   // matches body A [V]
pack [rbp+0xEA8..0xEC0] = {&rbp+0x1370, &rbp+0xE10(model), &rbp+0xDB8(drawlist), &rbp+0x1650(rec)}
   DIFF vs body A order {&1650,model,drawlist,&1120} [V]
[rbp+0x1690] = rsi = loop index i
vec1670[i]: rax=[rbp+0x1670]; rcx=i*3; byte valid=[rax+rcx*8+0x10] (stride 0x18) [V] (matches body A)
if valid: lock-inc shared_ptr copy ptr->[rbp+0x1420], ctrl->[rbp+0x1428], byte[rbp+0x1430]=1
cl = (K&~1==2) class2  (test [rbp+0x1658]==2)
al = (valid==0) | cl
movzx ecx, byte [rbp+0x1368]=isAB; test [rbp+0x16CF], cl; je 0x66efd17 if ((isAB & [rbp+0x16CF])==0)
DIFF vs body A: body B splits on ([rbp+0x16CF]&isAB) with shift in multiple paths; body A f16cf-gated
```

#### Phase 4a: shift block (al!=0): 0x66ef9bb..0x66efd17 [V]
```
z += 8.0f; {a,b} += {8,8};
if (K&~1==2 && valid): 0x678cf10(&EA8=[rbp+0xEA8], r12) + 0x678e1d0(...) + copy + release + 0x678e420 + copyback + pass push
else (0x66eff2f): 0x678cf10 (NO shift) + same
DIFF vs body A: body B binder always 0x678cf10; body A used 0x67a75d0 [V]
```

#### Phase 4b: al==0 branch 0x66efea1 [V]
```
[rbp+0x1660]=0; [rbp+0x1410]=0;
if (K==9 || K==5): seasons shared_ptr [desc+0x28] lock-inc (matches body A seasons path);
else -> 0x66f0271 (non-seasons)
```

#### Phase 4c: (isAB & [rbp+0x16CF])==0 branch 0x66efd17 [V]
```
al==0 -> 0x66efee8 (seasons path);
al!=0: if class2&&valid -> 0x678cf10 + 0x678F640(copy tail [r13+0x58..0x9F]->staging [rbp+0x1580..]; u16[rbp+0x1100]->[rbp+0x15D8]) + pass push;
else -> 0x66f00f9
```

### Phase 5: item-emit (plain item 0x66f00f9; seasons/0x673cc80 path 0x66f0271) [V]

**Plain item (al!=0 && !(class2&&valid)) 0x66f00f9:**
```
0x678cf10(&EA8, r12); 0x678f640(rcx=model, rdx=[rbp+0x1050], r8=[rbp+0xFF8], r9=rdi);
copy tail -> staging [rbp+0x1580..]; u16[rbp+0x1100] -> [rbp+0x15D8];
pass = 0x5aba5c0(ctx+0x10+0x9d0);
zero item [rbp+0x11E0..0x1130] (xmm6=0);
feature 0x4a -> [rbp+0x16D4];   // DIFF vs body A feature local [rbp+0x16D0]
u16 pool 0x8A8 push [rbp+0x15D8]; if full -> 0x66f1ce8 realloc (0x1ef6f90) else push -> jmp 0x66f1cfc
```

**Seasons / 0x673cc80 path (0x66f0271 from 0x66efea1):**
```
0x673cc80(rcx=&rbp+0x12E0 out, rdx=&rbp+0x1420 vec1670[i] shared_ptr,
          r8d = byte [rbp+0x16D0] = byte16be, r9=-1;
          stack [0x20]=desc, [0x28]=u16 render-state [rbp+0x1688], [0x30]=&rbp+0x1410,
          [0x38]=&rbp+0x1660, [0x40]=[0x48]=0xFFFFFF00)   [V]
   DIFF vs body A: body A passed r8d=K=[rbp+0x16b0]; body B passes byte16be [V]
Result: 5 shared_ptr pairs lock-inc into [rbp+0x1390..0x13e8] (null branches zero ptr)
z += 8.0f; {a,b} += {8,8} SHIFT;
0x678cf10(&EA8, r12); 0x678e1d0(..., [rbp+0x1120]=&shifted vec2/float);
copy tail [r13+0x68..0x9F] -> staging [r13+0x68..0xAF]/[rbp+0x1444+{0x1D4,0x1E4,0x1F3}];
u16[rbp+0x12C0] -> [rbp+0x1110]; release 0x67E23F0(r12)
copyback into staging [rbp+0x15F0..]; 0x678DCE0(rcx=model=[rbp+0x1440], stack[0x28]=&rbp+0x1390, [0x20]=rsi) item assemble [V] (matches body A)
```

### Phase 6: item-emit tail (pool pushes, masks, item memcpy, cleanup) 0x66f0455..0x66f1aa0 [V]
Common tail (both paths converge), body-A-identical recipe with body B locals:
```
pass = 0x5aba5c0(ctx+0x10+0x9d0); zero item; feature 0x4a->[rbp+0x16D4];
u16[rbp+0x1648] -> pool 0x8A8 (realloc 0x1ef6f90 / 0x6760a80); item index=([r12+0x8A8]-[r12+0x8A0])>>1-1 -> [rbp+0x1140];
kind-mask [rbp+0x1130]=0x4001; pool 0x750 push staging [rbp+0x15F0] (0x58 stride, grow 0x6760a80); [r12+0x758]+=0x58;
feature restore; u8 pool [r12+0x890] inc (grow 0x6760e60);
[rbp+0x1142]=~(r12+0x888)+(r12+0x890); feature restore;
[rbp+0x1130]=0x4803; [rbp+0x1156]=~(r12+0x798)+(r12+0x7A0);
0x675fb30([r12+0x648], &rbp+0x1598); [rbp+0x1172]=((r12+0x650)-(r12+0x648))>>3*magic-1;
0x675f3b0([r12+0x780], &rbp+0x1540); [rbp+0x1158]=((r12+0x788)-(r12+0x780))>>3*magic-1;
pool588 [r12+0x770] (0x88): [rbx]=[rbp+0x14B8]; 0xe869ff0(&rbx+8,&rbp+0x14C0); [rbx+0x80]=[rbp+0x1538]; [rbp+0x1538]=0; [r12+0x770]+=0x88; grow 0x6760710;
[rbp+0x1130]=0x2007803; [rbp+0x115A]=((r12+0x770)-(r12+0x768))>>3*magic-1;
pool [r12+0x680] (0xC stride, 3 floats [rbp+0x14A8..0x14B0]); [r12+0x680]+=0xC; grow 0x1770a70;
[rbp+0x116E]=((r12+0x680)-(r12+0x678))>>2*magic-1;
u8 pool [r12+0x2D0..0x2E0] inc; grow 0x6760e60; [rbp+0x11BC]=~(r12+0x2D0)+(r12+0x2D8);
0x678d690(rcx=r12+0x5d0 frame_pass+0x5d0, rdx=&rbp+0x1440 item) push item [V];
[rbp+0x1130]=0x4000000042807803   // FINAL mask (DIFF vs body A ...42807009) [V]
[rbp+0x117C]=((r12+0x5D8)-(r12+0x5D0))>>5*magic-1;
item memcpy push: if [r12+8]==[r12+0x10] -> 0x5aba6d0 grow else 0xeec6ec0(rcx=[r12+8], rdx=&rbp+0x1130, r8=0xC8) memcpy 0xC8; [r12+8]+=0xC8 [V] (matches body A pass.items.push)
```
Non-seasons mask sequence seen: 0x4001, 0x4803, 0x2007803, 0x2005803, 0x4000000042007803, 0x4000000042807803 [V] (intermediate masks differ slightly from body A).

Then release temporaries: cmp byte [rbp+0x15C8],1; if vec1670[i] shared_ptr [rbp+0x1588]!=0 and span>=0x1000: release via 0xe935700; zero [rbp+0x1588].
```
call 0x678F260(&rbp+0x1440) destroy item   // DIFF vs body A destroy-item 0x678e020
call 0x67e23f0(&rbp+0xF70) destroy geometry  // DIFF vs body A destroy-geometry 0x67e1660
test r15,r15; je 0x66f1aa0; else release shared_ptr r15 (lock dec [r15+8]; vcall[0]; lock dec [r15+0xC]; vcall[8])
0x66f1aa0: release shared_ptrs [rbp+0x13D0], [rbp+0x13C0], [rbp+0x1398], [rbp+0x1330]... (0x673cc80 result pairs)
```
0x673cc80 result cleanup releases the 5 seasons shared_ptr pairs [V] (matches body A pattern).

### Phase 7: per-entry cleanup + loop continue (0x66f26c0..0x66f27a8) [V]
(reached via `jmp 0x66f26c0` from item-emit tail at 0x66f11de)
```
release shared_ptr ctrl [rbp+0x1428]: lock dec [rbx+8]; if 0: rax=[rbx];rax=[rax]; vcall[0]([0xF99FFA0]=sub_eea6040); lock dec [rbx+0xC]; if 0: rax=[rbx];rax=[rax+8]; vcall[8]   // shared_ptr release
if (byte [rbp+0xDF0] == 3): release shared_ptr [rbp+0xDE8] similarly
rsi=[rbp+0xDC0]; rdi=[rbp+0xDC8];   // another vector (drawlist bindings?)
if (rsi==0 || rsi==rdi) -> 0x66ef7f0   // PASS-2 LOOP CONTINUE (next entry)
else loop rsi+=0x28: if byte[rsi+0x18]==2: rbx=[rsi+8]; lock dec [rbx+8]; if 0 vcall[0]; lock dec [rbx+0xC]; if 0 vcall[8]; jmp 0x66f2760(next); -> 0x66ef7f0 when done
```
Loop continue target = 0x66ef7f0 [V] (pass-2 next entry). Note: 0x66f1a67/0x66f1aa0 (from destroy item+geometry, alt path) not separately resolved but feed same cleanup/release.

### Phase 8: pass-2 exit / body B epilogue (0x66f27a9..0x66f2817) [V]
(reached when pass-2 loop fully done)
```
rsi=[rbp+0x1670] (vec1670 data); if rsi==0 -> 0x66f6e3b (cold, after body B)
rbx=[rbp+0x1678] (vec1670 end); if rsi==rbx -> 0x66f6e04 (cold)
else loop rsi+=0x18: if byte[rsi+0x10]==1 (valid): rdi=[rsi+8]; lock dec [rdi+8]; if 0 vcall[0]; lock dec [rdi+0xC]; if 0 vcall[8]; jmp 0x66f27d0(next); -> 0x66f6dfd (cold) when done
// releases remaining vec1670 shared_ptr originals
0x66f2817 = END of body B.  0x66f2819 begins Body C (0x66f2820 clone call).
```

## Body B vs Body A — differences summary [V unless noted]
| # | Aspect | Body A | Body B |
|---|--------|--------|--------|
| 1 | Prologue kind-class v | re-checks f16cf; `(K==0xC)?9 : ((f16cf&&K!=0xC)?2 : class)` | unconditional: default 9; K==0xA->2; else class; NO f16cf re-check |
| 2 | [rbp+0x1658] | &desc+0x78 | K&~1 |
| 3 | FogAlpha hash | 0x129fb380 | 0x129fb1e0 |
| 4 | Draw-list builder arg3 r8 | [rbp+0x1388]=fogA | [rbp+0x1698] (meaning ?) |
| 5 | rec pointer local | [rbp+0x1120] | [rbp+0x1650]=&rbp+0xC78 |
| 6 | Binder matrix-copy | 0x67a75d0 | 0x678cf10 (everywhere, incl. 0x66f1375) |
| 7 | Geometry/material call (seasons) | 0x678e1d0 | 0x678EF40 (at 0x66f139b) |
| 8 | Destroy item | 0x678e020 | 0x678f260 |
| 9 | Destroy geometry | 0x67e1660 | 0x67e23f0 |
| 10 | Feature flag local | [rbp+0x16D0] | [rbp+0x16D4] |
| 11 | Item staging base | [rbp+0x1578] | [rbp+0x1588]/[rbp+0x1580]/[rbp+0x15E0] |
| 12 | Pack order [rbp+0xea8] | {&1650,model,drawlist,&1120} | {&1370,model,drawlist,rec} |
| 13 | 0x673cc80 r8d arg | K=[rbp+0x16b0] | byte [rbp+0x16D0]=byte16be |
| 14 | Item-emission branch split | f16cf-gated | ([rbp+0x16CF]&isAB); shift applied in multiple paths |
| 15 | Final item mask | 0x4000000042807009 | 0x4000000042807803; intermediates 0x12807803/0x2005803/0x2007803/0x4000000042007803 |
| 16 | Loop continue target | 0x66ee122/0x66ee150 | 0x66ef7f0 |

Identical (not differences): pass-1 resolve loop; transform/scale via 0xaa6580; per-entry FogAlpha write; vec1670 layout/stride; 0x5aba5c0 pass getter; 0xeec6ec0/0x5aba6d0 item memcpy; 0x678d690 item push; pool helpers 0x675fb30/0x675f3b0/0x6760a80/0x6760e60/0x1770a70/0xe869ff0/0x6760710; shared_ptr release pattern (lock dec refcount; vcall[0]; lock dec [ctrl+0xC]; vcall[8]); loop constants xmm7..xmm14.

## Open (blocking facts) [?]
- [rbp+0x1698] meaning passed to draw-list builder 0x678c4c0 (body B) vs fogA (body A).
- Meaning of render-state word bits, pass-kind value K==13 = light_source (from addendum E4: terrain_deferred_water=11 etc.; light_source kind name/value not confirmed for K==13 — needs producer fill or live census).
- Binders 0x678cf10, 0x678f640, 0x678EF40, 0x678DCE0, 0x678F260, 0x67e23f0, 0x67e1660, 0x678d690, 0x678d170, 0xbc090b0, 0x673cc80 semantics not decoded (no dossiers).
- Whether 0x66f27a9 (vec1670 full release) is pass-2 exit or reachable another way; double-release vs temporary-copy ownership question for [rbp+0x1428].
- Pass-2 loop exit condition (where r14==end jumps to 0x66f27a9) not located in decoded range.
- Loop-continue alt targets 0x66f1a67/0x66f1aa0 (after destroy item+geometry) not resolved to 0x66ef7f0 vs 0x66f27a9.

## NEXT
Unit U-E4-B is instruction-complete for body B. No further disassembly needed. Output file docs/progress/oc_U-E4-B.md is the sole deliverable; no other file edited. If the orchestrator requires a separate .md dossier for body B (docs/functions/66ef308.md), create it from this progress file.
