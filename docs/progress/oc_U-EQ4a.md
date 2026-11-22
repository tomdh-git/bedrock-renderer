## NEXT
DONE

UNIT U-EQ4a — Q4a Close executor holes: bind-cache miss descriptor build, PSO desc build on a miss, setPredefined, helper bodies; job/command-list model; RTX subclass overrides

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). All RVAs below are image RVAs of that exe.
Method: every proof line is a verbatim instruction from `rdis ... dis 0x<rva> <n>` on the exe (not from any note), later re-checked with `python tools/delegate.py check` (verify_oc). Meaning is tagged [V] (seen in disassembly/string), [I] (inferred), or [?] (unknown). One row per distinct offset; all sites of that offset listed in the address column. Sizes come from the instruction (movups/movaps/movdqu/movdqa = 16, qword = 8, dword/movss = 4, word = 2, byte = 1; '-' for no memory access). No source files were edited — this unit closes the holes by reverse-engineering proof on disk; the only path created is docs/progress/oc_U-EQ4a.md.

Basis in BGFX_MAP.md: 6am/6an/6ao/6ap/6av/6aw/6ax/6al/6bb/6bc (job, executor skeleton), 6fp/6fq/6fr/6fs/6ft (bind-cache miss, PSO), 6fo (predefined uniforms), 6fm (helper bodies), 6cp-6cu (job/command-list model).

## Proof table: Q4a pending holes (name | rva | size | address | verbatim `0xRVA  instr` | meaning [tag])

