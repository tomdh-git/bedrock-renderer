## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only (live capture logs under docs/data/live are read-only inputs produced by the orchestrator).

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Already proven (cited from r1-r37; not re-decoded, not re-quoted except where a line is re-used below and was re-verified verbatim this session)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- MC-side createTexture issuance chain (live side) [V live + dis r24-r37]: sub_4e05e50 takes a TexturePtr* (rcx = a0; `0x4E05E6E  mov rdi,rcx`; `0x4E05E7E  lea rdx,[rdi+0x58]` so texture_obj = TexturePtr+0x58 [V this session]) → `0x4E05F77  call 0xBC41420` [r24] → sub_bc41420 → 0xc296b50 → wrapper 0xbc73bf0 → producer 0xbc73770 (command-byte-0x0E) → bgfx dispatcher case (`0xBC6A2B1  mov rax,[rax+0xD0]`, slot 26 = 0xe8143c0 [V BGFX_MAP]) → `0xBC6A2C2  call qword ptr [0xF99FFA0]` → createTexture 0xe8143c0 → `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live, docs/data/live/l8b_texcreate_record.txt]); returned handle `0xC296E1A  call 0xBC74120` (ax) → `0xC296E26  mov [rdi],ax` at [texture_obj+0x00] = TexturePtr+0x58 [V r24]; sdk TexturePtr/ClientTexture headers [V file read]. sub_4e05e50: fn 0x4E05E50..0x4E07E50, 0 static xrefs [V this session + r37].

## New work this session — new angles at the remaining blocker (static link texgroup_load(0x5421c90) -> sub_4e05e50)

### 1. sub_12893d0 decoded — the only static entry to sub_4e05e50

Live capture docs/data/live/mc_root_4e05e50_callers.txt: 150 hits / 32 samples; every sample is CALLER ret=0x1289496, i.e. the call site `0x1289490  call qword ptr [0xF99FFA0]` inside sub_12893d0 with ret site `0x1289496  nop`. sub_12893d0 (0x12893d0..0x128b3d0, size 0x2000, 13 xrefs in) is a listener-dispatch loop: it walks the entry list [obj+0]..[obj+8] in 0x18-byte steps, and for each entry whose +0x10 is a live listener object it calls listener->vptr[1] through the [0xF99FFA0] trampoline, then releases the listener through vptr[0]. Verbatim instruction proof:

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| sub_12893d0 entry | 0x12893d0 | - | - | `0x12893d0  push rbp` | listener-dispatch entry; 0x2000 bytes, 13 xrefs in | [V] |
| list begin | obj+0x0 | 8 | R: `0x1289406  mov r13,[rcx]` | r13 = [obj+0] = list-begin pointer | [V] |
| list end | obj+0x8 | 8 | R: `0x1289409  mov r14,[rcx+8]` | r14 = [obj+8] = list-end pointer | [V] |
| entry stride | entry stride 0x18 | 8 | R/W: `0x1289420  add r13,0x18` `0x1289424  cmp r13,r14` `0x1289427  je 0x128954F` | entries are 0x18 bytes; loop walks until r13 == end | [V] |
| entry object ptr | entry+0x8 | 8 | R: `0x1289431  mov rcx,[r13+8]` | rcx = entry+0x8 = refcounted object pointer | [V] |
| object refcount | object+0x8 | 8 | R/W: `0x1289447  lock cmpxchg [rcx+8],edx` | atomic refcount increment on object+0x8 | [V] |
| entry listener ptr | entry+0x10 | 8 | R: `0x128947d  mov rcx,[r13+0x10]` `0x1289497  mov rcx,[r13+0x10]` | rcx = entry+0x10 = listener object pointer (reloaded for the release path) | [V] |
| listener vptr | listener+0x0 | 8 | R: `0x1289486  mov rax,[rcx]` `0x12894a8  mov rax,[rcx]` | listener vptr; feeds the vptr[1] call at 0x1289490 and the vptr[0] Release call at 0x12894b3 | [V] |
| listener vptr[1] | listener+0x8 | 8 | R: `0x1289489  mov rax,[rax+8]` | rax = vptr[1] = sub_4e05e50 at runtime | [V] + [V live] |
| indirect call sites + data init | [0xF99FFA0] | 8 | R: `0x1289490  call qword ptr [0xF99FFA0]` `0x12894b3  call qword ptr [0xF99FFA0]` | trampoline tail-call sites (vptr[1] notify, vptr[0] Release); ret site `0x1289496  nop`; all 32 capture samples ret=0x1289496 (docs/data/live/mc_root_4e05e50_callers.txt). The qword at 0xF99FFA0 is a read-only .rdata PE initializer = abs 0x14EEA6040 = sub_eea6040 (`0xEEA6040  jmp rax`, 0 xrefs in); no code writer (section read-only) | [V] + [V live] |
| only static data ptr to sub_4e05e50 | 0xF215840 (.rdata) | 8 | [0xF215840] | - | `ptr 0x4E05E50` = 1 hit: vtable 0xF215840 slot[0] = sub_4e05e50, slot[1] = non-code 0x0; `xr 0xF215840` = 0 xrefs; `imm 0xF215840` = 0 hits → never installed as a vptr statically | [V] |

### 2. sub_12893d0 caller island — disconnected from texgroup_load

`rdis callers 0x12893d0` = 4 calling functions: sub_1145c20 (2 call sites), sub_6622610 (1), sub_66232b0 (8), sub_6632bf0 (2) [V this session]. One level up: sub_1145c20 <- sub_882ee0 (1 site); sub_6622610 <- sub_661a770, sub_661f200, sub_66232b0, sub_6632fd0, sub_bbd42d0, sub_bbd4490, sub_e86ced0 (1 site each); sub_66232b0 has 0 callers (it is a root); sub_6632bf0 <- sub_66232b0 (2 sites) [V this session]. None of these is texgroup_load 0x5421c90, texload 0x58a1310 or texload_task 0x541bf00, and all are in the 0x0882ee0..0xbbd4490 / 0xe86ced0 range, not the 0x54xxxx texture pack range.

### 3. Cache completion continuations — no link to the island

The static pack->GPU chain ends at the texture cache sub_18718d0 (called from texgroup_load at `0x54227af  call 0x18718D0` [V r2]) whose async completion paths 0x186DAC0 / 0x186E1E0 / 0x186E460 were decoded [V r2]: `rdis callees` on each shows calls only to sub_58ca10 (desc builder) and sub_71bc70 (ResourceLoadManager async enqueue; sub_186DAC0 also calls sub_76af20 and sub_9bc830) [V this session]. None calls sub_12893d0 or any island function, so the static cache chain cannot reach sub_4e05e50.

### [0xF99FFA0] trampoline (r37 finding, not redone)

[0xF99FFA0] is set to trampoline sub_eea6040 (`0xEEA6040  jmp rax`, .rdata read-only initializer = 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040), NOT sub_4e05e50; no code writer exists (.text store scan for [0xF99FFA0] = 0 hits; .rdata read-only). The real callee sub_4e05e50 lives in rax = listener->vptr[1] at runtime, observed live [V live].

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has 0 static xrefs and is entered only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (trampoline sub_eea6040 `0xEEA6040  jmp rax`), observed live at capture ret site 0x1289496 [V live]. The only static data pointer to sub_4e05e50's address is .rdata vtable 0xF215840 slot[0] (slot[1] = non-code; xr = 0 xrefs, imm = 0 hits — never installed as a vptr). sub_12893d0's static callers form a separate island (sub_66232b0 is a root with 0 callers; none of the island is in the 0x54xxxx pack->GPU tree) and the cache completion callbacks 0x186DAC0/0x186E1E0/0x186E460 call only sub_58ca10/sub_71bc70 (+sub_76af20/sub_9bc830). New angles tried this session and failed: (1) ptr/imm/xr hunt for sub_4e05e50's address → single unanchored .rdata pointer; (2) two-level caller trace of sub_12893d0 → disconnected island; (3) completion-callback callees → no link. The bind texgroup_load -> sub_4e05e50 is runtime-only (vtable[1] patched at runtime, observed live) and cannot be closed by static analysis. Everything else in L7e is [V]-proven: sampler flag decode + cache (6ax), D3D12 backend texture-management chain, createTexture issuance chain incl. handle store at TexturePtr+0x58, sdk TexturePtr/ClientTexture headers. Atlas stitchers (L8a/L8b) are separate units (MIRROR_SKIP).

## TOOL REQUESTS

- None. All instruction lines re-verified verbatim against fresh rdis dis this session; live capture logs are read-only inputs; no helper scripts written; no temporary files left behind.
