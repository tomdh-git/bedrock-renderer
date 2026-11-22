## NEXT
DONE

# Unit U-ED9c: close D9c checklist item — gamecomponents fields (GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration)

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown.

Input data (read fully, not re-generated):
- docs/progress/oc_U-D9c.md (clone/visitor offsets tabulated; 25 rows [UNVERIFIED])
- docs/progress/oc_U-D9c2.md (previously [UNVERIFIED] rows resolved where possible; remaining gaps: virtual call targets, hash map Value types)
- docs/progress/oc_U-ED9c_r1.md (prior RETRY attempt; CLOSES?=NO due to EditorHighlightConfiguration)
- docs/progress/oc_U-EL4w_r1.md (verify_oc 28/28; corrects ED9c Part C: after 0x666b3a6 r15 is the pass-vector cursor, so only description read is eh+0x08)
- docs/progress/oc_U-EffB.md (effect visitor tag read lists; tag 8: only 12 read sites)
- docs/BGFX_MAP.md section 6ee (clone kind/group/tag table)

Pending part of the D9c item line (single blocking fact):
- EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin): visitor reads desc+0x08 at `0x666b3be  mov rax,[rbx+8]` [V] (pointer to a refcounted object; addref `lock inc dword ptr [rax+8]` @0x666b3cb; null-checked `test rax,rax` @0x666b3c2), but no producer store into the description base at +0x08 exists; producer stores only +0x38 (byte), +0x40 (qword), +0x48 (qword inc), +0x60 (xmmword), +0x70 (xmmword) directly into rbx [V]. desc+0x08 is set before the producer — not yet located. All other claimed visitor-read offsets in oc_U-ED9c.md Part C use r15 after it was reassigned to the pass-vector cursor at `0x666b3a6  mov r15,[rsi+0x80]`, so they are not description reads (per oc_U-EL4w_r1.md). GameplayMetadata fully [V]; ServerGraphicsOverrideParameters visitor reads +0x260/+0x268 [V] + block metadata layout [V] (block Value type [?], non-blocking).

## Part A — GameplayMetadata (Light group, tag 2, clone 0x53e5910, fat 0x804 bytes)

