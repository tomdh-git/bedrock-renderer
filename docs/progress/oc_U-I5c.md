## NEXT: ALL STEPS COMPLETE - Step 1: string RVAs listed; Step 2: key regions of 0x674a3a0 and 0x186e6a0 analyzed; Step 3: atlas/texture creation sites documented. FontTexture string corrected (0xF0BCA58 is binary data, not a string). No "FontTexture" string exists. No direct bgfx texture creation in font paths; glyph atlas texture bound at draw time via "GlyphTexture" uniform lookup.

# UNIT U-I5c: Text/font rendering: glyph atlas

## Step 1: String RVAs and Referencing Instructions

### Glyph-related strings
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xf53b313 | "GlyphHeight" | `0x674e06a  lea rdx,[0xF53B313]` | 0x674a3a0 (UI group extractor) |
| 0xf543686 | "GlyphSmoothRadius" | `0x674ddbe  lea rdx,[0xF543686]` | 0x674a3a0 (UI group extractor) |
| 0xf5aff69 | "FontGlyph" | `0x186f442  lea rax,[0xF5AFF69]` | 0x186e6a0 (font data reset) |
| 0xf5aff73 | "textures/ui/ErrorGlyph" | `0x27f77c2  lea rdx,[0xF5AFF73]` | 0x27f7550 |
| 0xf5aff73 | "textures/ui/ErrorGlyph" | `0x28eefc3  lea rdx,[0xF5AFF73]` | 0x28eec00 |
| 0xf5aff73 | "textures/ui/ErrorGlyph" | `0x4f7894d  lea rdx,[0xF5AFF73]` | 0x4f78830 |
| 0xf5aff8a | "textures/ui/WarningGlyph" | `0x4f788fc  lea rdx,[0xF5AFF8A]` | 0x4f78830 |
| 0xf5aff8a | "textures/ui/WarningGlyph" | `0x50d887b  lea rdx,[0xF5AFF8A]` | 0x50d7fa0 |
| 0xf5c6dd7 | "GlyphTexture" | `0x674dca3  lea rdx,[0xF5C6DD7]` | 0x674a3a0 (UI group extractor) |

### Font-related strings (key references)
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xf0bc570 | "DefaultFont" | `0xe830bc  lea rdx,[0xF0BC570]` | 0xe82e00 (font init) |
| 0xf0bc590 | "RuneFont" | `0xe8326b  lea rdx,[0xF0BC590]` | 0xe82e00 (font init) |
| 0xf0bc5b0 | "UIFont" | `0xe834d1  lea rdx,[0xF0BC5B0]` | 0xe82e00 (font init) |
| 0xf0bc5d0 | "UnicodeFont" | `0xe83680  lea rdx,[0xF0BC5D0]` | 0xe82e00 (font init) |
| 0xf0bc5f0 | "SmoothFontLatin" | `0xe837e8  lea rdx,[0xF0BC5F0]` | 0xe82e00 (font init) |
| 0xf5aff69 | "FontGlyph" | `0x186f442  lea rax,[0xF5AFF69]` | 0x186e6a0 (font data reset) |
| 0xf60bdde | "ClearAndResetFontData" | `0x187005b  lea rax,[0xF60BDDE]` | 0x186e6a0 (font data reset) |
| 0xf55cdd3 | "TerrainAtlas" | `0x186f731  lea rax,[0xF55CDD3]` | 0x186e6a0 (font data reset) |
| 0xf55cde0 | "ItemAtlas" | `0x186f7fc  lea rax,[0xF55CDE0]` | 0x186e6a0 (font data reset) |
| 0xf55cdea | "BlockThumbnailAtlas" | `0x186f996  lea rax,[0xF55CDEA]` | 0x186e6a0 (font data reset) |
| 0xf55ce42 | "AnimatedAtlas" | `0x186f8c7  lea rax,[0xF55CE42]` | 0x186e6a0 (font data reset) |

