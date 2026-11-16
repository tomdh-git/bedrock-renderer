# UNIT U-B9b — D3D12 createProgram/destroyShader/destroyProgram + input-layout builder (BGFX_MAP 6au)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Header named in unit: none (src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h corroborates slot order).
Raw artifacts: docs/progress/oc_U-B9b_createProgram_fn_utf8.txt (rdis fn 0xe8142c0), oc_U-B9b_destroyShader_fn_utf8.txt (rdis fn 0xe8141e0), oc_U-B9b_destroyProgram_fn_utf8.txt (rdis fn 0xe8143a0), oc_U-B9b_inputlayout_fn_utf8.txt (rdis fn 0xe81e860), oc_U-B9b_inputlayout_dis_utf8.txt (rdis dis 0xe81e860 1600).
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## NEXT
Resume at: run `python tools/sigs/verify_oc.py docs/progress/oc_U-B9b.md` to validate every quoted `0xRVA  instr` line; fix mismatches; then finalize unit.

## (1) createProgram — rva 0xe8142c0 (vtable slot 24), size 0xd6

`rdis fn 0xe8142c0` → `sub_e8142c0 [0xe8142c0..0xe814396) size 0xd6  0 xrefs in` [V rdis fn output]. BGFX_MAP.md 6aj/1511: slot 24 = createProgram [I slot-number-to-role mapping; address verified by disassembly + BGFX_MAP line 401/1511].

Signature guess (arg shape matches BGFX_MAP line 1511 `createProgram(handle, vsh, fsh)`):
`void createProgram(RendererContext* this rcx, u16 program dx, u16 vsh r8w, u16 fsh r9d)` — 0xe8142c0.

Register map (from entry instructions, verbatim):
- rcx = arg1 = this (renderer context) → copied to rsi at e8142ce
- rdx = arg2 = program handle u16 → `movzx eax,dx` e8142d1; `imul r14,rax,0xF8` e8142d4 → r14 = program*0xF8 (program-record offset)
- r8 = arg3 = vsh handle u16 → `movzx eax,r8w` e8142db; `imul r15,rax,0xB8` e8142df → r15 = vsh*0xB8 (shader-record offset)
- r9 = arg4 = fsh handle u16 → `mov edi,r9d` e8142cb; `cmp di,0xFFFF` e814334 (0xFFFF = no fragment shader)
- r14 reused after e81433a as &program record (this + program*0xF8 + 0xB62178)

Verbatim disassembly (all instructions e8142c0..e814396):

```
e8142c0  push r15                                      
e8142c2  push r14                                      
e8142c4  push rsi                                      
e8142c5  push rdi                                      
e8142c6  push rbx                                      
e8142c7  sub rsp,0x20                                  
e8142cb  mov edi,r9d                                   
e8142ce  mov rsi,rcx                                   
e8142d1  movzx eax,dx                                  
e8142d4  imul r14,rax,0xF8                             
e8142db  movzx eax,r8w                                 
e8142df  imul r15,rax,0xB8                             
e8142e6  lea rax,[rcx+r15]                             ; rax = this + vsh*0xB8
e8142ea  add rax,0xAAA178                               ; rax = &shaders[vsh]  (table this+0xAAA178, stride 0xB8)
e8142f0  mov [rcx+r14+0xB62178],rax                    ; program record +0x00 = vs record ptr
e8142f8  movzx r8d,byte ptr [rcx+r15+0xAAA228]         ; r8d = shaders[vsh].+0xB0 = vs.entryCount
e814301  shl r8d,3                                      ; r8d = vs.count*8
e814305  lea rdx,[rcx+r15]                             ; rdx = &shaders[vsh]
e814309  add rdx,0xAAA188                              ; rdx = vs record +0x10 (entry array)
e814310  lea rbx,[rcx+r14]                             ; rbx = this + program*0xF8
e814314  add rbx,0xB62188                              ; rbx = program record +0x10 (entry array)
e81431b  mov rcx,rbx                                   
e81431e  call 0xEBCE390                                ; memcpy(program+0x10, vs+0x10, vs.count*8)
e814323  movzx eax,byte ptr [rsi+r15+0xAAA228]         ; eax = vs.entryCount (rsi == this)
e81432c  mov [rsi+r14+0xB62268],al                     ; program+0xF0 = vs.count  (0xB62268 = 0xB62178+0xF0)
e814334  cmp di,0xFFFF                                 
e814338  je short 0xE81438A                            ; fsh == 0xFFFF -> skip fragment part
e81433a  add r14,rsi                                    ; r14 = &program[program]
e81433d  add r14,0xB62178                              
e814344  add rsi,0xAAA178                              ; rsi = &shaders table base
e81434b  movzx ecx,di                                  
e81434e  imul rdi,rcx,0xB8                             ; rdi = fsh*0xB8
e814355  lea rcx,[rsi+rdi]                             ; rcx = &shaders[fsh]
e814359  mov [r14+8],rcx                               ; program+0x08 = fsh record ptr
e81435d  movzx r8d,byte ptr [rsi+rdi+0xB0]             ; r8d = fsh.entryCount
e814366  shl r8d,3                                      ; r8d = fsh.count*8
e81436a  lea rdx,[rsi+rdi]                             ; rdx = &shaders[fsh]
e81436e  add rdx,0x10                                   ; rdx = fsh record +0x10
e814372  lea rcx,[rbx+rax*8]                           ; rcx = program+0x10 + vs.count*8
e814376  call 0xEBCE390                                ; memcpy(program+0x10+vs.count*8, fsh+0x10, fsh.count*8)
e81437b  movzx eax,byte ptr [rsi+rdi+0xB0]             ; eax = fsh.entryCount
e814383  add [r14+0xF0],al                             ; program+0xF0 += fsh.count
loc_e81438a:
e81438a  add rsp,0x20                                  
e81438e  pop rbx                                       
e81438f  pop rdi                                       
e814390  pop rsi                                       
e814391  pop r14                                       
e814393  pop r15                                       
e814395  ret                                           
```

