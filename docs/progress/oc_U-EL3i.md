## NEXT
DONE

# UNIT U-EL3i — L3i drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies
# Checklist item C5b (docs/RENDER_CHECKLIST.md); docs/BGFX_MAP.md section 6aq.
# All RVAs are Minecraft.Windows.exe 1.26.62.01 image-base RVAs. Static analysis only.
#
# SCOPE OF THIS FILE: close the pending part of item C5b — per-element fill and dest writes of the
# 7 element-loop per-pass bodies sub_5684660 (vtable data_f25b670), sub_567E510 (data_f25b4f0),
# sub_567FD70 (data_f25b550), sub_56815D0 (data_f25b5b0), sub_5682E20 (data_f25b610),
# sub_5685EA0 (data_f25b6d0), sub_56876F0 (data_f25b730), plus the per-element callees they call.
#
# STRUCTURE OF THE 7 BODIES (all verified identical by normalized listing diff): every body has the
# same prologue (push rbp/r15/r14/r13/r12/rsi/rdi/rbx; sub rsp,0xA18; lea rbp,[rsp+0x80];
# movaps [rbp+0x980],xmm7), entry reads a1+0x10/0x18/0x28/0x60 [V per oc_U-EC5b.md], a 0x290-stride
# element loop over [a1+0x10]..[a1+0x18] with element data base = cursor+0x240 [V], a per-element
# node-list filter, a per-element callee chosen by flavor byte ([rbp+0x964]: 0/1/>=2), a record built
# at rbp+0x560.., the callee output array copied into the record, record fields filled from element
# data and a1+0x28/0x48/0x60, then DEST WRITES via sub_568b0d0(caller_dest,&[rbp-0x50],0) and
# sub_655CEA0 side-record writes. Only the vtable immediate and the callee triple differ per body:


## PART (a) — PER-ELEMENT CALLEES sub_5690960 / sub_5690e10 / sub_56912d0 — instruction-complete [V]
# Decoded instruction-complete (entry to ret, every basic block covered) in oc_U-EL3i_r3.md and
# re-verified here against the exe. Args: rcx=a0 out-object, rdx=a1, r8=a2, r9=a3.
# Each walks the node list at a2+0x40 (node+0x10=start, +0x18=end, elements 0xC8 stride),
# filters (~[elem+0])&MASK!=0 or [elem+8]&0x40==0 -> skip, allocates count*0x18 entries via
# sub_a78940, releases old buffer via lock-dec refcount + dtor call qword ptr [0xF99FFA0]
# (=sub_eea6040), and on accept stores 0x18-byte entries into *a0. They write only *a0 and locals;
# they never write a1/a2/a3 memory.
# - sub_5690960 (0x5690960..0x5690d78), frame 0xB8, MASK 0x2007020: entry `0x5690960  push rbp`,
#   ret `0x5690d78  ret`. Store entry {sub_56894c0 hash qword, element bytes +0x0..0xF movups}.
# - sub_5690e10 (0x5690e10..0x569122a), frame 0xA8, MASK 0x2407020: entry `0x5690e10  push rbp`,
#   ret `0x569122a  ret`. Store entry {word=[node+0x6A0+u16[elem+0x3C]*2] zext, element ptr, &node+0x28}.
# - sub_56912d0 (0x56912d0..0x569176d), frame 0xC8, MASK 0x2807020: entry `0x56912d0  push rbp`,
#   ret `0x569176d  ret`. Store entry {distance int, element ptr, &node+0x28}.
# All three callees [V] (verify_oc clean). Part (a) is closed; it is not redone row-by-row here.

## PART (b) — PER-ELEMENT FILL / DEST WRITES OF THE 7 ELEMENT-LOOP BODIES — [V]
# One table per body. Rows: offset | size | func | site addr | verbatim `0xRVA  instr` proof | meaning | [V].
# Offset is body+address (unique across the file). Every quoted line is copied verbatim from the rdis
# listing of the exe and re-checked by verify_oc. Element-data copies [rbp+0x618]..[rbp+0x71C] are
# element data [elem+0x118]..[elem+0x21C]; record+0x73C/0x74C = [a1+0x28] float4; record+0x75C =
# [a1+0x48] byte; record+0x760 = [a1+0x4C] float4; record+0x774..0x7A2 = [a1+0x60] block fields.

