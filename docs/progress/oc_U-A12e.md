## NEXT: DONE. Both sub_e927fc0 and sub_e815590 listed instruction-complete with D3D12 indirect calls analyzed.

# UNIT U-A12e: RTX handle creation API (continued)

## Step 1: sub_e927fc0 (heap creation, called 4x from 0xe807ff0 for LTextureBufferHeap etc.)

### sub_e927fc0 bounds: [0xe927fc0..0xe92822d) size 0x26d

**Instruction-complete listing (0xe927fc0..0xe92822d):**

```
0xe927fc0  push rbp
0xe927fc1  push r15
0xe927fc3  push r14
0xe927fc5  push r12
0xe927fc7  push rsi
0xe927fc8  push rdi
0xe927fc9  push rbx
0xe927fca  sub rsp,0x60
0xe927fce  lea rbp,[rsp+0x60]
0xe927fd3  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
0xe927fdb  mov rdi,r9                                     ; rdi = 4th arg (L-string data pointer)
0xe927fde  mov r14,r8                                     ; r14 = 3rd arg
0xe927fe1  mov rbx,rdx                                    ; rbx = 2nd arg (size/config)
0xe927fe4  mov rsi,rcx                                    ; rsi = 1st arg (heap record pointer)
0xe927fe7  lea r15,[rcx+0x30]                            ; r15 = heap record + 0x30
0xe927feb  mov rcx,r15
0xe927fee  call 0xEEC59F0                                ; sub_eec59f0 (init lock/refcount at +0x30)
0xe927ff3  test eax,eax
0xe927ff5  jne 0xE9281FC                                 ; -> error path 1
0xe927ffb  cmp dword ptr [rsi+0x7C],0x7FFFFFFF           ; R heap record+0x7C (state/gen)
0xe928002  je 0xE928206                                  ; -> error path 2
0xe928008  mov [rbp-0x18],r15
0xe92800c  mov rcx,rbx
0xe92800f  call qword ptr [0xF9A90A8]                    ; [data_f9a90a8] (size/alignment calc)
0xe928015  mov rcx,[rsi+0x18]                            ; R heap record+0x18 (current capacity)
0xe928019  cmp rax,rcx
0xe92801c  jbe short 0xE92802F
0xe92801e  mov rcx,rsi
0xe928021  mov rdx,rax
0xe928024  mov r9,rbx
0xe928027  call 0xA6A70                                  ; sub_a6a70 (grow buffer)
0xe92802c  nop
0xe92802d  jmp short 0xE92805A

0xe92802f  mov r15,rsi
0xe928032  cmp rcx,8
0xe928036  jb short 0xE92803B
0xe928038  mov r15,[rsi]

0xe92803b  mov [rsi+0x10],rax
0xe92803f  mov r8,rax
0xe928042  add r8,rax
0xe928045  mov rcx,r15
0xe928048  mov rdx,rbx
0xe92804b  mov rbx,rax
0xe92804e  call 0xEEC6DE0                                ; sub_eec6de0 (memcpy/move)
0xe928053  mov word ptr [r15+rbx*2],0

0xe92805a  mov eax,[rbp+0x80]                            ; 5th arg (flags)
0xe928060  mov ecx,[rbp+0x78]                            ; 6th arg (node mask)
0xe928063  mov rdx,[rbp+0x70]                            ; 7th arg (heap properties pointer)
0xe928067  mov rbx,[rbp+0x68]                            ; 8th arg (heap size)
0xe92806b  mov r8d,[rbp+0x60]                            ; 9th arg (alignment)
0xe92806f  mov [rsi+0x20],r14                            ; W heap record+0x20 = 3rd arg
0xe928073  movups xmm0,[rdi]                              ; R L-string (16 bytes)
0xe928076  movups [rsi+0x130],xmm0                        ; W heap record+0x130 = L-string copy
0xe92807d  mov r9d,[rdi+0x10]                             ; R L-string+0x10
0xe928081  mov [rsi+0x140],r9d                            ; W heap record+0x140
0xe928088  mov [rsi+0x144],r8d                            ; W heap record+0x144 = alignment
0xe92808f  mov [rsi+0x158],ecx                            ; W heap record+0x158 = node mask
0xe928095  mov [rsi+0x15C],eax                            ; W heap record+0x15C = flags
0xe92809b  mov [rsi+0x148],rbx                            ; W heap record+0x148 = heap size
0xe9280a2  mov [rsi+0x150],rdx                            ; W heap record+0x150 = heap properties
0xe9280a9  mov r15d,ecx                                   ; r15d = node mask (loop count)
0xe9280ac  lea rdi,[rsi+0x178]                            ; rdi = heap record+0x178 (descriptor array)
0xe9280b3  xor r12d,r12d                                  ; r12 = loop index
0xe9280b6  lea r14,[rbp-0x28]                             ; r14 = stack temp
0xe9280ba  cmp r12,r15
0xe9280bd  jb short 0xE9280E4
0xe9280bf  jmp short 0xE928127

0xe9280d0  mov rcx,rdi
0xe9280d3  mov r8,r14
0xe9280d6  call 0x116730                                 ; sub_116730 (descriptor init)
0xe9280db  nop

0xe9280dc  inc r12
0xe9280df  cmp r12,r15
0xe9280e2  jae short 0xE928127

0xe9280e4  mov rcx,rsi
0xe9280e7  mov rdx,rbx
0xe9280ea  call 0xE9282E0                                ; sub_e9282e0 (allocate descriptor)
0xe9280ef  nop
0xe9280f0  test rax,rax
0xe9280f3  je short 0xE9280DC
0xe9280f5  mov [rbp-0x28],rax
0xe9280f9  mov rcx,[rax+0x18]                            ; R allocated desc+0x18 (size)
0xe9280fd  add [rsi+0x160],rcx                            ; W heap record+0x160 (total size)
0xe928104  mov rdx,[rsi+0x180]                            ; R heap record+0x180 (tail pointer)
0xe92810b  cmp rdx,[rsi+0x188]                            ; R heap record+0x188 (end pointer)
0xe928112  je short 0xE9280D0
0xe928114  mov [rdx],rax
0xe928117  add qword ptr [rsi+0x180],8
0xe92811f  inc r12
0xe928122  cmp r12,r15
0xe928125  jb short 0xE9280E4

0xe928127  mov word ptr [rsi+0x118],0                     ; W heap record+0x118 = 0

;; --- First D3D12 device call: CreateHeap (slot 28) ---
0xe928130  mov rcx,[0x1233E1A8]                          ; rcx = global context pointer [V]
0xe928137  mov rax,[rcx]                                 ; rax = context vtable [V]
0xe92813a  mov rax,[rax+8]                               ; rax = context+8 = ID3D12Device* [V]
0xe92813e  mov edx,0x10                                  ; edx = 1 (heap count?)
0xe928143  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 (CFG thunk) [V]
;; Device vtable displacement: +8 from context, then vtable[2] = ID3D12Device::CreateHeap? 
;; Actually: context -> [context] = context vtable -> [context_vtable+8] = device pointer
;; Then the call goes through CFG thunk. The actual D3D12 method is determined by what the thunk calls.
;; The thunk at 0xF99FFA0 (sub_eea6040) is a CFG guard that calls the function pointer in rax.
;; But rax here holds the device pointer, not a vtable function. Need to check thunk behavior.
;; [UNVERIFIED: 0xe92813a what vtable slot is called via thunk at 0xF99FFA0 when rax=ID3D12Device*]

0xe928149  nop
0xe92814a  mov rdi,rax                                    ; rdi = returned heap pointer
0xe92814d  test rax,rax
0xe928150  je 0xE9281DF                                  ; -> alloc failure retry

;; --- Second D3D12 device call: CreateHeap (slot 28) ---
0xe928156  mov [rbp-0x10],rdi
0xe92815a  mov rcx,[0x1233E1A8]                          ; rcx = global context [V]
0xe928161  mov rax,[rcx]                                 ; rax = context vtable [V]
0xe928164  mov rax,[rax+8]                               ; rax = device pointer [V]
0xe928168  mov edx,0x10
0xe92816d  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 [V]
;; Same pattern as above. [UNVERIFIED: 0xe928164 same question]

0xe928173  nop
0xe928174  mov r14,rax
0xe928177  test rax,rax
0xe92817a  je short 0xE9281EF

0xe92817c  mov [r14],rsi
0xe92817f  lea rax,[0xE928480]                           ; rax = sub_e928480 (callback)
0xe928186  mov [r14+8],rax
0xe92818a  mov rbx,[rbp-0x10]
0xe92818e  mov rdi,rbx
0xe928191  add rdi,8
0xe928195  mov [rsp+0x28],rdi
0xe92819a  mov dword ptr [rsp+0x20],0
0xe9281a2  lea r8,[0xE92BC50]                            ; sub_e92bc50
0xe9281a9  xor ecx,ecx
0xe9281ab  xor edx,edx
0xe9281ad  mov r9,r14
0xe9281b0  call qword ptr [0xF9A8C08]                    ; [data_f9a8c08] = another thunk [V]

0xe9281b6  mov [rbx],rax
0xe9281b9  test rax,rax
0xe9281bc  je short 0xE928217
0xe9281be  mov [rsi+0x120],rbx                            ; W heap record+0x120
0xe9281c5  mov rcx,[rbp-0x18]
0xe9281c9  call 0xEEC5A10                                ; sub_eec5a10 (unlock)
0xe9281ce  mov al,1
0xe9281d0  add rsp,0x60
0xe9281d4  pop rbx
0xe9281d5  pop rdi
0xe9281d6  pop rsi
0xe9281d7  pop r12
0xe9281d9  pop r14
0xe9281db  pop r15
0xe9281dd  pop rbp
0xe9281de  ret

0xe9281df  mov ecx,0x10
0xe9281e4  call 0x9BC830                                 ; sub_9bc830 (alloc fallback)
0xe9281e9  nop
0xe9281ea  jmp 0xE928156

0xe9281ef  mov ecx,0x10
0xe9281f4  call 0x9BC830
0xe9281f9  nop
0xe9281fa  jmp short 0xE92817C

0xe9281fc  mov ecx,5
0xe928201  call 0xEEC5A00                                ; sub_eec5a00 (error)

0xe928206  mov dword ptr [rsi+0x7C],0x7FFFFFFE
0xe92820d  mov ecx,6
0xe928212  call 0xEEC5A00

0xe928217  mov [rbp-0x20],r14
0xe92821b  mov dword ptr [rdi],0
0xe928221  mov ecx,6
0xe928226  call 0xEEC5A00
0xe92822b  nop
0xe92822c  int3
```

