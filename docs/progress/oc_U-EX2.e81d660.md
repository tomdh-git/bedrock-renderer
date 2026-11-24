## NEXT
DONE.

## DONE
LIFT 0xe81d660 "D3D12 submit RTX override" (sub_e81d660), size 0x1af, depth 2, region d3d12, D0.
- Signature: std::uint32_t sub_e81d660(void* this, void* a1, std::uint32_t a2, std::uint32_t a3) — x64 ABI (rcx/rdx/r8d/r9d -> rax).
- Records one submit slot into a 3-cursor ring of the per-job D3D12 context, bumps counter[a2], fills record[tail] (a2/a3), fires a CFG-guarded virtual call on a1->[0x30] vtable slot 0x1A8, advances the tail, releases the submit lock, returns the entry-time tail.
- Callees: sub_eec59f0 / sub_eec5a00 / sub_eec5a10 are `lift` (jmp-thunks; forward-declared in the header, sub_eec5a00 marked [[noreturn]] per the int3-padded fatal path). sub_eea6040 is a `vendor` jmp-rax guard thunk via data slot 0xF99FFA0 (CFG-guarded virtual call), lifted as a direct call to the resolved vtable target.

## FILES
- docs/functions/e81d660.md (created)
- src/client/features/render/native/d3d12/sub_e81d660.h (created)
- src/client/features/render/native/d3d12/sub_e81d660.cpp (created)
- docs/progress/oc_U-EX2.e81d660.md (this file)

## LIFTCHECK
```
$ python tools/sigs/liftcheck.py 0xe81d660
LIFTCHECK OK 0xe81d660
```

## UNRESOLVED CALL
none — every call target is either lifted (sub_eec59f0, sub_eec5a00, sub_eec5a10, all classified `lift` in docs/data/native_boundary.tsv + native_functions.tsv) or a vendor boundary (sub_eea6040, `jmp rax` guard thunk via data slot 0xF99FFA0, classified `vendor` in native_boundary.tsv). The 0xe81d791 indirect call is the documented data-slot dispatch: the slot holds sub_eea6040 (`jmp rax`), rax = vtable[0x1A8] (0xe81d781/0xe81d784), so it invokes vtable[0x1A8](a1->[0x30], this->[0x7828], 2, tail*2).

## Checklist
X2.e81d660 LIFT sub_e81d660 (0xe81d660, 0x1af bytes, depth 2, D0, 0 callees in set)

## TOOL REQUESTS
None.

CLOSES? YES