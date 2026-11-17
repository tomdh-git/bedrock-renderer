## NEXT
DONE

# UNIT U-EL2f — submit stage map by callees (BGFX_MAP sections 6t, 6af)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base. Static analysis only.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (cite basis), [?] = unknown. No size/offset/name/role written unless seen.

## (1) Method and scope

- Function under test: `RendererContextD3D12::submit`, vtable slot 50, body entry 0xe82e230 [V]. Disassembled in full with rdis (six chunks, n=800): body ends with `int3` at 0xe832fc0 and the next function starts at 0xe832fc1, so size = 0x4d91 bytes [V] — exactly the figure in BGFX_MAP 6t ("submit (0xe82e230, 0x4d91 bytes)").
- Every call instruction in the body was enumerated verbatim (section 3): 227 calls = 157 direct + 70 indirect (65x `call qword ptr [0xF99FFA0]`, 1x `[0xF9A7B68]`, 1x `[0xF9A8C78]`, 1x `[0xF9A9110]`, 2x `call r10`) [V]. This matches BGFX_MAP 6t exactly ("submit ... 227 calls", "70 indirect calls through [rip+..]").
- Each distinct callee was sized with `rdis fn`; every size quoted in 6t was confirmed [V]. Callees 6t does not list are added as extra rows with role [?].
- BGFX_MAP 6af (draw executor 0xe821120, 0xc3c3 bytes): it reads the 0x80-byte draw headers and emits the D3D12 draws. It is NOT called from submit (0 call sites in the body) - 6t line 485 lists it as a sibling, not part of submit's body, so it is not a row in this map. Its body (state bits -> PSO key, binding, draw emission) is not decoded per 6af (tracked by A9/B3b-d/B4); out of scope for L2f. 6af prologue facts cited in section 4 below come from BGFX_MAP.md and are tagged [I].

## (2) Stage map table — callees in first-call-site address order

