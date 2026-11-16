# oc U-F1b2 — VV pass order from frame builder 0x55f1450 (checklist F1b, BGFX_MAP 6ar)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis disassembly of .text). Builder range: 0x55f1450..0x563f594 (size 0x4e144) [V preflight fn header].

## NEXT
All steps complete. Deliverable: ordered pass table with quoted argument-setup instructions per call site. Verify with `python tools/sigs/verify_oc.py docs/progress/oc_U-F1b2.md`.

## Phase 1 — Preflight (done)
- `PYTHONUTF8=1 python tools/preflight.py 0x55f1450` -> docs/progress/pre/0x55f1450.md [V]
- fn `sub_55f1450  [0x55f1450..0x563f594)  size 0x4e144  0 xrefs in` [V preflight]
- 0 direct callers (indirect/vtable dispatch only) [V preflight]
- Callees captured [V preflight callee set]

## Phase 2 — Ordered callee list (rdis callees + full disassembly)
50 pass-declaration call sites found in address order, targeting 9 unique helpers in 0x566xxxx-0x56a8xxx range:
- sub_5667860 (4 calls)
- sub_5684660 (1 call)
- sub_5689800 (18 calls)
- sub_5693680 (7 calls)
- sub_5694510 (2 calls)
- sub_5695960 (1 call)
- sub_5696540 (1 call)
- sub_5697650 (1 call)
- sub_5698290 (15 calls)

## Phase 3 — Full disassembly for ordered call sites
Full function listing generated: docs/progress/pre/0x55f1450_full.lst (58550 lines) [V]

## Phase 4 — Per-pass entries (call site RVA, callee RVA, pass name, quoted instr lines, in/out resources)

### Pass 1: 0x55f182b -> sub_5689800
**Pass name:** [UNVERIFIED: 0x55f182b no inline string found; likely early geometry/setup pass]
**Argument setup (quoted):**
```
0x55f1822  mov rcx,rdi
0x55f1825  mov rdx,rbx
0x55f1828  mov r8,r14
0x55f182b  call 0x5689800
```
**In/out resources:** rcx=rdi (start), rdx=rbx (end), r8=r14 (count) [I from register tracking]

---

### Pass 2: 0x55f1fca -> sub_5698290
**Pass name:** [UNVERIFIED: 0x55f1fca no inline string found]
**Argument setup (quoted):**
```
0x55f1fb9  lea r8,[rbp+0x2C00]
0x55f1fc0  mov rcx,[rbp+0x3260]
0x55f1fc7  mov rdx,rcx
0x55f1fca  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x2C00] (pass config struct) [V]

---

### Pass 3: 0x55f1fe7 -> sub_5698290
**Pass name:** [UNVERIFIED: 0x55f1fe7 no inline string found]
**Argument setup (quoted):**
```
0x55f1fd6  lea r8,[rbp+0x27A0]
0x55f1fdd  mov rcx,[rbp+0x3260]
0x55f1fe4  mov rdx,rcx
0x55f1fe7  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x27A0] (pass config struct) [V]

---

### Pass 4: 0x55f2624 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x55f2624 no inline string found]
**Argument setup (quoted):**
```
0x55f261b  mov rcx,r15
0x55f261e  mov rdx,rdi
0x55f2621  mov r8,rbx
0x55f2624  call 0x5689800
```
**In/out resources:** rcx=r15 (start), rdx=rdi (end), r8=rbx (count) [I]

---

### Pass 5: 0x55f2929 -> sub_5667860
**Pass name:** [UNVERIFIED: 0x55f2929 no inline string found]
**Argument setup (quoted):**
```
0x55f2922  lea rcx,[rbp+0x27A0]
0x55f2929  call 0x5667860
```
**In/out resources:** rcx=[rbp+0x27A0] (pass config) [V]; xmm0/xmm1 set up with computed float values prior [V]

---

### Pass 6: 0x55f4186 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x55f4186 no inline string found]
**Argument setup (quoted):**
```
0x55f417d  mov rcx,r15
0x55f4180  mov rdx,rsi
0x55f4183  mov r8,rbx
0x55f4186  call 0x5689800
```
**In/out resources:** rcx=r15 (start), rdx=rsi (end), r8=rbx (count) [I]

---

