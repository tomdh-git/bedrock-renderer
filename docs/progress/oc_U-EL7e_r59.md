## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator outputs, cited as [V live] with file.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted from a fresh rdis dis this session) / [V live] saw in an orchestrator live-capture reg dump (file cited) / [I] inferred from structure or BGFX_MAP.md / '-' = no instruction or string shows a meaning. Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1; direct call 5, indirect call qword ptr [mem] 8). No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r57; not re-decoded; quotes re-verified this session where reused)

### Half 1 — sampler flag decode + sampler cache (6ax) [V]
- docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.

### Half 2a — D3D12 backend texture-management chain [V]
- texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP.md 6z/6z-2/6aj/1524 confirm base/stride)
- createTexture 0xe8143c0 = renderer-context vtable slot 26 (BGFX_MAP.md line 403); updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750
- createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30

### Backend createTexture record (creation) [V] [V live]
| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0xE8143C0 | - | E: | `0xE8143C0  push rbp` | createTexture entry (renderer-context vtable slot 26) | [V] |
| this+0xBDE178 | 8 | R: | `0xE8143F3  lea r12,[rcx+0xBDE178]` | texture record table base = renderer ctx + 0xBDE178 | [V] |
| 0xE814427 | 5 | - | `0xE814427  imul r8,rbx,0xB8` | record stride 0xB8 per record index | [V] |
| 0xE81455B | 5 | - | `0xE81455B  call 0xE81BF30` | createTexture -> TextureD3D12::create (backend record fill) | [V] |
| 0xE814560 | 1 | - | `0xE814560  nop` | ret site after `call 0xE81BF30` = l8b_texcreate_record capture CALLER ret=0xE814560 | [V] [V live] |

## New work this session — indirect caller of sub_4e05e50 + deferred-txn path (NEW ANGLE on the texgroup_load->sub_4e05e50 blocker)

### The mc_root capture names the indirect caller of sub_4e05e50: sub_12893d0 (ret site 0x1289496) [V live + V rdis]

docs/data/live/mc_root_4e05e50_callers.txt: `CALLER ret=0x1289496` — all 32 samples enter sub_4e05e50 via the return address 0x1289496, i.e. the function containing 0x1289496 is the indirect caller of sub_4e05e50.

