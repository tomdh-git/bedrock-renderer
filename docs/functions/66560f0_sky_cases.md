# Sky visitor 0x66560f0: jump table and case bodies (EndSky 3, Sky 5, Stars 6, Celestial 7)

Companion of docs/functions/66560f0_sky_visitor.md (Cubemap/Legacy/Ambient/Fog + shared tails). Exe 1.26.62.01, RVAs image-relative.
Tags: [V] instruction seen in a listing AND re-run with rdis, [I] inference, [?] unknown. Listings (tools/sigs/dumplist.py): docs/data/listings/
sky_heads_6656174_6656983.txt (all case heads), sky_66580f0_6658ffc.txt, sky_6658ffc_6659615.txt, sky_celestial_66596a1_6659ee0.txt,
sky_celestial_shadow_665b736_665b900.txt, sky_endsky_66587cf_6658b10.txt, sky_endsky_6658e44_66590f6.txt, sky_tag5_66574d8.txt.
The case bodies are NOT contiguous: the compiler interleaved them, each case is a chain of fragments joined by jumps. Reading the 0x66580f0..0x6658ffc
listing linearly mixes four cases; the per-case chains below were separated by a control-flow walk over the whole function (script kept in the agent
scratchpad, not in the repo) and then every quoted read re-checked with `rdis dis`.

## 1. Dispatch and jump table [V]
Dispatcher (rdis 0x6656161..0x6656172): `mov rdi,[r8]` (description), `lea rcx,[0xF2BF39C]; movsxd rax,[rcx+rax*4]; add rax,rcx; jmp rax`.
Table: RVA 0xF2BF39C is in .rdata (file offset 0xF2BDD9C, section VA delta 0x1C00); 11 int32 entries, target = 0xF2BF39C + entry (parsed from the PE).
| Tag | Name (SkyGroupTag) | Target | Notes |
|---|---|---|---|
| 0 | AmbientAtmosphere | 0x6656174 | reads `+0x00 u16` (0x6656174), vec4 `+0xA4/+0xB4/+0xC4` (0x6656178..0x665619b), qword `+0xE0` shared ctrl (0x66561ac, lock inc [rax+8]), joins 0x6656D4B/0x6656D4D. Body not decoded. |
| 1 | Clouds | 0x6656697 | no read: `mov rcx,rbx; mov rdx,rsi; mov r8,rdi`, restores xmm6..12 from [rbp+0x550..0x5B0], `add rsp,0x648`, pops, `jmp 0x67375A0` (tail call, r8 = the DESCRIPTION pointer). |
| 2 | Cubemap | 0x66562d5 | see 66560f0_sky_visitor.md |
| 3 | EndSky | 0x665649c | section 3 |
| 4 | LegacyCubemap | 0x66561cc | see 66560f0_sky_visitor.md; extra reads in 0x6658d63..0x6658dc0 listed in section 8 |
| 5 | SkyStars (material "Sky") | 0x66566ee | section 4 |
| 6 | Stars | 0x6656812 | section 5 |
| 7 | CelestialBody | 0x6656516 | section 6 |
| 8 | VolumetricFog | 0x66569b1 | see 66560f0_sky_visitor.md |
| 9 | Weather | 0x665627e | same tail stub as tag 1, `jmp 0x6745440`. |
| 10 | SkyAmbientSamples | 0x6656983 | see 66560f0_sky_visitor.md |

## 2. Common machinery of the four cases (all [V])
- Frame context reads: `[rsi+0x70]==1` selects the "ForwardPBR" material name (cmove), `[rsi+0x40]`/`[rsi+0x68]` are the resource-cache arguments of the resolve
  call 0x675E440 (rdx=&[rbp+0x320 or 0x330], r8=static key table, stack: &name {ptr,len}, &[rbp+0x340]); `[rsi]` (first qword) is the 3rd argument of the
  material getter 0xE86B370 (rcx=&shared_ptr out, rdx=[material+0x170]).
