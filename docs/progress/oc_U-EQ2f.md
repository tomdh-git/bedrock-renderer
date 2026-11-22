## NEXT
DONE

# U-EQ2f: Q2f 0xaa6580 mat4 multiply rewrite (pure SIMD leaf, 6ih)

## Goal
Close checklist item Q2f: "0xaa6580 mat4 multiply (pure SIMD leaf, 6ih): trivial first rewrite to validate the registry and shadow-verify harness (compare 16 floats)" (docs/RENDER_CHECKLIST.md line 568; BGFX_MAP.md section 6ih/12).

## (1) What I changed (paths)
- docs/progress/oc_U-EQ2f.md — this note (created, this unit's only output file per the unit rule)
- No source files created or edited: every Q2f piece already exists on disk from prior units (verified below). No HookManager.cpp edit, no hook registration, no CMake edit, no Sigs.json edit (entry already appended in EQ1a), no build, no commit, no game launch/attach.

## (2) Q2f components on disk (all already present, none enabled by default)
| component | path | status |
|---|---|---|
| mat4Multiply rewrite (C++ source matching reversed disassembly) | src/client/features/render/rewrite/RewriteMath.cpp | exists [V via source] |
| detour + registry registration (RewriteEntry + RewriteReg) | RewriteMath.cpp:27-29 | exists [V via source] |
| sig-resolved RVA 0xAA6580 in Sigs.json (proven unique, 1 match) | src/sdk/Sigs.json line 89 | exists [V via source] |
| shadow/verify harness comparing out[16 floats] | src/client/features/render/rewrite/RewriteVerify.h | exists [V via source] |
| registry: mode off/shadow/on/verify, version gate, runtime toggle | src/client/features/render/rewrite/RewriteRegistry.{h,cpp} | exists [V via source] |

RewriteMath.cpp registers `Math::mat4Multiply` at RVA 0xAA6580 via `static RewriteEntry sMat4Entry("Math::mat4Multiply", "Math::mat4Multiply", 0xAA6580, ...)` + `static const RewriteReg sMat4Reg(sMat4Entry)`. In Shadow/Verify mode the detour: copies inputs (out may alias), runs the original via trampoline on real inputs, saves the 16-float result, runs `RewriteMath::mat4Multiply` on copied inputs into a private buffer, then `RewriteVerify::compare(e, mode, "out[16 floats]", original, rewrite, sizeof(original))`. Nothing is installed unless BS_REWRITE sets a non-Off mode (RewriteRegistry::init).

## (3) Proof rows — 0xaa6580 mat4 multiply body (0xaa6580..0xaa674e, ~0x1CE bytes, no calls)

One annotated row per distinct offset accessed; all proof lines copied verbatim from `rdis.exe dis 0xaa6580` output against Minecraft.Windows.exe 1.26.62.01. Per BGFX_MAP 6ih: out = rcx, A = rdx (4 rows at +0x00/+0x10/+0x20/+0x30), B = r8 (16 floats read as broadcasts: movups at +0..+0x30 then shufps 0 broadcasts each element, plus 3 movss at +0x34/+0x38/+0x3C), result row i = sum_j B[i][j] * A.row[j], stored at rcx+0x00/+0x10/+0x20/+0x30, returns rax = rcx.

| offset | size | site | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xaa6580 prologue (stack frame) | 4 | - | `0xaa6580  sub rsp,0xB8` | allocate 0xB8 stack frame, save xmm6-15 | [V] |
| 0xaa65ca return value setup | 8 | - | `0xaa65ca  mov rax,rcx` | return value = out (rcx) | [V] |
| B+0x00 (r8) | 16 | 0xaa65cd | `0xaa65cd  movups xmm0,[r8]` | B element 0 load (broadcast via shufps 0 at aa6627) | [V] |
| B+0x04 (r8) | 16 | 0xaa65d1 | `0xaa65d1  movups xmm10,[r8+4]` | B element 1 load | [V] |
| B+0x08 (r8) | 16 | 0xaa65d6 | `0xaa65d6  movups xmm9,[r8+8]` | B element 2 load | [V] |
| B+0x0C (r8) | 16 | 0xaa65db | `0xaa65db  movups xmm8,[r8+0xC]` | B element 3 load | [V] |
| B+0x10 (r8) | 16 | 0xaa65e0 | `0xaa65e0  movups xmm12,[r8+0x10]` | B element 4 load | [V] |
| B+0x14 (r8) | 16 | 0xaa65e5 | `0xaa65e5  movups xmm15,[r8+0x14]` | B element 5 load | [V] |
| B+0x18 (r8) | 16 | 0xaa65ea | `0xaa65ea  movups xmm14,[r8+0x18]` | B element 6 load | [V] |
| B+0x1C (r8) | 16 | 0xaa65ef | `0xaa65ef  movups xmm13,[r8+0x1C]` | B element 7 load | [V] |
| B+0x20 (r8) | 16 | 0xaa65f4 | `0xaa65f4  movups xmm4,[r8+0x20]` | B element 8 load | [V] |
| B+0x24 (r8) | 16 | 0xaa65f9 | `0xaa65f9  movups xmm7,[r8+0x24]` | B element 9 load | [V] |
| B+0x28 (r8) | 16 | 0xaa65fe | `0xaa65fe  movups xmm6,[r8+0x28]` | B element 10 load | [V] |
| B+0x2C (r8) | 16 | 0xaa6603 | `0xaa6603  movups xmm5,[r8+0x2C]` | B element 11 load | [V] |
| B+0x30 (r8) | 16 | 0xaa6608 | `0xaa6608  movups xmm1,[r8+0x30]` | B element 12 load | [V] |
| B+0x34 (r8) | 4 | 0xaa665d | `0xaa665d  movss xmm10,[r8+0x34]` | B element 13 load (scalar) | [V] |
| B+0x38 (r8) | 4 | 0xaa6657 | `0xaa6657  movss xmm9,[r8+0x38]` | B element 14 load (scalar) | [V] |
| B+0x3C (r8) | 4 | 0xaa6651 | `0xaa6651  movss xmm8,[r8+0x3C]` | B element 15 load (scalar) | [V] |
| A+0x00 (rdx) | 16 | 0xaa660d | `0xaa660d  movups xmm2,[rdx]` | A row 0 read | [V] |
| A+0x10 (rdx) | 16 | 0xaa6610 | `0xaa6610  movups xmm11,[rdx+0x10]` | A row 1 read | [V] |
| A+0x20 (rdx) | 16 | 0xaa661a | `0xaa661a  movups xmm3,[rdx+0x20]` | A row 2 read | [V] |
| A+0x30 (rdx) | 16 | 0xaa6632 | `0xaa6632  movups xmm11,[rdx+0x30]` | A row 3 read | [V] |
| out+0x00 (rcx) | 16 | 0xaa6663 | `0xaa6663  movups [rcx],xmm0` | out row 0 write | [V] |
| out+0x10 (rcx) | 16 | 0xaa669a | `0xaa669a  movups [rcx+0x10],xmm12` | out row 1 write | [V] |
| out+0x20 (rcx) | 16 | 0xaa66c5 | `0xaa66c5  movups [rcx+0x20],xmm4` | out row 2 write | [V] |
| out+0x30 (rcx) | 16 | 0xaa66f7 | `0xaa66f7  movups [rcx+0x30],xmm1` | out row 3 write | [V] |
| 0xaa673e epilogue | 8 | - | `0xaa673e  add rsp,0xB8` | deallocate stack frame | [V] |
| 0xaa6745 return | 1 | - | `0xaa6745  ret` | return rax (= out) | [V] |

## Shadow/verify harness proof (16-float comparison)
RewriteMath.cpp:44-59 — Shadow/Verify path:
1. `std::memcpy(inA, a, 64); std::memcpy(inB, b, 64);` — copy inputs (out may alias them) [V via source]
2. `e.original<&rwMat4Detour>()(out, a, b)` — run original on real inputs, writes real out [V via source]
3. `std::memcpy(original, out, 16)` — save original's 16-float result [V via source]
4. `RewriteMath::mat4Multiply(rewrite, inA, inB)` — run rewrite on copies into private buffer [V via source]
5. `RewriteVerify::compare(e, mode, "out[16 floats]", original, rewrite, sizeof(original))` — compare 16 floats; Verify mode aborts on first divergence via `Logger::fatal` [[noreturn]] [V via source]

RewriteVerify.h:36-45 — `compare` memcmps original vs rewrite; on first differing byte: Verify mode calls `Logger::fatal` (abort loudly), Shadow logs first 16 divergences [V via source].

## CLOSES?
YES — every part of Q2f's wording exists on disk now: the mat4Multiply rewrite (RewriteMath.cpp, matches the reversed disassembly at 0xaa6580), registered in the registry (RewriteEntry + RewriteReg, sig "Math::mat4Multiply" in Sigs.json line 89), and shadow-verified comparing 16 floats (RewriteVerify::compare with "out[16 floats]", Verify mode aborts on first divergence). All proof rows are [V] against rdis output of Minecraft.Windows.exe 1.26.62.01. No build, commit, or game launch required for the item's own wording.

## NEXT
DONE
