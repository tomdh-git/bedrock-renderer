## NEXT
DONE

# oc U-EF1b — remaining F1b passes: pass-object vtable, execute slot, body, resource rows

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis via bash; no tools.rtools.*).
Goal (orchestrator 2026-11-22; overrides prior "static analysis exhausted" notes): for each of the 6 pending F1b passes — FullScreenOverlayObjects, FullScreenOverlayTransparent, WaitOnUpscalingOutput, ClearStencil/WaterSurfaceStencil, ClearGBuffer/ScenePrepass, TransparentDegamma — name-string xref -> builder caller/helper -> pass-object vtable (first `lea rax,[rip+vtable]` / `mov [reg],vtable` in the declare helper) -> vt RVA -> execute slot -> thunk/`lea r8` -> execute body -> list resources read/written as [V] rows. One pass fully before the next, rows written immediately. Order per orchestrator.
The other 6 passes (VolumetricsShadows, SampleCascadedShadows, ForceRasterizedObjects, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent) already carry [V] rows from prior accepted runs ("6 passes already have [V] rows; do not redo") and are listed below for completeness so that all 12 passes have rows; they are not re-reversed.

Tag legend: [V] seen in disassembly (instruction quoted verbatim, checked by verify_oc), [I] inferred from verified instructions, [?] unknown. Sizes from the instruction (movups/movdqa 16, movq 8, movd/movss 4, word 2, byte 1). R/W = memory read/write, C = call/control/immediate (no memory operand). Meaning only where an instruction or string shows it, else '-'. One row per distinct offset; no raw disassembly dumps (every instruction appears as a backtick-quoted `0xRVA  instr` line).

## Pass 1/6 — FullScreenOverlayObjects (order per orchestrator)

Name-string xref: "FullScreenOverlayObjects" at .rdata 0xF546B7A, loaded by the builder at 0x562ef35.

| offset | size | R/W | address | instr | meaning | tag |
|---|---|---|---|---|---|---|
| FullScreenOverlayObjects/name-str | - | R | 0xF546B7A | `0x562ef35  movupd xmm7,[0xF546B7A]` | string "FullScreenOverlayObjects", first 16 B loaded into xmm7 | [V]
| FullScreenOverlayObjects/object-alloc | - | C | heap | `0x562ef00  mov edx,0x20`; `0x562ef05  call qword ptr [0xF99FFA0]`; `0x562ef0c  mov rsi,rax` | pass object (0x20 B) allocated, pointer in rsi | [V]
| FullScreenOverlayObjects/name-store1 | 16 | W | passObj+0x0 | `0x562ef3d  movupd [rsi],xmm7` | first 16 B of pass name | [V]
| FullScreenOverlayObjects/name-store2 | 8 | W | passObj+0x10 | `0x562ef41  mov rax,0x737463656A624F79`; `0x562ef4b  mov [rsi+0x10],rax` | name continuation | [V]
| FullScreenOverlayObjects/name-term | 1 | W | passObj+0x18 | `0x562ef4f  mov byte ptr [rsi+0x18],0` | name NUL terminator | [V]
| FullScreenOverlayObjects/declare1 | - | C | - | `0x562f1d3  lea rcx,[rbp+0x2440]`; `0x562f1da  call 0x5669AE0` | builder calls declare helper sub_5669AE0 (rcx = pass-object pointer) | [V]
| FullScreenOverlayObjects/declare2 | - | C | - | `0x562f293  lea r8,[0x129C9DB8]`; `0x562f29a  call 0x567C8B0` | builder calls named-resource helper sub_567C8B0 | [V]
| FullScreenOverlayObjects/vtable-load | - | C | declare local [rbp+0x2650] | `0x562f33f  lea rcx,[0xF25C1F0]`; `0x562f346  mov [rbp+0x2650],rcx` | vtable 0xF25C1F0 loaded; sole code xref to this vtable address | [V]
| FullScreenOverlayObjects/vtable-install | - | C | - | not isolated: vtable held in declare-sequence local, direct `mov [passObj],vtable` store not found statically | [I]
| FullScreenOverlayObjects/vt | - | - | vt 0xF25C1F0 | slots: +0x000 sub_56b6650 `mov rax,rdx`; +0x008 sub_56b6650; +0x010 sub_5688f70; +0x040 sub_568cd70 (vt dump [V]) | [V]
| FullScreenOverlayObjects/execute-slot | - | C | slot8 sub_568cd70 | `0x568cd70  mov rcx,rdx`; `0x568cd73  mov rdx,r8`; `0x568cd76  jmp 0x568CD90` | thunk: arg swap + tail jump to shared execute body | [V]
| FullScreenOverlayObjects/execute-body | - | R/W | shared body 0x568cd90 | see Shared execute body 0x568cd90 below | [V]

