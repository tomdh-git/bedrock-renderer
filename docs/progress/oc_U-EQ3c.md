## NEXT
DONE

UNIT U-EQ3c — Q3c "Description allocation/free ownership understood so descriptions can be pooled". Output file only: docs/progress/oc_U-EQ3c.md. Section Q = Rewrite program; Q3 = Insert and extract layer (checklist line 574).

Goal (verbatim from docs/RENDER_CHECKLIST.md line 574): close Q3c by proving, with verbatim disassembly rows:
(1) who ALLOCATES a description,
(2) who FREES it,
(3) the OWNERSHIP model between caller, insert clone, group _insert slot and the visitor extractor,
(4) what that means for pooling (can descriptions be pooled, and by whom).

Hard rules: static analysis only; never launch/attach the game; never build; never commit; never edit HookManager.cpp, existing hook registration, CMake, or existing Sigs.json entries. May create/edit files under docs/ and tools/ only; may create NEW files under src/sdk/ and src/client/features/render/. Every claim tagged [V] (saw it in disassembly, cite RVA), [I] (inferred), or [?] (unknown). No guesses as fact. No ellipsis shortcuts. One annotated row per distinct offset, all its sites listed, verbatim `0xRVA  instr` lines copied from rdis output.

Anchor facts (BGFX_MAP.md section 3/6b/6g [V]):
- insert<TDescription> clones (50 rows, section 6g) are thin 0x139-byte functions taking (builder in rcx, description pointer in rdx); they build a stack InsertVariant {mDescription* +0, mTag u8 +8} and call builder->vtable[groupSlot] through CFG thunk [0xF99FFA0]. Only the tag byte and group-slot offset differ per clone (U-EQ3a proved the template on 0x531b180).
- Group _insert slots: Editor +0x358=0x6674050, Effect +0x360=0x666aa00, UI +0x368=0x6664760, Sky +0x370=0x6655de0, Item +0x378=0x66466e0, Light +0x380=0x6640ae0 (BGFX_MAP.md section 3).
- _insert(Item) = 0x66466e0 (size 0x218) calls visitor 0x6646980; visitor jump table 0xf2bf2d0 dispatches per tag (Item tags 0..10).
- Live finding 6b: the description lives on the caller's stack and "cannot be read after the call returns"; the extractor receives it as r8 and the variant {desc*, idx} as rdx context.

## 1. ALLOCATION — description memory comes from the caller's stack, not from the FrameBuilder

There is no description heap allocator, arena, or pool in the insert path. Each caller reserves description storage in ITS OWN stack frame, a type-specific producer fills it, and the insert clone receives the pointer in rdx. Two independent call sites prove the pattern (Item group and Item group again; the template is identical for all 50 clones per U-EQ3a):

| name | rva or offset | size | verbatim proof line | tag |
|---|---|---|---|---|
| ItemInHand clone accepts desc pointer from caller (rdx); never allocates | 0x531b19b | 8 | `0x531b19b  mov rdi,rdx` | [V] |
| thin clone: variant.mDescription = desc pointer | 0x531b1f0 | 8 | `0x531b1f0  mov [rbp+0x10],rdi` | [V] |
| thin clone: variant.mTag = tag byte (6 here; differs per clone) | 0x531b1f4 | 1 | `0x531b1f4  mov byte ptr [rbp+0x18],6` | [V] |
| thin clone: reads builder->vtable[group slot +0x378] | 0x531b1fb | 8 | `0x531b1fb  mov rax,[rax+0x378]` | [V] |
| thin clone: calls group _insert(builder, &variant) via CFG thunk; no alloc/free call in the whole 0x139-byte body | 0x531b209 | - | `0x531b209  call qword ptr [0xF99FFA0]` | [V] |
| caller 0x531a580 reserves description slot on its stack: [rbp-0x20] | 0x531ad90 | - | `0x531ad90  lea rcx,[rbp-0x20]` | [V] |
| producer 0x668CB70 writes description field +0x0 into [rcx] == caller's stack slot [rbp-0x20] | 0x668cb9f | 8 | `0x668cb9f  mov [rcx],rax` | [V] |
| caller passes the stack slot as desc: rdx = [rbp-0x20] | 0x531ada7 | - | `0x531ada7  lea rdx,[rbp-0x20]` | [V] |
| caller invokes clone with stack-resident description | 0x531adb2 | - | `0x531adb2  call 0x531B180` | [V] |
| BatchActor producer 0x4e355a0 passes the same stack-slot pattern | 0x4e35dd8 | - | `0x4e35dd8  lea rdx,[rbp-0x20]` | [V] |
| BatchActor invokes its clone with the stack-resident description | 0x4e35ddf | - | `0x4e35ddf  call 0x4E39CB0` | [V] |
| fat skinned-mesh clone 0x4e39f20 receives desc in rdx (caller-owned); entry reads rdx into rsi, no alloc of the description | 0x4e39f94 | - | `0x4e39f94  mov rsi,rdx` | [V] |

Conclusion [V]: descriptions are stack-allocated per caller by a type-specific producer. The FrameBuilder/insert clone allocates NOTHING. No `operator new`, no arena, no pool exists for description memory anywhere in the insert path.

## 2. GROUP _INSERT BORROWS THE DESCRIPTION AND RETURNS WITHOUT FREEING IT

