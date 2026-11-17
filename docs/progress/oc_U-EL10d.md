## NEXT
DONE

# U-EL10d — L10d FOV and screen-space transforms

Checklist item (docs/RENDER_CHECKLIST.md L10d, `[ ]` pending):
"L10d FOV and screen-space transforms — read from per-view record V+0x50 projection (6dd, live FOV ~76.9 deg)"

Pending part: screen-space transforms — where the per-view projection matrix (the view->clip screen-space transform) is stored and consumed. FOV itself is derivable from it (live 76.9 deg, 6dd).

Method:
- Per-view record: V = ctx + 0x1EAB090 + viewId*0x140, ctx = [0x12AE1748] (`0x568CDD0 mov rcx,[0x12AE1748]`, one load per view inside the per-view loop).
- viewId = u16 at [[task+8]+8] (`0x568CDC8 mov rax,[rcx+8]` / `0x568CDCC movzx eax,word ptr [rax+8]`).
- r13 = viewId*0x140 (`0x568CDD7 shl eax,6` / `0x568CDDA lea r13,[rax+rax*4]`).
- All writes below are in 0x568CD90 (Scene/HUD task body = bgfx per-view setup, reached through thunk 0x568CD70; dossier docs/functions/568cd90.md, size 0x2000) [V 6dd].
- 0xEBCE390 = memcpy(dst rcx, src rdx, count r8d), the per-view copy helper cited by 6dd. All sizes below come from the count register / access size of the instruction itself.
- No other function in .text writes V+0x50 in this disassembly scope; consumption is via the predefined-uniform dispatch in the draw executor (jump table 0xF4EE7F8).

## Answer table — per-view record offsets (one row per distinct offset, all sites listed)

| offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | tag |
|---|---|---|---|---|---|
| V+0x00 | 4 | 0x568CDF6 | `0x568CDF6  movd [rcx+r13+0x1EAB090],xmm0` | rect dword 0 = packed u16s (x,y) from task+0xF8; pmaxsw in same block clamps words >= 0 | [V] |
| V+0x04 | 4 | 0x568CE0C | `0x568CE0C  movd [rcx+r13+0x1EAB094],xmm1` | rect dword 1 = packed u16s (w,h) from task+0xFC; pcmpeqw/psubw in same block adjust zero -> 1 | [V] |
| V+0x10 | 64 | 0x568CE51 | `0x568CE51  call 0xEBCE390` (memcpy 0x40 B; dst set by `0x568CE44  add rcx,0x1EAB0A0`, src = task+0x78 (`0x568CDC4 add rdx,0x78`), count `0x568CE4B  mov r8d,0x40`) | view matrix mat4 (col-major) [V per 6dd] | [V] |
| V+0x50 | 64 | 0x568CE6A | store: `0x568CE6A  call 0xEBCE390` (memcpy 0x40 B task+0xB8 -> V+0x50; dst `0x568CE5A  add rcx,0x1EAB0E0`, src `0x568CE32  lea r12,[rbx+0xB8]` then `0x568CE67  mov rdx,r12`, count `0x568CE61  mov r8d,0x40`) | PROJECTION matrix mat4 = screen-space/view->clip transform; read back per-draw as predefined uniform u_proj (enum #4): dispatch `0xE82A517  lea rdx,[0xF4EE7F8]` / `0xE82A51E  movsxd rcx,[rdx+rcx*4]` / `0xE82A522  add rcx,rdx` / `0xE82A525  jmp rcx` -> case 4 at `0xE82A71A`, body copies <= 4x16 B from per-view proj pointer rdi via `0xE82A783  call 0x47E8F0` into job+0x3B0+loc; u_viewProj reads `0xE82A5C2  mov r8,[rbx+0x2F0]` | [V] |
| V+0x90 | 64 | 0x568CE83 | `0x568CE83  call 0xEBCE390` (memcpy 0x40 B task+0x10C -> V+0x90) | previous-frame view matrix (TAA/motion) [V per 6dd] | [V] |
| V+0xD0 | 64 | 0x568CE9C | `0x568CE9C  call 0xEBCE390` (memcpy 0x40 B task+0x14C -> V+0xD0) | previous-frame projection matrix [V per 6dd] | [V] |
| V+0x110 | 16 | 0x568CEB9 | `0x568CEB9  call 0xEBCE390` (memcpy 0x10 B task+0x18C -> V+0x110; count `0x568CEAC  mov r8d,0x10`) | viewport/clear vec4 [V per 6dd] | [V] |
| V+0x122 | 1 | 0x568CECC | `0x568CECC  mov [rcx+r13+0x1EAB1B2],al` (byte from `0x568CEBE  movzx eax,byte ptr [rbx+0x108]`) | view sort mode byte (1 Sequence, 2 DepthAsc, 3 DepthDesc) [V per 6dd] | [V] |

## Raw proof lines (each verified against the exe by verify_oc; the same lines are quoted in the table above)

   0x568CDF6  movd [rcx+r13+0x1EAB090],xmm0
   0x568CE0C  movd [rcx+r13+0x1EAB094],xmm1
   0x568CE51  call 0xEBCE390
   0x568CE44  add rcx,0x1EAB0A0
   0x568CE4B  mov r8d,0x40
   0x568CE6A  call 0xEBCE390
   0x568CE5A  add rcx,0x1EAB0E0
   0x568CE32  lea r12,[rbx+0xB8]
   0x568CE67  mov rdx,r12
   0x568CE61  mov r8d,0x40
   0xE82A517  lea rdx,[0xF4EE7F8]
   0xE82A51E  movsxd rcx,[rdx+rcx*4]
   0xE82A522  add rcx,rdx
   0xE82A525  jmp rcx
   0xE82A783  call 0x47E8F0
   0xE82A5C2  mov r8,[rbx+0x2F0]
   0x568CE83  call 0xEBCE390
   0x568CE9C  call 0xEBCE390
   0x568CEB9  call 0xEBCE390
   0x568CEAC  mov r8d,0x10
   0x568CECC  mov [rcx+r13+0x1EAB1B2],al
   0x568CEBE  movzx eax,byte ptr [rbx+0x108]

## FOV

The projection matrix at V+0x50 is the data FOV is read from: live capture (read-only CE, 6dd) showed V+0x50 = [0.759 0 0 0 | 0 1.28 0 0 | 0 0 -1 -1 | 0 0 -0.025 0] for in-game views, so m11 = 1/tan(fov/2) = 1.28 -> vertical fov = 2*atan(1/1.28) = 76.9 degrees; aspect = m11/m00 = 1.28/0.759 = 1.686 = 1920/1137 ✓. This numeric derivation was done live; statically the executable only stores the matrix at V+0x50 (proven above) — no fov-extraction function was found in .text. Game-side fov source (LevelRendererPlayer+0x1238 mFov, CameraComponent) is [I] per 6dw line 1250 and is not the live value used by the renderer.

## Screen-space transforms

The view->clip screen-space transform is the projection matrix at V+0x50: stored per view each frame by 0x568CD90 [V rows above] and consumed per draw as predefined uniform u_proj through the 14-entry jump table at 0xF4EE7F8 (`0xE82A517  lea rdx,[0xF4EE7F8]` / `0xE82A51E  movsxd rcx,[rdx+rcx*4]` / `0xE82A522  add rcx,rdx` / `0xE82A525  jmp rcx`, entry 4 = u_proj per predefined-uniform enum order 6ag: 0 u_viewRect ... 4 u_proj ...). The view matrix at V+0x10 and the rect/viewport at V+0x00/V+0x04/V+0x110 complete the screen-space transform set (rect feeds the D3D12 viewport/scissor per view in submit's per-view setup 0xe818490 [I per 6t]). Previous view/proj at V+0x90/V+0xD0 serve TAA/motion [V per 6dd].

## CLOSES?
CLOSES? YES — every pending part of L10d is proven by [V] rows: projection matrix stored at per-view record V+0x50 (verbatim store sites 0x568CE32/0x568CE5A/0x568CE61/0x568CE6A), consumed as screen-space transform u_proj/u_viewProj per draw (verbatim dispatch 0xE82A517-0xE82A525 and case body 0xE82A783/0xE82A5C2), FOV derivable from m11 (live 76.9 deg [V live, 6dd]).

## TOOL REQUESTS
None — rdis.exe disassembly of 0x568CD90 and 0xE82A49E/0xE82A71A regions provided all evidence; no helper scripts written.