- Resolve result checks: null shared_ptr -> exit; `cmp byte [obj+0x10],1` (loaded flag) else exit; then owner chain `[ctrl]->[+0x18]->[0]` with lock inc/dec
  refcount juggling (0xF99FFA0 = release vcall) ending at the case join (Sky 0x66574d8, Stars 0x6657562, Celestial 0x665935d, EndSky 0x66575ee).
- Common body after the join: material getter 0xE86B370 -> `[rbp+0x50 / 0x1E8 / 0x58]`; `r15/r14=[rdi]` (mesh object); mesh item count
  `(([m+0x60]-[m+0x58])>>2)*0xAAAAAAAB` (stride 12) -> if nonzero `call 0xBBD7C70(&[rbp+0x340], 0x250+material, 0)` then `call 0x4DEDD00(mesh, &[rbp+0x340])`;
  `if byte [m+0x1D4] then r=[m+0x1D0] else 0` (Stars/EndSky/Celestial/Legacy only; passed as stack arg `[rsp+0x20]` of 0x66A0F60).
- Uniform sets: key = static TLS-initialised hash (`mov eax,[guard]; cmp eax,[tls+4]; jg cold` where the cold stub at 0x665D2xx..0x665Dxxx calls
  0x79580 with the name string); lookup of the key in the material feature table `[rbp+0x88]` (count u16 `[rbp+0x92]`, stride 0x10) or `[rbp+0x98]` (count
  `[rbp+0xA2]`, stride 0x30); if found, `[rbp+0x4E0]=index(u16)`, `[rbp+0x4E2]=1`, `call 0x5679DB0(material, &{idx,1}, &{1, dataPtr})` (data in [rbp+0x340]);
  texture: `call 0xBCABA00(&[rbp+0x1E0], &{idx*0xAAAB,1}, r8=&desc+8, r9=&{...}, 0)`. Role of 0x5679DB0 / 0xBCABA00 = uniform / sampler setter [I].
- Static key (guard-8) -> uniform name, read from the cold initialisers with rdis [V]: key 0x129F9F30 "FogColor" (guard 0x129F9F38, cold 0x665D828),
  0x129F9F40 "SkyColor" (0x665D89A); Stars 0x129F9F80 "StarsColor" (0x665D90C); Celestial 0x129F9FC0 "SunMoonColor" (0x665DC77), 0x129F9FD0 "SunMoonTexture"
  (0x665DCE9), 0x129F9FE0 "SunMoonEmissiveMultiplier" (0x665DD5B); EndSky 0x129F9D08 "SkyColor" (0x665D97E), 0x129F9D18 "SkyTexture" (0x665D9F0), 0x129F9D28
  "UV0Transform" (0x665DA62), 0x129F9D38 "MinimumSkyLuminance" (0x665DB93); Legacy 0x129F9C70 "CubemapRotation" (0x665DB21), 0x129F9C80
  "CloudRenderDistanceAndCloudHeight" (0x665DDD8). Material names also read as strings: "Stars"/"StarsForwardPBR" 0xF54C3E1/0xF7CA19E, "SunMoon"/
  "SunMoonForwardPBR" 0xF584D1D/0xF7CA226, "EndSky"/"EndSkyForwardPBR" 0xF51B961/0xF7CA148, "Sky" 0xF51B964 (a suffix of the "EndSky" literal, 3 chars).
- Draw state: after the uniforms the cases build the same DrawState block `[rbp+0x344]=N (dword, 0 for Sky/EndSky/Celestial, 6 for Stars), [0x348]=7 (byte),
  [0x34C]=1, word [0x350]=1, byte [0x352]=2, ... [0x39A]=0xFF`, call 0xE869FF0 (UB copy into [rbp+0x3A8]), store the 64-byte matrix into the record
  ([rbp+0x428..0x467] or [0x430..], type byte 0 = full matrix, 2 = 8-byte form, other = pointer form), store the u16 from the description into `[rbp+0x470/0x478]`,
  then a 4-way switch on a byte (jump tables below) copies the payload variant and joins the shared push tail.