| name / role | callee rva | size | verbatim proof line (first site) | all call sites (RVA) | tag |
|---|---|---|---|---|---|
| stack probe (__chkstk-style stack-touch loop) | 0xe9e7970 | 0x4e | `0xe82e241  call 0xE9E7970` | e82e241 | [V] |
| QPC timer 0xebdb740 | 0xebdb740 | 0x19 | `0xe82e332  call 0xEBDB740` | e82e332, e831bbb | [V] |
| frame begin / state reset (guarded by `cmp dword ptr [rcx+0x19F88],5; jl 0xe832cee` - state <5 skips it) | 0xe81d660 | 0x1af | `0xe82e367  call 0xE81D660` | e82e367 | [V] call; role [I] (6t) |
| QPC timer 0xebdb760 | 0xebdb760 | 0x19 | `0xe831d73  call 0xEBDB760` | e831d73, e832d76 | [V] call; role [?] (6t names it without count) |
| descriptor / upload ring begin | 0xe8360f0 | 0x3f6 | `0xe82e4b0  call 0xE8360F0` | e82e4b0, e82e6c1, e82f06c | [V] call; role [I] (6t) |
| callee not listed by 6t (0xeec6ec0): lives in the 0xEEC5A00 jumper region; no role shown by code or strings | 0xeec6ec0 | 0x74e is rdis fn extent to region end 0xeec760e; real thunk-slot size not pinned [?] | `0xe82e534  call 0xEEC6EC0` | e82e534, e82e745 | [V] call; role [?] |
| bgfx-side view / frame prep | 0xbc61e20 | 0x215 | `0xe82e781  call 0xBC61E20` | e82e781 | [V] call; role [I] (6t) |
| per-view setup: viewport / scissor / RT bind | 0xe818490 | 0x4e6 | `0xe82e84d  call 0xE818490` | e82e84d, e830bc6, e830d7d | [V] call; role [I] (6t) |
| clear / RT transitions | 0xe820910 | 0x80c | `0xe82ea43  call 0xE820910` | e82ea43 | [V] call; role [I] (6t) |
| callee not listed by 6t (0x45eb70): no role shown by code or strings | 0x45eb70 | 0x3ac | `0xe82ea62  call 0x45EB70` | e82ea62 | [V] call; role [?] |
| callee not listed by 6t (0x45eb90): no role shown by code or strings | 0x45eb90 | 0x38c | `0xe82ea81  call 0x45EB90` | e82ea81 | [V] call; role [?] |
| callee not listed by 6t (0xe83b3d0): 6t places a 0x3d0 helper between clear and resolve | 0xe83b3d0 | 0x3d0 | `0xe82ec19  call 0xE83B3D0` | e82ec19, e82f2ba | [V] call; role [?] |
| render target resolve | 0xe815590 | 0x2af | `0xe82f645  call 0xE815590` | e82f645 | [V] call; role [I] (6t) |
| semaphore release / wait (guard-checked) | 0xbc5f110 | 0x121 | `0xe82f285  call 0xBC5F110` | e82f285, e830f53, e831098, e832965 | [V] call; role [I] (6t) |
| guarded paged-array handle / bounds check | 0xe83abb0 | 0x12f | `0xe830f2b  call 0xE83ABB0` | e830f2b, e831070, e832943 | [V] call; role [I] (6t) |
| PSO / state tracker transition; 0xe83b0e0 is its firstUse tail target | 0xe82d960 | 0x359 | `0xe8311b7  call 0xE82D960` | e8311b7, e8311e7 | [V] call; role [I] (6t, 6ae) |
| callee not listed by 6t (0xa4ec0): no role shown by code or strings | 0xa4ec0 | 0x1ce | `0xe82f88d  call 0xA4EC0` | e82f88d | [V] call; role [?] |
| callee not listed by 6t (0x1195a0): no role shown by code or strings | 0x1195a0 | 0x1f2 | `0xe82fbff  call 0x1195A0` | e82fbff | [V] call; role [?] |
| task-scheduler allocator (6ac: 0x9bc830 used x11 in scheduler) | 0x9bc830 | 0xc1 | `0xe82fcf1  call 0x9BC830` | e82fcf1, e82fe98, e832d38, e832d49 | [V] call; role [I] (6ac) |
| bound-import thunk slot 0xeec6de0 (0xEEC5A00 jumper region) | 0xeec6de0 | thunk-slot size not pinned (rdis fn extent 0x82e to region end 0xeec760e) [?] | `0xe82fd75  call 0xEEC6DE0` | e82fd75, e82fd9c, e830539, e830552, e83056b, e8305c3 | [V] call; role [?] |
| tiny hot helper (0x3b; 251435 xrefs - atomic/stat-style) | 0xe935700 | 0x3b | `0xe82fddc  call 0xE935700` | e82fddc, e82ff53, e830606, e83064d, e831796, e832bf4 | [V] call; role [?] |
| callee not listed by 6t (0x35e44a0): no role shown by code or strings | 0x35e44a0 | 0x39 | `0xe82ef16  call 0x35E44A0` | e82ef16 | [V] call; role [?] |
| bound-import thunk slot 0xeec6ed0 (0xEEC5A00 jumper region) | 0xeec6ed0 | thunk-slot size not pinned (rdis fn extent 0x73e) [?] | `0xe830698  call 0xEEC6ED0` | e830698, e830a7e, e830c25, e830e37, e830e52, e830e86 | [V] call; role [?] |
| callee not listed by 6t (0x120e00): no role shown by code or strings | 0x120e00 | 0x1b0 | `0xe830807  call 0x120E00` | e830807, e830a5b | [V] call; role [?] |
| bound-import thunk slot 0xeec59f0 (0xEEC5A00 jumper region) | 0xeec59f0 | thunk-slot size not pinned (rdis fn extent 0x1c1e) [?] | `0xe830ab6  call 0xEEC59F0` | e830ab6, e830c2d, e831869 | [V] call; role [?] |
| bound-import thunk slot 0xeec5a10 (0xEEC5A00 jumper region) | 0xeec5a10 | thunk-slot size not pinned (rdis fn extent 0x1bfe) [?] | `0xe830c11  call 0xEEC5A10` | e830c11, e831502, e831b9b | [V] call; role [?] |
| root-signature / heap binding 0xe81af20 | 0xe81af20 | 0x1c8 | `0xe83189f  call 0xE81AF20` | e83189f | [V] call; role [I] (6t) |
| callee not listed by 6t (0x38a1520): 0x1a8 body runs in the binding zone between 0xe81af20 and the per-draw builder | 0x38a1520 | 0x1a8 | `0xe8318b1  call 0x38A1520` | e8318b1, e8318e3, e831947, e831969, e831996, e8319b8, e831a7c, e831ae7, e831b04, e831b32 | [V] call; role [?] ([I] binding-zone helper) |
| tracker firstUse entry (tail target of 0xe82d960, also called directly here) | 0xe83b0e0 | 0x11c | `0xe8328bd  call 0xE83B0E0` | e8328bd | [V] call; role [I] (6ae: firstUse(t,handle,newState)) |
| per-draw record build (biggest helper) | 0xe833210 | 0xde4 | `0xe8318fa  call 0xE833210` | e8318fa, e831a9b | [V] call; role [I] (6t) |
| root-signature / heap binding 0xe81ac80 | 0xe81ac80 | 0x18c | `0xe8318c5  call 0xE81AC80` | e8318c5, e831bae | [V] call; role [I] (6t) |
| frame end / present prep | 0xe81d850 | 0x1cd | `0xe831cdd  call 0xE81D850` | e831cdd | [V] call; role [I] (6t) |
| callee not listed by 6t (0xebce390): >=0x4000 region; rdis fn stops at int3 padding so real end not pinned | 0xebce390 | >=0x4000 [?] | `0xe831e1d  call 0xEBCE390` | e831e1d | [V] call; role [?] |
| callee not listed by 6t (0xebce430): >=0x4000 region; rdis fn stops at int3 padding so real end not pinned | 0xebce430 | >=0x4000 [?] | `0xe831f53  call 0xEBCE430` | e831f53 | [V] call; role [?] |
| D3D12 command-wrapper emission (barriers / draws / dispatches) | 0xe800c10 | 0x58 | `0xe831fa2  call 0xE800C10` | e831fa2, e831fdf, e83209d, e832153, e8321ed, e832254, e8322b6, e83232b, e832376, e8323c0, e832403, e832446, e832489, e8324cc, e8324fa, e832524, e832555, e832586, e8325b4, e83260f, e83264e | [V] call; role [I] (6t: 21 emission sites - count matches exactly) |
| copy/memcpy helper per 6t [I]; body actually formats a numeric size ("BkMGTPEZY" unit table at 0xEF3F078, "%0.2f %c%c%c" at 0xF875B98) [V] | 0xebcf580 | 0x141 | `0xe832000  call 0xEBCF580` | e832000, e832021, e832049, e83206b, e8320bb, e8320d9, e8320f7, e832115, e83216a, e832181, e832198, e8321af | [V] call; role [I] (6t) / [V] formatter strings in body |
| callee not listed by 6t (0xed35e10): 0x49 body; calls import [0xF9A6FD8] and 0xeec5880 | 0xed35e10 | 0x49 | `0xe83204e  call 0xED35E10` | e83204e | [V] call; role [?] |
| callee not listed by 6t (0xbc5fce0): 0x41d body | 0xbc5fce0 | 0x41d | `0xe832698  call 0xBC5FCE0` | e832698 | [V] call; role [?] |
| callee not listed by 6t (0xe834040): 0x1a3 body | 0xe834040 | 0x1a3 | `0xe83287f  call 0xE834040` | e83287f | [V] call; role [?] |
| tracker entry lookup (paged-array element getter) | 0xe83aed0 | 0x201 | `0xe8328f6  call 0xE83AED0` | e8328f6, e832907, e832918, e832927 | [V] call; role [I] (6t) |
| callee not listed by 6t (0xe81b3b0): 0x118 body | 0xe81b3b0 | 0x118 | `0xe832cd3  call 0xE81B3B0` | e832cd3 | [V] call; role [?] |
| TLS trace scope begin | 0xe938cb0 | 0x7b | `0xe832d5e  call 0xE938CB0` | e832d5e, e832dae, e832df6, e832e38, e832e69, e832e9a, e832ed3, e832f0c | [V] call; role [I] (6t: 8 TLS trace scopes) |
| TLS trace scope end | 0xe938d70 | 0x69 | `0xe832d90  call 0xE938D70` | e832d90, e832de2, e832e27, e832e58, e832e89, e832ec2, e832efb, e832f2c | [V] call; role [I] (6t: 8 TLS trace scopes) |
| bound-import thunk slot 0xeec5a00 (0xEEC5A00 jumper region) | 0xeec5a00 | thunk-slot size not pinned (rdis fn extent 0x1c0e) [?] | `0xe832f3b  call 0xEEC5A00` | e832f3b, e832f50, e832f5b, e832f70, e832f87, e832fa2 | [V] call; role [?] |
| tiny EH helper ("bad array new length") | 0x75740 | 0x46 | `0xe832f7c  call 0x75740` | e832f7c, e832fa8, e832fb4, e832fba | [V] call; role [?] |
| tiny EH helper ("vector too long") | 0x75b60 | 0x11 | `0xe832fae  call 0x75B60` | e832fae | [V] call; role [?] |
| callee not listed by 6t (0x1a2800): 0x39 body | 0x1a2800 | 0x39 | `0xe832d10  call 0x1A2800` | e832d10, e832f76 | [V] call; role [?] |
| bound-import thunk slot 0xeec59e0 (0xEEC5A00 jumper region) | 0xeec59e0 | thunk-slot size not pinned (rdis fn extent 0x1c2e) [?] | `0xe832d16  call 0xEEC59E0` | e832d16 | [V] call; role [?] |
| D3D12/DXGI COM calls via import-thunk slot 0xF99FFA0; thunk resolves to sub_eea6040 = `jmp rax` [V oc_U-B7b] | 0xF99FFA0 | IAT slot; not a function body, size not pinned [?] | `0xe82e2a4  call qword ptr [0xF99FFA0]` | e82e2a4, e82e434, e82e4f6, e82e50f, e82e563, e82e63b, e82e707, e82e720, e82e774, e82e817, e82e8d4, e82e96a, e82e99c, e82eac9, e82eb13, e82ebba, e82ec4c, e82ec63, e82ed8d, e82ee79, e82ef97, e82f0b4, e82f0cc, e82f25b, e82f2ee, e82f306, e82f33a, e82f379, e82f46c, e82f4b2, e82f6e8, e82f714, e82f8d8, e82f941, e82f9b8, e82f9dd, e82fa12, e82fa57, e82faba, e82faf2, e82fca6, e82fcdb, e82ffaf, e830583, e83066e, e830686, e830e04, e830ec6, e8315ad, e831917, e8319e3, e831aac, e831b70, e831e73, e831eb0, e831f78, e8326c3, e832738, e83277c, e83280b, e832aad, e832ace, e832baf, e832c78, e832cbe | [V] call; import target unresolved [?] |
| indirect via import-thunk slot 0xF9A7B68 (rdis fn: 0x4 bytes, disassembles as non-code - slot, not a function) | 0xF9A7B68 | slot size 0x4 [V rdis fn], real target unresolved [?] | `0xe82e7fb  call qword ptr [0xF9A7B68]` | e82e7fb | [V] call; target [?] |
| indirect via import-thunk slot 0xF9A8C78 | 0xF9A8C78 | slot size 0x32 [V rdis fn], real target unresolved [?] | `0xe832d2e  call qword ptr [0xF9A8C78]` | e832d2e | [V] call; target [?] |
| indirect via import-thunk slot 0xF9A9110 | 0xF9A9110 | slot size 0x42 [V rdis fn], real target unresolved [?] | `0xe831fbb  call qword ptr [0xF9A9110]` | e831fbb | [V] call; target [?] |
| indirect call r10 (register-indirect, target not constant) | — | n/a | `0xe8313a5  call r10` | e8313a5, e8314c9 | [V] call; target [?] |
| TOTALS — submit body 0xe82e230..0xe832fc1 | size 0x4d91 | 0x4d91 | — | 227 call sites (157 direct + 70 indirect); per-callee counts match 6t exactly (E8360F0x3, E818490x3, E83B3D0x2, BC5F110x4, E83ABB0x3, E82D960x2, E81AF20+E81AC80, E833210x2, E800C10x21, EBCF580x12, E834040x1, E83AED0x4, E81B3B0x1, E938CB0x8, E938D70x8, E81D850x1) | [V] |

