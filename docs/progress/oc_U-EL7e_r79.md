## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). Static analysis only, plus read-only live captures produced by the orchestrator (docs/data/live/*.txt). Never launch the game.

Tags: [V] saw in disassembly or live capture (RVA cited, verbatim line quoted), [I] inferred from structure/source, [?] unknown. Row rule: one annotated row per distinct offset; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis/live capture) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction.

## Already proven (do NOT redo — cited from r1/r2/r3 / verified files)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts. Called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 in oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture slot 26 = 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. createTexture reached only via indirect [vptr+0xD0] / bgfx command byte 14 -> dispatcher handler; xref.py callers 0xe8143c0 = EMPTY (no static caller).
- Minecraft-side cache (not the gap): texgroup_load 0x5421c90 -> texture cache 0x18718d0 at `0x54227af  call 0x18718D0` [V]; cache BST/completion/enqueue 0x71BC70 decoded [V] (r2/r3). texload 0x58a1310 and texload_task 0x541bf00: xref.py callers EMPTY, never decoded, not called by texgroup_load statically [V r3].

## New work this session — the pending link: Minecraft-side pack->GPU -> createTexture -> TexturePtr/ClientTexture handle write

### The indirect caller of sub_4e05e50 (names it)

Orchestrator capture mc_root_4e05e50_callers.txt (capture at 0x4E05E50 entry), line 3:
`CALLER ret=0x1289496 first_hit=1`
and line 4:
`RCX=3908FFDE900 hit=1 ret=0x1289496 385821A8F67F0000...`
So sub_4e05e50 is entered with return address 0x1289496, i.e. called from the instruction at 0x1289490, with RCX = 0x3908FFDE900 (the texture object / TexturePtr*) [V live].

Disassembly of the function containing 0x1289496 — sub_1289480 [0x1289480..0x128b480), size 0x2000, 0 static xrefs in (reached only indirectly):
`128947d  mov rcx,[r13+0x10]`        object pointer taken from list entry
`1289486  mov rax,[rcx]`             vtable pointer loaded
`1289489  mov rax,[rax+8]`           vtable slot 1 -> rax
`1289490  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040`  trampoline `jmp rax`
`1289496  nop`                       return address = 0x1289496

sub_1289480 walks a list of 0x18-stride entries ({data, refcount@+8, object*@+0x10}) and, for each live object, issues a virtual call on the object's vtable slot 1 via the [0xF99FFA0] trampoline. The mc_root capture proves rax = sub_4e05e50 (0x4E05E50) at that site [V live]. [0xF99FFA0] is read-only .rdata = trampoline sub_eea6040 (`jmp rax`), no writer [V r37]; static work exhausted [r37].

### sub_4e05e50 — texture object / TexturePtr* consumer

sub_4e05e50 [0x4e05e50..0x4e07e50), size 0x2000, 0 static xrefs in (reached only via the indirect vcall above). Prototype: RCX = texture object*:
`4e05e50  push rbp`                  entry
`4e05e6e  mov rdi,rcx`               rdi = texture object (a0)
`4e05e71  mov rax,[rcx+0x18]  ; R a0+0x18`  object field +0x18 read
`4e05f74  mov rcx,rdi`               rcx = a0 (+0x58 after `4e05f68 add rdi,0x58`)
`4e05f77  call 0xBC41420  ; -> sub_bc41420`  issues create via sub_bc41420 [V]
`4e05f7c  nop`

sdk mce::TexturePtr (src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h):
`class TexturePtr { std::shared_ptr<void> mClientTexture; std::shared_ptr<void> mResourceLocationPtr; ... }; static_assert(sizeof(TexturePtr) == 32);`  [V source]
mce::TexturePtr is 0x20 bytes. The in-game object passed in RCX (0x3908FFDE900 in the capture) is read up to +0xE0, so it is a ClientTexture/BedrockTexture carrying the TexturePtr, not the bare 0x20-byte SDK stub [I layout].

### Issuance chain to createTexture + handle write (proven [V live] in earlier sessions; not re-performed here)

`sub_4e05e50` -> `sub_bc41420` at `0x4E05F77  call 0xBC41420` [V this session]
`sub_bc41420` -> dragon entry `0xc296b50` at `0xbc41b39  call 0xC296B50  ; -> sub_c296b50` [V live r7]
`0xc296b50` -> `0xbc73bf0` -> `0xbc73770` (writes bgfx command byte 0x0E) [V live r4]
`0xbc73770` -> bgfx command-buffer dispatcher (case at 0xBC6A2C3) -> `createTexture 0xe8143c0` [V live r4/r5]
handle store `[texture_obj+0x00]` at `c296e26  mov [rdi],ax` [V live r7]

Full chain [V live]:
sub_1289480 (vcall [0xF99FFA0], rax=sub_4e05e50)
  -> sub_4e05e50(texture object/TexturePtr*, RCX=0x3908FFDE900)
    -> sub_bc41420
      -> 0xc296b50 -> 0xbc73bf0 -> 0xbc73770(cmd byte 0x0E) -> dispatcher -> createTexture 0xe8143c0
        -> handle store [texture_obj+0x00] at 0xc296e26

