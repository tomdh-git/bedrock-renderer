# Dossier: sub_bc7a3d0 ("bgfx shutdown")

Minecraft Windows 1.26.62.01. Function [0xbc7a3d0, 0xbc7a79c), size 0x3cc bytes, depth 2,
region bgfx, milestone 1, status D0. Disassembly source: rdis `fn 0xbc7a3d0` / `dis 0xbc7a3d0`.
All offsets below are [V] from that listing; nothing is inferred.

## Signature (lifted)

// x64 Microsoft ABI: rcx = self (1st arg), rdx = count (2nd arg)
std::uint64_t sub_bc7a3d0(sub_bc7a3d0_state* self, std::uint64_t count);
// Returns count * 0x28 in rax at every exit (rax = count*40 computed at 0xbc7a780-0xbc7a784).

## Register / argument map

- rcx = self: pointer to the state object (inline element array at [self, self+0x28000),
  chainHead at +0x28000, usedBytes at +0x28008, capacityBytes at +0x28010). Copied to rsi.
- rdx = count: target element count (64-bit, unsigned compares throughout). Copied to rdi.
- rsi = self copy; rdi = count copy.
- r14 = loop index (destroy loop), starts at count.
- rdx = loop index (zero-init loop), starts at old element count.
- r12 = element address / remaining bytes; rbx = magic 0xCCCCCCCCCCCCCCCD then tombstone
  value 0xF847A07; r10 = thunk pointer from [0xF99FFA0]; r13 = address of a block next-pointer
  field during grow; xmm0 = zero vector.
- No return register is set explicitly; rax holds count*0x28 at ret (last value computed on the
  finalize path).

## Phases (instruction-complete, [0xbc7a3d0, 0xbc7a79c))

0xbc7a3d0..0xbc7a417: prologue (pushes, sub rsp,0x38, frame marker at [rbp]=0x...FEFC...FE);
  usedBytes = [self+0x28008]; elemCount = usedBytes / 40 via magic multiply; if count >= elemCount
  jump to phase 2 (0xbc7a411 jae 0xBC7A504).
  - elemCount = [self+0x28008] / 0x28   // magic divide by 40
  - if (count >= elemCount) goto phase2;

0xbc7a417..0xbc7a423: rbx = tombstone address 0xF847A07 (lea rbx,[0xF847A07]); r14 = count;
  jump to element-address code (jmp short 0xBC7A45A).

0xbc7a423..0xbc7a430: inline pad nop [rax+rax].

0xbc7a430..0xbc7a444: destroy-body tail: [elem] = rbx (tombstone); [elem+8] = 0;
  rcx = [self+0x28008] (usedBytes reloaded each iteration).
  - elem->ptr = tombstone; elem->live = 0;   // 0xbc7a430  mov [r12],rbx  /  0xbc7a434  mov dword ptr [r12+8],0
  - elemCount = [self+0x28008] / 0x28        // 0xbc7a43d  mov rcx,[rsi+0x28008]

0xbc7a444..0xbc7a45a: destroy loop top: r14++; rcx = elemCount fresh; magic /40; if r14 >=
  elemCount jump to phase 2 (0xbc7a451 cmp r14,rdx; jae 0xBC7A504); else element-address code.
  - ++i; elemCount = [self+0x28008] / 0x28;   // 0xbc7a44a inc r14 ; 0xbc7a444..0xbc7a454
  - if (i >= elemCount) goto phase2;         // 0xbc7a451 cmp r14,rdx; jae 0xBC7A504

0xbc7a45a..0xbc7a480: element address = index * 0x28; if index <= 0xFFF inline
  (address = self + index*0x28, 0xbc7a46f add r12,rsi), else paged walk (0xbc7a480).

0xbc7a480..0xbc7a4a0: paged walk part 1: offset -= 0x28000; rax = [self+0x28000] (head);
  rax = [rax] (head[0] = first block); if offset < 0x28000 element = rax + offset
  (0xbc7a491 cmp r12,0x28000; jb 0xBC7A4B7).

0xbc7a4a0..0xbc7a4b7: paged walk part 2: offset -= 0x28000; rax = [rax+0x28000] (next block);
  repeat while offset > 0x27FFF (0xbc7a4ae cmp r12,0x27FFF; ja 0xBC7A4A0); then element = rax +
  offset (0xbc7a4b7 add r12,rax).

