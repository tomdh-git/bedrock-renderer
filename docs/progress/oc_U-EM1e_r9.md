## NEXT
DONE

# U-EM1e: M1e Pass lambdas (L6) — 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources

This run covers bloom down body 0xbc99739 / 0xbc99794 (step 2 of ordered pending bodies).

## Verified rows — bloom down hash-static registration sites (NOT code bodies; executed body is the shared ScreenDraw 0xbc04dc0)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|---------------------|-------------------------|---------|-----|
| 0xbc99739 | 8 | imm | `0xbc99739  mov rdx,0x34E743CD5E04564D` | 8-byte FNV-1 hash constant loaded into rdx, immediately before registration call 0x76AD00; hash-static registration site (lea rcx,sub_bc9ac80 then call 0xE935740 registers a bloom body) | [V] |
| 0xbc99794 | 8 | imm | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | 8-byte FNV-1 hash constant loaded into rdx before registration call 0x76AD00; hash-static registration site registering bloom body sub_bc9ad10 | [V] |
| 0xbc9978d | 8 | [data_f5d9717] | `0xbc9978d  lea r8,[0xF5D9717]` | loads pointer to string "ThresholdedDownSample" (data_f5d9717) used as the registration name arg in the bloom down site | [V] |

## Resource mapping for bloom down (from the registration site)

- Out resource: the registered bloom downsample texture/body (name "ThresholdedDownSample" at data_f5d9717), registered via call 0x76AD00 with body sub_bc9ac80. The executed render body is the shared ScreenDraw body 0xbc04dc0 (prior mapping 6gz: declare 0xbbbd3d0, build 0xbc37320, shared execute 0xbc04dc0, submit 0xbcc38e0) — [I], vtable slot re-verification pending in this file.
- No separate code body exists at 0xbc99739 / 0xbc99794; they are hash-static registration stubs (r4 correction).

## CLOSES?

CLOSES? NO — bloom down is proven as a hash-static registration site (3 [V] rows above), but M1e requires every one of the 35 VV/RTX lambdas + Fancy pass bodies with in/out resources; only bloom down is covered this run. Remaining pending: bloom up 0xbc9bbd4/0xbc9bc28, local exposure 0xbca2671, tail 0x568d480/0x568d750, RTX denoise UAV writes 0xbcc4b90, Fancy pass bodies (0xF25C9B0/0xF25C9E0/0xF440770/0xF43E9C0 are DATA/vtables, no code body), deferred bodies (only 0xbc2c590 verbatim [V], others [I structure]), and the ScreenDraw 0xbc04dc0 executed-body vtable slot not yet re-verified in this file.
