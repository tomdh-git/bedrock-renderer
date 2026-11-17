## NEXT
DONE

## Unit U-EI5d: ScreenRenderer internals — 0x6664a00 input builders (continuation of U-I5d/I5e/I5g/I5h)

### Summary of resolution

**Caller of 0x6664a00 (proven [V]).** Sole caller = `sub_6664760` at `0x66648C8  call 0x6664A00` (U-I5d listing, verified). `sub_6664760` has 0 direct xrefs; it is reached only as a vtable slot.

**Vtable owner/constructor (proven [V]).** `rdis vt 0xF2BDEB0 114` = BgfxFrameBuilder vtable, 114 slots; slot 109 (+0x368, RVA `0xF2BE218`) = `sub_6664760` size 0x218 = `_insert(UI)`, matching BGFX_MAP.md §3 row 109. `rdis ptr 0x6664760` -> exactly one data pointer holds it: `0xF2BE218 (.rdata)`; no other vtable references it.

Constructor `sub_660d940` [0x660d940..0x660e2cb), size 0x98b installs the most-derived vptr and zeroes the input fields:
- `0x660d9d0 lea rax,[0xF2BDEB0]` / `0x660d9d7 mov [r12],rax` — W a0+0x0 = vtable 0xF2BDEB0 (slot 109 = sub_6664760)
- `0x660d9ee movdqu [r12+0x20],xmm0` — zero a0+0x20..0x2F (16 B)
- `0x660dad0 movups [r12+0xF0],xmm6` — zero a0+0xF0..0xFF (16 B)
- `0x660daef call 0xC25B1A0` (rcx = a0+0x100) — inits a0+0x100
- `0x660dafe lea rdi,[r12+0x260]` / `0x660db13 call 0xEEC6ED0` — memfill a0+0x260 (0x111 bytes)
- `0x660dc9a lea rax,[rbx+0x380]` — address of a0+0x380 taken

**Factory / builder of a0 (proven [V], caller open).** `sub_980300` [0x980300..0x980385), size 0x85: allocates 0x908 bytes (`0x98033c call qword ptr [0xF99FFA0]`), calls `sub_660d940`, stores result at `[a1+0]` (`0x980362 mov [rsi],rax`). Its address is held as one data pointer at `0xF09BEE8 (.rdata)`; `rdis callers 0x980300` = 0 and `rdis xr 0xF09BEE8` = 0 -> invoked only via function pointer, static caller not located.

**Input to 0x6664a00 (proven [V]).** `sub_6664760` (a0 = BgfxFrameBuilder*, rsi=a0; rbx=a1) builds the 0x6664a00 input stack struct at rbp-0x28..rbp+0x4C from a0 fields, then `0x66648C8 call 0x6664A00` with rcx=[rsi+0x20] (a0+0x20), rdx=stack struct, r8=xmm save area.

### Field map — offsets read by sub_6664760 to build the 0x6664a00 input, and where each is initialized

| offset | size | read/store address | 0xRVA  instr (verbatim proof) | meaning | tag |
|--------|------|--------------------|-------------------------------|---------|-----|
| +0x00 | 8 B | `[rsi]` read; `[r12]` store (ctor) | `0x6664880  mov rax,[rsi]` | a0 vptr read; sub_6664760 follows `0x6664883 mov rax,[rax+0x230]` -> `0x666488D call qword ptr [0xF99FFA0]`; ctor installs vtable 0xF2BDEB0 at `0x660d9d7 mov [r12],rax` (`0x660d9d0 lea rax,[0xF2BDEB0]`) | [V] |
| +0x20 | 8 B | `[rsi+0x20]` read | `0x66648BC  mov rcx,[rsi+0x20]` | a0+0x20 -> rcx = `this` passed to 0x6664a00 at `0x66648C8 call 0x6664A00`; ctor zeroes a0+0x20 at `0x660d9ee movdqu [r12+0x20],xmm0` | [V] |
| +0xF0 | 8 B | `[rsi+0xF0]` read | `0x66647DE  mov rax,[rsi+0xF0]` | a0+0xF0 -> stack [rbp-0x28] (input field 0); ctor zeroes a0+0xF0 at `0x660dad0 movups [r12+0xF0],xmm6` | [V] |
| +0x100 | 8 B | `[rsi+0x100]` lea | `0x6664804  lea rax,[rsi+0x100]` | a0+0x100 -> stack [rbp-0x10] (input field); ctor passes rcx=r14=a0+0x100 to `0x660daef call 0xC25B1A0` (sub_c25b1a0, GraphicsTasks scheduler) | [V] |
| +0x260 | 8 B | `[rsi+0x260]` read | `0x666480F  mov rax,[rsi+0x260]` | a0+0x260 -> stack [rbp-8] (input field); ctor memfills a0+0x260 via `0x660dafe lea rdi,[r12+0x260]` / `0x660db13 call 0xEEC6ED0` (0x111 bytes) | [V] |
| +0x268 | 16 B | `[rsi+0x268]` read | `0x666485D  movups xmm0,[rsi+0x268]` | a0+0x268 (16 B) -> stack [rbp+0x30] (input field) | [V] |
| +0x380 | 8 B | `[rsi+0x380]` read | `0x66647F9  mov rax,[rsi+0x380]` | a0+0x380 -> stack [rbp-0x18] (input field); ctor takes `0x660dc9a lea rax,[rbx+0x380]` | [V] |
| +0x28/+0x18 | 8 B | `[rsi+0x28]` then `[rax+0x18]` | `0x666481A  mov rax,[rsi+0x28]` | *(a0+0x28)+0x18 -> xmm0; `0x666482C movdqa xmm1,[0xF2BDDE0]` / `0x6664838 paddq xmm0,[0xF2BDDF0]` -> stack [rbp+0x10] and [rbp+0x0] | [V] |
| +0x36C | 4 B | `[rsi+0x36C]` read | `0x6664877  mov eax,[rsi+0x36C]` | a0+0x36C -> stack [rbp+0x48] (input field) | [V] |
| +0x358/+0x6A1 | 8 B + 1 B | `[rsi+0x358]` then `[rax+0x6A1]` | `0x6664898  mov rax,[rsi+0x358]` | a0+0x358 -> rax; if nonzero `0x66648A4 movzx eax,byte ptr [rax+0x6A1]` -> stack [rbp+0x4C] else 0 (`0x66648AD xor eax,eax`) | [V] |
| +0x370 | 1 B | `[rsi+0x370]` read | `0x66648B2  movzx eax,byte ptr [rsi+0x370]` | a0+0x370 -> stack [rbp+0x4D] (input field byte) | [V] |
| call site | — | — | `0x66648C8  call 0x6664A00` | sub_6664760 -> UI frame fn; rcx=a0+0x20, rdx=stack struct (rbp-0x28), r8=xmm save area (rbp-0x40) | [V] |

