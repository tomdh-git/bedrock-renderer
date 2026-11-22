## NEXT
DONE

# U-EQ2e — Q2e Encoder::discard / RenderBind grow / side-table copy

GOAL: Close checklist item Q2e (docs/RENDER_CHECKLIST.md line 569): "Encoder::discard / RenderBind grow / side-table copy".

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01); every RVA below is a 1.26.62.01 image RVA.
TAGS: [V] = I saw the exact instruction in rdis output of this exe and re-checked it with verify_oc; [I] = meaning inferred from cross-referenced dossiers, not an offset claim.

STATUS: verifying the three sub-parts with my own rdis reads and verbatim proof lines:
- (a) Encoder::discard 0xbc60d10 — below
- (b) RenderBind grow / GuardedPagedArray::ensure 0xbc7a7c0 — below
- (c) per-draw side table copy 0xbc60f10 — below

## (1) What changed
- Created: docs/progress/oc_U-EQ2e.md (this note): verified field map + proof table for Q2e.
- No other file touched: no exe, no HookManager.cpp/hook registration, no CMake, no Sigs.json edit, no src/ edits, no build, no commit. No new src/ files needed — the deliverable is the verified record below.

## (2) Proof table — one row per distinct offset, all sites of that offset listed, size from the instruction

### (a) Encoder::discard 0xbc60d10 (Encoder object, this=rcx; rsi=rcx alias)

