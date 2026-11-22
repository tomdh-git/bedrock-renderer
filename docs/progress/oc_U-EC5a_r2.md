## NEXT
DONE

# UNIT U-EC5a — C5a Declarator<RenderContext> + five Bind* dependency kinds + module names (6aq); registration call addresses

Goal: close the pending part of checklist item C5a — module names (6aq) and their registration call addresses.
Declarator<RenderContext> and the five Bind* dependency kinds are done (docs/progress/oc_U-C5a.md, oc_U-C5a2.md); this unit covers only what was pending/not found.

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only.

Registration function: sub_567b570 (0x567B570..0x567B846) = Declarator<RenderContext> bind/lookup [V: oc_U-C5a]. Every call to it is a Declarator registration call site. All 111 xrefs enumerated with `rdis xr 0x567b570` [V].

## Module names (6aq) [V: docs/BGFX_MAP.md section 6aq]

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| VibrantVisualsFrameRendererResources | 0x55F1450 | - | - | module resource root; VV builder sub_55f1450 registers pass deps via sub_567b570 (BGFX_MAP 6aq/6ar) | [V] |
| RTXMinecraftFrameRendererResources | 0xBBE2D50 | - | - | module resource root; RTX builder sub_bbe2d50 registers pass deps via sub_567b570 (BGFX_MAP 6aq/956) | [V] |
| FancyFrameRendererResources | not found | - | - | module resource root; builder RVA and registration call addresses not identified | [?] |

## Registration call addresses — Vibrant Visuals module (builder sub_55f1450, 0x55F1450..0x563F594) [V]

