## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator outputs, cited as [V live] with file. Earlier attempts: docs/progress/oc_U-EL7e_r1.md .. r59.md (read, not re-decoded).

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted from a fresh rdis dis this session) / [V live] saw in an orchestrator live-capture reg dump (file cited) / [I] inferred from structure or BGFX_MAP.md / '-' = no instruction or string shows a meaning. Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1; direct call 5, indirect call qword ptr [mem] 8). No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r59; not re-decoded; quotes re-verified this session where reused)

### Half 1 — sampler flag decode + sampler cache (6ax) [V]
- docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120. [V] (r59; not re-decoded this session)

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

### createTexture issuance end-to-end below sub_4e05e50 [V] [V live]
sub_4e05e50 -> sub_bc41420 -> dragon entry 0xc296b50 (`0xBC41B39 call 0xC296B50`) -> thin wrapper 0xbc73bf0 (`0xC296D79 call 0xBC73BF0`) -> cmd-byte-0x0E producer sub_bc73770 (`0xBC73EA8 call 0xBC73770`) -> bgfx dispatcher (`0xBC6A28F mov rcx,[rdi+0x1EBF2D0]` / `0xBC6A2AE mov rax,[rcx]` / `0xBC6A2B1 mov rax,[rax+0xD0]` vptr[slot 26]) / `0xBC6A2C2 call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30. Returned u16 handle stored at texture object+0x00. All [V] (r57 Tables 2-3) + [V live] (createtexture_callers ret=0xBC6A2C8; dragon_texture_caller_bc41420 ret=0x4E05F7C; dragon_texture_entry_c296b50 ret=0xBC41B3E; bgfx_createtexture_producer sub_bc73770 verified r4).

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x4E05E50 | - | E: | `0x4E05E50  push rbp` | sub_4e05e50 entry; MC-side pack->GPU root; `xref.py callers 0x4E05E50` -> EMPTY (0 static callers, reconfirmed this session) | [V] |
| 0x4E05E7E | 8 | - | `0x4E05E7E  lea rdx,[rdi+0x58]` | texture object = sub_4e05e50 argument + 0x58 | [V] |
| 0x4E05F68 | 4 | - | `0x4E05F68  add rdi,0x58` | texture object = sub_4e05e50 argument + 0x58 | [V] |
| 0x4E05F77 | 5 | - | `0x4E05F77  call 0xBC41420` | sub_4e05e50 -> sub_bc41420 (rcx = texture object); ret site 0x4E05F7C | [V] [V live] |
| 0x4E05F7C | 1 | - | `0x4E05F7C  nop` | ret site after `call 0xBC41420` = dragon_texture_caller_bc41420 capture CALLER ret=0x4E05F7C | [V live] |
| 0xBC41B39 | 5 | - | `0xBC41B39  call 0xC296B50` | sub_bc41420 -> dragon entry 0xc296b50; ret site 0xBC41B3E | [V] [V live] |
| 0xC296D79 | 5 | - | `0xC296D79  call 0xBC73BF0` | dragon entry 0xc296b50 -> thin wrapper 0xbc73bf0; ret site 0xC296D7E | [V] [V live] |
| 0xBC73EA8 | 5 | - | `0xBC73EA8  call 0xBC73770` | wrapper 0xbc73bf0 -> cmd-byte-0x0E producer sub_bc73770 | [V] [V live] |
| 0xBC6A28F | 8 | R: [rdi+0x1EBF2D0] | `0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` | dispatcher: rcx = renderer-context vtable pointer | [V] |
| 0xBC6A2AE | 8 | R: [rcx] | `0xBC6A2AE  mov rax,[rcx]` | rax = renderer-context vtable | [V] |
| 0xBC6A2B1 | 8 | R: [rax+0xD0] | `0xBC6A2B1  mov rax,[rax+0xD0]` | rax = vptr[slot 26] = createTexture address | [V] |
| 0xBC6A2C2 | 8 | R: [0xF99FFA0] | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | indirect vcall through CFG trampoline -> createTexture 0xe8143c0 | [V] [V live] |

### Handle trace into TexturePtr/ClientTexture [V] [V live]
texture object = sub_4e05e50 argument + 0x58; returned u16 bgfx handle stored at texture object +0x00; 0x1C-byte create descriptor copied to +0x08; descriptor pointer at +0x18; sdk TexturePtr.h (sizeof 32, mClientTexture+0x00, mResourceLocationPtr+0x10 [V file read]) / ClientTexture.h (empty marker struct) [V file read].

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0xC296E26 | 2 | W: texture_obj+0x00 | `0xC296E26  mov [rdi],ax` | returned u16 bgfx handle stored at texture object +0x00 | [V] |
| 0xC296E2D | 16 | R: r12 (create desc) | `0xC296E2D  movups xmm0,[r12]` | 0x1C create descriptor load, dword 0-3 (16 B movups) | [V] |
| 0xC296E32 | 16 | W: texture_obj+0x08 | `0xC296E32  movups [rdi+8],xmm0` | descriptor copied to texture object +0x08 (16 B movups) | [V] |
| 0xC296E3B | 8 | W: texture_obj+0x18 | `0xC296E3B  mov [rdi+0x18],rdx` | descriptor pointer stored at texture object +0x18 | [V] |

## New work this session — texgroup_load(0x5421c90) -> sub_4e05e50 blocker (new angles)

### texgroup_load(0x5421c90) fully decoded — static universe contains no GPU-issuance call [V]
texgroup_load (7 static xrefs in; batch loader sub_5424290 calls texgroup_load per texture at `0x542430B call 0x5421C90` / `0x542433A call 0x5421C90`) is the CPU pack->GPU root. Its static callees are texture-cache/resource loading only; none reaches sub_4e05e50.

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x5421C90 | - | E: | `0x5421C90  push rbp` | texgroup_load entry; CPU texture load root (group insert group+0x248/+0x250 per L8a notes) | [V] |
| 0x54227AF | 5 | - | `0x54227AF  call 0x18718D0` | texgroup_load -> sub_18718d0 texture-cache lookup/release (the `undecoded 0x18718D0 at 0x54227af` from the checklist) | [V] |
| 0x5422869 | 5 | - | `0x5422869  call 0x5424000` | texgroup_load -> sub_5424000 refcount/teardown helper, not GPU upload | [V] |
| 0x5422C5D | 5 | - | `0x5422C5D  call 0x5424130` | texgroup_load -> sub_5424130 refcount/teardown helper, not GPU upload | [V] |

All other texgroup_load calls: sub_e935700 (free), sub_78ed0, sub_9BC830 (alloc), sub_eec6eb0/ec0 (strings), and indirect `call qword ptr [0xF99FFA0]` (CFG trampoline to sub_eea6040) — none is sub_4e05e50 or reaches it [V this session].

### Texture-cache path: sub_18718d0 -> sub_186dac0 -> ResourceLoadManager enqueue 0x71BC70 [V]
This is the furthest static point the pack->GPU chain reaches; from here it becomes async data-flow (ResourceLoadManager enqueue -> load-complete callback -> deferred-txn job), not a static call edge.

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x18718D0 | - | E: | `0x18718D0  push rbp` | sub_18718d0 entry; texture cache lookup/release; vtable 0xEFCA680 (`lea rax,[0xEFCA680]` at 0x1871A15) | [V] |
| 0x1871AB7 | 5 | - | `0x1871AB7  call 0x186DAC0` | sub_18718d0 -> sub_186dac0 | [V] |
| 0x186DAC0 | - | E: | `0x186DAC0  push rbp` | sub_186dac0 entry | [V] |
| 0x186DE55 | 5 | - | `0x186DE55  call 0x71BC70` | sub_186dac0 -> sub_71BC70 ResourceLoadManager enqueue (async resource load) | [V] |
| 0x186DF9F | 5 | - | `0x186DF9F  call 0x71BC70` | sub_186dac0 -> sub_71BC70 ResourceLoadManager enqueue (second path) | [V] |

### Runtime root of the deferred-txn consumer [V]
sub_6632bf0 ("Deferred Texture Transactions" processor) drains the deferred-txn queue and dispatches each object's vptr[1] through sub_12893d0 -> indirect `call qword ptr [0xF99FFA0]` -> sub_4e05e50 (vtable 0xF215838[1] = sub_4e05e50 [V vt output r57]). sub_6632bf0 is called ONLY by sub_66232b0; sub_66232b0 has 0 static callers (runtime root, entered via job system at runtime).

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x66232B0 | - | E: | `0x66232B0  push rbp` | sub_66232b0 entry; deferred-txn processor root; `xref.py callers 0x66232B0` -> EMPTY (0 static callers) | [V] |
| 0x6632BF0 | - | E: | `0x6632BF0  push rbp` | sub_6632bf0 entry; "Deferred Texture Transactions" processor; called only by sub_66232b0 | [V] |
| 0x6632C55 | 5 | - | `0x6632C55  call 0x12893D0` | sub_6632bf0 -> sub_12893d0 (deferred-txn queue dispatch) | [V] |
| 0x12893D0 | - | E: | `0x12893D0  push rbp` | sub_12893d0 entry; deferred-txn object dispatch; loads vptr[1] and tail-calls via `0x1289490 call qword ptr [0xF99FFA0]`; ret site 0x1289496 = mc_root capture CALLER ret=0x1289496 (all 32 samples) | [V] [V live] |
| 0x1289490 | 8 | R: [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | vptr[1] tail-call through CFG trampoline = sub_4e05e50 | [V] [V live] |

### sub_4e05450 xref (0x4e05xxx neighbor, called from deferred-txn region) [V]
sub_4e05450 (entry `0x4E05450 push rbp`) has 17 static xrefs in, including sub_66232b0 (+0xb3d0) and sub_6632fd0 (+0x1531) inside deferred-txn processing, plus dragon entries 0xc28f220/0xc294b90/0xc294c90, engine 0x4dfbxxx/0x64f0xxx/0x668xxx, backend 0xe86ced0. It is a texture-object method (touches [rcx+0x70], [rcx+0x58] refcounted handles); it is NOT sub_4e05e50, and the texgroup_load chain (sub_18718d0/sub_5424000/sub_5424130) never calls it. [V xref this session]

### Negative results — new angles that did NOT close the blocker [V]
- `rdis.exe "..." imm 0xF215838` -> 0 hits: vtable 0xF215838 (slot 1 = sub_4e05e50) is never materialized as an immediate in .text; no static store of that vptr is findable. [V this session]
- `xref.py str "Deferred Texture Transactions"` -> refs only at 0x66244E7/0x66264E6 (inside sub_66232b0) and 0x6632C19 (sub_6632bf0): consumer side only; no texgroup_load or producer reference. [V this session]
- `xref.py callers 0x4E05E50` -> EMPTY (0 static callers, reconfirmed this session); sub_4e05e50 reachable ONLY via the indirect `call qword ptr [0xF99FFA0]` in sub_12893d0 (vptr[1] of queued deferred-txn objects). [V this session + r59]
- `[0xF99FFA0]` is read-only .rdata (= CFG trampoline sub_eea6040, `jmp rax`); 0 stores; static work on the cell exhausted (r37/r59); rax at the trampoline jmp = vptr[1] of the queued object = sub_4e05e50 [V live mc_root + vt r57].

## What I tried that failed (new angles, not redone)
1. `xref.py callers 0x66232b0` -> EMPTY: the deferred-txn root sub_66232b0 (sub_6632bf0's only static caller) has 0 static callers; cannot build a static path texgroup_load -> ... -> sub_66232b0 -> sub_6632bf0 -> sub_12893d0 -> sub_4e05e50. [V this session + r59]
2. `xref.py callers 0x6632bf0` -> sub_66232b0 only: texgroup_load does not call sub_6632bf0 directly. [V]
3. texgroup_load(0x5421c90) static chain: calls sub_18718d0 at 0x54227AF, sub_5424000 at 0x5422869, sub_5424130 at 0x5422C5D; all are texture-cache/resource/teardown; none reaches sub_4e05e50. sub_18718d0 (texture cache, vtable 0xEFCA680) never reaches sub_4e05e50 [V r57]; texload 0x58a1310 / texload_task 0x541bf00 have 0 static callers and are not on the proven path [V r57].
4. `rdis imm 0xF215838` -> 0 hits: no static store of deferred-txn vtable 0xF215838 (slot 1 = sub_4e05e50). [V this session]
5. `xref.py str "Deferred Texture Transactions"` -> consumer refs only (sub_66232b0, sub_6632bf0); the enqueue/producer side is not statically referenced. [V this session]
6. livemem: not applicable — no statically-known queue/vector anchor for sub_66232b0's this/vector base (r57); deferred-txn enqueue is runtime-only through a data structure, not a call edge.
7. `[0xF99FFA0]` read-only .rdata initializer, 0 stores; static work exhausted.

## CLOSES?
NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. Both endpoints have 0 static callers (`xref.py callers 0x5421C90` and `xref.py callers 0x4E05E50` -> EMPTY), and sub_4e05e50 is reachable only via the indirect `call qword ptr [0xF99FFA0]` (vptr[1]) in sub_12893d0, itself reached through the runtime-only deferred-txn job chain sub_66232b0 (0 static callers) -> sub_6632bf0 -> sub_12893d0. The texgroup_load side terminates at sub_18718d0 -> sub_186dac0 -> ResourceLoadManager enqueue 0x71BC70 (async data-flow); from there to sub_4e05e50 is load-complete callback + deferred-txn enqueue, invisible to static analysis. [V live] evidence (mc_root_4e05e50_callers.txt: 32 samples, ret=0x1289496, RCX = texture objects 'tex'/'legs'/'spear') confirms sub_4e05e50 IS the runtime GPU-upload endpoint for loaded textures, but that is a live capture, not a static call edge. Everything else in L7e IS [V]-proven: Half 1 sampler flag decode + cache (6ax); Half 2a D3D12 backend texture-management chain; createTexture issuance end-to-end below sub_4e05e50 (producer sub_bc73770 writes cmd byte 0x0E, dispatcher vptr[slot 26] -> createTexture 0xe8143c0 -> TextureD3D12::create); handle trace into TexturePtr/ClientTexture (u16 handle at texture_obj+0x00, descriptor at +0x08/+0x18; sdk TexturePtr.h/ClientTexture.h); docs/BGFX_MAP.md cross-refs. Atlas stitchers (L8a/L8b) are separate open units (oc_U-EL8a/oc_U-EL8b), MIRROR_SKIP, not this unit.

## Verification
- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required (every quoted `0xRVA  instr` matched against a fresh rdis dis of the 1.26.62.01 exe).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; only then is line 2 after `## NEXT` set to DONE.

## TOOL REQUESTS
- None. No helper scripts written; no temporary files left behind in the repo (exploration listings kept in /tmp only).
