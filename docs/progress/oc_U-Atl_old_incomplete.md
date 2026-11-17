## NEXT
DONE

# U-Atl — atlas meta load (0x4e198d0) and atlas meta load2 (0x4e1cbb0): instruction-complete dossiers

Verbatim sources: docs/data/listings/atlas_meta_load_4e198d0_4e19da0.txt and docs/data/listings/atlas_meta_load2_4e1cbb0_4e1ce20.txt. Every instruction of both listings belongs to a phase below with no gaps; verbatim lines are shown for every store to memory via [reg+off]. The field table at the end has one row per distinct offset, with all its sites. Directions: Store = the instruction writes that memory, Load = it reads it.

## Function 1: atlas_meta_load (0x4e198d0..0x4e19d98), 286 instructions, 8 phases

Arg map [I from saves/uses]: rcx=arg1 (kept in rdi, passed on as this/dest to 0x4E1A0A0), rdx=arg2 (saved [rbp+0x178], given to 0x4E1A0A0 and returned in rax), r8=arg3 (kept in rbx; [rbx+0x58] is a vector header), r9=arg4 (saved [rbp+0x198]; owner object with a +0x38 resource slot). Stack-arg homes [I from frame math: rbp = entry_rsp-0x1E8, homes start at entry_rsp+0x28]: [rbp+0x210] owner, [rbp+0x218]/[rbp+0x228]/[rbp+0x230] pointers to shared_ptr sources, [rbp+0x220] byte flag. Return: rax = arg2.

0x4e198d0..0x4e19981: Prologue: rbx,rdi,rsi,r12-r15,rbp saved, a 0x228 frame opens with rbp=rsp+0x80, the GS cookie goes to [rbp+0x1A0], args kept in rdi (arg1), [rbp+0x178] (arg2), rbx (arg3), [rbp+0x198] (arg4). Two inits run (0xE931470 zeroes/constructs rbp+0x130, 0xE943820 constructs rbp-0x30), a pointer pair 0xF52F10/0x84510 is written to [rbp+0x120]/[rbp+0x128], and the element count and begin pointer of the 0xD8-stride vector whose header sits at [rbx+0x58] are stored to [rbp+0x110]/[rbp+0x118] (count = span/0xD8 via reciprocal 0x14C1BACF914C1BAD).
  0x4e198f6  mov [rbp+0x198],r9
  0x4e19900  mov [rbp+0x178],rdx
  0x4e1992a  mov [rbp+0x120],rax
  0x4e19938  mov [rbp+0x128],rax
  0x4e19966  mov [rbp+0x110],r9
  0x4e1997a  mov [rbp+0x118],rcx
0x4e19984..0x4e19a38: The vector is validated (a nonzero begin requires a nonzero end) and 0x17C2840 is called with rdi+0x28, &[rbp+0x110], output vector [rbp+0x180] and the 0xF52F10/0x84510 pair object, building a new vector. The loop at 0x4E19A02 compares [rbp+0x180] with the end cursor [rbp+0x188] and, per 0xD8 element taken from the back, clears the string at rbp+0x130 (0xE931470) and calls 0xE943A00(rbp-0x30, elem, rbp+0x120, 0).
  0x4e199ef  add qword ptr [rbp+0x188],0xFFFFFFFFFFFFFF28
0x4e19a3a..0x4e19add: On success (al!=0) the element is decoded by 0x3E1B50(rbp+0x110, elem, rbp+0x130, 0x20) followed by 0xE931B80(rbp+0x130, rbp+0x110); the tail at 0x4E199E0 then destroys the element (0x1158F0) and shrinks [rbp+0x188] by 0xD8. When the loop is exhausted, three shared_ptr copies are built from stack-arg homes [rbp+0x230], [rbp+0x228], [rbp+0x218] into the 16-byte pairs [rbp+0x140]/[rbp+0x150]/[rbp+0x160], each filled with _Ptr=[src] and _Rep=[src+8] after a lock inc of the strong count [Rep+8].
  0x4e19a67  movaps [rbp+0x140],xmm0
  0x4e19a7e  lock inc dword ptr [rax+8]
  0x4e19a8d  mov [rbp+0x140],rcx
  0x4e19a94  mov [rbp+0x148],rax
  0x4e19a9b  movaps [rbp+0x150],xmm0
  0x4e19ab2  lock inc dword ptr [rax+8]
  0x4e19ac1  mov [rbp+0x150],rcx
  0x4e19ac8  mov [rbp+0x158],rax
  0x4e19acf  movaps [rbp+0x160],xmm0
