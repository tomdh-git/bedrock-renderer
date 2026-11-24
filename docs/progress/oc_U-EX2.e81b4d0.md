## NEXT
DONE

## DONE
X2.e81b4d0 LIFT setVertexBuffers (per-draw vertex buffer views + transitions), fully reversed (0xe81b4d0, 0x24f bytes, depth 2, D2, 0 callees in set). Lifted source: src/client/features/render/native/d3d12/setVertexBuffers.cpp + setVertexBuffers.h (layout constants, static_asserts, exact x64 ABI signature, LIFT_FN registry entry). Dossier Reversed source section rewritten instruction-complete with range citations and both verbatim call quotes. Both callees are boundary functions: 0xe951550 (crt __security_check_cookie) and the CFG-guarded virtual call at 0xe81b606 -> sub_eea6040 (vendor jmp-rax thunk, vtable slot 0xD0 = ID3D12GraphicsCommandList::ResourceBarrier).

## FILES
- docs/progress/oc_U-EX2.e81b4d0.md (this file)
- docs/functions/e81b4d0.md (replaced 'Reversed source (complete)' section)
- src/client/features/render/native/d3d12/setVertexBuffers.h (new)
- src/client/features/render/native/d3d12/setVertexBuffers.cpp (new)

## LIFTCHECK
$ python tools/sigs/liftcheck.py 0xe81b4d0
LIFTCHECK OK 0xe81b4d0

## UNRESOLVED CALL
none
- 0xe81b606  call qword ptr [0xF99FFA0]  -> CFG-guarded virtual call; slot 0xF99FFA0 holds sub_eea6040 (native_boundary.tsv class=vendor, "thunk via data slot 0xF99FFA0 (loader-resolved)"), whose only instruction is `jmp rax` (0xeea6040). Target preloaded from command-list vtable slot 0xD0 (ResourceBarrier) at 0xe81b5f5. Boundary.
- 0xe81b719  call 0xE951550  -> __security_check_cookie, native_boundary.tsv class=crt. Boundary.

## TOOL REQUESTS
None.

CLOSES? YES