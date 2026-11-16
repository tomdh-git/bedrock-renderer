# U-A6c: bgfx sorted item list at Frame+0x94700 + sort key bit layout

Target: Minecraft.Windows.exe 1.26.62.01 (image-base RVAs). Static analysis only.

## Sources verified [V]
- `rdis fn 0xbc60740` (Encoder::submit, size 0x5d0) — full body quoted below.
- `rdis fn 0xbc61e20` (Frame::sort, size 0x215) — full body quoted below.
- `rdis fn 0xbc61560` (Encoder::submitCustom, custom item, key bit 53).
- `rdis dis 0xbc62040 60` (radix sort entry, called by Frame::sort).
- Headers: `src/sdk/mc/deps/bgfx/Frame.h`, `src/sdk/mc/deps/bgfx/Encoder.h`.
- Map: docs/BGFX_MAP.md sections 6am, 6e, 6t, 6ao, 6fg.
- Dossiers: docs/functions/bc60740.md, docs/functions/bc61e20.md.

---

## (1) Sort key bit layout — where the key u64 is BUILT

Built in `Encoder::submit` (0xbc60740) at the store:
```
bc60991  mov [rcx+r14*8+0x14700],rax        ; key u64 -> Frame+0x14700+idx*8
bc6099c  mov [rax+r14*2+0x94700],di         ; sorted u16 value (=idx) -> Frame+0x94700+idx*2
```
`rcx` = Encoder+0x00 = Frame*, `r14d` = allocated draw index (CAS on `Frame+0xDC57E8`). `rax` holds the assembled key.

The three key-type branches are selected by the per-view mode byte at `ctx+0x1EAB1B2 + viewId*0x140`:

```
bc60885  mov r11,[0x12AE1748]               ; s_ctx global
bc6088c  movzx edx,dx                       ; viewId
bc6088f  lea r14,[rdx+rdx*4]                ; viewId*5
bc60893  shl r14d,6                         ; viewId*0x140
bc60897  movzx r14d,byte ptr [r11+r14+0x1EAB1B2]  ; view mode byte
```

### View field (bits 54..61) — every branch

Depth branch (mode 2/3):
```
bc608d8  shl rdx,0x36                       ; viewId << 54   (rdx was viewId)
bc608dc  and rdx,rax                        ; rax = 0x3FC0000000000000 (bits 54..61 mask)
bc608df  or rdx,r10                         ; depth<<18 already in r10
bc608e2  or rdx,r11                         ; trans<<16
bc608e5  or rdx,r8                          ; program<<5
bc608e8  mov rax,0x14000000000000           ; tag 0x14 (depth), bits 50..52
bc608f2  jmp 0xBC6098B                      ; -> or rax,rdx
```

Sequence branch (mode 1):
```
bc60932  shl rdx,0x36                       ; viewId << 54
bc60936  and rdx,rax                        ; rax = 0x3FC0000000000000
bc60939  or rdx,rcx                         ; rcx = seq<<30 | trans<<28 | program<<17
bc6093c  mov rax,0x18000000000000           ; tag 0x18 (sequence)
bc60946  or rax,rdx
```

Program/default branch:
```
bc60977  shl rdx,0x36                       ; viewId << 54
bc6097b  and rdx,rax                        ; rax = 0x3FC0000000000000
bc6097e  or rdx,r11                         ; trans<<48
bc60981  mov rax,0x10000000000000           ; tag 0x10 (program)
bc6098b  or rax,rdx
```

Store of view mask constant:
```
bc60845  mov rax,0x3FC0000000000000         ; view mask = bits 54..61
```

### Tag/type field (bits 50..52), mode tag and draw bit

Bits 50..51 = sort type tag; bit 52 = draw bit (set on every draw key). The three tags:
```
bc608e8  mov rax,0x14000000000000           ; tag depth  = 0x14 << 48  (bits 50..52)
bc6093c  mov rax,0x18000000000000           ; tag sequence = 0x18 << 48
bc60981  mov rax,0x10000000000000           ; tag program  = 0x10 << 48
```
Draw bit is OR'd into every key via the tag constants themselves? No — the draw bit (bit 52) is part of the tag value: tag 0x10/0x14/0x18 at bits 50..52 already includes bit 52 = 1 (0x10 = bit 52). Compute items use neither bit 52 nor 53; custom items set bit 53.

