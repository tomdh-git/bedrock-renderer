## NEXT
Last analysed address: 0x52d4bee (end of listing). Analysis complete.

---

# Unit U-I5b: Ore UI / cohtml glue function 0x52d26a0 (analysis from verified listing docs/listings/L_52d26a0.txt)

## Function Bounds
- **RVA**: 0x52d26a0
- **Size**: 0x254e bytes
- **Range**: 0x52d26a0 .. 0x52d4bee
- **Listing file**: docs/listings/L_52d26a0.txt (1990 lines, verify_oc passes)

---

## (a) Phase Table (from L_52d26a0.txt)

| Address Range | Phase Description (1 sentence) | Key Instructions (from file) |
|---------------|--------------------------------|------------------------------|
| 0x52d26a0–0x52d2749 | Prologue: save regs, set up stack frame (rbp), load global context ptrs, call virtual fn at [0xF99FFA0] with dl=0x36, fetch ptr at [rbp+0x330]+0x10, branch on [rbp+0x348]==0 to early exit at 0x52d27eb | 0x52d26d2 `mov rcx,[0x1233E1B0]`; 0x52d26e2 `call qword ptr [0xF99FFA0]`; 0x52d2729 `call 0x1F4BDC0`; 0x52d2740 `call qword ptr [0xF99FFA0]`; 0x52d2749 `cmp dword ptr [rbp+0x348],0` |
| 0x52d2750–0x52d292b | Early-exit path (if [rbp+0x348]==0): iterate description list at [rbp+0x280]+0x98/0xA0, compare tag byte at [rdi+0x10] with bl, call 0xEEC6EB0 on match, store result to output at [r13], jump to epilogue 0x52d495c | 0x52d2768 `mov rdi,[rax+0x98]`; 0x52d276f `mov r12,[rax+0xA0]`; 0x52d27ad `cmp [rdi+0x10],bl`; 0x52d27dd `call 0xEEC6EB0`; 0x52d2927 `mov [r13],esi`; 0x52d292b `jmp 0x52D495C` |
| 0x52d27eb–0x52d292b | Alternate early-exit: similar list walk at [rbp+0x280]+0xB0 indexed by bl, fetch tag from [rdi], call 0x52d1a10 to insert into list, store to [r13], jump to epilogue | 0x52d280a `add rax,0xB0`; 0x52d2827 `mov rdi,[rax+rcx*8]`; 0x52d2854 `mov esi,[rdi]`; 0x52d2921 `call 0x52D1A10`; 0x52d2927 `mov [r13],esi` |
| 0x52d2930–0x52d2cbb | Full path: zero [rbp+0x338], call virtual at [0xF99FFA0] with dl=0x36, fetch vfunc at [r14]+0x848, call it, then fetch vfunc at [r14]+0x6C0, call with stack buffer at rbp+0x190, allocate object via [0x1233E1A8] size 0x98, refcount inc/dec on [rbp+0x198], call 0xA01DB70 (Cohtml view creation) | 0x52d293a `mov qword ptr [rax],0`; 0x52d295f `call r8`; 0x52d296b `mov rax,[rax+0x848]`; 0x52d2983 `call rdx`; 0x52d29ab `call r8`; 0x52d29c9 `call qword ptr [0xF99FFA0]`; 0x52d2a4c `call 0xA01DB70` |
| 0x52d2ae5–0x52d2cbb | Query vfuncs at [r14]+0x568, +0x4B0, +0x780, +0x848, store results to r12/r13/sil, allocate via [0x1233E1A8] size 0x298, zero stack buffers, call 0x40D2A0 (logging), refcount on [r14+0x10] | 0x52d2ae8 `mov rax,[rax+0x568]`; 0x52d2b0e `call rdx`; 0x52d2b14 `mov rdx,[rcx+0x4B0]`; 0x52d2b36 `call r8`; 0x52d2b5f `call rdx`; 0x52d2b87 `call rdx`; 0x52d2bfd `call qword ptr [0xF99FFA0]`; 0x52d2bd6 `call 0x40D2A0` |
| 0x52d2c10–0x52d2f2b | Refcount/string management on [rbp+0x198], [rbp+0x190], [rbp+0x1A0]; if valid call 0xA01DB70 again; build large Cohtml view object at rdx (size ~0x290) with vtable at 0xEFCC480/0xEFCC490, zero-init fields, set callbacks/ptrs at +0x80..+0xB0, flags at +0x240/+0x248, matrix zeroes at +0x24C..+0x288 | 0x52d2c30 `lock inc dword ptr [rax+8]`; 0x52d2c4c `call 0xA01DB70`; 0x52d2dcc `lea rax,[0xEFCC480]`; 0x52d2dd3 `mov [rdi],rax`; 0x52d2e0d `mov [rsi+8],rax`; 0x52d2e35 `lea rax,[0xF245FC0]`; 0x52d2e8f `movdqu [rdx+0x58],xmm2`; 0x52d2f8b `mov [rdx+0xA0],r15`; 0x52d2fc0 `mov byte ptr [rdx+0x240],0` |
| 0x52d2f2b–0x52d306a | Call virtual at [0xF99FFA0] with dl=0x36; check global flags at 0x128D8DEE/0x128D8DEF; if set and [r14+0x240]!=1 and [r14+0x1F8]==0 call 0x4FDE750; else call 0xEEC6ED0, set [r14+0x240]=1 | 0x52d3006 `call qword ptr [0xF99FFA0]`; 0x52d300f `cmp byte ptr [0x128D8DEE],0`; 0x52d302f `cmp byte ptr [r14+0x240],1`; 0x52d304d `call 0x4FDE750`; 0x52d305d `call 0xEEC6ED0`; 0x52d3062 `mov byte ptr [r14+0x240],1` |
| 0x52d306a–0x52d31c1 | String deallocation cleanup on [rbp+0x1F0]/[rbp+0x198] via 0xE935700 and refcount dec; call virtual at [r12]+0x6C0 with stack buffer at rbp+0x1F0; if result null or byte==0 jump to 0x52d3843; else release refs on [rbp+0x1F8]/[rbp+0x200] | 0x52d30c1 `call 0xE935700`; 0x52d31aa `call r8`; 0x52d31b8 `je 0x52D3843`; 0x52d31be `cmp byte ptr [rax],0`; 0x52d31ed `lock dec dword ptr [rsi+8]` |
| 0x52d31c3–0x52d3265 | Build draw params on stack at rbp+0x220..0x250: set word 0x220=1, dword 0x240=0x41000000, 0x247=0x1000000, 0x234=0x1F4; load matrix from 0xF242230 to rbp+0x224; read float from [rdi+0x40], cvt to int, compute clamped value into rbp+0x200; set byte 0x246=1 | 0x52d3265 `mov word ptr [rbp+0x220],1`; 0x52d326e `mov dword ptr [rbp+0x240],0x41000000`; 0x52d32ae `movsd xmm0,[rdi+0x40]`; 0x52d32d3 `movq [rbp+0x200],xmm0`; 0x52d32db `mov byte ptr [rbp+0x246],1` |
| 0x52d3265–0x52d3385 | Set up callbacks at rbp+0x208=0x52FED40, 0x210=0x52FF090; copy [rbp+0x2B8] to rbp+0x1F0, [rbp+0x2B0] to rbp+0x238; call virtual at [r12+0x10]→+0x18 with rbp+0x1F0; result in r13; call virtual on r13 at +0x1F8 twice with strings "window.__bedrockProvidedCohtmljs = true;" (0xF7D0777) and 0xF2424E0; call virtual at [0x1233E1B0] with dl=0x36 | 0x52d32ee `lea rax,[0x52FED40]`; 0x52d32fc `lea rax,[0x52FF090]`; 0x52d335f `call r8`; 0x52d3385 `lea rdx,[0xF7D0777]`; 0x52d338f `call r8`; 0x52d33b3 `lea rdx,[0xF2424E0]`; 0x52d33e6 `call r8` |
| 0x52d3385–0x52d3421 | Call virtual at [r12+0x18]→+0x8 with rbp+0x1F0; result in rsi, r14d=eax; fetch [r12+0x28], call virtual at [0x1233E1A8] size 0x168 → r12; test r12; pxor, set up stack args, call 0x9D6D0 with r9="ui_textured_premultiplied_alpha" (0xF60E118), len=0x1F, r12=material record — **SHADER REGISTRATION SITE** | 0x52d33fb `lea r8,[rbp+0x1F0]`; 0x52d3405 `call qword ptr [0xF99FFA0]`; 0x52d3489 `lea r9,[0xF60E118]`; 0x52d3490 `mov edx,0x1F`; 0x52d349c `call 0x9D6D0` |
| 0x52d3421–0x52d3521 | Material record init at rcx=r12: write vtable ptr at +0x0, shader ID at +0x8, zero +0x20..+0x50, write blend state 0x100000001 at +0x38, variant=1 at +0x40, texture bindings at +0x60=8, +0x68=0x100, +0x6C=0, more zeroes, texture handles at +0xA0/+0xC8/+0x128, counts at +0xA8/+0x130, userdata at +0x158=rsi, +0x160=rdi | 0x52d344f `mov [r12],r15`; 0x52d3453 `mov [r12+8],r14d`; 0x52d3528 `mov byte ptr [rcx+0x20],0`; 0x52d353f `mov [rcx+0x38],rax`; 0x52d3543 `mov dword ptr [rcx+0x40],1`; 0x52d355c `mov qword ptr [rcx+0x60],8`; 0x52d360f `mov [rcx+0x158],rsi` |
| 0x52d3521–0x52d369f | Call virtual at [0x1233E1B0] with byte from [rbp+0x2B8]; call virtual at [0x1233E1B0] with dl=0x36; call virtual at [0x1233E1A8] size 0xC8 → rdi; set up Cohtml draw call: 0xA0233E0, 0xA0228E0, virtual at [r12]+0x970, virtual at [0x1233E1A8] size 0xA8 → r10, refcount on [rbp+0x198], 0xA018300, list link at [rsi+0x38], virtual at [0x1233E1A8] size 0x48, 0xA0264A0, list link at [rsi+0x10] | 0x52d3639 `call qword ptr [0xF99FFA0]`; 0x52d3665 `call r8`; 0x52d368f `call r8`; 0x52d3705 `call 0xA0233E0`; 0x52d37c1 `call 0xA0228E0`; 0x52d37cd `call rdx`; 0x52d37e0 `call r10`; 0x52d381d `call 0xA018300`; 0x52d3891 `call qword ptr [0xF99FFA0]` |
| 0x52d369f–0x52d3a27 | Global refcount at 0x128C1508 (inc 0xE943178, dec 0xE94319C); check [0x128C1570] byte==1; lock inc [0x128C1578]; call virtual at +0x6E8 → esi; zero stack at rbp+0x200; release refs on r14; call 0x3B2020 if [rbp+0x1F8]==1; traverse r12 chain via +8/+0x238 to get byte at [rax+0x10] into edi | 0x52d37fa `lock inc qword ptr [0x128C1568]`; 0x52d3805 `call 0xE94319C`; 0x52d382f `lock inc dword ptr [rcx+8]`; 0x52d38a8 `call qword ptr [0xF99FFA0]`; 0x52d3946 `call 0x3B2020`; 0x52d3963 `mov rcx,[rcx+8]`; 0x52d3973 `movzx edi,byte ptr [rax+0x10]` |
| 0x52d397b–0x52d3c19 | Build vertex/uniform data on stack at rbp+0x190..0x1C8 (constants 1, 0xFA, 0x3F228F5C, 0x200000001, 0x78, 0x3F000000); call virtual at [0x1233E1A8] size 0xA0 → r15; cvtsi2ss esi, mul by 0xF242240; call 0x1F3A2C0 with rbp+0x190; call virtual at [r12]+0x568, +0x500, +0x358; call virtual at +0x58 with rbp+0x58 | 0x52d399f `mov dword ptr [rbp+0x190],1`; 0x52d39a9 `mov qword ptr [rbp+0x198],0xFA`; 0x52d3a1d `call r8`; 0x52d3a2d `cvtsi2ss xmm3,esi`; 0x52d3a31 `mulss xmm3,[0xF242240]`; 0x52d3a73 `call 0x1F3A2C0`; 0x52d3ad7 `call rdx`; 0x52d3b03 `call rdx`; 0x52d3b32 `call r8` |
| 0x52d3c19–0x52d3d39 | Texture upload: call 0xA01BDD0, 0xA0228E0, virtual at +0x970, virtual at [0x1233E1A8] size 0xA8, refcount on [rbp+0x198], 0xA018300, list link at [rsi+0x38]=r14, virtual size 0x48, 0xA0264A0, list link at [rsi+0x10] | 0x52d3c26 `call 0xA01BDD0`; 0x52d3cc1 `call 0xA0228E0`; 0x52d3cdf `call rdx`; 0x52d3d22 `call r8`; 0x52d3d38 `call 0xA018300`; 0x52d3e1f `call qword ptr [0xF99FFA0]`; 0x52d3e9e `call 0xA0264A0`; 0x52d3fbb `call 0x5302BB0` |
| 0x52d3d39–0x52d3f56 | Refcount cleanup on [rbp+0x198], [rbp+0x60]; build draw command on stack (rsp+0x20..0x50) with ptrs from rbp+0x10/0x18/0x30/0x28F/0xE8/0xF0; call 0x1F383F0; release refs on [rbp+0x198], [rbp+0x60] | 0x52d3d51 `lock inc dword ptr [rax+8]`; 0x52d3e29 `call 0x1F383F0`; 0x52d3e63 `lock dec dword ptr [rsi+8]`; 0x52d3f04 `lock dec dword ptr [rsi+0xC]` |
| 0x52d3f56–0x52d402a | Final submit: call virtual at [0x1233E1B0] with byte [rbp+0x168]; call virtual at [rdi]+0x568 → r15; call virtual at [0x1233E1B0] with dl=0x36; link r13 into list at [rbp+0x290]+0x20; free string at [rbp+0x118] via 0x52D1240/0xE935700; allocate list nodes via [0x1233E1A8] sizes 0x30/0xD0/0x48/0x80, link into lists at [rbp+0x170], [rbp+0xE8], [rbp+0x190] | 0x52d3f6b `call qword ptr [0xF99FFA0]`; 0x52d3f94 `call rdx`; 0x52d3fe0 `call r8`; 0x52d4018 `call 0x52D1240`; 0x52d4025 `call 0xE935700`; 0x52d404b `call r8`; 0x52d411e `call r8`; 0x52d41a4 `call r8`; 0x52d428d `call r8` |
| 0x52d402a–0x52d42ca | Cohtml element setup: 0xA018300, list link at [rsi+0x38], 0xA0264A0, list link at [rsi+0x10], 0x1F38E40/0xE935700 cleanup, 0x1F39A30, virtual at [r12]+0x568 → r12, virtual at +0x848, +0x38, +0x70, +0x48, +0x78, 0x625A480, 0x625BC10/0xE935700 cleanup, virtual at [r15]+0xD8 with 0x1E8 | 0x52d4138 `call 0xA018300`; 0x52d41da `call 0xA0264A0`; 0x52d4231 `call 0x1F38E40`; 0x52d4258 `call 0x1F39A30`; 0x52d42ad `call rdx`; 0x52d42ca `call 0x625A480`; 0x52d42f9 `call 0xE935700`; 0x52d432a `call r9` |
| 0x52d42ca–0x52d45b8 | Texture upload record at rdi: write width/height at +0x118/+0x11C, format 0x1C at +0x120, mip=1 at +0x124, comp=0 at +0x126, descriptor 0x100000001 at +0x128, zero swizzle at +0x138, offsets at +0x148/+0x14C, stride 0x28 at +0x150; call virtual at [0x1233E1B0] with byte [rbp+0x2B0]; call virtual at [r12]+0x38; append description to list at [rcx+0xA0] with tag=r15d, ptr=rdx, flags=al; call virtual at [rcx]+0x970 | 0x52d4461 `mov [rdi+0x118],r14d`; 0x52d4468 `mov [rdi+0x11C],esi`; 0x52d446e `mov dword ptr [rdi+0x120],0x1C`; 0x52d4596 `mov [r13],r15d`; 0x52d459a `mov [r13+8],rdx`; 0x52d45a5 `mov [r13+0x10],al`; 0x52d45a9 `add qword ptr [rcx+0xA0],0x18`; 0x52d456a `call rdx` |
| 0x52d45b8–0x52d49ed | List grow/resize logic: compute new capacity via multiply-shift (0xAAAAAAAAAAAAAAAB), allocate via [0x1233E1A8], copy old entries (0x18 each), zero new, update [rcx+0x98]/[rcx+0xA0]/[rcx+0xA8]; final epilogue: call virtual at [0x1233E1B0] with byte [rbp+0x2AF], if [rbp+0x348]==1 call 0x52D1A10; string cleanup via 0xE935700; pop regs, ret | 0x52d45ce `sar rcx,3`; 0x52d45d8 `imul rdx,rcx`; 0x52d462a `lea rdx,[r12*8]`; 0x52d4675 `call r8`; 0x52d46df `call 0x9BC830`; 0x52d4740 `mov ecx,[r14+rax]`; 0x52d48fd `mov rcx,[0x1233E1B0]`; 0x52d4912 `call qword ptr [0xF99FFA0]`; 0x52d4956 `call 0x52D1A10`; 0x52d49da `add rsp,0x348` |
| 0x52d49ee–0x52d4bee | Error handlers: 0x78ED0 (throw), 0x9BC830 (alloc) with sizes 0x98/1/0x298/0x18/0x168/0xC8/0x38/0xA8/0x48/0x80/0xD0/0x30, jump back to main flow labels; final: 0x75720 (terminate), 0x75740 (bad_alloc), 0x3B2020 (lock), int3 | 0x52d49ee `call 0x78ED0`; 0x52d49f9 `call 0x9BC830`; 0x52d4a17 `call 0x9BC830`; 0x52d4bb2 `call qword ptr [0xF9A8C78]`; 0x52d4bb9 `call 0x75720`; 0x52d4bca `call 0x75740`; 0x52d4be8 `call 0x3B2020`; 0x52d4bed `int3` |

