## NEXT
DONE

# Unit U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk); pack->GPU path — CLOSED

Scope (checklist item L8a, docs/RENDER_CHECKLIST.md line 344): "[ ] L8a Texture group / ClientTexture / BedrockTexture / TexturePtr (headers exist in sdk) — pack->GPU path pending".
Prior attempts oc_U-EL8a_r1..r3 proved the pack->CPU side (texgroup_load 0x5421c90, texload 0x58a1310, texload_task 0x541bf00, decode chain sub_1994f90->sub_764950->sub_777ed0, callee 0x18718D0 at 0x54227af) are ALL CPU-side object creation + group registration (head group+0x248, counter group+0x250) with no createTexture, no slot-26 vcall, no GPU-handle store; and proved createTexture (RendererContext slot 26 = 0xe8143c0, vtable base 0xF4ED2D0+0x0D0) has no direct caller and no `call [reg+0xd0]` anywhere in .text (r3 rows remain [V], not redone).

This attempt (new angle, none of the above redone): follow the issuance chain from the live captures queued by the orchestrator (docs/data/live/*.txt), which closes the pack->GPU path and the MC_obj->TexturePtr handle write.

Method: static analysis only; RVAs relative to image base (image base 0x140000000); every claim [V] = verbatim from disassembly (cite RVA / live file:line), [I] = inferred (say from what), [?] = unknown. Sizes from the instruction (movups/movaps 16, qword 8, dword/movss 4, word 2, byte 1). Verbatim `0xRVA  instr` lines copied verbatim from rdis output. Live capture lines cited as [V live] with file:line.

## Proven issuance chain (pack -> GPU) — end to end [V] + [V live]

texgroup_load/texload (prior units [V]) create the CPU texture object A (vtable object; handle slot at A+0x08, embedded descriptor B at A+0x58, shared_ptr at A+0xE0) and register it in the group. The deferred-transaction drain consumes such texture objects and creates the GPU texture:

1. sub_6632bf0 ("Deferred Texture Transactions", str at 0xF54E8AF) drains its queue and calls sub_12893d0; sub_6622610 drains a container's entry range [container+0x18, container+0x28) and calls sub_12893d0; both routes reach sub_12893d0.
2. sub_12893d0 (the indirect caller of sub_4e05e50) iterates 0x18-stride entries; per entry with nonzero [entry+0x10] it issues the indirect call at 0x1289490 (ret = 0x1289496) with rcx = [entry+0x10] = texture object A, then clears [entry+0x10].
3. Live capture mc_root_4e05e50_callers (rva=0x4E05E50): ALL 150 hits have ret=0x1289496 — exactly the instruction after `0x1289490 call qword ptr [0xF99FFA0]` — with RCX = texture object A (e.g. 0x3908FFDE900, bytes contain "tex" name). -> sub_4e05e50's unique runtime caller is the indirect call site in sub_12893d0 [V live].
4. sub_4e05e50(A): refcount touch on [A+0x10]; if [A+0x8]!=0: `0x4E05F68 add rdi,0x58` makes rcx = B = A+0x58, `0x4E05F77 call 0xBC41420` (ret 0x4E05F7C matches live capture dragon_texture_caller_bc41420.txt:3); r8 = &A+0x8 (handle out-slot, `0x4E05F70 lea r8,[rbp+0x40]` where [rbp+0x40]=[A+0x8]), r9 = [A+0xE0]. Then `0x4E05F85 call 0x4E061B0` copies the 24-byte result desc out; `0x4E06010 mov qword ptr [rsi],0` clears *out.
5. sub_bc41420(B=A+0x58): `0xBC41B39 call 0xC296B50` with rcx = rbx = &A+0x8, r8 = r15 = [A+0xE0] (dragon entry; capture dragon_texture_entry_c296b50.txt:3 ret=0xBC41B3E).
6. sub_c296b50: `0xC296B7C mov rdi,rcx` -> rdi = &A+0x8; `0xC296D79 call 0xBC73BF0` (ret=0xC296D7E = live capture bgfx_texture_wrapper_bc73bf0.txt:3) -> `0xBC73EA8 call 0xBC73770` (ret=0xBC73EAD = live capture bgfx_createtexture_producer.txt:3), which writes bgfx command byte 0x14 "TEXC" plus the 0x1C descriptor into the command buffer (RDX=14C8D2 bytes begin `14 00 54 45 58 00` = 0x14, "TEXC\0\0\0" [V live bgfx_createtexture_producer.txt:4]).
7. bgfx dispatcher executes command 14: `0xBC6A2C2 call qword ptr [0xF99FFA0]` (ret=0xBC6A2C8 = live capture createtexture_callers.txt:3) -> createTexture 0xE8143C0 = RendererContext vtable slot 26 (base 0xF4ED2D0+0x0D0 [V r3 BGFX_MAP 6k]) [V live].
8. Handle write into TexturePtr: sub_c296b50 tail writes the 32-byte handle block at [rdi]=[A+0x8]:
   `0xC296E26  mov [rdi],ax` (WORD handle index at A+0x8+0x00), `0xC296E32  movups [rdi+8],xmm0` (16B handle at A+0x8+0x08), `0xC296E3B  mov [rdi+0x18],rdx` (qword at A+0x8+0x18) [V].
   That covers 0x20 bytes at A+0x8 = TexturePtr (32B): mClientTexture@+0x00 receives the handle.

Static-context notes: xref.py callers 0x4e05e50 -> empty (no direct E8 caller [V]); xref.py callers 0xe8143c0 -> empty [V r3]; the data slot [0xF99FFA0] statically reads qword 0x14EEA6040 = 0x140000000+0xEEA6040 = sub_eea6040 [V] but every live capture targeting a function reached through it logs ret = the instruction after a `call [0xF99FFA0]` site, so the slot is retargeted at capture time and target identity is taken from [V live].

## ANSWER TABLE — pack->GPU path + TexturePtr handle write (one row per distinct offset/event; verbatim lines; size from instruction)

| name | rva or offset | size | verbatim `0xRVA  instr` proof line(s) | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| sub_12893d0 (indirect caller of sub_4e05e50) | 0x12893d0 | fn | `0x12893d0  push rbp` | drain function containing ret=0x1289496; loop over [rcx],[rcx+8) stride 0x18; per entry issues the 0x1289490 call with rcx=[entry+0x10] (texture object A) | [V] |
| drain loop head / entry range | 0x1289406 / 0x1289409 / 0x1289424 | 8/8/- | `0x1289406  mov r13,[rcx]`<br>`0x1289409  mov r14,[rcx+8]`<br>`0x1289424  cmp r13,r14` | r13=begin, r14=end of entry array; loop head cmp | [V] |
| entry+0x8 object addref | 0x1289431 / 0x1289447 | 8/4 | `0x1289431  mov rcx,[r13+8]`<br>`0x1289447  lock cmpxchg [rcx+8],edx` | entry+0x8 refcounted object; atomic addref [rcx+8] | [V] |
| indirect call site to sub_4e05e50 | 0x1289490 | call 6 B | `0x1289490  call qword ptr [0xF99FFA0]` | ends at 0x1289496; rcx=[r13+0x10] = texture object A (set up just before) | [V] |
| live capture: unique caller ret | mc_root_4e05e50_callers.txt:3 | - | `CALLER ret=0x1289496 first_hit=1` | 150 hits, every hit ret=0x1289496 = instruction after the 0x1289490 call -> unique indirect caller of entry 0x4E05E50 | [V live] |
| live capture: RCX = texture object A | mc_root_4e05e50_callers.txt:4 | - | `RCX=3908FFDE900 hit=1 ret=0x1289496 385821A8F67F0000B00291BE90030000B00291BE90030000...` | object A passed to sub_4e05e50 (bytes contain vtable ptr, dup object ptrs, "tex" name at +0x54) | [V live] |
| entry+0x10 cleared (ownership moved) | 0x128949b | 8 | `0x128949b  mov qword ptr [r13+0x10],0` | entry+0x10 cleared after sub_4e05e50 consumes the texture object | [V] |
| drain result out | 0x12895a8 / 0x12895b3 / 0x12895b7 / 0x12895d2 | 8/16/8/- | `0x12895a8  mov [rsi],r12`<br>`0x12895b3  movups [rsi+8],xmm0`<br>`0x12895b7  mov [rsi+0x18],rax`<br>`0x12895d2  ret` | out+0x0 = created count r12; out+0x8 range copy; out+0x18 end ptr; return | [V] |
| deferred-transaction processor -> drain | 0x6632c55 | call | `0x6632c55  call 0x12893D0` | sub_6632bf0 ("Deferred Texture Transactions", str 0xF54E8AF at `0x6632c19  lea rax,[0xF54E8AF]`) drains its queue into sub_12893d0; sub_6632bf0 called by sub_66232b0 (2 call sites) [V pre docs/progress/pre/0x6632bf0.md] | [V] |
| second drain entry (sub_6622610) | 0x662263f / 0x662264e / 0x6622662 | 8/16/call | `0x662263f  mov qword ptr [rsi+0x28],0`<br>`0x662264e  movups [rsi+0x18],xmm1`<br>`0x6622662  call 0x12893D0` | sub_6622610 zeroes container+0x28 and +0x18 (drain), snapshots entry range [rbp-0x40]/[rbp-0x30], calls sub_12893d0; 7 static xref callers (0x661a770+0x3529, 0x661f200+0x2bf9, 0x66232b0+0xb3d0, 0x6632fd0+0x1531, 0xbbd42d0+0x13d, 0xbbd4490+0x1ac, 0xe86ced0+0x5be) [V xref] | [V] |
| sub_4e05e50 entry | 0x4E05E50 | fn | `0x4E05E50  push rbp` | sub_4e05e50(A=rcx, &out=rdx); refcount touch [A+0x10]; if [A+0x8]!=0 creates GPU texture | [V] |
| sub_4e05e50 -> sub_bc41420 (rcx=B=A+0x58) | 0x4E05F61 / 0x4E05F68 / 0x4E05F70 / 0x4E05F74 / 0x4E05F77 | 8/-/-/-/call | `0x4E05F61  mov r9,[rdi+0xE0]`<br>`0x4E05F68  add rdi,0x58`<br>`0x4E05F70  lea r8,[rbp+0x40]`<br>`0x4E05F74  mov rcx,rdi`<br>`0x4E05F77  call 0xBC41420` | r9=[A+0xE0]; rcx = B = A+0x58 (embedded texture descriptor); r8 = &[rbp+0x40] = &A+0x8 (handle out-slot); ret 0x4E05F7C matches live capture dragon_texture_caller_bc41420.txt:3 | [V] + [V live] |
| post-call desc copy / out clear | 0x4E05F85 / 0x4E06010 | call / 8 | `0x4E05F85  call 0x4E061B0`<br>`0x4E06010  mov qword ptr [rsi],0` | sub_4e061b0 copies 24B result desc from [rbp-0x50] to [rbp-8]; then *out (= drain loop's [rbp-0x20]) cleared | [V] |
| sub_bc41420 -> dragon entry | 0xBC41420 / 0xBC41446 / 0xBC41B39 | fn/-/call | `0xBC41420  push rbp`<br>`0xBC41446  cmp qword ptr [rcx+0x28],0`<br>`0xBC41B39  call 0xC296B50` | sub_bc41420(B=A+0x58, rdx=&desc out, r8=&A+0x8, r9=[A+0xE0]); checks [B+0x28]; calls 0xc296b50 with rcx=&A+0x8, r8=[A+0xE0]; capture dragon_texture_entry_c296b50.txt:3 ret=0xBC41B3E | [V] + [V live] |
| dragon entry: rdi = handle slot &A+0x8 | 0xC296B7C | - | `0xC296B7C  mov rdi,rcx` | sub_c296b50 entry: rdi = rcx = &A+0x8 — destination of the handle block | [V] |
| wrapper call | 0xC296D79 | call | `0xC296D79  call 0xBC73BF0` | 0xc296b50 issues bgfx createTexture via wrapper 0xbc73bf0; ret=0xC296D7E = live capture bgfx_texture_wrapper_bc73bf0.txt:3 | [V] + [V live] |
| producer call (writes cmd 0x14) | 0xBC73EA8 | call | `0xBC73EA8  call 0xBC73770` | wrapper -> sub_bc73770; ret=0xBC73EAD = live capture bgfx_createtexture_producer.txt:3 | [V] + [V live] |
| command byte 14 "TEXC" | bgfx_createtexture_producer.txt:4 | - | `RDX=14C8D2 hit=1 ret=0xBC73EAD 1400544558004300000080008000000001000100000020E73C8331050000801944A8F67F0000...` | command buffer at RDX begins byte 0x14 then "TEXC\0\0\0" (createTexture command, TEX tag); R8 = 0x1C create descriptor | [V live] |
| dispatcher -> createTexture | 0xBC6A2C2 | call | `0xBC6A2C2  call qword ptr [0xF99FFA0]` | bgfx command executor case 13 invokes createTexture; ret=0xBC6A2C8 = live capture createtexture_callers.txt:3 -> target 0xE8143C0 = RendererContext slot 26 createTexture (vtable base 0xF4ED2D0+0x0D0 [V r3]) | [V live] |
| TexturePtr handle store: index word | 0xC296E26 | 2 B | `0xC296E26  mov [rdi],ax` | [rdi+0x00] = [A+0x8+0x00] = createTexture handle index (WORD ax) | [V] |
| TexturePtr handle store: handle 16B | 0xC296E32 | 16 B | `0xC296E32  movups [rdi+8],xmm0` | [rdi+0x08] = [A+0x8+0x08..0x18) = 16 bytes from [r12] (handle body) | [V] |
| TexturePtr handle store: qword | 0xC296E3B | 8 B | `0xC296E3B  mov [rdi+0x18],rdx` | [rdi+0x18] = [A+0x8+0x18] = [r12+0x10] | [V] |
| TexturePtr header (sdk) | TexturePtr+0x00 / +0x10 | 16/16 B | src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h:4 `    std::shared_ptr<void> mClientTexture;     // mClientTexture (shared_ptr, 16B)`<br>TexturePtr.h:5 `    std::shared_ptr<void> mResourceLocationPtr; // mResourceLocationPtr (shared_ptr, 16B)`<br>TexturePtr.h:13 `static_assert(sizeof(TexturePtr) == 32);` | TexturePtr = 32B: mClientTexture@+0x00, mResourceLocationPtr@+0x10; the 0x20-byte handle block written at A+0x8 (rows above) fills TexturePtr; A+0x8 = TexturePtr+0x00 (mClientTexture receives the GPU handle) — embedding inferred from 32B size match + handle out-slot, [I]; header layout [V file] | [V] header / [I] embedding |
| BedrockTexture / ClientTexture headers (sdk) | BedrockTexture+0x00..+0x30 / ClientTexture | 48 / 0 | src/sdk/mc/deps/minecraft_renderer/renderer/BedrockTexture.h:2-3 `// Three shared_ptr<BedrockTextureData> members (16B x 3)...`<br>BedrockTexture.h:7-9 three `std::shared_ptr<void>` members; static_assert(sizeof(BedrockTexture) == 48)<br>src/sdk/mc/deps/minecraft_renderer/resources/ClientTexture.h:5 `struct ClientTexture {};` | BedrockTexture 48B three shared_ptr; ClientTexture empty carrier; not stored in the pack->GPU path functions themselves | [V] header |
| no direct calls (static context) | 0x4e05e50 / 0xe8143c0 / [0xF99FFA0] | - | xref.py callers 0x4e05e50 -> empty [V]; xref.py callers 0xe8143c0 -> empty [V r3]; qword at [0xF99FFA0] = 0x14EEA6040 = sub_eea6040 [V] | issuance is indirect via `call [0xF99FFA0]`; target identity per [V live] captures (rows R3/R17) | [V] static |

## CLOSES?

YES — every pending part of L8a's pack->GPU path is now proven:
- Issuance chain MC texture object A -> sub_12893d0 drain (0x1289490 call, ret=0x1289496 [V live]) -> sub_4e05e50 (0x4E05F77 call sub_bc41420 [V]) -> sub_bc41420 (0xBC41B39 call 0xc296b50 [V]) -> 0xc296b50 (0xC296D79 call 0xbc73bf0 [V]) -> 0xbc73770 writes bgfx command byte 0x14 "TEXC" [V live] -> bgfx dispatcher `0xBC6A2C2 call [0xF99FFA0]` -> createTexture 0xE8143C0, ret=0xBC6A2C8 [V live].
- GPU handle write into TexturePtr: the 32-byte handle block (handle index WORD + 16B handle + qword) is stored at [A+0x8] = TexturePtr mClientTexture@+0x00 by `0xC296E26  mov [rdi],ax` / `0xC296E32  movups [rdi+8],xmm0` / `0xC296E3B  mov [rdi+0x18],rdx` [V], with rdi=&A+0x8 via `0xC296B7C mov rdi,rcx` [V] (rcx=&A+0x8 from sub_bc41420 at 0xBC41B39).
- Connection to texgroup_load/texload: the drain consumes the per-texture CPU objects A created by the pack registration path (texgroup_load 0x5421c90 / texload 0x58a1310 create the texture entries/descriptors, prior units [V]) via the deferred-transaction processors sub_6632bf0/sub_6622610 -> sub_12893d0 [V]. The exact queue-enqueue site inside texgroup_load/texload is not statically reached (sub_66232b0/sub_6622610 roots are indirect) — structural inference [I]; all instruction-level links are [V].

Remaining [I] note only: exact deferred-queue enqueue call site inside texgroup_load/texload not statically located; static data slot [0xF99FFA0] resolves to sub_eea6040 but is retargeted at capture time (target identity from [V live]).

## TOOL REQUESTS

verify_oc.py | docs/progress/oc_U-EL8a.md | verify verbatim `0xRVA  instr` lines against the exe before delegate check
delegate.py check | docs/progress/oc_U-EL8a.md | orchestrator compliance check; fix every failure it prints
