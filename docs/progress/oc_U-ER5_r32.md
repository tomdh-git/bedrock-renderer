## NEXT
DONE

# Unit U-ER5 — R5 EditorHighlight (Effect tag 8): 64-byte block (+0x10..+0x4F), +0x50, pass+0x80 consumer

Goal (checklist R5, docs/RENDER_CHECKLIST.md line 603): close the pending parts — (a) the meanings of the description's 64-byte block (+0x10..+0x4F) and +0x50, (b) the pass that consumes the pass+0x80 queue (begin +0x78, end +0x80, cap +0x88, stride 0x58; end advanced at 0x666b5c0).

## Status inherited from oc_U-ER5_r1.md (RET #1 — not redone)
- Proven [V] earlier and kept: the pass+0x80 queue shape (begin +0x78, end +0x80, cap +0x88, stride 0x58, end advanced by `0x666b5c0  add qword ptr [rsi+0x80],0x58`); visitor 0x666b316 copies the description verbatim as a 0x58-byte element (`0x666b586..0x666b5bc`).
- Previously [?], now [V] this unit: the consumer of pass+0x80 is inside sub_666aca0, tag-8 case at 0x666b316 (re-verified verbatim below).
- Still pending: semantic meanings of +0x10..+0x4F and +0x50 (byte values proven [V]; no instruction or string names them).

## What I tried this unit (new angles; nothing repeated from r1 without re-verification)
1. `rdis dis 0x666b316 220`: re-verified every visitor instruction quoted below verbatim. Tag 8 case = the queue writer inside sub_666aca0: pass object via `0x666b323  call 0x5ABA5C0` (rcx = [r12+0x10]+0x9D0), end = `0x666b3a6  mov r15,[rsi+0x80]`, cap = `0x666b3ad  cmp r15,[rsi+0x88]`, element stored at [r15] (`0x666b586..0x666b5bc`), end advanced `0x666b5c0  add qword ptr [rsi+0x80],0x58`. Grow path uses `0x666b4bf  sub r13,[rsi+0x78]`. [V]
2. `rdis dis` of producer 0x4c88900 (ranges 0x4c88900, 0x4c890c0, 0x4c892f0): re-verified every store that builds the description record at desc base [rbp+0x568] (`0x4c889ad  lea rdx,[rbp+0x568]`, `0x4c889b7  call qword ptr [0xF99FFA0]`, `0x4c889bd  mov r14,[rbp+0x568]`). Byte values of the whole 0x58-byte record are proven [V]. Settings object fields r12+0x74/+0x84/+0x8C/+0x90 are never named by any instruction or string → meanings stay [?].
3. `xref.py str "mBlock"` / `"mValue"` / `"EditorHighlightDescription"` / `"RenderEditorHighlight"`: no string names desc fields +0x10..+0x50. "EditorHighlight" (0xf53accc) is referenced only at 0xbb876ed/0xbb8935e inside 0xbb84ee0 (pass name; uniforms HighlightColor/HighlightAlpha/HighlightTextureColor/Depth/Edge — none are desc fields). Static name hunt failed.
4. New angle per the 2026-11-22 hint (live capture, no game access): capture er5_clone_4c8a5b0 was already queued 2026-11-22 at clone entry 0x4c8a5b0 (rdx = desc ptr, size 0x100, max 6), state pending. docs/data/live/er5_clone_4c8a5b0.txt does not exist yet → [V live] confirmation not available.

## Convention
[V] = seen in the disassembly, instruction cited verbatim; [I] = inferred from instruction pattern; [?] = unknown (no instruction or string shows it). Meaning column = '-' unless an instruction or string shows the meaning. All sizes come from the instruction (movups/movaps 16, qword 8, dword/movss 4).