---

## (b) Strings Referenced (RVA, text, call site)

| String RVA | Text | Call Site RVA | Context |
|------------|------|---------------|---------|
| 0xF7D0777 | "window.__bedrockProvidedCohtmljs = true;" | 0x52d3385 | Injected into Cohtml JS context via virtual call on r13 (+0x1F8) |
| 0xF60E118 | "ui_textured_premultiplied_alpha" | 0x52d3489 | Passed to shader/material registration 0x9D6D0 (r9=string, rdx=0x1F len, r12=material record) |
| 0xF2424E0 | (unknown, data ref) | 0x52d33b3 | Second JS injection via virtual call on r13 (+0x1F8) |
| 0xF242230 | (matrix data) | 0x52d32a0 | Loaded via movaps for draw params |
| 0xF089480 | (float const) | 0x52d32c0 | subps for float computation |
| 0xF242240 | (float const) | 0x52d3a31 | mulss for uniform scale |
| 0xEFCC480 | (vtable) | 0x52d2dcc | Cohtml view object vtable |
| 0xEFCC490 | (vtable) | 0x52d2e11 | String/SSO vtable |
| 0xF245FC0 | (vtable) | 0x52d2e35 | List node vtable |
| 0xF242320 | (vtable) | 0x52d2e4d | Cohtml view field |
| 0xF2423E0 | (vtable) | 0x52d2e5e | Cohtml view field |
| 0xF2462A0 | (vtable) | 0x52d369f | Cohtml element vtable |
| 0xF2462D0 | (vtable) | 0x52d36bb | Cohtml element vtable |
| 0xF246300 | (vtable) | 0x52d36de | Cohtml element vtable |
| 0xF246330 | (vtable) | 0x52d3a39 | Cohtml element vtable |
| 0xF0FFAE0 | (xmm data) | 0x52d44a4 | Texture upload swizzle |
| 0x128D00A0 | (string) | 0x52d2bcc | Logging via 0x40D2A0 |
| 0x128D8DEE | (flag byte) | 0x52d300f | Global flag check |
| 0x128D8DEF | (flag byte) | 0x52d301f | Global flag check |
| 0x1233E1A8 | (allocator) | multiple | Guarded paged array allocator |
| 0x1233E1B0 | (context) | multiple | Global render context |
| 0x128C1508 | (refcount obj) | 0x52d37eb | Global refcount |
| 0x128C1568 | (refcount) | 0x52d37fa | Global refcount |
| 0x128C1570 | (ptr) | 0x52d380a | Global object ptr |
| 0x128C1578 | (ptr) | 0x52d3823 | Global object ptr |
| 0x128C1580 | (ptr) | 0x52d385f | Global object ptr |
| 0x129C8290 | (data) | 0x52d34be | Hash/comparison data for 0x4DE7420 |

