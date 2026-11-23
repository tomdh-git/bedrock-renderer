## NEXT
DONE

# Unit U-EQ5d — Q5d Pass-level rewrites (own upscale, own post) behind the registry

Output file: docs/progress/oc_U-EQ5d.md (this unit's only output file).
Checklist item Q5d: docs/RENDER_CHECKLIST.md:586 — currently `[ ]` (REVIEW: registry entries + stubs exist, 30 [V]; TAAUpscaling body 0xbc8ab12 and ScreenDraw body 0xbc04dc0 not reversed, no working replacement, not ticked).

Scope respected: only docs/ and NEW files under src/sdk/ and src/client/features/render/ may be touched. No HookManager.cpp, no existing hook registration, no CMake, no existing Sigs.json entries modified (append-only proven new sigs), no build, no commit, no game launch/attach. Deferred-testing decision 2026-11-22: build + in-game run are NOT a CLOSES? NO reason; only missing REVERSING (an RVA/offset/meaning/[V] proof still unknown) forces NO.

## (1) What exists on disk (registry half — present)

| component | path | status |
|---|---|---|
| Pass target declarations | src/client/features/render/rewrite/RewritePasses.h | NEW, present — RewritePasses::taaUpscale and RewritePasses::screenDraw declared, same `__fastcall(void* _This, void* ctx, void* passRecord)` signature as the game's pass functions |
| Detours + registry entries | src/client/features/render/rewrite/RewritePasses.cpp | NEW, present — detours rwTaaUpscaleDetour / rwScreenDrawDetour registered with RewriteRegistry (RewriteEntry + RewriteReg statics), modes off/shadow/on/verify, version gate, runtime toggle via BS_REWRITE, nothing enabled by default |
| Sig: PassTAAUpscaling | src/sdk/Sigs.json line 161 | appended, proven unique: sigscan 31 bytes, exactly 1 match at file offset 0xbc89f12 (RVA 0xbc8ab12), no existing entry touched |
| Sig: PassScreenDraw | src/sdk/Sigs.json line 162 | appended, proven unique: sigscan 59 bytes, exactly 1 match at file offset 0xbc041c0 (RVA 0xbc04dc0), no existing entry touched |
| Verify harness | src/client/features/render/rewrite/RewriteVerify.h/.cpp | present — RewriteVerify::compare available; pass-record field comparison left as TODO pending full body reversal (GPU-side output can't be compared statically) |
| Build / in-game | — | not performed (deferred per 2026-11-22 user decision; not a CLOSES? NO reason) |

RewritePasses::taaUpscale and RewritePasses::screenDraw are currently empty stubs (On mode falls through to a no-op); Shadow/Verify runs the original via the trampoline and counts the call, with field comparison TODO.

## (2) Proof rows — appended Sigs.json signatures (proven unique by sigscan)

| symbol | rva | size | file offset of match | sigscan bytes | tag |
|---|---|---|---|---|---|
| PassTAAUpscaling | 0xbc8ab12 | 0x2000 | 0xbc89f12 | 31 concrete bytes | [V] |
| PassScreenDraw | 0xbc04dc0 | 0x2000 | 0xbc041c0 | 59 concrete bytes | [V] |

Both signatures were appended to Sigs.json under `deps.bgfx/RendererContextD3D12` only after proving uniqueness (exactly 1 match at the expected file offset = RVA − 0xC00). No existing Sigs.json entry was edited.

## (3) Proof rows — pass-body instruction reads (verbatim from `rdis.exe dis` against Minecraft.Windows.exe 1.26.62.01)

These rows document the prologue, calling convention, allocations, string-hash lookups, and the draw-submit call. They are NOT a full reversal of either body; they are the only instruction-level reads captured so far. Offset column = the RVA of the quoted instruction (each row is one distinct offset).

### TAAUpscaling body 0xbc8ab12 (claimed size 0x2000; listing truncated by `rdis --max 800` in part 4 near 0xbc8e0eb — body NOT fully captured)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc8ab12 | 8 | - | `0xbc8ab12  mov rax,0x33404347445A915D` | stack cookie value loaded into rax | [V] |
| 0xbc8ab1c | 8 | 0xbc8ab1c | `0xbc8ab1c  mov [rbp+0xB78],rax` | store stack cookie at [rbp+0xB78] | [V] |
| 0xbc8aba2 | 8 | 0xbc8aba2 | `0xbc8aba2  mov rcx,[0x1233E1A8]` | load global allocator pointer | [V] |
| 0xbc8abb0 | 4 | 0xbc8abb0 | `0xbc8abb0  mov edx,0x130` | allocation size = 0x130 bytes | [V] |
| 0xbc8abb5 | 8 | 0xbc8abb5 | `0xbc8abb5  call qword ptr [0xF99FFA0]` | call allocator allocate(size=edx) via [0xF99FFA0] | [V] |
| 0xbc8afdf | 4 | 0xbc8afdf | `0xbc8afdf  mov edx,0x340` | allocation size = 0x340 bytes | [V] |
| 0xbc8afe4 | 8 | 0xbc8afe4 | `0xbc8afe4  call qword ptr [0xF99FFA0]` | call allocator allocate(size=edx) via [0xF99FFA0] | [V] |
| 0xbc8b955 | 8 | 0xbc8b955 | `0xbc8b955  lea rdx,[0xF563B27]` | lea "InputFinalColor" string | [V] |
| 0xbc8b966 | 5 | 0xbc8b966 | `0xbc8b966  call 0x79580` | call sub_79580 (FNV-1a 64 string hash) | [V] |
| 0xbc8b9c7 | 8 | 0xbc8b9c7 | `0xbc8b9c7  lea rdx,[0xF549A53]` | lea "InputBufferMotionVectors" string | [V] |
| 0xbc8b9d8 | 5 | 0xbc8b9d8 | `0xbc8b9d8  call 0x79580` | call sub_79580 | [V] |

All `0xRVA  instr` lines above are copied verbatim from `docs/progress/_taa_p1.txt` (rdis dis 0xbc8ab12). FNV-1a basis 0xCBF29CE484222325 / prime 0x100000001B3 seen at 0xbc8b99c / 0xbc8ba0e; hash results stored to globals [0x12AE1B58/0x12AE1B60/0x12AE1B68].

### ScreenDraw body 0xbc04dc0 (size 0x2000; fully captured p1-p3, ends `ret` at 0xbc06fc7 — bulk not yet documented)

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xbc04dc0 | 1 | 0xbc04dc0 | `0xbc04dc0  push rbp` | function prologue | [V] |
| 0xbc04dee | 8 | 0xbc04dee | `0xbc04dee  mov rsi,r8` | passRecord (a2) -> rsi | [V] |
| 0xbc04df1 | 8 | 0xbc04df1 | `0xbc04df1  mov rbx,rdx` | ctx (a1) -> rbx | [V] |
| 0xbc04e11 | 8 | 0xbc04e11 | `0xbc04e11  movq xmm0,[r8+0x168]` | movq load 8 bytes passRecord+0x168 (rect min) | [V] |
| 0xbc04e22 | 4 | 0xbc04e22 | `0xbc04e22  movd xmm1,[r8+0x16C]` | movd load 4 bytes passRecord+0x16C (rect max) | [V] |
| 0xbc04e2b | 4 | 0xbc04e2b | `0xbc04e2b  movd [rcx+rdi+0x1EAB090],xmm0` | movd store 4 bytes to view record rect min | [V] |
| 0xbc04ee3 | 1 | 0xbc04ee3 | `0xbc04ee3  movzx eax,byte ptr [rsi+0x178]` | movzx load 1 byte passRecord+0x178 (flag) | [V] |
| 0xbc04fb3 | 8 | 0xbc04fb3 | `0xbc04fb3  mov r15,[rsi+0x278]` | load 8 bytes passRecord+0x278 (name length) | [V] |
| 0xbc04fcd | 8 | 0xbc04fcd | `0xbc04fcd  mov rbx,[rsi+0x268]` | load 8 bytes passRecord+0x268 (name string ptr) | [V] |
| 0xbc050a4 | 4 | 0xbc050a4 | `0xbc050a4  mov eax,[0xF7D08C5]` | load dword "raw:" from rodata | [V] |
| 0xbc050af | 8 | 0xbc050af | `0xbc050af  mov rax,[0xF7D08BE]` | load qword "ScreenDraw:" from rodata | [V] |
| 0xbc04f18 | 4 | 0xbc04f18 | `0xbc04f18  mov edx,0x30` | allocation size = 0x30 bytes | [V] |
| 0xbc04f1d | 8 | 0xbc04f1d | `0xbc04f1d  call qword ptr [0xF99FFA0]` | call allocator allocate(size=edx) via [0xF99FFA0] | [V] |
| 0xbc04f78 | 5 | 0xbc04f78 | `0xbc04f78  call 0xBCC1A30` | call sub_BCC1A30 (draw submission helper) | [V] |

All `0xRVA  instr` lines above are copied verbatim from `docs/progress/_sd_p1.txt` (rdis dis 0xbc04dc0). Calling convention confirmed: rcx = std::function callable (unused), rdx = render context -> rbx, r8 = pass record -> rsi; s_ctx = [0x12AE1748]; name std::string at passRecord+0x268 with length at +0x278.

## (4) What is NOT reversed / NOT on disk (blocking the item)

| item | state |
|---|---|
| TAAUpscaling body 0xbc8ab12 (0x2000 bytes) | NOT reversed at instruction level; listing truncated by `rdis --max 800` in part 4 near 0xbc8e0eb, never completed; no draw-core (shader/constants/command-list) identified; no C++ replacement |
| ScreenDraw body 0xbc04dc0 (0x2000 bytes) | NOT reversed at instruction level; only prologue/signature/allocation/draw-call rows documented above; bulk lacks [V]/offset/meaning; no C++ replacement |
| Working own-upscale / own-post | does not exist — RewritePasses::taaUpscale and RewritePasses::screenDraw are empty stubs |
| Shadow/Verify pass-record field comparison | TODO (RewriteVerify::compare present but GPU-side render-target output cannot be compared without a frame-buffer capture) |

## CLOSES?

NO — Q5d wording is "Pass-level rewrites (own upscale, own post) behind the registry". The registry half exists on disk (RewritePasses.h/.cpp registered with RewriteRegistry, Sigs.json sigs PassTAAUpscaling@0xbc8ab12 and PassScreenDraw@0xbc04dc0 proven unique, modes off/shadow/on/verify, version gate, runtime toggle, RewriteVerify harness), but the pass bodies are NOT reversed at instruction level and no working own-upscale or own-post replacement exists on disk. Single blocking fact: neither the TAAUpscaling body 0xbc8ab12 nor the ScreenDraw body 0xbc04dc0 (both ~0x2000 bytes) is reversed — the bulk of both bodies lacks [V] proof rows, offsets, and meanings (the TAA listing was truncated by `rdis --max 800` in part 4 near 0xbc8e0eb and never completed), so there is no working replacement to switch On. Remaining on-disk work: complete instruction-level reversal of both bodies (finish reading TAA p4 + SD p2/p3, identify draw-core shader/constants/command list), write C++ replacements in RewritePasses.cpp, verify_oc + `python tools/delegate.py check` clean, then CLOSES? YES with a docs/BIGBANG_TESTS.md section (build + single deferred in-game run are not a CLOSES? NO reason).

## NEXT
DONE
