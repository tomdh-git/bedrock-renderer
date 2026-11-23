## NEXT
DONE

# U-EL10c — 0x5C render-scale field: writer, sub_88bb50, live decode

## CHAIN (verified)

sub_887860 [0x887860..0x8897f9) per rdis fn is the function containing 0x88895b; its only caller is sub_879480 (rdis callers: 1 call site), which calls it at 0x87BD0F with RCX=rdi=sub_879480's a0; return address 0x87BD14 matches live capture u_el10c_887860.txt (ret=0x87BD14).

Inside sub_887860 a descriptor is built on the stack at [rbp+0x280] and the sub_e7e150 result is stored at descriptor+0x14 ([rbp+0x280]+0x14 == [rbp+0x294]):
  0x888951  mov rcx,[rbp+0x58]          ; object pointer argument
  0x888955  call 0xE7E150               ; sub_e7e150(a0=[rbp+0x58])
  0x88895b  movss [rbp+0x294],xmm0      ; descriptor+0x14 = result

sub_e7e150 [0xE7E150..0xE7E25D]: a0=RCX copied to RSI at 0xE7E169; if [a0+0xCB0] != 1 it returns [a0+0x5C] (0xE7E248); if ==1 it calls sub_88bb50(a0) and returns [rax+0x18] (0xE7E1C4) when non-null.
sub_88bb50 [0x88BB50..0x88BCFD]: returns 0 (0x88BBF2 xor esi,esi / 0x88BC84 xor esi,esi -> 0x88BBF4 mov rax,rsi) or the sub_1219a0() result (0x88BCDD mov rsi,rax -> 0x88BBF4 mov rax,rsi).

## TABLE (one row per distinct offset)

| offset | size | site | instr | meaning |
| 0x58 (stack slot in sub_887860 frame) | 8 | 0x888951 | `0x888951  mov rcx,[rbp+0x58]` | [V] loads the object pointer passed as a0 to sub_e7e150 at the call site 0x888955; the result is stored at descriptor+0x14 ([rbp+0x294] == [rbp+0x280]+0x14). [UNVERIFIED: 0x888951 [rbp+0x58] is loaded but never stored anywhere in sub_887860 (0x887860..0x889697 fully disassembled), so the object type/class is not visible statically.] |
| 0x5C (object field) | 4 | 0xE7E248 | `0xE7E248  movss xmm6,[rsi+0x5C]` | [V] sub_e7e150 normal return source = [a0+0x5C]. |
| 0x14 (descriptor field, [rbp+0x280]+0x14 == [rbp+0x294]) | 4 | 0x88895b | `0x88895b  movss [rbp+0x294],xmm0` | [V] descriptor+0x14 = sub_e7e150 result; per prior r17 this is element+0x14 = scale float; endFrame computes ratio = 1.0f/[elem+0x14]. |
| 0xCB0 (object flag byte) | 1 | 0xE7E16C | `0xE7E16C  cmp byte ptr [rcx+0xCB0],1` | [V] sub_e7e150 dispatch: !=1 -> [a0+0x5C]; ==1 -> sub_88bb50(a0)+0x18 path. |
| 0x18 (sub_88bb50 return-object field) | 4 | 0xE7E1C4 | `0xE7E1C4  movss xmm6,[rax+0x18]` | [V] read of [sub_88bb50(a0)+0x18] when sub_88bb50 returns non-null. |

## LIVE DECODE [V live]