---

## (c) Callees in Order of First Appearance

| Order | Callee RVA | Name / Via | First Call Site | Count | Notes |
|-------|------------|------------|-----------------|-------|-------|
| 1 | 0x1F4BDC0 | sub_1f4bdc0 | 0x52d2729 | 1 | std::string ctor (SSO) |
| 2 | 0xEEA6040 | via [0xF99FFA0] | 0x52d26e2 | 40+ | CFG virtual call thunk |
| 3 | 0xEEC6EB0 | sub_eec6eb0 | 0x52d27dd | 2 | String compare/lookup |
| 4 | 0x52D1A10 | sub_52d1a10 | 0x52d2921 | 2 | Description list insert |
| 5 | 0xA01DB70 | sub_a01db70 | 0x52d2a4c | 2 | Cohtml view creation |
| 6 | 0x9BC830 | sub_9bc830 | 0x52d29c9 | 18 | Allocator (guarded paged array) |
| 7 | 0xE935700 | sub_e935700 | 0x52d2d64 | 9 | Vector/string dealloc |
| 8 | 0xF9A7D10 | via [0xF9A7D10] | 0x52d2e46 | 1 | VTable init |
| 9 | 0xEEC6EC0 | sub_eec6ec0 | 0x52d2dc0 | 1 | String copy/assign |
| 10 | 0xEEC6ED0 | sub_eec6ed0 | 0x52d305d | 1 | Mem clear/init |
| 11 | 0x4FDE750 | sub_4fde750 | 0x52d304d | 1 | Cohtml callback registration |
| 12 | 0x40D2A0 | sub_40d2a0 | 0x52d2bd6 | 1 | Logging/debug |
| 13 | 0x9D6D0 | sub_9d6d0 | 0x52d349c | 1 | **Shader/material registration** — "ui_textured_premultiplied_alpha" |
| 14 | 0x4DE7420 | sub_4de7420 | 0x52d34cf | 1 | Hash/comparison setup |
| 15 | 0x625A480 | sub_625a480 | 0x52d42ca | 1 | Texture/resource binding |
| 16 | 0x625BC10 | sub_625bc10 | 0x52d42ec | 1 | Resource release |
| 17 | 0xA01BDD0 | sub_a01bdd0 | 0x52d3c26 | 1 | Cohtml texture upload |
| 18 | 0xA0228E0 | sub_a0228e0 | 0x52d3cc1 | 1 | Cohtml draw call setup |
| 19 | 0xA018300 | sub_a018300 | 0x52d3d38 | 2 | Cohtml element creation |
| 20 | 0xA0264A0 | sub_a0264a0 | 0x52d3e9e | 1 | Cohtml layout/measure |
| 21 | 0x1F383F0 | sub_1f383f0 | 0x52d3e29 | 1 | Draw command encoding |
| 22 | 0x1F38E40 | sub_1f38e40 | 0x52d4231 | 1 | Resource cleanup |
| 23 | 0x1F39A30 | sub_1f39a30 | 0x52d4258 | 1 | Texture handle lookup |
| 24 | 0x1F3A2C0 | sub_1f3a2c0 | 0x52d3a73 | 1 | Uniform/constant setup |
| 25 | 0x52D1240 | sub_52d1240 | 0x52d4018 | 1 | List node cleanup |
| 26 | 0x5302BB0 | sub_5302bb0 | 0x52d40e1 | 2 | Intrusive list erase |
| 27 | 0xE943178 | sub_e943178 | 0x52d37f5 | 1 | Refcount increment |
| 28 | 0xE94319C | sub_e94319c | 0x52d3805 | 1 | Refcount decrement |
| 29 | 0x3B2020 | sub_3b2020 | 0x52d3946 | 2 | Global lock acquire/release |
| 30 | 0x78ED0 | sub_78ed0 | 0x52d49ee | 1 | Exception throw |
| 31 | 0x75720 | sub_75720 | 0x52d4bb9 | 1 | std::terminate |
| 32 | 0x75740 | sub_75740 | 0x52d4bca | 2 | std::bad_alloc |

