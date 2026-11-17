## NEXT
DONE (orchestrator review 2026-11-16: verify_oc 1410/1420, 9 shifted lines near 0xc4bca4, 28 UNVERIFIED gaps listed; unit's 'Render Item Iterator' label for 0xBC60D10 is wrong, it is the Encoder reset)

## Function Analyses: Callees of 0x568CD90 (Scene/HUD per-view task body)

### 1. sub_BCC1A30 (0xBCC1A30..0xBCC1AD0) — Lambda Capture Initialization

**Role [I]**: Initializes per-pass lambda captures for the Scene/HUD task. Iterates over a range of capture objects ([rcx+0x50]..[rcx+0x58]) and dispatches to type-specific handlers (0xBC5DDB0, 0xBC5DAF0, 0xBC5DED0) based on a type byte at [rdi+0x10]. Called once per view before the item loop.

**Strings**: None (rvastr returns only instruction bytes).

**Callees in order**:
1. 0xBC5DDB0 — capture handler type 0 (at 0xBCC1A5A `call 0xBC5DDB0`)
2. 0xBC5DAF0 — capture handler type 1 (at 0xBCC1A9A `call 0xBC5DAF0`)
3. 0xBC5DED0 — capture handler type 2 (at 0xBCC1ABC `call 0xBC5DED0`)
4. 0x1166E0 — fail-fast/abort on unknown type (at 0xBCC1ACB `call 0x1166E0`)

**[reg+off] Reads/Writes into arguments**:
- rcx (arg1): capture array descriptor
  - Read [rcx+0x50] (qword, R) at 0xBCC1A37 `mov rdi,[rcx+0x50]` — begin pointer
  - Read [rcx+0x58] (qword, R) at 0xBCC1A3B `mov rbx,[rcx+0x58]` — end pointer
- rdx (arg2): destination/context pointer (passed to handlers as rcx)
  - Saved to rsi at 0xBCC1A44 `mov rsi,rdx` — forwarded to all handler calls as rcx
- rdi (iteration cursor): [rdi+0x10] (byte, R) at 0xBCC1A73 `movzx eax,byte ptr [rdi+0x10]` — capture type discriminator
- rdi+0x0C/0x0D (bytes, R) at 0xBCC1A80/0xBCC1A84 — extra args for type 1 handler
- Write: none to arg objects; handlers receive rsi (original rdx) as their rcx

**Return value**: None (void, ret at 0xBCC1ACA)

**Invocation from 0x568CD90**:
- Call site: L_568cd90.txt line 82 (`0x568CF1D  mov rcx,r14` / `0x568CF20  call 0xBCC1A30`)
- Registers at call:
  - rcx = r14 = [rbx+0x14C] (lambda capture array pointer from task object)
  - rdx = [rbp+0x50] (address of stack capture buffer at rbp+0x50)
  - r8/r9 = unused

---

### 2. sub_BC60D10 (0xBC60D10..0xBC60F0B) — Render Item Iterator / State Initializer

**Role [I]**: Initializes a render item iterator/state object (rcx) with default values, a magic constant pattern, and a lookup table. If a global pointer at [rcx+0x680] is non-null, walks a 0x410-byte buffer calling an indirect function at [0xF99FFA0] for each 0x10-byte chunk. Returns initialized iterator state in rcx.

**Strings**: None (rvastr returns only instruction bytes).

**Callees in order**:
1. 0xEEC6ED0 — memset/zero fill fallback (at 0xBC60EE7 `call 0xEEC6ED0`)
2. [0xF99FFA0] — indirect per-chunk callback (at 0xBC60EB1 `call qword ptr [0xF99FFA0]`)

**[reg+off] Reads/Writes into arguments**:
- rcx (arg1, also rsi): iterator state struct (size >= 0x688)
  - Write [rcx+0x6AD] (byte, W) = 0 at 0xBC60D21 `mov byte ptr [rcx+0x6AD],0`
  - Write [rcx+0x60] (qword, W) = 0x10000500000001F at 0xBC60D32
  - Write [rcx+0x68] (qword, W) = 0 at 0xBC60D36
  - Write [rcx+0x70] (16 bytes, W) = xmm0 (zero) at 0xBC60D41
  - Write [rcx+0x80] (16 bytes, W) = [0xF08EF70] at 0xBC60D4C
  - Write [rcx+0x90] (qword, W) = 0x100000000 at 0xBC60D5D
  - Write [rcx+0x98] (qword, W) = 0x1FFFF00000000 at 0xBC60D6E
  - Write [rcx+0xA2] (byte, W) = 0 at 0xBC60D7C
  - Write [rcx+0xA0] (word, W) = 0xFFFF at 0xBC60D7C
  - Write [rcx+0xA3] (word, W) = 0xFF00 at 0xBC60D85
  - Write [rcx+0x40] (qword, W) = 0xFFFFFFFF00000000 at 0xBC60D98
  - Write [rcx+0xB4] (qword, W) = -1 at 0xBC60D9C
  - Write [rcx+0xA8] (dword, W) = 0x7FFFFFFF at 0xBC60DA7
  - Write [rcx+0xAC..0xE3] (multiple fields, W) — zero/init loop 0xBC60E20..0xBC60E63
  - Read [rcx+0x680] (qword, R) at 0xBC60E65 — global buffer pointer
  - Write [rcx+0x688] (byte, W) = 1 at 0xBC60EF6 — done flag

**Return value**: rcx (initialized iterator state) — caller uses rcx at 0x568CF7A return

**Invocation from 0x568CD90**:
- Call site: L_568cd90.txt line 97 (`0x568CF76  mov rcx,[r14+0x10]` / `0x568CF7A  call 0xBC60D10`)
- Registers at call:
  - rcx = [r14+0x10] where r14 = [rbx+0x14C] (task+0x14C, points to iterator state)
  - rdx/r8/r9 = unused (function ignores them)

---

### 3. sub_568DB90 (0x568DB90..0x568DC0F) — Scene Pass Jump Table Dispatch

**Role [I]**: Jump table dispatcher for Scene render passes. Entry rcx selects a pass handler via jump table at 0xF25D03C. Slow path (case 0) manages a growable buffer (r8) and calls 0xE935700 for allocation; case 1 calls 0xE935700 directly; case 2 triggers fail-fast via [0xF9A8C78]. Cited lines: 0x568DB95 `lea rax,[0xF25D03C]` / 0x568DBA3 `jmp rcx` / 0x568DBA5 `mov rcx,[r8]` / 0x568DBDA `mov rsi,r8` / 0x568DBDD `call 0xE935700` / 0x568DBF6 `mov qword ptr [rsp+0x20],0` / 0x568DC09 `call qword ptr [0xF9A8C78]`.

**Strings Referenced**: None (rvastr returns only instruction bytes: `b'VH\x83\xec0H\x8d\x05\xa0\xf4\xbc\tHc\x0c\x88H\x01\xc1\xff\xe1I\x8b\x08H\x85\xc9tCI\x8bP\x10H)\xcaH\x81\xfa'`).

**Callees in Order**:
1. Jump table 0xF25D03C[rcx*4] — per-pass entry (at 0x568DB9C `movsxd rcx,[rax+rcx*4]` / 0x568DBA3 `jmp rcx`)
2. 0xE935700 — buffer allocation/growth (at 0x568DBDD `call 0xE935700`, cases 0/1 slow path)
3. [0xF9A8C78] — fail-fast/abort (at 0x568DC09 `call qword ptr [0xF9A8C78]`, case 2)

**[reg+off] Reads/Writes**:
- rcx (arg1): pass index (input), becomes jump target address
  - Read at 0x568DB9C `movsxd rcx,[rax+rcx*4]` — sign-extend index, fetch offset from jump table
- r8 (arg3): buffer descriptor (slow path cases 0/1 only)
  - Read [r8+0x0] (qword, R) at 0x568DBA5 `mov rcx,[r8]` — buffer base pointer
  - Read [r8+0x10] (qword, R) at 0x568DBAD `mov rdx,[r8+0x10]` — buffer end pointer
  - Write [r8+0x0] (16 bytes, W) at 0x568DBE5 `movups [rsi],xmm0` (rsi=r8) — zero buffer header
  - Write [r8+0x10] (qword, W) at 0x568DBE8 `mov qword ptr [rsi+0x10],0` — zero buffer end
- rdx (arg2): used as scratch in slow path
  - Read/Write at 0x568DBB1 `sub rdx,rcx` / 0x568DBD1 `add rdx,0x27` / 0x568DBD5 `mov rcx,rax` — size calc for 0xE935700
- Stack [rsp+0x20] (qword, W) at 0x568DBF6 `mov qword ptr [rsp+0x20],0` — error path arg for fail-fast

**Return Value**: Does not return normally from jump table dispatch (jmp to per-pass function at 0x568DBA3). Slow path (cases 0/1) returns void via `ret` at 0x568DBF5 after zeroing buffer. Case 2 never returns (calls fail-fast then int3 at 0x568DC0F).

**Invocation from 0x568CD90**:
1. Direct call at 0x568D21F (L_568cd90.txt line 245 / L_568cd70.txt line 263):
   - `0x568D210 movsx rcx,byte ptr [r12+0x18]` — pass index from capture object +0x18
   - `0x568D216 inc rcx` — index += 1
   - `0x568D219 mov rdx,rsi` — rdx = rsi = [rbp-0x50] (local buffer descriptor)
   - `0x568D21C mov r8,r12` — r8 = r12 (capture object pointer, 0x20-byte struct)
   - `0x568D21F call 0x568DB90`
2. Indirect via 0xE86D7F0 at 0xE86DE89 (L_e86d7f0.txt line 374):
   - `0xE86DE76 movsx rcx,byte ptr [rbp+0x18]` — pass index from rbp+0x18 (rbp = [rsp+0x98])
   - `0xE86DE7A cmp rcx,3` / `0xE86DE80 inc rcx` — skip if 3, else index += 1
   - `0xE86DE83 mov rdx,r14` — rdx = r14 (scratch buffer pointer)
   - `0xE86DE86 mov r8,rbp` — r8 = rbp (command record pointer)
   - `0xE86DE89 call 0x568DB90`
3. Indirect via 0xE86D7F0 at 0xE86E2D5 (L_e86d7f0.txt line 603):
   - `0xE86E2C2 movsx rcx,byte ptr [rbp+0x18]` — pass index from rbp+0x18
   - `0xE86E2C6 cmp rcx,3` / `0xE86E2CC inc rcx` — skip if 3, else index += 1
   - `0xE86E2CF mov rdx,r13` — rdx = r13 (scratch buffer pointer)
   - `0xE86E2D2 mov r8,rbp` — r8 = rbp (command record pointer)
   - `0xE86E2D5 call 0x568DB90`
4. Indirect via 0xE86D7F0 at 0xE86E585 (L_e86d7f0.txt line 763):
   - `0xE86E571 movsx rcx,byte ptr [rdi+0x18]` — pass index from rdi+0x18 (rdi = [rsp+0x98])
   - `0xE86E575 cmp rcx,2` / `0xE86E57A inc rcx` — skip if 2 (separate path), else index += 1
   - `0xE86E582 lea rdx,[rsp+0x90]` — rdx = local buffer on stack
   - `0xE86E585 call 0x568DB90`

---

### 4. sub_568D480 (0x568D480..0x568D740) — Final Per-View Lambda / Capture Comparator

**Role [I]**: Iterates over a range of capture objects ([rcx]..[rcx+8]) comparing each against a key (pointed by r8) using a detailed field-by-field comparison (0x58-byte records). On match, calls 0x568D750 with the matched capture and key. Used as a final per-view cleanup/notification lambda. (L_568d480.txt:49-50 `mov r15,[rcx]` / `mov r14,[rcx+8]` — range begin/end; 0x568D4F9-0x568D6BE — comparison loop; 0x568D6E8 `call 0x568D750`)

**Strings Referenced**: `python tools/sigs/rvastr.py 0x568d480` returns raw instruction bytes only (`b'AWAVATVWSH\x83\xecHH...'`); no readable strings referenced.

**Callees in Order**:
1. 0x568D750 — matched capture handler (at 0x568D6E8 `call 0x568D750`); receives rcx=rsi (key), rdx=rbx (stack temp range [rsp+0x28..0x38])
2. 0xE951550 — stack cookie check (__security_check_cookie) at 0x568D73B `call 0xE951550` (epilogue guard)

**[reg+off] Reads/Writes**:
- rcx (arg1): capture range descriptor (struct { qword begin; qword end; })
  - Read [rcx+0x0] (qword, R) at 0x568D49C `mov r15,[rcx]` — range begin
  - Read [rcx+0x8] (qword, R) at 0x568D4A3 `mov r14,[rcx+8]` — range end
  - Read [rcx+0x0] (dword, R) at 0x568D524 `mov edx,[rcx]` — key field 0 (match ID)
  - Read [rcx+0x4] (byte, R) at 0x568D550 `cmp r9b,[rcx+4]` — key field 1
  - Read [rcx+0x8] (dword, R) at 0x568D55E `cmp r9d,[rcx+8]` — key field 2
  - Read [rcx+0xC] (byte, R) at 0x568D56D `cmp r9b,[rcx+0xC]` — key field 3
  - Read [rcx+0xD] (byte, R) at 0x568D57C `cmp r9b,[rcx+0xD]` — key field 4
  - Read [rcx+0xE] (byte, R) at 0x568D58B `cmp r9b,[rcx+0xE]` — key field 5
  - Read [rcx+0x10] (dword, R) at 0x568D599 `cmp r9d,[rcx+0x10]` — key field 6
  - Read [rcx+0x14] (byte, R) at 0x568D5A8 `cmp r9b,[rcx+0x14]` — key field 7
  - Read [rcx+0x18] (float, R) at 0x568D5B8 `ucomiss xmm0,[rcx+0x18]` — key field 8
  - Read [rcx+0x1C] (float, R) at 0x568D5CE `ucomiss xmm0,[rcx+0x1C]` — key field 9
  - Read [rcx+0x20] (float, R) at 0x568D5E4 `ucomiss xmm0,[rcx+0x20]` — key field 10
  - Read [rcx+0x24] (float, R) at 0x568D5FA `ucomiss xmm0,[rcx+0x24]` — key field 11
  - Read [rcx+0x28] (dword, R) at 0x568D60E `cmp r9d,[rcx+0x28]` — key field 12
  - Read [rcx+0x2C] (float, R) at 0x568D61E `ucomiss xmm0,[rcx+0x2C]` — key field 13
  - Read [rcx+0x30] (float, R) at 0x568D634 `ucomiss xmm0,[rcx+0x30]` — key field 14
  - Read [rcx+0x34] (byte, R) at 0x568D673 `cmp r9b,[rcx+0x34]` — key field 15
  - Read [rcx+0x38] (dword, R) at 0x568D67D `cmp r9d,[rcx+0x38]` — key field 16
  - Read [rcx+0x3C] (dword, R) at 0x568D687 `cmp r9d,[rcx+0x3C]` — key field 17
  - Read [rcx+0x40] (dword, R) at 0x568D691 `cmp r9d,[rcx+0x40]` — key field 18
  - Read [rcx+0x44] (byte, R) at 0x568D69C `cmp r9b,[rcx+0x44]` — key field 19
  - Read [rcx+0x48] (dword, R) at 0x568D6A6 `cmp r9d,[rcx+0x48]` — key field 20
  - Read [rcx+0x4C] (dword, R) at 0x568D6B0 `cmp r9d,[rcx+0x4C]` — key field 21
  - Read [rcx+0x50] (dword, R) at 0x568D6BA `cmp r8d,[rcx+0x50]` — key field 22
  - Read [rcx+0x54] (byte, R) at 0x568D649 `cmp r9b,[rcx+0x54]` — key field 23 (flag)
  - Read [rcx+0x55] (byte, R) at 0x568D65D `cmp r9b,[rcx+0x55]` — key field 24 (conditional)
  - Read [rcx+0x56] (byte, R) at 0x568D668 `cmp r9b,[rcx+0x56]` — key field 25 (conditional)
- rdx (arg2): unused directly (caller passes [rbp+0x137], a stack flags byte; not read)
- r8 (arg3): key record pointer (0x58-byte record from [r9+0x738] indexed by word at [r15+0x2C])
  - Read [r8+0x4] (byte, R) at 0x568D54B `movzx r9d,byte ptr [r8+4]` — first compared field
  - Read [r8+0x8] (dword, R) at 0x568D55A `mov r9d,[r8+8]`
  - Read [r8+0xC] (byte, R) at 0x568D568 `movzx r9d,byte ptr [r8+0xC]`
  - Read [r8+0xD] (byte, R) at 0x568D577 `movzx r9d,byte ptr [r8+0xD]`
  - Read [r8+0xE] (byte, R) at 0x568D586 `movzx r9d,byte ptr [r8+0xE]`
  - Read [r8+0x10] (dword, R) at 0x568D595 `mov r9d,[r8+0x10]`
  - Read [r8+0x14] (byte, R) at 0x568D5A3 `movzx r9d,byte ptr [r8+0x14]`
  - Read [r8+0x18] (float, R) at 0x568D5B2 `movss xmm0,[r8+0x18]`
  - Read [r8+0x1C] (float, R) at 0x568D5C8 `movss xmm0,[r8+0x1C]`
  - Read [r8+0x20] (float, R) at 0x568D5DE `movss xmm0,[r8+0x20]`
  - Read [r8+0x24] (float, R) at 0x568D5F4 `movss xmm0,[r8+0x24]`
  - Read [r8+0x28] (dword, R) at 0x568D60A `mov r9d,[r8+0x28]`
  - Read [r8+0x2C] (float, R) at 0x568D618 `movss xmm0,[r8+0x2C]`
  - Read [r8+0x30] (float, R) at 0x568D62E `movss xmm0,[r8+0x30]`
  - Read [r8+0x34] (byte, R) at 0x568D66E `movzx r9d,byte ptr [r8+0x34]`
  - Read [r8+0x38] (dword, R) at 0x568D679 `mov r9d,[r8+0x38]`
  - Read [r8+0x3C] (dword, R) at 0x568D683 `mov r9d,[r8+0x3C]`
  - Read [r8+0x40] (dword, R) at 0x568D68D `mov r9d,[r8+0x40]`
  - Read [r8+0x44] (byte, R) at 0x568D697 `movzx r9d,byte ptr [r8+0x44]`
  - Read [r8+0x48] (dword, R) at 0x568D6A2 `mov r9d,[r8+0x48]`
  - Read [r8+0x4C] (dword, R) at 0x568D6AC `mov r9d,[r8+0x4C]`
  - Read [r8+0x50] (dword, R) at 0x568D6B6 `mov r8d,[r8+0x50]`
  - Read [r8+0x54] (byte, R) at 0x568D644 `movzx r9d,byte ptr [r8+0x54]`
  - Read [r8+0x55] (byte, R) at 0x568D658 `movzx r9d,byte ptr [r8+0x55]` (conditional)
  - Read [r8+0x56] (byte, R) at 0x568D663 `movzx r9d,byte ptr [r8+0x56]` (conditional)
- r9 (arg4): unused
- Stack temps at [rsp+0x28..0x38] (W) at 0x568D6D3-0x568D6DD: `{r15, r14, r15}` passed to 0x568D750 as rdx

**Return Value**: None (void). Returns at 0x568D732 after stack cookie check; 0x568D733-0x568D740 calls __security_check_cookie on mismatch then int3.

**Invocation from 0x568CD90**:
- Call site: L_568cd90.txt line 307 (`0x568D349  call 0x568D480`)
- Registers at call:
  - rcx = [rbp+0x88] = r14 (current item capture pointer, from 0x568D0FA `mov [rbp+0x88],r14`)
  - rdx = [rbp+0x137] (stack byte at rbp+0x137, flags; set up at 0x568D33F `lea rdx,[rbp+0x137]`)
  - r8 = r15 = [rbp-0x50] (local buffer base, from 0x568D346 `mov r8,r15` / 0x568D28E `mov [rbp-0x50],rax`)
  - r9 = unused (not set before call)

---

### 5. sub_C4BBA0 (0xC4BBA0..0xC4BE69) — Per-Pass Draw Function (Binary Search + Memcmp)

**Role [I]**: Performs a binary search over a sorted array of 0x30-byte records (range rdx..rdi) to find a record matching a key (r9, length in [r9+0x20] flag). On exact match, copies the matched record to output (rcx). Uses 0xEEC6EB0 for memcmp. The magic constant 0xAAAAAAAAAAAAAAAB is used for division-by-3 via multiplication.

**Strings**: None (rvastr returns only instruction bytes).

**Callees in order**:
1. 0xEEC6EB0 — memcmp (called 4x: at 0xC4BC8E, 0xC4BCBD, 0xC4BD5A, 0xC4BE18)

**[reg+off] Reads/Writes into arguments**:
- rcx (arg1): output pointer (result record destination)
  - Write [rcx] (qword, W) = matched record base at 0xC4BE52 `mov [rax],r15`
  - Write [rcx+8] (qword, W) = matched record end at 0xC4BE55 `mov [rax+8],r14`
- rdx (arg2): search range begin (r14/r15)
  - Read [rdx]..[rdx+0x2F] (multiple, R) during binary search comparisons
- r8 (arg3): search range end (rdi)
- r9 (arg4): key record pointer
  - Read [r9+0x20] (qword, R) at 0xC4BBD9 `cmp qword ptr [r9+0x20],0x10` — length flag
  - Read key fields [r9+8]..[r9+0x18] (R) for memcmp
- Stack [rsp+0x28..0x38]: temporaries for range/key pointers

**Return value**: None (output via rcx); matched record bounds in [rcx], [rcx+8]

**Invocation from 0x568CD90**:
- Call site: L_568cd90.txt line 199 (`0x568D13C  call 0xC4BBA0`)
- Registers at call:
  - rcx = r15 = [rbp-0x50] (output buffer for matched draw params)
  - rdx = rbx = [rbp+0xA8] (search range end, updated per iteration)
  - r8 = [rsi+0x2F8] (array base from render item)
  - r9 = rbx (same as rdx, key pointer for search)

---

### 6. sub_E86D7F0 (0xE86D7F0..0xE86E7C5) — Encoder Submit / Draw Call Dispatcher

**Role [I]**: Main bgfx encoder submit function. Iterates over multiple command buffers (transient vertex/index, uniforms, draw calls, compute, blit, etc.) and submits them to the bgfx encoder via a series of indirect calls (0xBC5E120, 0xE86EEF0, 0xE86FD80, 0xE86FB90, 0xE86F700, 0xE86E7D0, 0x568DB90). Handles multiple command types distinguished by bytes at offsets 0x18, 0x24, 0x30, 0x34 in command records. Returns success flag in al.

**Strings**: None (rvastr returns only instruction bytes).

**Callees in order** (major ones observed):
1. 0x13622E0 — bounds check / grow buffer (at 0xE86D89C, 0xE86DAC1)
2. 0x1195A0 — command validation (at 0xE86D8F7, 0xE86DAEF, 0xE86DB62)
3. 0xBC5E120 — transient buffer submit (at 0xE86D98B, 0xE86D9AD)
4. 0xE86EEF0 — draw/uniform submit (at 0xE86DE64, 0xE86E2B0, 0xE86E55F)
5. 0xE86FD80 — compute submit (at 0xE86DEEF)
6. 0xE86FB90 — blit submit (at 0xE86E007, 0xE86E649)
7. 0xE86F700 — generic encoder call (at 0xE86E141, 0xE86E466, 0xE86E725, 0xE86E456, 0xE86E787)
8. 0xE86E7D0 — per-draw validation (at 0xE86DBDB, 0xE86DC5D, 0xE86DD4F)
9. 0x568DB90 — Scene pass dispatch (at 0xE86DE89, 0xE86E2D5, 0xE86E585)
10. 0xC985870 — hash/combine (at 0xE86DE0C, 0xE86E25A)
11. 0x1166E0 — fail-fast (at 0xE86DD81)
12. 0x78ED0 / 0xB432E0 — error paths (at 0xE86E7AB, 0xE86E7B0)
13. 0xE951550 — stack cookie (at 0xE86E7C0)

**[reg+off] Reads/Writes into arguments**:
- rcx (arg1): encoder context / submit state
  - Read [rcx+0x398], [rcx+0x370], [rcx+0x380] (R) at 0xE86D92E..0xE86D94A
  - Read [rcx+0x52], [rcx+0x48], [rcx+0x62], [rcx+0x58], [rcx+0x72], [rcx+0x68] (R) — command buffer counts/pointers
- rdx (arg2): command buffer descriptor (rbp+0x10..0x18)
  - Read/Write [rdx], [rdx+8], [rdx+0x10], [rdx+0x18] (R/W) — buffer pointers
- r8 (arg3): scratch buffer / local state (rbp-0x50..)
- r9 (arg4): additional context (varies)
- [rsp+0x130] (stack arg): main render view/context pointer
  - Read extensively for buffer pointers and counts
- [rsp+0x138] (stack arg): rsi (global renderer state)

**Return value**: al = success (1) or failure (0) at 0xE86E334 `and dil,1` / `0xE86E336  mov eax,edi`

**Invocation from 0x568CD90**:
- Call site: L_568cd90.txt line 260 (`0x568D25A  lea r8,[rbx+0x38]` / `0x568D25D  lea r9,[rbp+0xD0]` / `0x568D264  call 0xE86D7F0`)
- Registers at call:
  - rcx = [rsp+0x28] = [rbp+0x50] (lambda capture buffer)
  - rdx = rbx = [rbp+0xA8] (current draw item pointer, advanced by 0x28 each iteration)
  - r8 = [rbx+0x38] (draw item + 0x38, per-pass data)
  - r9 = [rbp+0xD0] (r14 = [rbx+0x14C], lambda capture array)
  - Stack: [rsp+0x20] = rcx, [rsp+0x28] = [rbp+0x50], cl=1 (flag)

---

## Per-Item Loop Analysis (0x568CD90, 0x568CF80..0x568D350)

**What the loop iterates over**:
The loop at 0x568D051..0x568D350 iterates over **render items** in a linked list / array structure. Key evidence:
- `r14` holds the current item pointer, initialized from `[rbx+0x68]` (0x568CF35 `mov rbx,[rbx+0x68]`, 0x568CF6F `mov [rbp+0xB0],r14`)
- `r13` holds the end marker, computed as `rsi + rdi*3*8` (0x568CFF1 `lea rax,[rdi+rdi*2]` / `0x568CFF9  lea r13,[rsi+rax*8]`) where `rdi=[rbx+0x70]` (lambda capture array) and `rsi=[rbx+0x48]` (base pointer)
- Loop advances `r14` by 0x18 bytes per iteration (0x568D062 `lea rax,[rdx+rdx*2]` / `0x568D066  lea r14,[r14+rax*8]` = +0x18) and compares against `r13`
- Each item at `r14` has: `[r14+8]` (pointer, checked null at 0x568D077), `[r14+0x10]` (pointer, checked null at 0x568D080), `[r14+0x18+...]` (draw command data)

**What each iteration submits (as far as instructions show)**:
Each iteration performs the following submission sequence:
1. **0xC4BBA0** (0x568D13C) — Binary search / lookup of per-pass draw parameters in a sorted array (from `[rsi+0x2F8]`). Output to `[rbp-0x50]`.
2. **0x568DB90** (0x568D21F) — **Scene pass dispatch** via jump table 0xF25D03C. This is the **bgfx draw/encoder call entry point** for the current pass. The jump table leads to `sub_5698490`/`sub_5698710` which call `sub_5698510` (main per-pass draw logic using bgfx encoder).
3. **0xE86D7F0** (0x568D264) — **Encoder submit / draw call dispatcher**. This function iterates command buffers and issues bgfx encoder calls (transient buffers, uniforms, draw, compute, blit) via indirect calls to 0xBC5E120, 0xE86EEF0, 0xE86FD80, 0xE86FB90, 0xE86F700, and **recursively calls 0x568DB90** for nested pass dispatches.

**Conclusion**: Each iteration submits **one render item's draw commands for the current Scene pass** via a two-stage submission: (1) 0x568DB90 dispatches to the per-pass bgfx draw function (0x5698510), and (2) 0xE86D7F0 flushes encoder command buffers. The bgfx draw call itself occurs inside the 0x5698510 callee chain (not directly visible in 0x568CD90 instructions).

---

## UNVERIFIED Gaps

- [UNVERIFIED: 0xBC5DDB0] Capture handler type 0 — exact signature and effect on capture buffer
- [UNVERIFIED: 0xBC5DAF0] Capture handler type 1 — exact signature and effect
- [UNVERIFIED: 0xBC5DED0] Capture handler type 2 — exact signature and effect
- [UNVERIFIED: 0xBC5E120] Transient buffer submit — bgfx encoder call variant
- [UNVERIFIED: 0xE86EEF0] Draw/uniform submit — bgfx encoder call variant
- [UNVERIFIED: 0xE86FD80] Compute submit — bgfx encoder call variant
- [UNVERIFIED: 0xE86FB90] Blit submit — bgfx encoder call variant
- [UNVERIFIED: 0xE86F700] Generic encoder call — which bgfx function (bgfx::Encoder::submit?)
- [UNVERIFIED: 0xE86E7D0] Per-draw validation — what it checks
- [UNVERIFIED: 0x5698510] Main per-pass draw logic — exact bgfx calls (listing pending)
- [UNVERIFIED: 0x5698850] Per-pass helper — listing pending
- [UNVERIFIED: 0x5698A40] Per-pass helper — listing pending
- [UNVERIFIED: 0x567ACF0] Shared draw helper — listing pending
- [UNVERIFIED: 0x567AE50] Shared draw helper — listing pending
- [UNVERIFIED: 0x567ADE0] Shared draw helper — listing pending
- [UNVERIFIED: 0x3839220] Unknown helper — listing pending
- [UNVERIFIED: 0x1166E0] Fail-fast/abort — confirm RaiseFailFastException
- [UNVERIFIED: 0x13622E0] Bounds check / grow — exact behavior
- [UNVERIFIED: 0x1195A0] Command validation — exact behavior
- [UNVERIFIED: 0xC985870] Hash/combine — exact behavior
- [UNVERIFIED: 0xE935700] Buffer allocation — exact behavior
- [UNVERIFIED: 0xE951550] Stack cookie check — __security_check_cookie
- [UNVERIFIED: 0xEEC6EB0] memcmp — confirmed
- [UNVERIFIED: 0xEEC6ED0] memset — confirmed
- [UNVERIFIED: 0xF99FFA0] Indirect callback in 0xBC60D10 — target unknown
- [UNVERIFIED: 0xF9A8C78] Fail-fast indirect — target unknown
- [UNVERIFIED: 0xF25D03C] Jump table — exact mapping of 20 entries to pass functions
- [UNVERIFIED: 0xF25D050/0xF25D070/0xF25D084] Internal jump tables in 0x5698... — exact targets

---

## TOOL REQUESTS

- `dumplist.py` for 0xBC5DDB0, 0xBC5DAF0, 0xBC5DED0, 0xBC5E120, 0xE86EEF0, 0xE86FD80, 0xE86FB90, 0xE86F700, 0xE86E7D0, 0x5698510, 0x5698850, 0x5698A40, 0x567ACF0, 0x567AE50, 0x567ADE0, 0x3839220, 0x13622E0, 0x1195A0, 0xC985870, 0xE935700
- `casewalk.py` on L_568db90.txt (jump table 0xF25D03C) for full pass enumeration
- `stores.py` on L_e86d7f0.txt for [reg+off] extraction in encoder submit
- `rvastr.py` on all UNVERIFIED RVAs to check for string references

---

## Verification: Quoted Instructions (for verify_oc.py)

### sub_BCC1A30 (0xBCC1A30..0xBCC1AD0)
0xBCC1A30  push rsi
0xBCC1A31  push rdi
0xBCC1A32  push rbx
0xBCC1A33  sub rsp,0x30
0xBCC1A37  mov rdi,[rcx+0x50]
0xBCC1A3B  mov rbx,[rcx+0x58]
0xBCC1A3F  cmp rdi,rbx
0xBCC1A42  je short 0xBCC1AC3
0xBCC1A44  mov rsi,rdx
0xBCC1A47  add rdi,0x18
0xBCC1A4B  jmp short 0xBCC1A6F
0xBCC1A4D  nop [rax]
0xBCC1A50  lea r8,[rdi-0x10]
0xBCC1A54  mov rcx,rsi
0xBCC1A57  xor r9d,r9d
0xBCC1A5A  call 0xBC5DDB0
0xBCC1A5F  lea rax,[rdi+0x30]
0xBCC1A63  add rdi,0x18
0xBCC1A67  cmp rdi,rbx
0xBCC1A6A  mov rdi,rax
0xBCC1A6D  je short 0xBCC1AC3
0xBCC1A6F  lea rdx,[rdi-0x18]
0xBCC1A73  movzx eax,byte ptr [rdi+0x10]
0xBCC1A77  cmp eax,1
0xBCC1A7A  jg short 0xBCC1AB0
0xBCC1A7C  test eax,eax
0xBCC1A7E  jne short 0xBCC1A50
0xBCC1A80  movzx eax,byte ptr [rdi+0xC]
0xBCC1A84  movzx ecx,byte ptr [rdi+0xD]
0xBCC1A88  lea r8,[rdi-0x10]
0xBCC1A8C  mov [rsp+0x28],cl
0xBCC1A90  mov [rsp+0x20],al
0xBCC1A94  mov rcx,rsi
0xBCC1A97  mov r9,rdi
0xBCC1A9A  call 0xBC5DAF0
0xBCC1A9F  jmp short 0xBCC1A5F
0xBCC1AA1  nop [rax+rax]
0xBCC1AB0  cmp eax,2
0xBCC1AB3  jne short 0xBCC1ACB
0xBCC1AB5  lea r8,[rdi-0x10]
0xBCC1AB9  mov rcx,rsi
0xBCC1ABC  call 0xBC5DED0
0xBCC1AC1  jmp short 0xBCC1A5F
0xBCC1AC3  add rsp,0x30
0xBCC1AC7  pop rbx
0xBCC1AC8  pop rdi
0xBCC1AC9  pop rsi
0xBCC1ACA  ret
0xBCC1ACB  call 0x1166E0
0xBCC1AD0  int3

### sub_BC60D10 (0xBC60D10..0xBC60F0B)
0xBC60D10  push r14
0xBC60D12  push rsi
0xBC60D13  push rdi
0xBC60D14  push rbx
0xBC60D15  sub rsp,0x48
0xBC60D19  movaps [rsp+0x30],xmm6
0xBC60D1E  mov rsi,rcx
0xBC60D21  mov byte ptr [rcx+0x6AD],0
0xBC60D28  mov rax,0x10000500000001F
0xBC60D32  mov [rcx+0x60],rax
0xBC60D36  mov qword ptr [rcx+0x68],0
0xBC60D3E  xorps xmm0,xmm0
0xBC60D41  movaps [rcx+0x70],xmm0
0xBC60D45  movaps xmm0,[0xF08EF70]
0xBC60D4C  movaps [rcx+0x80],xmm0
0xBC60D53  mov rax,0x100000000
0xBC60D5D  mov [rcx+0x90],rax
0xBC60D64  mov rax,0x1FFFF00000000
0xBC60D6E  mov [rcx+0x98],rax
0xBC60D75  mov byte ptr [rcx+0xA2],0
0xBC60D7C  mov word ptr [rcx+0xA0],0xFFFF
0xBC60D85  mov word ptr [rcx+0xA3],0xFF00
0xBC60D8E  mov rax,0xFFFFFFFF00000000
0xBC60D98  mov [rcx+0x40],rax
0xBC60D9C  mov qword ptr [rcx+0xB4],0xFFFFFFFFFFFFFFFF
0xBC60DA7  mov dword ptr [rcx+0xA8],0x7FFFFFFF
0xBC60DB1  mov qword ptr [rcx+0xAC],0
0xBC60DBC  mov qword ptr [rcx+0xC0],0
0xBC60DC7  mov dword ptr [rcx+0xC8],0
0xBC60DD1  mov qword ptr [rcx+0xD0],0
0xBC60DDC  mov dword ptr [rcx+0xD8],0
0xBC60DE6  mov word ptr [rcx+0xE0],0
0xBC60DEF  mov byte ptr [rcx+0xE2],0xFF
0xBC60DF6  mov word ptr [rcx+0xCC],0xFFFF
0xBC60DFF  mov dword ptr [rcx+0xDC],0xFFFF0000
0xBC60E09  mov byte ptr [rcx+0xE3],0
0xBC60E10  mov eax,0x167
0xBC60E15  nop [rax+rax]
0xBC60E20  mov word ptr [rsi+rax-0x1D],0xFFFF
0xBC60E27  mov byte ptr [rsi+rax-0x14],0
0xBC60E2C  mov dword ptr [rsi+rax-0x27],0
0xBC60E34  mov dword ptr [rsi+rax-0x1B],0xFFFFFFFF
0xBC60E3C  cmp rax,0x667
0xBC60E42  je short 0xBC60E65
0xBC60E44  mov word ptr [rsi+rax-9],0xFFFF
0xBC60E4B  mov byte ptr [rsi+rax],0
0xBC60E4F  mov dword ptr [rsi+rax-0x13],0
0xBC60E57  mov dword ptr [rsi+rax-7],0xFFFFFFFF
0xBC60E5F  add rax,0x28
0xBC60E63  jmp short 0xBC60E20
0xBC60E65  mov rdi,[rsi+0x680]
0xBC60E6C  test rdi,rdi
0xBC60E6F  je 0xBC60EF6
0xBC60E75  mov rcx,[0x12ADF800]
0xBC60E7C  test rcx,rcx
0xBC60E7F  je short 0xBC60EDC
0xBC60E81  xor ebx,ebx
0xBC60E83  xorps xmm6,xmm6
0xBC60E86  jmp short 0xBC60ECF
0xBC60E88  nop [rax+rax]
0xBC60E90  mov rdx,[r14]
0xBC60E93  mov rax,[rcx]
0xBC60E96  mov rax,[rax+8]
0xBC60E9A  mov dword ptr [rsp+0x28],0
0xBC60EA2  mov qword ptr [rsp+0x20],0
0xBC60EAB  xor r8d,r8d
0xBC60EAE  xor r9d,r9d
0xBC60EB1  call qword ptr [0xF99FFA0]
0xBC60EB7  mov rcx,[0x12ADF800]
0xBC60EBE  movups [r14],xmm6
0xBC60EC2  add rbx,0x10
0xBC60EC6  cmp rbx,0x410
0xBC60ECD  je short 0xBC60EEC
0xBC60ECF  lea r14,[rdi+rbx]
0xBC60ED3  test rcx,rcx
0xBC60ED6  jne short 0xBC60E90
0xBC60ED8  xor ecx,ecx
0xBC60EDA  jmp short 0xBC60EBE
0xBC60EDC  mov r8d,0x410
0xBC60EE2  mov rcx,rdi
0xBC60EE5  xor edx,edx
0xBC60EE7  call 0xEEC6ED0
0xBC60EEC  mov dword ptr [rdi+0x410],0
0xBC60EF6  mov byte ptr [rsi+0x688],1
0xBC60EFD  movaps xmm6,[rsp+0x30]
0xBC60F02  add rsp,0x48
0xBC60F06  pop rbx
0xBC60F07  pop rdi
0xBC60F08  pop rsi
0xBC60F09  pop r14
0xBC60F0B  ret

### sub_568DB90 (0x568DB90..0x568DC0F)
0x568DB90  push rsi
0x568DB91  sub rsp,0x30
0x568DB95  lea rax,[0xF25D03C]
0x568DB9C  movsxd rcx,[rax+rcx*4]
0x568DBA0  add rcx,rax
0x568DBA3  jmp rcx
0x568DBA5  mov rcx,[r8]
0x568DBA8  test rcx,rcx
0x568DBAB  je short 0x568DBF0
0x568DBAD  mov rdx,[r8+0x10]
0x568DBB1  sub rdx,rcx
0x568DBB4  cmp rdx,0x1000
0x568DBBB  jb short 0x568DBDA
0x568DBBD  mov rax,[rcx-8]
0x568DBC1  add rcx,0xFFFFFFFFFFFFFFF8
0x568DBC5  sub rcx,rax
0x568DBC8  cmp rcx,0x20
0x568DBCC  jae short 0x568DBF6
0x568DBCE  mov rsi,r8
0x568DBD1  add rdx,0x27
0x568DBD5  mov rcx,rax
0x568DBD8  jmp short 0x568DBDD
0x568DBDA  mov rsi,r8
0x568DBDD  call 0xE935700
0x568DBE2  xorps xmm0,xmm0
0x568DBE5  movups [rsi],xmm0
0x568DBE8  mov qword ptr [rsi+0x10],0
0x568DBF0  add rsp,0x30
0x568DBF4  pop rsi
0x568DBF5  ret
0x568DBF6  mov qword ptr [rsp+0x20],0
0x568DBFF  xor ecx,ecx
0x568DC01  xor edx,edx
0x568DC03  xor r8d,r8d
0x568DC06  xor r9d,r9d
0x568DC09  call qword ptr [0xF9A8C78]
0x568DC0F  int3

### sub_568D480 (0x568D480..0x568D740)
0x568D480  push r15
0x568D482  push r14
0x568D484  push r12
0x568D486  push rsi
0x568D487  push rdi
0x568D488  push rbx
0x568D489  sub rsp,0x48
0x568D48D  mov rax,[0x1230A0C0]
0x568D494  xor rax,rsp
0x568D497  mov [rsp+0x40],rax
0x568D49C  mov r15,[rcx]
0x568D49F  mov r14,[rcx+8]
0x568D4A3  cmp r14,r15
0x568D4A6  je 0x568D711
0x568D4AC  mov rsi,r8
0x568D4AF  mov rdi,rcx
0x568D4B2  lea rbx,[rsp+0x28]
0x568D4B7  mov r12,0xAAAAAAAAAAAAAAAB
0x568D4C1  jmp short 0x568D4F9
0x568D4C3  nop [rax+rax]
0x568D4D0  sub r14,r15
0x568D4D3  add r14,0xFFFFFFFFFFFFFFE8
0x568D4D7  mov rax,r14
0x568D4DA  mul r12
0x568D4DD  shr rdx,4
0x568D4E1  inc rdx
0x568D4E4  lea rax,[rdx+rdx*2]
0x568D4E8  lea r15,[r15+rax*8]
0x568D4EC  mov r14,[rdi+8]
0x568D4F0  cmp r15,r14
0x568D4F3  je 0x568D711
0x568D4F9  mov rax,[r15+8]
0x568D4FD  test rax,rax
0x568D500  je short 0x568D515
0x568D502  mov rdx,[r15+0x10]
0x568D506  test rdx,rdx
0x568D509  je short 0x568D515
0x568D50B  test byte ptr [rax+1],0x40
0x568D50F  jne 0x568D6FD
0x568D515  xor ecx,ecx
0x568D517  lea rax,[r15+0x18]
0x568D51B  cmp rax,r14
0x568D51E  je 0x568D6D3
0x568D524  mov edx,[rcx]
0x568D526  mov r8,[rax+8]
0x568D52A  mov r9,[rax+0x10]
0x568D52E  movzx r10d,word ptr [r8+0x2C]
0x568D533  mov r8,[r9+0x738]
0x568D53A  imul r9,r10,0x58
0x568D53E  cmp [r8+r9],edx
0x568D542  jne 0x568D6D0
0x568D548  add r8,r9
0x568D54B  movzx r9d,byte ptr [r8+4]
0x568D550  cmp r9b,[rcx+4]
0x568D554  jne 0x568D6D0
0x568D55A  mov r9d,[r8+8]
0x568D55E  cmp r9d,[rcx+8]
0x568D562  jne 0x568D6D0
0x568D568  movzx r9d,byte ptr [r8+0xC]
0x568D56D  cmp r9b,[rcx+0xC]
0x568D571  jne 0x568D6D0
0x568D577  movzx r9d,byte ptr [r8+0xD]
0x568D57C  cmp r9b,[rcx+0xD]
0x568D580  jne 0x568D6D0
0x568D586  movzx r9d,byte ptr [r8+0xE]
0x568D58B  cmp r9b,[rcx+0xE]
0x568D58F  jne 0x568D6D0
0x568D595  mov r9d,[r8+0x10]
0x568D599  cmp r9d,[rcx+0x10]
0x568D59D  jne 0x568D6D0
0x568D5A3  movzx r9d,byte ptr [r8+0x14]
0x568D5A8  cmp r9b,[rcx+0x14]
0x568D5AC  jne 0x568D6D0
0x568D5B2  movss xmm0,[r8+0x18]
0x568D5B8  ucomiss xmm0,[rcx+0x18]
0x568D5BC  jne 0x568D6D0
0x568D5C2  jp 0x568D6D0
0x568D5C8  movss xmm0,[r8+0x1C]
0x568D5CE  ucomiss xmm0,[rcx+0x1C]
0x568D5D2  jne 0x568D6D0
0x568D5D8  jp 0x568D6D0
0x568D5DE  movss xmm0,[r8+0x20]
0x568D5E4  ucomiss xmm0,[rcx+0x20]
0x568D5E8  jne 0x568D6D0
0x568D5EE  jp 0x568D6D0
0x568D5F4  movss xmm0,[r8+0x24]
0x568D5FA  ucomiss xmm0,[rcx+0x24]
0x568D5FE  jne 0x568D6D0
0x568D604  jp 0x568D6D0
0x568D60A  mov r9d,[r8+0x28]
0x568D60E  cmp r9d,[rcx+0x28]
0x568D612  jne 0x568D6D0
0x568D618  movss xmm0,[r8+0x2C]
0x568D61E  ucomiss xmm0,[rcx+0x2C]
0x568D622  jne 0x568D6D0
0x568D628  jp 0x568D6D0
0x568D62E  movss xmm0,[r8+0x30]
0x568D634  ucomiss xmm0,[rcx+0x30]
0x568D638  jne 0x568D6D0
0x568D63E  jp 0x568D6D0
0x568D644  movzx r9d,byte ptr [r8+0x54]
0x568D649  cmp r9b,[rcx+0x54]
0x568D64D  jne 0x568D6D0
0x568D653  test r9b,r9b
0x568D656  je short 0x568D6C0
0x568D658  movzx r9d,byte ptr [r8+0x55]
0x568D65D  cmp r9b,[rcx+0x55]
0x568D661  jne short 0x568D6D0
0x568D663  movzx r9d,byte ptr [r8+0x56]
0x568D668  cmp r9b,[rcx+0x56]
0x568D66C  jne short 0x568D6D0
0x568D66E  movzx r9d,byte ptr [r8+0x34]
0x568D673  cmp r9b,[rcx+0x34]
0x568D677  jne short 0x568D6D0
0x568D679  mov r9d,[r8+0x38]
0x568D67D  cmp r9d,[rcx+0x38]
0x568D681  jne short 0x568D6D0
0x568D683  mov r9d,[r8+0x3C]
0x568D687  cmp r9d,[rcx+0x3C]
0x568D68B  jne short 0x568D6D0
0x568D68D  mov r9d,[r8+0x40]
0x568D691  cmp r9d,[rcx+0x40]
0x568D695  jne short 0x568D6D0
0x568D697  movzx r9d,byte ptr [r8+0x44]
0x568D69C  cmp r9b,[rcx+0x44]
0x568D6A0  jne short 0x568D6D0
0x568D6A2  mov r9d,[r8+0x48]
0x568D6A6  cmp r9d,[rcx+0x48]
0x568D6AA  jne short 0x568D6D0
0x568D6AC  mov r9d,[r8+0x4C]
0x568D6B0  cmp r9d,[rcx+0x4C]
0x568D6B4  jne short 0x568D6D0
0x568D6B6  mov r8d,[r8+0x50]
0x568D6BA  cmp r8d,[rcx+0x50]
0x568D6BE  jne short 0x568D6D0
0x568D6C0  add rax,0x18
0x568D6C4  cmp rax,r14
0x568D6C7  jne 0x568D526
0x568D6CD  jmp short 0x568D6D3
0x568D6CF  nop
0x568D6D0  mov r14,rax
0x568D6D3  mov [rsp+0x28],r15
0x568D6D8  mov [rsp+0x30],r14
0x568D6DD  mov [rsp+0x38],r15
0x568D6E2  mov rcx,rsi
0x568D6E5  mov rdx,rbx
0x568D6E8  call 0x568D750
0x568D6ED  cmp r15,r14
0x568D6F0  jne 0x568D4D0
0x568D6F6  xor edx,edx
0x568D6F8  jmp 0x568D4E4
0x568D6FD  movzx eax,word ptr [rax+0x2C]
0x568D701  imul rcx,rax,0x58
0x568D705  add rcx,[rdx+0x738]
0x568D70C  jmp 0x568D517
0x568D711  mov rax,[rsp+0x40]
0x568D716  xor rax,rsp
0x568D719  mov rcx,[0x1230A0C0]
0x568D720  cmp rcx,rax
0x568D723  jne short 0x568D733
0x568D725  add rsp,0x48
0x568D729  pop rbx
0x568D72A  pop rdi
0x568D72B  pop rsi
0x568D72C  pop r12
0x568D72E  pop r14
0x568D730  pop r15
0x568D732  ret
0x568D733  mov rcx,[rsp+0x40]
0x568D738  xor rcx,rsp
0x568D73B  call 0xE951550
0x568D740  int3

### sub_C4BBA0 (0xC4BBA0..0xC4BE69)
0xC4BBA0  push r15
0xC4BBA2  push r14
0xC4BBA4  push r13
0xC4BBA6  push r12
0xC4BBA8  push rsi
0xC4BBA9  push rdi
0xC4BBAA  push rbp
0xC4BBAB  push rbx
0xC4BBAC  sub rsp,0x48
0xC4BBB0  mov rdi,r8
0xC4BBB3  mov r14,rdx
0xC4BBB6  mov [rsp+0x40],rcx
0xC4BBBB  sub rdi,rdx
0xC4BBBE  mov r15,rdx
0xC4BBC1  cmp rdi,0x30
0xC4BBC5  jl 0xC4BE4D
0xC4BBCB  shr rdi,4
0xC4BBCF  mov rcx,0xAAAAAAAAAAAAAAAB
0xC4BBD9  cmp qword ptr [r9+0x20],0x10
0xC4BBDE  jb short 0xC4BBE6
0xC4BBE0  mov rax,[r9+8]
0xC4BBE4  jmp short 0xC4BBEA
0xC4BBE6  lea rax,[r9+8]
0xC4BBEA  mov [rsp+0x28],rax
0xC4BBEF  imul rdi,rcx
0xC4BBF3  mov rax,[r9]
0xC4BBF6  mov [rsp+0x38],rax
0xC4BBFB  mov r9,[r9+0x18]
0xC4BBFF  mov rbx,rdi
0xC4BC02  mov [rsp+0x30],r9
0xC4BC07  jmp short 0xC4BC2C
0xC4BC09  nop [rax]
0xC4BC10  add rsi,0x30
0xC4BC14  not rbx
0xC4BC17  add rbx,rdi
0xC4BC1A  mov r14,rsi
0xC4BC1D  mov rdi,rbx
0xC4BC23  test rbx,rbx
0xC4BC26  jle 0xC4BE4D
0xC4BC2C  shr rbx,1
0xC4BC2F  mov rax,rbx
0xC4BC32  shl rax,4
0xC4BC36  lea r13,[rax+rax*2]
0xC4BC3A  lea rsi,[r14+r13]
0xC4BC3E  mov rax,[r14+r13]
0xC4BC42  cmp rax,[rsp+0x38]
0xC4BC47  jne short 0xC4BC60
0xC4BC49  cmp qword ptr [rsi+0x20],0x10
0xC4BC4E  jb short 0xC4BC70
0xC4BC50  mov r15,[rsi+8]
0xC4BC54  jmp short 0xC4BC74
0xC4BC56  nop [rax+rax]
0xC4BC60  jb short 0xC4BC10
0xC4BC62  ja short 0xC4BC1D
0xC4BC64  jmp short 0xC4BCE1
0xC4BC66  nop [rax+rax]
0xC4BC70  lea r15,[rsi+8]
0xC4BC74  mov r12,[rsi+0x18]
0xC4BC78  mov rbp,r9
0xC4BC7B  cmp r9,r12
0xC4BC7E  jb short 0xC4BC83
0xC4BC80  mov rbp,r12
0xC4BC83  mov rcx,r15
0xC4BC86  mov rdx,[rsp+0x28]
0xC4BC8B  mov r8,rbp
0xC4BC8E  call 0xEEC6EB0
0xC4BC93  xor ecx,ecx
0xC4BC95  mov r9,[rsp+0x30]
0xC4BC9A  cmp r12,r9
0xC4BC9D  setb cl
0xC4BCA0  xor edx,edx
0xC4BCA4  test eax,eax
0xC4BCA7  sets dl
0xC4BCAA  cmovne ecx,edx
0xC4BCAC  test cl,cl
0xC4BCAE  jne 0xC4BC10
0xC4BCB2  mov rcx,[rsp+0x28]
0xC4BCB7  mov rdx,r15
0xC4BCBA  mov r8,rbp
0xC4BCBD  call 0xEEC6EB0
0xC4BCC2  mov r9,[rsp+0x30]
0xC4BCC7  xor ecx,ecx
0xC4BCC9  cmp r9,r12
0xC4BCCC  setb cl
0xC4BCCF  xor edx,edx
0xC4BCD1  test eax,eax
0xC4BCD3  sets dl
0xC4BCD6  cmovne ecx,edx
0xC4BCD9  test cl,cl
0xC4BCDB  jne 0xC4BC1D
0xC4BCE1  mov r15,r14
0xC4BCE4  test rbx,rbx
0xC4BCE7  je 0xC4BD8C
0xC4BCED  mov r14,rbx
0xC4BCF0  jmp short 0xC4BD0C
0xC4BCF2  nop [rax+rax]
0xC4BD00  mov rbx,r14
0xC4BD03  test r14,r14
0xC4BD06  jle 0xC4BD8C
0xC4BD0C  shr r14,1
0xC4BD0F  lea rax,[r14+r14*2]
0xC4BD13  shl rax,4
0xC4BD17  lea r12,[r15+rax]
0xC4BD1B  mov rcx,[rsp+0x38]
0xC4BD20  cmp [r15+rax],rcx
0xC4BD24  setb cl
0xC4BD27  jne short 0xC4BD76
0xC4BD29  cmp qword ptr [r12+0x20],0x10
0xC4BD2F  jb short 0xC4BD40
0xC4BD31  mov rcx,[r12+8]
0xC4BD36  jmp short 0xC4BD45
0xC4BD38  nop [rax+rax]
0xC4BD40  lea rcx,[r12+8]
0xC4BD45  mov rbp,[r12+0x18]
0xC4BD4A  mov r8,r9
0xC4BD4D  cmp r9,rbp
0xC4BD50  jb short 0xC4BD55
0xC4BD52  mov r8,rbp
0xC4BD55  mov rdx,[rsp+0x28]
0xC4BD5A  call 0xEEC6EB0
0xC4BD5F  xor ecx,ecx
0xC4BD61  mov r9,[rsp+0x30]
0xC4BD66  cmp rbp,r9
0xC4BD69  setb cl
0xC4BD6C  xor edx,edx
0xC4BD6E  test eax,eax
0xC4BD70  sets dl
0xC4BD73  cmovne ecx,edx
0xC4BD76  test cl,cl
0xC4BD78  je short 0xC4BD00
0xC4BD7A  add r12,0x30
0xC4BD7E  not r14
0xC4BD81  add r14,rbx
0xC4BD84  mov r15,r12
0xC4BD87  jmp 0xC4BD00
0xC4BD8C  shl rdi,4
0xC4BD90  lea rdi,[rdi+rdi*2]
0xC4BD94  add rsi,0x30
0xC4BD98  sub rdi,r13
0xC4BD9B  add rdi,0xFFFFFFFFFFFFFFD0
0xC4BD9F  test rdi,rdi
0xC4BDA2  jle 0xC4BE4A
0xC4BDA8  shr rdi,4
0xC4BDAC  mov rax,0xAAAAAAAAAAAAAAAB
0xC4BDB6  imul rdi,rax
0xC4BDBA  mov rbx,rdi
0xC4BDBD  jmp short 0xC4BDCC
0xC4BDBF  nop
0xC4BDC0  mov rdi,rbx
0xC4BDC3  test rbx,rbx
0xC4BDC6  jle 0xC4BE4A
0xC4BDCC  shr rbx,1
0xC4BDCF  lea rax,[rbx+rbx*2]
0xC4BDD3  shl rax,4
0xC4BDD7  lea r14,[rsi+rax]
0xC4BDE0  cmp rcx,[rsi+rax]
0xC4BDE4  setb cl
0xC4BDE7  jne short 0xC4BE34
0xC4BDE9  cmp qword ptr [r14+0x20],0x10
0xC4BDEE  jb short 0xC4BE00
0xC4BDF0  mov rdx,[r14+8]
0xC4BDF4  jmp short 0xC4BE04
0xC4BDF6  nop [rax+rax]
0xC4BE00  lea rdx,[r14+8]
0xC4BE04  mov r12,[r14+0x18]
0xC4BE08  mov r8,r12
0xC4BE0B  cmp r12,r9
0xC4BE0E  jb short 0xC4BE13
0xC4BE10  mov r8,r9
0xC4BE13  mov rcx,[rsp+0x28]
0xC4BE18  call 0xEEC6EB0
0xC4BE1D  mov r9,[rsp+0x30]
0xC4BE22  xor ecx,ecx
0xC4BE24  cmp r9,r12
0xC4BE27  setb cl
0xC4BE2A  xor edx,edx
0xC4BE2C  test eax,eax
0xC4BE2E  sets dl
0xC4BE31  cmovne ecx,edx
0xC4BE34  test cl,cl
0xC4BE36  jne short 0xC4BDC0
0xC4BE38  add r14,0x30
0xC4BE3C  not rbx
0xC4BE3F  add rbx,rdi
0xC4BE42  mov rsi,r14
0xC4BE45  jmp 0xC4BDC0
0xC4BE4A  mov r14,rsi
0xC4BE4D  mov rax,[rsp+0x40]
0xC4BE52  mov [rax],r15
0xC4BE55  mov [rax+8],r14
0xC4BE59  add rsp,0x48
0xC4BE5D  pop rbx
0xC4BE5E  pop rbp
0xC4BE5F  pop rdi
0xC4BE60  pop rsi
0xC4BE61  pop r12
0xC4BE63  pop r13
0xC4BE65  pop r14
0xC4BE67  pop r15
0xC4BE69  ret

### sub_E86D7F0 (0xE86D7F0..0xE86E7C5)
0xE86D7F0  push r15
0xE86D7F2  push r14
0xE86D7F4  push r13
0xE86D7F6  push r12
0xE86D7F8  push rsi
0xE86D7F9  push rdi
0xE86D7FA  push rbp
0xE86D7FB  push rbx
0xE86D7FC  sub rsp,0xC8
0xE86D803  mov rbp,r9
0xE86D806  mov [rsp+0x50],r8
0xE86D80B  mov [rsp+0x48],rdx
0xE86D810  mov r15d,ecx
0xE86D813  mov rsi,[rsp+0x138]
0xE86D81B  mov rax,[0x1230A0C0]
0xE86D822  xor rax,rsp
0xE86D825  mov [rsp+0xC0],rax
0xE86D82D  test rsi,rsi
0xE86D830  mov [rsp+0x38],r9
0xE86D835  je 0xE86DA7B
0xE86D83B  mov rax,[rsi+8]
0xE86D83F  mov rbx,[rax+8]
0xE86D843  mov r14,[rax+0x10]
0xE86D847  cmp rbx,r14
0xE86D84A  je 0xE86DA7B
0xE86D850  lea rax,[rbp+8]
0xE86D854  mov [rsp+0x40],rax
0xE86D859  mov rax,[rsp+0x130]
0xE86D861  movzx eax,word ptr [rax+0x42]
0xE86D865  movzx edi,ax
0xE86D868  mov [rsp+0x90],rdi
0xE86D870  mov rcx,[rbp+0x18]
0xE86D874  sub rcx,[rbp+8]
0xE86D878  sar rcx,3
0xE86D87C  mov rdx,0xAAAAAAAAAAAAAAAB
0xE86D886  imul rdx,rcx
0xE86D88A  cmp rdx,rdi
0xE86D88D  jae short 0xE86D8B0
0xE86D88F  lea rdx,[rsp+0x90]
0xE86D897  mov rcx,[rsp+0x40]
0xE86D89C  call 0x13622E0
0xE86D8A1  mov rax,[rsp+0x130]
0xE86D8A9  movzx eax,word ptr [rax+0x42]
0xE86D8AD  movzx edi,ax
0xE86D8B0  test ax,ax
0xE86D8B3  je 0xE86DC06
0xE86D8B9  sub r14,rbx
0xE86D8BC  sar r14,3
0xE86D8C0  mov rbx,0x8E38E38E38E38E39
0xE86D8CA  imul rbx,r14
0xE86D8CE  mov rax,[rsp+0x130]
0xE86D8D6  mov r14,[rax+0x38]
0xE86D8DA  shl edi,4
0xE86D8DD  add rdi,r14
0xE86D8E0  lea r13,[rsp+0x90]
0xE86D8E8  lea rbp,[rsp+0x70]
0xE86D8ED  jmp short 0xE86D90D
0xE86D8EF  mov rcx,[rsp+0x40]
0xE86D8F4  mov r8,r13
0xE86D8F7  call 0x1195A0
0xE86D8FC  nop [rax]
0xE86D900  add r14,0x10
0xE86D904  cmp r14,rdi
0xE86D907  je 0xE86DC06
0xE86D90D  mov rax,[r14]
0xE86D910  cmp byte ptr [rax+0x34],1
0xE86D914  jne short 0xE86D900
0xE86D916  test rbx,rbx
0xE86D919  je 0xE86D9F0
0xE86D91F  mov r12,[rax+0x28]
0xE86D923  mov rax,[rsp+0x130]
0xE86D92B  mov rcx,[rax]
0xE86D92E  mov rdx,[rcx+0x398]
0xE86D935  and rdx,r12
0xE86D938  mov rax,[rcx+0x370]
0xE86D93F  mov r8,[rcx+0x380]
0xE86D946  shl rdx,4
0xE86D94A  mov rcx,[r8+rdx+8]
0xE86D94F  cmp rcx,rax
0xE86D952  je short 0xE86D9A0
0xE86D954  cmp r12,[rcx+0x10]
0xE86D958  je short 0xE86D96F
0xE86D95A  mov rdx,[r8+rdx]
0xE86D95E  xchg ax,ax
0xE86D960  cmp rcx,rdx
0xE86D963  je short 0xE86D9A0
0xE86D965  mov rcx,[rcx+8]
0xE86D969  cmp r12,[rcx+0x10]
0xE86D96D  jne short 0xE86D960
0xE86D96F  cmp rcx,rax
0xE86D972  je short 0xE86D9A0
0xE86D974  mov rax,[rcx+0x18]
0xE86D978  mov [rsp+0x70],rax
0xE86D97D  mov byte ptr [rsp+0x78],1
0xE86D982  mov rcx,rsi
0xE86D985  mov rdx,r13
0xE86D988  mov r8,rbp
0xE86D98B  call 0xBC5E120
0xE86D990  test byte ptr [rsp+0xA0],1
0xE86D998  jne short 0xE86D9C2
0xE86D99A  nop [rax+rax]
0xE86D9A0  mov [rsp+0x70],r12
0xE86D9A5  mov byte ptr [rsp+0x78],0
0xE86D9AA  mov rcx,rsi
0xE86D9AD  mov rdx,r13
0xE86D9B0  mov r8,rbp
0xE86D9B3  call 0xBC5E120
0xE86D9B8  cmp byte ptr [rsp+0xA0],1
0xE86D9C0  jne short 0xE86D9F0
0xE86D9C2  mov rax,[rsp+0x98]
0xE86D9CA  dec rbx
0xE86D9CD  mov rcx,[r14]
0xE86D9D0  movzx edx,word ptr [rcx+0x32]
0xE86D9D4  mov [rsp+0x90],dx
0xE86D9DC  mov [rsp+0x98],rax
0xE86D9E4  movzx eax,word ptr [rcx+0x30]
0xE86D9E8  jmp short 0xE86DA3F
0xE86D9EA  nop [rax+rax]
0xE86D9F0  cmp byte ptr [r14+0xC],0
0xE86D9F5  jne short 0xE86DA09
0xE86D9F7  mov eax,[0x12BD9CC4]
0xE86D9FD  cmp eax,0x63
0xE86DA00  ja short 0xE86DA09
0xE86DA02  lock inc dword ptr [0x12BD9CC4]
0xE86DA09  mov rax,[r14]
0xE86DA0C  movzx ecx,word ptr [rax+0x32]
0xE86DA10  mov [rsp+0x90],cx
0xE86DA18  movzx ecx,word ptr [r14+8]
0xE86DA1D  mov rdx,[rsp+0x130]
0xE86DA25  cmp [rdx+0x28],rcx
0xE86DA29  jbe 0xE86E7AB
0xE86DA2F  add rcx,[rdx+0x30]
0xE86DA33  mov [rsp+0x98],rcx
0xE86DA3B  movzx eax,word ptr [rax+0x30]
0xE86DA3F  mov [rsp+0xA0],ax
0xE86DA47  mov rcx,[rsp+0x38]
0xE86DA4C  mov rdx,[rcx+0x10]
0xE86DA50  cmp rdx,[rcx+0x18]
0xE86DA54  je 0xE86D8EF
0xE86DA5A  mov rax,[rsp+0xA0]
0xE86DA62  mov [rdx+0x10],rax
0xE86DA66  movups xmm0,[rsp+0x90]
0xE86DA6E  movups [rdx],xmm0
0xE86DA71  add qword ptr [rcx+0x10],0x18
0xE86DA76  jmp 0xE86D900
0xE86DA7B  lea rdi,[rbp+8]
0xE86DA7F  mov rsi,[rsp+0x130]
0xE86DA87  movzx eax,word ptr [rsi+0x42]
0xE86DA8B  movzx r14d,ax
0xE86DA8F  mov [rsp+0x90],r14
0xE86DA97  mov rcx,[rbp+0x18]
0xE86DA9B  sub rcx,[rbp+8]
0xE86DA9F  sar rcx,3
0xE86DAA3  mov rdx,0xAAAAAAAAAAAAAAAB
0xE86DAAD  imul rdx,rcx
0xE86DAB1  cmp rdx,r14
0xE86DAB4  jae short 0xE86DACE
0xE86DAB6  lea rdx,[rsp+0x90]
0xE86DABE  mov rcx,rdi
0xE86DAC1  call 0x13622E0
0xE86DAC6  movzx eax,word ptr [rsi+0x42]
0xE86DACA  movzx r14d,ax
0xE86DACE  test ax,ax
0xE86DAD1  je 0xE86DB98
0xE86DAD7  mov r12,[rsi+0x38]
0xE86DADB  shl r14d,4
0xE86DADF  xor r13d,r13d
0xE86DAE2  lea rbx,[rsp+0x90]
0xE86DAEA  jmp short 0xE86DB0D
0xE86DAEC  mov rcx,rdi
0xE86DAEF  mov r8,rbx
0xE86DAF2  call 0x1195A0
0xE86DAF7  nop [rax+rax]
0xE86DB00  add r13,0x10
0xE86DB04  cmp r14,r13
0xE86DB07  je 0xE86DB98
0xE86DB0D  mov rax,[r12+r13]
0xE86DB11  cmp byte ptr [rax+0x34],1
0xE86DB15  jne short 0xE86DB00
0xE86DB17  cmp byte ptr [r12+r13+0xC],0
0xE86DB1D  jne short 0xE86DB31
0xE86DB1F  mov eax,[0x12BD9CC0]
0xE86DB25  cmp eax,0x63
0xE86DB28  ja short 0xE86DB31
0xE86DB2A  lock inc dword ptr [0x12BD9CC0]
0xE86DB31  mov rax,[r12+r13]
0xE86DB35  movzx ecx,word ptr [rax+0x32]
0xE86DB39  mov [rsp+0x90],cx
0xE86DB41  movzx ecx,word ptr [r12+r13+8]
0xE86DB47  cmp [rsi+0x28],rcx
0xE86DB4B  jbe 0xE86E7AB
0xE86DB51  add rcx,[rsi+0x30]
0xE86DB55  mov [rsp+0x98],rcx
0xE86DB5D  movzx eax,word ptr [rax+0x30]
0xE86DB61  mov [rsp+0xA0],ax
0xE86DB69  mov rdx,[rbp+0x10]
0xE86DB6D  cmp rdx,[rbp+0x18]
0xE86DB71  je 0xE86DAEC
0xE86DB77  mov rax,[rsp+0xA0]
0xE86DB7F  mov [rdx+0x10],rax
0xE86DB83  movups xmm0,[rsp+0x90]
0xE86DB8B  movups [rdx],xmm0
0xE86DB8E  add qword ptr [rbp+0x10],0x18
0xE86DB93  jmp 0xE86DB00
0xE86DB98  movzx eax,word ptr [rsi+0x52]
0xE86DB9C  test rax,rax
0xE86DB9F  je 0xE86DD86
0xE86DBA5  mov rdi,[rsi+0x48]
0xE86DBA9  shl eax,4
0xE86DBAC  lea rbx,[rax+rax*2]
0xE86DBB0  mov sil,1
0xE86DBB3  jmp short 0xE86DBF1
0xE86DBB5  nop [rax+rax]
0xE86DBC0  mov r9,[rdi+8]
0xE86DBC4  lea rax,[rdi+0x20]
0xE86DBC8  mov [rsp+0x20],rax
0xE86DBCD  mov byte ptr [rsp+0x28],0
0xE86DBD2  mov ecx,r15d
0xE86DBD5  mov rdx,rbp
0xE86DBD8  mov r8,rdi
0xE86DBDB  call 0xE86E7D0
0xE86DBE0  and sil,al
0xE86DBE3  add rdi,0x30
0xE86DBE7  add rbx,0xFFFFFFFFFFFFFFD0
0xE86DBEB  je 0xE86DD89
0xE86DBF1  movzx eax,byte ptr [rdi+0x10]
0xE86DBF5  cmp eax,1
0xE86DBF8  je short 0xE86DBE3
0xE86DBFA  cmp eax,0xFF
0xE86DBFF  jne short 0xE86DBC0
0xE86DC01  jmp 0xE86DD81
0xE86DC06  mov rcx,[rsp+0x130]
0xE86DC0E  movzx eax,word ptr [rcx+0x52]
0xE86DC12  test rax,rax
0xE86DC15  je 0xE86E14B
0xE86DC1B  mov r12,[rcx+0x48]
0xE86DC1F  lea rdi,[rax+rax*2]
0xE86DC23  shl edi,4
0xE86DC26  add rdi,r12
0xE86DC29  mov al,1
0xE86DC2B  mov [rsp+0x34],eax
0xE86DC2F  lea rbx,[rsp+0x98]
0xE86DC37  mov rbp,[rsp+0x38]
0xE86DC3C  jmp short 0xE86DC79
0xE86DC3E  xchg ax,ax
0xE86DC40  mov r9,[r12+8]
0xE86DC45  lea rax,[r12+0x20]
0xE86DC4A  mov [rsp+0x20],rax
0xE86DC4F  mov byte ptr [rsp+0x28],0
0xE86DC54  mov ecx,r15d
0xE86DC57  mov rdx,rbp
0xE86DC5A  mov r8,r12
0xE86DC5D  call 0xE86E7D0
0xE86DC62  mov ecx,[rsp+0x34]
0xE86DC66  and cl,al
0xE86DC68  mov [rsp+0x34],ecx
0xE86DC6C  add r12,0x30
0xE86DC70  cmp r12,rdi
0xE86DC73  je 0xE86E160
0xE86DC79  movzx eax,byte ptr [r12+0x10]
0xE86DC7F  test eax,eax
0xE86DC81  je short 0xE86DCA0
0xE86DC83  cmp eax,1
0xE86DC86  jne 0xE86DD81
0xE86DC8C  lea r8,[r12+8]
0xE86DC91  jmp short 0xE86DCA8
0xE86DC93  nop [rax+rax]
0xE86DCA0  mov r8,[r12]
0xE86DCA4  add r8,0x28
0xE86DCA8  mov rdx,[rsi+8]
0xE86DCAC  mov rcx,[rdx+8]
0xE86DCB0  mov rdx,[rdx+0x10]
0xE86DCB4  cmp rcx,rdx
0xE86DCB7  je short 0xE86DD02
0xE86DCB9  mov r8,[r8]
0xE86DCBC  movzx r9d,byte ptr [r12+0x18]
0xE86DCC2  jmp short 0xE86DCE7
0xE86DCC4  nop [rax+rax]
0xE86DCD0  cmp r10d,1
0xE86DCD4  jne 0xE86E7B0
0xE86DCDA  add rcx,0x48
0xE86DCDE  cmp rcx,rdx
0xE86DCE1  je 0xE86DD70
0xE86DCE7  movzx r10d,byte ptr [rcx+8]
0xE86DCEC  test r10d,r10d
0xE86DCEF  jne short 0xE86DCD0
0xE86DCF1  cmp [rcx],r8
0xE86DCF4  jne short 0xE86DCDA
0xE86DCF6  cmp [rcx+0x40],r9b
0xE86DCFA  jne short 0xE86DCDA
0xE86DCFC  cmp byte ptr [rcx+0x30],3
0xE86DD00  jne short 0xE86DCDA
0xE86DD02  cmp rcx,rdx
0xE86DD05  je short 0xE86DD70
0xE86DD07  cmp byte ptr [rcx+0x30],3
0xE86DD0B  jne short 0xE86DD81
0xE86DD0D  movups xmm0,[rcx+0x10]
0xE86DD11  movups xmm1,[rcx+0x20]
0xE86DD15  movaps [rsp+0xA0],xmm1
0xE86DD1D  movaps [rsp+0x90],xmm0
0xE86DD25  mov byte ptr [rsp+0xB0],1
0xE86DD2D  movzx eax,byte ptr [rsp+0xA4]
0xE86DD35  mov r9,[rsp+0x90]
0xE86DD3D  mov [rsp+0x28],al
0xE86DD41  mov [rsp+0x20],rbx
0xE86DD46  mov ecx,r15d
0xE86DD49  mov rdx,rbp
0xE86DD4C  mov r8,r12
0xE86DD4F  call 0xE86E7D0
0xE86DD54  test al,al
0xE86DD56  jne 0xE86DC6C
0xE86DD5C  jmp 0xE86E158
0xE86DD61  nop [rax+rax]
0xE86DD70  test eax,eax
0xE86DD72  je 0xE86DC40
0xE86DD78  cmp eax,1
0xE86DD7B  je 0xE86DC6C
0xE86DD81  call 0x1166E0
0xE86DD86  mov sil,1
0xE86DD89  mov [rsp+0x34],esi
0xE86DD8D  mov rax,[rsp+0x130]
0xE86DD95  movzx edi,word ptr [rax+0x72]
0xE86DD99  test edi,edi
0xE86DD9B  je 0xE86DE97
0xE86DDA1  mov rbx,[rax+0x68]
0xE86DDA5  shl edi,5
0xE86DDA8  lea rax,[rbp+0x20]
0xE86DDAC  mov [rsp+0x40],rax
0xE86DDB1  xor r15d,r15d
0xE86DDB4  lea r14,[rsp+0x90]
0xE86DDBC  jmp short 0xE86DDDD
0xE86DDBE  xchg ax,ax
0xE86DDC0  mov [rbp],r13d
0xE86DDC4  mov [rbp+4],r12b
0xE86DDC8  mov [rbp+8],esi
0xE86DDCB  add r15,0x20
0xE86DDCF  cmp rdi,r15
0xE86DDD2  mov rbp,[rsp+0x38]
0xE86DDD7  je 0xE86DE97
0xE86DDDD  movzx eax,word ptr [rbx+r15+8]
0xE86DDE3  mov ecx,[rbx+r15+0xC]
0xE86DDE8  movzx edx,byte ptr [rbx+r15+0x10]
0xE86DDEE  mov [rsp+0x84],ax
0xE86DDF6  mov [rsp+0x88],ecx
0xE86DDFD  mov [rsp+0x8C],dl
0xE86DE04  lea rcx,[rsp+0x84]
0xE86DE0C  call 0xC985870
0xE86DE11  mov r13d,eax
0xE86DE14  movzx r12d,byte ptr [rbx+r15+0x15]
0xE86DE1A  mov esi,[rbx+r15+0x18]
0xE86DE1F  mov [rsp+0x5F],r12b
0xE86DE24  mov rax,[rbp+0x28]
0xE86DE28  mov rcx,[rbp+0x40]
0xE86DE2C  mov [rsp+0x70],rax
0xE86DE31  mov [rsp+0x78],rcx
0xE86DE36  mov rax,[rbp+0x20]
0xE86DE3A  mov rcx,[rbp+0x38]
0xE86DE3E  mov [rsp+0x60],rax
0xE86DE43  mov [rsp+0x68],rcx
0xE86DE48  lea rax,[rsp+0x5F]
0xE86DE4D  mov [rsp+0x20],rax
0xE86DE52  mov rcx,[rsp+0x40]
0xE86DE57  mov rdx,r14
0xE86DE5A  lea r8,[rsp+0x60]
0xE86DE5F  lea r9,[rsp+0x70]
0xE86DE64  call 0xE86EEF0
0xE86DE69  mov rbp,[rsp+0x98]
0xE86DE71  movsx rcx,byte ptr [rbp+0x18]
0xE86DE76  cmp rcx,3
0xE86DE7A  je 0xE86DDC0
0xE86DE80  inc rcx
0xE86DE83  mov rdx,r14
0xE86DE86  mov r8,rbp
0xE86DE89  call 0x568DB90
0xE86DE8E  mov byte ptr [rbp+0x18],3
0xE86DE92  jmp 0xE86DDC0
0xE86DE97  mov rcx,[rsp+0x130]
0xE86DE9F  movzx eax,word ptr [rcx+0x62]
0xE86DEA3  test rax,rax
0xE86DEA6  je 0xE86E311
0xE86DEAC  mov rdi,[rcx+0x58]
0xE86DEB0  shl eax,3
0xE86DEB3  lea rbx,[rax+rax*4]
0xE86DEB7  add rdi,0x25
0xE86DEBB  xor r15d,r15d
0xE86DEBE  lea r12,[0xF4F01EC]
0xE86DEC5  lea r14,[rsp+0x90]
0xE86DECD  jmp short 0xE86DF0D
0xE86DECF  movups xmm0,[r8]
0xE86DED3  movaps [rsp+0x90],xmm0
0xE86DEDB  mov [rsp+0x28],rax
0xE86DEE0  mov [rsp+0x20],cl
0xE86DEE4  mov rcx,rbp
0xE86DEE7  mov rdx,[rsp+0x50]
0xE86DEEC  mov r8,r14
0xE86DEEF  call 0xE86FD80
0xE86DEF4  nop [rax+rax]
0xE86DF00  add r15,0x28
0xE86DF04  cmp rbx,r15
0xE86DF07  je 0xE86E311
0xE86DF0D  mov rax,[rdi+r15-0x25]
0xE86DF12  cmp byte ptr [rax+0x34],1
0xE86DF16  jne short 0xE86DF00
0xE86DF18  movzx r10d,byte ptr [rdi+r15-0xD]
0xE86DF1E  cmp r10,4
0xE86DF22  ja 0xE86DD81
0xE86DF28  movzx ecx,byte ptr [rdi+r15-1]
0xE86DF2E  movzx edx,byte ptr [rdi+r15]
0xE86DF33  movzx r9d,dl
0xE86DF37  lea r8,[rdi+r15]
0xE86DF3B  add r8,0xFFFFFFFFFFFFFFE3
0xE86DF3F  movsxd r10,[r12+r10*4]
0xE86DF43  add r10,r12
0xE86DF46  jmp r10
0xE86DF49  mov r8d,[r8]
0xE86DF4C  test r8d,0x10000
0xE86DF53  jne 0xE86E084
0xE86DF59  movzx eax,word ptr [rax+0x32]
0xE86DF5D  dec cl
0xE86DF5F  movzx ecx,cl
0xE86DF62  mov [rsp+0x90],dl
0xE86DF69  mov word ptr [rsp+0x92],0xFFFF
0xE86DF73  jmp 0xE86E0A8
0xE86DF78  mov r8,[r8]
0xE86DF7B  test r8,r8
0xE86DF7E  je short 0xE86DF00
0xE86DF80  mov r8,[r8+0x18]
0xE86DF84  test r8,r8
0xE86DF87  je 0xE86DF00
0xE86DF8D  dec cl
0xE86DF8F  cmp cl,2
0xE86DF92  ja 0xE86DF00
0xE86DF98  movzx ecx,cl
0xE86DF9B  movzx r9d,word ptr [r8]
0xE86DF9F  movzx r10d,byte ptr [r8+2]
0xE86DFA4  test r10d,r10d
0xE86DFA7  je 0xE86E0CC
0xE86DFAD  cmp r10d,1
0xE86DFB1  jne 0xE86DD81
0xE86DFB7  cmp r9w,0xFFFF
0xE86DFBC  je 0xE86DF00
0xE86DFC2  movzx eax,word ptr [rax+0x32]
0xE86DFC6  mov r8d,[r8+4]
0xE86DFCA  mov [rsp+0x90],dl
0xE86DFD1  mov [rsp+0x92],r9w
0xE86DFDA  mov byte ptr [rsp+0x94],2
0xE86DFE2  jmp 0xE86E124
0xE86DFE7  movups xmm0,[r8]
0xE86DFEB  movaps [rsp+0x90],xmm0
0xE86DFF3  mov [rsp+0x28],rax
0xE86DFF8  mov [rsp+0x20],cl
0xE86DFFC  mov rcx,rbp
0xE86DFFF  mov rdx,[rsp+0x48]
0xE86E004  mov r8,r14
0xE86E007  call 0xE86FB90
0xE86E00C  jmp 0xE86DF00
0xE86E011  mov r8,[r8]
0xE86E014  test r8,r8
0xE86E017  je 0xE86DF00
0xE86E01D  mov r8,[r8+0x18]
0xE86E021  test r8,r8
0xE86E024  je 0xE86DF00
0xE86E02A  dec cl
0xE86E02C  cmp cl,2
0xE86E02F  ja 0xE86DF00
0xE86E035  movzx ecx,cl
0xE86E038  movzx r9d,word ptr [r8]
0xE86E03C  movzx r10d,byte ptr [r8+2]
0xE86E041  test r10d,r10d
0xE86E044  je 0xE86E0F9
0xE86E04A  cmp r10d,1
0xE86E04E  jne 0xE86DD81
0xE86E054  cmp r9w,0xFFFF
0xE86E059  je 0xE86DF00
0xE86E05F  movzx eax,word ptr [rax+0x32]
0xE86E063  mov r8d,[r8+4]
0xE86E067  mov [rsp+0x90],dl
0xE86E06E  mov [rsp+0x92],r9w
0xE86E077  mov byte ptr [rsp+0x94],3
0xE86E07F  jmp 0xE86E124
0xE86E084  cmp r8w,0xFFFF
0xE86E089  je 0xE86DF00
0xE86E08F  movzx eax,word ptr [rax+0x32]
0xE86E093  dec cl
0xE86E095  movzx ecx,cl
0xE86E098  mov [rsp+0x90],dl
0xE86E09F  mov [rsp+0x92],r8w
0xE86E0A8  mov byte ptr [rsp+0x94],5
0xE86E0B0  mov [rsp+0x96],ax
0xE86E0B8  mov [rsp+0x98],ecx
0xE86E0BF  mov dword ptr [rsp+0x9C],0
0xE86E0CA  jmp short 0xE86E13B
0xE86E0CC  cmp r9w,0xFFFF
0xE86E0D1  je 0xE86DF00
0xE86E0D7  movzx eax,word ptr [rax+0x32]
0xE86E0DB  mov r8d,[r8+4]
0xE86E0DF  mov [rsp+0x90],dl
0xE86E0E6  mov [rsp+0x92],r9w
0xE86E0EF  mov byte ptr [rsp+0x94],0
0xE86E0F7  jmp short 0xE86E124
0xE86E0F9  cmp r9w,0xFFFF
0xE86E0FE  je 0xE86DF00
0xE86E104  movzx eax,word ptr [rax+0x32]
0xE86E108  mov r8d,[r8+4]
0xE86E10C  mov [rsp+0x90],dl
0xE86E113  mov [rsp+0x92],r9w
0xE86E11C  mov byte ptr [rsp+0x94],1
0xE86E124  mov [rsp+0x96],ax
0xE86E12C  mov [rsp+0x98],ecx
0xE86E133  mov [rsp+0x9C],r8d
0xE86E13B  mov rcx,rbp
0xE86E13E  mov r8,r14
0xE86E141  call 0xE86F700
0xE86E146  jmp 0xE86DF00
0xE86E14B  mov al,1
0xE86E14D  mov [rsp+0x34],eax
0xE86E151  mov rbp,[rsp+0x38]
0xE86E156  jmp short 0xE86E160
0xE86E158  mov dword ptr [rsp+0x34],0
0xE86E160  mov rax,[rsp+0x130]
0xE86E168  movzx r15d,word ptr [rax+0x72]
0xE86E16D  test r15d,r15d
0xE86E170  je 0xE86E2E3
0xE86E176  mov r12,[rax+0x68]
0xE86E17A  shl r15d,5
0xE86E17E  add r15,r12
0xE86E181  lea rax,[rbp+0x20]
0xE86E185  mov [rsp+0x40],rax
0xE86E18A  lea r13,[rsp+0x90]
0xE86E192  lea rbx,[rsp+0x70]
0xE86E197  jmp short 0xE86E1C5
0xE86E199  nop [rax]
0xE86E1A0  mov [rbp],r14d
0xE86E1A4  mov [rbp+4],sil
0xE86E1A8  mov [rbp+8],edi
0xE86E1AB  add r12,0x20
0xE86E1AF  cmp r12,r15
0xE86E1B2  mov rbp,[rsp+0x38]
0xE86E1B7  mov rsi,[rsp+0x138]
0xE86E1BF  je 0xE86E2E3
0xE86E1C5  movzx eax,word ptr [r12+8]
0xE86E1CB  mov rdx,[rsi+8]
0xE86E1CF  mov rcx,[rdx+8]
0xE86E1D3  mov rdx,[rdx+0x10]
0xE86E1D7  cmp rcx,rdx
0xE86E1DA  je short 0xE86E21E
0xE86E1DC  mov r8,[r12]
0xE86E1E0  mov r8,[r8+0x28]
0xE86E1E4  jmp short 0xE86E203
0xE86E1E6  nop [rax+rax]
0xE86E1F0  cmp r9d,1
0xE86E1F4  jne 0xE86E7B0
0xE86E1FA  add rcx,0x48
0xE86E1FE  cmp rcx,rdx
0xE86E201  je short 0xE86E231
0xE86E203  movzx r9d,byte ptr [rcx+8]
0xE86E208  test r9d,r9d
0xE86E20B  jne short 0xE86E1F0
0xE86E20D  cmp [rcx],r8
0xE86E210  jne short 0xE86E1FA
0xE86E212  cmp byte ptr [rcx+0x40],0
0xE86E216  jne short 0xE86E1FA
0xE86E218  cmp byte ptr [rcx+0x30],4
0xE86E21C  jne short 0xE86E1FA
0xE86E21E  cmp rcx,rdx
0xE86E221  je short 0xE86E231
0xE86E223  cmp byte ptr [rcx+0x30],4
0xE86E227  jne 0xE86DD81
0xE86E22D  movzx eax,word ptr [rcx+0x10]
0xE86E231  mov ecx,[r12+0xC]
0xE86E236  movzx edx,byte ptr [r12+0x10]
0xE86E23C  mov [rsp+0x84],ax
0xE86E244  mov [rsp+0x88],ecx
0xE86E24B  mov [rsp+0x8C],dl
0xE86E252  lea rcx,[rsp+0x84]
0xE86E25A  call 0xC985870
0xE86E25F  mov r14d,eax
0xE86E262  movzx esi,byte ptr [r12+0x15]
0xE86E268  mov edi,[r12+0x18]
0xE86E26D  mov [rsp+0x5F],sil
0xE86E272  mov rax,[rbp+0x28]
0xE86E276  mov rcx,[rbp+0x40]
0xE86E27A  mov [rsp+0x70],rax
0xE86E27F  mov [rsp+0x78],rcx
0xE86E284  mov rax,[rbp+0x20]
0xE86E288  mov rcx,[rbp+0x38]
0xE86E28C  mov [rsp+0x60],rax
0xE86E291  mov [rsp+0x68],rcx
0xE86E296  lea rax,[rsp+0x5F]
0xE86E29B  mov [rsp+0x20],rax
0xE86E2A0  mov rcx,[rsp+0x40]
0xE86E2A5  mov rdx,r13
0xE86E2AD  lea r8,[rsp+0x60]
0xE86E2A8  mov r9,rbx
0xE86E2B0  call 0xE86EEF0
0xE86E2B5  mov rbp,[rsp+0x98]
0xE86E2BD  movsx rcx,byte ptr [rbp+0x18]
0xE86E2C2  cmp rcx,3
0xE86E2C6  je 0xE86E1A0
0xE86E2CC  inc rcx
0xE86E2CF  mov rdx,r13
0xE86E2D2  mov r8,rbp
0xE86E2D5  call 0x568DB90
0xE86E2DA  mov byte ptr [rbp+0x18],3
0xE86E2DE  jmp 0xE86E1A0
0xE86E2E3  mov rcx,[rsp+0x130]
0xE86E2EB  movzx eax,word ptr [rcx+0x62]
0xE86E2EF  test rax,rax
0xE86E2F2  je short 0xE86E311
0xE86E2F4  mov rbx,[rcx+0x58]
0xE86E2F8  lea rax,[rax+rax*4]
0xE86E2FC  lea r14,[rbx+rax*8]
0xE86E300  lea r12,[rbp+0x20]
0xE86E304  lea rbp,[0xF4F01D8]
0xE86E30B  mov edi,[rsp+0x34]
0xE86E30F  jmp short 0xE86E387
0xE86E311  mov edi,[rsp+0x34]
0xE86E315  mov rax,[rsp+0xC0]
0xE86E31D  xor rax,rsp
0xE86E320  mov rcx,[0x1230A0C0]
0xE86E327  cmp rcx,rax
0xE86E32A  jne 0xE86E7B5
0xE86E330  and dil,1
0xE86E334  mov eax,edi
0xE86E336  add rsp,0xC8
0xE86E33D  pop rbx
0xE86E33E  pop rbp
0xE86E33F  pop rdi
0xE86E340  pop rsi
0xE86E341  pop r12
0xE86E343  pop r13
0xE86E345  pop r14
0xE86E347  pop r15
0xE86E349  ret
0xE86E34A  movups xmm0,[r11]
0xE86E34E  movaps [rsp+0x90],xmm0
0xE86E356  mov [rsp+0x28],rax
0xE86E35B  mov [rsp+0x20],cl
0xE86E35F  mov rcx,[rsp+0x38]
0xE86E364  mov rdx,[rsp+0x50]
0xE86E369  lea r8,[rsp+0x90]
0xE86E371  call 0xE86FD80
0xE86E376  mov rsi,[rsp+0x138]
0xE86E37E  add rbx,0x28
0xE86E382  cmp rbx,r14
0xE86E385  je short 0xE86E315
0xE86E387  mov rax,[rbx]
0xE86E38A  cmp byte ptr [rax+0x34],1
0xE86E38E  jne short 0xE86E37E
0xE86E390  movzx ecx,byte ptr [rbx+0x24]
0xE86E394  movzx r13d,byte ptr [rbx+0x25]
0xE86E399  mov r10,[rax+0x28]
0xE86E3A1  mov r8,[rsi+8]
0xE86E3A5  mov rdx,[r8+8]
0xE86E3A9  mov r8,[r8+0x10]
0xE86E3AC  cmp rdx,r8
0xE86E3AF  je short 0xE86E3F4
0xE86E3B1  mov r9,rdx
0xE86E3B4  jmp short 0xE86E3D7
0xE86E3B6  nop [rax+rax]
0xE86E3C0  cmp r11d,1
0xE86E3C4  jne 0xE86E7B0
0xE86E3CA  add r9,0x48
0xE86E3CE  cmp r9,r8
0xE86E3D1  je 0xE86E470
0xE86E3D7  movzx r11d,byte ptr [r9+8]
0xE86E3DC  test r11d,r11d
0xE86E3DF  jne short 0xE86E3C0
0xE86E3E1  cmp [r9],r10
0xE86E3E4  jne short 0xE86E3CA
0xE86E3E6  cmp byte ptr [r9+0x40],0
0xE86E3EB  jne short 0xE86E3CA
0xE86E3ED  cmp byte ptr [r9+0x30],5
0xE86E3F2  jne short 0xE86E3CA
0xE86E3F4  cmp r9,r8
0xE86E3F7  je short 0xE86E470
0xE86E3F9  cmp byte ptr [r9+0x30],5
0xE86E3FE  jne 0xE86DD81
0xE86E404  movzx edx,word ptr [r9+0x10]
0xE86E409  cmp dx,0xFFFF
0xE86E40D  je 0xE86E37E
0xE86E413  movzx eax,word ptr [rax+0x32]
0xE86E417  dec cl
0xE86E419  cmp cl,3
0xE86E41C  movzx ecx,cl
0xE86E41F  cmovb r15d,ecx
0xE86E423  mov [rsp+0x90],r13b
0xE86E42B  mov [rsp+0x92],dx
0xE86E433  mov byte ptr [rsp+0x94],5
0xE86E43B  mov [rsp+0x96],ax
0xE86E443  mov [rsp+0x98],r15d
0xE86E44B  mov dword ptr [rsp+0x9C],0
0xE86E456  mov rcx,[rsp+0x38]
0xE86E45B  mov edx,r13d
0xE86E45E  lea r8,[rsp+0x90]
0xE86E466  call 0xE86F700
0xE86E46B  jmp 0xE86E37E
0xE86E470  movzx esi,byte ptr [rbx+0x18]
0xE86E474  cmp rsi,4
0xE86E478  ja 0xE86DD81
0xE86E47E  movzx r9d,r13b
0xE86E482  lea r11,[rbx+8]
0xE86E486  movsxd rsi,[rbp+rsi*4]
0xE86E48B  add rsi,rbp
0xE86E48E  jmp rsi
0xE86E490  mov r9d,[r11]
0xE86E493  test r9d,0x10000
0xE86E49A  jne 0xE86E6CE
0xE86E4A0  mov rsi,[rsp+0x138]
0xE86E4A8  cmp rdx,r8
0xE86E4AB  jne short 0xE86E4C6
0xE86E4AD  jmp short 0xE86E4DF
0xE86E4AF  nop
0xE86E4B0  cmp ecx,1
0xE86E4B3  jne 0xE86E7B0
0xE86E4B9  add rdx,0x48
0xE86E4BD  cmp rdx,r8
0xE86E4C0  je 0xE86E37E
0xE86E4C6  movzx ecx,byte ptr [rdx+8]
0xE86E4CA  test ecx,ecx
0xE86E4CC  jne short 0xE86E4B0
0xE86E4CE  cmp [rdx],r10
0xE86E4D1  jne short 0xE86E4B9
0xE86E4D3  cmp byte ptr [rdx+0x40],0
0xE86E4D7  jne short 0xE86E4B9
0xE86E4D9  cmp byte ptr [rdx+0x30],6
0xE86E4DD  jne short 0xE86E4B9
0xE86E4DF  cmp rdx,r8
0xE86E4E2  je 0xE86E37E
0xE86E4E8  cmp byte ptr [rdx+0x30],6
0xE86E4EC  jne 0xE86DD81
0xE86E4F2  mov rcx,[rdx+0x10]
0xE86E4F6  movzx esi,word ptr [rcx]
0xE86E4FD  cmp si,0xFFFF
0xE86E4FD  je 0xE86E7A2
0xE86E503  movzx eax,word ptr [rax+0x32]
0xE86E507  mov [rsp+0x40],ax
0xE86E50C  mov [rsp+0x84],r13b
0xE86E514  mov rdx,[rsp+0x38]
0xE86E519  mov rax,[rdx+0x28]
0xE86E51D  mov rcx,[rdx+0x40]
0xE86E521  mov [rsp+0x70],rax
0xE86E526  mov [rsp+0x78],rcx
0xE86E52B  mov rax,[rdx+0x20]
0xE86E52F  mov rcx,[rdx+0x38]
0xE86E533  mov [rsp+0x60],rax
0xE86E538  mov [rsp+0x68],rcx
0xE86E53D  lea rax,[rsp+0x84]
0xE86E545  mov [rsp+0x20],rax
0xE86E54A  mov rcx,r12
0xE86E54D  lea rdx,[rsp+0x90]
0xE86E555  lea r8,[rsp+0x60]
0xE86E55A  lea r9,[rsp+0x70]
0xE86E55F  call 0xE86EEF0
0xE86E564  mov rdi,[rsp+0x98]
0xE86E56C  movsx rcx,byte ptr [rdi+0x18]
0xE86E571  cmp rcx,2
0xE86E575  je short 0xE86E58E
0xE86E577  inc rcx
0xE86E57A  lea rdx,[rsp+0x90]
0xE86E582  mov r8,rdi
0xE86E585  call 0x568DB90
0xE86E58A  mov byte ptr [rdi+0x18],2
0xE86E58E  mov [rdi],r13b
0xE86E591  movzx eax,word ptr [rsp+0x40]
0xE86E596  mov [rdi+2],ax
0xE86E59A  mov [rdi+4],si
0xE86E59E  mov edi,[rsp+0x34]
0xE86E5A2  jmp 0xE86E376
0xE86E5A7  mov rdx,[r11]
0xE86E5AA  test rdx,rdx
0xE86E5AD  je 0xE86E376
0xE86E5B3  mov rdx,[rdx+0x18]
0xE86E5B7  test rdx,rdx
0xE86E5BA  mov rsi,[rsp+0x138]
0xE86E5C2  je 0xE86E37E
0xE86E5C8  dec cl
0xE86E5CA  cmp cl,2
0xE86E5CD  ja 0xE86E37E
0xE86E5D3  movzx ecx,cl
0xE86E5D6  movzx r8d,word ptr [rdx]
0xE86E5DA  movzx r9d,byte ptr [rdx+2]
0xE86E5DF  test r9d,r9d
0xE86E5E2  je 0xE86E72F
0xE86E5E8  cmp r9d,1
0xE86E5EC  jne 0xE86DD81
0xE86E5F2  cmp r8w,0xFFFF
0xE86E5F7  je 0xE86E37E
0xE86E5FD  movzx eax,word ptr [rax+0x32]
0xE86E601  mov edx,[rdx+4]
0xE86E604  mov [rsp+0x90],r13b
0xE86E60C  mov [rsp+0x92],r8w
0xE86E615  mov byte ptr [rsp+0x94],2
0xE86E61D  jmp 0xE86E787
0xE86E622  movups xmm0,[r11]
0xE86E626  movaps [rsp+0x90],xmm0
0xE86E62E  mov [rsp+0x28],rax
0xE86E633  mov [rsp+0x20],cl
0xE86E637  mov rcx,[rsp+0x38]
0xE86E63C  mov rdx,[rsp+0x48]
0xE86E641  lea r8,[rsp+0x90]
0xE86E649  call 0xE86FB90
0xE86E64E  jmp 0xE86E376
0xE86E653  mov rdx,[r11]
0xE86E656  test rdx,rdx
0xE86E659  je 0xE86E376
0xE86E65F  mov rdx,[rdx+0x18]
0xE86E663  test rdx,rdx
0xE86E666  mov rsi,[rsp+0x138]
0xE86E66E  je 0xE86E37E
0xE86E674  dec cl
0xE86E676  cmp cl,2
0xE86E679  ja 0xE86E37E
0xE86E67F  movzx ecx,cl
0xE86E682  movzx r8d,word ptr [rdx]
0xE86E686  movzx r9d,byte ptr [rdx+2]
0xE86E68B  test r9d,r9d
0xE86E68E  je 0xE86E75C
0xE86E694  cmp r9d,1
0xE86E698  jne 0xE86DD81
0xE86E69E  cmp r8w,0xFFFF
0xE86E6A3  je 0xE86E37E
0xE86E6A9  movzx eax,word ptr [rax+0x32]
0xE86E6AD  mov edx,[rdx+4]
0xE86E6B0  mov [rsp+0x90],r13b
0xE86E6B8  mov [rsp+0x92],r8w
0xE86E6C1  mov byte ptr [rsp+0x94],3
0xE86E6C9  jmp 0xE86E787
0xE86E6CE  cmp r9w,0xFFFF
0xE86E6D3  je 0xE86E376
0xE86E6D9  movzx eax,word ptr [rax+0x32]
0xE86E6DD  dec cl
0xE86E6DF  movzx ecx,cl
0xE86E6E2  mov [rsp+0x90],r13b
0xE86E6EA  mov [rsp+0x92],r9w
0xE86E6F3  mov byte ptr [rsp+0x94],5
0xE86E6FB  mov [rsp+0x96],ax
0xE86E703  mov [rsp+0x98],ecx
0xE86E70A  mov dword ptr [rsp+0x9C],0
0xE86E715  mov rcx,[rsp+0x38]
0xE86E71A  mov edx,r13d
0xE86E71D  lea r8,[rsp+0x90]
0xE86E725  call 0xE86F700
0xE86E72A  jmp 0xE86E376
0xE86E72F  cmp r8w,0xFFFF
0xE86E734  je 0xE86E37E
0xE86E73A  movzx eax,word ptr [rax+0x32]
0xE86E73E  mov edx,[rdx+4]
0xE86E741  mov [rsp+0x90],r13b
0xE86E749  mov [rsp+0x92],r8w
0xE86E752  mov byte ptr [rsp+0x94],0
0xE86E75A  jmp short 0xE86E787
0xE86E75C  cmp r8w,0xFFFF
0xE86E761  je 0xE86E37E
0xE86E767  movzx eax,word ptr [rax+0x32]
0xE86E76B  mov edx,[rdx+4]
0xE86E76E  mov [rsp+0x90],r13b
0xE86E776  mov [rsp+0x92],r8w
0xE86E77F  mov byte ptr [rsp+0x94],1
0xE86E787  mov [rsp+0x96],ax
0xE86E78F  mov [rsp+0x98],ecx
0xE86E796  mov [rsp+0x9C],edx
0xE86E79D  jmp 0xE86E456
0xE86E7A2  mov edi,[rsp+0x34]
0xE86E7A6  jmp 0xE86E376
0xE86E7AB  call 0x78ED0
0xE86E7B0  call 0xB432E0
0xE86E7B5  mov rcx,[rsp+0xC0]
0xE86E7BD  xor rcx,rsp
0xE86E7C0  call 0xE951550
0xE86E7C5  int3