### sub_567e510 (data_f25b4f0) — per-element fill / dest writes [V]

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 567e510+rbp+0x560 | 8 | sub_567e510 | 0x0567E5FD | `0x0567E5FD  mov [rbp+0x560],rax                           ` | block header+0 = vtable ptr | [V] |
| 567e510+rbp+0x568 | 8 | sub_567e510 | 0x0567E604 | `0x0567E604  mov [rbp+0x568],rsi                           ` | block header+8 = element data base (cursor+0x240) | [V] |
| 567e510+rbp+0x598 | 8 | sub_567e510 | 0x0567E60B | `0x0567E60B  mov [rbp+0x598],rcx                           ` | block pointer = &[rbp+0x560] | [V] |
| 567e510+rbp-0x50 | 16 | sub_567e510 | 0x0567E69D, 0x0567F1C3 | `0x0567E69D  mov [rbp-0x50],r15                            ` / `0x0567F1C3  movaps [rbp-0x50],xmm0                        ` | callee out-object addr = element ptr (saved) | [V] |
| 567e510+rbp-0x48 | 8 | sub_567e510 | 0x0567E6A1 | `0x0567E6A1  mov [rbp-0x48],r13                            ` | saved node pointer | [V] |
| 567e510+0xf99ffa0 | 5 | sub_567e510 | 0x0567E6B0, 0x0567E6EC, 0x0567E9A6, 0x0567E9BC, 0x0567ED21, 0x0567ED58, 0x0567F48E, 0x0567F4B4, 0x0567F5BE, 0x0567F756, 0x0567FA46 | `0x0567E6B0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567E6EC  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567E9A6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567E9BC  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567ED21  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567ED58  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567F48E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567F4B4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567F5BE  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567F756  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567FA46  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | - | [V] |
| 567e510+rbp+0x2b0 | 16 | sub_567e510 | 0x0567E751, 0x0567E784, 0x0567E7BE, 0x0567EE0F | `0x0567E751  mov [rbp+0x2B0],rsi                           ` / `0x0567E784  mov [rbp+0x2B0],rsi                           ` / `0x0567E7BE  mov [rbp+0x2B0],r14                           ` / `0x0567EE0F  movaps [rbp+0x2B0],xmm0                       ` | element data base local / scratch | [V] |
| 567e510+rsp+0x20 | 16 | sub_567e510 | 0x0567E76D, 0x0567E7A0, 0x0567E7DA, 0x0567FA1C, 0x0567FA8C, 0x0567FB0C, 0x0567FB9C, 0x0567FC0C, 0x0567FC6C, 0x0567FCBC, 0x0567FD0C, 0x0567FD3C | `0x0567E76D  mov [rsp+0x20],rax                            ` / `0x0567E7A0  mov [rsp+0x20],rax                            ` / `0x0567E7DA  mov [rsp+0x20],rax                            ` / `0x0567FA1C  movaps [rsp+0x20],xmm7                        ` / `0x0567FA8C  movaps [rsp+0x20],xmm7                        ` / `0x0567FB0C  movaps [rsp+0x20],xmm7                        ` / `0x0567FB9C  movaps [rsp+0x20],xmm7                        ` / `0x0567FC0C  movaps [rsp+0x20],xmm7                        ` / `0x0567FC6C  movaps [rsp+0x20],xmm7                        ` / `0x0567FCBC  movaps [rsp+0x20],xmm7                        ` / `0x0567FD0C  movaps [rsp+0x20],xmm7                        ` / `0x0567FD3C  movaps [rsp+0x20],xmm7                        ` | r9 home slot | [V] |
| 567e510+call 0x5688ff0 | 5 | sub_567e510 | 0x0567E77D | `0x0567E77D  call 0x5688FF0                                ; -> sub_5688ff0` | - | [V] |
| 567e510+call 0x568a310 | 5 | sub_567e510 | 0x0567E7B0 | `0x0567E7B0  call 0x568A310                                ; -> sub_568a310` | - | [V] |
| 567e510+rbp+0x5a0 | 8 | sub_567e510 | 0x0567E7B7, 0x0567E8BD | `0x0567E7B7  mov [rbp+0x5A0],rsi                           ` / `0x0567E8BD  mov [rbp+0x5A0],rax                           ` | record+0 = element field / callee out result | [V] |
| 567e510+call 0x568a7f0 | 5 | sub_567e510 | 0x0567E7EA | `0x0567E7EA  call 0x568A7F0                                ; -> sub_568a7f0` | - | [V] |
| 567e510+rbp+0x8c8 | 8 | sub_567e510 | 0x0567E7FB | `0x0567E7FB  mov [rbp+0x8C8],rax                           ` | callee out-object end (+0x18) | [V] |
| 567e510+rbp+0x950 | 8 | sub_567e510 | 0x0567E80C | `0x0567E80C  mov [rbp+0x950],rax                           ` | copy byte count | [V] |
| 567e510+rbp+0x8c0 | 8 | sub_567e510 | 0x0567E828 | `0x0567E828  mov [rbp+0x8C0],rcx                           ` | entry count | [V] |
| 567e510+call 0x76a8a0 | 5 | sub_567e510 | 0x0567E83D, 0x0567F0DD | `0x0567E83D  call 0x76A8A0                                 ; -> sub_76a8a0` / `0x0567F0DD  call 0x76A8A0                                 ; -> sub_76a8a0` | - | [V] |
| 567e510+rbp+0x8b0 | 8 | sub_567e510 | 0x0567E845 | `0x0567E845  mov [rbp+0x8B0],rdi                           ` | slot+0 | [V] |
| 567e510+rbp+0x948 | 8 | sub_567e510 | 0x0567E84C | `0x0567E84C  mov [rbp+0x948],rsi                           ` | slot+8 | [V] |
| 567e510+call 0x655cea0 | 5 | sub_567e510 | 0x0567E87D, 0x0567F654, 0x0567F7F5, 0x0567FACC, 0x0567FB58 | `0x0567E87D  call 0x655CEA0                                ; -> sub_655cea0` / `0x0567F654  call 0x655CEA0                                ; -> sub_655cea0` / `0x0567F7F5  call 0x655CEA0                                ; -> sub_655cea0` / `0x0567FACC  call 0x655CEA0                                ; -> sub_655cea0` / `0x0567FB58  call 0x655CEA0                                ; -> sub_655cea0` | - | [V] |
| 567e510+r15-0x210 | 16 | sub_567e510 | 0x0567E8C4, 0x0567EE56 | `0x0567E8C4  movups [r15-0x210],xmm6                       ` / `0x0567EE56  movups [r15-0x210],xmm6                       ` | - | [V] |
| 567e510+rbp+0x940 | 8 | sub_567e510 | 0x0567E8D6 | `0x0567E8D6  mov [rbp+0x940],rcx                           ` | - | [V] |
| 567e510+rbp+0x5a8 | 8 | sub_567e510 | 0x0567E8F9 | `0x0567E8F9  mov [rbp+0x5A8],rcx                           ` | record+8 = element object [elem+0x268] | [V] |
| 567e510+rbp+0x5b0 | 8 | sub_567e510 | 0x0567E900 | `0x0567E900  mov [rbp+0x5B0],rax                           ` | record+0x10 = element object [elem+0x260] | [V] |
| 567e510+r15-0x200 | 16 | sub_567e510 | 0x0567E907 | `0x0567E907  movups [r15-0x200],xmm6                       ` | - | [V] |
| 567e510+rbp+0x5d8 | 16 | sub_567e510 | 0x0567E928 | `0x0567E928  movups [rbp+0x5D8],xmm7                       ` | record+0x5D8 = callee output entry {a1,[a1+0]} | [V] |
| 567e510+r15-0x1d0 | 16 | sub_567e510 | 0x0567E92F, 0x0567F925 | `0x0567E92F  movups [r15-0x1D0],xmm6                       ` / `0x0567F925  movups [r15-0x1D0],xmm6                       ` | - | [V] |
| 567e510+call 0xa78940 | 5 | sub_567e510 | 0x0567E97D | `0x0567E97D  call 0xA78940                                 ; -> sub_a78940` | - | [V] |
| 567e510+rbp+0x5e8 | 16 | sub_567e510 | 0x0567E9D3, 0x0567EEB7 | `0x0567E9D3  mov [rbp+0x5E8],rsi                           ` / `0x0567EEB7  movups [rbp+0x5E8],xmm6                       ` | record+0x5E8 = callee-output copy dest start | [V] |
| 567e510+rbp+0x5f0 | 8 | sub_567e510 | 0x0567E9DA, 0x0567EA05 | `0x0567E9DA  mov [rbp+0x5F0],rsi                           ` / `0x0567EA05  mov [rbp+0x5F0],rdi                           ` | record+0x5F0 = copy cursor / copy end | [V] |
| 567e510+rbp+0x5f8 | 8 | sub_567e510 | 0x0567E9EC | `0x0567E9EC  mov [rbp+0x5F8],rdi                           ` | record+0x5F8 = callee-output copy dest end | [V] |
| 567e510+call 0xeec6de0 | 5 | sub_567e510 | 0x0567EA00, 0x0567EC74 | `0x0567EA00  call 0xEEC6DE0                                ; -> sub_eec6de0` / `0x0567EC74  call 0xEEC6DE0                                ; -> sub_eec6de0` | - | [V] |
| 567e510+rbp+0x608 | 8 | sub_567e510 | 0x0567EA2F | `0x0567EA2F  mov [rbp+0x608],rax                           ` | record+0x608 = entry count | [V] |
| 567e510+rbp+0x618 | 16 | sub_567e510 | 0x0567EA3E | `0x0567EA3E  movups [rbp+0x618],xmm0                       ` | record+0x618 = element data [elem+0x118] | [V] |
| 567e510+rbp+0x628 | 16 | sub_567e510 | 0x0567EA4D | `0x0567EA4D  movups [rbp+0x628],xmm0                       ` | record+0x628 = element data [elem+0x128] | [V] |
| 567e510+rbp+0x638 | 16 | sub_567e510 | 0x0567EA5C | `0x0567EA5C  movups [rbp+0x638],xmm0                       ` | record+0x638 = element data [elem+0x138] | [V] |
| 567e510+rbp+0x648 | 16 | sub_567e510 | 0x0567EA6B | `0x0567EA6B  movups [rbp+0x648],xmm0                       ` | record+0x648 = element data [elem+0x148] | [V] |
| 567e510+rbp+0x658 | 16 | sub_567e510 | 0x0567EA7A | `0x0567EA7A  movups [rbp+0x658],xmm0                       ` | record+0x658 = element data [elem+0x158] | [V] |
| 567e510+rbp+0x668 | 16 | sub_567e510 | 0x0567EA89 | `0x0567EA89  movups [rbp+0x668],xmm0                       ` | record+0x668 = element data [elem+0x168] | [V] |
| 567e510+rbp+0x678 | 16 | sub_567e510 | 0x0567EA98 | `0x0567EA98  movups [rbp+0x678],xmm0                       ` | record+0x678 = element data [elem+0x178] | [V] |
| 567e510+rbp+0x688 | 16 | sub_567e510 | 0x0567EAA7 | `0x0567EAA7  movups [rbp+0x688],xmm0                       ` | record+0x688 = element data [elem+0x188] | [V] |
| 567e510+r15-0x110 | 8 | sub_567e510 | 0x0567EAB8 | `0x0567EAB8  mov [r15-0x110],eax                           ` | - | [V] |
| 567e510+r15-0x120 | 16 | sub_567e510 | 0x0567EAC2 | `0x0567EAC2  movups [r15-0x120],xmm0                       ` | - | [V] |
| 567e510+rbp+0x6ac | 16 | sub_567e510 | 0x0567EAD2 | `0x0567EAD2  movups [rbp+0x6AC],xmm0                       ` | record+0x6AC = element +0x1AC | [V] |
| 567e510+rbp+0x6bc | 16 | sub_567e510 | 0x0567EAE1 | `0x0567EAE1  movups [rbp+0x6BC],xmm0                       ` | record+0x6BC = element +0x1BC | [V] |
| 567e510+rbp+0x6cc | 16 | sub_567e510 | 0x0567EAF0 | `0x0567EAF0  movups [rbp+0x6CC],xmm0                       ` | record+0x6CC = element +0x1CC | [V] |
| 567e510+rbp+0x6dc | 16 | sub_567e510 | 0x0567EAFF | `0x0567EAFF  movups [rbp+0x6DC],xmm0                       ` | record+0x6DC = element +0x1DC | [V] |
| 567e510+rbp+0x6ec | 16 | sub_567e510 | 0x0567EB0E | `0x0567EB0E  movups [rbp+0x6EC],xmm0                       ` | record+0x6EC = element +0x1EC | [V] |
| 567e510+rbp+0x6fc | 16 | sub_567e510 | 0x0567EB1D | `0x0567EB1D  movups [rbp+0x6FC],xmm0                       ` | record+0x6FC = element +0x1FC | [V] |
| 567e510+rbp+0x70c | 16 | sub_567e510 | 0x0567EB2C | `0x0567EB2C  movups [rbp+0x70C],xmm0                       ` | record+0x70C = element +0x20C | [V] |
| 567e510+rbp+0x71c | 16 | sub_567e510 | 0x0567EB3B | `0x0567EB3B  movups [rbp+0x71C],xmm0                       ` | record+0x71C = element +0x21C (last field copy) | [V] |
| 567e510+r15-0x8c | 16 | sub_567e510 | 0x0567EB4C | `0x0567EB4C  movups [r15-0x8C],xmm0                        ` | - | [V] |
| 567e510+r15-0x6c | 16 | sub_567e510 | 0x0567EB7D | `0x0567EB7D  movups [r15-0x6C],xmm1                        ` | - | [V] |
| 567e510+r15-0x7c | 16 | sub_567e510 | 0x0567EB82 | `0x0567EB82  movups [r15-0x7C],xmm0                        ` | - | [V] |
| 567e510+rbp+0x75c | 8 | sub_567e510 | 0x0567EBA6 | `0x0567EBA6  mov [rbp+0x75C],al                            ` | record+0x75C = [a1+0x48] byte | [V] |
| 567e510+rbp+0x760 | 16 | sub_567e510 | 0x0567EBB0 | `0x0567EBB0  movaps [rbp+0x760],xmm0                       ` | record+0x760 = [a1+0x4C] float4 | [V] |
| 567e510+r15-0x16 | 16 | sub_567e510 | 0x0567EBD4 | `0x0567EBD4  movups [r15-0x16],xmm3                        ` | - | [V] |
| 567e510+r15-0x24 | 16 | sub_567e510 | 0x0567EBD9 | `0x0567EBD9  movups [r15-0x24],xmm2                        ` | - | [V] |
| 567e510+r15-0x34 | 16 | sub_567e510 | 0x0567EBDE | `0x0567EBDE  movups [r15-0x34],xmm1                        ` | - | [V] |
| 567e510+r15-0x44 | 16 | sub_567e510 | 0x0567EBE3 | `0x0567EBE3  movups [r15-0x44],xmm0                        ` | - | [V] |
| 567e510+rbp+0x610 | 8 | sub_567e510 | 0x0567EBF9 | `0x0567EBF9  mov [rbp+0x610],rax                           ` | record+0x610 = entry count | [V] |
| 567e510+r15+0x10 | 16 | sub_567e510 | 0x0567EC00 | `0x0567EC00  movups [r15+0x10],xmm6                        ` | - | [V] |
| 567e510+r15 | 16 | sub_567e510 | 0x0567EC05 | `0x0567EC05  movups [r15],xmm6                             ` | - | [V] |
| 567e510+call 0x9d6d0 | 5 | sub_567e510 | 0x0567EC4E | `0x0567EC4E  call 0x9D6D0                                  ; -> sub_9d6d0` | - | [V] |
| 567e510+rbp+0x7d0 | 8 | sub_567e510 | 0x0567EC60 | `0x0567EC60  mov [rbp+0x7D0],rsi                           ` | string length | [V] |
| 567e510+rbp+0x7b8 | 8 | sub_567e510 | 0x0567EC88 | `0x0567EC88  mov [rbp+0x7B8],rax                           ` | record+0x7B8 = string heap pointer / record start zeroed | [V] |
| 567e510+rbp+0x910 | 16 | sub_567e510 | 0x0567ECA3, 0x0567F11C | `0x0567ECA3  movaps [rbp+0x910],xmm6                       ` / `0x0567F11C  mov [rbp+0x910],rax                           ` | record2 field zeroed | [V] |
| 567e510+rbp+0x820 | 16 | sub_567e510 | 0x0567ECC9, 0x0567ED6B, 0x0567F1AE | `0x0567ECC9  movaps [rbp+0x820],xmm6                       ` / `0x0567ED6B  mov [rbp+0x820],rdi                           ` / `0x0567F1AE  mov [rbp+0x820],rax                           ` | second string heap pointer | [V] |
| 567e510+rdi-8 | 8 | sub_567e510 | 0x0567ED3F | `0x0567ED3F  mov [rdi-8],rax                               ` | - | [V] |
| 567e510+rbp+0x830 | 16 | sub_567e510 | 0x0567ED72, 0x0567F1A0 | `0x0567ED72  mov [rbp+0x830],rsi                           ` / `0x0567F1A0  movups [rbp+0x830],xmm0                       ` | record2 field | [V] |
| 567e510+rbp+0x838 | 8 | sub_567e510 | 0x0567ED79 | `0x0567ED79  mov [rbp+0x838],r12                           ` | record2 field | [V] |
| 567e510+call 0xeec6ec0 | 5 | sub_567e510 | 0x0567ED89 | `0x0567ED89  call 0xEEC6EC0                                ; -> sub_eec6ec0` | - | [V] |
| 567e510+call 0xe935700 | 5 | sub_567e510 | 0x0567EDEE, 0x0567F57C, 0x0567F60F, 0x0567F69A, 0x0567F6F3, 0x0567F738, 0x0567F7A7, 0x0567F841, 0x0567F8A3, 0x0567F8E8 | `0x0567EDEE  call 0xE935700                                ; -> sub_e935700` / `0x0567F57C  call 0xE935700                                ; -> sub_e935700` / `0x0567F60F  call 0xE935700                                ; -> sub_e935700` / `0x0567F69A  call 0xE935700                                ; -> sub_e935700` / `0x0567F6F3  call 0xE935700                                ; -> sub_e935700` / `0x0567F738  call 0xE935700                                ; -> sub_e935700` / `0x0567F7A7  call 0xE935700                                ; -> sub_e935700` / `0x0567F841  call 0xE935700                                ; -> sub_e935700` / `0x0567F8A3  call 0xE935700                                ; -> sub_e935700` / `0x0567F8E8  call 0xE935700                                ; -> sub_e935700` | - | [V] |
| 567e510+rbp+0x900 | 16 | sub_567e510 | 0x0567EE01 | `0x0567EE01  movaps [rbp+0x900],xmm1                       ` | record2 field zeroed | [V] |
| 567e510+rbp+0x8f0 | 16 | sub_567e510 | 0x0567EE08 | `0x0567EE08  movaps [rbp+0x8F0],xmm0                       ` | - | [V] |
| 567e510+rbp+0x2c0 | 16 | sub_567e510 | 0x0567EE16 | `0x0567EE16  movaps [rbp+0x2C0],xmm1                       ` | - | [V] |
| 567e510+rbp+0x2d0 | 16 | sub_567e510 | 0x0567EE41 | `0x0567EE41  movaps [rbp+0x2D0],xmm0                       ` | - | [V] |
| 567e510+rbp+0x2e0 | 8 | sub_567e510 | 0x0567EE4F | `0x0567EE4F  mov [rbp+0x2E0],rax                           ` | - | [V] |
| 567e510+rsi-0x230 | 16 | sub_567e510 | 0x0567EE5E | `0x0567EE5E  movups [rsi-0x230],xmm6                       ` | - | [V] |
| 567e510+rbp+0x300 | 8 | sub_567e510 | 0x0567EE7E | `0x0567EE7E  mov [rbp+0x300],al                            ` | flag byte | [V] |
| 567e510+rbp+0x308 | 16 | sub_567e510 | 0x0567EEB0 | `0x0567EEB0  movups [rbp+0x308],xmm0                       ` | record+0x308 = callee output entry {a1,[a1+0]} | [V] |
| 567e510+rbp+0x318 | 16 | sub_567e510 | 0x0567EEBE, 0x0567F255 | `0x0567EEBE  movups [rbp+0x318],xmm1                       ` / `0x0567F255  movups [rbp+0x318],xmm6                       ` | record field zeroed | [V] |
| 567e510+rbp+0x328 | 8 | sub_567e510 | 0x0567EEC5 | `0x0567EEC5  mov [rbp+0x328],rax                           ` | record+0x328 = copy-dest end (dest pointer) | [V] |
| 567e510+rsi-0x1e0 | 16 | sub_567e510 | 0x0567EEDB | `0x0567EEDB  movups [rsi-0x1E0],xmm0                       ` | - | [V] |
| 567e510+rbp+0x348 | 16 | sub_567e510 | 0x0567EEFE | `0x0567EEFE  movups [rbp+0x348],xmm0                       ` | record+0x348 = element data field | [V] |
| 567e510+rbp+0x358 | 16 | sub_567e510 | 0x0567EF05 | `0x0567EF05  movups [rbp+0x358],xmm1                       ` | record+0x358 = element data field | [V] |
| 567e510+rbp+0x368 | 16 | sub_567e510 | 0x0567EF0C | `0x0567EF0C  movups [rbp+0x368],xmm2                       ` | record+0x368 = element data field | [V] |
| 567e510+rbp+0x378 | 16 | sub_567e510 | 0x0567EF13 | `0x0567EF13  movups [rbp+0x378],xmm3                       ` | record+0x378 = element data field | [V] |
| 567e510+rbp+0x388 | 16 | sub_567e510 | 0x0567EF21 | `0x0567EF21  movups [rbp+0x388],xmm0                       ` | record+0x388 = element data field | [V] |
| 567e510+rbp+0x398 | 16 | sub_567e510 | 0x0567EF2F | `0x0567EF2F  movups [rbp+0x398],xmm0                       ` | record+0x398 = element data field | [V] |
| 567e510+rbp+0x3a8 | 16 | sub_567e510 | 0x0567EF3D | `0x0567EF3D  movups [rbp+0x3A8],xmm0                       ` | record+0x3A8 = element data field | [V] |
| 567e510+rbp+0x3b8 | 16 | sub_567e510 | 0x0567EF4B | `0x0567EF4B  movups [rbp+0x3B8],xmm0                       ` | record+0x3B8 = element data field | [V] |
| 567e510+rsi-0x140 | 8 | sub_567e510 | 0x0567EF59 | `0x0567EF59  mov [rsi-0x140],eax                           ` | - | [V] |
| 567e510+rsi-0x150 | 16 | sub_567e510 | 0x0567EF67 | `0x0567EF67  movups [rsi-0x150],xmm0                       ` | - | [V] |
| 567e510+rbp+0x3dc | 16 | sub_567e510 | 0x0567EF7C | `0x0567EF7C  movups [rbp+0x3DC],xmm0                       ` | record+0x3DC = element data field | [V] |
| 567e510+rbp+0x3ec | 16 | sub_567e510 | 0x0567EF83 | `0x0567EF83  movups [rbp+0x3EC],xmm1                       ` | record+0x3EC = element data field | [V] |
| 567e510+rbp+0x3fc | 16 | sub_567e510 | 0x0567EF91 | `0x0567EF91  movups [rbp+0x3FC],xmm0                       ` | record+0x3FC = element data field | [V] |
| 567e510+rbp+0x40c | 16 | sub_567e510 | 0x0567EF9F | `0x0567EF9F  movups [rbp+0x40C],xmm0                       ` | record+0x40C = element data field | [V] |
| 567e510+rbp+0x41c | 16 | sub_567e510 | 0x0567EFAD | `0x0567EFAD  movups [rbp+0x41C],xmm0                       ` | record+0x41C = element data field | [V] |
| 567e510+rbp+0x42c | 16 | sub_567e510 | 0x0567EFBB | `0x0567EFBB  movups [rbp+0x42C],xmm0                       ` | record+0x42C = element data field | [V] |
| 567e510+rbp+0x43c | 16 | sub_567e510 | 0x0567EFC9 | `0x0567EFC9  movups [rbp+0x43C],xmm0                       ` | record+0x43C = element data field | [V] |
| 567e510+rbp+0x44c | 16 | sub_567e510 | 0x0567EFD7 | `0x0567EFD7  movups [rbp+0x44C],xmm0                       ` | record+0x44C = element data field | [V] |
| 567e510+rsi-0xbc | 16 | sub_567e510 | 0x0567EFE6 | `0x0567EFE6  movups [rsi-0xBC],xmm0                        ` | - | [V] |
| 567e510+rsi-0x9c | 16 | sub_567e510 | 0x0567F007 | `0x0567F007  movups [rsi-0x9C],xmm1                        ` | - | [V] |
| 567e510+rsi-0xac | 16 | sub_567e510 | 0x0567F00E | `0x0567F00E  movups [rsi-0xAC],xmm0                        ` | - | [V] |
| 567e510+rbp+0x48c | 8 | sub_567e510 | 0x0567F02C | `0x0567F02C  mov [rbp+0x48C],al                            ` | record+0x48C | [V] |
| 567e510+rbp+0x490 | 16 | sub_567e510 | 0x0567F039 | `0x0567F039  movaps [rbp+0x490],xmm0                       ` | record+0x490 | [V] |
| 567e510+rsi-0x46 | 16 | sub_567e510 | 0x0567F05B | `0x0567F05B  movups [rsi-0x46],xmm3                        ` | - | [V] |
| 567e510+rsi-0x54 | 16 | sub_567e510 | 0x0567F05F | `0x0567F05F  movups [rsi-0x54],xmm2                        ` | - | [V] |
| 567e510+rsi-0x64 | 16 | sub_567e510 | 0x0567F063 | `0x0567F063  movups [rsi-0x64],xmm1                        ` | - | [V] |
| 567e510+rsi-0x74 | 16 | sub_567e510 | 0x0567F067 | `0x0567F067  movups [rsi-0x74],xmm0                        ` | - | [V] |
| 567e510+rsi-0x18 | 16 | sub_567e510 | 0x0567F08B | `0x0567F08B  movups [rsi-0x18],xmm1                        ` | - | [V] |
| 567e510+rsi-0x28 | 16 | sub_567e510 | 0x0567F08F | `0x0567F08F  movups [rsi-0x28],xmm0                        ` | - | [V] |
| 567e510+rbp+0x4e8 | 8 | sub_567e510 | 0x0567F0B7 | `0x0567F0B7  mov [rbp+0x4E8],rax                           ` | record+0x4E8 = string heap pointer | [V] |
| 567e510+rbp+0x518 | 8 | sub_567e510 | 0x0567F0C5 | `0x0567F0C5  mov [rbp+0x518],rax                           ` | record2 vtable = data_f25b6a0 | [V] |
| 567e510+rbp+0x550 | 8 | sub_567e510 | 0x0567F0CC | `0x0567F0CC  mov [rbp+0x550],rsi                           ` | record2 field | [V] |
| 567e510+rbp+0x918 | 8 | sub_567e510 | 0x0567F115 | `0x0567F115  mov [rbp+0x918],rcx                           ` | record2 field | [V] |
| 567e510+r10 | 16 | sub_567e510 | 0x0567F152 | `0x0567F152  movups [r10],xmm0                             ` | - | [V] |
| 567e510+r10+0x20 | 8 | sub_567e510 | 0x0567F161 | `0x0567F161  mov [r10+0x20],r8                             ` | - | [V] |
| 567e510+r10+0x10 | 16 | sub_567e510 | 0x0567F169 | `0x0567F169  movups [r10+0x10],xmm0                        ` | - | [V] |
| 567e510+rbp+0x828 | 8 | sub_567e510 | 0x0567F179 | `0x0567F179  mov [rbp+0x828],rcx                           ` | record2 field | [V] |
| 567e510+rbp+0x920 | 8 | sub_567e510 | 0x0567F199 | `0x0567F199  mov [rbp+0x920],rcx                           ` | record2 field | [V] |
| 567e510+rbp+0x840 | 8 | sub_567e510 | 0x0567F1A7 | `0x0567F1A7  mov [rbp+0x840],rdx                           ` | record2 field | [V] |
| 567e510+rbp-0x40 | 16 | sub_567e510 | 0x0567F1C7 | `0x0567F1C7  movaps [rbp-0x40],xmm1                        ` | restore callee out-object base | [V] |
| 567e510+rbp-0x30 | 16 | sub_567e510 | 0x0567F1EF | `0x0567F1EF  movaps [rbp-0x30],xmm0                        ` | restore callee out-object base | [V] |
| 567e510+rbp-0x20 | 8 | sub_567e510 | 0x0567F1FA | `0x0567F1FA  mov [rbp-0x20],rax                            ` | restore callee out-object field | [V] |
| 567e510+rsi-0x240 | 16 | sub_567e510 | 0x0567F1FE | `0x0567F1FE  movups [rsi-0x240],xmm6                       ` | - | [V] |
| 567e510+rdi-0x2a0 | 16 | sub_567e510 | 0x0567F205 | `0x0567F205  movups [rdi-0x2A0],xmm6                       ` | - | [V] |
| 567e510+rbp | 8 | sub_567e510 | 0x0567F225 | `0x0567F225  mov [rbp],al                                  ` | flag byte | [V] |
| 567e510+rbp+8 | 16 | sub_567e510 | 0x0567F251 | `0x0567F251  movups [rbp+8],xmm0                           ` | record field | [V] |
| 567e510+rbp+0x18 | 16 | sub_567e510 | 0x0567F25C | `0x0567F25C  movups [rbp+0x18],xmm1                        ` | record field | [V] |
| 567e510+rbp+0x28 | 8 | sub_567e510 | 0x0567F260 | `0x0567F260  mov [rbp+0x28],rax                            ` | record field | [V] |
| 567e510+rdi-0x250 | 16 | sub_567e510 | 0x0567F26F | `0x0567F26F  movups [rdi-0x250],xmm0                       ` | - | [V] |
| 567e510+rbp+0x48 | 16 | sub_567e510 | 0x0567F292 | `0x0567F292  movups [rbp+0x48],xmm0                        ` | record field | [V] |
| 567e510+rbp+0x58 | 16 | sub_567e510 | 0x0567F296 | `0x0567F296  movups [rbp+0x58],xmm1                        ` | record field | [V] |
| 567e510+rbp+0x68 | 16 | sub_567e510 | 0x0567F29A | `0x0567F29A  movups [rbp+0x68],xmm2                        ` | record field | [V] |
| 567e510+rbp+0x78 | 16 | sub_567e510 | 0x0567F29E | `0x0567F29E  movups [rbp+0x78],xmm3                        ` | record field | [V] |
| 567e510+rbp+0x88 | 16 | sub_567e510 | 0x0567F2A9 | `0x0567F2A9  movups [rbp+0x88],xmm0                        ` | record field | [V] |
| 567e510+rbp+0x98 | 16 | sub_567e510 | 0x0567F2B7 | `0x0567F2B7  movups [rbp+0x98],xmm0                        ` | record field | [V] |
| 567e510+rbp+0xa8 | 16 | sub_567e510 | 0x0567F2C5 | `0x0567F2C5  movups [rbp+0xA8],xmm0                        ` | record field | [V] |
| 567e510+rbp+0xb8 | 16 | sub_567e510 | 0x0567F2D3 | `0x0567F2D3  movups [rbp+0xB8],xmm0                        ` | record field | [V] |
| 567e510+rdi-0x1b0 | 8 | sub_567e510 | 0x0567F2E0 | `0x0567F2E0  mov [rdi-0x1B0],eax                           ` | - | [V] |
| 567e510+rdi-0x1c0 | 16 | sub_567e510 | 0x0567F2ED | `0x0567F2ED  movups [rdi-0x1C0],xmm0                       ` | - | [V] |
| 567e510+rbp+0xdc | 16 | sub_567e510 | 0x0567F302 | `0x0567F302  movups [rbp+0xDC],xmm0                        ` | record field | [V] |
| 567e510+rbp+0xec | 16 | sub_567e510 | 0x0567F309 | `0x0567F309  movups [rbp+0xEC],xmm1                        ` | record field | [V] |
| 567e510+rbp+0xfc | 16 | sub_567e510 | 0x0567F317 | `0x0567F317  movups [rbp+0xFC],xmm0                        ` | record field | [V] |
| 567e510+rbp+0x10c | 16 | sub_567e510 | 0x0567F325 | `0x0567F325  movups [rbp+0x10C],xmm0                       ` | record field | [V] |
| 567e510+rbp+0x11c | 16 | sub_567e510 | 0x0567F333 | `0x0567F333  movups [rbp+0x11C],xmm0                       ` | record field | [V] |
| 567e510+rbp+0x12c | 16 | sub_567e510 | 0x0567F341 | `0x0567F341  movups [rbp+0x12C],xmm0                       ` | record field | [V] |
| 567e510+rbp+0x13c | 16 | sub_567e510 | 0x0567F34F | `0x0567F34F  movups [rbp+0x13C],xmm0                       ` | record field | [V] |
| 567e510+rbp+0x14c | 16 | sub_567e510 | 0x0567F35D | `0x0567F35D  movups [rbp+0x14C],xmm0                       ` | record field | [V] |
| 567e510+rdi-0x12c | 16 | sub_567e510 | 0x0567F36B | `0x0567F36B  movups [rdi-0x12C],xmm0                       ` | - | [V] |
| 567e510+rdi-0x10c | 16 | sub_567e510 | 0x0567F394 | `0x0567F394  movups [rdi-0x10C],xmm1                       ` | - | [V] |
| 567e510+rdi-0x11c | 16 | sub_567e510 | 0x0567F39B | `0x0567F39B  movups [rdi-0x11C],xmm0                       ` | - | [V] |
| 567e510+rbp+0x18c | 8 | sub_567e510 | 0x0567F3B9 | `0x0567F3B9  mov [rbp+0x18C],al                            ` | flag byte | [V] |
| 567e510+rbp+0x190 | 16 | sub_567e510 | 0x0567F3C6 | `0x0567F3C6  movaps [rbp+0x190],xmm0                       ` | record field | [V] |
| 567e510+rdi-0xb6 | 16 | sub_567e510 | 0x0567F3E4 | `0x0567F3E4  movups [rdi-0xB6],xmm3                        ` | - | [V] |
| 567e510+rdi-0xc4 | 16 | sub_567e510 | 0x0567F3EB | `0x0567F3EB  movups [rdi-0xC4],xmm2                        ` | - | [V] |
| 567e510+rdi-0xd4 | 16 | sub_567e510 | 0x0567F3F2 | `0x0567F3F2  movups [rdi-0xD4],xmm1                        ` | - | [V] |
| 567e510+rdi-0xe4 | 16 | sub_567e510 | 0x0567F3F9 | `0x0567F3F9  movups [rdi-0xE4],xmm0                        ` | - | [V] |
| 567e510+rdi-0x88 | 16 | sub_567e510 | 0x0567F41A | `0x0567F41A  movups [rdi-0x88],xmm1                        ` | - | [V] |
| 567e510+rdi-0x98 | 16 | sub_567e510 | 0x0567F421 | `0x0567F421  movups [rdi-0x98],xmm0                        ` | - | [V] |
| 567e510+rbp+0x1e8 | 8 | sub_567e510 | 0x0567F453 | `0x0567F453  mov [rbp+0x1E8],rax                           ` | record field | [V] |
| 567e510+rbp+0x250 | 8 | sub_567e510 | 0x0567F46F, 0x0567F494 | `0x0567F46F  mov [rbp+0x250],rcx                           ` / `0x0567F494  mov [rbp+0x250],rax                           ` | record field | [V] |
| 567e510+rdi-0x18 | 16 | sub_567e510 | 0x0567F4DF | `0x0567F4DF  movups [rdi-0x18],xmm1                        ` | - | [V] |
| 567e510+rdi-0x28 | 16 | sub_567e510 | 0x0567F4E3 | `0x0567F4E3  movups [rdi-0x28],xmm0                        ` | - | [V] |
| 567e510+rbp+0x258 | 8 | sub_567e510 | 0x0567F50B | `0x0567F50B  mov [rbp+0x258],rax                           ` | record field | [V] |
| 567e510+rdi | 16 | sub_567e510 | 0x0567F515 | `0x0567F515  movups [rdi],xmm0                             ` | - | [V] |
| 567e510+rdi+0x20 | 8 | sub_567e510 | 0x0567F51C | `0x0567F51C  mov [rdi+0x20],rax                            ` | - | [V] |
| 567e510+rdi+0x10 | 16 | sub_567e510 | 0x0567F524 | `0x0567F524  movups [rdi+0x10],xmm0                        ` | - | [V] |
| 567e510+call 0x568b0d0 | 5 | sub_567e510 | 0x0567F536 | `0x0567F536  call 0x568B0D0                                ; -> sub_568b0d0` | - | [V] |
| 567e510+rdi-0x270 | 16 | sub_567e510 | 0x0567F63E | `0x0567F63E  movups [rdi-0x270],xmm6                       ` | - | [V] |
| 567e510+rsi-0x200 | 16 | sub_567e510 | 0x0567F7DC | `0x0567F7DC  movups [rsi-0x200],xmm6                       ` | - | [V] |
| 567e510+call 0x9bc830 | 5 | sub_567e510 | 0x0567F940, 0x0567F94E | `0x0567F940  call 0x9BC830                                 ; -> sub_9bc830` / `0x0567F94E  call 0x9BC830                                 ; -> sub_9bc830` | - | [V] |
| 567e510+call 0x78ed0 | 5 | sub_567e510 | 0x0567F9C9 | `0x0567F9C9  call 0x78ED0                                  ; -> sub_78ed0` | - | [V] |
| 567e510+0xf9a8c78 | 5 | sub_567e510 | 0x0567F9E1 | `0x0567F9E1  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]` | - | [V] |
| 567e510+call 0x75720 | 5 | sub_567e510 | 0x0567F9E8 | `0x0567F9E8  call 0x75720                                  ; -> sub_75720` | sub_75720 | [V] |
| 567e510+call 0x75b60 | 5 | sub_567e510 | 0x0567F9EE | `0x0567F9EE  call 0x75B60                                  ; -> sub_75b60` | - | [V] |
| 567e510+rsp+0x10 | 8 | sub_567e510 | 0x0567FA00, 0x0567FA70, 0x0567FAF0, 0x0567FB80, 0x0567FBF0, 0x0567FC50, 0x0567FCA0, 0x0567FCF0, 0x0567FD20 | `0x0567FA00  mov [rsp+0x10],rdx                            ` / `0x0567FA70  mov [rsp+0x10],rdx                            ` / `0x0567FAF0  mov [rsp+0x10],rdx                            ` / `0x0567FB80  mov [rsp+0x10],rdx                            ` / `0x0567FBF0  mov [rsp+0x10],rdx                            ` / `0x0567FC50  mov [rsp+0x10],rdx                            ` / `0x0567FCA0  mov [rsp+0x10],rdx                            ` / `0x0567FCF0  mov [rsp+0x10],rdx                            ` / `0x0567FD20  mov [rsp+0x10],rdx                            ` | - | [V] |
| 567e510+rsp+0x30 | 16 | sub_567e510 | 0x0567FA21, 0x0567FA91, 0x0567FB11, 0x0567FBA1, 0x0567FC11, 0x0567FC71, 0x0567FCC1, 0x0567FD11, 0x0567FD41 | `0x0567FA21  movaps [rsp+0x30],xmm6                        ` / `0x0567FA91  movaps [rsp+0x30],xmm6                        ` / `0x0567FB11  movaps [rsp+0x30],xmm6                        ` / `0x0567FBA1  movaps [rsp+0x30],xmm6                        ` / `0x0567FC11  movaps [rsp+0x30],xmm6                        ` / `0x0567FC71  movaps [rsp+0x30],xmm6                        ` / `0x0567FCC1  movaps [rsp+0x30],xmm6                        ` / `0x0567FD11  movaps [rsp+0x30],xmm6                        ` / `0x0567FD41  movaps [rsp+0x30],xmm6                        ` | - | [V] |
| 567e510+rax-0x1d0 | 16 | sub_567e510 | 0x0567FAB3, 0x0567FB3F | `0x0567FAB3  movups [rax-0x1D0],xmm0                       ` / `0x0567FB3F  movups [rax-0x1D0],xmm0                       ` | - | [V] |
| 567e510+call 0x73150 | 5 | sub_567e510 | 0x0567FB1D, 0x0567FC29, 0x0567FD4D | `0x0567FB1D  call 0x73150                                  ; -> sub_73150` / `0x0567FC29  call 0x73150                                  ; -> sub_73150` / `0x0567FD4D  call 0x73150                                  ; -> sub_73150` | sub_73150 | [V] |
| 567e510+call 0x568ae30 | 5 | sub_567e510 | 0x0567FBAA | `0x0567FBAA  call 0x568AE30                                ; -> sub_568ae30` | - | [V] |
| 567e510+call 0x81cb0 | 5 | sub_567e510 | 0x0567FBB6, 0x0567FBC2, 0x0567FBCE, 0x0567FCCD | `0x0567FBB6  call 0x81CB0                                  ; -> sub_81cb0` / `0x0567FBC2  call 0x81CB0                                  ; -> sub_81cb0` / `0x0567FBCE  call 0x81CB0                                  ; -> sub_81cb0` / `0x0567FCCD  call 0x81CB0                                  ; -> sub_81cb0` | - | [V] |
| 567e510+call 0x568aed0 | 5 | sub_567e510 | 0x0567FC1D | `0x0567FC1D  call 0x568AED0                                ; -> sub_568aed0` | - | [V] |
| 567e510+call 0x568b010 | 5 | sub_567e510 | 0x0567FC7D | `0x0567FC7D  call 0x568B010                                ; -> sub_568b010` | - | [V] |
| 567e510+call 0xeec6e40 | 5 | sub_567e510 | 0x0567FD16 | `0x0567FD16  call 0xEEC6E40                                ; -> sub_eec6e40` | - | [V] |


### sub_567fd70 (data_f25b550) — per-element fill / dest writes [V]

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 567fd70+rbp+0x560 | 8 | sub_567fd70 | 0x0567FE5D | `0x0567FE5D  mov [rbp+0x560],rax                           ` | block header+0 = vtable ptr | [V] |
| 567fd70+rbp+0x568 | 8 | sub_567fd70 | 0x0567FE64 | `0x0567FE64  mov [rbp+0x568],rsi                           ` | block header+8 = element data base (cursor+0x240) | [V] |
| 567fd70+rbp+0x598 | 8 | sub_567fd70 | 0x0567FE6B | `0x0567FE6B  mov [rbp+0x598],rcx                           ` | block pointer = &[rbp+0x560] | [V] |
| 567fd70+rbp-0x50 | 16 | sub_567fd70 | 0x0567FEFD, 0x05680A23 | `0x0567FEFD  mov [rbp-0x50],r15                            ` / `0x05680A23  movaps [rbp-0x50],xmm0                        ` | callee out-object addr = element ptr (saved) | [V] |
| 567fd70+rbp-0x48 | 8 | sub_567fd70 | 0x0567FF01 | `0x0567FF01  mov [rbp-0x48],r13                            ` | saved node pointer | [V] |
| 567fd70+0xf99ffa0 | 5 | sub_567fd70 | 0x0567FF10, 0x0567FF4C, 0x05680206, 0x0568021C, 0x05680581, 0x056805B8, 0x05680CEE, 0x05680D14, 0x05680E1E, 0x05680FB6, 0x056812A6 | `0x0567FF10  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0567FF4C  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05680206  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0568021C  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05680581  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056805B8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05680CEE  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05680D14  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05680E1E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05680FB6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056812A6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | - | [V] |
| 567fd70+rbp+0x2b0 | 16 | sub_567fd70 | 0x0567FFB1, 0x0567FFE4, 0x0568001E, 0x0568066F | `0x0567FFB1  mov [rbp+0x2B0],rsi                           ` / `0x0567FFE4  mov [rbp+0x2B0],rsi                           ` / `0x0568001E  mov [rbp+0x2B0],r14                           ` / `0x0568066F  movaps [rbp+0x2B0],xmm0                       ` | element data base local / scratch | [V] |
| 567fd70+rsp+0x20 | 16 | sub_567fd70 | 0x0567FFCD, 0x05680000, 0x0568003A, 0x0568127C, 0x056812EC, 0x0568136C, 0x056813FC, 0x0568146C, 0x056814CC, 0x0568151C, 0x0568156C, 0x0568159C | `0x0567FFCD  mov [rsp+0x20],rax                            ` / `0x05680000  mov [rsp+0x20],rax                            ` / `0x0568003A  mov [rsp+0x20],rax                            ` / `0x0568127C  movaps [rsp+0x20],xmm7                        ` / `0x056812EC  movaps [rsp+0x20],xmm7                        ` / `0x0568136C  movaps [rsp+0x20],xmm7                        ` / `0x056813FC  movaps [rsp+0x20],xmm7                        ` / `0x0568146C  movaps [rsp+0x20],xmm7                        ` / `0x056814CC  movaps [rsp+0x20],xmm7                        ` / `0x0568151C  movaps [rsp+0x20],xmm7                        ` / `0x0568156C  movaps [rsp+0x20],xmm7                        ` / `0x0568159C  movaps [rsp+0x20],xmm7                        ` | r9 home slot | [V] |
| 567fd70+call 0x568dc40 | 5 | sub_567fd70 | 0x0567FFDD | `0x0567FFDD  call 0x568DC40                                ; -> sub_568dc40` | - | [V] |
| 567fd70+call 0x568e110 | 5 | sub_567fd70 | 0x05680010 | `0x05680010  call 0x568E110                                ; -> sub_568e110` | - | [V] |
| 567fd70+rbp+0x5a0 | 8 | sub_567fd70 | 0x05680017, 0x0568011D | `0x05680017  mov [rbp+0x5A0],rsi                           ` / `0x0568011D  mov [rbp+0x5A0],rax                           ` | record+0 = element field / callee out result | [V] |
| 567fd70+call 0x568e5f0 | 5 | sub_567fd70 | 0x0568004A | `0x0568004A  call 0x568E5F0                                ; -> sub_568e5f0` | - | [V] |
| 567fd70+rbp+0x8c8 | 8 | sub_567fd70 | 0x0568005B | `0x0568005B  mov [rbp+0x8C8],rax                           ` | callee out-object end (+0x18) | [V] |
| 567fd70+rbp+0x950 | 8 | sub_567fd70 | 0x0568006C | `0x0568006C  mov [rbp+0x950],rax                           ` | copy byte count | [V] |
| 567fd70+rbp+0x8c0 | 8 | sub_567fd70 | 0x05680088 | `0x05680088  mov [rbp+0x8C0],rcx                           ` | entry count | [V] |
| 567fd70+call 0x76a8a0 | 5 | sub_567fd70 | 0x0568009D, 0x0568093D | `0x0568009D  call 0x76A8A0                                 ; -> sub_76a8a0` / `0x0568093D  call 0x76A8A0                                 ; -> sub_76a8a0` | - | [V] |
| 567fd70+rbp+0x8b0 | 8 | sub_567fd70 | 0x056800A5 | `0x056800A5  mov [rbp+0x8B0],rdi                           ` | slot+0 | [V] |
| 567fd70+rbp+0x948 | 8 | sub_567fd70 | 0x056800AC | `0x056800AC  mov [rbp+0x948],rsi                           ` | slot+8 | [V] |
| 567fd70+call 0x655cea0 | 5 | sub_567fd70 | 0x056800DD, 0x05680EB4, 0x05681055, 0x0568132C, 0x056813B8 | `0x056800DD  call 0x655CEA0                                ; -> sub_655cea0` / `0x05680EB4  call 0x655CEA0                                ; -> sub_655cea0` / `0x05681055  call 0x655CEA0                                ; -> sub_655cea0` / `0x0568132C  call 0x655CEA0                                ; -> sub_655cea0` / `0x056813B8  call 0x655CEA0                                ; -> sub_655cea0` | - | [V] |
| 567fd70+r15-0x210 | 16 | sub_567fd70 | 0x05680124, 0x056806B6 | `0x05680124  movups [r15-0x210],xmm6                       ` / `0x056806B6  movups [r15-0x210],xmm6                       ` | - | [V] |
| 567fd70+rbp+0x940 | 8 | sub_567fd70 | 0x05680136 | `0x05680136  mov [rbp+0x940],rcx                           ` | - | [V] |
| 567fd70+rbp+0x5a8 | 8 | sub_567fd70 | 0x05680159 | `0x05680159  mov [rbp+0x5A8],rcx                           ` | record+8 = element object [elem+0x268] | [V] |
| 567fd70+rbp+0x5b0 | 8 | sub_567fd70 | 0x05680160 | `0x05680160  mov [rbp+0x5B0],rax                           ` | record+0x10 = element object [elem+0x260] | [V] |
| 567fd70+r15-0x200 | 16 | sub_567fd70 | 0x05680167 | `0x05680167  movups [r15-0x200],xmm6                       ` | - | [V] |
| 567fd70+rbp+0x5d8 | 16 | sub_567fd70 | 0x05680188 | `0x05680188  movups [rbp+0x5D8],xmm7                       ` | record+0x5D8 = callee output entry {a1,[a1+0]} | [V] |
| 567fd70+r15-0x1d0 | 16 | sub_567fd70 | 0x0568018F, 0x05681185 | `0x0568018F  movups [r15-0x1D0],xmm6                       ` / `0x05681185  movups [r15-0x1D0],xmm6                       ` | - | [V] |
| 567fd70+call 0xa78940 | 5 | sub_567fd70 | 0x056801DD | `0x056801DD  call 0xA78940                                 ; -> sub_a78940` | - | [V] |
| 567fd70+rbp+0x5e8 | 16 | sub_567fd70 | 0x05680233, 0x05680717 | `0x05680233  mov [rbp+0x5E8],rsi                           ` / `0x05680717  movups [rbp+0x5E8],xmm6                       ` | record+0x5E8 = callee-output copy dest start | [V] |
| 567fd70+rbp+0x5f0 | 8 | sub_567fd70 | 0x0568023A, 0x05680265 | `0x0568023A  mov [rbp+0x5F0],rsi                           ` / `0x05680265  mov [rbp+0x5F0],rdi                           ` | record+0x5F0 = copy cursor / copy end | [V] |
| 567fd70+rbp+0x5f8 | 8 | sub_567fd70 | 0x0568024C | `0x0568024C  mov [rbp+0x5F8],rdi                           ` | record+0x5F8 = callee-output copy dest end | [V] |
| 567fd70+call 0xeec6de0 | 5 | sub_567fd70 | 0x05680260, 0x056804D4 | `0x05680260  call 0xEEC6DE0                                ; -> sub_eec6de0` / `0x056804D4  call 0xEEC6DE0                                ; -> sub_eec6de0` | - | [V] |
| 567fd70+rbp+0x608 | 8 | sub_567fd70 | 0x0568028F | `0x0568028F  mov [rbp+0x608],rax                           ` | record+0x608 = entry count | [V] |
| 567fd70+rbp+0x618 | 16 | sub_567fd70 | 0x0568029E | `0x0568029E  movups [rbp+0x618],xmm0                       ` | record+0x618 = element data [elem+0x118] | [V] |
| 567fd70+rbp+0x628 | 16 | sub_567fd70 | 0x056802AD | `0x056802AD  movups [rbp+0x628],xmm0                       ` | record+0x628 = element data [elem+0x128] | [V] |
| 567fd70+rbp+0x638 | 16 | sub_567fd70 | 0x056802BC | `0x056802BC  movups [rbp+0x638],xmm0                       ` | record+0x638 = element data [elem+0x138] | [V] |
| 567fd70+rbp+0x648 | 16 | sub_567fd70 | 0x056802CB | `0x056802CB  movups [rbp+0x648],xmm0                       ` | record+0x648 = element data [elem+0x148] | [V] |
| 567fd70+rbp+0x658 | 16 | sub_567fd70 | 0x056802DA | `0x056802DA  movups [rbp+0x658],xmm0                       ` | record+0x658 = element data [elem+0x158] | [V] |
| 567fd70+rbp+0x668 | 16 | sub_567fd70 | 0x056802E9 | `0x056802E9  movups [rbp+0x668],xmm0                       ` | record+0x668 = element data [elem+0x168] | [V] |
| 567fd70+rbp+0x678 | 16 | sub_567fd70 | 0x056802F8 | `0x056802F8  movups [rbp+0x678],xmm0                       ` | record+0x678 = element data [elem+0x178] | [V] |
| 567fd70+rbp+0x688 | 16 | sub_567fd70 | 0x05680307 | `0x05680307  movups [rbp+0x688],xmm0                       ` | record+0x688 = element data [elem+0x188] | [V] |
| 567fd70+r15-0x110 | 8 | sub_567fd70 | 0x05680318 | `0x05680318  mov [r15-0x110],eax                           ` | - | [V] |
| 567fd70+r15-0x120 | 16 | sub_567fd70 | 0x05680322 | `0x05680322  movups [r15-0x120],xmm0                       ` | - | [V] |
| 567fd70+rbp+0x6ac | 16 | sub_567fd70 | 0x05680332 | `0x05680332  movups [rbp+0x6AC],xmm0                       ` | record+0x6AC = element +0x1AC | [V] |
| 567fd70+rbp+0x6bc | 16 | sub_567fd70 | 0x05680341 | `0x05680341  movups [rbp+0x6BC],xmm0                       ` | record+0x6BC = element +0x1BC | [V] |
| 567fd70+rbp+0x6cc | 16 | sub_567fd70 | 0x05680350 | `0x05680350  movups [rbp+0x6CC],xmm0                       ` | record+0x6CC = element +0x1CC | [V] |
| 567fd70+rbp+0x6dc | 16 | sub_567fd70 | 0x0568035F | `0x0568035F  movups [rbp+0x6DC],xmm0                       ` | record+0x6DC = element +0x1DC | [V] |
| 567fd70+rbp+0x6ec | 16 | sub_567fd70 | 0x0568036E | `0x0568036E  movups [rbp+0x6EC],xmm0                       ` | record+0x6EC = element +0x1EC | [V] |
| 567fd70+rbp+0x6fc | 16 | sub_567fd70 | 0x0568037D | `0x0568037D  movups [rbp+0x6FC],xmm0                       ` | record+0x6FC = element +0x1FC | [V] |
| 567fd70+rbp+0x70c | 16 | sub_567fd70 | 0x0568038C | `0x0568038C  movups [rbp+0x70C],xmm0                       ` | record+0x70C = element +0x20C | [V] |
| 567fd70+rbp+0x71c | 16 | sub_567fd70 | 0x0568039B | `0x0568039B  movups [rbp+0x71C],xmm0                       ` | record+0x71C = element +0x21C (last field copy) | [V] |
| 567fd70+r15-0x8c | 16 | sub_567fd70 | 0x056803AC | `0x056803AC  movups [r15-0x8C],xmm0                        ` | - | [V] |
| 567fd70+r15-0x6c | 16 | sub_567fd70 | 0x056803DD | `0x056803DD  movups [r15-0x6C],xmm1                        ` | - | [V] |
| 567fd70+r15-0x7c | 16 | sub_567fd70 | 0x056803E2 | `0x056803E2  movups [r15-0x7C],xmm0                        ` | - | [V] |
| 567fd70+rbp+0x75c | 8 | sub_567fd70 | 0x05680406 | `0x05680406  mov [rbp+0x75C],al                            ` | record+0x75C = [a1+0x48] byte | [V] |
| 567fd70+rbp+0x760 | 16 | sub_567fd70 | 0x05680410 | `0x05680410  movaps [rbp+0x760],xmm0                       ` | record+0x760 = [a1+0x4C] float4 | [V] |
| 567fd70+r15-0x16 | 16 | sub_567fd70 | 0x05680434 | `0x05680434  movups [r15-0x16],xmm3                        ` | - | [V] |
| 567fd70+r15-0x24 | 16 | sub_567fd70 | 0x05680439 | `0x05680439  movups [r15-0x24],xmm2                        ` | - | [V] |
| 567fd70+r15-0x34 | 16 | sub_567fd70 | 0x0568043E | `0x0568043E  movups [r15-0x34],xmm1                        ` | - | [V] |
| 567fd70+r15-0x44 | 16 | sub_567fd70 | 0x05680443 | `0x05680443  movups [r15-0x44],xmm0                        ` | - | [V] |
| 567fd70+rbp+0x610 | 8 | sub_567fd70 | 0x05680459 | `0x05680459  mov [rbp+0x610],rax                           ` | record+0x610 = entry count | [V] |
| 567fd70+r15+0x10 | 16 | sub_567fd70 | 0x05680460 | `0x05680460  movups [r15+0x10],xmm6                        ` | - | [V] |
| 567fd70+r15 | 16 | sub_567fd70 | 0x05680465 | `0x05680465  movups [r15],xmm6                             ` | - | [V] |
| 567fd70+call 0x9d6d0 | 5 | sub_567fd70 | 0x056804AE | `0x056804AE  call 0x9D6D0                                  ; -> sub_9d6d0` | - | [V] |
| 567fd70+rbp+0x7d0 | 8 | sub_567fd70 | 0x056804C0 | `0x056804C0  mov [rbp+0x7D0],rsi                           ` | string length | [V] |
| 567fd70+rbp+0x7b8 | 8 | sub_567fd70 | 0x056804E8 | `0x056804E8  mov [rbp+0x7B8],rax                           ` | record+0x7B8 = string heap pointer / record start zeroed | [V] |
| 567fd70+rbp+0x910 | 16 | sub_567fd70 | 0x05680503, 0x0568097C | `0x05680503  movaps [rbp+0x910],xmm6                       ` / `0x0568097C  mov [rbp+0x910],rax                           ` | record2 field zeroed | [V] |
| 567fd70+rbp+0x820 | 16 | sub_567fd70 | 0x05680529, 0x056805CB, 0x05680A0E | `0x05680529  movaps [rbp+0x820],xmm6                       ` / `0x056805CB  mov [rbp+0x820],rdi                           ` / `0x05680A0E  mov [rbp+0x820],rax                           ` | second string heap pointer | [V] |
| 567fd70+rdi-8 | 8 | sub_567fd70 | 0x0568059F | `0x0568059F  mov [rdi-8],rax                               ` | - | [V] |
| 567fd70+rbp+0x830 | 16 | sub_567fd70 | 0x056805D2, 0x05680A00 | `0x056805D2  mov [rbp+0x830],rsi                           ` / `0x05680A00  movups [rbp+0x830],xmm0                       ` | record2 field | [V] |
| 567fd70+rbp+0x838 | 8 | sub_567fd70 | 0x056805D9 | `0x056805D9  mov [rbp+0x838],r12                           ` | record2 field | [V] |
| 567fd70+call 0xeec6ec0 | 5 | sub_567fd70 | 0x056805E9 | `0x056805E9  call 0xEEC6EC0                                ; -> sub_eec6ec0` | - | [V] |
| 567fd70+call 0xe935700 | 5 | sub_567fd70 | 0x0568064E, 0x05680DDC, 0x05680E6F, 0x05680EFA, 0x05680F53, 0x05680F98, 0x05681007, 0x056810A1, 0x05681103, 0x05681148 | `0x0568064E  call 0xE935700                                ; -> sub_e935700` / `0x05680DDC  call 0xE935700                                ; -> sub_e935700` / `0x05680E6F  call 0xE935700                                ; -> sub_e935700` / `0x05680EFA  call 0xE935700                                ; -> sub_e935700` / `0x05680F53  call 0xE935700                                ; -> sub_e935700` / `0x05680F98  call 0xE935700                                ; -> sub_e935700` / `0x05681007  call 0xE935700                                ; -> sub_e935700` / `0x056810A1  call 0xE935700                                ; -> sub_e935700` / `0x05681103  call 0xE935700                                ; -> sub_e935700` / `0x05681148  call 0xE935700                                ; -> sub_e935700` | - | [V] |
| 567fd70+rbp+0x900 | 16 | sub_567fd70 | 0x05680661 | `0x05680661  movaps [rbp+0x900],xmm1                       ` | record2 field zeroed | [V] |
| 567fd70+rbp+0x8f0 | 16 | sub_567fd70 | 0x05680668 | `0x05680668  movaps [rbp+0x8F0],xmm0                       ` | - | [V] |
| 567fd70+rbp+0x2c0 | 16 | sub_567fd70 | 0x05680676 | `0x05680676  movaps [rbp+0x2C0],xmm1                       ` | - | [V] |
| 567fd70+rbp+0x2d0 | 16 | sub_567fd70 | 0x056806A1 | `0x056806A1  movaps [rbp+0x2D0],xmm0                       ` | - | [V] |
| 567fd70+rbp+0x2e0 | 8 | sub_567fd70 | 0x056806AF | `0x056806AF  mov [rbp+0x2E0],rax                           ` | - | [V] |
| 567fd70+rsi-0x230 | 16 | sub_567fd70 | 0x056806BE | `0x056806BE  movups [rsi-0x230],xmm6                       ` | - | [V] |
| 567fd70+rbp+0x300 | 8 | sub_567fd70 | 0x056806DE | `0x056806DE  mov [rbp+0x300],al                            ` | flag byte | [V] |
| 567fd70+rbp+0x308 | 16 | sub_567fd70 | 0x05680710 | `0x05680710  movups [rbp+0x308],xmm0                       ` | record+0x308 = callee output entry {a1,[a1+0]} | [V] |
| 567fd70+rbp+0x318 | 16 | sub_567fd70 | 0x0568071E, 0x05680AB5 | `0x0568071E  movups [rbp+0x318],xmm1                       ` / `0x05680AB5  movups [rbp+0x318],xmm6                       ` | record field zeroed | [V] |
| 567fd70+rbp+0x328 | 8 | sub_567fd70 | 0x05680725 | `0x05680725  mov [rbp+0x328],rax                           ` | record+0x328 = copy-dest end (dest pointer) | [V] |
| 567fd70+rsi-0x1e0 | 16 | sub_567fd70 | 0x0568073B | `0x0568073B  movups [rsi-0x1E0],xmm0                       ` | - | [V] |
| 567fd70+rbp+0x348 | 16 | sub_567fd70 | 0x0568075E | `0x0568075E  movups [rbp+0x348],xmm0                       ` | record+0x348 = element data field | [V] |
| 567fd70+rbp+0x358 | 16 | sub_567fd70 | 0x05680765 | `0x05680765  movups [rbp+0x358],xmm1                       ` | record+0x358 = element data field | [V] |
| 567fd70+rbp+0x368 | 16 | sub_567fd70 | 0x0568076C | `0x0568076C  movups [rbp+0x368],xmm2                       ` | record+0x368 = element data field | [V] |
| 567fd70+rbp+0x378 | 16 | sub_567fd70 | 0x05680773 | `0x05680773  movups [rbp+0x378],xmm3                       ` | record+0x378 = element data field | [V] |
| 567fd70+rbp+0x388 | 16 | sub_567fd70 | 0x05680781 | `0x05680781  movups [rbp+0x388],xmm0                       ` | record+0x388 = element data field | [V] |
| 567fd70+rbp+0x398 | 16 | sub_567fd70 | 0x0568078F | `0x0568078F  movups [rbp+0x398],xmm0                       ` | record+0x398 = element data field | [V] |
| 567fd70+rbp+0x3a8 | 16 | sub_567fd70 | 0x0568079D | `0x0568079D  movups [rbp+0x3A8],xmm0                       ` | record+0x3A8 = element data field | [V] |
| 567fd70+rbp+0x3b8 | 16 | sub_567fd70 | 0x056807AB | `0x056807AB  movups [rbp+0x3B8],xmm0                       ` | record+0x3B8 = element data field | [V] |
| 567fd70+rsi-0x140 | 8 | sub_567fd70 | 0x056807B9 | `0x056807B9  mov [rsi-0x140],eax                           ` | - | [V] |
| 567fd70+rsi-0x150 | 16 | sub_567fd70 | 0x056807C7 | `0x056807C7  movups [rsi-0x150],xmm0                       ` | - | [V] |
| 567fd70+rbp+0x3dc | 16 | sub_567fd70 | 0x056807DC | `0x056807DC  movups [rbp+0x3DC],xmm0                       ` | record+0x3DC = element data field | [V] |
| 567fd70+rbp+0x3ec | 16 | sub_567fd70 | 0x056807E3 | `0x056807E3  movups [rbp+0x3EC],xmm1                       ` | record+0x3EC = element data field | [V] |
| 567fd70+rbp+0x3fc | 16 | sub_567fd70 | 0x056807F1 | `0x056807F1  movups [rbp+0x3FC],xmm0                       ` | record+0x3FC = element data field | [V] |
| 567fd70+rbp+0x40c | 16 | sub_567fd70 | 0x056807FF | `0x056807FF  movups [rbp+0x40C],xmm0                       ` | record+0x40C = element data field | [V] |
| 567fd70+rbp+0x41c | 16 | sub_567fd70 | 0x0568080D | `0x0568080D  movups [rbp+0x41C],xmm0                       ` | record+0x41C = element data field | [V] |
| 567fd70+rbp+0x42c | 16 | sub_567fd70 | 0x0568081B | `0x0568081B  movups [rbp+0x42C],xmm0                       ` | record+0x42C = element data field | [V] |
| 567fd70+rbp+0x43c | 16 | sub_567fd70 | 0x05680829 | `0x05680829  movups [rbp+0x43C],xmm0                       ` | record+0x43C = element data field | [V] |
| 567fd70+rbp+0x44c | 16 | sub_567fd70 | 0x05680837 | `0x05680837  movups [rbp+0x44C],xmm0                       ` | record+0x44C = element data field | [V] |
| 567fd70+rsi-0xbc | 16 | sub_567fd70 | 0x05680846 | `0x05680846  movups [rsi-0xBC],xmm0                        ` | - | [V] |
| 567fd70+rsi-0x9c | 16 | sub_567fd70 | 0x05680867 | `0x05680867  movups [rsi-0x9C],xmm1                        ` | - | [V] |
| 567fd70+rsi-0xac | 16 | sub_567fd70 | 0x0568086E | `0x0568086E  movups [rsi-0xAC],xmm0                        ` | - | [V] |
| 567fd70+rbp+0x48c | 8 | sub_567fd70 | 0x0568088C | `0x0568088C  mov [rbp+0x48C],al                            ` | record+0x48C | [V] |
| 567fd70+rbp+0x490 | 16 | sub_567fd70 | 0x05680899 | `0x05680899  movaps [rbp+0x490],xmm0                       ` | record+0x490 | [V] |
| 567fd70+rsi-0x46 | 16 | sub_567fd70 | 0x056808BB | `0x056808BB  movups [rsi-0x46],xmm3                        ` | - | [V] |
| 567fd70+rsi-0x54 | 16 | sub_567fd70 | 0x056808BF | `0x056808BF  movups [rsi-0x54],xmm2                        ` | - | [V] |
| 567fd70+rsi-0x64 | 16 | sub_567fd70 | 0x056808C3 | `0x056808C3  movups [rsi-0x64],xmm1                        ` | - | [V] |
| 567fd70+rsi-0x74 | 16 | sub_567fd70 | 0x056808C7 | `0x056808C7  movups [rsi-0x74],xmm0                        ` | - | [V] |
| 567fd70+rsi-0x18 | 16 | sub_567fd70 | 0x056808EB | `0x056808EB  movups [rsi-0x18],xmm1                        ` | - | [V] |
| 567fd70+rsi-0x28 | 16 | sub_567fd70 | 0x056808EF | `0x056808EF  movups [rsi-0x28],xmm0                        ` | - | [V] |
| 567fd70+rbp+0x4e8 | 8 | sub_567fd70 | 0x05680917 | `0x05680917  mov [rbp+0x4E8],rax                           ` | record+0x4E8 = string heap pointer | [V] |
| 567fd70+rbp+0x518 | 8 | sub_567fd70 | 0x05680925 | `0x05680925  mov [rbp+0x518],rax                           ` | record2 vtable = data_f25b6a0 | [V] |
| 567fd70+rbp+0x550 | 8 | sub_567fd70 | 0x0568092C | `0x0568092C  mov [rbp+0x550],rsi                           ` | record2 field | [V] |
| 567fd70+rbp+0x918 | 8 | sub_567fd70 | 0x05680975 | `0x05680975  mov [rbp+0x918],rcx                           ` | record2 field | [V] |
| 567fd70+r10 | 16 | sub_567fd70 | 0x056809B2 | `0x056809B2  movups [r10],xmm0                             ` | - | [V] |
| 567fd70+r10+0x20 | 8 | sub_567fd70 | 0x056809C1 | `0x056809C1  mov [r10+0x20],r8                             ` | - | [V] |
| 567fd70+r10+0x10 | 16 | sub_567fd70 | 0x056809C9 | `0x056809C9  movups [r10+0x10],xmm0                        ` | - | [V] |
| 567fd70+rbp+0x828 | 8 | sub_567fd70 | 0x056809D9 | `0x056809D9  mov [rbp+0x828],rcx                           ` | record2 field | [V] |
| 567fd70+rbp+0x920 | 8 | sub_567fd70 | 0x056809F9 | `0x056809F9  mov [rbp+0x920],rcx                           ` | record2 field | [V] |
| 567fd70+rbp+0x840 | 8 | sub_567fd70 | 0x05680A07 | `0x05680A07  mov [rbp+0x840],rdx                           ` | record2 field | [V] |
| 567fd70+rbp-0x40 | 16 | sub_567fd70 | 0x05680A27 | `0x05680A27  movaps [rbp-0x40],xmm1                        ` | restore callee out-object base | [V] |
| 567fd70+rbp-0x30 | 16 | sub_567fd70 | 0x05680A4F | `0x05680A4F  movaps [rbp-0x30],xmm0                        ` | restore callee out-object base | [V] |
| 567fd70+rbp-0x20 | 8 | sub_567fd70 | 0x05680A5A | `0x05680A5A  mov [rbp-0x20],rax                            ` | restore callee out-object field | [V] |
| 567fd70+rsi-0x240 | 16 | sub_567fd70 | 0x05680A5E | `0x05680A5E  movups [rsi-0x240],xmm6                       ` | - | [V] |
| 567fd70+rdi-0x2a0 | 16 | sub_567fd70 | 0x05680A65 | `0x05680A65  movups [rdi-0x2A0],xmm6                       ` | - | [V] |
| 567fd70+rbp | 8 | sub_567fd70 | 0x05680A85 | `0x05680A85  mov [rbp],al                                  ` | flag byte | [V] |
| 567fd70+rbp+8 | 16 | sub_567fd70 | 0x05680AB1 | `0x05680AB1  movups [rbp+8],xmm0                           ` | record field | [V] |
| 567fd70+rbp+0x18 | 16 | sub_567fd70 | 0x05680ABC | `0x05680ABC  movups [rbp+0x18],xmm1                        ` | record field | [V] |
| 567fd70+rbp+0x28 | 8 | sub_567fd70 | 0x05680AC0 | `0x05680AC0  mov [rbp+0x28],rax                            ` | record field | [V] |
| 567fd70+rdi-0x250 | 16 | sub_567fd70 | 0x05680ACF | `0x05680ACF  movups [rdi-0x250],xmm0                       ` | - | [V] |
| 567fd70+rbp+0x48 | 16 | sub_567fd70 | 0x05680AF2 | `0x05680AF2  movups [rbp+0x48],xmm0                        ` | record field | [V] |
| 567fd70+rbp+0x58 | 16 | sub_567fd70 | 0x05680AF6 | `0x05680AF6  movups [rbp+0x58],xmm1                        ` | record field | [V] |
| 567fd70+rbp+0x68 | 16 | sub_567fd70 | 0x05680AFA | `0x05680AFA  movups [rbp+0x68],xmm2                        ` | record field | [V] |
| 567fd70+rbp+0x78 | 16 | sub_567fd70 | 0x05680AFE | `0x05680AFE  movups [rbp+0x78],xmm3                        ` | record field | [V] |
| 567fd70+rbp+0x88 | 16 | sub_567fd70 | 0x05680B09 | `0x05680B09  movups [rbp+0x88],xmm0                        ` | record field | [V] |
| 567fd70+rbp+0x98 | 16 | sub_567fd70 | 0x05680B17 | `0x05680B17  movups [rbp+0x98],xmm0                        ` | record field | [V] |
| 567fd70+rbp+0xa8 | 16 | sub_567fd70 | 0x05680B25 | `0x05680B25  movups [rbp+0xA8],xmm0                        ` | record field | [V] |
| 567fd70+rbp+0xb8 | 16 | sub_567fd70 | 0x05680B33 | `0x05680B33  movups [rbp+0xB8],xmm0                        ` | record field | [V] |
| 567fd70+rdi-0x1b0 | 8 | sub_567fd70 | 0x05680B40 | `0x05680B40  mov [rdi-0x1B0],eax                           ` | - | [V] |
| 567fd70+rdi-0x1c0 | 16 | sub_567fd70 | 0x05680B4D | `0x05680B4D  movups [rdi-0x1C0],xmm0                       ` | - | [V] |
| 567fd70+rbp+0xdc | 16 | sub_567fd70 | 0x05680B62 | `0x05680B62  movups [rbp+0xDC],xmm0                        ` | record field | [V] |
| 567fd70+rbp+0xec | 16 | sub_567fd70 | 0x05680B69 | `0x05680B69  movups [rbp+0xEC],xmm1                        ` | record field | [V] |
| 567fd70+rbp+0xfc | 16 | sub_567fd70 | 0x05680B77 | `0x05680B77  movups [rbp+0xFC],xmm0                        ` | record field | [V] |
| 567fd70+rbp+0x10c | 16 | sub_567fd70 | 0x05680B85 | `0x05680B85  movups [rbp+0x10C],xmm0                       ` | record field | [V] |
| 567fd70+rbp+0x11c | 16 | sub_567fd70 | 0x05680B93 | `0x05680B93  movups [rbp+0x11C],xmm0                       ` | record field | [V] |
| 567fd70+rbp+0x12c | 16 | sub_567fd70 | 0x05680BA1 | `0x05680BA1  movups [rbp+0x12C],xmm0                       ` | record field | [V] |
| 567fd70+rbp+0x13c | 16 | sub_567fd70 | 0x05680BAF | `0x05680BAF  movups [rbp+0x13C],xmm0                       ` | record field | [V] |
| 567fd70+rbp+0x14c | 16 | sub_567fd70 | 0x05680BBD | `0x05680BBD  movups [rbp+0x14C],xmm0                       ` | record field | [V] |
| 567fd70+rdi-0x12c | 16 | sub_567fd70 | 0x05680BCB | `0x05680BCB  movups [rdi-0x12C],xmm0                       ` | - | [V] |
| 567fd70+rdi-0x10c | 16 | sub_567fd70 | 0x05680BF4 | `0x05680BF4  movups [rdi-0x10C],xmm1                       ` | - | [V] |
| 567fd70+rdi-0x11c | 16 | sub_567fd70 | 0x05680BFB | `0x05680BFB  movups [rdi-0x11C],xmm0                       ` | - | [V] |
| 567fd70+rbp+0x18c | 8 | sub_567fd70 | 0x05680C19 | `0x05680C19  mov [rbp+0x18C],al                            ` | flag byte | [V] |
| 567fd70+rbp+0x190 | 16 | sub_567fd70 | 0x05680C26 | `0x05680C26  movaps [rbp+0x190],xmm0                       ` | record field | [V] |
| 567fd70+rdi-0xb6 | 16 | sub_567fd70 | 0x05680C44 | `0x05680C44  movups [rdi-0xB6],xmm3                        ` | - | [V] |
| 567fd70+rdi-0xc4 | 16 | sub_567fd70 | 0x05680C4B | `0x05680C4B  movups [rdi-0xC4],xmm2                        ` | - | [V] |
| 567fd70+rdi-0xd4 | 16 | sub_567fd70 | 0x05680C52 | `0x05680C52  movups [rdi-0xD4],xmm1                        ` | - | [V] |
| 567fd70+rdi-0xe4 | 16 | sub_567fd70 | 0x05680C59 | `0x05680C59  movups [rdi-0xE4],xmm0                        ` | - | [V] |
| 567fd70+rdi-0x88 | 16 | sub_567fd70 | 0x05680C7A | `0x05680C7A  movups [rdi-0x88],xmm1                        ` | - | [V] |
| 567fd70+rdi-0x98 | 16 | sub_567fd70 | 0x05680C81 | `0x05680C81  movups [rdi-0x98],xmm0                        ` | - | [V] |
| 567fd70+rbp+0x1e8 | 8 | sub_567fd70 | 0x05680CB3 | `0x05680CB3  mov [rbp+0x1E8],rax                           ` | record field | [V] |
| 567fd70+rbp+0x250 | 8 | sub_567fd70 | 0x05680CCF, 0x05680CF4 | `0x05680CCF  mov [rbp+0x250],rcx                           ` / `0x05680CF4  mov [rbp+0x250],rax                           ` | record field | [V] |
| 567fd70+rdi-0x18 | 16 | sub_567fd70 | 0x05680D3F | `0x05680D3F  movups [rdi-0x18],xmm1                        ` | - | [V] |
| 567fd70+rdi-0x28 | 16 | sub_567fd70 | 0x05680D43 | `0x05680D43  movups [rdi-0x28],xmm0                        ` | - | [V] |
| 567fd70+rbp+0x258 | 8 | sub_567fd70 | 0x05680D6B | `0x05680D6B  mov [rbp+0x258],rax                           ` | record field | [V] |
| 567fd70+rdi | 16 | sub_567fd70 | 0x05680D75 | `0x05680D75  movups [rdi],xmm0                             ` | - | [V] |
| 567fd70+rdi+0x20 | 8 | sub_567fd70 | 0x05680D7C | `0x05680D7C  mov [rdi+0x20],rax                            ` | - | [V] |
| 567fd70+rdi+0x10 | 16 | sub_567fd70 | 0x05680D84 | `0x05680D84  movups [rdi+0x10],xmm0                        ` | - | [V] |
| 567fd70+call 0x568b0d0 | 5 | sub_567fd70 | 0x05680D96 | `0x05680D96  call 0x568B0D0                                ; -> sub_568b0d0` | - | [V] |
| 567fd70+rdi-0x270 | 16 | sub_567fd70 | 0x05680E9E | `0x05680E9E  movups [rdi-0x270],xmm6                       ` | - | [V] |
| 567fd70+rsi-0x200 | 16 | sub_567fd70 | 0x0568103C | `0x0568103C  movups [rsi-0x200],xmm6                       ` | - | [V] |
| 567fd70+call 0x9bc830 | 5 | sub_567fd70 | 0x056811A0, 0x056811AE | `0x056811A0  call 0x9BC830                                 ; -> sub_9bc830` / `0x056811AE  call 0x9BC830                                 ; -> sub_9bc830` | - | [V] |
| 567fd70+call 0x78ed0 | 5 | sub_567fd70 | 0x05681229 | `0x05681229  call 0x78ED0                                  ; -> sub_78ed0` | - | [V] |
| 567fd70+0xf9a8c78 | 5 | sub_567fd70 | 0x05681241 | `0x05681241  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]` | - | [V] |
| 567fd70+call 0x75720 | 5 | sub_567fd70 | 0x05681248 | `0x05681248  call 0x75720                                  ; -> sub_75720` | sub_75720 | [V] |
| 567fd70+call 0x75b60 | 5 | sub_567fd70 | 0x0568124E | `0x0568124E  call 0x75B60                                  ; -> sub_75b60` | - | [V] |
| 567fd70+rsp+0x10 | 8 | sub_567fd70 | 0x05681260, 0x056812D0, 0x05681350, 0x056813E0, 0x05681450, 0x056814B0, 0x05681500, 0x05681550, 0x05681580 | `0x05681260  mov [rsp+0x10],rdx                            ` / `0x056812D0  mov [rsp+0x10],rdx                            ` / `0x05681350  mov [rsp+0x10],rdx                            ` / `0x056813E0  mov [rsp+0x10],rdx                            ` / `0x05681450  mov [rsp+0x10],rdx                            ` / `0x056814B0  mov [rsp+0x10],rdx                            ` / `0x05681500  mov [rsp+0x10],rdx                            ` / `0x05681550  mov [rsp+0x10],rdx                            ` / `0x05681580  mov [rsp+0x10],rdx                            ` | - | [V] |
| 567fd70+rsp+0x30 | 16 | sub_567fd70 | 0x05681281, 0x056812F1, 0x05681371, 0x05681401, 0x05681471, 0x056814D1, 0x05681521, 0x05681571, 0x056815A1 | `0x05681281  movaps [rsp+0x30],xmm6                        ` / `0x056812F1  movaps [rsp+0x30],xmm6                        ` / `0x05681371  movaps [rsp+0x30],xmm6                        ` / `0x05681401  movaps [rsp+0x30],xmm6                        ` / `0x05681471  movaps [rsp+0x30],xmm6                        ` / `0x056814D1  movaps [rsp+0x30],xmm6                        ` / `0x05681521  movaps [rsp+0x30],xmm6                        ` / `0x05681571  movaps [rsp+0x30],xmm6                        ` / `0x056815A1  movaps [rsp+0x30],xmm6                        ` | - | [V] |
| 567fd70+rax-0x1d0 | 16 | sub_567fd70 | 0x05681313, 0x0568139F | `0x05681313  movups [rax-0x1D0],xmm0                       ` / `0x0568139F  movups [rax-0x1D0],xmm0                       ` | - | [V] |
| 567fd70+call 0x73150 | 5 | sub_567fd70 | 0x0568137D, 0x05681489, 0x056815AD | `0x0568137D  call 0x73150                                  ; -> sub_73150` / `0x05681489  call 0x73150                                  ; -> sub_73150` / `0x056815AD  call 0x73150                                  ; -> sub_73150` | sub_73150 | [V] |
| 567fd70+call 0x568ae30 | 5 | sub_567fd70 | 0x0568140A | `0x0568140A  call 0x568AE30                                ; -> sub_568ae30` | - | [V] |
| 567fd70+call 0x81cb0 | 5 | sub_567fd70 | 0x05681416, 0x05681422, 0x0568142E, 0x0568152D | `0x05681416  call 0x81CB0                                  ; -> sub_81cb0` / `0x05681422  call 0x81CB0                                  ; -> sub_81cb0` / `0x0568142E  call 0x81CB0                                  ; -> sub_81cb0` / `0x0568152D  call 0x81CB0                                  ; -> sub_81cb0` | - | [V] |
| 567fd70+call 0x568aed0 | 5 | sub_567fd70 | 0x0568147D | `0x0568147D  call 0x568AED0                                ; -> sub_568aed0` | - | [V] |
| 567fd70+call 0x568b010 | 5 | sub_567fd70 | 0x056814DD | `0x056814DD  call 0x568B010                                ; -> sub_568b010` | - | [V] |
| 567fd70+call 0xeec6e40 | 5 | sub_567fd70 | 0x05681576 | `0x05681576  call 0xEEC6E40                                ; -> sub_eec6e40` | - | [V] |


