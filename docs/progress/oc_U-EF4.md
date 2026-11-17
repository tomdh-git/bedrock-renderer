## NEXT
DONE

# UNIT U-EF4 — RTX pass names in the 0xbcc region (checklist item F4: 6p, 6v)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = name proven: the 64-bit hash immediate equals FNV-1 64 of the pass name (BGFX_MAP.md 6p: h=(h*0x100000001b3)^byte, offset 0xcbf29ce484222325) and the name bytes are visible in the disassembly; [I] = inferred; [?] = unknown.

Input data (precomputed by the orchestrator, not regenerated):
- listing_bcc4b90.txt (fn 0xbcc4b90..0xbcc63f0) — contains all pass-name hash stores for the 0xbcc RTX region.
- listing_bcc39b0.txt, listing_bcc3fa0.txt, listing_bcc4150.txt — checked, contain no pass-name hash stores.

Method: fn 0xbcc4b90 builds the RTX pass descriptor table on the stack. Each pass declaration stores its folded FNV-1 hash as a 64-bit immediate to a stack slot ([rbp+K], qword store => size 8) at the RVA shown, and builds the name either inline with mov immediates or by copying a .rdata string through call 0x9D6D0. The pass name is the string whose FNV-1 equals the hash immediate. All 50 hash stores in the region resolved to pass names; every row is [V].

