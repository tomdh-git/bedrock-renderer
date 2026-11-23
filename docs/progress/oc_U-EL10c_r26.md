## NEXT
DONE

UNIT U-EL10c — L10c viewport and render-resolution selection (a0+0x5C render-scale link). Output file: docs/progress/oc_U-EL10c.md (only file for this unit).
Minecraft.Windows.exe 1.26.62.01, image base 0x7FF605BE0000; all RVAs image-relative. Tools used: rdis.exe vt/xr/dis/fld/callers only (no exe-wide [reg+0x5C] rescan per orchestrator rule; no tools.rtools.*).
Live data cited as [V live] from docs/data/live/*.txt (w5c_watch.txt, u_el10c_e7e150.txt, u_el10c_887860.txt).
Tags: [V] = seen in rdis disassembly (verbatim instruction line quoted), [V live] = seen in live capture bytes, [I] = inferred, [?] = unknown.

GOAL (orchestrator 2026-11-22, class-found block): close the a0+0x5C link.
- a0 live vptr = 0x7FF614C9B220 -> vtable RVA 0xF0BB220 (base 0x7FF605BE0000).
- Ctor sub_e89e00 sets vtable at 0xe89eda and default scale `0xe89f05 movsd xmm1,[0xF0B86B0]` / `0xe89f0d movsd [rbx+0x5C],xmm1` (+0x5C = 2.0f).
- vt slots: sub_ecb4f0 (0), sub_e98900 (1), sub_eb76b0 (2, thunk), sub_eb76c0 (0xb8, thunk).
- exe-wide non-ctor writers of +0x5C: 0xee97a5 (sub_ee86d0) and 0xef3807 (sub_ef2910).
Pending this run: (1) is sub_ef2910+0xef7's object (rbx) this class, where does eax come from; (2) is sub_ee86d0+0x10d5's object this class; (3) ctor get-option calls 0xe89e94/0xe89f2f/...: option ids passed and fields results stored to (any store into a0+0x5C closes the link); (4) a0+0xCB0 flag byte — who sets it to 1.

## EVIDENCE TABLE (offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag)

| offset | size | site | instr | meaning | tag |
|--------|------|------|-------|---------|-----|
| vt+0x0 | - | `  0 +0x000  sub_ecb4f0           size 0x6c8  push rbp` | vtable[0] = sub_ecb4f0 (0xF0BB220 slot 0) | [V] |
| vt+0x8 | - | `  1 +0x008  sub_e98900           size 0x4b  sub rsp,0x38` | vtable[1] = sub_e98900 | [V] |
| vt+0x10 | - | `  2 +0x010  sub_eb76b0           size 0x4000  add rcx,0xFFFFFFFFFFFFFFF8` / `0xeb76b4  jmp 0xECB4F0` | slot 2 adjustor thunk: this-8, tail-jump to sub_ecb4f0 | [V] |
| vt+0xb8 | - | ` 23 +0x0b8  sub_eb76c0           size 0x4000  add rcx,0xFFFFFFFFFFFFFFD8` / `0xeb76c4  jmp 0xECB4F0` | slot 0xb8 adjustor thunk: this-0x28, tail-jump to sub_ecb4f0 | [V] |
| vt+0x18-0xb0 | - | `  3 +0x018  sub_768f0            size 0x1  ret` (slots 3-0xb0, repeated) | unused slots = ret | [V] |
| vt+0xc0+ | - | ` 24 +0x0c0  non-code 0x14f5ec99c` / ` 26 +0x0d0  non-code 0x0` | RTTI / non-code slots | [V] |
| - | 8 | `0xe89eda  lea rax,[0xF0BB220]` / `0xe89ee1  mov [rbx],rax` / `0xe89e32  mov rbx,rcx` / `0xe8a52f  mov [rbp+0x90],rbx` / `0xe8a7a7  mov r14,[rbp+0x90]` / `0xe8a52a  mov edx,0x11` / `0xe8a523  lea r9,[0xF51E3A4]` / `0xe8a536  call 0x9D6D0` | ctor: vptr = vtable 0xF0BB220 (W a0+0x0); rbx = a0 = this; r14 = a0 (chain e89e32 -> e8a52f -> e8a7a7); option NAME read "ui_invert_overlay" (`0xe8a523  lea r9,[0xF51E3A4]            ; [data_f51e3a4] "ui_invert_overlay"`), no field store seen for it | [V] |
| 0x5c | 8 | `0xe89f05  movsd xmm1,[0xF0B86B0]` / `0xe89f0d  movsd [rbx+0x5C],xmm1` / `0xef3807  mov [rbx+0x5C],eax` / `0xee97a5  mov dword ptr [rax+0x5C],0x7FFFFFFE` / `0xeb76b4  jmp 0xECB4F0` / `0xeb76c4  jmp 0xECB4F0` | a0+0x5C: ctor DEFAULT = 2.0f from data 0xF0B86B0, the ONLY [reg+0x5C] store in sub_e89e00 (full listing read); sub_ef2910+0xef7 stores bit 23 of edi ((edi>>0x17)&1) as DWORD 0/1 into a bitfield buffer (heap via call [0xF99FFA0] at 0xef29a3/0xef29e0, or stack at 0xef29d0) — NOT this class, NOT a scale; sub_ee86d0+0x10d5 stores 0x7FFFFFFE into an std::unordered_map bucket-count field (`0xee97b7 ... "unordered_map/set too long"`, `0xee97d8 ... "invalid hash bucket count"`) — NOT this class; vt slots 2/0xb8 are adjustor thunks to sub_ecb4f0 (dtor), no +0x5C store there | [V] |
| 0xcb0 | 1 | `0xe8a801  mov byte ptr [r14+0xCB0],0` / `0x53fbe34  mov byte ptr [rax+0xCB0],1` | flag [a0+0xCB0]: ctor initializes it to 0 [V]; the ONLY object-base byte-store of literal 1 to +0xCB0 image-wide (`fld --w 0xcb0`, 727 accesses) is `0x53fbe34` in sub_53fbc80 (render-stage loop, "RenderStage::render" at 0x53fbf67) with rax = [rdi+0xA0]; `rdis callers 0x53fbc80` -> 0 direct callers; object class of rax UNVERIFIED, so the flag=1 setter for a0's class is NOT proven [I] | [V]/[I] |
| 0x30 | 8 | `0xe89e8f  mov edx,0x18` / `0xe89e94  call qword ptr [0xF99FFA0]` / `0xe89ed2  mov [rbx+0x30],rax` | ctor reads option/slot 0x18 (same indirect-call slot [0xF99FFA0] sub_5b72000 uses for id-0x243 reads); result object stored at [a0+0x30]; failure path `0xe8a985  mov ecx,0x18` / `call 0x9BC830` | [V] |
| 0x38 | 8 | `0xe89ed6  mov [rbx+0x38],rdi` | same option/slot-0x18 result object -> stored at [a0+0x38] (node self-init `0xe89f4a  mov [rdi],rdi` / `0xe89f55  mov word ptr [rdi+0x18],0x101`) | [V] |
| 0x68 | 8 | `0xe89f2a  mov edx,0x20` / `0xe89f2f  call qword ptr [0xF99FFA0]` / `0xe89f5b  mov [rbx+0x68],rdi` | ctor reads option/slot 0x20; self-linked node stored at [a0+0x68]; failure path `0xe8a995  mov ecx,0x20` / `call 0x9BC830` | [V] |
| 0xc38 | 8 | `0xe8a77e  mov edx,0x58` / `0xe8a783  call qword ptr [0xF99FFA0]` / `0xe8a7ae  mov [r14+0xC38],rsi` | ctor reads option/slot 0x58; result stored at [a0+0xC38] (r14 = a0); failure path `0xe8a9a5  mov ecx,0x58` / `call 0x9BC830` | [V] |

## FINDINGS PER PENDING ITEM

(1) sub_ef2910+0xef7 = `0xef3807  mov [rbx+0x5C],eax`: eax = bit 23 of edi (`0xef37ff  mov eax,edi` / `0xef3801  shr eax,0x17` / `0xef3804  and eax,1`) = DWORD 0 or 1; rbx is a bitfield destination buffer. NOT an instance of the vtable-0xF0BB220 class and NOT a scale float. [V]
(2) sub_ee86d0+0x10d5 = `0xee97a5  mov dword ptr [rax+0x5C],0x7FFFFFFE`: rax = [rbp+0x570] inside std::unordered_map bucket code ("invalid hash bucket count" neighbor). NOT the vtable-0xF0BB220 class. [V]
(3) Ctor option/slot reads via call qword ptr [0xF99FFA0]: edx=0x18 -> result object at +0x30/+0x38; edx=0x20 -> node at +0x68; edx=0x58 -> result at +0xC38; plus name-read "ui_invert_overlay" (edx=0x11). NONE stores into a0+0x5C; a0+0x5C is written once in the ctor, the default 2.0f from data 0xF0B86B0 (`0xe89f0d  movsd [rbx+0x5C],xmm1`). Option-read -> a0+0x5C link does NOT exist in this class. [V]
Slot-1 method sub_e98900 (vt+0x8) also reads options: `0xe989c1  mov edx,0x20` / `e989c6  call r8` with strings "accessibility.enableTTS"/"accessibility.disableTTS" — unrelated to +0x5C. [V]
(4) Flag [a0+0xCB0]: ctor initializes it to 0 (`0xe8a801  mov byte ptr [r14+0xCB0],0`, r14=a0). Image-wide `fld --w 0xcb0` (727 accesses) yields exactly one object-base byte-store of literal 1: `0x53fbe34  mov byte ptr [rax+0xCB0],1` (sub_53fbc80+0x1b4; rax=[rdi+0xA0] in render-stage code; 0 direct callers) — object class of rax unverified, so the flag=1 setter for a0's class is NOT proven. [I]

## CLASS-METHODS SCOPED CHECK (+0x5C)
vt slots resolve to: slot 0 sub_ecb4f0 = destructor (list unlink/refcount at +0xD48/+0xD50/+0xCC8/+0xCD0/+0xC38/+0xC20/+0xC18/+0xC10 — no +0x5C); slots 2/0xb8 = adjustor thunks jmp-ing to sub_ecb4f0; slot 1 sub_e98900 head reads options (no +0x5C in head; full 0x2000-byte listing not read). No +0x5C store found in inspected class code. [I] scoped — combined with the two exe-wide writers above being provably other classes, the ctor default is the only +0x5C writer tied to this class.

## HOP CHAIN (endFrame element+0x14 = descriptor+0x14 = sub_e7e150([rbp+0x58]))
Hop 1 [V]: `0x888951  mov rcx,[rbp+0x58]` / `0x888955  call 0xE7E150` / `0x88895b  movss [rbp+0x294],xmm0` (sub_887860; called by sub_879480 `0x87bd0f  call 0x887860`, ret 0x87bd14 = live capture caller ret).
Hop 2 [V]: sub_e7e150: `0xe7e16c  cmp byte ptr [rcx+0xCB0],1` -> ==1 path: `0xe7e179  mov rcx,[rsi+0x98]` / `0xe7e183  mov rax,[rax+0x108]` (vtable slot 0x108 of *(a0+0x98)) / `0xe7e1b9  call 0x88BB50` / `0xe7e1c4  movss xmm6,[rax+0x18]` = [sub_88bb50(settings)+0x18]; !=1 path: `0xe7e173  jne 0xE7E248` / `0xe7e248  movss xmm6,[rsi+0x5C]` = [a0+0x5C] (`0xe7e24d  movaps xmm0,xmm6` return).
Hop 3 [V]: [a0+0x5C] = ctor default 2.0f (`0xe89f0d  movsd [rbx+0x5C],xmm1`, xmm1 = data 0xF0B86B0); live constant 2.0f across all captured caller groups (u_el10c_e7e150.txt RCX=0x22FC7F44600, [+0x5C] bytes `40 00 00 00`, ret= 0x6608063/0xE6FE79/0xE6FE95/0xE6FEBF); flag = 0 in ctor -> fallback path taken live.
Hop 4 [V]: no option-id-0x243 (upscaling_percentage) read is stored into a0+0x5C anywhere in the class (ctor reads target +0x30/+0x38/+0x68/+0xC38 only; ids 0x18/0x20/0x58, name "ui_invert_overlay").
Hop 5 [I]: flag=1 setter candidate `0x53fbe34  mov byte ptr [rax+0xCB0],1` (rax=[rdi+0xA0], class unverified); sub_88bb50 path keyed by settings-tree HASH 0xDA6A3486 (`0x88bccf  mov r8d,0xDA6A3486` / `0x88bcd8  call 0x1219a0`) -> [result+0x18]; hash unnamed (`imm 0xDA6A3486` hits only tree/lookup code, not sub_5b72000) -> NOT option id 0x243.

## SETTINGS-OBJECT LINK (L17h hint condition)
`0xe89f8a  mov [rbx+0x98],rsi` stores the ctor's 2nd argument (settings object) at a0+0x98 [V]; sub_e7e150 flag==1 path derefs *(a0+0x98) (`0xe7e179  mov rcx,[rsi+0x98]`) -> so the object IS built from the settings object, but via hash 0xDA6A3486, not option id 0x243 -> no upscaling link on this path.

## LIVE
- docs/data/live/w5c_watch.txt: `armed on 0x22FC7F4465C` (= 0x22FC7F44600+0x5C) — write-watch armed on live a0+0x5C [V live]
- docs/data/live/u_el10c_887860.txt L4: RCX=0x22FC62D0000 (sub_887860's own a0, DIFFERENT class), [RCX+0x5C] = qword ptr `50 2B C7 14 F6 7F 00 00` — [rbp+0x58]'s object (0x22FC7F44600 per e7e150 capture) NOT observable at sub_887860 entry [V live]

## CLOSES?
NO
Single blocking fact: a0+0x5C has exactly ONE writer in this class, the ctor default `0xe89f0d  movsd [rbx+0x5C],xmm1` = 2.0f from read-only data 0xF0B86B0; no option-id-0x243 (upscaling_percentage) read is ever stored into a0+0x5C (ctor reads target +0x30/+0x38/+0x68/+0xC38 only), and the flag [a0+0xCB0]=1 slow-path selector (sub_88bb50+0x18, settings-tree hash 0xDA6A3486 != id 0x243) is not shown to be option-driven and its setter's object class is unverified (single candidate `0x53fbe34  mov byte ptr [rax+0xCB0],1`, rax=[rdi+0xA0]). So element+0x14 = descriptor+0x14 = [a0+0x5C] stays constant 2.0f (ratio 1/2); the upscaling link via this path is NOT closed.

## TOOL REQUESTS
None — all evidence from rdis.exe (vt/xr/dis/fld/callers) and reads of docs/data/live/*.txt; no helper scripts written.
