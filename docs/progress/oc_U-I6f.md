## NEXT
Last line analysed: 0xbcb1d06 (line 4140) - END OF LISTING

## RANGE 1: 0xbcacd90..0xbcad53c (lines 1-400)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcacd90..0xbcacdf6 | Function prologue: saves callee-saved registers, allocates stack frame (0x1028 bytes via __chkstk), sets up rbp frame pointer at rsp+0x80, spills xmm6-xmm9, stores args (rcx,rdx,r8,r9) to [rbp+0xF40/0xF38/0xA60/0xF30], reads global 0x12AE23E8 |
| 0xbcacdfc..0xbcacef3 | Eight identical TLS guard checks: each loads a global (0x12AE23E8..0x12AE2458 step 0x10), reads TLS slot at gs:[0x58] + index*8 from 0x128767C8, compares global vs [rcx+4], jumps to error handlers 0xBCAF698..0xBCAF9B6 if global > TLS value |
| 0xbcacef9..0xbcacfd1 | Two more TLS guard checks for globals 0x12AE2468, 0x12AE2478, 0x12AE2488, 0x12AE2498, 0x12AE24A8 (same pattern, jumps to 0xBCAFA28..0xBCAFBF0) |
| 0xbcacfd7..0xbcad002 | Loads from [rbp+0x1050]→rax, [rbp+0x1038]→rcx→[rcx+8]→[rbp+0xA68], [rax+8]→[rbp+0xA70], [r15+0x28]→xmm0, calls 0xEEC7000 (returns float in xmm0), saves to xmm6 |
| 0xbcad008..0xbcad04c | Loads [r15+0x38]→xmm0, cvtss2sd, calls 0xEEC7430 (sd→sd), tests byte [r15], loads const from 0xEEC8060 to xmm7 (zeroed if [r15]==0), cvtsd2ss xmm8, loads [r14+8]→r14, tests byte [r15+0x34] (zeroes xmm1 if clear), cvtsi2ss [r15+8]→xmm0, mulss xmm8 * [0xF35EBD0] |
| 0xbcad052..0xbcad108 | Builds struct at [rbp+0xA80]: xmm0,xmm6,xmm1,0; sets [rbp+0x310]=1, [rbp+0x318]=rdi; iterates array at r14+8 (count from [r14+0x42]*16), searches for entry matching global 0x12AE2410 at offset 0x28, on match calls 0x5679DB0 with rdx=rbp, r8=[rbp+0x310], rcx=r14+8 |
| 0xbcad10d..0xbcad149 | Loads [r15+0x30]→xmm0 cvtss2sd→call 0xEEC7430→xmm6; loads [r15+0x3C]→xmm9; loads [r15+0x2C]→xmm0 cvtss2sd→call 0xEEC7430; movlhps xmm0,xmm6; cvtpd2ps; mulps * [0xF152830]; stores low 64b to [rbp+0xA80] |
| 0xbcad150..0xbcad162 | Stores xmm8→[rbp+0xA88], xmm9→[rbp+0xA8C]; sets [rbp+0x310]=1, [rbp+0x318]=rdi |
| 0xbcad16d..0xbcad1dc | Second array search: iterates r14+8 array (count [r14+0x42]), matches global 0x12AE2420 at offset 0x28, on match calls 0x5679DB0 with same args |
| 0xbcad1e1..0xbcad200 | Tests bl (from [rbp+0x1030]): if zero xorps xmm0, else loads const 0xEEC8060; loads byte [rbp+0x1060]→bl; xorps xmm1; cvtsi2ss [r15+4]→xmm1 |
| 0xbcad200..0xbcad232 | Builds struct at [rbp+0xA80]: xmm1, xmm7, xmm0, 0; sets [rbp+0x310]=1, [rbp+0x318]=rdi |
| 0xbcad232..0xbcad2a0 | Third array search: iterates r14+8 array, matches global 0x12AE2460 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcad2a5..0xbcad2c4 | Tests bl: if zero xorps xmm0, else loads const 0xEEC8060; shufps xmm0,xmm0,0 (broadcast); stores to [rbp+0xA80] |
| 0xbcad2cf..0xbcad33b | Fourth array search: iterates r14+8 array, matches global 0x12AE2470 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcad340..0xbcad39b | Loads [r15+0x40],[r15+0x44]→call rdi (0xF9A8F28)→xmm6; loads [r15+0x40],[r15+0x4C]→call rdi→xmm0→xmm3; mulss xmm3*xmm2([r15+0x48]); xmm4=xmm6-xmm3; mulss xmm6*xmm2; xmm6=xmm6-xmm3; divss xmm4/xmm6; xmm2=xmm0*xmm4; xmm0=xmm0-xmm2 |
| 0xbcad3a1..0xbcad3d3 | Stores xmm1→[rbp+0xA80], xmm4→[rbp+0xA84], xmm0→[rbp+0xA88], [r15+0x50]→[rbp+0xA8C]; sets [rbp+0x310]=1, [rbp+0x318]=rdi |
| 0xbcad3da..0xbcad440 | Fifth array search: iterates r14+8 array, matches global 0x12AE2490 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcad445..0xbcad4d8 | Sixth array search: iterates r14+8 array, matches global 0x12AE24A0 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcad4dd..0xbcad53c | Four more TLS guard checks for globals 0x12AE22C8, 0x12AE22D8, 0x12AE22E8 (same pattern, jumps to 0xBCAFC62, 0xBCAFCD4, ...) |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| 0xEEC8060 | [UNVERIFIED: 0xEEC8060 float constant] | 0xbcad014 (movss xmm1,[0xEEC8060]), 0xbcad1f8, 0xbcad2bc, 0xbcad2c2 |
| 0xF35EBD0 | [UNVERIFIED: 0xF35EBD0 float constant] | 0xbcad052 (mulss xmm8,[0xF35EBD0]) |
| 0xF152830 | [UNVERIFIED: 0xF152830 float constant/vector] | 0xbcad142 (mulps xmm0,[0xF152830]) |
| 0xF9A8F28 | [UNVERIFIED: 0xF9A8F28 function pointer] | 0xbcad350 (mov rdi,[0xF9A8F28]), called at 0xbcad357, 0xbcad368 |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0xE9E7970 | __chkstk (stack probe) | call | [V] |
| 0xEEC7000 | unknown (float→float) | call | [V] |
| 0xEEC7430 | unknown (double→double) | call | [V] |
| 0x5679DB0 | unknown (array callback) | call | [V] |
| 0xF9A8F28 | indirect via rdi | call | [V] |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [rbp+0xF40] | 8 | W | 0xbcacdef | rcx (arg1) saved |
| [rbp+0xF38] | 8 | W | 0xbcacde8 | rdx (arg2) saved |
| [rbp+0xA60] | 8 | W | 0xbcacde1 | r8 (arg3) saved |
| [rbp+0xF30] | 8 | W | 0xbcacdda | r9 (arg4) saved |
| [rbp+0x1050] | 8 | R | 0xbcacfd7 | loaded → rax |
| [rbp+0x1038] | 8 | R | 0xbcacfde | loaded → rcx |
| [rbp+0x1020] | 8 | R | 0xbcacfec | loaded → r15 |
| [rbp+0x1018] | 8 | R | 0xbcad038 | loaded → r14 |
| [rbp+0x1030] | 1 | R | 0xbcad10d | loaded → bl (byte flag) |
| [rbp+0x1060] | 1 | R | 0xbcad1ff | loaded → bl (byte flag) |
| [r15+0x28] | 4 | R | 0xbcad002 | float → xmm0 |
| [r15+0x38] | 4 | R | 0xbcad010 | float → xmm0 |
| [r15+0x0] | 1 | R | 0xbcad01f | byte test |
| [r15+0x34] | 1 | R | 0xbcad03f | byte test |
| [r15+0x8] | 4 | R | 0xbcad04c | int → cvtsi2ss |
| [r15+0x30] | 4 | R | 0xbcad114 | float → xmm0 |
| [r15+0x3C] | 4 | R | 0xbcad11a | float → xmm9 |
| [r15+0x2C] | 4 | R | 0xbcad12c | float → xmm0 |
| [r15+0x40] | 4 | R | 0xbcad344, 0xbcad35c, 0xbcad362 | float (used 3x) |
| [r15+0x44] | 4 | R | 0xbcad34a | float |
| [r15+0x4C] | 4 | R | 0xbcad368 | float |
| [r15+0x48] | 4 | R | 0xbcad370 | float → xmm2 |
| [r15+0x50] | 4 | R | 0xbcad393 | float → [rbp+0xA8C] |
| [r15+0x54] | 4 | R | 0xbcad453 | float → [rbp+0xA80] |
| [r14+0x8] | 8 | R | 0xbcad05b | array base |
| [r14+0x38] | 8 | R | 0xbcad0a1, 0xbcad174, 0xbcad1e1, 0xbcad2a5, 0xbcad340, 0xbcad445 | array base (reloaded) |
| [r14+0x42] | 2 | R | 0xbcad0a5, 0xbcad178, 0xbcad1e5, 0xbcad2ae, 0xbcad3d3, 0xbcad44e | array count (word) |
| [r14+0x42] | 2 | R | multiple | count * 16 = byte length |
| [rcx+8] | 8 | R | 0xbcacfec | from [rbp+0x1038] |
| [rax+8] | 8 | R | 0xbcacff5 | from [rbp+0x1050] |
| [r10+0x28] | 8 | R | 0xbcad0d3, 0xbcad1a4, 0xbcad264, 0xbcad304, 0xbcad404 | array element +0x28 compare |
| [r9+0x28] | 8 | R | 0xbcad1a4, 0xbcad264, 0xbcad304, 0xbcad404, 0xbcad4a3 | array element +0x28 compare |
| [r8+0x28] | 8 | R | 0xbcad0d3, 0xbcad1a4, 0xbcad264, 0xbcad304, 0xbcad404 | global compare target |
| [rbp+0xA80] | 16 | W | 0xbcad066, 0xbcad149, 0xbcad210, 0xbcad2c4, 0xbcad3a1, 0xbcad453 | output struct (4 floats) |
| [rbp+0xA84] | 4/8 | W | 0xbcad06e, 0xbcad150, 0xbcad218, 0xbcad3a9, 0xbcad461 | output struct field 1 |
| [rbp+0xA88] | 4 | W | 0xbcad076, 0xbcad159, 0xbcad220, 0xbcad3b1 | output struct field 2 |
| [rbp+0xA8C] | 4 | W | 0xbcad07e, 0xbcad162, 0xbcad228, 0xbcad3b9, 0xbcad46c | output struct field 3 |
| [rbp+0x310] | 8 | W | 0xbcad082, 0xbcad15f, 0xbcad232, 0xbcad2cf, 0xbcad3c1, 0xbcad461 | =1 (counter/flag) |
| [rbp+0x318] | 8 | W | 0xbcad09a, 0xbcad16d, 0xbcad23d, 0xbcad2da, 0xbcad3d3, 0xbcad481 | =rdi (ptr to [rbp+0xA80]) |
| [rbp+0xF50] | 8 | W | 0xbcad05f | =r14+8 (array base) |
| [rbp+0xF58] | 8 | W | 0xbcacdcf | =-2 (cookie) |
| [rbp] | 2 | W | 0xbcad0f2, 0xbcad1c6, 0xbcad28a, 0xbcad325, 0xbcad42a, 0xbcad4c2 | =cx (match index) |
| [rbp+2] | 1 | W | 0xbcad0f6, 0xbcad1ca, 0xbcad28e, 0xbcad329, 0xbcad42e, 0xbcad4c6 | =1 (found flag) |
| [0x12AE23E8] | 4 | R | 0xbcacdf6 | TLS guard global 1 |
| [0x12AE23F8] | 4 | R | 0xbcace1b | TLS guard global 2 |
| [0x12AE2408] | 4 | R | 0xbcace40 | TLS guard global 3 |
| [0x12AE2418] | 4 | R | 0xbcace65 | TLS guard global 4 |
| [0x12AE2428] | 4 | R | 0xbcace8a | TLS guard global 5 |
| [0x12AE2438] | 4 | R | 0xbcaceaf | TLS guard global 6 |
| [0x12AE2448] | 4 | R | 0xbcaced4 | TLS guard global 7 |
| [0x12AE2458] | 4 | R | 0xbcacef9 | TLS guard global 8 |
| [0x12AE2468] | 4 | R | 0xbcacf1e | TLS guard global 9 |
| [0x12AE2478] | 4 | R | 0xbcacf43 | TLS guard global 10 |
| [0x12AE2488] | 4 | R | 0xbcacf68 | TLS guard global 11 |
| [0x12AE2498] | 4 | R | 0xbcacf8d | TLS guard global 12 |
| [0x12AE24A8] | 4 | R | 0xbcacfb2 | TLS guard global 13 |
| [0x12AE2410] | 8 | R | 0xbcad0b8 | array search target 1 |
| [0x12AE2420] | 8 | R | 0xbcad189 | array search target 2 |
| [0x12AE2460] | 8 | R | 0xbcad24c | array search target 3 |
| [0x12AE2470] | 8 | R | 0xbcad2e9 | array search target 4 |
| [0x12AE2490] | 8 | R | 0xbcad3eb | array search target 5 |
| [0x12AE24A0] | 8 | R | 0xbcad490 | array search target 6 |
| [0x12AE22C8] | 4 | R | 0xbcad4dd | TLS guard global 14 |
| [0x12AE22D8] | 4 | R | 0xbcad502 | TLS guard global 15 |
| [0x12AE22E8] | 4 | R | 0xbcad527 | TLS guard global 16 |
| [0x128767C8] | 4 | R | multiple | TLS index |
| gs:[0x58] | 8 | R | multiple | TEB.ThreadLocalStoragePointer |