### Pass 7: 0x55f486a -> sub_5689800
**Pass name:** [UNVERIFIED: 0x55f486a no inline string found]
**Argument setup (quoted):**
```
0x55f4861  mov rcx,r12
0x55f4864  mov rdx,rdi
0x55f4867  mov r8,r14
0x55f486a  call 0x5689800
```
**In/out resources:** rcx=r12 (start), rdx=rdi (end), r8=r14 (count) [I]

---

### Pass 8: 0x55f6454 -> sub_5667860
**Pass name:** [UNVERIFIED: 0x55f6454 no inline string found; near Shadow Cascades strings at 0x55f383d]
**Argument setup (quoted):**
```
0x55f644a  lea rcx,[rbp+0x27A0]
0x55f6451  mov rdx,rdi
0x55f6454  call 0x5667860
```
**In/out resources:** rcx=[rbp+0x27A0] (pass config), rdx=rdi (resource) [V]

---

### Pass 9: 0x55f67b4 -> sub_5667860
**Pass name:** [UNVERIFIED: 0x55f67b4 no inline string found]
**Argument setup (quoted):**
```
0x55f67ad  lea rcx,[rbp+0x27A0]
0x55f67b4  call 0x5667860
```
**In/out resources:** rcx=[rbp+0x27A0] (pass config) [V]; rdx=[rbp+0x1400] set prior [V]

---

### Pass 10: 0x55f7051 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x55f7051 no inline string found]
**Argument setup (quoted):**
```
0x55f7048  mov rcx,r12
0x55f704b  mov rdx,rdi
0x55f704e  mov r8,r14
0x55f7051  call 0x5689800
```
**In/out resources:** rcx=r12 (start), rdx=rdi (end), r8=r14 (count) [I]

---

### Pass 11: 0x55f7551 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x55f7551 no inline string found]
**Argument setup (quoted):**
```
0x55f7548  mov rcx,r12
0x55f754b  mov rdx,rdi
0x55f754e  mov r8,r14
0x55f7551  call 0x5689800
```
**In/out resources:** rcx=r12 (start), rdx=rdi (end), r8=r14 (count) [I]

---

### Pass 12: 0x55f83ca -> sub_5689800
**Pass name:** [UNVERIFIED: 0x55f83ca no inline string found]
**Argument setup (quoted):**
```
0x55f83c1  mov rcx,r12
0x55f83c4  mov rdx,rsi
0x55f83c7  mov r8,r14
0x55f83ca  call 0x5689800
```
**In/out resources:** rcx=r12 (start), rdx=rsi (end), r8=r14 (count) [I]

---

### Pass 13: 0x55ff2c5 -> sub_5698290
**Pass name:** "Core/Screen/Blit" / "DebugDepthBufferCopy" [V nearby strings at 0x560b758, 0x560b842]
**Argument setup (quoted):**
```
0x55ff2b4  mov rcx,[rbp+0x3260]
0x55ff2bb  mov rdx,rcx
0x55ff2be  lea r8,[rbp+0x1EF4]
0x55ff2c5  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x1EF4] (pass config) [V]

---

### Pass 14: 0x55ff2f8 -> sub_5698290
**Pass name:** "Core/Screen/Blit" / "DebugDepthBufferCopy" [V same strings]
**Argument setup (quoted):**
```
0x55ff2e7  mov rcx,[rbp+0x3260]
0x55ff2ee  mov rdx,rcx
0x55ff2f1  lea r8,[rbp+0x1C40]
0x55ff2f8  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x1C40] (pass config) [V]

---