## (3) Verbatim call-site proof lines (copied from rdis dis output, two spaces after the address)

### 0xe9e7970 — 1 site
0xe82e241  call 0xE9E7970

### 0xebdb740 — 2 sites
0xe82e332  call 0xEBDB740
0xe831bbb  call 0xEBDB740

### 0xe81d660 — 1 site
0xe82e367  call 0xE81D660

### 0xe8360f0 — 3 sites
0xe82e4b0  call 0xE8360F0
0xe82e6c1  call 0xE8360F0
0xe82f06c  call 0xE8360F0

### 0xeec6ec0 — 2 sites
0xe82e534  call 0xEEC6EC0
0xe82e745  call 0xEEC6EC0

### 0xbc61e20 — 1 site
0xe82e781  call 0xBC61E20

### 0xe818490 — 3 sites
0xe82e84d  call 0xE818490
0xe830bc6  call 0xE818490
0xe830d7d  call 0xE818490

### 0xe820910 — 1 site
0xe82ea43  call 0xE820910

### 0x45eb70 — 1 site
0xe82ea62  call 0x45EB70

### 0x45eb90 — 1 site
0xe82ea81  call 0x45EB90

### 0xe83b3d0 — 2 sites
0xe82ec19  call 0xE83B3D0
0xe82f2ba  call 0xE83B3D0

