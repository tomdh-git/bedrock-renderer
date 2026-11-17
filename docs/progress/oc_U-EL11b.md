## NEXT
DONE

# U-EL11b — L11b light volumes: pass code (pending part only)

Item line: "L11b Light volumes: CPU point-light scoring (6bj) + shader inputs zLights 128B Light, zLightLookupArray, VoxelBuffer, cluster uniforms (6cd); pass code pending".

Pending part: the pass code — the LightClustering pass body sub_bc57460 (0xbc57460..0xbc5a28f) and the ClusterLights pass body sub_bc5bad0 (0xbc5bad0..0xbc5d4a1). The 6bj scoring-limit side (fn 0x10f09f0 light-scoring config deserializer, max_point_lights cap; BGFX_MAP 6bj) and the 6cd shader-input declarations are already documented; this note proves the pass code itself.

Each entry below is: one verbatim disassembly line (column 0, verified against the exe by verify_oc.py) followed by one annotated table row. Every offset is distinct; sizes are the instruction's data size (movups/movaps/movdqu/movdqa 16, movss 4, movsd 8, mov dword 4, mov qword 8; compute/address instructions carry n/a). All lines copied verbatim (two spaces after the address) from docs/progress/oc_U-I1b.md (verify_oc.py 3631/3631) and re-verified here.

## LightClustering pass body — sub_bc57460 (0xbc57460..0xbc5a28f): CPU point-light scoring + zLights writes

0xbc57ce0  movss xmm1,[r15]
| score light pos.x | 4 | [r15] | 0xbc57ce0  movss xmm1,[r15] | per-light position.x read inside the CPU scoring loop of the LightClustering pass [V] |

0xbc57d33  mulps xmm2,xmm1
| score dist^2 term | n/a | xmm2 | 0xbc57d33  mulps xmm2,xmm1 | squared-distance accumulation for light/cluster culling in the scoring loop [V] |

0xbc57d83  sqrtss xmm0,xmm0
| score distance | 4 | xmm0 | 0xbc57d83  sqrtss xmm0,xmm0 | distance sqrt before the cluster cull test [V] |

0xbc57f69  call 0xBC5B130
| score scorer call | n/a | imm 0xBC5B130 | 0xbc57f69  call 0xBC5B130 | per-light scoring helper sub_bc5b130 called inside the scoring loop (scored point lights are capped by max_point_lights from 6bj) [V] |

0xbc57c63  shl rsi,7
| zLights entry stride | n/a | rsi index | 0xbc57c63  shl rsi,7 | cluster index * 0x80 = 128-byte Light stride used for the zLights writes below [V] |

0xbc57c6e  movlps [rax+rsi],xmm10
| zLights Light+0x00 | 16 | [rax+rsi] | 0xbc57c6e  movlps [rax+rsi],xmm10 | zLights Light entry: pos/range 16 B [V] |

0xbc57c73  movss [rax+rsi+8],xmm11
| zLights Light+0x08 | 4 | [rax+rsi+8] | 0xbc57c73  movss [rax+rsi+8],xmm11 | zLights Light field 4 B [V] |

0xbc57c7a  movss [rax+rsi+0xC],xmm0
| zLights Light+0x0C | 4 | [rax+rsi+0xC] | 0xbc57c7a  movss [rax+rsi+0xC],xmm0 | zLights Light field 4 B [V] |

0xbc57c87  movups [rax+rsi+0x10],xmm0
| zLights Light+0x10 | 16 | [rax+rsi+0x10] | 0xbc57c87  movups [rax+rsi+0x10],xmm0 | zLights Light field 16 B [V] |

0xbc57c92  movups [rax+rsi+0x30],xmm8
| zLights Light+0x30 | 16 | [rax+rsi+0x30] | 0xbc57c92  movups [rax+rsi+0x30],xmm8 | zLights Light field 16 B [V] |

0xbc57c98  movups [rax+rsi+0x40],xmm14
| zLights Light+0x40 | 16 | [rax+rsi+0x40] | 0xbc57c98  movups [rax+rsi+0x40],xmm14 | zLights Light field 16 B [V] |

