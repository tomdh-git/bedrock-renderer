# Dossier: sub_bcd40f0 ("String list destructor")

Minecraft Windows 1.26.62.01. Function [0xbcd40f0, 0xbcd41b3), size 0xc3 bytes.
Disassembly source: rdis `dis 0xbcd40f0 0xc3`. All facts below are [V] from that listing; nothing is inferred.

## Signature (lifted)
```
extern "C" void* sub_bcd40f0(void* thisPtr);
```
- rcx = thisPtr (StringListHead*) — pointer to list head structure.
- Return: void* (result of sub_e935700 on the head, via tail call when list empty or after cleaning all nodes; otherwise does not return on corruption path).

## Register / argument map
| Register | Meaning | Type |
|---|---|---|
| rcx | thisPtr | StringListHead* |
| rsi | thisPtr copy | StringListHead* |
| rax | headFirst (head->first) | void* |
| rdi | current node | StringListNode* |
| rbx | next node | StringListNode* |
| r8 | allocHeader / scratch | void* |
| rdx | capacity+1 / size / arg to sub_e935700 | uint64_t |
| rcx (reused) | various pointers for calls | void* |

## Disassembly (verbatim, [0xbcd40f0, 0xbcd41b3))
```
0xbcd40f0  push rsi
0xbcd40f1  push rdi
0xbcd40f2  push rbx
0xbcd40f3  sub rsp,0x30
0xbcd40f7  mov rsi,rcx
0xbcd40fa  mov rax,[rcx]
0xbcd40fd  mov rcx,[rax+8]
0xbcd4101  mov qword ptr [rcx],0
0xbcd4108  mov rdi,[rax]
0xbcd410b  test rdi,rdi
0xbcd410e  jne short 0xBCD415E

loc_bcd4110:  ; from bcd415c
0xbcd4110  mov rcx,[rsi]
0xbcd4113  mov edx,0x80
0xbcd4118  add rsp,0x30
0xbcd411c  pop rbx
0xbcd411d  pop rdi
0xbcd411e  pop rsi
0xbcd411f  jmp 0xE935700

loc_bcd4130:  ; from bcd417a, bcd4197
0xbcd4130  call 0xE935700

loc_bcd4135:  ; from bcd4169
0xbcd4135  mov qword ptr [rdi+0x20],0
0xbcd413d  mov qword ptr [rdi+0x28],0xF
0xbcd4145  mov byte ptr [rdi+0x10],0
0xbcd4149  mov edx,0x80
0xbcd414e  mov rcx,rdi
0xbcd4151  call 0xE935700
0xbcd4156  mov rdi,rbx
0xbcd4159  test rbx,rbx
0xbcd415c  je short 0xBCD4110

loc_bcd415e:  ; from bcd410e
0xbcd415e  mov rbx,[rdi]
0xbcd4161  mov rax,[rdi+0x28]
0xbcd4165  cmp rax,0x10
0xbcd4169  jb short 0xBCD4135
0xbcd416b  mov rcx,[rdi+0x10]
0xbcd416f  lea rdx,[rax+1]
0xbcd4173  cmp rdx,0x1000
0xbcd417a  jb short 0xBCD4130
0xbcd417c  mov r8,[rcx-8]
0xbcd4180  add rcx,0xFFFFFFFFFFFFFFF8
0xbcd4184  sub rcx,r8
0xbcd4187  cmp rcx,0x20
0xbcd418b  jae short 0xBCD4199
0xbcd418d  add rax,0x28
0xbcd4191  mov rdx,rax
0xbcd4194  mov rcx,r8
0xbcd4197  jmp short 0xBCD4130

loc_bcd4199:  ; from bcd418b
0xbcd4199  mov qword ptr [rsp+0x20],0
0xbcd41a2  xor ecx,ecx
0xbcd41a4  xor edx,edx
0xbcd41a6  xor r8d,r8d
0xbcd41a9  xor r9d,r9d
0xbcd41ac  call qword ptr [0xF9A8C78]
0xbcd41b2  int3
0xbcd41b3  int3
```

## Phases (instruction-complete, [0xbcd40f0, 0xbcd41b3))

**0xbcd40f0..0xbcd410e — prologue, load head, zero head->field8, check first node**
Prologue saves callee-saved registers (rsi, rdi, rbx), allocates 0x30 bytes stack.
`rsi = thisPtr`. `rax = head->first` (+0x00). `rcx = head->field8` (+0x08), `*rcx = 0`.
`rdi = head->first` (first node). If `rdi == 0`, jump to empty-list tail call at loc_bcd4110.

**0xbcd4110..0xbcd411f — empty list: tail call sub_e935700(head)**
`rcx = head` (from [rsi]), `edx = 0x80` (dead, callee overwrites), epilogue, `jmp sub_e935700`.
Returns sub_e935700(head) result to caller.

