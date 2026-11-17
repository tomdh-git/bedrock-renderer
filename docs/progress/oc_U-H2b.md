## NEXT
DONE: All three steps completed. Hits table written, writer functions analyzed (sub_e7f5380, sub_e7f0f40, sub_e805480), sibling counters documented, role guess [I] provided with UNVERIFIED gaps flagged. Struct fields summary and TOOL REQUESTS included.

---
# UNIT U-H2b: Render-context occlusion-query counter at ctx+0x2035F0

## Step 1: Hits table — every instruction in .text accessing displacement 0x2035F0 (and neighbours 0x2035E0..0x203600) with a base register

| RVA | Instruction | Function | Offset | Access | Context |
|-----|-------------|----------|--------|--------|---------|
| 0xe7f5452 | lea rcx,[r12+0x2035F0] | sub_e7f5380 (debug overlay setup) | 0x2035F0 | WRITE (addr passed to sub_e805480) | r12 = context object; prepares counter for update via sub_e805480 |
| 0xe7f1619 | lea rcx,[rsi+0x2035F0] | sub_e7f0f40 (cleanup/reset) | 0x2035F0 | WRITE (addr passed to sub_e805480) | rsi = context object (from [0x12B77770]); resets counter via sub_e805480 |
| 0xe7fcb30 | mov eax,[r10+0x2035F0] | sub_e7f5380 (debug overlay draw) | 0x2035F0 | READ | r10 = [rbx+0x90] = context; reads counter for display " Occlusion queries: %3d " |

### Neighbour offsets (0x2035E0..0x203600) — sibling counters in same overlay block

| RVA | Instruction | Function | Offset | Access | Context |
|-----|-------------|----------|--------|--------|---------|
| 0xe7f5482 | lea rcx,[r12+0x2035D0] | sub_e7f5380 | 0x2035D0 | WRITE (addr passed to sub_e805480) | Precedes 0x2035F0 writer |
| 0xe7f5b2c | lea rcx,[r12+0x2035D0] | sub_e7f5380 | 0x2035D0 | WRITE (addr passed to sub_e805480) | Second write to 0x2035D0 |
| 0xe7fcb37 | mov ecx,[r10+0x2035D0] | sub_e7f5380 (debug draw) | 0x2035D0 | READ | Displayed in "%6d | %6d | %6d | %6d | %6d" |
| 0xe7fcb3e | mov edx,[r10+0x2035B0] | sub_e7f5380 (debug draw) | 0x2035B0 | READ | Displayed in "%6d | %6d | %6d | %6d | %6d" |
| 0xe7fcb45 | mov r9d,[r10+0x203570] | sub_e7f5380 (debug draw) | 0x203570 | READ | Displayed in "%6d | %6d | %6d | %6d | %6d" |
| 0xe7fcb4c | mov r10d,[r10+0x203590] | sub_e7f5380 (debug draw) | 0x203590 | READ | Displayed in "%6d | %6d | %6d | %6d | %6d" |
| 0xe7f160d | lea rcx,[rsi+0x2035D0] | sub_e7f0f40 | 0x2035D0 | WRITE (addr passed to sub_e805480) | Reset path |
| 0xe7f1619 | lea rcx,[rsi+0x2035F0] | sub_e7f0f40 | 0x2035F0 | WRITE (addr passed to sub_e805480) | Reset path |

---

## Step 2: Writer function analysis

### Writer 1: sub_e7f5380 at 0xe7f5452 (debug overlay setup/update)

**Function**: sub_e7f5380 [0xe7f5380..0xe7fcf12) — debug overlay render function
**Caller**: None (likely called via function pointer/vtable)
**Relevant phase**: 0xe7f5452..0xe7f545a

```
0xE7F5452  lea rcx,[r12+0x2035F0]        ; R a0+0x2035F0 — address of occlusion query counter
0xE7F545A  call 0xE805480                ; -> sub_e805480
```

**Preceding context (0xe7f5440..0xe7f5452)**:
```
0xE7F5440  cmp [r12+0xD440],ecx
0xE7F5448  je short 0xE7F5465
0xE7F544A  mov [r12+0xD440],ecx
0xE7F5452  lea rcx,[r12+0x2035F0]
0xE7F545A  call 0xE805480
```

**What increments/sets it**: The call to **sub_e805480** with RCX = address of context+0x2035F0. sub_e805480 is a list/queue management function that appears to **reset or initialize a queue structure** at the given address (it zeroes 0x40 bytes at the target and sets up next/end pointers).

**D3D12/bgfx call preceding it**: None directly. The preceding code checks `r12+0xD440` (a frame/config version) and `rdi+0xDC5810` (device caps/flags). No D3D12 query API calls (BeginQuery/EndQuery/ResolveQueryData/GetData) are visible in this function.