---

## (d) [reg+off] Stores into Output/Description Objects

Compiled from the listing (non-stack, non-rbp/rsp). Each row: first site where the offset is written.

| Target Object (inferred) | Base Reg | Offset | Size | R/W | First Site RVA | Instruction (from file) | Meaning (inferred) |
|--------------------------|----------|--------|------|-----|----------------|-------------------------|---------------------|
| String/SSO buffer | rsi | +0x8 | 8 | W | 0x52d2e0d | `mov [rsi+8], rax` | Refcount / capacity |
| String/SSO buffer | rsi | +0x10 | 1 | W | 0x52d2e22 | `mov byte ptr [rsi+0x10], 1` | SSO length flag |
| Description list node | rcx | +0x8 | 8 | W | 0x52d2e2d | `mov [rcx+8], rax` | Next pointer |
| Description list node | rcx | +0x10 | 8 | W | 0x52d2e31 | `mov [rcx+0x10], rsi` | Prev/data pointer |
| Cohtml view object | rdx | +0x18 | 8 | W | 0x52d2e65 | `mov [rdx+0x18], rax` | JS context pointer |
| Cohtml view object | rdx | +0x20 | 16 | W | 0x52d2e6d | `movdqu [rdx+0x20], xmm0` | Zero-init (bounds/callbacks) |
| Cohtml view object | rdx | +0x30 | 16 | W | 0x52d2e72 | `movdqu [rdx+0x30], xmm0` | Zero-init |
| Cohtml view object | rdx | +0x40 | 8 | W | 0x52d2e77 | `mov qword ptr [rdx+0x40], 0` | Null pointer |
| Cohtml view object | rdx | +0x48 | 16 | W | 0x52d2e94 | `movdqu [rdx+0x48], xmm1` | Viewport dims (xmm1 from stack) |
| Cohtml view object | rdx | +0x58 | 16 | W | 0x52d2e8f | `movdqu [rdx+0x58], xmm2` | Viewport dims (xmm2 from stack) |
| Cohtml view object | rdx | +0x68 | 16 | W | 0x52d2eb6 | `movdqu [rdx+0x68], xmm0` | Zero-init |
| Cohtml view object | rdx | +0x78 | 8 | W | 0x52d2ebb | `mov qword ptr [rdx+0x78], 0` | Null pointer |
| Cohtml view object | rdx | +0x80 | 8 | W | 0x52d2ed2 | `mov [rdx+0x80], rax` | Callback / userdata |
| Cohtml view object | rdx | +0x88 | 8/16 | W | 0x52d2ed9 / 0x52d2f03 | `movdqu [rdx+0x88], xmm0` / `mov [rdx+0x88], rcx` | Overwritten: first zero, then ptr |
| Cohtml view object | rdx | +0x90 | 8 | W | 0x52d2f0a | `mov [rdx+0x90], rax` | Callback / userdata |
| Cohtml view object | rdx | +0x98 | 8 | W | 0x52d2f18 | `mov [rdx+0x98], rax` | Callback / userdata |
| Cohtml view object | rdx | +0xA0 | 8 | W | 0x52d2f8b | `mov [rdx+0xA0], r15` | Shader handle pointer |
| Cohtml view object | rdx | +0xA8 | 8 | W | 0x52d2fa0 | `mov qword ptr [rdx+0xA8], 0` | Null pointer |
| Cohtml view object | rdx | +0xB0 | 8 | W | 0x52d2fab | `mov [rdx+0xB0], r13` | Material pointer |
| Cohtml view object | rdx | +0x240 | 1 | W | 0x52d2fc0 | `mov byte ptr [rdx+0x240], 0` | Dirty flag |
| Cohtml view object | rdx | +0x248 | 1 | W | 0x52d2fc7 | `mov byte ptr [rdx+0x248], 1` | Initialized flag |
| Cohtml view object | rdx | +0x24C | 16 | W | 0x52d2fce | `movdqu [rdx+0x24C], xmm0` | Zero-init (transform matrix?) |
| Cohtml view object | rdx | +0x25C | 16 | W | 0x52d2fd6 | `movdqu [rdx+0x25C], xmm0` | Zero-init |
| Cohtml view object | rdx | +0x26C | 16 | W | 0x52d2fde | `movdqu [rdx+0x26C], xmm0` | Zero-init |
| Cohtml view object | rdx | +0x27C | 16 | W | 0x52d2fe6 | `movdqu [rdx+0x27C], xmm0` | Zero-init |
| Cohtml view object | rdx | +0x288 | 16 | W | 0x52d2fee | `movdqu [rdx+0x288], xmm0` | Zero-init |
| Description list head | r14 | +0x240 | 1 | W | 0x52d3062 | `mov byte ptr [r14+0x240], 1` | Processed flag |
| Material/shader record | r12 | +0x0 | 8 | W | 0x52d344f | `mov [r12], r15` | VTable pointer |
| Material/shader record | r12 | +0x8 | 4 | W | 0x52d3453 | `mov [r12+8], r14d` | Shader ID / flags |
| Material/shader record | rcx | +0x20 | 1 | W | 0x52d3528 | `mov byte ptr [rcx+0x20], 0` | Transparency flag |
| Material/shader record | rcx | +0x28 | 16 | W | 0x52d3530 | `movdqu [rcx+0x28], xmm0` | Zero-init (params) |
| Material/shader record | rcx | +0x38 | 8 | W | 0x52d353f | `mov [rcx+0x38], rax` | Blend state packed (0x100000001) |
| Material/shader record | rcx | +0x40 | 4 | W | 0x52d3543 | `mov dword ptr [rcx+0x40], 1` | Shader variant index |
| Material/shader record | rcx | +0x44 | 16 | W | 0x52d354a | `movdqu [rcx+0x44], xmm0` | Zero-init |
| Material/shader record | rcx | +0x50 | 16 | W | 0x52d354f | `movdqu [rcx+0x50], xmm0` | Zero-init |
| Material/shader record | rcx | +0x60 | 8 | W | 0x52d355c | `mov qword ptr [rcx+0x60], 8` | Texture binding count |
| Material/shader record | rcx | +0x68 | 2 | W | 0x52d3562 | `mov word ptr [rcx+0x68], 0x100` | Texture flags |
| Material/shader record | rcx | +0x6C | 1 | W | 0x52d3566 | `mov byte ptr [rcx+0x6C], 0` | Sampler index |
| Material/shader record | rcx | +0x70 | 16 | W | 0x52d3572 | `movdqu [rcx+0x70], xmm0` | Zero-init |
| Material/shader record | rcx | +0x88 | 1 | W | 0x52d357a | `mov byte ptr [rcx+0x88], 0` | Alpha mode flag |
| Material/shader record | rcx | +0x90 | 16 | W | 0x52d3581 | `movdqu [rcx+0x90], xmm0` | Zero-init |
| Material/shader record | rcx | +0xA0 | 8 | W | 0x52d3586 | `mov [rcx+0xA0], rax` | Texture handle array |
| Material/shader record | rcx | +0xA8 | 4 | W | 0x52d358b | `mov dword ptr [rcx+0xA8], 1` | Texture count |
| Material/shader record | rcx | +0xAC | 16 | W | 0x52d3593 | `movdqu [rcx+0xAC], xmm0` | Zero-init |
| Material/shader record | rcx | +0xB8 | 16 | W | 0x52d359b | `movdqu [rcx+0xB8], xmm0` | Zero-init |
| Material/shader record | rcx | +0xC8 | 8 | W | 0x52d35a6 | `mov qword ptr [rcx+0xC8], 8` | Second texture binding |
| Material/shader record | rcx | +0xD0 | 2 | W | 0x52d35af | `mov word ptr [rcx+0xD0], 0x100` | Second texture flags |
| Material/shader record | rcx | +0xD4 | 1 | W | 0x52d35b6 | `mov byte ptr [rcx+0xD4], 0` | Second sampler index |
| Material/shader record | rcx | +0xD8 | 16 | W | 0x52d35be | `movdqu [rcx+0xD8], xmm0` | Zero-init |
| Material/shader record | rcx | +0xF0 | 1 | W | 0x52d35c5 | `mov byte ptr [rcx+0xF0], 0` | Clamp/wrap mode |
| Material/shader record | rcx | +0xF8 | 16 | W | 0x52d35d5 | `movdqu [rcx+0xF8], xmm0` | Zero-init |
| Material/shader record | rcx | +0x108 | 16 | W | 0x52d35cd | `movdqu [rcx+0x108], xmm0` | Zero-init |
| Material/shader record | rcx | +0x117 | 16 | W | 0x52d35c5 | `movdqu [rcx+0x117], xmm0` | Zero-init (unaligned) |
| Material/shader record | rcx | +0x128 | 8 | W | 0x52d35dd | `mov [rcx+0x128], rax` | Third texture handle |
| Material/shader record | rcx | +0x130 | 4 | W | 0x52d35e4 | `mov dword ptr [rcx+0x130], 1` | Third texture count |
| Material/shader record | rcx | +0x134 | 16 | W | 0x52d35f6 | `movdqu [rcx+0x134], xmm0` | Zero-init |
| Material/shader record | rcx | +0x13D | 16 | W | 0x52d35ee | `movdqu [rcx+0x13D], xmm0` | Zero-init (unaligned) |
| Material/shader record | rcx | +0x150 | 4 | W | 0x52d35fe | `mov dword ptr [rcx+0x150], 8` | Fourth binding |
| Material/shader record | rcx | +0x154 | 1 | W | 0x52d3608 | `mov byte ptr [rcx+0x154], 0` | Fourth sampler |
| Material/shader record | rcx | +0x158 | 8 | W | 0x52d360f | `mov [rcx+0x158], rsi` | Userdata / callback |
| Material/shader record | rcx | +0x160 | 8 | W | 0x52d3616 | `mov [rcx+0x160], rdi` | Userdata / callback |
| Description list node | r12 | +0x0 | 8 | W | 0x52d3ff7 | `mov [r12], r13` | Next pointer |
| Description list head | rax | +0x0 | 8 | W | 0x52d400d | `mov [rax], r14` | Head pointer update |
| Description list node | rsi | +0x0 | 8 | W | 0x52d405b | `mov [rsi], r13` | Next pointer |
| Description list head | rax | +0x0 | 8 | W | 0x52d407e | `mov [rax], rsi` | Head pointer update |
| Cohtml element | rsi | +0x38 | 8 | W | 0x52d4150 | `mov [rsi+0x38], r14` | Child/next element |
| Cohtml element | rsi | +0x8 | 8 | W | 0x52d4178 | `mov [rsi+8], r14` | Parent/prev element |
| Cohtml element | rax | +0x0 | 8 | W | 0x52d41b8 | `mov [rax], r14` | VTable / type |
| Cohtml element | rsi | +0x10 | 8 | W | 0x52d41eb | `mov [rsi+0x10], rax` | Child list head |
| Cohtml element | rax | +0x0 | 8 | W | 0x52d421c | `mov [rax], rcx` | List link |
| Cohtml element | rax | +0x0 | 8 | W | 0x52d42e1 | `mov [rax], rcx` | List link |
| Render context | rcx | +0x260 | 8 | W | 0x52d433c | `mov [rcx+0x260], rax` | Cohtml view pointer |
| Texture/upload record | rdi | +0x118 | 4 | W | 0x52d4461 | `mov [rdi+0x118], r14d` | Width |
| Texture/upload record | rdi | +0x11C | 4 | W | 0x52d4468 | `mov [rdi+0x11C], esi` | Height |
| Texture/upload record | rdi | +0x120 | 4 | W | 0x52d446e | `mov dword ptr [rdi+0x120], 0x1C` | Format / flags |
| Texture/upload record | rdi | +0x124 | 2 | W | 0x52d4478 | `mov word ptr [rdi+0x124], 1` | Mip count |
| Texture/upload record | rdi | +0x126 | 1 | W | 0x52d4481 | `mov byte ptr [rdi+0x126], 0` | Compression flag |
| Texture/upload record | rdi | +0x128 | 8 | W | 0x52d4488 | `mov [rdi+0x128], rax` | Packed descriptor (0x100000001) |
| Texture/upload record | rdi | +0x138 | 16 | W | 0x52d4492 | `movdqu [rdi+0x138], xmm0` | Zero-init (swizzle) |
| Texture/upload record | rdi | +0x148 | 4 | W | 0x52d44b4 | `mov dword ptr [rdi+0x148], 0` | Offset X |
| Texture/upload record | rdi | +0x14C | 1 | W | 0x52d44be | `mov byte ptr [rdi+0x14C], 0` | Offset Y |
| Texture/upload record | rdi | +0x150 | 4 | W | 0x52d44c5 | `mov dword ptr [rdi+0x150], 0x28` | Stride / pitch |
| Texture/upload record | rdi | +0x154 | 1 | W | 0x52d44cf | `mov byte ptr [rdi+0x154], 0` | Array index |
| Description list node | r13 | +0x0 | 4 | W | 0x52d4596 | `mov [r13], r15d` | Tag / type ID |
| Description list node | r13 | +0x8 | 8 | W | 0x52d459a | `mov [r13+8], rdx` | Pointer to data |
| Description list node | r13 | +0x10 | 1 | W | 0x52d45a5 | `mov [r13+0x10], al` | Flags |
| Description list head | rcx | +0xA0 | 8 | W | 0x52d45a9 | `add qword ptr [rcx+0xA0], 0x18` | Size/end pointer |

---

## Where 'ui_textured_premultiplied_alpha' is used

**String location**: 0xF60E118 (.rdata)

**Call site**: 0x52d3489–0x52d349c (from L_52d26a0.txt lines 750–753):
```
0x52d3489  lea r9,[0xF60E118]        ; "ui_textured_premultiplied_alpha"
0x52d3490  mov edx,0x1F              ; string length = 31
0x52d3495  mov [rbp+0x278],r12       ; material record pointer
0x52d349c  call 0x9D6D0              ; sub_9d6d0 — shader/material registration
```

**Following callee**: `sub_9d6d0` (0x9D6D0). This is the **shader/material registration function** that registers a shader permutation by name. The call passes:
- r9 = string pointer ("ui_textured_premultiplied_alpha")
- rdx = 0x1F (string length)
- r12 = material record (allocated at 0x52d3443 via allocator 0x9BC830 size 0x168)
- [rbp+0x278] = same material record pointer (redundant)

This is where the Ore UI / cohtml glue registers the **premultiplied-alpha textured shader variant** used for UI rendering. The material record at r12 is fully initialized just before (0x52d344f–0x52d3616) with vtable, shader ID, blend state, texture bindings, and userdata.