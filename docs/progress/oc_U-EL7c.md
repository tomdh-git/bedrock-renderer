## NEXT
DONE

# U-EL7c: L7c Variant axes + (pass, flags) permutation keys (6ap); runtime selection code

Pending part of checklist item L7c: the runtime code that builds/uses a (pass, flags) permutation key and selects a shader variant/program at draw time. (File-format side: pass/axis/variant/shader records in .material.bin = BGFX_MAP 6ap / checklist L7a, already closed.)

## Method
Every row quotes an instruction verbatim from rdis output over Minecraft.Windows.exe 1.26.62.01; every quoted line was re-checked with tools/sigs/verify_oc.py. Tags: [V] seen in disassembly at the cited RVA; [I] inferred from instruction flow or constant recognition (role/name not spelled out by an instruction or string); [?] unknown. Offsets are offsets into the named object; sizes are the instruction's memory-operand size (qword 8, dword 4, word 2, byte 1; '-' when the instruction has no memory operand).

## 1. Call chain (RVAs) — runtime (pass, flags) -> program selection at draw time

| name | rva or offset | size | verbatim `0xRVA  instr` proof | tag |
| MaterialPass::findVariant entry | 0xbcc7ce0 | - | `0xbcc7ce0  push rsi` | [V] |
meaning: signature findVariant(out rdx, pass rcx, defines r8): `0xbcc7ce7  mov rsi,rdx` (out), `0xbcc7cea  mov rdi,rcx` (pass kept in rdi), defines in r8.

| selectVariantId entry | 0xe879eb0 | - | `0xe879eb0  push rbp` | [V] |
meaning: selectVariantId(table rcx, span* rdx, passFlags r8, defines r9): `0xe879edb  mov r14,r9` (defines), `0xe879ede  mov [rbp+8],r8` (passFlags), `0xe879ee2  mov [rbp-8],rdx` (span*), `0xe879ee6  mov rsi,rcx` (table object).

| define validation entry | 0xe87b920 | - | `0xe87b920  push r15` | [V] |
| variant match predicate entry | 0xe879c60 | - | `0xe879c60  push r15` | [V] |
| findVariant call site (submitGeometry tail 0xbcc3b90) | 0xbcc3bea | - | `0xbcc3bea  call 0xBCC7CE0` | [V] |
meaning: out buffer at [rbp-0x28]. xref.py callers lists 17 direct call sites (pass bodies 0x56d3170, 0xbc0b240, 0xbc5bad0, ... and initFromMaterial 0xbcc7f20, which writes node+0x1C at load); this site is decoded in section 4.

| Encoder::submit entry | 0xbc60740 | - | `0xbc60740  push r15` | [V] |
meaning: called at 0xbcc3cbd with the selected program u16 in r8d (bgfx program created at material load).

