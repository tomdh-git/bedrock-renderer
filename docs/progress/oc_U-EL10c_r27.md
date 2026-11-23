## NEXT
DONE pending delegate check — open items listed below; CLOSES? NO (blocking fact named)

UNIT U-EL10c (docs/progress/oc_U-EL10c.md only). Checklist item L10c "viewport and render-resolution selection, dynamic resolution pending".
RE-SCOPED by ORCHESTRATOR 2026-11-22 (after r22): class of a0 is NOT unknown. Live a0 vptr = 0x7FF614C9B220; game base 0x7FF605BE0000; vtable RVA = 0xF0BB220 (VERIFIED [V]).
Chain: sub_e7e150(a0=[rbp+0x58]) returns [a0+0x5C] (fast path 0xe7e248) or sub_88bb50(a0)+0x18 (slow path 0xe7e1c4); feeds descriptor/element +0x14 -> +0x1F0 -> ctx+0x1F0 (0x67c791f) -> TAAU 0xbc8d34e render/display ratio. Option id 0x243 = upscaling_percentage, 0x246 = targetResolution.

TOOLS: rdis.exe "exe" <cmd> <rva>; exe = C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe. STATIC ONLY; never launch the exe. Live captures read-only under docs/data/live/.

------------------------------------------------------------
EVIDENCE TABLE (name | offset/RVA | size | verbatim `0xRVA  instr` proof | tag)
------------------------------------------------------------
| vtbl_f0bb220 class identity (vtable 0xF0BB220, no RTTI name) | 0xf0bb220 | - | - | [I] rdis class identity-only |
| vtable slot 0 | sub_ecb4f0 0xecb4f0 | size 0x6c8 | - | [V] rdis vt slot 0 |
| vtable slot 1 | sub_e98900 0xe98900 | size 0x4b | - | [V] rdis vt slot 1 |
| vtable slot 2 | sub_eb76b0 0xeb76b0 | size 0x4000 | - | [V] rdis vt slot 2 |
| vtable slot 0xb8 | sub_eb76c0 0xeb76c0 | size 0x4000 | - | [V] rdis vt slot 0xb8 |
| ctor vptr store site #1 (lea + mov [rcx],reg) | 0xe89eda | 7 (lea) | `0xe89eda  lea rax,[0xF0BB220]` | [V] |
| ctor vptr store #1 (mov [rbx],rax) | 0xe89ee1 | 8 (mov) | `0xe89ee1  mov [rbx],rax` ; W a0+0x0 = vtable 0xF0BB220 | [V] |
| ctor vptr store site #2 (lea + mov [rcx],reg) | 0xecb50e | 7 (lea) | `0xecb50e  lea rax,[0xF0BB220]` | [V] |
| default scale load (qword 0x400000 = 2.0f) | 0xe89f05 | 8 (movsd) | `0xe89f05  movsd xmm1,[0xF0B86B0]` ; [data_f0b86b0] | [V] |
| default scale store to a0+0x5C | 0xe89f0d | 8 (movsd) | `0xe89f0d  movsd [rbx+0x5C],xmm1` ; W a0+0x5C = 2.0f DEFAULT | [V] |
| ctor option read #1 id | 0xe89e8f | 4 (mov) | `0xe89e8f  mov edx,0x18` ; option id=0x18 (NOT 0x243) | [V] |
| ctor option read #1 get-option call | 0xe89e94 | 6 (call) | `0xe89e94  call qword ptr [0xF99FFA0]` ; sub_eea6040, rcx=[0x1233E1A8] options obj | [V] |
| ctor option read #1 result store | 0xe89ed2 | 8 (mov) | `0xe89ed2  mov [rbx+0x30],rax` ; W a0+0x30 (NOT +0x5C) | [V] |
| ctor option read #2 id | 0xe89f2a | 4 (mov) | `0xe89f2a  mov edx,0x20` ; option id=0x20 (NOT 0x243) | [V] |
| ctor option read #2 get-option call | 0xe89f2f | 6 (call) | `0xe89f2f  call qword ptr [0xF99FFA0]` ; sub_eea6040 | [V] |
| ctor option read #2 result store | 0xe89f5b | 8 (mov) | `0xe89f5b  mov [rbx+0x68],rdi` ; W a0+0x68 (NOT +0x5C) | [V] |
| ctor zeroes +0x1B0..+0x1BF (covers field +0x1BB8) | 0xe8a0ed | 16 (movups) | `0xe8a0ed  movups [rbx+0x1B0],xmm6` ; W a0+0x1B0..0x1BF = 0 | [V] |
| exe-wide +0x5C writer sub_ef3700+0xef7 (NOT our class) | 0xef3807 | 4 (mov) | `0xef3807  mov [rbx+0x5C],eax` ; eax=bit(edi>>0x17)&1=0/1; [rbx+0x0] overwritten=bitfield struct, NOT vtbl_f0bb220 | [V] |
| exe-wide +0x5C writer sub_ee86d0+0x10d5 (NOT our class) | 0xee97a5 | 4 (mov) | `0xee97a5  mov dword ptr [rax+0x5C],0x7FFFFFFE` ; rax=[rbp+0x570], unordered_map bucket internals, map sentinel | [I] |
| load a0=[rbp+0x58] in sub_887860 | 0x888951 | 8 (mov) | `0x888951  mov rcx,[rbp+0x58]` ; R a0 (vtbl_f0bb220 object) | [V] |
| call sub_e7e150(a0) | 0x888955 | 5 (call) | `0x888955  call 0xE7E150` | [V] |
| store descriptor+0x14 = sub_e7e150 result | 0x88895b | 4 (movss) | `0x88895b  movss [rbp+0x294],xmm0` ; W descriptor+0x14 | [V] |
| slow-path flag test [a0+0xCB0]==1 | 0xe7e16c | 1 (cmp byte) | `0xe7e16c  cmp byte ptr [rcx+0xCB0],1` ; R a0+0xCB0 ; jne->fast path | [V] |
| fast path return [a0+0x5C] | 0xe7e248 | 4 (movss) | `0xe7e248  movss xmm6,[rsi+0x5C]` ; R a0+0x5C, returned in xmm0 | [V] |
| slow path read [sub_88bb50_ret+0x18] | 0xe7e1c4 | 4 (movss) | `0xe7e1c4  movss xmm6,[rax+0x18]` ; R ret@88bb50+0x18 | [V] |