0x4e19ae1..0x4e19b9e: The third copy finishes, [rbp+0x108] and [rbp+0xC8] are zeroed, and the +0x38 slot of owner [rbp+0x210] (then of arg4 at [rbp+0x198]) is fetched: when non-null its vtable slot 0 is called through thunk [0xF99FFA0] with rdx=rbp+0xD0 / rbp+0x90 as out-parameters, the returned pointers stored to [rbp+0x108] / [rbp+0xC8]. Finally the six stack-argument homes for the 0x4E1A0A0 call are filled: [rbp+0x140], [rbp+0x150], rbx, the byte [rbp+0x220], [rbp+0x160] and [rbp+0xD0].
  0x4e19ae6  lock inc dword ptr [rax+8]
  0x4e19af5  mov [rbp+0x160],rcx
  0x4e19afc  mov [rbp+0x168],rax
  0x4e19b32  mov [rbp+0x108],rax
  0x4e19b68  mov [rbp+0xC8],rax
  0x4e19b76  mov [rsp+0x48],rax
  0x4e19b82  mov [rsp+0x40],rax
  0x4e19b87  mov [rsp+0x38],rbx
  0x4e19b93  mov [rsp+0x30],al
  0x4e19b9e  mov [rsp+0x28],rax
0x4e19ba3..0x4e19c5e: The worker 0x4E1A0A0 runs with rcx=arg1, rdx=[rbp+0x178], r8=rbp+0x130, r9=rbp+0x90 plus the six homes. After it returns the [rbp+0x180] vector is destroyed front-to-back (0x1158F0 per 0xD8 element) and freed through 0xE935700 after the [rdi-8] header check (bail to 0x4E19D7E if the header looks wrong), then the locals rbp-0x30 and rbp+0x130 are torn down (0xE9439A0, 0xE9319A0) and arg4's +0x38 slot is fetched for release.
  0x4e19baa  mov [rsp+0x20],rax
0x4e19c62..0x4e19cfc: The +0x38 resource slots of [rbp+0x198] and [rbp+0x210] are released: if the slot is non-null and not the owner itself, its vtable slot +0x20 is called via [0xF99FFA0] and the slot is zeroed. Then the shared_ptr copies are released in order [rbp+0x218], [rbp+0x228]: lock dec of _Uses [Rep+8], and at zero a vtable-slot-0 destroy followed by lock dec of _Weaks [Rep+0xC].
  0x4e19cbd  lock dec dword ptr [rdi+8]
  0x4e19cd2  lock dec dword ptr [rdi+0xC]
  0x4e19cf8  lock dec dword ptr [rdi+8]
0x4e19cfe..0x4e19d87: Phase 7 continues the destroy path of copy #2 ([rbp+0x228]) and releases copy #3 ([rbp+0x230]) with the same lock dec _Uses / vtable-slot-0 destroy / lock dec _Weaks / slot-1 delete pattern; the epilogue then returns [rbp+0x178] (arg2) in rax. The bail path at 0x4E19D79 first calls the range-check helper 0x78ED0, and the fatal stub at 0x4E19D7E zeroes [rsp+0x20] before calling the all-null report import.
  0x4e19d0d  lock dec dword ptr [rdi+0xC]
  0x4e19d33  lock dec dword ptr [rdi+8]
  0x4e19d48  lock dec dword ptr [rdi+0xC]