## 2. Field map: MaterialPass::findVariant (0xbcc7ce0, body ends at 0xbcc7e54 ret)
| name | offset | size | verbatim `0xRVA  instr` proof | tag |
| pass+0x40 flag-table object ptr | pass+0x40 | 8 | `0xbcc7cf7  mov rcx,[rdi+0x40]` | [V] |
meaning: pass object field +0x40 is passed as selectVariantId's table argument. Table (string map) fields used below: size @obj+0x10 (`0xe879f05  mov rax,[rsi+0x10]`), head @obj+8 (`0xe879fc5  mov rdi,[rax+8]`), bucket mask @obj+0x30 (`0xe87b9e7  and rax,[rcx+0x30]`).
| pass+0x48 variants span data ptr | pass+0x48 | 8 | `0xbcc7cfb  mov rdx,[rdi+0x48]` | [V] |
| pass+0x50 variants span end ptr | pass+0x50 | 8 | `0xbcc7cff  mov rax,[rdi+0x50]` | [V] |
meaning: variant span = {data @+0x48, end @+0x50}; element count = (end-data)>>3 via `0xbcc7d0c  sar r10,3`; span elements are VariantRec* pointers — the variant id IS the pointer.
| pass+0x60 passFlags map object ptr | pass+0x60 | 8 | `0xbcc7d38  lea r8,[rdi+0x60]` | [V] |
| pass+0xA0 default variant id | pass+0xA0 | 8 | `0xbcc7d50  mov rax,[rdi+0xA0]` | [V] |
meaning: used when defines->size == 0 (`0xbcc7cf2  je short 0xBCC7D50`); id == 0 => not found (`0xbcc7d5a  je 0xBCC7E45`).
| pass+0x108 variant-map sentinel | pass+0x108 | 8 | `0xbcc7dee  mov rdx,[rdi+0x108]` | [V] |
meaning: empty-bucket test `0xbcc7e05  cmp rcx,rdx` / `0xbcc7e2f  cmp rcx,rdx`; chain walk ends circling to `0xbcc7e20  cmp rcx,r8` where r8 = [bucket+0].
| pass+0x118 variant-map bucket array base | pass+0x118 | 8 | `0xbcc7df5  mov r9,[rdi+0x118]` | [V] |
meaning: bucket entries are 16 bytes (`0xbcc7dfc  shl r8,4`); walk starts at [bucket+8] (`0xbcc7e00  mov rcx,[r9+r8+8]`).
| pass+0x130 bucket mask | pass+0x130 | 8 | `0xbcc7de7  and r8,[rdi+0x130]` | [V] |
meaning: bucket = hash & mask.
| FNV-1a 64 offset basis (imm64) | imm64 | 8 | `0xbcc7d63  mov rdx,0xCBF29CE484222325` | [I] |
meaning: bytewise hash over the 8 id bytes: `0xbcc7d6d  xor rdx,rcx; 0xbcc7d7a  imul rdx,rcx` per byte, eight iterations (`0xbcc7de3  imul r8,rcx` last); bucket = hash & pass+0x130.
| FNV-1a 64 prime (imm64) | imm64 | 8 | `0xbcc7d70  mov rcx,0x100000001B3` | [I] |
| out+0x0 dword {u16 program, valid bit16} | out+0x0 | 4 | `0xbcc7e3b  mov [rsi],eax` | [V] |
meaning: eax = [rcx+0x1C] (`0xbcc7e34  mov eax,[rcx+0x1C]`).
| out+0x8 ptr to variant data (node+0x20) | out+0x8 | 8 | `0xbcc7e3d  mov [rsi+8],rcx` | [V] |
| out+0x10 engaged flag (u8) | out+0x10 | 1 | `0xbcc7e47  mov [rsi+0x10],al` | [V] |
| node+0x10 map key = id (VariantRec*) | node+0x10 | 8 | `0xbcc7e0a  cmp rax,[rcx+0x10]` | [V] |
| node+0x8 chain next pointer | node+0x8 | 8 | `0xbcc7e25  mov rcx,[rcx+8]` | [V] |
| node+0x1C u32 {u16 program, valid bit16} | node+0x1C | 4 | `0xbcc7e34  mov eax,[rcx+0x1C]` | [V] |
meaning: written at load by initFromMaterial (0xbcc7f20); valid = bit 16 = byte at node+0x1D.
| node+0x20 variant data pointer | node+0x20 | 8 | `0xbcc7e37  add rcx,0x20` ; `0xbcc7e3d  mov [rsi+8],rcx` | [V] |

## 3. selectVariantId / define validation / variant match (0xe879eb0, 0xe87b920, 0xe879c60)
| name | offset | size | verbatim `0xRVA  instr` proof | tag |
| merged map object (stack copy of the default flag table) | [rbp-0x50] | - | `0xe879efc  call 0x9B020` | [V] |
meaning: merged = copy of the pass+0x40 table map; `0xe879f01  mov [rbp],rsi` saves the table object; merged count at [rbp+0x10]; `0xe879fc5  mov rdi,[rax+8]` walks table nodes; each node copied by `0xe879ff6  call 0x49B1A0` (key obj @node+0x10, value obj @node+0x30).
| passFlags override into merged | - | - | `0xe87a04a  call 0x1336D0` ; `0xe87a08b  call 0x9D6D0` | [V] |
meaning: for each passFlags (name,value): find key in merged (`0xe87a040  lea r8,[rdi+0x10]` key obj), then merged[key] = passFlags value; copy terminated by `0xe87a032  mov byte ptr [r13+r12],0`.
| define validation via 0xe87b920 | - | - | `0xe87a106  call 0xE87B920` | [V] |
meaning: (table object, define name object): `0xe87b933  mov rbx,[rdx+0x10]` (define key len); bucket = name hash & table mask `0xe87b9e7  and rax,[rcx+0x30]`; chain compare len `0xe87ba10  cmp rbx,[r15+0x20]` and string `0xe87ba3a  call 0xEEC6EB0`; found flag `0xe87baf8  cmp rax,rbx` ; `0xe87bafb  setne al`. Invalid define => selection fails (`0xe87a10b  test al,al` ; `0xe87a10d  je 0xE87A349` => id = 0).
| define applied only when not fixed by passFlags | - | - | `0xe87a200  cmp r15,[r14+0x20]` ; `0xe87a22a  call 0xEEC6EB0` | [V] |
meaning: define key looked up in the passFlags map (bucket = hash & [rax+0x30] `0xe87a1cb  and rdx,[rax+0x30]`; chain start `0xe87a1db  mov r14,[rax+rdx+8]`); if the name is already in passFlags it is skipped (fixed by passFlags); otherwise merged[key] = define value via `0xe87a2ca  call 0x9D6D0`.
| variant match per VariantRec* span entry | - | - | `0xe87a326  call 0xE879C60` | [V] |
meaning: called per span entry (`0xe87a320  mov rcx,[r14]`); first entry with al==1 wins; return value = the VariantRec* pointer (the id) `0xe87a3df  mov rax,r12`, or 0 (`0xe87a349  xor r12d,r12d`).
| match predicate 0xe879c60 internals | - | - | `0xe879c70  mov rdx,[rdx+8]` ; `0xe879c91  mov rax,[rcx+0x38]` | [I] |
meaning: per merged (name,value): FNV-1a(name) & variantMapMask `0xe879df7  and rdx,[rsp+0x28]`; chain walk with key-length compare `0xe879e12  cmp rbx,[rbp+0x20]` and string compare `0xe879e4a  call 0xEEC6EB0`; equal-sized values `0xe879e78  cmp [rbp+0x40],r8`; result `0xe879e98  mov al,1` (match) / `0xe879e94  xor eax,eax` (no match); absent names ignored (bucket-empty path `0xe879e08  je 0xE879CC0` skips to next merged node). Exact field paired at the string call is inferred, not spelled out by an instruction or string => [I].