Fresh rdis of sub_12893d0 (this session):
| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x12893D0 | - | E: | `0x12893D0  push rbp` | sub_12893d0 entry; mc_root indirect-caller dispatch of sub_4e05e50; `xref.py callers 0x4E05E50` -> EMPTY (0 static callers on sub_4e05e50 itself) | [V] |
| 0x1289486 | 8 | R: [rcx] | `0x1289486  mov rax,[rcx]` | sub_12893d0: rax = deferred-txn object vptr ([r13+0x10]) | [V] |
| 0x1289489 | 8 | R: [rax+8] | `0x1289489  mov rax,[rax+8]` | rax = object->vptr[1] = the real indirect-call target | [V] |
| 0x1289490 | 8 | R: [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` ; [data_f99ffa0] = sub_eea6040 | sub_12893d0 tail-calls vptr[1] through the CFG trampoline = sub_4e05e50 (job vtable 0xF215838[1]); ret site = 0x1289496 | [V] |
| 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after the indirect call = mc_root capture CALLER ret=0x1289496 (all 32 samples) | [V] [V live] |

sub_12893d0 iterates a list of deferred-txn objects ([rcx]..[rcx+8], stride 0x18) and, for each non-null object at [r13+0x10], loads vptr[1] and tail-calls it via `0x1289490 call qword ptr [0xF99FFA0]`. vtable 0xF215838 slot +0x008 = sub_4e05e50 [V vt output r57], so the rax held at the trampoline jmp = sub_4e05e50 [V].

### sub_12893d0's static callers — the deferred-transaction root sub_6632bf0 [V rdis + xref]

`xref.py callers 0x12893D0` -> 4 static callers: 0x1145c20(+0x4ae), 0x6622610(+0x1c8), 0x66232b0(+0xb3d0), 0x6632bf0(+0x34b) [V xref this session]. The producer-side root is sub_6632bf0 ("Deferred Texture Transactions"):

Fresh rdis of sub_6632bf0 (this session):
| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x6632BF0 | - | E: | `0x6632BF0  push rbp` | sub_6632bf0 entry; "Deferred Texture Transactions" processor; 2 xrefs in, both from sub_66232b0 (docs/progress/pre/0x6632bf0.md) | [V] |
| [0xF54E8AF] | - | R: | `0x6632C19  lea rax,[0xF54E8AF]` ; [data_f54e8af] "Deferred Texture Transactions" | deferred-txn queue name string | [V] |
| 0x6632C55 | 5 | - | `0x6632C55  call 0x12893D0` ; -> sub_12893d0 | sub_6632bf0 -> sub_12893d0 (deferred texture transaction dispatch) | [V] |
| 0x6632D1E | 5 | - | `0x6632D1E  call 0x12893D0` ; -> sub_12893d0 | sub_6632bf0 -> sub_12893d0 (second dispatch, deferred buffer transactions) | [V] |
| 0x6632C81 | 8 | R: [rcx] | `0x6632C81  mov rax,[rcx]` | sub_6632bf0 drain loop: rcx = queued object, rax = its vptr | [V] |
| 0x6632C84 | 8 | R: [rax+8] | `0x6632C84  mov rax,[rax+8]` | rax = object->vptr[1] | [V] |
| 0x6632C88 | 8 | R: [0xF99FFA0] | `0x6632C88  call qword ptr [0xF99FFA0]` ; [data_f99ffa0] = sub_eea6040 | vptr[1] tail-call through CFG trampoline | [V] |

sub_6632bf0 is called ONLY by sub_66232b0 (preflight 0x6632bf0.md: "sub_66232b0 2 call site(s)"; docs/progress/pre/_f99ffa0_refs.txt shows `call qword ptr [0xF99FFA0]` sites resolving to sub_eea6040 throughout) [V].

### sub_66232b0 is a runtime root — no static caller [V xref this session]
`xref.py callers 0x66232b0` -> EMPTY. sub_66232b0 (sub_6632bf0's sole static caller) has no static caller itself; it is entered at runtime (indirect/vtable). The other sub_12893d0 callers (0x6622610, 0x1145c20, 0x6632fd0) are likewise not statically reachable from texgroup_load.

### TexturePtr/ClientTexture connection — sub_4e05e50's argument is the MC texture object [V live + V fresh rdis]

mc_root live dumps (docs/data/live/mc_root_4e05e50_callers.txt): RCX arguments carry texture-descriptor data and name strings 'tex' (hit 1), 'legs' (hit 2), 'spear' (hit 15) — i.e. RCX is the MC texture object being uploaded.

Fresh rdis of sub_4e05e50 (this session):
| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x4E05E50 | 1 | - | `0x4E05E50  push rbp` | sub_4e05e50 entry; MC-side pack->GPU root; `xref.py callers 0x4E05E50` -> EMPTY (0 static callers) | [V] |
| 0x4E05F61 | 8 | R: [rdi+0xE0] | `0x4E05F61  mov r9,[rdi+0xE0]` | sub_4e05e50 reads the renderer context from its argument object +0xE0 | [V] |
| 0x4E05E7E | 8 | - | `0x4E05E7E  lea rdx,[rdi+0x58]` | texture object = argument + 0x58 | [V] |
| 0x4E05F68 | 4 | - | `0x4E05F68  add rdi,0x58` | texture object = sub_4e05e50 argument + 0x58 | [V] |
| 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 -> sub_bc41420 (rcx = texture object); ret site 0x4E05F7C | [V] [V live] |
| 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | ret site after `call 0xBC41420` = dragon_texture_caller_bc41420 capture CALLER ret=0x4E05F7C | [V live] |

Handle trace into TexturePtr/ClientTexture [V live + V file read r57]: texture object = arg + 0x58; returned u16 bgfx handle stored at texture object +0x00 (`0xC296E26 mov [rdi],ax`); 0x1C-byte create descriptor copied to +0x08 (`0xC296E2D movups xmm0,[r12]` / `0xC296E32 movups [rdi+8],xmm0`, size 16); descriptor pointer at +0x18 (`0xC296E3B mov [rdi+0x18],rdx`); sdk TexturePtr.h (sizeof 32, mClientTexture+0x00, mResourceLocationPtr+0x10 [V file read]) / ClientTexture.h (empty marker struct) [V file read].

### Issuance chain below sub_4e05e50 (end-to-end, already proven r1-r55; not re-decoded)
sub_4e05e50 -> sub_bc41420 -> dragon entry 0xc296b50 (`0xBC41B39 call 0xC296B50`) -> thin wrapper 0xbc73bf0 (`0xC296D79 call 0xBC73BF0`) -> command-byte-0x0E producer sub_bc73770 (`0xBC73EA8 call 0xBC73770`) -> bgfx dispatcher (`0xBC6A28F mov rcx,[rdi+0x1EBF2D0]` / `0xBC6A2AE mov rax,[rcx]` / `0xBC6A2B1 mov rax,[rax+0xD0]` vptr[slot 26]) / `0xBC6A2C2 call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30. Returned u16 handle stored at texture object+0x00. All [V] (r57 Tables 2-3) + [V live] (createtexture_callers ret=0xBC6A2C8; dragon_texture_caller_bc41420 ret=0x4E05F7C; dragon_texture_entry_c296b50 ret=0xBC41B3E).

## What I tried that failed (new angle, not redone)

- `xref.py callers 0x66232b0` -> EMPTY: sub_66232b0 (sub_6632bf0's only static caller, the deferred-txn root) has 0 static callers [V this session]. Cannot build a static path texgroup_load -> ... -> sub_66232b0 -> sub_6632bf0 -> sub_12893d0 -> sub_4e05e50.
- `xref.py callers 0x6632bf0` -> sub_66232b0 only (preflight): texgroup_load does not call sub_6632bf0 directly [V].
- texgroup_load(0x5421c90) static chain ends at `0x54227AF call 0x18718D0` (sub_18718d0 texture-cache lookup/release, vtable 0xEFCA680); sub_18718d0 never reaches sub_4e05e50 [V r57]. texload 0x58a1310 / texload_task 0x541bf00 have 0 static callers and are not on the proven path [V r57].
- livemem: not applicable — no statically-known queue/vector anchor for sub_66232b0's `this`/vector base (r57); deferred transaction enqueue is runtime-only through a data structure, not a call edge.
- [0xF99FFA0] is read-only .rdata (= sub_eea6040 trampoline), 0 stores [V r57]; static work on the cell is exhausted.

## CLOSES?

NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. The createTexture issuance chain IS fully [V]-proven below sub_4e05e50 (sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770 -> dispatcher vptr[slot 26] -> createTexture 0xe8143c0 -> TextureD3D12::create), sub_4e05e50 IS called at runtime ([V live] mc_root ret=0x1289496 via sub_12893d0; all 32 samples), takes a TexturePtr* ([V live + sdk TexturePtr.h]), and the returned u16 handle is stored into the texture object (TexturePtr-related) [V]. The indirect caller sub_12893d0 is decoded [V] and its static caller sub_6632bf0 ("Deferred Texture Transactions") is decoded [V], but sub_6632bf0's only static caller sub_66232b0 has 0 static callers (runtime root) [V this session], and texgroup_load's static chain terminates at sub_18718d0 (texture cache) which never reaches sub_4e05e50 [V r57]. So the texgroup_load -> sub_4e05e50 enqueue/bind is runtime-only (deferred-transaction queue / job system) and cannot be closed statically. Everything else in L7e IS [V]-proven: Half 1 sampler flag decode + cache (6ax); Half 2a D3D12 backend texture-management chain; createTexture issuance end-to-end below sub_4e05e50; handle trace into TexturePtr/ClientTexture; sdk headers. Atlas stitchers (L8a/L8b) remain separate open units (oc_U-EL8a/oc_U-EL8b), MIRROR_SKIP, not this unit.

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required (every quoted `0xRVA  instr` line matched against a fresh rdis dis of the 1.26.62.01 exe this session).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; only then is line 2 after `## NEXT` set to DONE.

## TOOL REQUESTS

- None. No helper scripts written; no temporary files left behind in the repo.