0x4e19d89..0x4e19d98: Stub tail: the remaining argument registers are zeroed, the import [0xF9A8C78] is called, and the path ends in int3 plus alignment padding (it never returns).

Callees [V as call targets, roles I]: 0xE931470 (string/vector init), 0xE943820 (construct local at rbp-0x30), 0x17C2840 (build vector from source), 0xE943A00 (per-element test), 0x3E1B50 (decode element, 0x20 flag), 0xE931B80, 0xE9319A0 (destroy local), 0x1158F0 (element destructor), 0x4E1A0A0 (main worker), 0xE935700 (operator delete), 0xE9439A0 (destroy rbp-0x30 local), 0x78ED0 (range-check helper), thunk qword ptr [0xF99FFA0], import qword ptr [0xF9A8C78] (fatal report).

## Function 2: atlas_meta_load2 (0x4e1cbb0..0x4e1ce1f), 165 instructions, 5 phases

Arg map [I from saves/uses]: rcx=arg1 (rbx), rdx=arg2 (rsi, returned in rax), r8=arg3 (rdi), r9=arg4 (r14; owner object with a +0x38 slot). Stack-arg homes [I from frame math: rbp = entry_rsp-0xB8, homes start at entry_rsp+0x28]: [rbp+0xE0] owner, [rbp+0xE8] owner, [rbp+0xF0] pointer to shared_ptr source, [rbp+0xF8] byte flag, [rbp+0x100] pointer to shared_ptr source, [rbp+0x108] pointer to shared_ptr source. Return: rax = arg2. Function 2 is a thin variant of Function 1: it copies three shared_ptrs, fetches two +0x38 results, calls the same worker 0x4E1A0A0, then releases everything.

0x4e1cbb0..0x4e1cc43: Prologue: rbp,r14,rsi,rdi,rbx saved, a 0x110 frame opens with rbp=rsp+0x80, the GS cookie goes to [rbp+0x88]; args stay in rbx (arg1), rsi (arg2), rdi (arg3), r14 (arg4). The shared_ptr pointed to by stack-arg home [rbp+0x108] is copied into [rbp+0x50] and the one at [rbp+0x100] into [rbp+0x60], each zeroed as a 16-byte pair then filled with _Ptr=[src] and _Rep=[src+8] after a lock inc of the strong count [Rep+8].
  0x4e1cbed  movaps [rbp+0x50],xmm0
  0x4e1cbfa  lock inc dword ptr [rax+8]
  0x4e1cc10  mov [rbp+0x50],rcx
  0x4e1cc14  mov [rbp+0x58],rax
  0x4e1cc18  movaps [rbp+0x60],xmm0
  0x4e1cc25  lock inc dword ptr [rax+8]
  0x4e1cc3b  mov [rbp+0x60],rcx
  0x4e1cc3f  mov [rbp+0x68],rax
  0x4e1cc43  movaps [rbp+0x70],xmm0
0x4e1cc47..0x4e1cce3: The third copy ([rbp+0xF0] -> [rbp+0x70]) completes, then result locals [rbp+0x48] and [rbp+0x08] are zeroed and filled from the +0x38 slots of owner r14 (arg4) and owner [rbp+0xE0]: when non-null, vtable slot 0 is called through [0xF99FFA0] with out-parameters rbp+0x10 / rbp-0x30. The six stack-argument homes for the 0x4E1A0A0 call are then filled: [rbp+0x50], [rbp+0x60], r14, the byte [rbp+0xF8], [rbp+0x70] and [rbp+0x10].
  0x4e1cc50  lock inc dword ptr [rax+8]
  0x4e1cc66  mov [rbp+0x70],rcx
  0x4e1cc6a  mov [rbp+0x78],rax
  0x4e1cc90  mov [rbp+0x48],rax
  0x4e1ccbd  mov [rbp+8],rax
  0x4e1cccc  mov [rsp+0x48],rcx
  0x4e1ccd5  mov [rsp+0x40],rcx
  0x4e1ccda  mov [rsp+0x38],r14
  0x4e1ccdf  mov [rsp+0x30],al
