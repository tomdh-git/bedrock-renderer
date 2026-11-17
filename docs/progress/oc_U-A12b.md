## NEXT
- [ ] Verify no stores to Encoder+0x680 in any of the four callers (confirmed: only READs)
- [ ] Find the actual setter API (bgfx::Encoder::setVertexBuffer) that writes Encoder+0x680
- [ ] Cross-reference with BGFX_MAP.md for setVertexBuffer RVA
- [ ] Document the stream-index/handle/offset/count mapping for the setter when found

## Analysis Summary

**Unit U-A12b**: Encoder-side vertex-buffer range table setter identification.

**Key Finding**: The four callers of 0xBC60F10 (L_bc60740.txt, L_bc61140.txt, L_bc61560.txt, L_bc618e0.txt) are **Encoder::submit variants** that **CONSUME** (read) the vertex-buffer range table at Encoder+0x680. **NONE of them WRITE to Encoder+0x680**. The actual setter (bgfx::Encoder::setVertexBuffer) that fills Encoder+0x680 is NOT among these four callers.

Function 0xBC60F10 reads Encoder+0x680 (passed in r8 by callers) and copies/transforms it into Frame+0x8B4778 (SideTable: 0x41 entries of {Binding*, count}).

---

### Caller 1: 0xBC60740 (Encoder::submit primary)
**Listing**: docs/listings/L_bc60740.txt

#### (a) Role Guess [I]
Encoder::submit main path — builds draw sort key, copies encoder state to Frame, calls 0xBC60F10 to flush vertex-buffer ranges.
- Verbatim: `0xbc60b4f  mov r8,[rsi+0x680]` (read Encoder+0x680) → `0xbc60b60  call 0xBC60F10`
- Verbatim: `0xbc60991  mov [rcx+r14*8+0x14700],rax` (store sort key to Frame+0x14700)
- Verbatim: `0xbc60ac0  movaps [rax+rcx+0xB4770],xmm0` (copy encoder state block at Frame+0xB4770)

#### (b) Encoder [reg+off] Read/Write (rsi = encoder this)
| Offset | Size | R/W | First Site (RVA) | Meaning |
|--------|------|-----|------------------|---------|
| +0x10  | 2    | W   | 0xbc6087c        | view id (r8w) |
| +0x12  | 2    | W   | 0xbc60881        | (dx) |
| +0x8   | 4    | W   | 0xbc608b9        | sequence/encoder id (r10d) |
| +0xC   | 4    | W   | 0xbc60906        | draw counter (ecx) |
| +0x60  | 8    | W   | 0xbc60b78        | state reset (rax=0x10000500000001F) |
| +0x68  | 8    | W   | 0xbc60b7c        | zeroed |
| +0x70  | 16   | W   | 0xbc60b87        | xmm0 zeroed |
| +0x80  | 16   | W   | 0xbc60b92        | rect/scissor (from 0xF08EF70) |
| +0x90  | 8    | W   | 0xbc60ba3        | 0x100000000 |
| +0x98  | 8    | W   | 0xbc60bb4        | 0x1FFFF00000000 |
| +0xA0  | 2    | W   | 0xbc60bc2        | 0xFFFF |
| +0xA2  | 1    | W   | 0xbc60bbb        | 0 |
| +0xA3  | 2    | W   | 0xbc60bcb        | 0xFF00 |
| +0x40  | 8    | W   | 0xbc60bde        | 0xFFFFFFFF00000000 |
| +0xB4  | 8    | W   | 0xbc60be2        | -1 |
| +0xA8  | 4    | W   | 0xbc60bed        | 0x7FFFFFFF |
| +0xAC  | 8    | W   | 0xbc60bf7        | 0 |
| +0x68C | 4    | W   | 0xbc6083f        | submit counter++ |
| +0x690 | 4    | W   | 0xbc6080f        | draw counter++ |
| +0x694 | 4    | W   | 0xbc609b9        | saved draw index |
| +0x698 | 4    | W   | 0xbc60869        | view strat from ctx |
| +0x6AC | 1    | R   | 0xbc60859        | view id byte |
| +0x6AD | 1    | R   | 0xbc60773        | submitted flag |
| +0x688 | 1    | W   | 0xbc60aab        | vertex-buffer ranges dirty flag (0/1) |
| **+0x680** | 8  | **R** | **0xbc60b4f**    | **vertex-buffer range table ptr (READ ONLY)** |

