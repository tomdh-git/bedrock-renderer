## NEXT
Resume at: verify_oc.py on all allocator docs; then finalize.

---

# Unit U-A8a: Handle Allocators in bgfx::Context (checklist A8a)

Per checklist A8a (RENDER_CHECKLIST.md line 51): "Handle allocators located in Context (offsets) — 6s, 6ai (API fn map; per-allocator roles [I])"

This unit covers every handle allocator (alloc/free of handle indices) in the **bgfx::Context** (global `s_ctx` at RVA `0x12AE1748`). For each resource type: allocator object offset inside Context, its alloc/free function RVAs, max count (cmp immediates), and key instructions quoted from `rdis dis`.

> **Note**: The RendererContextD3D12 (vtable at `0xF4ED2D0`) has its own per-handle record tables (textures `+0xBDE178`, index buffers `+0x93A178`, vertex buffers `+0x9B2178`, framebuffers `+0xA32178`, programs `+0xB62178`, shaders `+0xAAA178`, window framebuffers `+0xC97698` — see BGFX_MAP 6z, 6au, A8b). Those are **record tables**, not handle allocators. The handle allocators live in the **bgfx::Context** (the >0x1EBF2F1-byte object created at `0xBC63690`, thread proc `0xBC65720`). The API-side create/destroy functions (6ai) take the Context lock (`ctx+0x1C0` via `0xEBDF10`) and manipulate these allocators.

> **Allocator structure** (bgfx `HandleAlloc`, per 6s): `u16 numHandles` at `+0`, `u16 maxHandles` at `+2`, dense `u16[]` array immediately after (size = maxHandles × 2), sparse `u16[]` array after that (size = maxHandles × 2). Allocation: `cmp ax, cx` (num vs max), `jae` = full; else take `dense[numHandles]`, write into `sparse[handle] = numHandles`, `dense[numHandles] = handle`, `numHandles++`. Free: reverse.

---

## 1. Index Buffer (static) — `createIndexBuffer` / `destroyIndexBuffer`

**Allocator offset**: `ctx + 0x1DE534C`  
**Create function**: `0xBC6F0A0` (size 0x1A9) — API-side createIndexBuffer-like  
**Destroy function**: `0xBC6FDC0` (size 0x245) — destroy for 0xBC6F910 (vertex buffer), queues handle to free-list drain `0xBC76E80`  
**Max count**: `u16 maxHandles` at `ctx+0x1DE534E` (cmp at `0xBC6F0E5`)  

**Key instructions** (from `rdis fn 0xBC6F0A0`):
```
0xBC6F0D7  movzx eax,word ptr [rbx+0x1DE534C]   ; load numHandles
0xBC6F0DE  movzx ecx,word ptr [rbx+0x1DE534E]   ; load maxHandles
0xBC6F0E5  cmp ax,cx                             ; num vs max
0xBC6F0E8  jae 0xBC6F1D7                         ; full -> error (returns 0xFFFF)
0xBC6F0EE  movzx edx,ax                          ; edx = numHandles
0xBC6F0F1  lea r8d,[rax+1]                       ; r8d = numHandles+1
0xBC6F0F5  mov [rbx+0x1DE534C],r8w               ; numHandles++
0xBC6F0FD  movzx edx,word ptr [rbx+rdx*2+0x1DE5350] ; dense[numHandles] -> handle
0xBC6F105  lea rcx,[rbx+rcx*2]                   ; rcx = &sparse[handle]
0xBC6F109  add rcx,0x1DE5350
0xBC6F110  mov [rcx+rdx*2],ax                    ; sparse[handle] = numHandles
0xBC6F114  mov [rsi],dx                          ; return handle to caller
```

**Destroy path** (0xBC6FDC0, queues to free-list) — corrected from disassembly:
```
0xBC6FE54  lea rcx,[rdi+0x1DDD2D0]               ; free-queue vector begin
0xBC6FE5B  movzx eax,word ptr [rsi]              ; load handle
0xBC6FE5E  shl rax,0x20
0xBC6FE62  mov edx,[rsi+4]
0xBC6FE65  or rdx,rax
0xBC6FE68  call 0xBC76E80                        ; sub_BC76E80 (push to free queue)
0xBC6FE6D  nop
0xBC6FE6E  mov rcx,[rdi+0x1DDD2D0]
0xBC6FE75  mov rdx,[rdi+0x1DDD2D8]
0xBC6FE7C  sub rdx,rcx
0xBC6FE7F  shr rdx,4                             ; element count (0x10 bytes each)
0xBC6FE83  lea r9,[0xBC76E60]                    ; destructor 0xBC76E60
0xBC6FE8A  mov r8d,0x10
0xBC6FE90  call 0xEBDBC90                        ; drain queue (calls 0xBC76E60 per element)
```

