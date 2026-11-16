## NEXT

# UNIT U-C4a — DragonFrameResources layout (static analysis)

## Scope
Decode every field of DragonFrameResources (DFR) touched by endFrame 0xC270460 -> dispatcher 0xE9002E0, including its constructor/destructor if findable, and identify who pushes/drains the vector<shared_ptr<Task>> at +0x298/+0x2A0.

All tags: [V] = read from disassembly (rdis), [I] = inferred from use, [?] = not located / unknown.

## Source of truth
- Dispatcher: 0xE9002E0 (size 0xC3A, single caller 0xC270460 = BgfxContext::endFrame)
- Preflight listing: docs/progress/pre/0xe9002e0.md
- DFR pointer loaded at 0xE900483: `mov rdi,[r15+0x20]` where r15 = args arg (rdx at entry), so rdi = DragonFrameResources*
- DFR lives at owner+0x268 (0x67CA3BB: `edx = 0x268; add rdx,[rsi+0x10]`)

## Fields touched by dispatcher 0xE9002E0 (all [V])

| Offset | Size | R/W | Meaning | Evidence (RVA) | Tag |
|--------|------|-----|---------|----------------|-----|
| +0x290 | 8 | R/W | vector<shared_ptr<Task>> first (begin) | R: 0xE900827, 0xE900913, 0xE9009FF, 0xE900A71; W: 0xE900ABA, 0xE900B2D | [V] |
| +0x298 | 8 | R/W | vector<shared_ptr<Task>> last (push cursor) | R: 0xE9004AA, 0xE90091A, 0xE90096F, 0xE900A16; W: 0xE9004C5, 0xE900ABA, 0xE900B3F | [V] |
| +0x2A0 | 8 | R/W | vector<shared_ptr<Task>> end (capacity) | R: 0xE9004B1, 0xE900A7F; W: 0xE900ADD, 0xE900B50 | [V] |

Element size: 0x10 = {Task*, shared_ptr control block*}. Push stores Task* at [last], ctrl at [last+8], then `add [rdi+0x298],0x10`.

## Fields NOT touched by dispatcher (unknown)
- Everything below +0x290 and at/after +0x2A8: no reader/writer found in 0xE9002E0
- Object size: unknown
- No other function touching +0x290/+0x298/+0x2A0 located

## Constructor / destructor
- [UNVERIFIED] No function that constructs or destroys DragonFrameResources was located (scans for +0x290/+0x298/+0x2A0 operand sets and `lea/add reg,0x268` + call produced nothing useful). Ctor/dtor remain OPEN per bgfx-d3d12-dragon.md C4a.

## vector<shared_ptr<Task>> at +0x298/+0x2A0 — who pushes, who drains

**Pushes:** Dispatcher 0xE9002E0 pushes kind==1 task entries:
- `0xE9004AA  mov r15,[rdi+0x298]` — load last cursor
- `0xE9004B1  cmp r15,[rdi+0x2A0]` — compare vs end; if full, jump to grow path at 0xE900824
- `0xE9004BE  mov [r15],r13` — store Task* at slot (r13 = task ptr)
- `0xE9004C1  mov [r15+8],rbx` — store shared_ptr ctrl at slot+8
- `0xE9004C5  add qword ptr [rdi+0x298],0x10` — advance last cursor by element size 0x10

**Grow path (when full):**
- `0xE900827  sub rsi,[rdi+0x290]` — size = last - first
- `0xE900831  sar rcx,4` — element count = size / 0x10
- Allocates new buffer via `call qword ptr [0xF99FFA0]` (sub_eea6040)
- `0xE900906  mov [r14+rsi],r13` / `0xE90090A  mov [r14+rsi+8],rbx` — copy entries to new buffer
- Commits: `0xE900ABA  mov [rdi+0x290],r14`; `0xE900ACC  mov [rdi+0x298],rax`; `0xE900ADD  mov [rdi+0x2A0],rax`

**Drains / clears:** Same dispatcher drains all tasks (decrements shared_ptr refcounts):
- `0xE900A39  mov r15,[r13+8]` — load ctrl from slot+8
- `0xE900A42  lock dec dword ptr [r15+8]` — decrement strong count
- `0xE900A52  call qword ptr [0xF99FFA0]` — free task object if strong hits 0
- `0xE900A58  lock dec dword ptr [r15+0xC]` — decrement weak count
- `0xE900A69  call qword ptr [0xF99FFA0]` — free ctrl block if weak hits 0
- Alternate drain block at 0xE900AF1..0xE900B22 (same pattern, r13 as cursor)

**Commit (reset after drain):**
- `0xE900ABA  mov [rdi+0x290],r14` — first = newBase (often null/0)
- `0xE900ACC  mov [rdi+0x298],rax` — last = newLast
- `0xE900ADD  mov [rdi+0x2A0],rax` — end = newEnd
- Alternate commit at 0xE900B2D..0xE900B50

## Call graph
- Only caller of 0xE9002E0: 0xC270460 (BgfxContext::endFrame), which forwards DFR& as args+0x20 (rdx)
- DFR pointer loaded from [args+0x20] at `0xE900483  mov rdi,[r15+0x20]`
- Callees of interest: sub_eea6040 (allocator/free via [0xF99FFA0]), sub_e935700 (relocate helper at 0xE900AB1)

## Verification quotes (for python tools/sigs/verify_oc.py)

0xE900483  mov rdi,[r15+0x20]
0xE9004AA  mov r15,[rdi+0x298]
0xE9004B1  cmp r15,[rdi+0x2A0]
0xE9004BE  mov [r15],r13
0xE9004C1  mov [r15+8],rbx
0xE9004C5  add qword ptr [rdi+0x298],0x10
0xE900827  sub rsi,[rdi+0x290]
0xE900906  mov [r14+rsi],r13
0xE90090A  mov [r14+rsi+8],rbx
0xE900913  mov r13,[rdi+0x290]
0xE90091A  mov rax,[rdi+0x298]
0xE90096F  mov rax,[rdi+0x298]
0xE9009FF  mov r13,[rdi+0x290]
0xE900A16  mov rsi,[rdi+0x298]
0xE900A42  lock dec dword ptr [r15+8]
0xE900A52  call qword ptr [0xF99FFA0]
0xE900A58  lock dec dword ptr [r15+0xC]
0xE900A69  call qword ptr [0xF99FFA0]
0xE900A71  mov r13,[rdi+0x290]
0xE900A7F  mov rdx,[rdi+0x2A0]
0xE900ABA  mov [rdi+0x290],r14
0xE900ACC  mov [rdi+0x298],rax
0xE900ADD  mov [rdi+0x2A0],rax
0xE900B2D  mov [rdi+0x290],r14
0xE900B3F  mov [rdi+0x298],rax
0xE900B50  mov [rdi+0x2A0],rax

## Open items
- DragonFrameResources constructor/destructor: NOT FOUND (blocking per bgfx-d3d12-dragon.md C4a)
- Owner type of DFR (the object at +0x268): unknown
- Fields outside +0x290/+0x298/+0x2A0: no reader found, layout unknown
- Object total size: unknown

## TOOL REQUESTS
- Run `python tools/sigs/verify_oc.py docs/progress/oc_U-C4a.md` to confirm all quoted instruction lines match rdis dis output
- If verification passes, next unit: C4b (IntraFrameAllocator) or C7b (frame-graph generator records), per orchestrator direction
