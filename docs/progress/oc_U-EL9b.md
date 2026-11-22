# Unit U-EL9b — L9b visibility: +0x63 reader (pending part only)

## NEXT
DONE

Exe: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base. Static analysis only; exe closed.

## Scope (this unit does ONLY the pending part)

Checklist item L9b (RENDER_CHECKLIST.md): launcher 0x7923d50, task body 0x792e630, compute 0x791f170 (+store 0x6b0c4c0), face matrix state+0x38..0x3d, listener 0x537dab0 (6bo-6br); phase 1 voxel occupancy read (6bs, Block+0xA3 opaque flag); flood 0x6b1ba90 read (6bt); BFS queue 0x6b0d380 (6bv), render-chunk record +0x254/0x258/0x25E (6bw); RenderChunk ctor 0x7926f20 layout (6bx); event processor 0x5334850 (6by) writes depth to draw record +0x63 via 0x533f580; draw-record handle lookup 0x533f580 (6bz, 6ca: ECS guess dropped); **+0x63 reader pending**.

Prior units (per RENDER_CHECKLIST.md) closed every part except "+0x63 reader". oc_U-H1d notes: +0x63 WRITER decoded (`mov [rax+0x63],bl` at 0x53365fa via 0x533f580 at 0x53365e8); +0x63 READER still unfound there; 0x533f580 has only sub_5334850 as caller (3 sites). This unit verifies the reader at 0x53398ee inside 0x5334850.

## Inputs read in full (no tool re-run)

- docs/BGFX_MAP.md sections 6bn, 6bq, 6br, 6bs, 6bt, 6bv, 6bw, 6bx, 6by, 6bz, 6ca — leads only; every claim below re-verified in the disassembly.
- docs/progress/RENDER_CHECKLIST.md lines ~171/353 (H1b item text + prior progress notes).
- docs/progress/ext-culling-visitor.md (claims reader `cmp byte [rax+0x63],0` at 0x53398ee — treated as a lead to verify, not proof).
- docs/progress/pre/0x537dab0.md, 0x6b1ba90.md, 0x791f170.md, 0x7923d50.md, 0x792e630.md (prior units' verified results; not redone).

## Pending part: +0x63 reader — verified

Verified with `rdis.exe "<exe>" dis 0x53398e0 44` (verbatim rdis output; the reader line is highlighted):

```
  53398e0  mov rdx,rdi
  53398e3  call 0x533F580      ; -> sub_533f580   (rax = per-chunk record for the section pos)
  53398e8  nop
  53398e9  test rax,rax
  53398ec  je short 0x53398D0  ; -> sub_53398d0   (null record -> skip)
  53398ee  cmp byte ptr [rax+0x63],0   ; R ret@533f580+0x63   <<< THE +0x63 READER
  53398f2  jne short 0x53398D0   ; -> sub_53398d0   (non-zero depth -> already visible -> skip)
  53398f4  cmp byte ptr [rsi],0
  53398f7  jne short 0x53398A0   ; -> sub_53398a0
  53398f9  mov dword ptr [0],0xDEADC0DE
  5339904  jmp short 0x53398A0   ; -> sub_53398a0
```

Flow: for each chunk position the loop calls handle lookup 0x533f580 (0x53398e3); `rax` is the record; `cmp byte ptr [rax+0x63],0` reads the depth byte at record+0x63 (1 byte); if non-zero the record is skipped (`jne 0x53398d0`), i.e. chunks that already have a visibility depth are not re-queued; zero entries fall through to be appended to the not-yet-visible/rebuild list. So +0x63 != 0 means "visibility depth assigned (visible)", +0x63 == 0 means "candidate". Semantics of the branch outcome are shown by the instruction flow itself [V]; the "visible list" naming is [I].

`xref.py callers 0x533f580` returns only `0x5334850 0x5f3c` — the event processor is the sole caller function of the lookup, so no other site obtains a `found` record through 0x533f580 and no other +0x63 reader exists on this path [V for single caller; the read itself is [V] at 0x53398ee].

## Answer table (pending part: +0x63 reader)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof line | [V]/[I]/[?] |
|---|---|---|---|---|---|
| +0x63 reader (record handle lookup feeding the read) | 0x53398e3 | - | - | `0x53398e3  call 0x533F580` | [V] |
| +0x63 reader | 0x53398ee | 1 | [rax+0x63] | `0x53398ee  cmp byte ptr [rax+0x63],0` | [V] |
| +0x63 reader branch (non-zero depth -> skip) | 0x53398f2 | - | - | `0x53398f2  jne short 0x53398D0` | [V] |

Size rule: byte-sized memory operand -> size 1; `call`/`jne` touch no memory -> "-".

## CLOSES?

CLOSES? YES — the only pending part of item L9b ("+0x63 reader pending") is proven by [V] rows: `0x53398ee  cmp byte ptr [rax+0x63],0` reads the depth byte of the record returned by 0x533f580 (`0x53398e3  call 0x533F580`), and `0x53398f2  jne short 0x53398D0` skips records whose +0x63 depth byte is non-zero; 0x533f580 has 0x5334850 as its only caller (xref callers), so no other reader site exists on this path. Out of scope for this unit (left open elsewhere): the event processor 0x5334850 is not instruction-complete (21 gaps per oc_U-H1d); writer sites 0x53365fa/0x5337eb1 are writes, not readers, and were not re-decoded here.

## TOOL REQUESTS

None (used existing tools only: rdis dis, xref.py callers; verified the ext-culling-visitor.md lead statically).