------------------------------------------------------------
LIVE EVIDENCE [V live]
------------------------------------------------------------
| a0+0x5C float across sub_e7e150 callers | +0x5C | 4 (float) | docs/data/live/u_el10c_e7e150.txt: RCX(=a0, vptr=0x7FF614C9B220=vtbl_f0bb220) +0x5C float=2.0 for callers ret=0x6608063 (line 4), 0xE6FE79 (line 9), 0xE6FE95 (line 13), 0xE6FEBF (line 17) | [V live] |
| w5c_watch.txt armed on [a0+0x5C]=0x22FC7F4465C | 0x22FC7F4465C | - | docs/data/live/w5c_watch.txt line 1: "armed on 0x22FC7F4465C"; NO write hits logged | [V live] |
| u_el10c_887860 caller ret=0x87BD14 | - | - | docs/data/live/u_el10c_887860.txt line 3-4: RCX=22FC62D0000 vptr=0x7FF614C7B250 (DIFFERENT class); [rbp+0x58] object is a sub-object/field, not the rcx arg | [V live] |

------------------------------------------------------------
CONFIRMED [V] — no +0x5C writer in class methods or exe-wide for this class
------------------------------------------------------------
- class vtable methods (slots sub_ecb4f0/sub_e98900/sub_eb76b0/sub_eb76c0): no store to [reg+0x5C] (per orchestrator [V] by rdis).
- exe-wide +0x5C writers: sub_ef3700+0xef7 (0xef3807 `mov [rbx+0x5C],eax` writes a FLAG BIT to a bitfield struct; [rbx+0x0] overwritten so rbx is not vtbl_f0bb220) and sub_ee86d0+0x10d5 (0xee97a5 `mov dword [rax+0x5C],0x7FFFFFFE` map sentinel in unordered_map internals). NEITHER writes the vtbl_f0bb220 class's +0x5C scale.

