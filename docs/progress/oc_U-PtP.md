## NEXT
DONE


## U-PtP - effect particle producer 0x5b8c2b0..0x5b8d178 (831 instructions, one listing)

Signature guess [I]: `EffectParticleProducer::spawn(ParticleEffectContext* ctx /*rcx*/, ParticleProducerOutput* out /*rdx*/, Registry* reg /*r8*/, void* arg4 /*r9*/, int elemIdx /*stack+0x28 -> r14 = idx<<6*/, void* arg6 /*stack+0x30 -> rbx*/)`. Output object at r13/rdx gets a grown vector of 0x38-byte records. All statements below are [V] at the cited RVAs unless tagged [I]/[?].

## Phases (instruction-complete: consecutive ranges tile 0x5b8c2b0..0x5b8d177)

### P1 0x5b8c2b0..0x5b8c35d (40 instructions)
Prologue: save nonvolatiles, `sub rsp,0x4A8`, rbp=rsp+0x80, save xmm6 and security cookie (`0x5b8c2d2  mov qword ptr [rbp+0x408],0xFFFFFFFFFFFFFFFE`); load args r15=rcx, r13=rdx, rsi=r9, rbx=[rbp+0x498], r14=[rbp+0x490]<<6, save [r9+8] to [rbp+0x3F0]. Then loads per-element ptr `0x5b8c303  mov rdx,[rcx+r14+0xA20]` and `0x5b8c30b  mov rcx,[r8+0x100]`; if [rcx+8] nonzero refcount it and copy {rax,[rcx+8]} into [r13], zero [r13+0x10..0x20], else fall to the zero-init branch at 0x5B8C3AB; releases go through lock dec + vtable calls at [0xF99FFA0].
Key field sites:
  0x5b8c2f8  mov rax,[r9+8]
  0x5b8c303  mov rdx,[rcx+r14+0xA20]
  0x5b8c30b  mov rcx,[r8+0x100]
  0x5b8c326  lock inc dword ptr [rax+8]
  0x5b8c334  movups [r13],xmm0
  0x5b8c348  mov [r13+8],r12
  0x5b8c350  movups [r13+0x10],xmm0
  0x5b8c355  mov qword ptr [r13+0x20],0

### P2 0x5b8c363..0x5b8c418 (40 instructions)
Tail of the release path (lock dec [r12+0xC], vtable dtor calls) then the other init branch at 0x5b8c3ba: `[r13]=rax`, movups-zero of [r13+8] and [r13+0x18], edi=0; store arg6 `0x5b8c3cd  mov [r13+0x28],rbx`; size check ([r13+0x20]-rdi)/8 * 0x6DB6DB6DB6DB6DB7 (= count of 0x38-byte elements) vs rdx, r13 saved to [rbp+0x400], r15 to [rbp+0x3E0]; if rdx >= 0x492492492492493 bail to 0x5B8D158 (overflow stub); else rbx=[r13+0x18], rdx saved [rbp+0x3F8], call 0x5BBB580 (vector grow/reserve, rcx=r13) returning new buffer r12.
Key field sites:
  0x5b8c37f  lock dec dword ptr [r12+0xC]
  0x5b8c3ba  mov [r13],rax
  0x5b8c3c1  movups [r13+8],xmm0
  0x5b8c3c6  movups [r13+0x18],xmm0
  0x5b8c3cd  mov [r13+0x28],rbx
  0x5b8c3d1  mov rax,[r13+0x20]
  0x5b8c414  mov rbx,[r13+0x18]
  0x5b8c422  call 0x5BBB580
### P3 0x5b8c41b..0x5b8c4c0 (40 instructions)
Move loop from old buffer rdi to new buffer r12: for each 0x38-byte element, copy members at +0, +8, +0x10, +0x18, +0x20, +0x28 as qwords and +0x30 as a byte, zeroing each moved source member first with movups (`0x5b8c440  movups [r12+rax],xmm0`, `0x5b8c445  mov rcx,[rdi+rax]` ... `0x5b8c499  movzx ecx,byte ptr [rdi+rax+0x30]`); loop until rdi+rax+0x38 == rbx. Then (rdi nonzero) start the old-element release walk: r15=rdi, `0x5b8c4dd  mov r13,[r15+0x28]` (member 5) and release it: `0x5b8c4e6  lock dec dword ptr [r13+8]`, then `0x5b8c4fd  lock dec dword ptr [r13+0xC]`, each zero path calling vtable+0 / vtable+8 through [0xF99FFA0].
Key field sites:
  0x5b8c440  movups [r12+rax],xmm0
  0x5b8c445  mov rcx,[rdi+rax]
  0x5b8c44d  mov rcx,[rdi+rax+8]
  0x5b8c499  movzx ecx,byte ptr [rdi+rax+0x30]
  0x5b8c4dd  mov r13,[r15+0x28]
  0x5b8c4e6  lock dec dword ptr [r13+8]
  0x5b8c4fd  lock dec dword ptr [r13+0xC]

### P4 0x5b8c4c2..0x5b8c56d (40 instructions)
Rest of the per-element release walk over the old buffer: `0x5b8c4d0  add r15,0x38` until r15==rbx; for each element release member [r15+0x28], then `0x5b8c520  mov r13,[r15+0x18]` (member 3) with `0x5b8c529  lock dec dword ptr [r13+8]` / `0x5b8c540  lock dec dword ptr [r13+0xC]`, then `0x5b8c560  mov r13,[r15+8]` (member 1) with the same double lock dec pattern (`0x5b8c56d  lock dec dword ptr [r13+8]`); every zero-count path calls virtual dtor slot vtable+0 or vtable+8 via [0xF99FFA0] with rcx=object.
Key field sites:
  0x5b8c4d0  add r15,0x38
  0x5b8c520  mov r13,[r15+0x18]
  0x5b8c529  lock dec dword ptr [r13+8]
  0x5b8c540  lock dec dword ptr [r13+0xC]
  0x5b8c560  mov r13,[r15+8]
  0x5b8c56d  lock dec dword ptr [r13+8]

### P5 0x5b8c572..0x5b8c630 (40 instructions)
Finish the last member release, then commit the grown vector: `0x5b8c5b3  mov [r13+0x10],r12` (begin), `0x5b8c5ba  mov [r13+0x18],rbx` (end), `0x5b8c5c9  mov [r13+0x20],rax` (capacity end = rdx*0x38+begin); restore r12=[rbp+0x3E8], r15=[rbp+0x3E0]. Then start iterating a std::list: `0x5b8c5e5  mov r15,[rax+8]` with rax=r15+r14+0xA10 (list head at ctx+idx*64+0xA18, saved root [rbp+0x388]); `0x5b8c610  mov r15,[r15]` walks next; exit to epilogue 0x5B8D13A when next == head sentinel [rbp+0x3E0]; per node `0x5b8c620  mov rax,[r15+0x18]` / `0x5b8c624  mov rdi,[r15+0x20]` (node vector begin/end), r9 = min((end-begin)>>1, 0xFFFF).
Key field sites:
  0x5b8c5ac  mov r13,[rbp+0x400]
  0x5b8c5b3  mov [r13+0x10],r12
  0x5b8c5ba  mov [r13+0x18],rbx
  0x5b8c5c9  mov [r13+0x20],rax
  0x5b8c5e5  mov r15,[rax+8]
  0x5b8c610  mov r15,[r15]
  0x5b8c620  mov rax,[r15+0x18]
  0x5b8c624  mov rdi,[r15+0x20]
