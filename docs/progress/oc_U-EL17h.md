## NEXT
DONE

# Unit U-EL17h — L17h graphics options plumbing (OptionSync)
Output file: docs/progress/oc_U-EL17h.md only.
Exe: Minecraft.Windows.exe 1.26.62.01 (all RVAs relative to image base).

GOAL (this run, per orchestrator 2026-11-22): trace how graphics options reach the renderer.
upscaling_percentage = option id 0x243; targetResolution = option id 0x246 (registered via sub_9c4220, [V] per r8). New hops, one row each:
(1) follow each reader of option id 0x243 forward: sub_5b0aa90->[obj+0x1BB8]; sub_5b71ef0->sub_d1720; sub_5bc3071->sub_9bf8b0; sub_5b72000 reads id 0x243 into edi and calls setters at vtable +0xC0/+0xC8 of object at [rsi+0x1A40].
(2) identify [rsi+0x1A40]'s object type: where [reg+0x1A40] is stored + the vtable written into it; resolve vtable slot 0xC0 to its target function; dis it; find where it stores the float; rdis rw that offset to find readers; see if sub_88bb50 / [rbp+0x58]'s +0x5C reads it.
(3) list the OptionSync pieces for the other graphics options in sub_5b72000 (each id read -> setter -> field).
Close condition: a [V] chain from option id 0x243 to a renderer-visible field, or [V] proof it ends at a field no render pass reads.

## Answer table (name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag)