### sub_56815d0 (data_f25b5b0) — per-element fill / dest writes [V]

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 56815d0+rbp+0x560 | 8 | sub_56815d0 | 0x056816BD | `0x056816BD  mov [rbp+0x560],rax                           ` | block header+0 = vtable ptr | [V] |
| 56815d0+rbp+0x568 | 8 | sub_56815d0 | 0x056816C4 | `0x056816C4  mov [rbp+0x568],rsi                           ` | block header+8 = element data base (cursor+0x240) | [V] |
| 56815d0+rbp+0x598 | 8 | sub_56815d0 | 0x056816CB | `0x056816CB  mov [rbp+0x598],rcx                           ` | block pointer = &[rbp+0x560] | [V] |
| 56815d0+rbp-0x50 | 16 | sub_56815d0 | 0x05681754, 0x05682273 | `0x05681754  mov [rbp-0x50],r15                            ` / `0x05682273  movaps [rbp-0x50],xmm0                        ` | callee out-object addr = element ptr (saved) | [V] |
| 56815d0+rbp-0x48 | 8 | sub_56815d0 | 0x05681758 | `0x05681758  mov [rbp-0x48],r13                            ` | saved node pointer | [V] |
| 56815d0+0xf99ffa0 | 5 | sub_56815d0 | 0x05681767, 0x056817A3, 0x05681A56, 0x05681A6C, 0x05681DD1, 0x05681E08, 0x0568253E, 0x05682564, 0x0568266E, 0x05682806, 0x05682AF6 | `0x05681767  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056817A3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05681A56  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05681A6C  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05681DD1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05681E08  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0568253E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05682564  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0568266E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05682806  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05682AF6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | - | [V] |
| 56815d0+rbp+0x2b0 | 16 | sub_56815d0 | 0x05681801, 0x05681834, 0x0568186E, 0x05681EBF | `0x05681801  mov [rbp+0x2B0],rsi                           ` / `0x05681834  mov [rbp+0x2B0],rsi                           ` / `0x0568186E  mov [rbp+0x2B0],r14                           ` / `0x05681EBF  movaps [rbp+0x2B0],xmm0                       ` | element data base local / scratch | [V] |
| 56815d0+rsp+0x20 | 16 | sub_56815d0 | 0x0568181D, 0x05681850, 0x0568188A, 0x05682ACC, 0x05682B3C, 0x05682BBC, 0x05682C4C, 0x05682CBC, 0x05682D1C, 0x05682D6C, 0x05682DBC, 0x05682DEC | `0x0568181D  mov [rsp+0x20],rax                            ` / `0x05681850  mov [rsp+0x20],rax                            ` / `0x0568188A  mov [rsp+0x20],rax                            ` / `0x05682ACC  movaps [rsp+0x20],xmm7                        ` / `0x05682B3C  movaps [rsp+0x20],xmm7                        ` / `0x05682BBC  movaps [rsp+0x20],xmm7                        ` / `0x05682C4C  movaps [rsp+0x20],xmm7                        ` / `0x05682CBC  movaps [rsp+0x20],xmm7                        ` / `0x05682D1C  movaps [rsp+0x20],xmm7                        ` / `0x05682D6C  movaps [rsp+0x20],xmm7                        ` / `0x05682DBC  movaps [rsp+0x20],xmm7                        ` / `0x05682DEC  movaps [rsp+0x20],xmm7                        ` | r9 home slot | [V] |
| 56815d0+call 0x568eb90 | 5 | sub_56815d0 | 0x0568182D | `0x0568182D  call 0x568EB90                                ; -> sub_568eb90` | - | [V] |
| 56815d0+call 0x568f030 | 5 | sub_56815d0 | 0x05681860 | `0x05681860  call 0x568F030                                ; -> sub_568f030` | - | [V] |
| 56815d0+rbp+0x5a0 | 8 | sub_56815d0 | 0x05681867, 0x0568196D | `0x05681867  mov [rbp+0x5A0],rsi                           ` / `0x0568196D  mov [rbp+0x5A0],rax                           ` | record+0 = element field / callee out result | [V] |
| 56815d0+call 0x568f4e0 | 5 | sub_56815d0 | 0x0568189A | `0x0568189A  call 0x568F4E0                                ; -> sub_568f4e0` | - | [V] |
| 56815d0+rbp+0x8c8 | 8 | sub_56815d0 | 0x056818AB | `0x056818AB  mov [rbp+0x8C8],rax                           ` | callee out-object end (+0x18) | [V] |
| 56815d0+rbp+0x950 | 8 | sub_56815d0 | 0x056818BC | `0x056818BC  mov [rbp+0x950],rax                           ` | copy byte count | [V] |
| 56815d0+rbp+0x8c0 | 8 | sub_56815d0 | 0x056818D8 | `0x056818D8  mov [rbp+0x8C0],rcx                           ` | entry count | [V] |
| 56815d0+call 0x76a8a0 | 5 | sub_56815d0 | 0x056818ED, 0x0568218D | `0x056818ED  call 0x76A8A0                                 ; -> sub_76a8a0` / `0x0568218D  call 0x76A8A0                                 ; -> sub_76a8a0` | - | [V] |
| 56815d0+rbp+0x8b0 | 8 | sub_56815d0 | 0x056818F5 | `0x056818F5  mov [rbp+0x8B0],rdi                           ` | slot+0 | [V] |
| 56815d0+rbp+0x948 | 8 | sub_56815d0 | 0x056818FC | `0x056818FC  mov [rbp+0x948],rsi                           ` | slot+8 | [V] |
| 56815d0+call 0x655cea0 | 5 | sub_56815d0 | 0x0568192D, 0x05682704, 0x056828A5, 0x05682B7C, 0x05682C08 | `0x0568192D  call 0x655CEA0                                ; -> sub_655cea0` / `0x05682704  call 0x655CEA0                                ; -> sub_655cea0` / `0x056828A5  call 0x655CEA0                                ; -> sub_655cea0` / `0x05682B7C  call 0x655CEA0                                ; -> sub_655cea0` / `0x05682C08  call 0x655CEA0                                ; -> sub_655cea0` | - | [V] |
| 56815d0+r15-0x210 | 16 | sub_56815d0 | 0x05681974, 0x05681F06 | `0x05681974  movups [r15-0x210],xmm6                       ` / `0x05681F06  movups [r15-0x210],xmm6                       ` | - | [V] |
| 56815d0+rbp+0x940 | 8 | sub_56815d0 | 0x05681986 | `0x05681986  mov [rbp+0x940],rcx                           ` | - | [V] |
| 56815d0+rbp+0x5a8 | 8 | sub_56815d0 | 0x056819A9 | `0x056819A9  mov [rbp+0x5A8],rcx                           ` | record+8 = element object [elem+0x268] | [V] |
| 56815d0+rbp+0x5b0 | 8 | sub_56815d0 | 0x056819B0 | `0x056819B0  mov [rbp+0x5B0],rax                           ` | record+0x10 = element object [elem+0x260] | [V] |
| 56815d0+r15-0x200 | 16 | sub_56815d0 | 0x056819B7 | `0x056819B7  movups [r15-0x200],xmm6                       ` | - | [V] |
| 56815d0+rbp+0x5d8 | 16 | sub_56815d0 | 0x056819D8 | `0x056819D8  movups [rbp+0x5D8],xmm7                       ` | record+0x5D8 = callee output entry {a1,[a1+0]} | [V] |
| 56815d0+r15-0x1d0 | 16 | sub_56815d0 | 0x056819DF, 0x056829D5 | `0x056819DF  movups [r15-0x1D0],xmm6                       ` / `0x056829D5  movups [r15-0x1D0],xmm6                       ` | - | [V] |
| 56815d0+call 0xa78940 | 5 | sub_56815d0 | 0x05681A2D | `0x05681A2D  call 0xA78940                                 ; -> sub_a78940` | - | [V] |
| 56815d0+rbp+0x5e8 | 16 | sub_56815d0 | 0x05681A83, 0x05681F67 | `0x05681A83  mov [rbp+0x5E8],rsi                           ` / `0x05681F67  movups [rbp+0x5E8],xmm6                       ` | record+0x5E8 = callee-output copy dest start | [V] |
| 56815d0+rbp+0x5f0 | 8 | sub_56815d0 | 0x05681A8A, 0x05681AB5 | `0x05681A8A  mov [rbp+0x5F0],rsi                           ` / `0x05681AB5  mov [rbp+0x5F0],rdi                           ` | record+0x5F0 = copy cursor / copy end | [V] |
| 56815d0+rbp+0x5f8 | 8 | sub_56815d0 | 0x05681A9C | `0x05681A9C  mov [rbp+0x5F8],rdi                           ` | record+0x5F8 = callee-output copy dest end | [V] |
| 56815d0+call 0xeec6de0 | 5 | sub_56815d0 | 0x05681AB0, 0x05681D24 | `0x05681AB0  call 0xEEC6DE0                                ; -> sub_eec6de0` / `0x05681D24  call 0xEEC6DE0                                ; -> sub_eec6de0` | - | [V] |
| 56815d0+rbp+0x608 | 8 | sub_56815d0 | 0x05681ADF | `0x05681ADF  mov [rbp+0x608],rax                           ` | record+0x608 = entry count | [V] |
| 56815d0+rbp+0x618 | 16 | sub_56815d0 | 0x05681AEE | `0x05681AEE  movups [rbp+0x618],xmm0                       ` | record+0x618 = element data [elem+0x118] | [V] |
| 56815d0+rbp+0x628 | 16 | sub_56815d0 | 0x05681AFD | `0x05681AFD  movups [rbp+0x628],xmm0                       ` | record+0x628 = element data [elem+0x128] | [V] |
| 56815d0+rbp+0x638 | 16 | sub_56815d0 | 0x05681B0C | `0x05681B0C  movups [rbp+0x638],xmm0                       ` | record+0x638 = element data [elem+0x138] | [V] |
| 56815d0+rbp+0x648 | 16 | sub_56815d0 | 0x05681B1B | `0x05681B1B  movups [rbp+0x648],xmm0                       ` | record+0x648 = element data [elem+0x148] | [V] |
| 56815d0+rbp+0x658 | 16 | sub_56815d0 | 0x05681B2A | `0x05681B2A  movups [rbp+0x658],xmm0                       ` | record+0x658 = element data [elem+0x158] | [V] |
| 56815d0+rbp+0x668 | 16 | sub_56815d0 | 0x05681B39 | `0x05681B39  movups [rbp+0x668],xmm0                       ` | record+0x668 = element data [elem+0x168] | [V] |
| 56815d0+rbp+0x678 | 16 | sub_56815d0 | 0x05681B48 | `0x05681B48  movups [rbp+0x678],xmm0                       ` | record+0x678 = element data [elem+0x178] | [V] |
| 56815d0+rbp+0x688 | 16 | sub_56815d0 | 0x05681B57 | `0x05681B57  movups [rbp+0x688],xmm0                       ` | record+0x688 = element data [elem+0x188] | [V] |
| 56815d0+r15-0x110 | 8 | sub_56815d0 | 0x05681B68 | `0x05681B68  mov [r15-0x110],eax                           ` | - | [V] |
| 56815d0+r15-0x120 | 16 | sub_56815d0 | 0x05681B72 | `0x05681B72  movups [r15-0x120],xmm0                       ` | - | [V] |
| 56815d0+rbp+0x6ac | 16 | sub_56815d0 | 0x05681B82 | `0x05681B82  movups [rbp+0x6AC],xmm0                       ` | record+0x6AC = element +0x1AC | [V] |
| 56815d0+rbp+0x6bc | 16 | sub_56815d0 | 0x05681B91 | `0x05681B91  movups [rbp+0x6BC],xmm0                       ` | record+0x6BC = element +0x1BC | [V] |
| 56815d0+rbp+0x6cc | 16 | sub_56815d0 | 0x05681BA0 | `0x05681BA0  movups [rbp+0x6CC],xmm0                       ` | record+0x6CC = element +0x1CC | [V] |
| 56815d0+rbp+0x6dc | 16 | sub_56815d0 | 0x05681BAF | `0x05681BAF  movups [rbp+0x6DC],xmm0                       ` | record+0x6DC = element +0x1DC | [V] |
| 56815d0+rbp+0x6ec | 16 | sub_56815d0 | 0x05681BBE | `0x05681BBE  movups [rbp+0x6EC],xmm0                       ` | record+0x6EC = element +0x1EC | [V] |
| 56815d0+rbp+0x6fc | 16 | sub_56815d0 | 0x05681BCD | `0x05681BCD  movups [rbp+0x6FC],xmm0                       ` | record+0x6FC = element +0x1FC | [V] |
| 56815d0+rbp+0x70c | 16 | sub_56815d0 | 0x05681BDC | `0x05681BDC  movups [rbp+0x70C],xmm0                       ` | record+0x70C = element +0x20C | [V] |
| 56815d0+rbp+0x71c | 16 | sub_56815d0 | 0x05681BEB | `0x05681BEB  movups [rbp+0x71C],xmm0                       ` | record+0x71C = element +0x21C (last field copy) | [V] |
| 56815d0+r15-0x8c | 16 | sub_56815d0 | 0x05681BFC | `0x05681BFC  movups [r15-0x8C],xmm0                        ` | - | [V] |
| 56815d0+r15-0x6c | 16 | sub_56815d0 | 0x05681C2D | `0x05681C2D  movups [r15-0x6C],xmm1                        ` | - | [V] |
| 56815d0+r15-0x7c | 16 | sub_56815d0 | 0x05681C32 | `0x05681C32  movups [r15-0x7C],xmm0                        ` | - | [V] |
| 56815d0+rbp+0x75c | 8 | sub_56815d0 | 0x05681C56 | `0x05681C56  mov [rbp+0x75C],al                            ` | record+0x75C = [a1+0x48] byte | [V] |
| 56815d0+rbp+0x760 | 16 | sub_56815d0 | 0x05681C60 | `0x05681C60  movaps [rbp+0x760],xmm0                       ` | record+0x760 = [a1+0x4C] float4 | [V] |
| 56815d0+r15-0x16 | 16 | sub_56815d0 | 0x05681C84 | `0x05681C84  movups [r15-0x16],xmm3                        ` | - | [V] |
| 56815d0+r15-0x24 | 16 | sub_56815d0 | 0x05681C89 | `0x05681C89  movups [r15-0x24],xmm2                        ` | - | [V] |
| 56815d0+r15-0x34 | 16 | sub_56815d0 | 0x05681C8E | `0x05681C8E  movups [r15-0x34],xmm1                        ` | - | [V] |
| 56815d0+r15-0x44 | 16 | sub_56815d0 | 0x05681C93 | `0x05681C93  movups [r15-0x44],xmm0                        ` | - | [V] |
| 56815d0+rbp+0x610 | 8 | sub_56815d0 | 0x05681CA9 | `0x05681CA9  mov [rbp+0x610],rax                           ` | record+0x610 = entry count | [V] |
| 56815d0+r15+0x10 | 16 | sub_56815d0 | 0x05681CB0 | `0x05681CB0  movups [r15+0x10],xmm6                        ` | - | [V] |
| 56815d0+r15 | 16 | sub_56815d0 | 0x05681CB5 | `0x05681CB5  movups [r15],xmm6                             ` | - | [V] |
| 56815d0+call 0x9d6d0 | 5 | sub_56815d0 | 0x05681CFE | `0x05681CFE  call 0x9D6D0                                  ; -> sub_9d6d0` | - | [V] |
| 56815d0+rbp+0x7d0 | 8 | sub_56815d0 | 0x05681D10 | `0x05681D10  mov [rbp+0x7D0],rsi                           ` | string length | [V] |
| 56815d0+rbp+0x7b8 | 8 | sub_56815d0 | 0x05681D38 | `0x05681D38  mov [rbp+0x7B8],rax                           ` | record+0x7B8 = string heap pointer / record start zeroed | [V] |
| 56815d0+rbp+0x910 | 16 | sub_56815d0 | 0x05681D53, 0x056821CC | `0x05681D53  movaps [rbp+0x910],xmm6                       ` / `0x056821CC  mov [rbp+0x910],rax                           ` | record2 field zeroed | [V] |
| 56815d0+rbp+0x820 | 16 | sub_56815d0 | 0x05681D79, 0x05681E1B, 0x0568225E | `0x05681D79  movaps [rbp+0x820],xmm6                       ` / `0x05681E1B  mov [rbp+0x820],rdi                           ` / `0x0568225E  mov [rbp+0x820],rax                           ` | second string heap pointer | [V] |
| 56815d0+rdi-8 | 8 | sub_56815d0 | 0x05681DEF | `0x05681DEF  mov [rdi-8],rax                               ` | - | [V] |
| 56815d0+rbp+0x830 | 16 | sub_56815d0 | 0x05681E22, 0x05682250 | `0x05681E22  mov [rbp+0x830],rsi                           ` / `0x05682250  movups [rbp+0x830],xmm0                       ` | record2 field | [V] |
| 56815d0+rbp+0x838 | 8 | sub_56815d0 | 0x05681E29 | `0x05681E29  mov [rbp+0x838],r12                           ` | record2 field | [V] |
| 56815d0+call 0xeec6ec0 | 5 | sub_56815d0 | 0x05681E39 | `0x05681E39  call 0xEEC6EC0                                ; -> sub_eec6ec0` | - | [V] |
| 56815d0+call 0xe935700 | 5 | sub_56815d0 | 0x05681E9E, 0x0568262C, 0x056826BF, 0x0568274A, 0x056827A3, 0x056827E8, 0x05682857, 0x056828F1, 0x05682953, 0x05682998 | `0x05681E9E  call 0xE935700                                ; -> sub_e935700` / `0x0568262C  call 0xE935700                                ; -> sub_e935700` / `0x056826BF  call 0xE935700                                ; -> sub_e935700` / `0x0568274A  call 0xE935700                                ; -> sub_e935700` / `0x056827A3  call 0xE935700                                ; -> sub_e935700` / `0x056827E8  call 0xE935700                                ; -> sub_e935700` / `0x05682857  call 0xE935700                                ; -> sub_e935700` / `0x056828F1  call 0xE935700                                ; -> sub_e935700` / `0x05682953  call 0xE935700                                ; -> sub_e935700` / `0x05682998  call 0xE935700                                ; -> sub_e935700` | - | [V] |
| 56815d0+rbp+0x900 | 16 | sub_56815d0 | 0x05681EB1 | `0x05681EB1  movaps [rbp+0x900],xmm1                       ` | record2 field zeroed | [V] |
| 56815d0+rbp+0x8f0 | 16 | sub_56815d0 | 0x05681EB8 | `0x05681EB8  movaps [rbp+0x8F0],xmm0                       ` | - | [V] |
| 56815d0+rbp+0x2c0 | 16 | sub_56815d0 | 0x05681EC6 | `0x05681EC6  movaps [rbp+0x2C0],xmm1                       ` | - | [V] |
| 56815d0+rbp+0x2d0 | 16 | sub_56815d0 | 0x05681EF1 | `0x05681EF1  movaps [rbp+0x2D0],xmm0                       ` | - | [V] |
| 56815d0+rbp+0x2e0 | 8 | sub_56815d0 | 0x05681EFF | `0x05681EFF  mov [rbp+0x2E0],rax                           ` | - | [V] |
| 56815d0+rsi-0x230 | 16 | sub_56815d0 | 0x05681F0E | `0x05681F0E  movups [rsi-0x230],xmm6                       ` | - | [V] |
| 56815d0+rbp+0x300 | 8 | sub_56815d0 | 0x05681F2E | `0x05681F2E  mov [rbp+0x300],al                            ` | flag byte | [V] |
| 56815d0+rbp+0x308 | 16 | sub_56815d0 | 0x05681F60 | `0x05681F60  movups [rbp+0x308],xmm0                       ` | record+0x308 = callee output entry {a1,[a1+0]} | [V] |
| 56815d0+rbp+0x318 | 16 | sub_56815d0 | 0x05681F6E, 0x05682305 | `0x05681F6E  movups [rbp+0x318],xmm1                       ` / `0x05682305  movups [rbp+0x318],xmm6                       ` | record field zeroed | [V] |
| 56815d0+rbp+0x328 | 8 | sub_56815d0 | 0x05681F75 | `0x05681F75  mov [rbp+0x328],rax                           ` | record+0x328 = copy-dest end (dest pointer) | [V] |
| 56815d0+rsi-0x1e0 | 16 | sub_56815d0 | 0x05681F8B | `0x05681F8B  movups [rsi-0x1E0],xmm0                       ` | - | [V] |
| 56815d0+rbp+0x348 | 16 | sub_56815d0 | 0x05681FAE | `0x05681FAE  movups [rbp+0x348],xmm0                       ` | record+0x348 = element data field | [V] |
| 56815d0+rbp+0x358 | 16 | sub_56815d0 | 0x05681FB5 | `0x05681FB5  movups [rbp+0x358],xmm1                       ` | record+0x358 = element data field | [V] |
| 56815d0+rbp+0x368 | 16 | sub_56815d0 | 0x05681FBC | `0x05681FBC  movups [rbp+0x368],xmm2                       ` | record+0x368 = element data field | [V] |
| 56815d0+rbp+0x378 | 16 | sub_56815d0 | 0x05681FC3 | `0x05681FC3  movups [rbp+0x378],xmm3                       ` | record+0x378 = element data field | [V] |
| 56815d0+rbp+0x388 | 16 | sub_56815d0 | 0x05681FD1 | `0x05681FD1  movups [rbp+0x388],xmm0                       ` | record+0x388 = element data field | [V] |
| 56815d0+rbp+0x398 | 16 | sub_56815d0 | 0x05681FDF | `0x05681FDF  movups [rbp+0x398],xmm0                       ` | record+0x398 = element data field | [V] |
| 56815d0+rbp+0x3a8 | 16 | sub_56815d0 | 0x05681FED | `0x05681FED  movups [rbp+0x3A8],xmm0                       ` | record+0x3A8 = element data field | [V] |
| 56815d0+rbp+0x3b8 | 16 | sub_56815d0 | 0x05681FFB | `0x05681FFB  movups [rbp+0x3B8],xmm0                       ` | record+0x3B8 = element data field | [V] |
| 56815d0+rsi-0x140 | 8 | sub_56815d0 | 0x05682009 | `0x05682009  mov [rsi-0x140],eax                           ` | - | [V] |
| 56815d0+rsi-0x150 | 16 | sub_56815d0 | 0x05682017 | `0x05682017  movups [rsi-0x150],xmm0                       ` | - | [V] |
| 56815d0+rbp+0x3dc | 16 | sub_56815d0 | 0x0568202C | `0x0568202C  movups [rbp+0x3DC],xmm0                       ` | record+0x3DC = element data field | [V] |
| 56815d0+rbp+0x3ec | 16 | sub_56815d0 | 0x05682033 | `0x05682033  movups [rbp+0x3EC],xmm1                       ` | record+0x3EC = element data field | [V] |
| 56815d0+rbp+0x3fc | 16 | sub_56815d0 | 0x05682041 | `0x05682041  movups [rbp+0x3FC],xmm0                       ` | record+0x3FC = element data field | [V] |
| 56815d0+rbp+0x40c | 16 | sub_56815d0 | 0x0568204F | `0x0568204F  movups [rbp+0x40C],xmm0                       ` | record+0x40C = element data field | [V] |
| 56815d0+rbp+0x41c | 16 | sub_56815d0 | 0x0568205D | `0x0568205D  movups [rbp+0x41C],xmm0                       ` | record+0x41C = element data field | [V] |
| 56815d0+rbp+0x42c | 16 | sub_56815d0 | 0x0568206B | `0x0568206B  movups [rbp+0x42C],xmm0                       ` | record+0x42C = element data field | [V] |
| 56815d0+rbp+0x43c | 16 | sub_56815d0 | 0x05682079 | `0x05682079  movups [rbp+0x43C],xmm0                       ` | record+0x43C = element data field | [V] |
| 56815d0+rbp+0x44c | 16 | sub_56815d0 | 0x05682087 | `0x05682087  movups [rbp+0x44C],xmm0                       ` | record+0x44C = element data field | [V] |
| 56815d0+rsi-0xbc | 16 | sub_56815d0 | 0x05682096 | `0x05682096  movups [rsi-0xBC],xmm0                        ` | - | [V] |
| 56815d0+rsi-0x9c | 16 | sub_56815d0 | 0x056820B7 | `0x056820B7  movups [rsi-0x9C],xmm1                        ` | - | [V] |
| 56815d0+rsi-0xac | 16 | sub_56815d0 | 0x056820BE | `0x056820BE  movups [rsi-0xAC],xmm0                        ` | - | [V] |
| 56815d0+rbp+0x48c | 8 | sub_56815d0 | 0x056820DC | `0x056820DC  mov [rbp+0x48C],al                            ` | record+0x48C | [V] |
| 56815d0+rbp+0x490 | 16 | sub_56815d0 | 0x056820E9 | `0x056820E9  movaps [rbp+0x490],xmm0                       ` | record+0x490 | [V] |
| 56815d0+rsi-0x46 | 16 | sub_56815d0 | 0x0568210B | `0x0568210B  movups [rsi-0x46],xmm3                        ` | - | [V] |
| 56815d0+rsi-0x54 | 16 | sub_56815d0 | 0x0568210F | `0x0568210F  movups [rsi-0x54],xmm2                        ` | - | [V] |
| 56815d0+rsi-0x64 | 16 | sub_56815d0 | 0x05682113 | `0x05682113  movups [rsi-0x64],xmm1                        ` | - | [V] |
| 56815d0+rsi-0x74 | 16 | sub_56815d0 | 0x05682117 | `0x05682117  movups [rsi-0x74],xmm0                        ` | - | [V] |
| 56815d0+rsi-0x18 | 16 | sub_56815d0 | 0x0568213B | `0x0568213B  movups [rsi-0x18],xmm1                        ` | - | [V] |
| 56815d0+rsi-0x28 | 16 | sub_56815d0 | 0x0568213F | `0x0568213F  movups [rsi-0x28],xmm0                        ` | - | [V] |
| 56815d0+rbp+0x4e8 | 8 | sub_56815d0 | 0x05682167 | `0x05682167  mov [rbp+0x4E8],rax                           ` | record+0x4E8 = string heap pointer | [V] |
| 56815d0+rbp+0x518 | 8 | sub_56815d0 | 0x05682175 | `0x05682175  mov [rbp+0x518],rax                           ` | record2 vtable = data_f25b6a0 | [V] |
| 56815d0+rbp+0x550 | 8 | sub_56815d0 | 0x0568217C | `0x0568217C  mov [rbp+0x550],rsi                           ` | record2 field | [V] |
| 56815d0+rbp+0x918 | 8 | sub_56815d0 | 0x056821C5 | `0x056821C5  mov [rbp+0x918],rcx                           ` | record2 field | [V] |
| 56815d0+r10 | 16 | sub_56815d0 | 0x05682202 | `0x05682202  movups [r10],xmm0                             ` | - | [V] |
| 56815d0+r10+0x20 | 8 | sub_56815d0 | 0x05682211 | `0x05682211  mov [r10+0x20],r8                             ` | - | [V] |
| 56815d0+r10+0x10 | 16 | sub_56815d0 | 0x05682219 | `0x05682219  movups [r10+0x10],xmm0                        ` | - | [V] |
| 56815d0+rbp+0x828 | 8 | sub_56815d0 | 0x05682229 | `0x05682229  mov [rbp+0x828],rcx                           ` | record2 field | [V] |
| 56815d0+rbp+0x920 | 8 | sub_56815d0 | 0x05682249 | `0x05682249  mov [rbp+0x920],rcx                           ` | record2 field | [V] |
| 56815d0+rbp+0x840 | 8 | sub_56815d0 | 0x05682257 | `0x05682257  mov [rbp+0x840],rdx                           ` | record2 field | [V] |
| 56815d0+rbp-0x40 | 16 | sub_56815d0 | 0x05682277 | `0x05682277  movaps [rbp-0x40],xmm1                        ` | restore callee out-object base | [V] |
| 56815d0+rbp-0x30 | 16 | sub_56815d0 | 0x0568229F | `0x0568229F  movaps [rbp-0x30],xmm0                        ` | restore callee out-object base | [V] |
| 56815d0+rbp-0x20 | 8 | sub_56815d0 | 0x056822AA | `0x056822AA  mov [rbp-0x20],rax                            ` | restore callee out-object field | [V] |
| 56815d0+rsi-0x240 | 16 | sub_56815d0 | 0x056822AE | `0x056822AE  movups [rsi-0x240],xmm6                       ` | - | [V] |
| 56815d0+rdi-0x2a0 | 16 | sub_56815d0 | 0x056822B5 | `0x056822B5  movups [rdi-0x2A0],xmm6                       ` | - | [V] |
| 56815d0+rbp | 8 | sub_56815d0 | 0x056822D5 | `0x056822D5  mov [rbp],al                                  ` | flag byte | [V] |
| 56815d0+rbp+8 | 16 | sub_56815d0 | 0x05682301 | `0x05682301  movups [rbp+8],xmm0                           ` | record field | [V] |
| 56815d0+rbp+0x18 | 16 | sub_56815d0 | 0x0568230C | `0x0568230C  movups [rbp+0x18],xmm1                        ` | record field | [V] |
| 56815d0+rbp+0x28 | 8 | sub_56815d0 | 0x05682310 | `0x05682310  mov [rbp+0x28],rax                            ` | record field | [V] |
| 56815d0+rdi-0x250 | 16 | sub_56815d0 | 0x0568231F | `0x0568231F  movups [rdi-0x250],xmm0                       ` | - | [V] |
| 56815d0+rbp+0x48 | 16 | sub_56815d0 | 0x05682342 | `0x05682342  movups [rbp+0x48],xmm0                        ` | record field | [V] |
| 56815d0+rbp+0x58 | 16 | sub_56815d0 | 0x05682346 | `0x05682346  movups [rbp+0x58],xmm1                        ` | record field | [V] |
| 56815d0+rbp+0x68 | 16 | sub_56815d0 | 0x0568234A | `0x0568234A  movups [rbp+0x68],xmm2                        ` | record field | [V] |
| 56815d0+rbp+0x78 | 16 | sub_56815d0 | 0x0568234E | `0x0568234E  movups [rbp+0x78],xmm3                        ` | record field | [V] |
| 56815d0+rbp+0x88 | 16 | sub_56815d0 | 0x05682359 | `0x05682359  movups [rbp+0x88],xmm0                        ` | record field | [V] |
| 56815d0+rbp+0x98 | 16 | sub_56815d0 | 0x05682367 | `0x05682367  movups [rbp+0x98],xmm0                        ` | record field | [V] |
| 56815d0+rbp+0xa8 | 16 | sub_56815d0 | 0x05682375 | `0x05682375  movups [rbp+0xA8],xmm0                        ` | record field | [V] |
| 56815d0+rbp+0xb8 | 16 | sub_56815d0 | 0x05682383 | `0x05682383  movups [rbp+0xB8],xmm0                        ` | record field | [V] |
| 56815d0+rdi-0x1b0 | 8 | sub_56815d0 | 0x05682390 | `0x05682390  mov [rdi-0x1B0],eax                           ` | - | [V] |
| 56815d0+rdi-0x1c0 | 16 | sub_56815d0 | 0x0568239D | `0x0568239D  movups [rdi-0x1C0],xmm0                       ` | - | [V] |
| 56815d0+rbp+0xdc | 16 | sub_56815d0 | 0x056823B2 | `0x056823B2  movups [rbp+0xDC],xmm0                        ` | record field | [V] |
| 56815d0+rbp+0xec | 16 | sub_56815d0 | 0x056823B9 | `0x056823B9  movups [rbp+0xEC],xmm1                        ` | record field | [V] |
| 56815d0+rbp+0xfc | 16 | sub_56815d0 | 0x056823C7 | `0x056823C7  movups [rbp+0xFC],xmm0                        ` | record field | [V] |
| 56815d0+rbp+0x10c | 16 | sub_56815d0 | 0x056823D5 | `0x056823D5  movups [rbp+0x10C],xmm0                       ` | record field | [V] |
| 56815d0+rbp+0x11c | 16 | sub_56815d0 | 0x056823E3 | `0x056823E3  movups [rbp+0x11C],xmm0                       ` | record field | [V] |
| 56815d0+rbp+0x12c | 16 | sub_56815d0 | 0x056823F1 | `0x056823F1  movups [rbp+0x12C],xmm0                       ` | record field | [V] |
| 56815d0+rbp+0x13c | 16 | sub_56815d0 | 0x056823FF | `0x056823FF  movups [rbp+0x13C],xmm0                       ` | record field | [V] |
| 56815d0+rbp+0x14c | 16 | sub_56815d0 | 0x0568240D | `0x0568240D  movups [rbp+0x14C],xmm0                       ` | record field | [V] |
| 56815d0+rdi-0x12c | 16 | sub_56815d0 | 0x0568241B | `0x0568241B  movups [rdi-0x12C],xmm0                       ` | - | [V] |
| 56815d0+rdi-0x10c | 16 | sub_56815d0 | 0x05682444 | `0x05682444  movups [rdi-0x10C],xmm1                       ` | - | [V] |
| 56815d0+rdi-0x11c | 16 | sub_56815d0 | 0x0568244B | `0x0568244B  movups [rdi-0x11C],xmm0                       ` | - | [V] |
| 56815d0+rbp+0x18c | 8 | sub_56815d0 | 0x05682469 | `0x05682469  mov [rbp+0x18C],al                            ` | flag byte | [V] |
| 56815d0+rbp+0x190 | 16 | sub_56815d0 | 0x05682476 | `0x05682476  movaps [rbp+0x190],xmm0                       ` | record field | [V] |
| 56815d0+rdi-0xb6 | 16 | sub_56815d0 | 0x05682494 | `0x05682494  movups [rdi-0xB6],xmm3                        ` | - | [V] |
| 56815d0+rdi-0xc4 | 16 | sub_56815d0 | 0x0568249B | `0x0568249B  movups [rdi-0xC4],xmm2                        ` | - | [V] |
| 56815d0+rdi-0xd4 | 16 | sub_56815d0 | 0x056824A2 | `0x056824A2  movups [rdi-0xD4],xmm1                        ` | - | [V] |
| 56815d0+rdi-0xe4 | 16 | sub_56815d0 | 0x056824A9 | `0x056824A9  movups [rdi-0xE4],xmm0                        ` | - | [V] |
| 56815d0+rdi-0x88 | 16 | sub_56815d0 | 0x056824CA | `0x056824CA  movups [rdi-0x88],xmm1                        ` | - | [V] |
| 56815d0+rdi-0x98 | 16 | sub_56815d0 | 0x056824D1 | `0x056824D1  movups [rdi-0x98],xmm0                        ` | - | [V] |
| 56815d0+rbp+0x1e8 | 8 | sub_56815d0 | 0x05682503 | `0x05682503  mov [rbp+0x1E8],rax                           ` | record field | [V] |
| 56815d0+rbp+0x250 | 8 | sub_56815d0 | 0x0568251F, 0x05682544 | `0x0568251F  mov [rbp+0x250],rcx                           ` / `0x05682544  mov [rbp+0x250],rax                           ` | record field | [V] |
| 56815d0+rdi-0x18 | 16 | sub_56815d0 | 0x0568258F | `0x0568258F  movups [rdi-0x18],xmm1                        ` | - | [V] |
| 56815d0+rdi-0x28 | 16 | sub_56815d0 | 0x05682593 | `0x05682593  movups [rdi-0x28],xmm0                        ` | - | [V] |
| 56815d0+rbp+0x258 | 8 | sub_56815d0 | 0x056825BB | `0x056825BB  mov [rbp+0x258],rax                           ` | record field | [V] |
| 56815d0+rdi | 16 | sub_56815d0 | 0x056825C5 | `0x056825C5  movups [rdi],xmm0                             ` | - | [V] |
| 56815d0+rdi+0x20 | 8 | sub_56815d0 | 0x056825CC | `0x056825CC  mov [rdi+0x20],rax                            ` | - | [V] |
| 56815d0+rdi+0x10 | 16 | sub_56815d0 | 0x056825D4 | `0x056825D4  movups [rdi+0x10],xmm0                        ` | - | [V] |
| 56815d0+call 0x568b0d0 | 5 | sub_56815d0 | 0x056825E6 | `0x056825E6  call 0x568B0D0                                ; -> sub_568b0d0` | - | [V] |
| 56815d0+rdi-0x270 | 16 | sub_56815d0 | 0x056826EE | `0x056826EE  movups [rdi-0x270],xmm6                       ` | - | [V] |
| 56815d0+rsi-0x200 | 16 | sub_56815d0 | 0x0568288C | `0x0568288C  movups [rsi-0x200],xmm6                       ` | - | [V] |
| 56815d0+call 0x9bc830 | 5 | sub_56815d0 | 0x056829F0, 0x056829FE | `0x056829F0  call 0x9BC830                                 ; -> sub_9bc830` / `0x056829FE  call 0x9BC830                                 ; -> sub_9bc830` | - | [V] |
| 56815d0+call 0x78ed0 | 5 | sub_56815d0 | 0x05682A79 | `0x05682A79  call 0x78ED0                                  ; -> sub_78ed0` | - | [V] |
| 56815d0+0xf9a8c78 | 5 | sub_56815d0 | 0x05682A91 | `0x05682A91  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]` | - | [V] |
| 56815d0+call 0x75720 | 5 | sub_56815d0 | 0x05682A98 | `0x05682A98  call 0x75720                                  ; -> sub_75720` | sub_75720 | [V] |
| 56815d0+call 0x75b60 | 5 | sub_56815d0 | 0x05682A9E | `0x05682A9E  call 0x75B60                                  ; -> sub_75b60` | - | [V] |
| 56815d0+rsp+0x10 | 8 | sub_56815d0 | 0x05682AB0, 0x05682B20, 0x05682BA0, 0x05682C30, 0x05682CA0, 0x05682D00, 0x05682D50, 0x05682DA0, 0x05682DD0 | `0x05682AB0  mov [rsp+0x10],rdx                            ` / `0x05682B20  mov [rsp+0x10],rdx                            ` / `0x05682BA0  mov [rsp+0x10],rdx                            ` / `0x05682C30  mov [rsp+0x10],rdx                            ` / `0x05682CA0  mov [rsp+0x10],rdx                            ` / `0x05682D00  mov [rsp+0x10],rdx                            ` / `0x05682D50  mov [rsp+0x10],rdx                            ` / `0x05682DA0  mov [rsp+0x10],rdx                            ` / `0x05682DD0  mov [rsp+0x10],rdx                            ` | - | [V] |
| 56815d0+rsp+0x30 | 16 | sub_56815d0 | 0x05682AD1, 0x05682B41, 0x05682BC1, 0x05682C51, 0x05682CC1, 0x05682D21, 0x05682D71, 0x05682DC1, 0x05682DF1 | `0x05682AD1  movaps [rsp+0x30],xmm6                        ` / `0x05682B41  movaps [rsp+0x30],xmm6                        ` / `0x05682BC1  movaps [rsp+0x30],xmm6                        ` / `0x05682C51  movaps [rsp+0x30],xmm6                        ` / `0x05682CC1  movaps [rsp+0x30],xmm6                        ` / `0x05682D21  movaps [rsp+0x30],xmm6                        ` / `0x05682D71  movaps [rsp+0x30],xmm6                        ` / `0x05682DC1  movaps [rsp+0x30],xmm6                        ` / `0x05682DF1  movaps [rsp+0x30],xmm6                        ` | - | [V] |
| 56815d0+rax-0x1d0 | 16 | sub_56815d0 | 0x05682B63, 0x05682BEF | `0x05682B63  movups [rax-0x1D0],xmm0                       ` / `0x05682BEF  movups [rax-0x1D0],xmm0                       ` | - | [V] |
| 56815d0+call 0x73150 | 5 | sub_56815d0 | 0x05682BCD, 0x05682CD9, 0x05682DFD | `0x05682BCD  call 0x73150                                  ; -> sub_73150` / `0x05682CD9  call 0x73150                                  ; -> sub_73150` / `0x05682DFD  call 0x73150                                  ; -> sub_73150` | sub_73150 | [V] |
| 56815d0+call 0x568ae30 | 5 | sub_56815d0 | 0x05682C5A | `0x05682C5A  call 0x568AE30                                ; -> sub_568ae30` | - | [V] |
| 56815d0+call 0x81cb0 | 5 | sub_56815d0 | 0x05682C66, 0x05682C72, 0x05682C7E, 0x05682D7D | `0x05682C66  call 0x81CB0                                  ; -> sub_81cb0` / `0x05682C72  call 0x81CB0                                  ; -> sub_81cb0` / `0x05682C7E  call 0x81CB0                                  ; -> sub_81cb0` / `0x05682D7D  call 0x81CB0                                  ; -> sub_81cb0` | - | [V] |
| 56815d0+call 0x568aed0 | 5 | sub_56815d0 | 0x05682CCD | `0x05682CCD  call 0x568AED0                                ; -> sub_568aed0` | - | [V] |
| 56815d0+call 0x568b010 | 5 | sub_56815d0 | 0x05682D2D | `0x05682D2D  call 0x568B010                                ; -> sub_568b010` | - | [V] |
| 56815d0+call 0xeec6e40 | 5 | sub_56815d0 | 0x05682DC6 | `0x05682DC6  call 0xEEC6E40                                ; -> sub_eec6e40` | - | [V] |


### sub_5682e20 (data_f25b610) — per-element fill / dest writes [V]

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 5682e20+rbp+0x560 | 8 | sub_5682e20 | 0x05682EF5 | `0x05682EF5  mov [rbp+0x560],rax                           ` | block header+0 = vtable ptr | [V] |
| 5682e20+rbp+0x568 | 8 | sub_5682e20 | 0x05682EFC | `0x05682EFC  mov [rbp+0x568],rsi                           ` | block header+8 = element data base (cursor+0x240) | [V] |
| 5682e20+rbp+0x598 | 8 | sub_5682e20 | 0x05682F0A | `0x05682F0A  mov [rbp+0x598],rax                           ` | block pointer = &[rbp+0x560] | [V] |
| 5682e20+rbp-0x50 | 16 | sub_5682e20 | 0x05682F97, 0x05683AB3 | `0x05682F97  mov [rbp-0x50],r15                            ` / `0x05683AB3  movaps [rbp-0x50],xmm0                        ` | callee out-object addr = element ptr (saved) | [V] |
| 5682e20+rbp-0x48 | 8 | sub_5682e20 | 0x05682F9B | `0x05682F9B  mov [rbp-0x48],r13                            ` | saved node pointer | [V] |
| 5682e20+0xf99ffa0 | 5 | sub_5682e20 | 0x05682FAA, 0x05682FE6, 0x05683296, 0x056832AC, 0x05683611, 0x05683648, 0x05683D7E, 0x05683DA4, 0x05683EAE, 0x05684046, 0x05684336 | `0x05682FAA  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05682FE6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05683296  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056832AC  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05683611  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05683648  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05683D7E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05683DA4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05683EAE  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05684046  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05684336  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | - | [V] |
| 5682e20+rbp+0x2b0 | 16 | sub_5682e20 | 0x05683044, 0x05683077, 0x056830B1, 0x056836FF | `0x05683044  mov [rbp+0x2B0],rsi                           ` / `0x05683077  mov [rbp+0x2B0],rsi                           ` / `0x056830B1  mov [rbp+0x2B0],r14                           ` / `0x056836FF  movaps [rbp+0x2B0],xmm0                       ` | element data base local / scratch | [V] |
| 5682e20+rsp+0x20 | 16 | sub_5682e20 | 0x05683060, 0x05683093, 0x056830CD, 0x0568430C, 0x0568437C, 0x056843FC, 0x0568448C, 0x056844FC, 0x0568455C, 0x056845AC, 0x056845FC, 0x0568462C | `0x05683060  mov [rsp+0x20],rax                            ` / `0x05683093  mov [rsp+0x20],rax                            ` / `0x056830CD  mov [rsp+0x20],rax                            ` / `0x0568430C  movaps [rsp+0x20],xmm7                        ` / `0x0568437C  movaps [rsp+0x20],xmm7                        ` / `0x056843FC  movaps [rsp+0x20],xmm7                        ` / `0x0568448C  movaps [rsp+0x20],xmm7                        ` / `0x056844FC  movaps [rsp+0x20],xmm7                        ` / `0x0568455C  movaps [rsp+0x20],xmm7                        ` / `0x056845AC  movaps [rsp+0x20],xmm7                        ` / `0x056845FC  movaps [rsp+0x20],xmm7                        ` / `0x0568462C  movaps [rsp+0x20],xmm7                        ` | r9 home slot | [V] |
| 5682e20+call 0x568fa60 | 5 | sub_5682e20 | 0x05683070 | `0x05683070  call 0x568FA60                                ; -> sub_568fa60` | - | [V] |
| 5682e20+call 0x568ff10 | 5 | sub_5682e20 | 0x056830A3 | `0x056830A3  call 0x568FF10                                ; -> sub_568ff10` | - | [V] |
| 5682e20+rbp+0x5a0 | 8 | sub_5682e20 | 0x056830AA, 0x056831AD | `0x056830AA  mov [rbp+0x5A0],rsi                           ` / `0x056831AD  mov [rbp+0x5A0],rax                           ` | record+0 = element field / callee out result | [V] |
| 5682e20+call 0x56903d0 | 5 | sub_5682e20 | 0x056830DD | `0x056830DD  call 0x56903D0                                ; -> sub_56903d0` | - | [V] |
| 5682e20+rbp+0x8c8 | 8 | sub_5682e20 | 0x056830EE | `0x056830EE  mov [rbp+0x8C8],rax                           ` | callee out-object end (+0x18) | [V] |
| 5682e20+rbp+0x950 | 8 | sub_5682e20 | 0x056830FF | `0x056830FF  mov [rbp+0x950],rax                           ` | copy byte count | [V] |
| 5682e20+rbp+0x8c0 | 8 | sub_5682e20 | 0x0568311B | `0x0568311B  mov [rbp+0x8C0],rcx                           ` | entry count | [V] |
| 5682e20+call 0x76a8a0 | 5 | sub_5682e20 | 0x05683130, 0x056839CD | `0x05683130  call 0x76A8A0                                 ; -> sub_76a8a0` / `0x056839CD  call 0x76A8A0                                 ; -> sub_76a8a0` | - | [V] |
| 5682e20+rbp+0x8b0 | 8 | sub_5682e20 | 0x05683138 | `0x05683138  mov [rbp+0x8B0],rdi                           ` | slot+0 | [V] |
| 5682e20+rbp+0x948 | 8 | sub_5682e20 | 0x0568313F | `0x0568313F  mov [rbp+0x948],rsi                           ` | slot+8 | [V] |
| 5682e20+call 0x655cea0 | 5 | sub_5682e20 | 0x0568316D, 0x05683F44, 0x056840E5, 0x056843BC, 0x05684448 | `0x0568316D  call 0x655CEA0                                ; -> sub_655cea0` / `0x05683F44  call 0x655CEA0                                ; -> sub_655cea0` / `0x056840E5  call 0x655CEA0                                ; -> sub_655cea0` / `0x056843BC  call 0x655CEA0                                ; -> sub_655cea0` / `0x05684448  call 0x655CEA0                                ; -> sub_655cea0` | - | [V] |
| 5682e20+r15-0x210 | 16 | sub_5682e20 | 0x056831B4, 0x05683746 | `0x056831B4  movups [r15-0x210],xmm6                       ` / `0x05683746  movups [r15-0x210],xmm6                       ` | - | [V] |
| 5682e20+rbp+0x940 | 8 | sub_5682e20 | 0x056831C6 | `0x056831C6  mov [rbp+0x940],rcx                           ` | - | [V] |
| 5682e20+rbp+0x5a8 | 8 | sub_5682e20 | 0x056831E9 | `0x056831E9  mov [rbp+0x5A8],rcx                           ` | record+8 = element object [elem+0x268] | [V] |
| 5682e20+rbp+0x5b0 | 8 | sub_5682e20 | 0x056831F0 | `0x056831F0  mov [rbp+0x5B0],rax                           ` | record+0x10 = element object [elem+0x260] | [V] |
| 5682e20+r15-0x200 | 16 | sub_5682e20 | 0x056831F7 | `0x056831F7  movups [r15-0x200],xmm6                       ` | - | [V] |
| 5682e20+rbp+0x5d8 | 16 | sub_5682e20 | 0x05683218 | `0x05683218  movups [rbp+0x5D8],xmm7                       ` | record+0x5D8 = callee output entry {a1,[a1+0]} | [V] |
| 5682e20+r15-0x1d0 | 16 | sub_5682e20 | 0x0568321F, 0x05684215 | `0x0568321F  movups [r15-0x1D0],xmm6                       ` / `0x05684215  movups [r15-0x1D0],xmm6                       ` | - | [V] |
| 5682e20+call 0xa78940 | 5 | sub_5682e20 | 0x0568326D | `0x0568326D  call 0xA78940                                 ; -> sub_a78940` | - | [V] |
| 5682e20+rbp+0x5e8 | 16 | sub_5682e20 | 0x056832C3, 0x056837A7 | `0x056832C3  mov [rbp+0x5E8],rsi                           ` / `0x056837A7  movups [rbp+0x5E8],xmm6                       ` | record+0x5E8 = callee-output copy dest start | [V] |
| 5682e20+rbp+0x5f0 | 8 | sub_5682e20 | 0x056832CA, 0x056832F5 | `0x056832CA  mov [rbp+0x5F0],rsi                           ` / `0x056832F5  mov [rbp+0x5F0],rdi                           ` | record+0x5F0 = copy cursor / copy end | [V] |
| 5682e20+rbp+0x5f8 | 8 | sub_5682e20 | 0x056832DC | `0x056832DC  mov [rbp+0x5F8],rdi                           ` | record+0x5F8 = callee-output copy dest end | [V] |
| 5682e20+call 0xeec6de0 | 5 | sub_5682e20 | 0x056832F0, 0x05683564 | `0x056832F0  call 0xEEC6DE0                                ; -> sub_eec6de0` / `0x05683564  call 0xEEC6DE0                                ; -> sub_eec6de0` | - | [V] |
| 5682e20+rbp+0x608 | 8 | sub_5682e20 | 0x0568331F | `0x0568331F  mov [rbp+0x608],rax                           ` | record+0x608 = entry count | [V] |
| 5682e20+rbp+0x618 | 16 | sub_5682e20 | 0x0568332E | `0x0568332E  movups [rbp+0x618],xmm0                       ` | record+0x618 = element data [elem+0x118] | [V] |
| 5682e20+rbp+0x628 | 16 | sub_5682e20 | 0x0568333D | `0x0568333D  movups [rbp+0x628],xmm0                       ` | record+0x628 = element data [elem+0x128] | [V] |
| 5682e20+rbp+0x638 | 16 | sub_5682e20 | 0x0568334C | `0x0568334C  movups [rbp+0x638],xmm0                       ` | record+0x638 = element data [elem+0x138] | [V] |
| 5682e20+rbp+0x648 | 16 | sub_5682e20 | 0x0568335B | `0x0568335B  movups [rbp+0x648],xmm0                       ` | record+0x648 = element data [elem+0x148] | [V] |
| 5682e20+rbp+0x658 | 16 | sub_5682e20 | 0x0568336A | `0x0568336A  movups [rbp+0x658],xmm0                       ` | record+0x658 = element data [elem+0x158] | [V] |
| 5682e20+rbp+0x668 | 16 | sub_5682e20 | 0x05683379 | `0x05683379  movups [rbp+0x668],xmm0                       ` | record+0x668 = element data [elem+0x168] | [V] |
| 5682e20+rbp+0x678 | 16 | sub_5682e20 | 0x05683388 | `0x05683388  movups [rbp+0x678],xmm0                       ` | record+0x678 = element data [elem+0x178] | [V] |
| 5682e20+rbp+0x688 | 16 | sub_5682e20 | 0x05683397 | `0x05683397  movups [rbp+0x688],xmm0                       ` | record+0x688 = element data [elem+0x188] | [V] |
| 5682e20+r15-0x110 | 8 | sub_5682e20 | 0x056833A8 | `0x056833A8  mov [r15-0x110],eax                           ` | - | [V] |
| 5682e20+r15-0x120 | 16 | sub_5682e20 | 0x056833B2 | `0x056833B2  movups [r15-0x120],xmm0                       ` | - | [V] |
| 5682e20+rbp+0x6ac | 16 | sub_5682e20 | 0x056833C2 | `0x056833C2  movups [rbp+0x6AC],xmm0                       ` | record+0x6AC = element +0x1AC | [V] |
| 5682e20+rbp+0x6bc | 16 | sub_5682e20 | 0x056833D1 | `0x056833D1  movups [rbp+0x6BC],xmm0                       ` | record+0x6BC = element +0x1BC | [V] |
| 5682e20+rbp+0x6cc | 16 | sub_5682e20 | 0x056833E0 | `0x056833E0  movups [rbp+0x6CC],xmm0                       ` | record+0x6CC = element +0x1CC | [V] |
| 5682e20+rbp+0x6dc | 16 | sub_5682e20 | 0x056833EF | `0x056833EF  movups [rbp+0x6DC],xmm0                       ` | record+0x6DC = element +0x1DC | [V] |
| 5682e20+rbp+0x6ec | 16 | sub_5682e20 | 0x056833FE | `0x056833FE  movups [rbp+0x6EC],xmm0                       ` | record+0x6EC = element +0x1EC | [V] |
| 5682e20+rbp+0x6fc | 16 | sub_5682e20 | 0x0568340D | `0x0568340D  movups [rbp+0x6FC],xmm0                       ` | record+0x6FC = element +0x1FC | [V] |
| 5682e20+rbp+0x70c | 16 | sub_5682e20 | 0x0568341C | `0x0568341C  movups [rbp+0x70C],xmm0                       ` | record+0x70C = element +0x20C | [V] |
| 5682e20+rbp+0x71c | 16 | sub_5682e20 | 0x0568342B | `0x0568342B  movups [rbp+0x71C],xmm0                       ` | record+0x71C = element +0x21C (last field copy) | [V] |
| 5682e20+r15-0x8c | 16 | sub_5682e20 | 0x0568343C | `0x0568343C  movups [r15-0x8C],xmm0                        ` | - | [V] |
| 5682e20+r15-0x6c | 16 | sub_5682e20 | 0x0568346D | `0x0568346D  movups [r15-0x6C],xmm1                        ` | - | [V] |
| 5682e20+r15-0x7c | 16 | sub_5682e20 | 0x05683472 | `0x05683472  movups [r15-0x7C],xmm0                        ` | - | [V] |
| 5682e20+rbp+0x75c | 8 | sub_5682e20 | 0x05683496 | `0x05683496  mov [rbp+0x75C],al                            ` | record+0x75C = [a1+0x48] byte | [V] |
| 5682e20+rbp+0x760 | 16 | sub_5682e20 | 0x056834A0 | `0x056834A0  movaps [rbp+0x760],xmm0                       ` | record+0x760 = [a1+0x4C] float4 | [V] |
| 5682e20+r15-0x16 | 16 | sub_5682e20 | 0x056834C4 | `0x056834C4  movups [r15-0x16],xmm3                        ` | - | [V] |
| 5682e20+r15-0x24 | 16 | sub_5682e20 | 0x056834C9 | `0x056834C9  movups [r15-0x24],xmm2                        ` | - | [V] |
| 5682e20+r15-0x34 | 16 | sub_5682e20 | 0x056834CE | `0x056834CE  movups [r15-0x34],xmm1                        ` | - | [V] |
| 5682e20+r15-0x44 | 16 | sub_5682e20 | 0x056834D3 | `0x056834D3  movups [r15-0x44],xmm0                        ` | - | [V] |
| 5682e20+rbp+0x610 | 8 | sub_5682e20 | 0x056834E9 | `0x056834E9  mov [rbp+0x610],rax                           ` | record+0x610 = entry count | [V] |
| 5682e20+r15+0x10 | 16 | sub_5682e20 | 0x056834F0 | `0x056834F0  movups [r15+0x10],xmm6                        ` | - | [V] |
| 5682e20+r15 | 16 | sub_5682e20 | 0x056834F5 | `0x056834F5  movups [r15],xmm6                             ` | - | [V] |
| 5682e20+call 0x9d6d0 | 5 | sub_5682e20 | 0x0568353E | `0x0568353E  call 0x9D6D0                                  ; -> sub_9d6d0` | - | [V] |
| 5682e20+rbp+0x7d0 | 8 | sub_5682e20 | 0x05683550 | `0x05683550  mov [rbp+0x7D0],rsi                           ` | string length | [V] |
| 5682e20+rbp+0x7b8 | 8 | sub_5682e20 | 0x05683578 | `0x05683578  mov [rbp+0x7B8],rax                           ` | record+0x7B8 = string heap pointer / record start zeroed | [V] |
| 5682e20+rbp+0x910 | 16 | sub_5682e20 | 0x05683593, 0x05683A0C | `0x05683593  movaps [rbp+0x910],xmm6                       ` / `0x05683A0C  mov [rbp+0x910],rax                           ` | record2 field zeroed | [V] |
| 5682e20+rbp+0x820 | 16 | sub_5682e20 | 0x056835B9, 0x0568365B, 0x05683A9E | `0x056835B9  movaps [rbp+0x820],xmm6                       ` / `0x0568365B  mov [rbp+0x820],rdi                           ` / `0x05683A9E  mov [rbp+0x820],rax                           ` | second string heap pointer | [V] |
| 5682e20+rdi-8 | 8 | sub_5682e20 | 0x0568362F | `0x0568362F  mov [rdi-8],rax                               ` | - | [V] |
| 5682e20+rbp+0x830 | 16 | sub_5682e20 | 0x05683662, 0x05683A90 | `0x05683662  mov [rbp+0x830],rsi                           ` / `0x05683A90  movups [rbp+0x830],xmm0                       ` | record2 field | [V] |
| 5682e20+rbp+0x838 | 8 | sub_5682e20 | 0x05683669 | `0x05683669  mov [rbp+0x838],r12                           ` | record2 field | [V] |
| 5682e20+call 0xeec6ec0 | 5 | sub_5682e20 | 0x05683679 | `0x05683679  call 0xEEC6EC0                                ; -> sub_eec6ec0` | - | [V] |
| 5682e20+call 0xe935700 | 5 | sub_5682e20 | 0x056836DE, 0x05683E6C, 0x05683EFF, 0x05683F8A, 0x05683FE3, 0x05684028, 0x05684097, 0x05684131, 0x05684193, 0x056841D8 | `0x056836DE  call 0xE935700                                ; -> sub_e935700` / `0x05683E6C  call 0xE935700                                ; -> sub_e935700` / `0x05683EFF  call 0xE935700                                ; -> sub_e935700` / `0x05683F8A  call 0xE935700                                ; -> sub_e935700` / `0x05683FE3  call 0xE935700                                ; -> sub_e935700` / `0x05684028  call 0xE935700                                ; -> sub_e935700` / `0x05684097  call 0xE935700                                ; -> sub_e935700` / `0x05684131  call 0xE935700                                ; -> sub_e935700` / `0x05684193  call 0xE935700                                ; -> sub_e935700` / `0x056841D8  call 0xE935700                                ; -> sub_e935700` | - | [V] |
| 5682e20+rbp+0x900 | 16 | sub_5682e20 | 0x056836F1 | `0x056836F1  movaps [rbp+0x900],xmm1                       ` | record2 field zeroed | [V] |
| 5682e20+rbp+0x8f0 | 16 | sub_5682e20 | 0x056836F8 | `0x056836F8  movaps [rbp+0x8F0],xmm0                       ` | - | [V] |
| 5682e20+rbp+0x2c0 | 16 | sub_5682e20 | 0x05683706 | `0x05683706  movaps [rbp+0x2C0],xmm1                       ` | - | [V] |
| 5682e20+rbp+0x2d0 | 16 | sub_5682e20 | 0x05683731 | `0x05683731  movaps [rbp+0x2D0],xmm0                       ` | - | [V] |
| 5682e20+rbp+0x2e0 | 8 | sub_5682e20 | 0x0568373F | `0x0568373F  mov [rbp+0x2E0],rax                           ` | - | [V] |
| 5682e20+rsi-0x230 | 16 | sub_5682e20 | 0x0568374E | `0x0568374E  movups [rsi-0x230],xmm6                       ` | - | [V] |
| 5682e20+rbp+0x300 | 8 | sub_5682e20 | 0x0568376E | `0x0568376E  mov [rbp+0x300],al                            ` | flag byte | [V] |
| 5682e20+rbp+0x308 | 16 | sub_5682e20 | 0x056837A0 | `0x056837A0  movups [rbp+0x308],xmm0                       ` | record+0x308 = callee output entry {a1,[a1+0]} | [V] |
| 5682e20+rbp+0x318 | 16 | sub_5682e20 | 0x056837AE, 0x05683B45 | `0x056837AE  movups [rbp+0x318],xmm1                       ` / `0x05683B45  movups [rbp+0x318],xmm6                       ` | record field zeroed | [V] |
| 5682e20+rbp+0x328 | 8 | sub_5682e20 | 0x056837B5 | `0x056837B5  mov [rbp+0x328],rax                           ` | record+0x328 = copy-dest end (dest pointer) | [V] |
| 5682e20+rsi-0x1e0 | 16 | sub_5682e20 | 0x056837CB | `0x056837CB  movups [rsi-0x1E0],xmm0                       ` | - | [V] |
| 5682e20+rbp+0x348 | 16 | sub_5682e20 | 0x056837EE | `0x056837EE  movups [rbp+0x348],xmm0                       ` | record+0x348 = element data field | [V] |
| 5682e20+rbp+0x358 | 16 | sub_5682e20 | 0x056837F5 | `0x056837F5  movups [rbp+0x358],xmm1                       ` | record+0x358 = element data field | [V] |
| 5682e20+rbp+0x368 | 16 | sub_5682e20 | 0x056837FC | `0x056837FC  movups [rbp+0x368],xmm2                       ` | record+0x368 = element data field | [V] |
| 5682e20+rbp+0x378 | 16 | sub_5682e20 | 0x05683803 | `0x05683803  movups [rbp+0x378],xmm3                       ` | record+0x378 = element data field | [V] |
| 5682e20+rbp+0x388 | 16 | sub_5682e20 | 0x05683811 | `0x05683811  movups [rbp+0x388],xmm0                       ` | record+0x388 = element data field | [V] |
| 5682e20+rbp+0x398 | 16 | sub_5682e20 | 0x0568381F | `0x0568381F  movups [rbp+0x398],xmm0                       ` | record+0x398 = element data field | [V] |
| 5682e20+rbp+0x3a8 | 16 | sub_5682e20 | 0x0568382D | `0x0568382D  movups [rbp+0x3A8],xmm0                       ` | record+0x3A8 = element data field | [V] |
| 5682e20+rbp+0x3b8 | 16 | sub_5682e20 | 0x0568383B | `0x0568383B  movups [rbp+0x3B8],xmm0                       ` | record+0x3B8 = element data field | [V] |
| 5682e20+rsi-0x140 | 8 | sub_5682e20 | 0x05683849 | `0x05683849  mov [rsi-0x140],eax                           ` | - | [V] |
| 5682e20+rsi-0x150 | 16 | sub_5682e20 | 0x05683857 | `0x05683857  movups [rsi-0x150],xmm0                       ` | - | [V] |
| 5682e20+rbp+0x3dc | 16 | sub_5682e20 | 0x0568386C | `0x0568386C  movups [rbp+0x3DC],xmm0                       ` | record+0x3DC = element data field | [V] |
| 5682e20+rbp+0x3ec | 16 | sub_5682e20 | 0x05683873 | `0x05683873  movups [rbp+0x3EC],xmm1                       ` | record+0x3EC = element data field | [V] |
| 5682e20+rbp+0x3fc | 16 | sub_5682e20 | 0x05683881 | `0x05683881  movups [rbp+0x3FC],xmm0                       ` | record+0x3FC = element data field | [V] |
| 5682e20+rbp+0x40c | 16 | sub_5682e20 | 0x0568388F | `0x0568388F  movups [rbp+0x40C],xmm0                       ` | record+0x40C = element data field | [V] |
| 5682e20+rbp+0x41c | 16 | sub_5682e20 | 0x0568389D | `0x0568389D  movups [rbp+0x41C],xmm0                       ` | record+0x41C = element data field | [V] |
| 5682e20+rbp+0x42c | 16 | sub_5682e20 | 0x056838AB | `0x056838AB  movups [rbp+0x42C],xmm0                       ` | record+0x42C = element data field | [V] |
| 5682e20+rbp+0x43c | 16 | sub_5682e20 | 0x056838B9 | `0x056838B9  movups [rbp+0x43C],xmm0                       ` | record+0x43C = element data field | [V] |
| 5682e20+rbp+0x44c | 16 | sub_5682e20 | 0x056838C7 | `0x056838C7  movups [rbp+0x44C],xmm0                       ` | record+0x44C = element data field | [V] |
| 5682e20+rsi-0xbc | 16 | sub_5682e20 | 0x056838D6 | `0x056838D6  movups [rsi-0xBC],xmm0                        ` | - | [V] |
| 5682e20+rsi-0x9c | 16 | sub_5682e20 | 0x056838F7 | `0x056838F7  movups [rsi-0x9C],xmm1                        ` | - | [V] |
| 5682e20+rsi-0xac | 16 | sub_5682e20 | 0x056838FE | `0x056838FE  movups [rsi-0xAC],xmm0                        ` | - | [V] |
| 5682e20+rbp+0x48c | 8 | sub_5682e20 | 0x0568391C | `0x0568391C  mov [rbp+0x48C],al                            ` | record+0x48C | [V] |
| 5682e20+rbp+0x490 | 16 | sub_5682e20 | 0x05683929 | `0x05683929  movaps [rbp+0x490],xmm0                       ` | record+0x490 | [V] |
| 5682e20+rsi-0x46 | 16 | sub_5682e20 | 0x0568394B | `0x0568394B  movups [rsi-0x46],xmm3                        ` | - | [V] |
| 5682e20+rsi-0x54 | 16 | sub_5682e20 | 0x0568394F | `0x0568394F  movups [rsi-0x54],xmm2                        ` | - | [V] |
| 5682e20+rsi-0x64 | 16 | sub_5682e20 | 0x05683953 | `0x05683953  movups [rsi-0x64],xmm1                        ` | - | [V] |
| 5682e20+rsi-0x74 | 16 | sub_5682e20 | 0x05683957 | `0x05683957  movups [rsi-0x74],xmm0                        ` | - | [V] |
| 5682e20+rsi-0x18 | 16 | sub_5682e20 | 0x0568397B | `0x0568397B  movups [rsi-0x18],xmm1                        ` | - | [V] |
| 5682e20+rsi-0x28 | 16 | sub_5682e20 | 0x0568397F | `0x0568397F  movups [rsi-0x28],xmm0                        ` | - | [V] |
| 5682e20+rbp+0x4e8 | 8 | sub_5682e20 | 0x056839A7 | `0x056839A7  mov [rbp+0x4E8],rax                           ` | record+0x4E8 = string heap pointer | [V] |
| 5682e20+rbp+0x518 | 8 | sub_5682e20 | 0x056839B5 | `0x056839B5  mov [rbp+0x518],rax                           ` | record2 vtable = data_f25b6a0 | [V] |
| 5682e20+rbp+0x550 | 8 | sub_5682e20 | 0x056839BC | `0x056839BC  mov [rbp+0x550],rsi                           ` | record2 field | [V] |
| 5682e20+rbp+0x918 | 8 | sub_5682e20 | 0x05683A05 | `0x05683A05  mov [rbp+0x918],rcx                           ` | record2 field | [V] |
| 5682e20+r10 | 16 | sub_5682e20 | 0x05683A42 | `0x05683A42  movups [r10],xmm0                             ` | - | [V] |
| 5682e20+r10+0x20 | 8 | sub_5682e20 | 0x05683A51 | `0x05683A51  mov [r10+0x20],r8                             ` | - | [V] |
| 5682e20+r10+0x10 | 16 | sub_5682e20 | 0x05683A59 | `0x05683A59  movups [r10+0x10],xmm0                        ` | - | [V] |
| 5682e20+rbp+0x828 | 8 | sub_5682e20 | 0x05683A69 | `0x05683A69  mov [rbp+0x828],rcx                           ` | record2 field | [V] |
| 5682e20+rbp+0x920 | 8 | sub_5682e20 | 0x05683A89 | `0x05683A89  mov [rbp+0x920],rcx                           ` | record2 field | [V] |
| 5682e20+rbp+0x840 | 8 | sub_5682e20 | 0x05683A97 | `0x05683A97  mov [rbp+0x840],rdx                           ` | record2 field | [V] |
| 5682e20+rbp-0x40 | 16 | sub_5682e20 | 0x05683AB7 | `0x05683AB7  movaps [rbp-0x40],xmm1                        ` | restore callee out-object base | [V] |
| 5682e20+rbp-0x30 | 16 | sub_5682e20 | 0x05683ADF | `0x05683ADF  movaps [rbp-0x30],xmm0                        ` | restore callee out-object base | [V] |
| 5682e20+rbp-0x20 | 8 | sub_5682e20 | 0x05683AEA | `0x05683AEA  mov [rbp-0x20],rax                            ` | restore callee out-object field | [V] |
| 5682e20+rsi-0x240 | 16 | sub_5682e20 | 0x05683AEE | `0x05683AEE  movups [rsi-0x240],xmm6                       ` | - | [V] |
| 5682e20+rdi-0x2a0 | 16 | sub_5682e20 | 0x05683AF5 | `0x05683AF5  movups [rdi-0x2A0],xmm6                       ` | - | [V] |
| 5682e20+rbp | 8 | sub_5682e20 | 0x05683B15 | `0x05683B15  mov [rbp],al                                  ` | flag byte | [V] |
| 5682e20+rbp+8 | 16 | sub_5682e20 | 0x05683B41 | `0x05683B41  movups [rbp+8],xmm0                           ` | record field | [V] |
| 5682e20+rbp+0x18 | 16 | sub_5682e20 | 0x05683B4C | `0x05683B4C  movups [rbp+0x18],xmm1                        ` | record field | [V] |
| 5682e20+rbp+0x28 | 8 | sub_5682e20 | 0x05683B50 | `0x05683B50  mov [rbp+0x28],rax                            ` | record field | [V] |
| 5682e20+rdi-0x250 | 16 | sub_5682e20 | 0x05683B5F | `0x05683B5F  movups [rdi-0x250],xmm0                       ` | - | [V] |
| 5682e20+rbp+0x48 | 16 | sub_5682e20 | 0x05683B82 | `0x05683B82  movups [rbp+0x48],xmm0                        ` | record field | [V] |
| 5682e20+rbp+0x58 | 16 | sub_5682e20 | 0x05683B86 | `0x05683B86  movups [rbp+0x58],xmm1                        ` | record field | [V] |
| 5682e20+rbp+0x68 | 16 | sub_5682e20 | 0x05683B8A | `0x05683B8A  movups [rbp+0x68],xmm2                        ` | record field | [V] |
| 5682e20+rbp+0x78 | 16 | sub_5682e20 | 0x05683B8E | `0x05683B8E  movups [rbp+0x78],xmm3                        ` | record field | [V] |
| 5682e20+rbp+0x88 | 16 | sub_5682e20 | 0x05683B99 | `0x05683B99  movups [rbp+0x88],xmm0                        ` | record field | [V] |
| 5682e20+rbp+0x98 | 16 | sub_5682e20 | 0x05683BA7 | `0x05683BA7  movups [rbp+0x98],xmm0                        ` | record field | [V] |
| 5682e20+rbp+0xa8 | 16 | sub_5682e20 | 0x05683BB5 | `0x05683BB5  movups [rbp+0xA8],xmm0                        ` | record field | [V] |
| 5682e20+rbp+0xb8 | 16 | sub_5682e20 | 0x05683BC3 | `0x05683BC3  movups [rbp+0xB8],xmm0                        ` | record field | [V] |
| 5682e20+rdi-0x1b0 | 8 | sub_5682e20 | 0x05683BD0 | `0x05683BD0  mov [rdi-0x1B0],eax                           ` | - | [V] |
| 5682e20+rdi-0x1c0 | 16 | sub_5682e20 | 0x05683BDD | `0x05683BDD  movups [rdi-0x1C0],xmm0                       ` | - | [V] |
| 5682e20+rbp+0xdc | 16 | sub_5682e20 | 0x05683BF2 | `0x05683BF2  movups [rbp+0xDC],xmm0                        ` | record field | [V] |
| 5682e20+rbp+0xec | 16 | sub_5682e20 | 0x05683BF9 | `0x05683BF9  movups [rbp+0xEC],xmm1                        ` | record field | [V] |
| 5682e20+rbp+0xfc | 16 | sub_5682e20 | 0x05683C07 | `0x05683C07  movups [rbp+0xFC],xmm0                        ` | record field | [V] |
| 5682e20+rbp+0x10c | 16 | sub_5682e20 | 0x05683C15 | `0x05683C15  movups [rbp+0x10C],xmm0                       ` | record field | [V] |
| 5682e20+rbp+0x11c | 16 | sub_5682e20 | 0x05683C23 | `0x05683C23  movups [rbp+0x11C],xmm0                       ` | record field | [V] |
| 5682e20+rbp+0x12c | 16 | sub_5682e20 | 0x05683C31 | `0x05683C31  movups [rbp+0x12C],xmm0                       ` | record field | [V] |
| 5682e20+rbp+0x13c | 16 | sub_5682e20 | 0x05683C3F | `0x05683C3F  movups [rbp+0x13C],xmm0                       ` | record field | [V] |
| 5682e20+rbp+0x14c | 16 | sub_5682e20 | 0x05683C4D | `0x05683C4D  movups [rbp+0x14C],xmm0                       ` | record field | [V] |
| 5682e20+rdi-0x12c | 16 | sub_5682e20 | 0x05683C5B | `0x05683C5B  movups [rdi-0x12C],xmm0                       ` | - | [V] |
| 5682e20+rdi-0x10c | 16 | sub_5682e20 | 0x05683C84 | `0x05683C84  movups [rdi-0x10C],xmm1                       ` | - | [V] |
| 5682e20+rdi-0x11c | 16 | sub_5682e20 | 0x05683C8B | `0x05683C8B  movups [rdi-0x11C],xmm0                       ` | - | [V] |
| 5682e20+rbp+0x18c | 8 | sub_5682e20 | 0x05683CA9 | `0x05683CA9  mov [rbp+0x18C],al                            ` | flag byte | [V] |
| 5682e20+rbp+0x190 | 16 | sub_5682e20 | 0x05683CB6 | `0x05683CB6  movaps [rbp+0x190],xmm0                       ` | record field | [V] |
| 5682e20+rdi-0xb6 | 16 | sub_5682e20 | 0x05683CD4 | `0x05683CD4  movups [rdi-0xB6],xmm3                        ` | - | [V] |
| 5682e20+rdi-0xc4 | 16 | sub_5682e20 | 0x05683CDB | `0x05683CDB  movups [rdi-0xC4],xmm2                        ` | - | [V] |
| 5682e20+rdi-0xd4 | 16 | sub_5682e20 | 0x05683CE2 | `0x05683CE2  movups [rdi-0xD4],xmm1                        ` | - | [V] |
| 5682e20+rdi-0xe4 | 16 | sub_5682e20 | 0x05683CE9 | `0x05683CE9  movups [rdi-0xE4],xmm0                        ` | - | [V] |
| 5682e20+rdi-0x88 | 16 | sub_5682e20 | 0x05683D0A | `0x05683D0A  movups [rdi-0x88],xmm1                        ` | - | [V] |
| 5682e20+rdi-0x98 | 16 | sub_5682e20 | 0x05683D11 | `0x05683D11  movups [rdi-0x98],xmm0                        ` | - | [V] |
| 5682e20+rbp+0x1e8 | 8 | sub_5682e20 | 0x05683D43 | `0x05683D43  mov [rbp+0x1E8],rax                           ` | record field | [V] |
| 5682e20+rbp+0x250 | 8 | sub_5682e20 | 0x05683D5F, 0x05683D84 | `0x05683D5F  mov [rbp+0x250],rcx                           ` / `0x05683D84  mov [rbp+0x250],rax                           ` | record field | [V] |
| 5682e20+rdi-0x18 | 16 | sub_5682e20 | 0x05683DCF | `0x05683DCF  movups [rdi-0x18],xmm1                        ` | - | [V] |
| 5682e20+rdi-0x28 | 16 | sub_5682e20 | 0x05683DD3 | `0x05683DD3  movups [rdi-0x28],xmm0                        ` | - | [V] |
| 5682e20+rbp+0x258 | 8 | sub_5682e20 | 0x05683DFB | `0x05683DFB  mov [rbp+0x258],rax                           ` | record field | [V] |
| 5682e20+rdi | 16 | sub_5682e20 | 0x05683E05 | `0x05683E05  movups [rdi],xmm0                             ` | - | [V] |
| 5682e20+rdi+0x20 | 8 | sub_5682e20 | 0x05683E0C | `0x05683E0C  mov [rdi+0x20],rax                            ` | - | [V] |
| 5682e20+rdi+0x10 | 16 | sub_5682e20 | 0x05683E14 | `0x05683E14  movups [rdi+0x10],xmm0                        ` | - | [V] |
| 5682e20+call 0x568b0d0 | 5 | sub_5682e20 | 0x05683E26 | `0x05683E26  call 0x568B0D0                                ; -> sub_568b0d0` | - | [V] |
| 5682e20+rdi-0x270 | 16 | sub_5682e20 | 0x05683F2E | `0x05683F2E  movups [rdi-0x270],xmm6                       ` | - | [V] |
| 5682e20+rsi-0x200 | 16 | sub_5682e20 | 0x056840CC | `0x056840CC  movups [rsi-0x200],xmm6                       ` | - | [V] |
| 5682e20+call 0x9bc830 | 5 | sub_5682e20 | 0x05684230, 0x0568423E | `0x05684230  call 0x9BC830                                 ; -> sub_9bc830` / `0x0568423E  call 0x9BC830                                 ; -> sub_9bc830` | - | [V] |
| 5682e20+call 0x78ed0 | 5 | sub_5682e20 | 0x056842B9 | `0x056842B9  call 0x78ED0                                  ; -> sub_78ed0` | - | [V] |
| 5682e20+0xf9a8c78 | 5 | sub_5682e20 | 0x056842D1 | `0x056842D1  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]` | - | [V] |
| 5682e20+call 0x75720 | 5 | sub_5682e20 | 0x056842D8 | `0x056842D8  call 0x75720                                  ; -> sub_75720` | sub_75720 | [V] |
| 5682e20+call 0x75b60 | 5 | sub_5682e20 | 0x056842DE | `0x056842DE  call 0x75B60                                  ; -> sub_75b60` | - | [V] |
| 5682e20+rsp+0x10 | 8 | sub_5682e20 | 0x056842F0, 0x05684360, 0x056843E0, 0x05684470, 0x056844E0, 0x05684540, 0x05684590, 0x056845E0, 0x05684610 | `0x056842F0  mov [rsp+0x10],rdx                            ` / `0x05684360  mov [rsp+0x10],rdx                            ` / `0x056843E0  mov [rsp+0x10],rdx                            ` / `0x05684470  mov [rsp+0x10],rdx                            ` / `0x056844E0  mov [rsp+0x10],rdx                            ` / `0x05684540  mov [rsp+0x10],rdx                            ` / `0x05684590  mov [rsp+0x10],rdx                            ` / `0x056845E0  mov [rsp+0x10],rdx                            ` / `0x05684610  mov [rsp+0x10],rdx                            ` | - | [V] |
| 5682e20+rsp+0x30 | 16 | sub_5682e20 | 0x05684311, 0x05684381, 0x05684401, 0x05684491, 0x05684501, 0x05684561, 0x056845B1, 0x05684601, 0x05684631 | `0x05684311  movaps [rsp+0x30],xmm6                        ` / `0x05684381  movaps [rsp+0x30],xmm6                        ` / `0x05684401  movaps [rsp+0x30],xmm6                        ` / `0x05684491  movaps [rsp+0x30],xmm6                        ` / `0x05684501  movaps [rsp+0x30],xmm6                        ` / `0x05684561  movaps [rsp+0x30],xmm6                        ` / `0x056845B1  movaps [rsp+0x30],xmm6                        ` / `0x05684601  movaps [rsp+0x30],xmm6                        ` / `0x05684631  movaps [rsp+0x30],xmm6                        ` | - | [V] |
| 5682e20+rax-0x1d0 | 16 | sub_5682e20 | 0x056843A3, 0x0568442F | `0x056843A3  movups [rax-0x1D0],xmm0                       ` / `0x0568442F  movups [rax-0x1D0],xmm0                       ` | - | [V] |
| 5682e20+call 0x73150 | 5 | sub_5682e20 | 0x0568440D, 0x05684519, 0x0568463D | `0x0568440D  call 0x73150                                  ; -> sub_73150` / `0x05684519  call 0x73150                                  ; -> sub_73150` / `0x0568463D  call 0x73150                                  ; -> sub_73150` | sub_73150 | [V] |
| 5682e20+call 0x568ae30 | 5 | sub_5682e20 | 0x0568449A | `0x0568449A  call 0x568AE30                                ; -> sub_568ae30` | - | [V] |
| 5682e20+call 0x81cb0 | 5 | sub_5682e20 | 0x056844A6, 0x056844B2, 0x056844BE, 0x056845BD | `0x056844A6  call 0x81CB0                                  ; -> sub_81cb0` / `0x056844B2  call 0x81CB0                                  ; -> sub_81cb0` / `0x056844BE  call 0x81CB0                                  ; -> sub_81cb0` / `0x056845BD  call 0x81CB0                                  ; -> sub_81cb0` | - | [V] |
| 5682e20+call 0x568aed0 | 5 | sub_5682e20 | 0x0568450D | `0x0568450D  call 0x568AED0                                ; -> sub_568aed0` | - | [V] |
| 5682e20+call 0x568b010 | 5 | sub_5682e20 | 0x0568456D | `0x0568456D  call 0x568B010                                ; -> sub_568b010` | - | [V] |
| 5682e20+call 0xeec6e40 | 5 | sub_5682e20 | 0x05684606 | `0x05684606  call 0xEEC6E40                                ; -> sub_eec6e40` | - | [V] |


