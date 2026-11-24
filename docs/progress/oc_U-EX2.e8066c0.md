## NEXT
DONE: sub_e8066c0 lifted; liftcheck printed LIFTCHECK OK 0xe8066c0; CLOSES? YES.

## FILES
created: src/client/features/render/native/d3d12/sub_e8066c0.h
created: src/client/features/render/native/d3d12/sub_e8066c0.cpp
created: docs/functions/e8066c0.md
created: docs/progress/oc_U-EX2.e8066c0.md

## SUMMARY
LIFTED sub_e8066c0 (0xe8066c0, size 0x11c, depth 1, milestone D0, region d3d12, name RendererContextD3D12 base slot 26).
Signature (x64 Microsoft ABI): extern "C" void* sub_e8066c0(void* out, const void* src) — rcx=out (32-byte scratch string object returned unchanged), rdx=src (uint16 read at [src+0x0], zero-extended to uint32).
Prologue saves rbp,r15,r14,rsi,rdi,rbx; frame rsp-0x48 with rbp=rsp+0x40.
Body:
- 0xe8066c0..0xe8066e6: movzx edx,word ptr [rdx] (src+0x0); call 0xE834520 (&tmp, v) writes tmp.data[16], tmp.size, tmp.cap.
- 0xe8066eb..0xe80671c: read size=tmp.size, cap=tmp.cap; if (cap - size < 9) call 0xE834330(&tmp, 9, (void*)0xF848D1A, (void*)9); jmp to store phase.
- 0xe806720..0xe8067bb: else tmp.size = size + 9; compute r15 = 9 or (tmp.data - 0xF848D1A)>>1 or 0 based on comparisons vs 0xF848D2C ("LVbo:" region) and 0xF848D1A ("LTexture: "); call 0xEEC6DE0(tmp.data+0x12, tmp.data, size*2+2); call 0xEEC6EC0(tmp.data, 0xF848D1A, r15*2); call 0xEEC6EC0(tmp.data+r15*2, 0xF848D1A+r15*2+0x12, 0x12 - r15*2).
- 0xe8067bd..0xe8067dc: movups [rsi+0x10] = {size,cap}; movups [rsi] = data[16]; mov rax,rsi; ret. Store order: size/cap first, then data.
No null guards or SEH (original has none).

Callees (all in lift set / classed lift):
- 0xe834520 void* sub_e834520(void*, std::uint32_t) [V] header sub_e834520.h
- 0xe834330 void* sub_e834330(void*, std::size_t, void*, void*) [V] header sub_e834330.h (global scope)
- 0xeec6de0 void sub_eec6de0(void*, void*, std::uint64_t) lift (native_boundary.tsv line 523, size 6, jmp qword ptr [0xF9A8AA0])
- 0xeec6ec0 void* sub_eec6ec0(void*, const void*, std::size_t) lift (native_boundary.tsv line 512, size 6, jmp qword ptr [0xF9A8A98])
No unresolved calls.

Layout constants + static_asserts for Str32 ({char data[16]; size_t size; size_t cap;}, sizeof 0x20) in sub_e8066c0.h.
Registry entry: LIFT_FN(sub_e8066c0, "sub_e8066c0", 0xe8066c0, sub_e8066c0, sub_e8066c0_footprint) in sub_e8066c0.cpp (footprint = {out, 0x20}).

## LIFTCHECK
LIFTCHECK OK 0xe8066c0

## UNRESOLVED CALL
none

CLOSES? YES