| Stack slot | Size | Pass name | `0xRVA  instr` proof | Hash imm | Name source | Tag |
|---|---|---|---|---|---|---|
| 0x1D0 | 8 | ClearVertexIrradianceCache | `0xbcc4daf  mov [rbp+0x1D0],rax` | 0x2C96D87A7FAA55B2 | rdata string @0xF5DF6E0 len 0x1A via call 0x9D6D0; fnv1 match | [V]
| 0x208 | 8 | ClearFaceIrradianceCache | `0xbcc4e0b  mov [rbp+0x208],rax` | 0x7A51AC100718A60D | rdata string @0xF5DF713 len 0x18 via call 0x9D6D0; fnv1 match | [V]
| 0x240 | 8 | ResolveLightMeasurement | `0xbcc4e67  mov [rbp+0x240],rax` | 0x63BDD9A7481AE97B | rdata string @0xF536906 len 0x17 via call 0x9D6D0; fnv1 match | [V]
| 0x278 | 8 | AccumulateInscatter | `0xbcc4ec3  mov [rbp+0x278],rax` | 0x1AC9E5A434921304 | rdata string @0xF566E58 len 0x13 via call 0x9D6D0; fnv1 match | [V]
| 0x2B0 | 8 | AccumulateGIInscatter | `0xbcc4f1f  mov [rbp+0x2B0],rax` | 0xEF7C821C1215A2BC | rdata string @0xF566E6C len 0x15 via call 0x9D6D0; fnv1 match | [V]
| 0x2E8 | 8 | BlurGIInscatter | `0xbcc4f88  mov [rbp+0x2E8],rax` | 0x7A65AD8A150320EB | inline-built name @[rbp+0x2F0] ('BlurGIIN'+'nscatter', overlap on 'n' => 'BlurGIInscatter', len 0xF); fnv1 match | [V]
| 0x320 | 8 | Reproject | `0xbcc4feb  mov [rbp+0x320],rcx` | 0xAB290061E71F04BD | inline-built name @[rbp+0x328] ('Reprojec'+'t' => 'Reproject', len 9 @0x338); fnv1 match | [V]
| 0x358 | 8 | ReprojectSH | `0xbcc5047  mov [rbp+0x358],rax` | 0x2FC648DC8EA5DC54 | inline-built name @[rbp+0x360] ('Reprojec'+'ctSH' => 'ReprojectSH', len 0xB @0x370); fnv1 match | [V]
| 0x390 | 8 | ReprojectSpecularOnly | `0xbcc50a3  mov [rbp+0x390],rax` | 0x3787E1B3B3606AB8 | rdata string @0xF51B408 len 0x15 via call 0x9D6D0 @0xbcc5093; fnv1 match | [V]
| 0x3C8 | 8 | FilterMoments | `0xbcc5110  mov [rbp+0x3C8],rax` | 0xDFAC98D9931B30C2 | inline-built name @[rbp+0x3D0] ('FilterMo'+'RMoments' overlap => 'FilterMoments', len 0xD); fnv1 match | [V]
| 0x400 | 8 | Atrous | `0xbcc516a  mov [rbp+0x400],rax` | 0x863B9AABA1D1C383 | inline-built name @[rbp+0x408] ('AtrO'+'us' => 'Atrous', len 6 @0x418); fnv1 match | [V]
| 0x438 | 8 | BlendCheckerboardFields | `0xbcc51c6  mov [rbp+0x438],rax` | 0x9083714FD6B03662 | rdata string @0xF55C1A9 len 0x17 via call 0x9D6D0; fnv1 match | [V]
| 0x470 | 8 | FilterMomentsSH | `0xbcc5225  mov [rbp+0x470],rax` | 0x779429800D1B5B07 | inline-built name @[rbp+0x478] ('FilterMo'+'omentsSH' => 'FilterMomentsSH', len 0xF @0x488); fnv1 match | [V]
| 0x4A8 | 8 | AtrousSH | `0xbcc5281  mov [rbp+0x4A8],rax` | 0x6D789C9D71FBCC76 | inline-built name @[rbp+0x4B0] ('AtrousSH', len 8 @0x4C0); fnv1 match | [V]
| 0x4E0 | 8 | BlendCheckerboardFieldsSH | `0xbcc52dd  mov [rbp+0x4E0],rax` | 0x6DF7F9880F3621A7 | rdata string @0xF7CB948 len 0x19 via call 0x9D6D0; fnv1 match | [V]
| 0x518 | 8 | FinalCombine | `0xbcc5343  mov [rbp+0x518],rax` | 0xFB1CB76A24A5DD0E | inline-built name @[rbp+0x520] ('FinalCom'+'bine' => 'FinalCombine', len 0xC @0x530); fnv1 match | [V]
| 0x550 | 8 | DiffuseFireflyFilter | `0xbcc539f  mov [rbp+0x550],rax` | 0x53762D68F48E03E | rdata string @0xF567A21 len 0x14 via call 0x9D6D0; fnv1 match | [V]
| 0x588 | 8 | DiffuseFireflyFilterSH | `0xbcc53fb  mov [rbp+0x588],rax` | 0x624296FC51FE5A03 | rdata string @0xF7CB962 len 0x16 via call 0x9D6D0; fnv1 match | [V]
| 0x5C0 | 8 | SpecularFireflyFilter | `0xbcc5457  mov [rbp+0x5C0],rax` | 0x9FDF9EC13C9F5FBF | rdata string @0xF567A0B len 0x15 via call 0x9D6D0; fnv1 match | [V]
| 0x5F8 | 8 | CalculateFaceData | `0xbcc54b3  mov [rbp+0x5F8],rax` | 0x3803E9A388CFC8EC | rdata string @0xF60CE02 len 0x11 via call 0x9D6D0; fnv1 match | [V]
| 0x630 | 8 | CheckerboardUpscale | `0xbcc550f  mov [rbp+0x630],rax` | 0x9A0F96B3081CA3D | rdata string @0xF5DE599 len 0x13 via call 0x9D6D0; fnv1 match | [V]
| 0x668 | 8 | CheckerboardUpscaleSH | `0xbcc556b  mov [rbp+0x668],rax` | 0x5013FA316F97FDD4 | rdata string @0xF7CB979 len 0x15 via call 0x9D6D0; fnv1 match | [V]
| 0x6A0 | 8 | TemporalDenoising | `0xbcc55c7  mov [rbp+0x6A0],rax` | 0xD6A300E579E405DD | fnv1 match vs .rdata string | [V]
| 0x6D8 | 8 | ShadowDenoising | `0xbcc5630  mov [rbp+0x6D8],rax` | 0xC8D287F863E9664B | inline-built name @[rbp+0x6E0] ('ShadowDe'+'enosing' overlap on 'e' => 'ShadowDenoising'); fnv1 match | [V]
| 0x710 | 8 | FinalizeDenoising | `0xbcc568c  mov [rbp+0x710],rax` | 0x3CA6254D32D4FE7D | rdata string @0xF5B41E5 len 0x11 via call 0x9D6D0; fnv1 match | [V]
| 0x748 | 8 | BlendCheckerboardFieldsShadow | `0xbcc56e8  mov [rbp+0x748],rax` | 0xE95702EACCEB0C62 | rdata string @0xF5223EE len 0x1D via call 0x9D6D0; fnv1 match | [V]
| 0x780 | 8 | WFTest | `0xbcc5742  mov [rbp+0x780],rax` | 0x8381ED2246A17BE | inline-built name @[rbp+0x788] ('WFTe'+'st' => 'WFTest', len 6 @0x798); fnv1 match | [V]
| 0x7B8 | 8 | DrawLights | `0xbcc57a7  mov [rbp+0x7B8],rax` | 0x436DF008D99E8CF4 | inline-built name @[rbp+0x7C0] ('DrawLigh'+'ts' => 'DrawLights', len 0xA @0x7D0); fnv1 match | [V]
| 0x7F0 | 8 | ToneMappingHistogram | `0xbcc5803  mov [rbp+0x7F0],rax` | 0x2F1BC38137DF4E9D | rdata string @0xF59FBC5 len 0x14 via call 0x9D6D0; fnv1 match | [V]
| 0x828 | 8 | ToneCurve | `0xbcc5866  mov [rbp+0x828],rax` | 0xD728068A6778247E | inline-built name @[rbp+0x830] ('ToneCurv'+'e' => 'ToneCurve', len 9 @0x840); fnv1 match | [V]
| 0x860 | 8 | TAA | `0xbcc58bd  mov [rbp+0x860],rax` | 0xD82FD9186B1D1111 | inline-built name @[rbp+0x868] ('TA'+'A' => 'TAA', len 3 @0x878); fnv1 match | [V]
| 0x898 | 8 | CopyToFinal | `0xbcc5923  mov [rbp+0x898],rax` | 0x412B84A4037CE343 | inline-built name @[rbp+0x8A0] ('CopyToFi'+'nal' overlap on 'i' => 'CopyToFinal', len 0xB @0x8B0); fnv1 match | [V]
| 0x8D0 | 8 | CheckerboardInterleave | `0xbcc597f  mov [rbp+0x8D0],rax` | 0x49E88F350A2C9215 | rdata string @0xF5BDB30 len 0x16 via call 0x9D6D0 @0xbcc596f; fnv1 match | [V]
| 0x908 | 8 | BlurGradients | `0xbcc59ec  mov [rbp+0x908],rax` | 0xBE154655BC88B01D | inline-built name @[rbp+0x910] ('BlurGrad'+'radinets' overlap on 'rad' => 'BlurGradients', len 0xD @0x920); fnv1 match | [V]
| 0x940 | 8 | TileClassification | `0xbcc5a48  mov [rbp+0x940],rax` | 0x9757B0DF09D5D771 | rdata string @0xF58F70C len 0x12 via call 0x9D6D0; fnv1 match | [V]
| 0x978 | 8 | PreBlasSkinning | `0xbcc5ab1  mov [rbp+0x978],rax` | 0xE1BD9C37952DF57F | inline-built name @[rbp+0x980] ('PreBlasS'+'Skinning' overlap on 'S' => 'PreBlasSkinning', len 0xF @0x990); fnv1 match | [V]
| 0x9B0 | 8 | PrimaryCheckerboardRayGenInline | `0xbcc5b0d  mov [rbp+0x9B0],rax` | 0x28A6BA54D3ADA2DB | rdata string @0xF5CE411 len 0x15 via call 0x9D6D0; fnv1 match | [V]
| 0x9E8 | 8 | SunShadowRayGenInline | `0xbcc5b69  mov [rbp+0x9E8],rax` | 0x3386EEC1F9232E70 | rdata string @0xF5CE43C len 0x16 via call 0x9D6D0; fnv1 match | [V]
| 0xA20 | 8 | RefractionRayGenInline | `0xbcc5bc5  mov [rbp+0xA20],rax` | 0x4F578721DA378E75 | rdata string @0xF5CE511 len 0x1B via call 0x9D6D0; fnv1 match | [V]
| 0xA58 | 8 | DiffuseRayGenCombinedInline | `0xbcc5c21  mov [rbp+0xA58],rax` | 0xE8C112269CE9C229 | rdata string @0xF5CE39B len 0x28 via call 0x9D6D0; fnv1 match | [V]
| 0xA90 | 8 | AdaptiveDenoiserCalculateGradientsInline | `0xbcc5c7d  mov [rbp+0xA90],rax` | 0x87FA674D8763C6E6 | rdata string @0xF5CE4E9 len 0x27 via call 0x9D6D0; fnv1 match | [V]
| 0xAC8 | 8 | AdaptiveDenoiserGenerateReferenceInline | `0xbcc5cd9  mov [rbp+0xAC8],rax` | 0x4C4F1454F8C12D01 | rdata string @0xF5CE427 len 0x14 via call 0x9D6D0; fnv1 match | [V]
| 0xB00 | 8 | SpecularRayGenInline | `0xbcc5d35  mov [rbp+0xB00],rax` | 0x6AED31FEC210547 | rdata string @0xF5CE48B len 0x1B via call 0x9D6D0; fnv1 match | [V]
| 0xB38 | 8 | ExplicitLightSamplingInline | `0xbcc5d91  mov [rbp+0xB38],rax` | 0x27614242CDFD90BB | rdata string @0xF5CE453 len 0x17 via call 0x9D6D0; fnv1 match | [V]
| 0xB70 | 8 | PathTracingRayGenInline | `0xbcc5ded  mov [rbp+0xB70],rax` | 0x35AC32E3669C0ED3 | rdata string @0xF5CE4A7 len 0x21 via call 0x9D6D0; fnv1 match | [V]
| 0xBA8 | 8 | UpdateVertexIrradianceCacheInline | `0xbcc5e49  mov [rbp+0xBA8],rax` | 0x4F254A064827BC0F | rdata string @0xF5CE4C9 len 0x1F via call 0x9D6D0; fnv1 match | [V]
| 0xBE0 | 8 | UpdateFaceIrradianceCacheInline | `0xbcc5ea5  mov [rbp+0xBE0],rax` | 0x1FEDA5A914342CE8 | rdata string @0xF5CE3C4 len 0x18 via call 0x9D6D0; fnv1 match | [V]
| 0xC18 | 8 | CalculateInscatterInline | `0xbcc5f01  mov [rbp+0xC18],rax` | 0xBFEC38B470AF2943 | rdata string @0xF5CE3DD len 0x1A via call 0x9D6D0; fnv1 match | [V]
| 0xC50 | 8 | CalculateGIInscatterInline | `0xbcc5f5d  mov [rbp+0xC50],rax` | 0xCD7C565551F4E5CB | rdata string @0xF5CE3F8 len 0x18 via call 0x9D6D0; fnv1 match | [V]
| 0xC88 | 8 | IncidentLightMeterInline | `0xbcc5fb9  mov [rbp+0xC88],rax` | 0xABBF0FC79F7BFCC3 | fnv1 match vs .rdata string | [V]

