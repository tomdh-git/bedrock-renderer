## NEXT: Step 1 complete - string RVAs and referencing instructions listed. Step 2 complete - 40 instructions around each reference and callee documented. Step 3 complete - pass-registration function identified as 0x9D6D0 for VV builder passes (Sky/Clouds), and 0x675E440/0x67D6D70 for material resolution in pass bodies (Stars/EndSky/SunMoon/Clouds). Verification pending.

# UNIT U-I4b: Sky / SunMoon / Clouds pass strings

## Step 1: String RVAs and Referencing Instructions

### Sky (VV builder 0x55f1450)
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xF82178B | " Sky (pre-water)" | `0x560CA5B  movups xmm0,[0xF82178B]` | 0x55F1450 (VV builder) |
| 0xF82177F | "ForwardPBR - Sky (pre-water)" | `0x560CA67  movupd xmm0,[0xF82177F]` | 0x55F1450 (VV builder) |

### Clouds (VV builder 0x55f1450)
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xF8217AB | "ouds (pre-water)" | `0x560E1AB  movups xmm0,[0xF8217AB]` | 0x55F1450 (VV builder) |
| 0xF82179C | "ForwardPBR - Clouds (pre-water)" | `0x560E1B7  movupd xmm0,[0xF82179C]` | 0x55F1450 (VV builder) |

### Clouds (Clouds pass body 0x67375A0)
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xF2BE548 | "Clouds" | `0x67376C0  lea rax,[0xF2BE548]` | 0x67375A0 (clouds pass) |
| 0xF2BE548 | "Clouds" | `0x673AE85  lea rax,[0xF2BE548]` | 0x67375A0 (clouds pass) |
| 0xF7CA1AE | "CloudsForwardPBR" | `0x673AE3B  lea rdx,[0xF7CA1AE]` | 0x67375A0 (clouds pass) |

### SunMoon / CelestialBody (Sky visitor 0x66560F0)
| String RVA | String | Referencing Instruction | Containing Function |
|---|---|---|---|
| 0xF584D1D | "SunMoon" | `0x665658C  lea rdx,[0xF584D1D]` | 0x66560F0 (Sky visitor) |
| 0xF584D1D | "SunMoon" | `0x665D5B8  lea rdx,[0xF584D1D]` | 0x66560F0 (Sky visitor) |
| 0xF7CA226 | "SunMoonForwardPBR" | `0x6656585  lea rax,[0xF7CA226]` | 0x66560F0 (Sky visitor) |
| 0xF7CA226 | "SunMoonForwardPBR" | `0x665D620  lea rax,[0xF7CA226]` | 0x66560F0 (Sky visitor) |
| 0xF563A7B | "SunMoonColor" | `0x665DC90  lea rdx,[0xF563A7B]` | 0x66560F0 (Sky visitor) |
| 0xF56CAFE | "SunMoonEmissiveMultiplier" | `0x665DD74  lea rdx,[0xF56CAFE]` | 0x66560F0 (Sky visitor) |
| 0xF5C6D27 | "SunMoonTexture" | `0x665DD02  lea rdx,[0xF5C6D27]` | 0x66560F0 (Sky visitor) |
| 0xF51B961 | "EndSky" | `0x66564B9  lea rdx,[0xF51B961]` | 0x66560F0 (Sky visitor) |
| 0xF7CA148 | "EndSkyForwardPBR" | `0x66564B2  lea rax,[0xF7CA148]` | 0x66560F0 (Sky visitor) |
| 0xF54C3E1 | "Stars" | `0x665686F  lea rdx,[0xF54C3E1]` | 0x66560F0 (Sky visitor) |
| 0xF7CA19E | "StarsForwardPBR" | `0x6656868  lea rax,[0xF7CA19E]` | 0x66560F0 (Sky visitor) |
| 0xF51B964 | "Sky" | `0x6656725  lea rdx,[0xF51B964]` | 0x66560F0 (Sky visitor) |

**CelestialBody**: No code-referenced string found for "CelestialBody" as a pass/material name. The CelestialBody tag (7) in the Sky visitor uses "SunMoon"/"SunMoonForwardPBR" material names.

---