### FONT_TYPE permutation string
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xf7cc3c4 | "FONT_TYPE" | `0x674d2bf  lea rdx,[0xF7CC3C4]` | 0x674a3a0 (UI group extractor) |
| 0xf7cc3c4 | "FONT_TYPE" | `0x674d6be  lea rdx,[0xF7CC3C4]` | 0x674a3a0 (UI group extractor) |

### SDF/MSDF strings
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xf7c84ac | "--disableSDFonGPU" | `0x4fc6b3c` | 0x4fc6730 |
| 0xf7cbe53 | "MSDF" | `0x674d2c6  lea r8,[0xF7CBE53]` | 0x674a3a0 (UI group extractor) |
| 0xf7cbe53 | "MSDF" | `0x674d6c5  lea r8,[0xF7CBE53]` | 0x674a3a0 (UI group extractor) |

### Atlas-related strings (in font reset function)
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xf55cdd3 | "TerrainAtlas" | `0x186f731  lea rax,[0xF55CDD3]` | 0x186e6a0 |
| 0xf55cde0 | "ItemAtlas" | `0x186f7fc  lea rax,[0xF55CDE0]` | 0x186e6a0 |
| 0xf55cdea | "BlockThumbnailAtlas" | `0x186f996  lea rax,[0xF55CDEA]` | 0x186e6a0 |
| 0xf55ce42 | "AnimatedAtlas" | `0x186f8c7  lea rax,[0xF55CE42]` | 0x186e6a0 |

### GlyphAtlas
No string "GlyphAtlas" found in the binary.

---

**Two most relevant functions for Step 2:**
1. **0x674a3a0** (UI group extractor) - references GlyphHeight, GlyphSmoothRadius, GlyphTexture, FONT_TYPE, MSDF - directly handles SDF glyph uniforms and FONT_TYPE permutation
2. **0x186e6a0** (ClearAndResetFontData) - references FontGlyph, ClearAndResetFontData, TerrainAtlas, ItemAtlas, BlockThumbnailAtlas, AnimatedAtlas - handles font data and atlas reset

---

## Step 2: Key Region Analysis of Containing Functions

### Function 0x674a3a0 (UI group extractor) - Size 0x4C66 (~19KB, >1500 insns)
**Key regions around string references:**

#### Region 1: FONT_TYPE + MSDF permutation setup (0x674d250..0x674d350)
```
0x674d2bf  lea rdx,[0xF7CC3C4]                           ; "FONT_TYPE"
0x674d2c6  lea r8,[0xF7CBE53]                            ; "MSDF"
0x674d2cd  lea rcx,[rbp+0x5F0]                           
0x674d2d4  mov r15,rcx                                   
0x674d2d7  call 0xF2EA00                                 ; sub_f2ea00 - string concat/build
```
**Callee 0xF2EA00**: String concatenation function (takes "FONT_TYPE" + "MSDF" → builds "FONT_TYPEMSDF" or similar permutation key). Returns constructed string in rcx (rbp+0x5F0).

**Phase**: Builds FONT_TYPE permutation string for MSDF variant. Followed by multiple uniform descriptor setups (ALPHA_TEST, FONT_BITMAP, Bitmoji, Outline) each calling `0x7D7890` to register uniform bindings.

#### Region 2: GlyphTexture uniform registration (0x674dca3)
```
0x674dca3  lea rdx,[0xF5C6DD7]                           ; "GlyphTexture"
0x674dcaa  lea r12,[rbp+0xC10]                           
0x674dcb1  mov rcx,r12                                   
0x674dcb4  call 0x79580                                  ; sub_79580 - FNV-1a 64 hash
0x674dcb9  nop                                           
0x674dcba  mov rdx,[rbp+0xC20]                           
0x674dcc1  cmp qword ptr [rbp+0xC28],0x10                
0x674dcc9  jb short 0x674DCD2                            ; SSO vs heap string handling
0x674dccb  mov r12,[rbp+0xC10]                           
```
**Callee 0x79580**: FNV-1a 64 hash of "GlyphTexture" uniform name. Result used for uniform lookup in hash table.

**Pattern**: Hash uniform name → compare string (SSO/heap) → FNV hash loop (0x674dd17..0x674dd51) → store hash at `0x129FA178` → call `0x73150` (hash table insert/lookup) → call `0xE938D70` (cleanup) → jump to next uniform handler.

