## NEXT
DONE

# U-EL14c — Glyph atlas: SDF glyph uniforms + FONT_TYPE permutation (atlas pending)

## Result

The glyph atlas is NOT created by font code. The GlyphTexture uniform value is a 16-byte SSO texture NAME string (not a bgfx handle) supplied by the caller as arg8 ([rbp+0xEB8]) and bound at draw time through sub_5679DB0 -> memcpy 0xEEC6EC0. The claimed object+0x38 SSO-name location is refuted: object [rbp+0xE80] in 0x674a3a0 reads fields +0x10/+0x18/+0x1D8/+0x1F8/+0x1DA/+0x1E8/+0x1FC/+0x20C/+0x21C/+0x244 and never +0x38, with no writes to [rbp+0xBA0]/[rbp+0xBAA] in 0x674a3a0..0x674abef. The value chain runs UI record field [r9+0x28] (or [r9]) as arg8 <- object+0xF0 then +0x28 via sub_6664760 ("FrameBuilder - Insert UI"), which has zero static callers (indirect dispatch) and is not statically locatable. No glyph-atlas name string, no createTexture/createDynamicTexture call, and no font init/reset texture creation exists in .text; font textures are pack-loaded <font>_ttf.png/_ttfmsdf.png via texload 0x58a1310 (callers sub_6b84680/sub_6ea2df0, not font).

## Finding table (name | rva | size | proof | status)

| GlyphTexture 16-byte NAME loaded from caller arg8 | 0x674aa09 | 16 | `0x674aa09  movups xmm0,[rax]` | [V]
| Name staged into uniform binder argument area | 0x674aa0c | 16 | `0x674aa0c  movaps [rbp+0xC10],xmm0` | [V]
| Binder name count set to 1 | 0x674aa13 | 8 | `0x674aa13  mov qword ptr [rbp+0x910],1` | [V]
| Object base loaded from [rbp+0xE80] | 0x674a4d1 | 8 | `0x674a4d1  mov r14,[rbp+0xE80]` | [V]
| Uniform slot entry record+0x28 hash compare | 0x674aa53 | 8 | `0x674aa53  cmp [r10+0x28],r8` | [V]
| Uniform slot valid flag set | 0x674aa79 | 1 | `0x674aa79  mov byte ptr [rbp+0x5F2],1` | [V]
| sub_5679DB0 reads binder count word | 0x5679dbf | 2 | `0x5679dbf  movzx r14d,word ptr [rdx]` | [V]
| sub_5679DB0 sets target slot valid flag | 0x5679dfe | 1 | `0x5679dfe  mov byte ptr [r15+r14+0xC],1` | [V]

## Answers to the task questions

- Where GlyphTexture value comes from: caller-provided arg8 at [rbp+0xEB8], loaded as a 16-byte NAME by `0x674aa09  movups xmm0,[rax]` and passed to sub_5679DB0 at `0x674aa91  call 0x5679DB0`. It is a texture NAME resolved by name at draw time, not a bgfx handle and not an atlas handle fetch.
- Which object field holds the texture handle: none. Object [rbp+0xE80] reads no field at +0x38 (refuting the r2 SSO-name claim); the value is not stored in an object field in this path, it arrives as arg8.
- Who writes that field: the UI record field [r9+0x28] (stride-0x38) / [r9] (stride-0x86) that becomes arg8 is assembled by sub_6664760, which has zero static callers and is unreachable through indirect dispatch, so the writer is NOT statically locatable. sub_5679DB0 writes the 16-byte name into the hash-selected uniform slot via `0x5679df9  call 0xEEC6EC0` (memcpy, size 16) and sets the valid flag.

## Blocking fact (why CLOSES? = NO)

No glyph-atlas texture creation/update site is statically locatable: zero direct bgfx createTexture/createDynamicTexture calls in .text, no atlas name string, font init/reset create no textures, and creation is vtable-indirect render-thread work (RendererContext slots 26/28, texture table this+0xbde178 stride 0xB8). The object-field writer (sub_6664760) is likewise not statically locatable. Closing requires a live trace on bgfx createTexture/updateTexture (RendererContext slots 26/28) and on the sub_6664760 record writer.

## Angles tried (not redone)

descscan2 UIText case 3; xref str glyph_/font/atlas; livemem (game not running); rdis xr/callers; field/rw struct scan of 0x674a3a0 (no [rbp+0xBA0]/[rbp+0xBAA] writes); vt/vcalls (sub_6664760 0 xrefs); texload 0x58a1310 callers.

CLOSES?=NO — blocking: glyph atlas creation site and object-field writer not statically locatable; needs live trace.