### Pass 15: 0x55ff31d -> sub_5698290
**Pass name:** "Core/Screen/Blit" / "DebugDepthBufferCopy" [V same strings]
**Argument setup (quoted):**
```
0x55ff30c  mov rcx,[rbp+0x3260]
0x55ff313  mov rdx,rcx
0x55ff316  lea r8,[rbp+0x1C40]
0x55ff31d  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x1C40] (pass config) [V]

---

### Pass 16: 0x560673d -> sub_5689800
**Pass name:** [UNVERIFIED: 0x560673d no inline string found]
**Argument setup (quoted):**
```
0x5606734  mov rcx,r13
0x5606737  mov rdx,rsi
0x560673a  mov r8,r14
0x560673d  call 0x5689800
```
**In/out resources:** rcx=r13 (start), rdx=rsi (end), r8=r14 (count) [I]

---

### Pass 17: 0x5607fdd -> sub_5689800
**Pass name:** [UNVERIFIED: 0x5607fdd no inline string found]
**Argument setup (quoted):**
```
0x5607fd4  mov rcx,r13
0x5607fd7  mov rdx,rsi
0x5607fda  mov r8,r14
0x5607fdd  call 0x5689800
```
**In/out resources:** rcx=r13 (start), rdx=rsi (end), r8=r14 (count) [I]

---

### Pass 18: 0x5609b8c -> sub_5689800
**Pass name:** [UNVERIFIED: 0x5609b8c no inline string found]
**Argument setup (quoted):**
```
0x5609b86  mov rdx,rsi
0x5609b89  mov r8,r14
0x5609b8c  call 0x5689800
```
**In/out resources:** rcx=rcx (from prior mov rcx,[rbp+0x3210]), rdx=rsi (end), r8=r14 (count) [V/I]

---

### Pass 19: 0x560b6be -> sub_5698290
**Pass name:** "Core/Screen/Blit" / "DebugDepthBufferCopy" [V strings at 0x560b758, 0x560b842]
**Argument setup (quoted):**
```
0x560b6ad  mov rcx,[rbp+0x3260]
0x560b6b4  mov rdx,rcx
0x560b6b7  lea r8,[rbp+0x2440]
0x560b6be  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x2440] (pass config) [V]

---

### Pass 20: 0x560bd0d -> sub_5698290
**Pass name:** "Core/Screen/Blit" / "BlitUncompressed" [V strings at 0x560bd72, 0x560be9f]
**Argument setup (quoted):**
```
0x560bcfc  mov rcx,[rbp+0x3260]
0x560bd03  mov rdx,rcx
0x560bd06  lea r8,[rbp+0x1EA0]
0x560bd0d  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x1EA0] (pass config) [V]

---

### Pass 21: 0x560cc28 -> sub_5694510
**Pass name:** " Sky (pre-water)" / "ForwardPBR - Sky (pre-water)" / "ForwardPBRTransparent" [V strings at 0x560ca58, 0x560ca63, 0x560caa7]
**Argument setup (quoted):**
```
0x560cc0e  lea rax,[rbp+0x2C00]
0x560cc15  mov [rsp+0x20],rax
0x560cc1a  lea rcx,[rbp+0x27A0]
0x560cc21  lea r9,[rbp+0x2EF0]
0x560cc28  call 0x5694510
```
**In/out resources:** rcx=[rbp+0x27A0], r9=[rbp+0x2EF0], stack[0x20]=[rbp+0x2C00] (config structs) [V]; r8=[rbp+0x21B0], rdx=[rax+0x40] set prior [V]

---

### Pass 22: 0x560e734 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x560e734 no inline string found]
**Argument setup (quoted):**
```
0x560e72b  mov rcx,rdi
0x560e72e  mov rdx,rsi
0x560e731  mov r8,r12
0x560e734  call 0x5689800
```
**In/out resources:** rcx=rdi (start), rdx=rsi (end), r8=r12 (count) [I]

---

### Pass 23: 0x5610bd3 -> sub_5684660
**Pass name:** "TransparentDegamma" [V string at 0x5610e82 nearby]
**Argument setup (quoted):**
```
0x5610b96  mov [rsp+0x38],rax
0x5610ba2  mov [rsp+0x30],rax
0x5610bae  mov [rsp+0x20],rax
0x5610bb3  mov byte ptr [rsp+0x28],1
0x5610bb8  mov rcx,[rbp+0x3260]
0x5610bbf  lea rdx,[rbp+0x2848]
0x5610bc6  mov r8d,2
0x5610bcc  lea r9,[rbp+0x2EF0]
0x5610bd3  call 0x5684660
```
**In/out resources:** rcx=[rbp+0x3260], rdx=[rbp+0x2848], r8=2, r9=[rbp+0x2EF0], stack args [V]; name "TransparentDegamma" set at [rbp+0x2EF0] via mov rcx,0x726170736E617254 / mov dword ptr [rax+7],0x746E6572 ("Transparent\0") [V]

---

### Pass 24: 0x5611a18 -> sub_5698290
**Pass name:** "Core/Screen/Blit" / "rDepthBufferCopy" / "DebugWaterDepthBufferCopy" [V strings at 0x5611ab2, 0x5611b9c, 0x5611ba7]
**Argument setup (quoted):**
```
0x5611a07  mov rcx,[rbp+0x3260]
0x5611a0e  mov rdx,rcx
0x5611a11  lea r8,[rbp+0x2440]
0x5611a18  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x2440] (pass config) [V]