Carried over from oc_U-ED9c_r1.md Part A, all [V], verified with corrected desc base (desc buffer = [rbp+0x40], so desc_off = rbp_off - 0x40). All 21 visitor-read offsets (+0x000..+0x080) plus distinct sub-fields have producer stores/zero-init [V]. No pending rows.

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| gm+0x000 | 16 | St 0x53e5ae2, 0x53e5ef3; R 0x6640f8c | `0x53e5ae2  movaps [rbp+0x40],xmm0` ; `0x53e5ef3  movss [rbp+0x40],xmm0` ; `0x6640f8c  movups xmm0,[rsi]` | xorps xmm0 @0x53e5ad3 then movaps zero-inits desc+0x000; movss overwrites low dword; visitor reads xmmword [V] | [V] |
| gm+0x008 | 4 | St 0x53e5c97 | `0x53e5c97  movss [rbp+0x48],xmm0` | float stored at desc+0x008 [V] | [V] |
| gm+0x00C | 4 | St 0x53e5ee0 | `0x53e5ee0  movss [rbp+0x4C],xmm0` | byte->float (cvtsi2ss) at desc+0x00C [V] | [V] |
| gm+0x010 | 16 | St 0x53e5ade; R 0x6640f8f | `0x53e5ade  movaps [rbp+0x50],xmm0` ; `0x6640f8f  movups xmm1,[rsi+0x10]` | zero-init mat4 row 1 [V] | [V] |
| gm+0x014 | 4 | St 0x53e5d2f | `0x53e5d2f  movss [rbp+0x54],xmm0` | - | [V] |
| gm+0x018 | 4 | St 0x53e5d40 | `0x53e5d40  movss [rbp+0x58],xmm0` | - | [V] |
| gm+0x01C | 4 | St 0x53e5f47 | `0x53e5f47  mov [rbp+0x5C],eax` | - | [V] |
| gm+0x020 | 16 | St 0x53e5ada, 0x53e5b31; R 0x6640f93 | `0x53e5ada  movaps [rbp+0x60],xmm0` ; `0x53e5b31  mov [rbp+0x60],eax` ; `0x6640f93  movups xmm2,[rsi+0x20]` | zero then dword from vcall [rax+0x420] @0x53e5b2a [V] | [V] |
| gm+0x024 | 4 | St 0x53e5c1e | `0x53e5c1e  mov [rbp+0x64],eax` | hash dword (imul 0x57619F1 sequence @0x53e5bfe-0x53e5c1e) [V] | [V] |
| gm+0x028 | 4 | St 0x53e5c44 | `0x53e5c44  mov [rbp+0x68],eax` | - | [V] |
| gm+0x02A | 16 | St 0x53e5ad6; R 0x6640f97 | `0x53e5ad6  movups [rbp+0x6A],xmm0` ; `0x6640f97  movups xmm3,[rsi+0x2A]` | unaligned zero-init row 3 [V] | [V] |
| gm+0x02C | 4 | St 0x53e5c8c; R 0x6641042 | `0x53e5c8c  mov [rbp+0x6C],eax` ; `0x6641042  movss xmm0,[rsi+0x6C]` | hash & 7 bucket index [V] | [V] |
| gm+0x030 | 4 | St 0x53e5df5, 0x53e5e0b; R 0x664104e | `0x53e5df5  mov eax,[rbp+0x70]` ; `0x53e5e0b  mov [rbp+0x70],eax` ; `0x664104e  movss xmm0,[rsi+0x70]` | flag bits read-modify-write back [V] | [V] |
| gm+0x034 | 2 | St 0x53e5be0 | `0x53e5be0  mov [rbp+0x74],ax` | - | [V] |
| gm+0x036 | 1 | St 0x53e5bab | `0x53e5bab  mov [rbp+0x76],al` | setge flag byte [V] | [V] |
| gm+0x037 | 1 | St 0x53e5bcb | `0x53e5bcb  sete [rbp+0x77]` | - | [V] |
| gm+0x038 | 1 | St 0x53e5b5b | `0x53e5b5b  mov [rbp+0x78],al` | byte [V] | [V] |
| gm+0x039 | 1 | St 0x53e5c4c | `0x53e5c4c  mov [rbp+0x79],al` | - | [V] |
| gm+0x03C | 8 | St 0x53e5aee, 0x53e5b38; R 0x6640fb2 | `0x53e5aee  movsd [rbp+0x7C],xmm1` ; `0x53e5b38  movss [rbp+0x7C],xmm0` ; `0x6640fb2  movss xmm0,[rsi+0x3C]` | movsd double then movss float overwrite [V] | [V] |
| gm+0x040 | 4 | St 0x53e5b42; R 0x6640fbe | `0x53e5b42  movss [rbp+0x80],xmm0` ; `0x6640fbe  movss xmm0,[rsi+0x40]` | float [V] | [V] |
| gm+0x044 | 4 | St 0x53e5af3, 0x53e5b4f; R 0x6640fca | `0x53e5af3  mov dword ptr [rbp+0x84],0x7F7FFFFF` ; `0x53e5b4f  movss [rbp+0x84],xmm0` ; `0x6640fca  movss xmm0,[rsi+0x44]` | max float then overwrite [V] | [V] |
| gm+0x048 | 4 | St 0x53e5afd, 0x53e5d93; R 0x6640fd6 | `0x6640fd6  movss xmm0,[rsi+0x48]` ; `0x53e5afd  movups [rbp+0x88],xmm0` ; `0x53e5d93  movss [rbp+0x88],xmm0` | visitor reads dword; producer zero-inits 16B xmmword then float [V] | [V] |
| gm+0x04C | 4 | St 0x53e5da2; R 0x6640fe2 | `0x6640fe2  movss xmm0,[rsi+0x4C]` ; `0x53e5da2  movups [rbp+0x8C],xmm4` | visitor reads dword; producer xmmword [V] | [V] |
| gm+0x050 | 4 | St: zero-init 0x53e5afd covers +0x048..+0x057; no later store; R 0x6640fee | `0x6640fee  movss xmm0,[rsi+0x50]` ; `0x53e5afd  movups [rbp+0x88],xmm0` | zero-initialized, never overwritten [V] | [V] |
| gm+0x058 | 4 | St: zero-init 0x53e5b04 covers +0x058..+0x067; R 0x6641006 | `0x6641006  movss xmm0,[rsi+0x58]` ; `0x53e5b04  movups [rbp+0x98],xmm0` | producer zero-inits 16 bytes; visitor reads dword [V] | [V] |
| gm+0x05C | 4 | St 0x53e5da9; R 0x6641012 | `0x53e5da9  movss [rbp+0x9C],xmm2` ; `0x6641012  movss xmm0,[rsi+0x5C]` | - | [V] |
| gm+0x060 | 4 | St 0x53e5dc6; R 0x664101e | `0x664101e  movss xmm0,[rsi+0x60]` ; `0x53e5dc6  movsd [rbp+0xA0],xmm1` | producer stores double (movsd 8B at desc+0x060); visitor reads dword [V] | [V] |
| gm+0x064 | 4 | St: covered by movsd [rbp+0xA0] @0x53e5dc6 (+0x060..+0x067); R 0x664102a | `0x664102a  movss xmm0,[rsi+0x64]` ; `0x53e5dc6  movsd [rbp+0xA0],xmm1` | high dword of the double at +0x060 [I: overlap, no distinct store] | [I] |
| gm+0x068 | 4 | St 0x53e5b0b, 0x53e5dce; R 0x6641036 | `0x6641036  movss xmm0,[rsi+0x68]` ; `0x53e5b0b  movups [rbp+0xA8],xmm0` ; `0x53e5dce  movss [rbp+0xA8],xmm0` | zero-init 16B then float overwrite [V] | [V] |
| gm+0x06C | 4 | St: zero-init movups [rbp+0xA8] covers +0x068..+0x077; R 0x6641042 | `0x6641042  movss xmm0,[rsi+0x6C]` ; `0x53e5b0b  movups [rbp+0xA8],xmm0` | zero-initialized, no later store [V] | [V] |
| gm+0x070 | 4 | St: zero-init movups [rbp+0xA8] covers +0x068..+0x077; R 0x664104e | `0x664104e  movss xmm0,[rsi+0x70]` ; `0x53e5b0b  movups [rbp+0xA8],xmm0` | zero-initialized [V] (flag stores at [rbp+0x70] write desc+0x030, a different field) | [V] |
| gm+0x074 | 4 | St: zero-init movups [rbp+0xB4] covers +0x074..+0x083; R 0x664105a | `0x664105a  movss xmm0,[rsi+0x74]` ; `0x53e5b12  movups [rbp+0xB4],xmm0` | zero-initialized [V] | [V] |
| gm+0x078 | 4 | St: zero-init movups [rbp+0xB4]; R 0x6641066 | `0x6641066  movss xmm0,[rsi+0x78]` ; `0x53e5b12  movups [rbp+0xB4],xmm0` | zero-initialized [V] | [V] |
| gm+0x07C | 4 | St: zero-init movups [rbp+0xB4]; R 0x6641072 | `0x6641072  movss xmm0,[rsi+0x7C]` ; `0x53e5b12  movups [rbp+0xB4],xmm0` | zero-initialized [V] (producer movss [rbp+0x7C] writes desc+0x03C, a different field) | [V] |
| gm+0x080 | 4 | St: zero-init movups [rbp+0xB4]; R 0x664107e | `0x664107e  movss xmm0,[rsi+0x80]` ; `0x53e5b12  movups [rbp+0xB4],xmm0` | zero-initialized [V] | [V] |