### P6 0x5b8c633..0x5b8c6d8 (40 instructions)
Clamp element count r9 to 0xFFFF (cmovae, 0x5b8c63d..0x5b8c642), `mov byte ptr [rsp+0x20],0`, call 0x54175A0(rcx=[rbp+0x3F0], rdx=rsi, r8b=1, r9=count, stack byte 0). Then rdi>>=3 and a bounded loop (ebx up to 0x3FFE) that walks the node vector: `0x5b8c682  mov rax,[rax+0x20]` (vtable slot) and virtual call via [0xF99FFA0] with rdx=rsi on every element. Finally zero xmm6 into [rbp+0x3C0] and build a shared_ptr from r12+0x108/+0x110 (strong-ref: lock inc [rax+8]) stored to [rbp+0x3C0]/[rbp+0x3C8], plus `0x5b8c6d8  mov rcx,[r12+0x118]` saved to [rbp+0x3D0].
Key field sites:
  0x5b8c646  mov byte ptr [rsp+0x20],0
  0x5b8c655  call 0x54175A0
  0x5b8c682  mov rax,[rax+0x20]
  0x5b8c6a1  mov rax,[r12+0x110]
  0x5b8c6c2  mov rax,[r12+0x108]
  0x5b8c6d8  mov rcx,[r12+0x118]

### P7 0x5b8c6e0..0x5b8c7ac (40 instructions)
Guard: if [rbp+0x3C0] null or `0x5b8c6f0  cmp byte ptr [rax],0` equal -> fallback branch 0x5B8C850; else `0x5b8c6f9  mov rax,[rcx]` / [rax+8] vtable+8 virtual call, test al false -> 0x5B8C850; then `0x5b8c716  cmp byte ptr [rax+0x255],0` (rax=[rbp+0x3F0]) nonzero -> jump 0x5B8CBC9 skipping the spawn. Build string arg {0xF5AFB66, len 0x19} at [rbp+0x370]/[rbp+0x378], word [rsp+0x20]=0, `0x5b8c762  call 0x5418DE0` (rcx=[rbp+0x3F0], rdx=rbp-0x38, r8d=2, r9=rbp+0x370), then `0x5b8c76c  call 0x4DEF080` on rbp-0x38, test al false -> 0x5B8D060. Zero-init temps: struct at rbp+0x288 (`0x5b8c781  movups [rax],xmm6`, byte [rax+0x10]=0, `0x5b8c79d  movups [rax+0x28],xmm6`, movups [rax+0x18]), movaps [rbp+0x270]/[rbp+0x260], byte [rbp+0x280]=0; then vtable+0x28 virtual call on node element ([r15+0x18] -> [rax] -> [rcx] -> [rax+0x28]).
Key field sites:
  0x5b8c6f0  cmp byte ptr [rax],0
  0x5b8c6f9  mov rax,[rcx]
  0x5b8c700  call qword ptr [0xF99FFA0]
  0x5b8c716  cmp byte ptr [rax+0x255],0
  0x5b8c731  mov [rbp+0x370],rax
  0x5b8c762  call 0x5418DE0
  0x5b8c76c  call 0x4DEF080
  0x5b8c781  movups [rax],xmm6
  0x5b8c79d  movups [rax+0x28],xmm6

### P8 0x5b8c7af..0x5b8c870 (40 instructions)
rdi = result of the vcall (`0x5b8c7c1  mov rdi,[rax]`), null replaced by empty-string constant 0x129C1210 (`0x5b8c7ce  cmove rdi,rax`); `0x5b8c7d2  mov rbx,[rdi]` -> if null jump 0x5B8CEFD. Lazy-init check: [0x128D8FC8] vs TLS index [0x128767C8] via gs:[0x58] slot, expired -> init path 0x5B8D104; else rwlock read-lock `0x5b8c803  lock inc word ptr [rbx+0x10]`, `0x5b8c808  movzx eax,byte ptr [rbx+0x12]` bit0 test -> 0x5B8CEFD. Then copy a shared_ptr member of rdi: [rdi] -> word [rax+0x10] (0x5b8c823), [rdi+8] -> lock inc and jmp 0x5B8CDC3 (null path 0x5B8CDC1). Fallback branch at 0x5b8c850: string {0xF5AFBFF, len 0xD} into [rbp+0x260]/[rbp+0x268], word [rsp+0x20]=0, rcx=[rbp+0x3F0] for the call in P9.
Key field sites:
  0x5b8c7c1  mov rdi,[rax]
  0x5b8c7ce  cmove rdi,rax
  0x5b8c7d2  mov rbx,[rdi]
  0x5b8c803  lock inc word ptr [rbx+0x10]
  0x5b8c808  movzx eax,byte ptr [rbx+0x12]
  0x5b8c823  movzx eax,word ptr [rax+0x10]
  0x5b8c834  lock inc dword ptr [rax+8]
  0x5b8c857  mov [rbp+0x260],rax
  0x5b8c85e  mov qword ptr [rbp+0x268],0xD
### P9 0x5b8c877..0x5b8c92b (40 instructions)
`0x5b8c885  call 0x5418DE0` (rcx=[rbp+0x3F0], rdx=rbp-0x38, r8d=0, r9=&{0xF5AFBFF,0xD}); then global factory rcx=[0x1233E1A8], `0x5b8c89e  call qword ptr [0xF99FFA0]` (vtable+8) with edx=0x270 allocating a new object r14; null -> 0x5B8D0F4 (call 0x9BC830, ecx=0x270, jmp back 0x5B8C8B1). Init: `0x5b8c8bb  mov [r14+8],rax` = 0x100000001 (both refcounts 1), `0x5b8c8c6  mov [r14],rax` = 0xF249870 vtable, save to [rbp+0x3F8]; r14+=0x10, `0x5b8c8db  call 0x4DE7FB0` (rcx=r14, rdx=rbp-0x38) building the sub-object; store the temp pair `0x5b8c8e1  mov [rbp+0x2C0],r14` / `0x5b8c8ef  mov [rbp+0x2C8],rax`; repeat element vtable+0x28 vcall (0x5b8c904); zero `0x5b8c912  movups [rcx+8],xmm6` (rcx=rbp+0x2C8); `0x5b8c91f  lock inc dword ptr [rcx+8]` grabbing [rax+8].
Key field sites:
  0x5b8c885  call 0x5418DE0
  0x5b8c89e  call qword ptr [0xF99FFA0]
  0x5b8c8bb  mov [r14+8],rax
  0x5b8c8c6  mov [r14],rax
  0x5b8c8db  call 0x4DE7FB0
  0x5b8c8e1  mov [rbp+0x2C0],r14
  0x5b8c8ef  mov [rbp+0x2C8],rax
  0x5b8c912  movups [rcx+8],xmm6
  0x5b8c91f  lock inc dword ptr [rcx+8]

