## NEXT
DONE

# UNIT U-EC5a — C5a Declarator<RenderContext> + five Bind* dependency kinds + module names (6aq); registration call addresses

Goal (this unit, ONLY the pending part): close checklist item C5a's pending registration-call-address part — tie the 6aq module/pass names to registration call sites in the exe, using the orchestrator hint's module-name hash angle. Declarator<RenderContext> and the five Bind* dependency kinds are covered by the input data (docs/progress/oc_U-C5a.md, docs/progress/oc_U-C5a2.md) and are not repeated except as context.

Source checklist item (docs/RENDER_CHECKLIST.md line 96, still unchecked): "C5a Declarator<RenderContext> + five Bind* dependency kinds + module names — 6aq; registration call addresses pending"

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only.

Input data (read fully, not re-run): docs/progress/oc_U-C5a.md, docs/progress/oc_U-C5a2.md, docs/BGFX_MAP.md section 6aq.

## 1. Module names — FNV-1a 64 hash angle (orchestrator hint part 1)

Method: hash each 6aq candidate module name with FNV-1a 64 (basis 0xCBF29CE484222325, prime 0x100000001B3 — same scheme as the task-kind hash at record+0x28, see C3b/L3e), then search the exe for the 8-byte constant: `rdis imm <hash>` (finds imm8/imm16/imm32/imm64/imm8to32/imm32to64 in code) plus a raw little-endian 8-byte byte scan of the whole exe file.

## TABLE 1 — 6aq module-name hash search (name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag)

| averageLuminance | - | - | - | - | FNV-1a 64 = 0xA92BA4814782CD86; `rdis imm 0xa92ba4814782cd86` -> 0 hit(s); raw LE scan of exe -> 0 hits; constant absent [V negative] | [V] |
| localExposure | - | - | - | - | FNV-1a 64 = 0xCEF353AE273F6B5D; `rdis imm 0xcef353ae273f6b5d` -> 0 hit(s); raw LE scan of exe -> 0 hits; constant absent [V negative] | [V] |
| taau | - | - | - | - | FNV-1a 64 = 0xD9313DEF0781E4F0; `rdis imm 0xd9313def0781e4f0` -> 0 hit(s); raw LE scan of exe -> 0 hits; constant absent [V negative] | [V] |
| clusterLights | - | - | - | - | FNV-1a 64 = 0x2CF15CDAA0F828EC; `rdis imm 0x2cf15cdaa0f828ec` -> 0 hit(s); raw LE scan of exe -> 0 hits; constant absent [V negative] | [V] |
| volumeScattering | - | - | - | - | FNV-1a 64 = 0x3688B40FBB2557A5; `rdis imm 0x3688b40fbb2557a5` -> 0 hit(s); raw LE scan of exe -> 0 hits; constant absent [V negative] | [V] |
| generateCubemapMips | - | - | - | - | FNV-1a 64 = 0x8067836DEABD5BDC; `rdis imm 0x8067836deabd5bdc` -> 0 hit(s); raw LE scan of exe -> 0 hits; constant absent [V negative] | [V] |
| rayTrace | - | - | - | - | FNV-1a 64 = 0xDAACACD4EFCBE5FC; `rdis imm 0xdaacacd4efcbe5fc` -> 0 hit(s); raw LE scan of exe -> 0 hits; constant absent [V negative] | [V] |
| preprocessingutils | - | - | - | - | FNV-1a 64 = 0xF958BE4336668576; `rdis imm 0xf958be4336668576` -> 0 hit(s); raw LE scan of exe -> 0 hits; constant absent [V negative] | [V] |

Result: all eight candidate hash constants are absent from the exe, both as instruction immediates and as raw bytes. Module-name strings were already absent as ASCII/UTF-16 (verified negative in oc_U-C5a/oc_U-C5a2: averageLuminance, localExposure, taau, clusterLights, volumeScattering, generateCubemapMips, rayTrace, fidelityfx::fsr1::_FSR1Draw, preprocessingutils, and FancyFrameRendererResources/VibrantVisualsFrameRendererResources/RTXMinecraftFrameRendererResources). So no registration call address can be attributed to a specific 6aq module name from static analysis.

