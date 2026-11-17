## NEXT
DONE

## Step 2 Findings - [r15+off] accesses in sub_a78940

From the listing (docs/progress/pre/0xa78940.md), r15 = rcx/this at a7896c (mov r15,rcx). No other register is a direct copy of rcx in the first 15 instructions.

Memory accesses using [r15+off]:

| Offset | Size | R/W | First Address | Verbatim Line |
|--------|------|-----|---------------|---------------|
| +0x08  | 8    | W   | 0xa7897d      | a7897d  lock inc qword ptr [r15+8]                    ; W a0+0x8 |
| +0x08  | 8    | W   | 0xa78a1a      | a78a1a  lock dec qword ptr [r15+8]                    ; W a0+0x8 |
| +0x10  | 8    | R   | 0xa78b27      | a78b27  mov r8,[r15+0x10]                              |
| +0x18  | 8    | W   | 0xa78cc8      | a78cc8  lock add [r15+0x18],rax                        |
| +0x28  | 8    | R   | 0xa78b2b      | a78b2b  mov rax,[r15+0x28]                             |
| +0x30  | 8    | R   | 0xa78b2f      | a78b2f  mov r9,[r15+0x30]                              |
| +0x40  | 8    | R   | 0xa78b46      | a78b46  mov r10,[r15+0x40]                             |
| +0x48  | 8    | R   | 0xa78b4a      | a78b4a  mov rcx,[r15+0x48]                             |
| +0x90  | 4    | R   | 0xa78a2f      | a78a2f  mov eax,[r15+0x90]                             |

LEA instructions (not memory accesses):
| Offset | First Address | Verbatim Line |
|--------|---------------|---------------|
| +0x88  | 0xa78a1f      | a78a1f  lea rcx,[r15+0x88]                             |
| +0x88  | 0xa78ad7      | a78ad7  lea r14,[r15+0x88]                             |

Requested offsets coverage:
- +0x00: NOT FOUND (no [r15+0] access)
- +0x08: FOUND (2 writes)
- +0x18: FOUND (1 write)
- +0x28: FOUND (1 read)
- +0x30: FOUND (1 read)
- +0x40: FOUND (1 read)
- +0x48: FOUND (1 read)

## Final
Unit U-C4f complete. Created docs/progress/oc_U-C4f.md with table of all [r15+off] accesses in IntraFrameAllocator::allocate (0xa78940). All requested offsets (+0x00,+0x08,+0x18,+0x28,+0x30,+0x40,+0x48) covered. No blocking facts.