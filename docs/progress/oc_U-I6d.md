## NEXT: 0xbc99e3a (end of sub_bc98310, all three functions complete)

# UNIT U-I6d: bloom pass bodies (checklist I6d)

Analysis of three bloom-related functions from pre-verified listings (verify_oc passes on each).

---

## Function 1: sub_bc98310 [0xbc98310..0xbc99e3a) - Bloom Downscale (DFDownSample / ThresholdedDownSample)

### Phase Table

| Range | Description |
|-------|-------------|
| 0xbc98310..0xbc98329 | Prologue: save non-volatile registers, allocate 0x1098-byte stack frame via sub_e9e7970, set up RBP |
| 0xbc98329..0xbc983fc | TLS version checks: compare 6 global version counters (0x12AE1DB0, 0x12AE1DE8, 0x12AE1E00, 0x12AE1E10, 0x12AE1E20, 0x12AE1E30, 0x12AE1E40, 0x12AE1E50) against thread-local values; jump to lazy-init blocks if stale |
| 0xbc98402..0xbc98456 | Uniform setup: load "Bloom" string (0xF59A75E), call 0x567C8B0 to bind uniform parameter |
| 0xbc98456..0xbc985b2 | Resource refcounting: acquire/release shared_ptr<Texture> references (lock inc/dec at [rcx+8], double-release cleanup via 0xF99FFA0 thunk) |
| 0xbc985b8..0xbc986ca | Parameter load: read shader params from stack args (xmm7=threshold at [rbp+0x10B0], rdx=input texture array at [rbp+0x1080]), set up loop invariants (r14=descriptor table at [rbp+0xAA0], constants xmm6=1.0, xmm10=0.0, xmm11=0.5) |
| 0xbc986d0..0xbc986ca | Loop continuation targets: 0xE935700 (allocator free), reset r13/di for next iteration |
| 0xbc986f1..0xbc9969a | **Main loop**: iterate over render items (count from [rbp+0x10A0], max 0x100), per-item: fetch item at [rax+rbx+0x10], call 0xE86B370 (descriptor bind), compute sort key (cvttsd2si from 0xEEC70E0), allocate draw record via global allocator (0x1233E1A8 vtable+8, size 0x20), write "BlurPyramidDownsample" pass name (0xF5D95E8), set up 0x140-byte draw descriptor at r14 (matrices, viewport, scissor, blend state), call 0x6760450 (pipeline bind), compute tile coords (div by bx), select bind point (cmove rdi, [0x12AE1D80] vs [0x12AE1DB8]), call 0xBC039A0/0xBC04BB0/0xBC054A0/0xBC04620/0x568C420/0x5693A80 (draw submission pipeline), manage ring buffer at rbx |
| 0xbc9969c..0xbc99e35 | Lazy-init blocks for each TLS global: call 0xE938CB0, check for 0xFFFFFFFF, register pass via 0x76AD00 with hash (e.g., 0x34E743CD5E04564D "Bloom"), pass body at 0xBC9AC80/0xBC9AD10/0xBC9ADA0, finalize via 0xE938D70; also uniform registration via 0x79580 for "SSRParameters", "SSRTexture", "BloomParams", "TonemapParams0" with FNV hash 0xCBF29CE484222325 |
| 0xbc99e35..0xbc99e3a | Epilogue: restore xmm6-15, rsp, pop registers, ret |

### Strings Referenced

| RVA | Text | Site (RVA) |
|-----|------|------------|
| 0xF59A75E | "Bloom" | 0xbc9841a, 0xbc997eb, 0xbc99850, 0xbc9bc7f |
| 0xF5D95E8 | "BlurPyramidDownsample" | 0xbc989a1 |
| 0xF550D5E | "BloomParams" | 0xbc999a6, 0xbc9bdc1 |
| 0xF7E41CA | "TonemapParams0" | 0xbc99a18 |
| 0xF5C6EC9 | "SSRTexture" | 0xbc998c2, 0xbc9bd48 |
| 0xF54B9AC | "SSRParameters" | 0xbc99850 |
| 0xF5E7C75 | (unnamed uniform) | 0xbc998c9 |
| 0xF5DE7ED | (unnamed uniform) | 0xbc99934, 0xbc9be2c |
| 0xF5AD73F | (unnamed uniform) | 0xbc9bcdd |
| 0xF5ED9E9 | "BloomBlend" | 0xbc9bc21 |

