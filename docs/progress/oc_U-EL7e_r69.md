## NEXT
DONE

UNIT U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"
Output file: docs/progress/oc_U-EL7e.md (only this file)
Source checklist line: docs/RENDER_CHECKLIST.md:338
`- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): ... Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.
Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.
Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1).

================================================================================
1. HALF 1 — sampler flag decode + sampler cache (6ax): already closed [V], cited not re-derived
================================================================================

- docs/functions/e820500.md decodes 0xe820500 (sampler descriptor builder + cache) instruction-complete.
- src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Correction vs BGFX_MAP 6ax: bit 28 (0x10000000) selects MaxLOD 3.0 vs FLT_MAX — NOT the border-colour selector; the border colour comes from the r9 table (bits 24..27) gated by BORDER address mode (see docs/functions/e820500.md line 22 and docs/progress/materials-visuals.md).

================================================================================
2. HALF 2 — texture/atlas management (the pending half): Minecraft-side pack->GPU chain
================================================================================

This unit proves the Minecraft-side texture->GPU root through D3D12 createTexture 0xe8143c0 and the handle write back into the texture object / TexturePtr::mClientTexture. The D3D12 backend texture-management chain (record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0 slot 26, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750) was proven in prior rounds (B7a/B7b/B9b, 6z/6aj) and is cited, not redone. Atlas stitchers remain open items L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

Proven downstream chain [V live + dis] (cited from prior rounds, not redone):
sub_4e05e50 -> `0x4E05F77  call 0xBC41420` -> sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (writes bgfx command byte 0x0E) -> bgfx dispatcher -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live, l8b_texcreate_record]). Returned handle `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` at [texture_obj+0x00] [V r24]; texture_obj = TexturePtr+0x58 (`0x4E05F68  add rdi,0x58`); sdk TexturePtr/ClientTexture [V file read].

================================================================================
3. THIS SESSION — newly decoded: indirect caller sub_12893d0 + root sub_4e05e50
================================================================================

docs/data/live/mc_root_4e05e50_callers.txt (capture rva=0x4E05E50, kind=regs): line 3 `CALLER ret=0x1289496 first_hit=1`; all 15/32 hits ret=0x1289496 => sub_4e05e50 has ONE observed call site, the call ending at 0x1289496 [V live]. RCX = vptr-bearing heap ClientTexture objects (vptr 0x...A8215838-class, name fields "tex"/"legs"/"_spear"/"hud"/"mary") => TexturePtr::mClientTexture pointee, not the 32B TexturePtr stub [V live].

sub_12893d0 (entry 0x12893D0, walked by rdis dis 0x1289380) walks a 0x18-byte entry array [this+0]..[this+8]; per non-null entry it addrefs entry[+8], copies the entry, then tail-calls entry[+0x10]->vtable[1] (in rax) through [0xF99FFA0]=sub_eea6040 (`jmp rax`) with rcx=entry[+0x10]; afterwards NULLs entry[+0x10] and releases the old object via vtable[0]. The indirect call site is 0x1289490 (fall-through 0x1289496 = the capture ret). Live capture: 15/15 hits ret=0x1289496 => entry[+0x10]->vtable[1] = sub_4e05e50. So sub_12893d0 is the indirect caller of sub_4e05e50 [V] + [V live].

sub_4e05e50 (entry 0x4E05E50, fn 0x4E05E50..0x4E06074): releases old texture at this+0x10/this+0x18 via vtable calls through [0xF99FFA0], then builds a GPU texture from the descriptor at this+0x58 with sampler/flags from this+0xE0 and issues it via `0x4E05F77  call 0xBC41420` (call ends at 0x4E05F7C = LIVE RESULT 5 ret [V live]) -> ... -> createTexture 0xe8143c0. Handle lands in [texture_obj+0x00] at 0xC296E26 [V live]. sub_4e05e50 has 0 static xrefs; reached only via sub_12893d0's indirect vtable[1] tail-call.

================================================================================
4. FIELD / ACCESS TABLE
================================================================================

| offset     | size | site(s)                                  | verbatim `0xRVA  instr`                        | meaning                                                                               | tag     |
|------------|------|------------------------------------------|------------------------------------------------|---------------------------------------------------------------------------------------|---------|
| 0x0        | 8    | 0x1289406, 0x4E06010                     | `0x1289406  mov r13,[rcx]`                     | [this+0] = entry-array begin loaded as walk cursor r13 (sub_12893d0); [rsi] = output handle slot cleared to 0 on skip path (sub_4e05e50) | [V]     |
| 0x8 (end)  | 8    | 0x1289409, 0x1289431                     | `0x1289431  mov rcx,[r13+8]`                   | [this+8] = entry-array end (r14); entry[+8] = refcounted object loaded as rcx         | [V]     |
| 0x8 (rc)   | 4    | 0x1289447                                | `0x1289447  lock cmpxchg [rcx+8],edx`          | atomic refcount increment of entry[+8] object (retry loop at 0x1289440)               | [V]     |
| 0x10       | 8    | 0x128947d, 0x1289497, 0x4E05E8C          | `0x128947d  mov rcx,[r13+0x10]`                | entry[+0x10] = texture object loaded as `this` for the indirect call (then NULLed at 0x128949B); sub_4e05e50 reads old texture at this+0x10 | [V]     |
| 0x18 (this)| 8    | 0x4E05E71                                | `0x4E05E71  mov rax,[rcx+0x18]`                | this+0x18 object released via vtable[1] ([0xF99FFA0] call at 0x4E05E86)               | [V]     |
| 0x18 (clr) | 16   | 0x662264E                                | `0x662264E  movups [rsi+0x18],xmm1`            | sub_6622610 clears [rsi+0x18] before rebuilding the entry passed to sub_12893d0         | [V]     |
| 0x20       | 16   | 0x6632C2F                                | `0x6632C2F  movups [rcx+0x20],xmm1`            | sub_6632bf0 ("Deferred Texture Transactions") clears transaction record +0x20           | [V]     |
| 0x28       | 8    | 0x662263F                                | `0x662263F  mov qword ptr [rsi+0x28],0`        | sub_6622610 clears a0+0x28                                                             | [V]     |
| 0x58       | 4    | 0x4E05F68                                | `0x4E05F68  add rdi,0x58`                      & this+0x58 descriptor address passed as rcx to sub_bc41420; texture_obj = TexturePtr+0x58 | [V]     |
| 0xE0       | 8    | 0x4E05F61                                | `0x4E05F61  mov r9,[rdi+0xE0]`                 | this+0xE0 sampler/flag word (6ax sampler flag) passed as r9 to sub_bc41420              | [V]     |
| 0xF99FFA0  | 6    | 0x1289490, 0x12894b3, 0x4E05E86          | `0x1289490  call qword ptr [0xF99FFA0]`        | indirect call through trampoline [0xF99FFA0] = sub_eea6040 (`jmp rax`, verified at 0xEEA6040); rax = vtable[1] = sub_4e05e50 (15/15 live hits ret=0x1289496) | [V]     |
| nop @0x4E05F7C | 1 | 0x4E05F7C                                | `0x4E05F7C  nop`                               | end of `call 0xBC41420` (starts 0x4E05F77) = LIVE RESULT 5 ret=0x4E05F7C [V live]    | [V live]|
| call sub_bc41420 | 5 | 0x4E05F77                                | `0x4E05F77  call 0xBC41420`                    | sub_4e05e50 -> sub_bc41420 (desc at &this+0x58, r8=&saved obj, r9=this+0xE0) -> ... -> createTexture 0xE8143C0 | [V]     |
| call sub_12893d0 | 5 | 0x6622662, 0x6632C55, 0x1145D5A, 0x1145EE5 | `0x6622662  call 0x12893D0`                    | static direct calls into sub_12893d0: sub_6622610 (0x6622662), sub_6632bf0 "Deferred Texture Transactions" (0x6632C55), sub_1145c20 (0x1145D5A, 0x1145EE5); xref.py callers additionally names sub_66232b0 (exact site not pinned) | [V]     |
| call sub_6632bf0 | 5 | 0x66233AE                                | `0x66233AE  call 0x6632BF0`                    | sub_66232b0 (root, 0 code xrefs) -> sub_6632bf0 -> sub_12893d0                         | [V]     |
| trampoline 0xEEA6040 | 2 | 0xEEA6040                                | `0xEEA6040  jmp rax`                           | trampoline body: [0xF99FFA0] = sub_eea6040 = jmp rax, real target held in rax           | [V]     |
| handle store [texture_obj+0x00] | 2 | 0xC296E26                                | `0xC296E26  mov [rdi],ax`                      | returned createTexture handle stored at texture object +0x00 (r24); texture_obj = TexturePtr+0x58 | [V]     |

================================================================================
5. CLOSES?
================================================================================

NO — single blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50.

What IS proven (all [V]/[V live]):
- sampler flag decode + sampler cache (6ax): closed [V] in docs/functions/e820500.md + src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h (not re-derived here).
- D3D12 backend texture-management chain: closed [V] (record table this+0xBDE178 stride 0xB8; slots 26 createTexture 0xe8143c0, 28 updateTexture 0xe814a70, 30 readTexture 0xe8150f0, 31 resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0 / blitSetup 0xe819750).
- createTexture issuance chain downstream of sub_4e05e50: closed [V live] (sub_bc41420 -> 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 writes bgfx cmd byte 0x0E -> bgfx dispatcher -> createTexture 0xe8143c0; handle stored [texture_obj+0x00] at 0xC296E26 [V]).
- sub_4e05e50 fully decoded (entry 0x4E05E50; releases old texture at this+0x10/+0x18 via vtable[1] through [0xF99FFA0]; descriptor from this+0x58; sampler flags from this+0xE0; `0x4E05F77  call 0xBC41420`, call ends 0x4E05F7C = LIVE RESULT 5 ret [V live]).
- indirect caller of sub_4e05e50 = sub_12893d0, entry 0x12893D0, call site 0x1289490 (fall-through 0x1289496 = 15/15 live-capture ret values [V live]); [0xF99FFA0] = sub_eea6040 `jmp rax` (0xEEA6040 [V]); rcx = ClientTexture-class texture object (TexturePtr::mClientTexture pointee) [V live].
- static callers of sub_12893d0 enumerated with exact call sites [V]: sub_6622610 (0x6622662), sub_6632bf0 (0x6632C55), sub_1145c20 (0x1145D5A, 0x1145EE5), sub_66232b0 (xref-named, exact site not pinned).

What remains NOT statically provable (blocking fact):
- sub_4e05e50 (fn 0x4E05E50..0x4E06074) has 0 static xrefs; reached only via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` (trampoline).
- [0xF99FFA0] is a read-only .rdata PE data initializer holding 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 RVA 0xEEA6040 (the trampoline), NOT sub_4e05e50. `.text` store scan for [0xF99FFA0] = 0 hits; .rdata is read-only (section flags 0x40000040), so there is NO code writer and it is never rewritten (r37).
- sub_66232b0 (which calls sub_12893d0) has 0 static code xrefs; its only reference is the .rdata vtable pointer at 0xF2BDF40 (virtual dispatch target, [I] class not named). It is absent from both depth-4 callee trees of texgroup_load(0x5421c90) and texload(0x58A1310).
- Therefore the static link texgroup_load -> sub_66232b0 -> sub_12893d0 -> sub_4e05e50 -> createTexture is an INDIRECT virtual bind, resolved only at runtime (observed live [V live]); it cannot be closed by static analysis. Atlas stitchers (L8a/L8b) remain separate open items, not this unit.

================================================================================
6. TOOL REQUESTS
================================================================================

None — all data from rdis/xref.py and the two provided live capture logs (mc_root_4e05e50_callers.txt, l8b_texcreate_record.txt); no helper scripts written, no temporary files left behind.
