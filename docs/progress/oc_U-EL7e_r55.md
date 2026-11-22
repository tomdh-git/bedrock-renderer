## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures under docs/data/live are read-only orchestrator outputs, cited as [V live] with file:line.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted from fresh rdis this session) / [V live] saw in an orchestrator live-capture reg dump (file cited) / [I] inferred from structure or BGFX_MAP.md / '-' = no instruction or string shows a meaning. Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1; direct call 5, indirect call qword ptr [mem] 8). No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r51; not re-decoded, not re-quoted here)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP.md 6z/6z-2/6aj/1524 confirm base/stride and live texture records); createTexture 0xe8143c0 = vtable slot 26 (BGFX_MAP.md line 403/1812, RTX thunk 0xe83d400 tracks the handle, base 0xe8143c0 calls TextureD3D12::create 0xe81bf30); updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750.
- texgroup_load(0x5421c90) static chain end: `0x54227AF call 0x18718D0` into the texture cache (cache objects vtable 0xEFCA680); texload 0x58a1310 and texload_task 0x541bf00 have 0 static callers and were never decoded; the item-line texgroup_load->texload->texload_task->0x18718D0 chain is NOT statically supported. 0x18718D0 decoded [V r44]: texture-cache lookup/release (vtable 0xEFCA680, vptr[0] destructor dispatch via the same trampoline); it does not reach sub_4e05e50.
- [0xF99FFA0] = read-only trampoline cell = sub_eea6040 (`0xEEA6040 jmp rax`); .text store scan 0 hits, no static writer (r37/r42).

## New work this session — the remaining links attacked with new angles (nothing redone)

### Table 1 — who PRODUCES bgfx command byte 0x0E (createTexture): sub_bc73770 (orchestrator hint step 1)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0xBC73770 | - | E: | `0xBC73770  push rbp` | sub_bc73770 entry (command-byte-0x0E producer; 3 static xrefs in) | [V] |
| [rdi+0x1CFD0C8] | 8 | R: | `0xBC73AA3  mov rbx,[rdi+0x1CFD0C8]` | command-buffer state object (BGFX_MAP.md 6ai) | [V] |
| [rbp+0x2C] | 1 | W: | `0xBC73AAA  mov byte ptr [rbp+0x2C],0xE` / R: `0xBC73ABF  lea rdx,[rbp+0x2C]` / `0xBC73AC3  mov r8d,1` / `0xBC73AC9  call 0xEBCE390` | byte 14 = createTexture staged, then 1 byte written into the command buffer | [V] |
| [rbp+0x2E] | 2 | W: | `0xBC73853  mov [rbp+0x2E],ax` / R: `0xBC73AEB  lea rdx,[rbp+0x2E]` / `0xBC73AEF  mov r8d,2` / `0xBC73AF5  call 0xEBCE390` | ax = handle index from sub_bc79a60 staged, then 2 bytes written into the command buffer right after the cmd byte | [V] |
| [rbx+0xDC5818] | 4 | R: | `0xBC73AAE  mov eax,[rbx+0xDC5818]` / W: `0xBC73AE2  mov [rbx+0xDC5818],ecx` | ring write index, bumped by 2 after the handle | [V] |
| [rbx+0xDC5820+idx] | 1 | R: | `0xBC73AB4  lea rcx,[rbx+rax]` / `0xBC73AB8  add rcx,0xDC5820` | command-buffer entry address (cmd byte at [entry], handle at [entry+1]) | [V] |
| [rsi] | 2 | R: | `0xBC73B70  movzx edi,word ptr [rbp+0x2E]` / W: `0xBC73B74  mov [rsi],di` | 16-bit handle returned to the createTexture API caller | [V] |

sub_bc73770 also parses the bimg/TEX container (`0xBC737C5 call 0xEBD2160`) and allocates the handle (`0xBC7384D call 0xBC79A60`) [V r44]. Live: docs/data/live/bgfx_createtexture_producer.txt — capture at 0xBC73770, every hit `ret=0xBC73EAD` (the `0xBC73EA8 call 0xBC73770` site inside thin wrapper sub_bc73bf0); RDX/R8 point at the 0x1C-byte create descriptor ("TEX" tag `54 45 58 00`, width/height u16 near the end) [V live bytes]. Wrapper: docs/data/live/bgfx_texture_wrapper_bc73bf0.txt — `CALLER ret=0xC296D7E` (inside dragon entry 0xc296b50) [V live]. The producer is reached only from the dragon-layer wrappers (0xbc73bf0/0xbc73ed0/0xbc74120 called from dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80 [V r4]); MC texture code calls none statically.

