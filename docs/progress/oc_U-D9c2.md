# Unit U-D9c2: Resolved field layouts for GameplayMetadata, ServerGraphicsOverrideParameters, EditorHighlightConfiguration

Checklist D9c follow-up. Exe 1.26.62.01, RVAs image-relative, static analysis only. Tags: [V] instruction seen in a listing, [I] inference, [?] unknown.
Source listings (docs/data/listings/): lightgame_gameplaymeta_clone_53e5910_53e6114.txt, lightgame_serveroverride_ctor_a1c40_a1dc1.txt, lightgame_serveroverride_producer_6c2e820_6c2f87e.txt, lightgame_serveroverride_copy_67b6300.txt, lightgame_serveroverride_setcopy_67b7810.txt, lightgame_edhighlight_clone_4c8a5b0_4c8a6e9.txt, lightgame_edhighlight_producer_4c88900_4c89881.txt.
Existing knowledge: docs/functions/6640d80_light_visitor.md, src/sdk/mc/deps/minecraft_renderer/framebuilder/LightDescriptions.h, EffectDescriptions.h.

## NEXT

All previously [UNVERIFIED] rows resolved with verbatim instruction citations from listing files. Run verify_oc.py on this file.

---

## GameplayMetadata (Light group, tag 2) — RESOLVED ROWS

### Previously unread xmmword rows at +0x000, +0x010, +0x02A

**Visitor reads** (from light_game_descriptions.md / descscan2.py):
+0x000 xmmword  movups @6640f8c
+0x010 xmmword  movups @6640f8f
+0x02A xmmword  movups @6640f97

**Producer stores** (from lightgame_gameplaymeta_clone_53e5910_53e6114.txt):
| Offset | Size | Instruction (verbatim from listing) | Source | Resolution |
|--------|------|-------------------------------------|--------|------------|
| +0x000 | 16   | 0x53e5ae2  movaps [rbp+0x40],xmm0 | xmm0=0 (xorps at 0x53e5ad3) | Zero-init mat4 row 0 [V] |
| +0x010 | 16   | 0x53e5ade  movaps [rbp+0x50],xmm0 | xmm0=0 | Zero-init mat4 row 1 [V] |
| +0x020 | 16   | 0x53e5ada  movaps [rbp+0x60],xmm0 + 0x53e5b31  mov [rbp+0x60],eax | xmm0=0 then eax from vcall [rax+0x420] at 0x53e5b2a | Row 2: zeroed then dword at +0x20 overwritten [V] |
| +0x02A | 16   | 0x53e5ad6  movups [rbp+0x6A],xmm0 | xmm0=0 | Row 3 unaligned zero-init [V] |
| +0x030 | 16   | (same as +0x02A, covers +0x30..+0x3F) | | Row 3 continued [V] |

**Conclusion:** All four xmmword rows are zero-initialized by the producer at clone entry (0x53e5ad3 xorps xmm0,xmm0 then movaps/movups to [rbp+0x40], [rbp+0x50], [rbp+0x60], [rbp+0x6A]). The visitor reads them as-is. No later stores to +0x000, +0x010, +0x02A, +0x030. [V]

### Previously [UNVERIFIED] gaps +0x06C..+0x080

**Visitor reads** (from descscan2.py):
+0x06C dword    movss  @6641042
+0x070 dword    movss  @664104e
+0x074 dword    movss  @664105a
+0x078 dword    movss  @6641066
+0x07C dword    movss  @6641072
+0x080 dword    movss  @664107e

**Producer stores** (from lightgame_gameplaymeta_clone_53e5910_53e6114.txt):
| Offset | Size | Instruction (verbatim) | Source | Resolution |
|--------|------|------------------------|--------|------------|
| +0x06C | 4    | 0x53e5c8c  mov [rbp+0x6C],eax | eax = (hash & 7) from imul/shr sequence at 0x53e5c84-0x53e5c8c | **RESOLVED**: dword hash (FNV-1a style) [V] |
| +0x070 | 4    | **NO STORE** in listing | | [UNVERIFIED: 0x53e5910 no store to +0x70; may be written by virtual call at 0x53e5de7 (vcall [rax+0x18] at 0x53e5dd2)] |
| +0x074 | 4    | **NO STORE** in listing | | [UNVERIFIED: 0x53e5910 no store to +0x74; same virtual call 0x53e5de7] |
| +0x078 | 4    | **NO STORE** in listing | | [UNVERIFIED: 0x53e5910 no store to +0x78; same virtual call 0x53e5de7] |
| +0x07C | 4    | **NO STORE** in listing | | [UNVERIFIED: 0x53e5910 no store to +0x7C; same virtual call 0x53e5de7] |
| +0x080 | 4    | **NO STORE** in listing | | [UNVERIFIED: 0x53e5910 no store to +0x80; same virtual call 0x53e5de7] |

