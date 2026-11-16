# UNIT U-B3b — D3D12 submit descriptor binding types (BGFX_MAP sections 6an, 6ao; submit function 0xe82e230)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

## NEXT
DONE: `python tools/sigs/verify_oc.py docs/progress/oc_U-B3b.md` -> claimed=76 match=76 mismatch=0 no-such-instr=0 [PASS]. Resume at: address open items listed at end (submit-vs-executor relationship of the three items, the 7 flush call sites of 0xe81b720, record +0x11 access-flag semantics), then finalize unit.

## (0) Anchor: submit 0xe82e230 callee map (from oc_U-B3a.md [V])
- submit 0xe82e230 size 0x4d91 (0xe82e230..0xe832fc1), single direct caller 0xe83d440. Descriptor-related stages in submit: S5 = descriptor/upload ring begin calling 0xe8360f0 (x3); S27 = tracker firstUse + descriptor copy calling 0xe83aed0 (x4). Per BGFX_MAP 6an/6ao the descriptor-binding-type switch, the sort-key program field read, and the descriptor flush live in the draw-executor path reached from submit; all three verified by disassembly below.

## (1) Descriptor-binding-type switch / compare code [V]
Location: draw-executor bind-list dispatch at 0xe8230b8..0xe8230c6. Per-draw binding records are 20 bytes (`lea rax,[rax+rax*4]` = index*5 for 20-byte stride at 0xe823086), count bound to 0x41 (65) at 0xe82306e/0xe823071. The type byte is read at record+0x13; types 0..8 accepted (>8 -> default at 0xe824FBE). Jump table base 0xF4EE774 (data_f4ee774), int32 signed offsets, indirect `jmp rax`.

Quoted instructions [V]:
```
e82306e  cmp eax,0x41                                   ; record count bound 0x41 (65)
e823071  jae 0xE8258F5
e823077  mov [rbx+0x150],eax
e82307d  mov eax,eax
e82307f  mov [rbx+0x1C0],rax
e823086  lea rax,[rax+rax*4]                            ; index*5 (20-byte record stride)
e82308a  mov rcx,[rbx+0x1F0]                            ; record array base
e823091  movzx edi,word ptr [rcx+rax*4+0xA]             ; handle at record+0xA
e823096  cmp rdi,0xFFFF
e82309d  je short 0xE823030                             ; handle==0xFFFF (none) -> skip
e82309f  mov [rbx+0xF0],r10d
e8230a6  lea rsi,[rcx+rax*4]                            ; rsi = &record[index]
e8230aa  movzx eax,byte ptr [rsi+0x13]                  ; AL = record type byte (record+0x13), types 0..8
e8230ae  cmp rax,8
e8230b2  ja 0xE824FBE                                   ; type>8 -> default
e8230b8  lea rcx,[0xF4EE774]                           ; jump table base [data_f4ee774]
e8230bf  movsxd rax,[rcx+rax*4]                         ; rax = table[type] (int32 offset)
e8230c3  add rax,rcx                                    ; rax = base + offset = handler RVA
e8230c6  jmp rax                                        ; indirect jump to handler
```

Jump table decoded with `python tools/sigs/jt.py 0xF4EE774 9` [V]:
| tag | handler RVA |
|---|---|
| 0 | 0xe8230c8 |
| 1 | 0xe824a42 |
| 2 | 0xe824a4f |
| 3 | 0xe8230c8 |
| 4 | 0xe824991 |
| 5 | 0xe824ab7 |
| 6 | 0xe82326d |
| 7 | 0xe82326d |
| 8 | 0xe824af1 |

## (2) Binding-type table (value, handler RVA, what it binds, [V] quoted instructions)
Each handler entry verified as real code; `0xe82dcc0(rec, cmdlist, 8)` transition helper called when record `+0x11` access flag set; writes use `0xe82d960` (6ae) [I per 6an].