## RANGE 2: 0xbcad540..0xbcadcdb (lines 401-800)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcad540..0xbcad771 | Twelve more TLS guard checks for globals 0x12AE22F8..0x12AE23D8 (step 0x10), same pattern: load global, read TLS at gs:[0x58]+index*8 from 0x128767C8, compare vs [rcx+4], jump to handlers 0xBCAFD46..0xBCB03F4 if global > TLS value |
| 0xbcad777..0xbcad7c0 | Loads [rbp+0x1028]→rbx; movsx byte [rbx+0x1C]→eax, byte [rbx+0x14]→ecx; cvtsi2ss ecx→xmm0, loads [rbx+0x18]→xmm1, cvtsi2ss eax→xmm2; stores xmm0,xmm1,xmm2,0 to [rbp+0xA80..0xA8C]; sets [rbp+0x310]=1, [rbp+0x318]=rdi |
| 0xbcad7c7..0xbcad832 | Seventh array search: iterates r14+8 array (count [r14+0x42]), matches global 0x12AE22C0 at offset 0x28, on match calls 0x5679DB0 with rdx=rbp, r8=[rbp+0x310], rcx=[rbp+0xF50] |
| 0xbcad837..0xbcad86d | Loads bytes from rbx: [rbx]→sil, [rbx+8]→r13b, [rbx+9]→r12b, [rbx+0xF4]→r14b, [rbx+0x45]→dil, [rbx+0x46]→r15b; computes r8b = r14b & sil & [rbx+0x44]; loads [rbx+0x28]→xmm0; cvtsi2ss r8d→xmm1; loads [rbx+0x20]→xmm2 (sd); stores xmm2→[rbp+0xA80], xmm0→[rbp+0xA88], xmm1→[rbp+0xA8C] |
| 0xbcad86d..0xbcad912 | Eighth array search: iterates r14+8 array, matches global 0x12AE22D0 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcad917..0xbcad96d | Reloads r14 from [rbp+0x1018]; computes r8b = r14b & r13b & dil; loads [rbx+0x34]→xmm0; cvtsi2ss r8d→xmm1; loads [rbx+0x2C]→xmm2 (sd); stores xmm2→[rbp+0xA80], xmm0→[rbp+0xA88], xmm1→[rbp+0xA8C]; sets up [rbp+0x318]=rdi |
| 0xbcad96d..0xbcad9d2 | Ninth array search: iterates r14+8 array, matches global 0x12AE22E0 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcad9d7..0xbcada1f | Reloads r14; computes r14b = r14b & r12b & r15b; loads [rbx+0x40]→xmm0; cvtsi2ss r14d→xmm1; loads [rbx+0x38]→xmm2 (sd); stores xmm2→[rbp+0xA80], xmm0→[rbp+0xA88], xmm1→[rbp+0xA8C]; sets [rbp+0x318]=rdi |
| 0xbcada1f..0xbcada92 | Tenth array search: iterates r14+8 array, matches global 0x12AE22F0 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcada97..0xbcadab3 | Reloads r14; loads bytes [rbx+0xF5]→r14b, [rbx+0x71]→dil, [rbx+0x72]→r15b; computes r8b = r14b & sil & [rbx+0x70] |
| 0xbcadab3..0xbcadaff | Loads [rbx+0x54]→xmm0; cvtsi2ss r8d→xmm1; loads [rbx+0x4C]→xmm2 (sd); stores xmm2→[rbp+0xA80], xmm0→[rbp+0xA88], xmm1→[rbp+0xA8C]; sets [rbp+0x318]=r8 |
| 0xbcadaff..0xbcadb62 | Eleventh array search: iterates r14+8 array, matches global 0x12AE2300 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcadb67..0xbcadbbd | Reloads r14; computes r8b = r14b & r13b & dil; loads [rbx+0x60]→xmm0; cvtsi2ss r8d→xmm1; loads [rbx+0x58]→xmm2 (sd); stores xmm2→[rbp+0xA80], xmm0→[rbp+0xA88], xmm1→[rbp+0xA8C]; sets [rbp+0x318]=rdi |
| 0xbcadbbd..0xbcadc22 | Twelfth array search: iterates r14+8 array, matches global 0x12AE2310 at offset 0x28, on match calls 0x5679DB0 |
| 0xbcadc27..0xbcadcdb | Reloads r14; computes r14b = r14b & r12b & r15b; loads [rbx+0x6C]→xmm0; cvtsi2ss r14d→xmm1; loads [rbx+0x64]→xmm2 (sd); stores xmm2→[rbp+0xA80], xmm0→[rbp+0xA88], xmm1→[rbp+0xA8C]; sets [rbp+0x318]=rdi; thirteenth array search for global 0x12AE2320 at offset 0x28, calls 0x5679DB0 on match |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| (none new) | | |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0x5679DB0 | unknown (array callback) | call | [V] (called 7x in this range) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [rbp+0x1028] | 8 | R | 0xbcad777 | loaded → rbx (parameter struct) |
| [rbx+0x1C] | 1 | R | 0xbcad77e | byte → movsx eax |
| [rbx+0x14] | 1 | R | 0xbcad782 | byte → movsx ecx |
| [rbx+0x18] | 4 | R | 0xbcad78a | float → xmm1 |
| [rbx+0x20] | 8 | R | 0xbcad883 | double → xmm2 → [rbp+0xA80] |
| [rbx+0x28] | 4 | R | 0xbcad86d | float → xmm0 |
| [rbx+0x2C] | 8 | R | 0xbcad945 | double → xmm2 → [rbp+0xA80] |
| [rbx+0x34] | 4 | R | 0xbcad934 | float → xmm0 |
| [rbx+0x38] | 8 | R | 0xbcad9e2 | double → xmm2 → [rbp+0xA80] |
| [rbx+0x40] | 4 | R | 0xbcad9f1 | float → xmm0 |
| [rbx+0x44] | 1 | R | 0xbcad869 | byte (mask) |
| [rbx+0x45] | 1 | R | 0xbcad85a | byte → dil |
| [rbx+0x46] | 1 | R | 0xbcad85e | byte → r15b |
| [rbx+0x4C] | 8 | R | 0xbcadad7 | double → xmm2 → [rbp+0xA80] |
| [rbx+0x54] | 4 | R | 0xbcadac6 | float → xmm0 |
| [rbx+0x58] | 8 | R | 0xbcadb95 | double → xmm2 → [rbp+0xA80] |
| [rbx+0x60] | 4 | R | 0xbcadb84 | float → xmm0 |
| [rbx+0x64] | 8 | R | 0xbcadc52 | double → xmm2 → [rbp+0xA80] |
| [rbx+0x6C] | 4 | R | 0xbcadc41 | float → xmm0 |
| [rbx+0x70] | 1 | R | 0xbcadac2 | byte (mask) |
| [rbx+0x71] | 1 | R | 0xbcadab3 | byte → dil |
| [rbx+0x72] | 1 | R | 0xbcadab7 | byte → r15b |
| [rbx+0xF4] | 1 | R | 0xbcad84d | byte → r14b |
| [rbx+0xF5] | 1 | R | 0xbcada9b | byte → r14b |
| [rbx+0x0] | 1 | R | 0xbcad83f | byte → sil |
| [rbx+0x8] | 1 | R | 0xbcad842 | byte → r13b |
| [rbx+0x9] | 1 | R | 0xbcad848 | byte → r12b |
| [rbp+0xF50] | 8 | R | 0xbcad82b, 0xbcad90b, 0xbcad9cb, 0xbcada8b, 0xbcadb5b, 0xbcadcdb | array base (saved r14+8) |
| [rbp+0x1018] | 8 | R | 0xbcad917, 0xbcad9d7, 0xbcada97, 0xbcadb67, 0xbcadc27 | reload r14 |
| [r14+0x38] | 8 | R | multiple | array base (reloaded each search) |
| [r14+0x42] | 2 | R | multiple | array count (word) |
| [0x12AE22C0] | 8 | R | 0xbcad7dc | array search target 7 |
| [0x12AE22D0] | 8 | R | 0xbcad8bc | array search target 8 |
| [0x12AE22E0] | 8 | R | 0xbcad983 | array search target 9 |
| [0x12AE22F0] | 8 | R | 0xbcada39 | array search target 10 |
| [0x12AE2300] | 8 | R | 0xbcadb15 | array search target 11 |
| [0x12AE2310] | 8 | R | 0xbcadb89 | array search target 12 |
| [0x12AE2320] | 8 | R | 0xbcadc89 | array search target 13 |
| [0x12AE22F8] | 4 | R | 0xbcad54c | TLS guard global 17 |
| [0x12AE2308] | 4 | R | 0xbcad571 | TLS guard global 18 |
| [0x12AE2318] | 4 | R | 0xbcad596 | TLS guard global 19 |
| [0x12AE2328] | 4 | R | 0xbcad5bb | TLS guard global 20 |
| [0x12AE2338] | 4 | R | 0xbcad5e0 | TLS guard global 21 |
| [0x12AE2348] | 4 | R | 0xbcad605 | TLS guard global 22 |
| [0x12AE2358] | 4 | R | 0xbcad62a | TLS guard global 23 |
| [0x12AE2368] | 4 | R | 0xbcad64f | TLS guard global 24 |
| [0x12AE2378] | 4 | R | 0xbcad674 | TLS guard global 25 |
| [0x12AE2388] | 4 | R | 0xbcad699 | TLS guard global 26 |
| [0x12AE2398] | 4 | R | 0xbcad6be | TLS guard global 27 |
| [0x12AE23A8] | 4 | R | 0xbcad6e3 | TLS guard global 28 |
| [0x12AE23B8] | 4 | R | 0xbcad708 | TLS guard global 29 |
| [0x12AE23C8] | 4 | R | 0xbcad72d | TLS guard global 30 |
| [0x12AE23D8] | 4 | R | 0xbcad752 | TLS guard global 31 |