### P10 0x5b8c929..0x5b8ca0c (40 instructions)
r13=[rbp+0x400] (output vector); build second shared_ptr from the vcall result: `0x5b8c932  mov rdx,[rax]` -> `0x5b8c935  mov [rbp+0x2D0],rdx` / `0x5b8c93c  mov [rbp+0x2D8],rcx`; `0x5b8c94a  movups [rcx+0x18],xmm6` (rcx=rbp+0x2C8 -> rbp+0x2E0); third member [rax+0x18] refcounted -> rcx, `0x5b8c963  mov r12,[rax+0x10]`, `0x5b8c967  mov byte ptr [rbp+0x2F0],0`. If [r13+0x18] != [r13+0x20] (space left): append a 0x38-byte record at rbx from the temps ([rbp+0x2C0], [rbp+0x2C8], [rbp+0x2D0], [rbp+0x2D8], r12, rcx, byte 0 at +0x30), zero each temp after the copy (`0x5b8c98d  movaps [rbp+0x2C0],xmm6`), `0x5b8c9c5  add rbx,0x38`, new end to [r13+0x18], `0x5b8c9cd  jmp 0x5B8CB47`; else grow path: `0x5b8c9d2  mov rdi,[r13+0x10]`, new capacity = count+1 clamped to [count+1, 0x492492492492492] (count = (end-begin)/7 via 0x6DB6DB6DB6DB6DB7 magic), saved to [rbp+0x3F8], `0x5b8ca2d  call 0x5BBB580` -> new buffer r13.
Key field sites:
  0x5b8c932  mov rdx,[rax]
  0x5b8c935  mov [rbp+0x2D0],rdx
  0x5b8c93c  mov [rbp+0x2D8],rcx
  0x5b8c94a  movups [rcx+0x18],xmm6
  0x5b8c963  mov r12,[rax+0x10]
  0x5b8c967  mov byte ptr [rbp+0x2F0],0
  0x5b8c96e  mov rbx,[r13+0x18]
  0x5b8c972  cmp rbx,[r13+0x20]
  0x5b8c97f  mov [rbx],rax
  0x5b8c98d  movaps [rbp+0x2C0],xmm6
  0x5b8c9c5  add rbx,0x38
  0x5b8c9cd  jmp 0x5B8CB47
  0x5b8c9d2  mov rdi,[r13+0x10]
  0x5b8ca2d  call 0x5BBB580

### P11 0x5b8ca0f..0x5b8caac (40 instructions)
Store the appended record into the new buffer at rax=(old_end-old_begin): `0x5b8ca42  mov [r13+rax],rcx` ([rbp+0x2C0]), `0x5b8ca4e  mov [r13+rax+8],rcx` ([rbp+0x2C8]), `0x5b8ca61  mov [r13+rax+0x10],rcx` ([rbp+0x2D0]), `0x5b8ca6d  mov [r13+rax+0x18],rcx` ([rbp+0x2D8]), `0x5b8ca7d  mov [r13+rax+0x20],r12`, `0x5b8ca89  mov [r13+rax+0x28],rdx` ([rbp+0x380]), `0x5b8ca92  mov byte ptr [r13+rax+0x30],0`; every temp cleared after copy (movaps/movups at rbp+0x2C0/2D0/2E0). Then move the old elements rdi -> r13 with the same 0x38-stride pattern as P3 (zeroing sources), loop until rdi+rax+0x38 == rbx.
Key field sites:
  0x5b8ca42  mov [r13+rax],rcx
  0x5b8ca4e  mov [r13+rax+8],rcx
  0x5b8ca61  mov [r13+rax+0x10],rcx
  0x5b8ca6d  mov [r13+rax+0x18],rcx
  0x5b8ca7d  mov [r13+rax+0x20],r12
  0x5b8ca89  mov [r13+rax+0x28],rdx
  0x5b8ca92  mov byte ptr [r13+rax+0x30],0
### P12 0x5b8cab0..0x5b8cb58 (40 instructions)
Old-element move loop into the new buffer r13 (0x38-stride copy + source zeroing, as P3); if rdi nonzero jump `0x5b8cb19  jne 0x5B8CC7D` (old-element release walk). Commit the grown vector: rcx=[rbp+0x400], `0x5b8cb26  mov [rcx+0x10],r13` (begin), `0x5b8cb35  mov [rcx+0x18],rax` (end = [rbp+0x3F8]*0x38+r13), `0x5b8cb43  mov [rcx+0x20],rax` (cap = r14*0x38+r13), r13=rcx. Then release temp shared_ptr `0x5b8cb47  mov r14,[rbp+0x2D8]`: `0x5b8cb53  lock dec dword ptr [r14+8]`, `0x5b8cb69  lock dec dword ptr [r14+0xC]`, zero paths call vtable+0 / vtable+8 dtors.
Key field sites:
  0x5b8cb19  jne 0x5B8CC7D
  0x5b8cb26  mov [rcx+0x10],r13
  0x5b8cb35  mov [rcx+0x18],rax
  0x5b8cb43  mov [rcx+0x20],rax
  0x5b8cb47  mov r14,[rbp+0x2D8]
  0x5b8cb53  lock dec dword ptr [r14+8]
  0x5b8cb69  lock dec dword ptr [r14+0xC]

### P13 0x5b8cb5a..0x5b8cbf6 (40 instructions)
Vtable dtor calls for the released temp; then release `0x5b8cb80  mov r14,[rbp+0x2C8]` (`0x5b8cb93  lock dec dword ptr [r14+8]`, `0x5b8cba9  lock dec dword ptr [r14+0xC]`, dtors), restore r12=[rbp+0x3E8]; destroy the temp buffer rbp-0x38 (`0x5b8cbc0  lea rcx,[rbp-0x38]`, `0x5b8cbc4  call 0x4DEA990`). Common tail 0x5b8cbc9: `0x5b8cbc9  mov r14,[rbp+0x3C8]`, `0x5b8cbd0  movaps [rbp+0x3C0],xmm6`, release that shared_ptr (`0x5b8cbe0  lock dec dword ptr [r14+8]`), reload r14, `0x5b8cc14  mov qword ptr [rbp+0x3D0],0`, release again, then back to the list loop at 0x5B8C610.
Key field sites:
  0x5b8cb80  mov r14,[rbp+0x2C8]
  0x5b8cb93  lock dec dword ptr [r14+8]
  0x5b8cba9  lock dec dword ptr [r14+0xC]
  0x5b8cbc0  lea rcx,[rbp-0x38]
  0x5b8cbc4  call 0x4DEA990
  0x5b8cbc9  mov r14,[rbp+0x3C8]
  0x5b8cbd0  movaps [rbp+0x3C0],xmm6
  0x5b8cbe0  lock dec dword ptr [r14+8]
  0x5b8cc0d  mov r14,[rbp+0x3C8]
  0x5b8cc14  mov qword ptr [rbp+0x3D0],0

### P14 0x5b8cbfb..0x5b8cc92 (40 instructions)
Finish the [rbp+0x3C8] release (lock dec [r14+8]/[r14+0xC] + dtor calls, `0x5b8cc2d  jne 0x5B8C610`, `0x5b8cc5d  jmp 0x5B8C610` -> next list node). Then the old-element release walk used by the grow path: `0x5b8cc70  add rdi,0x38` until rdi==rbx; per element release `0x5b8cc7d  mov r12,[rdi+0x28]`, `0x5b8ccc0  mov r12,[rdi+0x18]`, [rdi+8], each with `0x5b8cc86  lock dec dword ptr [r12+8]` / `0x5b8cc9e  lock dec dword ptr [r12+0xC]` and virtual dtor calls via [0xF99FFA0].
Key field sites:
  0x5b8cc2d  jne 0x5B8C610
  0x5b8cc5d  jmp 0x5B8C610
  0x5b8cc70  add rdi,0x38
  0x5b8cc7d  mov r12,[rdi+0x28]
  0x5b8cc86  lock dec dword ptr [r12+8]
  0x5b8cc9e  lock dec dword ptr [r12+0xC]
  0x5b8ccc0  mov r12,[rdi+0x18]
  0x5b8ccc9  lock dec dword ptr [r12+8]
