## NEXT
DONE

# Unit U-EL1q — Record table field layouts (checklist L1q pending part: 0x130 framebuffer-texture record)

Goal (checklist L1q): decode field layouts of the 0x78/0x80/0x130/0x68 record tables. Texture 0xB8 [V]; shader 0xB8 @+0xAAA178 and program 0xF8 @+0xB62178 done per 6au — not this unit. Done previously (oc_U-EL1q_r1.md .. r7.md): 0x78 index-buffer records at renderer+0x93A178 [V], 0x80 vertex-buffer records at renderer+0x9B2178 [V], 0x68 framebuffer-window records at renderer+0xC97698 [V] (128 entries) — those three layouts are complete and are not re-derived here.

Scope of this file: only the pending part — the 0x130 framebuffer-texture record whose pointer is held in the guard slot at ctx+0xA32178+handle*0x78 (createFrameBuffer 0xe816380). Fields +0x01..+0x12F to decode. Records are separate allocations from sub_e8360f0 (bump arena ctx+0x238+8, align 0x10); record size 0x130 per checklist L1q. ctx = renderer-context base = qword at [0x12BB4910] [V live]. All RVAs image-relative. Instruction quotes verbatim from rdis `dis` of docs/progress/pre/_tmp_el1q_*.txt (read fully, not regenerated). Meaning column: '-' unless an instruction/string shows it; live values are observations for one instance, not proof of constants. Tags: [V] = seen in disassembly (RVA cited); [V live] = livemem observation, exact command cited; [?] = not provable from available evidence (no instruction touches the offset).

Stride resolution (0xA32178): the table at ctx+0xA32178 is a 0x78-stride GUARD-SLOT array (createFrameBuffer `0xe816396  imul rbp,rcx,0x78` / `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0`; destroyer `0xe816583  imul rax,0x78` / `0xe81658a  add rcx,0xA32178`), slot+0x00 holds the record pointer qword. The 0x130-byte records themselves are bump-allocated (not table-contiguous) — confirmed live: 3 records in one instance were 0x2730 bytes apart and in different heap segments. BGFX_MAP.md line 543's "0xa32178 (0x130-byte stride)" is base-spacing arithmetic from the slot-59 shutdown loop ([I]); line 1521's "0xA32178 | 0x78 | 4096 | slots 36, 37 (create) and 38 ... | frame buffers" and line 721's executor bind at 0xe824991 (table at this+0xA32178, stride 0x78, slot+0x00 = record pointer) agree: 0x78 guard slots, 0x130 records.

## New angles tried and failed (RETRY #3)

(a) Preceding attempts r1-r7 (not redone): other callers via rdis `xr`/`callers` — createFrameBuffer 0xe816380 is vtable-dispatched, stored at entries 0xF4ED3F8 (base vtable 0xF4ED2D0 slot 37) and 0xF4EEFA8 (RTX vtable 0xF4EEE80 slot 37); callers use indirect `call qword ptr [reg+0x128]`, unenumerable by xr/callers; descscan2.py broken (TypeError); rdis `rw`/`struct` N/A (plain data struct); vt/vcalls N/A (no vtable/virtual calls in the record); static writers for record bytes +0x01..+0x12F: none — createFrameBuffer reads record+0x00/+0x10/+0x1C and performs ONE bulk copy to an unresolved external destination, writes NO record byte; destroyer sub_e80ef60 touches only guard-slot fields; sub_e92a8f0 reads slot-resource object fields; imm scan for table base 0xA32178: 2 hits only (destroy stub e815fc0 `add rcx,0xA32178`, createFrameBuffer e816380 `add rdi,0xA32178`); executor bind-handler 0xe824991 reads the record pointer from the guard-slot table and stores it at executor_local+0xC8, then passes it to sub_eea6040 — it does NOT write record fields.

(b) NEW this attempt — exhaustive caller scan for createFrameBuffer (vtable slot 37, displacement 0x128):
- `rdis ptr 0xe816380` → only 2 data slots: 0xF4ED3F8 (.rdata) and 0xF4EEFA8 (.rdata); no other data reference to the function.
- Scan of .text for `call qword ptr [reg+0x128]` (all regs, REX forms included): exactly 2 sites — 0xEC6D71D (func 0xEC6D520, WebRTC-object vcall) and 0xECD0EBA (func 0xECD0E90, iterates element sub-objects calling [[vtable+0x18]+0x128]); neither passes ctx or touches framebuffer records.
- Scan for direct `call 0xe816380` (E8 rel32): 0 sites. Scan for `jmp qword ptr [reg+0x128]`: 0 sites.
→ createFrameBuffer has NO call site inside Minecraft.Windows.exe; its runtime caller (stores the record pointer into guard slot [ctx+0xA32178+handle*0x78]+0x00 and initializes record fields) lives outside this executable (another module), so its writes are not statically available here.

(c) Orchestrator-hint livemem reads (read-only; game pid 18956 running, I did not start it):
- `python tools/sigs/livemem.py status` → pid 18956, base 0x7ff699000000, version OK 1.26.62.01.
- `python tools/sigs/livemem.py ptr @0x12BB4910 1` → +0x0  0x000005314A010000  ptr (ctx; same heap base as r4/r5 — the game was NOT restarted).
- `python tools/sigs/livemem.py read 0x5314AA32178 0x180` (ctx+0xA32178, guard slots 0-7, stride 0x78) → ALL ZEROS.
- `python tools/sigs/livemem.py read 0x5314AA32538 0x400` (guard slots 8-15) → ALL ZEROS.
→ No live framebuffer-texture record exists in this instance right now; the hint's planned reads of 2-3 records at stride 0x130 cannot execute. r4's three record snapshots from the same pid (records then at p0=0x172B581F0, p1=0x172B55AC0, p2=0x1B62E37F0 via `python tools/sigs/livemem.py read <addr> 0x130`) are stale — the guard slots that held them are now zero. Kept below as [V live] observations (that instance only, not constants), not as a closure path.