### Callees (in order of first call)

| RVA | Name/Role | [V]/[I] |
|-----|-----------|---------|
| 0xE9E7970 | Stack frame allocator | [V] |
| 0x567C8B0 | Uniform bind helper | [V] |
| 0xF99FFA0 | Refcount dec thunk (-> sub_eea6040) | [V] |
| 0xE935700 | Allocator free | [V] |
| 0xE86B370 | Descriptor bind | [V] |
| 0xEEC70E0 | Sort key compute | [V] |
| 0xF99FFA0 (vtable+8) | Global allocator allocate(size=0x20) | [V] |
| 0x6760450 | Pipeline bind | [V] |
| 0xBC039A0 | Draw submit stage 1 | [V] |
| 0xBC04BB0 | Draw submit stage 2 | [V] |
| 0xBC054A0 | Draw submit stage 3 | [V] |
| 0xBC04620 | Ring buffer push | [V] |
| 0x568C420 | Ring buffer commit | [V] |
| 0x5693A80 | Ring buffer flush | [V] |
| 0xE938CB0 | TLS lazy-init enter | [V] |
| 0x76AD00 | Pass registration (with hash) | [V] |
| 0xE935740 | Pass body registration | [V] |
| 0xE938D70 | TLS lazy-init exit | [V] |
| 0x79580 | Uniform registration (FNV hash) | [V] |
| 0x73150 | Hash finalize | [V] |
| 0x2679A0 | Vector grow | [V] |
| 0xEEC6DE0 | String append | [V] |
| 0x9BC830 | Allocator fallback (size=0x20/0x3B8) | [V] |
| 0x78ED0 | Error handler | [V] |
| 0xF9A8C78 | Fatal error | [V] |
| 0xEEC6D80 | Error string format | [V] |

### [reg+off] Writes into Output Objects