**Neighbouring fields (from same function)**:
| Offset | Size | R/W | Meaning | Tag |
|--------|------|-----|---------|-----|
| 0x2035D0 | 4 | W | Sibling counter (written at 0xe7f5482, 0xe7f5b2c) | [V] |
| 0x2035F0 | 4 | W | **Occlusion query counter** (this unit) | [V] |
| 0xD440 | 4 | R/W | Frame/config version guard | [V] |
| 0xD444 | 1 | R/W | Bitfield (bit 0x11 = occlusion enabled?) | [V] |
| 0xD3E8 | 4 | R | Feature bitmask | [V] |

**Callees in order**:
1. 0xE805480 (sub_e805480) — queue/list reset at context+0x2035F0 [V]
2. 0xE805480 (sub_e805480) — queue/list reset at context+0x2035D0 [V]

---

### Writer 2: sub_e7f0f40 at 0xe7f1619 (cleanup/reset function)

**Function**: sub_e7f0f40 [0xe7f0f40..0xe7f2f40) — render context cleanup/reset
**Caller**: None found (0 callers)
**Relevant phase**: 0xe7f160d..0xe7f1620

```
0xE7F160D  lea rcx,[rsi+0x2035D0]        ; R a0+0x2035D0
0xE7F1614  call 0xE805480                ; -> sub_e805480
0xE7F1619  lea rcx,[rsi+0x2035F0]        ; R a0+0x2035F0
0xE7F1620  call 0xE805480                ; -> sub_e805480
```

**What increments/sets it**: Same **sub_e805480** call pattern — resets the queue structure at context+0x2035F0 (and 0x2035D0). This appears to be a **shutdown/reset path** that clears all queue structures.

**D3D12/bgfx call preceding it**: The function **does call D3D12 vtable functions** earlier (0xe7f0f71, 0xe7f0fa4, 0xe7f0fcb, 0xe7f101e, 0xe7f1092, etc.) via the CFG thunk at [0xF99FFA0]. These appear to be **resource release calls** (Release on COM objects), not query operations. No ID3D12GraphicsCommandList::BeginQuery/EndQuery or ResolveQueryData/GetData calls identified.

**Neighbouring fields (from same function)**: This function manages **four queue structures** at:
- Queue 1: base=0x2035B8, next=0x2035C0, end=0x2035C8, counter=0x2035B0
- Queue 2: base=0x203578, next=0x203580, end=0x203588, counter=0x203570
- Queue 3: base=0x203598, next=0x2035A0, end=0x2035A8, counter=0x203590
- Queue 4: base=0x2035D0, next=?, end=?, counter=0x2035D0? (uses sub_e805480)
- **Target**: base=0x2035F0? (uses sub_e805480)

Each queue structure appears to be 0x48 bytes (based on `add rax,0x48` for next pointer).

**Callees in order (relevant to 0x2035F0)**:
1. 0xE805480 (sub_e805480) at 0xe7f1614 — reset queue at context+0x2035D0 [V]
2. 0xE805480 (sub_e805480) at 0xe7f1620 — **reset queue at context+0x2035F0** [V]

---

### sub_e805480 analysis (the actual writer)

**Function**: sub_e805480 [0xe805480..0xe807480)
**Signature**: `void sub_e805480(struct QueueHeader* q)` where RCX = q
**Purpose**: Reset/initialize a queue header structure (zero 0x40 bytes, set next=base+0x48, end=base+0x48, clear counter)

```
; Entry: RCX = address of queue header (context+0x2035F0 or similar)
0xE805486  mov rsi,rcx                    ; rsi = queue header ptr
0xE805489  mov rdx,[rcx+8]                ; rdx = q->base (q+8)
0xE80548D  mov rdi,[rdx]                  ; rdi = *base (first element)
; ... loop releasing all elements via vtable+0x10 (Release)
0xE805524  mov [rsi+0x10],rdx             ; q->next = base
0xE805528  lea rax,[rdx+0x48]             ; rax = base + 0x48
0xE80552C  cmp rax,[rsi+0x18]             ; compare with q->end
; ... if needed, allocate new buffer via D3D12 (CreateResource at vtable+0x10 of 0x12ADF800)
; ... copy old data to new buffer
0xE80564C  mov [rsi+8],rdi                ; q->base = new_base (or old)
0xE805650  lea rax,[rdi+0x48]             ; rax = new_base + 0x48
0xE805654  mov [rsi+0x18],rax             ; q->end = new_base + 0x48
0xE805658  xorps xmm0,xmm0
0xE80565B  movups [rdi+0x30],xmm0         ; zero 16 bytes at base+0x30
0xE80565F  movups [rdi+0x20],xmm0         ; zero 16 bytes at base+0x20
0xE805663  movups [rdi+0x10],xmm0         ; zero 16 bytes at base+0x10
0xE805667  movups [rdi],xmm0              ; zero 16 bytes at base+0x0
0xE80566A  mov qword ptr [rdi+0x40],0     ; zero qword at base+0x40
0xE805672  mov rax,[rsi+8]
0xE805676  add rax,0x48
0xE80567A  mov [rsi+0x10],rax             ; q->next = base + 0x48
0xE80567E  mov qword ptr [rsi],0          ; **q->counter = 0** (at q+0x0)
```