#### Region 3: GlyphSmoothRadius uniform registration (0x674ddbe)
```
0x674ddbe  lea rdx,[0xF543686]                           ; "GlyphSmoothRadius"
0x674ddc5  lea r12,[rbp+0xC10]                           
0x674ddcc  mov rcx,r12                                   
0x674ddcf  call 0x79580                                  ; FNV-1a hash
```
Identical pattern to GlyphTexture: hash → string compare → FNV loop → store hash at `0x129FA568` → `0x73150` → `0xE938D70`.

#### Region 4: GlyphHeight uniform registration (0x674e06a)
```
0x674e06a  lea rdx,[0xF53B313]                           ; "GlyphHeight"
0x674e071  lea r12,[rbp+0xC10]                           
0x674e078  mov rcx,r12                                   
0x674e07b  call 0x79580                                  ; FNV-1a hash
```
Identical pattern: hash → string compare → FNV loop → store hash at `0x129FA5C8` → `0x73150` → `0xE938D70`.

**Common registration flow for all three SDF glyph uniforms**:
1. Load uniform name string RVA into rdx
2. Call `0x79580` (FNV-1a 64 hash) with string buffer at rbp+0xC10
3. Handle SSO (short string optimization) vs heap-allocated string
4. Compute FNV-1a hash byte-by-byte (constant 0xCBF29CE484222325, prime 0x100000001B3)
5. Store resulting hash at a TLS/global location (e.g., `0x129FA178`, `0x129FA568`, `0x129FA5C8`)
6. Call `0x73150` (uniform hash table registration)
7. Call `0xE938D70` (cleanup)
8. Jump to shared handler at `0x674A4C3` / `0x674AAC7` / `0x674AAEC`

**Uniform registration helper 0x7D7890**: Called after each uniform descriptor block setup (e.g., at 0x674d37d, 0x674d493, 0x674d5a2). Iterates a vector of 0x40-byte records and calls `0xAA840` (hash table lookup) for each. This registers the uniform binding in the bgfx uniform system.

**Callees in order (key ones)**:
- `0xF2EA00` - string concatenation for permutation keys
- `0x79580` - FNV-1a 64 hash of uniform names
- `0x73150` - uniform hash table registration
- `0xE938D70` - cleanup
- `0x7D7890` - vector iteration + `0xAA840` hash lookup per element
- `0xAA840` - FNV hash table lookup (finds uniform binding record)
- `0xEEC6EC0` - string copy (used in 0xF2EA00)

---

### Function 0x186e6a0 (ClearAndResetFontData) - Size 0x1CB7 (~7KB, >1500 insns)
**Key regions around string references:**

#### Region 1: FontGlyph handling (0x186f442)
```
0x186f442  lea rax,[0xF5AFF69]                           ; "FontGlyph"
0x186f449  mov [rbp+0xC0],rax                            
0x186f450  mov qword ptr [rbp+0xC8],9                    
0x186f45b  mov [rsp+0x20],rsi                            
0x186f460  lea rdx,[rbp+0xC0]                            
0x186f467  lea rsi,[rbp+0x390]                           
0x186f46e  mov rcx,[rbp+0x628]                           
0x186f475  mov r8,rsi                                    
0x186f478  mov r9d,9                                     
0x186f47e  call 0x1870DE0                                ; sub_1870de0 - map/vector insert
```
**Callee 0x1870DE0**: Inserts "FontGlyph" key into a map/vector structure (likely the font resource registry). Preceded by cleanup of previous entry at rbp+0x370 (calls `0x2FE440` destroy + `0xE935700` release).

