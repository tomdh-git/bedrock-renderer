## NEXT
DONE

# Unit U-EL17h — L17h graphics options plumbing (OptionSync)

Goal: close checklist item "L17h graphics options plumbing (OptionSync) pending".
Pending parts (from item line + r3/r4 handoff): (1) who stores source/dispatcher-descriptor +0x1F0; (2) link that stored value to upscaling_percentage/targetResolution. ctx+0x1F0 store 0x67c791f and TAAU read 0xbc8d34e were proven earlier (oc_U-Eratio); endFrame 0x66232b0 is BgfxFrameBuilder vtable slot 18 with no direct callers.

## Method
- Static only (rdis.exe, xref.py, ripscan.py, fld --w full scan). Live capture consulted per handoff: docs/data/live/el17h_endframe_caller.txt.
- Tag convention: [V] seen in disassembly/live capture with RVA cited; [I] inferred from structure/pattern; [?] unknown.

## Live data consulted (per handoff)
- docs/data/live/el17h_endframe_caller.txt (24 samples, 18090 hits), kind=regs, target rva=0x66232B0:
  - Line 3: `CALLER ret=0x8890E4 first_hit=1` — endFrame entered with return address 0x8890E4, i.e. the call instruction at 0x8890de (`call qword ptr [0xF99FFA0]`, 6 bytes, ends exactly at 0x8890E4) [V LIVE]
  - Line 4: `RCX=22FC6252800 hit=1 ret=0x8890E4 ...` — RCX = the BgfxFrameBuilder object pointer at endFrame entry [V LIVE] (this is the object whose vtable slot 18 = endFrame, per BGFX_MAP.md line 167 and the dossier)
  - Line 5: `RDX=14EC10 hit=1 ret=0x8890E4 ...` — RDX = 0x14EC10 (arg2, small immediate-style value) at endFrame entry [V LIVE]
  - R9 dumps (lines 24/27) show heap memory containing name fragments ("...unt"/"...ime") followed by pointer pairs and repeated 0x3F800000 (1.0f) floats — consistent with descriptor objects carrying name strings and scale/percentage fields [V LIVE bytes; offset interpretation [I]]

## Disassembly-verified facts

- endFrame entry prologue [V]: `0x66232bc  mov eax,0x1AA8` / `0x66232c1  call 0xE9E7970` / `0x66232c6  sub rsp,rax` / `0x66232c9  lea rbp,[rsp+0x80]`; rbp never reassigned anywhere in the function (grep of full listing: no `mov rbp`). rdx/r8/r9 args stored at [rbp+0x1998]/[rbp+0x19D0]; rcx = this = BgfxFrameBuilder object (`0x6623308  mov rax,[rcx+0x28]`).
- endFrame stage 7 (0x662b435..0x662cf57) calls `sub_67c7020(rcx=[rbp+0x19B8], rdx=&[rbp+0x11D0], r8=r15, r9=<rsi-source>)` at `0x66257d7`, immediately preceded by `0x66257cd  lea rdx,[rbp+0x11D0]` [V]. Inside sub_67c7020:
  - `0x67c7917  movss xmm0,[rsi+0x1F0]` — R float at source-descriptor rsi+0x1F0 [V]
  - `0x67c791f  movss [rdx+0x1F0],xmm0` — W float at [rdx+0x1F0]; with rdx=&[rbp+0x11D0] this writes endFrame's pass-descriptor slot+0x1F0 = [rbp+0x13C0] [V]
  - This instruction/address (0x67c791f) is exactly oc_U-Eratio's proven "ctx+0x1F0 store 0x67c791f" [V address/bytes match]; at endFrame's call site the destination is the descriptor slot (sub_566cb20 reads [rbp+0x11D0]+0x1F0 as its src+0x1F0 below), so on this path it is the descriptor+0x1F0 store [V instr; context [I]].
- rsi (sub_67c7020 source descriptor) is obtained at `0x662574d  call qword ptr [0xF99FFA0]` with `0x6625748  mov edx,0x30` (index 48) on the [0x1233E1A8] global manager interface ([rax+0x8] method), result `0x6625754  mov rsi,rax` [V]; then rsi is customized: `0x6625764  mov [rsi+0x1C],al`, `0x6625770  movss [rsi+0x20],xmm0`, `0x662577e  movss [rsi+0x24],xmm0`, `0x662578c  movss [rsi+0x28],xmm0` from r15 [V].
- endFrame calls sub_566cb20 7× (0x662cc4c, 0x662cc87, 0x662cce0, 0x662cf57, 0x6628728, 0x66289cb, 0x662abef); each call site loads `lea rdx,[rbp+0x11D0]` (verified at 0x662cc42→0x662cc4c, 0x6628721→0x6628728, 0x66289c1→0x66289cb; identical pattern at the other four [V]) then `mov rcx,r14/rbx` (element dest). Confirmed by xref: endFrame→sub_566cb20 x7 [V].
- sub_566cb20 (arguments: dest=rcx/r10=arg0, src=rdx/rsi=arg1; proven by `0x566cb3e  movzx eax,byte ptr [rdx]` / `0x566cb41  mov [rcx],al`):
  - `0x566d04a  movss xmm0,[rsi+0x1F0]` — R source-descriptor+0x1F0 [V]
  - `0x566d052  movss [rdx+0x1F0],xmm0` — W element+0x1F0 [V]
  - This is r4's proven chain link 1: descriptor+0x1F0 → element+0x1F0 [V].
