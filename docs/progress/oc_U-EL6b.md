## NEXT
DONE

# U-EL6b: VV in/out resources per pass (builder 0x55f1450)

Pending item from checklist L6b: "in/out resources per pass" for VV passes declared inside builder 0x55f1450 (size 0x4e144).

## Method

Scanned all 50 pass-declaration call sites in 0x55f1450_full.lst (pre/pass_decl_calls.txt, pre/pass_decl_context.txt). The dominant declaration function is 0x5698290 (15 call sites), which receives a 28-byte pass descriptor struct in r8. Additional decl functions: 0x5684660 (1 named pass "Transparent"), 0x5667860 (4), 0x5693680 (7), 0x5694510 (2), 0x5695960 (1), 0x5696540 (1), 0x5697650 (1), 0x56CB540 (1), 0xBBBD7F0 (1). The 0x5689800 calls (18) are memmove loops, not pass declarations.

## Callee semantics: 0x5698290

Disassembled 0x5698290 (rdis, 80 instr). It:
1. Allocates 0x28 bytes (40 bytes)
2. Stores vtable at allocated+0x00
3. `56982dc  movups xmm0,[rbx]` — reads 16 bytes at input struct +0x00; `56982df  movups xmm1,[rbx+0xC]` — reads 16 bytes at input struct +0x0C
4. Writes to allocated+0x08 and allocated+0x14
5. Adds allocated struct to a pointer list at context+0x28
6. Adds a 0x50-stride entry at context+0x40 (entry+0x00 = context+0x50 value, entry+0x08 = allocated struct ptr, entry+0x40 = 0, entry+0x48 = 0xFFFFFFFF)
7. Calls 0x567A7B0 with context+0x68, which allocates 0x30 bytes and copies allocated+0x00 (vtable) and allocated+0x08 (word+word) into the new struct
8. Returns the allocated struct pointer

The callee copies ALL 28 input bytes opaquely — no instruction distinguishes input from output resource fields.

## Descriptor struct layout (verified from 0x5698290 call sites)

28-byte struct passed in r8 to 0x5698290. One row per distinct offset, all store sites listed. Representative call site 0x55f1fca -> 0x5698290; same offsets also stored at 0x55f1fe7, 0x55ff2f8, 0x55ff31d, 0x562cc0a, 0x562e4e3, 0x562e661, 0x563281e, 0x5632b0e, 0x5633359 (different base addresses: [rbp+0x1C40], [rbp+0x2440]).

| offset | size | site | instr | meaning |
|--------|------|------|-------|---------|
| +0x00 | 2B | [rbp+0x2C00], [rbp+0x1C40], [rbp+0x2440] | `0x55f1f68  mov [rbp+0x2C00],ax` | - |
| +0x02 | 2B | [rbp+0x2C02], [rbp+0x1C42] | `0x55f1f76  mov [rbp+0x2C02],ax` | - |
| +0x04 | 4B | [rbp+0x2C04], [rbp+0x1C44], [rbp+0x2444] | `0x55f1fa5  mov dword ptr [rbp+0x2C04],0x2D` | - |
| +0x08 | 8B | [rbp+0x2C08], [rbp+0x1C48], [rbp+0x2448] | `0x55f1f90  mov [rbp+0x2C08],rax` | - |
| +0x10 | 8B | [rbp+0x2C10], [rbp+0x1C50], [rbp+0x2450] | `0x55f1f9e  mov [rbp+0x2C10],rax` | - |
| +0x18 | 4B | [rbp+0x2C18], [rbp+0x1C58], [rbp+0x2454] | `0x55f1faf  mov dword ptr [rbp+0x2C18],0` | - |

All six fields are read by 0x5698290 via `56982dc  movups xmm0,[rbx]` (16B at +0x00) and `56982df  movups xmm1,[rbx+0xC]` (16B at +0x0C), then copied opaquely to the allocated struct. No instruction or string labels any field as input resource or output resource.

## Named pass declaration: 0x5684660 ("Transparent")

Call site 0x5610bd3 -> 0x5684660. Builds name string "Transparent" at [rbp+0x2EF8], hash 0xAE2D576F32B04C19 at [rbp+0x2EF0]:
- `0x5610b63  mov rcx,0x726170736E617254` ("Transparent")
- `0x5610b6d  mov [rax],rcx`
- `0x5610b70  mov dword ptr [rax+7],0x746E6572`
- `0x5610b7e  mov rax,0xAE2D576F32B04C19`
- `0x5610b88  mov [rbp+0x2EF0],rax`

Takes multiple pointer args: rdx=&[rbp+0x2848], r8d=2, r9=&[rbp+0x2EF0], stack args &[rbp+0x2440], 1, &[rbp+0x2620], &[rbp+0x2770]. Callee 0x5684660 reads [rdx+0x10], [rdx+0x18], [rdx+0x28], [rdx+0x60] but field semantics (input vs output) are not distinguished by any instruction.

## Conclusion

CLOSES? NO — blocking fact: the pass declaration functions (0x5698290, 0x5684660, 0x5667860, 0x5693680, 0x5694510, 0x5695960, 0x5696540, 0x5697650, 0x56CB540, 0xBBBD7F0) copy all descriptor struct fields opaquely; no instruction or string within 0x55f1450 or its callees distinguishes which struct fields hold input resources versus output resources. The struct layout (28 bytes: word,word,dword,qword,qword,dword) and all store instructions are verified [V], but the input/output resource classification is not provable from static analysis alone.

## NEXT
DONE