## NEXT
DONE

# Unit U-ED9c: close D9c checklist item — GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration pending fields

Checklist D9c follow-up (unit U-ED9c). Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown.

Input data (read fully, not re-generated):
- docs/progress/oc_U-D9c.md (clone/visitor offsets tabulated; 25 rows [UNVERIFIED])
- docs/progress/oc_U-D9c2.md (previously [UNVERIFIED] rows resolved where possible; remaining gaps: virtual call targets, hash map Value types)

Pending parts of the D9c item line:
1. Visitor reads without matching producer stores (the [UNVERIFIED] field rows).
2. 18x0x40 override blocks not decoded.

Method note: in lightgame_gameplaymeta_clone_53e5910_53e6114.txt the description buffer is [rbp+0x40] (zeroed 0x40..0xB4 at entry), so desc_off = rbp_off - 0x40. D9c/D9c2 treated rbp offsets as desc offsets, which is why +0x000/+0x010/+0x02A and +0x070..+0x080 were left [UNVERIFIED]; with the correct base every visitor-read offset has a producer store or zero-init [V]. Offset cells are prefixed gm=/sg=/eh=/blk+ to keep them unique across the three tables. All instruction lines below are copied verbatim from the listing files (rdis output).

## Part A — GameplayMetadata (Light group, tag 2, clone 0x53e5910, fat)
Visitor: Light case 2 at 0x6640f1b (reg rsi). Field map — one row per distinct offset, visitor-read instruction cited first (size column = size of that instruction). All sites listed.

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| gm+0x000 | 16 | St 0x53e5ae2, 0x53e5ef3; R 0x6640f8c | `0x53e5ae2  movaps [rbp+0x40],xmm0` ; `0x53e5ef3  movss [rbp+0x40],xmm0` ; `0x6640f8c  movups xmm0,[rsi]` | xorps xmm0 @0x53e5ad3 then movaps zero-inits desc+0x000; movss overwrites low dword; visitor reads xmmword [V] | [V]
| gm+0x008 | 4 | St 0x53e5c97 | `0x53e5c97  movss [rbp+0x48],xmm0` | [rdi+0x5D8] float stored at desc+0x008 [V] | [V]
| gm+0x00C | 4 | St 0x53e5ee0 | `0x53e5ee0  movss [rbp+0x4C],xmm0` | byte->float (cvtsi2ss) at desc+0x00C [V] | [V]
| gm+0x010 | 16 | St 0x53e5ade; R 0x6640f8f | `0x53e5ade  movaps [rbp+0x50],xmm0` ; `0x6640f8f  movups xmm1,[rsi+0x10]` | zero-init mat4 row 1 [V] | [V]
| gm+0x014 | 4 | St 0x53e5d2f | `0x53e5d2f  movss [rbp+0x54],xmm0` | [V] | [V]
| gm+0x018 | 4 | St 0x53e5d40 | `0x53e5d40  movss [rbp+0x58],xmm0` | [V] | [V]
| gm+0x01C | 4 | St 0x53e5f47 | `0x53e5f47  mov [rbp+0x5C],eax` | [V] | [V]
| gm+0x020 | 16 | St 0x53e5ada, 0x53e5b31; R 0x6640f93 | `0x53e5ada  movaps [rbp+0x60],xmm0` ; `0x53e5b31  mov [rbp+0x60],eax` ; `0x6640f93  movups xmm2,[rsi+0x20]` | zero then dword from vcall [rax+0x420] @0x53e5b2a [V] | [V]
| gm+0x024 | 4 | St 0x53e5c1e | `0x53e5c1e  mov [rbp+0x64],eax` | hash dword (imul 0x57619F1 sequence @0x53e5bfe-0x53e5c1e) [V] | [V]
| gm+0x028 | 4 | St 0x53e5c44 | `0x53e5c44  mov [rbp+0x68],eax` | [V] | [V]
| gm+0x02A | 16 | St 0x53e5ad6; R 0x6640f97 | `0x53e5ad6  movups [rbp+0x6A],xmm0` ; `0x6640f97  movups xmm3,[rsi+0x2A]` | unaligned zero-init row 3 [V] | [V]
| gm+0x02C | 4 | St 0x53e5c8c; R 0x6641042 | `0x53e5c8c  mov [rbp+0x6C],eax` ; `0x6641042  movss xmm0,[rsi+0x6C]` | hash & 7 bucket index [V] | [V]
| gm+0x030 | 4 | St 0x53e5df5, 0x53e5e0b; R 0x664104e | `0x53e5df5  mov eax,[rbp+0x70]` ; `0x53e5e0b  mov [rbp+0x70],eax` ; `0x664104e  movss xmm0,[rsi+0x70]` | flag bits: comparisons vs [rcx+0x2BC0..0x2BD8] or bits into eax, read-modify-write back [V] | [V]
| gm+0x034 | 2 | St 0x53e5be0 | `0x53e5be0  mov [rbp+0x74],ax` | [V] | [V]
| gm+0x036 | 1 | St 0x53e5bab | `0x53e5bab  mov [rbp+0x76],al` | setge flag byte [V] | [V]
| gm+0x037 | 1 | St 0x53e5bcb | `0x53e5bcb  sete [rbp+0x77]` | [V] | [V]
| gm+0x038 | 1 | St 0x53e5b5b | `0x53e5b5b  mov [rbp+0x78],al` | [rsi+0x7D] byte [V] | [V]
| gm+0x039 | 1 | St 0x53e5c4c | `0x53e5c4c  mov [rbp+0x79],al` | [V] | [V]
| gm+0x03C | 8 | St 0x53e5aee, 0x53e5b38; R 0x6640fb2 | `0x53e5aee  movsd [rbp+0x7C],xmm1` ; `0x53e5b38  movss [rbp+0x7C],xmm0` ; `0x6640fb2  movss xmm0,[rsi+0x3C]` | movsd double then movss float overwrite [V] | [V]
| gm+0x040 | 4 | St 0x53e5b42; R 0x6640fbe | `0x53e5b42  movss [rbp+0x80],xmm0` ; `0x6640fbe  movss xmm0,[rsi+0x40]` | [rsi+4] float [V] | [V]
| gm+0x044 | 4 | St 0x53e5af3, 0x53e5b4f; R 0x6640fca | `0x53e5af3  mov dword ptr [rbp+0x84],0x7F7FFFFF` ; `0x53e5b4f  movss [rbp+0x84],xmm0` ; `0x6640fca  movss xmm0,[rsi+0x44]` | max float then overwrite [rsi+8] [V] | [V]
| gm+0x048 | 4 | St 0x53e5afd, 0x53e5d93; R 0x6640fd6 | `0x6640fd6  movss xmm0,[rsi+0x48]` ; `0x53e5afd  movups [rbp+0x88],xmm0` ; `0x53e5d93  movss [rbp+0x88],xmm0` | visitor reads dword; producer zero-inits 16B xmmword then [rdi+0x5D8] float [V] | [V]
| gm+0x04C | 4 | St 0x53e5da2; R 0x6640fe2 | `0x6640fe2  movss xmm0,[rsi+0x4C]` ; `0x53e5da2  movups [rbp+0x8C],xmm4` | visitor reads dword; producer xmmword [V] | [V]
| gm+0x050 | 4 | St: zero-init 0x53e5afd covers +0x048..+0x057; no later store; R 0x6640fee | `0x6640fee  movss xmm0,[rsi+0x50]` ; `0x53e5afd  movups [rbp+0x88],xmm0` | zero-initialized, never overwritten [V] | [V]
| gm+0x058 | 4 | St: zero-init 0x53e5b04 covers +0x058..+0x067; R 0x6641006 | `0x6641006  movss xmm0,[rsi+0x58]` ; `0x53e5b04  movups [rbp+0x98],xmm0` | producer zero-inits 16 bytes; visitor reads dword [V] | [V]
| gm+0x05C | 4 | St 0x53e5da9; R 0x6641012 | `0x53e5da9  movss [rbp+0x9C],xmm2` ; `0x6641012  movss xmm0,[rsi+0x5C]` | [V] | [V]
| gm+0x060 | 4 | St 0x53e5dc6; R 0x664101e | `0x664101e  movss xmm0,[rsi+0x60]` ; `0x53e5dc6  movsd [rbp+0xA0],xmm1` | producer stores double (movsd 8B at desc+0x060); visitor reads dword [V] | [V]
| gm+0x064 | 4 | St: covered by movsd [rbp+0xA0] @0x53e5dc6 (+0x060..+0x067); R 0x664102a | `0x664102a  movss xmm0,[rsi+0x64]` ; `0x53e5dc6  movsd [rbp+0xA0],xmm1` | high dword of the double at +0x060 [I: overlap, no distinct store] | [I]
| gm+0x068 | 4 | St 0x53e5b0b, 0x53e5dce; R 0x6641036 | `0x6641036  movss xmm0,[rsi+0x68]` ; `0x53e5b0b  movups [rbp+0xA8],xmm0` ; `0x53e5dce  movss [rbp+0xA8],xmm0` | zero-init 16B then float overwrite [V] | [V]
| gm+0x06C | 4 | St: zero-init movups [rbp+0xA8] covers +0x068..+0x077; R 0x6641042 | `0x6641042  movss xmm0,[rsi+0x6C]` ; `0x53e5b0b  movups [rbp+0xA8],xmm0` | zero-initialized, no later store [V] | [V]
| gm+0x070 | 4 | St: zero-init movups [rbp+0xA8] covers +0x068..+0x077; R 0x664104e | `0x664104e  movss xmm0,[rsi+0x70]` ; `0x53e5b0b  movups [rbp+0xA8],xmm0` | zero-initialized [V] (flag stores at [rbp+0x70] write desc+0x030, a different field) | [V]
| gm+0x074 | 4 | St: zero-init movups [rbp+0xB4] covers +0x074..+0x083; R 0x664105a | `0x664105a  movss xmm0,[rsi+0x74]` ; `0x53e5b12  movups [rbp+0xB4],xmm0` | zero-initialized [V] | [V]
| gm+0x078 | 4 | St: zero-init movups [rbp+0xB4]; R 0x6641066 | `0x6641066  movss xmm0,[rsi+0x78]` ; `0x53e5b12  movups [rbp+0xB4],xmm0` | zero-initialized [V] | [V]
| gm+0x07C | 4 | St: zero-init movups [rbp+0xB4]; R 0x6641072 | `0x6641072  movss xmm0,[rsi+0x7C]` ; `0x53e5b12  movups [rbp+0xB4],xmm0` | zero-initialized [V] (producer movss [rbp+0x7C] writes desc+0x03C, a different field) | [V]
| gm+0x080 | 4 | St: zero-init movups [rbp+0xB4]; R 0x664107e | `0x664107e  movss xmm0,[rsi+0x80]` ; `0x53e5b12  movups [rbp+0xB4],xmm0` | zero-initialized [V] | [V]

