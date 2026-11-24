## NEXT
DONE: sub_bc7dc90 lifted to L1; liftcheck printed LIFTCHECK OK 0xbc7dc90; no open items.

## FILES
- docs/progress/oc_U-EX1.bc7dc90.md (this result file; created)
- docs/functions/bc7dc90.md (dossier with Reversed source (complete); created)
- src/client/features/render/native/bgfx/sub_bc7dc90.cpp (lifted source, first line `// LIFT 0xbc7dc90 size 0x13e 1.26.62.01 sub_bc7dc90`; created)
- src/client/features/render/native/bgfx/sub_bc7dc90.h (layout constants + static_asserts + forward declaration of native::sub_e935700; created)
No other files were created or changed (no edits to Sigs.json, shared headers, CMake, hooks, or other units).

## Summary of the lift
Function 0xbc7dc90, size 0x13e bytes ([0xbc7dc90, 0xbc7ddce)), x64 Microsoft ABI `extern "C" void sub_bc7dc90(BuilderState* a0 /*rcx*/)`, returns void. It clears two small strings ({ptr,size,cap} at +0x00/+0x10/+0x18 and +0xC8/+0xD8/+0xE0, SSO threshold capacity < 0x10), releases the +0xB8 single-owner object via vtable[4] (offset 0x20), and releases the +0x28 RefCounted (strong at +0x8, weak at +0xC; vtable[0] destroy, vtable[8] dealloc — same layout as ::native::RefCounted from sub_bc55ea0). Every branch is lifted, including the invalid-parameter cold path. Every instruction of [0xbc7dc90, 0xbc7ddce) is inside a cited `// 0xA..0xB` range; every `call` is quoted verbatim (`0xRVA  call ...`, two spaces) and matches the disassembly (verify_oc mismatch=0, no-such-instr=0). Layout constants with static_asserts live in the header; LIFT_FN registration in the .cpp; footprint {{a0, sizeof(BuilderState)}}.

Calls:
- 0xbc7dcd9, 0xbc7dd95: `call 0xE935700` → native::sub_e935700 (classified `lift` in docs/data/native_boundary.tsv; forward-declared in the header as `extern "C" uintptr_t sub_e935700(std::uint64_t, std::uint64_t)` and called by native symbol; body is `jmp 0x392960` → sub_392960, which invokes the global object at VA 0x15233E1A8 via vtable[2]; entry arg2 is dead in the callee).
- 0xbc7dd1b, 0xbc7dd44, 0xbc7dd5a: `call qword ptr [0xF99FFA0]` → data slot holds sub_eea6040 (`jmp rax` thunk, class vendor per docs/data/native_boundary.tsv); lifted as the virtual call through the vtable entry pre-loaded into rax (vt[4]/vt[0]/vt[8] with rcx = object), exactly as the sibling unit sub_bc2bca0 does for the same gadget.
- 0xbc7ddc7: `call qword ptr [0xF9A8C78]` → data slot (VA 0x14F9A8C78 = image base 0x140000000 + RVA 0xF9A8C78); target not statically known and not in either table, so per the indirect-call rule the pointer is read from the slot at call time and invoked with all five arguments zero, followed by `__debugbreak()` mirroring the trailing `int3`. UNRESOLVED CALL = none.

No stubs, no skipped branches, no [?]/[I]/TODO/UNVERIFIED tags, no null guards or SEH beyond the original's explicit tests.

## LIFTCHECK
LIFTCHECK OK 0xbc7dc90

## UNRESOLVED CALL
none

## TOOL REQUESTS
None

CLOSES? YES
