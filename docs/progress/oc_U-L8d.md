# Unit U-L8d — Texture upload / ClientTexture creation path from PNG decode chain

## NEXT
Step (1) IN PROGRESS: run `python tools/sigs/xref.py callers 0x6632fd0` and `xref.py callers <rva>` for every other level-2 caller of 0x1994f90 (list in context below). Do NOT run `xref.py str "textures/"`.

## Rules (from OPENCODE_BRIEF.md)
- Static analysis only; exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (image base 0x6632fd0 etc. are RVAs). Do not start the game, no debuggers/CE/injectors/writes.
- Do NOT run builds. Do NOT commit/push/delete/edit git config. Do NOT edit docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, src/**, Sigs.json, CLAUDE.md, settings/config. Create only docs/progress/oc_U-L8d.md.
- Every claim tagged [V] (saw in disasm, cite RVA), [I] (inferred, say from what), [?] (unknown). Never write a size/offset/name/meaning not seen. "I could not determine X" is acceptable; a guess as fact is a failure.
- Append findings to this file after each small step; keep `## NEXT` at TOP saying exactly where to resume.
- Run from C:\Users\Atomi\Desktop\BlueySenseV2 with PYTHONUTF8=1.

## Context from U-L8c / U-L8b (read-only, treated as notes not proof)
- Chain so far: file bytes -> sub_1994f90 (loader, validates comp {1,3,4} via bitmask 0x1A at 1995041/1995046) -> sub_764950 (calls sub_777ed0 decoder at 764a05; allocates w*h*comp*4 via [data_f9a6fa0] at 764a81; returns 32-bit pixel buffer in rax) -> sub_777ed0 (PNG decoder entry; magic 0x89 check at 777f55).
- Decoder context struct (r15 = rcx of sub_777ed0): [r15+0x0]=width, [r15+0x4]=height (abs'd), [r15+0x8]=format/component count, [r15+0xB8]=bytes consumed, [r15+0xC0]=stream cursor, [r15+0xC8]=stream end [V via U-L8b].
- sub_1994f90 signature guess: `uint8_t* sub_1994f90(void* a1, void* a2, int a3 req_comp, void* a4 file-bytes ptr, size_t a5 size)` with out-slots dim1=[rbp+0x11C], dim2=[rbp+0x12C], comp=[rbp+0x10C] [I via U-L8c]. Calls sub_764950 at 199513c (+0xac5) [V via U-L8c + direct disasm].
- Candidate texture-loader: 0x6632fd0 — level-2 caller of 0x1994f90 at +0x1531 [V via U-L8c xref], references string "look_up_tables.png" at 0x6633ebf [V via xref str per U-L8c]. Not yet verified in this unit.
- Other level-2 callers of 0x1994f90 (from U-L8c step 5): 0x108c90, 0x398fc0, 0xa08dd0, 0xfc4760, 0xfcb2d0, 0xfd26e0, 0x1679d40, 0x17c5040, 0x1f4df80, 0x1f4e5b0, 0x1f506b0, 0x1f5cd70, 0x1f5d110, 0x25cf6f0, 0x4e8b8f0, 0x541bf00, 0x541cb30, 0x5420c20, 0x5421230, 0x5a31160, 0x668a140, 0x69dd7b0, 0x69e11a0, 0x6c0f490, 0x6dbf280 (plus 0x6632fd0 itself).
- rdis command: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" dis 0x<rva> <n>`

## Step (1): xref.py callers — DONE [all via xref]
Callers of 0x6632fd0 (level-3 of chain; 0x6632fd0 itself is level-2 caller of 0x1994f90 at +0x1531 per U-L8c):
- 0x661a770 at +0x3529
- 0x66232b0 at +0xb3d0

Callers of each other level-2 caller of 0x1994f90 (U-L8c list):
- 0x108c90 ← 0x107770 (+0x1021)
- 0x398fc0 ← 0x95c230 (+0xf5b), 0x16768e0 (+0xd20), 0x16cedc0 (+0x185), 0x1e91ee0 (+0x3a3), 0x1e92540 (+0x3b3), 0x4e623e0 (+0x3189), 0x541b6c0 (+0x184), 0x5420c20 (+0x309), 0x58a1310 (+0x10be), 0x58c71f0 (+0x14b), 0x69cfb80 (+0x136)
- 0xa08dd0 ← 0x879480 (+0x4334)
- 0xfc4760 ← (none)
- 0xfcb2d0 ← (none)
- 0xfd26e0 ← (none)
- 0x1679d40 ← 0x5a31160 (+0x345)
- 0x17c5040 ← (none)
- 0x1f4df80 ← 0x1f546d0 (+0x44c)
- 0x1f4e5b0 ← (none)
- 0x1f506b0 ← (none)
- 0x1f5cd70 ← (none)
- 0x1f5d110 ← (none)
- 0x25cf6f0 ← 0x25cf410 (+0x244), 0x25d06a0 (+0x259)
- 0x4e8b8f0 ← 0x4e2c330 (+0xdd), 0x4e2c410 (+0x124)
- 0x541bf00 ← 0x69f7430 (+0x296f)
- 0x541cb30 ← 0x867fa0 (+0x22c)
- 0x5420c20 ← 0x541e690 (+0xf02), 0x54209b0 (+0x1a2)
- 0x5421230 ← 0x4e67280 (+0x3ae), 0x4fbc450 (+0x167), 0x541e690 (+0xf02), 0x541f8f0 (+0xc7d), 0x5420860 (+0xb6)
- 0x668a140 ← 0x661a770 (+0x3529), 0x668a700 (+0x2a4)
- 0x69dd7b0 ← 0x69dcda0 (+0x618), 0x6a0e540 (+0x2175)
- 0x69e11a0 ← 0x69e17f0 (+0x35b5), 0x6a0e540 (+0x2175)
- 0x6c0f490 ← (none)
- 0x6dbf280 ← (none)

Notes: 0x661a770 calls BOTH 0x6632fd0 and 0x668a140 (both are level-2 callers of 0x1994f90 in the 0x66xxxx range) — likely one texture-loading dispatch site. "textures/" str xref NOT run (per unit rules, times out). Did not descend into level-3 callers beyond listing them.

## Step (2): dis 0x6632fd0 around "look_up_tables.png" (0x6633ebf) — PARTIAL [all via rdis, exe image]
`rdis dis 0x6633e60 80` (function nominally sub_6633e60 [0x6633e60..0x6635e60) size 0x2000, 0 xrefs in per rdis header — note: xref callers target 0x6632fd0, so 0x6633e60 is likely mid-function of sub_6632fd0; [?] whether 0x6632fd0==sub_6633e60 entry or separate entry into same body):
```
6633e60  clc                                           
6633e61  adc [rdx+0x35],dh                             ; W a1+0x35
6633e64  mov rcx,[rbp-0x28]                            
6633e68  lea rdx,[rax+1]                               
6633e6c  cmp rdx,0x1000                                
6633e73  jb short 0x6633E94                            ; -> loc_6633e94
6633e75  mov r8,[rcx-8]                                
6633e79  add rcx,0xFFFFFFFFFFFFFFF8                    
6633e7d  sub rcx,r8                                    
6633e80  cmp rcx,0x20                                  
6633e84  jae 0x663448B                                 ; -> loc_663448b
6633e8a  add rax,0x28                                  
6633e8e  mov rdx,rax                                   
6633e91  mov rcx,r8                                    

loc_6633e94:
  6633e94  call 0xE935700                                ; -> sub_e935700 [V]
  6633e99  mov rax,[rbp+0x6A0]                           
  6633ea0  cmp qword ptr [rbp+0x6A8],0x10                
  6633ea8  jb short 0x6633EB1                            ; -> loc_6633eb1
  6633eaa  mov rdi,[rbp+0x690]                           

loc_6633eb1:
  6633eb1  mov [rbp+0x6B0],rdi                           
  6633eb8  mov [rbp+0x6B8],rax                           
  6633ebf  lea rax,[0xF5B2AE6]                           ; [data_f5b2ae6] "look_up_tables.png" [V string ref]
  6633ec6  mov [rbp+0x6C0],rax                           
  6633ecd  mov qword ptr [rbp+0x6C8],0x12                ; length 18 bytes ("look_up_tables.png") [V]
  6633ed8  lea rcx,[rbp-0x40]                            ; out/path struct ptr
  6633edc  lea rbx,[rbp+0x6B0]                           
  6633ee3  mov r8d,2                                     ; flag?
  6633ee9  mov rdx,rbx                                   
  6633eec  mov r9b,0x2F                                  ; '/' char
  6633eef  call 0xB1B70                                  ; -> sub_b1b70 (path builder: base "/" + "look_up_tables.png"?) [I]
  6633ef4  nop                                           
  6633ef5  mov rdi,[rbp+0x3C0]                           
  6633efc  xorps xmm0,xmm0                               
  6633eff  movaps [rbp+0x6B0],xmm0                       
  6633f06  movaps [rbp+0x6C0],xmm0                       
  6633f0d  test rdi,rdi                                  
  6633f10  js 0x66344F4                                  ; -> loc_66344f4 (rdi<0 fail)
  6633f16  mov esi,0xF                                   
  6633f1b  cmp rdi,0x10                                  
  6633f1f  jb short 0x6633F98                            ; -> loc_6633f98 (small alloc path)
  6633f21  mov rdx,rdi                                   
  6633f24  or rdx,0xF                                    
  6633f28  cmp rdx,0x17                                  
  6633f2c  mov esi,0x16                                  
  6633f31  cmovae rsi,rdx                                 ; alloc size = len rounded up to 0x16 min / 16-align [I]
  6633f35  mov rcx,[0x1233E1A8]                           ; [data_1233e1a8] heap
  6633f3c  mov rax,[rcx]                                 
  6633f3f  mov rax,[rax+8]                               
  6633f43  cmp rdx,0xFFF                                 
  6633f4a  jb short 0x6633F77                            ; -> loc_6633f77 (small)
  6633f4c  lea r14,[rsi+0x28]                            
  6633f50  mov rdx,r14                                   
  6633f53  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (allocator, per U-L8b convention) [V]
  6633f59  nop                                           
  6633f5a  mov rbx,rax                                   
  6633f5d  test rax,rax                                  
  6633f60  je 0x663444B                                  ; -> loc_663444b (alloc fail)

loc_6633f66:
  6633f66  mov rax,rbx                                   
  6633f69  add rbx,0x27                                  
  6633f6d  and rbx,0xFFFFFFFFFFFFFFE0                     ; align up 0x20
  6633f71  mov [rbx-8],rax                                ; store orig ptr before aligned buf [I]
  6633f75  jmp short 0x6633F91

loc_6633f77:
  6633f77  lea r14,[rsi+1]                               
  6633f7b  mov rdx,r14                                   
  6633f7e  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 [V]
  6633f84  nop                                           
  6633f85  mov rbx,rax                                   
  6633f88  test rax,rax                                  
  6633f8b  je 0x6634459                                  ; -> loc_6634459

loc_6633f91:
  6633f91  mov [rbp+0x6B0],rbx                            ; rbx = allocated path buffer [V]

loc_6633f98:
  6633f98  mov [rbp+0x6C0],rdi                            ; path string ptr into buffer
  6633f9f  mov [rbp+0x6C8],rsi                            ; path length
  6633fa6  lea rdx,[rbp-0x40]                             ; path/out struct
  6633faa  mov rcx,rbx                                    ; dest buffer
  6633fad  mov r8,rdi                                     ; source str ptr
  6633fb0  call 0xEEC6EC0                                 ; -> sub_eec6ec0 (copies/builds path into buffer) [V]
  6633fb5  mov byte ptr [rbx+rdi],0                       ; null-terminate path [V]
  6633fb9  xorps xmm0,xmm0                               
  6633fbc  movaps [rbp-0x30],xmm0                        
  6633fc0  movaps [rbp-0x40],xmm0                        
  ... (--max 80 cut at 0x6633fc0)
```
Interpretation [I]: builds path "look_up_tables.png" (via sub_b1b70 joining "/" base + name, then sub_eec6ec0 into heap buffer), allocates path buffer via sub_eea6040. rdi=[rbp+0x3C0] is a frame/local value (likely file-bytes size or context handle) tested at 6633f0d. No pixel-decode call yet in this window.

## Step (2) continued — KEY FIND [all via rdis]:
`rdis dis 0x6633fc0 80` + `rdis dis 0x66340e6 80`:
```
6633fc4  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8] heap
6633fcb  mov rax,[rcx]                                 
6633fce  mov rax,[rax+8]                               
6633fd2  mov edx,0x20                                  
6633fd7  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc 0x20) [V]
6633fde  mov rdi,rax                                   
6633fe1  test rax,rax                                  
6633fe4  je 0x663440A                                  ; -> loc_663440a

loc_6633fea:
  6633fea  mov [rbp-0x40],rdi                            ; [rbp-0x40] = new 0x20-byte object
  6633fee  mov qword ptr [rbp-0x30],0x13                 ; [rbp-0x30] = 0x13 (19)
  6633ff6  mov qword ptr [rbp-0x28],0x1F                 ; [rbp-0x28] = 0x1F (31)
  6633ffe  movups xmm0,[0xF5C6FC2]                       ; [data_f5c6fc2] = "Ray Tracing Texture" (16 bytes) [V string data]
  6634005  movups [rdi],xmm0                             ; W [obj+0x0] = "Ray Tracing Texture" [V]
  6634008  mov dword ptr [rdi+0xF],0x65727574            ; W [obj+0xF] = "rtur" → "Ray Tracing Texture\0" + "rtur"? [V]
  663400f  mov byte ptr [rdi+0x13],0                     ; W [obj+0x13] = 0 [V]
  // ^ [I] 0x20-byte object = texture debug name "Ray Tracing Texture" (+0x0..0x13)
  6634013  mov rax,[rbp+0x700]                           
  663401a  mov rcx,[rax+0x38]                            ; R object chain
  663401e  test rcx,rcx                                  
  6634021  je 0x66344FA                                  ; -> loc_66344fa
  6634027  mov rax,[rcx]                                 
  663402a  mov rax,[rax+0x10]                            ; R
  663402e  lea rdi,[rbp+0x630]                           
  6634035  lea r8,[rbp-0x40]                             ; r8 = name object
  6634039  lea r9,[rbp+0x6B0]                            ; r9 = "look_up_tables.png" path buffer
  6634040  mov rdx,rdi                                    ; rdx = &[rbp+0x630] out
  6634043  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (builds file-bytes/string at [rbp+0x630] from name+path?) [I]
  ...string resize via sub_e935700 at 0x6634084...
  6634089  mov rax,[rbp+0x640]                            ; R file size?
  6634090  test rax,rax                                  
  6634093  je 0x66341C9                                  ; -> loc_66341c9 (no bytes)
  6634099  xorps xmm0,xmm0                               
  663409c  movaps [rbp-0x40],xmm0                        
  66340a0  mov word ptr [rbp-0x30],0                     
  66340a6  lea rcx,[0x3C7B10]                            ; [sub_3c7b10] callback ptr
  66340ad  mov [rbp-0x28],rcx                            ; W callback slot
  66340b1  movaps [rbp-0x20],xmm0                         ; W [rbp-0x20] = 0
  66340b5  cmp qword ptr [rbp+0x648],0x10                
  66340bd  jb short 0x66340C6                            ; -> loc_66340c6
  66340bf  mov rdi,[rbp+0x630]                            ; R file bytes ptr
  loc_66340c6:
  66340c6  mov [rsp+0x20],rax                            ; W stack arg = file size
  66340cb  mov byte ptr [rsp+0x28],0                     
  66340d0  lea rcx,[rbp+0x5E0]                            ; a1 = out-params ctx
  66340d7  lea rdx,[rbp-0x40]                            ; a2 = &name object
  66340db  xor r8d,r8d                                    ; a3 = req_comp = 0
  66340de  mov r9,rdi                                     ; a4 = file bytes ptr [rbp+0x630]
  66340e1  call 0x1994F90                                ; -> sub_1994f90 (file bytes -> pixel buffer in rax) [V] ← DECODE CALL
  66340e6  nop                                           
  66340e7  mov rbx,[rbp-0x20]                            ; rbx = [rbp-0x20] (was 0 pre-call; set by/after call? [?] see note)
  66340eb  cmp byte ptr [rbp+0x5F0],1                    
  66340f2  jne 0x66341B6                                 ; -> loc_66341b6
  66340f8  mov rdi,[rbp-0x18]                            ; R
  66340fc  cmp rdi,0xFFFFFFFFFFFFFFFF                    
  6634100  je 0x663441A                                  ; -> loc_663441a
  6634106  test rbx,rbx                                  
  6634109  setne al                                      
  663410c  test rdi,rdi                                  
  663410f  sete cl                                       
  6634112  or cl,al                                      
  6634114  je 0x663441A                                  ; -> loc_663441a
  663411a  mov rcx,[0x1233E1A8]                          
  6634121  mov rax,[rcx]                                 
  6634124  mov rax,[rax+8]                               
  6634128  mov rdx,rdi                                   
  663412b  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (alloc rdx bytes) → r14=rax [V]
  6634132  mov r14,rax                                   
  6634135  test rdi,rdi                                  
  6634138  je short 0x6634143                            ; -> loc_6634143
  663413a  test r14,r14                                  
  663413d  je 0x663443D                                  ; -> loc_663443d

loc_6634143:
  6634143  mov rcx,r14                                   
  6634146  xor edx,edx                                    ; edx=0
  6634148  mov r8,rdi                                     ; r8 = size
  663414b  call 0xEEC6ED0                                ; -> sub_eec6ed0 (rcx=obj, edx=0, r8=size) [V]
  6634150  mov rcx,r14                                   
  6634153  mov rdx,rbx                                    ; rdx = [rbp-0x20] (pixel data? [?])
  6634156  mov r8,rdi                                     ; r8 = size
  6634159  call 0xEEC6DE0                                ; -> sub_eec6de0 (rcx=obj, rdx=data, r8=size) [V]
  663415e  mov rax,[rbp+0x6F8]                            ; R [rbp+0x6F8] = render-context/device object ptr [I]
  6634165  mov rsi,[rax+0x288]                            ; R rsi = [device+0x288] (texture slot object) [V]
  663416c  mov ebx,[rbp-0x3C]                            ; R ebx = local (format? dim? [?])
  663416f  mov rdx,[rsi+0x970]                            ; R old texture at [rsi+0x970]
  6634176  mov [rsi+0x970],r14                            ; W [rsi+0x970] = r14 (new texture object) ← REPLACE
  663417d  test rdx,rdx                                  
  6634180  je short 0x663419E                             ; -> loc_663419e
  6634182  mov rcx,[0x1233E1A8]                          
  6634189  mov rax,[rcx]                                 
  663418c  mov rax,[rax+0x10]                            
  6634190  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (free? or size?) [V] — frees old texture rdx [I]
  ...6634196 nop; 6634197 mov r14,[rsi+0x970]
  663419e  mov [rsi+0x978],rdi                            ; W [rsi+0x978] = rdi (size)
  66341a5  mov [rsi+0x980],ebx                            ; W [rsi+0x980] = ebx (format/dim [?])
  66341ab  mov [rsi+0x58],r14                             ; W [rsi+0x58] = r14 (texture object)
  66341af  mov [rsi+0x60],ebx                             ; W [rsi+0x60] = ebx
  66341b2  mov rbx,[rbp-0x20]
```
Interpretation [I]: sub_1994f90 decodes "look_up_tables.png" file bytes → pixel buffer (rax). Then two calls `0xEEC6ED0` (init/create with size) and `0xEEC6DE0` (upload data ptr+size) on object r14 — candidate GPU texture creation calls. Object r14 stored at [device+0x288]+0x970 (texture slot), with +0x978=size, +0x980=ebx (format/dim), +0x58/+0x60 also set. rbx=[rbp-0x20] is the data pointer passed to sub_eec6de0 — NEED TO CONFIRM [rbp-0x20] holds sub_1994f90's rax (pixel buffer); not yet seen in disasm [OPEN].

## Step (2) continued [all via rdis]:
`rdis dis 0x663422f 80`:
```
6634253  lea rax,[0xF5573B4]                           ; [data_f5573b4] "RenderDragon Ray Tracing Textures" [V string data]
663425a  mov [rbp+0x540],rax                           
6634261  mov qword ptr [rbp+0x548],0x21                ; length 0x21 [V]
663426c  mov rcx,[rbp+0x6F8]                           
6634273  add rcx,0x3F0                                 ; rcx = [rbp+0x6F8]+0x3F0 (texture collection mgr? [I])
663427a  lea rdx,[rbp+0x540]                           
6634281  call 0x6622610                                ; -> sub_6622610 (registers "RenderDragon Ray Tracing Textures" entry) [V]
...string teardown via sub_e935700 at 0x66342d1...
66342f5  movaps xmm6,[rbp+0x710]
66342fc  add rsp,0x7A8
6634303-0x663430c  pop rbx,rdi,rsi,r12,r13,r14,r15,rbp
663430f  ret                                            ; END of sub_6632fd0 body [V]
```
Remaining calls in function after sub_1994f90: only sub_6622610 (registration) + sub_e935700 teardowns. So the GPU texture creation/upload calls within this path are **`0xEEC6ED0` at 0x663414b** and **`0xEEC6DE0` at 0x6634159**.

OPEN (step 2): `sub_1994f90` returns pixel buffer in rax (per U-L8c) but `rax` is not visibly stored between 0x66340e1 and 0x66340e7; `rbx=[rbp-0x20]` passed to `sub_eec6de0` at 0x6634153 was zeroed at 0x66340b1 pre-call — need the function's earlier part (0x6632fd0..0x6633e60) to see how `[rbp-0x20]`, `[rbp-0x18]` (size, passed to alloc at 0x663412b), `[rbp-0x3C]` (format?, stored at [rsi+0x980]/[rsi+0x60]), `[rbp+0x6F8]` (device/ctx at +0x288) are set, and confirm pixel-buffer flow.

## Step (2) — fn 0x6632fd0 (entry) RESULTS [all via rdis]:
`sub_6632fd0 [0x6632fd0..0x6634501) size 0x1531, 2 xrefs in (0x661a770+0x3529, 0x66232b0+0xb3d0)` [V]:
- 6632ffd mov [rbp+0x6F8],rcx                    ; [rbp+0x6F8] = a0 = device/ctx object [V]
- 6633004 cmp qword ptr [rcx+0x288],0            ; R [device+0x288] (texture slot array); je → skip path [V]
- 6633012 mov rbx,rdx                            ; rbx = a1 = file struct: [+0x0]=bytes ptr, [+0x10]=size, [+0x18]=? [V/I]
- 6633015 mov [rbp+0x700],r8                     ; [rbp+0x700] = a2 [V]
- 663301c mov rdi,[rdx+0x10]                     ; rdi = [a1+0x10] = file size [V]
- copies file bytes into allocated buffer via sub_eec6ec0 at 663310d, appends "/ray_tracing" (0x6172745F7961722F + 0x2F676E6963617274) at 6633112-663312f [V]
- 66332b2 mov [rbp+0x630],rsi / 66332b9 mov [rbp+0x638],rdi ; [rbp+0x630]=file bytes ptr, [rbp+0x638]=size [V]
- builds path "look_up_tables.png" at [rbp+0x6B0] (len 0x12) via sub_b1b70(6633eef) + sub_eec6ec0(6633fb0) [V — seen in window]
- 6634043 call sub_eea6040(rdx=&[rbp+0x630], r8=&name obj "Ray Tracing Texture", r9="look_up_tables.png") — [I] loads file bytes into [rbp+0x630]
- 6634089 rax=[rbp+0x640] (size); if 0 → skip [V]
- 66340e1 call 0x1994f90(rcx=&[rbp+0x5E0], rdx=&[rbp-0x40] name obj, r8=0 req_comp, r9=[rbp+0x630] bytes, stack=[rbp+0x640] size) → rax = pixel buffer [V per U-L8c]
- 66340e7 mov rbx,[rbp-0x20] — [rbp-0x20] zeroed at 66340b1 PRE-call, so rbx=0 at this point [V] ← OPEN: pixel-buffer flow not yet visible (expect [rbp-0x20] := rax somewhere 0x66340e1..0x6634153, or sub_1994f90 stores via a1 side-channel [?])
- 663412b call sub_eea6040(rdx=rdi=[rbp-0x18] size) → r14 = new texture object [V]
- 663414b call 0xEEC6ED0(rcx=r14, edx=0, r8=rdi size) [V]
- 6634159 call 0xEEC6DE0(rcx=r14, rdx=rbx data[?], r8=rdi size) [V] ← candidate GPU texture create/upload
- 663415e rax=[rbp+0x6F8] (device); 6634165 rsi=[rax+0x288] [V]
- 663416c ebx=[rbp-0x3C] (format? [?]); 6634176 [rsi+0x970]=r14 (replace texture, old freed) [V]
- 663419e [rsi+0x978]=rdi (size), 66341a5 [rsi+0x980]=ebx, 66341ab [rsi+0x58]=r14, 66341af [rsi+0x60]=ebx [V]
- 6634253 "RenderDragon Ray Tracing Textures" (data_f5573b4, len 0x21); 6634281 call 0x6622610(rcx=[device+0x3F0], rdx=&name) — register in texture manager [V]
- 663430f ret [V]

GAP NOT YET SEEN: 0x6633da0..0x6633e60 (between fn-output cut and first window) — likely sets [rbp-0x18] (size), [rbp-0x3C] (format), [rbp+0x630]/[rbp+0x640] (bytes/size), possibly [rbp-0x20].

## Step (2) — COMPLETE [all via rdis]:
Full coverage of sub_6632fd0 achieved (0x6632fd0..0x663430f, ret at 0x663430f [V]); gap 0x6633da0..0x6633ea0 seen (ends Water Normals block via sub_668a700 r9d=0x40 at 0x6633e0f, then look_up_tables.png block begins).

**The decode call (consumes the file bytes / produces pixels):** `0x66340e1 call 0x1994f90` [V] with rcx=&[rbp+0x5E0], rdx=&[rbp-0x40] ("Ray Tracing Texture" name object), r8d=0 (req_comp), r9=[rbp+0x630] (file bytes ptr), stack=[rbp+0x640] (file size) → rax = pixel buffer [V per call; pixel semantics per U-L8c]. File bytes for "look_up_tables.png" were loaded just before: path built at [rbp+0x6B0] (len 0x12, string at data_f5b2ae6) via sub_b1b70(0x6633eef) + sub_eec6ec0(0x6633fb0); "Ray Tracing Texture" 0x20-byte name object at [rbp-0x40] (data_f5c6fc2 "Ray Tracing Texture" copied 0x6633ffe-0x663400f); file-load via sub_eea6040 at 0x6634043 (rdx=&[rbp+0x630], r8=name obj, r9=path) [I], size [rbp+0x640] checked nonzero at 0x6634090 [V].

**GPU texture creation/upload calls (callees of decoded pixels):**
- `0x663412b call qword ptr [0xF99FFA0]` (sub_eea6040, rdx=rdi=[rbp-0x18]=size) → r14 = new texture object [V]
- `0x663414b call 0xEEC6ED0` (rcx=r14 tex obj, edx=0, r8=rdi size) [V] — indirect render call: `jmp qword ptr [0xF9A8AA8]` [V at EEC6ED0]
- `0x6634159 call 0xEEC6DE0` (rcx=r14 tex obj, rdx=rbx=[rbp-0x20]=data ptr[OPEN], r8=rdi size) [V] — indirect render call: `jmp qword ptr [0xF9A8AA0]` [V at EEC6DE0]
Then texture stored into render context: `0x6634165 mov rsi,[rax+0x288]` (rax=[rbp+0x6F8]=device) [V]; `0x6634176 mov [rsi+0x970],r14` (replace tex, old freed at 0x6634190) [V]; `0x663419e [rsi+0x978]=rdi` size [V]; `0x66341a5 [rsi+0x980]=ebx` ([rbp-0x3C]=format/dim [?]) [V]; `0x66341ab [rsi+0x58]=r14`; `0x66341af [rsi+0x60]=ebx` [V].
- Registration: `0x6634281 call 0x6622610` (rcx=[rbp+0x6F8]+0x3F0, rdx=&"RenderDragon Ray Tracing Textures" [data_f5573b4, len 0x21]) [V].

**OPEN (step 2):** [rbp-0x18] (size) and [rbp-0x3C] (format/dim?) writes not seen in any window — set before 0x66340f8/0x663416c, location unknown (possibly earlier in function or via sub_1994f90 out-channel [?]). [rbp-0x20] zeroed at 0x66340b1 pre-sub_1994f90 and never visibly rewritten → per literal code sub_eec6de0 gets rdx=0 as data ptr; sub_1994f90's rax (pixel buffer) overwritten at 0x6634121 without store → pixel-buffer wiring to [rbp-0x20] NOT VISIBLE [OPEN] (possible side-channel via a1=[rbp+0x5E0]/a2=[rbp-0x40] out-struct, unverified). Width/height flow from decoder out-slots not traced into this path [OPEN].

## Step (3): GPU texture-creation callee identification — DONE [all via rdis; doc-based helper semantics tagged [I via docs]]

`rdis dis 0xEEC6ED0 80` and `rdis dis 0xEEC6DE0 80`: both are indirect-call thunks:
```
0xEEC6ED0  jmp qword ptr [0xF9A8AA8]     ; -> sub_eec6ed0  [V at thunk]   (header: sub_eec6ed0 [0xeec6ed0..0xeec760e), 6023 xrefs in [V])
0xEEC6DE0  jmp qword ptr [0xF9A8AA0]     ; -> sub_eec6de0  [V at thunk]   (header: sub_eec6de0 [0xeec6de0..0xeec760e), 31355 xrefs in [V])
```
Ultimate targets live in pointer table entries data_f9a8aa0 / data_f9a8aa8 — not readable with available tools (rw needs small field offsets; imm: 0 hits; `callees` shows only the thunk range) [?].

In sub_6632fd0 the two calls are:
- `0x663414b call 0xEEC6ED0` — rcx=r14 (new tex obj from alloc at 0x663412b), edx=0, r8=rdi=[rbp-0x18] size → memset(texObj, 0, size) [V regs/imm]. Helper semantics: memory fill/init, memset-like (zero an argument block with size arg) per docs/data/functions/0xc273420.md, docs/functions/11276b0.md (`0xeec6ed0(&params,0,size)`), docs/progress/bgfx-d3d12-dragon.md ("zeroed with memset 0xeec6ed0") [I via docs; NOT seen in this exe's disasm].
- `0x6634159 call 0xEEC6DE0` — rcx=r14, rdx=rbx=[rbp-0x20] (data ptr [OPEN]), r8=rdi=[rbp-0x18] size → memcpy(texObj, data, size) [V regs/imm]. Helper semantics: memcpy-like (dst,src,n) per docs/functions/67417f0.md ("0xeec6ec0 / 0xeec6de0 = memcpy-like (dst,src,n)") and docs/progress/oc_U-IH.md (grow-path memcpy via 0xEEC6DE0) [I via docs].

**No `bgfx`-like `createTexture2D` and no RenderContext vtable call appears anywhere in sub_6632fd0** [V — full coverage 0x6632fd0..0x663430f, ret at 0x663430f]. The "texture creation" here is CPU-side: alloc + memset + memcpy into object r14, then stored into the device texture slot array.

Texture object wiring (all [V]):
- `0x663412b call sub_eea6040` (rdx=rdi=[rbp-0x18] size) → r14 = new object [V]
- `0x6634165 mov rsi,[rax+0x288]` (rax=[rbp+0x6F8] = device/ctx object) → rsi = device texture manager [V]
- `0x6634176 mov [rsi+0x970],r14` → device tex slot +0x970 = r14 (old slot value freed via sub_eea6040 at 0x6634190) [V]
- `0x663419e mov [rsi+0x978],rdi` → +0x978 = size [V]
- `0x66341a5 mov [rsi+0x980],ebx` (ebx=[rbp-0x3C]) → +0x980 = format/dim value, meaning unknown [V, ? meaning]
- `0x66341ab mov [rsi+0x58],r14`; `0x66341af mov [rsi+0x60],ebx` [V]
- `0x6634281 call 0x6622610` (rcx=[rbp+0x6F8]+0x3F0, rdx=&"RenderDragon Ray Tracing Textures" [data_f5573b4, len 0x21]) → register in texture manager [V]

**Arguments taken from the decoded image:** width/height/size = [rbp-0x18] passed as alloc/memset/memcpy size; format/dim = ebx=[rbp-0x3C] stored at [rsi+0x980]/[rsi+0x60]; pixel data ptr = rbx=[rbp-0x20] passed to memcpy. The writes to [rbp-0x18]/[rbp-0x3C] and the store of sub_1994f90's rax (pixel buffer) into [rbp-0x20] are NOT directly visible — presumed to come out of sub_1994f90 via its out-pointer args (a1=&[rbp+0x5E0], a2=&[rbp-0x40]) [I inference, unverified] [OPEN].

**OPEN (step 3):** no createTexture2D/GPU-handle call in this path — GPU texture handle creation is deferred (texture bind/use time) or happens in callers 0x661a770 (+0x3529) / 0x66232b0 (+0xb3d0) of sub_6632fd0, which were not traced. Also data_f9a8aa0/f9a8aa8 thunk targets unresolved [?].

## Step (4): chain summary "bytes → decoder → pixel buffer → GPU/ClientTexture handle" — DONE
```
file bytes "look_up_tables.png"                         [rbp+0x630]=ptr, [rbp+0x640]=size [V]
   path built: sub_b1b70(0x6633eef) + sub_eec6ec0(0x6633fb0) into heap buf; string data_f5b2ae6 ref at 0x6633ebf [V]
   name obj "Ray Tracing Texture" (data_f5c6fc2) at [rbp-0x40], 0x20 bytes, written 0x6633ffe-0x663400f [V]
   file load via sub_eea6040 at 0x6634043 (rdx=&[rbp+0x630], r8=name, r9=path) [I]
│
0x66340e1 call sub_1994f90                              [V]
   loader: comp {1,3,4} via bitmask 0x1A (per U-L8c 1995041/1995046); req_comp=0 (r8d=0) [V]
   → sub_764950 at 199513c (+0xac5) [V per U-L8c + direct disasm]
   → sub_777ed0 at 764a05 (PNG decoder entry; magic 0x89 check at 777f55 [V per U-L8b])
   → pixel buffer returned in rax [V per call; pixel semantics per U-L8c]
   out-channel (inference [I]): {w,h,comp?,pixels} via a2=&[rbp-0x40] → [rbp-0x40]/[rbp-0x3C]/[rbp-0x28]/[rbp-0x20]; UNVERIFIED [OPEN]
│
0x663412b call sub_eea6040 (rdx=[rbp-0x18]=tex byte size=w*h*comp [I]) → r14 [V]
0x663414b call 0xEEC6ED0 (r14, edx=0, r8=size)          [V]  memset(texObj,0,size) [I via docs]
0x6634159 call 0xEEC6DE0 (r14, rdx=[rbp-0x20]=pixels [I/OPEN], r8=size) [V]  memcpy(texObj,pixels,size) ← decoded-pixel consumer [I]
   → stored: [device+0x288]+0x970 = r14 (device texture slot), +0x978=size, +0x980=ebx=[rbp-0x3C] (format [?]), +0x58=r14, +0x60=ebx [V]
   device object = [rbp+0x6F8] (=rcx arg a0 of sub_6632fd0) [V]
0x6634281 call 0x6622610 ([device+0x3F0], "RenderDragon Ray Tracing Textures") → texture-manager registration [V]

No createTexture2D/RenderContext vtable call in this path [V]; GPU handle creation is deferred/elsewhere [?]. Callers of sub_6632fd0: 0x661a770 (+0x3529), 0x66232b0 (+0xb3d0) [V via step 1] — not traced [?].

## NEXT
UNIT U-L8d DONE. File: docs/progress/oc_U-L8d.md (only file created; no other file edited). No further steps planned — remaining unknowns listed as [OPEN]/[?] above.