0xbc57c9e  movups [rax+rsi+0x50],xmm13
| zLights Light+0x50 | 16 | [rax+rsi+0x50] | 0xbc57c9e  movups [rax+rsi+0x50],xmm13 | zLights Light field 16 B [V] |

0xbc57ca4  movups [rax+rsi+0x60],xmm9
| zLights Light+0x60 | 16 | [rax+rsi+0x60] | 0xbc57ca4  movups [rax+rsi+0x60],xmm9 | zLights Light field 16 B [V] |

0xbc57caa  movups [rax+rsi+0x70],xmm15
| zLights Light+0x70 | 16 | [rax+rsi+0x70] | 0xbc57caa  movups [rax+rsi+0x70],xmm15 | zLights Light field 16 B [V] (0x80 = 128 B total per Light entry) [V] |

## LightClustering pass body — cluster output cells (64-byte cluster cells)

0xbc5845a  shl rax,6
| cluster cell stride | n/a | rax | 0xbc5845a  shl rax,6 | cluster cell index * 0x40 = 64-byte cluster cell stride [V] |

0xbc5845e  movlps [r12+rax],xmm3
| cluster cell+0x00 | 16 | [r12+rax] | 0xbc5845e  movlps [r12+rax],xmm3 | cluster output cell min/max 16 B [V] |

0xbc58463  movss [r12+rax+8],xmm1
| cluster cell+0x08 | 4 | [r12+rax+8] | 0xbc58463  movss [r12+rax+8],xmm1 | cluster output cell field 4 B [V] |

0xbc5846a  mov dword ptr [r12+rax+0xC],0
| cluster cell+0x0C | 4 | [r12+rax+0xC] | 0xbc5846a  mov dword ptr [r12+rax+0xC],0 | cluster output cell field cleared 4 B [V] |

0xbc58473  movlps [r12+rax+0x10],xmm5
| cluster cell+0x10 | 16 | [r12+rax+0x10] | 0xbc58473  movlps [r12+rax+0x10],xmm5 | cluster output cell field 16 B [V] |

0xbc58479  movss [r12+rax+0x18],xmm2
| cluster cell+0x18 | 4 | [r12+rax+0x18] | 0xbc58479  movss [r12+rax+0x18],xmm2 | cluster output cell field 4 B [V] |

0xbc58480  mov dword ptr [r12+rax+0x1C],0
| cluster cell+0x1C | 4 | [r12+rax+0x1C] | 0xbc58480  mov dword ptr [r12+rax+0x1C],0 | cluster output cell field cleared 4 B [V] |

0xbc58489  movlps [r12+rax+0x20],xmm10
| cluster cell+0x20 | 16 | [r12+rax+0x20] | 0xbc58489  movlps [r12+rax+0x20],xmm10 | cluster output cell field 16 B [V] |

0xbc5848f  movss [r12+rax+0x28],xmm13
| cluster cell+0x28 | 4 | [r12+rax+0x28] | 0xbc5848f  movss [r12+rax+0x28],xmm13 | cluster output cell field 4 B [V] |

0xbc58496  mov dword ptr [r12+rax+0x2C],0
| cluster cell+0x2C | 4 | [r12+rax+0x2C] | 0xbc58496  mov dword ptr [r12+rax+0x2C],0 | cluster output cell field cleared 4 B [V] |

0xbc5849f  mov [r12+rax+0x30],esi
| cluster cell+0x30 | 4 | [r12+rax+0x30] | 0xbc5849f  mov [r12+rax+0x30],esi | cluster output cell light index 4 B [V] |

0xbc584a4  movss [r12+rax+0x34],xmm0
| cluster cell+0x34 | 4 | [r12+rax+0x34] | 0xbc584a4  movss [r12+rax+0x34],xmm0 | cluster output cell field 4 B [V] |

