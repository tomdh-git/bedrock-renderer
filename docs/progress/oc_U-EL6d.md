## NEXT
DONE

# Unit U-EL6d — 0xBC3.... lambdas (pending part of F2b / L6d / 6dd)

## Source context

Pending item (the only part still open for checklist line L6d/F2b): **"the 0xBC3.... lambdas pending"**.
Already proven elsewhere [V]: task body 0x568CD90 per-view setup (view rect V+0x00/+0x04, 4 mat4 at V+0x10/+0x50/+0x90/+0xD0, sortMode V+0x110, byte V+0x122); all 13 std::function _Copy slots share _Do_call 0x568CD70 (thunk `jmp 0x568CD90`), lambdas differ only by captured state.

This unit decodes the 12 std::function `_Copy` slots that live in the 0xBC3.... region (one lambda per Scene pass + HUD task). Each `_Copy` is the copy constructor of a distinct MSVC `std::_Func_impl` lambda type; all share `_Do_call = 0x568CD70 -> jmp 0x568CD90` (common thunk, verified in docs/listings/L_568cd70.txt). The 13th lambda (_Copy at 0x56AE9C0, vtable 0xF25BF90) is NOT in the 0xBC3.... region and is out of scope for this unit.

## Method

- `rdis dis 0xBC36B10`, `0xBC36B60`, `0xBC36C70`, `0xBC36CC0`, `0xBC36D10`, `0xBC36D60`, `0xBC36E50`, `0xBC36EF0`, `0xBC36F40`, `0xBC370D0`, `0xBC37170`, `0xBC37300` (12 _Copy slots in 0xBC3.... region).
- Each _Copy verified verbatim via rdis disassembly output.

## Result — 0xBC3.... lambda _Copy slots [V]

Every _Copy follows the identical 0xE-byte pattern:
`mov rax,rdx` (copy source this ptr) / `lea rcx,[vtable]` (load lambda vtable) / `mov [rdx],rcx` (store vtable into std::function object) / `ret`.

| Name | RVA | Size | Read/Store addr | Verbatim `0xRVA  instr` | Meaning | Tag |
|------|-----|------|-----------------|-------------------------|---------|-----|
| lambda_copy_vtbl_0xF43FE10 | 0xBC36B10 | 14 | [rdx] | `0xBC36B10  mov rax,rdx` | std::function _Copy: store vtable 0xF43FE10 at [rdx] | [V] |
| lambda_copy_vtbl_0xF43FE70 | 0xBC36B60 | 14 | [rdx] | `0xBC36B60  mov rax,rdx` | std::function _Copy: store vtable 0xF43FE70 at [rdx] | [V] |
| lambda_copy_vtbl_0xF43FF00 | 0xBC36C70 | 14 | [rdx] | `0xBC36C70  mov rax,rdx` | std::function _Copy: store vtable 0xF43FF00 at [rdx] | [V] |
| lambda_copy_vtbl_0xF43FF60 | 0xBC36CC0 | 14 | [rdx] | `0xBC36CC0  mov rax,rdx` | std::function _Copy: store vtable 0xF43FF60 at [rdx] | [V] |
| lambda_copy_vtbl_0xF43FFC0 | 0xBC36D10 | 14 | [rdx] | `0xBC36D10  mov rax,rdx` | std::function _Copy: store vtable 0xF43FFC0 at [rdx] | [V] |
| lambda_copy_vtbl_0xF440020 | 0xBC36D60 | 14 | [rdx] | `0xBC36D60  mov rax,rdx` | std::function _Copy: store vtable 0xF440020 at [rdx] | [V] |
| lambda_copy_vtbl_0xF440140 | 0xBC36E50 | 14 | [rdx] | `0xBC36E50  mov rax,rdx` | std::function _Copy: store vtable 0xF440140 at [rdx] | [V] |
| lambda_copy_vtbl_0xF440200 | 0xBC36EF0 | 14 | [rdx] | `0xBC36EF0  mov rax,rdx` | std::function _Copy: store vtable 0xF440200 at [rdx] | [V] |
| lambda_copy_vtbl_0xF440260 | 0xBC36F40 | 14 | [rdx] | `0xBC36F40  mov rax,rdx` | std::function _Copy: store vtable 0xF440260 at [rdx] | [V] |
| lambda_copy_vtbl_0xF440440 | 0xBC370D0 | 14 | [rdx] | `0xBC370D0  mov rax,rdx` | std::function _Copy: store vtable 0xF440440 at [rdx] | [V] |
| lambda_copy_vtbl_0xF440500 | 0xBC37170 | 14 | [rdx] | `0xBC37170  mov rax,rdx` | std::function _Copy: store vtable 0xF440500 at [rdx] | [V] |
| lambda_copy_vtbl_0xF4406E0 | 0xBC37300 | 14 | [rdx] | `0xBC37300  mov rax,rdx` | std::function _Copy: store vtable 0xF4406E0 at [rdx] (HUD task lambda) | [V] |