Program record layout — table `this+0xB62178`, stride 0xF8, index = program handle [V BGFX_MAP 6au lines 764-765; every field write below verified at quoted RVA]:

| Offset | Size | Field / meaning | Write evidence (RVA) | Tag |
|--------|------|-----------------|----------------------|-----|
| +0x00 | u64 | ptr to vertex shader record (`this+0xAAA178 + vsh*0xB8`) | `mov [rcx+r14+0xB62178],rax` e8142f0, rax = this+vsh*0xB8+0xAAA178 | [V] |
| +0x08 | u64 | ptr to fragment shader record (`this+0xAAA178 + fsh*0xB8`), only written if fsh != 0xFFFF | `mov [r14+8],rcx` e814359, rcx = &shaders[fsh] | [V] |
| +0x10 .. +0x10+vs.count*8 | vs.count*8 bytes | copy of vertex shader entry array from vs+0x10 | `call 0xEBCE390` e81431e (rcx=dest program+0x10, rdx=vs+0x10, r8=vs.count*8) | [V] |
| +0x10+vs.count*8 .. +fs.count*8 bytes | fs.count*8 bytes | copy of fragment shader entry array from fs+0x10 | `call 0xEBCE390` e814376 (rcx=program+0x10+vs.count*8, rdx=fs+0x10, r8=fs.count*8) | [V] |
| +0xF0 | u8 | total entry count = vs.count + fs.count | `mov [rsi+r14+0xB62268],al` e81432c (=vs.count), then `add [r14+0xF0],al` e814383 (+=fs.count); 0xB62268 = 0xB62178+0xF0 | [V] |
| +0xF1 .. +0xF7 | — | never written | — | [V gap] |

`0xEBCE390` = memcpy-like callee (rcx=dest, rdx=src, r8=count), called twice [I from arg order]. No ID3D12PipelineState is created here — records only [I per BGFX_MAP 6au consequence].

Callees: 0xEBCE390 (memcpy) x2 [I]. OPEN: none for createProgram body.

## (2) destroyShader — rva 0xe8141e0 (slot 23), size 0xd8

`rdis fn 0xe8141e0` → `sub_e8141e0 [0xe8141e0..0xe8142b8) size 0xd8  0 xrefs in` [V]. Slot 23 = destroyShader [I per BGFX_MAP 6aj].

Signature: `void destroyShader(this rcx, u16 handle dx)` [I arg shape mirrors createProgram: handle u16 in dx → `imul rax,0xB8`].

Verbatim disassembly:

