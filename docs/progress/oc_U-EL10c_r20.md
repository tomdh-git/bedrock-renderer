## NEXT
DONE

# U-EL10c: endFrame element +0x14 scale float source chain — COMPLETE

## Goal
Trace endFrame element +0x14 scale float source chain back to settings option id 0x243 (upscaling_percentage). RESOLVED.

## Chain (fully traced)

endFrame element+0x14 = descriptor+0x14 = return of sub_e7e150([rbp+0x58])

sub_e7e150(a0=[rbp+0x58]) [0xE7E150..0xE7E25D]:
- Reads flag byte at [a0+0xCB0]
- If flag==1: loads [a0+0x98], vcall [rax+0x108], calls sub_88bb50(vcall_result), returns [sub_88bb50_result+0x18]
- If flag!=1: returns [a0+0x5C] directly
- Return stored at [rbp+0x294] = descriptor+0x14 [V dis 0x888955-0x88895b]

sub_88bb50 [0x88BB50..0x88BBCD]:
- Looks up settings tree by hash key 0xDA6A3486 via sub_1219a0
- Returns settings value object pointer (or 0)
- [sub_88bb50_result+0x18] = float value read as descriptor+0x14

sub_5b72000 (get-option-by-id) [0x5B72000..0x5B72177]:
- Uses option id 0x243 (upscaling_percentage) directly via r8d=0x243
- ALSO uses hash key 0xDA6A3486 (same as sub_88bb50!) at 0x5B720C7
- Reads option 0x243 value at [option_obj+0x18] (0x5B72053)
- Reads option 0x244 value at [option_obj+0x18] (0x5B72093)
- Calls sub_eea6040 with [a0+0x1A40]+0xC0 and [a0+0x1A40]+0xC8 as likely setters

## Critical connection: 0xDA6A3486 = hash key for option id 0x243

Both sub_88bb50 (via sub_1219a0) AND sub_5b72000 use hash key 0xDA6A3486.
sub_5b72000 also uses option id 0x243 (upscaling_percentage) directly.
This confirms: 0xDA6A3486 is the hash key for upscaling_percentage.

Both [sub_88bb50_result+0x18] and [option_obj+0x18] store float setting values at +0x18 offset.

## Final chain

endFrame element+0x14 (scale float)
  = descriptor+0x14
  = sub_e7e150([rbp+0x58]) return value
  = [sub_88bb50(a0)+0x18] (when flag at [a0+0xCB0]==1)
  = settings value object for hash key 0xDA6A3486
  = upscaling_percentage option (id 0x243) float value
  = [option_obj+0x18]

Alternative path (flag!=1): [a0+0x5C] = cached/direct float on descriptor object

## Remaining minor items (not blocking)

1. Who writes [obj+0x5C] on [rbp+0x58]'s class: [rbp+0x58] is NEVER written in sub_887860 (only read at 0x888951). Must be set before sub_887860 is called. Potential writers via fld 0x5C --w: movss at 0x512d5e, 0x599938, 0x69e5a7, 0x798ce3, 0x94446f. sub_943fe0 writes [rdx+0x5C] alongside other float fields (+0x60,+0x64,+0x68,+0x6C) — likely settings struct initializer.

2. Who writes [sub_88bb50_result+0x18]: settings value object's +0x18 written during settings initialization/config load. Not traced to specific writer but follows same pattern as sub_5b72000's [option_obj+0x18].

3. Follow sub_5b72000 to its stores: sub_5b72000 returns void; calls sub_eea6040 with option values (possible setters). The actual store to [option_obj+0x18] happens during settings initialization, not in sub_5b72000 itself.

## Live capture confirmation

RDX=0x14EC10 array1 pointers at 0x38/0x40 confirmed. Element stride 0x18 confirmed by sub_6A03D0 loop at 0x8891A9.
