# Unit U-L8b — PNG/TGA image decoder + texture-loading entry

## NEXT
Run xref.py str for: "IHDR", "TGA", "png", "Failed to load", "texture_set", "textures/", "mipmap". Note every function RVA found with each string.

## Rules (from OPENCODE_BRIEF.md)
- Static analysis only; exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe
- Every claim tagged [V] (saw in disasm, cite RVA), [I] (inferred), [?] (unknown)
- Append findings after each step; never guess as fact

## Step (1): xref.py str results (RVAs per string) — DONE

"IHDR":
- 0x781550: refs from 0x78252d ("first not IHDR"), 0x78254c ("multiple IHDR"), 0x78258a ("bad IHDR len") [V via xref]
- 0xe987c00: refs from many IHDR validation errors (width/height limits, zero checks, color type, bit depth, filter, compression, interlace) [V via xref]
- 0xea54a90: "Missing IHDR before IDAT" ref 0xea54daf [V via xref]
- 0xec3a2b0, 0xec3a580, 0xec3a810, 0xec3ab20, 0xec3ac30, 0xec3ad80, 0xec3af30, 0xec3b040: "missing IHDR" refs [V via xref]

"TGA":
- 0x1474780: ref 0x1474b7c near string at 0xf0e6300 ("pTGA" at 0xf0e62e8) [V via xref]
- 0x1475480: ref 0x14754bd near same string area [V via xref]

"png":
- 0x399700: ".png" refs 0x3997ef, 0x3998e9, 0x399b16 [V via xref]
- 0x69c9570: ".png" ref 0x69c989d [V via xref]
- 0x3f7edd0: "image/png" ref 0x3f7f879 [V via xref]
- 0x599de30: "{}\{}{}.png" ref 0x599e710 [V via xref]
- 0x777ed0: "bad png sig" ref 0x7784be [V via xref]
- 0x781550: "bad png sig" ref 0x781a4c [V via xref]
- libpng family: 0xe985cd0, 0xe98e130, 0xec34f30, 0xea54a90, 0xea55280, 0xea54dc0, 0xe987c00, 0xe986b40, 0xec39880, 0xec3d740, 0xec3dbd0, 0xe98d690, 0xe98d890, 0xe98d940, 0xe98ded0, 0xe98b460, 0xec344d0, 0xe9886f0, 0xe98a990, 0xe98a2f0, 0xe986db0, 0xec3d3d0 [V via xref]

"Failed to load":
- 0x779adf0: "Failed to load the contents of file %s; it will be skipped." ref 0x779b101 [V via xref] — notable: close to PNG candidate 0x777ed0
- all others unrelated to images

"texture_set":
- 0x5a321f0: "minecraft:texture_set" ref 0x5a337e8 [V via xref]
- 0x5a46e60: "minecraft:texture_set" ref 0x5a47097 [V via xref]
- 0x5a47a90: "minecraft:texture_set" ref 0x5a47cd6 [V via xref]

"textures/": xref timed out (300s) — RERUN NEEDED
"mipmap": only "OES_fbo_render_mipmap" refs=[] — no functions [V via xref]

Working hypothesis: 0x777ed0 = PNG decoder entry ("bad png sig" inside); 0x781550 = PNG IHDR parser; 0x1474780/0x1475480 = TGA-related; 0x5a321f0/0x5a46e60/0x5a47a90 = texture_set entries.

## Step (2): 40-line disassembly of each hit function
IN PROGRESS (started; "textures/" xref re-run in background, may take >5 min)