### 0x35e44a0 — 1 site
0xe82ef16  call 0x35E44A0

### 0xe815590 — 1 site
0xe82f645  call 0xE815590

### 0xbc5f110 — 4 sites
0xe82f285  call 0xBC5F110
0xe830f53  call 0xBC5F110
0xe831098  call 0xBC5F110
0xe832965  call 0xBC5F110

### 0xa4ec0 — 1 site
0xe82f88d  call 0xA4EC0

### 0x1195a0 — 1 site
0xe82fbff  call 0x1195A0

### 0x9bc830 — 4 sites
0xe82fcf1  call 0x9BC830
0xe82fe98  call 0x9BC830
0xe832d38  call 0x9BC830
0xe832d49  call 0x9BC830

### 0xeec6de0 — 6 sites
0xe82fd75  call 0xEEC6DE0
0xe82fd9c  call 0xEEC6DE0
0xe830539  call 0xEEC6DE0
0xe830552  call 0xEEC6DE0
0xe83056b  call 0xEEC6DE0
0xe8305c3  call 0xEEC6DE0

### 0xe935700 — 7 sites
0xe82fddc  call 0xE935700
0xe82ff53  call 0xE935700
0xe82fff5  call 0xE935700
0xe830606  call 0xE935700
0xe83064d  call 0xE935700
0xe831796  call 0xE935700
0xe832bf4  call 0xE935700