- Payload-variant tails (int32 tables parsed from the exe): 0xF2BF3F8 [0x665a8e5, 0x6659340, 0x66595a8, 0x66595ba] (Sky, switch at 0x665933d on byte [rbp+0x518]);
  0xF2BF3E8 [0x665a7b7, 0x66594a5, 0x6659576, 0x6659585] (Stars, 0x66594a2, byte [rbp+0x88]); 0xF2BF3C8 [0x665c11b, 0x665b6bc, 0x665b704, 0x665b713]
  (Celestial, 0x665b6b9, byte [rbp+0x88]); 0xF2BF438 [0x665af0b, 0x6659563, 0x66595e0, 0x66595f2] (EndSky, 0x6659560, byte [rbp+0x518]).
  Sky and Stars both reach the SKY-PUSH tail 0x665a8e5 (exit 0x665aee8/0x665aeef); Celestial reaches 0x665c11b (exit 0x665c24c -> 0x665cf64); EndSky reaches 0x665af0b
  (exit 0x665b56e..0x665b5ee). The tails themselves are covered in 66560f0_sky_visitor.md section 6 (as joins) and not re-decoded.

## 3. EndSky (tag 3), description = Descriptions.h RenderSkyDescription (0xB0)
Chain: head 0x665649c..0x6656511 -> resolve 0x6656be0/0x6656bec..0x6656d46 -> join 0x66575ee -> 0x66575f7.. (null/not loaded -> 0x665b56e) -> body 0x66587cf..0x6658b0b ->
0x6658e44..0x66590a5 (+ fall-through 0x6658ff5 into 0x6658ffc) -> 0x66594b5.. -> table 0xF2BF438.
- Head: `eax=[rsi+0x70]` saved to `[rbp+0x540]`; `cmp eax,1`; r14 = "EndSkyForwardPBR" (len r15=0x10) if equal else "EndSky" (len 6); the PBR name is heap-allocated
  via [0x1233E1A8] vslot+8 (0x20 bytes, 0x66564da..0x66564f3), the short name is built into [rbp+0x120] (0x6656be0..0x6656c08, SSO cap 0xF/0x1F); resolve call 0x675E440 with
  r8=0x129F9CF0 (0x6656c8b); TLS guard 0x129F9D00.
| Desc off | Size | Read at | Use |
|---|---|---|---|
| +0x00 | q | 0x665884d, 0x6658eb8 | mesh object `[rdi]` (its +0x58/+0x60 count, +0x1B0/+0x1B8 shared_ptr copy, +0x1D0/+0x1D4) |
| +0x08 | addr | 0x6658a13 `lea r8,[rdi+8]` | passed as data of sampler "SkyTexture" (0xBCABA00); never dereferenced here |
| +0x18 | u16 | 0x6658eb3 | -> r15w -> `[rbp+0x470]` (0x66594ec) [I: draw-order/flag word] |
| +0x1C | 16 | 0x6658915 | uniform "SkyColor" |
| +0x2C..+0x6B | 4x16 | 0x6658e80, 0x6658e8b, 0x6658e96, 0x6658ea1 | matrix -> [rbp+0x170..0x1AF], `[rbp+0x1B0]=0` |
| +0x6C | addr | 0x66589a3 `lea r9,[rdi+0x6C]` | data of uniform "UV0Transform" via 0x56D55E0(material, &[rbp+0x340], key 0x129F9D28, r9); 0x40 bytes by adjacency to +0xAC [I] |
| +0xAC | 4 | 0x6658aa1 | `movss; shufps 0` -> uniform "MinimumSkyLuminance", only if `[rbp+0x540]==1` (0x6658a6f) |
Material: "EndSky" / "EndSkyForwardPBR". Exits: material not found / not loaded -> 0x665b56e (release [rbp+0x328], free heap name if cap>=0x10) -> 0x665d154 (epilogue);
normal path ends the same way (0x665b5ee jmp 0x665d154). Correction: the code at 0x6658ffc..0x6659340 that docs/progress/oc_U-SK5b.md calls the "Stars base draw" is the
EndSky tail (reached by the fall-through 0x6658ff5, `[rbp+0x1B0]` matrix-type switch, `[rbp+0x470]=r15w`), the table at 0x6659322 is the SKY (tag 5) payload switch, 0x6659353.. is the
Celestial join and 0x66593dc..0x66594a2 the Stars payload switch. The Stars body proper is 0x66585b4..0x6658cd3.

