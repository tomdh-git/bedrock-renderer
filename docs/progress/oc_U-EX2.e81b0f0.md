## NEXT
DONE

## FILES
- docs/functions/e81b0f0.md (created)
- src/client/features/render/native/d3d12/sub_e81b0f0.h (created)
- src/client/features/render/native/d3d12/sub_e81b0f0.cpp (created)
- docs/progress/oc_U-EX2.e81b0f0.md (this file)

## LIFTCHECK
Command: `python tools/sigs/liftcheck.py 0xe81b0f0`
Output:
```
LIFTCHECK OK 0xe81b0f0
```

## UNRESOLVED CALL
none

Checklist line: X2.e81b0f0 LIFT sub_e81b0f0 (0xe81b0f0, 0x14b bytes, depth 0, D0, 0 callees in set)

Calls in the function (all lifted-or-boundary):
- `0xe81b119  call qword ptr [0xF99FFA0]` — guarded virtual call, target self->vtable[0x1E8] (slot 0xF99FFA0 = sub_eea6040, vendor CFG thunk; native_boundary.tsv row 0xeea6040).
- `0xe81b1f9  call qword ptr [0xF99FFA0]` — guarded virtual call, target self->[0xCC9268]->vtable[0x50] (same thunk slot).
- `0xe81b235  call 0xE951550` — sub_e951550 = __security_check_cookie (crt boundary; native_boundary.tsv row 0xe951550).

CLOSES? YES