### Table 2 — bgfx dispatcher: renderer-context vptr[slot 26] = createTexture (hint step 2, issuance)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| [rdi+0x1EBF2D0] | 8 | R: | `0xBC6A28F  mov rcx,[rdi+0x1EBF2D0]` | renderer-context-like object whose vtable is dispatched | [V] |
| [rcx] | 8 | R: | `0xBC6A2AE  mov rax,[rcx]` | vtable pointer loaded into rax | [V] |
| [rax+0xD0] | 8 | R: | `0xBC6A2B1  mov rax,[rax+0xD0]` | vtable slot 26 (0xD0/8 = 26) function pointer = createTexture loaded into rax | [V] |
| 0xBC6A2C2 (dispatcher) | 8 | R: | `0xBC6A2C2  call qword ptr [0xF99FFA0]` / `0xBC6A2C8  test rax,rax` | createTexture issued via CFG trampoline; rax = returned handle tested | [V] |

BGFX_MAP.md lines 1477-1478: handler 0xbc69487 requires magic 0x00584554 ('TEX'), parses the 0x18-byte TextureCreate header, and calls renderer vtable slot 26 (`[rax+0xd0]`) = createTexture; returned pointer stored in the Context per-handle texture table ctx+0x1e55ab8 element+0x10 [V code / I meaning]. Line 1505: byte 14 = createTexture (slot 26). Line 1812: createTexture (slot 26: RTX thunk 0xe83d400 tracks the handle, base 0xe8143c0) locates the record and calls TextureD3D12::create 0xe81bf30. Live: docs/data/live/createtexture_callers.txt — capture at 0xE8143C0, 1612 hits, ONE caller: `CALLER ret=0xBC6A2C8` on every hit (instruction right after `0xBC6A2C2 call qword ptr [0xF99FFA0]`); R8 = 0x1C-byte create descriptor ("TEX" tag visible at +0x10) [V live].

### Table 3 — CFG trampoline [0xF99FFA0] and the rax-at-jmp target (r37 pending part, resolved [V])

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0xEEA6040 | - | E: | `0xEEA6040  jmp rax` | CFG trampoline: jumps to whatever rax holds | [V] |
| cell [0xF99FFA0] | 8 | - | - | `.rdata` read-only initializer = sub_eea6040 (`[data_f99ffa0] = sub_eea6040`); .text store scan 0 hits -> no code writer, never rewritten | [V] |
| 0xF215838+0x008 | 8 | - | - | `rdis vt 0xF215838`: slot +0x000 = sub_4e060b0, slot +0x008 = sub_4e05e50 (size 0x224, `push rbp`), slot +0x010 = non-code 0x0 | vtbl[1] of TextureTransaction vtable 0xF215838 = sub_4e05e50 | [V] |
| .rdata+0xF215840 | 8 | - | - | `xref.py ptr 0x4E05E50`: exactly ONE data pointer, .rdata RVA 0xF215840 holds 0x4E05E50 | single data reference to the sub_4e05e50 address | [V] |
| imm 0xF215838 | - | - | - | `rdis imm 0xF215838`: 0 hits | no code materializes the vtable address (no inline vptr write) | [V] |
| 0x4E060BB | 8 | - | `0x4E060BB  lea rax,[0xF215838]` | sub_4e060b0 loads the TextureTransaction vtable address | [V] |
| 0x4E060C2 | 8 | W: | `0x4E060C2  mov [rcx],rax` | sub_4e060b0 writes vptr = 0xF215838 into transaction object +0x00 | [V] |