---

## 2. Vertex Buffer (static) — `createVertexBuffer` / `destroyVertexBuffer`

**Allocator offset**: `ctx + 0x1DDD308` (primary, 4096-entry)  
**Secondary allocator**: `ctx + 0x1DE534C` (shared with index buffer)  
**Create function**: `0xBC6F910` (size 0x308)  
**Destroy function**: `0xBC6FDC0` (size 0x245) — same as index buffer destroy  
**Max count**: `u16 maxHandles` at `ctx+0x1DDD30A` (cmp at `0xBC6F95B`) = **4096** (0x1000)  

**Key instructions** (from `rdis fn 0xBC6F910`):
```
0xBC6F94D  movzx eax,word ptr [rdi+0x1DDD308]    ; load numHandles
0xBC6F954  movzx ecx,word ptr [rdi+0x1DDD30A]    ; load maxHandles
0xBC6F95B  cmp ax,cx                             ; num vs max
0xBC6F95E  jae 0xBC6FB00                         ; full -> error
0xBC6F964  movzx r8d,ax                          ; r8d = numHandles
0xBC6F968  lea edx,[rax+1]                       ; edx = numHandles+1
0xBC6F96B  mov [rdi+0x1DDD308],dx                ; numHandles++
0xBC6F972  movzx r12d,word ptr [rdi+r8*2+0x1DDD30C] ; dense[numHandles] -> handle
0xBC6F97B  lea r9,[rdi+rcx*2]                    ; r9 = &sparse[handle]
0xBC6F97F  add r9,0x1DDD30C
0xBC6F986  mov [r9+r12*2],ax                     ; sparse[handle] = numHandles
0xBC6F98B  cmp r12d,0xFFFF
0xBC6F992  je 0xBC6FB00                          ; invalid handle -> error
```

**Secondary allocator use** (same 0x1DE534C as index buffer):
```
0xBC6F9D0  movzx ecx,word ptr [rdi+0x1DE534C]    ; numHandles (secondary)
0xBC6F9D7  movzx r10d,word ptr [rdi+0x1DE534E]   ; maxHandles (secondary)
0xBC6F9DF  mov r11,r8
0xBC6F9E2  mov r15d,eax
0xBC6F9E5  cmp cx,r10w                           ; num vs max
0xBC6F9E9  jae 0xBC6FBCB                         ; full
0xBC6F9EF  movzx r11d,cx
0xBC6F9F3  lea r15d,[rcx+1]
0xBC6F9F7  mov [rdi+0x1DE534C],r15w              ; secondary numHandles++
0xBC6F9FF  movzx r11d,word ptr [rdi+r11*2+0x1DE5350] ; dense[numHandles] -> handle
0xBC6FA08  lea r10,[rdi+r10*2]                   ; r10 = &sparse[handle]
0xBC6FA0C  add r10,0x1DE5350
0xBC6FA13  mov [r10+r11*2],cx                    ; sparse[handle] = numHandles
```

---

## 3. Vertex Layout / Index Buffer (large) — `createVertexLayout` / `destroyVertexLayout`

**Allocator offset**: `ctx + 0x1DA10C8` (record table) + free-queue at `ctx + 0x1DE1310`/`0x1DE1318`  
**Stride-size fields**: at `ctx+0x1DA90C8` (stride at `+4`, `+8`, `+0xC` per 6ai)  
**Create function**: `0xBC70240` (size 0x40D, slot 19/20 area)  
**Destroy function**: `0xBC70800` (size 0x242)  
**Max count**: `u16 maxHandles` at `ctx+0x1DE134A` (cmp at `0xBC702A9`)  

