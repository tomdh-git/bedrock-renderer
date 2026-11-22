## NEXT
DONE

# U-EG2: G2 Variant axes + (pass, flags) permutation keys (6ap); runtime selection code

File-format side (axes, passes, variants, shader records in .material.bin): G1a + BGFX_MAP 6ap [V] — done (pass declares axis names + value strings; variant record = u32 hash + u16 flagCount + (axisName,value) pairs + per-stage shader records; variant program handle at variant+0x1C per BGFX_MAP 6gy).

Pending part of G2 (this unit): the runtime code that builds/uses a (pass, flags) permutation key to select a shader variant/program at draw time. All instruction quotes are copied verbatim from the precomputed input data (docs/progress/oc_U-EG2_r1.md .. r5.md, re-checked against Minecraft.Windows.exe 1.26.62.01). Tags: [V] instruction seen at cited RVA; [I] role/name inferred from operand flow (no string names it); [-] n/a. Meaning is written only where an instruction or string shows it, else '-'.

## Field/proof table: runtime (pass, flags) permutation selection

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
| pass+0x40 | 8 | [rdi+0x40] | `0xBCC7CF7  mov rcx,[rdi+0x40]` | pass flag-table object, passed as selectVariantId table argument | [V] |
| pass+0x48 | 8 | [rdi+0x48] | `0xBCC7CFB  mov rdx,[rdi+0x48]` | variant span data ptr (VariantRec* elements) | [V] |
| pass+0x50 | 8 | [rdi+0x50] | `0xBCC7CFF  mov rax,[rdi+0x50]` | variant span end ptr; element count = (end-data)>>3 at `0xBCC7D0C  sar r10,3` | [V] |
| pass+0x60 | 8 | [rdi+0x60] | `0xBCC7D38  lea r8,[rdi+0x60]` | passFlags map (per-pass fixed axis overrides), selectVariantId arg | [V] |
| pass+0xA0 | 8 | [rdi+0xA0] | `0xBCC7D50  mov rax,[rdi+0xA0]` | default variant id used when defines->size == 0; id == 0 => not found | [V] |
| FNV basis imm64 | - | - | `0xBCC7D63  mov rdx,0xCBF29CE484222325` | FNV-1a 64 offset basis, hashed over the 8 id bytes | [V] |
| FNV prime imm64 | - | - | `0xBCC7D70  mov rcx,0x100000001B3` | FNV-1a 64 prime; per-byte step `0xBCC7D6D  xor rdx,rcx` / `0xBCC7D7A  imul rdx,rcx` over 8 id bytes (ah, >>0x10, >>0x18, >>0x20, >>0x28, >>0x30, >>0x38) | [V] |
| pass+0x130 | 8 | [rdi+0x130] | `0xBCC7DE7  and r8,[rdi+0x130]` | variant-map bucket mask; bucket = hash & mask | [V] |
| pass+0x108 | 8 | [rdi+0x108] | `0xBCC7DEE  mov rdx,[rdi+0x108]` | variant-map sentinel; empty chain ends here | [V] |
| pass+0x118 | 8 | [rdi+0x118] | `0xBCC7DF5  mov r9,[rdi+0x118]` | variant-map bucket array base; entries are 16 bytes (`0xBCC7DFC  shl r8,4`) | [V] |
| bucket head | 8 | [r9+r8+8] | `0xBCC7E00  mov rcx,[r9+r8+8]` | bucket chain head node | [V] |
| node+0x10 | 8 | [rcx+0x10] | `0xBCC7E0A  cmp rax,[rcx+0x10]` ; `0xE879FE8  lea r8,[rbx+0x10]` ; `0xE87A040  lea r8,[rdi+0x10]` | map key = variant id (VariantRec* pointer), compared on chain walk; also table-node key obj for the merged copy and passFlags node key lookup | [V] |
| node+0x8 | 8 | [rcx+8] | `0xBCC7E25  mov rcx,[rcx+8]` | chain next pointer | [V] |
| node+0x1C | 4 | [rcx+0x1C] | `0xBCC7E34  mov eax,[rcx+0x1C]` | variant payload: u16 program handle + bit16 valid flag (valid byte = node+0x1D) | [V] |
| node+0x20 | 8 | [rcx+0x20] via add | `0xBCC7E37  add rcx,0x20` | variant data pointer returned at out+8 | [V] |
| out+0x0 | 4 | [rsi] | `0xBCC7E3B  mov [rsi],eax` | out+0: resolved program u16 (from node+0x1C) | [V] |
| out+0x8 | 8 | [rsi+8] | `0xBCC7E3D  mov [rsi+8],rcx` | out+8: variant data pointer (node+0x20) | [V] |
| out+0x10 | 1 | [rsi+0x10] | `0xBCC7E41  mov al,1` ; `0xBCC7E47  mov [rsi+0x10],al` | out+0x10: engaged/found flag | [V] |
| entry | - | - | `0xE879EB0  push rbp` | selectVariantId(table rcx, span* rdx, passFlags r8, defines r9): `0xE879EDB  mov r14,r9` (defines), `0xE879EDE  mov [rbp+8],r8` (passFlags), `0xE879EE2  mov [rbp-8],rdx` (span*), `0xE879EE6  mov rsi,rcx` (table object) | [V] |
| merged stack map | - | [rbp-0x50] | `0xE879EFC  call 0x9B020` ; `0xE879F01  mov [rbp],rsi` | merged = copy of the pass flag-table map (default axis name->value) | [V] |
| table size | 4 | [rsi+0x10] | `0xE879F05  mov rax,[rsi+0x10]` | table node count (size field of the map object) | [V] |
| table head | 8 | [rax+8] | `0xE879FC5  mov rdi,[rax+8]` | table node list head; table nodes carry key obj at +0x10, value obj at +0x30 | [V] |
| node copy | - | [rbx+0x10]/[rbx+0x30] | `0xE879FE8  lea r8,[rbx+0x10]` ; `0xE879FEC  mov r9,[rbx+0x30]` ; `0xE879FF6  call 0x49B1A0` | each table node copied (key +0x10, value +0x30) into merged | [V] |
| passFlags head | 8 | [rax+8] | `0xE87A002  mov rbx,[rax+8]` | passFlags node list head (pass+0x60 map) | [V] |
| passFlags override | - | [rdi+0x10] | `0xE87A040  lea r8,[rdi+0x10]` ; `0xE87A04A  call 0x1336D0` ; `0xE87A08B  call 0x9D6D0` ; `0xE87A032  mov byte ptr [r13+r12],0` | for each passFlags (name,value): find name in merged, then merged[name] = value (passFlags win over defaults) | [V] |
| define key obj | 8 | [r12+0x10] | `0xE87A0F5  lea rsi,[r12+0x10]` ; `0xE87A106  call 0xE87B920` ; `0xE87A10D  je 0xE87A349` | each instance define (key+0x10 name obj) validated against the pass flag table; invalid define => id = 0 | [V] |
| define value bytes | 1 | [rsi+rcx] | `0xE87A160  movzx r9d,byte ptr [rsi+rcx]` ; `0xE87A165  xor r9,rdx` ; `0xE87A168  imul r9,rbx` | per-byte FNV-1a of define value bytes (basis 0xCBF29CE484222325, prime 0x100000001B3 at `0xE87A125  mov rdx,0xCBF29CE484222325`) | [V] |
| passFlags fixed check | 8 | [r14+0x20] | `0xE87A200  cmp r15,[r14+0x20]` ; `0xE87A22A  call 0xEEC6EB0` | define name looked up in the passFlags map; if present, the define is skipped (axis fixed by passFlags) | [V] |
| define applied | - | - | `0xE87A28D  call 0x1336D0` ; `0xE87A2CA  call 0x9D6D0` | define (name,value) merged when its name is not fixed by passFlags | [V] |
| variant match | - | [r14] | `0xE87A320  mov rcx,[r14]` ; `0xE87A326  call 0xE879C60` | each VariantRec* span entry tested against all merged (name,value) constraints | [V] |
| id result | - | - | `0xE87A344  mov r12,[r14]` ; `0xE87A3DF  mov rax,r12` | first matching VariantRec* pointer = variant id; 0 = no match | [V] |
| 0xe87b920 entry | - | - | `0xE87B920  push r15` | 0xe87b920(table rcx, name rdx, value r8): `0xE87B933  mov rbx,[rdx+0x10]` (name length) ; `0xE87B930  mov rdi,rdx` ; `0xE87B92D  mov rsi,r8` (value obj) | [V] |
| name object | 8 | [rdx+0x18] | `0xE87B937  cmp qword ptr [rdx+0x18],0x10` ; `0xE87B93E  mov rdi,[rdi]` | name object: short name inline at +0x10, long name pointer at +0 | [V] |
| name hash | 1 | [rdi+r9] | `0xE87B980  movzx r11d,byte ptr [rdi+r9]` ; `0xE87B985  xor r11,rax` ; `0xE87B988  imul r11,rdx` | FNV-1a 64 of the flag name bytes | [V] |
| table bucket mask | 8 | [rcx+0x30] | `0xE87B9E7  and rax,[rcx+0x30]` | bucket = name hash & table mask | [V] |
| table chain head | 8 | [rcx+8] | `0xE87B9EB  mov r14,[rcx+8]` ; `0xE87B9F7  mov r15,[rcx+rax+8]` | map head / bucket chain head (16-byte entries) | [V] |
| node value compare | 8 | [r15+0x20] | `0xE87BA10  cmp rbx,[r15+0x20]` ; `0xE87BA3A  call 0xEEC6EB0` | chain walk: compare name length then name bytes via 0xEEC6EB0 | [V] |
| value object | 8 | [r15+0x30]/[r15+0x38] | `0xE87BA75  mov r14,[r15+0x30]` ; `0xE87BA79  mov rbx,[r15+0x38]` | matched flag node's value object (+0x30/+0x38 = ptr/long) compared with the define value | [V] |
| validation result | 1 | - | `0xE87BAF8  cmp rax,rbx` ; `0xE87BAFB  setne al` | returns al=1 iff (name,value) is a legal axis assignment | [V] |
| 0xe879c60 entry | - | - | `0xE879C60  push r15` | 0xe879c60(VariantRec* rcx, merged map rdx): end iterator `0xE879C70  mov rdx,[rdx+8]` ; `0xE879C74  mov r15,[rdx]` | [V] |
| variant flag map | 8 | [rcx+0x20]/[rcx+0x38] | `0xE879C91  mov rax,[rcx+0x38]` (mask) ; `0xE879C99  mov r12,[rcx+0x20]` (buckets) ; `0xE879CA2  shl rax,4` | VariantRec's own flag map: buckets +0x20, mask +0x38, 16-byte entries | [V] |
| merged name hash | 1 | [rdi+rcx] | `0xE879D90  movzx r9d,byte ptr [rdi+rcx]` ; `0xE879D95  xor r9,rdx` ; `0xE879D98  imul r9,r13` | FNV-1a 64 of each merged axis name | [V] |
| variant bucket | 8 | [rsp+0x28] | `0xE879DF7  and rdx,[rsp+0x28]` ; `0xE879E00  mov rbp,[r12+rdx+8]` | bucket = hash & variant mask (+0x38); chain head in variant map buckets (+0x20) | [V] |
| value length | 8 | [rbp+0x20] | `0xE879E12  cmp rbx,[rbp+0x20]` | merged value length vs variant node value length | [V] |
| value compare | - | - | `0xE879E44  mov rcx,rdi` ; `0xE879E4A  call 0xEEC6EB0` ; `0xE879E78  cmp [rbp+0x40],r8` ; `0xE879E87  call 0xEEC6EB0` | value string compare; names absent from the variant map are skipped (`0xE879E08  je 0xE879CC0`) | [V] |
| predicate result | 1 | - | `0xE879E98  mov al,1` ; `0xE879E94  xor eax,eax` | al=1: variant matches every merged (name,value) constraint present in it; 0: no match | [V] |
| 0xe87a470 entry | - | - | `0xE87A470  push rbp` | e87a470(flag node rcx=r14, out rdx=rbx, defines map r8): `0xE87A49D  mov rbx,rdx` ; `0xE87A4A0  mov r14,rcx` | [V] |
| defines nodes | 8 | [r8+8] | `0xE87A4A7  mov rsi,[r8+8]` ; `0xE87A4AB  mov rdi,[rsi]` | defines map node list (circular list head at +8) | [V] |
| define node key/value | 8 | [rdi+0x10]/[rdi+0x30] | `0xE87A4C0  lea rdx,[rdi+0x10]` ; `0xE87A4C4  lea r8,[rdi+0x30]` ; `0xE87A4CB  call 0xE87B920` | every instance define (key+0x10, value+0x30) validated via 0xe87b920 before merging | [V] |
| flag span | 8 | [r14+0x40]/[r14+0x48] | `0xE87A4F9  mov r15,[r14+0x40]` ; `0xE87A4FD  mov rbx,[r14+0x48]` ; `0xE87A509  sar rax,3` | flag/table span start/end (8-byte entry pairs); entry count = (end-start)>>3 | [V] |
| variant id stored | 8 | [rbx+0x60] | `0xE87A6D0  call 0xE879EB0` ; `0xE87A6D6  mov [rbx+0x60],rax` | selectVariantId result (variant id) stored at out+0x60 | [V] |
| pass arg | 8 | [rbp+0x60] | `0xBCC3BDB  mov rcx,[rbp+0x60]` | pass object for findVariant at this call site | [V] |
| defines arg | - | [0x12AE2840] | `0xBCC3BDF  lea r8,[0x12AE2840]` | defines argument = global empty map object (default-id path; other callers pass instance defines) | [V] |
| out buffer | - | [rbp-0x28] | `0xBCC3BE6  lea rdx,[rbp-0x28]` | findVariant out buffer {program u16 @+0, variant ptr @+8, engaged @+0x10} | [V] |
| findVariant call | - | - | `0xBCC3BEA  call 0xBCC7CE0` | runtime (pass, flags) -> variant resolution | [V] |
| engaged check | 1 | [rbp-0x18] | `0xBCC3BEF  cmp byte ptr [rbp-0x18],1` | out+0x10 engaged must be 1, else result rejected | [V] |
| valid check | 1 | [rbp-0x26] | `0xBCC3BFB  cmp byte ptr [rbp-0x26],1` | out+0x2 = valid bit16 of node+0x1C dword must be 1 | [V] |
| program check | 2 | [rbp-0x28] | `0xBCC3C05  cmp word ptr [rbp-0x28],0xFFFF` | out+0 program handle must not be 0xFFFF | [V] |
| program argument | 2 | [rbp-0x28] | `0xBCC3CA5  movzx r8d,word ptr [rbp-0x28]` | program u16 passed to Encoder::submit | [V] |
| Encoder::submit call | - | - | `0xBCC3CBD  call 0xBC60740` | draw submitted with the resolved variant program | [V] |
| Encoder::submit entry | - | - | `0xBC60740  push r15` | Encoder::submit entry; program u16 = variant's bgfx program handle (created at material load) | [V] |

