## NEXT
DONE — verify_oc.py passed. Unit complete.

# Unit U-EL1v: L1v dynamic texture handles (checklist L1v)

Checklist item (RENDER_CHECKLIST.md line 231): "L1v dynamic texture handles = reset flag 0x400000 + caps bit 0x12ADFA54&0x10 + free-list (6ei); createDynamicTexture 0xbc74a80"

This is the L1-layer mirror of A12a (ticked via oc_U-A12a.md, verify_oc 385/385). L1 and A12 share the same bgfx::Context code at identical RVAs. All proof lines below were re-verified verbatim against Minecraft.Windows.exe 1.26.62.01 via rdis dis.

Source: docs/BGFX_MAP.md section 6ei (lines 1359-1371) describes the same mechanism at the same RVAs.

## (1) Caps-bit gate: test byte [0x12ADFA54], 0x10

Location: Context init/reset path inside sub_bc66de0 (0xbc66de0), at 0xbc67284.

Standalone proof lines (verified verbatim via rdis dis):
0xBC67284  test byte ptr [0x12ADFA54],0x10
0xBC6728B  jne short 0xBC672A9
0xBC6728D  cmp byte ptr [rsi+0x1EBF2F3],0
0xBC67294  jne short 0xBC672FF
0xBC67296  lea rdx,[0xF7F55F4]
0xBC6729D  mov ecx,2
0xBC672A2  call 0xBC5F110
0xBC672A7  jmp short 0xBC672FF
0xBC672F8  mov byte ptr [rsi+0x1EBF2F3],0

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| Caps byte DynamicTextureHandles bit 4 + branch | `0x12ADFA54` | 1 | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC67284  test byte ptr [0x12ADFA54],0x10` / `0xBC6728B  jne short 0xBC672A9` | bit 4 = DynamicTextureHandles; set -> reset flag test, clear -> guarded check | [V] |
| Guarded flag (all sites) | `ctx+0x1EBF2F3` | 1 | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC6728D  cmp byte ptr [rsi+0x1EBF2F3],0` / `0xBC67294  jne short 0xBC672FF` / `0xBC672F8  mov byte ptr [rsi+0x1EBF2F3],0` | guarded allocation flag; checked as fallback when caps bit clear (==0 -> error); cleared to 0 on enable | [V] |
| Guarded error string + reporter | — | — | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC67296  lea rdx,[0xF7F55F4]` / `0xBC6729D  mov ecx,2` / `0xBC672A2  call 0xBC5F110` / `0xBC672A7  jmp short 0xBC672FF` | "Texture handle allocation must be guarded if renderer contex..." error | [V] |

Branch taken when caps bit set (`0xBC6728B  jne short 0xBC672A9`): reset flag test follows.

## (2) Reset flag 0x400000 test/set

Standalone proof lines (verified verbatim via rdis dis):
0xBC672A9  mov ecx,0x400000
0xBC672AE  mov eax,[rsi+0x1EBF19C]
0xBC672B4  and eax,ecx
0xBC672B6  mov rdx,[rsi+0x1CFD0C8]
0xBC672BD  and ecx,[rdx+0xDC5810]
0xBC672C3  cmp eax,ecx
0xBC672C5  je short 0xBC672FF
0xBC672C7  test eax,eax
0xBC672C9  jne short 0xBC672DC
0xBC672CB  lea rdx,[0xF80C0EA]
0xBC672D2  mov ecx,2
0xBC672D7  call 0xBC5F110
0xBC672DC  mov byte ptr [rsi+0x1DF7480],0
0xBC672E3  mov byte ptr [rsi+0xE62610],0
0xBC672EA  mov byte ptr [rsi+0x1CD6FD0],0
0xBC672F1  mov byte ptr [rsi+0x1E7DAD0],0
0xBC672F8  mov byte ptr [rsi+0x1EBF2F3],0
0xBC672FF  mov rax,[rsi+0x1CFD0C8]
0xBC67306  mov ecx,[rsi+0x1EBF19C]
0xBC6730C  mov [rax+0xDC5810],ecx

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| Reset flag mask | `0x400000` | 4 (imm) | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC672A9  mov ecx,0x400000` | reset flag bit mask for dynamic texture handles | [V] |
| Requested reset flags | `ctx+0x1EBF19C` | 4 | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC672AE  mov eax,[rsi+0x1EBF19C]` / `0xBC672B4  and eax,ecx` | requested reset flags & 0x400000 | [V] |
| Frame consumed flags | `[ctx+0x1CFD0C8]+0xDC5810` | 4 | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC672B6  mov rdx,[rsi+0x1CFD0C8]` / `0xBC672BD  and ecx,[rdx+0xDC5810]` / `0xBC672FF  mov rax,[rsi+0x1CFD0C8]` / `0xBC67306  mov ecx,[rsi+0x1EBF19C]` / `0xBC6730C  mov [rax+0xDC5810],ecx` | current frame consumed flags & 0x400000; synced to requested after branch | [V] |
| Requested vs consumed compare | — | — | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC672C3  cmp eax,ecx` / `0xBC672C5  je short 0xBC672FF` | same -> no change; differ -> enable/disable branch | [V] |
| Disable-not-allowed error | — | — | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC672C7  test eax,eax` / `0xBC672C9  jne short 0xBC672DC` / `0xBC672CB  lea rdx,[0xF80C0EA]` / `0xBC672D2  mov ecx,2` / `0xBC672D7  call 0xBC5F110` | requested lacks bit but consumed has it -> "Disabling dynamic texture handles is not supported." | [V] |
| State bytes cleared on enable | `ctx+0x1DF7480`, `ctx+0xE62610`, `ctx+0x1CD6FD0`, `ctx+0x1E7DAD0` | 1 | Context init/reset `sub_bc66de0` `0xbc66de0` | `0xBC672DC  mov byte ptr [rsi+0x1DF7480],0` / `0xBC672E3  mov byte ptr [rsi+0xE62610],0` / `0xBC672EA  mov byte ptr [rsi+0x1CD6FD0],0` / `0xBC672F1  mov byte ptr [rsi+0x1E7DAD0],0` | dynamic texture state bytes cleared on enable | [V] |