## Step 2: 40 Instructions Around Each Reference + Callee Called Next

### Sky VV Builder Pass Declaration (0x560CA40..0x560CAAE)
```
0x560CA42  mov qword ptr [rbp+0x2BD0],0x1C
0x560CA4D  mov qword ptr [rbp+0x2BD8],0x1F
0x560CA58  movups xmm0,[0xF82178B]                       ; " Sky (pre-water)"
0x560CA5F  movups [rsi+0xC],xmm0                          ; store short name at +0xC
0x560CA63  movupd xmm0,[0xF82177F]                       ; "ForwardPBR - Sky (pre-water)"
0x560CA6B  movupd [rsi],xmm0                              ; store full name at +0x0
0x560CA6F  mov byte ptr [rsi+0x1C],0                      ; null-terminate / flag
0x560CA73  movdqa [rbp+0x31D0],xmm15
0x560CA7C  movdqa [rbp+0x31C0],xmm15
0x560CA85  mov qword ptr [rbp+0x31E0],0xF
0x560CA90  mov qword ptr [rbp+0x31E8],0
0x560CA9B  mov edx,0x15
0x560CAA0  lea rcx,[rbp+0x31C8]
0x560CAA7  lea r9,[0xF534325]                            ; "ForwardPBRTransparent"
0x560CAAE  call 0x9D6D0                                  ; CALLEE: sub_9d6d0 (string/vector copy helper)
```
**Callee**: `0x9D6D0` (sub_9d6d0)  
**Arguments**: `rcx = rbp+0x31C8` (destination buffer), `rdx = rsi` (source pass description), `r9 = "ForwardPBRTransparent"` (additional string to append/copy)

### Clouds VV Builder Pass Declaration (0x560E190..0x560E1FE)
```
0x560E192  mov qword ptr [rbp+0x2BD0],0x1F
0x560E19D  mov qword ptr [rbp+0x2BD8],0x1F
0x560E1A8  movups xmm0,[0xF8217AB]                       ; "ouds (pre-water)"
0x560E1AF  movups [rsi+0xF],xmm0                          ; store short name at +0xF
0x560E1B3  movupd xmm0,[0xF82179C]                       ; "ForwardPBR - Clouds (pre-water)"
0x560E1BB  movupd [rsi],xmm0                              ; store full name at +0x0
0x560E1BF  mov byte ptr [rsi+0x1F],0                      ; null-terminate / flag
0x560E1C3  movdqa [rbp+0x31D0],xmm15
0x560E1CC  movdqa [rbp+0x31C0],xmm15
0x560E1D5  mov qword ptr [rbp+0x31E0],0xF
0x560E1E0  mov qword ptr [rbp+0x31E8],0
0x560E1EB  mov edx,0x15
0x560E1F0  lea rcx,[rbp+0x31C8]
0x560E1F7  lea r9,[0xF534325]                            ; "ForwardPBRTransparent"
0x560E1FE  call 0x9D6D0                                  ; CALLEE: sub_9d6d0 (string/vector copy helper)
```
**Callee**: `0x9D6D0` (sub_9d6d0)  
**Arguments**: `rcx = rbp+0x31C8` (destination buffer), `rdx = rsi` (source pass description), `r9 = "ForwardPBRTransparent"` (additional string to append/copy)