### sub_5685ea0 (data_f25b6d0) — per-element fill / dest writes [V]

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 5685ea0+rbp+0x560 | 8 | sub_5685ea0 | 0x05685F8D | `0x05685F8D  mov [rbp+0x560],rax                           ` | block header+0 = vtable ptr | [V] |
| 5685ea0+rbp+0x568 | 8 | sub_5685ea0 | 0x05685F94 | `0x05685F94  mov [rbp+0x568],rsi                           ` | block header+8 = element data base (cursor+0x240) | [V] |
| 5685ea0+rbp+0x598 | 8 | sub_5685ea0 | 0x05685F9B | `0x05685F9B  mov [rbp+0x598],rcx                           ` | block pointer = &[rbp+0x560] | [V] |
| 5685ea0+rbp-0x50 | 16 | sub_5685ea0 | 0x05686024, 0x05686B43 | `0x05686024  mov [rbp-0x50],r15                            ` / `0x05686B43  movaps [rbp-0x50],xmm0                        ` | callee out-object addr = element ptr (saved) | [V] |
| 5685ea0+rbp-0x48 | 8 | sub_5685ea0 | 0x05686028 | `0x05686028  mov [rbp-0x48],r13                            ` | saved node pointer | [V] |
| 5685ea0+0xf99ffa0 | 5 | sub_5685ea0 | 0x05686037, 0x05686073, 0x05686326, 0x0568633C, 0x056866A1, 0x056866D8, 0x05686E0E, 0x05686E34, 0x05686F3E, 0x056870D6, 0x056873C6 | `0x05686037  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05686073  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05686326  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0568633C  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056866A1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056866D8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05686E0E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05686E34  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05686F3E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056870D6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056873C6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | - | [V] |
| 5685ea0+rbp+0x2b0 | 16 | sub_5685ea0 | 0x056860D1, 0x05686104, 0x0568613E, 0x0568678F | `0x056860D1  mov [rbp+0x2B0],rsi                           ` / `0x05686104  mov [rbp+0x2B0],rsi                           ` / `0x0568613E  mov [rbp+0x2B0],r14                           ` / `0x0568678F  movaps [rbp+0x2B0],xmm0                       ` | element data base local / scratch | [V] |
| 5685ea0+rsp+0x20 | 16 | sub_5685ea0 | 0x056860ED, 0x05686120, 0x0568615A, 0x0568739C, 0x0568740C, 0x0568748C, 0x0568751C, 0x0568758C, 0x056875EC, 0x0568763C, 0x0568768C, 0x056876BC | `0x056860ED  mov [rsp+0x20],rax                            ` / `0x05686120  mov [rsp+0x20],rax                            ` / `0x0568615A  mov [rsp+0x20],rax                            ` / `0x0568739C  movaps [rsp+0x20],xmm7                        ` / `0x0568740C  movaps [rsp+0x20],xmm7                        ` / `0x0568748C  movaps [rsp+0x20],xmm7                        ` / `0x0568751C  movaps [rsp+0x20],xmm7                        ` / `0x0568758C  movaps [rsp+0x20],xmm7                        ` / `0x056875EC  movaps [rsp+0x20],xmm7                        ` / `0x0568763C  movaps [rsp+0x20],xmm7                        ` / `0x0568768C  movaps [rsp+0x20],xmm7                        ` / `0x056876BC  movaps [rsp+0x20],xmm7                        ` | r9 home slot | [V] |
| 5685ea0+call 0x5691860 | 5 | sub_5685ea0 | 0x056860FD | `0x056860FD  call 0x5691860                                ; -> sub_5691860` | - | [V] |
| 5685ea0+call 0x5691d00 | 5 | sub_5685ea0 | 0x05686130 | `0x05686130  call 0x5691D00                                ; -> sub_5691d00` | - | [V] |
| 5685ea0+rbp+0x5a0 | 8 | sub_5685ea0 | 0x05686137, 0x0568623D | `0x05686137  mov [rbp+0x5A0],rsi                           ` / `0x0568623D  mov [rbp+0x5A0],rax                           ` | record+0 = element field / callee out result | [V] |
| 5685ea0+call 0x56921b0 | 5 | sub_5685ea0 | 0x0568616A | `0x0568616A  call 0x56921B0                                ; -> sub_56921b0` | - | [V] |
| 5685ea0+rbp+0x8c8 | 8 | sub_5685ea0 | 0x0568617B | `0x0568617B  mov [rbp+0x8C8],rax                           ` | callee out-object end (+0x18) | [V] |
| 5685ea0+rbp+0x950 | 8 | sub_5685ea0 | 0x0568618C | `0x0568618C  mov [rbp+0x950],rax                           ` | copy byte count | [V] |
| 5685ea0+rbp+0x8c0 | 8 | sub_5685ea0 | 0x056861A8 | `0x056861A8  mov [rbp+0x8C0],rcx                           ` | entry count | [V] |
| 5685ea0+call 0x76a8a0 | 5 | sub_5685ea0 | 0x056861BD, 0x05686A5D | `0x056861BD  call 0x76A8A0                                 ; -> sub_76a8a0` / `0x05686A5D  call 0x76A8A0                                 ; -> sub_76a8a0` | - | [V] |
| 5685ea0+rbp+0x8b0 | 8 | sub_5685ea0 | 0x056861C5 | `0x056861C5  mov [rbp+0x8B0],rdi                           ` | slot+0 | [V] |
| 5685ea0+rbp+0x948 | 8 | sub_5685ea0 | 0x056861CC | `0x056861CC  mov [rbp+0x948],rsi                           ` | slot+8 | [V] |
| 5685ea0+call 0x655cea0 | 5 | sub_5685ea0 | 0x056861FD, 0x05686FD4, 0x05687175, 0x0568744C, 0x056874D8 | `0x056861FD  call 0x655CEA0                                ; -> sub_655cea0` / `0x05686FD4  call 0x655CEA0                                ; -> sub_655cea0` / `0x05687175  call 0x655CEA0                                ; -> sub_655cea0` / `0x0568744C  call 0x655CEA0                                ; -> sub_655cea0` / `0x056874D8  call 0x655CEA0                                ; -> sub_655cea0` | - | [V] |
| 5685ea0+r15-0x210 | 16 | sub_5685ea0 | 0x05686244, 0x056867D6 | `0x05686244  movups [r15-0x210],xmm6                       ` / `0x056867D6  movups [r15-0x210],xmm6                       ` | - | [V] |
| 5685ea0+rbp+0x940 | 8 | sub_5685ea0 | 0x05686256 | `0x05686256  mov [rbp+0x940],rcx                           ` | - | [V] |
| 5685ea0+rbp+0x5a8 | 8 | sub_5685ea0 | 0x05686279 | `0x05686279  mov [rbp+0x5A8],rcx                           ` | record+8 = element object [elem+0x268] | [V] |
| 5685ea0+rbp+0x5b0 | 8 | sub_5685ea0 | 0x05686280 | `0x05686280  mov [rbp+0x5B0],rax                           ` | record+0x10 = element object [elem+0x260] | [V] |
| 5685ea0+r15-0x200 | 16 | sub_5685ea0 | 0x05686287 | `0x05686287  movups [r15-0x200],xmm6                       ` | - | [V] |
| 5685ea0+rbp+0x5d8 | 16 | sub_5685ea0 | 0x056862A8 | `0x056862A8  movups [rbp+0x5D8],xmm7                       ` | record+0x5D8 = callee output entry {a1,[a1+0]} | [V] |
| 5685ea0+r15-0x1d0 | 16 | sub_5685ea0 | 0x056862AF, 0x056872A5 | `0x056862AF  movups [r15-0x1D0],xmm6                       ` / `0x056872A5  movups [r15-0x1D0],xmm6                       ` | - | [V] |
| 5685ea0+call 0xa78940 | 5 | sub_5685ea0 | 0x056862FD | `0x056862FD  call 0xA78940                                 ; -> sub_a78940` | - | [V] |
| 5685ea0+rbp+0x5e8 | 16 | sub_5685ea0 | 0x05686353, 0x05686837 | `0x05686353  mov [rbp+0x5E8],rsi                           ` / `0x05686837  movups [rbp+0x5E8],xmm6                       ` | record+0x5E8 = callee-output copy dest start | [V] |
| 5685ea0+rbp+0x5f0 | 8 | sub_5685ea0 | 0x0568635A, 0x05686385 | `0x0568635A  mov [rbp+0x5F0],rsi                           ` / `0x05686385  mov [rbp+0x5F0],rdi                           ` | record+0x5F0 = copy cursor / copy end | [V] |
| 5685ea0+rbp+0x5f8 | 8 | sub_5685ea0 | 0x0568636C | `0x0568636C  mov [rbp+0x5F8],rdi                           ` | record+0x5F8 = callee-output copy dest end | [V] |
| 5685ea0+call 0xeec6de0 | 5 | sub_5685ea0 | 0x05686380, 0x056865F4 | `0x05686380  call 0xEEC6DE0                                ; -> sub_eec6de0` / `0x056865F4  call 0xEEC6DE0                                ; -> sub_eec6de0` | - | [V] |
| 5685ea0+rbp+0x608 | 8 | sub_5685ea0 | 0x056863AF | `0x056863AF  mov [rbp+0x608],rax                           ` | record+0x608 = entry count | [V] |
| 5685ea0+rbp+0x618 | 16 | sub_5685ea0 | 0x056863BE | `0x056863BE  movups [rbp+0x618],xmm0                       ` | record+0x618 = element data [elem+0x118] | [V] |
| 5685ea0+rbp+0x628 | 16 | sub_5685ea0 | 0x056863CD | `0x056863CD  movups [rbp+0x628],xmm0                       ` | record+0x628 = element data [elem+0x128] | [V] |
| 5685ea0+rbp+0x638 | 16 | sub_5685ea0 | 0x056863DC | `0x056863DC  movups [rbp+0x638],xmm0                       ` | record+0x638 = element data [elem+0x138] | [V] |
| 5685ea0+rbp+0x648 | 16 | sub_5685ea0 | 0x056863EB | `0x056863EB  movups [rbp+0x648],xmm0                       ` | record+0x648 = element data [elem+0x148] | [V] |
| 5685ea0+rbp+0x658 | 16 | sub_5685ea0 | 0x056863FA | `0x056863FA  movups [rbp+0x658],xmm0                       ` | record+0x658 = element data [elem+0x158] | [V] |
| 5685ea0+rbp+0x668 | 16 | sub_5685ea0 | 0x05686409 | `0x05686409  movups [rbp+0x668],xmm0                       ` | record+0x668 = element data [elem+0x168] | [V] |
| 5685ea0+rbp+0x678 | 16 | sub_5685ea0 | 0x05686418 | `0x05686418  movups [rbp+0x678],xmm0                       ` | record+0x678 = element data [elem+0x178] | [V] |
| 5685ea0+rbp+0x688 | 16 | sub_5685ea0 | 0x05686427 | `0x05686427  movups [rbp+0x688],xmm0                       ` | record+0x688 = element data [elem+0x188] | [V] |
| 5685ea0+r15-0x110 | 8 | sub_5685ea0 | 0x05686438 | `0x05686438  mov [r15-0x110],eax                           ` | - | [V] |
| 5685ea0+r15-0x120 | 16 | sub_5685ea0 | 0x05686442 | `0x05686442  movups [r15-0x120],xmm0                       ` | - | [V] |
| 5685ea0+rbp+0x6ac | 16 | sub_5685ea0 | 0x05686452 | `0x05686452  movups [rbp+0x6AC],xmm0                       ` | record+0x6AC = element +0x1AC | [V] |
| 5685ea0+rbp+0x6bc | 16 | sub_5685ea0 | 0x05686461 | `0x05686461  movups [rbp+0x6BC],xmm0                       ` | record+0x6BC = element +0x1BC | [V] |
| 5685ea0+rbp+0x6cc | 16 | sub_5685ea0 | 0x05686470 | `0x05686470  movups [rbp+0x6CC],xmm0                       ` | record+0x6CC = element +0x1CC | [V] |
| 5685ea0+rbp+0x6dc | 16 | sub_5685ea0 | 0x0568647F | `0x0568647F  movups [rbp+0x6DC],xmm0                       ` | record+0x6DC = element +0x1DC | [V] |
| 5685ea0+rbp+0x6ec | 16 | sub_5685ea0 | 0x0568648E | `0x0568648E  movups [rbp+0x6EC],xmm0                       ` | record+0x6EC = element +0x1EC | [V] |
| 5685ea0+rbp+0x6fc | 16 | sub_5685ea0 | 0x0568649D | `0x0568649D  movups [rbp+0x6FC],xmm0                       ` | record+0x6FC = element +0x1FC | [V] |
| 5685ea0+rbp+0x70c | 16 | sub_5685ea0 | 0x056864AC | `0x056864AC  movups [rbp+0x70C],xmm0                       ` | record+0x70C = element +0x20C | [V] |
| 5685ea0+rbp+0x71c | 16 | sub_5685ea0 | 0x056864BB | `0x056864BB  movups [rbp+0x71C],xmm0                       ` | record+0x71C = element +0x21C (last field copy) | [V] |
| 5685ea0+r15-0x8c | 16 | sub_5685ea0 | 0x056864CC | `0x056864CC  movups [r15-0x8C],xmm0                        ` | - | [V] |
| 5685ea0+r15-0x6c | 16 | sub_5685ea0 | 0x056864FD | `0x056864FD  movups [r15-0x6C],xmm1                        ` | - | [V] |
| 5685ea0+r15-0x7c | 16 | sub_5685ea0 | 0x05686502 | `0x05686502  movups [r15-0x7C],xmm0                        ` | - | [V] |
| 5685ea0+rbp+0x75c | 8 | sub_5685ea0 | 0x05686526 | `0x05686526  mov [rbp+0x75C],al                            ` | record+0x75C = [a1+0x48] byte | [V] |
| 5685ea0+rbp+0x760 | 16 | sub_5685ea0 | 0x05686530 | `0x05686530  movaps [rbp+0x760],xmm0                       ` | record+0x760 = [a1+0x4C] float4 | [V] |
| 5685ea0+r15-0x16 | 16 | sub_5685ea0 | 0x05686554 | `0x05686554  movups [r15-0x16],xmm3                        ` | - | [V] |
| 5685ea0+r15-0x24 | 16 | sub_5685ea0 | 0x05686559 | `0x05686559  movups [r15-0x24],xmm2                        ` | - | [V] |
| 5685ea0+r15-0x34 | 16 | sub_5685ea0 | 0x0568655E | `0x0568655E  movups [r15-0x34],xmm1                        ` | - | [V] |
| 5685ea0+r15-0x44 | 16 | sub_5685ea0 | 0x05686563 | `0x05686563  movups [r15-0x44],xmm0                        ` | - | [V] |
| 5685ea0+rbp+0x610 | 8 | sub_5685ea0 | 0x05686579 | `0x05686579  mov [rbp+0x610],rax                           ` | record+0x610 = entry count | [V] |
| 5685ea0+r15+0x10 | 16 | sub_5685ea0 | 0x05686580 | `0x05686580  movups [r15+0x10],xmm6                        ` | - | [V] |
| 5685ea0+r15 | 16 | sub_5685ea0 | 0x05686585 | `0x05686585  movups [r15],xmm6                             ` | - | [V] |
| 5685ea0+call 0x9d6d0 | 5 | sub_5685ea0 | 0x056865CE | `0x056865CE  call 0x9D6D0                                  ; -> sub_9d6d0` | - | [V] |
| 5685ea0+rbp+0x7d0 | 8 | sub_5685ea0 | 0x056865E0 | `0x056865E0  mov [rbp+0x7D0],rsi                           ` | string length | [V] |
| 5685ea0+rbp+0x7b8 | 8 | sub_5685ea0 | 0x05686608 | `0x05686608  mov [rbp+0x7B8],rax                           ` | record+0x7B8 = string heap pointer / record start zeroed | [V] |
| 5685ea0+rbp+0x910 | 16 | sub_5685ea0 | 0x05686623, 0x05686A9C | `0x05686623  movaps [rbp+0x910],xmm6                       ` / `0x05686A9C  mov [rbp+0x910],rax                           ` | record2 field zeroed | [V] |
| 5685ea0+rbp+0x820 | 16 | sub_5685ea0 | 0x05686649, 0x056866EB, 0x05686B2E | `0x05686649  movaps [rbp+0x820],xmm6                       ` / `0x056866EB  mov [rbp+0x820],rdi                           ` / `0x05686B2E  mov [rbp+0x820],rax                           ` | second string heap pointer | [V] |
| 5685ea0+rdi-8 | 8 | sub_5685ea0 | 0x056866BF | `0x056866BF  mov [rdi-8],rax                               ` | - | [V] |
| 5685ea0+rbp+0x830 | 16 | sub_5685ea0 | 0x056866F2, 0x05686B20 | `0x056866F2  mov [rbp+0x830],rsi                           ` / `0x05686B20  movups [rbp+0x830],xmm0                       ` | record2 field | [V] |
| 5685ea0+rbp+0x838 | 8 | sub_5685ea0 | 0x056866F9 | `0x056866F9  mov [rbp+0x838],r12                           ` | record2 field | [V] |
| 5685ea0+call 0xeec6ec0 | 5 | sub_5685ea0 | 0x05686709 | `0x05686709  call 0xEEC6EC0                                ; -> sub_eec6ec0` | - | [V] |
| 5685ea0+call 0xe935700 | 5 | sub_5685ea0 | 0x0568676E, 0x05686EFC, 0x05686F8F, 0x0568701A, 0x05687073, 0x056870B8, 0x05687127, 0x056871C1, 0x05687223, 0x05687268 | `0x0568676E  call 0xE935700                                ; -> sub_e935700` / `0x05686EFC  call 0xE935700                                ; -> sub_e935700` / `0x05686F8F  call 0xE935700                                ; -> sub_e935700` / `0x0568701A  call 0xE935700                                ; -> sub_e935700` / `0x05687073  call 0xE935700                                ; -> sub_e935700` / `0x056870B8  call 0xE935700                                ; -> sub_e935700` / `0x05687127  call 0xE935700                                ; -> sub_e935700` / `0x056871C1  call 0xE935700                                ; -> sub_e935700` / `0x05687223  call 0xE935700                                ; -> sub_e935700` / `0x05687268  call 0xE935700                                ; -> sub_e935700` | - | [V] |
| 5685ea0+rbp+0x900 | 16 | sub_5685ea0 | 0x05686781 | `0x05686781  movaps [rbp+0x900],xmm1                       ` | record2 field zeroed | [V] |
| 5685ea0+rbp+0x8f0 | 16 | sub_5685ea0 | 0x05686788 | `0x05686788  movaps [rbp+0x8F0],xmm0                       ` | - | [V] |
| 5685ea0+rbp+0x2c0 | 16 | sub_5685ea0 | 0x05686796 | `0x05686796  movaps [rbp+0x2C0],xmm1                       ` | - | [V] |
| 5685ea0+rbp+0x2d0 | 16 | sub_5685ea0 | 0x056867C1 | `0x056867C1  movaps [rbp+0x2D0],xmm0                       ` | - | [V] |
| 5685ea0+rbp+0x2e0 | 8 | sub_5685ea0 | 0x056867CF | `0x056867CF  mov [rbp+0x2E0],rax                           ` | - | [V] |
| 5685ea0+rsi-0x230 | 16 | sub_5685ea0 | 0x056867DE | `0x056867DE  movups [rsi-0x230],xmm6                       ` | - | [V] |
| 5685ea0+rbp+0x300 | 8 | sub_5685ea0 | 0x056867FE | `0x056867FE  mov [rbp+0x300],al                            ` | flag byte | [V] |
| 5685ea0+rbp+0x308 | 16 | sub_5685ea0 | 0x05686830 | `0x05686830  movups [rbp+0x308],xmm0                       ` | record+0x308 = callee output entry {a1,[a1+0]} | [V] |
| 5685ea0+rbp+0x318 | 16 | sub_5685ea0 | 0x0568683E, 0x05686BD5 | `0x0568683E  movups [rbp+0x318],xmm1                       ` / `0x05686BD5  movups [rbp+0x318],xmm6                       ` | record field zeroed | [V] |
| 5685ea0+rbp+0x328 | 8 | sub_5685ea0 | 0x05686845 | `0x05686845  mov [rbp+0x328],rax                           ` | record+0x328 = copy-dest end (dest pointer) | [V] |
| 5685ea0+rsi-0x1e0 | 16 | sub_5685ea0 | 0x0568685B | `0x0568685B  movups [rsi-0x1E0],xmm0                       ` | - | [V] |
| 5685ea0+rbp+0x348 | 16 | sub_5685ea0 | 0x0568687E | `0x0568687E  movups [rbp+0x348],xmm0                       ` | record+0x348 = element data field | [V] |
| 5685ea0+rbp+0x358 | 16 | sub_5685ea0 | 0x05686885 | `0x05686885  movups [rbp+0x358],xmm1                       ` | record+0x358 = element data field | [V] |
| 5685ea0+rbp+0x368 | 16 | sub_5685ea0 | 0x0568688C | `0x0568688C  movups [rbp+0x368],xmm2                       ` | record+0x368 = element data field | [V] |
| 5685ea0+rbp+0x378 | 16 | sub_5685ea0 | 0x05686893 | `0x05686893  movups [rbp+0x378],xmm3                       ` | record+0x378 = element data field | [V] |
| 5685ea0+rbp+0x388 | 16 | sub_5685ea0 | 0x056868A1 | `0x056868A1  movups [rbp+0x388],xmm0                       ` | record+0x388 = element data field | [V] |
| 5685ea0+rbp+0x398 | 16 | sub_5685ea0 | 0x056868AF | `0x056868AF  movups [rbp+0x398],xmm0                       ` | record+0x398 = element data field | [V] |
| 5685ea0+rbp+0x3a8 | 16 | sub_5685ea0 | 0x056868BD | `0x056868BD  movups [rbp+0x3A8],xmm0                       ` | record+0x3A8 = element data field | [V] |
| 5685ea0+rbp+0x3b8 | 16 | sub_5685ea0 | 0x056868CB | `0x056868CB  movups [rbp+0x3B8],xmm0                       ` | record+0x3B8 = element data field | [V] |
| 5685ea0+rsi-0x140 | 8 | sub_5685ea0 | 0x056868D9 | `0x056868D9  mov [rsi-0x140],eax                           ` | - | [V] |
| 5685ea0+rsi-0x150 | 16 | sub_5685ea0 | 0x056868E7 | `0x056868E7  movups [rsi-0x150],xmm0                       ` | - | [V] |
| 5685ea0+rbp+0x3dc | 16 | sub_5685ea0 | 0x056868FC | `0x056868FC  movups [rbp+0x3DC],xmm0                       ` | record+0x3DC = element data field | [V] |
| 5685ea0+rbp+0x3ec | 16 | sub_5685ea0 | 0x05686903 | `0x05686903  movups [rbp+0x3EC],xmm1                       ` | record+0x3EC = element data field | [V] |
| 5685ea0+rbp+0x3fc | 16 | sub_5685ea0 | 0x05686911 | `0x05686911  movups [rbp+0x3FC],xmm0                       ` | record+0x3FC = element data field | [V] |
| 5685ea0+rbp+0x40c | 16 | sub_5685ea0 | 0x0568691F | `0x0568691F  movups [rbp+0x40C],xmm0                       ` | record+0x40C = element data field | [V] |
| 5685ea0+rbp+0x41c | 16 | sub_5685ea0 | 0x0568692D | `0x0568692D  movups [rbp+0x41C],xmm0                       ` | record+0x41C = element data field | [V] |
| 5685ea0+rbp+0x42c | 16 | sub_5685ea0 | 0x0568693B | `0x0568693B  movups [rbp+0x42C],xmm0                       ` | record+0x42C = element data field | [V] |
| 5685ea0+rbp+0x43c | 16 | sub_5685ea0 | 0x05686949 | `0x05686949  movups [rbp+0x43C],xmm0                       ` | record+0x43C = element data field | [V] |
| 5685ea0+rbp+0x44c | 16 | sub_5685ea0 | 0x05686957 | `0x05686957  movups [rbp+0x44C],xmm0                       ` | record+0x44C = element data field | [V] |
| 5685ea0+rsi-0xbc | 16 | sub_5685ea0 | 0x05686966 | `0x05686966  movups [rsi-0xBC],xmm0                        ` | - | [V] |
| 5685ea0+rsi-0x9c | 16 | sub_5685ea0 | 0x05686987 | `0x05686987  movups [rsi-0x9C],xmm1                        ` | - | [V] |
| 5685ea0+rsi-0xac | 16 | sub_5685ea0 | 0x0568698E | `0x0568698E  movups [rsi-0xAC],xmm0                        ` | - | [V] |
| 5685ea0+rbp+0x48c | 8 | sub_5685ea0 | 0x056869AC | `0x056869AC  mov [rbp+0x48C],al                            ` | record+0x48C | [V] |
| 5685ea0+rbp+0x490 | 16 | sub_5685ea0 | 0x056869B9 | `0x056869B9  movaps [rbp+0x490],xmm0                       ` | record+0x490 | [V] |
| 5685ea0+rsi-0x46 | 16 | sub_5685ea0 | 0x056869DB | `0x056869DB  movups [rsi-0x46],xmm3                        ` | - | [V] |
| 5685ea0+rsi-0x54 | 16 | sub_5685ea0 | 0x056869DF | `0x056869DF  movups [rsi-0x54],xmm2                        ` | - | [V] |
| 5685ea0+rsi-0x64 | 16 | sub_5685ea0 | 0x056869E3 | `0x056869E3  movups [rsi-0x64],xmm1                        ` | - | [V] |
| 5685ea0+rsi-0x74 | 16 | sub_5685ea0 | 0x056869E7 | `0x056869E7  movups [rsi-0x74],xmm0                        ` | - | [V] |
| 5685ea0+rsi-0x18 | 16 | sub_5685ea0 | 0x05686A0B | `0x05686A0B  movups [rsi-0x18],xmm1                        ` | - | [V] |
| 5685ea0+rsi-0x28 | 16 | sub_5685ea0 | 0x05686A0F | `0x05686A0F  movups [rsi-0x28],xmm0                        ` | - | [V] |
| 5685ea0+rbp+0x4e8 | 8 | sub_5685ea0 | 0x05686A37 | `0x05686A37  mov [rbp+0x4E8],rax                           ` | record+0x4E8 = string heap pointer | [V] |
| 5685ea0+rbp+0x518 | 8 | sub_5685ea0 | 0x05686A45 | `0x05686A45  mov [rbp+0x518],rax                           ` | record2 vtable = data_f25b6a0 | [V] |
| 5685ea0+rbp+0x550 | 8 | sub_5685ea0 | 0x05686A4C | `0x05686A4C  mov [rbp+0x550],rsi                           ` | record2 field | [V] |
| 5685ea0+rbp+0x918 | 8 | sub_5685ea0 | 0x05686A95 | `0x05686A95  mov [rbp+0x918],rcx                           ` | record2 field | [V] |
| 5685ea0+r10 | 16 | sub_5685ea0 | 0x05686AD2 | `0x05686AD2  movups [r10],xmm0                             ` | - | [V] |
| 5685ea0+r10+0x20 | 8 | sub_5685ea0 | 0x05686AE1 | `0x05686AE1  mov [r10+0x20],r8                             ` | - | [V] |
| 5685ea0+r10+0x10 | 16 | sub_5685ea0 | 0x05686AE9 | `0x05686AE9  movups [r10+0x10],xmm0                        ` | - | [V] |
| 5685ea0+rbp+0x828 | 8 | sub_5685ea0 | 0x05686AF9 | `0x05686AF9  mov [rbp+0x828],rcx                           ` | record2 field | [V] |
| 5685ea0+rbp+0x920 | 8 | sub_5685ea0 | 0x05686B19 | `0x05686B19  mov [rbp+0x920],rcx                           ` | record2 field | [V] |
| 5685ea0+rbp+0x840 | 8 | sub_5685ea0 | 0x05686B27 | `0x05686B27  mov [rbp+0x840],rdx                           ` | record2 field | [V] |
| 5685ea0+rbp-0x40 | 16 | sub_5685ea0 | 0x05686B47 | `0x05686B47  movaps [rbp-0x40],xmm1                        ` | restore callee out-object base | [V] |
| 5685ea0+rbp-0x30 | 16 | sub_5685ea0 | 0x05686B6F | `0x05686B6F  movaps [rbp-0x30],xmm0                        ` | restore callee out-object base | [V] |
| 5685ea0+rbp-0x20 | 8 | sub_5685ea0 | 0x05686B7A | `0x05686B7A  mov [rbp-0x20],rax                            ` | restore callee out-object field | [V] |
| 5685ea0+rsi-0x240 | 16 | sub_5685ea0 | 0x05686B7E | `0x05686B7E  movups [rsi-0x240],xmm6                       ` | - | [V] |
| 5685ea0+rdi-0x2a0 | 16 | sub_5685ea0 | 0x05686B85 | `0x05686B85  movups [rdi-0x2A0],xmm6                       ` | - | [V] |
| 5685ea0+rbp | 8 | sub_5685ea0 | 0x05686BA5 | `0x05686BA5  mov [rbp],al                                  ` | flag byte | [V] |
| 5685ea0+rbp+8 | 16 | sub_5685ea0 | 0x05686BD1 | `0x05686BD1  movups [rbp+8],xmm0                           ` | record field | [V] |
| 5685ea0+rbp+0x18 | 16 | sub_5685ea0 | 0x05686BDC | `0x05686BDC  movups [rbp+0x18],xmm1                        ` | record field | [V] |
| 5685ea0+rbp+0x28 | 8 | sub_5685ea0 | 0x05686BE0 | `0x05686BE0  mov [rbp+0x28],rax                            ` | record field | [V] |
| 5685ea0+rdi-0x250 | 16 | sub_5685ea0 | 0x05686BEF | `0x05686BEF  movups [rdi-0x250],xmm0                       ` | - | [V] |
| 5685ea0+rbp+0x48 | 16 | sub_5685ea0 | 0x05686C12 | `0x05686C12  movups [rbp+0x48],xmm0                        ` | record field | [V] |
| 5685ea0+rbp+0x58 | 16 | sub_5685ea0 | 0x05686C16 | `0x05686C16  movups [rbp+0x58],xmm1                        ` | record field | [V] |
| 5685ea0+rbp+0x68 | 16 | sub_5685ea0 | 0x05686C1A | `0x05686C1A  movups [rbp+0x68],xmm2                        ` | record field | [V] |
| 5685ea0+rbp+0x78 | 16 | sub_5685ea0 | 0x05686C1E | `0x05686C1E  movups [rbp+0x78],xmm3                        ` | record field | [V] |
| 5685ea0+rbp+0x88 | 16 | sub_5685ea0 | 0x05686C29 | `0x05686C29  movups [rbp+0x88],xmm0                        ` | record field | [V] |
| 5685ea0+rbp+0x98 | 16 | sub_5685ea0 | 0x05686C37 | `0x05686C37  movups [rbp+0x98],xmm0                        ` | record field | [V] |
| 5685ea0+rbp+0xa8 | 16 | sub_5685ea0 | 0x05686C45 | `0x05686C45  movups [rbp+0xA8],xmm0                        ` | record field | [V] |
| 5685ea0+rbp+0xb8 | 16 | sub_5685ea0 | 0x05686C53 | `0x05686C53  movups [rbp+0xB8],xmm0                        ` | record field | [V] |
| 5685ea0+rdi-0x1b0 | 8 | sub_5685ea0 | 0x05686C60 | `0x05686C60  mov [rdi-0x1B0],eax                           ` | - | [V] |
| 5685ea0+rdi-0x1c0 | 16 | sub_5685ea0 | 0x05686C6D | `0x05686C6D  movups [rdi-0x1C0],xmm0                       ` | - | [V] |
| 5685ea0+rbp+0xdc | 16 | sub_5685ea0 | 0x05686C82 | `0x05686C82  movups [rbp+0xDC],xmm0                        ` | record field | [V] |
| 5685ea0+rbp+0xec | 16 | sub_5685ea0 | 0x05686C89 | `0x05686C89  movups [rbp+0xEC],xmm1                        ` | record field | [V] |
| 5685ea0+rbp+0xfc | 16 | sub_5685ea0 | 0x05686C97 | `0x05686C97  movups [rbp+0xFC],xmm0                        ` | record field | [V] |
| 5685ea0+rbp+0x10c | 16 | sub_5685ea0 | 0x05686CA5 | `0x05686CA5  movups [rbp+0x10C],xmm0                       ` | record field | [V] |
| 5685ea0+rbp+0x11c | 16 | sub_5685ea0 | 0x05686CB3 | `0x05686CB3  movups [rbp+0x11C],xmm0                       ` | record field | [V] |
| 5685ea0+rbp+0x12c | 16 | sub_5685ea0 | 0x05686CC1 | `0x05686CC1  movups [rbp+0x12C],xmm0                       ` | record field | [V] |
| 5685ea0+rbp+0x13c | 16 | sub_5685ea0 | 0x05686CCF | `0x05686CCF  movups [rbp+0x13C],xmm0                       ` | record field | [V] |
| 5685ea0+rbp+0x14c | 16 | sub_5685ea0 | 0x05686CDD | `0x05686CDD  movups [rbp+0x14C],xmm0                       ` | record field | [V] |
| 5685ea0+rdi-0x12c | 16 | sub_5685ea0 | 0x05686CEB | `0x05686CEB  movups [rdi-0x12C],xmm0                       ` | - | [V] |
| 5685ea0+rdi-0x10c | 16 | sub_5685ea0 | 0x05686D14 | `0x05686D14  movups [rdi-0x10C],xmm1                       ` | - | [V] |
| 5685ea0+rdi-0x11c | 16 | sub_5685ea0 | 0x05686D1B | `0x05686D1B  movups [rdi-0x11C],xmm0                       ` | - | [V] |
| 5685ea0+rbp+0x18c | 8 | sub_5685ea0 | 0x05686D39 | `0x05686D39  mov [rbp+0x18C],al                            ` | flag byte | [V] |
| 5685ea0+rbp+0x190 | 16 | sub_5685ea0 | 0x05686D46 | `0x05686D46  movaps [rbp+0x190],xmm0                       ` | record field | [V] |
| 5685ea0+rdi-0xb6 | 16 | sub_5685ea0 | 0x05686D64 | `0x05686D64  movups [rdi-0xB6],xmm3                        ` | - | [V] |
| 5685ea0+rdi-0xc4 | 16 | sub_5685ea0 | 0x05686D6B | `0x05686D6B  movups [rdi-0xC4],xmm2                        ` | - | [V] |
| 5685ea0+rdi-0xd4 | 16 | sub_5685ea0 | 0x05686D72 | `0x05686D72  movups [rdi-0xD4],xmm1                        ` | - | [V] |
| 5685ea0+rdi-0xe4 | 16 | sub_5685ea0 | 0x05686D79 | `0x05686D79  movups [rdi-0xE4],xmm0                        ` | - | [V] |
| 5685ea0+rdi-0x88 | 16 | sub_5685ea0 | 0x05686D9A | `0x05686D9A  movups [rdi-0x88],xmm1                        ` | - | [V] |
| 5685ea0+rdi-0x98 | 16 | sub_5685ea0 | 0x05686DA1 | `0x05686DA1  movups [rdi-0x98],xmm0                        ` | - | [V] |
| 5685ea0+rbp+0x1e8 | 8 | sub_5685ea0 | 0x05686DD3 | `0x05686DD3  mov [rbp+0x1E8],rax                           ` | record field | [V] |
| 5685ea0+rbp+0x250 | 8 | sub_5685ea0 | 0x05686DEF, 0x05686E14 | `0x05686DEF  mov [rbp+0x250],rcx                           ` / `0x05686E14  mov [rbp+0x250],rax                           ` | record field | [V] |
| 5685ea0+rdi-0x18 | 16 | sub_5685ea0 | 0x05686E5F | `0x05686E5F  movups [rdi-0x18],xmm1                        ` | - | [V] |
| 5685ea0+rdi-0x28 | 16 | sub_5685ea0 | 0x05686E63 | `0x05686E63  movups [rdi-0x28],xmm0                        ` | - | [V] |
| 5685ea0+rbp+0x258 | 8 | sub_5685ea0 | 0x05686E8B | `0x05686E8B  mov [rbp+0x258],rax                           ` | record field | [V] |
| 5685ea0+rdi | 16 | sub_5685ea0 | 0x05686E95 | `0x05686E95  movups [rdi],xmm0                             ` | - | [V] |
| 5685ea0+rdi+0x20 | 8 | sub_5685ea0 | 0x05686E9C | `0x05686E9C  mov [rdi+0x20],rax                            ` | - | [V] |
| 5685ea0+rdi+0x10 | 16 | sub_5685ea0 | 0x05686EA4 | `0x05686EA4  movups [rdi+0x10],xmm0                        ` | - | [V] |
| 5685ea0+call 0x568b0d0 | 5 | sub_5685ea0 | 0x05686EB6 | `0x05686EB6  call 0x568B0D0                                ; -> sub_568b0d0` | - | [V] |
| 5685ea0+rdi-0x270 | 16 | sub_5685ea0 | 0x05686FBE | `0x05686FBE  movups [rdi-0x270],xmm6                       ` | - | [V] |
| 5685ea0+rsi-0x200 | 16 | sub_5685ea0 | 0x0568715C | `0x0568715C  movups [rsi-0x200],xmm6                       ` | - | [V] |
| 5685ea0+call 0x9bc830 | 5 | sub_5685ea0 | 0x056872C0, 0x056872CE | `0x056872C0  call 0x9BC830                                 ; -> sub_9bc830` / `0x056872CE  call 0x9BC830                                 ; -> sub_9bc830` | - | [V] |
| 5685ea0+call 0x78ed0 | 5 | sub_5685ea0 | 0x05687349 | `0x05687349  call 0x78ED0                                  ; -> sub_78ed0` | - | [V] |
| 5685ea0+0xf9a8c78 | 5 | sub_5685ea0 | 0x05687361 | `0x05687361  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]` | - | [V] |
| 5685ea0+call 0x75720 | 5 | sub_5685ea0 | 0x05687368 | `0x05687368  call 0x75720                                  ; -> sub_75720` | sub_75720 | [V] |
| 5685ea0+call 0x75b60 | 5 | sub_5685ea0 | 0x0568736E | `0x0568736E  call 0x75B60                                  ; -> sub_75b60` | - | [V] |
| 5685ea0+rsp+0x10 | 8 | sub_5685ea0 | 0x05687380, 0x056873F0, 0x05687470, 0x05687500, 0x05687570, 0x056875D0, 0x05687620, 0x05687670, 0x056876A0 | `0x05687380  mov [rsp+0x10],rdx                            ` / `0x056873F0  mov [rsp+0x10],rdx                            ` / `0x05687470  mov [rsp+0x10],rdx                            ` / `0x05687500  mov [rsp+0x10],rdx                            ` / `0x05687570  mov [rsp+0x10],rdx                            ` / `0x056875D0  mov [rsp+0x10],rdx                            ` / `0x05687620  mov [rsp+0x10],rdx                            ` / `0x05687670  mov [rsp+0x10],rdx                            ` / `0x056876A0  mov [rsp+0x10],rdx                            ` | - | [V] |
| 5685ea0+rsp+0x30 | 16 | sub_5685ea0 | 0x056873A1, 0x05687411, 0x05687491, 0x05687521, 0x05687591, 0x056875F1, 0x05687641, 0x05687691, 0x056876C1 | `0x056873A1  movaps [rsp+0x30],xmm6                        ` / `0x05687411  movaps [rsp+0x30],xmm6                        ` / `0x05687491  movaps [rsp+0x30],xmm6                        ` / `0x05687521  movaps [rsp+0x30],xmm6                        ` / `0x05687591  movaps [rsp+0x30],xmm6                        ` / `0x056875F1  movaps [rsp+0x30],xmm6                        ` / `0x05687641  movaps [rsp+0x30],xmm6                        ` / `0x05687691  movaps [rsp+0x30],xmm6                        ` / `0x056876C1  movaps [rsp+0x30],xmm6                        ` | - | [V] |
| 5685ea0+rax-0x1d0 | 16 | sub_5685ea0 | 0x05687433, 0x056874BF | `0x05687433  movups [rax-0x1D0],xmm0                       ` / `0x056874BF  movups [rax-0x1D0],xmm0                       ` | - | [V] |
| 5685ea0+call 0x73150 | 5 | sub_5685ea0 | 0x0568749D, 0x056875A9, 0x056876CD | `0x0568749D  call 0x73150                                  ; -> sub_73150` / `0x056875A9  call 0x73150                                  ; -> sub_73150` / `0x056876CD  call 0x73150                                  ; -> sub_73150` | sub_73150 | [V] |
| 5685ea0+call 0x568ae30 | 5 | sub_5685ea0 | 0x0568752A | `0x0568752A  call 0x568AE30                                ; -> sub_568ae30` | - | [V] |
| 5685ea0+call 0x81cb0 | 5 | sub_5685ea0 | 0x05687536, 0x05687542, 0x0568754E, 0x0568764D | `0x05687536  call 0x81CB0                                  ; -> sub_81cb0` / `0x05687542  call 0x81CB0                                  ; -> sub_81cb0` / `0x0568754E  call 0x81CB0                                  ; -> sub_81cb0` / `0x0568764D  call 0x81CB0                                  ; -> sub_81cb0` | - | [V] |
| 5685ea0+call 0x568aed0 | 5 | sub_5685ea0 | 0x0568759D | `0x0568759D  call 0x568AED0                                ; -> sub_568aed0` | - | [V] |
| 5685ea0+call 0x568b010 | 5 | sub_5685ea0 | 0x056875FD | `0x056875FD  call 0x568B010                                ; -> sub_568b010` | - | [V] |
| 5685ea0+call 0xeec6e40 | 5 | sub_5685ea0 | 0x05687696 | `0x05687696  call 0xEEC6E40                                ; -> sub_eec6e40` | - | [V] |


### sub_56876f0 (data_f25b730) — per-element fill / dest writes [V]

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 56876f0+rbp+0x560 | 8 | sub_56876f0 | 0x056877DD | `0x056877DD  mov [rbp+0x560],rax                           ` | block header+0 = vtable ptr | [V] |
| 56876f0+rbp+0x568 | 8 | sub_56876f0 | 0x056877E4 | `0x056877E4  mov [rbp+0x568],rsi                           ` | block header+8 = element data base (cursor+0x240) | [V] |
| 56876f0+rbp+0x598 | 8 | sub_56876f0 | 0x056877EB | `0x056877EB  mov [rbp+0x598],rcx                           ` | block pointer = &[rbp+0x560] | [V] |
| 56876f0+rbp-0x50 | 16 | sub_56876f0 | 0x0568787D, 0x056883A3 | `0x0568787D  mov [rbp-0x50],r15                            ` / `0x056883A3  movaps [rbp-0x50],xmm0                        ` | callee out-object addr = element ptr (saved) | [V] |
| 56876f0+rbp-0x48 | 8 | sub_56876f0 | 0x05687881 | `0x05687881  mov [rbp-0x48],r13                            ` | saved node pointer | [V] |
| 56876f0+0xf99ffa0 | 5 | sub_56876f0 | 0x05687890, 0x056878CC, 0x05687B86, 0x05687B9C, 0x05687F01, 0x05687F38, 0x0568866E, 0x05688694, 0x0568879E, 0x05688936, 0x05688C26 | `0x05687890  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056878CC  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05687B86  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05687B9C  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05687F01  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05687F38  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0568866E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05688694  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x0568879E  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05688936  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05688C26  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | - | [V] |
| 56876f0+rbp+0x2b0 | 16 | sub_56876f0 | 0x05687931, 0x05687964, 0x0568799E, 0x05687FEF | `0x05687931  mov [rbp+0x2B0],rsi                           ` / `0x05687964  mov [rbp+0x2B0],rsi                           ` / `0x0568799E  mov [rbp+0x2B0],r14                           ` / `0x05687FEF  movaps [rbp+0x2B0],xmm0                       ` | element data base local / scratch | [V] |
| 56876f0+rsp+0x20 | 16 | sub_56876f0 | 0x0568794D, 0x05687980, 0x056879BA, 0x05688BFC, 0x05688C6C, 0x05688CEC, 0x05688D7C, 0x05688DEC, 0x05688E4C, 0x05688E9C, 0x05688EEC, 0x05688F1C | `0x0568794D  mov [rsp+0x20],rax                            ` / `0x05687980  mov [rsp+0x20],rax                            ` / `0x056879BA  mov [rsp+0x20],rax                            ` / `0x05688BFC  movaps [rsp+0x20],xmm7                        ` / `0x05688C6C  movaps [rsp+0x20],xmm7                        ` / `0x05688CEC  movaps [rsp+0x20],xmm7                        ` / `0x05688D7C  movaps [rsp+0x20],xmm7                        ` / `0x05688DEC  movaps [rsp+0x20],xmm7                        ` / `0x05688E4C  movaps [rsp+0x20],xmm7                        ` / `0x05688E9C  movaps [rsp+0x20],xmm7                        ` / `0x05688EEC  movaps [rsp+0x20],xmm7                        ` / `0x05688F1C  movaps [rsp+0x20],xmm7                        ` | r9 home slot | [V] |
| 56876f0+call 0x5692730 | 5 | sub_56876f0 | 0x0568795D | `0x0568795D  call 0x5692730                                ; -> sub_5692730` | - | [V] |
| 56876f0+call 0x5692c00 | 5 | sub_56876f0 | 0x05687990 | `0x05687990  call 0x5692C00                                ; -> sub_5692c00` | - | [V] |
| 56876f0+rbp+0x5a0 | 8 | sub_56876f0 | 0x05687997, 0x05687A9D | `0x05687997  mov [rbp+0x5A0],rsi                           ` / `0x05687A9D  mov [rbp+0x5A0],rax                           ` | record+0 = element field / callee out result | [V] |
| 56876f0+call 0x56930e0 | 5 | sub_56876f0 | 0x056879CA | `0x056879CA  call 0x56930E0                                ; -> sub_56930e0` | - | [V] |
| 56876f0+rbp+0x8c8 | 8 | sub_56876f0 | 0x056879DB | `0x056879DB  mov [rbp+0x8C8],rax                           ` | callee out-object end (+0x18) | [V] |
| 56876f0+rbp+0x950 | 8 | sub_56876f0 | 0x056879EC | `0x056879EC  mov [rbp+0x950],rax                           ` | copy byte count | [V] |
| 56876f0+rbp+0x8c0 | 8 | sub_56876f0 | 0x05687A08 | `0x05687A08  mov [rbp+0x8C0],rcx                           ` | entry count | [V] |
| 56876f0+call 0x76a8a0 | 5 | sub_56876f0 | 0x05687A1D, 0x056882BD | `0x05687A1D  call 0x76A8A0                                 ; -> sub_76a8a0` / `0x056882BD  call 0x76A8A0                                 ; -> sub_76a8a0` | - | [V] |
| 56876f0+rbp+0x8b0 | 8 | sub_56876f0 | 0x05687A25 | `0x05687A25  mov [rbp+0x8B0],rdi                           ` | slot+0 | [V] |
| 56876f0+rbp+0x948 | 8 | sub_56876f0 | 0x05687A2C | `0x05687A2C  mov [rbp+0x948],rsi                           ` | slot+8 | [V] |
| 56876f0+call 0x655cea0 | 5 | sub_56876f0 | 0x05687A5D, 0x05688834, 0x056889D5, 0x05688CAC, 0x05688D38 | `0x05687A5D  call 0x655CEA0                                ; -> sub_655cea0` / `0x05688834  call 0x655CEA0                                ; -> sub_655cea0` / `0x056889D5  call 0x655CEA0                                ; -> sub_655cea0` / `0x05688CAC  call 0x655CEA0                                ; -> sub_655cea0` / `0x05688D38  call 0x655CEA0                                ; -> sub_655cea0` | - | [V] |
| 56876f0+r15-0x210 | 16 | sub_56876f0 | 0x05687AA4, 0x05688036 | `0x05687AA4  movups [r15-0x210],xmm6                       ` / `0x05688036  movups [r15-0x210],xmm6                       ` | - | [V] |
| 56876f0+rbp+0x940 | 8 | sub_56876f0 | 0x05687AB6 | `0x05687AB6  mov [rbp+0x940],rcx                           ` | - | [V] |
| 56876f0+rbp+0x5a8 | 8 | sub_56876f0 | 0x05687AD9 | `0x05687AD9  mov [rbp+0x5A8],rcx                           ` | record+8 = element object [elem+0x268] | [V] |
| 56876f0+rbp+0x5b0 | 8 | sub_56876f0 | 0x05687AE0 | `0x05687AE0  mov [rbp+0x5B0],rax                           ` | record+0x10 = element object [elem+0x260] | [V] |
| 56876f0+r15-0x200 | 16 | sub_56876f0 | 0x05687AE7 | `0x05687AE7  movups [r15-0x200],xmm6                       ` | - | [V] |
| 56876f0+rbp+0x5d8 | 16 | sub_56876f0 | 0x05687B08 | `0x05687B08  movups [rbp+0x5D8],xmm7                       ` | record+0x5D8 = callee output entry {a1,[a1+0]} | [V] |
| 56876f0+r15-0x1d0 | 16 | sub_56876f0 | 0x05687B0F, 0x05688B05 | `0x05687B0F  movups [r15-0x1D0],xmm6                       ` / `0x05688B05  movups [r15-0x1D0],xmm6                       ` | - | [V] |
| 56876f0+call 0xa78940 | 5 | sub_56876f0 | 0x05687B5D | `0x05687B5D  call 0xA78940                                 ; -> sub_a78940` | - | [V] |
| 56876f0+rbp+0x5e8 | 16 | sub_56876f0 | 0x05687BB3, 0x05688097 | `0x05687BB3  mov [rbp+0x5E8],rsi                           ` / `0x05688097  movups [rbp+0x5E8],xmm6                       ` | record+0x5E8 = callee-output copy dest start | [V] |
| 56876f0+rbp+0x5f0 | 8 | sub_56876f0 | 0x05687BBA, 0x05687BE5 | `0x05687BBA  mov [rbp+0x5F0],rsi                           ` / `0x05687BE5  mov [rbp+0x5F0],rdi                           ` | record+0x5F0 = copy cursor / copy end | [V] |
| 56876f0+rbp+0x5f8 | 8 | sub_56876f0 | 0x05687BCC | `0x05687BCC  mov [rbp+0x5F8],rdi                           ` | record+0x5F8 = callee-output copy dest end | [V] |
| 56876f0+call 0xeec6de0 | 5 | sub_56876f0 | 0x05687BE0, 0x05687E54 | `0x05687BE0  call 0xEEC6DE0                                ; -> sub_eec6de0` / `0x05687E54  call 0xEEC6DE0                                ; -> sub_eec6de0` | - | [V] |
| 56876f0+rbp+0x608 | 8 | sub_56876f0 | 0x05687C0F | `0x05687C0F  mov [rbp+0x608],rax                           ` | record+0x608 = entry count | [V] |
| 56876f0+rbp+0x618 | 16 | sub_56876f0 | 0x05687C1E | `0x05687C1E  movups [rbp+0x618],xmm0                       ` | record+0x618 = element data [elem+0x118] | [V] |
| 56876f0+rbp+0x628 | 16 | sub_56876f0 | 0x05687C2D | `0x05687C2D  movups [rbp+0x628],xmm0                       ` | record+0x628 = element data [elem+0x128] | [V] |
| 56876f0+rbp+0x638 | 16 | sub_56876f0 | 0x05687C3C | `0x05687C3C  movups [rbp+0x638],xmm0                       ` | record+0x638 = element data [elem+0x138] | [V] |
| 56876f0+rbp+0x648 | 16 | sub_56876f0 | 0x05687C4B | `0x05687C4B  movups [rbp+0x648],xmm0                       ` | record+0x648 = element data [elem+0x148] | [V] |
| 56876f0+rbp+0x658 | 16 | sub_56876f0 | 0x05687C5A | `0x05687C5A  movups [rbp+0x658],xmm0                       ` | record+0x658 = element data [elem+0x158] | [V] |
| 56876f0+rbp+0x668 | 16 | sub_56876f0 | 0x05687C69 | `0x05687C69  movups [rbp+0x668],xmm0                       ` | record+0x668 = element data [elem+0x168] | [V] |
| 56876f0+rbp+0x678 | 16 | sub_56876f0 | 0x05687C78 | `0x05687C78  movups [rbp+0x678],xmm0                       ` | record+0x678 = element data [elem+0x178] | [V] |
| 56876f0+rbp+0x688 | 16 | sub_56876f0 | 0x05687C87 | `0x05687C87  movups [rbp+0x688],xmm0                       ` | record+0x688 = element data [elem+0x188] | [V] |
| 56876f0+r15-0x110 | 8 | sub_56876f0 | 0x05687C98 | `0x05687C98  mov [r15-0x110],eax                           ` | - | [V] |
| 56876f0+r15-0x120 | 16 | sub_56876f0 | 0x05687CA2 | `0x05687CA2  movups [r15-0x120],xmm0                       ` | - | [V] |
| 56876f0+rbp+0x6ac | 16 | sub_56876f0 | 0x05687CB2 | `0x05687CB2  movups [rbp+0x6AC],xmm0                       ` | record+0x6AC = element +0x1AC | [V] |
| 56876f0+rbp+0x6bc | 16 | sub_56876f0 | 0x05687CC1 | `0x05687CC1  movups [rbp+0x6BC],xmm0                       ` | record+0x6BC = element +0x1BC | [V] |
| 56876f0+rbp+0x6cc | 16 | sub_56876f0 | 0x05687CD0 | `0x05687CD0  movups [rbp+0x6CC],xmm0                       ` | record+0x6CC = element +0x1CC | [V] |
| 56876f0+rbp+0x6dc | 16 | sub_56876f0 | 0x05687CDF | `0x05687CDF  movups [rbp+0x6DC],xmm0                       ` | record+0x6DC = element +0x1DC | [V] |
| 56876f0+rbp+0x6ec | 16 | sub_56876f0 | 0x05687CEE | `0x05687CEE  movups [rbp+0x6EC],xmm0                       ` | record+0x6EC = element +0x1EC | [V] |
| 56876f0+rbp+0x6fc | 16 | sub_56876f0 | 0x05687CFD | `0x05687CFD  movups [rbp+0x6FC],xmm0                       ` | record+0x6FC = element +0x1FC | [V] |
| 56876f0+rbp+0x70c | 16 | sub_56876f0 | 0x05687D0C | `0x05687D0C  movups [rbp+0x70C],xmm0                       ` | record+0x70C = element +0x20C | [V] |
| 56876f0+rbp+0x71c | 16 | sub_56876f0 | 0x05687D1B | `0x05687D1B  movups [rbp+0x71C],xmm0                       ` | record+0x71C = element +0x21C (last field copy) | [V] |
| 56876f0+r15-0x8c | 16 | sub_56876f0 | 0x05687D2C | `0x05687D2C  movups [r15-0x8C],xmm0                        ` | - | [V] |
| 56876f0+r15-0x6c | 16 | sub_56876f0 | 0x05687D5D | `0x05687D5D  movups [r15-0x6C],xmm1                        ` | - | [V] |
| 56876f0+r15-0x7c | 16 | sub_56876f0 | 0x05687D62 | `0x05687D62  movups [r15-0x7C],xmm0                        ` | - | [V] |
| 56876f0+rbp+0x75c | 8 | sub_56876f0 | 0x05687D86 | `0x05687D86  mov [rbp+0x75C],al                            ` | record+0x75C = [a1+0x48] byte | [V] |
| 56876f0+rbp+0x760 | 16 | sub_56876f0 | 0x05687D90 | `0x05687D90  movaps [rbp+0x760],xmm0                       ` | record+0x760 = [a1+0x4C] float4 | [V] |
| 56876f0+r15-0x16 | 16 | sub_56876f0 | 0x05687DB4 | `0x05687DB4  movups [r15-0x16],xmm3                        ` | - | [V] |
| 56876f0+r15-0x24 | 16 | sub_56876f0 | 0x05687DB9 | `0x05687DB9  movups [r15-0x24],xmm2                        ` | - | [V] |
| 56876f0+r15-0x34 | 16 | sub_56876f0 | 0x05687DBE | `0x05687DBE  movups [r15-0x34],xmm1                        ` | - | [V] |
| 56876f0+r15-0x44 | 16 | sub_56876f0 | 0x05687DC3 | `0x05687DC3  movups [r15-0x44],xmm0                        ` | - | [V] |
| 56876f0+rbp+0x610 | 8 | sub_56876f0 | 0x05687DD9 | `0x05687DD9  mov [rbp+0x610],rax                           ` | record+0x610 = entry count | [V] |
| 56876f0+r15+0x10 | 16 | sub_56876f0 | 0x05687DE0 | `0x05687DE0  movups [r15+0x10],xmm6                        ` | - | [V] |
| 56876f0+r15 | 16 | sub_56876f0 | 0x05687DE5 | `0x05687DE5  movups [r15],xmm6                             ` | - | [V] |
| 56876f0+call 0x9d6d0 | 5 | sub_56876f0 | 0x05687E2E | `0x05687E2E  call 0x9D6D0                                  ; -> sub_9d6d0` | - | [V] |
| 56876f0+rbp+0x7d0 | 8 | sub_56876f0 | 0x05687E40 | `0x05687E40  mov [rbp+0x7D0],rsi                           ` | string length | [V] |
| 56876f0+rbp+0x7b8 | 8 | sub_56876f0 | 0x05687E68 | `0x05687E68  mov [rbp+0x7B8],rax                           ` | record+0x7B8 = string heap pointer / record start zeroed | [V] |
| 56876f0+rbp+0x910 | 16 | sub_56876f0 | 0x05687E83, 0x056882FC | `0x05687E83  movaps [rbp+0x910],xmm6                       ` / `0x056882FC  mov [rbp+0x910],rax                           ` | record2 field zeroed | [V] |
| 56876f0+rbp+0x820 | 16 | sub_56876f0 | 0x05687EA9, 0x05687F4B, 0x0568838E | `0x05687EA9  movaps [rbp+0x820],xmm6                       ` / `0x05687F4B  mov [rbp+0x820],rdi                           ` / `0x0568838E  mov [rbp+0x820],rax                           ` | second string heap pointer | [V] |
| 56876f0+rdi-8 | 8 | sub_56876f0 | 0x05687F1F | `0x05687F1F  mov [rdi-8],rax                               ` | - | [V] |
| 56876f0+rbp+0x830 | 16 | sub_56876f0 | 0x05687F52, 0x05688380 | `0x05687F52  mov [rbp+0x830],rsi                           ` / `0x05688380  movups [rbp+0x830],xmm0                       ` | record2 field | [V] |
| 56876f0+rbp+0x838 | 8 | sub_56876f0 | 0x05687F59 | `0x05687F59  mov [rbp+0x838],r12                           ` | record2 field | [V] |
| 56876f0+call 0xeec6ec0 | 5 | sub_56876f0 | 0x05687F69 | `0x05687F69  call 0xEEC6EC0                                ; -> sub_eec6ec0` | - | [V] |
| 56876f0+call 0xe935700 | 5 | sub_56876f0 | 0x05687FCE, 0x0568875C, 0x056887EF, 0x0568887A, 0x056888D3, 0x05688918, 0x05688987, 0x05688A21, 0x05688A83, 0x05688AC8 | `0x05687FCE  call 0xE935700                                ; -> sub_e935700` / `0x0568875C  call 0xE935700                                ; -> sub_e935700` / `0x056887EF  call 0xE935700                                ; -> sub_e935700` / `0x0568887A  call 0xE935700                                ; -> sub_e935700` / `0x056888D3  call 0xE935700                                ; -> sub_e935700` / `0x05688918  call 0xE935700                                ; -> sub_e935700` / `0x05688987  call 0xE935700                                ; -> sub_e935700` / `0x05688A21  call 0xE935700                                ; -> sub_e935700` / `0x05688A83  call 0xE935700                                ; -> sub_e935700` / `0x05688AC8  call 0xE935700                                ; -> sub_e935700` | - | [V] |
| 56876f0+rbp+0x900 | 16 | sub_56876f0 | 0x05687FE1 | `0x05687FE1  movaps [rbp+0x900],xmm1                       ` | record2 field zeroed | [V] |
| 56876f0+rbp+0x8f0 | 16 | sub_56876f0 | 0x05687FE8 | `0x05687FE8  movaps [rbp+0x8F0],xmm0                       ` | - | [V] |
| 56876f0+rbp+0x2c0 | 16 | sub_56876f0 | 0x05687FF6 | `0x05687FF6  movaps [rbp+0x2C0],xmm1                       ` | - | [V] |
| 56876f0+rbp+0x2d0 | 16 | sub_56876f0 | 0x05688021 | `0x05688021  movaps [rbp+0x2D0],xmm0                       ` | - | [V] |
| 56876f0+rbp+0x2e0 | 8 | sub_56876f0 | 0x0568802F | `0x0568802F  mov [rbp+0x2E0],rax                           ` | - | [V] |
| 56876f0+rsi-0x230 | 16 | sub_56876f0 | 0x0568803E | `0x0568803E  movups [rsi-0x230],xmm6                       ` | - | [V] |
| 56876f0+rbp+0x300 | 8 | sub_56876f0 | 0x0568805E | `0x0568805E  mov [rbp+0x300],al                            ` | flag byte | [V] |
| 56876f0+rbp+0x308 | 16 | sub_56876f0 | 0x05688090 | `0x05688090  movups [rbp+0x308],xmm0                       ` | record+0x308 = callee output entry {a1,[a1+0]} | [V] |
| 56876f0+rbp+0x318 | 16 | sub_56876f0 | 0x0568809E, 0x05688435 | `0x0568809E  movups [rbp+0x318],xmm1                       ` / `0x05688435  movups [rbp+0x318],xmm6                       ` | record field zeroed | [V] |
| 56876f0+rbp+0x328 | 8 | sub_56876f0 | 0x056880A5 | `0x056880A5  mov [rbp+0x328],rax                           ` | record+0x328 = copy-dest end (dest pointer) | [V] |
| 56876f0+rsi-0x1e0 | 16 | sub_56876f0 | 0x056880BB | `0x056880BB  movups [rsi-0x1E0],xmm0                       ` | - | [V] |
| 56876f0+rbp+0x348 | 16 | sub_56876f0 | 0x056880DE | `0x056880DE  movups [rbp+0x348],xmm0                       ` | record+0x348 = element data field | [V] |
| 56876f0+rbp+0x358 | 16 | sub_56876f0 | 0x056880E5 | `0x056880E5  movups [rbp+0x358],xmm1                       ` | record+0x358 = element data field | [V] |
| 56876f0+rbp+0x368 | 16 | sub_56876f0 | 0x056880EC | `0x056880EC  movups [rbp+0x368],xmm2                       ` | record+0x368 = element data field | [V] |
| 56876f0+rbp+0x378 | 16 | sub_56876f0 | 0x056880F3 | `0x056880F3  movups [rbp+0x378],xmm3                       ` | record+0x378 = element data field | [V] |
| 56876f0+rbp+0x388 | 16 | sub_56876f0 | 0x05688101 | `0x05688101  movups [rbp+0x388],xmm0                       ` | record+0x388 = element data field | [V] |
| 56876f0+rbp+0x398 | 16 | sub_56876f0 | 0x0568810F | `0x0568810F  movups [rbp+0x398],xmm0                       ` | record+0x398 = element data field | [V] |
| 56876f0+rbp+0x3a8 | 16 | sub_56876f0 | 0x0568811D | `0x0568811D  movups [rbp+0x3A8],xmm0                       ` | record+0x3A8 = element data field | [V] |
| 56876f0+rbp+0x3b8 | 16 | sub_56876f0 | 0x0568812B | `0x0568812B  movups [rbp+0x3B8],xmm0                       ` | record+0x3B8 = element data field | [V] |
| 56876f0+rsi-0x140 | 8 | sub_56876f0 | 0x05688139 | `0x05688139  mov [rsi-0x140],eax                           ` | - | [V] |
| 56876f0+rsi-0x150 | 16 | sub_56876f0 | 0x05688147 | `0x05688147  movups [rsi-0x150],xmm0                       ` | - | [V] |
| 56876f0+rbp+0x3dc | 16 | sub_56876f0 | 0x0568815C | `0x0568815C  movups [rbp+0x3DC],xmm0                       ` | record+0x3DC = element data field | [V] |
| 56876f0+rbp+0x3ec | 16 | sub_56876f0 | 0x05688163 | `0x05688163  movups [rbp+0x3EC],xmm1                       ` | record+0x3EC = element data field | [V] |
| 56876f0+rbp+0x3fc | 16 | sub_56876f0 | 0x05688171 | `0x05688171  movups [rbp+0x3FC],xmm0                       ` | record+0x3FC = element data field | [V] |
| 56876f0+rbp+0x40c | 16 | sub_56876f0 | 0x0568817F | `0x0568817F  movups [rbp+0x40C],xmm0                       ` | record+0x40C = element data field | [V] |
| 56876f0+rbp+0x41c | 16 | sub_56876f0 | 0x0568818D | `0x0568818D  movups [rbp+0x41C],xmm0                       ` | record+0x41C = element data field | [V] |
| 56876f0+rbp+0x42c | 16 | sub_56876f0 | 0x0568819B | `0x0568819B  movups [rbp+0x42C],xmm0                       ` | record+0x42C = element data field | [V] |
| 56876f0+rbp+0x43c | 16 | sub_56876f0 | 0x056881A9 | `0x056881A9  movups [rbp+0x43C],xmm0                       ` | record+0x43C = element data field | [V] |
| 56876f0+rbp+0x44c | 16 | sub_56876f0 | 0x056881B7 | `0x056881B7  movups [rbp+0x44C],xmm0                       ` | record+0x44C = element data field | [V] |
| 56876f0+rsi-0xbc | 16 | sub_56876f0 | 0x056881C6 | `0x056881C6  movups [rsi-0xBC],xmm0                        ` | - | [V] |
| 56876f0+rsi-0x9c | 16 | sub_56876f0 | 0x056881E7 | `0x056881E7  movups [rsi-0x9C],xmm1                        ` | - | [V] |
| 56876f0+rsi-0xac | 16 | sub_56876f0 | 0x056881EE | `0x056881EE  movups [rsi-0xAC],xmm0                        ` | - | [V] |
| 56876f0+rbp+0x48c | 8 | sub_56876f0 | 0x0568820C | `0x0568820C  mov [rbp+0x48C],al                            ` | record+0x48C | [V] |
| 56876f0+rbp+0x490 | 16 | sub_56876f0 | 0x05688219 | `0x05688219  movaps [rbp+0x490],xmm0                       ` | record+0x490 | [V] |
| 56876f0+rsi-0x46 | 16 | sub_56876f0 | 0x0568823B | `0x0568823B  movups [rsi-0x46],xmm3                        ` | - | [V] |
| 56876f0+rsi-0x54 | 16 | sub_56876f0 | 0x0568823F | `0x0568823F  movups [rsi-0x54],xmm2                        ` | - | [V] |
| 56876f0+rsi-0x64 | 16 | sub_56876f0 | 0x05688243 | `0x05688243  movups [rsi-0x64],xmm1                        ` | - | [V] |
| 56876f0+rsi-0x74 | 16 | sub_56876f0 | 0x05688247 | `0x05688247  movups [rsi-0x74],xmm0                        ` | - | [V] |
| 56876f0+rsi-0x18 | 16 | sub_56876f0 | 0x0568826B | `0x0568826B  movups [rsi-0x18],xmm1                        ` | - | [V] |
| 56876f0+rsi-0x28 | 16 | sub_56876f0 | 0x0568826F | `0x0568826F  movups [rsi-0x28],xmm0                        ` | - | [V] |
| 56876f0+rbp+0x4e8 | 8 | sub_56876f0 | 0x05688297 | `0x05688297  mov [rbp+0x4E8],rax                           ` | record+0x4E8 = string heap pointer | [V] |
| 56876f0+rbp+0x518 | 8 | sub_56876f0 | 0x056882A5 | `0x056882A5  mov [rbp+0x518],rax                           ` | record2 vtable = data_f25b6a0 | [V] |
| 56876f0+rbp+0x550 | 8 | sub_56876f0 | 0x056882AC | `0x056882AC  mov [rbp+0x550],rsi                           ` | record2 field | [V] |
| 56876f0+rbp+0x918 | 8 | sub_56876f0 | 0x056882F5 | `0x056882F5  mov [rbp+0x918],rcx                           ` | record2 field | [V] |
| 56876f0+r10 | 16 | sub_56876f0 | 0x05688332 | `0x05688332  movups [r10],xmm0                             ` | - | [V] |
| 56876f0+r10+0x20 | 8 | sub_56876f0 | 0x05688341 | `0x05688341  mov [r10+0x20],r8                             ` | - | [V] |
| 56876f0+r10+0x10 | 16 | sub_56876f0 | 0x05688349 | `0x05688349  movups [r10+0x10],xmm0                        ` | - | [V] |
| 56876f0+rbp+0x828 | 8 | sub_56876f0 | 0x05688359 | `0x05688359  mov [rbp+0x828],rcx                           ` | record2 field | [V] |
| 56876f0+rbp+0x920 | 8 | sub_56876f0 | 0x05688379 | `0x05688379  mov [rbp+0x920],rcx                           ` | record2 field | [V] |
| 56876f0+rbp+0x840 | 8 | sub_56876f0 | 0x05688387 | `0x05688387  mov [rbp+0x840],rdx                           ` | record2 field | [V] |
| 56876f0+rbp-0x40 | 16 | sub_56876f0 | 0x056883A7 | `0x056883A7  movaps [rbp-0x40],xmm1                        ` | restore callee out-object base | [V] |
| 56876f0+rbp-0x30 | 16 | sub_56876f0 | 0x056883CF | `0x056883CF  movaps [rbp-0x30],xmm0                        ` | restore callee out-object base | [V] |
| 56876f0+rbp-0x20 | 8 | sub_56876f0 | 0x056883DA | `0x056883DA  mov [rbp-0x20],rax                            ` | restore callee out-object field | [V] |
| 56876f0+rsi-0x240 | 16 | sub_56876f0 | 0x056883DE | `0x056883DE  movups [rsi-0x240],xmm6                       ` | - | [V] |
| 56876f0+rdi-0x2a0 | 16 | sub_56876f0 | 0x056883E5 | `0x056883E5  movups [rdi-0x2A0],xmm6                       ` | - | [V] |
| 56876f0+rbp | 8 | sub_56876f0 | 0x05688405 | `0x05688405  mov [rbp],al                                  ` | flag byte | [V] |
| 56876f0+rbp+8 | 16 | sub_56876f0 | 0x05688431 | `0x05688431  movups [rbp+8],xmm0                           ` | record field | [V] |
| 56876f0+rbp+0x18 | 16 | sub_56876f0 | 0x0568843C | `0x0568843C  movups [rbp+0x18],xmm1                        ` | record field | [V] |
| 56876f0+rbp+0x28 | 8 | sub_56876f0 | 0x05688440 | `0x05688440  mov [rbp+0x28],rax                            ` | record field | [V] |
| 56876f0+rdi-0x250 | 16 | sub_56876f0 | 0x0568844F | `0x0568844F  movups [rdi-0x250],xmm0                       ` | - | [V] |
| 56876f0+rbp+0x48 | 16 | sub_56876f0 | 0x05688472 | `0x05688472  movups [rbp+0x48],xmm0                        ` | record field | [V] |
| 56876f0+rbp+0x58 | 16 | sub_56876f0 | 0x05688476 | `0x05688476  movups [rbp+0x58],xmm1                        ` | record field | [V] |
| 56876f0+rbp+0x68 | 16 | sub_56876f0 | 0x0568847A | `0x0568847A  movups [rbp+0x68],xmm2                        ` | record field | [V] |
| 56876f0+rbp+0x78 | 16 | sub_56876f0 | 0x0568847E | `0x0568847E  movups [rbp+0x78],xmm3                        ` | record field | [V] |
| 56876f0+rbp+0x88 | 16 | sub_56876f0 | 0x05688489 | `0x05688489  movups [rbp+0x88],xmm0                        ` | record field | [V] |
| 56876f0+rbp+0x98 | 16 | sub_56876f0 | 0x05688497 | `0x05688497  movups [rbp+0x98],xmm0                        ` | record field | [V] |
| 56876f0+rbp+0xa8 | 16 | sub_56876f0 | 0x056884A5 | `0x056884A5  movups [rbp+0xA8],xmm0                        ` | record field | [V] |
| 56876f0+rbp+0xb8 | 16 | sub_56876f0 | 0x056884B3 | `0x056884B3  movups [rbp+0xB8],xmm0                        ` | record field | [V] |
| 56876f0+rdi-0x1b0 | 8 | sub_56876f0 | 0x056884C0 | `0x056884C0  mov [rdi-0x1B0],eax                           ` | - | [V] |
| 56876f0+rdi-0x1c0 | 16 | sub_56876f0 | 0x056884CD | `0x056884CD  movups [rdi-0x1C0],xmm0                       ` | - | [V] |
| 56876f0+rbp+0xdc | 16 | sub_56876f0 | 0x056884E2 | `0x056884E2  movups [rbp+0xDC],xmm0                        ` | record field | [V] |
| 56876f0+rbp+0xec | 16 | sub_56876f0 | 0x056884E9 | `0x056884E9  movups [rbp+0xEC],xmm1                        ` | record field | [V] |
| 56876f0+rbp+0xfc | 16 | sub_56876f0 | 0x056884F7 | `0x056884F7  movups [rbp+0xFC],xmm0                        ` | record field | [V] |
| 56876f0+rbp+0x10c | 16 | sub_56876f0 | 0x05688505 | `0x05688505  movups [rbp+0x10C],xmm0                       ` | record field | [V] |
| 56876f0+rbp+0x11c | 16 | sub_56876f0 | 0x05688513 | `0x05688513  movups [rbp+0x11C],xmm0                       ` | record field | [V] |
| 56876f0+rbp+0x12c | 16 | sub_56876f0 | 0x05688521 | `0x05688521  movups [rbp+0x12C],xmm0                       ` | record field | [V] |
| 56876f0+rbp+0x13c | 16 | sub_56876f0 | 0x0568852F | `0x0568852F  movups [rbp+0x13C],xmm0                       ` | record field | [V] |
| 56876f0+rbp+0x14c | 16 | sub_56876f0 | 0x0568853D | `0x0568853D  movups [rbp+0x14C],xmm0                       ` | record field | [V] |
| 56876f0+rdi-0x12c | 16 | sub_56876f0 | 0x0568854B | `0x0568854B  movups [rdi-0x12C],xmm0                       ` | - | [V] |
| 56876f0+rdi-0x10c | 16 | sub_56876f0 | 0x05688574 | `0x05688574  movups [rdi-0x10C],xmm1                       ` | - | [V] |
| 56876f0+rdi-0x11c | 16 | sub_56876f0 | 0x0568857B | `0x0568857B  movups [rdi-0x11C],xmm0                       ` | - | [V] |
| 56876f0+rbp+0x18c | 8 | sub_56876f0 | 0x05688599 | `0x05688599  mov [rbp+0x18C],al                            ` | flag byte | [V] |
| 56876f0+rbp+0x190 | 16 | sub_56876f0 | 0x056885A6 | `0x056885A6  movaps [rbp+0x190],xmm0                       ` | record field | [V] |
| 56876f0+rdi-0xb6 | 16 | sub_56876f0 | 0x056885C4 | `0x056885C4  movups [rdi-0xB6],xmm3                        ` | - | [V] |
| 56876f0+rdi-0xc4 | 16 | sub_56876f0 | 0x056885CB | `0x056885CB  movups [rdi-0xC4],xmm2                        ` | - | [V] |
| 56876f0+rdi-0xd4 | 16 | sub_56876f0 | 0x056885D2 | `0x056885D2  movups [rdi-0xD4],xmm1                        ` | - | [V] |
| 56876f0+rdi-0xe4 | 16 | sub_56876f0 | 0x056885D9 | `0x056885D9  movups [rdi-0xE4],xmm0                        ` | - | [V] |
| 56876f0+rdi-0x88 | 16 | sub_56876f0 | 0x056885FA | `0x056885FA  movups [rdi-0x88],xmm1                        ` | - | [V] |
| 56876f0+rdi-0x98 | 16 | sub_56876f0 | 0x05688601 | `0x05688601  movups [rdi-0x98],xmm0                        ` | - | [V] |
| 56876f0+rbp+0x1e8 | 8 | sub_56876f0 | 0x05688633 | `0x05688633  mov [rbp+0x1E8],rax                           ` | record field | [V] |
| 56876f0+rbp+0x250 | 8 | sub_56876f0 | 0x0568864F, 0x05688674 | `0x0568864F  mov [rbp+0x250],rcx                           ` / `0x05688674  mov [rbp+0x250],rax                           ` | record field | [V] |
| 56876f0+rdi-0x18 | 16 | sub_56876f0 | 0x056886BF | `0x056886BF  movups [rdi-0x18],xmm1                        ` | - | [V] |
| 56876f0+rdi-0x28 | 16 | sub_56876f0 | 0x056886C3 | `0x056886C3  movups [rdi-0x28],xmm0                        ` | - | [V] |
| 56876f0+rbp+0x258 | 8 | sub_56876f0 | 0x056886EB | `0x056886EB  mov [rbp+0x258],rax                           ` | record field | [V] |
| 56876f0+rdi | 16 | sub_56876f0 | 0x056886F5 | `0x056886F5  movups [rdi],xmm0                             ` | - | [V] |
| 56876f0+rdi+0x20 | 8 | sub_56876f0 | 0x056886FC | `0x056886FC  mov [rdi+0x20],rax                            ` | - | [V] |
| 56876f0+rdi+0x10 | 16 | sub_56876f0 | 0x05688704 | `0x05688704  movups [rdi+0x10],xmm0                        ` | - | [V] |
| 56876f0+call 0x568b0d0 | 5 | sub_56876f0 | 0x05688716 | `0x05688716  call 0x568B0D0                                ; -> sub_568b0d0` | - | [V] |
| 56876f0+rdi-0x270 | 16 | sub_56876f0 | 0x0568881E | `0x0568881E  movups [rdi-0x270],xmm6                       ` | - | [V] |
| 56876f0+rsi-0x200 | 16 | sub_56876f0 | 0x056889BC | `0x056889BC  movups [rsi-0x200],xmm6                       ` | - | [V] |
| 56876f0+call 0x9bc830 | 5 | sub_56876f0 | 0x05688B20, 0x05688B2E | `0x05688B20  call 0x9BC830                                 ; -> sub_9bc830` / `0x05688B2E  call 0x9BC830                                 ; -> sub_9bc830` | - | [V] |
| 56876f0+call 0x78ed0 | 5 | sub_56876f0 | 0x05688BA9 | `0x05688BA9  call 0x78ED0                                  ; -> sub_78ed0` | - | [V] |
| 56876f0+0xf9a8c78 | 5 | sub_56876f0 | 0x05688BC1 | `0x05688BC1  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]` | - | [V] |
| 56876f0+call 0x75720 | 5 | sub_56876f0 | 0x05688BC8 | `0x05688BC8  call 0x75720                                  ; -> sub_75720` | sub_75720 | [V] |
| 56876f0+call 0x75b60 | 5 | sub_56876f0 | 0x05688BCE | `0x05688BCE  call 0x75B60                                  ; -> sub_75b60` | - | [V] |
| 56876f0+rsp+0x10 | 8 | sub_56876f0 | 0x05688BE0, 0x05688C50, 0x05688CD0, 0x05688D60, 0x05688DD0, 0x05688E30, 0x05688E80, 0x05688ED0, 0x05688F00 | `0x05688BE0  mov [rsp+0x10],rdx                            ` / `0x05688C50  mov [rsp+0x10],rdx                            ` / `0x05688CD0  mov [rsp+0x10],rdx                            ` / `0x05688D60  mov [rsp+0x10],rdx                            ` / `0x05688DD0  mov [rsp+0x10],rdx                            ` / `0x05688E30  mov [rsp+0x10],rdx                            ` / `0x05688E80  mov [rsp+0x10],rdx                            ` / `0x05688ED0  mov [rsp+0x10],rdx                            ` / `0x05688F00  mov [rsp+0x10],rdx                            ` | - | [V] |
| 56876f0+rsp+0x30 | 16 | sub_56876f0 | 0x05688C01, 0x05688C71, 0x05688CF1, 0x05688D81, 0x05688DF1, 0x05688E51, 0x05688EA1, 0x05688EF1, 0x05688F21 | `0x05688C01  movaps [rsp+0x30],xmm6                        ` / `0x05688C71  movaps [rsp+0x30],xmm6                        ` / `0x05688CF1  movaps [rsp+0x30],xmm6                        ` / `0x05688D81  movaps [rsp+0x30],xmm6                        ` / `0x05688DF1  movaps [rsp+0x30],xmm6                        ` / `0x05688E51  movaps [rsp+0x30],xmm6                        ` / `0x05688EA1  movaps [rsp+0x30],xmm6                        ` / `0x05688EF1  movaps [rsp+0x30],xmm6                        ` / `0x05688F21  movaps [rsp+0x30],xmm6                        ` | - | [V] |
| 56876f0+rax-0x1d0 | 16 | sub_56876f0 | 0x05688C93, 0x05688D1F | `0x05688C93  movups [rax-0x1D0],xmm0                       ` / `0x05688D1F  movups [rax-0x1D0],xmm0                       ` | - | [V] |
| 56876f0+call 0x73150 | 5 | sub_56876f0 | 0x05688CFD, 0x05688E09, 0x05688F2D | `0x05688CFD  call 0x73150                                  ; -> sub_73150` / `0x05688E09  call 0x73150                                  ; -> sub_73150` / `0x05688F2D  call 0x73150                                  ; -> sub_73150` | sub_73150 | [V] |
| 56876f0+call 0x568ae30 | 5 | sub_56876f0 | 0x05688D8A | `0x05688D8A  call 0x568AE30                                ; -> sub_568ae30` | - | [V] |
| 56876f0+call 0x81cb0 | 5 | sub_56876f0 | 0x05688D96, 0x05688DA2, 0x05688DAE, 0x05688EAD | `0x05688D96  call 0x81CB0                                  ; -> sub_81cb0` / `0x05688DA2  call 0x81CB0                                  ; -> sub_81cb0` / `0x05688DAE  call 0x81CB0                                  ; -> sub_81cb0` / `0x05688EAD  call 0x81CB0                                  ; -> sub_81cb0` | - | [V] |
| 56876f0+call 0x568aed0 | 5 | sub_56876f0 | 0x05688DFD | `0x05688DFD  call 0x568AED0                                ; -> sub_568aed0` | - | [V] |
| 56876f0+call 0x568b010 | 5 | sub_56876f0 | 0x05688E5D | `0x05688E5D  call 0x568B010                                ; -> sub_568b010` | - | [V] |
| 56876f0+call 0xeec6e40 | 5 | sub_56876f0 | 0x05688EF6 | `0x05688EF6  call 0xEEC6E40                                ; -> sub_eec6e40` | - | [V] |
| 56876f0+rax | 8 | sub_56876f0 | 0x05688F5A | `0x05688F5A  mov [rax],rdx                                 ` | - | [V] |
| 56876f0+rax+8 | 8 | sub_56876f0 | 0x05688F61 | `0x05688F61  mov [rax+8],rcx                               ` | - | [V] |
| 56876f0+call 0xe93b480 | 5 | sub_56876f0 | 0x05688FC1 | `0x05688FC1  call 0xE93B480                                ; -> sub_e93b480` | - | [V] |