```
e8141e0  push rsi                                      
e8141e1  push rdi                                      
e8141e2  sub rsp,0x38                                  
e8141e6  movzx eax,dx                                  
e8141e9  imul rax,0xB8                                 
e8141f0  lea rdi,[rcx+rax]                             ; rdi = this + handle*0xB8
e8141f4  add rdi,0xAAA178                              ; rdi = &shaders[handle]
e8141fb  mov rdx,[rcx+rax+0xAAA180]                   ; rdx = shader+0x08 = code/DXBC pointer (0xAAA180 = 0xAAA178+8)
e814203  test rdx,rdx                                  
e814206  je short 0xE814240                            ; no code pointer -> skip free
e814208  mov rcx,[0x12ADF800]                          ; rcx = allocator object
e81420f  test rcx,rcx                                  
e814212  je short 0xE814238                            ; no allocator -> skip free
e814214  mov rax,[rcx]                                 
e814217  mov rax,[rax+8]                               ; rax = allocator vtable slot 1 = free
e81421b  mov dword ptr [rsp+0x28],0                    
e814223  mov qword ptr [rsp+0x20],0                    
e81422c  xor r8d,r8d                                   
e81422f  xor r9d,r9d                                   
e814232  call qword ptr [0xF99FFA0]                    ; import thunk -> jmp rax = free(allocator, codePtr)
e814238:
e814238  mov qword ptr [rdi+8],0                       ; shader+0x08 = 0
e814240  mov byte ptr [rdi+0xB0],0                     ; shader+0xB0 entry count = 0
e814247  mov rsi,[rdi]                                 ; rsi = shader+0x00 owned pointer
e81424a  test rsi,rsi                                  
e81424d  je short 0xE8142B1                            ; null -> epilog
e81424f  mov rcx,[rsi]                                 ; rcx = (*rsi) vtable pointer
e814252  lea rax,[rsi+0x10]                            
e814256  cmp rcx,rax                                   
e814259  je short 0xE81426D                            ; 
e81425b  mov rax,[rax]                                 
e81425e  test rax,rax                                  
e814261  je short 0xE81426D                            ;
e814263  mov rdx,[rsi+0x18]                            
e814267  call qword ptr [0xF99FFA0]                    ; import thunk -> rax = [rcx+8] = vtable[1] of owned object
e81426d:
e81426d  mov rcx,[0x12ADF800]                          ; allocator
e814274  test rcx,rcx                                  
e814277  je short 0xE8142A0                            ;
e814279  mov rax,[rcx]                                 
e81427c  mov rax,[rax+8]                               ; allocator vtable slot 1 = free
e814280  mov dword ptr [rsp+0x28],0                    
e814288  mov qword ptr [rsp+0x20],0                    
e814291  mov rdx,rsi                                    ; rdx = owned pointer to free
e814294  xor r8d,r8d                                   
e814297  xor r9d,r9d                                   
e81429a  call qword ptr [0xF99FFA0]                    ; free(allocator, rsi)
e8142a0  mov qword ptr [rdi],0                         ; shader+0x00 = 0
e8142a7  mov dword ptr [rdi+0xA8],0                    ; shader+0xA8 signature = 0
e8142b1  add rsp,0x38                                  
e8142b5  pop rdi                                       
e8142b6  pop rsi                                       
e8142b7  ret                                           
```

What destroyShader frees/clears (shader record at `this+0xAAA178 + handle*0xB8`, stride 0xB8):

| Offset | Size | Action | Evidence (RVA) | Tag |
|--------|------|--------|----------------|-----|
| +0x08 | u64 | Freed via allocator vtable slot 1 (`[0x12ADF800]` → vtable+8 → thunk `[0xF99FFA0]`), then cleared | e814208-232 free; `mov qword ptr [rdi+8],0` e814238 | [V] |
| +0xB0 | u8 | Cleared (entry count) | `mov byte ptr [rdi+0xB0],0` e814240 | [V] |
| +0x00 | u64 | Owned pointer released via its vtable slot 1 (`[rsi]`, rdx=[rsi+0x18], thunk `[0xF99FFA0]` at e814267), then freed with allocator (e81429a), then cleared | e814247-29a; `mov qword ptr [rdi],0` e8142a0 | [V call] / [I exact semantics of the e814267 release] |
| +0xA8 | u32 | Cleared (signature) | `mov dword ptr [rdi+0xA8],0` e8142a7 | [V] |
| +0x10 .. +0xA7 | 8-byte entry array (up to 19 uniform handles/refs) | NOT touched by destroyShader | No write to this range in body | [V gap] / [I entries are uniform refs owned elsewhere] |

