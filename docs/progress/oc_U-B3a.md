# UNIT U-B3a — D3D12 submit stage map by callees: draw executor / submit function 0xe82e230 (BGFX_MAP 6t, 6af; slot 50)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

## NEXT
Resume at: run `python tools/sigs/verify_oc.py docs/progress/oc_U-B3a.md` to validate every quoted `0xRVA  instr` line; then finalize unit.

## (1) `rdis fn 0xe82e230` size; register map at entry

`rdis fn 0xe82e230 --max 300` (listing saved to docs/progress/oc_U-B3a_fn.txt, full listing to docs/progress/oc_U-B3a_listing.txt):
- `sub_e82e230  [0xe82e230..0xe832fc1)  size 0x4d91  1 xrefs in` ([V] rdis fn output header). [I] 0x4d91 = 19,881 bytes.
- Confirmed by BGFX_MAP.md 6t/line 410: "slot 50 ... `0xe82e230` submit (0x4d91 bytes, 227 calls)" [V static].

Entry register map (quoted verbatim from listing, first instructions):
```
e82e230  push rbp                                      
e82e231  push r15                                      
e82e233  push r14                                      
e82e235  push r13                                      
e82e237  push r12                                      
e82e239  push rsi                                      
e82e23a  push rdi                                      
e82e23b  push rbx                                      
e82e23c  mov eax,0x1778                                ; stack-probe size
e82e241  call 0xE9E7970                                ; -> sub_e9e7970 (__chkstk-style stack probe)
e82e246  sub rsp,rax                                   ; allocate 0x1778-byte frame
e82e249  lea rbp,[rsp+0x80]                            ; rbp = frame base
e82e251  movapd [rbp+0x16E0],xmm7                      ; save xmm7
e82e259  movapd [rbp+0x16D0],xmm6                      ; save xmm6
e82e261  mov qword ptr [rbp+0x16C8],0xFFFFFFFFFFFFFFFE ; stack cookie canary slot
e82e26c  mov [rbp+0x16A8],rdx                          ; [rbp+0x16A8] = rdx = Frame*
e82e273  cmp dword ptr [rcx+0x19F88],5                 ; rcx = RendererContext* this; renderer-state guard
```

- `rcx` = arg1 = `RendererContext*` this (saved to rdi at e82e280, to [rbp+0x16C0] at e82e2d4) [V]
- `rdx` = arg2 = `Frame*` (saved to [rbp+0x16A8] at e82e26c; per BGFX_MAP 6b `submit(rcx=RendererContext, rdx=Frame*, r8, r9)`) [V]
- `r8`, `r9` = arg3, arg4 = two small helper objects (clear-quad / text blitter style) [I per BGFX_MAP 6b]
- `rsi` at e82e2a1 = r9 (reloaded for the slot-60 virtual call) [V]
- Callee-saved registers preserved: rbx, rbp, rsi, rdi, r12, r13, r14, r15, xmm6, xmm7 (pushed at entry) [V]

Stack frame: 0x1778 bytes (0x1778 = 6008) probed via `mov eax,0x1778; call 0xe9e7970; sub rsp,rax` [V]. Cookie at [rbp+0x16C8] / check `mov rax,[0x1230A0C0]` pattern (cookie verify at epilog, see 0xe832cee/0xe832d54/0xe832da4/0xe832def region tails) [V].

Signature guess: `void submit(RendererContext* this /*rcx*/, Frame* frame /*rdx*/, void* r8, void* r9)` — rcx/rdx seen at entry; r8/r9 unused directly at entry but present per BGFX_MAP 6b. [I]

[UNVERIFIED: 0xe82e230 exact names of r8/r9 args; not referenced at entry within the first 40 instructions]

## (2) Every distinct callee in order of first call

Source: `rdis callees 0xe82e230` (docs/progress/oc_U-B3a_callees.txt) gives count per direct `call 0x...` target; first-call site and quoted instruction from `rdis fn` listing (docs/progress/oc_U-B3a_fn.txt, decoded utf-16). IAT thunks `call qword ptr [0xF9XXXXXX]` resolved per site; 0xF99FFA0 -> sub_eea6040 ([V] per U-B7b `jmp rax` thunk). Other IAT entries not resolved [UNVERIFIED].

