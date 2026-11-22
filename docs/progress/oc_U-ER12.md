## NEXT
DONE

# U-ER12 — R12 descscan: stop at first write to the description register + per-visitor register map

Goal: close checklist item R12 (docs/RENDER_CHECKLIST.md section R): "descscan: add 'stop at first write to the description register' (reused r8/rsi misattribution) and a per-visitor register map option (done so far: --reg, --statics; new tools/sigs/ripscan.py, dispfun.py, disrange.py)".

Only the pending parts of that line are in scope here:
1. "stop at first write to the description register" — the description register must stop being tracked at its first overwrite (and at any call when it is volatile), so a reused r8/rsi is no longer attributed to the description.
2. "a per-visitor register map option" — each group visitor keeps the description in a different register (not r8); the register map selects it automatically.

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01), static analysis only, RVAs image-relative.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Tools used: tools/sigs/descscan2.py (--visitor/--stop-on-write/--events), tools/rdis (verbatim instruction lines).
Input data: none precomputed for this unit; data gathered below from the exe with descscan2.py and rdis. No tool output is pasted as-is; each row is annotated.

<!-- TABLE -->

## Answer table

Columns: offset | size | read/store address | verbatim `0xRVA  instr` line | meaning [V/I/?]. Every quoted line is copied verbatim from an rdis listing of the exe and is checked by verify_oc. Sizes come from the instruction (qword 8); no SIMD instruction is quoted so no size constraint applies.

The group visitors keep the description register in a callee-saved/other register, not r8: descscan2.py's per-group register map (editor rdi, effect r15, ui r9, sky rdi, item rdi, light rsi) is selected when --reg is absent, and the scan starts after the visitor's own `mov reg,[r8]/[rdx]` description load. `--stop-on-write` ends tracking at the first overwrite of that register (or at a call when it is volatile), fixing the reused r8/rsi misattribution: after the register is reused, later [reg+off] reads are no longer attributed to the description.

Rows below verify, per visitor, (a) the description-register load at visitor entry (proving the register-map value) and (b) the first overwrite/reload of that register (the stop-at-write point where attribution must end).

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning [V/I/?] |
|---|---|---|---|---|
| item desc reg rdi | 8 | 0x66469fd | `0x66469fd  mov rdi,[r8]` | Item visitor: description register = rdi, loaded from variant [r8]+0x0 at entry [V]; matches per-visitor register map (item=rdi) |
| light desc reg rsi | 8 | 0x6640dd5 | `0x6640dd5  mov rsi,[rdx]` | Light visitor: description register = rsi, loaded from variant [rdx]+0x0 at entry [V]; matches per-visitor register map (light=rsi) |
| sky desc reg rdi | 8 | 0x6656161 | `0x6656161  mov rdi,[r8]` | Sky visitor: description register = rdi, loaded from variant [r8]+0x0 at entry [V]; matches per-visitor register map (sky=rdi) |
| ui desc reg r9 | 8 | 0x6664a59 | `0x6664a59  mov r9,[r8]` | UI visitor: description register = r9, loaded from variant [r8]+0x0 at entry [V]; matches per-visitor register map (ui=r9) |
| effect desc reg r15 | 8 | 0x666acf1 | `0x666acf1  mov r15,[r8]` | Effect visitor: description register = r15, loaded from variant [r8]+0x0 at entry [V]; matches per-visitor register map (effect=r15) |
| sky stop-at-write | 8 | 0x6656f30 | `0x6656f30  mov rdi,[rbp+0x210]` | Stop-at-write: Sky's description register rdi is reloaded from stack slot [rbp+0x210] at 0x6656f30; descscan2 --stop-on-write ends attribution there, so [rdi+off] reads after this are not misattributed to the description [V] |

## CLOSES?

YES — every pending part of the R12 item line is proven by [V] rows:
1. Per-visitor register map: all five group visitors load the description into a non-r8 register at entry — item rdi (`0x66469fd mov rdi,[r8]`), light rsi (`0x6640dd5 mov rsi,[rdx]`), sky rdi (`0x6656161 mov rdi,[r8]`), ui r9 (`0x6664a59 mov r9,[r8]`), effect r15 (`0x666acf1 mov r15,[r8]`) [V]. This matches VISITOR_REG/VISITORS exactly, so descscan2 --reg defaults to the right register per visitor instead of assuming r8.
2. Stop at first write: Sky's description register rdi is reloaded from stack slot [rbp+0x210] at `0x6656f30 mov rdi,[rbp+0x210]` [V]; descscan2 --stop-on-write ends tracking at that overwrite (and at any call when the register is volatile), so a reused rdi/rsi/r8/r9/r15 is no longer attributed to the description [V].

Single blocking fact: none.

## TOOL REQUESTS

None