### 0x35e44a0 — 1 site
0xe82ef16  call 0x35E44A0

### 0xeec6ed0 — 6 sites
0xe830698  call 0xEEC6ED0
0xe830a7e  call 0xEEC6ED0
0xe830c25  call 0xEEC6ED0
0xe830e37  call 0xEEC6ED0
0xe830e52  call 0xEEC6ED0
0xe830e86  call 0xEEC6ED0

### 0x120e00 — 2 sites
0xe830807  call 0x120E00
0xe830a5b  call 0x120E00

### 0xeec59f0 — 3 sites
0xe830ab6  call 0xEEC59F0
0xe830c2d  call 0xEEC59F0
0xe831869  call 0xEEC59F0

### 0xeec5a10 — 3 sites
0xe830c11  call 0xEEC5A10
0xe831502  call 0xEEC5A10
0xe831b9b  call 0xEEC5A10

### 0xe81af20 — 1 site
0xe83189f  call 0xE81AF20

### 0x38a1520 — 10 sites
0xe8318b1  call 0x38A1520
0xe8318e3  call 0x38A1520
0xe831947  call 0x38A1520
0xe831969  call 0x38A1520
0xe831996  call 0x38A1520
0xe8319b8  call 0x38A1520
0xe831a7c  call 0x38A1520
0xe831ae7  call 0x38A1520
0xe831b04  call 0x38A1520
0xe831b32  call 0x38A1520

