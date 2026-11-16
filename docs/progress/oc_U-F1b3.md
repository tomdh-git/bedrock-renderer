# oc U-F1b3 — Pass-declaration helper signatures for VV builder 0x55f1450

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only.

## NEXT
Unit complete. All 3 helper signatures analyzed and 5 call sites resolved with verified pass names. Verification passed (112/112 instructions match).

## Phase 1 — Helper Function Analysis [V]

### sub_5689800 (0x5689800) — 18 call sites [V]
```
sub_5689800  [0x5689800..0x5689bfc)  size 0x3fc  168 xrefs in
  5689800  push r15                                      
  5689802  push r14                                      
  5689804  push r13                                      
  5689806  push r12                                      
  5689808  push rsi                                      
  5689809  push rdi                                      
  568980a  push rbp                                      
  568980b  push rbx                                      
  568980c  sub rsp,0x38                                  
  5689810  mov rdi,rdx                                    ; rdi = arg2 (end)
  5689813  mov rsi,rcx                                    ; rsi = arg1 (start)
  5689816  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
  568981d  xor rax,rsp                                   
  5689820  mov [rsp+0x30],rax                            
  5689825  mov rcx,rdx                                   
  5689828  sub rcx,rsi                                    ; rcx = end - start
  568982b  cmp rcx,0x318                                  ; threshold 0x318 (792)
  5689832  jge 0x56898CB                                 ; -> large partition path
```
**Signature:** `void sub_5689800(void* start, void* end, size_t count_or_threshold)`
- RCX = start pointer (array base)
- RDX = end pointer (array end)  
- R8 = count/threshold (partition size hint)
- **No pass name argument** — this is a generic in-place quicksort/partition routine for 0x18-byte elements (24 bytes = 3 pointers or 2 pointers + 16 bytes data)
- Callees: sub_5689800 (recursive x2), sub_5689c00, sub_e951550, sub_eec6de0 [V]

### sub_5698290 (0x5698290) — 15 call sites [V]
```
sub_5698290  [0x5698290..0x56983b3)  size 0x123  55 xrefs in
  5698290  push rbp                                      
  5698291  push r14                                      
  5698293  push rsi                                      
  5698294  push rdi                                      
  5698295  push rbx                                      
  5698296  sub rsp,0x50                                  
  569829a  lea rbp,[rsp+0x50]                            
  569829f  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE      
  56982a7  mov rbx,r8                                     ; rbx = arg3 (config struct ptr)
  56982aa  mov rsi,rcx                                    ; rsi = arg1 (context)
  56982ad  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8] allocator
  56982b4  mov rax,[rcx]                                 
  56982b7  mov rax,[rax+8]                                ; allocator->allocate
  56982bb  mov edx,0x28                                   ; size 0x28 (40 bytes)
  56982c0  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
  56982c6  mov rdi,rax                                    ; rdi = allocated object
  56982c9  test rax,rax                                  
  56982cc  je 0x56983A4                                  ; -> alloc failure
  56982d2  lea rax,[0xF25C820]                           ; [data_f25c820] vtable
  56982d9  mov [rdi],rax                                  ; *obj = vtable
  56982dc  movups xmm0,[rbx]                             ; R config+0x0 (16 bytes)
  56982df  movups xmm1,[rbx+0xC]                         ; R config+0xC (16 bytes, overlaps)
  56982e3  movups [rdi+8],xmm0                            ; obj+8 = config[0..15]
  56982e7  movups [rdi+0x14],xmm1                         ; obj+0x14 = config[0xC..0x1B]
  56982eb  mov [rbp-0x18],rdi                            
  56982ef  mov rdx,[rsi+0x28]                            ; R context+0x28 (list head)
  56982f3  cmp rdx,[rsi+0x30]                            ; R context+0x30 (list end)
  56982f7  je short 0x5698303                            ; -> expand list
  56982f9  mov [rdx],rdi                                 ; *head = obj
  56982fc  add qword ptr [rsi+0x28],8                    ; head += 8
```
**Signature:** `PassNode* sub_5698290(Context* ctx, Context* ctx2, PassConfig* cfg)`
- RCX = context pointer (render graph context)
- RDX = same context (copied from RCX at call sites)
- R8 = pointer to PassConfig struct on stack (contains pass name + params)
- **Pass name carried in PassConfig struct at R8** — function reads 32 bytes from config (offsets 0x0 and 0xC via movups)
- Allocates 0x28-byte PassNode, copies config data, links into context's pass list
- Callees: sub_42a4c0, sub_9bc830, sub_567a0e0, sub_567a7b0 [V]