| offset | size | site(s) | verbatim `0xRVA  instr` | meaning | tag |
| enc+0x6AD m_discard flag | 1 | 0xbc60d21 | `0xbc60d21  mov byte ptr [rcx+0x6AD],0` | discard flag = 0 | [V] |
| enc+0x60 draw state u64 | 8 | 0xbc60d32 | `0xbc60d32  mov [rcx+0x60],rax` | state = 0x01000050000001F default | [V] |
| enc+0x68 state2 u64 | 8 | 0xbc60d36 | `0xbc60d36  mov qword ptr [rcx+0x68],0` | state2 = 0 | [V] |
| enc+0x70 transform block | 16 | 0xbc60d41 | `0xbc60d41  movaps [rcx+0x70],xmm0` | 16 bytes zeroed | [V] |
| enc+0x80 rect/default 16B | 16 | 0xbc60d4c | `0xbc60d4c  movaps [rcx+0x80],xmm0` | copied from rodata 0xF08EF70 | [V] |
| enc+0x90 | 8 | 0xbc60d5d | `0xbc60d5d  mov [rcx+0x90],rax` | = 0x100000000 | [V] |
| enc+0x98 | 8 | 0xbc60d6e | `0xbc60d6e  mov [rcx+0x98],rax` | = 0x1FFFF00000000 | [V] |
| enc+0xA2 | 1 | 0xbc60d75 | `0xbc60d75  mov byte ptr [rcx+0xA2],0` | = 0 | [V] |
| enc+0xA0 | 2 | 0xbc60d7c | `0xbc60d7c  mov word ptr [rcx+0xA0],0xFFFF` | = 0xFFFF | [V] |
| enc+0xA3 | 2 | 0xbc60d85 | `0xbc60d85  mov word ptr [rcx+0xA3],0xFF00` | = 0xFF00 | [V] |
| enc+0x40 draw start | 8 | 0xbc60d98 | `0xbc60d98  mov [rcx+0x40],rax` | = 0xFFFFFFFF00000000 | [V] |
| enc+0xB4 | 8 | 0xbc60d9c | `0xbc60d9c  mov qword ptr [rcx+0xB4],0xFFFFFFFFFFFFFFFF` | = ~0 | [V] |
| enc+0xA8 | 4 | 0xbc60da7 | `0xbc60da7  mov dword ptr [rcx+0xA8],0x7FFFFFFF` | depth/clear = 0x7FFFFFFF | [V] |
| enc+0xAC | 8 | 0xbc60db1 | `0xbc60db1  mov qword ptr [rcx+0xAC],0` | = 0 | [V] |
| enc+0xC0 compute block | 8 | 0xbc60dbc | `0xbc60dbc  mov qword ptr [rcx+0xC0],0` | = 0 (start of +0xC0..+0xE3 block) | [V] |
| enc+0xC8 | 4 | 0xbc60dc7 | `0xbc60dc7  mov dword ptr [rcx+0xC8],0` | = 0 | [V] |
| enc+0xD0 | 8 | 0xbc60dd1 | `0xbc60dd1  mov qword ptr [rcx+0xD0],0` | = 0 | [V] |
| enc+0xD8 | 4 | 0xbc60ddc | `0xbc60ddc  mov dword ptr [rcx+0xD8],0` | = 0 | [V] |
| enc+0xE0 | 2 | 0xbc60de6 | `0xbc60de6  mov word ptr [rcx+0xE0],0` | = 0 | [V] |
| enc+0xE2 | 1 | 0xbc60def | `0xbc60def  mov byte ptr [rcx+0xE2],0xFF` | = 0xFF | [V] |
| enc+0xCC | 2 | 0xbc60df6 | `0xbc60df6  mov word ptr [rcx+0xCC],0xFFFF` | = 0xFFFF | [V] |
| enc+0xDC | 4 | 0xbc60dff | `0xbc60dff  mov dword ptr [rcx+0xDC],0xFFFF0000` | = 0xFFFF0000 | [V] |
| enc+0xE3 | 1 | 0xbc60e09 | `0xbc60e09  mov byte ptr [rcx+0xE3],0` | = 0 | [V] |
| enc+0x140+b*0x14+0x00 bind field | 4 | 0xbc60e2c, 0xbc60e4f | `0xbc60e2c  mov dword ptr [rsi+rax-0x27],0` · `0xbc60e4f  mov dword ptr [rsi+rax-0x13],0` | binding dword field = 0 | [V] |
| enc+0x140+b*0x14+0x0A bind idx u16 | 2 | 0xbc60e20, 0xbc60e44 | `0xbc60e20  mov word ptr [rsi+rax-0x1D],0xFFFF` · `0xbc60e44  mov word ptr [rsi+rax-9],0xFFFF` | bind idx = 0xFFFF (unbound) | [V] |
| enc+0x140+b*0x14+0x0C bind extra | 4 | 0xbc60e34, 0xbc60e57 | `0xbc60e34  mov dword ptr [rsi+rax-0x1B],0xFFFFFFFF` · `0xbc60e57  mov dword ptr [rsi+rax-7],0xFFFFFFFF` | bind extra = 0xFFFFFFFF | [V] |
| enc+0x140+b*0x14+0x13 bind type u8 | 1 | 0xbc60e27, 0xbc60e4b | `0xbc60e27  mov byte ptr [rsi+rax-0x14],0` · `0xbc60e4b  mov byte ptr [rsi+rax],0` | bind type = 0 (unbound) | [V] |
| enc+0x140 bind loop bound | - | 0xbc60e3c | `0xbc60e3c  cmp rax,0x667` | stride 0x28 per iteration (2 bindings); loop runs 0x167..0x63F | [V] |
| enc+0x680 side-table ptr | 8 | 0xbc60e65 | `0xbc60e65  mov rdi,[rsi+0x680]` | SideTable* read | [V] |
| side-table entry zeroed | 16 | 0xbc60ebe | `0xbc60ebe  movups [r14],xmm6` | each 0x10-byte entry zeroed | [V] |
| side-table entry loop bound | - | 0xbc60ec6 | `0xbc60ec6  cmp rbx,0x410` | 0x41 entries × 0x10 bytes | [V] |
| side-table used count | 4 | 0xbc60eec | `0xbc60eec  mov dword ptr [rdi+0x410],0` | used = 0 | [V] |
| enc+0x688 bindDirty flag | 1 | 0xbc60ef6 | `0xbc60ef6  mov byte ptr [rsi+0x688],1` | bindDirty = 1 | [V] |

### (b) RenderBind grow 0xbc7a7c0 (GuardedPagedArray at Frame+0x8B4700; rcx=array, rsi=array alias; element = 0x540-byte RenderBind record)