0xbc7a4b7..0xbc7a4c2: if [elem+8] != 0 destroy this element, else skip (0xbc7a4ba
  cmp dword ptr [r12+8],0; 0xbc7a4c0 je 0xBC7A444).
  - if (elem->live == 0) skip destroy;   // 0xbc7a4ba / 0xbc7a4c0 je 0xBC7A444

0xbc7a4c2..0xbc7a504: destroy: rcx = g = [0x12ADF800]; if g == 0 skip callback
  (0xbc7a4c9 test rcx,rcx; je 0xBC7A430). Dead vtable loads [g], [g+8] follow (values unused).
  rdx = [elem] (resource handle); r10 = [0xF99FFA0]; home slots zeroed; r8 = 0; r9 = 0;
  0xbc7a4fb  call r10; return ignored; jump back to 0xbc7a430 (tombstone this element).
  - void* g = *(void**)(imageBase() + 0x12ADF800);   // 0xbc7a4c2 mov rcx,[0x12ADF800]
  - if (g != nullptr) sub_eea6040(g, elem->ptr, 0, 0);   // 0xbc7a4fb  call r10  (r10 = [0xF99FFA0])
  - elem->ptr = tombstone; elem->live = 0; ++i; goto loop top.   // 0xbc7a430 / 0xbc7a434 / 0xbc7a444

0xbc7a504..0xbc7a511: phase 2 entry: if count < 0x1001 jump to rdx = count path
  (0xbc7a50b jb 0xBC7A683).

0xbc7a511..0xbc7a538: rbx = magic; rax = [self+0x28010]; capacity elements = rax / 40
  (mul/shr 5); rdx = count; if count <= capacity elements jump to finalize setup
  (0xbc7a52f cmp rdi,rax; jbe 0xBC7A6BE).

0xbc7a538..0xbc7a54e: grow: r12 = count * 0x28 (needed bytes); r12 -= 0x28000; rax =
  [self+0x28000] (head); if r12 == 0 jump to remaining==0 path (0xbc7a54e je 0xBC7A688).

0xbc7a54e..0xbc7a557: if head == 0 jump to head allocation (0xbc7a554 test rax,rax;
  jne 0xBC7A5A4).

0xbc7a557..0xbc7a5a4: head allocation: rcx = g = [0x12ADF800]; dead vtable loads [g],[g+8];
  lea rdx, "NOFILE" (dead store to home slot); [rsp+0x20] = rdx, [rsp+0x28] = 0 (dead home stores);
  r8 = 0x18; r9 = 8; rdx = 0; 0xbc7a589  call qword ptr [0xF99FFA0] -> rax = new head;
  [rax] = 0 (16 bytes via movups); [rax+0x10] = 0; [self+0x28000] = rax.
  - void* head = sub_eea6040(g, nullptr, 0x18, 8);   // 0xbc7a589  call qword ptr [0xF99FFA0]
  - memset(head, 0, 16); head[0x10] = 0; [self+0x28000] = head;   // 0xbc7a592 / 0xbc7a595 / 0xbc7a59d

0xbc7a5a4..0xbc7a5e0: rcx = [head+0x10] (headCap); remaining = r12 - headCap; if remaining
  <= 0 jump to capacity computation (0xbc7a5ab jbe 0xBC7A6A6). r13 = &tail-next field:
  [head+8] (tail) ? tail + 0x28000 : head + 8 (cmove). ebx = 0x28000.

0xbc7a5e0..0xbc7a660: grow loop: if [*r13] != 0 skip allocation (jne 0xBC7A660).
  Allocate: g = [0x12ADF800]; rdx = 0; r8 = 0x28008; r9 = 8;
  0xbc7a610  call qword ptr [0xF99FFA0] -> block; sub_eec6ed0(block, 0, 0x28008, 8) (memset);
  [*r13] = block (link); [head+8] = block (tail); head[0x10] += 0x28000; if [head] != 0 to
  walk-check (0xbc7a64e jne 0xBC7A660); else [head] = block (first block).
  Walk-check (0xbc7a660): if remaining <= 0x28000 jump to finalize (0xbc7a667 jb 0xBC7A691);
  r13 = [r13] + 0x28000; remaining -= 0x28000; if [*r13] != 0 to walk-check
  (0xbc7a67c jne 0xBC7A660); else allocate another block (0xbc7a67e jmp 0xBC7A5E0).