Custom item (0xbc61560, submitCustom(view, fn=a, user=b), key bit 53):
```
bc61645  mov [rsi+0x100],r8                 ; payload word a -> Encoder+0x100
bc6164c  mov [rsi+0x108],r9                 ; payload word b -> Encoder+0x108
...
bc61697  mov rcx,0x20000000000000           ; bit 53 (custom bit)
bc616a1  or rcx,rax                         ; rax = view<<54 | seq<<20
bc616aa  mov [rax+r15*8+0x14700],rcx        ; key store (custom item)
bc616b5  mov [rax+r15*2+0x94700],di         ; sorted u16 value
```
[UNVERIFIED: 0xbc61560 payload words r8/r9 meaning — fn pointer + user data per 6fg/6fh, not re-read for this unit.]

### Sequence field (mode 1, Sequential)
```
bc608fc  lock xadd [r11+rdx*4+0x1EAAC60],ecx   ; per-view sequence counter, ctx+0x1EAAC60+view*4
bc60906  mov [rsi+0xC],ecx                      ; seq result -> Encoder+0x0C
bc60909  and ecx,0xFFFFF                        ; seq & 0xFFFFF (20 bits)
bc6090f  shl rcx,0x1E                           ; seq << 30
bc60913  mov edx,[rsi+0x10]                     ; program
bc60916  shl edx,0x11                           ; program << 17
bc60919  and edx,0xFFE0000                      ; program bits
bc6091f  or rdx,rcx
bc60922  mov ecx,[rsi+0x14]                     ; trans (flags low 2 bits)
bc60925  and ecx,3
bc60928  shl ecx,0x1C                           ; trans << 28
bc6092b  or rcx,rdx
```
Sequence key: `0x18<<48 | view<<54 | (seq&0xFFFFF)<<30 | (program<<17)&0x0FFE0000 | (trans&3)<<28`
[I: program occupies bits 17..27 within low32; trans bits 28..29; seq bits 30..49.]

### Depth field (mode 2 DepthAscending / 3 DepthDescending)
```
bc608b6  neg r10d                               ; depth = -depth for DepthDescending
bc608b9  mov [rsi+8],r10d                       ; depth -> Encoder+0x08
bc608c0  shl r10,0x12                           ; depth << 18
bc608c4  shl r8d,5                              ; program << 5
bc608c8  movzx r8d,r8w
bc608cc  mov r11d,[rsi+0x14]                    ; trans
bc608d0  and r11d,3
bc608d4  shl r11d,0x10                          ; trans << 16
bc608d8  shl rdx,0x36                           ; viewId << 54
bc608dc  and rdx,rax
bc608df  or rdx,r10                             ; depth<<18
bc608e2  or rdx,r11                             ; trans<<16
bc608e5  or rdx,r8                              ; program<<5
bc608e8  mov rax,0x14000000000000               ; tag depth
```
Depth key: `0x14<<48 | view<<54 | depth<<18 | (program<<5)&0xFFFF | (trans&3)<<16`
[I: depth is u32 at bits 18..49; program bits 5..15; trans bits 16..17.]