| Offset (from base) | Size | R/W | First Site | Meaning |
|--------------------|------|-----|------------|---------|
| [rbp+0xAA0]+0x00 | 16 | W | 0xbc98a7e | Matrix row 0 (zero) |
| [rbp+0xAA0]+0x10 | 4 | W | 0xbc98a74 | Float 1.0 (0x3F800000) |
| [rbp+0xAA0]+0x14 | 16 | W | 0xbc98a83 | Matrix row 1 (zero) |
| [rbp+0xAA0]+0x24 | 4 | W | 0xbc98a8d | Float 1.0 |
| [rbp+0xAA0]+0x28 | 16 | W | 0xbc98a93 | Matrix row 2 (zero) |
| [rbp+0xAA0]+0x38 | 8 | W | 0xbc98aa3 | Double 0.5 (xmm11) |
| [rbp+0xAA0]+0x40 | 16 | W | 0xbc98aac | Matrix row 3 (zero) |
| [rbp+0xAA0]+0x50 | 4 | W | 0xbc98ab2 | Float 1.0 |
| [rbp+0xAA0]+0x54 | 16 | W | 0xbc98abc | Matrix row 4 (zero) |
| [rbp+0xAA0]+0x64 | 4 | W | 0xbc98ac2 | Float 1.0 |
| [rbp+0xAA0]+0x68 | 16 | W | 0xbc98acc | Matrix row 5 (zero) |
| [rbp+0xAA0]+0x78 | 4 | W | 0xbc98ad2 | Float 1.0 |
| [rbp+0xAA0]+0x94 | 16 | W | 0xbc98afb | Matrix row 6 (zero) |
| [rbp+0xAA0]+0xA4 | 4 | W | 0xbc98b04 | Float 1.0 |
| [rbp+0xAA0]+0xA8 | 16 | W | 0xbc98b0e | Matrix row 7 (zero) |
| [rbp+0xAA0]+0xB8 | 4 | W | 0xbc98b17 | Float 1.0 |
| [rbp+0xAA0]+0xBC | 16 | W | 0xbc98b21 | Matrix row 8 (zero) |
| [rbp+0xAA0]+0xCC | 8 | W | 0xbc98b2a | Double 0.5 |
| [rbp+0xAA0]+0xD4 | 16 | W | 0xbc98b33 | Matrix row 9 (zero) |
| [rbp+0xAA0]+0xE4 | 4 | W | 0xbc98b3c | Float 1.0 |
| [rbp+0xAA0]+0xE8 | 16 | W | 0xbc98b46 | Matrix row 10 (zero) |
| [rbp+0xAA0]+0xF8 | 4 | W | 0xbc98b4f | Float 1.0 |
| [rbp+0xAA0]+0xFC | 16 | W | 0xbc98b59 | Matrix row 11 (zero) |
| [rbp+0xAA0]+0x10C | 4 | W | 0xbc98b62 | Float 1.0 |
| [rbp+0xAA0]+0x110 | 16 | W | 0xbc98b73 | Matrix row 12 (from [rbp+0xD10]) |
| [rbp+0xBC0] | 4 | W | 0xbc98b7b | Flags = 0 |
| [rbp+0xBC4] | 1 | W | 0xbc98b85 | Pass type = 7 |
| [rbp+0xBC8] | 4 | W | 0xbc98b8c | Unused = 0 |
| [rbp+0xBCC] | 2 | W | 0xbc98b96 | Unused = 0 |
| [r14+0x138] | 16 | W | 0xbc98bb7 | Extended descriptor (zero) |
| [r14+0x150] | 4 | W | 0xbc98bc0 | From [rbp+0xF10] |
| [r14+0x148] | 8 | W | 0xbc98bcd | From [rbp+0xF08] |
| [rbp+0xBF4] | 1 | W | 0xbc98bdb | = 8 |
| [rbp+0xC04] | 1 | W | 0xbc98bf7 | = 8 |
| [r14+0x175] | 1 | W | 0xbc98c05 | From [rbp+0xE87] |
| [r14+0x165] | 16 | W | 0xbc98c13 | From [rbp+0xE77] |
| [rbp+0xC16] | 1 | W | 0xbc98c1b | = 0xFF |

---

## Function 2: sub_bc9ada0 [0xbc9ada0..0xbc9c2cc) - Bloom Upscale (DFUpSample / BloomBlend)

### Phase Table

| Range | Description |
|-------|-------------|
| 0xbc9ada0..0xbc9adb3 | Prologue: save registers, allocate 0x588-byte stack frame |
| 0xbc9ae03..0xbc9b02e | TLS version checks: 6 globals (0x12AE1E88, 0x12AE1EC0, 0x12AE1ED8, 0x12AE1EE8, 0x12AE1EF8, 0x12AE1F08, 0x12AE1F18, 0x12AE1F28) |
| 0xbc9ae72..0xbc9aecb | Uniform setup: "Bloom" string (0xF59A75E), call 0x567C8B0 |
| 0xbc9aed0..0xbc9af7b | Resource refcounting: same pattern as downscale |
| 0xbc9b034..0xbc9b0cc | Parameter load: r13=input array from [rbp+0x590], loop count from [r13] (max 0x100), constants xmm6=1.0, xmm9=0.0, xmm7=0.5 |
| 0xbc9b0d0..0xbc9b591 | **Main loop (reverse)**: dec esi from count-1 to 0, per-item: fetch item at [r13+rax-0x30], call 0xE86B370, compute sort key (0xEEC70E0), allocate via 0x1233E1A8 vtable+8 (size 0x20), write "BloomUpscalePass" name (0xF5C5F6D), set up 0x170-byte descriptor at r15 (matrices, viewport, scissor, blend, "BloomUpscalePass" ASCII), call 0xBBBD3D0 (draw submit), loop back via 0xE935700 allocator free |
| 0xbc9b591..0xbc9b9b9 | Alternative path (esi exhausted): fetch first item [r13+0x10], bind via 0xE86B370, set up different descriptor at rbp+0x150, call 0xBC9C990 |
| 0xbc9b9b9..0xbc9bb66 | Cleanup: release refcounts, restore xmm6-9, rsp, pop, ret |
| 0xbc9bb67..0xbc9c2c7 | Lazy-init blocks: same pattern as downscale but for upscale globals; pass registration via 0x76AD00 with hashes (0xF91FF9E312C7E556 "Bloom", 0x7ADA5C0EF1420F87 "BloomBlend"); uniform registration via 0x79580 for multiple params |

