# Progress: U-E4-A2 — chunk extractor body A remainder 0x66ed987..0x66ef28d

## NEXT
Body A complete through 0x66ef28d (end boundary). Nothing remaining in this unit.

## Status
- Dossier 66ea3d0.md: body A decoded through 0x66ed973 (summary only; mask table [~]). Remainder 0x66ed987..0x66ef28d now fully transcribed in this file (phases 9..32).
- Disassembly: dumped 1312 instructions (C:\Users\Atomi\AppData\Local\Temp\opencode\bodyA_remainder.asm, chunks 0/320/640/960/1280).
- Phases transcribed: 0x66ed987..0x66edc57 (phases 1-8, prior), 0x66edc57..0x66ef28d (phases 9-32, this file).
- Tags: [V] = seen in disassembly at cited RVA; [I] = inferred; [?] = unknown.

## Transcribed phases

### Phase 1: 0x66ed987..0x66ed9e2 — build args and call 0x673cc80 (shader-binding block) [V]
Sets up a stack arg block at [rsp+0x20..0x48] and calls the binding-block builder.
```
out          = &rbp+0x12e0;
arg2         = &rbp+0x1420;
r8d          = [rbp+0x16b0] (u32);
r9           = 0xffffffffffffffff (-1);
[rsp+0x20]   = [rbp+0x16c0] (ptr, seasons resource [I]);
[rsp+0x28]   = (u16)[rbp+0x16d4] (render-state word);
[rsp+0x30]   = &rbp+0x1660;
[rsp+0x38]   = &rbp+0x1370;
[rsp+0x40]   = 0xffffff00;
[rsp+0x48]   = 0xffffff00;
0x673cc80(out, arg2, r8d, -1, [rsp+0x20..0x48]);   // [V] 0x66ed9e2
```
Semantics [I]: 0x673cc80 fills a shader-binding block at rbp+0x12e0 (five {ptr,ctrl} shared_ptr pairs) and returns refcount-incremented copies.

### Phase 2: 0x66ed9e7..0x66eda3e — copy binding pair0 + u16 pair1 into rbp+0x1390..0x13b0 [V]
```
tmp = [rbp+0x12e8];
if (tmp) lock++ [tmp+8]; else tmp = 0;
[rbp+0x1390] = [rbp+0x12e0]; [rbp+0x1398] = tmp;                    // pair0 ptr/ctrl

src = &rbp+0x12f0;
u16 = *(u16*)(src+0x10);
dst = &rbp+0x13a0;
*(u16*)(dst+0x10) = u16;
*(u128*)dst = *(u128*)src;        // 16 bytes
*(u128*)(dst+0x18) = 0;           // zero
```
[V] 0x66ed9e7..0x66eda3a. pair1 is a {u16,16-byte-payload} entry (not a shared pair).

### Phase 3: 0x66eda3e..0x66edaa2 — copy binding pair2 (shared_ptr) into rbp+0x13b8..0x13c0 [V]
```
tmp = [rbp+0x1310];
if (tmp) lock++ [tmp+8]; else tmp = 0;
[rbp+0x13b8] = [rbp+0x1308];
[rbp+0x13c0] = tmp;
```
[V] 0x66eda3e..0x66edaa2.

### Phase 4: 0x66edaa2..0x66edaf2 — copy binding pairs 3 and 4 into rbp+0x13c8..0x13e8 [V]
Pair 3:
```
tmp = [rbp+0x1320];
if (tmp) lock++ [tmp+8]; else tmp = 0;
[rbp+0x13c8] = [rbp+0x1318];
[rbp+0x13d0] = tmp;
```
Pair 4:
```
rbx = [rbp+0x1330]; if (rbx) lock++ [rbx+8]; else rbx = 0;
[rbp+0x13d8] = [rbp+0x1328];
[rbp+0x13e0] = rbx;
[rbp+0x13e8] = [rbp+0x1338];
```
[V] 0x66edaa2..0x66edaeb. Result: binding block of shared_ptr copies at rbp+0x1390..0x13e8 [I].