The indirect target rax holds at the MC-root trampoline call site IS sub_4e05e50: `0x1289486 mov rax,[rcx]` / `0x1289489 mov rax,[rax+8]` (rax = transaction object vptr[1]) then `0x1289490 call qword ptr [0xF99FFA0]` (ret site `0x1289496 nop`) [V verbatim below]. Live confirmation: docs/data/live/mc_root_4e05e50_callers.txt — capture at 0x4E05E50, hits=150 samples=32 (_status.txt:2), every sample `CALLER ret=0x1289496` (line 3), i.e. sub_4e05e50 is entered exclusively through sub_12893d0's vptr[1] trampoline tail-call; RCX = heap objects carrying texture-descriptor data and name strings ('tex', 'legends', 'spear') [V live bytes]. r37's "capture at 0xEEA6040 entry, read rax" is therefore unnecessary: the rax target is resolved statically ([V] vtable decode + ptr scan + imm scan) and [V live] (32/32 mc_root samples enter sub_4e05e50 via ret=0x1289496).

### Table 4 — sub_12893d0 dispatch body (function containing ret site 0x1289496, the MC-side indirect caller of sub_4e05e50)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x1289486 | 8 | R: | `0x1289486  mov rax,[rcx]` | rax = entry+0x10 transaction object | [V] |
| 0x1289489 | 8 | R: | `0x1289489  mov rax,[rax+8]` | rax = transaction object vptr[1] = sub_4e05e50 at runtime | [V] |
| 0x1289490 (mc root) | 8 | R: | `0x1289490  call qword ptr [0xF99FFA0]` / `0x1289496  nop` | trampoline tail-call; ret site = capture CALLER ret=0x1289496 | [V] [V live] |

sub_12893d0 walks a list of 0x18-byte entries ([obj+0x0]..[obj+0x8], entry {+0 object, +8 refcount, +0x10 transaction object}); per entry it bumps the refcount (`0x1289447 lock cmpxchg [rcx+8],edx`) and tail-calls vptr[1] through the trampoline [V r44; instruction rows above re-verified this session]. Its complete static caller set is {0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0} (`xref.py callers 0x12893D0` -> 0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0 [V]); all four upward chains dead-end at 0-static-caller functions or are internal-only; none is reachable from texgroup_load/texload/texload_task [V r44].

### Table 5 — Minecraft-side pack->GPU chain below sub_4e05e50, and handle trace into the texture object (TexturePtr/ClientTexture)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0x4E05F68 | - | - | `0x4E05F68  add rdi,0x58` | texture object = sub_4e05e50 arg (RCX, TexturePtr*-shaped transaction) + 0x58 | [V] |
| 0x4E05F77 | 5 | S: | `0x4E05F77  call 0xBC41420` / `0x4E05F7C  nop` | sub_4e05e50 -> sub_bc41420 (RCX = texture object); ret site = capture CALLER ret=0x4E05F7C | [V] [V live] |
| 0xBC41B39 | 5 | S: | `0xBC41B39  call 0xC296B50` / `0xBC41B3E  movzx eax,byte ptr [rbp+0x188]` | sub_bc41420 -> dragon entry 0xc296b50; ret site = capture CALLER ret=0xBC41B3E | [V] [V live] |
| 0xC296D79 | 5 | S: | `0xC296D79  call 0xBC73BF0` / `0xC296D7E  nop` / `0xC296D7F  jmp 0xC296E26` | dragon entry -> thin bgfx createTexture wrapper; fallthrough to the handle store | [V] [V live] |
| 0xBC73EA8 | 5 | S: | `0xBC73EA8  call 0xBC73770` / `0xBC73EAD  movzx eax,word ptr [rsp+0x32]` | wrapper -> command-byte-0x0E producer; u16 handle read back from createTexture | [V] [V live] |
| [texture object+0x00] | 2 | W: | `0xC296E26  mov [rdi],ax` (ax from `0xC296E1A  call 0xBC74120`; invalid-handle fallback `0xC296E22  mov ax,0xFFFF`) | returned 16-bit bgfx texture handle stored at texture object +0x00 | [V] |
| [texture object+0x08] | 16 | R: | `0xC296E2D  movups xmm0,[r12]` / W: `0xC296E32  movups [rdi+8],xmm0` | 0x1C-byte create descriptor block copied to texture object +0x08 | [V] |
| [texture object+0x18] | 8 | W: | `0xC296E3B  mov [rdi+0x18],rdx` | descriptor pointer stored at texture object +0x18 | [V] |
| 0xE8143C0 | - | E: | `0xE8143C0  push rbp` | createTexture entry (D3D12 slot 26) | [V] |
| this+0xBDE178 | 8 | R: | `0xE8143F3  lea r12,[rcx+0xBDE178]` | texture record table base = renderer ctx + 0xBDE178 | [V] |
| 0xE814427 | - | - | `0xE814427  imul r8,rbx,0xB8` | record stride 0xB8 per record index | [V] |
| 0xE81455B | 5 | S: | `0xE81455B  call 0xE81BF30` | createTexture -> TextureD3D12::create (backend record fill) | [V] |
| 0xE814560 | 1 | - | - | ret site after `call 0xE81BF30`; = capture CALLER ret=0xE814560 | [V] [V live] |