#### Region 2: ClearAndResetFontData string (0x187005b)
```
0x187005b  lea rax,[0xF60BDDE]                           ; "ClearAndResetFontData"
0x1870062  mov [rbp+0x1C0],rax                           
0x1870069  mov qword ptr [rbp+0x1C8],0x15                
0x1870074  mov [rsp+0x20],rsi                            
0x1870079  lea rdx,[rbp+0x1C0]                           
0x1870080  lea rsi,[rbp+0x438]                           
0x1870087  mov rcx,[rbp+0x628]                           
0x187008e  mov r8,rsi                                    
0x1870091  mov r9d,0x1D                                  
0x1870097  call 0x1870DE0                                ; sub_1870de0 - map/vector insert
```
Same pattern: registers "ClearAndResetFontData" as a resource/task name in the font system registry.

#### Region 3: Atlas resource registration (TerrainAtlas 0x186f731, ItemAtlas 0x186f7fc, BlockThumbnailAtlas 0x186f996, AnimatedAtlas 0x186f8c7)
Each follows identical pattern:
```
0x186f731  lea rax,[0xF55CDD3]                           ; "TerrainAtlas"
0x186f738  mov [rbp+0x100],rax                           
0x186f73f  mov qword ptr [rbp+0x108],0xC                 
...
0x186f74f  lea rdx,[rbp+0x100]                           
0x186f756  lea rsi,[rbp+0x530]                           
0x186f75d  mov rcx,[rbp+0x628]                           
0x186f764  mov r8,rsi                                    
0x186f767  mov r9d,6                                     
0x186f76d  call 0x1870DE0                                ; insert into registry
```
**Preceded by**: Allocator call via `[0xF99FFA0]` (sub_eea6040) with size 4/8/0x10, then initialization of allocated object (e.g., `mov dword ptr [rdi],1` for TerrainAtlas/ItemAtlas, `movaps xmm0,[0xF0FBCE0]` for AnimatedAtlas).

**Callee 0x1870DE0**: Resource registry insert. The `r9d` value (6, 9, 0x26, 8, etc.) appears to be a resource type/index enum.

**Allocator**: `[0xF99FFA0]` = `sub_eea6040` (global allocator vtable+8 → allocate). Called multiple times with different sizes (4, 8, 0x10, 0x18) for each atlas resource object.

**Resource objects created**:
- TerrainAtlas: 4-byte object, initialized with `dword=1`
- ItemAtlas: 4-byte object, initialized with `dword=1`  
- AnimatedAtlas: 0x10-byte object, initialized with `xmm0` from `0xF0FBCF0`
- BlockThumbnailAtlas: 4-byte object, initialized with `dword=6`
- BlockGraphics: 8-byte object, initialized with `dword=7` (0x600000007)
- ItemRenderer: 8-byte object, initialized with `dword=6` (0x700000006)
- DynamicTextures: 8-byte object, initialized with `dword=0x19` (0x900000001)
- ClearAndResetFontData: 4-byte object, initialized with `dword=0x2A`

---

## Step 3: Glyph Atlas Texture Creation/Update Sites

### Font Initialization Path (creates font objects + likely glyph atlas)

**Function 0xE82E00** (font init entry, size 0xDDA) → calls **0xE84070** for each font type:
- `0xE830CE` call 0xE84070 with "DefaultFont"
- `0xE83280` call 0xE84070 with "RuneFont"  
- `0xE834E5` call 0xE84070 with "UIFont"
- `0xE83694` call 0xE84070 with "UnicodeFont"
- `0xE837FC` call 0xE84070 with "SmoothFontLatin"

**Function 0xE84070** (font object creation, size 0xD38, 4 xrefs):
- Allocates font object via `[0xF99FFA0]` (allocator, 0x20 bytes + 0x38 bytes for two strings)
- Sets up vtable pointer `0xF09AA70` at allocated object
- Reads font data from `rbx+0x328` and `rbx+0x338` (font description pointers)
- Copies font name strings via `0xEEC6EC0`
- Allocates secondary object (0x38 bytes) via `[0xF99FFA0]`
- **Critical**: At `0xE84275` calls `[0xF99FFA0]` with size 0x38 for texture-related object
- Stores font name at `rbp-0x10` (from `0xF0BCA58` - likely "FontTexture" or similar)

