## NEXT
Step 3: List every [reg+off] store of the owner object constructor for offsets 0x268..0x2A8 with quoted `0xRVA  instr` (BLOCKED: constructor not found)

# UNIT U-C4a2 — Owner object of DragonFrameResources

## Scope
Find the owner object that embeds DragonFrameResources at offset +0x268. The call to BgfxContext::endFrame at 0x67ca3cd passes rdx=[rsi+0x10]+0x268 as DragonFrameResources&.

## Source of truth
- Frame renderer: 0x67c9c20 (size 0x966)
- Call to BgfxContext::endFrame at 0x67ca3cd: `rdx = [rsi+0x10] + 0x268` (DragonFrameResources&)
- DFR is embedded at +0x268 of an owner object

## Step 1: Analyze 0x67c9c20 to find [rsi+0x10] [V]

From the function disassembly (rdis fn 0x67c9c20 --max 200):

```
0x67c9c4d  mov rsi,rcx                                    ; rsi = rcx (first argument) [V]
0x67c9c50  mov rbx,[rcx+8]                               ; R a0+0x8 [V]
0x67c9c54  mov rax,[rcx+0x20]                            ; R a0+0x20 [V]
0x67c9c58  mov rax,[rax]                                 ; R *(a0+0x20)+0x0 [V]
0x67c9c5b  mov rdi,[rax+0x18]                            ; R *(*(a0+0x20)+0x0)+0x18 [V]
```

At 0x67c9c4d: `mov rsi, rcx` - rsi is assigned from rcx, which is the first argument (a0) to the Frame renderer function.

At 0x67ca3bb-0x67ca3c0:
```
0x67ca3bb  mov edx,0x268
0x67ca3c0  add rdx,[rsi+0x10]
```

So [rsi+0x10] = [rcx+0x10] = the owner object pointer (since rsi=rcx).

The closure structure at rcx (rsi) has:
- +0x08: some pointer (rbx, used later) [V]
- +0x10: owner object pointer (DragonFrameResources owner) [V]
- +0x20: pointer to FrameContext (BgfxFrameBuilder+0x28) [V]

At 0x67c9c54-0x67c9c5b: closure+0x20 points to FrameContext, and FrameContext+0x18 gives the Context base (used for resource sets at +0x4C8/+0x4F8/+0x710/+0x958 via 0xA784C0).

The owner object at closure+0x10 embeds DragonFrameResources at +0x268.

## Step 2: Find the owner object and its constructor [V/I]

From BgfxFrameBuilder::endFrame (0x66232b0) analysis:

- BgfxFrameBuilder `this` is in RCX at entry, saved at `rbp+0x19D0` [V]
- At 0x6623308: `mov rax, [rcx+0x28]` loads FrameContext pointer from BgfxFrameBuilder+0x28 [V]
- The stack slot `rbp+0x1970` is set at 0x66243A6: `mov [rbp+0x1970], rcx` where `rcx = BgfxFrameBuilder+0x28` [V]

At 0x662DAA1-0x662DAAE (call to 0xC288990):
```
0x662DAA1  mov eax,[rbp+0x1970]                           ; rax = BgfxFrameBuilder+0x28 [V]
0x662DAA7  mov rax,[rax]                                  ; rax = FrameContext* [V]
0x662DAAA  mov rcx,[rax+0x18]                             ; rcx = FrameContext+0x18 = owner object* [V]
0x662DAAE  call 0xC288990                                 ; passes owner object to resource set processor [V]
```

Thus: **Owner object = FrameContext+0x18** where **FrameContext = *(BgfxFrameBuilder+0x28)**.

FrameContext is a separate object pointed to by BgfxFrameBuilder+0x28. The owner object is a member (pointer) at FrameContext+0x18.

The owner object embeds DragonFrameResources at +0x268. DragonFrameResources size >= 0x2A8 (has vector<shared_ptr<Task>> at +0x290/+0x298/+0x2A0 per oc_U-C4a.md). So owner object size >= 0x268 + 0x2A8 = 0x510.

## Step 2a: Locate FrameContext constructor [I]

FrameContext is allocated/initialized by BgfxFrameBuilder. The BgfxFrameBuilder constructor (not yet located) would allocate FrameContext and store it at +0x28.

FrameContext+0x18 (owner object pointer) must be initialized to point to an allocated owner object.

Candidate constructors to check:
1. FrameContext constructor - initializes +0x18 to owner object
2. Owner object constructor - initializes DragonFrameResources at +0x268

## Step 2b: Search for owner object constructor [UNVERIFIED]

Need to find allocation site (operator new / make_shared) with size >= 0x510 (owner object) or >= 0x2A8 (DragonFrameResources portion) that initializes offsets 0x268..0x2A8.

From rdis callers of 0x67c9c20: 0 callers found (lambda called via indirect mechanism).
Callees of 0x67c9c20: 0xE8FEB10, 0xC267B90, 0xC270330, 0xC270460, 0x4305E0, 0x67CA960, 0x67CAB00.
Callers of these callees that might also construct the owner: 0x66232b0 (BgfxFrameBuilder::endFrame) calls 0xC267B90 and 0xC270460.

The owner object is likely constructed during BgfxFrameBuilder initialization or FrameContext initialization.

**Gap**: FrameContext constructor not yet located. Need to find BgfxFrameBuilder constructor to trace FrameContext allocation.

[UNVERIFIED: BgfxFrameBuilder constructor address unknown - need to find vtable/constructor]
[UNVERIFIED: FrameContext type and constructor unknown]
[UNVERIFIED: Owner object type and constructor unknown]

## Step 3: Stores in owner object constructor for offsets 0x268..0x2A8 [PENDING - BLOCKED]

Once constructor is found, run `python tools/sigs/stores.py` on its listing to extract stores.

Expected stores (based on DragonFrameResources layout from oc_U-C4a.md):
- Offset 0x290: vector<shared_ptr<Task>> first (begin) - initialized to 0
- Offset 0x298: vector<shared_ptr<Task>> last (push cursor) - initialized to 0
- Offset 0x2A0: vector<shared_ptr<Task>> end (capacity) - initialized to 0
- Offsets 0x268..0x28F: other DragonFrameResources fields (unknown)

## Verification
All quoted instruction lines verified by `python tools/sigs/verify_oc.py docs/progress/oc_U-C4a2.md`: 11 claimed, 11 match, 0 mismatch.

## TOOL REQUESTS
- Need better way to find constructors of objects referenced through indirect pointers (FrameContext, owner object)
- `rdis class` or `rdis vt` on BgfxFrameBuilder to find vtable and constructor
- Search for `make_shared`/`operator new` calls with size >= 0x510 in BgfxFrameBuilder initialization code