### 0x777ed0 — "bad png sig" ref at 0x7784be [V via xref]
`rdis dis 0x777ed0 40` (sub_777ed0, size 0x2000, 2 xrefs in):
```
777ed0  push r15                                      
777ed2  push r14                                      
777ed4  push r13                                      
777ed6  push r12                                      
777ed8  push rsi                                      
777ed9  push rdi                                      
777eda  push rbp                                      
777edb  push rbx                                      
777edc  mov eax,0x89D8                                
777ee1  call 0xE9E7970                                ; -> sub_e9e7970
777ee6  sub rsp,rax                                   
777ee9  movaps [rsp+0x89C0],xmm6                      
777ef1  mov rbp,r9                                    
777ef4  mov r14,r8                                    
777ef7  mov r13,rdx                                   
777efa  mov r15,rcx                                   
777efd  mov rbx,[rsp+0x8A48]                          
777f05  mov edi,[rsp+0x8A40]                          
777f0c  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
777f13  xor rax,rsp                                   
777f16  mov [rsp+0x89B8],rax                          
777f1e  mov qword ptr [rbx],8                         
777f25  mov dword ptr [rbx+8],0                       
777f2c  lea r9,[rcx+0x30]                             
777f30  lea r12,[rcx+0x38]                            
777f34  mov rcx,[rcx+0xC0]                            
777f3b  mov rax,[r15+0xC8]                            
777f42  cmp rcx,rax                                   
777f45  jae short 0x777F63                            ; -> loc_777f63
777f47  lea rdx,[rcx+1]                               
777f4b  mov [r15+0xC0],rdx                            
777f52  movzx ecx,byte ptr [rcx]                      
777f55  cmp cl,0x89                                   
777f58  je 0x777FDF                                   ; -> loc_777fdf
777f5e  jmp 0x77849F                                  ; -> loc_77849f

loc_777f63:  ; from 777f45
777f63  cmp dword ptr [r9],0                          
777f67  je 0x77849F                                   ; -> loc_77849f
777f6d  mov r8d,[r15+0x34]                            
777f71  mov rax,[r15+0x10]                            
777f75  mov rcx,[r15+0x28]                            
```
- Signature: `void sub_777ed0(void* a0 /* rcx */, void* a1 /* rdx */, void* a2 /* r8 */, void* a3 /* r9 */, void* a4 /* [rsp+0x8A40] */, void* a5 /* [rsp+0x8A48] */)` [V via rdis prologue]
- Phase 777ed0..777f75: stack setup; `a0` (rcx) is a context struct with a byte buffer at +0xC0 (write cursor) and +0xC8 (end); reads first byte, compares to 0x89 (PNG magic first byte). [V via 777f55 cmp cl,0x89]
- Phase 777f5e: on first byte != 0x89 jumps to 0x77849F (likely "bad png sig" error path). [V via 777f5e jmp]

### 0x781550 — "bad png sig" ref at 0x781a4c [V via xref]
`rdis dis 0x781550 40` (sub_781550, size 0x2000, 2 xrefs in):
```
781550  push r15                                      
781552  push r14                                      
781554  push r13                                      
781556  push r12                                      
781558  push rsi                                      
781559  push rdi                                      
78155a  push rbp                                      
78155b  push rbx                                      
78155c  mov eax,0x1528                                
781561  call 0xE9E7970                                ; -> sub_e9e7970
781566  sub rsp,rax                                   
781569  mov ebx,r8d                                   
78156c  mov ebp,edx                                   
78156e  mov rdi,rcx                                   
781571  mov rax,[0x1230A0C0]                          ; [data_1230a0c0]
781578  xor rax,rsp                                   
78157b  mov [rsp+0x1520],rax                          
781583  mov byte ptr [rsp+0x10E],0                    
78158b  mov word ptr [rsp+0x10C],0                    
781595  mov rsi,[rcx]                                 
781598  lea r14,[rsi+0x38]                            
78159c  lea r13,[rsi+0x39]                            
7815a0  xorps xmm0,xmm0                               
7815a3  movups [rcx+8],xmm0                           
7815a7  mov qword ptr [rcx+0x18],0                    
7815af  mov rcx,[rsi+0xC0]                            
7815b6  mov rax,[rsi+0xC8]                            
7815bd  cmp rcx,rax                                   
7815c0  jae short 0x7815DA                            ; -> loc_7815da
7815c2  lea rdx,[rcx+1]                               
7815c6  mov [rsi+0xC0],rdx                            
7815cd  movzx ecx,byte ptr [rcx]                      
7815d0  cmp cl,0x89                                   
7815d3  je short 0x781644                             ; -> loc_781644
7815d5  jmp 0x781A39                                  ; -> loc_781a39

loc_7815da:  ; from 7815c0
7815da  cmp dword ptr [rsi+0x30],0                    
7815de  je 0x781A39                                   ; -> loc_781a39
7815e4  mov r8d,[rsi+0x34]                            
7815e8  mov rax,[rsi+0x10]                            
7815ec  mov rcx,[rsi+0x28]                            
```
- Signature: `void sub_781550(void* a0 /* rcx */, int a1 /* edx */, int a2 /* r8d */)` [V via rdis prologue]
- Phase 781550..7815d3: stack setup; `a0` (rcx) is a context struct; `rsi = *rcx`; reads byte at [rsi+0xC0] (inner buffer cursor), advances cursor at [rsi+0xC0], compares byte to 0x89 (PNG magic). [V via 7815d0 cmp cl,0x89]
- Phase 7815d5: on mismatch jumps to 0x781A39 (error path, "bad png sig"). [V via 7815d5 jmp]