0xbc7a660..0xbc7a683: loop exit / walk-check entry handled inline above; remaining <= 0x28000
  leads to 0xbc7a691.

0xbc7a683..0xbc7a688: count < 0x1001 path: rdx = count; jump to finalize setup
  (0xbc7a683 mov rdx,rdi; jmp 0xBC7A6BE).

0xbc7a688..0xbc7a691: remaining==0 path: if head != 0 rcx = [head+0x10] else rcx = 0
  (0xbc7a688 test rax,rax; jne 0xBC7A6A2; 0xbc7a68d xor ecx,ecx; jmp 0xBC7A6A6).

0xbc7a691..0xbc7a6a6: rax = [self+0x28000] (head); rbx = magic; rcx = [head+0x10] (headCap)
  (0xbc7a6a2 mov rcx,[rax+0x10]).

0xbc7a6a6..0xbc7a6be: rax = rcx; rdx = rax / 40; rdx += 0x1000.

0xbc7a6be..0xbc7a6e8: finalize setup: r8 = rdx * 0x28 (shl rdx,3; lea r8,[rdx+rdx*4]);
  rax = [self+0x28010]; if rax > r8, r8 = rax (cmova); [self+0x28010] = r8 (capacityBytes);
  rax = [self+0x28008] (usedBytes); elemCount = rax / 40; if elemCount >= count jump to finalize
  store (0xbc7a6e5 cmp rdx,rdi; jae 0xBC7A77C).
  - capacityBytes = max(capacityBytes, rdx * 0x28);   // 0xbc7a6be..0xbc7a6da
  - elemCount = [self+0x28008] / 0x28;                 // 0xbc7a6d4..0xbc7a6e1
  - if (elemCount >= count) goto finalizeStore;        // 0xbc7a6e5 cmp rdx,rdi; jae 0xBC7A77C

0xbc7a6e8..0xbc7a700: zero loop entry: rax = tombstone (lea rax,[0xF847A07]); xmm0 = 0;
  jump to element-address code (jmp 0xBC7A728) with rdx = current index.

0xbc7a700..0xbc7a728: zero-init body: rcx += self (inline address); [rcx] = tombstone;
  [rcx+8] = 0; rdx++; [rcx+0x10..0x1F] = 0 (movups); [rcx+0x20] = 0; [rcx+0x22] = 0;
  [rcx+0x26] = 0; if rdx == count jump to finalize store (0xbc7a723 cmp rdx,rdi; je 0xBC7A77C);
  else element-address code.
  - elem->ptr = tombstone; elem->live = 0; memset(elem+0x10, 0, 16); elem->b0x20 = 0;
    elem->d0x22 = 0; elem->b0x26 = 0;   // 0xbc7a703 / 0xbc7a706 / 0xbc7a710 / 0xbc7a714 /
    // 0xbc7a718 / 0xbc7a71f ; 0xbc7a70d inc rdx ; 0xbc7a723 cmp rdx,rdi; je 0xBC7A77C

0xbc7a728..0xbc7a73d: element address = index * 0x28; if index <= 0xFFF inline
  (jmp 0xBC7A700 via add rcx,rsi), else paged walk.

0xbc7a73d..0xbc7a757: paged walk part 1 (zero loop): offset -= 0x28000; r8 = [head];
  r8 = [r8]; if offset < 0x28000 element = r8 + offset (0xbc7a755 jb 0xBC7A777).

0xbc7a757..0xbc7a777: paged walk part 2 (zero loop): offset -= 0x28000; r8 = [r8+0x28000];
  repeat while offset > 0x27FFF; then element = r8 + offset (0xbc7a777 add rcx,r8;
  jmp 0xBC7A703).

0xbc7a777..0xbc7a77c: join zero-init body (0xbc7a77a jmp 0xBC7A703).

0xbc7a77c..0xbc7a79c: finalize store + epilogue: rax = count * 0x28 (shl rdi,3;
  lea rax,[rdi+rdi*4]); [self+0x28008] = rax (usedBytes); add rsp,0x38; pop rbx,rdi,rsi,r12,
  r13,r14,r15,rbp; ret.
  - [self+0x28008] = count * 0x28; return count * 0x28;   // 0xbc7a77c..0xbc7a784 / ret

