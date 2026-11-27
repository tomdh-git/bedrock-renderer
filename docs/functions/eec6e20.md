# Function 0xEEC6E20 (sub_eec6e20)

## Signature
```cpp
extern "C" void sub_eec6e20(void* dest, const void* src);
```

## Register/Argument Map
| Register | Argument | Meaning |
|----------|----------|---------|
| RCX      | dest     | Destination pointer (first argument) |
| RDX      | src      | Source pointer (second argument) |
| RAX      | -        | Not used for return (tail call) |

Calling convention: Microsoft x64 ABI. Two arguments in RCX, RDX. Tail call via `jmp` - no return to this function.

## Disassembly Phases

### 0xEEC6E20..0xEEC6E26: Indirect tail call through IAT
```asm
0xeec6e20  jmp qword ptr [0xF9A8A48]                     ; [data_f9a8a48]
```
- Reads 64-bit function pointer from IAT slot at RVA 0xF9A8A48
- Performs unconditional tail jump to that address
- The IAT slot initially points to import name `__std_exception_copy`; loader patches with actual CRT address
- Arguments (RCX, RDX) passed through unchanged to target
- No stack frame, no prologue/epilogue

C++ equivalent:
```cpp
auto* iat_slot = reinterpret_cast<StdExceptionCopyFn*>(0xF9A8A48);
StdExceptionCopyFn target = *iat_slot;
target(dest, src); // tail call semantics approximated by regular call
```

## Struct Fields Touched
None (no memory reads/writes except the IAT slot read)

## Callees
| RVA | Target | Class | Tag |
|-----|--------|-------|-----|
| 0xF9A8A48 (slot) | `__std_exception_copy` (CRT) | crt (boundary) | [V] |

The call is an indirect `jmp` through the IAT slot at 0xF9A8A48. The target is a CRT function (`__std_exception_copy`), classified as `crt` boundary. In lifted code, invoked via function pointer read from the documented slot.

## Ownership / Threading
- Stateless trampoline; no object ownership
- Thread-safe: pure forwarding, no shared mutable state
- Called from multiple contexts (80+ callers) for exception object copying

## Version Anchors
- 1.26.62.01: RVA 0xEEC6E20, size 0x6, IAT slot 0xF9A8A48 → `__std_exception_copy`
- Part of C++ exception handling thunk table (0xEEC6E20..0xEEC760E, 0x7EE bytes, 126 entries)

## Verification
- Instruction coverage: 100% (6 bytes, single instruction)
- Call quote: `0xeec6e20  jmp qword ptr [0xF9A8A48]`
- No `[?]`/`[I]`/`TODO`/`UNVERIFIED` tags
- Layout constant `kIatStdExceptionCopy` asserted in header
- Registry entry `LIFT_FN_EEC6E20` defined

## Reversed source
```cpp
// LIFT 0xeec6e20 size 0x6 1.26.62.01 sub_eec6e20
#include "sub_eec6e20.h"

namespace native {

// 0xeec6e20..0xeec6e26
// 0xeec6e20  jmp qword ptr [0xF9A8A48]                     ; [data_f9a8a48]
extern "C" void sub_eec6e20(void* dest, const void* src) {
    // Indirect tail call through IAT slot at 0xF9A8A48 (__std_exception_copy)
    // The loader patches this slot with the actual CRT function address.
    // We replicate by reading the function pointer and calling it.
    // 0xeec6e20  jmp qword ptr [0xF9A8A48]
    auto* iat_slot = reinterpret_cast<StdExceptionCopyFn*>(kIatStdExceptionCopy);
    StdExceptionCopyFn target = *iat_slot;
    target(dest, src);
}

} // namespace native

// Verbatim instruction quotes for liftcheck
#if 0
0xeec6e20  jmp qword ptr [0xF9A8A48]
#endif
```

## Open Questions
- None - all behavior documented and lifted