### Phase 5: 0x66edaf2..0x66edb29 — draw-list descriptor prep + geometry/material fill [V]
```
rcx = &rbp+0xea8;          // descriptor in
r15 = &rbp+0xf70;          // descriptor out
0x67a75d0(&rbp+0xea8, &rbp+0xf70);                  // [V] 0x66edb03  (ChunkDrawDescriptor pack [I])
rcx = &rbp+0x1440;         // draw item out
rdx = r13;                 // draw-list entry (ChunkDrawListEntry [I])
r8 = &rbp+0xff8;
r9 = r15 = &rbp+0xf70;
0x678ef40(&rbp+0x1440, r13, &rbp+0xff8, &rbp+0xf70);   // [V] 0x66edb29  (geometry+material fill [I])
```
[V] 0x66edaf2..0x66edb2e. r13 is the current draw-list entry; fields +0x50,+0x60,+0x78,+0x88,+0x97 read below [V].

### Phase 6: 0x66edb2f..0x66edb90 — build staging block at rbp+0x15d8 from entry fields [V]
```
staging = &rbp+0x15d8;
*(u32*)(staging+0x10) = r13->+0x60;         // u32
*(u128*)staging = *(u128*)(r13+0x50);       // 16 bytes
```
[V] 0x66edb2f..0x66edb42.

### Phase 7: 0x66edb45..0x66edb90 — copy flag byte + 16 bytes, copy 3 vec4s entry->rsi, load word [rbp+0x10f8] [V]
```
[rbp+0x15ec] = (u8)[rbp+0x10b4];                    // flag byte
*(u128*)(&rbp+0x15f0) = *(u128*)(&rbp+0x10b8);      // 16 bytes
[rbp+0x1630] = (u16)[rbp+0x10f8];                   // u16
```
and (the three movups below use r13->rsi; rsi base [?] set before this range):
```
rsi->+0x1bc = *(u128*)(r13+0x78);
rsi->+0x1cc = *(u128*)(r13+0x88);
rsi->+0x1db = *(u128*)(r13+0x97);   // unaligned movups
```
[V] 0x66edb45..0x66edb91.

### Phase 8: 0x66edb98..0x66edc57 — resolve pass object + query feature flag 0x4a, then push u16 to pool 0x8a8 [V]
```
rcx = [rbp+0x16a8];                 // frame ctx
rcx = rcx->+0x10;
r15 = 0x5aba5c0(rcx + 0x9d0);       // pass object [V] 0x66edbab
// zero 12 xmm slots at r14-0xd8..r14-0x28 [V] 0x66edbb4..0x66edbfa
mem128(r14-0xd8 .. r14-0x28, 0, 12);
rcx = *(u64*)rip+0xbc505a7;         // vtable/interface ptr [V] 0x66edc02
al = (*rcx->+0x10)(dl=0x4a);        // feature-flag query vcall [V] 0x66edc0c..0x66edc12
[rbp+0x16d0] = al;                  // save flag
rdx = r15->+0x8a8;   // u16 pool end
if (rdx == r15->+0x8b0) { 0x1ef6f90(&r15+0x8a0, &rbp+0x1630); }   // grow path [V] 0x66edc43
else { *(u16*)rdx = (u16)[rbp+0x1630]; r15->+0x8a8 += 2; }        // fast push [V] 0x66edc2f
```
[V] 0x66edb98..0x66edc56. The 12 xmm stores zero a 0xc0-byte region [I].