**Key instructions** (from `rdis fn 0xBC70240`):
```
0xBC7029A  movzx r9d,word ptr [rdi+0x1DE1348]    ; numHandles
0xBC702A2  movzx eax,word ptr [rdi+0x1DE134A]    ; maxHandles
0xBC702A9  cmp r9w,ax                            ; num vs max
0xBC702AD  jae 0xBC7060D                         ; full -> error
0xBC702B3  movzx r10d,r9w                        ; r10d = numHandles
0xBC702B7  lea ecx,[r9+1]                        ; ecx = numHandles+1
0xBC702BB  mov [rdi+0x1DE1348],cx                ; numHandles++
0xBC702C2  movzx ecx,word ptr [rdi+r10*2+0x1DE134C] ; dense[numHandles] -> handle
0xBC702CB  lea r11,[rdi+rax*2]                   ; r11 = &sparse[handle]
0xBC702CF  add r11,0x1DE134C
0xBC702D6  mov [r11+rcx*2],r9w                   ; sparse[handle] = numHandles
```

**Destroy uses free-queue** (0xBC70800):
```
0xBC70870  movzx eax,r9w
0xBC70874  lea rcx,[rdi+0x1DE1310]               ; free-queue vector begin
0xBC7087B  shl rax,0x20
0xBC7087F  mov edx,[rsi+4]
0xBC70882  or rdx,rax
0xBC70885  call 0xBC76E80                        ; push to free queue
0xBC7088A  nop
0xBC7088B  mov rcx,[rdi+0x1DE1310]
0xBC70892  mov rdx,[rdi+0x1DE1318]
0xBC70899  sub rdx,rcx
0xBC7089C  shr rdx,4                             ; element count
0xBC708A0  lea r9,[0xBC76E60]                    ; destructor 0xBC76E60
0xBC708A7  mov r8d,0x10
0xBC708AD  call 0xEBDBC90                        ; drain queue
```

**Destroy path for vertex buffer** (0xBC6FDC0, queues to free-list) — corrected from disassembly:
```
0xBC6FE54  lea rcx,[rdi+0x1DDD2D0]               ; free-queue vector begin
0xBC6FE5B  movzx eax,word ptr [rsi]              ; load handle
0xBC6FE5E  shl rax,0x20
0xBC6FE62  mov edx,[rsi+4]
0xBC6FE65  or rdx,rax
0xBC6FE68  call 0xBC76E80                        ; sub_BC76E80 (push to free queue)
0xBC6FE6D  nop
0xBC6FE6E  mov rcx,[rdi+0x1DDD2D0]
0xBC6FE75  mov rdx,[rdi+0x1DDD2D8]
0xBC6FE7C  sub rdx,rcx
0xBC6FE7F  shr rdx,4                             ; element count (0x10 bytes each)
0xBC6FE83  lea r9,[0xBC76E60]                    ; destructor 0xBC76E60
0xBC6FE8A  mov r8d,0x10
0xBC6FE90  call 0xEBDBC90                        ; drain queue (calls 0xBC76E60 per element)
```

---

## 4. Texture — `createTexture` (2D/cube) / `destroyTexture`

**Allocator offset**: `ctx + 0x1DFC298`  
**Create functions**: `0xBC716A0` (2D, size 0x295), `0xBC71990` (cube, size 0x295) — share allocator  
**Destroy function**: `0xBC71DA0` (size 0x167)  
**Max count**: `u16 maxHandles` at `ctx+0x1DFC29A` (cmp at `0xBC718DD`)  

**Key instructions** (from `rdis fn 0xBC716A0`):
```
0xBC718C9  movzx ecx,word ptr [rdi+0x1DFC298]    ; numHandles
0xBC718D0  movzx edx,word ptr [rdi+0x1DFC29A]    ; maxHandles
0xBC718D7  mov ax,0xFFFF
0xBC718DB  cmp cx,dx                             ; num vs max
0xBC718DE  jae short 0xBC7191B                   ; full -> error
0xBC718E0  movzx r8d,cx                          ; r8d = numHandles
0xBC718E4  lea r9d,[rcx+1]                       ; r9d = numHandles+1
0xBC718E8  mov [rdi+0x1DFC298],r9w               ; numHandles++
0xBC718F0  movzx r8d,word ptr [rdi+r8*2+0x1DFC29C] ; dense[numHandles] -> handle
0xBC718F9  lea rdx,[rdi+rdx*2]                   ; rdx = &sparse[handle]
0xBC718FD  add rdx,0x1DFC29C
0xBC71904  mov [rdx+r8*2],cx                     ; sparse[handle] = numHandles
0xBC71909  mov [rbp-0xA],r8w                     ; save handle
```