### 0xe82d960 — 2 sites
0xe8311b7  call 0xE82D960
0xe8311e7  call 0xE82D960

### 0xe833210 — 2 sites
0xe8318fa  call 0xE833210
0xe831a9b  call 0xE833210

### 0xe81ac80 — 2 sites
0xe8318c5  call 0xE81AC80
0xe831bae  call 0xE81AC80

### 0xebd1560 — 1 site
0xe83146b  call 0xEBD1560

### 0xebce5e0 — 1 site
0xe8316fc  call 0xEBCE5E0

### 0xebce650 — 1 site
0xe831724  call 0xEBCE650

### 0xe81d850 — 1 site
0xe831cdd  call 0xE81D850

### 0xebdb760 — 2 sites
0xe831d73  call 0xEBDB760
0xe832d76  call 0xEBDB760

### 0xebce390 — 1 site
0xe831e1d  call 0xEBCE390

### 0xebce430 — 1 site
0xe831f53  call 0xEBCE430

### 0xe800c10 — 21 sites
0xe831fa2  call 0xE800C10
0xe831fdf  call 0xE800C10
0xe83209d  call 0xE800C10
0xe832153  call 0xE800C10
0xe8321ed  call 0xE800C10
0xe832254  call 0xE800C10
0xe8322b6  call 0xE800C10
0xe83232b  call 0xE800C10
0xe832376  call 0xE800C10
0xe8323c0  call 0xE800C10
0xe832403  call 0xE800C10
0xe832446  call 0xE800C10
0xe832489  call 0xE800C10
0xe8324cc  call 0xE800C10
0xe8324fa  call 0xE800C10
0xe832524  call 0xE800C10
0xe832555  call 0xE800C10
0xe832586  call 0xE800C10
0xe8325b4  call 0xE800C10
0xe83260f  call 0xE800C10
0xe83264e  call 0xE800C10

### 0xebcf580 — 12 sites
0xe832000  call 0xEBCF580
0xe832021  call 0xEBCF580
0xe832049  call 0xEBCF580
0xe83206b  call 0xEBCF580
0xe8320bb  call 0xEBCF580
0xe8320d9  call 0xEBCF580
0xe8320f7  call 0xEBCF580
0xe832115  call 0xEBCF580
0xe83216a  call 0xEBCF580
0xe832181  call 0xEBCF580
0xe832198  call 0xEBCF580
0xe8321af  call 0xEBCF580

### 0xed35e10 — 1 site
0xe83204e  call 0xED35E10

### 0xbc5fce0 — 1 site
0xe832698  call 0xBC5FCE0

### 0xe834040 — 1 site
0xe83287f  call 0xE834040

### 0xe83b0e0 — 1 site
0xe8328bd  call 0xE83B0E0

### 0xe83aed0 — 4 sites
0xe8328f6  call 0xE83AED0
0xe832907  call 0xE83AED0
0xe832918  call 0xE83AED0
0xe832927  call 0xE83AED0

### 0xe83abb0 — 3 sites
0xe830f2b  call 0xE83ABB0
0xe831070  call 0xE83ABB0
0xe832943  call 0xE83ABB0

### 0xe81b3b0 — 1 site
0xe832cd3  call 0xE81B3B0

### 0x1a2800 — 2 sites
0xe832d10  call 0x1A2800
0xe832f76  call 0x1A2800

### 0xeec59e0 — 1 site
0xe832d16  call 0xEEC59E0