------------------------------------------------------------
KEY CONCLUSION [V]
------------------------------------------------------------
The +0x5C render scale of class vtbl_f0bb220 is written ONLY by the ctor default (`0xe89f0d  movsd [rbx+0x5C],xmm1` = 2.0f from `0xe89f05  movsd xmm1,[0xF0B86B0]` = qword 0x400000). No class method and no exe-wide writer writes this class's +0x5C. Live data confirms +0x5C = constant 2.0f across all sub_e7e150 callers; w5c_watch logged no [a0+0x5C] writes. Ctor option reads pass id 0x18 (`0xe89e8f mov edx,0x18`) and id 0x20 (`0xe89f2a mov edx,0x20`), NEITHER is upscaling id 0x243, NEITHER writes +0x5C. Therefore the upscaling_percentage (0x243) link to the render ratio is NOT via an override of +0x5C. It can only enter via the SLOW path of sub_e7e150 (flag [a0+0xCB0]==1 at `0xe7e16c cmp byte ptr [rcx+0xCB0],1` -> sub_88bb50(a0) -> `0xe7e1c4 movss xmm6,[rax+0x18]`, which reads an option via get-option [0xF99FFA0] on [a0+0x98]).

------------------------------------------------------------
OPEN ITEMS (not yet [V])
------------------------------------------------------------
| static store location of [rbp+0x58] in sub_887860 | [rbp+0x58] | - | Only READ at `0x888951 mov rcx,[rbp+0x58]`; NO direct `mov [rbp+0x58],...` store found in full listing 0x887860..0x889860; no `lea ...[rbp+0x58]` out-param. Type proven [V live] via sub_e7e150's RCX (vptr 0x7FF614C9B220, +0x5C=2.0). | [?] |
| who sets slow-path flag a0+0xCB0 = 1 | +0xCB0 | 1 (byte) | tested at `0xe7e16c`; setter not located | [?] |
| sub_88bb50 return +0x18 source | ret+0x18 | 4 | sub_88bb50 [0x88bb50..0x88db50) returns rax=rsi (epilogue `0x88bbf4 mov rax,rsi`, often 0); slow path reads [rax+0x18] only when non-null; source not traced | [?] |
| L17h +0x1BB8 link (sub_5b0aa90 -> [obj+0x1BB8]) | +0x1BB8 | - | ctor zeroes [rbx+0x1B0..0x1BF] (`0xe8a0ed`) covering +0x1BB8; whether [rbp+0x58] object IS/contains the settings object sub_5b0aa90 writes at +0x1BB8 not established | [?] |

------------------------------------------------------------
CLOSES?
------------------------------------------------------------
NO

Single blocking fact: the upscaling_percentage (0x243) -> render-ratio link is not closed. Proven [V]: +0x5C scale = ctor-default constant 2.0f (never overridden; exe-wide +0x5C writers are not this class; live +0x5C=2.0, no w5c_watch hits), fed via sub_e7e150 fast path to descriptor+0x14 -> +0x1F0 -> ctx+0x1F0 -> TAAU. The ONLY possible upscaling entry is the slow path ([a0+0xCB0]==1 -> sub_88bb50(a0)+0x18 via get-option on [a0+0x98]), but (a) who sets [a0+0xCB0]=1 is unknown, (b) sub_88bb50's +0x18 source is unknown, (c) the static store location of [rbp+0x58] in sub_887860 is not found (type only [V live]). Until the slow-path chain to option id 0x243 is proven by [V] rows, L10c dynamic-resolution selection cannot close.

------------------------------------------------------------
TOOL REQUESTS
------------------------------------------------------------
name | input -> output | why
None yet (all evidence from rdis.exe vt/class/xr/fn/callers/dis and live capture files already on disk; no new scripts written).
