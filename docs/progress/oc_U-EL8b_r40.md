## NEXT
DONE

# Unit U-EL8b — Atlases (terrain, items), mipmaps and compression (Minecraft.Windows.exe 1.26.62.01, PE ImageBase 0x140000000)

GOAL: close checklist item L8b (terrain atlas, item atlas, mipmaps, BC1/BC3/BC7 compression). Current verdict: NO — see CLOSES? below.

## 1. Inherited proven state (NOT redone this unit)
- TerrainAtlas idx6 / ItemAtlas idx7 registered in sub_186e6a0 (name at obj+0, idx at obj+8) [V r-latest]; sub_1870de0 also registers atlases [V r8]; sub_1042320 = ServerLevelLoad [V r10]
- Texture-create chain 0xc296b50 -> 0xbc73bf0 -> createTexture 0xe8143c0 [V L8a]
- l8b_texcreate_record (rva=0xE81BF30, hits=150 samples=24, DONE per _status.txt): line 3 `CALLER ret=0xE814560 first_hit=1` [V live]; all 7 sampled creations format 0x1C at desc+0xB0, numMips=1, no atlas-name strings [V live]
- mc_root_4e05e50_callers (rva=0x4E05E50, hits=150 samples=32, DONE): line 3 `CALLER ret=0x1289496 first_hit=1` [V live]
- No item-atlas string/code in exe [V prior]; BC1/BC3/BC7 strings unreferenced [V prior]; mip generator not located [V prior]; terrain atlas only TerrainAtlasBlit task name [V prior]

## 2. New angle this session: indirect caller of sub_4e05e50
sub_4e05e50 [0x4e05e50..0x4e06074) has 0 static xrefs. The capture at its entry names the caller: mc_root_4e05e50_callers.txt line 3 `CALLER ret=0x1289496 first_hit=1`. Address 0x1289496 is the `nop` immediately after
`0x1289490  call qword ptr [0xF99FFA0]                    ; [data_f99ffa0] = sub_eea6040`
inside sub_12893d0 [0x12893d0..0x12895d3). So sub_12893d0 is the indirect caller of sub_4e05e50 via [0xF99FFA0], returning to 0x1289496 [V disasm + V live]. 150 hits = one texture object processed per list entry per call.

sub_4e05e50 decoded (rcx = a0 = one MC texture object). Field accesses [V]:
`0x4e05e71  mov rax,[rcx+0x18]                            ; R a0+0x18` — sub-object ptr, released via [0xF99FFA0]
`0x4e05e82  mov rax,[rax+0x10]                            ; R *(a0+0x18)+0x10` — dtor target of that sub-object
`0x4e05e8c  mov rdx,[rdi+0x10]                            ; R a0+0x10` — refcounted texture object
`0x4e05e95  mov eax,[rdx+8]                               ; R *(a0+0x10)+0x8` — refcount read
`0x4e05ea8  lock cmpxchg [rdx+8],r8d                      ; R *(a0+0x10)+0x8` — refcount try-acquire
`0x4e05eb0  mov rcx,[rdi+8]                               ; R a0+0x8` — link/list ptr
`0x4e05e7e  lea rdx,[rdi+0x58]                            ; R a0+0x58` — passed to the release path
`0x4e05f61  mov r9,[rdi+0xE0]                             ; R a0+0xE0` — 4th arg of the texture call below

Then sub_4e05e50 issues the texture op:
`0x4e05f77  call 0xBC41420                                ; -> sub_bc41420`
confirmed live: dragon_texture_caller_bc41420.txt line 3 `CALLER ret=0x4E05F7C first_hit=1` (0x4E05F7C is the nop right after the call at 4e05f77) [V live]. The dragon chain continues `4e05f77 -> sub_bc41420 -> sub_c296b50` (dragon_texture_entry_c296b50.txt line 3 `CALLER ret=0xBC41B3E first_hit=1`, ret inside sub_bc41420) [V live] -> 0xc296b50 -> 0xbc73bf0 -> createTexture 0xe8143c0 [V L8a]. sub_4e05e50 also calls `0x4e05f85  call 0x4E061B0                                ; -> sub_4e061b0` and, on the decode path, `0x4e05fca  call 0xE935700` which is a trampoline `0xe935700  jmp 0x392960                                  ; -> sub_392960` [V]; sub_e935710 stores a vtable `0xe935720  mov [rcx],rax                                 ; W a0+0x0` from [data_eec80a8] [V].

sub_12893d0 (rcx = a0 = list container; entries walked by r13/r14 in 0x18 steps) [V]:
`0x1289406  mov r13,[rcx]                                 ; R a0+0x0` — list head
`0x1289409  mov r14,[rcx+8]                               ; R a0+0x8` — list end
`0x1289431  mov rcx,[r13+8]                               ; R entry+0x8` — entry's refcount object ptr
`0x128947d  mov rcx,[r13+0x10]                            ; R entry+0x10` — per-texture object handed to sub_4e05e50
`0x128949b  mov qword ptr [r13+0x10],0                    ; W entry+0x10` — cleared after hand-off

sub_12893d0's callers [V xref callers 0x12893d0 = exactly 4]: sub_1145c20 (+0x4ae), sub_6622610 (+0x1c8; drains [rcx+0xD8] then calls sub_12893d0 at 6622662), sub_6632bf0 (+0xb3d0; "Deferred Texture Transactions" data_f54e8af at `0x6632c19  lea rax,[0xF54E8AF]                           ; [data_f54e8af] "Deferred Texture Transactions"` and "Deferred Buffer Transactions" data_f54e847 at `0x6632c42  lea rax,[0xF54E847]                           ; [data_f54e847] "Deferred Buffer Transactions"`, calls sub_12893d0 at 6632c55), sub_66232b0 (0xb3d0-byte function, 0 static xrefs, calls sub_c293850 adjacent to the 0xc296b50 chain). Neither texgroup_load 0x5421c90 nor texload 0x58a1310 calls sub_12893d0 statically [V xref].