## Answer table
| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| +0x00 | 8 | [rbx] read `0x666b586`, stored [r15] `0x666b589`; pair built by producer out-param `0x4c889ad  lea rdx,[rbp+0x568]` / `0x4c889b7  call qword ptr [0xF99FFA0]`; `0x4c889bd  mov r14,[rbp+0x568]` | `0x666b586  mov rax,[rbx]` | '-': shared_ref object pointer (pair start at desc+0x00; name not shown) | [I] |
| +0x08 | 8 | [rbx+8] read `0x666b58c`, stored [r15+8] `0x666b590`; strong refcount `0x666b3cb  lock inc dword ptr [rax+8]` (rax = [rbx+8]) | `0x666b58c  mov rax,[rbx+8]` | '-': control-block pointer (visitor refcounts it on queue append; name not shown) | [I] |
| +0x10 | 4 | desc base [rbp+0x568]; `0x4c893df  mov dword ptr [rbp+0x578],1` ([rbp+0x578] = desc+0x10) | `0x4c893df  mov dword ptr [rbp+0x578],1` | '-': dword 1 (enable flag; no name shown) | [?] |
| +0x14 | 8 | rcx = [rbp+0x57C] = desc+0x14; `0x4c89400  mov [rcx],rax` (rax = [r12+0x84] via `0x4c8937e  mov rax,[r12+0x84]`) | `0x4c89400  mov [rcx],rax` | '-': qword [settings+0x84] (settings list element r12; field unnamed) | [?] |
| +0x1C | 4 | `0x4c893f6  mov [rcx+8],eax` (eax = [r12+0x8C] via `0x4c89370  mov eax,[r12+0x8C]`) | `0x4c893f6  mov [rcx+8],eax` | '-': dword [settings+0x8C] (unnamed) | [?] |
| +0x20 | 4 | `0x4c89403  movss [rbp+0x588],xmm14` (xmm14 = `0x4c8938d  movss xmm14,[r12+0x90]`) | `0x4c89403  movss [rbp+0x588],xmm14` | '-': f32 [settings+0x90] (unnamed) | [?] |
| +0x24 | 8 | `0x4c8941c  mov [rcx+0x10],rax` (rax = [r12+0x84]) | `0x4c8941c  mov [rcx+0x10],rax` | '-': qword [settings+0x84] (unnamed) | [?] |
| +0x2C | 4 | `0x4c89412  mov [rcx+0x18],eax` (eax = [r12+0x8C]) | `0x4c89412  mov [rcx+0x18],eax` | '-': dword [settings+0x8C] (unnamed) | [?] |
| +0x30 | 4 | `0x4c89420  movss [rbp+0x598],xmm14` | `0x4c89420  movss [rbp+0x598],xmm14` | '-': f32 [settings+0x90] (unnamed) | [?] |
| +0x34 | 16 | `0x4c89430  movups [rcx+0x20],xmm0` (xmm0 = `0x4c89363  movups xmm0,[r12+0x74]`) | `0x4c89430  movups [rcx+0x20],xmm0` | '-': vec4 [settings+0x74] (unnamed) | [?] |
| +0x44 | 16 | `0x4c89434  movups [rbp+0x5AC],xmm12` (xmm12 = `0x4c890df  movaps xmm12,[0xF20A380]`) | `0x4c89434  movups [rbp+0x5AC],xmm12` | '-': constant vec4 from [0xF20A380] (exact floats unconfirmed this unit; prior note: 0.12, 1, 1, 0.125) | [I] |
| +0x50 | 8 | visitor read `0x666b5b8  mov rax,[rbx+0x50]`, stored `0x666b5bc  mov [r15+0x50],rax`; producer: +0x50..+0x53 inside constant-vec4 store `0x4c89434`, +0x54..+0x57 = `0x4c8943c  mov dword ptr [rbp+0x5BC],0x3F800000` | `0x666b5b8  mov rax,[rbx+0x50]` | '-': +0x50..+0x53 = 0.125f (const vec4 element 3); +0x54..+0x57 = 1.0f; no semantic name shown | [?] |
| pass object | - | `0x666b323  call 0x5ABA5C0` (rcx = [r12+0x10]+0x9D0: `0x666b319  mov ecx,0x9D0` / `0x666b31e  add rcx,[r12+0x10]`; rsi = pass `0x666b328  mov rsi,rax` | `0x666b323  call 0x5ABA5C0` | ThreadLocalObject::get pass owning the +0x80 queue | [V] |
| pass+0x78 | 8 | [rsi+0x78] `0x666b4bf  sub r13,[rsi+0x78]` | `0x666b4bf  sub r13,[rsi+0x78]` | vector begin (element-index math on grow path, loc_666b4bc) | [V] |
| pass+0x80 | 8 | [rsi+0x80] read `0x666b3a6  mov r15,[rsi+0x80]`; element inserted at [r15] via `0x666b589  mov [r15],rax`..`0x666b5bc`; advanced `0x666b5c0` | `0x666b3a6  mov r15,[rsi+0x80]` | end cursor; 0x58-byte element inserted at [end], then end += stride | [V] |
| pass+0x88 | 8 | [rsi+0x88] `0x666b3ad  cmp r15,[rsi+0x88]` | `0x666b3ad  cmp r15,[rsi+0x88]` | vector capacity | [V] |

## Value map of the 0x58-byte description (contents proven [V] by producer stores + verbatim visitor copy)
- +0x00..+0x0F shared_ref pair (object ptr + control block)
- +0x10 = 1; +0x14/+0x24 = qword [r12+0x84]; +0x1C/+0x2C = dword [r12+0x8C]; +0x20/+0x30 = f32 [r12+0x90]; +0x34..+0x43 = vec4 [r12+0x74]
- +0x44..+0x53 = constant vec4 from [0xF20A380]; +0x54..+0x57 = 1.0f (+0x50 qword = {0.125f, 1.0f})
None of these fields has a semantic name in any instruction or string; settings fields r12+0x74/+0x84/+0x8C/+0x90 are unnamed [I: sources only].

## CLOSES?
CLOSES?: NO — single blocking fact: the semantic meanings of the 64-byte block (+0x10..+0x4F) and +0x50 have no [V] proof (no instruction or string names them; they remain [?] rows above). Byte layout/values are [V]-proven, and the pass+0x80 consumer part is [V]-proven inside sub_666aca0 (tag-8 case at 0x666b316). The only evidence that can add to this is the live capture er5_clone_4c8a5b0 (clone entry 0x4c8a5b0, rdx = desc ptr, queued 2026-11-22, state pending), whose result file docs/data/live/er5_clone_4c8a5b0.txt does not exist yet — read it when the orchestrator runs it; even so, it can confirm values, not names.

## TOOL REQUESTS
CAPTURE REQUESTED er5_clone_4c8a5b0 (already queued, state pending: rva 0x4c8a5b0 clone entry, rdx = desc ptr, size 0x100, max 6, why "R5: clone entry, rdx = desc ptr: 64-byte block (+0x10..+0x4F) and +0x50 values"). No other requests; no scripts written this unit.