**Destroy** (0xBC71DA0) returns handle to free list:
```
0xBC71E9B  movzx ecx,word ptr [rdi+0x1DFC298]    ; numHandles
0xBC71EA2  movzx edx,word ptr [rdi+0x1DFC29A]    ; maxHandles
0xBC71EA9  mov ax,0xFFFF
0xBC71EAD  cmp cx,dx
0xBC71EB0  jae short 0xBC71EED                   ; already empty
0xBC71EB2  movzx r8d,cx
0xBC71EB6  lea r9d,[rcx+1]
0xBC71EBA  mov [rdi+0x1DFC298],r9w               ; numHandles++
0xBC71EC2  movzx r8d,word ptr [rdi+r8*2+0x1DFC29C] ; dense[numHandles] -> free handle
0xBC71ECB  lea rdx,[rdi+rdx*2]
0xBC71ECF  add rdx,0x1DFC29C
0xBC71ED6  mov [rdx+r8*2],cx                     ; sparse[free_handle] = numHandles
```

---

## 5. Framebuffer (texture-backed) — `createFrameBuffer` / `destroyFrameBuffer`

**Allocator offset**: `ctx + 0x1DF145C`  
**Create functions**: `0xBC72C80` (size 0x321), `0xBC73000` (size 0x285) — share allocator  
**Destroy function**: `0xBC732E0` (size 0x280) — complex, uses ref-count on 0x1E52AB8 table  
**Max count**: `u16 maxHandles` at `ctx+0x1DF145E` (cmp at `0xBC72D73` / `0xBC7309F`)  

**Key instructions** (from `rdis fn 0xBC72C80`):
```
0xBC72D63  movzx r10d,word ptr [rdi+0x1DF145C]   ; numHandles
0xBC72D6B  movzx r11d,word ptr [rdi+0x1DF145E]   ; maxHandles
0xBC72D73  cmp r10w,r11w                         ; num vs max
0xBC72D77  jae 0xBC72E7B                         ; full -> error
0xBC72D7D  movzx r8d,r10w                        ; r8d = numHandles
0xBC72D81  lea r12d,[r10+1]                      ; r12d = numHandles+1
0xBC72D85  mov [rdi+0x1DF145C],r12w              ; numHandles++
0xBC72D8D  movzx r8d,word ptr [rdi+r8*2+0x1DF1460] ; dense[numHandles] -> handle
0xBC72D96  lea r11,[rdi+r11*2]                   ; r11 = &sparse[handle]
0xBC72D9A  add r11,0x1DF1460
0xBC72DA1  mov [r11+r8*2],r10w                   ; sparse[handle] = numHandles
0xBC72DA6  mov [rbp-0xA],r8w                     ; save handle
```

**Destroy** (0xBC732E0) — ref-counted, not simple free-list:
```
0xBC732F9  mov di,dx
0xBC732FC  mov rsi,rcx
0xBC73316  lea rbx,[rax+rax*2]
0xBC7331A  movzx edx,word ptr [rsi+rbx*2+0x1E52AB8] ; load ref count
0xBC73325  call 0xBC79790                        ; cleanup attachment
0xBC73349  dec word ptr [rbx+4]                  ; dec ref count
0xBC7334D  je short 0xBC73366                    ; if zero -> full destroy
```

---

## 6. Dynamic Texture — `createDynamicTexture` / `destroyDynamicTexture`

**Allocator offset**: `ctx + 0x1DFB48C`  
**Create function**: `0xBC74A80` (size 0x5C5)  
**Destroy function**: `0xBC750B0` (size 0x1EB) / `0xBC752F0` (update, size 0xFE)  
**Max count**: `u16 maxHandles` at `ctx+0x1DFB48E` (cmp at `0xBC74AC8` / `0xBC750F3`)  
**Caps gate**: `ctx+0x1EBF2F3` (guarded flag) + global caps `0x12ADFA54` bit 4 (DynamicTextureHandles) — see 6dm, 6am  

