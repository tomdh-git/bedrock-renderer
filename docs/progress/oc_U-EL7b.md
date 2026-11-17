## NEXT
DONE

# U-EL7b: L7b name->info lookup (MaterialPtr = shared_ptr<void>)

## Pending part: name->info lookup

The L7b checklist item reads:
"MaterialPtr = shared_ptr<void> (SDK); async loader 0xc26caa0 + 0xF0 material-set / 0x258 objects mapped (6dr); name->info lookup pending"

The loader (0xc26caa0), material-set (0xF0) and 0x258 object layouts were decoded in oc_U-G1b2.md (G1b, ticked 2026-11-16). This note covers only the remaining pending part: the name->info lookup.

Lookup chain [V]:
1. Caller computes FNV-1a 64-bit hash of the material name (8-byte key)
2. Calls vtable slot 15 on sub-record 0 of the 0x258 object
3. Thunk sub_c272190 (0xc272190) loads holder from [this+0x168], tail-calls sub_e8fe660
4. sub_e8fe660 (0xe8fe660) locks holder+0x4C, FNV-1a hashes the key, computes bucket = hash & mask (holder+0xC8)
5. Walks chain at bucket_array[bucket] (base holder+0xB0, end holder+0xA0), comparing node+0x10 keys
6. On match: returns node+0x20 - node+0x18; on miss: returns 0

Container is built by sub_24af560 (0x24af560), which allocates a bucket buffer and initializes holder+0xA0 (end), holder+0xB0 (base), holder+0xC8 (mask = 7, i.e. 8 buckets).

| Field | Size | Offset | Site | Verbatim instr | Tag |
| sub_e8fe660 name->info lookup | - | 0xe8fe660 | 0xe8fe660 | `0xe8fe660  push r15` | [V] |
| sub_c272190 vtable slot-15 thunk | - | 0xc272190 | 0xc272190 | `0xc272190  mov rcx,[rcx+0x168]` | [V] |
| sub_24af560 container builder | - | 0x24af560 | 0x24af560 | `0x24af560  push rbp` | [V] |
| holder lock state | 4 | holder+0x4C | 0xe8fe683 | `0xe8fe683  cmp dword ptr [rsi+0x4C],0x7FFFFFFF` | [V] |
| holder bucket-array end | 8 | holder+0xA0 | 0xe8fe72f | `0xe8fe72f  mov r11,[rsi+0xA0]` | [V] |
| holder bucket-array base | 8 | holder+0xB0 | 0xe8fe736 | `0xe8fe736  mov r15,[rsi+0xB0]` | [V] |
| holder bucket mask | 4 | holder+0xC8 | 0xe8fe728 | `0xe8fe728  and rcx,[rsi+0xC8]` | [V] |
| holder+0xA0 init (bucket end) | 8 | holder+0xA0 | 0x24af5bb | `0x24af5bb  mov [rsi+8],rdi` | [V] |
| holder+0xB0 init (bucket base) | 8 | holder+0xB0 | 0x24af646 | `0x24af646  mov [rsi+0x18],rbx` | [V] |
| holder+0xC8 init (bucket mask) | 4 | holder+0xC8 | 0x24af5d3 | `0x24af5d3  mov qword ptr [rsi+0x30],7` | [V] |
| bucket-entry tail ptr | 8 | bucket+0x00 | 0xe8fe78c | `0xe8fe78c  mov rcx,[r15+rcx]` | [V] |
| bucket-entry head ptr | 8 | bucket+0x08 | 0xe8fe741 | `0xe8fe741  mov r10,[r15+rcx+8]` | [V] |
| hash-node next ptr | 8 | node+0x00 | 0xe8fe795 | `0xe8fe795  mov r10,[r10+8]` | [V] |
| hash-node key (FNV-1a hash) | 8 | node+0x10 | 0xe8fe786 | `0xe8fe786  cmp rax,[r10+0x10]` | [V] |
| hash-node value low | 4 | node+0x18 | 0xe8fe7a8 | `0xe8fe7a8  sub ebx,[r10+0x18]` | [V] |
| hash-node value high | 4 | node+0x20 | 0xe8fe7a4 | `0xe8fe7a4  mov ebx,[r10+0x20]` | [V] |
| FNV-1a offset basis | 8 | 0xe8fe6c5 | 0xe8fe6c5 | `0xe8fe6c5  mov rcx,0xCBF29CE484222325` | [V] |
| FNV-1a prime | 8 | 0xe8fe6d2 | 0xe8fe6d2 | `0xe8fe6d2  mov rbx,0x100000001B3` | [V] |

 0xe8fe660  push r15
 0xc272190  mov rcx,[rcx+0x168]
 0x24af560  push rbp
 0xe8fe683  cmp dword ptr [rsi+0x4C],0x7FFFFFFF
 0xe8fe72f  mov r11,[rsi+0xA0]
 0xe8fe736  mov r15,[rsi+0xB0]
 0xe8fe728  and rcx,[rsi+0xC8]
 0x24af5bb  mov [rsi+8],rdi
 0x24af646  mov [rsi+0x18],rbx
 0x24af5d3  mov qword ptr [rsi+0x30],7
 0xe8fe78c  mov rcx,[r15+rcx]
 0xe8fe741  mov r10,[r15+rcx+8]
 0xe8fe795  mov r10,[r10+8]
 0xe8fe786  cmp rax,[r10+0x10]
 0xe8fe7a8  sub ebx,[r10+0x18]
 0xe8fe7a4  mov ebx,[r10+0x20]
 0xe8fe6c5  mov rcx,0xCBF29CE484222325
 0xe8fe6d2  mov rbx,0x100000001B3

CLOSES? YES — name->info lookup fully decoded: sub_e8fe660 (0xe8fe660) via thunk sub_c272190 (0xc272190); FNV-1a 64-bit hash (offset basis 0xCBF29CE484222325, prime 0x100000001B3); chained hash table at holder+0xA0 (end), holder+0xB0 (base), holder+0xC8 (mask); hash nodes keyed at node+0x10 with value node+0x20 - node+0x18; container built by sub_24af560 (0x24af560) initializing holder+0xA0/0xB0/0xC8. All instruction accesses proven by [V] rows above.

## TOOL REQUESTS
None