Counts: direct `call 0x...` total 154 (sum of `rdis callees` counts). IAT `call qword ptr [0xF99FFA0]` x65 (sites incl. e82e2a4, e82e434, ...); `call qword ptr [0xF9A7B68]` x1 (e82e7fb); `call qword ptr [0xF9A9110]` x1 (e831fbb); `call qword ptr [0xF9A8C78]` x1 (e832d2e). [V count from listing]

| # | Callee RVA | Count | First site | Quoted call | Identification | Tag |
|---|------------|-------|------------|-------------|----------------|-----|
| 1 | 0xe9e7970 | 1 | 0xe82e241 | `e82e241  call 0xE9E7970  ; -> sub_e9e7970` | Stack probe (__chkstk-style): `mov eax,0x1778; call; sub rsp,rax` allocates the 0x1778-byte frame | [V] |
| 2 | 0xf99ffa0 (IAT -> sub_eea6040) | 65 | 0xe82e2a4 | `e82e2a4  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040` | Import thunk -> `sub_eea6040` = single `jmp rax`; D3D12 command-list wrapper emission (barrier/draw) | [V IAT->eea6040 per U-B7b] |
| 3 | 0xebdb740 | 2 | 0xe82e332 | `e82e332  call 0xEBDB740  ; -> sub_ebdb740` | QPC timestamp read (per BGFX_MAP 6ac/753 render-thread wait timing) | [V] per 753 |
| 4 | 0xe81d660 | 1 | 0xe82e367 | `e82e367  call 0xE81D660  ; -> sub_e81d660` | Frame begin / state reset (0x1af) | [V] per 6t |
| 5 | 0xe8360f0 | 3 | 0xe82e4b0 | `e82e4b0  call 0xE8360F0  ; -> sub_e8360f0` | Descriptor / upload ring begin (0x3f6), x3 | [V] per 6t |
| 6 | 0xeec6ec0 | 2 | 0xe82e534 | `e82e534  call 0xEEC6EC0  ; -> sub_eec6ec0` | Block-copy primitive (0xebce390 jmp's to it); per-handle record copy at e82e534 | [I] |
| 7 | 0xbc61e20 | 1 | 0xe82e781 | `e82e781  call 0xBC61E20  ; -> sub_bc61e20` | bgfx `Frame::sort` / view+frame prep (0x215) | [V] functions.tsv L8 + 6t |
| 8 | 0xf9a7b68 (IAT) | 1 | 0xe82e7fb | `e82e7fb  call qword ptr [0xF9A7B68]` | IAT thunk; callee not resolved | [UNVERIFIED: 0xe82e7fb target of IAT 0xF9A7B68] |
| 9 | 0xe818490 | 3 | 0xe82e84d | `e82e84d  call 0xE818490  ; -> sub_e818490` | Per-view setup: viewport/scissor/RT bind (0x4e6), x3 | [V] per 6t |
| 10 | 0xe820910 | 1 | 0xe82ea43 | `e82ea43  call 0xE820910  ; -> sub_e820910` | Clear / RT transitions (0x80c) | [V] per 6t |
| 11 | 0x45eb70 | 1 | 0xe82ea62 | `e82ea62  call 0x45EB70` | Small helper adjacent to 0x45eb90; role not decoded | [?] |
| 12 | 0x45eb90 | 1 | 0xe82ea81 | `e82ea81  call 0x45EB90` | Small helper; role not decoded | [?] |
| 13 | 0xe83b3d0 | 2 | 0xe82ec19 | `e82ec19  call 0xE83B3D0  ; -> sub_e83b3d0` | Role not given in 6t (0x3d0) | [?] |
| 14 | 0x35e44a0 | 1 | 0xe82ef16 | `e82ef16  call 0x35E44A0` | Role not decoded | [?] |
| 15 | 0xbc5f110 | 4 | 0xe82f285 | `e82f285  call 0xBC5F110  ; -> sub_bc5f110` | Semaphore release/wait; also the guarded-array out-of-bounds error reporter (reports "FAILED: accessing a guarded paged heap backed array out of bounds.") | [V] per 6t + 539 |
| 16 | 0xe815590 | 1 | 0xe82f645 | `e82f645  call 0xE815590  ; -> sub_e815590` | Render target resolve (0x2af) | [V] per 6t |
| 17 | 0xa4ec0 | 1 | 0xe82f88d | `e82f88d  call 0xA4EC0` | Role not decoded | [?] |
| 18 | 0x1195a0 | 1 | 0xe82fbff | `e82fbff  call 0x1195A0` | Role not decoded | [?] |
| 19 | 0x9bc830 | 4 | 0xe82fcf1 | `e82fcf1  call 0x9BC830` | Role not decoded | [?] |
| 20 | 0xeec6de0 | 6 | 0xe82fd75 | `e82fd75  call 0xEEC6DE0  ; -> sub_eec6de0` | Copy/memcpy helper (0x141 family) | [I] |
| 21 | 0xe935700 | 7 | 0xe82fddc | `e82fddc  call 0xE935700  ; -> sub_e935700` | Role not decoded; also referenced from 0x75b60 vector-too-long path | [?] |
| 22 | 0xeec6ed0 | 6 | 0xe830698 | `e830698  call 0xEEC6ED0  ; -> sub_eec6ed0` | Copy helper | [I] |
| 23 | 0x120e00 | 2 | 0xe830807 | `e830807  call 0x120E00` | Role not decoded | [?] |
| 24 | 0xeec59f0 | 3 | 0xe830ab6 | `e830ab6  call 0xEEC59F0  ; -> sub_eec59f0` | IAT thunk `jmp qword ptr [0xF9A75A8]`; mutex/sync (per 772 slot 61 locks this+0x3C563C0 via 0xeec59f0/0xeec5a10) | [I] |
| 25 | 0xeec5a10 | 3 | 0xe830c11 | `e830c11  call 0xEEC5A10  ; -> sub_eec5a10` | IAT thunk `jmp qword ptr [0xF9A75B8]`; mutex/sync (unlock side) | [I] |
| 26 | 0xe83abb0 | 3 | 0xe830f2b | `e830f2b  call 0xE83ABB0  ; -> sub_e83abb0` | Guarded paged-array bounds/guard check (0x12f) | [V] per 579 + 6t |
| 27 | 0xe82d960 | 2 | 0xe8311b7 | `e8311b7  call 0xE82D960  ; -> sub_e82d960` | Resource state-transition helper / tracker (0x359); unit U-B7b | [V] per 579 + functions.tsv L26 |
| 28 | 0xebd1560 | 1 | 0xe83146b | `e83146b  call 0xEBD1560  ; -> sub_ebd1560` | Role not decoded | [?] |
| 29 | 0xebce5e0 | 1 | 0xe8316fc | `e8316fc  call 0xEBCE5E0  ; -> sub_ebce5e0` | Adjacent to memcpy family (0xebce390 jmp's to eec6ec0); likely copy/mem | [I] |
| 30 | 0xebce650 | 1 | 0xe831724 | `e831724  call 0xEBCE650  ; -> sub_ebce650` | Role not decoded | [?] |
| 31 | 0xe81af20 | 1 | 0xe83189f | `e83189f  call 0xE81AF20  ; -> sub_e81af20` | Root-sig/heap binding; slot 61 executes current command list via 0xe81af20 (per 772) | [V] per 772 + 6t |
| 32 | 0x38a1520 | 10 | 0xe8318b1 | `e8318b1  call 0x38A1520  ; -> sub_38a1520` | OR-combines fields [rcx+0x0..0x128] of a 0x130-byte block (state/hash combine over a record); called 10x (hot) | [I] from disassembly (dis 0x38a1520 40) |
| 33 | 0xe81ac80 | 2 | 0xe8318c5 | `e8318c5  call 0xE81AC80  ; -> sub_e81ac80` | Root-sig/heap binding; slot 61 opens next command list via 0xe81ac80 (per 772) | [V] per 772 + 6t |
| 34 | 0xe833210 | 2 | 0xe8318fa | `e8318fa  call 0xE833210  ; -> sub_e833210` | Per-draw record build (0xde4), the biggest helper | [V] per 6t |
| 35 | 0xe81d850 | 1 | 0xe831cdd | `e831cdd  call 0xE81D850  ; -> sub_e81d850` | Frame end / present prep (0x1cd) | [V] per 6t |
| 36 | 0xebdb760 | 2 | 0xe831d73 | `e831d73  call 0xEBDB760  ; -> sub_ebdb760` | QPC timestamp (pair with 0xebdb740) | [V] |
| 37 | 0xebce390 | 1 | 0xe831e1d | `e831e1d  call 0xEBCE390  ; -> sub_ebce390` | `jmp 0xEEC6EC0` then loop calling eec6ec0 = block memcpy (0x40-byte copy helper per 1116) | [V] dis 0xebce390 |
| 38 | 0xebce430 | 1 | 0xe831f53 | `e831f53  call 0xEBCE430  ; -> sub_ebce430` | Role not decoded | [?] |
| 39 | 0xe800c10 | 21 | 0xe831fa2 | `e831fa2  call 0xE800C10  ; -> sub_e800c10` | D3D12 command wrapper (0x58), 21 emission sites (barriers/draws/dispatches) | [V] per 6t |
| 40 | 0xf9a9110 (IAT) | 1 | 0xe831fbb | `e831fbb  call qword ptr [0xF9A9110]` | IAT thunk; callee not resolved | [UNVERIFIED: 0xe831fbb target of IAT 0xF9A9110] |
| 41 | 0xebcf580 | 12 | 0xe832000 | `e832000  call 0xEBCF580  ; -> sub_ebcf580` | Copy/memcpy helper (0x141) | [I] per 6t |
| 42 | 0xed35e10 | 1 | 0xe83204e | `e83204e  call 0xED35E10  ; -> sub_ed35e10` | Role not decoded | [?] |
| 43 | 0xbc5fce0 | 1 | 0xe832698 | `e832698  call 0xBC5FCE0  ; -> sub_bc5fce0` | Role not decoded | [?] |
| 44 | 0xe834040 | 1 | 0xe83287f | `e83287f  call 0xE834040  ; -> sub_e834040` | Role not given in 6t (0x1a3) | [?] |
| 45 | 0xe83b0e0 | 1 | 0xe8328bd | `e8328bd  call 0xE83B0E0  ; -> sub_e83b0e0` | Tracker first-use (0x11c); unit U-B7b tail-call target | [V] per 579 |
| 46 | 0xe83aed0 | 4 | 0xe8328f6 | `e8328f6  call 0xE83AED0  ; -> sub_e83aed0` | Paged-array element getter / descriptor copy (0x201) | [V] per 579 + 6t |
| 47 | 0xe81b3b0 | 1 | 0xe832cd3 | `e832cd3  call 0xE81B3B0  ; -> sub_e81b3b0` | Role not given in 6t (0x118) | [?] |
| 48 | 0x1a2800 | 2 | 0xe832d10 | `e832d10  call 0x1A2800` | Role not decoded | [?] |
| 49 | 0xeec59e0 | 1 | 0xe832d16 | `e832d16  call 0xEEC59E0  ; -> sub_eec59e0` | IAT-thunk-family sync helper | [I] |
| 50 | 0xf9a8c78 (IAT) | 1 | 0xe832d2e | `e832d2e  call qword ptr [0xF9A8C78]` | IAT thunk; callee not resolved | [UNVERIFIED: 0xe832d2e target of IAT 0xF9A8C78] |
| 51 | 0xe938cb0 | 8 | 0xe832d5e | `e832d5e  call 0xE938CB0  ; -> sub_e938cb0` | TLS trace scope (pair with 0xe938d70) | [V] per 6t |
| 52 | 0xe938d70 | 8 | 0xe832d90 | `e832d90  call 0xE938D70  ; -> sub_e938d70` | TLS trace scope (pair with 0xe938cb0) | [V] per 6t |
| 53 | 0xeec5a00 | 6 | 0xe832f3b | `e832f3b  call 0xEEC5A00  ; -> sub_eec5a00` | IAT thunk `jmp qword ptr [0xF9A72F0]`; sync/error | [I] |
| 54 | 0x75740 | 4 | 0xe832f7c | `e832f7c  call 0x75740` | STL length-error helper ("bad array new length"; size 0x2000, 11080 xrefs) | [V] dis 0x75740 |
| 55 | 0x75b60 | 1 | 0xe832fae | `e832fae  call 0x75B60` | STL length-error helper ("vector too long"; size 0x2000, 6017 xrefs) | [V] dis 0x75b60 |

Strings referenced inside 0xe82e230 (from `rdis callees` str output; `xref.py str` confirms these live in the function range e82e230..e832fc1):
- `e82f27e` "TLAS isn't big enough.  But you said it was as big as it wou..." (RTX TLAS overflow assert; per 959 lives in submit slot 50)
- `e82f638` "LBLAS"
- `e830f4c` / `e831091` / `e83295e` "FAILED: accessing a guarded paged heap backed array out of b..." (guarded-array bounds error; reported via 0xbc5f110)
- `e831f8b` " %s (FL %d.%d) / Clang 22.1.5 / x86 / 64-bit / Windows "
- `e831fc6` " Device: %s"
- `e832084` " Memory: %s (video), %s (system), %s (shared), %s (process) "
- `e83212e` "Local    "
- `e83213a` "   %s - Budget: %10s, Usage: %10s, AvailRes: %10s, CurrRes: %10s" (DXGI QueryVideoMemoryInfo)
- `e8321cf` "Non-local"
- `e832302` " Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
- `e83235b` " Submitted: %5d (draw %5d, compute %4d) / CPU %7.4f [ms] "
- `e832399` "Triangles", `e8323a5` "   %9s: %7d (#inst: %5d), submitted: %7d ", `e8323e3` "TriStrip", `e832426` "Lines", `e832469` "LineStrip", `e8324ac` "Points"
- `e8324e5` " [F11 - RenderDoc capture] "
- `e832509` "      Indices: %7d ", `e83253a` "     DVB size: %7d ", `e83256b` "     DIB size: %7d "
- `e832599` "     Capture: %7.4f [ms] ", `e8325f7` " Submit wait: %7.4f [ms] ", `e832636` " Render wait: %7.4f [ms] "
(Per 6dh: bgfx debug overlay/timing strings; drawn only when BGFX_DEBUG_STATS/TEXT set.)

[UNVERIFIED: 0xe82e230 ~70 indirect COM calls referenced by 6t ("through [rip+..]") — the listing shows `call qword ptr [0xF9XXXXXX]` IAT thunks (4 entries, 68 sites total) and no obvious `call qword ptr [reg+off]` vtable COM calls inside the body; reconcile with 6t's "70 indirect calls".]

## (3) Stage map — split into stages in address order

Boundary instructions quoted verbatim from listing. Stage ranges are approximate (function is one linear body; splits chosen at calls/major branches). Tags [V] = boundary instruction seen at that RVA, [I] = stage grouping/meaning inferred. `e82e230..e832fc1` full range [V size].

| Stage | Address range | Boundary instruction (start -> end) | One-line meaning | Tag |
|-------|---------------|-------------------------------------|------------------|-----|
| S0 Prologue / stack probe | 0xe82e230..0xe82e26c | `e82e230  push rbp` -> `e82e26c  mov [rbp+0x16A8],rdx` | Push callee-saved regs, `__chkstk`-style probe `mov eax,0x1778; call 0xe9e7970; sub rsp,rax`, set frame base rbp, save Frame* to [rbp+0x16A8] | [V] |
| S1 Renderer-state guard + slot-60 reset | 0xe82e273..0xe82e2af | `e82e273  cmp dword ptr [rcx+0x19F88],5` -> `e82e2af  jne 0xE832CEE` | If renderer state <5 skip; else if `[this+0x2D8]!=0` call virtual +0x1E0 (slot 60 reset) with rdx=Frame+0xDC5808 (backbuffer size); abort submit if reset needed | [V] per 6dn |
| S2 Frame timer / QPC | 0xe82e2b5..0xe82e330 | `e82e2b5  mov eax,[0x12BB4948]` (x3 TLS/gcs blocks) -> `e82e332  call 0xEBDB740` | QPC timestamp reads via gs:[0x58] TLS + `call 0xebdb740` | [V] per 753 |
| S3 Frame begin / state reset | 0xe82e332..0xe82e372 | `e82e332  call 0xEBDB740` -> `e82e372  cmp dword ptr [rsi+0xDC57F0],0` | `call 0xe81d660` at e82e367 (frame begin/state reset), then read frame counter `r9d=[rsi+0xE746D8]` and resource-table ptr `[rdi+0x19F58]` | [V] per 6t |
| S4 Transient index-buffer guard | 0xe82e372..0xe82e468 | `e82e372  cmp dword ptr [rsi+0xDC57F0],0` -> `e82e468  movzx eax,word ptr [rsi+0x10]` | If transient IB size !=0: validate handle via guarded array (`[rax+rdx*8+0x48]` bitmap, `bt r8,rcx`), set state dword to 0x400, emit one barrier via `call qword ptr [0xF99FFA0]` (NumBarriers=1) at e82e434 | [V] |
| S5 Descriptor / upload ring begin | 0xe82e468..0xe82e4b5 | `e82e468  movzx eax,word ptr [rsi+0x10]` -> `e82e4b0  call 0xE8360F0` | `call 0xe8360f0` (upload ring allocator, 0x3f6) | [V] per 6t |
| S6 Per-handle record + command-list setup | 0xe82e4b5..0xe82e569 | `e82e4b5  mov r13d,[rbp+0x7F0]` -> `e82e563  call qword ptr [0xF99FFA0]` | Refcount/decref per-handle record (`lock dec [r12+8]`, release via thunk), then `call qword ptr [0xF99FFA0]` cmdlist op with r8=&desc | [V] |
| S7 bgfx Frame::sort / view prep | 0xe82e569..0xe82e84d | `e82e569  mov rax,[rbp+0x16A8]` -> `e82e84d  call 0xE818490` | `call 0xbc61e20` (Frame::sort, 0x215) at e82e781; then sort-based view/frame preparation | [V] functions.tsv L8 + 6t |
| S8 Per-view setup x3 | 0xe82e84d..0xe82ea43 | `e82e84d  call 0xE818490` -> `e82ea43  call 0xE820910` | `call 0xe818490` x3 (viewport/scissor/RT bind, 0x4e6 each) | [V] per 6t |
| S9 Clear / RT transitions | 0xe82ea43..0xe82e84d(next) | `e82ea43  call 0xE820910` -> `e82ec19  call 0xE83B3D0` | `call 0xe820910` (clear/RT transitions, 0x80c) | [V] per 6t |
| S10 Small helpers 0x45eb70/0x45eb90 | 0xe82ea62..0xe82ec19 | `e82ea62  call 0x45EB70`; `e82ea81  call 0x45EB90` | Two small helpers (roles not decoded) | [?] |
| S11 0xe83b3d0 x2 | 0xe82ec19..0xe82ef16 | `e82ec19  call 0xE83B3D0` -> `e82ef16  call 0x35E44A0` | `call 0xe83b3d0` x2 (0x3d0); role not given in 6t | [?] |
| S12 0x35e44a0 | 0xe82ef16..0xe82f285 | `e82ef16  call 0x35E44A0` -> `e82f285  call 0xBC5F110` | Small helper; role not decoded | [?] |
| S13 Semaphore 0xbc5f110 | 0xe82f285..0xe82f645 | `e82f285  call 0xBC5F110` -> `e82f645  call 0xE815590` | `call 0xbc5f110` (semaphore release/wait / OOB-error reporter) | [V] per 6t + 539 |
| S14 Render-target resolve | 0xe82f645..0xe82f88d | `e82f645  call 0xE815590` -> `e82f88d  call 0xA4EC0` | `call 0xe815590` (RT resolve, 0x2af) | [V] per 6t |
| S15 Small helpers 0xa4ec0/0x1195a0/0x9bc830 | 0xe82f88d..0xe82fd75 | `e82f88d  call 0xA4EC0`; `e82fbff  call 0x1195A0`; `e82fcf1  call 0x9BC830` | Three small helpers; roles not decoded | [?] |
| S16 Copy helpers 0xeec6de0/0xe935700/0xeec6ed0 | 0xe82fd75..0xe830807 | `e82fd75  call 0xEEC6DE0`; `e82fddc  call 0xE935700`; `e830698  call 0xEEC6ED0`; `e830807  call 0x120E00` | Copy/memcpy + TLS/misc helpers | [I] |
| S17 Mutex lock/unlock 0xeec59f0/0xeec5a10 | 0xe830ab6..0xe830f2b | `e830ab6  call 0xEEC59F0`; `e830c11  call 0xEEC5A10` -> `e830f2b  call 0xE83ABB0` | Lock (0xeec59f0) ... unlock (0xeec5a10) around guarded-array access | [I] per 772 |
| S18 Guarded paged-array check 0xe83abb0 | 0xe830f2b..0xe8311b7 | `e830f2b  call 0xE83ABB0` -> `e8311b7  call 0xE82D960` | `call 0xe83abb0` (bounds/guard check on resource table) | [V] per 579 + 6t |
| S19 Tracker state transition 0xe82d960 x2 | 0xe8311b7..0xe83189f | `e8311b7  call 0xE82D960` -> `e83189f  call 0xE81AF20` | `call 0xe82d960` x2 (tracker transition, 0x359; U-B7b) interleaved with small helpers 0xebd1560/0xebce5e0/0xebce650 | [V] per 579 |
| S20 Root-sig/heap binding 0xe81af20/0xe81ac80 | 0xe83189f..0xe8318fa | `e83189f  call 0xE81AF20`; `e8318c5  call 0xE81AC80` -> `e8318fa  call 0xE833210` | Execute current command list (0xe81af20) / open next list (0xe81ac80) [V per 772]; state-combine 0x38a1520 x10 at e8318b1 | [V] per 772 |
| S21 Per-draw record build 0xe833210 x2 | 0xe8318fa..0xe831cdd | `e8318fa  call 0xE833210` -> `e831cdd  call 0xE81D850` | `call 0xe833210` x2 (per-draw record build, 0xde4, biggest helper) | [V] per 6t |
| S22 Frame end / present prep | 0xe831cdd..0xe831d73 | `e831cdd  call 0xE81D850` -> `e831d73  call 0xEBDB760` | `call 0xe81d850` (frame end/present prep, 0x1cd) | [V] per 6t |
| S23 QPC + memcpy 0xebce390 | 0xe831d73..0xe831fa2 | `e831d73  call 0xEBDB760`; `e831e1d  call 0xEBCE390`; `e831f53  call 0xEBCE430` -> `e831fa2  call 0xE800C10` | QPC end timestamp + block memcpy (0xebce390 -> eec6ec0) | [V] |
| S24 D3D12 command wrapper 0xe800c10 x21 | 0xe831fa2..0xe832698 | `e831fa2  call 0xE800C10` -> `e832698  call 0xBC5FCE0` | `call 0xe800c10` x21 (command wrapper emission: barriers/draws/dispatches) interleaved with copy helpers 0xebcf580 x12 | [V] per 6t |
| S25 0xbc5fce0 | 0xe832698..0xe83287f | `e832698  call 0xBC5FCE0` -> `e83287f  call 0xE834040` | Small helper; role not decoded | [?] |
| S26 0xe834040 | 0xe83287f..0xe8328bd | `e83287f  call 0xE834040` -> `e8328bd  call 0xE83B0E0` | Helper (0x1a3); role not given in 6t | [?] |
| S27 Tracker firstUse 0xe83b0e0 + descriptor copy 0xe83aed0 | 0xe8328bd..0xe832cd3 | `e8328bd  call 0xE83B0E0`; `e8328f6  call 0xE83AED0` -> `e832cd3  call 0xE81B3B0` | `call 0xe83b0e0` (tracker first-use, 0x11c) + `call 0xe83aed0` x4 (paged-array element getter / descriptor copy, 0x201) | [V] per 579 + 6t |
| S28 0xe81b3b0 + small helpers | 0xe832cd3..0xe832f3b | `e832cd3  call 0xE81B3B0`; `e832d10  call 0x1A2800`; `e832d16  call 0xEEC59E0`; `e832d2e  call [0xF9A8C78]`; `e832d5e  call 0xE938CB0`; `e832d90  call 0xE938D70`; `e832f3b  call 0xEEC5A00` | Tail helpers: TLS trace scopes 0xe938cb0/0xe938d70 x8, sync 0xeec5a00, small helpers | [V] per 6t (scopes) |
| S29 Epilog / stack cookie / return | 0xe832f3b..0xe832fc1 | `e832f7c  call 0x75740`; `e832fae  call 0x75B60` -> `0xe832fc1` (end) | Stack cookie verify + STL length-error helpers (0x75740 "bad array new length" x4, 0x75b60 "vector too long" x1), then function end | [V] per dis |

Stage-tail note: function end is 0xe832fc1 (exclusive) per `rdis fn` header. The epilog region (0xe832cee / 0xe832d54 / 0xe832da4 / 0xe832def labels are skip targets from the early guards) converges here.

[UNVERIFIED: 0xe82e230 exact stage boundaries between S4..S28 — boundaries chosen at call sites; instructions within each range not all individually quoted (would exceed scope); "instruction-complete" per brief not fully achieved for hot middle ranges — flagged.]
[UNVERIFIED: 0xe82e230 whether the `call qword ptr [0xF99FFA0]` x65 are all command-wrapper emissions or include barriers — 6t says 0xe800c10 x21 is the wrapper with 21 emission sites; relationship between the 65 IAT-thunk calls and 21 wrapper calls not resolved.]

## (4) Callers of 0xe82e230

`python tools/sigs/xref.py callers 0xe82e230` -> docs/progress/oc_U-B3a_callers.txt:
```
0xe83d440 0x381
```
Only ONE direct caller found: `0xe83d440` (size 0x381) — the RTX D3D12 submit wrapper (slot 50 of the RTX subclass vtable 0xF4EEE80). Per BGFX_MAP 6bi/line 1370: RTX submit override `0xe83d440` (0x381 bytes) does TLAS/BLAS pre-pass then **calls base submit `0xe82e230`**. [V]

Indirect callers (via vtable slot 50, not returned by xref.py callers):
- Base D3D12 context vtable `0xF4ED2D0` slot 50 = `0xe82e230` [V per 6f/line 265]
- RTX subclass vtable `0xF4EEE80` slot 50 = `0xe83d440` (wrapper that calls 0xe82e230) [V per 6f/line 266]
- Render thread reaches submit via renderer vtable `[rax+0x190]` = slot 50 at `0xbc633a8` inside `0xbc63150` render-frame step [V per 1493]

[UNVERIFIED: 0xe82e230 whether xref.py's "1 xrefs in" (rdis fn) vs the 11/19 caller pattern seen on 0xe82d960 (U-B7b) applies here — only 1 direct caller found, remainder are indirect vtable dispatch.]

## Verification artifacts
- docs/progress/oc_U-B3a_fn.txt — `rdis ... fn 0xe82e230 --max 300` (entry + full body, utf-16)
- docs/progress/oc_U-B3a_listing.txt — `python tools/sigs/dumplist.py 0xe82e230 0xe832fc1` (4020 lines)
- docs/progress/oc_U-B3a_callees.txt — `rdis ... callees 0xe82e230` (counts + strings)
- docs/progress/oc_U-B3a_callers.txt — `python tools/sigs/xref.py callers 0xe82e230`
- Per-callee dis: oc_U-B3a_c_75740.txt, oc_U-B3a_c_75b60.txt, oc_U-B3a_c_eec59f0.txt, oc_U-B3a_c_ebce390.txt, oc_U-B3a_c_38a1520.txt

Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-B3a.md` (validate every quoted `0xRVA  instr` line).

## TOOL REQUESTS
None needed for this unit; all data from rdis/xref/dumplist already in tools/sigs.