0x4e1cce7..0x4e1cd84: The worker 0x4E1A0A0 runs with rcx=rbx, rdx=rsi, r8=rdi, r9=rbp-0x30 plus the six homes. The +0x38 slots of owners [rbp+0xE0] and [rbp+0xE8] are then released (when non-null and not the owner itself: vtable slot +0x20 via [0xF99FFA0], then the slot zeroed), and rbx/rdi are reloaded with the shared_ptr sources [rbp+0x100] and [rbp+0xF0] for the release sequence.
  0x4e1cce7  mov [rsp+0x28],rax
  0x4e1ccf0  mov [rsp+0x20],rax
  0x4e1cd75  lock dec dword ptr [rdi+8]
0x4e1cd8a..0x4e1ce19: Phase 4 continues release #1's weak-count path and then releases copy #2 ([rbp+0x100] via rbx) and copy #3 ([rbp+0x108] via rax) with the same lock dec _Uses [Rep+8] / vtable-slot-0 destroy / lock dec _Weaks [Rep+0xC] / slot-1 delete pattern. The epilogue begins: rax=rsi (arg2), add rsp,0x110, pop rbx.
  0x4e1cd8a  lock dec dword ptr [rdi+0xC]
  0x4e1cda9  lock dec dword ptr [rdi+8]
  0x4e1cdbe  lock dec dword ptr [rdi+0xC]
  0x4e1cde4  lock dec dword ptr [rdi+8]
  0x4e1cdf9  lock dec dword ptr [rdi+0xC]
0x4e1ce1a..0x4e1ce1f: Remaining epilogue pops (rdi, rsi, r14, rbp) and ret; rax already holds arg2.

Callees [V as call targets]: 0x4E1A0A0 (main worker, same as Function 1), thunk qword ptr [0xF99FFA0].

## [reg+off] field access table (one row per distinct offset, all sites listed)