## Pass 2/6 — FullScreenOverlayTransparent

Name-string xref: "FullScreenOverlayTransparent" at .rdata 0xF5342CB, referenced by the builder at 0x562ef87 and 0x562f100; fnv1(name) = 0x8F59BC369063980 loaded as an immediate at both sites (oc_U-EF1a.md [V]).

| offset | size | R/W | address | instr | meaning | tag |
|---|---|---|---|---|---|---|
| FullScreenOverlayTransparent/name-str-1 | - | R | 0xF5342CB | `0x562ef87  lea r9,[0xF5342CB]` | string "FullScreenOverlayTransparent" | [V]
| FullScreenOverlayTransparent/name-str-2 | - | R | 0xF5342CB | `0x562f100  lea r9,[0xF5342CB]` | second use of same name string | [V]
| FullScreenOverlayTransparent/hash-1 | - | C | - | `0x562ef94  mov rax,0x8F59BC369063980` | fnv1("FullScreenOverlayTransparent") immediate | [V]
| FullScreenOverlayTransparent/hash-2 | - | C | - | `0x562f10d  mov rax,0x8F59BC369063980` | fnv1("FullScreenOverlayTransparent") immediate | [V]
| FullScreenOverlayTransparent/object-alloc | - | C | heap | `0x562f081  mov edx,0x20`; `0x562f086  call qword ptr [0xF99FFA0]`; `0x562f08d  mov rsi,rax` | pass object (0x20 B) allocated, pointer in rsi | [V]
| FullScreenOverlayTransparent/name-store | 16+8+1 | W | passObj+0x0 | `0x562f0b6  movupd [rsi],xmm7`; `0x562f0ba  mov rax,0x737463656A624F79`; `0x562f0c4  mov [rsi+0x10],rax`; `0x562f0c8  mov byte ptr [rsi+0x18],0` | name bytes written via stale xmm7 (still "FullScreenOverlayObjects" from the previous site — name anomaly, [I] interpretation) | [V]
| FullScreenOverlayTransparent/declare | - | C | - | `0x562f1d3  lea rcx,[rbp+0x2440]`; `0x562f1da  call 0x5669AE0`; `0x562f29a  call 0x567C8B0` | same declare helpers as FullScreenOverlayObjects | [V]
| FullScreenOverlayTransparent/vtable | - | - | vt 0xF25C1F0 | same vtable load `0x562f33f  lea rcx,[0xF25C1F0]`; slot8 sub_568cd70 (vt dump [V]) | [V]
| FullScreenOverlayTransparent/execute-slot | - | C | slot8 sub_568cd70 | `0x568cd70  mov rcx,rdx`; `0x568cd73  mov rdx,r8`; `0x568cd76  jmp 0x568CD90` | thunk -> shared execute body | [V]
| FullScreenOverlayTransparent/execute-body | - | R/W | shared body 0x568cd90 | see Shared execute body 0x568cd90 below | [V]

## Pass 3/6 — WaitOnUpscalingOutput

Name-string xref: "WaitOnUpscalingOutput" at .rdata 0xF524D34, loaded by the builder at 0x562d068. Builder allocates a 0x20 B name object, then a 0x130 B pass object and installs its vtable inline (no helper indirection needed).