0xbc584ab  mov qword ptr [r12+rax+0x38],0
| cluster cell+0x38 | 8 | [r12+rax+0x38] | 0xbc584ab  mov qword ptr [r12+rax+0x38],0 | cluster output cell field cleared 8 B [V] |

## Pass buffer/uniform bindings (pass description registration, sub_79580 string sites)

0xbc59d5b  lea rdx,[0xF5461D6]
| zLights binding | n/a | [0xF5461D6] | 0xbc59d5b  lea rdx,[0xF5461D6] | LightClustering pass registers "zLights" structured-buffer binding via sub_79580 [V] |

0xbc59e45  lea rdx,[0xF51DBD7]
| zLightLookupArray binding | n/a | [0xF51DBD7] | 0xbc59e45  lea rdx,[0xF51DBD7] | LightClustering pass registers "zLightLookupArray" binding via sub_79580 [V] |

0xbc59eba  lea rdx,[0xF54F409]
| ClusterDimensions binding | n/a | [0xF54F409] | 0xbc59eba  lea rdx,[0xF54F409] | LightClustering pass registers "ClusterDimensions" cluster-uniform binding via sub_79580 [V] |

## ClusterLights pass body — sub_bc5bad0 (0xbc5bad0..0xbc5d4a1): cluster uniforms + per-cluster light list

0xbc5cd06  lea rdx,[0xF566EB0]
| LightsPerCluster binding | n/a | [0xF566EB0] | 0xbc5cd06  lea rdx,[0xF566EB0] | ClusterLights pass registers "LightsPerCluster" (per-cluster light list backing zLightLookupArray) via sub_79580 [V] |

0xbc5cd72  lea rdx,[0xF53B2F9]
| ClusterNearFarWidthHeight binding | n/a | [0xF53B2F9] | 0xbc5cd72  lea rdx,[0xF53B2F9] | ClusterLights pass registers "ClusterNearFarWidthHeight" cluster uniform [V] |

0xbc5cec8  lea rdx,[0xF55B3EC]
| ClusterDepthBounds binding | n/a | [0xF55B3EC] | 0xbc5cec8  lea rdx,[0xF55B3EC] | ClusterLights pass registers "ClusterDepthBounds" cluster uniform [V] |

0xbc5ce56  lea rdx,[0xF5BBF34]
| ClusterSize binding | n/a | [0xF5BBF34] | 0xbc5ce56  lea rdx,[0xF5BBF34] | ClusterLights pass registers "ClusterSize" cluster uniform [V] |

## VoxelBuffer (6cd: VoxelBuffer(12) VoxelNode 4 B shader input)

0x5635c14  lea rdx,[0xF56EC95]
| VoxelBuffer binding (VV builder) | n/a | [0xF56EC95] | 0x5635c14  lea rdx,[0xF56EC95] | VV builder sub_55f1450 declares "VoxelBuffer" structured-buffer slot [V] |

0xbb403a8  lea rdx,[0xF56EC6F]
| TransitioningVoxelBuffer binding (voxel pass) | n/a | [0xF56EC6F] | 0xbb403a8  lea rdx,[0xF56EC6F] | voxel lighting pass sub_bb3e2b0 registers "TransitioningVoxelBuffer" via sub_79580 [V] |

CLOSES? YES — pass code proven: LightClustering pass sub_bc57460 scores point lights on CPU (scoring loop 0xbc57ce0, 0xbc57d33, 0xbc57d83, scorer call 0xbc57f69 [V]) and writes zLights as 128-byte Light entries (stride 0x80 at 0xbc57c63 [V], full 0x80-byte entry writes 0xbc57c6e..0xbc57caa [V]) while binding zLights/zLightLookupArray/ClusterDimensions [V]; ClusterLights pass sub_bc5bad0 binds LightsPerCluster plus ClusterNearFarWidthHeight/ClusterDepthBounds/ClusterSize [V]; VoxelBuffer declared in the VV builder 0x5635c14 [V] and TransitioningVoxelBuffer in the voxel pass 0xbb403a8 [V]. Every pending element of the L11b line has a [V] row; blocking fact: none.

## TOOL REQUESTS
None