## RANGE 3: 0xbcadce2..0xbcae437 (lines 801-1200)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcadce2..0xbcaddc2 | Fourteenth array search: calls 0x5679DB0 (from previous match), reloads r14, computes r14b=[rbx+0xF6], dil=[rbx+0x99], r15b=[rbx+0x9A], r8b=r14b&sil&[rbx+0x98]; loads [rbx+0x7C]→xmm0, cvtsi2ss r8d→xmm1, [rbx+0x74]→xmm2(sd); stores xmm2→[rbp+0xA80], xmm0→[rbp+0xA88], xmm1→[rbp+0xA8C]; fifteenth array search for global 0x12AE2330 at offset 0x28, calls 0x5679DB0 on match |
| 0xbcae04b..0xbcae102 | Sixteenth array search prep: r14b=[rbx+0xF7], dil=[rbx+0xC1], r15b=[rbx+0xC2], r8b=r14b&sil&[rbx+0xC0]; loads [rbx+0xA4]→xmm0, cvtsi2ss r8d→xmm1, [rbx+0x9C]→xmm2(sd); stores to [rbp+0xA80/0xA88/0xA8C]; seventeenth array search for global 0x12AE2360, calls 0x5679DB0 |
| 0xbcae11b..0xbcae1c2 | Eighteenth array search prep: r14b=[rbx+0xF8], dil=[rbx+0xE9], r15b=[rbx+0xEA]; sil&=r14b&[rbx+0xE8]; loads [rbx+0xCC]→xmm0, cvtsi2ss sil→xmm1, [rbx+0xC4]→xmm2(sd); stores to output; nineteenth array search for global 0x12AE2390, calls 0x5679DB0 |
| 0xbcae2bb..0xbcae372 | Twentieth array search prep: r13b&=r14b&dil; loads [rbx+0xD8]→xmm0, cvtsi2ss r13b→xmm1, [rbx+0xD0]→xmm2(sd); stores to output; twenty-first array search for global 0x12AE23A0, calls 0x5679DB0 |
| 0xbcae385..0xbcae432 | Twenty-second array search prep: r14b&=r12b&r15b; loads [rbx+0xE4]→xmm0, cvtsi2ss r14b→xmm1, [rbx+0xDC]→xmm2(sd); stores to output; twenty-third array search for global 0x12AE23B0, calls 0x5679DB0 |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| (none new) | | |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0x5679DB0 | unknown (array callback) | call | [V] (called 6x in this range) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [rbx+0x74] | 8 | R | 0xbcadd30 | double → xmm2 → [rbp+0xA80] |
| [rbx+0x7C] | 4 | R | 0xbcadd1f | float → xmm0 |
| [rbx+0x80] | 8 | R | 0xbcade00 | double → xmm2 → [rbp+0xA80] |
| [rbx+0x88] | 4 | R | 0xbcaddec | float → xmm0 |
| [rbx+0x8C] | 8 | R | 0xbcadecd | double → xmm2 → [rbp+0xA80] |
| [rbx+0x94] | 4 | R | 0xbcadeb1 | float → xmm0 |
| [rbx+0x98] | 1 | R | 0xbcadd18 | byte (mask) |
| [rbx+0x99] | 1 | R | 0xbcadd03 | byte → dil |
| [rbx+0x9A] | 1 | R | 0xbcadd0a | byte → r15b |
| [rbx+0x9C] | 8 | R | 0xbcadfab | double → xmm2 → [rbp+0xA80] |
| [rbx+0xA4] | 4 | R | 0xbcadf8f | float → xmm0 |
| [rbx+0xA8] | 8 | R | 0xbcae068 | double → xmm2 → [rbp+0xA80] |
| [rbx+0xB0] | 4 | R | 0xbcae054 | float → xmm0 |
| [rbx+0xB4] | 8 | R | 0xbcae135 | double → xmm2 → [rbp+0xA80] |
| [rbx+0xBC] | 4 | R | 0xbcae121 | float → xmm0 |
| [rbx+0xC0] | 1 | R | 0xbcadf88 | byte (mask) |
| [rbx+0xC1] | 1 | R | 0xbcadf73 | byte → dil |
| [rbx+0xC2] | 1 | R | 0xbcadf7a | byte → r15b |
| [rbx+0xC4] | 8 | R | 0xbcae210 | double → xmm2 → [rbp+0xA80] |
| [rbx+0xCC] | 4 | R | 0xbcae1fc | float → xmm0 |
| [rbx+0xD0] | 8 | R | 0xbcae2d5 | double → xmm2 → [rbp+0xA80] |
| [rbx+0xD8] | 4 | R | 0xbcae2c1 | float → xmm0 |
| [rbx+0xDC] | 8 | R | 0xbcae39f | double → xmm2 → [rbp+0xA80] |
| [rbx+0xE4] | 4 | R | 0xbcae38b | float → xmm0 |
| [rbx+0xE8] | 1 | R | 0xbcae1f5 | byte (mask) |
| [rbx+0xE9] | 1 | R | 0xbcae1e3 | byte → dil |
| [rbx+0xEA] | 1 | R | 0xbcae1ea | byte → r15b |
| [rbx+0xF6] | 1 | R | 0xbcadcfb | byte → r14b |
| [rbx+0xF7] | 1 | R | 0xbcadf6b | byte → r14b |
| [rbx+0xF8] | 1 | R | 0xbcae1db | byte → r14b |
| [0x12AE2330] | 8 | R | 0xbcadd6e | array search target 14 |
| [0x12AE2340] | 8 | R | 0xbcade39 | array search target 15 |
| [0x12AE2350] | 8 | R | 0xbcadf06 | array search target 16 |
| [0x12AE2360] | 8 | R | 0xbcae005 | array search target 17 |
| [0x12AE2370] | 8 | R | 0xbcae0a9 | array search target 18 |
| [0x12AE2380] | 8 | R | 0xbcae16f | array search target 19 |
| [0x12AE2390] | 8 | R | 0xbcae251 | array search target 20 |
| [0x12AE23A0] | 8 | R | 0xbcae31d | array search target 21 |
| [0x12AE23B0] | 8 | R | 0xbcae3e0 | array search target 22 |

