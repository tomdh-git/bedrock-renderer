# Dossier: sub_ebdbf10 ("sub_ebdbf10")

Minecraft Windows 1.26.62.01. Function [0xebdbf10, 0xebdbf17), size 0x7 bytes.
Disassembly source: rdis `dis 0xebdbf10` / `sum 0xebdbf10`. All facts below are [V] from those listings; nothing is inferred.

## Signature (lifted)
void sub_ebdbf10(void* lock);   // argument in RCX = address of the ctx lock field (ctx+0x1C0) [V: callers 0xbc66c9d `call 0xEBDBF10`, 0xbc6f828 `call 0xEBDBF10`]; return unused (RAX as the tail-jmp target leaves it)

## Register / argument map
RCX = lock (void*) at entry; result in RAX (forwarded by the tail jump, unused by callers) [V: sub_bc70ca0.h / sub_bc66c50.h forward declarations and call sites]

## Phases (instruction-complete, [0xebdbf10, 0xebdbf17))
0xebdbf10..0xebdbf17: 8-byte pointer load from data slot 0xF9A7B10 and tail jump to it; argument RCX forwarded, result returned in RAX as-is.
  0xebdbf10  jmp qword ptr [0xF9A7B10]                     ; [data_f9a7b10]

## Struct fields touched
none: the function reads no struct fields and writes no memory; it only loads the pointer from data slot 0xF9A7B10 (global data, not a struct field) [V: rdis `sum` shows one 8-byte read at &data_f9a7b10, ip 0xebdbf10, rw=R, size=8]

## Callees
none in the lift set; the jmp target is the loader-resolved pointer in data slot 0xF9A7B10 and is invoked through a function pointer (boundary rule #69: read the slot at call time, document the slot RVA) [V: rdis `dis` shows `jmp qword ptr [0xF9A7B10]` at 0xebdbf10]

## Verbatim instruction quotes (all instructions in the function)
0xebdbf10  jmp qword ptr [0xF9A7B10]

## OPEN questions
none: the function is a single indirect tail jump; the slot target is resolved by the loader at runtime, so no static target exists [V: rdis `sum` marks the jump at ebdbf10 "unresolved indirect jump", pointer value at runtime]

## Reversed source (complete)
// Reversed from the disassembly of [0xebdbf10, 0xebdbf17), size 0x7, Minecraft Windows 1.26.62.01 (rdis dis output).
// The body is one instruction:
//   0xebdbf10  jmp qword ptr [0xF9A7B10]   ; tail jump through data slot 0xF9A7B10
// No reads of struct fields, no writes, no calls; the argument arrives in RCX and the result leaves in RAX as the slot target leaves it.

void sub_ebdbf10(void* lock) {
    static_assert(sizeof(void*) == 8, "sub_ebdbf10: x64 ABI");
    // 0xebdbf10..0xebdbf17:  jmp qword ptr [0xF9A7B10]
    using Fn = void (*)(void*);
    return reinterpret_cast<Fn>(*reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A7B10ull))(lock);   // 0xebdbf10  jmp qword ptr [0xF9A7B10]
}