## 4. SkyStars / "Sky" (tag 5): layout different from RenderSkyDescription
Chain: head 0x66566ee..0x665680d (guard 0x129F9F28; name "Sky" len 3 at 0x6656725/0x6656733; `call 0x675E440` r8=0x129F9F18; null/not loaded -> 0x665AEE8) -> join 0x66574d8 (`test r14,r14; je 0x665AEE8`;
`r14=[rsi]`) -> 0x6658445/0x665845A (material getter) -> 0x66584c3 mesh -> 0x665854f FogColor -> 0x66590f6 SkyColor -> 0x66590aa..0x6659322 -> table 0xF2BF3F8.
| Desc off | Size | Read at | Use |
|---|---|---|---|
| +0x00 | q | 0x66584c3, 0x66591b8 | mesh object (count/bind as common; `call 0x4DE9FA0(mesh, &[rbp+0x170])`, then 0x66A6190(&[rbp+0x4E0], [rsi], &[rbp+0x170])) |
| +0x08 | 16 | 0x66590f6 | uniform "SkyColor" (key 0x129F9F40, lookup in [rbp+0x88] table, set via 0x5679DB0 at 0x665916c) |
| +0x18 | 16 | 0x665854f | uniform "FogColor" (key 0x129F9F30, set at 0x66590dd) |
| +0x28..+0x67 | 4x16 | 0x665917c, 0x6659187, 0x6659192, 0x665919f | matrix -> [rbp+0x120..0x15F], `[rbp+0x160]=0` -> stored at [rbp+0x428..0x467] (0x66592a6..0x66592bc) |
| +0x68 | u16 | 0x66591b3 | `r14w` -> `[rbp+0x470]` (0x66592cb) |
DrawState (0x66591df..0x665926f): `[0x344]=0, [0x348]=7, [0x34C]=1, [0x350]=1, [0x352]=2, ... [0x39A]=0xFF`; `call 0xE869FF0(&[rbp+0x3A8], rbx)`; `cmp rax,3; ja 0x665A8EB`, table 0xF2BF3F8. Exit: shared tail 0x665a8e5 ->
0x665aee8 `mov rsi,[rbp+0x328]` -> 0x665aeef `jmp 0x665D124`. No other description field is read; no `[rdi+0x70/+0x80]`. Finding: the 0xB0 RenderSkyDescription of Descriptions.h (flags +0x18, color +0x1C,
matrix +0x2C, uv +0x6C, value +0xAC) is exactly what tag 3 reads, not tag 5; tag 5's producer layout (SkyColor/FogColor vec4s + matrix at +0x28 + u16 +0x68) is not yet matched to a constructor [?].