**Key instructions** (from `rdis fn 0xBC74A80`):
```
0xBC74ABA  movzx eax,word ptr [rbx+0x1DFB48C]    ; numHandles
0xBC74AC1  movzx ecx,word ptr [rbx+0x1DFB48E]    ; maxHandles
0xBC74AC8  cmp ax,cx                             ; num vs max
0xBC74ACB  mov [rbp-0x10],rsi                    ; save arg
0xBC74ACF  jae 0xBC74E22                         ; full -> error
0xBC74AD5  movzx edx,ax
0xBC74AD8  lea r8d,[rax+1]
0xBC74ADC  mov [rbx+0x1DFB48C],r8w               ; numHandles++
0xBC74AE4  movzx edx,word ptr [rbx+rdx*2+0x1DFB490] ; dense[numHandles] -> handle
0xBC74AEC  lea rcx,[rbx+rcx*2]
0xBC74AF0  add rcx,0x1DFB490
0xBC74AF7  mov [rcx+rdx*2],ax                    ; sparse[handle] = numHandles
0xBC74AFB  mov [rsi],dx                          ; return handle
```

**Destroy** (0xBC750B0):
```
0xBC750E5  movzx eax,word ptr [rdi+0x1DFB48C]    ; numHandles
0xBC750EC  movzx ecx,word ptr [rdi+0x1DFB48E]    ; maxHandles
0xBC750F3  cmp ax,cx
0xBC750F6  jae 0xBC7527F                         ; full/empty
0xBC750FC  movzx edx,ax
0xBC750FF  lea r8d,[rax+1]
0xBC75103  mov [rdi+0x1DFB48C],r8w               ; numHandles++
0xBC7510B  movzx edx,word ptr [rdi+rdx*2+0x1DFB490] ; dense -> handle
0xBC75113  lea rcx,[rdi+rcx*2]
0xBC75117  add rcx,0x1DFB490
0xBC7511E  mov [rcx+rdx*2],ax                    ; sparse[handle] = numHandles
0xBC75122  mov [rsi],dx                          ; return handle (for deferred destroy)
```

---

## 7. Uniform — `createUniform` / `destroyUniform`

**Allocator offset**: `ctx + 0x1DFB690` (per 6ah)  
**Create function**: `0xBC75440` (size 0x67A)  
**Destroy function**: `0xBC75C30` (size 0x2A9) — uses hash table, not simple free-list  
**Max count**: `u16 maxHandles` at `ctx+0x1DFB692` (cmp at `0xBC7558D`)  
**Hash table**: keys `u32[1024]` at `ctx+0x1E1C2A4`, handles `u16[1024]` at `ctx+0x1E1D2A4`, records stride 0x18 at `ctx+0x1E1DAA8`  

**Key instructions** (from `rdis fn 0xBC75440`):
```
0xBC7557F  movzx eax,word ptr [rbx+0x1DFB690]    ; numHandles
0xBC75586  movzx ecx,word ptr [rbx+0x1DFB692]    ; maxHandles
0xBC7558D  cmp ax,cx                             ; num vs max
0xBC75590  jae 0xBC756E4                         ; full -> error (0xFFFF)
0xBC75596  movzx edx,ax
0xBC75599  lea r8d,[rax+1]
0xBC7559D  mov [rbx+0x1DFB690],r8w               ; numHandles++
0xBC755A5  movzx edx,word ptr [rbx+rdx*2+0x1DFB694] ; dense[numHandles] -> handle
0xBC755AD  lea rcx,[rbx+rcx*2]
0xBC755B1  add rcx,0x1DFB694
0xBC755B8  mov [rcx+rdx*2],ax                    ; sparse[handle] = numHandles
0xBC755BC  mov [rbp-0x12],dx                     ; save handle
```

**Destroy** (0xBC75C30) — hash table cleanup, not allocator free:
```
0xBC75C49  mov edi,edx
0xBC75C61  movzx eax,di
0xBC75C64  lea rax,[rax+rax*2]
0xBC75C68  dec word ptr [rsi+rax*8+0x1E1DABE]   ; dec ref count in record
0xBC75C70  jne 0xBC75EC3                         ; if non-zero, just dec
0xBC75CFB  lea rax,[rsi+0x1E1D2A4]              ; hash table handles
0xBC75D20  cmp [rax+rcx*2],di                   ; find handle in hash table
0xBC75D26  mov word ptr [rsi+rcx*2+0x1E1D2A4],0xFFFF ; clear hash entry
0xBC75D30  dec edx
0xBC75D32  mov [rsi+0x1E1C2A0],edx              ; dec hash table count
```