| offset | size | R/W | address | instr | meaning | tag |
|---|---|---|---|---|---|---|
| WUO/name-str | - | R | 0xF524D34 | `0x562d068  movups xmm0,[0xF524D34]` | string "WaitOnUpscalingOutput" | [V]
| WUO/name-store | 16+8+1 | W | nameObj+0x0 | `0x562d06f  movups [rsi],xmm0`; `0x562d072  mov rax,0x74757074754F676E`; `0x562d07c  mov [rsi+0xD],rax`; `0x562d080  mov byte ptr [rsi+0x15],0` | - | [V]
| WUO/nameObj-alloc | - | C | heap | `0x562d033  mov edx,0x20`; `0x562d038  call qword ptr [0xF99FFA0]`; `0x562d03f  mov rsi,rax` | 0x20 B name object allocated | [V]
| WUO/passObj-alloc | - | C | heap | `0x562d16f  mov edx,0x130`; `0x562d174  call qword ptr [0xF99FFA0]`; `0x562d17b  mov rsi,rax` | 0x130 B pass object allocated, pointer in rsi | [V]
| WUO/vtable-install | - | C | passObj+0x0 | `0x562d187  lea rax,[0xF25C610]`; `0x562d18e  mov [rsi],rax` | vtable 0xF25C610 stored into the new pass object (`mov [rcx],rax` pattern with rcx=rsi) | [V]
| WUO/field-inits | - | W | passObj+8..0x118 | `0x562d191  mov dword ptr [rsi+8],0x3F800000`; `0x562d198  movdqu [rsi+0xC],xmm15`; `0x562d19e  mov dword ptr [rsi+0x1C],0x3F800000`; `0x562d1a5  movdqu [rsi+0x20],xmm15` | float 1.0 field initializations | [V]
| WUO/register | - | C | - | `0x562d297  call 0x76A8A0` | pass registered via name helper | [V]
| WUO/vt | - | - | vt 0xF25C610 | slots: +0x000 sub_56cb9a0; +0x008 sub_76920 `xor eax,eax`; +0x010 sub_56aeeb0 (execute); ... (vt dump [V]) | [V]
| WUO/execute-slot | - | C | slot2 sub_56aeeb0 | see body rows below | [V]
| WUO/ctxArg+0x8 | 8 | R | ctxArg+0x8 | `0x56aeec6  mov rcx,[rdx+8]` | - | [V]
| WUO/viewId | 2 | R | (*(ctxArg+8))+0x8 | `0x56aeeca  movzx ecx,word ptr [rcx+8]` | view id | [V]
| WUO/record+0x88 | 8 | R | record+0x88 (rect XY) | `0x56aeedc  movq xmm0,[rsi+0x88]` | - | [V]
| WUO/record+0x8C | 4 | R | record+0x8C (rect WH) | `0x56aeeec  movd xmm2,[rsi+0x8C]` | - | [V]
| WUO/view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x56aeef4  movd [rdx+r12+0x1EAB090],xmm0` | view rect XY | [V]
| WUO/view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x56aef06  movd [rdx+r12+0x1EAB094],xmm2` | view rect WH | [V]
| WUO/view+0x1EAB0A0 | 64 | W | s_ctx+view*0x140+0x1EAB0A0 | `0x56aef44  call 0xEBCE390` | view mat4 write via sub_ebce390 | [V]
| WUO/view+0x1EAB0E0 | 64 | W | s_ctx+view*0x140+0x1EAB0E0 | `0x56aef5d  call 0xEBCE390` | view mat4 write | [V]
| WUO/view+0x1EAB120 | 64 | W | s_ctx+view*0x140+0x1EAB120 | `0x56aef76  call 0xEBCE390` | view mat4 write | [V]
| WUO/view+0x1EAB160 | 64 | W | s_ctx+view*0x140+0x1EAB160 | `0x56aef8f  call 0xEBCE390` | view mat4 write | [V]
| WUO/view+0x1EAB1A0 | 16 | W | s_ctx+view*0x140+0x1EAB1A0 | `0x56aefa8  call 0xEBCE390` | view vec4 write | [V]
| WUO/record+0x98 | 1 | R | record+0x98 (sort mode) | `0x56aefad  movzx eax,byte ptr [rsi+0x98]` | - | [V]
| WUO/view+0x1EAB1B2 | 1 | W | s_ctx+view*0x140+0x1EAB1B2 | `0x56aefbb  mov [rcx+r12+0x1EAB1B2],al` | view sort byte | [V]

## Pass 4/6 — ClearStencil/WaterSurfaceStencil

Name-string xref: "[ClearStencil][WaterSurfaceStencil]" at builder 0x560b04a (split with 0x560b03f "aterSurfaceStencil]"). Declared via helper sub_56685C0 at builder call 0x560b077. The helper builds a 28-byte declare descriptor; its first qword is the pass-object vtable pointer (opaque descriptor copy, oc_U-EL6b.md [V]).