`0x12ADF800` = global allocator object [V data ref]. `0xF99FFA0` = import thunk = single `jmp rax` (tail-call to the vtable-resolved function) [V; same thunk as U-B7b e82dc84].

## (3) destroyProgram — rva 0xe8143a0 (slot 25), size 0x1e

`rdis fn 0xe8143a0` → `sub_e8143a0 [0xe8143a0..0xe8143be) size 0x1e  0 xrefs in` [V]. Slot 25 = destroyProgram [I per BGFX_MAP]. "Tiny stub" [V size].

Verbatim disassembly (complete):

```
e8143a0  movzx eax,dx                                  
e8143a3  imul rax,0xF8                                 
e8143aa  mov byte ptr [rcx+rax+0xB62268],0             ; program+0xF0 entry count = 0  (0xB62268 = 0xB62178+0xF0)
e8143b2  xorps xmm0,xmm0                               
e8143b5  movups [rcx+rax+0xB62178],xmm0                ; program+0x00..+0x0F = 0 (vs ptr + fsh ptr zeroed)
e8143bd  ret                                           
```

Program record at `this+0xB62178 + handle*0xF8`:
- +0xF0 (u8) total entry count → 0 [W e8143aa]
- +0x00/+0x08 (u64×2) vs/fsh shader-record pointers → 0 via 16-byte movups [W e8143b5]
- Entry array +0x10 .. +0xEF NOT cleared; shader records NOT freed (owned by createShader/destroyShader) [I gap]

## (4) Input-layout builder — rva 0xe81e860, size 0x1c9a

`rdis fn 0xe81e860` → `sub_e81e860 [0xe81e860..0xe8204fa) size 0x1c9a  2 xrefs in` [V]. Body ends 0xe8204fa; `int3` padding 0xe8204fa..0xe820500, next function at 0xe820500 [V listing].

2 xrefs in: `0xe818bc0` (blit, vtable slot 51) and `0xe821120` (draw executor item loop) [V `xref.py callers 0xe81e860`]. Role: builds the vertex input layout (D3D12_INPUT_ELEMENT_DESC array) and the graphics pipeline state from the program/shader records + vertex element records [I from data flow].

Argument map (register args rcx/rdx/r8/r9 + stack home slots read at entry; exact role of most slots inferred):
- rcx = arg1 → `[rsp+0x30]` e81e886; used as guarded-array base for texture/vertex tables (this+0xC97698/0xC976B0 walks) [V]
- rdx = arg2 → r12 e81e8de; `imul rax,0xF8` on `word ptr [rsp+0x7F8]` (u16 program handle) e81e88b/d7; `rbx = rdx + prog*0xF8 + 0xB62178` = program record e81e8e1/e81e8e5 [V]
- r8 = arg3 → r13 e81e883; reloaded `[rsp+0x7F0]` = r8 e81e89b = array of pointers to 0x54-byte element records (indexed `[rsp+0x7F0] + i*8`) [V]
- r9 = arg4 → `[rsp+0x38]` e81e903 [V]
- `[rsp+0x7D0]` → r15d e81e8bd; `[rsp+0x7D8]` → xmm6 e81e8b4; `[rsp+0x7E0]` → xmm7 e81e8ab; `[rsp+0x7E8]` → ebp (byte) e81e8a3; `[rsp+0x810]` → rdi e81e893 (pointer; dereferenced `rax=[rdi]` → `[rsp+0x630]` at e8203a4) [V]
- Stack frame 0x768; stack cookie `[rsp+0x738]` vs `[0x1230A0C0]` e81e8c5/e8204a2 [V]

