## NEXT
DONE

## Unit
U-EX4.6639bc0 — LIFT sub_6639bc0 ("BgfxFrameBuilder slot 87", 0x6639bc0, size 0x24, depth 0, milestone 4, region framebuilder). 0 callees in the lift set; one straight-line 10-instruction function, no branches.

## What the function does (all [V] from rdis dis 0x6639bc0 0x24)
0x6639bc0  push rsi
0x6639bc1  sub rsp,0x20
0x6639bc5  mov rsi,rdx
0x6639bc8  lea rcx,[0x12AE0E90]          ; [data_12ae0e90]
0x6639bcf  mov [rdx],rcx                 ; W out+0x0 = &data_12ae0e90
0x6639bd2  call 0xEEC7570                ; CRT strlen thunk: 0xEEC7570  jmp qword ptr [0xF9A9048], [0xF9A9048] = strlen [V] (peimports.py key IAT resolution docs/progress/oc_U-EX0b1.md:10; cross-verified 0x76a72c call 0xEEC7570 then 0x76a731 cmp rax,0xF [V])
0x6639bd7  mov [rsi+8],rax               ; W out+0x8 = strlen(out->ptr)
0x6639bdb  mov rax,rsi
0x6639bde  add rsp,0x20
0x6639be2  pop rsi
0x6639be3  ret                         ; RAX = out = RDX

Entry RCX is dead (overwritten before any read). The 16-byte object at *RDX: +0x0 const char* ptr = &data_12ae0e90, +0x8 size_t length = strlen(ptr). Same reads, writes, calls, order, return; no null guard/SEH (original has none).

Call handling: 0x6639bd2 call 0xEEC7570 is a CRT library intrinsic (strlen) through import thunk 0xEEC7570, data slot 0xF9A9048; called directly as std::strlen with the slot RVA documented — same precedent as 0xEEC6EC0/memcpy via [0xF9A8A98] (sub_eec6ec0.cpp). Not a lift-set callee, not a boundary row, no wrapper invented, not unresolved.

## FILES
- docs/progress/oc_U-EX4.6639bc0.md (this result file)
- docs/functions/6639bc0.md (dossier: signature, register/argument map, Reversed source (complete), phases, struct fields touched, callees, OPEN questions)
- src/client/features/render/native/framebuilder/sub_6639bc0.h (layout constants kSlot87OffsetPtr/Length/Size, FrameBuilderSlot87 struct, static_asserts, extern data_12ae0e90, signature)
- src/client/features/render/native/framebuilder/sub_6639bc0.cpp (first line `// LIFT 0x6639bc0 size 0x24 1.26.62.01 sub_6639bc0`, lifted body with range citations, verbatim call quotes in #if 0 block, LIFT_FN registry entry)

No other files edited (no Sigs.json, no shared headers, no CMake, no hooks, no other units' files; no build, no game).

## LIFTCHECK
`python tools/sigs/liftcheck.py 0x6639bc0` printed:

LIFTCHECK OK 0x6639bc0

(verify_oc on the source: claimed=11 match=11 mismatch=0 no-such-instr=0. cppsyntax: 61 environment include-chain errors (Detour.h/Profiler.h std::atomic PCH ordering), identical count for the reference unit sub_eec6ec0.cpp, and zero errors inside sub_6639bc0.cpp itself.)

## UNRESOLVED CALL
none — the single call target 0xEEC7570 resolves to CRT strlen via import slot [0xF9A9048] [V] and is called directly as std::strlen (library intrinsic precedent), so it is neither a lift-set callee nor a boundary row nor an unresolved call.

## TOOL REQUESTS
None.

CLOSES? YES