### D3D12 indirect calls in sub_e927fc0

| RVA | Instruction sequence | Object source | Displacement | Slot | D3D12 Method | Verified |
|-----|---------------------|---------------|--------------|------|--------------|----------|
| 0xe928130 | `mov rcx,[0x1233E1A8]` → `mov rax,[rcx]` → `mov rax,[rax+8]` → `call [0xF99FFA0]` | Global context at 0x1233E1A8 → context vtable → context+8 = device | Thunk call, rax holds device* | Unknown (thunk) | **CreateHeap** (expected, slot 28) | [UNVERIFIED: 0xe92813a thunk target resolution] |
| 0xe92815a | Same sequence | Same | Same | Unknown (thunk) | **CreateHeap** (expected, slot 28) | [UNVERIFIED: 0xe928164 thunk target resolution] |

**Notes:**
- The object at `[0x1233E1A8]` is a global context (likely `ID3D12Device` wrapper). Its vtable at `[context]` has at offset +8 a pointer to the actual `ID3D12Device`.
- The CFG thunk at `[0xF99FFA0]` (sub_eea6040) is called with `rax = ID3D12Device*`. The thunk likely loads the real vtable function from the device and calls it. Without analyzing sub_eea6040, the exact slot is [UNVERIFIED].
- Based on the heap creation context and the prior analysis in U-A12c (where `device_vtable+0xD0` = slot 26 = GetCustomHeapProperties was used for heap creation), the intended method here is likely **CreateHeap (slot 28, offset 0xE0)** or **CreateCommittedResource (slot 27, offset 0xD8)**. But the displacement used in the thunk call is not directly visible.
- [UNVERIFIED: 0xe92813a / 0xe928164 need sub_eea6040 analysis to confirm which vtable slot the thunk invokes]

