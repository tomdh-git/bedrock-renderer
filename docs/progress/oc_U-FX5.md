# Unit U-FX5 progress — FullscreenEffect visitor (tag 7) body decode (listing lines 5413..5869)

## Source
- Listing: docs/data/listings/effect_visitor_666aca0_667191c.txt (each line `0xRVA  instruction`)
- Target range: listing lines 5413..5869 (end of file; file has 5869 lines, verified)
- Context (from oc_U-FX4): tag-7 body entered at 0x666b5cf (listing line 475); U-FX3 tables covered lines 2950..4259 and placed the tag-7 body epilogue jump at line 4252 `jmp 0x6670032` (RVA 0x666FBBB) [V]. Lines 4253..5869 are cold-path targets of those branches plus whatever jump-table cases (other tags) begin inside this range. Unit U-FX4 covered lines 4253..5412; this unit covers lines 5413..5869 (end of file).

## Register context carried from oc_U-FX4 [I]
- r12 = description pointer after line 3115 `mov r12,[r12]`; reused/clobbered later (e.g. line 4341 `mov r12,[r14]`).
- rsi = description pointer reloaded at lines 3276/3294 `mov rsi,[rax+0x78]`; clobbered at line 4196.
- r13 = copy of description pointer (r13=r12 at line 3114).
- Other registers hold chain/refcount/heap objects; [rbp+...] stack slots. Notes tag [V]=seen in listing, [I]=inferred, [?]=unknown.

## NEXT
Resume at listing line 5413 (first line of this unit). Block 1 (5413..5452) below; next block to append: 5453..5492.

## Block 1 — listing lines 5413..5452 (40 lines)

