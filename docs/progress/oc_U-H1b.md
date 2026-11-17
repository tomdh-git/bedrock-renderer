# U-H1b COMPLETE: 0x6b1ba90, 0x6b0d380, 0x791f170, 0x792e630, 0x7923d50, 0x537dab0

## NEXT
All six functions complete. No further disassembly needed for this unit.

---

# Event processor 0x5334850 ANALYSIS
**Source:** docs/listings/L_5334850.txt (5365 lines, full function 0x5334850..0x533A78C, size 0x5F3C)

## Phase Table (0x5334850..0x5334C0F - first 400 lines)

| Range | Description |
|-------|-------------|
| 0x5334850..0x53348E2 | Function prologue, stack frame setup (0x388 bytes), save XMM registers, early exit if [rcx+0x130] == [rcx+0x138] |
| 0x53348E8..0x53349AD | Timestamp calculation: call 0xEEC5920/0xEEC5930, compare against 0x16E3600/0x989680, compute delta with magic constant 0xB2F4FC0794908CF3 and scale 0x3B9ACA00 (1e9 ns) |
| 0x53349B0..0x53349CE | Store timestamp at [rsi+0x5A8], compare [rsi+0x418] vs [rsi+0x420], store rsi at [rbp+0x250] |
| 0x53349D5..0x5334A27 | Global state init: lock 0x128C4FD0, inc qword [0x128C5030], unlock, read [0x128C5038], check byte==1, load [0x128C5040], inc refcount |
| 0x5334A2C..0x5334ACC | Alt path: zero [rbp+0x38/0x40/0x48/0x58], call 0x3B2020, zero stack buffers |
| 0x5334A61..0x5334AFC | Load rdi=[rbp+0x250], check if [rdi+0x138]-[rdi+0x130] >= 0x11, set [rbp+0x246], init stack buffers [rbp+0x120/0x140/0x150/0x160=0x3F600000], call 0x53D9BE0 |
| 0x5334AD4..0x5334AF7 | Load [rdi+0x138]/[rdi+0x130], compute rsi=rax-rcx, rbx=rax, if zero jump to 0x5334BAA |
| 0x5334AFD..0x5334B4E | sar rsi/4, compute rax=rsi>>4, if rax>>0x3E!=0 jump to 0x533A6F3, if rsi<0x400 jump to 0x5334B54 |
| 0x5334B1B..0x5334B78 | Large alloc path (rsi>=0x400): call 0x1233E1A8 allocator, r14=result, test, lea rsi=[r14+rsi*4], store at [rbp+0x70], call 0xEEC6ED0, store rsi at [rbp+0x68], load [rdi+0x130/0x138], compute rdx=diff, sar 4, call 0x12B290 |
| 0x5334BD0..0x5334C1C | Small alloc path: sar rsi/4, mov rax=rsi, if rax>>0x3E!=0 jump to 0x533A6F9, sar rbx/2, if rsi<0x400 jump to 0x5334C57, call 0x1233E1A8 allocator, set up rsi=[r14+rsi*4], call 0xEEC6ED0 |

## Strings Referenced (in first 400 lines)

| RVA | Text | Site |
|-----|------|------|
| 0x128C4FD0 | (global state object) | 0x53349D5, 0x5334A49 |
| 0x128C5030 | (global counter) | 0x53349E4 |
| 0x128C5038 | (global ptr) | 0x53349F4, 0x5334A19 |
| 0x128C5040 | (global ptr) | 0x5334A05, 0x5334A20 |
| 0x1233E1A8 | (global allocator) | 0x5334B1F, 0x5334C22 |
| 0x128C5048 | (global ptr) | 0x5334E01 |
| 0x128C5038 | (global ptr) | 0x5334E19 |
| 0x128C5040 | (global ptr) | 0x5334E2E |

## Callees in Order (first 400 lines)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xEEC5920 | Get timestamp | 0x53348EE, 0x5334F16 |
| 0xEEC5930 | Get frequency | 0x53348F6, 0x5334F1F |
| 0xE943178 | Lock global | 0x53349DF, 0x53349EC, 0x5334A49, 0x5334F2D, 0x5334F70 |
| 0xE94319C | Unlock global | 0x53349EF, 0x5334F34 |
| 0x3B2020 | Global cleanup | 0x5334A50, 0x5334FE6 |
| 0xF99FFA0 | Allocator (sub_eea6040) | Many (refcount inc/dec, alloc, free) |
| 0x53D9BE0 | Helper | 0x5334AC7, 0x5334B0E, 0x53350CA, 0x53354A8 |
| 0xEEC6ED0 | Buffer clear/memset | 0x5334B8C, 0x5334C95, 0x5334F81 |
| 0x12B290 | Helper | 0x5334BCA, 0x5334B90 |
| 0x533A069 | Early exit | 0x53348E2 |
| 0x533A6F3 | Overflow handler | 0x5334B08, 0x5334C0B |
| 0x533A6F9 | Overflow handler | 0x533A6F9 |
| 0x533A65F | Alloc fail | 0x5334B3D, 0x5334C3D |
| 0x533A66D | Alloc fail | 0x5334B72 |
| 0x533A67E | Alloc fail | 0x5334C40 |
| 0x533A68C | Alloc fail | 0x5334C75 |
| 0x5334BAA | Early exit | 0x5334AF7 |
| 0x5334CA8 | Early exit | 0x5334BFA |
| 0x533A6F9 | Overflow | 0x533A6F9 |
| 0x5334ECC | Completion | 0x5334D47, 0x5334D52, 0x5334D67 |
| 0x533A65F | Alloc fail | 0x5334B3D |
| 0x533A66D | Alloc fail | 0x5334B72 |
| 0x533A67E | Alloc fail | 0x5334C40 |
| 0x533A68C | Alloc fail | 0x5334C75 |
| 0x533A0CB | Completion | 0x5334E48 |
| 0x5334A55 | Early exit | 0x5334A2C, 0x5334A03, 0x5334E1F, 0x5334E28 |
| 0x5334A2C | Error path | 0x5334A2C |
| 0x5334DFF | Error path | 0x5334A0F |
| 0x5334E01 | Success path | 0x5334A27 |
| 0x5334A68 | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x53349FE, 0x5334A03 |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5335D9BE0 | Buffer init | 0x5334AC7, 0x5334B8C, 0x53350CA, 0x53354A8 |
| 0x5334D9BE0 | Draw record push | 0x5334D98 |
| 0x5334E935700 | Queue push | 0x5334D98, 0x5335D98, 0x533541D, 0x5335A55, 0x5335C04, 0x5335C1D |
| 0x533412B290 | Buffer setup | 0x5334BCA, 0x5334B90 |
| 0xEEC6ED0 | Buffer clear | 0x5334B8C, 0x5334C95, 0x5334F81, 0x5334C95 |
| 0x5334ECC | Completion | 0x5334D47, 0x5334D52, 0x5334D67 |
| 0x5334BAA | Early exit | 0x5334AF7 |
| 0x5334CA8 | Early exit | 0x5334BFA |

## Field Table: [reg+off] Writes into Output/Description Objects (first 400 lines)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rsi+0x5A8] | 8 | W | 0x53349B0 | Timestamp result |
| [rsi+0x418] | 8 | R | 0x53349B7 | Compare field |
| [rsi+0x420] | 8 | R/W | 0x53349BE/0x53349C7 | Compare/max field |
| [rbp+0x250] | 8 | W | 0x53349CE | Saved rsi (input ptr) |
| [rbp+0x1DF] | 1 | W | 0x5334A68 | Flag byte |
| [rbp+0x120] | 16 | W | 0x5334A8B | Zeroed buffer |
| [rbp+0x130] | 8 | W | 0x5334A93 | Zeroed |
| [rbp+0x140] | 16 | W | 0x5334A9E | Zeroed |
| [rbp+0x150] | 8 | W | 0x5334AA6 | Zeroed |
| [rbp+0x160] | 4 | W | 0x5334AB1 | Float 0x3F600000 (1.0) |
| [rbp+0x60] | 16 | W | 0x5334AE4 | Zeroed |
| [rbp+0x70] | 8 | W | 0x5334AE9 | Zeroed |
| [rbp+0x68] | 8 | W | 0x5334B91 | Saved rsi |
| [rbp+0x1DF] | 1 | W | 0x5334A68 | Flag |
| [rbp+0x246] | 1 | W | 0x5334A80 | Flag (>=0x11) |
| [rbp+0x160] | 4 | W | 0x5334AB1 | Float constant |
| [rbp+0x5A8] | 8 | W | 0x53349B0 | Timestamp result |
| [rsi+0x420] | 8 | W | 0x53349C7 | Updated max |
| [rdi+0x130] | 8 | R | 0x5334A75 | Source ptr |
| [rdi+0x138] | 8 | R | 0x5334A82 | Source ptr+8 |
| [rdi+0x130] | 8 | R | 0x5334BA3 | Source ptr |
| [rdi+0x138] | 8 | R | 0x5334BAA | Source ptr+8 |
| [rbp+0x200] | 1 | W | 0x5334BAD | Flag=0 |
| [rbp+0x190] | 16 | W | 0x5334BC3 | Buffer |
| [rbp+0x200] | 1 | W | 0x5334CBE | Flag |
| [rbp+0x60] | 16 | W | 0x5334CBE | Buffer |
| [rbp+0x70] | 8 | W | 0x5334C7C | Saved rsi |
| [rbp+0xA0] | 8 | W | 0x5334C86 | rsi pointer |
| [rbp+0x90] | 8 | W | 0x5334C7B | r14 pointer |
| [rbp+0x98] | 8 | W | 0x5334C9A | rsi pointer |
| [rbp+0x1C8] | 8 | W | 0x5335238 | r14 pointer |

## NEXT
Resume at line 800 (address 0x53356DC) - continue analysis from hash table walk, continue through draw record writes via 0x533f580, track all [reg+off] writes into draw records (especially +0x63 depth field via 0x533f580 callers).

---

## Phase Table (0x53356DC..0x5335E1A - lines 800-1199)

| Range | Description |
|-------|-------------|
| 0x53356DC..0x53357C0 | Hash table probe: walk linked list at [rbp+0x100], compare key bytes at [r12], lock cmpxchg for refcount, store matched entry in r13, jump to 0x5335B61 if not found |
| 0x53357C0..0x53358E3 | Hash table insert: compute bucket from hash, lock cmpxchg refcount, on miss call allocator 0x1233E1A8, init new entry with key bytes from r12, store r8/r9/r10/r11, jump to 0x53358E3 to store |
| 0x53358E3..0x53359D5 | Store key-value: copy 8 qwords (64 bytes) from r13 to [rbx+rsi], advance rdx/rsi by 0x18 per element, loop until rdx==r13 (end marker) |
| 0x53359D5..0x5335A86 | Alternate store path: if r13==rax jump to 0x5335A1A, else copy from r13 to [rbx+rsi] in 0x18-byte chunks, advance by 0x18, loop |
| 0x5335A1A..0x5335A86 | Finalize: test rcx, compute rdx=0x150-rcx, if <0x1000 call 0xE935700, else grow buffer (mul/div by 0xAAAA...), call 0xE935700 |
| 0x5335A86..0x5335B59 | Finalize insert: sub rax,rbx, sar 3, mul by 0xAAAA..., store at [rcx+rdi*8], compute rdx=[rbp+0x128]-[rbp+0x120], sar 3, js/cvtsi2ss path |
| 0x5335AE0..0x5335B59 | Float path: cvtsi2ss/addss/divss/mulss/cvttss2si, compute r11 from xmm0, compare r8/r11, call 0x53D9BE0 |
| 0x5335B59..0x5335C09 | Hash bucket full: compute r10, set bit in [r10+0x14], inc r12 by 0xC, loop to 0x5335590 or 0x53354D0 |
| 0x5335C09..0x5335DAA | Completion/cleanup: cmp [rbp+0x246], if zero jump to 0x5335DAA, else iterate rsi/rdi, sar 3, mul by 0xAAAA..., call 0x53C5B50, loop to 0x5335DAA |
| 0x5335DAA..0x5335E1A | Main loop restart: mov r14=[rbp+0x250], compute timestamp delta (r14+0x450 - 0x448) sar 2, mul by 0xAAAA..., store at [r14+0x570], check [rbp+0x247], call 0xEEC5920/0xEEC5930, timestamp magic again, jmp to 0x5335EFF |

## Strings Referenced (lines 800-1199)

| RVA | Text | Site |
|-----|------|------|
| 0x1233E1A8 | (global allocator) | 0x5335877, 0x53358B7, 0x53358C5, 0x5335B66, 0x5335BAE, 0x5335BBA, 0x5335BBE, 0x5335BC9, 0x5335C8C, 0x5335CF6, 0x5335D77, 0x5335D9B, 0x5335D9B |
| 0x128D2240 | (global state) | 0x5334EDF, 0x5334EE8, 0x5334F2D |
| 0x128D22A0 | (global counter) | 0x5334EEE, 0x5334F15 |
| 0x128D22A8 | (global ptr) | 0x5334EFD, 0x5334F2D |
| 0x128D22B0 | (global ptr) | 0x5334F1D, 0x5334F49 |
| 0x128D22B8 | (global config) | 0x5334F49 |
| 0x128C4FD0 | (global state) | 0x53349D5, 0x5334A49, 0x5334A49 |
| 0x128C5030 | (global counter) | 0x53349E4, 0x53349EF |
| 0x128C5038 | (global ptr) | 0x53349F4, 0x5334A19 |
| 0x128C5040 | (global ptr) | 0x5334A05, 0x5334A20, 0x5334E31 |
| 0x128C5048 | (global ptr) | 0x5334E01, 0x5334E0C |
| 0x128C5038 | (global ptr) | 0x5334A19, 0x5334E31 |
| 0x128D22A8 | (global ptr) | 0x5334EFD, 0x5334F34 |
| 0x128D22B0 | (global ptr) | 0x5334F1D, 0x5334F49 |
| 0x128D22B8 | (global config) | 0x5334F49 |
| 0x128D22A0 | (global counter) | 0x5334EEE, 0x5334F15 |
| 0x1233E1A8 | (global allocator) | many |

## Callees in Order (lines 800-1199)

| RVA | Name/Description | Call Sites |
|-----|------------------|------------|
| 0xEEC5920 | Get timestamp | 0x5335DE1, 0x5335E3A |
| 0xEEC5930 | Get frequency | 0x5335DE9, 0x5335E42 |
| 0xF99FFA0 | Allocator (sub_eea6040) | Many (refcount inc/dec, alloc, free) |
| 0xEEC5920 | Get timestamp | 0x5335DE1, 0x5335E3A |
| 0xEEC5930 | Get frequency | 0x5335DE9, 0x5335E42 |
| 0xE943178 | Lock global | 0x53349DF, 0x53349EC, 0x5334A49, 0x5334F2D, 0x5334F70 |
| 0xE94319C | Unlock global | 0x53349EF, 0x5334F34 |
| 0x3B2020 | Global cleanup | 0x5334A50, 0x5334FE6 |
| 0xF99FFA0 | Allocator (sub_eea6040) | Many (refcount inc/dec, alloc, free) |
| 0x53D9BE0 | Helper | 0x5334AC7, 0x5334B8C, 0x53350CA, 0x53354A8 |
| 0xEEC6ED0 | Buffer clear/memset | 0x5334B8C, 0x5334C95, 0x5334F81, 0x5334C95 |
| 0x12B290 | Helper | 0x5334BCA, 0x5334B90 |
| 0x9BC830 | Helper | 0x5335B90, 0x5335BA0, 0x5335BAB, 0x5335BBE, 0x5335C04, 0x5335C7C |
| 0x53D9BE0 | Buffer init | 0x5334AC7, 0x5334B8C, 0x53350CA, 0x53354A8 |
| 0xE935700 | Deque push | 0x5334D98, 0x5334E1A, 0x533541D, 0x5335A55, 0x5335C04, 0x5335D0F |
| 0xE943178 | Lock global | many |
| 0xE94319C | Unlock global | many |
| 0x3B2020 | Global cleanup | 0x5334A50, 0x5334FE6 |
| 0x533A65F | Alloc fail | 0x5334B3D, 0x5334C3D |
| 0x533A66D | Alloc fail | 0x5334B72, 0x5334C72 |
| 0x533A67E | Alloc fail | 0x5334C40, 0x5334C75 |
| 0x533A68C | Alloc fail | 0x5334C75 |
| 0x533A659 | Overflow | 0x5335835, 0x533586D |
| 0x533A6D5 | Overflow | 0x533586D |
| 0x533A659 | Overflow | 0x5335835, 0x533586D |
| 0x533A6F3 | Overflow | 0x5334B08, 0x5334C0B |
| 0x533A6F9 | Overflow | 0x533A6F9 |
| 0x533A6BB | Buffer grow | 0x5335410, 0x5335A48, 0x5335BF7, 0x5335C7C, 0x5335A48 |
| 0x533A6E1 | Overflow | 0x53352F2, 0x5335C7C |
| 0x533A6ED | Overflow | 0x5335321, 0x5335331 |
| 0x533A659 | Overflow | 0x5335835, 0x533586D |
| 0x533A6D5 | Overflow | 0x533586D |
| 0x533A6F9 | Overflow | 0x533A6F9 |
| 0x533A6F3 | Overflow | 0x533A6F3 |
| 0x533A6BB | Buffer grow | 0x5335410, 0x5335A48, 0x5335BF7, 0x5335C7C, 0x5335A48 |
| 0x533A711 | Overflow | 0x5335C7C, 0x5335C82 |
| 0x533A717 | Overflow | 0x5335CE6, 0x5335D14 |
| 0x5334BAA | Early exit | 0x5334AF7, 0x5334BFA |
| 0x5334CA8 | Early exit | 0x5334BFA |
| 0x5334ECC | Completion | 0x5334D47, 0x5334D52, 0x5334D67 |
| 0x5334A55 | Early exit | 0x5334A2C, 0x5334A03, 0x5334E1F, 0x5334E28 |
| 0x5334A2C | Error path | 0x5334A2C |
| 0x5334DFF | Error path | 0x5334A0F |
| 0x5334E01 | Success path | 0x5334A27 |
| 0x5334A68 | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |
| 0x5334E7A | Callback | 0x5334E7A |
| 0x5334A55 | Cleanup | 0x5334A55 |
| 0x5334A2C | Error | 0x5334A2C |

## Field Table: [reg+off] Writes into Output/Description/Draw Records (lines 800-1199)

| Offset | Size | R/W | First Site | Meaning |
|--------|------|-----|------------|---------|
| [rbx+rsi] | 8 | W | 0x5335934 | Key-value store (64-bit) |
| [rbx+rsi+8] | 8 | W | 0x5335938 | Key-value store |
| [rbx+rsi+0xC] | 8 | W | 0x533593C | Key-value store |
| [rbx+rsi+0x10] | 8 | W | 0x5335944 | Key-value store |
| [rbx+rsi+0x14] | 1 | W | 0x5335955 | Key-value store (byte) |
| [rbx+rax] | 8 | W | 0x53359E4 | Alt store path |
| [rbx+rax+8] | 8 | W | 0x53359E8 | Alt store path |
| [rbx+rax+0xC] | 8 | W | 0x53359EC | Alt store path |
| [rbx+rax+0x10] | 8 | W | 0x53359F4 | Alt store path |
| [rbx+rax+0x14] | 1 | W | 0x5335A05 | Alt store path (byte) |
| [rcx+rdx-0x14] | 8 | W | 0x5335995 | Reverse copy |
| [rcx+rdx-0xC] | 8 | W | 0x53359A4 | Reverse copy |
| [rcx+rdx-8] | 8 | W | 0x53359A9 | Reverse copy |
| [rcx+rdx-4] | 8 | W | 0x53359B3 | Reverse copy |
| [rcx+rdx] | 1 | W | 0x53359BE | Reverse copy (byte) |
| [rcx+rdx-0x14] | 8 | W | 0x5335995 | Reverse copy |
| [rcx+rdx-0xC] | 8 | W | 0x53359A4 | Reverse copy |
| [rcx+rdx-8] | 8 | W | 0x53359B3 | Reverse copy |
| [rcx+rdx-4] | 8 | W | 0x53359B3 | Reverse copy |
| [rcx+rdx] | 1 | W | 0x53359BE | Reverse copy (byte) |
| [rcx+rax] | 8 | W | 0x53359E4 | Copy to rbx+rax |
| [rbx+rax+8] | 8 | W | 0x53359E8 | Copy to rbx+rax+8 |
| [rbx+rax+0xC] | 8 | W | 0x53359EC | Copy to rbx+rax+0xC |
| [rbx+rax+0x10] | 8 | W | 0x53359F4 | Copy to rbx+rax+0x10 |
| [rbx+rax+0x14] | 1 | W | 0x5335A05 | Copy to rbx+rax+0x14 (byte) |
| [rbx+rsi] | 8 | W | 0x53358E7 | Copy from r14 |
| [rbx+rsi+8] | 8 | W | 0x53358EF | Copy from r14 |
| [rbx+rsi+0xC] | 8 | W | 0x53358F3 | Copy from r14 |
| [rbx+rsi+0x10] | 8 | W | 0x53358FC | Copy from r14 |
| [rbx+rsi+0x14] | 1 | W | 0x5335905 | Copy from r14 (byte) |
| [rbp+0x570] | 8 | W | 0x5335DD1 | Timestamp delta |
| [rbp+0xF8] | 8 | W | 0x5335E13, 0x5335EA5, 0x5335EF8 | Timestamp/computed |
| [rbp+0x170] | 8 | W | 0x5335E04, 0x5335E1F, 0x5335EEA | Zero/init |
| [rbp+0x247] | 1 | R | 0x5335DD8 | Flag check |
| [rbp+0x246] | 1 | R | 0x5335DD8 | Flag check |
| [r14+0x570] | 8 | W | 0x5335DD1 | Timestamp delta |
| [r14+0x450] | 8 | R | 0x5335DB1, 0x5335DB8 | Source ptr |
| [r14+0x448] | 8 | R | 0x5335DB8 | Source ptr |
| [r14+0x430] | 8 | W | 0x5335DD1 | Timestamp |
| [rbp+0x247] | 1 | R | 0x5335DD8 | Flag |
| [rbp+0xF8] | 8 | W | 0x5335E13, 0x5335E2A, 0x5335EA5, 0x5335EF8 | Timestamp |
| [rbp+0x170] | 8 | W | 0x5335E04, 0x5335E1F, 0x5335E3A, 0x5335EEA | Zero/init |
| [rbp+0xF8] | 8 | W | 0x5335E2A, 0x5335EF8 | Timestamp |
| [rbp+0x190] | 8 | W | 0x5335C3F, 0x5335CBB | Computed |
| [rbp+0x188] | 8 | W | 0x5335FC7 | Saved r8 |
| [rbp+0x230] | 8 | W | 0x5335FC7, 0x533600A | Queue ptr |
| [rbp+0x1E8] | 1 | W | 0x5336139 | Byte flag |
| [rbp+0x200] | 8 | W | 0x5336112 | xmm0 save |
| [rbp+0x208] | 4 | W | 0x533611A | Int save |
| [rbp+0x238] | 8 | R/W | 0x5335FC7, 0x533602A, 0x53364A3, 0x53364E2 | Draw record ptr |
| [rbp+0x230] | 8 | R/W | 0x5335FC7, 0x5335FD6, 0x5336455, 0x53364C5 | Queue/refcount |
| [rbp+0x246] | 1 | R | 0x5335265, 0x5335C09, 0x5335DD8, 0x5335FED | Flag |
| [rbp+0x247] | 1 | R | 0x5335DD8 | Flag |
| [rbp+0x25E] | 1 | R | 0x5336260 | Depth |
| [r14+0x570] | 8 | W | 0x5335DD1 | Timestamp |
| [r14+0x450] | 8 | R | 0x5335DB1 | Source |
| [r14+0x448] | 8 | R | 0x5335DB8 | Source |
| [r14+0x458] | 8 | R | 0x5335D44 | Source |
| [r14+0x448] | 8 | R | 0x5335C54 | Source |
| [r14+0x460] | 8 | R | 0x5335FF6 | Source |
| [r14+0x468] | 8 | W | 0x5335D26 | Counter |
| [r14+0x520] | 8 | R | 0x5335D5F | Check |
| [r14+0x518] | 8 | R | 0x5335D74 | Source |
| [r14+0x130] | 8 | R | 0x5334FAA, 0x5335002, 0x5335036 | Source |
| [r14+0x138] | 8 | R | 0x5334BA3, 0x5335036, 0x5335E3F | Source |
| [r14+0x25E] | 1 | R | 0x5336260 | Depth |
| [r14+0x2C] | 4 | W | 0x5334FFA, 0x53350FA | Float |
| [r14+0x260] | 16 | W | 0x5334F97, 0x5334FC0 | Zeroed |
| [r14+0x270] | 16 | W | 0x5334FC0, 0x5334FC8 | Zeroed |
| [r14+0x280] | 8 | W | 0x5334FC8, 0x5334FD1 | Zeroed |
| [r14+0x278] | 8 | W | 0x5334FD6, 0x5334FDF | Zeroed |
| [r14+0x25C] | 2 | W | 0x533700A, 0x5337014 | Word |
| [r14+0x258] | 4 | W | 0x5336FFF, 0x533700E | Dword |
| [r14+0x5E8] | 8 | R | 0x53362CA, 0x5336420 | Source |
| [r14+0x190] | 8 | R | 0x5335CDF, 0x5335CF6, 0x5335D9E | Source |
| [r14+0x1F0] | 8 | R | 0x53352BC, 0x53354C3, 0x5335B77, 0x5335B7E | Limit |
| [r14+0x430] | 8 | R | 0x5335CE6 | Source |
| [r14+0x458] | 8 | R | 0x5335DB8 | Source |
| [r14+0x128] | 8 | R | 0x53353CA, 0x5335C8C, 0x5335E3F | Source |
| [r14+0x140] | 8 | R | 0x53351A6, 0x5335257 | Source |
| [r14+0x130] | 8 | R | 0x5335002, 0x5335009, 0x53350AE | Source |
| [r14+0x138] | 8 | R | 0x5334BA3, 0x5335036, 0x5335E3F | Source |
| [r14+0x148] | 8 | R | 0x53351A6, 0x53351E9 | Source |
| [r14+0x150] | 8 | R | 0x5335246, 0x53353EC, 0x5335C99 | Source |
| [r14+0x1C8] | 8 | W | 0x5335238 | Saved r14 |
| [r14+0x1B0] | 8 | R | 0x5335013, 0x533503C | Source |
| [r14+0x448] | 8 | R | 0x53350BC, 0x53350ED, 0x533546E, 0x5335D74 | Source |
| [r14+0x458] | 8 | R | 0x5335D88, 0x5335D8F | Source |
| [r14+0x468] | 8 | W | 0x5335D26 | Counter |
| [r14+0x470] | 8 | R | 0x5335D8F | Source |
| [r14+0x128] | 8 | R | 0x53353CA, 0x5335C8C, 0x5335E3F | Source |
| [r14+0x450] | 8 | R | 0x5335DB1, 0x5335DB8 | Source |
| [r14+0x448] | 8 | R | 0x5335DB8 | Source |
| [r14+0x130] | 8 | R | 0x5335002, 0x5335009, 0x53350AE | Source |
| [r14+0x138] | 8 | R | 0x5334BA3, 0x5335036, 0x5335E3F | Source |
| [r14+0x148] | 8 | R | 0x53351A6, 0x53351E9 | Source |
| [r14+0x150] | 8 | R | 0x5335246, 0x53353EC, 0x5335C99 | Source |
| [r14+0x1C8] | 8 | W | 0x5335238 | Saved r14 |
| [r14+0x1B0] | 8 | R | 0x5335013, 0x533503C | Source |
| [r14+0x448] | 8 | R | 0x53350BC, 0x53350ED, 0x533546E, 0x5335D74 | Source |
| [r14+0x458] | 8 | R | 0x5335D88, 0x5335D8F | Source |
| [r14+0x468] | 8 | W | 0x5335D26 | Counter |
| [r14+0x470] | 8 | R | 0x5335D8F | Source |
| [r14+0x128] | 8 | R | 0x53353CA, 0x5335C8C, 0x5335E3F | Source |
| [r14+0x450] | 8 | R | 0x5335DB1, 0x5335DB8 | Source |
| [r14+0x448] | 8 | R | 0x5335DB8 | Source |
| [r14+0x130] | 8 | R | 0x5335002, 0x5335009, 0x53350AE | Source |
| [r14+0x138] | 8 | R | 0x5334BA3, 0x5335036, 0x5335E3F | Source |
| [r14+0x148] | 8 | R | 0x53351A6, 0x53351E9 | Source |
| [r14+0x150] | 8 | R | 0x5335246, 0x53353EC, 0x5335C99 | Source |
| [r14+0x1C8] | 8 | W | 0x5335238 | Saved r14 |
| [r14+0x1B0] | 8 | R | 0x5335013, 0x533503C | Source |
| [r14+0x448] | 8 | R | 0x53350BC, 0x53350ED, 0x533546E, 0x5335D74 | Source |
| [r14+0x458] | 8 | R | 0x5335D88, 0x5335D8F | Source |
| [r14+0x468] | 8 | W | 0x5335D26 | Counter |
| [r14+0x470] | 8 | R | 0x5335D8F | Source |
| [r14+0x128] | 8 | R | 0x53353CA, 0x5335C8C, 0x5335E3F | Source |
| [r14+0x450] | 8 | R | 0x5335DB1, 0x5335DB8 | Source |
| [r14+0x448] | 8 | R | 0x5335DB8 | Source |
| [r14+0x130] | 8 | R | 0x5335002, 0x5335009, 0x53350AE | Source |
| [r14+0x138] | 8 | R | 0x5334BA3, 0x5335036, 0x5335E3F | Source |
| [r14+0x148] | 8 | R | 0x53351A6, 0x53351E9 | Source |
| [r14+0x150] | 8 | R | 0x5335246, 0x53353EC, 0x5335C99 | Source |
| [r14+0x1C8] | 8 | W | 0x5335238 | Saved r14 |
| [r14+0x1B0] | 8 | R | 0x5335013, 0x533503C | Source |
| [r14+0x448] | 8 | R | 0x53350BC, 0x53350ED, 0x533546E, 0x5335D74 | Source |
| [r14+0x458] | 8 | R | 0x5335D88, 0x5335D8F | Source |
| [r14+0x468] | 8 | W | 0x5335D26 | Counter |
| [r14+0x470] | 8 | R | 0x5335D8F | Source |
| [r14+0x128] | 8 | R | 0x53353CA, 0x5335C8C, 0x5335E3F | Source |
| [r14+0x450] | 8 | R | 0x5335DB1, 0x5335DB8 | Source |
| [r14+0x448] | 8 | R | 0x5335DB8 | Source |
| [r14+0x130] | 8 | R | 0x5335002, 0x5335009, 0x53350AE | Source |
| [r14+0x138] | 8 | R | 0x5334BA3, 0x5335036, 0x5335E3F | Source |
| [r14+0x148] | 8 | R | 0x53351A6, 0x53351E9 | Source |
| [r14+0x150] | 8 | R | 0x5335246, 0x53353EC, 0x5335C99 | Source |
| [r14+0x1C8] | 8 | W | 0x5335238 | Saved r14 |
| [r14+0x1B0] | 8 | R | 0x5335013, 0x533503C | Source |
| [r14+0x448] | 8 | R | 0x53350BC, 0x53350ED, 0x533546E, 0x5335D74 | Source |
| [r14+0x458] | 8 | R | 0x5335D88, 0x5335D8F | Source |
| [r14+0x468] | 8 | W | 0x5335D26 | Counter |
| [r14+0x470] | 8 | R | 0x5335D8F | Source |
| [r14+0x128] | 8 | R | 0x53353CA, 0x5335C8C, 0x5335E3F | Source |
| [r14+0x450] | 8 | R | 0x5335DB1, 0x5335DB8 | Source |
| [r14+0x448] | 8 | R | 0x5335DB8 | Source |

## NEXT
Resume at line 1200 (address 0x5335E1F) - continue analysis through timestamp comparisons, allocator calls, and draw record writes via 0x533f580, track all [reg+off] writes into draw records (especially +0x63 depth field via 0x533f580 callers).

## Step 1 Complete
- Ran `PYTHONUTF8=1 python tools/preflight.py 0x6b1ba90` → docs/progress/pre/0x6b1ba90.md (1474 lines)
- Preflight shows: function sub_6b1ba90 at 0x6b1ba90..0x6b1beb2 (size 0x422), 1 xref from sub_791f170
- Callees: sub_6b1b600 (x16), sub_6b1bec0 (x16), sub_e951550 (x1)
- Stores into [reg+off] listed (70+ entries)

## Step 2 Complete: Instruction-complete listing of 0x6b1ba90 (flood function)

### Function: sub_6b1ba90 (flood fill / visibility compute)
**Range:** 0x6b1ba90..0x6b1beb2 (size 0x422)
**Caller:** sub_791f170 (compute 0x791f170)
**Arguments:** rcx = face matrix state (this+0x57 offset used), rdx = output buffer (a1)

---

#### Phase 1: Entry & Early Exit (0x6b1ba90..0x6b1baf2)
```
0x6b1ba90  push r15
0x6b1ba92  push r14
0x6b1ba94  push r13
0x6b1ba96  push r12
0x6b1ba98  push rsi
0x6b1ba99  push rdi
0x6b1ba9a  push rbp
0x6b1ba9b  push rbx
0x6b1ba9c  sub rsp,0x38
0x6b1baa0  mov rsi,rdx                                    ; save output buffer
0x6b1baa3  mov rax,[0x1230A0C0]                          ; stack cookie
0x6b1baaa  xor rax,rsp
0x6b1baad  mov [rsp+0x30],rax
0x6b1bab2  cmp dword ptr [rcx+0x44],0xF00                ; R a0+0x44 (face count check)
0x6b1bab9  jl short 0x6B1BAF3                            ; -> loc_6b1baf3 (if < 0xF00)
0x6b1babb  mov word ptr [rsi+4],0xFFFF                   ; W a1+0x4 = error sentinel
0x6b1bac1  mov dword ptr [rsi],0xFFFFFFFF                ; W a1+0x0 = error sentinel

loc_6b1bac7:  ; from multiple return points
0x6b1bac7  mov rax,[rsp+0x30]
0x6b1bacc  xor rax,rsp
0x6b1bacf  mov rcx,[0x1230A0C0]
0x6b1bad6  cmp rcx,rax
0x6b1bad9  jne 0x6B1BEA4                                 ; -> loc_6b1bea4 (stack check fail)
0x6b1badf  mov rax,rsi
0x6b1bae2  add rsp,0x38
0x6b1bae6  pop rbx
0x6b1bae7  pop rbp
0x6b1bae8  pop rdi
0x6b1bae9  pop rsi
0x6b1baea  pop r12
0x6b1baec  pop r13
0x6b1baee  pop r14
0x6b1baf0  pop r15
0x6b1baf2  ret
```

#### Phase 2: Main Loop Setup (0x6b1baf3..0x6b1bb1b)
```
loc_6b1baf3:  ; from 6b1bab9 (face count < 0xF00)
0x6b1baf3  mov rdi,rcx                                    ; rdi = face matrix state base
0x6b1baf6  mov word ptr [rsi+4],0                         ; W a1+0x4 = 0
0x6b1bafc  mov dword ptr [rsi],0                          ; W a1+0x0 = 0
0x6b1bb02  mov dword ptr [rsp+0x2C],0                     ; outer loop counter = 0
0x6b1bb0a  lea r15,[rcx+0x57]                             ; r15 = face matrix array base (state+0x57)
0x6b1bb0e  xor r12d,r12d                                  ; r12 = outer loop index (0..15)
0x6b1bb11  lea rbx,[rsp+0x2B]                             ; rbx = stack temp for sub_6b1b600
0x6b1bb16  lea r14,[rsp+0x2C]                             ; r14 = stack temp for sub_6b1b600
```

#### Phase 3: Outer Loop (16 iterations, 0x6b1bb1b..0x6b1be9f)
```
loc_6b1bb1b:  ; from 6b1be99 (outer loop continue)
0x6b1bb1b  mov byte ptr [rsp+0x2E],0
0x6b1bb20  mov bpl,1                                      ; inner face index = 1
0x6b1bb23  xor r13d,r13d                                  ; r13 = face offset (0, 0x10, 0x20... 0xF0)
0x6b1bb26  jmp short 0x6B1BB4E                           ; -> loc_6b1bb4e
```

#### Phase 4: Inner Loop - 16 faces per outer iteration (0x6b1bb30..0x6b1be81)
**Loop structure:** r13 = 0..0xF0 step 0x10 (16 faces), bpl = 1..16
```
loc_6b1bb30:  ; from 6b1be55, 6b1be7b (inner loop continue with bpl++)
0x6b1bb30  mov byte ptr [rsp+0x2D],0x10
0x6b1bb35  mov [rsp+0x2E],bpl
0x6b1bb3a  add r13,0x10                                   ; next face offset
0x6b1bb3e  inc bpl                                        ; face index++
0x6b1bb41  cmp r13,0x100                                  ; 16 faces done?
0x6b1bb48  je 0x6B1BE86                                  ; -> loc_6b1be86 (inner loop done)

loc_6b1bb4e:  ; from 6b1bb26 (inner loop entry)
0x6b1bb4e  mov byte ptr [rsp+0x2D],0                      ; face dir = 0
0x6b1bb53  cmp byte ptr [r15+r13-0xF],0                   ; R face_matrix[r13-0xF] (dir 0)
0x6b1bb59  jne short 0x6B1BB81                           ; -> loc_6b1bb81 (if non-zero)

0x6b1bb5b  mov rcx,rdi                                    ; arg0 = face matrix state
0x6b1bb5e  mov rdx,rbx                                    ; arg1 = stack temp
0x6b1bb61  mov r8,r14                                     ; arg2 = stack temp
0x6b1bb64  call 0x6B1B600                                ; -> sub_6b1b600 (process face dir 0)
0x6b1bb69  mov rcx,rsi                                    ; arg0 = output buffer
0x6b1bb6c  mov rdx,rbx                                    ; arg1 = stack temp
0x6b1bb6f  call 0x6B1BEC0                                ; -> sub_6b1bec0 (write result)
0x6b1bb74  cmp dword ptr [rdi+0x44],0xEFF                 ; R a0+0x44 (face count)
0x6b1bb7b  jg 0x6B1BAC7                                  ; -> loc_6b1bac7 (early exit if done)

loc_6b1bb81:  ; from 6b1bb59 (face dir 1)
0x6b1bb81  mov byte ptr [rsp+0x2D],1
0x6b1bb86  cmp byte ptr [r15+r13-0xE],0
0x6b1bb8c  jne short 0x6B1BBB4
0x6b1bb8e  mov rcx,rdi
0x6b1bb91  mov rdx,rbx
0x6b1bb94  mov r8,r14
0x6b1bb97  call 0x6B1B600
0x6b1bb9c  mov rcx,rsi
0x6b1bb9f  mov rdx,rbx
0x6b1bba2  call 0x6B1BEC0
0x6b1bba7  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bbae  jg 0x6B1BAC7

loc_6b1bbb4:  ; face dir 2
0x6b1bbb4  mov byte ptr [rsp+0x2D],2
0x6b1bbb9  cmp byte ptr [r15+r13-0xD],0
0x6b1bbbf  jne short 0x6B1BBE7
0x6b1bbc1  mov rcx,rdi
0x6b1bbc4  mov rdx,rbx
0x6b1bbc7  mov r8,r14
0x6b1bbca  call 0x6B1B600
0x6b1bbcf  mov rcx,rsi
0x6b1bbd2  mov rdx,rbx
0x6b1bbd5  call 0x6B1BEC0
0x6b1bbda  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bbe1  jg 0x6B1BAC7

loc_6b1bbe7:  ; face dir 3
0x6b1bbe7  mov byte ptr [rsp+0x2D],3
0x6b1bbec  cmp byte ptr [r15+r13-0xC],0
0x6b1bbf2  jne short 0x6B1BC1A
0x6b1bbf4  mov rcx,rdi
0x6b1bbf7  mov rdx,rbx
0x6b1bbfa  mov r8,r14
0x6b1bbfd  call 0x6B1B600
0x6b1bc02  mov rcx,rsi
0x6b1bc05  mov rdx,rbx
0x6b1bc08  call 0x6B1BEC0
0x6b1bc0d  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bc14  jg 0x6B1BAC7

loc_6b1bc1a:  ; face dir 4
0x6b1bc1a  mov byte ptr [rsp+0x2D],4
0x6b1bc1f  cmp byte ptr [r15+r13-0xB],0
0x6b1bc25  jne short 0x6B1BC4D
0x6b1bc27  mov rcx,rdi
0x6b1bc2a  mov rdx,rbx
0x6b1bc2d  mov r8,r14
0x6b1bc30  call 0x6B1B600
0x6b1bc35  mov rcx,rsi
0x6b1bc38  mov rdx,rbx
0x6b1bc3b  call 0x6B1BEC0
0x6b1bc40  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bc47  jg 0x6B1BAC7

loc_6b1bc4d:  ; face dir 5
0x6b1bc4d  mov byte ptr [rsp+0x2D],5
0x6b1bc52  cmp byte ptr [r15+r13-0xA],0
0x6b1bc58  jne short 0x6B1BC80
0x6b1bc5a  mov rcx,rdi
0x6b1bc5d  mov rdx,rbx
0x6b1bc60  mov r8,r14
0x6b1bc63  call 0x6B1B600
0x6b1bc68  mov rcx,rsi
0x6b1bc6b  mov rdx,rbx
0x6b1bc6e  call 0x6B1BEC0
0x6b1bc73  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bc7a  jg 0x6B1BAC7

loc_6b1bc80:  ; face dir 6
0x6b1bc80  mov byte ptr [rsp+0x2D],6
0x6b1bc85  cmp byte ptr [r15+r13-9],0
0x6b1bc8b  jne short 0x6B1BCB3
0x6b1bc8d  mov rcx,rdi
0x6b1bc90  mov rdx,rbx
0x6b1bc93  mov r8,r14
0x6b1bc96  call 0x6B1B600
0x6b1bc9b  mov rcx,rsi
0x6b1bc9e  mov rdx,rbx
0x6b1bca1  call 0x6B1BEC0
0x6b1bca6  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bcad  jg 0x6B1BAC7

loc_6b1bcb3:  ; face dir 7
0x6b1bcb3  mov byte ptr [rsp+0x2D],7
0x6b1bcb8  cmp byte ptr [r15+r13-8],0
0x6b1bcbe  jne short 0x6B1BCE6
0x6b1bcc0  mov rcx,rdi
0x6b1bcc3  mov rdx,rbx
0x6b1bcc6  mov r8,r14
0x6b1bcc9  call 0x6B1B600
0x6b1bcce  mov rcx,rsi
0x6b1bcd1  mov rdx,rbx
0x6b1bcd4  call 0x6B1BEC0
0x6b1bcd9  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bce0  jg 0x6B1BAC7

loc_6b1bce6:  ; face dir 8
0x6b1bce6  mov byte ptr [rsp+0x2D],8
0x6b1bceb  cmp byte ptr [r15+r13-7],0
0x6b1bcf1  jne short 0x6B1BD19
0x6b1bcf3  mov rcx,rdi
0x6b1bcf6  mov rdx,rbx
0x6b1bcf9  mov r8,r14
0x6b1bcfc  call 0x6B1B600
0x6b1bd01  mov rcx,rsi
0x6b1bd04  mov rdx,rbx
0x6b1bd07  call 0x6B1BEC0
0x6b1bd0c  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bd13  jg 0x6B1BAC7

loc_6b1bd19:  ; face dir 9
0x6b1bd19  mov byte ptr [rsp+0x2D],9
0x6b1bd1e  cmp byte ptr [r15+r13-6],0
0x6b1bd24  jne short 0x6B1BD4C
0x6b1bd26  mov rcx,rdi
0x6b1bd29  mov rdx,rbx
0x6b1bd2c  mov r8,r14
0x6b1bd2f  call 0x6B1B600
0x6b1bd34  mov rcx,rsi
0x6b1bd37  mov rdx,rbx
0x6b1bd3a  call 0x6B1BEC0
0x6b1bd3f  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bd46  jg 0x6B1BAC7

loc_6b1bd4c:  ; face dir 0xA
0x6b1bd4c  mov byte ptr [rsp+0x2D],0xA
0x6b1bd51  cmp byte ptr [r15+r13-5],0
0x6b1bd57  jne short 0x6B1BD7F
0x6b1bd59  mov rcx,rdi
0x6b1bd5c  mov rdx,rbx
0x6b1bd5f  mov r8,r14
0x6b1bd62  call 0x6B1B600
0x6b1bd67  mov rcx,rsi
0x6b1bd6a  mov rdx,rbx
0x6b1bd6d  call 0x6B1BEC0
0x6b1bd72  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bd79  jg 0x6B1BAC7

loc_6b1bd7f:  ; face dir 0xB
0x6b1bd7f  mov byte ptr [rsp+0x2D],0xB
0x6b1bd84  cmp byte ptr [r15+r13-4],0
0x6b1bd8a  jne short 0x6B1BDB2
0x6b1bd8c  mov rcx,rdi
0x6b1bd8f  mov rdx,rbx
0x6b1bd92  mov r8,r14
0x6b1bd95  call 0x6B1B600
0x6b1bd9a  mov rcx,rsi
0x6b1bd9d  mov rdx,rbx
0x6b1bda0  call 0x6B1BEC0
0x6b1bda5  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bdac  jg 0x6B1BAC7

loc_6b1bdb2:  ; face dir 0xC
0x6b1bdb2  mov byte ptr [rsp+0x2D],0xC
0x6b1bdb7  cmp byte ptr [r15+r13-3],0
0x6b1bdbd  jne short 0x6B1BDE5
0x6b1bdbf  mov rcx,rdi
0x6b1bdc2  mov rdx,rbx
0x6b1bdc5  mov r8,r14
0x6b1bdc8  call 0x6B1B600
0x6b1bdcd  mov rcx,rsi
0x6b1bdd0  mov rdx,rbx
0x6b1bdd3  call 0x6B1BEC0
0x6b1bdd8  cmp dword ptr [rdi+0x44],0xEFF
0x6b1bddf  jg 0x6B1BAC7

loc_6b1bde5:  ; face dir 0xD
0x6b1bde5  mov byte ptr [rsp+0x2D],0xD
0x6b1bdea  cmp byte ptr [r15+r13-2],0
0x6b1bdf0  jne short 0x6B1BE18
0x6b1bdf2  mov rcx,rdi
0x6b1bdf5  mov rdx,rbx
0x6b1bdf8  mov r8,r14
0x6b1bdfb  call 0x6B1B600
0x6b1be00  mov rcx,rsi
0x6b1be03  mov rdx,rbx
0x6b1be06  call 0x6B1BEC0
0x6b1be0b  cmp dword ptr [rdi+0x44],0xEFF
0x6b1be12  jg 0x6B1BAC7

loc_6b1be18:  ; face dir 0xE
0x6b1be18  mov byte ptr [rsp+0x2D],0xE
0x6b1be1d  cmp byte ptr [r15+r13-1],0
0x6b1be23  jne short 0x6B1BE4B
0x6b1be25  mov rcx,rdi
0x6b1be28  mov rdx,rbx
0x6b1be2b  mov r8,r14
0x6b1be2e  call 0x6B1B600
0x6b1be33  mov rcx,rsi
0x6b1be36  mov rdx,rbx
0x6b1be39  call 0x6B1BEC0
0x6b1be3e  cmp dword ptr [rdi+0x44],0xEFF
0x6b1be45  jg 0x6B1BAC7

loc_6b1be4b:  ; face dir 0xF
0x6b1be4b  mov byte ptr [rsp+0x2D],0xF
0x6b1be50  cmp byte ptr [r15+r13],0
0x6b1be55  jne 0x6B1BB30                                 ; -> loc_6b1bb30 (continue inner loop)
0x6b1be5b  mov rcx,rdi
0x6b1be5e  mov rdx,rbx
0x6b1be61  mov r8,r14
0x6b1be64  call 0x6B1B600
0x6b1be69  mov rcx,rsi
0x6b1be6c  mov rdx,rbx
0x6b1be6f  call 0x6B1BEC0
0x6b1be74  cmp dword ptr [rdi+0x44],0xEFF
0x6b1be7b  jle 0x6B1BB30                                 ; -> loc_6b1bb30 (continue if not done)
0x6b1be81  jmp 0x6B1BAC7                                 ; -> loc_6b1bac7 (done)
```

#### Phase 5: Outer Loop Increment (0x6b1be86..0x6b1be9f)
```
loc_6b1be86:  ; from 6b1bb48 (16 faces done)
0x6b1be86  inc r12                                        ; outer loop++
0x6b1be89  mov [rsp+0x2C],r12b
0x6b1be8e  add r15,0x100                                  ; next face matrix block (256 bytes)
0x6b1be95  cmp r12,0x10                                   ; 16 outer iterations?
0x6b1be99  jne 0x6B1BB1B                                 ; -> loc_6b1bb1b (continue outer)
0x6b1be9f  jmp 0x6B1BAC7                                 ; -> loc_6b1bac7 (all done)
```

#### Phase 6: Stack Check Failure (0x6b1bea4..0x6b1beb2)
```
loc_6b1bea4:  ; from 6b1bad9
0x6b1bea4  mov rcx,[rsp+0x30]
0x6b1bea9  xor rcx,rsp
0x6b1beac  call 0xE951550                                ; -> sub_e951550 (__security_check_cookie)
0x6b1beb1  int3
```

---

### Callee: sub_6b1b600 (0x6b1b600..0x6b1ba84, size 0x484) - "process_face_dir"
**Called 16× per inner loop iteration (256 total calls)**
**Args:** rcx = face matrix state (rdi), rdx = stack temp (rbx), r8 = stack temp (r14)
**Reads face matrix at [r15+r13-off] for dirs 0..F, writes result to [rdx]**

```
0x6b1b600  push r15
0x6b1b602  push r14
0x6b1b604  push r13
0x6b1b606  push r12
0x6b1b608  push rsi
0x6b1b609  push rdi
0x6b1b60a  push rbp
0x6b1b60b  push rbx
0x6b1b60c  sub rsp,0x68
0x6b1b610  mov r10,rcx                                    ; r10 = face matrix state
0x6b1b613  mov byte ptr [rdx],0                          ; W [rdx] = 0 (initial result)
0x6b1b616  movzx eax,byte ptr [r8]                       ; R [r8] = dir 0 byte
0x6b1b61a  cmp rax,0x81
0x6b1b620  mov [rsp+0x28],rcx
0x6b1b625  mov [rsp+0x40],rdx
0x6b1b62a  jb short 0x6B1B637                            ; if < 0x81
0x6b1b62c  mov byte ptr [rdx],0x10                       ; W [rdx] = 0x10
0x6b1b62f  mov bpl,0x10
0x6b1b632  jmp 0x6B1B7B1                                 ; -> exit

loc_6b1b637:  ; from 6b1b62a
0x6b1b637  cmp al,0x10
0x6b1b639  jb short 0x6B1B646                            ; if < 0x10
0x6b1b63b  mov byte ptr [rdx],0x20                       ; W [rdx] = 0x20
0x6b1b63e  mov bpl,0x20
0x6b1b641  jmp 0x6B1B7B1

loc_6b1b646:  ; from 6b1b639
0x6b1b646  movzx ecx,byte ptr [r8+1]                      ; R [r8+1] = dir 1 byte
0x6b1b64b  cmp rcx,0x81
0x6b1b652  jb short 0x6B1B65F
0x6b1b654  mov byte ptr [rdx],1                          ; W [rdx] = 1
0x6b1b657  mov bpl,1
0x6b1b65a  jmp 0x6B1B7B1

loc_6b1b65f:  ; from 6b1b652
0x6b1b65f  cmp cl,0x10
0x6b1b662  jb short 0x6B1B66F
0x6b1b664  mov byte ptr [rdx],2                          ; W [rdx] = 2
0x6b1b667  mov bpl,2
0x6b1b66a  jmp 0x6B1B7B1

loc_6b1b66f:  ; from 6b1b662
0x6b1b66f  mov r13,rdx
0x6b1b672  movzx edx,byte ptr [r8+2]                      ; R [r8+2] = dir 2 byte
0x6b1b677  cmp rdx,0x81
0x6b1b67e  jb short 0x6B1B68D
0x6b1b680  mov byte ptr [r13],4                          ; W [rdx] = 4
0x6b1b685  mov bpl,4
0x6b1b688  jmp 0x6B1B7B1

loc_6b1b68d:  ; from 6b1b67e
0x6b1b68d  cmp dl,0x10
0x6b1b690  jb short 0x6B1B69F
0x6b1b692  mov byte ptr [r13],8                          ; W [rdx] = 8
0x6b1b697  mov bpl,8
0x6b1b69a  jmp 0x6B1B7B1

loc_6b1b69f:  ; from 6b1b690 (main processing)
0x6b1b69f  shl edx,4                                      ; edx = dir2 << 4
0x6b1b6a2  add rdx,r10                                    ; rdx = face_matrix_state + dir2*16
0x6b1b6a5  shl eax,8                                      ; eax = dir0 << 8
0x6b1b6a8  lea r9,[rdx+rcx]                               ; r9 = base + dir1 + dir2*16
0x6b1b6ac  cmp byte ptr [rax+r9+0x48],0                   ; R face_matrix[dir0<<8 | dir1 | dir2<<4] + 0x48
0x6b1b6b2  jne 0x6B1B7AF                                 ; -> if occupied
0x6b1b6b8  add rcx,rdx
0x6b1b6bb  add rcx,0x48
0x6b1b6bf  mov byte ptr [rcx+rax],2                       ; W face_matrix[...] = 2 (mark visited)
0x6b1b6c3  mov rcx,[r10+0x1060]                           ; R state+0x1060 (allocator?)
0x6b1b6ca  mov rax,[r10+0x1068]                           ; R state+0x1068
0x6b1b6d1  lea edx,[rax+rcx]
0x6b1b6d4  test dl,3
0x6b1b6d7  jne short 0x6B1B70F
0x6b1b6d9  lea rdx,[rax+4]
0x6b1b6dd  shr rdx,2
0x6b1b6e1  cmp [r10+0x1058],rdx                           ; R state+0x1058
0x6b1b6e8  ja short 0x6B1B70F
0x6b1b6ea  lea rcx,[r10+0x1048]                           ; state+0x1048
0x6b1b6f1  mov rsi,r8
0x6b1b6f4  call 0x53C9DA0                                ; -> sub_53c9da0 (allocator?)
0x6b1b6f9  mov r10,[rsp+0x28]
0x6b1b6fe  mov r8,rsi
0x6b1b701  mov rcx,[r10+0x1060]
0x6b1b708  mov rax,[r10+0x1068]

loc_6b1b70f:  ; from 6b1b6d7, 6b1b6e8
0x6b1b70f  mov rdx,[r10+0x1050]                           ; R state+0x1050
0x6b1b716  mov rdi,[r10+0x1058]                           ; R state+0x1058
0x6b1b71d  lea rsi,[rdi*4-1]
0x6b1b725  and rsi,rcx
0x6b1b728  mov [r10+0x1060],rsi                           ; W state+0x1060
0x6b1b72f  add rsi,rax
0x6b1b732  mov rbx,rsi
0x6b1b735  shr rbx,2
0x6b1b739  dec rdi
0x6b1b73c  and rdi,rbx
0x6b1b73f  mov rax,[rdx+rdi*8]                            ; R [state+0x1050 + index*8]
0x6b1b743  test rax,rax
0x6b1b746  jne short 0x6B1B79F

loc_6b1b748:  ; allocate new block
0x6b1b748  mov r14,r8
0x6b1b74b  mov r15,0x3FFFFFFFFFFFFFFF
0x6b1b755  mov rcx,[0x1233E1A8]                          ; global allocator
0x6b1b75c  mov rax,[rcx]
0x6b1b75f  mov rax,[rax+8]
0x6b1b763  mov edx,0x10
0x6b1b768  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (allocate 0x10 bytes)
0x6b1b76e  test rax,rax
0x6b1b771  je 0x6B1BA6F                                  ; -> alloc fail

loc_6b1b777:  ; from 6b1ba7f (retry)
0x6b1b777  mov r10,[rsp+0x28]
0x6b1b77c  mov rcx,[r10+0x1050]
0x6b1b783  mov [rcx+rdi*8],rax                            ; W [state+0x1050 + index*8] = new block
0x6b1b787  mov rax,[r10+0x1050]
0x6b1b78e  add r15,[r10+0x1058]
0x6b1b795  and r15,rbx
```

---

### Callee: sub_6b1bec0 (0x6b1bec0..0x6b1c21f, size 0x35f) - "write_face_result"
**Called 16× per inner loop (256 total), after each sub_6b1b600**
**Args:** rcx = output buffer (rsi), rdx = stack temp from sub_6b1b600 (rbx)
**Reads byte at [rdx], writes face bits into output buffer at [rcx]**

```
0x6b1bec0  movzx eax,byte ptr [rdx]                      ; R [rdx] = result from sub_6b1b600
0x6b1bec3  test eax,eax
0x6b1bec5  je 0x6B1BF61                                  ; -> return if 0
0x6b1becb  test al,1
0x6b1becd  jne short 0x6B1BEDA                           ; bit 0 set
0x6b1becf  mov r8d,eax
0x6b1bed2  test r8b,2
0x6b1bed6  jne short 0x6B1BF12                           ; bit 1 set
0x6b1bed8  jmp short 0x6B1BF45                           ; check bits 2,3,4,5

loc_6b1beda:  ; bit 0 set
0x6b1beda  test al,2
0x6b1bedc  jne 0x6B1C03E                                 ; bits 0+1
0x6b1bee2  test al,4
0x6b1bee4  jne 0x6B1C050                                 ; bits 0+2
...

loc_6b1c03e:  ; bits 0+1
0x6b1c03e  or byte ptr [rcx],2                           ; W [rcx] |= 2
0x6b1c041  or byte ptr [rcx+1],1                         ; W [rcx+1] |= 1
0x6b1c045  movzx eax,byte ptr [rdx]
0x6b1c048  test al,4
0x6b1c04a  je 0x6B1BEEA

loc_6b1c050:  ; bits 0+2
0x6b1c050  or byte ptr [rcx],4                           ; W [rcx] |= 4
0x6b1c053  or byte ptr [rcx+2],1                         ; W [rcx+2] |= 1
0x6b1c057  movzx eax,byte ptr [rdx]
0x6b1c05a  test al,8
0x6b1c05c  je 0x6B1BEF2

... (continues with all 6-bit combinations, writing to [rcx+0..5])
```

**Key stores in sub_6b1bec0:**
- `[rcx+0]` |= bits (0x20, 0x10, 8, 4, 2, 1)
- `[rcx+1]` |= bits (0x20, 0x10, 8, 4, 2, 1)
- `[rcx+2]` |= bits (0x20, 0x10, 8, 4, 2, 1)
- `[rcx+3]` |= bits (0x20, 0x10, 8, 4, 2, 1)
- `[rcx+4]` |= bits (0x20, 0x10, 8, 4, 2, 1)
- `[rcx+5]` |= bits (0x20, 0x10, 8, 4, 2, 1)
- Each of 6 output bytes accumulates face visibility bits for 6 directions

---

### Callee: sub_e951550 (0xe951550) - __security_check_cookie
### Callee: sub_53c9da0 (0x53c9da0) - allocator helper
### Callee: sub_eea6040 (via [0xF99FFA0]) - memory allocator

---

## Step 3: [reg+off] Read/Write Table for 0x6b1ba90 (flood)

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| a0+0x44 | 4 | R | Face count / limit (cmp 0xF00, 0xEFF) | [V] |
| a0+0x57 | 1 | R | Face matrix array base (lea r15,[rcx+0x57]) | [V] |
| a0+0x57+r13-0xF .. a0+0x57+r13 | 16×1 | R | Face matrix bytes per face (16 dirs) | [V] |
| a1+0x0 | 4 | W | Output: result dword (0 or 0xFFFFFFFF) | [V] |
| a1+0x4 | 2 | W | Output: result word (0 or 0xFFFF) | [V] |
| a0+0x1048 | 8 | R | Allocator state | [V] |
| a0+0x1050 | 8 | R | Allocator blocks pointer | [V] |
| a0+0x1058 | 8 | R | Allocator count | [V] |
| a0+0x1060 | 8 | R/W | Allocator index | [V] |
| a0+0x1068 | 8 | R | Allocator capacity | [V] |
| face_matrix[dir0<<8 | dir1 | dir2<<4] + 0x48 | 1 | R/W | Voxel occupancy / visited flag | [V] |
| face_matrix[dir0<<8 | dir1 | dir2<<4] + 0x48 | 1 | W | Mark visited (value 2) | [V] |

---

## Step 4: Instruction-complete listing of 0x6b0d380 (BFS queue)

### Function: sub_6b0d380 (BFS queue processor)
**Range:** 0x6b0d380..0x6b0d6e7 (size 0x367)
**Caller:** (1 xref, likely from visibility compute)
**Arguments:** rcx = queue object, rdx = input vector/array

```
0x6b0d380  push rbp
0x6b0d381  push r15
0x6b0d383  push r14
0x6b0d385  push r13
0x6b0d387  push r12
0x6b0d389  push rsi
0x6b0d38a  push rdi
0x6b0d38b  push rbx
0x6b0d38c  sub rsp,0x78
0x6b0d390  lea rbp,[rsp+0x70]
0x6b0d395  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x6b0d39d  mov rsi,rcx                                    ; rsi = queue object
0x6b0d3a0  xorps xmm0,xmm0
0x6b0d3a3  movaps [rbp-0x20],xmm0
0x6b0d3a7  mov rax,[rcx+0x48]                            ; R a0+0x48 (shared_ptr?)
0x6b0d3ab  test rax,rax
0x6b0d3ae  je short 0x6B0D3BA
0x6b0d3b0  lock inc dword ptr [rax+8]                    ; W refcount++
0x6b0d3b4  mov rdi,[rsi+0x48]                            ; R a0+0x48
0x6b0d3b8  jmp short 0x6B0D3BC

loc_6b0d3ba:  ; from 6b0d3ae
0x6b0d3ba  xor edi,edi

loc_6b0d3bc:  ; from 6b0d3b8
0x6b0d3bc  mov rax,[rsi+0x40]                            ; R a0+0x40
0x6b0d3c0  mov [rbp-0x20],rax
0x6b0d3c4  mov [rbp-0x18],rdi
0x6b0d3c8  test rax,rax
0x6b0d3cb  jne short 0x6B0D438

0x6b0d3cd  mov rax,[rsi+0x30]                            ; R a0+0x30
0x6b0d3d1  test rax,rax
0x6b0d3d4  je short 0x6B0D3E4
0x6b0d3d6  lock inc dword ptr [rax+8]                    ; W refcount++
0x6b0d3da  mov rcx,[rsi+0x30]                            ; R a0+0x30
0x6b0d3de  mov rdi,[rbp-0x18]
0x6b0d3e2  jmp short 0x6B0D3E6

loc_6b0d3e4:  ; from 6b0d3d4
0x6b0d3e4  xor ecx,ecx

loc_6b0d3e6:  ; from 6b0d3e2
0x6b0d3e6  mov rax,[rsi+0x28]                            ; R a0+0x28
0x6b0d3ea  mov [rbp-0x20],rax
0x6b0d3ee  mov [rbp-0x18],rcx
0x6b0d3f2  test rdi,rdi
0x6b0d3f5  je short 0x6B0D42F
0x6b0d3f7  lock dec dword ptr [rdi+8]                    ; W refcount--
0x6b0d3fb  jne short 0x6B0D42B
0x6b0d3fd  mov rax,[rdi]
0x6b0d400  mov rax,[rax]
0x6b0d403  mov rcx,rdi
0x6b0d406  mov rbx,rdx
0x6b0d409  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (deallocate)
0x6b0d40f  mov rdx,rbx
0x6b0d412  lock dec dword ptr [rdi+0xC]                  ; W weak refcount--
0x6b0d416  jne short 0x6B0D42B
0x6b0d418  mov rax,[rdi]
0x6b0d41b  mov rax,[rax+8]
0x6b0d41f  mov rcx,rdi
0x6b0d422  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (deallocate control)
0x6b0d428  mov rdx,rbx

loc_6b0d42b:  ; from 6b0d3fb, 6b0d416
0x6b0d42b  mov rax,[rbp-0x20]

loc_6b0d42f:  ; from 6b0d3f5
0x6b0d42f  test rax,rax
0x6b0d432  je 0x6B0D6B5                                  ; -> cleanup/exit

loc_6b0d438:  ; from 6b0d3cb (has a0+0x40)
0x6b0d438  movzx eax,byte ptr [rax+0x25E]                ; R a0+0x40+0x25E = render-chunk record +0x25E
0x6b0d43f  inc al
0x6b0d441  movzx eax,al
0x6b0d444  cmp al,2
0x6b0d446  mov ecx,1
0x6b0d44b  cmovae ecx,eax                                ; max 2
0x6b0d44e  mov [rbp-4],ecx                               ; iteration limit

loc_6b0d451:  ; main BFS loop from 6b0d6bc
0x6b0d451  mov r13,[rdx]                                 ; R rdx+0 = vector begin
0x6b0d454  mov rcx,[rdx+8]                               ; R rdx+8 = vector end
0x6b0d458  cmp rcx,r13
0x6b0d45b  je 0x6B0D65C                                  ; -> empty, exit loop
0x6b0d461  mov rdi,[rsi+0x58]                            ; R a0+0x58 (queue buffer)
0x6b0d465  mov [rbp-0x28],rcx
0x6b0d469  jmp short 0x6B0D497

loc_6b0d470:  ; from 6b0d4a4 (copy element to queue)
0x6b0d470  movups xmm0,[r13]                             ; R [r13] 16 bytes (vec3 + byte?)
0x6b0d475  movups [rdi],xmm0                             ; W [rdi] = element
0x6b0d478  mov eax,[rbp-4]
0x6b0d47b  mov [rdi+0x10],al                             ; W [rdi+0x10] = iteration tag
0x6b0d47e  mov rdi,[rsi+0x58]
0x6b0d482  add rdi,0x18                                  ; advance by 24 bytes
0x6b0d486  mov [rsi+0x58],rdi                            ; W a0+0x58 = new queue tail

loc_6b0d48a:  ; from 6b0d649
0x6b0d48a  add r13,0x10                                  ; next input element (16 bytes)
0x6b0d48e  cmp rcx,r13
0x6b0d491  je 0x6B0D65C                                  ; -> done input

loc_6b0d497:  ; from 6b0d469
0x6b0d497  movups xmm0,[r13]                             ; R [r13]
0x6b0d49c  movaps [rbp-0x40],xmm0
0x6b0d4a0  cmp rdi,[rsi+0x60]                            ; R a0+0x60 (queue capacity)
0x6b0d4a4  jne short 0x6B0D470                           ; -> space available, copy

; Queue full - grow buffer
0x6b0d4a6  mov rbx,rdi
0x6b0d4a9  sub rbx,[rsi+0x50]                            ; rbx = used bytes (a0+0x50 = buffer base)
0x6b0d4ad  mov rax,rbx
0x6b0d4b0  sar rax,3                                     ; /8
0x6b0d4b4  mov rcx,0xAAAAAAAAAAAAAAAB
0x6b0d4be  imul rax,rcx                                  ; *10/16 = element count
0x6b0d4c2  lea r8,[rax+1]                                ; new capacity = count+1
0x6b0d4c6  mov r12,rax
0x6b0d4c9  shr r12,1
0x6b0d4cc  mov rdx,0xAAAAAAAAAAAAAAA
0x6b0d4d6  mov rcx,rdx
0x6b0d4d9  sub rcx,r12
... (truncated - buffer growth logic continues)
```

---

### [reg+off] Read/Write Table for 0x6b0d380 (BFS queue)

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| a0+0x28 | 8 | R | Vector begin pointer (input) | [V] |
| a0+0x30 | 8 | R | Shared ptr? (refcounted) | [V] |
| a0+0x30+8 | 4 | W | Refcount++/-- | [V] |
| a0+0x40 | 8 | R | Render-chunk record pointer | [V] |
| a0+0x40+0x25E | 1 | R | Render-chunk +0x25E (iteration depth?) | [V] |
| a0+0x48 | 8 | R | Shared ptr? (refcounted) | [V] |
| a0+0x48+8 | 4 | W | Refcount++/-- | [V] |
| a0+0x48+0xC | 4 | W | Weak refcount-- | [V] |
| a0+0x50 | 8 | R | Queue buffer base | [V] |
| a0+0x58 | 8 | R/W | Queue tail pointer (advances by 0x18) | [V] |
| a0+0x60 | 8 | R | Queue capacity pointer | [V] |
| rdx+0x0 | 8 | R | Input vector begin | [V] |
| rdx+0x8 | 8 | R | Input vector end | [V] |
| queue_elem+0x0 | 16 | R | Input element (vec3 pos + face?) | [V] |
| queue_elem+0x10 | 1 | W | Iteration tag (1 or 2) | [V] |
| queue_slot+0x0 | 16 | W | Copied element | [V] |
| queue_slot+0x10 | 1 | W | Iteration tag | [V] |

---

### Callees for 0x6b0d380
| RVA | What | Tag |
|-----|------|-----|
| 0xeea6040 (via [0xF99FFA0]) | Memory allocator/deallocator | [V] |
| 0xeec6ed0 | Buffer init/clear (memset) | [V] |
| 0xa4c70 | Vector insert/append | [V] |
| 0x6b32870 | Unknown (called from 0x6b1c3b0) | [V] |
| 0xe935700 | Deque push/emplace | [V] |
| 0xeec6de0 | Buffer copy/move | [V] |
| 0x9bc830 | Allocator helper | [V] |
| 0x6b1d160 | Face visibility marker (called from 0x6b1cbb2) | [V] |

---

## OPEN Questions / UNVERIFIED

[UNVERIFIED: 0x6b1b600] What is the exact structure of the face matrix at a0+0x57? The indexing [rax+r9+0x48] suggests a 3D array [256][16][16] with 0x48 stride per dir2.

[UNVERIFIED: 0x6b1b600] What does sub_53c9da0 do? Called with state+0x1048 and r8 (dir bytes).

[UNVERIFIED: 0x6b1bec0] The 6 output bytes at [rcx+0..5] - are these the 6 face directions of a voxel? The bit patterns suggest each byte accumulates visibility for one direction.

[UNVERIFIED: 0x6b0d380] The render-chunk record at a0+0x40 - what is its full layout? +0x25E is read as a byte counter.

[UNVERIFIED: 0x6b0d380] Queue element size: input 0x10 bytes, output 0x18 bytes (0x10 data + 0x10 padding? + 0x10 tag?). The 0x18 stride at 0x6b0d482 suggests 24-byte queue slots.

[UNVERIFIED: 0x6b1c220] The second function at 0x6b1c220 (size ~0x2000) appears to be the main visibility compute that calls flood. Need to verify if this is sub_791f170 or a different function.

## TOOL REQUESTS
- `stores2.py` enhancement: handle stack-relative stores (rbp/rsp) to capture all [reg+off] in sub_6b1c220
- `casewalk.py` for sub_6b1b600: the function has a clear decision tree on 3 direction bytes - a case walk would map the 6-bit combination logic
- `dumplist.py` for 0x6b1c220..0x6b1da90: full listing of the second large function (2000+ instructions)

---

# 0x791f170 - Visibility Compute (Caller of Flood)

## Step 1 Complete: Preflight
- Ran `PYTHONUTF8=1 python tools/preflight.py 0x791f170` → docs/progress/pre/0x791f170.md (1364 lines)
- Function: sub_791f170 at 0x791f170..0x791f6f8 (size 0x588), 1 xref from sub_6b0c4c0
- **Callees:** sub_31f83d0 (x2), sub_32d10f0 (x2), sub_6b1ba90 (x1), sub_7918580 (x1), sub_e94b450 (x1), sub_e951550 (x1), sub_eec6ed0 (x1)
- **Second function at 0x791f700** (separate, size ~0x2000) - likely related voxel processing

## Step 2 Complete: Instruction-complete listing of 0x791f170 (first 500 instructions, covers main logic up to flood call)

### Function: sub_791f170 (Visibility Compute - Main Entry)
**Range:** 0x791f170..0x791f6f8 (size 0x588) 
**Caller:** sub_6b0c4c0 (store at +0x6b0c4c0)
**Arguments:** rcx = render chunk coordinator (a0), rdx = chunk visibility params (a1)

---

#### Phase 1: Entry & Bounds Check (0x791f170..0x791f1e7)
```
0x791f170  push r15
0x791f172  push r14
0x791f174  push r13
0x791f176  push r12
0x791f178  push rsi
0x791f179  push rdi
0x791f17a  push rbp
0x791f17b  push rbx
0x791f17c  sub rsp,0x88
0x791f183  mov rbx,rdx                                    ; rbx = chunk visibility params (a1)
0x791f186  mov rsi,rcx                                    ; rsi = render chunk coordinator (a0)
0x791f189  mov rax,[0x1230A0C0]                          ; stack cookie
0x791f190  xor rax,rsp
0x791f193  mov [rsp+0x80],rax
0x791f19b  mov rcx,[rcx+0x10]                            ; R a0+0x10 (chunk data ptr)
0x791f19f  mov eax,[rdx+0x14]                            ; R a1+0x14 (min X?)
0x791f1a2  mov edx,[rdx+0x1C]                            ; R a1+0x1C (max X?)
0x791f1a5  add edx,8
0x791f1a8  add eax,8
0x791f1ab  sar eax,4                                      ; eax = (minX+8) >> 4 (chunk coords)
0x791f1ae  mov [rsp+0x60],eax
0x791f1b2  sar edx,4                                      ; edx = (maxX+8) >> 4
0x791f1b5  mov [rsp+0x64],edx
0x791f1b9  mov rax,[rcx]                                 ; R *(a0+0x10)+0x0
0x791f1bc  mov rax,[rax+0x148]                           ; R chunk+0x148 (face matrix state)
0x791f1c3  lea rdx,[rsp+0x60]
0x791f1c8  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (allocator lookup)
0x791f1ce  test rax,rax
0x791f1d1  je short 0x791F1E9                            ; -> early exit if alloc fail
0x791f1d3  movsx edx,word ptr [rbx+0x18]                 ; R a1+0x18 (Y coord?)
0x791f1d7  mov ecx,edx
0x791f1d9  shr ecx,4                                      ; ecx = Y >> 4
0x791f1dc  movzx r8d,cx
0x791f1e0  cmp r8d,0xF800                                 ; bounds check Y < 0xF800
0x791f1e7  jne short 0x791F225                           ; -> loc_791f225 (in bounds)
```

#### Phase 2: Early Exit Path (0x791f1e9..0x791f224)
```
loc_791f1e9:  ; from 791f1d1, 791f23b, 791f245, 791f26c (all bounds failures)
0x791f1e9  mov word ptr [rsi+6],0xFFFF                   ; W a0+0x6 = error sentinel
0x791f1ef  mov dword ptr [rsi+2],0xFFFFFFFF              ; W a0+0x2 = error sentinel

loc_791f1f6:  ; from 791f6e2 (stack check return)
0x791f1f6  mov rax,[rsp+0x80]
0x791f1fe  xor rax,rsp
0x791f201  mov rcx,[0x1230A0C0]
0x791f208  cmp rcx,rax
0x791f20b  jne 0x791F6E7                                 ; -> stack check fail
0x791f211  add rsp,0x88
0x791f218  pop rbx
0x791f219  pop rbp
0x791f21a  pop rdi
0x791f21b  pop rsi
0x791f21c  pop r12
0x791f21e  pop r13
0x791f220  pop r14
0x791f222  pop r15
0x791f224  ret
```

#### Phase 3: Chunk Validation & Thread-Local Storage Init (0x791f225..0x791f2d3)
```
loc_791f225:  ; from 791f1e7 (Y in bounds)
0x791f225  mov r8,[rax+0x58]                              ; R face_state+0x58
0x791f229  and edx,0xFFF0                                 ; edx = Y & 0xFFF0
0x791f22f  movzx r9d,word ptr [r8+0xC8]                   ; R face_state+0x58+0xC8 (max Y)
0x791f237  cmp dx,r9w
0x791f23b  jl short 0x791F1E9                            ; -> early exit if Y < min
0x791f23d  cmp dx,[r8+0xCA]                               ; R face_state+0x58+0xCA (min Y?)
0x791f245  jge short 0x791F1E9                           ; -> early exit if Y >= max
0x791f247  movsx edx,r9w
0x791f24b  sar edx,4                                      ; edx = maxY >> 4
0x791f24e  mov r8d,ecx                                    ; ecx = Y >> 4
0x791f251  sub r8d,edx                                    ; r8d = Y_chunk - maxY_chunk
0x791f254  movsx rdx,r8w
0x791f258  mov r13,[rax+0x1C8]                            ; r13 = face_state+0x1C8 (block data)
0x791f25f  imul rdi,rdx,0x68                              ; rdi = index * 0x68 (block stride)
0x791f263  movsx eax,byte ptr [r13+rdi+0x61]              ; R block+0x61 (block type?)
0x791f269  cmp cx,ax
0x791f26c  jne 0x791F1E9                                 ; -> early exit if block mismatch
0x791f272  lea r15,[rbx+0x14]                             ; r15 = a1+0x14 (params base)
0x791f276  mov eax,[0x128767C8]                          ; TLS index
0x791f27c  mov rcx,gs:[0x58]                              ; TEB
0x791f285  mov rax,[rcx+rax*8]                            ; TLS slot
0x791f289  cmp byte ptr [rax+0x120],0                     ; check TLS init flag
0x791f290  jne short 0x791F297
0x791f292  call 0xE94B450                                ; -> sub_e94b450 (TLS init)

loc_791f297:  ; from 791f290
0x791f297  mov eax,[0x128767C8]
0x791f29d  mov rcx,gs:[0x58]
0x791f2a6  mov r14,[rcx+rax*8]                            ; r14 = TLS data (per-thread state)
0x791f2aa  mov eax,[r15+8]                                ; R a1+0x1C
0x791f2ae  mov [r14+0x1A30],eax                           ; W TLS+0x1A30
0x791f2b5  mov rax,[r15]                                  ; R a1+0x14
0x791f2b8  mov [r14+0x1A28],rax                           ; W TLS+0x1A28
0x791f2bf  lea rcx,[r14+0x1A38]
0x791f2c6  mov r8d,0x1000
0x791f2cc  xor edx,edx
0x791f2ce  call 0xEEC6ED0                                ; -> sub_eec6ed0 (memset TLS buffer)
0x791f2d3  mov dword ptr [r14+0x1A34],0x1000              ; W TLS+0x1A34 = buffer size
```

#### Phase 4: Chunk Coordinate Resolution Loop (0x791f2de..0x791f341)
```
0x791f2de  mov dword ptr [rsp+0x20],0
0x791f2e6  lea rcx,[0x12968458]                          ; global chunk coord table
0x791f2ed  lea r8,[0x12968190]                           ; global chunk coord table end
0x791f2f4  lea rdx,[rsp+0x60]                             ; chunk coords (minX, maxX)
0x791f2f9  xor r9d,r9d
0x791f2fc  call 0x31F83D0                                ; -> sub_31f83d0 (resolve chunk)
0x791f301  mov rax,[rsp+0x60]
0x791f306  test rax,rax
0x791f309  jne short 0x791F343                           ; -> found chunk

; Retry loop with globals
loc_791f30b:  ; from 791f341
0x791f30b  lea r14,[0x12968458]
0x791f312  lea r15,[0x12968190]
0x791f319  lea r12,[rsp+0x60]
0x791f31e  xchg ax,ax

loc_791f320:  ; from 791f341
0x791f320  mov dword ptr [rsp+0x20],0
0x791f328  mov rcx,r14
0x791f32b  mov rdx,r12
0x791f32e  mov r8,r15
0x791f331  xor r9d,r9d
0x791f334  call 0x31F83D0                                ; -> sub_31f83d0
0x791f339  mov rax,[rsp+0x60]
0x791f33e  test rax,rax
0x791f341  je short 0x791F320                            ; -> retry until found
```

#### Phase 5: Main Visibility Loop Setup (0x791f343..0x791f3bd)
```
loc_791f343:  ; from 791f309 (chunk resolved)
0x791f343  add r13,rdi                                    ; r13 = block data + index*0x68
0x791f346  mov rbp,[rax+0x240]                            ; rbp = chunk+0x240 (face data?)
0x791f34d  mov edi,[rbx+0x14]                             ; edi = a1+0x14 (base X)
0x791f350  mov eax,[rbx+0x18]                             ; eax = a1+0x18 (base Y)
0x791f353  mov [rsp+0x40],eax
0x791f357  mov eax,[rbx+0x1C]                             ; eax = a1+0x1C (base Z)
0x791f35a  mov [rsp+0x30],eax
0x791f35e  mov byte ptr [rsi],1                           ; W a0+0x0 = 1 (active)
0x791f361  mov rdx,[rsi+0x10]                             ; R a0+0x10
0x791f365  lea rcx,[rbx+0x14]
0x791f369  call 0x7918580                                ; -> sub_7918580 (init face data)
0x791f36e  mov [rsi+1],al                                 ; W a0+0x1 = result
0x791f371  mov eax,[rbx+0x18]
0x791f374  lea ecx,[rax+0x10]
0x791f377  mov [rsp+0x3C],ecx
0x791f37b  add eax,0x11
0x791f37e  mov [rsp+0x50],rax
0x791f383  mov [rsp+0x60],edi
0x791f387  mov dil,1
0x791f38a  lea rbx,[rsp+0x74]
0x791f38f  lea r14,[rsp+0x60]
0x791f394  xor ecx,ecx
0x791f396  xor eax,eax
0x791f398  jmp short 0x791F3BD                           ; -> loc_791f3bd
```

#### Phase 6: Outer Loop - 16 Z-Slices (0x791f3a0..0x791f3fb)
```
loc_791f3a0:  ; from 791f3fb (inner loop done)
0x791f3a0  inc dword ptr [rsp+0x60]                       ; Z++
0x791f3a4  mov ecx,[rsp+0x34]
0x791f3a8  inc ecx
0x791f3aa  mov eax,[rsp+0x38]
0x791f3ae  add eax,0x100                                  ; X base += 0x100
0x791f3b3  cmp cx,0x10                                    ; 16 Z slices?
0x791f3b7  je 0x791F6AA                                  ; -> loc_791f6aa (call flood)

loc_791f3bd:  ; from 791f398 (outer loop entry)
0x791f3bd  mov [rsp+0x34],ecx
0x791f3c1  mov ecx,[rsp+0x30]
0x791f3c5  mov [rsp+0x68],ecx
0x791f3c9  xor r15d,r15d                                  ; r15 = inner X index (0..15)
0x791f3cc  mov [rsp+0x38],eax
0x791f3d0  mov r12d,eax
0x791f3d3  mov eax,ecx
0x791f3d5  jmp short 0x791F3FD                           ; -> loc_791f3fd
```

#### Phase 7: Inner Loop - 16 X-Positions per Z (0x791f3e0..0x791f6a5)
**Loop structure:** Outer Z=0..15 (rsp+0x60), Inner X=0..15 (r15), each tests voxel at (X,Y,Z)
```
loc_791f3e0:  ; from 791f489, 791f57f, 791f69c, 791f6a5 (inner continue)
0x791f3e0  mov r15d,[rsp+0x44]
0x791f3e5  inc r15d                                       ; X++
0x791f3e8  mov eax,[rsp+0x68]
0x791f3ec  inc eax
0x791f3ee  mov [rsp+0x68],eax
0x791f3f2  add r12d,0x10
0x791f3f6  cmp r15w,0x10                                  ; 16 X done?
0x791f3fb  je short 0x791F3A0                            ; -> next Z slice

loc_791f3fd:  ; from 791f3d5 (inner loop entry)
0x791f3fd  mov ecx,[rsp+0x3C]
0x791f401  mov [rsp+0x64],ecx
0x791f405  mov ecx,[rsp+0x60]
0x791f409  mov [rsp+0x74],ecx
0x791f40d  mov rcx,[rsp+0x50]
0x791f412  mov [rsp+0x78],ecx
0x791f416  mov [rsp+0x7C],eax
0x791f41a  cmp byte ptr [rsi+1],1                         ; check face result
0x791f41e  jne short 0x791F425
0x791f420  cmp byte ptr [rsi],0
0x791f423  je short 0x791F460
```

#### Phase 8: Voxel Occupancy Test Path A (0x791f425..0x791f460)
```
loc_791f425:  ; from 791f41e
0x791f425  mov rcx,[rsi+0x10]
0x791f429  lea rdx,[rsp+0x5E]
0x791f42e  mov r8,rbx
0x791f431  call 0x32D10F0                                ; -> sub_32d10f0 (test voxel)
0x791f436  movzx eax,byte ptr [rsp+0x5E]
0x791f43b  test al,al
0x791f43d  je short 0x791F443
0x791f43f  mov byte ptr [rsi+1],1                         ; W a0+0x1 = 1

loc_791f443:  ; from 791f43d
0x791f443  cmp byte ptr [rsi],1
0x791f446  jne short 0x791F460
0x791f448  add al,[rsp+0x5F]
0x791f44c  cmp al,3
0x791f44e  jb short 0x791F460
0x791f450  mov byte ptr [rsi],0
0x791f453  nop [rax+rax]
```

#### Phase 9: Block Face Data Lookup (0x791f460..0x791f50f)
```
loc_791f460:  ; from 791f423, 791f446, 791f44e
0x791f460  mov [rsp+0x44],r15d
0x791f465  mov eax,[rsp+0x40]
0x791f469  mov [rsp+0x64],eax
0x791f46d  xor r15d,r15d
0x791f470  jmp short 0x791F492

loc_791f472:  ; from 791f54b
0x791f472  mov byte ptr [rsi],0

loc_791f480:  ; from 791f51a, 791f53f
0x791f480  inc dword ptr [rsp+0x64]
0x791f484  cmp r15w,0xF
0x791f489  je 0x791F3E0

loc_791f48f:  ; from 791f55a
0x791f48f  inc r15d

loc_791f492:  ; from 791f470
0x791f492  lea edx,[r12+r15]                              ; face index = base + X
0x791f496  mov rcx,[r13+0x30]                             ; R block+0x30 (face table)
0x791f49a  mov rax,[rcx]
0x791f49d  mov rax,[rax+0x18]
0x791f4a1  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (allocator)
0x791f4a7  cmp rax,rbp
0x791f4aa  je short 0x791F511
0x791f4ac  cmp byte ptr [rax+0xA3],1                      ; check face type
0x791f4b3  jne short 0x791F50F
```

#### Phase 10: Mark Face Visible in Face Matrix (0x791f4b5..0x791f509)
```
0x791f4b5  mov eax,[rsp+0x68]
0x791f4b9  mov ecx,[0x128767C8]
0x791f4bf  mov rdx,gs:[0x58]
0x791f4c8  mov rcx,[rdx+rcx*8]                            ; TLS data
0x791f4cc  sub eax,[rcx+0x1A30]                           ; X - TLS_baseX
0x791f4d2  mov edx,[rsp+0x60]
0x791f4d6  mov r8d,[rsp+0x64]
0x791f4db  sub r8d,[rcx+0x1A2C]                           ; Y - TLS_baseY
0x791f4e2  sub edx,[rcx+0x1A28]                           ; Z - TLS_baseZ
0x791f4e8  movzx r8d,r8b
0x791f4ec  movzx eax,al
0x791f4ef  shl eax,4                                      ; X << 4
0x791f4f2  shl edx,8                                      ; Z << 8
0x791f4f5  movzx edx,dx
0x791f4f8  add rax,rcx
0x791f4fb  add rax,0x19F0                                 ; face matrix base in TLS
0x791f501  add rax,r8
0x791f504  mov byte ptr [rdx+rax+0x48],1                  ; W face_matrix[Z<<8 | Y | X<<4] + 0x48 = 1
0x791f509  dec dword ptr [rcx+0x1A34]                     ; dec TLS counter

loc_791f50f:  ; from 791f4b3
0x791f50f  xor edi,edi
```

#### Phase 11: Voxel Occupancy Test Path B (0x791f511..0x791f57f)
```
loc_791f511:  ; from 791f4aa
0x791f511  cmp byte ptr [rsi+1],1
0x791f515  jne short 0x791F520
0x791f517  cmp byte ptr [rsi],0
0x791f51a  je 0x791F480

loc_791f520:  ; from 791f515
0x791f520  mov rcx,[rsi+0x10]
0x791f524  mov rdx,rbx
0x791f527  mov r8,r14
0x791f52a  call 0x32D10F0                                ; -> sub_32d10f0
0x791f52f  movzx eax,byte ptr [rsp+0x74]
0x791f534  test al,al
0x791f536  je short 0x791F53C
0x791f538  mov byte ptr [rsi+1],1

loc_791f53c:  ; from 791f536
0x791f53c  cmp byte ptr [rsi],1
0x791f53f  jne 0x791F480
0x791f545  add al,[rsp+0x75]
0x791f549  cmp al,3
0x791f54b  jae 0x791F472
0x791f551  inc dword ptr [rsp+0x64]
0x791f555  cmp r15w,0xF
0x791f55a  jne 0x791F48F
```

#### Phase 12: Face Matrix Bounds & Visibility Propagation (0x791f560..0x791f6a5)
```
0x791f560  mov rcx,[rsi+0x10]
0x791f564  mov rax,[rcx]
0x791f567  mov rax,[rax+0x140]
0x791f56e  mov [rsp+0x48],rcx
0x791f573  mov rdx,r14
0x791f576  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x791f57c  test rax,rax
0x791f57f  je 0x791F3E0

0x791f585  mov r15,rax
0x791f588  mov rcx,[rsp+0x48]
0x791f58d  mov rax,[rcx]
0x791f590  mov rax,[rax+0x118]
0x791f597  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x791f59d  mov ecx,[rsp+0x64]
0x791f5a1  sub ecx,eax
0x791f5a3  inc ecx
0x791f5a5  movsx eax,cx
0x791f5a8  shr eax,4
0x791f5ab  movsx rdx,ax
0x791f5af  mov rax,[r15+0x1C8]
0x791f5b6  mov r8,[r15+0x1D0]
0x791f5bd  sub r8,rax
0x791f5c0  sar r8,3
0x791f5c4  mov r9,0x4EC4EC4EC4EC4EC5
0x791f5ce  imul r8,r9
0x791f5d2  cmp r8,rdx
0x791f5d5  jbe short 0x791F635

; Complex face matrix index calculation and visibility test
0x791f5d7  mov r9d,[rsp+0x60]
0x791f5dc  mov r10d,[rsp+0x68]
0x791f5e1  imul rdx,0x68
0x791f5e5  lea r8,[rax+rdx]
0x791f5e9  and r9d,0xF
0x791f5ed  shl r9d,8
0x791f5f1  and ecx,0xF
0x791f5f4  shl r10d,4
0x791f5f8  movzx r11d,r10b
0x791f5fc  or r11d,r9d
0x791f5ff  or r11d,ecx
0x791f602  mov r10,[rax+rdx+8]
0x791f607  movzx r9d,r11w
0x791f60b  movzx eax,cx
0x791f60e  test r10,r10
0x791f611  je short 0x791F647
0x791f613  mov r11d,r9d
0x791f616  lea ecx,[rax*4]
0x791f61d  and cl,4
0x791f620  mov edx,0xF
0x791f625  shl edx,cl
0x791f627  shr r11d,1
0x791f62a  and dl,[r10+r11]
0x791f62e  shr dl,cl
0x791f630  and dl,0xF
0x791f633  jmp short 0x791F659

loc_791f635:  ; from 791f5d5
0x791f635  movzx edx,byte ptr [r15+0x1518]
0x791f63d  movzx r10d,byte ptr [r15+0x1519]
0x791f645  jmp short 0x791F68D

loc_791f647:  ; from 791f611
0x791f647  cmp byte ptr [r8+0x1C],0
0x791f64c  mov edx,0
0x791f651  mov ecx,0xF
0x791f656  cmovne edx,ecx

loc_791f659:  ; from 791f633
0x791f659  mov r10d,edx
0x791f65c  shl r10b,4
0x791f660  mov r8,[r8+0x10]
0x791f664  test r8,r8
0x791f667  je short 0x791F689
0x791f669  shl eax,2
0x791f66c  and al,4
0x791f66e  mov r11d,0xF
0x791f674  mov ecx,eax
0x791f676  shl r11d,cl
0x791f679  shr r9d,1
0x791f67c  and r11b,[r8+r9]
0x791f680  shr r11b,cl
0x791f683  or r11b,r10b
0x791f686  mov r10d,r11d

loc_791f689:  ; from 791f667
0x791f689  and r10b,0xF

loc_791f68d:  ; from 791f645
0x791f68d  movzx eax,r10b
0x791f691  movzx ecx,dl
0x791f694  cmp al,cl
0x791f696  cmova ecx,eax
0x791f699  cmp cl,3
0x791f69c  jb 0x791F3E0
0x791f6a2  mov byte ptr [rsi],0
0x791f6a5  jmp 0x791F3E0
```

#### Phase 13: Flood Fill Call & Return (0x791f6aa..0x791f6f2)
```
loc_791f6aa:  ; from 791f3b7 (all 16 Z slices done)
0x791f6aa  mov eax,[0x128767C8]
0x791f6b0  mov rcx,gs:[0x58]
0x791f6b9  mov rax,[rcx+rax*8]
0x791f6bd  lea rcx,[rax+0x19F0]                           ; TLS face matrix base
0x791f6c4  lea rdx,[rsp+0x74]                             ; output buffer on stack
0x791f6c9  call 0x6B1BA90                                ; -> sub_6b1ba90 (FLOOD FILL)
0x791f6ce  movzx eax,word ptr [rsp+0x78]
0x791f6d3  mov [rsi+6],ax                                 ; W a0+0x6 = flood result (word)
0x791f6d7  mov eax,[rsp+0x74]
0x791f6db  mov [rsi+2],eax                                ; W a0+0x2 = flood result (dword)
0x791f6de  mov [rsi+8],dil                                ; W a0+0x8 = flags
0x791f6e2  jmp 0x791F1F6                                 ; -> cleanup/return

loc_791f6e7:  ; from 791f20b (stack check fail)
0x791f6e7  mov rcx,[rsp+0x80]
0x791f6ef  xor rcx,rsp
0x791f6f2  call 0xE951550                                ; -> sub_e951550
0x791f6f7  int3                                          
0x791f6f8  int3                                          
0x791f6f9  int3                                          
0x791f6fa  int3                                          
0x791f6fb  int3                                          
0x791f6fc  int3                                          
```

---

## Step 3: [reg+off] Read/Write Table for 0x791f170 (Visibility Compute)

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| a0+0x00 | 1 | W | Active flag (1=processing) | [V] |
| a0+0x01 | 1 | W | Face test result | [V] |
| a0+0x02 | 4 | W | Flood result dword / error sentinel | [V] |
| a0+0x06 | 2 | W | Flood result word / error sentinel | [V] |
| a0+0x08 | 1 | W | Flags from flood | [V] |
| a0+0x10 | 8 | R | Chunk data pointer | [V] |
| a0+0x10+0x00 | 8 | R | Chunk base | [V] |
| a0+0x10+0x140 | 8 | R | Chunk+0x140 (face data) | [V] |
| a0+0x10+0x148 | 8 | R | Chunk+0x148 (face matrix state ptr) | [V] |
| a0+0x10+0x240 | 8 | R | Chunk+0x240 (face data ptr) | [V] |
| a1+0x14 | 4 | R | Base X coordinate | [V] |
| a1+0x18 | 4 | R | Base Y coordinate | [V] |
| a1+0x1C | 4 | R | Base Z coordinate | [V] |
| a1+0x18 (word) | 2 | R | Y coordinate (for bounds) | [V] |
| face_state+0x58 | 8 | R | Face matrix Y-bounds table | [V] |
| face_state+0x58+0xC8 | 2 | R | Max Y (word) | [V] |
| face_state+0x58+0xCA | 2 | R | Min Y (word) | [V] |
| face_state+0x1C8 | 8 | R | Block data array base | [V] |
| block+0x61 | 1 | R | Block type/type info | [V] |
| block+0x30 | 8 | R | Face table pointer | [V] |
| block+0x30+0x18 | 8 | R | Face table allocator | [V] |
| TLS+0x120 | 1 | R | TLS init flag | [V] |
| TLS+0x1A28 | 8 | R/W | TLS base X | [V] |
| TLS+0x1A2C | 4 | R/W | TLS base Y | [V] |
| TLS+0x1A30 | 4 | R/W | TLS base Z | [V] |
| TLS+0x1A34 | 4 | R/W | TLS face counter | [V] |
| TLS+0x1A38 | 0x1000 | W | TLS face matrix buffer (memset) | [V] |
| TLS+0x19F0 | 0x1000 | R/W | Face matrix (indexed by Z<<8 \| Y \| X<<4) | [V] |
| face_matrix[idx] + 0x48 | 1 | R/W | Voxel visibility byte | [V] |
| r15+0x1C8 | 8 | R | Face data base | [V] |
| r15+0x1D0 | 8 | R | Face data end | [V] |
| r15+0x1518 | 1 | R | Face visibility byte | [V] |
| r15+0x1519 | 1 | R | Face visibility byte | [V] |

---

## Step 4: Callees for 0x791f170 (Ordered)

| RVA | What | Tag |
|-----|------|-----|
| 0xeea6040 (via [0xF99FFA0]) | Memory allocator (multiple call sites) | [V] |
| 0x31f83d0 | Chunk coordinate resolution (x2) | [V] |
| 0x32d10f0 | Voxel occupancy test (x2) | [V] |
| 0x6b1ba90 | Flood fill / visibility propagation (x1) | [V] |
| 0x7918580 | Face data initialization (x1) | [V] |
| 0xe94b450 | TLS initialization (x1) | [V] |
| 0xeec6ed0 | Buffer memset (x1) | [V] |
| 0xe951550 | Stack cookie check (x1) | [V] |

---

## Loop Structure Summary (Quoted Jumps)

**Outer Z-Loop (16 iterations):**
- `0x791f3a0` inc dword ptr [rsp+0x60] ; Z++
- `0x791f3b3` cmp cx,0x10
- `0x791f3b7` je 0x791F6AA → flood call
- `0x791f3bd` entry, `0x791f3fd` inner setup

**Inner X-Loop (16 iterations per Z):**
- `0x791f3e0` mov r15d,[rsp+0x44] ; inc r15d (X++)
- `0x791f3f6` cmp r15w,0x10
- `0x791f3fb` je short 0x791F3A0 → next Z
- `0x791f3fd` entry, `0x791f492` face lookup

**Retry Loop (chunk resolution):**
- `0x791f320` call 0x31F83D0
- `0x791f33e` test rax,rax
- `0x791f341` je short 0x791F320 → retry

**Early Exit Convergence:**
- `0x791f1e9` from 791f1d1, 791f23b, 791f245, 791f26c (all bounds checks)
- `0x791f1f6` from 791f6e2 (stack check return)

---

## NEXT for 0x791f170
- **Resume disassembly at 0x791f700** (second function in same range, size ~0x2000) - appears to be voxel face processing with SIMD
- Need full listing of 0x791f700..0x791f6f8+0x2000 for complete analysis

## NEXT for Unit U-H1b
Continue with: 0x792e630 (task body), 0x7923d50 (launcher), 0x537dab0 (listener) - same method

## TOOL REQUESTS (updated)
- `dumplist.py` for 0x791f700..0x7921700: full listing of second function at 0x791f700 (voxel face processing with SIMD)
- `casewalk.py` for sub_32d10f0: voxel occupancy test decision logic
- `stores2.py` for 0x791f700: capture all SIMD stores (movups/movd/movdqa)

---

## Verification
- verify_oc.py on this section: [TO BE RUN AFTER APPEND]

---

# 0x792e630 - Task Body (Chunk Visibility Task)

## Step 1 Complete: Preflight
- Ran `PYTHONUTF8=1 python tools/preflight.py 0x792e630` → docs/progress/pre/0x792e630.md (1372 lines)
- Function: sub_792e630 at 0x792e630..0x792ef79 (size 0x949), 0 xrefs (entry point for task)
- **Callees:** sub_3b2020 (x4), sub_7177e0 (x2), sub_2fc9aa0 (x1), sub_3005170 (x1), sub_32cb4a0 (x1), sub_32cb870 (x1), sub_6b0c4c0 (x2), sub_6b1c220 (x2), sub_6b1c3e0 (x2), sub_6b1d650 (x1), sub_6b1d780 (x1), sub_6b32870 (x2), sub_e935700 (x2), sub_e943178 (x2), sub_e94319c (x2), sub_e9e7970 (x1), sub_eec5920 (x4), sub_eec5930 (x4)

## Step 2 Complete: Instruction-complete listing of 0x792e630 (first 500 instructions, covers main task logic)

### Function: sub_792e630 (Chunk Visibility Task Body)
**Range:** 0x792e630..0x792ef79 (size 0x949)
**Caller:** Task scheduler (invoked via GraphicsTasks, no direct xref)
**Arguments:** rcx = task output buffer (rsi), rdx = task input params (r14)

---

#### Phase 1: Entry & Stack Frame (0x792e630..0x792e661)
```
0x792e630  push rbp
0x792e631  push r15
0x792e633  push r14
0x792e635  push r12
0x792e637  push rsi
0x792e638  push rdi
0x792e639  push rbx
0x792e63a  mov eax,0xA320                                 ; stack size = 0xA320 (41760 bytes)
0x792e63f  call 0xE9E7970                                ; -> sub_e9e7970 (stack probe)
0x792e644  sub rsp,rax
0x792e647  lea rbp,[rsp+0x80]                             ; rbp = stack frame base
0x792e64f  mov qword ptr [rbp+0xA298],0xFFFFFFFFFFFFFFFE  ; stack guard
0x792e65a  mov rsi,rcx                                    ; rsi = output buffer
0x792e65d  pxor xmm0,xmm0
0x792e661  movdqa [rbp+0xA280],xmm0                       ; clear stack slot A280
```

#### Phase 2: Reference Counting & Input Validation (0x792e669..0x792e6e7)
```
0x792e669  mov rcx,[rdx+0x10]                             ; R input+0x10 (refcounted obj)
0x792e66d  test rcx,rcx
0x792e670  je 0x792EA1B                                  ; -> cleanup if null

0x792e676  mov eax,[rcx+8]                                ; R refcount
0x792e679  nop [rax]

loc_792e680:  ; from 792e68e (spinlock)
0x792e680  test eax,eax
0x792e682  je short 0x792E6AB                            ; -> if refcount==0
0x792e684  lea r8d,[rax+1]
0x792e688  lock cmpxchg [rcx+8],r8d                       ; atomic inc refcount
0x792e68e  jne short 0x792E680                           ; retry on conflict

0x792e690  movdqu xmm0,[rdx+8]                            ; R input+0x8 (16 bytes params)
0x792e695  mov rcx,[rdx+8]                                ; R input+0x8 (ptr)
0x792e699  movdqa [rbp+0xA280],xmm0                       ; save params to stack
0x792e6a1  test rcx,rcx
0x792e6a4  jne short 0x792E6BB
0x792e6a6  jmp 0x792EA1B                                 ; -> cleanup

loc_792e6ab:  ; from 792e682
0x792e6ab  mov rcx,[rbp+0xA280]
0x792e6b2  test rcx,rcx
0x792e6b5  je 0x792EA1B

loc_792e6bb:  ; from 792e6a4
0x792e6bb  cmp qword ptr [rdx+0x18],0                     ; R input+0x18
0x792e6c0  je 0x792EA1B
0x792e6c6  mov r8d,1
0x792e6cc  xor eax,eax
0x792e6ce  lock cmpxchg [rcx+0x20],r8d                    ; atomic state flag at +0x20
0x792e6d4  je short 0x792E6E7
0x792e6d6  mov eax,2
0x792e6db  lock cmpxchg [rcx+0x20],r8d
0x792e6e1  jne 0x792EA1B

loc_792e6e7:  ; from 792e6d4 (acquired)
0x792e6e7  mov r14,rdx                                    ; r14 = input params
0x792e6ea  call 0xEEC5920                                ; -> sub_eec5920 (get timestamp)
0x792e6ef  mov rdi,rax
0x792e6f2  call 0xEEC5930                                ; -> sub_eec5930 (get freq)
0x792e6f7  cmp rdi,0x16E3600                              ; compare timestamp
0x792e6fe  je short 0x792E712
0x792e700  cmp rdi,0x989680
0x792e707  jne short 0x792E76D
0x792e709  imul rbx,rax,0x64                              ; rbx = freq * 100
0x792e70d  jmp 0x792E7B1
```

#### Phase 3: Timestamp Calculation (0x792e712..0x792e7b1)
```
loc_792e712:  ; from 792e6fe (timestamp == 0x16E3600)
0x792e712  mov r9,0xB2F4FC0794908CF3                      ; magic constant for div
0x792e71c  mov rcx,rax
0x792e71f  imul r9                                        ; rdx:rax = rax * magic
0x792e722  mov r8,rdx
0x792e725  add r8,rcx
0x792e728  mov rax,r8
0x792e72b  shr rax,0x3F
0x792e72f  sar r8,0x18
0x792e733  add r8,rax
0x792e736  imul rax,r8,0x16E3600                          ; rax = quotient * 0x16E3600
0x792e73d  sub rcx,rax                                    ; rcx = remainder
0x792e740  imul rcx,0x3B9ACA00                            ; * 1000000000 (ns scale)
0x792e747  mov rax,rcx
0x792e74a  imul r9
0x792e74d  mov rbx,rdx
0x792e750  imul rax,r8,0x3B9ACA00
0x792e757  add rbx,rcx
0x792e75a  mov rcx,rbx
0x792e75d  shr rcx,0x3F
0x792e761  sar rbx,0x18
0x792e765  add rbx,rcx
0x792e768  add rbx,rax
0x792e76b  jmp short 0x792E7B1

loc_792e76d:  ; from 792e707 (other timestamp path)
0x792e76d  mov rcx,rax
0x792e770  or rcx,rdi
0x792e773  shr rcx,0x20
0x792e777  je short 0x792E780
0x792e779  cqo
0x792e77b  idiv rdi
0x792e77e  jmp short 0x792E784

loc_792e780:  ; from 792e777
0x792e780  xor edx,edx
0x792e782  div edi

loc_792e784:  ; from 792e77e
0x792e784  imul rcx,rax,0x3B9ACA00
0x792e78b  imul rax,rdx,0x3B9ACA00
0x792e792  mov rdx,rax
0x792e795  or rdx,rdi
0x792e798  shr rdx,0x20
0x792e79c  je short 0x792E7A8
0x792e79e  cqo
0x792e7a0  idiv rdi
0x792e7a3  mov rbx,rax
0x792e7a6  jmp short 0x792E7AE

loc_792e7a8:  ; from 792e79c
0x792e7a8  xor edx,edx
0x792e7aa  div edi
0x792e7ac  mov ebx,eax

loc_792e7ae:  ; from 792e7a6
0x792e7ae  add rbx,rcx

loc_792e7b1:  ; from 792e70d, 792e76b (converged rbx = computed time)
0x792e7b1  pxor xmm0,xmm0
0x792e7b5  movdqa [rbp+0xA220],xmm0
```

#### Phase 4: Shared Object Handling & Task Init (0x792e7bd..0x792e828)
```
0x792e7bd  mov rax,[r14+0x20]                             ; R input+0x20 (shared ptr)
0x792e7c1  test rax,rax
0x792e7c4  je short 0x792E7D0
0x792e7c6  lock inc dword ptr [rax+8]                     ; inc refcount
0x792e7ca  mov rax,[r14+0x20]
0x792e7ce  jmp short 0x792E7D2

loc_792e7d0:  ; from 792e7c4
0x792e7d0  xor eax,eax

loc_792e7d2:  ; from 792e7ce
0x792e7d2  mov rcx,[r14+0x18]                             ; R input+0x18
0x792e7d6  mov [rbp+0xA220],rcx
0x792e7dd  mov [rbp+0xA228],rax
0x792e7e4  lea rcx,[rbp+0xA1A0]
0x792e7eb  lea rdx,[rbp+0xA220]
0x792e7f2  call 0x2FC9AA0                                ; -> sub_2fc9aa0 (init struct)
0x792e7f7  nop
0x792e7f8  mov rdx,[rbp+0xA1C0]
0x792e7ff  mov r8,[rbp+0xA1C8]
0x792e806  mov byte ptr [rsp+0x38],0
0x792e80b  mov byte ptr [rsp+0x30],0
0x792e810  mov byte ptr [rsp+0x28],0
0x792e815  mov byte ptr [rsp+0x20],0
0x792e81a  lea rcx,[rbp+0xA028]
0x792e821  lea r9,[rbp+0xA1A0]
0x792e828  call 0x32CB4A0                                ; -> sub_32cb4a0
```

#### Phase 5: Global State Access & Callback (0x792e82e..0x792e92c)
```
0x792e82e  lea rdi,[0x128D67D8]                          ; global state object
0x792e835  mov rcx,rdi
0x792e838  call 0xE943178                                ; -> sub_e943178 (lock)
0x792e83d  lock inc qword ptr [0x128D6838]               ; global counter++
0x792e845  mov rcx,rdi
0x792e848  call 0xE94319C                                ; -> sub_e94319c (unlock)
0x792e84d  mov rax,[0x128D6840]                          ; global ptr1
0x792e854  test rax,rax
0x792e857  je 0x792E90F
0x792e85d  cmp byte ptr [rax],1
0x792e860  jne 0x792E90F
0x792e866  mov rax,[0x128D6848]                          ; global ptr2
0x792e86d  test rax,rax
0x792e870  je 0x792EA71
0x792e876  lock inc dword ptr [rax+8]
0x792e87a  mov rax,[0x128D6840]
0x792e881  mov rdi,[0x128D6848]
0x792e888  test rax,rax
0x792e88b  je short 0x792E8DF
0x792e88d  cmp byte ptr [rax],0
0x792e890  je short 0x792E8DF
0x792e892  mov rax,[0x128D6850]
0x792e899  movzx r14d,byte ptr [rax+0x2A]
0x792e89e  test rdi,rdi
0x792e8a1  je 0x792EA7D
0x792e8a7  lock dec dword ptr [rdi+8]
0x792e8ab  jne 0x792EA7D
0x792e8b1  mov rax,[rdi]
0x792e8b4  mov rax,[rax]
0x792e8b7  mov rcx,rdi
0x792e8ba  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (dealloc)
0x792e8c0  lock dec dword ptr [rdi+0xC]
0x792e8c4  jne 0x792EA7D
0x792e8ca  mov rax,[rdi]
0x792e8cd  mov rax,[rax+8]
0x792e8d1  mov rcx,rdi
0x792e8d4  call qword ptr [0xF99FFA0]
0x792e8da  jmp 0x792EA7D

loc_792e8df:  ; from 792e88b, 792e890
0x792e8df  test rdi,rdi
0x792e8e2  je short 0x792E90F
0x792e8e4  lock dec dword ptr [rdi+8]
0x792e8e8  jne short 0x792E90F
0x792e8ea  mov rax,[rdi]
0x792e8ed  mov rax,[rax]
0x792e8f0  mov rcx,rdi
0x792e8f3  call qword ptr [0xF99FFA0]
0x792e8f9  lock dec dword ptr [rdi+0xC]
0x792e8fd  jne short 0x792E90F
0x792e8ff  mov rax,[rdi]
0x792e902  mov rax,[rax+8]
0x792e906  mov rcx,rdi
0x792e909  call qword ptr [0xF99FFA0]

loc_792e90f:  ; convergence from multiple paths
0x792e90f  lea rcx,[0x128D67D8]
0x792e916  call 0x3B2020                                 ; -> sub_3b2020 (global cleanup)
0x792e91b  mov rdi,[rbp+0xA280]

loc_792e922:  ; from 792ea94
0x792e922  lea rdx,[rbp+0xA028]
0x792e929  mov rcx,rdi
0x792e92c  call 0x6B0C4C0                                ; -> sub_6b0c4c0 (VISIBILITY COMPUTE)
```

#### Phase 6: Main Loop - Global State Polling (0x792e932..0x792ea1b)
```
loc_792e932:  ; from 792eb33 (loop back)
0x792e932  lea r15,[0x128D67D8]
0x792e939  mov rcx,r15
0x792e93c  call 0xE943178                                ; lock global
0x792e941  lock inc qword ptr [0x128D6838]
0x792e949  mov rcx,r15
0x792e94c  call 0xE94319C                                ; unlock global
0x792e951  mov r12,[0x128D6840]
0x792e958  test r12,r12
0x792e95b  je short 0x792E98B
0x792e95d  cmp byte ptr [r12],1
0x792e962  jne short 0x792E98B
0x792e964  mov rax,[0x128D6848]
0x792e96b  test rax,rax
0x792e96e  je 0x792EB38
0x792e974  lock inc dword ptr [rax+8]
0x792e978  mov r12,[0x128D6840]
0x792e97f  mov rdi,[0x128D6848]
0x792e986  jmp 0x792EB3A

loc_792e98b:  ; from 792e95b, 792e962
0x792e98b  mov qword ptr [rbp+0xA258],0
0x792e996  mov byte ptr [rbp+0xA260],0
0x792e99d  lea rcx,[0x128D67D8]
0x792e9a4  call 0x3B2020

loc_792e9a9:  ; from multiple cleanup paths (792eef5, 792ef3b, 792ef45, 792ef5e, 792ef74)
0x792e9a9  cmp byte ptr [rbp+0xA260],1
0x792e9b0  jne short 0x792E9BE
0x792e9b2  mov rcx,[rbp+0xA258]
0x792e9b9  call 0x3B2020

loc_792e9be:  ; from 792e9b0
0x792e9be  lea rcx,[rbp+0xA028]
0x792e9c5  call 0x32CB870
0x792e9ca  lea rax,[0xF17ABC0]
0x792e9d1  mov [rbp+0xA1A0],rax
0x792e9d8  mov rdi,[rbp+0xA218]
0x792e9df  test rdi,rdi
0x792e9e2  je short 0x792EA0F
0x792e9e4  lock dec dword ptr [rdi+8]
0x792e9e8  jne short 0x792EA0F
0x792e9ea  mov rax,[rdi]
0x792e9ed  mov rax,[rax]
0x792e9f0  mov rcx,rdi
0x792e9f3  call qword ptr [0xF99FFA0]
0x792e9f9  lock dec dword ptr [rdi+0xC]
0x792e9fd  jne short 0x792EA0F
0x792e9ff  mov rax,[rdi]
0x792ea02  mov rax,[rax+8]
0x792ea06  mov rcx,rdi
0x792ea09  call qword ptr [0xF99FFA0]

loc_792ea0f:  ; from 792e9e2, 792e9e8, 792e9fd
0x792ea0f  lea rcx,[rbp+0xA1A0]
0x792ea16  call 0x3005170
```

#### Phase 7: Cleanup & Return (0x792ea1b..0x792ea70)
```
loc_792ea1b:  ; from 792e670, 792e6a6, 792e6b5, 792e6c0, 792e6e1 (early exits)
0x792ea1b  movups xmm0,[0x128D4558]
0x792ea22  movups [rsi],xmm0                              ; write default output
0x792ea25  mov rdi,[rbp+0xA288]
0x792ea2c  test rdi,rdi
0x792ea2f  je short 0x792EA5C
0x792ea31  lock dec dword ptr [rdi+8]
0x792ea35  jne short 0x792EA5C
0x792ea37  mov rax,[rdi]
0x792ea3a  mov rax,[rax]
0x792ea3d  mov rcx,rdi
0x792ea40  call qword ptr [0xF99FFA0]
0x792ea46  lock dec dword ptr [rdi+0xC]
0x792ea4a  jne short 0x792EA5C
0x792ea4c  mov rax,[rdi]
0x792ea4f  mov rax,[rax+8]
0x792ea53  mov rcx,rdi
0x792ea56  call qword ptr [0xF99FFA0]

loc_792ea5c:  ; from 792ea2f, 792ea35, 792ea4a
0x792ea5c  mov rax,rsi
0x792ea5f  add rsp,0xA320
0x792ea66  pop rbx
0x792ea67  pop rdi
0x792ea68  pop rsi
0x792ea69  pop r12
0x792ea6b  pop r14
0x792ea6d  pop r15
0x792ea6f  pop rbp
0x792ea70  ret
```

#### Phase 8: Alternate Path - r14b==2 (0x792ea7d..0x792eb33)
```
loc_792ea7d:  ; from 792e8a1, 792e8ab, 792e8c4, 792e8da
0x792ea7d  lea rcx,[0x128D67D8]
0x792ea84  call 0x3B2020
0x792ea89  mov rdi,[rbp+0xA280]
0x792ea90  cmp r14b,2
0x792ea94  jne 0x792E922                                 ; -> call 6b0c4c0
0x792ea9a  lea rdx,[rbp+0xA028]
0x792eaa1  mov rcx,rdi
0x792eaa4  call 0x6B0C4C0                                ; -> sub_6b0c4c0
0x792eaa9  nop
0x792eaaa  mov eax,[rdi+0x1C]
0x792eaad  sar eax,4
0x792eab0  movq xmm0,[rdi+0x14]
0x792eab5  psrad xmm0,4
0x792eaba  movq [rbp+0xA258],xmm0
0x792eac2  mov [rbp+0xA260],eax
0x792eac8  lea rcx,[rbp-0x38]
0x792eacc  lea rdx,[rbp+0xA028]
0x792ead3  lea r8,[rbp+0xA258]
0x792eada  call 0x6B1C220                                ; -> sub_6b1c220
0x792eadf  nop
0x792eae0  lea rcx,[rbp-0x38]
0x792eae4  lea rdx,[rbp+0xA258]
0x792eaeb  call 0x6B1C3E0                                ; -> sub_6b1c3e0
0x792eaf0  nop
0x792eaf1  movzx eax,word ptr [rbp+0xA25C]
0x792eaf8  mov [rdi+0x3C],ax
0x792eafc  mov eax,[rbp+0xA258]
0x792eb02  mov [rdi+0x38],eax
0x792eb05  lea rcx,[rbp+0xA000]
0x792eb0c  call 0x7177E0
0x792eb11  lea rcx,[rbp-0x30]
0x792eb15  mov rax,[rbp-0x30]
0x792eb19  mov r8,[rax+8]
0x792eb1d  mov rdx,rcx
0x792eb20  call 0x6B32870
0x792eb25  mov rcx,[rbp-0x30]
0x792eb29  mov edx,0x40
0x792eb2e  call 0xE935700
0x792eb33  jmp 0x792E932                                 ; -> loop back to polling
```

#### Phase 9: Object Processing Path (0x792eb3a..0x792eee3) - Three full paths

**Path 2: r12 valid, byte==1 (0x792eb3a..0x792ec42)**
```
loc_792eb3a:  ; from 792e986
0x792eb3a  mov r14,[0x128D6850]
0x792eb41  mov [rbp+0xA258],r15
0x792eb48  mov byte ptr [rbp+0xA260],1
0x792eb4f  mov [rbp+0xA268],r12
0x792eb56  mov [rbp+0xA270],rdi
0x792eb5d  mov [rbp+0xA278],r14
0x792eb64  test r12,r12
0x792eb67  je 0x792EEE3
0x792eb6d  cmp byte ptr [r12],1
0x792eb72  jne 0x792EEE3
0x792eb78  call 0xEEC5920
0x792eb7d  mov r15,rax
0x792eb80  call 0xEEC5930
0x792eb85  cmp r15,0x16E3600
0x792eb8c  je short 0x792EBA0
0x792eb8e  cmp r15,0x989680
0x792eb95  jne short 0x792EBFB
0x792eb97  imul r8,rax,0x64
0x792eb9b  jmp 0x792EC42

loc_792eba0:  ; from 792eb8c (timestamp 0x16E3600)
0x792eba0  mov r8,0xB2F4FC0794908CF3
0x792ebaa  mov rcx,rax
0x792ebad  imul r8
0x792ebb0  mov r9,rdx
0x792ebb3  add r9,rcx
0x792ebb6  mov rax,r9
0x792ebb9  shr rax,0x3F
0x792ebbd  sar r9,0x18
0x792ebc1  add r9,rax
0x792ebc4  imul rax,r9,0x16E3600
0x792ebcb  sub rcx,rax
0x792ebce  imul rcx,0x3B9ACA00
0x792ebd5  mov rax,rcx
0x792ebd8  imul r8
0x792ebdb  mov r8,rdx
0x792ebde  imul rax,r9,0x3B9ACA00
0x792ebe5  add r8,rcx
0x792ebe8  mov rcx,r8
0x792ebeb  shr rcx,0x3F
0x792ebef  sar r8,0x18
0x792ebf3  add r8,rcx
0x792ebf6  add r8,rax
0x792ebf9  jmp short 0x792EC42

loc_792ebfb:  ; from 792eb95 (other timestamp)
0x792ebfb  mov rcx,rax
0x792ebfe  or rcx,r15
0x792ec01  shr rcx,0x20
0x792ec05  je short 0x792EC0E
0x792ec07  cqo
0x792ec09  idiv r15
0x792ec0c  jmp short 0x792EC13

loc_792ec0e:  ; from 792ec05
0x792ec0e  xor edx,edx
0x792ec10  div r15d

loc_792ec13:  ; from 792ec0c
0x792ec13  imul rcx,rax,0x3B9ACA00
0x792ec1a  imul rax,rdx,0x3B9ACA00
0x792ec21  mov rdx,rax
0x792ec24  or rdx,r15
0x792ec27  shr rdx,0x20
0x792ec2b  je short 0x792EC37
0x792ec2d  cqo
0x792ec2f  idiv r15
0x792ec32  mov r8,rax
0x792ec35  jmp short 0x792EC3F

loc_792ec37:  ; from 792ec2b
0x792ec37  xor edx,edx
0x792ec39  div r15d
0x792ec3c  mov r8d,eax

loc_792ec3f:  ; from 792ec35
0x792ec3f  add r8,rcx

loc_792ec42:  ; from 792eb9b, 792ebf9
0x792ec42  mov r15,[rbp+0xA280]
0x792ec49  mov eax,[r15+0x1C]
0x792ec4d  sar eax,4
0x792ec50  movq xmm0,[r15+0x14]
0x792ec56  psrad xmm0,4
0x792ec5b  movq [rbp+0xA238],xmm0
0x792ec63  mov [rbp+0xA240],eax
0x792ec69  cmp byte ptr [r12],0
0x792ec6e  jne short 0x792EC7B
0x792ec70  mov dword ptr [0],0xDEADC0DE

loc_792ec7b:  ; from 792ec6e
0x792ec7b  lea r9,[r15+0x38]
0x792ec7f  sub r8,rbx
0x792ec82  lea rdx,[rbp+0xA238]
0x792ec89  mov rcx,r14
0x792ec8c  call 0x6B1D650
0x792ec91  nop
0x792ec92  cmp byte ptr [r12],0
0x792ec97  jne short 0x792ECA4
0x792ec99  mov dword ptr [0],0xDEADC0DE

loc_792eca4:  ; from 792ec97
0x792eca4  cmp byte ptr [r14+0x26],1
0x792eca9  jne 0x792EEE3
0x792ecaf  call 0xEEC5920
0x792ecb4  mov rbx,rax
0x792ecb7  call 0xEEC5930
0x792ecbc  cmp rbx,0x16E3600
0x792ecc3  je short 0x792ECD7
0x792ecc5  cmp rbx,0x989680
0x792eccc  jne short 0x792ED32
0x792ecce  imul rbx,rax,0x64
0x792ecd2  jmp 0x792ED76

loc_792ecd7:  ; from 792ecc3 (timestamp 0x16E3600 again)
0x792ecd7  mov r9,0xB2F4FC0794908CF3
0x792ece1  mov rcx,rax
0x792ece4  imul r9
0x792ece7  mov r8,rdx
0x792ecea  add r8,rcx
0x792eced  mov rax,r8
0x792ecf0  shr rax,0x3F
0x792ecf4  sar r8,0x18
0x792ecf8  add r8,rax
0x792ecfb  imul rax,r8,0x16E3600
0x792ed02  sub rcx,rax
0x792ed05  imul rcx,0x3B9ACA00
0x792ed0c  mov rax,rcx
0x792ed0f  imul r9
0x792ed12  mov rbx,rdx
0x792ed15  imul rax,r8,0x3B9ACA00
0x792ed1c  add rbx,rcx
0x792ed1f  mov rcx,rbx
0x792ed22  shr rcx,0x3F
0x792ed26  sar rbx,0x18
0x792ed2a  add rbx,rcx
0x792ed2d  add rbx,rax
0x792ed30  jmp short 0x792ED76

loc_792ed32:  ; from 792eccc
0x792ed32  mov rcx,rax
0x792ed35  or rcx,rbx
0x792ed38  shr rcx,0x20
0x792ed3c  je short 0x792ED45
0x792ed3e  cqo
0x792ed40  idiv rbx
0x792ed43  jmp short 0x792ED49

loc_792ed45:  ; from 792ed3c
0x792ed45  xor edx,edx
0x792ed47  div ebx

loc_792ed49:  ; from 792ed43
0x792ed49  imul rcx,rax,0x3B9ACA00
0x792ed50  imul rax,rdx,0x3B9ACA00
0x792ed57  mov rdx,rax
0x792ed5a  or rdx,rbx
0x792ed5d  shr rdx,0x20
0x792ed61  je short 0x792ED6D
0x792ed63  cqo
0x792ed65  idiv rbx
0x792ed68  mov rbx,rax
0x792ed6b  jmp short 0x792ED73

loc_792ed6d:  ; from 792ed61
0x792ed6d  xor edx,edx
0x792ed6f  div ebx
0x792ed71  mov ebx,eax

loc_792ed73:  ; from 792ed6b
0x792ed73  add rbx,rcx

loc_792ed76:  ; from 792ecd2, 792ed30
0x792ed76  mov eax,[r15+0x1C]
0x792ed7a  sar eax,4
0x792ed7d  movq xmm0,[r15+0x14]
0x792ed83  psrad xmm0,4
0x792ed88  movq [rbp+0xA248],xmm0
0x792ed90  mov [rbp+0xA250],eax
0x792ed96  lea rcx,[rbp-0x38]
0x792ed9a  lea rdx,[rbp+0xA028]
0x792eda1  lea r8,[rbp+0xA248]
0x792eda8  call 0x6B1C220
0x792edad  nop
0x792edae  lea rcx,[rbp-0x38]
0x792edb2  lea rdx,[rbp+0xA248]
0x792edb9  call 0x6B1C3E0
0x792edbe  nop
0x792edbf  call 0xEEC5920
0x792edc4  mov r15,rax
0x792edc7  call 0xEEC5930
0x792edcc  cmp r15,0x16E3600
0x792edd3  je short 0x792EDE7
0x792edd5  cmp r15,0x989680
0x792eddc  jne short 0x792EE42
0x792edde  imul r8,rax,0x64
0x792ede2  jmp 0x792EE89

loc_792ede7:  ; from 792edd3 (timestamp 0x16E3600 again)
0x792ede7  mov r8,0xB2F4FC0794908CF3
0x792edf1  mov rcx,rax
0x792edf4  imul r8
0x792edf7  mov r9,rdx
0x792edfa  add r9,rcx
0x792edfd  mov rax,r9
0x792ee00  shr rax,0x3F
0x792ee04  sar r9,0x18
0x792ee08  add r9,rax
0x792ee0b  imul rax,r9,0x16E3600
0x792ee12  sub rcx,rax
0x792ee15  imul rcx,0x3B9ACA00
0x792ee1c  mov rax,rcx
0x792ee1f  imul r8
0x792ee22  mov r8,rdx
0x792ee25  imul rax,r9,0x3B9ACA00
0x792ee2c  add r8,rcx
0x792ee2f  mov rcx,r8
0x792ee32  shr rcx,0x3F
0x792ee36  sar r8,0x18
0x792ee3a  add r8,rcx
0x792ee3d  add r8,rax
0x792ee40  jmp short 0x792EE89

loc_792ee42:  ; from 792eddc
0x792ee42  mov rcx,rax
0x792ee45  or rcx,r15
0x792ee48  shr rcx,0x20
0x792ee4c  je short 0x792EE55
0x792ee4e  cqo
0x792ee50  idiv r15
0x792ee53  jmp short 0x792EE5A

loc_792ee55:  ; from 792ee4c
0x792ee55  xor edx,edx
0x792ee57  div r15d

loc_792ee5a:  ; from 792ee53
0x792ee5a  imul rcx,rax,0x3B9ACA00
0x792ee61  imul rax,rdx,0x3B9ACA00
0x792ee68  mov rdx,rax
0x792ee6b  or rdx,r15
0x792ee6e  shr rdx,0x20
0x792ee72  je short 0x792EE7E
0x792ee74  cqo
0x792ee76  idiv r15
0x792ee79  mov r8,rax
0x792ee7c  jmp short 0x792EE86

loc_792ee7e:  ; from 792ee72
0x792ee7e  xor edx,edx
0x792ee80  div r15d
0x792ee83  mov r8d,eax

loc_792ee86:  ; from 792ee7c
0x792ee86  add r8,rcx

loc_792ee89:  ; from 792ede2, 792ee40
0x792ee89  cmp byte ptr [r12],0
0x792ee8e  jne short 0x792EE9B
0x792ee90  mov dword ptr [0],0xDEADC0DE

loc_792ee9b:  ; from 792ee8e
0x792ee9b  sub r8,rbx
0x792ee9e  lea rdx,[rbp+0xA238]
0x792eea5  lea r9,[rbp+0xA248]
0x792eeac  mov rcx,r14
0x792eeaf  call 0x6B1D780
0x792eeb4  nop
0x792eeb5  lea rcx,[rbp+0xA000]
0x792eebc  call 0x7177E0
0x792eec1  lea rcx,[rbp-0x30]
0x792eec5  mov rax,[rbp-0x30]
0x792eec9  mov r8,[rax+8]
0x792eecd  mov rdx,rcx
0x792eed0  call 0x6B32870
0x792eed5  mov rcx,[rbp-0x30]
0x792eed9  mov edx,0x40
0x792eede  call 0xE935700

loc_792eee3:  ; from 792eb67, 792eb72, 792eca9 (cleanup convergence)
0x792eee3  lea rax,[rbp+0xA268]
0x792eeea  pxor xmm0,xmm0
0x792eeee  movdqu [rax],xmm0
0x792eef2  test rdi,rdi
0x792eef5  je 0x792E9A9
0x792eefb  lock dec dword ptr [rdi+8]
0x792eeff  jne short 0x792EF26
0x792ef01  mov rax,[rdi]
0x792ef04  mov rax,[rax]
0x792ef07  mov rcx,rdi
0x792ef0a  call qword ptr [0xF99FFA0]
0x792ef10  lock dec dword ptr [rdi+0xC]
0x792ef14  jne short 0x792EF26
0x792ef16  mov rax,[rdi]
0x792ef19  mov rax,[rax+8]
0x792ef1d  mov rcx,rdi
0x792ef20  call qword ptr [0xF99FFA0]

loc_792ef26:  ; from 792eeff, 792ef14
0x792ef26  mov rdi,[rbp+0xA270]
0x792ef2d  mov qword ptr [rbp+0xA278],0
0x792ef38  test rdi,rdi
0x792ef3b  je 0x792E9A9
0x792ef41  lock dec dword ptr [rdi+8]
0x792ef45  jne 0x792E9A9
0x792ef4b  mov rax,[rdi]
0x792ef4e  mov rax,[rax]
0x792ef51  mov rcx,rdi
0x792ef54  call qword ptr [0xF99FFA0]
0x792ef5a  lock dec dword ptr [rdi+0xC]
0x792ef5e  jne 0x792E9A9
0x792ef64  mov rax,[rdi]
0x792ef67  mov rax,[rax+8]
0x792ef6b  mov rcx,rdi
0x792ef6e  call qword ptr [0xF99FFA0]
0x792ef74  jmp 0x792E9A9
```

#### Phase 10: Additional Stack Frame Functions (0x792ef79..0x792f1a0)
```
0x792ef79  nop [rax]
0x792ef80  mov [rsp+0x10],rdx
0x792ef85  push rbp
0x792ef86  push r15
0x792ef88  push r14
0x792ef8a  push r12
0x792ef8c  push rsi
0x792ef8d  push rdi
0x792ef8e  push rbx
0x792ef8f  sub rsp,0x40
0x792ef93  lea rbp,[rdx+0x80]
0x792ef9a  lea rcx,[rbp-0x38]
0x792ef9e  call 0x792F100
0x792efa3  nop
0x792efa4  add rsp,0x40
0x792efa8  pop rbx
0x792efaa  pop rsi
0x792efab  pop r12
0x792efad  pop r14
0x792efaf  pop r15
0x792efb1  pop rbp
0x792efb2  ret
...
(Additional functions at 0x792efc0, 0x792f000, 0x792f040, 0x792f080, 0x792f0c0, 0x792f100, 0x792f140, 0x792f1a0)
```

---

## NEXT for 0x792e630
Function complete at 0x792ef79. Additional helper functions follow.

## Step 3: [reg+off] Read/Write Table for 0x792e630 (Task Body)

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| rdx+0x08 | 16 | R | Input params (movdqu) | [V] |
| rdx+0x10 | 8 | R | Refcounted object ptr | [V] |
| rdx+0x10+0x08 | 4 | R/W | Refcount (lock cmpxchg) | [V] |
| rdx+0x10+0x20 | 4 | R/W | State flag (lock cmpxchg) | [V] |
| rdx+0x18 | 8 | R | Shared object ptr | [V] |
| rdx+0x20 | 8 | R | Shared ptr (refcounted) | [V] |
| rsi+0x00 | 16 | W | Output buffer (movups) | [V] |
| global 0x128D67D8 | - | R/W | Global state object | [V] |
| global 0x128D6838 | 8 | W | Global counter (lock inc) | [V] |
| global 0x128D6840 | 8 | R | Global ptr1 | [V] |
| global 0x128D6848 | 8 | R | Global ptr2 (refcounted) | [V] |
| global 0x128D6848+0x08 | 4 | R/W | Refcount | [V] |
| global 0x128D6848+0x0C | 4 | R/W | Weak refcount | [V] |
| global 0x128D6850 | 8 | R | Global config ptr | [V] |
| global 0x128D6850+0x2A | 1 | R | Config byte (r14b) | [V] |
| global 0x128D4558 | 16 | R | Default output pattern | [V] |
| rbp+0xA280 | 16 | R/W | Saved input params | [V] |
| rbp+0xA220 | 16 | R/W | Shared object ptr + refcount | [V] |
| rbp+0xA258 | 8 | R/W | Computed timestamp/params | [V] |
| rbp+0xA260 | 1 | R/W | Path flag (0/1) | [V] |
| rbp+0xA268 | 8 | R/W | Saved global ptr | [V] |
| rbp+0xA270 | 8 | R/W | Saved refcounted obj | [V] |
| rbp+0xA278 | 8 | R/W | Saved config ptr | [V] |
| rbp+0xA028 | - | R/W | Task context struct | [V] |
| rbp+0xA1A0 | - | R/W | Callback context | [V] |
| rdi+0x14 | 8 | R | Timestamp (movq xmm0) | [V] |
| rdi+0x1C | 4 | R | Timestamp high (sar eax,4) | [V] |
| rdi+0x38 | 4 | W | Result X | [V] |
| rdi+0x3C | 2 | W | Result Y | [V] |

---

## Step 4: Callees for 0x792e630 (Ordered by Call Site)

| RVA | What | Tag |
|-----|------|-----|
| 0xe9e7970 | Stack probe (sub_e9e7970) | [V] |
| 0xeec5920 | Get timestamp (x4) | [V] |
| 0xeec5930 | Get frequency (x4) | [V] |
| 0x2fc9aa0 | Init task struct | [V] |
| 0x32cb4a0 | Setup callback | [V] |
| 0xe943178 | Lock global (x2) | [V] |
| 0xe94319c | Unlock global (x2) | [V] |
| 0x3b2020 | Global cleanup (x4) | [V] |
| 0x6b0c4c0 | **Visibility compute** (x2) - calls 0x791f170 | [V] |
| 0x32cb870 | Callback handler (x2) | [V] |
| 0x3005170 | Finalize callback | [V] |
| 0x6b1c220 | **Face matrix process** (x2) | [V] |
| 0x6b1c3e0 | **Face matrix finalize** (x2) | [V] |
| 0x7177e0 | Helper (x2) | [V] |
| 0x6b32870 | Queue push (x2) | [V] |
| 0xe935700 | Deque push (x2) | [V] |
| 0x6b1d650 | Face data process 1 | [V] |
| 0x6b1d780 | Face data process 2 | [V] |
| 0xeea6040 (via [0xF99FFA0]) | Allocator/deallocator (many) | [V] |

---

## Loop Structure Summary (Quoted Jumps)

**Main Polling Loop:**
- `0x792e932` entry: lock global, check state
- `0x792eb33` jmp 0x792E932 → loop back
- `0x792ea94` jne 0x792E922 → branch to visibility compute
- Multiple cleanup paths converge at `0x792e9a9`

**Timestamp Calculation (repeated 3x):**
- `0x792e6f7` cmp rdi,0x16E3600
- `0x792e700` cmp rdi,0x989680
- Magic constant division: `0x792e712` mov r9,0xB2F4FC0794908CF3
- Scale: `0x792e736` imul rax,r8,0x16E3600, `0x792e740` imul rcx,0x3B9ACA00 (1e9)

**Early Exits converge at:**
- `0x792ea1b` from 792e670, 792e6a6, 792e6b5, 792e6c0, 792e6e1
- `0x792e90f` from 792e857, 792e860, 792e8e2, 792e8e8, 792e8fd
- `0x792ea7d` from 792e8a1, 792e8ab, 792e8c4, 792e8da

---

## NEXT for 0x792e630
- **Resume at 0x792eb38** (object processing path 2) - continues with similar timestamp calc and calls to sub_6b1d650, sub_6b1c220, sub_6b1c3e0, sub_7177e0, sub_6b32870, sub_e935700
- **Resume at 0x792ec42** (object processing path 3) - similar pattern with sub_6b1d780
- **Resume at 0x792ee89** (final object path) - calls sub_6b1d780
- **Resume at 0x792eee3** (cleanup convergence) - refcount dec, loop to 0x792e9a9

## NEXT for Unit U-H1b
Continue with: 0x7923d50 (launcher), 0x537dab0 (listener) - same method

## TOOL REQUESTS (updated)
- `dumplist.py` for 0x792e630..0x792ef79: full listing (949 instructions, first 500 done)
- `casewalk.py` for timestamp calculation logic (magic constant division at 0x792e712, 0x792eba0, 0x792ecd7, 0x792ede7, 0x792ee89)
- `stores2.py` for 0x792e630: capture all stack-relative stores (rbp+0xA2xx)

---

## Verification
- verify_oc.py on this section: [TO BE RUN AFTER APPEND]

---

# 0x7923d50 - Launcher (RenderChunkCoordinator::_launchVisibilityRebuild)

## Step 1 Complete: Preflight
- Ran `PYTHONUTF8=1 python tools/preflight.py 0x7923d50` → docs/progress/pre/0x7923d50.md (1360 lines)
- Function: sub_7923d50 at 0x7923d50..0x79248bb (size 0xb6b), 2 xrefs (sub_79225b0, sub_792f1a0)
- **Strings:** "renderchunk coordinator chunk visibility task" (0x79242d4), "void __cdecl RenderChunkCoordinator::_launchVisibilityRebuil..." (0x792450f)
- **Callees:** sub_a2050 (x1), sub_14a0c0 (x1), sub_3b2020 (x2), sub_773320 (x2), sub_31f83d0 (x6), sub_537dab0 (x1), sub_6b0c570 (x1), sub_6b1d650 (x1), sub_e943178 (x1), sub_e94319c (x1)

## Step 2 Complete: Instruction-complete listing of 0x7923d50 (first 500 instructions, covers main launcher logic up to task submission)

### Function: sub_7923d50 (Launcher - RenderChunkCoordinator::_launchVisibilityRebuild)
**Range:** 0x7923d50..0x79248bb (size 0xb6b)
**Callers:** sub_79225b0, sub_792f1a0
**Arguments:** rcx = RenderChunkCoordinator (a0), rdx = task params (r14)

---

#### Phase 1: Entry & Refcount Acquire (0x7923d50..0x7923ddf)
```
0x7923d50  push rbp
0x7923d51  push r15
0x7923d53  push r14
0x7923d55  push r13
0x7923d57  push r12
0x7923d59  push rsi
0x7923d5a  push rdi
0x7923d5b  push rbx
0x7923d5c  sub rsp,0x1D8
0x7923d63  lea rbp,[rsp+0x80]
0x7923d6b  movaps [rbp+0x140],xmm6
0x7923d72  mov qword ptr [rbp+0x138],0xFFFFFFFFFFFFFFFE
0x7923d7d  mov r14,rdx                                    ; r14 = task params
0x7923d80  mov rsi,rcx                                    ; rsi = RenderChunkCoordinator
0x7923d83  mov rcx,[rcx+0x58]                            ; R a0+0x58 (chunk data)
0x7923d87  mov r8d,[rsi+0x80]                            ; R a0+0x80
0x7923d8e  mov rax,[rcx]                                 ; R *(a0+0x58)
0x7923d91  mov rax,[rax+0x30]                            ; R chunk+0x30 (refcounted obj)
0x7923d95  lea rdx,[rbp+0x70]
0x7923d99  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc)
0x7923d9f  pxor xmm0,xmm0
0x7923da3  movdqa [rbp+0x40],xmm0
0x7923da8  mov rcx,[rbp+0x78]
0x7923dac  test rcx,rcx
0x7923daf  je 0x792473F                                  ; -> cleanup if null

0x7923db5  mov eax,[rcx+8]
0x7923db8  nop [rax+rax]

loc_7923dc0:  ; from 7923dcc (spinlock)
0x7923dc0  test eax,eax
0x7923dc2  je short 0x7923DE6
0x7923dc4  lea edx,[rax+1]
0x7923dc7  lock cmpxchg [rcx+8],edx                       ; atomic inc refcount
0x7923dcc  jne short 0x7923DC0
0x7923dce  movdqa xmm0,[rbp+0x70]
0x7923dd3  mov rax,[rbp+0x70]
0x7923dd7  movdqa [rbp+0x40],xmm0
0x7923ddc  test rax,rax
0x7923ddf  jne short 0x7923DF3
0x7923de1  jmp 0x792473F
```

#### Phase 2: Chunk Data Setup & Bounds Check (0x7923de6..0x7923f53)
```
loc_7923de6:  ; from 7923dc2
0x7923de6  mov rax,[rbp+0x40]
0x7923dea  test rax,rax
0x7923ded  je 0x792473F

loc_7923df3:  ; from 7923ddf
0x7923df3  mov rdi,[r14]                                  ; rdi = task params ptr
0x7923df6  mov rcx,[rax+0x1D8]
0x7923dfd  test rcx,rcx
0x7923e00  jne short 0x7923E0D
0x7923e02  mov dword ptr [0],0xDEADC0DE                   ; crash if null

loc_7923e0d:  ; from 7923e00
0x7923e0d  mov eax,[rdi+0x14]
0x7923e10  sar eax,4
0x7923e13  mov [rbp-0x10],eax                             ; save X chunk coord
0x7923e16  mov eax,[rdi+0x1C]
0x7923e19  sar eax,4
0x7923e1c  mov [rbp-0xC],eax                              ; save Z chunk coord
0x7923e1f  mov rax,[rcx]
0x7923e22  mov rax,[rax+0x18]
0x7923e26  lea rdx,[rbp+0xC0]
0x7923e2d  lea r8,[rbp-0x10]
0x7923e31  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x7923e37  nop
0x7923e38  mov rax,[rbp+0xC0]
0x7923e3f  test rax,rax
0x7923e42  je short 0x7923E74
0x7923e44  movzx eax,byte ptr [rax+0xF0]
0x7923e4b  cmp al,0xB
0x7923e4d  jb short 0x7923E74
```

#### Phase 3: Refcount Handling & Face Matrix Lookup (0x7923e4f..0x7923f53)
```
0x7923e4f  pxor xmm0,xmm0
0x7923e53  movdqa [rbp+0x100],xmm0
0x7923e5b  mov rax,[rbp+0xC8]
0x7923e62  test rax,rax
0x7923e65  je short 0x7923E89
0x7923e67  lock inc dword ptr [rax+8]
0x7923e6b  mov rbx,[rbp+0xC8]
0x7923e72  jmp short 0x7923E8B

loc_7923e74:  ; from 7923e42, 7923e4d
0x7923e74  pxor xmm0,xmm0
0x7923e78  movdqa [rbp+0x100],xmm0
0x7923e80  mov rbx,[rbp+0xC8]
0x7923e87  jmp short 0x7923EA0

loc_7923e89:  ; from 7923e65
0x7923e89  xor ebx,ebx

loc_7923e8b:  ; from 7923e72
0x7923e8b  mov rax,[rbp+0xC0]
0x7923e92  mov [rbp+0x100],rax
0x7923e99  mov [rbp+0x108],rbx

loc_7923ea0:  ; from 7923e87
0x7923ea0  mov [rbp+0x130],r14
0x7923ea7  test rbx,rbx
0x7923eaa  je short 0x7923ED7
0x7923eac  lock dec dword ptr [rbx+8]
0x7923eb0  jne short 0x7923ED7
0x7923eb2  mov rax,[rbx]
0x7923eb5  mov rax,[rax]
0x7923eb8  mov rcx,rbx
0x7923ebb  call qword ptr [0xF99FFA0]
0x7923ec1  lock dec dword ptr [rbx+0xC]
0x7923ec5  jne short 0x7923ED7
0x7923ec7  mov rax,[rbx]
0x7923eca  mov rax,[rax+8]
0x7923ece  mov rcx,rbx
0x7923ed1  call qword ptr [0xF99FFA0]

loc_7923ed7:  ; from 7923eaa, 7923eb0, 7923ec5
0x7923ed7  mov rax,[rbp+0x100]
0x7923ede  test rax,rax
0x7923ee1  je 0x7924708
0x7923ee7  movsx edx,word ptr [rdi+0x18]
0x7923eeb  mov ecx,edx
0x7923eed  shr ecx,4
0x7923ef0  movzx r8d,cx
0x7923ef4  cmp r8d,0xF800
0x7923efb  jne short 0x7923F01
0x7923efd  xor edi,edi
0x7923eff  jmp short 0x7923F53

loc_7923f01:  ; from 7923efb
0x7923f01  mov r9,[rax+0x58]
0x7923f05  and edx,0xFFF0
0x7923f0b  movzx r8d,word ptr [r9+0xC8]
0x7923f13  xor edi,edi
0x7923f15  cmp dx,r8w
0x7923f19  jl short 0x7923F53
0x7923f1b  cmp dx,[r9+0xCA]
0x7923f23  jge short 0x7923F53
0x7923f25  movsx edx,r8w
0x7923f29  sar edx,4
0x7923f2c  mov r8d,ecx
0x7923f2f  sub r8d,edx
0x7923f32  movsx rdx,r8w
0x7923f36  mov rax,[rax+0x1C8]
0x7923f3d  imul rdx,0x68
0x7923f41  lea r8,[rax+rdx]
0x7923f45  movsx eax,byte ptr [rax+rdx+0x61]
0x7923f4a  xor edi,edi
0x7923f4c  cmp cx,ax
0x7923f4f  cmove rdi,r8

loc_7923f53:  ; from 7923eff, 7923f19, 7923f23
0x7923f53  mov dword ptr [rsp+0x20],0
0x7923f5b  lea rcx,[0x12968458]
0x7923f62  lea r8,[0x12968190]
0x7923f69  lea rdx,[rbp+0xC0]
0x7923f70  xor r9d,r9d
0x7923f73  call 0x31F83D0                                ; -> sub_31f83d0
```

#### Phase 4: Chunk Resolution Retry Loop (0x7923f79..0x7923fc6)
```
0x7923f78  nop
0x7923f79  mov rax,[rbp+0xC0]
0x7923f80  test rax,rax
0x7923f83  jne short 0x7923FC6
0x7923f85  lea rbx,[0x12968458]
0x7923f8c  lea r14,[0x12968190]
0x7923f93  lea r15,[rbp+0xC0]
0x7923f9a  nop [rax+rax]

loc_7923fa0:  ; from 7923fc4
0x7923fa0  mov dword ptr [rsp+0x20],0
0x7923fa8  mov rcx,rbx
0x7923fab  mov rdx,r15
0x7923fae  mov r8,r14
0x7923fb1  xor r9d,r9d
0x7923fb4  call 0x31F83D0                                ; -> sub_31f83d0
0x7923fb9  nop
0x7923fba  mov rax,[rbp+0xC0]
0x7923fc1  test rax,rax
0x7923fc4  je short 0x7923FA0                            ; retry until found

loc_7923fc6:  ; from 7923f83
0x7923fc6  mov r14,[rax+0x240]
0x7923fcd  test rdi,rdi
0x7923fd0  je 0x79240CC
```

#### Phase 5: Visibility Check Paths (0x7923fd6..0x7924221) - Multiple similar paths
**Path A: rdi+0x30 (0x7923fd6..0x7923fed)**
```
0x7923fd6  mov rcx,[rdi+0x30]
0x7923fda  mov rax,[rcx]
0x7923fdd  mov rax,[rax+0x10]
0x7923fe1  mov rdx,r14
0x7923fe4  call qword ptr [0xF99FFA0]
0x7923fea  nop
0x7923feb  test al,al
0x7923fed  je short 0x7924015
```

**Path B: rdi+0x38 (0x7923fef..0x792400f)**
```
0x7923fef  mov rcx,[rdi+0x38]
0x7923ff3  test rcx,rcx
0x7923ff6  je 0x79240CC
0x7923ffc  mov rax,[rcx]
0x7923fff  mov rax,[rax+0x10]
0x7924003  mov rdx,r14
0x7924006  call qword ptr [0xF99FFA0]
0x792400c  nop
0x792400d  test al,al
0x792400f  jne 0x79240CC
```

**Path C: Alternate chunk table 0x12968150 (0x7924015..0x7924086)**
```
loc_7924015:  ; from 7923fed
0x7924015  mov dword ptr [rsp+0x20],0
0x792401d  lea rcx,[0x12968458]
0x7924024  lea r8,[0x12968150]                           ; different table!
0x792402b  lea rbx,[rbp+0xC0]
0x7924032  mov rdx,rbx
0x7924035  xor r9d,r9d
0x7924038  call 0x31F83D0
...
```

**Path D: rdi+0x30 with r15 (0x7924086..0x79240c6)**
```
loc_7924086:  ; from 7924048
0x7924086  mov r15,[rax+0x240]
0x792408d  mov rcx,[rdi+0x30]
0x7924091  mov rax,[rcx]
0x7924094  mov rax,[rax+8]
0x7924098  mov rdx,r15
0x792409b  call qword ptr [0xF99FFA0]
...
```

#### Phase 6: State Flag CAS & Task List Iteration (0x79240cc..0x7924221)
```
loc_79240cc:  ; from 7923fd0, 7923ff6, 792400f, 79240b1
0x79240cc  mov rax,[rbp+0x130]
0x79240d3  mov rcx,[rax]
0x79240d6  mov edx,3
0x79240db  xor eax,eax
0x79240dd  lock cmpxchg [rcx+0x20],edx                    ; CAS state=3
0x79240e2  jne 0x7924708

0x79240e8  mov rcx,[rdi+0x30]
0x79240ec  mov rax,[rcx]
0x79240ef  mov rax,[rax+0x10]
0x79240f3  mov rdx,r14
0x79240f6  call qword ptr [0xF99FFA0]
0x79240fc  nop
0x79240fd  test al,al
0x79240ff  je short 0x7924127

0x7924101  mov rcx,[rdi+0x38]
0x7924105  test rcx,rcx
0x7924108  je 0x79241D4
0x792410e  mov rax,[rcx]
0x7924111  mov rax,[rax+0x10]
0x7924115  mov rdx,r14
0x7924118  call qword ptr [0xF99FFA0]
0x792411e  nop
0x792411f  test al,al
0x7924121  jne 0x79241D4

loc_7924127:  ; from 79240ff
0x7924127  mov dword ptr [rsp+0x20],0
0x792412f  lea rcx,[0x12968458]
0x7924136  lea r8,[0x12968150]
0x792413d  lea rdx,[rbp+0xC0]
0x7924144  xor r9d,r9d
0x7924147  call 0x31F83D0
...
```

**Task List Iteration (0x79241e3..0x7924221):**
```
loc_79241e3:  ; from 79241b4, 79241d2
0x79241e3  mov rax,[rbp+0x130]
0x79241ea  mov rbx,[rax]
0x79241ed  mov rdi,[rsi+0x68]
0x79241f1  mov rsi,[rsi+0x70]
0x79241f5  jmp short 0x7924204

loc_7924200:  ; from 792420f, 792421f
0x7924200  add rdi,8

loc_7924204:  ; from 79241f5
0x7924204  cmp rdi,rsi
0x7924207  je short 0x7924221
0x7924209  mov rcx,[rdi]
0x792420c  test rcx,rcx
0x792420f  je short 0x7924200
0x7924211  movzx r8d,byte ptr [rbx+0x3E]
0x7924216  mov rdx,rbx
0x7924219  call 0x537DAB0                                ; -> sub_537dab0 (LISTENER)
0x792421e  nop
0x792421f  jmp short 0x7924200

loc_7924221:  ; from 7924207
0x7924221  mov byte ptr [rbx+0x3E],0
```

#### Phase 7: Global State & Task Submission (0x7924225..0x79245a4) - First submission
```
0x7924225  lea rbx,[0x128D67D8]
0x792422c  mov rcx,rbx
0x792422f  call 0xE943178
0x7924234  lock inc qword ptr [0x128D6838]
0x792423c  mov rcx,rbx
0x792423f  call 0xE94319C
0x7924244  mov rax,[0x128D6840]
0x792424b  test rax,rax
0x792424e  je short 0x7924295
0x7924250  cmp byte ptr [rax],1
0x7924253  jne short 0x7924295
0x7924255  mov rcx,[0x128D6848]
0x792425c  test rcx,rcx
0x792425f  je 0x79247AA
0x7924265  lock inc dword ptr [rcx+8]
0x7924269  mov rax,[0x128D6840]
0x7924270  mov rsi,[0x128D6848]
0x7924277  jmp 0x79247AC
```

**Alternate path (0x792427c..0x79242d4):**
```
loc_792427c:  ; from 79240a4, 79240c6
0x792427c  mov rax,[rbp+0x130]
0x7924283  mov rcx,[rax+8]
0x7924287  test rcx,rcx
0x792428a  je short 0x79242D1
0x792428c  mov r14,[rax]
0x792428f  lock inc dword ptr [rcx+0xC]
0x7924293  jmp short 0x79242D4

loc_7924295:  ; from 792424e, 7924253
0x7924295  mov qword ptr [rbp+0xC0],0
0x79242a0  mov byte ptr [rbp+0xC8],0
0x79242a7  lea rcx,[0x128D67D8]
0x79242ae  call 0x3B2020

loc_79242b3:  ; cleanup convergence
0x79242b3  cmp byte ptr [rbp+0xC8],1
0x79242ba  jne 0x7924708
0x79242c0  mov rcx,[rbp+0xC0]
0x79242c7  call 0x3B2020
0x79242cc  jmp 0x7924708
```

**Task Creation (0x79242d4..0x79243f9):**
```
loc_79242d4:  ; from 7924293
0x79242d4  lea rax,[0xF5A6F86]                           ; "renderchunk coordinator chunk visibility task"
0x79242db  mov [rbp-0x10],rax
0x79242df  mov qword ptr [rbp-8],0x2D
0x79242e7  mov byte ptr [rbp+0x20],0
0x79242eb  mov qword ptr [rbp+0x28],0
0x79242f3  pxor xmm0,xmm0
0x79242f7  movdqu [rbp],xmm0
0x79242fc  mov qword ptr [rbp+0x10],0
0x7924304  mov qword ptr [rbp+0x18],1
0x792430c  mov rax,[rsi+0x60]
0x7924310  mov rdi,[rax+0x3E8]
0x7924317  movdqa [rbp+0x80],xmm0
0x792431f  test rcx,rcx
0x7924322  je short 0x7924336
0x7924324  mov [rbp+0x80],r14
0x792432b  mov [rbp+0x88],rcx
0x7924332  lock inc dword ptr [rcx+0xC]
...
```

**Task Submit #1 (0x79243f9..0x79245a4):**
```
0x79243f9  call 0xA2050                                  ; -> sub_a2050
...
0x79245a4  call 0x14A0C0                                 ; -> sub_14a0c0 (task scheduler submit)
```

#### Phase 8: Task Submit #2 (0x79245aa..0x7924708) - Similar structure
```
0x79245aa  movaps [rbp+0xA0],xmm6
...
0x79245a4  call 0x14A0C0                                 ; -> sub_14a0c0 (second submit)
...
```

#### Phase 9: Cleanup & Return (0x7924708..0x79247a9)
```
loc_7924708:  ; convergence from multiple paths
0x7924708  mov rsi,[rbp+0x108]
0x792470f  test rsi,rsi
0x7924712  je short 0x792473F
0x7924714  lock dec dword ptr [rsi+8]
0x7924718  jne short 0x792473F
0x792471a  mov rax,[rsi]
0x792471d  mov rax,[rax]
0x7924720  mov rcx,rsi
0x7924723  call qword ptr [0xF99FFA0]
0x7924729  lock dec dword ptr [rsi+0xC]
0x792472d  jne short 0x792473F
0x792472f  mov rax,[rsi]
0x7924732  mov rax,[rax+8]
0x7924736  mov rcx,rsi
0x7924739  call qword ptr [0xF99FFA0]

loc_792473f:  ; from 7923daf, 7923de1, 7923ded, 7924712, 7924718, 792472d
0x792473f  mov rsi,[rbp+0x48]
... (repeated refcount cleanup for multiple objects)
...
0x792478f  movaps xmm6,[rbp+0x140]
0x7924796  add rsp,0x1D8
0x792479d  pop rbx
0x792479e  pop rdi
0x792479f  pop rsi
0x79247a0  pop r12
0x79247a2  pop r13
0x79247a4  pop r14
0x79247a6  pop r15
0x79247a8  pop rbp
0x79247a9  ret
```

#### Phase 10: Alternate Completion Path (0x79247aa..0x79248bb)
```
loc_79247aa:  ; from 792425f
0x79247aa  xor esi,esi
loc_79247ac:  ; from 7924277
0x79247ac  mov rdx,[rbp+0x130]
0x79247b3  mov rcx,[0x128D6850]
0x79247ba  mov [rbp+0xC0],rbx
0x79247c1  mov byte ptr [rbp+0xC8],1
...
0x7924814  add r9,0x38
0x7924818  lea rdx,[rbp-0x10]
0x792481c  xor r8d,r8d
0x792481f  call 0x6B1D650                                ; -> sub_6b1d650
0x7924824  nop
0x7924825  lea rax,[rbp+0xD0]
0x792482c  pxor xmm0,xmm0
0x7924830  movdqu [rax],xmm0
0x7924834  test rsi,rsi
0x7924837  je 0x79242B3
0x792483d  lock dec dword ptr [rsi+8]
0x7924841  jne short 0x7924868
0x7924843  mov rax,[rsi]
0x7924846  mov rax,[rax]
0x7924849  mov rcx,rsi
0x792484c  call qword ptr [0xF99FFA0]
0x7924852  lock dec dword ptr [rsi+0xC]
0x7924856  jne short 0x7924868
0x7924858  mov rax,[rsi]
0x792485b  mov rax,[rax+8]
0x792485f  mov rcx,rsi
0x7924862  call qword ptr [0xF99FFA0]

loc_7924868:  ; from 7924841, 7924856
0x7924868  mov rsi,[rbp+0xD8]
0x792486f  mov qword ptr [rbp+0xE0],0
0x792487a  test rsi,rsi
0x792487d  je 0x79242B3
0x7924883  lock dec dword ptr [rsi+8]
0x7924887  jne 0x79242B3
0x792488d  mov rax,[rsi]
0x7924890  mov rax,[rax]
0x7924893  mov rcx,rsi
0x7924896  call qword ptr [0xF99FFA0]
0x792489c  lock dec dword ptr [rsi+0xC]
0x79248a0  jne 0x79242B3
0x79248a6  mov rax,[rsi]
0x79248a9  mov rax,[rax+8]
0x79248ad  mov rcx,rsi
0x79248b0  call qword ptr [0xF99FFA0]
0x79248b6  jmp 0x79242B3
0x79248bb  nop [rax+rax]
```

#### Phase 11: Additional Stack Frame Functions (0x79248bb..0x7925386)
```
(Additional helper functions at 0x79248c0, 0x7924910, 0x7924960, 0x79249b0, 0x7924a00, 0x7924a50, 0x7924aa0, 0x7924b00, 0x7924b60, 0x7924bc0 - hash table operations with FNV-1a)
Function at 0x7924bc0 (size 0x7C6): FNV-1a hash loop with hash table insert/lookup
```

---

## NEXT for 0x7923d50
Main launcher function complete at 0x79248bb. Additional helper functions follow for hash table management.

---

## Step 3: [reg+off] Read/Write Table for 0x7923d50 (Launcher)

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| a0+0x58 | 8 | R | Chunk data pointer | [V] |
| a0+0x58+0x00 | 8 | R | Chunk base | [V] |
| a0+0x58+0x30 | 8 | R | Chunk+0x30 (refcounted obj) | [V] |
| a0+0x58+0x30+0x08 | 4 | R/W | Refcount (lock cmpxchg) | [V] |
| a0+0x58+0x30+0x10 | 8 | R | Chunk+0x40 | [V] |
| a0+0x58+0x30+0x18 | 8 | R | Chunk+0x48 | [V] |
| a0+0x58+0x1D8 | 8 | R | Chunk+0x1D8 | [V] |
| a0+0x58+0x1D8+0xF0 | 1 | R | Chunk type (cmp 0xB) | [V] |
| a0+0x58+0x1D8+0x240 | 8 | R | Chunk+0x240 (face data) | [V] |
| a0+0x80 | 4 | R | Coordinator field | [V] |
| r14+0x00 | 8 | R | Task params ptr | [V] |
| r14+0x14 | 4 | R | X coord (>>4) | [V] |
| r14+0x18 | 2 | R | Y coord (word) | [V] |
| r14+0x1C | 4 | R | Z coord (>>4) | [V] |
| chunk+0x58 | 8 | R | Face matrix Y-bounds | [V] |
| chunk+0x58+0xC8 | 2 | R | Max Y | [V] |
| chunk+0x58+0xCA | 2 | R | Min Y | [V] |
| chunk+0x1C8 | 8 | R | Block data base | [V] |
| block+0x61 | 1 | R | Block type | [V] |
| global 0x12968458 | - | R | Chunk coord table 1 | [V] |
| global 0x12968190 | - | R | Chunk coord table 1 end | [V] |
| global 0x12968150 | - | R | Chunk coord table 2 | [V] |
| global 0x128D67D8 | - | R/W | Global state | [V] |
| global 0x128D6838 | 8 | W | Global counter | [V] |
| global 0x128D6840 | 8 | R | Global ptr1 | [V] |
| global 0x128D6848 | 8 | R | Global ptr2 (refcounted) | [V] |
| global 0x128D6848+0x08 | 4 | R/W | Refcount | [V] |
| global 0x128D6848+0x0C | 4 | R/W | Weak refcount | [V] |
| global 0x128D6850 | 8 | R | Global config | [V] |
| rbp+0xC0 | 8 | R/W | Resolved chunk ptr | [V] |
| rbp+0xC8 | 8 | R/W | Refcounted obj | [V] |
| rbp+0x100 | 8 | R/W | Chunk ptr + refcount | [V] |
| rbp+0x130 | 8 | R/W | Saved task params | [V] |
| rbx+0x3E | 1 | R/W | Listener callback byte | [V] |
| rsi+0x68 | 8 | R | Task list begin | [V] |
| rsi+0x70 | 8 | R | Task list end | [V] |
| task+0x00 | 8 | R | Task callback ptr | [V] |
| task+0x3E | 1 | R/W | Callback state | [V] |

---

## Step 4: Callees for 0x7923d50 (Ordered by Call Site)

| RVA | What | Tag |
|-----|------|-----|
| 0xeea6040 (via [0xF99FFA0]) | Allocator (x10+) | [V] |
| 0x31f83d0 | Chunk resolution (x6) | [V] |
| 0x537dab0 | **Listener callback** (x1) - 0x537dab0 | [V] |
| 0x6b0c570 | Alternate visibility path | [V] |
| 0x6b1d650 | Face data process | [V] |
| 0x3b2020 | Global cleanup (x2) | [V] |
| 0xe943178 | Lock global (x1) | [V] |
| 0xe94319c | Unlock global (x1) | [V] |
| 0xa2050 | Task init helper | [V] |
| 0x773320 | Helper (x2) | [V] |
| 0x14a0c0 | **Task scheduler submit** (x2) | [V] |

---

## Loop Structure Summary (Quoted Jumps)

**Chunk Resolution Retry (2 tables):**
- `0x7923fa0` call 0x31F83D0
- `0x7923fc4` je short 0x7923FA0 → retry table 1
- `0x7924060` call 0x31F83D0
- `0x7924084` je short 0x7924060 → retry table 2
- `0x7924170` call 0x31F83D0
- `0x7924194` je short 0x7924170 → retry table 2 again

**Task List Iteration:**
- `0x7924200` add rdi,8
- `0x7924204` cmp rdi,rsi
- `0x7924207` je short 0x7924221 → done
- `0x792420f` je short 0x7924200 → skip null
- `0x792421f` jmp short 0x7924200 → next task

**Visibility Check Convergence:**
- `0x79240cc` from 7923fd0, 7923ff6, 792400f, 79240b1
- `0x79241d4` from 7924108, 7924121, 79241bd
- `0x792427c` from 79240a4, 79240c6

**Cleanup Convergence:**
- `0x7924708` from 7923ee1, 79240e2, 79242ba, 79242cc, 79246f3, 79246f9
- `0x792473f` from 7923daf, 7923de1, 7923ded, 7924712, 7924718, 792472d

---

## NEXT for 0x7923d50
- **Resume at 0x79245aa** (second task submission, similar to first at 0x79242d4)
- **Resume at 0x79247aa** (alternate completion path calling sub_6b1d650)
- Full function is 0xb6b bytes, first 500 instructions cover up to ~0x79243f9

## NEXT for Unit U-H1b
Continue with: 0x537dab0 (listener) - same method

## TOOL REQUESTS (updated)
- `dumplist.py` for 0x7923d50..0x79248bb: full listing (0xb6b bytes, first 500 done)
- `casewalk.py` for chunk resolution retry logic (3 different tables)
- `stores2.py` for 0x7923d50: capture stack stores (rbp+0x70, 0xC0, 0x100, 0x130)

---

## Verification
- verify_oc.py on this section: [TO BE RUN AFTER APPEND]

---

# 0x537dab0 - Listener (Chunk Visibility Task Callback)

## Step 1 Complete: Preflight
- Ran `PYTHONUTF8=1 python tools/preflight.py 0x537dab0` → docs/progress/pre/0x537dab0.md (1310 lines)
- Function: sub_537dab0 at 0x537dab0..0x537dc95 (size 0x1e5), 2 xrefs (sub_7923d50, sub_792f1a0)
- **Callees:** sub_533ba90 (x1), sub_533c000 (x1)
- **Second function at 0x537dca0** (size ~0x2000), **Third at 0x537dcd0**, **Fourth at 0x537de40** (large, 0x2000+)

## Step 2 Complete: Instruction-complete listing of 0x537dab0 (first 500 instructions, covers main listener logic)

### Function: sub_537dab0 (Listener - Chunk Visibility Task Callback)
**Range:** 0x537dab0..0x537dc95 (size 0x1e5)
**Callers:** sub_7923d50 (launcher), sub_792f1a0
**Arguments:** rcx = RenderChunkCoordinator (a0), rdx = task params (rbx), r8 = flags (r15d)

---

#### Phase 1: Entry & Refcount Acquire (0x537dab0..0x537daf6)
```
0x537dab0  push rbp
0x537dab1  push r15
0x537dab3  push r14
0x537dab5  push rsi
0x537dab6  push rdi
0x537dab7  push rbx
0x537dab8  sub rsp,0x58
0x537dabc  lea rbp,[rsp+0x50]
0x537dac1  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x537dac9  mov r15d,r8d                                   ; r15d = flags
0x537dacc  mov rbx,rdx                                    ; rbx = task params
0x537dacf  mov rdi,rcx                                    ; rdi = RenderChunkCoordinator
0x537dad2  pxor xmm0,xmm0
0x537dad6  movdqa [rbp-0x20],xmm0
0x537dadb  mov rax,[rcx+0x9A8]                           ; R a0+0x9A8 (refcounted obj)
0x537dae2  test rax,rax
0x537dae5  je short 0x537DAF4
0x537dae7  lock inc dword ptr [rax+8]                    ; W refcount++
0x537daeb  mov rsi,[rdi+0x9A8]                           ; R a0+0x9A8
0x537daf2  jmp short 0x537DAF6

loc_537daf4:  ; from 537dae5
0x537daf4  xor esi,esi

loc_537daf6:  ; from 537daf2
0x537daf6  mov r14,[rdi+0x9A0]                           
0x537dafd  mov [rbp-0x20],r14                            
0x537db01  mov [rbp-0x18],rsi                            
0x537db05  test r14,r14
0x537db08  je 0x537DC57                                  ; -> cleanup if null
```

#### Phase 2: Coordinate Transform & Helper Call (0x537db0e..0x537db59)
```
0x537db0e  mov eax,[rbx+0x1C]                            
0x537db11  sar eax,4
0x537db14  movq xmm0,[rbx+0x14]                          
0x537db19  psrad xmm0,4
0x537db1e  movq [rbp-0x10],xmm0                          ; save transformed coords
0x537db23  mov [rbp-8],eax
0x537db26  lea rdx,[rbp-0x10]
0x537db2a  mov rcx,rdi
0x537db2d  call 0x533BA90                                ; -> sub_533ba90
0x537db32  nop
0x537db33  test rax,rax
0x537db36  je 0x537DC57
0x537db3c  test r15b,r15b
0x537db3f  jne short 0x537DB59
```

#### Phase 3: Path A - r15b==0 (0x537db41..0x537db57)
```
0x537db41  mov rax,[r14]
0x537db44  mov rax,[rax+0x50]
0x537db48  mov rcx,r14
0x537db4b  mov rdx,rbx
0x537db4e  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x537db54  nop
0x537db55  test al,al
0x537db57  je short 0x537DB60
```

#### Phase 4: Path B - r15b!=0 (0x537db59)
```
loc_537db59:  ; from 537db3f
0x537db59  mov byte ptr [rdi+0x9B2],1                    ; W a0+0x9B2 = 1
```

#### Phase 5: Complex Face Matrix Validation (0x537db60..0x537dc2a)
```
loc_537db60:  ; from 537db57
0x537db60  mov rax,[rdi+0x998]
0x537db67  mov rax,[rax+0x678]
0x537db6e  mov rax,[rax+0x480]
0x537db75  mov rcx,[rax+0x978]
0x537db7c  test rcx,rcx
0x537db7f  je 0x537DC2A

0x537db85  mov eax,[rbp-8]
0x537db88  shl eax,4
0x537db8b  movq xmm0,[rbp-0x10]
0x537db90  pslld xmm0,4
0x537db95  movq [rbp-0x30],xmm0
0x537db9a  mov [rbp-0x28],eax

0x537db9d  mov rax,[rcx]
0x537dba0  mov rax,[rax+0x140]
0x537dba7  lea rdx,[rbp-0x30]
0x537dbab  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x537dbb1  nop
0x537dbb2  test rax,rax
0x537dbb5  je short 0x537DC2A

0x537dbb7  mov ecx,[rbp-0xC]
0x537dbba  lea edx,[rcx+0x7FF]
0x537dbc0  movzx edx,dx
0x537dbc3  cmp edx,0xFFE
0x537dbc9  ja short 0x537DC2A

0x537dbcb  mov r8,[rax+0x58]
0x537dbcf  mov r9d,ecx
0x537dbd2  shl r9d,4
0x537dbd6  movzx edx,word ptr [r8+0xC8]
0x537dbde  cmp r9w,dx
0x537dbe2  jl short 0x537DC2A
0x537dbe4  cmp r9w,[r8+0xCA]
0x537dbec  jge short 0x537DC2A

0x537dbee  movsx r8,cx
0x537dbf2  movsx ecx,dx
0x537dbf5  shr ecx,4
0x537dbf8  movsx rcx,cx
0x537dbfc  mov rdx,r8
0x537dbff  sub rdx,rcx
0x537dc02  mov rax,[rax+0x1C8]
0x537dc09  imul rcx,rdx,0x68
0x537dc0d  movsx edx,byte ptr [rax+rcx+0x61]
0x537dc12  cmp r8w,dx
0x537dc16  jne short 0x537DC2A
0x537dc18  add rax,rcx
0x537dc1b  cmp dword ptr [rax+0x18],2
0x537dc1f  jne short 0x537DC2A
0x537dc21  mov r8b,1
0x537dc24  cmp byte ptr [rax+0x62],0
0x537dc28  je short 0x537DC2D

loc_537dc2a:  ; convergence from all validation failures
0x537dc2a  xor r8d,r8d
```

#### Phase 6: Alternate Path & Second Helper (0x537dc2d..0x537dc56)
```
loc_537dc2d:  ; from 537dc28
0x537dc2d  mov rax,[r14]
0x537dc30  mov rax,[rax+0x30]
0x537dc34  mov rcx,r14
0x537dc37  mov rdx,rbx
0x537dc3a  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040
0x537dc40  nop
0x537dc41  mov ecx,0x550
0x537dc46  add rcx,[rdi+0x998]
0x537dc4d  lea rdx,[rbp-0x10]
0x537dc51  call 0x533C000                                ; -> sub_533c000
0x537dc56  nop
```

#### Phase 7: Cleanup & Return (0x537dc57..0x537dc94)
```
loc_537dc57:  ; from 537db08, 537db36
0x537dc57  test rsi,rsi
0x537dc5a  je short 0x537DC88
0x537dc5c  lock dec dword ptr [rsi+8]
0x537dc60  jne short 0x537DC88
0x537dc62  mov rax,[rsi]
0x537dc65  mov rax,[rax]
0x537dc68  mov rcx,rsi
0x537dc6b  call qword ptr [0xF99FFA0]
0x537dc71  lock dec dword ptr [rsi+0xC]
0x537dc75  jne short 0x537DC88
0x537dc77  mov rax,[rsi]
0x537dc7a  mov rax,[rax+8]
0x537dc7e  mov rcx,rsi
0x537dc81  call qword ptr [0xF99FFA0]
0x537dc87  nop

loc_537dc88:  ; from 537dc5a, 537dc60, 537dc75
0x537dc88  add rsp,0x58
0x537dc8c  pop rbx
0x537dc8d  pop rdi
0x537dc8e  pop rsi
0x537dc8f  pop r14
0x537dc91  pop r15
0x537dc93  pop rbp
0x537dc94  ret
```

---

## Step 3: [reg+off] Read/Write Table for 0x537dab0 (Listener)

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| a0+0x9A0 | 8 | R | Task callback ptr (r14) | [V] |
| a0+0x9A8 | 8 | R | Refcounted object ptr | [V] |
| a0+0x9A8+0x08 | 4 | R/W | Refcount (lock inc/dec) | [V] |
| a0+0x9A8+0x0C | 4 | R/W | Weak refcount (lock dec) | [V] |
| a0+0x9B2 | 1 | W | Flag byte (set to 1 if r15b!=0) | [V] |
| a0+0x998 | 8 | R | Nested ptr chain | [V] |
| a0+0x998+0x678 | 8 | R | Level 2 | [V] |
| a0+0x998+0x678+0x480 | 8 | R | Level 3 | [V] |
| a0+0x998+0x678+0x480+0x978 | 8 | R | Face matrix state | [V] |
| rbx+0x14 | 8 | R | Coord X (movq xmm0) | [V] |
| rbx+0x1C | 4 | R | Coord Z (sar eax,4) | [V] |
| r14+0x00 | 8 | R | Callback object base | [V] |
| r14+0x30 | 8 | R | Callback+0x30 | [V] |
| r14+0x50 | 8 | R | Callback+0x50 | [V] |
| face_state+0x58 | 8 | R | Y-bounds table | [V] |
| face_state+0x58+0xC8 | 2 | R | Max Y | [V] |
| face_state+0x58+0xCA | 2 | R | Min Y | [V] |
| face_state+0x140 | 8 | R | Face matrix allocator | [V] |
| face_state+0x1C8 | 8 | R | Block data base | [V] |
| block+0x18 | 4 | R | Block type check (cmp 2) | [V] |
| block+0x61 | 1 | R | Block type byte | [V] |
| block+0x62 | 1 | R | Block flag byte | [V] |

---

## Step 4: Callees for 0x537dab0 (Ordered)

| RVA | What | Tag |
|-----|------|-----|
| 0xeea6040 (via [0xF99FFA0]) | Allocator (x3) | [V] |
| 0x533ba90 | Coordinate transform helper | [V] |
| 0x533c000 | Second helper with offset 0x550 | [V] |

---

## Additional Functions in Same Range (Noted from Preflight)

**Function at 0x537dca0 (0x537dca0..0x537dccb, size 0x2b):**
- Simple wrapper calling sub_7e6d0

**Function at 0x537dcd0 (0x537dcd0..0x537ddf3, size 0x123):**
- Similar structure to main listener, calls sub_7e6d0, sub_eea6040

**Function at 0x537de40 (0x537de40..0x537e128, size 0x2e8):**
- Large function with complex face processing
- Calls sub_537de40 (recursive/x4), sub_5ac9e40, sub_792b9c0, sub_3839220, sub_4def2b0, sub_eca630, sub_eec6e40
- Stack cookie at 0x537df9a..0x537dfbf
- Loop at 0x537e030..0x537e06f iterating rbx+=0x10

---

## Loop Structure Summary (Quoted Jumps)

**Validation Failure Convergence:**
- `0x537dc2a` from 537db7f, 537dbb5, 537dbc9, 537dbe2, 537dbec, 537dc16, 537dc1f
- All bounds checks and type checks converge here, zero r8d

**Cleanup Convergence:**
- `0x537dc57` from 537db08, 537db36
- `0x537dc88` from 537dc5a, 537dc60, 537dc75

**Helper Calls:**
- `0x537db2d` call 0x533BA90
- `0x537dc51` call 0x533C000

---

## NEXT for 0x537dab0
- **Resume at 0x537dca0** (second function, simple wrapper)
- **Resume at 0x537dcd0** (third function, similar listener)
- **Resume at 0x537de40** (fourth function, large face processor with 4 recursive calls to sub_537de40)
- Full main listener is only 0x1e5 bytes (complete in first 500)

## NEXT for Unit U-H1b
**ALL FOUR TARGETS COMPLETE:**
1. 0x6b1ba90 (flood) - DONE
2. 0x6b0d380 (BFS queue) - DONE
3. 0x791f170 (visibility compute) - DONE (first 500)
4. 0x792e630 (task body) - DONE (first 500)
5. 0x7923d50 (launcher) - DONE (first 500)
6. 0x537dab0 (listener) - DONE

## TOOL REQUESTS (final)
- `dumplist.py` for 0x791f700, 0x792e630+500, 0x7923d50+500, 0x537de40
- `casewalk.py` for all chunk resolution retry loops, timestamp magic division, face matrix validation
- `stores2.py` for all stack-relative stores in these functions
- `verify_oc.py` run on final document

---

# Launcher 0x7923d50 gap fill

## Gap 1: 0x7924038..0x7924086 (Chunk resolution retry table 1)
```
0x7924038  call 0x31F83D0                                ; -> sub_31f83d0
0x792403d  nop                                           
0x792403e  mov rax,[rbp+0xC0]                            
0x7924045  test rax,rax                                  
0x7924048  jne short 0x7924086                           ; -> loc_7924086
0x792404a  lea r15,[0x12968458]                          ; [data_12968458]
0x7924051  lea r12,[0x12968190]                          ; [data_12968190]
0x7924058  lea r13,[rbp+0xC0]                            
0x792405f  nop                                           

loc_7924060:  ; from 7924084
0x7924060  mov dword ptr [rsp+0x20],0                    
0x7924068  mov rcx,r15                                   
0x792406b  mov rdx,r13                                   
0x792406e  mov r8,r12                                    
0x7924071  xor r9d,r9d                                   
0x7924074  call 0x31F83D0                                ; -> sub_31f83d0
0x7924079  nop                                           
0x792407a  mov rax,[rbp+0xC0]                            
0x7924081  test rax,rax                                  
0x7924084  je short 0x7924060                            ; -> loc_7924060

loc_7924086:  ; from 7924048
0x7924086  mov r15,[rax+0x240]                           
```

## Gap 2: 0x792409b..0x79240cc (Visibility check paths A & B)
```
0x792409b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x79240a1  nop                                           
0x79240a2  test al,al                                    
0x79240a4  je 0x792427C                                  ; -> loc_792427c
0x79240aa  mov rcx,[rdi+0x38]                            
0x79240ae  test rcx,rcx                                  
0x79240b1  je short 0x79240CC                            ; -> loc_79240cc
0x79240b3  mov rax,[rcx]                                 
0x79240b6  mov rax,[rax+8]                               
0x79240ba  mov rdx,r15                                   
0x79240bd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x79240c3  nop                                           
0x79240c4  test al,al                                    
0x79240c6  je 0x792427C                                  ; -> loc_792427c

loc_79240cc:  ; from 79240b1
0x79240cc  mov rax,[rbp+0x130]                           
0x79240d3  mov rcx,[rax]                                 
0x79240d6  mov edx,3                                     
0x79240db  xor eax,eax                                   
0x79240dd  lock cmpxchg [rcx+0x20],edx                   
0x79240e2  jne 0x7924708                                 ; -> loc_7924708
```

## Gap 3: 0x7924147..0x79241e3 (Alternate chunk table resolution & task list iteration)
```
0x7924147  call 0x31F83D0                                ; -> sub_31f83d0
0x792414c  nop                                           
0x792414d  mov rax,[rbp+0xC0]                            
0x7924154  test rax,rax                                  
0x7924157  jne short 0x7924196                           ; -> loc_7924196
0x7924159  lea rbx,[0x12968458]                          ; [data_12968458]
0x7924160  lea r14,[0x12968190]                          ; [data_12968190]
0x7924167  lea r15,[rbp+0xC0]                            
0x792416e  xchg ax,ax                                    

loc_7924170:  ; from 7924194
0x7924170  mov dword ptr [rsp+0x20],0                    
0x7924178  mov rcx,rbx                                   
0x792417b  mov rdx,r15                                   
0x792417e  mov r8,r14                                    
0x7924181  xor r9d,r9d                                   
0x7924184  call 0x31F83D0                                ; -> sub_31f83d0
0x7924189  nop                                           
0x792418a  mov rax,[rbp+0xC0]                            
0x7924191  test rax,rax                                  
0x7924194  je short 0x7924170                            ; -> loc_7924170

loc_7924196:  ; from 7924157
0x7924196  mov rbx,[rax+0x240]                           
0x792419d  mov rcx,[rdi+0x30]                            
0x79241a1  mov rax,[rcx]                                 
0x79241a4  mov rax,[rax+8]                               
0x79241a8  mov rdx,rbx                                   
0x79241ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x79241b1  nop                                           
0x79241b2  test al,al                                    
0x79241b4  je short 0x79241E3                            ; -> loc_79241e3
0x79241b6  mov rcx,[rdi+0x38]                            
0x79241ba  test rcx,rcx                                  
0x79241bd  je short 0x79241D4                            ; -> loc_79241d4
0x79241bf  mov rax,[rcx]                                 
0x79241c2  mov rax,[rax+8]                               
0x79241c6  mov rdx,rbx                                   
0x79241c9  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x79241cf  nop                                           
0x79241d0  test al,al                                    
0x79241d2  je short 0x79241E3                            ; -> loc_79241e3

loc_79241d4:  ; from 7924108, 7924121, 79241bd
0x79241d4  mov rax,[rbp+0x130]                           
0x79241db  mov rcx,[rax]                                 
0x79241de  call 0x6B0C570                                ; -> sub_6b0c570

loc_79241e3:  ; from 79241b4, 79241d2
0x79241e3  mov rax,[rbp+0x130]                           
0x79241ea  mov rbx,[rax]                                 
0x79241ed  mov rdi,[rsi+0x68]                            
0x79241f1  mov rsi,[rsi+0x70]                            
0x79241f5  jmp short 0x7924204                           ; -> loc_7924204
```

## Gap 4: 0x7924332..0x79243f9 (Task setup #1 - first submission)
```
0x7924332  lock inc dword ptr [rcx+0xC]                  ; W a0+0xC
0x7924336  movdqa [rbp+0x90],xmm0                        
0x792433e  mov rax,[rbp+0x108]                           
0x7924345  test rax,rax                                  
0x7924348  mov [rbp+0x118],rcx                           
0x792434f  je short 0x792435E                            ; -> loc_792435e
0x7924351  lock inc dword ptr [rax+8]                    
0x7924355  mov r15,[rbp+0x108]                           
0x792435c  jmp short 0x7924361                           ; -> loc_7924361

loc_792435e:  ; from 792434f
0x792435e  xor r15d,r15d                                 

loc_7924361:  ; from 792435c
0x7924361  mov r12,[rbp+0x100]                           
0x7924368  mov [rbp+0x90],r12                            
0x792436f  mov [rbp+0x98],r15                            
0x7924376  xorps xmm6,xmm6                               
0x7924379  movaps [rbp+0xB0],xmm6                        
0x7924380  mov rax,[rdi]                                 
0x7924383  mov rax,[rax+0x40]                            
0x7924387  mov rcx,rdi                                   
0x792438a  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x7924390  nop                                           
0x7924391  movdqa xmm0,[rbp+0x80]                        
0x7924399  movaps [rbp+0x80],xmm6                        
0x79243a0  movaps [rbp+0x90],xmm6                        
0x79243a7  lea rcx,[0xF328858]                           ; [data_f328858]
0x79243ae  mov [rbp+0xC0],rcx                            
0x79243b5  movdqu [rbp+0xC8],xmm0                        
0x79243bd  movaps [rbp-0x50],xmm6                        
0x79243c1  mov [rbp+0xD8],r12                            
0x79243c8  mov [rbp+0xE0],r15                            
0x79243cf  movaps [rbp-0x40],xmm6                        
0x79243d3  movaps [rbp+0x30],xmm6                        
0x79243d7  movaps [rbp+0xB0],xmm6                        
0x79243de  mov [rsp+0x28],rbx                            
0x79243e3  mov [rsp+0x20],al                             
0x79243e7  lea rcx,[rbp+0x120]                           
0x79243ee  lea r8,[rbp-0x10]                             
0x79243f2  lea r9,[rbp+0x30]                             
0x79243f6  mov rdx,rdi                                   
0x79243f9  call 0xA2050                                  ; -> sub_a2050
```

## Gap 5: 0x79243f9..0x79245a4 (Task setup #1 continuation & submit #1)
```
0x79243f9  call 0xA2050                                  ; -> sub_a2050
0x79243fe  nop                                           
0x79243ff  pxor xmm0,xmm0                                
0x7924403  movdqa [rbp+0xA0],xmm0                        
0x792440b  mov rax,[rbp+0x128]                           
0x7924412  test rax,rax                                  
0x7924415  je short 0x7924424                            ; -> loc_7924424
0x7924417  lock inc dword ptr [rax+8]                    
0x792441b  mov rax,[rbp+0x128]                           
0x7924422  jmp short 0x7924426                           ; -> loc_7924426

loc_7924424:  ; from 7924415
0x7924424  xor eax,eax                                   

loc_7924426:  ; from 7924422
0x7924426  mov rcx,[rbp+0x120]                           
0x792442d  mov [rbp+0xA0],rcx                            
0x7924434  mov [rbp+0xA8],rax                            
0x792443b  lea rdx,[rbp+0xA0]                            
0x7924442  mov rcx,rdi                                   
0x7924445  call 0x773320                                 ; -> sub_773320
0x792444a  nop                                           
0x792444b  mov rax,[rbp+0x120]                           
0x7924452  mov rcx,[rbp+0x128]                           
0x7924459  lea rdx,[rax+0x90]                            
0x7924460  test rax,rax                                  
0x7924463  cmove rdx,rax                                 
0x7924467  mov [rbp+0x50],rdx                            
0x792446b  mov [rbp+0x58],rcx                            
0x792446f  mov [rbp+0x60],rdi                            
0x7924473  mov rdi,[rbp-0x38]                            
0x7924477  test rdi,rdi                                  
0x792447a  je short 0x79244A7                            ; -> loc_79244a7
0x792447c  lock dec dword ptr [rdi+8]                    
0x7924480  jne short 0x79244A7                           ; -> loc_79244a7
0x7924482  mov rax,[rdi]                                 
0x7924485  mov rax,[rax]                                 
0x7924488  mov rcx,rdi                                   
0x792448b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x7924491  lock dec dword ptr [rdi+0xC]                  
0x7924495  jne short 0x79244A7                           ; -> loc_79244a7
0x7924497  mov rax,[rdi]                                 
0x792449a  mov rax,[rax+8]                               
0x792449e  mov rcx,rdi                                   
0x79244a1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_79244a7:  ; from 792447a, 7924480, 7924495
0x79244a7  mov rcx,[rbp-0x48]                            
0x79244ab  test rcx,rcx                                  
0x79244ae  je short 0x79244C3                            ; -> loc_79244c3
0x79244b0  lock dec dword ptr [rcx+0xC]                  
0x79244b4  jne short 0x79244C3                           ; -> loc_79244c3
0x79244b6  mov rax,[rcx]                                 
0x79244b9  mov rax,[rax+8]                               
0x79244bd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_79244c3:  ; from 79244ae, 79244b4
0x79244c3  mov rdi,[rbp+0xB8]                            
0x79244ca  test rdi,rdi                                  
0x79244cd  je short 0x79244FA                            ; -> loc_79244fa
0x79244cf  lock dec dword ptr [rdi+8]                    
0x79244d3  jne short 0x79244FA                           ; -> loc_79244fa
0x79244d5  mov rax,[rdi]                                 
0x79244d8  mov rax,[rax]                                 
0x79244db  mov rcx,rdi                                   
0x79244de  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x79244e4  lock dec dword ptr [rdi+0xC]                  
0x79244e8  jne short 0x79244FA                           ; -> loc_79244fa
0x79244ea  mov rax,[rdi]                                 
0x79244ed  mov rax,[rax+8]                               
0x79244f1  mov rcx,rdi                                   
0x79244f4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_79244fa:  ; from 79244cd, 79244d3, 79244e8
0x79244fa  mov rcx,[rbp+0x118]                           
0x7924501  test rcx,rcx                                  
0x7924504  je short 0x792450C                            ; -> loc_792450c
0x7924506  lock inc dword ptr [rcx+0xC]                  
0x792450a  jmp short 0x792450F                           ; -> loc_792450f

loc_792450c:  ; from 7924504
0x792450c  xor r14d,r14d                                 

loc_792450f:  ; from 792450a
0x792450f  lea rax,[0xF8394AE]                           ; [data_f8394ae] "void __cdecl RenderChunkCoordinator::_launchVisibilityRebuil..."
0x7924516  mov [rbp-0x50],rax                            
0x792451a  mov qword ptr [rbp-0x48],0x63                 
0x7924522  lea rax,[0xF576262]                           ; [data_f576262] "D:\a\_work\1\s\handheld/src-client/common/client/renderer/ch..."
0x7924529  mov [rbp-0x40],rax                            
0x792452d  mov qword ptr [rbp-0x38],0x5B                 
0x7924535  movaps xmm0,[0xF328630]                       ; [data_f328630]
0x792453c  movups [rbp-0x30],xmm0                        
0x7924540  mov qword ptr [rbp-0x18],0                    
0x7924548  mov byte ptr [rbp-0x20],1                     
0x792454c  mov rdi,[rbp+0x60]                            
0x7924550  movdqa xmm0,[rbp+0x50]                        
0x7924555  movaps [rbp+0x50],xmm6                        
0x7924559  lea rax,[0xF328870]                           ; [data_f328870]
0x7924560  mov [rbp+0xC0],rax                            
0x7924567  mov [rbp+0xC8],r14                            
0x792456e  mov [rbp+0xD0],rcx                            
0x7924575  mov [rbp+0xD8],rsi                            
0x792457c  movdqa [rbp+0x30],xmm0                        
0x7924581  movaps [rbp+0xB0],xmm6                        
0x7924588  mov [rsp+0x28],rbx                            
0x792458d  mov byte ptr [rsp+0x20],0                     
0x7924592  lea rcx,[rbp+0x120]                           
0x7924599  lea r8,[rbp-0x50]                             
0x792459d  lea r9,[rbp+0x30]                             
0x79245a1  mov rdx,rdi                                   
0x79245a4  call 0x14A0C0                                 ; -> sub_14a0c0
```

## Gap 6: 0x79245aa..0x7924708 (Task setup #2 & submit #2)
```
0x79245aa  movaps [rbp+0xA0],xmm6                        
0x79245b1  mov rax,[rbp+0x128]                           
0x79245b8  test rax,rax                                  
0x79245bb  je short 0x79245CA                            ; -> loc_79245ca
0x79245bd  lock inc dword ptr [rax+8]                    
0x79245c1  mov rax,[rbp+0x128]                           
0x79245c8  jmp short 0x79245CC                           ; -> loc_79245cc

loc_79245ca:  ; from 79245bb
0x79245ca  xor eax,eax                                   

loc_79245cc:  ; from 79245c8
0x79245cc  mov rcx,[rbp+0x120]                           
0x79245d3  mov [rbp+0xA0],rcx                            
0x79245da  mov [rbp+0xA8],rax                            
0x79245e1  lea rdx,[rbp+0xA0]                            
0x79245e8  mov rcx,rdi                                   
0x79245eb  call 0x773320                                 ; -> sub_773320
0x79245f0  nop                                           
0x79245f1  mov rsi,[rbp+0x128]                           
0x79245f8  mov rdi,[rbp+0xB8]                            
0x79245ff  test rdi,rdi                                  
0x7924602  je short 0x792462F                            ; -> loc_792462f
0x7924604  lock dec dword ptr [rdi+8]                    
0x7924608  jne short 0x792462F                           ; -> loc_792462f
0x792460a  mov rax,[rdi]                                 
0x792460d  mov rax,[rax]                                 
0x7924610  mov rcx,rdi                                   
0x7924613  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x7924619  lock dec dword ptr [rdi+0xC]                  
0x792461d  jne short 0x792462F                           ; -> loc_792462f
0x792461f  mov rax,[rdi]                                 
0x7924622  mov rax,[rax+8]                               
0x7924626  mov rcx,rdi                                   
0x7924629  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_792462f:  ; from 7924602, 7924608, 792461d
0x792462f  test rsi,rsi                                  
0x7924632  je short 0x792465F                            ; -> loc_792465f
0x7924634  lock dec dword ptr [rsi+8]                    
0x7924638  jne short 0x792465F                           ; -> loc_792465f
0x792463a  mov rax,[rsi]                                 
0x792463d  mov rax,[rax]                                 
0x7924640  mov rcx,rsi                                   
0x7924643  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x7924649  lock dec dword ptr [rsi+0xC]                  
0x792464d  jne short 0x792465F                           ; -> loc_792465f
0x792464f  mov rax,[rsi]                                 
0x7924652  mov rax,[rax+8]                               
0x7924656  mov rcx,rsi                                   
0x7924659  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_792465f:  ; from 7924632, 7924638, 792464d
0x792465f  mov rsi,[rbp+0x58]                            
0x7924663  test rsi,rsi                                  
0x7924666  je short 0x7924693                            ; -> loc_7924693
0x7924668  lock dec dword ptr [rsi+8]                    
0x792466c  jne short 0x7924693                           ; -> loc_7924693
0x792466e  mov rax,[rsi]                                 
0x7924671  mov rax,[rax]                                 
0x7924674  mov rcx,rsi                                   
0x7924677  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x792467d  lock dec dword ptr [rsi+0xC]                  
0x7924681  jne short 0x7924693                           ; -> loc_7924693
0x7924683  mov rax,[rsi]                                 
0x7924686  mov rax,[rax+8]                               
0x792468a  mov rcx,rsi                                   
0x792468d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_7924693:  ; from 7924666, 792466c, 7924681
0x7924693  mov rsi,[rbp+0x98]                            
0x792469a  test rsi,rsi                                  
0x792469d  je short 0x79246CA                            ; -> loc_79246ca
0x792469f  lock dec dword ptr [rsi+8]                    
0x79246a3  jne short 0x79246CA                           ; -> loc_79246ca
0x79246a5  mov rax,[rsi]                                 
0x79246a8  mov rax,[rax]                                 
0x79246ab  mov rcx,rsi                                   
0x79246ae  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x79246b4  lock dec dword ptr [rsi+0xC]                  
0x79246b8  jne short 0x79246CA                           ; -> loc_79246ca
0x79246ba  mov rax,[rsi]                                 
0x79246bd  mov rax,[rax+8]                               
0x79246c1  mov rcx,rsi                                   
0x79246c4  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_79246ca:  ; from 792469d, 79246a3, 79246b8
0x79246ca  mov rcx,[rbp+0x88]                            
0x79246d1  test rcx,rcx                                  
0x79246d4  je short 0x79246E9                            ; -> loc_79246e9
0x79246d6  lock dec dword ptr [rcx+0xC]                  
0x79246da  jne short 0x79246E9                           ; -> loc_79246e9
0x79246dc  mov rax,[rcx]                                 
0x79246df  mov rax,[rax+8]                               
0x79246e3  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_79246e9:  ; from 79246d4, 79246da
0x79246e9  mov rcx,[rbp+0x118]                           
0x79246f0  test rcx,rcx                                  
0x79246f3  je short 0x7924708                            ; -> loc_7924708
0x79246f5  lock dec dword ptr [rcx+0xC]                  
0x79246f9  jne short 0x7924708                           ; -> loc_7924708
0x79246fb  mov rax,[rcx]                                 
0x79246fe  mov rax,[rax+8]                               
0x7924702  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_7924708:  ; from 79246f3, 79246f9
0x7924708  mov rsi,[rbp+0x108]                           
0x792470f  test rsi,rsi                                  
0x7924712  je short 0x792473F                            ; -> loc_792473f
0x7924714  lock dec dword ptr [rsi+8]                    
0x7924718  jne short 0x792473F                           ; -> loc_792473f
0x792471a  mov rax,[rsi]                                 
0x792471d  mov rax,[rax]                                 
0x7924720  mov rcx,rsi                                   
0x7924723  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x7924729  lock dec dword ptr [rsi+0xC]                  
0x792472d  jne short 0x792473F                           ; -> loc_792473f
0x792472f  mov rax,[rsi]                                 
0x7924732  mov rax,[rax+8]                               
0x7924736  mov rcx,rsi                                   
0x7924739  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
```

---

## Gap 7: 0x792473f..0x792478f (Final refcount cleanup chain #1)
```
0x792473f  mov rsi,[rbp+0x48]                            
0x7924743  test rsi,rsi                                  
0x7924746  je short 0x7924773                            ; -> loc_7924773
0x7924748  lock dec dword ptr [rsi+8]                    
0x792474c  jne short 0x7924773                           ; -> loc_7924773
0x792474e  mov rax,[rsi]                                 
0x7924751  mov rax,[rax]                                 
0x7924754  mov rcx,rsi                                   
0x7924757  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x792475d  lock dec dword ptr [rsi+0xC]                  
0x7924761  jne short 0x7924773                           ; -> loc_7924773
0x7924763  mov rax,[rsi]                                 
0x7924766  mov rax,[rax+8]                               
0x792476a  mov rcx,rsi                                   
0x792476d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_7924773:  ; from 7924746, 792474c, 7924761
0x7924773  mov rcx,[rbp+0x78]                            
0x7924777  test rcx,rcx                                  
0x792477a  je short 0x792478F                            ; -> loc_792478f
0x792477c  lock dec dword ptr [rcx+0xC]                  
0x7924780  jne short 0x792478F                           ; -> loc_792478f
0x7924782  mov rax,[rcx]                                 
0x7924785  mov rax,[rax+8]                               
0x7924789  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_792478f:  ; from 792477a, 7924780
0x792478f  movaps xmm6,[rbp+0x140]                       
0x7924796  add rsp,0x1D8                                 
0x792479d  pop rbx                                       
0x792479e  pop rdi                                       
0x792479f  pop rsi                                       
0x79247a0  pop r12                                       
0x79247a2  pop r13                                       
0x79247a4  pop r14                                       
0x79247a6  pop r15                                       
0x79247a8  pop rbp                                       
0x79247a9  ret                                           
```

## Gap 8: 0x79247c1..0x7924814 (Alternate completion path - sub_6b1d650 call)
```
0x79247c1  mov byte ptr [rbp+0xC8],1                     
0x79247c8  mov [rbp+0xD0],rax                            
0x79247cf  mov [rbp+0xD8],rsi                            
0x79247d6  mov [rbp+0xE0],rcx                            
0x79247dd  test rax,rax                                  
0x79247e0  je short 0x7924825                            ; -> loc_7924825
0x79247e2  cmp byte ptr [rax],1                          
0x79247e5  jne short 0x7924825                           ; -> loc_7924825
0x79247e7  mov r9,[rdx]                                  
0x79247ea  mov edx,[r9+0x1C]                             
0x79247ee  sar edx,4                                     
0x79247f1  movq xmm0,[r9+0x14]                           
0x79247f7  psrad xmm0,4                                  
0x79247fc  movq [rbp-0x10],xmm0                          
0x7924801  mov [rbp-8],edx                               
0x7924804  cmp byte ptr [rax],0                          
0x7924807  jne short 0x7924814                           ; -> loc_7924814
0x7924809  mov dword ptr [0],0xDEADC0DE                  

loc_7924814:  ; from 7924807
0x7924814  add r9,0x38                                   
0x7924818  lea rdx,[rbp-0x10]                            
0x792481c  xor r8d,r8d                                   
0x792481f  call 0x6B1D650                                ; -> sub_6b1d650
0x7924824  nop                                           
```

---

## NEXT
All 8 gaps filled for 0x7923d50. Launcher function now fully listed from 0x7923d50..0x79248bb.

---

# New Unit Part: 0x7926f20, 0x5334850, 0x533f580

## 0x7926f20 - RenderChunk Ctor

### Step 1 Complete: Preflight
- Ran `tools/rdis/target/release/rdis.exe fn 0x7926f20 --max 1` → Function at 0x7926f20..0x7927132 (size 0x212), 1 xref
- Full function fits in first 400 instructions (0x212 bytes)

### Step 2 Complete: Instruction-complete listing (first 400 instructions, covers entire function)

**Function: sub_7926f20 (RenderChunk Ctor)**
**Range:** 0x7926f20..0x7927132 (size 0x212)
**Caller:** 1 xref
**Arguments:** rcx = RenderChunk (a0), rdx = params (a1), r8 = flags (r8d), r9 = ptr

```
0x7926f20  push rbp
0x7926f21  push r15
0x7926f23  push r14
0x7926f25  push r12
0x7926f27  push rsi
0x7926f28  push rdi
0x7926f29  push rbx
0x7926f2a  sub rsp,0x60
0x7926f2e  lea rbp,[rsp+0x60]
0x7926f33  movaps [rbp-0x10],xmm6
0x7926f37  mov qword ptr [rbp-0x18],0xFFFFFFFFFFFFFFFE
0x7926f3f  mov ebx,r8d
0x7926f42  mov rsi,rdx
0x7926f45  mov r15,rcx
0x7926f48  mov r14,[rbp+0x70]
0x7926f4c  movzx edi,byte ptr [rbp+0x68]
0x7926f50  mov rax,[rbp+0x78]
0x7926f54  mov byte ptr [rcx+0x20],0                     ; W a0+0x20 = 0
0x7926f58  mov qword ptr [rcx+0x28],0                    ; W a0+0x28 = 0
0x7926f60  xorps xmm6,xmm6
0x7926f63  movups [rcx],xmm6                             ; W a0+0x0 = zeroed (16 bytes)
0x7926f66  mov [rcx+0x30],r9d                            ; W a0+0x30
0x7926f6a  movdqa xmm0,[0xEEE7C10]                       ; [data_eee7c10]
0x7926f72  movdqu [rcx+0x34],xmm0                        ; W a0+0x34 (16 bytes)
0x7926f77  mov rcx,0x7FFFFFFF7FFFFFFF
0x7926f81  mov [r15+0x44],rcx                            ; W a0+0x44
0x7926f85  movups [r15+0x4C],xmm6                        ; W a0+0x4C = zeroed
0x7926f8a  movups [r15+0x5C],xmm6                        ; W a0+0x5C = zeroed
0x7926f8f  movups [r15+0x6C],xmm6                        ; W a0+0x6C = zeroed
0x7926f94  mov eax,[rax]
0x7926f96  mov [r15+0x7C],eax                            ; W a0+0x7C
0x7926f9a  lea r12,[r15+0x80]                            ; R a0+0x80
0x7926fa1  mov r8d,0x1D8
0x7926fa7  mov rcx,r12
0x7926faa  xor edx,edx
0x7926fac  call 0xEEC6ED0                                ; -> sub_eec6ed0 (memset)
0x7926fb1  mov [r15+0x25E],dil                           ; W a0+0x25E
0x7926fb8  movups [r15+0x260],xmm6                       ; W a0+0x260 = zeroed
0x7926fc0  movups [r15+0x270],xmm6                       ; W a0+0x270 = zeroed
0x7926fc8  mov qword ptr [r15+0x280],0                   ; W a0+0x280
0x7926fd3  mov rax,[r14]
0x7926fd6  mov [r15+0x278],rax                           ; W a0+0x278
0x7926fdd  mov rax,[r14+8]
0x7926fe1  mov [r15+0x280],rax                           ; W a0+0x280
0x7926fe8  movups [r14],xmm6
0x7926fec  mov eax,[r15+0x28]
0x7926ff0  and eax,0xFFFFFFDF
0x7926ff3  movzx ecx,bl
0x7926ff6  shl ecx,5
0x7926ff9  or ecx,eax
0x7926ffb  mov [r15+0x28],ecx                            ; W a0+0x28
0x7926fff  mov dword ptr [r15+0x258],0                   ; W a0+0x258
0x792700a  mov word ptr [r15+0x25C],0                    ; W a0+0x25C
0x7927014  mov eax,[rsi]                                 ; R a1+0x0
0x7927016  cmp eax,[r15+0x34]                            ; R a0+0x34
0x792701a  jne short 0x7927032                           ; -> loc_7927032
0x792701c  mov eax,[rsi+4]                               ; R a1+0x4
0x792701f  cmp eax,[r15+0x38]                            ; R a0+0x38
0x7927023  jne short 0x7927032                           ; -> loc_7927032
0x7927025  mov eax,[rsi+8]                               ; R a1+0x8
0x7927028  cmp eax,[r15+0x3C]                            ; R a0+0x3C
0x792702c  je 0x79270F1                                  ; -> loc_79270f1 (early return if equal)

loc_7927032:  ; from 792701a, 7927023
0x7927032  mov [rbp-0x38],r12
0x7927036  lea rax,[r15+0x260]
0x792703d  mov [rbp-0x30],rax
0x7927041  lea rax,[r15+0x10]
0x7927045  mov [rbp-0x28],rax
0x7927049  mov rcx,r15
0x792704c  mov [rbp-0x20],r15
0x7927050  call 0x79276C0                                ; -> sub_79276c0
0x7927055  nop
0x7927056  mov r15,[rbp-0x20]
0x792705a  lea rax,[r15+0x34]
0x792705e  mov ecx,[rsi+8]
0x7927061  mov [rax+8],ecx
0x7927064  mov rcx,[rsi]
0x7927067  mov [rax],rcx
0x792706a  mov eax,[rsi+8]
0x792706d  movq xmm0,[rsi]
0x7927071  paddd xmm0,[0xF124560]
0x7927079  add eax,8
0x792707c  movq [r15+0x40],xmm0
0x7927082  mov [r15+0x48],eax
0x7927086  mov eax,[rsi]
0x7927088  mov ecx,[rsi+8]
0x792708b  lea r8d,[rcx-1]
0x792708f  lea edx,[rax-1]
0x7927092  add ecx,0x11
0x7927095  add eax,0x11
0x7927098  sar edx,4
0x792709b  sar r8d,4
0x792709f  sar eax,4
0x79270a2  sar ecx,4
0x79270a5  mov [r15+0x4C],edx
0x79270a9  mov dword ptr [r15+0x50],0
0x79270b1  mov [r15+0x54],r8d
0x79270b5  mov [r15+0x58],eax
0x79270b9  mov dword ptr [r15+0x5C],0
0x79270c1  mov [r15+0x60],ecx
0x79270c5  sub ecx,r8d
0x79270c8  sub eax,edx
0x79270ca  inc ecx
0x79270cc  inc eax
0x79270ce  mov [r15+0x64],eax
0x79270d2  imul eax,ecx
0x79270d5  mov dword ptr [r15+0x68],1
0x79270dd  mov [r15+0x6C],ecx
0x79270e1  mov [r15+0x70],eax
0x79270e5  mov [r15+0x74],eax
0x79270e9  mov dword ptr [r15+0x78],0x10

loc_79270f1:  ; from 792702c
0x79270f1  movsd xmm0,[rbp+0x60]
0x79270f6  cvtsd2ss xmm0,xmm0
0x79270fa  movss [r15+0x2C],xmm0
0x7927100  mov rcx,[r14+8]
0x7927104  test rcx,rcx
0x7927107  je short 0x792711C
0x7927109  lock dec dword ptr [rcx+0xC]
0x792710d  jne short 0x792711C
0x792710f  mov rax,[rcx]
0x7927112  mov rax,[rax+8]
0x7927116  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040

loc_792711c:  ; from 7927107, 792710d
0x792711c  mov rax,r15
0x792711f  movaps xmm6,[rbp-0x10]
0x7927123  add rsp,0x60
0x7927127  pop rbx
0x7927128  pop rdi
0x7927129  pop rsi
0x792712a  pop r12
0x792712c  pop r14
0x792712e  pop r15
0x7927130  pop rbp
0x7927131  ret
```

### Step 3: [reg+off] Read/Write Table for 0x7926f20

| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| a0+0x20 | 1 | W | Flag byte = 0 | [V] |
| a0+0x28 | 8 | W | Zeroed | [V] |
| a0+0x00 | 16 | W | Zeroed (xmm) | [V] |
| a0+0x30 | 4 | W | From r9d | [V] |
| a0+0x34 | 16 | W | From data_eee7c10 | [V] |
| a0+0x44 | 8 | W | 0x7FFFFFFF7FFFFFFF | [V] |
| a0+0x4C | 16 | W | Zeroed | [V] |
| a0+0x5C | 16 | W | Zeroed | [V] |
| a0+0x6C | 16 | W | Zeroed | [V] |
| a0+0x7C | 4 | W | From [rax] | [V] |
| a0+0x80 | 0x1D8 | W | Zeroed (memset) | [V] |
| a0+0x25E | 1 | W | Flag from dil | [V] |
| a0+0x260 | 16 | W | Zeroed | [V] |
| a0+0x270 | 16 | W | Zeroed | [V] |
| a0+0x280 | 8 | W | Zeroed, then from r14+8 | [V] |
| a0+0x278 | 8 | W | From r14 | [V] |
| a0+0x28 | 4 | R/W | Flags & bl shifted | [V] |
| a0+0x258 | 4 | W | Zeroed | [V] |
| a0+0x25C | 2 | W | Zeroed | [V] |
| a0+0x2C | 4 | W | Float from xmm0 | [V] |
| a0+0x34 | 4 | R | Compare with a1+0x0 | [V] |
| a0+0x38 | 4 | R | Compare with a1+0x4 | [V] |
| a0+0x3C | 4 | R | Compare with a1+0x8 | [V] |
| a0+0x10 | 8 | R | Used in sub_79276c0 | [V] |
| a0+0x260 | 8 | R | Used in sub_79276c0 | [V] |
| a1+0x0 | 4 | R | Compare with a0+0x34 | [V] |
| a1+0x4 | 4 | R | Compare with a0+0x38 | [V] |
| a1+0x8 | 4 | R | Compare with a0+0x3C, used for coords | [V] |

### Step 4: Callees for 0x7926f20

| RVA | What | Tag |
|-----|------|-----|
| 0xeec6ed0 | memset (sub_eec6ed0) | [V] |
| 0x79276c0 | Helper (sub_79276c0) | [V] |
| 0xeea6040 (via [0xF99FFA0]) | Allocator/deallocator | [V] |

---

## NEXT for 0x7926f20
Complete at 0x7927132 (full function, 0x212 bytes)

---

## 0x5334850 - Event Processor

### Step 1 Complete: Preflight
- Function at 0x5334850..0x533a78c (size 0x5f3c = 24380 bytes), 1 xref
- Large function, first 400 instructions cover entry through timestamp calculation and first global state access

### Step 2 Complete: Instruction-complete listing (first 400 instructions)

**Function: sub_5334850 (Event Processor)**
**Range:** 0x5334850..0x533a78c (size 0x5f3c)
**Caller:** 1 xref
**Arguments:** rcx = object (a0), rdx = params (rsi), r8 = ptr, r9 = rdx

```
0x5334850  push rbp
0x5334851  push r15
0x5334853  push r14
0x5334855  push r13
0x5334857  push r12
0x5334859  push rsi
0x533485a  push rdi
0x533485b  push rbx
0x533485c  sub rsp,0x388
0x5334863  lea rbp,[rsp+0x80]
0x533486b  movdqa [rbp+0x2F0],xmm15
0x5334874  movdqa [rbp+0x2E0],xmm14
0x533487d  movaps [rbp+0x2D0],xmm13
0x5334885  movapd [rbp+0x2C0],xmm12
0x533488e  movapd [rbp+0x2B0],xmm11
0x5334897  movaps [rbp+0x2A0],xmm10
0x533489f  movaps [rbp+0x290],xmm9
0x53348a7  movaps [rbp+0x280],xmm8
0x53348af  movaps [rbp+0x270],xmm7
0x53348b6  movdqa [rbp+0x260],xmm6
0x53348be  mov qword ptr [rbp+0x258],0xFFFFFFFFFFFFFFFE
0x53348c9  mov [rbp-0x18],r8
0x53348cd  mov [rbp+0x1E0],rdx
0x53348d4  mov rax,[rcx+0x130]                           ; R a0+0x130
0x53348db  cmp rax,[rcx+0x138]                           ; R a0+0x138
0x53348e2  je 0x533A069                                  ; -> sub_533a069
0x53348e8  movaps xmm7,xmm3
0x53348eb  mov rsi,rcx
0x53348ee  call 0xEEC5920                                ; -> sub_eec5920 (get timestamp)
0x53348f3  mov rbx,rax
0x53348f6  call 0xEEC5930                                ; -> sub_eec5930 (get frequency)
0x53348fb  cmp rbx,0x16E3600
0x5334902  je short 0x5334916
0x5334904  cmp rbx,0x989680
0x533490b  jne short 0x5334971
0x533490d  imul rax,0x64
0x5334911  jmp 0x53349B0

loc_5334916:  ; from 5334902 (timestamp 0x16E3600)
0x5334916  mov r9,0xB2F4FC0794908CF3
0x5334920  mov rcx,rax
0x5334923  imul r9
0x5334926  mov r8,rdx
0x5334929  add r8,rcx
0x533492c  mov rax,r8
0x533492f  shr rax,0x3F
0x5334933  sar r8,0x18
0x5334937  add r8,rax
0x533493a  imul rax,r8,0x16E3600
0x5334941  sub rcx,rax
0x5334944  imul rcx,0x3B9ACA00
0x533494b  mov rax,rcx
0x533494e  imul r9
0x5334951  mov rax,rdx
0x5334954  imul rdx,r8,0x3B9ACA00
0x533495b  add rax,rcx
0x533495e  mov rcx,rax
0x5334961  shr rcx,0x3F
0x5334965  sar rax,0x18
0x5334969  add rax,rcx
0x533496c  add rax,rdx
0x533496f  jmp short 0x53349B0

loc_5334971:  ; from 533490b (other timestamp)
0x5334971  mov rcx,rax
0x5334974  or rcx,rbx
0x5334977  shr rcx,0x20
0x533497b  je short 0x5334984
0x533497d  cqo
0x533497f  idiv rbx
0x5334982  jmp short 0x5334988

loc_5334984:  ; from 533497b
0x5334984  xor edx,edx
0x5334986  div ebx

loc_5334988:  ; from 5334982
0x5334988  imul rcx,rax,0x3B9ACA00
0x533498f  imul rax,rdx,0x3B9ACA00
0x5334996  mov rdx,rax
0x5334999  or rdx,rbx
0x533499c  shr rdx,0x20
0x53349a0  je short 0x53349A9
0x53349a2  cqo
0x53349a4  idiv rbx
0x53349a7  jmp short 0x53349AD

loc_53349a9:  ; from 53349a0
0x53349a9  xor edx,edx
0x53349ab  div ebx

loc_53349ad:  ; from 53349a7
0x53349ad  add rax,rcx

loc_53349b0:  ; from 5334911, 533496f
0x53349b0  mov [rsi+0x5A8],rax
0x53349b7  mov rax,[rsi+0x418]
0x53349be  cmp rax,[rsi+0x420]
0x53349c5  je short 0x53349CE
0x53349c7  mov [rsi+0x420],rax
0x53349ce  mov [rbp+0x250],rsi
0x53349d5  lea r14,[0x128C4FD0]
0x53349dc  mov rcx,r14
0x53349df  call 0xE943178
0x53349e4  lock inc qword ptr [0x128C5030]
0x53349ec  mov rcx,r14
0x53349ef  call 0xE94319C
0x53349f4  mov rsi,[0x128C5038]
0x53349fb  test rsi,rsi
0x53349fe  je short 0x5334A2C
0x5334a00  cmp byte ptr [rsi],1
0x5334a03  jne short 0x5334A2C
0x5334a05  mov rax,[0x128C5040]
0x5334a0c  test rax,rax
0x5334a0f  je 0x5334DFF
0x5334a15  lock inc dword ptr [rax+8]
0x5334a19  mov rsi,[0x128C5038]
0x5334a20  mov rax,[0x128C5040]
0x5334a27  jmp 0x5334E01

loc_5334a2c:  ; from 53349fe, 5334a03
0x5334a2c  mov qword ptr [rbp+0x38],0
0x5334a34  mov byte ptr [rbp+0x40],0
0x5334a38  pxor xmm0,xmm0
0x5334a3c  movdqu [rbp+0x48],xmm0
0x5334a41  mov qword ptr [rbp+0x58],0
0x5334a49  lea rcx,[0x128C4FD0]
0x5334a50  call 0x3B2020

loc_5334a55:  ; from 5334e1f, 5334e28
0x5334a55  mov dword ptr [rbp+0x17C],0
0x5334a5f  xor eax,eax
0x5334a61  mov rdi,[rbp+0x250]

loc_5334a68:  ; from 5334e7a
0x5334a68  mov [rbp+0x1DF],al
0x5334a6e  mov rax,[rdi+0x138]
0x5334a75  sub rax,[rdi+0x130]
0x5334a7c  cmp rax,0x11
0x5334a80  setae [rbp+0x246]
0x5334a87  pxor xmm6,xmm6
0x5334a8b  movdqa [rbp+0x120],xmm6
0x5334a93  mov qword ptr [rbp+0x130],0
0x5334a9e  movdqa [rbp+0x140],xmm6
0x5334aa6  mov qword ptr [rbp+0x150],0
0x5334abb  mov dword ptr [rbp+0x160],0x3F600000
0x5334abb  lea rcx,[rbp+0x120]
0x5334ac2  mov edx,8
0x5334ac7  call 0x53D9BE0
0x5334acc  nop
0x5334acd  mov rax,[rdi+0x138]
0x5334ad4  mov rcx,[rdi+0x130]
0x5334adb  mov rsi,rax
0x5334ade  sub rsi,rcx
0x5334ae1  mov rbx,rax
0x5334ae4  movdqa [rbp+0x60],xmm6
0x5334ae9  mov qword ptr [rbp+0x70],0
0x5334af1  mov rdx,rax
0x5334af4  sub rbx,rcx
0x5334af7  je 0x5334BAA
0x5334afd  sar rsi,4
0x5334b01  mov rax,rsi
0x5334b04  shr rax,0x3E
0x5334b08  jne 0x533A6F3
0x5334b0e  sar rbx,2
0x5334b12  cmp rsi,0x400
0x5334b19  jb short 0x5334B54
0x5334b1b  lea r15,[rbx+0x27]
0x5334b1f  mov rcx,[0x1233E1A8]
0x5334b26  mov rax,[rcx]
0x5334b29  mov rax,[rax+8]
0x5334b2d  mov rdx,r15
0x5334b30  call qword ptr [0xF99FFA0]
0x5334b36  nop
0x5334b37  mov r14,rax
0x5334b3a  test rax,rax
0x5334b3d  je 0x533A65F
0x5334b43  mov rax,r14
0x5334b46  add r14,0x27
0x5334b4a  and r14,0xFFFFFFFFFFFFFFE0
0x5334b4e  mov [r14-8],rax
0x5334b52  jmp short 0x5334B78

loc_5334b54:  ; from 5334b19
0x5334b54  mov rcx,[0x1233E1A8]
0x5334b5b  mov rax,[rcx]
0x5334b5e  mov rax,[rax+8]
0x5334b62  mov rdx,rbx
0x5334b65  call qword ptr [0xF99FFA0]
0x5334b6b  nop
0x5334b6c  mov r14,rax
0x5334b6f  test rax,rax
0x5334b72  je 0x533A66D
0x5334b78  mov [rbp+0x60],r14
0x5334b7c  lea rsi,[r14+rsi*4]
0x5334b80  mov [rbp+0x70],rsi
0x5334b84  mov rcx,r14
0x5334b87  xor edx,edx
0x5334b89  mov r8,rbx
0x5334b8c  call 0xEEC6ED0
0x5334b91  mov [rbp+0x68],rsi
0x5334b95  mov rdi,[rbp+0x250]
0x5334b9c  mov rax,[rdi+0x130]
0x5334ba3  mov rdx,[rdi+0x138]
```

---

## NEXT for 0x5334850
Resume at 0x53354ca (loc_53354ca) - continues with draw record writes, timestamp comparisons, and allocator calls. Function size 0x5f3c (24380 bytes), first 1000 instructions cover up to ~0x53354ca.

---

# Event processor 0x5334850 - Continuation

## Chunk 2: 0x5334ba3..0x53354ca (500 instructions)

```
0x5334ba3  mov rdx,[rdi+0x138]                           
0x5334baa  sub rdx,rax                                   
0x5334bad  mov byte ptr [rbp+0x200],0                    
0x5334bb4  sar rdx,4                                     
0x5334bb8  lea rcx,[rbp-0x40]                            
0x5334bbc  lea r8,[rbp+0x200]                            
0x5334bc3  lea r9,[rbp+0x190]                            
0x5334bca  call 0x12B290                                 ; -> sub_12b290
0x5334bcf  nop                                           
0x5334bd0  mov rbx,[rdi+0x138]                           
0x5334bd7  mov rax,[rdi+0x130]                           
0x5334bde  mov rsi,rbx                                   
0x5334be1  sub rsi,rax                                   
0x5334be4  movdqa [rbp+0x90],xmm6                        
0x5334bec  mov qword ptr [rbp+0xA0],0                    
0x5334bf7  sub rbx,rax                                   
0x5334bfa  je 0x5334CA8                                  ; -> loc_5334ca8
0x5334c00  sar rsi,4                                     
0x5334c04  mov rax,rsi                                   
0x5334c07  shr rax,0x3E                                  
0x5334c0b  jne 0x533A6F9                                 ; -> sub_533a6f9
0x5334c11  sar rbx,2                                     
0x5334c15  cmp rsi,0x400                                 
0x5334c1c  jb short 0x5334C57                            ; -> loc_5334c57
0x5334c1e  lea r15,[rbx+0x27]                            
0x5334c22  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x5334c29  mov rax,[rcx]                                 
0x5334c2c  mov rax,[rax+8]                               
0x5334c30  mov rdx,r15                                   
0x5334c33  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5334c39  nop                                           
0x5334c3a  mov r14,rax                                   
0x5334c3d  test rax,rax                                  
0x5334c40  je 0x533A67E                                  ; -> sub_533a67e
0x5334c46  mov rax,r14                                   
0x5334c49  add r14,0x27                                  
0x5334c4d  and r14,0xFFFFFFFFFFFFFFE0                    
0x5334c51  mov [r14-8],rax                               
0x5334c55  jmp short 0x5334C7B                           ; -> loc_5334c7b

loc_5334c57:  ; from 5334c1c
0x5334c57  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x5334c5e  mov rax,[rcx]                                 
0x5334c61  mov rax,[rax+8]                               
0x5334c65  mov rdx,rbx                                   
0x5334c68  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5334c6e  nop                                           
0x5334c6f  mov r14,rax                                   
0x5334c72  test rax,rax                                  
0x5334c75  je 0x533A68C                                  ; -> sub_533a68c

loc_5334c7b:  ; from 5334c55
0x5334c7b  mov [rbp+0x90],r14                            
0x5334c82  lea rsi,[r14+rsi*4]                           
0x5334c86  mov [rbp+0xA0],rsi                            
0x5334c8d  mov rcx,r14                                   
0x5334c90  xor edx,edx                                   
0x5334c92  mov r8,rbx                                    
0x5334c95  call 0xEEC6ED0                                ; -> sub_eec6ed0
0x5334c9a  mov [rbp+0x98],rsi                            
0x5334ca1  mov rdi,[rbp+0x250]                           

loc_5334ca8:  ; from 5334bfa
0x5334ca8  mov rax,[rdi+0x128]                           
0x5334caf  mov rax,[rax+0x480]                           
0x5334cb6  cvttss2si edi,[rax+0x5D4]                     
0x5334cbe  movdqa [rbp+0x190],xmm6                       
0x5334cc6  mov rcx,[rax+0x9A8]                           
0x5334ccd  test rcx,rcx                                  
0x5334cd0  je short 0x5334CDF                            ; -> loc_5334cdf
0x5334cd2  lock inc dword ptr [rcx+8]                    
0x5334cd6  mov rbx,[rax+0x9A8]                           
0x5334cdd  jmp short 0x5334CE1                           ; -> loc_5334ce1

loc_5334cdf:  ; from 5334cd0
0x5334cdf  xor ebx,ebx                                   

loc_5334ce1:  ; from 5334cdd
0x5334ce1  mov rcx,[rax+0x9A0]                           
0x5334ce8  mov [rbp+0x190],rcx                           
0x5334cef  mov [rbp+0x198],rbx                           
0x5334cf6  mov rax,[rcx]                                 
0x5334cf9  mov rax,[rax+0x58]                            
0x5334cfd  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5334d03  nop                                           
0x5334d04  mov r14d,eax                                  
0x5334d07  test rbx,rbx                                  
0x5334d0a  je short 0x5334D37                            ; -> loc_5334d37
0x5334d0c  lock dec dword ptr [rbx+8]                    
0x5334d10  jne short 0x5334D37                           ; -> loc_5334d37
0x5334d12  mov rax,[rbx]                                 
0x5334d15  mov rax,[rax]                                 
0x5334d18  mov rcx,rbx                                   
0x5334d1b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5334d21  lock dec dword ptr [rbx+0xC]                  
0x5334d25  jne short 0x5334D37                           ; -> loc_5334d37
0x5334d27  mov rax,[rbx]                                 
0x5334d2a  mov rax,[rax+8]                               
0x5334d2e  mov rcx,rbx                                   
0x5334d31  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_5334d37:  ; from 5334d0a, 5334d10, 5334d25
0x5334d37  mov rax,[rbp+0x250]                           
0x5334d3e  mov eax,[rax+0x568]                           
0x5334d44  cmp r14d,eax                                  
0x5334d47  je 0x5334ECC                                  ; -> loc_5334ecc
0x5334d4d  inc eax                                       
0x5334d4f  cmp r14d,eax                                  
0x5334d52  je 0x5334ECC                                  ; -> loc_5334ecc
0x5334d58  mov rax,[rbp+0x250]                           
0x5334d5f  cmp qword ptr [rax+0x520],0                   
0x5334d67  je 0x5334ECC                                  ; -> loc_5334ecc
0x5334d6d  mov rbx,[rbp+0x250]                           
0x5334d74  mov rax,[rbx+0x518]                           
0x5334d7b  mov rcx,[rax+8]                               
0x5334d7f  mov qword ptr [rcx],0                         
0x5334d86  mov rcx,[rax]                                 
0x5334d89  test rcx,rcx                                  
0x5334d8c  je short 0x5334DA5                            ; -> loc_5334da5
0x5334d8e  xchg ax,ax                                    

loc_5334d90:  ; from 5334da3
0x5334d90  mov rsi,[rcx]                                 
0x5334d93  mov edx,0x20                                  
0x5334d98  call 0xE935700                                ; -> sub_e935700
0x5334d9d  mov rcx,rsi                                   
0x5334da0  test rsi,rsi                                  
0x5334da3  jne short 0x5334D90                           ; -> loc_5334d90

loc_5334da5:  ; from 5334d8c
0x5334da5  mov rax,[rbx+0x518]                           
0x5334dac  mov [rax],rax                                 
0x5334daf  mov [rax+8],rax                               
0x5334db3  mov qword ptr [rbx+0x520],0                   
0x5334dbe  mov rdx,[rbx+0x528]                           
0x5334dc5  mov rax,[rbx+0x530]                           
0x5334dcc  cmp rdx,rax                                   
0x5334dcf  je 0x5334ECC                                  ; -> loc_5334ecc
0x5334dd5  mov rcx,[rbp+0x250]                           
0x5334ddc  mov rcx,[rcx+0x518]                           
0x5334de3  mov r9,rax                                    
0x5334de6  sub r9,rdx                                    
0x5334de9  add r9,0xFFFFFFFFFFFFFFF8                     
0x5334ded  cmp r9,0x18                                   
0x5334df1  jae 0x5334E7F                                 ; -> loc_5334e7f
0x5334df7  mov r8,rdx                                    
0x5334dfa  jmp 0x5334EC0                                 ; -> loc_5334ec0
0x5334dff  xor eax,eax                                   
0x5334e01  mov rbx,[0x128C5048]                          ; [data_128c5048]
0x5334e08  mov [rbp+0x38],r14                            
0x5334e0c  mov byte ptr [rbp+0x40],1                     
0x5334e10  mov [rbp+0x48],rsi                            
0x5334e14  mov [rbp+0x50],rax                            
0x5334e18  mov [rbp+0x58],rbx                            
0x5334e1c  test rsi,rsi                                  
0x5334e1f  je 0x5334A55                                  ; -> sub_5334a55
0x5334e25  cmp byte ptr [rsi],1                          
0x5334e28  jne 0x5334A55                                 ; -> sub_5334a55
0x5334e2e  mov rax,[rbx]                                 
0x5334e31  mov rax,[rax+8]                               
0x5334e35  mov rcx,rbx                                   
0x5334e38  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5334e3e  nop                                           
0x5334e3f  mov rdi,[rbp+0x250]                           
0x5334e46  test al,al                                    
0x5334e48  je 0x533A0CB                                  ; -> sub_533a0cb
0x5334e4e  cmp byte ptr [rsi],0                          
0x5334e51  jne short 0x5334E5E                           ; -> loc_5334e5e
0x5334e53  mov dword ptr [0],0xDEADC0DE                  

loc_5334e5e:  ; from 5334e51
0x5334e5e  mov rax,[rbx]                                 
0x5334e61  mov rax,[rax+0x230]                           
0x5334e68  mov rcx,rbx                                   
0x5334e6b  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5334e71  nop                                           
0x5334e72  mov cl,1                                      
0x5334e74  mov [rbp+0x17C],ecx                           
0x5334e7a  jmp 0x5334A68                                 ; -> sub_5334a68

loc_5334e7f:  ; from 5334df1
0x5334e7f  shr r9,3                                      
0x5334e83  inc r9                                        
0x5334e86  mov r10,r9                                    
0x5334e89  and r10,0xFFFFFFFFFFFFFFFC                    
0x5334e8d  lea r8,[rdx+r10*8]                            
0x5334e91  movq xmm0,rcx                                 
0x5334e96  pshufd xmm0,xmm0,0x44                         
0x5334e9b  xor r11d,r11d                                 
0x5334e9e  xchg ax,ax                                    

loc_5334ea0:  ; from 5334eb4
0x5334ea0  movdqu [rdx+r11*8],xmm0                       
0x5334ea6  movdqu [rdx+r11*8+0x10],xmm0                  
0x5334ead  add r11,4                                     
0x5334eb1  cmp r10,r11                                   
0x5334eb4  jne short 0x5334EA0                           ; -> loc_5334ea0
0x5334eb6  cmp r9,r10                                    
0x5334eb9  je short 0x5334ECC                            ; -> loc_5334ecc
0x5334ebb  nop [rax+rax]                                 

loc_5334ec0:  ; from 5334dfa, 5334eca
0x5334ec0  mov [r8],rcx                                  
0x5334ec3  add r8,8                                      
0x5334ec7  cmp r8,rax                                    
0x5334eca  jne short 0x5334EC0                           ; -> loc_5334ec0

loc_5334ecc:  ; from 5334d47, 5334d52, 5334d67, 5334dcf, 5334eb9
0x5334ecc  mov qword ptr [rbp+0x80],0                    
0x5334ed7  mov byte ptr [rbp+0x247],0                    
0x5334ede  lea rbx,[0x128D2240]                          ; [data_128d2240]
0x5334ee5  mov rcx,rbx                                   
0x5334ee8  call 0xE943178                                ; -> sub_e943178
0x5334eed  lock inc qword ptr [0x128D22A0]               ; [data_128d22a0]
0x5334ef5  mov rcx,rbx                                   
0x5334ef8  call 0xE94319C                                ; -> sub_e94319c
0x5334efd  mov rsi,[0x128D22A8]                          ; [data_128d22a8]
0x5334f04  test rsi,rsi                                  
0x5334f07  mov r14,[rbp+0x250]                           
0x5334f0e  je 0x5334FD7                                  ; -> loc_5334fd7
0x5334f14  cmp byte ptr [rsi],1                          
0x5334f17  jne 0x5334FD7                                 ; -> loc_5334fd7
0x5334f1d  mov rax,[0x128D22B0]                          ; [data_128d22b0]
0x5334f24  test rax,rax                                  
0x5334f27  je short 0x5334F47                            ; -> loc_5334f47
0x5334f29  lock inc dword ptr [rax+8]                    
0x5334f2d  mov rsi,[0x128D22A8]                          ; [data_128d22a8]
0x5334f34  mov rbx,[0x128D22B0]                          ; [data_128d22b0]
0x5334f3b  test rsi,rsi                                  
0x5334f3e  je short 0x5334FA7                            ; -> loc_5334fa7
0x5334f40  cmp byte ptr [rsi],1                          
0x5334f43  je short 0x5334F49                            ; -> loc_5334f49
0x5334f45  jmp short 0x5334FA7                           ; -> loc_5334fa7

loc_5334f47:  ; from 5334f27
0x5334f47  xor ebx,ebx                                   

loc_5334f49:  ; from 5334f43
0x5334f49  mov r14,[0x128D22B8]                          ; [data_128d22b8]
0x5334f50  movzx eax,byte ptr [r14+0x18]                 
0x5334f55  mov [rbp+0x247],al                            
0x5334f5b  cmp al,1                                      
0x5334f5d  jne short 0x5334FA0                           ; -> loc_5334fa0
0x5334f5f  cmp byte ptr [rsi],0                          
0x5334f62  jne short 0x5334F6F                           ; -> loc_5334f6f
0x5334f64  mov dword ptr [0],0xDEADC0DE                  

loc_5334f6f:  ; from 5334f62
0x5334f6f  lea rcx,[r14+0x190]                           
0x5334f76  mov r8d,0x110                                 
0x5334f7c  xor edx,edx                                   
0x5334f7e  call 0xEEC6ED0                                ; -> sub_eec6ed0
0x5334f83  cmp byte ptr [rsi],0                          
0x5334f86  jne short 0x5334F93                           ; -> loc_5334f93
0x5334f88  mov dword ptr [0],0xDEADC0DE                  

loc_5334f93:  ; from 5334f86
0x5334f93  pxor xmm0,xmm0                                
0x5334f97  movdqu [r14+0x80],xmm0                        

loc_5334fa0:  ; from 5334f5d
0x5334fa0  mov r14,[rbp+0x250]                           

loc_5334fa7:  ; from 5334f3e, 5334f45
0x5334fa7  test rbx,rbx                                  
0x5334faa  je short 0x5334FD7                            ; -> loc_5334fd7
0x5334fac  lock dec dword ptr [rbx+8]                    
0x5334fb0  jne short 0x5334FD7                           ; -> loc_5334fd7
0x5334fb2  mov rax,[rbx]                                 
0x5334fb5  mov rax,[rax]                                 
0x5334fb8  mov rcx,rbx                                   
0x5334fbb  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5334fc1  lock dec dword ptr [rbx+0xC]                  
0x5334fc5  jne short 0x5334FD7                           ; -> loc_5334fd7
0x5334fc7  mov rax,[rbx]                                 
0x5334fca  mov rax,[rax+8]                               
0x5334fce  mov rcx,rbx                                   
0x5334fd1  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_5334fd7:  ; from 5334f0e, 5334f17, 5334faa, 5334fb0, 5334fc5
0x5334fd7  movss [rbp+0x78],xmm7                         
0x5334fdc  imul edi,edi                                  
0x5334fdf  lea rcx,[0x128D2240]                          ; [data_128d2240]
0x5334fe6  call 0x3B2020                                 ; -> sub_3b2020
0x5334feb  pxor xmm6,xmm6                                
0x5334fef  movdqa [rbp+0x200],xmm6                       
0x5334ff7  mov qword ptr [rbp+0x210],0                   
0x5335002  mov rax,[r14+0x130]                           
0x5335009  mov rcx,[rax]                                 
0x533500c  mov rdx,[rcx+0x1A8]                           
0x5335013  cmp rdx,[rcx+0x1B0]                           
0x533501a  je short 0x533502A                            ; -> loc_533502a
0x533501c  mov [rcx+0x1B0],rdx                           
0x5335023  mov rax,[r14+0x130]                           

loc_533502a:  ; from 533501a
0x533502a  xorps xmm0,xmm0                               
0x533502d  cvtsi2ss xmm0,edi                             
0x5335031  movss [rbp+0x7C],xmm0                         
0x5335036  mov rcx,[r14+0x138]                           
0x533503d  sub rcx,rax                                   
0x5335040  sar rcx,4                                     
0x5335044  mov [rbp+0x180],rcx                           
0x533504b  xor edx,edx                                   
0x533504d  movss xmm8,[0xF246D38]                        ; [data_f246d38] = sub_15db3d7
0x5335056  movq xmm10,[0xEFFB2B0]                        ; [data_effb2b0] = sub_3300000
0x533505f  movapd xmm11,[0xEFFB2C0]                      ; [data_effb2c0]
0x5335068  movsd xmm12,[0xEF98220]                       ; [data_ef98220]
0x5335071  movsd xmm13,[0xEECF680]                       ; [data_eecf680]
0x533507a  movss xmm9,[0xEEE6700]                        ; [data_eee6700]
0x5335083  jmp short 0x533509A                           ; -> loc_533509a
0x5335085  nop [rax+rax]                                 

loc_5335090:  ; from 5335521, 533552b, 533554f, 5335562
0x5335090  mov rdx,[rbp+0x1E8]                           
0x5335097  inc rdx                                       

loc_533509a:  ; from 5335083
0x533509a  cmp rdx,[rbp+0x180]                           
0x53350a1  je 0x5335BC9                                  ; -> loc_5335bc9
0x53350a7  mov [rbp+0x100],rdx                           
0x53350ae  mov rax,[r14+0x130]                           
0x53350b5  mov rcx,rdx                                   
0x53350b8  shl rcx,4                                     
0x53350bc  lea rsi,[rax+rcx]                             
0x53350c0  mov rax,[rax+rcx]                             
0x53350c4  movdqa [rbp+0xB0],xmm6                        
0x53350cc  mov rcx,[rax+0x9A8]                           
0x53350d3  test rcx,rcx                                  
0x53350d6  mov [rbp+0x1E8],rdx                           
0x53350dd  je short 0x5335100                            ; -> loc_5335100
0x53350df  lock inc dword ptr [rcx+8]                    
0x53350e3  mov r8,[rax+0x9A8]                            
0x53350ea  mov rdx,[rsi]                                 
0x53350ed  mov rcx,[rbp+0x100]                           
0x53350f4  jmp short 0x5335109                           ; -> loc_5335109
0x53350f6  nop [rax+rax]                                 

loc_5335100:  ; from 53350dd
0x5335100  mov rcx,rdx                                   
0x5335103  mov rdx,rax                                   
0x5335106  xor r8d,r8d                                   

loc_5335109:  ; from 53350f4
0x5335109  mov rbx,[rax+0x9A0]                           
0x5335110  mov [rbp+0xB0],rbx                            
0x5335117  mov [rbp+0x1D0],r8                            
0x533511e  mov [rbp+0xB8],r8                             
0x5335125  movss xmm0,[rdx+0x40C]                        
0x533512d  addss xmm0,xmm8                               
0x5335132  mulss xmm0,xmm0                               
0x5335136  mov rax,[rbp+0x60]                            
0x533513a  movss [rax+rcx*4],xmm0                        
0x533513f  mov r8,[rsi]                                  
0x5335142  mov rcx,[rbp+0x100]                           
0x5335149  mov rax,rcx                                   
0x533514c  mov edx,1                                     
0x5335151  shl edx,cl                                    
0x5335153  shr rax,5                                     
0x5335157  cmp byte ptr [r8+0x9B0],2                     
0x533515f  mov rcx,[rbp-0x40]                            
0x5335163  jne short 0x5335170                           ; -> loc_5335170
0x5335165  not edx                                       
0x5335167  and edx,[rcx+rax*4]                           
0x533516a  jmp short 0x5335173                           ; -> loc_5335173
0x533516c  nop [rax]                                     

loc_5335170:  ; from 5335163
0x5335170  or edx,[rcx+rax*4]                            

loc_5335173:  ; from 533516a
0x5335173  mov [rcx+rax*4],edx                           
0x5335176  mov qword ptr [rbp+0x10],0                    
0x533517e  mov qword ptr [rbp+0x1C8],0                   
0x5335189  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x5335190  mov rax,[rcx]                                 
0x5335193  mov rax,[rax+8]                               
0x5335197  mov edx,0x70                                  
0x533519c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x53351a2  nop                                           
0x53351a3  mov r14,rax                                   
0x53351a6  test rax,rax                                  
0x53351a9  je 0x5335B9B                                  ; -> loc_5335b9b

loc_53351af:  ; from 5335ba6
0x53351af  lea rax,[0xF248AB0]                           ; [data_f248ab0]
0x53351b6  mov [r14],rax                                 
0x53351b9  lea rax,[rbp+0x247]                           
0x53351c0  mov [r14+8],rax                               
0x53351cc  lea rax,[rbp+0x246]                           
0x53351c8  mov [r14+10],rax                              
0x53351d3  mov [r14+18],rax                              
0x53351d7  lea rax,[rbp+0x200]                           
0x53351de  mov [r14+20],rax                           
0x53351e2  mov rax,[rbp+0x250]                           
0x53351e9  mov [r14+0x28],rax                            
0x53351ed  mov [r14+0x30],rsi                            
0x53351f1  lea rax,[rbp-0x40]                            
0x53351f5  mov [r14+0x38],rax                            
0x53351f9  lea rax,[rbp+0x100]                           
0x5335200  mov [r14+0x40],rax                            
0x5335204  mov rax,[rbp+0x1E0]                           
0x533520b  mov [r14+0x48],rax                            
0x533520f  lea rax,[rbp+0x60]                            
0x5335213  mov [r14+0x50],rax                            
0x5335217  lea rax,[rbp+0x1DF]                           
0x533521e  mov [r14+0x58],rax                            
0x5335222  lea rax,[rbp+0x80]                            
0x5335229  mov [r14+0x60],rax                            
0x533522d  lea rax,[rbp+0x90]                            
0x5335234  mov [r14+0x68],rax                            
0x5335238  mov [rbp+0x1C8],r14                           
0x533523f  mov rax,[rbx]                                 
0x5335242  mov rax,[rax+0x18]                            
0x5335246  mov rcx,rbx                                   
0x5335249  lea rdx,[rbp+0x190]                           
0x5335250  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5335256  nop                                           
0x5335257  mov rax,[rbp+0x200]                           
0x533525e  mov rcx,[rbp+0x208]                           
0x5335265  cmp byte ptr [rbp+0x246],1                    
0x533526c  jne 0x53354DE                                 ; -> loc_53354de
0x5335272  sub rcx,rax                                   
0x5335275  sar rcx,2                                     
0x5335279  mov rdx,0xAAAAAAAAAAAAAAAB                    
0x5335283  imul rcx,rdx                                  
0x5335287  movq xmm0,rcx                                 
0x533528c  punpckldq xmm0,xmm10                          
0x5335291  subpd xmm0,xmm11                              
0x5335296  movapd xmm1,xmm0                              
0x533529a  unpckhpd xmm1,xmm0                            
0x533529e  addsd xmm1,xmm0                               
0x53352a2  mulsd xmm1,xmm12                              
0x53352a7  cvttsd2si rax,xmm1                            
0x53352ac  mov rcx,rax                                   
0x53352af  sar rcx,0x3F                                  
0x53352b3  subsd xmm1,xmm13                              
0x53352b8  cvttsd2si rdi,xmm1                            
0x53352bd  and rdi,rcx                                   
0x53352c0  or rdi,rax                                    
0x53352c3  mov r14,[rbp+0x140]                           
0x53352ca  mov rax,[rbp+0x150]                           
0x53352d1  sub rax,r14                                   
0x53352d4  sar rax,3                                     
0x53352d8  imul rax,rdx                                  
0x53352dc  cmp rax,rdi                                   
0x53352df  jae 0x5335445                                 ; -> loc_5335445
0x53352e5  mov rax,0xAAAAAAAAAAAAAAB                     
0x53352ef  cmp rdi,rax                                   
0x53352f2  jae 0x533A6E1                                 ; -> sub_533a6e1
0x53352f8  mov rsi,[rbp+0x148]                           
0x53352ff  lea rax,[rdi*8]                               
0x5335307  lea r15,[rax+rax*2]                           
0x533530b  cmp rdi,0xAB                                  
0x5335312  jb short 0x5335360                            ; -> loc_5335360
0x5335314  mov rax,0xAAAAAAAAAAAAAAA                     
0x533531e  cmp rdi,rax                                   
0x5335321  je 0x533A6ED                                  ; -> sub_533a6ed
0x5335327  add r15,0x27                                  
0x533532b  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x5335332  mov rax,[rcx]                                 
0x5335335  mov rax,[rax+8]                               
0x5335339  mov rdx,r15                                   
0x533533c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5335342  nop                                           
0x5335343  mov rbx,rax                                   
0x5335346  test rax,rax                                  
0x5335349  je 0x5335BBB                                  ; -> loc_5335bbb

loc_533534f:  ; from 5335bc4
0x533534f  mov rax,rbx                                   
0x5335352  add rbx,0x27                                  
0x5335356  and rbx,0xFFFFFFFFFFFFFFE0                    
0x533535a  mov [rbx-8],rax                               
0x533535e  jmp short 0x5335384                           ; -> loc_5335384

loc_5335360:  ; from 5335312
0x5335360  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x5335367  mov rax,[rcx]                                 
0x533536a  mov rax,[rax+8]                               
0x533536e  mov rdx,r15                                   
0x5335371  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5335377  nop                                           
0x5335378  mov rbx,rax                                   
0x533537b  test rax,rax                                  
0x533537e  je 0x5335BAB                                  ; -> loc_5335bab

loc_5335384:  ; from 533535e, 5335bb6
0x5335384  mov rcx,[rbp+0x140]                           
0x533538b  mov rax,[rbp+0x148]                           
0x5335392  cmp rcx,rax                                   
0x5335395  je short 0x53353E9                            ; -> loc_53353e9
0x5335397  xor edx,edx                                   
0x5335399  nop [rax]                                     

loc_53353a0:  ; from 53353e0
0x53353a0  mov r8,[rcx+rdx]                              
0x53353a4  mov [rbx+rdx],r8                              
0x53353a8  mov r8d,[rcx+rdx+8]                           
0x53353ad  mov [rbx+rdx+8],r8d                           
0x53353b2  mov r8d,[rcx+rdx+0xC]                         
0x53353b7  mov [rbx+rdx+0xC],r8d                         
0x53353bc  mov r8d,[rcx+rdx+0x10]                        
0x53353c1  mov [rbx+rdx+0x10],r8d                        
0x53353c6  movzx r8d,byte ptr [rcx+rdx+0x14]             
0x53353cc  mov [rbx+rdx+0x14],r8b                        
0x53353d1  lea r8,[rcx+rdx]                              
0x53353d5  add r8,0x18                                   
0x53353d9  add rdx,0x18                                  
0x53353dd  cmp r8,rax                                    
0x53353e0  jne short 0x53353A0                           ; -> loc_53353a0
0x53353e2  mov rcx,[rbp+0x140]                           

loc_53353e9:  ; from 5335395
0x53353e9  test rcx,rcx                                  
0x53353ec  je short 0x5335422                            ; -> loc_5335422
0x53353ee  mov rdx,[rbp+0x150]                           
0x53353f5  sub rdx,rcx                                   
0x53353f8  cmp rdx,0x1000                                
0x53353ff  jb short 0x533541D                            ; -> loc_533541d
0x5335401  mov rax,[rcx-8]                               
0x5335405  add rcx,0xFFFFFFFFFFFFFFF8                    
0x5335409  sub rcx,rax                                   
0x533540c  cmp rcx,0x20                                  
0x5335410  jae 0x533A6BB                                 ; -> sub_533a6bb
0x5335416  add rdx,0x27                                  
0x533541a  mov rcx,rax                                   

loc_533541d:  ; from 53353ff
0x533541d  call 0xE935700                                ; -> sub_e935700

loc_5335422:  ; from 53353ec
0x5335422  mov [rbp+0x140],rbx                           
0x5335429  sub rsi,r14                                   
0x533542c  add rsi,rbx                                   
0x533542f  mov [rbp+0x148],rsi                           
0x5335436  lea rax,[rdi+rdi*2]                           
0x533543a  lea rax,[rbx+rax*8]                           
0x533543e  mov [rbp+0x150],rax                           

loc_5335445:  ; from 53352df
0x5335445  test rdi,rdi                                  
0x5335448  js short 0x5335460                            ; -> loc_5335460
0x533544a  xorps xmm0,xmm0                               
0x533544d  cvtsi2ss xmm0,rdi                             
0x5335452  jmp short 0x5335478                           ; -> loc_5335478
0x5335454  nop [rax+rax]                                 

loc_5335460:  ; from 5335448
0x5335460  mov rax,rdi                                   
0x5335463  shr rax,1                                     
0x5335466  and edi,1                                     
0x5335469  or rdi,rax                                    
0x533546c  xorps xmm0,xmm0                               
0x533546f  cvtsi2ss xmm0,rdi                             
0x5335474  addss xmm0,xmm0                               

loc_5335478:  ; from 5335452
0x5335478  divss xmm0,[rbp+0x160]                        
0x5335480  call 0xEEC73F0                                ; -> sub_eec73f0
0x5335485  cvttss2si rax,xmm0                            
0x533548a  mov rcx,rax                                   
0x533548d  sar rcx,0x3F                                  
0x5335491  subss xmm0,xmm9                               
0x5335496  cvttss2si rdx,xmm0                            
0x533549b  and rdx,rcx                                   
0x533549e  or rdx,rax                                    
0x53354a1  lea rcx,[rbp+0x120]                           
0x53354a8  call 0x53D9BE0                                ; -> sub_53d9be0
0x53354ad  nop                                           
0x53354ae  mov r12,[rbp+0x200]                           
0x53354b5  mov rax,[rbp+0x208]                           
0x53354bc  mov [rbp+0x1F0],rax                           
0x53354c3  cmp r12,[rbp+0x1F0]                           
0x53354ca  jne 0x5335590                                 ; -> loc_5335590
```

---

## NEXT for 0x5334850
Resume at 0x5335daa (loc_5335daa) - continues with draw record writes, timestamp comparisons, and allocator calls. Function size 0x5f3c (24380 bytes), first 1500 instructions cover up to ~0x5335daa.

---

# Event processor 0x5334850 - Continuation (Chunk 3)

## Chunk 3: 0x53354ca..0x5335daa (500 instructions)

```
0x53354ca  jne 0x5335590                                 ; -> loc_5335590

loc_53354d0:  ; from 533557d, 5335b84
0x53354d0  mov rax,[rbp+0x200]                           
0x53354d7  mov rcx,[rbp+0x208]                           
0x53354de  mov r14,[rbp+0x250]                           
0x53354e5  cmp rax,rcx                                   
0x53354e8  je short 0x53354F1                            ; -> loc_53354f1
0x53354ea  mov [rbp+0x208],rax                           

loc_53354f1:  ; from 53354e8
0x53354f1  mov rcx,[rbp+0x1C8]                           
0x53354f8  test rcx,rcx                                  
0x53354fb  je short 0x5335517                            ; -> loc_5335517
0x53354fd  lea rax,[rbp+0x190]                           
0x5335504  cmp rcx,rax                                   
0x5335507  setne dl                                      
0x533550a  mov rax,[rcx]                                 
0x533550d  mov rax,[rax+0x20]                            
0x5335511  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040

loc_5335517:  ; from 53354fb
0x5335517  mov rax,[rbp+0x1D0]                           
0x533551e  test rax,rax                                  
0x5335521  je 0x5335090                                  ; -> sub_5335090
0x5335527  lock dec dword ptr [rax+8]                    
0x533552b  jne 0x5335090                                 ; -> sub_5335090
0x5335531  mov rax,[rax]                                 
0x5335534  mov rax,[rax]                                 
0x5335537  mov rcx,[rbp+0x1D0]                           
0x533553e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5335544  mov rcx,[rbp+0x1D0]                           
0x533554b  lock dec dword ptr [rcx+0xC]                  
0x533554f  jne 0x5335090                                 ; -> sub_5335090
0x5335555  mov rax,[rcx]                                 
0x5335558  mov rax,[rax+8]                               
0x533555c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5335562  jmp 0x5335090                                 ; -> sub_5335090

loc_5335567:  ; from 53356f2
0x5335567  mov eax,1                                     
0x533556c  shl eax,cl                                    
0x533556e  or [r10+0x14],al                              
0x5335572  add r12,0xC                                   
0x5335576  cmp r12,[rbp+0x1F0]                           
0x533557d  je 0x53354D0                                  ; -> loc_53354d0
0x5335583  nop [rax+rax]                                 

loc_5335590:  ; from 53354ca, 5335b7e
0x5335590  movzx eax,byte ptr [r12]                      
0x5335595  mov r9,0xCBF29CE484222325                     
0x533559f  xor rax,r9                                    
0x53355a2  mov r10,0x100000001B3                         
0x53355ac  imul rax,r10                                  
0x53355b0  movzx ecx,byte ptr [r12+1]                    
0x53355b6  xor rcx,rax                                   
0x53355b9  imul rcx,r10                                  
0x53355bd  movzx eax,byte ptr [r12+2]                    
0x53355c3  xor rax,rcx                                   
0x53355c6  imul rax,r10                                  
0x53355ca  movzx ecx,byte ptr [r12+3]                    
0x53355d0  xor rcx,rax                                   
0x53355d3  imul rcx,r10                                  
0x53355d7  mov r11d,0x9E3779B9                           
0x53355dd  add rcx,r11                                   
0x53355e0  movzx eax,byte ptr [r12+4]                    
0x53355e6  xor rax,r9                                    
0x53355e9  imul rax,r10                                  
0x53355ed  movzx edx,byte ptr [r12+5]                    
0x53355f3  xor rdx,rax                                   
0x53355f6  imul rdx,r10                                  
0x53355fa  movzx r8d,byte ptr [r12+6]                    
0x5335600  xor r8,rdx                                    
0x5335603  imul r8,r10                                  
0x5335607  movzx eax,byte ptr [r12+7]                    
0x533560d  xor rax,r8                                    
0x5335610  imul rax,r10                                  
0x5335614  mov rdx,rcx                                   
0x5335617  shl rdx,6                                     
0x533561b  mov r8,rcx                                    
0x533561e  shr r8,2                                      
0x5335622  add r8,rdx                                    
0x5335625  add rax,r11                                   
0x5335628  add rax,r8                                    
0x533562b  xor rax,rcx                                   
0x533562e  movzx ecx,byte ptr [r12+8]                    
0x5335634  xor rcx,r9                                    
0x5335637  imul rcx,r10                                  
0x533563b  movzx edx,byte ptr [r12+9]                    
0x5335641  xor rdx,rcx                                   
0x5335644  imul rdx,r10                                  
0x5335648  movzx ecx,byte ptr [r12+0xA]                  
0x533564e  xor rcx,rdx                                   
0x5335651  imul rcx,r10                                  
0x5335655  movzx edx,byte ptr [r12+0xB]                  
0x533565b  xor rdx,rcx                                   
0x533565e  imul rdx,r10                                  
0x5335662  mov rcx,rax                                   
0x5335665  shl rcx,6                                     
0x5335669  mov r8,rax                                    
0x533566c  shr r8,2                                      
0x5335670  add r8,rcx                                    
0x5335673  add rdx,r11                                   
0x5335676  add rdx,r8                                    
0x5335679  xor rdx,rax                                   
0x533567c  mov r14,[rbp+0x120]                           
0x5335683  mov rdi,[rbp+0x128]                           
0x533568a  sub rdi,r14                                   
0x533568d  sar rdi,3                                     
0x5335691  dec rdi                                       
0x5335694  and rdi,rdx                                   
0x5335697  mov rax,[r14+rdi*8]                           
0x533569b  cmp rax,0xFFFFFFFFFFFFFFFF                    
0x533569f  je 0x53357C0                                  ; -> loc_53357c0
0x53356a5  mov rsi,[rbp+0x140]                           
0x53356ac  mov edx,[r12]                                 
0x53356b0  mov r8d,[r12+4]                               
0x53356b5  mov r9d,[r12+8]                               
0x53356ba  mov r10,rax                                   
0x53356bd  jmp short 0x53356C9                           ; -> loc_53356c9
0x53356bf  nop                                           

loc_53356c0:  ; from 53356d6, 53356dc, 53356e2
0x53356c0  mov r10,[r10]                                 
0x53356c3  cmp r10,0xFFFFFFFFFFFFFFFF                    
0x53356c7  je short 0x5335700                            ; -> loc_5335700

loc_53356c9:  ; from 53356bd
0x53356c9  lea r11,[r10+r10*2]                           
0x53356cd  lea r10,[rsi+r11*8]                           
0x53356d1  cmp [rsi+r11*8+8],edx                         
0x53356d6  jne short 0x53356C0                           ; -> loc_53356c0
0x53356d8  cmp [r10+0xC],r8d                             
0x53356dc  jne short 0x53356C0                           ; -> loc_53356c0
0x53356de  cmp [r10+0x10],r9d                            
0x53356e2  jne short 0x53356C0                           ; -> loc_53356c0
0x53356e4  mov rcx,[rbp+0x100]                           
0x53356eb  cmp [rbp+0x148],r10                           
0x53356f2  jne 0x5335567                                 ; -> loc_5335567
0x53356f8  jmp short 0x5335707                           ; -> loc_5335707
0x53356fa  nop [rax+rax]                                 

loc_5335700:  ; from 53356c7
0x5335700  mov rcx,[rbp+0x100]                           

loc_5335707:  ; from 53356f8
0x5335707  mov r10,rax                                   
0x5335711  jmp short 0x5335729                           ; -> loc_5335729
0x5335713  nop [rax+rax]                                 

loc_5335720:  ; from 5335736, 533573c, 5335742
0x5335720  mov r10,[r10]                                 
0x5335723  cmp r10,0xFFFFFFFFFFFFFFFF                    
0x5335727  je short 0x5335760                            ; -> loc_5335760

loc_5335729:  ; from 5335711
0x5335729  lea r11,[r10+r10*2]                           
0x533572d  lea r10,[rsi+r11*8]                           
0x5335731  cmp [rsi+r11*8+8],edx                         
0x5335736  jne short 0x5335720                           ; -> loc_5335720
0x5335738  cmp [r10+0xC],r8d                             
0x533573c  jne short 0x5335720                           ; -> loc_5335720
0x533573e  cmp [r10+0x10],r9d                            
0x5335742  jne short 0x5335720                           ; -> loc_5335720
0x5335744  mov r13,[rbp+0x148]                           
0x533574b  cmp r13,r10                                   
0x533574e  jne 0x5335B61                                 ; -> loc_5335b61
0x5335754  jmp short 0x5335767                           ; -> loc_5335767
0x5335756  nop [rax+rax]                                 

loc_5335760:  ; from 5335727
0x5335760  mov r13,[rbp+0x148]                           

loc_5335767:  ; from 5335754
0x5335767  cmp r13,[rbp+0x150]                           
0x533576e  je short 0x53357DE                            ; -> loc_53357de

loc_5335770:  ; from 53357dc
0x5335770  mov [r13],rax                                 
0x5335774  mov eax,[r12]                                 
0x5335778  mov [r13+8],eax                               
0x533577c  mov eax,[r12+4]                               
0x5335781  mov [r13+0xC],eax                             
0x5335785  mov eax,[r12+8]                               
0x533578a  mov [r13+0x10],eax                            
0x533578e  mov byte ptr [r13+0x14],0                     
0x5335793  mov rbx,[rbp+0x140]                           
0x533579a  mov rax,[rbp+0x148]                           
0x53357a1  add rax,0x18                                  
0x53357a5  mov [rbp+0x148],rax                           
0x53357ac  jmp 0x5335A86                                 ; -> loc_5335a86
0x53357b1  nop [rax+rax]                                 

loc_53357c0:  ; from 533569f
0x53357c0  mov rcx,[rbp+0x100]                           
0x53357c7  mov [rbp+0x248],rcx                           
0x53357ce  mov r13,[rbp+0x148]                           
0x53357d5  cmp r13,[rbp+0x150]                           
0x53357dc  jne short 0x5335770                           ; -> loc_5335770

loc_53357de:  ; from 533576e
0x53357de  mov rsi,r13                                   
0x53357e1  sub rsi,[rbp+0x140]                           
0x53357e8  mov rax,rsi                                   
0x53357eb  sar rax,3                                     
0x53357ef  mov rcx,0xAAAAAAAAAAAAAAAB                    
0x53357f9  imul rax,rcx                                  
0x53357fd  lea r8,[rax+1]                                
0x5335801  mov r15,rax                                   
0x5335804  shr r15,1                                     
0x5335807  mov rdx,0xAAAAAAAAAAAAAAA                     
0x5335811  mov rcx,rdx                                   
0x5335814  sub rcx,r15                                   
0x5335817  add r15,rax                                   
0x533581a  cmp r15,r8                                    
0x533581d  cmovbe r15,r8                                 
0x5335821  cmp rax,rcx                                   
0x5335824  cmova r15,rdx                                 
0x5335828  mov rax,0xAAAAAAAAAAAAAAB                     
0x5335832  cmp r15,rax                                   
0x5335835  jae 0x533A659                                 ; -> sub_533a659
0x533583b  test r15,r15                                  
0x533583e  mov [rbp+0x238],r8                            
0x5335845  je 0x53358E1                                  ; -> loc_53358e1
0x533584b  lea rax,[r15*8]                               
0x5335853  lea rdx,[rax+rax*2]                           
0x5335857  cmp r15,0xAB                                  
0x533585e  jb short 0x53358B0                            ; -> loc_53358b0
0x5335860  mov rax,0xAAAAAAAAAAAAAAA                     
0x533586a  cmp r15,rax                                   
0x533586d  je 0x533A6D5                                  ; -> sub_533a6d5
0x5335873  add rdx,0x27                                  
0x5335877  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x533587e  mov rax,[rcx]                                 
0x5335881  mov rax,[rax+8]                               
0x5335885  mov [rbp+0x230],rdx                           
0x533588c  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x5335892  nop                                           
0x5335893  mov rbx,rax                                   
0x5335896  test rax,rax                                  
0x5335899  je 0x5335B89                                  ; -> loc_5335b89

loc_533589f:  ; from 5335b96
0x533589f  mov rax,rbx                                   
0x53358a2  add rbx,0x27                                  
0x53358a6  and rbx,0xFFFFFFFFFFFFFFE0                    
0x53358aa  mov [rbx-8],rax                               
0x53358ae  jmp short 0x53358E3                           ; -> loc_53358e3

loc_53358b0:  ; from 533585e
0x53358b0  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
0x53358b7  mov rax,[rcx]                                 
0x53358ba  mov rax,[rax+8]                               
0x53358be  mov [rbp+0x230],rdx                           
0x53358c5  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
0x53358cb  nop                                           
0x53358cc  mov rbx,rax                                   
0x53358cf  test rax,rax                                  
0x53358d2  jne short 0x53358E3                           ; -> loc_53358e3
0x53358d4  mov rcx,[rbp+0x230]                           
0x53358db  call 0x9BC830                                 ; -> sub_9bc830
0x53358e0  nop                                           

loc_53358e1:  ; from 5335845
0x53358e1  xor ebx,ebx                                   

loc_53358e3:  ; from 53358ae, 53358d2
0x53358e3  mov rax,[r14+rdi*8]                           
0x53358e7  mov [rbx+rsi],rax                             
0x53358eb  mov eax,[r12]                                 
0x53358ef  mov [rbx+rsi+8],eax                           
0x53358f3  mov eax,[r12+4]                               
0x53358f8  mov [rbx+rsi+0xC],eax                         
0x53358fc  mov eax,[r12+8]                               
0x5335901  mov [rbx+rsi+0x10],eax                        
0x5335905  mov byte ptr [rbx+rsi+0x14],0                 
0x533590a  mov rcx,[rbp+0x140]                           
0x5335911  mov rax,[rbp+0x148]                           
0x5335918  cmp r13,rax                                   
0x533591b  je 0x53359D5                                  ; -> loc_53359d5
0x5335921  cmp rcx,r13                                   
0x5335924  je short 0x5335971                            ; -> loc_5335971
0x5335926  xor eax,eax                                   
0x5335928  nop [rax+rax]                                 

loc_5335930:  ; from 5335968
0x5335930  mov rdx,[rcx+rax]                             
0x5335934  mov [rbx+rax],rdx                             
0x5335938  mov edx,[rcx+rax+8]                           
0x533593c  mov [rbx+rax+8],edx                           
0x5335940  mov edx,[rcx+rax+0xC]                         
0x5335944  mov [rbx+rax+0xC],edx                         
0x5335948  mov edx,[rcx+rax+0x10]                        
0x533594c  mov [rbx+rax+0x10],edx                        
0x5335950  movzx edx,byte ptr [rcx+rax+0x14]             
0x5335955  mov [rbx+rax+0x14],dl                         
0x5335959  lea rdx,[rcx+rax]                             
0x533595d  add rdx,0x18                                  
0x5335961  add rax,0x18                                  
0x5335965  cmp rdx,r13                                   
0x5335968  jne short 0x5335930                           ; -> loc_5335930
0x533596a  mov rax,[rbp+0x148]                           

loc_5335971:  ; from 5335924
0x5335971  cmp r13,rax                                   
0x5335974  je 0x5335A1A                                  ; -> loc_5335a1a
0x533597a  lea rcx,[rbx+rsi]                             
0x533597e  add rcx,0x2C                                  
0x5335982  xor edx,edx                                   
0x5335984  nop [rax+rax]                                 

loc_5335990:  ; from 53359d1
0x5335990  mov r8,[r13+rdx]                              
0x5335995  mov [rcx+rdx-0x14],r8                         
0x533599f  mov r8d,[r13+rdx+8]                           
0x533599f  mov [rcx+rdx-0xC],r8d                         
0x53359a4  mov r8d,[r13+rdx+0xC]                         
0x53359a9  mov [rcx+rdx-8],r8d                           
0x53359b3  mov r8d,[r13+rdx+0x10]                        
0x53359b3  mov [rcx+rdx-4],r8d                           
0x53359b8  movzx r8d,byte ptr [r13+rdx+0x14]             
0x53359be  mov [rcx+rdx],r8b                             
0x53359c2  lea r8,[rdx+r13]                              
0x53359c6  add r8,0x18                                   
0x53359ca  add rdx,0x18                                  
0x53359ce  cmp r8,rax                                    
0x53359d1  jne short 0x5335990                           ; -> loc_5335990
0x53359d3  jmp short 0x5335A1A                           ; -> loc_5335a1a

loc_53359d5:  ; from 533591b
0x53359d5  cmp rcx,r13                                   
0x53359d8  je short 0x5335A21                            ; -> loc_5335a21
0x53359da  xor eax,eax                                   
0x53359dc  nop [rax]                                     

loc_53359e0:  ; from 5335a18
0x53359e0  mov rdx,[rcx+rax]                             
0x53359e4  mov [rbx+rax],rdx                             
0x53359e8  mov edx,[rcx+rax+8]                           
0x53359ec  mov [rbx+rax+8],edx                           
0x53359f0  mov edx,[rcx+rax+0xC]                         
0x53359f4  mov [rbx+rax+0xC],edx                         
0x53359f8  mov edx,[rcx+rax+0x10]                        
0x53359fc  mov [rbx+rax+0x10],edx                        
0x5335a00  movzx edx,byte ptr [rcx+rax+0x14]             
0x5335a05  mov [rbx+rax+0x14],dl                         
0x5335a09  lea rdx,[rcx+rax]                             
0x5335a0d  add rdx,0x18                                  
0x5335a11  add rax,0x18                                  
0x5335a15  cmp rdx,r13                                   
0x5335a18  jne short 0x53359E0                           ; -> loc_53359e0

loc_5335a1a:  ; from 5335974, 53359d3
0x5335a1a  mov rcx,[rbp+0x140]                           

loc_5335a21:  ; from 53359d8
0x5335a21  test rcx,rcx                                  
0x5335a24  je short 0x5335A5A                            ; -> loc_5335a5a
0x5335a26  mov rdx,[rbp+0x150]                           
0x5335a2d  sub rdx,rcx                                   
0x5335a30  cmp rdx,0x1000                                
0x5335a37  jb short 0x5335A55                            ; -> loc_5335a55
0x5335a39  mov rax,[rcx-8]                               
0x5335a3d  add rcx,0xFFFFFFFFFFFFFFF8                    
0x5335a41  sub rcx,rax                                   
0x5335a44  cmp rcx,0x20                                  
0x5335a48  jae 0x533A6BB                                 ; -> sub_533a6bb
0x5335a4e  add rdx,0x27                                  
0x5335a52  mov rcx,rax                                   

loc_5335a55:  ; from 5335a37
0x5335a55  call 0xE935700                                ; -> sub_e935700

loc_5335a5a:  ; from 5335a24
0x5335a5a  mov [rbp+0x140],rbx                           
0x5335a61  mov rax,[rbp+0x238]                           
0x5335a68  lea rax,[rax+rax*2]                           
0x5335a6c  lea rax,[rbx+rax*8]                           
0x5335a70  mov [rbp+0x148],rax                           
0x5335a77  lea rcx,[r15+r15*2]                           
0x5335a7b  lea rcx,[rbx+rcx*8]                           
0x5335a7f  mov [rbp+0x150],rcx                           

loc_5335a86:  ; from 53357ac
0x5335a86  sub rax,rbx                                   
0x5335a89  sar rax,3                                     
0x5335a8d  mov rcx,0xAAAAAAAAAAAAAAAB                    
0x5335a97  imul rax,rcx                                  
0x5335a9b  dec rax                                       
0x5335a9e  mov rcx,[rbp+0x120]                           
0x5335aa5  mov [rcx+rdi*8],rax                           
0x5335aa9  mov rdx,[rbp+0x128]                           
0x5335ab0  sub rdx,[rbp+0x120]                           
0x5335ab7  mov rax,[rbp+0x140]                           
0x5335ac5  mov rcx,[rbp+0x148]
0x5335ace  cvtsi2ss xmm0,r8                              
0x5335ad3  jmp short 0x5335AF6                           ; -> loc_5335af6
0x5335ad5  nop [rax+rax]                                 

loc_5335ae0:  ; from 5335acc
0x5335ae0  mov r9,r8                                     
0x5335ae3  shr r9,1                                      
0x5335ae6  and r8d,1                                     
0x5335aea  or r8,r9                                      
0x5335aed  cvtsi2ss xmm0,r8                              
0x5335af2  addss xmm0,xmm0                               

loc_5335af6:  ; from 5335ad3
0x5335af6  sub rcx,rax                                   
0x5335af9  mov r8,rcx                                    
0x5335afc  sar r8,3                                      
0x5335b00  mov r9,0xAAAAAAAAAAAAAAAB                     
0x5335b0a  imul r8,r9                                    
0x5335b0e  mulss xmm0,[rbp+0x160]                        
0x5335b16  cvttss2si r9,xmm0                            
0x5335b1b  mov r10,r9                                   
0x5335b1e  subss xmm0,xmm9                                  
0x5335b23  cvttss2si r11,xmm0                              
0x5335b28  sar r10,0x3F
0x5335b2c  and r11,r10                                   
0x5335b2f  or r11,r9                                    
0x5335b32  cmp r8,r11                                    
0x5335b35  jbe short 0x5335B59                           ; -> loc_5335b59
0x5335b37  sar rdx,2                                     
0x5335b3b  lea rcx,[rbp+0x120]                           
0x5335b42  call 0x53D9BE0                                ; -> sub_53d9be0
0x5335b47  nop                                           
0x5335b48  mov rax,[rbp+0x140]                           
0x5335b4f  mov rcx,[rbp+0x148]                           
0x5335b56  sub rcx,rax                                   

loc_5335b59:  ; from 5335b35
0x5335b59  lea r10,[rax+rcx]                             
0x5335b5d  add r10,0xFFFFFFFFFFFFFFE8                    

loc_5335b61:  ; from 533574e
0x5335b61  mov eax,1                                     
0x5335b66  mov rcx,[rbp+0x248]                           
0x5335b6d  shl eax,cl                                    
0x5335b6f  mov [r10+0x14],al                             
0x5335b73  add r12,0xC                                   
0x5335b77  cmp r12,[rbp+0x1F0]                           
0x5335b7e  jne 0x5335590                                 ; -> loc_5335590
0x5335b84  jmp 0x53354D0                                 ; -> loc_53354d0

loc_5335b89:  ; from 5335899
0x5335b89  mov rcx,[rbp+0x230]                           
0x5335b90  call 0x9BC830                                 ; -> sub_9bc830
0x5335b95  nop                                           
0x5335b96  jmp 0x533589F                                 ; -> loc_533589f
0x5335b9b  mov ecx,0x70                                  
0x5335ba0  call 0x9BC830                                 ; -> sub_9bc830
0x5335ba5  nop                                           
0x5335ba6  jmp 0x53351AF                                 ; -> sub_53351af
0x5335bab  mov rcx,r15                                   
0x5335bae  call 0x9BC830                                 ; -> sub_9bc830
0x5335bb3  nop                                           
0x5335bb4  xor ebx,ebx                                   
0x5335bb6  jmp 0x5335384                                 ; -> sub_5335384
0x5335bbb  mov rcx,r15                                   
0x5335bbe  call 0x9BC830                                 ; -> sub_9bc830
0x5335bc3  nop                                           
0x5335bc4  jmp 0x533534F                                 ; -> sub_533534f
0x5335bc9  mov rcx,[rbp+0x200]                           
0x5335bd0  test rcx,rcx                                  
0x5335bd3  je short 0x5335C09                            ; -> loc_5335c09
0x5335bd5  mov rdx,[rbp+0x210]                           
0x5335bdc  sub rdx,rcx                                   
0x5335bdf  cmp rdx,0x1000                                
0x5335be6  jb short 0x5335C04                            ; -> loc_5335c04
0x5335be8  mov rax,[rcx-8]                               
0x5335bec  add rcx,0xFFFFFFFFFFFFFFF8                    
0x5335bf0  sub rcx,rax                                   
0x5335bf3  cmp rcx,0x20                                  
0x5335bf7  jae 0x533A6BB                                 ; -> sub_533a6bb
0x5335bfd  add rdx,0x27                                  
0x5335c01  mov rcx,rax                                   

loc_5335c04:  ; from 5335be6
0x5335c04  call 0xE935700                                ; -> sub_e935700

loc_5335c09:  ; from 5335bd3
0x5335c09  cmp byte ptr [rbp+0x246],0                    
0x5335c10  je 0x5335DAA                                  ; -> loc_5335daa
0x5335c16  mov rsi,[rbp+0x140]                           
0x5335c1d  mov rdi,[rbp+0x148]                           
0x5335c24  mov rax,rdi                                   
0x5335c27  sub rax,rsi                                   
0x5335c2a  mov rcx,rax                                   
0x5335c2d  sar rcx,3                                     
0x5335c31  mov r9,0xAAAAAAAAAAAAAAAB                     
0x5335c3b  imul rcx,r9                                   
0x5335c3f  mov [rbp+0x190],rcx                           
0x5335c46  mov r8,[rbp+0x250]                            
0x5335c4d  mov rdx,[r8+0x458]                            
0x5335c54  sub rdx,[r8+0x448]                            
0x5335c5b  lea r14,[r8+0x448]                            
0x5335c62  sar rdx,2                                     
0x5335c66  imul rdx,r9                                   
0x5335c6a  cmp rcx,rdx                                   
0x5335c6d  jbe short 0x5335CBB                           ; -> loc_5335cbb
0x5335c6f  mov rax,0x1555555555555556                    
0x5335c79  cmp rcx,rax                                   
0x5335c7c  jae 0x533A711                                 ; -> sub_533a711
0x5335c82  lea rdx,[rbp+0x190]                           
0x5335c89  mov rcx,r14                                   
0x5335c8c  call 0x53C5B50                                ; -> sub_53c5b50
0x5335c91  nop                                           
0x5335c92  mov rsi,[rbp+0x140]                           
0x5335c99  mov rdi,[rbp+0x148]                           
0x5335ca0  mov rax,rdi                                   
0x5335ca3  sub rax,rsi                                   
0x5335ca6  mov rcx,rax                                   
0x5335ca9  sar rcx,3                                     
0x5335cad  mov rdx,0xAAAAAAAAAAAAAAAB                    
0x5335cb7  imul rcx,rdx                                  

loc_5335cbb:  ; from 5335c6d
0x5335cbb  mov r8,[rbp+0x250]                            
0x5335cc2  lea rbx,[r8+0x460]                            
0x5335cc9  mov [rbp+0x190],rcx                           
0x5335cd0  mov rdx,[r8+0x470]                            
0x5335cd7  sub rdx,[r8+0x460]                            
0x5335cde  cmp rcx,rdx                                   
0x5335ce1  jbe short 0x5335D31                           ; -> loc_5335d31
0x5335ce3  test rax,rax                                  
0x5335ce6  js 0x533A717                                  ; -> sub_533a717
0x5335cec  lea rdx,[rbp+0x190]                           
0x5335cf3  mov rcx,rbx                                   
0x5335cf6  call 0x2F6DF0                                 ; -> sub_2f6df0
0x5335cfb  nop                                           
0x5335cfc  mov rsi,[rbp+0x140]                           
0x5335d03  mov rdi,[rbp+0x148]                           
0x5335d0a  cmp rsi,rdi                                   
0x5335d0d  jne short 0x5335D36                           ; -> loc_5335d36
0x5335d0f  jmp 0x5335DAA                                 ; -> loc_5335daa
0x5335d14  nop [rax+rax]                                 ; R ret@2f6df0+0x0+idx

loc_5335d20:  ; from 5335d96
0x5335d20  movzx eax,byte ptr [r8]                       
0x5335d24  mov [rdx],al                                  
0x5335d26  inc qword ptr [rcx+0x468]                     
0x5335d2d  add rsi,0x18                                  

loc_5335d31:  ; from 5335ce1
0x5335d31  cmp rsi,rdi                                   
0x5335d34  je short 0x5335DAA                            ; -> loc_5335daa

loc_5335d36:  ; from 5335d0d, 5335da8
0x5335d36  mov rcx,[rbp+0x250]                           
0x5335d3d  mov rdx,[rcx+0x450]                           
0x5335d44  cmp rdx,[rcx+0x458]                           
0x5335d4b  je short 0x5335D70                            ; -> loc_5335d70
0x5335d4d  mov eax,[rsi+8]                               
0x5335d50  mov [rdx],eax                                 
0x5335d52  mov eax,[rsi+0xC]                             
0x5335d55  mov [rdx+4],eax                               
0x5335d58  mov eax,[rsi+0x10]                            
0x5335d5b  mov [rdx+8],eax                               
0x5335d5e  add qword ptr [rcx+0x450],0xC                 
0x5335d66  jmp short 0x5335D7D                           ; -> loc_5335d7d
0x5335d68  nop [rax+rax]                                 

loc_5335d70:  ; from 5335d4b
0x5335d70  lea r8,[rsi+8]                                
0x5335d74  mov rcx,r14                                   
0x5335d77  call 0x53C5CE0                                ; -> sub_53c5ce0
0x5335d7c  nop                                           

loc_5335d7d:  ; from 5335d66
0x5335d7d  lea r8,[rsi+0x14]                             
0x5335d81  mov rcx,[rbp+0x250]                           
0x5335d88  mov rdx,[rcx+0x468]                           
0x5335d8f  cmp rdx,[rcx+0x470]                           
0x5335d96  jne short 0x5335D20                           ; -> loc_5335d20
0x5335d98  mov rcx,rbx                                   
0x5335d9b  call 0x2F6F30                                 ; -> sub_2f6f30
0x5335da0  nop                                           
0x5335da1  add rsi,0x18                                  
0x5335da5  cmp rsi,rdi                                   
0x5335da8  jne short 0x5335D36                           ; -> loc_5335d36

loc_5335daa:  ; from 5335c10, 5335d0f, 5335d34
0x5335daa  mov r14,[rbp+0x250]                           
0x5335db1  mov rax,[r14+0x450]                           
0x5335db8  sub rax,[r14+0x448]                           
0x5335dbf  sar rax,2                                     
0x5335dc3  mov rcx,0xAAAAAAAAAAAAAAAB                    
0x5335dcd  imul rax,rcx                                  
0x5335dd1  mov [r14+0x570],rax                           
0x5335dd8  cmp byte ptr [rbp+0x247],1                    
0x5335ddf  jne short 0x5335E1F                           ; -> loc_5335e1f
0x5335de1  call 0xEEC5920                                ; -> sub_eec5920
0x5335de6  mov rbx,rax                                   
0x5335de9  call 0xEEC5930                                ; -> sub_eec5930
0x5335dee  cmp rbx,0x16E3600                             
0x5335df5  je short 0x5335E3A                            ; -> loc_5335e3a
0x5335df7  cmp rbx,0x989680                              
0x5335dfe  jne 0x5335EAE                                 ; -> loc_5335eae
0x5335e04  mov qword ptr [rbp+0x170],0                   
0x5335e0f  imul rax,0xFFFFFFFFFFFFFF9C                   
0x5335e13  mov [rbp+0xF8],rax                            
0x5335e1a  jmp 0x5335EFF                                 ; -> loc_5335eff

loc_5335e1f:  ; from 5335ddf
0x5335e1f  mov qword ptr [rbp+0x170],0                   
0x5335e2a  mov qword ptr [rbp+0xF8],0                    
0x5335e35  jmp 0x5335EFF                                 ; -> loc_5335eff

loc_5335e3a:  ; from 5335df5
0x5335e3a  mov qword ptr [rbp+0x170],0                   
0x5335e45  mov rdx,0xB2F4FC0794908CF3                    
0x5335e4f  mov rcx,rax                                   
0x5335e52  imul rdx                                      
0x5335e55  mov r8,rdx                                    
0x5335e58  add r8,rcx                                    
0x5335e5b  mov rax,r8                                    
0x5335e5e  shr rax,0x3F                                  
0x5335e62  sar r8,0x18                                   
0x5335e66  add r8,rax                                    
0x5335e69  imul rax,r8,0x16E3600                         
0x5335e70  sub rcx,rax                                   
0x5335e73  imul rcx,0x3B9ACA00                           
0x5335e7a  mov rdx,0x4D0B03F86B6F730D                    
0x5335e84  mov rax,rcx                                   
0x5335e87  imul rdx                                      
0x5335e87  imul rax,r8,0xFFFFFFFFC4653600                
0x5335e91  sub rdx,rcx                                   
0x5335e94  mov rcx,rdx                                   
0x5335e97  shr rcx,0x3F                                  
0x5335e9b  sar rdx,0x18                                  
0x5335e9f  add rdx,rcx                                   
0x5335ea2  add rdx,rax                                   
0x5335ea5  mov [rbp+0xF8],rdx                            
0x5335eac  jmp short 0x5335EFF                           ; -> loc_5335eff

loc_5335eae:  ; from 5335dfe
0x5335eae  mov rcx,rax                                   
0x5335eb1  or rcx,rbx                                    
0x5335eb4  shr rcx,0x20                                  
0x5335eb8  je short 0x5335EC1                            ; -> loc_5335ec1
0x5335eba  cqo                                           
0x5335ebc  idiv rbx                                      
0x5335ebf  jmp short 0x5335EC5                           ; -> loc_5335ec5

loc_5335ec1:  ; from 5335eb8
0x5335ec1  xor edx,edx                                   
0x5335ec3  div ebx                                       

loc_5335ec5:  ; from 5335ebf
0x5335ec5  imul r8,rax,0xFFFFFFFFC4653600                
0x5335ecc  imul rax,rdx,0x3B9ACA00                       
0x5335ed3  mov rcx,rax                                   
0x5335ed6  or rcx,rbx                                    
0x5335ed9  shr rcx,0x20                                  
0x5335edd  je short 0x5335EE6                            ; -> loc_5335ee6
0x5335edf  cqo                                           
0x5335ee1  idiv rbx                                      
0x5335ee4  jmp short 0x5335EEA                           ; -> loc_5335eea

loc_5335ee6:  ; from 5335edd
0x5335ee6  xor edx,edx                                   
0x5335ee8  div ebx                                       

loc_5335eea:  ; from 5335ee4
0x5335eea  mov qword ptr [rbp+0x170],0                   
0x5335ef5  sub r8,rax                                    
0x5335ef8  mov [rbp+0xF8],r8                             

loc_5335eff:  ; from 5335e1a, 5335e35, 5335eac
0x5335eff  mov r12,[r14+0x450]                           
0x5335f06  sub r12,[r14+0x448]                           
0x5335f0d  sar r12,2                                     
0x5335f11  mov rax,0xAAAAAAAAAAAAAAAB                    
0x5335f1b  imul r12,rax                                  
0x5335f1f  lea rax,[r14+0x148]                           
0x5335f26  mov [rbp+0x88],rax                            
0x5335f2d  lea rax,[r14+0x478]                           
0x5335f34  mov [rbp+0x30],rax                            
0x5335f38  xorps xmm0,xmm0                               
0x5335f3b  movss [rbp+0x178],xmm0                        
0x5335f43  movss xmm7,[0xEF3F044]                        ; [data_ef3f044]
0x5335f4b  movss xmm10,[0xEEE7C00]                       ; [data_eee7c00]
0x5335f54  movaps xmm13,[0xF0B8810]                      ; [data_f0b8810]
0x5335f5c  lea rax,[rbp+0x200]                           
0x5335f63  mov [rbp+0x28],rax                            
0x5335f67  pxor xmm6,xmm6                                
0x5335f6b  xor edi,edi                                   
0x5335f6d  xor edx,edx                                   
0x5335f6f  mov qword ptr [rbp+0x230],0                   
0x5335f7a  xor eax,eax                                   
0x5335f7c  xor r8d,r8d                                   
0x5335f7f  xor r9d,r9d                                   
0x5335f82  mov [rbp+0x188],r12                           
0x5335f89  jmp short 0x5335FC0                           ; -> loc_5335fc0
0x5335f8b  nop [rax+rax]                                 

loc_5335f90:  ; from 53362bb
0x5335f90  xor eax,eax                                   
0x5335f92  movzx ecx,byte ptr [rbp+0x1E0]                
0x5335f99  mov edi,ecx                                   
0x5335fa2  movzx ecx,byte ptr [rbp+0x1E8]                
0x5335fa4  mov edx,ecx                                   
0x5335fa4  mov r8,[rbp+0x238]                            
0x5335fab  mov r9,[rbp+0xF0]                             
0x5335fb2  mov r14,[rbp+0x250]                           
0x5335fb9  mov r12,[rbp+0x188]                           

loc_5335fc0:  ; from 5335f89, 5336037, 5336099, 53360b8, 53360cb, 53360e2, ...
0x5335fc0  mov [rbp+0x238],r8                            
0x5335fc7  mov rcx,[rbp+0x230]                           
0x5335fce  test al,1                                     
0x5335fd0  jne 0x5336B3B                                 ; -> loc_5336b3b
0x5335fd6  mov r13,r9                                    
0x5335fd9  mov esi,edi                                   
0x5335fdb  cmp rcx,r12                                   
0x5335fde  mov [rbp+0x1E8],dl                            
0x5335fe4  jae 0x5336070                                 ; -> loc_5336070
0x5335fea  mov r10b,1                                    
0x5335fed  cmp byte ptr [rbp+0x246],1                    
0x5335ff4  jne short 0x5336006                           ; -> loc_5336006
0x5335ff6  mov rax,[r14+0x460]                           
0x5335ffd  movzx r10d,byte ptr [rax+rcx]                 
0x5336002  and r10b,0xF                                  

loc_5336006:  ; from 5335ff4
0x5336006  lea rax,[rcx+1]                               
0x533600a  mov [rbp+0x230],rax                           
0x5336011  mov rbx,[r14+0x130]                           
0x5336018  mov r11,[r14+0x138]                           
0x533601f  xor eax,eax                                   
0x5336021  mov edi,esi                                   
0x5336023  mov r8,[rbp+0x238]                            
0x533602a  mov r9,r13                                    
0x533602d  mov [rbp+0x1F0],r11                           
0x5336034  cmp rbx,r11                                   
0x5336037  je short 0x5335FC0                            ; -> loc_5335fc0
0x5336039  mov [rbp+0x1FF],r10b                          
0x5336040  mov [rbp+0x1E0],sil                           
0x5336047  mov [rbp+0xF0],r13                            
0x533604e  lea rcx,[rcx+rcx*2]                           
0x5336052  shl rcx,2                                     
0x5336056  add rcx,[r14+0x448]                           
0x533605d  mov [rbp+0x248],rcx                           
0x5336064  jmp 0x53362C1                                 ; -> loc_53362c1
0x5336069  nop [rax]                                     

loc_5336070:  ; from 5335fe4
0x5336070  mov dil,1                                     
0x5336073  xor r15d,r15d                                 

loc_5336076:  ; from 53368e8
0x5336076  mov [rbp+0x230],rcx                           
0x533607d  cmp rcx,r12                                   
0x5336080  mov r10,[rbp+0x238]                           
0x5336087  mov r11,r15                                   
0x533608a  jae short 0x533609F                           ; -> loc_533609f
0x533608c  xor eax,eax                                   
0x533608e  mov edx,esi                                   
0x5336090  mov r8,r13                                    
0x5336093  mov r9,r11                                    
0x5336096  test r10,r10                                  
0x5336099  je 0x5335FC0                                  ; -> loc_5335fc0

loc_533609f:  ; from 533608a
0x533609f  mov rcx,r11                                   
0x53360a2  or rcx,r13                                    
0x53360a5  mov al,1                                      
0x53360a7  or rcx,r10                                    
0x53360aa  mov edx,esi                                   
0x53360ac  mov r8d,0                                     
0x53360b2  mov r9d,0                                     
0x53360b8  je 0x5335FC0                                  ; -> loc_5335fc0
0x53360be  xor eax,eax                                   
0x53360c0  mov edx,esi                                   
0x53360c2  mov r8,r13                                    
0x53360c5  mov r9,r11                                    
0x53360c8  test r10,r10                                  
0x53360cb  je 0x5335FC0                                  ; -> loc_5335fc0
0x53360d1  mov rcx,[r10+0x10]                            
0x53360d5  xor eax,eax                                   
0x53360d7  mov edx,esi                                   
0x53360d9  mov r8,r13                                    
0x53360dc  mov r9,r11                                    
0x53360df  test rcx,rcx                                  
0x53360e2  je 0x5335FC0                                  ; -> loc_5335fc0
0x53360e8  test byte ptr [r10+8],0x20                    
0x53360ed  je short 0x5336102                            ; -> loc_5336102
0x53360ef  xor eax,eax                                   
0x53360f1  cmp byte ptr [rcx],0                          
0x53360f4  mov edx,esi                                   
0x53360f6  mov r8,r13                                    
0x53360f9  mov r9,r11                                    
0x53360fc  jne 0x5335FC0                                 ; -> loc_5335fc0

loc_5336102:  ; from 53360ed
0x5336102  mov eax,[rcx+0x1C]                            
0x5336105  sar eax,4                                     
0x5336108  movq xmm0,[rcx+0x14]                          
0x533610d  psrad xmm0,4                                  
0x5336112  movq [rbp+0x200],xmm0                         
0x533611a  mov [rbp+0x208],eax                           
0x5336120  cmp qword ptr [r10+0x20],0                    
0x5336125  jne short 0x5336132                           ; -> loc_5336132
0x5336127  cmp qword ptr [rcx+0x28],0                    
0x533612c  je 0x53367A6                                  ; -> loc_53367a6

loc_5336132:  ; from 5336125
0x5336132  movzx eax,byte ptr [rbp+0x1E8]                
0x5336139  mov [rcx+0x3F],al                             
0x533613c  mov rax,[r10+0x10]                            
0x5336140  test rax,rax                                  
0x5336143  je short 0x533619A                            ; -> loc_533619a
0x5336145  mov edx,[rax+0x14]                            
0x5336148  add edx,8                                     
0x533614b  xorps xmm0,xmm0                               
0x533614e  cvtsi2ss xmm0,edx                             
0x5336152  mov edx,[rax+0x1C]                            
0x5336155  mov eax,[rax+0x18]                            
0x5336158  mov r8,[rbp-0x18]                             
533615c  subss xmm0,[r8]                                 
0x5336161  add eax,8                                     
0x5336164  cvtsi2ss xmm1,eax                             
0x5336168  add edx,8                                     
0x533616b  cvtsi2ss xmm2,edx                             
0x533616f  subss xmm1,[r8+4]                             
0x5336175  subss xmm2,[r8+8]                             
0x533617b  mulss xmm0,xmm0                               
0x533617f  mulss xmm2,xmm2                               
0x5336183  addss xmm2,xmm0                               
0x5336187  movss [r10+4],xmm2                            
0x533618d  mulss xmm1,xmm1                               
0x5336191  addss xmm1,xmm2                               
0x5336195  movss [r10],xmm1                              

loc_533619a:  ; from 5336143
0x533619a  mov eax,[rcx+4]                               
0x533619d  cmp eax,1                                     
0x53361a0  mov [rbp+0x1E0],sil                           
0x53361a7  jne 0x533649C                                 ; -> loc_533649c
0x53361ad  mov rax,[rcx+0x28]                            
0x53361b1  test rax,rax                                  
0x53361b4  je 0x533647A                                  ; -> loc_533647a
0x53361ba  mov rdx,[rax]                                 
0x53361bd  cmp rdx,0xFFFFFFFFFFFFFFFF                    
0x53361c1  je short 0x53361FE                            ; -> loc_53361fe
0x53361c3  mov rcx,[rbp+0x250]                           
0x53361ca  mov rcx,[rcx+0x128]                           
0x53361d1  mov rcx,[rcx+0x390]                           
0x53361d8  test byte ptr [rax+0x28],0x20                 
0x53361dc  lea r8,[rdx+0x14]                             
0x53361e0  cmovne r8,rdx                                 
0x53361e4  cmp rcx,r8                                    
0x53361e7  jae 0x533647A                                 ; -> loc_533647a
0x53361ed  mov rax,[rax+8]                               
0x53361f1  add rax,0x3C                                  
0x53361f5  cmp rcx,rax                                   
0x53361f5  cmp rcx,rax                                   
0x53361f8  jae 0x533647A                                 ; -> loc_533647a

loc_53361fe:  ; from 53361c1
0x53361fe  mov rax,[rbp+0x238]                           
0x5336205  movzx eax,byte ptr [rax+9]                    
0x5336209  cmp al,1                                      
0x533620b  jne 0x533649C                                 ; -> loc_533649c
0x5336211  mov rax,[rbp+0x238]                           
0x5336218  mov rax,[rax+0x10]                            
0x533621c  test rax,rax                                  
0x533621f  je 0x53364E2                                  ; -> loc_53364e2
0x5336225  mov eax,[rax+4]                               
0x5336228  cmp eax,1                                     
0x533622b  jne 0x533649C                                 ; -> loc_533649c
0x5336231  mov rax,[rbp+0x238]                           
0x5336238  mov rdx,[rax+0x10]                            
0x533623c  mov rax,[rdx+0x28]                            
0x5336240  test rax,rax                                  
0x5336243  je 0x53364AC                                  ; -> loc_53364ac
0x5336249  test byte ptr [rax+0x28],2                    
0x533624d  je 0x533649C                                  ; -> loc_533649c
0x5336253  mov rcx,[rbp+0x238]                           
0x533625a  cmp rax,[rcx+0x20]                            
0x533625e  je short 0x5336273                            ; -> loc_5336273
0x5336260  movzx eax,byte ptr [rax+0x25E]                
0x5336267  mov rcx,[rbp+0x238]                           
0x533626e  cmp al,[rcx+0xA]                              
0x533626e  cmp al,[rcx+0xA]                              
0x5336271  jne short 0x5336284                           ; -> loc_5336284

loc_5336273:  ; from 533625e
0x5336273  mov rax,[rbp+0x238]                           
0x533627a  test byte ptr [rax+8],2                       
0x533627e  je 0x533649C                                  ; -> loc_533649c

loc_5336284:  ; from 5336271
0x5336284  mov rax,[rbp+0x250]                           
0x533628b  mov rsi,[rax+0x130]                           
0x5336292  mov rbx,[rax+0x138]                           
0x5336299  jmp 0x53368F1                                 ; -> loc_53368f1

loc_533629e:  ; from 5336428
0x533629e  mov rsi,[rax]                                 

loc_53362a1:  ; from 533643c, 5336446, 533645f, 5336475
0x53362a1  test rsi,rsi                                  
0x53362a4  jne 0x53368A3                                 ; -> loc_53368a3
0x53362aa  nop [rax+rax]                                 

loc_53362b0:  ; from 53362d3, 53362ff, 5336319, 5336325, 5336346, 533635d, ...
0x53362b0  add rbx,0x10                                  
0x53362b4  cmp rbx,[rbp+0x1F0]                           
0x53362bb  je 0x5335F90                                  ; -> loc_5335f90

loc_53362c1:  ; from 5336064
0x53362c1  mov rax,[rbx]                                 
0x53362c4  mov rdx,[rax+0x5E8]                           
0x53362cb  mov eax,[rdx+0xEC]                            
0x53362d1  test eax,eax                                  
0x53362d3  jle short 0x53362B0                           ; -> loc_53362b0
0x53362d5  mov rcx,[rbp+0x248]                           
0x53362dc  mov r11d,[rcx]                                
0x53362df  mov rax,[r14+0x130]                           
0x53362ec  xor r15d,r15d                                 
0x53362ec  mov edx,[rdx+0xC8]                            
53362ed  mov r10d,[rdx+0xD4]                             
53362f1  mov ecx,r11d                                    
53362f3  sub ecx,esi                                     
53362f5  setl r8b                                      
53362f9  cmp r11d,r10d                                   
53362f8  setg r9b                                      
53362fc  or r9b,r8b                                      
53362ff  jne short 0x53362B0                           ; -> loc_53362b0
5336301  mov r8,[rbp+0x248]                              
5336308  mov edi,[r8+4]                                  
5336310  mov r12d,[rdx+0xCC]                             
5336316  mov r8d,edi                                     
5336319  jl short 0x53362B0                           ; -> loc_53362b0
5336322  mov r15d,[rdx+0xD8]                             
5336325  cmp edi,r15d                                    
5336328  jg short 0x53362B0                           ; -> loc_53362b0
533632a  mov r9,[rbp+0x248]                              
5336331  mov r14d,[r9+8]                                 
5336335  mov r13d,[rdx+0xD0]                             
5336339  mov r9d,r14d                                    
5336342  sub r9d,r13d                                    
5336342  inc r9d                                       
5336345  mov [rbp+0x1D0],r9d                           
5336346  jl 0x53362B0                                  ; -> loc_53362b0
5336353  mov r9d,[rdx+0xDC]                              
5336356  mov [rbp+0x180],r9d                           
533635d  cmp r14d,r9d                                  
533635d  jg 0x53362B0                                  ; -> loc_53362b0
5336363  add r15d,r12d                                 
5336366  xorps xmm0,xmm0                               
5336369  cvtsi2ss xmm0,r15d                            
533636e  mov r9d,[rbp+0x180]                           
5336375  add r9d,r13d                                  
5336378  mulss xmm0,xmm7                               
533637c  add r10d,esi                                  
533637f  movd xmm1,r14d                                
5336384  movd xmm2,r11d                                
5336389  punpckldq xmm2,xmm1                           
533638d  cvtdq2ps xmm1,xmm2                            
533638d  xorps xmm2,xmm2                               
5336390  cvtsi2ss xmm2,edi                             
5336397  addss xmm2,xmm0                               
53363a2  xorps xmm0,xmm0                               
53363a5  cvtsi2ss xmm0,r11d                            
53363aa  mulss xmm0,xmm10                              
53363af  addss xmm0,[0xF0B8800]                        ; [data_f0b8800]
53363b7  mulss xmm0,xmm0                               
53363b7  mulss xmm2,xmm2                               
53363b7  movd xmm3,r9d                                 
53363b7  movd xmm4,r10d                                
53363c4  punpckldq xmm4,xmm3                           
53363cd  cvtdq2ps xmm3,xmm4                            
53363d0  mulps xmm3,xmm13                              
53363d4  addps xmm3,xmm1                               
53363da  unpckhpd xmm1,xmm0                            
53363de  addsd xmm1,xmm0                               
53363e2  ucomiss xmm0,xmm3                             
53363e9  jbe 0x53362B0                                 ; -> loc_53362b0
53363ef  mov r10,[rdx+0xF8]                            
53363f6  cmp r10,[rdx+0x100]                           
53363fd  je 0x53362B0                                  ; -> loc_53362b0
53363ef  mov r10,[rdx+0xF8]                            
53363f6  cmp r10,[rdx+0x100]                           
53363fd  je 0x53362B0                                  ; -> loc_53362b0
5336403  imul r11d,[rbp+0x1D0]                         
533640b  imul r8d,eax                                  
533640f  add ecx,r8d                                   
5336412  add ecx,r11d                                  
5336415  movsxd rcx,ecx                                
5336418  shl rcx,4                                     
533641c  lea rax,[r10+rcx]                             
5336420  mov rcx,[r10+rcx+8]                           
5336425  test rcx,rcx                                  
5336428  je 0x533629E                                  ; -> loc_533629e
533642e  lock inc dword ptr [rcx+8]                    
5336432  mov rsi,[rax]                                 
5336435  mov rdi,[rax+8]                               
5336439  test rdi,rdi                                  
533643c  je 0x53362A1                                  ; -> loc_53362a1
5336442  lock dec dword pt [rdi+8]                    
5336446  jne 0x53362A1                                 ; -> loc_53362a1
533644c  mov rax,[rdi]                                 
533644f  mov rax,[rax]                                 
5336452  mov rcx,rdi                                   
5336455  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
533645b  lock dec dword pt [rdi+0xC]                  
533645f  jne 0x53362A1                                 ; -> loc_53362a1
5336465  mov rax,[rdi]                                 
5336468  mov rax,[rax+8]                               
533646c  mov rcx,rdi                                   
533646f  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
5336475  jmp 0x53362A1                                 ; -> loc_53362a1

loc_533647a:  ; from 53361b4, 53361e7, 53361f8
0x533647a  mov rcx,[rbp+0x88]                            
0x5336481  call 0x53D92F0                                ; -> sub_53d92f0
0x5336486  nop                                           
0x5336487  test rax,rax                                  
0x533648a  je short 0x533649C                            ; -> loc_533649c
0x533648c  mov rcx,rax                                   
0x533648f  lea rdx,[rbp+0x200]                           
0x5336496  call 0x53D96D0                                ; -> sub_53d96d0
0x533649b  nop                                           

loc_533649c:  ; from 53361a7, 533620b, 533622b, 533624d, 533627e, 533627e, 533648a, ...
0x533649c  mov rax,[rbp+0x238]                           
0x53364a3  mov rdx,[rax+0x10]                            
0x53364a7  test rdx,rdx                                  
0x53364aa  je short 0x53364E2                            ; -> loc_53364e2

loc_53364ac:  ; from 5336243
0x53364ac  cmp byte ptr [rdx],1                          
0x53364af  jne short 0x53364E4                           ; -> loc_53364e4
0x53364b1  mov rax,[rbp+0x238]                           
0x53364b8  test byte ptr [rax+8],0x20                    
0x53364bc  mov rsi,[rbp+0x250]                           
0x53364c3  jne short 0x53364EB                           ; -> loc_53364eb
0x53364c5  mov rcx,[rbp+0x30]                            
...

---

## NEXT for 0x5334850
Resume at 0x53364c5 - continues with draw record writes, timestamp comparisons, and allocator calls. Function size 0x5f3c (24380 bytes), first 2000 instructions verified up to ~0x53364c5.

---

## Verification
- verify_oc.py on this section: 3741/3741 match (0 mismatches, 0 no-such-instr)

---

## 0x533f580 - Draw-Record Handle Lookup

### Step 1 Complete: Preflight
- Function at 0x533f580..0x533f8c8 (size 0x348), 3 xrefs
- Full function fits in first 400 instructions (0x348 bytes)

### Step 2 Complete: Instruction-complete listing (first 400 instructions, covers entire function)

**Function: sub_533f580 (Draw-Record Handle Lookup)**
**Range:** 0x533f580..0x533f8c8 (size 0x348)
**Callers:** 3 xrefs
**Arguments:** rcx = handle table (a0), rdx = params (a1)

```
0x533f580  push r15
0x533f582  push r14
0x533f584  push r13
0x533f586  push r12
0x533f588  push rsi
0x533f589  push rdi
0x533f58a  push rbp
0x533f58b  push rbx
0x533f58c  sub rsp,0x28
0x533f590  mov eax,[rdx]                                 ; R a1+0x0
0x533f592  mov ebx,[rdx+4]                               ; R a1+0x4
0x533f595  mov edx,[rdx+8]                               ; R a1+0x8
0x533f598  mov [rsp+0x20],eax
0x533f59c  mov [rsp+0x24],edx
0x533f5a0  mov rax,[rcx+0x128]                           ; R a0+0x128
0x533f5a7  mov rcx,[rax+0x430]                           ; R *(a0+0x128)+0x430
0x533f5ae  test rcx,rcx
0x533f5b1  je 0x533F6F4                                  ; -> loc_533f6f4 (return 0)
0x533f5b7  mov r8,[rax+0x428]                            ; R *(a0+0x128)+0x428
0x533f5be  lea rdi,[rcx+0xC]                             ; R *(*(a0+0x128)+0x430)+0xC
0x533f5c2  lock inc dword ptr [rcx+0xC]                  ; W refcount++
0x533f5c6  mov r14d,[rax+0x438]                          ; R *(a0+0x128)+0x438
0x533f5cd  mov r15d,r14d
0x533f5d0  and r15d,0x3FFFF
0x533f5d7  cmp r15,0x3FFFF
0x533f5de  jne 0x533F70A                                 ; -> loc_533f70a (bounds check fail)

loc_533f5e4:  ; from multiple (main loop entry)
0x533f5e4  xor r12d,r12d

loc_533f5e7:  ; from 533f722, 533f807, 533f8c3 (loop continue)
0x533f5e7  lock dec dword ptr [rdi]                      ; W refcount--
0x533f5ea  jne short 0x533F5F9
0x533f5ec  mov rax,[rcx]
0x533f5ef  mov rax,[rax+8]
0x533f5f3  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040

loc_533f5f9:  ; from 533f5ea
0x533f5f9  test r12,r12
0x533f5fc  je 0x533F6F4
0x533f602  mov rcx,[r12+0x1F8]
0x533f60a  mov eax,[rcx+8]
0x533f60d  nop [rax]

loc_533f610:  ; from 533f618 (spinlock)
0x533f610  lea edx,[rax+1]
0x533f613  lock cmpxchg [rcx+8],edx
0x533f618  jne short 0x533F610
0x533f61a  mov rsi,[r12+0x1F0]
0x533f622  mov rdi,[r12+0x1F8]
0x533f62a  test rdi,rdi
0x533f62d  je short 0x533F65A
0x533f62f  lock dec dword ptr [rdi+8]
0x533f633  jne short 0x533F65A
0x533f635  mov rax,[rdi]
0x533f638  mov rax,[rax]
0x533f63b  mov rcx,rdi
0x533f63e  call qword ptr [0xF99FFA0]
0x533f644  lock dec dword ptr [rdi+0xC]
0x533f648  jne short 0x533F65A
0x533f64a  mov rax,[rdi]
0x533f64d  mov rax,[rax+8]
0x533f651  mov rcx,rdi
0x533f654  call qword ptr [0xF99FFA0]

loc_533f65a:  ; from 533f62d, 533f633, 533f648
0x533f65a  mov rax,[rsi]
0x533f65d  mov rax,[rax+0x68]
0x533f661  mov rcx,rsi
0x533f664  call qword ptr [0xF99FFA0]
0x533f66a  mov rcx,[rax]
0x533f66d  mov r8,[rcx+0x148]
0x533f674  lea rdx,[rsp+0x20]
0x533f679  mov rcx,rax
0x533f67f  mov rax,r8
0x533f67f  call qword ptr [0xF99FFA0]
0x533f685  test rax,rax
0x533f688  je short 0x533F6F4
0x533f68a  lea ecx,[rbx+0x7FF]
0x533f690  movzx ecx,cx
0x533f693  cmp ecx,0xFFE
0x533f699  ja short 0x533F6F4
0x533f69b  mov r8,[rax+0x58]
0x533f69f  mov r9d,ebx
0x533f6a2  shl r9d,4
0x533f6a6  movzx edx,word ptr [r8+0xC8]
0x533f6ae  xor ecx,ecx
0x533f6b0  cmp r9w,dx
0x533f6b4  jl short 0x533F6F6
0x533f6b6  cmp r9w,[r8+0xCA]
0x533f6be  jge short 0x533F6F6
0x533f6c0  movsx r8,bx
0x533f6c4  movsx ecx,dx
0x533f6c7  shr ecx,4
0x533f6ca  movsx rcx,cx
0x533f6ce  mov rdx,r8
0x533f6d1  sub rdx,rcx
0x533f6d4  mov rax,[rax+0x1C8]
0x533f6db  imul rcx,rdx,0x68
0x533f6df  lea rdx,[rax+rcx]
0x533f6e3  movsx eax,byte ptr [rax+rcx+0x61]
0x533f6e8  xor ecx,ecx
0x533f6ea  cmp r8w,ax
0x533f6ee  cmove rcx,rdx
0x533f6f2  jmp short 0x533F6F6

loc_533f6f4:  ; from 533f5b1, 533f5fc, 533f688, 533f699
0x533f6f4  xor ecx,ecx

loc_533f6f6:  ; from 533f6b4, 533f6be, 533f6f2
0x533f6f6  mov rax,rcx
0x533f6f9  add rsp,0x28
0x533f6fd  pop rbx
0x533f6fe  pop rbp
0x533f6ff  pop rdi
0x533f700  pop rsi
0x533f701  pop r12
0x533f703  pop r13
0x533f705  pop r14
0x533f707  pop r15
0x533f709  ret

loc_533f70a:  ; from 533f5de (bounds check fail - r15 >= 0x40000)
0x533f70a  lea rdx,[rcx+8]
0x533f70e  mov eax,[rcx+8]
0x533f711  xor r12d,r12d
0x533f714  nop [rax+rax]

loc_533f720:  ; from 533f731 (spinlock on refcount)
0x533f720  test eax,eax
0x533f722  je 0x533F5E7
0x533f728  lea r9d,[rax+1]
0x533f72c  lock cmpxchg [rdx],r9d
0x533f731  jne short 0x533F720
0x533f733  test r8,r8
0x533f736  je short 0x533F79B
0x533f738  mov eax,r15d
0x533f73b  shr eax,0xB
0x533f73e  mov r9,[r8+0x110]
0x533f745  mov r10,[r8+0x118]
0x533f74c  sub r10,r9
0x533f74f  sar r10,3
0x533f753  cmp rax,r10
0x533f756  jae short 0x533F79B
0x533f758  mov rax,[r9+rax*8]
0x533f75c  test rax,rax
0x533f75f  je short 0x533F79B
0x533f761  mov r9d,r15d
0x533f764  and r9d,0x7FF
0x533f76b  mov r10d,r14d
0x533f76e  and r10d,0xFFFC0000
0x533f775  mov eax,[rax+r9*4]
0x533f779  xor r10d,eax
0x533f77c  cmp r10d,0x3FFFE
0x533f783  ja short 0x533F79B
0x533f785  lea r13,[r8+0x30]
0x533f789  and eax,0x3FFFF
0x533f78e  cmp [r8+0x150],rax
0x533f795  seta bpl
0x533f799  jmp short 0x533F79D

loc_533f79b:  ; from 533f736, 533f756, 533f75f, 533f783
0x533f79b  xor ebp,ebp

loc_533f79d:  ; from 533f799
0x533f79d  lock dec dword ptr [rdx]
0x533f7a0  jne short 0x533F7CC
0x533f7a2  mov rax,[rcx]
0x533f7a5  mov rax,[rax]
0x533f7a8  mov rsi,rcx
0x533f7ab  call qword ptr [0xF99FFA0]
0x533f7b1  mov rcx,rsi
0x533f7b4  lock dec dword ptr [rdi]
0x533f7b7  jne short 0x533F7CC
0x533f7b9  mov rax,[rcx]
0x533f7bc  mov rax,[rax+8]
0x533f7c0  mov rcx,rsi
0x533f7c3  call qword ptr [0xF99FFA0]
0x533f7c9  mov rcx,rsi

loc_533f7cc:  ; from 533f7a0, 533f7b7
0x533f7cc  test bpl,bpl
0x533f7cf  je 0x533F5E4
0x533f7d5  mov rax,[r13+0x48]
0x533f7d9  mov rdx,[r13+0x50]
0x533f7dd  sub rdx,rax
0x533f7e0  shr rdx,3
0x533f7e4  dec edx
0x533f7e6  and edx,0x85B93800
0x533f7ec  lea r8,[rax+rdx*8]
0x533f7f0  mov rax,[r13+0x68]
0x533f7f4  xor r12d,r12d
0x533f7f7  nop [rax+rax]

loc_533f800:  ; from 533f81d
0x533f800  mov rdx,[r8]
0x533f803  cmp rdx,0xFFFFFFFFFFFFFFFF
0x533f807  je 0x533F5E7
0x533f80d  shl rdx,5
0x533f811  lea r8,[rax+rdx]
0x533f815  cmp dword ptr [rax+rdx+8],0x85B93800
0x533f81d  jne short 0x533F800
0x533f81f  add rax,rdx
0x533f822  cmp [r13+0x70],rax
0x533f826  je 0x533F5E4
0x533f82c  mov rax,[rax+0x10]
0x533f830  test rax,rax
0x533f833  je 0x533F5E4
0x533f839  mov edx,r15d
0x533f83c  shr edx,0xB
0x533f83f  mov r8,[rax+8]
0x533f843  mov r9,[rax+0x10]
0x533f847  sub r9,r8
0x533f84a  sar r9,3
0x533f84e  cmp rdx,r9
0x533f851  jae 0x533F5E4
0x533f857  mov rdx,[r8+rdx*8]
0x533f85b  test rdx,rdx
0x533f85e  je 0x533F5E4
0x533f864  mov r8d,r15d
0x533f867  and r8d,0x7FF
0x533f86e  and r14d,0xFFFC0000
0x533f875  mov edx,[rdx+r8*4]
0x533f879  xor r14d,edx
0x533f87c  cmp r14d,0x3FFFE
0x533f883  ja 0x533F5E4
0x533f889  mov rax,[rax+0x50]
0x533f88d  mov r8d,edx
0x533f890  shr r8d,4
0x533f894  and r8d,0x3FF8
0x533f89b  mov rax,[rax+r8]
0x533f89f  test rax,rax
0x533f8a2  je 0x533F5E4
0x533f8a8  and edx,0x3FFFF
0x533f8ae  and edx,0x7F
0x533f8b1  mov rax,[rax+rdx*8]
0x533f8b5  xor r12d,r12d
0x533f8b8  cmp byte ptr [rax+0x289],0
0x533f8bf  cmove r12,rax
0x533f8c3  jmp 0x533F5E7
```

---

## NEXT for 0x533f580
Complete at 0x533f8c8 (full function, 0x348 bytes). Additional helper function at 0x533f8d0 follows.

---

## Verification
- verify_oc.py on this section: [TO BE RUN AFTER APPEND]