## 5. Stars (tag 6)
Chain: head 0x6656812..0x665697e (names "Stars"/"StarsForwardPBR", sizes 5/0xF, guards 0x129F9F60/0x129F9F78, resolve with r8=0x129F9F50/F68; oc_U-SK4.md) -> 0x6657562 (null -> 0x665AEE8; `r15=[rsi]`) ->
0x6657586 -> 0x66585b4/0x66585c9 (material getter at 0x66585f2) -> 0x6658638 mesh -> 0x66586b9 StarsColor -> 0x6658745 `call 0x66A08B0` -> 0x665874b matrix -> 0x6658792 texture shared_ptr copy ->
0x6658b10..0x6658cd3 (call 0x66A0F60 at 0x6658b88, DrawState with `[rbp+0x344]=6`) -> switch on `[rbp+0x520]` -> 0x665940d/0x66593dc -> 0x6659413 -> table 0xF2BF3E8 -> shared tail 0x665a8e5.
| Desc off | Size | Read at | Use |
|---|---|---|---|
| +0x00 | q | 0x6658638, 0x665867d, 0x6658792 | mesh object; `[m+0x1B0]` (checked `test`, `movzx word [rcx+0x10]`) and `[m+0x1B8]` (lock inc ctrl) copied into [rbp+0x330]/[rbp+0x338] (0x6658b12..0x6658b27); `[m+0x1D4]/[m+0x1D0]` -> r13d (0x6658683) |
| +0x08 | 16 | 0x66586b9 | uniform "StarsColor" (key 0x129F9F80; table [rbp+0x218], count [rbp+0x222], stride 0x10) |
| +0x18..+0x57 | 16,16,16,8,8 | 0x6658750, 0x665875b, 0x6658766, 0x665874b, 0x6658779 | matrix -> [rbp+0x4E0..0x517]; `[rbp+0x520]=0` (matrix type) |
| +0x58 | u16 | 0x665878d | `r15d` -> `[rbp+0x478]` (0x6659436) |
The Stars head reads no description field (confirms oc_U-SK4.md). Description byte +0x5A of Descriptions.h is not read by this case [V: no `[rdi+0x5A]` in the chain]. Exit: shared tail, as Sky.

## 6. CelestialBody (tag 7)
Chain: head 0x6656516 (xmm6=[rdi+0x18]; skip test; guards 0x129F9FA0/0x129F9FB8; names "SunMoon" len 7 / "SunMoonForwardPBR" len 0x11 via cmove with r10 = 7 or 0x11; resolve 0x675E440 r8=0x129F9F90 (0x129F9FA8 for PBR); null/not loaded -> 0x665CF64)
-> 0x66565f1..0x6656692 -> join 0x665935d (null -> 0x665CF64) -> 0x6659366.. (own material code copy 0x66596a1..0x6659726, getter 0xE86B370 at 0x66596df) -> `cmp [rsi+0x70],2`:
- ctx == 2 (0x6659737 falls through): 0x665973d `r9=[rdi]`, 0xBBD7F70, `r8=[rdi]`, `[r8+0x1D0/0x1D4]` -> r14, early exit 0x665CEC8 if r14==0 or [rbp+0xA8]!=1 (0x6659781), 0x6693320, flags
  `test dword [rdi+0x6C],0xFFFFFFFD; setne; shl 9; add 0x200` (0x66597a8..0x66597b5), `lea rcx,[rdi+8]` (0x66597ba) -> 0x665b738 (`call 0x673CC80`, mesh +0x1B0/+0x1B8 copy, 0x66A0F60, matrix 16 B at +0x28/0x38/0x48/0x58 (0x665b838..0x665b859), `r13d=[rdi+0x68]` 0x665b78a).
- otherwise 0x66597dc: mesh `[rdi]`, count, bind (0xBBD7C70/0x4DEDD00), `[r15+0x1D4/0x1D0]` -> r13d, uniform "SunMoonColor" = xmm6 (0x66598a7, key 0x129F9FC0), sampler "SunMoonTexture" with `lea r8,[rdi+8]`
  (0x6659d7c, key 0x129F9FD0, 0xBCABA00 at 0x6659db4), uniform "SunMoonEmissiveMultiplier" = float [rdi+0x80] (0x6659dba, key 0x129F9FE0, set at 0x6659e53), matrix, u16, mesh texture copy, 0x66A0F60 (0x665a653), DrawState, table 0xF2BF3C8.
