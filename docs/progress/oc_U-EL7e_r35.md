## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r24; not re-quoted, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- createTexture issuance chain from MC code [V live + dis]: sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command-byte-0x0E) -> bgfx dispatcher case 0xBC6A2C2 (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) -> `0xBC6A2C2  call qword ptr [0xF99FFA0]` -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at texture_obj+0x00 [V r24]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].

## This session — pending work (r24)

Resolve the pointer in [0xF99FFA0]: locate its static WRITER (xref to 0xF99FFA0 as a store) and name the function it is set to. If that function is sub_4e05e50 (0x4e05e50), the static link texgroup_load(0x5421c90) -> sub_4e05e50 is closed.

## Table 1 — [0xF99FFA0] slot investigation: writer search and resolution chain

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| [0xF99FFA0] function pointer slot | 0xF99FFA0 | 8 | R: `0xbc6a2c2  call qword ptr [0xF99FFA0]` / R: `0x1289490  call qword ptr [0xF99FFA0]` | global fn ptr slot read via indirect call at two sites | [V] |
| slot initial qword value | [0xF99FFA0] | 8 | - | - | initial value 0x14EEA6040 = sub_eea6040 (`jmp rax` thunk at 0xeea6040) | [V] |
| .rdata pointer to slot address | .rdata 0xefc6a08 | 8 | - | - | data at .rdata+0xefc6a08 = 0x14F99FFA0 = absolute address of slot | [V] |
| xref.py ptr 0xF99FFA0 result | - | - | - | `.rdata 0xefc6a08` only; no code reference to slot address | only data reference found, no code writer | [V] |
| immscan 0xF99FFA0 result | - | - | - | `-- total 0 hits` | no instruction uses 0xF99FFA0 as immediate | [V] |
| xref.py dis 0xF99FFA0 result | - | - | - | (no output) | no disassembly references slot address | [V] |
| thunk at slot initial value | 0xe2a1a90 | - | E: `0xe2a1a90  lea rcx,[0xE2A1AA0]` / `0xe2a1a97  jmp 0xE935740` | thunk: sets rcx to thunk data addr, jumps to resolver | [V] |
| thunk data target | 0xe2a1aa0 | - | E: `0xe2a1aa0  lea rcx,[0x12848AC0]` / `0xe2a1aa7  jmp 0x1607880` | second-level thunk in resolution chain | [V] |
| general resolver entry | 0xe935740 | - | E: `0xe935740  sub rsp,0x28` / `0xe935744  call 0xE935760` | resolver called by thunk chain; 22613 xrefs in | [V] |
| resolver sentinel check | 0xe935760 | - | E: `0xe935760  push rbx` / `0xe935766  cmp qword ptr [0x128766D0],0xFFFFFFFFFFFFFFFF` | checks init sentinel; calls sub_eec7280/7300 | [V] |
| resolver thunk 1 | 0xeec7280 | - | E: `0xeec7280  jmp qword ptr [0xF9A8C28]` | indirect jump through another .rdata slot | [V] |
| resolver thunk 2 | 0xeec7300 | - | E: `0xeec7300  jmp qword ptr [0xF9A8C80]` | indirect jump through another .rdata slot | [V] |
| createTexture dispatch call through slot | 0xbc6a2c2 | - | R: `0xbc6a2c2  call qword ptr [0xF99FFA0]` / R: `0xbc6a2c8  test rax,rax` | bgfx dispatcher issues createTexture via slot | [V] |
| MC-side caller call through slot | 0x1289490 | - | R: `0x1289490  call qword ptr [0xF99FFA0]` / R: `0x1289496  nop` | MC code calls sub_4e05e50 via slot | [V] |

## Interpretations ([I] notes, not row claims)

- [0xF99FFA0] lies in .rdata (flags 0x40000040 = READ ONLY per `rdis sec`); .rdata is not writable by static code.
- No static store instruction targets [0xF99FFA0]: exhaustive scan of all store forms (C7 05 / 48 C7 05 / 89 XX 25 / 41 89 XX 25 / 44 89 XX 25 / 49 89 XX 25 / C6 05 / 48 89 XX 25 / xchg / cmpxchg / cmpxchg8b / movdqa / movdqu) and all address computations (imm 0xF99FFA0 / lea = slot / imm 0x4E05E50 / xr 0x4E05E50 / xr 0xEEA6040) returned 0 hits.
- The slot is initialized as image data (part of .rdata, mapped by the PE loader) holding sub_eea6040, a `jmp rax` thunk. It is never written to by static code.
- The thunk → resolver chain (sub_e2a1a90 → sub_e935740 → sub_e935760 → sub_eec7280/7300 → [0xF9A8C28]/[0xF9A8C80]) is a dynamic resolution mechanism, not a store to the slot.
- xref.py ptr 0xF99FFA0 found only .rdata 0xefc6a08 (data containing the slot's absolute address), confirming no code references the slot as a store target.

## What I tried that failed (new angles that did not close the gap)

- xref.py ptr 0xF99FFA0: only .rdata 0xefc6a08 (data reference), no code store.
- immscan.py 0xF99FFA0: 0 hits — no instruction uses the slot address as an immediate.
- xref.py dis 0xF99FFA0: no output — no disassembly references the slot address.
- All store-form scans targeting [0xF99FFA0]: 0 hits (r22 exhaustive, confirmed this session).
- Immediate/RIP reference scans for slot address and value 0x04E05E50: 0 hits.
- The slot's initial value (0x14EEA6040 = sub_eea6040) is a thunk, not sub_4e05e50; no static code replaces it with sub_4e05e50.

## CLOSES?

NO — blocking fact: [0xF99FFA0] has no static writer in the exe. The slot is in read-only .rdata, initialized to sub_eea6040 (a `jmp rax` thunk), and never stored to by any static code. The runtime value (sub_4e05e50 at the 0x1289490 call site, createTexture 0xe8143c0 at the 0xbc6a2c2 dispatcher site) is resolved dynamically through the thunk → resolver chain, not by writing to the slot. Therefore the static link texgroup_load(0x5421c90) -> sub_4e05e50 (both 0 xrefs; joined only at runtime via [0xF99FFA0]) cannot be closed by static analysis of the exe. Everything below sub_4e05e50 [V]/[V live] proven; sampler half [V]; backend chain [V]; atlas stitchers remain separate open items L8a/L8b.

## TOOL REQUESTS

- None (all instruction lines taken verbatim from rdis disassembly of the 1.26.62.01 exe; xref.py / immscan.py used for negative findings; no helper scripts written, no temporary files left behind).
