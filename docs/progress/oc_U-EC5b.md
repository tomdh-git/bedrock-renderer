## NEXT
DONE

# U-EC5b — C5b drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies pending
Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only.
Reference: docs/BGFX_MAP.md section 6aq (drawutils pass templates: BindMaterialTexture x1110, BindFramebufferDepth x826, BindFramebufferColor x823, BindShaderBuffer x373, BindAccelerationStructure x49); sections 6o/6p (VV builder, FNV-1 pass names/hashes); 6ar (VV builder 0x55F1450..0x563F594 declaration order).
Previously closed ([V], docs/progress/oc_U-EC5b_r1.md, not re-proven here): sub_5667860 (field-copy body, fields 0x0..0xC4, 0xD4, 0xE4, 0x100, 0xE8, 0xF0, 0xF8, 0x108, 0x110); sub_5667c80 (calls sub_5667860 then clears +0x118/+0x128); sub_5667e70 (byte check [rcx+0x168]==1); sub_5668ac0 (FNV-1 hash helper, [r8+8]/[rdx+8] qword reads).

## Pending work — enumeration
Every distinct `call` target inside sub_55f1450 (VV builder, 0x55F1450..0x563F594; docs/progress/builder_full.lst) lying in 0x5660000..0x568FFFF, plus what sub_bbe2d50 (RTX builder) calls. Role: P = per-pass body (writes a pass record), D = descriptor builder (builds locals + calls a declare helper, no direct dest writes), H = shared helper (not a per-pass body).

| body | role | builder call sites | sub_bbe2d50 | status |
|---|---|---|---|---|
| sub_5667860 | P: field copy dest+0x0..0x110 | 4 | — | [V] (oc_U-EC5b_r1.md) |
| sub_5667c80 | P: sub_5667860 + clear dest+0x118/+0x128 | 5 | — | [V] (oc_U-EC5b_r1.md) |
| sub_5667e70 | P: byte check dest+0x168==1; also element callback | 6 | — | [V] (oc_U-EC5b_r1.md) |
| sub_5668ac0 | H: FNV-1 pass-name hash | 10 | — | [V] (oc_U-EC5b_r1.md) |
| sub_5667fe0 | P: Color0/1/2 record + lazy FNV-1 name hashes | 1 | — | [V] this note |
| sub_56685c0 | D: SSO-name descriptor + declare sub_5699580 | 2 | — | [V] this note |
| sub_566a450 | P: sub_5667860 + string copy into dest+0x118..0x168 | 2 | — | [V] this note |
| sub_566adb0 | P: tiny body, "PreviousGameColorRT" hash + dest+0x28=0 | 1 | — | [V] this note |
| sub_566d690 | D: move 3 string descriptors (a1/a2/a3) + declare sub_56b87d0 | 2 | — | [V] this note |
| sub_5668d90 | D: big local descriptor + declare sub_56c9930 | 5 | — | [V] observed sites this note |
| sub_5669cf0 | D: descriptor + declare sub_56cba60 | 1 | — | [V] observed sites this note |
| sub_566a880 | D: descriptor + declare sub_5699580 | 1 | — | [V] observed sites this note |
| sub_567c110 | P: field copy dest+0x0..0x120 | 2 | — | [V] this note |
| sub_568bdc0 | P: large record build dest+0x0..0x2D8 | 10 | — | [V] observed sites this note |
| sub_567e510 | P?: element-loop body, 0x290 stride, vtable data_f25b4f0 | 1 | — | [?] entry only |
| sub_567fd70 | P?: same family, vtable data_f25b550 | 1 | — | [?] entry only |
| sub_56815d0 | P?: same family, vtable data_f25b5b0 | 1 | — | [?] entry only |
| sub_5682e20 | P?: same family, vtable data_f25b610 | 1 | — | [?] entry only |
| sub_5684660 | P?: same family, vtable data_f25b670 | 1 | — | [?] entry only |
| sub_5685ea0 | P?: same family, vtable data_f25b6d0 | 1 | — | [?] entry only |
| sub_56876f0 | P?: same family, vtable data_f25b730 | 1 | — | [?] entry only |
| sub_5669ae0 | H: array destroyer, stride 0x290 | 13 | — | [I] |
| sub_566a620 | H: pass-struct destroyer | 2 | — | [I] |
| sub_566b010 | H: array destroyer, stride 0x170, calls sub_5667e70 per element | 1 | — | [I] |
| sub_5679f20 | H: 0x50-stride array appender (vtable data_f25c7d0) | 1 | 1 ([V] 0xbbe364e) | [I] |
| sub_567a930 | H: 0x50-stride array appender (vtable data_f25c7e0) | 1 | 1 ([V] 0xbbe3661) | [I] |
| sub_567b570 | H: hash-table lookup (registration/helper), 111 xrefs total | 90 | 3 ([V] 0xbbe34b8/0xbbe3545/0xbbe35a9) | [I] |
| sub_567c3f0 | H: hash-table lookup variant (shl 6) | 6 | — | [I] |
| sub_567c8b0 | H: name-hash registration (0x30-byte alloc) | 10 | — | [I] |
| sub_56894c0 | H: hash helper (*(a1+0)+0x2C)*0x58 + [*(a1+8)+0x738] mix | 2 | — | [I] |
| sub_5689800 | H: vector erase/compact (0x18-stride elements) | 18 | 1 ([V] 0xbbe3134) | [I] |
| sub_568ad40 | H: SSO string copy | 4 | — | [I] |
| sub_568b0d0 | H: 0x308-byte object creator (vtable data_effe910) | 3 | — | [I] |
| sub_568c4e0 | H: declare-by-name core (reads [rcx+0x58] table) | — | — | [I] |
| sub_568c420 / sub_568cb30 | H: declare-by-name wrappers (flag byte 1 / 2) | 2 / 1 | — | [I] |
| sub_568cbe0 | H: string allocator (called by sub_568ad40) | — | — | [I] |

sub_bbe2d50 (RTX builder): head scanned (500 instrs) — calls only shared helpers (sub_567b570 x3 [V at 0xbbe34b8/0xbbe3545/0xbbe35a9], sub_5689800 [V at 0xbbe3134], sub_5679f20 [V at 0xbbe364e], sub_567a930 [V at 0xbbe3661]) plus inline sub_5698290 declare calls at 0xbbe3fbc/0xbbe3f5a/0xbbe41bd/0xbbe421f [V per oc_U-EG4b.md]; no sub_566*/sub_567*/sub_568* per-pass body callee seen; tail unscanned [?].
Out of strict scope (0x569xxxx+, called from sub_55f1450): sub_5698290 declarator [V per oc_U-EG4b.md]; sub_5693680/sub_5694510/sub_5695960/sub_5696540/sub_5697650 among others, listed by oc_U-EF1b.md as undecoded helper signatures [?].

## ANSWER TABLE (pending part of C5b)
Columns: body+offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag. Size from the instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1, call 5). One row per distinct offset; all sites listed. Rows whose instruction line is quoted are [V]; meaning is stated only where an instruction or string shows it, else '-'.

