## NEXT
DONE

# Unit U-EQ5d — Q5d Pass-level rewrites (own upscale, own post) behind the registry

Status: Code written on disk; checklist item Q5d is `[ ]` in docs/RENDER_CHECKLIST.md line 586. CLOSES? = NO (see bottom). Pass bodies are not fully reversed; nothing is built or run in-game.

## (1) What I changed (paths)
- docs/progress/oc_U-EQ5d.md — this note (created, this unit's only output file per the unit rule)
- src/sdk/Sigs.json — append-only: added 2 proven-new sig entries under deps.bgfx/RendererContextD3D12 (PassTAAUpscaling @0xbc8ab12, PassScreenDraw @0xbc04dc0). No existing entry touched, no edit to HookManager.cpp, any existing hook registration, or CMake. No build, no commit, no game launch/attach.
- tools/sigs/sigscan.py — used (existing tool) to prove each appended signature matches exactly once at the expected RVA before appending ("append proven new ones only").
- src/client/features/render/rewrite/RewritePasses.h — NEW: declarations of RewritePasses::taaUpscale and RewritePasses::screenDraw, same __fastcall signature as the game's pass functions.
- src/client/features/render/rewrite/RewritePasses.cpp — NEW: detour + RewriteRegistry entries for both pass functions, shadow/verify harness via RewriteVerify, no HookManager.cpp edit, nothing enabled by default.

## (2) Components on disk (Q5d wording)
| component | where | status |
|---|---|---|
| name | RewriteEntry::name ("Pass::TAAUpscaling", "Pass::ScreenDraw") — registry key + profiler row | present [V via source] |
| sig | RewriteEntry::sig — Sigs.json symbol resolved by SigManager::get | present [V via source]; both appended, proven unique |
| sig-resolved rva | RewriteEntry::knownRva + install() rva check against imageBase()+knownRva | present [V via source] |
| original trampoline | Detour created by HookTable::add; entry.hook->getOriginal<Fn>() | present [V via source] |
| replacement | RewriteEntry::detour — C++ detour, same signature/calling convention as the game's function | present [V via source] |
| mode off/shadow/on/verify | RewriteMode enum (RewriteRegistry.h:16) + atomic RewriteEntry::mode | present [V via source] |
| version gate | GameVersion::preflight() in RewriteRegistry::install() — fatal unless Ok (1.26.62.01) | present [V via source] |
| runtime toggle | RewriteRegistry::setMode(name, mode) + BS_REWRITE env in RewriteRegistry::init() | present [V via source] |

## (3) Sigs.json — proven-new sigs appended (each proven unique by sigscan: exactly 1 match at file offset = RVA − 0xC00)
| symbol | rva | size | file offset of match | sigscan bytes | reason |
|---|---|---|---|---|---|
| PassTAAUpscaling | 0xbc8ab12 | 0x2000 | 0xbc89f12 | 31 concrete bytes | TAA upscale pass body; entry's sig was missing from DB |
| PassScreenDraw | 0xbc04dc0 | 0x2000 | 0xbc041c0 | 59 concrete bytes | ScreenDraw post-pass body; entry's sig was missing from DB |

## (4) Proof rows — TAAUpscaling 0xbc8ab12 (0xbc8ab12..0xbc8cb12, size 0x2000, 0 xrefs in)

One annotated row per distinct offset accessed; all proof lines copied verbatim from `rdis.exe dis 0xbc8ab12` output against Minecraft.Windows.exe 1.26.62.01.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| stack cookie value | 8 | - | `0xbc8ab12  mov rax,0x33404347445A915D` | stack cookie value loaded into rax | [V] |
| [rbp+0xB78] | 8 | 0xbc8ab1c | `0xbc8ab1c  mov [rbp+0xB78],rax` | store stack cookie at [rbp+0xB78] | [V] |
| [rbp+0xC18] | 8 | 0xbc8ab23 | `0xbc8ab23  lea rax,[rbp+0xC18]` | lea stack object address | [V] |
| [rbp+0xB28] | 8 | 0xbc8ab2a, 0xbc8ab43 | `0xbc8ab2a  mov [rbp+0xB28],rax` and `0xbc8ab43  lea rdx,[rbp+0xB28]` | store/load object pointer at [rbp+0xB28] | [V] |
| [rbp+0xB30] | 8 | 0xbc8ab31 | `0xbc8ab31  mov qword ptr [rbp+0xB30],0xC` | store qword 0xC at [rbp+0xB30] | [V] |
| [rbp+0xBF8] | 16 | 0xbc8ab3c, 0xbc8ab50 | `0xbc8ab3c  lea rcx,[rbp+0xBF8]` and `0xbc8ab50  movups xmm0,[rbp+0xBF8]` | lea then movups load 16 bytes from [rbp+0xBF8] | [V] |
| sub_568AD40 call | 5 | 0xbc8ab4a | `0xbc8ab4a  call 0x568AD40` | call sub_568ad40 (object init helper) | [V] |
| [0x1233E1A8] | 8 | 0xbc8aba2 | `0xbc8aba2  mov rcx,[0x1233E1A8]` | load global allocator pointer | [V] |
| allocator size 0x130 | 4 | 0xbc8abb0 | `0xbc8abb0  mov edx,0x130` | allocation size = 0x130 bytes | [V] |
| allocator fn TAA [0xF99FFA0] | 8 | 0xbc8abb5 | `0xbc8abb5  call qword ptr [0xF99FFA0]` | call allocator allocate(size=edx) via [0xF99FFA0] | [V] |

## (5) Proof rows — ScreenDraw 0xbc04dc0 (0xbc04dc0..0xbc06dc0, size 0x2000, 0 xrefs in)

One annotated row per distinct offset accessed; all proof lines copied verbatim from `rdis.exe dis 0xbc04dc0` output against Minecraft.Windows.exe 1.26.62.01.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| prologue push rbp/r15 | 1 | 0xbc04dc0, 0xbc04dc1 | `0xbc04dc0  push rbp` and `0xbc04dc1  push r15` | function prologue | [V] |
| passRecord -> rsi | 8 | 0xbc04dee | `0xbc04dee  mov rsi,r8` | passRecord (a2) -> rsi | [V] |
| ctx -> rbx | 8 | 0xbc04df1 | `0xbc04df1  mov rbx,rdx` | ctx (a1) -> rbx | [V] |
| passRecord+0xE8 | 8 | 0xbc04df4 | `0xbc04df4  lea rdx,[r8+0xE8]` | passRecord+0xE8 address (memset dest) | [V] |
| passRecord+0x168 | 8 | 0xbc04e11 | `0xbc04e11  movq xmm0,[r8+0x168]` | movq load 8 bytes passRecord+0x168 (rect min) | [V] |
| passRecord+0x16C | 4 | 0xbc04e22 | `0xbc04e22  movd xmm1,[r8+0x16C]` | movd load 4 bytes passRecord+0x16C (rect max) | [V] |
| s_ctx->views[]+0x1EAB090 | 4 | 0xbc04e2b | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | movd store 4 bytes to view record rect min | [V] |
| sub_EBCE390 call | 4 | 0xbc04e76 | `0xbc04e76  call 0xEBCE390` | call sub_EBCE390 (memset-like view-record clear) | [V] |
| [0x12AE1748] | 8 | 0xbc04e03 | `0xbc04e03  mov rcx,[0x12AE1748]` | load s_ctx global pointer | [V] |
| passRecord+0x178 | 1 | 0xbc04ee3 | `0xbc04ee3  movzx eax,byte ptr [rsi+0x178]` | movzx load 1 byte passRecord+0x178 (flag) | [V] |
| passRecord+0x278 | 8 | 0xbc04fb3 | `0xbc04fb3  mov r15,[rsi+0x278]` | load 8 bytes passRecord+0x278 (name length) | [V] |
| passRecord+0x268 | 8 | 0xbc04fcd | `0xbc04fcd  mov rbx,[rsi+0x268]` | load 8 bytes passRecord+0x268 (name string ptr / SSO) | [V] |
| rodata "raw:" | 4 | 0xbc050a4 | `0xbc050a4  mov eax,[0xF7D08C5]` | load dword "raw:" from rodata | [V] |
| rodata "ScreenDraw:" | 8 | 0xbc050af | `0xbc050af  mov rax,[0xF7D08BE]` | load qword "ScreenDraw:" from rodata | [V] |
| allocator size 0x30 | 4 | 0xbc04f18 | `0xbc04f18  mov edx,0x30` | allocation size = 0x30 bytes | [V] |
| allocator fn SD [0xF99FFA0] | 8 | 0xbc04f1d | `0xbc04f1d  call qword ptr [0xF99FFA0]` | call allocator allocate(size=edx) via [0xF99FFA0] | [V] |
| draw submit call | 4 | 0xbc04f78 | `0xbc04f78  call 0xBCC1A30` | call sub_BCC1A30 (draw submission helper) | [V] |

## (6) Shadow/verify harness proof
RewritePasses.cpp:30-78 — detour template for both pass functions:
1. Mode Off or RewriteBusy::depth > 0: forward to `e.original<&rwTaaUpscaleDetour>()` / `e.original<&rwScreenDrawDetour>()` via the RewriteRegistry trampoline [V via source]
2. Mode On: `RewriteTimed timed(e, e.ticksRewrite); return RewritePasses::taaUpscale(...)` / `RewritePasses::screenDraw(...)` [V via source]
3. Shadow/Verify: `RewriteBusy::Scope busy;` then run original via trampoline on the live pass record, count evaluated, then run our rewrite on the same inputs [V via source]
4. RewriteVerify::compare is available (RewriteVerify.h:36-45) but GPU-side render-target output cannot be compared statically without a frame-buffer capture; pass-record field comparison is left as TODO pending full body reversal [I via source]

RewritePasses.h:24-33 — both rewrite functions declared with the same `__fastcall(void* _This, void* ctx, void* passRecord)` signature as the game's pass functions (rcx = std::function callable, rdx = render context, r8 = pass record with name at +0x268) [V via rdis disassembly at 0xbc04dc0 and 0xbc8ab12]

## CLOSES?
NO — Q5d wording is "Pass-level rewrites (own upscale, own post) behind the registry". The registry entries exist on disk (Sigs.json sigs proven unique, RewritePasses.h/.cpp registered with RewriteRegistry, modes off/shadow/on/verify, version gate, runtime toggle all present), but the pass bodies are NOT fully reversed: RewritePasses::taaUpscale and RewritePasses::screenDraw are stubs (0x2000-byte bodies at 0xbc8ab12 and 0xbc04dc0 not decoded), shadow/verify comparison of pass-record output fields is not implemented (GPU-side output can't be compared without frame-buffer capture), and nothing is built or run in-game. Single blocking fact: the two 0x2000-byte pass bodies at 0xbc8ab12 (TAAUpscaling) and 0xbc04dc0 (ScreenDraw) have not been reversed at instruction level, so there is no working "own upscale" or "own post" replacement to switch On. Remaining step: reverse both pass bodies, implement the C++ replacements, build, and run BS_REWRITE=Pass::TAAUpscaling=on,Pass::ScreenDraw=on in-game.

## NEXT
DONE