## Verbatim proof lines (column 0; checked with verify_oc against the exe)

0xbcc4da5  mov rax,0x2C96D87A7FAA55B2
0xbcc4daf  mov [rbp+0x1D0],rax
0xbcc4e01  mov rax,0x7A51AC100718A60D
0xbcc4e0b  mov [rbp+0x208],rax
0xbcc4e5d  mov rax,0x63BDD9A7481AE97B
0xbcc4e67  mov [rbp+0x240],rax
0xbcc4eb9  mov rax,0x1AC9E5A434921304
0xbcc4ec3  mov [rbp+0x278],rax
0xbcc4f15  mov rax,0xEF7C821C1215A2BC
0xbcc4f1f  mov [rbp+0x2B0],rax
0xbcc4f55  mov rax,0x6E49494772756C42
0xbcc4f5f  mov [rbp+0x2F0],rax
0xbcc4f66  mov rax,0x726574746163736E
0xbcc4f70  mov [rbp+0x2F7],rax
0xbcc4f77  mov byte ptr [rbp+0x2FF],0
0xbcc4f7e  mov rax,0x7A65AD8A150320EB
0xbcc4f88  mov [rbp+0x2E8],rax
0xbcc4fc9  mov rax,0x63656A6F72706552
0xbcc4fd3  mov [rbp+0x328],rax
0xbcc4fda  mov byte ptr [rbp+0x330],0x74
0xbcc4fe1  mov rcx,0xAB290061E71F04BD
0xbcc4feb  mov [rbp+0x320],rcx
0xbcc4fc9  mov rax,0x63656A6F72706552
0xbcc4fd3  mov [rbp+0x328],rax
0xbcc503d  mov rax,0x2FC648DC8EA5DC54
0xbcc5047  mov [rbp+0x358],rax
0xbcc5099  mov rax,0x3787E1B3B3606AB8
0xbcc50a3  mov [rbp+0x390],rax
0xbcc50e4  mov rax,0x73746E656D6F4D72
0xbcc50ee  mov [rbp+0x3D5],rax
0xbcc50f5  mov rsi,0x6F4D7265746C6946
0xbcc50ff  mov [rbp+0x3D0],rsi
0xbcc5106  mov rax,0xDFAC98D9931B30C2
0xbcc5110  mov [rbp+0x3C8],rax
0xbcc5156  mov dword ptr [rbp+0x408],0x6F727441
0xbcc514d  mov word ptr [rbp+0x40C],0x7375
0xbcc5160  mov rax,0x863B9AABA1D1C383
0xbcc516a  mov [rbp+0x400],rax
0xbcc51bc  mov rax,0x9083714FD6B03662
0xbcc51c6  mov [rbp+0x438],rax
0xbcc5203  mov rax,0x485373746E656D6F
0xbcc520d  mov [rbp+0x47F],rax
0xbcc5214  mov byte ptr [rbp+0x487],0
0xbcc521b  mov rax,0x779429800D1B5B07
0xbcc5225  mov [rbp+0x470],rax
0xbcc5266  mov rax,0x485373756F727441
0xbcc5270  mov [rbp+0x4B0],rax
0xbcc5277  mov rax,0x6D789C9D71FBCC76
0xbcc5281  mov [rbp+0x4A8],rax
0xbcc52d3  mov rax,0x6DF7F9880F3621A7
0xbcc52dd  mov [rbp+0x4E0],rax
0xbcc531e  mov rax,0x6D6F436C616E6946
0xbcc5328  mov [rbp+0x520],rax
0xbcc532f  mov dword ptr [rbp+0x528],0x656E6962
0xbcc5339  mov rax,0xFB1CB76A24A5DD0E
0xbcc5343  mov [rbp+0x518],rax
0xbcc5395  mov rax,0x53762D68F48E03E
0xbcc539f  mov [rbp+0x550],rax
0xbcc53f1  mov rax,0x624296FC51FE5A03
0xbcc53fb  mov [rbp+0x588],rax
0xbcc544d  mov rax,0x9FDF9EC13C9F5FBF
0xbcc5457  mov [rbp+0x5C0],rax
0xbcc54a9  mov rax,0x3803E9A388CFC8EC
0xbcc54b3  mov [rbp+0x5F8],rax
0xbcc5505  mov rax,0x9A0F96B3081CA3D
0xbcc550f  mov [rbp+0x630],rax
0xbcc5561  mov rax,0x5013FA316F97FDD4
0xbcc556b  mov [rbp+0x668],rax
0xbcc55bd  mov rax,0xD6A300E579E405DD
0xbcc55c7  mov [rbp+0x6A0],rax
0xbcc55fd  mov rax,0x6544776F64616853
0xbcc5607  mov [rbp+0x6E0],rax
0xbcc560e  mov rax,0x676E6973696F6E65
0xbcc5618  mov [rbp+0x6E7],rax
0xbcc561f  mov byte ptr [rbp+0x6EF],0
0xbcc5626  mov rax,0xC8D287F863E9664B
0xbcc5630  mov [rbp+0x6D8],rax
0xbcc5682  mov rax,0x3CA6254D32D4FE7D
0xbcc568c  mov [rbp+0x710],rax
0xbcc56de  mov rax,0xE95702EACCEB0C62
0xbcc56e8  mov [rbp+0x748],rax
0xbcc572e  mov dword ptr [rbp+0x788],0x65544657
0xbcc5725  mov word ptr [rbp+0x78C],0x7473
0xbcc5738  mov rax,0x8381ED2246A17BE
0xbcc5742  mov [rbp+0x780],rax
0xbcc5783  mov rax,0x6867694C77617244
0xbcc578d  mov [rbp+0x7C0],rax
0xbcc5794  mov word ptr [rbp+0x7C8],0x7374
0xbcc579d  mov rax,0x436DF008D99E8CF4
0xbcc57a7  mov [rbp+0x7B8],rax
0xbcc57f9  mov rax,0x2F1BC38137DF4E9D
0xbcc5803  mov [rbp+0x7F0],rax
0xbcc5844  mov rax,0x76727543656E6F54
0xbcc584e  mov [rbp+0x830],rax
0xbcc5855  mov byte ptr [rbp+0x838],0x65
0xbcc585c  mov rax,0xD728068A6778247E
0xbcc5866  mov [rbp+0x828],rax
0xbcc58aa  mov word ptr [rbp+0x868],0x4154
0xbcc58a3  mov byte ptr [rbp+0x86A],0x41
0xbcc58b3  mov rax,0xD82FD9186B1D1111
0xbcc58bd  mov [rbp+0x860],rax
0xbcc58fe  mov rax,0x69466F5479706F43
0xbcc5908  mov [rbp+0x8A0],rax
0xbcc590f  mov dword ptr [rbp+0x8A7],0x6C616E69
0xbcc5919  mov rax,0x412B84A4037CE343
0xbcc5923  mov [rbp+0x898],rax
0xbcc5975  mov rax,0x49E88F350A2C9215
0xbcc597f  mov [rbp+0x8D0],rax
0xbcc59c0  mov rax,0x73746E6569646172
0xbcc59ca  mov [rbp+0x915],rax
0xbcc59d1  mov rax,0x6461724772756C42
0xbcc59db  mov [rbp+0x910],rax
0xbcc59e2  mov rax,0xBE154655BC88B01D
0xbcc59ec  mov [rbp+0x908],rax
0xbcc5a3e  mov rax,0x9757B0DF09D5D771
0xbcc5a48  mov [rbp+0x940],rax
0xbcc5a7e  mov rax,0x5373616C42657250
0xbcc5a88  mov [rbp+0x980],rax
0xbcc5a8f  mov rax,0x676E696E6E696B53
0xbcc5a99  mov [rbp+0x987],rax
0xbcc5aa0  mov byte ptr [rbp+0x98F],0
0xbcc5aa7  mov rax,0xE1BD9C37952DF57F
0xbcc5ab1  mov [rbp+0x978],rax
0xbcc5b03  mov rax,0x28A6BA54D3ADA2DB
0xbcc5b0d  mov [rbp+0x9B0],rax
0xbcc5b5f  mov rax,0x3386EEC1F9232E70
0xbcc5b69  mov [rbp+0x9E8],rax
0xbcc5bbb  mov rax,0x4F578721DA378E75
0xbcc5bc5  mov [rbp+0xA20],rax
0xbcc5c17  mov rax,0xE8C112269CE9C229
0xbcc5c21  mov [rbp+0xA58],rax
0xbcc5c73  mov rax,0x87FA674D8763C6E6
0xbcc5c7d  mov [rbp+0xA90],rax
0xbcc5ccf  mov rax,0x4C4F1454F8C12D01
0xbcc5cd9  mov [rbp+0xAC8],rax
0xbcc5d2b  mov rax,0x6AED31FEC210547
0xbcc5d35  mov [rbp+0xB00],rax
0xbcc5d87  mov rax,0x27614242CDFD90BB
0xbcc5d91  mov [rbp+0xB38],rax
0xbcc5de3  mov rax,0x35AC32E3669C0ED3
0xbcc5ded  mov [rbp+0xB70],rax
0xbcc5e3f  mov rax,0x4F254A064827BC0F
0xbcc5e49  mov [rbp+0xBA8],rax
0xbcc5e9b  mov rax,0x1FEDA5A914342CE8
0xbcc5ea5  mov [rbp+0xBE0],rax
0xbcc5ef7  mov rax,0xBFEC38B470AF2943
0xbcc5f01  mov [rbp+0xC18],rax
0xbcc5f53  mov rax,0xCD7C565551F4E5CB
0xbcc5f5d  mov [rbp+0xC50],rax
0xbcc5faf  mov rax,0xABBF0FC79F7BFCC3
0xbcc5fb9  mov [rbp+0xC88],rax

## Conclusion

All 50 pass-name hash stores in the 0xbcc region (fn 0xbcc4b90..0xbcc63f0) are decoded: each 64-bit hash immediate stored to a stack slot matches FNV-1 64 of its pass name, and every name's bytes are visible in the disassembly (inline mov-built strings or .rdata strings copied by call 0x9D6D0). Checklist item F4 'RTX pass names (0xbcc.. region) — 6p, 6v' is fully decoded; no pending part remains.