**Font object structure** (inferred from 0xE84070):
- `+0x00`: vtable `0xF09AA70`
- `+0x10`: refcount (starts at 1)
- `+0x18..`: string data (SSO buffer)
- `+0x30`: pointer to font description (from `rbx+0x328`)
- `+0x38`: pointer to secondary data (from `rbx+0x338`)

**CORRECTION**: The value at `0xF0BCA58` (referenced at `0xE8425E  lea rax,[0xF0BCA58]`) is NOT a string. `rvastr.py` shows bytes `90 80 07 40 01` (binary data, likely a vtable pointer or function address). There is NO "FontTexture" string in the binary (searched via `xref.py str "FontTexture"` - no results).

### Glyph Atlas Texture Binding in UI Extractor

**Uniform "GlyphTexture" registration** at 0x674a3a0 (0x674dca3):
- Hash computed via `0x79580` (FNV-1a of "GlyphTexture")
- Registered via `0x73150` (uniform hash table)
- Later bound via `0x7D7890` → `0xAA840` (hash table lookup for binding record)

**Uniform "GlyphHeight" and "GlyphSmoothRadius"**: Same registration pattern.

**FONT_TYPE + MSDF permutation**: String concatenation via `0xF2EA00` creates permutation key (likely "FONT_TYPEMSDF" = 0xE84070 selects MSDF shader variant).

### Callers of Font Reset (atlas cleanup/recreation)

**Caller 1: 0x8F6919** (in 0x8F6810 - init step 1)
```
0x8F6912  mov rcx,rdi                                   
0x8F6915  mov [rbp],rdi                                 
0x8F6919  call 0x186E6A0                                ; ClearAndResetFontData
```
Context: During game initialization (initStep1), after allocating font resource object (0x78 bytes via `[0xF99FFA0]`). Stores result at `rsi+0x6A0`.

**Caller 2: 0x104237E** (in 0x1042320 - ServerLevelLoad)
```
0x1042378  mov rcx,rax                                   
0x104237B  mov rdx,rsi                                   
0x104237E  call 0x186E6A0                                ; ClearAndResetFontData
```
Context: During server level load (`ResourceLoadType::ServerLevelLoad` / `ServerLevelAssignResults`). Re-initializes font resources after level load.

### Texture Description Stores (visible in font init)

**Allocator `[0xF99FFA0]` = `sub_eea6040`** (global allocator vtable+8):
- Called at 0xE840D5 (size 0x20) - primary font object
- Called at 0xE84275 (size 0x38) - secondary texture object  
- Called at 0x8F68FB (size 0x78) - font resource container in init
- Called multiple times in 0x186E6A0 for each atlas resource (4, 8, 0x10, 0x18 bytes)

**Texture description stores in 0xE84070**:
- `0xE840FD  mov [rsi],rax` - vtable `0xF09AA70` at font object +0x00
- `0xE84104  lea rax,[rsi+0x10]` - SSO buffer at +0x10
- `0xE84288  mov [r12],rax` - stores secondary object pointer
- `0xE84244  mov [rbp+0x78],rax` - font name string pointer

### Atlas/Texture Creation Call Sites (from 0x186E6A0 callees)

**Callee analysis of 0x186E6A0** (`rdis callees 0x186e6a0`):
- `sub_75720` x1 - error handler
- `sub_2fe440` x35 - destroy/release (called before each registry insert)
- `sub_7709c0` x1 - thread naming ("Main Thread")
- `sub_772520` x1 - unknown
- `sub_9bc830` x28 - exception/error handler
- `sub_1870de0` x35 - **resource registry insert** (map/vector insert for each atlas/font resource)
- `sub_e935700` x35 - **resource release** (refcount decrement + destroy)
- `sub_eec6ec0` x1 - string copy

**Atlas resource creation sites in 0x186E6A0** (each preceded by allocator call + registry insert):