| offset | size | site(s) | verbatim `0xRVA  instr` | meaning | tag |
| gpa+0x00 base ptr | 8 | 0xbc7a84e | `0xbc7a84e  mov rdi,[rsi]` | committed base read | [V] |
| gpa+0x08 maxCount u32 | 4 | 0xbc7a7df, 0xbc7a919 | `0xbc7a7df  cmp edx,[rcx+8]` · `0xbc7a919  mov edi,[rsi+8]` | maxCount; idx >= maxCount -> fail_fast | [V] |
| gpa+0x10 reservedBytes | 8 | 0xbc7a843 | `0xbc7a843  mov rax,[rsi+0x10]` | reservedBytes read (cap for commit) | [V] |
| gpa+0x18 zeroedCount | 8 | 0xbc7a931, 0xbc7a959 | `0xbc7a931  mov rcx,[rsi+0x18]` · `0xbc7a959  mov [rsi+0x18],rdi` | zeroedCount R/W | [V] |
| gpa+0x20 committedBytes | 8 | 0xbc7a7f8, 0xbc7a826, 0xbc7a95d | `0xbc7a7f8  mov rax,[rcx+0x20]` · `0xbc7a826  mov r14,[rsi+0x20]` · `0xbc7a95d  mov [rsi+0x20],rbx` | committedBytes R/W | [V] |
| gpa+0x28 mutex | - | 0xbc7a805, 0xbc7a80c, 0xbc7a964 | `0xbc7a805  lea r15,[rsi+0x28]` · `0xbc7a80c  call 0xEEC59F0` · `0xbc7a964  call 0xEEC5A10` | _Mtx_lock / _Mtx_unlock | [V] |
| gpa+0x74 lock count | 4 | 0xbc7a819 | `0xbc7a819  cmp dword ptr [rsi+0x74],0x7FFFFFFF` | lock owner count read | [V] |
| grow: need = idx*0x540+0x540 | - | 0xbc7a7eb, 0xbc7a7f1 | `0xbc7a7eb  imul ebx,edx,0x540` · `0xbc7a7f1  lea rdi,[rbx+0x540]` | record size 0x540 | [V] |
| grow: fast-path need<=committed | - | 0xbc7a7fc, 0xbc7a7ff | `0xbc7a7fc  cmp rdi,rax` · `0xbc7a7ff  jbe 0xBC7A96A` | return if already committed | [V] |
| grow: round to 64KiB | - | 0xbc7a837, 0xbc7a83d | `0xbc7a837  add ebx,0x1053F` · `0xbc7a83d  and ebx,0xFFF0000` | newCommit = (need+0x1053F)&0xFFF0000 | [V] |
| grow: commit via iface slot+8 | - | 0xbc7a85f, 0xbc7a889, 0xbc7a8b1 | `0xbc7a85f  mov rax,[rax+0x28]` · `0xbc7a889  mov rax,[rax+8]` · `0xbc7a8b1  call r10` | platformMemory->commit(base+committedBytes, size, flags) | [V] |
| grow: assert id | - | 0xbc7a8b5 | `0xbc7a8b5  mov rax,0x235B04BE0011DCAA` | BS_assert id on commit failure | [V] |
| grow: count = newCommit/0x540 capped | - | 0xbc7a91e, 0xbc7a921, 0xbc7a928, 0xbc7a92e | `0xbc7a91e  shr eax,6` · `0xbc7a921  imul rax,0xC30C30D` · `0xbc7a928  shr rax,0x20` · `0xbc7a92e  cmovb edi,eax` | count = min(newCommit/0x540, maxCount) | [V] |
| grow: memset new pages | - | 0xbc7a941, 0xbc7a948, 0xbc7a94b, 0xbc7a954 | `0xbc7a941  imul rcx,0x540` · `0xbc7a948  add rcx,[rsi]` · `0xbc7a94b  imul r8,rax,0x540` · `0xbc7a954  call 0xEEC6ED0` | memset(base+zeroedCount*0x540, 0, (count-zeroedCount)*0x540) | [V] |

### (c) per-draw side table copy 0xbc60f10 (commitSideTable; rcx=Frame, edx=idx, r8=src SideTable*; element Binding = 0x14 bytes, 0x41 stages)