Capture chain index [V live]: docs/data/live/dragon_texture_caller_bc41420.txt — capture at 0xBC41420, `CALLER ret=0x4E05F7C`; RCX = 0x1C-byte create descriptor (flags 0x80000000, size 0x1C, tag "tex" `74 65 78 00`, width/height fields) [V live bytes]. docs/data/live/dragon_texture_entry_c296b50.txt — capture at 0xC296B50, `CALLER ret=0xBC41B3E`; RCX = texture object, R8 = desc ptr, R9 = flags [V live bytes]. docs/data/live/l8b_texcreate_record.txt — capture at 0xE81BF30, `CALLER ret=0xE814560` (hits=150 samples=24, _status.txt:4); R8 = "Texture: 2815"/"Texture: 2799" runtime-created record names [V live bytes].

End-to-end pack->GPU chain below sub_4e05e50 [V dis + V live]: transaction object --sub_4e05e50(TexturePtr*)--> sub_bc41420 (`0x4E05F77 call 0xBC41420`) --> dragon entry 0xc296b50 (`0xBC41B39 call 0xC296B50`) --> wrapper 0xbc73bf0 (`0xC296D79 call 0xBC73BF0`) --> sub_bc73770 (`0xBC73EA8 call 0xBC73770`) writes bgfx command byte 0x0E (`0xBC73AAA mov byte ptr [rbp+0x2C],0xE`) + 2-byte handle into the command buffer [V Table 1] --> dispatcher (`0xBC6A28F mov rcx,[rdi+0x1EBF2D0]` / `0xBC6A2AE mov rax,[rcx]` / `0xBC6A2B1 mov rax,[rax+0xD0]` / `0xBC6A2C2 call qword ptr [0xF99FFA0]`, slot 26 = createTexture 0xe8143c0 per BGFX_MAP.md; sole caller ret=0xBC6A2C8 [V live]) --> createTexture body (`0xE81455B call 0xE81BF30`, ret site 0xE814560 [V live]) --> D3D12 texture record table this+0xBDE178 stride 0xB8 --> returned u16 handle read back (`0xBC73EAD movzx eax,word ptr [rsp+0x32]` [V live]) and stored at [texture object+0x00] (`0xC296E26 mov [rdi],ax` [V], texture object = arg+0x58 [V]); sdk TexturePtr.h (sizeof==32, mClientTexture+0x00, mResourceLocationPtr+0x10 [V file read]) / ClientTexture.h (empty marker struct) [V file read].

### Table 6 — orchestrator hint: vtable 0xEFCA580 slot 4 (texture-object init calling bgfx createTexture wrapper) — checked, NEGATIVE

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| 0xEFCA580+0x020 | 8 | - | - | `rdis vt 0xEFCA580`: slot +0x020 (literal slot 4, address 0xEFCA5A0) = sub_a3f10 (size 0x2d) | [V] |
| 0xA3F10 | - | E: | `0xA3F10  push rsi` / `0xA3F1B  call 0xA3F40` | sub_a3f10 (slot-4 entry) calls sub_a3f40; NO call to 0xbc73bf0/0xbc73ed0/0xbc74120/0xbc73770 | [V] |
| 0xA3F4C | 8 | - | `0xA3F4C  lea rax,[0xEFCA5A0]` / `0xA3F53  mov [rcx],rax` | sub_a3f40 writes object vptr = 0xEFCA5A0 and refcount-releases a member via `0xA3F8D call qword ptr [0xF99FFA0]` — constructor/destructor-style code, no bgfx wrapper | [V] |
| 0xA34A0 | - | E: | `0xA34A0  push rbp` | sub_a34a0 = candidate slot 4 if the written vptr 0xEFCA5A0 is the real table base; full-range disassembly contains zero calls to 0xbc73bf0/0xbc73ed0/0xbc74120/0xbc73770/0xe8143c0 | [V] |
| xref callers 0xbc73bf0 | - | - | - | `xref.py callers 0xBC73BF0`: dragon entries only (0xc296b50 and other dragon entries), no texture-object init calls the wrapper | [V] |