## RANGE 4: 0xbcae43b..0xbcaecb2 (lines 1201-1600)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcae43b..0xbcae4e6 | Twenty-fourth array search prep: loads [rbx+0xEC]→xmm0, [rbx+4]→xmm1, [rbx+0xC]→xmm2, [rbx+0x48]→xmm3; stores xmm3,xmm1,xmm2,xmm0 to [rbp+0xA80..0xA8C]; sets [rbp+0x310]=1, [rbp+0x318]=rsi; twenty-fourth array search for global 0x12AE23C0 at offset 0x28, calls 0x5679DB0 on match |
| 0xbcae4f9..0xbcae58e | Twenty-fifth array search prep: movsx byte [rbx+0xF9]→r8d, cvtsi2ss→xmm0, stores xmm0,0,0 to [rbp+0xA80..0xA8C]; twenty-fifth array search for global 0x12AE23D0 at offset 0x28 (different loop pattern: uses rcx=global, r9=rdx, r8=rax), calls 0x5679DB0 on match |
| 0xbcae593..0xbcae5df | Checks [rdi+8]==2 (where rdi=[rbp+0x1040]); if not equal jumps to 0xBCAE7DA; loads global 0x12AE22B0→rsi; if null jumps to 0xBCAE5DF; TLS guard check for global 0x129C13C0 (jump to 0xBCB04E3); lock inc word [rsi+0x10]; tests byte [rsi+0x12]&1, jne to 0xBCAE701 |
| 0xbcae5df..0xbcae6cf | Loads floats from rdi+0x28/0x2C/0x30→xmm8/xmm7/xmm6; zeroes [rbp+0xEE0], [rbp+0xEF0]; computes r12-[rdi+0x10] (pointer diff), sar 3 (div 8 = count); if zero jumps to 0xBCAE6CF; checks count < 0x200 |
| 0xbcae634..0xbcae6cf | Allocates buffer: if count>=0x200 uses aligned alloc via [0xF99FFA0] (with +0x27 align 32), else direct alloc; stores buffer ptr to [rbp+0xEE0/EE8/EF0]; copies data from [rdi+0x10] via 0xEEC6DE0 (memcpy) |
| 0xbcae6cf..0xbcae7d5 | Sets up stack args: xmm8/xmm6/xmm7 to [rsp+0x30/0x28/0x20]; lea rdx=[0x12AE22B0], r8=[rbp+0xEE0], rcx=[rbp+0xF38], r9w=0x100; calls 0xE86CED0; TLS guard for 0x12AE24B8 (jump 0xBCB0466) |
| 0xbcae726..0xbcae7d5 | Array search on r13+0x48 (count from [r13+0x52]*0x30), target global 0x12AE24B0 at offset 0x28; on match computes index via imul 0xFFFFAAAB (div 16), stores to [rbp+0x310/0x312/0xA80..0xA8C]; calls 0xBCABA00 with rcx=r13, rdx=[rbp+0x310], r8=[0x12AE22B0], r9=[rbp+0xA80], [rsp+0x20]=0 |
| 0xbcae7da..0xbcae87b | Epilogue-like: reloads r14=[rbp+0x1048], rdi=[rbp+0x1040], rax=[rbp+0x1010]; movsd [rax]→xmm0→[rbp+0xA80]; sets [rbp+0x310]=1, [rbp+0x318]=rax; twenty-sixth array search on r13+0x38 for global 0x12AE23E0 at offset 0x28, calls 0x5679DB0 |
| 0xbcae880..0xbcae90e | Initializes locals: zeros [rbp+0xA22], [rbp+0xA28]; loads [rbp+0xF30]→rax→[rax]→rsi; loads globals 0x12AE2450→r12, 0x12AE2400→rbx, 0x128C1A58→r15d; r12=[r12+0x18]; [0x12AE2430]→[rbp+0xA78]; [rdi+0x18]→[rbp+0xF38]; [0x12AE23F0]→[rbp+0xF30]; zeros [rbp+0xF18]; allocates via [0xF99FFA0] (size 0x20), stores to [rbp+0xF10], sets [rbp+0xF20]=0x15, [rbp+0xF28]=0x1F |
| 0xbcae92b..0xbcaea7b | Initializes large struct at [rbp+0x9E0..0x7FD]: writes constant 0x16D95E79CDB26A8F to [rbp+0x9E0]; fills multiple 0x3F800000 (1.0f) patterns at offsets 0x948,0x95C,0x970,0x984,0x684,0x698,0x6AC,0x700,0x714,0x72C,0x740,0x754,0x76C,0x780,0x794; zeroes xmm6 regions; loads 0xEFD3400→xmm1→[rbp+0x6C0]; stores rsi to [rbp+0x704/0x70C]; 0x3F80000000000001 to [rbp+0x714]; sets bytes at 0x7AC=7, 0x7B6=2, 0x7DC=8, 0x7EC=8; copies from [rbp+0xA1F] to [rbp+0x7ED], [rbp+0xA2F] to [rbp+0x7FD], 0xFF to [rbp+0x7FE] |
| 0xbcaea8c..0xbcaec93 | Sets up call to 0x56B8630: rsi=[rbp+0xA60]; [rsi]→[rbp+0x310], xmm0→[rbp+0x318], 0→[rbp+0x328]; computes count from [rsi+0x10]-[rsi+8] sar 3 * 0xCCCCCCCCCCCCCCCD; sets [rbp+0xF4E]=1; calls 0x56B8630; then jump table dispatch on [rsi+0x38] (0-3) via [0xF44B7F0]: case 0: [rcx]→[rbp+0x338]; case 1: movups [rcx]→[rdx]; case 2: zero [rdx]; case 3: [rcx]→[rbp+0x338], lock inc [rdx+8] if [rsi+0x30]!=0; stores [rsi+0x50]→[rbp+0x360], [rsi+0x40]→[rbp+0x350] |
| 0xbcaec73..0xbcaecb2 | Final: [r13]→[rbp+0xA80]; calls 0xE869FF0 with rcx=[rbp+0xA88], rdx=[rbp+0xF50]; [r13+0x80]→[rbp+0xB00], zeros [r13+0x80]; clears [rbp+0xF4F]=0 |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| 0xF5C5E67 | [UNVERIFIED: 0xF5C5E67 16-byte constant] | 0xbcae92b (movups xmm0,[0xF5C5E67]) |
| 0xF547EEF | [UNVERIFIED: 0xF547EEF string/pointer] | 0xbcae96a (lea r9,[0xF547EEF]) |
| 0xF44B7F0 | [UNVERIFIED: 0xF44B7F0 jump table] | 0xbcaec0c (lea r8,[0xF44B7F0]) |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0x5679DB0 | unknown (array callback) | call | [V] (called 3x in this range) |
| 0xF99FFA0 | allocator (indirect) | call | [V] (called 2x) |
| 0xEEC6DE0 | memcpy | call | [V] |
| 0xE86CED0 | unknown | call | [V] |
| 0xBCABA00 | unknown | call | [V] |
| 0x56B8630 | unknown | call | [V] |
| 0xE869FF0 | unknown | call | [V] |
| 0x9D6D0 | unknown (string init?) | call | [V] |
| 0x6760450 | unknown | call | [V] |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [rbx+0xEC] | 4 | R | 0xbcae445 | float → xmm0 → [rbp+0xA8C] |
| [rbx+0x4] | 4 | R | 0xbcae44d | float → xmm1 → [rbp+0xA84] |
| [rbx+0xC] | 4 | R | 0xbcae452 | float → xmm2 → [rbp+0xA88] |
| [rbx+0x48] | 4 | R | 0xbcae457 | float → xmm3 → [rbp+0xA80] |
| [rbx+0xF9] | 1 | R | 0xbcae4f3 | byte → movsx r8d → xmm0 |
| [rdi+0x8] | 4 | R | 0xbcae593 | dword compare ==2 |
| [rdi+0x10] | 8 | R | 0xbcae608, 0xbcae6a8 | pointer base |
| [rdi+0x18] | 8 | R | 0xbcae604, 0xbcae6ac, 0xbcae8cc | pointer end |
| [rdi+0x28] | 4 | R | 0xbcae5e4 | float → xmm8 |
| [rdi+0x2C] | 4 | R | 0xbcae5ef | float → xmm7 |
| [rdi+0x30] | 4 | R | 0xbcae5df | float → xmm6 |
| [rdi+0x38] | 1 | R | 0xbcaebf5 | byte (jump table index 0-3) |
| [rsi+0x10] | 8 | R | 0xbcae5ce, 0xbcaebb1 | lock inc word, pointer end |
| [rsi+0x12] | 1 | R | 0xbcae5d7 | byte test &1 |
| [rsi+0x20] | 8 | R | 0xbcaebdf | → [rbp+0x330] |
| [rsi+0x28] | 8 | R | 0xbcaec02, 0xbcaec17, 0xbcaec23, 0xbcaec42 | case dispatch source |
| [rsi+0x30] | 8 | R | 0xbcaec35, 0xbcaec3a, 0xbcaec3e | refcount pointer |
| [rsi+0x38] | 1 | R | 0xbcaebf5 | jump table index |
| [rsi+0x40] | 16 | R | 0xbcaec68 | movups → [rbp+0x350] |
| [rsi+0x50] | 8 | R | 0xbcaec5d | → [rbp+0x360] |
| [rbp+0x1040] | 8 | R | 0xbcae7e1 | → rdi |
| [rbp+0x1048] | 8 | R | 0xbcae7da | → r14 |
| [rbp+0x1010] | 8 | R | 0xbcae7e8 | → rax (double source) |
| [rbp+0xF30] | 8 | R | 0xbcae896, 0xbcae8da | loaded/stored |
| [rbp+0xF38] | 8 | R | 0xbcae6f0, 0xbcae8cc | loaded/stored |
| [rbp+0xF50] | 8 | R | 0xbcae87b, 0xbcaec93 | array base |
| [rbp+0x1018] | 8 | R | 0xbcae6c8, 0xbcae7d5 | → r13 |
| [r13+0x38] | 8 | R | 0xbcae813 | array base (search 26) |
| [r13+0x42] | 2 | R | 0xbcae817 | array count |
| [r13+0x48] | 8 | R | 0xbcae72d | array base (search 0x12AE24B0) |
| [r13+0x52] | 2 | R | 0xbcae731 | array count (*0x30) |
| [r13+0x80] | 8 | R/W | 0xbcaec99, 0xbcaeca7 | read → [rbp+0xB00], write 0 |
| [r13] | 8 | R | 0xbcaec73 | → [rbp+0xA80] |
| [0x12AE22B0] | 8 | R | 0xbcae59d, 0xbcae6e2, 0xbcae7c4 | global pointer (refcounted) |
| [0x12AE23C0] | 8 | R | 0xbcae496 | array search target 24 |
| [0x12AE23D0] | 8 | R | 0xbcae540 | array search target 25 |
| [0x12AE23E0] | 8 | R | 0xbcae82a | array search target 26 |
| [0x12AE24B0] | 8 | R | 0xbcae748 | array search target (stride 0x30) |
| [0x12AE2450] | 8 | R | 0xbcae8a0 | global → r12 → [r12+0x18] |
| [0x12AE2400] | 8 | R | 0xbcae8a7 | global → rbx |
| [0x12AE2430] | 8 | R | 0xbcae8ba | global → [rbp+0xA78] |
| [0x12AE23F0] | 8 | R | 0xbcae8d3 | global → [rbp+0xF30] |
| [0x128C1A58] | 2 | R | 0xbcae8ae | word → r15d |
| [0x128C1A60] | 2 | R | 0xbcae726 | word → eax |
| [0x129C13C0] | 4 | R | 0xbcae5a1 | TLS guard global |
| [0x12AE24B8] | 4 | R | 0xbcae701 | TLS guard global |
| [0x1233E1A8] | 8 | R | 0xbcae63a, 0xbcae66d, 0xbcae8ec | allocator vtable |
| [0xF99FFA0] | 8 | R | 0xbcae64a, 0xbcae67e, 0xbcae8fa | allocator function (indirect) |
| [0xEFD3400] | 8 | R | 0xbcaea2a | double constant |
| [0xF5C5E67] | 16 | R | 0xbcae92b | 16-byte constant |
| [0xF547EEF] | - | R | 0xbcae96a | lea r9 (string?) |
| [0xF44B7F0] | - | R | 0xbcaec0c | jump table base |
| [0x12AE22B0] | 8 | R | multiple | refcounted object |
| gs:[0x58] | 8 | R | 0xbcae5be, 0xbcae716 | TLS base |
| [0x128767C8] | 4 | R | multiple | TLS index |