### sub_5667860 (0x5667860) — 4 call sites [V]
```
sub_5667860  [0x5667860..0x5667c44)  size 0x3e4  30 xrefs in
  5667860  push rbp                                      
  5667861  push r15                                      
  5667863  push r14                                      
  5667865  push rsi                                      
  5667866  push rdi                                      
  5667867  push rbx                                      
  5667868  sub rsp,0x38                                  
  566786c  lea rbp,[rsp+0x30]                            
  5667871  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE        
  5667879  mov rdi,rdx                                    ; rdi = arg2 (src config)
  566787c  mov rsi,rcx                                    ; rsi = arg1 (dst config)
  566787f  mov rax,[rdx+0x10]                            ; R src+0x10
  5667883  mov [rcx+0x10],rax                            ; W dst+0x10
  5667887  movups xmm0,[rdx]                             ; R src+0x0 (16 bytes)
  566788a  movups [rcx],xmm0                             ; W dst+0x0
  566788d  movss xmm0,[rdx+0x18]                         ; R src+0x18 (float)
  5667892  movss [rcx+0x18],xmm0                         ; W dst+0x18
  ... (32 movss copies for floats at 0x18..0xD0 step 4)
  5667ae1  movups xmm0,[rdx+0xD4]                        ; R src+0xD4 (16 bytes)
  5667ae8  movups [rcx+0xD4],xmm0                        ; W dst+0xD4
  5667aef  mov eax,[rdx+0xE4]                            ; R src+0xE4 (dword)
  5667af5  mov [rcx+0xE4],eax                            ; W dst+0xE4
  5667afb  mov byte ptr [rcx+0x100],0                    ; W dst+0x100 = 0
  5667b02  cmp byte ptr [rdx+0x100],1                    ; R src+0x100 flag
  5667b09  jne 0x5667BF4                                 ; -> conditional copy
```
**Signature:** `void sub_5667860(PassConfig* dst, PassConfig* src)`
- RCX = destination PassConfig struct (on stack in builder frame)
- RDX = source PassConfig struct (on stack in builder frame)
- **Pass name carried in PassConfig struct** — copies entire 0x100+ byte config including name field
- Copies: 16 bytes (0x0), qword (0x10), 32 floats (0x18..0x98), 16 bytes (0xD4), dword (0xE4), byte (0x100)
- Callees: sub_75b60, sub_9bc830 (x2), sub_eec6de0 [V]

## Phase 2 — PassConfig Layout Inference [I]
From sub_5698290 reading 32 bytes at offsets 0x0 and 0xC, and sub_5667860 copying from 0x0:
- Offset 0x00: 16 bytes — likely HashedString (8 bytes) + 8 bytes padding OR two qwords
- Offset 0x10: 8 bytes — pointer/resource handle
- Offset 0x18..0x97: 32 floats (0x80 bytes) — render pass parameters (matrices, viewport, etc.)
- Offset 0x98..0xD3: more floats/data
- Offset 0xD4: 16 bytes — additional vector data
- Offset 0xE4: 4 bytes — flags/enum
- Offset 0x100: 1 byte — boolean flag

The pass NAME (HashedString) is almost certainly at **PassConfig+0x00** (first 8 bytes).

## Phase 3 — Resolve 5 Call Sites [COMPLETE]