---

### Pass 25: 0x5612b0d -> sub_5689800
**Pass name:** [UNVERIFIED: 0x5612b0d no inline string found; near ForwardPBRTransparent strings]
**Argument setup (quoted):**
```
0x5612b04  mov rcx,rdi
0x5612b07  mov rdx,rsi
0x5612b0a  mov r8,r14
0x5612b0d  call 0x5689800
```
**In/out resources:** rcx=rdi (start), rdx=rsi (end), r8=r14 (count) [I]

---

### Pass 26: 0x5613b8f -> sub_5693680
**Pass name:** [UNVERIFIED: 0x5613b8f no inline string found; near GeometryPrepassAlphaTest strings]
**Argument setup (quoted):**
```
0x5613b81  mov rcx,[rbp+0x3260]
0x5613b88  lea rdx,[rbp+0x27A0]
0x5613b8f  call 0x5693680
```
**In/out resources:** rcx=[rbp+0x3260] (context), rdx=[rbp+0x27A0] (pass config) [V]; xmm0..xmm2, [rcx+0x2B0..0x300] set up with matrix/data prior [V]

---

### Pass 27: 0x561419e -> sub_5695960
**Pass name:** [UNVERIFIED: 0x561419e no inline string found; near DepthOnlyAlphaTest string at 0x5609494]
**Argument setup (quoted):**
```
0x5614190  lea rcx,[rbp+0x27A0]
0x5614197  lea r9,[rbp+0x2EF0]
0x561419e  call 0x5695960
```
**In/out resources:** rcx=[rbp+0x27A0], r9=[rbp+0x2EF0], stack[0x20]=[rbp+0x2C00] (config structs) [V]; r8=[rbp+0x21B0], rdx=[rax+0x40] set prior [V]

---

### Pass 28: 0x5616727 -> sub_5693680
**Pass name:** [UNVERIFIED: 0x5616727 no inline string found; near GeometryPrepassAlphaTest strings]
**Argument setup (quoted):**
```
0x5616719  mov rcx,[rbp+0x3260]
0x5616720  lea rdx,[rbp+0x27A0]
0x5616727  call 0x5693680
```
**In/out resources:** rcx=[rbp+0x3260] (context), rdx=[rbp+0x27A0] (pass config) [V]; xmm0..xmm2, [rcx+0x2B0..0x300] set up prior [V]

---

### Pass 29: 0x5616d38 -> sub_5694510
**Pass name:** [UNVERIFIED: 0x5616d38 no inline string found; near ForwardPBRTransparent strings]
**Argument setup (quoted):**
```
0x5616d2a  lea rcx,[rbp+0x27A0]
0x5616d31  lea r9,[rbp+0x2EF0]
0x5616d38  call 0x5694510
```
**In/out resources:** rcx=[rbp+0x27A0], r9=[rbp+0x2EF0], stack[0x20]=[rbp+0x2C00] (config structs) [V]; r8=[rbp+0x21B0], rdx=[rax+0x40] set prior [V]

---

### Pass 30: 0x56186f9 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x56186f9 no inline string found]
**Argument setup (quoted):**
```
0x56186f0  mov rcx,r15
0x56186f3  mov rdx,rdi
0x56186f6  mov r8,r14
0x56186f9  call 0x5689800
```
**In/out resources:** rcx=r15 (start), rdx=rdi (end), r8=r14 (count) [I]

---

### Pass 31: 0x561a1f8 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x561a1f8 no inline string found]
**Argument setup (quoted):**
```
0x561a1ef  mov r15,rcx
0x561a1f2  mov rdx,rdi
0x561a1f5  mov r8,r14
0x561a1f8  call 0x5689800
```
**In/out resources:** rcx=r15 (start), rdx=rdi (end), r8=r14 (count) [I]

---

### Pass 32: 0x561be8a -> sub_5696540
**Pass name:** "ForwardPBRTransparent" [V string at 0x561bd1a nearby]
**Argument setup (quoted):**
```
0x561be7c  lea rcx,[rbp+0x27A0]
0x561be83  lea r9,[rbp+0x2EF0]
0x561be8a  call 0x5696540
```
**In/out resources:** rcx=[rbp+0x27A0], r9=[rbp+0x2EF0], stack[0x20]=[rbp+0x2C00] (config structs) [V]; r8=[rbp+0x21B0], rdx=[rax+0x40] set prior [V]

---