#### (c) Callees in Order
1. 0xBC60D10 (encoder reset/path) — at 0xbc6080a, 0xbc60797
2. **0xBC60F10** (vertex-buffer range table flush) — at 0xbc60b60
3. 0xBC76610 (hash/compute) — at 0xbc60a50
4. 0xBC7A7C0 (Frame side-table init) — at 0xbc60b2e
5. 0xEEC6EC0 (descriptor copy) — at 0xbc60b4a
6. 0xEEC6ED0 (memset/zero) — at 0xbc60ce7 (cleanup path)
7. 0xE951550 (stack check fail) — at 0xbc60d0a

#### (d) Stream-Index/Handle/Offset/Count Argument Map
**At call to 0xBC60F10 (0xbc60b60):**
- rcx = [rsi] = Frame pointer
- rdx = edi = draw index (stream index)
- r8 = [rsi+0x680] = **Encoder vertex-buffer range table pointer (READ)**
- No handle/offset/count visible here; they are encoded inside the table at Encoder+0x680

#### (e) Public bgfx Call
**Encoder::submit** (not setVertexBuffer). This is the submit path that *consumes* the vertex buffer ranges previously set via setVertexBuffer.

---

### Caller 2: 0xBC61140 (Encoder::submit variant #2)
**Listing**: docs/listings/L_bc61140.txt

#### (a) Role Guess [I]
Encoder::submit variant for instanced/indirect draws — different encoder state layout (writes to +0xC0..+0xE2), same vertex-buffer range consumption.
- Verbatim: `0xbc613d8  mov r8,[rsi+0x680]` → `0xbc613e9  call 0xBC60F10`
- Verbatim: `0xbc61235  mov [rsi+0xC8],eax` (writes instance data to encoder+0xC8)
- Verbatim: `0xbc6124a  mov [rsi+0xE0],ax` (writes instance count)

#### (b) Encoder [reg+off] Read/Write (rsi = encoder this)
| Offset | Size | R/W | First Site (RVA) | Meaning |
|--------|------|-----|------------------|---------|
| +0x8   | 4    | W   | 0xbc61278        | zeroed |
| +0x10  | 2    | W   | 0xbc61273        | view id (r8w) |
| +0x12  | 2    | W   | 0xbc6127f        | (dx) |
| +0xC   | 4    | W   | 0xbc6129b        | draw counter (edx) |
| +0xC0  | 8    | W   | 0xbc612ed        | saved draw index (rax from +0x694) |
| +0xC8  | 4    | W   | 0xbc61235        | instance base (eax from +0x7C) |
| +0xD0  | 4    | W   | 0xbc61259        | instance count (r9d) |
| +0xD4  | 4    | W   | 0xbc61266        | start instance (r10d) |
| +0xD8  | 4    | W   | 0xbc6126d        | base vertex (ecx) |
| +0xE0  | 2    | W   | 0xbc6124a        | index count (ax) |
| +0xE2  | 1    | W   | 0xbc612e0        | view id byte |
| +0x68C | 4    | W   | 0xbc61206        | submit counter++ |
| +0x690 | 4    | W   | 0xbc611fb        | draw counter++ |
| +0x694 | 4    | W   | 0xbc612ed        | saved draw index |
| +0x698 | 4    | W   | 0xbc61225        | view strat from ctx |
| +0x6AC | 1    | R   | 0xbc6121e        | view id byte |
| +0x6AD | 1    | R   | 0xbc61172        | submitted flag |
| +0x688 | 1    | W   | 0xbc61372        | vertex-buffer ranges dirty flag (0/1) |
| **+0x680** | 8  | **R** | **0xbc613d8**    | **vertex-buffer range table ptr (READ ONLY)** |

#### (c) Callees in Order
1. 0xBC60D10 — at 0xbc611f6, 0xbc61193
2. **0xBC60F10** — at 0xbc613e9
3. 0xBC76610 — at 0xbc61317
4. 0xBC7A7C0 — at 0xbc613b7
5. 0xEEC6EC0 — at 0xbc613d3
6. 0xEEC6ED0 — at 0xbc61507 (cleanup)
7. 0xE951550 — at 0xbc6154b

#### (d) Stream-Index/Handle/Offset/Count Argument Map
**At call to 0xBC60F10 (0xbc613e9):**
- rcx = [rsi] = Frame pointer
- rdx = edi = draw index
- r8 = [rsi+0x680] = Encoder vertex-buffer range table pointer (READ)
- Instance params at encoder+0xC0..+0xE0 (base vertex, start instance, instance count, index count) are separate from vertex-buffer ranges