### Verbatim instruction proof lines (each verified against rdis disassembly)

0x6664880  mov rax,[rsi]
0x6664883  mov rax,[rax+0x230]
0x666488D  call qword ptr [0xF99FFA0]
0x66648BC  mov rcx,[rsi+0x20]
0x66647DE  mov rax,[rsi+0xF0]
0x6664804  lea rax,[rsi+0x100]
0x666480F  mov rax,[rsi+0x260]
0x666485D  movups xmm0,[rsi+0x268]
0x66647F9  mov rax,[rsi+0x380]
0x666481A  mov rax,[rsi+0x28]
0x666482C  movdqa xmm1,[0xF2BDDE0]
0x6664838  paddq xmm0,[0xF2BDDF0]
0x6664877  mov eax,[rsi+0x36C]
0x6664898  mov rax,[rsi+0x358]
0x66648A4  movzx eax,byte ptr [rax+0x6A1]
0x66648AD  xor eax,eax
0x66648B2  movzx eax,byte ptr [rsi+0x370]
0x66648C8  call 0x6664A00
0x660d9d0  lea rax,[0xF2BDEB0]
0x660d9d7  mov [r12],rax
0x660d9ee  movdqu [r12+0x20],xmm0
0x660dad0  movups [r12+0xF0],xmm6
0x660daef  call 0xC25B1A0
0x660dafe  lea rdi,[r12+0x260]
0x660db13  call 0xEEC6ED0
0x660dc9a  lea rax,[rbx+0x380]

### Still open (one level up — indirect-call boundary, not part of the literal EI5d ask)

- Who invokes `sub_6664760` (vtable slot 109 at `0xF2BE218`): 0 direct xrefs; reached via virtual call `[vptr+0x368]` or an `insert<UI>` clone through CFG thunk `[0xF99FFA0]`; static call site not located.
- Who calls `sub_980300` (factory at `0xF09BEE8` pointer): 0 direct xrefs; invoked via function pointer; static caller not located.
- Live (non-zero) values written into a0+0x20/+0xF0/+0x100/+0x260/+0x268/+0x380 after construction (ctor zeroes +0x20/+0xF0): filler not located.

### CLOSES?

YES — every pending part named in the EI5d item line is [V]-proven: (1) caller of 0x6664a00 = sub_6664760 at `0x66648C8 call 0x6664A00`; (2) vtable owner = BgfxFrameBuilder vtable `0xF2BDEB0`, slot 109 (+0x368) = sub_6664760 `_insert(UI)`; (3) constructor = `sub_660d940` installs vtable at +0x00 and zeroes +0x20/+0xF0; (4) builder of a0 = `sub_980300` (alloc 0x908 -> ctor -> store [a1+0]); (5) input to 0x6664a00 = stack struct built by sub_6664760 from a0 fields +0x20/+0xF0/+0x100/+0x260/+0x268/+0x380/+0x36C/+0x370/+0x358+0x6A1. The upstream trigger (who calls sub_6664760 / sub_980300) is an indirect-call boundary left as open [?], but it is outside the literal "callers of 0x6664a00 and what builds its input" ask.

## TOOL REQUESTS

None — all evidence gathered with rdis (vt/ptr/callers/callees/xr/fn/dis) and verify_oc.py.