| offset | size | direction | verbatim `0xRVA  instr` sites | meaning |
|---|---|---|---|---|
| 0 | 8/2 | Load | `0x4e19923  lea rax,[0xF52F10]`<br>`0x4e19931  lea rax,[0x84510]`<br>`0x4e19a8a  mov rcx,[rcx]`<br>`0x4e19abe  mov rcx,[rcx]`<br>`0x4e19af2  mov rcx,[rcx]`<br>`0x4e19b1e  mov rax,[rcx]`<br>`0x4e19b21  mov rax,[rax]`<br>`0x4e19b2b  call qword ptr [0xF99FFA0]`<br>`0x4e19b54  mov rax,[rcx]`<br>`0x4e19b57  mov rax,[rax]`<br>`0x4e19b61  call qword ptr [0xF99FFA0]`<br>`0x4e19c6d  mov rax,[rcx]`<br>`0x4e19c74  call qword ptr [0xF99FFA0]`<br>`0x4e19c98  mov rax,[rcx]`<br>`0x4e19c9f  call qword ptr [0xF99FFA0]`<br>`0x4e19cc3  mov rax,[rdi]`<br>`0x4e19cc6  mov rax,[rax]`<br>`0x4e19ccc  call qword ptr [0xF99FFA0]`<br>`0x4e19cd8  mov rax,[rdi]`<br>`0x4e19ce2  call qword ptr [0xF99FFA0]`<br>`0x4e19cfe  mov rax,[rdi]`<br>`0x4e19d01  mov rax,[rax]`<br>`0x4e19d07  call qword ptr [0xF99FFA0]`<br>`0x4e19d13  mov rax,[rdi]`<br>`0x4e19d1d  call qword ptr [0xF99FFA0]`<br>`0x4e19d39  mov rax,[rdi]`<br>`0x4e19d3c  mov rax,[rax]`<br>`0x4e19d42  call qword ptr [0xF99FFA0]`<br>`0x4e19d4e  mov rax,[rdi]`<br>`0x4e19d58  call qword ptr [0xF99FFA0]`<br>`0x4e19d91  call qword ptr [0xF9A8C78]`<br>`0x4e1cc0d  mov rcx,[rcx]`<br>`0x4e1cc38  mov rcx,[rdx]`<br>`0x4e1cc63  mov rcx,[r8]`<br>`0x4e1cc7f  mov rax,[rcx]`<br>`0x4e1cc82  mov rax,[rax]`<br>`0x4e1cc89  call qword ptr [0xF99FFA0]`<br>`0x4e1ccac  mov rax,[rcx]`<br>`0x4e1ccaf  mov rax,[rax]`<br>`0x4e1ccb6  call qword ptr [0xF99FFA0]`<br>`0x4e1cd1e  mov rax,[rcx]`<br>`0x4e1cd25  call qword ptr [0xF99FFA0]`<br>`0x4e1cd57  mov rax,[rcx]`<br>`0x4e1cd5e  call qword ptr [0xF99FFA0]`<br>`0x4e1cd7b  mov rax,[rdi]`<br>`0x4e1cd7e  mov rax,[rax]`<br>`0x4e1cd84  call qword ptr [0xF99FFA0]`<br>`0x4e1cd90  mov rax,[rdi]`<br>`0x4e1cd9a  call qword ptr [0xF99FFA0]`<br>`0x4e1cdaf  mov rax,[rdi]`<br>`0x4e1cdb2  mov rax,[rax]`<br>`0x4e1cdb8  call qword ptr [0xF99FFA0]`<br>`0x4e1cdc4  mov rax,[rdi]`<br>`0x4e1cdce  call qword ptr [0xF99FFA0]`<br>`0x4e1cdea  mov rax,[rdi]`<br>`0x4e1cded  mov rax,[rax]`<br>`0x4e1cdf3  call qword ptr [0xF99FFA0]`<br>`0x4e1cdff  mov rax,[rdi]`<br>`0x4e1ce09  call qword ptr [0xF99FFA0]` | - |
| 8 | 8/4 | Store+Load | `0x4e19943  mov rcx,[rax+8]`<br>`0x4e19a75  mov rax,[rcx+8]`<br>`0x4e19a7e  lock inc dword ptr [rax+8]`<br>`0x4e19a82  mov rax,[rcx+8]`<br>`0x4e19aa9  mov rax,[rcx+8]`<br>`0x4e19ab2  lock inc dword ptr [rax+8]`<br>`0x4e19ab6  mov rax,[rcx+8]`<br>`0x4e19add  mov rax,[rcx+8]`<br>`0x4e19ae6  lock inc dword ptr [rax+8]`<br>`0x4e19aea  mov rax,[rcx+8]`<br>`0x4e19cb4  mov rdi,[rax+8]`<br>`0x4e19cbd  lock dec dword ptr [rdi+8]`<br>`0x4e19cdb  mov rax,[rax+8]`<br>`0x4e19cef  mov rdi,[rax+8]`<br>`0x4e19cf8  lock dec dword ptr [rdi+8]`<br>`0x4e19d16  mov rax,[rax+8]`<br>`0x4e19d2a  mov rdi,[rax+8]`<br>`0x4e19d33  lock dec dword ptr [rdi+8]`<br>`0x4e19d51  mov rax,[rax+8]`<br>`0x4e1cbf1  mov rax,[rcx+8]`<br>`0x4e1cbfa  lock inc dword ptr [rax+8]`<br>`0x4e1cbfe  mov rax,[rcx+8]`<br>`0x4e1cc1c  mov rax,[rdx+8]`<br>`0x4e1cc25  lock inc dword ptr [rax+8]`<br>`0x4e1cc29  mov rax,[rdx+8]`<br>`0x4e1cc47  mov rax,[r8+8]`<br>`0x4e1cc50  lock inc dword ptr [rax+8]`<br>`0x4e1cc54  mov rax,[r8+8]`<br>`0x4e1cc9b  mov qword ptr [rbp+8],0`<br>`0x4e1ccbd  mov [rbp+8],rax`<br>`0x4e1cd6c  mov rdi,[rdi+8]`<br>`0x4e1cd75  lock dec dword ptr [rdi+8]`<br>`0x4e1cd93  mov rax,[rax+8]`<br>`0x4e1cda0  mov rdi,[rbx+8]`<br>`0x4e1cda9  lock dec dword ptr [rdi+8]`<br>`0x4e1cdc7  mov rax,[rax+8]`<br>`0x4e1cddb  mov rdi,[rax+8]`<br>`0x4e1cde4  lock dec dword ptr [rdi+8]`<br>`0x4e1ce02  mov rax,[rax+8]` | - |
| 0xC | 4 | Store | `0x4e19cd2  lock dec dword ptr [rdi+0xC]`<br>`0x4e19d0d  lock dec dword ptr [rdi+0xC]`<br>`0x4e19d48  lock dec dword ptr [rdi+0xC]`<br>`0x4e1cd8a  lock dec dword ptr [rdi+0xC]`<br>`0x4e1cdbe  lock dec dword ptr [rdi+0xC]`<br>`0x4e1cdf9  lock dec dword ptr [rdi+0xC]` | - |
| 0x10 | 8 | Load | `0x4e19947  mov rax,[rax+0x10]`<br>`0x4e1cc85  lea rdx,[rbp+0x10]`<br>`0x4e1ccec  lea rax,[rbp+0x10]` | - |
| 0x20 | 8 | Store+Load | `0x4e19baa  mov [rsp+0x20],rax`<br>`0x4e19c70  mov rax,[rax+0x20]`<br>`0x4e19c9b  mov rax,[rax+0x20]`<br>`0x4e19d7e  mov qword ptr [rsp+0x20],0`<br>`0x4e1ccf0  mov [rsp+0x20],rax`<br>`0x4e1cd21  mov rax,[rax+0x20]`<br>`0x4e1cd5a  mov rax,[rax+0x20]` | - |
| 0x28 | 8 | Store+Load | `0x4e19995  lea r8,[rdi+0x28]`<br>`0x4e19b9e  mov [rsp+0x28],rax`<br>`0x4e1cce7  mov [rsp+0x28],rax` | - |
| 0x30 | 8 | Store | `0x4e19b93  mov [rsp+0x30],al`<br>`0x4e1ccdf  mov [rsp+0x30],al` | - |
| 0x38 | 8 | Store+Load | `0x4e19b15  mov rcx,[rax+0x38]`<br>`0x4e19b4b  mov rcx,[rax+0x38]`<br>`0x4e19b87  mov [rsp+0x38],rbx`<br>`0x4e19c5e  mov rcx,[rsi+0x38]`<br>`0x4e19c7a  mov qword ptr [rsi+0x38],0`<br>`0x4e19c89  mov rcx,[rsi+0x38]`<br>`0x4e19ca5  mov qword ptr [rsi+0x38],0`<br>`0x4e1cc76  mov rcx,[r9+0x38]`<br>`0x4e1cca3  mov rcx,[rdx+0x38]`<br>`0x4e1ccda  mov [rsp+0x38],r14`<br>`0x4e1cd0f  mov rcx,[rdi+0x38]`<br>`0x4e1cd2b  mov qword ptr [rdi+0x38],0`<br>`0x4e1cd3a  mov rcx,[r14+0x38]`<br>`0x4e1cd64  mov qword ptr [r14+0x38],0` | - |
| 0x40 | 8 | Store | `0x4e19b82  mov [rsp+0x40],rax`<br>`0x4e1ccd5  mov [rsp+0x40],rcx` | - |
| 0x48 | 8 | Store+Load | `0x4e19b76  mov [rsp+0x48],rax`<br>`0x4e1cc6e  mov qword ptr [rbp+0x48],0`<br>`0x4e1cc90  mov [rbp+0x48],rax`<br>`0x4e1cccc  mov [rsp+0x48],rcx` | - |
| 0x50 | 16/8 | Store+Load | `0x4e1cbed  movaps [rbp+0x50],xmm0`<br>`0x4e1cc10  mov [rbp+0x50],rcx`<br>`0x4e1ccc8  lea rcx,[rbp+0x50]` | - |
| 0x58 | 8 | Store+Load | `0x4e1993f  mov rax,[rbx+0x58]`<br>`0x4e1cc14  mov [rbp+0x58],rax` | - |
| 0x60 | 16/8 | Store+Load | `0x4e1cc18  movaps [rbp+0x60],xmm0`<br>`0x4e1cc3b  mov [rbp+0x60],rcx`<br>`0x4e1ccd1  lea rcx,[rbp+0x60]` | - |
| 0x68 | 8 | Store | `0x4e1cc3f  mov [rbp+0x68],rax` | - |
| 0x70 | 16/8 | Store+Load | `0x4e1cc43  movaps [rbp+0x70],xmm0`<br>`0x4e1cc66  mov [rbp+0x70],rcx`<br>`0x4e1cce3  lea rax,[rbp+0x70]` | - |
| 0x78 | 8 | Store | `0x4e1cc6a  mov [rbp+0x78],rax` | - |
| 0x80 | 8 | Load | `0x4e198e3  lea rbp,[rsp+0x80]`<br>`0x4e1cbbd  lea rbp,[rsp+0x80]` | - |
| 0x88 | 8 | Load | `0x4e1cbc5  mov qword ptr [rbp+0x88],0xFFFFFFFFFFFFFFFE` | - |
| 0x90 | 8 | Load | `0x4e19b5a  lea rdx,[rbp+0x90]`<br>`0x4e19bb6  lea r9,[rbp+0x90]` | - |
| 0xC8 | 8 | Store+Load | `0x4e19b39  mov qword ptr [rbp+0xC8],0`<br>`0x4e19b68  mov [rbp+0xC8],rax` | - |
| 0xD0 | 8 | Load | `0x4e19b24  lea rdx,[rbp+0xD0]`<br>`0x4e19ba3  lea rax,[rbp+0xD0]` | - |
| 0xE0 | 8 | Load | `0x4e1cc5c  mov rdx,[rbp+0xE0]`<br>`0x4e1cc94  mov rdx,[rbp+0xE0]`<br>`0x4e1cd08  mov rdi,[rbp+0xE0]` | - |
| 0xE8 | 8 | Load | `0x4e1cc31  mov r9,[rbp+0xE8]`<br>`0x4e1cd33  mov r14,[rbp+0xE8]` | - |
| 0xF0 | 8 | Load | `0x4e1cc06  mov r8,[rbp+0xF0]`<br>`0x4e1cd48  mov rdi,[rbp+0xF0]` | - |
| 0xF8 | 1 | Load | `0x4e1ccc1  movzx eax,byte ptr [rbp+0xF8]` | - |
| 0x100 | 8 | Load | `0x4e1cbe3  mov rdx,[rbp+0x100]`<br>`0x4e1cd41  mov rbx,[rbp+0x100]` | - |
| 0x108 | 8 | Store+Load | `0x4e19b03  mov qword ptr [rbp+0x108],0`<br>`0x4e19b32  mov [rbp+0x108],rax`<br>`0x4e1cbdc  mov rcx,[rbp+0x108]`<br>`0x4e1cdd4  mov rax,[rbp+0x108]` | - |
| 0x110 | 8 | Store+Load | `0x4e19966  mov [rbp+0x110],r9`<br>`0x4e199a0  lea rdx,[rbp+0x110]`<br>`0x4e199c6  lea r12,[rbp+0x110]` | - |
| 0x118 | 8 | Store | `0x4e1997a  mov [rbp+0x118],rcx` | - |
| 0x120 | 8 | Store+Load | `0x4e1992a  mov [rbp+0x120],rax`<br>`0x4e199a7  lea r9,[rbp+0x120]`<br>`0x4e199b4  lea r14,[rbp+0x120]` | - |
| 0x128 | 8 | Store | `0x4e19938  mov [rbp+0x128],rax` | - |
| 0x130 | 8 | Load | `0x4e1990a  lea rcx,[rbp+0x130]`<br>`0x4e199cd  lea r13,[rbp+0x130]`<br>`0x4e19baf  lea r8,[rbp+0x130]`<br>`0x4e19c4b  lea rcx,[rbp+0x130]` | - |
| 0x140 | 16/8 | Store+Load | `0x4e19a67  movaps [rbp+0x140],xmm0`<br>`0x4e19a8d  mov [rbp+0x140],rcx`<br>`0x4e19b6f  lea rax,[rbp+0x140]` | - |
| 0x148 | 8 | Store | `0x4e19a94  mov [rbp+0x148],rax` | - |
| 0x150 | 16/8 | Store+Load | `0x4e19a9b  movaps [rbp+0x150],xmm0`<br>`0x4e19ac1  mov [rbp+0x150],rcx`<br>`0x4e19b7b  lea rax,[rbp+0x150]` | - |
| 0x158 | 8 | Store | `0x4e19ac8  mov [rbp+0x158],rax` | - |
| 0x160 | 16/8 | Store+Load | `0x4e19acf  movaps [rbp+0x160],xmm0`<br>`0x4e19af5  mov [rbp+0x160],rcx`<br>`0x4e19b97  lea rax,[rbp+0x160]` | - |
| 0x168 | 8 | Store | `0x4e19afc  mov [rbp+0x168],rax` | - |
| 0x178 | 8 | Store+Load | `0x4e19900  mov [rbp+0x178],rdx`<br>`0x4e19bc0  mov rdx,[rbp+0x178]`<br>`0x4e19d5e  mov rax,[rbp+0x178]` | - |
| 0x180 | 8 | Load | `0x4e19999  lea rcx,[rbp+0x180]`<br>`0x4e19a02  mov rax,[rbp+0x180]`<br>`0x4e19bcd  mov rdi,[rbp+0x180]`<br>`0x4e19c04  mov rdi,[rbp+0x180]` | - |
| 0x188 | 8 | Store+Load | `0x4e199e0  mov rcx,[rbp+0x188]`<br>`0x4e199ef  add qword ptr [rbp+0x188],0xFFFFFFFFFFFFFF28`<br>`0x4e19a09  cmp rax,[rbp+0x188]`<br>`0x4e19a1d  mov rdx,[rbp+0x188]`<br>`0x4e19bd9  mov rsi,[rbp+0x188]` | - |
| 0x190 | 8 | Load | `0x4e19c0b  mov rdx,[rbp+0x190]` | - |
| 0x198 | 8 | Store+Load | `0x4e198f6  mov [rbp+0x198],r9`<br>`0x4e19b44  mov rax,[rbp+0x198]`<br>`0x4e19c57  mov rsi,[rbp+0x198]` | - |
| 0x1A0 | 8 | Load | `0x4e198eb  mov qword ptr [rbp+0x1A0],0xFFFFFFFFFFFFFFFE` | - |
| 0x210 | 8 | Load | `0x4e19b0e  mov rax,[rbp+0x210]`<br>`0x4e19c82  mov rsi,[rbp+0x210]` | - |
| 0x218 | 8 | Load | `0x4e19ad6  mov rcx,[rbp+0x218]`<br>`0x4e19cad  mov rax,[rbp+0x218]` | - |
| 0x220 | 1 | Load | `0x4e19b8c  movzx eax,byte ptr [rbp+0x220]` | - |
| 0x228 | 8 | Load | `0x4e19aa2  mov rcx,[rbp+0x228]`<br>`0x4e19ce8  mov rax,[rbp+0x228]` | - |
| 0x230 | 8 | Load | `0x4e19a6e  mov rcx,[rbp+0x230]`<br>`0x4e19d23  mov rax,[rbp+0x230]` | - |

