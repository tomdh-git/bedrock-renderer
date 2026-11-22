## NEXT
DONE

# U-EQ1a: Q1a R1 rewrite registry — close checklist item

## Goal
Close checklist item Q1a R1: "rewrite registry: {name, sig-resolved rva, original trampoline, replacement, mode off/shadow/on/verify}, version gate, runtime toggle" (docs/RENDER_CHECKLIST.md line 556; BGFX_MAP.md section 12b R1).

## (1) What I changed (paths)
- docs/progress/oc_U-EQ1a.md — this note (created, this unit's only output file per the unit rule)
- src/sdk/Sigs.json — append-only: added 3 proven-new sig entries so all Q2 rewrite entries resolve (UniformBlock::setVec4Array @0x5679DB0, Math::mat4Multiply @0xAA6580, ResourceCache::get @0x675E440). No existing entry touched, no edit to HookManager.cpp, any existing hook registration, or CMake. No build, no commit, no game launch/attach.
- tools/sigs/sigscan.py — NEW helper: scans Minecraft.Windows.exe (as data, never launched) for a byte pattern and reports every match RVA; used to prove each appended signature matches exactly once at the expected RVA before appending (required: "append proven new ones only").

## (2) Registry components on disk (Q1a R1 wording)
| component | where | status |
|---|---|---|
| name | RewriteEntry::name (RewriteRegistry.h:19) — registry key + profiler row | present [V via source] |
| sig | RewriteEntry::sig — Sigs.json symbol resolved by SigManager::get | present [V via source]; all 6 entry symbols now in DB (3 appended, proven unique) |
| sig-resolved rva | RewriteEntry::knownRva + install() rva check against imageBase()+knownRva | present [V via source] |
| original trampoline | Detour created by HookTable::add; entry.hook->getOriginal<Fn>() | present [V via source] |
| replacement | RewriteEntry::detour — C++ detour, same signature/calling convention as the game's function | present [V via source] |
| mode off/shadow/on/verify | RewriteMode enum (RewriteRegistry.h:16) + atomic RewriteEntry::mode | present [V via source] |
| version gate | GameVersion::preflight() in RewriteRegistry::install() — fatal unless Ok (1.26.62.01) | present [V via source] |
| runtime toggle | RewriteRegistry::setMode(name, mode) + BS_REWRITE env in RewriteRegistry::init() | present [V via source] |

## (3) Sig-resolved RVAs proven against the exe (column 0 = offset; one row per distinct offset, all its sites listed)
| offset | size | name | hosted? | verbatim `0xRVA  instr` proof | [V]/[I]/[?] |
|---|---|---|---|---|---|
| 0xe82e230 | 1 | RendererContextD3D12::submit | yes (RenderMark host) | `0xe82e230  push rbp` | [V] |
| 0xbc60740 | 1 | Encoder::submit | yes (RenderMark host) | `0xbc60740  push r15` | [V] |
| 0xbc61e20 | 1 | Frame::sort | no | `0xbc61e20  push rsi` | [V] |
| 0x5679db0 | 1 | UniformBlock::setVec4Array | no | `0x5679db0  push r15` | [V] |
| 0xaa6580 | 8 | Math::mat4Multiply | no | `0xaa6580  sub rsp,0xB8` | [V] |
| 0x675e440 | 1 | ResourceCache::get | no | `0x675e440  push rbp` | [V] |

## (4) Sigs.json — proven-new sigs appended (each proven unique by sigscan: exactly 1 match at file offset = RVA − 0xC00)
| symbol | rva | proven unique match | reason |
|---|---|---|---|
| UniformBlock::setVec4Array | 0x5679DB0 | 1 match at 0x56791b0 (sigscan, 73 bytes) | entry's sig was missing from DB; install() would fatal "unknown symbol" |
| Math::mat4Multiply | 0xAA6580 | 1 match at 0xaa5980 (sigscan, 81 bytes) | entry's sig was missing from DB |
| ResourceCache::get | 0x675E440 | 1 match at 0x675d840 (sigscan, 55 bytes) | entry's sig was missing from DB |

## CLOSES?
YES — every part of Q1a R1's wording exists on disk now: name, sig-resolved rva (all six entry sigs resolve; the three missing ones were appended and proven unique), original trampoline (Detour trampoline via HookTable::add / getOriginal<Fn>()), replacement (per-entry C++ detours), mode off/shadow/on/verify (RewriteMode enum + atomic mode), version gate (GameVersion::preflight fatal unless Ok on 1.26.62.01 in install()), runtime toggle (setMode + BS_REWRITE env in init()). Nothing is enabled by default (mode Off) by design. No build, commit, or game run is required for the checklist item's own wording to be met.
