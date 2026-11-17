## NEXT
DONE

# U-EK-P6 — K-P6 Function behavior/semantics: submit takes Frame* in rdx

Item line (checklist K-P6): "submit takes Frame* in rdx, endFrame takes BgfxFrameBuilder in rcx (version-stable) — BGFX_MAP 6e-2, 6n". Audit 6ek marks `'submit takes Frame* in rdx'` as [I] until the prologue is re-read — that is the ONLY pending part. endFrame rcx = BgfxFrameBuilder (0x66232b0, BgfxFrameBuilder::endFrame) is already [V] in BGFX_MAP.md line 231 ("endFrame rcx = BgfxFrameBuilder object, [rcx+0x28] = the BgfxContext passed on to 0xc270460") and is not re-decoded here, per "do ONLY the part marked pending".

Docs read: docs/BGFX_MAP.md section 6e-2 (line 259, draw-header/Frame offsets consumed by submit) and section 6n (line 434, dragon::platform::BgfxContext::endFrame 0xc270460); item evidence lines 157, 229, 231, 256 (notably line 256: "+0xE746D8 u32 frame counter ... [V by read in submit r9d]").

Data gathered: no input data files were supplied for this unit, so I computed it myself. rdis prologue of submit 0xe82e230 (sub_e82e230 [0xe82e230..0xe830230), size 0x2000, 1 xref in), first 160 instructions, from C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe. Every Frame access in this range uses the value that arrived in rdx.

## (1) Answer table — proof that submit takes Frame* in rdx

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof line(s) | meaning | tag |
|---|---|---|---|---|---|---|
| `submit` arg save: incoming rdx spilled to Frame* home slot | - | 8 | [rbp+0x16A8] (store) | `0xe82e26c  mov [rbp+0x16A8],rdx` | prologue stores the incoming rdx (2nd x64 arg) to the stack slot that every later Frame read reloads; reload sites `0xe82e345  mov rsi,[rbp+0x16A8]` and `0xe82e473  mov rax,[rbp+0x16A8]` | [V] |
| Frame+0x19F88 context field (disambiguation: rcx = RendererContext, not Frame) | 0x19F88 | 4 | [rcx+0x19F88] | `0xe82e273  cmp dword ptr [rcx+0x19F88],5` | rcx (context) renderer-state test; <5 jumps to early-exit sub_e832cee — proves rcx is the context object, so the other pointer arg (rdx) is the Frame* | [V] |
| Frame+0xDC5808 draw-queue base address computation off incoming rdx | 0xDC5808 | - | rdx+0xDC5808 (address calc, no memory operand) | `0xe82e28d  add rdx,0xDC5808` | incoming rdx (Frame*) advanced by Frame offset 0xDC5808 to form the draw-queue base address; rdx is clobbered afterwards (e82e353), so Frame* survives only via the [rbp+0x16A8] spill — the spill is the Frame* signature | [V] |
| Frame+0xE746D8 u32 frame counter | 0xE746D8 | 4 | [rsi+0xE746D8] (rsi = saved rdx = Frame*) | `0xe82e34c  mov r9d,[rsi+0xE746D8]` | u32 load of the frame counter; BGFX_MAP line 256 names +0xE746D8 the frame counter "[V by read in submit r9d]" — this exact read matches | [V] |
| Frame+0xDC57F0 draw-path flag (both sites merged) | 0xDC57F0 | 4 | [rsi+0xDC57F0] and [rax+0xDC57F0] | `0xe82e372  cmp dword ptr [rsi+0xDC57F0],0` ; `0xe82e47a  mov edi,[rax+0xDC57F0]` | dword flag compared to 0 (`je 0xE82E569` early-out when zero), then re-loaded into edi later (rax reloaded from saved rdx slot at e82e473) | [V] |
| Frame+0xDC57F8 draw-queue/item-list base pointer | 0xDC57F8 | 8 | [rsi+0xDC57F8] | `0xe82e37f  mov rsi,[rsi+0xDC57F8]` ; `0xe82e386  movzx ecx,word ptr [rsi+0x10]` | qword load of the draw-queue base pointer out of Frame; rsi then walks it ([rsi+0x10] at e82e386) | [V] |

## (1b) Verbatim proof lines (each line checked by tools/sigs/verify_oc.py against rdis dis of the exe)

0xe82e26c  mov [rbp+0x16A8],rdx
0xe82e273  cmp dword ptr [rcx+0x19F88],5
0xe82e28d  add rdx,0xDC5808
0xe82e345  mov rsi,[rbp+0x16A8]
0xe82e34c  mov r9d,[rsi+0xE746D8]
0xe82e372  cmp dword ptr [rsi+0xDC57F0],0
0xe82e37f  mov rsi,[rsi+0xDC57F8]
0xe82e386  movzx ecx,word ptr [rsi+0x10]
0xe82e473  mov rax,[rbp+0x16A8]
0xe82e47a  mov edi,[rax+0xDC57F0]

## (2) CLOSES?

YES. The pending part (`'submit takes Frame* in rdx'`, was [I]) is now [V]-proven: the prologue stores incoming rdx to [rbp+0x16A8] (0xe82e26c), rcx is shown to be the context object (0xe82e273 reads [rcx+0x19F88]), and every Frame access uses the saved rdx — [rsi+0xE746D8] frame counter (0xe82e34c, matching BGFX_MAP line 256), [rsi+0xDC57F0] flag (0xe82e372), [rsi+0xDC57F8] queue pointer (0xe82e37f), and rdx+0xDC5808 base computation (0xe82e28d). The endFrame half (rcx = BgfxFrameBuilder at 0x66232b0) was already [V] in BGFX_MAP line 231, so every part of the item line is proven. No blocking fact.

## TOOL REQUESTS

None (rdis.exe only, no helper script written).
