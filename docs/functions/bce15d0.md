# Dossier: sub_bce15d0 (0xbce15d0, size 0x91, 1.26.62.01)

Source: `src/client/features/render/native/helpers/sub_bce15d0.cpp` + `.h` (first line
`// LIFT 0xbce15d0 size 0x91 1.26.62.01 sub_bce15d0`), registered with
`LIFT_FN(bce15d0, "sub_bce15d0", 0xbce15d0, sub_bce15d0, nullptr)`.
Disassembly basis: `rdis dis 0xbce15d0` (39 instructions, [0xbce15d0, 0xbce1661)),
`rdis fn 0xbce15d0`, `rdis fn 0xb432e0`, `rdis sec` (.rdata at RVA 0xeec8000 holds the jump
table at image RVA 0xF44C2F0).

## Signature guess

`int sub_bce15d0(void* rcx /*unused*/, void* rdx=a1, void* r8=a2, void* r9=a3)` — x64
Microsoft ABI; return in EAX. RCX arrives but is never read before being overwritten, so
argument 1 is unused by this function. R9 (argument 4) is only observed on the crash path,
where it is forwarded to sub_b432e0 which reads none of its arguments.

## Register / argument map

- RCX = a0: unused (overwritten at 0xbce15e5 before any read).
- RDX = a1: pointer to object 1; [a1+0x0] = P1 pointer.
- R8 = a2: pointer to object 2; [a2+0x0] = P2 pointer.
- R9 = a3: incoming 4th argument, forwarded to sub_b432e0 on the crash path.
- RAX = scratch: P1, then Q1 = [P1+0x18], then word [Q1+0].
- RCX = scratch: P2, then Q2 = [P2+0x18], then word [Q2+0] (at 0xbce161b).
- RDX/R8 = index computation and jump-table scratch.
- R8 = jump-table base (0xbce160b `lea r8,[0xF44C2F0]` → imageBase + 0xF44C2F0).
- EAX = result: `(w1 & 0xFF00) | resultByte`.

## Reversed source (complete)

All addresses verified [V] against `rdis dis 0xbce15d0`. Every instruction of
[0xbce15d0, 0xbce1661) is inside a cited range below.

### 0xbce15d0..0xbce15da — prologue and first null guard

```
0xbce15d0  sub rsp,0x28                                  
0xbce15d4  mov rax,[rdx]                                 ; R a1+0x0
0xbce15d7  test rax,rax                                  
0xbce15da  je short 0xBCE1640                            ; -> loc_bce1640
```
C-like: `void* const p1 = *(void**)a1; if (p1 == nullptr) return 0;` — 0xbce15d4 reads
P1 at [a1+0x0] [V]; 0xbce15d7-0xbce15da null-guard P1 [V]; on null: `xor eax,eax` at
0xbce1640, return 0 [V].

### 0xbce15dc..0xbce15e3 — Q1 pointer and second null guard

```
0xbce15dc  mov rax,[rax+0x18]                            ; R *(a1+0x0)+0x18
0xbce15e0  test rax,rax                                  
0xbce15e3  je short 0xBCE1640                            ; -> loc_bce1640
```
C-like: `Q1 = *(void**)(P1 + 0x18); if (Q1 == nullptr) return 0;` [V]. rax still holds Q1
for the compare block at 0xbce161e.

### 0xbce15e5..0xbce15eb — second object null guard

```
0xbce15e5  mov rcx,[r8]                                  ; R a2+0x0
0xbce15e8  test rcx,rcx                                  
0xbce15eb  je short 0xBCE1640                            ; -> loc_bce1640
```
C-like: `void* const p2 = *(void**)a2; if (p2 == nullptr) return 0;` [V].

### 0xbce15ed..0xbce15f4 — Q2 pointer and third null guard

```
0xbce15ed  mov rcx,[rcx+0x18]                            ; R *(a2+0x0)+0x18
0xbce15f1  test rcx,rcx                                  
0xbce15f4  je short 0xBCE1640                            ; -> loc_bce1640
```
C-like: `Q2 = *(void**)(P2 + 0x18); if (Q2 == nullptr) return 0;` [V]. rcx still holds Q2
for 0xbce161b.

### 0xbce15f6..0xbce1619 — jump-table index and indirect jump