=> The producer of command byte 0x0E is sub_bc73770, reached only from dragon-layer wrappers (called from dragon entry 0xc296b50); it is NOT called from any texture-object init vtable slot. Hint angle closed: not statically reachable as stated — reported with xref/dis evidence, stopped.

## CLOSES?

NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. sub_4e05e50 (entry 0x4E05E50, size 0x224) has 0 static calling functions (`xref.py callers 0x4E05E50` -> none; `rdis imm 0xF215838` -> 0 hits, no inline vptr-write site) and is entered only at runtime via sub_12893d0's vptr[1] trampoline tail-call `0x1289490 call qword ptr [0xF99FFA0]` (ret site `0x1289496 nop` = capture CALLER ret=0x1289496, all 32 mc_root samples [V live]). [0xF99FFA0] is the read-only trampoline initializer = sub_eea6040 (`0xEEA6040 jmp rax`); no static writer exists. The deferred-texture-transaction construction/push site (sub_4e060b0, vptr 0xF215838 writer `0x4E060BB lea rax,[0xF215838]` / `0x4E060C2 mov [rcx],rax`) has 0 static xrefs (`xref.py callers 0x4E060B0` -> none) and is not reached from texgroup_load/texload/texload_task; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` — 0x18718D0 is a texture-cache lookup/release (vtable 0xEFCA680, vptr[0] dispatch via the same trampoline [V r44]) that does not reach sub_4e05e50. The bind is runtime-async (BgfxFrameBuilder::endFrame 0x66232b0 "Deferred Texture Transactions" flush [BGFX_MAP 6dv] -> sub_6632bf0 -> sub_12893d0 runner -> vptr[1]=sub_4e05e50). Closing it requires the transaction push site (a live capture at sub_4e060b0 entry or the deferred transaction vector); livemem was considered but there is no statically-known anchor (sub_6632bf0's `this`/vector base is not located), so no livemem read is applicable under the brief's last-resort rule.

Everything else in L7e IS [V]/[V]-proven: sampler flag decode + cache (6ax); D3D12 backend texture-management chain; createTexture issuance end-to-end below sub_4e05e50; returned u16 handle stored at texture object+0x00 (= arg+0x58, TexturePtr-shaped); sdk TexturePtr/ClientTexture headers. Atlas stitchers (L8a/L8b) remain separate open units (oc_U-EL8a/oc_U-EL8b), MIRROR_SKIP, not this unit.

## What I tried that failed (new angles, not redone)

- vtable 0xEFCA580/0xEFCA5A0 slot-4 bgfx-wrapper hypothesis (orchestrator hint): NEGATIVE — slot 4 = sub_a3f10 (and sub_a34a0 for the written vptr 0xEFCA5A0); neither calls a bgfx createTexture wrapper [V dis; full-range sub_a34a0 scan found no call to 0xbc73bf0/0xbc73ed0/0xbc74120/0xbc73770/0xe8143c0].
- rdis imm 0xF215838 vtable-address materialization scan — 0 hits [V]: no inline transaction-construction site writing vptr 0xF215838 anywhere in .text.
- livemem read of deferred transaction vector — not applicable: no statically-known anchor (sub_6632bf0's `this`/vector base not located); game is running (pid 13452) but livemem is a last resort requiring a specific rdis-found address.
- Not redone (exhausted in r1-r51): xref.py callers 0xe8143c0/0x4E05E50/0x12893d0/0x1289400 all EMPTY or dead-end; texload 0x58a1310/texload_task 0x541bf00 have 0 static callers and are not on the proven path; [0xF99FFA0] writer search — read-only cell, 0 stores.

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required (every quoted `0xRVA  instr` line matched against a fresh rdis dis of the 1.26.62.01 exe this session).
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; only then is line 2 after `## NEXT` set to DONE.

## TOOL REQUESTS

- None. No helper scripts written; no temporary files left behind in the repo.