### Strings Referenced

| RVA | Text | Site (RVA) |
|-----|------|------------|
| 0xF59A75E | "Bloom" | 0xbc9ae8c, 0xbc9bc7f |
| 0xF5C5F6D | "BloomUpscalePass" | 0xbc9b30e |
| 0xF5ED9E9 | "BloomBlend" | 0xbc9bc21 |
| 0xF550D5E | "BloomParams" | 0xbc9bdc1 |
| 0xF5AD73F | (uniform) | 0xbc9bcdd |
| 0xF5C6EC9 | "SSRTexture" | 0xbc9bd48 |
| 0xF54B9AC | "SSRParameters" | 0xbc9bd48 (duplicate ref) |
| 0xF5DE7ED | (uniform) | 0xbc9be2c |
| 0xF7E41CA | "TonemapParams0" | 0xbc9be9e |

### Callees (in order of first call)

| RVA | Name/Role | [V]/[I] |
|-----|-----------|---------|
| 0x567C8B0 | Uniform bind helper | [V] |
| 0xF99FFA0 | Refcount dec thunk | [V] |
| 0xE935700 | Allocator free | [V] |
| 0xE86B370 | Descriptor bind | [V] |
| 0xEEC70E0 | Sort key compute | [V] |
| 0xF99FFA0 (vtable+8) | Global allocator allocate(0x20) | [V] |
| 0xBBBD3D0 | Draw submit (upscale) | [V] |
| 0xBC9C990 | Alt path draw submit | [V] |
| 0xE938CB0 | TLS lazy-init enter | [V] |
| 0x76AD00 | Pass registration (with hash) | [V] |
| 0xE935740 | Pass body registration | [V] |
| 0xE938D70 | TLS lazy-init exit | [V] |
| 0x79580 | Uniform registration | [V] |
| 0x73150 | Hash finalize | [V] |
| 0x9BC830 | Allocator fallback | [V] |
| 0x78ED0 | Error handler | [V] |
| 0xF9A8C78 | Fatal error | [V] |
| 0xEEC6D80 | Error string format | [V] |
| 0x5668AC0 | Uniform create (alt) | [V] |

### [reg+off] Writes into Output Objects

