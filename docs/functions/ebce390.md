# sub_ebce390 (0xebce390, size 0x5, 1.26.62.01)

## Source
src/client/features/render/native/helpers/sub_ebce390.cpp with header src/client/features/render/native/helpers/sub_ebce390.h. First line of the .cpp: `// LIFT 0xebce390 size 0x5 1.26.62.01 sub_ebce390`. Registry entry: `LIFT_FN(sub_ebce390, "sub_ebce390", 0xEBCE390, sub_ebce390_lifted, nullptr)` (footprint nullptr: the function itself writes no memory).

## Signature (x64 Microsoft ABI), from the disassembly of the callers
extern "C" void sub_ebce390(void* dst, void* src, std::uint32_t count);

Register/argument map [V] from call sites of 0xebce390, e.g. 0x568ce40..0x568ce51 and 0x56ae2d7..0x56ae2e8:
- dst = rcx: the caller computes a pointer into rcx immediately before the call (0x568ce40  lea rcx,[rsi+r13]; 0x56ae2d7  lea rcx,[r14+rsi]).
- src = rdx: the caller moves a pointer into rdx immediately before the call (0x568ce67  mov rdx,r12; 0x56ae2fe  mov rdx,r13).
- count = r8d: the caller loads a 32-bit immediate into r8d immediately before the call (0x568ce4b  mov r8d,0x40; 0x56ae2e2  mov r8d,0x40; also 0x10 seen at 0x568ceac), zero-extended into r8.
- Return: void. rax is never read after a call to 0xebce390 at the sampled call sites, so the return value is unobserved by callers.

## Disassembly of the function [0xebce390, 0xebce395)
0xebce390  jmp 0xEEC6EC0     ; -> sub_eec6ec0
0xebce395  int3              ; padding, outside the function

The function is exactly one instruction: a tail jump to sub_eec6ec0 (0x5 bytes, [0xebce390, 0xebce395)). It forwards rcx, rdx, r8 unchanged and returns whatever sub_eec6ec0 leaves in rax.

## Reversed source (complete)
// 0xebce390..0xebce395
return sub_eec6ec0(dst, src, count);   // 0xebce390  jmp 0xEEC6EC0

Every instruction of [0xebce390, 0xebce395) is the single jmp above, covered by the cited range and by the verbatim quote in the source file. There is no x86 `call` instruction in the function (the only control-transfer instruction is the jmp), so no verbatim `0xRVA  call ...` quote exists for this function.

## Calls
The lifted body calls native::sub_eec6ec0 directly (plain C++ call through the forward declaration in sub_ebce390.h). sub_eec6ec0 (0xeec6ec0) is class `lift` in docs/data/native_boundary.tsv and has its own X7 unit; no boundary wrapper and no unresolved call.

## Struct fields touched
None: the function reads no struct or class fields and writes no memory itself.

## Callees
sub_eec6ec0 (0xeec6ec0, lift set, native_boundary.tsv class `lift`), called via the tail jump; own unit X7.eec6ec0.

## Version anchors
Minecraft Bedrock 1.26.62.01; RVAs relative to the image base. Evidence: `rdis dis 0xebce390 5` and `rdis xr 0xebce390` call sites.