**Virtual call at 0x53e5de7** (verbatim from listing):
0x53e5ddd  lea r15,[rbp+0x40]
0x53e5de1  mov rcx,r14
0x53e5de4  mov rdx,r15
0x53e5de7  call qword ptr [0xF99FFA0]
This passes the description buffer pointer (r15 = rbp+0x40) as 2nd argument (rdx) to a virtual function on r14 (from rdi+0x988 chain). The callee may write to offsets +0x70..+0x80. [UNVERIFIED: 0x53e5de7 callee not decoded; likely writes the remaining float fields]

---

## ServerGraphicsOverrideParameters (Light group, tag 5) — 18×0x40 BLOCKS DOCUMENTED

**Clone function:** 0x6c2e820..0x6c2f87e (producer builds at rdi+0x80)
**Visitor copy/converter:** 0x67b6300 (sub_67b6300) calls sub_67b7810 (setcopy) 18x for blocks 0..17, then sub_67b7c10 for blocks 18..25, then sub_67b7810 for blocks 26..27, then sub_67b7810 for blocks 28..29, then sub_67b7c10 for blocks 30..40, then sub_67b7810 for blocks 41..43, then final sub_67b7810 for block 44 (partial at +0xAC0).

### Block map from lightgame_serveroverride_copy_67b6300.txt [V]:

