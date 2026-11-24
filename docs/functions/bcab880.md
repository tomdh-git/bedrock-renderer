# Dossier: sub_bcab880 (0xbcab880)

Target: Minecraft Bedrock 1.26.62.01, `Minecraft.Windows.exe`, RVAs relative to image base 0x140000000 [V: slot 0xF99FFA0 stores VA 0x14eea6040 = base + 0xeea6040].

## Mechanical facts

- Function row: docs/data/native_functions.tsv line 1142 — `0xbcab880  0x6a  3  1  bgfx  D0     group insert UI`, callees in set: none (empty), callees outside set: none (empty) [V from the data file].
- Size: 0x6a bytes, [0xbcab880, 0xbcab8ea). 31 instructions, 2 calls, stack frame 0x28, saves rsi/rdi [V: every instruction cited in "Reversed source (complete)" below].
- Prologue: `push rsi; push rdi; sub rsp,0x28` (0xbcab880..0xbcab886) [V].
- Epilogue: `test rdi,rdi; setne al; add rsp,0x28; pop rdi; pop rsi; ret` (0xbcab8dd..0xbcab8ea) [V].
- Calls: 2x `call qword ptr [0xF99FFA0]` at 0xbcab8b5 and 0xbcab8cb, both through data slot 0xF99FFA0 [V].
- Data slot 0xF99FFA0 contains VA 0x14eea6040 = image base 0x140000000 + RVA 0xeea6040 = sub_eea6040, read directly from the PE bytes at file offset for RVA 0xF99FFA0 [V].
- sub_eea6040 is class `vendor` in docs/data/native_boundary.tsv line 506: `0xeea6040	vendor	thunk via data slot 0xF99FFA0 (loader-resolved)	auto-manual` [V]. It is a boundary callee, not in the lift set; calls go through a slot read at call time (no wrapper invented).

## Argument use

- rcx = entry (GroupEntry*): +0x00 read at 0xbcab893 (`mov rax,[rcx]`); +0x08 read at 0xbcab886 and 0xbcab896 (`mov rax,[rcx+8]`, `mov rsi,[rcx+8]`) [V].
- No other entry register read; no stack arguments; rdi is fully defined on every path before use [V].
- Return: AL = (rdi != 0) via `setne al` at 0xbcab8e0, where rdi = *(uintptr_t*)*(UiObject**)(entry->uiObject + 0x18) [V: 0xbcab89a `mov rax,[rax+0x18]`, 0xbcab89e `mov rdi,[rax]`].

## Direct callees

- sub_eea6040 (0xeea6040), class vendor boundary, via data slot 0xF99FFA0, called 2x with this = rc2 (the refCnt object), return value ignored [V; native_boundary.tsv line 506].
- No callees in the lift set; no STL/CRT/alloc calls [V from the empty callee lists in docs/progress/_d_U-EX1.bcab880.txt and the disassembly].

## Indirect calls

- 0xbcab8b5  call qword ptr [0xF99FFA0]   [data_f99ffa0] = sub_eea6040   [V]
- 0xbcab8cb  call qword ptr [0xF99FFA0]   [data_f99ffa0] = sub_eea6040   [V]
Both read the pointer from slot 0xF99FFA0 at call time, exactly as the instruction does, with rcx = refCnt; documented slot RVA 0xF99FFA0 [V].

## Signature

```cpp
// x64 Microsoft ABI: rcx = entry (GroupEntry*), return in AL =
// (*(uintptr_t*)*(UiObject**)(entry->uiObject + 0x18) != 0).
bool sub_bcab880(GroupEntry* entry);   // [V] from prologue/register use
```

## Reversed source (complete)