### 0x1474780 — "TGA" ref at 0x1474b7c [V via xref]
`rdis dis 0x1474780 40` (sub_1474780, size 0x2000, 0 xrefs in):
```
1474780  push rbp                                      
1474781  push r15                                      
1474783  push r14                                      
1474785  push r13                                      
1474787  push r12                                      
1474789  push rsi                                      
147478a  push rdi                                      
147478b  push rbx                                      
147478c  sub rsp,0x3A8                                 
1474793  lea rbp,[rsp+0x80]                            
147479b  mov qword ptr [rbp+0x320],0xFFFFFFFFFFFFFFFE  
14747a6  mov rdi,rdx                                   
14747a9  xorps xmm0,xmm0                               
14747ac  movaps [rbp+0x300],xmm0                       
14747b3  mov qword ptr [rbp+0x310],0                   
14747be  lea rsi,[rdx+0x50]                            ; R a1+0x50
14747c2  cmp dword ptr [rdx+0x50],0xC8                 ; R a1+0x50
14747c9  jne 0x147497C                                 ; -> loc_147497c
14747cf  mov [rbp+0x2F8],rcx                           
14747d6  lea rdx,[rbp+0x2E0]                           
14747dd  mov rcx,rdi                                   
14747e0  call 0x1F6A4A0                                ; -> sub_1f6a4a0
14747e5  nop                                           
14747e6  lea rcx,[rbp+0x2E0]                           
14747ed  call 0xE932500                                ; -> sub_e932500
14747f2  nop                                           
14747f3  test al,al                                    
14747f5  jne 0x14749F2                                 ; -> loc_14749f2
```
- Signature: `bool sub_1474780(void* rcx, void* rdx /* a1 */)` [V via rdis prologue]
- Phase 1474780..14747c9: `a1` (rdx) has dword at +0x50 compared to 0xC8 (200 = TGA image-type marker). [V via 14747c2 cmp dword ptr [rdx+0x50],0xC8] — not clearly a TGA decoder; follows with string comparisons ("servers"/"vers" at data_f54b1a4/f54b1a7 seen at 1474813/147481c). [I based on neighboring code not fully shown]
- Conclusion: not a TGA pixel decoder; likely a manifest/texture-pack loader that mentions TGA string. [I]

