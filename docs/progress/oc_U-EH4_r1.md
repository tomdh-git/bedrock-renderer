## NEXT
DONE

# Unit U-EH4 — Per-frame constants close: FogAndDistanceControl/sky/weather pending

Terrain side (6co: ViewPositionAndTime w=seconds, FogColor, MeshContext, GlobalRoughness) is already proven [V] in docs/BGFX_MAP.md section 6co (live capture, scene=The End, game time ~864s): slot 7 MeshContext=(0,0,0,0) at call site 0x66eb6b5; slot 10 ViewPositionAndTime=(-0,0,-0,863.9) w=elapsed seconds at 0x66eb901; slot 2 GlobalRoughness=(0.6563,1.0,128.0,57.0) at 0x66eb998; slot 4 FogColor=(0.0402,0.0494,0.09,1.0) at 0x66eba35. Slot id = index in RenderChunk uniform list order (6cc): 0 DitherParams,1 DitherParams2,2 GlobalRoughness,3 FogAndDistanceControl,4 FogColor,...,7 MeshContext,...,10 ViewPositionAndTime.

Pending parts proven [V] below. Registers: visitor prologue `mov rsi,rdx; mov rbx,rcx; mov rdi,[r8]` => rdi=desc, rsi=frame-ctx, rbx=frameBuilder.

| offset | size | R/W | verbatim instruction line(s) | meaning |
| rsi+0x98 | 16 | R | 0x6746335  movups xmm0,[rsi+0x98] | [V] Weather extractor 0x6745440: desc+0x98 FogAndDistanceControl f4 loaded into xmm0 (WeatherDescription field, per 6745440.md cold-tail field list) |
| rbp+0x340 | 16 | W | 0x674633c  movaps [rbp+0x340],xmm0<br>0x6658553  movaps [rbp+0x340],xmm0 | [V] FogAndDistanceControl (weather, desc+0x98) and FogColor (sky, desc+0x18) vec4 staged to local span buffer arr[0]; both sites write the same local offset |
| rbp+0x4F0 | 8 | W | 0x6746343  mov qword ptr [rbp+0x4F0],1 | [V] Weather: span count=1 (one vec4) for FogAndDistanceControl |
| rbp+0x4F8 | 8 | W | 0x674634e  mov [rbp+0x4F8],r15 | [V] Weather: span ptr = r15=&rbp+0x340 (local arr) |
| rbp+0x1E0 | 8 | W | 0x665855a  mov qword ptr [rbp+0x1E0],1 | [V] Sky visitor case 5/tag5: span count=1 (one vec4) for FogColor |
| rbp+0x1E8 | 8 | W | 0x6658565  mov [rbp+0x1E8],r15 | [V] Sky visitor case 5/tag5: span ptr = r15=&rbp+0x340 (local arr) |
| 0x129F9FF0 | 8 | R | 0x674635d  mov rdx,[0x129F9FF0] | [V] Weather: FogAndDistanceControl name-hash static (FNV-1a); scanned against slot-entry [+0x28] name hash |
| 0x129F9F30 | 8 | R | 0x665858a  mov r9,[0x129F9F30] | [V] Sky visitor case 5/tag5: FogColor name-hash static (FNV-1a); scanned against slot-entry [+0x28] name hash |
| shaderbuf+slot3 | 16 | W | 0x67463b4  call 0x5679DB0 | [V] Weather: FogAndDistanceControl vec4 span (count=1 at rbp+0x4F0, ptr at rbp+0x4F8) written to FogAndDistanceControl slot; slot id = index 3 per RenderChunk uniform list order (6cc) via 0x5679db0 |
| shaderbuf+FogColor_slot | 16 | W | 0x66590dd  call 0x5679DB0 | [V] Sky visitor case 5/tag5: FogColor vec4 span (count=1 at rbp+0x1E0, ptr at rbp+0x1E8) written to FogColor slot; slot id = index in material uniform list per 6cc via 0x5679db0 |

## Verbatim instruction proof lines (verified against the exe)

0x6746335  movups xmm0,[rsi+0x98]
0x674633c  movaps [rbp+0x340],xmm0
0x6746343  mov qword ptr [rbp+0x4F0],1
0x674634e  mov [rbp+0x4F8],r15
0x674635d  mov rdx,[0x129F9FF0]
0x67463b4  call 0x5679DB0
0x665854f  movups xmm0,[rdi+0x18]
0x6658553  movaps [rbp+0x340],xmm0
0x665855a  mov qword ptr [rbp+0x1E0],1
0x6658565  mov [rbp+0x1E8],r15
0x665858a  mov r9,[0x129F9F30]
0x66590dd  call 0x5679DB0

CLOSES? YES
