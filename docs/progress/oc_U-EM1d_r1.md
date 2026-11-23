## NEXT
DONE

# U-EM1d — M1d dossier verification: ItemInHand extractor 0x6698e30 pending ranges + extractor/clone/visitor status

## Summary

This unit verifies (instruction-level, [V]) the still-open ranges of the ItemInHand extractor `0x6698e30` (the one M1d extractor whose dossier exists but is not instruction-complete) and records the status of every other M1d sub-item (clones, visitors, extractors) so the M1d checklist line can be assessed.

Verified ranges (all from `Minecraft.Windows.exe` 1.26.62.01 via `rdis dis`, instruction lines match the exe):
- `0x669b4b9..0x669b510` — transform-packet prep + guard (`0x67d0b00` call, `0xe935700` alloc failure tail)
- `0x669c2a6..0x669c35f` — packet assembly start (vtable/fn ptr store, gate flag, shared_ptr inc, movups zeroing)
- `0x669c35f..0x669c44b` — gated optional block copies (SSO init, shared_ptr-like pairs with `lock inc`, movaps/movups field copies)
- `0x669c980..0x669c9e7` — submit call site (`call 0x67d14e0`, release temporaries via `0x675df40`, epilogue)
- `0x669be56..0x669becd` — D-tree leaves (flag latches, desc.d78 bit test, kind/mask set, desc+0x68/+0x6C copies)

## Verified field-access table (ItemInHand extractor 0x6698e30, pending ranges)

| offset | size | site | `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0x1a70 | 8 | 0x669b4b9 | `0x669b4b9  lea rcx,[rbp+0x1A70]` | transform-packet out ptr passed to `0x67d0b00` [V] |
| 0x1bb0 | 8 | 0x669b4c0, 0x669c9c8, 0x669c2ad | `0x669c9c8  mov [rbp+0x1BB0],rax` | vtable/fn ptr stored into packet block (3 sites) [V] |
| 0x1bf0 | 1 | 0x669b4cc, 0x669c2b4 | `0x669b4cc  cmp byte ptr [rbp+0x1BF0],1` | gate flag selecting packet branch path [V] |
| 0x1bb8 | 8 | 0x669c9ac, 0x669c9cf, 0x669c2c2, 0x669c2fe | `0x669c2fe  mov [rbp+0x1BB8],rdx` | geometry packet pair ptr (4 sites) [V] |
| 0x18c0 | 4 | 0x669c35f | `0x669c35f  mov eax,[rbp+0x18C0]` | staged scalar dword read into packet header [V] |
| 0x1bf8 | 4 | 0x669c365 | `0x669c365  mov [rbp+0x1BF8],eax` | staged dword stored to packet header [V] |
| 0x1c38 | 1 | 0x669c379, 0x669c3bb | `0x669c379  mov byte ptr [rbp+0x1C38],0` | validity flag for gated optional SSO block [V] |
| 0x1900 | 1 | 0x669c380 | `0x669c380  cmp byte ptr [rbp+0x1900],1` | gate: SSO/init block present (==1) [V] |
| r8+0x78 | 1 | 0x669be66 | `0x669be66  test byte ptr [r8+0x78],0x20` | desc.d78 flag bit 0x20 (Textured variant selector) [V] |
| r8+0x6c | 8 | 0x669beb2 | `0x669beb2  movsd xmm0,[r8+0x6C]` | desc+0x6C qword/vec2 copied via movsd (8B) [V] |
| r8+0x68 | 4 | 0x669beb8 | `0x669beb8  movss xmm1,[r8+0x68]` | desc+0x68 float copied via movss (4B) [V] |
| 0x1a00 | 4 | 0x669bec5 | `0x669bec5  movss [rbp+0x1A00],xmm1` | desc+0x68 float stored to local rbp+0x1a00 [V] |
| 0x1a0c | 1 | 0x669bebe | `0x669bebe  movzx eax,byte ptr [rbp+0x1A0C]` | local flag byte read to condition desc copy [V] |
| 0x1991 | 1 | 0x669be91, 0x669be9e | `0x669be91  cmp byte ptr [rbp+0x1991],0` | secondary-geometry gate latch [V] |

## Other M1d sub-item status (from existing on-disk dossiers, [V] = instruction-verified in those files)

- **21 thin insert clones** — DONE, one 0x139-byte template, docs/functions/insert_thin_clones.md [V] (6fu)
- **Fat clones**: Nametag 0x1127330 [V], PlayerVision 0x53e62b0 [V], Shadow 0x53e6c30 [V], MeshFallback 0x4def480 [V], Crack 0x539fff0 [V], Clouds 0x53e88a0 [V], Sky/Stars 0x5369b30 [V] (6fv-6ga, 6gb, 6fx-6fy)
- **Constructors**: Nametag 0x668b6e0 [V], MeshFallback 0x668b850 [V], Clouds 0x668e940 [V], SkinnedMesh 0x668d350 [V], EnvironmentalText/UIText [V], BlockSelectionOverlay 0x668d990 [V], Sky 0x668c910 [V] (6fv, 6fz, 6gb-6gf)
- **Item visitor dispatch** 0x6646980 — tag->handler table mapped, all 52 cases [V] (6gg-6gj)
- **Group insert wrappers + visitors** — all six groups mapped (6gh)
- **Extractors with dossiers**: ItemInHand 0x6698e30 (D1+, pending ranges above), BatchActor 0x66d9af0 (D1+, layouts live-verified), Clouds 0x67375a0 (structure only), Particle 0x67417f0 (structure only), Weather 0x6745440 (head only)
- **Extractors without dossiers**: chunk geometry, skinned mesh, nametag (no extractor RVA dossiers on disk)

## CLOSES?

NO — blocking fact: M1d requires dossiers for *every* extractor (chunk, batch actor, item-in-hand, skinned, nametag, particle, sky). On disk now: chunk/skinned/nametag extractors have no dossiers at all; particle/clouds/weather are structure/head-only; ItemInHand 0x6698e30 has verified instruction lines for its pending ranges (this unit) but is not instruction-complete (packet-copy byte semantics, shared_ptr bookkeeping 0x669bd5d..0x669c2a6, callee bodies 0x67d14e0/0x6693850/0x66a0f60/0x67d0750/0x66a17c0/0x67d0b00/0x56d55e0/0xbcaba00 not reversed). The verified [V] rows above cover 14 distinct offsets from the ItemInHand pending ranges.
