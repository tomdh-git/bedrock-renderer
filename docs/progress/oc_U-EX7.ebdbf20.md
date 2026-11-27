## NEXT DONE

Unit: U-EX7.ebdbf20 — function 0xebdbf20, size 0x7 bytes, depth 0, milestone D0, region root, 0 callees in set.
INPUT DATA (docs/progress/_d_U-EX7.ebdbf20.txt): row `0xebdbf20 0x7 0 7 root D0 added 0xebdbf20`; CALLEES IN THE LIFT SET: none; boundary.tsv row `0xebdbf20 lift auto-unresolved->lift`.

## DISASSEMBLY (gathered, [V] from rdis dis)
Function 0xebdbf20 is exactly one 7-byte indirect tail jump through data slot 0xF9A7B28:
```
ebdbf20  jmp qword ptr [0xF9A7B28]                     ; [data_f9a7b28]
ebdbf27  int3   (padding past the 7-byte span)
```
The `jmp qword ptr [0xF9A7B28]` is the REX.W `48 FF 25 <disp32>` form = exactly 7 bytes (0xebdbf20..0xebdbf26), matching the input size 0x7. There is NO `call` instruction, no struct field access, no memory write, and no `.pdata` entry. rcx (a0) is a caller-supplied pointer passed straight through; rax result is the slot target's result (unused by callers; verified at call sites 8b9c233, bc65085, bc687dd, bc68633).

## DATA SLOT (read statically from the exe, read-only PE parse — not launched)
Slot 0xF9A7B28 holds u64 = 0xF9AC476 at image time (siblings: [0xF9A7B10]=0xF9AC41A for sub_ebdbf10, [0xF9A7B60]=0xF9AC50C used by sub_ebdbc60). These values are non-code (.rdata) and are loader/runtime-resolved to the real target, so the target is not statically knowable — exactly the "indirect call through data slot" hard-rule case: read the pointer from the slot at call time, call it as a function pointer with the same arguments, document slot RVA 0xF9A7B28; no wrapper invented, not an unresolved call. [V: rdis dis/sum, PE section parse of Minecraft.Windows.exe]

## FILES created
- docs/progress/oc_U-EX7.ebdbf20.md (this result file)
- docs/functions/ebdbf20.md (dossier: analysis + Reversed source (complete))
- src/client/features/render/native/helpers/sub_ebdbf20.cpp (first line `// LIFT 0xebdbf20 size 0x7 1.26.62.01 sub_ebdbf20`, body + LIFT_FN registry entry)
- src/client/features/render/native/helpers/sub_ebdbf20.h (layout constants + static_asserts + signature)

## LIFTCHECK
`LIFTCHECK OK 0xebdbf20`

## UNRESOLVED CALL
none — the function contains no `call` instruction; its single `jmp` is an indirect tail jump through documented data slot 0xF9A7B28 (hard-rule data-slot case, not a blocker).

CLOSES? YES
