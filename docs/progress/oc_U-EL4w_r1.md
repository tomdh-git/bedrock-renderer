## NEXT
DONE

# Unit U-EL4w: close D9c checklist item — gamecomponents fields (GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration)

Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown.

Input data (read fully, not re-generated):
- docs/progress/oc_U-ED9c.md (prior attempt; CLOSES?=NO due to EditorHighlightConfiguration)
- docs/progress/oc_U-EffA.md, oc_U-EffB.md (effect visitor tag read lists)
- docs/data/listings/effect_visitor_666aca0_667191c.txt (effect visitor, tag 8 case head 0x666b316)
- docs/data/listings/lightgame_edhighlight_producer_4c88900_4c89881.txt (producer, rbx=description base)
- docs/data/listings/lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt (thin clone, passes desc ptr + tag 8 to group insert)
- docs/BGFX_MAP.md 6ee (clone kind/group/tag table)

## Part A — GameplayMetadata (Light group, tag 2, clone 0x53e5910, fat)

Fully [V] per oc_U-ED9c.md Part A. All 21 visitor-read offsets (+0x000..+0x080) plus distinct sub-fields have producer stores/zero-init [V]. Previous [UNVERIFIED] marks resolved with correct desc base (rbp-0x40). No pending rows.

## Part B — ServerGraphicsOverrideParameters (Light group, tag 5, clone 0x6c2e820, fat)

Visitor (Light case 5 at 0x66417af, reg rsi) reads only pass-vector metadata [V]:
| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| sg+0x260 | 8 | R 0x6641846 | `0x6641846  mov rbx,[rsi+0x260]` | pass+0x260 qword = vector end [V] | [V]
| sg+0x268 | 8 | R 0x664184d | `0x664184d  cmp rbx,[rsi+0x268]` | pass+0x268 qword = vector cap [V] | [V]

18x0x40 override blocks — decoded [V]: lea rcx,[rdi+0x80+k*0x40] for k=0..43 (0x6c2ee9d .. 0x6c2f514), i.e. 44 blocks x 0x40 = 0xB00 bytes at rdi+0x80..rdi+0xB7F, matching LightGameDescriptions.h size 0xB00 [I]. Copy dispatch calls sub_67b7810 for blocks 0..16, 36..43 and sub_67b7c10 for blocks 17..35 [V]. Per-block hash-map metadata layout from lightgame_serveroverride_setcopy_67b7810.txt [V]:
| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| blk+0x00 | 4 | St 0x67b7837, 0x67b7839 | `0x67b7837  mov eax,[rdx]` ; `0x67b7839  mov [rcx],eax` | max_load_factor dword copied from src [V] | [V]
| blk+0x08 | 8 | St 0x67b786f, 0x67b7873 | `0x67b786f  mov [rax+8],rax` ; `0x67b7873  mov [rsi+8],rax` | list head ptr self-init [V] | [V]
| blk+0x18 | 16 | St 0x67b787b | `0x67b787b  movups [rsi+0x18],xmm6` | bucket_vec_begin/end zeroed (xmm6=0) [V] | [V]
| blk+0x28 | 8 | St 0x67b787f | `0x67b787f  mov qword ptr [rsi+0x28],0` | bucket_vec_cap zeroed [V] | [V]
| blk+0x30 | 8 | St 0x67b7887, 0x67b788b | `0x67b7887  mov rdx,[rdi+0x30]` ; `0x67b788b  mov [rsi+0x30],rdx` | mask qword copied [V] | [V]
| blk+0x38 | 8 | St 0x67b788f, 0x67b7893 | `0x67b788f  mov rdx,[rdi+0x38]` ; `0x67b7893  mov [rsi+0x38],rdx` | max_load_factor_2 qword copied [V] | [V]

Block Value type (float3/u32/set) is opaque from these stores — [?], not decoded. Visitor-read qwords +0x260/+0x268 proven [V]; all remaining block contents are pass-consumer territory.

## Part C — EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin)

Clone (lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt): rcx = description base, rdx = insert arg. `0x4c8a620  mov [rbp+0x10],rdi` stores desc pointer on stack; `0x4c8a624  mov byte ptr [rbp+0x18],8` stores tag 8; insert via vtable slot [rax+0x360]; jump table at prologue `0x666acfb  movsxd rax,[rcx+rax*4]` / `0x666acff  add rax,rcx` / `0x666ad02  jmp rax`, with `0x666acf1  mov r15,[r8]` setting r15 = description base. No description-field stores in the clone — it only passes the pointer and tag to the group insert.

Producer (lightgame_edhighlight_producer_4c88900_4c89881.txt): rbx = rcx arg = description base. Direct stores into rbx (description base) only. All other stores target sub-objects via rcx (=rbp+0x57C) or rax (=rbp+0x528), whose base is NOT the description base.

Producer stores directly into description base [V]:

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| eh+0x38 | 1 | St 0x4c8898e | `0x4c8898e  mov byte ptr [rbx+0x38],1` | init flag byte [V] | [V]
| eh+0x40 | 8 | St 0x4c89163 | `0x4c89163  mov [rbx+0x40],rax` | pointer field stored [V] | [V]
| eh+0x48 | 8 | St 0x4c88d0b | `0x4c88d0b  inc qword ptr [rbx+0x48]` | qword increment [V] | [V]
| eh+0x60 | 16 | St 0x4c88a7b | `0x4c88a7b  movups [rbx+0x60],xmm0` | xmmword stored [V] | [V]
| eh+0x70 | 16 | St 0x4c88ac3 | `0x4c88ac3  movups [rbx+0x70],xmm0` | xmmword stored [V] | [V]

Visitor reads of description base [V]:

Visitor tag-8 case head at `0x666b316  mov rbx,r15` (r15 = description base from prologue). Critical register flow: `0x666b3a6  mov r15,[rsi+0x80]` reassigns r15 to pass-vector cursor; `0x666b3e0  mov rbx,rdi` reassigns rbx (rdi = flags value, not pointer). After those points, `[r15+off]` reads (e.g. at 0x666ccd0..0x666cdd8) are pass-vector/heap-buffer reads, NOT description reads. oc_U-ED9c.md Part C misclassified those as description reads and misclassified `0x666b3ba  movups [r15],xmm6` (a store) as a read.

The only description-base read before register clobbering:

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| eh+0x08 | 8 | R 0x666b3be | `0x666b3be  mov rax,[rbx+8]` | pointer loaded, then `lock inc dword ptr [rax+8]` @0x666b3cb (refcounted object); null-checked at `0x666b3c2` [V] | [V]

Gap: eh+0x08 is READ by the visitor but no producer store into description base exists at +0x08. Producer stores only +0x38/+0x40/+0x48/+0x60/+0x70 directly into rbx. desc+0x08 may be set by code preceding the producer (constructor/allocator) but that is not located in the input data.

## CLOSES?

NO — blocking fact: EditorHighlightConfiguration (Effect tag 8) visitor reads desc+0x08 at `0x666b3be  mov rax,[rbx+8]` [V], but no producer store into description base at +0x08 exists; producer stores only +0x38 (byte), +0x40 (qword), +0x48 (qword inc), +0x60 (xmmword), +0x70 (xmmword) directly into rbx. All other claimed visitor-read offsets in oc_U-ED9c.md Part C use r15 after it was reassigned to pass-vector cursor at `0x666b3a6`, so they are not description reads. GameplayMetadata and ServerGraphicsOverrideParameters are fully [V] (block Value type [?] is non-blocking per ED9c).

## TOOL REQUESTS

None