### sub_5667fe0 — Color0/1/2 per-pass record builder (builder site 0x55ff4de). Args: rsi=dest pass record (rcx), rdi=declare context (rdx), r14d=r8d (u16), rbx=r9d. Builds 3 descriptors on the stack (fmt dword 0x1C/0x0A/0x0C at rbp-0x14/0x5C/0x3C, strings "Color0"/"Color1"/"Color2"), declares each via sub_5698290, then writes dest. Lazy one-time FNV-1 of each name (strings 0xF7E41CA/0xF7DDEC4/0xF7D9C07; basis 0xCBF29CE484222325, prime 0x100000001B3) cached in data_129CA3A0/3B0/3C0, guarded by data_129CA3A8/3B8/3C8 vs the security cookie (signed `jg`).
| 5667fe0+0x0 | 8 | [rsi+0x0] write | `0x5668121  mov [rsi],rcx` | dest+0 = Color2 name hash (data_129CA3C0) | [V] |
| 5667fe0+0x8 | 8 | [rsi+0x8] write | `0x5668124  mov [rsi+8],rax` | dest+8 = Color2 declare return (node ptr) | [V] |
| 5667fe0+0x12 | 1 | [rsi+0x12] write | `0x5668128  mov byte ptr [rsi+0x12],0` | dest+0x12 = 0 | [V] |
| 5667fe0+0x18 | 8 | [rsi+0x18] write | `0x566812c  mov [rsi+0x18],r12` | dest+0x18 = Color1 name hash (data_129CA3B0) | [V] |
| 5667fe0+0x20 | 8 | [rsi+0x20] write | `0x5668130  mov [rsi+0x20],r14` | dest+0x20 = Color2 declare return | [V] |
| 5667fe0+0x2A | 1 | [rsi+0x2A] write | `0x5668134  mov byte ptr [rsi+0x2A],0` | dest+0x2A = 0 | [V] |
| 5667fe0+0x30 | 8 | [rsi+0x30] write | `0x5668138  mov [rsi+0x30],r15` | dest+0x30 = Color0 name hash (data_129CA3A0) | [V] |
| 5667fe0+0x38 | 8 | [rsi+0x38] write | `0x566813c  mov [rsi+0x38],rbx` | dest+0x38 = Color0 declare return | [V] |
| 5667fe0+0x42 | 1 | [rsi+0x42] write | `0x5668140  mov byte ptr [rsi+0x42],0` | dest+0x42 = 0 | [V] |
| 0x129CA3A8 | 4 | [0x129CA3A8] read | `0x566800d  mov eax,[0x129CA3A8]` | Color0 lazy-init flag vs security cookie | [V] |
| 0x129CA3B8 | 4 | [0x129CA3B8] read | `0x5668032  mov eax,[0x129CA3B8]` | Color1 lazy-init flag vs security cookie | [V] |
| 0x129CA3C8 | 4 | [0x129CA3C8] read | `0x5668057  mov eax,[0x129CA3C8]` | Color2 lazy-init flag vs security cookie | [V] |
| 0x129CA3A0 | 4 | [0x129CA3A0] write | `0x5668359  mov [0x129CA3A0],rcx` | Color0 FNV-1 hash cache | [V] |
| 0x129CA3B0 | 4 | [0x129CA3B0] write | `0x5668420  mov [0x129CA3B0],rcx` | Color1 FNV-1 hash cache | [V] |
| 0x129CA3C0 | 4 | [0x129CA3C0] write | `0x56684d4  mov [0x129CA3C0],rdx` | Color2 FNV-1 hash cache | [V] |
| call@0x56680b5 | 5 | - | `0x56680b5  call 0x5698290` | declare Color0 (desc @rbp-0x18, fmt dword 0x1C at 0x56680a4) | [V] |
| call@0x56680e5 | 5 | - | `0x56680e5  call 0x5698290` | declare Color1 (desc @rbp-0x60, fmt dword 0x0A at 0x56680d4) | [V] |
| call@0x5668115 | 5 | - | `0x5668115  call 0x5698290` | declare Color2 (desc @rbp-0x40, fmt dword 0x0C at 0x5668104) | [V] |

### sub_56685c0 — descriptor-builder per-pass body (2 builder sites). Args: rsi=dest (rcx), rbx=a1 (rdx), r14=a2 (r8), rdi=a3 (r9). Builds a descriptor on the stack (SSO string from a1+0x10/+0x18, a3+0x8 byte flag), hashes via sub_568ad40, resolves via sub_76a8a0, declares via sub_5699580. No [rsi]+K stores seen; pass record is written by the declare helper [I].
| 56685c0+a3+0x8 | 1 | [r9+0x8] read | `0x56685EE  movzx r15d,byte ptr [r9+8]` | a3+0x8 byte flag | [V] |
| 56685c0+a1+0x10 | 8 | [rdx+0x10] read | `0x56685F3  mov rax,[rdx+0x10]` | a1+0x10 SSO string ptr | [V] |
| 56685c0+a1+0x18 | 8 | [rdx+0x18] read | `0x56685F7  cmp qword ptr [rdx+0x18],0x10` | a1+0x18 SSO length vs 0x10 | [V] |
| 56685c0+a1+0x0 | 8 | [rbx] read (rbx=a1) | `0x5668601  mov rcx,[rbx]` | a1+0x0 heap string ptr (long string) | [V] |
| 56685c0+a3+0x0 | 8 | [rdi] read (rdi=a3) | `0x56686FB  mov r8,[rdi]` | a3+0x0 object ptr | [V] |
| 56685c0+obj+0x8 | 2 | [rax+0x8] read (rax=[rdi]) | `0x56687A8  movzx ecx,word ptr [rax+8]` | object+0x8 u16 | [V] |
| 56685c0+obj+0x0 | 8 | [rax] read | `0x56687B0  mov rax,[rax]` | object+0x0 qword | [V] |
| call@0x5668862 | 5 | - | `0x5668862  call 0x5699580` | declare pass (rcx=rsi=dest, rdx=&desc rbp-0x50, r8=0) | [V] |

