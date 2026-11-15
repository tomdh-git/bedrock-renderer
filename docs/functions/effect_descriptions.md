# Effect-group descriptions (1.26.62.01)

Effect group: vslot 0x360, wrapper 0x666aa00, visitor 0x666aca0 (spans 0x666aca0..0x667191c, ret 0x667005b), jump table 0xF2BF49C, 9 cases.
Tags: 0 FlameBillboard, 1 BlitFlipbook, 2 Particle, 3 PlayerVision, 4 Shadow, 5 FadeToBlack, 6 AimAssistHighlight, 7 FullscreenEffect, 8 EditorHighlight.
Header with offsetof asserts: src/sdk/mc/deps/minecraft_renderer/framebuilder/EffectDescriptions.h (could not be compile-checked, no compiler on this box; offsets checked by hand against the listings).
Listings: docs/data/listings/effect_*.txt (dumplist.py). Tags: [V] seen in a listing and re-run with rdis, [I] inference.

Visitor registers: r15 = description, r12 = frame ctx, rbx = rcx.

## 1 Visitor heads [V]

0x666ad04  mov rcx,rbx
0x666ad88  mov rcx,rbx
0x666ad3b  mov rdx,[r15]
0x666adbf  movzx r13d,byte ptr [r15]
0x666ae72  mov rax,[r15+0x78]
0x666b6cf  mov rax,[r15+0x10]
0x666b6d3  mov r14,[r15+0x18]

- Case 0 (0x666ad04) and case 2 (0x666ad88) restore registers and tail-jump to 0x673D150 (Flame) and 0x67417F0 (Particle) with r8 = description.
- Case 4 Shadow (0x666ad3b): needs [[desc]+0x28], +0x38, +0x48 non-zero (else exit 0x6670032); then `[r12+0x70]==1` -> 0x66A9D50 else 0x66A6830.
- Case 3 PlayerVision (0x666adbf): copies byte +0 and 16 bytes at +4 into a 0x14-byte element of the pass vector pass+0x330/0x338/0x340, then appends one 0xC8 record (qword +0 = 0x0400000000000000, word +0x84 = index, count tag 0x4A) via the shared tail 0x666caeb.
- Case 1 BlitFlipbook: material "Flipbook"; loop over {count at +0x10, data at +0x18}, stride 0x40.

## 2 Particle (tag 2) [V]

Thin clone 0x5B8D520 -> variant {desc, tag 2}, vslot 0x360; producers 0x5B8C2B0 and 0x6B550B0 build the description with ctor 0x668C220.

0x668c225  mov [rcx],rdx
0x668c395  mov [rax+0x93],r10b
0x668c3b0  mov [rax+0xA8],ecx
0x5b8d594  mov byte ptr [rbp+0x18],2
0x6743061  cmp byte ptr [rcx+0x28],1
0x67433c9  movzx eax,byte ptr [r11+0x93]
0x6745102  mov r14w,[rcx+0x94]

Layout (sizeof 0xB0): +0 mesh; +0x08/+0x18/+0x30 SharedRef {obj,ctrl} (ParticleTexture, MERS, Normal); +0x28 MERS flag byte; +0x40 byte (stored only); +0x48/+0x58 SharedRef (stored only); +0x68 dword (stored only); +0x6C FogColor vec4; +0x7C FogAndDistanceControl vec4; +0x8C..0x92 seven flag bytes (read: +0x8C, +0x8D, +0x91); +0x93 mode byte (1->2, 2->1); +0x94 u16 flags (DrawArgs helper 0x67450A0); +0x98 MERSUniforms vec4 used only when byte +0xA8 == 1.
Exits: no mesh / hasDrawableData false -> 0x67439b9; ret 0x67439cc.
Corrections: (a) ParticleSkyExtractors.h `0x74` "kFlagPointLight" is a frame-ctx byte (0x67419a5 `and sil,[rdi+0x74]`, rdi = ctx), not a description field; (b) the +0x20/+0x28 qword reads at 0x6741cea/0x6741cf7 are r8 reuse (key block), the real +0x28 read is the byte at 0x6743061.

## 3 FlameBillboard (tag 0) [V]

Fat clone 0x594CBE0 (post step of ActorRenderDispatcher::render 0x594C5C0, call 0x594c993) -> ctor 0x668B160 (call 0x594eaa9).

0x668b166  mov [rcx],rdx
0x668b31c  mov [rax+0xBC],bl
0x668b3f0  mov [rax+0xF2],dx
0x594eb1f  mov byte ptr [rbp+0x328],0
0x594eb29  mov rax,[rax+0x360]
0x6741210  movzx ecx,word ptr [rax+0xF2]

Layout (0xF8): +0 mesh; +0x08..0x47 mat4 (read by record helper 0x67411B0 as four movups); +0x48 FlameAtlas ref; +0x58 MERS ref, +0x68 byte; +0x70 Normal ref, +0x80 enable byte; +0x88/+0x98 refs (stored only); +0xA8 vec4 PBR (metalness, emissive, roughness, subsurface); +0xB8 dword (byte==1 gates PBR); +0xBC fog-override byte; +0xC0 UVOffset; +0xC8 FogColor; +0xD8 FogAndDistance (+0xE0 pair); +0xE8 TileLightIntensity; +0xF0 dithering; +0xF2 u16 (record word). ret 0x673f505.
Correction: descscan "+0x10 dword @0x673ec36" is `mov ecx,[r8+0x10]` with r8 reused, not a description read.

## 4 PlayerVision (tag 3) [V]