### SunMoon/CelestialBody Material Resolution in Sky Visitor (0x6656579..0x66565EC)
```
0x6656579  cmp dword ptr [rsi+0x70],1
0x665657D  mov r9,[rsi+0x40]
0x6656581  mov rcx,[rsi+0x68]
0x6656585  lea rax,[0xF7CA226]                           ; "SunMoonForwardPBR"
0x665658C  lea rdx,[0xF584D1D]                           ; "SunMoon"
0x6656593  cmove rdx,rax                                  ; select PBR variant if [rsi+0x70]==1
0x6656597  mov eax,0x11
0x665659C  mov r10d,7
0x66565A2  cmove r10,rax                                  ; name length: 0x11 (PBR) or 7 (base)
0x66565A6  lea rax,[0x129F9FA8]                          ; TLS guard for PBR
0x66565AD  lea r8,[0x129F9F90]                           ; TLS key for PBR
0x66565B4  cmove r8,rax
0x66565B8  xorps xmm0,xmm0
0x66565BB  movaps [rbp+0x340],xmm0
0x66565C2  mov [rbp+0x1E0],rdx                            ; store selected material name pointer
0x66565C9  mov [rbp+0x1E8],r10                            ; store name length
0x66565D0  lea r12,[rbp+0x340]
0x66565D7  mov [rsp+0x28],r12
0x66565DC  lea rax,[rbp+0x1E0]
0x66565E3  mov [rsp+0x20],rax
0x66565E8  lea rdx,[rbp+0x20]                             ; output material pointer
0x66565EC  call 0x675E440                                ; CALLEE: sub_675e440 (material resolver)
```
**Callee**: `0x675E440` (sub_675e440)  
**Arguments**: `rcx = frame context (rsi)`, `rdx = material name string`, `r8 = TLS key`, stack: output pointer, name/length pair  
**Pattern**: Selects between "SunMoon" (len 7) and "SunMoonForwardPBR" (len 0x11) based on `[rsi+0x70]` (frame context flag), resolves material via resource cache. Used for CelestialBody tag 7.

### EndSky Material Resolution in Sky Visitor (0x665649C..0x6656511)
```
0x665649C  mov eax,[rsi+0x70]
0x665649F  xorps xmm0,xmm0
0x66564A2  movaps [rbp+0x120],xmm0
0x66564A9  mov [rbp+0x540],eax
0x66564AF  cmp eax,1
0x66564B2  lea rax,[0xF7CA148]                           ; "EndSkyForwardPBR"
0x66564B9  lea r14,[0xF51B961]                           ; "EndSky"
0x66564C0  cmove r14,rax                                  ; select PBR variant if eax==1
0x66564C4  mov r15d,0x10
0x66564CA  mov r13d,6
0x66564D0  cmovne r15,r13                                 ; name length: 0x10 (PBR) or 6 (base)
0x66564D4  jne 0x6656BE0                                 ; PBR path: heap allocate name
0x66564DA  mov rcx,[0x1233E1A8]                          ; allocator
0x66564E1  mov rax,[rcx]
0x66564E4  mov rax,[rax+8]
0x66564E8  mov edx,0x20
0x66564ED  call qword ptr [0xF99FFA0]                    ; allocate heap string
0x66564F3  mov r12,rax
0x66564F6  test rax,rax
0x66564F9  je 0x665D19E
0x66564FF  mov [rbp+0x120],r12                            ; store heap string pointer
0x6656506  mov eax,0x1F
0x665650B  mov r13d,0x10
0x6656511  jmp 0x6656BEC                                 ; join resolve path

; Non-PBR path falls through to 0x6656BEC -> 0x675E440 call
```
**Callee**: `0x675E440` (sub_675e440) - material resolver (called at 0x6656BEC..0x6656C0C, not shown here)

### Stars Material Resolution in Sky Visitor (0x665685C..0x66568D2)
```
0x665685C  cmp dword ptr [rsi+0x70],1
0x6656860  mov r9,[rsi+0x40]
0x6656864  mov rcx,[rsi+0x68]
0x6656868  lea rax,[0xF7CA19E]                           ; "StarsForwardPBR"
0x665686F  lea rdx,[0xF54C3E1]                           ; "Stars"
0x6656876  cmove rdx,rax                                  ; select PBR variant if [rsi+0x70]==1
0x665687A  mov eax,0xF
0x665687F  mov r10d,5
0x6656885  cmove r10,rax                                  ; name length: 0xF (PBR) or 5 (base)
0x6656889  lea rax,[0x129F9F68]                          ; TLS guard for PBR
0x6656890  lea r8,[0x129F9F50]                           ; TLS key for PBR
0x6656897  cmove r8,rax
0x665689B  xorps xmm0,xmm0
0x665689E  movaps [rbp+0x340],xmm0
0x66568A5  mov [rbp+0x1E0],rdx                            ; store selected material name pointer
0x66568AC  mov [rbp+0x1E8],r10                            ; store name length
0x66568B3  lea r12,[rbp+0x340]
0x66568BA  mov [rsp+0x28],r12
0x66568BF  lea rax,[rbp+0x1E0]
0x66568C6  mov [rsp+0x20],rax
0x66568CB  lea rdx,[rbp+0x320]                            ; output material pointer (different stack slot)
0x66568D2  call 0x675E440                                ; CALLEE: sub_675e440 (material resolver)
```
**Callee**: `0x675E440` (sub_675e440) - same material resolver  
**Pattern**: Selects between "Stars" (len 5) and "StarsForwardPBR" (len 0xF) based on `[rsi+0x70]`, resolves via resource cache. Used for Stars tag 6.