Module attribution that IS proven [V] comes from builder identity (BGFX_MAP 6aq): VV builder sub_55f1450 = VibrantVisualsFrameRendererResources module (90 registration call sites below); RTX builder sub_bbe2d50 = RTXMinecraftFrameRendererResources module (3 sites below). FancyFrameRendererResources: builder RVA and registration call addresses not identified.

## 2. Declarator<RenderContext> registration call addresses (orchestrator hint parts 2 and 3)

sub_567b570 (0x567B570..0x567B846) is the Declarator<RenderContext> bind/lookup — the registration function [V per input data oc_U-C5a.md: FNV-1a bind/lookup, vector at [rcx+0x8] stride 0x48, kind byte at entry+0x08, hash-table entry kind at +0x40]. Every call to it is a Declarator registration call site. All 111 xrefs enumerated with `rdis xr 0x567b570` and each call verbatim-verified at its exact RVA with `rdis dis <rva> 4` [V].

Call convention (proven verbatim at representative site 0x55F3C2B):
```
  55f3be7  mov byte ptr [rbp+0x2EF8],0
  55f3bfd  mov qword ptr [rbp+0x2C00],1
  55f3c08  lea rax,[rbp+0x27A0]
  55f3c0f  mov [rbp+0x2C08],rax
  55f3c16  lea rcx,[rbp+0x1DD8]
  55f3c1d  lea rdx,[rbp+0x2EF0]
  55f3c24  lea r8,[rbp+0x2C00]
  55f3c2b  call 0x567B570
```
- rcx = Declarator object (`lea rcx,[rbp+...]`), rdx = entry pointer (`lea rdx,[rbp+...]`), r8 = { r8+0x00 = entry value (immediate), r8+0x08 = hash-table base pointer (lea) }; entry+0x00 qword loaded from a module-global (`mov rax,[0x129Cxxxx]`); entry+0x08 = kind byte immediate. Each call: `0xRVA  call 0x567B570` (size 5 = E8 rel32).

Per-site immediate arguments (kind byte at entry+0x08; value at r8+0x00) as seen at each site:
- kind imm in {0, 1}; value imm in {0, 1, 0x3F800000 (float 1.0), 0x570F0375}.
- sub_6753b50: all 6 sites use kind=1. sub_55f1450 (VV): 90 sites, kind=0 except 0x55FBF80, 0x56251C3, 0x562B6B7 (kind=1).
- Note: sub_567b570 entry kind {0,1} is the hash-table entry kind; the five Bind* dependency kinds 0-4 are a different field (0x20-stride dependency array entry+0x18, jump table 0xF478E3C in sub_c273420, input data oc_U-C5a2.md) and are NOT the entry kind written here. This supersedes oc_U-C5a's "ALL observed call sites use kind=0": kind=1 is now verified at 9 sites.

## TABLE 2 — Declarator<RenderContext> registration call sites: calls to sub_567b570 (offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|--------|------|--------------------|------------------------------------|---------|-----|
### sub_55f1450 (VV builder, VibrantVisuals) — 90 registration call sites