**GameplayMetadata conclusion:** all visitor-read offsets have producer stores/zero-init [V]. No pending rows.

## Part B — ServerGraphicsOverrideParameters (Light group, tag 5, clone 0x6c2e820, fat 0x105e bytes)

Visitor (Light case 5 at 0x66417af, reg rsi) reads only pass-vector metadata [V]:

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| sg+0x260 | 8 | R 0x6641846 | `0x6641846  mov rbx,[rsi+0x260]` | pass+0x260 qword = vector end (read twice) [V] | [V] |
| sg+0x268 | 8 | R 0x664184d | `0x664184d  cmp rbx,[rsi+0x268]` | pass+0x268 qword = vector cap [V] | [V] |

18x0x40 override blocks — decoded [V]: lea rcx,[rdi+0x80+k*0x40] for k=0..43 (0x6c2ee9d .. 0x6c2f514), i.e. 44 blocks x 0x40 = 0xB00 bytes at rdi+0x80..rdi+0xB7F, matching LightGameDescriptions.h size 0xB00 [I]. Copy dispatch calls sub_67b7810 for blocks 0..16, 36..43 and sub_67b7c10 for blocks 17..35 [V]. Per-block hash-map metadata layout from lightgame_serveroverride_setcopy_67b7810.txt [V]:

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| blk+0x00 | 4 | St 0x67b7837, 0x67b7839 | `0x67b7837  mov eax,[rdx]` ; `0x67b7839  mov [rcx],eax` | max_load_factor dword copied from src [V] | [V] |
| blk+0x08 | 8 | St 0x67b786f, 0x67b7873 | `0x67b786f  mov [rax+8],rax` ; `0x67b7873  mov [rsi+8],rax` | list head ptr self-init [V] | [V] |
| blk+0x18 | 16 | St 0x67b787b | `0x67b787b  movups [rsi+0x18],xmm6` | bucket_vec_begin/end zeroed (xmm6=0) [V] | [V] |
| blk+0x28 | 8 | St 0x67b787f | `0x67b787f  mov qword ptr [rsi+0x28],0` | bucket_vec_cap zeroed [V] | [V] |
| blk+0x30 | 8 | St 0x67b7887, 0x67b788b | `0x67b7887  mov rdx,[rdi+0x30]` ; `0x67b788b  mov [rsi+0x30],rdx` | mask qword copied [V] | [V] |
| blk+0x38 | 8 | St 0x67b788f, 0x67b7893 | `0x67b788f  mov rdx,[rdi+0x38]` ; `0x67b7893  mov [rsi+0x38],rdx` | max_load_factor_2 qword copied [V] | [V] |

