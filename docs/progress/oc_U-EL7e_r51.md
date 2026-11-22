## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live captures are orchestrator-produced read-only logs cited as [V live].

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted), [V live] seen in an orchestrator live-capture log (file + line cited), [I] inferred from structure/BGFX_MAP docs, [?] unknown / not located.
Row rule: one annotated row per distinct offset, all its sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after address, copied from rdis) | meaning only if an instruction/string shows it else '-' | tag. Sizes from instruction (movups 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets. No raw instruction dumps outside tables.

## Already proven (do NOT redo — cited from r1/r3/r48 and the live captures)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries static_asserts.
- Half 2a — D3D12 backend texture-management chain: [V] Tables 1-8 of oc_U-EL7e_r1.md: record table this+0xBDE178 stride 0xB8; createTexture slot 26 = 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750. xref.py callers 0xe8143c0 = EMPTY (r2, not redone): only indirect [vptr+0xD0] dispatch.
- Texture record fields (BGFX_MAP 6z, live-verified): +0x00 qword, +0x08 u32 state/type, +0x18 width u32, +0x20 height u32, +0x24 flags, +0x28 DXGI_FORMAT, +0x2c u32, +0x98 flags, +0x9C width, +0xA0 height, +0xAF requested format, +0xB0 actual format byte, +0xB1 numMips. Guard byte this+0xC96190; page list this+0xC96178.

## What earlier attempts tried that failed (do not repeat)

- xref.py callers 0xe8143c0: empty, only indirect [vptr+0xD0] thunks (r2, r3).
- texload 0x58a1310 / texload_task 0x541bf00: xref.py callers EMPTY for both; texgroup_load 0x5421c90 does not call them; its cache-bound call goes to 0x18718D0.
- Backend->cache adjacency (0xe82e00/0xe84070/0xe85290/0xe86630): font-init roots only, not createTexture (r3).
- [0xF99FFA0] as a writable function pointer: read-only .rdata initializer = trampoline sub_eea6040 (`jmp rax`); no writer store found (r37). Static work on that link exhausted.

## New work this session (new angles — createTexture issuance end to end)

- Angle 1: pointer scan for the [0xF99FFA0] target resolved r37's open question — xref.py ptr 0x4E05E50 finds EXACTLY ONE data pointer: .rdata RVA 0xF215840 holds 0x4E05E50; vtable base 0xF215838, so vtable[1] (+8) = sub_4e05e50 statically [V]. sub_4e060b0 writes vptr 0xF215838 (`0x4E060BB lea rax,[0xF215838]` / `0x4E060C2 mov [rcx],rax`) but has 0 static xrefs in [?] — transaction constructor/pusher not statically located.
- Angle 2: sub_12893d0 fully decoded [V]: it is the deferred-transaction runner — RCX = list object {+0x00 begin, +0x08 end} of 0x18-byte entries {+0 object, +8 refcount, +0x10 transaction object}; for each entry it loads [entry+0x10], then [vtable+8], and invokes it via `0x1289490 call qword ptr [0xF99FFA0]` (ret=0x1289496, live capture mc_root_4e05e50_callers.txt first CALLER ret=0x1289496). That vtable[1] IS sub_4e05e50 (the .rdata pointer above). So sub_4e05e50 = TextureTransaction::run().
- Angle 3: sub_4e05e50 fully decoded [V]: RCX=transaction object; releases refcounted members at +0x18/+0x10; if [+0x8] != 0 calls sub_bc41420(rcx=a0+0x58 texture object, rdx=&out local, r8=[a0+8], r9=[a0+0xE0] desc pointer) at `0x4E05F77 call 0xBC41420` (ret=0x4E05F7C, live capture), copies the result block via sub_4e061b0 (`0x4E05F85 call 0x4E061B0`), frees temporaries via sub_e935700, stores `0x4E06010 mov qword ptr [rsi],0`, returns.
- Angle 4: endFrame flush — BGFX_MAP 6dv: sub_6632bf0 ("Deferred Texture Transactions", strings at 0x6632C19/0x6632C42) holds two std::vector<Transaction*> ({begin,end,cap} at +0x00/+0x18), moves both out and passes to sub_12893d0; each transaction's vtbl[1] = run() is then invoked, vtbl[0] deletes. Verified: `0x6632C55 call 0x12893D0` and `0x6632D1E call 0x12893D0` inside sub_6632bf0 (preflight 0x6632bf0.md). endFrame 0x66232b0 references the "Deferred Texture Transactions" string (0xF54E8AF) at `0x66244E7 lea rax,[0xF54E8AF]` and `0x66264E6 lea rax,[0xF54E8AF]` [V], and calls the flush per BGFX_MAP 6dv [I].
- Angle 5: pack->GPU entry — xref.py callers 0x18718D0 lists 0x5421C90 (+0x190F) = texgroup_load references sub_18718D0 [V]. sub_18718D0 fully decoded [V]: per entry it processes [vptr+8] dispatch sites (`0x1871948 mov rax,[rax+8]` / `0x1871979 mov rax,[rax+8]` / `call qword ptr [0xF99FFA0]`) and calls sub_186DAC0 which builds a `Bedrock::Threading::Async<void>` task (string 0xF820C35 "ResourceLoadManager:...") and enqueues it via `0x186DE55 call 0x71BC70` [V] — ResourceLoadManager enqueue, the pack->GPU boundary (r2, not redone).
- Angle 6 (failed): static construction/push site of the TextureTransaction into the deferred texture vector — sub_4e060b0 (vptr 0xF215838 writer) has 0 static xrefs in; sub_661a770 (deferred-texture resource owner, string "RenderDragon Deferred Textures" 0xF5573D6 at 0x661A770+0x661C51E) is referenced only from 0x661A400+0x2E6, not tied to texgroup_load/texload/texload_task. Not located — see CLOSES? below.

## Answer table — command byte 0x0E producer (who writes 0x0E into the bgfx command buffer)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| cmd-byte-0x0E producer entry | 0xBC73770 | - | E: `0xBC73770  push rbp` | sub_bc73770 entry; command byte 0x0E producer (r4 [V live]) | - | [V live] |
| wrapper -> producer call | - | - | S: `0xBC73EA8  call 0xBC73770` | thin bgfx createTexture wrapper calls the producer | - | [V] |
| producer handle readback | 0xBC73EAD | 2 | R: `0xBC73EAD  movzx eax,word ptr [rsp+0x32]` | u16 handle returned by createTexture read back after the call | - | [V live] |
| live capture: producer caller | ret=0xBC73EAD | - | - | bgfx_createtexture_producer.txt: all hits ret=0xBC73EAD, i.e. the call at 0xBC73EA8 | - | [V live] |

## Answer table — bgfx dispatcher createTexture case ([vptr+0xD0] vcall, slot 26)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| dispatch case vtable load | 0xBC6A2AE | 8 | R: `0xBC6A2AE  mov rax,[rcx]` | load vtable pointer from context object | - | [V] |
| dispatch case slot-26 load | 0xBC6A2B1 | 8 | R: `0xBC6A2B1  mov rax,[rax+0xD0]` | load slot 26 (0xD0/8=26) function pointer from vtable | - | [V] |
| dispatch indirect call | 0xBC6A2C2 | - | S: `0xBC6A2C2  call qword ptr [0xF99FFA0]` | [vptr+0xD0] vcall through trampoline sub_eea6040 | createTexture | [V] |
| createTexture return site | 0xBC6A2C8 | - | - | `0xBC6A2C8  test rax,rax` — tests createTexture return handle | - | [V live] |
| live capture: createTexture caller | ret=0xBC6A2C8 | - | - | createtexture_callers.txt: all hits ret=0xBC6A2C8, RCX=renderer ctx, R8=0x1C-byte desc with "TEX" tag | - | [V live] |
| createTexture target | 0xE8143C0 | - | - | D3D12 slot 26 createTexture; xref.py callers = EMPTY, only [vptr+0xD0] | - | [V] |
| indirect-call trampoline | 0xEEA6040 | - | E: `0xEEA6040  jmp rax` | trampoline; rax holds the runtime target | - | [V] |

## Answer table — TextureTransaction vtable[1] = sub_4e05e50 (resolves r37: what rax holds at the jmp)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| vtable[1] data pointer | .rdata+0xF215840 | 8 | R: - | xref.py ptr 0x4E05E50: exactly one pointer, .rdata RVA 0xF215840 = 0x4E05E50; vtable base 0xF215838 | vtbl[1] of TextureTransaction = sub_4e05e50 | [V] |
| vptr write | 0x4E060C2 | 8 | W: `0x4E060C2  mov [rcx],rax` | sub_4e060b0 writes vptr = 0xF215838 into transaction object +0x00 (preceded by `0x4E060BB lea rax,[0xF215838]`) | transaction object ctor/dtor | [V] |
| sub_4e060b0 static xrefs in | 0 | - | - | xref.py callers 0x4E060B0 = EMPTY — transaction constructor/pusher not statically located | - | [?] |

## Answer table — sub_12893d0 deferred-transaction runner (MC-side issuer of sub_4e05e50)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| runner entry | 0x12893D0 | - | E: `0x12893D0  push rbp` | sub_12893d0 entry; RCX=list {+0 begin,+8 end} of 0x18-byte entries | - | [V] |
| entry vcall object load | 0x1289486 | 8 | R: `0x1289486  mov rax,[rcx]` | rax = [entry+0x10] transaction object | - | [V] |
| vtable slot-1 load | 0x1289489 | 8 | R: `0x1289489  mov rax,[rax+8]` | rax = vtable[1] of the transaction object | - | [V] |
| transaction run vcall | 0x1289490 | - | S: `0x1289490  call qword ptr [0xF99FFA0]` | invokes vtable[1] (= sub_4e05e50 at runtime); ret=0x1289496 | TextureTransaction::run | [V] |
| run return site | 0x1289496 | - | - | `0x1289496  nop` after the call | - | [V live] |
| runner call from flush | 0x6632C55 / 0x6632D1E | - | S: `0x6632C55  call 0x12893D0` / `0x6632D1E  call 0x12893D0` | sub_6632bf0 "Deferred Texture Transactions" flush passes both vectors to the runner | - | [V] |

## Answer table — sub_4e05e50 = TextureTransaction::run (MC-side createTexture issuer, takes TexturePtr*-shaped transaction)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| run() entry | 0x4E05E50 | - | E: `0x4E05E50  push rbp` | sub_4e05e50 entry; RCX=transaction object, RDX=out ptr | - | [V] |
| release member +0x18 | 0x4E05E71 | 8 | R: `0x4E05E71  mov rax,[rcx+0x18]` | transaction +0x18 refcounted object | - | [V] |
| release member dtor call | 0x4E05E86 | - | S: `0x4E05E86  call qword ptr [0xF99FFA0]` | release/destroy via trampoline | - | [V] |
| addref member +0x10 | 0x4E05EA8 | 4 | R/W: `0x4E05EA8  lock cmpxchg [rdx+8],r8d` | addref [rdx+8] where rdx=[rdi+0x10] | - | [V] |
| texture object arg setup | 0x4E05F68 | - | - | `0x4E05F68  add rdi,0x58` → RCX = transaction+0x58 = texture object passed to sub_bc41420 | - | [V] |
| desc pointer arg | 0x4E05F61 | 8 | R: `0x4E05F61  mov r9,[rdi+0xE0]` | R9 = [transaction+0xE0] = create descriptor pointer | - | [V] |
| sub_bc41420 call | 0x4E05F77 | - | S: `0x4E05F77  call 0xBC41420` | sub_bc41420(rcx=texture obj, rdx=&out, r8=[transaction+8], r9=desc ptr); ret=0x4E05F7C | - | [V] |
| result block copy | 0x4E05F85 | - | S: `0x4E05F85  call 0x4E061B0` | copies sub_bc41420 result block | - | [V] |
| out null | 0x4E06010 | 8 | W: `0x4E06010  mov qword ptr [rsi],0` | stores 0 at [rsi] after create | - | [V] |
| live capture: run caller | ret=0x4E05F7C | - | - | dragon_texture_caller_bc41420.txt / mc_root_4e05e50_callers.txt: sub_4e05e50 entered from sub_12893d0+0x120 | - | [V live] |

## Answer table — handle trace into the texture object (TexturePtr/ClientTexture handle write)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| dragon entry → wrapper call | - | - | S: `0xC296D79  call 0xBC73BF0` | sub_c296b50 (texture-object init) calls thin wrapper sub_bc73bf0 | - | [V] |
| entry fallthrough to store | 0xC296D7F | - | - | `0xC296D7F  jmp 0xC296E26` after `0xC296D79 call 0xBC73BF0`; ret=0xC296D7E | - | [V live] |
| handle store at texture_obj+0x00 | 0xC296E26 | 2 | W: `0xC296E26  mov [rdi],ax` | u16 bgfx handle stored at texture object +0x00 (rdi = RCX texture obj from sub_c296b50) | - | [V live] |
| desc block copy | 0xC296E32 | 16 | W: `0xC296E32  movups [rdi+8],xmm0` | 16-byte descriptor block copied to texture object +0x08 | - | [V live] |
| desc pointer field | 0xC296E3B | 8 | W: `0xC296E3B  mov [rdi+0x18],rdx` | descriptor pointer stored at texture object +0x18 | - | [V live] |
| wrapper → producer call | 0xBC73EA8 | - | S: `0xBC73EA8  call 0xBC73770` | wrapper calls cmd-byte-0x0E producer | - | [V] |
| handle readback | 0xBC73EAD | 2 | R: `0xBC73EAD  movzx eax,word ptr [rsp+0x32]` | u16 handle read back from createTexture | - | [V live] |
| sub_bc41420 → dragon entry | 0xBC41B39 | - | S: `0xBC41B39  call 0xC296B50` | sub_bc41420 calls dragon texture entry; ret=0xBC41B3E | - | [V] |
| sub_4e05e50 → sub_bc41420 | 0x4E05F77 | - | S: `0x4E05F77  call 0xBC41420` | TextureTransaction::run calls sub_bc41420 | - | [V] |

## Answer table — TexturePtr / ClientTexture (sdk headers)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| TexturePtr class | src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h | 32 | - | `class TexturePtr { std::shared_ptr<void> mClientTexture; std::shared_ptr<void> mResourceLocationPtr; }; static_assert(sizeof(TexturePtr) == 32);` | 32-byte handle, two shared_ptrs (16B each) | [V static] |
| ClientTexture class | src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h | - | - | `struct ClientTexture {};` | empty marker struct | [V static] |

## Answer table — pack->GPU entry (texgroup_load side, not redone)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| texgroup_load references sub_18718D0 | 0x5421C90 (+0x190F) | - | - | xref.py callers 0x18718D0 lists 0x5421C90 offset 0x190F | texgroup_load -> sub_18718D0 | [V] |
| ResourceLoadManager enqueue | 0x186DE55 | - | S: `0x186DE55  call 0x71BC70` | sub_186DAC0 enqueues Async<void> task; string 0xF820C35 "ResourceLoadManager:..." | pack->GPU boundary (r2) | [V] |
| endFrame deferred flush refs | 0x66244E7 / 0x66264E6 | - | R: `0x66244E7  lea rax,[0xF54E8AF]` / `0x66264E6  lea rax,[0xF54E8AF]` | "Deferred Texture Transactions" string refs in BgfxFrameBuilder::endFrame 0x66232b0 (BGFX_MAP 6dv) | flush trigger | [V] |

## CLOSES?

NO — createTexture issuance and handle trace are proven [V]/[V live]: sub_4e05e50 (TextureTransaction::run, vtable 0xF215838 vtbl[1] = 0x4E05E50 at .rdata+0xF215840 [V ptr scan]) is invoked by sub_12893d0 (`0x1289490 call qword ptr [0xF99FFA0]`, ret=0x1289496 [V live]) from the sub_6632bf0 "Deferred Texture Transactions" flush (`0x6632C55`/`0x6632D1E call 0x12893D0` [V]) triggered by BgfxFrameBuilder::endFrame 0x66232b0 (BGFX_MAP 6dv [I]); sub_4e05e50 calls sub_bc41420(`0x4E05F77 call 0xBC41420` [V]) → sub_c296b50(`0xBC41B39 call 0xC296B50` [V]) → wrapper(`0xC296D79 call 0xBC73BF0` [V]) → producer(`0xBC73EA8 call 0xBC73770` [V], cmd byte 0x0E) → bgfx dispatcher(`0xBC6A2AE mov rax,[rcx]` / `0xBC6A2B1 mov rax,[rax+0xD0]` / `0xBC6A2C2 call qword ptr [0xF99FFA0]` [V], ret=0xBC6A2C8 [V live]) → createTexture 0xe8143c0 [V]; u16 handle read back `0xBC73EAD movzx eax,word ptr [rsp+0x32]` [V live] and stored at texture object +0x00 `0xC296E26 mov [rdi],ax` [V live], with desc block `0xC296E32 movups [rdi+8],xmm0` and desc ptr `0xC296E3B mov [rdi+0x18],rdx` [V live]. texgroup_load -> sub_18718D0 -> sub_186DAC0 -> ResourceLoadManager enqueue 0x71BC70 [V] is the pack->GPU boundary. Single blocking fact (unchanged): the static construction/push of the TextureTransaction (vptr 0xF215838) into the Deferred Transactions texture vector from the texgroup_load -> ResourceLoadManager async-completion path is not located — sub_4e060b0 (vptr 0xF215838 writer) has 0 static xrefs in; sub_661a770 (deferred-texture resource owner, string 0xF5573D6) is referenced only from 0x661A400+0x2E6, not tied to texgroup_load/texload/texload_task. Static work on this link exhausted; requires the transaction push site (or a live capture at sub_4e060b0 entry / the deferred vector push). Atlas stitchers remain L8a/L8b (oc_U-EL8a/oc_U-EL8b), not this unit.

## TOOL REQUESTS

- verify_oc.py + delegate.py checks required before CLOSES? is final. No new helper scripts written, no temporary files left behind in the repo.