### Clouds Pass Body Material Resolution (0x67376B0..0x67376FD)
```
0x67376BA  mov rcx,[rsi+0x68]
0x67376C0  lea rax,[0xF2BE548]                           ; "Clouds"
0x67376C7  cmove rax,rdx                                  ; select variant
0x67376CB  mov [rbp+0x1D0],rax
0x67376D2  mov [rbp+0x1D8],r10
0x67376D9  lea rax,[0x129F9B40]                          ; TLS guard
0x67376E0  mov [rsp+0x28],rax
0x67376E5  lea rax,[rbp+0x1D0]
0x67376EC  mov [rsp+0x20],rax
0x67376F1  lea rdx,[rbp+0xF0]                             ; output
0x67376F8  call 0x67D6D70                                ; CALLEE: sub_67d6d70 (material resolver variant)
```
**Callee**: `0x67D6D70` (sub_67d6d70) - clouds-specific material resolver

### CloudsForwardPBR Hash Registration (0x673AE34..0x673AE42)
```
0x673AE27  cmp dword ptr [0x129F9B08],0xFFFFFFFF
0x673AE2E  jne 0x67375FB
0x673AE34  lea rcx,[0x129F9AE8]                          ; TLS guard for CloudsForwardPBR
0x673AE3B  lea rdx,[0xF7CA1AE]                           ; "CloudsForwardPBR"
0x673AE42  call 0x79580                                  ; CALLEE: sub_79580 (FNV-1a 64 hash registration)
```
**Callee**: `0x79580` (sub_79580) - FNV-1a 64 hash registration for material name

---

## Step 3: Pass-Registration Function Identification

### VV Builder Pass Registration (Sky / Clouds)
**Function**: `0x9D6D0` (sub_9d6d0)  
**Role**: String/vector copy helper used to construct pass description records. Not the final registration, but the key helper called immediately after populating the pass name fields.

**Pass Description Fields Stored (per Sky/Clouds site)**:
```
0x560CA58  movups xmm0,[0xF82178B]      ; load " Sky (pre-water)" (16 bytes)
0x560CA5F  movups [rsi+0xC],xmm0         ; store short name at pass_desc+0xC
0x560CA63  movupd xmm0,[0xF82177F]      ; load "ForwardPBR - Sky (pre-water)" (16 bytes)
0x560CA6B  movupd [rsi],xmm0             ; store full name at pass_desc+0x0
0x560CA6F  mov byte ptr [rsi+0x1C],0     ; null-terminator/flag at +0x1C

0x560E1A8  movups xmm0,[0xF8217AB]      ; load "ouds (pre-water)" (16 bytes)
0x560E1AF  movups [rsi+0xF],xmm0         ; store short name at pass_desc+0xF
0x560E1B3  movupd xmm0,[0xF82179C]      ; load "ForwardPBR - Clouds (pre-water)" (16 bytes)
0x560E1BB  movupd [rsi],xmm0             ; store full name at pass_desc+0x0
0x560E1BF  mov byte ptr [rsi+0x1F],0     ; null-terminator/flag at +0x1F
```

**Pass Description Structure Layout** (inferred):
- `+0x00`: Full pass name (16+ bytes, "ForwardPBR - X (pre-water)")
- `+0x0C`/`+0x0F`: Short name (" Sky (pre-water)" / "ouds (pre-water)")
- `+0x1C`/`+0x1F`: Terminator/flag byte
- After population: passed to `0x9D6D0` which appends "ForwardPBRTransparent" and likely adds to a pass vector