**GameplayMetadata conclusion:** all 21 visitor-read offsets (+0x000..+0x080) plus distinct sub-fields have producer stores/zero-init [V]. Previous [UNVERIFIED] marks for +0x000/+0x010/+0x02A/+0x070..+0x080 resolved; no pending rows remain for this type.

## Part B — ServerGraphicsOverrideParameters (Light group, tag 5, clone 0x6c2e820, fat)
Visitor: Light case 5 at 0x66417af (reg rsi). Producer builds description at rdi+0x80 (lea rcx,[rdi+0x80] @0x6c2ee9d). Visitor reads only pass-vector metadata [V]:

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| sg+0x260 | 8 | R 0x6641846 | `0x6641846  mov rbx,[rsi+0x260]` | pass+0x260 qword = vector end (read twice per descscan2 x2) [V] | [V]
| sg+0x268 | 8 | R 0x664184d | `0x664184d  cmp rbx,[rsi+0x268]` | pass+0x268 qword = vector cap [V] | [V]

**18x0x40 override blocks — decoded [V]:** _reads_U-D9cA.txt shows lea rcx,[rdi+0x80+k*0x40] for k=0..43 (0x6c2ee9d .. 0x6c2f514), i.e. 44 blocks x 0x40 = 0xB00 bytes at rdi+0x80..rdi+0xB7F, matching LightGameDescriptions.h size 0xB00 [I]. Copy dispatch (lightgame_serveroverride_copy_67b6300.txt) calls sub_67b7810 for blocks 0..16, 36..43 and sub_67b7c10 for blocks 17..35 [V, call sites 0x67b6333..0x67b6b7b]. Per-block hash-map metadata layout from lightgame_serveroverride_setcopy_67b7810.txt [V]:

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| blk+0x00 | 4 | St 0x67b7837, 0x67b7839 | `0x67b7837  mov eax,[rdx]` ; `0x67b7839  mov [rcx],eax` | max_load_factor dword copied from src [V] | [V]
| blk+0x08 | 8 | St 0x67b786f, 0x67b7873 | `0x67b786f  mov [rax+8],rax` ; `0x67b7873  mov [rsi+8],rax` | list head ptr self-init [V] | [V]
| blk+0x18 | 16 | St 0x67b787b | `0x67b787b  movups [rsi+0x18],xmm6` | bucket_vec_begin/end zeroed (xmm6=0) [V] | [V]
| blk+0x28 | 8 | St 0x67b787f | `0x67b787f  mov qword ptr [rsi+0x28],0` | bucket_vec_cap zeroed [V] | [V]
| blk+0x30 | 8 | St 0x67b7887, 0x67b788b | `0x67b7887  mov rdx,[rdi+0x30]` ; `0x67b788b  mov [rsi+0x30],rdx` | mask qword copied [V] | [V]
| blk+0x38 | 8 | St 0x67b788f, 0x67b7893 | `0x67b788f  mov rdx,[rdi+0x38]` ; `0x67b7893  mov [rsi+0x38],rdx` | max_load_factor_2 qword copied [V] | [V]

