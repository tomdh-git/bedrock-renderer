## NEXT
DONE

## FILES
- docs/progress/oc_U-EX7.eec5850.md (this result file; created at step 1, now final)
- docs/functions/eec5850.md (created: dossier with signature, phases, callees, and 'Reversed source (complete)')
- src/client/features/render/native/helpers/sub_eec5850.cpp (created: first line `// LIFT 0xeec5850 size 0x6 1.26.62.01 sub_eec5850`, body, LIFT_FN registry entry)
- src/client/features/render/native/helpers/sub_eec5850.h (created: layout constants with static_asserts, signature declaration, std::_Xlength_error declaration with its real symbol)

## SUMMARY
Lifted sub_eec5850 (0xeec5850, 0x6 bytes, depth 0, D0, root, 0 callees in set): one instruction,
`0xeec5850  jmp qword ptr [0xF9A7320]`, an indirect tail jump through data slot 0xF9A7320.
[V] Slot 0xF9A7320 (.rdata, file off 0xf9a5d20) contains import-by-name RVA 0xF9AA680: hint 654
(0x028E), name `?_Xlength_error@std@@YAXPEBD@Z` = std::_Xlength_error(const char*) of the MSVC CRT.
[V] Callers prove the ABI: `sub rsp,0x28; lea rcx,<"too long" message>; call 0xEEC5850;` followed by
unreachable `int3` (e.g. 0x7572b "string too long", 0x75b6b "vector too long", 0xa4eab "map/set too
long", 0xab1db "deque<T> too long", 0x12d04b "vector<bool> too long") → void (const char*), RCX =
message, never returns (throws std::length_error).
No `call` instruction exists in [0xeec5850, 0xeec5856), so there are no call quotes and no callees;
the jmp is covered by the cited range `// 0xeec5850..0xeec5856` and verbatim-quoted in the #if 0 block.
The lifted body calls std::_Xlength_error(message) directly (same target the slot resolves to,
declared with its real symbol, per the sub_eec59e0 pattern for this same forwarder family).
No struct fields are touched; only the x64 ABI contract is asserted (sizeof(void*) == 8,
sizeof(function pointer) == 8). No stubs, no skipped branches, no [?]/[I]/TODO/UNVERIFIED tags in
source or reversed-source block, no null guards/SEH (the original has none).

## LIFTCHECK
LIFTCHECK OK 0xeec5850

## UNRESOLVED CALL
none: the function contains no call instruction; the indirect jump target (std::_Xlength_error via
data slot 0xF9A7320) is resolved from the PE import table and declared with its real symbol, so it
is neither an external call nor an unresolved callee.

CLOSES? YES
