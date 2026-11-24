## NEXT
DONE

## UNIT
U-EX1.bc6a9d0 — LIFT bgfx rendererUpdateUniforms (0xbc6a9d0, 0x200 bytes, depth 2, D2). Checklist line: X1.bc6a9d0 LIFT bgfx rendererUpdateUniforms, fully reversed.

## SUMMARY
Lifted function 0xbc6a9d0 (Minecraft Windows 1.26.62.01, size 0x200, [0xbc6a9d0, 0xbc6abd0)) into C++ with the exact x64 MSVC ABI signature:
`void rendererUpdateUniforms(RendererContextI* renderer /*rcx*/, UniformBuffer* ub /*rdx*/, uint32_t begin /*r8d*/, uint32_t end /*r9d*/, std::vector<uint16_t>* touched /*5th stack arg, may be null*/, void* ctx /*6th stack arg*/)`, void return.

Behavior [V from disassembly of [0xbc6a9d0, 0xbc6abd0)]:
- touched->clear() (last = first) when touched != null; loop over [begin, end).
- Each iteration: memcpy 4-byte op from ub->data + pos; op == 1 (End) -> exit; type = op >> 27; size = ((op >> 1) & 0x3FF) * kUniformTypeSize[type], table {4, 0, 16, 36, 64} at RVA 0xF441930 [V: bytes read from the exe .rdata]; payload = ub->data + pos + 4.
- op > 0x27FFFFFF -> marker: tail call renderer->setMarker(ctx, payload, size) via the jmp-rax trampoline at [0xF99FFA0] = sub_eea6040 (vtable slot 47); loop continues at pos += size + 4.
- op <= 0x27FFFFFF -> handle = op >> 11; if touched != null: lower_bound over touched storage for first element >= handle; skip if *ip == handle; else insert handle sorted/unique: if last == cap -> boundary sub_74c9c0(vec, ip, &handle) (class stl, growth); else if ip == last -> append; else shift [ip, last) right by one element (*last = *(last-1), last += 2, memmove(ip+1, ip, bytes), *ip = handle) and update the vector's last member.
- Copy bit op & 1: src = payload (inline bytes) else src = *(const void**)payload; tail call renderer->updateUniform(ctx, handle, src, size) via the same trampoline (vtable slot 46); pos += size + 4.

Calls in the function (all quoted verbatim beside their statements and in the call log):
0xbc6aa3b  call qword ptr [0xF99FFA0]  (tail call -> renderer->setMarker, slot 47)
0xbc6aa5d  call 0xEBCE390              (memcpy intrinsic; forwarder to sub_eec6ec0)
0xbc6ab2f  call 0xEEC6DE0              (memmove intrinsic)
0xbc6ab45  call 0x74C9C0               (boundary, class stl)
0xbc6abaf  call qword ptr [0xF99FFA0]  (tail call -> renderer->updateUniform, slot 46)
No other calls; no [?]/[I]/TODO/UNVERIFIED tags; no stubs; no skipped branches; no null guards/SEH beyond the original.

Layout constants with static_asserts in rendererUpdateUniforms.h (and repeated in the .cpp): Uniform16Vector {first +0x00, last +0x08, end_storage +0x10, sizeof 0x18}; UniformBuffer {size +0x00, pos +0x04, sizeof 0x08 (data at +0x08)}; RendererContextI vtable slots 46 (+0x170) updateUniform, 47 (+0x178) setMarker; kUniformTypeSize[5] = {4, 0, 16, 36, 64}.

## FILES
- docs/progress/oc_U-EX1.bc6a9d0.md (this result file; created)
- docs/functions/bc6a9d0.md (changed: 'Reversed source (complete)' section replaced with complete lifted source, instruction ranges and verbatim call quotes)
- src/client/features/render/native/bgfx/rendererUpdateUniforms.cpp (created: first line `// LIFT 0xbc6a9d0 size 0x200 1.26.62.01 rendererUpdateUniforms`, source, verbatim call log, LIFT_FN registry entry)
- src/client/features/render/native/bgfx/rendererUpdateUniforms.h (created: layout constants, static_asserts, signature)

Not edited (per rules): Sigs.json, shared headers, CMake, hooks, other units' files, docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, docs/data/*.tsv. No builds, no game.

## LIFTCHECK
LIFTCHECK OK 0xbc6a9d0

## UNRESOLVED CALL
none: 0xEBCE390 and 0xEEC6DE0 are compiler library intrinsics (memcpy/memmove), 0x74C9C0 is a boundary callee (class stl, docs/data/native_boundary.tsv line 129) called via native::sub_74c9c0, and the two [0xF99FFA0] calls are tail calls through the jmp-rax trampoline sub_eea6040 to the renderer interface virtuals updateUniform (slot 46) and setMarker (slot 47). No callee is outside the lift set, boundary, or intrinsic set.

## Callee classification
- 0x74c9c0: boundary stl (native_boundary.tsv line 129) -> native::sub_74c9c0(Uniform16Vector*, uint16_t*, const uint16_t*)
- 0xEBCE390: memcpy intrinsic (tail-forwarder to sub_eec6ec0, docs/progress/pre/0xEBCE390.md)
- 0xEEC6DE0: memmove intrinsic
- [0xF99FFA0] -> sub_eea6040 = `jmp rax` tail-call trampoline (docs/progress/pre/0xEEA6040.md); real targets are renderer->updateUniform (vtable slot 46, [rax+0x170]) and renderer->setMarker (vtable slot 47, [rax+0x178])

CLOSES? YES
