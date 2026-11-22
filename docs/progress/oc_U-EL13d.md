## NEXT
DONE

# L13d end sky / cubemap — description fields (unit U-EL13d, docs/progress/oc_U-EL13d.md)

Goal: close checklist item "L13d end sky / cubemap — 6ed (clones found, fields pending)" (docs/RENDER_CHECKLIST.md line 381). The pending part is the description fields. docs/BGFX_MAP.md section 6ed lists the four Sky-group clones found (EndSky tag 3 @0x53707a0, CelestialBody tag 7 @0x5370b20, Cubemap tag 2 @0x660b720, LegacyCubemap tag 4 @0x660b1a0, all inserting through Sky vslot 0x370) but leaves every field pending. This unit decodes the fields of EndSky (tag 3) and Cubemap (tag 2) — the two names in the item line — from the Sky visitor 0x66560f0 (tag-2 case head 0x66562d5 into shared body 0x6659615; tag-3 case head 0x665649c, body 0x66587cf..0x66590a5). CelestialBody and LegacyCubemap fields are documented elsewhere (docs/functions/66560f0_sky_cases.md §6, 66560f0_sky_visitor.md §3) and are not named in this item line, so they are out of scope here (do ONLY the part marked pending).

Input data read fully:
- docs/BGFX_MAP.md sections 6d, 6ed, 6w (Sky clone table + tags)
- docs/functions/53707a0.md (EndSky thin clone), 660b720.md (Cubemap thin clone), 66560f0_sky_cases.md (EndSky tag-3 field table), 66560f0_sky_visitor.md (Cubemap tag-2 field table), 668c910.md (RenderSkyDescription ctor 0x668c910), 668eb10.md (RenderCubemapDescription ctor 0x668eb10)
- docs/data/producer_fields.txt (Cubemap/EndSky producer sections: ctor 0x668eb10 @6606d13; ctor 0x668c910 @5369f7b)
- docs/data/listings/sky_heads_6656174_6656983.txt, sky_endsky_66587cf_6658b10.txt, sky_endsky_6658e44_66590f6.txt, sky_66580f0_6658ffc.txt, sky_6658ffc_6659615.txt
- docs/data/live_desc_sky_light_effect_1.26.62.01.txt (live capture: only tags 0/5/6/7 fired; Cubemap tag 2 and EndSky tag 3 did not fire — no live rows for them, static only)

Method: one row per distinct description offset; size from the instruction (movups/movaps 16 B, qword load 8 B, movss 4 B, word 2 B, byte 1 B, lea = address taken only, size 0); every proof line is a verbatim `0xRVA  instr` copied from rdis dis output and re-checked against the exe; meaning is given only where an instruction or string data shows it, otherwise '-'; [V] = offset/size/site proven in disassembly, [I] = meaning or extent inferred from structure, no [?] rows.

## Field map

### EndSky — RenderSkyDescription (0xB0; built by ctor 0x668c910 per docs/functions/668c910.md, inserted with tag 3 by thin clone 0x53707a0; visitor tag-3 case head 0x665649c, body 0x66587cf..0x66590a5 per docs/functions/66560f0_sky_cases.md §3)

| Offset | Size | Field | `0xRVA  instr` proof site(s) | Meaning (shown by instruction/string data) | Tag |
|---|---|---|---|---|---|
| EndSky +0x00 | 8 | source | `0x665884d  mov r15,[rdi]`; `0x6658eb8  mov rax,[rdi]` | mesh object ptr; its +0x58/+0x60 give the item count, +0x1B0/+0x1B8 the shared_ref, +0x1D0/+0x1D4 flags (mesh-object field layout [I]) | [V] |
| EndSky +0x08 | 0 (lea, no deref) | texture | `0x6658a13  lea r8,[rdi+8]` | address of the texture shared-ref, handed as sampler "SkyTexture" data to 0xBCABA00; never dereferenced in this case | [V] |
| EndSky +0x18 | 2 | flags | `0x6658eb3  movzx r15d,word ptr [rdi+0x18]` | u16 → r15w → [rbp+0x470] pass-record word; record-word semantics (draw-order/flag) are not named by code [I] | [V] |
| EndSky +0x1C | 16 | color | `0x6658915  movups xmm0,[rdi+0x1C]` | vec4 → uniform "SkyColor" (string key data_129f9d08 [V]) | [V] |
| EndSky +0x2C | 16 | matrix row 0 | `0x6658e80  movups xmm0,[rdi+0x2C]` | mat4 row 0 → [rbp+0x170] | [V] |
| EndSky +0x3C | 16 | matrix row 1 | `0x6658e8b  movups xmm0,[rdi+0x3C]` | mat4 row 1 → [rbp+0x180] | [V] |
| EndSky +0x4C | 16 | matrix row 2 | `0x6658e96  movups xmm0,[rdi+0x4C]` | mat4 row 2 → [rbp+0x190] | [V] |
| EndSky +0x5C | 16 | matrix row 3 | `0x6658ea1  movups xmm0,[rdi+0x5C]` | mat4 row 3 → [rbp+0x1A0] | [V] |
| EndSky +0x6C | 0 (lea; extent 0x40 B [I]) | uvTransform | `0x66589a3  lea r9,[rdi+0x6C]` | address passed as uniform "UV0Transform" data to 0x56D55E0 (string key 0x129F9D28 [V]); extent 0x40 B by adjacency to +0xAC [I] | [I] |
| EndSky +0xAC | 4 | value | `0x6658aa1  movss xmm0,[rdi+0xAC]` | float → uniform "MinimumSkyLuminance" (string key 0x129F9D38 [V]); emitted only when [rbp+0x540]==1, i.e. frameCtx+0x70==1 (head 0x665649c `mov eax,[rsi+0x70]`, stored 0x66564a9 `mov [rbp+0x540],eax`) | [V] |