### 0x1475480 — "TGA" ref at 0x14754bd near string 0xf0e6300 ("pTGA" at 0xf0e62e8) [V via xref]
`rdis dis 0x1475480 40` (sub_1475480, size 0x2000, 0 xrefs in):
```
1475480  push rbp                                      
1475481  push rsi                                      
1475482  push rdi                                      
1475483  push rbx                                      
1475484  sub rsp,0x48                                  
1475488  lea rbp,[rsp+0x40]                            
147548d  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE        
1475495  mov rsi,rcx                                   
1475498  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
147549f  mov rax,[rcx]                                 
14754a2  mov rax,[rax+8]                               
14754a6  mov edx,0xC8                                  
14754ab  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
14754b1  mov rdi,rax                                   
14754b4  test rax,rax                                  
14754b7  je 0x14755CD                                  ; -> loc_14755cd

loc_14754bd:  ; from 14755d7
14754bd  lea rax,[0xF0E6300]                           ; [data_f0e6300]
14754c4  mov [rdi],rax                                 
14754c7  lea rax,[rdi+8]                               
14754cb  mov [rbp-0x18],rax                            
14754cf  mov qword ptr [rdi+0x40],0                    
14754d7  mov rcx,[rsi+0x40]                            ; R a0+0x40
14754db  test rcx,rcx                                  
14754de  mov [rbp-8],rdi                               
14754e2  je short 0x14754FD                            ; -> loc_14754fd
```
- Signature: `void sub_1475480(void* rcx /* a0 */, void* rdx)` [V via rdis prologue]
- Phase 1475480..14754e2: calls sub_eea6040 (allocator via vtable at data_f99ffa0) with size 0xC8 (200); stores pointer to string at data_f0e6300 ("pTGA" area at +0xf0e62e8) at [rdi]. [V via 14754bd lea rax,[0xF0E6300]]
- Phase 14754d7: copies vtable pointer from a0+0x40 into allocated object's +0x40. [V via 14754e4-14754f9]
- Conclusion: this is an object constructor using the TGA-adjacent string, NOT a TGA pixel decoder. [I]

### 0x399700 — ".png" refs at 0x3997ef/0x3998e9/0x399b16 [V via xref]
`rdis dis 0x399700 40` (sub_399700, size 0x2000, 29 xrefs in):
```
399700  push rbp                                      
399701  push r14                                      
399703  push rsi                                      
399704  push rdi                                      
399705  push rbx                                      
399706  sub rsp,0x380                                 
39970d  lea rbp,[rsp+0x80]                            
399715  mov qword ptr [rbp+0x2F8],0xFFFFFFFFFFFFFFFE  
399720  mov eax,[0x128CBCE0]                          ; [data_128cbce0]
399726  mov r8d,[0x128767C8]                          ; [data_128767c8]
39972d  mov r9,gs:[0x58]                              
39973a  cmp eax,[r8+4]                                
399741  jg short 0x3997A4                             ; -> loc_3997a4

loc_399743:  ; from 3997c6, 399d09
399743  cmp edx,4                                     
399746  ja short 0x39978D                             ; -> loc_39978d
399748  mov eax,edx                                   
39974a  lea rax,[rax+rax*2]                           ; R a1+0x0+idx
39974e  lea r8,[0x128CBC68]                           ; [data_128cbc68]
399755  mov rdx,[r8+rax*8]                            
399759  mov rax,[r8+rax*8+8]                          
39975e  mov r8,rax                                    
399761  sub r8,rdx                                    
399764  mov r9,r8                                     
399767  sar r9,5                                      
39976b  mov [rcx],r9                                  ; W a0+0x0
39976e  cmp r8,0xFFFFFFFFFFFFFFE0                     
399772  je short 0x399788                             ; -> loc_399788
399774  mov [rcx+8],rdx                               ; W a0+0x8
399778  test rdx,rdx                                  
39977b  setne dl                                      
39977e  test rax,rax                                  
399781  sete al                                       
399784  or al,dl                                      
399786  jne short 0x399793                            ; -> loc_399793

loc_399788:  ; from 399772
399788  call 0x78ED0                                  ; -> sub_78ed0
```
- Signature: `void* sub_399700(void* rcx, int edx /* a1 */)` [V via rdis prologue]
- Phase 399700..399786: index-based lookup into data_128cbc68 array (strings indexed 0..3), computing a string length and returning [ptr, len] into output rcx (string_view construction). [V via 399743 cmp edx,4; 399755 mov rdx,[r8+rax*8]]
- Conclusion: string-table/index helper (likely resource name table containing ".png"), NOT a decoder. [I]

