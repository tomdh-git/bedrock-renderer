## NEXT
DONE

# oc U-EF1b — VV pass order from builder 0x55f1450 (6ar): in/out resources per pass

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only; the exe is data, read-only via rdis/descscan2.
Item line: "F1b VV pass order from builder 0x55f1450 (6ar); in/out resources per pass pending ... pass declaration fns (0x5698290, 0x5684660, 0x5667860, 0x5693680 ...) copy a 28-byte descriptor struct opaquely [V]; nothing in 0x55f1450 or callees separates input from output resources statically, so in/out stays open".
Pending part to verify/close: in/out resources per pass. The 28-byte descriptor = offsets 0x00..0x1B. Direction: R = read from the source descriptor argument (pass config = input); W = write to the destination descriptor object (pass record = output).

Input data read fully (not re-run): docs/progress/oc_U-F1b.md, docs/progress/oc_U-F1b2.md (50 ordered call sites; 9 helpers; callee set from preflight [V]).
BGFX_MAP 6ar [V]: pass names/order from inline immediates already documented in docs/functions/vv_builder_pass_order_55f1450.md — names are pass labels, not resource directions; not redone here.

## Method

- descscan2.py --start/--end --reg on each declaration fn (tracks the descriptor-pointer register and its copies/spills, reports every [reg+off] access with width and site) [V tool]
- rdis dis/fn of each declaration fn to quote exact instruction text [V]

## 28-byte descriptor field map (offsets 0x00..0x1B) — one row per distinct offset, all its sites listed

| offset | size | sites (R = read from source descriptor / input; W = write to dest descriptor / output) | verbatim `0xRVA  instr` proof | meaning | tag |
| 0x00 | 16 | R sub_5667860 0x5667887 [rdx+0x00] (a1 source); R sub_5698290 0x56982dc [rbx+0x00] (a2=r8 source); W sub_5667860 0x566788a [rcx+0x00] (a0 dest) | `0x5667887  movups xmm0,[rdx]` `0x56982dc  movups xmm0,[rbx]` `0x566788a  movups [rcx],xmm0` | bytes 0x00-0x0F read from source descriptor (input) and written to dest descriptor at same byte position (output): same bytes both directions, opaque pass-through, no input/output split | [V] |
| 0x0C | 16 | R sub_5698290 0x56982df [rbx+0x0C] (a2=r8 source) | `0x56982df  movups xmm1,[rbx+0xC]` | source bytes 0x0C-0x1B read (input); dest counterpart written by row 0x14 store (same 16 bytes, shifted copy) | [V] |
| 0x10 | 8 | R sub_5667860 0x566787f [rdx+0x10] (a1 source); W sub_5667860 0x5667883 [rcx+0x10] (a0 dest); R sub_5693680 0x56936f2 [rsi+0x10] (source) | `0x566787f  mov rax,[rdx+0x10]` `0x5667883  mov [rcx+0x10],rax` `0x56936f2  mov rax,[rsi+0x10]` | bytes 0x10-0x17 read (input) and written at same byte position (output): opaque pass-through, no input/output split | [V] |
| 0x14 | 16 | W sub_5698290 0x56982e7 [rdi+0x14] (dest) | `0x56982e7  movups [rdi+0x14],xmm1` | dest bytes 0x14-0x23 written (output); source counterpart read at row 0x0C (shifted copy) | [V] |
| 0x18 | 4 | R sub_5667860 0x566788d [rdx+0x18] (a1 source); W sub_5667860 0x5667892 [rcx+0x18] (a0 dest) | `0x566788d  movss xmm0,[rdx+0x18]` `0x5667892  movss [rcx+0x18],xmm0` | bytes 0x18-0x1B read (input) and written at same byte position (output): opaque pass-through, no input/output split | [V] |

Coverage: rows 0x00 (0x00-0x0F), 0x10 (0x10-0x17), 0x18 (0x18-0x1B) cover all 28 bytes 0x00..0x1B; every byte is read from the source argument and written to the destination argument. Rows 0x0C/0x14 are sub_5698290's encoding of the same copy (reads rbx+0x00/0x0C, writes rdi+8/+0x14). Sub_5684660 reads rdx+0x08/0x10/0x18 [V descscan2, linear path, branches not followed] and sub_5693680 reads rsi+0x00/0x08/0x10/0x18 [V descscan2] — same fields, same read+write treatment, no separating tag.
No declaration fn, and no call site in 0x55f1450 (50 sites, 9 helpers; args are pointers, ranges and counts only — see oc_U-F1b2.md Phase 4), marks any descriptor byte as input-only or output-only, and no resource IDs are passed per pass. Builder-side names (Shadow Cascades .. FullScreenOverlayObjects) are pass labels, not resource directions [V docs/functions/vv_builder_pass_order_55f1450.md].

## CLOSES?

CLOSES? NO — blocking fact: the 28-byte pass descriptor is copied opaquely in every pass-declaration fn (all bytes 0x00-0x1B are read from the source argument and written to the destination argument; e.g. sub_5667860 same-offset field copy at 0x00/0x10/0x18 [V], sub_5698290 shifted copy reads rbx+0x00/0x0C and writes rdi+8/+0x14 [V]); nothing in 0x55f1450 or its callees tags any descriptor field as input-only or output-only and no per-pass resource IDs exist at the call sites, so in/out resources per pass cannot be assigned statically — in/out stays open.

## TOOL REQUESTS

None — used existing tools only: descscan2.py, rdis.exe fn/dis, verify_oc.py, delegate.py.