### P15 0x5b8cc98..0x5b8cd65 (40 instructions)
Rest of the old-element release walk: `0x5b8cd00  mov r12,[rdi+8]` (member 1) with `0x5b8cd0d  lock dec dword ptr [r12+8]` / [r12+0xC] + dtor calls, `jmp 0x5B8CC70` to advance. Then grow commit at 0x5b8cd4b: `0x5b8cd4b  mov r12,[rbp+0x2E8]` (saved refcounted temp), `0x5b8cd52  mov rcx,[rbp+0x400]`, `0x5b8cd59  mov [rcx+0x10],r13`, `0x5b8cd68  mov [rcx+0x18],rax` (end=[rbp+0x3F8]*0x38+r13), `0x5b8cd76  mov [rcx+0x20],rax` (cap=r14*0x38+r13), r13=rcx.
Key field sites:
  0x5b8cd00  mov r12,[rdi+8]
  0x5b8cd0d  lock dec dword ptr [r12+8]
  0x5b8cd4b  mov r12,[rbp+0x2E8]
  0x5b8cd52  mov rcx,[rbp+0x400]
  0x5b8cd59  mov [rcx+0x10],r13
  0x5b8cd68  mov [rcx+0x18],rax
  0x5b8cd76  mov [rcx+0x20],rax

### P16 0x5b8cd6c..0x5b8ce0e (40 instructions)
Release [rbp+0x2E8] (r12): `0x5b8cd83  lock dec dword ptr [r12+8]` / `0x5b8cd9f  lock dec dword ptr [r12+0xC]` + vtable dtors, `jmp 0x5B8CB47`. Then the record-store shared_ptr update (from 0x5b8cdc1, null rax=0): `0x5b8cdc3  mov rcx,[rdi]` saved to [rbp+0x390], `0x5b8cdcd  mov r14,[rbp+0x398]` old value released, `0x5b8cdd4  mov [rbp+0x398],rax` new value, then `0x5b8cde0  lock dec dword ptr [r14+8]` / `0x5b8cdf6  lock dec dword ptr [r14+0xC]` with dtor calls; ends at `0x5b8ce0e  lea rcx,[rbp+0x2C0]` for the next call.
Key field sites:
  0x5b8cd83  lock dec dword ptr [r12+8]
  0x5b8cd9f  lock dec dword ptr [r12+0xC]
  0x5b8cdc3  mov rcx,[rdi]
  0x5b8cdc6  mov [rbp+0x390],rcx
  0x5b8cdcd  mov r14,[rbp+0x398]
  0x5b8cdd4  mov [rbp+0x398],rax
  0x5b8cde0  lock dec dword ptr [r14+8]
  0x5b8cdf6  lock dec dword ptr [r14+0xC]
  0x5b8ce0e  lea rcx,[rbp+0x2C0]

### P17 0x5b8ce15..0x5b8ceb4 (40 instructions)
`0x5b8ce1c  call 0x4DFB570` (rcx=rbp+0x2C0, rdx=rbp+0x390) - stores the built data into the temp pair; then move shared_ptr into [rbp+0x260]/[rbp+0x268]: `0x5b8ce22  mov rax,[rbp+0x2C8]` with `0x5b8ce2e  lock inc dword ptr [rax+8]` -> [rbp+0x268], `0x5b8ce3d  mov rcx,[rbp+0x2C0]` -> `0x5b8ce44  mov [rbp+0x260],rcx`; release the old [rbp+0x268] (`0x5b8ce4b  mov r14,[rbp+0x268]`, `0x5b8ce5e  lock dec dword ptr [r14+8]`, `0x5b8ce74  lock dec dword ptr [r14+0xC]` + dtors) and the old [rbp+0x2C8] (`0x5b8ce8b  mov r14,[rbp+0x2C8]` + same double lock-dec + dtors); ends reloading r14=[rbp+0x398].
Key field sites:
  0x5b8ce15  lea rdx,[rbp+0x390]
  0x5b8ce1c  call 0x4DFB570
  0x5b8ce22  mov rax,[rbp+0x2C8]
  0x5b8ce2e  lock inc dword ptr [rax+8]
  0x5b8ce3d  mov rcx,[rbp+0x2C0]
  0x5b8ce44  mov [rbp+0x260],rcx
  0x5b8ce4b  mov r14,[rbp+0x268]
  0x5b8ce5e  lock dec dword ptr [r14+8]
  0x5b8ce74  lock dec dword ptr [r14+0xC]
  0x5b8ce8b  mov r14,[rbp+0x2C8]

### P18 0x5b8ceb7..0x5b8cf3e (31 instructions)
Release of the [rbp+0x398] shared_ptr copy: lock dec [r14+8], on zero the vtable+0 dtor; lock dec [r14+0xC], on zero the vtable+8 dtor [V 0x5b8cec4..0x5b8cef7]. Assert block at 0x5b8cefd: rax=[rbp+0x3C0] must be non-null and byte [rax] non-zero, else `mov dword ptr [0],0xDEADC0DE` [V 0x5b8cf09/0x5b8cf20]. Then r14=[rbp+0x3D0], edx=[r15+0x10], rcx=r13, call 0x1D30360, nop.

Key field sites:
  0x5b8cec4  mov r14,[rbp+0x398]
  0x5b8ced0  lock dec dword ptr [r14+8]
  0x5b8cee6  lock dec dword ptr [r14+0xC]
  0x5b8cefd  mov rax,[rbp+0x3C0]
  0x5b8cf09  mov dword ptr [0],0xDEADC0DE
  0x5b8cf2b  mov r14,[rbp+0x3D0]
  0x5b8cf32  mov edx,[r15+0x10]

### P19 0x5b8cf3f..0x5b8cfd5 (33 instructions)
call 0x76A8A0(rcx=[rbp+0x390], rdx=r13) finishes the result shared_ptr; then r9d=[rbp+0x390], rax=[[rbp+0x498]]->[+0x40], rax+=0x180, rcx=[r12+0x20], edx=byte [r12+0x74], byte [rbp+0x23C]=0; five stack args staged at [rsp+0x20/0x28/0x30/0x38/0x40] before call 0x668C220(rdi=[rbp+0x2C0] temp, rdx=rbp-0x38, r8=rbp+0x260) [V 0x5b8cfac], then call 0x5B8D520(r14, rdi). Releases [rbp+0x2C8] via 0x4E3B020; std::string dealloc guard: capacity field [rbp+0x3B0] >= 0x10 -> heap block pointer [rbp+0x398].

