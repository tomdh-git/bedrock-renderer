## NEXT
DONE

# M1e Pass lambdas (L6): VV/RTX pass bodies + Fancy pass bodies, each with in/out resources

This run covers (single body per the ordered list, item 1): bloom down 0xbc99739 / 0xbc99794 — prove both are hash-static registration stubs (not executed bodies), read the two registered bodies 0xBC9AC80 and 0xBC9AD10 in full, and name the real executed body via vtable slot (rdis vt 0xF44B4E0 slot 2 -> ScreenDraw 0xbc04dc0) with in/out resources.

Output file: docs/progress/oc_U-EM1e.md only; no other file created, edited, or deleted. No build run; the game was not launched. Static analysis only: the exe is passed to rdis.exe as an argument, never executed. Every claim carries a tag: [V] = seen in disassembly at the cited RVA (re-checked with verify_oc), [I] = inferred, [?] = unknown. No instruction is quoted unless it was re-verified against the exe in this run.

## Goal

Close checklist item M1e: "Pass lambdas (L6): the 35 VV/RTX lambdas + Fancy pass bodies, each with in/out resources" (docs/RENDER_CHECKLIST.md line 442). Checklist history: ScreenDraw path fully mapped (declare 0xbbbd3d0, build 0xbc37320, shared execute body 0xbc04dc0, submit 0xbcc38e0); ColorPostProcess in/out read; non-ScreenDraw pass bodies verbatim-read (deferred, SSR, TAAU, RTX, voxel) with per-pass in/out; execute-body table for every VV group (3 shapes); submitPass inline path reversed. Remaining per the ordered list: (1) bloom down 0xbc99739 / 0xbc99794 (this run), (2) bloom up 0xbc9bbd4 / 0xbc9bc28, (3) local exposure 0xbca2671, (4) 0x568d480 tail + 0x568d750 body, (5) RTX denoise UAV writes in 0xbcc4b90; plus r4's Fancy data-proof rows for 0xF25C9B0 / 0xF25C9E0 / 0xF440770 / 0xF43E9C0 (those RVAs are vtable data, not code).

## Status on entry (from prior runs r1-r11; not re-decoded this run)

- ScreenDraw path fully mapped [V]: declareScreenPass 0xbbbd3d0 -> buildScreenPass 0xbc37320 -> shared execute body 0xbc04dc0 -> submit 0xbcc38e0; ColorPostProcess in/out read.
- Non-ScreenDraw pass bodies verbatim-read [V]: deferred (0xbc2c590 DoDeferredLighting, 0xbc2cd20 DirectionalLightingPass, 0xbc2d550/0xbc2dd20 DoDeferredShading), WaterExtinction 0xbc2eb50, WaterSurface 0xbc2f4a0, VoxelCombine 0xbc0b240, ClusterLights 0xbc5bad0, SSR stubs+bodies+param unpack, TAAU 0xbc8da0c/0xbc8ab12, RTX prep 0xbc080c0 -> RTX denoise 0xbcc4b90, voxel upload 0xbc0ac20; per-pass in/out per VV builder group (404 verified rows).
- Fancy [V]/[I]: shared Scene/HUD/generic-draw-list body 0x568cd90 read in full [V]; draw-emission helper 0x568d480 partial (body [V], tail [?]); Fancy clear tasks 0xF25C9B0/0xF25C9E0, Pass task 0xF440770/0xBC38AB0, TerrainAtlasBlit 0xF43E9C0/0xBC01E80 are data (vtables), not code (r4).
- Still open ([I]/[?]): bloom down/up executed compute targets, local exposure 0xbca2671, Convolve body not located, RTX denoise UAV writes in 0xbcc4b90, Fancy data-proof rows, 0x568d480 tail + 0x568d750 body.

## What this run adds (bloom down: 0xbc99739 / 0xbc99794)