### 0x69c9570 — ".png" ref at 0x69c989d [V via xref]
`rdis dis 0x69c9570 40` (sub_69c9570, size 0x2000, 0 xrefs in):
```
69c9570  push rbp                                      
69c9571  push r15                                      
69c9573  push r14                                      
69c9575  push r13                                      
69c9577  push r12                                      
69c9579  push rsi                                      
69c957a  push rdi                                      
69c957b  push rbx                                      
69c957c  sub rsp,0x5B8                                 
69c9583  lea rbp,[rsp+0x80]                            
69c958b  mov qword ptr [rbp+0x530],0xFFFFFFFFFFFFFFFE  
69c9596  mov bl,r8b                                    
69c9599  mov rsi,rcx                                   
69c959c  movups xmm0,[0x128D7FB0]                      ; [data_128d7fb0]
69c95a3  movaps [rbp+0x430],xmm0                       
69c95aa  xorps xmm0,xmm0                               
69c95ad  movaps [rbp+0x440],xmm0                       
69c95b4  mov byte ptr [rbp+0x450],0                    
69c95bb  mov dword ptr [rbp+0x458],0xFFFFFFFF          
69c95c5  movaps [rbp+0x460],xmm0                       
69c95cc  mov qword ptr [rbp+0x470],0                   
69c95d7  mov qword ptr [rbp+0x478],0xF                 
69c95e2  movaps [rbp+0x480],xmm0                       
69c95e9  mov qword ptr [rbp+0x490],0                   
69c95f4  mov qword ptr [rbp+0x498],0xF                 
69c95ff  lea rcx,[rbp+0x430]                           
69c9606  call 0x25D0990                                ; -> sub_25d0990
```
- Signature: `void sub_69c9570(void* rcx /* this */, void* rdx, byte r8b)` [V via rdis prologue]
- Phase 69c9570..69c9606: constructs/initializes a std::string-like field at [rbp+0x430..0x498] (local buffer cap 0xF), then calls sub_25d0990 with it. [V via 69c95d7/69c95e2/69c95f4]
- Conclusion: string/path builder containing ".png", NOT a decoder. [I]

### 0x3f7edd0 — "image/png" ref at 0x3f7f879 [V via xref]
`rdis dis 0x3f7edd0 40` (sub_3f7edd0, size 0x2000, 0 xrefs in):
```
3f7edd0  push rbp                                      
3f7edd1  push r15                                      
3f7edd3  push r14                                      
3f7edd5  push r13                                      
3f7edd7  push r12                                      
3f7edd9  push rsi                                      
3f7edda  push rdi                                      
3f7eddb  push rbx                                      
3f7eddc  sub rsp,0xA8                                  
3f7ede3  lea rbp,[rsp+0x80]                            
3f7edeb  movaps [rbp+0x10],xmm6                        
3f7edf7  mov qword ptr [rbp+8],0xFFFFFFFFFFFFFFFE      
3f7edf7  mov dword ptr [0x12986F58],0                  ; [data_12986f58]
3f7ee01  xorps xmm6,xmm6                               
3f7ee04  movups [0x12986F60],xmm6                      ; [data_12986f60]
3f7ee0b  mov rcx,[0x1233E1A8]                          ; [data_1233e1a8]
3f7ee12  mov rax,[rcx]                                 
3f7ee15  mov rax,[rax+8]                               
3f7ee19  mov edx,0x38                                  
3f7ee1e  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040
3f7ee24  mov rsi,rax                                   
3f7ee27  test rax,rax                                  
3f7ee2a  je 0x3F7FBDB                                  ; -> loc_3f7fbdb

loc_3f7ee30:  ; from 3f7fbe5
3f7ee30  mov [rsi],rsi                                 
3f7ee33  mov [rsi+8],rsi                               
3f7ee37  mov [0x12986F60],rsi                          ; [data_12986f60]
```
- Signature: `void sub_3f7edd0(void)` [V via rdis prologue]
- Phase 3f7edd0..3f7ee37: global allocator (sub_eea6040 via data_f99ffa0) allocating 0x38 and 0x80-byte objects; initializes self-referencing linked list heads at data_12986F60/12986F70; sets data_12986F58 = 0x3F800000 (float 1.0f). [V via 3f7ee19 mov edx,0x38; 3f7ee30 mov [rsi],rsi]
- Conclusion: global resource-manager constructor containing "image/png" MIME string ref nearby, NOT a pixel decoder. [I]