### Phase 9: 0x66edc57..0x66edcb4 — feature-flag restore vcall + pool 0x8a8 item-index computation [V]
```
rcx = *(u64*)[rip+0xbc50552];       // vtable/interface ptr [V] 0x66edc57
rax = [rcx]; rax = [rax+0x10];      // vtable[0x10] method [V] 0x66edc5e..0x66edc61
dl = [rbp+0x16d0];                  // saved flag byte
call qword ptr [rip+0x92b232e];     // vcall: restore feature flag 0x4a [V] 0x66edc65..0x66edc6c
[rbp+0x16d0] = al;                  // [V] 0x66edc72..0x66edc73
[rbp+0x1130] = 1;                   // u32 kind-mask low word = 1 [V] 0x66edc7e
eax = [r15+0x8a8] - [r15+0x8a0];    // pool 0x8a8: end - begin [V] 0x66edc7e..0x66edc85
shr eax, 1;                         // divide by 2 (u16 count) [V] 0x66edc8c
dec eax;                            // item index = count - 1 [V] 0x66edc8e
mov word ptr [rbp+0x1140], ax;      // store item index [V] 0x66edc90
```
[V] 0x66edc57..0x66edc97. The item index is computed as `(pool_end - pool_begin)/2 - 1` for the u16 pool at pass+0x8a0/0x8a8 [I].

### Phase 10: 0x66edcb4..0x66edd40 — push 0x58-byte state entry onto pool 0x750 (fast path) [V]
```
vcall flag 0x4a save/restore: rcx = *(u64*)[rip+0xbc50512]; dl = 0x4a; call [rip+0x92b22f3]; [rbp+0x16d0] = al   // [V] 0x66edc97..0x66edcae
rdx = [r15+0x758];   // pool 0x750 write cursor
if (rdx == [r15+0x760]) goto grow 0x66edd40;      // pool full? [V] 0x66edcb4..0x66edcc2
// fast path: copy staging block rbp+0x15d8 (0x58 bytes) into [rdx]
[rdx+0x10] = [rbp+0x15d8+0x10];                   // u32 [V] 0x66edcc4..0x66edcce
[rdx+0x00..0x10] = movups [rbp+0x15d8];           // 16 bytes [V] 0x66edcd1..0x66edcd4
[rdx+0x14] = (u8)[rbp+0x15ec];                    // flag byte [V] 0x66edcd7..0x66edcde
[rdx+0x18] = float [rbp+0x15f0];                  // [V] 0x66edce1..0x66edce9
[rdx+0x1c] = float [rbp+0x15f4];                  // [V] 0x66edcee..0x66edcf6
[rdx+0x20] = float [rbp+0x15f8];                  // [V] 0x66edcfb..0x66edd03
[rdx+0x24] = float [rbp+0x15fc];                  // [V] 0x66edd08..0x66edd10
[rdx+0x28..0x38] = movups [rsi+0x1bc];            // vec4 [V] 0x66edd15..0x66edd1c
[rdx+0x38..0x48] = movups [rsi+0x1cc];            // vec4 [V] 0x66edd1c..0x66edd23
[rdx+0x47..0x58] = movups [rsi+0x1db];            // vec4 (unaligned, 15 bytes) [V] 0x66edd23..0x66edd32
[r15+0x758] += 0x58;                              // advance cursor [V] 0x66edd36
jmp 0x66edd54;
```
[V] 0x66edcb4..0x66edd3e. The staging block layout matches the 0x58-byte DrawItem/state entry template from docs/functions/66d9af0_builders.md [I].

### Phase 11: 0x66edd40..0x66edd54 — pool 0x750 grow path [V]
```
lea rcx, [r15+0x750];   // pool base
lea r8, [rbp+0x15d8];   // staging source
call 0x6760a80;         // pool grow + push [V] 0x66edd40..0x66edd4e
```
[V] 0x66edd40..0x66edd53. 0x6760a80 is the slow-path pool push helper [I].

