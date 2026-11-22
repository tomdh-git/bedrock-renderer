## NEXT
DONE

# U-EM1e: M1e Pass lambdas (L6) — 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources

## Scope (from ORCHESTRATOR HINT)

Already verified (reference docs, not re-derived here):
- vv_lambda_bodies.md: all VV/RTX pass lambda bodies; ScreenDraw shared body 0xbc04dc0; RTX 0xbc080c0->0xbcc4b90; TAAU 0xbc8cfd0; voxel 0xbc0b240/0xbc0ac20; ColorPostProcess in/out.
- pass_bodies.md: 3 body shapes; DirectionalLightingPass 0xbc2cd20; submitPass 0xbcc38e0 variant corrected.
- vv_rtx_pass_table.md: group builder -> body -> name table with FNV-1 hashes.
- BGFX_MAP.md 6gz/6ha/6hb/6hr verified.

Remaining (this unit): fix 2 verify_oc mismatches (0x568cdbe, 0x568d0b8); read pending hash/registration sites (bloom 4, local exposure 1); read RTX denoise body 0xbcc4b90; read Fancy ctor sites 0xBC38AB0/0xBC01E80 (vtable DATA at 0xF440770/0xF43E9C0); confirm deferred bodies 0xbc2c590/0xbc2d550/0xbc2dd20/0xbc2eb50/0xbc2f4a0 template; tail sites 0x568d480/0x568d750.

## Verified rows (fixed mismatches + newly read sites)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|---------------------|-------------------------|---------|-----|
| 0x568cdbe | 8 | [rbx] | `0x568cdbe  mov rbx,rdx` | copy pass-object ptr rdx->rbx; fixes wrong claim `movq xmm0,[rbx+f8]` (the movq is at 0x568cdde) | [V] |
| 0x568cdde | 16 | [rbx+0xF8] | `0x568cdde  movq xmm0,[rbx+0xF8]` | load rect x/y from pass object +0xF8; offset +0xf8 confirmed correct | [V] |
| 0x568d0b8 | 2 | [rdx+0x2A] | `0x568d0b8  movzx edx,word ptr [rdx+0x2A]` | load word field at +0x2A; fixes wrong claim `movzx r10d,word ptr [r8+2c]` (reg edx not r10d, off +0x2a not +0x2c) | [V] |
| 0xbc99739 | 8 | imm | `0xbc99739  mov rdx,0x34E743CD5E04564D` | bloom DFDownSample FNV-1 hash static (builder registration; body is ScreenDraw 0xbc04dc0, not a separate body) | [V] |
| 0xbc99794 | 8 | imm | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | bloom ThresholdedDownSample FNV-1 hash static | [V] |
| 0xbc9bbd4 | 8 | imm | `0xbc9bbd4  mov rdx,0xF91FF9E312C7E556` | bloom DFUpSample FNV-1 hash static | [V] |
| 0xbc9bc28 | 8 | imm | `0xbc9bc28  mov rdx,0x7ADA5C0EF1420F87` | bloom BloomBlend FNV-1 hash static | [V] |
| 0xbca2671 | 8 | imm | `0xbca2671  mov rdx,0x15C5632A1EBCD723` | local exposure ApplyLocalExposure FNV-1 hash static | [V] |
| 0xbc2c5e8 | 16 | [rbx+0x88] | `0xbc2c5e8  movq xmm0,[rbx+0x88]` | CausticsMultiplierPass 0xbc2c590: load rect x/y from pass object +0x88 | [V] |
| 0xbc2c5f8 | 4 | [rbx+0x8C] | `0xbc2c5f8  movd xmm1,[rbx+0x8C]` | CausticsMultiplierPass 0xbc2c590: load rect w/h from pass object +0x8C | [V] |
| 0xbc2c648 | 8 | call 0xEBCE390 | `0xbc2c648  call 0xEBCE390` | CausticsMultiplierPass 0xbc2c590: memcpy view matrix +0x9C (4x memcpy via 0xebce390 for mats +0x08/+0x48/+0x9C/+0xDC) | [V] |
| 0xbc0810b | 16 | [rbx+0x88] | `0xbc0810b  movq xmm0,[rbx+0x88]` | RTX driver 0xbc080c0: load rect x/y from pass object +0x88 | [V] |
| 0xbc0811b | 4 | [rbx+0x8C] | `0xbc0811b  movd xmm1,[rbx+0x8C]` | RTX driver 0xbc080c0: load rect w/h from pass object +0x8C | [V] |
| 0xbc08166 | 8 | call 0xEBCE390 | `0xbc08166  call 0xEBCE390` | RTX driver 0xbc080c0: memcpy view matrix +0x9C via 0xebce390 | [V] |
| 0xbcc4b90 | 8 | [rcx] | `0xbcc4b90  push rbp` | RTX denoise driver body 0xbcc4b90: prologue; calls 0xc28f000 (tex binder), 0xbcc1a30, 0xeec6ec0; per-pass outputs not named in 0x1E8 params block | [V code, I outputs] |
| 0xbc38ab0 | 1 | [none] | `0xbc38ab0  push rsi` | Fancy clear-task ctor 0xBC38AB0: prologue push rsi | [V] |
| 0xbc38abb | 8 | [rcx] | `0xbc38abb  lea rax,[0xF440770]` | load vtable addr 0xF440770; `mov [rcx],rax` at 0xbc38ac2 installs it as vtable ptr; Fancy clear task vtable DATA at 0xF440770 | [V] |
| 0xbc38ac2 | 8 | [rcx] | `0xbc38ac2  mov [rcx],rax` | write vtable ptr 0xF440770 to [rcx] (pass object +0x0) | [V] |
| 0xbc01e80 | 1 | [none] | `0xbc01e80  push rsi` | Fancy TerrainAtlasBlit ctor 0xBC01E80: prologue push rsi | [V] |
| 0xbc01e8b | 8 | [rcx] | `0xbc01e8b  lea rax,[0xF43E9C0]` | load vtable addr 0xF43E9C0; `mov [rcx],rax` at 0xbc01e92 installs it as vtable ptr; Fancy TerrainAtlasBlit vtable DATA at 0xF43E9C0 | [V] |
| 0xbc01e92 | 8 | [rcx] | `0xbc01e92  mov [rcx],rax` | write vtable ptr 0xF43E9C0 to [rcx] (pass object +0x0) | [V] |
| 0x568d797 | 2 | [rcx+0x2C] | `0x568d797  movzx ecx,word ptr [rcx+0x2C]` | tail site 0x568d750: loads word field at +0x2C (confirms +0x2c used at this site; mismatch at 0x568d0b8 was +0x2a, different site) | [V] |