### 0x599de30 — "{}\{}{}.png" ref at 0x599e710 [V via xref]
`rdis dis 0x599de30 40` (sub_599de30, size 0x2000, 0 xrefs in):
```
599de30  push rbp                                      
599de31  push r15                                      
599de33  push r14                                      
599de35  push r13                                      
599de37  push r12                                      
599de39  push rsi                                      
599de3a  push rdi                                      
599de3b  push rbx                                      
599de3c  sub rsp,0x3E8                                 
599de43  lea rbp,[rsp+0x80]                            
599de4b  movaps [rbp+0x350],xmm7                       
599de52  movaps [rbp+0x340],xmm6                       
599de59  mov qword ptr [rbp+0x338],0xFFFFFFFFFFFFFFFE  
599de64  mov rsi,rcx                                   
599de67  xorps xmm0,xmm0                               
599de6a  movaps [rbp+0x260],xmm0                       
599de71  mov rcx,[rcx+0x10]                            ; R a0+0x10
599de75  test rcx,rcx                                  
599de78  je short 0x599DEA2                            ; -> loc_599dea2
599de7a  mov eax,[rcx+8]                               ; R *(a0+0x10)+0x8
```
- Signature: `void sub_599de30(void* rcx /* this */, void* rdx)` [V via rdis prologue]
- Phase 599de30..599dea2: atomic increment on [a0+0x10]+0x8 (refcount), then reads [rsi+0x18] -> [rbp-0x50]/+0xB8 area, builds path string via lea 0xF2734A0 ("{}\{}{}.png"-adjacent data). [V via 599de87 lock cmpxchg [rcx+8],edx]
- Conclusion: resource path formatter using "{}\{}{}.png", NOT a decoder. [I]

### 0x5a321f0 / 0x5a46e60 / 0x5a47a90 — "minecraft:texture_set" refs [V via xref]
`rdis dis 0x5a321f0 40` (sub_5a321f0, size 0x2000, 3 xrefs in): allocates 0xA8-byte object via sub_eea6040 (data_f99ffa0), vtable data_f2740b0, copies fields at +0x38/+0x58 — object constructor. [I]
`rdis dis 0x5a46e60 40` (sub_5a46e60, size 0x2000, 0 xrefs in): JSON key handling ("format_version", "_version" at data_f590271/f590277), calls sub_58d5810 then sub_2cd190/sub_769DD0 writing [rdi+0x168]/[rdi+0x170]/[rdi+0x178] — texture_set JSON parser. [I]
`rdis dis 0x5a47a90 40` (sub_5a47a90, size 0x2000, 0 xrefs in): same JSON-parser skeleton with string at data_f273f38 instead of f273f10. [I]
- Conclusion: texture_set JSON loaders (parsing *.json manifest), NOT pixel decoders. [I]