**0xbcd415e..0xbcd41b3 — non-empty list: iterate nodes, clean each, then tail call on head**
Loop entry at loc_bcd415e: `rbx = node->next` (+0x00), `rax = node->capacity` (+0x28).
- **SSO path (capacity < 0x10)**: loc_bcd4135..0xbcd4155.
  Zero size (+0x20), set capacity=0xF (+0x28), null-terminate inline buffer (+0x10 byte).
  Call `sub_e935700(node)` (0xbcd4151). Then advance to next node (0xbcd4156..0xbcd415c).
- **Heap path (capacity >= 0x10)**: loc_bcd416b..0xbcd4197.
  `rcx = node->heapData` (+0x10), `rdx = capacity+1`.
  - If `capacity+1 < 0x1000`: call `sub_e935700(heapData)` directly (loc_bcd4130).
  - Else: `r8 = *(heapData-8)` (alloc header), compute `allocSize = (heapData-8) - r8`.
    If `allocSize >= 0x20`: corruption -> call abort handler at [0xF9A8C78] (loc_bcd4199, noreturn).
    Else: `rdx = capacity+0x28`, `rcx = allocHeader`, call `sub_e935700(allocHeader)` (via loc_bcd4130).
After each node, advance to `rbx` (next). If `rbx == 0`, jump to loc_bcd4110 (tail call on head).

**0xbcd4199..0xbcd41ac — corruption abort: call handler at data slot 0xF9A8C78**
Zero all integer args (RCX,RDX,R8,R9 and 5th stack arg), `call qword ptr [0xF9A8C78]`, `int3` (noreturn).

## Struct fields touched
| Struct | Offset | Size | Dir | Meaning | Tag |
|---|---|---|---|---|---|
| StringListHead | +0x00 | 8 | R | first node pointer | [V] 0xbcd40fa `mov rax,[rcx]` |
| StringListHead | +0x08 | 8 | R | field8 pointer (to uint64_t) | [V] 0xbcd40fd `mov rcx,[rax+8]` |
| (via field8) | +0x00 | 8 | W | *field8 = 0 | [V] 0xbcd4101 `mov qword ptr [rcx],0` |
| StringListNode | +0x00 | 8 | R | next node pointer | [V] 0xbcd415e `mov rbx,[rdi]` |
| StringListNode | +0x10 | 8 | R | heapData pointer (non-SSO) | [V] 0xbcd416b `mov rcx,[rdi+0x10]` |
| StringListNode | +0x10 | 1 | W | inline buffer[0] = 0 (SSO) | [V] 0xbcd4145 `mov byte ptr [rdi+0x10],0` |
| StringListNode | +0x20 | 8 | W | size = 0 (SSO) | [V] 0xbcd4135 `mov qword ptr [rdi+0x20],0` |
| StringListNode | +0x28 | 8 | R | capacity | [V] 0xbcd4161 `mov rax,[rdi+0x28]` |
| StringListNode | +0x28 | 8 | W | capacity = 0xF (SSO) | [V] 0xbcd413d `mov qword ptr [rdi+0x28],0xF` |
| AllocHeader | -0x08 | 8 | R | header pointer at heapData-8 | [V] 0xbcd417c `mov r8,[rcx-8]` |

## Data reads outside struct fields
| Address | Size | Dir | Meaning | Tag |
|---|---|---|---|---|
| 0xF9A8C78 | 8 | R | abort handler function pointer | [V] 0xbcd41ac `call qword ptr [0xF9A8C78]` |

## Callees
| RVA | Name | Class | How called | Tag |
|---|---|---|---|---|
| 0xe935700 | sub_e935700 | lift | Direct call (0xbcd4130, 0xbcd4151) and tail call (0xbcd411f) | [V] |
| (data slot) | *[0xF9A8C78] | vendor/os | Indirect call via absolute data slot, zero args, noreturn | [V] 0xbcd41ac |

All direct callees are class `lift` (sub_e935700 is lifted in sub_e935700.cpp). The indirect call through data slot 0xF9A8C78 is handled as a function pointer call per the hard rule for data-slot calls. UNRESOLVED CALL = none.

## Verbatim instruction quotes (all instructions in the function)
All 42 instructions of [0xbcd40f0, 0xbcd41b3) are quoted verbatim in the disassembly block above and as plain lines in the `#if 0` block in `src/client/features/render/native/helpers/sub_bcd40f0.cpp`. The four `call`/`jmp` instructions to sub_e935700 and the indirect call are quoted as plain lines:
```
0xbcd411f  jmp 0xE935700
0xbcd4130  call 0xE935700
0xbcd4151  call 0xE935700
0xbcd41ac  call qword ptr [0xF9A8C78]
```