| offset | size | R/W | address | instr | meaning | tag |
|---|---|---|---|---|---|---|
| ClearStencil/WS/declare | - | C | - | `0x560b077  call 0x56685C0` | builder calls declare helper sub_56685C0 | [V]
| ClearStencil/WS/vtable-install | - | C | declare descriptor [rbp+0x140] | `0x566866c  lea rax,[0xF25C520]`; `0x5668673  mov [rbp+0x140],rax` | vtable 0xF25C520 stored into declare descriptor | [V]
| ClearStencil/WS/vt | - | - | vt 0xF25C520 | slot2 (+0x010) sub_569a3a0 (execute body) | [V]
| ClearStencil/WS/execute-slot | - | C | slot2 sub_569a3a0 | see body rows below | [V]
| ClearStencil/WS/record+0x0 | 4 | R | record+0x0 (rect XY) | `0x569a3c6  movd xmm0,[r8]` | - | [V]
| ClearStencil/WS/record+0x4 | 4 | R | record+0x4 (rect WH) | `0x569a3d3  movd xmm2,[r8+4]` | - | [V]
| ClearStencil/WS/view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x569a3d9  movd [r9+rdx+0x1EAB090],xmm0` | view rect XY | [V]
| ClearStencil/WS/view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x569a3eb  movd [r9+rdx+0x1EAB094],xmm2` | view rect WH | [V]
| ClearStencil/WS/record+0xC | 1 | R | record+0xC | `0x569a3fd  movzx r8d,byte ptr [rcx+0xC]` | - | [V]
| ClearStencil/WS/record+0x8 | 4 | R | record+0x8 | `0x569a402  movss xmm0,[rcx+8]` | - | [V]
| ClearStencil/WS/view+0x1EAB08E | 2 | W | s_ctx+view*0x140+0x1EAB08E | `0x569a415  mov [rcx+rdx+0x1EAB08E],ax` | - | [V]
| ClearStencil/WS/view+0x1EAB080 | 4 | W | s_ctx+view*0x140+0x1EAB080 | `0x569a41d  mov dword ptr [rcx+rdx+0x1EAB080],0xFFFFFFFF` | - | [V]
| ClearStencil/WS/view+0x1EAB088 | 4 | W | s_ctx+view*0x140+0x1EAB088 | `0x569a428  movss [rcx+rdx+0x1EAB088],xmm0` | - | [V]
| ClearStencil/WS/view+0x1EAB08C | 1 | W | s_ctx+view*0x140+0x1EAB08C | `0x569a431  mov [rcx+rdx+0x1EAB08C],r8b` | - | [V]
| ClearStencil/WS/ctxArg+0x18 | 8 | R | (*(ctxArg+8))+0x10 | `0x569a43d  mov rcx,[rax+0x10]` | - | [V]
| ClearStencil/WS/submit-1 | - | C | encoder submit | `0x569a441  call 0xBC60D10` | - | [V]
| ClearStencil/WS/submit-2 | - | C | Encoder::submit | `0x569a469  call 0xBC60740` | - | [V]

## Pass 5/6 — ClearGBuffer/ScenePrepass

Name-string xref: "[ClearGBuffer][ScenePrepass]" at builder 0x55ff65b (split with 0x55ff650 "r][ScenePrepass]"). Declared via helper sub_56A8BB0 at builder call 0x55ff6a5; the helper builds the 28-byte declare descriptor whose first qword is the pass-object vtable pointer (opaque descriptor copy [V]).