| Atlas Resource | Allocator Call RVA (size) | Init Pattern | Registry Insert (r9d) |
|---|---|---|---|
| FontGlyph | (cleanup only) | N/A | 9 |
| Localization | (cleanup only) | N/A | 4 |
| Tessellator | (cleanup only) | N/A | 0xB |
| ClientInstanceLoadResources | (cleanup only) | N/A | 0x17 |
| **TerrainAtlas** | `0x186F7BC` size=4 | `mov dword ptr [rdi],1` | 6 |
| **ItemAtlas** | `0x186F887` size=4 | `mov dword ptr [rdi],1` | 9 |
| **AnimatedAtlas** | `0x186F952` size=0x10 | `movaps xmm0,[0xF0FBCF0]` | 0x26 |
| **BlockThumbnailAtlas** | `0x186FA21` size=4 | `mov dword ptr [rdi],6` | 8 |
| **BlockGraphics** | `0x186FAEC` size=8 | `mov rcx,0x600000007` → `mov [rdi],rcx` | 0xA |
| **ItemRenderer** | `0x186FBBE` size=8 | `mov rbx,0x700000006` → `mov [rdi],rbx` | 0x18 |
| **DynamicTextures** | `0x186FC7B` size=4 | `mov dword ptr [rdi],6` | 0x19 |
| **ClearAndResetFontData** | `0x18700D1` size=4 | `mov dword ptr [rdi],0x2A` | 0x1D |
| **FinalizeLoad** | (no allocator call) | N/A (registry insert only) | 0x1E |

**Verbatim call sites for atlas resource allocation** (allocator `[0xF99FFA0]` = `sub_eea6040`):

```
; TerrainAtlas (size 4) at 0x186F7A9..0x186F7BC
0x186F7A9  mov rcx,[0x1233E1A8]
0x186F7B0  mov rax,[rcx]
0x186F7B3  mov rax,[rax+8]
0x186F7B7  mov edx,4
0x186F7BC  call qword ptr [0xF99FFA0]

; ItemAtlas (size 4) at 0x186F874..0x186F887
0x186F874  mov rcx,[0x1233E1A8]
0x186F87B  mov rax,[rcx]
0x186F87E  mov rax,[rax+8]
0x186F882  mov edx,4
0x186F887  call qword ptr [0xF99FFA0]

; AnimatedAtlas (size 0x10) at 0x186F93F..0x186F952
0x186F93F  mov rcx,[0x1233E1A8]
0x186F946  mov rax,[rcx]
0x186F949  mov rax,[rax+8]
0x186F94D  mov edx,0x10
0x186F952  call qword ptr [0xF99FFA0]

; BlockThumbnailAtlas (size 4) at 0x186FA0E..0x186FA21
0x186FA0E  mov rcx,[0x1233E1A8]
0x186FA15  mov rax,[rcx]
0x186FA18  mov rax,[rax+8]
0x186FA1C  mov edx,4
0x186FA21  call qword ptr [0xF99FFA0]

; BlockGraphics (size 8) at 0x186FAD9..0x186FAEC
0x186FAD9  mov rcx,[0x1233E1A8]
0x186FAE0  mov rax,[rcx]
0x186FAE3  mov rax,[rax+8]
0x186FAE7  mov edx,8
0x186FAEC  call qword ptr [0xF99FFA0]

; ItemRenderer (size 8) at 0x186FBAB..0x186FBBE
0x186FBAB  mov rcx,[0x1233E1A8]
0x186FBB2  mov rax,[rcx]
0x186FBB5  mov rax,[rax+8]
0x186FBB9  mov edx,8
0x186FBBE  call qword ptr [0xF99FFA0]

; DynamicTextures (size 4) at 0x186FC68..0x186FC7B
0x186FC68  mov rcx,[0x1233E1A8]
0x186FC6F  mov rax,[rcx]
0x186FC72  mov rax,[rax+8]
0x186FC76  mov edx,4
0x186FC7B  call qword ptr [0xF99FFA0]

; ClearAndResetFontData (size 4) at 0x18700BE..0x18700D1
0x18700BE  mov rcx,[0x1233E1A8]
0x18700C5  mov rax,[rcx]
0x18700C8  mov rax,[rax+8]
0x18700CC  mov edx,4
0x18700D1  call qword ptr [0xF99FFA0]

; FinalizeLoad: NO allocator call - only registry insert at 0x187014A
```