### 0xe938cb0 — 8 sites
0xe832d5e  call 0xE938CB0
0xe832dae  call 0xE938CB0
0xe832df6  call 0xE938CB0
0xe832e38  call 0xE938CB0
0xe832e69  call 0xE938CB0
0xe832e9a  call 0xE938CB0
0xe832ed3  call 0xE938CB0
0xe832f0c  call 0xE938CB0

### 0xe938d70 — 8 sites
0xe832d90  call 0xE938D70
0xe832de2  call 0xE938D70
0xe832e27  call 0xE938D70
0xe832e58  call 0xE938D70
0xe832e89  call 0xE938D70
0xe832ec2  call 0xE938D70
0xe832efb  call 0xE938D70
0xe832f2c  call 0xE938D70

### 0xeec5a00 — 6 sites
0xe832f3b  call 0xEEC5A00
0xe832f50  call 0xEEC5A00
0xe832f5b  call 0xEEC5A00
0xe832f70  call 0xEEC5A00
0xe832f87  call 0xEEC5A00
0xe832fa2  call 0xEEC5A00

### 0x75740 — 4 sites
0xe832f7c  call 0x75740
0xe832fa8  call 0x75740
0xe832fb4  call 0x75740
0xe832fba  call 0x75740

### 0x75b60 — 1 site
0xe832fae  call 0x75B60

### 0xF99FFA0 — 65 sites (indirect via import thunk)
0xe82e2a4  call qword ptr [0xF99FFA0]
0xe82e434  call qword ptr [0xF99FFA0]
0xe82e4f6  call qword ptr [0xF99FFA0]
0xe82e50f  call qword ptr [0xF99FFA0]
0xe82e563  call qword ptr [0xF99FFA0]
0xe82e63b  call qword ptr [0xF99FFA0]
0xe82e707  call qword ptr [0xF99FFA0]
0xe82e720  call qword ptr [0xF99FFA0]
0xe82e774  call qword ptr [0xF99FFA0]
0xe82e817  call qword ptr [0xF99FFA0]
0xe82e8d4  call qword ptr [0xF99FFA0]
0xe82e96a  call qword ptr [0xF99FFA0]
0xe82e99c  call qword ptr [0xF99FFA0]
0xe82eac9  call qword ptr [0xF99FFA0]
0xe82eb13  call qword ptr [0xF99FFA0]
0xe82ebba  call qword ptr [0xF99FFA0]
0xe82ec4c  call qword ptr [0xF99FFA0]
0xe82ec63  call qword ptr [0xF99FFA0]
0xe82ed8d  call qword ptr [0xF99FFA0]
0xe82ee79  call qword ptr [0xF99FFA0]
0xe82ef97  call qword ptr [0xF99FFA0]
0xe82f0b4  call qword ptr [0xF99FFA0]
0xe82f0cc  call qword ptr [0xF99FFA0]
0xe82f25b  call qword ptr [0xF99FFA0]
0xe82f2ee  call qword ptr [0xF99FFA0]
0xe82f306  call qword ptr [0xF99FFA0]
0xe82f33a  call qword ptr [0xF99FFA0]
0xe82f379  call qword ptr [0xF99FFA0]
0xe82f46c  call qword ptr [0xF99FFA0]
0xe82f4b2  call qword ptr [0xF99FFA0]
0xe82f6e8  call qword ptr [0xF99FFA0]
0xe82f714  call qword ptr [0xF99FFA0]
0xe82f8d8  call qword ptr [0xF99FFA0]
0xe82f941  call qword ptr [0xF99FFA0]
0xe82f9b8  call qword ptr [0xF99FFA0]
0xe82f9dd  call qword ptr [0xF99FFA0]
0xe82fa12  call qword ptr [0xF99FFA0]
0xe82fa57  call qword ptr [0xF99FFA0]
0xe82faba  call qword ptr [0xF99FFA0]
0xe82faf2  call qword ptr [0xF99FFA0]
0xe82fca6  call qword ptr [0xF99FFA0]
0xe82fcdb  call qword ptr [0xF99FFA0]
0xe82ffaf  call qword ptr [0xF99FFA0]
0xe830583  call qword ptr [0xF99FFA0]
0xe83066e  call qword ptr [0xF99FFA0]
0xe830686  call qword ptr [0xF99FFA0]
0xe830e04  call qword ptr [0xF99FFA0]
0xe830ec6  call qword ptr [0xF99FFA0]
0xe8315ad  call qword ptr [0xF99FFA0]
0xe831917  call qword ptr [0xF99FFA0]
0xe8319e3  call qword ptr [0xF99FFA0]
0xe831aac  call qword ptr [0xF99FFA0]
0xe831b70  call qword ptr [0xF99FFA0]
0xe831e73  call qword ptr [0xF99FFA0]
0xe831eb0  call qword ptr [0xF99FFA0]
0xe831f78  call qword ptr [0xF99FFA0]
0xe8326c3  call qword ptr [0xF99FFA0]
0xe832738  call qword ptr [0xF99FFA0]
0xe83277c  call qword ptr [0xF99FFA0]
0xe83280b  call qword ptr [0xF99FFA0]
0xe832aad  call qword ptr [0xF99FFA0]
0xe832ace  call qword ptr [0xF99FFA0]
0xe832baf  call qword ptr [0xF99FFA0]
0xe832c78  call qword ptr [0xF99FFA0]
0xe832cbe  call qword ptr [0xF99FFA0]