Key field sites:
  0x5b8cf4f  mov r9d,[rbp+0x390]
  0x5b8cf56  mov rax,[rbp+0x498]
  0x5b8cf6c  mov rcx,[r12+0x20]
  0x5b8cf71  movzx edx,byte ptr [r12+0x74]
  0x5b8cf77  mov byte ptr [rbp+0x23C],0
  0x5b8cf85  mov [rsp+0x40],r8
  0x5b8cf8a  mov [rsp+0x38],dx
  0x5b8cf8f  mov [rsp+0x28],rax
  0x5b8cf94  mov [rsp+0x20],rcx
  0x5b8cf99  mov byte ptr [rsp+0x30],2
  0x5b8cfbe  lea rcx,[rbp+0x2C8]
  0x5b8cfca  mov rax,[rbp+0x3B0]

### P20 0x5b8cfd7..0x5b8d05b (31 instructions)
String dealloc for [rbp+0x3B0]/[rbp+0x398]: rdx=len+1, if >=0x1000 skip; r8=[rcx-8] (allocation-size header), rcx -= 8, sub rcx,r8; if >=0x20 -> 0x5B8D15E (bad size); call 0xE935700 (free) [V 0x5b8d00a]. Identical pattern for the [rbp+0x258]/[rbp+0x240] string [V 0x5b8d00f..0x5b8d04f]. Then release [rbp+0x260] via call 0x4E3B020.

Key field sites:
  0x5b8cfd7  mov rcx,[rbp+0x398]
  0x5b8cfeb  mov r8,[rcx-8]
  0x5b8d00a  call 0xE935700
  0x5b8d00f  mov rax,[rbp+0x258]
  0x5b8d01c  mov rcx,[rbp+0x240]
  0x5b8d030  mov r8,[rcx-8]
  0x5b8d04f  call 0xE935700
  0x5b8d054  lea rcx,[rbp+0x260]

### P21 0x5b8d060..0x5b8d0ef (22 instructions)
Effect-state cleanup at 0x5b8d060: rdi=[rbp+0x3F0] (the [r9+8] object saved at entry); dword [rdi+0x298]=0 and the state flags zeroed: bytes [rdi+0x255], [rdi+0x2A0], [rdi+0x1CA], [rdi], [rdi+0x1B4], [rdi+0x188], [rdi+0x1BA], [rdi+0x168], [rdi+0x194], [rdi+0x1A0], [rdi+0x1AC], [rdi+0x1BE], [rdi+0x1C9], plus qword [rdi+0x170]=0 [V 0x5b8d067..0x5b8d0d8]; rcx=[rbp+0x388] call 0x4DF0440 (release list node); lea rcx,[rbp-0x38] call 0x4DEA990; r13=[rbp+0x400]; jmp 0x5B8CBC9.

Key field sites:
  0x5b8d060  mov rdi,[rbp+0x3F0]
  0x5b8d067  mov dword ptr [rdi+0x298],0
  0x5b8d086  mov rcx,[rbp+0x388]
  0x5b8d095  mov qword ptr [rdi+0x170],0
  0x5b8d0e8  mov r13,[rbp+0x400]

### P22 0x5b8d0f4..0x5b8d177 (34 instructions)
Cold paths. 0x5b8d0f4: operator new(0x270) via call 0x9BC830, jmp 0x5B8C8B1 (factory-null retry). 0x5b8d104: one-time init: call 0xE938CB0 on [0x128D8FC8]; if the dword there != 0xFFFFFFFF jmp 0x5B8C803, else throw via 0xE935740(0xA771D0), then 0xE938D70, jmp 0x5B8C803. Epilogue 0x5b8d13a: rax=r13 (return the output vector), movaps xmm6,[rbp+0x410], add rsp,0x4A8, pop rbx/rdi/rsi/r12/r13/r14/r15/rbp, ret. 0x5b8d158: call 0x75B60 (count-overflow trap). 0x5b8d15e: qword [rsp+0x20]=0, zero ecx/edx/r8d/r9d, call [0xF9A8C78] (abort), int3.

Key field sites:
  0x5b8d0f9  call 0x9BC830
  0x5b8d110  cmp dword ptr [0x128D8FC8],0xFFFFFFFF
  0x5b8d13d  movaps xmm6,[rbp+0x410]
  0x5b8d144  add rsp,0x4A8
  0x5b8d157  ret
  0x5b8d158  call 0x75B60
  0x5b8d171  call qword ptr [0xF9A8C78]
  0x5b8d177  int3

## FIELD TABLE (all [reg+off] accesses; LEA, [abs], gs:[0x58] and [reg+reg*scale] forms excluded; sites merged per distinct address)