## RANGE 5: 0xbcaecb9..0xbcaf4d4 (lines 1601-2000)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcaecb9..0xbcaece7 | Sets up stack args: [rsp+0x28]=rdi, [rsp+0x20]=[rbp+0x9E8]; calls 0xBC039A0 with rcx=rbp, rdx=[rbp+0xA80], r8=[rbp+0x310], r9=[rbp+0x684] |
| 0xbcaece8..0xbcaed28 | Refcount cleanup: if [rbp+0x348]==3 and [rbp+0x340]!=0, lock dec [rsi+8], if zero calls vtable[0] and vtable[1] via [0xF99FFA0] (double free) |
| 0xbcaed28..0xbcaed85 | Iterates array at [rbp+0x318] to [rbp+0x320] step 0x28; for each entry where byte [rdi+0x18]==2, refcount dec [rsi+8], if zero calls vtable[0] and vtable[1] |
| 0xbcaed85..0xbcaedb4 | Checks [rbp+0xE0]==0 (bad instr at 0xbcaded8d); compares [rbp+0xF28] vs 0x10; selects rcx=[rbp+0xF10] or lea [rbp+0xF10]; stores to [rbp+0x9A0/0x9A8] |
| 0xbcaedc9..0xbcaee4a | Calls 0x568AD40 with rcx=[rbp+0x840], rdx=[rbp+0x9A0]; calls 0xBC04BB0 with rcx=[rbp+0x310], rdx=[rbp+0x840], r8=rbp; sets [rbp+0x800]=[0xF44B7C0], [rbp+0x838]=&[rbp+0x800] |
| 0xbcaee4b..0xbcaef77 | Initializes large struct at [rbp+0x890..0x940]: stores r12,rbx,r14,r15,r8,r9,r10,r11 and various zeros/lengths; loads [rdx+0x10]→[rbp+0x940], [rdx]→xmm0→[rbp+0x930]; [rbp+0xA40]→xmm0→[rbp+0x870/0x9C0] |
| 0xbcaef7e..0xbcaefe8 | Calls 0xBC054A0 with rcx=rsi=[rbp+0xA80], rdx=[rbp+0x310]; copies [rbp+0x890-0x28]→[rbp+0xDF8/E08] (xmm0/xmm1); zeroes [rbp+0x878], sets [rbp+0x880]=0xF, [rbp+0x868]=0, [rbp+0xDF0]=rdi |
| 0xbcaeff9..0xbcaf109 | Copies from [rax] (source struct) to [rbp+0xE20..0xEC0] in 0x10 chunks: 0xE20/E30 from [rax], 0xE48/E58 from [rax+0x28], 0xE70/E80 from [rax+0x50], 0xE98/EA8 from [rax+0x78], 0xEC0 from [rax+0xA0]; allocates 0x3B8 bytes via [0xF99FFA0]→rbx=rdi |
| 0xbcaf10a..0xbcaf1e6 | Initializes allocated object: [rdi+8]=0x100000001, [rdi]=[0xF221610]; stores to [rbp+0xF50]; calls 0xBC04620 with rdi+0x10, r8=[rbp+0x990]; sets [rbp+0xF00]=rdi+0x10, [rbp+0xF08]=rdi |
| 0xbcaf1e7..0xbcaf2f7 | Appends to vector at rbx=[rbp+0xF40]: if [rbx+0x10]!= [rbx+0x18], stores rdi/rax to [rbx+0x10] and increments; else calls 0x2679A0 (reserve); refcount dec on [rbp+0xF08] if needed; calls 0x5693A80 four times with [rbp+0xEC0/E98/E70/E48/E20]; compares [rbx+8] vs [rbp+0xDF0]; string copy via 0x9D6D0/0xEEC6DE0 |
| 0xbcaf2f7..0xbcaf37b | Stores [rbp+0xDF0]→[rbx+8]; zeros [rbx+0x30], [rax+0x58] (rax=[rbp+0xF40]); calls 0xBC03CD0 on [rbp+0xA80]; string dealloc pattern for [rbp+0x880/0x9D0/0xA50]: if len>=0x10, checks capacity, calls 0xE935700 (free) |
| 0xbcaf37b..0xbcaf4d4 | Four string deallocs: [rbp+0x880], [rbp+0x9D0], [rbp+0xA50] via 0xE935700; calls 0xBC03CD0 on [rbp+0x310]; final string dealloc for [rbp+0x858]; checks [rbp+0x308]==1 |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| 0xF44B7C0 | [UNVERIFIED: 0xF44B7C0 vtable/interface] | 0xbcaedf4 (lea rax,[0xF44B7C0]) |
| 0xF221610 | [UNVERIFIED: 0xF221610 vtable/interface] | 0xbcaf139 (lea rax,[0xF221610]) |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0xBC039A0 | unknown | call | [V] |
| 0xF99FFA0 | allocator/deallocator (indirect) | call | [V] (called 6x) |
| 0x568AD40 | unknown | call | [V] |
| 0xBC04BB0 | unknown | call | [V] |
| 0x76A8A0 | unknown | call | [V] |
| 0xBC054A0 | unknown | call | [V] |
| 0xBC04620 | unknown | call | [V] |
| 0x2679A0 | vector reserve | call | [V] |
| 0x5693A80 | unknown (refcount?) | call | [V] (called 4x) |
| 0x9D6D0 | string copy/init | call | [V] |
| 0xEEC6DE0 | memcpy | call | [V] |
| 0xBC03CD0 | unknown (cleanup) | call | [V] (called 2x) |
| 0xE935700 | string free | call | [V] (called 4x) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [rbp+0x9E8] | - | R | 0xbcaecc5 | lea → [rsp+0x20] |
| [rbp+0xA80] | - | R | 0xbcaecd4 | lea → rdx (arg to 0xBC039A0) |
| [rbp+0x310] | - | R | 0xbcaecdb | lea → r8 (arg to 0xBC039A0/BC04BB0) |
| [rbp+0x684] | - | R | 0xbcaece2 | lea → r9 (arg to 0xBC039A0) |
| [rbp+0x348] | 1 | R | 0xbcaece8 | byte == 3 check |
| [rbp+0x340] | 8 | R | 0xbcaecf1 | refcounted pointer |
| [rsi+8] | 4 | R/W | 0xbcaecfd, 0xbcaed12 | lock dec refcount (outer/inner) |
| [rsi] | 8 | R | 0xbcaed03, 0xbcaed18 | vtable pointer |
| [rsi+0xC] | 4 | R/W | 0xbcaed16, 0xbcaed22 | lock dec secondary refcount |
| [rbp+0x318] | 8 | R | 0xbcaed27 | array base for cleanup loop |
| [rbp+0x320] | 8 | R | 0xbcaed34 | array end for cleanup loop |
| [rdi+0x18] | 1 | R | 0xbcaed49 | byte == 2 check |
| [rdi+8] | 8 | R | 0xbcaed4f | refcounted pointer |
| [rbp+0xE0] | 8 | R | 0xbcaed85 | compare == 0 |
| [rbp+0xF28] | 8 | R | 0xbcaed9a | compare vs 0x10 (SSO threshold) |
| [rbp+0xF10] | 8 | R | 0xbcaeda4, 0xbcaedad | string data pointer |
| [rbp+0xF20] | 8 | R | 0xbcaed93 | string length |
| [rbp+0x9A0] | 8 | W | 0xbcaedb4 | =rcx (string ptr) |
| [rbp+0x9A8] | 8 | W | 0xbcaedbb | =rax (string len) |
| [rbp+0x840] | - | R/W | 0xbcaedc9, 0xbcaede4 | buffer for 0x568AD40/BC04BB0 |
| [rbp+0x800] | 8 | W | 0xbcaedf4 | =0xF44B7C0 |
| [rbp+0x838] | 8 | W | 0xbcaee02, 0xbcaee2c | =&[rbp+0x800] then 0 |
| [rbp+0x678] | 8 | R | 0xbcaee09 | compare != 0 |
| [rbp+0x640] | 8 | W | 0xbcaee1e, 0xbcaee25 | =rax then =rcx |
| [rbp+0x1058] | 8 | R | 0xbcaee4b | → rdx |
| [rbp+0xA30] | 8 | R | 0xbcaee52 | → rdi |
| [rbp+0xA38] | 8 | R | 0xbcaee59 | → rcx |
| [rbp+0xA50] | 8 | R/W | 0xbcaee60, 0xbcaee67 | string: len=0xF, byte=0 |
| [rbp+0x9D8] | 8 | W | 0xbcaee79 | =0 |
| [rbp+0x9B8] | 8 | W | 0xbcaee8b, 0xbcaeea8 | =rdi then byte=0 |
| [rbp+0x9B0] | 8 | W | 0xbcaee92 | =rcx |
| [rbp+0x9C8] | 8 | W | 0xbcaee9d | =0 |
| [rbp+0x9D0] | 8 | W | 0xbcaeea8 | =0xF (SSO cap) |
| [rbp+0x890] | 8 | W | 0xbcaeeb2 | =r12 |
| [rbp+0x898] | 2 | W | 0xbcaeebf | =0 |
| [rbp+0x89C] | 4 | W | 0xbcaeec9 | =0 |
| [rbp+0x8A0] | 1 | W | 0xbcaeed0 | =0 |
| [rbp+0x8A8] | 8 | W | 0xbcaeede | =[rbp+0xA70] |
| [rbp+0x8B2] | 1 | W | 0xbcaeee5 | =0 |
| [rbp+0x8B8] | 8 | W | 0xbcaeeec | =rbx |
| [rbp+0x8C0] | 2 | W | 0xbcaeef4 | =r15w |
| [rbp+0x8C4] | 4 | W | 0xbcaeefe | =0 |
| [rbp+0x8C8] | 1 | W | 0xbcaef05 | =0 |
| [rbp+0x8D0] | 8 | W | 0xbcaef0c | =r14 |
| [rbp+0x8DA] | 1 | W | 0xbcaef13 | =0 |
| [rbp+0x8E0] | 8 | W | 0xbcaef1a | =[rbp+0xA78] |
| [rbp+0x8E8] | 2 | W | 0xbcaef21 | =r15w |
| [rbp+0x8EC] | 4 | W | 0xbcaef29 | =0 |
| [rbp+0x8F0] | 1 | W | 0xbcaef33 | =0 |
| [rbp+0x8F8] | 8 | W | 0xbcaef3a | =[rbp+0xF38] |
| [rbp+0x902] | 1 | W | 0xbcaef48 | =0 |
| [rbp+0x908] | 8 | W | 0xbcaef4f | =[rbp+0xF30] |
| [rbp+0x910] | 2 | W | 0xbcaef5d | =0 |
| [rbp+0x914] | 4 | W | 0xbcaef66 | =0 |
| [rbp+0x918] | 1 | W | 0xbcaef70 | =0 |
| [rbp+0x920] | 8 | W | 0xbcaef77 | =[rbp+0xA68] |
| [rbp+0x92A] | 1 | W | 0xbcaef85 | =0 |
| [rbp+0x940] | 8 | W | 0xbcaef8c | =[rdx+0x10] |
| [rbp+0x930] | 16 | W | 0xbcaef9a | =xmm0 from [rdx] |
| [rbp+0x888] | 8 | W | 0xbcaefa1 | =0 |
| [rbp+0x868] | 8 | W | 0xbcaefac | =rcx |
| [rbp+0xA40] | 16 | R | 0xbcaefb3 | xmm0 source |
| [rbp+0x870] | 16 | W | 0xbcaefd3 | =xmm0 |
| [rbp+0x9C0] | 8 | W | 0xbcaefd3 | =rcx from [rbp+0xA40] |
| [rbp+0x880] | 8 | W | 0xbcaefe1 | =rax |
| [rbp+0x860] | 8 | W | 0xbcaefe8 | =rdi |
| [rbp+0xDF8] | 16 | W | 0xbcaf019 | =xmm0 from [rax-0x28] |
| [rbp+0xE08] | 16 | W | 0xbcaf020 | =xmm1 from [rax-0x18] |
| [rbp+0x878] | 8 | W | 0xbcaf032 | =0 |
| [rbp+0x880] | 8 | W | 0xbcaf037 | =0xF |
| [rbp+0x868] | 1 | W | 0xbcaf044 | =0 |
| [rbp+0xDF0] | 8 | W | 0xbcaf04b | =rdi |
| [rbp+0xE40] | 8 | W | 0xbcaf056 | =[rax+0x20] |
| [rbp+0xE30] | 16 | W | 0xbcaf05d | =xmm1 from [rax+0x10] |
| [rbp+0xE20] | 16 | W | 0xbcaf064 | =xmm0 from [rax] |
| [rbp+0xE68] | 8 | W | 0xbcaf06f | =[rax+0x48] |
| [rbp+0xE58] | 16 | W | 0xbcaf07e | =xmm1 from [rax+0x38] |
| [rbp+0xE48] | 16 | W | 0xbcaf085 | =xmm0 from [rax+0x28] |
| [rbp+0xE90] | 8 | W | 0xbcaf08c | =[rax+0x70] |
| [rbp+0xE80] | 16 | W | 0xbcaf09f | =xmm1 from [rax+0x60] |
| [rbp+0xE70] | 16 | W | 0xbcaf0a6 | =xmm0 from [rax+0x50] |
| [rbp+0xEB8] | 8 | W | 0xbcaf0b4 | =[rax+0x98] |
| [rbp+0xEA8] | 16 | W | 0xbcaf0c6 | =xmm1 from [rax+0x88] |
| [rbp+0xE98] | 16 | W | 0xbcaf0cd | =xmm0 from [rax+0x78] |
| [rbp+0xED0] | 8 | W | 0xbcaf0db | =[rax+0xB0] |
| [rbp+0xEC0] | 16 | W | 0xbcaf0e9 | =xmm0 from [rax+0xA0] |
| [rbp+0xF40] | 8 | R | 0xbcaf10a | → rbx (vector) |
| [rbp+0xF50] | 8 | W | 0xbcaf143 | =rdi (allocated obj) |
| [rbp+0xA90] | 8 | R | 0xbcaf14e | string data |
| [rbp+0xA98] | 8 | R | 0xbcaf155 | string cap |
| [rbp+0xA80] | 8 | R | 0xbcaf15f, 0xbcaf166 | string data (SSO) |
| [rbp+0x990] | 8 | W | 0xbcaf16d | =rsi |
| [rbp+0x998] | 8 | W | 0xbcaf174 | =rax |
| [rbp+0xF00] | 8 | W | 0xbcaf184 | =rdi |
| [rbp+0xF08] | 8 | W | 0xbcaf192 | =rax |
| [rbx+0x10] | 8 | R/W | 0xbcaf19d, 0xbcaf1a7, 0xbcaf1ae | vector end pointer |
| [rbx+0x18] | 8 | R | 0xbcaf19d | vector capacity |
| [rbx+0x28] | 8 | R | 0xbcaf2c0 | string capacity |
| [rbx+0x20] | 8 | W | 0xbcaf2e5 | =rsi (string size) |
| [rbx+8] | 8 | R/W | 0xbcaf235, 0xbcaf2fe | string data pointer |
| [rbx+0x30] | 8 | W | 0xbcaf30a | =0 |
| [rbx+0x58] | 8 | W | 0xbcaf1c6, 0xbcaf235, 0xbcaf311 | string data/len |
| [rbx+0x60] | 1 | W | 0xbcaf1be | =1 |
| [rax+0x58] | 8 | W | 0xbcaf311 | =0 (rax=[rbp+0xF40]) |
| [rbp+0xE10] | 8 | R | 0xbcaf251, 0xbcaf319 | string length |
| [rbp+0xDF8] | 8 | R | 0xbcaf253, 0xbcaf326 | string data |
| [rbp+0x880] | 8 | R | 0xbcaf38e | string cap for free |
| [rbp+0x868] | 8 | R | 0xbcaf394 | string data for free |
| [rbp+0x9D0] | 8 | R | 0xbcaf3cc | string cap for free |
| [rbp+0x9B8] | 8 | R | 0xbcaf3d9 | string data for free |
| [rbp+0xA50] | 8 | R | 0xbcaf411 | string cap for free |
| [rbp+0xA38] | 8 | R | 0xbcaf41e | string data for free |
| [rbp+0x858] | 8 | R | 0xbcaf48f | string cap for free |
| [rbp+0x840] | 8 | R | 0xbcaf495 | string data for free |
| [rbp+0x308] | 1 | R | 0xbcaf4cd | byte == 1 check |