Block Value type (float3/u32/set) is opaque from these stores — [?], not decoded (non-blocking per ED9c). Visitor-read qwords +0x260/+0x268 proven [V]; all remaining block contents are pass-consumer territory.

## Part C — EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin 0x139 bytes)

Clone (lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt): `0x4c8a5cb  mov rdi,rdx` (description pointer), `0x4c8a5ce  mov rsi,rcx` (insert target); `0x4c8a620  mov [rbp+0x10],rdi` stores desc pointer on stack; `0x4c8a624  mov byte ptr [rbp+0x18],8` stores tag 8; `0x4c8a628  mov rax,[rsi]` / `0x4c8a62b  mov rax,[rax+0x360]` vtable slot 0x360 (Effect group); `0x4c8a639  call qword ptr [0xF99FFA0]` invokes group insert. No description-memory stores in the clone — it only passes the pointer and tag [V]. At the producer's clone call site `0x4c89478  call 0x4C8A5B0`, rdx = `0x4c89471  lea rdx,[rbp+0x568]` (out-param of a virtual call) and rcx = `0x4c8946a  mov rcx,[rbp+0x6C0]` — identity of that pointer with the producer's rbx base is not provable from the listing.

Producer (lightgame_edhighlight_producer_4c88900_4c89881.txt): `0x4c88974  mov rbx,rcx` (rbx = rcx arg = description base), `0x4c88977  cmp byte ptr [rcx+0x38],0` (init flag checked at entry — description object persists across producer calls). **Complete [rbx+off] store enumeration via tools/sigs/stores.py [V] (21 store sites; all others target sub-objects via rcx/rax or NULL [0]):**

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| eh+0x38 | 1 | St 0x4c8898e | `0x4c8898e  mov byte ptr [rbx+0x38],1` | init flag byte [V] | [V] |
| eh+0x40 | 8 | St 0x4c89163 | `0x4c89163  mov [rbx+0x40],rax` | pointer field stored [V] | [V] |
| eh+0x48 | 8 | St 0x4c88d0b | `0x4c88d0b  inc qword ptr [rbx+0x48]` | qword increment [V] | [V] |
| eh+0x60 | 16 | St 0x4c88a7b | `0x4c88a7b  movups [rbx+0x60],xmm0` | xmmword stored [V] | [V] |
| eh+0x70 | 16 | St 0x4c88ac3 | `0x4c88ac3  movups [rbx+0x70],xmm0` | xmmword stored [V] | [V] |