### Program field (default mode, sort by program)
```
bc6094e  mov r10d,[rsi+8]                       ; depth
bc60956  shl r10,5                              ; depth << 5
bc6095a  movzx r8d,r8w                          ; program
bc6095e  and r8d,0x7FF                          ; program & 0x7FF (11 bits)
bc60965  shl r8,0x25                            ; program << 37
bc60969  or r8,r10                              ; depth<<5
bc6096c  and r11d,3                             ; trans
bc60970  shl r11,0x30                           ; trans << 48
bc60974  or r11,r8
bc60977  shl rdx,0x36                           ; viewId << 54
bc6097b  and rdx,rax
bc6097e  or rdx,r11
bc60981  mov rax,0x10000000000000               ; tag program
```
Program key: `0x10<<48 | view<<54 | (program&0x7FF)<<37 | (trans&3)<<48 | depth<<5`
[I: depth bits 5..~16; program bits 37..47; trans bits 48..49. Note tag program's bit 52 (0x10) overlaps trans<<48 bit 48..49? No: 0x10<<48 = bits 50..52; trans<<48 = bits 48..49 — adjacent, no overlap.]

### Field summary table

| Bit range | Width | Encodes | Quoted instruction that shifts/ors it |
|-----------|-------|---------|---------------------------------------|
| 54..61 | 8 | view id | `bc608d8  shl rdx,0x36` / `bc60932  shl rdx,0x36` / `bc60977  shl rdx,0x36` (view<<54), masked with `bc60845  mov rax,0x3FC0000000000000` |
| 52 | 1 | draw bit (set on every draw key; clear on compute/custom) | part of tag constants `0x10<<48`/`0x14<<48`/`0x18<<48` (0x10 = bit 52); custom sets `bc61697  mov rcx,0x20000000000000` (bit 53) |
| 53 | 1 | custom item (submitCustom) | `bc61697  mov rcx,0x20000000000000` ; `bc616a1  or rcx,rax` |
| 50..51 | 2 | sort type tag low bits | within tag constants 0x10/0x14/0x18 << 48 |
| 48..49 | 2 | trans (flags low 2 bits) — payload high bits | `bc60928  shl ecx,0x1C` (seq) / `bc608d4  shl r11d,0x10` (depth) / `bc60970  shl r11,0x30` (program) |
| 30..49 (seq) | 20 | sequence counter (per view) | `bc6090f  shl rcx,0x1E` (seq<<30) |
| 17..29 (seq) | 13 | program (seq type) | `bc60916  shl edx,0x11` (program<<17), `and edx,0xFFE0000` |
| 28..29 (seq) | 2 | trans (seq type) | `bc60928  shl ecx,0x1C` |
| 18..49 (depth) | 32 | depth (u32) | `bc608c0  shl r10,0x12` (depth<<18) |
| 5..15 (depth) | 11 | program (depth type) | `bc608c4  shl r8d,5` |
| 16..17 (depth) | 2 | trans (depth type) | `bc608d4  shl r11d,0x10` |
| 37..47 (program) | 11 | program (program type) | `bc60965  shl r8,0x25` |
| 5..16 (program) | 12 | depth (program type) | `bc60956  shl r10,5` |
| 48..49 (program) | 2 | trans (program type) | `bc60970  shl r11,0x30` |

Key assembly: `bc608e2  or rdx,r11` / `bc608e5  or rdx,r8` / `bc6091f  or rdx,rcx` / `bc6092b  or rcx,rdx` / `bc6097e  or rdx,r11` / `bc6098b  or rax,rdx`, final store `bc6098e  mov [rcx+r14*8+0x14700],rax`.

[UNVERIFIED: 0xbc60740 exact bit boundaries of program/depth/trans within each type — field ranges above are inferred from shifts+masks, not live-checked against a key; tag values 0x10/0x14/0x18 at bits 50..52 are [V] from the immediates.]

---

## (2) Where the key is CONSUMED — Frame::sort

Function RVA: **0xbc61e20** (`bgfx::Frame::sort`), size 0x215 bytes, 119 instructions. Called by `0xe82e230` (RendererContextD3D12::submit slot 50), `0xe7f5380`, `0xe85e5c0`.

Algorithm: **radix sort** (`bx::radixSort`), NOT std::sort comparison. Called via:
```
bc61f67  call 0xBC62040                 ; bx::radixSort(m_sortKeys, tempKeys, m_sortValues, tempValues, count)
```
Arguments:
```
bc61f40  mov rdx,[0x12AE1748]           ; s_ctx
bc61f47  lea r9,[rdx+0x1D7D0C8]         ; tempValues (uint16_t[])
bc61f4e  lea r8,[rsi+0x94700]           ; m_sortValues (output, u16 item indices)
bc61f55  add rdx,0x1CFD0D0              ; tempKeys (u64[] scratch)
bc61f5c  lea rcx,[rsi+0x14700]          ; m_sortKeys (input, u64 keys)
bc61f63  mov [rsp+0x20],eax             ; count = m_numRenderItems
```
Element stride: keys are u64 (stride 8) at `Frame+0x14700`, values are u16 (stride 2) at `Frame+0x94700`. What is sorted: key u64 + item index u16 together (radix sort permutes both in parallel). Radix sort body at 0xbc62040 (0x2000 bytes) sorts by key bytes (seen bucketing on `key & 0x7FF` at `bc620c7  and r10d,0x7FF`).

Before sorting, Frame::sort remaps view id -> view order in every key:
```
bc61e92  mov rax,0xC03FFFFFFFFFFFFF     ; mask clears bits 54..61 (view)
bc61ec3  shr r11,0x36                   ; key >> 54 = view id
bc61ecb  movzx r11d,word ptr [rsp+r11*2+0x30]   ; viewRemap[view] -> order
bc61ed1  shl r11,0x36                   ; order << 54
bc61ed5  and r9,rax                     ; key & mask (view cleared)
bc61ed8  or r9,r11                      ; key with remapped view
bc61edb  mov [rsi+rcx*8+0x14700],r9     ; write back
```
Loop: `bc61eb0..bc61f0d` (two keys per iteration, unrolled x2), tail `bc61f14..bc61f32` (single key). Count from `bc61e7c  mov edx,[rsi+0xDC57E8]` (m_numRenderItems). If count==1, single-key path `bc61ea1..bc61f32`; if 0, skip (`bc61e8c  je 0xBC61F40`).

After the draw sort, blit keys (`Frame+0x934778`, view in top byte byte+3) are remapped then tail-jumped to radix sort at `bc6201f  jmp 0xBC62BC0`.

The comparator is **not** std::sort — it's `bx::radixSort` (LSB/MSB radix on u64 keys) [V: direct call to 0xbc62040, no std::sort symbol referenced]. The sorted output is the u16 item-index list at `Frame+0x94700`, walked in order by the executor (`0xe821120` reads `u16 [Frame+0x94700+pos*2]`).

---

## (3) What Frame+0x94700 holds

- Element type: **uint16_t** (u16), one per sorted slot.
- Array size: **65536 entries** (0x20000 bytes) = `uint16_t m_sortValues[65536]` (Frame.h `kSortedItems = 0x94700`), ends exactly at `Frame+0xB4700` (draw headers). 65535 valid entries (BGFX_CONFIG_MAX_DRAW_CALLS-1), slot 65535 unused/padding.
- Semantics: **render item index per sorted slot** — `sorted[i]` = the index (0..numItems-1) of the i-th draw in key order. Initialized to `idx` (the item's own index) at submit: `bc6099c  mov [rax+r14*2+0x94700],di`. After Frame::sort the list is in radix-sorted key order; the executor walks `sorted[0..numItems)` and for each `idx` reads draw header at `Frame+0xB4700 + idx*0x80`.
- Count location: **`Frame+0xDC57E8`** = `uint32_t m_numRenderItems` (atomic slot counter, cap 0xFFFE). Read at `bc61e7c  mov edx,[rsi+0xDC57E8]`. Allocated via CAS `lock cmpxchg [rcx+0xDC57E8],r14d` at submit (`bc607ea`).
- Adjacent: keys u64 at `Frame+0x14700` (stride 8); blit keys u32 at `Frame+0x934778`, blit count `u16 Frame+0xDC57EC`.

---

## Open / unverified

- [UNVERIFIED: 0xbc61560] custom-item payload words r8 (fn) / r9 (user) exact meaning — per 6fg/6fh it's `fn(user, ctx)` on the render thread; not re-verified in this unit.
- [UNVERIFIED: 0xbc60740] exact bit boundaries of program/depth/trans within each key type are inferred from shift/mask immediates, not live-checked against an actual key value.
- [UNVERIFIED: 0xbc62040] radix-sort inner body (bucket count, passes) not fully read — only the call site and the `key & 0x7FF` bucketing seen in the first 60 instructions.

## Verification
Quoted `0xRVA  instr` lines above are taken verbatim from `rdis fn` output; run `python tools/sigs/verify_oc.py docs/progress/oc_U-A6c.md` to confirm.