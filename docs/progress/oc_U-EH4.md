## NEXT
DONE

# Unit U-EH4 — Per-frame constants close: FogAndDistanceControl/sky/weather pending

Terrain side (6co: ViewPositionAndTime w=seconds, FogColor, MeshContext, GlobalRoughness) already proven [V] in docs/BGFX_MAP.md section 6co (live capture, scene=The End, game time ~864s): slot 7 MeshContext=(0,0,0,0) at call site 0x66eb6b5; slot 10 ViewPositionAndTime=(-0,0,-0,863.9) w=elapsed seconds at 0x66eb901; slot 2 GlobalRoughness=(0.6563,1.0,128.0,57.0) at 0x66eb998; slot 4 FogColor=(0.0402,0.0494,0.09,1.0) at 0x66eba35. Slot id = index in RenderChunk uniform list order (6cc): 0 DitherParams,1 DitherParams2,2 GlobalRoughness,3 FogAndDistanceControl,4 FogColor,...,7 MeshContext,...,10 ViewPositionAndTime.

Already proven [V] (carried forward):
- Weather FogAndDistanceControl = Weather desc+0x98: 0x6746335 movups xmm0,[rsi+0x98]; name hash 0x674635d mov rdx,[0x129F9FF0]; written via 0x67463b4 call 0x5679DB0.
- Sky FogColor = sky desc+0x18: 0x665854f movups xmm0,[rdi+0x18]; name hash 0x665858a mov r9,[0x129F9F30]; written via 0x66590dd call 0x5679DB0.

Pending — now proven [V]: the remaining RenderWeatherDescription per-frame uniforms in the Weather extractor 0x6745440 (desc pointer in rsi, size 0x130 [I] per 6ib). Each 16-byte vec4 block is loaded from desc, staged to [rbp+0x340], span count=1 at [rbp+0x4F0], span ptr [rbp+0x4F8]=[rbp+0x340], name matched to an FNV-1a hash static, written via 0x5679db0. Per 6ib the ten vec4 blocks are FogColor+0x88, FogAndDistanceControl+0x98, PositionBaseOffset+0xA8, PrevPositionForwardOffset+0xB8, PrevPositionBaseOffset+0xC8, PositionForwardOffset+0xD8, ViewPosition+0xE8, UVOffsetAndScale+0xF8, Velocity+0x108, Dimensions+0x118; plus OcclusionHeightOffset+0x80 (i32 splat to vec4). FogAndDistanceControl (+0x98) was already proven above; the other nine vec4 blocks and OcclusionHeightOffset are enumerated below. The hash statics (0x129F8348 FogColor, 0x129FA040 PrevPositionBaseOffset, 0x129FA050 PrevPositionForwardOffset, 0x129FA060 PositionBaseOffset, 0x129FA070 PositionForwardOffset, 0x129FA080 ViewPosition, 0x129FA090 UVOffsetAndScale, 0x129FA0A0 Velocity, 0x129FA0B0 Dimensions, 0x129FA0C0 OcclusionHeightOffset) are established by 6ib's [V mapping] method and are consumed by the loads below.