**No direct bgfx `createTexture` or `createDynamicTexture` calls found in 0x186E6A0 or 0xE84070**. The atlas resources appear to be registry entries (4-0x18 byte objects) that likely reference texture handles created elsewhere (possibly during resource pack loading via the material system). The glyph atlas texture handle is bound at draw time via the "GlyphTexture" uniform lookup (0x674A3A0 → 0x73150 → 0xAA840), but the texture creation site is not in the font init/reset paths analyzed here.

---

## Verification Summary

| Item | Status | Notes |
|---|---|---|
| GlyphHeight uniform | FOUND | 0x674E06A in 0x674A3A0, hash registered via 0x79580/0x73150 |
| GlyphSmoothRadius uniform | FOUND | 0x674DDBE in 0x674A3A0, same pattern |
| GlyphTexture uniform | FOUND | 0x674DCA3 in 0x674A3A0, same pattern |
| FONT_TYPE permutation | FOUND | 0x674D2BF/0x674D6BE, concatenated with MSDF via 0xF2EA00 |
| MSDF string | FOUND | 0x674D2C6/0x674D6C5 in 0x674A3A0 |
| Font init (DefaultFont, RuneFont, etc.) | FOUND | 0xE82E00 → 0xE84070 ×5 |
| Font reset (ClearAndResetFontData) | FOUND | 0x186E6A0, called at init (0x8F6919) and level load (0x104237E) |
| Atlas resources in font reset | FOUND | TerrainAtlas, ItemAtlas, AnimatedAtlas, BlockThumbnailAtlas, BlockGraphics, ItemRenderer, DynamicTextures, ClearAndResetFontData, FinalizeLoad |
| GlyphAtlas string | NOT FOUND | No "GlyphAtlas" string in binary |
| FontTexture string | NOT FOUND | 0xF0BCA58 is binary data (90 80 07 40 01), no "FontTexture" string exists |
| Glyph atlas texture creation | NOT IN FONT PATHS | No bgfx createTexture/createDynamicTexture calls in 0x186E6A0 or 0xE84070; atlas resources are registry entries (4-0x18 bytes), texture handle bound at draw time via "GlyphTexture" uniform |

---

## Gaps / Unverified

- [UNVERIFIED: 0x674A3A0] How the "GlyphTexture" uniform binding resolves to an actual bgfx texture handle (the hash table lookup 0xAA840 finds a binding record, but the texture handle source is not traced)
- [UNVERIFIED: 0x129FA178/0x129FA568/0x129FA5C8] TLS/global locations where uniform hashes are stored - need to confirm these are per-frame or persistent
- [UNVERIFIED: 0x7D7890] The vector being iterated (0x40-byte records) - need to confirm this is the per-draw uniform binding array
- [UNVERIFIED: 0xF2EA00] Exact permutation string format - "FONT_TYPE" + "MSDF" → "FONT_TYPE_MSDF" or "FONT_TYPEMSDF"?
- [UNVERIFIED: 0x73150] Uniform hash table registration - does it create new binding or find existing?
- [UNVERIFIED: 0x186E6A0] Atlas resource objects (TerrainAtlas, ItemAtlas, etc.) are registry entries only - where are their actual bgfx texture handles created? (likely in material/resource pack loading path)
- [UNVERIFIED: 0xE84070] Secondary 0x38-byte allocation at 0xE84275 - confirmed as font resource object, not a texture handle

---

## TOOL REQUESTS

- `uniform_binding_tracer.py` | input: uniform name hash (e.g., from 0x79580) → output: binding record + texture handle source | would trace from uniform hash registration (0x73150) through hash table lookup (0xAA840) to the actual bgfx texture handle
- `font_texture_creator.py` | input: 0xE84070 call site → output: texture creation call chain | would trace the secondary allocation at 0xE84275 to see if it calls bgfx createTexture or dynamic texture creation
- `atlas_resource_mapper.py` | input: atlas name strings in 0x186E6A0 → output: resource object layout + texture handle field | would map the allocated resource objects (TerrainAtlas, ItemAtlas, etc.) to their texture handle fields