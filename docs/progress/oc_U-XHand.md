## NEXT
DONE

# U-XHand: ItemInHand extractor 0x6698E30 — description read list

## tag 0 (description pointer = r14; r8 copied at entry `0x6698e7a  mov r14,r8`)
| offset | size | read address | verbatim instruction | meaning |
|---|---|---|---|---|
| 0x0 | 8 | 0x66992f7, 0x6699311, 0x6699483, 0x669949d, 0x6699567, 0x6699581, 0x6699698, 0x66996b2, 0x6699745, 0x669975b, 0x669aaeb, 0x669ab05, 0x669b1f8, 0x669b687, 0x669b69d, 0x669b6ef, 0x669b705, 0x669bc99, 0x669bcaf, 0x669bd05, 0x669bd1b, 0x669bd30, 0x669bd46 | `0x66992f7  mov rax,[r14]` | - [UNVERIFIED: r14 reused] |
| 0x8 | 4 | 0x66992ec, 0x6699478, 0x669955c, 0x669968d, 0x669973e, 0x669aae0, 0x669b420, 0x669b680, 0x669b6e8, 0x669b8ca, 0x669bade, 0x669bb64, 0x669bc2c, 0x669bc92, 0x669bcfa, 0x669bcfe | `0x66992ec  lock dec dword ptr [r14+8]` | atomic decrement (counter) [V]; sites 0x669b8ca, 0x669bade, 0x669bb64, 0x669bc2c are lock inc (atomic increment) [V]; 0x669b420 mov r12,[r14+8] reads 8 bytes; 0x669bcfa lea rsi,[r14+8] computes the address, no memory read [UNVERIFIED: r14 reused] |
| 0xC | 4 | 0x6699306, 0x6699492, 0x6699576, 0x66996a7, 0x6699754, 0x669aafa, 0x669b696, 0x669b6fe, 0x669bca8, 0x669bd14, 0x669bd3f | `0x6699306  lock dec dword ptr [r14+0xC]` | atomic decrement (counter) [V] [UNVERIFIED: r14 reused] |
| 0x18 | 1 | 0x669b419 | `0x669b419  cmp byte ptr [r14+0x18],2` | compare byte with 2 [V] [UNVERIFIED: r14 reused] |
| 0x28 | 8 | 0x6698ede, 0x669b15d | `0x6698ede  mov rax,[r14+0x28]` | - [UNVERIFIED: r14 reused] |
| 0x38 | 4 | 0x669b04a | `0x669b04a  movss xmm0,[r14+0x38]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x3C | 4 | 0x669b054 | `0x669b054  movss xmm0,[r14+0x3C]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x40 | 4 | 0x669b05f | `0x669b05f  movss xmm0,[r14+0x40]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x44 | 4 | 0x669b06a | `0x669b06a  movss xmm0,[r14+0x44]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x48 | 4 | 0x669b075 | `0x669b075  movss xmm0,[r14+0x48]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x4C | 4 | 0x669b080 | `0x669b080  movss xmm0,[r14+0x4C]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x50 | 4 | 0x669b08b | `0x669b08b  movss xmm0,[r14+0x50]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x54 | 4 | 0x669b096 | `0x669b096  movss xmm0,[r14+0x54]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x58 | 8 | 0x66997be, 0x669b0a1 | `0x66997be  sub rax,[r14+0x58]` | rax -= 8-byte value at +0x58 [V]; site 0x669b0a1 movss xmm0,[r14+0x58] reads 4 bytes (float) [V] [UNVERIFIED: r14 reused] |
| 0x5C | 4 | 0x669b0ac | `0x669b0ac  movss xmm0,[r14+0x5C]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x60 | 8 | 0x66997ba, 0x669b0b7 | `0x66997ba  mov rax,[r14+0x60]` | - ; site 0x669b0b7 movss xmm0,[r14+0x60] reads 4 bytes (float) [V] [UNVERIFIED: r14 reused] |
| 0x64 | 4 | 0x669b0c2 | `0x669b0c2  movss xmm0,[r14+0x64]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x68 | 4 | 0x669b0cd | `0x669b0cd  movss xmm0,[r14+0x68]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x6C | 4 | 0x669b0d8 | `0x669b0d8  movss xmm0,[r14+0x6C]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x70 | 4 | 0x669b0e3 | `0x669b0e3  movss xmm0,[r14+0x70]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x74 | 4 | 0x669b0ee | `0x669b0ee  movss xmm0,[r14+0x74]` | load float [V] [UNVERIFIED: r14 reused] |
| 0x78 | 1 | 0x669b133 | `0x669b133  movzx eax,byte ptr [r14+0x78]` | - [UNVERIFIED: r14 reused] |
| 0x7A | 1 | 0x6698ead, 0x669b13d | `0x6698ead  movzx ecx,byte ptr [r14+0x7A]` | - [UNVERIFIED: r14 reused] |
| 0x11C | 2 | 0x669b1ac | `0x669b1ac  movzx eax,word ptr [r14+0x11C]` | - [UNVERIFIED: r14 reused] |
| 0x158 | 16 | 0x669b1c2 | `0x669b1c2  movups xmm0,[r14+0x158]` | - [UNVERIFIED: r14 reused] |
| 0x168 | 8 | 0x669b1d1 | `0x669b1d1  movsd xmm0,[r14+0x168]` | load double [V] [UNVERIFIED: r14 reused] |
| 0x170 | 16 | 0x669b1e2 | `0x669b1e2  movups xmm0,[r14+0x170]` | - [UNVERIFIED: r14 reused] |
| 0x1D0 | 4 | 0x669980f | `0x669980f  mov ecx,[r14+0x1D0]` | - [UNVERIFIED: r14 reused] |
| 0x1D4 | 1 | 0x6699805 | `0x6699805  cmp byte ptr [r14+0x1D4],0` | test byte == 0 [V] [UNVERIFIED: r14 reused] |

Notes:
- Sizes come from the instruction (movups 16, movsd/mov rax 8, dword/movss/mov ecx 4, word 2, byte 1).
- Rows 0x8, 0x58, 0x60 have mixed sizes across their sites; the size column is the first (verbatim) instruction's size, and the other sites' sizes are stated in the meaning column.
- Every row is a distinct [r14+off] offset (29 offsets, 80 read lines from docs/progress/_x_hand_data.txt).

## verbatim first instructions (one per distinct offset, from docs/progress/_x_hand_data.txt)
0x66992f7  mov rax,[r14]
0x66992ec  lock dec dword ptr [r14+8]
0x6699306  lock dec dword ptr [r14+0xC]
0x669b419  cmp byte ptr [r14+0x18],2
0x6698ede  mov rax,[r14+0x28]
0x669b04a  movss xmm0,[r14+0x38]
0x669b054  movss xmm0,[r14+0x3C]
0x669b05f  movss xmm0,[r14+0x40]
0x669b06a  movss xmm0,[r14+0x44]
0x669b075  movss xmm0,[r14+0x48]
0x669b080  movss xmm0,[r14+0x4C]
0x669b08b  movss xmm0,[r14+0x50]
0x669b096  movss xmm0,[r14+0x54]
0x66997be  sub rax,[r14+0x58]
0x669b0ac  movss xmm0,[r14+0x5C]
0x66997ba  mov rax,[r14+0x60]
0x669b0c2  movss xmm0,[r14+0x64]
0x669b0cd  movss xmm0,[r14+0x68]
0x669b0d8  movss xmm0,[r14+0x6C]
0x669b0e3  movss xmm0,[r14+0x70]
0x669b0ee  movss xmm0,[r14+0x74]
0x669b133  movzx eax,byte ptr [r14+0x78]
0x6698ead  movzx ecx,byte ptr [r14+0x7A]
0x669b1ac  movzx eax,word ptr [r14+0x11C]
0x669b1c2  movups xmm0,[r14+0x158]
0x669b1d1  movsd xmm0,[r14+0x168]
0x669b1e2  movups xmm0,[r14+0x170]
0x669980f  mov ecx,[r14+0x1D0]
0x6699805  cmp byte ptr [r14+0x1D4],0


## writes to the register (r14)
The data file lists 25 instructions that overwrite r14 (first is the entry copy `0x6698e7a  mov r14,r8`; every later one, starting at `0x6698f57  mov r14d,2`, means the description is NOT in r14 on that path). Reads at an address after such an overwrite are flagged as possibly reading a different object. Only two read sites precede the first overwrite and are not flagged: 0x6698ead (offset 0x7A) and 0x6698ede (offset 0x28). Every table row above contains at least one flagged site, so all 29 rows are marked [UNVERIFIED: r14 reused]. Flagged read lines: all read sites except 0x6698ead and 0x6698ede.

## TOOL REQUESTS
None
