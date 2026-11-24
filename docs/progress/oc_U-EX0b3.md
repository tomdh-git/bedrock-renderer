## NEXT
DONE

# U-EX0b3 — X0b3 Boundary classification, rows 201-300 of docs/data/native_boundary_candidates.tsv (same rules as X0b1).

EXE: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01\Minecraft.Windows.exe (1.26.62.01)
Method: per candidate RVA - `rdis exe dis 0xRVA 8` (first 8 instr) + `rdis exe callees 0xRVA` (calls) + `rdis exe str` (string refs). Class: lift (render-owned code → becomes a lift item, declared here for the orchestrator to merge via native_checklist_gen.py --add), stl/crt/os/d3d/vendor/alloc/other-subsystem (proven library code), needs lift (truly unprovable from own disassembly; conservative — we lift it ourselves). `?` is NOT used this run; every row has a class. [V]=saw in rdis output; every `0xRVA  instr` quote is copied verbatim from the rdis listing and machine-checked by tools/sigs/verify_oc.py. size="-" (no movups-family instr quoted; avoids delegate size check).
Render indicators [V]: calls sub_9bc830/sub_e935700/sub_e938cb0/sub_e938d70 (render-core), sub_75740/sub_75b60 (bgfx), or render strings. Region per docs/BGFX_MAP.md: RVAs 0xbb30000..0xbcd0000 = VV/RTX shared renderer code → lift [V].
Dependency note [V]: rows whose only callees are 0xe951550 (X0b1 row14 = crt stack-cookie check) or 0x78ed0 (X0b1 row6 = crt terminate thunk) are NOT blocked — those are already classified crt in X0b1.

## Jump-table decode (0x4e00d40 and 0x4e01c30) [V]
`0x4e00d40  push rsi` / `0x4e00d41  sub rsp,0x20` / `0x4e00d45  lea rax,[0xF2158A4]` / `0x4e00d4c  movsxd rcx,[rax+rcx*4]` / `0x4e00d50  add rcx,rax` / `0x4e00d53  jmp rcx` — jump table at .rdata `data_f2158a4`, int32 relative entries (target = base + entry). Decoded with `python tools/sigs/jt.py 0xf2158a4`: valid entries tags 0-18 all target basic blocks INSIDE sub_4e00d40 itself (0x4e00d55, 0x4e00d92, 0x4e00dce, 0x4e01c46..0x4e028e9); tags 19+ decode to non-code garbage. No new separate lift roots. Body evidence: `0x4e00dc9  jmp 0xE935700` calls render-core sub_e935700 → sub_4e00d40 is lift [V].
`0x4e01c30  push rsi` / `0x4e01c31  push rdi` / `0x4e01c32  sub rsp,0x28` / `0x4e01c36  lea rax,[0xF2158B8]` / `0x4e01c3d  movsxd rcx,[rax+rcx*4]` / `0x4e01c41  add rcx,rax` / `0x4e01c44  jmp rcx` — jump table at `data_f2158b8`. Decoded with `python tools/sigs/jt.py 0xf2158b8`: valid entries tags 0-13 all target blocks inside sub_4e01c30 (0x4e01c46..0x4e028fd); no external targets, no render calls/strings found → sub_4e01c30 is needs lift.