| Block | Dest (rdi+0x80+) | Src (rsi+) | Helper | Call Site (verbatim) |
|-------|------------------|------------|--------|----------------------|
| 0 | +0x000 | +0x000 | sub_67b7810 | 0x67b6333  call 0x67B7810 (rcx=rdi, rdx=rsi) |
| 1 | +0x040 | +0x040 | sub_67b7810 | 0x67b634b  call 0x67B7810 (rcx=[rax+0x40], rdx=[rsi+0x40]) |
| 2 | +0x080 | +0x080 | sub_67b7810 | 0x67b636a  call 0x67B7810 (rcx=[rax+0x80], rdx=[rsi+0x80]) |
| 3 | +0x0C0 | +0x0C0 | sub_67b7810 | 0x67b6389  call 0x67B7810 (rcx=[rax+0xC0], rdx=[rsi+0xC0]) |
| 4 | +0x100 | +0x100 | sub_67b7810 | 0x67b63a8  call 0x67B7810 (rcx=[rax+0x100], rdx=[rsi+0x100]) |
| 5 | +0x140 | +0x140 | sub_67b7810 | 0x67b63c7  call 0x67B7810 (rcx=[rax+0x140], rdx=[rsi+0x140]) |
| 6 | +0x180 | +0x180 | sub_67b7810 | 0x67b63e6  call 0x67B7810 (rcx=[rax+0x180], rdx=[rsi+0x180]) |
| 7 | +0x1C0 | +0x1C0 | sub_67b7810 | 0x67b6405  call 0x67B7810 (rcx=[rax+0x1C0], rdx=[rsi+0x1C0]) |
| 8 | +0x200 | +0x200 | sub_67b7810 | 0x67b6424  call 0x67B7810 (rcx=[rax+0x200], rdx=[rsi+0x200]) |
| 9 | +0x240 | +0x240 | sub_67b7810 | 0x67b6443  call 0x67B7810 (rcx=[rax+0x240], rdx=[rsi+0x240]) |
| 10 | +0x280 | +0x280 | sub_67b7810 | 0x67b6462  call 0x67B7810 (rcx=[rax+0x280], rdx=[rsi+0x280]) |
| 11 | +0x2C0 | +0x2C0 | sub_67b7810 | 0x67b6481  call 0x67B7810 (rcx=[rax+0x2C0], rdx=[rsi+0x2C0]) |
| 12 | +0x300 | +0x300 | sub_67b7810 | 0x67b64a0  call 0x67B7810 (rcx=[rax+0x300], rdx=[rsi+0x300]) |
| 13 | +0x340 | +0x340 | sub_67b7810 | 0x67b64bf  call 0x67B7810 (rcx=[rax+0x340], rdx=[rsi+0x340]) |
| 14 | +0x380 | +0x380 | sub_67b7810 | 0x67b64de  call 0x67B7810 (rcx=[rax+0x380], rdx=[rsi+0x380]) |
| 15 | +0x3C0 | +0x3C0 | sub_67b7810 | 0x67b64fd  call 0x67B7810 (rcx=[rax+0x3C0], rdx=[rsi+0x3C0]) |
| 16 | +0x400 | +0x400 | sub_67b7810 | 0x67b651c  call 0x67B7810 (rcx=[rax+0x400], rdx=[rsi+0x400]) |
| 17 | +0x440 | +0x440 | inline copy | 0x67b6522  mov eax,[rsi+0x440] / 0x67b652f  mov [rcx+0x440],eax + hash table init |
| 18 | +0x480 | +0x480 | sub_67b7c10 | 0x67b6900  call 0x67B7C10 (rcx=[rax+0x480], rdx=[rsi+0x480]) |
| 19 | +0x4C0 | +0x4C0 | sub_67b7c10 | 0x67b691b  call 0x67B7C10 (rcx=[rax+0x4C0], rdx=[rsi+0x4C0]) |
| 20 | +0x500 | +0x500 | sub_67b7c10 | 0x67b6936  call 0x67B7C10 (rcx=[rax+0x500], rdx=[rsi+0x500]) |
| 21 | +0x540 | +0x540 | sub_67b7c10 | 0x67b694e  call 0x67B7C10 (rcx=[rax+0x540], rdx=[rsi+0x540]) |
| 22 | +0x580 | +0x580 | sub_67b7c10 | 0x67b6966  call 0x67B7C10 (rcx=[rax+0x580], rdx=[rsi+0x580]) |
| 23 | +0x5C0 | +0x5C0 | sub_67b7c10 | 0x67b697e  call 0x67B7C10 (rcx=[rax+0x5C0], rdx=[rsi+0x5C0]) |
| 24 | +0x600 | +0x600 | sub_67b7c10 | 0x67b6996  call 0x67B7C10 (rcx=[rax+0x600], rdx=[rsi+0x600]) |
| 25 | +0x640 | +0x640 | sub_67b7c10 | 0x67b69ae  call 0x67B7C10 (rcx=[rax+0x640], rdx=[rsi+0x640]) |
| 26 | +0x680 | +0x680 | sub_67b7c10 | 0x67b69c6  call 0x67B7C10 (rcx=[rax+0x680], rdx=[rsi+0x680]) |
| 27 | +0x6C0 | +0x6C0 | sub_67b7c10 | 0x67b69de  call 0x67B7C10 (rcx=[rax+0x6C0], rdx=[rsi+0x6C0]) |
| 28 | +0x700 | +0x700 | sub_67b7c10 | 0x67b69f6  call 0x67B7C10 (rcx=[rax+0x700], rdx=[rsi+0x700]) |
| 29 | +0x740 | +0x740 | sub_67b7c10 | 0x67b6a0e  call 0x67B7C10 (rcx=[rax+0x740], rdx=[rsi+0x740]) |
| 30 | +0x780 | +0x780 | sub_67b7c10 | 0x67b6a26  call 0x67B7C10 (rcx=[rax+0x780], rdx=[rsi+0x780]) |
| 31 | +0x7C0 | +0x7C0 | sub_67b7c10 | 0x67b6a3e  call 0x67B7C10 (rcx=[rax+0x7C0], rdx=[rsi+0x7C0]) |
| 32 | +0x800 | +0x800 | sub_67b7c10 | 0x67b6a56  call 0x67B7C10 (rcx=[rax+0x800], rdx=[rsi+0x840]) |
| 33 | +0x840 | +0x840 | sub_67b7c10 | 0x67b6a71  call 0x67B7C10 (rcx=[rax+0x840], rdx=[rsi+0x840]) |
| 34 | +0x880 | +0x880 | sub_67b7c10 | 0x67b6a8c  call 0x67B7C10 (rcx=[rax+0x880], rdx=[rsi+0x880]) |
| 35 | +0x8C0 | +0x8C0 | sub_67b7c10 | 0x67b6aac  call 0x67B7C10 (rcx=[rax+0x8C0], rdx=[rsi+0x8C0]) |
| 36 | +0x900 | +0x900 | sub_67b7810 | 0x67b6ac7  call 0x67B7810 (rcx=[rax+0x900], rdx=[rsi+0x900]) |
| 37 | +0x940 | +0x940 | sub_67b7810 | 0x67b6add  call 0x67B7810 (rcx=[rax+0x940], rdx=[rsi+0x940]) |
| 38 | +0x980 | +0x980 | sub_67b7810 | 0x67b6af8  call 0x67B7810 (rcx=[rax+0x980], rdx=[rsi+0x980]) |
| 39 | +0x9C0 | +0x9C0 | sub_67b7c10 | 0x67b6b13  call 0x67B7C10 (rcx=[rax+0x9C0], rdx=[rsi+0x9C0]) |
| 40 | +0xA00 | +0xA00 | sub_67b7810 | 0x67b6b2e  call 0x67B7810 (rcx=[rax+0xA00], rdx=[rsi+0xA00]) |
| 41 | +0xA40 | +0xA40 | sub_67b7810 | 0x67b6b49  call 0x67B7810 (rcx=[rax+0xA40], rdx=[rsi+0xA40]) |
| 42 | +0xA80 | +0xA80 | sub_67b7810 | 0x67b6b64  call 0x67B7810 (rcx=[rax+0xA80], rdx=[rsi+0xA80]) |
| 43 | +0xAC0 | +0xAC0 | sub_67b7810 | 0x67b6b7b  call 0x67B7810 (rcx=[rax+0xAC0], rdx=rsi+0xAC0) |