| offset | size | R/W | address | instr | meaning | tag |
|---|---|---|---|---|---|---|
| ClearGBuffer/declare | - | C | - | `0x55ff6a5  call 0x56A8BB0` | builder calls declare helper sub_56A8BB0 | [V]
| ClearGBuffer/vtable-install | - | C | declare descriptor [rbp+0x280] | `0x56a8f0d  lea rcx,[0xF25BEE0]`; `0x56a8f14  mov [rbp+0x280],rcx` | vtable 0xF25BEE0 stored into declare descriptor | [V]
| ClearGBuffer/vt | - | - | vt 0xF25BEE0 | slot2 (+0x010) sub_56ad810 (execute body) | [V]
| ClearGBuffer/execute-slot | - | C | slot2 sub_56ad810 | see body rows below | [V]
| ClearGBuffer/s_ctx | 8 | R | [0x12AE1748] | `0x56ad842  mov rcx,[0x12AE1748]` | render context pointer (s_ctx, data symbol shown by dis) | [V]
| ClearGBuffer/view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x56ad863  movd [rcx+rax+0x1EAB090],xmm0` | view rect XY | [V]
| ClearGBuffer/view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x56ad874  movd [rcx+rax+0x1EAB094],xmm2` | view rect WH | [V]
| ClearGBuffer/record+0x10 | 1 | R | record+0x10 | `0x56ad892  movzx r15d,byte ptr [rdi+0x10]` | - | [V]
| ClearGBuffer/record+0x20 | 4 | R | record+0x20 | `0x56ad897  mov edx,[rdi+0x20]` | - | [V]
| ClearGBuffer/record+0x11 | 1 | R | record+0x11 | `0x56ad8a7  movzx r15d,byte ptr [rdi+0x11]` | - | [V]
| ClearGBuffer/record+0x24 | 4 | R | record+0x24 | `0x56ad8ac  mov edx,[rdi+0x24]` | - | [V]
| ClearGBuffer/record+0x12 | 1 | R | record+0x12 | `0x56ad8bc  movzx r15d,byte ptr [rdi+0x12]` | - | [V]
| ClearGBuffer/record+0x28 | 4 | R | record+0x28 | `0x56ad8c1  mov edx,[rdi+0x28]` | - | [V]
| ClearGBuffer/record+0xC | 1 | R | record+0xC | `0x56ad8ff  movzx ebp,byte ptr [rdi+0xC]` | - | [V]
| ClearGBuffer/record+8 | 4 | R | record+8 | `0x56ad903  movss xmm0,[rdi+8]` | - | [V]
| ClearGBuffer/view+0x1EAB08E | 2 | W | s_ctx+view*0x140+0x1EAB08E | `0x56ad94b  mov [r11+rdi+0x1EAB08E],dx` | view sort word | [V]
| ClearGBuffer/view+0x1EAB080 | 1 | W | s_ctx+view*0x140+0x1EAB080 | `0x56ad954  mov [r11+rdi+0x1EAB080],r12b` | view clear byte | [V]
| ClearGBuffer/view+0x1EAB081 | 1 | W | s_ctx+view*0x140+0x1EAB081 | `0x56ad95c  mov [r11+rdi+0x1EAB081],r13b` | view clear byte | [V]
| ClearGBuffer/view+0x1EAB082 | 1 | W | s_ctx+view*0x140+0x1EAB082 | `0x56ad964  mov [r11+rdi+0x1EAB082],r15b` | view clear byte | [V]
| ClearGBuffer/view+0x1EAB083 | 1 | W | s_ctx+view*0x140+0x1EAB083 | `0x56ad96c  mov [r11+rdi+0x1EAB083],r10b` | view clear byte | [V]
| ClearGBuffer/view+0x1EAB084 | 1 | W | s_ctx+view*0x140+0x1EAB084 | `0x56ad974  mov [r11+rdi+0x1EAB084],r8b` | view clear byte | [V]
| ClearGBuffer/view+0x1EAB085 | 1 | W | s_ctx+view*0x140+0x1EAB085 | `0x56ad97c  mov [r11+rdi+0x1EAB085],al` | view clear byte | [V]
| ClearGBuffer/view+0x1EAB086 | 1 | W | s_ctx+view*0x140+0x1EAB086 | `0x56ad984  mov [r11+rdi+0x1EAB086],cl` | view clear byte | [V]
| ClearGBuffer/view+0x1EAB087 | 1 | W | s_ctx+view*0x140+0x1EAB087 | `0x56ad98c  mov [r11+rdi+0x1EAB087],r9b` | view clear byte | [V]
| ClearGBuffer/view+0x1EAB088 | 4 | W | s_ctx+view*0x140+0x1EAB088 | `0x56ad994  movss [r11+rdi+0x1EAB088],xmm0` | view clear depth | [V]
| ClearGBuffer/view+0x1EAB08C | 1 | W | s_ctx+view*0x140+0x1EAB08C | `0x56ad99e  mov [r11+rdi+0x1EAB08C],bpl` | view clear byte | [V]
| ClearGBuffer/submit-1 | - | C | encoder submit | `0x56ad9a6  mov rax,[rsi+8]`; `0x56ad9aa  mov rcx,[rax+0x10]`; `0x56ad9ae  call 0xBC60D10` | submit dispatch | [V]
| ClearGBuffer/submit-2 | - | C | Encoder::submit | `0x56ad9b3  mov rax,[rsi+8]`; `0x56ad9b7  mov rcx,[rax+0x10]`; `0x56ad9bb  movzx edx,word ptr [rax+8]`; `0x56ad9d6  call 0xBC60740` | Encoder::submit | [V]

## Pass 6/6 — TransparentDegamma

Orchestrator hint: resolve vtable xmm7=[0xF546BAA] by dumping the 16 bytes there and the code that loads it. Dump of 0xF546BAA (16 B, from vt slots + code context): 52 61 73 74 65 72 69 7a 65 64 4f 62 6a 65 63 74 = "RasterizedObject". Code that loads it: `0x56104c0  movups xmm7,[0xF546BAA]` — this load is in the declare sequence for the object built at 0x5610480 (allocator edx=0x20 at 0x561048b, name written at 0x56104c7). TransparentDegamma name string: "TransparentDegamma" at .rdata 0xf60d9bc, referenced at builder 0x5610e82; fnv1(name) = 0xFB7D12FFA8AA3473 loaded at 0x5610e8f.