### Phase 12: 0x66edd54..0x66edd89 — flag restore + pool 0x858 byte-push index [V]
```
rcx = *(u64*)[rip+0xbc50455]; dl = [rbp+0x16d0]; call [rip+0x92b2231];   // vcall flag 0x4a restore [V] 0x66edd54..0x66edd6f
eax = [r15+0x758] - [r15+0x750];   // pool 0x750: cursor - begin [V] 0x66edd70..0x66edd77
shr eax, 3;                        // divide by 8 (0x58-byte entries) [V] 0x66edd7e
imul eax, eax, 0xffff8ba3;         // magic multiply for division [V] 0x66edd81
dec eax;                           // item index [V] 0x66edd87
mov word ptr [rbp+0x115c], ax;     // store pool 0x750 item index [V] 0x66edd89
```
[V] 0x66edd54..0x66edd89.

### Phase 13: 0x66edd89..0x66eddc9 — flag restore + pool 0x860 u16 push [V]
```
rcx = *(u64*)[rip+0xbc50419]; dl = [rbp+0x16d0]; call [rip+0x92b21fa];   // vcall flag 0x4a [V] 0x66edd90..0x66edda6
[rbp+0x16d0] = al;                  // [V] 0x66eda7..0x66edda7
rdx = [r15+0x860];   // pool 0x860 cursor
if (rdx == [r15+0x868]) goto grow 0x66eddc9;      // pool full? [V] 0x66eddad..0x66edcbb
rdx++;                                           // fast push (u16 increment) [V] 0x66eddbd
[r15+0x860] = rdx;                               // [V] 0x66eddc0
jmp 0x66eddd6;
grow: lea rcx, [r15+0x858]; call 0x6760e60;       // byte-pool grow [V] 0x66eddc9..0x66eddd5
```
[V] 0x66edd89..0x66eddd5.

### Phase 14: 0x66eddd6..0x66ede09 — flag restore + [rbp+0x1146] = ~[r15+0x2d0] + [r15+0x2d8] [V]
```
rcx = *(u64*)[rip+0xbc503d3]; dl = [rbp+0x16d0]; call [rip+0x92b21af];   // vcall flag 0x4a [V] 0x66eddd6..0x66eddf1
[rbp+0x16d0] = al;                  // [V] 0x66eddf1..0x66eddf2
eax = [r15+0x2d0];                  // pool 0x2d0 begin [V] 0x66eddf2
not eax;                            // bitwise NOT [V] 0x66eddf9
add eax, [r15+0x2d8];               // add pool 0x2d8 cursor [V] 0x66eddfb
mov word ptr [rbp+0x1146], ax;      // item start index = ~begin + cursor [V] 0x66ede02
```
[V] 0x66eddd6..0x66ede02.

### Phase 15: 0x66ede09..0x66ede38 — flag restore + pool 0x648 u64 push (0x675fb30) [V]
```
rcx = *(u64*)[rip+0xbc503a0]; dl = [rbp+0x16d0]; call [rip+0x92b2181];   // vcall flag 0x4a [V] 0x66ede09..0x66ede1f
[rbp+0x16d0] = al;                  // [V] 0x66ede1f..0x66ede25
lea rcx, [r15+0x648];               // pool 0x648 base
lea rdx, [rbp+0x1588];              // source value
call 0x675fb30;                     // pool push helper [V] 0x66ede25..0x66ede38
```
[V] 0x66ede09..0x66ede38.

### Phase 16: 0x66ede38..0x66ede74 — pool 0x648 index + pool 0x780 u64 push (0x675f3b0) [V]
```
rcx = *(u64*)[rip+0xbc50370]; dl = [rbp+0x16d0]; call [rip+0x92b214c];   // vcall flag 0x4a [V] 0x66ede39..0x66ede54
[rbp+0x16d0] = al;                  // [V] 0x66ede54..0x66ede55
eax = [r15+0x650] - [r15+0x648];    // pool 0x648: end - begin [V] 0x66ede55..0x66ede5c
shr eax, 3;                         // divide by 8 [V] 0x66ede63
imul eax, eax, 0xffff8e39;         // magic multiply [V] 0x66ede66
dec eax;                            // item index [V] 0x66ede6c
mov word ptr [rbp+0x1172], ax;      // store index [V] 0x66ede6e
lea rcx, [r15+0x780];               // pool 0x780 base
lea rdx, [rbp+0x1530];              // source value
call 0x675f3b0;                     // pool push helper [V] 0x66ede75..0x66ede88
```
[V] 0x66ede38..0x66ede88.

