## NEXT
DONE - L12d skin-shadow-blob decoded inside nametag producer 0x11276b0; table + CLOSES? written

# Unit U-EL12d — L12d nametags (0x1127330/0x11276b0): skin shadows blob (pending part)

Goal: close L12d "nametags (0x1127330/0x11276b0) — 6l, 6m (decoded); skin shadows blob pending".
The nametag part (clone 0x1127330, caller 0x11276b0, description 0x98 built by 0x668b6e0, Item tag 1) is decoded per BGFX_MAP 6l/6m and is NOT re-decoded here. Only the pending part is done: the skin-shadow-blob production inside 0x11276b0.

0x11276b0 (size 0x2000; exactly one xref in, from 0x539e3b0 which walks actor records with stride 0x90) is the per-actor nametag producer. Per actor record [rbx] (name [rbx+0x10], desc [rbx+0x20], position [rbx+0x50..0x5C], flags [rbx+0x60]/[rbx+0x70]/[rbx+0x88]) it (a) inserts the nametag via clone 0x1127330 (two call sites, flag-selected) and (b) — the pending part — builds a camera-facing billboard mat4 with distance-attenuation fade and inserts it via MeshFallback clone 0x4DEF480 (two call sites, each preceded by memset 0x148 of [rbp+0x48]). That billboard insert is the skin-shadow-blob: a per-actor blob shadow (camera-facing billboard, alpha fading with distance via a polynomial). Mechanism below is [V]; the "skin shadow" semantic label is [I] (no shadow/blob string is referenced from 0x11276b0 — xref str "shadow" and "blob" show no xref into 0x1127xxx; cf. BGFX_MAP M1d "blob shadows drawn through MeshFallback" [I]).

