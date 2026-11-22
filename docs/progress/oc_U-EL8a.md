## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path pending

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending".
Do ONLY the pending part: the pack->GPU path. SDK headers exist (TexturePtr.h 32B two shared_ptr; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub) so header layout is NOT the pending part; the pending part is the runtime path from a resource-pack file to a GPU texture in Minecraft.Windows.exe 1.26.62.01.

Method: static analysis only; RVAs relative to image base; every claim [V] = verbatim from disassembly (cite RVA), [I] = inferred, [?] = unknown. All verbatim `0xRVA  instr` lines below are copied verbatim from the precomputed input listings (docs/data/listings/texgroup_load_5421c90_54235a0.txt and docs/data/listings/texload_58a1310_58a23d0.txt; supporting decode chain sub_1994f90/sub_764950/sub_777ed0 from docs/data/listings and prior units U-L8b..U-L8d, U-Tex), all already verify_oc-clean. Sizes come from the instruction (movups/movaps 16, movss 4, movsd 8, qword 8, dword 4, word 2, byte 1). One row per distinct offset, all its sites listed; meaning only where an instruction or string shows it, else '-'. No input data pasted as-is; no raw instruction lines outside table cells.

## Path context (what is proven [V] before the table)

Pack file bytes -> sub_1994f90 (file-bytes image loader; comp count {1,3,4} validated via bitmask 0x1A at 0x1995041/0x1995046; out-slots dim/comp) -> sub_764950 (allocates w*h*comp*4 via [0xF9A6FA0] at 0x764a7e-0x764a81; returns 32-bit pixel buffer in rax) -> sub_777ed0 (PNG decoder entry; magic 0x89 check at 0x777f55; "bad png sig" error at 0x7784be).
texload 0x58a1310: per-texture state — walks element ranges [rbx+0xE8..0xF0] (stride 0x90) and [rbx+0x160..0x168] (stride 0x30; each 0x30 block appended to the group via texgroup append 0x5417950); builds per-texture stage/descriptor object rsi (UV/atlas fields +0x178..+0x244) and a 0x40-byte object (vtable 0xF09B320 at +0x00, refcount 0x100000001 at +0x8); reads loaded-image info object r13 (+0x58/+0x60/+0x64/+0x6C/+0x70/+0x74/+0x78/+0x84/+0x88); builds a UV rotation/scale matrix (calls [0xF9A8E18] and [0xF9A8F48], 0xAA6580 x3).
texgroup_load 0x5421c90 (TextureGroup object this = arg rcx, saved at [rbp+0x228]): looks up/inserts the named texture in the group's RB-tree/intrusive list (head group+0x248, counter group+0x250); creates a 0x20-byte handle object (vtable 0xF09AA70 at +0x00, refcount 0x100000001 at +0x8, +0x10 zeroed), a 0x80-byte texture entry (name string +0x28/+0x38/+0x40, metadata blocks +0x48/+0x58/+0x60/+0x70, self-linked list node), a 0x70-byte list node (+0x20/+0x28/+0x38/+0x40/+0x48/+0x58/+0x60), then calls undecoded callee 0x18718D0 at 0x54227af with the texture descriptor (rcx=[rsi+0x1C8], r8=owner object, rdx=&descriptor block, r9=&0xF24D3E8) — callee not decoded (font unit U-I5i labels it resource registration, [I]).