---

## Step 2: sub_e815590 (called for LTLAS from 0xe817070)

### sub_e815590 bounds: [0xe815590..0xe81583f) size 0x2af

**Instruction-complete listing (0xe815590..0xe81583f):**

```
0xe815590  push rsi
0xe815591  push rdi
0xe815592  push rbx
0xe815593  sub rsp,0x80
0xe81559a  mov rax,r8                                     ; rax = 3rd arg (L-string data)
0xe81559d  mov rsi,rdx                                    ; rsi = 2nd arg (output handle record)
0xe8155a0  mov r10d,[rsp+0xD0]                            ; r10d = 6th arg (flags)
0xe8155a8  mov r8,[rsp+0xC0]                              ; r8 = 5th arg
0xe8155b0  mov rdx,[0x1230A0C0]                          ; rdx = stack cookie
0xe8155b7  xor rdx,rsp
0xe8155ba  mov [rsp+0x78],rdx
0xe8155bf  movsxd rdx,r9d                                 ; rdx = 4th arg (index)
0xe8155c2  mov rdi,[rcx+rdx*8+0x19F08]                   ; rdi = context+0x19F08 + index*8 (heap pointer)
0xe8155ca  test rdi,rdi
0xe8155cd  setne dl
0xe8155d0  and dl,[rcx+0x55]                             ; context+0x55 (feature flag)
0xe8155d3  cmp dl,1
0xe8155d6  jne short 0xE815656

0xe8155d8  mov ebx,[rsp+0xC8]                             ; ebx = 7th arg (size/count)
0xe8155df  cmp r9d,5
0xe8155e3  jne 0xE8156B1                                 ; if index != 5

;; Path for index == 5 (LTLAS)
0xe8155e9  lea rcx,[rsp+0x40]
0xe8155ee  mov [rsp+0x38],rcx
0xe8155f3  mov [rsp+0x28],r10d
0xe8155f8  mov [rsp+0x20],ebx
0xe8155fc  mov qword ptr [rsp+0x30],0
0xe815605  mov rcx,rdi                                    ; rcx = heap pointer from context+0x19F08+40
0xe815608  mov rdx,rax                                    ; rdx = L-string
0xe81560b  xor r9d,r9d
0xe81560e  call 0xE928660                                ; sub_e928660 (create placed resource?)
0xe815613  test rax,rax
0xe815616  jne short 0xE815646
0xe815618  mov rcx,[0x12BB4910]                          ; global context
0xe81561f  cmp dword ptr [rcx+0x19F88],5
0xe815626  jl short 0xE815646
0xe815628  mov edx,[rdi+0x28]                            ; R heap+0x28 (error code)
0xe81562b  test edx,edx
0xe81562d  js 0xE815752

0xe815633  mov r8d,3
0xe815639  mov [rcx+0x19F88],r8d                         ; W context+0x19F88 = 3
0xe815640  mov [rcx+0x19F8C],edx                         ; W context+0x19F8C = error

0xe815646  mov [rsi],rax                                 ; W output+0 = resource pointer
0xe815649  mov [rsi+8],ebx                               ; W output+8 = size/count
0xe81564c  mov rax,[rsp+0x40]
0xe815651  jmp 0xE815728

;; Path for index != 5
0xe815656  mov rdx,[rcx+0x400]                           ; R context+0x400
0xe81565d  mov dword ptr [rsp+0x40],1
0xe815665  mov qword ptr [rsp+0x48],0
0xe81566e  mov [rsp+0x50],r8
0xe815673  mov rax,0x1000100000001
0xe81567d  mov [rsp+0x58],rax
0xe815682  movaps xmm0,[0xEF9FDD0]                       ; constant data
0xe815689  movups [rsp+0x60],xmm0
0xe81568e  mov [rsp+0x70],r10d
0xe815693  mov qword ptr [rsp+0x20],0
0xe81569c  lea rax,[rsp+0x40]
0xe8156a1  mov rcx,rsi                                    ; rcx = output handle record
0xe8156a4  mov r8d,r9d
0xe8156a7  mov r9,rax
0xe8156aa  call 0xE806560                                ; sub_e806560 (generic create)
0xe8156af  jmp short 0xE81572C

0xe8156b1  xorps xmm0,xmm0
0xe8156b4  movups [rsp+0x30],xmm0
0xe8156b9  mov [rsp+0x28],r10d
0xe8156be  mov [rsp+0x20],ebx
0xe8156c2  mov rcx,rdi                                    ; rcx = heap pointer
0xe8156c5  mov rdx,rax                                    ; rdx = L-string
0xe8156c8  xor r9d,r9d
0xe8156cb  call 0xE928FB0                                ; sub_e928fb0 (create resource)
0xe8156d0  test rax,rax
0xe8156d3  je short 0xE8156F0
0xe8156d5  mov [rsi],rax                                 ; W output+0 = resource
0xe8156d8  mov [rsi+8],ebx                               ; W output+8 = size
0xe8156db  mov rcx,[rax]                                 ; R resource vtable
0xe8156de  mov rdx,[rcx+0x58]                            ; R resource_vtable+0x58
0xe8156e2  mov rcx,rax                                    ; rcx = resource
0xe8156e5  mov rax,rdx                                    ; rax = resource_vtable[11]
0xe8156e8  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040 [V]

0xe8156ee  jmp short 0xE815728

0xe8156f0  mov rax,[0x12BB4910]                          ; global context
0xe8156f7  cmp dword ptr [rax+0x19F88],5
0xe8156fe  jl short 0xE81571C
0xe815700  mov ecx,[rdi+0x28]                            ; R heap+0x28
0xe815703  test ecx,ecx
0xe815705  js 0xE81579E

0xe81570b  mov edx,3
0xe815710  mov [rax+0x19F88],edx
0xe815716  mov [rax+0x19F8C],ecx

0xe81571c  mov qword ptr [rsi],0
0xe815723  mov [rsi+8],ebx
0xe815726  xor eax,eax

0xe815728  mov [rsi+0x10],rax                            ; W output+0x10

0xe81572c  mov rax,[rsp+0x78]
0xe815731  xor rax,rsp
0xe815734  mov rcx,[0x1230A0C0]
0xe81573b  cmp rcx,rax
0xe81573e  jne 0xE815831
0xe815744  mov rax,rsi
0xe815747  add rsp,0x80
0xe81574e  pop rbx
0xe81574f  pop rdi
0xe815750  pop rsi
0xe815751  ret

;; Error handling for HRESULT checks
0xe815752  mov r8d,4
0xe815758  cmp edx,0x887A0004
0xe81575e  jg 0xE8157E5
0xe815764  lea r9d,[rdx+0x7789F798]
0xe81576b  cmp r9d,0xC
0xe81576f  ja short 0xE815781
0xe815771  mov r10d,0x1101
0xe815777  bt r10d,r9d
0xe81577b  jb 0xE815639

0xe815781  cmp edx,0x8007000E
0xe815787  je 0xE815633
0xe81578d  cmp edx,0x88760826
0xe815793  je 0xE815639
0xe815799  jmp 0xE815633

0xe81579e  mov edx,4
0xe8157a3  cmp ecx,0x887A0004
0xe8157a9  jg short 0xE81580B
0xe8157ab  lea r8d,[rcx+0x7789F798]
0xe8157b2  cmp r8d,0xC
0xe8157b6  ja short 0xE8157C8
0xe8157b8  mov r9d,0x1101
0xe8157be  bt r9d,r8d
0xe8157c2  jb 0xE815710

0xe8157c8  cmp ecx,0x8007000E
0xe8157ce  je 0xE81570B
0xe8157d4  cmp ecx,0x88760826
0xe8157da  je 0xE815710
0xe8157e0  jmp 0xE81570B

0xe8157e5  lea r9d,[rdx+0x7785FFFB]
0xe8157ec  cmp r9d,0x1D
0xe8157f0  ja 0xE815633
0xe8157f6  mov r10d,0x28000007
0xe8157fc  bt r10d,r9d
0xe815800  jb 0xE815639
0xe815806  jmp 0xE815633

0xe81580b  lea r8d,[rcx+0x7785FFFB]
0xe815812  cmp r8d,0x1D
0xe815816  ja 0xE81570B
0xe81581c  mov r9d,0x28000007
0xe815822  bt r9d,r8d
0xe815826  jb 0xE815710
0xe81582c  jmp 0xE81570B

0xe815831  mov rcx,[rsp+0x78]
0xe815836  xor rcx,rsp
0xe815839  call 0xE951550
0xe81583e  int3
```