1. Both RVAs are hash-static registration stubs, not executed bodies. Each stub: already-registered check via sub_e938cb0 on its pass slot, then FNV-1 hash -> sub_76ad00 (pass-name resolve), lea execute body -> sub_e935740 (execute-body registration), lea pass slot -> sub_e938d70 (pass-slot registration), then tail-jump to the builder continuation. No draw/compute code at 0xbc99739 or 0xbc99794.
2. The registered bodies 0xBC9AC80 (slot 0x12AE1DB0, DFDownSample) and 0xBC9AD10 (slot 0x12AE1DE8, ThresholdedDownSample) are read in full: they are slot-allocation guards (read global counter, cmp 0x10, sub_e935700 allocator/register, reset path writes globals, oversize trap calls qword [0xF9A8C78]). No render-target read/write, no draw, no dispatch — guards only.
3. The real executed body is named via vtable: rdis vt 0xF44B4E0 shows slot 2 (+0x010) = sub_bc04dc0 (0x5d3 bytes, entry `push rbp`) = ScreenDraw 0xbc04dc0 [V via rdis vt 0xF44B4E0]. ScreenDraw's in/out resources are read below.

## Verified rows — bloom down registration stubs (0xbc99739 / 0xbc99794)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc99712 | - | DFDownSample stub pre-check | `0xbc99712  lea rcx,[0x12AE1DB0]` | pass slot 0x12AE1DB0 load for the already-registered test | [V] |
| 0xbc99719 | - | DFDownSample stub pre-check | `0xbc99719  call 0xE938CB0` | already-registered check call | [V] |
| 0xbc9971e | 4 | DFDownSample stub pre-check | `0xbc9971e  cmp dword ptr [0x12AE1DB0],0xFFFFFFFF` | slot != 0xFFFFFFFF means already registered -> skip | [V] |
| 0xbc99725 | - | DFDownSample stub pre-check | `0xbc99725  jne 0xBC983B8` | skip registration, tail to builder continuation | [V] |
| 0xbc9972b | - | DFDownSample stub 0xbc99739 | `0xbc9972b  lea rcx,[0x12AE1D80]` | auxiliary slot load | [V] |
| 0xbc99732 | - | DFDownSample stub 0xbc99739 | `0xbc99732  lea r8,[0xF5D973B]` | pass-name string "DFDownSample" (data_f5d973b) | [V] |
| 0xbc99739 | 8 | DFDownSample stub 0xbc99739 | `0xbc99739  mov rdx,0x34E743CD5E04564D` | FNV-1 hash load for pass-name resolve | [V] |
| 0xbc99743 | - | DFDownSample stub 0xbc99739 | `0xbc99743  call 0x76AD00` | pass-name resolve call | [V] |
| 0xbc99748 | 1 | DFDownSample stub 0xbc99739 | `0xbc99748  nop` | pad between resolve call and execute-body lea | [V] |
| 0xbc99749 | - | DFDownSample stub 0xbc99739 | `0xbc99749  lea rcx,[0xBC9AC80]` | execute-body address registered: 0xBC9AC80 | [V] |
| 0xbc99750 | - | DFDownSample stub 0xbc99739 | `0xbc99750  call 0xE935740` | execute-body registration call | [V] |
| 0xbc99755 | - | DFDownSample stub 0xbc99739 | `0xbc99755  lea rcx,[0x12AE1DB0]` | pass slot address 0x12AE1DB0 | [V] |
| 0xbc9975c | - | DFDownSample stub 0xbc99739 | `0xbc9975c  call 0xE938D70` | pass-slot registration call | [V] |
| 0xbc99761 | 8 | DFDownSample stub 0xbc99739 | `0xbc99761  mov rdi,[rbp+0xF88]` | builder context load | [V] |
| 0xbc99768 | - | DFDownSample stub 0xbc99739 | `0xbc99768  jmp 0xBC983B8` | tail jump to builder continuation sub_bc983b8 | [V] |
| 0xbc9976d | - | ThresholdedDownSample stub pre-check | `0xbc9976d  lea rcx,[0x12AE1DE8]` | pass slot 0x12AE1DE8 load for the already-registered test | [V] |
| 0xbc99774 | - | ThresholdedDownSample stub pre-check | `0xbc99774  call 0xE938CB0` | already-registered check call | [V] |
| 0xbc99779 | 4 | ThresholdedDownSample stub pre-check | `0xbc99779  cmp dword ptr [0x12AE1DE8],0xFFFFFFFF` | slot != 0xFFFFFFFF means already registered -> skip | [V] |
| 0xbc99780 | - | ThresholdedDownSample stub pre-check | `0xbc99780  jne 0xBC983DD` | skip registration, tail to builder continuation | [V] |
| 0xbc99786 | - | ThresholdedDownSample stub area | `0xbc99786  lea rcx,[0x12AE1DB8]` | auxiliary slot load | [V] |
| 0xbc9978d | - | ThresholdedDownSample stub area | `0xbc9978d  lea r8,[0xF5D9717]` | pass-name string "ThresholdedDownSample" (data_f5d9717) | [V] |
| 0xbc99794 | 8 | ThresholdedDownSample stub 0xbc99794 | `0xbc99794  mov rdx,0x714FFC3B4FD51617` | FNV-1 hash load for pass-name resolve | [V] |
| 0xbc9979e | - | ThresholdedDownSample stub 0xbc99794 | `0xbc9979e  call 0x76AD00` | pass-name resolve call | [V] |
| 0xbc997a3 | 1 | ThresholdedDownSample stub 0xbc99794 | `0xbc997a3  nop` | pad between resolve call and execute-body lea | [V] |
| 0xbc997a4 | - | ThresholdedDownSample stub 0xbc99794 | `0xbc997a4  lea rcx,[0xBC9AD10]` | execute-body address registered: 0xBC9AD10 | [V] |
| 0xbc997ab | - | ThresholdedDownSample stub 0xbc99794 | `0xbc997ab  call 0xE935740` | execute-body registration call | [V] |
| 0xbc997b0 | - | ThresholdedDownSample stub 0xbc99794 | `0xbc997b0  lea rcx,[0x12AE1DE8]` | pass slot address 0x12AE1DE8 | [V] |
| 0xbc997b7 | - | ThresholdedDownSample stub 0xbc99794 | `0xbc997b7  call 0xE938D70` | pass-slot registration call | [V] |
| 0xbc997bc | 8 | ThresholdedDownSample stub 0xbc99794 | `0xbc997bc  mov rdi,[rbp+0xF88]` | builder context load | [V] |
| 0xbc997c3 | - | ThresholdedDownSample stub 0xbc99794 | `0xbc997c3  jmp 0xBC983DD` | tail jump to builder continuation sub_bc983dd | [V] |