#### (e) Public bgfx Call
**Encoder::submit (instanced variant)** — consumes vertex buffers, not the setter.

---

### Caller 3: 0xBC61560 (Encoder::submit variant #3)
**Listing**: docs/listings/L_bc61560.txt

#### (a) Role Guess [I]
Encoder::submit variant for vertex-buffer-offset draws — writes handle/offset to encoder+0x100/+0x108 before submit.
- Verbatim: `0xbc6178f  mov r8,[rsi+0x680]` → `0xbc617a0  call 0xBC60F10`
- Verbatim: `0xbc61645  mov [rsi+0x100],r8` (handle from arg r8)
- Verbatim: `0xbc6164c  mov [rsi+0x108],r9` (offset from arg r9)

#### (b) Encoder [reg+off] Read/Write (rsi = encoder this)
| Offset | Size | R/W | First Site (RVA) | Meaning |
|--------|------|-----|------------------|---------|
| +0x8   | 4    | W   | 0xbc61659        | zeroed |
| +0x10  | 2    | W   | 0xbc61653        | zeroed (view id?) |
| +0x12  | 2    | W   | 0xbc61660        | (dx) |
| +0xC   | 4    | W   | 0xbc6167c        | draw counter (edx) |
| **+0x100** | 8  | **W** | **0xbc61645**    | **vertex buffer handle (from arg r8)** |
| **+0x108** | 8  | **W** | **0xbc6164c**    | **vertex buffer offset (from arg r9)** |
| +0x68C | 4    | W   | 0xbc6161a        | submit counter++ |
| +0x690 | 4    | W   | 0xbc6160f        | draw counter++ |
| +0x694 | 4    | W   | 0xbc617b2        | saved draw index |
| +0x698 | 4    | W   | 0xbc61638        | view strat from ctx |
| +0x6AC | 1    | R   | 0xbc61631        | view id byte |
| +0x6AD | 1    | R   | 0xbc61584        | submitted flag |
| +0x688 | 1    | W   | 0xbc6173c        | vertex-buffer ranges dirty flag (0/1) |
| **+0x680** | 8  | **R** | **0xbc6178f**    | **vertex-buffer range table ptr (READ ONLY)** |

#### (c) Callees in Order
1. 0xBC60D10 — at 0xbc6160a, 0xbc615a5
2. **0xBC60F10** — at 0xbc617a0
3. 0xBC76610 — at 0xbc616e1
4. 0xBC7A7C0 — at 0xbc6176d
5. 0xEEC6EC0 — at 0xbc6178a
6. 0xEEC6ED0 — at 0xbc61887 (cleanup)
7. 0xE951550 — at 0xbc618cc

#### (d) Stream-Index/Handle/Offset/Count Argument Map
**At call to 0xBC60F10 (0xbc617a0):**
- rcx = [rsi] = Frame pointer
- rdx = edi = draw index
- r8 = [rsi+0x680] = Encoder vertex-buffer range table pointer (READ)
- **Handle at encoder+0x100 (from incoming r8), Offset at encoder+0x108 (from incoming r9)** — these are the setVertexBuffer arguments staged before submit

#### (e) Public bgfx Call
**Encoder::submit (vertex-buffer-offset variant)** — the handle/offset at +0x100/+0x108 match `setVertexBuffer(handle, offset)` staging. The actual `setVertexBuffer` call would have written these earlier.

---

### Caller 4: 0xBC618E0 (Encoder::submit variant #4)
**Listing**: docs/listings/L_bc618e0.txt

#### (a) Role Guess [I]
Encoder::submit variant for indexed draws with extra resource binding — most complex, writes to +0xC0..+0xE3 and calls EEC6EC0 twice.
- Verbatim: `0xbc61b8a  mov r8,[rsi+0x680]` → `0xbc61b9b  call 0xBC60F10`
- Verbatim: `0xbc619eb  mov [rsi+0xC8],eax` (instance data)
- Verbatim: `0xbc61bae  call 0xEEC6EC0` with rdx=rbx (arg r8), r8d=0x1E8 (extra binding copy)