### Phase 17: 0x66ede89..0x66ede9e — set mask word [rbp+0x1130] = 0x2005009 [V]
```
mov qword ptr [rbp+0x1130], 0x2005009;   // [V] 0x66ede89
```
[V] 0x66ede89.

### Phase 18: 0x66ede9e..0x66edf24 — pool 0x768 index + pool 0x770 u64 push (fast path) [V]
```
rcx = *(u64*)[rip+0xbc502f5]; dl = [rbp+0x16d0]; call [rip+0x92b20d6];   // vcall flag 0x4a [V] 0x66edeb4..0x66edeca
[rbp+0x16d0] = al;                  // [V] 0x66edeca..0x66edce1 (actually 0x66edcea..0x66edce1 -- store at 0x66edcea)
eax = [r15+0x788] - [r15+0x780];    // pool 0x768: end - begin [V] 0x66ede94..0x66ede9b
shr eax, 3;                         // divide by 8 [V] 0x66edea2
imul eax, eax, 0xffff8ba3;         // magic multiply [V] 0x66edea5
dec eax;                            // item index [V] 0x66edeab
mov word ptr [rbp+0x1158], ax;      // store index [V] 0x66edead
rcx = *(u64*)[rip+0xbc50232]; dl = [rbp+0x16d0]; call [rip+0x92b2013];   // vcall flag 0x4a [V] 0x66edf77..0x66edf8d
[rbp+0x16d0] = al;                  // [V] 0x66edf8d..0x66edf8e
r12 = [r15+0x770];   // pool 0x770 cursor [V] 0x66eded0
if (r12 == [r15+0x778]) goto grow 0x66edf24;      // pool full? [V] 0x66eded7..0x66edede
// fast path:
rax = [rbp+0x14a8];                 // [V] 0x66edee0
[r12] = rax;                        // 8-byte store [V] 0x66edee7
lea rcx, [r12+8];                   // [V] 0x66edeeb
lea rdx, [rbp+0x14b0];              // [V] 0x66edef0
call 0xe869ff0;                     // 16-byte copy (shared_ptr copy?) [V] 0x66edef7
rax = [rbp+0x1528];                 // [V] 0x66edefd
[r12+0x80] = rax;                   // store at +0x80 [V] 0x66edf04
[rbp+0x1528] = 0;                   // clear source [V] 0x66edf0c
[r15+0x770] += 0x88;                // advance cursor by 0x88 [V] 0x66edf17
jmp 0x66edf3b;
```
[V] 0x66ede9e..0x66edf22. Pool entry size is 0x88 bytes [I].

### Phase 19: 0x66edf24..0x66edf3b — pool 0x770 grow path [V]
```
lea rcx, [r15+0x768];               // pool 0x768 base
mov rdx, r12;                       // cursor value
lea r8, [rbp+0x14a8];               // source ptr
call 0x6760710;                     // pool grow + push [V] 0x66edf24..0x66edf35
```
[V] 0x66edf24..0x66edf3a.

### Phase 20: 0x66edf3b..0x66edf70 — flag restore + pool 0x768 index [V]
```
rcx = *(u64*)[rip+0xbc5026e]; dl = [rbp+0x16d0]; call [rip+0x92b204a];   // vcall flag 0x4a [V] 0x66edf3b..0x66edf56
[rbp+0x16d0] = al;                  // [V] 0x66edf56..0x66edf57
eax = [r15+0x770] - [r15+0x768];    // pool 0x770: cursor - begin [V] 0x66edf57..0x66edf5e
shr eax, 3;                         // divide by 8 [V] 0x66edf65
imul eax, eax, 0xfffff0f1;         // magic multiply [V] 0x66edf68
dec eax;                            // item index [V] 0x66edf6e
mov word ptr [rbp+0x115a], ax;      // store index [V] 0x66edf70
```
[V] 0x66edf3b..0x66edf70.