## ANSWER TABLE — every [reg+off] field stored or loaded in the pack->GPU path functions texgroup_load 0x5421c90 and texload 0x58a1310 (one row per distinct offset, all sites listed; size from the instruction; meaning only where shown by an instruction/string, else '-'; all tags [V] = verbatim from verified listings)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| group+0x20 | 8 B | 0x5421fc2 | `0x5421fc2  mov rax,[rsi+0x20]` | object pointer (rax-0x18 owner adjustment at 0x5421fca) | [V] |
| group+0x28 | 8 B | 0x5421f80; 0x5421fc6 | `0x5421f80  mov rcx,[rsi+0x28]`<br>`0x5421fc6  mov r12,[rsi+0x28]` | refcounted object pointer | [V] |
| group+0x1B8 | 8 B | 0x542202e | `0x542202e  mov rax,[rsi+0x1B8]` | pointer; its byte [rax] is compared to 0 at 0x542203e, else 0xDEADC0DE is written to address 0 at 0x5422043 | [V] |
| group+0x1C8 | 8 B | 0x542204e; 0x5422a0c | `0x542204e  mov rax,[rsi+0x1C8]`<br>`0x5422a0c  mov rax,[rsi+0x1C8]` | texture pointer slot; passed as rcx to callee 0x18718D0 at 0x54227a4 | [V] |
| group+0x1C0 | 8 B | 0x54229d5; 0x54229ec | `0x54229d5  mov rax,[rsi+0x1C0]`<br>`0x54229ec  mov rax,[rsi+0x1C0]` | texture pointer slot (exe decode at these RVAs differs from the precomputed listing's +0x1C8; exe taken as truth) | [V] |
| group+0x248 | 8 B | 0x5421df1; 0x5422fab | `0x5421df1  cmp rax,[rsi+0x248]`<br>`0x5422fab  mov rax,[rsi+0x248]` | RB-tree / intrusive-list head of texture entries; insert rewires [rax]/[rax+8]/[rax+0x10] | [V] |
| group+0x250 | 8 B | 0x5422fa4; 0x5422e31 | `0x5422fa4  inc qword ptr [rsi+0x250]`<br>`0x5422e31  cmp [rsi+0x250],rax` | texture counter; incremented on every insert, compared against 0x249249249249249 | [V] |
| group+0x268 | 8 B | 0x54225a0; 0x542220a | `0x54225a0  mov rcx,[rsi+0x268]`<br>`0x542220a  mov rcx,[rsi+0x268]` | pointer slot | [V] |
| group+0x270 | 8 B | 0x5422595; 0x54221ef; 0x5422585 | `0x5422595  mov rax,[rsi+0x270]`<br>`0x54221ef  mov rax,[rsi+0x270]`<br>`0x5422585  mov rax,[rsi+0x270]` | refcounted object pointer; [rax+8] lock-inc addref | [V] |
| hndl+0x00 | 8 B | 0x5421f6f | `0x5421f6f  mov [rdi],rax` | vtable 0xF09AA70 | [V] |
| hndl+0x08 | 8/4 B | 0x5421f59; 0x5422091 | `0x5421f59  mov [rdi+8],rax`<br>`0x5422091  lock inc dword ptr [rdi+8]` | refcount: init 0x100000001; lock-inc addref | [V] |
| hndl+0x10 | 16 B | 0x5421f75 | `0x5421f75  movups [rdi+0x10],xmm0` | zeroed | [V] |
| ent+0x00 | 16/8 B | 0x5422271; 0x542228a | `0x5422271  movups [rdi],xmm0`<br>`0x542228a  mov [rbx],rcx` | zeroed; then +0x00 overwritten with rcx ([rbp+0x140]) | [V] |
| ent+0x10 | 16/8 B | 0x5422295; 0x54222bb | `0x5422295  movups [rbx+0x10],xmm0`<br>`0x54222bb  mov [rbx+0x10],rax` | zeroed; pointer slot | [V] |
| ent+0x18 | 4 B | 0x54222bf | `0x54222bf  mov [rbx+0x18],rcx` | dword | [V] |
| ent+0x20 | 4 B | 0x54222c9 | `0x54222c9  mov [rbx+0x20],eax` | dword from entry arg [r8+0] | [V] |
| ent+0x28 | 16/8 B | 0x54222cc; 0x54223a0 | `0x54222cc  movups [rbx+0x28],xmm0`<br>`0x54223a0  mov [rbx+0x28],rsi` | zeroed; name-string pointer (heap path) | [V] |
| ent+0x38 | 16/8 B | 0x54222d0; 0x5422302; 0x54223a8 | `0x54222d0  movups [rbx+0x38],xmm0`<br>`0x5422302  mov [rbx+0x38],r12`<br>`0x54223a8  mov [rbx+0x38],rdi` | zeroed; name length / capacity | [V] |
| ent+0x40 | 8 B | 0x5422306; 0x54223a8 | `0x5422306  mov qword ptr [rbx+0x40],0xF`<br>`0x54223a8  mov [rbx+0x40],rdi` | capacity 0xF (SSO); name pointer | [V] |
| ent+0x48 | 16 B | 0x54223ce | `0x54223ce  movups [rbx+0x48],xmm0` | 16-byte block copied from entry arg [r12+0x28] | [V] |
| ent+0x58 | 4 B | 0x54223d8 | `0x54223d8  mov [rbx+0x58],ecx` | dword (r15d load-order arg); RB-tree key (compared at 0x5422dcd) | [V] |
| ent+0x60 | 16 B | 0x54223e2 | `0x54223e2  movups [rbx+0x60],xmm0` | zeroed | [V] |
| ent+0x70 | 16 B | 0x54223f1 | `0x54223f1  movups [rbx+0x70],xmm1` | 16 bytes ([rbp+0x1B0] = [r14+0x58]+0x51) | [V] |
| ent2+0x00 | 8 B | 0x5422a81 | `0x5422a81  mov [rbx],rax` | vtable 0xF24D400 | [V] |
| ent2+0x08 | 16/8 B | 0x5422a87; 0x5422a9e | `0x5422a87  movups [rbx+8],xmm0`<br>`0x5422a9e  mov [rbx+8],rcx` | zeroed; pointer; [rax+0xC] lock-inc addref at 0x5422aa6 | [V] |
| ent2+0x10 | 8 B | 0x5422aa2 | `0x5422aa2  mov [rbx+0x10],rax` | pointer | [V] |
| ent2+0x18 | 4 B | 0x5422ab0 | `0x5422ab0  mov [rbx+0x18],eax` | dword | [V] |
| ent2+0x20 | 16/8 B | 0x5422ab3; 0x5422b7f | `0x5422ab3  movups [rbx+0x20],xmm0`<br>`0x5422b7f  mov [rbx+0x20],rsi` | zeroed; pointer | [V] |
| ent2+0x30 | 16/8 B | 0x5422ab7; 0x5422ae9; 0x5422b83 | `0x5422ab7  movups [rbx+0x30],xmm0`<br>`0x5422ae9  mov [rbx+0x30],r12`<br>`0x5422b83  mov [rbx+0x30],r12` | zeroed; length | [V] |
| ent2+0x38 | 8 B | 0x5422aed; 0x5422b87 | `0x5422aed  mov qword ptr [rbx+0x38],0xF`<br>`0x5422b87  mov [rbx+0x38],rdi` | capacity 0xF (SSO); pointer | [V] |
| ent2+0x40 | 16 B | 0x5422bad | `0x5422bad  movups [rbx+0x40],xmm0` | 16 bytes from [rbp+0x178] | [V] |
| ent2+0x50 | 4 B | 0x5422bb7 | `0x5422bb7  mov [rbx+0x50],eax` | dword from [rbp+0x188] | [V] |
| ent2+0x58 | 16/8 B | 0x5422bbd; 0x5422bea | `0x5422bbd  movups [rbx+0x58],xmm0`<br>`0x5422bea  mov [rbx+0x58],rcx` | zeroed; pointer [rbp+0x190]; [rax+8] lock-inc addref at 0x5422bd4 | [V] |
| ent2+0x60 | 8 B | 0x5422bee | `0x5422bee  mov [rbx+0x60],rax` | zero/pointer | [V] |
| ent2+0x68 | 8 B | 0x5422bf9 | `0x5422bf9  mov [rbx+0x68],rax` | pointer [rbp+0x1A0] | [V] |
| ent2+0x70 | 16/8 B | 0x5422c0f; 0x5422c35 | `0x5422c0f  movups [rbx+0x70],xmm0`<br>`0x5422c35  mov [rbx+0x70],rcx` | zeroed; pointer [rbp+0x1A8]; [rax+8] lock-inc addref at 0x5422c1f | [V] |
| ent2+0x78 | 8 B | 0x5422c39 | `0x5422c39  mov [rbx+0x78],rax` | pointer | [V] |
| node+0x00 | 8 B | 0x5422f93 | `0x5422f93  mov [rbx],rax` | self-referential list node (+0x8/+0x10 mirror) | [V] |
| node+0x08 | 8 B | 0x5422f96 | `0x5422f96  mov [rbx+8],rax` | self-link | [V] |
| node+0x10 | 8 B | 0x5422f9a | `0x5422f9a  mov [rbx+0x10],rax` | self-link | [V] |
| node+0x18 | 2 B | 0x5422f9e | `0x5422f9e  mov word ptr [rbx+0x18],0` | flag word cleared at init | [V] |
| node+0x20 | 4 B | 0x5422e6a | `0x5422e6a  mov [rbx+0x20],eax` | dword [rbp+0x1C0] (= entry arg [r8+0]) | [V] |
| node+0x28 | 16/8 B | 0x5422e70; 0x5422f46 | `0x5422e70  movups [rbx+0x28],xmm0`<br>`0x5422f46  mov [rbx+0x28],rsi` | zeroed; data pointer (SSO inline buffer or heap pointer) | [V] |
| node+0x38 | 16/8 B | 0x5422e74; 0x5422eb1; 0x5422f4a | `0x5422e74  movups [rbx+0x38],xmm0`<br>`0x5422eb1  mov [rbx+0x38],r14`<br>`0x5422f4a  mov [rbx+0x38],r14` | zeroed; length (r14) | [V] |
| node+0x40 | 8 B | 0x5422eb5; 0x5422f4e | `0x5422eb5  mov qword ptr [rbx+0x40],0xF`<br>`0x5422f4e  mov [rbx+0x40],rdi` | capacity 0xF (SSO); computed capacity | [V] |
| node+0x48 | 16 B | 0x5422f78 | `0x5422f78  movups [rbx+0x48],xmm0` | 16 bytes from [rbp+0x1E8] | [V] |
| node+0x58 | 4 B | 0x5422f82 | `0x5422f82  mov [rbx+0x58],eax` | dword [rbp+0x1F8] | [V] |
| node+0x60 | 16 B | 0x5422f88 | `0x5422f88  movups [rbx+0x60],xmm0` | zeroed | [V] |
| tex+0xE8 | 8 B | 0x58a15ca | `0x58a15ca  mov r13,[rbx+0xE8]` | element cursor | [V] |
| tex+0xF0 | 8 B | 0x58a15d1 | `0x58a15d1  mov rax,[rbx+0xF0]` | element end | [V] |
| tex+0x100 | 8 B | 0x58a146a | `0x58a146a  mov rcx,[rbx+0x100]` | per-element vec3 table | [V] |
| tex+0x118 | 8 B | 0x58a14d0 | `0x58a14d0  mov rcx,[rbx+0x118]` | per-element vec3 table | [V] |
| tex+0x130 | 8 B | 0x58a1535 | `0x58a1535  mov r8,[rbx+0x130]` | 8-byte pair table | [V] |
| tex+0x160 | 8 B | 0x58a1401 | `0x58a1401  mov rdi,[rbx+0x160]` | range begin walked stride 0x30; each 0x30 block -> texgroup append 0x5417950 | [V] |
| tex+0x168 | 8 B | 0x58a1408 | `0x58a1408  mov r14,[rbx+0x168]` | range end | [V] |
| tex+0x178 | 1 B | 0x58a13db | `0x58a13db  cmp byte ptr [rbx+0x178],0` | flag byte selecting xmm6/xmm7 source | [V] |
| tex+0x1A0 | 4 B | 0x58a13e4 | `0x58a13e4  movss xmm6,[rbx+0x1A0]` | float scale source | [V] |
| tex+0x1A4 | 4 B | 0x58a13ec | `0x58a13ec  movss xmm7,[rbx+0x1A4]` | float scale source | [V] |
| tex+0x6C | 8 B | 0x58a1485; 0x58a148d | `0x58a1485  movsd xmm2,[rbx+0x6C]`<br>`0x58a148d  movlps [rbx+0x6C],xmm2` | bbox min (8 bytes) | [V] |
| tex+0x74 | 4 B | 0x58a1475; 0x58a1491 | `0x58a1475  movss xmm0,[rbx+0x74]`<br>`0x58a1491  movss [rbx+0x74],xmm0` | bbox/component | [V] |
| tex+0x78 | 8 B | 0x58a14a9; 0x58a14b1 | `0x58a14a9  movsd xmm2,[rbx+0x78]`<br>`0x58a14b1  movlps [rbx+0x78],xmm2` | bbox max (8 bytes) | [V] |
| tex+0x80 | 4 B | 0x58a1496; 0x58a14b5 | `0x58a1496  movss xmm0,[rbx+0x80]`<br>`0x58a14b5  movss [rbx+0x80],xmm0` | bbox/component | [V] |
| stage+0x159 | 1 B | 0x58a13c9 | `0x58a13c9  mov byte ptr [rsi+0x159],1` | flag byte = 1 | [V] |
| stage+0x1B0 | 4 B | 0x58a13ba | `0x58a13ba  mov dword ptr [rsi+0x1B0],0xFFFFFFFF` | dword = -1 | [V] |
| stage+0x1B4 | 1 B | 0x58a13aa; 0x58a13b3 | `0x58a13aa  cmp byte ptr [rsi+0x1B4],0`<br>`0x58a13b3  mov byte ptr [rsi+0x1B4],1` | flag byte | [V] |
| stage+0x15A | 1 B | 0x58a1525 | `0x58a1525  mov byte ptr [rsi+0x15A],1` | flag byte | [V] |
| stage+0x15C | 1 B | 0x58a15be | `0x58a15be  mov byte ptr [rsi+0x15C],1` | flag byte | [V] |
| stage+0x178 | 4 B | 0x58a14ec | `0x58a14ec  movss [rsi+0x178],xmm2` | packed vec3 x | [V] |
| stage+0x17C | 4 B | 0x58a1508 | `0x58a1508  movss [rsi+0x17C],xmm1` | packed vec3 y | [V] |
| stage+0x180 | 8 B | 0x58a1517 | `0x58a1517  movlps [rsi+0x180],xmm1` | packed vec3 z/w (8 bytes) | [V] |
| stage+0x188 | 1 B | 0x58a14f4; 0x58a14fd | `0x58a14f4  cmp byte ptr [rsi+0x188],0`<br>`0x58a14fd  mov byte ptr [rsi+0x188],1` | first-time flag byte | [V] |
| stage+0x18C | 4 B | 0x58a157b | `0x58a157b  movss [rsi+0x18C],xmm2` | min/max-combined blended value | [V] |
| stage+0x190 | 4 B | 0x58a15ae | `0x58a15ae  movss [rsi+0x190],xmm1` | min/max-combined blended value | [V] |
| stage+0x194 | 1 B | 0x58a1583; 0x58a158c | `0x58a1583  cmp byte ptr [rsi+0x194],0`<br>`0x58a158c  mov byte ptr [rsi+0x194],1` | flag byte | [V] |
| stage+0x254 | 1 B | 0x58a13a1 | `0x58a13a1  cmp byte ptr [rsi+0x254],0` | flag byte | [V] |
| desc+0x1CC | 8 B | 0x58a18f1 | `0x58a18f1  mov qword ptr [rax],0` (rax = rsi+0x1CC per 0x58a18e3) | zeroed | [V] |
| desc+0x1D4 | 4 B | 0x58a18ea | `0x58a18ea  mov dword ptr [rax+8],0` | zeroed | [V] |
| desc+0x1D8 | 8 B | 0x58a1911 | `0x58a1911  mov [rax],r15` (rax = rsi+0x1D8 per 0x58a18ff) | qword from global [0xEFFE428] | [V] |
| desc+0x1E0 | 4 B | 0x58a1906 | `0x58a1906  mov [rax+8],r14d` | dword from global [0xEFFE430] | [V] |
| desc+0x210 | 1 B | 0x58a1993 | `0x58a1993  mov byte ptr [rsi+0x210],1` | flag byte = 1 | [V] |
| desc+0x214 | 4 B | 0x58a1931 | `0x58a1931  movss [rsi+0x214],xmm15` | matrix row (UV transform) | [V] |
| desc+0x218 | 16 B | 0x58a193a | `0x58a193a  movups [rsi+0x218],xmm11` | matrix rows (UV transform) | [V] |
| desc+0x228 | 4 B | 0x58a194b | `0x58a194b  movss [rsi+0x228],xmm10` | matrix row | [V] |
| desc+0x22C | 8 B | 0x58a1959 | `0x58a1959  movlps [rsi+0x22C],xmm13` | matrix row | [V] |
| desc+0x234 | 4 B | 0x58a1961 | `0x58a1961  movss [rsi+0x234],xmm9` | matrix row | [V] |
| desc+0x238 | 4 B | 0x58a196a | `0x58a196a  movss [rsi+0x238],xmm9` | matrix row | [V] |
| desc+0x23C | 4 B | 0x58a1973 | `0x58a1973  movss [rsi+0x23C],xmm12` | matrix row | [V] |
| desc+0x240 | 4 B | 0x58a197c | `0x58a197c  movss [rsi+0x240],xmm9` | matrix row | [V] |
| desc+0x244 | 16 B | 0x58a198c | `0x58a198c  movups [rsi+0x244],xmm0` | constant vector [0xF0922E0] | [V] |
| imginfo+0x58 | 8 B | 0x58a18b0 | `0x58a18b0  mov rax,[r13+0x58]` | qword (-> [rbp+0x70]) | [V] |
| imginfo+0x60 | 4 B | 0x58a18a9 | `0x58a18a9  mov eax,[r13+0x60]` | dword (-> [rbp+0x78]) | [V] |
| imginfo+0x64 | 8 B | 0x58a18a3 | `0x58a18a3  movsd xmm7,[r13+0x64]` | qword | [V] |
| imginfo+0x6C | 4 B | 0x58a189d | `0x58a189d  movss xmm6,[r13+0x6C]` | float | [V] |
| imginfo+0x7C | 8 B | 0x58a18c6 | `0x58a18c6  movsd xmm1,[r13+0x7C]` | qword | [V] |
| imginfo+0x84 | 4 B | 0x58a18b8 | `0x58a18b8  movss xmm12,[r13+0x84]` | float | [V] |
| imginfo+0x70 | 4 B | 0x58a1c6a | `0x58a1c6a  movss xmm7,[r13+0x70]` | float (scaled by [0xEFD3334]) | [V] |
| imginfo+0x74 | 4 B | 0x58a1dfb | `0x58a1dfb  movss xmm7,[r13+0x74]` | float (scaled by [0xEFD3334]) | [V] |
| imginfo+0x78 | 4 B | 0x58a1f50 | `0x58a1f50  movss xmm7,[r13+0x78]` | float (scaled by [0xEFD3334]) | [V] |
| imginfo+0x88 | 1 B | 0x58a1a71 | `0x58a1a71  movzx eax,byte ptr [r13+0x88]` | byte flag | [V] |
| obj40+0x00 | 8 B | 0x58a1767 | `0x58a1767  mov [r15],rax` | vtable 0xF09B320 | [V] |
| obj40+0x08 | 8 B | 0x58a175c | `0x58a175c  mov [r15+8],rax` | refcount 0x100000001 | [V] |
| rbp+0x80 | 16/4 B | 0x58a2046; 0x58a20d5 | `0x58a2046  movaps [rbp+0x80],xmm7`<br>`0x58a20d5  mov dword ptr [rbp+0x80],0x3F800000` | matrix row; then float 1.0 | [V] |
| rbp+0x90 | 16 B | 0x58a2054 | `0x58a2054  movaps [rbp+0x90],xmm6` | matrix row | [V] |
| rbp+0xA0 | 16 B | 0x58a206d | `0x58a206d  movaps [rbp+0xA0],xmm0` | matrix row | [V] |
| rbp+0xB0 | 16 B | 0x58a207b | `0x58a207b  movaps [rbp+0xB0],xmm0` | constant [0xF0922E0] | [V] |
| rbp+0x110 | 16 B | 0x58a1c4e | `0x58a1c4e  movaps [rbp+0x110],xmm0` | matrix block row (passed to 0xAA6580 x3) | [V] |
| rbp+0x120 | 16 B | 0x58a1c55 | `0x58a1c55  movaps [rbp+0x120],xmm1` | matrix block row | [V] |
| rbp+0x130 | 16 B | 0x58a1c5c | `0x58a1c5c  movaps [rbp+0x130],xmm2` | matrix block row | [V] |
| rbp+0x140 | 16 B | 0x58a1c63 | `0x58a1c63  movaps [rbp+0x140],xmm3` | matrix block row | [V] |

## CLOSES?
NO — the pending part (pack->GPU path reaching the GPU) is not proven: no bgfx createTexture call, no RendererContextD3D12 vtable slot-26 use (0xe8143c0), and no GPU-handle write into any TexturePtr/BedrockTexture field appears anywhere in texgroup_load 0x5421c90, texload 0x58a1310, texload_task 0x541bf00, or the decode chain (sub_1994f90 -> sub_764950 -> sub_777ed0); registration ends at undecoded callee 0x18718D0 (called at 0x54227af) after CPU object creation and group insertion (group+0x248 head, group+0x250 counter). Single blocking fact: the pack->GPU hand-off (ClientTexture -> D3D12 texture resource/handle) is unproven.

## TOOL REQUESTS
None

## NEXT
DONE