### lines 5413..5452 (0x66710CB..0x6671191)
Jump to shared tag-7 code at 0x666FE83 (line 5419), then FNV-1a hash setup: loads global [0x129F92A0], compares with 0xFFFFFFFF, calls string hashing function 0x79580, prepares for 4-byte-aligned FNV-1a hash loop with constants 0xCBF29CE484222325 and 0x100000001B3 [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5413 | 0x66710cb | `lea rcx,[0x567DBA0]` | rcx = string address [V] |
| 5414 | 0x66710d2 | `call 0xE935740` | call 0xE935740 [V] |
| 5415 | 0x66710d7 | `lea rcx,[0x129CA5E0]` | rcx = global dword address [V] |
| 5416 | 0x66710de | `call 0xE938D70` | call 0xE938D70 [V] |
| 5417 | 0x66710e3 | `mov r14,[rbp+0x650]` | r14 = object pointer [V] |
| 5418 | 0x66710ea | `mov r12,[rbp+0x648]` | r12 = stack/object slot [V] |
| 5419 | 0x66710f1 | `jmp 0x666FE83` | jump to shared tag-7 code 0x666FE83 [V] |
| 5420 | 0x66710f6 | `call 0x75740` | call 0x75740 [V] |
| 5421 | 0x66710fb | `nop` | — |
| 5422 | 0x66710fc | `call 0x75740` | call 0x75740 [V] |
| 5423 | 0x6671101 | `nop` | — |
| 5424 | 0x6671102 | `lea rcx,[0xF5B2BCD]` | rcx = string address [V] |
| 5425 | 0x6671109 | `call 0xEEC5850` | call 0xEEC5850 [V] |
| 5426 | 0x667110e | `nop` | — |
| 5427 | 0x667110f | `lea rcx,[0x129F92A0]` | rcx = global address [V] |
| 5428 | 0x6671116 | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5429 | 0x667111b | `cmp dword ptr [0x129F92A0],0xFFFFFFFF` | compare global with 0xFFFFFFFF [V] |
| 5430 | 0x6671122 | `jne 0x6670103` | branch exit 0x6670103 [V] |
| 5431 | 0x6671128 | `lea rdx,[0xF56398C]` | rdx = string address [V] |
| 5432 | 0x667112f | `lea rsi,[rbp+0x3F0]` | rsi = stack buffer [V] |
| 5433 | 0x6671136 | `mov rcx,rsi` | rcx = rsi [V] |
| 5434 | 0x6671139 | `call 0x79580` | call 0x79580 (string copy/hash prep) [V] |
| 5435 | 0x667113e | `nop` | — |
| 5436 | 0x667113f | `mov r8,[rbp+0x400]` | r8 = string length [V] |
| 5437 | 0x6671146 | `cmp qword ptr [rbp+0x408],0x10` | compare buffer size with 0x10 [V] |
| 5438 | 0x667114e | `jb short 0x6671157` | branch exit 0x6671157 [V] |
| 5439 | 0x6671150 | `mov rsi,[rbp+0x3F0]` | rsi = stack buffer [V] |
| 5440 | 0x667115a | `test r8,r8` | test length [V] |
| 5441 | 0x667115a | `je 0x66716E7` | branch exit 0x66716E7 [V] |
| 5442 | 0x6671160 | `mov eax,r8d` | eax = length [V] |
| 5443 | 0x6671163 | `and eax,3` | eax &= 3 (remainder) [V] |
| 5444 | 0x6671166 | `mov rcx,0x100000001B3` | rcx = FNV prime [V] |
| 5445 | 0x6671170 | `cmp r8,4` | compare length with 4 [V] |
| 5446 | 0x6671174 | `jae 0x66716F3` | branch exit 0x66716F3 [V] |
| 5447 | 0x667117a | `mov rdx,0xCBF29CE484222325` | rdx = FNV offset basis [V] |
| 5448 | 0x6671184 | `xor r9d,r9d` | r9d = 0 [V] |
| 5449 | 0x6671187 | `jmp 0x6671745` | branch exit 0x6671745 [V] |
| 5450 | 0x667118c | `call 0x75B60` | call 0x75B60 [V] |
| 5451 | 0x6671191 | `nop` | — |

**Branch exits in this block:** 0x666FE83 (5419), 0x6670103 (5430), 0x6671157 (5438), 0x66716E7 (5441), 0x66716F3 (5446), 0x6671745 (5449). Calls: 0xE935740 (5414), 0xE938D70 (5416), 0x75740 (5420, 5422), 0xEEC5850 (5425), 0xE938CB0 (5428), 0x79580 (5434), 0x75B60 (5450). No description reads.

## NEXT
Resume at listing line 5453. Block 2 (5453..5492) below; next block to append: 5493..5532.

## Block 2 — listing lines 5453..5492 (40 lines)

### lines 5453..5492 (0x6671192..0x667127B)
FNV-1a hash loop main body: processes 4 bytes at a time with xor/imul, handles remainder bytes, stores hash to [0x129FA0E8], calls cleanup 0x73150, calls 0xE938D70, jumps to tag handler 0x666B6AA [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5452 | 0x6671192 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5453 | 0x667119c | `jmp 0x667127D` | branch exit 0x667127D [V] |
| 5454 | 0x66711a1 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5455 | 0x66711ab | `jmp 0x667132C` | branch exit 0x667132C [V] |
| 5456 | 0x66711b0 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5457 | 0x66711ba | `jmp 0x66713DB` | branch exit 0x66713DB [V] |
| 5458 | 0x66711bf | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5459 | 0x66711c9 | `jmp 0x6671483` | branch exit 0x6671483 [V] |
| 5460 | 0x66711ce | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5461 | 0x66711d8 | `jmp 0x667152B` | branch exit 0x667152B [V] |
| 5462 | 0x66711dd | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5463 | 0x66711e7 | `jmp 0x66715D3` | branch exit 0x66715D3 [V] |
| 5464 | 0x66711ec | `lea rcx,[0xF5B2BCD]` | rcx = string address [V] |
| 5465 | 0x66711f3 | `call 0xEEC5850` | call 0xEEC5850 [V] |
| 5466 | 0x66711f8 | `nop` | — |
| 5467 | 0x66711f9 | `and rdx,0xFFFFFFFFFFFFFFFC` | rdx &= ~3 (aligned length) [V] |
| 5468 | 0x66711fd | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5469 | 0x6671207 | `xor r8d,r8d` | r8d = 0 (index) [V] |
| 5470 | 0x667120a | `mov r9,0x100000001B3` | r9 = FNV prime [V] |
| 5471 | 0x6671214 | `movzx r10d,byte ptr [rsi+r8]` | load byte [rsi+r8] [V] |
| 5472 | 0x6671219 | `xor r10,rcx` | xor with hash [V] |
| 5473 | 0x667121c | `imul r10,r9` | multiply by FNV prime [V] |
| 5474 | 0x6671220 | `movzx ecx,byte ptr [rsi+r8+1]` | load byte [rsi+r8+1] [V] |
| 5475 | 0x6671226 | `xor rcx,r10` | xor with hash [V] |
| 5476 | 0x6671229 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5477 | 0x667122d | `movzx r10d,byte ptr [rsi+r8+2]` | load byte [rsi+r8+2] [V] |
| 5478 | 0x6671233 | `xor r10,rcx` | xor with hash [V] |
| 5479 | 0x6671236 | `imul r10,r9` | multiply by FNV prime [V] |
| 5480 | 0x667123a | `movzx ecx,byte ptr [rsi+r8+3]` | load byte [rsi+r8+3] [V] |
| 5481 | 0x6671240 | `xor rcx,r10` | xor with hash [V] |
| 5482 | 0x6671243 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5483 | 0x6671247 | `add r8,4` | advance index by 4 [V] |
| 5484 | 0x667124b | `cmp rdx,r8` | compare aligned length with index [V] |
| 5485 | 0x667124e | `jne short 0x6671214` | loop back [V] |
| 5486 | 0x6671250 | `test rax,rax` | test remainder count [V] |
| 5487 | 0x6671253 | `je short 0x667127D` | branch exit 0x667127D [V] |
| 5488 | 0x6671255 | `add rsi,r8` | advance buffer pointer [V] |
| 5489 | 0x6671258 | `xor edx,edx` | edx = 0 [V] |
| 5490 | 0x667125a | `mov r8,0x100000001B3` | r8 = FNV prime [V] |
| 5491 | 0x6671264 | `mov r9,rcx` | r9 = current hash [V] |
| 5492 | 0x6671267 | `movzx ecx,byte ptr [rsi+rdx]` | load remainder byte [V] |

**Branch exits:** 0x667127D (5453, 5487), 0x667132C (5455), 0x66713DB (5457), 0x6671483 (5459), 0x667152B (5461), 0x66715D3 (5463), 0x6671214 (5485, loop). Calls: 0xEEC5850 (5465). No description reads.

## NEXT
Resume at listing line 5493. Block 3 (5493..5532) below; next block to append: 5533..5572.

## Block 3 — listing lines 5493..5532 (40 lines)

### lines 5493..5532 (0x667126B..0x6671337)
Remainder-byte FNV-1a loop, stores hash to [0x129FA0E8], cleanup call 0x73150, call 0xE938D70, jump to tag handler 0x666B6AA [V]. Then second FNV-1a setup begins for [0x129FA0F8].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5493 | 0x667126b | `xor rcx,r9` | xor with hash [V] |
| 5494 | 0x667126e | `imul rcx,r8` | multiply by FNV prime [V] |
| 5495 | 0x6671272 | `inc rdx` | increment index [V] |
| 5496 | 0x6671275 | `mov r9,rcx` | r9 = updated hash [V] |
| 5497 | 0x6671278 | `cmp rax,rdx` | compare remainder count with index [V] |
| 5498 | 0x667127b | `jne short 0x6671267` | loop back [V] |
| 5499 | 0x667127d | `mov [0x129FA0E8],rcx` | store hash to global [V] |
| 5500 | 0x6671284 | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |
| 5501 | 0x667128b | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5502 | 0x6671290 | `lea rcx,[0x129FA0F0]` | rcx = global address [V] |
| 5503 | 0x6671297 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5504 | 0x667129c | `lea r13,[rbp+0x3F0]` | r13 = stack buffer [V] |
| 5505 | 0x66712a3 | `jmp 0x666B6AA` | jump to tag handler 0x666B6AA [V] |
| 5506 | 0x66712a8 | `and rdx,0xFFFFFFFFFFFFFFFC` | rdx &= ~3 (aligned length) [V] |
| 5507 | 0x66712ac | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5508 | 0x66712b6 | `xor r8d,r8d` | r8d = 0 (index) [V] |
| 5509 | 0x66712b9 | `mov r9,0x100000001B3` | r9 = FNV prime [V] |
| 5510 | 0x66712c3 | `movzx r10d,byte ptr [rsi+r8]` | load byte [rsi+r8] [V] |
| 5511 | 0x66712c8 | `xor r10,rcx` | xor with hash [V] |
| 5512 | 0x66712cb | `imul r10,r9` | multiply by FNV prime [V] |
| 5513 | 0x66712cf | `movzx ecx,byte ptr [rsi+r8+1]` | load byte [rsi+r8+1] [V] |
| 5514 | 0x66712d5 | `xor rcx,r10` | xor with hash [V] |
| 5515 | 0x66712d8 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5516 | 0x66712dc | `movzx r10d,byte ptr [rsi+r8+2]` | load byte [rsi+r8+2] [V] |
| 5517 | 0x66712e2 | `xor r10,rcx` | xor with hash [V] |
| 5518 | 0x66712e5 | `imul r10,r9` | multiply by FNV prime [V] |
| 5519 | 0x66712e9 | `movzx ecx,byte ptr [rsi+r8+3]` | load byte [rsi+r8+3] [V] |
| 5520 | 0x66712ef | `xor rcx,r10` | xor with hash [V] |
| 5521 | 0x66712f2 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5522 | 0x66712f6 | `add r8,4` | advance index by 4 [V] |
| 5523 | 0x66712fa | `cmp rdx,r8` | compare aligned length with index [V] |
| 5524 | 0x66712fd | `jne short 0x66712C3` | loop back [V] |
| 5525 | 0x66712ff | `test rax,rax` | test remainder count [V] |
| 5526 | 0x6671302 | `je short 0x667132C` | branch exit 0x667132C [V] |
| 5527 | 0x6671304 | `add rsi,r8` | advance buffer pointer [V] |
| 5528 | 0x6671307 | `xor edx,edx` | edx = 0 [V] |
| 5529 | 0x6671309 | `mov r8,0x100000001B3` | r8 = FNV prime [V] |
| 5530 | 0x6671313 | `mov r9,rcx` | r9 = current hash [V] |
| 5531 | 0x6671316 | `movzx ecx,byte ptr [rsi+rdx]` | load remainder byte [V] |
| 5532 | 0x667131a | `xor rcx,r9` | xor with hash [V] |

**Branch exits:** 0x666B6AA (5505), 0x667132C (5526), 0x66712C3 (5524, loop). Calls: 0x73150 (5501), 0xE938D70 (5503). No description reads.

## NEXT
Resume at listing line 5533. Block 4 (5533..5572) below; next block to append: 5573..5612.

## Block 4 — listing lines 5533..5572 (40 lines)

### lines 5533..5572 (0x667131D..0x66713DB)
Remainder-byte FNV-1a loop, stores hash to [0x129FA0F8], cleanup call 0x73150, call 0xE938D70, jump to tag handler 0x666B6CF [V]. Then third FNV-1a setup begins for [0x129FA148].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5533 | 0x667131d | `imul rcx,r8` | multiply by FNV prime [V] |
| 5534 | 0x6671321 | `inc rdx` | increment index [V] |
| 5535 | 0x6671324 | `mov r9,rcx` | r9 = updated hash [V] |
| 5536 | 0x6671327 | `cmp rax,rdx` | compare remainder count with index [V] |
| 5537 | 0x667132a | `jne short 0x6671316` | loop back [V] |
| 5538 | 0x667132c | `mov [0x129FA0F8],rcx` | store hash to global [V] |
| 5539 | 0x6671333 | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |
| 5540 | 0x667133a | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5541 | 0x667133f | `lea rcx,[0x129FA100]` | rcx = global address [V] |
| 5542 | 0x6671346 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5543 | 0x667134b | `lea r13,[rbp+0x3F0]` | r13 = stack buffer [V] |
| 5544 | 0x6671352 | `jmp 0x666B6CF` | jump to tag handler 0x666B6CF [V] |
| 5545 | 0x6671357 | `and rdx,0xFFFFFFFFFFFFFFFC` | rdx &= ~3 (aligned length) [V] |
| 5546 | 0x667135b | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5547 | 0x6671365 | `xor r8d,r8d` | r8d = 0 (index) [V] |
| 5548 | 0x6671368 | `mov r9,0x100000001B3` | r9 = FNV prime [V] |
| 5549 | 0x6671372 | `movzx r10d,byte ptr [rsi+r8]` | load byte [rsi+r8] [V] |
| 5550 | 0x6671377 | `xor r10,rcx` | xor with hash [V] |
| 5551 | 0x667137a | `imul r10,r9` | multiply by FNV prime [V] |
| 5552 | 0x667137e | `movzx ecx,byte ptr [rsi+r8+1]` | load byte [rsi+r8+1] [V] |
| 5553 | 0x6671384 | `xor rcx,r10` | xor with hash [V] |
| 5554 | 0x6671387 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5555 | 0x667138b | `movzx r10d,byte ptr [rsi+r8+2]` | load byte [rsi+r8+2] [V] |
| 5556 | 0x6671391 | `xor r10,rcx` | xor with hash [V] |
| 5557 | 0x6671394 | `imul r10,r9` | multiply by FNV prime [V] |
| 5558 | 0x6671398 | `movzx ecx,byte ptr [rsi+r8+3]` | load byte [rsi+r8+3] [V] |
| 5559 | 0x667139e | `xor rcx,r10` | xor with hash [V] |
| 5560 | 0x66713a1 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5561 | 0x66713a5 | `add r8,4` | advance index by 4 [V] |
| 5562 | 0x66713a9 | `cmp rdx,r8` | compare aligned length with index [V] |
| 5563 | 0x66713ac | `jne short 0x6671372` | loop back [V] |
| 5564 | 0x66713ae | `test rax,rax` | test remainder count [V] |
| 5565 | 0x66713b1 | `je short 0x66713DB` | branch exit 0x66713DB [V] |
| 5566 | 0x66713b3 | `add rsi,r8` | advance buffer pointer [V] |
| 5567 | 0x66713b6 | `xor edx,edx` | edx = 0 [V] |
| 5568 | 0x66713b8 | `mov r8,0x100000001B3` | r8 = FNV prime [V] |
| 5569 | 0x66713c2 | `mov r9,rcx` | r9 = current hash [V] |
| 5570 | 0x66713c5 | `movzx ecx,byte ptr [rsi+rdx]` | load remainder byte [V] |
| 5571 | 0x66713c9 | `xor rcx,r9` | xor with hash [V] |
| 5572 | 0x66713cc | `imul rcx,r8` | multiply by FNV prime [V] |

**Branch exits:** 0x666B6CF (5544), 0x66713DB (5565), 0x6671372 (5563, loop). Calls: 0x73150 (5539), 0xE938D70 (5541). No description reads.

## NEXT
Resume at listing line 5573. Block 5 (5573..5612) below; next block to append: 5613..5652.

## Block 5 — listing lines 5573..5612 (40 lines)

### lines 5573..5612 (0x66713D0..0x6671481)
Remainder-byte FNV-1a loop, stores hash to [0x129FA148], cleanup call 0x73150, call 0xE938D70, jump to tag handler 0x666C91E [V]. Then fourth FNV-1a setup begins for [0x129FA158].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5573 | 0x66713d0 | `inc rdx` | increment index [V] |
| 5574 | 0x66713d3 | `mov r9,rcx` | r9 = updated hash [V] |
| 5575 | 0x66713d6 | `cmp rax,rdx` | compare remainder count with index [V] |
| 5576 | 0x66713d9 | `jne short 0x66713C5` | loop back [V] |
| 5577 | 0x66713db | `mov [0x129FA148],rcx` | store hash to global [V] |
| 5578 | 0x66713e2 | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |
| 5579 | 0x66713e9 | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5580 | 0x66713ee | `lea rcx,[0x129FA150]` | rcx = global address [V] |
| 5581 | 0x66713f5 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5582 | 0x66713fa | `jmp 0x666C91E` | jump to tag handler 0x666C91E [V] |
| 5583 | 0x66713ff | `and rdx,0xFFFFFFFFFFFFFFFC` | rdx &= ~3 (aligned length) [V] |
| 5584 | 0x6671403 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5585 | 0x667140d | `xor r8d,r8d` | r8d = 0 (index) [V] |
| 5586 | 0x6671410 | `mov r9,0x100000001B3` | r9 = FNV prime [V] |
| 5587 | 0x667141a | `movzx r10d,byte ptr [rsi+r8]` | load byte [rsi+r8] [V] |
| 5588 | 0x667141f | `xor r10,rcx` | xor with hash [V] |
| 5589 | 0x6671422 | `imul r10,r9` | multiply by FNV prime [V] |
| 5590 | 0x6671426 | `movzx ecx,byte ptr [rsi+r8+1]` | load byte [rsi+r8+1] [V] |
| 5591 | 0x667142c | `xor rcx,r10` | xor with hash [V] |
| 5592 | 0x667142f | `imul rcx,r9` | multiply by FNV prime [V] |
| 5593 | 0x6671433 | `movzx r10d,byte ptr [rsi+r8+2]` | load byte [rsi+r8+2] [V] |
| 5594 | 0x6671439 | `xor r10,rcx` | xor with hash [V] |
| 5595 | 0x667143c | `imul r10,r9` | multiply by FNV prime [V] |
| 5596 | 0x6671440 | `movzx ecx,byte ptr [rsi+r8+3]` | load byte [rsi+r8+3] [V] |
| 5597 | 0x6671446 | `xor rcx,r10` | xor with hash [V] |
| 5598 | 0x6671449 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5599 | 0x667144d | `add r8,4` | advance index by 4 [V] |
| 5600 | 0x6671451 | `cmp rdx,r8` | compare aligned length with index [V] |
| 5601 | 0x6671454 | `jne short 0x667141A` | loop back [V] |
| 5602 | 0x6671456 | `test rax,rax` | test remainder count [V] |
| 5603 | 0x6671459 | `je short 0x6671483` | branch exit 0x6671483 [V] |
| 5604 | 0x667145b | `add rsi,r8` | advance buffer pointer [V] |
| 5605 | 0x667145e | `xor edx,edx` | edx = 0 [V] |
| 5606 | 0x6671460 | `mov r8,0x100000001B3` | r8 = FNV prime [V] |
| 5607 | 0x667146a | `mov r9,rcx` | r9 = current hash [V] |
| 5608 | 0x667146d | `movzx ecx,byte ptr [rsi+rdx]` | load remainder byte [V] |
| 5609 | 0x6671471 | `xor rcx,r9` | xor with hash [V] |
| 5610 | 0x6671474 | `imul rcx,r8` | multiply by FNV prime [V] |
| 5611 | 0x6671478 | `inc rdx` | increment index [V] |
| 5612 | 0x667147b | `mov r9,rcx` | r9 = updated hash [V] |

**Branch exits:** 0x666C91E (5582), 0x6671483 (5603), 0x667141A (5601, loop). Calls: 0x73150 (5579), 0xE938D70 (5581). No description reads.

## NEXT
Resume at listing line 5613. Block 6 (5613..5652) below; next block to append: 5653..5692.

## Block 6 — listing lines 5613..5652 (40 lines)

### lines 5613..5652 (0x667147E..0x6671529)
Remainder-byte FNV-1a loop, stores hash to [0x129FA158], cleanup call 0x73150, call 0xE938D70, jump to tag handler 0x666C943 [V]. Then fifth FNV-1a setup begins for [0x129FA168].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5613 | 0x667147e | `cmp rax,rdx` | compare remainder count with index [V] |
| 5614 | 0x6671481 | `jne short 0x667146D` | loop back [V] |
| 5615 | 0x6671483 | `mov [0x129FA158],rcx` | store hash to global [V] |
| 5616 | 0x667148a | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |
| 5617 | 0x6671491 | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5618 | 0x6671496 | `lea rcx,[0x129FA160]` | rcx = global address [V] |
| 5619 | 0x667149d | `call 0xE938D70` | call 0xE938D70 [V] |
| 5620 | 0x66714a2 | `jmp 0x666C943` | jump to tag handler 0x666C943 [V] |
| 5621 | 0x66714a7 | `and rdx,0xFFFFFFFFFFFFFFFC` | rdx &= ~3 (aligned length) [V] |
| 5622 | 0x66714ab | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5623 | 0x66714b5 | `xor r8d,r8d` | r8d = 0 (index) [V] |
| 5624 | 0x66714b8 | `mov r9,0x100000001B3` | r9 = FNV prime [V] |
| 5625 | 0x66714c2 | `movzx r10d,byte ptr [rsi+r8]` | load byte [rsi+r8] [V] |
| 5626 | 0x66714c7 | `xor r10,rcx` | xor with hash [V] |
| 5627 | 0x66714ca | `imul r10,r9` | multiply by FNV prime [V] |
| 5628 | 0x66714ce | `movzx ecx,byte ptr [rsi+r8+1]` | load byte [rsi+r8+1] [V] |
| 5629 | 0x66714d4 | `xor rcx,r10` | xor with hash [V] |
| 5630 | 0x66714d7 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5631 | 0x66714db | `movzx r10d,byte ptr [rsi+r8+2]` | load byte [rsi+r8+2] [V] |
| 5632 | 0x66714e1 | `xor r10,rcx` | xor with hash [V] |
| 5633 | 0x66714e4 | `imul r10,r9` | multiply by FNV prime [V] |
| 5634 | 0x66714e8 | `movzx ecx,byte ptr [rsi+r8+3]` | load byte [rsi+r8+3] [V] |
| 5635 | 0x66714ee | `xor rcx,r10` | xor with hash [V] |
| 5636 | 0x66714f1 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5637 | 0x66714f5 | `add r8,4` | advance index by 4 [V] |
| 5638 | 0x66714f9 | `cmp rdx,r8` | compare aligned length with index [V] |
| 5639 | 0x66714fc | `jne short 0x66714C2` | loop back [V] |
| 5640 | 0x66714fe | `test rax,rax` | test remainder count [V] |
| 5641 | 0x6671501 | `je short 0x667152B` | branch exit 0x667152B [V] |
| 5642 | 0x6671503 | `add rsi,r8` | advance buffer pointer [V] |
| 5643 | 0x6671506 | `xor edx,edx` | edx = 0 [V] |
| 5644 | 0x6671508 | `mov r8,0x100000001B3` | r8 = FNV prime [V] |
| 5645 | 0x6671512 | `mov r9,rcx` | r9 = current hash [V] |
| 5646 | 0x6671515 | `movzx ecx,byte ptr [rsi+rdx]` | load remainder byte [V] |
| 5647 | 0x6671519 | `xor rcx,r9` | xor with hash [V] |
| 5648 | 0x667151c | `imul rcx,r8` | multiply by FNV prime [V] |
| 5649 | 0x6671520 | `inc rdx` | increment index [V] |
| 5650 | 0x6671523 | `mov r9,rcx` | r9 = updated hash [V] |
| 5651 | 0x6671526 | `cmp rax,rdx` | compare remainder count with index [V] |
| 5652 | 0x6671529 | `jne short 0x6671515` | loop back [V] |

**Branch exits:** 0x666C943 (5620), 0x667152B (5641), 0x66714C2 (5639, loop). Calls: 0x73150 (5617), 0xE938D70 (5619). No description reads.

## NEXT
Resume at listing line 5653. Block 7 (5653..5692) below; next block to append: 5693..5732.

## Block 7 — listing lines 5653..5692 (40 lines)

### lines 5653..5692 (0x667152B..0x66715D1)
Remainder-byte FNV-1a loop, stores hash to [0x129FA168], cleanup call 0x73150, call 0xE938D70, jump to tag handler 0x666C968 [V]. Then sixth FNV-1a setup begins for [0x129FA120].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5653 | 0x667152b | `mov [0x129FA168],rcx` | store hash to global [V] |
| 5654 | 0x6671532 | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |
| 5655 | 0x6671539 | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5656 | 0x667153e | `lea rcx,[0x129FA170]` | rcx = global address [V] |
| 5657 | 0x6671545 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5658 | 0x667154a | `jmp 0x666C968` | jump to tag handler 0x666C968 [V] |
| 5659 | 0x667154f | `and rdx,0xFFFFFFFFFFFFFFFC` | rdx &= ~3 (aligned length) [V] |
| 5660 | 0x6671553 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5661 | 0x667155d | `xor r8d,r8d` | r8d = 0 (index) [V] |
| 5662 | 0x6671560 | `mov r9,0x100000001B3` | r9 = FNV prime [V] |
| 5663 | 0x667156a | `movzx r10d,byte ptr [rsi+r8]` | load byte [rsi+r8] [V] |
| 5664 | 0x667156f | `xor r10,rcx` | xor with hash [V] |
| 5665 | 0x6671572 | `imul r10,r9` | multiply by FNV prime [V] |
| 5666 | 0x6671576 | `movzx ecx,byte ptr [rsi+r8+1]` | load byte [rsi+r8+1] [V] |
| 5667 | 0x667157c | `xor rcx,r10` | xor with hash [V] |
| 5668 | 0x667157f | `imul rcx,r9` | multiply by FNV prime [V] |
| 5669 | 0x6671583 | `movzx r10d,byte ptr [rsi+r8+2]` | load byte [rsi+r8+2] [V] |
| 5670 | 0x6671589 | `xor r10,rcx` | xor with hash [V] |
| 5671 | 0x667158c | `imul r10,r9` | multiply by FNV prime [V] |
| 5672 | 0x6671590 | `movzx ecx,byte ptr [rsi+r8+3]` | load byte [rsi+r8+3] [V] |
| 5673 | 0x6671596 | `xor rcx,r10` | xor with hash [V] |
| 5674 | 0x6671599 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5675 | 0x667159d | `add r8,4` | advance index by 4 [V] |
| 5676 | 0x66715a1 | `cmp rdx,r8` | compare aligned length with index [V] |
| 5677 | 0x66715a4 | `jne short 0x667156A` | loop back [V] |
| 5678 | 0x66715a6 | `test rax,rax` | test remainder count [V] |
| 5679 | 0x66715a9 | `je short 0x66715D3` | branch exit 0x66715D3 [V] |
| 5680 | 0x66715ab | `add rsi,r8` | advance buffer pointer [V] |
| 5681 | 0x66715ae | `xor edx,edx` | edx = 0 [V] |
| 5682 | 0x66715b0 | `mov r8,0x100000001B3` | r8 = FNV prime [V] |
| 5683 | 0x66715ba | `mov r9,rcx` | r9 = current hash [V] |
| 5684 | 0x66715bd | `movzx ecx,byte ptr [rsi+rdx]` | load remainder byte [V] |
| 5685 | 0x66715c1 | `xor rcx,r9` | xor with hash [V] |
| 5686 | 0x66715c4 | `imul rcx,r8` | multiply by FNV prime [V] |
| 5687 | 0x66715c8 | `inc rdx` | increment index [V] |
| 5688 | 0x66715cb | `mov r9,rcx` | r9 = updated hash [V] |
| 5689 | 0x66715ce | `cmp rax,rdx` | compare remainder count with index [V] |
| 5690 | 0x66715d1 | `jne short 0x66715BD` | loop back [V] |
| 5691 | 0x66715d3 | `mov [0x129FA120],rcx` | store hash to global [V] |
| 5692 | 0x66715da | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |

**Branch exits:** 0x666C968 (5658), 0x66715D3 (5679), 0x667156A (5677, loop). Calls: 0x73150 (5655), 0xE938D70 (5657). No description reads.

## NEXT
Resume at listing line 5693. Block 8 (5693..5732) below; next block to append: 5733..5772.

## Block 8 — listing lines 5693..5732 (40 lines)

### lines 5693..5732 (0x66715E1..0x66716A4)
Remainder-byte FNV-1a loop, stores hash to [0x129FA120], cleanup call 0x73150, call 0xE938D70, jump to tag handler 0x666CFE1 [V]. Then seventh hash setup: calls 0x1A2800, 0x75740, calls 0xE938CB0 with global [0x129F9280], compares with 0xFFFFFFFF, jumps to 0x666EFE1 or proceeds with string copy 0x79580.

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5693 | 0x66715e1 | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5694 | 0x66715e6 | `lea rcx,[0x129FA128]` | rcx = global address [V] |
| 5695 | 0x66715ed | `call 0xE938D70` | call 0xE938D70 [V] |
| 5696 | 0x66715f2 | `jmp 0x666CFE1` | jump to tag handler 0x666CFE1 [V] |
| 5697 | 0x66715f7 | `call 0x1A2800` | call 0x1A2800 [V] |
| 5698 | 0x66715fc | `nop` | — |
| 5699 | 0x66715fd | `call 0x75740` | call 0x75740 [V] |
| 5700 | 0x6671602 | `nop` | — |
| 5701 | 0x6671603 | `lea rcx,[0x129F9280]` | rcx = global address [V] |
| 5702 | 0x667160a | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5703 | 0x667160f | `cmp dword ptr [0x129F9280],0xFFFFFFFF` | compare global with 0xFFFFFFFF [V] |
| 5704 | 0x6671616 | `jne 0x666EFE1` | branch exit 0x666EFE1 [V] |
| 5705 | 0x667161c | `lea rdx,[0xF60CFF6]` | rdx = string address [V] |
| 5706 | 0x6671623 | `lea rsi,[rbp+0x3F0]` | rsi = stack buffer [V] |
| 5707 | 0x667162a | `mov rcx,rsi` | rcx = rsi [V] |
| 5708 | 0x667162d | `call 0x79580` | call 0x79580 (string copy/hash prep) [V] |
| 5709 | 0x6671632 | `nop` | — |
| 5710 | 0x6671633 | `mov rdx,[rbp+0x400]` | rdx = string length [V] |
| 5711 | 0x667163a | `cmp qword ptr [rbp+0x408],0x10` | compare buffer size with 0x10 [V] |
| 5712 | 0x6671642 | `jb short 0x667164B` | branch exit 0x667164B [V] |
| 5713 | 0x6671644 | `mov rsi,[rbp+0x3F0]` | rsi = stack buffer [V] |
| 5714 | 0x667164b | `test rdx,rdx` | test length [V] |
| 5715 | 0x667164e | `je 0x6671797` | branch exit 0x6671797 [V] |
| 5716 | 0x6671654 | `mov eax,edx` | eax = length [V] |
| 5717 | 0x6671656 | `and eax,3` | eax &= 3 (remainder) [V] |
| 5718 | 0x6671659 | `cmp rdx,4` | compare length with 4 [V] |
| 5719 | 0x667165d | `jae 0x66717B5` | branch exit 0x66717B5 [V] |
| 5720 | 0x6671663 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5721 | 0x667166d | `xor r8d,r8d` | r8d = 0 [V] |
| 5722 | 0x6671670 | `jmp 0x6671811` | branch exit 0x6671811 [V] |
| 5723 | 0x6671675 | `lea rcx,[0x129F9290]` | rcx = global address [V] |
| 5724 | 0x667167c | `call 0xE938CB0` | call 0xE938CB0 [V] |
| 5725 | 0x6671681 | `cmp dword ptr [0x129F9290],0xFFFFFFFF` | compare global with 0xFFFFFFFF [V] |
| 5726 | 0x6671688 | `jne 0x666F2F7` | branch exit 0x666F2F7 [V] |
| 5727 | 0x667168e | `lea rdx,[0xF56398C]` | rdx = string address [V] |
| 5728 | 0x6671695 | `lea rsi,[rbp+0x3F0]` | rsi = stack buffer [V] |
| 5729 | 0x667169c | `mov rcx,rsi` | rcx = rsi [V] |
| 5730 | 0x667169f | `call 0x79580` | call 0x79580 (string copy/hash prep) [V] |
| 5731 | 0x66716a4 | `nop` | — |
| 5732 | 0x66716a5 | `mov rdx,[rbp+0x400]` | rdx = string length [V] |

**Branch exits:** 0x666CFE1 (5696), 0x666EFE1 (5704), 0x667164B (5712), 0x6671797 (5715), 0x66717B5 (5719), 0x6671811 (5722), 0x666F2F7 (5726). Calls: 0x73150 (5693), 0xE938D70 (5695), 0x1A2800 (5697), 0x75740 (5699), 0xE938CB0 (5702, 5724), 0x79580 (5708, 5730). No description reads.

## NEXT
Resume at listing line 5733. Block 9 (5733..5772) below; next block to append: 5773..5812.

## Block 9 — listing lines 5733..5772 (40 lines)

### lines 5733..5772 (0x66716AC..0x6671773)
Seventh FNV-1a hash loop: processes 4 bytes at a time with xor/imul, handles remainder bytes, stores hash to [0x129F9298], cleanup call 0x73150, call 0xE938D70, then loads r14/r12 from stack and jumps to 0x6670103 [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5733 | 0x66716ac | `cmp qword ptr [rbp+0x408],0x10` | compare buffer size with 0x10 [V] |
| 5734 | 0x66716b4 | `jb short 0x66716BD` | branch exit 0x66716BD [V] |
| 5735 | 0x66716b6 | `mov rsi,[rbp+0x3F0]` | rsi = stack buffer [V] |
| 5736 | 0x66716bd | `test rdx,rdx` | test length [V] |
| 5737 | 0x66716c0 | `je 0x66717A6` | branch exit 0x66717A6 [V] |
| 5738 | 0x66716c6 | `mov eax,edx` | eax = length [V] |
| 5739 | 0x66716c8 | `and eax,3` | eax &= 3 (remainder) [V] |
| 5740 | 0x66716cb | `cmp rdx,4` | compare length with 4 [V] |
| 5741 | 0x66716cf | `jae 0x6671864` | branch exit 0x6671864 [V] |
| 5742 | 0x66716d5 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5743 | 0x66716df | `xor r8d,r8d` | r8d = 0 [V] |
| 5744 | 0x66716e2 | `jmp 0x66718C0` | branch exit 0x66718C0 [V] |
| 5745 | 0x66716e7 | `mov rdx,0xCBF29CE484222325` | rdx = FNV offset basis [V] |
| 5746 | 0x66716f1 | `jmp short 0x6671765` | branch exit 0x6671765 [V] |
| 5747 | 0x66716f3 | `and r8,0xFFFFFFFFFFFFFFFC` | r8 &= ~3 (aligned length) [V] |
| 5748 | 0x66716f7 | `mov rdx,0xCBF29CE484222325` | rdx = FNV offset basis [V] |
| 5749 | 0x6671701 | `xor r9d,r9d` | r9d = 0 (index) [V] |
| 5750 | 0x6671704 | `movzx r10d,byte ptr [rsi+r9]` | load byte [rsi+r9] [V] |
| 5751 | 0x6671709 | `xor r10,rdx` | xor with hash [V] |
| 5752 | 0x667170c | `imul r10,rcx` | multiply by FNV prime [V] |
| 5753 | 0x6671710 | `movzx edx,byte ptr [rsi+r9+1]` | load byte [rsi+r9+1] [V] |
| 5754 | 0x6671716 | `xor rdx,r10` | xor with hash [V] |
| 5755 | 0x6671719 | `imul rdx,rcx` | multiply by FNV prime [V] |
| 5756 | 0x667171d | `movzx r10d,byte ptr [rsi+r9+2]` | load byte [rsi+r9+2] [V] |
| 5757 | 0x6671723 | `xor r10,rdx` | xor with hash [V] |
| 5758 | 0x6671726 | `imul r10,rcx` | multiply by FNV prime [V] |
| 5759 | 0x667172a | `movzx edx,byte ptr [rsi+r9+3]` | load byte [rsi+r9+3] [V] |
| 5760 | 0x6671730 | `xor rdx,r10` | xor with hash [V] |
| 5761 | 0x6671733 | `imul rdx,rcx` | multiply by FNV prime [V] |
| 5762 | 0x6671737 | `add r9,4` | advance index by 4 [V] |
| 5763 | 0x667173b | `cmp r8,r9` | compare aligned length with index [V] |
| 5764 | 0x667173e | `jne short 0x6671704` | loop back [V] |
| 5765 | 0x6671740 | `test rax,rax` | test remainder count [V] |
| 5766 | 0x6671743 | `je short 0x6671765` | branch exit 0x6671765 [V] |
| 5767 | 0x6671745 | `add rsi,r9` | advance buffer pointer [V] |
| 5768 | 0x6671748 | `xor r8d,r8d` | r8d = 0 [V] |
| 5769 | 0x667174b | `mov r9,rdx` | r9 = current hash [V] |
| 5770 | 0x667174e | `movzx edx,byte ptr [rsi+r8]` | load remainder byte [V] |
| 5771 | 0x6671753 | `xor rdx,r9` | xor with hash [V] |
| 5772 | 0x6671756 | `imul rdx,rcx` | multiply by FNV prime [V] |

**Branch exits:** 0x66716BD (5734), 0x66717A6 (5737), 0x6671864 (5741), 0x66718C0 (5744), 0x6671765 (5746, 5766), 0x6671704 (5764, loop). Calls: none. No description reads.

## NEXT
Resume at listing line 5773. Block 10 (5773..5812) below; next block to append: 5813..5852.

## Block 10 — listing lines 5773..5812 (40 lines)

### lines 5773..5812 (0x667175A..0x6671837)
Remainder-byte FNV-1a loop, stores hash to [0x129F9278], cleanup call 0x73150, call 0xE938D70, loads r15/r12 from stack, jumps to 0x666EFE1 [V]. Then eighth FNV-1a setup begins for [0x129F9288].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5773 | 0x667175a | `inc r8` | increment index [V] |
| 5774 | 0x667175d | `mov r9,rdx` | r9 = updated hash [V] |
| 5775 | 0x6671760 | `cmp rax,r8` | compare remainder count with index [V] |
| 5776 | 0x6671763 | `jne short 0x667174E` | loop back [V] |
| 5777 | 0x6671765 | `mov [0x129F9298],rdx` | store hash to global [V] |
| 5778 | 0x667176c | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |
| 5779 | 0x6671773 | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5780 | 0x6671778 | `lea rcx,[0x129F92A0]` | rcx = global address [V] |
| 5781 | 0x667177f | `call 0xE938D70` | call 0xE938D70 [V] |
| 5782 | 0x6671784 | `mov r14,[rbp+0x650]` | r14 = object pointer [V] |
| 5783 | 0x667178b | `mov r12,[rbp+0x648]` | r12 = stack/object slot [V] |
| 5784 | 0x6671792 | `jmp 0x6670103` | jump to tag handler 0x6670103 [V] |
| 5785 | 0x6671797 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5786 | 0x66717a1 | `jmp 0x6671839` | branch exit 0x6671839 [V] |
| 5787 | 0x66717a6 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5788 | 0x66717b0 | `jmp 0x66718E8` | branch exit 0x66718E8 [V] |
| 5789 | 0x66717b5 | `and rdx,0xFFFFFFFFFFFFFFFC` | rdx &= ~3 (aligned length) [V] |
| 5790 | 0x66717b9 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5791 | 0x66717c3 | `xor r8d,r8d` | r8d = 0 [V] |
| 5792 | 0x66717c6 | `mov r9,0x100000001B3` | r9 = FNV prime [V] |
| 5793 | 0x66717d0 | `movzx r10d,byte ptr [rsi+r8]` | load byte [rsi+r8] [V] |
| 5794 | 0x66717d5 | `xor r10,rcx` | xor with hash [V] |
| 5795 | 0x66717d8 | `imul r10,r9` | multiply by FNV prime [V] |
| 5796 | 0x66717dc | `movzx ecx,byte ptr [rsi+r8+1]` | load byte [rsi+r8+1] [V] |
| 5797 | 0x66717e2 | `xor rcx,r10` | xor with hash [V] |
| 5798 | 0x66717e5 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5799 | 0x66717e9 | `movzx r10d,byte ptr [rsi+r8+2]` | load byte [rsi+r8+2] [V] |
| 5800 | 0x66717ef | `xor r10,rcx` | xor with hash [V] |
| 5801 | 0x66717f2 | `imul r10,r9` | multiply by FNV prime [V] |
| 5802 | 0x66717f6 | `movzx ecx,byte ptr [rsi+r8+3]` | load byte [rsi+r8+3] [V] |
| 5803 | 0x66717fc | `xor rcx,r10` | xor with hash [V] |
| 5804 | 0x66717ff | `imul rcx,r9` | multiply by FNV prime [V] |
| 5805 | 0x6671803 | `add r8,4` | advance index by 4 [V] |
| 5806 | 0x6671807 | `cmp rdx,r8` | compare aligned length with index [V] |
| 5807 | 0x667180a | `jne short 0x66717D0` | loop back [V] |
| 5808 | 0x667180c | `test rax,rax` | test remainder count [V] |
| 5809 | 0x667180f | `je short 0x6671839` | branch exit 0x6671839 [V] |
| 5810 | 0x6671811 | `add rsi,r8` | advance buffer pointer [V] |
| 5811 | 0x6671814 | `xor edx,edx` | edx = 0 [V] |
| 5812 | 0x6671816 | `mov r8,0x100000001B3` | r8 = FNV prime [V] |

**Branch exits:** 0x6670103 (5784), 0x6671839 (5786, 5809), 0x66718E8 (5788), 0x66717D0 (5807, loop). Calls: 0x73150 (5779), 0xE938D70 (5781). No description reads.

## NEXT
Resume at listing line 5813. Block 11 (5813..5852) below; next block to append: 5853..5869.

## Block 11 — listing lines 5813..5852 (40 lines)

### lines 5813..5852 (0x6671820..0x66718DF)
Remainder-byte FNV-1a loop, stores hash to [0x129F9288], cleanup call 0x73150, call 0xE938D70, loads r15 from stack, jumps to 0x666F2F7 [V].

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5813 | 0x6671820 | `mov r9,rcx` | r9 = current hash [V] |
| 5814 | 0x6671823 | `movzx ecx,byte ptr [rsi+rdx]` | load remainder byte [V] |
| 5815 | 0x6671827 | `xor rcx,r9` | xor with hash [V] |
| 5816 | 0x667182a | `imul rcx,r8` | multiply by FNV prime [V] |
| 5817 | 0x667182e | `inc rdx` | increment index [V] |
| 5818 | 0x6671831 | `mov r9,rcx` | r9 = updated hash [V] |
| 5819 | 0x6671834 | `cmp rax,rdx` | compare remainder count with index [V] |
| 5820 | 0x6671837 | `jne short 0x6671823` | loop back [V] |
| 5821 | 0x6671839 | `mov [0x129F9278],rcx` | store hash to global [V] |
| 5822 | 0x6671840 | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |
| 5823 | 0x6671847 | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5824 | 0x667184c | `lea rcx,[0x129F9280]` | rcx = global address [V] |
| 5825 | 0x6671853 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5826 | 0x6671858 | `mov r15,[rbp+0x650]` | r15 = object pointer [V] |
| 5827 | 0x667185f | `jmp 0x666EFE1` | jump to tag handler 0x666EFE1 [V] |
| 5828 | 0x6671864 | `and rdx,0xFFFFFFFFFFFFFFFC` | rdx &= ~3 (aligned length) [V] |
| 5829 | 0x6671868 | `mov rcx,0xCBF29CE484222325` | rcx = FNV offset basis [V] |
| 5830 | 0x6671872 | `xor r8d,r8d` | r8d = 0 [V] |
| 5831 | 0x6671875 | `mov r9,0x100000001B3` | r9 = FNV prime [V] |
| 5832 | 0x667187f | `movzx r10d,byte ptr [rsi+r8]` | load byte [rsi+r8] [V] |
| 5833 | 0x6671884 | `xor r10,rcx` | xor with hash [V] |
| 5834 | 0x6671887 | `imul r10,r9` | multiply by FNV prime [V] |
| 5835 | 0x667188b | `movzx ecx,byte ptr [rsi+r8+1]` | load byte [rsi+r8+1] [V] |
| 5836 | 0x6671891 | `xor rcx,r10` | xor with hash [V] |
| 5837 | 0x6671894 | `imul rcx,r9` | multiply by FNV prime [V] |
| 5838 | 0x6671898 | `movzx r10d,byte ptr [rsi+r8+2]` | load byte [rsi+r8+2] [V] |
| 5839 | 0x667189e | `xor r10,rcx` | xor with hash [V] |
| 5840 | 0x66718a1 | `imul r10,r9` | multiply by FNV prime [V] |
| 5841 | 0x66718a5 | `movzx ecx,byte ptr [rsi+r8+3]` | load byte [rsi+r8+3] [V] |
| 5842 | 0x66718ab | `xor rcx,r10` | xor with hash [V] |
| 5843 | 0x66718ae | `imul rcx,r9` | multiply by FNV prime [V] |
| 5844 | 0x66718b2 | `add r8,4` | advance index by 4 [V] |
| 5845 | 0x66718b6 | `cmp rdx,r8` | compare aligned length with index [V] |
| 5846 | 0x66718b9 | `jne short 0x667187F` | loop back [V] |
| 5847 | 0x66718bb | `test rax,rax` | test remainder count [V] |
| 5848 | 0x66718be | `je short 0x66718E8` | branch exit 0x66718E8 [V] |
| 5849 | 0x66718c0 | `add rsi,r8` | advance buffer pointer [V] |
| 5850 | 0x66718c3 | `xor edx,edx` | edx = 0 [V] |
| 5851 | 0x66718c5 | `mov r8,0x100000001B3` | r8 = FNV prime [V] |
| 5852 | 0x66718cf | `mov r9,rcx` | r9 = current hash [V] |

**Branch exits:** 0x666EFE1 (5827), 0x66718E8 (5848), 0x667187F (5846, loop), 0x6671823 (5820, loop). Calls: 0x73150 (5823), 0xE938D70 (5825). No description reads.

## NEXT
Resume at listing line 5853. Block 12 (5853..5869) below; next block to append: (none — end of file).

## Block 12 — listing lines 5853..5869 (17 lines)

### lines 5853..5869 (0x66718D2..0x667191B)
Remainder-byte FNV-1a loop, stores hash to [0x129F9288], cleanup call 0x73150, call 0xE938D70, loads r15 from stack, jumps to 0x666F2F7 [V]. Then final code: `mov rcx,rdi`, `call 0x9BC830`, `int3` (end of listing).

| line | 0xRVA | `instruction` | note |
|---|---|---|---|
| 5853 | 0x66718d2 | `movzx ecx,byte ptr [rsi+rdx]` | load remainder byte [V] |
| 5854 | 0x66718d6 | `xor rcx,r9` | xor with hash [V] |
| 5855 | 0x66718d9 | `imul rcx,r8` | multiply by FNV prime [V] |
| 5856 | 0x66718dd | `inc rdx` | increment index [V] |
| 5857 | 0x66718e0 | `mov r9,rcx` | r9 = updated hash [V] |
| 5858 | 0x66718e3 | `cmp rax,rdx` | compare remainder count with index [V] |
| 5859 | 0x66718e6 | `jne short 0x66718D2` | loop back [V] |
| 5860 | 0x66718e8 | `mov [0x129F9288],rcx` | store hash to global [V] |
| 5861 | 0x66718ef | `lea rcx,[rbp+0x3F0]` | rcx = stack buffer [V] |
| 5862 | 0x66718f6 | `call 0x73150` | call 0x73150 (cleanup) [V] |
| 5863 | 0x66718fb | `lea rcx,[0x129F9290]` | rcx = global address [V] |
| 5864 | 0x6671902 | `call 0xE938D70` | call 0xE938D70 [V] |
| 5865 | 0x6671907 | `mov r15,[rbp+0x650]` | r15 = object pointer [V] |
| 5866 | 0x667190e | `jmp 0x666F2F7` | jump to tag handler 0x666F2F7 [V] |
| 5867 | 0x6671913 | `mov rcx,rdi` | rcx = rdi [V] |
| 5868 | 0x6671916 | `call 0x9BC830` | call 0x9BC830 [V] |
| 5869 | 0x667191b | `int3` | breakpoint / end of function [V] |

**Branch exits:** 0x666F2F7 (5866), 0x66718D2 (5859, loop). Calls: 0x73150 (5862), 0xE938D70 (5864), 0x9BC830 (5868). No description reads.

## NEXT
Resume at: end of file (line 5869). No more blocks.

---

## Tag-7 body end

The tag-7 (FullscreenEffect) body ends at listing line 4252 (RVA 0x666FBBB area) with the epilogue jump `jmp 0x6670032` [V], as recorded in oc_U-FX4. Lines 4253..5869 (this unit's range 5413..5869 included) are cold-path branch targets and jump-table cases for OTHER tags, not tag-7 code.

The trailing code in lines 5413..5869 consists of nine FNV-1a hash computations (constants 0xCBF29CE484222325 and 0x100000001B3 [V]) storing hashes to globals [0x129FA0E8], [0x129FA0F8], [0x129FA148], [0x129FA158], [0x129FA168], [0x129FA120], [0x129F9298], [0x129F9278], [0x129F9288] [V], each followed by cleanup call 0x73150, call 0xE938D70, and a jump to a tag handler:
- 0x666B6AA (line 5505), 0x666B6CF (line 5544), 0x666C91E (line 5582), 0x666C943 (line 5620), 0x666C968 (line 5658), 0x666CFE1 (line 5696), 0x666EFE1 (lines 5704, 5827), 0x6670103 (line 5784), 0x666F2F7 (lines 5726, 5866)

The file ends at line 5869 (RVA 0x667191B) with `int3` [V], preceded by `mov rcx,rdi` (line 5867) and `call 0x9BC830` (line 5868) [V] — these are likely the final tag-case epilogue or a separate function's tail. The tag-7 body itself does not extend into this range; its confirmed end is line 4252 `jmp 0x6670032` [V] per oc_U-FX4.