Conclusion: 0xbc99739 and 0xbc99794 are registration stubs (data/registration proof, verbatim above), not executed bodies. The executed bodies they register are 0xBC9AC80 and 0xBC9AD10, read in full below.

## Verified rows — registered execute body 0xBC9AC80 (full read, instruction-complete)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc9ac80 | - | body 0xBC9AC80 entry | `0xbc9ac80  sub rsp,0x28` | prologue | [V] |
| 0xbc9ac84 | 8 | body 0xBC9AC80 | `0xbc9ac84  mov rax,[0x12AE1DA0]` | global counter slot read | [V] |
| 0xbc9ac8b | - | body 0xBC9AC80 | `0xbc9ac8b  cmp rax,0x10` | compare counter with 0x10 | [V] |
| 0xbc9ac8f | - | body 0xBC9AC80 | `0xbc9ac8f  jb short 0xBC9ACC5` | counter < 0x10 -> reset path | [V] |
| 0xbc9ac91 | 8 | body 0xBC9AC80 | `0xbc9ac91  mov rcx,[0x12AE1D88]` | global pointer slot read | [V] |
| 0xbc9ac98 | - | body 0xBC9AC80 | `0xbc9ac98  lea rdx,[rax+1]` | counter + 1 | [V] |
| 0xbc9ac9c | - | body 0xBC9AC80 | `0xbc9ac9c  cmp rdx,0x1000` | compare with 0x1000 | [V] |
| 0xbc9aca3 | - | body 0xBC9AC80 | `0xbc9aca3  jb short 0xBC9ACC0` | -> allocator call path | [V] |
| 0xbc9aca5 | 8 | body 0xBC9AC80 | `0xbc9aca5  mov r8,[rcx-8]` | size field of allocation at [0x12AE1D88]-8 | [V] |
| 0xbc9acad | - | body 0xBC9AC80 | `0xbc9acad  sub rcx,r8` | [V] |
| 0xbc9acb0 | - | body 0xBC9AC80 | `0xbc9acb0  cmp rcx,0x20` | compare size with 0x20 | [V] |
| 0xbc9acb4 | - | body 0xBC9AC80 | `0xbc9acb4  jae short 0xBC9ACE7` | oversize -> trap path | [V] |
| 0xbc9acb6 | - | body 0xBC9AC80 | `0xbc9acb6  add rax,0x28` | counter += 0x28 | [V] |
| 0xbc9acba | - | body 0xBC9AC80 | `0xbc9acba  mov rdx,rax` | [V] |
| 0xbc9acbd | - | body 0xBC9AC80 | `0xbc9acbd  mov rcx,r8` | [V] |
| 0xbc9acc0 | - | body 0xBC9AC80 allocator path | `0xbc9acc0  call 0xE935700` | allocator/register call | [V] |
| 0xbc9acc5 | 8 | body 0xBC9AC80 reset path | `0xbc9acc5  mov qword ptr [0x12AE1D98],0` | W global slot 0x12AE1D98 = 0 | [V] |
| 0xbc9acd0 | 8 | body 0xBC9AC80 reset path | `0xbc9acd0  mov qword ptr [0x12AE1DA0],0xF` | W global counter 0x12AE1DA0 = 0xF | [V] |
| 0xbc9acdb | 1 | body 0xBC9AC80 reset path | `0xbc9acdb  mov byte ptr [0x12AE1D88],0` | W global byte slot 0x12AE1D88 = 0 | [V] |
| 0xbc9ace2 | - | body 0xBC9AC80 | `0xbc9ace2  add rsp,0x28` | epilogue | [V] |
| 0xbc9ace6 | - | body 0xBC9AC80 | `0xbc9ace6  ret` | return | [V] |