| Desc off | Size | Read at | Use |
|---|---|---|---|
| +0x00 | q | 0x665973d, 0x6659754, 0x66597dc, 0x6659ea0 | mesh object |
| +0x08 | addr | 0x66597ba, 0x6659d7c | sampler data pointer ("SunMoonTexture") |
| +0x18 | 16 | 0x6656516 (head) | "SunMoonColor" (in the ctx==2 variant xmm6 is zeroed at 0x6659787 first) |
| +0x28..+0x67 | 16,16,16,8,8 / 4x16 | 0x6659e5e, 0x6659e69, 0x6659e74, 0x6659e59, 0x6659e87 / 0x665b838..0x665b859 | matrix [rbp+0x4E0..0x517] or [rbp+0x120..0x15F]; `[rbp+0x520]=0` |
| +0x68 | u16 | 0x6659e9b, 0x665b78a | -> r15w / r13w -> `[rbp+0x478]` |
| +0x6C | dword | 0x66597a8 | flag test (ctx==2 variant only) |
| +0x70 | byte | 0x6656525 | only when ctx `[rsi+0x70]` not in {1,2}: `v-3` unsigned `> 0xFFFFFFFD` skips the test; byte != 0 -> `jne 0x665D154` (draw suppressed, function epilogue) |
| +0x80 | float | 0x6659dba | "SunMoonEmissiveMultiplier" |
Exits: 0x665CF64 (`mov rsi,[rbp+0x28]; jmp 0x665D124`), 0x665D154, joined tail 0x665c11b..0x665c24c.

## 7. Verification (rdis re-run, 30 claims)
Jump-table dispatcher (0x6656164..0x6656172); the 11 targets (PE parse); strings "Sky", "EndSky", "EndSkyForwardPBR", "Stars", "StarsForwardPBR", "SunMoon", "SunMoonForwardPBR", "FogColor",
"SkyColor" (PE bytes + rdis comments); the 20 field reads 0x665854f, 0x66590f6, 0x665917c, 0x66591b3, 0x66586b9, 0x665878d, 0x6658750, 0x66598a7, 0x6659dba, 0x66597a8, 0x6658915, 0x6658aa1, 0x6658e80,
0x6658eb3, 0x66589a3, 0x6659e59, 0x6659e9b, 0x66584c3, 0x6658d63, 0x6658dc0; cold-initialiser names for the 15 static keys (rdis string comments at 0x665D2EE..0x665DDD8); the four payload tables
(PE parse); epilogue 0x665d11d/0x665d124/0x665d154 (rdis); tail stubs 0x66562d0 `jmp 0x6745440` and 0x66566e9 `jmp 0x67375A0` (rdis listing).

## 8. Remaining / out of scope
- Atmosphere (tag 0) body from 0x6656d4b, Weather/Clouds are tail calls to 0x6745440 / 0x67375A0 (bodies not decoded here).
- The tails (0x665a7b7..0x665a8e5, 0x665c11b.., 0x665af0b..) were only identified, not re-decoded; their contents are in oc_U-SK1*.md (joins).
- Fragment 0x66580fd..0x6658350 (a SkyAmbientSamples/VolumetricFog tail variant ending `mov rsi,[rbp+0x1F0]; jmp 0x665D124`) and 0x665803c..0x66580f0 are Ambient/Fog, not decoded here.
- Legacy (tag 4) reads not in SkyDescriptions.h: `[rdi+0x20]` qword (0x6658d63, data of "CubemapRotation" via 0x56D55E0), `[rdi+0x28]` float (0x6658dc8), `[rdi+0x2C]` s16 (0x6658dc0), cloud-distance uniform "CloudRenderDistanceAndCloudHeight" (0x665DDD8).
- Roles of 0x5679DB0, 0xBCABA00, 0x56D55E0, 0x66A0F60, 0x4DE9FA0, 0x66A6190, 0x673CC80 are [I]/[?]; sizes of the +0x08 sampler data and the uv transform are by adjacency only.
- Which constructor produces the tag-5 layout (SkyColor/FogColor) is unresolved (Descriptions.h RenderSkyDescription matches tag 3).