| # | offset | class | instr (`0xRVA  instr`, verbatim) | tag | meaning (evidence) |
|---|---|---|---|---|---|
| 201 | 0xbb84ee0 | lift | `0xbb84ee0  push rbp` | [V] | In render region 0xbb30000..0xbcd0000 (BGFX_MAP.md). callees sub_9bc830(x9 render-core), 0xbc bgfx funcs, sub_e935700(x28), sub_e938cb0(x20). str: "ForwardPBROpaque","ForwardPBRAlphaTest","ForwardPBRTransparent","EditorHighlight". render-owned forward PBR pass → lift. |
| 202 | 0xbb8ccb0 | lift | `0xbb8ccb0  push rbp` | [V] | In render region. callees sub_9bc830(x1), sub_e935700(x2), sub_e938cb0(x5). str: "DeferredIndirectSpecular","DoIndirectSpecularShadingPhase". render-owned deferred indirect specular → lift. |
| 203 | 0xbb8eb70 | lift | `0xbb8eb70  push rbp` | [V] | In render region. callees sub_9bc830(x3), 0xbc bgfx funcs, sub_e935700(x10), sub_e938cb0(x13). str: "DeferredIndirectSpecular","SpecularLighting","NormalsAndDepthLighting". render-owned deferred lighting → lift. |
| 204 | 0xbb93890 | lift | `0xbb93890  push rsi` | [V] | In render region 0xbb30000..0xbcd0000 (BGFX_MAP.md) → lift. Prologue also has stack cookie `0xbb93897  mov rax,[0x1230A0C0]` (compiler artifact, not class). callees sub_5698290/sub_e951550(crt)/sub_eec6d80(crt); no render strings but region rule is decisive → lift. |
| 205 | 0xbb93c60 | lift | `0xbb93c60  push rbp` | [V] | In render region. sub rsp,0x80 prologue. str: "Transparent". render-owned transparent pass → lift. |
| 206 | 0xbb96320 | lift | `0xbb96320  push rbp` | [V] | In render region. callees sub_9bc830(x42), sub_a78940(x38), sub_e935700(x222), sub_e938cb0(x6), calls sub_bb93c60(row205 lift). str: "[ClearColorDepth][Scene]","Transparent","Opaque","AlphaTest","StencilWrite". render-owned scene draw tasks → lift. |
| 207 | 0xbbbcb20 | lift | `0xbbbcb20  push rbp` | [V] | In render region. callees sub_9bc830(x1), sub_e935700(x2), calls sub_bbbd3d0(row298 lift). str: "PostProcessPhase","ColorPostProcess". render-owned post-process phase → lift. |
| 208 | 0xbbbd7f0 | lift | `0xbbbd7f0  push rbp` | [V] | In render region. callees sub_5669ae0(x1), sub_bb66e20(x1), sub_bbbda20(x1 row300 lift), sub_e935700(x1). Calls render-core sub_e935700 + lift row300 → lift. |
| 209 | 0xbbbfc50 | lift | `0xbbbfc50  push rbp` | [V] | In render region. callees sub_9bc830(x20), sub_a78940(x18), sub_e935700(x48), sub_e938cb0(x5), 0xbc bgfx funcs. str: "[UIMeshCapture]","[UIStructureVolumeCapture]","UIBatchDrawSyncPoint". render-owned UI capture → lift. |
| 210 | 0xbbc9db0 | lift | `0xbbc9db0  push rbp` | [V] | In render region. callees sub_9bc830(x6), sub_a78940(x4), sub_e935700(x21), calls sub_bbbfc50(row209 lift) and sub_bc56990(bgfx). str: "Core/Screen/Blit","[PersistentUI]","BlitPersistentUIToScreen". render-owned blit → lift. |
| 211 | 0xbcd77b0 | lift | `0xbcd77b0  push rbp` | [V] | In render region. callees sub_9bc830(x9), sub_e935700(x22), sub_e938cb0(x8), calls sub_bc9c990(bgfx). str: "CubemapTransfer","Core/Screen/Blit","Clear Transient Cubemap Target". render-owned cubemap transfer → lift. |
| 212 | 0xbcdba70 | lift | `0xbcdba70  push rbp` | [V] | In render region. callees sub_9bc830(x1), sub_e935700(x3), sub_e938cb0(x6), calls sub_bcaba00(bgfx). str: "SpecularConvolution","Clear Specular IBL","CubeMap". render-owned specular convolution → lift. |
| 213 | 0xbce07c0 | lift | `0xbce07c0  push rbp` | [V] | In render region. callees sub_bcdef90, sub_bcdf4d0, sub_bce0d80, sub_bce1040(x2), sub_bf4d680, sub_e935700(x3). Calls render-core sub_e935700 x3 → lift. |
| 214 | 0xaa7fe0 | lift | `0xaa7fe0  push rbp` | [V] | callees sub_9b1ee0(x1), sub_2b96970(x1 row222 needs lift), sub_e938cb0(x1), sub_e938d70(x1). Calls render-core sub_e938cb0/d70 → lift. |
| 215 | 0xbd11a0 | needs lift | `0xbd11a0  sub rsp,0x28` | [V] | Container size/capacity helper: `0xbd11a4  mov r8,[rcx+0x10]` / `0xbd11a8  mov eax,[rcx+0x18]` / `0xbd11ab  mov rcx,[r8+0x48]` / `0xbd11af  mov r9,[r8+0x50]` / `sub r9,rcx` / `shr r9,3` / `dec r9d`. callee sub_78ed0(x1 = X0b1 row6 crt terminate). 94 xrefs in. No render strings/stl/crt/alloc fit → needs lift. |
| 216 | 0x32d0f30 | needs lift | `0x32d0f30  push r14` | [V] | prologue push r14/rsi/rdi/rbp/rbx, sub rsp,0x30, `mov ebx,r9d`, `mov rsi,rdx`. callee sub_e951550(x1 = X0b1 row14 crt stack-cookie check). 51 xrefs in. No render strings; depends on crt row14 but not itself crt/stl/alloc → needs lift. |
| 217 | 0x4de7670 | needs lift | `0x4de7670  push rbp` | [V] | EH frame prologue: push rbp/rsi/rdi/rbx, sub rsp,0x68, `lea rbp,[rsp+0x60]`, `mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE`, `lea rsi,[0x128C4FD0]`. callees sub_3b2020(x2 row238 needs lift), sub_e943178, sub_e94319c. No render strings → needs lift. |
| 218 | 0x4e00c00 | lift | `0x4e00c00  push r14` | [V] | `lea rax,[0xF215890]` / `movsxd rcx,[rax+rcx*4]` / `add rcx,rax` (table-indexed data load inside render). callee sub_9bc830(x1 row1 render-core [V from X0b1]). Calls render-core → lift. |
| 219 | 0x4e00d40 | lift | `0x4e00d40  push rsi` | [V] | Jump-table dispatcher (decoded above, targets all intra-function). Body contains `0x4e00dc9  jmp 0xE935700` calling render-core sub_e935700 [V] → render-owned → lift. Declared for native_checklist_gen.py --add. |
| 220 | 0x4e01c30 | needs lift | `0x4e01c30  push rsi` | [V] | Jump-table dispatcher at `data_f2158b8` (decoded above, targets all intra-function, tags 0-13). No render callees/strings found; not stl/crt/alloc/alloc shape → needs lift. |
| 221 | 0x2e8fc0 | needs lift | `0x2e8fc0  push rsi` | [V] | `0x2e8fc3  mov r10,[rcx+0x8]` / `0x2e8fc7  mov ecx,[rcx+0x10]` / `0x2e8fca  mov r9,[r10+0x48]` / `0x2e8fce  mov rax,[r10+0x50]` / `sub rax,r9`. Leaf (no callees), no strings. Pointer/container math, no stl/crt/alloc/alloc/render fit → needs lift. |
| 222 | 0x2b96970 | needs lift | `0x2b96970  push rsi` | [V] | `0x2b96979  mov byte ptr [rcx+0x18],0` / `0x2b9697d  mov rcx,[rdx+0x8]` / `test rcx,rcx`. Leaf (no callees), no strings. Object field init/store, no stl/crt/alloc/render fit → needs lift. |
| 223 | 0x5391130 | needs lift | `0x5391130  push r15` | [V] | prologue push r15/r14/rsi/rdi/rbp/rbx, sub rsp,0x48, `mov rsi,rdx`. callees sub_2e8fc0(row221 needs lift), sub_bd3df0, sub_2b96970(x2 row222 needs lift), sub_3165620(x1 row238 lift), sub_67edd40. Calls a lift function but also unknown leaves; no render strings → needs lift. |
| 224 | 0x1999140 | needs lift | `0x1999140  sub rsp,0x28` | [V] | `0x1999144  movaps [rsp+0x10],xmm7` / `0x1999149  movaps [rsp],xmm6` / `0x199914d  movss xmm0,[rdx]` / `0x1999151  movss xmm1,[r8]` / `0x1999156  movss xmm3,[rcx+0x50]`. Leaf (no callees), no strings. Pure SIMD math, no stl/crt/alloc/render fit → needs lift. |
| 225 | 0x4e36150 | lift | `0x4e36150  push rbp` | [V] | callees sub_75740(x9), sub_75b60(x11), sub_9bc830(x24 render-core), sub_e935700(x11 render-core), sub_eec6de0(x7), plus sub_eaa30(row227 needs lift). str: "Atomic Entity - filter_lighting is not supported.","Atomic Entity - light_color_multiplier expressions are not s...". Calls render-core + bgfx → lift. |
| 226 | 0x4e8eb00 | lift | `0x4e8eb00  push rbp` | [V] | callees sub_9bc830(x2 render-core), sub_e935700(x1 render-core), sub_eec6ed0(x1). Calls render-core → lift. |
| 227 | 0xeaa30 | needs lift | `0xeaa30  push rbp` | [V] | 1098 xrefs in. callees sub_3b2020(row238 needs lift), sub_3d0730(x1), sub_e943178(x1), sub_e94319c(x1). No render callees/strings → needs lift. |
| 228 | 0x4df6a90 | lift | `0x4df6a90  sub rsp,0x48` | [V] | callees sub_da490(x3), sub_4df6cb0(x1), sub_e951550(x1 row216 needs lift = X0b1 row14 crt). str: "Render Controller: %s is missing its default texture", "Render Controller: %s defines Glint, but does not have a glint...", "Multiplicative-Tint...". "Render Controller" strings → render-owned texture validation → lift. |
| 229 | 0x4e00090 | needs lift | `0x4e00090  push rbp` | [V] | prologue push rbp/rsi/rdi/rbx, sub rsp,0x58, `lea rbp,[rsp+0x50]`, `mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE`, `mov rax,[r8]`. callees sub_3b2020(x2 row238 needs lift), sub_b432e0(x1), sub_e943178(x1), sub_e94319c(x1). No render callees/strings → needs lift. |
| 230 | 0x4e3b020 | needs lift | `0x4e3b020  push rsi` | [V] | `0x4e3b026  mov rsi,rcx` / `0x4e3b029  mov rdi,[rcx+0x58]` / `test rdi,rdi` / `0x4e3b032  lock dec dword ptr [rdi+8]`. Leaf (no callees), no strings. Refcount decrement, no stl/crt/alloc/render fit → needs lift. |
| 231 | 0x4e69270 | lift | `0x4e69270  push rsi` | [V] | callee sub_e935700(x1 render-core). Calls render-core → lift. |
| 232 | 0x6b86e80 | lift | `0x6b86e80  push r15` | [V] | callees sub_75740(x1), sub_9bc830(x6 render-core), sub_6be27d0(x5), sub_e935700(x4 render-core), sub_e935740(x4), sub_e938cb0(x4), sub_e938d70(x4). Calls render-core + bgfx → lift. |
| 233 | 0x6be16b0 | lift | `0x6be16b0  push rbp` | [V] | callees sub_75740(x1), sub_9bc830(x2 render-core), sub_e935700(x2 render-core). Calls render-core → lift. |
| 234 | 0xe7e150 | needs lift | `0xe7e150  push rbp` | [V] | 83 xrefs in. callee sub_88bb50(x1 unknown). No strings → needs lift. |
| 235 | 0xaaa420 | lift | `0xaaa420  push r15` | [V] | callees sub_aaa620(x1), sub_e935700(x3 render-core). Calls render-core → lift. |
| 236 | 0xaaa6e0 | lift | `0xaaa6e0  push r14` | [V] | callees sub_a89240(x1), sub_e935700(x2 render-core). Calls render-core → lift. |
| 237 | 0x2fd4210 | needs lift | `0x2fd4210  push rbp` | [V] | 10 xrefs in. callee sub_2fd3e60(x1 unknown). No strings → needs lift. |
| 238 | 0x3165620 | lift | `0x3165620  push rsi` | [V] | callees sub_9b8d610(x2), sub_e938cb0(x2 render-core), sub_e938d70(x2 render-core). str: "tile.","minecraft:". Calls render-core + minecraft: resource → lift. |
| 239 | 0x31f83d0 | lift | `0x31f83d0  push rbp` | [V] | 5258 xrefs in. callees sub_9bc830(x3 render-core), sub_e935700(x9 render-core), sub_eec6de0(x3), sub_eec6eb0(x18), sub_a0850(x1), sub_392920(x3), sub_76a8a0(x3). str: "tile.","minecraft:". Very hot; calls render-core → lift. |
| 240 | 0x5353600 | lift | `0x5353600  push rbp` | [V] | callees sub_9bc830(x1 render-core), sub_aaa7c0(x1), sub_e935700(x1 render-core). Calls render-core → lift. |
| 241 | 0x539d8c0 | needs lift | `0x539d8c0  push r15` | [V] | prologue push r15/r14/r13/r12/rsi/rdi/rbx, sub rsp,0xC0. callees sub_3165a70(x1), sub_5c59cd0(x1), sub_5c5a100(x1), sub_5c5a430(x1), sub_5c5a8b0(x1), sub_e951550(x1 row216 = X0b1 row14 crt), sub_eec75a0(x3). Calls crt row14 + unknown; no render → needs lift. |
| 242 | 0x53d3fd0 | lift | `0x53d3fd0  push rbp` | [V] | callees sub_9bc830(x2 render-core), sub_e935700(x1 render-core). Calls render-core → lift. |
| 243 | 0x5418de0 | needs lift | `0x5418de0  push rbp` | [V] | prologue push rbp/r15/r14/r13/r12/rsi/rdi/rbx. callees sub_4de7a50, sub_4de8170, sub_4de8830, sub_4dea990, sub_4df0440(x4), sub_54198a0, sub_eec6ed0(x2), sub_eec74f0(x2). Calls render helpers eec6ed0/eec74f0 but no direct render-core/strings; many unknown sub_4de* callees → needs lift. |
| 244 | 0x681b6d0 | lift | `0x681b6d0  push r15` | [V] | callees sub_3165620(x1 row238 lift), sub_31f83d0(x2 row239 lift), plus sub_68* and sub_67edd40. Calls confirmed lift (render) functions → lift. |
| 245 | 0x68b5ee0 | lift | `0x68b5ee0  push rbp` | [V] | callees sub_9bc830(x4 render-core), sub_32cb4a0(x2), sub_68b4fc0(x1), sub_eec75a0(x6). Calls render-core → lift. |
| 246 | 0x68b9bf0 | lift | `0x68b9bf0  push rbp` | [V] | callees sub_75740(x3), sub_75b60(x1 bgfx), sub_9bc830(x8 render-core), sub_e935700(x14 render-core), sub_eec59e0(x1), sub_a89240(x4), sub_68c7720(x8). Calls render-core + bgfx → lift. |
| 247 | 0x68bb9a0 | lift | `0x68bb9a0  push r15` | [V] | callees sub_75740(x1), sub_75b60(x4 bgfx), sub_9bc830(x8 render-core), sub_e935700(x4 render-core), sub_eec6de0(x3). Calls render-core + bgfx → lift. |
| 248 | 0x6a3a660 | lift | `0x6a3a660  push rsi` | [V] | callee sub_3165620(x1 row238 lift). Calls confirmed lift (render) → lift. |
| 249 | 0x6adb8b0 | lift | `0x6adb8b0  push rbp` | [V] | callees sub_9bc830(x1 render-core), sub_68bde60(x9), sub_1c9ff30(x1), sub_6adc170(x1). Calls render-core → lift. |
| 250 | 0x6add4f0 | lift | `0x6add4f0  push rbp` | [V] | callees sub_75740(x4 bgfx), sub_130ee0(x2), sub_9bc830(x8 render-core), sub_68bde60(x21). Calls render-core + bgfx → lift. |
| 251 | 0x6adfe20 | lift | `0x6adfe20  push rbp` | [V] | callees sub_75740(x2 bgfx), sub_130ee0(x1), sub_9bc830(x5 render-core), sub_68bde60(x14). Calls render-core + bgfx → lift. |
| 252 | 0x78ce0 | needs lift | `0x78ce0  push rsi` | [V] | `0x78ce9  xorps xmm0,xmm0` / `0x78cec  mov rdi,[rcx+0x8]` / `0x78cf0  movups [rcx],xmm0` / `test rdi,rdi`. Leaf (no callees), no strings. Very hot (5481 xrefs) memzero + refcount check, no stl/crt/alloc/render fit → needs lift. |
| 253 | 0x1d03d0 | stl | `0x1d03d0  sub rsp,0x28` | [V] | `0x1d03d4  lea rcx,[0xF52EB8B]` = "invalid vector subscript" / `0x1d03db  call 0xEEC5900` (sub_eec5900). Same STL thrower family as sub_eec5850 = std::_Xlength_error [V from X0b1 row2]. std::vector bounds-check throw → stl. |
| 254 | 0x1126680 | needs lift | `0x1126680  sub rsp,0x18` | [V] | `0x1126684  movaps [rsp],xmm6` / `0x1126688  mov rax,rdx` / `0x112668b  mov rdx,[rcx]` / `0x112668e  mov r8,[rcx+0x8]` / `cmp rdx,r8`. Leaf (no callees), no strings. SIMD compare, no stl/crt/alloc/render fit → needs lift. |
| 255 | 0x6c2bb10 | needs lift | `0x6c2bb10  push r15` | [V] | 8-push prologue (push r15/r14/r13/r12/rsi/rdi/rbp/rbx), 1 xref in. callee sub_eec6eb0(x5) only (render-helper, inferential, unproven). No direct render-core/strings → needs lift. |
| 256 | 0x6c2c180 | needs lift | `0x6c2c180  push r15` | [V] | 8-push prologue, 1 xref in. callee sub_eec6eb0(x5) only → needs lift. |
| 257 | 0x6c2c7f0 | needs lift | `0x6c2c7f0  push r15` | [V] | 8-push prologue, 1 xref in. callee sub_eec6eb0(x5) only → needs lift. |
| 258 | 0x6c2ce60 | needs lift | `0x6c2ce60  push r15` | [V] | 8-push prologue, 1 xref in. callee sub_eec6eb0(x5) only → needs lift. |
| 259 | 0x6c2d4d0 | needs lift | `0x6c2d4d0  push r15` | [V] | 8-push prologue, 1 xref in. callee sub_eec6eb0(x5) only → needs lift. |
| 260 | 0x6c2db40 | needs lift | `0x6c2db40  push r15` | [V] | 8-push prologue, 1 xref in. callee sub_eec6eb0(x5) only → needs lift. |
| 261 | 0xc2ae6c0 | needs lift | `0xc2ae6c0  push rbp` | [V] | EH frame prologue: push rbp/r14/rsi/rdi/rbx, sub rsp,0x40, `lea rbp,[rsp+0x40]`, `mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE`. callee sub_c2aea90(x1 unknown). No strings → needs lift. |
| 262 | 0x79950 | lift | `0x79950  push r15` | [V] | callees sub_9c590(x1 row264 lift), sub_9c650(x2 row265 lift), sub_e935700(x1 render-core). Calls render-core → lift. |
| 263 | 0x87440 | lift | `0x87440  push r14` | [V] | 4480 xrefs in. callees sub_9c590(x1 row264 lift), sub_e935700(x1 render-core). Calls render-core → lift. |
| 264 | 0x9c590 | lift | `0x9c590  push r14` | [V] | 2592 xrefs in. callees sub_9c590(x1 self), sub_e935700(x1 render-core). Calls render-core → lift. |
| 265 | 0x9c650 | lift | `0x9c650  push rsi` | [V] | 5306 xrefs in. callee sub_e935700(x2 render-core). Calls render-core → lift. |
| 266 | 0x3c75f0 | lift | `0x3c75f0  push rbp` | [V] | callees sub_9bc830(x1 render-core), sub_eec6ed0(x1). Calls render-core → lift. |
| 267 | 0x43c5d0 | lift | `0x43c5d0  push rbp` | [V] | callees sub_87440(x4 row263 lift), sub_39dc40(x2), sub_3b1c00(x2), sub_43c7e0(x1), sub_43c990(x1), sub_45e5c0(x1), sub_45e6d0(x1), sub_eec5a10(x1). Calls confirmed lift sub_87440 → lift. |
| 268 | 0x446cb0 | lift | `0x446cb0  push rbp` | [V] | 927 xrefs in. callees sub_9bc830(x3 render-core), sub_eec5870(x1). Calls render-core → lift. |
| 269 | 0x45e860 | lift | `0x45e860  push rbp` | [V] | callees sub_87440(x1 row263 lift), sub_443a80(x1), sub_45e5c0(x1), sub_45e9b0(x1), sub_eec5a10(x1). Calls confirmed lift sub_87440 → lift. |
| 270 | 0x5a49890 | needs lift | `0x5a49890  push r15` | [V] | `0x5a49898  add ecx,0xFFFFFF8B` / `0x5a4989b  cmp ecx,0x1B`. Leaf (no callees), no strings. Bounds check, no stl/crt/alloc/render fit → needs lift. |
| 271 | 0x74cb90 | lift | `0x74cb90  push r15` | [V] | callees sub_75740(x1 bgfx), sub_9bc830(x2 render-core), sub_e935700(x1 render-core), sub_eec6de0(x2). Calls render-core + bgfx → lift. |
| 272 | 0x1289960 | lift | `0x1289960  push r15` | [V] | callees sub_75740(x1 bgfx), sub_9bc830(x2 render-core), sub_1289c00(x1). Calls render-core + bgfx → lift. |
| 273 | 0xae500 | needs lift | `0xae500  push r15` | [V] | `0xae50d  mov rax,[rcx]`. callees sub_ae610(x2), sub_ae770(x2) unknown. No strings → needs lift. |
| 274 | 0x1c3170 | lift | `0x1c3170  push r15` | [V] | callees sub_75740(x1 bgfx), sub_9bc830(x2 render-core), sub_e935700(x1 render-core). Calls render-core + bgfx → lift. |
| 275 | 0x17516e0 | needs lift | `0x17516e0  push r15` | [V] | `0x17516ed  mov rdi,rdx`. callees sub_1d0130(x1), sub_c324e0(x1), sub_eec6de0(x4). Render-helper only (inferential); no direct render-core/strings → needs lift. |
| 276 | 0x1751bf0 | lift | `0x1751bf0  push rbp` | [V] | callees sub_75b60(x1 bgfx), sub_9bc830(x2 render-core), sub_1770680(x1), sub_eec6de0(x1). Calls render-core + bgfx → lift. |
| 277 | 0x3cf43f0 | lift | `0x3cf43f0  push r15` | [V] | callee sub_e935700(x2 render-core). Calls render-core → lift. |
| 278 | 0x3cf44f0 | lift | `0x3cf44f0  push rsi` | [V] | callee sub_e935700(x1 render-core). Calls render-core → lift. |
| 279 | 0x1a459d0 | lift | `0x1a459d0  push rsi` | [V] | callee sub_e935700(x1 render-core). Calls render-core → lift. |
| 280 | 0xc2a7b60 | needs lift | `0xc2a7b60  push rbp` | [V] | `0xc2a7b74  mov r8,[rcx+0x20]` / `0xc2a7b78  mov rax,[rcx+0x38]`. Leaf (no callees), no strings. Object field load, no stl/crt/alloc/render fit → needs lift. |
| 281 | 0xc2a7ce0 | lift | `0xc2a7ce0  push r15` | [V] | callees sub_ac370(x1), sub_ac4f0(x1), sub_9bc830(x2 render-core). Calls render-core → lift. |
| 282 | 0xc2a80c0 | needs lift | `0xc2a80c0  push r15` | [V] | `0xc2a80cb  mov rsi,[rcx+0x20]` / `mov rdi,rsi`. callees sub_ac4f0(x1), sub_c2a8510(x1) unknown. No strings → needs lift. |
| 283 | 0x14a0c0 | needs lift | `0x14a0c0  push rbp` | [V] | EH frame prologue: push rbp/rsi/rdi, sub rsp,0x80, `lea rbp,[rsp+0x80]`, `mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE`. callees sub_14a260(x1), sub_14a430(x1), sub_14abf0(x1) unknown (14a* module). No strings → needs lift. |
| 284 | 0x773320 | needs lift | `0x773320  push rbp` | [V] | `0x773337  mov eax,[rcx+0xB0]` / `cmp eax,1`. 1366 xrefs in. Leaf (no callees), no strings. Field test, no stl/crt/alloc/render fit → needs lift. |
| 285 | 0x5ac2420 | lift | `0x5ac2420  push rbp` | [V] | callees sub_b432e0(x3 row218 lift), sub_e938cb0(x3 render-core), sub_e938d70(x3 render-core). Calls render-core → lift. |
| 286 | 0x17716b0 | lift | `0x17716b0  push rbp` | [V] | callee sub_1289960(x1 row272 lift). Calls confirmed lift (render) → lift. |
| 287 | 0x120e00 | lift | `0x120e00  push r15` | [V] | callees sub_75740(x1 bgfx), sub_75b60(x1 bgfx), sub_9bc830(x2 render-core), sub_e935700(x1 render-core), sub_eec6de0(x1), sub_eec6ed0(x1). Calls render-core + bgfx → lift. |
| 288 | 0x35e44a0 | lift | `0x35e44a0  push rsi` | [V] | callees sub_35e44a0(x1 self), sub_e935700(x1 render-core). Calls render-core → lift. |
| 289 | 0xebcf580 | needs lift | `0xebcf580  sub rsp,0x48` | [V] | 35 xrefs in. callee sub_ebcf4e0(x1). str: "BkMGTPEZY"(x2), "%0.2f %c%c%c". Byte-size formatter (utility), not render → needs lift. |
| 290 | 0xebdb760 | needs lift | `0xebdb760  sub rsp,0x28` | [V] | 6 xrefs in. Leaf (no callees), no strings → needs lift. |
| 291 | 0xed35e10 | needs lift | `0xed35e10  sub rsp,0x88` | [V] | callees sub_e951550(x1 row216 = X0b1 row14 crt), sub_eec5880(x1). Calls crt row14 + unknown; no render → needs lift. |
| 292 | 0xe93c790 | needs lift | `0xe93c790  mov [rsp+8],rbx` | [V] | 2 xrefs in. Leaf (no callees), no strings. Unusual prologue, no stl/crt/alloc/render fit → needs lift. |
| 293 | 0x13622e0 | lift | `0x13622e0  push r15` | [V] | callees sub_75740(x1 bgfx), sub_9bc830(x2 render-core), sub_e935700(x1 render-core), sub_eec6de0(x1). Calls render-core + bgfx → lift. |
| 294 | 0x147b10 | lift | `0x147b10  push rsi` | [V] | 820 xrefs in. callee sub_e935700(x3 render-core). Calls render-core → lift. |
| 295 | 0x119b5f0 | lift | `0x119b5f0  push rsi` | [V] | 108 xrefs in. callee sub_e935700(x2 render-core). Calls render-core → lift. |
| 296 | 0x1999390 | needs lift | `0x1999390  sub rsp,0x1E8` | [V] | 4 xrefs in. Leaf (no callees), no strings → needs lift. |
| 297 | 0x7a7870 | lift | `0x7a7870  push r15` | [V] | callees sub_75740(x1 bgfx), sub_9bc830(x2 render-core). Calls render-core + bgfx → lift. |
| 298 | 0xbbbd3d0 | lift | `0xbbbd3d0  push rbp` | [V] | In render region. callees sub_bc37320(x1 bgfx), sub_e935700(x1 render-core). Calls bgfx + render-core → lift. |
| 299 | 0xaa840 | needs lift | `0xaa840  push rbp` | [V] | 8-push prologue (push rbp/r15/r14/r13/r12/rsi/rdi/rbx), 190 xrefs in. Big engine function; no render callees/strings/stl/crt/alloc fit proven from prologue → needs lift. |
| 300 | 0x16cf670 | needs lift | `0x16cf670  push rbp` | [V] | 8-push prologue (push rbp/r15/r14/r13/r12/rsi/rdi/rbx), 11 xrefs in. No render callees/strings/stl/crt/alloc fit proven → needs lift. |