**No store to rbx+0x08 exists anywhere in the producer** (confirmed by the complete enumeration above; the rcx+8/rax+8 sites are sub-object refcount fields, not the description base).

Visitor register flow (Effect case 8 head at `0x666b316  mov rbx,r15`, so rbx = description base; rbx is clobbered only later at `0x666b3e0  mov rbx,rdi`; r15 is reassigned to the pass-vector cursor at `0x666b3a6  mov r15,[rsi+0x80]`):

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| eh+0x08 | 8 | R 0x666b3be; St: NONE | `0x666b3be  mov rax,[rbx+8]` ; `0x666b3c2  test rax,rax` ; `0x666b3cb  lock inc dword ptr [rax+8]` | pointer to a refcounted object loaded from desc+0x08, addrefed by the visitor, null-checked; **no producer store to rbx+0x08 exists** (complete rbx store enumeration [V]); clone writes no description memory [V]; producer 0x4c88900 has no direct callers and address 0x4c88900 is not referenced anywhere in the exe (imm32/imm64/ripscan: 0 hits [V]) — called indirectly, so the code that sets desc+0x08 before the producer is upstream of the input data and not located | [UNVERIFIED: 0x4c88900 no store to rbx+0x08; writer of desc+0x08 not found] |

All other eh+0x.. offsets claimed in oc_U-ED9c.md Part C are NOT description reads: `0x666b3ba  movups [r15],xmm6` is a store, and every `[r15+off]` read at 0x666ccd0..0x666cdd8 uses r15 after `0x666b3a6  mov r15,[rsi+0x80]` made it the pass-vector cursor (per oc_U-EL4w_r1.md, verify_oc 28/28). Producer stores into sub-objects (rcx = rbp+0x57C, rax = rbp+0x528) have bases not provably equal to the description base, so they cannot close eh+0x08.

**EditorHighlightConfiguration conclusion:** only eh+0x38/+0x40/+0x48/+0x60/+0x70 have producer stores into the description base [V]; eh+0x08 is the sole visitor-read description-base offset and has no matching producer store — it is set before the producer by code not located in the inputs.

## CLOSES?

NO — blocking fact: EditorHighlightConfiguration (Effect tag 8) visitor reads desc+0x08 at `0x666b3be  mov rax,[rbx+8]` [V] (refcounted-object pointer; addref `0x666b3cb  lock inc dword ptr [rax+8]`; null-check `0x666b3c2  test rax,rax`), but no producer store into the description base exists at +0x08. Complete [rbx+off] store enumeration [V] covers only rbx+0x38 (byte), +0x40 (qword), +0x48 (qword inc), +0x60 (xmmword), +0x70 (xmmword); clone 0x4c8a5b0 writes no description memory [V]. Producer 0x4c88900 has no direct callers and its address is not referenced anywhere in the exe (imm32 imm64 ripscan: 0 hits [V]) — called indirectly — so the code that sets desc+0x08 before the producer is upstream of the input data and not located. [UNVERIFIED: 0x4c88900 no store to rbx+0x08; writer of desc+0x08 not found]. GameplayMetadata fully [V]; ServerGraphicsOverrideParameters visitor reads +0x260/+0x268 [V] + block metadata [V] (block Value type [?], non-blocking).

## TOOL REQUESTS

1. **indirect-caller / vtable-slot resolver** | input: producer RVA 0x4c88900 | output: caller(s) that set desc+0x08 before the extractor runs | why: producer address is not referenced as a literal anywhere in the exe (imm32/imm64/ripscan all 0 hits), so its caller — and the writer of desc+0x08 — cannot be found statically from current inputs.

## NEXT

step 2