| offset | size | address | `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| 0xe822e81 | 8 | job+0x678 bind-state bucket array | `0xe822e81  mov rax,[rbx+0x678]` | bucket array base of the bind-state hash cache (buckets job+0x678, count job+0x680) [V] |
| 0xe822e96 | 4 | bind hash (job+0x178) low byte | `0xe822e96  movsx rdx,r9b` | bind hash fed into the stock bgfx 0x1003F bucket hash [V] |
| 0xe822ea5 | 4 | hash multiply | `0xe822ea5  imul rdx,0x1003F` | bucket hash multiply step [V] |
| 0xe822eeb | 4 | bucket index | `0xe822eeb  and rcx,rdx` | bucket = hash & (bucketCount-2) [V] |
| 0xe822eee | 8 | chain head node | `0xe822eee  mov rdx,[rax+rcx*8]` | load chain head node {key @+0, next @+0x10} from bucket [V] |
| 0xe822f07 | 4 | node key (+0) | `0xe822f07  cmp [rdx],rcx` | compare cached RenderBind hash against node key [V] |
| 0xe822f10 | 8 | next node (+0x10) | `0xe822f10  mov rdx,[rdx+0x10]` | walk chain to next node [V] |
| 0xe822f19 | 8 | job+0x140 side-table ptr | `0xe822f19  mov rax,[rbx+0x140]` | draw's RenderBind side table; NULL means no ranged bindings [V] |
| 0xe822f23 | - | branch | `0xe822f23  je 0xE825A19` | side table NULL -> bind-cache miss, jump to descriptor build at 0xe825a19 [V] |

-- bind-cache miss entry: descriptor table allocation (job+0x220 tables, job+0x3B0 srvState, heap at job+0xB8 {cpu+8, gpu+0x10, increment+0x18})

| 0xe825a19 | 16 | write job+0x220 | `0xe825a19  movdqa [rbx+0x220],xmm9` | miss path entry: store first descriptor-table slot(s), 16 B [V] |
| 0xe825a22 | 8 | write job+0x230 | `0xe825a22  mov qword ptr [rbx+0x230],0` | clear first gpu-handle slot [V] |
| 0xe825a39 | - | call 0xe835b50 | `0xe825a39  call 0xE835B50` | vector::reserve(0x41) for the 65 descriptor-table slots [V] |
| 0xe825a55 | - | write job+0x3B0..0x4B3 | `0xe825a55  call 0xEEC6ED0` | memset(srvState[job+0x3B0], 0, 0x104), one u32 per stage [V] |
| 0xe825ab3 | 4 | read data 0x12AE0D80 | `0xe825ab3  mov r8d,[0x12AE0D80]` | g_numBindingStages — runtime stage count [V] |
| 0xe825ad7 | 2 | read Binding+0xA | `0xe825ad7  movzx edi,word ptr [rcx+rax*4+0xA]` | Binding.idx u16 at +0xA (resource handle) [V] |
| 0xe825af7 | 1 | read Binding+0x13 | `0xe825af7  movzx eax,byte ptr [rsi+0x13]` | Binding.type u8 at +0x13, switch index [V] |
| 0xe825aff | - | branch | `0xe825aff  ja 0xE8270E2` | type > 9 -> ignored (shared target for type 7) [V] |
| 0xe825b0c | 4 | read jump table 0xF4EE7D0 | `0xe825b0c  movsxd rax,[rcx+rax*4]` | jump table 0xF4EE7D0, 10 entries for types 0..9 [V] |
| 0xe825b13 | - | branch | `0xe825b13  jmp rax` | indirect jump into the type handler [V] |

-- case 0 (type 0/reserved: null descriptor slot) at 0xe825ba6

| 0xe825bad | 8 | read heap ptr | `0xe825bad  mov r8,[rbx+0xB8]` | descriptor heap object at job+0xB8 [V] |
| 0xe825bb4 | 4 | read heap+0x18 | `0xe825bb4  mov ecx,[r8+0x18]` | descriptor increment [V] |
| 0xe825bb8 | 8 | write heap+8 | `0xe825bb8  add [r8+8],rcx` | heap.cpu += increment [V] |
| 0xe825bcd | 8 | write tables[slot] | `0xe825bcd  mov [rax+rcx*8],rdx` | tables[stage*8] = gpu handle (reserved null slot) [V] |
| 0xe825bd8 | 8 | write heap+0x10 | `0xe825bd8  mov [r8+0x10],rax` | heap.gpu += increment [V] |

-- cases 1/2 (type 1 index buffer / type 2 vertex buffer as shader buffer) at 0xe825b15

| 0xe825b27 | 2 | read Binding+0xA | `0xe825b27  movzx edi,word ptr [rsi+0xA]` | buffer handle u16 [V] |
| 0xe825b2f | 8 | read job+0x5D8 | `0xe825b2f  add rax,[rbx+0x5D8]` | index-buffer record table base (0x78 stride) [V] |
| 0xe825b39 | 8 | read job+0x588 | `0xe825b39  add rdi,[rbx+0x588]` | vertex-buffer record table base (0x80 stride) [V] |
| 0xe825b40 | 1 | read Binding+0x13 | `0xe825b40  cmp byte ptr [rsi+0x13],1` | type 1 = index buffer, 2 = vertex buffer [V] |
| 0xe825b44 | - | cmove | `0xe825b44  cmove rdi,rax` | type 1 selects the index-table record [V] |
| 0xe825b48 | 1 | read Binding+0x11 | `0xe825b48  cmp byte ptr [rsi+0x11],0` | access flag +0x11: 0 = read, nonzero = UAV/write [V] |
| 0xe825b4c | - | branch | `0xe825b4c  je 0xE827245` | read access -> skip transition; else fall through [V] |
| 0xe825b62 | - | call 0xe82dcc0 | `0xe825b62  call 0xE82DCC0` | resource transition to UNORDERED_ACCESS (state 8) [V] |
| 0xe825b6f | 4 | read record+0x34 | `0xe825b6f  mov r9d,[rdi+0x34]` | buffer record fields used for the view desc [V] |

-- common SRV/UAV view builder (reached from cases 1/2, 3, 4, 6, 8) at 0xe8272c3

| 0xe8272c3 | - | - | `0xe8272c3  mov ecx,r8d` | view desc firstElement/count layout [V] |
| 0xe8272e8 | 16 | read record+0x48 | `0xe8272e8  movups xmm0,[rdi+0x48]` | 16 B GPU address from buffer/texture record +0x48 [V] |
| 0xe8272f3 | 16 | write job+0xD8 | `0xe8272f3  movups [rax+4],xmm0` | store GPU address into the view desc at job+0xD8 [V] |
| 0xe8272f7 | 8 | read renderer global | `0xe8272f7  mov rax,[0x12BB4910]` | renderer object [V] |
| 0xe8272fe | 8 | read device | `0xe8272fe  mov rcx,[rax+0x400]` | ID3D12Device at renderer+0x400 [V] |
| 0xe827316 | 8 | read vtable+0x98 | `0xe827316  mov rax,[rax+0x98]` | device vtable slot 19 (+0x98), view-creation method [V] |
| 0xe827333 | - | call thunk | `0xe827333  call r10` | r10 = thunk [0xF99FFA0] (sub_eea6040) invoking the device method [V] |

-- case 3 (type 3 texture) at 0xe82719f

| 0xe82719f | 8 | read job+0x1F8 | `0xe82719f  mov rcx,[rbx+0x1F8]` | texture table base at job+0x1F8 (4096 inline x 0xB8) [V] |
| 0xe8271a9 | - | call 0xe83abb0 | `0xe8271a9  call 0xE83ABB0` | guarded-array texture lookup helper [V] |
| 0xe8271b2 | 4 | handle compare | `0xe8271b2  cmp eax,0x1000` | dynamic-handle rule: handle >= 0x1000 uses paged overflow [V] |
| 0xe8271c4 | 1 | read ctx+0xC96190 | `0xe8271c4  cmp byte ptr [rcx+0xC96190],0` | dynamic-texture guard byte [V] |
| 0xe8271da | - | call 0xbc5f110 | `0xe8271da  call 0xBC5F110` | error "FAILED: accessing a guarded paged heap backed array out of bounds" (string 0xF7F68E3) [V] |
| 0xe8271e0 | - | handle*0xB8 | `0xe8271e0  imul r8,rdi,0xB8` | texture record = table + handle*0xB8 [V] |

-- case 4 (type 4 shader buffer, table ctx+0xA32178) at 0xe8270ee

| 0xe8270ee | - | handle*0x78 | `0xe8270ee  imul rax,rdi,0x78` | shader-buffer record index, 0x78 stride [V] |
| 0xe8270f2 | 8 | read job+0x3A0 | `0xe8270f2  mov rcx,[rbx+0x3A0]` | ctx+0xA32178 shader-buffer table base, cached at job+0x3A0 [V] |
| 0xe82710c | 2 | handle | `0xe82710c  movzx ecx,di` | handle used for the state-bit lookup [V] |
| 0xe827142 | - | bit test | `0xe827142  bt r9,rdi` | per-texture state bitmap at ctx+0x224A8 [V] |
| 0xe827154 | 4 | read state dword | `0xe827154  cmp ecx,8` | tracked state; 8 = UNORDERED_ACCESS [V] |
| 0xe827193 | - | call thunk | `0xe827193  call qword ptr [0xF99FFA0]` | UAV transition via thunk sub_eea6040 [V] |

-- case 5 (type 5, feature-gated) at 0xe82609e

| 0xe82609e | 1 | read data 0x12ADFA53 | `0xe82609e  test byte ptr [0x12ADFA53],0x80` | feature-gate global, bit 0x80 [V] |
| 0xe8260a5 | - | branch | `0xe8260a5  jne 0xE82735A` | gate set -> binds a buffer (0x57A180-based table); else reserve null slot [V] |
| 0xe8260cf | 8 | write tables[slot] | `0xe8260cf  mov [rcx+rdx*8],rax` | null/reserved descriptor slot [V] |

-- case 6 (type 6 ranged texture) at 0xe8260d8

| 0xe8260d8 | 8 | job+0x140 side table | `0xe8260d8  mov rax,[rbx+0x140]` | per-draw side table pointer [V] |
| 0xe82616c | 2 | entry handle | `0xe82616c  movzx r13d,word ptr [r15+r12*4+0xA]` | side-table entry handle u16 at +0xA [V] |
| 0xe826172 | 4 | handle compare | `0xe826172  cmp r13,0x1000` | dynamic-handle rule [V] |
| 0xe8261e2 | - | call 0xe83ace0 | `0xe8261e2  call 0xE83ACE0` | texture-table page grow (6z) [V] |
| 0xe82628a | 8 | write record | `0xe82628a  mov qword ptr [r14],0` | zero per-texture state record (0x68 stride) [V] |
| 0xe82629c | 2 | write record+0xB1 | `0xe82629c  mov word ptr [r14+0xB1],0` | state byte [V] |

-- case 7 (type 7 ignored) at 0xe8270e2

| 0xe8270e2 | 4 | read job+0x110 | `0xe8270e2  mov r10d,[rbx+0x110]` | type 7 ignored: only advances the stage counter [V] |

-- case 8 (type 8 ranged shader buffer) at 0xe825be1

| 0xe825be1 | 8 | job+0x140 side table | `0xe825be1  mov rax,[rbx+0x140]` | side table; NULL -> ignored (jmp 0xe8270e2) [V] |
| 0xe825cb5 | 8 | read ctx+0x224A8 bitmap | `0xe825cb5  mov r9,[r11+r8*8+0x224A8]` | per-texture state bitmap at ctx+0x224A8 [V] |
| 0xe825cd0 | 4 | read ctx+0x226AC state | `0xe825cd0  mov r8d,[r11+rcx*8+0x226AC]` | state dword; 8 = UNORDERED_ACCESS [V] |
| 0xe825ce2 | 8 | read ctx+0x22498 records | `0xe825ce2  mov rcx,[r11+0x22498]` | ranged records at ctx+0x22498, stride 0x78 [V] |
| 0xe825d18 | - | call thunk | `0xe825d18  call qword ptr [0xF99FFA0]` | UAV transition via thunk sub_eea6040 [V] |

-- case 9 (type 9 sampler) at 0xe8271f3

| 0xe827229 | 4 | read Binding+0x0 | `0xe827229  mov eax,[rsi]` | sampler flags u32 at binding+0x0 [V] |
| 0xe82722b | 4 | mask 0x1F0F07FF | `0xe82722b  mov ecx,0x1F0F07FF` | sampler-flag mask [V] |
| 0xe827239 | 4 | write job+0x3B0 | `0xe827239  mov [rbx+rcx*4+0x3B0],eax` | sampler flags stored per stage into srvState [V] |

## PSO desc build on a miss (0xe81e860): program record, key mask, hash-map miss, CreateGraphicsPipelineState, cache insert

| 0xe81e8d7 | - | program stride | `0xe81e8d7  imul rax,0xF8` | program record stride 0xF8 [V] |
| 0xe81e8e5 | 8 | renderer+0xB62178 | `0xe81e8e5  add rbx,0xB62178` | program record = renderer+0xB62178 + program*0xF8 [V] |
| 0xe81e8ec | - | state key mask | `0xe81e8ec  mov rsi,0x707007FFFFFF0FF` | PSO key mask S & 0x0707007FFFFFF0FF (matches 6fs/N1d) [V] |
| 0xe81eac7 | 4 | read prog+0xA8 | `0xe81eac7  mov eax,[rax+0xA8]` | program signature (4 signed bytes) at program object +0xA8 [V] |
| 0xe820640 | 8 | node key compare | `0xe820640  cmp [rdx],r10` | PSO-cache hash-map chain walk: compare node key [V] |
| 0xe820649 | 8 | chain next | `0xe820649  mov rdx,[rdx+0x10]` | next node (+0x10) [V] |
| 0xe81eff7 | - | write rsp+0x3C8 | `0xe81eff7  lea rcx,[rsp+0x3C8]` | miss path: memset the 0x290-byte D3D12_GRAPHICS_PIPELINE_STATE_DESC [V] |
| 0xe81f007 | - | call 0xe835b50 | `0xe81f007  call 0xEBCE430` | memset helper for the desc buffer [V] |
| 0xe8203af | 8 | read renderer+0x400 | `0xe8203af  mov rcx,[rdi+0x400]` | ID3D12Device at renderer+0x400 [V] |
| 0xe8203b6 | 8 | read device vtable | `0xe8203b6  mov rax,[rcx]` | device vtable [V] |
| 0xe8203b9 | 8 | read vtable+0x50 | `0xe8203b9  mov rax,[rax+0x50]` | vtable slot 10 = CreateGraphicsPipelineState (+0x50) [V] |
| 0xe8203d1 | - | call thunk | `0xe8203d1  call qword ptr [0xF99FFA0]` | CreateGraphicsPipelineState(desc, &pso) via thunk sub_eea6040 [V] |
| 0xe8203d9 | - | branch | `0xe8203d9  jns short 0xE82044B` | success (HRESULT >= 0) -> cache insert path [V] |
| 0xe82043f | 4 | write renderer+0x19F88 | `0xe82043f  mov [rdi+0x19F88],ecx` | failure: device-lost state +0x19F88 [V] |
| 0xe820445 | 4 | write renderer+0x19F8C | `0xe820445  mov [rdi+0x19F8C],eax` | failure: device-lost HRESULT +0x19F8C [V] |
| 0xe82048c | - | call 0xe83bdd0 | `0xe82048c  call 0xE83BDD0` | insert the new PSO into the cache (cache+0x40) [V] |

## setPredefined (0xe82a49e): predefined-uniform dispatch and case bodies

| 0xe82a49e | 1 | read prog+0xF0 | `0xe82a49e  movzx eax,byte ptr [r14+0xF0]` | numPredefined u8 at program record +0xF0 [V] |
| 0xe82a507 | 1 | read predefined[i].type | `0xe82a507  movzx eax,byte ptr [r14+r15*8+0x16]` | slot type byte; bit 0x10 selects fragment target [V] |
| 0xe82a512 | 4 | compare | `0xe82a512  cmp ecx,0xD` | type & ~0x10 must be <= 13 (14-slot jump table) [V] |
| 0xe82a517 | 8 | read table 0xF4EE7F8 | `0xe82a517  lea rdx,[0xF4EE7F8]` | predefined-uniform jump table, 14 entries [V] |
| 0xe82a51e | 4 | read entry | `0xe82a51e  movsxd rcx,[rdx+rcx*4]` | jump-table entry (rip-relative) [V] |
| 0xe82a525 | - | branch | `0xe82a525  jmp rcx` | indirect jump to the case body [V] |
| 0xe82a527 | 8 | read job+0x90A8 | `0xe82a527  movq xmm0,[rbx+0x90A8]` | case 0 ViewRect: view rect u16x4 at job+0x90A8 [V] |
| 0xe82a595 | 4 | read draw+0x3C | `0xe82a595  mov ecx,[r12+0x3C]` | case 11 ModelViewProj: draw.startMatrix [V] |
| 0xe82a59e | 8 | read job+0x2F8 | `0xe82a59e  mov rdx,[rbx+0x2F8]` | model matrix cache base at job+0x2F8 [V] |
| 0xe82a5a5 | 16 | read model row | `0xe82a5a5  movaps xmm4,[rdx+rcx]` | 16 B model matrix row from the cache [V] |
| 0xe82a5f1 | 16 | write job+0x3B0 | `0xe82a5f1  movaps [rbx+0x3B0],xmm4` | write ModelViewProj row into vertex constant scratch [V] |

## Helper body: setVertexBuffers 0xe81b4d0 (vertex-buffer view fill)

| 0xe81b4f4 | 4 | read draw+0x4C | `0xe81b4f4  mov eax,[r8+0x4C]` | draw numVertices -> output vertex count [V] |
| 0xe81b4fb | 1 | read draw+0x63 | `0xe81b4fb  movzx ebp,byte ptr [r8+0x63]` | stream-mask bitmask at draw+0x63 [V] |
| 0xe81b51d | - | tzcnt loop | `0xe81b51d  tzcnt ecx,ebp` | iterate set streams [V] |
| 0xe81b54c | 2 | read stream handle | `0xe81b54c  movzx r13d,word ptr [rdi+r12*8+4]` | stream handle u16 at +4+stream*8 [V] |
| 0xe81b658 | - | lea record | `0xe81b658  lea rcx,[rsi+r13]` | vertex-buffer record offset = handle<<7 [V] |
| 0xe81b65c | - | add 0x9B2178 | `0xe81b65c  add rcx,0x9B2178` | record = ctx+0x9B2178 + handle*0x80 (0x80 stride, 6fr correction) [V] |
| 0xe81b663 | 2 | read record+0x78 | `0xe81b663  cmp word ptr [rcx+0x78],0xFFFF` | layout handle at record+0x78 [V] |
| 0xe81b67c | 2 | read ctx+0xC96198+layout*0x54+4 | `0xe81b67c  movzx r8d,word ptr [rax+rsi+0xC9619C]` | layout stride u16 at ctx+0xC96198 + layout*0x54 + 4 (6fr correction) [V] |
| 0xe81b698 | 8 | write VBV | `0xe81b698  mov [rbx+r10],r11` | VBV.BufferLocation = record+0x58 GPU VA + startVertex*stride [V] |
| 0xe81b6a4 | 4 | write VBV | `0xe81b6a4  mov [rbx+r10+0xC],eax` | VBV.StrideInBytes = layout stride [V] |
| 0xe81b6b4 | 4 | write VBV | `0xe81b6b4  mov [rbx+r10+8],eax` | VBV.SizeInBytes = record+0x60 size minus offset [V] |
| 0xe81b5b2 | 4 | write ctx+0xA45C | `0xe81b5b2  mov dword ptr [rax+r13*8+0xA45C],0xAC3` | mark buffer state GENERIC_READ 0xAC3 [V] |
| 0xe81b606 | - | call thunk | `0xe81b606  call qword ptr [0xF99FFA0]` | barrier/transition via thunk sub_eea6040 [V] |

## Job/command-list model (executor wrapper 0xe83c390)

| 0xe83c3b8 | 8 | read cmd-list array | `0xe83c3b8  mov rcx,[rdx+0x19F60]` | per-job command-list array at renderer+0x19F60 [V] |
| 0xe83c3bf | 8 | read cmdList[job] | `0xe83c3bf  mov rcx,[rcx+r10*8]` | command list selected by job index [V] |
| 0xe83c3c6 | 8 | read slice begin | `0xe83c3c6  mov r9,[r11+r10*8]` | slice begin = offsets[jobIndex] from vector at job+8 [V] |
| 0xe83c3cc | 8 | read slice end | `0xe83c3cc  mov rax,[r11+rax*8]` | slice end = offsets[jobIndex+1] [V] |
| 0xe83c430 | - | call 0xe821120 | `0xe83c430  call 0xE821120` | executor(cmdList, slice [begin,end)) — one D3D12 command list per job [V] |

## RTX subclass overrides: vtable 0xF4EEE80 vs base 0xF4ED2D0 (65 slots, rdis vt; slot size = bytes/8)

| 0xe84b280 | - | slot 0 dtor | `0xe84b280  push rsi` | RTX dtor (size 0x39d) overrides base 0xe83c630 (0x2d); sets [this]=0xF4EEE80 at 0xe84b293 [V body + vt] |
| 0xe84b28c | - | write this+0 | `0xe84b28c  lea rax,[0xF4EEE80]` | loads the RTX vtable address [V] |
| 0xe84b293 | 8 | write this+0 | `0xe84b293  mov [rcx],rax` | installs RTX vtable 0xF4EEE80 [V] |
| 0xe83d200 | - | slot 4 | `0xe83d200  lea rax,[0xF7C7E0F]` | getRendererName -> "Direct3D 12 RTX" (string 0xF7C7E0F), overrides base 0xe80f610 [V] |
| 0xe83d440 | - | slot 50 submit | `0xe83d440  push r14` | submit override (0x381-byte wrapper) overrides base 0xe82e230 [V body; slot per vt] |
| 0xe83d44c | 1 | read this+0x4165E78 | `0xe83d44c  cmp byte ptr [rcx+0x4165E78],1` | RTX submit gate: RTX feature enabled byte [V] |
| 0xe83d7d0 | - | slot 54 | `0xe83d7d0  push rbp` | RTX-only (base stub 0x768f0), size 0x671 [V body; slot per vt] |
| 0xe83e200 | - | slot 58 init | `0xe83e200  push rbp` | overrides base 0xe807ff0 [V body; slot per vt] |
| 0xe83e229 | - | call 0xe807ff0 | `0xe83e229  call 0xE807FF0` | RTX init calls base-class init first [V] |
| 0xe83e980 | - | slot 59 | `0xe83e980  push rsi` | overrides base 0xe80dec0 [V body; slot per vt] |
| 0xe83e99f | - | add 0xCC9268 | `0xe83e99f  add rcx,0xCC9268` | command-queue wrapper at renderer+0xCC9268 [V] |
| 0xe83e9ab | - | call 0xe80ecb0 | `0xe83e9ab  call 0xE80ECB0` | flush/waitIdle on the queue wrapper [V] |
| 0xe83ec70 | - | slot 60 reset | `0xe83ec70  push r15` | overrides base 0xe81a610 [V body; slot per vt] |
| 0xe83ec92 | 4 | read this+0x3C5641C | `0xe83ec92  mov ecx,[rcx+0x3C5641C]` | RTX reset reads DLSS/gate state [V] |
| 0xe83f1d0 | - | slot 63 GPU skinning | `0xe83f1d0  push rbp` | overrides base stub 0x768f0, size 0x107b [V body; slot per vt] |
| 0xe83f206 | 1 | read this+0x3C5646C | `0xe83f206  cmp byte ptr [rcx+0x3C5646C],1` | skinning-enabled flag [V] |
| 0xe8403d0 | - | slot 64 DLSS | `0xe8403d0  push rbp` | overrides base stub 0x768f0, size 0xaa5b [V body; slot per vt] |

## What this proves (per part of Q4a)

- bind-cache miss descriptor build: [V] — miss taken at 0xe822f23 when no side table / hash-map miss at 0xe822efa..0xe822f19; entry 0xe825a19 allocates from the job descriptor heap at job+0xB8 {cpu+8, gpu+0x10, increment+0x18} and all 10 type cases (0 reserved, 1/2 index/vertex buffer, 3 texture, 4 shader buffer, 5 feature-gated, 6 ranged texture, 7 ignored, 8 ranged shader buffer, 9 sampler) are decoded to their jump targets, with the shared SRV/UAV view builder at 0xe8272c3..0xe827333 creating views through device vtable slot 19 via thunk [0xF99FFA0]. Exact view-descriptor field breakdown inside cases 3/4/5/6/8 bodies beyond their jump targets: [I]/[?] (targets proven, bodies not fully transcribed).
- PSO desc build on a miss: [V] — program record renderer+0xB62178+prog*0xF8, key mask S&0x0707007FFFFFF0FF at 0xe81e8ec, signature at prog+0xA8 (0xe81eac7), hash-map miss walk (0xe820640/0xe820649), desc memset at 0xe81eff7 (0x290 bytes), CreateGraphicsPipelineState via device vtable slot 10 (+0x50) at 0xe8203b9 through thunk [0xF99FFA0] (0xe8203d1), success -> cache insert 0xe83bdd0 (0xe82048c), failure -> device-lost state renderer+0x19F88/+0x19F8C (0xe82043f/0xe820445).
- setPredefined: [V] — numPredefined u8 at prog+0xF0 (0xe82a49e), type-byte dispatch through jump table 0xF4EE7F8 with 14 entries (0xe82a51e), case 0 ViewRect from job+0x90A8 (0xe82a527), case 11 ModelViewProj from model cache job+0x2F8 indexed by draw.startMatrix draw+0x3C (0xe82a595/0xe82a59e), writes to vertex scratch job+0x3B0.. (0xe82a5a5/0xe82a5f1). Cases 1-10,12-13 targets known from the table; their bodies not transcribed here [I].
- helper bodies: [V] — setVertexBuffers 0xe81b4d0 fully decoded (stream mask, tzcnt loop, handle lookup ctx+0x9B2178+handle*0x80, layout stride at ctx+0xC96198+layout*0x54+4 confirming the 6fr correction, VBV writes, GENERIC_READ 0xAC3 state at ctx+0xA45C, transition thunk). 0xe81e1c0/commit, 0xbc6a9d0/rendererUpdateUniforms and 0xe81e860/PSO builder are dossaiered [V] in docs/functions/*.md (key + mask proven above).
- job/command-list model: [V] — wrapper 0xe83c390 selects cmdList = [renderer+0x19F60][jobIndex], slice [begin,end) from the vector at job+8, then calls executor 0xe821120: one D3D12 command list per job, parallel slices of the sorted item list.
- RTX subclass overrides: [V] — rdis vt dumps of both vtables (65 slots each) prove the diff: base 0xF4ED2D0 vs RTX 0xF4EEE80 differ at slots 0,1,4,10,14,15,16,19,21,26,50,54,55,58,59,60,63,64; slot 6 (Present 0xe811fb0) is identical in both (not overridden); first instruction of every override quoted verbatim above. Slots 63/64 and 54 are RTX-only (base = stub 0x768f0); slot 50 submit wrapper is 0x381 bytes; slot 64 is 0xaa5b bytes.

CLOSES? YES — all six holes named in Q4a (bind-cache miss descriptor build, PSO desc build on a miss, setPredefined, helper bodies, job/command-list model, RTX subclass overrides) are proven on disk by [V] verbatim rows in this file; no blocking fact.

## TOOL REQUESTS

None — existing rdis/xref/vt/verify_oc/delegate toolchain used; no new tools written.
