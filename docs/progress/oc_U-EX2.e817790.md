## NEXT
DONE

## FILES
- docs/progress/oc_U-EX2.e817790.md (this result file)
- docs/functions/e817790.md (dossier; new — mechanical facts, signature, Reversed source (complete))
- src/client/features/render/native/d3d12/sub_e817790.cpp (new — lifted body + LIFT_FN registry entry)
- src/client/features/render/native/d3d12/sub_e817790.h (new — E817790Registry/E817790PerKey/E817790Slot layouts with static_asserts, constants, ABI)

## SUMMARY
X2.e817790 LIFT sub_e817790 (0xe817790, 0xe8 bytes, depth 1, D0, 0 callees in set)

Lifted RendererContextD3D12 base slot 40 (`sub_e817790`), size 0xe8, into
`src/client/features/render/native/d3d12/sub_e817790.{h,cpp}`. Signature
`extern "C" void sub_e817790(void* self, std::uint16_t key, std::uint32_t value)` (rcx/rdx/r8d),
proved by the caller at 0xe8176a0 (0xe817703..0xe817708: edx=handle, r8d=0). The body:
bounds-check key<=0x7F, set present[key>>6] bit + append key to keyList/count if new, store value
into perKey[key].v0/v1, then if self->slots[key].connection != null make three guarded virtual
calls (vtable +0x120 -> byte, +0x48 with that byte and &0xF4ED2C0 and &outLocal, +0x10 on outLocal
if non-null), then the /GS cookie epilogue.

## LIFTCHECK
```
LIFTCHECK OK 0xe817790
```

## CALL TARGETS
- 0xe817813 / 0xe817833 / 0xe81784a: `call qword ptr [0xF99FFA0]`. Slot 0xF99FFA0 holds
  sub_eea6040 (`jmp rax`; docs/data/native_boundary.tsv class vendor, "thunk via data slot 0xF99FFA0");
  rax is loaded from connection vtable slots 0x120 / 0x48 / 0x10 immediately before each call, so each
  is a guarded (CFG) virtual call. Expressed as the resolved vtable-slot invocation (identical to the
  jmp-rax chain). Indirect-through-data-slot: not a blocker.
- 0xe817872: `call 0xE951550` = sub_e951550, __security_check_cookie (docs/data/native_boundary.tsv class crt).

## UNRESOLVED CALL
none

## TOOL REQUESTS
None.

CLOSES? YES