```
0xbce15f6  movsx rdx,byte ptr [rax+2]                    ; R *(*(a1+0x0)+0x18)+0x2
0xbce15fb  movsx r8,byte ptr [rcx+2]                     ; R *(*(a2+0x0)+0x18)+0x2
0xbce1600  lea rdx,[rdx+rdx*2]
0xbce1604  add rdx,r8
0xbce1607  add rdx,4
0xbce160b  lea r8,[0xF44C2F0]                            ; [data_f44c2f0]
0xbce1612  movsxd rdx,[r8+rdx*4]
0xbce1616  add rdx,r8
0xbce1619  jmp rdx
```
C-like: `idx = (int8_t)*(uint8_t*)(Q1 + 2) * 3 + (int8_t)*(uint8_t*)(Q2 + 2) + 4;`
[V: 0xbce15f6 sign-extended byte at Q1+2; 0xbce15fb sign-extended byte at Q2+2;
0xbce1600-0xbce1607 index arithmetic]; `off = *(int32_t*)(tableVA + idx*4);`
[V: 0xbce1612 movsxd sign-extended int32 load]; `jump to tableVA + off`
[V: 0xbce1616 add rdx,r8; 0xbce1619 jmp rdx]. tableVA = imageBase + 0xF44C2F0
[V: rdis resolves the RIP-relative lea to data label data_f44c2f0 at RVA 0xF44C2F0].

### 0xbce161b..0xbce163f — compare block (table target 0xbce161b)

```
0xbce161b  movzx ecx,word ptr [rcx]                      ; R *(*(a2+0x0)+0x18)+0x0
0xbce161e  movzx eax,word ptr [rax]                      ; R *(*(a1+0x0)+0x18)+0x0
0xbce1621  cmp ax,cx                                     
0xbce1624  sete dl                                       
0xbce1627  cmp ax,0xFFFF                                 
0xbce162b  setne r8b                                     
0xbce162f  cmp cx,0xFFFF                                 
0xbce1633  setne al                                      
0xbce1636  and al,r8b                                    
0xbce1639  and al,dl                                    
0xbce163b  add rsp,0x28                                  
0xbce163f  ret                                           
```
C-like: `w1 = *(uint16_t*)Q1; w2 = *(uint16_t*)Q2; result = (w1 == w2) && (w1 != 0xFFFF)
&& (w2 != 0xFFFF); return (w1 & 0xFF00) | (result ? 1 : 0);` — note `movzx eax,word
[rax]` at 0xbce161e leaves w1 in EAX; only AL is overwritten by the flag computations, so
the returned EAX keeps w1's high byte (bits 8-15) in the high byte [V].

### 0xbce1640..0xbce1646 — loc_bce1640 (all null guards jump here)

```
0xbce1640  xor eax,eax                                   
0xbce1642  add rsp,0x28                                  
0xbce1646  ret                                           
```
C-like: `return 0;` [V]. Jump targets: 0xbce15da, 0xbce15e3, 0xbce15eb, 0xbce15f4 [V].

### 0xbce1647..0xbce1660 — crash path (table targets 0xbce1647..0xbce165b)

```
0xbce1647  call 0xB432E0                                 ; -> sub_b432e0
0xbce164c  call 0xB432E0                                 ; -> sub_b432e0
0xbce1651  call 0xB432E0                                 ; -> sub_b432e0
0xbce1656  call 0xB432E0                                 ; -> sub_b432e0
0xbce165b  call 0xB432E0                                 ; -> sub_b432e0
0xbce1660  int3                                          
```
C-like: `sub_b432e0(q2, tableVA + off, tableVA, a3);` at each entry, falling through to the
next call (register state at fall-through entries is clobbered by the preceding call, but
sub_b432e0 never returns so the distinction is unobservable), then `int3` at 0xbce1660
[V]. sub_b432e0 body [V: rdis fn 0xb432e0]:
`0xb432e0  sub rsp,0x28; call 0x1166E0; 0xb432e9  int3` — reads none of its arguments,
never returns (sub_1166e0 at 0x1166e0 itself ends in int3 at 0x116718).

## Struct fields touched

| struct | offset | size | dir | meaning | tag |
|--------|--------|------|-----|---------|-----|
| Bce15d0_Object.p | 0x00 | 8 | R | pointer to P = [a1+0x0] / [a2+0x0] | [V] 0xbce15d4 / 0xbce15e5 |
| Bce15d0_P.q | 0x18 | 8 | R | pointer to Q = [P+0x18] | [V] 0xbce15dc / 0xbce15ed |
| Bce15d0_Q.id0x0 | 0x00 | 2 | R | uint16 compared | [V] 0xbce161e / 0xbce161b |
| Bce15d0_Q.type0x2 | 0x02 | 1 | R | int8 jump-table input | [V] 0xbce15f6 / 0xbce15fb |

No writes to game memory (only its own stack frame, which is never read back).

## Callees

- 0xb432e0 (sub_b432e0): boundary class crt (docs/data/native_boundary.tsv row 173)
  [V]. Called 0..5 times on the crash path via `native::Boundary<std::uintptr_t,...> sub_b432e0("sub_b432e0")`;
  reads none of its register arguments, never returns. Quoted verbatim in the source
  (#if 0 block, 0xbce1647..0xbce165b).
- 0 callees in the lift set.

## OPEN questions

None: every instruction, read, write (none), call and return of [0xbce15d0, 0xbce1661)
is accounted for from the disassembly; the jump table is modeled generically by entry
value (targetVA - tableVA), so no table entry contents are needed.