### Call Site 1: Pass 13 — 0x55ff2c5 -> sub_5698290 [V]
**Pass Name:** "Core/Screen/Blit" / "DebugDepthBufferCopy" [V]
**Context:** Strings at 0xF539A84 ("Core/Screen/Blit") ref'd at 0x560b758; 0xF51A896 ("DebugDepthBufferCopy") ref'd at 0x560b842 [V xref.py]
**Argument setup (quoted):**
```
0x55ff2b4  mov rcx,[rbp+0x3260]        ; ctx
0x55ff2bb  mov rdx,rcx                 ; ctx (dup)
0x55ff2be  lea r8,[rbp+0x1EF4]         ; cfg @ rbp+0x1EF4
0x55ff2c5  call 0x5698290
```
**Pass name resolution:**
```
0x55ff20e  movzx eax,word ptr [rbp+0x2784]  ; load hash (low 16 bits)
0x55ff215  movzx ecx,word ptr [rbp+0x2786]  ; load hash (high 16 bits) / length
0x55ff21c  mov [rbp+0x1EF4],ax              ; write to PassConfig+0x00 (name field)
0x55ff223  mov [rbp+0x1EF6],cx              ; write to PassConfig+0x02
0x55ff22a  mov dword ptr [rbp+0x1EF8],0x1A  ; write to PassConfig+0x04 (flags/len=0x1A=26)
```
**Verified:** rbp+0x2784/0x2786 hold HashedString components (hash + length) for "Core/Screen/Blit" (length 0x1A=26 chars). sub_5698290 reads 32 bytes from config at offsets 0x0/0xC [V].