| upscaling_percentage id=0x243 registration | 0x5b3e844 | 4 | 0x5b3e844 | `0x5b3e844  mov edx,0x243` | sub_5b3e100 sets id argument = 0x243 (upscaling_percentage) before registration | [V] |
| upscaling_percentage id=0x243 registration call | 0x5b3e855 | — | 0x5b3e855 | `0x5b3e855  call 0x9C4220` | registers option with id 0x243 | [V] |
| targetResolution id=0x246 registration | 0x5b3eb1b | 4 | 0x5b3eb1b | `0x5b3eb1b  mov edx,0x246` | sub_5b3ea00 sets id argument = 0x246 (targetResolution) before registration | [V] |
| targetResolution id=0x246 registration call | 0x5b3eb2c | — | 0x5b3eb2c | `0x5b3eb2c  call 0x9C4220` | registers option with id 0x246 | [V] |
| option object id field +0x1CC store | 0x1CC | 4 | 0x9be850 | `0x9be850  mov [r13+0x1CC],eax` | sub_9be400 stores option id (eax=edx from caller: 0x243 or 0x246) at option+0x1CC | [V] |
| option value field +0x18 read | 0x18 | 4 | 0x5b0b683 | `0x5b0b683  mov eax,[rax+0x18]` | sub_5b0aa90 reads option float value at [opt+0x18] after get-option-by-id(0x243) | [V] |
| settings upscaling cache +0x1BB8 store | 0x1BB8 | 4 | 0x5b0b68d | `0x5b0b68d  mov [r13+0x1BB8],eax` | sub_5b0aa90 stores upscaling_percentage at settings object+0x1BB8 (r13=[rbp+0x6D8]) | [V] |
| settings upscaling cache +0x1BB8 read | 0x1BB8 | 4 | 0x5bc3090 | `0x5bc3090  mov edx,[rdi+0x1BB8]` | sub_5bc2eb0 reads cached upscaling_percentage as fallback when get-option-by-id(0x243) returns null, then passes it to sub_9bf8b0 | [V] |
| sub_5bc2eb0 id=0x243 setup | 0x5bc3071 | 4 | 0x5bc3071 | `0x5bc3071  mov r8d,0x243` | sub_5bc2eb0 sets id argument = 0x243 before get-option-by-id call | [V] |
| sub_5bc2eb0 get-option-by-id call | 0x5bc3077 | — | 0x5bc3077 | `0x5bc3077  call qword ptr [0xF99FFA0]` | reads option object for id 0x243 | [V] |
| sub_9bf8b0 reads divisor field +0x14 | 0x9bf904 | 4 | 0x9bf904 | `9bf904  mov ecx,[rsi+0x14]` | sub_9bf8b0 reads [a0+0x14] (clamps option value against it) | [V] |
| sub_9bf8b0 stores clamped value +0x18 | 0x9bf96a | 4 | 0x9bf96a | `9bf96a  mov [rsi+0x18],ecx` | sub_9bf8b0 stores clamped upscaling value at [a0+0x18] | [V] |
| sub_9bf8b0 notifier call | 0x9bf974 | — | 0x9bf974 | `9bf974  call 0xD1720` | sub_9bf8b0 notifies listeners via sub_d1720(rcx=[a0+8], rdx=a0) | [V] |
| sub_d1720 indirect vtable[2] call | 0xd1782 | — | 0xd1782 | `d1782  call qword ptr [0xF99FFA0]` | sub_d1720 walks listener list [rcx+8] stride 0x10 calling vtable[2](listener, option_obj) per element; stores no option value (only refcount decrements) | [V] |
| settings object +0x1A40 store (renderer object pointer) | 0x1A40 | 8 | 0x5b0ab9a | `0x5b0ab9a  mov [r14+0x1A40],rax` | sub_5b0aa90 (settings ctor) stores renderer object pointer at settings+0x1A40 (ownership steal: rax=[r15]=*rdx_arg, [r15] nulled) | [V] |
| renderer object vtable write | 0x0 | 8 | 0x5b02327 | `0x5b02327  mov [rcx],rax` | sub_5b02300 ctor writes renderer-object vtable ptr; vtable = 0xF277BA0 (loaded at `0x5b02320  lea rax,[0xF277BA0]`) | [V] |
| sub_5b72000 id=0x243 setup | 0x5b7202a | 4 | 0x5b7202a | `0x5b7202a  mov r8d,0x243` | sub_5b72000 sets get-option-by-id argument = 0x243 (upscaling_percentage) | [V] |
| sub_5b72000 get-option-by-id(0x243) call | 0x5b72030 | — | 0x5b72030 | `0x5b72030  call qword ptr [0xF99FFA0]` | reads option object for id 0x243 | [V] |
| sub_5b72000 upscaling value load | 0x5b72053 | 4 | 0x5b72053 | `0x5b72053  mov edi,[rax+0x18]` | edi = upscaling_percentage value from [opt+0x18] | [V] |
| sub_5b72000 id=0x244 setup | 0x5b72068 | 4 | 0x5b72068 | `0x5b72068  mov r8d,0x244` | id argument = 0x244 (option "upscaling_mode_dropdown", see registration row below) | [V] |
| sub_5b72000 get-option-by-id(0x244) call | 0x5b7206e | — | 0x5b7206e | `0x5b7206e  call qword ptr [0xF99FFA0]` | reads option object for id 0x244 → ebx=[rax+0x18] at `0x5b72093  mov ebx,[rax+0x18]` | [V] |
| sub_5b72000 renderer object load | 0x5b72096 | 8 | 0x5b72096 | `0x5b72096  mov r14,[rsi+0x1A40]` | r14 = renderer object at settings+0x1A40 (vtable 0xF277BA0) | [V] |
| sub_5b72000 vtable[0xC0] load | 0x5b72120 | 8 | 0x5b72120 | `0x5b72120  mov rax,[rax+0xC0]` | loads renderer vtable slot at byte offset 0xC0 = sub_5b06090 (rdis vt 0xF277BA0: `24 +0x0c0 sub_5b06090`) | [V] |
| sub_5b72000 vtable[0xC0] call (upscaling setter) | 0x5b7212c | — | 0x5b7212c | `0x5b7212c  call qword ptr [0xF99FFA0]` | vtable[0xC0](renderer_this=r14, edx=edi=upscaling_percentage); target = sub_5b06090 | [V] |
| sub_5b72000 vtable[0xC8] load | 0x5b7213c | 8 | 0x5b7213c | `0x5b7213c  mov rax,[rax+0xC8]` | loads renderer vtable slot at byte offset 0xC8 = sub_5b063e0 (rdis vt 0xF277BA0: `25 +0x0c8 sub_5b063e0`) | [V] |
| sub_5b72000 vtable[0xC8] call | 0x5b72145 | — | 0x5b72145 | `0x5b72145  call qword ptr [0xF99FFA0]` | vtable[0xC8](renderer_this, edx=ebx=opt 0x244 value); target = sub_5b063e0 | [V] |
| upscaling tier constants | - | - | 0x5b0622a-0x5b0626f | `0x5b0623d  movss xmm0,[0xEEE7C00]` / `0x5b06247  movss xmm0,[0xF08AF90]` / `0x5b06251  movss xmm0,[0xEFD3440]` / `0x5b0622a  movss xmm0,[0xEEC8060]` / `0x5b0626f  movss xmm0,[0xF0A1880]` | sub_5b06090 switch on value low byte: 0x32(50)/0x41(65)/0x4B(75)/0x64(100)/default load per-tier float constants (0xEEC8060 is read-only 1.0f per L10c) | [V] |
| renderer +0xBA0 upscale scale store | 0xBA0 | 4 | 0x5b06287 | `0x5b06287  movss [rax+0xBA0],xmm0` | sub_5b06090 (vtable[0xC0] setter) stores upscale-scale float at [render_obj+0xBA0]; rax = ([0x128C5048])->vtable[0x270]() render-context object; exe-wide [reg+0xBA0] heap-object writes: only this site (rest are stack [rbp+0xBA0] or unrelated classes) | [V] |
| renderer +0xC3C/+0xC3E mode words store | 0xC3C/0xC3E | 2 | 0x5b06277/0x5b0627f | `0x5b06277  mov [rax+0xC3C],r14w` / `0x5b0627f  mov [rax+0xC3E],r15w` | sub_5b06090 stores per-tier words from data table 0xF27A070/0xF27A07E at [render_obj+0xC3C/+0xC3E] | [V] |
| renderer +0xB9C bool store | 0xB9C | 4 | 0x5b06503 | `0x5b06503  mov [rax+0xB9C],esi` | sub_5b063e0 (vtable[0xC8] setter) stores bool (opt0x244==1) at [render_obj+0xB9C] | [V] |
| render-thread +0xBA0 read | 0xBA0 | 8 | 0x3b4587 | `3b4587  mov rcx,[rax+0xBA0]` | sub_3b4570 (render thread; object = TLS gs:[0x58]+tls_idx[0x128767C8]*8) reads render-context +0xBA0 and compares with +0xBB0; zeroes both if unchanged (`3b45ec  movups [rax+0xBA0],xmm0`) | [V] read; object identity with sub_5b06090's rax [I] |
| endFrame chain: descriptor+0x1F0 read | 0x1F0 | 4 | 0x566d04a | `0x566d04a  movss xmm0,[rsi+0x1F0]` | sub_566cb20 reads pass descriptor+0x1F0 | [V] |
| endFrame chain: element+0x1F0 write | 0x1F0 | 4 | 0x566d052 | `0x566d052  movss [rdx+0x1F0],xmm0` | sub_566cb20 writes element+0x1F0 from descriptor+0x1F0 | [V] |
| endFrame chain: source+0x1F0 read | 0x1F0 | 4 | 0x67c7917 | `0x67c7917  movss xmm0,[rsi+0x1F0]` | struct-copy 0x67C73D0 reads source element+0x1F0 | [V] |
| endFrame chain: ctx+0x1F0 write | 0x1F0 | 4 | 0x67c791f | `0x67c791f  movss [rdx+0x1F0],xmm0` | struct-copy 0x67C73D0 writes ctx+0x1F0 (ctx=r15) | [V] |
| endFrame chain: TAAU +0x1F0 consume | 0x1F0 | 16 | 0xbc8d34e | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | TAAU body 0xbc8cfd0 consumes ctx+0x1F0 as render/display ratio | [V] |
| endFrame ratio computation | 0x14 | 4 | 0x6625094 | `0x6625094  divss xmm8,[r15+0x14]` | endFrame ratio = 1.0f (`0x6625077  movss xmm7,[0xEEC8060]`) / [elem+0x14] (r15 = element) | [V] |
| option id 0x244 name registration | 0x51de411 | 16 | 0x51de411 | `0x51de411  movups xmm0,[0xF580804]` | builds string "upscaling_mode_dropdown" ([data_f580804]) and `0x51de442  mov edx,0x244` / `0x51de447  call 0x4BB3F10` registers it with id 0x244 | [V] name+id pairing at one call site |
| dropped reader: sub_10c1ad0 id=0xFD | 0x10c1b52 | 4 | 0x10c1b52 | `0x10c1b52  mov r8d,0xFD` | sub_10c1ad0 reads option id 0xFD via get-option-by-id — NOT 0x243; {0x243,0x246} ∩ {0xFD,0xFE,0x100,0x101} = ∅; sub_10c1ad0 is not the upscaling reader | [V] |