| offset | size | R/W | verbatim `0xRVA  instr` line(s) | meaning [tag] |
| rsi+0x88 | 16 | R | 0x6745d7a  movups xmm0,[rsi+0x88]<br>0x6745d81  movaps [rbp+0x340],xmm0<br>0x6745d88  mov qword ptr [rbp+0x4F0],1<br>0x6745d93  lea r15,[rbp+0x340]<br>0x6745d9a  mov [rbp+0x4F8],r15<br>0x6745dbb  mov r9,[0x129F8348]<br>0x6745e18  call 0x5679DB0 | Weather FogColor vec4 (desc+0x88) read; span staged; name hash 0x129F8348 = FogColor (6ib); written to shader slot via 0x5679db0 [V] |
| rsi+0x98 | 16 | R | 0x6746335  movups xmm0,[rsi+0x98]<br>0x674633c  movaps [rbp+0x340],xmm0<br>0x6746343  mov qword ptr [rbp+0x4F0],1<br>0x674634e  mov [rbp+0x4F8],r15<br>0x674635d  mov rdx,[0x129F9FF0]<br>0x67463b4  call 0x5679DB0 | Weather FogAndDistanceControl vec4 (desc+0x98) [V; previously proven] |
| rsi+0xA8 | 16 | R | 0x6745f71  movups xmm0,[rsi+0xA8]<br>0x6745f78  movaps [rbp+0x340],xmm0<br>0x6745f7f  mov qword ptr [rbp+0x4F0],1<br>0x6745f8a  mov [rbp+0x4F8],r15<br>0x6745f99  mov r9,[0x129FA060]<br>0x6745ff8  call 0x5679DB0 | Weather PositionBaseOffset vec4 (desc+0xA8); name hash 0x129FA060 = PositionBaseOffset (6ib); written via 0x5679db0 [V] |
| rsi+0xB8 | 16 | R | 0x6745ed1  movups xmm0,[rsi+0xB8]<br>0x6745ed8  movaps [rbp+0x340],xmm0<br>0x6745edf  mov qword ptr [rbp+0x4F0],1<br>0x6745eea  mov [rbp+0x4F8],r15<br>0x6745ef9  mov r9,[0x129FA050]<br>0x6745f58  call 0x5679DB0 | Weather PrevPositionForwardOffset vec4 (desc+0xB8); name hash 0x129FA050 = PrevPositionForwardOffset (6ib); written via 0x5679db0 [V] |
| rsi+0xC8 | 16 | R | 0x6745e31  movups xmm0,[rsi+0xC8]<br>0x6745e38  movaps [rbp+0x340],xmm0<br>0x6745e3f  mov qword ptr [rbp+0x4F0],1<br>0x6745e4a  mov [rbp+0x4F8],r15<br>0x6745e59  mov r9,[0x129FA040]<br>0x6745eb8  call 0x5679DB0 | Weather PrevPositionBaseOffset vec4 (desc+0xC8); name hash 0x129FA040 = PrevPositionBaseOffset (6ib); written via 0x5679db0 [V] |
| rsi+0xD8 | 16 | R | 0x6746011  movups xmm0,[rsi+0xD8]<br>0x6746018  movaps [rbp+0x340],xmm0<br>0x674601f  mov qword ptr [rbp+0x4F0],1<br>0x674602a  mov [rbp+0x4F8],r15<br>0x6746039  mov r9,[0x129FA070]<br>0x6746098  call 0x5679DB0 | Weather PositionForwardOffset vec4 (desc+0xD8); name hash 0x129FA070 = PositionForwardOffset (6ib); written via 0x5679db0 [V] |
| rsi+0xE8 | 16 | R | 0x67460b1  movups xmm0,[rsi+0xE8]<br>0x67460b8  movaps [rbp+0x340],xmm0<br>0x67460bf  mov qword ptr [rbp+0x4F0],1<br>0x67460ca  mov [rbp+0x4F8],r15<br>0x67460d9  mov r9,[0x129FA080]<br>0x6746138  call 0x5679DB0 | Weather ViewPosition vec4 (desc+0xE8); name hash 0x129FA080 = ViewPosition (6ib); written via 0x5679db0 [V] |
| rsi+0xF8 | 16 | R | 0x6746151  movups xmm0,[rsi+0xF8]<br>0x6746158  movaps [rbp+0x340],xmm0<br>0x674615f  mov qword ptr [rbp+0x4F0],1<br>0x674616a  mov [rbp+0x4F8],r15<br>0x6746179  mov r9,[0x129FA090]<br>0x67461d8  call 0x5679DB0 | Weather UVOffsetAndScale vec4 (desc+0xF8); name hash 0x129FA090 = UVOffsetAndScale (6ib); written via 0x5679db0 [V] |
| rsi+0x108 | 16 | R | 0x67461f1  movups xmm0,[rsi+0x108]<br>0x67461f8  movaps [rbp+0x340],xmm0<br>0x67461ff  mov qword ptr [rbp+0x4F0],1<br>0x674620a  mov [rbp+0x4F8],r15<br>0x6746219  mov r9,[0x129FA0A0]<br>0x6746278  call 0x5679DB0 | Weather Velocity vec4 (desc+0x108); name hash 0x129FA0A0 = Velocity (6ib); written via 0x5679db0 [V] |
| rsi+0x118 | 16 | R | 0x6746291  movups xmm0,[rsi+0x118]<br>0x6746298  movaps [rbp+0x340],xmm0<br>0x674629f  mov qword ptr [rbp+0x4F0],1<br>0x67462aa  mov [rbp+0x4F8],r15<br>0x67462b9  mov r9,[0x129FA0B0]<br>0x674631c  call 0x5679DB0 | Weather Dimensions vec4 (desc+0x118); name hash 0x129FA0B0 = Dimensions (6ib); written via 0x5679db0 [V] (not-found path falls through to FogAndDistanceControl at 0x6746335) |
| rsi+0x80 | 4 | R | 0x67465c8  cvtsi2ss xmm0,dword ptr [rsi+0x80]<br>0x67465d0  shufps xmm0,xmm0,0<br>0x67465d4  movaps [rbp+0x340],xmm0<br>0x67465db  mov qword ptr [rbp+0x4F0],1<br>0x67465e6  mov [rbp+0x4F8],r15<br>0x674660a  mov r8,[0x129FA0C0]<br>0x6746661  call 0x5679DB0 | Weather OcclusionHeightOffset i32 (desc+0x80) splatted to vec4; name hash 0x129FA0C0 = OcclusionHeightOffset (6ib); written via 0x5679db0 [V] |
| rdi+0x18 | 16 | R | 0x665854f  movups xmm0,[rdi+0x18]<br>0x665858a  mov r9,[0x129F9F30]<br>0x66590dd  call 0x5679DB0 | Sky FogColor vec4 (desc+0x18); name hash 0x129F9F30 = FogColor (6ib); written via 0x5679db0 [V] |