## RANGE 6: 0xbcaf4d6..0xbcafc89 (lines 2001-2400)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcaf4d6..0xbcaf52b | String dealloc for [rbp+0x2C8]: if ptr!=0, len=end-start; if len>=0x1000 check alloc header (at -8), if header valid and size>=0x20 call 0xE935700 (free); else or len with 0x27, call 0xE935700; zeroes [rbp+0x2C8..0x2D8] |
| 0xbcaf52b..0xbcaf57c | Calls 0x56C9740(rcx=rbp); checks [rbp+0x988]==1; if so, string dealloc for [rbp+0x948] (same pattern: len check, header check, free via 0xE935700) |
| 0xbcaf57c..0xbcaf606 | String dealloc for [rbp+0xA00] (cap at [rbp+0xA00], data at [rbp+0x9E8]); string dealloc for [rbp+0xF28] (cap at [rbp+0xF28], data at [rbp+0xF10]); both use same free pattern via 0xE935700 |
| 0xbcaf606..0xbcaf637 | Epilogue: restores xmm6-xmm9 from [rbp+0xF60..0xF90]; add rsp,0x1028; pops rbx,rdi,rsi,r12,r13,r14,r15,rbp; ret |
| 0xbcaf638..0xbcaf651 | Error path 1 (from 0xBCAF638): calls 0x78ED0 (alloc?), mov ecx,0x20, rdi=rax, calls 0x9BC830 (init?), jmp to 0xBCAE90E (alloc retry) |
| 0xbcaf652..0xbcaf65c | Error path 2 (from 0xBCAF652): mov ecx,0x3B8, calls 0x9BC830, jmp to 0xBCAF11D (alloc retry) |
| 0xbcaf662..0xbcaf67a | Error path 3/4: call 0x9BC830 on r13/r12, zero r13d, jmp to 0xBCAE65C/0xBCAE690 |
| 0xbcaf67f..0xbcaf697 | Error path 5 (from 0xBCAF67F): calls crash handler [0xF9A8C78] with zeroed args; TLS init for 0x12AE23E8: lea rcx,[0x12AE23E8], call 0xE938CB0; if [0x12AE23E8]!=-1 jmp to 0xBCACE1B |
| 0xbcaf698..0xbcafc89 | **TLS lazy initialization block** (13 identical sequences for globals 0x12AE23E8..0x12AE22C8 step 0x10): each does: lea rcx,[global], call 0xE938CB0 (init); if global != -1 jmp to main function label; else lea rdx,[error_string], lea r14,[rbp+0xA80], call 0x79580 (format error); if [rbp+0xA98]<0x10 use SSO else heap ptr; test rdx, je to far error; FNV1a hash init (rcx=0xCBF29CE484222325) for error string processing |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| 0xF5DE7ED | [UNVERIFIED: 0xF5DE7ED error string for 0x12AE23E8] | 0xbcaf6b2 (lea rdx,[0xF5DE7ED]) |
| 0xF5C6CEB | [UNVERIFIED: 0xF5C6CEB error string for 0x12AE23F8] | 0xbcaf723 (lea rdx,[0xF5C6CEB]) |
| 0xF5E7C75 | [UNVERIFIED: 0xF5E7C75 error string for 0x12AE2408] | 0xbcaf795 (lea rdx,[0xF5E7C75]) |
| 0xF58CE54 | [UNVERIFIED: 0xF58CE54 error string for 0x12AE2418] | 0xbcaf807 (lea rdx,[0xF58CE54]) |
| 0xF531C11 | [UNVERIFIED: 0xF531C11 error string for 0x12AE2428] | 0xbcaf879 (lea rdx,[0xF531C11]) |
| 0xF5E7C36 | [UNVERIFIED: 0xF5E7C36 error string for 0x12AE2438] | 0xbcaf8eb (lea rdx,[0xF5E7C36]) |
| 0xF5C6CE2 | [UNVERIFIED: 0xF5C6CE2 error string for 0x12AE2448] | 0xbcaf95d (lea rdx,[0xF5C6CE2]) |
| 0xF563D27 | [UNVERIFIED: 0xF563D27 error string for 0x12AE2458] | 0xbcaf9cf (lea rdx,[0xF563D27]) |
| 0xF7E419B | [UNVERIFIED: 0xF7E419B error string for 0x12AE2468] | 0xbcafa41 (lea rdx,[0xF7E419B]) |
| 0xF5FA4B5 | [UNVERIFIED: 0xF5FA4B5 error string for 0x12AE2478] | 0xbcafab3 (lea rdx,[0xF5FA4B5]) |
| 0xF7E41AA | [UNVERIFIED: 0xF7E41AA error string for 0x12AE2488] | 0xbcafb25 (lea rdx,[0xF7E41AA]) |
| 0xF5A843D | [UNVERIFIED: 0xF5A843D error string for 0x12AE2498] | 0xbcafb97 (lea rdx,[0xF5A843D]) |
| 0xF550D6A | [UNVERIFIED: 0xF550D6A error string for 0x12AE24A8] | 0xbcafc09 (lea rdx,[0xF550D6A]) |
| 0xF550E1C | [UNVERIFIED: 0xF550E1C error string for 0x12AE22C8] | 0xbcafc7b (lea rdx,[0xF550E1C]) |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0xE935700 | string/vector free | call | [V] (called 5x) |
| 0x56C9740 | unknown (cleanup) | call | [V] |
| 0x78ED0 | allocator | call | [V] |
| 0x9BC830 | object init | call | [V] (called 4x) |
| 0xF9A8C78 | crash handler (indirect) | call | [V] |
| 0xE938CB0 | TLS init | call | [V] (called 13x) |
| 0x79580 | string format/error | call | [V] (called 13x) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [rbp+0x2C8] | 8 | R/W | 0xbcaf4d6, 0xbcaf515 | string data ptr (read, then zeroed) |
| [rbp+0x2D8] | 8 | R | 0xbcaf4e2 | string end ptr |
| [rbp+0x988] | 1 | R | 0xbcaf522 | byte flag == 1 |
| [rbp+0x948] | 8 | R | 0xbcaf53c | string data ptr |
| [rbp+0x958] | 8 | R | 0xbcaf548 | string end ptr |
| [rbp+0xA00] | 8 | R | 0xbcaf57c | string capacity |
| [rbp+0x9E8] | 8 | R | 0xbcaf589 | string data ptr |
| [rbp+0xF28] | 8 | R | 0xbcaf5c1 | string capacity |
| [rbp+0xF10] | 8 | R | 0xbcaf5ce | string data ptr |
| [rbp+0xF60] | 16 | R | 0xbcaf606 | restore xmm6 |
| [rbp+0xF70] | 16 | R | 0xbcaf60d | restore xmm7 |
| [rbp+0xF80] | 16 | R | 0xbcaf614 | restore xmm8 |
| [rbp+0xF90] | 16 | R | 0xbcaf61c | restore xmm9 |
| [0x12AE23E8] | 4 | R/W | 0xbcaf6a4, 0xbcaf6ab | TLS global (read -1 check, written by 0xE938CB0) |
| [0x12AE23F8] | 4 | R/W | 0xbcaf711, 0xbcaf716 | TLS global |
| [0x12AE2408] | 4 | R/W | 0xbcaf77c, 0xbcaf788 | TLS global |
| [0x12AE2418] | 4 | R/W | 0xbcaf7ee, 0xbcaf7fa | TLS global |
| [0x12AE2428] | 4 | R/W | 0xbcaf860, 0xbcaf86c | TLS global |
| [0x12AE2438] | 4 | R/W | 0xbcaf8d2, 0xbcaf8de | TLS global |
| [0x12AE2448] | 4 | R/W | 0xbcaf944, 0xbcaf950 | TLS global |
| [0x12AE2458] | 4 | R/W | 0xbcaf9b6, 0xbcaf9c2 | TLS global |
| [0x12AE2468] | 4 | R/W | 0xbcafa28, 0xbcafa34 | TLS global |
| [0x12AE2478] | 4 | R/W | 0xbcafa9a, 0xbcafaa6 | TLS global |
| [0x12AE2488] | 4 | R/W | 0xbcafb0c, 0xbcafb18 | TLS global |
| [0x12AE2498] | 4 | R/W | 0xbcafb7e, 0xbcafb8a | TLS global |
| [0x12AE24A8] | 4 | R/W | 0xbcafbf0, 0xbcafbfc | TLS global |
| [0x12AE22C8] | 4 | R/W | 0xbcafc62, 0xbcafc6e | TLS global |
| [rbp+0xA80] | 16 | R/W | 0xbcaf6bf, 0xbcaf731, etc | error format buffer (lea r14) |
| [rbp+0xA90] | 8 | R | 0xbcaf6c8, 0xbcaf73a, etc | error string data |
| [rbp+0xA98] | 8 | R | 0xbcaf6cf, 0xbcaf741, etc | error string capacity |
| [0xF5DE7ED] | - | R | 0xbcaf6b2 | error string literal |
| [0xF5C6CEB] | - | R | 0xbcaf723 | error string literal |
| [0xF5E7C75] | - | R | 0xbcaf795 | error string literal |
| [0xF58CE54] | - | R | 0xbcaf807 | error string literal |
| [0xF531C11] | - | R | 0xbcaf879 | error string literal |
| [0xF5E7C36] | - | R | 0xbcaf8eb | error string literal |
| [0xF5C6CE2] | - | R | 0xbcaf95d | error string literal |
| [0xF563D27] | - | R | 0xbcaf9cf | error string literal |
| [0xF7E419B] | - | R | 0xbcafa41 | error string literal |
| [0xF5FA4B5] | - | R | 0xbcafab3 | error string literal |
| [0xF7E41AA] | - | R | 0xbcafb25 | error string literal |
| [0xF5A843D] | - | R | 0xbcafb97 | error string literal |
| [0xF550D6A] | - | R | 0xbcafc09 | error string literal |
| [0xF550E1C] | - | R | 0xbcafc7b | error string literal |