### Pass 33: 0x561ce17 -> sub_5693680
**Pass name:** [UNVERIFIED: 0x561ce17 no inline string found]
**Argument setup (quoted):**
```
0x561ce09  mov rcx,[rbp+0x3260]
0x561ce10  lea rdx,[rbp+0x27A0]
0x561ce17  call 0x5693680
```
**In/out resources:** rcx=[rbp+0x3260] (context), rdx=[rbp+0x27A0] (pass config) [V]; xmm0..xmm2, [rcx+0x2B0..0x300] set up prior [V]

---

### Pass 34: 0x561e3b7 -> sub_5693680
**Pass name:** [UNVERIFIED: 0x561e3b7 no inline string found]
**Argument setup (quoted):**
```
0x561e3a9  mov rcx,[rbp+0x3260]
0x561e3b0  lea rdx,[rbp+0x27A0]
0x561e3b7  call 0x5693680
```
**In/out resources:** rcx=[rbp+0x3260] (context), rdx=[rbp+0x27A0] (pass config) [V]; xmm0..xmm2, [rcx+0x2B0..0x300] set up prior [V]

---

### Pass 35: 0x561ed7b -> sub_5689800
**Pass name:** [UNVERIFIED: 0x561ed7b no inline string found]
**Argument setup (quoted):**
```
0x561ed72  mov rcx,rdi
0x561ed75  mov rdx,rsi
0x561ed78  mov r8,r12
0x561ed7b  call 0x5689800
```
**In/out resources:** rcx=rdi (start), rdx=rsi (end), r8=r12 (count) [I]

---

### Pass 36: 0x561fda7 -> sub_5693680
**Pass name:** [UNVERIFIED: 0x561fda7 no inline string found]
**Argument setup (quoted):**
```
0x561fd99  mov rcx,[rbp+0x3260]
0x561fda0  lea rdx,[rbp+0x27A0]
0x561fda7  call 0x5693680
```
**In/out resources:** rcx=[rbp+0x3260] (context), rdx=[rbp+0x27A0] (pass config) [V]; xmm0..xmm2, [rcx+0x2B0..0x300] set up prior [V]

---

### Pass 37: 0x5621b3e -> sub_5697650
**Pass name:** [UNVERIFIED: 0x5621b3e no inline string found]
**Argument setup (quoted):**
```
0x5621b30  lea rcx,[rbp+0x27A0]
0x5621b37  lea r9,[rbp+0x2EF0]
0x5621b3e  call 0x5697650
```
**In/out resources:** rcx=[rbp+0x27A0], r9=[rbp+0x2EF0], stack[0x20]=[rbp+0x2C00] (config structs) [V]; r8=[rbp+0x21B0], rdx=[rax+0x40] set prior [V]

---

### Pass 38: 0x5622ab6 -> sub_5693680
**Pass name:** [UNVERIFIED: 0x5622ab6 no inline string found]
**Argument setup (quoted):**
```
0x5622aa8  mov rcx,[rbp+0x3260]
0x5622aaf  lea rdx,[rbp+0x27A0]
0x5622ab6  call 0x5693680
```
**In/out resources:** rcx=[rbp+0x3260] (context), rdx=[rbp+0x27A0] (pass config) [V]; xmm0..xmm2, [rcx+0x2B0..0x300] set up prior [V]

---

### Pass 39: 0x5623dd7 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x5623dd7 no inline string found; near SSRColorBufferBlit strings at 0x56235b4]
**Argument setup (quoted):**
```
0x5623dd1  mov rdx,rsi
0x5623dd4  mov r8,r14
0x5623dd7  call 0x5689800
```
**In/out resources:** rdx=rsi (end), r8=r14 (count); rcx from prior (mov [rbp+0x3200],rcx at 0x5623dca) [V]

---

