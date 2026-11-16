# UNIT U-B7c — D3D12 upload tracking lists (0x48/0x18 entries at ctx +0x1A000 / +0x1A018), slots 55/56/57

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Header named in unit: src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h

## NEXT
Resume at: none — unit complete; run `python tools/sigs/verify_oc.py docs/progress/oc_U-B7c.md` then finalize.

## (1) Anchor RVAs and sizes (from docs/BGFX_MAP.md 6ba/6bb/6az)

Located via `grep -n 'slot 5[567]\|0x1A000\|0x1A018' docs/BGFX_MAP.md`:

| Slot | RVA | Size | Identification | Source | Tag |
|------|-----|------|----------------|--------|-----|
| 55 | 0xe8165a0 | 0x99c | upload/update of buffers via ring; writes 0x48-entry list +0x38 handle; references 0x93A178 | BGFX_MAP.md L661; rdis fn [V] | [V] |
| 56 | 0xe817070 | 0x5e2 | readback/fence; uses this+0x19FE0/0x19FE8/0x19FF0; same 0x57A178 table | BGFX_MAP.md L662; rdis fn [V] | [V] |
| 57 | 0xe816f40 | 0x130 | destroy of indexed 0x78-byte record; erases from 0x48 list at +0x1A000, retires 0x18 list at +0x1A018 | BGFX_MAP.md L663/L795; rdis fn [V] | [V] |

`rdis fn` outputs:
- `sub_e8165a0  [0xe8165a0..0xe816f3c)  size 0x99c  1 xrefs in` [V]
- `sub_e817070  [0xe817070..0xe817652)  size 0x5e2  0 xrefs in` [V]
- `sub_e816f40  [0xe816f40..0xe817070)  size 0x130  0 xrefs in` [V]

Canonical D3D12 vtable slot indices for 55/56/57 are Mojang extras not in stock RendererContextI — not re-derived here. [UNVERIFIED: canonical vtable slot index for slots 55/56/57 beyond byte offsets 0x1A000/0x19FE0/0x1A000 context offsets]

## (2) Context fields used by all three slots (read map)

| Context offset | Size | Slot(s) | Direction | Evidence (RVA) | Tag |
|----------------|------|---------|-----------|----------------|-----|
| +0x57A100 | qword | 55 | R (lazy-init ring resource ptr) | `cmp qword ptr [rcx+0x57A100],0` e8165c0 | [V] |
| +0x57A178 | table base | 55/56/57 | R (0x78-stride per-handle records) | `add rcx,0x57A178` e816f5a / e81688b | [V] |
| +0x19F58 | qword | 55 | R (cmd-list wrapper) | `mov rbx,[rsi+0x19F58]` e8165da | [V] |
| +0x238 | qword | 55 | R (device) | `mov r8,[rsi+0x238]` e816688 | [V] |
| +0x50 | dword | 55 | R | `mov ecx,[rsi+0x50]` e816b69 | [V] |
| +0x19FE0 | qword | 56 | R (0x18-list begin) | `mov r13,[rbx+0x19FE0]` e8172cb | [V] |
| +0x19FE8 | qword | 56 | R/W (0x18-list end) | `mov r15,[rbx+0x19FE8]` e817185 | [V] |
| +0x19FF0 | qword | 56 | R (0x18-list cap) | `cmp r15,[rbx+0x19FF0]` e81718c | [V] |
| +0x1A000 | qword | 55/57 | R/W (0x48-list begin) | `mov rbx,[rsi+0x1A000]` e816f66 | [V] |
| +0x1A008 | qword | 55/57 | R/W (0x48-list end) | `mov rdx,[rsi+0x1A008]` e816f6d | [V] |
| +0x1A010 | qword | 55 | R/W (0x48-list cap) | `mov [rsi+0x1A010],rax` e816eef | [V] |
| +0x1A018 | qword | 57 | R (0x18-list begin) | `mov rax,[rsi+0x1A018]` e81700d area (slot57 dis e816fff) | [V] |
| +0x1A020 | qword | 55/57 | R (0x18-list end) | `cmp rdx,[rsi+0x1A020]` e816c6b | [V] |
| +0x1A028 | qword | 55 | R (0x18-list cap) | `cmp rdx,[rsi+0x1A028]` e816c6b | [V] |