Data flow (verbatim key instructions):
- e81e934 `mov rax,[rbx]` / e81e937 `movdqu xmm0,[rax+0x80]` — program+0x00 = vs record; vs+0x80 read [V]
- e81eac4 `mov rax,[rbx]` / e81eac7 `mov eax,[rax+0xA8]` → vs record +0xA8 signature hashed into buffer [V]
- e81eb0d `mov eax,[rax+0xA8]` — fsh record ([rbx+8]) +0xA8 signature hashed if fsh present [V]
- Buffer `[rsp+0x70]` accumulates 4/8-byte hashed values via `call 0xEBCE5E0`/`call 0xBC76610` e81ea40..e81eb2d [V]
- `e81ef04..e81ef5c` — FNV-1a-style combine (prime 0x5BD1E995) of `[rsp+0x74]`, `[rsp+0x70]`, `[rsp+0x7C]` → `[rsp+0x70]` = combined layout hash [V]
- `e81ef60` `mov rax,[r12+0x48]` / `e81ef65` `mov rcx,[r12+0x50]` / `sub rcx,rax / shr rcx,3` — qword count [V]
- `e81ef80..e81efce` — hash → table `[rax+rcx*8]`/`[rax+rcx*8+8]` chain walk; `e81efe0 cmp [rdx],rsi` → hit returns `[rdx+8]` at e81f062 → `jne 0xE82049A` (cached hit, early return) [V]
- e81eff7 `lea rcx,[rsp+0x3C8]` / `mov r8d,0x290` / `xor edx,edx` / `call 0xEBCE430` — memset 0x290 bytes at rsp+0x3C8 (state descriptor) [V]
- e8203af `mov rcx,[rdi+0x400]` / e8203b6 `mov rax,[rcx]` / e8203b9 `mov rax,[rax+0x50]` — device wrapper +0x400 → vtable → slot +0x50 [V]
- e8203bd `lea r8,[0xF4EDD64]` / e8203c4 `lea rdx,[rsp+0x3C8]` / e8203cc `lea r9,[rsp+0x68]` / e8203d1 `call qword ptr [0xF99FFA0]` — indirect device call (rdx=&desc, r8=.rdata blob ptr 0xF4EDD64, r9=&out ptr) [V]
- e8203d9 `test eax,eax / jns 0xE82044B` — HRESULT; negative → device-lost/TDR path ([rdi+0x19F88] cmp 5, eax 0x887A0004 etc.) e8203db..e82043f [V]
- e82044b `mov rsi,[rsp+0x68]` — created object; non-null → `call 0xE83BBF0` / `call 0xE83BDD0`; `[rsp+0x6B0]=rdi / [rsp+0x6B8]=rsi` e820464-479 [V]

Callees [I]: sub_ebce390 = memcpy (rcx=dest, rdx=src, r8=count); sub_ebce430 = memset; sub_bc76610 = string hash; sub_ebce5e0 = strlen-like (rdx=0x7FFFFFFF max, len in eax); sub_ebce570 = strcmp-like (rcx=&{ptr,len}, rdx=&{ptr,len}, r8=maxlen; eax==0 if equal); sub_e83abb0 = guarded paged-array lookup; 0xEBCE390 also used as memcpy elsewhere in this unit [consistent with createProgram].

### Semantic-name strings referenced

Only ONE semantic name is referenced as a literal string inside 0xe81e860:
- `e81fdc5 lea r15,[0xF7CCFBB]` — RVA 0xF7CCFBB = "TEXCOORD" [V disassembly; PE string confirmed via tools/sigs/pepeek.py]. Used at e81fe00/e81ff32 (`mov rcx,r15; call 0xEBCE5E0` → strlen) and compared against each desc's SemanticName via `call 0xEBCE570` e81fe71/e81ffa1.
- `e81fdbe lea rsi,[0xF847A07]` — empty string (PE-decoded, first byte NUL) [V], initial placeholder pair before being overwritten by "TEXCOORD".

Static semantic-name table (attribute→semantic descriptor table):
- `e81f563 lea rdi,[0xF4EDF30]` — table base RVA 0xF4EDF30 [V]. Decoded as data with PE read (tools/sigs/pepeek.py; VA 0x14F7CA830 = image base 0x140000000 + RVA 0xF7CA830, confirmed because all three pointer dwords land on known string RVAs):
  - entry 0 (+0x00): `+0x00 = 0x000000014F7CA830` → "POSITION" (RVA 0xF7CA830) [V PE]; `+0x08 = 1`; `+0x0C = 6`; `+0x10 = 0`; `+0x14 = 0xFFFFFFFF`; `+0x18 = 0`; `+0x1C = 0`
  - entry 1 (+0x20): `+0x20 = 0x000000014F7CB11C` → "NORMAL" (RVA 0xF7CB11C) [V PE]; `+0x24 = 1`; `+0x2C = 6`
  Entry size 0x20; table extent beyond entry 1 not determined [UNVERIFIED: 0xe81e860 how many entries does the 0xF4EDF30 table have?].