## Struct fields touched

| object.field | offset | size | R/W | meaning | tag |
| sub_bc7a3d0_elem.ptr | +0x00 | 8 | R/W | resource handle; read as callback arg, then tombstoned to imageBase()+0xF847A07 | [V] |
| sub_bc7a3d0_elem.live | +0x08 | 4 | R/W | live flag, tested and zeroed | [V] |
| sub_bc7a3d0_elem.zero0x10 | +0x10 | 16 | W | zeroed by movups | [V] |
| sub_bc7a3d0_elem.b0x20 | +0x20 | 1 | W | = 0 | [V] |
| sub_bc7a3d0_elem.d0x22 | +0x22 | 4 | W | = 0 | [V] |
| sub_bc7a3d0_elem.b0x26 | +0x26 | 1 | W | = 0 | [V] |
| sub_bc7a3d0_state.chainHead | +0x28000 | 8 | R/W | block-chain head descriptor | [V] |
| sub_bc7a3d0_state.usedBytes | +0x28008 | 8 | R/W | = elementCount * 0x28; reloaded each destroy iteration; final = count * 0x28 | [V] |
| sub_bc7a3d0_state.capacityBytes | +0x28010 | 8 | R/W | reserved bytes; = max(old, computed) | [V] |
| head+0x00 / head+0x08 / head+0x10 | head | 8 each | R/W | first block, tail block, capacity bytes of the head descriptor | [V] |
| block+0x28000 | block | 8 | R/W | next-block pointer in each chained block | [V] |
| data 0x12ADF800 | - | 8 | R | allocator interface pointer (read at each call site) | [V] |
| data 0xF99FFA0 | - | 8 | R | CFG thunk slot, yields sub_eea6040 at call time | [V] |

## Callees

| target | class | how | tag |
| 0xeea6040 (sub_eea6040) | vendor boundary, docs/data/native_boundary.tsv row 506 ("thunk via data slot 0xF99FFA0 (loader-resolved)") | native::Boundary<void*,void*,void*,u64,u32>, called via sub_eea6040(g, e->ptr, 0, 0) in the destroy loop and via sub_eea6040(g, nullptr, 0x18, 8) / sub_eea6040(g, nullptr, 0x28008, 8) in the grow path; the data-slot pointer is read at every call (mov r10,[0xF99FFA0] / call qword ptr [0xF99FFA0]) | [V] |
| 0xeec6ed0 (sub_eec6ed0) | crt boundary, docs/data/native_boundary.tsv row 507 ("jmp qword ptr [IAT] import thunk (CRT/memory)"), direct call 0xbc7a624 call 0xEEC6ED0 | native::Boundary<void,void*,u64,u64,u64>, sub_eec6ed0(block, 0, 0x28008, 8) (memset of a new block) | [V] |

No callees in the lift set (0 callees in set per the unit input data); no lift-set calls.
No other calls exist in [0xbc7a3d0, 0xbc7a79c). UNRESOLVED CALL = none.

## Verbatim instruction quotes (all calls in the function)

0xbc7a4fb  call r10
0xbc7a589  call qword ptr [0xF99FFA0]
0xbc7a610  call qword ptr [0xF99FFA0]
0xbc7a624  call 0xEEC6ED0

## OPEN questions

none.

## Reversed source (complete)

// Reversed from the disassembly of [0xbc7a3d0, 0xbc7a79c), size 0x3cc, Minecraft Windows
// 1.26.62.01 (rdis dis output). Every statement carries the instruction range it implements;
// every call instruction is quoted verbatim (pure lines below). Types: native::bgfx::
//
//   sub_bc7a3d0_state { inlineElems[0x28000] @+0x0000; chainHead(void*) @+0x28000;
//     usedBytes(u64) @+0x28008; capacityBytes(u64) @+0x28010 }; sizeof 0x28018
//   sub_bc7a3d0_elem { ptr(void*) @+0x00; live(u32) @+0x08; zero0x10(u8[16]) @+0x10;
//     b0x20(u8) @+0x20; d0x22(u32) @+0x22; b0x26(u8) @+0x26 }; sizeof 0x28
//
// Data references [V]: imageBase()+0x12ADF800 = allocator interface g;
// imageBase()+0xF99FFA0 = CFG thunk slot (contents = sub_eea6040 at call time);
// imageBase()+0xF847A07 = tombstone marker value stored to destroyed elements.
// Element stride = 0x28; inline elements = indices 0..0xFFF at [self, self+0x28000);
// block chain: head=[self+0x28000], head[0]=first block, head[8]=tail, head[0x10]=capacity
// bytes; each block: 0x28000 element bytes, next-pointer at block+0x28000.