Vector begin/end/cap offsets inside the context (quoted): the 0x48-byte list is tracked by `[rsi+0x1A000]` begin, `[rsi+0x1A008]` end, `[rsi+0x1A010]` capacity [V e816f66/e816f6d/e816eef]. The 0x18-byte list is tracked by `[rsi+0x19FE0]` begin, `[rsi+0x19FE8]` end, `[rsi+0x19FF0]` capacity [V e8172cb/e817185/e81718c]. These grow by 0x48 and 0x18 (i.e. 0x20 bytes written per 0x18-list entry including pad) respectively [V add qword ptr [rsi+0x1A008],0x48 e816d1a / add qword ptr [rbx+0x19FE8],0x20 e8171b4].

## (3) Slot 55 — upload path (0xe8165a0, size 0x99c) — push logic

Lazy first-use init (runs when `[ctx+0x57A100]==0`): allocates 0x2FFF4-byte upload resource via `0xe812740` (e8166c8), builds a pool of 0x18-byte entries as a free list linking each entry to the next 4 positions ahead (entries indexed r9 step 8, size 0x18, ending at index 0xFFF8 — i.e. 8192 entries x 0x18 ≈ 0x2FFF4) via stores [rcx], [rcx+2], [rcx+0xA], [rcx+0xC], [rcx+0xE], [rcx+0x16] (e816630/e816642/e816647/e816659/e81666a/e81666f) [V]. Then registers a mapped range via cmd-list wrapper vtable +0xD0 (e816701/e816712) and `0xe8360f0(device+8, desc, 0x2FFF4, 0x10)` (e816734) [V]. The `this+0x57A100` upload ring becomes the destination; per-handle 0x78 records live at `ctx+0x57A178` [V].

Per-call copy path (from loc_e81684b): reads caller-spill args at `[rsp+0x1A0]` (handle hi), `[rsp+0x198]`, `[rsp+0x188]` (count?), `[rsp+0x180]` (handle lo r11w), `[rsp+0x170]` (ebx = byte count), `[rsp+0x190]` (dst offset) [V e81684b-86e]. Computes record ptr `ctx + r8w*0x80` then `+0x93A178` (vertex/index table select by `cmp cx,0xFFFF cmove`) e816875-893 [V]. Writes the per-handle 0x78 record at `ctx+0x93A178 + handle*0x78`: +0x60=eax, +0x64=0x200, +0x66=1, +0x70=1 (e816a68/a6b/a71/a75) [V]. Then `imul rax,rdi,0x34; lea r12,[rsi+rax+0x3DA100]` (e816a1d/a21) and builds a D3D12 range/copy desc on stack [rsp+0x50..0xE8], calls cmd-list wrapper vtable +0x1F8 (e816a00/a17) [V]. Copies via `sub_e815590` (e816aaf) [V].

Then appends a 0x48-byte tracking entry at `ctx+0x1A008` (end pointer): fields written (all from stack/build area):
- `+0x00` = ax (handle lo) `mov [r12],ax` e816b7f [V]
- `+0x02` = ax `mov [r12+2],ax` e816b89 [V]
- `+0x04` = bp `mov [r12+4],bp` e816b8f [V]
- `+0x06` = ax `mov [r12+6],ax` e816b9d [V]
- `+0x08` = eax `mov [r12+8],eax` e816baa [V]
- `+0x0C` = eax `mov [r12+0xC],eax` e816bba [V]
- `+0x10` = eax `mov [r12+0x10],eax` e816bd3 [V]
- `+0x14` = r15d `mov [r12+0x14],r15d` e816bd8 [V]
- `+0x18` = eax `mov [r12+0x18],eax` e816be8 [V]
- `+0x1C` = r13w `mov [r12+0x1C],r13w` e816bed [V]
- `+0x20` = ecx `mov [r12+0x20],ecx` e816b6c [V]
- `+0x24` = ecx `mov [r12+0x24],ecx` e816bfc [V]
- `+0x28` = 0xFFFFFFFF `mov dword ptr [r12+0x28],0xFFFFFFFF` e816b71 [V]
- `+0x2C` = ax `mov [r12+0x2C],ax` e816c0f [V]
- `+0x2E` = 0xFFFFFFFF `mov dword ptr [r12+0x2E],0xFFFFFFFF` e816bf3 [V]
- `+0x32` = byte OR 1 `or byte ptr [r12+0x32],1` e816c01 [V]
- `+0x40` = rax `mov [rdi+0x40],rax` e816cec [V]
Plus xmm block copies at `+0x00,+0x10,+0x20,+0x30` (movdqu/movups 16 bytes each) e816d16/d11/d0d/d09 [V].
The entry handle (key for slot 57 erase) is at `entry+0x38` per BGFX_MAP 6ba [I from 6ba text; +0x38 not directly written in slot 55 body scanned — see OPEN].
After writing the entry: `add qword ptr [rsi+0x1A008],0x48` e816d1a [V] (end += 0x48).