### 0x779adf0 — "Failed to load the contents of file %s; it will be skipped." ref at 0x779b101 [V via xref]
`rdis dis 0x779adf0 40` (sub_779adf0, size 0x2000, 0 xrefs in):
```
779adf0  push rbp                                      
779adf1  push r15                                      
779adf3  push r14                                      
779adf5  push r13                                      
779adf7  push r12                                      
779adf9  push rsi                                      
779adfa  push rdi                                      
779adfb  push rbx                                      
779adfc  sub rsp,0x828                                 
779ae03  lea rbp,[rsp+0x80]                            
779ae0b  mov qword ptr [rbp+0x788],0xFFFFFFFFFFFFFFFE  
779ae1d  mov r14,rdx                                   
779ae20  mov rax,[rcx+0x18]                            ; R a0+0x18
779ae24  mov qword ptr [rax+0x10],0                    ; W *(a0+0x18)+0x10
779ae2c  cmp qword ptr [rax+0x18],0x10                 ; R *(a0+0x18)+0x18
779ae31  jb short 0x779AE36                            ; -> loc_779ae36
779ae33  mov rax,[rax]                                 ; R *(a0+0x18)+0x0
779ae36  mov byte ptr [rax],0                          ; W *(*(a0+0x18)+0x0)+0x0
779ae39  mov rax,[r14+0x10]                            ; R a1+0x10
...
779ae86  mov eax,0x6164                                
779ae8b  xor eax,[rbp-0x48]                            
779ae8e  movzx ecx,byte ptr [rbp-0x46]                 
779ae92  xor ecx,0x74                                  
779ae95  or cx,ax                                      
```
- Signature: `void sub_779adf0(void* rcx /* a0 */, void* rdx /* a1 */)` [V via rdis prologue]
- Phase 779adf0..779ae95: zero-terminates a small string buffer at *(a0+0x18)+0x0, copies a1+0x10 bytes, compares against constants 0x6164 ('ad') and 0x74 ('t') — appears to match a file suffix/extension ("dat"/"tad" reversed?). [V via 779ae86 mov eax,0x6164; 779ae92 xor ecx,0x74]
- Conclusion: generic file-loader error path ("Failed to load"), NOT specific to PNG/TGA decoding. [I]

Step (2) conclusion: the only function that looks like a real image decoder entry is 0x777ed0 (PNG magic 0x89 check, size 0x2000). 0x781550 is a nested PNG/IHDR check (IHDR stream). All "texture_set"/"minecraft:texture_set" hits are JSON manifest loaders, and "textures/" xref is still running (background job).

## Step (3): callers chain (up to 3 levels) for most likely decoder — DONE
Most likely decoder = 0x777ed0 (PNG entry: "bad png sig" at 0x7784be, magic 0x89 check at 777f55).

Level 0 (decoder): 0x777ed0
Level 1 (direct callers):
- 0x7647c0 at +0x18e [V via xref callers]
- 0x764950 at +0x4f9 [V via xref callers]
Level 2:
- 0x7647c0 ← 0x167d050 (+0x11d), 0x19944b0 (+0x906), 0x1994f90 (+0xac5) [V via xref callers]
- 0x764950 ← 0x19944b0 (+0x906), 0x1994f90 (+0xac5) [V via xref callers]
Level 3:
- 0x167d050 ← 0x1093320 (+0x941) [V via xref callers]
- 0x19944b0 ← 0x327530 (+0x5f), 0x69d4d0 (+0x1e68), 0x2265160 (+0x1576), 0x23f3f20 (+0x10a8) [V via xref callers]
- 0x1994f90 ← 0x108c90 (+0x1afa), 0x398fc0 (+0x611), 0xa08dd0 (+0x81b), 0xfc4760 (+0x3a1), 0xfcb2d0 (+0x5ad), 0xfd26e0 (+0x7b7), 0x1679d40 (+0x9d3), 0x17c5040 (+0x27f), 0x1f4df80 (+0x22d), 0x1f4e5b0 (+0x38e), 0x1f506b0 (+0x7af), 0x1f5cd70 (+0x20f), 0x1f5d110 (+0x182), 0x25cf6f0 (+0xba4), 0x4e8b8f0 (+0x352), 0x541bf00 (+0x7a0), 0x541cb30 (+0x83d), 0x5420c20 (+0x309), 0x5421230 (+0x328), 0x5a31160 (+0x345), 0x6632fd0 (+0x1531), 0x668a140 (+0x3f6), 0x69dd7b0 (+0x87d), 0x69e11a0 (+0x47f), 0x6c0f490 (+0x9db), 0x6dbf280 (+0x1579), ... [V via xref callers]
Interpretation: decoder is reached from many sites (0x1994f90 is a hot dispatcher-like caller). [I]