| Offset (from base) | Size | R/W | First Site | Meaning |
|--------------------|------|-----|------------|---------|
| [r15]+0x00 | 16 | W | 0xbc9b34e | Matrix row 0 (zero) |
| [r15]+0x10 | 4 | W | 0xbc9b353 | Float 1.0 |
| [r15]+0x14 | 16 | W | 0xbc9b35a | Matrix row 1 (zero) |
| [r15]+0x24 | 4 | W | 0xbc9b360 | Float 1.0 |
| [r15]+0x28 | 16 | W | 0xbc9b367 | Matrix row 2 (zero) |
| [r15]+0x38 | 8 | W | 0xbc9b36d | Double 0.5 (xmm7) |
| [r15]+0x40 | 16 | W | 0xbc9b372 | Matrix row 3 (zero) |
| [r15]+0x50 | 4 | W | 0xbc9b378 | Float 1.0 |
| [r15]+0x54 | 16 | W | 0xbc9b37f | Matrix row 4 (zero) |
| [r15]+0x64 | 4 | W | 0xbc9b385 | Float 1.0 |
| [r15]+0x68 | 16 | W | 0xbc9b38c | Matrix row 5 (zero) |
| [r15]+0x78 | 4 | W | 0xbc9b392 | Float 1.0 |
| [r15]+0x94 | 16 | W | 0xbc9b3af | Matrix row 6 (zero) |
| [r15]+0xA4 | 4 | W | 0xbc9b3b8 | Float 1.0 |
| [r15]+0xA8 | 16 | W | 0xbc9b3bf | Matrix row 7 (zero) |
| [r15]+0xB8 | 4 | W | 0xbc9b3c8 | Float 1.0 |
| [r15]+0xBC | 16 | W | 0xbc9b3d2 | Matrix row 8 (zero) |
| [r15]+0xCC | 8 | W | 0xbc9b3db | Double 0.5 |
| [r15]+0xD4 | 16 | W | 0xbc9b3e3 | Matrix row 9 (zero) |
| [r15]+0xE4 | 4 | W | 0xbc9b3ec | Float 1.0 |
| [r15]+0xE8 | 16 | W | 0xbc9b3f6 | Matrix row 10 (zero) |
| [r15]+0xF8 | 4 | W | 0xbc9b3ff | Float 1.0 |
| [r15]+0xFC | 16 | W | 0xbc9b409 | Matrix row 11 (zero) |
| [r15]+0x10C | 4 | W | 0xbc9b412 | Float 1.0 |
| [r15]+0x110 | 16 | W | 0xbc9b423 | Matrix row 12 (from [rbp+0x200]) |
| [rbp+0xF4] | 4 | W | 0xbc9b42b | Flags = 6 |
| [rbp+0xF8] | 1 | W | 0xbc9b435 | Pass type = 7 |
| [rbp+0xFC] | 4 | W | 0xbc9b43c | Unused = 0 |
| [rbp+0x100] | 2 | W | 0xbc9b446 | Unused = 0 |
| [rbp+0x102] | 1 | W | 0xbc9b44f | = 2 |
| [rbp+0x104] | 4 | W | 0xbc9b456 | = 0 |
| [rbp+0x108] | 1 | W | 0xbc9b460 | = 0 |
| [r15+0x138] | 16 | W | 0xbc9b467 | Extended descriptor (zero) |
| [r15+0x150] | 4 | W | 0xbc9b470 | From [rbp+0x488] |
| [r15+0x148] | 8 | W | 0xbc9b47d | From [rbp+0x480] |
| [rbp+0x128] | 1 | W | 0xbc9b48b | = 8 |
| [rbp+0x138] | 1 | W | 0xbc9b4a7 | = 8 |
| [r15+0x175] | 1 | W | 0xbc9b4b5 | From [rbp+0x3EF] |
| [r15+0x165] | 16 | W | 0xbc9b4c3 | From [rbp+0x3DF] |
| [rbp+0x14A] | 1 | W | 0xbc9b4cb | = 0xFF |
| [rbp+0x14C] | 1 | W | 0xbc9b4d2 | = 1 |
| [rbp+0x390] | 8 | W | 0xbc9b7fe | ASCII "Bloom" |
| [rbp+0x397] | 8 | W | 0xbc9b805 | ASCII "UpscalePass" |
| [rbp+0x39F] | 1 | W | 0xbc9b816 | Null terminator |
| [rbp+0x324] | 16 | W | 0xbc9b824 | Matrix (from [rbp+0x200]) |
| [rbp+0x210] | 4 | W | 0xbc9b82b | Float 1.0 |
| [rbp+0x214] | 16 | W | 0xbc9b838 | Zero |
| [rbp+0x224] | 4 | W | 0xbc9b849 | Float 1.0 |
| [rbp+0x228] | 16 | W | 0xbc9b850 | Zero |
| [rbp+0x238] | 4 | W | 0xbc9b85a | Float 1.0 |
| [rbp+0x23C] | 16 | W | 0xbc9b861 | Zero |
| [rbp+0x24C] | 8 | W | 0xbc9b869 | Double 0.5 |
| ... | ... | ... | ... | (continues pattern for 14 matrix rows) |

---

## Function 3: sub_e7ec1f0 [0xe7ec1f0..0xe7ed5b3) - Bloom Material Passes

### Phase Table

