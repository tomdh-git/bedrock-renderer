## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only orchestrator outputs, cited as [V live] with file:line.

Tags: [V] saw in disassembly (RVA cited, verbatim `0xRVA  instr` quoted from a fresh rdis dis this session) / [V live] saw in an orchestrator live-capture reg dump (file:line cited) / [I] inferred from structure or BGFX_MAP.md / '-' = no instruction or string shows a meaning. Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes come from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1; direct call 5, indirect call qword ptr [mem] 8). No input data pasted as-is; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## 1. Already proven (cited from r1-r56; not re-decoded here; every verbatim line below re-matched against a fresh rdis dis this session)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] texture record table at this+0xBDE178 stride 0xB8 (BGFX_MAP.md slot table line 1524, slotscan 638 confirm base/stride); createTexture 0xe8143c0 = renderer-context vtable slot 26 ([rax+0xD0], BGFX_MAP.md line 403/1524); updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30 (call 0xe81455B, ret site 0xe814560 [V live]); record layout per BGFX_MAP.md 1812 (+0x00 ID3D12Resource*, +0x18 width, +0x20 height, +0x28 DXGI_FORMAT, +0x98 flags, +0x9C/+0xA0 width/height, +0xAE type, +0xAF requested format, +0xB0 actual format, +0xB1 numMips; guarded paged array guard byte this+0xC96190, page list this+0xC96178).
- createTexture issuance end-to-end below sub_4e05e50: [V dis] + [V live] (field map, Table 2/3 below); returned u16 handle stored at texture object+0x00; sdk TexturePtr/ClientTexture headers [V file read].

## 2. New work this session