u_el10c_e7e150.txt (sub_e7e150 entry, a0=RCX), decoded with struct '<f':
- line 4 (CALLER ret=0x6608063, first sample, RCX=0x22FC7F44600): +0x50=960.0f, +0x54=509.0f, +0x58=int 1, **+0x5C = 2.0f** (`00000040` = 0x40000000), +0x60=0.5f. [LIVE u_el10c_e7e150.txt:4]
- line 9 (CALLER ret=0xE6FE79): identical bytes, +0x5C = 2.0f. [LIVE u_el10c_e7e150.txt:9]
- line 13 (CALLER ret=0xE6FE95): identical bytes, +0x5C = 2.0f. [LIVE u_el10c_e7e150.txt:13]
- line 17 (CALLER ret=0xE6FEBF): identical bytes, +0x5C = 2.0f. [LIVE u_el10c_e7e150.txt:17]
- Remaining CALLER-only lines (ret=0x6C126A9...) carry no register bytes — no data.
Grouped by ret= caller: 0x6608063 -> 2.0, 0xE6FE79 -> 2.0, 0xE6FE95 -> 2.0, 0xE6FEBF -> 2.0. Same global object (0x22FC7F44600) in all four samples, so +0x5C is a constant 2.0f in this capture.

u_el10c_887860.txt (sub_887860 entry, CALLER ret=0x87BD14, line 4):
- RCX = a0 = 0x22FC62D0000. RCX+0x58 = qword ptr 0x00007FF614C73410, so RCX+0x5C holds pointer bytes `F67F0000` (float decode 4.59e-41, meaningless — it is pointer data, not a float field). sub_887860 itself never reads +0x5C: there is no `+0x5C` instruction anywhere in 0x887860..0x889697; it reaches [obj+0x5C] only indirectly, via sub_e7e150 from [rbp+0x58]. [LIVE u_el10c_887860.txt:4]
- R8+0x5C = 0, R9+0x5C = 0 (zeroed pages). [LIVE u_el10c_887860.txt:4]

## +0x5C WRITER / OPTION-0x243 LINK (blocked, not found)

- fld 0x5C --w over the whole image: no write to [reg+0x5C] inside sub_887860 (0x887860..0x889697). +0x5C float writes exist elsewhere (movss [rcx+0x5C] at 0x512d5e/0x6adaf1/0x798ce3; movss [rdx+0x5C] at 0x69e5a7/0x94446f/0x945543; movss [rbp+0x5C] at 0x2e77a8) but none can be tied to [rbp+0x58]'s object type.
- [rbp+0x58] is never stored anywhere in sub_887860 (verified above: only the load at 0x888951; fld 0x58 --w confirms no rbp+0x58 write), so its class/vtable is not visible statically. The live object at sub_e7e150 entry (0x22FC7F44600) has +0x00 = ptr 0x00007FF6C9B22020, which does not map to an exe RVA at capture time (ASLR/other module), so rdis vt/class cannot be applied.
- Consequently the chain sub_5b72000 (get-option-by-id r8d=0x243 upscaling_percentage / 0x246 targetResolution) -> return value stores -> +0x5C writer's source could not be traced, and the L17h forward-hint (sub_5b0aa90 -> [obj+0x1BB8] vs a [rbp+0x58] field at 0x1BB8) cannot be checked.

## CONCLUSION

Live: [a0+0x5C] decodes to 2.0f in every sub_e7e150 sample (callers 0x6608063, 0xE6FE79, 0xE6FE95, 0xE6FEBF; same global object 0x22FC7F44600); sub_e7e150 returns it and sub_887860 stores it at descriptor+0x14 ([rbp+0x294]); if this is the endFrame path, element+0x14 = 2.0f and endFrame's ratio = 1.0f/2.0f = 0.5. No sample shows any other value; whether +0x5C changes with the in-game upscaling_percentage cannot be determined from this single capture and is not provable statically because the writer of +0x5C on that object's class was not located. sub_887860 itself never reads +0x5C.

## CLOSES?
NO — the writer of [obj+0x5C] on [rbp+0x58]'s object class was not located (no store to [rbp+0x58] in sub_887860; the object's live vtable pointer 0x00007FF6C9B22020 is not mappable to an exe RVA), so the link from [obj+0x5C]=2.0f to upscaling_percentage (option 0x243) is not proven. Observed value IS a constant 2.0 in the capture, independent of any option variation visible here.

## TOOL REQUESTS
None.