## 4. Consumer: submitGeometry tail 0xbcc3b90 -> Encoder::submit 0xbc60740
| name | offset | size | verbatim `0xRVA  instr` proof | tag |
| out+0x0 program u16 != 0xFFFF | [rbp-0x28] | 2 | `0xbcc3c05  cmp word ptr [rbp-0x28],0xFFFF` | [V] |
| out+0x2 valid byte == 1 | [rbp-0x26] | 1 | `0xbcc3bfb  cmp byte ptr [rbp-0x26],1` | [V] |
| out+0x10 engaged flag == 1 | [rbp-0x18] | 1 | `0xbcc3bef  cmp byte ptr [rbp-0x18],1` | [V] |
meaning: all three must hold or the findVariant result is rejected (`0xbcc3cc6  xor eax,eax`).
| per-view draw index CAS | [rcx+0xD457C0] | 4 | `0xbcc3c4b  lock cmpxchg [rcx+0xD457C0],r8d` | [V] |
meaning: index allocated by CAS (cap 0xFFFF via `0xbcc3c3e  cmovae r8d,edx`); draw record base = rcx + index*0x40 + 0x9457C0 (`0xbcc3c77  shl rax,6` ; `0xbcc3c7e  add rcx,0x9457C0`), filled by `0xbcc3c88  call 0xEBCE390`, index stored at `0xbcc3c8d  mov [r14+0x7C],r15d`, flag `0xbcc3c91  mov word ptr [r14+0x9E],1`.
| program argument u16 | [rbp-0x28] | 2 | `0xbcc3ca5  movzx r8d,word ptr [rbp-0x28]` | [V] |
| Encoder::submit(program, ...) call | 0xbc60740 | 5 | `0xbcc3cbd  call 0xBC60740` | [V] |
meaning: the selected variant's program (u16 from node+0x1C, created at load by initFromMaterial) is submitted as this draw's program — the runtime (pass, flags) permutation selection is consumed here.

## File-format side (context; closed previously as L7a/6ap)
Each .material.bin pass declares axis names with value strings (e.g. Instancing {Off,On}, Fancy {Off,On}); variant records carry u32 hash + u16 flagCount + (axisName,value) flag pairs (BGFX_MAP 6ap step 9; parsed by tools/lce/matparse.py over 1.26.62.01 data/renderer/materials/*.material.bin). Those (name,value) pairs are exactly the constraints merged and matched by the runtime code in sections 2-3. Axis names and values exist only in .material.bin data [I from matparse dump]; no runtime code compares axis-name strings — the runtime compares name/value objects loaded from the material at load time.

## CLOSES?
CLOSES? YES — the pending part (runtime selection code) is fully located and decoded: defines validated against the pass flag table (0xe87b920), merged with defaults then passFlags (0xe879eb0), first matching variant record selected by per-record predicate 0xe879c60 (string compare via 0xEEC6EB0; absent names ignored), variant id = VariantRec* pointer looked up by FNV-1a 64 of its 8 bytes in the pass+0x108 map (buckets @pass+0x118, mask @pass+0x130) by findVariant 0xbcc7ce0 -> node+0x1C {u16 program, valid bit16}; consumer 0xbcc3b90 rejects not-engaged/invalid/0xFFFF programs and calls Encoder::submit 0xbc60740 with the program u16. All table rows are proven by quoted instructions ([V] except three [I] constant-recognition/field-pairing rows noted above); no [?] rows; no blocking fact.

Remaining non-blocking inferences: exact object field paired at 0xe879e4a vs 0xe879e87 (name or value object) [I]; type names MaterialPass/DefineMap/VariantRec are dossier labels [I]; the file-format axis table is data-side only [I from matparse].

## TOOL REQUESTS
None
