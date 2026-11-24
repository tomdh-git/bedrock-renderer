# Lifted function: sub_bc7c4e0 (0xbc7c4e0)

- RVA: 0xbc7c4e0, size 0x95 bytes (range proven by .pdata: [0xbc7c4e0, 0xbc7c575)) [V]
- Version: Minecraft Bedrock 1.26.62.01 (image base 0x140000000) [V]
- Region: bgfx; name in the unit data file: "VV frame-graph builder" [V]
- Source: src/client/features/render/native/bgfx/sub_bc7c4e0.cpp (first line `// LIFT 0xbc7c4e0 size 0x95 1.26.62.01 sub_bc7c4e0`)
- Header: src/client/features/render/native/bgfx/sub_bc7c4e0.h (layout constants + static_asserts)
- Registry: LIFT_FN(sub_bc7c4e0, "native::sub_bc7c4e0", 0xbc7c4e0, sub_bc7c4e0, sub_bc7c4e0Footprint) in the .cpp

## Signature (from the disassembly [V])

`extern "C" void sub_bc7c4e0(FrameSlot* a0 /*rcx*/, FrameSlot* a1 /*rdx*/);`

The function never stores a meaningful return value: every exit reaches `0xbc7c574  ret` with rax holding path-dependent leftovers. The caller (0xbc7ba60, call site `0xbc7bae1  call 0xBC7C4E0`) discards the result. Declared void [I].

## Register / argument map (x64 Microsoft ABI [V])

- rcx = a0: pointer to FrameSlot (+0x00 raw, +0x08 ref, +0x10 flag)
- rdx = a1: pointer to FrameSlot (same layout)
- r8, r9 (a2, a3) at entry: not read by the function
- rdi = src: the slot whose flag != 0 (selected with cmovne)
- rcx (reused) = dst: the slot whose flag == 0
- rsi = src->ref (the RefCounted* control block) during the release path
- rax = scratch (vtable loads, refcount operand)
- xmm0 = zero register for the 16-byte dst clear

## Layout used [V]

FrameSlot: raw +0x00 (pointer), ref +0x08 (pointer to RefCounted), flag +0x10 (uint8). Consecutive slots in the caller's array are 0x18 apart (caller passes rsi+0x28 and rsi+0x40) → sizeof(FrameSlot) == 0x18 [V]. RefCounted (reused from the sub_bc55ea0 dossier [V]): vptr +0x00, strong std::uint32_t +0x08 (lock inc/dec), weak std::uint32_t +0x0C (lock dec); vtable[0] = destroy, vtable[1] = dealloc.

## Disassembly phases

### 0xbc7c4e0..0xbc7c4f9 — prologue and flag comparison
`0xbc7c4e6  movzx eax,byte ptr [rcx+0x10]` loads a0->flag into eax; `0xbc7c4ea  cmp al,[rdx+0x10]` compares with a1->flag.
- Equal: `0xbc7c4ef  test al,al` / `0xbc7c4f1  je short 0xBC7C56E` — flag == 0 → epilogue (no-op return).
- Equal and nonzero: `0xbc7c4f3  add rsp,0x28` / `0xbc7c4f7  pop rdi` / `0xbc7c4f8  pop rsi` / `0xbc7c4f9  jmp 0xBC55EA0` — tail call into sub_bc55ea0(a0, a1); its return value becomes this function's return.
- Differ: fall through to 0xbc7c4fe.

### 0xbc7c4fe..0xbc7c52c — select source/destination and move the reference
`0xbc7c4fe  test al,al` (al == a0->flag) / `0xbc7c500  mov rdi,rdx` / `0xbc7c503  cmovne rdi,rcx` / `0xbc7c507  cmovne rcx,rdx`:
src (rdi) = f0 != 0 ? a0 : a1; dst (rcx) = f0 != 0 ? a1 : a0.
`0xbc7c50b  xorps xmm0,xmm0` / `0xbc7c50e  movups [rcx],xmm0` — zero dst's raw+ref (16 bytes).
`0xbc7c511  mov rax,[rdi+8]` / `0xbc7c515  test rax,rax` / `0xbc7c518  je short 0xBC7C51E` / `0xbc7c51a  lock inc dword ptr [rax+8]` — addref src->ref when non-null.
`0xbc7c51e  mov rax,[rdi]` / `0xbc7c521  mov [rcx],rax` / `0xbc7c524  mov rax,[rdi+8]` / `0xbc7c528  mov [rcx+8],rax` — copy src->raw, src->ref into dst.
`0xbc7c52c  mov byte ptr [rcx+0x10],1` — dst->flag = 1 (dst now owns the reference).