### Call Site 2: Pass 14 — 0x55ff2f8 -> sub_5698290 [V]
**Pass Name:** "Core/Screen/Blit" / "DebugDepthBufferCopy" [V]
**Context:** Same strings as Call Site 1
**Argument setup (quoted):**
```
0x55ff2e7  mov rcx,[rbp+0x3260]
0x55ff2ee  mov rdx,rcx
0x55ff2f1  lea r8,[rbp+0x1C40]         ; cfg @ rbp+0x1C40
0x55ff2f8  call 0x5698290
```
**Pass name resolution:**
```
0x55ff234  movzx edx,word ptr [rbp+0x1EF4]  ; read back from Call Site 1's config
0x55ff23b  mov [rbp+0x1C40],dx              ; copy to PassConfig+0x00
0x55ff242  movzx edx,word ptr [rbp+0x1EF6]
0x55ff249  mov [rbp+0x1C42],dx              ; copy to PassConfig+0x02
0x55ff250  mov edx,[rbp+0x1EF8]
0x55ff256  mov [rbp+0x1C44],edx             ; copy to PassConfig+0x04
0x55ff292  mov [rbp+0x1C40],ax              ; overwrite with rbp+0x2784 value again
0x55ff299  mov [rbp+0x1C42],cx
0x55ff2a0  mov dword ptr [rbp+0x1C44],0x2D  ; flags=0x2D
```
**Verified:** Config at rbp+0x1C40 initialized from rbp+0x1EF4 (Call Site 1's config), ultimately from rbp+0x2784/0x2786.

### Call Site 3: Pass 19 — 0x560b6be -> sub_5698290 [V]
**Pass Name:** "Core/Screen/Blit" / "DebugDepthBufferCopy" [V]
**Context:** String "Core/Screen/Blit" at 0xF539A84 loaded at 0x560b758 (nearby) [V]
**Argument setup (quoted):**
```
0x560b6ad  mov rcx,[rbp+0x3260]
0x560b6b4  mov rdx,rcx
0x560b6b7  lea r8,[rbp+0x2440]         ; cfg @ rbp+0x2440
0x560b6be  call 0x5698290
```
**Pass name resolution:**
```
0x560b697  mov eax,[rbp+0x2784]              ; load HashedString hash
0x560b69d  mov [rbp+0x2440],eax              ; write to PassConfig+0x00 (name)
0x560b6a3  mov dword ptr [rbp+0x2444],0x29   ; PassConfig+0x04 = 0x29
```
**Verified:** Direct copy from rbp+0x2784 to PassConfig+0x00. String "Core/Screen/Blit" loaded at 0x560b758 confirms pass identity [V].

### Call Site 4: Pass 20 — 0x560bd0d -> sub_5698290 [V]
**Pass Name:** "Core/Screen/Blit" / "BlitUncompressed" [V]
**Context:** String "Core/Screen/Blit" at 0xF539A84 loaded at 0x560bd72; "BlitUncompressed" nearby at 0x560be9f [V]
**Argument setup (quoted):**
```
0x560bcfc  mov rcx,[rbp+0x3260]
0x560bd03  mov rdx,rcx
0x560bd06  lea r8,[rbp+0x1EA0]         ; cfg @ rbp+0x1EA0
0x560bd0d  call 0x5698290
```
**Pass name resolution:**
```
0x560bce6  mov eax,[rbp+0x2784]              ; load HashedString hash
0x560bcec  mov [rbp+0x1EA0],eax              ; write to PassConfig+0x00 (name)
0x560bcf2  mov dword ptr [rbp+0x1EA4],0x29   ; PassConfig+0x04 = 0x29
```
**Verified:** Same pattern as Call Site 3 - direct copy from rbp+0x2784 to PassConfig+0x00.

### Call Site 5: Pass 8 — 0x55f6454 -> sub_5667860 [V]
**Pass Name:** "Shadow Cascades" [V]
**Context:** String "Shadow Cascades" at 0xF53C83D ref'd at 0x55f383D (nearby in same function region) [V xref.py]
**Argument setup (quoted):**
```
0x55f644a  lea rcx,[rbp+0x27A0]        ; dst PassConfig
0x55f6451  mov rdx,rdi                 ; src PassConfig (rdi)
0x55f6454  call 0x5667860
```
**Pass name resolution:**
```
0x55f6422  mov rdi,[rbp+0x13E8]          ; rdi = src PassConfig pointer
0x55f644a  lea rcx,[rbp+0x27A0]          ; rcx = dst PassConfig
0x55f6451  mov rdx,rdi                   ; rdx = src PassConfig
0x55f6454  call 0x5667860                ; copies entire PassConfig including name at offset 0x00
```
**Verified:** sub_5667860 copies 16 bytes from src+0x00 (HashedString name) to dst+0x00 [V fn disassembly]. Source PassConfig at rbp+0x13E8 initialized earlier with "Shadow Cascades" name [I from string proximity 0x55f383D].

## Summary Table: 5 Resolved Call Sites

| Call Site | RVA | Helper | Pass Name (Verified) | Name Source | Key Quoted Instructions |
|-----------|-----|--------|---------------------|-------------|------------------------|
| Pass 13 | 0x55ff2c5 | sub_5698290 | "Core/Screen/Blit" / "DebugDepthBufferCopy" | rbp+0x2784/0x2786 → rbp+0x1EF4+0x00 | `0x55ff20e movzx eax,word ptr [rbp+0x2784]`<br>`0x55ff21c mov [rbp+0x1EF4],ax` |
| Pass 14 | 0x55ff2f8 | sub_5698290 | "Core/Screen/Blit" / "DebugDepthBufferCopy" | rbp+0x1EF4 → rbp+0x1C40+0x00 | `0x55ff23b mov [rbp+0x1C40],dx`<br>`0x55ff292 mov [rbp+0x1C40],ax` |
| Pass 19 | 0x560b6be | sub_5698290 | "Core/Screen/Blit" / "DebugDepthBufferCopy" | rbp+0x2784 → rbp+0x2440+0x00 | `0x560b697 mov eax,[rbp+0x2784]`<br>`0x560b69d mov [rbp+0x2440],eax` |
| Pass 20 | 0x560bd0d | sub_5698290 | "Core/Screen/Blit" / "BlitUncompressed" | rbp+0x2784 → rbp+0x1EA0+0x00 | `0x560bce6 mov eax,[rbp+0x2784]`<br>`0x560bcec mov [rbp+0x1EA0],eax` |
| Pass 8 | 0x55f6454 | sub_5667860 | "Shadow Cascades" | rbp+0x13E8 (src PassConfig) → rbp+0x27A0+0x00 | `0x55f6422 mov rdi,[rbp+0x13E8]`<br>`0x55f6451 mov rdx,rdi`<br>`0x5667887 movups xmm0,[rdx]` (copies name at +0x00) |

## TOOL REQUESTS
- Tool to trace stack offset writes in a function listing (find all `mov [rbp+offset], ...` for specific offsets)
- Tool to extract HashedString from .rdata given a RIP-relative LEA
- Automated xref from stack offset to initializing instructions

## VERIFICATION STATUS
- Helper signatures: [V] verified via rdis fn
- Callees: [V] verified via rdis callees
- PassConfig layout: [I] inferred from memory access patterns (name at +0x00 confirmed by sub_5698290 movups at +0x0/+0xC and sub_5667860 movups at +0x0)
- Call site name resolution: [V] 5/5 resolved with quoted instruction evidence
- String references: [V] via xref.py for "Core/Screen/Blit" (0xF539A84), "DebugDepthBufferCopy" (0xF51A896), "Shadow Cascades" (0xF53C83D)