Answer: the skin-shadow-blob is the per-actor camera-facing billboard mat4 with distance-attenuation fade, inserted via MeshFallback clone 0x4DEF480 at 0x11288d5 and 0x1128945 inside nametag producer 0x11276b0, alongside the nametag insert at 0x1127e8e/0x1127efa.

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|--------|------|------|------------------------------------|---------|-------------|
| [rbx+0x10] | 8B | [rbx+0x10] | `0x1127850  mov rax,[rbx+0x10]` | per-actor record name pointer; name copied to stack buffer [rbp+0x18] (max 10 chars, sub_3e8fb0 r8b=0xA at 0x112787a) | [V] |
| [rbx+0x20] | 8B | [rbx+0x20] | `0x1127b18  cmp qword ptr [rbx+0x20],0` | nametag description pointer; zero skips the nametag+shadow insert path; passed as r8 to MeshFallback clone | [V] |
| [rbx+0x50] | 4B | [rbx+0x50] | `0x11278ca  subss xmm0,[rbx+0x50]` | actor position X, camera-relative vector component | [V] |
| [rbx+0x54] | 8B | [rbx+0x54] | `0x11278fb  movsd xmm1,[rbx+0x54]` | actor position component | [V] |
| [rbx+0x58] | 4B | [rbx+0x58] | `0x1127ba5  movss xmm1,[rbx+0x58]` | actor height/Y used in camera-relative offset | [V] |
| [rbx+0x5C] | 4B | [rbx+0x5C] | `0x1127861  movss xmm11,[rbx+0x5C]` | blob scale base (multiplied by [0xF0922D0]) | [V] |
| [rbx+0x60] | 4B | [rbx+0x60] | `0x1127e03  cmp dword ptr [rbx+0x60],0` | shared/count field; gates nametag and shadow paths | [V] |
| [rbx+0x70] | 1B | [rbx+0x70] | `0x1127dee  movzx eax,byte ptr [rbx+0x70]` | path selector flag: 0 -> nametag+shadow, 1 -> scaled nametag only, >=2 -> error path 0x1128A2A | [V] |
| [rbx+0x88] | 4B | [rbx+0x88] | `0x1127a72  mov eax,[rbx+0x88]` | byte flag selecting shadow-scale variant (test al,al at 0x1127ad3) | [V] |
| [0xF0CD500] | 4B | [0xF0CD500] | `0x11279ab  movss xmm0,[0xF0CD500]` | distance-attenuation polynomial term (fade with distance) | [V] |
| [0xF0CD504] | 4B | [0xF0CD504] | `0x11279c2  movss xmm2,[0xF0CD504]` | distance-attenuation term | [V] |
| [0xEF3F018] | 4B | [0xEF3F018] | `0x11279d2  movss xmm5,[0xEF3F018]` | distance-attenuation term | [V] |
| [0xEF3F050] | 16B | [0xEF3F050] | `0x11279f6  movaps xmm10,[0xEF3F050]` | sign-flip mask for fade (also 0x1127e42, 0x1127eaa, 0x1128363) | [V] |
| [0xEEE7C00] | 4B | [0xEEE7C00] | `0x1127a33  movss xmm0,[0xEEE7C00]` | distance-attenuation term | [V] |
| [0xEEC8060] | 4B | [0xEEC8060] | `0x1127c1c  movss xmm2,[0xEEC8060]` | distance-attenuation clamp term (also 0x1128061, 0x11283ae) | [V] |
| [0xF0922D0] | 4B | [0xF0922D0] | `0x1127b06  mulss xmm11,[0xF0922D0]` | blob scale multiplier | [V] |
| [0xEF40D2C] | 4B | [0xEF40D2C] | `0x1127b0f  mulss xmm12,[0xEF40D2C]` | name-length vertical offset multiplier | [V] |
| [rbp+0x1E0..0x20C] | 4B | [rbp+0x1E0] | `0x1127c7e  movss [rbp+0x1E0],xmm5` ; `0x1127c86  movss [rbp+0x1E4],xmm15` ; `0x1127ca4  movss [rbp+0x1E8],xmm13` ; `0x1127cc7  movss [rbp+0x1F8],xmm13` ; `0x1127cde  movss [rbp+0x200],xmm5` ; `0x1127cea  movss [rbp+0x204],xmm1` ; `0x1127cf6  movss [rbp+0x208],xmm2` | 15-float billboard block (shadow transform) built at [rbp+0x1E0..0x20C] | [V] |
| [rbp+0x20C] | 16B | [rbp+0x20C] | `0x1127d01  movups [rbp+0x20C],xmm0` | billboard block padding (w component zeroed) | [V] |
| [rbp+0x21C] | 4B | [rbp+0x21C] | `0x1127d08  mov dword ptr [rbp+0x21C],0x3F800000` | billboard block padding = 1.0 | [V] |
| [rbp+0x1EC] | 4B | [rbp+0x1EC] | `0x1127c2b  mov dword ptr [rbp+0x1EC],0` | billboard block field zeroed | [V] |
| [rbp+0x1F0] | 8B | [rbp+0x1F0] | `0x1127cad  movlps [rbp+0x1F0],xmm14` | billboard block field | [V] |
| [rbp+0x1FC] | 4B | [rbp+0x1FC] | `0x1127cd0  mov dword ptr [rbp+0x1FC],0` | billboard block field zeroed | [V] |
| [rbp+0x48..0x84] -> ring entry [r12+0x00..0x3C] | 4B | [r12+0x00] | `0x1127d2e  movss [r12],xmm0` ; `0x1127d39  movss [r12+4],xmm0` ; `0x1127d45  movss [r12+8],xmm0` ; `0x1127d51  movss [r12+0xC],xmm0` ; `0x1127d5d  movss [r12+0x10],xmm0` ; `0x1127d69  movss [r12+0x14],xmm0` ; `0x1127d75  movss [r12+0x18],xmm0` ; `0x1127d81  movss [r12+0x1C],xmm0` ; `0x1127d8d  movss [r12+0x20],xmm0` ; `0x1127d99  movss [r12+0x24],xmm0` ; `0x1127da5  movss [r12+0x28],xmm0` ; `0x1127db1  movss [r12+0x2C],xmm0` ; `0x1127dbd  movss [r12+0x30],xmm0` ; `0x1127dc9  movss [r12+0x34],xmm0` ; `0x1127dd8  movss [r12+0x38],xmm0` ; `0x1127de7  movss [r12+0x3C],xmm0` | per-actor camera-facing billboard mat4 (16 floats, from [rbp+0x48..0x84] via sub_aa6580) stored into the ring entry — the shadow transform | [V] |
| sub_aa6580 call | - | - | `0x1127d23  call 0xAA6580` ; `0x112829f  call 0xAA6580` | builds final billboard mat4 from ring entry + 15-float block | [V] |
| nametag clone calls (context, 6l/6m already decoded) | - | - | `0x1127e8e  call 0x1127330` ; `0x1127efa  call 0x1127330` | insert<RenderNametagDescription> per actor, flag-selected | [V] |
| memset 0x148 of shadow block | - | [rbp+0x48] | `0x11288b0  call 0xEEC6ED0` ; `0x112891d  call 0xEEC6ED0` | zeroes 0x148-byte block at [rbp+0x48] before each MeshFallback insert (r8d=0x148 at 0x11288a8/0x1128912) | [V] |
| MeshFallback clone insert calls | - | - | `0x11288d5  call 0x4DEF480` ; `0x1128945  call 0x4DEF480` | per-actor insert via MeshFallback clone 0x4DEF480 (Item tag 2, fat 0x714 — identity [I per BGFX_MAP 6g/6w]; clone family confirmed [V] by shared 0x4DEF080 validation call at 0x4DEF4C0); args rcx (=[rbx+0x60] call#1 / [rbp+0x340] call#2), rdx=[r13+0x10], r8=[rbx+0x20], r9=&[rbp+0x48] | the skin-shadow-blob insert [V mechanism / I semantic] |
| clone return tag | 1B | [rbp+0x1D8] | `0x11288db  movzx eax,byte ptr [rbp+0x1D8]` ; `0x112894b  movzx eax,byte ptr [rbp+0x1D8]` | clone return tag (0..3) switched via jump table | [V] |
| jump table 0xF0DF06C | 16B | 0xF0DF06C | `0x11288ec  lea rcx,[0xF0DF06C]` | decoded via jt.py: tag0 -> 0x1127f00 (done), tag1 -> 0x11289b6 (call 0x4DFB470([rbp+0x1C0])), tag2/3 -> 0x112896c (release [rbp+0x1D0]) | [V] |
| jump table 0xF0DF07C | 16B | 0xF0DF07C | `0x112895c  lea rcx,[0xF0DF07C]` | same targets as 0xF0DF06C | [V] |
| tag2/3 release | 8B | [rbp+0x1D0] | `0x112896c  mov r15,[rbp+0x1D0]` ; `0x1128990  call qword ptr [0xF99FFA0]` ; `0x11289ab  call qword ptr [0xF99FFA0]` | frees clone-returned shared object | [V] |
| tag1 handler | - | - | `0x11289bd  call 0x4DFB470` | rcx=[rbp+0x1C0] | [V] |
| actor-record stride (caller context) | - | - | `0x539e404  add r15,0x90` | caller 0x539e3b0 iterates actor records stride 0x90, invoking 0x11276b0 per actor | [V] |

## Verification proof lines (one per line, for rdis cross-check)

0x1127850  mov rax,[rbx+0x10]
0x1127b18  cmp qword ptr [rbx+0x20],0
0x11278ca  subss xmm0,[rbx+0x50]
0x1127bb8  addss xmm0,[rbx+0x50]
0x1128013  addss xmm0,[rbx+0x50]
0x11278fb  movsd xmm1,[rbx+0x54]
0x1128028  movsd xmm0,[rbx+0x54]
0x1127ba5  movss xmm1,[rbx+0x58]
0x1127fb1  movss xmm1,[rbx+0x58]
0x1127861  movss xmm11,[rbx+0x5C]
0x1127b06  mulss xmm11,[0xF0922D0]
0x1127e03  cmp dword ptr [rbx+0x60],0
0x1127dee  movzx eax,byte ptr [rbx+0x70]
0x1127a72  mov eax,[rbx+0x88]
0x11279ab  movss xmm0,[0xF0CD500]
0x11279c2  movss xmm2,[0xF0CD504]
0x11279d2  movss xmm5,[0xEF3F018]
0x11279f6  movaps xmm10,[0xEF3F050]
0x1127a33  movss xmm0,[0xEEE7C00]
0x1127c1c  movss xmm2,[0xEEC8060]
0x1128061  movss xmm12,[0xEEC8060]
0x11283ae  movss xmm6,[0xEEC8060]
0x1127b0f  mulss xmm12,[0xEF40D2C]
0x1127c7e  movss [rbp+0x1E0],xmm5
0x1127c86  movss [rbp+0x1E4],xmm15
0x1127ca4  movss [rbp+0x1E8],xmm13
0x1127cc7  movss [rbp+0x1F8],xmm13
0x1127cde  movss [rbp+0x200],xmm5
0x1127cea  movss [rbp+0x204],xmm1
0x1127cf6  movss [rbp+0x208],xmm2
0x1127d01  movups [rbp+0x20C],xmm0
0x1127d08  mov dword ptr [rbp+0x21C],0x3F800000
0x1127c2b  mov dword ptr [rbp+0x1EC],0
0x1127cad  movlps [rbp+0x1F0],xmm14
0x1127cd0  mov dword ptr [rbp+0x1FC],0
0x1127d2e  movss [r12],xmm0
0x1127d39  movss [r12+4],xmm0
0x1127d45  movss [r12+8],xmm0
0x1127d51  movss [r12+0xC],xmm0
0x1127d5d  movss [r12+0x10],xmm0
0x1127d69  movss [r12+0x14],xmm0
0x1127d75  movss [r12+0x18],xmm0
0x1127d81  movss [r12+0x1C],xmm0
0x1127d8d  movss [r12+0x20],xmm0
0x1127d99  movss [r12+0x24],xmm0
0x1127da5  movss [r12+0x28],xmm0
0x1127db1  movss [r12+0x2C],xmm0
0x1127dbd  movss [r12+0x30],xmm0
0x1127dc9  movss [r12+0x34],xmm0
0x1127dd8  movss [r12+0x38],xmm0
0x1127de7  movss [r12+0x3C],xmm0
0x1127d23  call 0xAA6580
0x112829f  call 0xAA6580
0x1127e8e  call 0x1127330
0x1127efa  call 0x1127330
0x11288b0  call 0xEEC6ED0
0x112891d  call 0xEEC6ED0
0x11288d5  call 0x4DEF480
0x1128945  call 0x4DEF480
0x11288db  movzx eax,byte ptr [rbp+0x1D8]
0x112894b  movzx eax,byte ptr [rbp+0x1D8]
0x11288ec  lea rcx,[0xF0DF06C]
0x112895c  lea rcx,[0xF0DF07C]
0x112896c  mov r15,[rbp+0x1D0]
0x1128990  call qword ptr [0xF99FFA0]
0x11289ab  call qword ptr [0xF99FFA0]
0x11289bd  call 0x4DFB470
0x539e404  add r15,0x90

CLOSES? YES — the pending skin-shadows-blob part of L12d is proven by [V] rows: per-actor camera-facing billboard mat4 ([rbp+0x48..0x84] -> ring entry [r12], 16x movss [V]) with distance-attenuation fade (constants [0xF0CD500], [0xF0CD504], [0xEF3F018], [0xEF3F050], [0xEEE7C00], [0xEEC8060] [V]) inserted via MeshFallback clone 0x4DEF480 at 0x11288d5 and 0x1128945, each after memset 0x148 of [rbp+0x48] via call 0xEEC6ED0 (0x11288b0/0x112891d [V]), args rdx=[r13+0x10], r8=[rbx+0x20], r9=&[rbp+0x48] [V], return tag switched via jt 0xF0DF06C/0xF0DF07C (decoded [V]). What remains [I] only: the "skin shadow" semantic label (no shadow/blob string referenced from 0x11276b0; cf. BGFX_MAP M1d "blob shadows drawn through MeshFallback" [I]) and the MeshFallback-clone identity of 0x4DEF480 (BGFX_MAP 6g/6w [I]). No blocking fact remains.

Open:
[UNVERIFIED: 0x11288ca rdx=[r13+0x10] argument passed to MeshFallback clone 0x4DEF480 — name pointer or object pointer, not shown by any instruction]
[UNVERIFIED: 0x539e3b0 — caller of 0x11276b0; its enclosing function/identity not identified (0 xrefs in to sub_539e3b0)]

## NEXT
DONE - L12d skin-shadow-blob decoded inside nametag producer 0x11276b0; table + CLOSES? written

## TOOL REQUESTS

None