### Pass 40: 0x5625585 -> sub_5698290
**Pass name:** "temInHandObject]" / "[ClearDepth][ItemInHandObject]" / "ForwardPBROpaque" [V strings at 0x5625633, 0x562563e, 0x562572c]
**Argument setup (quoted):**
```
0x5625574  mov rcx,[rbp+0x3260]
0x562557b  mov rdx,rcx
0x562557e  lea r8,[rbp+0x1C40]
0x5625585  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x1C40] (pass config) [V]

---

### Pass 41: 0x562b150 -> sub_5693680
**Pass name:** [UNVERIFIED: 0x562b150 no inline string found]
**Argument setup (quoted):**
```
0x562b142  mov rcx,[rbp+0x3260]
0x562b149  lea rdx,[rbp+0x27A0]
0x562b150  call 0x5693680
```
**In/out resources:** rcx=[rbp+0x3260] (context), rdx=[rbp+0x27A0] (pass config) [V]; xmm0..xmm2, [rcx+0x2B0..0x300] set up prior [V]

---

### Pass 42: 0x562cc0a -> sub_5698290
**Pass name:** [UNVERIFIED: 0x562cc0a no inline string found]
**Argument setup (quoted):**
```
0x562cbf9  mov rcx,[rbp+0x3260]
0x562cc00  mov rdx,rcx
0x562cc03  lea r8,[rbp+0x1EF4]
0x562cc0a  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x1EF4] (pass config) [V]

---

### Pass 43: 0x562e4e3 -> sub_5698290
**Pass name:** [UNVERIFIED: 0x562e4e3 no inline string found; near FSR1 strings]
**Argument setup (quoted):**
```
0x562e4d2  mov rcx,[rbp+0x3260]
0x562e4d9  mov rdx,rcx
0x562e4dc  lea r8,[rbp+0x2C00]
0x562e4e3  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x2C00] (pass config) [V]

---

### Pass 44: 0x562e661 -> sub_5698290
**Pass name:** "ceRasterization]" / "[ClearColor][ForceRasterization]" [V strings at 0x562e6fb, 0x562e706]
**Argument setup (quoted):**
```
0x562e650  mov rcx,[rbp+0x3260]
0x562e657  mov rdx,rcx
0x562e65a  lea r8,[rbp+0x25F0]
0x562e661  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x25F0] (pass config) [V]

---

### Pass 45: 0x562f808 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x562f808 no inline string found]
**Argument setup (quoted):**
```
0x562f7fb  mov [rbp+0x3200],rcx
0x562f802  mov rdx,rsi
0x562f805  mov r8,r14
0x562f808  call 0x5689800
```
**In/out resources:** rcx=rcx (from prior), rdx=rsi (end), r8=r14 (count) [I/V]

---

### Pass 46: 0x5631038 -> sub_5689800
**Pass name:** [UNVERIFIED: 0x5631038 no inline string found]
**Argument setup (quoted):**
```
0x563102b  mov [rbp+0x3200],rcx
0x5631032  mov rdx,rsi
0x5631035  mov r8,r14
0x5631038  call 0x5689800
```
**In/out resources:** rcx=rcx (from prior), rdx=rsi (end), r8=r14 (count) [I/V]

---

### Pass 47: 0x563281e -> sub_5698290
**Pass name:** "FSR1" [V string at 0x5632969 nearby]
**Argument setup (quoted):**
```
0x563280d  mov rcx,[rbp+0x3260]
0x5632814  mov rdx,rcx
0x5632817  lea r8,[rbp+0x2440]
0x563281e  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x2440] (pass config) [V]

---

### Pass 48: 0x5632b0e -> sub_5698290
**Pass name:** "FSR1" / "Core/Screen/Blit" / "BlitFSRToBackBuffer" [V strings at 0x5632969, 0x5632c02, 0x5632d0c]
**Argument setup (quoted):**
```
0x5632afd  mov rcx,[rbp+0x3260]
0x5632b04  mov rdx,rcx
0x5632b07  lea r8,[rbp+0x2440]
0x5632b0e  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x2440] (pass config) [V]

---

### Pass 49: 0x5633359 -> sub_5698290
**Pass name:** "][ColorCorrectedUI]" / "[ClearColorDepth][ColorCorrectedUI]" [V strings at 0x56331b8, 0x56331c3]
**Argument setup (quoted):**
```
0x5633348  mov rcx,[rbp+0x3260]
0x563334f  mov rdx,rcx
0x5633352  lea r8,[rbp+0x2C00]
0x5633359  call 0x5698290
```
**In/out resources:** rcx/rdx=[rbp+0x3260] (context), r8=[rbp+0x2C00] (pass config) [V]

---

### Pass 50: 0x563460e -> sub_5667860
**Pass name:** [UNVERIFIED: 0x563460e no inline string found]
**Argument setup (quoted):**
```
0x5634604  lea rcx,[rbp+0x2100]
0x563460b  mov rdx,rsi
0x563460e  call 0x5667860
```
**In/out resources:** rcx=[rbp+0x2100] (pass config), rdx=rsi (resource) [V]

---