## Items that are DATA, not code bodies ([?])

- 0xF25C9B0: rdis yields 'bad' instructions (jo short 0xf25c970, insb, add [rax],al...) = DATA, not a Fancy clear task body [?]
- 0xF25C9E0: 'bad' instructions (xor dl,al, insb...) = DATA [?]
- 0xF440770: `mov al,0x8A; ret` then garbage = vtable DATA (installed as vtable ptr by 0xBC38AB0 via `mov [rcx],rax`) [?]
- 0xF43E9C0: garbage = vtable DATA (installed by 0xBC01E80 via `mov [rcx],rax`) [?]

## Deferred bodies — same template, structure [V] (instruction-level not fully read for each)

All five deferred bodies (0xbc2c590 CausticsMultiplierPass, 0xbc2d550 DiscreteIndirectCombinedLightingPass, 0xbc2dd20 SurfaceRadianceUpscalePass, 0xbc2eb50 WaterExtinction, 0xbc2f4a0 WaterSurface) share the template: view setup from this=rbx; rect +0x88/+0x8C; mats +0x08/+0x48/+0x9C/+0xDC; four memcpy via 0xebce390; `movq xmm0,[rbx+0x88]`; `movd xmm1,[rbx+0x8C]`. Verified verbatim at 0xbc2c590 (CausticsMultiplierPass) above; others inferred identical [I structure].

## CLOSES?

CLOSES? NO — Fancy pass bodies 0xF25C9B0/0xF25C9E0/0xF440770/0xF43E9C0 are DATA (vtables/bad disassembly), not code bodies — no Fancy pass body code exists at those RVAs. Bloom/local-exposure "bodies" are hash-static registration sites; the real body is ScreenDraw 0xbc04dc0. Not all deferred bodies have full [V] instruction-level reads (only 0xbc2c590 verified verbatim; others [I structure]).