Full verbatim instruction listings (all confirmed via rdis):

- 0xBC36B10 `mov rax,rdx` / 0xBC36B13 `lea rcx,[0xF43FE10]` / 0xBC36B1A `mov [rdx],rcx` / 0xBC36B1D `ret` (size 0xE)
- 0xBC36B60 `mov rax,rdx` / 0xBC36B63 `lea rcx,[0xF43FE70]` / 0xBC36B6A `mov [rdx],rcx` / 0xBC36B6D `ret` (size 0xE)
- 0xBC36C70 `mov rax,rdx` / 0xBC36C73 `lea rcx,[0xF43FF00]` / 0xBC36C7A `mov [rdx],rcx` / 0xBC36C7D `ret` (size 0xE)
- 0xBC36CC0 `mov rax,rdx` / 0xBC36CC3 `lea rcx,[0xF43FF60]` / 0xBC36CCA `mov [rdx],rcx` / 0xBC36CCD `ret` (size 0xE)
- 0xBC36D10 `mov rax,rdx` / 0xBC36D13 `lea rcx,[0xF43FFC0]` / 0xBC36D1A `mov [rdx],rcx` / 0xBC36D1D `ret` (size 0xE)
- 0xBC36D60 `mov rax,rdx` / 0xBC36D63 `lea rcx,[0xF440020]` / 0xBC36D6A `mov [rdx],rcx` / 0xBC36D6D `ret` (size 0xE)
- 0xBC36E50 `mov rax,rdx` / 0xBC36E53 `lea rcx,[0xF440140]` / 0xBC36E5A `mov [rdx],rcx` / 0xBC36E5D `ret` (size 0xE)
- 0xBC36EF0 `mov rax,rdx` / 0xBC36EF3 `lea rcx,[0xF440200]` / 0xBC36EFA `mov [rdx],rcx` / 0xBC36EFD `ret` (size 0xE)
- 0xBC36F40 `mov rax,rdx` / 0xBC36F43 `lea rcx,[0xF440260]` / 0xBC36F4A `mov [rdx],rcx` / 0xBC36F4D `ret` (size 0xE)
- 0xBC370D0 `mov rax,rdx` / 0xBC370D3 `lea rcx,[0xF440440]` / 0xBC370DA `mov [rdx],rcx` / 0xBC370DD `ret` (size 0xE)
- 0xBC37170 `mov rax,rdx` / 0xBC37173 `lea rcx,[0xF440500]` / 0xBC3717A `mov [rdx],rcx` / 0xBC3717D `ret` (size 0xE)
- 0xBC37300 `mov rax,rdx` / 0xBC37303 `lea rcx,[0xF4406E0]` / 0xBC3730A `mov [rdx],rcx` / 0xBC3730D `ret` (size 0xE)

All 12 _Copy slots belong to the 12 Scene passes + HUD task lambdas. Their vtables' `_Do_call` (slot 2 at vtable+0x10) all point to 0x568CD70 = `mov rcx,rdx; mov rdx,r8; jmp 0x568CD90` (common thunk, verified). The per-pass differentiation occurs via captures in the lambda objects (std::function at task+0x70), not via distinct _Do_call targets.

## CLOSES?

YES — all 12 0xBC3.... lambda _Copy slots are proven by [V] verbatim rows. The pending part of the F2b/L6d checklist item ("the 0xBC3.... lambdas") is closed.

## TOOL REQUESTS

None — all work done with rdis.exe only.