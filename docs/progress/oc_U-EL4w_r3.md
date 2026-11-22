## NEXT
DONE

# Unit U-EL4w: close L4w gamecomponents fields — EditorHighlightConfiguration desc+0x08 (pending, blocked)

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown.
Image base 0x140000000.

## Proven — carried over (do NOT redo)

- Part A GameplayMetadata (Light group, tag 2): fully [V] per oc_U-ED9c.md Part A. No pending rows.
- Part B ServerGraphicsOverrideParameters (Light group, tag 5): visitor-read +0x260/+0x268 [V]; block copies [V]; block Value type [?] non-blocking per ED9c.
- Part C EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin): clone passes desc ptr + tag 8 to group insert only, no desc-field stores [V].
- Producer `rbx = rcx` arg = description base (`0x4c88974 mov rbx,rcx`); init flag checked at entry (`0x4c88977 cmp byte ptr [rcx+0x38],0` — desc object persists across calls).

## Answer table — eh+0x08 (pending writer) vs proven producer stores into description base

| Offset | Size | Site | Verbatim `0xRVA  instr` proof | Meaning | Tag |
|--------|------|------|-------------------------------|---------|-----|
| eh+0x08 | 8 | R `0x666b3be` | `0x666b3be  mov rax,[rbx+8]` | refcounted-object pointer READ by visitor; addref `lock inc dword ptr [rax+8]` @`0x666b3cb`; null-checked @`0x666b3c2`; **no producer store to +0x08 located** | [V] |
| eh+0x38 | 1 | St `0x4c8898e` | `0x4c8898e  mov byte ptr [rbx+0x38],1` | producer init flag | [V] |
| eh+0x40 | 8 | St `0x4c89163` | `0x4c89163  mov [rbx+0x40],rax` | producer qword store | [V] |
| eh+0x48 | 8 | St `0x4c88d0b` | `0x4c88d0b  inc qword ptr [rbx+0x48]` | producer qword increment | [V] |
| eh+0x60 | 16 | St `0x4c88a7b` | `0x4c88a7b  movups [rbx+0x60],xmm0` | producer xmmword store | [V] |
| eh+0x70 | 16 | St `0x4c88ac3` | `0x4c88ac3  movups [rbx+0x70],xmm0` | producer xmmword store | [V] |

descscan2 `--start 0x4c88900 --end 0x4c89881 --reg rbx` [V]: rbx accesses at +0x018,+0x038,+0x040,+0x048,+0x060,+0x068,+0x070,+0x078; GAPS include `0x0-0x38` (+0x00..+0x37 untouched). Confirms NO `[rbx+0x08]` store anywhere in the producer.

## Vtable lead (orchestrator hint) — VA correction

`rdis ptr 0x4c88900` -> one .rdata ptr at `0xf20aa50` = slot 0 of vtable `0xf20aa50` (slot 2 = sub_4c9d010 size 0x4000, slot 6 = sub_4c8d340). Producer reached ONLY by virtual call slot 0 on object whose vtable = 0xf20aa50; object `this` = desc base.

- Verified: vtable slot0 stored at `0xf20aa50` = `0089c84401000000` = VA `0x144C88900` = imagebase+0x4C88900 ✓
- **CRITICAL CORRECTION:** vtable VA = `0x144F20AA50` (image base 0x140000000), NOT `0x140F20AA50`.
- `rdis imm 0x144F20AA50` -> 0 hits; `rdis imm 0x004F20AA50` -> 0 hits; scan .rdata+.data for qword == `0x144F20AA50` -> 0 hits. vptr is NEVER materialized statically — purely copied at runtime from another object.
- RTTI dead: `0xf20aa48` shows repeated filler `0x1400768F0` (RVA 0x768F0 = .text), not clean RTTI ptr.
- `rdis xr 0xf20aa50` -> 0 xrefs; `rdis ptr 0xf20aa50` -> 0 pointers.
- Virtual-call dispatcher `sub_eea6040` = `jmp rax` via `call [0xF99FFA0]`. Slot-0 call pattern `mov rax,[obj]; mov rax,[rax]; mov edx,1; call [0xF99FFA0]` exists at many sites (all classes) — cannot filter to vtable 0xf20aa50 statically. Dead thunks `0x4c888d0`/`0x4c888e1` do slot-0 tail-call but 0 static xrefs.

## Constructor hunt — all angles attempted this session (FAILED, do NOT redo)

