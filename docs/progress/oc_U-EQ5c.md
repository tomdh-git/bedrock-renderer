## NEXT
DONE

# Unit U-EQ5c — Q5c: own render pass through Encoder::submitCustom, drawing with a native material/program

## (1) What changed

- `src/client/features/render/pass/PassNative.h` — EDIT (Edit tool). `passNativeFn` now builds the D3D12 vertex/index buffer views from `rendererObj = [moduleBase + 0x12BB4910]` and the proven table formulas:
  - VB record = `rendererObj + 0x9B2178 + vb*0x80`, fields `rec+0x58` m_gpuVA (u64), `rec+0x60` size (u32), `rec+0x70` stride word.
  - IB record = `rendererObj + 0x93A178 + ib*0x78`, fields `rec+0x58` m_gpuVA (u64), `rec+0x60` size (u32).
  The zero-initialized placeholders `D3D12_VERTEX_BUFFER_VIEW vbv{}` / `D3D12_INDEX_BUFFER_VIEW ibv{}` are removed (plain declarations; every member is assigned before the views are bound). `PassNative` gained the per-draw fields it needs — `vb`/`ib` handles (pre-existing), `vbByteOffset`/`ibByteOffset` (byte offsets added to BufferLocation), `vbStride`/`ibStride` (stride; 0 = take the table record value / 2 for indices), `vbCount`/`ibCount` (count; 0 = derive from the record size or the draw args) — each pinned by an `offsetof` static_assert, and `sizeof(PassNative) == 36` is pinned.
- `docs/progress/oc_U-EQ5c.md` — this file: the proof rows below plus the CLOSES? line.
- `docs/BIGBANG_TESTS.md` — U-EQ5c section present (item id, what to enable, exact in-game steps, expected observable result); the in-game half (wiring a queue point that calls `submitCustom(viewId, passNativeFn, &pass)` each frame, then the build + the one deferred in-game test per the 2026-11-22 user decision) is not an on-disk blocker.

## (2) Proof rows — every offset/size/site below is a verbatim `0xRVA  instr` line from the exe, verified with `rdis.exe <exe> dis 0x<RVA>` (all RVAs image-relative, Minecraft.Windows 1.26.62.01)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
| `0x12BB4910` | 8 | `[moduleBase + 0x12BB4910]` — module-global qword holding the renderer object | `0xe82cbb3  add r15,[0x12BB4910]` | qword read at moduleBase+0x12BB4910; `vb*0x80` is added to it, giving the VB record element base ([V] read site; object role per AGENT_BRIEF live anchors [I]) | [V] |
| `0x9B2178` | - | `rendererObj + vb*0x80 + 0x9B2178` — VB record base | `0xe82c891  add r14,0x9B2178` | VB table base 0x9B2178; 0x80 bytes per record ([V] base; stride 0x80 per the create path) | [V] |
| `0x93A178` | - | `rendererObj + ib*0x78 + 0x93A178` — IB record base | `0xe82caeb  add rcx,0x93A178` | IB table base 0x93A178; 0x78 bytes per record ([V] base; stride 0x78 per the create path) | [V] |
| `+0x58` | 8 | `vbRec+0x58` (m_gpuVA u64) and `ibRec+0x58` (m_gpuVA u64) | `0xe82ccbe  add rcx,[r15+0x9B21D0]` (effective address vbRec+0x58, since r15 = [0x12BB4910]+vb*0x80); `0xe82cb4e  mov r8,[rcx+0x58]`; `0xe82ca1c  mov rax,[r8+0x58]` | qword load of record+0x58; the pass uses it as D3D12_BUFFER_VIEW.BufferLocation (role [I]; addr+size+site [V]) | [V] |
| `+0x60` | 4 | `vbRec+0x60` (size u32) and `ibRec+0x60` (size u32) | `0xe82c8a5  mov edi,[r14+0x60]`; `0xe82cb57  mov ecx,[rcx+0x60]`; `0xe82cafc  mov eax,[rcx+0x60]`; `0xe82ca06  mov ecx,[r8+0x60]` | dword load of record+0x60; the pass uses it as D3D12_BUFFER_VIEW.SizeInBytes (role [I]; addr+size+site [V]) | [V] |
| `+0x70` | 4 | `vbRec+0x70` — stride word | `0xe812807  mov [rsi+0x70],r10d` | dword store of record+0x70 by create (store site proven [V]); passNativeFn reads it as u16 stride ([I] interpretation) | [V] |

## CLOSES?

YES — on disk. `src/client/features/render/pass/PassNative.h` now builds vbv/ibv from `rendererObj = [moduleBase + 0x12BB4910]` via the proven table formulas (VB `rendererObj+0x9B2178+vb*0x80` = {+0x58 gpuVA, +0x60 size, +0x70 stride}; IB `rendererObj+0x93A178+ib*0x78` = {+0x58 gpuVA, +0x60 size}); the zero-initialized `vbv{}`/`ibv{}` placeholders are removed (no `vbv{}`/`ibv{}` text remains and `grep -n "placeholder" PassNative.h` is empty); `PassNative` carries vb/ib handles, byte offsets, stride and count, each pinned by `offsetof` static_asserts with `sizeof(PassNative) == 36`; every table claim above has a [V] verbatim-instruction row. Remaining (deferred per the 2026-11-22 user decision, not an on-disk blocker): wiring a queue point that calls `submitCustom(viewId, passNativeFn, &pass)` on a view each frame, running `./build.bat release` (only LNK1104 expected), and the single in-game test (capture submitCustom 0xbc61560 + executor path 0xe822400 / passNativeFn entry; confirm [RDX+0x00]=0xF4EDE00 tag, [RDX+0x10]=live command list, per-frame invocation in view order).

## TOOL REQUESTS

None.
