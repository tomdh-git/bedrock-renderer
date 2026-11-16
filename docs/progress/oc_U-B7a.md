# oc_U-B7a — D3D12 backend createTexture (vtable slot 26, RVA 0xe8143c0)

## NEXT
Unit complete. File written: docs/progress/oc_U-B7a.md. Verified with `python tools/sigs/verify_oc.py docs/progress/oc_U-B7a.md` (see ## Verification below). No further steps for U-B7a.

## Method (static analysis only)
- Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe, image-base RVAs.
- Function listing: `rdis ... fn 0xe8143c0` (full body, size 0x2e1); `dis 0xe81bf30 n=100` only for the callee preview in section 4.
- Identification: docs/data/functions.tsv, docs/BGFX_MAP.md (6z, 6z-2, lines 539/579/619), docs/functions/e82d960.md, docs/functions/e81bf30.md.
- Header: src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h, `CreateTexture` block (lines 150-160).

Tags: [V] = seen in disassembly (RVA cited), [I] = inferred, [?] = unknown. Unclear items flagged `[UNVERIFIED: 0x<rva> question]`.

## 1. Function RVA and size [V]
`sub_e8143c0 [0xe8143c0..0xe8146a1) size 0x2e1 0 xrefs in` (rdis `fn` output). Reached indirectly through vtable slot 26 (`[rax+0xd0]` per docs/BGFX_MAP.md 6et); no direct callers (0 xrefs in).

## 2. Signature and argument-register usage [V for saves/uses; I for C signature]
C signature (per D3D12Context.h lines 142-143; register map verified in listing):

```c
void* createTexture(RendererContextD3D12* this, u16 handle, const bgfx::Memory* mem /*{data*, u32 size}*/, u32 flags, u8 skip /*stack*/);
```
Entry (x64 fastcall): rcx=this, rdx=handle, r8=mem, r9=flags, skip = stack arg at caller [rsp+0x28] = [rbp+0xA0] inside this frame. Return: rax = out.ptr (ID3D12Resource*) via `e81466f  mov rax,[rbp+0x18]`; `e814686  ret` [V].

Argument saves at entry:
- `e8143ec  mov rdi,rcx` — this saved to rdi [V]
- `e8143e7  mov r14,r8` — mem (Memory*) saved to r14 [V]
- `e8143ea  mov esi,edx` — handle (u16) saved to esi [V]
- `e8143e3  mov [rbp+0x28],r9d` — flags (u32) spilled to [rbp+0x28] [V]
- `e8143ef  mov [rbp+0x2E],dx` — handle spilled to [rbp+0x2E] [V]

First-60-instruction usage (literal instruction count from entry; #60 is `e8144be`):
- `e8143f3  lea r12,[rcx+0xBDE178]` — r12 = texture-table base = this + 0xBDE178 [V]
- `e8143fa  movzx ebx,dx` — ebx = zero-extended handle [V]
- `e8143fd  mov rcx,r12` — table base → 1st arg of bounds helper [V]
- `e814400  mov rdx,rbx` — handle → 2nd arg of bounds helper [V]
- `e814408  cmp ebx,0x1000` — handle >= 0x1000 selects overflow-page path [V]
- `e814410  cmp byte ptr [rdi+0xC96190],0` — dynamic-guard byte read [V]
- `e814427` / `e814430  imul r8,rbx,0xB8` — r8 = handle * stride 0xB8 [V]
- `e81451e  mov r8d,[r14+8]` — mem->size (instruction #79, just past 60) [V]
- `e814522  mov rdx,[r14]` — mem->data (instruction #80) [V]
- `e814536  movzx eax,byte ptr [rbp+0xA0]` — skip (stack arg, instruction #87) [V]
- `e81453d  mov [rsp+0x30],al` — skip stored to outgoing stack slot [V]

`e8143db  mov qword ptr [rbp+0x30],0xFFFFFFFFFFFFFFFE` — prologue/EH store, not an argument use [V].

## 3. Texture record table indexing: base, stride, bounds check [V]
Base expression: `e8143f3  lea r12,[rcx+0xBDE178]` → r12 = this + 0xBDE178 (D3D12Tables::kTextures = 0xBDE178, header line 44) [V].
Stride: `e814430  imul r8,rbx,0xB8` (inline path) and `e814427  imul r8,rbx,0xB8` (overflow path) → record offset = handle * 0xB8; stride 0xB8 per checklist/BGFX_MAP line 541 [V].

Handle bounds check / page selection:
```
e814408  cmp ebx,0x1000
e81440e  jb short 0xE814430          ; handle < 0x1000 → inline record
e814410  cmp byte ptr [rdi+0xC96190],0   ; dynamic-guard byte (kDynamicTextureGuard)
e814417  je short 0xE814430          ; guard == 0 → falls through to inline indexing
e814419  lea rdx,[0xF7F68E3]         ; "FAILED: accessing a guarded paged heap backed array out of b..."
e814420  xor ecx,ecx
e814422  call 0xBC5F110              ; error report
e814427  imul r8,rbx,0xB8
e81442e  jmp short 0xE814443         ; → overflow-page walk
e8144fd  add r12,r8                  ; inline record = base + handle*0xB8
```
Overflow-page walk (guard != 0), matching the BGFX_MAP line 539 pattern (`chain = [this+0xc96178] -> [*chain]`, page size 0xB8000, `mov rcx,[rcx+0xb8000]`, magic multiply):
```
e814443  lea r12,[r8-0xB8000]        ; in-page offset
e81444a  mov rax,[rdi+0xC96178]      ; page-chain head
e814451  mov rcx,[rax]               ; first page
e814454  cmp r12,0xB8000
e81445b  jb 0xE8144F8                ; offset < one page → page 0
e814461  add r8,0xFFFFFFFFFFE90000   ; magic-divide prep (divide by 0xB8000)
e814468  mov rax,r8
e81446b  shr rax,0xF
e81446f  mov rdx,0xB21642C8590B217
e814479  mul rdx
e81447c  mov eax,edx
e81447e  not eax
e814480  test al,7
e814482  je short 0xE8144A3
e814484  inc edx
e814486  and edx,7
e814490  add r12,0xFFFFFFFFFFF48000  ; -0xB8000 per page walked
e814497  mov rcx,[rcx+0xB8000]       ; follow next-page pointer
e81449e  dec rdx
e8144a1  jne short 0xE814490
e8144f8  add r12,rcx                 ; record = page + offset
```
Secondary chain bounds validation (guard against short/corrupt page chains):
```
e8144a3  cmp r8d,0x508000
e8144aa  jb short 0xE8144F8
e8144b0  mov rax,[rcx+0xB8000]       ; x8 chain reads
e8144e1  add r12,0xFFFFFFFFFFA40000  ; -0x5C0000
e8144e8  mov rcx,[rax+0xB8000]
e8144ef  cmp r12,0xB7FFF
e8144f6  ja short 0xE8144B0
```

## 4. Stores into the texture record [V]
createTexture itself performs ZERO stores into the texture record: the complete listing 0xe8143c0..0xe8146a1 contains no instruction with r12 (the record pointer) as a store base [V]. r12 is consumed only as `e814555  mov rcx,r12` — the record pointer passed as the first argument of `e81455b  call 0xE81BF30` (TextureD3D12::create), which performs all record writes [V]. The D3D12Context.h comment attributing "+0x98 flags ... +0xB1 numMips" writes to createTexture is therefore imprecise; those writes live in the callee.

Out struct passed by reference: `e81454d  lea rdx,[rbp+0x18]` → {ptr at +0, u32 state at +8} per the header's `&out{ptr +0, u32 state +8}`; filled by the callee; returned in rax (`e81466f  mov rax,[rbp+0x18]`) [V].

Record stores performed inside the callee 0xe81bf30 (first 100 instructions; context only, NOT createTexture):
```
e81bfdc  mov [rdi+0x98],esi          ; W record+0x98 flags (esi = flags arg)
e81bfe5  mov [rdi+0x9C],edx          ; W record+0x9C width
e81bfef  mov [rdi+0xA0],r8d          ; W record+0xA0 height
e81bffb  mov [rdi+0xA4],eax          ; W record+0xA4 depth
e81c004   mov [rdi+0xA8],ecx          ; W record+0xA8 numLayers
e81c00f   mov [rdi+0xAF],sil          ; W record+0xAF requested format
e81c077   mov [rdi+0xB0],r13b         ; W record+0xB0 actual format
e81c0a2/e81c0b9/e81c0c6 mov byte ptr [rdi+0xAE],2/1/0  ; W record+0xAE type (cube/3D/2D)
```

## 5. Callees in order of first call [V call sites; identification tags per row]

| # | RVA | First call site | Identification | Tag |
|---|-----|-----------------|----------------|-----|
| 1 | 0xe83abb0 | `e814403  call 0xE83ABB0` (rcx=table=r12, rdx=handle=rbx) | Common guarded paged-array bounds/guard check `0xe83abb0(table, handle)` | [V] call site; [V] identification per BGFX_MAP lines 539/579/619 |
| 2 | 0xbc5f110 | `e814422  call 0xBC5F110` (rdx=error string data_f7f68e3) | Out-of-bounds error reporter: "FAILED: accessing a guarded paged heap backed array out of bounds." | [V] call site + string; [V] identification per BGFX_MAP line 539 |
| 3 | 0xe8066c0 | `e81450b  call 0xE8066C0` (rcx=&[rbp-8] string out, rdx=&[rbp+0x2E] handle) | Debug-name helper `0xe8066c0(&string, &handle)` per D3D12Context.h line 145 | [V] call site; [I] identification (header comment only) |
| 4 | 0xebd2160 | `e81452c  call 0xEBD2160` (rcx=&[rbp-0x40] container, rdx=[r14]=mem->data, r8d=[r14+8]=mem->size, r9d=0) | bimg image parse `0xebd2160(&container, mem->data, mem->size, 0)`; parses the 0x18-byte TextureCreate header (TEX magic 0x00584554, "MemoryReader: read truncated." per BGFX_MAP 6et) | [V] call site + args; [I] identification per header/BGFX_MAP 6et |
| 5 | 0xe81bf30 | `e81455b  call 0xE81BF30` (rcx=record=r12, rdx=&[rbp+0x18] out, r8=name, r9=&[rbp-0x40] container; stack [rsp+0x20]=mem, [rsp+0x28]=flags, [rsp+0x30]=skip) | TextureD3D12::create | [V] functions.tsv L2 6hz; args per listing |
| 6 | 0xe935700 | `e8145b9  call 0xE935700` (name-buffer free path, r15>=8) | Allocator free helper `free(ptr, size)` per BGFX_MAP lines 440/1086/1195; here frees the e8066c0 name buffer | [V] BGFX_MAP; role here [I] |
| 7 | 0xe83aed0 | `e8145e8  call 0xE83AED0` (rcx=array=tracker+0x14428, rdx=handle=rbx) → rax=entry | Paged-array element getter `0xe83aed0(array, handle)` per BGFX_MAP line 579 → TrackerEntry {u64 state @+0, u8 tracked @+8} | [V] call site; [V] identification per BGFX_MAP 579; entry layout [I] per header TrackerEntry |
| 8 | 0xe83b0e0 | `e81464d  call 0xE83B0E0` (rcx=tracker+0x14420, rdx=handle=esi, r8d=state=r14d) | First-use tracker entry `0xe83b0e0(tracker base, handle, state)` (0x11c) per BGFX_MAP line 579 | [V] call site; [V] identification per BGFX_MAP 579 |
| 9 | 0xe82d960 | `e81466a  call 0xE82D960` (rcx=wrapper+0x14458 tracker block, rdx=[wrapper+0x30] command list, r8d=handle, r9d=state) | Resource state transition helper | [V] functions.tsv L2 6ae; BGFX_MAP lines 579/723 |

Additional targets in-body (not first calls): second `0xe83abb0` at `e81461e` (bounds check on the tracker's texture table, rcx=[tracker+0x14420]=[r15] reloaded at `e814615`), second `0xbc5f110` at `e81463e` (overflow dynamic-handle error after `e81462b  cmp byte ptr [r15+0xB8018],0` — note r15+0xB8018 == table+0xB8000+0x18 == guard byte at renderer+0xC96190 [V arithmetic]), and indirect `e81469a  call qword ptr [0xF9A8C78]` followed by `e8146a0  int3` on the name-buffer validation failure path (`e8145a6  jae 0xE814687`) [V]; IAT slot target unresolved → `[UNVERIFIED: 0xF9A8C78 import target — likely invalid-parameter handler, not resolved from this listing]`.

Handle 0xFFFF shortcut: `e8145c2  cmp si,0xFFFF; e8145c6  je 0xE814652` skips the tracker but still reaches the transition helper at `e814652` [V], consistent with `0xe82d960(...handle 0xFFFF = none...)` (BGFX_MAP 579) [I].

Parse failure path: `e814532  test al,al; e814534  je short 0xE81456D` → `e81456d  mov qword ptr [rbp+0x18],0; e814575  mov dword ptr [rbp+0x20],0` (out.ptr=0, out.state=0) then tracker/transition with state 0 [V].

## Disassembly phases (≤40 instructions each) [V]
e8143c0..e814430: prologue (8 pushes, sub rsp,0xB8, rbp=rsp+0x80), argument saves (this→rdi, mem→r14, handle→esi, flags→[rbp+0x28], handle→[rbp+0x2E]), table base r12=this+0xBDE178, ebx=handle, first call `0xe83abb0(table, handle)`, then `cmp ebx,0x1000`; below → inline path, else guard byte `[rdi+0xC96190]` (zero → inline, non-zero → error via 0xbc5f110 then overflow path).
e814430..e814500: inline offset r8=handle*0xB8; `cmp ebx,0xFFF; jbe` → inline record base+r8. Overflow: r12=offset-0xB8000, walk page chain `[rdi+0xC96178]`→`[rcx+0xB8000]` with magic-divide page index (`mul 0xB21642C8590B217` after `shr rax,0xF`, `test al,7/inc edx/and edx,7` correction), per-page `add r12,-0xB8000`, then `add r12,rcx` = record; secondary chain validation `cmp r8d,0x508000`, 8x `[rcx+0xB8000]` reads, `add r12,-0x5C0000`, `cmp r12,0xB7FFF`.
e814500..e8146a1: debug name `0xe8066c0(&[rbp-8], &[rbp+0x2E])`; `cmp r15,[rbp+0x10], 8` inline/heap branch ([UNVERIFIED: 0xe814510 source/meaning of [rbp+0x10]]); bimg parse `0xebd2160(&[rbp-0x40], mem->data, mem->size, 0)`; on failure out={0,0} (`e81456d`); on success build out stack slots (mem [rsp+0x20], flags [rsp+0x28], skip [rsp+0x30] from [rbp+0xA0]) and call `0xe81bf30(record, &[rbp+0x18], name, &container, mem, flags, skip)`; tracker first-use via `0xe83aed0(tracker+0x14428, handle)` → entry {state qword @+0, tracked byte @+8}; missing → `0xe83b0e0(tracker+0x14420, handle, state)`; store `(state<<32)\|state` to entry+0, set tracked=1; second `0xe83abb0` on tracker texture table; overflow dynamic-handle error `0xbc5f110` if `[table+0xB8018]` guard set; transition `0xe82d960(wrapper+0x14458, [wrapper+0x30], handle, state)`; return rax=[rbp+0x18]; epilogue; invalid-parameter path `e814687`: zero args, `call [0xF9A8C78]`, `int3`.

## OPEN questions
- [UNVERIFIED: 0xe814510 [rbp+0x10] → r15] read and compared with 8 at `e814510`/`e814561` but never written inside createTexture; source unknown (caller frame local or set by e8066c0); controls inline-vs-heap name handling (`e81451a`/`e814582`) and name-buffer cleanup.
- [UNVERIFIED: 0xF9A8C78] import-slot indirect call target at `e81469a` (invalid-parameter path).
- e8066c0 exact name format not verified beyond header comment [I].
- All record-field writes are in TextureD3D12::create (0xe81bf30), see docs/functions/e81bf30.md; not part of this unit.

## TOOL REQUESTS
None — all work done with rdis `fn`/`dis`, functions.tsv, BGFX_MAP.md, and verify_oc.py.

## Verification
Quoted lines checked with `python tools/sigs/verify_oc.py docs/progress/oc_U-B7a.md` after writing; every `0xRVA  instr` line in this document was copied verbatim from the rdis listing.