### 0xbc7c530..0xbc7c56a — conditional release of the source's old reference
`0xbc7c530  cmp byte ptr [rdi+0x10],1` / `0xbc7c534  jne short 0xBC7C56E` — only when src->flag == 1 (sole owner).
`0xbc7c536  mov rsi,[rdi+8]` / `0xbc7c53a  test rsi,rsi` / `0xbc7c53d  je short 0xBC7C56A` — rsi = src->ref; null ref → clear flag, done.
`0xbc7c53f  lock dec dword ptr [rsi+8]` / `0xbc7c543  jne short 0xBC7C56A` — strong--; nonzero → clear flag, done.
Strong reached 0: `0xbc7c545  mov rax,[rsi]` / `0xbc7c548  mov rax,[rax]` (vtable[0]) / `0xbc7c54b  mov rcx,rsi` / `0xbc7c54e  call qword ptr [0xF99FFA0]` — virtual destroy(rsi) through the [0xF99FFA0] gadget (cell holds sub_eea6040 = `jmp rax`).
`0xbc7c554  lock dec dword ptr [rsi+0xC]` / `0xbc7c558  jne short 0xBC7C56A` — weak--; nonzero → clear flag, done.
Weak reached 0: `0xbc7c55a  mov rax,[rsi]` / `0xbc7c55d  mov rax,[rax+8]` (vtable[1]) / `0xbc7c561  mov rcx,rsi` / `0xbc7c564  call qword ptr [0xF99FFA0]` — virtual dealloc(rsi) through the same gadget.
`0xbc7c56a  mov byte ptr [rdi+0x10],0` — src->flag = 0 (source no longer owns anything).

### 0xbc7c56e..0xbc7c574 — epilogue
`0xbc7c56e  add rsp,0x28` / `0xbc7c572  pop rdi` / `0xbc7c573  pop rsi` / `0xbc7c574  ret`.

## Reversed source (complete)

// x64 Microsoft ABI: rcx = a0 (FrameSlot*), rdx = a1 (FrameSlot*). Returns void.
// 0xbc7c4e0  push rsi
// 0xbc7c4e1  push rdi
// 0xbc7c4e2  sub rsp,0x28
std::uint8_t f0 = a0->flag;                                // 0xbc7c4e6  movzx eax,byte ptr [rcx+0x10]
if (f0 == a1->flag) {                                      // 0xbc7c4ea  cmp al,[rdx+0x10] ; 0xbc7c4ed  jne short 0xBC7C4FE
    if (f0 == 0) {                                         // 0xbc7c4ef  test al,al ; 0xbc7c4f1  je short 0xBC7C56E
        return;                                            // 0xbc7c56e  add rsp,0x28 ; 0xbc7c572  pop rdi ; 0xbc7c573  pop rsi ; 0xbc7c574  ret
    }
    // 0xbc7c4f3  add rsp,0x28
    // 0xbc7c4f7  pop rdi
    // 0xbc7c4f8  pop rsi
    // 0xbc7c4f9  jmp 0xBC55EA0
    return native::sub_bc55ea0(                            // 0xbc7c4f9  jmp 0xBC55EA0
        reinterpret_cast<Slot*>(a0),
        reinterpret_cast<Slot*>(a1));
}
// 0xbc7c4fe  test al,al
// 0xbc7c500  mov rdi,rdx
// 0xbc7c503  cmovne rdi,rcx
// 0xbc7c507  cmovne rcx,rdx
FrameSlot* src = f0 != 0 ? a0 : a1;
FrameSlot* dst = f0 != 0 ? a1 : a0;
// 0xbc7c50b  xorps xmm0,xmm0
// 0xbc7c50e  movups [rcx],xmm0   (16-byte zero store of dst->raw + dst->ref)
dst->raw = nullptr;
dst->ref = nullptr;
// 0xbc7c511  mov rax,[rdi+8]
// 0xbc7c515  test rax,rax
if (src->ref != nullptr) {                                 // 0xbc7c518  je short 0xBC7C51E
    // 0xbc7c51a  lock inc dword ptr [rax+8]
    src->ref->strong.fetch_add(1u, std::memory_order_seq_cst);
}
// 0xbc7c51e  mov rax,[rdi]
// 0xbc7c521  mov [rcx],rax
dst->raw = src->raw;
// 0xbc7c524  mov rax,[rdi+8]
// 0xbc7c528  mov [rcx+8],rax
dst->ref = src->ref;
// 0xbc7c52c  mov byte ptr [rcx+0x10],1
dst->flag = 1;
// 0xbc7c530  cmp byte ptr [rdi+0x10],1
if (src->flag == 1) {                                      // 0xbc7c534  jne short 0xBC7C56E
    // 0xbc7c536  mov rsi,[rdi+8]
    RefCounted* rsi = src->ref;
    // 0xbc7c53a  test rsi,rsi
    if (rsi != nullptr) {                                  // 0xbc7c53d  je short 0xBC7C56A
        // 0xbc7c53f  lock dec dword ptr [rsi+8]
        if (rsi->strong.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
            // 0xbc7c543  jne short 0xBC7C56A
            // 0xbc7c545  mov rax,[rsi]
            // 0xbc7c548  mov rax,[rax]   (vtable[0])
            VoidFn destroy = vtableDestroy(rsi);
            // 0xbc7c54b  mov rcx,rsi
            // 0xbc7c54e  call qword ptr [0xF99FFA0]
            destroy(rsi);
            // 0xbc7c554  lock dec dword ptr [rsi+0xC]
            if (rsi->weak.fetch_sub(1u, std::memory_order_seq_cst) == 1u) {
                // 0xbc7c558  jne short 0xBC7C56A
                // 0xbc7c55a  mov rax,[rsi]
                // 0xbc7c55d  mov rax,[rax+8]   (vtable[1])
                VoidFn dealloc = vtableDealloc(rsi);
                // 0xbc7c561  mov rcx,rsi
                // 0xbc7c564  call qword ptr [0xF99FFA0]
                dealloc(rsi);
            }
        }
    }
    // 0xbc7c56a  mov byte ptr [rdi+0x10],0
    src->flag = 0;
}
// 0xbc7c56e  add rsp,0x28
// 0xbc7c572  pop rdi
// 0xbc7c573  pop rsi
// 0xbc7c574  ret
return;

