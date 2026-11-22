## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator).

Tags: [V] = saw in disassembly (RVA cited, verbatim line quoted) / [V live] = saw in an orchestrator live capture log (file cited) / [I] = inferred from structure or BGFX_MAP / [?] = unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r24; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis r24]: sub_4e05e50 -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher (RendererContext slot 26 = 0xe8143c0 via [reg+0xD0]) -> createTexture 0xe8143c0 -> TextureD3D12::create (ret 0xe814560 [V live]); returned handle stored at [texture_obj+0x00] with texture_obj = TexturePtr+0x58 [V]; sdk TexturePtr/ClientTexture [V file read]. Atlas stitchers (L8a/L8b) out of scope (MIRROR_SKIP).

## This session — new angle: the runtime bind texgroup_load(0x5421c90) -> sub_4e05e50

r36/r37 concluded CLOSES NO because sub_4e05e50 has 0 static xrefs and [0xF99FFA0] is a read-only .rdata trampoline with no writer. This session attacked that blocker from a new angle using the two newly available captures (docs/data/live/mc_root_4e05e50_callers.txt, docs/data/live/l8b_texcreate_record.txt) plus fresh rdis disassembly, to confirm whether any static path exists.

(1) Indirect caller of sub_4e05e50, decoded [V]. mc_root_4e05e50_callers.txt captured sub_4e05e50 entry; all 32 samples have ret=0x1289496, i.e. the call site `0x1289490  call qword ptr [0xF99FFA0]` and ret site `0x1289496  nop`. Fresh `rdis dis 0x1289450` shows the containing function reads the object vptr and tail-calls vptr[1] through the trampoline: `0x128947d  mov rcx,[r13+0x10]`, `0x1289486  mov rax,[rcx]`, `0x1289489  mov rax,[rax+8]`, `0x1289490  call qword ptr [0xF99FFA0]`. rdis reports this function `[0x1289450..0x128b450) size 0x2000 0 xrefs in` — no static caller. `xref.py callers 0x1289450` confirms empty.

(2) [0xF99FFA0] is the universal indirect-call trampoline, read-only .rdata [V].
  - `0xEEA6040  jmp rax` (2 bytes): fresh `rdis dis 0xEEA6040` and preflight 0xEEA6040.md both show `eea6040 jmp rax` + int3 padding; fn = `[0xeea6040..0xeea6045) size 0x5 0 xrefs in`. Pure tail-call trampoline; rax holds whatever the caller set (here vptr[1] = sub_4e05e50). No further static decoding possible.
  - PE .rdata at RVA 0xF99FFA0 = 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040 -> [0xF99FFA0] = sub_eea6040 trampoline, NOT sub_4e05e50.
  - _f99ffa0_refs.txt / _f99ffa0_xr.txt: `call qword ptr [0xF99FFA0]` appears in hundreds of functions (0x730e9 .. 0x7cf4e, 1088051 xrefs) — the shared vtable-call trampoline for ALL indirect calls, not a sub_4e05e50-specific pointer.
  - .rdata section flags 0x40000040 = read + initialized data -> read-only, never rewritten; .text store scan for `mov [rip+disp32]` targeting 0xF99FFA0 = 0 hits -> no code writer.
  - _eea6040_refs.txt: eea6040 referenced only at eea603c (func eea6020) — no store repointing [0xF99FFA0].

(3) sub_4e05e50 has 0 static xrefs/callers [V]: `xref.py callers 0x4E05E50` -> empty; rdis `fn 0x4E05E50` (0x4E05E50..0x4E06074) -> 0 calling functions.

(4) Live capture [V live]: mc_root_4e05e50_callers.txt — all 32 samples ret=0x1289496; RCX = TexturePtr* (first sample 0x3908FFDE900) pointing at objects whose bytes contain "tex\0". Confirms the bind is real at runtime through dynamic vtable[1] dispatch, but NOT reachable by static code.

(5) l8b_texcreate_record.txt [V live]: capture at 0xE81BF30 (TextureD3D12::create), ret=0xE814560 in all samples; R8 carries texture-name strings ("Texture: 2815", ...) and descriptor pointers. Confirms createTexture -> TextureD3D12::create is live; does not restore a static texgroup_load link.

## Findings table (new-angle verification)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| trampoline sub_eea6040 | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax (the vptr[n] indirect-call target) | [V] |
| vptr load | [rcx+0x0] | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | rax = object vptr (indirect caller of sub_4e05e50) | [V] |
| vptr[1] load = callee in rax | [rax+0x8] | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | rax = obj->vptr[1] = sub_4e05e50 at runtime | [V] |
| indirect call through [0xF99FFA0] | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` | trampoline tail-call; rax = vptr[1] = sub_4e05e50; pushed ret = 0x1289496 | [V] + [V live] |
| capture ret site | 0x1289496 | 1 | - | `0x1289496  nop` | instruction right after call; matches capture ret=0x1289496 in all 32 samples | [V live] |
| [0xF99FFA0] .rdata initializer | 0xF99FFA0 | 8 | [0xF99FFA0] | - | PE .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040; read-only section, no code writer | [V] |

## Interpretation

[0xF99FFA0] holds sub_eea6040 (`0xEEA6040  jmp rax`, absolute 0x14EEA6040), the universal indirect-call trampoline used via `call qword ptr [0xF99FFA0]` for ALL vtable calls. The actual callee sub_4e05e50 lives in rax = obj->vptr[1], tail-called through the trampoline. [0xF99FFA0] is NOT set to sub_4e05e50, is read-only .rdata, and has no code writer. sub_4e05e50 has 0 static xrefs and its only static call-site (sub_1289450) itself has 0 static callers. Therefore no static path texgroup_load(0x5421c90) -> sub_4e05e50 exists; the bind is runtime-only via dynamic vtable[1] dispatch, observed live [V live].

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 (0x4E05E50..0x4E06074) has 0 static xrefs/callers (`xref.py callers 0x4E05E50` empty). Its sole static call-site is sub_1289450's vtable[1] indirect call `0x1289490  call qword ptr [0xF99FFA0]` (ret site `0x1289496  nop`), and sub_1289450 itself has 0 static callers (`xref.py callers 0x1289450` empty; rdis `dis 0x1289450` -> "0 xrefs in"). [0xF99FFA0] is a read-only .rdata PE initializer = 0x14EEA6040 = sub_eea6040 (`0xEEA6040  jmp rax`, 2 bytes), the universal indirect-call trampoline (hundreds of `call qword ptr [0xF99FFA0]` sites in _f99ffa0_refs.txt), NOT sub_4e05e50, with no code writer (read-only section; .text store scan = 0 hits). The texture-creation issuance itself (sub_4e05e50 -> sub_bc41420 -> ... -> createTexture 0xe8143c0 -> handle stored at [texture_obj+0x00] = TexturePtr+0x58) is [V live + dis] proven, but the static texgroup_load bind is runtime-only and cannot be closed by static analysis.

## TOOL REQUESTS

- None. Static analysis is exhausted: [0xF99FFA0] is a read-only .rdata PE initializer (0x14EEA6040 = sub_eea6040 `jmp rax` trampoline), no code store exists; sub_4e05e50 and its caller sub_1289450 both have 0 static callers; all instruction lines re-verified verbatim against fresh rdis dis this session; live capture logs are read-only inputs. No helper scripts written; no temporary files left behind.