## Table — the resolved indirect link (this session)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_4e05e50 entry | 0x4E05E50 | - | E: `4e05e50  push rbp` | texture-init entry (0 static xrefs in) | [V] |
| indirect caller return address | ret=0x1289496 | - | `CALLER ret=0x1289496 first_hit=1` (mc_root_4e05e50_callers.txt line 3) | sub_4e05e50 entered from 0x1289490 | [V live] |
| TexturePtr*/texture-object argument | RCX | 8 | `RCX=3908FFDE900 hit=1 ret=0x1289496` (mc_root_4e05e50_callers.txt line 4) | RCX = texture object / TexturePtr* at entry | [V live] |
| list object pointer | obj+0x10 | 8 | R: `128947d  mov rcx,[r13+0x10]` | object* taken from list entry | [V] |
| vtable load | obj+0x00 | 8 | R: `1289486  mov rax,[rcx]` | vtable pointer loaded | [V] |
| vtable slot 1 -> rax | vtable+0x08 | 8 | R: `1289489  mov rax,[rax+8]` | slot-1 function pointer into rax | [V] |
| indirect vcall | [0xF99FFA0] | 8 | R/C: `1289490  call qword ptr [0xF99FFA0]  ; [data_f99ffa0] = sub_eea6040` | calls sub_eea6040 = `jmp rax` (rax = sub_4e05e50) | [V] |
| return after vcall | 0x1289496 | - | `1289496  nop` | return address = 0x1289496 | [V] |
| sub_4e05e50: RCX -> RDI | arg1 | 8 | `4e05e6e  mov rdi,rcx` | texture object copied to rdi | [V] |
| sub_4e05e50: field read | a0+0x18 | 8 | `4e05e71  mov rax,[rcx+0x18]  ; R a0+0x18` | object field +0x18 read | [V] |
| sub_4e05e50 -> sub_bc41420 | - | - | `4e05f74  mov rcx,rdi` / `4e05f77  call 0xBC41420  ; -> sub_bc41420` | issues create via sub_bc41420 | [V] |
| TexturePtr layout | mce::TexturePtr | 0x20 | source: TexturePtr.h | two shared_ptr members; sizeof==32 | [V source] |
| sub_bc41420 -> dragon entry | 0xbc41b39 | - | `0xbc41b39  call 0xC296B50  ; -> sub_c296b50` | sub_bc41420 calls 0xc296b50 | [V live r7] |
| handle store | texture_obj+0x00 | 8 | W: `c296e26  mov [rdi],ax` | returned handle stored at [texture_obj+0x00] | [V live r7] |
| createTexture issuance | 0xe8143c0 | - | bgfx cmd byte 0x0E -> dispatcher case 0xBC6A2C3 -> `0xe8143c0` | D3D12 createTexture slot 26 | [V live r4/r5] |

## Interpretations ([I] notes, not row claims)

- sub_1289480 is reached only indirectly (0 static xrefs in); it is the "who calls sub_4e05e50" indirect caller named by the mc_root capture [V live].
- sub_4e05e50 is vtable slot 1 of live texture objects; sub_1289480 dispatches to it via the [0xF99FFA0] trampoline [V live].
- [0xF99FFA0] is read-only .rdata = sub_eea6040 (`jmp rax`), no writer [V r37]; rax = sub_4e05e50 resolved [V live mc_root]. Static work exhausted [r37].
- The texture object passed to sub_4e05e50 (RCX=0x3908FFDE900) is read up to +0xE0, so it is a ClientTexture/BedrockTexture carrying the mce::TexturePtr [I layout].

## CLOSES?

NO — blocking fact: no static [V] instruction path exists from texgroup_load(0x5421c90) to sub_4e05e50/sub_1289480 (both have 0 static xrefs in; texgroup_load is a root, sub_4e05e50 is reached only through the indirect vcall [0xF99FFA0]). Everything from sub_4e05e50 onward to createTexture issuance and the [texture_obj+0x00] handle store IS proven [V]/[V live], but the pack->GPU entry hop (texgroup_load -> sub_4e05e50) cannot be bound statically; static work is exhausted [r37] and the link is resolved only [V live]. Sampler half (6ax) [V]; D3D12 backend texture-management chain [V]; atlas stitchers remain separate open items L8a/L8b.

## Verification

Verbatim `0xRVA  instr` lines copied from `rdis.exe dis` output; live capture lines copied verbatim from docs/data/live/mc_root_4e05e50_callers.txt. `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` and `python tools/delegate.py check docs/progress/oc_U-EL7e.md` required before CLOSES? is final.

## TOOL REQUESTS

- None (no helper scripts written; all instruction lines verbatim from rdis/live capture; a capture at 0xEEA6040 to read rax could not be queued — 4 pending — but mc_root capture already resolves rax = sub_4e05e50 [V live], so it is not needed).