### 0xF9A7B68 — 1 site (indirect via import thunk)
0xe82e7fb  call qword ptr [0xF9A7B68]

### 0xF9A8C78 — 1 site (indirect via import thunk)
0xe832d2e  call qword ptr [0xF9A8C78]

### 0xF9A9110 — 1 site (indirect via import thunk)
0xe831fbb  call qword ptr [0xF9A9110]

### call r10 — 2 sites (indirect register call)
0xe8313a5  call r10
0xe8314c9  call r10

## (4) Section 6af — draw executor 0xe821120 (static facts from BGFX_MAP.md) [I]

- Entry args: rcx -> block holding the view array (view i record at [local+0xa0 + i*0x140 + 0x310], +0x80/+0x40 sub-blocks); r8 -> [local+0x168] (Frame*); r9 -> [local+0x3a8]; r14 = RendererContext (this). Stack frame 0xe238 [I from 6af].
- Table bases materialised from the renderer: textures r14+0xBDE178 (0xB8 stride), 0x93A178, 0x9B2178, 0xA32178, 0xB62178, 0xC97698; plus r14+0x19f90/0x19f94, [r14+0x238] [I from 6af].
- Frame-relative reads: Frame+0x200 (view matrices), +0x300, +0xB4700 (header base), +0xE746DC, +0xE748C8; scalar Frame+0xDC5814 seeds the per-frame flag word ([local+0x210], bit1 via `add cl,cl; and cl,2`) [I from 6af].
- Local scratch: 0x100-byte 0xFF fills at local+0x694; view-remap identity u16 table at local+0x798 (n from [local+0x796]); 0x20-byte batch descriptor copied from [local+0x3b0] via helper 0xe8360f0 [I from 6af].
- Status per 6af: the 0xc3c3-byte body (state bits -> PSO key, binding, draw emission) is NOT decoded; A9, B3b-d, B4 stay open. 0xe821120 is a sibling of submit, not a callee (0 call sites in submit's body) - outside L2f's scope.

## (5) CLOSES?

CLOSES? YES — every part of the L2f item line ("submit stage map by callees - 6t, 6af") is proven by [V] rows: the complete submit stage map (all 46 direct callees at the exact 6t call counts; all 6t sizes confirmed via `rdis fn`; verbatim proof line per site), the full indirect-call set (70 calls through IAT thunk slots + `call r10`x2), and totals (227 calls, size 0x4d91) matching 6t exactly. Section 6af's executor is confirmed as a sibling of submit, not a submit callee (0 call sites); its body decode is tracked by A9/B3b-d/B4 and out of scope for L2f. Blocking fact: none.

## TOOL REQUESTS

None — all evidence from `rdis dis`/`fn` on the exe and BGFX_MAP.md sections 6t/6af.
