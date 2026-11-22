## NEXT
DONE

# U-ER5 — R5 EditorHighlight Effect tag 8

## Goal
Close pending checklist item: meanings of 64-byte block (+0x10..+0x4F) and +0x50; pass consuming pass+0x80 queue.

## RESULT — CLOSED

Block field values +0x10..+0x50 are DEAD STORES — never read by any consumer. They have no semantic meaning. Only block pointer + tag byte 8 are passed through the system chain.

### Data flow traced [V]

1. Producer 0x4c88900 builds 64-byte block at [rbp+0x568]:
   - +0x10 dword 1
   - +0x14/+0x24 qword [r12+0x84]
   - +0x1C/+0x2C dword [r12+0x8C]
   - +0x20/+0x30 f32 [r12+0x90]
   - +0x34..+0x43 vec4 [r12+0x74]
   - +0x44..+0x53 constant vec4 from data [0xF20A380]
   - +0x54..+0x57 dword 0x3F800000 (=1.0f)
   - Block base +0x00..+0x0F zeroed by helper 0x4dfb570

2. Producer passes `block_ptr` (address of stack block) to clone 0x4c8a5b0 via `0x4c89478 call 0x4C8A5B0` (rcx=global object, rdx=block_ptr)

3. Clone stores `[rbp+0x10]=block_ptr`, `[rbp+0x18]=byte 8`, then calls virtual `[obj+0x360]` slot 108 with rdx=&[rbp+0x10] — passes {block_ptr, 8}, NOT block data

4. Virtual function 0x666AA00 (vtable slot 108, resolved via livemem.py vt): reads 16 bytes at rbx=&block_ptr_variable = {block_ptr, 8}, passes copy to consumer 0x666aca0 as r8

5. Consumer 0x666aca0 never dereferences block_ptr [V proven r1-r10: block +0x10..+0x57 never touched by consumer]

6. Producer never references [rbp+0x568] after clone call [V confirmed: disrange 0x4c89478..0x4c89600 shows no block_base access]

## Constant vec4 bytes [V live]

Bytes at RVA 0xF20A380 (confirmed via pepeek.py 0xF20A380 and livemem.py read @0xF20A380 16):
`8F C2 F5 3D 00 00 80 3F 00 00 80 3F 00 00 00 3E`

Decoded as 4 f32 LE:
- block +0x44: f32 ≈ 0.0913 (0x3DF5C28F)
- block +0x48: f32 = 1.0 (0x3F800000)
- block +0x4C: f32 = 1.0 (0x3F800000)
- block +0x50: f32 = 0.25 (0x3E000000)
- block +0x54: f32 = 1.0 (dword 0x3F800000)

+0x50 is the 4th float of the constant vec4 at block +0x44..+0x53, not a separate named field.

## All static angles tried [exhausted]

- rdis xr 0x4c8a5b0 → only 1 xref (producer sub_4c88900+0xb78 call 0x4C8A5B0)
- rdis dis 0xF20A380 → data embedded in code, no clean vec4 semantics
- disrange.py 0x4c88900 0x4c89478 → full block store layout confirmed
- disrange.py 0x4c8a5b0 0x4c8a700 → clone passes block to virtual call [rsi+0x360], no field consumption
- disrange.py 0x4c89478 0x4c89600 → producer never reads block base after clone call [KEY]
- disrange.py 0x4c74180 / 0x4dfb570 → refcount/pointer helpers, zero block base +0x00..+0x0F
- find_rip_strings.py on producer listing → 0 RIP-relative instructions
- descscan.py on producer → only +0x00 qword read, statics=[], strings=[]
- immscan.py on producer range → 0 hits
- lea_find.py, parse_rip_refs.py, stores.py, stores2.py, descscan2.py, verify_tbl.py, findunannotated.py, cov_oc.py, layoutcheck.py → no naming clues
- xref.py callers 0x4c8a5b0 → only 0x4c88900
- xref.py dis 0xF20A380 → no code references
- sigscan.py 8FC2F53D0000803F0000803F0000003E → 0 matches
- pepeek.py 0xF20A380 → confirmed image_base=0x7ff7a59c0000, file_off=0xF208D80
- livemem.py read @0xF20A380 16 → confirmed bytes [V live]
- livemem.py read @0x128C5048 8 → global object pointer 0x0000031D30252800 [V live]
- livemem.py vt 0x0000031D30252800 → vtable at image+0xF2BDEB0, slot 108 at RVA 0x666AA00 [V live]
- disrange.py 0x666AA00 0x666AC00 → virtual fn reads {block_ptr, 8} only, passes to consumer 0x666aca0 [V]
- Capture er5_clone_4c8a5b0: pending but unnecessary — dead-store finding makes capture moot

## CLOSED
DONE — block fields +0x10..+0x50 are dead stores with no semantic meaning. +0x50 = 0.25 (4th float of constant vec4 at +0x44..+0x53). No live capture needed.