## Mechanics established ([V] unless marked)

- get-option-by-id = `call qword ptr [0xF99FFA0]` → thunk 0xeea6040 `jmp rax` (vtable[0xD8] content invoked indirectly). `rdis find FF 91 D8 00 00 00` = 0 hits: no `call qword ptr [reg+0xD8]` exists in .exe [V r11].
- Option id registration: upscaling_percentage id=0x243 (`0x5b3e844`/`0x5b3e855 call 0x9C4220`, sub_5b3e100; id stored option+0x1CC by `0x9be850 mov [r13+0x1CC],eax` in sub_9be400). targetResolution id=0x246 (`0x5b3eb1b`/`0x5b3eb2c call 0x9C4220`, sub_5b3ea00) [V r8].
- Readers of option id 0x243: sub_5b0aa90 → stores [r13+0x1BB8] (`0x5b0b68d`); sub_5b71ef0 → passes option object to sub_d1720 (`0x5b71f6e call 0xD1720`); sub_5bc3071 → fallback `0x5bc3090 mov edx,[rdi+0x1BB8]` then sub_9bf8b0 (`0x5bc3099 call 0x9BF8B0`) which clamps by [a0+0x14]/[a0+0x10], stores [a0+0x18] (`0x5bf96a mov [rsi+0x18],ecx`), notifies via sub_d1720; sub_20ff240 → reads, result unused [V r11].
- sub_d1720 (0xd1720..0xd18b6): refcounted notifier; walks listener list [rcx+8] stride 0x10, calls vtable[2](listener, option object) per element (`0xd1782 call qword ptr [0xF99FFA0]`); stores no option value [V].
- fld 0x1BB8 --r (41 accesses): settings-relevant reader only `0x5bc3090 mov edx,[rdi+0x1BB8]`; no sub_888xxx / sub_88bb50 / sub_e7e150-filler among readers [V]. fld 0x1BB8 --w: `0x5bc2f46 mov [rdi+0x1BB8],eax` (sub_5bc2eb0 cache) and `0x5b0b68d` (sub_5b0aa90 path) [V].
- Renderer object type: vtable 0xF277BA0, ctor sub_5b02300 (`0x5b02327 mov [rcx],rax`, rax=0xF277BA0 from `0x5b02320 lea rax,[0xF277BA0]`); pointer stored at settings+0x1A40 by sub_5b0aa90 (`0x5b0ab9a mov [r14+0x1A40],rax`) [V]. Renderer object = global manager [0x1233E1A8] get-by-id(0x1D70) result (sub_877360 `0x87766f mov edx,0x1D70` → `0x8776b2 mov r13,[rbp+0x198]` → passed to sub_5b0aa90 at `0x877805 call 0x5B0AA90`) [V].
- sub_5b72000 (0x5b72000..0x5b72177, 1 xref: sub_895830 `0x89605c call 0x5B72000`, rcx=[rbp+0x58]): reads id 0x243 into edi (`0x5b72053 mov edi,[rax+0x18]`) and id 0x244 into ebx; calls vtable[0xC0](renderer@[rsi+0x1A40], edx=upscaling_percentage) at `0x5b7212c` and vtable[0xC8](renderer, edx=opt0x244) at `0x5b72145` [V].
- sub_5b06090 (vtable[0xC0], 0x5b06090..0x5b06354): ignores this; uses render global [0x128C5048]->vtable[0x270]() → rax; tier switch stores `movss [rax+0xBA0],xmm0` (`0x5b06287`) and words [rax+0xC3C]/[rax+0xC3E] (`0x5b06277`/`0x5b0627f`) [V].
- sub_5b063e0 (vtable[0xC8], 0x5b063e0..0x5b065cc): stores `mov [rax+0xB9C],esi` = bool (opt0x244==1) at [render_obj+0xB9C] (`0x5b06503`) [V].
- Render-thread consumption: sub_3b4570 reads TLS render-context `3b4587 mov rcx,[rax+0xBA0]`, compares vs +0xBB0, zeroes both when unchanged (`3b45ec movups [rax+0xBA0],xmm0`) [V read].
- Legacy +0x1F0 chain (separate, driven by option ids 0xFD/0xFE/0x100/0x101 via sub_10c1ad0, NOT by 0x243/0x246): descriptor+0x1F0 → element+0x1F0 → ctx+0x1F0 → TAAU 0xbc8d34e [V r4]; endFrame ratio = 1.0f/[elem+0x14] (`0x6625094 divss xmm8,[r15+0x14]`, 0xEEC8060 = 1.0f) [V r9]; elem+0x14 is ctor constant 2.0f, NOT option-driven (L10c closed) — stop looking for 0x243 → elem+0x14.
- Option id 0x246 (targetResolution): no reader via get-option-by-id found (`rdis imm 0x246`: only registration/WebRTC/SSL) [V r12]; skipped per orchestrator scope.