Resolve the r37 pending part (what rax holds at sub_eea6040's `jmp rax`, i.e. the indirect target of the MC-side sub_4e05e50 entry), read the two captures that just arrived (docs/data/live/mc_root_4e05e50_callers.txt, docs/data/live/l8b_texcreate_record.txt), and attack the remaining static bind (texgroup_load -> sub_4e05e50) from new angles. Nothing redone.

### New angles tried this session (none closes the bind)

1. sub_4e060b0 fully decoded [0x4E060B0..0x4E0611D): it is the TextureTransaction deleting destructor (vtbl slot 0): `0x4E060BB lea rax,[0xF215838]` / `0x4E060C2 mov [rcx],rax` writes vptr = 0xF215838 during teardown; releases refcounted members at +0x18 and +0x10 via the trampoline; on dil&1 does `0x4E06107 mov edx,0xE8` / `0x4E0610F call 0xE935700` (operator delete of the 0xE8-byte transaction object). It is NOT the constructor: `rdis imm 0xF215838` -> 0 hits (no static construction site writes the vtable address) and `xref.py callers 0x4E060B0` -> EMPTY (called only via vtbl[0] through the trampoline, e.g. 0x12894b3 in sub_4e05e50 itself).
2. sub_661a400/sub_661a770 (deferred-texture resource owner; string "RenderDragon Deferred Textures" at .rdata 0xF5573D6): `xref.py str "Deferred Texture Transactions"` returns exactly 3 refs — 0x66244e7 and 0x66264e6 in BgfxFrameBuilder::endFrame 0x66232b0, and 0x6632c19 in the flush sub_6632bf0 (BGFX_MAP.md 6dv) — and sub_661a770 is referenced only from within sub_661a400 (0x661a400+0x2e6 area). No transaction construction/push site tied to texgroup_load/texload/texload_task.
3. livemem: considered and rejected — brief rule: last resort, needs a statically-known anchor; sub_6632bf0's this/vector base is not statically located, so no livemem read is applicable.

### Capture evidence read this session

- docs/data/live/mc_root_4e05e50_callers.txt (_status.txt line 2: hits=150 samples=32): line 3 `CALLER ret=0x1289496 first_hit=1`; every one of the 32 samples has CALLER ret=0x1289496 — sub_4e05e50 is entered exclusively through sub_12893d0's vptr[1] trampoline tail-call at `0x1289490 call qword ptr [0xF99FFA0]` (ret site `0x1289496 nop`) [V live]. RCX = the transaction object (e.g. 0x3908FFDE900 hit 1); its first qword `385821A8F67F0000` = runtime vptr 0x00007FF6A8215838 = module base 0x7FF6A72F4000 + vtable RVA 0xF215838 at runtime [V live bytes]; the dump carries texture names 'tex' / 'legs' / 'spear' and descriptor fields (width/height u16) [V live bytes]. R9 = descriptor-object pointers [V live bytes].
- docs/data/live/l8b_texcreate_record.txt (_status.txt line 4: hits=150 samples=24): `CALLER ret=0xE814560` matching `0xE814560 nop` after `0xE81455B call 0xE81BF30` [V live]; R8 dumps carry UTF-16 names 'Texture: 2815' (hit 1) and 'Texture: 2799' (hit 2) tying TextureD3D12::create to named textures [V live bytes].
- docs/data/live/createtexture_callers.txt (prior): all hits `CALLER ret=0xBC6A2C8` — createTexture is issued only from the bgfx command-byte-14 dispatcher at `0xBC6A2C2 call qword ptr [0xF99FFA0]`, not from MC texture code directly; R8 = 0x1C-byte create descriptor ("TEX" tag) [V live].

### Field map — L7e verified offsets (one row per distinct offset, all sites listed)

| offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| .rdata+0xF215840 | 8 | - | - | `xref.py ptr 0x4E05E50`: exactly one data pointer, .rdata RVA 0xF215840 = 0x4E05E50; vtable base 0xF215838, so vtbl[1] (+8) = sub_4e05e50 | [V] |
| vtable 0xF215838+0x000 | 8 | - | - | `rdis vt 0xF215838`: slot +0x000 = sub_4e060b0 size 0x6e (deleting destructor), slot +0x008 = sub_4e05e50 size 0x224 push rbp (run), slot +0x010 = non-code 0x0 — the job-object vtable carried by sub_12893d0's entries | [V] |
| xref.py callers 0x4E05E50 | 0 | - | - | `xref.py callers 0x4E05E50` -> EMPTY: sub_4e05e50 (0x4E05E50..0x4E06074 per vt size 0x224) has zero static callers; entered only indirectly via the trampoline | [V] |
| xref.py callers 0x4E060B0 | 0 | - | - | `xref.py callers 0x4E060B0` -> EMPTY: the destructor is reached only via vtbl[0] dispatch through the trampoline | [V] |
| rdis imm 0xF215838 | 0 | - | - | `rdis imm 0xF215838`: 0 hits — no code materializes the vtable address except sub_4e060b0's own teardown write | [V] |
| 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | CFG trampoline body: tail-calls rax (the real indirect target held in rax) | [V] |
| [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490 call qword ptr [0xF99FFA0]` / `0xBC6A2C2 call qword ptr [0xF99FFA0]` | trampoline indirect call; rdis resolves `[data_f99ffa0] = sub_eea6040` at every site; .rdata is read-only (no code writer; .text store scan 0 hits) | [V] |
| 0x1289486 | 8 | R: | `0x1289486 mov rax,[rcx]` | sub_12893d0 deferred-transaction runner: rax = entry+0x10 transaction object | [V] |
| 0x1289489 | 8 | R: | `0x1289489 mov rax,[rax+8]` | rax = transaction object vptr[1] = the real indirect target jumped to by the trampoline | [V] |
| 0x1289490 | 8 | R: | `0x1289490 call qword ptr [0xF99FFA0]` | sub_12893d0 tail-calls vptr[1] through the trampoline; ret site = 0x1289496 | [V] [V live] |
| 0x1289496 | 1 | - | `0x1289496 nop` | instruction right after the indirect call; = mc_root capture CALLER ret=0x1289496 in all 32 samples | [V] [V live] |
| 0x4E05E50 | - | E: | `0x4E05E50 push rbp` | sub_4e05e50 entry = TextureTransaction::run; RCX = transaction object; xref callers EMPTY (row above) | [V] |
| 0x4E05E71 | 8 | R: | `0x4E05E71 mov rax,[rcx+0x18]` | run() releases refcounted member at transaction+0x18 | [V] |
| 0x4E05E86 | 8 | R: | `0x4E05E86 call qword ptr [0xF99FFA0]` | release/destroy of member via trampoline | [V] |
| 0x4E05EA8 | 4 | R/W: | `0x4E05EA8 lock cmpxchg [rdx+8],r8d` | addref [rdx+8] where rdx=[rdi+0x10] | [V] |
| 0x4E05F61 | 8 | R: | `0x4E05F61 mov r9,[rdi+0xE0]` | R9 = [transaction+0xE0] = create descriptor pointer | [V] |
| 0x4E05F68 | - | - | `0x4E05F68 add rdi,0x58` | texture object = transaction object + 0x58, passed as RCX to sub_bc41420 | [V] |
| 0x4E05F77 | 5 | S: | `0x4E05F77 call 0xBC41420` | run() -> dragon-layer create sub_bc41420(rcx=texture object); ret site = 0x4E05F7C | [V] [V live] |
| 0x4E05F7C | 1 | - | `0x4E05F7C nop` | ret site after `call 0xBC41420`; = capture CALLER ret=0x4E05F7C | [V live] |
| 0x4E05F85 | 5 | S: | `0x4E05F85 call 0x4E061B0` | copies the sub_bc41420 result block | [V] |
| 0x4E06010 | 8 | W: | `0x4E06010 mov qword ptr [rsi],0` | stores 0 at [rsi] after create | [V] |
| 0xBC41B39 | 5 | S: | `0xBC41B39 call 0xC296B50` | sub_bc41420 -> dragon texture entry 0xc296b50; ret site = 0xBC41B3E | [V] [V live] |
| 0xBC41B3E | 4 | - | `0xBC41B3E movzx eax,byte ptr [rbp+0x188]` | ret site after `call 0xC296B50`; = capture CALLER ret=0xBC41B3E | [V live] |
| 0xC296D79 | 5 | S: | `0xC296D79 call 0xBC73BF0` | dragon entry 0xc296b50 -> thin bgfx createTexture wrapper sub_bc73bf0 | [V] [V live] |
| 0xC296D7E | 1 | - | `0xC296D7E nop` | ret site after `call 0xBC73BF0`; = capture CALLER ret=0xC296D7E | [V live] |
| 0xC296D7F | - | - | `0xC296D7F jmp 0xC296E26` | fallthrough from the wrapper call to the handle store | [V live] |
| 0xBC73EA8 | 5 | S: | `0xBC73EA8 call 0xBC73770` | wrapper sub_bc73bf0 -> command-byte-0x0E producer sub_bc73770 | [V] [V live] |
| 0xBC73EAD | 2 | R: | `0xBC73EAD movzx eax,word ptr [rsp+0x32]` | u16 handle returned by createTexture read back to the wrapper caller | [V] [V live] |
| 0xBC73AAA | 1 | W: | `0xBC73AAA mov byte ptr [rbp+0x2C],0xE` | sub_bc73770: byte 14 = createTexture staged into the command buffer | [V] |
| 0xBC73AAE | 4 | R: | `0xBC73AAE mov eax,[rbx+0xDC5818]` | command-buffer ring write index | [V] |
| 0xBC73AE2 | 4 | W: | `0xBC73AE2 mov [rbx+0xDC5818],ecx` | ring index bumped (by 2 after the handle) | [V] |
| 0xBC73AB4 | - | - | `0xBC73AB4 lea rcx,[rbx+rax]` / `0xBC73AB8 add rcx,0xDC5820` | command-buffer entry address (cmd byte at [entry], handle at [entry+1]) | [V] |
| 0xBC73B70 | 2 | R/W: | `0xBC73B70 movzx edi,word ptr [rbp+0x2E]` / `0xBC73B74 mov [rsi],di` | 16-bit handle returned to the createTexture API caller | [V] |
| 0xC296E1A | 5 | S: | `0xC296E1A call 0xBC74120` | ax = returned 16-bit bgfx texture handle | [V] |
| 0xC296E22 | 2 | - | `0xC296E22 mov ax,0xFFFF` | invalid-handle fallback (ax=0xFFFF) | [V] |
| 0xC296E26 | 2 | W: | `0xC296E26 mov [rdi],ax` | returned 16-bit handle stored at texture object +0x00; texture object = arg+0x58 | [V] [V live] |
| 0xC296E2D | 16 | R/W: | `0xC296E2D movups xmm0,[r12]` / `0xC296E32 movups [rdi+8],xmm0` | 16-byte create-descriptor block copied to texture object +0x08 | [V] [V live] |
| 0xC296E36 | 8 | R/W: | `0xC296E36 mov rdx,[r12+0x10]` / `0xC296E3B mov [rdi+0x18],rdx` | descriptor pointer stored at texture object +0x18 | [V] [V live] |
| 0xBC6A2AE | 8 | R: | `0xBC6A2AE mov rax,[rcx]` | bgfx dispatcher: rax = renderer-context vptr | [V] |
| 0xBC6A2B1 | 8 | R: | `0xBC6A2B1 mov rax,[rax+0xD0]` | rax = renderer-context vptr[slot 26] (0xD0/8 = 26) function pointer = createTexture | [V] |
| 0xBC6A2C2 | 8 | R: | `0xBC6A2C2 call qword ptr [0xF99FFA0]` | [vptr+0xD0] vcall through trampoline = createTexture issuance; rax = returned handle tested at next row | [V] [V live] |
| 0xBC6A2C8 | 4 | - | `0xBC6A2C8 test rax,rax` | ret site after the dispatcher tail-call; = createtexture_callers capture CALLER ret=0xBC6A2C8 | [V] [V live] |
| 0xE8143C0 | - | E: | `0xE8143C0 push rbp` | createTexture entry (D3D12 slot 26); xref.py callers 0xe8143c0 -> EMPTY, reached only via indirect [vptr+0xD0] | [V] |
| 0xE8143F3 | - | - | `0xE8143F3 lea r12,[rcx+0xBDE178]` | texture record table base = renderer ctx + 0xBDE178 | [V] |
| 0xE814427 | - | - | `0xE814427 imul r8,rbx,0xB8` | record stride 0xB8 per record index | [V] |
| 0xE81455B | 5 | S: | `0xE81455B call 0xE81BF30` | createTexture -> TextureD3D12::create (backend record fill) | [V] |
| 0xE814560 | 1 | - | `0xE814560 nop` | ret site after `call 0xE81BF30`; = l8b_texcreate_record capture CALLER ret=0xE814560 | [V live] |
| 0x54227AF | 5 | S: | `0x54227AF call 0x18718D0` | texgroup_load (0x5421c90) static chain: calls sub_18718D0 texture-cache lookup/release | [V] |
| 0x186DE55 | 5 | S: | `0x186DE55 call 0x71BC70` | sub_186DAC0 enqueues the Bedrock::Threading::Async<void> task; string 0xF820C35 "ResourceLoadManager:..." — pack->GPU boundary | [V] |
| TexturePtr.h | 32 | - | - | `class TexturePtr { std::shared_ptr<void> mClientTexture; std::shared_ptr<void> mResourceLocationPtr; }; static_assert(sizeof(TexturePtr) == 32);` — mClientTexture+0x00, mResourceLocationPtr+0x10, no vptr (plain shared_ptr carrier) | [V static] |
| ClientTexture.h | - | - | - | `struct ClientTexture {};` — empty marker struct | [V static] |

## 3. What this proves and what remains open

Resolved [V] (the r37 pending part): rax at the `0xEEA6040 jmp rax` trampoline is the transaction object's vptr[1]. `rdis vt 0xF215838` shows slot +0x008 = sub_4e05e50 statically [V], corroborated by the unique data pointer .rdata+0xF215840 = 0x4E05E50 [V] and by the mc_root capture: all 32 samples enter sub_4e05e50 via ret=0x1289496, and RCX's runtime vptr resolves to vtable RVA 0xF215838 [V live bytes]. So sub_4e05e50 = TextureTransaction::run, the deferred-transaction job body, invoked by sub_12893d0's tail-call from the sub_6632bf0 "Deferred Texture Transactions" flush (BGFX_MAP.md 6dv) triggered by BgfxFrameBuilder::endFrame 0x66232b0. The issuance chain below it is fully [V]/[V live]: sub_4e05e50 -> sub_bc41420 (`0x4E05F77 call 0xBC41420`) -> dragon entry 0xc296b50 (`0xBC41B39 call 0xC296B50`) -> wrapper 0xbc73bf0 (`0xC296D79 call 0xBC73BF0`) -> producer 0xbc73770 (`0xBC73EA8 call 0xBC73770`, cmd byte 0x0E at `0xBC73AAA mov byte ptr [rbp+0x2C],0xE`) -> bgfx dispatcher slot 26 (`0xBC6A2AE mov rax,[rcx]` / `0xBC6A2B1 mov rax,[rax+0xD0]` / `0xBC6A2C2 call qword ptr [0xF99FFA0]`) -> createTexture 0xe8143c0 -> TextureD3D12::create 0xe81bf30 (`0xE81455B call 0xE81BF30`, ret 0xE814560 [V live]); u16 handle read back (`0xBC73EAD movzx eax,word ptr [rsp+0x32]` [V live]) and stored at texture object+0x00 (`0xC296E26 mov [rdi],ax` [V live]), descriptor block at +0x08 and descriptor pointer at +0x18 [V live].

Still open (single blocking fact): no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50 exists. sub_4e05e50 has 0 static callers (xref EMPTY [V]) and sub_12893d0's complete static caller set {0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0} is outside texgroup_load's chain [V r44/r55]; texgroup_load's static chain ends at `0x54227AF call 0x18718D0` — sub_18718D0 is a 0xEFCA680 cache-object lookup (vptr[0] destructor dispatch only, never vptr[1]) -> sub_186DAC0 -> `0x186DE55 call 0x71BC70` ResourceLoadManager enqueue [V]. The async completion that constructs and pushes the TextureTransaction (vptr 0xF215838) into sub_6632bf0's Deferred Texture Transactions vectors is not statically locatable: sub_4e060b0 is the deleting destructor (not the constructor; its vptr write is teardown), `rdis imm 0xF215838` -> 0 hits, and `xref.py callers 0x4E060B0` -> EMPTY [V]. The bind is runtime-async, so static analysis is exhausted for this link. The `xref.py str` result confirms the deferred-transaction string is referenced only by endFrame 0x66232b0 and the flush sub_6632bf0 (3 refs total), with no construction/push site tied to the texgroup_load path.

Everything else in L7e IS [V]/[V live]-proven: Half 1 sampler flag decode + sampler cache (6ax); Half 2a D3D12 backend texture-management chain; MC-side createTexture issuance and handle trace into the texture object; sdk TexturePtr/ClientTexture headers. Atlas stitchers (L8a/L8b) remain separate open units (oc_U-EL8a/oc_U-EL8b), not this unit (MIRROR_SKIP).

## CLOSES?

NO — single blocking fact: no static path texgroup_load(0x5421c90) -> sub_4e05e50 exists and one provably cannot be built from static evidence (sub_4e05e50 has 0 static callers [V xref EMPTY]; entered only at runtime via sub_12893d0's vtbl[1] trampoline tail-call `0x1289490 call qword ptr [0xF99FFA0]`, ret site 0x1289496; mc_root capture 150 hits/32 samples all ret=0x1289496 [V live]). rax at that jmp IS resolved [V] (vtable 0xF215838 slot 1 = sub_4e05e50; unique pointer .rdata+0xF215840 -> 0x4E05E50 [V]) but that only names the runtime job body; the texgroup_load -> ResourceLoadManager enqueue chain ends statically at `0x54227AF call 0x18718D0` / `0x186DE55 call 0x71BC70` [V], and the TextureTransaction construction/push site into the deferred-transaction queue is not statically locatable (sub_4e060b0 = destructor, imm scan 0 hits, no ctor/push site [V]). New angles tried this session: full decode of sub_4e060b0 (destructor, not constructor), sub_661a400/sub_661a770 deferred-texture owner (string refs confined to endFrame + flush), livemem (rejected: no statically-known anchor per brief).

## Verification

- `python tools/sigs/verify_oc.py docs/progress/oc_U-EL7e.md` — mismatch=0, no-such-instr=0 required; every quoted `0xRVA  instr` line above re-matched verbatim against a fresh rdis dis of the 1.26.62.01 exe this session.
- `python tools/delegate.py check docs/progress/oc_U-EL7e.md` — must exit 0; only then is the line after `## NEXT` set to DONE.

## TOOL REQUESTS

None. No helper scripts written; no temporary files left behind in the repo.