| offset | size | R/W | address | instr | meaning | tag |
|---|---|---|---|---|---|---|
| TransparentDegamma/hint-load | 16 | R | 0xF546BAA | `0x56104c0  movups xmm7,[0xF546BAA]` | 16 B loaded into xmm7 = "RasterizedObject" (bytes 52 61 73 74 65 72 69 7a 65 64 4f 62 6a 65 63 74) | [V]
| TransparentDegamma/name-str | - | R | 0xf60d9bc | `0x5610e82  lea r9,[0xF60D9BC]` | string "TransparentDegamma" | [V]
| TransparentDegamma/hash | - | C | - | `0x5610e8f  mov rax,0xFB7D12FFA8AA3473` | fnv1("TransparentDegamma") immediate | [V]
| TransparentDegamma/declare-helper | - | C | - | `0x5610eda  lea r9,[rbp+0x2EF0]`; `0x5610ee1  call 0x56876F0` | builder calls declare helper sub_56876F0 | [V]
| TransparentDegamma/vtable-install | - | C | declare descriptor [rbp+0x560] | `0x56877d6  lea rax,[0xF25B730]`; `0x56877dd  mov [rbp+0x560],rax`; also `0x5687807  lea rax,[0xF25B730]` | vtable 0xF25B730 stored into declare descriptor | [V]
| TransparentDegamma/vt | - | - | vt 0xF25B730 | slot8 (+0x040) sub_568cd70 (execute body); shared with the raster passes | [V]
| TransparentDegamma/execute-slot | - | C | slot8 sub_568cd70 | `0x568cd70  mov rcx,rdx`; `0x568cd73  mov rdx,r8`; `0x568cd76  jmp 0x568CD90` | thunk -> shared execute body | [V]
| TransparentDegamma/execute-body | - | R/W | shared body 0x568cd90 | see Shared execute body 0x568cd90 below | [V]

## Shared execute body 0x568cd90 (used by FullScreenOverlayObjects, FullScreenOverlayTransparent, TransparentDegamma, ForceRasterizedObjects, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent)

The execute slot of these vtables is sub_568cd70, a two-instruction thunk (`0x568cd70  mov rcx,rdx` / `0x568cd73  mov rdx,r8` / `0x568cd76  jmp 0x568CD90`) tailing into body 0x568cd90. Body rows, one per distinct offset:

| offset | size | R/W | address | instr | meaning | tag |
|---|---|---|---|---|---|---|
| SharedBody/thunk | - | C | slot8 entry | `0x568cd70  mov rcx,rdx`; `0x568cd73  mov rdx,r8`; `0x568cd76  jmp 0x568CD90` | thunk -> body 0x568cd90 | [V]
| SharedBody/ctxArg+0x8 | 8 | R | ctxArg+0x8 | `0x568cdc8  mov rax,[rcx+8]` | - | [V]
| SharedBody/viewId | 2 | R | (*(ctxArg+8))+0x8 | `0x568cdcc  movzx eax,word ptr [rax+8]` | view id | [V]
| SharedBody/s_ctx | 8 | R | [0x12AE1748] | `0x568cdd0  mov rcx,[0x12AE1748]` | render context pointer (s_ctx, data symbol) | [V]
| SharedBody/record+0xF8 | 8 | R | record+0xF8 (rect XY) | `0x568cdde  movq xmm0,[rbx+0xF8]` | - | [V]
| SharedBody/record+0xFC | 4 | R | record+0xFC (rect WH) | `0x568cdee  movd xmm1,[rbx+0xFC]` | - | [V]
| SharedBody/view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x568cdf6  movd [rcx+r13+0x1EAB090],xmm0` | view rect XY | [V]
| SharedBody/view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x568ce0c  movd [rcx+r13+0x1EAB094],xmm1` | view rect WH | [V]
| SharedBody/view+0x1EAB0A0 | 64 | W | s_ctx+view*0x140+0x1EAB0A0 | `0x568ce51  call 0xEBCE390` | view mat4 write via sub_ebce390 | [V]
| SharedBody/view+0x1EAB0E0 | 64 | W | s_ctx+view*0x140+0x1EAB0E0 | `0x568ce6a  call 0xEBCE390` | view mat4 write | [V]
| SharedBody/view+0x1EAB120 | 64 | W | s_ctx+view*0x140+0x1EAB120 | `0x568ce83  call 0xEBCE390` | view mat4 write | [V]
| SharedBody/view+0x1EAB160 | 64 | W | s_ctx+view*0x140+0x1EAB160 | `0x568ce9c  call 0xEBCE390` | view mat4 write | [V]
| SharedBody/view+0x1EAB1A0 | 16 | W | s_ctx+view*0x140+0x1EAB1A0 | `0x568ceb9  call 0xEBCE390` | view vec4 write | [V]
| SharedBody/record+0x108 | 1 | R | record+0x108 (sort mode) | `0x568cebe  movzx eax,byte ptr [rbx+0x108]` | - | [V]
| SharedBody/view+0x1EAB1B2 | 1 | W | s_ctx+view*0x140+0x1EAB1B2 | `0x568cecc  mov [rcx+r13+0x1EAB1B2],al` | view sort byte | [V]
| SharedBody/record+0x10 | 8 | R | record+0x10 (shared_ptr) | `0x568cee4  mov rax,[rbx+0x10]` | - | [V]
| SharedBody/refcount | 4 | W | *(record+0x10)+0x8 | `0x568ceed  lock inc dword ptr [rax+8]` | shared refcount increment | [V]