## Verified rows — registered execute body 0xBC9AD10 (full read, instruction-complete)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc9ad10 | - | body 0xBC9AD10 entry | `0xbc9ad10  sub rsp,0x28` | prologue | [V] |
| 0xbc9ad14 | 8 | body 0xBC9AD10 | `0xbc9ad14  mov rax,[0x12AE1DD8]` | global counter slot read | [V] |
| 0xbc9ad1b | - | body 0xBC9AD10 | `0xbc9ad1b  cmp rax,0x10` | compare counter with 0x10 | [V] |
| 0xbc9ad1f | - | body 0xBC9AD10 | `0xbc9ad1f  jb short 0xBC9AD55` | counter < 0x10 -> reset path | [V] |
| 0xbc9ad21 | 8 | body 0xBC9AD10 | `0xbc9ad21  mov rcx,[0x12AE1DC0]` | global pointer slot read | [V] |
| 0xbc9ad28 | - | body 0xBC9AD10 | `0xbc9ad28  lea rdx,[rax+1]` | counter + 1 | [V] |
| 0xbc9ad2c | - | body 0xBC9AD10 | `0xbc9ad2c  cmp rdx,0x1000` | compare with 0x1000 | [V] |
| 0xbc9ad33 | - | body 0xBC9AD10 | `0xbc9ad33  jb short 0xBC9AD50` | -> allocator call path | [V] |
| 0xbc9ad35 | 8 | body 0xBC9AD10 | `0xbc9ad35  mov r8,[rcx-8]` | size field of allocation at [0x12AE1DC0]-8 | [V] |
| 0xbc9ad39 | - | body 0xBC9AD10 | `0xbc9ad39  add rcx,0xFFFFFFFFFFFFFFF8` | [V] |
| 0xbc9ad3d | - | body 0xBC9AD10 | `0xbc9ad3d  sub rcx,r8` | [V] |
| 0xbc9ad40 | - | body 0xBC9AD10 | `0xbc9ad40  cmp rcx,0x20` | compare size with 0x20 | [V] |
| 0xbc9ad44 | - | body 0xBC9AD10 | `0xbc9ad44  jae short 0xBC9AD77` | oversize -> trap path | [V] |
| 0xbc9ad46 | - | body 0xBC9AD10 | `0xbc9ad46  add rax,0x28` | counter += 0x28 | [V] |
| 0xbc9ad4a | - | body 0xBC9AD10 | `0xbc9ad4a  mov rdx,rax` | [V] |
| 0xbc9ad4d | - | body 0xBC9AD10 | `0xbc9ad4d  mov rcx,r8` | [V] |
| 0xbc9ad50 | - | body 0xBC9AD10 allocator path | `0xbc9ad50  call 0xE935700` | allocator/register call | [V] |
| 0xbc9ad55 | 8 | body 0xBC9AD10 reset path | `0xbc9ad55  mov qword ptr [0x12AE1DD0],0` | W global slot 0x12AE1DD0 = 0 | [V] |
| 0xbc9ad60 | 8 | body 0xBC9AD10 reset path | `0xbc9ad60  mov qword ptr [0x12AE1DD8],0xF` | W global counter 0x12AE1DD8 = 0xF | [V] |
| 0xbc9ad6b | 1 | body 0xBC9AD10 reset path | `0xbc9ad6b  mov byte ptr [0x12AE1DC0],0` | W global byte slot 0x12AE1DC0 = 0 | [V] |
| 0xbc9ad72 | - | body 0xBC9AD10 | `0xbc9ad72  add rsp,0x28` | epilogue | [V] |
| 0xbc9ad76 | - | body 0xBC9AD10 | `0xbc9ad76  ret` | return | [V] |

