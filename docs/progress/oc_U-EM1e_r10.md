## NEXT
DONE

# U-EM1e: M1e Pass lambdas (L6) — bloom down run (0xbc99739 / 0xbc99794)

This run covers bloom down body 0xbc99739 / 0xbc99794: the DFDownSample (0xbc99739) and ThresholdedDownSample (0xbc99794) hash-static registration sites in builder 0xbc98310 ("Bloom"). They are NOT code bodies; the executed body for both is ScreenDraw 0xbc04dc0 via closure vtable 0xF44B4E0 slot 2.

Evidence this run: rdis dis 0xbc99728 (14 instr), rdis dis 0xbc99739 (140 instr), rdis vt 0xF44B4E0, xref str "DFDownSample" / "ThresholdedDownSample". Every quoted instruction below was re-checked against the exe this run.

## Verified rows — bloom down registration sites (offset | size | address | verbatim `0xRVA  instr` | meaning | tag)

| offset | size | address | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc99732 | 8 | [0xF5D973B] | `0xbc99732  lea r8,[0xF5D973B]` | "DFDownSample" name string (data_f5d973b; xref str refs this address + builder 0xbc98310), argument to call 0x76AD00 (sub_76ad00 hash resolve) in the DFDownSample site | [V] |
| 0xbc99739 | 8 | imm | `0xbc99739  mov rdx,0x34E743CD5E04564D` | DFDownSample FNV-1 64 hash (pass table 6p: "DFDownSample 0xbc99739") loaded into rdx before call 0x76AD00 | [V] |
| 0xbc99749 | 8 | [0xBC9AC80] | `0xbc99749  lea rcx,[0xBC9AC80]` | body sub_bc9ac80 (DFDownSample lambda) passed as 1st arg of call 0xE935740 (execute-body registration sub_e935740) | [V] |
| 0xbc99755 | 8 | [0x12AE1DB0] | `0xbc99755  lea rcx,[0x12AE1DB0]` | pass slot 0x12AE1DB0 passed as 1st arg of call 0xE938D70 (pass-slot registration sub_e938d70) for DFDownSample | [V] |
| 0xbc99786 | 8 | [0x12AE1DB8] | `0xbc99786  lea rcx,[0x12AE1DB8]` | adjacent slot/name field 0x12AE1DB8 loaded into rcx in the ThresholdedDownSample sequence, immediately before the name-string lea | [V] |
| 0xbc9978d | 8 | [0xF5D9717] | `0xbc9978d  lea r8,[0xF5D9717]` | "ThresholdedDownSample" name string (data_f5d9717; xref str refs this address + builder 0xbc98310), argument to call 0x76AD00 in the ThresholdedDownSample site | [V] |
| 0xbc99794 | 8 | imm | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | ThresholdedDownSample FNV-1 64 hash (pass table 6p: "ThresholdedDownSample 0xbc99794") loaded into rdx before call 0x76AD00 | [V] |
| 0xbc997a4 | 8 | [0xBC9AD10] | `0xbc997a4  lea rcx,[0xBC9AD10]` | body sub_bc9ad10 (ThresholdedDownSample lambda) passed as 1st arg of call 0xE935740 | [V] |
| 0xbc997b0 | 8 | [0x12AE1DE8] | `0xbc997b0  lea rcx,[0x12AE1DE8]` | pass slot 0x12AE1DE8 passed as 1st arg of call 0xE938D70 for ThresholdedDownSample | [V] |

## Executed body (verified via rdis vt)

| offset | size | address | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc04dc0 | - | vt 0xF44B4E0 slot 2 (+0x010) | `0xbc04dc0  push rbp` | Executed body of both bloom-down closures: closure vtable 0xF44B4E0 (pass table bloom-down row) slot 2 -> sub_bc04dc0 (0x5d3 bytes) = ScreenDraw 0xbc04dc0 [V via rdis vt 0xF44B4E0; first instruction push rbp verified]. ScreenDraw writes view rect + four mat4 + 16 bytes + sort byte into s_ctx views[viewId] (+0x10/+0x14/+0x20/+0x60/+0xA0/+0xE0/+0x120/+0x132), emits marker "ScreenDraw:<pass name>" (name std::string at pass +0x268 via sub_ebce5e0), binds material 0xe86d7f0 / state / uniforms / textures / buffers, and submits via 0xbcc38e0 (6gz [V]) | [V] |

## In / out resources (bloom down)

| offset | size | address | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc98310 | - | builder statics | - | Builder 0xbc98310 ("Bloom") declares DFDownSample + ThresholdedDownSample (name refs 0xbc99732 / 0xbc9978d [V xref str]); per its declaration (vv_group_builders.md line 58): textures T = AverageLuminance, Color0 (target), BlurPyramidTexture; uniforms U = ViewportScale, BloomParams; drawPacket 0xbc98db4; body ScreenDraw 0xbc04dc0. Out: downsampled/thresholded bloom mip (BlurPyramidTexture target). In/out NAMES are [I] — taken from the builder declaration, not re-read from the exe this run; the registration-site instructions and the executed body are [V]. | [I] |

## CLOSES?

CLOSES? NO — bloom down is proven this run (9 [V] registration-site rows + executed body ScreenDraw 0xbc04dc0 [V via rdis vt]; in/out names [I] from builder doc). The M1e item is not closed: the ordered pending bodies remain — next is bloom up 0xbc9bbd4 / 0xbc9bc28, then local exposure 0xbca2671, tail 0x568d480 / 0x568d750, RTX denoise UAV writes 0xbcc4b90, Fancy data-only sites, and the [I] deferred bodies.

## TOOL REQUESTS

None. (rdis dis/vt and xref str from docs/OPENCODE_BRIEF.md sufficed; no helper script written.)