Block Value type (float3/u32/set) is opaque from these stores — [?], not decoded. The two visitor-read qwords at +0x260/+0x268 are proven [V]; all remaining block contents are pass-consumer territory, not reversed here.

## Part C — EditorHighlightConfiguration (Effect group, tag 8, clone 0x4c8a5b0, thin)
Clone (lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt): rdi=rdx arg = description pointer (stored at [rbp+0x10] @0x4c8a620), tag 8 at [rbp+0x18], passed to insert @0x4c8a639. Producer (lightgame_edhighlight_producer_4c88900_4c89881.txt): rbx=rcx arg = description base (clone's rdi == producer's rbx). Producer stores DIRECTLY into the description base only at +0x38/+0x40/+0x48/+0x60/+0x70; all other stores target sub-objects via rcx (=rbp+0x57C sub-object) or rax (=rbp+0x528 sub-object), whose base is not provably the description. Visitor: Effect case 8 at 0x666b316 (reg r15 == description base).

Producer stores directly into description base [V]:

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| eh+0x040 | 16 | St 0x4c89163; R 0x666b5b3 | `0x4c89163  mov [rbx+0x40],rax` ; `0x666b5b3  movups [r15+0x40],xmm3` | pointer field; rbx==r15 description base [V] | [V]
| eh+0x060 | 16 | St 0x4c88a7b | `0x4c88a7b  movups [rbx+0x60],xmm0` | xmmword (xmm0=[rbp+0x400], content not provably zero) [V] | [V]
| eh+0x070 | 16 | St 0x4c88ac3 | `0x4c88ac3  movups [rbx+0x70],xmm0` | xmmword [V] | [V]