### Cubemap — RenderCubemapDescription (0xC0; built by ctor 0x668eb10 with producer 0x6606580 per docs/functions/668eb10.md and docs/data/producer_fields.txt, inserted with tag 2 by thin clone 0x660b720; visitor tag-2 case head 0x66562d5, shared body 0x6659615 per docs/functions/66560f0_sky_visitor.md §2)

| Offset | Size | Field | `0xRVA  instr` proof site(s) | Meaning (shown by instruction/string data) | Tag |
|---|---|---|---|---|---|
| Cubemap +0x00 | 8 | texture | `0x66562d5  mov r14,[rdi]`; `0x665973d  mov r9,[rdi]`; `0x6656306  lock inc word ptr [r14+0x10]`; `0x665630c  movzx eax,byte ptr [r14+0x12]` | texture/resource object ptr (read in the head and again in the shared body); the last two sites read fields of *desc+0x00 (refcount word, ready bit0), not of the description itself | [V] |
| Cubemap +0x08 | 0 (lea, no deref) | ctrl | `0x66597ba  lea rcx,[rdi+8]` | shared_ref ctrl address taken; never dereferenced for Cubemap | [V] |
| Cubemap +0x10 | 16 | transform row 0 | `0x665a22a  movups xmm6,[rdi+0x10]` | vec4 → [rbp+0x4E0], part of the 4-vec4 block copied when +0x52==1 | [V] |
| Cubemap +0x20 | 16 | transform row 1 | `0x665a235  movups xmm7,[rdi+0x20]` | → [rbp+0x4F0] | [V] |
| Cubemap +0x30 | 16 | transform row 2 | `0x665a240  movups xmm8,[rdi+0x30]` | → [rbp+0x500] | [V] |
| Cubemap +0x40 | 16 | transform row 3 | `0x665a24d  movups xmm9,[rdi+0x40]` | → [rbp+0x510] | [V] |
| Cubemap +0x50 | 2 | value | `0x665a261  mov di,[rdi+0x50]` | u16 into the pass record | [V] |
| Cubemap +0x52 | 1 | guard | `0x665a220  cmp byte ptr [rdi+0x52],1` | ==1 selects this 4-vec4 block shape; otherwise the second shape at 0x665a411..0x665a448 | [V] |

Note on the Cubemap +0x10..+0x4F block: guard byte +0x52==1 (0x665a220) selects this shape; the block is written to [rbp+0x4E0..0x51F] with [rbp+0x520]=0 (0x665a25a `mov byte ptr [rbp+0x520],0`) before the DrawState constants (0x665a27f..0x665a2aa).

## Residual (non-blocking)
- EndSky +0x18: offset/size/read site [V]; the record-word meaning ("draw-order/flag") is not named by code [I].
- EndSky +0x6C: address-taking [V]; the 0x40 B extent is by adjacency to +0xAC [I].
- CelestialBody (tag 7) and LegacyCubemap (tag 4) fields are not part of this item line ("end sky / cubemap"); they are covered in the sky visitor dossiers cited above.
- Producer field stores (docs/data/producer_fields.txt) agree with the visitor reads above without needing quotes here (EndSky ctor 0x668c910 writes +0x00..+0xAC per docs/functions/668c910.md; Cubemap ctor 0x668eb10 writes +0x10..+0x52 per docs/functions/668eb10.md).

## CLOSES?
YES — the pending part of L13d ("fields pending") is closed for both named descriptions: every EndSky (tag 3) and Cubemap (tag 2) field offset, size and read site is proven by [V] rows whose `0xRVA  instr` lines match rdis dis of the exe (verify_oc clean). The only [I]-qualified claims are two meaning glosses (mFlags record-word semantics; uvTransform extent), which do not leave any field undecoded.

## TOOL REQUESTS
None