## PROVEN [V] — createFrameBuffer 0xe816380 (verbatim from _tmp_el1q_createfb.txt)

- `0xe816390  mov rdi,rcx` — rdi = this = renderer object = ctx = qword at [0x12BB4910].
- `0xe816393  movzx ecx,dx` / `0xe816396  imul rbp,rcx,0x78` / `0xe81639a  cmp qword ptr [rdi+rbp+0xA32178],0` / `0xe8163a3  je 0xE816567` — guard slot at ctx+0xA32178+handle*0x78; if slot+0x00 (record pointer) is 0 the function returns (create runs only on an occupied slot).
- `0xe81648f  mov r14,[r9]` — source r14 = qword at [r9] (createFrameBuffer arg 4 = caller's buffer pointer); null-checked `0xe816521  test r14,r14` / `0xe816524  je short 0xE816534` — copy skipped when source NULL.
- `0xe816492  mov ebx,[r9+8]` then `0xe81652c  mov r8,rbx` — size rbx = dword at [r9+8], zero-extended into r8 (runtime block byte count; the caller is unlocatable, see angle (b), so the size is unobservable statically).
- `0xe8164bb  call 0xE8360F0` (rcx=[rdi+0x238]+8 arena object, rdx=&[rsp+0x48] out-param, r8=rbx=[r9+8] size, r9d=0x10 align) — sub_e8360f0 bump-allocates [r9+8] bytes aligned 0x10 and stores the allocated pointer at out-param+0x00 (`0xe836308  mov [rsi],rcx`); hence `0xe8164c4  mov rax,[rsp+0x48]` loads rax = RECORD POINTER. The allocator writes only its out-param stack block; no located instruction writes any byte of the allocated record itself.
- `0xe8164c0  mov esi,[rsp+0x58]` — esi = dword at [rsp+0x58], allocator-provided runtime value ([rsp+0x58] = out-param+0x10, the allocator's block info; runtime, not a constant).
- Record field reads on the fresh record (rax = record ptr):
  - `0xe8164dc  mov r15,[rax]` — qword read at record+0x00; r15 passed as r9 to device call `0xe81654f  mov rax,[rax+0x78]` / `0xe816560  call qword ptr [0xF99FFA0]`; role of +0x00 not shown by any instruction.
  - `0xe8164ce  mov rcx,[rax+0x10]` — qword read at record+0x10; memcpy-destination base component (`0xe8164d2  add rcx,rsi`).
  - `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` — dword type tag compared against 2; r12 = (record+0x1C==2) ? record+0x10+rsi : 0.
- `0xe816517  add rdi,rbp` / `0xe81651a  add rdi,0xA32178` / `0xe816534  mov rdx,[rdi]` — creator re-reads guard slot [ctx+0xA32178+handle*0x78]+0x00 to get the record pointer back.
- `0xe816526  mov rcx,r12` / `0xe816529  mov rdx,r14` / `0xe81652c  mov r8,rbx` / `0xe81652f  call 0xEEC6EC0` — import-thunk memcpy/memmove: 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` (rcx=dst rdx=src r8=size per orchestrator hint; thunk target not chased). Copies [r9+8] bytes from [r9] into dst r12 — an EXTERNAL address (record+0x10 + allocator block-info when record+0x1C==2, else 0), NOT a fixed record offset and NOT a record-field store; path inert when record+0x1C==0 (all live instances) and skipped when r14==0.
- No store of the record pointer into the guard slot appears in the createFrameBuffer listing; the slot write is done by the indirect caller after the call returns (caller unlocatable, see angle (b)). No other located function reads or writes any record byte: sub_e80ef60 touches only guard-slot fields (+0x00 record ptr, +0x0C type tag vs 0xB, +0x58 slot resource released via sub_e92a8f0, +0x5F, +0x68 clears — all SLOT fields); executor 0xe824991 only copies the record pointer (`0xe824991  imul rax,rdi,0x78` / `0xe824995  mov rcx,[rbx+0x3A0]` / `0xe82499c  lea r14,[rcx+rax]` / `0xe824a07  mov rax,[rcx+rax]` / `0xe824a16  mov [rbx+c8],rax`); sub_e92a8f0 reads slot-resource object fields ([rsi+0x7C], [rsi+0x128], [rsi+0x178], [rsi+0x180], [rsi+0xC8], [rsi+0xD8]…).

## Field table — 0x130 framebuffer-texture record (record pointer held at guard slot [ctx+0xA32178+handle*0x78]+0x00)

| name | offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag |
|------|--------|------|------|-------------------------------|---------|-----|
| framebuffer-texture record +0x00 | +0x00 | 8 | createFrameBuffer 0xe816380 (rax = record ptr = sub_e8360f0 out-param [rsp+0x48]) | `0xe8164dc  mov r15,[rax]` | qword read at record+0x00; r15 passed as r9 to device call `0xe81654f  mov rax,[rax+0x78]` / `0xe816560  call qword ptr [0xF99FFA0]`; live: 0x000007FBA1D2E100 stable shared ptr across r4's 3 snapshots; role of +0x00 not shown by any instruction | [V] |
| framebuffer-texture record +0x10 | +0x10 | 8 | createFrameBuffer 0xe816380 | `0xe8164ce  mov rcx,[rax+0x10]` | qword read at record+0x10; used as memcpy-destination base component (`0xe8164d2  add rcx,rsi`, r12 = record+0x10+rsi when record+0x1C==2); live: 0 in all 3 r4 snapshots | [V] |
| framebuffer-texture record +0x1C | +0x1C | 4 | createFrameBuffer 0xe816380 | `0xe8164d8  cmp dword ptr [rax+0x1C],2` / `0xe8164df  cmove r12,rcx` | dword type tag compared against 2; selects memcpy path r12 = record+0x10+rsi else 0; live: 0 in all 3 r4 snapshots (copy path inert) | [V] |
| framebuffer-texture record +0x20 | +0x20 | 8 | livemem read (r4, stale instance) | — | qword 0x000007FBA1D2E0D8 stable shared ptr across 3 snapshots (`read 0x172B581F0 0x130` / `read 0x172B55AC0 0x130` / `read 0x1B62E37F0 0x130`); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x40 | +0x40 | 4 | livemem read (r4, stale instance) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x48 | +0x48 | 4 | livemem read (r4, stale instance) | — | dword 2 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x50 | +0x50 | 8 | livemem read (r4, stale instance) | — | qword 0x000007FFBDB76198 stable shared ptr across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x58 | +0x58 | 4 | livemem read (r4, stale instance) | — | varies: dword 0xFFFFFFFF in rec0/rec1; 0 in rec2 (rec2 also has qword -1 at +0x60/+0x68); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x60 | +0x60 | 8 | livemem read (r4, stale instance) | — | varies: 0 in rec0/rec1; qword 0xFFFFFFFFFFFFFFFF in rec2; no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x68 | +0x68 | 8 | livemem read (r4, stale instance) | — | varies: 0 in rec0/rec1; qword 0xFFFFFFFFFFFFFFFF in rec2; no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xA0 | +0xA0 | 8 | livemem read (r4, stale instance) | — | varies (near-record pointer: p0-0x30, p1+0x70, p2-0x30); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xA8 | +0xA8 | 8 | livemem read (r4, stale instance) | — | qword 0x000000000653A400 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xB0 | +0xB0 | 8 | livemem read (r4, stale instance) | — | qword = record's own address (self pointer) in all 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xB8 | +0xB8 | 4 | livemem read (r4, stale instance) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xBC | +0xBC | 4 | livemem read (r4, stale instance) | — | 0 in rec0/rec1; dword 0x5C0F3C49 in rec2 only; no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xC0 | +0xC0 | 8 | livemem read (r4, stale instance) | — | varies (pointer: 0x00000172B55B90 / 0x00000172C61EC0 / 0x000001C726BC40); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xC8 | +0xC8 | 8 | livemem read (r4, stale instance) | — | varies (pointer: 0x00000172B57BA0 / 0x00000172B582C0 / 0x000001C7341360); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xD8 | +0xD8 | 8 | livemem read (r4, stale instance) | — | qword 0x000007FBA1D2E1C0 stable shared ptr across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xE0 | +0xE0 | 4 | livemem read (r4, stale instance) | — | varies (dword 8 / 0x20 / 0x40000); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xE8 | +0xE8 | 4 | livemem read (r4, stale instance) | — | dword 0x11000000 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xEC | +0xEC | 4 | livemem read (r4, stale instance) | — | dword 0x14000001 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xF0 | +0xF0 | 4 | livemem read (r4, stale instance) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xF4 | +0xF4 | 4 | livemem read (r4, stale instance) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0xF8 | +0xF8 | 4 | livemem read (r4, stale instance) | — | dword 1 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x100 | +0x100 | 4 | livemem read (r4, stale instance) | — | dword 4 stable across 3 snapshots (same 3 read commands); no instruction site, meaning '-' | [V live] |
| framebuffer-texture record +0x1 | +0x1 | - | - | - | - | [?] |
| framebuffer-texture record +0x2 | +0x2 | - | - | - | - | [?] |
| framebuffer-texture record +0x3 | +0x3 | - | - | - | - | [?] |
| framebuffer-texture record +0x4 | +0x4 | - | - | - | - | [?] |
| framebuffer-texture record +0x5 | +0x5 | - | - | - | - | [?] |
| framebuffer-texture record +0x6 | +0x6 | - | - | - | - | [?] |
| framebuffer-texture record +0x7 | +0x7 | - | - | - | - | [?] |
| framebuffer-texture record +0x8 | +0x8 | - | - | - | - | [?] |
| framebuffer-texture record +0x9 | +0x9 | - | - | - | - | [?] |
| framebuffer-texture record +0xA | +0xA | - | - | - | - | [?] |
| framebuffer-texture record +0xB | +0xB | - | - | - | - | [?] |
| framebuffer-texture record +0xC | +0xC | - | - | - | - | [?] |
| framebuffer-texture record +0xD | +0xD | - | - | - | - | [?] |
| framebuffer-texture record +0xE | +0xE | - | - | - | - | [?] |
| framebuffer-texture record +0xF | +0xF | - | - | - | - | [?] |
| framebuffer-texture record +0x11 | +0x11 | - | - | - | - | [?] |
| framebuffer-texture record +0x12 | +0x12 | - | - | - | - | [?] |
| framebuffer-texture record +0x13 | +0x13 | - | - | - | - | [?] |
| framebuffer-texture record +0x14 | +0x14 | - | - | - | - | [?] |
| framebuffer-texture record +0x15 | +0x15 | - | - | - | - | [?] |
| framebuffer-texture record +0x16 | +0x16 | - | - | - | - | [?] |
| framebuffer-texture record +0x17 | +0x17 | - | - | - | - | [?] |
| framebuffer-texture record +0x18 | +0x18 | - | - | - | - | [?] |
| framebuffer-texture record +0x19 | +0x19 | - | - | - | - | [?] |
| framebuffer-texture record +0x1A | +0x1A | - | - | - | - | [?] |
| framebuffer-texture record +0x1B | +0x1B | - | - | - | - | [?] |
| framebuffer-texture record +0x1D | +0x1D | - | - | - | - | [?] |
| framebuffer-texture record +0x1E | +0x1E | - | - | - | - | [?] |
| framebuffer-texture record +0x1F | +0x1F | - | - | - | - | [?] |
| framebuffer-texture record +0x21 | +0x21 | - | - | - | - | [?] |
| framebuffer-texture record +0x22 | +0x22 | - | - | - | - | [?] |
| framebuffer-texture record +0x23 | +0x23 | - | - | - | - | [?] |
| framebuffer-texture record +0x24 | +0x24 | - | - | - | - | [?] |
| framebuffer-texture record +0x25 | +0x25 | - | - | - | - | [?] |
| framebuffer-texture record +0x26 | +0x26 | - | - | - | - | [?] |
| framebuffer-texture record +0x27 | +0x27 | - | - | - | - | [?] |
| framebuffer-texture record +0x28 | +0x28 | - | - | - | - | [?] |
| framebuffer-texture record +0x29 | +0x29 | - | - | - | - | [?] |
| framebuffer-texture record +0x2A | +0x2A | - | - | - | - | [?] |
| framebuffer-texture record +0x2B | +0x2B | - | - | - | - | [?] |
| framebuffer-texture record +0x2C | +0x2C | - | - | - | - | [?] |
| framebuffer-texture record +0x2D | +0x2D | - | - | - | - | [?] |
| framebuffer-texture record +0x2E | +0x2E | - | - | - | - | [?] |
| framebuffer-texture record +0x2F | +0x2F | - | - | - | - | [?] |
| framebuffer-texture record +0x30 | +0x30 | - | - | - | - | [?] |
| framebuffer-texture record +0x31 | +0x31 | - | - | - | - | [?] |
| framebuffer-texture record +0x32 | +0x32 | - | - | - | - | [?] |
| framebuffer-texture record +0x33 | +0x33 | - | - | - | - | [?] |
| framebuffer-texture record +0x34 | +0x34 | - | - | - | - | [?] |
| framebuffer-texture record +0x35 | +0x35 | - | - | - | - | [?] |
| framebuffer-texture record +0x36 | +0x36 | - | - | - | - | [?] |
| framebuffer-texture record +0x37 | +0x37 | - | - | - | - | [?] |
| framebuffer-texture record +0x38 | +0x38 | - | - | - | - | [?] |
| framebuffer-texture record +0x39 | +0x39 | - | - | - | - | [?] |
| framebuffer-texture record +0x3A | +0x3A | - | - | - | - | [?] |
| framebuffer-texture record +0x3B | +0x3B | - | - | - | - | [?] |
| framebuffer-texture record +0x3C | +0x3C | - | - | - | - | [?] |
| framebuffer-texture record +0x3D | +0x3D | - | - | - | - | [?] |
| framebuffer-texture record +0x3E | +0x3E | - | - | - | - | [?] |
| framebuffer-texture record +0x3F | +0x3F | - | - | - | - | [?] |
| framebuffer-texture record +0x41 | +0x41 | - | - | - | - | [?] |
| framebuffer-texture record +0x42 | +0x42 | - | - | - | - | [?] |
| framebuffer-texture record +0x43 | +0x43 | - | - | - | - | [?] |
| framebuffer-texture record +0x44 | +0x44 | - | - | - | - | [?] |
| framebuffer-texture record +0x45 | +0x45 | - | - | - | - | [?] |
| framebuffer-texture record +0x46 | +0x46 | - | - | - | - | [?] |
| framebuffer-texture record +0x47 | +0x47 | - | - | - | - | [?] |
| framebuffer-texture record +0x49 | +0x49 | - | - | - | - | [?] |
| framebuffer-texture record +0x4A | +0x4A | - | - | - | - | [?] |
| framebuffer-texture record +0x4B | +0x4B | - | - | - | - | [?] |
| framebuffer-texture record +0x4C | +0x4C | - | - | - | - | [?] |
| framebuffer-texture record +0x4D | +0x4D | - | - | - | - | [?] |
| framebuffer-texture record +0x4E | +0x4E | - | - | - | - | [?] |
| framebuffer-texture record +0x4F | +0x4F | - | - | - | - | [?] |
| framebuffer-texture record +0x51 | +0x51 | - | - | - | - | [?] |
| framebuffer-texture record +0x52 | +0x52 | - | - | - | - | [?] |
| framebuffer-texture record +0x53 | +0x53 | - | - | - | - | [?] |
| framebuffer-texture record +0x54 | +0x54 | - | - | - | - | [?] |
| framebuffer-texture record +0x55 | +0x55 | - | - | - | - | [?] |
| framebuffer-texture record +0x56 | +0x56 | - | - | - | - | [?] |
| framebuffer-texture record +0x57 | +0x57 | - | - | - | - | [?] |
| framebuffer-texture record +0x59 | +0x59 | - | - | - | - | [?] |
| framebuffer-texture record +0x5A | +0x5A | - | - | - | - | [?] |
| framebuffer-texture record +0x5B | +0x5B | - | - | - | - | [?] |
| framebuffer-texture record +0x5C | +0x5C | - | - | - | - | [?] |
| framebuffer-texture record +0x5D | +0x5D | - | - | - | - | [?] |
| framebuffer-texture record +0x5E | +0x5E | - | - | - | - | [?] |
| framebuffer-texture record +0x5F | +0x5F | - | - | - | - | [?] |
| framebuffer-texture record +0x61 | +0x61 | - | - | - | - | [?] |
| framebuffer-texture record +0x62 | +0x62 | - | - | - | - | [?] |
| framebuffer-texture record +0x63 | +0x63 | - | - | - | - | [?] |
| framebuffer-texture record +0x64 | +0x64 | - | - | - | - | [?] |
| framebuffer-texture record +0x65 | +0x65 | - | - | - | - | [?] |
| framebuffer-texture record +0x66 | +0x66 | - | - | - | - | [?] |
| framebuffer-texture record +0x67 | +0x67 | - | - | - | - | [?] |
| framebuffer-texture record +0x69 | +0x69 | - | - | - | - | [?] |
| framebuffer-texture record +0x6A | +0x6A | - | - | - | - | [?] |
| framebuffer-texture record +0x6B | +0x6B | - | - | - | - | [?] |
| framebuffer-texture record +0x6C | +0x6C | - | - | - | - | [?] |
| framebuffer-texture record +0x6D | +0x6D | - | - | - | - | [?] |
| framebuffer-texture record +0x6E | +0x6E | - | - | - | - | [?] |
| framebuffer-texture record +0x6F | +0x6F | - | - | - | - | [?] |
| framebuffer-texture record +0x70 | +0x70 | - | - | - | - | [?] |
| framebuffer-texture record +0x71 | +0x71 | - | - | - | - | [?] |
| framebuffer-texture record +0x72 | +0x72 | - | - | - | - | [?] |
| framebuffer-texture record +0x73 | +0x73 | - | - | - | - | [?] |
| framebuffer-texture record +0x74 | +0x74 | - | - | - | - | [?] |
| framebuffer-texture record +0x75 | +0x75 | - | - | - | - | [?] |
| framebuffer-texture record +0x76 | +0x76 | - | - | - | - | [?] |
| framebuffer-texture record +0x77 | +0x77 | - | - | - | - | [?] |
| framebuffer-texture record +0x78 | +0x78 | - | - | - | - | [?] |
| framebuffer-texture record +0x79 | +0x79 | - | - | - | - | [?] |
| framebuffer-texture record +0x7A | +0x7A | - | - | - | - | [?] |
| framebuffer-texture record +0x7B | +0x7B | - | - | - | - | [?] |
| framebuffer-texture record +0x7C | +0x7C | - | - | - | - | [?] |
| framebuffer-texture record +0x7D | +0x7D | - | - | - | - | [?] |
| framebuffer-texture record +0x7E | +0x7E | - | - | - | - | [?] |
| framebuffer-texture record +0x7F | +0x7F | - | - | - | - | [?] |
| framebuffer-texture record +0x80 | +0x80 | - | - | - | - | [?] |
| framebuffer-texture record +0x81 | +0x81 | - | - | - | - | [?] |
| framebuffer-texture record +0x82 | +0x82 | - | - | - | - | [?] |
| framebuffer-texture record +0x83 | +0x83 | - | - | - | - | [?] |
| framebuffer-texture record +0x84 | +0x84 | - | - | - | - | [?] |
| framebuffer-texture record +0x85 | +0x85 | - | - | - | - | [?] |
| framebuffer-texture record +0x86 | +0x86 | - | - | - | - | [?] |
| framebuffer-texture record +0x87 | +0x87 | - | - | - | - | [?] |
| framebuffer-texture record +0x88 | +0x88 | - | - | - | - | [?] |
| framebuffer-texture record +0x89 | +0x89 | - | - | - | - | [?] |
| framebuffer-texture record +0x8A | +0x8A | - | - | - | - | [?] |
| framebuffer-texture record +0x8B | +0x8B | - | - | - | - | [?] |
| framebuffer-texture record +0x8C | +0x8C | - | - | - | - | [?] |
| framebuffer-texture record +0x8D | +0x8D | - | - | - | - | [?] |
| framebuffer-texture record +0x8E | +0x8E | - | - | - | - | [?] |
| framebuffer-texture record +0x8F | +0x8F | - | - | - | - | [?] |
| framebuffer-texture record +0x90 | +0x90 | - | - | - | - | [?] |
| framebuffer-texture record +0x91 | +0x91 | - | - | - | - | [?] |
| framebuffer-texture record +0x92 | +0x92 | - | - | - | - | [?] |
| framebuffer-texture record +0x93 | +0x93 | - | - | - | - | [?] |
| framebuffer-texture record +0x94 | +0x94 | - | - | - | - | [?] |
| framebuffer-texture record +0x95 | +0x95 | - | - | - | - | [?] |
| framebuffer-texture record +0x96 | +0x96 | - | - | - | - | [?] |
| framebuffer-texture record +0x97 | +0x97 | - | - | - | - | [?] |
| framebuffer-texture record +0x98 | +0x98 | - | - | - | - | [?] |
| framebuffer-texture record +0x99 | +0x99 | - | - | - | - | [?] |
| framebuffer-texture record +0x9A | +0x9A | - | - | - | - | [?] |
| framebuffer-texture record +0x9B | +0x9B | - | - | - | - | [?] |
| framebuffer-texture record +0x9C | +0x9C | - | - | - | - | [?] |
| framebuffer-texture record +0x9D | +0x9D | - | - | - | - | [?] |
| framebuffer-texture record +0x9E | +0x9E | - | - | - | - | [?] |
| framebuffer-texture record +0x9F | +0x9F | - | - | - | - | [?] |
| framebuffer-texture record +0xA1 | +0xA1 | - | - | - | - | [?] |
| framebuffer-texture record +0xA2 | +0xA2 | - | - | - | - | [?] |
| framebuffer-texture record +0xA3 | +0xA3 | - | - | - | - | [?] |
| framebuffer-texture record +0xA4 | +0xA4 | - | - | - | - | [?] |
| framebuffer-texture record +0xA5 | +0xA5 | - | - | - | - | [?] |
| framebuffer-texture record +0xA6 | +0xA6 | - | - | - | - | [?] |
| framebuffer-texture record +0xA7 | +0xA7 | - | - | - | - | [?] |
| framebuffer-texture record +0xA9 | +0xA9 | - | - | - | - | [?] |
| framebuffer-texture record +0xAA | +0xAA | - | - | - | - | [?] |
| framebuffer-texture record +0xAB | +0xAB | - | - | - | - | [?] |
| framebuffer-texture record +0xAC | +0xAC | - | - | - | - | [?] |
| framebuffer-texture record +0xAD | +0xAD | - | - | - | - | [?] |
| framebuffer-texture record +0xAE | +0xAE | - | - | - | - | [?] |
| framebuffer-texture record +0xAF | +0xAF | - | - | - | - | [?] |
| framebuffer-texture record +0xB1 | +0xB1 | - | - | - | - | [?] |
| framebuffer-texture record +0xB2 | +0xB2 | - | - | - | - | [?] |
| framebuffer-texture record +0xB3 | +0xB3 | - | - | - | - | [?] |
| framebuffer-texture record +0xB4 | +0xB4 | - | - | - | - | [?] |
| framebuffer-texture record +0xB5 | +0xB5 | - | - | - | - | [?] |
| framebuffer-texture record +0xB6 | +0xB6 | - | - | - | - | [?] |
| framebuffer-texture record +0xB7 | +0xB7 | - | - | - | - | [?] |
| framebuffer-texture record +0xB9 | +0xB9 | - | - | - | - | [?] |
| framebuffer-texture record +0xBA | +0xBA | - | - | - | - | [?] |
| framebuffer-texture record +0xBB | +0xBB | - | - | - | - | [?] |
| framebuffer-texture record +0xBD | +0xBD | - | - | - | - | [?] |
| framebuffer-texture record +0xBE | +0xBE | - | - | - | - | [?] |
| framebuffer-texture record +0xBF | +0xBF | - | - | - | - | [?] |
| framebuffer-texture record +0xC1 | +0xC1 | - | - | - | - | [?] |
| framebuffer-texture record +0xC2 | +0xC2 | - | - | - | - | [?] |
| framebuffer-texture record +0xC3 | +0xC3 | - | - | - | - | [?] |
| framebuffer-texture record +0xC4 | +0xC4 | - | - | - | - | [?] |
| framebuffer-texture record +0xC5 | +0xC5 | - | - | - | - | [?] |
| framebuffer-texture record +0xC6 | +0xC6 | - | - | - | - | [?] |
| framebuffer-texture record +0xC7 | +0xC7 | - | - | - | - | [?] |
| framebuffer-texture record +0xC9 | +0xC9 | - | - | - | - | [?] |
| framebuffer-texture record +0xCA | +0xCA | - | - | - | - | [?] |
| framebuffer-texture record +0xCB | +0xCB | - | - | - | - | [?] |
| framebuffer-texture record +0xCC | +0xCC | - | - | - | - | [?] |
| framebuffer-texture record +0xCD | +0xCD | - | - | - | - | [?] |
| framebuffer-texture record +0xCE | +0xCE | - | - | - | - | [?] |
| framebuffer-texture record +0xCF | +0xCF | - | - | - | - | [?] |
| framebuffer-texture record +0xD0 | +0xD0 | - | - | - | - | [?] |
| framebuffer-texture record +0xD1 | +0xD1 | - | - | - | - | [?] |
| framebuffer-texture record +0xD2 | +0xD2 | - | - | - | - | [?] |
| framebuffer-texture record +0xD3 | +0xD3 | - | - | - | - | [?] |
| framebuffer-texture record +0xD4 | +0xD4 | - | - | - | - | [?] |
| framebuffer-texture record +0xD5 | +0xD5 | - | - | - | - | [?] |
| framebuffer-texture record +0xD6 | +0xD6 | - | - | - | - | [?] |
| framebuffer-texture record +0xD7 | +0xD7 | - | - | - | - | [?] |
| framebuffer-texture record +0xD9 | +0xD9 | - | - | - | - | [?] |
| framebuffer-texture record +0xDA | +0xDA | - | - | - | - | [?] |
| framebuffer-texture record +0xDB | +0xDB | - | - | - | - | [?] |
| framebuffer-texture record +0xDC | +0xDC | - | - | - | - | [?] |
| framebuffer-texture record +0xDD | +0xDD | - | - | - | - | [?] |
| framebuffer-texture record +0xDE | +0xDE | - | - | - | - | [?] |
| framebuffer-texture record +0xDF | +0xDF | - | - | - | - | [?] |
| framebuffer-texture record +0xE1 | +0xE1 | - | - | - | - | [?] |
| framebuffer-texture record +0xE2 | +0xE2 | - | - | - | - | [?] |
| framebuffer-texture record +0xE3 | +0xE3 | - | - | - | - | [?] |
| framebuffer-texture record +0xE4 | +0xE4 | - | - | - | - | [?] |
| framebuffer-texture record +0xE5 | +0xE5 | - | - | - | - | [?] |
| framebuffer-texture record +0xE6 | +0xE6 | - | - | - | - | [?] |
| framebuffer-texture record +0xE7 | +0xE7 | - | - | - | - | [?] |
| framebuffer-texture record +0xE9 | +0xE9 | - | - | - | - | [?] |
| framebuffer-texture record +0xEA | +0xEA | - | - | - | - | [?] |
| framebuffer-texture record +0xEB | +0xEB | - | - | - | - | [?] |
| framebuffer-texture record +0xED | +0xED | - | - | - | - | [?] |
| framebuffer-texture record +0xEE | +0xEE | - | - | - | - | [?] |
| framebuffer-texture record +0xEF | +0xEF | - | - | - | - | [?] |
| framebuffer-texture record +0xF1 | +0xF1 | - | - | - | - | [?] |
| framebuffer-texture record +0xF2 | +0xF2 | - | - | - | - | [?] |
| framebuffer-texture record +0xF3 | +0xF3 | - | - | - | - | [?] |
| framebuffer-texture record +0xF5 | +0xF5 | - | - | - | - | [?] |
| framebuffer-texture record +0xF6 | +0xF6 | - | - | - | - | [?] |
| framebuffer-texture record +0xF7 | +0xF7 | - | - | - | - | [?] |
| framebuffer-texture record +0xF9 | +0xF9 | - | - | - | - | [?] |
| framebuffer-texture record +0xFA | +0xFA | - | - | - | - | [?] |
| framebuffer-texture record +0xFB | +0xFB | - | - | - | - | [?] |
| framebuffer-texture record +0xFC | +0xFC | - | - | - | - | [?] |
| framebuffer-texture record +0xFD | +0xFD | - | - | - | - | [?] |
| framebuffer-texture record +0xFE | +0xFE | - | - | - | - | [?] |
| framebuffer-texture record +0xFF | +0xFF | - | - | - | - | [?] |
| framebuffer-texture record +0x101 | +0x101 | - | - | - | - | [?] |
| framebuffer-texture record +0x102 | +0x102 | - | - | - | - | [?] |
| framebuffer-texture record +0x103 | +0x103 | - | - | - | - | [?] |
| framebuffer-texture record +0x104 | +0x104 | - | - | - | - | [?] |
| framebuffer-texture record +0x105 | +0x105 | - | - | - | - | [?] |
| framebuffer-texture record +0x106 | +0x106 | - | - | - | - | [?] |
| framebuffer-texture record +0x107 | +0x107 | - | - | - | - | [?] |
| framebuffer-texture record +0x108 | +0x108 | - | - | - | - | [?] |
| framebuffer-texture record +0x109 | +0x109 | - | - | - | - | [?] |
| framebuffer-texture record +0x10A | +0x10A | - | - | - | - | [?] |
| framebuffer-texture record +0x10B | +0x10B | - | - | - | - | [?] |
| framebuffer-texture record +0x10C | +0x10C | - | - | - | - | [?] |
| framebuffer-texture record +0x10D | +0x10D | - | - | - | - | [?] |
| framebuffer-texture record +0x10E | +0x10E | - | - | - | - | [?] |
| framebuffer-texture record +0x10F | +0x10F | - | - | - | - | [?] |
| framebuffer-texture record +0x110 | +0x110 | - | - | - | - | [?] |
| framebuffer-texture record +0x111 | +0x111 | - | - | - | - | [?] |
| framebuffer-texture record +0x112 | +0x112 | - | - | - | - | [?] |
| framebuffer-texture record +0x113 | +0x113 | - | - | - | - | [?] |
| framebuffer-texture record +0x114 | +0x114 | - | - | - | - | [?] |
| framebuffer-texture record +0x115 | +0x115 | - | - | - | - | [?] |
| framebuffer-texture record +0x116 | +0x116 | - | - | - | - | [?] |
| framebuffer-texture record +0x117 | +0x117 | - | - | - | - | [?] |
| framebuffer-texture record +0x118 | +0x118 | - | - | - | - | [?] |
| framebuffer-texture record +0x119 | +0x119 | - | - | - | - | [?] |
| framebuffer-texture record +0x11A | +0x11A | - | - | - | - | [?] |
| framebuffer-texture record +0x11B | +0x11B | - | - | - | - | [?] |
| framebuffer-texture record +0x11C | +0x11C | - | - | - | - | [?] |
| framebuffer-texture record +0x11D | +0x11D | - | - | - | - | [?] |
| framebuffer-texture record +0x11E | +0x11E | - | - | - | - | [?] |
| framebuffer-texture record +0x11F | +0x11F | - | - | - | - | [?] |
| framebuffer-texture record +0x120 | +0x120 | - | - | - | - | [?] |
| framebuffer-texture record +0x121 | +0x121 | - | - | - | - | [?] |
| framebuffer-texture record +0x122 | +0x122 | - | - | - | - | [?] |
| framebuffer-texture record +0x123 | +0x123 | - | - | - | - | [?] |
| framebuffer-texture record +0x124 | +0x124 | - | - | - | - | [?] |
| framebuffer-texture record +0x125 | +0x125 | - | - | - | - | [?] |
| framebuffer-texture record +0x126 | +0x126 | - | - | - | - | [?] |
| framebuffer-texture record +0x127 | +0x127 | - | - | - | - | [?] |
| framebuffer-texture record +0x128 | +0x128 | - | - | - | - | [?] |
| framebuffer-texture record +0x129 | +0x129 | - | - | - | - | [?] |
| framebuffer-texture record +0x12A | +0x12A | - | - | - | - | [?] |
| framebuffer-texture record +0x12B | +0x12B | - | - | - | - | [?] |
| framebuffer-texture record +0x12C | +0x12C | - | - | - | - | [?] |
| framebuffer-texture record +0x12D | +0x12D | - | - | - | - | [?] |
| framebuffer-texture record +0x12E | +0x12E | - | - | - | - | [?] |
| framebuffer-texture record +0x12F | +0x12F | - | - | - | - | [?] |

## Live observations (stale r4 instance, pid 18956; not re-obtainable now — guard slots all zero)

Commands used: `python tools/sigs/livemem.py read 0x172B581F0 0x130` / `read 0x172B55AC0 0x130` / `read 0x1B62E37F0 0x130`; `python tools/sigs/livemem.py ptr @0x12BB4910 1` → 0x000005314A010000 (ctx).
- Stable across all 3 snapshots: +0x00 = 0x000007FBA1D2E100, +0x20 = 0x000007FBA1D2E0D8, +0x40 = 1, +0x48 = 2, +0x50 = 0x000007FFBDB76198, +0xA8 = 0x000000000653A400, +0xB0 = record's own address (self pointer), +0xB8 = 1, +0xD8 = 0x000007FBA1D2E1C0, +0xE8 = 0x11000000, +0xEC = 0x14000001, +0xF0 = 1, +0xF4 = 1, +0xF8 = 1, +0x100 = 4.
- Varies per record: +0x58 (dword 0xFFFFFFFF in rec0/rec1; 0 in rec2), +0x60/+0x68 (0 in rec0/rec1; qword -1 in rec2), +0xA0 (near-record pointer), +0xC0/+0xC8 (varying pointers), +0xE0 (dword 8 / 0x20 / 0x40000), +0xBC (0 in rec0/rec1; 0x5C0F3C49 in rec2 only).
- +0x10 = 0 and +0x1C = 0 in all 3 snapshots → copy path inert (r12 = 0); no record byte written by the copy in the observed instance.
- All other offsets (+0x01..+0x0F, +0x11..+0x1F, +0x21..+0x12F except the live rows above): 0x00 in all 3 snapshots — value observations with meaning '-', not field layouts and not tied to the copy.

## Unproven

Every offset tagged [?] above (+0x01..+0x0F, +0x11..+0x1F, +0x21..+0x12F except the [V]/[V live] rows): no located instruction reads or writes them; they read 0x00 in all 3 r4 live snapshots. No writer for any record byte in +0x01..+0x12F exists in this executable: createFrameBuffer 0xe816380 writes the record only via the external memcpy at unresolved dst r12; its caller (which would store the record pointer into the guard slot and initialize fields) has no call site in .text (see angle (b)) and is not observable from read-only livemem (no mid-call register access; no live records exist in the current instance). descscan2.py is broken; vt/vcalls and rdis rw/struct do not apply to this plain data struct.

## CLOSES?

NO — blocking fact: no instruction in Minecraft.Windows.exe writes any byte of the 0x130 framebuffer-texture record at +0x01..+0x12F, so those offsets have no [V] row and cannot be proven. The only record-field reads are +0x00 (`0xe8164dc  mov r15,[rax]`), +0x10 (`0xe8164ce  mov rcx,[rax+0x10]`), +0x1C (`0xe8164d8  cmp dword ptr [rax+0x1C],2`); the only record-block write is the memcpy `0xe81652f  call 0xEEC6EC0` (rcx=dst rdx=src r8=size; 0xEEC6EC0 = `0xeec6ec0  jmp qword ptr [0xF9A8A98]` import thunk per orchestrator hint) whose record-relative destination r12 = (record+0x1C==2) ? record+0x10+[rsp+0x58] : 0 is not statically resolvable and is inert in every observed instance (record+0x1C==0 → r12==0; skipped when src r14=[r9] == 0). Proven copy facts: size rbx=[r9+8] (`0xe816492  mov ebx,[r9+8]`), source r14=[r9] (`0xe81648f  mov r14,[r9]`), record allocated by sub_e8360f0 (`0xe8164bb  call 0xE8360F0`, pointer at out-param+0x00 `0xe836308  mov [rsi],rcx`). createFrameBuffer's runtime caller — vtable slot 37 entries 0xF4ED3F8/0xF4EEFA8 hold 0xE816380 [V rdis ptr] — has no call site in this executable: 0 direct `call 0xe816380`, 0 `jmp [reg+0x128]`, and the only two `call [reg+0x128]` sites (0xEC6D71D in func 0xEC6D520, 0xECD0EBA in func 0xECD0E90) are unrelated objects; the field-initializing caller lives outside this exe. The destroyer sub_e80ef60 touches only guard-slot fields (`0xe80ef70  mov rdx,[rcx]`, `0xe80ef7c  mov r8d,[rcx+0xC]` / `0xe80ef82  cmp r8d,0xB`, `0xe80efb4  mov rdx,[rcx+0x58]` / `0xe80efbe  call 0xE92A8F0`, clears `0xe80f259  mov qword ptr [rcx],0` / `0xe80f260  mov qword ptr [rcx+0x68],0` / `0xe80f268  mov qword ptr [rcx+0x58],0` / `0xe80f270  mov qword ptr [rcx+0x5F],0`); executor 0xe824991 only copies the record pointer. No live records exist now (guard slots at ctx+0xA32178 all zero: `read 0x5314AA32178 0x180` and `read 0x5314AA32538 0x400` both all zeros), so the orchestrator's live-layout retry cannot execute; r4's three record snapshots are stale. Until a writer function or live records become available, the 0x130 record layout cannot be closed.

## TOOL REQUESTS

- dispfun.py 0x128 | .text scan for `call [reg+0x128]` → exactly 2 sites, both unrelated | proved createFrameBuffer has no caller in .text; replaced hand-hunting of vtable xrefs with an exhaustive byte scan.
- Inline python one-liners (E8 rel32 target scan; `jmp [reg+0x128]` scan; `0xA32178` imm scan) | .text scans | generalized caller/reference enumeration for vtable-dispatched functions; worth keeping as a reusable recipe.
