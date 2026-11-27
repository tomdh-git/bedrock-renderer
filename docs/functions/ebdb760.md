# Dossier: sub_ebdb760 (0xebdb760, size 0x19, 1.26.62.01)

## Signature guess
`extern "C" uint64_t sub_ebdb760(void);` — x64 Microsoft ABI, no register arguments on entry (RCX is overwritten by the lea before it is read), 8-byte return value in RAX.

## Register / argument map
- RCX: clobbered by `lea rcx,[rsp+0x30]` before any read; not an incoming argument.
- RAX: holds the return value (`[rsp+0x30]` contents) at `ret`.
- RSP: frame pointer for the local buffer at `[rsp+0x30]` after `sub rsp,0x28`.

## Disassembly phases ([0xebdb760, 0xebdb779))
- `0xebdb760..0xebdb764`: `sub rsp,0x28` — reserve 32 bytes of stack space.
- `0xebdb764..0xebdb769`: `lea rcx,[rsp+0x30]` — RCX = address of the stack qword buffer (callee out argument).
- `0xebdb769..0xebdb76f`: `call qword ptr [0xF9A7CA0]` — indirect call through the loader-resolved data slot 0xF9A7CA0; the callee fills `*RCX`. The callee's return value (RAX) is discarded.
- `0xebdb76f..0xebdb774`: `mov rax,[rsp+0x30]` — RAX = the qword the callee wrote.
- `0xebdb774..0xebdb778`: `add rsp,0x28` — restore the stack pointer.
- `0xebdb778..0xebdb779`: `ret` — return RAX.
The int3 padding at `0xebdb779..0xebdb780` lies past the 0x19-byte function span [V: rdis dis 0xebdb760 0x19].

## Struct fields touched
None. The function reads/writes only its own stack frame and the data slot; no struct field offsets are used. Layout constants: `sizeof(void*)==8`, `sizeof(uint64_t)==8` (asserted in `sub_ebdb760.h`).

## Callees
- `0xebdb769  call qword ptr [0xF9A7CA0]` — indirect call through data slot 0xF9A7CA0 (loader-resolved import slot). Per the data-slot indirect-call rule the pointer is read from `imageBase() + 0xF9A7CA0` at call time and invoked as `uint64_t (*)(uint64_t* out)` with `RCX = &buf`. Not a boundary wrapper and not a lift-set callee; the target address comes from the slot at runtime [V: rdis dis 0xebdb760 0x19; PE .rdata slot at RVA 0xF9A7CA0]. Depth 0, 0 callees in the lift set.

## Ownership / threading
Leaf, no synchronization, no thread-shared state touched except through the data-slot callee (behavior of the callee is outside this unit). Pure from this function's perspective: no memory write observable outside its own stack frame.

## Version anchors
Minecraft Bedrock 1.26.62.01 (`C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`), RVAs relative to image base 0x140000000.

## Reversed source (complete)
```cpp
// LIFT 0xebdb760 size 0x19 1.26.62.01 sub_ebdb760
// (body in src/client/features/render/native/helpers/sub_ebdb760.cpp)

uint64_t sub_ebdb760_lifted(void) {
    // 0xebdb760..0xebdb764:  sub rsp,0x28   [0xebdb760  sub rsp,0x28]
    // 0xebdb764..0xebdb769:  lea rcx,[rsp+0x30]   [0xebdb764  lea rcx,[rsp+0x30]]
    uint64_t buf = 0;
    // 0xebdb769..0xebdb76f:  call qword ptr [0xF9A7CA0]   [0xebdb769  call qword ptr [0xF9A7CA0]]
    Ebdb760Callee fn = reinterpret_cast<Ebdb760Callee>(
        *reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A7CA0ull));
    fn(&buf);
    // 0xebdb76f..0xebdb774:  mov rax,[rsp+0x30]   [0xebdb76f  mov rax,[rsp+0x30]]
    // 0xebdb774..0xebdb778:  add rsp,0x28   [0xebdb774  add rsp,0x28]
    // 0xebdb778..0xebdb779:  ret   [0xebdb778  ret]
    return buf;
}

// Verbatim call instruction of the function:
0xebdb769  call qword ptr [0xF9A7CA0]
```

## Verification
- verify_oc: every quoted `0xRVA  instr` line matches rdis dis output for 0xebdb760.
- liftcheck: coverage of [0xebdb760, 0xebdb779) via cited ranges + verbatim call quote; LIFT marker; LIFT_FN registry entry; static_asserts present.

OPEN: none.