---

## 8. Shader — `createShader` / `destroyShader`

**No standard handle allocator** — uses fixed 3×1024-entry tables at `ctx+0x1E7DAD8`/`0x1E7DAE0` (by-name, 0xBC71140) and `ctx+0x1E2CAC0`/`0x1E2CAB8` (binary, 0xBC729E0).  
**Create functions**: `0xBC71140` (by name, size 0x235), `0xBC729E0` (binary, size 0x23F)  
**Destroy function**: `0xE8141E0` (RendererContextD3D12 slot 23, size 0xD8) — destroys RendererContext shader record, not Context handle  
**RendererContext shader record table**: `this+0xAAA178`, stride 0xB8 (6au) — 4096 entries  

**Key instructions** (from `rdis fn 0xBC71140` — by-name):
```
0xBC71175  movzx eax,bx
0xBC71178  lea rax,[rax+rax*4]
0xBC7117C  lea r13,[rdi+rax*8]
0xBC71180  add r13,0x1E7DAD8                    ; table base + idx*0x28
0xBC71187  cmp dword ptr [rdi+rax*8+0x1E7DAE0],0 ; check if slot empty
0xBC7118F  je short 0xBC711DD                   ; empty -> use it
```

**Key instructions** (from `rdis fn 0xBC729E0` — binary):
```
0xBC72A15  movzx eax,bx
0xBC72A18  shl eax,5                            ; idx * 32
0xBC72A1B  lea r13,[rdi+rax]
0xBC72A1F  cmp dword ptr [rdi+rax+0x1E2CAC0],0  ; check 0x1E2CAC0 table
0xBC72A27  je short 0xBC72A7E                   ; empty -> use it
```

---

## 9. Program — `createProgram` / `destroyProgram`

**No Context handle allocator** — programs are RendererContextD3D12 objects.  
**Create function**: `0xBC71F60` (size 0xA05, API-side) -> calls RendererContext slot 24 (`0xE8142C0`)  
**Destroy function**: RendererContext slot 25 (`0xE8143A0`, tiny stub)  
**RendererContext program record table**: `this+0xB62178`, stride 0xF8 (6au) — 2048 entries  

**Key instructions** (from `rdis fn 0xBC71F60` — API-side):
```
0xBC721F6  imul r12d,eax,0x19B1                 ; hash -> probe index
0xBC721FD  and r12d,0x1FFF                      ; mask 8191 (8k buckets)
0xBC72204  mov eax,r12d
0xBC72210  mov edx,eax
0xBC72212  movzx ecx,word ptr [r8+rdx*2+0x1E28AB0] ; load handle from bucket
0xBC7221B  cmp rcx,0xFFFF
0xBC72222  je short 0xBC7223E                   ; empty bucket -> insert
0xBC72224  cmp [r8+rdx*4+0x1E20AB0],esi         ; compare signature
0xBC7222C  je 0xBC7238F                         ; match -> reuse
```

---

## 10. Occlusion Query — **No dedicated handle allocator found in Context**

**Caps**: `maxOcclusionQueries = 256` (6j), `OcclusionQuery` flag bit 0x1000 (6bl)  
**Draw header field**: `RenderDraw+0x7A` = occlusion query handle (u16, 0xFFFF = none)  
**Frame storage**: `Frame+0x14300` = `int32 m_occlusion[256]` by query handle (6e-2, 1573)  
**Encoder::submit** sets `draw+0x7A` and state bit 62 (occlusion query flag)  
**RendererContextD3D12 slots 39-45** (6k): "occlusion query, setMarker, setName and Mojang extras" — but 6aj reassigns 39-41 to uniform record update (0xC97698 table).  
**Status**: [UNVERIFIED: 0xE817880..0xE8189C0 occlusion query create/destroy not isolated] — may use fixed 256-entry array without handle allocator, or be handled entirely in RendererContextD3D12.

---

## 11. View — **Fixed 256 views, no handle allocator**