- `e81f56a lea r14,[0xF4ECF40]` — 256-byte attribute-id→format decode table (8 groups × 4 entries × 8 bytes; indexed `table[(attr&0x38)/8*32 + (attr&3)*8 + ((attr>>5)&1)*4]`) [V e81fcee/e81fd01; PE-decoded values: +00=62,+04=61,+08=50,+0C=49,+10=30,+14=28,...]

`xref.py str POSITION/COLOR/NORMAL` shows none of those strings have a reference inside 0xe81e860 (their refs are at 0xaaae00/0xa0d5870/0xbb68xxx etc.) [V]. So POSITION/NORMAL reach this builder only via the 0xF4EDF30 table; COLOR/TANGENT/etc. are not referenced here at all [V negative].

### D3D12_INPUT_ELEMENT_DESC (0x20 bytes) array fill

Canonical field offsets [task spec]: SemanticName +0, SemanticIndex +8, Format +0xC, InputSlot +0x10, AlignedByteOffset +0x14, InputSlotClass +0x18, InstanceDataStepRate +0x1C.
Array base during phase 1 = `rsp+0xA0`, stride 0x20, max 0x13 (19) entries (`cmp r12,0x13` e81fd20); final array base → `[rsp+0x5F0]` (= rsp+0xA0 if count>0 else 0), count → `[rsp+0x5F8]` [V e820045/e82004c].

Every store observed (verbatim):

Phase 1 — per attribute r12 (e81fd2a..e81fd64):
- `e81fd3f mov rdx,rsi` / `e81fd42 call 0xEBCE390` — `memcpy(r13, rsi, 0x20)` copies a 0x20-byte source record → covers SemanticName(+0, pointer) and SemanticIndex(+8) plus the rest from the source; rsi advances +0x20 per iteration `e81fd1c add rsi,0x20` [V]. (rsi = pointer to semantic-name struct, set up in the e81fcca/e81fce0 lookup region.)
- `e81fd04 mov [r13+0xC],eax` — Format(+0xC) from attr-id→format table lookup via 0xF4ECF40 (`e81fcee..e81fd01`: `mov edx,eax / and edx,0x38 / lea rdx,[r14+rdx*4] / lea rcx,[rdx+rcx*8] / shr eax,5 / and eax,4 / mov eax,[rax+rcx]`) [V]
- `e81fd11 mov [r13+0x14],eax` — AlignedByteOffset(+0x14) = `[rsp+r12*2+0x6B6]` when attr-id(`[rsp+r12*2+0x6DC]`) != 0; else `e81fd57 xor eax,eax` → offset 0 [V]
- `e81fd47 mov [r13+0x10],ebp` — InputSlot(+0x10) = ebp (element slot index) [V]
- `e81fd2a cmp word ptr [rsp+r12*2+0x6DC],0xFFFF / je short 0xE81FD19` — attr-id 0xFFFF skips the entry entirely [V]

Phase 2 — instance TEXCOORD entries (e81feb0..e81fed6), entered when byte `[rsp+0x800]` != 0 (`e81fe99 cmp byte ptr [rsp+0x800],0 / je 0xE82001F`):
- `e81feb4 mov r8d,0x20 / mov rcx,r13 / lea rdx,[rsp+0x6B0] / call 0xEBCE390` — `memcpy(dest=r13, src=&[rsp+0x6B0], 0x20)` copies the template descriptor [V]
- Template `[rsp+0x6B0]` (0x20 bytes) built at e81fd74 `movdqa [rsp+0x6C0],xmm0` (from `[0xF4ECCD0]`) and e81fd84 `movdqa [rsp+0x6B0],xmm0` (from `[0xF4ECCC0]`) [V]. PE-decoded template:
  - +0x00 SemanticName = ptr `0x000000014F7CCFBB` → RVA 0xF7CCFBB "TEXCOORD" [V PE]
  - +0x08 SemanticIndex = 0
  - +0x0C Format = 2
  - +0x10 InputSlot = 0
  - +0x14 AlignedByteOffset = 0xFFFFFFFF (D3D12_APPEND_ALIGNED_ELEMENT)
  - +0x18 InputSlotClass = 1 (PER_INSTANCE_DATA)
  - +0x1C InstanceDataStepRate = 1
