# Unit U-FX4 progress — FullscreenEffect visitor (tag 7) body decode (listing lines 4253..5869)

## Source
- Listing: docs/data/listings/effect_visitor_666aca0_667191c.txt (each line `0xRVA  instruction`)
- Target range: listing lines 4253..5869 (end of file; file has 5869 lines, verified)
- Context (from oc_U-FX3): tag-7 body entered at 0x666b5cf (listing line 475); U-FX3 tables covered lines 2950..4259 and placed the tag-7 body epilogue jump at line 4252 `jmp 0x6670032` (RVA 0x666FBBB) [V]. Lines 4253..5869 are cold-path targets of those branches plus whatever jump-table cases (other tags) begin inside this range.

## Register context carried from oc_U-FX3 [I]
- r12 = description pointer after line 3115 `mov r12,[r12]` (before that, slot address r15+0x78). Reused/clobbered later in this range (e.g. line 4341 `mov r12,[r14]`).
- rsi = description pointer reloaded at lines 3276/3294 `mov rsi,[rax+0x78]` (rax=[rbp+0x668]); clobbered at line 4196.
- r13 = copy of description pointer (r13=r12 at line 3114).
- Other registers hold chain/refcount/heap objects; [rbp+...] stack slots. Notes tag [V]=seen in listing, [I]=inferred, [?]=unknown.

## NEXT
Resume at listing line 4253 (first line of this unit). Block 1 (4253..4292) below; next block to append: 4293..4332.

## Block 1 — listing lines 4253..4292 (40 lines)

### lines 4253..4292 (0x666FBC0..0x666FC73)
Cold-path tail of a bucket-chain splice (shared with the tag-7 body): links (rax, rdx=[rax+8]) in after r14=[rbp+0x658] in bucket [rcx+rdi*16], with duplicate-entry checks (r8 vs rax; [rcx+rdi+8] vs rdx) jumping to 0x666FC6D / 0x666FC73 / 0x666FC7C [V]. All instruction text below is quoted exactly from the listing.

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4253 | 0x666FBC0 | `mov rax,[rbx]` | [rbx] qword → rax [V] |
| 4254 | 0x666FBC3 | `mov r14,[rbp+0x658]` | r14 = stack slot [rbp+0x658] [V] |
| 4255 | 0x666FBCA | `mov qword ptr [rbp+0x3F8],0` | zero stack slot [V] |
| 4256 | 0x666FBD5 | `mov rdx,[rax+8]` | [rax+8] qword → rdx [V] |
| 4257 | 0x666FBD9 | `inc qword ptr [rbp+0x5F0]` | [rbp+0x5F0] qword++ [V] |
| 4258 | 0x666FBE0 | `mov [r14],rax` | store rax at [r14] [V] |
| 4259 | 0x666FBE3 | `mov [r14+8],rdx` | store rdx at [r14+8] [V] |
| 4260 | 0x666FBE7 | `mov [rdx],r14` | back-link patch [rdx]=r14 [V] |
| 4261 | 0x666FBEA | `mov [rax+8],r14` | back-link patch [rax+8]=r14 [V] |
| 4262 | 0x666FBEE | `mov rcx,[rbp+0x5F8]` | bucket base pointer [V] |
| 4263 | 0x666FBF5 | `and rdi,[rbp+0x610]` | rdi = index mask [V] |
| 4264 | 0x666FBFC | `shl rdi,4` | rdi *= 16 (entry stride) [V] |
| 4265 | 0x666FC00 | `mov r8,[rcx+rdi]` | bucket head → r8 [V] |
| 4266 | 0x666FC04 | `cmp r8,[rbp+0x5E8]` | compare head with limit [V] |
| 4267 | 0x666FC0B | `je short 0x666FC73` | branch exit 0x666FC73 [V] |
| 4268 | 0x666FC0D | `cmp r8,rax` | duplicate check vs rax [V] |
| 4269 | 0x666FC10 | `je short 0x666FC6D` | branch exit 0x666FC6D [V] |
| 4270 | 0x666FC12 | `cmp [rcx+rdi+8],rdx` | compare bucket+8 with rdx [V] |
| 4271 | 0x666FC17 | `jne short 0x666FC7C` | branch exit 0x666FC7C [V] |
| 4272 | 0x666FC19 | `jmp short 0x666FC77` | branch exit 0x666FC77 [V] |
| 4273 | 0x666FC1B | `mov rax,rbx` | rax = rbx [V] |
| 4274 | 0x666FC1E | `mov r14,[rbp+0x658]` | r14 = stack slot again [V] |
| 4275 | 0x666FC25 | `mov qword ptr [rbp+0x3F8],0` | zero stack slot [V] |
| 4276 | 0x666FC30 | `mov rdx,[rax+8]` | [rax+8] qword → rdx [V] |
| 4277 | 0x666FC34 | `inc qword ptr [rbp+0x5F0]` | [rbp+0x5F0] qword++ [V] |
| 4278 | 0x666FC3B | `mov [r14],rax` | store rax [V] |
| 4279 | 0x666FC3E | `mov [r14+8],rdx` | store rdx [V] |
| 4280 | 0x666FC42 | `mov [rdx],r14` | back-link patch [V] |
| 4281 | 0x666FC45 | `mov [rax+8],r14` | back-link patch [V] |
| 4282 | 0x666FC49 | `mov rcx,[rbp+0x5F8]` | bucket base pointer [V] |
| 4283 | 0x666FC50 | `and rdi,[rbp+0x610]` | index mask [V] |
| 4284 | 0x666FC57 | `shl rdi,4` | stride 16 [V] |
| 4285 | 0x666FC5B | `mov r8,[rcx+rdi]` | bucket head → r8 [V] |
| 4286 | 0x666FC5F | `cmp r8,[rbp+0x5E8]` | compare head [V] |
| 4287 | 0x666FC66 | `je short 0x666FC73` | branch exit 0x666FC73 [V] |
| 4288 | 0x666FC68 | `cmp r8,rax` | duplicate check [V] |
| 4289 | 0x666FC6B | `jne short 0x666FC12` | branch exit 0x666FC12 [V] |
| 4290 | 0x666FC6D | `mov [rcx+rdi],r14` | store r14 into bucket slot [V] |
| 4291 | 0x666FC71 | `jmp short 0x666FC7C` | branch exit 0x666FC7C [V] |
| 4292 | 0x666FC73 | `mov [rcx+rdi],r14` | store r14 into bucket slot [V] |

**Branch exits in this block:** 0x666FC73 (lines 4267, 4287), 0x666FC6D (line 4269), 0x666FC7C (lines 4271, 4291), 0x666FC77 (line 4272), 0x666FC12 (line 4289). Calls: none. No description-pointer reads (r12/r13/rsi not used).

## Block 2 — listing lines 4293..4332 (40 lines)