## 3. Field map (offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag)

| MC_obj+0x18 | 8 | 4e05e71 | `0x4e05e71  mov rax,[rcx+0x18]                            ; R a0+0x18` | sub-object ptr (released) | [V] |
| MC_obj+0x18+0x10 | 8 | 4e05e82 | `0x4e05e82  mov rax,[rax+0x10]                            ; R *(a0+0x18)+0x10` | dtor target | [V] |
| MC_obj+0x10 | 8 | 4e05e8c | `0x4e05e8c  mov rdx,[rdi+0x10]                            ; R a0+0x10` | refcounted texture object | [V] |
| TexObj+0x8 | 4 | 4e05e95 | `0x4e05e95  mov eax,[rdx+8]                               ; R *(a0+0x10)+0x8` | refcount read | [V] |
| TexObj+0x8 (atomic) | 4 | 4e05ea8 | `0x4e05ea8  lock cmpxchg [rdx+8],r8d                      ; R *(a0+0x10)+0x8` | refcount try-acquire | [V] |
| MC_obj+0x8 | 8 | 4e05eb0 | `0x4e05eb0  mov rcx,[rdi+8]                               ; R a0+0x8` | link/list ptr | [V] |
| MC_obj+0x58 | 8 | 4e05e7e | `0x4e05e7e  lea rdx,[rdi+0x58]                            ; R a0+0x58` | release-path arg | [V] |
| MC_obj+0xE0 | 8 | 4e05f61 | `0x4e05f61  mov r9,[rdi+0xE0]                             ; R a0+0xE0` | 4th arg to sub_bc41420 | [V] |
| List+0x0 | 8 | 1289406 | `0x1289406  mov r13,[rcx]                                 ; R a0+0x0` | list head | [V] |
| List+0x8 | 8 | 1289409 | `0x1289409  mov r14,[rcx+8]                               ; R a0+0x8` | list end | [V] |
| ListEntry+0x8 | 8 | 1289431 | `0x1289431  mov rcx,[r13+8]                               ; R entry+0x8` | entry refcount object ptr | [V] |
| ListEntry+0x10 | 8 | 128947d | `0x128947d  mov rcx,[r13+0x10]                            ; R entry+0x10` | per-texture object -> sub_4e05e50 | [V] |
| ListEntry+0x10 (clear) | 8 | 128949b | `0x128949b  mov qword ptr [r13+0x10],0                    ; W entry+0x10` | cleared after hand-off | [V] |
| Dtxn+0x0 | 16 | 6632c0e (R) + 6632c33 (W) | `0x6632c0e  movups xmm0,[rcx]                             ; R a0+0x0` | deferred-txn queue head: read at 6632c0e, cleared by write `0x6632c33  movups [rcx],xmm1                             ; W a0+0x0` | [V] |
| Dtxn+0x10 | 16 | 6632c36 | `0x6632c36  movups [rcx+0x10],xmm1                        ; W a0+0x10` | deferred-txn queue slot cleared | [V] |
| Dtxn+0x20 | 16 | 6632c2f | `0x6632c2f  movups [rcx+0x20],xmm1                        ; W a0+0x20` | deferred-txn queue tail cleared | [V] |

## 4. What is still missing (blocking fact)
- Stitcher: nothing in the exe builds the atlas texture description from the registered TerrainAtlas (idx6)/ItemAtlas (idx7) objects after sub_1042320 (ServerLevelLoad). sub_12893d0's consumers are the deferred-transaction drainers above, not texgroup_load/texload — no static path from registration to a texture description build was found.
- Mipmaps: no mip generator located; every live creation has numMips=1 [V live l8b_texcreate_record]; only material mip params + numMips +0xB1 [V prior].
- Compression: BC1/BC3/BC7 unreferenced, no compression path [V prior].
- Decode location (r13 lead): a live object carries a +0x00 pointer to 0x7FF6A8215838. PE ImageBase = 0x140000000 [V], so 0x7FF6A8215838 is outside Minecraft.Windows.exe — another module [V via ImageBase math]; stitcher/mip/compression decode may be out-of-exe or data-driven, i.e. not statically decidable from this exe.

Live capture l8b_resizetex_slot31 (rva=0xe815840, resizeTexture slot 31 — "mips>1 is mip-generation evidence", names the stitcher caller via ret=) is already pending in the queue, but docs/data/live/l8b_resizetex_slot31.txt does not exist yet (orchestrator has not run it). The capture queue is full (4 pending), so no new capture request can be added this unit.

CLOSES? NO — single blocking fact: the atlas texture-description builder (stitcher) consuming the registered TerrainAtlas/ItemAtlas objects after ServerLevelLoad, mip generation, and BC1/BC3/BC7 compression are not present in Minecraft.Windows.exe statically (no atlas-name string, no BC1/BC3/BC7 reference, all live creations numMips=1 format 0x1C), and the live object's +0x00 pointer 0x7FF6A8215838 resolves outside the exe image (ImageBase 0x140000000), i.e. to another module; closing requires the pending l8b_resizetex_slot31 capture result or access to that other module.

## TOOL REQUESTS
None new — l8b_resizetex_slot31 already pending (queue at 4/4 cap); result awaited in docs/data/live/l8b_resizetex_slot31.txt. No helper scripts written.
