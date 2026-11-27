## NEXT
DONE

## UNIT
U-EX2.e8189c0: LIFT sub_e8189c0 (0xe8189c0, 0xa1 bytes, depth 0, D0, 1 callees in set: X7.ebce650; plus X7.ebce5e0 lift-set forward declaration; crt boundary sub_e951550)

## FILES
- docs/progress/oc_U-EX2.e8189c0.md (created; this file)
- docs/functions/0xe8189c0.md (extended; added 'Reversed source (complete)' section)
- src/client/features/render/native/d3d12/sub_e8189c0.h (new; RendererContextD3D12 partial layout, layout constants + static_asserts, ABI signature, lift-set callee forward declaration)
- src/client/features/render/native/d3d12/sub_e8189c0.cpp (new; first line `// LIFT 0xe8189c0 size 0xa1 1.26.62.01 sub_e8189c0`, reversed body with range citations, verbatim call quotes, boundary wrapper, LIFT_FN registry entry, footprint)

## SUMMARY
Disassembled 0xe8189c0..0xe818a61 (0xa1 bytes, pdata-proven). Calls: 0xe8189ff call 0xEBCE5E0 (sub_ebce5e0, lift-set; forward-declared in native::d3d12 per native_boundary.tsv row 504), 0xe818a32 call 0xEBCE650 (sub_ebce650, lift-set; header native/helpers/sub_ebce650.h; ABI: int sub_ebce650(char* dst, int dstSize, SrcDesc* srcdesc, int maxlen)), 0xe818a5b call 0xE951550 (sub_e951550, crt boundary row 467; native::boundary::sub_e951550(std::uintptr_t cookie)). Writes desc {ptr, maxlen} at this + index*0x100 + 0x7EDE via sub_ebce650(dst, 0xFA, &desc, 0x7FFFFFFF); default descriptor {&data_f847a07, 0} when name null or length 0; stack cookie from [0x1230A0C0] with sub_e951550 + int3 fail path. Lifted as void sub_e8189c0(RendererContextD3D12* ctx, uint16_t index, const char* name) noexcept in namespace native::d3d12, footprint = [ctx + 0x7EDE + index*0x100, 0xFA). No stubs, no skipped branches, no guards the original lacks. cppsyntax OK; verify_oc mismatch=0 no-such-instr=0.

## LIFTCHECK
LIFTCHECK OK 0xe8189c0

## UNRESOLVED CALL
none

## TOOL REQUESTS
None

CLOSES? YES