## RANGE 7: 0xbcafc8c..0xbcb049d (lines 2401-2800)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcafc8c..0xbcb0461 | **Continued TLS lazy initialization block** (19 more identical sequences for globals 0x12AE22C8..0x12AE23D8 step 0x10, plus 0x12AE24B8): each does: lea rcx,[global], call 0xE938CB0 (init); if global != -1 jmp to main function label (0xBCAD502..0xBCAD777, 0xBCAE726); else lea rdx,[error_string], lea r12/rbx,[rbp+0xA80], call 0x79580 (format error); if [rbp+0xA98]<0x10 use SSO else heap ptr; test rdx, je to far error (0xBCB05E1..0xBCB06E0); FNV1a hash init (rcx=0xCBF29CE484222325) for error string processing, jmp to hash loop (0xBCB0FE0..0xBCB1C07) |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| 0xF54600B | [UNVERIFIED: 0xF54600B error string for 0x12AE22D8] | 0xbcafced (lea rdx,[0xF54600B]) |
| 0xF557C84 | [UNVERIFIED: 0xF557C84 error string for 0x12AE22E8] | 0xbcafd5f (lea rdx,[0xF557C84]) |
| 0xF5427FA | [UNVERIFIED: 0xF5427FA error string for 0x12AE22F8] | 0xbcafdd1 (lea rdx,[0xF5427FA]) |
| 0xF54604B | [UNVERIFIED: 0xF54604B error string for 0x12AE2308] | 0xbcafe43 (lea rdx,[0xF54604B]) |
| 0xF557CC0 | [UNVERIFIED: 0xF557CC0 error string for 0x12AE2318] | 0xbcafeb5 (lea rdx,[0xF557CC0]) |
| 0xF542834 | [UNVERIFIED: 0xF542834 error string for 0x12AE2328] | 0xbcaff27 (lea rdx,[0xF542834]) |
| 0xF54606E | [UNVERIFIED: 0xF54606E error string for 0x12AE2338] | 0xbcaff99 (lea rdx,[0xF54606E]) |
| 0xF557CE1 | [UNVERIFIED: 0xF557CE1 error string for 0x12AE2348] | 0xbcb000b (lea rdx,[0xF557CE1]) |
| 0xF542854 | [UNVERIFIED: 0xF542854 error string for 0x12AE2358] | 0xbcb007d (lea rdx,[0xF542854]) |
| 0xF54602C | [UNVERIFIED: 0xF54602C error string for 0x12AE2368] | 0xbcb00ef (lea rdx,[0xF54602C]) |
| 0xF557CA3 | [UNVERIFIED: 0xF557CA3 error string for 0x12AE2378] | 0xbcb0161 (lea rdx,[0xF557CA3]) |
| 0xF542818 | [UNVERIFIED: 0xF542818 error string for 0x12AE2388] | 0xbcb01d3 (lea rdx,[0xF542818]) |
| 0xF54608B | [UNVERIFIED: 0xF54608B error string for 0x12AE2398] | 0xbcb0245 (lea rdx,[0xF54608B]) |
| 0xF557CFC | [UNVERIFIED: 0xF557CFC error string for 0x12AE23A8] | 0xbcb02b7 (lea rdx,[0xF557CFC]) |
| 0xF54286E | [UNVERIFIED: 0xF54286E error string for 0x12AE23B8] | 0xbcb0329 (lea rdx,[0xF54286E]) |
| 0xF605A7B | [UNVERIFIED: 0xF605A7B error string for 0x12AE23C8] | 0xbcb039b (lea rdx,[0xF605A7B]) |
| 0xF7DA6CD | [UNVERIFIED: 0xF7DA6CD error string for 0x12AE23D8] | 0xbcb040d (lea rdx,[0xF7DA6CD]) |
| 0xF58CE4E | [UNVERIFIED: 0xF58CE4E error string for 0x12AE24B8] | 0xbcb047f (lea rdx,[0xF58CE4E]) |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0xE938CB0 | TLS init | call | [V] (called 19x) |
| 0x79580 | string format/error | call | [V] (called 19x) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [0x12AE22D8] | 4 | R/W | 0xbcafcdb, 0xbcafce0 | TLS global |
| [0x12AE22E8] | 4 | R/W | 0xbcafd4d, 0xbcafd52 | TLS global |
| [0x12AE22F8] | 4 | R/W | 0xbcafdb8, 0xbcafdc4 | TLS global |
| [0x12AE2308] | 4 | R/W | 0xbcafe2a, 0xbcafe36 | TLS global |
| [0x12AE2318] | 4 | R/W | 0xbcafe9c, 0xbcafea8 | TLS global |
| [0x12AE2328] | 4 | R/W | 0xbcaff0e, 0xbcaff1a | TLS global |
| [0x12AE2338] | 4 | R/W | 0xbcaff80, 0xbcaff8c | TLS global |
| [0x12AE2348] | 4 | R/W | 0xbcafff2, 0xbcafff9 | TLS global |
| [0x12AE2358] | 4 | R/W | 0xbcb0064, 0xbcb0070 | TLS global |
| [0x12AE2368] | 4 | R/W | 0xbcb00d6, 0xbcb00e2 | TLS global |
| [0x12AE2378] | 4 | R/W | 0xbcb0148, 0xbcb0154 | TLS global |
| [0x12AE2388] | 4 | R/W | 0xbcb01ba, 0xbcb01c6 | TLS global |
| [0x12AE2398] | 4 | R/W | 0xbcb022c, 0xbcb0238 | TLS global |
| [0x12AE23A8] | 4 | R/W | 0xbcb029e, 0xbcb02aa | TLS global |
| [0x12AE23B8] | 4 | R/W | 0xbcb0310, 0xbcb031c | TLS global |
| [0x12AE23C8] | 4 | R/W | 0xbcb0382, 0xbcb038e | TLS global |
| [0x12AE23D8] | 4 | R/W | 0xbcb03f4, 0xbcb0400 | TLS global |
| [0x12AE24B8] | 4 | R/W | 0xbcb0466, 0xbcb0472 | TLS global |
| [rbp+0xA80] | 16 | R/W | multiple (lea r12/rbx) | error format buffer |
| [rbp+0xA90] | 8 | R | multiple | error string data |
| [rbp+0xA98] | 8 | R | multiple | error string capacity (SSO check) |
| [0xF54600B] | - | R | 0xbcafced | error string literal |
| [0xF557C84] | - | R | 0xbcafd5f | error string literal |
| [0xF5427FA] | - | R | 0xbcafdd1 | error string literal |
| [0xF54604B] | - | R | 0xbcafe43 | error string literal |
| [0xF557CC0] | - | R | 0xbcafeb5 | error string literal |
| [0xF542834] | - | R | 0xbcaff27 | error string literal |
| [0xF54606E] | - | R | 0xbcaff99 | error string literal |
| [0xF557CE1] | - | R | 0xbcb000b | error string literal |
| [0xF542854] | - | R | 0xbcb007d | error string literal |
| [0xF54602C] | - | R | 0xbcb00ef | error string literal |
| [0xF557CA3] | - | R | 0xbcb0161 | error string literal |
| [0xF542818] | - | R | 0xbcb01d3 | error string literal |
| [0xF54608B] | - | R | 0xbcb0245 | error string literal |
| [0xF557CFC] | - | R | 0xbcb02b7 | error string literal |
| [0xF54286E] | - | R | 0xbcb0329 | error string literal |
| [0xF605A7B] | - | R | 0xbcb039b | error string literal |
| [0xF7DA6CD] | - | R | 0xbcb040d | error string literal |
| [0xF58CE4E] | - | R | 0xbcb047f | error string literal |

## RANGE 8: 0xbcb04a5..0xbcb0c71 (lines 2801-3200)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcb04a5..0xbcb04d1 | Final TLS init for 0x12AE24B8: error string format, FNV1a hash (rcx=0x100000001B3, prime=0xCBF29CE484222325), processes 4 bytes at a time, then remainder; stores hash to [0x12AE24B0], calls 0x73150, marks TLS init done via 0xE938D70, jmp to 0xBCAE726 |
| 0xbcb04e3..0xbcb0514 | TLS init for 0x129C13C0 (from 0xBCB04E3): calls 0xE938CB0; if != -1 jmp to 0xBCAE5CE; else calls 0xE935740 (logging?), 0xE938D70 (mark init), jmp to 0xBCAE5CE |
| 0xbcb0519..0xbcb0514 | Error hash jump targets: 32 identical FNV1a hash loops (0xBCB070A..0xBCB1C30) for each TLS global; each loads error string from [rbp+0xA80] (r14), computes FNV1a hash, stores to corresponding global slot ([0x12AE23E0]..[0x12AE2450]), calls 0x73150, marks TLS init via 0xE938D70, jmps back to main function |
| 0xbcb06ef..0xbcb0c71 | **FNV1a hash computation loops** (13 shown here for globals 0x12AE23E0..0x12AE2450): each does: rdx &= ~3; rcx=FNV_offset_basis; r9=FNV_prime; processes 4 bytes at a time (xor+imul); handles remainder bytes; stores final hash to target global ([0x12AE23E0]..[0x12AE2450]); calls 0x73150 (cleanup?); calls 0xE938D70 (mark TLS init complete); jmps to main function label |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| 0x4E05030 | [UNVERIFIED: 0x4E05030 log/error string] | 0xbcb04fc (lea rcx,[0x4E05030]) |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0xE938CB0 | TLS init | call | [V] |
| 0xE935740 | logging/error | call | [V] |
| 0xE938D70 | TLS init complete | call | [V] (called 14x) |
| 0x75B60 | unknown (error path) | call | [V] |
| 0x73150 | string cleanup | call | [V] (called 13x) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [0x129C13C0] | 4 | R/W | 0xbcb04ef, 0xbcb04f6 | TLS global |
| [0x12AE24B0] | 8 | W | 0xbcb0777 | FNV1a hash result for 0x12AE24B8 |
| [0x12AE23E0] | 8 | W | 0xbcb0777 | FNV1a hash result for 0x12AE23E8 |
| [0x12AE23F0] | 8 | W | 0xbcb081d | FNV1a hash result for 0x12AE23F8 |
| [0x12AE2400] | 8 | W | 0xbcb08c6 | FNV1a hash result for 0x12AE2408 |
| [0x12AE2410] | 8 | W | 0xbcb096f | FNV1a hash result for 0x12AE2418 |
| [0x12AE2420] | 8 | W | 0xbcb0a18 | FNV1a hash result for 0x12AE2428 |
| [0x12AE2430] | 8 | W | 0xbcb0ac1 | FNV1a hash result for 0x12AE2438 |
| [0x12AE2440] | 8 | W | 0xbcb0b6a | FNV1a hash result for 0x12AE2448 |
| [0x12AE2450] | 8 | W | 0xbcb0c13 | FNV1a hash result for 0x12AE2458 |
| [rbp+0xA80] | 16 | R | 0xbcb070a, 0xbcb07b3, etc | error string buffer (r14) |
| [rbp+0xA90] | 8 | R | 0xbcb049d | error string data (r8) |
| [rbp+0xA98] | 8 | R | 0xbcb04a5 | error string capacity |
| [0x4E05030] | - | R | 0xbcb04fc | log/error string literal |

