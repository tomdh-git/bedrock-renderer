## NEXT
DONE

# UNIT U-EL3f — DragonFrameResources object size + constructor (L3f pending part)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred from instruction evidence, [?] = unknown / not located. Nothing invented; no offsets, sizes, or meanings beyond what instructions show.

## Basis — already closed (not re-derived in this unit)

- DragonFrameResources task vector at +0x290/+0x298/+0x2A0 = {begin, end/cursor, capacity}, 16-byte {Task*, shared_ptr control block*} elements, stride 0x10 — proven [V] in endFrame 0xe9002e0 (oc_U-EC4a.md, check OK; BGFX_MAP 6cx/1081). Every +0x290/+0x298/+0x2A0 access in the exe is inside 0xe9002e0; no other function reads/writes them [V per prior full-exe field scans, oc_U-C4a2 / bgfx-d3d12-dragon.md].
- DragonFrameResources is embedded at owner object +0x268: the sole endFrame caller passes `rdx = [rsi+0x10] + 0x268` (DragonFrameResources&) at 0x67ca3cd [V]. Hence sizeof(DragonFrameResources) >= 0x2A8 (vector occupies +0x290..+0x2A8) and sizeof(owner) >= 0x268 + 0x2A8 = 0x510 [I].
- +0x08/+0x0C/+0x10/+0x18 seen via rdi are taskList/shared_ptr fields (rdi = taskList until 0xe900483), NOT DragonFrameResources fields [EC4a].

## Pending part of this unit: object size + constructor

| name | offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| DragonFrameResources+0x290 | +0x290 | 8 | `0xe900827  sub rsi,[rdi+0x290]`; `0xe900913  mov r13,[rdi+0x290]`; `0xe9009ff  mov r13,[rdi+0x290]`; `0xe900a71  mov r13,[rdi+0x290]`; `0xe900aba  mov [rdi+0x290],r14`; `0xe900b2d  mov [rdi+0x290],r14` | vector begin — base of the 16-byte element storage; element index = (ptr - begin) >> 4 (sar rcx,4 at 0xe900831); restored at realloc (0xe900b2d) | [V] |
| DragonFrameResources+0x298 | +0x298 | 8 | `0xe9004aa  mov r15,[rdi+0x298]`; `0xe9004c5  add qword ptr [rdi+0x298],0x10`; `0xe90091a  mov rax,[rdi+0x298]`; `0xe90096f  mov rax,[rdi+0x298]`; `0xe900a16  mov rsi,[rdi+0x298]`; `0xe900acc  mov [rdi+0x298],rax`; `0xe900b3f  mov [rdi+0x298],rax` | vector end / write cursor; advanced by 0x10 (16-byte stride) per pushed task (0xe9004c5); push stores {object*,ctrl} at [end]/[end+8] (0xe9004be/0xe9004c1) | [V] |
| DragonFrameResources+0x2A0 | +0x2A0 | 8 | `0xe9004b1  cmp r15,[rdi+0x2A0]`; `0xe900a7f  mov rdx,[rdi+0x2A0]`; `0xe900add  mov [rdi+0x2A0],rax`; `0xe900b50  mov [rdi+0x2A0],rax` | vector capacity end; `cmp r15,[rdi+0x2A0]` tests end == capacity (triggers realloc) | [V] |
| DragonFrameResources sizeof | - | - | - | highest confirmed field is +0x2A0 (qword) ⇒ sizeof(DragonFrameResources) >= 0x2A8 [I]; exact total size is shown by no instruction — endFrame borrows DFR by reference (args+0x20 in 0xe9002e0) and never allocates or sizes the object | [I] bound; exact size [?] |
| endFrame call site | 0x67ca3cd | - | `67ca3bb  mov edx,0x268`; `67ca3c0  add rdx,[rsi+0x10]` | rdx = [rsi+0x10] + 0x268 = DragonFrameResources& passed by reference; the call site constructs nothing — no DFR allocation/ctor/memset here | [V] |
| DragonFrameResources constructor | - | - | - | not located: 0xe9002e0 receives DFR by reference and contains no DFR allocation, operator new, memset, or ctor call (its allocations are 0x88/0x98-byte task-entry objects); prior ctor scans (oc_U-C4a2; bgfx-d3d12-dragon.md C4a/L3f "no function that constructs or destroys DragonFrameResources was found") negative | [?] |

## CLOSES?

NO — single blocking fact: the DragonFrameResources constructor and exact object size are not located in the executable. endFrame (0xe9002e0) and its only caller (0x67ca3cd) only borrow DFR by reference (rdx = [rsi+0x10] + 0x268 at 0x67ca3c0); no instruction zero-inits DFR+0x290/+0x298/+0x2A0, allocates the DFR object, or calls a DFR constructor; exact sizeof(DragonFrameResources) is bounded only (>= 0x2A8 from the highest confirmed field +0x2A0), not proven. Previous constructor searches in oc_U-C4a2 and bgfx-d3d12-dragon.md were also negative, so there is no [V] row to close the pending "object size + ctor" part.

## TOOL REQUESTS

- None.