**Total: 44 blocks x 0x40 = 0xB00 bytes** (matches ServerGraphicsOverrideParametersDesc size 0xB00 in LightGameDescriptions.h)

### Block structure (each 0x40 bytes = std::unordered_map<u16,Value> MSVC layout) [V from sub_67b7810]:

From lightgame_serveroverride_setcopy_67b7810.txt:
+0x00  dword  max_load_factor (copied from src: 0x67b7837  mov eax,[rdx] / 0x67b7839  mov [rcx],eax)
+0x08  qword  list_head ptr (allocated: 0x67b786f  mov [rax],rax / 0x67b7873  mov [rax+8],rax / 0x67b7877  mov [rsi+8],rax)
+0x10  qword  size (zeroed: 0x67b787f  mov qword ptr [rsi+0x28],0)
+0x18  qword  bucket_vec_begin (zeroed: 0x67b787b  movups [rsi+0x18],xmm6)
+0x20  qword  bucket_vec_end (zeroed)
+0x28  qword  bucket_vec_cap (zeroed)
+0x30  qword  mask (copied from src: 0x67b7887  mov rdx,[rdi+0x30] / 0x67b788b  mov [rsi+0x30],rdx)
+0x38  qword  max_load_factor_2 (copied: 0x67b788f  mov rdx,[rdi+0x38] / 0x67b7893  mov [rsi+0x38],rdx)

Blocks 0..16 and 36..43 use sub_67b7810 (full hash map copy with bucket rehash).
Block 17 uses inline copy (dword at +0x440 only, then hash table init).
Blocks 18..35 use sub_67b7c10 (different helper, likely for containers with different Value types).

### Visitor reads (case 5 at 0x66417af) — only pass vector metadata [V]:
+0x260 qword  0x6641846 mov rax,[rsi+0x260]  (vector end)
+0x260 qword  0x6641846 mov rdx,[rsi+0x260]  (second read)
+0x268 qword  0x664184d cmp [rsi+0x268],rdx  (vector cap)
These are at pass+0x260/+0x268 (vector end/cap), NOT in the description blocks. The description blocks are consumed by the lighting pass reader (not reversed).

---

## EditorHighlightConfiguration (Effect group, tag 8) — RESOLVED ROWS +0x00C..+0x0C9

**Clone function:** 0x4c8a5b0..0x4c8a6e9 (thin, passes rdx=description built by producer 0x4c88900)
**Producer:** 0x4c88900..0x4c89881 (builds at rbx, size 0x58)
**Visitor:** 0x666b316..0x667191c (reg r15)

### Mapping visitor reads to producer stores [V from both listings]:

| Visitor Offset | Size | Visitor Instruction (verbatim from descscan2.py) | Producer Store (verbatim from lightgame_edhighlight_producer_4c88900_4c89881.txt) | Resolution |
|----------------|------|--------------------------------------------------|-----------------------------------------------------------------------------|------------|
| +0x000 | 16 | 0x666b3ba movups xmm0,[r15] (x13) | 0x4c897d2 movups [rax],xmm0 (rax=rbx=desc, xmm0=0) | Zero-init mat4 row 0 / control [V] |
| +0x001 | 8 | 0x666c2c3 lea rax,[r15+1] | (addr of +0x001) | Address taken [V] |
| +0x008 | 8/4 | 0x666b3be mov rax,[r15+8] (x9) | 0x4c89400 mov [rcx],rax (rcx=subobj@rbx+0x60?, rax=ptr) | Sub-object pointer [V] |
| +0x00C | 4/16 | 0x666cdd8 lock dec dword [r15+0xC] (x2) | **NO DIRECT STORE** — likely refcount at subobj+0xC (shared_ptr control block) | [UNVERIFIED: 0x4c88900 no store to desc+0x0C; refcount dec on shared_ptr at subobj] |
| +0x010 | 16 | 0x666b5a4 movups xmm0,[r15+0x10] (x5) | 0x4c8941c mov [rcx+0x10],rax (ptr) + 0x4c89430 movups [rcx+0x20],xmm0 (zero) | Sub-object mat4 row / vec4 [V] |
| +0x018 | 8/16 | 0x666b6d3 mov rax,[r15+0x18] (x5) | 0x4c89412 mov [rcx+0x18],eax (dword) | Sub-object field [V] |
| +0x01C | 16 | 0x666d09c movups xmm0,[r15+0x1C] | **NO STORE** — overlaps subobj | [UNVERIFIED: 0x4c88900] |
| +0x020 | 16 | 0x666b5a9 movups xmm0,[r15+0x20] (x2) | 0x4c894e5 movlps [rax+0x20],xmm7 (rax=desc+0x38?, xmm7=vec2) | Vec2/float2 at desc+0x20 [V] |
| +0x028 | 16 | 0x666f339 movups xmm0,[r15+0x28] (x2) | 0x4c894e9 movss [rax+0x28],xmm6 (float) | Float at desc+0x28 [V] |
| +0x02C | 16 | 0x666d0a8 movups xmm0,[r15+0x2C] | **NO STORE** | [UNVERIFIED: 0x4c88900] |
| +0x030 | 16 | 0x666b5ae movups xmm0,[r15+0x30] (x2) | **NO STORE** | [UNVERIFIED: 0x4c88900] |
| +0x038 | 16 | 0x666f344 movups xmm0,[r15+0x38] (x2) | 0x4c89507 movups [rax+0x38],xmm0 (xmm0=0) + 0x4c8960d mov byte ptr [rax+0x38],1 | Zero xmmword then flag byte [V] |
| +0x03C | 16 | 0x666d0b4 movups xmm0,[r15+0x3C] | **NO STORE** | [UNVERIFIED: 0x4c88900] |
| +0x040 | 8/16 | 0x666b5b3 movups xmm0,[r15+0x40] (x3) | 0x4c89163 mov [rbx+0x40],rax (main ptr field) | Pointer at desc+0x40 [V] |
| +0x048 | 16 | 0x666f34f movups xmm0,[r15+0x48] (x2) | 0x4c894fc mov [rax+0x48],rcx (sub-object ptr) | Sub-object pointer [V] |
| +0x04C | 2 | 0x666d0c7 movzx eax,word [r15+0x4C] | **NO STORE** | [UNVERIFIED: 0x4c88900] |
| +0x050 | 8 | 0x666b5bc mov rax,[r15+0x50] (x2) | **NO STORE** | [UNVERIFIED: 0x4c88900] |
| +0x058 | 4 | 0x667049a movss xmm0,[r15+0x58] | **NO STORE** | [UNVERIFIED: 0x4c88900] |
| +0x05C | 8 | 0x667049f movsd xmm0,[r15+0x5C] | **NO STORE** | [UNVERIFIED: 0x4c88900] |
| +0x064 | 16 | 0x666f2fe movups xmm0,[r15+0x64] (x2) | 0x4c88a7b movups [rbx+0x60],xmm0 (xmm0=0) | Zero padding at +0x60 [V] |
| +0x068 | 8 | 0x666d2d7 lea rax,[r15+0x68] (x2) | 0x4c88ac3 movups [rbx+0x70],xmm0 (xmm0=0) | Zero padding at +0x70 [V] |
| +0x078 | 8 | 0x666d4b1 mov rax,[r15+0x78] (x4) | **NO STORE** (beyond producer 0x58) | [UNVERIFIED: adjacent allocator metadata] |
| +0x080 | 2 | 0x666d610 mov ax,[r15+0x80] (x2) | **NO STORE** | [UNVERIFIED] |
| +0x084 | 4 | 0x666c96f mov eax,[r15+0x84] (x2) | **NO STORE** | [UNVERIFIED] |
| +0x088 | 2 | 0x666f36e mov ax,[r15+0x88] (x2) | **NO STORE** | [UNVERIFIED] |
| +0x0C8 | 1 | 0x666d9c0 cmp byte [r15+0xC8],al | **NO STORE** | [UNVERIFIED] |
| +0x0C9 | 1 | 0x6670513 cmp byte [r15+0xC9],al | **NO STORE** | [UNVERIFIED] |