- **Sibling constructors near producer materialize OTHER vtables via lea, never 0xF20AA50:**
  - `sub_4c88570`: `0x4c885a1 lea rax,[0xF20A9D0]; mov [rcx],rax` (vptr 0xF20A9D0), `0x4c88587 mov dword ptr [rcx+8],0x3F800000` (+0x08=float 1.0), `0x4c885ab lea rax,[0xF20AA60]; mov [rcx+0x10],rax`, `0x4c885b6 lea rax,[0xF20AAB0]; mov [rcx+0x18],rax`, alloc 0x48 sub-object: `0x4c885ff mov rax,0x100000001; mov [rdi+8],rax`; `0x4c8860d lea rax,[0xF146F20]; mov [rdi],rax`; `0x4c8863f mov [rsi+0x70],rdi`. [V]
  - `sub_4c886d0`: same family, vptr 0xF20A9D0 at `0x4c8872a`, sub-object vptr 0xF146F20 at `0x4c8879e`, `0x4c88790 mov rbx,0x100000001; mov [rdi+8],rbx`, sub-object vptr 0xF20B420 at `0x4c8880c`. [V]
  - Pattern `lea rax,[0xF20AA50]` does NOT exist anywhere (lea_find 0xf20aa50 -> 0). So our class does NOT materialize its vptr.
- **Constructor pattern at `0x4c8d407` (vtable slot-6 region) IS an object-header copy constructor but for a DIFFERENT class:** `0x4c8d407 mov rcx,0x100000001; mov [rax+8],rcx` (+0x08 = immediate 0x100000001, NOT a pointer); `0x4c8d415 lea rcx,[0xF0ED760]; mov [rax],rcx` (vptr 0xF0ED760); `0x4c8d46a mov [rsi],rcx; mov [rsi+8],rax`. vptr 0xF0ED760 != 0xF20AA50, and +0x08 is an immediate not a pointer (visitor addrefs desc+0x08 so it must be a valid heap pointer). [V]
- **sub_4c9d010 (vtable slot 2):** adjustor-thunk/collection iterator at `0x4c9d010 add rcx,0xFFFFFFF0; jmp 0x4CA48D0`, then `0x4c9d040` real body iterates vector with `lock inc dword ptr [rax+8]` (addref) and `movups [rsi],xmm0` @`0x4c9d0d3`. Not a constructor setting desc+0x08. [V]
- **sub_4c8d340 (vtable slot 6):** tiny accessor `mov rcx,[rcx+0x30]...call sub_1580f30...ret`. Not our constructor. [V]
- **Producer-internal virtual call:** `0x4c889a3 mov rax,[rsi]; mov rax,[rax+0x338]; lea rdx,[rbp+0x568]; mov rcx,rsi; call qword ptr [0xF99FFA0]` (slot 0x338 on object rsi=r8, result [rbp+0x568]=r14, refcounted). This r14 is used for texture loading (`0x4c889d5` `0x79616C7265764F2D`, `0x4c889e3 movups xmm0,[0xF51E461]` "textures/editor/Volume-Highlight-Overlay"), stored at desc+0x60/+0x70 region, NOT desc+0x08. [V]
- **`call 0x331df0` (refcounted-field init):** 30 sites, NONE inits [reg+0x08] (only +0x18 at producer `0x4c88989`, +0x28 at `0x6c52832`). [V]
- **`fld 8 --w`:** no [reg+8] writes in producer region. [V]
- **Livemem:** game running (pid 18956, base 0x7ff699000000, version OK) [V status], but NO EditorHighlightConfiguration instance address known to target; range-scanning forbidden by brief. `livemem vt 0x14A604` earlier -> all zeros (no tag-8 live capture data). [V] Cannot ground-truth desc+0x08 via live without a target address.

## CLOSES?

NO — blocking fact: EditorHighlightConfiguration (Effect tag 8) visitor reads desc+0x08 at `0x666b3be mov rax,[rbx+8]` [V] (refcounted-object pointer; addref `0x666b3cb lock inc dword ptr [rax+8]`; null-check `0x666b3c2 test rax,rax`), but NO producer store into description base at +0x08 exists (complete rbx store enumeration [V]: only +0x38/+0x40/+0x48/+0x60/+0x70). desc+0x08 is set before the producer by a constructor that (a) stores vptr 0xf20aa50 at [obj+0] and (b) stores a valid heap refcounted pointer at [obj+0x08]. vptr 0xf20aa50 is NEVER materialized statically (imm/lea/data-scan all 0 [V]) — purely runtime-copied from a prototype — so the constructor and the desc+0x08 writer cannot be located by any static angle attempted. RTTI stripped [V]. GameplayMetadata fully [V]; ServerGraphicsOverrideParameters fully [V] (block Value type [?] non-blocking per ED9c).

## TOOL REQUESTS

None
