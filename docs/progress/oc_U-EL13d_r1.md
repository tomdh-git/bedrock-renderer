## NEXT
DONE

UNIT U-EL13d — L13d end sky / cubemap — 6ed (clones found, fields pending)
Goal: decode the END SKY and CUBEMAP description fields (the pending part of checklist item L13d). Clones are already found: EndSky thin clone 0x53707a0 (Sky group +0x370 tag 3), Cubemap thin clone 0x660b720 (Sky tag 2), LegacyCubemap 0x660b1a0 (Sky tag 4, fat). Only the field decode is in scope here.

Input data (read-only, already computed, not re-run):
- docs/data/listings/sky_producer_5369f60_536a2f4.txt  (covers EndSky clone 0x53707a0 region)
- docs/data/listings/sky_endsky_66587cf_6658b10.txt
- docs/data/listings/sky_endsky_6658e44_66590f6.txt
- docs/data/listings/sky_66580f0_6658ffc.txt
- docs/data/listings/sky_6658ffc_6659615.txt          (Cubemap body region per 6o: 0x6659615..0x665aee8)
- docs/data/listings/sky_celestial_66596a1_6659ee0.txt
- docs/data/listings/sky_heads_6656174_6656983.txt
- docs/functions/66560f0_sky_cases.md                  (visitor cases for sky tags, read-level)
- docs/BGFX_MAP.md 6o, 6w (clone/tag table), 6ee (clone kind/group/tag table)
- docs/data/producer_fields.txt                        (Cubemap + EndSky producer store offsets)

Format per rule: table rows name | rva or offset | size | verbatim `0xRVA  instr` proof line | [V]/[I]/[?]. Size from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). Meaning only if an instruction/string shows it, else '-'. One annotated row per distinct offset, all its sites listed. Appended in pieces after each piece.

## END SKY — RenderSkyDescription (0xB0), tag 3, thin clone 0x53707a0
Visitor reads proven [V] from listings sky_endsky_66587cf_6658b10.txt, sky_endsky_6658e44_66590f6.txt:

| Offset | Size | Site | `0xRVA  instr` | [V]/[I]/[?] | Meaning |
| es+0x00 | 8 | [rdi] | `0x665884d  mov r15,[rdi]; 0x6658eb8  mov rax,[rdi]` | [V] | mesh object pointer |
| es+0x08 | 8 | [rdi+8] | - | [I] | "SkyTexture" sampler data address (documented in sky_cases.md @0x6658a13; listing gap 0x6658b10-0x6658e44 not available) |
| es+0x18 | 2 | [rdi+0x18] | `0x6658eb3  movzx r15d,word ptr [rdi+0x18]` | [V] | u16; stored to [rbp+0x470], meaning [I] |
| es+0x1C | 16 | [rdi+0x1C] | `0x6658915  movups xmm0,[rdi+0x1C]` | [V] | SkyColor vec4 |
| es+0x2C | 16 | [rdi+0x2C] | `0x6658e80  movups xmm0,[rdi+0x2C]` | [V] | mat4 row 0 |
| es+0x3C | 16 | [rdi+0x3C] | `0x6658e8b  movups xmm0,[rdi+0x3C]` | [V] | mat4 row 1 |
| es+0x4C | 16 | [rdi+0x4C] | `0x6658e96  movups xmm0,[rdi+0x4C]` | [V] | mat4 row 2 |
| es+0x5C | 16 | [rdi+0x5C] | `0x6658ea1  movups xmm0,[rdi+0x5C]` | [V] | mat4 row 3 |
| es+0x6C | 8 | [rdi+0x6C] | `0x66589a3  lea r9,[rdi+0x6C]` | [V] | UV0Transform data address; size bounded by adjacency to +0xAC [I] |
| es+0xAC | 4 | [rdi+0xAC] | `0x6658aa1  movss xmm0,[rdi+0xAC]` | [V] | MinimumSkyLuminance float; only read when [rbp+0x540]==1 |

## CUBEMAP — RenderCubemapDescription (0xC0), tag 2, thin clone 0x660b720
Producer ctor 0x668eb10 + direct stores from docs/data/producer_fields.txt (clone 0x660b720). NO verbatim `0xRVA  instr` proof lines available in input data: no listing exists for producer 0x6606580, ctor 0x668eb10 body, or visitor body 0x6659615..0x665aee8. RVAs cited are from producer_fields.txt "first @" entries only.

| Offset | Size | Site | `0xRVA  instr` | [V]/[I]/[?] | Meaning |
| cb+0x00 | 8 | - | - | [?] | resolved texture ref via 0x4dfb570 (ctor 0x668eb10 r8 +0x00..+0x3C) [I] |
| cb+0x08 | 8 | - | - | [?] | SharedRef ctrl; store @0x660674b (producer_fields.txt only) [I] |
| cb+0x10 | 64 | - | - | [?] | mat4 transform[16]; store @0x6606bf6 (producer_fields.txt only) [I] |
| cb+0x50 | 2 | - | - | [?] | u16 value [I] |
| cb+0x52 | 1 | - | - | [?] | byte [I] |
| cb+0x60 | 8 | - | - | [?] | producer field; store @0x6606660 [I] |
| cb+0x68 | 1 | - | - | [?] | producer field; store @0x6606667 [I] |
| cb+0x70 | 8 | - | - | [?] | producer field; store @0x660666e [I] |
| cb+0x78 | 8 | - | - | [?] | producer field; store @0x6606675 [I] |
| cb+0x80 | 8 | - | - | [?] | producer field; store @0x660667c [I] |
| cb+0x88 | 8 | - | - | [?] | producer field; store @0x66065b1 [I] |
| cb+0x90 | 16 | - | - | [?] | producer field; store @0x66065aa [I] |
| cb+0xA0 | 16 | - | - | [?] | producer field; store @0x66065a3 [I] |
| cb+0xB0 | 16 | - | - | [?] | producer field; store @0x660659b [I] |

## Raw verification lines (verify_oc.py checks these against rdis dis output)

  0x665884d  mov r15,[rdi]
  0x6658eb8  mov rax,[rdi]
  0x6658eb3  movzx r15d,word ptr [rdi+0x18]
  0x6658915  movups xmm0,[rdi+0x1C]
  0x6658e80  movups xmm0,[rdi+0x2C]
  0x6658e8b  movups xmm0,[rdi+0x3C]
  0x6658e96  movups xmm0,[rdi+0x4C]
  0x6658ea1  movups xmm0,[rdi+0x5C]
  0x66589a3  lea r9,[rdi+0x6C]
  0x6658aa1  movss xmm0,[rdi+0xAC]

CLOSES? = NO — EndSky visitor-read fields are [V]-proven, but Cubemap fields (cb+0x08..cb+0xB0) have no verbatim `0xRVA  instr` proof line in any input data file (producer 0x6606580 / ctor 0x668eb10 / visitor body 0x6659615..0x665aee8 listings not available); not every pending field is proven by [V] rows. Single blocking fact: Cubemap producer store instructions not present in any input data file, so Cubemap fields cannot be [V]-proven.
