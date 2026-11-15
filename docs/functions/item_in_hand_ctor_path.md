# I2c: renderItemFull 0x531b490 -> renderItem 0x531a580 -> ItemInHand ctor 0x668cb70 (1.26.62.01)

Tags [V] disassembly (disrange.py), [I] inferred. Note: docs/first-person-hand-notes-1.26.60.md uses 60.05 RVAs; renderItem was 0x531a210 there and is 0x531a580 here [I by identical shape and the single ctor-caller].

## Chain [V]
- 0x668cb70 (ItemInHand constructor) has exactly one caller function: 0x531a580 (two call sites 0x531ada1 and 0x531ae80, one per branch of the same selection).
- 0x531a580 (renderItem) has 6 callers: 0x531b490 (renderItemFull, call at 0x531cf16 and a second shape at ~0x531cec5 via 0x5324a20), 0x5321530, 0x5325160, 0x532b5a0, 0x598fa90, 0x6a61fe0.

## Call at 0x531cf16 (renderItemFull -> renderItem) [V]
rcx = [rbp+0x750] (ItemInHandRenderer this), rdx = rdi (render ctx, ctx+0x28 -> frame data), r8 = r12 (item render info; byte +0x290 is a "valid" flag, +0x270 the held-item pointer), r9 = rbp+0x6c8 (local transform/params), stack arg [rsp+0x20] = byte r15b (flags).

## renderItem 0x531a580 prologue [V]
rbx = this, r15 = ctx (rdx), rsi = item info (r8), r14 = r9 param, r13d = flags byte (stack arg [rbp+0x250]), rdi = [ctx+0x28].
Selection of the hand matrix base r12: flags bit 0x40 set -> this+0x260; else this + 0x1d0 + ((flags>>7)&1)<<6 (so two 0x40-sized matrices at this+0x1d0/+0x210 for main/off hand, and this+0x260 special) [V from 0x531a661..0x531a682, tag the "main/off hand" meaning [I]]. Then flags |= 8.

## ItemInHand ctor call arguments (0x531ada1 / 0x531ae80) [V]
0x668cb70(rcx = out ItemInHand* at rbp-0x20, rdx = rsi item info, r8 = rbp+0x250 (the flags byte slot), r9 = r12 hand matrix pointer,
 [rsp+0x20] = &[rbp+0x170] (item shared_ptr copy: pointer r13/r8 deref + control block at +0x178, refcount inc/dec seen),
 [rsp+0x28] = deque slot: ring entry from [[ctx+0x28]+0x18] (+0x48 array, +0x50 mask size, +0x58/+0x60 head/count; byte +0x78 set to 1 first) - the current per-frame render-data entry,
 [rsp+0x30] = byte [rdi+0x75], [rsp+0x38] = qword [rdi+0x20], [rsp+0x40] = word from byte [rdi+0x74], [rsp+0x48] = r14 (renderItem arg4), [rsp+0x50] = byte [rdi+0x7c]).
The ctor stores out = this+8 into [rcx], reads [item+0x270] (held item ptr, falls back to a static default when null) and copies its shared_ptr pair (refcount at +8/+0xC) [V]. Result is then handed to 0x531b180 (submit/queue) and destroyed with 0x531b340 [V].

## Open
- Field names of the 0x88 bytes read at [rdi+0x20/0x74/0x75/0x7c] (frame render-data flags) are [?].
- Full ctor body (0x668cb70..end) not reversed here.