## Verbatim instruction proof lines (verified against the exe)

0x6745d7a  movups xmm0,[rsi+0x88]
0x6745d81  movaps [rbp+0x340],xmm0
0x6745d88  mov qword ptr [rbp+0x4F0],1
0x6745d93  lea r15,[rbp+0x340]
0x6745d9a  mov [rbp+0x4F8],r15
0x6745dbb  mov r9,[0x129F8348]
0x6745e18  call 0x5679DB0
0x6746335  movups xmm0,[rsi+0x98]
0x674633c  movaps [rbp+0x340],xmm0
0x6746343  mov qword ptr [rbp+0x4F0],1
0x674634e  mov [rbp+0x4F8],r15
0x674635d  mov rdx,[0x129F9FF0]
0x67463b4  call 0x5679DB0
0x6745f71  movups xmm0,[rsi+0xA8]
0x6745f78  movaps [rbp+0x340],xmm0
0x6745f7f  mov qword ptr [rbp+0x4F0],1
0x6745f8a  mov [rbp+0x4F8],r15
0x6745f99  mov r9,[0x129FA060]
0x6745ff8  call 0x5679DB0
0x6745ed1  movups xmm0,[rsi+0xB8]
0x6745ed8  movaps [rbp+0x340],xmm0
0x6745edf  mov qword ptr [rbp+0x4F0],1
0x6745eea  mov [rbp+0x4F8],r15
0x6745ef9  mov r9,[0x129FA050]
0x6745f58  call 0x5679DB0
0x6745e31  movups xmm0,[rsi+0xC8]
0x6745e38  movaps [rbp+0x340],xmm0
0x6745e3f  mov qword ptr [rbp+0x4F0],1
0x6745e4a  mov [rbp+0x4F8],r15
0x6745e59  mov r9,[0x129FA040]
0x6745eb8  call 0x5679DB0
0x6746011  movups xmm0,[rsi+0xD8]
0x6746018  movaps [rbp+0x340],xmm0
0x674601f  mov qword ptr [rbp+0x4F0],1
0x674602a  mov [rbp+0x4F8],r15
0x6746039  mov r9,[0x129FA070]
0x6746098  call 0x5679DB0
0x67460b1  movups xmm0,[rsi+0xE8]
0x67460b8  movaps [rbp+0x340],xmm0
0x67460bf  mov qword ptr [rbp+0x4F0],1
0x67460ca  mov [rbp+0x4F8],r15
0x67460d9  mov r9,[0x129FA080]
0x6746138  call 0x5679DB0
0x6746151  movups xmm0,[rsi+0xF8]
0x6746158  movaps [rbp+0x340],xmm0
0x674615f  mov qword ptr [rbp+0x4F0],1
0x674616a  mov [rbp+0x4F8],r15
0x6746179  mov r9,[0x129FA090]
0x67461d8  call 0x5679DB0
0x67461f1  movups xmm0,[rsi+0x108]
0x67461f8  movaps [rbp+0x340],xmm0
0x67461ff  mov qword ptr [rbp+0x4F0],1
0x674620a  mov [rbp+0x4F8],r15
0x6746219  mov r9,[0x129FA0A0]
0x6746278  call 0x5679DB0
0x6746291  movups xmm0,[rsi+0x118]
0x6746298  movaps [rbp+0x340],xmm0
0x674629f  mov qword ptr [rbp+0x4F0],1
0x67462aa  mov [rbp+0x4F8],r15
0x67462b9  mov r9,[0x129FA0B0]
0x674631c  call 0x5679DB0
0x67465c8  cvtsi2ss xmm0,dword ptr [rsi+0x80]
0x67465d0  shufps xmm0,xmm0,0
0x67465d4  movaps [rbp+0x340],xmm0
0x67465db  mov qword ptr [rbp+0x4F0],1
0x67465e6  mov [rbp+0x4F8],r15
0x674660a  mov r8,[0x129FA0C0]
0x6746661  call 0x5679DB0
0x665854f  movups xmm0,[rdi+0x18]
0x665858a  mov r9,[0x129F9F30]
0x66590dd  call 0x5679DB0

CLOSES? YES
Every pending part of H4 is now [V]-proven: terrain (ViewPositionAndTime w=seconds, FogColor, MeshContext, GlobalRoughness) via 6co; weather FogAndDistanceControl (+0x98) plus the other nine weather vec4 uniforms (+0x88 FogColor, +0xA8..+0x118) and OcclusionHeightOffset (+0x80) all read from RenderWeatherDescription and written via 0x5679db0 with name-hash statics; sky FogColor (+0x18) written via 0x5679db0. No blocking fact remains.

## TOOL REQUESTS
None.