### lines 4293..4332 (0x666FC77..0x666FD3B)
Second cold-path splice variant (same shape as block 1, entering at 0x666FC77), followed by a 0x50-byte allocation sequence: reads global [0x129F9240]/[0x129F9228] for allocator state, loads [rax+0x40] and [rax+0x68] from [rbp+0x650] object, calls allocator 0xE935700 / qword ptr [0xF99FFA0] [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4293 | 0x666FC77 | `mov [rcx+rdi+8],r14` | store r14 at [rcx+rdi+8] [V] |
| 4294 | 0x666FC7C | `mov r14,[rbp+0x3F8]` | r14 = stack slot (zeroed above) [V] |
| 4295 | 0x666FC83 | `test r14,r14` | test r14 [V] |
| 4296 | 0x666FC86 | `je short 0x666FC9E` | branch exit 0x666FC9E [V] |
| 4297 | 0x666FC88 | `lea rcx,[r14+0x10]` | rcx = r14+0x10 [V] |
| 4298 | 0x666FC8C | `call 0x9B250` | call 0x9B250 [V] |
| 4299 | 0x666FC91 | `mov edx,0x50` | edx = 0x50 (allocation size) [V] |
| 4300 | 0x666FC96 | `mov rcx,r14` | rcx = r14 [V] |
| 4301 | 0x666FC99 | `call 0xE935700` | call 0xE935700 [V] |
| 4302 | 0x666FC9E | `cmp qword ptr [0x129F9240],0x10` | compare global with 0x10 [V] |
| 4303 | 0x666FCA6 | `jb short 0x666FCB1` | branch exit 0x666FCB1 [V] |
| 4304 | 0x666FCA8 | `mov r13,[0x129F9228]` | r13 = global pointer [V] |
| 4305 | 0x666FCAF | `jmp short 0x666FCB8` | branch exit 0x666FCB8 [V] |
| 4306 | 0x666FCB1 | `lea r13,[0x129F9228]` | rcx... r13 = address of global [V] |
| 4307 | 0x666FCB8 | `mov rax,[rbp+0x650]` | rax = object pointer [V] |
| 4308 | 0x666FCBF | `mov rbx,[rax+0x40]` | [rax+0x40] qword → rbx [V] |
| 4309 | 0x666FCC3 | `mov r15,[rax+0x68]` | [rax+0x68] qword → r15 [V] |
| 4310 | 0x666FCC7 | `mov rdi,[0x129F9238]` | rdi = global [V] |
| 4311 | 0x666FCCE | `mov eax,[rbp+0x5E0]` | eax = dword [rbp+0x5E0] [V] |
| 4312 | 0x666FCD4 | `mov [rbp+0x300],eax` | store eax [V] |
| 4313 | 0x666FCDA | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 4314 | 0x666FCDD | `movups [rbp+0x308],xmm0` | zero 16 bytes at [rbp+0x308] [V] |
| 4315 | 0x666FCE4 | `mov rcx,[0x1233E1A8]` | rcx = global heap handle [V] |
| 4316 | 0x666FCEB | `mov rax,[rcx]` | [rcx] qword → rax [V] |
| 4317 | 0x666FCEE | `mov rax,[rax+8]` | [rax+8] qword → rax [V] |
| 4318 | 0x666FCF2 | `mov edx,0x50` | edx = 0x50 [V] |
| 4319 | 0x666FCF7 | `call qword ptr [0xF99FFA0]` | indirect call allocator [V] |
| 4320 | 0x666FCFD | `nop` | — |
| 4321 | 0x666FCFE | `mov rsi,rax` | rsi = allocation result [V] |
| 4322 | 0x666FD01 | `test rax,rax` | test result [V] |
| 4323 | 0x666FD04 | `je 0x66709C7` | branch exit 0x66709C7 [V] |
| 4324 | 0x666FD0A | `mov [rbp+0x660],rdi` | store rdi [V] |
| 4325 | 0x666FD11 | `mov [rsi],rsi` | self-pointer init [rsi]=rsi [V] |
| 4326 | 0x666FD14 | `mov [rsi+8],rsi` | [rsi+8]=rsi [V] |
| 4327 | 0x666FD18 | `mov [rbp+0x308],rsi` | store rsi [V] |
| 4328 | 0x666FD1F | `lea rcx,[rbp+0x318]` | rcx = stack addr [V] |
| 4329 | 0x666FD26 | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 4330 | 0x666FD29 | `movups [rbp+0x318],xmm0` | zero stack block [V] |
| 4331 | 0x666FD30 | `mov qword ptr [rbp+0x328],0` | zero stack slot [V] |
| 4332 | 0x666FD3B | `movups xmm0,[rbp+0x610]` | load 16 bytes [rbp+0x610] → xmm0 [V] |

**Branch exits:** 0x666FC9E (4296), 0x666FCB1 (4303), 0x666FCB8 (4305), 0x66709C7 (4323). Calls: 0x9B250 (4298), 0xE935700 (4301), qword ptr [0xF99FFA0] (4319). No description reads.

## Block 3 — listing lines 4333..4372 (40 lines)

### lines 4333..4372 (0x666FD42..0x666FE01)
Continues setup: copies [rbp+0x610]/[rbp+0x600] state, computes (rdi-rsi)>>3 count, calls 0x76B30, then walks a circular list via r12=[r14], [r12] following until r12==r14, calling 0xAA840 per element [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4333 | 0x666FD42 | `movups [rbp+0x330],xmm0` | store 16 bytes [V] |
| 4334 | 0x666FD49 | `mov rdx,[rbp+0x600]` | rdx = [rbp+0x600] [V] |
| 4335 | 0x666FD50 | `sub rdx,[rbp+0x5F8]` | rdx -= [rbp+0x5F8] [V] |
| 4336 | 0x666FD57 | `sar rdx,3` | rdx >>= 3 (signed) [V] |
| 4337 | 0x666FD5B | `mov r8,rsi` | r8 = rsi (alloc result) [V] |
| 4338 | 0x666FD5E | `call 0x76B30` | call 0x76B30 [V] |
| 4339 | 0x666FD63 | `nop` | — |
| 4340 | 0x666FD64 | `mov r14,[rbp+0x5E8]` | r14 = list head/sentinel [V] |
| 4341 | 0x666FD6B | `mov r12,[r14]` | **[r14] qword → r12; r12 reused as list walker [V]** |
| 4342 | 0x666FD6E | `cmp r12,r14` | list-empty check [V] |
| 4343 | 0x666FD71 | `je short 0x666FDAA` | branch exit 0x666FDAA [V] |
| 4344 | 0x666FD73 | `lea rsi,[rbp+0x300]` | rsi = stack work addr [V] |
| 4345 | 0x666FD7A | `lea rdi,[rbp+0x3F0]` | rdi = stack dest addr [V] |
| 4346 | 0x666FD81 | `nop [rax+rax]` | nop padding [V] |
| 4347 | 0x666FD90 | `lea r8,[r12+0x10]` | r8 = walker+0x10 [V] |
| 4348 | 0x666FD95 | `mov rcx,rsi` | rcx = work addr [V] |
| 4349 | 0x666FD98 | `mov rdx,rdi` | rdx = dest addr [V] |
| 4350 | 0x666FD9B | `call 0xAA840` | call 0xAA840 per list element [V] |
| 4351 | 0x666FDA0 | `nop` | — |
| 4352 | 0x666FDA1 | `mov r12,[r12]` | **[r12] qword → r12: advance to next list node [V]** |
| 4353 | 0x666FDA5 | `cmp r12,r14` | vs sentinel [V] |
| 4354 | 0x666FDA8 | `jne short 0x666FD90` | branch exit 0x666FD90 (loop) [V] |
| 4355 | 0x666FDAA | `cmp qword ptr [0x129F9240],0x10` | global compare again [V] |
| 4356 | 0x666FDB2 | `jb short 0x666FDBD` | branch exit 0x666FDBD [V] |
| 4357 | 0x666FDB4 | `mov rax,[0x129F9228]` | rax = global pointer [V] |
| 4358 | 0x666FDBB | `jmp short 0x666FDC4` | branch exit 0x666FDC4 [V] |
| 4359 | 0x666FDBD | `lea rax,[0x129F9228]` | rax = address of global [V] |
| 4360 | 0x666FDC4 | `mov r14,[rbp+0x650]` | r14 = object pointer [V] |
| 4361 | 0x666FDCB | `mov rsi,rbx` | rsi = rbx [V] |
| 4362 | 0x666FDCE | `mov rbx,[rbp+0x660]` | rbx = stack slot [V] |
| 4363 | 0x666FDD5 | `mov rcx,[0x129F9238]` | rcx = global [V] |
| 4364 | 0x666FDDC | `mov [rbp+0x630],rax` | store rax [V] |
| 4365 | 0x666FDE3 | `mov [rbp+0x638],rcx` | store rcx [V] |
| 4366 | 0x666FDEA | `mov rcx,rbp` | rcx = rbp [V] |
| 4367 | 0x666FDED | `lea rdx,[rbp+0x630]` | rdx = stack addr [V] |
| 4368 | 0x666FDF4 | `lea r8,[rbp+0x300]` | r8 = stack addr [V] |
| 4369 | 0x666FDFB | `call 0x66A02D0` | call 0x66A02D0 [V] |
| 4370 | 0x666FE00 | `nop` | — |
| 4371 | 0x666FE01 | `mov [rbp+0x3F0],r13` | store r13 [V] |
| 4372 | 0x666FE08 | `mov [rbp+0x3F8],rbx` | store rbx [V] |

**Branch exits:** 0x666FDAA (4343), 0x666FD90 (4354, loop back), 0x666FDBD (4356), 0x666FDC4 (4358). Calls: 0x76B30 (4338), 0xAA840 (4350), 0x66A02D0 (4369). r12 is a list walker here, not the description pointer [I].

## Block 4 — listing lines 4373..4412 (40 lines)

### lines 4373..4412 (0x666FE0F..0x666FEAF)
Sets up args ([rbp+0x5E0], [rbp+0x3F0], [rbp+0x5C0]...) and calls 0x67CFD80, then walks/frees an rsi chain: test rbx, if [rbx+0x10]==1 jump 0x666FF60; incref [rax+8] where rax=[rsi+8], walk [rsi] chain with release calls to qword ptr [0xF99FFA0] [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4373 | 0x666FE0F | `lea rax,[rbp+0x5E0]` | rax = stack addr [V] |
| 4374 | 0x666FE16 | `mov [rsp+0x28],rax` | store arg [V] |
| 4375 | 0x666FE1B | `lea rax,[rbp+0x3F0]` | rax = stack addr [V] |
| 4376 | 0x666FE22 | `mov [rsp+0x20],rax` | store arg [V] |
| 4377 | 0x666FE27 | `lea rdx,[rbp+0x5C0]` | rdx = stack addr [V] |
| 4378 | 0x666FE2E | `mov r8,rbp` | r8 = rbp [V] |
| 4379 | 0x666FE31 | `mov rcx,r15` | rcx = r15 [V] |
| 4380 | 0x666FE34 | `mov r9,rsi` | r9 = rsi [V] |
| 4381 | 0x666FE37 | `call 0x67CFD80` | call 0x67CFD80 [V] |
| 4382 | 0x666FE3C | `nop` | — |
| 4383 | 0x666FE3D | `lea rdi,[rbp+0x5F8]` | rdi = stack addr [V] |
| 4384 | 0x666FE44 | `mov rsi,[rbp+0x5C0]` | rsi = chain head [V] |
| 4385 | 0x666FE4B | `mov rbx,[rsi]` | rbx = [rsi] qword [V] |
| 4386 | 0x666FE4E | `test rbx,rbx` | test rbx [V] |
| 4387 | 0x666FE51 | `mov r12,[rbp+0x648]` | r12 = stack/object slot [V] |
| 4388 | 0x666FE58 | `je 0x666FF60` | branch exit 0x666FF60 [V] |
| 4389 | 0x666FE5E | `mov eax,[0x129CA5E0]` | eax = global dword [V] |
| 4390 | 0x666FE64 | `mov ecx,[0x128767C8]` | ecx = global dword [V] |
| 4391 | 0x666FE6A | `mov rdx,gs:[0x58]` | rdx = GS:0x58 (TEB) [V] |
| 4392 | 0x666FE73 | `mov rcx,[rdx+rcx*8]` | rcx = table entry [V] |
| 4393 | 0x666FE77 | `cmp eax,[rcx+4]` | compare [V] |
| 4394 | 0x666FE7D | `jg 0x66710A5` | branch exit 0x66710A5 [V] |
| 4395 | 0x666FE83 | `cmp byte ptr [rbx+0x10],1` | [rbx+0x10] byte vs 1 [V] |
| 4396 | 0x666FE87 | `jne 0x666FF60` | branch exit 0x666FF60 [V] |
| 4397 | 0x666FE8D | `mov rax,[rsi+8]` | rax = [rsi+8] qword [V] |
| 4398 | 0x666FE91 | `test rax,rax` | test rax [V] |
| 4399 | 0x666FE94 | `je short 0x666FEDA` | branch exit 0x666FEDA [V] |
| 4400 | 0x666FE96 | `lock inc dword ptr [rax+8]` | [rax+8] dword++ (incref) [V] |
| 4401 | 0x666FE9A | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4402 | 0x666FE9D | `mov rsi,[rsi+8]` | rsi = [rsi+8] (advance chain) [V] |
| 4403 | 0x666FEA1 | `mov rax,[rax+0x18]` | rax = [rax+0x18] [V] |
| 4404 | 0x666FEA5 | `mov rbx,[rax]` | rbx = [rax] [V] |
| 4405 | 0x666FEA8 | `test rsi,rsi` | test rsi [V] |
| 4406 | 0x666FEAB | `je short 0x666FEE4` | branch exit 0x666FEE4 [V] |
| 4407 | 0x666FEAD | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- (release) [V] |
| 4408 | 0x666FEB1 | `jne short 0x666FEE4` | branch exit 0x666FEE4 [V] |
| 4409 | 0x666FEB3 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4410 | 0x666FEB6 | `mov rax,[rax]` | rax = [rax] vtable [V] |
| 4411 | 0x666FEB9 | `mov rcx,rsi` | rcx = rsi [V] |
| 4412 | 0x666FEBC | `call qword ptr [0xF99FFA0]` | indirect release call [V] |

**Branch exits:** 0x666FF60 (4388, 4396), 0x66710A5 (4394), 0x666FEDA (4399), 0x666FEE4 (4406, 4408). Calls: 0x67CFD80 (4381), qword ptr [0xF99FFA0] (4412). No description reads.

## Block 5 — listing lines 4413..4452 (40 lines)

### lines 4413..4452 (0x666FEC2..0x666FF67)
Continuation of the chain-release loop: second release path at 0x666FEC2, then decref/dispose of rsi, test rbx==0 → 0x666FF60; incref [rcx+8] where rcx=[rax+8], copy [rax] to [rbp+0x3F0], release old rsi chain, jmp 0x6670071 [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4413 | 0x666FEC2 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- (release) [V] |
| 4414 | 0x666FEC6 | `jne short 0x666FEE4` | branch exit 0x666FEE4 [V] |
| 4415 | 0x666FEC8 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4416 | 0x666FECB | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 4417 | 0x666FECF | `mov rcx,rsi` | rcx = rsi [V] |
| 4418 | 0x666FED2 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4419 | 0x666FED8 | `jmp short 0x666FEE4` | branch exit 0x666FEE4 [V] |
| 4420 | 0x666FEDA | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4421 | 0x666FEDD | `mov rax,[rax+0x18]` | rax = [rax+0x18] [V] |
| 4422 | 0x666FEE1 | `mov rbx,[rax]` | rbx = [rax] [V] |
| 4423 | 0x666FEE4 | `test rbx,rbx` | test rbx [V] |
| 4424 | 0x666FEE7 | `je short 0x666FF60` | branch exit 0x666FF60 [V] |
| 4425 | 0x666FEE9 | `mov rbx,[r14]` | rbx = [r14] [V] |
| 4426 | 0x666FEEC | `mov rax,[rbp+0x5C0]` | rax = stack object [V] |
| 4427 | 0x666FEF3 | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 4428 | 0x666FEF6 | `movaps [rbp+0x3F0],xmm0` | clear slot [rbp+0x3F0] [V] |
| 4429 | 0x666FEFD | `mov rcx,[rax+8]` | rcx = [rax+8] qword [V] |
| 4430 | 0x666FF01 | `test rcx,rcx` | test rcx [V] |
| 4431 | 0x666FF04 | `je 0x667005C` | branch exit 0x667005C [V] |
| 4432 | 0x666FF0A | `lock inc dword ptr [rcx+8]` | [rcx+8] dword++ (incref) [V] |
| 4433 | 0x666FF0E | `mov rsi,[rbp+0x3F8]` | rsi = old value [V] |
| 4434 | 0x666FF15 | `movups xmm0,[rax]` | xmm0 = [rax] 16 bytes [V] |
| 4435 | 0x666FF18 | `movaps [rbp+0x3F0],xmm0` | install new value [V] |
| 4436 | 0x666FF1F | `test rsi,rsi` | test old [V] |
| 4437 | 0x666FF22 | `je 0x6670071` | branch exit 0x6670071 [V] |
| 4438 | 0x666FF28 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 4439 | 0x666FF2C | `jne 0x6670071` | branch exit 0x6670071 [V] |
| 4440 | 0x666FF32 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4441 | 0x666FF35 | `mov rax,[rax]` | rax = [rax] [V] |
| 4442 | 0x666FF38 | `mov rcx,rsi` | rcx = rsi [V] |
| 4443 | 0x666FF3B | `call qword ptr [0xF99FFA0]` | indirect release [V] |
| 4444 | 0x666FF41 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 4445 | 0x666FF45 | `jne 0x6670071` | branch exit 0x6670071 [V] |
| 4446 | 0x666FF4B | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4447 | 0x666FF4E | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 4448 | 0x666FF52 | `mov rcx,rsi` | rcx = rsi [V] |
| 4449 | 0x666FF55 | `call qword ptr [0xF99FFA0]` | indirect release [V] |
| 4450 | 0x666FF5B | `jmp 0x6670071` | branch exit 0x6670071 [V] |
| 4451 | 0x666FF60 | `mov rsi,[rbp+0x5C8]` | rsi = stack slot [V] |
| 4452 | 0x666FF67 | `test rsi,rsi` | test rsi [V] |

**Branch exits:** 0x666FEE4 (4414, 4419), 0x666FF60 (4424), 0x667005C (4431), 0x6670071 (4437, 4439, 4445, 4450). Calls: qword ptr [0xF99FFA0] (4418, 4443, 4449). No description reads.

## Block 6 — listing lines 4453..4492 (40 lines)

### lines 4453..4492 (0x666FF97..0x6670000)
Release-tail of the rsi chain (second decref/dispose path), then guard-checked free of [rbp+0x5F8] region via call 0xE935700, clear [rdi], and walk the [rbp+0x5E8] list freeing each node (call 0x9B250 then call 0xE935700 with 0x50 size) [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4453 | 0x666FF97 | `je short 0x666FF97` | branch exit 0x666FF97 (self-loop target from earlier je) [V] |
| 4454 | 0x666FF6C | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 4455 | 0x666FF70 | `jne short 0x666FF97` | branch exit 0x666FF97 [V] |
| 4456 | 0x666FF72 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4457 | 0x666FF75 | `mov rax,[rax]` | rax = [rax] vtable [V] |
| 4458 | 0x666FF78 | `mov rcx,rsi` | rcx = rsi [V] |
| 4459 | 0x666FF7B | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4460 | 0x666FF81 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 4461 | 0x666FF85 | `jne short 0x666FF97` | branch exit 0x666FF97 [V] |
| 4462 | 0x666FF87 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4463 | 0x666FF8A | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 4464 | 0x666FF8E | `mov rcx,rsi` | rcx = rsi [V] |
| 4465 | 0x666FF91 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4466 | 0x666FF97 | `mov rcx,[rbp+0x5F8]` | rcx = stack slot [V] |
| 4467 | 0x666FF9E | `test rcx,rcx` | test rcx [V] |
| 4468 | 0x666FFA1 | `je short 0x666FFE5` | branch exit 0x666FFE5 [V] |
| 4469 | 0x666FFA3 | `mov rdx,[rbp+0x608]` | rdx = end pointer [V] |
| 4470 | 0x666FFAA | `sub rdx,rcx` | size computation [V] |
| 4471 | 0x666FFAD | `cmp rdx,0x1000` | guard vs 0x1000 [V] |
| 4472 | 0x666FFB4 | `jb short 0x666FFD2` | branch exit 0x666FFD2 [V] |
| 4473 | 0x666FFB6 | `mov rax,[rcx-8]` | [rcx-8] qword → rax [V] |
| 4474 | 0x666FFBA | `add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 [V] |
| 4475 | 0x666FFBE | `sub rcx,rax` | rcx -= rax [V] |
| 4476 | 0x666FFC1 | `cmp rcx,0x20` | compare vs 0x20 [V] |
| 4477 | 0x666FFC5 | `jae 0x6670A7A` | branch exit 0x6670A7A [V] |
| 4478 | 0x666FFCB | `add rdx,0x27` | rdx += 0x27 [V] |
| 4479 | 0x666FFCF | `mov rcx,rax` | rcx = rax [V] |
| 4480 | 0x666FFD2 | `call 0xE935700` | call 0xE935700 (free) [V] |
| 4481 | 0x666FFD7 | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 4482 | 0x666FFDA | `movups [rdi],xmm0` | clear 16 bytes at [rdi] [V] |
| 4483 | 0x666FFDD | `mov qword ptr [rdi+0x10],0` | clear [rdi+0x10] [V] |
| 4484 | 0x666FFE5 | `mov rax,[rbp+0x5E8]` | rax = list head [V] |
| 4485 | 0x666FFEC | `mov rcx,[rax+8]` | rcx = [rax+8] qword [V] |
| 4486 | 0x666FFF0 | `mov qword ptr [rcx],0` | clear forward link [V] |
| 4487 | 0x666FFF7 | `mov rsi,[rax]` | rsi = next node [V] |
| 4488 | 0x666FFFA | `test rsi,rsi` | test rsi [V] |
| 4489 | 0x666FFFD | `je short 0x6670021` | branch exit 0x6670021 [V] |
| 4490 | 0x666FFFF | `nop` | — |
| 4491 | 0x6670000 | `mov rdi,[rsi]` | rdi = [rsi] [V] |
| 4492 | 0x6670003 | `lea rcx,[rsi+0x10]` | rcx = node+0x10 [V] |

**Branch exits:** 0x666FF97 (4453, 4455, 4461), 0x666FFE5 (4468), 0x666FFD2 (4472), 0x6670A7A (4477), 0x6670021 (4489). Calls: qword ptr [0xF99FFA0] (4459, 4465), 0xE935700 (4480), 0x9B250 (4493, next block). No description reads.

## Block 7 — listing lines 4493..4532 (40 lines)

### lines 4493..4532 (0x6670007..0x66700B1)
List-free loop completes (call 0x9B250 + 0xE935700 per node), then FUNCTION EPILOGUE at 0x6670032 — the exact target of the tag-7 body epilogue jump `jmp 0x6670032` at listing line 4252 [V]: restores xmm6-xmm8, `add rsp,0x738`, pops rbx/rdi/rsi/r12/r13/r14/r15/rbp, `ret` at 0x667005B (line 4515). Cold path 0x667005C (line 4516) re-derives [rbp+0x3F0] and joins flow at 0x6670071 → call 0xE86B370 → release chain to 0x66700DE [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4493 | 0x6670007 | `call 0x9B250` | call 0x9B250 (free helper) [V] |
| 4494 | 0x667000C | `mov edx,0x50` | edx = 0x50 [V] |
| 4495 | 0x6670011 | `mov rcx,rsi` | rcx = rsi [V] |
| 4496 | 0x6670014 | `call 0xE935700` | call 0xE935700 (free) [V] |
| 4497 | 0x6670019 | `mov rsi,rdi` | rsi = rdi (next node) [V] |
| 4498 | 0x667001C | `test rdi,rdi` | test rdi [V] |
| 4499 | 0x667001F | `jne short 0x6670000` | branch exit 0x6670000 (loop) [V] |
| 4500 | 0x6670021 | `mov rcx,[rbp+0x5E8]` | rcx = list head [V] |
| 4501 | 0x6670028 | `mov edx,0x50` | edx = 0x50 [V] |
| 4502 | 0x667002D | `call 0xE935700` | call 0xE935700 (free head) [V] |
| 4503 | 0x6670032 | `movaps xmm6,[rbp+0x680]` | **EPILOGUE START — target of tag-7 body exit jump at line 4252 [V]** |
| 4504 | 0x6670039 | `movaps xmm7,[rbp+0x690]` | restore xmm7 [V] |
| 4505 | 0x6670040 | `movaps xmm8,[rbp+0x6A0]` | restore xmm8 [V] |
| 4506 | 0x6670048 | `add rsp,0x738` | deallocate stack frame [V] |
| 4507 | 0x667004F | `pop rbx` | — |
| 4508 | 0x6670050 | `pop rdi` | — |
| 4509 | 0x6670051 | `pop rsi` | — |
| 4510 | 0x6670052 | `pop r12` | — |
| 4511 | 0x6670054 | `pop r13` | — |
| 4512 | 0x6670056 | `pop r14` | — |
| 4513 | 0x6670058 | `pop r15` | — |
| 4514 | 0x667005A | `pop rbp` | — |
| 4515 | 0x667005B | `ret` | function return [V] |
| 4516 | 0x667005C | `mov rax,[rax]` | cold path 0x667005C: reload [rax] [V] |
| 4517 | 0x667005F | `mov [rbp+0x3F0],rax` | install [rbp+0x3F0] [V] |
| 4518 | 0x6670066 | `mov qword ptr [rbp+0x3F8],0` | clear slot [V] |
| 4519 | 0x6670071 | `mov rax,[rbp+0x3F0]` | cold-path join 0x6670071 [V] |
| 4520 | 0x6670078 | `mov rax,[rax+0x18]` | [rax+0x18] qword → rax [V] |
| 4521 | 0x667007C | `mov rax,[rax]` | rax = [rax] [V] |
| 4522 | 0x667007F | `mov [rbp+0x1D0],rax` | store [V] |
| 4523 | 0x6670086 | `lea r15,[rbp+0x1D8]` | r15 = stack addr [V] |
| 4524 | 0x667008D | `mov r8,[rbx]` | r8 = [rbx] [V] |
| 4525 | 0x6670090 | `mov rdx,[rax+0x170]` | [rax+0x170] qword → rdx [V] |
| 4526 | 0x6670097 | `mov rcx,r15` | rcx = r15 [V] |
| 4527 | 0x667009A | `call 0xE86B370` | call 0xE86B370 [V] |
| 4528 | 0x667009F | `nop` | — |
| 4529 | 0x66700A0 | `mov [rbp+0x250],rbx` | store rbx [V] |
| 4530 | 0x66700A7 | `mov rsi,[rbp+0x3F8]` | rsi = chain object [V] |
| 4531 | 0x66700AE | `test rsi,rsi` | test rsi [V] |
| 4532 | 0x66700B1 | `je short 0x66700DE` | branch exit 0x66700DE [V] |

**Branch exits:** 0x6670000 (4499), 0x66700DE (4532). **Epilogue:** entry 0x6670032 (line 4503), ret 0x667005B (line 4515). Calls: 0x9B250 (4493), 0xE935700 (4496, 4502), 0xE86B370 (4527). No description reads.

## Block 8 — listing lines 4533..4572 (40 lines)

### lines 4533..4572 (0x66700B3..0x6670166)
Release chain finishes at cold path 0x66700DE; security-check style compare `eax=[0x129F92A0]` vs `[gs:[0x58]+rcx*8+4]` with `jg 0x667110F` [V]; then STRING DISPATCH: rsi=[r12+0x100], bounds-checked string compare against pointers at 0xF536687 then 0xF5366A7 via call 0xEEC6EB0 — pattern matches other-tag case entry (string-id dispatch) inside this range [I], though no jump-table entry edge is visible here.

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4533 | 0x66700B3 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 4534 | 0x66700B7 | `jne short 0x66700DE` | branch exit 0x66700DE [V] |
| 4535 | 0x66700B9 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4536 | 0x66700BC | `mov rax,[rax]` | rax = [rax] [V] |
| 4537 | 0x66700BF | `mov rcx,rsi` | rcx = rsi [V] |
| 4538 | 0x66700C2 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4539 | 0x66700C8 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 4540 | 0x66700CC | `jne short 0x66700DE` | branch exit 0x66700DE [V] |
| 4541 | 0x66700CE | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4542 | 0x66700D1 | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 4543 | 0x66700D5 | `mov rcx,rsi` | rcx = rsi [V] |
| 4544 | 0x66700D8 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4545 | 0x66700DE | `mov eax,[0x129F92A0]` | eax = global dword [V] |
| 4546 | 0x66700E4 | `mov ecx,[0x128767C8]` | ecx = global dword [V] |
| 4547 | 0x66700EA | `mov rdx,gs:[0x58]` | rdx = GS:0x58 (TEB) [V] |
| 4548 | 0x66700F3 | `mov rcx,[rdx+rcx*8]` | rcx = table slot [V] |
| 4549 | 0x66700F7 | `cmp eax,[rcx+4]` | compare [rcx+4] with eax [V] |
| 4550 | 0x66700FD | `jg 0x667110F` | branch exit 0x667110F [V] |
| 4551 | 0x6670103 | `mov rsi,[r12+0x100]` | rsi = [r12+0x100] qword (string candidate) [V] |
| 4552 | 0x667010B | `cmp qword ptr [r12+0x108],0x10` | size/local check [V] |
| 4553 | 0x6670114 | `jb short 0x6670120` | branch exit 0x6670120 [V] |
| 4554 | 0x6670116 | `mov r12,[r12+0xF0]` | r12 = [r12+0xF0] (small-string inline ptr) [V] |
| 4555 | 0x667011E | `jmp short 0x6670127` | branch exit 0x6670127 [V] |
| 4556 | 0x6670120 | `add r12,0xF0` | r12 += 0xF0 [V] |
| 4557 | 0x6670127 | `cmp rsi,0x1F` | rsi length vs 0x1F [V] |
| 4558 | 0x667012B | `mov r8d,0x1F` | r8d = 0x1F [V] |
| 4559 | 0x6670131 | `cmovb r8,rsi` | r8 = min(rsi,0x1F) [V] |
| 4560 | 0x6670135 | `lea rdx,[0xF536687]` | rdx = string pointer 0xF536687 [V] |
| 4561 | 0x667013C | `mov rcx,r12` | rcx = candidate string [V] |
| 4562 | 0x667013F | `call 0xEEC6EB0` | call 0xEEC6EB0 (string compare) [V] |
| 4563 | 0x6670144 | `cmp rsi,0x1F` | [V] |
| 4564 | 0x6670148 | `jne short 0x667014E` | branch exit 0x667014E [V] |
| 4565 | 0x667014A | `test eax,eax` | compare result test [V] |
| 4566 | 0x667014C | `je short 0x667017D` | branch exit 0x667017D (match) [V] |
| 4567 | 0x667014E | `cmp rsi,0x1E` | [V] |
| 4568 | 0x6670152 | `mov r8d,0x1E` | r8d = 0x1E [V] |
| 4569 | 0x6670158 | `cmovb r8,rsi` | r8 = min(rsi,0x1E) [V] |
| 4570 | 0x667015C | `lea rdx,[0xF5366A7]` | rdx = string pointer 0xF5366A7 [V] |
| 4571 | 0x6670163 | `mov rcx,r12` | rcx = candidate string [V] |
| 4572 | 0x6670166 | `call 0xEEC6EB0` | call 0xEEC6EB0 (string compare) [V] |

**Branch exits:** 0x66700DE (4534, 4540), 0x667110F (4550), 0x6670120 (4553), 0x6670127 (4555), 0x667014E (4564), 0x667017D (4566). Calls: qword ptr [0xF99FFA0] (4538, 4544), 0xEEC6EB0 (4562, 4572). The string compares at 0xF536687 / 0xF5366A7 indicate other-tag case dispatch begins in this vicinity [I]; no jump-table entry edge visible in this range.

## Block 9 — listing lines 4573..4612 (40 lines)

### lines 4573..4612 (0x667016B..0x667020F)
String-compare results: on match jump 0x667020F; otherwise compute index `(rcx-rdx)>>4` → [rbp+0x340], set [rbp+0x342]=1, call 0x5679DB0; then fall to second dispatch at 0x667020F [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4573 | 0x667016B | `cmp rsi,0x1E` | compare length [V] |
| 4574 | 0x667016F | `jne 0x667020F` | branch exit 0x667020F [V] |
| 4575 | 0x6670175 | `test eax,eax` | compare result [V] |
| 4576 | 0x6670177 | `jne 0x667020F` | branch exit 0x667020F [V] |
| 4577 | 0x667017D | `mov rax,[rbp+0x668]` | rax = object [V] (match path: second string matched) |
| 4578 | 0x6670184 | `movups xmm0,[rax+0x64]` | [rax+0x64] 16 bytes → xmm0 [V] |
| 4579 | 0x6670188 | `movaps [rbp+0x3F0],xmm0` | store [V] |
| 4580 | 0x667018F | `mov qword ptr [rbp],1` | flag = 1 [V] |
| 4581 | 0x6670197 | `lea rax,[rbp+0x3F0]` | rax = stack addr [V] |
| 4582 | 0x667019E | `mov [rbp+8],rax` | store arg [V] |
| 4583 | 0x66701A2 | `mov rax,[rbp+0x208]` | table base [V] |
| 4584 | 0x66701A9 | `movzx r8d,word ptr [rbp+0x212]` | count [V] |
| 4585 | 0x66701B1 | `mov edx,r8d` | — |
| 4586 | 0x66701B4 | `shl edx,4` | — |
| 4587 | 0x66701B7 | `mov rcx,rax` | — |
| 4588 | 0x66701BA | `test r8d,r8d` | count == 0? [V] |
| 4589 | 0x66701BD | `je short 0x66701E1` | branch exit 0x66701E1 [V] |
| 4590 | 0x66701BF | `mov r8,[0x129F9298]` | r8 = global string pointer [V] |
| 4591 | 0x66701C6 | `mov r9,rdx` | — |
| 4592 | 0x66701C9 | `mov rcx,rax` | — |
| 4593 | 0x66701CC | `mov r10,[rcx]` | r10 = [rcx] [V] |
| 4594 | 0x66701CF | `cmp [r10+0x28],r8` | compare with global string [V] |
| 4595 | 0x66701D3 | `je short 0x66701E1` | branch exit 0x66701E1 [V] |
| 4596 | 0x66701D5 | `add rcx,0x10` | next entry [V] |
| 4597 | 0x66701D9 | `add r9,0xFFFFFFFFFFFFFFF0` | end -= 16 [V] |
| 4598 | 0x66701DD | `jne short 0x66701CC` | branch exit 0x66701CC (loop) [V] |
| 4599 | 0x66701DF | `jmp short 0x667020F` | branch exit 0x667020F [V] |
| 4600 | 0x66701E1 | `add rdx,rax` | rdx = end addr [V] |
| 4601 | 0x66701E4 | `cmp rcx,rdx` | walker vs end [V] |
| 4602 | 0x66701E7 | `jae short 0x667020F` | branch exit 0x667020F [V] |
| 4603 | 0x66701E9 | `sub ecx,eax` | index computation [V] |
| 4604 | 0x66701EB | `shr ecx,4` | index >>= 4 [V] |
| 4605 | 0x66701EE | `mov [rbp+0x340],cx` | store index [V] |
| 4606 | 0x66701F5 | `mov byte ptr [rbp+0x342],1` | set flag [V] |
| 4607 | 0x66701FC | `lea rdx,[rbp+0x340]` | rdx = arg [V] |
| 4608 | 0x6670203 | `mov r8,rbp` | r8 = rbp [V] |
| 4609 | 0x6670206 | `mov rcx,r15` | rcx = r15 [V] |
| 4610 | 0x6670209 | `call 0x5679DB0` | call 0x5679DB0 [V] |
| 4611 | 0x667020E | `nop` | — |
| 4612 | 0x667020F | `mov rax,[rbp+0x218]` | second table base [V] |

**Branch exits:** 0x667020F (4574, 4576, 4599, 4602), 0x66701E1 (4589, 4595), 0x66701CC (4598). Calls: 0x5679DB0 (4610). No description reads.

## Block 10 — listing lines 4613..4652 (40 lines)

### lines 4613..4652 (0x6670218..0x66702BF)
Second dispatch: identical string-compare/index pattern (global 0x129F8318, stride 0x30), then store results to [rbp]/[rbp+0x3F8]/[rbp+0x3F0], set [rbp+0x3FC]=1, call 0xBCABA00; ends at line 4652 `mov r9,[rax]` mid-sequence [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4613 | 0x6670218 | `movzx r8d,word ptr [rbp+0x222]` | count [V] |
| 4614 | 0x667021E | `mov ecx,r8d` | — |
| 4615 | 0x6670221 | `shl ecx,4` | — |
| 4616 | 0x6670224 | `lea rdx,[rcx+rcx*2]` | rdx = count*48 (end) [V] |
| 4617 | 0x6670228 | `mov rcx,rax` | walker = table base [V] |
| 4618 | 0x667022B | `test r8,r8` | count == 0? [V] |
| 4619 | 0x667022E | `je short 0x6670252` | branch exit 0x6670252 [V] |
| 4620 | 0x6670230 | `mov r8,[0x129F8318]` | r8 = global string pointer [V] |
| 4621 | 0x6670237 | `mov r9,rdx` | — |
| 4622 | 0x667023A | `mov rcx,rax` | — |
| 4623 | 0x667023D | `mov r10,[rcx]` | r10 = [rcx] [V] |
| 4624 | 0x6670240 | `cmp [r10+0x28],r8` | compare with global string [V] |
| 4625 | 0x6670244 | `je short 0x6670252` | branch exit 0x6670252 [V] |
| 4626 | 0x6670246 | `add rcx,0x30` | next entry [V] |
| 4627 | 0x667024A | `add r9,0xFFFFFFFFFFFFFFD0` | end -= 48 [V] |
| 4628 | 0x667024E | `jne short 0x667023D` | branch exit 0x667023D (loop) [V] |
| 4629 | 0x6670250 | `jmp short 0x66702B8` | branch exit 0x66702B8 [V] |
| 4630 | 0x6670252 | `add rdx,rax` | rdx = end addr [V] |
| 4631 | 0x6670255 | `cmp rcx,rdx` | walker vs end [V] |
| 4632 | 0x6670258 | `jae short 0x66702B8` | branch exit 0x66702B8 [V] |
| 4633 | 0x667025A | `mov rdx,[rbp+0x668]` | rdx = object [V] |
| 4634 | 0x6670261 | `lea r8,[rdx+8]` | r8 = object+8 [V] |
| 4635 | 0x6670265 | `sub ecx,eax` | index computation [V] |
| 4636 | 0x6670267 | `shr ecx,4` | index >>= 4 [V] |
| 4637 | 0x667026A | `imul eax,ecx,0xFFFFAAAB` | magic multiply [V] |
| 4638 | 0x6670270 | `mov [rbp],ax` | store index [V] |
| 4639 | 0x6670274 | `mov byte ptr [rbp+2],1` | flag = 1 [V] |
| 4640 | 0x6670278 | `mov eax,[rbp+0x3E8]` | eax = dword [V] |
| 4641 | 0x667027E | `mov [rbp+0x3F8],eax` | store [V] |
| 4642 | 0x6670284 | `mov rax,[rbp+0x3E0]` | rax = qword [V] |
| 4643 | 0x667028B | `mov [rbp+0x3F0],rax` | store [V] |
| 4644 | 0x6670292 | `mov byte ptr [rbp+0x3FC],1` | flag = 1 [V] |
| 4645 | 0x6670299 | `mov dword ptr [rsp+0x20],0` | clear stack [V] |
| 4646 | 0x66702A1 | `lea rcx,[rbp+0x1D0]` | rcx = arg [V] |
| 4647 | 0x66702A8 | `mov rdx,rbp` | rdx = rbp [V] |
| 4648 | 0x66702AB | `lea r9,[rbp+0x3F0]` | r9 = arg [V] |
| 4649 | 0x66702B2 | `call 0xBCABA00` | call 0xBCABA00 [V] |
| 4650 | 0x66702B7 | `nop` | — |
| 4651 | 0x66702B8 | `mov rax,[rbp+0x668]` | rax = object [V] |
| 4652 | 0x66702BF | `mov r9,[rax]` | r9 = [rax] (sequence continues past line 4652) [V] |

**Branch exits:** 0x6670252 (4619, 4625), 0x667023D (4628), 0x66702B8 (4629, 4632). Calls: 0xBCABA00 (4649). No description reads.

## Block 11 — listing lines 4653..4692 (40 lines)

### lines 4653..4692 (0x66702C2..0x6670385)
Post-dispatch work: call 0xBBD7F70 with stack args, then `cmp byte ptr [rbp+0x398],1 / jne 0x66706A8` — jump to hub 0x66706A8 if flag not set (multi-entry hub, target of branches at lines 4828/4849 as well) [V]. Otherwise zero [rbp+0x1D0..] via 0xEEC6ED0 (0x1C0 bytes), call 0x66E5C50, store [rbp+0x1D0] to [rbp+0x3F0], call 0xE869FF0, load rsi=[rbp+0x668] object, branch on [rbp+0x158] byte (jne 0x6670382) calling 0xE86A0D0 vs 0xE869FF0, both storing [rbp+0x470] to [rbp+0x150] and joining at 0x66703A0 [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4653 | 0x66702C2 | `lea rcx,[rbp+0x340]` | rcx = arg [V] |
| 4654 | 0x66702C9 | `lea r8,[rbp+0x1D0]` | r8 = arg [V] |
| 4655 | 0x66702D0 | `mov rdx,r14` | rdx = r14 [V] |
| 4656 | 0x66702D3 | `call 0xBBD7F70` | call 0xBBD7F70 [V] |
| 4657 | 0x66702D8 | `nop` | — |
| 4658 | 0x66702D9 | `cmp byte ptr [rbp+0x398],1` | flag compare [V] |
| 4659 | 0x66702E0 | `jne 0x66706A8` | **branch exit 0x66706A8 (multi-entry cold hub; also targeted by lines 4828, 4849)** [V] |
| 4660 | 0x66702E6 | `mov rsi,rbp` | rsi = rbp [V] |
| 4661 | 0x66702E9 | `mov r8d,0x1C0` | r8d = 0x1C0 [V] |
| 4662 | 0x66702EF | `mov rcx,rsi` | rcx = rbp [V] |
| 4663 | 0x66702F2 | `xor edx,edx` | edx = 0 [V] |
| 4664 | 0x66702F4 | `call 0xEEC6ED0` | call 0xEEC6ED0 (zero 0x1C0 bytes at rbp) [V] |
| 4665 | 0x66702F9 | `lea rdx,[rbp+0x340]` | rdx = arg [V] |
| 4666 | 0x6670300 | `mov rcx,rsi` | rcx = rsi [V] |
| 4667 | 0x6670303 | `call 0x66E5C50` | call 0x66E5C50 [V] |
| 4668 | 0x6670308 | `mov rax,[rbp+0x1D0]` | rax = qword [V] |
| 4669 | 0x667030F | `mov [rbp+0x3F0],rax` | store [V] |
| 4670 | 0x6670316 | `lea r12,[rbp+0x3F8]` | r12 = stack addr [V] |
| 4671 | 0x667031D | `mov rcx,r12` | rcx = r12 [V] |
| 4672 | 0x6670320 | `mov rdx,r15` | rdx = r15 [V] |
| 4673 | 0x6670323 | `call 0xE869FF0` | call 0xE869FF0 [V] |
| 4674 | 0x6670328 | `nop` | — |
| 4675 | 0x6670329 | `mov rsi,[rbp+0x668]` | rsi = object [V] (not description — [rbp+0x668] local object per prior blocks) |
| 4676 | 0x6670330 | `mov rax,[rbp+0x250]` | rax = qword [V] |
| 4677 | 0x6670337 | `mov [rbp+0x470],rax` | store [V] |
| 4678 | 0x667033E | `mov qword ptr [rbp+0x250],0` | clear [V] |
| 4679 | 0x6670349 | `movzx eax,byte ptr [rbp+0x158]` | al = flag byte [V] |
| 4680 | 0x6670350 | `mov rcx,[rbp+0x3F0]` | rcx = qword [V] |
| 4681 | 0x6670357 | `mov [rbp+0xD0],rcx` | store [V] |
| 4682 | 0x667035E | `lea rcx,[rbp+0xD8]` | rcx = stack addr [V] |
| 4683 | 0x6670365 | `cmp al,1` | flag vs 1 [V] |
| 4684 | 0x6670367 | `jne short 0x6670382` | branch exit 0x6670382 [V] |
| 4685 | 0x6670369 | `mov rdx,r12` | rdx = r12 [V] |
| 4686 | 0x667036C | `call 0xE86A0D0` | call 0xE86A0D0 [V] |
| 4687 | 0x6670371 | `nop` | — |
| 4688 | 0x6670372 | `mov rax,[rbp+0x470]` | rax = qword [V] |
| 4689 | 0x6670379 | `mov [rbp+0x150],rax` | store [V] |
| 4690 | 0x6670380 | `jmp short 0x66703A0` | branch exit 0x66703A0 [V] |
| 4691 | 0x6670382 | `mov rdx,r12` | rdx = r12 [V] |
| 4692 | 0x6670385 | `call 0xE869FF0` | call 0xE869FF0 [V] |

**Branch exits:** 0x66706A8 (4659), 0x6670382 (4684), 0x66703A0 (4690). Calls: 0xBBD7F70 (4656), 0xEEC6ED0 (4664), 0x66E5C50 (4667), 0xE869FF0 (4673, 4692), 0xE86A0D0 (4686). No description reads.

## Block 12 — listing lines 4693..4732 (40 lines)

### lines 4693..4732 (0x667038A..0x6670447)
Merge path at 0x667038A: store [rbp+0x470] to [rbp+0x150], set [rbp+0x158]=1, join at 0x66703A0; then copy object fields [rsi+0x18],[rsi+0x28],[rsi+0x38],[rsi+0x48] to stack slots [rbp+0x3F0]..[rbp+0x420], call 0x66E5DC0, read [rsi+0x88] word, and begin field pack based on flag bytes [rbp+0xC], [rbp+0x78] [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4693 | 0x667038A | `nop` | — |
| 4694 | 0x667038B | `mov rax,[rbp+0x470]` | rax = qword [V] |
| 4695 | 0x6670392 | `mov [rbp+0x150],rax` | store [V] |
| 4696 | 0x6670399 | `mov byte ptr [rbp+0x158],1` | flag = 1 [V] |
| 4697 | 0x66703A0 | `movups xmm0,[rsi+0x18]` | [rsi+0x18] 16 bytes → xmm0 (rsi=[rbp+0x668] object [I]) [V] |
| 4698 | 0x66703A4 | `movaps [rbp+0x3F0],xmm0` | store [V] |
| 4699 | 0x66703AB | `movups xmm0,[rsi+0x28]` | [rsi+0x28] 16 bytes → xmm0 [V] |
| 4700 | 0x66703AF | `movaps [rbp+0x400],xmm0` | store [V] |
| 4701 | 0x66703B6 | `movups xmm0,[rsi+0x38]` | [rsi+0x38] 16 bytes → xmm0 [V] |
| 4702 | 0x66703BA | `movaps [rbp+0x410],xmm0` | store [V] |
| 4703 | 0x66703C1 | `movups xmm0,[rsi+0x48]` | [rsi+0x48] 16 bytes → xmm0 [V] |
| 4704 | 0x66703C5 | `movaps [rbp+0x420],xmm0` | store [V] |
| 4705 | 0x66703CC | `mov byte ptr [rbp+0x430],0` | flag = 0 [V] |
| 4706 | 0x66703D3 | `mov rcx,rbp` | rcx = rbp [V] |
| 4707 | 0x66703D6 | `lea rdx,[rbp+0x3F0]` | rdx = arg [V] |
| 4708 | 0x66703DD | `call 0x66E5DC0` | call 0x66E5DC0 [V] |
| 4709 | 0x66703E2 | `movzx eax,word ptr [rsi+0x88]` | [rsi+0x88] word → eax [V] |
| 4710 | 0x66703E9 | `cmp byte ptr [rbp+0xC],0` | flag byte [V] |
| 4711 | 0x66703ED | `jne short 0x66703F3` | branch exit 0x66703F3 [V] |
| 4712 | 0x66703EF | `mov byte ptr [rbp+0xC],1` | flag = 1 [V] |
| 4713 | 0x66703F3 | `mov [rbp+0xA],ax` | store word [V] |
| 4714 | 0x66703F7 | `mov eax,[rbp+0x2A0]` | eax = dword [V] |
| 4715 | 0x66703FD | `movzx r9d,byte ptr [rbp+0x2A4]` | r9d = byte [V] |
| 4716 | 0x6670405 | `movzx ecx,byte ptr [rbp+0x2B4]` | ecx = byte [V] |
| 4717 | 0x667040C | `movups xmm0,[rbp+0x2B8]` | xmm0 = 16 bytes [V] |
| 4718 | 0x6670413 | `lea r8,[rbp+0x2C8]` | r8 = stack addr [V] |
| 4719 | 0x667041A | `lea rdx,[rbp+0x48]` | rdx = stack addr [V] |
| 4720 | 0x667041E | `cmp byte ptr [rbp+0x78],1` | flag vs 1 [V] |
| 4721 | 0x6670422 | `jne short 0x6670459` | branch exit 0x6670459 [V] |
| 4722 | 0x6670424 | `mov [rbp+0x24],r9b` | store byte [V] |
| 4723 | 0x6670428 | `mov r9d,[rbp+0x2B0]` | r9d = dword [V] |
| 4724 | 0x667042F | `mov [rbp+0x30],r9d` | store dword [V] |
| 4725 | 0x6670433 | `mov r9,[rbp+0x2A8]` | r9 = qword [V] |
| 4726 | 0x667043A | `mov [rbp+0x28],r9` | store qword [V] |
| 4727 | 0x667043E | `movups xmm1,[r8]` | xmm1 = [rbp+0x2C8] [V] |
| 4728 | 0x6670442 | `movups xmm2,[r8+0x10]` | xmm2 = [rbp+0x2D8] [V] |
| 4729 | 0x6670447 | `movups xmm3,[r8+0x1F]` | xmm3 = [rbp+0x2E7] [V] |

**Branch exits:** 0x66703F3 (4711), 0x6670459 (4721). Calls: 0x66E5DC0 (4708). No description reads (rsi=[rbp+0x668] object [I]).

## Block 13 — listing lines 4733..4772 (40 lines)

### lines 4733..4772 (0x667044C..0x66704F8)
Store packed xmm1-3 to [rbp+0x48..], jmp 0x6670490 join; alternate path at 0x6670459 stores bytes/qwords differently, sets [rbp+0x78]=1; join stores eax/cl/xmm0, then float fields [rsi+0x58]/[rsi+0x5C] to [rbp+0x10]/[rbp+0x14], flag bytes [rbp+0x1C],[rbp+9],[rbp+0x430] set to 1; guard check [rbp+0x400]-[rbp+0x3F0] vs 0x1000 then call 0xE935700; jae 0x6670A7A [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4733 | 0x667044C | `movups [rdx],xmm1` | store xmm1 [V] |
| 4734 | 0x667044F | `movups [rdx+0x1F],xmm3` | store xmm3 [V] |
| 4735 | 0x6670453 | `movups [rdx+0x10],xmm2` | store xmm2 [V] |
| 4736 | 0x6670457 | `jmp short 0x6670490` | branch exit 0x6670490 [V] |
| 4737 | 0x6670459 | `mov [rbp+0x24],r9b` | store byte [V] |
| 4738 | 0x667045D | `mov r9,[rbp+0x2A5]` | r9 = qword [V] |
| 4739 | 0x6670464 | `mov r10,[rbp+0x2AC]` | r10 = qword [V] |
| 4740 | 0x667046B | `mov [rbp+0x2C],r10` | store [V] |
| 4741 | 0x667046F | `mov [rbp+0x25],r9` | store [V] |
| 4742 | 0x6670473 | `movups xmm1,[r8]` | xmm1 = [rbp+0x2C8] [V] |
| 4743 | 0x6670477 | `movups xmm2,[r8+0x10]` | xmm2 = [rbp+0x2D8] [V] |
| 4744 | 0x667047C | `movups xmm3,[r8+0x1F]` | xmm3 = [rbp+0x2E7] [V] |
| 4745 | 0x6670481 | `movups [rdx],xmm1` | store xmm1 [V] |
| 4746 | 0x6670484 | `movups [rdx+0x1F],xmm3` | store xmm3 [V] |
| 4747 | 0x6670488 | `movups [rdx+0x10],xmm2` | store xmm2 [V] |
| 4748 | 0x667048C | `mov byte ptr [rbp+0x78],1` | flag = 1 [V] |
| 4749 | 0x6670490 | `mov [rbp+0x20],eax` | store eax [V] |
| 4750 | 0x6670493 | `mov [rbp+0x34],cl` | store byte [V] |
| 4751 | 0x6670496 | `movups [rbp+0x38],xmm0` | store xmm0 [V] |
| 4752 | 0x667049A | `movss xmm1,[rsi+0x58]` | [rsi+0x58] dword → xmm1 (rsi object [I]) [V] |
| 4753 | 0x667049F | `movsd xmm0,[rsi+0x5C]` | [rsi+0x5C] qword → xmm0 [V] |
| 4754 | 0x66704A4 | `movss [rbp+0x10],xmm1` | store [V] |
| 4755 | 0x66704A9 | `cmp byte ptr [rbp+0x1C],0` | flag [V] |
| 4756 | 0x66704AD | `jne short 0x66704B3` | branch exit 0x66704B3 [V] |
| 4757 | 0x66704AF | `mov byte ptr [rbp+0x1C],1` | flag = 1 [V] |
| 4758 | 0x66704B3 | `movlps [rbp+0x14],xmm0` | store lo qword [V] |
| 4759 | 0x66704B7 | `cmp byte ptr [rbp+9],0` | flag [V] |
| 4760 | 0x66704BB | `jne short 0x66704C1` | branch exit 0x66704C1 [V] |
| 4761 | 0x66704BD | `mov byte ptr [rbp+9],1` | flag = 1 [V] |
| 4762 | 0x66704C1 | `cmp byte ptr [rbp+0x430],1` | flag vs 1 [V] |
| 4763 | 0x66704C8 | `jne short 0x667050A` | branch exit 0x667050A [V] |
| 4764 | 0x66704CA | `mov rcx,[rbp+0x3F0]` | rcx = qword [V] |
| 4765 | 0x66704D1 | `test rcx,rcx` | test rcx [V] |
| 4766 | 0x66704D4 | `je short 0x667050A` | branch exit 0x667050A [V] |
| 4767 | 0x66704D6 | `mov rdx,[rbp+0x400]` | rdx = end [V] |
| 4768 | 0x66704DD | `sub rdx,rcx` | size [V] |
| 4769 | 0x66704E0 | `cmp rdx,0x1000` | guard vs 0x1000 [V] |
| 4770 | 0x66704E7 | `jb short 0x6670505` | branch exit 0x6670505 [V] |
| 4771 | 0x66704E9 | `mov rax,[rcx-8]` | [rcx-8] qword → rax [V] |
| 4772 | 0x66704ED | `add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 [V] |

**Branch exits:** 0x6670490 (4736), 0x66704B3 (4756), 0x66704C1 (4760), 0x667050A (4763, 4766), 0x6670505 (4770), 0x6670A7A (4772, next line). Calls: none directly; 0xE935700 at line 4775 (next block). No description reads.

## Block 14 — listing lines 4773..4812 (40 lines)

### lines 4773..4812 (0x66704FE..0x66705AA)
Free call 0xE935700, then flag byte chain ([rbp+0x670]==1? [rsi+0xC9]==1? set [rbp+3]/[rbp+7]/[rbp+5]/[rbp+1]=1), then `lea rax,[0xF2BEEC0]` (string pointer), [rbp+0x3F0]=rax, call 0x67DB350; then set up a large arg block ([rsp+0x20..0x58]) with lea of stack addresses [rbp+0x3FA]..[rbp+0x558], ecx=0x9D0+[r14+0x10] where r14=[rbp+0x650] object [I] so [r14+0x10] is object field [V] [I-not-description], and call 0x67DB7A0 [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4773 | 0x66704FE | `or rdx,0x27` | rdx |= 0x27 [V] |
| 4774 | 0x6670502 | `mov rcx,rax` | rcx = rax [V] |
| 4775 | 0x6670505 | `call 0xE935700` | call 0xE935700 (free) [V] |
| 4776 | 0x667050A | `cmp dword ptr [rbp+0x670],1` | dword vs 1 [V] |
| 4777 | 0x6670511 | `jne short 0x6670528` | branch exit 0x6670528 [V] |
| 4778 | 0x6670513 | `cmp byte ptr [rsi+0xC9],1` | [rsi+0xC9] byte vs 1 (rsi object [I]) [V] |
| 4779 | 0x667051A | `jne short 0x667053E` | branch exit 0x667053E [V] |
| 4780 | 0x667051C | `cmp byte ptr [rbp+3],0` | flag [V] |
| 4781 | 0x6670520 | `jne short 0x6670548` | branch exit 0x6670548 [V] |
| 4782 | 0x6670522 | `mov byte ptr [rbp+3],1` | flag = 1 [V] |
| 4783 | 0x6670526 | `jmp short 0x6670548` | branch exit 0x6670548 [V] |
| 4784 | 0x6670528 | `cmp byte ptr [rbp+7],0` | flag [V] |
| 4785 | 0x667052C | `jne short 0x6670532` | branch exit 0x6670532 [V] |
| 4786 | 0x667052E | `mov byte ptr [rbp+7],1` | flag = 1 [V] |
| 4787 | 0x6670532 | `cmp byte ptr [rbp+5],0` | flag [V] |
| 4788 | 0x6670536 | `jne short 0x6670548` | branch exit 0x6670548 [V] |
| 4789 | 0x6670538 | `mov byte ptr [rbp+5],1` | flag = 1 [V] |
| 4790 | 0x667053C | `jmp short 0x6670548` | branch exit 0x6670548 [V] |
| 4791 | 0x667053E | `cmp byte ptr [rbp+1],0` | flag [V] |
| 4792 | 0x6670542 | `jne short 0x6670548` | branch exit 0x6670548 [V] |
| 4793 | 0x6670544 | `mov byte ptr [rbp+1],1` | flag = 1 [V] |
| 4794 | 0x6670548 | `lea rax,[0xF2BEEC0]` | rax = string pointer 0xF2BEEC0 [V] |
| 4795 | 0x667054F | `mov [rbp+0x3F0],rax` | store string pointer [V] |
| 4796 | 0x6670556 | `mov rdx,rbp` | rdx = rbp [V] |
| 4797 | 0x6670559 | `mov rcx,r12` | rcx = r12 ([rbp+0x3F8] addr from line 4670) [V] |
| 4798 | 0x667055C | `call 0x67DB350` | call 0x67DB350 [V] |
| 4799 | 0x6670561 | `nop` | — |
| 4800 | 0x6670562 | `mov ecx,0x9D0` | ecx = 0x9D0 [V] |
| 4801 | 0x6670567 | `add rcx,[r14+0x10]` | **[r14+0x10] qword → rcx; r14=[rbp+0x650] object (set line 4360, clobbered at line 4807) → object+0x10 read [V]; [I] not description** |
| 4802 | 0x667056B | `lea rax,[rbp+0x3FA]` | rax = stack addr [V] |
| 4803 | 0x6670572 | `lea r10,[rbp+0x3FC]` | r10 = stack addr [V] |
| 4804 | 0x6670579 | `lea r11,[rbp+0x3FE]` | r11 = stack addr [V] |
| 4805 | 0x6670580 | `lea rsi,[rbp+0x400]` | rsi = stack addr [V] |
| 4806 | 0x6670587 | `lea rbx,[rbp+0x402]` | rbx = stack addr [V] |
| 4807 | 0x667058E | `lea r14,[rbp+0x408]` | r14 clobbered → stack addr [V] |
| 4808 | 0x6670595 | `lea r15,[rbp+0x418]` | r15 = stack addr [V] |
| 4809 | 0x667059C | `lea r9,[rbp+0x478]` | r9 = stack addr [V] |
| 4810 | 0x66705A3 | `lea r8,[rbp+0x4C8]` | r8 = stack addr [V] |
| 4811 | 0x66705AA | `lea rdx,[rbp+0x558]` | rdx = stack addr [V] |

**Branch exits:** 0x6670528 (4777), 0x667053E (4779), 0x6670548 (4781, 4785, 4788, 4790, 4792). Calls: 0xE935700 (4775), 0x67DB350 (4798). No description-pointer reads ([r14+0x10] at line 4801 is object [rbp+0x650] field, [I] not description).

## Block 15 — listing lines 4813..4852 (40 lines)

### lines 4813..4852 (0x66705B1..0x6670663)
Store arg block to [rsp+0x20..0x58], call 0x67DB7A0; then `lea rax,[0xF2BEEC0]`, [rbp+0x3F0]=rax, lea rcx,[rbp+0x3F8], call 0x6774ED0 twice (rcx=[rbp+0x3F8] then rcx=rbp); `cmp byte ptr [rbp+0x398],1 / jne 0x66706A8` (hub again); `cmp byte ptr [rbp+0x378],3 / jne 0x667064E`; release chain on rsi=[rbp+0x370] (decref+dispose via qword ptr [0xF99FFA0]); `mov rbx,[rbp+0x348] / test rbx,rbx / je 0x66706A8` (hub again); `mov r14,[rbp+0x350] / jmp 0x6670667` [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4813 | 0x66705B6 | `mov [rsp+0x50],rax` | store arg [V] |
| 4814 | 0x66705BB | `mov [rsp+0x48],r10` | store arg [V] |
| 4815 | 0x66705C0 | `mov [rsp+0x40],r11` | store arg [V] |
| 4816 | 0x66705C5 | `mov [rsp+0x38],rsi` | store arg [V] |
| 4817 | 0x66705CA | `mov [rsp+0x30],rbx` | store arg [V] |
| 4818 | 0x66705CF | `mov [rsp+0x28],r14` | store arg [V] |
| 4819 | 0x66705D4 | `mov [rsp+0x20],r15` | store arg [V] |
| 4820 | 0x66705D9 | `call 0x67DB7A0` | call 0x67DB7A0 [V] |
| 4821 | 0x66705DE | `nop` | — |
| 4822 | 0x66705DF | `lea rax,[0xF2BEEC0]` | rax = string pointer 0xF2BEEC0 [V] |
| 4823 | 0x66705E6 | `mov [rbp+0x3F0],rax` | store [V] |
| 4824 | 0x66705ED | `lea rcx,[rbp+0x3F8]` | rcx = stack addr [V] |
| 4825 | 0x66705F4 | `call 0x6774ED0` | call 0x6774ED0 [V] |
| 4826 | 0x66705F9 | `mov rcx,rbp` | rcx = rbp [V] |
| 4827 | 0x66705FC | `call 0x6774ED0` | call 0x6774ED0 [V] |
| 4828 | 0x6670601 | `cmp byte ptr [rbp+0x398],1` | flag compare [V] |
| 4829 | 0x6670608 | `jne 0x66706A8` | **branch exit 0x66706A8 (cold hub)** [V] |
| 4830 | 0x667060E | `cmp byte ptr [rbp+0x378],3` | flag vs 3 [V] |
| 4831 | 0x6670615 | `jne short 0x667064E` | branch exit 0x667064E [V] |
| 4832 | 0x6670617 | `mov rsi,[rbp+0x370]` | rsi = chain object [V] |
| 4833 | 0x667061E | `test rsi,rsi` | test rsi [V] |
| 4834 | 0x6670621 | `je short 0x667064E` | branch exit 0x667064E [V] |
| 4835 | 0x6670623 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 4836 | 0x6670627 | `jne short 0x667064E` | branch exit 0x667064E [V] |
| 4837 | 0x6670629 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4838 | 0x667062C | `mov rax,[rax]` | rax = [rax] [V] |
| 4839 | 0x667062F | `mov rcx,rsi` | rcx = rsi [V] |
| 4840 | 0x6670632 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4841 | 0x6670638 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 4842 | 0x667063C | `jne short 0x667064E` | branch exit 0x667064E [V] |
| 4843 | 0x667063E | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4844 | 0x6670641 | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 4845 | 0x6670645 | `mov rcx,rsi` | rcx = rsi [V] |
| 4846 | 0x6670648 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4847 | 0x667064E | `mov rbx,[rbp+0x348]` | rbx = qword [V] |
| 4848 | 0x6670655 | `test rbx,rbx` | test rbx [V] |
| 4849 | 0x6670658 | `je short 0x66706A8` | **branch exit 0x66706A8 (cold hub)** [V] |
| 4850 | 0x667065A | `mov r14,[rbp+0x350]` | r14 = qword [V] |
| 4851 | 0x6670661 | `jmp short 0x6670667` | branch exit 0x6670667 [V] |
| 4852 | 0x6670663 | `add rbx,0x28` | rbx += 0x28 [V] |

**Branch exits:** 0x66706A8 (4829, 4849), 0x667064E (4831, 4834, 4836, 4842), 0x6670667 (4851). Calls: 0x67DB7A0 (4820), 0x6774ED0 (4825, 4827), qword ptr [0xF99FFA0] (4840, 4846). No description reads. Hub 0x66706A8 is reached from 3 sites [V]; its position in file not yet determined [?].

## Block 16 — listing lines 4853..4892 (40 lines)

### lines 4853..4892 (0x6670667..0x66706F2)
Bucket-chain release loop (rbx..r14, entries stride 0x28, [rbx+0x18]==2 filter): decref+dispose each via qword ptr [0xF99FFA0], loop to 0x6670663, exit to hub 0x66706A8 when done. Hub 0x66706A8 (reached from lines 4659, 4829, 4849, 4854) releases rsi=[rbp+0x5C8] chain, then guard-checks [rbp+0x5F8] region and calls 0xE935700 [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4853 | 0x6670667 | `cmp rbx,r14` | walker vs end [V] |
| 4854 | 0x667066A | `je short 0x66706A8` | branch exit 0x66706A8 (hub) [V] |
| 4855 | 0x667066C | `cmp byte ptr [rbx+0x18],2` | [rbx+0x18] byte vs 2 [V] |
| 4856 | 0x6670670 | `jne short 0x6670663` | branch exit 0x6670663 (loop) [V] |
| 4857 | 0x6670672 | `mov rsi,[rbx+8]` | [rbx+8] qword → rsi [V] |
| 4858 | 0x6670676 | `test rsi,rsi` | test rsi [V] |
| 4859 | 0x6670679 | `je short 0x6670663` | branch exit 0x6670663 [V] |
| 4860 | 0x667067B | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 4861 | 0x667067F | `jne short 0x6670663` | branch exit 0x6670663 [V] |
| 4862 | 0x6670681 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4863 | 0x6670684 | `mov rax,[rax]` | rax = [rax] vtable [V] |
| 4864 | 0x6670687 | `mov rcx,rsi` | rcx = rsi [V] |
| 4865 | 0x667068A | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4866 | 0x6670690 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 4867 | 0x6670694 | `jne short 0x6670663` | branch exit 0x6670663 [V] |
| 4868 | 0x6670696 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4869 | 0x6670699 | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 4870 | 0x667069D | `mov rcx,rsi` | rcx = rsi [V] |
| 4871 | 0x66706A0 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4872 | 0x66706A6 | `jmp short 0x6670663` | branch exit 0x6670663 [V] |
| 4873 | 0x66706A8 | `mov rsi,[rbp+0x5C8]` | **HUB 0x66706A8**: rsi = stack slot [V] |
| 4874 | 0x66706AF | `test rsi,rsi` | test rsi [V] |
| 4875 | 0x66706B2 | `je short 0x66706DF` | branch exit 0x66706DF [V] |
| 4876 | 0x66706B4 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 4877 | 0x66706B8 | `jne short 0x66706DF` | branch exit 0x66706DF [V] |
| 4878 | 0x66706BA | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4879 | 0x66706BD | `mov rax,[rax]` | rax = [rax] [V] |
| 4880 | 0x66706C0 | `mov rcx,rsi` | rcx = rsi [V] |
| 4881 | 0x66706C3 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4882 | 0x66706C9 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 4883 | 0x66706CD | `jne short 0x66706DF` | branch exit 0x66706DF [V] |
| 4884 | 0x66706CF | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4885 | 0x66706D2 | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 4886 | 0x66706D6 | `mov rcx,rsi` | rcx = rsi [V] |
| 4887 | 0x66706D9 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4888 | 0x66706DF | `mov rcx,[rbp+0x5F8]` | rcx = stack slot [V] |
| 4889 | 0x66706E6 | `test rcx,rcx` | test rcx [V] |
| 4890 | 0x66706E9 | `je short 0x667072D` | branch exit 0x667072D [V] |
| 4891 | 0x66706EB | `mov rdx,[rbp+0x608]` | rdx = end pointer [V] |
| 4892 | 0x66706F2 | `sub rdx,rcx` | size computation [V] |

**Branch exits:** 0x66706A8 (4854), 0x6670663 (4856, 4859, 4861, 4867, 4872), 0x66706DF (4875, 4877, 4883), 0x667072D (4890). Calls: qword ptr [0xF99FFA0] (4865, 4871, 4881, 4887). No description reads. Hub 0x66706A8 = common release code, not a tag case [I].

## Block 17 — listing lines 4893..4932 (40 lines)

### lines 4893..4932 (0x66706F5..0x66707A2)
Guard check [rdx vs 0x1000] → call 0xE935700 (jae 0x6670A7A), clear [rdi], then free the [rbp+0x5E8] node list (call 0x9B250 + 0xE935700 per node, je 0x6670021 when done). Then at 0x6670771: load [rbp+0x1F8] xmm, store to [r11], inc-ref [rbp+0x200] object or zero, store [rbp+0x550]/[rbp+0x558]/[rbp+0x560] [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4893 | 0x66706F5 | `cmp rdx,0x1000` | guard vs 0x1000 [V] |
| 4894 | 0x66706FC | `jb short 0x667071A` | branch exit 0x667071A [V] |
| 4895 | 0x66706FE | `mov rax,[rcx-8]` | [rcx-8] qword → rax [V] |
| 4896 | 0x6670702 | `add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 [V] |
| 4897 | 0x6670706 | `sub rcx,rax` | rcx -= rax [V] |
| 4898 | 0x6670709 | `cmp rcx,0x20` | compare vs 0x20 [V] |
| 4899 | 0x667070D | `jae 0x6670A7A` | branch exit 0x6670A7A [V] |
| 4900 | 0x6670713 | `add rdx,0x27` | rdx += 0x27 [V] |
| 4901 | 0x6670717 | `mov rcx,rax` | rcx = rax [V] |
| 4902 | 0x667071A | `call 0xE935700` | call 0xE935700 (free) [V] |
| 4903 | 0x667071F | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 4904 | 0x6670722 | `movups [rdi],xmm0` | clear [rdi] [V] |
| 4905 | 0x6670725 | `mov qword ptr [rdi+0x10],0` | clear [rdi+0x10] [V] |
| 4906 | 0x667072D | `mov rax,[rbp+0x5E8]` | rax = list head [V] |
| 4907 | 0x6670734 | `mov rcx,[rax+8]` | rcx = [rax+8] [V] |
| 4908 | 0x6670738 | `mov qword ptr [rcx],0` | clear forward link [V] |
| 4909 | 0x667073F | `mov rsi,[rax]` | rsi = next node [V] |
| 4910 | 0x6670742 | `test rsi,rsi` | test rsi [V] |
| 4911 | 0x6670745 | `je 0x6670021` | branch exit 0x6670021 [V] |
| 4912 | 0x667074B | `mov rdi,[rsi]` | rdi = [rsi] [V] |
| 4913 | 0x667074E | `lea rcx,[rsi+0x10]` | rcx = node+0x10 [V] |
| 4914 | 0x6670752 | `call 0x9B250` | call 0x9B250 (free helper) [V] |
| 4915 | 0x6670757 | `mov edx,0x50` | edx = 0x50 [V] |
| 4916 | 0x667075C | `mov rcx,rsi` | rcx = rsi [V] |
| 4917 | 0x667075F | `call 0xE935700` | call 0xE935700 (free) [V] |
| 4918 | 0x6670764 | `mov rsi,rdi` | rsi = rdi (next) [V] |
| 4919 | 0x6670767 | `test rdi,rdi` | test rdi [V] |
| 4920 | 0x667076A | `jne short 0x667074B` | branch exit 0x667074B (loop) [V] |
| 4921 | 0x667076C | `jmp 0x6670021` | branch exit 0x6670021 [V] |
| 4922 | 0x6670771 | `lea rsi,[rbp+0x1F8]` | rsi = stack addr [V] |
| 4923 | 0x6670778 | `movups xmm0,[rsi]` | xmm0 = [rbp+0x1F8] 16 bytes [V] |
| 4924 | 0x667077B | `movups [r11],xmm0` | store [V] |
| 4925 | 0x667077F | `jmp short 0x66707B7` | branch exit 0x66707B7 [V] |
| 4926 | 0x6670781 | `movups [r11],xmm0` | store [V] |
| 4927 | 0x6670785 | `mov r11,[rbp+0x200]` | r11 = qword [V] |
| 4928 | 0x667078C | `test r11,r11` | test r11 [V] |
| 4929 | 0x667078F | `je short 0x667079F` | branch exit 0x667079F [V] |
| 4930 | 0x6670791 | `lock inc dword ptr [r11+8]` | [r11+8] dword++ (incref) [V] |
| 4931 | 0x6670796 | `mov r11,[rbp+0x200]` | r11 = qword [V] |
| 4932 | 0x667079D | `jmp short 0x66707A2` | branch exit 0x66707A2 [V] |

**Branch exits:** 0x667071A (4894), 0x6670A7A (4899), 0x6670021 (4911, 4921), 0x667074B (4920), 0x66707B7 (4925), 0x667079F (4929), 0x66707A2 (4932). Calls: 0xE935700 (4902, 4917), 0x9B250 (4914). No description reads.

## Block 18 — listing lines 4933..4972 (40 lines)

### lines 4933..4972 (0x667079F..0x6670864)
`xor r11d,r11d` (null case), then mov rsi=[rbp+0x1F8], store [rbp+0x550]=rsi, [rbp+0x558]=r11, [rbp+0x560]=cl, [rbp+0x578]=[rbp+0x220], copy [rbp+0x210] to [rbp+0x568]; `mov ecx,0x9D0 / add rcx,[r15+0x10]` where r15=[rbp+0x418] stack addr (set line 4808) → stack field read [I] not description; store args [rsp+0x28]/[rsp+0x20], call 0x67DAA20, call 0x66E5B10 with [rbp+0x3F0]; `cmp byte ptr [rbp+0x380],1 / jne 0x6670847`; guard-check [rbp+0x350]-[rbp+0x340] vs 0x1000 → call 0xE935700 (jae 0x6670A7A); `cmp byte ptr [rbp+0x228],1 / jne 0x66708EE`; `cmp byte ptr [rbp+0x208],3 / jne 0x6670894`; rsi=[rbp+0x200] chain head [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4933 | 0x667079F | `xor r11d,r11d` | r11d = 0 [V] |
| 4934 | 0x66707A2 | `mov rsi,[rbp+0x1F8]` | rsi = qword [V] |
| 4935 | 0x66707A9 | `mov [rbp+0x550],rsi` | store [V] |
| 4936 | 0x66707B0 | `mov [rbp+0x558],r11` | store [V] |
| 4937 | 0x66707B7 | `mov [rbp+0x560],cl` | store byte [V] |
| 4938 | 0x66707BD | `mov rcx,[rbp+0x220]` | rcx = qword [V] |
| 4939 | 0x66707C4 | `mov [rbp+0x578],rcx` | store [V] |
| 4940 | 0x66707CB | `movaps xmm0,[rbp+0x210]` | xmm0 = 16 bytes [V] |
| 4941 | 0x66707D2 | `movups [rbp+0x568],xmm0` | store [V] |
| 4942 | 0x66707D9 | `mov ecx,0x9D0` | ecx = 0x9D0 [V] |
| 4943 | 0x66707DE | `add rcx,[r15+0x10]` | **[r15+0x10] qword → rcx; r15=[rbp+0x418] stack addr (line 4808) → stack+0x10 read [V]; [I] not description** |
| 4944 | 0x66707E2 | `mov [rsp+0x28],rax` | store arg [V] |
| 4945 | 0x66707E7 | `mov [rsp+0x20],r10` | store arg [V] |
| 4946 | 0x66707EC | `call 0x67DAA20` | call 0x67DAA20 [V] |
| 4947 | 0x66707F1 | `nop` | — |
| 4948 | 0x66707F2 | `lea rcx,[rbp+0x3F0]` | rcx = arg [V] |
| 4949 | 0x66707F9 | `call 0x66E5B10` | call 0x66E5B10 [V] |
| 4950 | 0x66707FE | `cmp byte ptr [rbp+0x380],1` | flag vs 1 [V] |
| 4951 | 0x6670805 | `jne short 0x6670847` | branch exit 0x6670847 [V] |
| 4952 | 0x6670807 | `mov rcx,[rbp+0x340]` | rcx = qword [V] |
| 4953 | 0x667080E | `test rcx,rcx` | test rcx [V] |
| 4954 | 0x6670811 | `je short 0x6670847` | branch exit 0x6670847 [V] |
| 4955 | 0x6670813 | `mov rdx,[rbp+0x350]` | rdx = end [V] |
| 4956 | 0x667081A | `sub rdx,rcx` | size [V] |
| 4957 | 0x667081D | `cmp rdx,0x1000` | guard vs 0x1000 [V] |
| 4958 | 0x6670824 | `jb short 0x6670842` | branch exit 0x6670842 [V] |
| 4959 | 0x6670826 | `mov rax,[rcx-8]` | [rcx-8] qword → rax [V] |
| 4960 | 0x667082A | `add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 [V] |
| 4961 | 0x667082E | `sub rcx,rax` | rcx -= rax [V] |
| 4962 | 0x6670831 | `cmp rcx,0x20` | compare vs 0x20 [V] |
| 4963 | 0x6670835 | `jae 0x6670A7A` | branch exit 0x6670A7A [V] |
| 4964 | 0x667083B | `or rdx,0x27` | rdx |= 0x27 [V] |
| 4965 | 0x667083F | `mov rcx,rax` | rcx = rax [V] |
| 4966 | 0x6670842 | `call 0xE935700` | call 0xE935700 (free) [V] |
| 4967 | 0x6670847 | `cmp byte ptr [rbp+0x228],1` | flag vs 1 [V] |
| 4968 | 0x667084E | `jne 0x66708EE` | branch exit 0x66708EE [V] |
| 4969 | 0x6670854 | `cmp byte ptr [rbp+0x208],3` | flag vs 3 [V] |
| 4970 | 0x667085B | `jne short 0x6670894` | branch exit 0x6670894 [V] |
| 4971 | 0x667085D | `mov rsi,[rbp+0x200]` | rsi = chain object [V] |
| 4972 | 0x6670864 | `test rsi,rsi` | test rsi [V] |

**Branch exits:** 0x6670847 (4951, 4954), 0x6670842 (4958), 0x6670A7A (4963), 0x66708EE (4968), 0x6670894 (4970). Calls: 0x67DAA20 (4946), 0x66E5B10 (4949), 0xE935700 (4966). No description reads.

## Block 19 — listing lines 4973..5012 (40 lines)

### lines 4973..5012 (0x6670866..0x66708EC)
Release rsi=[rbp+0x200] chain (decref+dispose via qword ptr [0xF99FFA0], exit 0x6670894); then bucket-chain release loop rbx=[rbp+0x1D8]..r14=[rbp+0x1E0] stride 0x28, [rbx+0x18]==2 filter, same dispose pattern, exit to 0x66708EE when done [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 4973 | 0x6670867 | `je short 0x6670894` | branch exit 0x6670894 [V] |
| 4974 | 0x6670869 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 4975 | 0x667086D | `jne short 0x6670894` | branch exit 0x6670894 [V] |
| 4976 | 0x667086F | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4977 | 0x6670872 | `mov rax,[rax]` | rax = [rax] vtable [V] |
| 4978 | 0x6670875 | `mov rcx,rsi` | rcx = rsi [V] |
| 4979 | 0x6670878 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4980 | 0x667087E | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 4981 | 0x6670882 | `jne short 0x6670894` | branch exit 0x6670894 [V] |
| 4982 | 0x6670884 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 4983 | 0x6670887 | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 4984 | 0x667088B | `mov rcx,rsi` | rcx = rsi [V] |
| 4985 | 0x667088E | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 4986 | 0x6670894 | `mov rbx,[rbp+0x1D8]` | rbx = walker [V] |
| 4987 | 0x667089B | `test rbx,rbx` | test rbx [V] |
| 4988 | 0x667089E | `je short 0x66708EE` | branch exit 0x66708EE [V] |
| 4989 | 0x66708A0 | `mov r14,[rbp+0x1E0]` | r14 = end [V] |
| 4990 | 0x66708A7 | `jmp short 0x66708AD` | branch exit 0x66708AD [V] |
| 4991 | 0x66708A9 | `add rbx,0x28` | rbx += 0x28 (loop advance) [V] |
| 4992 | 0x66708AD | `cmp rbx,r14` | walker vs end [V] |
| 4993 | 0x66708B0 | `je short 0x66708EE` | branch exit 0x66708EE [V] |
| 4994 | 0x66708B2 | `cmp byte ptr [rbx+0x18],2` | [rbx+0x18] byte vs 2 [V] |
| 4995 | 0x66708B6 | `jne short 0x66708A9` | branch exit 0x66708A9 [V] |
| 4996 | 0x66708B8 | `mov rsi,[rbx+8]` | [rbx+8] qword → rsi [V] |
| 4997 | 0x66708BC | `test rsi,rsi` | test rsi [V] |
| 4998 | 0x66708BF | `je short 0x66708A9` | branch exit 0x66708A9 [V] |
| 4999 | 0x66708C1 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 5000 | 0x66708C5 | `jne short 0x66708A9` | branch exit 0x66708A9 [V] |
| 5001 | 0x66708C7 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 5002 | 0x66708CA | `mov rax,[rax]` | rax = [rax] vtable [V] |
| 5003 | 0x66708CD | `mov rcx,rsi` | rcx = rsi [V] |
| 5004 | 0x66708D0 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 5005 | 0x66708D6 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 5006 | 0x66708DA | `jne short 0x66708A9` | branch exit 0x66708A9 [V] |
| 5007 | 0x66708DC | `mov rax,[rsi]` | rax = [rsi] [V] |
| 5008 | 0x66708DF | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 5009 | 0x66708E3 | `mov rcx,rsi` | rcx = rsi [V] |
| 5010 | 0x66708E6 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 5011 | 0x66708EC | `jmp short 0x66708A9` | branch exit 0x66708A9 [V] |

**Branch exits:** 0x6670894 (4973, 4975, 4981), 0x66708EE (4988, 4993), 0x66708AD (4990), 0x66708A9 (4991/4995/4998/5000/5006/5011 loop). Calls: qword ptr [0xF99FFA0] (4979, 4985, 5004, 5010). No description reads.

## Block 20 — listing lines 5013..5052 (40 lines)

### lines 5013..5052 (0x66708EE..0x6670994)
Release rsi=[rbp+0x638] chain (exit 0x6670925); guard-check/free [rbp+0x5F8] region → call 0xE935700 (jae 0x6670A7A); clear [rdi]; free [rbp+0x5E8] node list; `je 0x666E261` at line 5050 — **backward jump into earlier body region (0x666E261, U-FX3 range ~line 2999) — cold-path re-entry, not sequential flow** [V]; then continue node free loop [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5013 | 0x66708EE | `mov rsi,[rbp+0x638]` | rsi = chain object [V] |
| 5014 | 0x66708F5 | `test rsi,rsi` | test rsi [V] |
| 5015 | 0x66708F8 | `je short 0x6670925` | branch exit 0x6670925 [V] |
| 5016 | 0x66708FA | `lock dec dword ptr [rsi+8]` | [rsi+8] dword-- [V] |
| 5017 | 0x66708FE | `jne short 0x6670925` | branch exit 0x6670925 [V] |
| 5018 | 0x6670900 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 5019 | 0x6670903 | `mov rax,[rax]` | rax = [rax] vtable [V] |
| 5020 | 0x6670906 | `mov rcx,rsi` | rcx = rsi [V] |
| 5021 | 0x6670909 | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 5022 | 0x667090F | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword-- [V] |
| 5023 | 0x6670913 | `jne short 0x6670925` | branch exit 0x6670925 [V] |
| 5024 | 0x6670915 | `mov rax,[rsi]` | rax = [rsi] [V] |
| 5025 | 0x6670918 | `mov rax,[rax+8]` | rax = [rax+8] [V] |
| 5026 | 0x667091C | `mov rcx,rsi` | rcx = rsi [V] |
| 5027 | 0x667091F | `call qword ptr [0xF99FFA0]` | indirect release call [V] |
| 5028 | 0x6670925 | `mov rcx,[rbp+0x5F8]` | rcx = stack slot [V] |
| 5029 | 0x667092C | `test rcx,rcx` | test rcx [V] |
| 5030 | 0x667092F | `je short 0x6670973` | branch exit 0x6670973 [V] |
| 5031 | 0x6670931 | `mov rdx,[rbp+0x608]` | rdx = end pointer [V] |
| 5032 | 0x6670938 | `sub rdx,rcx` | size [V] |
| 5033 | 0x667093B | `cmp rdx,0x1000` | guard vs 0x1000 [V] |
| 5034 | 0x6670942 | `jb short 0x6670960` | branch exit 0x6670960 [V] |
| 5035 | 0x6670944 | `mov rax,[rcx-8]` | [rcx-8] qword → rax [V] |
| 5036 | 0x6670948 | `add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 [V] |
| 5037 | 0x667094C | `sub rcx,rax` | rcx -= rax [V] |
| 5038 | 0x667094F | `cmp rcx,0x20` | compare vs 0x20 [V] |
| 5039 | 0x6670953 | `jae 0x6670A7A` | branch exit 0x6670A7A [V] |
| 5040 | 0x6670959 | `add rdx,0x27` | rdx += 0x27 [V] |
| 5041 | 0x667095D | `mov rcx,rax` | rcx = rax [V] |
| 5042 | 0x6670960 | `call 0xE935700` | call 0xE935700 (free) [V] |
| 5043 | 0x6670965 | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 5044 | 0x6670968 | `movups [rdi],xmm0` | clear [rdi] [V] |
| 5045 | 0x667096B | `mov qword ptr [rdi+0x10],0` | clear [rdi+0x10] [V] |
| 5046 | 0x6670973 | `mov rax,[rbp+0x5E8]` | rax = list head [V] |
| 5047 | 0x667097A | `mov rcx,[rax+8]` | rcx = [rax+8] [V] |
| 5048 | 0x667097E | `mov qword ptr [rcx],0` | clear forward link [V] |
| 5049 | 0x6670985 | `mov rsi,[rax]` | rsi = next node [V] |
| 5050 | 0x6670988 | `test rsi,rsi` | test rsi [V] |
| 5051 | 0x667098B | `je 0x666E261` | **backward jump to 0x666E261 (earlier body region, U-FX3 range) — cold-path re-entry [V]** |
| 5052 | 0x6670991 | `mov rdi,[rsi]` | rdi = [rsi] [V] |

**Branch exits:** 0x6670925 (5015, 5017, 5023), 0x6670973 (5030), 0x6670960 (5034), 0x6670A7A (5039), 0x666E261 (5051, backward [V]). Calls: qword ptr [0xF99FFA0] (5021, 5027), 0xE935700 (5042). No description reads.

## Block 21 — listing lines 5053..5092 (40 lines)

### lines 5053..5092 (0x6670998..0x6670A34)
Node-free loop completes (0x6670998..0x66709B0: call 0x9B250 + 0xE935700 per node, jne loop, jmp 0x666E261 when done) — another backward jump into earlier body region [V]. Then a series of FAILURE HANDLERS: each `mov ecx,0x50/0x20 / call 0x9BC830 / jmp 0x666XXXX` jumps back to an earlier body address (0x666DC05, 0x666FD0A, 0x666B4A8, 0x666B56D, 0x666DE0A, 0x666DEF1, 0x666DF68, 0x666DAE3, 0x666E01B, 0x666E092, 0x666F8EF) — all targets are BELOW 0x666FBC0, i.e. inside the tag-7 body proper (U-FX3 range) [V]. None of these is a jump-table case; they are failure cleanup paths [I].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5053 | 0x6670998 | `call 0x9B250` | call 0x9B250 (free helper) [V] |
| 5054 | 0x667099D | `mov edx,0x50` | edx = 0x50 [V] |
| 5055 | 0x66709A2 | `mov rcx,rsi` | rcx = rsi [V] |
| 5056 | 0x66709A5 | `call 0xE935700` | call 0xE935700 (free) [V] |
| 5057 | 0x66709AA | `mov rsi,rdi` | rsi = rdi (next node) [V] |
| 5058 | 0x66709AD | `test rdi,rdi` | test rdi [V] |
| 5059 | 0x66709B0 | `jne short 0x6670991` | branch exit 0x6670991 (loop) [V] |
| 5060 | 0x66709B2 | `jmp 0x666E261` | backward jump to earlier body (0x666E261) [V] |
| 5061 | 0x66709B7 | `mov ecx,0x50` | failure handler: ecx = 0x50 [V] |
| 5062 | 0x66709BC | `call 0x9BC830` | call 0x9BC830 (free) [V] |
| 5063 | 0x66709C1 | `nop` | — |
| 5064 | 0x66709C2 | `jmp 0x666DC05` | **jmp back into tag-7 body proper (0x666DC05 < 0x666FBC0)** [V] |
| 5065 | 0x66709C7 | `mov ecx,0x50` | failure handler [V] |
| 5066 | 0x66709CC | `call 0x9BC830` | call 0x9BC830 [V] |
| 5067 | 0x66709D1 | `nop` | — |
| 5068 | 0x66709D2 | `jmp 0x666FD0A` | jmp back into body (0x666FD0A) [V] |
| 5069 | 0x66709D7 | `mov rcx,r15` | failure handler: rcx = r15 [V] |
| 5070 | 0x66709DA | `call 0x9BC830` | call 0x9BC830 [V] |
| 5071 | 0x66709DF | `nop` | — |
| 5072 | 0x66709E0 | `jmp 0x666B4A8` | jmp back into body (0x666B4A8) [V] |
| 5073 | 0x66709E5 | `mov rcx,rdi` | failure handler: rcx = rdi [V] |
| 5074 | 0x66709E8 | `call 0x9BC830` | call 0x9BC830 [V] |
| 5075 | 0x66709ED | `nop` | — |
| 5076 | 0x66709EE | `jmp 0x666B56D` | jmp back into body (0x666B56D) [V] |
| 5077 | 0x66709F3 | `mov ecx,0x20` | failure handler: ecx = 0x20 [V] |
| 5078 | 0x66709F8 | `call 0x9BC830` | call 0x9BC830 [V] |
| 5079 | 0x66709FD | `nop` | — |
| 5080 | 0x66709FE | `jmp 0x666DE0A` | jmp back into body (0x666DE0A) [V] |
| 5081 | 0x6670A03 | `mov qword ptr [rbp+0x1C8],0` | failure handler: clear slot [V] |
| 5082 | 0x6670A0E | `mov ecx,0x50` | ecx = 0x50 [V] |
| 5083 | 0x6670A13 | `call 0x9BC830` | call 0x9BC830 [V] |
| 5084 | 0x6670A18 | `nop` | — |
| 5085 | 0x6670A19 | `jmp 0x666DEF1` | jmp back into body (0x666DEF1) [V] |
| 5086 | 0x6670A1E | `mov ecx,0x20` | failure handler: ecx = 0x20 [V] |
| 5087 | 0x6670A23 | `call 0x9BC830` | call 0x9BC830 [V] |
| 5088 | 0x6670A28 | `nop` | — |
| 5089 | 0x6670A29 | `jmp 0x666DF68` | jmp back into body (0x666DF68) [V] |
| 5090 | 0x6670A2E | `mov rcx,rdi` | failure handler: rcx = rdi [V] |
| 5091 | 0x6670A31 | `mov rdi,rax` | rdi = rax [V] |
| 5092 | 0x6670A34 | `call 0x9BC830` | call 0x9BC830 [V] |

**Branch exits:** 0x6670991 (5059), 0x666E261 (5060, backward), 0x666DC05 (5064), 0x666FD0A (5068), 0x666B4A8 (5072), 0x666B56D (5076), 0x666DE0A (5080), 0x666DEF1 (5085), 0x666DF68 (5089), then fall-through to line 5093 (next block). Calls: 0x9B250 (5053), 0xE935700 (5056), 0x9BC830 (5062, 5066, 5070, 5074, 5078, 5083, 5087, 5092). No description reads. All jmp targets are earlier body addresses — failure handlers, not tag cases [I].

## Block 22 — listing lines 5093..5132 (40 lines)

### lines 5093..5132 (0x6670A39..0x6670AFD)
Failure handler continues: `mov rax,rdi / jmp 0x666DAE3`; then `[rbp+0x1C0]=0 / call 0x9BC830 / jmp 0x666E01B`; `call 0x9BC830 / jmp 0x666E092`; `mov rcx,r15 / call 0x9BC830 / jmp 0x666F8EF`. Then ALLOCATION-FAILURE HANDLER at 0x6670A7A: zero args, `call qword ptr [0xF9A8C78]`, `call 0x75B60`, `lea rcx,[0x129FA0E0] / call 0xE938CB0 / cmp [0x129FA0E0],0xFFFFFFFF / jne 0x666AEE7` (back into body); else set [rbp+0x630]=0, [rbp+0x3D0]=string 0xF5A7830, [rbp+0x3D8]=8, call 0x5668AC0, `lea rcx,[0x129FA0E0] / call 0xE938D70 / jmp 0x666AEE7` [V]. All jmp targets here are earlier body addresses (< 0x666FBC0).

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5093 | 0x6670A39 | `mov rax,rdi` | rax = rdi [V] |
| 5094 | 0x6670A3C | `jmp 0x666DAE3` | jmp back into body (0x666DAE3) [V] |
| 5095 | 0x6670A41 | `mov qword ptr [rbp+0x1C0],0` | clear slot [V] |
| 5096 | 0x6670A4C | `mov ecx,0x50` | ecx = 0x50 [V] |
| 5097 | 0x6670A51 | `call 0x9BC830` | call 0x9BC830 [V] |
| 5098 | 0x6670A56 | `nop` | — |
| 5099 | 0x6670A57 | `jmp 0x666E01B` | jmp back into body (0x666E01B) [V] |
| 5100 | 0x6670A5C | `mov ecx,0x20` | ecx = 0x20 [V] |
| 5101 | 0x6670A61 | `call 0x9BC830` | call 0x9BC830 [V] |
| 5102 | 0x6670A66 | `nop` | — |
| 5103 | 0x6670A67 | `jmp 0x666E092` | jmp back into body (0x666E092) [V] |
| 5104 | 0x6670A6C | `mov rcx,r15` | rcx = r15 [V] |
| 5105 | 0x6670A6F | `call 0x9BC830` | call 0x9BC830 [V] |
| 5106 | 0x6670A74 | `nop` | — |
| 5107 | 0x6670A75 | `jmp 0x666F8EF` | jmp back into body (0x666F8EF) [V] |
| 5108 | 0x6670A7A | `mov qword ptr [rsp+0x20],0` | **ALLOC-FAILURE HANDLER 0x6670A7A** (target of many `jae 0x6670A7A` guards) [V] |
| 5109 | 0x6670A83 | `xor ecx,ecx` | — |
| 5110 | 0x6670A85 | `xor edx,edx` | — |
| 5111 | 0x6670A87 | `xor r8d,r8d` | — |
| 5112 | 0x6670A8A | `xor r9d,r9d` | — |
| 5113 | 0x6670A8D | `call qword ptr [0xF9A8C78]` | indirect call [V] |
| 5114 | 0x6670A93 | `nop` | — |
| 5115 | 0x6670A94 | `call 0x75B60` | call 0x75B60 [V] |
| 5116 | 0x6670A99 | `nop` | — |
| 5117 | 0x6670A9A | `lea rcx,[0x129FA0E0]` | rcx = global addr [V] |
| 5118 | 0x6670AA1 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5119 | 0x6670AA6 | `cmp dword ptr [0x129FA0E0],0xFFFFFFFF` | global vs -1 [V] |
| 5120 | 0x6670AAD | `jne 0x666AEE7` | jmp back into body (0x666AEE7) [V] |
| 5121 | 0x6670AB3 | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 5122 | 0x6670AB6 | `movaps [rbp+0x630],xmm0` | clear slot [V] |
| 5123 | 0x6670ABD | `lea rax,[0xF5A7830]` | rax = string pointer 0xF5A7830 [V] |
| 5124 | 0x6670AC4 | `mov [rbp+0x3D0],rax` | store string pointer [V] |
| 5125 | 0x6670ACB | `mov qword ptr [rbp+0x3D8],8` | store 8 [V] |
| 5126 | 0x6670AD6 | `lea rcx,[0x129FA0D0]` | rcx = global addr [V] |
| 5127 | 0x6670ADD | `lea rdx,[rbp+0x3D0]` | rdx = arg [V] |
| 5128 | 0x6670AE4 | `lea r8,[rbp+0x630]` | r8 = arg [V] |
| 5129 | 0x6670AEB | `call 0x5668AC0` | call 0x5668AC0 [V] |
| 5130 | 0x6670AF0 | `nop` | — |
| 5131 | 0x6670AF1 | `lea rcx,[0x129FA0E0]` | rcx = global addr [V] |
| 5132 | 0x6670AF8 | `call 0xE938D70` | call 0xE938D70 [V] |

**Branch exits:** 0x666DAE3 (5094), 0x666E01B (5099), 0x666E092 (5103), 0x666F8EF (5107), 0x666AEE7 (5120, 5133 next block). Calls: 0x9BC830 (5097, 5101, 5105), qword ptr [0xF9A8C78] (5113), 0x75B60 (5115), 0xE938CB0 (5118), 0x5668AC0 (5129), 0xE938D70 (5132). No description reads. All jump targets point back into the tag-7 body proper — failure cleanup, not other tag cases [I].

## Block 23 — listing lines 5133..5172 (40 lines)

### lines 5133..5172 (0x6670AFD..0x6670BE0)
`jmp 0x666AEE7`; then another failure-handler pattern: `lea rcx,[0x129FA118] / call 0xE938CB0 / cmp [0x129FA118],0xFFFFFFFF / jne 0x666B02E`; else zero [rbp+0x300], [rbp+0x5C0]=string 0xF2BE5A8, [rbp+0x5C8]=7, `lea rcx,[0x129FA108] / call 0x5668AC0 / lea rcx,[0x129FA118] / call 0xE938D70 / jmp 0x666B02E` [V]. All targets back into body.

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5133 | 0x6670AFD | `jmp 0x666AEE7` | jmp back into body (0x666AEE7) [V] |
| 5134 | 0x6670B02 | `lea rcx,[0x129FA118]` | rcx = global addr [V] |
| 5135 | 0x6670B09 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5136 | 0x6670B0E | `cmp dword ptr [0x129FA118],0xFFFFFFFF` | global vs -1 [V] |
| 5137 | 0x6670B15 | `jne 0x666B02E` | jmp back into body (0x666B02E) [V] |
| 5138 | 0x6670B1B | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 5139 | 0x6670B1E | `movaps [rbp+0x300],xmm0` | clear slot [V] |
| 5140 | 0x6670B25 | `lea rax,[0xF2BE5A8]` | rax = string pointer 0xF2BE5A8 [V] |
| 5141 | 0x6670B2C | `mov [rbp+0x5C0],rax` | store string pointer [V] |
| 5142 | 0x6670B33 | `mov qword ptr [rbp+0x5C8],7` | store 7 [V] |
| 5143 | 0x6670B3E | `lea rcx,[0x129FA108]` | rcx = global addr [V] |
| 5144 | 0x6670B45 | `lea rdx,[rbp+0x5C0]` | rdx = arg [V] |
| 5145 | 0x6670B4C | `lea r8,[rbp+0x300]` | r8 = arg [V] |
| 5146 | 0x6670B53 | `call 0x5668AC0` | call 0x5668AC0 [V] |
| 5147 | 0x6670B58 | `nop` | — |
| 5148 | 0x6670B59 | `lea rcx,[0x129FA118]` | rcx = global addr [V] |
| 5149 | 0x6670B60 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5150 | 0x6670B65 | `jmp 0x666B02E` | jmp back into body (0x666B02E) [V] |
| 5151 | 0x6670B6A | `lea rax,[0x129FB1B0]` | failure handler: rax = global addr [V] |
| 5152 | 0x6670B71 | `mov rsi,rcx` | rsi = rcx [V] |
| 5153 | 0x6670B74 | `mov rcx,rax` | rcx = rax [V] |
| 5154 | 0x6670B77 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5155 | 0x6670B7C | `mov rcx,rsi` | rcx = rsi [V] |
| 5156 | 0x6670B7F | `cmp dword ptr [0x129FB1B0],0xFFFFFFFF` | global vs -1 [V] |
| 5157 | 0x6670B86 | `jne 0x666B058` | jmp back into body (0x666B058) [V] |
| 5158 | 0x6670B8C | `mov dword ptr [rbp+0x3F0],0` | clear slot [V] |
| 5159 | 0x6670B96 | `lea rcx,[0x129FB170]` | rcx = global addr [V] |
| 5160 | 0x6670B9D | `lea rdx,[rbp+0x3F0]` | rdx = arg [V] |
| 5161 | 0x6670BA4 | `mov r8,rbp` | r8 = rbp [V] |
| 5162 | 0x6670BA7 | `call 0x9B020` | call 0x9B020 [V] |
| 5163 | 0x6670BAC | `nop` | — |
| 5164 | 0x6670BAD | `lea rcx,[0x6761090]` | rcx = code address 0x6761090 [V] |
| 5165 | 0x6670BB4 | `call 0xE935740` | call 0xE935740 [V] |
| 5166 | 0x6670BB9 | `lea rcx,[0x129FB1B0]` | rcx = global addr [V] |
| 5167 | 0x6670BC0 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5168 | 0x6670BC5 | `mov rcx,rsi` | rcx = rsi [V] |
| 5169 | 0x6670BC8 | `jmp 0x666B058` | jmp back into body (0x666B058) [V] |

**Branch exits:** 0x666AEE7 (5133), 0x666B02E (5137, 5150), 0x666B058 (5157, 5169). Calls: 0xE938CB0 (5135, 5154), 0x5668AC0 (5146), 0xE938D70 (5149, 5167), 0x9B020 (5162), 0xE935740 (5165). No description reads. All jump targets back into tag-7 body — failure handlers [I].

## Block 24 — listing lines 5173..5212 (40 lines)

### lines 5173..5212 (0x6670BE6..0x6670CA9)
Failure handler: `jne 0x666B228`; else zero [rbp+0x5E0], [rbp+0x300]=string 0xF53ACB3, [rbp+0x308]=0x18, `lea rcx,[0x129FA130] / call 0x5668AC0 / lea rcx,[0x129FA140] / call 0xE938D70 / jmp 0x666B228`. Then `call 0x1166E0 / call 0x75740`; `lea rcx,[0x129CA5E0] / call 0xE938CB0 / cmp [0x129CA5E0],0xFFFFFFFF / jne 0x666AF6D`; else `lea rcx,[0x129CA568] / call 0x567DB00 / lea rcx,[0x567DBA0] / call 0xE935740 / lea rcx,[0x129CA5E0] / call 0xE938D70 / jmp 0x666AF6D`. Then another: `lea rcx,[0x129CA5E0] / call 0xE938CB0 / cmp / (bad)` at line 5206 — undecodable bytes (likely embedded data/padding in cold region) [V]; then `call 0x567DB00 / lea rcx,[0x567DBA0] / call 0xE935740 / lea rcx,[0x129CA5E0] / call 0xE938D70 / jmp 0x666B0D9` [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5173 | 0x6670BE6 | `xorps xmm0,xmm0` | zero xmm0 [V] |
| 5174 | 0x6670BE9 | `movaps [rbp+0x5E0],xmm0` | clear slot [V] |
| 5175 | 0x6670BF0 | `lea rax,[0xF53ACB3]` | rax = string pointer 0xF53ACB3 [V] |
| 5176 | 0x6670BF7 | `mov [rbp+0x300],rax` | store string pointer [V] |
| 5177 | 0x6670BFE | `mov qword ptr [rbp+0x308],0x18` | store 0x18 [V] |
| 5178 | 0x6670C09 | `lea rcx,[0x129FA130]` | rcx = global addr [V] |
| 5179 | 0x6670C10 | `lea rdx,[rbp+0x300]` | rdx = arg [V] |
| 5180 | 0x6670C17 | `lea r8,[rbp+0x5E0]` | r8 = arg [V] |
| 5181 | 0x6670C1E | `call 0x5668AC0` | call 0x5668AC0 [V] |
| 5182 | 0x6670C23 | `nop` | — |
| 5183 | 0x6670C24 | `lea rcx,[0x129FA140]` | rcx = global addr [V] |
| 5184 | 0x6670C2B | `call 0xE938D70` | call 0xE938D70 [V] |
| 5185 | 0x6670C30 | `jmp 0x666B228` | jmp back into body (0x666B228) [V] |
| 5186 | 0x6670C35 | `call 0x1166E0` | call 0x1166E0 [V] |
| 5187 | 0x6670C3A | `nop` | — |
| 5188 | 0x6670C3B | `call 0x75740` | call 0x75740 [V] |
| 5189 | 0x6670C40 | `nop` | — |
| 5190 | 0x6670C41 | `lea rcx,[0x129CA5E0]` | rcx = global addr [V] |
| 5191 | 0x6670C48 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5192 | 0x6670C4D | `cmp dword ptr [0x129CA5E0],0xFFFFFFFF` | global vs -1 [V] |
| 5193 | 0x6670C54 | `jne 0x666AF6D` | jmp back into body (0x666AF6D) [V] |
| 5194 | 0x6670C5A | `lea rcx,[0x129CA568]` | rcx = global addr [V] |
| 5195 | 0x6670C61 | `call 0x567DB00` | call 0x567DB00 [V] |
| 5196 | 0x6670C66 | `nop` | — |
| 5197 | 0x6670C67 | `lea rcx,[0x567DBA0]` | rcx = code address 0x567DBA0 [V] |
| 5198 | 0x6670C6E | `call 0xE935740` | call 0xE935740 [V] |
| 5199 | 0x6670C73 | `lea rcx,[0x129CA5E0]` | rcx = global addr [V] |
| 5200 | 0x6670C7A | `call 0xE938D70` | call 0xE938D70 [V] |
| 5201 | 0x6670C7F | `jmp 0x666AF6D` | jmp back into body (0x666AF6D) [V] |
| 5202 | 0x6670C84 | `lea rcx,[0x129CA5E0]` | rcx = global addr [V] |
| 5203 | 0x6670C8B | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5204 | 0x6670C90 | `cmp dword ptr [0x129CA5E0],0xFFFFFFFF` | global vs -1 [V] |
| 5205 | 0x6670C97 | `(bad)` | **undecodable bytes (cold region padding/embedded data)** [V] |
| 5206 | 0x6670C98 | `test [rsp],edi` | misdecode of data bytes [V] |
| 5207 | 0x6670C9B | `(bad)` | undecodable bytes [V] |
| 5208 | 0x6670C9C | `dec dword ptr [rax-0x73]` | misdecode [V] |
| 5209 | 0x6670C9F | `or eax,0xC3598C4` | misdecode [V] |
| 5210 | 0x6670CA4 | `call 0x567DB00` | call 0x567DB00 [V] |
| 5211 | 0x6670CA9 | `nop` | — |

**Branch exits:** 0x666B228 (5185), 0x666AF6D (5193, 5201), 0x666B0D9 (5217 next block). Calls: 0x5668AC0 (5181), 0xE938D70 (5184), 0x1166E0 (5186), 0x75740 (5188), 0xE938CB0 (5191), 0x567DB00 (5195, 5210), 0xE935740 (5198, 5211), 0xE938D70 (5200, 5216 next block). No description reads. Lines 5205-5209 are misdecodes of non-code bytes — a cold-region anomaly, not a tag case [I].

## Block 25 — listing lines 5213..5252 (40 lines)

### lines 5213..5252 (0x6670CAA..0x6670D80)
Failure-handler tail: `lea rcx,[0x567DBA0] / call 0xE935740 / lea rcx,[0x129CA5E0] / call 0xE938D70 / jmp 0x666B0D9`; then `lea rcx,[0x129CA5E0] / call 0xE938CB0 / cmp [0x129CA5E0],0xFFFFFFFF / jne 0x666B2A5`; else `lea rcx,[0x129CA568] / call 0x567DB00 / lea rcx,[0x567DBA0] / call 0xE935740 / lea rcx,[0x129CA5E0] / call 0xE938D70 / jmp 0x666B2A5`. Then `lea rcx,[0x129F9248] / call 0xE938CB0 / cmp [0x129F9248],0xFFFFFFFF / jne 0x666D9C0`; else `lea rcx,[0x129F9228] / lea rdx,[0xF540FFD] / call 0x79580 / lea rcx,[0x66E59F0] / call 0xE935740 / lea rcx,[0x129F9248] / call 0xE938D70 / jmp 0x666D9C0`. Then `call 0x75740 / call 0x75740`; `lea rcx,[0x129FA0F0] / call 0xE938CB0 / cmp [0x129FA0F0],0xFFFFFFFF / jne 0x666B6AA`; `lea rdx,[0xF5C6B83] / lea rsi,[rbp+0x3F0]` (continues past line 5252) [V]. Every jump target is an earlier body address (< 0x666FBC0).

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5213 | 0x6670CAA | `lea rcx,[0x567DBA0]` | rcx = code address 0x567DBA0 [V] |
| 5214 | 0x6670CB1 | `call 0xE935740` | call 0xE935740 [V] |
| 5215 | 0x6670CB6 | `lea rcx,[0x129CA5E0]` | rcx = global addr [V] |
| 5216 | 0x6670CBD | `call 0xE938D70` | call 0xE938D70 [V] |
| 5217 | 0x6670CC2 | `jmp 0x666B0D9` | jmp back into body (0x666B0D9) [V] |
| 5218 | 0x6670CC7 | `lea rcx,[0x129CA5E0]` | rcx = global addr [V] |
| 5219 | 0x6670CCE | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5220 | 0x6670CD3 | `cmp dword ptr [0x129CA5E0],0xFFFFFFFF` | global vs -1 [V] |
| 5221 | 0x6670CDA | `jne 0x666B2A5` | jmp back into body (0x666B2A5) [V] |
| 5222 | 0x6670CE0 | `lea rcx,[0x129CA568]` | rcx = global addr [V] |
| 5223 | 0x6670CE7 | `call 0x567DB00` | call 0x567DB00 [V] |
| 5224 | 0x6670CEC | `nop` | — |
| 5225 | 0x6670CED | `lea rcx,[0x567DBA0]` | rcx = code address 0x567DBA0 [V] |
| 5226 | 0x6670CF4 | `call 0xE935740` | call 0xE935740 [V] |
| 5227 | 0x6670CF9 | `lea rcx,[0x129CA5E0]` | rcx = global addr [V] |
| 5228 | 0x6670D00 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5229 | 0x6670D05 | `jmp 0x666B2A5` | jmp back into body (0x666B2A5) [V] |
| 5230 | 0x6670D0A | `lea rcx,[0x129F9248]` | rcx = global addr [V] |
| 5231 | 0x6670D11 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5232 | 0x6670D16 | `cmp dword ptr [0x129F9248],0xFFFFFFFF` | global vs -1 [V] |
| 5233 | 0x6670D1D | `jne 0x666D9C0` | jmp back into body (0x666D9C0) [V] |
| 5234 | 0x6670D23 | `lea rcx,[0x129F9228]` | rcx = global addr [V] |
| 5235 | 0x6670D2A | `lea rdx,[0xF540FFD]` | rdx = string pointer 0xF540FFD [V] |
| 5236 | 0x6670D31 | `call 0x79580` | call 0x79580 [V] |
| 5237 | 0x6670D36 | `nop` | — |
| 5238 | 0x6670D37 | `lea rcx,[0x66E59F0]` | rcx = code address 0x66E59F0 [V] |
| 5239 | 0x6670D3E | `call 0xE935740` | call 0xE935740 [V] |
| 5240 | 0x6670D43 | `lea rcx,[0x129F9248]` | rcx = global addr [V] |
| 5241 | 0x6670D4A | `call 0xE938D70` | call 0xE938D70 [V] |
| 5242 | 0x6670D4F | `jmp 0x666D9C0` | jmp back into body (0x666D9C0) [V] |
| 5243 | 0x6670D54 | `call 0x75740` | call 0x75740 [V] |
| 5244 | 0x6670D59 | `nop` | — |
| 5245 | 0x6670D5A | `call 0x75740` | call 0x75740 [V] |
| 5246 | 0x6670D5F | `nop` | — |
| 5247 | 0x6670D60 | `lea rcx,[0x129FA0F0]` | rcx = global addr [V] |
| 5248 | 0x6670D67 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5249 | 0x6670D6C | `cmp dword ptr [0x129FA0F0],0xFFFFFFFF` | global vs -1 [V] |
| 5250 | 0x6670D73 | `jne 0x666B6AA` | jmp back into body (0x666B6AA) [V] |
| 5251 | 0x6670D79 | `lea rdx,[0xF5C6B83]` | rdx = string pointer 0xF5C6B83 [V] |
| 5252 | 0x6670D80 | `lea rsi,[rbp+0x3F0]` | rsi = stack addr [V] |

**Branch exits:** 0x666B0D9 (5217), 0x666B2A5 (5221, 5229), 0x666D9C0 (5233, 5242), 0x666B6AA (5250), fall-through to line 5253 (next block). Calls: 0xE935740 (5214, 5226, 5239), 0xE938D70 (5216, 5228, 5241), 0xE938CB0 (5219, 5231, 5248), 0x567DB00 (5223), 0x79580 (5236), 0x75740 (5243, 5245). No description reads. All jump targets back into tag-7 body — failure handlers [I].

## Block 26 — listing lines 5253..5292 (40 lines)

### lines 5253..5292 (0x6670D87..0x6670E4B)
FNV-1a hash setup over string at [rbp+0x3F0] (rcx basis 0xCBF29CE484222325, r9 prime 0x100000001B3, length rdx from [rbp+0x400], small-string branch via [rbp+0x408]<=0x10), then global check `call 0xE938CB0 / cmp [0x129FA100],0xFFFFFFFF / jne 0x666B6CF` (jump back into tag-7 body proper), `call 0x79580` to hash, repeat for next string 0xF5A0883 [V]. All `jmp 0x666XXXX` targets are earlier body addresses (< 0x666FBC0) — continuation back into the body, not other tag cases [I].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5253 | 0x6670D87 | `mov rcx,rsi` | rcx = rsi [V] |
| 5254 | 0x6670D8A | `call 0x79580` | call 0x79580 (hash helper) [V] |
| 5255 | 0x6670D8F | `nop` | — |
| 5256 | 0x6670D90 | `mov rdx,[rbp+0x400]` | rdx = string length [V] |
| 5257 | 0x6670D97 | `cmp qword ptr [rbp+0x408],0x10` | small-string threshold [V] |
| 5258 | 0x6670D9F | `jb short 0x6670DA8` | branch exit 0x6670DA8 [V] |
| 5259 | 0x6670DA1 | `mov rsi,[rbp+0x3F0]` | rsi = string pointer (heap case) [V] |
| 5260 | 0x6670DA8 | `test rdx,rdx` | length == 0? [V] |
| 5261 | 0x6670DAB | `je 0x6671192` | branch exit 0x6671192 [V] |
| 5262 | 0x6670DB1 | `mov eax,edx` | — |
| 5263 | 0x6670DB3 | `and eax,3` | — |
| 5264 | 0x6670DB6 | `cmp rdx,4` | length vs 4 [V] |
| 5265 | 0x6670DBA | `jae 0x66711F9` | branch exit 0x66711F9 (aligned hash path) [V] |
| 5266 | 0x6670DC0 | `mov rcx,0xCBF29CE484222325` | FNV basis [V] |
| 5267 | 0x6670DCA | `xor r8d,r8d` | index i = 0 [V] |
| 5268 | 0x6670DCD | `jmp 0x6671255` | branch exit 0x6671255 (hash loop) [V] |
| 5269 | 0x6670DD2 | `lea rcx,[0x129FA100]` | rcx = global addr [V] |
| 5270 | 0x6670DD9 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5271 | 0x6670DDE | `cmp dword ptr [0x129FA100],0xFFFFFFFF` | global vs -1 [V] |
| 5272 | 0x6670DE5 | `jne 0x666B6CF` | **jmp back into tag-7 body (0x666B6CF < 0x666FBC0)** [V] |
| 5273 | 0x6670DEB | `lea rdx,[0xF5A0883]` | rdx = string pointer 0xF5A0883 [V] |
| 5274 | 0x6670DF2 | `lea rsi,[rbp+0x3F0]` | rsi = string [V] |
| 5275 | 0x6670DF9 | `mov rcx,rsi` | rcx = rsi [V] |
| 5276 | 0x6670DFC | `call 0x79580` | call 0x79580 (hash helper) [V] |
| 5277 | 0x6670E01 | `nop` | — |
| 5278 | 0x6670E02 | `mov rdx,[rbp+0x400]` | rdx = string length [V] |
| 5279 | 0x6670E09 | `cmp qword ptr [rbp+0x408],0x10` | small-string threshold [V] |
| 5280 | 0x6670E11 | `jb short 0x6670E1A` | branch exit 0x6670E1A [V] |
| 5281 | 0x6670E13 | `mov rsi,[rbp+0x3F0]` | rsi = string pointer [V] |
| 5282 | 0x6670E1A | `test rdx,rdx` | length == 0? [V] |
| 5283 | 0x6670E1D | `je 0x66711A1` | branch exit 0x66711A1 [V] |
| 5284 | 0x6670E23 | `mov eax,edx` | — |
| 5285 | 0x6670E25 | `and eax,3` | — |
| 5286 | 0x6670E28 | `cmp rdx,4` | length vs 4 [V] |
| 5287 | 0x6670E2C | `jae 0x66712A8` | branch exit 0x66712A8 [V] |
| 5288 | 0x6670E32 | `mov rcx,0xCBF29CE484222325` | FNV basis [V] |
| 5289 | 0x6670E3C | `xor r8d,r8d` | index i = 0 [V] |
| 5290 | 0x6670E3F | `jmp 0x6671304` | branch exit 0x6671304 (hash loop) [V] |
| 5291 | 0x6670E44 | `lea rcx,[0x129FA150]` | rcx = global addr [V] |
| 5292 | 0x6670E4B | `call 0xE938CB0` | call 0xE938CB0 [V] |

**Branch exits:** 0x6670DA8 (5258), 0x6671192 (5261), 0x66711F9 (5265), 0x6671255 (5268), 0x666B6CF (5272), 0x6670E1A (5280), 0x66711A1 (5283), 0x66712A8 (5287), 0x6671304 (5290). Calls: 0x79580 (5254, 5276), 0xE938CB0 (5270, 5292). No description reads.

## Block 27 — listing lines 5293..5332 (40 lines)

### lines 5293..5332 (0x6670E50..0x6670F1F)
Same hash-continuation pattern: `cmp [0x129FA150],0xFFFFFFFF / jne 0x666C91E`, hash string 0xF5C6BAE via 0x79580; then length dispatch to 0x6671357; `cmp [0x129FA160],0xFFFFFFFF / jne 0x666C943`, hash string 0xF563982, length dispatch to 0x66713FF [V]. All body jumps go back below 0x666FBC0 [I].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5293 | 0x6670E50 | `cmp dword ptr [0x129FA150],0xFFFFFFFF` | global vs -1 [V] |
| 5294 | 0x6670E57 | `jne 0x666C91E` | **jmp back into body (0x666C91E)** [V] |
| 5295 | 0x6670E5D | `lea rdx,[0xF5C6BAE]` | rdx = string pointer 0xF5C6BAE [V] |
| 5296 | 0x6670E64 | `lea rsi,[rbp+0x3F0]` | rsi = string [V] |
| 5297 | 0x6670E6B | `mov rcx,rsi` | rcx = rsi [V] |
| 5298 | 0x6670E6E | `call 0x79580` | call 0x79580 (hash helper) [V] |
| 5299 | 0x6670E73 | `nop` | — |
| 5300 | 0x6670E74 | `mov rdx,[rbp+0x400]` | rdx = string length [V] |
| 5301 | 0x6670E7B | `cmp qword ptr [rbp+0x408],0x10` | threshold [V] |
| 5302 | 0x6670E83 | `jb short 0x6670E8C` | branch exit 0x6670E8C [V] |
| 5303 | 0x6670E85 | `mov rsi,[rbp+0x3F0]` | rsi = string pointer [V] |
| 5304 | 0x6670E8C | `test rdx,rdx` | length == 0? [V] |
| 5305 | 0x6670E8F | `je 0x66711B0` | branch exit 0x66711B0 [V] |
| 5306 | 0x6670E95 | `mov eax,edx` | — |
| 5307 | 0x6670E97 | `and eax,3` | — |
| 5308 | 0x6670E9A | `cmp rdx,4` | length vs 4 [V] |
| 5309 | 0x6670E9E | `jae 0x6671357` | branch exit 0x6671357 [V] |
| 5310 | 0x6670EA4 | `mov rcx,0xCBF29CE484222325` | FNV basis [V] |
| 5311 | 0x6670EAE | `xor r8d,r8d` | index i = 0 [V] |
| 5312 | 0x6670EB1 | `jmp 0x66713B3` | branch exit 0x66713B3 (hash loop) [V] |
| 5313 | 0x6670EB6 | `lea rcx,[0x129FA160]` | rcx = global addr [V] |
| 5314 | 0x6670EBD | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5315 | 0x6670EC2 | `cmp dword ptr [0x129FA160],0xFFFFFFFF` | global vs -1 [V] |
| 5316 | 0x6670EC9 | `jne 0x666C943` | **jmp back into body (0x666C943)** [V] |
| 5317 | 0x6670ECF | `lea rdx,[0xF563982]` | rdx = string pointer 0xF563982 [V] |
| 5318 | 0x6670ED6 | `lea rsi,[rbp+0x3F0]` | rsi = string [V] |
| 5319 | 0x6670EDD | `mov rcx,rsi` | rcx = rsi [V] |
| 5320 | 0x6670EE0 | `call 0x79580` | call 0x79580 (hash helper) [V] |
| 5321 | 0x6670EE5 | `nop` | — |
| 5322 | 0x6670EE6 | `mov rdx,[rbp+0x400]` | rdx = string length [V] |
| 5323 | 0x6670EED | `cmp qword ptr [rbp+0x408],0x10` | threshold [V] |
| 5324 | 0x6670EF5 | `jb short 0x6670EFE` | branch exit 0x6670EFE [V] |
| 5325 | 0x6670EF7 | `mov rsi,[rbp+0x3F0]` | rsi = string pointer [V] |
| 5326 | 0x6670EFE | `test rdx,rdx` | length == 0? [V] |
| 5327 | 0x6670F01 | `je 0x66711BF` | branch exit 0x66711BF [V] |
| 5328 | 0x6670F07 | `mov eax,edx` | — |
| 5329 | 0x6670F09 | `and eax,3` | — |
| 5330 | 0x6670F0C | `cmp rdx,4` | length vs 4 [V] |
| 5331 | 0x6670F10 | `jae 0x66713FF` | branch exit 0x66713FF [V] |
| 5332 | 0x6670F16 | `mov rcx,0xCBF29CE484222325` | FNV basis [V] |

**Branch exits:** 0x666C91E (5294), 0x6670E8C (5302), 0x66711B0 (5305), 0x6671357 (5309), 0x66713B3 (5312), 0x666C943 (5316), 0x6670EFE (5324), 0x66711BF (5327), 0x66713FF (5331). Calls: 0x79580 (5298, 5320), 0xE938CB0 (5314). No description reads.

## Block 28 — listing lines 5333..5372 (40 lines)

### lines 5333..5372 (0x6670F20..0x6670FF0)
Hash loop for previous string (jmp 0x667145B), then `cmp [0x129FA170],0xFFFFFFFF / jne 0x666C968`, hash string 0xF516F7D via 0x79580, length dispatch to 0x66714A7; then `cmp [0x129F9270],0xFFFFFFFF / jne 0x666DA01`, hash string 0xF7CA278 via `call 0x79580` with `lea rcx,[0x66E5A80] / call 0xE935740` pair, `jmp 0x666DA01`; then `call 0x75720 / lea rcx,[0x129FA128] / call 0xE938CB0` [V]. All body jumps back below 0x666FBC0 [I].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5333 | 0x6670F20 | `xor r8d,r8d` | index i = 0 [V] |
| 5334 | 0x6670F23 | `jmp 0x667145B` | branch exit 0x667145B (hash loop) [V] |
| 5335 | 0x6670F35 | `lea rcx,[0x129FA170]` | rcx = global addr [V] |
| 5336 | 0x6670F3C | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5337 | 0x6670F44 | `cmp dword ptr [0x129FA170],0xFFFFFFFF` | global vs -1 [V] |
| 5338 | 0x6670F4B | `jne 0x666C968` | **jmp back into body (0x666C968)** [V] |
| 5339 | 0x6670F51 | `lea rdx,[0xF516F7D]` | rdx = string pointer 0xF516F7D [V] |
| 5340 | 0x6670F58 | `lea rsi,[rbp+0x3F0]` | rsi = string [V] |
| 5341 | 0x6670F5F | `mov rcx,rsi` | rcx = rsi [V] |
| 5342 | 0x6670F62 | `call 0x79580` | call 0x79580 (hash helper) [V] |
| 5343 | 0x6670F67 | `nop` | — |
| 5344 | 0x6670F68 | `mov rdx,[rbp+0x400]` | rdx = string length [V] |
| 5345 | 0x6670F6F | `cmp qword ptr [rbp+0x408],0x10` | threshold [V] |
| 5346 | 0x6670F77 | `jb short 0x6670F70` | branch exit 0x6670F70 [V] |
| 5347 | 0x6670F79 | `mov rsi,[rbp+0x3F0]` | rsi = string pointer [V] |
| 5348 | 0x6670F80 | `test rdx,rdx` | length == 0? [V] |
| 5349 | 0x6670F83 | `je 0x66711CE` | branch exit 0x66711CE [V] |
| 5350 | 0x6670F89 | `mov eax,edx` | — |
| 5351 | 0x6670F8B | `and eax,3` | — |
| 5352 | 0x6670F8E | `cmp rdx,4` | length vs 4 [V] |
| 5353 | 0x6670F96 | `jae 0x66714A7` | branch exit 0x66714A7 [V] |
| 5354 | 0x6670F9C | `mov rcx,0xCBF29CE484222325` | FNV basis [V] |
| 5355 | 0x6670FA6 | `xor r8d,r8d` | index i = 0 [V] |
| 5356 | 0x6670FA9 | `jmp 0x6671503` | branch exit 0x6671503 (hash loop) [V] |
| 5357 | 0x6670FAF | `lea rcx,[0x129F9270]` | rcx = global addr [V] |
| 5358 | 0x6670FB6 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5359 | 0x6670FBD | `cmp dword ptr [0x129F9270],0xFFFFFFFF` | global vs -1 [V] |
| 5360 | 0x6670FC4 | `jne 0x666DA01` | **jmp back into body (0x666DA01)** [V] |
| 5361 | 0x6670FCA | `lea rcx,[0x129F9250]` | rcx = global addr [V] |
| 5362 | 0x6670FD1 | `lea rdx,[0xF7CA278]` | rdx = string pointer 0xF7CA278 [V] |
| 5363 | 0x6670FD8 | `call 0x79580` | call 0x79580 (hash helper) [V] |
| 5364 | 0x6670FDD | `nop` | — |
| 5365 | 0x6670FDE | `lea rcx,[0x66E5A80]` | rcx = code address 0x66E5A80 [V] |
| 5366 | 0x6670FE5 | `call 0xE935740` | call 0xE935740 [V] |
| 5367 | 0x6670FEC | `lea rcx,[0x129F9270]` | rcx = global addr [V] |
| 5368 | 0x6670FF3 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5369 | 0x6670FFA | `jmp 0x666DA01` | **jmp back into body (0x666DA01)** [V] |
| 5370 | 0x6670FFF | `call 0x75720` | call 0x75720 [V] |
| 5371 | 0x6671006 | `lea rcx,[0x129FA128]` | rcx = global addr [V] |
| 5372 | 0x667100D | `call 0xE938CB0` | call 0xE938CB0 [V] |

**Branch exits:** 0x667145B (5334), 0x666C968 (5338), 0x6670F70 (5346), 0x66711CE (5349), 0x66714A7 (5353), 0x6671503 (5356), 0x666DA01 (5360, 5369), 0x666CFE1 (next block). Calls: 0xE938CB0 (5336, 5358, 5372), 0x79580 (5342, 5363), 0xE935740 (5366), 0xE938D70 (5368), 0x75720 (5370). No description reads.

## Block 29 — listing lines 5373..5412 (40 lines)

### lines 5373..5412 (0x6670FF5..0x66710CC)
`cmp [0x129FA128],0xFFFFFFFF / jne 0x666CFE1`, hash string 0xF563982 via 0x79580, length dispatch to 0x667154F; `cmp [0x129CA5E0],0xFFFFFFFF / jne 0x666DD67`, then `lea rcx,[0x129CA568] / call 0x567DB00 / lea rcx,[0x567DBA0] / call 0xE935740 / lea rcx,[0x129CA5E0] / call 0xE938D70 / mov r15,[rbp+0x650] / jmp 0x666DD67`; then repeat global check `jne 0x666FE83` [V]. All body jumps back below 0x666FBC0 [I].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5373 | 0x6670FF5 | `cmp dword ptr [0x129FA128],0xFFFFFFFF` | global vs -1 [V] |
| 5374 | 0x6670FFC | `jne 0x666CFE1` | **jmp back into body (0x666CFE1)** [V] |
| 5375 | 0x6671002 | `lea rdx,[0xF563982]` | rdx = string pointer 0xF563982 [V] |
| 5376 | 0x6671009 | `lea rsi,[rbp+0x3F0]` | rsi = string [V] |
| 5377 | 0x6671010 | `mov rcx,rsi` | rcx = rsi [V] |
| 5378 | 0x6671013 | `call 0x79580` | call 0x79580 (hash helper) [V] |
| 5379 | 0x6671018 | `nop` | — |
| 5380 | 0x6671019 | `mov rdx,[rbp+0x400]` | rdx = string length [V] |
| 5381 | 0x6671020 | `cmp qword ptr [rbp+0x408],0x10` | threshold [V] |
| 5382 | 0x6671028 | `jb short 0x6671031` | branch exit 0x6671031 [V] |
| 5383 | 0x667102A | `mov rsi,[rbp+0x3F0]` | rsi = string pointer [V] |
| 5384 | 0x6671031 | `test rdx,rdx` | length == 0? [V] |
| 5385 | 0x6671034 | `je 0x66711DD` | branch exit 0x66711DD [V] |
| 5386 | 0x667103A | `mov eax,edx` | — |
| 5387 | 0x667103C | `and eax,3` | — |
| 5388 | 0x667103F | `cmp rdx,4` | length vs 4 [V] |
| 5389 | 0x6671043 | `jae 0x667154F` | branch exit 0x667154F [V] |
| 5390 | 0x6671049 | `mov rcx,0xCBF29CE484222325` | FNV basis [V] |
| 5391 | 0x6671053 | `xor r8d,r8d` | index i = 0 [V] |
| 5392 | 0x6671056 | `jmp 0x66715AB` | branch exit 0x66715AB (hash loop) [V] |
| 5393 | 0x667105B | `lea rcx,[0x129CA5E0]` | rcx = global addr [V] |
| 5394 | 0x6671062 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5395 | 0x6671067 | `cmp dword ptr [0x129CA5E0],0xFFFFFFFF` | global vs -1 [V] |
| 5396 | 0x667106E | `jne 0x666DD67` | **jmp back into body (0x666DD67)** [V] |
| 5397 | 0x6671074 | `lea rcx,[0x129CA568]` | rcx = global addr [V] |
| 5398 | 0x667107B | `call 0x567DB00` | call 0x567DB00 [V] |
| 5399 | 0x6671080 | `nop` | — |
| 5400 | 0x6671081 | `lea rcx,[0x567DBA0]` | rcx = code address 0x567DBA0 [V] |
| 5401 | 0x6671088 | `call 0xE935740` | call 0xE935740 [V] |
| 5402 | 0x667108D | `lea rcx,[0x129CA5E0]` | rcx = global addr [V] |
| 5403 | 0x6671094 | `call 0xE938D70` | call 0xE938D70 [V] |

**Branch exits:** 0x666CFE1 (5374), 0x6671031 (5382), 0x66711DD (5385), 0x667154F (5389), 0x66715AB (5392), 0x666DD67 (5396, next line). Calls: 0x79580 (5378), 0xE938CB0 (5394), 0x567DB00 (5398), 0xE935740 (5401), 0xE938D70 (5403). No description reads.

## NEXT
Blocks 1-29 written (lines 4253..5412). Next block to append: 5413..5452.