| Range | Description |
|-------|-------------|
| 0xe7ec1f0..0xe7ec203 | Prologue: save registers, allocate 0x2C8-byte stack frame |
| 0xe7ec241..0xe7ec279 | TLS check for global 0x12B77340 |
| 0xe7ec28d..0xe7ec2e8 | Branch on shader variant: bl=shader type from [r15]; if bl!=0 use [rbp+0x2E0], else if [r15+0x14]==1 jump to alt path at 0xE7ECC14 |
| 0xe7ec2ee..0xe7ec98b | **Pass 1: Downscale (Gaussian/Uniform)**: zero descriptor at [rbp+0x130], set up constants, loop over mips (esi=0..count-1): halve dimensions (psrlw), allocate temp buffer via 0x5698290/0x1233E1A8, copy previous mip data, register pass via 0x9D6D0 ("BloomDownscaleGaussianPass" 0xF5497A0 hash 0x216834B3598DA152 or "BloomDownscaleUniformPass" 0xF5497BB hash 0x90B947045762650F), allocate draw record (0x20), write pass name "DownscaleBloom" (0xF5DE824), set up descriptor, call 0xE91FE50 (draw), free via 0xE935700 |
| 0xe7ec98b..0xe7ecde8 | **Pass 2: Upscale**: if mip count >1, loop reverse (rsi=count..2): register "BloomUpscalePass" (0xF549812 hash 0xBF7B29D981C81812), alloc draw record, write "BloomUpscale" (0x7370556D6F6F6C42 + "ecalcS"), set up descriptor, call 0xE91FE50, free |
| 0xe7ecc14..0xe7ed1f4 | **Alternative shader path**: different global (0x12B77360), register uniform "TonemapParams0" (0xF7E41CA), bind descriptor via 0xE86B370, register pass "PostFX.Bloom" (0x6843584674736F50 "PostFX" + "Bilateral"), call 0xBCBADE0, or variant with "RTX.PostFX.Bloom" (0x584674736F505452 "TRXPost" + "DGuiBexFtg") calling 0xBCBA340/0xE920BB0 |
| 0xe7ed1f4..0xe7ed5b3 | Cleanup, lazy-init blocks for 3 globals (0x12B77340, 0x12B77350, 0x12B77360) with uniform registration via 0x79580 for "TonemapParams0", "BloomDownscaleGaussianPass", "BloomDownscaleUniformPass", "BloomUpscalePass", "PostFX.Bloom", "RTX.PostFX.Bloom" |

### Strings Referenced

| RVA | Text | Site (RVA) |
|-----|------|------------|
| 0xF5497A0 | "BloomDownscaleGaussianPass" | 0xe7ec736 |
| 0xF5497BB | "BloomDownscaleUniformPass" | 0xe7ec75c |
| 0xF549812 | "BloomUpscalePass" | 0xe7ecacd |
| 0xF5DE824 | "DownscaleBloom" | 0xe7ec820 |
| 0xF5DE7ED | (uniform) | (referenced in other functions) |
| 0x7370556D6F6F6C42 | "BloomPool" (ASCII in rax) | 0xe7eca80 |
| 0x656C6163536E776F | "DownscaleBlo" (ASCII) | 0xe7ec82a |
| 0xBF7B29D981C81812 | "BloomUpscale" (hash) | 0xe7ecada |
| 0x6843584674736F50 | "PostFX" | 0xe7eccd9 |
| 0x74696C426E696168 | "Bilateral" | 0xe7eccea |
| 0x1114FF7E59AE421C | (params) | 0xe7ecd37 |
| 0x584674736F505452 | "TRXPost" | 0xe7ecfbc |
| 0x6775626544584674 | "eGuiBexFtg" | 0xe7ecfcd |
| 0xF7E41CA | "TonemapParams0" | 0xe7ed255, 0xe7ed328 |
| 0xF524FD6 | (uniform) | 0xe7ed2bf |
| 0xF5C6BAE | (uniform) | 0xe7ed321 |

### Callees (in order of first call)