## 9. Tails, Atmosphere, Clouds, Weather and the tag-5 producer (second pass, static)
Listings: sky_tail_665a7b7_665a8e5.txt, sky_tail_665a8e5_665aef4.txt, sky_tail_665c11b_665c269.txt, sky_tail_665af0b_665b624.txt, sky_atmosphere_6656d4b_6657090.txt, sky_producer_5369f60_536a2f4.txt.
- Stars payload tail 0x665a7b7 (69 instr) [V]: stores the variant tag byte `[rbp+0x4B8]`, copies [rbp+0xA0]/[rbp+0x90] into [rbp+0x4D0]/[rbp+0x4C0], `rcx=0x9D0+[rsi+0x10]`, `call 0x67EA0D0` (push into the pass object, stack args rax/r10/r11 = the 3 payload pointers set by the table 0xF2BF3E8 entry), `call 0x673CB40(&[rbp+0x340])` (record destructor), releases `[rbp+0x80]` when `[rbp+0x88]==3`, walks the 0x28-stride array `[rbp+0x58]..[rbp+0x60]` releasing entries with type byte `[+0x18]==2`, then `cmp byte [rbp+0x520],1; jne 0x665AEE8` and the final release of `[rbp+0x4E0]` through 0x665AEBB -> 0x665aee8 -> 0x665aeef `jmp 0x665D124`. Reads no description field.
- Sky (tag 5) tail 0x665a8e5 (325 instr, covered earlier by oc_U-SK2c as the "SKY-PUSH tail") [V]: `0x5ABA5C0(0x9D0+[rsi+0x10])`, zero 12 vec4 of record scratch, then in order: pool 0x780 (`call 0x675F3B0`, index `[rbp+0x208]=(cursor/8)*0xFFFF8BA3-1`), u16 array 0x8A0 (value `[rbp+0x470]`, the description u16), pool 0x648 (`0x675FB30`), 0x88-stride pool 0x768 (`0xE869FF0`, 0x6760710), 0x58-stride pool 0x750 (0x6760A80), byte pool 0x858 (0x6760E60), byte pool 0x2A0 (0x6760E60), then the 0xC8 record `[rbp+0x1E0]` appended to `[rsi+8]` (`mov r8d,0xC8; call 0xEEC6EC0`, full: `call 0x5ABA6D0`), `call 0x66A9AD0(&[rbp+0x340])`, releases, exit 0x665aeef. Reads no description field.
- Celestial tail 0x665c11b (79 instr) [V]: same shape as the Stars tail (`0x67EA0D0` at 0x665c155, `0x673CB40` at 0x665c162, 0x28-stride release loop at 0x665c1bf) ending `jmp 0x665CF64` (0x665c24c) -> `mov rsi,[rbp+0x28]; jmp 0x665D124`.
- EndSky tail 0x665af0b (383 instr) [V]: SKY-PUSH twin of 0x665a8e5 (`0x5ABA5C0` 0x665af36, pools 0x780/0x8A0/0x648/0x768/0x750 and THREE byte pools via 0x6760E60 at 0x665b2bd/0x665b33f/0x665b3c4, 0xC8 record 0x665b43d, `0x66A9AD0` 0x665b482), frees the heap material name when cap >= 0x10 (0x665b569) and leaves through `jmp 0x665D154` (0x665b5ee).
- Atmosphere (tag 0) [V]: head 0x6656174 reads u16 +0x00, vec4 +0xA4/+0xB4/+0xC4, qword +0xE0 (null -> 0x6656D4B, else `lock inc [rax+8]` and reload); body 0x6656d4b..0x6656f96 copies the 0x138-byte description field by field into [rbp+0x210..0x30F] and [rbp+0x340..0x3B7] (full field list in SkyDescriptions.h AtmosphereDescriptionReads); one derived value: `[rbp+0x26C]=max([rdi+0x10]-[rdi+0xC], [0xEEC8060])`; `0xEEC6EC0(r8d=0xAD)` copy at 0x6656f88..0x6656f91; `0x5ABA5C0` (0x6656fb8); record push into `[rsi+0x548]` (stride 0x130 table, `cmp r15,[rsi+0x550]`) and then the shared Ambient/Fog code 0x6657237.., 0x66573c3.., 0x66578e0..0x6657dc4, exit `0x6657ff4 jmp 0x665D124`. No material string, no uniform lookup (like Ambient/Fog).
- Clouds (tag 1): `jmp 0x67375A0` with rbx = r8 = description. The target (0x67375a0, size >0x2000) reads `[rbx+0x00..0x3F]` matrix (movups 0x00/0x10/0x20, movss 0x30/0x34, movsd 0x38), `lea r9,[rbx+0x40]`, qword `+0x80` (mesh), vec4 `+0x88`, bytes `+0x98`/`+0x9A`, float `+0x9C`, u16 `+0xA0`; material "Clouds" (runtime-built PBR name in data_129f9ae8), frame ctx `[rsi+0x70]`, `[rsi+0x40]`, `[rsi+0x68]`. Matches Descriptions.h RenderCloudsDescription.
- Weather (tag 9): `jmp 0x6745440` (r8 = description saved at [rbp+0x5F8]). Reads: dword +0x84 (0x6745482, first), mesh `[rsi]` (0x6745b18), ten vec4 uniforms +0x88/+0x98/+0xA8/+0xB8/+0xC8/+0xD8/+0xE8/+0xF8/+0x108/+0x118 via 0x5679DB0, samplers `lea r8,[rsi+0x50/0x60/0x70]` via 0xBCABA00, `cvtsi2ss [rsi+0x80]`, matrix +0x10/+0x20/+0x30 vec4 + movsd +0x40/+0x48, u16 +0x128; materials "Weather"/"WeatherForwardPBR" (0xF56D754/0xF7CA1E5, len 7/0x11), "NoVariety"/"PointLightShading" strings further in. Matches Descriptions.h RenderWeatherDescription.
- Tag-5 producer FOUND [V rdis]: inline in clone 0x5369b30 at 0x536a146..0x536a25a (mesh `[r15]`, SkyColor = movlps xmm8 + movss xmm6 + 1.0f, FogColor = 16 bytes from rdi+0x18, 16 floats matrix from `[[rbp+0x38]]`, u16 from byte `[[rbp+0x2E0]+0x74]`), inserted at 0x536a2e3 with `mov byte [rbp+0x298],5` (0x536a2d8) through vslot 0x370. The 0xB0 object built by 0x668c910 (call 0x5369f89) is inserted earlier by the EndSky thin clone 0x53707a0 (call 0x5369f99), so RenderSkyDescription = tag 3. Added `RenderSkyColorsDescription` (tag 5) to Descriptions.h; the visitor tag-5 reads match it field for field.
Verified again with rdis in this pass (20 claims): 0x6656d4d, 0x6656de6, 0x6656e11, 0x6656ea9, 0x66561ac, 0x6656fb8, 0x6656f88, 0x6737880, 0x6737943, 0x6737dd8, 0x6737d8a, 0x6746674, 0x67465c8, 0x67466b9, 0x665a7f1, 0x665a8a5, 0x665c155, 0x665af36, 0x665b43d, 0x536a2d8/0x536a2e3/0x5369f89/0x5369f99.
Still open: Clouds/Weather bodies beyond the description reads (0x2000+ bytes each, see docs/functions/67375a0.md), pool roles, callee roles (0x67EA0D0, 0x673CB40, 0x66A9AD0 [?]).