### Phase 21: 0x66edf70..0x66edfb0 — flag restore + pool 0x2d8 u16 push (increment) [V]
```
rcx = *(u64*)[rip+0xbc501ec]; dl = [rbp+0x16d0]; call [rip+0x92b1fc8];   // vcall flag 0x4a [V] 0x66edfbd..0x66edfd8
[rbp+0x16d0] = al;                  // [V] 0x66edfd8..0x66edfd9
eax = [r15+0x2d0];                  // pool 0x2d0 begin [V] 0x66edfd9
not eax;                            // bitwise NOT [V] 0x66edfe0
add eax, [r15+0x2d8];               // add pool 0x2d8 cursor [V] 0x66edfe2
mov word ptr [rbp+0x11bc], ax;      // item start index = ~begin + cursor [V] 0x66edfe9
rdx = [r15+0x2d8];   // pool 0x2d8 cursor [V] 0x66edf94
if (rdx == [r15+0x2e0]) goto grow 0x66edfb0;      // pool full? [V] 0x66edf9b..0x66edfa2
rdx++;                                           // fast push (u16 increment) [V] 0x66edfa4
[r15+0x2d8] = rdx;                               // [V] 0x66edfc0
jmp 0x66edfbd;
grow: lea rcx, [r15+0x2d0]; call 0x6760e60;       // byte-pool grow [V] 0x66edfb0..0x66edfb7
```
[V] 0x66edf70..0x66edfbc. (The [rbp+0x11bc] compute at 0x66edfd9..0x66edfe9 is interleaved with the pool push; shown together for clarity.)

### Phase 22: 0x66edfb0..0x66edfe9 — [rbp+0x11bc] = ~[r15+0x2d0] + [r15+0x2d8] [V]
(See Phase 21 — the compute at 0x66edfd9..0x66edfe9 is part of the same sequence.)
```
eax = [r15+0x2d0]; not eax; add eax, [r15+0x2d8]; [rbp+0x11bc] = ax;
```
[V] 0x66edfd9..0x66edfe9.

### Phase 23: 0x66edfe9..0x66ee018 — call 0x678d690 + set mask word [rbp+0x1130] = 0x4000000042007009 [V]
```
rcx = r15 + 0x5d0;                  // frame_pass + 0x5d0 [V] 0x66edff3
rdx = &rbp+0x1440;                  // draw item [V] 0x66edffa
call 0x678d690;                     // item emission into pass pool [V] 0x66ee001
mov qword ptr [rbp+0x1130], 0x4000000042007009;   // mask word [V] 0x66ee007..0x66ee011
```
[V] 0x66edfe9..0x66ee018.

### Phase 24: 0x66ee018..0x66ee031 — pool 0x5d0 index computation [V]
```
rcx = *(u64*)[rip+0xbc50171]; dl = [rbp+0x16d0]; call [rip+0x92b1f52];   // vcall flag 0x4a [V] 0x66ee038..0x66ee04e
[rbp+0x16d0] = al;                  // [V] 0x66ee04e..0x66ee04f
eax = [r15+0x5d8] - [r15+0x5d0];    // pool 0x5d0: end - begin [V] 0x66ee018..0x66ee01f
shr eax, 5;                         // divide by 32 (0x20-byte entries) [V] 0x66ee026
imul eax, eax, 0xffffaaab;         // magic multiply [V] 0x66ee029
dec eax;                            // item index [V] 0x66ee02f
mov word ptr [rbp+0x117c], ax;      // store index [V] 0x66ee031
```
[V] 0x66ee018..0x66ee038.