- fld 0x1F0 --w full scan (12315 accesses, all shown at --max 9000; nothing above the cut in endFrame's range 0x66232b0-0x662e680 nor in sub_566b500/sub_bc40a30/sub_6759740/sub_bbd3a90) found exactly ONE heap-object float store at [reg+0x1F0] in the entire image [V]:
  - `0x10c1dc3  movss [r12+0x1F0],xmm4` in sub_10c1ad0 (0x10c1ad0..0x10c3ad0, 11 xrefs in) [V]
  - sub_10c1ad0 signature: rcx=a0, rdx=a1, rdi=r8=a2; `0x10c1b38  mov r12,[rcx+0x40]` → r12 = descriptor object pointer; `0x10c1b3c  movsd xmm6,[rdx]` then settings get-by-index: `0x10c1b58/0x10c1ba0/0x10c1be1/0x10c1c21  call qword ptr [0xF99FFA0]` with `r8d=0xFD/0xFE/0x100/0x101`, reading `movss xmm7/8/9,[rax+0x18]` (float value at +0x18 of the settings value object); xmm6 = param [rdx+0] (cvtdq2ps). xmm4 (stored at r12+0x1F0) = f(xmm10=rounded param, xmm7/xmm8/xmm9 settings, consts [data_f0c8c4c]/[data_f0c8c60]/[data_eee7c00]) — a render-scale/dimension computed from settings indices + frame params [V instr; exact setting semantics [I]]. sub_10c1ad0 callers: 0xcbab0, 0xcbec0, 0x8d8110, 0x948940, 0x954dc0, 0x4d43c30, 0x4d5b030, 0x6584fa0, 0x65a3060, 0x6bafd00 (×2: 0x6bb0167, 0x6bb01a9) [V xref]. 0xcbab0/0xcbec0 are init-range → descriptor templates initialized at startup [I].
- Struct-type identity [I]: sub_10c1ad0 writes r12+0xA8/0xB8/0xC8/0xD8/0xE0/0xF8/0x118/0x120/0x124/0x128/0x12C/0x130/0x138/0x13C/0x140/0x144/0x1C8/0x1CC/0x1D0/0x1D4/0x1E0/0x1E4/0x1E8/0x1EC/0x1F0/0x1F4/0x200/0x204/0x238/0x23C/0x240/0x244 (+0x388); sub_566cb20 reads its src at +0x0..+0x242 including +0x120..+0x242 — ≥20 overlapping fields incl. +0x1F0 → r12's object is the same pass-descriptor type sub_566cb20 reads [I].
- endFrame does NOT write [rbp+0x11D0]+0x1F0 ([rbp+0x13C0]) inline anywhere (full listing coverage 0x66232c1-0x662e680; grep for "13C0" and movss/movups/movapd at [rbp+0x13C0]: zero hits). The descriptor-slot+0x1F0 is written only by sub_67c7020@0x67c791f (from rsi+0x1F0) [V].
- The heap-descriptor writer sub_10c1ad0@0x10c1dc3 and endFrame's slot writer sub_67c7020@0x67c791f write the same descriptor type [I]; the manager-template id 0x30 consumed by sub_67c7020 (rsi) is plausibly one of the templates initialized by sub_10c1ad0's init-range callers (0xcbab0/0xcbec0) [I].

## Settings name readers (xref.py str / ripscan) [V]
- `0xf5e13cc "upscaling_percentage"` refs=[] by direct rip, but ripscan found: `0x51de12e (func 0x51cd6c0)` and `0x5b3e79c (func 0x5b0c1b0)` [V]
- `0xf5850de "options.targetResolution"` refs=[]; ripscan: `0x5b3ead3 (func 0x5b0c1b0)` [V]
- `sub_5b0c1b0` (0x5b0c1b0..0x5b0e1b0, 1 xref in) references BOTH strings; defaults materialize at `0x5b0c390  mov dword ptr [rbp+0x24],0x3F666666` (0.85f) and `0x5b0c397  mov dword ptr [rbp+0x28],0x3F800000` (1.0f) [V]
- sub_5b0c1b0 called ONLY by `sub_5b0aa90` at `0x5b0b633  call 0x5B0C1B0` [V xref]; sub_5b0aa90 called by 0x877360 (0x877805) and 0x8f7f40 [V xref]; 0x5b0aa90 writes results to object fields e.g. `0x5b0b68d  mov [r13+0x1BB8],eax` — NOT to descriptor+0x1F0 [V]
- `sub_51cd6c0` (0x51cd6c0, 1 xref in) references "upscaling_percentage" at 0x51de12e; called by 0x51c90a0 [V xref]; reads settings by NAME-walk (sub_9d6d0 strcmp over [rax+8]/[rax+0x238] list), writes value to [rsi+0xF28] [V]

## Evidence table (offset | size | site | instr | meaning | tag)

| offset | size | site | instr | meaning | tag |
|--------|------|------|-------|---------|-----|
| 0x1F0 | 4 (movss) | 0x67c7917, 0x67c791f, 0x566d04a, 0x566d052, 0x10c1dc3 | `0x67c7917  movss xmm0,[rsi+0x1F0]`<br>`0x67c791f  movss [rdx+0x1F0],xmm0`<br>`0x566d04a  movss xmm0,[rsi+0x1F0]`<br>`0x566d052  movss [rdx+0x1F0],xmm0`<br>`0x10c1dc3  movss [r12+0x1F0],xmm4` | Every +0x1F0 site in the chain: sub_67c7020 loads source-descriptor rsi+0x1F0 (0x67c7917) and writes [rdx+0x1F0]; at endFrame's call `0x66257d7  call 0x67C7020`, rdx=&[rbp+0x11D0] → pass-descriptor slot+0x1F0 = [rbp+0x13C0] (same instruction as oc_U-Eratio's proven "ctx+0x1F0 store 0x67c791f"); sub_566cb20 copies descriptor-slot+0x1F0 → element+0x1F0 at 0x566d04a/0x566d052 (r4 proven link 1; endFrame calls it 7× with src=[rbp+0x11D0]); sub_10c1ad0 writes heap pass-descriptor+0x1F0 at 0x10c1dc3 (r12=[rcx+0x40]; xmm4 computed from settings get-by-index r8d=0xFD/0xFE/0x100/0x101 + params) | [V] |
| 0x13C0 | 4 (movss) | 0x67c791f | `0x67c791f  movss [rdx+0x1F0],xmm0` | Effective address [rbp+0x11D0]+0x1F0 = [rbp+0x13C0] written by sub_67c7020 on endFrame's direct path (rdx=&slot) — this is the descriptor+0x1F0 store that feeds sub_566cb20's src+0x1F0 | [V] instr; [I] effective-address label |
| 0x24 | 4 (dword imm) | 0x5b0c390 | `0x5b0c390  mov dword ptr [rbp+0x24],0x3F666666` | sub_5b0c1b0 default 0x3F666666 = 0.85f materialized in the settings reader that parses "upscaling_percentage" | [V] instr; [I] default semantics |
| 0x28 | 4 (dword imm) | 0x5b0c397 | `0x5b0c397  mov dword ptr [rbp+0x28],0x3F800000` | sub_5b0c1b0 default 0x3F800000 = 1.0f materialized in the same reader that parses "options.targetResolution" | [V] instr; [I] default semantics |
| - | - | 0x5b3e79c, 0x5b3ead3 | `0xf5e13cc "upscaling_percentage" refs=0x51de12e,0x5b3e79c` (ripscan)<br>`0xf5850de "options.targetResolution" refs=0x5b3ead3` (ripscan) | Settings names read inside sub_5b0c1b0: "upscaling_percentage" at xref 0x5b3e79c, "options.targetResolution" at xref 0x5b3ead3 [V string xrefs] | [V] |