where vtableDestroy loads r->vptr then vtable[0], vtableDealloc loads r->vptr then vtable[1]; each
`0xbc7c54e  call qword ptr [0xF99FFA0]` / `0xbc7c564  call qword ptr [0xF99FFA0]` is the jmp-rax gadget
(cell holds sub_eea6040) that turns the loaded rax into the actual indirect call target.

## Struct fields touched

| object | offset | size | direction | meaning | tag |
| FrameSlot | +0x00 | 8 | R/W | raw pointer, copied between slots | [V] |
| FrameSlot | +0x08 | 8 | R/W | RefCounted* ref, addrefed/released | [V] |
| FrameSlot | +0x10 | 1 | R/W | flag: 0 empty, 1 sole owner, other shared | [V] [role inferred] |
| RefCounted (src->ref) | +0x00 | 8 | R | vptr, read to fetch vtable[0]/vtable[1] | [V] |
| RefCounted | +0x08 | 4 | R/W | strong count: lock inc on acquire, lock dec on release | [V] |
| RefCounted | +0x0C | 4 | R/W | weak count: lock dec after destroy | [V] |
| data slot | 0xF99FFA0 | 8 | R | indirect-call cell; holds sub_eea6040 (`jmp rax`, loader-resolved) | [V] |

## Callees

| address in this fn | target | class | how | tag |
| 0xbc7c4f9 | sub_bc55ea0 (native::sub_bc55ea0) | lift | tail call `0xbc7c4f9  jmp 0xBC55EA0`, args rcx=a0, rdx=a1 forwarded | [V] |
| 0xbc7c54e | sub_eea6040 via data slot 0xF99FFA0 | vendor boundary | net effect: virtual destroy(rsi) = vtable[0](rsi) | [V] |
| 0xbc7c564 | sub_eea6040 via data slot 0xF99FFA0 | vendor boundary | net effect: virtual dealloc(rsi) = vtable[1](rsi) | [V] |

sub_bc55ea0 is classified `lift` in docs/data/native_functions.tsv and is called through its native symbol; sub_eea6040 is classified `vendor` in docs/data/native_boundary.tsv ("thunk via data slot 0xF99FFA0 (loader-resolved)") and is reached exactly as the instruction does: rax = loaded vtable entry, `call qword ptr [0xF99FFA0]`. No call target lies outside the lift set and the boundary table.

## Ownership / threading

The function moves one strong reference between two FrameSlots: the source's strong count is addrefed before the destination is published and released once if the source was the sole owner (strong reaching 0 runs vtable[0] destroy, weak reaching 0 runs vtable[1] dealloc). All atomic ops are locked (full barrier). No locks are held across calls; safe to call concurrently on distinct slots; the two slots may alias the same RefCounted but never each other (flags differ on entry to the move path). Thread-model proof suffices; V2 footprint covers {a0, sizeof(FrameSlot)} and {a1, sizeof(FrameSlot)}; the dynamically touched refcount bytes are reachable through the declared slots. No SEH, no null guards beyond the explicit tests in the original.

## Open questions

none.

## Verification

- liftcheck: pending — run `python tools/sigs/liftcheck.py 0xbc7c4e0`.
- All instruction addresses in [0xbc7c4e0, 0xbc7c575) are covered by cited ranges in the source/dossier; both `call` instructions and the tail `jmp` are quoted verbatim.