### Phase 25: 0x66ee031..0x66ee07e — pool 8 u16 push (0xc8 bytes) + flag restore [V]
```
rcx = *(u64*)[rip+0xbc5011b]; dl = [rbp+0x16d0]; call [rip+0x92b1ef7];   // vcall flag 0x4a [V] 0x66ee08e..0x66ee0a9
[rbp+0x16d0] = al;                  // [V] 0x66ee0a9..0x66ee0aa
rdx = [r15+8];   // pool 8 cursor
if (rdx == [r15+0x10]) goto grow 0x66ee07e;       // pool full? [V] 0x66ee055..0x66ee05d
r8d = 0xc8;               // 200 bytes [V] 0x66ee05f
rcx = rdx;                // dest [V] 0x66ee065
lea rdx, [rbp+0x1130];    // source (mask word) [V] 0x66ee068
call 0xeec6ec0;           // memcpy 0xc8 bytes [V] 0x66ee06f
[r15+8] += 0xc8;          // advance cursor [V] 0x66ee074
jmp 0x66ee08e;
grow: lea rcx, [r15]; lea r8, [rbp+0x1130]; call 0x5aba6d0;   // pool grow [V] 0x66ee07e..0x66ee088
```
[V] 0x66ee031..0x66ee08e.

### Phase 26: 0x66ee07e..0x66ee0aa — flag restore [V]
```
rcx = *(u64*)[rip+0xbc5011b]; dl = [rbp+0x16d0]; call [rip+0x92b1ef7];   // vcall flag 0x4a [V] 0x66ee08e..0x66ee0a9
[rbp+0x16d0] = al;                  // [V] 0x66ee0a9..0x66ee0aa
```
[V] 0x66ee08e..0x66ee0aa.

### Phase 27: 0x66ee0aa..0x66ee105 — conditional free: if byte [rbp+0x15c8] == 1 and [rbp+0x1588] != 0 [V]
```
if ((u8)[rbp+0x15c8] != 1) goto 0x66ee105;   // [V] 0x66ee0aa..0x66ee0b1
rcx = [rbp+0x1588];                   // pointer [V] 0x66ee0b3
if (rcx == 0) goto 0x66ee105;         // [V] 0x66ee0ba..0x66ee0bd
rdx = [rbp+0x1598] - rcx;             // size = end - begin [V] 0x66ee0bf..0x66ee0c6
if (rdx < 0x1000) goto 0x66ee0ee;     // small alloc: direct free [V] 0x66ee0c9..0x66ee0d0
rax = [rcx-8];                        // heap header [V] 0x66ee0d2
rcx -= 8; rcx -= rax;                 // adjust pointer [V] 0x66ee0d6..0x66ee0da
if (rcx >= 0x20) goto 0x66f82bb;      // out-of-range check [V] 0x66ee0dd..0x66ee0e1
rdx |= 0x27;                          // combine size with flags [V] 0x66ee0e7
rcx = rax;                            // [V] 0x66ee0eb
call 0xe935700;                       // free [V] 0x66ee0ee
```
[V] 0x66ee0aa..0x66ee0ee.

### Phase 28: 0x66ee0ee..0x66ee150 — free call + clear + item/geometry release + shared_ptr releases [V]
```
call 0xe935700;                       // free [V] 0x66ee0ee
lea rax, [rbp+0x1588];                // clear pointer [V] 0x66ee0f3
movups [rax], xmm6;                   // zero 16 bytes [V] 0x66ee0fa
mov qword ptr [rax+0x10], 0;          // zero +0x10 [V] 0x66ee0fd
rcx = &rbp+0x1440; call 0x678f260;    // release draw item [V] 0x66ee105..0x66ee10c
rcx = &rbp+0xf70; call 0x67e23f0;     // release geometry [V] 0x66ee111..0x66ee118
test rbx, rbx; je 0x66ee150;         // rbx = shared ctrl block? [V] 0x66ee11d
// shared_ptr release sequence (repeated for each pointer):
lock dec dword ptr [rbx+8]; jne done; call [rax] (dtor); lock dec dword ptr [rbx+0xc]; jne done; call [rax+8] (dealloc)
```
Releases at [rbp+0x13d0] (0x66ee150), [rbp+0x13c0] (0x66ee190), [rbp+0x1398] (0x66ee1d0), [rbp+0x1330] (0x66ee210), [rbp+0x1320] (0x66ee250), [rbp+0x1310] (0x66ee290), [rbp+0x12e8] (0x66ee2d0), [rbp+0x1668] (0x66ee310), [rbp+0x1378] (0x66ee350; then jmp 0x66ef170). [V] 0x66ee122..0x66ee393.

