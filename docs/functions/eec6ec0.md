# sub_eec6ec0 (0xeec6ec0, size 0x6, depth 0, milestone 7, region root, D0) — Minecraft Bedrock 1.26.62.01

## Source of truth
`tools/rdis/target/release/rdis.exe "<exe>" dis 0xeec6ec0 6` — one instruction:
`0xeec6ec0  jmp qword ptr [0xF9A8A98]  ; [data_f9a8a98]`
Function size from docs/data/native_functions.tsv row: 0x6 bytes; 0 callees in the lift set; callee classification `lift` (auto-unresolved->lift) in docs/data/native_boundary.tsv line 512.

## Signature guess
`void* sub_eec6ec0(void* dst, const void* src, size_t n)` — x64 Microsoft ABI: RCX = dst, RDX = src, R8 = n, return RAX = dst. Identical to the memcpy target the thunk tail-jumps to (no register shuffling).

## Register / argument map
- RCX = dst (1st arg) — forwarded unchanged to memcpy [V: ABI; thunk reads no register before the jmp].
- RDX = src (2nd arg) — forwarded unchanged [V].
- R8 = n (3rd arg) — forwarded unchanged [V].
- RAX = return value = dst (memcpy returns its destination) [V: memcpy semantics; no instruction after the jmp can alter RAX].
- No registers are read or written by the thunk itself other than the fall-through register arguments; no stack frame, no prologue/epilogue [V: the function is one 6-byte instruction].

## Reversed source (complete)

// 0xeec6ec0..0xeec6ec6
void* sub_eec6ec0(void* dst, const void* src, size_t n) {
    return std::memcpy(dst, src, n);   // 0xeec6ec0  jmp qword ptr [0xF9A8A98] ; tail call to memcpy via data slot 0xF9A8A98
}

// Verbatim instruction (matches rdis dis 0xeec6ec0; instruction part):
0xeec6ec0  jmp qword ptr [0xF9A8A98]

## Phase
0xeec6ec0..0xeec6ec6: one instruction, an indirect tail jump through data slot 0xF9A8A98 to memcpy; dst/src/n arrive in RCX/RDX/R8 and are forwarded unchanged, memcpy's return (dst) lands in RAX and is returned to the caller; control never returns to the thunk [V: rdis dis listing above].
  return std::memcpy(dst, src, n);   // 0xeec6ec0  jmp qword ptr [0xF9A8A98]

## Target of the indirect jump
Slot 0xF9A8A98 is the MSVC CRT import of memcpy:
- [V] docs/functions/bc40a30.md line 195: "0xEEC6EC0 | CRT/library intrinsic | memcpy (thunk, jmp [0xF9A8A98])" citing `0xbc40b17  call 0xEEC6EC0`.
- [V] docs/BGFX_MAP.md:928: the terrain extractor copies `count<<4` bytes (vec4 array) "with 0xeec6ec0 (memcpy)" to pool+offset — consistent with memcpy(dst=pool+offset, src=data, n=count<<4).
- [V] docs/functions/67417f0.md:169: "0xeec6ec0 / 0xeec6de0 = memcpy-like (dst,src,n)".
- [V live] docs/data/live/readlog.txt line 6: "17:25:47 ptr @0xF9A8A98 1" — the slot is read at runtime.
At runtime the loader fills the slot with memcpy's address [I: standard PE loader behavior for an unbound import slot; the resolved name is bound by the convergent [V] dossier evidence above, since the IAT slot contents cannot be read with the read-only static tools available to this unit].

## Struct fields touched
none: the function touches no struct fields [V: single jmp instruction, no memory operand other than the slot load for control flow]. The tail-jumped memcpy reads [src, src+n) and writes [dst, dst+n) in the caller's memory — declared as the function's footprint by the caller side, not by this thunk.

## Callees
none directly — 0 callees in the lift set [V: the listing contains no call instruction]. The indirect target memcpy is called from the lifted body as `std::memcpy`, a CRT library intrinsic the compiler may inline (permitted call class per docs/RENDER_NATIVE_SPEC.md section 2); it is not a lift callee and not a boundary wrapper.

## OPEN questions
none.