```cpp
// LIFT 0xbcab880 size 0x6a 1.26.62.01 sub_bcab880 (dossier mirror of
// src/client/features/render/native/bgfx/sub_bcab880.cpp; identical body).
// Range comments cite the instruction range each block implements; call
// lines are quoted verbatim from the disassembly. [V]
// 0xbcab880..0xbcab882: prologue push rsi / push rdi / sub rsp,0x28
// 0xbcab886  mov rax,[rcx+8]                         -> rc1 = entry->refCnt
// 0xbcab88a  test rax,rax
// 0xbcab88d  je short 0xBCAB8D3                      -> skips the addref when refCnt == 0
if (rc1 != nullptr) {
    // 0xbcab88f  lock inc dword ptr [rax+8]          -> rc1->strong++
    rc1->strong.fetch_add(1u, std::memory_order_seq_cst);
}
// 0xbcab893  mov rax,[rcx]                           -> uiObject = entry->uiObject
// 0xbcab896  mov rsi,[rcx+8]                         -> rc2 = entry->refCnt (reloaded)
// 0xbcab89a  mov rax,[rax+0x18]                      -> next = uiObject->next (+0x18)
// 0xbcab89e  mov rdi,[rax]                           -> retSlot0 = *next
// 0xbcab8a1  test rsi,rsi
// 0xbcab8a4  je short 0xBCAB8DD                      -> skips both release stages when rc2 == 0
if (rc2 != nullptr) {
    // 0xbcab8a6  lock dec dword ptr [rsi+8]
    // 0xbcab8aa  jne short 0xBCAB8DD                 -> when strong != 0 skip both stages
    if (rc2->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
        // 0xbcab8ac  mov rax,[rsi]                   (dead read of the vptr)
        // 0xbcab8af  mov rax,[rax]                   (dead read of vtable slot 0)
        // 0xbcab8b2  mov rcx,rsi
        // 0xbcab8b5  call qword ptr [0xF99FFA0]
        // `0xbcab8b5  call qword ptr [0xF99FFA0]`   target sub_eea6040 via data slot 0xF99FFA0 (vendor boundary); this = rc2; return ignored
        callReleaseThunk(rc2);
        // 0xbcab8bb  lock dec dword ptr [rsi+0xC]
        // 0xbcab8bf  jne short 0xBCAB8DD             -> when weak != 0 skip the final call
        if (rc2->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            // 0xbcab8c1  mov rax,[rsi]               (dead read of the vptr)
            // 0xbcab8c4  mov rax,[rax+8]             (dead read of vtable slot 1)
            // 0xbcab8c8  mov rcx,rsi
            // 0xbcab8cb  call qword ptr [0xF99FFA0]
            // `0xbcab8cb  call qword ptr [0xF99FFA0]`   target sub_eea6040 via data slot 0xF99FFA0 (vendor boundary); this = rc2; return ignored
            callReleaseThunk(rc2);
        }
        // 0xbcab8d1  jmp short 0xBCAB8DD             (fall through either way)
    }
    // 0xbcab8aa / 0xbcab8bf  jne short 0xBCAB8DD     landing pad
}
// 0xbcab8d3..0xbcab8da: refCnt == 0 entry path recomputes rdi = *(uintptr_t*)next
// identically; computed above and still live.
// 0xbcab8dd  test rdi,rdi
// 0xbcab8e0  setne al                                 -> return (retSlot0 != 0)
// 0xbcab8e3  add rsp,0x28
// 0xbcab8e7  pop rdi
// 0xbcab8e8  pop rsi
// 0xbcab8e9  ret
return retSlot0 != 0;
```

## Struct fields touched

| address | object+offset | size | R/W | meaning | tag |
|---|---|---|---|---|---|
| 0xbcab886 | GroupEntry+0x00 (via rcx) read of +0x08 | 8 | R | refCnt = entry->refCnt | [V] |
| 0xbcab88f | RefCnt+0x08 | 4 | W | strong++ (lock inc) | [V] |
| 0xbcab893 | GroupEntry+0x00 | 8 | R | uiObject = entry->uiObject | [V] |
| 0xbcab896 | GroupEntry+0x00 (via rcx) read of +0x08 | 8 | R | refCnt = entry->refCnt (reloaded) | [V] |
| 0xbcab89a | uiObject+0x18 | 8 | R | next = *(UiObject**)(uiObject + 0x18) | [V] |
| 0xbcab89e | next+0x00 | 8 | R | retSlot0 = *next (feeds AL return) | [V] |
| 0xbcab8a6 | RefCnt+0x08 | 4 | RW | strong-- (lock dec, result tested) | [V] |
| 0xbcab8ac/0xbcab8af | RefCnt+0x00, then (*vptr)+0x00 | 8/8 | R | dead reads of vptr and vtable slot 0 | [V] |
| 0xbcab8bb | RefCnt+0x0C | 4 | RW | weak-- (lock dec, result tested) | [V] |
| 0xbcab8c1/0xbcab8c4 | RefCnt+0x00, then (*vptr)+0x08 | 8/8 | R | dead reads of vptr and vtable slot 1 | [V] |
| 0xF99FFA0 | data slot | 8 | R | call target = sub_eea6040 VA (loader-resolved) | [V] |

## Ownership / threading

- strong/weak are updated with lock-prefixed inc/dec (full barrier); the refCnt object is shared and owned by the caller's graph (group insert UI), entry itself is caller-owned [I: refcounting discipline inferred from lock inc/dec on +0x08/+0x0C].
- The function takes no mutex and allocates nothing; the two boundary calls to sub_eea6040 may have side effects outside the declared footprint [V: calls through data slot].
- Called by 0x674a3a0 (UI text renderer, "group insert UI" root per docs/data/native_functions.tsv line 645) [I: caller list from the data file].

## Version anchors

- Minecraft Bedrock 1.26.62.01 (`Minecraft.Windows.exe`); RVAs relative to image base 0x140000000 [V].

## Verification

- Source: src/client/features/render/native/bgfx/sub_bcab880.cpp (+ .h) with `// LIFT 0xbcab880 size 0x6a ...` first line, LIFT_FN registry entry, static_asserts for all used offsets.
- `python tools/sigs/liftcheck.py 0xbcab880` result is recorded under `## LIFTCHECK` in docs/progress/oc_U-EX1.bcab880.md; every quoted instruction line is machine-checked by verify_oc (mismatch=0, no-such-instr=0 required).