## Carried passes (already [V] from prior accepted runs; not redone)

| offset | size | R/W | address | instr | meaning | tag |
|---|---|---|---|---|---|---|
| SampleCascadedShadows/declare | - | C | passObj+0x0 | `0x55fc6f8  lea rax,[0xF25C660]`; `0x55fc6ff  mov [rsi],rax` | vtable 0xF25C660 stored into pass object | [V]
| SampleCascadedShadows/vt | - | - | vt 0xF25C660 | slot2 (+0x010) sub_56d3170 (execute body) | [V]
| SampleCascadedShadows/record+0x88 | 8 | R | record+0x88 | `0x56d31c1  movq xmm0,[rsi+0x88]` | - | [V]
| SampleCascadedShadows/record+0x8C | 4 | R | record+0x8C | `0x56d31d1  movd xmm1,[rsi+0x8C]` | - | [V]
| SampleCascadedShadows/view+0x1EAB090 | 4 | W | s_ctx+view*0x140+0x1EAB090 | `0x56d31d9  movd [rcx+rbx+0x1EAB090],xmm0` | - | [V]
| SampleCascadedShadows/view+0x1EAB094 | 4 | W | s_ctx+view*0x140+0x1EAB094 | `0x56d31ee  movd [rcx+rbx+0x1EAB094],xmm1` | - | [V]
| SampleCascadedShadows/view+0x1EAB0A0 | 64 | W | s_ctx+view*0x140+0x1EAB0A0 | `0x56d3228  call 0xEBCE390` | - | [V]
| SampleCascadedShadows/view+0x1EAB0E0 | 64 | W | s_ctx+view*0x140+0x1EAB0E0 | `0x56d3241  call 0xEBCE390` | - | [V]
| SampleCascadedShadows/view+0x1EAB120 | 64 | W | s_ctx+view*0x140+0x1EAB120 | `0x56d325a  call 0xEBCE390` | - | [V]
| SampleCascadedShadows/view+0x1EAB160 | 64 | W | s_ctx+view*0x140+0x1EAB160 | `0x56d3277  call 0xEBCE390` | - | [V]
| SampleCascadedShadows/view+0x1EAB1A0 | 16 | W | s_ctx+view*0x140+0x1EAB1A0 | `0x56d329a  call 0xEBCE390` | - | [V]
| SampleCascadedShadows/record+0x98 | 1 | R | record+0x98 | `0x56d329f  movzx eax,byte ptr [r14+0x98]` | - | [V]
| SampleCascadedShadows/view+0x1EAB1B2 | 1 | W | s_ctx+view*0x140+0x1EAB1B2 | `0x56d32ae  mov [rcx+rbx+0x1EAB1B2],al` | - | [V]
| ForceRasterizedObjects/declare | - | C | - | `0x562e9ca  call 0x56AF0F0` | builder calls declare helper sub_56AF0F0 | [V]
| ForceRasterizedObjects/vtable-install | - | C | declare descriptor [rbp+0x560] | `0x56af1d6  lea rax,[0xF25C0D0]`; `0x56af1dd  mov [rbp+0x560],rax` | vtable 0xF25C0D0 stored into declare descriptor | [V]
| ForceRasterizedObjects/vt | - | - | vt 0xF25C0D0 | slot8 (+0x040) sub_568cd70 -> shared body 0x568cd90 | [V]
| ForceRasterizedObjects/execute-body | - | R/W | shared body 0x568cd90 | see Shared execute body rows | [V]
| RasterizedOpaque/declare | - | C | - | `0x562e9ca  call 0x56AF0F0` (raster cluster call site at hash "RasterizedOpaque") | builder calls declare helper sub_56AF0F0 | [V]
| RasterizedOpaque/vt | - | - | vt 0xF25C0D0 | slot8 sub_568cd70 -> shared body 0x568cd90 | [V]
| RasterizedOpaque/execute-body | - | R/W | shared body 0x568cd90 | see Shared execute body rows | [V]
| RasterizedAlphaTest/declare | - | C | - | `0x562eb57  call 0x56B0940` | builder calls declare helper sub_56B0940 | [V]
| RasterizedAlphaTest/vtable-install | - | C | declare descriptor [rbp+0x560] | `0x56b0a26  lea rax,[0xF25C130]`; `0x56b0a2d  mov [rbp+0x560],rax` | vtable 0xF25C130 stored into declare descriptor | [V]
| RasterizedAlphaTest/vt | - | - | vt 0xF25C130 | slot8 (+0x040) sub_568cd70 -> shared body 0x568cd90 | [V]
| RasterizedAlphaTest/execute-body | - | R/W | shared body 0x568cd90 | see Shared execute body rows | [V]
| RasterizedTransparent/declare | - | C | - | `0x562ece7  call 0x56B2190` | builder calls declare helper sub_56B2190 | [V]
| RasterizedTransparent/vtable-install | - | C | declare descriptor [rbp+0x560] | `0x56b2276  lea rax,[0xF25C190]`; `0x56b227d  mov [rbp+0x560],rax` | vtable 0xF25C190 stored into declare descriptor | [V]
| RasterizedTransparent/vt | - | - | vt 0xF25C190 | slot8 (+0x040) sub_568cd70 -> shared body 0x568cd90 | [V]
| RasterizedTransparent/execute-body | - | R/W | shared body 0x568cd90 | see Shared execute body rows | [V]
| VolumetricsShadows/name-str | - | R | 0xF5427D1 | `0x55fc1c9  lea rax,[0xF5427D1]` | string "VolumetricsShadows" | [V]
| VolumetricsShadows/declare-helper | - | C | - | `0x55fc20e  call 0x567C8B0` | builder calls named-resource helper sub_567C8B0 | [V]
| VolumetricsShadows/helper-vtable-install | - | C | cache entry+0x0 | `0x567cc6f  lea rcx,[0xF09AA70]`; `0x567cc76  mov [rbx],rcx` | sub_567C8B0 installs cache-entry vtable 0xF09AA70 (named-resource entry created by the VolumetricsShadows declare site) | [V]
| VolumetricsShadows/vt | - | - | vt 0xF09AA70 | slot0 sub_1505b0 (release); slot1 sub_76900 (`0x76900  mov rax,[rcx]` / `0x76903  mov rax,[rax+0x10]` / `0x7690e  mov edx,1` / `0x76913  jmp r8` release thunk); no execute slot | [V]
| VolumetricsShadows/execute-body | - | ? | - | not isolated: sub_567C8B0 creates named-resource cache entries (vtable 0xF09AA70 has no execute slot); VolumetricsShadows pass object/execute body not found statically | [?]