#### (b) Encoder [reg+off] Read/Write (rsi = encoder this)
| Offset | Size | R/W | First Site (RVA) | Meaning |
|--------|------|-----|------------------|---------|
| +0x8   | 4    | W   | 0xbc61a27        | zeroed |
| +0x10  | 2    | W   | 0xbc61a21        | 0xFFFF (special view id?) |
| +0x12  | 2    | W   | 0xbc61a2e        | (dx) |
| +0xC   | 4    | W   | 0xbc61a4a        | draw counter (edx) |
| +0xC0  | 8    | W   | 0xbc61a9c        | saved draw index (rax from +0x694) |
| +0xC8  | 4    | W   | 0xbc619eb        | instance base (eax from +0x7C) |
| +0xD0  | 4    | W   | 0xbc61a14        | (r10d from stack) |
| +0xD4  | 4    | W   | 0xbc61a1b        | (ecx from stack) |
| +0xE0  | 2    | W   | 0xbc619f8        | index count (ax from +0x9E) |
| +0xE2  | 1    | W   | 0xbc61a8f        | view id byte |
| +0xE3  | 1    | W   | 0xbc61a07        | flag = 1 |
| +0x68C | 4    | W   | 0xbc619c2        | submit counter++ |
| +0x690 | 4    | W   | 0xbc619ab        | draw counter++ |
| +0x694 | 4    | W   | 0xbc61cee        | saved draw index |
| +0x698 | 4    | W   | 0xbc619db        | view strat from ctx |
| +0x6AC | 1    | R   | 0xbc619cc        | view id byte |
| +0x6AD | 1    | R   | 0xbc61916        | submitted flag |
| +0x688 | 1    | W   | 0xbc61b21        | vertex-buffer ranges dirty flag (0/1) |
| **+0x680** | 8  | **R** | **0xbc61b8a**    | **vertex-buffer range table ptr (READ ONLY)** |

#### (c) Callees in Order
1. 0xBC60D10 — at 0xbc619a6, 0xbc61937
2. **0xBC60F10** — at 0xbc61b9b
3. 0xBC76610 — at 0xbc61ac6
4. 0xBC7A7C0 — at 0xbc61b69
5. 0xEEC6EC0 — at 0xbc61b85 (primary), **0xbc61bae (secondary, rdx=rbx=arg r8, r8d=0x1E8)**
6. 0xEEC6ED0 — at 0xbc61dc7 (cleanup)
7. 0xE951550 — at 0xbc61e0c

#### (d) Stream-Index/Handle/Offset/Count Argument Map
**At call to 0xBC60F10 (0xbc61b9b):**
- rcx = [rsi] = Frame pointer
- rdx = edi = draw index
- r8 = [rsi+0x680] = Encoder vertex-buffer range table pointer (READ)
- rbx = incoming r8 (handle), r15 = incoming r9 — used in second EEC6EC0 call at 0xbc61bae for extra binding

#### (e) Public bgfx Call
**Encoder::submit (indexed + extra binding variant)** — consumes vertex buffers, not the setter.

---

### The Actual Setter (NOT in these four callers)
**Function 0xBC60F10** (docs/listings/L_bc60f10.txt) is the **consumer** that reads Encoder+0x680 and writes Frame+0x8B4778.

**Stores in 0xBC60F10 (from stores.py):**
- `0xbc61009  movups [r13],xmm6` — zero Frame SideTable entry (r13 = rsi+r15 = Frame+0x8B4778 + index)
- `0xbc61080  mov [rsi+0x410],eax` — write count to SideTable[stream].count
- `0xbc6108e  mov [rcx+0x410],eax` — write count to encoder table copy
- `0xbc610fe  movups [rbx],xmm6` — zero encoder table entry (cleanup path)
- `0xbc6112b  mov dword ptr [rsi+0x410],0` — zero SideTable count (cleanup)

**The SETTER that writes Encoder+0x680** is the public **bgfx::Encoder::setVertexBuffer** (or similar), which:
- Takes (stream index, handle, offset, count)
- Allocates/updates the 0x41-entry table at Encoder+0x680
- Sets the dirty flag at Encoder+0x688 = 1

[UNVERIFIED: 0xBC60F10 caller setter RVA — need to find the actual setVertexBuffer function that writes Encoder+0x680]

---

## TOOL REQUESTS
- stores.py | LISTING file → store table | Worked perfectly; no changes needed
- rtools.callees | RVA → callee list | Worked perfectly; no changes needed
- Need: xref.py callers on candidate setVertexBuffer RVAs to find the setter
- Need: rdis walk from candidate setter to trace stores to [reg+0x680]