| type | handler RVA | what it binds | [V] quoted instructions |
|---|---|---|---|
| 0, 3 | 0xe8230c8 | texture — guarded paged array `[r9+0xC96180]` stride 0xB8, guard byte 0xC96190, handle>>12 page select (table `this+0xBDE178` per 6an) | `e8230c8  movzx ecx,byte ptr [r9+0xC96190]` / `e8230e8  mov rax,[r9+0xC96180]` / `e8230ef  shr rax,3` |
| 1 | 0xe824a42 | buffer in the 0x78-stride table (`this+0x93A178` per 6an; code uses `[rbx+0x5D8 + handle*0x78]`) | `e824a42  imul rdi,0x78` / `e824a46  add rdi,[rbx+0x5D8]` |
| 2 | 0xe824a4f | buffer in the 0x80-stride table (`this+0x9B2178` per 6an; code uses `[rbx+0x588 + handle<<7]`) | `e824a4f  shl edi,7` / `e824a52  add rdi,[rbx+0x588]` |
| 4 | 0xe824991 | framebuffer/render target — `[rbx+0x3A0 + handle*0x78]` stride 0x78 [V, resolves the 6an/6z stride conflict in favor of 0x78] + framebuffer-attachment array `[r11+r8*8+0x224A8]` indexed by handle>>6 | `e824991  imul rax,rdi,0x78` / `e8249c7  shr r8d,6` / `e8249d2  mov r9,[r11+r8*8+0x224A8]` |
| 5 | 0xe824ab7 | inline constant/uniform stream copy — reads `[stream+0x10]`, advances `[stream+8] += [stream+0x18]` | `e824ad2  mov eax,[r8+0x18]` / `e824ad6  add [r8+8],rax` / `e824ae4  mov rax,[r8+0x10]` / `e824ae8  mov [rcx+rdx*8],rax` |
| 6, 7 | 0xe82326d | descriptor-table list — loop over a 16-byte-stride array at `local+0x1C0` (`shl rcx,4`), 20-byte records (handle +0xA), guarded array `[r9+0xC96190]` | `e823283  shl rcx,4` / `e8232fc  lea r10,[rax+rax*4]` / `e823300  movzx r12d,word ptr [r14+r10*4+0xA]` |
| 8 | 0xe824af1 | list variant of 5/6 — loops a 16-byte-stride array (`shl rsi,4`), each entry a 20-byte record, binds via 0x78-stride table | `e824b07  shl rsi,4` / `e824b77  lea rdx,[rcx+rcx*4]` / `e824b8d  imul rax,rcx,0x78` |

Note: BGFX_MAP 6an stated the jump table at "rva 0xFAE774" — disassembly shows the actual base is 0xF4EE774 [V]. It also listed type-4 table stride as possibly 0x130 (6z conflict) — disassembly confirms stride 0x78 (`imul rax,rdi,0x78` at 0xe824991) [V].

## (3) Sort-key program field read [V]
Per BGFX_MAP 6ao: `(key >> 0x15) & 0x7FF` = program index (11 bits) -> `this+0xB62178 + idx*0xF8` (program record array, 0xF8 stride, base in `rbx+0x5E0`). Exact instructions in the draw executor at 0xe822480..0xe8224b0 [V]:

```
e822480  mov rax,r15                                    ; r15 = sort key (u64)
e822483  shr rax,0x15                                   ; rax = key >> 0x15   (program field shift)
e822487  mov [rbx+0x160],rax
e82248e  and eax,0x7FF                                  ; eax = (key >> 0x15) & 0x7FF = program index   (mask)
e822493  imul rax,0xF8                                  ; rax = programIdx * 0xF8
e82249a  mov rcx,[rbx+0x5E0]                            ; rcx = program record array base (this+0xB62178)
e8224a1  lea rdx,[rcx+rax]                              ; rdx = &program record[programIdx]
e8224a5  mov [rbx+0x130],rdx
e8224ac  mov rax,[rcx+rax]                              ; rax = program record[+0x00] = vertex-shader record ptr
e8224b0  mov esi,[rax+0xA8]                             ; esi = signature u32 at vs record +0xA8 (PSO-cache probe key)
```

So the exact instruction that reads the program field out of the sort key is the **shift** `e822483  shr rax,0x15` immediately followed by the **mask** `e82248e  and eax,0x7FF`. Related tag fields also decoded nearby: `e822650  shr r11d,0x11` / `e822656  shr r11,0x25` / `e82265a  and r11d,0x7FF` (view/depth-type tags) [V].

## (4) Descriptor flush call [V]
Per BGFX_MAP 6ao (corrected in the 6ay/6ej region note): `0xe81b720` is the descriptor flush (draw-batch flush), signature `0xe81b720(DescAllocator* rcx, Device rdx, CmdList wrapper r8, kind r9d)`. Called 7 times in the executor (6 flush sites + 1 after state change) [I per 6ao]. Function entry and argument register map verified by disassembly at 0xe81b720.. [V]:

```
e81b720  push r15                                       ; prologue
e81b722  push r14
e81b724  push r13
e81b726  push r12
e81b728  push rsi
e81b729  push rdi
e81b72a  push rbp
e81b72b  push rbx
e81b72c  sub rsp,0x88
e81b733  mov r12d,r9d                                   ; r12d = kind (arg4)
e81b736  mov esi,[rcx+r12*4+0x10]                       ; esi = per-kind pending count [rcx+kind*4+0x10]
e81b73e  je 0xE81BF0F                                   ; count==0 -> nothing to flush
e81b744  mov rbx,r8                                     ; rbx = CmdList wrapper (arg3)
e81b747  mov rdi,rcx                                    ; rdi = DescAllocator (arg1)
e81b74a  mov dword ptr [rcx+r12*4+0x10],0               ; reset per-kind pending count to 0
e81b753  cmp [rcx+0x115C],esi                           ; capacity [rcx+0x115C] vs count
e81b759  jae short 0xE81B78F                            ; no wrap -> skip copy path
...wrap path...
e81b78f  inc dword ptr [rdi+r12*4+0x1148]               ; stats wrap counter +0x1148
e81b797  lea r14,[rdi+0x10C0]                           ; r14 = descriptor state copy src (rcx+0x10C0, 0x50 bytes)
e81b79e  mov r15,[rdi+r12*8+0x18]                       ; r15 = per-kind heap u64 [rcx+kind*8+0x18]
e81b7b3  mov rax,[r15+0x60]                             ; heap GPU descriptor handle +0x60
e81b7b7  mov [rdi+0x1120],rax
e81b7be  mov rax,[r15+0x68]                             ; heap GPU descriptor handle +0x68
e81b7c2  mov [rdi+0x1128],rax
e81b7c9  mov rcx,[rbx+0x30]                             ; rcx = cmdlist object ([wrapper+0x30])
e81b7cd  mov r8,[r15+0x60]                              ; r8 = GPU handle +0x60
e81b7d1  mov rax,[rcx]
e81b7d4  mov rax,[rax+0x130]                            ; cmdlist vtable +0x130
e81b7db  mov edx,2                                      ; root param index 2
e81b7e0  call qword ptr [0xF99FFA0]                     ; SetGraphicsRootDescriptorTable(rootParam=2, handle=heap+0x60)
e81b7e6  mov rcx,[rbx+0x30]
e81b7ea  mov r8,[r15+0x68]                              ; r8 = GPU handle +0x68
e81b7ee  mov rax,[rcx]
e81b7f1  mov rax,[rax+0x130]                            ; cmdlist vtable +0x130
e81b7f8  mov edx,3                                      ; root param index 3
e81b7fd  call qword ptr [0xF99FFA0]                     ; SetGraphicsRootDescriptorTable(rootParam=3, handle=heap+0x68)
e81b803  mov r8d,0x50
e81b809  mov rcx,r14                                    ; 0x50-byte descriptor-state copy
e81b80c  mov rdx,r15
e81b80f  call 0xEBCE390                                 ; copy descriptor state
e81b814  mov rcx,[rbx+0x30]
e81b818  mov rax,[rcx]
e81b81b  mov rax,[rax+0x160]                            ; cmdlist vtable +0x160
e81b822  xor edx,edx
e81b824  mov r8d,5                                      ; root param index 5
e81b82a  mov r9,r15                                     ; r9 = GPU handle
e81b82d  call qword ptr [0xF99FFA0]                     ; SetGraphicsRootConstantBufferView/DescriptorTable(rootParam=5)
```

Descriptor flush function RVA: **0xe81b720**.
Arguments: rcx = DescAllocator*, rdx = Device (present in signature, not consumed at entry), r8 = CmdList wrapper, r9d = kind (u32).
Per-kind state touched: pending count `u32 [rcx+kind*4+0x10]`, heap `u64 [rcx+kind*8+0x18]`, stats `+0x1148` (wrap) / `+0x1150`, capacity `+0x115C`, enable flag byte `+0x1164`, descriptor-state copy src `rcx+0x10C0` (0x50 bytes) [V].
Vtable slots used on the command-list object (`[wrapper+0x30]`): +0x130 (root params 2 and 3), +0x160 (root param 5), +0x158 (IASetIndexBuffer, seen at e81b84f) [V].

## Open
- Whether submit 0xe82e230 itself (vs. the draw executor it drives) directly performs the binding-type switch / sort-key read / flush calls — these three are confirmed in the executor path (0xe822400/0xe823000/0xe81b720); submit's own direct callees (per oc_U-B3a.md) are 0xe8360f0 (S5) and 0xe83aed0 (S27), neither of which is the type switch or flush. [I] relationship to be confirmed by orchestrator.
- Exact call sites of 0xe81b720 (the 7 flush sites) within the executor not individually quoted [UNVERIFIED: 0xe81b720 call sites].
- Record `+0x11` access-flag semantics (0=read, nonzero=needs UAV/write transition) [I per 6an].

## TOOL REQUESTS
None needed for this unit; all data from rdis/jt.py/disassembly already in tools/sigs.
