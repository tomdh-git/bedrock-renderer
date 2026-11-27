# Dossier: sub_ebdbf20 (0xebdbf20)

Target: Minecraft Bedrock 1.26.62.01 (`C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`), RVAs relative to the image base.
Source artifact: `src/client/features/render/native/helpers/sub_ebdbf20.cpp` + `.h`.

## Signature guess
`void sub_ebdbf20(void* a0);`  // x64 Microsoft ABI: a0 in RCX, result in RAX (forwarded as-is from the slot target).

## Register / argument map
- RCX = a0: a caller-supplied pointer, passed straight through to the slot target (not dereferenced by this function).
- RAX = result: whatever the slot target leaves in RAX (return value unused by every caller).
- No other argument registers are set up by this function; it is a pure tail-forward.

## Disassembly (function span 0xebdbf20..0xebdbf27, size 0x7)

Phase 0xebdbf20..0xebdbf27 — the entire function is one indirect tail jump through data slot 0xF9A7B28:
```
// 0xebdbf20..0xebdbf27
// 0xebdbf20  jmp qword ptr [0xF9A7B28]   ; [data_f9a7b28]
```
Semantics: load the 8-byte function pointer stored at data slot RVA 0xF9A7B28 and tail-jump to it (REX.W `48 FF 25 <disp32>` = exactly 7 bytes, 0xebdbf20..0xebdbf26; the next instruction pointer would be 0xebdbf27). Equivalent C++: read `*(void**)(imageBase + 0xF9A7B28)`, call it with a0 in RCX, return its RAX result.

The bytes 0xebdbf27..0xebdbf2f are `int3` padding past the 7-byte function span (not part of the function; [V: rdis dis, `ebdbf27 int3`]).

## Verbatim instruction quote (checked against the exe)
```
0xebdbf20  jmp qword ptr [0xF9A7B28]                     ; [data_f9a7b28]
```

## Struct fields touched
None. The function reads no struct field and writes no memory. The only memory access is the 8-byte read of the data slot at 0xF9A7B28.

Layout constants (asserted in `sub_ebdbf20.h`, `sub_ebdbf20Layout`):
- `sizeof(void*) == 8` — x64 ABI, pointer-sized argument in RCX and result in RAX.

## Callees
There are no `call` instructions in the function (it is a `jmp`, not a call), so there are no static callees.
The indirect jump target is the pointer stored at data slot RVA `0xF9A7B28`. At static/image time that slot holds `0xF9AC476` (a non-code value in .rdata); the slot is loader/runtime-resolved to the real target, so the target is not statically knowable and is not a lift-set or boundary callee.
Per the hard rule for indirect calls through data slots, this is not a blocker: the lifted code reads the pointer from the slot at call time and calls it as a function pointer with the same arguments, documenting the slot RVA `0xF9A7B28`; no wrapper is invented.
- CALLEES IN THE LIFT SET: none (input data row lists none).
- Boundary: none (no `call`; the data-slot indirect jump is documented above, not an unresolved call).

## Reversed source (complete)
```
// LIFT 0xebdbf20 size 0x7 1.26.62.01 sub_ebdbf20
// 0xebdbf20..0xebdbf27  jmp qword ptr [0xF9A7B28]   ; tail jump through loader-resolved data slot 0xF9A7B28
void sub_ebdbf20(void* a0) {
    static_assert(sizeof(void*) == 8, "sub_ebdbf20: x64 ABI, pointer-sized argument in RCX and result in RAX");
    using Fn = void (*)(void*);
    return reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A7B28ull))(a0);   // 0xebdbf20  jmp qword ptr [0xF9A7B28]   ; 8-byte load from the slot, tail jump, RAX result as-is
}
```

## Ownership / threading
No memory is written by this function, so it has no ownership or threading side-effects of its own. Thread-safety of the slot target is the target's concern.

## Version anchors
- Game: 1.26.62.01.
- Slot RVA: 0xF9A7B28 (sibling slots: 0xF9A7B10 for sub_ebdbf10, 0xF9A7B60 used by sub_ebdbc60).

## OPEN questions
- None. The function is a single indirect tail jump through a loader-resolved data slot; the target is intentionally not resolved statically (per the data-slot hard rule) and the slot RVA is documented.

## Verification
- `docs/progress/oc_U-EX7.ebdbf20.md` carries the liftcheck result and `CLOSES?`.