- `e81feca mov dword ptr [r13+0x10],1` — InputSlot(+0x10) = 1 [V]
- `e81fed2 mov [r13+8],ebx` — SemanticIndex(+0x8) = ebx (descending from max TEXCOORD index) [V]
- `e81fee0 mov [r13+0x14],eax` — AlignedByteOffset(+0x14) = `ecx<<4` = counter*16; `e81fee4 inc ecx` [V]
- `e81fff0..e82001a` (fallback when count==0 path e81ffd5): appends default per-instance entries; `e820008 mov dword ptr [rdi+0x10],1` (InputSlot=1), `e82000f mov [rdi+8],ebp` (SemanticIndex = ebp = 0,-1,-2... via `e820015 dec ebp`), `e820012 mov [rdi+0x14],ebx` (AlignedByteOffset; `e820017 add ebx,0x10`) [V]

TEXCOORD index tracking (e81fded..e81fe94): for each desc `[rsp+rbp+0xA0]` (SemanticName ptr), if `sub_ebce570` match against "TEXCOORD" (eax==0) → `e81fe7e mov eax,[rsp+rbp+0xA8]` (SemanticIndex +8) / `e81fe8a cmp eax,ecx / e81fe8c cmova ecx,eax` → `[rsp+0x28]` = max TEXCOORD semantic index [V].

### Attribute-to-semantic table address

RVA 0xF4EDF30 [V e81f563] — static table of {char* SemanticName; u32; u32; u32; u32; u32; u32} stride 0x20; decoded entries above ("POSITION"→RVA 0xF7CA830, "NORMAL"→RVA 0xF7CB11C) [V PE]. No separate attribute-ID→semantic-name table is referenced in this function; semantics are carried by the vertex element records (array of pointers at `[rsp+0x7F0]`, each a 0x54-byte record copied to `[rsp+0x6B0]`, e81f5a8/e81f5b0) [I].

UNVERIFIED items:
- [UNVERIFIED: 0xe81e860 exact role of tables 0xF4ECC00/0xF4ECC70/0xF4ECC90/0xF4ECCB0/0xF4ECBD0/0xF4ED700 (shader-signature bitfield format decode) — values decoded via PE, roles inferred]
- [UNVERIFIED: 0xe8203b9 exact device method at vtable slot +0x50 (likely ID3D12Device::CreateGraphicsPipelineState; 4-arg indirect call through thunk [0xF99FFA0])]
- [UNVERIFIED: 0xe81e860 exact field-name mapping of +0x10/+0x18 (InputSlot vs InputSlotClass) — stores match canonical D3D12_INPUT_ELEMENT_DESC offsets but the exe's struct is not independently confirmed]
- [UNVERIFIED: 0xe81e860 how [rsp+0x20] (used as guarded-array base at e82007b/e820100/e820151/e82019f/e820268/e8202a9) is initialized — not seen written in the listing]
- [UNVERIFIED: 0xe81e860 whether destroyShader's +0x10..+0xA7 entry array (uniform refs) is freed elsewhere]

## Verification artifacts
- docs/progress/oc_U-B9b_createProgram_fn_utf8.txt — `rdis ... fn 0xe8142c0`
- docs/progress/oc_U-B9b_destroyShader_fn_utf8.txt — `rdis ... fn 0xe8141e0`
- docs/progress/oc_U-B9b_destroyProgram_fn_utf8.txt — `rdis ... fn 0xe8143a0`
- docs/progress/oc_U-B9b_inputlayout_fn_utf8.txt — `rdis ... fn 0xe81e860`
- docs/progress/oc_U-B9b_inputlayout_dis_utf8.txt — `rdis ... dis 0xe81e860 1600`
- tools/sigs/pepeek.py — PE RVA→file-offset reader (general; see TOOL REQUESTS)

## TOOL REQUESTS
pepeek.py | RVA -> file offset + string/u32/bytes decode | general PE data decoder built on the jt.py parse_pe pattern; used to decode 0xF4ECCC0/0xF4ECCD0 template, 0xF4EDF30 semantic table, 0xF4ECF40 format table, and string RVAs 0xF7CCFBB/0xF7CA830/0xF7CB11C instead of doing it by hand