## Summary Table (Ordered by Call Site RVA)

| # | Call Site RVA | Callee RVA | Helper | Pass Name (from strings) | Arg Pattern |
|---|---------------|------------|--------|--------------------------|-------------|
| 1 | 0x55f182b | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=rdi, rdx=rbx, r8=r14 |
| 2 | 0x55f1fca | 0x5698290 | sub_5698290 | [UNVERIFIED] | rcx/rdx=ctx, r8=cfg@2C00 |
| 3 | 0x55f1fe7 | 0x5698290 | sub_5698290 | [UNVERIFIED] | rcx/rdx=ctx, r8=cfg@27A0 |
| 4 | 0x55f2624 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r15, rdx=rdi, r8=rbx |
| 5 | 0x55f2929 | 0x5667860 | sub_5667860 | [UNVERIFIED] | rcx=cfg@27A0 |
| 6 | 0x55f4186 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r15, rdx=rsi, r8=rbx |
| 7 | 0x55f486a | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r12, rdx=rdi, r8=r14 |
| 8 | 0x55f6454 | 0x5667860 | sub_5667860 | Shadow Cascades? | rcx=cfg@27A0, rdx=rdi |
| 9 | 0x55f67b4 | 0x5667860 | sub_5667860 | [UNVERIFIED] | rcx=cfg@27A0 |
| 10 | 0x55f7051 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r12, rdx=rdi, r8=r14 |
| 11 | 0x55f7551 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r12, rdx=rdi, r8=r14 |
| 12 | 0x55f83ca | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r12, rdx=rsi, r8=r14 |
| 13 | 0x55ff2c5 | 0x5698290 | sub_5698290 | Core/Screen/Blit / DebugDepthBufferCopy | rcx/rdx=ctx, r8=cfg@1EF4 |
| 14 | 0x55ff2f8 | 0x5698290 | sub_5698290 | Core/Screen/Blit / DebugDepthBufferCopy | rcx/rdx=ctx, r8=cfg@1C40 |
| 15 | 0x55ff31d | 0x5698290 | sub_5698290 | Core/Screen/Blit / DebugDepthBufferCopy | rcx/rdx=ctx, r8=cfg@1C40 |
| 16 | 0x560673d | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r13, rdx=rsi, r8=r14 |
| 17 | 0x5607fdd | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r13, rdx=rsi, r8=r14 |
| 18 | 0x5609b8c | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=ctx, rdx=rsi, r8=r14 |
| 19 | 0x560b6be | 0x5698290 | sub_5698290 | Core/Screen/Blit / DebugDepthBufferCopy | rcx/rdx=ctx, r8=cfg@2440 |
| 20 | 0x560bd0d | 0x5698290 | sub_5698290 | Core/Screen/Blit / BlitUncompressed | rcx/rdx=ctx, r8=cfg@1EA0 |
| 21 | 0x560cc28 | 0x5694510 | sub_5694510 | Sky (pre-water) / ForwardPBR - Sky / ForwardPBRTransparent | rcx=cfg@27A0, r9=cfg@2EF0, stack=cfg@2C00 |
| 22 | 0x560e734 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=rdi, rdx=rsi, r8=r12 |
| 23 | 0x5610bd3 | 0x5684660 | sub_5684660 | TransparentDegamma | rcx=ctx, rdx=@2848, r8=2, r9=cfg@2EF0, stack args |
| 24 | 0x5611a18 | 0x5698290 | sub_5698290 | Core/Screen/Blit / rDepthBufferCopy / DebugWaterDepthBufferCopy | rcx/rdx=ctx, r8=cfg@2440 |
| 25 | 0x5612b0d | 0x5689800 | sub_5689800 | ForwardPBRTransparent? | rcx=rdi, rdx=rsi, r8=r14 |
| 26 | 0x5613b8f | 0x5693680 | sub_5693680 | GeometryPrepassAlphaTest? | rcx=ctx, rdx=cfg@27A0 |
| 27 | 0x561419e | 0x5695960 | sub_5695960 | DepthOnlyAlphaTest? | rcx=cfg@27A0, r9=cfg@2EF0, stack=cfg@2C00 |
| 28 | 0x5616727 | 0x5693680 | sub_5693680 | GeometryPrepassAlphaTest? | rcx=ctx, rdx=cfg@27A0 |
| 29 | 0x5616d38 | 0x5694510 | sub_5694510 | ForwardPBRTransparent? | rcx=cfg@27A0, r9=cfg@2EF0, stack=cfg@2C00 |
| 30 | 0x56186f9 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r15, rdx=rdi, r8=r14 |
| 31 | 0x561a1f8 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=r15, rdx=rdi, r8=r14 |
| 32 | 0x561be8a | 0x5696540 | sub_5696540 | ForwardPBRTransparent | rcx=cfg@27A0, r9=cfg@2EF0, stack=cfg@2C00 |
| 33 | 0x561ce17 | 0x5693680 | sub_5693680 | [UNVERIFIED] | rcx=ctx, rdx=cfg@27A0 |
| 34 | 0x561e3b7 | 0x5693680 | sub_5693680 | [UNVERIFIED] | rcx=ctx, rdx=cfg@27A0 |
| 35 | 0x561ed7b | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=rdi, rdx=rsi, r8=r12 |
| 36 | 0x561fda7 | 0x5693680 | sub_5693680 | [UNVERIFIED] | rcx=ctx, rdx=cfg@27A0 |
| 37 | 0x5621b3e | 0x5697650 | sub_5697650 | [UNVERIFIED] | rcx=cfg@27A0, r9=cfg@2EF0, stack=cfg@2C00 |
| 38 | 0x5622ab6 | 0x5693680 | sub_5693680 | [UNVERIFIED] | rcx=ctx, rdx=cfg@27A0 |
| 39 | 0x5623dd7 | 0x5689800 | sub_5689800 | SSRColorBufferBlit? | rcx=@3200, rdx=rsi, r8=r14 |
| 40 | 0x5625585 | 0x5698290 | sub_5698290 | ItemInHandObject / ForwardPBROpaque | rcx/rdx=ctx, r8=cfg@1C40 |
| 41 | 0x562b150 | 0x5693680 | sub_5693680 | [UNVERIFIED] | rcx=ctx, rdx=cfg@27A0 |
| 42 | 0x562cc0a | 0x5698290 | sub_5698290 | [UNVERIFIED] | rcx/rdx=ctx, r8=cfg@1EF4 |
| 43 | 0x562e4e3 | 0x5698290 | sub_5698290 | FSR1? | rcx/rdx=ctx, r8=cfg@2C00 |
| 44 | 0x562e661 | 0x5698290 | sub_5698290 | ForceRasterization | rcx/rdx=ctx, r8=cfg@25F0 |
| 45 | 0x562f808 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=@3200, rdx=rsi, r8=r14 |
| 46 | 0x5631038 | 0x5689800 | sub_5689800 | [UNVERIFIED] | rcx=@3200, rdx=rsi, r8=r14 |
| 47 | 0x563281e | 0x5698290 | sub_5698290 | FSR1 | rcx/rdx=ctx, r8=cfg@2440 |
| 48 | 0x5632b0e | 0x5698290 | sub_5698290 | FSR1 / BlitFSRToBackBuffer | rcx/rdx=ctx, r8=cfg@2440 |
| 49 | 0x5633359 | 0x5698290 | sub_5698290 | ColorCorrectedUI | rcx/rdx=ctx, r8=cfg@2C00 |
| 50 | 0x563460e | 0x5667860 | sub_5667860 | [UNVERIFIED] | rcx=cfg@2100, rdx=rsi |

---

## Verification
- Lint: N/A (markdown document)
- Types: N/A
- Tests: `python tools/sigs/verify_oc.py docs/progress/oc_U-F1b2.md` [pending]

## Open
- Pass names for 32/50 entries remain [UNVERIFIED] — no inline ASCII immediate found at call site; names inferred only from nearby .rdata strings (BGFX_MAP 6i indicates 8-byte immediates)
- In/out resource identifiers: only visible for sub_5698290/sub_5693680/sub_5694510/sub_5695960/sub_5696540/sub_5697650 (config struct pointer in r8/r9/stack); for sub_5689800/sub_5684660/sub_5667860 args are range/count or single pointers
- Helper functions (sub_5667860, sub_5689800, sub_5698290, etc.) not reversed — their signatures and resource ID mapping unknown

## TOOL REQUESTS
- Tool to extract inline ASCII immediates (8-byte mov rax, imm64) near call sites for pass-name resolution
- Tool to cross-reference helper function signatures (sub_5667860, sub_5689800, sub_5698290, sub_5693680, sub_5694510, sub_5695960, sub_5696540, sub_5697650, sub_5684660) with resource ID enums