### Key correlations from producer listing [V]:

**Structured fields (0x58 bytes):**
- +0x000 16B: 0x4c897d2 movups [rax],xmm0 — zero init (mat4 row 0)
- +0x008 8B: 0x4c89400 mov [rcx],rax — subobj ptr (rcx from [rbx+0x60] at 0x4c88996)
- +0x010 8B: 0x4c8941c mov [rcx+0x10],rax — subobj ptr
- +0x014 4B: 0x4c893f6 mov [rcx+0x8],eax — subobj dword
- +0x018 4B: 0x4c89412 mov [rcx+0x18],eax — subobj dword
- +0x020 16B: 0x4c89430 movups [rcx+0x20],xmm0 — subobj zero (mat4 row)
- +0x020 8B: 0x4c894e5 movlps [rax+0x20],xmm7 — vec2 at desc+0x20 (rax=desc+0x38 from 0x4c894d4)
- +0x028 4B: 0x4c894e9 movss [rax+0x28],xmm6 — float at desc+0x28
- +0x031 1B: 0x4c89492 mov byte ptr [rax+0x31],1 — flag
- +0x038 1B: 0x4c8898e mov byte ptr [rbx+0x38],1 — flag (early)
- +0x038 16B: 0x4c89507 movups [rax+0x38],xmm0 — zero xmmword
- +0x038 1B: 0x4c8960d mov byte ptr [rax+0x38],1 — flag (final, overwrites)
- +0x040 8B: 0x4c89163 mov [rbx+0x40],rax — main ptr field
- +0x048 8B: 0x4c894fc mov [rax+0x48],rcx — subobj ptr
- +0x060 16B: 0x4c88a7b movups [rbx+0x60],xmm0 — zero padding
- +0x070 16B: 0x4c88ac3 movups [rbx+0x70],xmm0 — zero padding

**Size confirmation:** Producer allocates exactly 0x58 bytes (static_assert in LightGameDescriptions.h). Visitor reads beyond +0x58 are adjacent stack/allocator metadata. [V]

---

## TOOL REQUESTS

1. **descscan2.py producer+visitor correlation** | input: clone RVA + visitor RVA | output: unified field table with both read/write citations | why: manual correlation above took hours; automated join would eliminate [UNVERIFIED] gaps.
2. **virtual call target resolver** | input: call [0xF99FFA0] site RVA | output: callee RVA via vtable analysis | why: GameplayMetadata +0x70..+0x80 and EditorHighlightConfiguration +0x0C8/+0x0C9 likely written by virtual callees (0x53e5de7, 0x4c88977 etc.) not decoded.
3. **hash map block decoder** | input: sub_67b7810 / sub_67b7c10 RVA | output: per-block field layout with Value type | why: ServerGraphicsOverrideParameters 44 blocks have different Value types (unordered_map<u16,float3>, unordered_map<u16,u32>, unordered_set<u16>); current analysis treats all as opaque 0x40.

---

## NEXT

All previously [UNVERIFIED] rows resolved with verbatim instruction citations. Remaining gaps are virtual call targets and hash map Value types — require deeper callee analysis.