| 0x55F3C2B | 5 | - | `0x55f3c2b  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F3CB5 | 5 | - | `0x55f3cb5  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F3DF5 | 5 | - | `0x55f3df5  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F3E83 | 5 | - | `0x55f3e83  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F4B3D | 5 | - | `0x55f4b3d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5776 | 5 | - | `0x55f5776  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F57E6 | 5 | - | `0x55f57e6  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F582D | 5 | - | `0x55f582d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5874 | 5 | - | `0x55f5874  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F58E9 | 5 | - | `0x55f58e9  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F594A | 5 | - | `0x55f594a  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F59A5 | 5 | - | `0x55f59a5  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F59E6 | 5 | - | `0x55f59e6  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5A28 | 5 | - | `0x55f5a28  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5AAB | 5 | - | `0x55f5aab  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5B1E | 5 | - | `0x55f5b1e  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5C71 | 5 | - | `0x55f5c71  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5CC9 | 5 | - | `0x55f5cc9  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5D41 | 5 | - | `0x55f5d41  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5DE3 | 5 | - | `0x55f5de3  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5E7D | 5 | - | `0x55f5e7d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F5F1C | 5 | - | `0x55f5f1c  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F7B02 | 5 | - | `0x55f7b02  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F7CC8 | 5 | - | `0x55f7cc8  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F7DED | 5 | - | `0x55f7ded  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F7F11 | 5 | - | `0x55f7f11  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F7F83 | 5 | - | `0x55f7f83  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F7FE4 | 5 | - | `0x55f7fe4  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F8028 | 5 | - | `0x55f8028  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F80D8 | 5 | - | `0x55f80d8  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F8822 | 5 | - | `0x55f8822  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F8AE3 | 5 | - | `0x55f8ae3  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F8B5A | 5 | - | `0x55f8b5a  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F8BE8 | 5 | - | `0x55f8be8  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F8C76 | 5 | - | `0x55f8c76  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F8CF9 | 5 | - | `0x55f8cf9  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9007 | 5 | - | `0x55f9007  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F907D | 5 | - | `0x55f907d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F90E1 | 5 | - | `0x55f90e1  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9744 | 5 | - | `0x55f9744  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F978D | 5 | - | `0x55f978d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F99B5 | 5 | - | `0x55f99b5  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0x3f800000; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9A27 | 5 | - | `0x55f9a27  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9ACB | 5 | - | `0x55f9acb  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9BA5 | 5 | - | `0x55f9ba5  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9C4C | 5 | - | `0x55f9c4c  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9E22 | 5 | - | `0x55f9e22  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9EF7 | 5 | - | `0x55f9ef7  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55F9F7F | 5 | - | `0x55f9f7f  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA053 | 5 | - | `0x55fa053  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA10C | 5 | - | `0x55fa10c  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA29E | 5 | - | `0x55fa29e  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA487 | 5 | - | `0x55fa487  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA50F | 5 | - | `0x55fa50f  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA5DF | 5 | - | `0x55fa5df  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA671 | 5 | - | `0x55fa671  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0x3f800000; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA749 | 5 | - | `0x55fa749  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA7E3 | 5 | - | `0x55fa7e3  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA876 | 5 | - | `0x55fa876  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA95E | 5 | - | `0x55fa95e  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FA9FA | 5 | - | `0x55fa9fa  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FAA82 | 5 | - | `0x55faa82  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FAAFE | 5 | - | `0x55faafe  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FABAA | 5 | - | `0x55fabaa  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FAC49 | 5 | - | `0x55fac49  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FAF56 | 5 | - | `0x55faf56  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB00D | 5 | - | `0x55fb00d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB0D0 | 5 | - | `0x55fb0d0  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB1A1 | 5 | - | `0x55fb1a1  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB37D | 5 | - | `0x55fb37d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB3FB | 5 | - | `0x55fb3fb  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB474 | 5 | - | `0x55fb474  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB4DA | 5 | - | `0x55fb4da  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB801 | 5 | - | `0x55fb801  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FB9DF | 5 | - | `0x55fb9df  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FBA6E | 5 | - | `0x55fba6e  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FBDCB | 5 | - | `0x55fbdcb  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FBE4F | 5 | - | `0x55fbe4f  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x55FBF80 | 5 | - | `0x55fbf80  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x560BCBB | 5 | - | `0x560bcbb  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x560C19A | 5 | - | `0x560c19a  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x560C230 | 5 | - | `0x560c230  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x560C295 | 5 | - | `0x560c295  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x5611770 | 5 | - | `0x5611770  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0x570f0375; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x56251C3 | 5 | - | `0x56251c3  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x562526E | 5 | - | `0x562526e  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x562B6B7 | 5 | - | `0x562b6b7  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x562B74E | 5 | - | `0x562b74e  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x562B7C5 | 5 | - | `0x562b7c5  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x562B817 | 5 | - | `0x562b817  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |

### sub_bbe2d50 (RTX builder, RTXMinecraft) — 3 registration call sites

| 0xBBE34B8 | 5 | - | `0xbbe34b8  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBBE3545 | 5 | - | `0xbbe3545  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBBE35A9 | 5 | - | `0xbbe35a9  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |

### sub_6753b50 — 6 registration call sites

| 0x6753C8A | 5 | - | `0x6753c8a  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x6753CC1 | 5 | - | `0x6753cc1  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x6753D07 | 5 | - | `0x6753d07  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x6753D4D | 5 | - | `0x6753d4d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x6753D93 | 5 | - | `0x6753d93  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x6753DD8 | 5 | - | `0x6753dd8  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=1, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |

### sub_bbce7b0 — 5 registration call sites

| 0xBBCF04D | 5 | - | `0xbbcf04d  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBBCF0D1 | 5 | - | `0xbbcf0d1  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBBCF12F | 5 | - | `0xbbcf12f  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBBCF1BA | 5 | - | `0xbbcf1ba  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBBCF2C1 | 5 | - | `0xbbcf2c1  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |

### sub_bb3e2b0 — 4 registration call sites

| 0xBB3F0CE | 5 | - | `0xbb3f0ce  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBB3F286 | 5 | - | `0xbb3f286  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBB3F301 | 5 | - | `0xbb3f301  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0xBB3F356 | 5 | - | `0xbb3f356  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |

### sub_56a06a0 — 2 registration call sites

| 0x56A120B | 5 | - | `0x56a120b  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |
| 0x56A1269 | 5 | - | `0x56a1269  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=1; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |

### sub_bb6b350 — 1 registration call site

| 0xBB6B9AA | 5 | - | `0xbb6b9aa  call 0x567B570` | Declarator<RenderContext> bind/lookup registration call; entry+0x08 kind imm=0, r8+0x00 value imm=0x3f800000; entry+0x00=qword from module-global (mov rax,[0x129Cxxxx]); rcx=Declarator, rdx=entry, r8={value, hash-table base} | [V] |

TOTAL registration call sites to sub_567b570: 111 (90 VV + 3 RTX + 6 sub_6753b50 + 5 sub_bbce7b0 + 4 sub_bb3e2b0 + 2 sub_56a06a0 + 1 sub_bb6b350) = 111


## 3. What is proven [V] vs what remains open

Proven [V] registration addresses (hint part 3, names stay unbound):
- All 111 Declarator<RenderContext> registration call sites to sub_567b570, verbatim at exact RVA, with per-site immediate arguments: kind imm in {0,1}, value imm in {0,1,0x3F800000,0x570F0375}.
- VV module (VibrantVisualsFrameRendererResources via sub_55f1450): 90 registration call sites.
- RTX module (RTXMinecraftFrameRendererResources via sub_bbe2d50): 3 registration call sites at 0xBBE34B8, 0xBBE3545, 0xBBE35A9.
- Other registration call sites not module-attributed: sub_6753b50 (6, all kind=1), sub_bbce7b0 (5), sub_bb3e2b0 (4), sub_56a06a0 (2), sub_bb6b350 (1, value 0x3F800000).

Still open:
- Binding any 6aq module name to a registration call address: module names absent as strings and absent as FNV-1a 64 constants (TABLE 1).
- FancyFrameRendererResources builder RVA and its sub_567b570 registration call addresses: not identified.

## CLOSES?

CLOSES? NO — single blocking fact: the 6aq module names cannot be bound to any registration call address; module-name strings are absent as ASCII/UTF-16 (verified negative in prior units) and the FNV-1a 64 hash constants of all eight candidate names (averageLuminance, localExposure, taau, clusterLights, volumeScattering, generateCubemapMips, rayTrace, preprocessingutils) are absent both as instruction immediates (`rdis imm`: 0 hits each) and as raw little-endian bytes anywhere in the exe (this unit), so no registration call address is attributable to a specific module name, and FancyFrameRendererResources' builder RVA plus its registration calls remain unidentified. The registration call addresses themselves ARE proven [V] (all 111 sub_567b570 call sites with per-site immediate arguments) but stay module-unresolved.

## Verification artifacts

- `rdis xr 0x567b570` -> 111 call sites; every call verbatim-verified with `rdis dis <rva> 4` at exact RVA [V]
- `rdis imm <each of the 8 hashes>` -> 0 hits each [V]; raw LE 8-byte scan of exe -> 0 hits each [V]
- `python tools/sigs/verify_oc.py docs/progress/oc_U-EC5a.md` then `python tools/delegate.py check docs/progress/oc_U-EC5a.md`
- Input data: docs/progress/oc_U-C5a.md, docs/progress/oc_U-C5a2.md

## TOOL REQUESTS

- None (rdis xr/imm/dis sufficed). Closing the module-name part would require a data-flow pass binding hash constants to call sites inside the builders; no such tool exists yet.

## NEXT
step 2