**View array**: `ctx+0x1EAB080`, stride 0x140, 256 entries (6q)  
**View remap**: `ctx+0x1EAAA60`, `u16[256]` (6s)  
**Frame view state**: copied via `memcpy(frame+?, ctx+0x1EAB080, 0x14000)` in `frame()` (0xBC66DE0)

---

## 12. Encoder — **Fixed small pool, no handle allocator**

**Caps**: `encoders = 10` (6j)  
**Encoder objects**: created on API thread, submitted via `Encoder::submit` (0xBC5FB40)  
**No Context handle allocator** — encoder handles managed separately.

---

## Summary Table

| Resource Type | Context Allocator Offset | Create RVA | Destroy RVA | Max Count (cmp) | Allocator Style |
|--------------|-------------------------|------------|-------------|-----------------|-----------------|
| Index Buffer (static) | `+0x1DE534C` | `0xBC6F0A0` | `0xBC6FDC0` | `ctx+0x1DE534E` | Standard dense/sparse |
| Vertex Buffer (static) | `+0x1DDD308` (+ `+0x1DE534C` shared) | `0xBC6F910` | `0xBC6FDC0` | `ctx+0x1DDD30A` = 4096 | Standard dense/sparse |
| Vertex Layout / IB (large) | `+0x1DE1348` + free-queue `+0x1DE1310` | `0xBC70240` | `0xBC70800` | `ctx+0x1DE134A` | Standard + free-queue |
| Texture (2D/cube) | `+0x1DFC298` | `0xBC716A0` / `0xBC71990` | `0xBC71DA0` | `ctx+0x1DFC29A` | Standard dense/sparse |
| Framebuffer (texture) | `+0x1DF145C` | `0xBC72C80` / `0xBC73000` | `0xBC732E0` | `ctx+0x1DF145E` | Standard dense/sparse |
| Dynamic Texture | `+0x1DFB48C` | `0xBC74A80` | `0xBC750B0` | `ctx+0x1DFB48E` | Standard dense/sparse |
| Uniform | `+0x1DFB690` | `0xBC75440` | `0xBC75C30` | `ctx+0x1DFB692` | Standard + hash table |
| Shader | *None* (fixed tables) | `0xBC71140` / `0xBC729E0` | `0xE8141E0` (RC) | N/A (3×1024 fixed) | Direct table indexing |
| Program | *None* (RendererContext) | `0xBC71F60` -> `0xE8142C0` | `0xE8143A0` (RC) | N/A (2048 RC table) | RendererContext table |
| Occlusion Query | *Not found* | *Slots 39-45?* | *Slots 39-45?* | 256 (caps) | [UNVERIFIED] |
| View | *Fixed array* | N/A | N/A | 256 | Fixed `ctx+0x1EAB080` |
| Encoder | *Fixed pool* | N/A | N/A | 10 | Separate management |

---

## Verification Status

| Allocator | Create Doc'd | Destroy Doc'd | verify_oc.py |
|-----------|--------------|---------------|--------------|
| Index Buffer | ✅ | ✅ | PENDING |
| Vertex Buffer | ✅ | ✅ | PENDING |
| Vertex Layout | ✅ | ✅ | PENDING |
| Texture | ✅ | ✅ | PENDING |
| Framebuffer | ✅ | ✅ | PENDING |
| Dynamic Texture | ✅ | ✅ | PENDING |
| Uniform | ✅ | ✅ | PENDING |
| Shader | ✅ | ✅ | PENDING |
| Program | ✅ | ✅ | PENDING |
| Occlusion Query | ❌ [UNVERIFIED] | ❌ [UNVERIFIED] | N/A |

---

## TOOL REQUESTS

| Name | Input → Output | Why it would have helped |
|------|----------------|--------------------------|
| `allocator_finder.py` | Context base RVA → table of all `cmp ax,cx` / `jae` patterns near `numHandles`/`maxHandles` offsets | Automates finding all handle allocators; currently done by manual cross-ref of 6ai create/destroy functions |
| `verify_oc.py` | progress markdown → PASS/FAIL | Required by unit spec; will run after writing all allocator sections |
| `preflight.py` | RVA → bundled dossier (listing + callers + stores + case walk) | Would give callers, stores, listing in one go; run manually per function |

---

## NEXT
Resume at: verify_oc.py on all allocator docs; then finalize.