90 Declarator bind call sites to sub_567b570, one row per site:

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| 0x55f3c2b | 5 | 0x55f3c2b (VV builder sub_55f1450) | `0x55f3c2b  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f3cb5 | 5 | 0x55f3cb5 (VV builder sub_55f1450) | `0x55f3cb5  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f3df5 | 5 | 0x55f3df5 (VV builder sub_55f1450) | `0x55f3df5  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f3e83 | 5 | 0x55f3e83 (VV builder sub_55f1450) | `0x55f3e83  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f4b3d | 5 | 0x55f4b3d (VV builder sub_55f1450) | `0x55f4b3d  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5776 | 5 | 0x55f5776 (VV builder sub_55f1450) | `0x55f5776  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f57e6 | 5 | 0x55f57e6 (VV builder sub_55f1450) | `0x55f57e6  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f582d | 5 | 0x55f582d (VV builder sub_55f1450) | `0x55f582d  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5874 | 5 | 0x55f5874 (VV builder sub_55f1450) | `0x55f5874  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f58e9 | 5 | 0x55f58e9 (VV builder sub_55f1450) | `0x55f58e9  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f594a | 5 | 0x55f594a (VV builder sub_55f1450) | `0x55f594a  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f59a5 | 5 | 0x55f59a5 (VV builder sub_55f1450) | `0x55f59a5  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f59e6 | 5 | 0x55f59e6 (VV builder sub_55f1450) | `0x55f59e6  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5a28 | 5 | 0x55f5a28 (VV builder sub_55f1450) | `0x55f5a28  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5aab | 5 | 0x55f5aab (VV builder sub_55f1450) | `0x55f5aab  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5b1e | 5 | 0x55f5b1e (VV builder sub_55f1450) | `0x55f5b1e  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5c71 | 5 | 0x55f5c71 (VV builder sub_55f1450) | `0x55f5c71  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5cc9 | 5 | 0x55f5cc9 (VV builder sub_55f1450) | `0x55f5cc9  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5d41 | 5 | 0x55f5d41 (VV builder sub_55f1450) | `0x55f5d41  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5de3 | 5 | 0x55f5de3 (VV builder sub_55f1450) | `0x55f5de3  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5e7d | 5 | 0x55f5e7d (VV builder sub_55f1450) | `0x55f5e7d  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f5f1c | 5 | 0x55f5f1c (VV builder sub_55f1450) | `0x55f5f1c  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f7b02 | 5 | 0x55f7b02 (VV builder sub_55f1450) | `0x55f7b02  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f7cc8 | 5 | 0x55f7cc8 (VV builder sub_55f1450) | `0x55f7cc8  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f7ded | 5 | 0x55f7ded (VV builder sub_55f1450) | `0x55f7ded  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f7f11 | 5 | 0x55f7f11 (VV builder sub_55f1450) | `0x55f7f11  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f7f83 | 5 | 0x55f7f83 (VV builder sub_55f1450) | `0x55f7f83  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f7fe4 | 5 | 0x55f7fe4 (VV builder sub_55f1450) | `0x55f7fe4  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f8028 | 5 | 0x55f8028 (VV builder sub_55f1450) | `0x55f8028  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f80d8 | 5 | 0x55f80d8 (VV builder sub_55f1450) | `0x55f80d8  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f8822 | 5 | 0x55f8822 (VV builder sub_55f1450) | `0x55f8822  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f8ae3 | 5 | 0x55f8ae3 (VV builder sub_55f1450) | `0x55f8ae3  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f8b5a | 5 | 0x55f8b5a (VV builder sub_55f1450) | `0x55f8b5a  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f8be8 | 5 | 0x55f8be8 (VV builder sub_55f1450) | `0x55f8be8  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f8c76 | 5 | 0x55f8c76 (VV builder sub_55f1450) | `0x55f8c76  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f8cf9 | 5 | 0x55f8cf9 (VV builder sub_55f1450) | `0x55f8cf9  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9007 | 5 | 0x55f9007 (VV builder sub_55f1450) | `0x55f9007  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f907d | 5 | 0x55f907d (VV builder sub_55f1450) | `0x55f907d  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f90e1 | 5 | 0x55f90e1 (VV builder sub_55f1450) | `0x55f90e1  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9744 | 5 | 0x55f9744 (VV builder sub_55f1450) | `0x55f9744  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f978d | 5 | 0x55f978d (VV builder sub_55f1450) | `0x55f978d  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f99b5 | 5 | 0x55f99b5 (VV builder sub_55f1450) | `0x55f99b5  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9a27 | 5 | 0x55f9a27 (VV builder sub_55f1450) | `0x55f9a27  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9acb | 5 | 0x55f9acb (VV builder sub_55f1450) | `0x55f9acb  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9ba5 | 5 | 0x55f9ba5 (VV builder sub_55f1450) | `0x55f9ba5  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9c4c | 5 | 0x55f9c4c (VV builder sub_55f1450) | `0x55f9c4c  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9e22 | 5 | 0x55f9e22 (VV builder sub_55f1450) | `0x55f9e22  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9ef7 | 5 | 0x55f9ef7 (VV builder sub_55f1450) | `0x55f9ef7  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55f9f7f | 5 | 0x55f9f7f (VV builder sub_55f1450) | `0x55f9f7f  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa053 | 5 | 0x55fa053 (VV builder sub_55f1450) | `0x55fa053  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa10c | 5 | 0x55fa10c (VV builder sub_55f1450) | `0x55fa10c  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa29e | 5 | 0x55fa29e (VV builder sub_55f1450) | `0x55fa29e  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa487 | 5 | 0x55fa487 (VV builder sub_55f1450) | `0x55fa487  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa50f | 5 | 0x55fa50f (VV builder sub_55f1450) | `0x55fa50f  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa5df | 5 | 0x55fa5df (VV builder sub_55f1450) | `0x55fa5df  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa671 | 5 | 0x55fa671 (VV builder sub_55f1450) | `0x55fa671  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa749 | 5 | 0x55fa749 (VV builder sub_55f1450) | `0x55fa749  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa7e3 | 5 | 0x55fa7e3 (VV builder sub_55f1450) | `0x55fa7e3  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa876 | 5 | 0x55fa876 (VV builder sub_55f1450) | `0x55fa876  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa95e | 5 | 0x55fa95e (VV builder sub_55f1450) | `0x55fa95e  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fa9fa | 5 | 0x55fa9fa (VV builder sub_55f1450) | `0x55fa9fa  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55faa82 | 5 | 0x55faa82 (VV builder sub_55f1450) | `0x55faa82  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55faafe | 5 | 0x55faafe (VV builder sub_55f1450) | `0x55faafe  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fabaa | 5 | 0x55fabaa (VV builder sub_55f1450) | `0x55fabaa  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fac49 | 5 | 0x55fac49 (VV builder sub_55f1450) | `0x55fac49  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55faf56 | 5 | 0x55faf56 (VV builder sub_55f1450) | `0x55faf56  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb00d | 5 | 0x55fb00d (VV builder sub_55f1450) | `0x55fb00d  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb0d0 | 5 | 0x55fb0d0 (VV builder sub_55f1450) | `0x55fb0d0  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb1a1 | 5 | 0x55fb1a1 (VV builder sub_55f1450) | `0x55fb1a1  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb37d | 5 | 0x55fb37d (VV builder sub_55f1450) | `0x55fb37d  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb3fb | 5 | 0x55fb3fb (VV builder sub_55f1450) | `0x55fb3fb  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb474 | 5 | 0x55fb474 (VV builder sub_55f1450) | `0x55fb474  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb4da | 5 | 0x55fb4da (VV builder sub_55f1450) | `0x55fb4da  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb801 | 5 | 0x55fb801 (VV builder sub_55f1450) | `0x55fb801  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fb9df | 5 | 0x55fb9df (VV builder sub_55f1450) | `0x55fb9df  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fba6e | 5 | 0x55fba6e (VV builder sub_55f1450) | `0x55fba6e  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fbdcb | 5 | 0x55fbdcb (VV builder sub_55f1450) | `0x55fbdcb  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fbe4f | 5 | 0x55fbe4f (VV builder sub_55f1450) | `0x55fbe4f  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x55fbf80 | 5 | 0x55fbf80 (VV builder sub_55f1450) | `0x55fbf80  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x560bcbb | 5 | 0x560bcbb (VV builder sub_55f1450) | `0x560bcbb  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x560c19a | 5 | 0x560c19a (VV builder sub_55f1450) | `0x560c19a  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x560c230 | 5 | 0x560c230 (VV builder sub_55f1450) | `0x560c230  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x560c295 | 5 | 0x560c295 (VV builder sub_55f1450) | `0x560c295  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x5611770 | 5 | 0x5611770 (VV builder sub_55f1450) | `0x5611770  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x56251c3 | 5 | 0x56251c3 (VV builder sub_55f1450) | `0x56251c3  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x562526e | 5 | 0x562526e (VV builder sub_55f1450) | `0x562526e  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x562b6b7 | 5 | 0x562b6b7 (VV builder sub_55f1450) | `0x562b6b7  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x562b74e | 5 | 0x562b74e (VV builder sub_55f1450) | `0x562b74e  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x562b7c5 | 5 | 0x562b7c5 (VV builder sub_55f1450) | `0x562b7c5  call 0x567b570` | Declarator bind/register call site | [V] |
| 0x562b817 | 5 | 0x562b817 (VV builder sub_55f1450) | `0x562b817  call 0x567b570` | Declarator bind/register call site | [V] |