### sub_5684660 (data_f25b670) — per-element fill / dest writes [V]

| offset | size | func | site addr | verbatim `0xRVA  instr` | meaning | [V] |
|--------|------|------|-----------|-------------------------|---------|-----|
| 5684660+rbp+0x560 | 8 | sub_5684660 | 0x05684735 | `0x05684735  mov [rbp+0x560],rax                           ` | block header+0 = vtable ptr | [V] |
| 5684660+rbp+0x568 | 8 | sub_5684660 | 0x0568473C | `0x0568473C  mov [rbp+0x568],rsi                           ` | block header+8 = element data base (cursor+0x240) | [V] |
| 5684660+rbp+0x598 | 8 | sub_5684660 | 0x0568474A | `0x0568474A  mov [rbp+0x598],rax                           ` | block pointer = &[rbp+0x560] | [V] |
| 5684660+rbp-0x50 | 16 | sub_5684660 | 0x056847D7, 0x056852F3 | `0x056847D7  mov [rbp-0x50],r15                            ` / `0x056852F3  movaps [rbp-0x50],xmm0                        ` | callee out-object addr = element ptr (saved) | [V] |
| 5684660+rbp-0x48 | 8 | sub_5684660 | 0x056847DB | `0x056847DB  mov [rbp-0x48],r13                            ` | saved node pointer | [V] |
| 5684660+0xf99ffa0 | 5 | sub_5684660 | 0x056847EA, 0x05684826, 0x05684AD6, 0x05684AEC, 0x05684E51, 0x05684E88, 0x056855BE, 0x056855E4, 0x056856EE, 0x05685886, 0x05685B76 | `0x056847EA  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05684826  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05684AD6  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05684AEC  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05684E51  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05684E88  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056855BE  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056855E4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x056856EE  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05685886  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` / `0x05685B76  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040` | - | [V] |
| 5684660+rbp+0x2b0 | 16 | sub_5684660 | 0x05684884, 0x056848B7, 0x056848F1, 0x05684F3F | `0x05684884  mov [rbp+0x2B0],rsi                           ` / `0x056848B7  mov [rbp+0x2B0],rsi                           ` / `0x056848F1  mov [rbp+0x2B0],r14                           ` / `0x05684F3F  movaps [rbp+0x2B0],xmm0                       ` | element data base local / scratch | [V] |
| 5684660+rsp+0x20 | 16 | sub_5684660 | 0x056848A0, 0x056848D3, 0x0568490D, 0x05685B4C | `0x056848A0  mov [rsp+0x20],rax                            ` / `0x056848D3  mov [rsp+0x20],rax                            ` / `0x0568490D  mov [rsp+0x20],rax                            ` / `0x05685B4C  movaps [rsp+0x20],xmm7                        ` | r9 home slot | [V] |
| 5684660+call 0x5690960 | 5 | sub_5684660 | 0x056848B0 | `0x056848B0  call 0x5690960                                ; -> sub_5690960` | - | [V] |
| 5684660+call 0x5690e10 | 5 | sub_5684660 | 0x056848E3 | `0x056848E3  call 0x5690E10                                ; -> sub_5690e10` | - | [V] |
| 5684660+rbp+0x5a0 | 8 | sub_5684660 | 0x056848EA, 0x056849ED | `0x056848EA  mov [rbp+0x5A0],rsi                           ` / `0x056849ED  mov [rbp+0x5A0],rax                           ` | record+0 = element field / callee out result | [V] |
| 5684660+call 0x56912d0 | 5 | sub_5684660 | 0x0568491D | `0x0568491D  call 0x56912D0                                ; -> sub_56912d0` | - | [V] |
| 5684660+rbp+0x8c8 | 8 | sub_5684660 | 0x0568492E | `0x0568492E  mov [rbp+0x8C8],rax                           ` | callee out-object end (+0x18) | [V] |
| 5684660+rbp+0x950 | 8 | sub_5684660 | 0x0568493F | `0x0568493F  mov [rbp+0x950],rax                           ` | copy byte count | [V] |
| 5684660+rbp+0x8c0 | 8 | sub_5684660 | 0x0568495B | `0x0568495B  mov [rbp+0x8C0],rcx                           ` | entry count | [V] |
| 5684660+call 0x76a8a0 | 5 | sub_5684660 | 0x05684970, 0x0568520D | `0x05684970  call 0x76A8A0                                 ; -> sub_76a8a0` / `0x0568520D  call 0x76A8A0                                 ; -> sub_76a8a0` | - | [V] |
| 5684660+rbp+0x8b0 | 8 | sub_5684660 | 0x05684978 | `0x05684978  mov [rbp+0x8B0],rdi                           ` | slot+0 | [V] |
| 5684660+rbp+0x948 | 8 | sub_5684660 | 0x0568497F | `0x0568497F  mov [rbp+0x948],rsi                           ` | slot+8 | [V] |
| 5684660+call 0x655cea0 | 5 | sub_5684660 | 0x056849AD, 0x05685784, 0x05685925 | `0x056849AD  call 0x655CEA0                                ; -> sub_655cea0` / `0x05685784  call 0x655CEA0                                ; -> sub_655cea0` / `0x05685925  call 0x655CEA0                                ; -> sub_655cea0` | - | [V] |
| 5684660+r15-0x210 | 16 | sub_5684660 | 0x056849F4, 0x05684F86 | `0x056849F4  movups [r15-0x210],xmm6                       ` / `0x05684F86  movups [r15-0x210],xmm6                       ` | - | [V] |
| 5684660+rbp+0x940 | 8 | sub_5684660 | 0x05684A06 | `0x05684A06  mov [rbp+0x940],rcx                           ` | - | [V] |
| 5684660+rbp+0x5a8 | 8 | sub_5684660 | 0x05684A29 | `0x05684A29  mov [rbp+0x5A8],rcx                           ` | record+8 = element object [elem+0x268] | [V] |
| 5684660+rbp+0x5b0 | 8 | sub_5684660 | 0x05684A30 | `0x05684A30  mov [rbp+0x5B0],rax                           ` | record+0x10 = element object [elem+0x260] | [V] |
| 5684660+r15-0x200 | 16 | sub_5684660 | 0x05684A37 | `0x05684A37  movups [r15-0x200],xmm6                       ` | - | [V] |
| 5684660+rbp+0x5d8 | 16 | sub_5684660 | 0x05684A58 | `0x05684A58  movups [rbp+0x5D8],xmm7                       ` | record+0x5D8 = callee output entry {a1,[a1+0]} | [V] |
| 5684660+r15-0x1d0 | 16 | sub_5684660 | 0x05684A5F, 0x05685A55 | `0x05684A5F  movups [r15-0x1D0],xmm6                       ` / `0x05685A55  movups [r15-0x1D0],xmm6                       ` | - | [V] |
| 5684660+call 0xa78940 | 5 | sub_5684660 | 0x05684AAD | `0x05684AAD  call 0xA78940                                 ; -> sub_a78940` | - | [V] |
| 5684660+rbp+0x5e8 | 16 | sub_5684660 | 0x05684B03, 0x05684FE7 | `0x05684B03  mov [rbp+0x5E8],rsi                           ` / `0x05684FE7  movups [rbp+0x5E8],xmm6                       ` | record+0x5E8 = callee-output copy dest start | [V] |
| 5684660+rbp+0x5f0 | 8 | sub_5684660 | 0x05684B0A, 0x05684B35 | `0x05684B0A  mov [rbp+0x5F0],rsi                           ` / `0x05684B35  mov [rbp+0x5F0],rdi                           ` | record+0x5F0 = copy cursor / copy end | [V] |
| 5684660+rbp+0x5f8 | 8 | sub_5684660 | 0x05684B1C | `0x05684B1C  mov [rbp+0x5F8],rdi                           ` | record+0x5F8 = callee-output copy dest end | [V] |
| 5684660+call 0xeec6de0 | 5 | sub_5684660 | 0x05684B30, 0x05684DA4 | `0x05684B30  call 0xEEC6DE0                                ; -> sub_eec6de0` / `0x05684DA4  call 0xEEC6DE0                                ; -> sub_eec6de0` | - | [V] |
| 5684660+rbp+0x608 | 8 | sub_5684660 | 0x05684B5F | `0x05684B5F  mov [rbp+0x608],rax                           ` | record+0x608 = entry count | [V] |
| 5684660+rbp+0x618 | 16 | sub_5684660 | 0x05684B6E | `0x05684B6E  movups [rbp+0x618],xmm0                       ` | record+0x618 = element data [elem+0x118] | [V] |
| 5684660+rbp+0x628 | 16 | sub_5684660 | 0x05684B7D | `0x05684B7D  movups [rbp+0x628],xmm0                       ` | record+0x628 = element data [elem+0x128] | [V] |
| 5684660+rbp+0x638 | 16 | sub_5684660 | 0x05684B8C | `0x05684B8C  movups [rbp+0x638],xmm0                       ` | record+0x638 = element data [elem+0x138] | [V] |
| 5684660+rbp+0x648 | 16 | sub_5684660 | 0x05684B9B | `0x05684B9B  movups [rbp+0x648],xmm0                       ` | record+0x648 = element data [elem+0x148] | [V] |
| 5684660+rbp+0x658 | 16 | sub_5684660 | 0x05684BAA | `0x05684BAA  movups [rbp+0x658],xmm0                       ` | record+0x658 = element data [elem+0x158] | [V] |
| 5684660+rbp+0x668 | 16 | sub_5684660 | 0x05684BB9 | `0x05684BB9  movups [rbp+0x668],xmm0                       ` | record+0x668 = element data [elem+0x168] | [V] |
| 5684660+rbp+0x678 | 16 | sub_5684660 | 0x05684BC8 | `0x05684BC8  movups [rbp+0x678],xmm0                       ` | record+0x678 = element data [elem+0x178] | [V] |
| 5684660+rbp+0x688 | 16 | sub_5684660 | 0x05684BD7 | `0x05684BD7  movups [rbp+0x688],xmm0                       ` | record+0x688 = element data [elem+0x188] | [V] |
| 5684660+r15-0x110 | 8 | sub_5684660 | 0x05684BE8 | `0x05684BE8  mov [r15-0x110],eax                           ` | - | [V] |
| 5684660+r15-0x120 | 16 | sub_5684660 | 0x05684BF2 | `0x05684BF2  movups [r15-0x120],xmm0                       ` | - | [V] |
| 5684660+rbp+0x6ac | 16 | sub_5684660 | 0x05684C02 | `0x05684C02  movups [rbp+0x6AC],xmm0                       ` | record+0x6AC = element +0x1AC | [V] |
| 5684660+rbp+0x6bc | 16 | sub_5684660 | 0x05684C11 | `0x05684C11  movups [rbp+0x6BC],xmm0                       ` | record+0x6BC = element +0x1BC | [V] |
| 5684660+rbp+0x6cc | 16 | sub_5684660 | 0x05684C20 | `0x05684C20  movups [rbp+0x6CC],xmm0                       ` | record+0x6CC = element +0x1CC | [V] |
| 5684660+rbp+0x6dc | 16 | sub_5684660 | 0x05684C2F | `0x05684C2F  movups [rbp+0x6DC],xmm0                       ` | record+0x6DC = element +0x1DC | [V] |
| 5684660+rbp+0x6ec | 16 | sub_5684660 | 0x05684C3E | `0x05684C3E  movups [rbp+0x6EC],xmm0                       ` | record+0x6EC = element +0x1EC | [V] |
| 5684660+rbp+0x6fc | 16 | sub_5684660 | 0x05684C4D | `0x05684C4D  movups [rbp+0x6FC],xmm0                       ` | record+0x6FC = element +0x1FC | [V] |
| 5684660+rbp+0x70c | 16 | sub_5684660 | 0x05684C5C | `0x05684C5C  movups [rbp+0x70C],xmm0                       ` | record+0x70C = element +0x20C | [V] |
| 5684660+rbp+0x71c | 16 | sub_5684660 | 0x05684C6B | `0x05684C6B  movups [rbp+0x71C],xmm0                       ` | record+0x71C = element +0x21C (last field copy) | [V] |
| 5684660+r15-0x8c | 16 | sub_5684660 | 0x05684C7C | `0x05684C7C  movups [r15-0x8C],xmm0                        ` | - | [V] |
| 5684660+r15-0x6c | 16 | sub_5684660 | 0x05684CAD | `0x05684CAD  movups [r15-0x6C],xmm1                        ` | - | [V] |
| 5684660+r15-0x7c | 16 | sub_5684660 | 0x05684CB2 | `0x05684CB2  movups [r15-0x7C],xmm0                        ` | - | [V] |
| 5684660+rbp+0x75c | 8 | sub_5684660 | 0x05684CD6 | `0x05684CD6  mov [rbp+0x75C],al                            ` | record+0x75C = [a1+0x48] byte | [V] |
| 5684660+rbp+0x760 | 16 | sub_5684660 | 0x05684CE0 | `0x05684CE0  movaps [rbp+0x760],xmm0                       ` | record+0x760 = [a1+0x4C] float4 | [V] |
| 5684660+r15-0x16 | 16 | sub_5684660 | 0x05684D04 | `0x05684D04  movups [r15-0x16],xmm3                        ` | - | [V] |
| 5684660+r15-0x24 | 16 | sub_5684660 | 0x05684D09 | `0x05684D09  movups [r15-0x24],xmm2                        ` | - | [V] |
| 5684660+r15-0x34 | 16 | sub_5684660 | 0x05684D0E | `0x05684D0E  movups [r15-0x34],xmm1                        ` | - | [V] |
| 5684660+r15-0x44 | 16 | sub_5684660 | 0x05684D13 | `0x05684D13  movups [r15-0x44],xmm0                        ` | - | [V] |
| 5684660+rbp+0x610 | 8 | sub_5684660 | 0x05684D29 | `0x05684D29  mov [rbp+0x610],rax                           ` | record+0x610 = entry count | [V] |
| 5684660+r15+0x10 | 16 | sub_5684660 | 0x05684D30 | `0x05684D30  movups [r15+0x10],xmm6                        ` | - | [V] |
| 5684660+r15 | 16 | sub_5684660 | 0x05684D35 | `0x05684D35  movups [r15],xmm6                             ` | - | [V] |
| 5684660+call 0x9d6d0 | 5 | sub_5684660 | 0x05684D7E | `0x05684D7E  call 0x9D6D0                                  ; -> sub_9d6d0` | - | [V] |
| 5684660+rbp+0x7d0 | 8 | sub_5684660 | 0x05684D90 | `0x05684D90  mov [rbp+0x7D0],rsi                           ` | string length | [V] |
| 5684660+rbp+0x7b8 | 8 | sub_5684660 | 0x05684DB8 | `0x05684DB8  mov [rbp+0x7B8],rax                           ` | record+0x7B8 = string heap pointer / record start zeroed | [V] |
| 5684660+rbp+0x910 | 16 | sub_5684660 | 0x05684DD3, 0x0568524C | `0x05684DD3  movaps [rbp+0x910],xmm6                       ` / `0x0568524C  mov [rbp+0x910],rax                           ` | record2 field zeroed | [V] |
| 5684660+rbp+0x820 | 16 | sub_5684660 | 0x05684DF9, 0x05684E9B, 0x056852DE | `0x05684DF9  movaps [rbp+0x820],xmm6                       ` / `0x05684E9B  mov [rbp+0x820],rdi                           ` / `0x056852DE  mov [rbp+0x820],rax                           ` | second string heap pointer | [V] |
| 5684660+rdi-8 | 8 | sub_5684660 | 0x05684E6F | `0x05684E6F  mov [rdi-8],rax                               ` | - | [V] |
| 5684660+rbp+0x830 | 16 | sub_5684660 | 0x05684EA2, 0x056852D0 | `0x05684EA2  mov [rbp+0x830],rsi                           ` / `0x056852D0  movups [rbp+0x830],xmm0                       ` | record2 field | [V] |
| 5684660+rbp+0x838 | 8 | sub_5684660 | 0x05684EA9 | `0x05684EA9  mov [rbp+0x838],r12                           ` | record2 field | [V] |
| 5684660+call 0xeec6ec0 | 5 | sub_5684660 | 0x05684EB9 | `0x05684EB9  call 0xEEC6EC0                                ; -> sub_eec6ec0` | - | [V] |
| 5684660+call 0xe935700 | 5 | sub_5684660 | 0x05684F1E, 0x056856AC, 0x0568573F, 0x056857CA, 0x05685823, 0x05685868, 0x056858D7, 0x05685971, 0x056859D3, 0x05685A18 | `0x05684F1E  call 0xE935700                                ; -> sub_e935700` / `0x056856AC  call 0xE935700                                ; -> sub_e935700` / `0x0568573F  call 0xE935700                                ; -> sub_e935700` / `0x056857CA  call 0xE935700                                ; -> sub_e935700` / `0x05685823  call 0xE935700                                ; -> sub_e935700` / `0x05685868  call 0xE935700                                ; -> sub_e935700` / `0x056858D7  call 0xE935700                                ; -> sub_e935700` / `0x05685971  call 0xE935700                                ; -> sub_e935700` / `0x056859D3  call 0xE935700                                ; -> sub_e935700` / `0x05685A18  call 0xE935700                                ; -> sub_e935700` | - | [V] |
| 5684660+rbp+0x900 | 16 | sub_5684660 | 0x05684F31 | `0x05684F31  movaps [rbp+0x900],xmm1                       ` | record2 field zeroed | [V] |
| 5684660+rbp+0x8f0 | 16 | sub_5684660 | 0x05684F38 | `0x05684F38  movaps [rbp+0x8F0],xmm0                       ` | - | [V] |
| 5684660+rbp+0x2c0 | 16 | sub_5684660 | 0x05684F46 | `0x05684F46  movaps [rbp+0x2C0],xmm1                       ` | - | [V] |
| 5684660+rbp+0x2d0 | 16 | sub_5684660 | 0x05684F71 | `0x05684F71  movaps [rbp+0x2D0],xmm0                       ` | - | [V] |
| 5684660+rbp+0x2e0 | 8 | sub_5684660 | 0x05684F7F | `0x05684F7F  mov [rbp+0x2E0],rax                           ` | - | [V] |
| 5684660+rsi-0x230 | 16 | sub_5684660 | 0x05684F8E | `0x05684F8E  movups [rsi-0x230],xmm6                       ` | - | [V] |
| 5684660+rbp+0x300 | 8 | sub_5684660 | 0x05684FAE | `0x05684FAE  mov [rbp+0x300],al                            ` | flag byte | [V] |
| 5684660+rbp+0x308 | 16 | sub_5684660 | 0x05684FE0 | `0x05684FE0  movups [rbp+0x308],xmm0                       ` | record+0x308 = callee output entry {a1,[a1+0]} | [V] |
| 5684660+rbp+0x318 | 16 | sub_5684660 | 0x05684FEE, 0x05685385 | `0x05684FEE  movups [rbp+0x318],xmm1                       ` / `0x05685385  movups [rbp+0x318],xmm6                       ` | record field zeroed | [V] |
| 5684660+rbp+0x328 | 8 | sub_5684660 | 0x05684FF5 | `0x05684FF5  mov [rbp+0x328],rax                           ` | record+0x328 = copy-dest end (dest pointer) | [V] |
| 5684660+rsi-0x1e0 | 16 | sub_5684660 | 0x0568500B | `0x0568500B  movups [rsi-0x1E0],xmm0                       ` | - | [V] |
| 5684660+rbp+0x348 | 16 | sub_5684660 | 0x0568502E | `0x0568502E  movups [rbp+0x348],xmm0                       ` | record+0x348 = element data field | [V] |
| 5684660+rbp+0x358 | 16 | sub_5684660 | 0x05685035 | `0x05685035  movups [rbp+0x358],xmm1                       ` | record+0x358 = element data field | [V] |
| 5684660+rbp+0x368 | 16 | sub_5684660 | 0x0568503C | `0x0568503C  movups [rbp+0x368],xmm2                       ` | record+0x368 = element data field | [V] |
| 5684660+rbp+0x378 | 16 | sub_5684660 | 0x05685043 | `0x05685043  movups [rbp+0x378],xmm3                       ` | record+0x378 = element data field | [V] |
| 5684660+rbp+0x388 | 16 | sub_5684660 | 0x05685051 | `0x05685051  movups [rbp+0x388],xmm0                       ` | record+0x388 = element data field | [V] |
| 5684660+rbp+0x398 | 16 | sub_5684660 | 0x0568505F | `0x0568505F  movups [rbp+0x398],xmm0                       ` | record+0x398 = element data field | [V] |
| 5684660+rbp+0x3a8 | 16 | sub_5684660 | 0x0568506D | `0x0568506D  movups [rbp+0x3A8],xmm0                       ` | record+0x3A8 = element data field | [V] |
| 5684660+rbp+0x3b8 | 16 | sub_5684660 | 0x0568507B | `0x0568507B  movups [rbp+0x3B8],xmm0                       ` | record+0x3B8 = element data field | [V] |
| 5684660+rsi-0x140 | 8 | sub_5684660 | 0x05685089 | `0x05685089  mov [rsi-0x140],eax                           ` | - | [V] |
| 5684660+rsi-0x150 | 16 | sub_5684660 | 0x05685097 | `0x05685097  movups [rsi-0x150],xmm0                       ` | - | [V] |
| 5684660+rbp+0x3dc | 16 | sub_5684660 | 0x056850AC | `0x056850AC  movups [rbp+0x3DC],xmm0                       ` | record+0x3DC = element data field | [V] |
| 5684660+rbp+0x3ec | 16 | sub_5684660 | 0x056850B3 | `0x056850B3  movups [rbp+0x3EC],xmm1                       ` | record+0x3EC = element data field | [V] |
| 5684660+rbp+0x3fc | 16 | sub_5684660 | 0x056850C1 | `0x056850C1  movups [rbp+0x3FC],xmm0                       ` | record+0x3FC = element data field | [V] |
| 5684660+rbp+0x40c | 16 | sub_5684660 | 0x056850CF | `0x056850CF  movups [rbp+0x40C],xmm0                       ` | record+0x40C = element data field | [V] |
| 5684660+rbp+0x41c | 16 | sub_5684660 | 0x056850DD | `0x056850DD  movups [rbp+0x41C],xmm0                       ` | record+0x41C = element data field | [V] |
| 5684660+rbp+0x42c | 16 | sub_5684660 | 0x056850EB | `0x056850EB  movups [rbp+0x42C],xmm0                       ` | record+0x42C = element data field | [V] |
| 5684660+rbp+0x43c | 16 | sub_5684660 | 0x056850F9 | `0x056850F9  movups [rbp+0x43C],xmm0                       ` | record+0x43C = element data field | [V] |
| 5684660+rbp+0x44c | 16 | sub_5684660 | 0x05685107 | `0x05685107  movups [rbp+0x44C],xmm0                       ` | record+0x44C = element data field | [V] |
| 5684660+rsi-0xbc | 16 | sub_5684660 | 0x05685116 | `0x05685116  movups [rsi-0xBC],xmm0                        ` | - | [V] |
| 5684660+rsi-0x9c | 16 | sub_5684660 | 0x05685137 | `0x05685137  movups [rsi-0x9C],xmm1                        ` | - | [V] |
| 5684660+rsi-0xac | 16 | sub_5684660 | 0x0568513E | `0x0568513E  movups [rsi-0xAC],xmm0                        ` | - | [V] |
| 5684660+rbp+0x48c | 8 | sub_5684660 | 0x0568515C | `0x0568515C  mov [rbp+0x48C],al                            ` | record+0x48C | [V] |
| 5684660+rbp+0x490 | 16 | sub_5684660 | 0x05685169 | `0x05685169  movaps [rbp+0x490],xmm0                       ` | record+0x490 | [V] |
| 5684660+rsi-0x46 | 16 | sub_5684660 | 0x0568518B | `0x0568518B  movups [rsi-0x46],xmm3                        ` | - | [V] |
| 5684660+rsi-0x54 | 16 | sub_5684660 | 0x0568518F | `0x0568518F  movups [rsi-0x54],xmm2                        ` | - | [V] |
| 5684660+rsi-0x64 | 16 | sub_5684660 | 0x05685193 | `0x05685193  movups [rsi-0x64],xmm1                        ` | - | [V] |
| 5684660+rsi-0x74 | 16 | sub_5684660 | 0x05685197 | `0x05685197  movups [rsi-0x74],xmm0                        ` | - | [V] |
| 5684660+rsi-0x18 | 16 | sub_5684660 | 0x056851BB | `0x056851BB  movups [rsi-0x18],xmm1                        ` | - | [V] |
| 5684660+rsi-0x28 | 16 | sub_5684660 | 0x056851BF | `0x056851BF  movups [rsi-0x28],xmm0                        ` | - | [V] |
| 5684660+rbp+0x4e8 | 8 | sub_5684660 | 0x056851E7 | `0x056851E7  mov [rbp+0x4E8],rax                           ` | record+0x4E8 = string heap pointer | [V] |
| 5684660+rbp+0x518 | 8 | sub_5684660 | 0x056851F5 | `0x056851F5  mov [rbp+0x518],rax                           ` | record2 vtable = data_f25b6a0 | [V] |
| 5684660+rbp+0x550 | 8 | sub_5684660 | 0x056851FC | `0x056851FC  mov [rbp+0x550],rsi                           ` | record2 field | [V] |
| 5684660+rbp+0x918 | 8 | sub_5684660 | 0x05685245 | `0x05685245  mov [rbp+0x918],rcx                           ` | record2 field | [V] |
| 5684660+r10 | 16 | sub_5684660 | 0x05685282 | `0x05685282  movups [r10],xmm0                             ` | - | [V] |
| 5684660+r10+0x20 | 8 | sub_5684660 | 0x05685291 | `0x05685291  mov [r10+0x20],r8                             ` | - | [V] |
| 5684660+r10+0x10 | 16 | sub_5684660 | 0x05685299 | `0x05685299  movups [r10+0x10],xmm0                        ` | - | [V] |
| 5684660+rbp+0x828 | 8 | sub_5684660 | 0x056852A9 | `0x056852A9  mov [rbp+0x828],rcx                           ` | record2 field | [V] |
| 5684660+rbp+0x920 | 8 | sub_5684660 | 0x056852C9 | `0x056852C9  mov [rbp+0x920],rcx                           ` | record2 field | [V] |
| 5684660+rbp+0x840 | 8 | sub_5684660 | 0x056852D7 | `0x056852D7  mov [rbp+0x840],rdx                           ` | record2 field | [V] |
| 5684660+rbp-0x40 | 16 | sub_5684660 | 0x056852F7 | `0x056852F7  movaps [rbp-0x40],xmm1                        ` | restore callee out-object base | [V] |
| 5684660+rbp-0x30 | 16 | sub_5684660 | 0x0568531F | `0x0568531F  movaps [rbp-0x30],xmm0                        ` | restore callee out-object base | [V] |
| 5684660+rbp-0x20 | 8 | sub_5684660 | 0x0568532A | `0x0568532A  mov [rbp-0x20],rax                            ` | restore callee out-object field | [V] |
| 5684660+rsi-0x240 | 16 | sub_5684660 | 0x0568532E | `0x0568532E  movups [rsi-0x240],xmm6                       ` | - | [V] |
| 5684660+rdi-0x2a0 | 16 | sub_5684660 | 0x05685335 | `0x05685335  movups [rdi-0x2A0],xmm6                       ` | - | [V] |
| 5684660+rbp | 8 | sub_5684660 | 0x05685355 | `0x05685355  mov [rbp],al                                  ` | flag byte | [V] |
| 5684660+rbp+8 | 16 | sub_5684660 | 0x05685381 | `0x05685381  movups [rbp+8],xmm0                           ` | record field | [V] |
| 5684660+rbp+0x18 | 16 | sub_5684660 | 0x0568538C | `0x0568538C  movups [rbp+0x18],xmm1                        ` | record field | [V] |
| 5684660+rbp+0x28 | 8 | sub_5684660 | 0x05685390 | `0x05685390  mov [rbp+0x28],rax                            ` | record field | [V] |
| 5684660+rdi-0x250 | 16 | sub_5684660 | 0x0568539F | `0x0568539F  movups [rdi-0x250],xmm0                       ` | - | [V] |
| 5684660+rbp+0x48 | 16 | sub_5684660 | 0x056853C2 | `0x056853C2  movups [rbp+0x48],xmm0                        ` | record field | [V] |
| 5684660+rbp+0x58 | 16 | sub_5684660 | 0x056853C6 | `0x056853C6  movups [rbp+0x58],xmm1                        ` | record field | [V] |
| 5684660+rbp+0x68 | 16 | sub_5684660 | 0x056853CA | `0x056853CA  movups [rbp+0x68],xmm2                        ` | record field | [V] |
| 5684660+rbp+0x78 | 16 | sub_5684660 | 0x056853CE | `0x056853CE  movups [rbp+0x78],xmm3                        ` | record field | [V] |
| 5684660+rbp+0x88 | 16 | sub_5684660 | 0x056853D9 | `0x056853D9  movups [rbp+0x88],xmm0                        ` | record field | [V] |
| 5684660+rbp+0x98 | 16 | sub_5684660 | 0x056853E7 | `0x056853E7  movups [rbp+0x98],xmm0                        ` | record field | [V] |
| 5684660+rbp+0xa8 | 16 | sub_5684660 | 0x056853F5 | `0x056853F5  movups [rbp+0xA8],xmm0                        ` | record field | [V] |
| 5684660+rbp+0xb8 | 16 | sub_5684660 | 0x05685403 | `0x05685403  movups [rbp+0xB8],xmm0                        ` | record field | [V] |
| 5684660+rdi-0x1b0 | 8 | sub_5684660 | 0x05685410 | `0x05685410  mov [rdi-0x1B0],eax                           ` | - | [V] |
| 5684660+rdi-0x1c0 | 16 | sub_5684660 | 0x0568541D | `0x0568541D  movups [rdi-0x1C0],xmm0                       ` | - | [V] |
| 5684660+rbp+0xdc | 16 | sub_5684660 | 0x05685432 | `0x05685432  movups [rbp+0xDC],xmm0                        ` | record field | [V] |
| 5684660+rbp+0xec | 16 | sub_5684660 | 0x05685439 | `0x05685439  movups [rbp+0xEC],xmm1                        ` | record field | [V] |
| 5684660+rbp+0xfc | 16 | sub_5684660 | 0x05685447 | `0x05685447  movups [rbp+0xFC],xmm0                        ` | record field | [V] |
| 5684660+rbp+0x10c | 16 | sub_5684660 | 0x05685455 | `0x05685455  movups [rbp+0x10C],xmm0                       ` | record field | [V] |
| 5684660+rbp+0x11c | 16 | sub_5684660 | 0x05685463 | `0x05685463  movups [rbp+0x11C],xmm0                       ` | record field | [V] |
| 5684660+rbp+0x12c | 16 | sub_5684660 | 0x05685471 | `0x05685471  movups [rbp+0x12C],xmm0                       ` | record field | [V] |
| 5684660+rbp+0x13c | 16 | sub_5684660 | 0x0568547F | `0x0568547F  movups [rbp+0x13C],xmm0                       ` | record field | [V] |
| 5684660+rbp+0x14c | 16 | sub_5684660 | 0x0568548D | `0x0568548D  movups [rbp+0x14C],xmm0                       ` | record field | [V] |
| 5684660+rdi-0x12c | 16 | sub_5684660 | 0x0568549B | `0x0568549B  movups [rdi-0x12C],xmm0                       ` | - | [V] |
| 5684660+rdi-0x10c | 16 | sub_5684660 | 0x056854C4 | `0x056854C4  movups [rdi-0x10C],xmm1                       ` | - | [V] |
| 5684660+rdi-0x11c | 16 | sub_5684660 | 0x056854CB | `0x056854CB  movups [rdi-0x11C],xmm0                       ` | - | [V] |
| 5684660+rbp+0x18c | 8 | sub_5684660 | 0x056854E9 | `0x056854E9  mov [rbp+0x18C],al                            ` | flag byte | [V] |
| 5684660+rbp+0x190 | 16 | sub_5684660 | 0x056854F6 | `0x056854F6  movaps [rbp+0x190],xmm0                       ` | record field | [V] |
| 5684660+rdi-0xb6 | 16 | sub_5684660 | 0x05685514 | `0x05685514  movups [rdi-0xB6],xmm3                        ` | - | [V] |
| 5684660+rdi-0xc4 | 16 | sub_5684660 | 0x0568551B | `0x0568551B  movups [rdi-0xC4],xmm2                        ` | - | [V] |
| 5684660+rdi-0xd4 | 16 | sub_5684660 | 0x05685522 | `0x05685522  movups [rdi-0xD4],xmm1                        ` | - | [V] |
| 5684660+rdi-0xe4 | 16 | sub_5684660 | 0x05685529 | `0x05685529  movups [rdi-0xE4],xmm0                        ` | - | [V] |
| 5684660+rdi-0x88 | 16 | sub_5684660 | 0x0568554A | `0x0568554A  movups [rdi-0x88],xmm1                        ` | - | [V] |
| 5684660+rdi-0x98 | 16 | sub_5684660 | 0x05685551 | `0x05685551  movups [rdi-0x98],xmm0                        ` | - | [V] |
| 5684660+rbp+0x1e8 | 8 | sub_5684660 | 0x05685583 | `0x05685583  mov [rbp+0x1E8],rax                           ` | record field | [V] |
| 5684660+rbp+0x250 | 8 | sub_5684660 | 0x0568559F, 0x056855C4 | `0x0568559F  mov [rbp+0x250],rcx                           ` / `0x056855C4  mov [rbp+0x250],rax                           ` | record field | [V] |
| 5684660+rdi-0x18 | 16 | sub_5684660 | 0x0568560F | `0x0568560F  movups [rdi-0x18],xmm1                        ` | - | [V] |
| 5684660+rdi-0x28 | 16 | sub_5684660 | 0x05685613 | `0x05685613  movups [rdi-0x28],xmm0                        ` | - | [V] |
| 5684660+rbp+0x258 | 8 | sub_5684660 | 0x0568563B | `0x0568563B  mov [rbp+0x258],rax                           ` | record field | [V] |
| 5684660+rdi | 16 | sub_5684660 | 0x05685645 | `0x05685645  movups [rdi],xmm0                             ` | - | [V] |
| 5684660+rdi+0x20 | 8 | sub_5684660 | 0x0568564C | `0x0568564C  mov [rdi+0x20],rax                            ` | - | [V] |
| 5684660+rdi+0x10 | 16 | sub_5684660 | 0x05685654 | `0x05685654  movups [rdi+0x10],xmm0                        ` | - | [V] |
| 5684660+call 0x568b0d0 | 5 | sub_5684660 | 0x05685666 | `0x05685666  call 0x568B0D0                                ; -> sub_568b0d0` | - | [V] |
| 5684660+rdi-0x270 | 16 | sub_5684660 | 0x0568576E | `0x0568576E  movups [rdi-0x270],xmm6                       ` | - | [V] |
| 5684660+rsi-0x200 | 16 | sub_5684660 | 0x0568590C | `0x0568590C  movups [rsi-0x200],xmm6                       ` | - | [V] |
| 5684660+call 0x9bc830 | 5 | sub_5684660 | 0x05685A70, 0x05685A7E | `0x05685A70  call 0x9BC830                                 ; -> sub_9bc830` / `0x05685A7E  call 0x9BC830                                 ; -> sub_9bc830` | - | [V] |
| 5684660+call 0x78ed0 | 5 | sub_5684660 | 0x05685AF9 | `0x05685AF9  call 0x78ED0                                  ; -> sub_78ed0` | - | [V] |
| 5684660+0xf9a8c78 | 5 | sub_5684660 | 0x05685B11 | `0x05685B11  call qword ptr [0xF9A8C78]                    ; [data_f9a8c78]` | - | [V] |
| 5684660+call 0x75720 | 5 | sub_5684660 | 0x05685B18 | `0x05685B18  call 0x75720                                  ; -> sub_75720` | sub_75720 | [V] |
| 5684660+call 0x75b60 | 5 | sub_5684660 | 0x05685B1E | `0x05685B1E  call 0x75B60                                  ; -> sub_75b60` | - | [V] |
| 5684660+rsp+0x10 | 8 | sub_5684660 | 0x05685B30 | `0x05685B30  mov [rsp+0x10],rdx                            ` | - | [V] |
| 5684660+rsp+0x30 | 16 | sub_5684660 | 0x05685B51 | `0x05685B51  movaps [rsp+0x30],xmm6                        ` | - | [V] |