Separately appends a 0x18-byte entry at `ctx+0x1A020` (end of 0x18 list): `mov [rdx+0x10],rax` e816c7c; `movdqu [rdx],xmm0` e816c89; `add qword ptr [rsi+0x1A020],0x18` e816c8d [V]. If list full (`end==cap`, e816c72) calls `sub_1195A0` (e816cc0) to grow/realloc [V].

Full-field read map via descscan2 `--reg rsi` on 0xe8165a0..0xe816f3c: reads +0x050 (e816b69) and +0x238 (e816688) only [V descscan output docs/progress/oc_U-B7c_descscan_s55.txt]. All other field writes target the 0x48-entry (r12), 0x78-record (rbx), 0x18-entry (rdx) temporaries, not the context base [V].

## (4) Slot 57 — destroy path (0xe816f40, size 0x130)

Signature `(this=rcx=rsi, handle=edx=edi)` [V e816f4b]. Runs record destructor `0xe80ef60(ctx + handle*0x78 + 0x57A178)`:
```
e816f4b  mov edi,edx                                    ; edi = handle
e816f50  movzx eax,dx                                   ; eax = handle (u16)
e816f53  imul r15,rax,0x78                              ; r15 = handle*0x78
e816f57  add rcx,r15                                    ; rcx = ctx + handle*0x78
e816f5a  add rcx,0x57A178                               ; rcx = &record
e816f61  call 0xE80EF60                                 ; record destructor
```
Then erases handle from the 0x48-byte list at `ctx+0x1A000` (begin rbx, end rdx):
```
e816f66  mov rbx,[rsi+0x1A000]                          ; rbx = list begin
e816f6d  mov rdx,[rsi+0x1A008]                          ; rdx = list end
e816f74  cmp rbx,rdx
e816f77  je short 0xE816F8F                             ; empty -> skip erase
e816f80  cmp [rbx+0x38],di                              ; entry->+0x38 == handle?
e816f84  je short 0xE816F8F                             ; found -> erase
e816f86  add rbx,0x48                                   ; advance to next entry
e816f8a  cmp rbx,rdx
e816f8d  jne short 0xE816F80
```
Erase by shifting (memmove down by 0x48): copies 4 xmmword blocks `[rax+0x0,0x10,0x20,0x30]` -> `[rbx+0x0,0x10,0x20,0x30]` then `add rbx,0x48`; loop `e816fa0` [V]. Finally `mov r14,[rsi+0x1A008]; sub r14,rdx; ... call 0xEEC6DE0; mov [rsi+0x1A008],r14` (end -= removed, memmove tail) e816fe0/e816ff8 [V]. On the realloc path (slot 55's full-list path `loc_e816cc0` -> `sub_1195A0`), begin/cap updated: `mov [rsi+0x1A000],r14` e816eca; `mov [rsi+0x1A008],rax` e816ee0; `mov [rsi+0x1A010],rax` e816eef [V] (these are in slot 55 body but shared list metadata).

Then the 0x18-byte list at `ctx+0x1A018` (begin rax, end rcx): find entry where `[entry+4]==handle`:
```
e817020  cmp [rax+4],di                                 ; entry->+4 == handle?
e817024  je short 0xE817031
e817026  add rax,0x18
e81702a  cmp rax,rcx
e81702d  jne short 0xE817020
```
On match: `mov dword ptr [rax],4` e817031 — sets state dword to 4 = "retire" instead of erase [V]. Then `jmp 0xE80EF60` via tail at e817055/0x57A178+handle region [V].

Field reads/writes on entries [V stores]:
- 0x48 entry: reads `+0x38` (handle key) e816f80/e816fa9; writes `+0x00,+0x10,+0x20,+0x30,+0x40` during shift e816fd2/fce/fca/fb3 [V].
- 0x18 entry: reads `+4` e817020; writes `+0` = 4 (state retire) e817031 [V].

## (5) Slot 56 — copy path / readback fence (0xe817070, size 0x5e2)

Signature `(this=rcx=rbx, handle=edx=r12d, size=r8d=edi, userptr=r9)` [V e81709e/09b/097]. Pushes a 0x18-byte entry onto the ring at `ctx+0x19FE8` (end), growing end by 0x20:
```
e817185  mov r15,[rbx+0x19FE8]                          ; r15 = end
e81718c  cmp r15,[rbx+0x19FF0]                          ; end == cap? full?
e817193  je short 0xE8171C1
e817195  mov [r15],r12w                                 ; entry+0 = handle (u16)
e817199  xorps xmm0,xmm0
e81719c  movups [r14],xmm0                              ; zero entry+0..0xF
e8171a0  mov qword ptr [r14+0x10],0                     ; entry+0x10 = 0
e8171a8  mov [r15+8],r13                                ; entry+8 = alloc ptr
e8171ac  mov [r15+0x10],rsi                             ; entry+0x10 = size (rsi)
e8171b0  mov [r15+0x18],rsi                             ; entry+0x18 = size (dup)
e8171b4  add qword ptr [rbx+0x19FE8],0x20               ; end += 0x20
```
0x18-entry fields: +0x00 handle(u16), +0x08 alloc ptr(qword), +0x10 size(qword), +0x18 size(qword dup) [V]. When full (end==cap), grows via allocator path at loc_e8171C1..e8172a1 and then re-enters the push at e8172a1 (`mov [r12+r14],ax` etc.) [V]. Uses `sub_eec6ed0`/`sub_eec6ec0` (aligned alloc) e817153/e817180 [V].

After push, processes the ring: walks entries `r13=[rbx+0x19FE0]` to `r15=[rbx+0x19FE8]` step 0x20, for each: `movzx ecx,word ptr [r13+rax]` (handle), `mov [r12+rax],cx` (copy handle to new ring), `mov rcx,[r13+rax+0x18]; mov [r13+rax+0x18],0` (clear +0x18 fence/size), `movups` move +8..+0x17, `mov [r12+rax+0x18],rcx` e8172f0-31b [V] — compaction/retire of processed entries. Finally updates ring pointers:
```
e8174b2  mov [rbx+0x19FE0],r12                          ; begin = new base
e8174c4  mov [rbx+0x19FE8],rax                          ; end = new end
e8174d2  mov [rbx+0x19FF0],rax                          ; cap = new cap
```
Record write at `ctx+0x57A178 + handle*0x78` (loc_e817518): +0x60=0x2000000, +0x64=0x200, +0x66=1, +0x70=1, +0x00=rax, +0x58=rdx, +0x08=r8(0xB00000000), +0x10=0x1688, +0x18=rdx e817523/52a/530/534/581/588/599/59d/5a4 [V].

## (6) Entry layouts — EVERY field read/written

### 0x48-byte entry (in-flight/upload tracking list, ctx+0x1A000)

| Offset | Size | Direction | Meaning | Evidence | Tag |
|--------|------|-----------|---------|----------|-----|
| +0x00 | u16 | W | handle lo | `mov [r12],ax` e816b7f | [V] |
| +0x02 | u16 | W | handle hi | `mov [r12+2],ax` e816b89 | [V] |
| +0x04 | u16 | W | bp (arg) | `mov [r12+4],bp` e816b8f | [?] |
| +0x06 | u16 | W | ax | `mov [r12+6],ax` e816b9d | [?] |
| +0x08 | u32 | W | eax | `mov [r12+8],eax` e816baa | [?] |
| +0x0C | u32 | W | eax | `mov [r12+0xC],eax` e816bba | [?] |
| +0x10 | u32 | W | eax | `mov [r12+0x10],eax` e816bd3 | [?] |
| +0x14 | u32 | W | r15d | `mov [r12+0x14],r15d` e816bd8 | [?] |
| +0x18 | u32 | W | eax | `mov [r12+0x18],eax` e816be8 | [?] |
| +0x1C | u16 | W | r13w | `mov [r12+0x1C],r13w` e816bed | [?] |
| +0x20 | u32 | W | ecx | `mov [r12+0x20],ecx` e816b6c | [?] |
| +0x24 | u32 | W | ecx | `mov [r12+0x24],ecx` e816bfc | [?] |
| +0x28 | u32 | W | 0xFFFFFFFF | `mov dword ptr [r12+0x28],0xFFFFFFFF` e816b71 | [V] |
| +0x2C | u16 | W | ax | `mov [r12+0x2C],ax` e816c0f | [?] |
| +0x2E | u32 | W | 0xFFFFFFFF | `mov dword ptr [r12+0x2E],0xFFFFFFFF` e816bf3 | [V] |
| +0x32 | u8 | W/R | OR 1 flag; key `+0x38` read by slot 57 | `or byte ptr [r12+0x32],1` e816c01 | [V] |
| +0x38 | u16 | R | handle key (slot 57 erase match) | `cmp [rbx+0x38],di` e816f80 | [V] |
| +0x40 | u64 | W | rax (copy src) | `mov [rdi+0x40],rax` e816cec | [V] |
| +0x00,+0x10,+0x20,+0x30 | 16B each | W | xmm block copy | e816d16/d11/d0d/d09 | [V] |

Field semantics for offsets without an immediate meaning are [?] — not determined from the body alone; only slot-57 key `+0x38` and sentinel `+0x28/+0x2E=0xFFFFFFFF` are pinned.

### 0x18-byte entry (readback/fence ring, ctx+0x19FE8)

| Offset | Size | Direction | Meaning | Evidence | Tag |
|--------|------|-----------|---------|----------|-----|
| +0x00 | u16 | W | handle | `mov [r15],r12w` e817195 | [V] |
| +0x08 | qword | W | alloc ptr | `mov [r15+8],r13` e8171a8 | [V] |
| +0x10 | qword | W | size | `mov [r15+0x10],rsi` e8171ac | [V] |
| +0x18 | qword | W | size dup / fence | `mov [r15+0x18],rsi` e8171b0; cleared to 0 `mov [r13+rax+0x18],0` e817300 | [V] |
| +0x00..+0x0F | 16B | W | zeroed | `movups [r14],xmm0` e81719c | [V] |

## (7) Push/pop/erase logic — vector begin/end/cap offsets (quoted)

0x48-list (ctx+0x1A000 begin / +0x1A008 end / +0x1A010 cap):
- Push: `add qword ptr [rsi+0x1A008],0x48` e816d1a [V] (end += 0x48).
- Full-check: `cmp rdi,[rsi+0x1A008]` vs `cmp rdi,[rsi+0x1A010]` e816cdb/ce2 [V] (end vs cap) -> if full call `sub_1195A0` e816cc0 [V].
- Erase (slot 57): scan `cmp [rbx+0x38],di` e816f80; shift `movups` blocks +0x48 e816faf-fd5; `mov [rsi+0x1A008],r14` e816ff8 (end -= delta) [V].
- Realloc (shared with slot 55 full path): `mov [rsi+0x1A000],r14` e816eca; `mov [rsi+0x1A008],rax` e816ee0; `mov [rsi+0x1A010],rax` e816eef [V].

0x18-list (ctx+0x19FE0 begin / +0x19FE8 end / +0x19FF0 cap):
- Push: `add qword ptr [rbx+0x19FE8],0x20` e8171b4 [V] (end += 0x20).
- Full-check: `cmp r15,[rbx+0x19FF0]` e81718c [V] -> grow path loc_e8171C1.
- Retire (slot 57): `mov dword ptr [rax],4` e817031 [V] (state=4 retire, no erase).
- Ring reset/compact: `mov [rbx+0x19FE0],r12` e8174b2; `mov [rbx+0x19FE8],rax` e8174c4; `mov [rbx+0x19FF0],rax` e8174d2 [V].

## (8) Verification artifacts
- docs/progress/oc_U-B7c_s55.txt — dumplist 0xe8165a0..0xe816f3c
- docs/progress/oc_U-B7c_s56.txt — dumplist 0xe817070..0xe817652
- docs/progress/oc_U-B7c_s57.txt — dumplist 0xe816f40..0xe817070
- docs/progress/oc_U-B7c_s55_stores.txt / s56_stores.txt / s57_stores.txt — stores.py output
- docs/progress/oc_U-B7c_descscan_s55.txt — descscan2 --reg rsi (ctx reads +0x50/+0x238 only)
- docs/progress/pre/0xe8165a0.md — preflight (already existed)

Open questions / UNVERIFIED:
- [UNVERIFIED: 0xe8165a0] exact field semantics of 0x48-entry offsets +0x04/+0x06/+0x08/+0x0C/+0x10/+0x14/+0x18/+0x1C/+0x20/+0x24/+0x2C (written but meaning not pinned by immediates).
- [UNVERIFIED: 0xe8165a0] whether +0x38 handle is written by slot 55 (key used by slot 57 at e816f80; +0x38 not seen written in slot 55 body — may be written by caller or another path).
- [UNVERIFIED] canonical vtable slot indices for 55/56/57 (Mojang extras; context offsets 0x1A000/0x19FE0/0x1A000 observed directly).
- [UNVERIFIED: 0xe816c7c/0xe816c89] 0x18-list entry at +0x1A020 fields beyond +0x00/+0x10 written by slot 55.

## TOOL REQUESTS
None | — | All field offsets gathered via rdis dis + stores.py + descscan2; no custom script needed.

## DONE
Unit U-B7c complete. Files: docs/progress/oc_U-B7c.md (full dossier), docs/progress/oc_U-B7c_header.h (static_asserts), docs/progress/oc_U-B7c_s55/s56/s57.txt (+stores +descscan) listings. verify_oc.py: 34/34 quoted instructions match.
