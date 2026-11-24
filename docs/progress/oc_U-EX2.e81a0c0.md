## NEXT
DONE — U-EX2.e81a0c0 LIFT complete. sub_e81a0c0 lifted at L1 (liftcheck OK). Files: src/client/features/render/native/d3d12/sub_e81a0c0.{h,cpp}, docs/functions/e81a0c0.md.

X2.e81a0c0 LIFT sub_e81a0c0 (0xe81a0c0, 0x54a bytes, depth 1, D0, 0 callees in set)

## FILES
- docs/progress/oc_U-EX2.e81a0c0.md (this result file)
- docs/functions/e81a0c0.md (dossier; added 'Reversed source (complete)')
- src/client/features/render/native/d3d12/sub_e81a0c0.h (new: layout view struct S81a0c0 + offsetof/sizeof static_asserts + extern "C" signature)
- src/client/features/render/native/d3d12/sub_e81a0c0.cpp (new: full lift; first line `// LIFT 0xe81a0c0 size 0x54a 1.26.62.01 sub_e81a0c0`; registry via LIFT_FN)

## WHAT IT DOES
RendererContextD3D12 base slot 60 (this=rcx). Resets two container buffers (each a {first,last,end}
triple at +0x48/+0x50/+0x58 and +0x68/+0x70/+0x78): walks each buffer's intrusive linked list
(next at node+0x10) — vecA also calls obj->vtable[2](obj) per node (obj=node->[8]) before freeing —
frees every node and the old buffer via the global allocator g->vtable[1], and reallocates a zeroed
0x48-byte (9-slot) region (last=first+0x48). Zeros this->+0x40 and this->+0x60. Finally reads
count = ((uint16_t*)this->p08)[1], frees the old index buffer this->p08, allocates count*4+4 bytes,
and fills it as an identity map [0]=0, [1]=count, [2+i]=i (uint16 lanes; original uses SIMD movdqa
from .rdata constants 0xF441430/0xF08ED30/0xF441630/0xF441640/0xF441650, verified [V] to produce the
same identity sequence), then stores this->p08 = new buffer.

## LIFTCHECK
```
LIFTCHECK OK 0xe81a0c0
```
(command: `python tools/sigs/liftcheck.py 0xe81a0c0`, exit 0)

## UNRESOLVED CALL
none — all 9 calls are `call qword ptr [0xF99FFA0]`, a loader-resolved CFG thunk (sub_eea6040 = `jmp rax`,
data slot 0xF99FFA0), classified `vendor` in docs/data/native_boundary.tsv (line 506). The preloaded rax
(allocator/object vtable entry) is the effective callee; modeled as an indirect call through that vtable
entry, documenting the slot. No lifted-set callees (input data callees_in_set empty).

## TOOL REQUESTS
readconst.py | inline PE section-table parse of Minecraft.Windows.exe -> read N bytes at an RVA (used to dump the five SIMD fill constants 0xF441430/0xF08ED30/0xF441630/0xF441640/0xF441650) | a general `rdis data <rva> <n>` / hex-dump command would have avoided hand-parsing the PE headers to read .rdata constants.

CLOSES? YES