### Phase 29: 0x66ee350..0x66ef170 — release [rbp+0x1378] + release [rbp+0x1428] + conditional release [rbp+0xde8] [V]
```
rbx = [rbp+0x1378];                   // [V] 0x66ee350
if (rbx == 0) goto 0x66ef170;         // [V] 0x66ee35a
// shared_ptr release sequence [V] 0x66ee360..0x66ee393
jmp 0x66ef170;                        // [V] 0x66ee393
rbx = [rbp+0x1428];                   // [V] 0x66ef170
if (rbx == 0) goto 0x66ef1b0;         // [V] 0x66ef17a
// shared_ptr release sequence [V] 0x66ef17c..0x66ef1a7
if ((u8)[rbp+0xdf0] != 3) goto 0x66ef1f0;   // feature/check byte [V] 0x66ef1b0
rbx = [rbp+0xde8];                    // [V] 0x66ef1b9
if (rbx == 0) goto 0x66ef1f0;         // [V] 0x66ef1c0
// shared_ptr release sequence [V] 0x66ef1c5..0x66ef1ea
```
[V] 0x66ee350..0x66ef1ea.

### Phase 30: 0x66ef1f0..0x66ef25a — cleanup loop over [rbp+0xdc0]..[rbp+0xdc8] step 0x28 [V]
```
r15 = [rbp+0xdc0];                    // loop begin [V] 0x66ef1f0
if (r15 == 0) goto 0x66ec630;         // empty: jump to pass-2 continuation [V] 0x66ef1f7
r12 = [rbp+0xdc8];                    // loop end [V] 0x66ef200
loop_top:
if (r15 == r12) goto 0x66ec630;       // done: jump to pass-2 continuation [V] 0x66ef214..0x66ef217
if ((u8)[r15+0x18] != 2) goto skip;   // only process type-2 entries [V] 0x66ef21d..0x66ef222
rbx = [r15+8];                        // shared_ptr [V] 0x66ef224
if (rbx == 0) goto skip;              // [V] 0x66ef228
// shared_ptr release sequence [V] 0x66ef22d..0x66ef252
skip:
r15 += 0x28;                          // advance to next entry [V] 0x66ef210
goto loop_top;                        // [V] 0x66ef258
```
[V] 0x66ef1f0..0x66ef258. The jump target 0x66ec630 is in the earlier-decoded part of body A (pass-2 loop continuation) [I].

### Phase 31: 0x66ef25a..0x66ef28d — cleanup loop setup over [rbp+0x1670]..[rbp+0x1678] step 0x18 [V]
```
rsi = [rbp+0x1670];                   // loop begin [V] 0x66ef25a
if (rsi == 0) goto 0x66f6e3b;         // empty: jump to body A epilogue [V] 0x66ef264
rbx = [rbp+0x1678];                   // loop end [V] 0x66ef26a
if (rsi != rbx) goto 0x66ef28d;       // work remains: jump to body A end boundary [V] 0x66ef271..0x66ef274
goto 0x66f6e04;                       // no work: jump to epilogue [V] 0x66ef276
```
[V] 0x66ef25a..0x66ef276. The loop body at 0x66ef28d is beyond this unit's range [I]. Body A ends at 0x66ef28d [V].