Producer 0x53E62B0 (matches Descriptions.h, sizeof 0x14): +0 byte (night vision id 0x10 or conduit 0x1A), +4 float scale (flicker with 0.7/0.3 constants), +8 [player+0x4D4], +0xC block brightness * 0.0625 (const 0xF0A3FD0), +0x10 max(0, x*0.45) (const 0xF215E90).

0x53e66fc  mov byte ptr [rbp-0x48],3
0x53e6703  mov rax,[rax+0x360]

## 5 Shadow (tag 4) [V]

Producer 0x53E6C30. Description (0x20): +0 source (= renderer+0x5E0), +8 ptr to newest 0x40-byte matrix of a ring buffer, +0x10 ptr to local vec3, +0x18 u16.

0x53e737a  mov [rbp+0x1F0],ax
0x53e73ef  mov byte ptr [rbp-0x30],4
0x53e73f6  mov rax,[rax+0x360]
0x66aa13f  mov rdi,[rbx+0x10]
0x66aa452  mov si,[r12+0x18]

Source reads: +0x10/+0x18 caster vector (0x14-byte elements: +4 vec3, +0x10 scale); main extractor 0x66A9D50 (ctx mode 1, "SimpleOccluder") reads mesh +0x48, ret 0x66aa2cd; alt 0x66A6830 reads +0x28 mesh, +0x38, +0x70 vec4, materials "ShadowVolume"/"ShadowOverlay"/"SimpleOccluder", ret 0x66a861e. 0xAA6580 = mat4 multiply (out rcx, A rdx, B r8).

## 6 VolumetricFog (Sky tag 8) [V]

Producer 0x53E3AA0 (r12 = [rcx+8], r13 = [rcx+0x10]); variant at [rbp+0x170], tag 8, vslot 0x370.

0x53e4921  mov [rbp+0x90],ax
0x53e49b9  mov [rbp+0xE8],al
0x53e4a36  mov byte ptr [rbp+0x178],8

Stores (desc base rbp+0x90): +0 u16 (byte [r13+0x74]); +4 8 B [r12+0x45C]; +0xC [r12+0x464]; +0x10 [r12+0x468]; +0x20 [r12+0x478]; +0x30 [r12+0x4C8]; +0x34 [r12+0x488]; +0x44 [r12+0x498]; +0x54 [r12+0x4CC]; +0x58 byte [r12+0x968]. The last store is at rbp+0xE8, so sizeof ~0x5C.
Correction of Descriptions.h: bytes +0x5C..+0xDF are NOT written by the producer ([rbp+0xF0..0x16F] are unrelated locals); the visitor's qword read at +0x54 spans float + byte + 3 never-written bytes. Visitor part: docs/functions/66560f0_sky_visitor.md.

## 7 BlitFlipbookTexture (tag 1) [V]

Thin clone 0x5ACBE20; producer 0x5ACA680 builds elements with 0x6BF7260 / 0x5ACB9C0 and the span with 0x5ACBFE0.

0x5acbe94  mov byte ptr [rbp+0x18],1
0x5acb267  call 0x5ACBE20

Description (0x20): +0 SharedRef (0x4DFB570), +0x10 count = (end-begin)>>6, +0x18 data. Element (0x40): +0 object, +8 SharedRef, +0x18/+0x1C/+0x20 floats (frame position), +0x24 16 B, +0x34 8 B, +0x3C byte 0. Visitor passes &elem+8 to 0xBCABA00 and reads +0x18 (movsd), +0x20, +0x24 (movups). Exit 0x666c846.

## 8 FullscreenEffect (tag 7), PARTIAL

Clone 0x530A1B0: ctor 0x668BF20 (call 0x530a605), tag 7 stored, vslot 0x360.

0x530a67b  mov byte ptr [rbp+0x148],7
0x530a685  mov rax,[rax+0x360]

Descriptions.h RenderFullscreenEffectDescription (0xD0) matches the ctor. Visitor head 0x666ae72: `mov rax,[r15+0x78]`, pointee +0x40 must be non-zero, then 0x66B2B30 (render-state mapper), then 0x666b5cf. Reads attributed to tag 7 by exclusive control-flow reach: +0x00, +0x08 (address), four vec4 at +0x18/+0x28/+0x38/+0x48, +0x58, +0x5C, +0x64 vec4, +0x78 (Mesh-like: [+0x58]/[+0x60] item range), +0x88 u16, +0xC8, +0xC9.
NOT DONE: the tag-7 body (about 3700 reachable instructions, 2172 exclusive; strings "ALPHA_TEST", "fullscreen_cube_overlay") is not decoded instruction by instruction, and spill slot [rbp+0x668] is shared with tags 1 and 6, so attribution is by reachability only. D7c/L4s stays open.

## 9 Corrections summary

1. VolumetricFog description ends at +0x58 (sizeof ~0x5C), not 0xE0.
2. Particle +0x74 is a frame-ctx flag, not a description field.
3. Flame +0x08..0x47 is a read mat4 and +0xF2 is read (record helper 0x67411B0).
4. FullscreenEffect +0x78 behaves like a Mesh*.
5. descscan false positives (register reuse): Particle +0x20/+0x28, Flame +0x10, Shadow rbx/r14.

## 10 Re-verified claims

All quoted `0x<rva>  <instr>` lines above were re-run against the exe with tools/sigs/verify_oc.py (34 of 34 matched). Listing addresses cited in EffectDescriptions.h comments were checked to be valid instruction starts in the listings (262 references; the exceptions are call targets and constants).