| offset | size | site(s) | verbatim `0xRVA  instr` | meaning | tag |
| Frame+0x8B4778+idx*8 SideTable* slot | 8 | 0xbc60f2f, 0xbc60f8b | `0xbc60f2f  mov rsi,[rcx+r14*8+0x8B4778]` · `0xbc60f8b  mov [rdi+r14*8+0x8B4778],rsi` | dst SideTable* R/W | [V] |
| src SideTable+0x410 used count | 4 | 0xbc60f24 | `0xbc60f24  cmp dword ptr [r8+0x410],0` | src->used == 0 -> empty-draw path | [V] |
| dst SideTable alloc 0x418 | - | 0xbc60f67, 0xbc60f72 | `0xbc60f67  mov r8d,0x418` · `0xbc60f72  call qword ptr [0xF99FFA0]` | realloc(nullptr, 0x418) when !dst | [V] |
| dst SideTable memset 0x410 | - | 0xbc60f7b, 0xbc60f86 | `0xbc60f7b  mov r8d,0x410` · `0xbc60f86  call 0xEEC6ED0` | memset(dst, 0, 0x410) | [V] |
| dst entry[i]+0x00 data ptr | 8 | 0xbc61052, 0xbc6105b | `0xbc61052  mov [rsi+r15],rcx` · `0xbc6105b  mov rdx,[rbx+r15]` | data ptr W/R | [V] |
| dst entry[i]+0x08 count | 8 | 0xbc60fc1, 0xbc61056 | `0xbc60fc1  mov r12,[rbx+r15+8]` · `0xbc61056  mov [rsi+r15+8],r12` | count R/W | [V] |
| entry loop bound 0x41 entries | - | 0xbc60fb0, 0xbc60fb4 | `0xbc60fb0  add r15,0x10` · `0xbc60fb4  cmp r15,0x410` | 0x41 entries × 0x10 bytes | [V] |
| per-entry memcpy count*0x14 | - | 0xbc61020, 0xbc61070 | `0xbc61020  lea r8,[rax+rax*4]` · `0xbc61070  call 0xEBCE390` | memcpy(dst->data, src->data, count*0x14) | [V] |
| dst SideTable+0x410 used written | 4 | 0xbc6107a, 0xbc61080, 0xbc61086, 0xbc6108e | `0xbc6107a  mov eax,[rbx+0x410]` · `0xbc61080  mov [rsi+0x410],eax` · `0xbc61086  mov rcx,[rdi+r14*8+0x8B4778]` · `0xbc6108e  mov [rcx+0x410],eax` | dst->used = src->used (written twice) | [V] |
| empty-draw: dst already empty check | - | 0xbc610ae, 0xbc610b5 | `0xbc610ae  cmp dword ptr [rsi+0x410],0` · `0xbc610b5  je short 0xBC61094` | skip if dst->used == 0 | [V] |
| empty-draw: clear dst (movups) | 16 | 0xbc610fe, 0xbc6112b | `0xbc610fe  movups [rbx],xmm6` · `0xbc6112b  mov dword ptr [rsi+0x410],0` | zero entries + used = 0 | [V] |

## CLOSES?
YES — all three sub-parts of Q2e are proven by [V] rows on disk now:
- (a) Encoder::discard 0xbc60d10: clears m_discard (+0x6AD), draw state (+0x60/+0x68/+0x70/+0x80/+0x90/+0x98), defaults (+0x40/+0xA0/+0xA2/+0xA3/+0xA8/+0xAC/+0xB4), the +0xC0..+0xE3 compute block, all bindings at +0x140 (idx=0xFFFF, type=0, stride 0x28/iteration bound cmp rax,0x667), frees/zeroes the side table via Encoder+0x680, and sets bindDirty +0x688 — all [V].
- (b) RenderBind grow 0xbc7a7c0: GuardedPagedArray at Frame+0x8B4700 with base/maxCount/reservedBytes/zeroedCount/committedBytes/mutex/lock-count; idx bounds check vs maxCount, fast-path need<=committedBytes, 64KiB-rounded commit via platformMemory iface (slot+8 query then slot+8 commit), assert id 0x235B04BE0011DCAA, count=min(newCommit/0x540,maxCount), memset of new pages — all [V].
- (c) side-table copy 0xbc60f10: Frame+0x8B4778+idx*8 SideTable* slot, alloc 0x418/memset 0x410, per-entry data(ptr)/count copy for 0x41 entries, memcpy count*0x14, dst->used = src->used (written twice) — all [V].

No game or build step remains for Q2e itself; hooking this seam is a later unit's work.

## TOOL REQUESTS
None