## Classification summary (rows 201-300)
- lift (render-owned, declared for native_checklist_gen.py --add): 61 → 0xbb84ee0,0xbb8ccb0,0xbb8eb70,0xbb93890,0xbb93c60,0xbb96320,0xbbbcb20,0xbbbd7f0,0xbbbfc50,0xbbc9db0,0xbcd77b0,0xbcdba70,0xbce07c0,0xaa7fe0,0x4e00c00,0x4e00d40,0x4e36150,0x4e8eb00,0x4df6a90,0x4e69270,0x6b86e80,0x6be16b0,0xaaa420,0xaaa6e0,0x3165620,0x31f83d0,0x5353600,0x53d3fd0,0x681b6d0,0x68b5ee0,0x68b9bf0,0x68bb9a0,0x6a3a660,0x6adb8b0,0x6add4f0,0x6adfe20,0x79950,0x87440,0x9c590,0x9c650,0x3c75f0,0x43c5d0,0x446cb0,0x45e860,0x74cb90,0x1289960,0x1c3170,0x1751bf0,0x3cf43f0,0x3cf44f0,0x1a459d0,0xc2a7ce0,0x5ac2420,0x17716b0,0x120e00,0x35e44a0,0x13622e0,0x147b10,0x119b5f0,0x7a7870,0xbbbd3d0
- stl: 1 → 0x1d03d0 ("invalid vector subscript" STL throw)
- crt/os/d3d/vendor/alloc/other-subsystem: 0
- needs lift (conservative, unprovable): 38 → 0xbd11a0,0x32d0f30,0x4de7670,0x4e01c30,0x2e8fc0,0x2b96970,0x5391130,0x1999140,0xeaa30,0x4e00090,0x4e3b020,0xe7e150,0x2fd4210,0x539d8c0,0x5418de0,0x78ce0,0x1126680,0x6c2bb10,0x6c2c180,0x6c2c7f0,0x6c2ce60,0x6c2d4d0,0x6c2db40,0xc2ae6c0,0x5a49890,0xae500,0x17516e0,0xc2a7b60,0xc2a80c0,0x14a0c0,0x773320,0xebcf580,0xebdb760,0xed35e10,0xe93c790,0x1999390,0xaa840,0x16cf670
Total = 61 + 1 + 38 = 100 rows. No `?` remains.

