## NEXT
DONE

# oc U-EF1b — VV pass order F1b: in/out resources per pass (pending part of 6ar)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis disassembly).
Item line (pending part): "in/out resources per pass still pending | PROGRESS 2026-11-21 oc_U-EL6b.md (verify_oc 11/11): pass declaration fns (0x5698290, 0x5684660, 0x5667860, 0x5693680 ...) copy a 28-byte descriptor struct opaquely [V]; nothing in 0x55f1450 or callees separates input from output resources statically, so in/out stays open".

This unit does ONLY the pending part: field map of the 28-byte pass descriptor as consumed by the declaration helpers, to test whether any field separates input from output resources.

Prior [V]: oc_U-EL6b (verify_oc 11/11) — declaration helpers copy a 28-byte descriptor opaquely. oc_U-F1b2 — 50 ordered call sites to 9 helpers (sub_5698290 x15, sub_5689800 x18, sub_5667860 x4, sub_5693680 x7, sub_5694510 x2, sub_5695960 x1, sub_5696540 x1, sub_5697650 x1, sub_5684660 x1).
BGFX_MAP 6aq [V]: declaration fns are templates over Declarator<RenderContext> (dragon::framerenderer::drawutils); inputs/outputs declared only via five binders (BindMaterialTexture, BindFramebufferDepth, BindFramebufferColor, BindShaderBuffer, BindAccelerationStructure); no other dependency kind exists. BGFX_MAP 6ar [V]: builder 0x55f1450 emits declarations in source order (pass order: shadows -> volume -> prepass -> copies/blits -> forward PBR -> motion -> objects -> UI -> nametags -> draw).

## Evidence — sub_5698290 (the 28-byte descriptor declaration helper, 15 call sites)

sub_5698290 [0x5698290..0x569a290): signature (rcx=Declarator*, r8=descriptor*). It calls the allocator with edx=0x28 (40-byte record: 8-byte vtable header + 28-byte descriptor) and copies the descriptor opaquely — every descriptor byte is read exactly once, never tested or branched on:

- descriptor +0x00..+0x0F: `0x56982dc  movups xmm0,[rbx]`   (rbx = r8 = descriptor, written to record +8)
- descriptor +0x0C..+0x1B: `0x56982df  movups xmm1,[rbx+0xC]` (written to record +0x14)

Union of the two reads covers all 28 bytes (+0x00..+0x1B). Then the record pointer is appended to the Declarator's 8-byte entry vector (Declarator+0x28 end), a 0x50-stride pass-entry record is appended at Declarator+0x40 ({+0x00 = Declarator+0x50 ctx ptr, +0x08 = descriptor record ptr, +0x40 = byte 0, +0x48 = dword 0xFFFFFFFF}), and sub_567a7b0 (callee) registers {desc-record ptr, count} at Declarator+0x68 opaquely (stores record ptr at +0x20, count dword at +0x28 of its own 0x30-byte record; no descriptor field interpreted).

The other declaration helpers (sub_5684660, sub_5667860, sub_5693680, ...) consume larger per-pass config structs (0x110..0x2F0 bytes), copied field-by-field or opaquely in blocks; none of them reads this 28-byte descriptor.

## Field map — 28-byte descriptor pass struct (offsets within the descriptor, plus the two pass-entry record fields written by the same helper)

One row per distinct offset, all its sites listed, verbatim instruction lines copied from rdis output. Meaning '-' unless an instruction or string shows it.

| offset | size | field | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
| +0x00 | 16 | descriptor bytes +0x00..+0x0F (opaque resource/param half) | 0x56982dc | `0x56982dc  movups xmm0,[rbx]` | - | [V] |
| +0x0C | 16 | descriptor bytes +0x0C..+0x1B (opaque resource/param half) | 0x56982df | `0x56982df  movups xmm1,[rbx+0xC]` | - | [V] |
| +0x40 | 1 | pass-entry record flag byte | 0x5698344 | `0x5698344  mov byte ptr [rbx+0x40],0` | - | [V] |
| +0x48 | 4 | pass-entry record sentinel dword | 0x5698348 | `0x5698348  mov dword ptr [rbx+0x48],0xFFFFFFFF` | - | [V] |

## Builder-side descriptor construction (one decoded call site: pass 13 at 0x55ff2c5 -> sub_5698290; descriptor = [rbp+0x1EF4..0x1F0F])

Stores set concrete values only; no store and no string marks any field as input or output:
- `0x55ff1e3  mov dword ptr [rbp+0x1F00],0`        (+0x0C = 0)
- `0x55ff1ed  mov byte ptr [rbp+0x1F04],0`           (+0x10 = 0)
- `0x55ff1f4  mov word ptr [rbp+0x1EFC],0`           (+0x08 = 0)
- `0x55ff1fd  mov rax,0x300000001` / `0x55ff207  mov [rbp+0x1F08],rax` (+0x14 = qword 0x300000001)
- `0x55ff21c  mov [rbp+0x1EF4],ax`                   (+0x00 = u16 from [rbp+0x2784])
- `0x55ff223  mov [rbp+0x1EF6],cx`                   (+0x02 = u16 from [rbp+0x2786])
- `0x55ff22a  mov dword ptr [rbp+0x1EF8],0x1A`       (+0x04 = u32 0x1A)

## Answer

The 28-byte descriptor has no field that separates input from output resources. Both resource/param halves are copied opaquely by the declaration helper (two movups reads covering all of +0x00..+0x1B), the builder sets only size/format/flag-like values, and sub_567a7b0 stores the descriptor record pointer and a count without inspecting fields. The five binder types from 6aq exist in the dependency vocabulary but are not encoded as read/write direction anywhere in this struct or its declaration flow.

CLOSES? NO — the single blocking fact: nothing in builder 0x55f1450 or its pass-declaration callees separates input from output resources statically; the 28-byte descriptor is copied opaquely (`0x56982dc  movups xmm0,[rbx]` and `0x56982df  movups xmm1,[rbx+0xC]` cover all of +0x00..+0x1B) and no instruction or string tags either resource field as input or output, so per-pass in/out cannot be assigned from this item alone.

## TOOL REQUESTS
- None