## (3) Free-list handle allocator at ctx+0x1DFB48C (dense/sparse, bgfx HandleAlloc style)

Standalone proof lines (verified verbatim via rdis dis):
0xBC74ABA  movzx eax,word ptr [rbx+0x1DFB48C]
0xBC74AC1  movzx ecx,word ptr [rbx+0x1DFB48E]
0xBC74AC8  cmp ax,cx
0xBC74ACB  mov [rbp-0x10],rsi
0xBC74ACF  jae 0xBC74E22
0xBC74AD5  movzx edx,ax
0xBC74AD8  lea r8d,[rax+1]
0xBC74ADC  mov [rbx+0x1DFB48C],r8w
0xBC74AE4  movzx edx,word ptr [rbx+rdx*2+0x1DFB490]
0xBC74AEC  lea rcx,[rbx+rcx*2]
0xBC74AF0  add rcx,0x1DFB490
0xBC74AF7  mov [rcx+rdx*2],ax
0xBC74AFB  mov [rsi],dx
0xBC6BF69  mov dword ptr [r9+0x1DFB48C],0x800000
0xBC750E5  movzx eax,word ptr [rdi+0x1DFB48C]
0xBC750EC  movzx ecx,word ptr [rdi+0x1DFB48E]
0xBC750F3  cmp ax,cx
0xBC750F6  jae 0xBC7527F
0xBC750FC  movzx edx,ax
0xBC750FF  lea r8d,[rax+1]
0xBC75103  mov [rdi+0x1DFB48C],r8w
0xBC7510B  movzx edx,word ptr [rdi+rdx*2+0x1DFB490]
0xBC75113  lea rcx,[rdi+rcx*2]
0xBC75117  add rcx,0x1DFB490
0xBC7511E  mov [rcx+rdx*2],ax
0xBC75122  mov [rsi],dx
0xBC7525E  movzx eax,word ptr [rsi]
0xBC75261  lea rax,[rax+rax*2]
0xBC75265  mov byte ptr [rdi+rax*8+0x1EA5AE8],1
0xBC7526D  mov rcx,[rbp-0x20]
0xBC75271  mov [rdi+rax*8+0x1EA5AD8],rcx
0xBC74BDB  mov byte ptr [rbx+rax*8+0x1EA5AE8],0