### D3D12 indirect calls in sub_e815590

| RVA | Instruction sequence | Object source | Displacement | Slot | D3D12 Method | Verified |
|-----|---------------------|---------------|--------------|------|--------------|----------|
| 0xe8156db | `mov rcx,[rax]` → `mov rdx,[rcx+0x58]` → `mov rax,rdx` → `call [0xF99FFA0]` | `rax` = resource pointer from sub_e928fb0 → `[rax]` = resource vtable | +0x58 (88 bytes) | 11 (0x58/8) | **CreateComputePipelineState** | [V] displacement, [UNVERIFIED: 0xe8156db object is ID3D12Resource not ID3D12Device] |
| 0xe8156e8 | `call qword ptr [0xF99FFA0]` | CFG thunk, `rax` holds vtable[11] | Thunk | Thunk | Thunk to vtable[11] | [V] thunk call |

**Critical analysis of 0xe8156db-0xe8156e8:**
- `rax` at 0xe8156d5 comes from `sub_e928fb0` return value → this is an `ID3D12Resource*` (placed/reserved resource), NOT an `ID3D12Device*`
- `[rax]` = resource vtable
- `[rax+0x58]` = resource vtable slot 11
- ID3D12Resource vtable (after IUnknown 0-2): slot 3=GetPrivateData, 4=SetPrivateData, 5=SetPrivateDataInterface, 6=SetName, 7=GetDevice, 8=Map, 9=Unmap, 10=GetDesc, 11=GetGPUVirtualAddress...
- **Slot 11 of ID3D12Resource = GetGPUVirtualAddress**, not CreateComputePipelineState (which is a Device method)
- The SDK order given in the brief is for **ID3D12Device**. For ID3D12Resource, the vtable differs.
- [UNVERIFIED: 0xe8156db need ID3D12Resource vtable layout to confirm slot 11 meaning]

---

## Verification
- verify_oc.py: PASS (308/308 instructions matched)

## Gaps
- [UNVERIFIED: 0xe92813a / 0xe928164 sub_eea6040 thunk behavior — which device vtable slot does it call when rax=ID3D12Device*?]
- [UNVERIFIED: 0xe8156db ID3D12Resource vtable slot 11 = GetGPUVirtualAddress per SDK, but brief's slot table is for ID3D12Device]
- [UNVERIFIED: sub_e9282e0, sub_e928660, sub_e928fb0, sub_eec59f0, sub_eec6de0, sub_eea6040, sub_eec5a10, sub_eec5a00, sub_a6a70, sub_116730, sub_9bc830, sub_e806560, sub_e92bc50, sub_e928480, sub_e935700, sub_e951550 — callees not analyzed]
- [UNVERIFIED: Global context at 0x1233E1A8 structure and vtable layout]
- [UNVERIFIED: Global context at 0x12BB4910 structure (used in sub_e815590)]

## TOOL REQUESTS
- `rdis fn` for sub_eea6040 (CFG thunk at 0xF99FFA0) to understand thunk dispatch logic
- `rdis fn` for sub_e928fb0 to confirm it returns ID3D12Resource*
- ID3D12Resource vtable layout reference for slot verification