| offset (base+off) | size (B) | R/W | verbatim first site | other sites | meaning |
|---|---|---|---|---|---|
| rax+0x0 | 8 | R | `0x5b8c369  mov rax,[rax]` | 0x5b8c4f1, 0x5b8c534, 0x5b8c57c, 0x5b8c7a9, 0x5b8c932, 0x5b8cb5d, 0x5b8cb9d, 0x5b8cbea, 0x5b8cc36, 0x5b8cc92, 0x5b8ccd5, 0x5b8cd1d, 0x5b8cd93, 0x5b8cdea, 0x5b8ce68, 0x5b8cea1, 0x5b8ceda, 0x5b8cf5d | vtable slot 0 loaded before dtor vcalls via [0xF99FFA0] |
| rax+0x8 | 8 | R | `0x5b8c38b  mov rax,[rax+8]` | 0x5b8c508, 0x5b8c54b, 0x5b8c597, 0x5b8c6fc, 0x5b8c895, 0x5b8c916, 0x5b8c923, 0x5b8cb73, 0x5b8cbb3, 0x5b8cc00, 0x5b8cc50, 0x5b8ccaa, 0x5b8cced, 0x5b8cd39, 0x5b8cdaf, 0x5b8ce00, 0x5b8ce7e, 0x5b8ceb7 | vtable slot 1 / weak-ctrl field loaded before second dtor vcall |
| rax+0x10 | 2/8 | R | `0x5b8c823  movzx eax,word ptr [rax+0x10]` | 0x5b8c963 | - |
| rax+0x18 | 8 | R | `0x5b8c94e  mov rcx,[rax+0x18]` | 0x5b8c95b | shared_ptr member of [rbp+0x3F8] object; its ctrl refcount inc'd at 0x5b8c957 |
| rax+0x20 | 8 | R | `0x5b8c682  mov rax,[rax+0x20]` | - | vtable+0x20 slot for per-element vcall |
| rax+0x28 | 8 | R | `0x5b8c7af  mov rax,[rax+0x28]` | 0x5b8c900 | vtable+0x28 slot for per-element vcall |
| rax+0x40 | 8 | R | `0x5b8cf60  mov rax,[rax+0x40]` | - | vtable+0x40 slot on the [[rbp+0x498]] object; +0x180 added |
| rax+0x255 | 1 | R | `0x5b8c716  cmp byte ptr [rax+0x255],0` | - | effect-state flag byte on [rbp+0x3F0] object; set -> skip to 0x5B8CBC9 |
| rcx+0x0 | 8 | R | `0x5b8c32a  mov rax,[rcx]` | 0x5b8c3ae, 0x5b8c67f, 0x5b8c6f9, 0x5b8c7ac, 0x5b8c892, 0x5b8c8fd | vtable slot 0 loaded before vcalls |
| rcx+0x4 | 4 | R | `0x5b8c7f7  cmp eax,[rcx+4]` | - | dword compared in TLS slot check |
| rcx+0x8 | 8 | R | `0x5b8c312  mov rax,[rcx+8]` | 0x5b8c32d | ctrl-block ptr of [r8+0x100] object; refcount inc'd at 0x5b8c326/0x5b8c33e |
| rcx+0x10 | 8 | W | `0x5b8cb26  mov [rcx+0x10],r13` | 0x5b8cd59 | output vector begin (commit) |
| rcx+0x18 | 8 | W | `0x5b8cb35  mov [rcx+0x18],rax` | 0x5b8cd68 | output vector end (commit) |
| rcx+0x20 | 8 | W | `0x5b8cb43  mov [rcx+0x20],rax` | 0x5b8cd76 | output vector capacity end (commit) |
| rcx-0x8 | 8 | R | `0x5b8cfeb  mov r8,[rcx-8]` | 0x5b8d030 | allocation-size header read before free 0xE935700 |
| rcx+r14+0xA20 | 8 | R | `0x5b8c303  mov rdx,[rcx+r14+0xA20]` | - | ctx member at ctx+elemIdx*0x40+0xA20 |
| r12+0x0 | 8 | R | `0x5b8c365  mov rax,[r12]` | 0x5b8c387 | vtable slot 0 |
| r12+0x8 | 4 | R/W | `0x5b8c33e  lock inc dword ptr [r12+8]` | 0x5b8c35d | strong refcount inc/dec of saved [rcx+8] object |
| r12+0xC | 4 | R/W | `0x5b8c37f  lock dec dword ptr [r12+0xC]` | - | weak refcount dec (dtor vcall at 0x5b8c38b..0x5b8c392) |
| r12+0x20 | 8 | R | `0x5b8cf6c  mov rcx,[r12+0x20]` | - | - |
| r12+0x74 | 1 | R | `0x5b8cf71  movzx edx,byte ptr [r12+0x74]` | - | - |
| r12+0x108 | 8 | R | `0x5b8c6c2  mov rax,[r12+0x108]` | - | element shared_ptr member -> [rbp+0x3C0] |
| r12+0x110 | 8 | R | `0x5b8c6a1  mov rax,[r12+0x110]` | 0x5b8c6b2 | element shared_ptr member -> [rbp+0x3C8]; ctrl refcount inc'd 0x5b8c6ae |
| r12+0x118 | 8 | R | `0x5b8c6d8  mov rcx,[r12+0x118]` | - | element shared_ptr member -> [rbp+0x3D0] |
| r12+rax | 16/8 | W | `0x5b8c440  movups [r12+rax],xmm0` | 0x5b8c449 | dest record field 0 while moving old->new buffer (0x38-stride) |
| r12+rax+8 | 8 | W | `0x5b8c452  mov [r12+rax+8],rcx` | - | dest record field 8 |
| r12+rax+0x10 | 16/8 | W | `0x5b8c45b  movups [r12+rax+0x10],xmm0` | 0x5b8c466 | dest record field 0x10 |
| r12+rax+0x18 | 8 | W | `0x5b8c470  mov [r12+rax+0x18],rcx` | - | dest record field 0x18 |
| r12+rax+0x20 | 16/8 | W | `0x5b8c47a  movups [r12+rax+0x20],xmm0` | 0x5b8c485 | dest record field 0x20 |
| r12+rax+0x28 | 8 | W | `0x5b8c48f  mov [r12+rax+0x28],rcx` | - | dest record field 0x28 |
| r12+rax+0x30 | 1 | W | `0x5b8c49e  mov [r12+rax+0x30],cl` | - | dest record flag byte 0x30 |
| r13+0x0 | 16/8 | W | `0x5b8c334  movups [r13],xmm0` | 0x5b8c344, 0x5b8c3ba | result-vector shared_ptr {ptr} init |
| r13+0x8 | 16/8 | W | `0x5b8c348  mov [r13+8],r12` | 0x5b8c3c1 | result-vector shared_ptr {ctrl} init (zeroed by movups) |
| r13+0x10 | 8 | R/W | `0x5b8c5b3  mov [r13+0x10],r12` | 0x5b8c9d2 | output vector begin |
| r13+0x18 | 8 | R/W | `0x5b8c414  mov rbx,[r13+0x18]` | 0x5b8c5ba, 0x5b8c96e, 0x5b8c9c9 | output vector end (0x38-stride records) |
| r13+0x20 | 8 | R/W | `0x5b8c355  mov qword ptr [r13+0x20],0` | 0x5b8c3d1, 0x5b8c5c9, 0x5b8c972 | output vector capacity end |
| r13+0x28 | 8 | W | `0x5b8c3cd  mov [r13+0x28],rbx` | - | stack arg6 stored into result object |
| r13+rax | 16/8 | W | `0x5b8caa0  movups [r13+rax],xmm6` | 0x5b8ca42, 0x5b8caaa | record field 0 stored into grown buffer (zero or copy) |
| r13+rax+8 | 8 | W | `0x5b8ca4e  mov [r13+rax+8],rcx` | 0x5b8cab4 | record field 8 |
| r13+rax+0x10 | 16/8 | W | `0x5b8cabd  movups [r13+rax+0x10],xmm6` | 0x5b8ca61, 0x5b8cac8 | record field 0x10 |
| r13+rax+0x18 | 8 | W | `0x5b8ca6d  mov [r13+rax+0x18],rcx` | 0x5b8cad2 | record field 0x18 |
| r13+rax+0x20 | 16/8 | W | `0x5b8cadc  movups [r13+rax+0x20],xmm6` | 0x5b8ca7d, 0x5b8cae7 | record field 0x20 |
| r13+rax+0x28 | 8 | W | `0x5b8ca89  mov [r13+rax+0x28],rdx` | 0x5b8caf1 | record field 0x28 |
| r13+rax+0x30 | 1 | W | `0x5b8ca92  mov byte ptr [r13+rax+0x30],0` | 0x5b8cb00 | record flag byte 0x30 |
| r14+0x0 | 8 | R/W | `0x5b8c8c6  mov [r14],rax` | 0x5b8cb5a, 0x5b8cb9a, 0x5b8cbe7, 0x5b8cbfd, 0x5b8cc33, 0x5b8cc4d, 0x5b8cde7, 0x5b8ced7 | new-object vtable store 0xF249870; later vtable slot 0 loads for dtors |
| r14+0x8 | 8/4 | R/W | `0x5b8c8bb  mov [r14+8],rax` | 0x5b8cb53, 0x5b8cb93, 0x5b8cbe0, 0x5b8cc28, 0x5b8cde0, 0x5b8ced0 | init qword 0x100000001 (vtable+strong count); later strong refcount lock dec |
| r14+0xC | 4 | R/W | `0x5b8cb69  lock dec dword ptr [r14+0xC]` | 0x5b8cba9, 0x5b8cbf6, 0x5b8cc42, 0x5b8cdf6, 0x5b8cee6 | weak refcount lock dec |
| rbx+0x0 | 8 | W | `0x5b8c97f  mov [rbx],rax` | - | record field 0 (appended at old end) |
| rbx+8 | 8 | W | `0x5b8c989  mov [rbx+8],rax` | - | record field 8 |
| rbx+0x10 | 2/8 | R/W | `0x5b8c803  lock inc word ptr [rbx+0x10]` | 0x5b8c99b | rwlock count word (lock inc); later qword record field 0x10 |
| rbx+0x12 | 1 | R | `0x5b8c808  movzx eax,byte ptr [rbx+0x12]` | - | state byte bit0 tested |
| rbx+0x18 | 8 | W | `0x5b8c9a6  mov [rbx+0x18],rax` | - | record field 0x18 |
| rbx+0x20 | 8 | W | `0x5b8c9b9  mov [rbx+0x20],r12` | - | record field 0x20 |
| rbx+0x28 | 8 | W | `0x5b8c9bd  mov [rbx+0x28],rcx` | - | record field 0x28 |
| rbx+0x30 | 1 | W | `0x5b8c9c1  mov byte ptr [rbx+0x30],0` | - | record flag byte 0x30 |
| r15+0x0 | 8 | R | `0x5b8c610  mov r15,[r15]` | - | std::list node next walk |
| r15+0x8 | 8 | R | `0x5b8c560  mov r13,[r15+8]` | - | list member released (refcount dec 0x5b8c56d) |
| r15+0x10 | 4 | R | `0x5b8cf32  mov edx,[r15+0x10]` | - | dword arg for call 0x1D30360 |
| r15+0x18 | 8 | R | `0x5b8c520  mov r13,[r15+0x18]` | 0x5b8c677, 0x5b8c7a9, 0x5b8c8fa | element shared_ptr member; ctrl refcounts inc/dec |
| r15+0x20 | 8 | R | `0x5b8c624  mov rdi,[r15+0x20]` | - | list node member -> release walk base |
| r15+0x28 | 8 | R | `0x5b8c4dd  mov r13,[r15+0x28]` | - | list member released (refcount dec 0x5b8c4e6) |
| r15+r14+0x8 | 8 | R | `0x5b8c5e5  mov r15,[rax+8]` | - | list node at head+elemIdx*0x40, member +8 (rax=r15+r14) |
| rdi+0x0 | 8/1 | R/W | `0x5b8c7d2  mov rbx,[rdi]` | 0x5b8cdc3, 0x5b8d092 | vtable slot 0 loads; state byte zeroed at cleanup |
| rdi+0x8 | 8 | R | `0x5b8c81b  mov rax,[rdi+8]` | 0x5b8c827, 0x5b8c832, 0x5b8cd00 | shared_ptr member loaded; ctrl refcount inc/dec |
| rdi+0x18 | 8 | R | `0x5b8ccc0  mov r12,[rdi+0x18]` | - | member released (refcount dec 0x5b8ccc9/0x5b8cce1) |
| rdi+0x28 | 8 | R | `0x5b8cc7d  mov r12,[rdi+0x28]` | - | member released (refcount dec 0x5b8cc86/0x5b8cc9e) |
| rdi+0x298 | 4 | W | `0x5b8d067  mov dword ptr [rdi+0x298],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x255 | 1 | W | `0x5b8d071  mov byte ptr [rdi+0x255],0` | - | effect-state flag cleared at cleanup 0x5b8d060; also tested at 0x5b8c716 |
| rdi+0x2A0 | 1 | W | `0x5b8d078  mov byte ptr [rdi+0x2A0],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x1CA | 1 | W | `0x5b8d07f  mov byte ptr [rdi+0x1CA],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x170 | 8 | W | `0x5b8d095  mov qword ptr [rdi+0x170],0` | - | effect-state field cleared at cleanup 0x5b8d060 |
| rdi+0x1B4 | 1 | W | `0x5b8d0a0  mov byte ptr [rdi+0x1B4],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x188 | 1 | W | `0x5b8d0a7  mov byte ptr [rdi+0x188],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x1BA | 1 | W | `0x5b8d0ae  mov byte ptr [rdi+0x1BA],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x168 | 1 | W | `0x5b8d0b5  mov byte ptr [rdi+0x168],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x194 | 1 | W | `0x5b8d0bc  mov byte ptr [rdi+0x194],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x1A0 | 1 | W | `0x5b8d0c3  mov byte ptr [rdi+0x1A0],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x1AC | 1 | W | `0x5b8d0ca  mov byte ptr [rdi+0x1AC],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x1BE | 1 | W | `0x5b8d0d1  mov byte ptr [rdi+0x1BE],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+0x1C9 | 1 | W | `0x5b8d0d8  mov byte ptr [rdi+0x1C9],0` | - | effect-state flag cleared at cleanup 0x5b8d060 |
| rdi+rax | 16/8 | R/W | `0x5b8c445  mov rcx,[rdi+rax]` | 0x5b8c457, 0x5b8caa6, 0x5b8cab9 | source record field 0 during move/zero |
| rdi+rax+8 | 8 | R | `0x5b8c44d  mov rcx,[rdi+rax+8]` | 0x5b8caaf | source record field 8 |
| rdi+rax+0x10 | 16/8 | R/W | `0x5b8c461  mov rcx,[rdi+rax+0x10]` | 0x5b8c475, 0x5b8cac3, 0x5b8cad7 | source record field 0x10 |
| rdi+rax+0x18 | 8 | R | `0x5b8c46b  mov rcx,[rdi+rax+0x18]` | 0x5b8cacd | source record field 0x18 |
| rdi+rax+0x20 | 16/8 | R/W | `0x5b8c480  mov rcx,[rdi+rax+0x20]` | 0x5b8c494, 0x5b8cae2, 0x5b8caf6 | source record field 0x20 |
| rdi+rax+0x28 | 8 | R | `0x5b8c48a  mov rcx,[rdi+rax+0x28]` | 0x5b8caec | source record field 0x28 |
| rdi+rax+0x30 | 1 | R | `0x5b8c499  movzx ecx,byte ptr [rdi+rax+0x30]` | 0x5b8cafb | source record flag byte 0x30 |
| r9+0x8 | 8 | R | `0x5b8c2f8  mov rax,[r9+8]` | - | arg4 object member saved to [rbp+0x3F0] |
| r8+0x100 | 8 | R | `0x5b8c30b  mov rcx,[r8+0x100]` | - | arg3 object member -> shared_ptr target |
| rbp+0x23C | 1 | W | `0x5b8cf77  mov byte ptr [rbp+0x23C],0` | - | - |
| rbp+0x240 | 8 | R | `0x5b8d01c  mov rcx,[rbp+0x240]` | - | std::string data ptr; freed at 0x5b8d04f with cap [rbp+0x258] |
| rbp+0x258 | 8 | R | `0x5b8d00f  mov rax,[rbp+0x258]` | - | std::string capacity field >=0x10 -> heap free |
| rbp+0x260 | 16/8 | W | `0x5b8c78f  movaps [rbp+0x260],xmm6` | 0x5b8c857, 0x5b8ce44 | zeroed; string constant {0xF5AFBFF,0xD}; later result shared_ptr dest |
| rbp+0x268 | 8 | R/W | `0x5b8c85e  mov qword ptr [rbp+0x268],0xD` | 0x5b8ce4b, 0x5b8ce52 | len 0xD; later ctrl ptr released (lock dec 0x5b8ce5e/0x5b8ce74) |
| rbp+0x270 | 16 | W | `0x5b8c788  movaps [rbp+0x270],xmm6` | - | 16B temp zero |
| rbp+0x280 | 1 | W | `0x5b8c796  mov byte ptr [rbp+0x280],0` | - | - |
| rbp+0x288 | 16 | W | `0x5b8c781  movups [rax],xmm6` | - | 16B temp zero (alias rax=rbp+0x288) |
| rbp+0x298 | 1 | W | `0x5b8c784  mov byte ptr [rax+0x10],0` | - | temp flag zero (alias rax+0x10=rbp+0x298) |
| rbp+0x2A0 | 16 | W | `0x5b8c7a1  movups [rax+0x18],xmm6` | - | 16B temp zero (alias rax+0x18=rbp+0x2A0) |
| rbp+0x2B0 | 16 | W | `0x5b8c79d  movups [rax+0x28],xmm6` | - | 16B temp zero (alias rax+0x28=rbp+0x2B0) |
| rbp+0x2C0 | 16/8 | R/W | `0x5b8c8e1  mov [rbp+0x2C0],r14` | 0x5b8c978, 0x5b8c98d, 0x5b8ca3b, 0x5b8ca53, 0x5b8ce3d | temp shared_ptr {ptr} for new record |
| rbp+0x2C8 | 8 | R/W | `0x5b8c8e8  mov [rbp+0x2C8],rax` | 0x5b8c982, 0x5b8cb47, 0x5b8cb80, 0x5b8ce22, 0x5b8ce8b | temp shared_ptr {ctrl}; alias base for 16B zeroing of rbp+0x2D0/0x2E0 |
| rbp+0x2D0 | 16/8 | R/W | `0x5b8c912  movups [rcx+8],xmm6` | 0x5b8c935, 0x5b8c994, 0x5b8c9b1, 0x5b8ca79 | temp shared_ptr {ptr} (alias rcx+8=rbp+0x2D0) |
| rbp+0x2D8 | 8 | R/W | `0x5b8c93c  mov [rbp+0x2D8],rcx` | 0x5b8c99f, 0x5b8cb47 | temp shared_ptr {ctrl}, released at 0x5b8cb53 |
| rbp+0x2E0 | 16 | W | `0x5b8c94a  movups [rcx+0x18],xmm6` | 0x5b8c9bd, 0x5b8ca8e | 16B zero spanning 0x2E0-0x2EF (alias rcx+0x18=rbp+0x2E0) |
| rbp+0x2E8 | 8 | R | `0x5b8cd4b  mov r12,[rbp+0x2E8]` | - | old-element base for release walk; zeroed via overlapping rbp+0x2E0 store |
| rbp+0x2F0 | 1 | W | `0x5b8c967  mov byte ptr [rbp+0x2F0],0` | - | - |
| rbp+0x370 | 8 | W | `0x5b8c731  mov [rbp+0x370],rax` | - | string constant ptr 0xF5AFB66 |
| rbp+0x378 | 8 | W | `0x5b8c738  mov qword ptr [rbp+0x378],0x19` | - | string constant len 0x19 |
| rbp+0x380 | 8 | R/W | `0x5b8c9e0  mov [rbp+0x380],rcx` | 0x5b8ca82 | temp member stored into record field 0x28 |
| rbp+0x388 | 8 | R/W | `0x5b8c5f4  mov [rbp+0x388],rax` | 0x5b8d086 | saved std::list head (ctx member) |
| rbp+0x390 | 16/8/4 | R/W | `0x5b8c814  movaps [rbp+0x390],xmm6` | 0x5b8cdc6, 0x5b8cf4f | result shared_ptr temp; dword read as r9d arg for 0x668C220 |
| rbp+0x398 | 8 | R/W | `0x5b8cdcd  mov r14,[rbp+0x398]` | 0x5b8cdd4, 0x5b8cec4, 0x5b8cfd7 | string heap data ptr / ctrl; released at 0x5b8ced0, freed at 0x5b8d00a |
| rbp+0x3B0 | 8 | R | `0x5b8cfca  mov rax,[rbp+0x3B0]` | - | string capacity field >=0x10 -> heap free |
| rbp+0x3C0 | 16/8 | R/W | `0x5b8c69a  movaps [rbp+0x3C0],xmm6` | 0x5b8c6ca, 0x5b8cbd0, 0x5b8cefd | copied element shared_ptr {ptr}; asserted non-null at 0x5b8cefd |
| rbp+0x3C8 | 8 | R/W | `0x5b8c6d1  mov [rbp+0x3C8],rcx` | 0x5b8cbc9, 0x5b8cc0d | copied element shared_ptr {ctrl}; released twice at tail |
| rbp+0x3D0 | 8 | R/W | `0x5b8c6e0  mov [rbp+0x3D0],rcx` | 0x5b8cc14, 0x5b8cf2b | third copied member; zeroed at tail, reloaded for 0x1D30360 |
| rbp+0x3E0 | 8 | R/W | `0x5b8c3fa  mov [rbp+0x3E0],r15` | 0x5b8c5d4, 0x5b8c5fe, 0x5b8c613 | list walk cursor/end marker |
| rbp+0x3E8 | 8 | R/W | `0x5b8c319  mov [rbp+0x3E8],r8` | 0x5b8c3a2, 0x5b8c3b3, 0x5b8c5cd | saved r8 arg object |
| rbp+0x3F0 | 8 | R/W | `0x5b8c2fc  mov [rbp+0x3F0],rax` | 0x5b8c5e9, 0x5b8c64b, 0x5b8c70f, 0x5b8c74a, 0x5b8c870, 0x5b8d060 | saved [r9+8] effect object; state cleared at cleanup |
| rbp+0x3F8 | 8 | R/W | `0x5b8c41b  mov [rbp+0x3F8],rdx` | 0x5b8c5be, 0x5b8c8c9, 0x5b8c8e8, 0x5b8ca15, 0x5b8cb2a, 0x5b8cd5d | record count; imul 0x38 for byte size |
| rbp+0x400 | 8 | R/W | `0x5b8c3ed  mov [rbp+0x400],r13` | 0x5b8c5ac, 0x5b8c71d, 0x5b8c92b, 0x5b8cb1f, 0x5b8cd52, 0x5b8d0e8 | result vector object ptr |
| rbp+0x408 | 8 | W | `0x5b8c2d2  mov qword ptr [rbp+0x408],0xFFFFFFFFFFFFFFFE` | - | security cookie init |
| rbp+0x410 | 16 | R/W | `0x5b8c2cb  movaps [rbp+0x410],xmm6` | 0x5b8d13d | xmm6 callee save/restore |
| rbp+0x490 | 4 | R | `0x5b8c2ed  movsxd r14,[rbp+0x490]` | - | stack arg (int) -> elemIdx base |
| rbp+0x498 | 8 | R | `0x5b8c2e6  mov rbx,[rbp+0x498]` | 0x5b8cf56 | stack arg (ptr) |
| rsp+0x20 | 8/2/1 | W | `0x5b8c646  mov byte ptr [rsp+0x20],0` | 0x5b8c743, 0x5b8c869, 0x5b8cf94, 0x5b8d15e | shadow-space slot; stack arg for 0x668C220, zeroed for abort call |
| rsp+0x28 | 8 | W | `0x5b8cf8f  mov [rsp+0x28],rax` | - | stack arg for 0x668C220 |
| rsp+0x30 | 1 | W | `0x5b8cf99  mov byte ptr [rsp+0x30],2` | - | stack arg byte 2 |
| rsp+0x38 | 2 | W | `0x5b8cf8a  mov [rsp+0x38],dx` | - | stack arg word |
| rsp+0x40 | 8 | W | `0x5b8cf85  mov [rsp+0x40],r8` | - | stack arg ptr |

## TOOL REQUESTS
None