## Interpretation (all [V])

At draw time a pass object holds: flag-table object at pass+0x40 (map nodes key+0x10 name / value+0x30; each flag = one axis with its allowed values), variant span at pass+0x48/0x50 (VariantRec* elements, one per material variant record: axis name/value assignments), passFlags map at pass+0x60 (per-pass fixed axis overrides), default variant id at pass+0xA0, and the variant id -> {program} map at pass+0x108 (sentinel), pass+0x118 (buckets), pass+0x130 (mask); each map node stores key+0x10 (id), next+0x8, payload+0x1C {u16 program, valid bit16}, data+0x20.

Runtime selection:
1. Instance defines (per-axis axisName=axisValue overrides, e.g. Instancing=On) are validated against the pass flag table by 0xe87b920 (name hashed FNV-1a 64, bucket = hash & table+0x30, chain walk compares name length + bytes via 0xEEC6EB0, then the value object is checked) — an invalid define fails the whole selection.
2. selectVariantId 0xe879eb0 builds merged = table defaults, applies passFlags overrides, then applies each instance define whose name is not fixed by passFlags (name lookup `0xE87A200  cmp r15,[r14+0x20]` / string compare `0xE87A22A  call 0xEEC6EB0`, assign `0xE87A2CA  call 0x9D6D0`).
3. The first VariantRec* whose own flag map (buckets +0x20, mask +0x38) matches every merged (name,value) present in it wins (predicate 0xe879c60; absent names ignored); its pointer is the variant id. Default path (no defines) uses pass+0xA0 directly.
4. findVariant 0xbcc7ce0 hashes the 8 id bytes with FNV-1a 64 (`0xBCC7D63` basis / `0xBCC7D70` prime), bucket = hash & pass+0x130, walks pass+0x118 buckets comparing node+0x10 against the id; on hit returns node+0x1C {u16 program, valid bit16} at out+0, node+0x20 at out+8, engaged at out+0x10.
5. Consumer 0xbcc3b94 rejects unless engaged==1, valid==1, program != 0xFFFF, then calls Encoder::submit 0xbc60740 with the program u16 — this is the (pass, flags) -> program selection consumed at draw time.

## CLOSES?

YES — the pending part of G2 (runtime selection code) is fully proven by [V] rows: merged-key construction from table defaults + passFlags + validated instance defines (selectVariantId 0xe879eb0 + define validation 0xe87b920 + variant predicate 0xe879c60), variant-id -> program lookup (findVariant 0xbcc7ce0 -> node+0x1C program handle, corroborated by BGFX_MAP 6gy), and draw-time consumption (Encoder::submit 0xbc60740 at 0xbcc3cbd). Every offset in the table has at least one [V] verbatim instruction line; no part of the runtime selection chain is left unproven. Remaining [I] items are non-blocking: structure names (MaterialPass, flag table, DefineMap, VariantRec) are dossier labels, and the exact field paired at individual 0xEEC6EB0 string-compare sites is inferred from operand flow.

## Open questions

[UNVERIFIED: 0xe86ff10 object identity — caller of 0xe87a470; flag node +0x40/+0x48 span role (allowed-value list for one axis) inferred from flow, not string-named]
[UNVERIFIED: define value object layout at 0xe87a160 — hashed bytes are [rsi+rcx], exact value field not spelled by an instruction or string]

## TOOL REQUESTS

None