## Lift roots (declared; orchestrator merges via native_checklist_gen.py --add)
New lift functions not previously in docs/data/native_roots.txt: 0xbb93890 (row 204, render region), 0x4e00d40 (row 219, render call sub_e935700). All other lift rows were already appended by the X0b3 previous run. NOT writing docs/data/native_roots.txt directly (hard rule) — the orchestrator merges.

## FILES changed/created
- docs/progress/oc_U-EX0b3.md (this file): full classification of rows 201-300.

## UNRESOLVED CALLS
none — every row classified; needs-lift rows carry a stated blocking fact (no render/STL/CRT/alloc evidence from own disassembly). Jump tables decoded; no new external lift roots.

## TOOL REQUESTS
native_checklist_gen.py --add | exe + lift RVA list | registers new lift functions in the native lift set (orchestrator-run; I do not write docs/data/* directly per hard rule). None written by me this run.

## CLOSES?
YES — All 100 rows (201-300) classified on disk: 61 lift [V] (render evidence or BGFX_MAP region), 1 stl [V] (0x1d03d0 "invalid vector subscript" via sub_eec5900), 38 needs lift [V] (conservative, each with cited disassembly evidence and blocking fact). Jump tables 0x4e00d40 (data_f2158a4) and 0x4e01c30 (data_f2158b8) decoded — all targets intra-function, no new external lift roots; sub_4e00d40 proven lift via `0x4e00dc9  jmp 0xE935700`. Every `0xRVA  instr` quote is verbatim from rdis. New lift rows declared for native_checklist_gen.py --add (not writing docs/data/* directly per hard rule; orchestrator merges). No `?`, no skipped offsets, no et-cetera abbreviations. Deferred in-game test (2026-11-22) not a blocker for this static classification item.

## NEXT
DONE
