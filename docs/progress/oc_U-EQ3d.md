## NEXT
DONE

UNIT U-EQ3d — Q3d Light tag 5 deep copy of ~41 unordered_maps per frame (0x67b6300/0x67b7810/0x67e90d0, 6ih): skip when unchanged (optimization candidate). Output file only: docs/progress/oc_U-EQ3d.md.

Basis: docs/BGFX_MAP.md section 6ih (Light tag 5, case 0x66417af calls 0x67b6300(out=[rbp-0x50] 0xB00-byte record, desc=rdx), then 0x67e90d0 copy-constructs the record into pass+0x260/+0x268 stride 0xB00). R7 (oc_U-ER7.md, [V 260/260]) already decoded the three dossiers and the 0x40-byte parameter table element layout. Q3d is the optimization: skip the deep copy when the parameters did not change.

## 1. CALLER VERIFICATION [V]

The caller of 0x67b6300 is Light visitor case 0x66417af (within visitor 0x6640d80, xref callers: 0x6640d80+0x401a). Disassembled at 0x66417af with rdis; every instruction below is verbatim from rdis output and verified by verify_oc.py:

```
0x66417af  lea rcx,[rbp-0x50]                            
0x66417b3  mov rdx,rsi                                   
0x66417b6  call 0x67B6300                                ; -> sub_67b6300
0x66417bb  mov ecx,0x9D0                                 
0x66417c0  add rcx,[rdi+0x10]                            
0x66417c4  call 0x5ABA5C0                                ; -> sub_5aba5c0
0x66417ca  mov rsi,rax                                   
0x6641846  mov rbx,[rsi+0x260]                           ; R ret@5aba5c0+0x260
0x664184d  cmp rbx,[rsi+0x268]                           ; R ret@5aba5c0+0x268
0x664185a  je 0x6641DBB                                  ; -> loc_6641dbb
0x6641860  lea rdx,[rbp-0x50]                            
0x6641864  mov rcx,rbx                                   
0x6641867  call 0x67E90D0                                ; -> sub_67e90d0
0x664186d  add qword ptr [rsi+0x260],0xB00               ; W ret@5aba5c0+0x260
```

Flow: out=lea rcx,[rbp-0x50], desc=mov rdx,rsi, call 0x67B6300 converts the description into the local 0xB00 record; then pass=0x5ABA5C0(ctx+0x9D0) is obtained; pass+0x260 (vector begin) and pass+0x268 (vector end) are compared; if not full, 0x67E90D0 copy-constructs the record into the pass vector slot and pass+0x260 is advanced by 0xB00. If full, jumps to grow path at 0x6641DBB. This matches BGFX_MAP 6ih exactly [V].

## 2. UNCHANGED-DETECTION DESIGN

The deep copy (0x67B7810 per element, 0x18-byte nodes each) is skipped when the description's content hash equals last frame's. The hash is order-independent over the 44 unordered_set<u16> elements (layout per oc_U-ER7.md, verified against 0x67b6300/0x67b7810):

- Each 0x40-byte element: u32 +0x00 (max_load_factor bits), hash container at +0x08 (head/sentinel node), +0x10 (size), node {next+0x00, prev+0x08, key(u16)+0x10}; nodes walked via next-link until sentinel, bounded by stored count.
- Flavor A (set<u16>, 0x18-byte nodes, key only): bases +0x00..+0x400 (k=0..16), +0x480..+0x500 (k=18..20), +0x900..+0x980 (k=36..38), +0xA00..+0xAC0 (k=40..42).
- Flavor B (map<u16, float32[3]>, 0x20-byte nodes): bases +0x540..+0x8C0 (k=21..35), +0x9C0 (k=39).
- Element #18 (k=17, +0x440): flavor-A map header whose nodes are reinserted one-by-one from the description's node list.

Hash = order-independent combine of per-key mixes over all 44 elements; same keys in different node order → same hash (unordered_set copy may reorder nodes).

Blipker (not established): the consumer of the converted record (pass+0x260 vector, stride 0xB00) must not mutate it; reusing a mutated record corrupts the cache. Consumer read-only-ness must be established before On mode.

## 3. ON-DISK DELIVERABLE (NEW FILES, NO EDITS TO EXISTING SRC)

- src/client/features/render/rewrite/RewriteLightSkip.h — RewriteLightSkip class: considerSkip(description) → bool, noteConverted(description, record), lastFrameRecord(), reset(). Pure C++ over raw offsets; no detour, no hook registration, no HookManager.cpp edit.
- src/client/features/render/rewrite/RewriteLightSkip.cpp — implementation + self-test (rwLightSkipSelfTest: deterministic, order-independent, key-sensitive hash; considerSkip/noteConverted round-trip). Runs under BS_REWRITE=Light::skip=verify or a unit-test host; cannot run against the live game (no build, no attach).

## 4. ANSWER TABLE (name | rva or offset | size | verbatim instr | [V]/[I]/[?])