**Key finding**: The **counter at offset 0x0 of the queue header** (which is context+0x2035F0 when called with RCX=context+0x2035F0) is **zeroed at 0xe80567E**: `mov qword ptr [rsi],0`.

**Structure of queue header (at RCX = context+0x2035F0)**:
| Offset | Size | Field | Meaning |
|--------|------|-------|---------|
| 0x0 | 8 | counter | **Occlusion query count (what we're tracking)** |
| 0x8 | 8 | base | Pointer to element array |
| 0x10 | 8 | next | Next free element pointer |
| 0x18 | 8 | end | End of element array |

**Callees of sub_e805480**:
- 0xEEA6040 (via [0xF99FFA0] CFG thunk) — D3D12 vtable calls (Release, CreateResource) [V]
- 0xEBCE430 (memcpy) [V]

---

## Step 3: Sibling counters in debug overlay (near 0xe7fcab9)

The debug overlay at 0xe7fcab9 prints " Occlusion queries: %3d " reading from context+0x2035F0.
The preceding format string at 0xe7fcb71: " %6d | %6d | %6d | %6d | %6d  " reads five counters:

| Print Order | Offset | Register | Likely Meaning |
|-------------|--------|----------|----------------|
| 1 | 0x2035F0 | eax | **Occlusion queries** (this unit) |
| 2 | 0x2035D0 | ecx | Unknown counter A |
| 3 | 0x2035B0 | edx | Unknown counter B |
| 4 | 0x203570 | r9d | Unknown counter C |
| 5 | 0x203590 | r10d | Unknown counter D |

**Writers for sibling offsets**:

| Offset | Writer RVA | Function | Instruction |
|--------|------------|----------|-------------|
| 0x2035D0 | 0xe7f5482, 0xe7f5b2c, 0xe7f160d | sub_e7f5380, sub_e7f0f40 | lea rcx,[r12/rsi+0x2035D0] → call sub_e805480 |
| 0x2035B0 | 0xe7f11c9 | sub_e7f0f40 | mov qword ptr [rsi+0x2035B0],0 |
| 0x203570 | 0xe7f13e9 | sub_e7f0f40 | mov qword ptr [rsi+0x203570],0 |
| 0x203590 | 0xe7f1602 | sub_e7f0f40 | mov qword ptr [rsi+0x203590],0 |

**All sibling counters are zeroed by sub_e7f0f40 (reset path)** and managed by sub_e805480 (queue reset). The debug overlay reads them but no increment logic is visible in the static binary.

---

## Role guess [I] for ctx+0x2035F0

**Role**: **Occlusion query counter — counts active/completed occlusion queries in a ring buffer / queue structure**

**Evidence**:
1. Debug overlay displays it as " Occlusion queries: %3d " [V: 0xe7fcb30, string at 0xf84056b]
2. It lives at offset 0x0 of a queue header structure managed by sub_e805480 [V: 0xe80567E `mov qword ptr [rsi],0`]
3. The queue header structure (counter, base, next, end) matches a **ring buffer / free-list** for occlusion query objects
4. sub_e805480 releases old elements via D3D12 Release (vtable+0x10) and can allocate new buffers via D3D12 CreateResource [V: 0xe8054ab, 0xe805569 calls via CFG thunk]
5. Two code paths write it: debug overlay setup (sub_e7f5380) and context reset (sub_e7f0f40) — both call sub_e805480 to **reset the queue**, which zeroes the counter

**Missing [UNVERIFIED]**:
- [UNVERIFIED: 0xe8054ab] What D3D12 vtable slot is called at 0xe8054ab? (looks like Release on query objects)
- [UNVERIFIED: 0xe805569] What D3D12 vtable slot at 0xe805569? (looks like CreateResource for query heap)
- [UNVERIFIED: 0xe7f5452] Does sub_e7f5380 ever **increment** the counter, or only reset it? (Only reset observed)
- [UNVERIFIED: ?] Where is the **increment** (when a query is issued)? Not found in static analysis.
- [UNVERIFIED: 0xe7f0f40] Why does this function have 0 callers? Is it dead code or called via function pointer?

---

## Struct fields touched (summary)

| Offset | Size | Direction | Meaning | Tag |
|--------|------|-----------|---------|-----|
| 0x2035F0 | 8 | W (zero) | Occlusion query counter (queue header +0x0) | [V] |
| 0x2035F8 | 8 | W | Queue base pointer (queue header +0x8) | [V] |
| 0x203600 | 8 | W | Queue next pointer (queue header +0x10) | [V] |
| 0x203608 | 8 | W | Queue end pointer (queue header +0x18) | [V] |
| 0x2035D0 | 8 | W | Sibling queue header counter | [V] |
| 0x2035B0 | 8 | W | Sibling queue 1 counter | [V] |
| 0x203570 | 8 | W | Sibling queue 2 counter | [V] |
| 0x203590 | 8 | W | Sibling queue 3 counter | [V] |

---

## TOOL REQUESTS

None — all analysis done with existing rtools (dis, fn, callers, preflight) and manual reading.