### sub_566a450 — sub_5667860 variant (2 builder sites). Calls sub_5667860 first (fields dest+0x0..0x110, [V] per oc_U-EC5b_r1.md), then clears dest+0x118/+0x128, copies the a2 SSO string into dest+0x118..+0x128 (alloc via [0xF99FFA0] when long), and if [rsi+0x38]==1 copies src fields into dest+0x130..+0x168.
| 566a450+0x118 | 16 | [r15+0x118] write (r15=dest) | `0x566a47a  movups [r15+0x118],xmm0` `0x566a519  mov [r15+0x118],r14` | string begin: zeroed, then alloc ptr | [V] |
| 566a450+0x120 | 8 | [r15+0x120] write | `0x566a520  mov [r15+0x120],r14` | string capacity | [V] |
| 566a450+0x128 | 8 | [r15+0x128] write | `0x566a482  mov qword ptr [r15+0x128],0` `0x566a52a  mov [r15+0x128],rbx` | string end: 0, then copy end | [V] |
| 566a450+0x130 | 8 | [r15+0x130] write | `0x566a561  mov [r15+0x130],rax` (rax=[rsi]) | dest+0x130 = src+0x0 (gated [rsi+0x38]==1) | [V] |
| 566a450+0x138 | 16 | [r15+0x138] write | `0x566a56b  movups [r15+0x138],xmm0` `0x566a584  mov [r15+0x138],rax` | zeroed, then dest+0x138 = src+8 | [V] |
| 566a450+0x140 | 8 | [r15+0x140] write | `0x566a58f  mov [r15+0x140],rax` (rax=[rsi+0x10], refcount inc'd) | dest+0x140 = src+0x10 | [V] |
| 566a450+0x148 | 16 | [r15+0x148] write | `0x566a596  movups [r15+0x148],xmm0` | dest+0x148 = 0 | [V] |
| 566a450+0x158 | 8 | [r15+0x158] write | `0x566a59e  mov qword ptr [r15+0x158],0` | dest+0x158 = 0 | [V] |
| 566a450+0x160 | 1 | [r15+0x160] write | `0x566a5a9  mov byte ptr [r15+0x160],1` | flag = 1 | [V] |
| 566a450+0x168 | 1 | [r15+0x168] write | `0x566a550  mov byte ptr [r15+0x168],0` `0x566a5b1  mov byte ptr [r15+0x168],1` | flag 0 -> 1 | [V] |
| 566a450+a2+0x8 | 8 | [rdi+0x8] read (rdi=a2) | `0x566a48d  mov rbx,[rdi+8]` | a2+0x8 string length | [V] |
| 566a450+a2+0x0 | 8 | [rdi] read | `0x566a491  mov rcx,[rdi]` | a2+0x0 string ptr | [V] |
| 566a450+src+0x38 | 1 | [rsi+0x38] read (rsi=src) | `0x566a558  cmp byte ptr [rsi+0x38],1` | src+0x38 flag == 1 gate | [V] |

### sub_566adb0 — tiny per-pass body (1 builder site). Args: rsi=dest (rcx), rdi=a2 (rdx), rbx=a3 (r8). Lazy FNV-1 of "PreviousGameColorRT" (string 0xF7C86EA; flag data_129CA550 vs cookie, cache data_129CA548), reads a3+0xA78 object chain, calls sub_56cc5e0/sub_56cca60/sub_56cc330/sub_56cc4f0.
| 566adb0+0x28 | 1 | [rsi+0x28] write | `0x566ae44  mov byte ptr [rsi+0x28],0` | dest+0x28 = 0 | [V] |
| 566adb0+a3+0xA78 | 8 | [r9+0xA78] read (r9=a3) | `0x566ADDA  mov rax,[r9+0xA78]` | a3+0xA78 object ptr | [V] |
| 566adb0+obj+0x0 | 8 | [rax] read (rax=[r9+0xA78]) | `0x566ade8  mov rdx,[rax]` | object+0x0 qword | [V] |
| 0x129CA550 | 4 | [0x129CA550] read | `0x566ae23  mov eax,[0x129CA550]` | lazy-init flag vs security cookie | [V] |
| 0x129CA548 | 4 | [0x129CA548] write | `0x566af6b  mov [0x129CA548],rdx` | "PreviousGameColorRT" FNV-1 hash cache | [V] |

### sub_566d690 — descriptor builder: moves 3 SSO string descriptors (a1=rdx, a2=r8, a3=r9) into locals (zeroing the sources), then declares via sub_56b87d0 (2 builder sites). Args: rsi=dest (rcx), returned unchanged.
| 566d690+a3+0x0(R) | 16 | [r9+0x0] read | `0x566d6ac  movups xmm0,[r9]` | a3 descriptor +0x0 (16 B) | [V] |
| 566d690+a3+0x10(R) | 16 | [r9+0x10] read | `0x566d6b0  movups xmm1,[r9+0x10]` | a3 descriptor +0x10 (16 B) | [V] |
| 566d690+a3+0x10(W) | 8 | [r9+0x10] write (reset) | `0x566d6bd  mov qword ptr [r9+0x10],0` | a3+0x10 = 0 | [V] |
| 566d690+a3+0x18 | 8 | [r9+0x18] write (reset) | `0x566d6c5  mov qword ptr [r9+0x18],0xF` | a3+0x18 = 0xF | [V] |
| 566d690+a3+0x0(W) | 1 | [r9] write (reset) | `0x566d6cd  mov byte ptr [r9],0` | a3+0x0 = 0 | [V] |
| 566d690+a2+0x0(R) | 16 | [r8+0x0] read | `0x566d6d1  movups xmm0,[r8]` | a2 descriptor +0x0 (16 B) | [V] |
| 566d690+a2+0x10(R) | 16 | [r8+0x10] read | `0x566d6d5  movups xmm1,[r8+0x10]` | a2 descriptor +0x10 (16 B) | [V] |
| 566d690+a2+0x10(W) | 8 | [r8+0x10] write (reset) | `0x566d6e2  mov qword ptr [r8+0x10],0` | a2+0x10 = 0 | [V] |
| 566d690+a2+0x18 | 8 | [r8+0x18] write (reset) | `0x566d6ea  mov qword ptr [r8+0x18],0xF` | a2+0x18 = 0xF | [V] |
| 566d690+a2+0x0(W) | 1 | [r8] write (reset) | `0x566d6f2  mov byte ptr [r8],0` | a2+0x0 = 0 | [V] |
| 566d690+a1+0x0(R) | 16 | [rdx+0x0] read | `0x566d6f6  movups xmm0,[rdx]` | a1 descriptor +0x0 (16 B) | [V] |
| 566d690+a1+0x10(R) | 16 | [rdx+0x10] read | `0x566d6f9  movups xmm1,[rdx+0x10]` | a1 descriptor +0x10 (16 B) | [V] |
| 566d690+a1+0x10(W) | 8 | [rdx+0x10] write (reset) | `0x566d705  mov qword ptr [rdx+0x10],0` | a1+0x10 = 0 | [V] |
| 566d690+a1+0x18 | 8 | [rdx+0x18] write (reset) | `0x566d70d  mov qword ptr [rdx+0x18],0xF` | a1+0x18 = 0xF | [V] |
| 566d690+a1+0x0(W) | 1 | [rdx] write (reset) | `0x566d715  mov byte ptr [rdx],0` | a1+0x0 = 0 | [V] |
| call@0x566d794 | 5 | - | `0x566d794  call 0x56b87d0` | declare pass (rcx=rsi=dest, rdx=&desc block rbp-0x60) | [V] |

### sub_5668d90 — descriptor builder: big local descriptor (rbp+0x93C..), reads a1=a2? sources, a 4-way switch on [a4+0x38] via jump table data_f25cc58, then declares via sub_56c9930 (5 builder sites). Args: rsi=dest (rcx), no [rsi]+K stores seen; declare helper writes the pass record [I].
| 5668d90+a1+0x0 | 8 | [rdx+0x0] read | `0x5668dd6  mov rax,[rdx]` | a1+0x0 qword | [V] |
| 5668d90+a2+0x0 | 8 | [r8+0x0] read | `0x5668dd9  mov rcx,[r8]` | a2+0x0 qword | [V] |
| 5668d90+a4+0x38 | 1 | [r14+0x38] read | `0x5668fb8  movzx eax,byte ptr [r14+0x38]` | a4+0x38 (4-way switch) | [V] |
| 5668d90+a4+0x0 | 8 | [r14] read | `0x5668f5c  mov rax,[r14]` | a4+0x0 qword | [V] |
| 5668d90+a4+0x10 | 8 | [r14+0x10] read | `0x5668f7c  mov rax,[r14+0x10]` | a4+0x10 qword | [V] |
| 5668d90+a4+0x20 | 8 | [r14+0x20] read | `0x5668fa6  mov rax,[r14+0x20]` | a4+0x20 qword | [V] |
| 5668d90+a4+0x28 | 8 | [r14+0x28] | `0x5668fca  lea rcx,[r14+0x28]` | a4+0x28 address | [V] |
| 5668d90+a4+0x30 | 8 | [r14+0x30] read | `0x5668ff9  mov rdx,[r14+0x30]` | a4+0x30 qword | [V] |
| 5668d90+a4+0x40 | 16 | [r14+0x40] read | `0x5669030  movups xmm0,[r14+0x40]` | a4+0x40 (16 B) | [V] |
| 5668d90+a4+0x50 | 8 | [r14+0x50] read | `0x5669025  mov rax,[r14+0x50]` | a4+0x50 qword | [V] |
| 5668d90+obj+0x170 | 8 | [rax+0x170] read (rax=[rbx]=[a4+0x28]) | `0x5669057  mov rdx,[rax+0x170]` | object+0x170 qword | [V] |
| call@0x5669433 | 5 | - | `0x5669433  call 0x56c9930` | declare pass (rcx=rsi=dest, rdx=&desc rbp+0x270) | [V] |

### sub_5669cf0 — descriptor builder (1 builder site). Args: rsi=dest (rcx), rbx=a1 (rdx), r14=a2 (r8), rdi=a3 (r9), r15=[rbp+0x2B0]. Builds descriptor (SSO name from a1, float a3+0x8? no — r15+8 float, r15+0xC byte), hashes, resolves via sub_76a8a0, declares via sub_56cba60. No [rsi]+K stores seen [I].
| 5669cf0+a3+0x8 | 4 | [r9+0x8] read | `0x5669d30  mov r12d,[r9+8]` | a3+0x8 dword | [V] |
| 5669cf0+ctx+0x8 | 4 | [r15+0x8] read | `0x5669d34  movss xmm6,[r15+8]` | ctx+0x8 float | [V] |
| 5669cf0+ctx+0xC | 1 | [r15+0xC] read | `0x5669d3a  movzx r13d,byte ptr [r15+0xC]` | ctx+0xC byte | [V] |
| 5669cf0+a1+0x10 | 8 | [rbx+0x10] read | `0x5669d71  mov rax,[rbx+0x10]` | a1+0x10 SSO ptr | [V] |
| 5669cf0+a1+0x18 | 8 | [rbx+0x18] read | `0x5669d75  cmp qword ptr [rbx+0x18],0x10` | a1+0x18 SSO length vs 0x10 | [V] |
| 5669cf0+a1+0x0 | 8 | [rbx] read | `0x5669d7f  mov rcx,[rbx]` | a1+0x0 heap string ptr | [V] |
| 5669cf0+ctx+0x0 | 8 | [r15] read | `0x5669f0d  mov rdx,[r15]` | ctx+0x0 qword | [V] |
| 5669cf0+a3+0x0 | 16 | [r8] read | `0x5669f69  movups xmm1,[r8]` | a3+0x0 (16 B) | [V] |
| 5669cf0+a3+0x10 | 8 | [r8+0x10] read | `0x5669f5e  mov rdx,[r8+0x10]` | a3+0x10 qword | [V] |
| call@0x566a0b0 | 5 | - | `0x566a0b0  call 0x56cba60` | declare pass (rcx=rsi=dest, rdx=&desc rbp-0x50, r8=0) | [V] |

### sub_566a880 — descriptor builder (1 builder site). Same shape as sub_56685c0 (a3+0x8 float, a3+0xC byte, a1 SSO string, object at a3+0 with +0x8 u16), declares via sub_5699580 at 0x566ab2d. No [rsi]+K stores seen; tail = local cleanup [I].
| 566a880+a3+0x8 | 4 | [r9+0x8] read | `0x566a8b5  movss xmm6,[r9+8]` | a3+0x8 float | [V] |
| 566a880+a3+0xC | 1 | [r9+0xC] read | `0x566a8bb  movzx r15d,byte ptr [r9+0xC]` | a3+0xC byte | [V] |
| 566a880+a1+0x10 | 8 | [rdx+0x10] read | `0x566a8c0  mov rax,[rdx+0x10]` | a1+0x10 SSO ptr | [V] |
| 566a880+a1+0x18 | 8 | [rdx+0x18] read | `0x566a8c4  cmp qword ptr [rdx+0x18],0x10` | a1+0x18 SSO length vs 0x10 | [V] |
| 566a880+a1+0x0 | 8 | [rbx] read (rbx=a1) | `0x566a8ce  mov rcx,[rbx]` | a1+0x0 heap string ptr | [V] |
| 566a880+a3+0x0 | 8 | [rdi] read (rdi=a3) | `0x566a9c6  mov r8,[rdi]` | a3+0x0 object ptr | [V] |
| 566a880+obj+0x8 | 2 | [rax+0x8] read (rax=[rdi]) | `0x566aa73  movzx ecx,word ptr [rax+8]` | object+0x8 u16 | [V] |
| 566a880+obj+0x0 | 8 | [rax] read | `0x566aa7b  mov rax,[rax]` | object+0x0 qword | [V] |
| call@0x566ab2d | 5 | - | `0x566ab2d  call 0x5699580` | declare pass (rcx=rsi=dest, rdx=&desc rbp-0x50, r8=0) | [V] |

### sub_567c110 — pure field-copy per-pass body (2 builder sites). Args: rsi=dest (rcx), rdi=src+0xE8 block (rdx advanced), src=rdx. Copies src+0x0..0x120 into dest, with a helper block (sub_119b5f0) for dest+0xE8..0x107, then dest+0x108..0x120 from rdi.
| 567c110+0x0 | 16 | [rdx+0x0]->[rcx+0x0] | `0x567c124  movups xmm0,[rdx]` `0x567c127  movups [rcx],xmm0` | copy 16-byte block +0x0 | [V] |
| 567c110+0x10 | 8 | [rdx+0x10]->[rcx+0x10] | `0x567c11c  mov rax,[rdx+0x10]` `0x567c120  mov [rcx+0x10],rax` | copy qword +0x10 | [V] |
| 567c110+0x18 | 4 | [rdx+0x18]->[rcx+0x18] | `0x567c12a  movss xmm0,[rdx+0x18]` `0x567c12f  movss [rcx+0x18],xmm0` | copy float +0x18 | [V] |
| 567c110+0x1C | 4 | [rdx+0x1C]->[rcx+0x1C] | `0x567c134  movss xmm0,[rdx+0x1C]` `0x567c139  movss [rcx+0x1C],xmm0` | copy float +0x1C | [V] |
| 567c110+0x20 | 4 | [rdx+0x20]->[rcx+0x20] | `0x567c13e  movss xmm0,[rdx+0x20]` `0x567c143  movss [rcx+0x20],xmm0` | copy float +0x20 | [V] |
| 567c110+0x24 | 4 | [rdx+0x24]->[rcx+0x24] | `0x567c148  movss xmm0,[rdx+0x24]` `0x567c14d  movss [rcx+0x24],xmm0` | copy float +0x24 | [V] |
| 567c110+0x28 | 4 | [rdx+0x28]->[rcx+0x28] | `0x567c152  movss xmm0,[rdx+0x28]` `0x567c157  movss [rcx+0x28],xmm0` | copy float +0x28 | [V] |
| 567c110+0x2C | 4 | [rdx+0x2C]->[rcx+0x2C] | `0x567c15c  movss xmm0,[rdx+0x2C]` `0x567c161  movss [rcx+0x2C],xmm0` | copy float +0x2C | [V] |
| 567c110+0x30 | 4 | [rdx+0x30]->[rcx+0x30] | `0x567c166  movss xmm0,[rdx+0x30]` `0x567c16b  movss [rcx+0x30],xmm0` | copy float +0x30 | [V] |
| 567c110+0x34 | 4 | [rdx+0x34]->[rcx+0x34] | `0x567c170  movss xmm0,[rdx+0x34]` `0x567c175  movss [rcx+0x34],xmm0` | copy float +0x34 | [V] |
| 567c110+0x38 | 4 | [rdx+0x38]->[rcx+0x38] | `0x567c17a  movss xmm0,[rdx+0x38]` `0x567c17f  movss [rcx+0x38],xmm0` | copy float +0x38 | [V] |
| 567c110+0x3C | 4 | [rdx+0x3C]->[rcx+0x3C] | `0x567c184  movss xmm0,[rdx+0x3C]` `0x567c189  movss [rcx+0x3C],xmm0` | copy float +0x3C | [V] |
| 567c110+0x40 | 4 | [rdx+0x40]->[rcx+0x40] | `0x567c18e  movss xmm0,[rdx+0x40]` `0x567c193  movss [rcx+0x40],xmm0` | copy float +0x40 | [V] |
| 567c110+0x44 | 4 | [rdx+0x44]->[rcx+0x44] | `0x567c198  movss xmm0,[rdx+0x44]` `0x567c19d  movss [rcx+0x44],xmm0` | copy float +0x44 | [V] |
| 567c110+0x48 | 4 | [rdx+0x48]->[rcx+0x48] | `0x567c1a2  movss xmm0,[rdx+0x48]` `0x567c1a7  movss [rcx+0x48],xmm0` | copy float +0x48 | [V] |
| 567c110+0x4C | 4 | [rdx+0x4C]->[rcx+0x4C] | `0x567c1ac  movss xmm0,[rdx+0x4C]` `0x567c1b1  movss [rcx+0x4C],xmm0` | copy float +0x4C | [V] |
| 567c110+0x50 | 4 | [rdx+0x50]->[rcx+0x50] | `0x567c1b6  movss xmm0,[rdx+0x50]` `0x567c1bb  movss [rcx+0x50],xmm0` | copy float +0x50 | [V] |
| 567c110+0x54 | 4 | [rdx+0x54]->[rcx+0x54] | `0x567c1c0  movss xmm0,[rdx+0x54]` `0x567c1c5  movss [rcx+0x54],xmm0` | copy float +0x54 | [V] |
| 567c110+0x58 | 4 | [rdx+0x58]->[rcx+0x58] | `0x567c1ca  movss xmm0,[rdx+0x58]` `0x567c1cf  movss [rcx+0x58],xmm0` | copy float +0x58 | [V] |
| 567c110+0x5C | 4 | [rdx+0x5C]->[rcx+0x5C] | `0x567c1d4  movss xmm0,[rdx+0x5C]` `0x567c1d9  movss [rcx+0x5C],xmm0` | copy float +0x5C | [V] |
| 567c110+0x60 | 4 | [rdx+0x60]->[rcx+0x60] | `0x567c1de  movss xmm0,[rdx+0x60]` `0x567c1e3  movss [rcx+0x60],xmm0` | copy float +0x60 | [V] |
| 567c110+0x64 | 4 | [rdx+0x64]->[rcx+0x64] | `0x567c1e8  movss xmm0,[rdx+0x64]` `0x567c1ed  movss [rcx+0x64],xmm0` | copy float +0x64 | [V] |
| 567c110+0x68 | 4 | [rdx+0x68]->[rcx+0x68] | `0x567c1f2  movss xmm0,[rdx+0x68]` `0x567c1f7  movss [rcx+0x68],xmm0` | copy float +0x68 | [V] |
| 567c110+0x6C | 4 | [rdx+0x6C]->[rcx+0x6C] | `0x567c1fc  movss xmm0,[rdx+0x6C]` `0x567c201  movss [rcx+0x6C],xmm0` | copy float +0x6C | [V] |
| 567c110+0x70 | 4 | [rdx+0x70]->[rcx+0x70] | `0x567c206  movss xmm0,[rdx+0x70]` `0x567c20b  movss [rcx+0x70],xmm0` | copy float +0x70 | [V] |
| 567c110+0x74 | 4 | [rdx+0x74]->[rcx+0x74] | `0x567c210  movss xmm0,[rdx+0x74]` `0x567c215  movss [rcx+0x74],xmm0` | copy float +0x74 | [V] |
| 567c110+0x78 | 4 | [rdx+0x78]->[rcx+0x78] | `0x567c21a  movss xmm0,[rdx+0x78]` `0x567c21f  movss [rcx+0x78],xmm0` | copy float +0x78 | [V] |
| 567c110+0x7C | 4 | [rdx+0x7C]->[rcx+0x7C] | `0x567c224  movss xmm0,[rdx+0x7C]` `0x567c229  movss [rcx+0x7C],xmm0` | copy float +0x7C | [V] |
| 567c110+0x80 | 4 | [rdx+0x80]->[rcx+0x80] | `0x567c22e  movss xmm0,[rdx+0x80]` `0x567c236  movss [rcx+0x80],xmm0` | copy float +0x80 | [V] |
| 567c110+0x84 | 4 | [rdx+0x84]->[rcx+0x84] | `0x567c23e  movss xmm0,[rdx+0x84]` `0x567c246  movss [rcx+0x84],xmm0` | copy float +0x84 | [V] |
| 567c110+0x88 | 4 | [rdx+0x88]->[rcx+0x88] | `0x567c24e  movss xmm0,[rdx+0x88]` `0x567c256  movss [rcx+0x88],xmm0` | copy float +0x88 | [V] |
| 567c110+0x8C | 4 | [rdx+0x8C]->[rcx+0x8C] | `0x567c25e  movss xmm0,[rdx+0x8C]` `0x567c266  movss [rcx+0x8C],xmm0` | copy float +0x8C | [V] |
| 567c110+0x90 | 4 | [rdx+0x90]->[rcx+0x90] | `0x567c26e  movss xmm0,[rdx+0x90]` `0x567c276  movss [rcx+0x90],xmm0` | copy float +0x90 | [V] |
| 567c110+0x94 | 4 | [rdx+0x94]->[rcx+0x94] | `0x567c27e  movss xmm0,[rdx+0x94]` `0x567c286  movss [rcx+0x94],xmm0` | copy float +0x94 | [V] |
| 567c110+0x98 | 4 | [rdx+0x98]->[rcx+0x98] | `0x567c28e  movss xmm0,[rdx+0x98]` `0x567c296  movss [rcx+0x98],xmm0` | copy float +0x98 | [V] |
| 567c110+0x9C | 4 | [rdx+0x9C]->[rcx+0x9C] | `0x567c29e  movss xmm0,[rdx+0x9C]` `0x567c2a6  movss [rcx+0x9C],xmm0` | copy float +0x9C | [V] |
| 567c110+0xA0 | 4 | [rdx+0xA0]->[rcx+0xA0] | `0x567c2ae  movss xmm0,[rdx+0xA0]` `0x567c2b6  movss [rcx+0xA0],xmm0` | copy float +0xA0 | [V] |
| 567c110+0xA4 | 4 | [rdx+0xA4]->[rcx+0xA4] | `0x567c2be  movss xmm0,[rdx+0xA4]` `0x567c2c6  movss [rcx+0xA4],xmm0` | copy float +0xA4 | [V] |
| 567c110+0xA8 | 4 | [rdx+0xA8]->[rcx+0xA8] | `0x567c2ce  movss xmm0,[rdx+0xA8]` `0x567c2d6  movss [rcx+0xA8],xmm0` | copy float +0xA8 | [V] |
| 567c110+0xAC | 4 | [rdx+0xAC]->[rcx+0xAC] | `0x567c2de  movss xmm0,[rdx+0xAC]` `0x567c2e6  movss [rcx+0xAC],xmm0` | copy float +0xAC | [V] |
| 567c110+0xB0 | 4 | [rdx+0xB0]->[rcx+0xB0] | `0x567c2ee  movss xmm0,[rdx+0xB0]` `0x567c2f6  movss [rcx+0xB0],xmm0` | copy float +0xB0 | [V] |
| 567c110+0xB4 | 4 | [rdx+0xB4]->[rcx+0xB4] | `0x567c2fe  movss xmm0,[rdx+0xB4]` `0x567c306  movss [rcx+0xB4],xmm0` | copy float +0xB4 | [V] |
| 567c110+0xB8 | 4 | [rdx+0xB8]->[rcx+0xB8] | `0x567c30e  movss xmm0,[rdx+0xB8]` `0x567c316  movss [rcx+0xB8],xmm0` | copy float +0xB8 | [V] |
| 567c110+0xBC | 4 | [rdx+0xBC]->[rcx+0xBC] | `0x567c31e  movss xmm0,[rdx+0xBC]` `0x567c326  movss [rcx+0xBC],xmm0` | copy float +0xBC | [V] |
| 567c110+0xC0 | 4 | [rdx+0xC0]->[rcx+0xC0] | `0x567c32e  movss xmm0,[rdx+0xC0]` `0x567c336  movss [rcx+0xC0],xmm0` | copy float +0xC0 | [V] |
| 567c110+0xC4 | 4 | [rdx+0xC4]->[rcx+0xC4] | `0x567c33e  movss xmm0,[rdx+0xC4]` `0x567c346  movss [rcx+0xC4],xmm0` | copy float +0xC4 | [V] |
| 567c110+0xC8 | 4 | [rdx+0xC8]->[rcx+0xC8] | `0x567c34e  movss xmm0,[rdx+0xC8]` `0x567c356  movss [rcx+0xC8],xmm0` | copy float +0xC8 | [V] |
| 567c110+0xCC | 4 | [rdx+0xCC]->[rcx+0xCC] | `0x567c35e  movss xmm0,[rdx+0xCC]` `0x567c366  movss [rcx+0xCC],xmm0` | copy float +0xCC | [V] |
| 567c110+0xD0 | 4 | [rdx+0xD0]->[rcx+0xD0] | `0x567c36e  movss xmm0,[rdx+0xD0]` `0x567c376  movss [rcx+0xD0],xmm0` | copy float +0xD0 | [V] |
| 567c110+0xD4 | 16 | [rdx+0xD4]->[rcx+0xD4] | `0x567c37e  movups xmm0,[rdx+0xD4]` `0x567c385  movups [rcx+0xD4],xmm0` | copy 16-byte block +0xD4 | [V] |
| 567c110+0xE4 | 4 | [rdx+0xE4]->[rcx+0xE4] | `0x567c38c  mov eax,[rdx+0xE4]` `0x567c392  mov [rcx+0xE4],eax` | copy dword +0xE4 | [V] |
| call@0x567c3a6 | 5 | - | `0x567c3a6  call 0x119b5f0` | helper copies block at dest+0xE8..0x107 (both ptrs advanced by 0xE8 first) | [I] |
| 567c110+0x108 | 8 | [rdi+0x108]->[rsi+0x108] | `0x567c3b7  mov rax,[rdi+0x108]` `0x567c3be  mov [rsi+0x108],rax` | copy qword +0x108 | [V] |
| 567c110+0x110 | 4 | [rdi+0x110]->[rsi+0x110] | `0x567c3ab  mov eax,[rdi+0x110]` `0x567c3b1  mov [rsi+0x110],eax` | copy dword +0x110 | [V] |
| 567c110+0x118 | 8 | [rdi+0x118]->[rsi+0x118] | `0x567c3c5  mov rax,[rdi+0x118]` `0x567c3cc  mov [rsi+0x118],rax` | copy qword +0x118 | [V] |
| 567c110+0x120 | 1 | [rdi+0x120]->[rsi+0x120] | `0x567c3d3  movzx eax,byte ptr [rdi+0x120]` `0x567c3da  mov [rsi+0x120],al` | copy byte +0x120 | [V] |

### sub_568bdc0 — large record per-pass body (10 builder sites). Args: r14=dest (rcx), r8=a2 (rsi), r9=a3 (rdi), rdx=a2. Builds dest record dest+0x0..0x2D8: vtable data_f25c7b0, SSO/string transfers from a3 (stealing source pointers), refcounted handle at a2+0x38 -> dest+0x70, conditional blocks gated on [a3+0x60], [a3+0x214], [a3+0x1D0], [a3+0x218], and helper sub_5669770 for dest+0xF0..
| 568bdc0+0x0 | 8 | [rcx+0x0] write | `0x568be0a  mov [rcx],rax` (rax = vtable data_f25c7b0) | dest+0 = vtable ptr | [V] |
| 568bdc0+0x8 | 16 | [rcx+0x8] write | `0x568bdef  movups [rcx+8],xmm6` | dest+0x8 = 0 | [V] |
| 568bdc0+0x18 | 16 | [rcx+0x18] write | `0x568bdeb  movups [rcx+0x18],xmm6` | dest+0x18 = 0 | [V] |
| 568bdc0+0x28 | 8 | [rcx+0x28] write | `0x568bdf3  mov qword ptr [rcx+0x28],0xF` | dest+0x28 = 0xF | [V] |
| 568bdc0+0x30 | 8 | [rcx+0x30] write | `0x568bdfb  mov qword ptr [rcx+0x30],0` | dest+0x30 = 0 | [V] |
| 568bdc0+0x70 | 8 | [r14+0x70] write | `0x568be11  mov qword ptr [rcx+0x70],0` `0x568be2a  mov [r14+0x70],rcx` `0x568be40  mov [r14+0x70],rax` | dest+0x70 = 0 -> a2+0x38 -> refcounted result | [V] |
| 568bdc0+0x78 | 8 | [r14+0x78] write | `0x568be6b  mov [r14+0x78],rax` (rax=[rdi]) | dest+0x78 = a3+0x0 | [V] |
| 568bdc0+0x80 | 8 | [r14+0x80] write | `0x568be7b  mov [r14+0x80],rax` ([rdi+8]) | dest+0x80 = a3+0x8 (source cleared after) | [V] |
| 568bdc0+0x88 | 8 | [r14+0x88] write | `0x568be86  mov [r14+0x88],rax` ([rdi+0x10]) | dest+0x88 = a3+0x10 | [V] |
| 568bdc0+0x90 | 16 | [r14+0x90] write | `0x568be91  movups [r14+0x90],xmm6` | dest+0x90 = 0 | [V] |
| 568bdc0+0xA0 | 8 | [r14+0xA0] write | `0x568be99  mov qword ptr [r14+0xA0],0` | dest+0xA0 = 0 | [V] |
| 568bdc0+0xA8 | 1 | [r14+0xA8] write | `0x568bea8  mov [r14+0xA8],al` ([rdi+0x30]) | dest+0xA8 = a3+0x30 byte | [V] |
| 568bdc0+0xD8 | 1 | [r14+0xD8] write | `0x568beaf  mov byte ptr [r14+0xD8],0` `0x568beef  mov byte ptr [r14+0xD8],1` | flag 0 -> 1 | [V] |
| 568bdc0+0xB0 | 8 | [r14+0xB0] write | `0x568bec1  mov [r14+0xB0],rax` ([rdi+0x38], gated [rdi+0x60]==1) | dest+0xB0 = a3+0x38 | [V] |
| 568bdc0+0xB8 | 16 | [r14+0xB8] write | `0x568bedf  movups [r14+0xB8],xmm0` ([rdi+0x40]) | dest+0xB8 = a3+0x40 | [V] |
| 568bdc0+0xC8 | 16 | [r14+0xC8] write | `0x568bee7  movups [r14+0xC8],xmm1` ([rdi+0x50]) | dest+0xC8 = a3+0x50 | [V] |
| 568bdc0+0xE0 | 16 | [r14+0xE0] write | `0x568befb  movups [r14+0xE0],xmm0` ([rdi+0x68]) | dest+0xE0 = a3+0x68 | [V] |
| call@0x568bf0e | 5 | - | `0x568bf0e  call 0x5669770` | helper: dest+0xF0.. from a3+0x78 | [V] |
| 568bdc0+0x28C | 1 | [r14+0x28C] write | `0x568bf13  mov byte ptr [r14+0x28C],0` `0x568bfed  mov byte ptr [r14+0x28C],1` | flag 0 -> 1 | [V] |
| 568bdc0+0x214 | 16 | [r14+0x214] write | `0x568bf3e  movups [r14+0x214],xmm0` ([rdi+0x19C], gated [rdi+0x214]==1) | dest+0x214 = a3+0x19C | [V] |
| 568bdc0+0x224 | 16 | [r14+0x224] write | `0x568bf36  movups [r14+0x224],xmm1` ([rdi+0x1AC]) | dest+0x224 = a3+0x1AC | [V] |
| 568bdc0+0x248 | 1 | [r14+0x248] write | `0x568bf46  mov byte ptr [r14+0x248],0` `0x568bfa9  mov byte ptr [r14+0x248],1` | flag 0 -> 1 | [V] |
| 568bdc0+0x234 | 1 | [r14+0x234] write | `0x568bf5e  mov [r14+0x234],al` ([rdi+0x1BC], gated [rdi+0x1D0]==1) | dest+0x234 = a3+0x1BC byte | [V] |
| 568bdc0+0x238 | 4 | [r14+0x238] write | `0x568bf6d  movss [r14+0x238],xmm0` ([rdi+0x1C0]) | dest+0x238 = a3+0x1C0 float | [V] |
| 568bdc0+0x23C | 4 | [r14+0x23C] write | `0x568bf7e  movss [r14+0x23C],xmm0` ([rdi+0x1C4]) | dest+0x23C = a3+0x1C4 float | [V] |
| 568bdc0+0x240 | 4 | [r14+0x240] write | `0x568bf8f  movss [r14+0x240],xmm0` ([rdi+0x1C8]) | dest+0x240 = a3+0x1C8 float | [V] |
| 568bdc0+0x244 | 4 | [r14+0x244] write | `0x568bfa0  movss [r14+0x244],xmm0` ([rdi+0x1CC]) | dest+0x244 = a3+0x1CC float | [V] |
| 568bdc0+0x24C | 16 | [r14+0x24C] write | `0x568bfe5  movups [r14+0x24C],xmm0` ([rdi+0x1D4]) | dest+0x24C = a3+0x1D4 | [V] |
| 568bdc0+0x25C | 16 | [r14+0x25C] write | `0x568bfdd  movups [r14+0x25C],xmm1` ([rdi+0x1E4]) | dest+0x25C = a3+0x1E4 | [V] |
| 568bdc0+0x26C | 16 | [r14+0x26C] write | `0x568bfd5  movups [r14+0x26C],xmm2` ([rdi+0x1F4]) | dest+0x26C = a3+0x1F4 | [V] |
| 568bdc0+0x27A | 16 | [r14+0x27A] write | `0x568bfcd  movups [r14+0x27A],xmm3` ([rdi+0x202]) | dest+0x27A = a3+0x202 | [V] |
| 568bdc0+0x290 | 16 | [r14+0x290] write | `0x568c00e  movups [r14+0x290],xmm0` `0x568c073  mov [r14+0x290],rax` ([rax]=[rsi+0x0]) | dest+0x290 = 0 -> string ptr | [V] |
| 568bdc0+0x298 | 16 | [r14+0x298] write | `0x568c047  movups [r14+0x298],xmm1` ([rdi+0x220], gated [rdi+0x218] chain) | dest+0x298 = a3+0x220 | [V] |
| 568bdc0+0x2A0 | 16 | [r14+0x2A0] write | `0x568c006  movups [r14+0x2A0],xmm0` | dest+0x2A0 = 0 | [V] |
| 568bdc0+0x2A8 | 16 | [r14+0x2A8] write | `0x568c03f  movups [r14+0x2A8],xmm2` ([rdi+0x230]) | dest+0x2A8 = a3+0x230 | [V] |
| 568bdc0+0x2B0 | 8 | [r14+0x2B0] write | `0x568c016  mov qword ptr [r14+0x2B0],0xF` | dest+0x2B0 = 0xF | [V] |
| 568bdc0+0x2B8 | 8 | [r14+0x2B8] write | `0x568c021  mov qword ptr [r14+0x2B8],0` | dest+0x2B8 = 0 | [V] |
| 568bdc0+0x2C0 | 16 | [r14+0x2C0] write | `0x568c07a  movups [r14+0x2C0],xmm0` | dest+0x2C0 = 0 | [V] |
| 568bdc0+0x2D0 | 16 | [r14+0x2D0] write | `0x568c082  movups [r14+0x2D0],xmm0` `0x568c132  mov [r14+0x2D0],rdi` | dest+0x2D0 = 0 -> a3 copy ptr | [V] |
| 568bdc0+0x2D8 | 8 | [r14+0x2D8] write | `0x568c139  mov [r14+0x2D8],r12` | dest+0x2D8 = size (0x16/0xF) | [V] |
| 568bdc0+a2+0x38 | 8 | [rdx+0x38] read | `0x568be19  mov rcx,[rdx+0x38]` | a2+0x38 (feeds dest+0x70) | [V] |
| 568bdc0+a3+0x60 | 1 | [rdi+0x60] read | `0x568beb7  cmp byte ptr [rdi+0x60],1` | a3+0x60 gate | [V] |
| 568bdc0+a3+0x214 | 1 | [rdi+0x214] read | `0x568bf1b  cmp byte ptr [rdi+0x214],1` | a3+0x214 gate | [V] |
| 568bdc0+a3+0x1D0 | 1 | [rdi+0x1D0] read | `0x568bf4e  cmp byte ptr [rdi+0x1D0],1` | a3+0x1D0 gate | [V] |

### sub_567e510 / sub_567fd70 / sub_56815d0 / sub_5682e20 / sub_5684660 / sub_5685ea0 / sub_56876f0 — element-loop per-pass bodies (one builder site each). Same shape: 0xA18 stack; read a1+0x10/+0x18 (SSO string), a1+0x28, a1+0x60; loop r14 from [a1+0x240] to [a1+0xE0) stride 0x290; per element build local block at rbp+0x560 (vtable data_f25b4f0/f25b550/f25b5b0/f25b610/f25b670/f25b6d0/f25b730) via sub_e935700-managed strings. Per-element fill and any dest writes not decoded [?]. Entry reads [V]:
| 567e510+a1+0x10 | 8 | [rdx+0x10] read | `0x567e552  mov r14,[rdx+0x10]` | a1+0x10 SSO ptr | [V] |
| 567e510+a1+0x18 | 8 | [rdx+0x18] read | `0x567e556  mov rax,[rdx+0x18]` | a1+0x18 SSO length vs 0x10 | [V] |
| 567e510+a1+0x28 | 8 | [rdx+0x28] read | `0x567e561  lea rax,[rdx+0x28]` | a1+0x28 address | [V] |
| 567e510+a1+0x60 | 8 | [rdx+0x60] read | `0x567e588  lea rax,[rdx+0x60]` | a1+0x60 address | [V] |
| 567fd70+a1+0x10 | 8 | [rdx+0x10] read | `0x567fdb2  mov r14,[rdx+0x10]` | a1+0x10 SSO ptr | [V] |
| 567fd70+a1+0x18 | 8 | [rdx+0x18] read | `0x567fdb6  mov rax,[rdx+0x18]` | a1+0x18 SSO length vs 0x10 | [V] |
| 567fd70+a1+0x28 | 8 | [rdx+0x28] read | `0x567fdc1  lea rax,[rdx+0x28]` | a1+0x28 address | [V] |
| 567fd70+a1+0x60 | 8 | [rdx+0x60] read | `0x567fde8  lea rax,[rdx+0x60]` | a1+0x60 address | [V] |
| 56815d0+a1+0x10 | 8 | [rdx+0x10] read | `0x5681612  mov r14,[rdx+0x10]` | a1+0x10 SSO ptr | [V] |
| 56815d0+a1+0x18 | 8 | [rdx+0x18] read | `0x5681616  mov rax,[rdx+0x18]` | a1+0x18 SSO length vs 0x10 | [V] |
| 56815d0+a1+0x28 | 8 | [rdx+0x28] read | `0x5681621  lea rax,[rdx+0x28]` | a1+0x28 address | [V] |
| 56815d0+a1+0x60 | 8 | [rdx+0x60] read | `0x5681648  lea rax,[rdx+0x60]` | a1+0x60 address | [V] |
| 5682e20+a1+0x10 | 8 | [rdx+0x10] read | `0x5682e62  mov r14,[rdx+0x10]` | a1+0x10 SSO ptr | [V] |
| 5682e20+a1+0x18 | 8 | [rdx+0x18] read | `0x5682e66  mov rax,[rdx+0x18]` | a1+0x18 SSO length vs 0x10 | [V] |
| 5682e20+a1+0x28 | 8 | [rdx+0x28] read | `0x5682e71  lea rax,[rdx+0x28]` | a1+0x28 address | [V] |
| 5682e20+a1+0x60 | 8 | [rdx+0x60] read | `0x5682e98  lea rax,[rdx+0x60]` | a1+0x60 address | [V] |
| 5684660+a1+0x10 | 8 | [rdx+0x10] read | `0x56846a2  mov r14,[rdx+0x10]` | a1+0x10 SSO ptr | [V] |
| 5684660+a1+0x18 | 8 | [rdx+0x18] read | `0x56846a6  mov rax,[rdx+0x18]` | a1+0x18 SSO length vs 0x10 | [V] |
| 5684660+a1+0x28 | 8 | [rdx+0x28] read | `0x56846b1  lea rax,[rdx+0x28]` | a1+0x28 address | [V] |
| 5684660+a1+0x60 | 8 | [rdx+0x60] read | `0x56846d8  lea rax,[rdx+0x60]` | a1+0x60 address | [V] |
| 5685ea0+a1+0x10 | 8 | [rdx+0x10] read | `0x5685ee2  mov r14,[rdx+0x10]` | a1+0x10 SSO ptr | [V] |
| 5685ea0+a1+0x18 | 8 | [rdx+0x18] read | `0x5685ee6  mov rax,[rdx+0x18]` | a1+0x18 SSO length vs 0x10 | [V] |
| 5685ea0+a1+0x28 | 8 | [rdx+0x28] read | `0x5685ef1  lea rax,[rdx+0x28]` | a1+0x28 address | [V] |
| 5685ea0+a1+0x60 | 8 | [rdx+0x60] read | `0x5685f18  lea rax,[rdx+0x60]` | a1+0x60 address | [V] |
| 56876f0+a1+0x10 | 8 | [rdx+0x10] read | `0x5687732  mov r14,[rdx+0x10]` | a1+0x10 SSO ptr | [V] |
| 56876f0+a1+0x18 | 8 | [rdx+0x18] read | `0x5687736  mov rax,[rdx+0x18]` | a1+0x18 SSO length vs 0x10 | [V] |
| 56876f0+a1+0x28 | 8 | [rdx+0x28] read | `0x5687741  lea rax,[rdx+0x28]` | a1+0x28 address | [V] |
| 56876f0+a1+0x60 | 8 | [rdx+0x60] read | `0x5687768  lea rax,[rdx+0x60]` | a1+0x60 address | [V] |

## CLOSES?
NO — blocking fact: 7 element-loop per-pass bodies (sub_567E510, sub_567FD70, sub_56815D0, sub_5682E20, sub_5684660, sub_5685EA0, sub_56876F0) are entry-decoded only (their source reads at a1+0x10/0x18/0x28/0x60 and the 0x290-stride element loop are [V], but per-element fill and any dest writes are not), and the tail of sub_bbe2d50 plus the undecoded 0x569xxxx helper set (sub_5693680, sub_5694510, sub_5695960, sub_5696540, sub_5697650 per oc_U-EF1b.md) remain unproven — so not every pending per-pass instantiation of the 178 drawutils signatures is [V]-proven.

## TOOL REQUESTS
None
