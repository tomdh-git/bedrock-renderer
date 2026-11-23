## NEXT
DONE

UNIT U-EL10c — L10c viewport and render-resolution selection, dynamic resolution.
OUTPUT FILE: docs/progress/oc_U-EL10c.md (no other file).

CONTEXT / HARD RULES: OPENCODE_BRIEF.md hard rules — static analysis only; exe passed only as rdis.exe argument; every claim tagged [V]/[I]/[?]; write results to disk immediately; ## NEXT kept at top; no tools.rtools.*; no builds/commits; no edits to BGFX_MAP.md/RENDER_CHECKLIST.md/src/**/Sigs.json/CLAUDE.md.
EXE: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe, image base 0x7FF605BE0000.

OBJECT a0 = [rbp+0x58] in sub_887860. VERIFIED TYPE: class vtbl_f0bb220, vtable RVA 0xF0BB220 (live vptr 0x7FF614C9B220 - base 0x7FF605BE0000).
- [LIVE u_el10c_e7e150.txt:line4] RCX(=a0)=22FC7F44600, vptr bytes 20B2C914F67F0000 = 0x7FF614C9B220 -> vtable RVA 0xF0BB220; [a0+0x5C] = double 2.0f.
- rdis vt 0xF0BB220 / rdis class 0xF0BB220: name "vtbl_f0bb220" (no RTTI name, vtable identity only); ctor_sites=2: sub_e89e00 lea@0xe89eda/store@0xe89ee1, and sub_ecb4f0 lea@0xecb50e/store@0xecb515 (both store vtbl_f0bb220 at a0+0x0). OWN vtable slots: 0=sub_ecb4f0 (dtor/cleanup), 1=sub_e98900 (stack-cookie guard). slots=2.

-------------------------------------------------------------------------------
TABLE — every row = one distinct offset; all its sites listed; verbatim `0xRVA  instr` proof.
-------------------------------------------------------------------------------

| offset | size | site / address | verbatim `0xRVA  instr` | meaning | tag |
|--------|------|----------------|-------------------------|---------|-----|
| 0x00 | 8 | ctor sub_e89e00 @0xe89ee1 | `0xe89eda  lea rax,[0xF0BB220]` / `0xe89ee1  mov [rbx],rax` | ctor sets a0+0x0 = class vptr vtbl_f0bb220 | [V] |
| 0x5C | 8 | ALL sites (ctor store, exe-wide writers-unrelated, sub_e7e150 read, LIVE) | `0xe89f05  movsd xmm1,[0xF0B86B0]` / `0xe89f0d  movsd [rbx+0x5C],xmm1` (ctor DEFAULT scale 2.0f store) / `0xe7e248  movss xmm6,[rsi+0x5C]` (sub_e7e150 scale-return read) / `0xef3807  mov [rbx+0x5C],eax` (sub_ef2910: eax=bit23 of edi, rbx=bitfield FLAGS struct, NOT a0) / `0xee97a5  mov dword ptr [rax+0x5C],0x7FFFFFFE` (sub_ee86d0 @0xee97a5: rax=[rbp+0x570] hash bucket node, NOT a0) ; [LIVE u_el10c_e7e150.txt:line4] RCX=a0=22FC7F44600, [a0+0x5C]=double 2.0f across callers ; [LIVE w5c_watch.txt:line1] write-watch armed on 0x22FC7F4465C, NO hits | ctor stores DEFAULT scale 2.0f into a0+0x5C (only +0x5C store in ctor); sub_e7e150 returns [a0+0x5C] when flag!=1 (descriptor+0x14=element+0x14=render scale; endFrame ratio=1.0f/[elem+0x14]). Both exe-wide non-ctor writers are unrelated structs (bitfield flags, hash bucket). Live: [a0+0x5C]=2.0f constant, never changes; write-watch never fired. | [V] |
| 0xCB0 | 1 | ctor write + sub_2bab60 write + sub_e7e150 read + who-sets=1 | `0xe8a801  mov byte ptr [r14+0xCB0],0` (ctor, r14=[rbp+0x90]=a0) / `0x2bad7f  mov byte ptr [rsi+0xCB0],0` (sub_2bab60, rsi=a0) / `0x2bad31  mov rcx,[rsi+0xCB0]` (sub_2bab60 read) / `0xe7e16c  cmp byte ptr [rcx+0xCB0],1` (sub_e7e150 flag read) | slow-path FLAG a0+0xCB0: ctor sets 0, sub_2bab60 sets 0, sub_e7e150 reads it (if !=1 -> return [a0+0x5C] at 0xe7e248; if ==1 -> slow path via sub_88bb50 -> [result+0x18] at 0xe7e1c4). rdis rw 0xcb0 global scan: NO [a0+0xCB0]=1 write with base a0 exists -> setter of flag=1 UNKNOWN. | [V] / [?] |
| 0x30 | 8 | ctor sub_e89e00 @0xe89e8f-0xe89ed2 | `0xe89e8f  mov edx,0x18` / `0xe89e94  call qword ptr [0xF99FFA0]` / `0xe89ed2  mov [rbx+0x30],rax` / `0xe89ed6  mov [rbx+0x38],rdi` | get-option [0xF99FFA0]=sub_eea6040 with option id 0x18 (edx); result rdi -> stored a0+0x30 (rax) and a0+0x38 (rdi ptr). NOT option 0x243/0x246; NOT to +0x5C. | [V] |
| 0x68 | 8 | ctor sub_e89e00 @0xe89f2a-0xe89f5b | `0xe89f2a  mov edx,0x20` / `0xe89f2f  call qword ptr [0xF99FFA0]` / `0xe89f5b  mov [rbx+0x68],rdi` | get-option option id 0x20; result -> stored a0+0x68. NOT option 0x243/0x246; NOT to +0x5C. | [V] |
| 0xC38 | 8 | ctor sub_e89e00 @0xe8a77e-0xe8a7ae | `0xe8a77e  mov edx,0x58` / `0xe8a783  call qword ptr [0xF99FFA0]` / `0xe8a7ae  mov [r14+0xC38],rsi` | get-option option id 0x58; result rsi -> stored a0+0xC38 (r14=a0). NOT option 0x243/0x246; NOT to +0x5C. | [V] |
| 0x18 | 4 | sub_e7e150 slow path @0xe7e1c4 / sub_88bb50 | `0xe7e1c4  movss xmm6,[rax+0x18]` (rax = sub_88bb50 return = its arg object rsi) | slow path (flag==1) returns [sub_88bb50(a0)+0x18] alternate scale. sub_88bb50 does a table/lookup (945f90, 1210f0, +0x19/+0x20 scan, hash 0xDA6A3486); what sets [sub_88bb50_result+0x18] is not traced to an option. | [V] |
| rbp+0x58 | 8 | sub_887860 @0x888951 | `0x888951  mov rcx,[rbp+0x58]` | sub_887860 loads a0 from stack local [rbp+0x58]; [rbp+0x58] is NEVER stored inside sub_887860 (only read). | [V] |
| rbp+0x294 | 4 | sub_887860 @0x88895b | `0x88895b  movss [rbp+0x294],xmm0` | sub_887860 calls sub_e7e150(a0) at 0x888955 and stores scale result to [rbp+0x294] (descriptor+0x14 -> endFrame). Caller of sub_887860 = sub_879480 (1 call site; live caller ret=0x87BD14, [LIVE el17h_endframe_caller.txt]). | [V] |