## CLOSES?

YES — every pending part of the item line is proven by [V] rows:
(1) sub_5b72000 reads option id 0x243 (upscaling_percentage) into edi (`0x5b7202a mov r8d,0x243` / `0x5b72053 mov edi,[rax+0x18]`) and calls the setter at vtable byte offset 0xC0 (sub_5b06090, `0x5b7212c call qword ptr [0xF99FFA0]`) plus vtable[0xC8] (sub_5b063e0, id 0x244 "upscaling_mode_dropdown", `0x5b72145`) on the renderer object at settings+0x1A40 [V].
(2) Object type identified: vtable 0xF277BA0 written by ctor sub_5b02300 (`0x5b02327 mov [rcx],rax`, `0x5b02320 lea rax,[0xF277BA0]`); pointer written at settings+0x1A40 by sub_5b0aa90 (`0x5b0ab9a mov [r14+0x1A40],rax`) [V]. sub_5b06090 stores the upscale-scale float at render-object field +0xBA0 (`0x5b06287 movss [rax+0xBA0],xmm0`) [V]; sub_5b063e0 stores bool at +0xB9C (`0x5b06503 mov [rax+0xB9C],esi`) [V]. The +0xBA0 field is read by render-thread code sub_3b4570 (`3b4587 mov rcx,[rax+0xBA0]`, TLS render context) [V read]. Hence a [V] chain exists: option id 0x243 → renderer-visible upscale-scale field +0xBA0 → consumed by render thread.
(3) Other OptionSync piece in sub_5b72000: id 0x244 ("upscaling_mode_dropdown", `0x51de411 movups xmm0,[0xF580804]` + `0x51de442 mov edx,0x244` / `0x51de447 call 0x4BB3F10`) → vtable[0xC8] sub_5b063e0 → +0xB9C bool [V].
Residual [I] (not blocking): same-instance identity between sub_5b06090's `([0x128C5048])->vtable[0x270]()` object and sub_3b4570's TLS render context is inferred from shared render subsystem, not proven by a single instruction.

## TOOL REQUESTS

None — all work done with rdis.exe (vt/fld/dis/fn), xref.py, ripscan.py and live captures already on disk (el17h_endframe_caller.txt, u_el10c_e7e150.txt, u_em1f_endframe.txt, u_em1f_view_setup.txt).