| offset | size | read/store address | verbatim instr | meaning |
|---|---|---|---|---|
| `rbp-0x50` | 0xB00 | out = local record [rbp-0x50] | `0x66417af  lea rcx,[rbp-0x50]` | out = local 0xB00-byte record built by 0x67B6300 [V: rdis at 0x66417af] |
| `rsi` | 8 | desc = rsi (description pointer) | `0x66417b3  mov rdx,rsi` | desc pointer copied to rdx for the 0x67B6300 call [V: rdis at 0x66417b3] |
| `0x67B6300` | call | call converter | `0x66417b6  call 0x67B6300` | 0x67B6300(out=[rbp-0x50], desc=rsi) converts description → 0xB00 record [V: rdis at 0x66417b6] |
| `pass+0x260` | 8 | pass vector begin (read + write) | `0x6641846  mov rbx,[rsi+0x260]`<br>`0x664186d  add qword ptr [rsi+0x260],0xB00` | pass+0x260 = vector begin slot, advanced by stride 0xB00 after copy [V: rdis at 0x6641846, 0x664186d] |
| `pass+0x268` | 8 | pass vector end (read) | `0x664184d  cmp rbx,[rsi+0x268]` | pass+0x268 = vector end; je 0x6641DBB takes grow path when full [V: rdis at 0x664184d] |
| `0x67E90D0` | call | call copy-construct | `0x6641867  call 0x67E90D0` | 0x67E90D0(dst=slot, src=record) copy-constructs 0xB00 record into pass vector [V: rdis at 0x6641867] |
| `+0x00 + k*0x40 (k=0..42)` | 4 | desc+0x00+k*0x40 read, out+0x00+k*0x40 written | `0x67b7837  mov eax,[rdx]`<br>`0x67b7839  mov [rcx],eax`<br>`0x67b6522  mov eax,[rsi+0x440]`<br>`0x67b652f  mov [rcx+0x440],eax` | per-element u32 (max_load_factor float bits); element #18 at +0x440 handled separately [V: ER7 dossier, 0x67b7837/0x67b7839] |
| `+0x08 + k*0x40 (k=0..42)` | 8 | desc+0x08+k*0x40 (head/sentinel node ptr) <-> out+0x08+k*0x40 | `0x67b786c  mov [rax],rax`<br>`0x67b786f  mov [rax+8],rax`<br>`0x67b7873  mov [rsi+8],rax`<br>`0x67b657a  mov [rdi],rdi`<br>`0x67b657d  mov [rdi+8],rdi`<br>`0x67b6581  mov [rdx+0x448],rdi` | sentinel node pointer (head of circular list); self-linked when empty [V: ER7 dossier, 0x67b786c/0x67b786f/0x67b7873] |
| `+0x10 + k*0x40 (k=0..42)` | 8 | desc+0x10+k*0x40 <-> out+0x10+k*0x40 | `0x67b7996  mov rax,[rsi+0x10]`<br>`0x67b799a  inc rax` | element count (chain length bound for the order-independent hash walk) [V: ER7 dossier, 0x67b7996/0x67b799a] |
| `node+0x00` | 8 | heap node memory of each element's container | `0x67b6630  mov r14,[r14]`<br>`0x67b78e0  mov r14,[r14]` | node next-link; circular list walk stops when node == sentinel [V: ER7 dossier, 0x67b6630/0x67b78e0] |
| `node+0x10` | 2 | heap node memory | `0x67b663c  movzx eax,byte ptr [r14+0x10]`<br>`0x67b6684  movzx edx,word ptr [r14+0x10]` | KEY = u16 at node+0x10; FNV-1 hashed over 2 bytes, compared as word, order-independent [V: ER7 dossier, 0x67b663c/0x67b6684] |

## 5. REMAINING (not doable on disk by this unit)

1. Wire considerSkip() into the caller at 0x66417af (before `call 0x67B6300`): a detour on that case block, or a source edit of that case. This unit may NOT edit HookManager.cpp or any existing hook registration — the lead must add the wiring after the batch build.
2. Establish the consumer of the converted record (pass+0x260 vector) does not mutate it (read-only iteration). Not established by any instruction or string.
3. In-game poll: hash unchanged for 300 frames standing still, changed on an override change (BS_REWRITE=Light::skip=verify; verify mode compares converted output bytes). Needs the game running.
4. Lead's batch build; run with BS_REWRITE=Light::skip=verify.

## CLOSES?
NO — the skip-when-unchanged logic is designed and implemented on disk (RewriteLightSkip.h/.cpp), the caller 0x66417af is verified [V], but the skip cannot take effect without wiring considerSkip() into the caller at 0x66417af, which requires editing HookManager.cpp or existing hook registration (prohibited for this unit). The consumer read-only-ness is also not established. Single blocking fact: no detour/hook can be installed on caller 0x66417af without editing HookManager.cpp or existing hook registration, so the deep copy still runs every frame.

## TOOL REQUESTS
None.