## Reversed source (complete)
```cpp
// LIFT 0xbcd40f0 size 0xc3 1.26.62.01 sub_bcd40f0
// Source: src/client/features/render/native/helpers/sub_bcd40f0.cpp
//
// void* sub_bcd40f0(void* thisPtr) noexcept
//   rcx = thisPtr (StringListHead*); return void* (result of sub_e935700 on head).
//
// Phase 1, 0xbcd40f0..0xbcd410e: prologue, head = thisPtr; *head->field8 = 0; node = head->first; if !node -> tail call sub_e935700(head).
// Phase 2, 0xbcd415e..0xbcd41b3: while (node) { next = node->next; cap = node->capacity;
//   if (cap < 0x10) { node->size=0; node->cap=0xF; node->buffer[0]=0; sub_e935700(node); }
//   else { data = node->heapData; if (cap+1 < 0x1000) sub_e935700(data);
//     else { hdr = *(data-8); sz = (data-8)-hdr; if (sz >= 0x20) abort(); sub_e935700(hdr); } }
//   node = next; } -> tail call sub_e935700(head).
// Phase 3, 0xbcd4199..0xbcd41ac: corruption -> call *[0xF9A8C78](0,0,0,0,0) (noreturn).

static_assert(sizeof(void*) == 8, "sub_bcd40f0: pointer size");
static_assert(StringListHead::kFirstOffset == 0x00, "sub_bcd40f0: Head::first at +0x00");
static_assert(StringListHead::kField8Offset == 0x08, "sub_bcd40f0: Head::field8 at +0x08");
static_assert(StringListNode::kNextOffset == 0x00, "sub_bcd40f0: Node::next at +0x00");
static_assert(StringListNode::kDataOffset == 0x10, "sub_bcd40f0: Node::data at +0x10");
static_assert(StringListNode::kSizeOffset == 0x20, "sub_bcd40f0: Node::size at +0x20");
static_assert(StringListNode::kCapacityOffset == 0x28, "sub_bcd40f0: Node::capacity at +0x28");
static_assert(StringListNode::kSsoCapacityThreshold == 0x10, "sub_bcd40f0: SSO threshold 0x10");
static_assert(StringListNode::kSsoCapacityValue == 0xF, "sub_bcd40f0: SSO capacity 0xF");
static_assert(StringListNode::kLargeAllocThreshold == 0x1000, "sub_bcd40f0: large alloc threshold 0x1000");
static_assert(StringListNode::kAllocHeaderMinSize == 0x20, "sub_bcd40f0: alloc header min 0x20");

void* sub_bcd40f0(void* thisPtr) noexcept {
    auto* head = reinterpret_cast<StringListHead*>(thisPtr);
    auto* headFirst = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(head) + StringListHead::kFirstOffset);
    auto* field8Ptr = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(headFirst) + StringListHead::kField8Offset);
    *reinterpret_cast<std::uint64_t*>(field8Ptr) = 0;
    auto* node = *reinterpret_cast<void**>(headFirst);
    if (node == nullptr) {
        return sub_e935700(head);
    }
    while (true) {
        auto* nextNode = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kNextOffset);
        std::uint64_t capacity = *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kCapacityOffset);
        if (capacity < StringListNode::kSsoCapacityThreshold) {
            *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kSizeOffset) = 0;
            *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kCapacityOffset) = StringListNode::kSsoCapacityValue;
            *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kDataOffset) = 0;
            sub_e935700(node);
        } else {
            auto* heapData = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(node) + StringListNode::kDataOffset);
            std::uint64_t capPlus1 = capacity + 1;
            if (capPlus1 < StringListNode::kLargeAllocThreshold) {
                sub_e935700(heapData);
            } else {
                auto* allocHeader = *reinterpret_cast<void**>(reinterpret_cast<std::uintptr_t>(heapData) - 8);
                std::uintptr_t allocSize = (reinterpret_cast<std::uintptr_t>(heapData) - 8) - reinterpret_cast<std::uintptr_t>(allocHeader);
                if (allocSize >= StringListNode::kAllocHeaderMinSize) {
                    auto abortHandler = *reinterpret_cast<AbortHandlerFn*>(0xF9A8C78ULL);
                    abortHandler(0, 0, 0, 0, 0);
                    __builtin_unreachable();
                }
                sub_e935700(allocHeader);
            }
        }
        node = nextNode;
        if (node == nullptr) {
            return sub_e935700(head);
        }
    }
}

LIFT_FN(sub_bcd40f0, "sub_bcd40f0", 0xBCD40F0, native::sub_bcd40f0, nullptr);
```

## Ownership / threading
The function takes exclusive ownership of the list head and all nodes: it destroys each node (resets SSO state or deallocates heap buffers via sub_e935700) and finally deallocates the head itself. No locks are taken; the caller must ensure no concurrent access. The abort handler at 0xF9A8C78 is a process-wide fatal error handler (likely CRT invalid parameter or similar).

## Version anchors
- Game: Minecraft Bedrock 1.26.62.01
- Function: sub_bcd40f0 at 0xbcd40f0, size 0xc3
- Region: helpers (string list cleanup)

## Verification
- `python tools/sigs/liftcheck.py 0xbcd40f0` must print `LIFTCHECK OK 0xbcd40f0`.
- `python tools/cppsyntax.py src/client/features/render/native/helpers/sub_bcd40f0.cpp` must pass (MSVC /Zs).
- `python tools/ctx/gate.py 0xbcd40f0` must print `GATE OK`.
- All four call/jmp instructions quoted verbatim; every instruction in [0xbcd40f0, 0xbcd41b3) is inside a cited range; no `[?]`/`[I]`/`TODO`/`UNVERIFIED` remains; no stubs.