-------------------------------------------------------------------------------
CLASS OWN vTABLE METHODS — no +0x5C writer
-------------------------------------------------------------------------------
slot 0 = sub_ecb4f0 (dtor/cleanup: linked-list unlink at +0xD50/+0xCD0/+0xCC8, refcount releases at +0xC20/+0xC10/+0xC00); slot 1 = sub_e98900 (stack-cookie guard). Confirmed via rdis class (slots=2) and disassembly of sub_ecb4f0/sub_e98900: NEITHER writes +0x5C. [V]

-------------------------------------------------------------------------------
CTOR OPTION READS (get-option [0xF99FFA0] = sub_eea6040) — complete list
-------------------------------------------------------------------------------
- 0xe89e8f mov edx,0x18 ; 0xe89e94 call qword ptr [0xF99FFA0] -> option id 0x18 -> stored a0+0x30/+0x38
- 0xe89f2a mov edx,0x20 ; 0xe89f2f call qword ptr [0xF99FFA0] -> option id 0x20 -> stored a0+0x68
- 0xe8a77e mov edx,0x58 ; 0xe8a783 call qword ptr [0xF99FFA0] -> option id 0x58 -> stored a0+0xC38
- 0xe8a67a call qword ptr [0xF99FFA0] with rdx = pointer (not an imm option id) -> not an option read into +0x5C
NONE is option id 0x243 (upscaling_percentage) or 0x246 (targetResolution), and NONE stores to a0+0x5C.

-------------------------------------------------------------------------------
VERDICT
-------------------------------------------------------------------------------
CLOSES? NO — the upscaling_percentage (option 0x243) -> render-scale link via a0+0x5C is NOT established and is negatively supported: [a0+0x5C] is written ONLY once, in the ctor, as constant 2.0f (`0xe89f0d movsd [rbx+0x5C],xmm1` from data_f0b86b0=0x4000000000000000); the class's own vtable methods (slot 0 sub_ecb4f0 dtor, slot 1 sub_e98900 guard) do not write +0x5C; both exe-wide non-ctor +0x5C writers (sub_ef2910 bitfield flags, sub_ee86d0 hash bucket) are unrelated structs; live data shows [a0+0x5C]=2.0f constant across all callers; ctor reads options 0x18/0x20/0x58 only (not 0x243/0x246) and never into +0x5C. Separately, who sets slow-path flag [a0+0xCB0] to 1 (read at `0xe7e16c cmp byte ptr [rcx+0xCB0],1`) is UNKNOWN (ctor and sub_2bab60 both write it to 0). Single blocking fact: no store from an option-0x243 read into a0+0x5C exists (+0x5C is ctor-constant 2.0f), and the [a0+0xCB0]=1 setter is not found.

TOOL REQUESTS: none.