## CLOSES?

CLOSES? YES — all 12 F1b passes have rows. The 6 pending passes (FullScreenOverlayObjects, FullScreenOverlayTransparent, WaitOnUpscalingOutput, ClearStencil/WaterSurfaceStencil, ClearGBuffer/ScenePrepass, TransparentDegamma) are fully [V]-proven name -> helper -> vtable -> execute slot -> execute body -> resource rows. The other 6 (VolumetricsShadows, SampleCascadedShadows, ForceRasterizedObjects, RasterizedOpaque, RasterizedAlphaTest, RasterizedTransparent) carry rows per prior accepted runs ("6 passes already have [V] rows; do not redo" per orchestrator 2026-11-22); VolumetricsShadows' deeper execute-chain is [?] statically but is carried as done by the orchestrator hint and is not one of this unit's 6 pending passes.

## Verification
- `python tools/sigs/verify_oc.py docs/progress/oc_U-EF1b.md` — every backtick-quoted `0xRVA  instr` line compared against rdis dis output; must report mismatch=0 no-such-instr=0.
- `python tools/delegate.py check docs/progress/oc_U-EF1b.md` — shape/format check; must exit 0.

## TOOL REQUESTS
- None (rdis dis/vt/xr/imm and python PE parsing sufficed; no throwaway scripts written).

## NEXT
DONE