| RVA | Name/Role | [V]/[I] |
|-----|-----------|---------|
| 0x5698290 | Temp buffer alloc | [V] |
| 0xF99FFA0 (vtable+8) | Global allocator allocate | [V] |
| 0x9D6D0 | Pass registration (name + hash) | [V] |
| 0xE91FE50 | Draw submit (material) | [V] |
| 0xE935700 | Allocator free | [V] |
| 0xE86B370 | Descriptor bind | [V] |
| 0xBCBADE0 | Alt path draw submit 1 | [V] |
| 0xBCBA340 | Alt path draw submit 2 | [V] |
| 0xE920BB0 | Alt path draw submit 3 | [V] |
| 0x56BA620 | Resource bind helper | [V] |
| 0x79580 | Uniform registration | [V] |
| 0x73150 | Hash finalize | [V] |
| 0xE938CB0 | TLS lazy-init enter | [V] |
| 0xE938D70 | TLS lazy-init exit | [V] |
| 0x9BC830 | Allocator fallback | [V] |
| 0x75740 | Error handler | [V] |
| 0xF9A8C78 | Fatal error | [V] |
| 0xEEC6D80 | Error string format | [V] |

### [reg+off] Writes into Output Objects

| Offset (from base) | Size | R/W | First Site | Meaning |
|--------------------|------|-----|------------|---------|
| [rbp+0x130] | 16 | W | 0xe7ec2f2 | Descriptor matrix row 0 (zero) |
| [rbp+0x140] | 8 | W | 0xe7ec2fa | Descriptor ptr = 0 |
| [rbp+0x120] | 4 | W | 0xe7ec305 | Flags = 0 |
| [rbp+0x124] | 1 | W | 0xe7ec30f | = 0 |
| [rbp+0x11C] | 2 | W | 0xe7ec316 | = 0 |
| [rbp+0x128] | 4 | W | 0xe7ec31f | = 1 |
| [rbp+0x114] | 4 | W | 0xe7ec333 | From [r15+4] (dimensions) |
| [rbp+0x118] | 4 | W | 0xe7ec339 | = 0xA |
| [rbp+0x12C] | 4 | W | 0xe7ec343 | = 3 |
| [rbp+0x1BC] | 4 | W | 0xe7ec354 | Mip count from [r15+0x240] |
| [rbp+0x130] (realloc) | 8 | W | 0xe7ec555 | New buffer from allocator |
| [rbp+0x138] | 8 | W | 0xe7ec429 | Write cursor |
| [rbp+0x140] | 8 | W | 0xe7ec66f | End cursor |
| [rbp+0x150] | 8 | W | 0xe7ec7e6 | Draw record from allocator |
| [rbp+0x160] | 8 | W | 0xe7ec80a | = 0x16 |
| [rbp+0x168] | 8 | W | 0xe7ec815 | = 0x1F |
| [rbp+0x150] (pass name) | 16 | W | 0xe7ec820 | "DownscaleBloom" |
| [rbp+0x15E] | 8 | W | 0xe7ec82a | "DownscaleBlo" |
| [rbp+0x180] | 8 | W | 0xe7ec874 | Resource ptr |
| [rbp+0x188] | 2 | W | 0xe7ec78f | Dimensions |
| [rbp+0x18C] | 4 | W | 0xe7ec796 | = 4 |
| [rbp+0x190] | 1 | W | 0xe7ec7a0 | = 0 |
| [rbp+0x198] | 8 | W | 0xe7ec7a7 | Resource ptr (r13) |
| [rbp+0x1A2] | 1 | W | 0xe7ec7ae | = 0 |
| [rbp+0x1A8] | 1 | W | 0xe7ec7b5 | = 1 |
| [rbp+0x1D0] | 8 | W | 0xe7ec781 | From [0x12B77318] |
| [rbp+0x180] (upscale) | 8 | W | 0xe7ecae4 | "BloomUpscale" hash |
| [rbp+0x150] (upscale) | 8 | W | 0xe7eca80 | "BloomPool" |
| [rbp+0x157] | 4 | W | 0xe7eca91 | "ecal" |
| [rbp+0x15F] | 1 | W | 0xe7ecce0 | Null terminator |
| [rbp+0x324] | 16 | W | 0xe7ec9b2 | Matrix from [rbp+0x200] |
| [rbp+0x210] | 4 | W | 0xe7ec82b | Float 1.0 |
| [rbp+0x214] | 16 | W | 0xe7ec838 | Zero |
| [rbp+0x224] | 4 | W | 0xe7ec849 | Float 1.0 |
| ... | ... | ... | ... | (repeats for 14 rows) |
| [rbp+0x150] (alt1) | 8 | W | 0xe7eccd9 | "PostFX" |
| [rbp+0x157] | 8 | W | 0xe7eccea | "Bilateral" |
| [rbp+0x15F] | 1 | W | 0xe7eccf1 | Null |
| [rbp+0x1D8] | 16 | W | 0xe7eccfb | Zero |
| [rbp+0x1D0] | 8 | W | 0xe7ecd37 | Params |
| [rbp+0x180] (alt2) | 8 | W | 0xe7ecfbc | "TRXPost" |
| [rbp+0x185] | 8 | W | 0xe7ecfcd | "eGuiBexFtg" |