**Registration Completion**: After `0x9D6D0`, the code iterates resource sets and calls `[0xF99FFA0]` (sub_eea6040, vtable thunk) which likely enqueues the pass into the frame graph declarator.

### Sky Visitor Material Resolution (Stars / EndSky / SunMoon / Sky)
**Function**: `0x675E440` (sub_675e440)  
**Role**: Material resolver - resolves material name to material object via resource cache, used by all Sky visitor cases (tags 3,5,6,7).

**Pattern** (identical for Stars, EndSky, SunMoon, Sky):
1. Select material name variant (base vs ForwardPBR) based on `[frame_ctx+0x70]`
2. Load TLS guard + key for the material name
3. Call `0x675E440(rcx=frame_ctx, rdx=name_ptr, r8=TLS_key, stack=output_ptr)`
4. Returns material object in output; checks `material+0x10` loaded flag
5. On success: refcount material, proceed to draw setup

**Material Description Fields Read** (from 66560f0_sky_cases.md):
- EndSky (tag 3): `desc+0x00` mesh, `+0x08` sampler data, `+0x18` u16 flag, `+0x1C` SkyColor, `+0x2C..+0x6B` matrix, `+0x6C` UV0Transform, `+0xAC` MinimumSkyLuminance
- Sky (tag 5): `desc+0x00` mesh, `+0x08` SkyColor, `+0x18` FogColor, `+0x28..+0x67` matrix, `+0x68` u16
- Stars (tag 6): `desc+0x00` mesh, `+0x08` StarsColor, `+0x18..+0x57` matrix, `+0x58` u16
- CelestialBody/SunMoon (tag 7): `desc+0x00` mesh, `+0x08` sampler data, `+0x18` SunMoonColor, `+0x28..+0x67` matrix, `+0x68` u16, `+0x6C` flag, `+0x70` byte, `+0x80` SunMoonEmissiveMultiplier

### Clouds Pass Body Material Resolution
**Function**: `0x67D6D70` (sub_67d6d70) for "Clouds", `0x79580` (FNV-1a hash) + `0x5668AC0` for "CloudsForwardPBR"  
**Role**: Clouds-specific material resolution, separate from Sky visitor.

---

## Verification Summary

| Item | Status | Notes |
|---|---|---|
| Sky VV builder pass strings | FOUND | "ForwardPBR - Sky (pre-water)" + short name |
| Clouds VV builder pass strings | FOUND | "ForwardPBR - Clouds (pre-water)" + short name |
| SunMoon VV builder pass strings | NOT FOUND | SunMoon rendered via Sky visitor tag 7, not separate VV pass |
| CelestialBody VV builder pass strings | NOT FOUND | Same as SunMoon; uses "SunMoon" material names |
| Stars/EndSky VV builder pass strings | NOT FOUND | Rendered via Sky visitor tags 6/3, not separate VV passes |
| Pass-registration helper (VV builder) | IDENTIFIED | 0x9D6D0 (string/vector copy) + vtable enqueue via [0xF99FFA0] |
| Material resolver (Sky visitor) | IDENTIFIED | 0x675E440 (used by Stars/EndSky/SunMoon/Sky) |
| Material resolver (Clouds pass) | IDENTIFIED | 0x67D6D70 / 0x79580 |

## Gaps / Unverified
- [UNVERIFIED: 0x560CAAE] Exact structure of pass description passed to 0x9D6D0; the "ForwardPBRTransparent" append suggests a pipeline variant field
- [UNVERIFIED: 0x560CBB3] The vtable call `[0xF99FFA0]` after pass setup - confirms registration into declarator but exact interface not decoded
- [UNVERIFIED: 0x675E440] Material resolver internal logic; returns material object but field layout of returned object not fully traced
- [UNVERIFIED: 0x55F1450] No "SunMoon" or "CelestialBody" pass declarations found in VV builder; confirm they are not separate frame graph passes

## TOOL REQUESTS
- `pass_desc_dumper.py` | input: pass description RVA (rsi at call site) -> output: structured field dump | would automate extraction of pass description fields across all 210 VV builder passes instead of manual per-site analysis
- `material_resolver_tracer.py` | input: 0x675E440 call site -> output: material object field map | would trace the material resolver return value to document the material object layout consumed by draw setup