## Chain status
Proven [V]: endFrame vtable-slot-18 call site (0x8890de, live ret=0x8890E4) → sub_67c7020 writes descriptor-slot+0x1F0 (0x67c791f from rsi+0x1F0 at 0x67c7917) → sub_566cb20 copies slot+0x1F0 → element+0x1F0 (0x566d052) → element+0x1F0 → ctx+0x1F0 (proven oc_U-Eratio) → TAAU reads ctx+0x1F0 (proven oc_U-Eratio, 0xbc8d34e). Descriptor+0x1F0 writers identified: sub_67c7020@0x67c791f (endFrame slot path) and sub_10c1ad0@0x10c1dc3 (heap-descriptor path, settings-index computed).

## CLOSES?
CLOSES? NO — blocking fact: the link descriptor+0x1F0 = upscaling_percentage/targetResolution is NOT statically provable. sub_10c1ad0 (the only heap +0x1F0 float store) reads settings by FIXED INDEX (r8d=0xFD/0xFE/0x100/0x101 via [rdi+0x28]→[+0xD8] get-by-index); the name-based readers sub_5b0c1b0 ("upscaling_percentage" @0x5b3e79c, "options.targetResolution" @0x5b3ead3) and sub_51cd6c0 ("upscaling_percentage" @0x51de12e) are reached only via sub_5b0aa90@0x5b0b633 from 0x877360/0x8f7f40, and 0x5b0aa90 stores its results at object+0x1BB8, not at descriptor+0x1F0. No index↔name mapping exists in the binary to connect them. Everything else in the item is proven by [V] rows above.

## TOOL REQUESTS
None.

## NEXT
DONE