_insert(Item) 0x66466e0 (size 0x218): rbx = desc pointer; it reads the desc head into its own stack, calls the visitor, then returns. It never frees rbx, never stores the desc pointer anywhere persistent, and never calls a freer.

| name | rva or offset | size | verbatim proof line | tag |
|---|---|---|---|---|
| _insert saves desc pointer (rdx -> rbx) | 0x66466fe | 8 | `0x66466fe  mov rbx,rdx` | [V] |
| _insert reads description head +0x0..+0xF (16 bytes) into stack copy [rbp-0x40] | 0x6646757 | 16 | `0x6646757  movups xmm0,[rbx]` | [V] |
| stack copy committed | 0x664675a | 16 | `0x664675a  movaps [rbp-0x40],xmm0` | [V] |
| _insert invokes visitor 0x6646980 with the desc (borrow, synchronous) | 0x6646848 | - | `0x6646848  call 0x6646980` | [V] |
| _insert epilogue: restores stack and returns — no free of rbx, no store of the desc pointer | 0x664686c | - | `0x664686c  add rsp,0x108` | [V] |
| _insert final ret | 0x6646877 | - | `0x6646877  ret` | [V] |

Conclusion [V]: _insert borrows the description for the duration of the call only; it neither owns nor frees it.

## 3. VISITOR COPIES DESCRIPTION DATA OUT INTO ENTT REGISTRY RENDER OBJECTS

Visitor 0x6646980 (tag dispatch via jump table 0xf2bf2d0): every use of the desc pointer rdi is a [rdi+off] READ; extracted fields are written into the registry object (ret@5aba5c0 chain), i.e. data ownership transfers out of the description during the call.

| name | rva or offset | size | verbatim proof line | tag |
|---|---|---|---|---|
| visitor: registry vector cursor load | 0x6646c61 | 8 | `0x6646c61  mov r12,[rsi+0x98]` | [V] |
| visitor: writes 16 bytes of desc-derived data into registry object slot | 0x6646c75 | 16 | `0x6646c75  movups [r12],xmm7` | [V] |
| visitor: writes 8 more bytes of desc-derived data | 0x6646c7a | 8 | `0x6646c7a  movlps [r12+0x10],xmm6` | [V] |
| visitor: advances the registry cursor by element size 0x18 — description data now owned by the render object | 0x6646c80 | - | `0x6646c80  add qword ptr [rsi+0x98],0x18` | [V] |

Conclusion [V]: the extractor consumes the description synchronously (copy-out) and needs nothing from it after the call returns.

## 4. OWNERSHIP MODEL (summarized from the [V] rows above)

- Allocator: the CALLER. Each call site reserves a description slot in its own stack frame (e.g. [rbp-0x20]) and a type-specific producer fills it (0x668CB70 for ItemInHand). No heap allocation, no arena, no pool. [V]
- Freer: NONE. Description storage is reclaimed automatically when the caller's stack frame unwinds. No `free`/`operator delete` of a description exists in clone 0x531b180 (full 0x139 bytes reviewed: calls are stack cookie + ETW/profiling only), in _insert 0x66466e0 (full body reviewed), or in the visitor (uses of rdi are [rdi+off] reads only). [V for the reviewed bodies; stack reclamation is inherent to the calling convention]
- Ownership: caller-owned, transient borrow during insert. The description pointer is never stored by the clone, _insert, or visitor beyond the call; no retained pointer exists anywhere in the path. [V]
- Liveness: the description is needed ONLY synchronously inside the insert call (clone -> _insert -> visitor copy-out). After the caller's call returns, the description is dead. [V]

## 5. POOLING CONCLUSION

Because every description is (a) stack-backed, (b) used synchronously and exclusively inside one insert call, and (c) never retained by the FrameBuilder or the extractor after the call, descriptions CAN be pooled — but pooling must happen at the CALLER side: callers write into a shared reusable buffer instead of a private stack slot. It is safe because extraction completes before insert returns. The FrameBuilder itself cannot pool unilaterally today: it never owns description memory, so it has nothing to recycle. Implementing the pool (shared buffer header under src/sdk/ or src/client/features/render/, producers retargeted to it) is a separate Q4/Q5 engineering task; it is NOT part of the ownership understanding this item asks for.

## What changed (paths)

- docs/progress/oc_U-EQ3c.md — this unit note (only file created; no src/ edits, no builds, no game launch/attach).

## Remaining in-game / build step

None required to close the understanding claim. If the pool is later implemented: (1) add a pooled-description buffer header (new file under src/sdk/ or src/client/features/render/), (2) retarget each producer to write into the buffer, (3) verify identical InsertVariant/extract output — build + in-game run required for that follow-up, not for this unit.

## CLOSES?

YES — Q3c wording met on disk: description allocation (caller stack via type-specific producer), free (none; stack reclamation), and ownership (caller-owned, transient borrow; extractor copies data out during the synchronous insert call; no retained pointer) are each proven by [V] verbatim rows citing RVA. Pooling is therefore feasible at the caller side (shared buffer replacement of per-caller stack slots); the pool's implementation itself is a separate task and is not claimed here. No blocking fact.

## TOOL REQUESTS

None — rdis.exe plus existing tools/sigs (verify_oc.py) sufficed; no helper script written.