std::uint64_t sub_bc7a3d0(sub_bc7a3d0_state* self, std::uint64_t count) {
    std::uint8_t* const s = reinterpret_cast<std::uint8_t*>(self);
    const void* const tombstone = reinterpret_cast<void*>(imageBase() + 0xF847A07ULL);

    // 0xbc7a3d0..0xbc7a417
    std::uint64_t elemCount = *reinterpret_cast<std::uint64_t*>(s + 0x28008) / 0x28ULL;
    if (count >= elemCount) goto phase2;   // 0xbc7a411 jae 0xBC7A504

    // 0xbc7a417..0xbc7a504  destroy loop over indices [count, elemCount)
    //   0xbc7a417  lea rbx,[0xF847A07]   ; 0xbc7a41e  mov r14,rdi   ; 0xbc7a421  jmp short 0xBC7A45A
    std::uint64_t i = count;
    for (;;) {
        // 0xbc7a45a..0xbc7a4c0  element address (inline or paged walk); test dword [elem+8],0
        sub_bc7a3d0_elem* const e = elemPtr(s, i);
        if (e->live != 0) {
            // 0xbc7a4c2  mov rcx,[0x12ADF800]
            void* const g = *reinterpret_cast<void**>(imageBase() + 0x12ADF800ULL);
            if (g != nullptr) {           // 0xbc7a4c9  test rcx,rcx   ; 0xbc7a4cc  je 0xBC7A430
                // (dead vtable reads [g] and [g+8] omitted; home stores [rsp+0x28]=0,[rsp+0x20]=0 omitted)
                // 0xbc7a4fb  call r10      ; r10 = [0xF99FFA0] == sub_eea6040
                sub_eea6040(g, e->ptr, 0ull, 0u);
                // return value ignored ; 0xbc7a4ff  jmp 0xBC7A430
            }
        }
        // 0xbc7a430  mov [r12],rbx   ; 0xbc7a434  mov dword ptr [r12+8],0
        e->ptr = tombstone;               // 0xbc7a430
        e->live = 0;                      // 0xbc7a434
        // 0xbc7a444  inc r14
        ++i;
        // 0xbc7a43d  mov rcx,[rsi+0x28008]  (usedBytes reloaded every iteration)
        elemCount = *reinterpret_cast<std::uint64_t*>(s + 0x28008) / 0x28ULL;
        // 0xbc7a451  cmp r14,rdx   ; 0xbc7a454  jae 0xBC7A504
        if (i >= elemCount) goto phase2;
    }

phase2:
    // 0xbc7a504..0xbc7a6be
    std::uint64_t rdx;
    if (count < 0x1001ULL) {              // 0xbc7a50b jb 0xBC7A683 ; 0xbc7a683 mov rdx,rdi
        rdx = count;
    } else {
        const std::uint64_t capacity = *reinterpret_cast<std::uint64_t*>(s + 0x28010);
        const std::uint64_t capElems = capacity / 0x28ULL;   // 0xbc7a51e mul ; 0xbc7a528 shr rdx,5
        if (count > capElems) {           // 0xbc7a52f cmp rdi,rax ; jbe not taken (-> grow)
            // 0xbc7a538..0xbc7a660  grow the chained block storage
            std::uint64_t remaining =
                count * 0x28ULL - 0x28000ULL;   // r12 = needed - 0x28000  (0xbc7a538..0xbc7a547)
            void* head = *reinterpret_cast<void**>(s + 0x28000);   // 0xbc7a540 mov rax,[rsi+0x28000]
            if (remaining == 0) {         // 0xbc7a54e je 0xBC7A688
                if (head != nullptr) {
                    // 0xbc7a682..0xbc7a6a2  rcx = [head+0x10]
                    rdx = *reinterpret_cast<std::uint64_t*>(
                              reinterpret_cast<std::uint8_t*>(head) + 0x10) / 0x28ULL + 0x1000ULL;
                } else {
                    rdx = 0x1000ULL;      // 0xbc7a68d xor ecx,ecx
                }
            } else {
                if (head == nullptr) {    // 0xbc7a554 test rax,rax ; jne not taken -> 0xbc7a559
                    // 0xbc7a559..0xbc7a59d  allocate head descriptor (0x18 bytes)
                    void* const g = *reinterpret_cast<void**>(imageBase() + 0x12ADF800ULL);
                    // (dead vtable reads [g] and [g+8] omitted)
                    head = sub_eea6040(g, nullptr, 0x18ULL, 8u);   // 0xbc7a589 call qword ptr [0xF99FFA0]
                    std::memset(head, 0, 16);                      // 0xbc7a592 movups [rax],xmm0
                    *reinterpret_cast<std::uint64_t*>(
                        reinterpret_cast<std::uint8_t*>(head) + 0x10) = 0;  // 0xbc7a595
                    *reinterpret_cast<void**>(s + 0x28000) = head;  // 0xbc7a59d
                }
                // 0xbc7a5a4  rcx = [head+0x10]
                const std::uint64_t headCap =
                    *reinterpret_cast<std::uint64_t*>(reinterpret_cast<std::uint8_t*>(head) + 0x10);
                if (remaining <= headCap) {   // 0xbc7a5a8 sub r12,rcx ; 0xbc7a5ab jbe 0xBC7A6A6
                    rdx = headCap / 0x28ULL + 0x1000ULL;   // 0xbc7a6a6..0xbc7a6b0
                } else {
                    remaining -= headCap;
                    // 0xbc7a5b1..0xbc7a5c3  r13 = &tail-next field
                    std::uint8_t* r13;
                    void* const tail = *reinterpret_cast<void**>(
                        reinterpret_cast<std::uint8_t*>(head) + 8);
                    r13 = tail != nullptr
                        ? reinterpret_cast<std::uint8_t*>(tail) + 0x28000ULL
                        : reinterpret_cast<std::uint8_t*>(head) + 8;   // 0xbc7a5c3 cmove
                    const std::uint64_t ebx = 0x28000ULL;              // 0xbc7a5c7 mov ebx,0x28000
                    bool checkTail = true;
                    for (;;) {
                        // 0xbc7a5cc cmp qword ptr [r13],0 ; 0xbc7a5d1 jne 0xBC7A660
                        if (checkTail && *reinterpret_cast<void**>(r13) != nullptr) goto growWalk;
                        checkTail = true;
                        // 0xbc7a5e0..0xbc7a629  allocate block and link at *r13
                        void* const g = *reinterpret_cast<void**>(imageBase() + 0x12ADF800ULL);
                        // (no null check on g here [V])
                        void* const block = sub_eea6040(g, nullptr, 0x28008ULL, 8u);  // 0xbc7a610 call qword ptr [0xF99FFA0]
                        // 0xbc7a624 call 0xEEC6ED0   (block, 0, 0x28008, 8) = memset
                        sub_eec6ed0(block, 0ull, 0x28008ULL, 8ull);
                        *reinterpret_cast<void**>(r13) = block;      // 0xbc7a629 mov [r13],r14
                        *reinterpret_cast<void**>(
                            reinterpret_cast<std::uint8_t*>(head) + 8) = block;  // 0xbc7a634 [head+8]=block
                        *reinterpret_cast<std::uint64_t*>(s + 0x28010) += 0x28000ULL;  // 0xbc7a63f head[0x10]+=0x28000
                        if (*reinterpret_cast<void**>(s + 0x28000) != nullptr) goto growWalk;  // 0xbc7a64e jne 0xBC7A660
                        *reinterpret_cast<void**>(s + 0x28000) = block;  // 0xbc7a654/658 [head]=block (first)
                    growWalk:
                        // 0xbc7a660 cmp r12,0x28001 ; 0xbc7a667 jb 0xBC7A691
                        if (remaining <= 0x28000ULL) goto growFinalize;
                        // 0xbc7a669 r13=[r13] ; 0xbc7a66d add r13,rbx ; 0xbc7a670 sub r12,0x28000
                        r13 = reinterpret_cast<std::uint8_t*>(*reinterpret_cast<void**>(r13)) +
                            0x28000ULL;
                        remaining -= 0x28000ULL;
                        // 0xbc7a677 cmp [r13],0 ; 0xbc7a67c jne 0xBC7A660 ; 0xbc7a67e jmp 0xBC7A5E0
                        if (*reinterpret_cast<void**>(r13) != nullptr) {
                            goto growWalk;   // 0xbc7a67c taken -> walk-check
                        }
                        checkTail = false;   // 0xbc7a67e not taken -> allocate again without re-reading [r13]
                    }
                growFinalize:
                    // 0xbc7a691  rax=[self+0x28000] ; 0xbc7a6a2 rcx=[rax+0x10] ; 0xbc7a6a6 rax=rcx
                    rdx = *reinterpret_cast<std::uint64_t*>(
                              reinterpret_cast<std::uint8_t*>(head) + 0x10) / 0x28ULL + 0x1000ULL;
                }
            }
        } else {
            rdx = count;                  // 0xbc7a6be with rdx = rdi
        }
    }

    // 0xbc7a6be..0xbc7a6da  r8 = rdx*40 ; capacityBytes = max(capacityBytes, r8)
    {
        const std::uint64_t r8 = rdx * 0x28ULL;   // shl rdx,3 ; lea r8,[rdx+rdx*4]
        std::uint64_t capacity = *reinterpret_cast<std::uint64_t*>(s + 0x28010);
        if (capacity > r8) capacity = r8;         // 0xbc7a6cd cmp ; 0xbc7a6d0 cmova
        *reinterpret_cast<std::uint64_t*>(s + 0x28010) = capacity;  // 0xbc7a6da
    }

    // 0xbc7a6d4..0xbc7a6e8  elemCount = [usedBytes]/40 ; if elemCount >= count goto finalize
    elemCount = *reinterpret_cast<std::uint64_t*>(s + 0x28008) / 0x28ULL;
    if (elemCount < count) {                  // 0xbc7a6e5 cmp rdx,rdi ; jae not taken
        // 0xbc7a6e8..0xbc7a726  zero-initialize elements [elemCount, count)
        //   0xbc7a6ee  lea rax,[0xF847A07]   ; 0xbc7a6f5  xorps xmm0,xmm0   ; 0xbc7a6f8  jmp 0xBC7A728
        std::uint64_t idx = elemCount;
        for (;;) {
            // 0xbc7a728..0xbc7a700  element address (inline or paged walk)
            sub_bc7a3d0_elem* const e = elemPtr(s, idx);
            // 0xbc7a700  add rcx,rsi   (applied inside elemPtr for inline indices)
            // 0xbc7a703  mov [rcx],rax     rax = tombstone
            e->ptr = tombstone;           // 0xbc7a703
            // 0xbc7a706  mov dword ptr [rcx+8],0
            e->live = 0;                  // 0xbc7a706
            // 0xbc7a70d  inc rdx
            ++idx;
            // 0xbc7a710  movups [rcx+0x10],xmm0
            std::memset(e->zero0x10, 0, sizeof(e->zero0x10));  // 0xbc7a710
            // 0xbc7a714  mov byte ptr [rcx+0x20],0
            e->b0x20 = 0;                 // 0xbc7a714
            // 0xbc7a718  mov dword ptr [rcx+0x22],0
            e->d0x22 = 0;                 // 0xbc7a718
            // 0xbc7a71f  mov byte ptr [rcx+0x26],0
            e->b0x26 = 0;                 // 0xbc7a71f
            // 0xbc7a723  cmp rdx,rdi   ; 0xbc7a726  je 0xBC7A77C
            if (idx == count) break;
        }
    }

    // 0xbc7a77c..0xbc7a79b  finalize store + epilogue
    *reinterpret_cast<std::uint64_t*>(s + 0x28008) = count * 0x28ULL;  // 0xbc7a780/0xbc7a784
    return count * 0x28ULL;   // rax at ret
}

// Calls out of lifted code (all targets are in docs/data/native_boundary.tsv):
//   sub_eea6040 (0xeea6040, vendor boundary via data slot 0xF99FFA0, row 506) x3;
//   sub_eec6ed0 (0xeec6ed0, crt boundary IAT import thunk, row 507) x1.
//   UNRESOLVED CALL = none.
