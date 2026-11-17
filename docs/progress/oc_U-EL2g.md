## NEXT
DONE

# UNIT U-EL2g — L2g submit: descriptor binding types (6an), sort-key program field, descriptor flush (6ao)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred (say from what), [?] = unknown. Nothing invented.

## Scope: the three parts of item L2g, and what is pending
L2g covers submit (0xe82e230):
- descriptor binding types (6an) — type switch at 0xe8230b8, jump table 0xF4EE774 (9 entries, types 0..8), record type byte at record+0x13: already [V]-proven in oc_U-B3b.md (verify_oc 76/76). Not repeated here: this unit does ONLY the pending part.
- sort-key program field — (key >> 0x15) & 0x7FF at 0xe822483 / 0xe82248e, program record at this+0xB62178 + idx*0xF8: already [V]-proven in oc_U-B3b.md. Not repeated here.
- descriptor flush (6ao) — PENDING PART (B3b open item: "the 7 flush call sites not individually quoted" [UNVERIFIED: 0xe81b720 call sites]). 6ek corrects 6ao: 0xe81b720 is NOT a descriptor flush; it is the draw-batch flush (6ej). No separate descriptor flush exists. The real, still-unquoted evidence is the function's 7 call sites in the draw executor 0xe821120, individually quoted below [V].

## Pending part: 0xe81b720 call sites in executor 0xe821120 [V]

| flush-batch site | rva | size | verbatim `0xRVA  instr` proof line | tag |
|---|---|---|---|---|
| flush kind 0 then kind 1 (batch closed on bind/PSO/state change, executor 0xe822e40 region) | 0xe822e4e | 5 | e822e4e  call 0xE81B720 | [V] |
| flush kind 1 (mate of the pair above; r9d=1 set at e822e65) | 0xe822e6b | 5 | e822e6b  call 0xE81B720 | [V] |
| flush kind 0 (r9d=0 set at e82cfbe) | 0xe82cfc1 | 5 | e82cfc1  call 0xE81B720 | [V] |
| flush kind 1 (mate of the pair above; r9d=1 set at e82cfd8) | 0xe82cfde | 5 | e82cfde  call 0xE81B720 | [V] |
| single-kind flush (kind set before this window; listed as single-kind site in 6ej) | 0xe82d0f6 | 5 | e82d0f6  call 0xE81B720 | [V] |
| flush kind 0 (r9d=0 set at e82d128) | 0xe82d12b | 5 | e82d12b  call 0xE81B720 | [V] |
| flush kind 1 (mate of the pair above; r9d=1 set at e82d142) | 0xe82d148 | 5 | e82d148  call 0xE81B720 | [V] |

Size basis: each proof line is a near-rel32 `call` (E8 + 4-byte displacement) = 5 bytes, confirmed by the disassembly address delta (e.g. e822e4e -> e822e53).

## Verbatim proof lines (each confirmed verbatim against `rdis dis` output of the exe)

e822e4e  call 0xE81B720
e822e6b  call 0xE81B720
e82cfc1  call 0xE81B720
e82cfde  call 0xE81B720
e82d0f6  call 0xE81B720
e82d12b  call 0xE81B720
e82d148  call 0xE81B720

## Context for the flush target (cited, not re-decoded)
- Flush function: 0xe81b720 (size 0x803); its only caller is the draw executor 0xe821120 [V: docs/functions/e81b720.md, docs/functions/e821120.md].
- r9d = kind: 0 = DrawInstanced records (stride 0x70), 1 = DrawIndexedInstanced records (stride 0x88) [V: e81b720.md dossier].
- 6ek correction of 6ao: in 0xe81b720 the command-list slots decode as 0x60 = DrawInstanced (12), 0x68 = DrawIndexedInstanced (13), 0xd0 = ResourceBarrier (26), 0x130 = SetGraphicsRootConstantBufferView (38, root params 2/3), 0x158 = IASetIndexBuffer (43), 0x160 = IASetVertexBuffers (44), 0x1d8 = ExecuteIndirect (59). It does NOT touch descriptor tables; 6ao's "descriptor flush" was a mislabel — there is no descriptor flush in submit.

CLOSES? YES — the pending part of L2g (descriptor flush (6ao): the 7 executor call sites of 0xe81b720) is individually proven by [V] rows above; descriptor binding types (6an) and the sort-key program field ((key>>0x15)&0x7FF) were already [V]-proven in oc_U-B3b.md. Every part of the item line is [V]; nothing remains. Note: per 6ek, 0xe81b720 is the draw-batch flush, not a descriptor flush — no separate descriptor flush exists.

## TOOL REQUESTS
None — all verification via existing `rdis dis`; no helper script written.