## RANGE 9: 0xbcb0c74..0xbcb136c (lines 3201-3600)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcb0c74..0xbcb1028 | **Continued FNV1a hash loops** for TLS globals 0x12AE2460, 0x12AE2470, 0x12AE2480, 0x12AE2490, 0x12AE24A0 (using r14 as string ptr): each computes hash, stores to target global, calls 0x73150, calls 0xE938D70, jmps to main function label (0xBCACF43..0xBCACFD7) |
| 0xbcb0d89..0xbcb0d95 | Corrupted/disassembly error region at 0xbcb0d8d (bad instruction: `mov ecx,0x84222325` / `in al,0x9C` / `ret far`) - likely data or jump table padding |
| 0xbcb103b..0xbcb136c | **FNV1a hash loops for TLS globals 0x12AE22C0..0x12AE2300** (using r12 as string ptr, loaded from [rbp+0x1018] at 0xbcb102f/10df/10ed/119d/11a4/125b/130b): each computes hash, stores to target global ([0x12AE22C0]..[0x12AE2300]), calls 0x73150, calls 0xE938D70, sets r14=[rbp+0x1018], rdi=[rbp+0xA80], jmps to main function (0xBCAD502..0xBCAD596) |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| (none new) | | |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0x73150 | string cleanup | call | [V] (called 11x) |
| 0xE938D70 | TLS init complete | call | [V] (called 11x) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [0x12AE2460] | 8 | W | 0xbcb0cbc | FNV1a hash result |
| [0x12AE2470] | 8 | W | 0xbcb0d65 | FNV1a hash result |
| [0x12AE2480] | 8 | W | 0xbcb0e0e | FNV1a hash result |
| [0x12AE2490] | 8 | W | 0xbcb0eb7 | FNV1a hash result |
| [0x12AE24A0] | 8 | W | 0xbcb0f60 | FNV1a hash result |
| [0x12AE22C0] | 8 | W | 0xbcb1009 | FNV1a hash result |
| [0x12AE22D0] | 8 | W | 0xbcb10c0 | FNV1a hash result |
| [0x12AE22E0] | 8 | W | 0xbcb1177 | FNV1a hash result |
| [0x12AE22F0] | 8 | W | 0xbcb122e | FNV1a hash result |
| [0x12AE2300] | 8 | W | 0xbcb12e5 | FNV1a hash result |
| [rbp+0x1018] | 8 | R | 0xbcb102f, 0xbcb10df, etc | string pointer (→ r12) |
| [rbp+0xA80] | 16 | R | multiple | string buffer (r14/r12) |
| [rbp+0xA90] | 8 | R | (implicit) | string data |
| [rbp+0xA98] | 8 | R | (implicit) | string capacity |

## RANGE 10: 0xbcb136e..0xbcb1a92 (lines 3601-4000)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcb136e..0xbcb1a92 | **Continued FNV1a hash loops for TLS globals 0x12AE2310..0x12AE23A0** (using r12 as string ptr from [rbp+0x1018]): 9 identical sequences, each computes FNV1a hash of error string, stores to target global ([0x12AE2310]..[0x12AE23A0]), calls 0x73150, calls 0xE938D70, sets r14=[rbp+0x1018], rdi=[rbp+0xA80], jmps to main function labels (0xBCAD5BB..0xBCAD708) |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| (none new) | | |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0x73150 | string cleanup | call | [V] (called 9x) |
| 0xE938D70 | TLS init complete | call | [V] (called 9x) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [0x12AE2310] | 8 | W | 0xbcb139c | FNV1a hash result |
| [0x12AE2320] | 8 | W | 0xbcb1453 | FNV1a hash result |
| [0x12AE2330] | 8 | W | 0xbcb150a | FNV1a hash result |
| [0x12AE2340] | 8 | W | 0xbcb15c1 | FNV1a hash result |
| [0x12AE2350] | 8 | W | 0xbcb1678 | FNV1a hash result |
| [0x12AE2360] | 8 | W | 0xbcb172f | FNV1a hash result |
| [0x12AE2370] | 8 | W | 0xbcb17e6 | FNV1a hash result |
| [0x12AE2380] | 8 | W | 0xbcb189d | FNV1a hash result |
| [0x12AE2390] | 8 | W | 0xbcb1954 | FNV1a hash result |
| [0x12AE23A0] | 8 | W | 0xbcb1a0b | FNV1a hash result |
| [rbp+0x1018] | 8 | R | multiple | string pointer (→ r12) |
| [rbp+0xA80] | 16 | R | multiple | string buffer |

## RANGE 11: 0xbcb1a94..0xbcb1d06 (lines 4001-4140)

### Phase Table
| Address Range | Description |
|---|---|
| 0xbcb1a94..0xbcb1c5d | **Final FNV1a hash loops for TLS globals 0x12AE23B0, 0x12AE23C0, 0x12AE23D0, 0x12AE23D8** (using r12 as string ptr from [rbp+0x1018]): 4 identical sequences, each computes FNV1a hash, stores to target global, calls 0x73150, calls 0xE938D70, sets r14=[rbp+0x1018], rdi=[rbp+0xA80], jmps to main function labels (0xBCAD72D..0xBCAD777) |
| 0xbcb1c62..0xbcb1d06 | **Final FNV1a hash for TLS global 0x12AE24B8** (using rbx as string ptr, different register setup): computes hash with rdx=FNV_offset_basis, rcx=FNV_prime, r9=index; stores hash to [0x12AE24B0], calls 0x73150, calls 0xE938D70, sets r13=[rbp+0x1018], jmps to 0xBCAE726 |

### Strings Referenced
| RVA | Text | Site / Callee |
|---|---|---|
| (none new) | | |

### Callees (in order)
| RVA | Target | Type | Tag |
|---|---|---|---|
| 0x73150 | string cleanup | call | [V] (called 5x) |
| 0xE938D70 | TLS init complete | call | [V] (called 5x) |

### [reg+off] Reads/Writes (Argument/Output Objects)
| Offset | Size | R/W | First Site | Context |
|---|---|---|---|---|
| [0x12AE23B0] | 8 | W | 0xbcb1ac2 | FNV1a hash result |
| [0x12AE23C0] | 8 | W | 0xbcb1b79 | FNV1a hash result |
| [0x12AE23D0] | 8 | W | 0xbcb1c30 | FNV1a hash result |
| [0x12AE23D8] | 8 | W | (implicit from jmp) | TLS global (init complete) |
| [0x12AE24B0] | 8 | W | 0xbcb1ce0 | FNV1a hash result for 0x12AE24B8 |
| [0x12AE24B8] | 4 | R/W | 0xbcb1cf3, 0xbcb1cfa | TLS global (init complete) |
| [rbp+0x1018] | 8 | R | multiple | string pointer (→ r12/r13) |
| [rbp+0xA80] | 16 | R | multiple | string buffer |

## TOOL REQUESTS
None
## ORCHESTRATOR: real content at every 0xF... RVA mentioned in this file (tools/sigs/rvastrdoc.py, 2026-11-16). Where a string label above disagrees with this table, THIS TABLE IS RIGHT (units guessed labels; movups loads show a 16-byte slice of longer names).
| RVA | real content at RVA (exe bytes) |
|---|---|
| 0xF152830 | bytes 0000003e0000003e |
| 0xF221610 | bytes a02d0a4001000000 |
| 0xF35EBD0 | bytes ec51383e00000000 |
| 0xF44B7C0 | bytes 8031cb4b01000000 |
| 0xF44B7F0 | bytes 673486fc273486fc |
| 0xF531C11 | "LuminanceMinMaxAndWhitePointAndMinWhitePoint" |
| 0xF5427FA | "ColorGrading_Contrast_Shadows" |
| 0xF542818 | "ColorGrading_Offset_Shadows" |
| 0xF542834 | "ColorGrading_Saturation_Shadows" |
| 0xF542854 | "ColorGrading_Gain_Shadows" |
| 0xF54286E | "ColorGrading_Gamma_Shadows" |
| 0xF54600B | "ColorGrading_Contrast_Highlights" |
| 0xF54602C | "ColorGrading_Offset_Highlights" |
| 0xF54604B | "ColorGrading_Saturation_Highlights" |
| 0xF54606E | "ColorGrading_Gain_Highlights" |
| 0xF54608B | "ColorGrading_Gamma_Highlights" |
| 0xF547EEF | "ColorPostProcess" |
| 0xF550D6A | "GenericTonemapperCrosstalkParams" |
| 0xF550E1C | "ColorGrading_Temperature_Params" |
| 0xF557C84 | "ColorGrading_Contrast_Midtones" |
| 0xF557CA3 | "ColorGrading_Offset_Midtones" |
| 0xF557CC0 | "ColorGrading_Saturation_Midtones" |
| 0xF557CE1 | "ColorGrading_Gain_Midtones" |
| 0xF557CFC | "ColorGrading_Gamma_Midtones" |
| 0xF563D27 | "RasterizedColor" |
| 0xF58CE4E | "CustomExposureCompensation" |
| 0xF58CE54 | "ExposureCompensation" |
| 0xF5A843D | "GenericTonemapperContrastAndScaleAndOffsetAndCrosstalk" |
| 0xF5C5E67 | "ColorPostProcessPhase" |
| 0xF5C6CE2 | "LuminanceColorTexture" |
| 0xF5C6CEB | "ColorTexture" |
| 0xF5DE7ED | "ViewportScale" |
| 0xF5E7C36 | "PreExposureLuminance" |
| 0xF5E7C75 | "AverageLuminance" |
| 0xF5FA4B5 | "RasterizedColorEnabled" |
| 0xF605A7B | "ColorGrading_Misc" |
| 0xF7DA6CD | "ColorGrading_Misc2" |
| 0xF7E419B | "TonemapParams0" |
| 0xF7E41AA | "GlobalParams0" |
| 0xF99FFA0 | bytes 4060ea4e01000000 |
| 0xF9A8C78 | bytes 5e059b0f00000000 |
| 0xF9A8F28 | bytes f8089b0f00000000 |