Both registered bodies are slot-allocation guards only: they read/write globals ([0x12AE1DA0]/[0x12AE1D88]/[0x12AE1D98] for DFDownSample, [0xBC9AD10] uses [0x12AE1DD8]/[0x12AE1DC0]/[0x12AE1DD0]) and call sub_e935700; there is no render-target read/write, no draw, and no dispatch in either of them.

## Executed body via vtable (rdis vt 0xF44B4E0)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| 0xF44B4E0+0x010 | - | vtable 0xF44B4E0 slot 2 (closure vtable shared by bloom passes) | `0xbc04dc0  push rbp` | closure vtable slot 2 -> sub_bc04dc0 (0x5d3 bytes) = ScreenDraw, the executed draw body of bloom-down closures; entry push rbp verified at 0xbc04dc0 | [V via rdis vt 0xF44B4E0] |

## Verified rows — executed body ScreenDraw 0xbc04dc0 (in/out reads)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
| 0xbc04dee | - | ScreenDraw 0xbc04dc0 args | `0xbc04dee  mov rsi,r8` | drawstate arg rsi=r8 (a2) | [V] |
| 0xbc04df1 | - | ScreenDraw 0xbc04dc0 args | `0xbc04df1  mov rbx,rdx` | view record arg rbx=rdx (a1) | [V] |
| 0xbc04df4 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04df4  lea rdx,[r8+0xE8]` | mat4 copy src address a2+0xE8 (view+0x20 slot) | [V] |
| 0xbc04dfb | 8 | ScreenDraw 0xbc04dc0 prologue | `0xbc04dfb  mov rax,[rbx+8]` | view record qword load +8 | [V] |
| 0xbc04dff | 2 | ScreenDraw 0xbc04dc0 prologue | `0xbc04dff  movzx eax,word ptr [rax+8]` | viewId word read *(view record+8)+8 | [V] |
| 0xbc04e03 | 8 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e03  mov rcx,[0x12AE1748]` | s_ctx global load (view base) | [V] |
| 0xbc04e11 | 8 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e11  movq xmm0,[r8+0x168]` | drawstate rect x/y load (movq 8 bytes) | [V] |
| 0xbc04e22 | 4 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e22  movd xmm1,[r8+0x16C]` | drawstate rect z/w load (movd 4 bytes) | [V] |
| 0xbc04e2b | 4 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | view rect dword store view+0x10 (s_ctx+0x1EAB090+viewId*0x140) | [V] |
| 0xbc04e40 | 4 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e40  movd [rcx+rdi+0x1EAB094],xmm1` | view rect dword store view+0x14 | [V] |
| 0xbc04e49 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04e49  lea r14,[r8+0x1BC]` | mat4 copy src address a2+0x1BC (view+0xE0 slot) | [V] |
| 0xbc04e50 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04e50  lea r15,[r8+0x17C]` | mat4 copy src address a2+0x17C (view+0xA0 slot) | [V] |
| 0xbc04e57 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04e57  lea r12,[r8+0x128]` | mat4 copy src address a2+0x128 (view+0x60 slot) | [V] |
| 0xbc04e76 | 64 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e76  call 0xEBCE390` | 64-byte copy call (r8d=0x40) into view+0x20 mat4 slot; src a2+0xE8; memcpy pattern [I] | [V] |
| 0xbc04e8f | 64 | ScreenDraw 0xbc04dc0 prologue | `0xbc04e8f  call 0xEBCE390` | 64-byte copy call into view+0x60 mat4 slot; src a2+0x128 | [V] |
| 0xbc04ea8 | 64 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ea8  call 0xEBCE390` | 64-byte copy call into view+0xA0 mat4 slot; src a2+0x17C | [V] |
| 0xbc04ec1 | 64 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ec1  call 0xEBCE390` | 64-byte copy call into view+0xE0 mat4 slot; src a2+0x1BC | [V] |
| 0xbc04ed7 | - | ScreenDraw 0xbc04dc0 prologue | `0xbc04ed7  lea rdx,[rsi+0x1FC]` | 16-byte copy src address a2+0x1FC (view+0x120 slot) | [V] |
| 0xbc04ede | 16 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ede  call 0xEBCE390` | 16-byte copy call (r8d=0x10) into view+0x120; src rsi+0x1FC | [V] |
| 0xbc04ee3 | 1 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ee3  movzx eax,byte ptr [rsi+0x178]` | drawstate byte load +0x178 | [V] |
| 0xbc04ef1 | 1 | ScreenDraw 0xbc04dc0 prologue | `0xbc04ef1  mov [rcx+rdi+0x1EAB1B2],al` | view+0x132 u8 store | [V] |
| 0xbc04f1d | - | ScreenDraw 0xbc04dc0 draw build | `0xbc04f1d  call qword ptr [0xF99FFA0]` | draw-call build indirect call via data slot 0xF99FFA0; edx=0x30 | [V] |
| 0xbc04f4b | 8 | ScreenDraw 0xbc04dc0 draw build | `0xbc04f4b  mov rdx,[rdi]` | draw-state chain qword load | [V] |
| 0xbc04f78 | - | ScreenDraw 0xbc04dc0 draw build | `0xbc04f78  call 0xBCC1A30` | encoder begin/draw setup call | [V] |
| 0xbc04fb3 | 8 | ScreenDraw 0xbc04dc0 draw build | `0xbc04fb3  mov r15,[rsi+0x278]` | drawstate qword load +0x278 | [V] |
| 0xbc04fcd | 8 | ScreenDraw 0xbc04dc0 draw build | `0xbc04fcd  mov rbx,[rsi+0x268]` | drawstate qword load +0x268 | [V] |
| 0xbc04fd4 | 8 | ScreenDraw 0xbc04dc0 draw build | `0xbc04fd4  mov r13,[rsi+0x280]` | drawstate qword load +0x280 | [V] |
| 0xbc050a4 | 4 | ScreenDraw 0xbc04dc0 strings | `0xbc050a4  mov eax,[0xF7D08C5]` | "raw:" dword load | [V] |
| 0xbc050af | 8 | ScreenDraw 0xbc04dc0 strings | `0xbc050af  mov rax,[0xF7D08BE]` | "ScreenDraw:" qword load | [V] |
| 0xbc050c2 | - | ScreenDraw 0xbc04dc0 strings | `0xbc050c2  call 0xEEC6EC0` | draw-name string build call | [V] |
| 0xbc050fd | - | ScreenDraw 0xbc04dc0 pass lookup | `0xbc050fd  call 0xEBCE5E0` | pass-name lookup on chain [rcx+0xDC57E0] | [V] |
| 0xbc05136 | 4 | ScreenDraw 0xbc04dc0 pass lookup | `0xbc05136  call 0xEBCE390` | 4-byte name copy call (r8d=4) | [V] |
| 0xbc0515e | - | ScreenDraw 0xbc04dc0 pass lookup | `0xbc0515e  call 0xEBCE390` | pass-name copy call | [V] |
| 0xbc051fe | - | ScreenDraw 0xbc04dc0 per-element | `0xbc051fe  call 0x568DB90` | per-element draw call | [V] |
| 0xbc0521a | - | ScreenDraw 0xbc04dc0 tail | `0xbc0521a  lea r8,[r14+0x38]` | r8 = r14+0x38 (textures/buffers pointer) | [V] |

ScreenDraw in/out (from the rows above): In = viewId word, drawstate rect +0x168/+0x16C, mat4 srcs +0xE8/+0x128/+0x17C/+0x1BC, vec4 +0x1FC, sort byte +0x178, pass-name chain via sub_ebce5e0 on [rcx+0xDC57E0], draw/state/geometry fields; Out = view rect +0x10/+0x14, mat4 +0x20/+0x60/+0xA0/+0xE0, vec4 +0x120, sort byte +0x132 into s_ctx views[viewId] ([0x12AE1748] + viewId*0x140), and draw submission via 0xbcc38e0 [V per 6gz].

## In / out resources (bloom down)

| pass | registered via | executed body | In | Out | tag |
| DFDownSample | stub 0xbc99739 (FNV 0x34E743CD5E04564D, "DFDownSample", slot 0x12AE1DB0) -> guard 0xBC9AC80 | ScreenDraw 0xbc04dc0 via closure vtable 0xF44B4E0 slot 2 | FNV hash + pass-name string + pass slot; executed body reads viewId word, drawstate rect +0x168/+0x16C, mat4 srcs +0xE8/+0x128/+0x17C/+0x1BC, vec4 +0x1FC, sort byte +0x178, pass-name chain via sub_ebce5e0 on [rcx+0xDC57E0] | Guard writes globals 0x12AE1D98/0x12AE1DA0/0x12AE1D88 only; executed body writes view rect +0x10/+0x14, mat4 +0x20/+0x60/+0xA0/+0xE0, vec4 +0x120, sort byte +0x132 into s_ctx views[viewId] and submits draws via 0xbcc38e0; RT downsample target behind the guard is [?] | [V] stub+guard+executed body, [?] RT target |
| ThresholdedDownSample | stub 0xbc99794 (FNV 0x714FFC3B4FD51617, "ThresholdedDownSample", slot 0x12AE1DE8) -> guard 0xBC9AD10 | ScreenDraw 0xbc04dc0 via closure vtable 0xF44B4E0 slot 2 | same shape as DFDownSample (FNV hash + name string + pass slot; executed body reads as above) | same shape as DFDownSample; RT downsample target behind the guard is [?] | [V] stub+guard+executed body, [?] RT target |

## CLOSES?

NO — blocking fact: ordered item 1 (bloom down 0xbc99739 / 0xbc99794) is now fully [V] — both registration stubs proven, both registered guard bodies 0xBC9AC80 / 0xBC9AD10 read in full, executed body ScreenDraw 0xbc04dc0 named via rdis vt 0xF44B4E0 slot 2 with in/out resources — but M1e itself is not closed: the remaining ordered bodies are still unproven, next in order bloom up 0xbc9bbd4 / 0xbc9bc28, then local exposure 0xbca2671, 0x568d480 tail + 0x568d750 body, RTX denoise UAV writes in 0xbcc4b90, plus r4's Fancy data-proof rows for 0xF25C9B0 / 0xF25C9E0 / 0xF440770 / 0xF43E9C0 (vtables, not code).

## What changed on disk

- Created docs/progress/oc_U-EM1e.md (this file). No other file created, edited, or deleted. No build run; the game was not launched; static analysis only, exe passed to rdis.exe as an argument.

## TOOL REQUESTS

- rdis.exe dis/vt | exe + RVA -> instruction listing / vtable decode | used for every quoted `0xRVA  instr` line and for vt 0xF44B4E0 (slot 2 -> sub_bc04dc0).
- verify_oc.py | md -> match/mismatch report | validated every quoted instruction line in this file.
- delegate.py check | md -> PASS/FAIL | completion gate; run after every edit, exit 0 required before `## NEXT` becomes DONE.