## CLOSES?
YES — every pending part of item C5b is now [V]-proven in this file:
# - Part (a): per-element callees sub_5690960/sub_5690e10/sub_56912d0 instruction-complete [V]
#   (entry to ret, every basic block covered; verify_oc clean). [Not redone row-by-row here; see oc_U-EL3i_r3.md.]
# - Part (b): per-element fill and dest writes of all 7 element-loop per-pass bodies [V]:
#   sub_5684660 (data_f25b670) [V per oc_U-EL3i_r3.md; table reproduced below], sub_567E510
#   (data_f25b4f0), sub_567FD70 (data_f25b550), sub_56815D0 (data_f25b5b0), sub_5682E20
#   (data_f25b610), sub_5685EA0 (data_f25b6d0), sub_56876F0 (data_f25b730) [V in the tables below].
#   Each body's entry reads a1+0x10/0x18/0x28/0x60 and its 0x290-stride element loop were already
#   [V] (oc_U-EC5b.md); the per-element fill (record construction at rbp+0x560.., callee-output copy,
#   element-data and a1-derived field writes) and the dest writes (sub_568b0d0 caller-dest write +
#   sub_655CEA0 side-record writes) are now [V] with verbatim instruction proof for every site.
#   No blocking fact remains. The only per-body variations are the vtable immediate and the callee
#   triple; sub_5682E20 additionally filters on element bit 0x08 instead of 0x20 (noted at its
#   filter site, does not change the fill/dest writes).
#
# Everything else named in the C5b item line (declare machinery sub_5698290/sub_568c4e0, wrappers
# flag 1..5, and all non-element-loop per-pass bodies sub_5667860/c80/e70, sub_5667fe0, sub_56685c0,
# sub_566a450, sub_566adb0, sub_566d690, sub_5668d90, sub_5669cf0, sub_566a880, sub_567c110,
# sub_568bdc0, sub_5693680, sub_5694510, and shared helpers sub_5669ae0/sub_5689800/sub_5695960/
# sub_5696540/sub_5697650/sub_56cb540) was already [V] in oc_U-EC5b.md/oc_U-EL3i_r1.md/r2.md and is
# not redone here.
#
# No subagents, no tools.rtools.*, static analysis only, no game launched. Every quoted
# `0xRVA  instr` line re-checked against the exe by verify_oc.

## TOOL REQUESTS
None — all proof lines copied verbatim from rdis listings of the exe; verify_oc re-checks each line.
