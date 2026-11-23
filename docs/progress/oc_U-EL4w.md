## NEXT
DONE

# Unit U-EL4w: EditorHighlightConfiguration desc+0x08 writer — vtable slot-0 / constructor angle

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown. Image base 0x140000000.
Producer 0x4c88900 = vtable slot 0 of vtable 0xf20aa50 (`rdis vt 0xf20aa50`: slot 0=sub_4c88900 size 0xf81, slot 2=sub_4c9d010 size 0x4000, slot 6=sub_4c8d340; `rdis ptr 0x4c88900` -> sole .rdata pointer at 0xf20aa50) [V].
Goal (orchestrator 2026-11-21): find who stores vtable 0xf20aa50 into an object (constructor) and who calls slot 0 on it — that creator/caller sets desc+0x08 before the producer runs.

Carried over, not redone:
- After 0x666b3a6 r15 is the pass-vector cursor; the only description read is eh+0x08 at `0x666b3be mov rax,[rbx+8]` (refcounted) [V].
- Producer stores into rbx (config object, vtable-0xf20aa50 input) only at +0x38/+0x40/+0x48/+0x60/+0x70; complete [rbx+off] enumeration [V]; NO store to rbx+0x08; clone 0x4c8a5b0 writes no description memory [V].

## Answer table — EditorHighlightConfiguration description-base fields

| Offset | Size | Site | Verbatim `0xRVA  instr` proof line(s) | Meaning | Tag |
|--------|------|------|---------------------------------------|---------|-----|
| eh+0x08 (config object rbx+0x08) | 8 | R `0x666b3be` | `0x666b3be  mov rax,[rbx+8]` | visitor (Effect case 8) reads desc+0x08 = refcounted shared_ptr control-block pointer; null-checked `0x666b3c2 test rax,rax`; addref `0x666b3cb lock inc dword ptr [rax+8]`; verbatim-copied into pass entry `0x666b590 mov [r15+8],rax` [V]. NO producer or pre-producer store to rbx+0x08 (complete rbx store enumeration [V]: only +0x38 byte, +0x40 qword, +0x48 qword-inc, +0x60 xmmword, +0x70 xmmword). | [V read / ? write] |
| local insert desc+0x08 (rbp+0x568+0x08) | 8 | W `0x4dfb60f` | `0x4dfb60f  mov [r8+8],rax` | sub_4dfb570 (called by producer at `0x4c893cf lea rcx,[rbp+0x568]` / `0x4c893d6 mov rdx,r12` / `0x4c893d9 call 0x4DFB570`; rcx=rbp+0x568 dst=r8) stores transient insert-description +0x08 = rax = [[rbx+0x60]+0x18]+8, highlight-texture shared_ptr control block; built DURING the producer from rbx+0x60's texture object — NOT the config object before the producer | [V] |
| local insert desc+0x00 (rbp+0x568+0x00) | 8 | W `0x4dfb608` | `0x4dfb608  mov [r8],rcx` | sub_4dfb570 stores insert-description +0x00 = [rsi] = [[rbx+0x60]+0x18]+0, texture resource pointer | [V] |
| rbx+0x38 | 1 | W `0x4c8898e` | `0x4c8898e  mov byte ptr [rbx+0x38],1` | producer init flag byte | [V] |
| rbx+0x40 | 8 | W `0x4c89163` | `0x4c89163  mov [rbx+0x40],rax` | producer qword store into description base | [V] |
| rbx+0x48 | 8 | W `0x4c88d0b` | `0x4c88d0b  inc qword ptr [rbx+0x48]` | producer qword increment into description base | [V] |
| rbx+0x60 | 16 | W `0x4c88a7b` | `0x4c88a7b  movups [rbx+0x60],xmm0` | producer xmmword store (texture object from r8's virtual slot-0x338 call `0x4c889b7 call qword ptr [0xF99FFA0]`) | [V] |
| rbx+0x70 | 16 | W `0x4c88ac3` | `0x4c88ac3  movups [rbx+0x70],xmm0` | producer xmmword store into description base | [V] |
| vtable 0xf20aa50 store (constructor) | - | W: none statically | - | vptr 0x14F20AA50 never materialized statically: `rdis xr 0xf20aa50`=0 [V], `rdis imm 0xf20aa50`=0 [V], `rdis imm 0x14f20aa50`=0 [V], `rdis imm 0xf20aa48`=0 [V], `rdis class 0xf20aa50`=error [V], RTTI stripped [V], no ctor for this class in functions.tsv [V]. Constructor / slot-0 caller not statically locatable. | [V search / ? writer] |

## Prior angles that failed (not redone)

`rdis xr/callers 0x4c88900` -> 0 (indirect virtual slot-0 call only) [V]; `rdis xr/imm/lea/data-scan` for vtable 0xf20aa50 and VA/RTTI-adjacent forms -> 0 [V]; RTTI stripped [V]; thousands of `call qword ptr [0xF99FFA0]` slot-0 dispatcher sites unfilterable to this vtable [V]; sibling/nearby factories construct other vptrs (sub_4c88570/sub_4c886d0 vptr 0xF20A9D0, sub_4c88808 vptr 0xF20B420, sub_1c8b100 family, sub_4c8d407 vptr 0xF0ED760) [V]; functions.tsv has no ctor for this class [V]; no live instance seed (range-scan forbidden) [V]. `rdis xr 0xf20b420` validates xr catches lea refs (`4c8880c sub_4c886d0+0x13c lea rax,[0xF20B420]`) but no lea targets 0xf20aa50 [V]. rdis imm validated on 0xf20b420 -> 0 (lea encodes target as RIP-relative disp, not a literal imm) [V].

## CLOSES?

NO — single blocking fact (missing REVERSING): the EditorHighlightConfiguration constructor that stores vtable 0xf20aa50 into the config object and thereby sets desc+0x08 (rbx+0x08) before the producer runs is not statically locatable. The vptr 0x14F20AA50 is never materialized as an immediate or lea target (`rdis xr`/`rdis imm` all 0 [V]), RTTI is stripped [V], no ctor for this class exists [V], and the slot-0 virtual caller is not filterable among thousands of `call qword ptr [0xF99FFA0]` dispatcher sites [V]. The only [V] store to a description +0x08 is `0x4dfb60f mov [r8+8],rax` into the producer's transient local insert description (sub_4dfb570, called at `0x4c893d9 call 0x4DFB570`), built during the producer from rbx+0x60's texture object — not the config object before the producer. The single unknown is the constructor/slot-0 caller RVA.

## TOOL REQUESTS

None — all evidence from static rdis listings verified with verify_oc; no live capture can identify the code writer (a capture shows values, not the writer), and range-scanning memory is forbidden by the brief.
