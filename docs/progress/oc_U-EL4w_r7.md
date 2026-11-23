## NEXT
DONE

# Unit U-EL4w (RETRY 2026-11-22): EditorHighlightConfiguration desc+0x08 writer — RESOLVED

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown. Image base 0x140000000.

## Resolution

The pending field is the visitor-read eh+0x08 (Effect tag 8, `0x666b3be mov rax,[rbx+8]` [V]). It is NOT written into rbx (the producer's `this`, the vtable-0xf20aa50 EditorHighlightConfiguration input object: producer stores into rbx only at +0x38/+0x40/+0x48/+0x60/+0x70 — complete `[rbx+off]` enumeration [V]). It IS written into the insert description the producer builds at stack rbp+0x568 and hands to the tag-8 insert clone `0x4c89478 call 0x4C8A5B0` (rdx=&rbp+0x568, tag byte `0x4c8a624 mov byte ptr [rbp+0x18],8`) — that insert description is what the Effect visitor case 8 reads via its per-type node (rbx=r15=[r8]).

The store is inside sub_4dfb570, called by the producer at `0x4c893d9 call 0x4DFB570` (rcx=rbp+0x568 dst, rdx=rbp+0x480 src). The src rbp+0x480 is the texture-descriptor pair `[rbx+0x60]/[rbx+0x60+8]` stored there by sub_4c74180 (`0x4c893c9 call 0x4C74180`) after `0x4c88a28 call 0x3946B0` built the "Volume-Highlight-Overlay" name string; rbx+0x60 is filled by the producer itself (`0x4c88a7b movups [rbx+0x60],xmm0`, texture object from r8's virtual slot-0x338 call `0x4c889b7 call qword ptr [0xF99FFA0]`). sub_4dfb570 validates the texture (`0x4dfb58b cmp byte ptr [rsi+0x68],2`), addrefs the control block (`0x4dfb5e7 lock inc dword ptr [rax+8]`) and stores the pair (`0x4dfb608 mov [r8],rcx` / `0x4dfb60f mov [r8+8],rax`). Because desc+0x00/+0x08 are runtime copies from a live texture object, neither is materialized as a static immediate/lea/data qword — which is why `rdis imm`/lea/data-scan for 0xf20aa50 all returned 0 and no separate "EditorHighlightConfiguration constructor" exists: the vtable-0xf20aa50 object (rbx) is a distinct persistent input object whose pre-producer constructor / virtual slot-0 caller is not statically locatable, but rbx+0x08 is not read by the producer or the visitor, so it does not block this item.

## Answer table — EditorHighlightConfiguration description-base fields (eh = description base read by the visitor)

| Offset | Size | Site | Verbatim `0xRVA  instr` proof line(s) | Meaning | Tag |
|--------|------|------|---------------------------------------|---------|-----|
| eh+0x08 | 8 | W `0x4dfb60f`; R `0x666b3be`, `0x666b58c`, `0x666b590` | `0x4dfb60f  mov [r8+8],rax` (W — sub_4dfb570 called by producer at `0x4c893d9 call 0x4DFB570`, rcx=rbp+0x568 dst; desc+0x08 = rax = [rsi+8] = `[[rbx+0x60]+0x18]+8`, highlight-texture resource shared_ptr control block; addrefed by `0x4dfb5e7 lock inc dword ptr [rax+8]`); `0x666b3be  mov rax,[rbx+8]` (R — visitor Effect case 8, rbx=r15=[r8] group desc node; null-check `0x666b3c2 test rax,rax`; addref `0x666b3cb lock inc dword ptr [rax+8]`); `0x666b590  mov [r15+8],rax` (verbatim copy into pass entry after `0x666b58c mov rax,[rbx+8]`) | desc+0x08 of the Effect tag-8 description the visitor reads: stored into the insert description (rbp+0x568 → clone `0x4c89478 call 0x4C8A5B0` → Effect group tag 8 → visitor), NOT into rbx | [V] |
| eh+0x00 | 8 | W `0x4dfb608` | `0x4dfb608  mov [r8],rcx` | desc+0x00 = [rsi+0] = `[[rbx+0x60]+0x18]+0`, texture resource object pointer; runtime-copied like +0x08, hence no static materialization | [V] |
| src rbp+0x480+00 | 16 | W `0x4c7418c`, `0x4c741b3` | `0x4c7418c  movups [rcx],xmm0` (sub_4c74180, called at `0x4c893c9 call 0x4C74180`; zeroes rbp+0x480+0x00..0x0F first; name string built at `0x4c88a28 call 0x3946B0` from "Volume-Highlight-Overlay") ; `0x4c741b3  mov [rsi],rcx` | rbp+0x480+00 = [rbx+0x60] (16-byte texture descriptor qword pair) | [V] |
| src rbp+0x480+08 | 8 | W `0x4c741ba` | `0x4c741ba  mov [rsi+8],rax` ; addref `0x4c741a4 lock inc dword ptr [rax+8]` | rbp+0x480+08 = [rbx+0x60+8] (control block) | [V] |
| rbx+0x60 | 16 | W `0x4c88a7b` | `0x4c88a7b  movups [rbx+0x60],xmm0` | producer stores 16-byte texture descriptor into rbx+0x60 (xmm0 from sub_541f8f0; texture object r14 from r8's virtual slot-0x338 call `0x4c889b7 call qword ptr [0xF99FFA0]`) | [V] |
| rbx (producer this) | - | - | `0x4c88974 mov rbx,rcx` ; `0x4c88977 cmp byte ptr [rcx+0x38],0` | rbx = producer's this = vtable-0xf20aa50 persistent config input object (init flag +0x38); its pre-producer constructor / virtual slot-0 caller not statically locatable (indirect call, vptr never materialized [V]) but rbx+0x08 not read by producer or visitor — not blocking | [V instrs / I conclusion] |

## Prior angles that failed (not redone)

`rdis xr/callers 0x4c88900` → 0 (indirect virtual slot-0 call only); `rdis xr/imm/lea/data-scan` for vtable 0xf20aa50 and VA/RVA/RTTI-adjacent forms → 0 [V]; RTTI stripped [V]; `rdis comp` 0 functions [V]; thousands of `call qword ptr [0xF99FFA0]` slot-0 dispatcher sites unfilterable to this vtable [V]; sibling/nearby factories (sub_4c88570, sub_4c886d0, sub_1c8b100 family, sub_4c8d407) construct other vptrs [V]; functions.tsv has no ctor for this class [V]; no tag-8 live capture data (effect_visitor tags 1-4 only; editor_visitor/editor_extractor empty; er5_clone_4c8a5b0[_b] zero-hit) [V]; no live instance seed (range-scan forbidden) [V]. The break was realizing the producer BUILDS the visitor-read description (rbp+0x568) via sub_4dfb570 instead of writing rbx+0x08.

## CLOSES?

YES — every pending part of the item line is proven by [V] rows: eh+0x08 (the description-base field the visitor reads at `0x666b3be mov rax,[rbx+8]`) is stored at `0x4dfb60f mov [r8+8],rax` inside sub_4dfb570 (called by producer at `0x4c893d9 call 0x4DFB570`), value = `[[rbx+0x60]+0x18]+8` (highlight-texture shared_ptr control block, addrefed at `0x4dfb5e7 lock inc dword ptr [rax+8]`), with eh+0x00 stored at `0x4dfb608 mov [r8],rcx`. Note: the store is inside the producer (insert-description construction), not before it; the vtable-0xf20aa50 object rbx is a separate input whose pre-producer constructor is not statically locatable but is not read by the producer/visitor.

## TOOL REQUESTS

None — all evidence from static rdis listings verified with verify_oc/delegate; no live capture needed for this item.
