## NEXT
DONE

## SUMMARY
LIFTed sub_eec59f0 (0xeec59f0, size 0x6, depth 0, D0, 0 callees in set) — Minecraft Bedrock 1.26.62.01.

Facts (all [V] from disassembly / PE import table):
- 0xeec59f0  jmp qword ptr [0xF9A75A8]      ; [data_f9a75a8]   — one instruction, size 0x6, then int3 padding at 0xeec59f6
- Data slot 0xF9A75A8 (.rdata) = MSVCP140.dll IAT slot index 160; on-disk content import-by-name RVA 0xF9AB92C, hint 1413, name _Mtx_lock
- Call sites confirm the signature: 0x7e9d1  mov rcx,rbx / 0x7e9d4  call 0xeec59f0 ; 0x7ef00  lea ecx,[0x128CBD78] / 0x7ef06  call 0xeec59f0  -> void(struct _Mtx*), RCX = mutex pointer, void return
- Tail jump: the argument is forwarded as-is and control never returns to the caller

Lifted as native::sub_eec59f0 via the data-slot rule (call the import target through its declared signature, slot documented), mirroring sibling unit sub_eec59e0.

## FILES
src/client/features/render/native/helpers/sub_eec59f0.h   (new: layout constants, static_asserts, signature, _Mtx_lock declaration)
src/client/features/render/native/helpers/sub_eec59f0.cpp (new: LIFT marker, lifted body, verbatim quote, LIFT_FN registry entry)
docs/functions/eec59f0.md                                  (new: dossier with Reversed source (complete))
docs/progress/oc_U-EX7.eec59f0.md                          (this result file)

## LIFTCHECK
LIFTCHECK OK 0xeec59f0

## UNRESOLVED CALL
none

CLOSES? YES