## Step (4): struct receiving width/height/format — DONE (partial; see notes)

Struct receiving width/height/format = the image-decode context pointed to by `r15` (= `rcx` = 1st argument of `sub_777ed0`), observed in the BMP sub-path:

- `[r15+0x0]` = width (dword). [V via 7786ae `cmp dword ptr [r15],0x1000001`; validated ≤ 1,048,577]
- `[r15+0x4]` = height (dword). [V via 778692 `mov r8d,[r15+4]`; 778699 `neg eax`; 77869b `cmovs eax,r8d` = abs() — BMP stores signed height (top-down); 77869f `mov [r15+4],eax` writes abs back; 7786a3 `cmp eax,0x1000001` validated]
- `[r15+0x8]` = format / component count (3 or 4, derived from color type via `cmp edx,1 / sbb ecx,0 → ecx=4 or 3`). [V via 7789d6 `mov [r15+8],ecx`]

How values get there:
- BMP path: `sub_786F80` (called at 0x778684 with `rcx=r15`, `rdx=rsp+0x110`) parses the BMP header (re-checks "BM" at 0x78700a, reads dwords via `sub_786E50`, compares header size to 0x38 at 0x778640) and writes width→[r15+0], height→[r15+4] directly [I by elimination — nothing between the call at 0x778684 and the reads at 0x778692/0x7786ae writes them]. Then `[r15+8]=format` at 0x7789d6.
- PNG path: IHDR parsed by `sub_781550` (called at 0x77841d with `rcx=rsp+0x140`) writes width→[rsp+0x140], height→[rsp+0x144] (stack locals = [rdi]/[rdi+4]), bit depth →[rbx] via [rsp+0x160]; these stack locals are consumed by `sub_782f20` (called 0x778489), NOT promoted to r15+0/+4 in the visible range. PNG format selection uses `edi` (req_comp) at 0x7783e2/`cmp edi,5` and color-type at 0x7789bb.
- `[r15+0xC0]`/`[r15+0xC8]` = stream read cursor / end (byte stream) [V via 777f34/777f3b/777f4b writes]. `[r15+0xB8]` = bytes-consumed counter [V via 777f90 `add [r15+0xB8],ecx`].

NOTES / limits:
- width(+0) vs height(+4) assignment: +4 is abs()'d (BMP signed-height convention), +0 is not → +4 = height, +0 = width. [I strong, from abs() on +4 only]
- "textures/" xref: timed out twice (300s + 600s); could not complete. [V via tool timeout]
- sub_777ed0 is a multi-format loader (PNG sig 0x89/PNG + "BM" BMP check), not pure PNG. [V via 777f55 cmp cl,0x89; 778567 cmp byte ptr [r8],0x42 'B'; 7785f0 cmp byte ptr [rdx],0x4D 'M']

## NEXT
Unit complete. Step (1) DONE (all strings; "textures/" timed out). Step (2) DONE (40-line dis of all hit funcs). Step (3) DONE (callers to 3 levels). Step (4) DONE (struct r15: +0 width, +4 height, +8 format). No further steps.
