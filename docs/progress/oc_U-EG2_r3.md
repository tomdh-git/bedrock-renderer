## NEXT
DONE

# U-EG2: G2 Variant axes + (pass, flags) permutation keys (6ap); runtime selection code

File-format side (axes, passes, variants, shader records in .material.bin) is G1a + BGFX_MAP 6ap [V] — done.
Pending part of G2: the runtime code that builds/uses a (pass, flags) permutation key to select a shader variant/program at draw time.

BGFX_MAP 6ap step 9: each variant record = u32 hash, u16 flagCount, (axisName,value) pairs, then per-stage shader records; loader keeps one shader per stage per variant. BGFX_MAP 6gy: per variant the program handle is stored at variant+0x1C as {u16 handle, valid bit 16}.

## Runtime selection code located

The runtime selection is a hash-map lookup `sub_bcc7ce0(object, out, global)` (0xbcc7ce0, 17 xrefs) called from pass bodies at draw time, e.g. the submitPass inline-transform path `sub_bcc3b90` (0xbcc3b90). `sub_e879eb0` (0xe879eb0) derives an FNV-1 64 key from the pass object; `sub_bcc7ce0` looks it up in the object's bucket map (bucket base [rdi+0x118], mask [rdi+0x130]) and returns node+0x1C (the variant program handle) at out+0, the node pointer at out+8, and a found flag at out+0x10.

## Field/proof table (one row per distinct offset, all sites listed)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
| node+0x1C | 4 | [rcx+0x1C] | `0xbcc7e34  mov eax,[rcx+0x1C]` | variant node payload: program handle u32 (low 16 bits = bgfx program handle) | [V] |
| out+0 | 4 | [rsi] | `0xbcc7e3b  mov [rsi],eax` | out param: resolved program handle | [V] |
| out+8 | 8 | [rsi+8] | `0xbcc7e3d  mov [rsi+8],rcx` | out param: resolved variant/node pointer | [V] |
| out+0x10 | 1 | [rsi+0x10] | `0xbcc7e47  mov [rsi+0x10],al` | out param: found flag (1 = key present in map) | [V] |
| map+0x130 | 4 | [rdi+0x130] | `0xbcc7de7  and r8,[rdi+0x130]` | bucket mask (bucket_count-1) of the pass-object hash map | [V] |
| node+0x10 | 8 | [rcx+0x10] | `0xbcc7e0a  cmp rax,[rcx+0x10]` | stored node key compared against the derived key | [V] |
| bucket+0x8 | 8 | [r9+r8+8] | `0xbcc7e00  mov rcx,[r9+r8+8]` | bucket chain head node pointer | [V] |
| FNV prime | 8 | rbx imm | `0xe87a0b7  mov rbx,0x100000001B3` | FNV-1 64 prime used by sub_e879eb0 key derivation | [V] |
| FNV basis | 8 | rdx imm | `0xe87a125  mov rdx,0xCBF29CE484222325` | FNV-1 64 offset basis used by sub_e879eb0 key derivation | [V] |
| key-buffer byte | 1 | [rsi+rcx] | `0xe87a160  movzx r9d,byte ptr [rsi+rcx]` ; `0xe87a168  imul r9,rbx` | FNV-1 step: load a byte of the derived key buffer, xor into hash, multiply by prime | [V] |
| global+0x10 | 8 | [r8+0x10] | `0xbcc7ced  cmp qword ptr [r8+0x10],0` | global map object enable flag (data 0x12AE2840+0x10) gates the lookup | [V] |

## Caller proof (submitPass consumes the out params)

submitPass inline-transform `sub_bcc3b90` (0xbcc3b90): `0xbcc3bea  call 0xBCC7CE0` (rcx = [rbp+0x60] pass object, rdx = &[rbp-0x28] out, r8 = 0x12AE2840 global map object); `0xbcc3bef  cmp byte ptr [rbp-0x18],1` checks out+0x10 found flag (jne → miss, return 0); `0xbcc3c05  cmp word ptr [rbp-0x28],0xFFFF` checks out+0 program handle != 0xFFFF (valid). 17 direct callers of 0xbcc7ce0 (pass bodies ClusterLights 0xbc5bad0, voxel combine 0xbc0b240, submitGeometry list 0xbcc39b0, submitPass 0xbcc3b90, MaterialInstance::initFromMaterial 0xbcc7f20, …).

## Interpretation

0xbcc7ce0 is the runtime permutation selection: given a pass object, sub_e879eb0 derives an FNV-1 64 key from it (basis 0xCBF29CE484222325, prime 0x100000001B3 [V]) and the bucket map returns the matching variant node; node+0x1C is the variant's program handle [V]. This is the pass → program-handle half of the (pass, flags) selection, executed per pass at draw time [V via 17 xrefs]. The variant's program handle at node/variant+0x1C is corroborated by BGFX_MAP 6gy.

## CLOSES?
NO — blocking fact: the (pass, flags) → permutation-key composition is only partially proven. The FNV-1 64 hashing of a pass-object-derived buffer is verified [V] and node+0x1C = program handle is verified [V], but the code that combines the per-axis flag values (axis ordinals such as Instancing/Fancy/Change_Color/Emissive/MaskedMultitexture) into the key buffer consumed by sub_e879eb0 was not located, and where instance active flags select among a pass's multiple variants at runtime was not located. So the flag-axis selection half of "(pass, flags)" remains open.

## Open questions
[UNVERIFIED: 0xe879eb0 which bytes of the pass object (including any flags field) are hashed into the permutation key]
[UNVERIFIED: where instance active flags (defines map / MaterialInstance+0x2A8) select among a pass's multiple variants at runtime]

## TOOL REQUESTS
None
