## NEXT
DONE — 0x6639930 lifted (size 0x72, "BgfxFrameBuilder slot 90", depth 0, milestone 4, region framebuilder, D0); liftcheck printed LIFTCHECK OK 0x6639930; no further steps.

## FILES
- created: docs/progress/oc_U-EX4.6639930.md (this result file)
- created: docs/functions/6639930.md (dossier: mechanical facts, argument use, callees, signature, version anchors, 'Reversed source (complete)', struct fields touched, verification, open questions)
- created: src/client/features/render/native/framebuilder/sub_6639930.h (layout constants k*Offset* with static_asserts: self+0x278 field0x278, self+0x358 state0x358, vtable+0x230/vtable+0x228 byte-offset constants, state+0x7E5 byte0x7E5, pointee+0x180 value0x180; structs BgfxFrameBuilder, Field0x278Pointee, BuilderState; signature declaration int32_t sub_6639930(BgfxFrameBuilder* self) in namespace native)
- created: src/client/features/render/native/framebuilder/sub_6639930.cpp (first line `// LIFT 0x6639930 size 0x72 1.26.62.01 BgfxFrameBuilder slot 90`; complete reversed source with per-instruction `// 0xA..0xB` citations covering [0x6639930, 0x66399a2), verbatim call quotes in the #if 0 block, and LIFT_FN(sub_6639930, "sub_6639930", 0x6639930, sub_6639930, nullptr) registry entry; footprint nullptr — read-only function)

No existing files edited (no Sigs.json, no shared headers, no CMake, no hooks, no other unit's files). No builds run.

## Summary of the lift [V]
Disassembly (rdis fn 0x6639930; [0x6639930, 0x66399a2), 33 instructions): prologue push rsi / sub rsp,0x20 / mov rsi,rcx; self+0x0 (vtable pointer) and vtable+0x230 loaded; call #1 `0x6639942  call qword ptr [0xF99FFA0]`; `test al,al` — non-zero -> state+0x7E5 byte (movzx, zero-extended) returned and jump to epilogue; zero -> self+0x0 and vtable+0x228 reloaded, `mov rcx,rsi`, call #2 `0x6639969  call qword ptr [0xF99FFA0]`; `mov ecx,eax; mov al,3` (EAX = (call2 & ~0xFF) | 3); `test cl,cl` — zero -> return EAX; else self+0x278 pointer loaded — null -> return EAX; else pointee+0x180 int32 v: `xor eax,eax / cmp ecx,2 / sete al / lea eax,[rax+rax*2] / add eax,3 / test ecx,ecx / cmove eax,ecx` -> v==0 ? 0 : (v==2 ? 6 : 3); epilogue add rsp,0x20 / pop rsi / ret.
Same reads (self+0x0 x2, vtable+0x230, vtable+0x228, self+0x358, state+0x7E5, self+0x278, pointee+0x180), same writes (none), same calls in the same order (2), same return (EAX). No null guard, no SEH (none in the original, none added). No [?]/[I]/TODO/UNVERIFIED tags in source or dossier reversed-source block.

## Callee resolution [V]
Both calls: rdis annotation `[data_f99ffa0] = sub_eea6040`; docs/data/native_boundary.tsv line 506: `0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)` -> class boundary/vendor, NOT an unresolved call. sub_eea6040 body [V]: `0xEEA6040  jmp rax` (rdis dis 0xeea6040) -> tail-call to RAX with RCX unchanged; net effect call #1 = (*self->vtable+0x230)(self) [vtable slot 70], call #2 = (*self->vtable+0x228)(self) [vtable slot 69], exactly the targets the vtable loads right before each call set up. Same convention as sibling unit sub_66399b0 (identical trampoline pattern, 0x66399c2).

## LIFTCHECK
LIFTCHECK OK 0x6639930

## UNRESOLVED CALL
none (both call targets resolve to sub_eea6040, boundary/vendor via native_boundary.tsv)

CLOSES? YES