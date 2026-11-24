## NEXT
DONE U-EX2.e81b3b0 LIFT sub_e81b3b0

## FILES
- src/client/features/render/native/d3d12/sub_e81b3b0.h (created)
- src/client/features/render/native/d3d12/sub_e81b3b0.cpp (created)
- docs/functions/e81b3b0.md (created)

## LIFTCHECK
```
$ python tools/sigs/liftcheck.py 0xe81b3b0
LIFTCHECK OK 0xe81b3b0
```

## UNRESOLVED CALL
none

## NOTES
- 0xe81b3b0, size 0x118, depth 1, region d3d12, status D0, "RendererContextD3D12 base slot 7".
- Signature `extern "C" bool sub_e81b3b0(void* self)` — sole arg in rcx; returns bool = (id != -1).
- Three call sites, all resolved:
  - `0xe81b3d8 / 0xe81b430 / 0xe81b47c  call qword ptr [0xF99FFA0]` — jmp-rax thunk sub_eea6040; modeled as the resolved vtable-slot virtual call (slot 0x40 on idSource, slot 0x10 on each element's sub38).
  - `0xe81b4b5  call 0xEEC59E0` — sub_eec59e0 = _Xbad_function_call (class lift, called as boundary here; extern "C" forward decl).
  - `0xe81b4c2  call 0xE951550` — sub_e951550 = __security_check_cookie (native::Boundary crt).
- Checklist: X2.e81b3b0 LIFT sub_e81b3b0 (0xe81b3b0, 0x118 bytes, depth 1, D0, 0 callees in set)

CLOSES? YES