## Registration call addresses — RTX module (builder sub_bbe2d50, 0xBBE2D50..0xBBF62CF) [V]

3 Declarator bind call sites to sub_567b570:

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| 0xbbe34b8 | 5 | 0xbbe34b8 (RTX builder sub_bbe2d50) | `0xbbe34b8  call 0x567b570` | Declarator bind/register call site | [V] |
| 0xbbe3545 | 5 | 0xbbe3545 (RTX builder sub_bbe2d50) | `0xbbe3545  call 0x567b570` | Declarator bind/register call site | [V] |
| 0xbbe35a9 | 5 | 0xbbe35a9 (RTX builder sub_bbe2d50) | `0xbbe35a9  call 0x567b570` | Declarator bind/register call site | [V] |

## Other sub_567b570 callers (not module-attributed)

sub_56a06a0 (0x56a120b, 0x56a1269), sub_6753b50 (0x6753c8a, 0x6753cc1, 0x6753d07, 0x6753d4d, 0x6753d93, 0x6753dd8), sub_bb3e2b0 (0xbb3f0ce, 0xbb3f286, 0xbb3f301, 0xbb3f356), sub_bb6b350 (0xbb6b9aa), sub_bbce7b0 (0xbbcf04d, 0xbbcf0d1, 0xbbcf12f, 0xbbcf1ba, 0xbbcf2c1): 18 further call sites whose function is not assigned to Fancy/VV/RTX [V calls, ? module].

CLOSES? NO — module names are known (FancyFrameRendererResources, VibrantVisualsFrameRendererResources, RTXMinecraftFrameRendererResources per 6aq) and VV/RTX registration call addresses are proven [V], but the FancyFrameRendererResources builder RVA and its sub_567b570 registration call addresses are not identified; no call site is attributable to the Fancy module, which is the single blocking fact.