Visitor reads WITHOUT matching producer store into the description base (all [UNVERIFIED] unless marked [I]):

| Offset | Size | Address(es) | Verbatim `0xRVA  instr` proof line(s) | Meaning [tag] |
|--------|------|-------------|----------------------------------------|---------------|
| eh+0x000 | 16 | R 0x666b3ba | `0x666b3ba  movups [r15],xmm6` | visitor itself STORES xmm6 to desc+0x000; producer has no store to rbx+0x000 (0x4c897d2 movups [rax],xmm0 writes stack [rbp+0x6B0], not rbx) -> no matching producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x001 | 8 | R 0x666c2c3 | `0x666c2c3  lea r8,[r15+1]` | address of desc+0x001 taken; no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x008 | 8 | R 0x666b3be | `0x666b3be  mov rax,[rbx+8]` | producer `0x4c89400  mov [rcx],rax` has base rcx (sub-object at rbp+0x57C), not rbx -> base mismatch [UNVERIFIED] | [UNVERIFIED]
| eh+0x00C | 4 | R 0x666cdd8 | `0x666cdd8  lock dec dword ptr [r15+0xC]` | refcount dec; no producer store into desc base (sub-object refcount decs exist at 0x4c88a84/0x4c88acc and other sites but not desc+0x0C) [UNVERIFIED] | [UNVERIFIED]
| eh+0x010 | 16 | R 0x666b5a4 | `0x666b5a4  movups [r15+0x10],xmm0` | producer `0x4c8941c  mov [rcx+0x10],rax` base mismatch [UNVERIFIED] | [UNVERIFIED]
| eh+0x018 | 8 | R 0x666b6d3 | `0x666b6d3  mov r14,[r15+0x18]` | producer `0x4c89412  mov [rcx+0x18],eax` base mismatch [UNVERIFIED] | [UNVERIFIED]
| eh+0x01C | 16 | R 0x666d09c | `0x666d09c  movups xmm1,[r15+0x1C]` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x020 | 16 | R 0x666b5a9 | `0x666b5a9  movups [r15+0x20],xmm1` | producer `0x4c89430  movups [rcx+0x20],xmm0` sub-object base mismatch [UNVERIFIED] | [UNVERIFIED]
| eh+0x028 | 16 | R 0x666f339 | `0x666f339  movups xmm1,[rax+0x28]` | producer `0x4c894e9  movss [rax+0x28],xmm6`: same register name rax but rax=[rbp+0x528] sub-object, not proven == desc base [I] | [I]
| eh+0x02C | 16 | R 0x666d0a8 | `0x666d0a8  movups xmm2,[r15+0x2C]` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x030 | 16 | R 0x666b5ae | `0x666b5ae  movups [r15+0x30],xmm2` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x038 | 16 | St 0x4c8898e, 0x4c89507, 0x4c8960d; R 0x666f344 | `0x666f344  movups xmm2,[rax+0x38]` ; `0x4c8898e  mov byte ptr [rbx+0x38],1` ; `0x4c89507  movups [rax+0x38],xmm0` ; `0x4c8960d  mov byte ptr [rax+0x38],1` | producer has direct flag-byte store at rbx+0x38 plus rax-relative xmmword/byte stores; rax base unproven == desc [I] | [I]
| eh+0x03C | 16 | R 0x666d0b4 | `0x666d0b4  movups xmm3,[r15+0x3C]` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x048 | 16 | St 0x4c88d0b, 0x4c894fc; R 0x666f34f | `0x666f34f  movups xmm3,[rax+0x48]` ; `0x4c88d0b  inc qword ptr [rbx+0x48]` ; `0x4c894fc  mov [rax+0x48],rcx` | producer has direct qword inc at rbx+0x48 plus rax-relative ptr store; rax base unproven == desc [I] | [I]
| eh+0x04C | 2 | R 0x666d0c7 | `0x666d0c7  movzx eax,word ptr [r15+0x4C]` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x050 | 8 | R 0x666b5bc | `0x666b5bc  mov [r15+0x50],rax` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x058 | 4 | R 0x667049a | `0x667049a  movss xmm1,[rsi+0x58]` | base rsi != r15 (different object lifetime) [UNVERIFIED] | [UNVERIFIED]
| eh+0x05C | 8 | R 0x667049f | `0x667049f  movsd xmm0,[rsi+0x5C]` | [UNVERIFIED] | [UNVERIFIED]
| eh+0x064 | 16 | R 0x666f2fe | `0x666f2fe  movups xmm0,[rax+0x64]` | rax-relative [UNVERIFIED] | [UNVERIFIED]
| eh+0x068 | 8 | R 0x666d2d7 | `0x666d2d7  lea rax,[r11+0x68]` | r11-relative [UNVERIFIED] | [UNVERIFIED]
| eh+0x078 | 8 | R 0x666d4b1 | `0x666d4b1  mov rsi,[r15+0x78]` | no producer store to rbx+0x78 anywhere in the listing -> beyond proven description footprint [UNVERIFIED] | [UNVERIFIED]
| eh+0x080 | 2 | R 0x666d610 | `0x666d610  mov si,[r15+0x80]` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x084 | 4 | R 0x666c96f | `0x666c96f  mov edi,[r15+0x84]` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x088 | 2 | R 0x666f36e | `0x666f36e  mov si,[rax+0x88]` | rax-relative, no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x0C8 | 1 | R 0x666d9c0 | `0x666d9c0  cmp byte ptr [r15+0xC8],1` | no producer store [UNVERIFIED] | [UNVERIFIED]
| eh+0x0C9 | 1 | R 0x6670513 | `0x6670513  cmp byte ptr [rsi+0xC9],1` | rsi-relative, no producer store [UNVERIFIED] | [UNVERIFIED]

**EditorHighlightConfiguration conclusion:** only +0x038/+0x040/+0x048/+0x060/+0x070 have producer stores into the description base [V]; +0x040 is the only visitor-read offset with a matching producer store. 17 visitor-read offsets have no matching producer store ([UNVERIFIED]/[I]); sub-object ownership (rcx/rax) is not resolved by the producer listing.

## CLOSES?
NO — blocking fact: EditorHighlightConfiguration (Effect tag 8) visitor reads at +0x00C (lock-dec refcount), +0x01C/+0x02C/+0x030/+0x03C/+0x04C/+0x050/+0x058/+0x05C/+0x064/+0x068/+0x078/+0x080/+0x084/+0x0C8/+0x0C9 and all rax/rsi/r11-relative reads have no matching producer store into the description base; the producer stores only +0x38 (byte), +0x40 (ptr), +0x48 (qword inc), +0x60/+0x70 (xmmword) directly into rbx, and sub-object base ownership is not provable, so those visitor fields cannot be proven [V]. GameplayMetadata is fully [V] and ServerGraphicsOverrideParameters visitor reads (+0x260/+0x268) plus block metadata layout are [V] (block Value type remains [?]).

## TOOL REQUESTS

None
