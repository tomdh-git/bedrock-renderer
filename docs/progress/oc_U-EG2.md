## NEXT
DONE

# U-EG2: G2 Variant axes + (pass, flags) permutation keys (6ap); runtime selection code

File-format side (axes/passes/variants/shader records in .material.bin) is G1a + BGFX_MAP 6ap [V] — done. Pending part of G2: the runtime code that builds/uses a (pass, flags) permutation key to select a shader variant/program at draw time.

## What was proven (runtime selection machinery)

6ap (BGFX_MAP.md 725-738): each .material.bin pass declares pass name, 14-char enable mask, u16 axisCount, per axis: axis name + valueCount + value strings (Off/On/Multi/Emissive/EmissiveOnly); variant records: u32 hash, u16 flagCount, (axisName,value) pairs, then per-stage shader records. "Runtime: loader builds the permutation table keyed by (pass, flag set); FrameBuilder extractors choose a variant by setting flag values (Instancing, Fancy) before submit; draw program index in the sort key (6ao) indexes the result."

The runtime selection code located and decoded:

1. **sub_675e440 (0x675e440, size 0x2000)** = material/pass resolver: get-or-create lookup in a hash map (`a0` = material map object) keyed by a 16-byte key {u64 part1, u64 part2}; bucket = FNV-1 (offset basis 0xCBF29CE484222325, prime 0x100000001B3) of key part2, masked by `a0+0x70`; chain walk compares stored node keys at `node+0x10`/`node+0x18`; on hit returns the material/pass node, on miss delegates to sub_567d280 which allocates a 0x38-byte node and inserts it. Out param: `[rsi]=node ptr, [rsi+8]=0/1 found flag`. Callers include the terrain extractor 0x66ea3d0 (x5, e.g. 0x66ea88f), item visitor 0x6646980 (0x6646eab), Sky 0x66560f0, UI 0x6664a00, and others (ripscan lists 34 xrefs). So pass/material selection at runtime is by **name hash**, resolved through this map.

2. **sub_567d280 (0x567d280, size 0x2000)** = the map's get-or-create node allocator: same FNV-1 hash, bucket mask at `a0+0x30`, bucket base at `a0+0x18`, allocates 0x38-byte nodes (`mov edx,0x38`), links into the bucket chain, returns node ptr.

3. **Sort key -> program (BGFX_MAP 6ao, [V by disassembly])**: sort key `(key >> 0x15) & 0x7FF` = program index (11 bits) -> `this+0xB62178 + idx*0xF8` program record (0xF8 stride); program object signature u32 at `+0xA8` (four signed bytes) is hashed (`...*0xFC5D1543EC5F01`) into the PSO cache bucket chain (`bgfxBlock+0x48..0x50`) walked at 0xe822540 comparing node key `[node+0]`.

## What remains unproven (the blocking gap)

The code that constructs a **(pass, flags) permutation key from axis values** (e.g. Instancing=On, Fancy=Off) and **selects a variant record / program index** at runtime was not located. Axis names ("Instancing","Fancy","Change_Color",...) exist only as .material.bin data strings (xref finds them only in the caps dump 0x660ecd0); no runtime code compares them as strings or combines pass+flag ordinals into a lookup key. What IS proven is name-based pass/material resolution (0x675e440/0x567d280) and sort-key program indexing (6ao) — neither is keyed by the flag set.

## Verbatim proof lines (from rdis, verified)

0x675e551  and rdx,[r14+0x70]
0x675e555  mov rcx,[r14+0x48]
0x675e559  mov r8,[r14+0x58]
0x675e577  cmp rax,[r15+0x10]
0x675e58f  cmp r8,[r15+0x18]
0x675e5a7  call 0x567D280
0x675e879  mov [rsi],rcx
0x675e87c  mov [rsi+8],rax
0x567d33b  mov rdx,[rdi+0x30]
0x567d346  mov r8,[rdi+0x18]
0x567d360  cmp rax,[rcx+0x10]
0x567d387  mov [rsi],rcx
0x567d3c0  mov edx,0x38

## Annotated field map (a0 = material map object; node = hash node; rsi = out buffer)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
| 0x70 | 8 | a0+0x70 ([r14+0x70]) | `0x675e551  and rdx,[r14+0x70]` | bucket mask (bucket_count-1) for material hash map | [V] |
| 0x48 | 8 | a0+0x48 ([r14+0x48]) | `0x675e555  mov rcx,[r14+0x48]` | bucket-array end sentinel | [V] |
| 0x58 | 8 | a0+0x58 ([r14+0x58]) | `0x675e559  mov r8,[r14+0x58]` | bucket-array base pointer | [V] |
| node+0x10 | 8 | node+0x10 ([r15+0x10] / [rcx+0x10]) | `0x675e577  cmp rax,[r15+0x10]` ; `0x567d360  cmp rax,[rcx+0x10]` | stored key part 1 compared on chain walk | [V] |
| node+0x18 | 8 | node+0x18 ([r15+0x18]) | `0x675e58f  cmp r8,[r15+0x18]` | stored key part 2 compared on chain walk | [V] |
| 0x30 | 4 | a0+0x30 ([rdi+0x30]) | `0x567d33b  mov rdx,[rdi+0x30]` | map bucket mask (insert path) | [V] |
| 0x18 | 8 | a0+0x18 ([rdi+0x18]) | `0x567d346  mov r8,[rdi+0x18]` | map bucket-array base (insert path) | [V] |
| node size | - | - | `0x567d3c0  mov edx,0x38` | allocated hash node = 0x38 bytes | [V] |
| out+0 | 8 | out+0 ([rsi]) | `0x675e879  mov [rsi],rcx` | out param: resolved node pointer | [V] |
| out+8 | 8 | out+8 ([rsi+8]) | `0x675e87c  mov [rsi+8],rax` | out param: found flag (0/1) | [V] |
| sort-key program idx | - | - | - | `(key>>0x15)&0x7FF` = program index -> `this+0xB62178+idx*0xF8` program record (BGFX_MAP 6ao) | [V] |

## CLOSES?

NO — blocking fact: the runtime code that builds a (pass, flags) permutation key from axis values and selects a variant/program index is not located; axis names exist only in .material.bin data, no runtime pass+flag key construction found. Only name-based pass/material resolution (0x675e440 + 0x567d280) and sort-key program indexing (6ao) are proven.

## Open questions

[UNVERIFIED: where the extractor sets per-axis flag values (Instancing/Fancy ordinals) before calling 0x675e440 — not seen in 0x66ea3d0/0x6646980 call sites]
[UNVERIFIED: whether the material node returned by 0x675e440 carries the selected variant/program index, or a separate variant table is consulted]

## TOOL REQUESTS

None
