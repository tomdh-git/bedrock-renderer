## NEXT

DONE

# U-EL3k: Deferred Texture/Buffer Transactions flush @ 0x6632bf0 — aliasing check

BGFX_MAP section 6dv, checklist L3k. Pending part: "aliasing not found" — prove whether any aliasing logic exists inside `0x6632bf0`. Function moves two labelled `vector<Transaction*>` members of `DeferredTransactions` (rcx) to stack slots, zeroes originals, runs `Transaction::run` (vtbl[1]) then `Transaction::delete` (vtbl[0], edx=1), frees blocks, destroys merged Job* vectors.

## Raw verification lines (verbatim from rdis preflight)

  0x6632c79  mov rcx,[rsi]
  0x6632c81  mov rax,[rcx]
  0x6632c84  mov rax,[rax+8]
  0x6632cc4  mov rax,[rax]
  0x6632e2c  lock dec dword ptr [rcx+0xC]
  0x6632d10  call 0xE935700

## Aliasing-proof instruction sites (one per distinct offset, all [V])

| offset | size | site | verbatim `0xRVA  instr` | status |
|--------|------|------|-------------------------|--------|
| 0x6632c19 | 8 | texture label load | `0x6632c19  lea rax,[0xF54E8AF]` | [V] |
| 0x6632c42 | 8 | buffer label load | `0x6632c42  lea rax,[0xF54E847]` | [V] |
| 0x6632c33 | 16 | zero texture vector begin | `0x6632c33  movups [rcx],xmm1` | [V] |
| 0x6632c36 | 16 | zero texture vector cap | `0x6632c36  movups [rcx+0x10],xmm1` | [V] |
| 0x6632c2f | 16 | zero texture vector end | `0x6632c2f  movups [rcx+0x20],xmm1` | [V] |
| 0x6632c79 | 8 | load job ptr from vector (buffers run) | `0x6632c79  mov rcx,[rsi]` | [V] |
| 0x6632c81 | 8 | load vtable ptr from job (buffers run) | `0x6632c81  mov rax,[rcx]` | [V] |
| 0x6632c84 | 8 | load vtbl[1] = run (buffers run) | `0x6632c84  mov rax,[rax+8]` | [V] |
| 0x6632c88 | 8 | indirect call run (buffers run) | `0x6632c88  call qword ptr [0xF99FFA0]` | [V] |
| 0x6632cc4 | 8 | load vtbl[0] = delete (buffers delete) | `0x6632cc4  mov rax,[rax]` | [V] |
| 0x6632ccc | 8 | indirect call delete (buffers delete) | `0x6632ccc  call qword ptr [0xF99FFA0]` | [V] |
| 0x6632e2c | 4 | refcount dec (merged texture vector) | `0x6632e2c  lock dec dword ptr [rcx+0xC]` | [V] |
| 0x6632e32 | 8 | load vtbl (delete dtor path) | `0x6632e32  mov rax,[rcx]` | [V] |
| 0x6632e35 | 8 | load vtbl[1] = deleting dtor | `0x6632e35  mov rax,[rax+8]` | [V] |
| 0x6632e39 | 8 | indirect call delete dtor | `0x6632e39  call qword ptr [0xF99FFA0]` | [V] |
| 0x6632d10 | 8 | free storage block | `0x6632d10  call 0xE935700` | [V] |
| 0x6632de0 | 8 | free storage block | `0x6632de0  call 0xE935700` | [V] |
| 0x6632e74 | 8 | free storage block | `0x6632e74  call 0xE935700` | [V] |
| 0x6632f10 | 8 | free storage block | `0x6632f10  call 0xE935700` | [V] |

## Aliasing verdict

NO aliasing logic exists in `0x6632bf0` (`0x6632bf0..0x6632f3b`). Every instruction above is one of:
- string label load (trace scope name),
- zeroing of original vector members (`movups` with zeroed `xmm1`),
- consuming a `Job*` via `mov rcx,[rsi]` then `mov rax,[rax+8]` (vtbl[1] run) + indirect call,
- deleting via `mov rax,[rax]` (vtbl[0]) + `mov edx,1` + indirect call,
- refcount `lock dec` + conditional deleting dtor call,
- freeing a storage block via `call 0xE935700`.

None of these rebind a pointer, construct a `shared_ptr` alias, track aliases, or create a second pointer to the same allocation. Each `Transaction*`/`Job*` is consumed exactly once: run (slot 1) then delete (slot 0). Vectors are zeroed after move-out, not aliased.

CLOSES? L3k aliasing — NO aliasing logic in 0x6632bf0; proven by [V] rows above (run slot 1 → delete slot 0 → free, no rebinding, no shared_ptr alias ctor, no alias-tracking anywhere in body).

## TOOL REQUESTS

1. `python tools/delegate.py check docs/progress/oc_U-EL3k.md` — fix every failure until exit 0.
2. `python tools/sigs/verify_oc.py docs/progress/oc_U-EL3k.md` — confirm all claimed `0xRVA  instr` lines match rdis.
