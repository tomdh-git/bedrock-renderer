## NEXT
DONE

# Unit U-EL1q — Record table field layouts (checklist L1q pending part)

Goal (checklist L1q): decode field layouts of the 0x78/0x80/0x130/0x68 record tables. Texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 done per 6au — not this unit. Done previously (oc_U-EL1q_r1.md): 0x78 index-buffer records at renderer+0x93A178 [V], 0x80 vertex-buffer records at renderer+0x9B2178 [V], 0x68 framebuffer-window records at renderer+0xC97698 [V] (128 entries).

Pending part (this unit): 0x130 framebuffer-texture record whose pointer is held in the guard slot at renderer+0xA32178+handle*0x78 (createFrameBuffer 0xe816380). Fields +0x01..+0x12F to decode.

Method: full listing of createFrameBuffer 0xe816380, the slot destroyer sub_e80ef60, and the memcpy target sub_eec6ec0 inspected via rdis. Result:
- sub_eec6ec0 (0xeec6ec0) is a CFG-thunk: `jmp qword ptr [0xF9A8A98]` — real target not statically resolvable, so the attachment-descriptor memcpy at e81652f writes through r12 whose record-relative offset is unresolved (r12 = ([rax+0x1C]==2) ? [rax+0x10]+rsi : 0; rsi at e8164d2 unclear).
- createFrameBuffer 0xe816380 performs NO direct stores into record +0x01..+0x12F.
- sub_e80ef60 (destroyer, rcx=&slot) reads record+0x0C (4B, cmp 0xB) and record+0x58 (8B, released via sub_e92a8f0); it clears only SLOT fields (+0x00/+0x58/+0x5F/+0x68), not record fields.
- Only proven record-field accesses are reads at +0x00/+0x0C/+0x10/+0x1C/+0x58, tabled below verbatim from rdis.

| name | offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag |
|------|--------|------|------|-------------------------------|---------|-----|
| framebuffer-texture record +0x00 | +0x00 | 8 | createFrameBuffer 0xe816380 (record=rax=[rsp+0x48], alloc via sub_e8360f0 e8164bb) | `0xe8164dc  mov r15,[rax]` | qword read at entry; r15 passed as r9 to indirect call [rax+0x78] at e816560; attachment memcpy call 0xEEC6EC0 at e81652f writes r12 (record-relative dst offset unresolved) | [V] |
| framebuffer-texture record +0x0C | +0x0C | 4 | destroyer sub_e80ef60 (rcx=&slot) | `0xe80ef7c  mov r8d,[rcx+0xC]` | dword compared against 0xB at e80ef82 (record type check) | [V] |
| framebuffer-texture record +0x10 | +0x10 | 8 | createFrameBuffer 0xe816380 (record=rax) | `0xe8164ce  mov rcx,[rax+0x10]` | qword base; r12 = [rax+0x10]+rsi when [rax+0x1C]==2 (rsi at e8164d2 unresolved) | [V] |
| framebuffer-texture record +0x1C | +0x1C | 4 | createFrameBuffer 0xe816380 (record=rax) | `0xe8164d8  cmp dword ptr [rax+0x1C],2` | dword compared against 2 (type tag selecting the +0x10+rsi path) | [V] |
| framebuffer-texture record +0x58 | +0x58 | 8 | destroyer sub_e80ef60 (rcx=&slot) | `0xe80efb4  mov rdx,[rcx+0x58]` | qword resource released via sub_e92a8f0 at e80efbe | [V] |

CLOSES? NO — blocking fact: the 0x130 framebuffer-texture record fields +0x01..+0x12F are not provable by any [V] row: createFrameBuffer 0xe816380 writes the record only via the indirect call 0xEEC6EC0 (CFG thunk at data slot 0xF9A8A98) with an unresolved record-relative dst r12; sub_eec6ec0's real target cannot be resolved statically, and no other located function writes any record byte in +0x01..+0x12F. Only reads at +0x00/+0x0C/+0x10/+0x1C/+0x58 are [V]-proven above. The checklist item closes only when every pending offset has a [V] row; it does not.

## TOOL REQUESTS

None — all data from rdis dis of createFrameBuffer 0xe816380, sub_e80ef60, sub_eec6ec0.