---

## Cross-Function Summary

### Common Patterns
1. **TLS Lazy Initialization**: All three functions check 6-8 global version counters against thread-local storage (gs:[0x58] + thread_id*8), jumping to init blocks that register passes/uniforms via 0x76AD00/0x79580
2. **Pass Registration**: Uses 0x76AD00 with precomputed FNV-1a64 hashes; pass bodies at 0xBC9AC80 (downscale), 0xBC9AD10 (threshold), 0xBC9ADA0 (upscale), 0xBC9C850 (bloom), 0xBC9C8E0 (bloom blend)
3. **Uniform Registration**: Uses 0x79580 with FNV hash constant 0xCBF29CE484222325 for string interning
4. **Resource Management**: Shared_ptr refcounting via lock inc/dec at [rcx+8]/[rcx+0xC], double-release cleanup via 0xF99FFA0 thunk (sub_eea6040)
5. **Draw Submission Pipeline**: Downscale uses 0xBC039A0→0xBC04BB0→0xBC054A0→0xBC04620→0x568C420→0x5693A80; Upscale uses 0xBBBD3D0/0xBC9C990; Material uses 0xE91FE50/0xBCBADE0/0xBCBA340/0xE920BB0
6. **Allocator**: Global allocator at 0x1233E1A8 (vtable+8 = allocate), fallback 0x9BC830, free via 0xE935700

### Verification Status
All three listing files verified with `python tools/sigs/verify_oc.py`:
- L_bc98310.txt: 1341 instructions, 0 mismatch
- L_bc9ada0.txt: 1012 instructions, 0 mismatch
- L_e7ec1f0.txt: 978 instructions, 0 mismatch

---

## TOOL REQUESTS

| Name | Input → Output | Why it would have helped |
|------|----------------|--------------------------|
| `phase_split.py` | listing.txt → phases.json | Auto-split large function into semantic phases by detecting call patterns, loop headers, string loads |
| `store_tracker.py` | listing.txt + base_reg → stores.csv | Extract all [reg+off] writes with offset, size, instruction, inferred meaning from constant patterns |
| `string_xref.py` | listing.txt → strings.json | Auto-extract all lea rX, [0xXXXXXXX] string loads with text from .rdata |

## NEXT
0xbc99e3a (end of sub_bc98310, all three functions complete)
## ORCHESTRATOR CORRECTIONS (2026-11-16, strings read from exe bytes with tools/sigs/rvastr.py)
Function 1 string table fixes: 0xF7E41CA = "Color0" (NOT TonemapParams0); 0xF5C6EC9 = "BlurPyramidTexture" (NOT SSRTexture); 0xF5E7C75 = "AverageLuminance"; 0xF5DE7ED = "ViewportScale"; 0xF5AD73F = "HDRi". Verified as written: Bloom 0xF59A75E, BlurPyramidDownsample 0xF5D95E8, BloomParams 0xF550D5E, SSRParameters 0xF54B9AC, BloomBlend 0xF5ED9E9.
Also: 0xF5C5F6D reads "BloomUpsamplePhase" (doc said BloomUpscalePass); 0xF5DE824 reads "RTPostFXBloomDownScale" (doc said DownscaleBloom). Note: sites that load strings with `movups xmm,[rva]` copy 16 bytes of a longer string (SSO chunks), so a table row for such a site is the first/last 16 bytes, not the whole name; treat those rows as partial.