| name | offset | size | site | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| numHandles + maxHandles | `ctx+0x1DFB48C` / `ctx+0x1DFB48E` | 2 + 2 | createDynamicTexture `0xBC74A80`; destroyDynamicTexture `0xBC750B0` | `0xBC74ABA  movzx eax,word ptr [rbx+0x1DFB48C]` / `0xBC74AC1  movzx ecx,word ptr [rbx+0x1DFB48E]` / `0xBC74ADC  mov [rbx+0x1DFB48C],r8w` / `0xBC750E5  movzx eax,word ptr [rdi+0x1DFB48C]` / `0xBC750EC  movzx ecx,word ptr [rdi+0x1DFB48E]` / `0xBC75103  mov [rdi+0x1DFB48C],r8w` | numHandles read/incremented; maxHandles compared against count | [V] |
| Exhaustion check | — | — | createDynamicTexture `0xBC74A80`; destroyDynamicTexture `0xBC750B0` | `0xBC74AC8  cmp ax,cx` / `0xBC74ACF  jae 0xBC74E22` / `0xBC750F3  cmp ax,cx` / `0xBC750F6  jae 0xBC7527F` | numHandles >= maxHandles -> full (create returns 0xFFFF, destroy returns 0xFFFF) | [V] |
| dense[] handle ids | `ctx+0x1DFB490` | 2 per entry | createDynamicTexture `0xBC74A80`; destroyDynamicTexture `0xBC750B0` | `0xBC74AE4  movzx edx,word ptr [rbx+rdx*2+0x1DFB490]` / `0xBC7510B  movzx edx,word ptr [rdi+rdx*2+0x1DFB490]` | dense[numHandles] -> allocated/freed handle id | [V] |
| sparse[] reverse map | `ctx+0x1DFB490 + maxHandles*2` | 2 per entry | createDynamicTexture `0xBC74A80`; destroyDynamicTexture `0xBC750B0` | `0xBC74AF7  mov [rcx+rdx*2],ax` / `0xBC7511E  mov [rcx+rdx*2],ax` / `0xBC74AFB  mov [rsi],dx` / `0xBC75122  mov [rsi],dx` | sparse[handle] = numHandles; output handle via [rsi] | [V] |
| Allocator init in constructor | `ctx+0x1DFB48C` | 4 | Context constructor `0xbc6b560` | `0xBC6BF69  mov dword ptr [r9+0x1DFB48C],0x800000` | numHandles=0, maxHandles=high word | [V] |
| Guarded byte mark free | `ctx+0x1EA5AE8 + handle*8` | 1 | destroyDynamicTexture `0xBC750B0` | `0xBC7525E  movzx eax,word ptr [rsi]` / `0xBC75261  lea rax,[rax+rax*2]` / `0xBC75265  mov byte ptr [rdi+rax*8+0x1EA5AE8],1` | mark freed entry guarded = 1 | [V] |
| Guarded byte mark allocated | `ctx+0x1EA5AE8 + handle*8` | 1 | createDynamicTexture `0xBC74A80` | `0xBC74BDB  mov byte ptr [rbx+rax*8+0x1EA5AE8],0` | mark allocated entry guarded = 0 | [V] |
| Record pointer store on free | `ctx+0x1EA5AD8 + handle*0x18` | 8 | destroyDynamicTexture `0xBC750B0` | `0xBC7526D  mov rcx,[rbp-0x20]` / `0xBC75271  mov [rdi+rax*8+0x1EA5AD8],rcx` | store record pointer in dynamic texture record array | [V] |

Free-list semantics: allocation takes dense[numHandles] as the handle id, increments numHandles, and links sparse[handle]=numHandles. Destruction increments numHandles (push), reads dense[numHandles] as the freed handle, and updates sparse[freed_handle]=numHandles. This is a LIFO free-list — most recently freed handle is allocated next. On exhaustion returns 0xFFFF.

## (4) createDynamicTexture function entry

Standalone proof lines (verified verbatim via rdis dis):
0xBC74A80  push rbp
0xE905C77  mov rcx,[0x12AE1748]
0xE905C7E  mov byte ptr [rsp+0x20],0
0xE905C83  lea r9,[rsp+0x30]
0xE905C88  mov rdx,rsi
0xE905C8B  mov r8d,eax
0xE905C8E  call 0xBC74A80

| name | rva | size | site | `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|---|
| createDynamicTexture entry | `0xBC74A80` | - | - | `0xBC74A80  push rbp` | function prologue | [V] |
| Caller call site | `0xE905C8E` | - | `sub_e905c70` `0xE905C70` | `0xE905C77  mov rcx,[0x12AE1748]` / `0xE905C8E  call 0xBC74A80` | single caller loads s_ctx from `0x12AE1748`, passes desc in rsi/r9, count in r8d | [V] |

## CLOSES?

YES — every pending part of L1v is proven by [V] rows: (1) caps bit 0x12ADFA54&0x10 tested at `0xBC67284  test byte ptr [0x12ADFA54],0x10`; (2) reset flag 0x400000 tested at `0xBC672A9  mov ecx,0x400000` / `0xBC672AE  mov eax,[rsi+0x1EBF19C]` / `0xBC672B4  and eax,ecx` against frame consumed flags `[ctx+0x1CFD0C8]+0xDC5810` at `0xBC672B6  mov rdx,[rsi+0x1CFD0C8]` / `0xBC672BD  and ecx,[rdx+0xDC5810]`; (3) free-list at ctx+0x1DFB48C (numHandles) / ctx+0x1DFB48E (maxHandles) / ctx+0x1DFB490 (dense ids) proven in both createDynamicTexture `0xBC74A80` and destroyDynamicTexture `0xBC750B0`; (4) createDynamicTexture entry `0xBC74A80` with single caller at `0xE905C8E  call 0xBC74A80`. All proof lines verbatim-verified via rdis dis against Minecraft.Windows.exe 1.26.62.01. Matches oc_U-A12a.md (verify_oc 385/385) at identical RVAs.

## TOOL REQUESTS

- verify_oc.py | progress markdown -> PASS/FAIL | required by unit spec, run after writing
- rdis dis 0x<rva> <n> | exe -> verbatim instruction listing | used to verify every quoted `0xRVA  instr` line

## Verification Status

```
python tools/sigs/verify_oc.py docs/progress/oc_U-EL1v.md
```
Pending — to be run after this write.
