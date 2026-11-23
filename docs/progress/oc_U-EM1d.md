## NEXT
DONE

# oc_U-EM1d — M1d: sub_6648d13 shared variant-copy / registry-emplace (Item tag 7, skinned path)

## Identification [V]
- `rdis fn 0x6648d13` (shell, static, exe passed as argument): `sub_6648d13  [0x6648d13..0x664ad13)  size 0x2000  2 xrefs in`. rdis treats the shared tail as its own function; it is in fact a region inside Item visitor `sub_6646980` ([0x6646980..0x664fda5)), tag-7 entry 0x6646dc2 (jump table 0xF2BF2D0). Confirmed by the `fn` header line itself (verbatim from rdis output).
- One window covers it: `rdis dis 0x6648d13 3000` → 0x6648d13..0x664ad0f (last decoded instruction), then `(bad)` at 0x664ad0f; 4 bytes 0x664ad0f..0x664ad12 undecoded; region end per rdis = 0x664ad13 exclusive. No second window needed — the "0x2000 Sigs window" IS the whole region.
- Role (orchestrator hint, verified by disassembly): shared variant-copy + registry-emplace tail used by the skinned path; interleaved with the tails of cases 2/3/9. Copies the description's variant payload into a registry component block (header at [rbp+0x5A0], data at [rbp+0x5A0+..]), emplaces it into the entt registry via several emplace helpers, builds the draw-state block ([rbp+0x224..0x398]), resolves materials/pass-name hashes, and handles shared_ptr acquire/release.

## Entry state [I from disassembly]
- rdi = description pointer (variant payload). rbp = frame base (locals rbp+0x10..rbp+0x900). rbp+0x778 = variant index byte (0..3; >3 exits to 0x664B8C3). rbp+0x740/0x750/0x760 = saved 16-byte vector state. r14 = working destination pointer ([rbp+0x700] or &rbp+0x18). rbx/rsi hold description-related pointers per block.

## Jump tables [V] (int32-relative entries; target = table + disp, read from .rdata; verified by PE section mapping)
- 0xF2BF34C at 0x6648D7E on byte [rbp+0x778]: idx0->0x664B8BD, idx1->0x6648D8E, idx2->0x66495C4, idx3->0x66495D7
- 0xF2BF37C at 0x6649593: idx0->0x664CDEB, idx1->0x66495B1, idx2->0x664C2F5, idx3->0x664C307
- 0xF2BF38C at 0x6649D8D: idx0->0x664BF56, idx1->0x6649DAF, idx2->0x664BF49, idx3->0x664BF7D
- 0xF2BF32C at 0x664A8BC: idx0->0x664E33E, idx1->0x664A8DD, idx2->0x664C91E, idx3->0x664C93D
- 0xF2BF31C at 0x664AB35: idx0->0x664E39E, idx1->0x664AB5A, idx2->0x664C92E, idx3->0x664C95F
- 0xF2BF36C at 0x664A5E7: idx0->0x664C36D, idx1->0x664A606, idx2->0x664A616, idx3->0x664A628

## Callees [V] (direct calls seen in the listing; roles from the instruction operands)
- 0x66E75F0 mesh binding helper (rcx=rbx, rdx=[rbp+0x8A0], r8=&rbp+0x220) — same helper the ItemInHand extractor uses (6gh)
- 0x539DD40 small forwarder (rcx=&rbp+0x220), result chained into the shared_ptr reload at 0x6648DE1
- 0xE86B370 registry emplace (rcx=&out, rdx=[rax+0x170], r8=[rbx]) — called at 0x6648E19 and 0x66491CC/0x66492DB
- 0xBBD7C70 copy/construct 0x250-byte block (rcx=&rbp+0x220, rdx=0x250+[rbp+0x10], r8=0) at 0x6648E92
- 0x4DEDD00 MeshFallback-side helper (rcx=r15=[rdi+0xB0] element, rdx=&rbp+0x220) at 0x6648EA2
- 0xE869FF0 transform copy packet (rcx=&dst, rdx=r15/src) at 0x6649D1A, 0x664A7F4, 0x664AA4E
- 0x5679DB0 registry component set (rcx=&slot, rdx=&{u16 index, byte flag=1}, r8=&rbp+0x5A0) — ~9 calls
- 0xBBD7F70 registry emplace (rcx=&rbp+0x7C0/0x740, r8=&rbp+0x5A0 or &rbp+0x10, rdx=[rbp+0x8A0]) — 3 calls
- 0x66B2B30 entity registry emplace (shared with Nametag/Cracks handlers per 6u) — 3 calls
- 0xBCAC390 registry get/emplace by name (r8=string pointer [0x129F9368])
- 0xEEC6EC0 / 0xEEC6EB0 / 0xEEC6ED0 memcpy / set helpers
- 0x5AB9970 texture/render-target create
- 0xBBD46C0 registry emplace
- 0x66A0F60 mesh binding (rcx=&rbp+0x10, rdx=[rax], r9=&rbp+0x740, r8=[r13+0x3B8])
- 0xE93BF00 string ends-with compare ("fullscreen_cube_overlay", len 0x17)
- 0xE935700 free
- shared_ptr acquire/release dtor + allocator via [0xF99FFA0] = sub_eea6040 (CFG thunk)

## Data / constants [V]
- Table-scan comparands (qwords in .data, read vs entry+0x28, stride 0x10 or 0x30): 0x129F8310, 0x129F9338, 0x129F8320, 0x129F8328, 0x129F8330, 0x129F8348, 0x129F8350, 0x129F8318, 0x129F8388
- Telemetry counters (TLS-guarded reads): 0x129F9CD8, 0x129F9CE8, 0x129F9340, 0x129F9220, 0x129F9350, 0x129F9360, 0x129F9370, 0x129F9380
- 0x1233E1A8 = 0x15233DE18 (heap/allocator global); [0xF99FFA0] = sub_eea6040
- Strings: "fullscreen_cube_overlay" 0xF51E3D7 (len 0x17), "shaders/uv_selection_overlay.vertex" 0xF51FE2B, "MeshFallbackPosUVNormalColor" 0xF563B37 — all verified present at those RVAs in the file
- FNV-1 64 hashes compared against rsi: 0xC58E8376A835167E, 0xD8B3C5186B8CA065, 0x3372F51E15C9A9A, 0x1E171F0477EAD280, 0x1E171F0477EAD281, 0x2404F172C5EAB109, 0x66A1990A3561111B, 0xDB99DF931C70EBAB, 0xEB01AFA8A054432F
- Doubles: [0xEFD3400] = 1.0; floats: [0xEEC8060] = 1.0f; [0xF07C974] = (-5.0f,-5.0f) vec2; [0xF275E70] = 0x1C; [0xF5C6AE8] = "eCapture", [0xF5C6AD8] = "UIStruct" (8-byte chunks)

## Block map — reads / writes / calls / field offsets [V per instruction]
| block | range | entry | exits | reads / writes / calls / field offsets |
|---|---|---|---|---|
| G1 | 0x6648d13..0x6648d8c | region start | table 0xF2BF34C | write [rbp+0x6C8]=al (variant tag), write [rbp+0x6D0]=si; read [rbp+0x740/0x750/0x760] vector state; writes [rbp+0x748]=0, [rbp+0x6D8], [rbp+0x750]=0, [rbp+0x6E8], [rbp+0x6F8]=[rbp+0x760]; r14=&rbp+0x700; [rbp+0x710]=0xFF; read variant byte [rbp+0x778]; jump table 0xF2BF34C |
| G2 | 0x6648d8e..0x6648d9c | table idx1 | 0x664b8bd | read [rbp+0x768] → write [rbp+0x700] |
| G3 | 0x6648da1..0x6648ddc | (external jump target) | 0x664ebd7 | write [r14+8]=0; read [rdi+0x10] → write [r14+0x10]; write [rbp+0x2D0]=sil; call 0x66e75f0; call 0x539dd40 → rax |
| G4 | 0x6648de1..0x6648e5f | (external jump target) | loc_6648e5f | shared_ptr chain: read [rbp+0x220], [rax+0x18], [rax] → write [rbp+0x10]; r14=&rbp+0x18; read [rbx], [rax+0x170]; call 0xe86b370 (emplace #1); write [rbp+0x90]=rbx; shared_ptr release of [rbp+0x228] (lock dec [r15+8], dtor via [0xF99FFA0]=sub_eea6040, [r15+0xC]) |
| G5 | 0x6648e5f..0x6648eaf | loc_6648e5f | loc_6648eaf | read [rdi+0xB0]=r15; count=(([r15+0x60]-[r15+0x58])>>2)*0xAAAAAAAB low32; if 0 → loc_6648eaf; else call 0xbbd7c70 (0x250-byte copy, rdx=0x250+[rbp+0x10]); call 0x4dedd00 (rcx=r15, rdx=&rbp+0x220); r15=[rdi+0xB0] |
| G6 | 0x6648eaf..0x6648ec9 | loc_6648eaf | loc_6648ec9 | read [rdi+0xB8]=eax; r12d=0; if byte [r15+0x1D4]!=0: r12d=[r15+0x1D0] |
| G7 | 0x6648ec9..0x6648ee1 | loc_6648ec9 | loc_6648ee1 / 0x664cb91 | test eax; jle 0x664cb91; else eax/3 via imul 0xAAAAAAAB,shr 0x20, and ~1 → r12d; test r12d; je 0x664cb91 |
| G8 | 0x6648ee1..0x66490ec | loc_6648ee1 | 0x664cb91 / fallthrough | telemetry reads [0x129F9CD8],[0x129F9CE8] (TLS guard); default block init: writes 0x3F800000 (1.0f) to [rbp+0x220..0x40C] stride 0x14; movsd [rbp+0x25C/0x29C/0x2DC/0x31C/0x35C/0x39C]=[0xEFD3400]=1.0 double |
| G9 | 0x66490ec..0x664914f | fallthrough | 0x664ed47 / fallthrough | read [rdi+0xC0]==-1? → 0x664ed47; read [rdi+0xC8]; write [rbp+0x850]=[rax],[rbp+0x858]=[rcx]; if rcx==0 && rax==0 → 0x664ed47 (shared_ptr empty test); call 0x6698060 (rcx=&rbp+0x850, rdx=&rbp+0x220) copy; write [rbp+0x5A0]=8, [rbp+0x5A8]=&rbp+0x220 |
| G10 | 0x664914f..0x6649191 | fallthrough | 0x664ae25 / 0x664ae22 / 0x664ae68 | table scan #1: rax=[rbp+0x48], edx=word [rbp+0x52] (count), stride 0x10; r9=[0x129F8310]; read [r10+0x28] vs r9; found→0x664ae22, not found→0x664ae68 (dx=1), empty→0x664ae25 |
| G11 | 0x6649191..0x664921d | table #1 found | loc_664921d | shared_ptr reload chain ([rbp+0x220]→[rax+0x18]→[rax]→[rbp+0x10]); r8=[rsi], rdx=[rax+0x170]; call 0xe86b370 emplace #2; write [rbp+0x90]=rsi; shared_ptr release [rbp+0x228] |
| G12 | 0x664921d..0x6649281 | loc_664921d | 0x6649641 | telemetry [0x129F9340]; read [rdi+0x64] → write [rbp+0x220]; [rbp+0x5A0]=1, [rbp+0x5A8]=r14(&rbp+0x700); table scan #2: r9=[0x129F9338]; not found→jmp 0x6649641 |
| G13 | 0x6649281..0x664929d | scan #2 loop | loc_66495fb | read [r10+0x28] vs r9; found→loc_66495fb: r8+=rax |
| G14 | 0x664929d..0x6649321 | (external jump target) | loc_6649321 | shared_ptr reload; write [rbp+0x7C0]=[rax]; r14=&rbp+0x7C8; call 0xe86b370 emplace; write [rbp+0x840]=rbx; shared_ptr release [rbp+0x228] |
| G15 | 0x6649321..0x66493db | loc_6649321 | loc_66493db | telemetry [0x129F9220]; read [rdi+0x68] → [rbp+0x220]; [rbp+0x5A0]=1; table scan #3: r9=[0x129F9218] (qword), stride 0x10; index→[rbp+0x740]=cx, [rbp+0x742]=1; call 0x5679db0 |
| G16 | 0x66493db..0x664942b | loc_66493db | 0x664d484 / loc_664942b | byte [rbp+0x144]&=0xF7; read [rdi]=r9; call 0xbbd7f70 emplace (rcx=&rbp+0x740, r8=&rbp+0x7C0, rdx=[rbp+0x8A0]); if byte [rbp+0x798]==0 → 0x664d484 |
| G17 | 0x664942b..0x66495fe | loc_664942b | table 0xF2BF37C | draw-state block: read [rdi+0x50] ss→[rbp+0x228]; movups chain [rdi+0x8/0x18/0x28/0x38] → [rbp+0x1A0/0x1B0/0x1C0/0x1D0]; byte [rbp+0x1E0]=0; si=word [rdi+0x80]; sd [rdi+0x48]→[rbp+0x220]; movups copies to [rbp+0x238..0x268]; byte [rbp+0x278]=0; xmm [rbp+0x140/0x158/0x168/0x178/0x187] → [rbp+0x280..0x2C7]; read [rbp+0x7C0]→[rbp+0x2D8]; lea rdi=&rbp+0x2e0; call 0xe869ff0 transform copy; write [rbp+0x358]=[rbp+0x840], [rbp+0x840]=0, [rbp+0x360]=si; [rbp+0x748]=0; [rbp+0x368/0x378]=xmm0/xmm1; [rbp+0x388]=[rbp+0x760]; byte [rbp+0x3a0]=0xFF; read variant byte [rbp+0x778]; table 0xF2BF37C |
| G18 | 0x66495b1..0x66495bf | table 0xF2BF37C idx1 | 0x664cdeb | read [rbp+0x768] → write [rbp+0x390] |
| G19 | 0x66495c4..0x66495db | table 0xF2BF34C idx2 | 0x664b8bd | movups xmm0=[rbp+0x768] → write [r14] |
| G20 | 0x66495d7..0x66495ef | table 0xF2BF34C idx3 | 0x664b8a6/0x664b8a8 | movups [r14]=xmm0; read [rbp+0x770]=rcx; if rcx==0 → 0x664b8a6; else lock inc [rcx+8] (shared_ptr acquire); → 0x664b8a8 |
| G21 | 0x66495fe..0x6649641 | scan #2 found | loc_6649641 | r9=rax+rcx; if r8>=r9 → 0x6649641; else index=(r8d-eax)>>4 → write [rbp+0x7c0]=r8w, [rbp+0x7c2]=1; call 0x5679db0 (rcx=r15, rdx=&rbp+0x7c0, r8=&rbp+0x5a0) |
| G22 | 0x6649641..0x664975c | fallthrough / jmp target | table 0xF2BF37C-chain | read [rdi+0x8c] → [rbp+0x220]; [rbp+0x5a0]=1, [rbp+0x5a8]=r14; table scans #3..#6: r9=[0x129F8320] src [rdi+0x8c]; r9=[0x129F8328] src [rdi+0x9c]; r9=[0x129F8330] src [rdi+0xa4]; r9=[0x129F8348] src [rdi+0xb4]; each: stride-0x10 scan read [r10+0x28] vs r9; index→[rbp+0x7c0]=r8w, [rbp+0x7c2]=1; call 0x5679db0 |
| G23 | 0x664975c..0x664987a | (cont.) | (cont.) | same scan pattern for [rdi+0xb4] vs [0x129F8348] |
| G24 | 0x664987a..0x6649915 | fallthrough | loc_6649915 | read ss [rdi+0xcc]→[rbp+0x220], sd [rdi+0xc4]→[rbp+0x228]; [rbp+0x22c]=0; [rbp+0x5a0]=1, [rbp+0x5a8]=r14; scan #7: rdx=[0x129F8350] qword, stride 0x10, read [r10+0x28]; index→[rbp+0x7c0]; call 0x5679db0 |
| G25 | 0x6649915..0x6649963 | loc_6649915 | loc_6649963 | read [rdi+0x78]=rax, [rax+0x40]=rcx; flags: byte [rcx+0x1ad], [rcx+0x1ae], [rcx+0x1af] → al = 1\|4\|16\|0x40; ecx=byte [rcx+0x1ac]; test cl,0xfb; if 0: al|=0x40, cx=0x500 else ecx=0 |
| G26 | 0x6649963..0x6649a10 | loc_6649963 | loc_6649a10 | read rdx=[rbp+0x58]; r10d=word [rbp+0x62]; r8=r10*0x30; scan stride 0x30 vs r10=[0x129F8318] (read [rsi+0x28]); index: r9d-=edx, shr 4, imul 0xFFFFAAAB → write [rbp+0x5a0]=dx, [rbp+0x5a2]=1; write [rbp+0x220]=cx, [rbp+0x224]=0, [rbp+0x228]=0, [rbp+0x22c]=1, [rsp+0x20]=0; call 0xbcaba00 (rcx=&rbp+0x10, rdx=&rbp+0x5a0, r9=&rbp+0x220) component emplace |
| G27 | 0x6649a10..0x6649ac0 | loc_6649a10 | loc_6649ac0 | telemetry [0x129f9350]; read [rbx+0x3e0] → [rbp+0x220]; [rbp+0x5a0]=1, [rbp+0x5a8]=r14; table scan #8 vs r9=[0x129f9348]; index→call 0x5679db0 |
| G28 | 0x6649ac0..0x6649b83 | loc_6649ac0 | 0x664c2a1 / fallthrough | read byte [rdi+0x88]; if 0: xmm0=0 else xmm0=ss [0xeec8060]=1.0f; shufps broadcast → [rbp+0x220]; [rbp+0x5a0]=1, [rbp+0x5a8]=r14; table scan #9 vs r9=[0x129f9358]; call 0x5679db0; call 0xbbd7f70 emplace (rcx=&rbp+0x7c0, r8=&rbp+0x10, rdx=[rbp+0x8a0]) |
| G29 | 0x6649b83..0x6649c0f | loc_6649b83 | 0x664c2a1 / loc_6649bec / loc_6649bfa | if byte [rbp+0x818]==0 → 0x664c2a1; read byte [rdi+0x39]=r8d; call 0x66b2b30 emplace (rcx=&rbp+0x740, rdx=r12, r8=byte [rdi+0x39]); write [rbp+0x744]=0xF; if byte [rdi+0xe0]!=0: [rbp+0x754]=1, movups [rdi+0xd0]→[rbp+0x758]; write [rbp+0x768]=0xFFFFFFE0, [rbp+0x76c]=0 |
| G30 | 0x6649c0f..0x6649d20 | loc_6649c0f | 0x664f714 / fallthrough | read ss [rdi+0x58]→[rbp+0x5a0], sd [rdi+0x5c]→[rbp+0x5a4]; read [rdi+0x18],[rdi+0x1c],[rdi+0x20],[rdi+0x30],[rdi+0x40],[rdi+0x50] → [rbp+0x5a0..0x5d8]; byte [rbp+0x5e0]=0; if byte [rbp+0x818]==0 → 0x664f714; read word [rdi+0xe4]→si; [rbp+0x234]=[rbp+0x750]; movups [rbp+0x740]→[rbp+0x224]; al=[rcx=&rbp+0x768]→[rbp+0x238]; movups [rcx],[rcx+0x10],[rcx+0x1f] → [rbp+0x23c/0x25c/0x26b]; ss/sd → [rbp+0x27c/0x280/0x290/0x2a0/0x2b0/0x2c0]; byte [rbp+0x2c8]=0; read [rbp+0x10]→[rbp+0x2d0]; call 0xe869ff0 (rcx=&rbp+0x2d8, rdx=r15) |
| G31 | 0x6649d20..0x6649d97 | fallthrough | table 0xF2BF38C | [rbp+0x350]=[rbp+0x90], [rbp+0x90]=0, [rbp+0x358]=si; [rbp+0x360]=[rbp+0x7c0], [rbp+0x7c8]=0, [rbp+0x370]=[rbp+0x7d0]; [rbp+0x380]=[rbp+0x7e0]; byte [rbp+0x398]=0xFF; read variant byte [rbp+0x7f8]; table 0xF2BF38C |
| G32 | 0x6649daf..0x6649dbd | table 0xF2BF38C idx1 | 0x664bf56 | read [rbp+0x7e8] → write [rbp+0x388] |
| G33 | 0x6649dc2..0x6649dc8 | (external jump target) | 0x664abf5 | xor ecx,ecx; jmp 0x664abf5 |
| G34 | 0x6649dc9..0x6649ece | alternate region entry | loc_6649ece | r15+=8; r12+=r15; lea r8="fullscreen_cube_overlay" 0xF51E3D7, r9d=0x17; call 0xe93bf00 string ends-with (rcx=r15, rdx=r12); result → r12b; read [rbp+0x238] size checks vs 0x10/0x1000/0x20; read [rdi]=rax; byte [rax+0x39]=r8d; call 0x66b2b30 emplace (rcx=&rbp+0x740, rdx=r14) |
| G35 | 0x6649ece..0x6649f65 | loc_6649ece | 0x664f047 / fallthrough | [rbp+0x140]=0; test r14; js 0x664f047; if r14<0x10: ebx=0xF else rdx=r14\|0xF, ebx=max(0x16,rdx); rcx=[0x1233e1a8]=0x15233de18; rax=[rcx],[rax+8]; cmp rdx,0xFFF; if >=: r12=&rbx+0x28, call [0xF99FFA0] alloc (rdx=size), test rax → 0x664eda9; r12+=0x27, and ~0x1F, write [r12-8]=rax (aligned alloc with back-ptr) |
| G36 | 0x6649f65..0x6649ff6 | loc_6649f6c / loc_6649f65 | loc_6649ff6 | [rbp+0x140]=r12 (buffer); [rbp+0x150]=r14(size), [rbp+0x158]=rbx(cap); call 0xeec6ec0 memcpy (rcx=r12, rdx=r15(src), r8=r14); write byte [r12+r14]=0; [rbp+0x598]=1; rsi vs FNV constants (0x1E171F0477EAD280/.../0xEB01AFA8A054432F) → else [rbp+0x598]=0 |
| G37 | 0x6649ff6..0x664a0e4 | loc_6649ff6 | 0x664a086 / 0x664a09f | rax=[rbp+0x150]=size; r8d=min(size,0x23); lea rdx="shaders/uv_selection_overlay.vertex" 0xF51FE2B; sete bl; call 0xeec6eb0 → eax; r15b=eax&bl; read byte [rdi+0xdc]=al; rsi vs FNV 0x8E31F9DB7CE887B7 / 0x72BE7BFDEE2D2411; dl=[rbp+0x598]\|al\|cl\|r15b; draw-flag computation with [rbp+0x8a0]+0x70 → r9d |
| G38 | 0x664a0e4..0x664a27c | loc_664a0e4 | 0x664eb99 / loc_664a268 / loc_664a27c | call 0xbbd46c0 emplace (rcx=&rbp+0x5a0, r8=rdi); if byte [rbp+0x628]==1 → 0x664eb99; [rbp+0x1a0]=0; r14d=0; if byte [rdi+0xdc]==1: if byte [rdi+0x1a0]==3: [rbp+0x7b8/0x7bc]=0 else [rbp+0x7bc]=[rdi+0x188], [rbp+0x7b8]=[rdi+0x18c]; r14=[rbp+0x8a0]+0x48; alloc 0x30 via [0xF99FFA0]; write [r15+0x10]="eCapture", [r15]="UIStruct", byte [r15+0x20]=0; [rbp+0x220]=[rbp+0x7bc], [rbp+0x224]=[rbp+0x7b8], [rbp+0x228]=[0xF275E70]=0x1C; [rbp+0x238]=r15, [rbp+0x240]=0, [rbp+0x248]=0x20, [rbp+0x250]=0x2F; call 0x5ab9970 texture create (rcx=r14, rdx=&rbp+0x220, r8=&rbp+0x10); refcount/free path (0xe935700); [rbp+0x87f]=r15b |
| G39 | 0x664a27c..0x664a31b | loc_664a27c | loc_664a31b | write [rbp+0x87f]=r15b; read ss [rdi+0x134] broadcast → [rbp+0x220]; [rbp+0x10]=1, [rbp+0x18]=&rbp+0x220; read [rbp+0x5d8]=rax, r8d=word [rbp+0x5e2]; table scan vs r9=[0x129f8388] stride 0x10 read [r10+0x28]; index→call 0x5679db0 (rcx=&rbp+0x5a8, rdx=&rbp+0x7c0, r8=&rbp+0x10) |
| G40 | 0x664a31b..0x664a549 | loc_664a31b | 0x664a375 / 0x664a381 / loc_664a3ad / loc_664a549 | bl|=r13b; [rbp-0x1c]=ebx; if bl!=1 → 0x664a375 ([rbp+0x744]&=0xF7, jmp 0x664a549); telemetry [0x129f9370]; rcx=[rbp+0x898]; read [rcx+0x430]; if 0 or byte[rax]!=1 → 0x664a381; else read [rcx+0x440]=rax; rbx=0xC0+[rax+0x18]; shared_ptr acquire [rax+8]; xmm0=[rbx]→[rbp+0x220]; call 0xbcac390 (rcx=&rbp+0x5a0, rdx=&rbp+0x10, r8=[0x129f9368] name, r9=&rbp+0x220); release shared_ptr [rbp+0x228]; telemetry [0x129f9380]; read [rbx+0x3e0]→[rbp+0x220]; [rbp+0x10]=1, [rbp+0x18]=r15; table scan vs [0x129f9378]; index→call 0x5679db0; write [rbp+0x744]=0xF |
| G41 | 0x664a549..0x664a69b | loc_664a549 | 0x664eb5b / loc_664a592 / loc_664a69b | call 0xbbd7f70 emplace (rcx=&rbp+0x7c0, r8=&rbp+0x5a0, rdx=[rbp+0x8a0]); if byte [rbp+0x818]!=1 → 0x664eb5b; if byte [rdi+0x164]==1: [rbp+0x754]=1, movups [rdi+0x154]→[rbp+0x758]; else → loc_664a592; rcx=&rbp+0x220, r8d=0x358, edx=0; call 0xeec6ed0 set 0x358 bytes; [rbp+0x10]=[rbp+0x7c0], [rbp+0x20]=[rbp+0x7d0], [rbp+0x7c8]=0; [rbp+0x30]=[rbp+0x7e0]; byte [rbp+0x48]=0xff; read variant byte [rbp+0x7f8]; table 0xF2BF36C: idx0→0x664c36d; idx1: [rbp+0x38]=[rbp+0x7e8] → 0x664c36d; idx2: movups [rbp+0x7e8]→[rbp+0x38] → 0x664c36d; idx3: read [rbp+0x7f0]=rcx; if 0 → 0x664c35c else lock inc [rcx+8] → 0x664c35e; fallback: read [rax+0x1b0]→[rbp+0x740]; r15=[rbp+0x748], [rbp+0x748]=rcx; shared_ptr release r15 → loc_664a69b |
| G42 | 0x664a69b..0x664a8ed | loc_664a69b | loc_664a8ed | call 0x66a0f60 mesh binding (rcx=&rbp+0x10, rdx=[rax], r9=&rbp+0x740, r8=[r13+0x3b8]); xor esi,1; if byte [rdi+0x20]==1 → skinned path G43 |
| G43 | 0x664a6de..0x664a8ea | byte [rdi+0x20]==1 | table 0x664f2bf32c exits | skinned draw block: sd [r12]→[rbp+0x7c0], ss [r12+8]→[rbp+0x7c8], xmm [r12+0xc/0x1c/0x2c], ss [r12+0x3c]→[rbp+0x7fc]; byte [rbp+0x800]=0; di=word [rdi+0x22]; write draw-state [rbp+0x224]=8, [rbp+0x228]=7, [rbp+0x22c]=esi, [rbp+0x230]=0x101, [rbp+0x232]=4, [rbp+0x234]=0, [rbp+0x238]=0, [rbp+0x23c]=0, [rbp+0x24c]=0xFFFFFFE0, movd [0xF07C974]=(-5.0f,-5.0f)→[rbp+0x250], [rbp+0x258]=8, [rbp+0x25c]=0, [rbp+0x264]=0, [rbp+0x268]=8, [rbp+0x26c]=0, [rbp+0x272]=0, [rbp+0x27a]=0xFF; read [rbp+0x5a0]→[rbp+0x280]; call 0xe869ff0 (rcx=&rbp+0x288, rdx=r14); fill [rbp+0x308..0x390] from [rbp+0x7c0..], di, [rbp+0x10], [rbp+0x30]; byte [rbp+0x390]=0xff; read byte [rbp+0x48]; table 0xF2BF32C |
| G44 | 0x664a8ed..0x664ab6a | byte [rdi+0x20]!=1 | table 0x664f2bf31c exits | non-skinned draw block: ss [r12+0x38/0x30/0x34], sd [r12]→[rbp+0x7c0], ss [r12+8]→[rbp+0x7c8], xmm [r12+0xc/0x1c/0x2c], ss [r12+0x3c]→[rbp+0x7fc]; [rbp+0x7f0]=ss [r12+0x30], [rbp+0x7f4]=[r12+0x34], [rbp+0x7f8]=[r12+0x38]; byte [rbp+0x800]=0; same draw-state writes as G43 (0x224..0x27a), [rbp+0x27c]=xmm8([r12+0x30]), [rbp+0x280]=xmm7, [rbp+0x284]=xmm6; read [rbp+0x5a0]→[rbp+0x288]; call 0xe869ff0 (rcx=&rbp+0x290); fill [rbp+0x310..0x398]; table 0xF2BF31C |
| G45 | 0x664ab6a..0x664abf5 | (external jump target from 0x6649dc2) | loc_664ab7a / loc_664abf5 | copy loop #1: stride-0x20 pairs from [rax+0x10] into [rbp+rcx+0x5a0], count [rbp+0x620]++ per pair; r9d=edx&~1 |
| G46 | 0x664abf5..0x664aca1 | loc_664abf5 | loc_664aca1 / loc_664ac88 | read rdx=[rsi+0x2c0]+0x40; r9d=[rdx+0x28]; if 0 → loc_664aca1; copy loop #2 stride 0x20 from [rbx] into [rax+r8], count [rbp+0x6a8]++ |
| G47 | 0x664aca1..0x664ad0f | loc_664aca1 | 0x664ad64 / 0x664ad4f / end | read ss [rdx] → write [rbp+0x6b0]; [rbp+0x90]=0; rdx=0xFFFFFFFFFFFFFFF; rcx mask loop (rcx&=rdx; if result==1 → r8d=0 → 0x664ad4f); r14=&rbp+0x5a0; tail copy: `movups xmm1,[rbp+0x5a0]`; `movups [rbp+r8+0x10],xmm1` at 0x664ad05/0x664ad09; then 4 undecoded bytes 0x664ad0f..0x664ad12; region end 0x664ad13 |

Legend: [rbp+K] = stack locals; [rdi+K] = description fields; "table scan" = stride-0x10 (or 0x30) array, compare entry+0x28 against a .data global qword; "emplace" = entt registry component insertion helper; "mesh binding" = 0x66a0f60/0x66e75f0 draw-binding builders.

## STATUS
Region fully decoded: 0x6648d13..0x664ad0f (last instruction); 4 trailing bytes undecoded; region end 0x664ad13 per rdis `fn`. Full [V] instruction table appended below (verify_oc-clean). Decode mirrored to docs/functions/item_tag7_skinned.md.

CLOSES? YES — sub_6648d13 (0x6648d13..0x664ad13) decoded block by block: all instruction offsets covered by [V] rows in docs/progress/oc_U-EM1d.md (delegate check OK, verify_oc mismatch=0 no-such-instr=0), block map + callees + field offsets documented, and the decode added to docs/functions/item_tag7_skinned.md.

## TOOL REQUESTS
rdis.exe via shell (static, exe as argument) | exe + RVA -> listing | replaced manual disassembly; used for fn/dis bounds and every proof row
verify_oc.py + delegate.py | progress file -> proof check | validated all quoted 0xRVA  instr lines against the exe

## Full instruction table — sub_6648d13 (0x6648d13..0x664ad0f), one row per offset, [V] from rdis dis

| offset | size | access | `0xRVA  instr` | meaning | [V] |
|---|---|---|---|---|---|
| 0x6648d13 | - | - | `0x6648d13  mov [rbp+0x6C8],al` | store variant tag byte (al) to [rbp+0x6c8] | [V] |
| 0x6648d19 | - | - | `0x6648d19  mov [rbp+0x6D0],si` | store word (si) to [rbp+0x6d0] | [V] |
| 0x6648d20 | 16 | read 16 bytes rbp+0x740 | `0x6648d20  movaps xmm0,[rbp+0x740]` | read 16 bytes rbp+0x740 | [V] |
| 0x6648d27 | 16 | read 16 bytes rbp+0x750 | `0x6648d27  movaps xmm1,[rbp+0x750]` | read 16 bytes rbp+0x750 | [V] |
| 0x6648d2e | 8 | write rbp+0x748 | `0x6648d2e  mov qword ptr [rbp+0x748],0` | clear [rbp+0x748] | [V] |
| 0x6648d39 | 16 | write 16 bytes rbp+0x6d8 | `0x6648d39  movups [rbp+0x6D8],xmm0` | write 16 bytes rbp+0x6d8 | [V] |
| 0x6648d40 | 16 | - | `0x6648d40  xorps xmm0,xmm0` | - | [V] |
| 0x6648d43 | 16 | write 16 bytes rbp+0x750 | `0x6648d43  movaps [rbp+0x750],xmm0` | clear [rbp+0x750] = 0 | [V] |
| 0x6648d4a | 16 | write 16 bytes rbp+0x6e8 | `0x6648d4a  movups [rbp+0x6E8],xmm1` | save vector state [rbp+0x6e8] = [rbp+0x750] | [V] |
| 0x6648d51 | 8 | read rbp+0x760 | `0x6648d51  mov rax,[rbp+0x760]` | read rbp+0x760 | [V] |
| 0x6648d58 | - | - | `0x6648d58  mov [rbp+0x6F8],rax` | - | [V] |
| 0x6648d5f | 8 | - | `0x6648d5f  lea r14,[rbp+0x700]` | - | [V] |
| 0x6648d66 | 1 | write rbp+0x710 | `0x6648d66  mov byte ptr [rbp+0x710],0xFF` | set flag byte [rbp+0x710] = 0xFF | [V] |
| 0x6648d6d | 4 | - | `0x6648d6d  movzx eax,byte ptr [rbp+0x778]` | - | [V] |
| 0x6648d74 | 8 | - | `0x6648d74  cmp rax,3` | - | [V] |
| 0x6648d78 | 2 | - | `0x6648d78  ja 0x664B8C3` | branch to 0x664b8c3 | [V] |
| 0x6648d7e | 8 | - | `0x6648d7e  lea rcx,[0xF2BF34C]` | jump-table / string base 0xf2bf34c | [V] |
| 0x6648d85 | 8 | read 4 bytes rcx+rax*4 (jump table) | `0x6648d85  movsxd rdx,[rcx+rax*4]` | read 4 bytes rcx+rax*4 (jump table entry) | [V] |
| 0x6648d89 | 8 | - | `0x6648d89  add rdx,rcx` | - | [V] |
| 0x6648d8c | 2 | jump rdx | `0x6648d8c  jmp rdx` | indirect jump via jump table (rdx) | [V] |
| 0x6648d8e | 8 | read rbp+0x768 | `0x6648d8e  mov rcx,[rbp+0x768]` | read rbp+0x768 | [V] |
| 0x6648d95 | - | - | `0x6648d95  mov [rbp+0x700],rcx` | - | [V] |
| 0x6648d9c | 5 | jump 0x664B8BD | `0x6648d9c  jmp 0x664B8BD` | jump to 0x664b8bd | [V] |
| 0x6648da1 | 8 | write r14+8 | `0x6648da1  mov qword ptr [r14+8],0` | - | [V] |
| 0x6648da9 | 16 | read 16 bytes rdi+0x10 | `0x6648da9  movups xmm0,[rdi+0x10]` | read 16 bytes rdi+0x10 | [V] |
| 0x6648dad | 16 | write 16 bytes r14+0x10 | `0x6648dad  movups [r14+0x10],xmm0` | write 16 bytes r14+0x10 | [V] |
| 0x6648db2 | - | - | `0x6648db2  mov [rbp+0x2D0],sil` | store sil to [rbp+0x2d0] | [V] |
| 0x6648db9 | 8 | - | `0x6648db9  lea r8,[rbp+0x220]` | - | [V] |
| 0x6648dc0 | - | - | `0x6648dc0  mov rcx,rbx` | - | [V] |
| 0x6648dc3 | 8 | read rbp+0x8a0 | `0x6648dc3  mov rdx,[rbp+0x8A0]` | read rbp+0x8a0 | [V] |
| 0x6648dca | 5 | call 0x66E75F0 | `0x6648dca  call 0x66E75F0` | call sub_66e75f0 (mesh binding helper (out=[rbp+0x220], same as ItemInHand extractor)) | [V] |
| 0x6648dcf | - | - | `0x6648dcf  nop` | - | [V] |
| 0x6648dd0 | 8 | - | `0x6648dd0  lea rcx,[rbp+0x220]` | - | [V] |
| 0x6648dd7 | 5 | call 0x539DD40 | `0x6648dd7  call 0x539DD40` | call sub_539dd40 (small forwarder) | [V] |
| 0x6648ddc | 5 | jump 0x664EBD7 | `0x6648ddc  jmp 0x664EBD7` | jump to 0x664ebd7 | [V] |
| 0x6648de1 | 8 | read rax | `0x6648de1  mov rax,[rax]` | read rax | [V] |
| 0x6648de4 | - | - | `0x6648de4  mov [rbp+0x220],rax` | - | [V] |
| 0x6648deb | 8 | write rbp+0x228 | `0x6648deb  mov qword ptr [rbp+0x228],0` | - | [V] |
| 0x6648df6 | 8 | read rbp+0x220 | `0x6648df6  mov rax,[rbp+0x220]` | read rbp+0x220 | [V] |
| 0x6648dfd | 8 | read rax+0x18 | `0x6648dfd  mov rax,[rax+0x18]` | read rax+0x18 | [V] |
| 0x6648e01 | 8 | read rax | `0x6648e01  mov rax,[rax]` | read rax | [V] |
| 0x6648e04 | - | - | `0x6648e04  mov [rbp+0x10],rax` | - | [V] |
| 0x6648e08 | 8 | - | `0x6648e08  lea r14,[rbp+0x18]` | - | [V] |
| 0x6648e0c | 8 | read rbx | `0x6648e0c  mov r8,[rbx]` | read rbx | [V] |
| 0x6648e0f | 8 | read rax+0x170 | `0x6648e0f  mov rdx,[rax+0x170]` | read rax+0x170 | [V] |
| 0x6648e16 | - | - | `0x6648e16  mov rcx,r14` | - | [V] |
| 0x6648e19 | 5 | call 0xE86B370 | `0x6648e19  call 0xE86B370` | call sub_e86b370 (registry emplace (rcx=&out, rdx=[rax+0x170], r8=[rbx])) | [V] |
| 0x6648e1e | - | - | `0x6648e1e  nop` | - | [V] |
| 0x6648e1f | - | - | `0x6648e1f  mov [rbp+0x90],rbx` | - | [V] |
| 0x6648e26 | 8 | read rbp+0x228 | `0x6648e26  mov r15,[rbp+0x228]` | read rbp+0x228 | [V] |
| 0x6648e2d | 8 | - | `0x6648e2d  test r15,r15` | - | [V] |
| 0x6648e30 | 2 | - | `0x6648e30  je short 0x6648E5F` | - | [V] |
| 0x6648e32 | 4 | read+write r15+8 | `0x6648e32  lock dec dword ptr [r15+8]` | shared_ptr refcount adjust (read+write r15+8) | [V] |
| 0x6648e37 | 2 | - | `0x6648e37  jne short 0x6648E5F` | - | [V] |
| 0x6648e39 | 8 | read r15 | `0x6648e39  mov rax,[r15]` | read r15 | [V] |
| 0x6648e3c | 8 | read rax | `0x6648e3c  mov rax,[rax]` | read rax | [V] |
| 0x6648e3f | - | - | `0x6648e3f  mov rcx,r15` | - | [V] |
| 0x6648e42 | 8 | call qword | `0x6648e42  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x6648e48 | 4 | read+write r15+0xc | `0x6648e48  lock dec dword ptr [r15+0xC]` | shared_ptr refcount adjust (read+write r15+0xc) | [V] |
| 0x6648e4d | 2 | - | `0x6648e4d  jne short 0x6648E5F` | - | [V] |
| 0x6648e4f | 8 | read r15 | `0x6648e4f  mov rax,[r15]` | read r15 | [V] |
| 0x6648e52 | 8 | read rax+8 | `0x6648e52  mov rax,[rax+8]` | read rax+8 | [V] |
| 0x6648e56 | - | - | `0x6648e56  mov rcx,r15` | - | [V] |
| 0x6648e59 | 8 | call qword | `0x6648e59  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x6648e5f | 8 | read rdi+0xb0 | `0x6648e5f  mov r15,[rdi+0xB0]` | read rdi+0xb0 | [V] |
| 0x6648e66 | 8 | read r15+0x60 | `0x6648e66  mov rax,[r15+0x60]` | read r15+0x60 | [V] |
| 0x6648e6a | 8 | - | `0x6648e6a  sub rax,[r15+0x58]` | - | [V] |
| 0x6648e6e | 8 | - | `0x6648e6e  shr rax,2` | - | [V] |
| 0x6648e72 | - | - | `0x6648e72  imul eax,0xAAAAAAAB` | - | [V] |
| 0x6648e78 | 4 | - | `0x6648e78  test eax,eax` | - | [V] |
| 0x6648e7a | - | - | `0x6648e7a  mov rbx,r13` | - | [V] |
| 0x6648e7d | 2 | - | `0x6648e7d  je short 0x6648EAF` | - | [V] |
| 0x6648e7f | - | - | `0x6648e7f  mov edx,0x250` | - | [V] |
| 0x6648e84 | 8 | - | `0x6648e84  add rdx,[rbp+0x10]` | - | [V] |
| 0x6648e88 | 8 | - | `0x6648e88  lea rcx,[rbp+0x220]` | - | [V] |
| 0x6648e8f | 4 | - | `0x6648e8f  xor r8d,r8d` | - | [V] |
| 0x6648e92 | 5 | call 0xBBD7C70 | `0x6648e92  call 0xBBD7C70` | call sub_bbd7c70 (copy/construct 0x250-byte block) | [V] |
| 0x6648e97 | - | - | `0x6648e97  nop` | - | [V] |
| 0x6648e98 | 8 | - | `0x6648e98  lea rdx,[rbp+0x220]` | - | [V] |
| 0x6648e9f | - | - | `0x6648e9f  mov rcx,r15` | - | [V] |
| 0x6648ea2 | 5 | call 0x4DEDD00 | `0x6648ea2  call 0x4DEDD00` | call sub_4dedd00 (MeshFallback-side helper (rcx=element [rdi+0xB0])) | [V] |
| 0x6648ea7 | - | - | `0x6648ea7  nop` | - | [V] |
| 0x6648ea8 | 8 | read rdi+0xb0 | `0x6648ea8  mov r15,[rdi+0xB0]` | read rdi+0xb0 | [V] |
| 0x6648eaf | 8 | read rdi+0xb8 | `0x6648eaf  mov eax,[rdi+0xB8]` | read rdi+0xb8 | [V] |
| 0x6648eb5 | 4 | - | `0x6648eb5  xor r12d,r12d` | - | [V] |
| 0x6648eb8 | - | - | `0x6648eb8  cmp byte ptr [r15+0x1D4],0` | - | [V] |
| 0x6648ec0 | 2 | - | `0x6648ec0  je short 0x6648EC9` | - | [V] |
| 0x6648ec2 | 4 | read r15+0x1d0 | `0x6648ec2  mov r12d,[r15+0x1D0]` | read r15+0x1d0 | [V] |
| 0x6648ec9 | 4 | - | `0x6648ec9  test eax,eax` | - | [V] |
| 0x6648ecb | 2 | - | `0x6648ecb  jle short 0x6648EE1` | - | [V] |
| 0x6648ecd | - | - | `0x6648ecd  mov eax,eax` | - | [V] |
| 0x6648ecf | - | - | `0x6648ecf  mov r12d,0xAAAAAAAB` | - | [V] |
| 0x6648ed5 | - | - | `0x6648ed5  imul r12,rax` | - | [V] |
| 0x6648ed9 | 8 | - | `0x6648ed9  shr r12,0x20` | - | [V] |
| 0x6648edd | 4 | - | `0x6648edd  and r12d,0xFFFFFFFE` | - | [V] |
| 0x6648ee1 | 4 | - | `0x6648ee1  test r12d,r12d` | - | [V] |
| 0x6648ee4 | 2 | - | `0x6648ee4  je 0x664CB91` | branch to 0x664cb91 | [V] |
| 0x6648eea | 8 | read 0x129f9cd8 | `0x6648eea  mov eax,[0x129F9CD8]` | read 0x129f9cd8 | [V] |
| 0x6648ef0 | 8 | read 0x128767c8 | `0x6648ef0  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x6648ef6 | - | - | `0x6648ef6  mov rdx,gs:[0x58]` | - | [V] |
| 0x6648eff | 8 | read rdx+rcx*8 | `0x6648eff  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x6648f03 | 4 | - | `0x6648f03  cmp eax,[rcx+4]` | - | [V] |
| 0x6648f09 | 2 | - | `0x6648f09  jg 0x664F625` | branch to 0x664f625 | [V] |
| 0x6648f0f | 8 | read 0x129f9ce8 | `0x6648f0f  mov eax,[0x129F9CE8]` | read 0x129f9ce8 | [V] |
| 0x6648f15 | 8 | read 0x128767c8 | `0x6648f15  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x6648f1b | - | - | `0x6648f1b  mov rdx,gs:[0x58]` | - | [V] |
| 0x6648f24 | 8 | read rdx+rcx*8 | `0x6648f24  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x6648f28 | 4 | - | `0x6648f28  cmp eax,[rcx+4]` | - | [V] |
| 0x6648f2e | 2 | - | `0x6648f2e  jg 0x664F697` | branch to 0x664f697 | [V] |
| 0x6648f34 | 4 | write rbp+0x220 | `0x6648f34  mov dword ptr [rbp+0x220],0x3F800000` | default = 1.0f | [V] |
| 0x6648f3e | 16 | - | `0x6648f3e  pxor xmm0,xmm0` | - | [V] |
| 0x6648f42 | 16 | write 16 bytes rbp+0x224 | `0x6648f42  movdqu [rbp+0x224],xmm0` | write 16 bytes rbp+0x224 | [V] |
| 0x6648f4a | 4 | write rbp+0x234 | `0x6648f4a  mov dword ptr [rbp+0x234],0x3F800000` | default = 1.0f | [V] |
| 0x6648f54 | 16 | write 16 bytes rbp+0x238 | `0x6648f54  movdqu [rbp+0x238],xmm0` | write 16 bytes rbp+0x238 | [V] |
| 0x6648f5c | 4 | write rbp+0x248 | `0x6648f5c  mov dword ptr [rbp+0x248],0x3F800000` | default = 1.0f | [V] |
| 0x6648f66 | 16 | write 16 bytes rbp+0x24c | `0x6648f66  movdqu [rbp+0x24C],xmm0` | write 16 bytes rbp+0x24c | [V] |
| 0x6648f6e | 8 | read 8 bytes 0xefd3400 | `0x6648f6e  movsd xmm1,[0xEFD3400]` | load double 1.0 ([0xEFD3400]) | [V] |
| 0x6648f76 | 8 | write 8 bytes rbp+0x25c | `0x6648f76  movsd [rbp+0x25C],xmm1` | default double = 1.0 ([0xEFD3400]) | [V] |
| 0x6648f7e | 16 | write 16 bytes rbp+0x264 | `0x6648f7e  movdqu [rbp+0x264],xmm0` | write 16 bytes rbp+0x264 | [V] |
| 0x6648f86 | 4 | write rbp+0x274 | `0x6648f86  mov dword ptr [rbp+0x274],0x3F800000` | default = 1.0f | [V] |
| 0x6648f90 | 16 | write 16 bytes rbp+0x278 | `0x6648f90  movdqu [rbp+0x278],xmm0` | write 16 bytes rbp+0x278 | [V] |
| 0x6648f98 | 4 | write rbp+0x288 | `0x6648f98  mov dword ptr [rbp+0x288],0x3F800000` | default = 1.0f | [V] |
| 0x6648fa2 | 16 | write 16 bytes rbp+0x28c | `0x6648fa2  movdqu [rbp+0x28C],xmm0` | write 16 bytes rbp+0x28c | [V] |
| 0x6648faa | 8 | write 8 bytes rbp+0x29c | `0x6648faa  movsd [rbp+0x29C],xmm1` | write 8 bytes rbp+0x29c | [V] |
| 0x6648fb2 | 16 | write 16 bytes rbp+0x2a4 | `0x6648fb2  movdqu [rbp+0x2A4],xmm0` | write 16 bytes rbp+0x2a4 | [V] |
| 0x6648fba | 4 | write rbp+0x2b4 | `0x6648fba  mov dword ptr [rbp+0x2B4],0x3F800000` | default = 1.0f | [V] |
| 0x6648fc4 | 16 | write 16 bytes rbp+0x2b8 | `0x6648fc4  movdqu [rbp+0x2B8],xmm0` | write 16 bytes rbp+0x2b8 | [V] |
| 0x6648fcc | 4 | write rbp+0x2c8 | `0x6648fcc  mov dword ptr [rbp+0x2C8],0x3F800000` | default = 1.0f | [V] |
| 0x6648fd6 | 16 | write 16 bytes rbp+0x2cc | `0x6648fd6  movdqu [rbp+0x2CC],xmm0` | write 16 bytes rbp+0x2cc | [V] |
| 0x6648fde | 8 | write 8 bytes rbp+0x2dc | `0x6648fde  movsd [rbp+0x2DC],xmm1` | write 8 bytes rbp+0x2dc | [V] |
| 0x6648fe6 | 16 | write 16 bytes rbp+0x2e4 | `0x6648fe6  movdqu [rbp+0x2E4],xmm0` | write 16 bytes rbp+0x2e4 | [V] |
| 0x6648fee | 4 | write rbp+0x2f4 | `0x6648fee  mov dword ptr [rbp+0x2F4],0x3F800000` | default = 1.0f | [V] |
| 0x6648ff8 | 16 | write 16 bytes rbp+0x2f8 | `0x6648ff8  movdqu [rbp+0x2F8],xmm0` | write 16 bytes rbp+0x2f8 | [V] |
| 0x6649000 | 4 | write rbp+0x308 | `0x6649000  mov dword ptr [rbp+0x308],0x3F800000` | default = 1.0f | [V] |
| 0x664900a | 16 | write 16 bytes rbp+0x30c | `0x664900a  movdqu [rbp+0x30C],xmm0` | write 16 bytes rbp+0x30c | [V] |
| 0x6649012 | 8 | write 8 bytes rbp+0x31c | `0x6649012  movsd [rbp+0x31C],xmm1` | write 8 bytes rbp+0x31c | [V] |
| 0x664901a | 16 | write 16 bytes rbp+0x324 | `0x664901a  movdqu [rbp+0x324],xmm0` | write 16 bytes rbp+0x324 | [V] |
| 0x6649022 | 4 | write rbp+0x334 | `0x6649022  mov dword ptr [rbp+0x334],0x3F800000` | default = 1.0f | [V] |
| 0x664902c | 16 | write 16 bytes rbp+0x338 | `0x664902c  movdqu [rbp+0x338],xmm0` | write 16 bytes rbp+0x338 | [V] |
| 0x6649034 | 4 | write rbp+0x348 | `0x6649034  mov dword ptr [rbp+0x348],0x3F800000` | default = 1.0f | [V] |
| 0x664903e | 16 | write 16 bytes rbp+0x34c | `0x664903e  movdqu [rbp+0x34C],xmm0` | write 16 bytes rbp+0x34c | [V] |
| 0x6649046 | 8 | write 8 bytes rbp+0x35c | `0x6649046  movsd [rbp+0x35C],xmm1` | write 8 bytes rbp+0x35c | [V] |
| 0x664904e | 16 | write 16 bytes rbp+0x364 | `0x664904e  movdqu [rbp+0x364],xmm0` | write 16 bytes rbp+0x364 | [V] |
| 0x6649056 | 4 | write rbp+0x374 | `0x6649056  mov dword ptr [rbp+0x374],0x3F800000` | default = 1.0f | [V] |
| 0x6649060 | 16 | write 16 bytes rbp+0x378 | `0x6649060  movdqu [rbp+0x378],xmm0` | write 16 bytes rbp+0x378 | [V] |
| 0x6649068 | 4 | write rbp+0x388 | `0x6649068  mov dword ptr [rbp+0x388],0x3F800000` | default = 1.0f | [V] |
| 0x6649072 | 16 | write 16 bytes rbp+0x38c | `0x6649072  movdqu [rbp+0x38C],xmm0` | write 16 bytes rbp+0x38c | [V] |
| 0x664907a | 8 | write 8 bytes rbp+0x39c | `0x664907a  movsd [rbp+0x39C],xmm1` | write 8 bytes rbp+0x39c | [V] |
| 0x6649082 | 16 | write 16 bytes rbp+0x3a4 | `0x6649082  movdqu [rbp+0x3A4],xmm0` | write 16 bytes rbp+0x3a4 | [V] |
| 0x664908a | 4 | write rbp+0x3b4 | `0x664908a  mov dword ptr [rbp+0x3B4],0x3F800000` | default = 1.0f | [V] |
| 0x6649094 | 16 | write 16 bytes rbp+0x3b8 | `0x6649094  movdqu [rbp+0x3B8],xmm0` | write 16 bytes rbp+0x3b8 | [V] |
| 0x664909c | 4 | write rbp+0x3c8 | `0x664909c  mov dword ptr [rbp+0x3C8],0x3F800000` | default = 1.0f | [V] |
| 0x66490a6 | 16 | write 16 bytes rbp+0x3cc | `0x66490a6  movdqu [rbp+0x3CC],xmm0` | write 16 bytes rbp+0x3cc | [V] |
| 0x66490ae | 8 | write 8 bytes rbp+0x3dc | `0x66490ae  movsd [rbp+0x3DC],xmm1` | write 8 bytes rbp+0x3dc | [V] |
| 0x66490b6 | 16 | write 16 bytes rbp+0x3e4 | `0x66490b6  movdqu [rbp+0x3E4],xmm0` | write 16 bytes rbp+0x3e4 | [V] |
| 0x66490be | 4 | write rbp+0x3f4 | `0x66490be  mov dword ptr [rbp+0x3F4],0x3F800000` | default = 1.0f | [V] |
| 0x66490c8 | 16 | write 16 bytes rbp+0x3f8 | `0x66490c8  movdqu [rbp+0x3F8],xmm0` | write 16 bytes rbp+0x3f8 | [V] |
| 0x66490d0 | 4 | write rbp+0x408 | `0x66490d0  mov dword ptr [rbp+0x408],0x3F800000` | default = 1.0f | [V] |
| 0x66490da | 16 | write 16 bytes rbp+0x40c | `0x66490da  movdqu [rbp+0x40C],xmm0` | write 16 bytes rbp+0x40c | [V] |
| 0x66490e2 | 4 | write rbp+0x41c | `0x66490e2  mov dword ptr [rbp+0x41C],0x3F800000` | default = 1.0f | [V] |
| 0x66490ec | 8 | read rdi+0xc0 | `0x66490ec  mov rax,[rdi+0xC0]` | read rdi+0xc0 | [V] |
| 0x66490f3 | 8 | - | `0x66490f3  cmp rax,0xFFFFFFFFFFFFFFFF` | - | [V] |
| 0x66490f7 | 2 | - | `0x66490f7  je 0x664ED47` | branch to 0x664ed47 | [V] |
| 0x66490fd | 8 | read rdi+0xc8 | `0x66490fd  mov rcx,[rdi+0xC8]` | read rdi+0xc8 | [V] |
| 0x6649104 | - | - | `0x6649104  mov [rbp+0x850],rax` | - | [V] |
| 0x664910b | - | - | `0x664910b  mov [rbp+0x858],rcx` | - | [V] |
| 0x6649112 | 8 | - | `0x6649112  test rcx,rcx` | - | [V] |
| 0x6649115 | 1 | - | `0x6649115  setne cl` | - | [V] |
| 0x6649118 | 8 | - | `0x6649118  test rax,rax` | - | [V] |
| 0x664911b | 1 | - | `0x664911b  sete al` | - | [V] |
| 0x664911e | 4 | - | `0x664911e  or al,cl` | - | [V] |
| 0x6649120 | 2 | - | `0x6649120  je 0x664ED47` | branch to 0x664ed47 | [V] |
| 0x6649126 | 8 | - | `0x6649126  lea rcx,[rbp+0x850]` | - | [V] |
| 0x664912d | 8 | - | `0x664912d  lea r15,[rbp+0x220]` | - | [V] |
| 0x6649134 | - | - | `0x6649134  mov rdx,r15` | - | [V] |
| 0x6649137 | 5 | call 0x6698060 | `0x6649137  call 0x6698060` | call sub_6698060 (helper) | [V] |
| 0x664913c | - | - | `0x664913c  nop` | - | [V] |
| 0x664913d | 8 | write rbp+0x5a0 | `0x664913d  mov qword ptr [rbp+0x5A0],8` | - | [V] |
| 0x6649148 | - | - | `0x6649148  mov [rbp+0x5A8],r15` | - | [V] |
| 0x664914f | 8 | read rbp+0x48 | `0x664914f  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x6649153 | 4 | - | `0x6649153  movzx edx,word ptr [rbp+0x52]` | - | [V] |
| 0x6649157 | - | - | `0x6649157  mov ecx,edx` | - | [V] |
| 0x6649159 | 8 | - | `0x6649159  shl ecx,4` | - | [V] |
| 0x664915c | - | - | `0x664915c  mov r8,rax` | - | [V] |
| 0x664915f | 4 | - | `0x664915f  test edx,edx` | - | [V] |
| 0x6649161 | 2 | - | `0x6649161  je 0x664AE25` | branch to 0x664ae25 | [V] |
| 0x6649167 | 8 | read 0x129f8310 | `0x6649167  mov r9,[0x129F8310]` | read 0x129f8310 | [V] |
| 0x664916e | 4 | - | `0x664916e  xor r8d,r8d` | - | [V] |
| 0x6649171 | 8 | read rax+r8 | `0x6649171  mov r10,[rax+r8]` | read rax+r8 | [V] |
| 0x6649175 | - | read r10+0x28 | `0x6649175  cmp [r10+0x28],r9` | read r10+0x28 (compare) | [V] |
| 0x6649179 | 2 | - | `0x6649179  je 0x664AE22` | branch to 0x664ae22 | [V] |
| 0x664917f | 8 | - | `0x664917f  add r8,0x10` | - | [V] |
| 0x6649183 | 8 | - | `0x6649183  cmp rcx,r8` | - | [V] |
| 0x6649186 | 2 | - | `0x6649186  jne short 0x6649171` | - | [V] |
| 0x6649188 | - | - | `0x6649188  mov dx,1` | - | [V] |
| 0x664918c | 5 | jump 0x664AE68 | `0x664918c  jmp 0x664AE68` | jump to 0x664ae68 | [V] |
| 0x6649191 | 8 | read rax | `0x6649191  mov rax,[rax]` | read rax | [V] |
| 0x6649194 | - | - | `0x6649194  mov [rbp+0x220],rax` | - | [V] |
| 0x664919b | 8 | write rbp+0x228 | `0x664919b  mov qword ptr [rbp+0x228],0` | - | [V] |
| 0x66491a6 | - | - | `0x66491a6  mov rbx,r14` | - | [V] |
| 0x66491a9 | 8 | read rbp+0x220 | `0x66491a9  mov rax,[rbp+0x220]` | read rbp+0x220 | [V] |
| 0x66491b0 | 8 | read rax+0x18 | `0x66491b0  mov rax,[rax+0x18]` | read rax+0x18 | [V] |
| 0x66491b4 | 8 | read rax | `0x66491b4  mov rax,[rax]` | read rax | [V] |
| 0x66491b7 | - | - | `0x66491b7  mov [rbp+0x10],rax` | - | [V] |
| 0x66491bb | 8 | - | `0x66491bb  lea r15,[rbp+0x18]` | - | [V] |
| 0x66491bf | 8 | read rsi | `0x66491bf  mov r8,[rsi]` | read rsi | [V] |
| 0x66491c2 | 8 | read rax+0x170 | `0x66491c2  mov rdx,[rax+0x170]` | read rax+0x170 | [V] |
| 0x66491c9 | - | - | `0x66491c9  mov rcx,r15` | - | [V] |
| 0x66491cc | 5 | call 0xE86B370 | `0x66491cc  call 0xE86B370` | call sub_e86b370 (registry emplace (rcx=&out, rdx=[rax+0x170], r8=[rbx])) | [V] |
| 0x66491d1 | - | - | `0x66491d1  nop` | - | [V] |
| 0x66491d2 | 8 | - | `0x66491d2  lea r14,[rbp+0x220]` | - | [V] |
| 0x66491d9 | - | - | `0x66491d9  mov [rbp+0x90],rsi` | - | [V] |
| 0x66491e0 | 8 | read rbp+0x228 | `0x66491e0  mov r12,[rbp+0x228]` | read rbp+0x228 | [V] |
| 0x66491e7 | 8 | - | `0x66491e7  test r12,r12` | - | [V] |
| 0x66491ea | 2 | - | `0x66491ea  je short 0x664921D` | - | [V] |
| 0x66491ec | 4 | read+write r12+8 | `0x66491ec  lock dec dword ptr [r12+8]` | shared_ptr refcount adjust (read+write r12+8) | [V] |
| 0x66491f2 | 2 | - | `0x66491f2  jne short 0x664921D` | - | [V] |
| 0x66491f4 | 8 | read r12 | `0x66491f4  mov rax,[r12]` | read r12 | [V] |
| 0x66491f8 | 8 | read rax | `0x66491f8  mov rax,[rax]` | read rax | [V] |
| 0x66491fb | - | - | `0x66491fb  mov rcx,r12` | - | [V] |
| 0x66491fe | 8 | call qword | `0x66491fe  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x6649204 | 4 | read+write r12+0xc | `0x6649204  lock dec dword ptr [r12+0xC]` | shared_ptr refcount adjust (read+write r12+0xc) | [V] |
| 0x664920a | 2 | - | `0x664920a  jne short 0x664921D` | - | [V] |
| 0x664920c | 8 | read r12 | `0x664920c  mov rax,[r12]` | read r12 | [V] |
| 0x6649210 | 8 | read rax+8 | `0x6649210  mov rax,[rax+8]` | read rax+8 | [V] |
| 0x6649214 | - | - | `0x6649214  mov rcx,r12` | - | [V] |
| 0x6649217 | 8 | call qword | `0x6649217  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664921d | 8 | read 0x129f9340 | `0x664921d  mov eax,[0x129F9340]` | read 0x129f9340 | [V] |
| 0x6649223 | 8 | read 0x128767c8 | `0x6649223  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x6649229 | - | - | `0x6649229  mov rdx,gs:[0x58]` | - | [V] |
| 0x6649232 | 8 | read rdx+rcx*8 | `0x6649232  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x6649236 | 4 | - | `0x6649236  cmp eax,[rcx+4]` | - | [V] |
| 0x664923c | 2 | - | `0x664923c  jg 0x664F421` | branch to 0x664f421 | [V] |
| 0x6649242 | 16 | read 16 bytes rdi+0x64 | `0x6649242  movups xmm0,[rdi+0x64]` | read 16 bytes rdi+0x64 | [V] |
| 0x6649246 | 16 | write 16 bytes rbp+0x220 | `0x6649246  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x664924d | 8 | write rbp+0x5a0 | `0x664924d  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x6649258 | - | - | `0x6649258  mov [rbp+0x5A8],r14` | - | [V] |
| 0x664925f | 8 | read rbp+0x48 | `0x664925f  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x6649263 | 4 | - | `0x6649263  movzx edx,word ptr [rbp+0x52]` | - | [V] |
| 0x6649267 | - | - | `0x6649267  mov ecx,edx` | - | [V] |
| 0x6649269 | 8 | - | `0x6649269  shl ecx,4` | - | [V] |
| 0x664926c | - | - | `0x664926c  mov r8,rax` | - | [V] |
| 0x664926f | 4 | - | `0x664926f  test edx,edx` | - | [V] |
| 0x6649271 | 2 | - | `0x6649271  je 0x66495FE` | branch to 0x66495fe | [V] |
| 0x6649277 | 8 | read 0x129f9338 | `0x6649277  mov r9,[0x129F9338]` | read 0x129f9338 | [V] |
| 0x664927e | 4 | - | `0x664927e  xor r8d,r8d` | - | [V] |
| 0x6649281 | 8 | read rax+r8 | `0x6649281  mov r10,[rax+r8]` | read rax+r8 | [V] |
| 0x6649285 | - | read r10+0x28 | `0x6649285  cmp [r10+0x28],r9` | read r10+0x28 (compare) | [V] |
| 0x6649289 | 2 | - | `0x6649289  je 0x66495FB` | branch to 0x66495fb | [V] |
| 0x664928f | 8 | - | `0x664928f  add r8,0x10` | - | [V] |
| 0x6649293 | 8 | - | `0x6649293  cmp rcx,r8` | - | [V] |
| 0x6649296 | 2 | - | `0x6649296  jne short 0x6649281` | - | [V] |
| 0x6649298 | 5 | jump 0x6649641 | `0x6649298  jmp 0x6649641` | jump to 0x6649641 | [V] |
| 0x664929d | 8 | read rax | `0x664929d  mov rax,[rax]` | read rax | [V] |
| 0x66492a0 | - | - | `0x66492a0  mov [rbp+0x220],rax` | - | [V] |
| 0x66492a7 | 8 | write rbp+0x228 | `0x66492a7  mov qword ptr [rbp+0x228],0` | - | [V] |
| 0x66492b2 | 8 | read rbp+0x220 | `0x66492b2  mov rax,[rbp+0x220]` | read rbp+0x220 | [V] |
| 0x66492b9 | 8 | read rax+0x18 | `0x66492b9  mov rax,[rax+0x18]` | read rax+0x18 | [V] |
| 0x66492bd | 8 | read rax | `0x66492bd  mov rax,[rax]` | read rax | [V] |
| 0x66492c0 | - | - | `0x66492c0  mov [rbp+0x7C0],rax` | - | [V] |
| 0x66492c7 | 8 | - | `0x66492c7  lea r14,[rbp+0x7C8]` | - | [V] |
| 0x66492ce | 8 | read rbx | `0x66492ce  mov r8,[rbx]` | read rbx | [V] |
| 0x66492d1 | 8 | read rax+0x170 | `0x66492d1  mov rdx,[rax+0x170]` | read rax+0x170 | [V] |
| 0x66492d8 | - | - | `0x66492d8  mov rcx,r14` | - | [V] |
| 0x66492db | 5 | call 0xE86B370 | `0x66492db  call 0xE86B370` | call sub_e86b370 (registry emplace (rcx=&out, rdx=[rax+0x170], r8=[rbx])) | [V] |
| 0x66492e0 | - | - | `0x66492e0  nop` | - | [V] |
| 0x66492e1 | - | - | `0x66492e1  mov [rbp+0x840],rbx` | - | [V] |
| 0x66492e8 | 8 | read rbp+0x228 | `0x66492e8  mov r15,[rbp+0x228]` | read rbp+0x228 | [V] |
| 0x66492ef | 8 | - | `0x66492ef  test r15,r15` | - | [V] |
| 0x66492f2 | 2 | - | `0x66492f2  je short 0x6649321` | - | [V] |
| 0x66492f4 | 4 | read+write r15+8 | `0x66492f4  lock dec dword ptr [r15+8]` | shared_ptr refcount adjust (read+write r15+8) | [V] |
| 0x66492f9 | 2 | - | `0x66492f9  jne short 0x6649321` | - | [V] |
| 0x66492fb | 8 | read r15 | `0x66492fb  mov rax,[r15]` | read r15 | [V] |
| 0x66492fe | 8 | read rax | `0x66492fe  mov rax,[rax]` | read rax | [V] |
| 0x6649301 | - | - | `0x6649301  mov rcx,r15` | - | [V] |
| 0x6649304 | 8 | call qword | `0x6649304  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664930a | 4 | read+write r15+0xc | `0x664930a  lock dec dword ptr [r15+0xC]` | shared_ptr refcount adjust (read+write r15+0xc) | [V] |
| 0x664930f | 2 | - | `0x664930f  jne short 0x6649321` | - | [V] |
| 0x6649311 | 8 | read r15 | `0x6649311  mov rax,[r15]` | read r15 | [V] |
| 0x6649314 | 8 | read rax+8 | `0x6649314  mov rax,[rax+8]` | read rax+8 | [V] |
| 0x6649318 | - | - | `0x6649318  mov rcx,r15` | - | [V] |
| 0x664931b | 8 | call qword | `0x664931b  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x6649321 | 8 | read 0x129f9220 | `0x6649321  mov eax,[0x129F9220]` | read 0x129f9220 | [V] |
| 0x6649327 | 8 | read 0x128767c8 | `0x6649327  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x664932d | - | - | `0x664932d  mov rdx,gs:[0x58]` | - | [V] |
| 0x6649336 | 8 | read rdx+rcx*8 | `0x6649336  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x664933a | 4 | - | `0x664933a  cmp eax,[rcx+4]` | - | [V] |
| 0x6649340 | 2 | - | `0x6649340  jg 0x664F577` | branch to 0x664f577 | [V] |
| 0x6649346 | 16 | read 16 bytes rdi+0x68 | `0x6649346  movups xmm0,[rdi+0x68]` | read 16 bytes rdi+0x68 | [V] |
| 0x664934a | 16 | write 16 bytes rbp+0x220 | `0x664934a  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x6649351 | 8 | write rbp+0x5a0 | `0x6649351  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x664935c | 8 | - | `0x664935c  lea rax,[rbp+0x220]` | - | [V] |
| 0x6649363 | - | - | `0x6649363  mov [rbp+0x5A8],rax` | - | [V] |
| 0x664936a | 8 | read rbp+0x7f8 | `0x664936a  mov rax,[rbp+0x7F8]` | read rbp+0x7f8 | [V] |
| 0x6649371 | 4 | - | `0x6649371  movzx r8d,word ptr [rbp+0x802]` | - | [V] |
| 0x6649379 | - | - | `0x6649379  mov edx,r8d` | - | [V] |
| 0x664937c | 8 | - | `0x664937c  shl edx,4` | - | [V] |
| 0x664937f | - | - | `0x664937f  mov rcx,rax` | - | [V] |
| 0x6649382 | 4 | - | `0x6649382  test r8d,r8d` | - | [V] |
| 0x6649385 | 2 | - | `0x6649385  je short 0x66493A9` | - | [V] |
| 0x6649387 | 8 | read 0x129f9218 | `0x6649387  mov r8,[0x129F9218]` | read 0x129f9218 | [V] |
| 0x664938e | - | - | `0x664938e  mov r9,rdx` | - | [V] |
| 0x6649391 | - | - | `0x6649391  mov rcx,rax` | - | [V] |
| 0x6649394 | 8 | read rcx | `0x6649394  mov r10,[rcx]` | read rcx | [V] |
| 0x6649397 | - | read r10+0x28 | `0x6649397  cmp [r10+0x28],r8` | read r10+0x28 (compare) | [V] |
| 0x664939b | 2 | - | `0x664939b  je short 0x66493A9` | - | [V] |
| 0x664939d | 8 | - | `0x664939d  add rcx,0x10` | - | [V] |
| 0x66493a1 | 8 | - | `0x66493a1  add r9,0xFFFFFFFFFFFFFFF0` | - | [V] |
| 0x66493a5 | 2 | - | `0x66493a5  jne short 0x6649394` | - | [V] |
| 0x66493a7 | 2 | jump short | `0x66493a7  jmp short 0x66493DB` | jump to 0x66493db | [V] |
| 0x66493a9 | 8 | - | `0x66493a9  add rdx,rax` | - | [V] |
| 0x66493ac | 8 | - | `0x66493ac  cmp rcx,rdx` | - | [V] |
| 0x66493af | 2 | - | `0x66493af  jae short 0x66493DB` | - | [V] |
| 0x66493b1 | 4 | - | `0x66493b1  sub ecx,eax` | - | [V] |
| 0x66493b3 | 8 | - | `0x66493b3  shr ecx,4` | - | [V] |
| 0x66493b6 | - | - | `0x66493b6  mov [rbp+0x740],cx` | - | [V] |
| 0x66493bd | 1 | write rbp+0x742 | `0x66493bd  mov byte ptr [rbp+0x742],1` | - | [V] |
| 0x66493c4 | 8 | - | `0x66493c4  lea rdx,[rbp+0x740]` | - | [V] |
| 0x66493cb | 8 | - | `0x66493cb  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x66493d2 | - | - | `0x66493d2  mov rcx,r14` | - | [V] |
| 0x66493d5 | 5 | call 0x5679DB0 | `0x66493d5  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x66493da | - | - | `0x66493da  nop` | - | [V] |
| 0x66493db | - | - | `0x66493db  and byte ptr [rbp+0x144],0xF7` | - | [V] |
| 0x66493e2 | 8 | read rdi | `0x66493e2  mov r9,[rdi]` | read rdi | [V] |
| 0x66493e5 | 8 | - | `0x66493e5  lea rcx,[rbp+0x740]` | - | [V] |
| 0x66493ec | 8 | - | `0x66493ec  lea r8,[rbp+0x7C0]` | - | [V] |
| 0x66493f3 | 8 | read rbp+0x8a0 | `0x66493f3  mov rdx,[rbp+0x8A0]` | read rbp+0x8a0 | [V] |
| 0x66493fa | 5 | call 0xBBD7F70 | `0x66493fa  call 0xBBD7F70` | call sub_bbd7f70 (registry emplace) | [V] |
| 0x66493ff | - | - | `0x66493ff  nop` | - | [V] |
| 0x6649400 | - | - | `0x6649400  cmp byte ptr [rbp+0x798],0` | - | [V] |
| 0x6649407 | 2 | - | `0x6649407  je 0x664D484` | branch to 0x664d484 | [V] |
| 0x664940d | - | - | `0x664940d  cmp byte ptr [rdi+0x94],1` | - | [V] |
| 0x6649414 | 2 | - | `0x6649414  jne short 0x664942B` | - | [V] |
| 0x6649416 | 1 | write rbp+0x154 | `0x6649416  mov byte ptr [rbp+0x154],1` | - | [V] |
| 0x664941d | 16 | read 16 bytes rdi+0x84 | `0x664941d  movups xmm0,[rdi+0x84]` | read 16 bytes rdi+0x84 | [V] |
| 0x6649424 | 16 | write 16 bytes rbp+0x158 | `0x6649424  movups [rbp+0x158],xmm0` | write 16 bytes rbp+0x158 | [V] |
| 0x664942b | 4 | read 4 bytes rdi+0x50 | `0x664942b  movss xmm0,[rdi+0x50]` | read 4 bytes rdi+0x50 | [V] |
| 0x6649430 | 16 | read 16 bytes rdi+8 | `0x6649430  movups xmm1,[rdi+8]` | read 16 bytes rdi+8 | [V] |
| 0x6649434 | 16 | write 16 bytes rbp+0x1a0 | `0x6649434  movaps [rbp+0x1A0],xmm1` | write 16 bytes rbp+0x1a0 | [V] |
| 0x664943b | 16 | read 16 bytes rdi+0x18 | `0x664943b  movups xmm2,[rdi+0x18]` | read 16 bytes rdi+0x18 | [V] |
| 0x664943f | 16 | write 16 bytes rbp+0x1b0 | `0x664943f  movaps [rbp+0x1B0],xmm2` | write 16 bytes rbp+0x1b0 | [V] |
| 0x6649446 | 16 | read 16 bytes rdi+0x28 | `0x6649446  movups xmm3,[rdi+0x28]` | read 16 bytes rdi+0x28 | [V] |
| 0x664944a | 16 | write 16 bytes rbp+0x1c0 | `0x664944a  movaps [rbp+0x1C0],xmm3` | write 16 bytes rbp+0x1c0 | [V] |
| 0x6649451 | 16 | read 16 bytes rdi+0x38 | `0x6649451  movups xmm4,[rdi+0x38]` | read 16 bytes rdi+0x38 | [V] |
| 0x6649455 | 16 | write 16 bytes rbp+0x1d0 | `0x6649455  movaps [rbp+0x1D0],xmm4` | write 16 bytes rbp+0x1d0 | [V] |
| 0x664945c | 1 | write rbp+0x1e0 | `0x664945c  mov byte ptr [rbp+0x1E0],0` | - | [V] |
| 0x6649463 | 8 | read rdi+0x80 | `0x6649463  mov si,[rdi+0x80]` | read rdi+0x80 | [V] |
| 0x664946a | 8 | read 8 bytes rdi+0x48 | `0x664946a  movsd xmm5,[rdi+0x48]` | read 8 bytes rdi+0x48 | [V] |
| 0x664946f | 8 | write 8 bytes rbp+0x220 | `0x664946f  movsd [rbp+0x220],xmm5` | write 8 bytes rbp+0x220 | [V] |
| 0x6649477 | 4 | write 4 bytes rbp+0x228 | `0x6649477  movss [rbp+0x228],xmm0` | default = 1.0f | [V] |
| 0x664947f | 16 | write 16 bytes rbp+0x238 | `0x664947f  movups [rbp+0x238],xmm1` | write 16 bytes rbp+0x238 | [V] |
| 0x6649486 | 16 | write 16 bytes rbp+0x248 | `0x6649486  movups [rbp+0x248],xmm2` | write 16 bytes rbp+0x248 | [V] |
| 0x664948d | 16 | write 16 bytes rbp+0x258 | `0x664948d  movups [rbp+0x258],xmm3` | write 16 bytes rbp+0x258 | [V] |
| 0x6649494 | 16 | write 16 bytes rbp+0x268 | `0x6649494  movups [rbp+0x268],xmm4` | write 16 bytes rbp+0x268 | [V] |
| 0x664949b | 1 | write rbp+0x278 | `0x664949b  mov byte ptr [rbp+0x278],0` | - | [V] |
| 0x66494a2 | 16 | read 16 bytes rbp+0x140 | `0x66494a2  movups xmm0,[rbp+0x140]` | read 16 bytes rbp+0x140 | [V] |
| 0x66494a9 | 16 | write 16 bytes rbp+0x280 | `0x66494a9  movups [rbp+0x280],xmm0` | write 16 bytes rbp+0x280 | [V] |
| 0x66494b0 | 8 | read rbp+0x150 | `0x66494b0  mov eax,[rbp+0x150]` | read rbp+0x150 | [V] |
| 0x66494b6 | - | - | `0x66494b6  mov [rbp+0x290],eax` | - | [V] |
| 0x66494bc | 4 | - | `0x66494bc  movzx eax,byte ptr [rbp+0x154]` | - | [V] |
| 0x66494c3 | - | - | `0x66494c3  mov [rbp+0x294],al` | - | [V] |
| 0x66494c9 | 16 | read 16 bytes rbp+0x158 | `0x66494c9  movups xmm0,[rbp+0x158]` | read 16 bytes rbp+0x158 | [V] |
| 0x66494d0 | 16 | write 16 bytes rbp+0x298 | `0x66494d0  movups [rbp+0x298],xmm0` | write 16 bytes rbp+0x298 | [V] |
| 0x66494d7 | 16 | read 16 bytes rbp+0x168 | `0x66494d7  movups xmm0,[rbp+0x168]` | read 16 bytes rbp+0x168 | [V] |
| 0x66494de | 16 | read 16 bytes rbp+0x178 | `0x66494de  movups xmm1,[rbp+0x178]` | read 16 bytes rbp+0x178 | [V] |
| 0x66494e5 | 16 | read 16 bytes rbp+0x187 | `0x66494e5  movups xmm2,[rbp+0x187]` | read 16 bytes rbp+0x187 | [V] |
| 0x66494ec | 16 | write 16 bytes rbp+0x2a8 | `0x66494ec  movups [rbp+0x2A8],xmm0` | write 16 bytes rbp+0x2a8 | [V] |
| 0x66494f3 | 16 | write 16 bytes rbp+0x2b8 | `0x66494f3  movups [rbp+0x2B8],xmm1` | write 16 bytes rbp+0x2b8 | [V] |
| 0x66494fa | 16 | write 16 bytes rbp+0x2c7 | `0x66494fa  movups [rbp+0x2C7],xmm2` | write 16 bytes rbp+0x2c7 | [V] |
| 0x6649501 | 8 | read rbp+0x7c0 | `0x6649501  mov rax,[rbp+0x7C0]` | read rbp+0x7c0 | [V] |
| 0x6649508 | - | - | `0x6649508  mov [rbp+0x2D8],rax` | - | [V] |
| 0x664950f | 8 | - | `0x664950f  lea rdi,[rbp+0x2E0]` | - | [V] |
| 0x6649516 | - | - | `0x6649516  mov rcx,rdi` | - | [V] |
| 0x6649519 | - | - | `0x6649519  mov rdx,r14` | - | [V] |
| 0x664951c | 5 | call 0xE869FF0 | `0x664951c  call 0xE869FF0` | call sub_e869ff0 (transform copy packet (4x16 bytes + 2 qwords)) | [V] |
| 0x6649521 | - | - | `0x6649521  nop` | - | [V] |
| 0x6649522 | 8 | read rbp+0x840 | `0x6649522  mov rax,[rbp+0x840]` | read rbp+0x840 | [V] |
| 0x6649529 | - | - | `0x6649529  mov [rbp+0x358],rax` | - | [V] |
| 0x6649530 | 8 | write rbp+0x840 | `0x6649530  mov qword ptr [rbp+0x840],0` | - | [V] |
| 0x664953b | - | - | `0x664953b  mov [rbp+0x360],si` | - | [V] |
| 0x6649542 | 16 | read 16 bytes rbp+0x740 | `0x6649542  movaps xmm0,[rbp+0x740]` | read 16 bytes rbp+0x740 | [V] |
| 0x6649549 | 16 | read 16 bytes rbp+0x750 | `0x6649549  movaps xmm1,[rbp+0x750]` | read 16 bytes rbp+0x750 | [V] |
| 0x6649550 | 8 | write rbp+0x748 | `0x6649550  mov qword ptr [rbp+0x748],0` | clear [rbp+0x748] | [V] |
| 0x664955b | 16 | write 16 bytes rbp+0x368 | `0x664955b  movups [rbp+0x368],xmm0` | write 16 bytes rbp+0x368 | [V] |
| 0x6649562 | 16 | - | `0x6649562  xorps xmm0,xmm0` | - | [V] |
| 0x6649565 | 16 | write 16 bytes rbp+0x750 | `0x6649565  movaps [rbp+0x750],xmm0` | clear [rbp+0x750] = 0 | [V] |
| 0x664956c | 16 | write 16 bytes rbp+0x378 | `0x664956c  movups [rbp+0x378],xmm1` | write 16 bytes rbp+0x378 | [V] |
| 0x6649573 | 8 | read rbp+0x760 | `0x6649573  mov rax,[rbp+0x760]` | read rbp+0x760 | [V] |
| 0x664957a | - | - | `0x664957a  mov [rbp+0x388],rax` | - | [V] |
| 0x6649581 | 1 | write rbp+0x3a0 | `0x6649581  mov byte ptr [rbp+0x3A0],0xFF` | - | [V] |
| 0x6649588 | 4 | - | `0x6649588  movzx eax,byte ptr [rbp+0x778]` | - | [V] |
| 0x664958f | 8 | - | `0x664958f  cmp rax,3` | - | [V] |
| 0x6649593 | 2 | - | `0x6649593  ja 0x664CDF1` | branch to 0x664cdf1 | [V] |
| 0x6649599 | 8 | - | `0x6649599  lea rcx,[rbp+0x390]` | - | [V] |
| 0x66495a0 | 8 | - | `0x66495a0  lea rdx,[0xF2BF37C]` | jump-table / string base 0xf2bf37c | [V] |
| 0x66495a7 | 8 | read 4 bytes rdx+rax*4 (jump table) | `0x66495a7  movsxd r8,[rdx+rax*4]` | read 4 bytes rdx+rax*4 (jump table entry) | [V] |
| 0x66495ab | 8 | - | `0x66495ab  add r8,rdx` | - | [V] |
| 0x66495ae | 2 | jump r8 | `0x66495ae  jmp r8` | indirect jump via jump table (r8) | [V] |
| 0x66495b1 | 8 | read rbp+0x768 | `0x66495b1  mov rcx,[rbp+0x768]` | read rbp+0x768 | [V] |
| 0x66495b8 | - | - | `0x66495b8  mov [rbp+0x390],rcx` | - | [V] |
| 0x66495bf | 5 | jump 0x664CDEB | `0x66495bf  jmp 0x664CDEB` | jump to 0x664cdeb | [V] |
| 0x66495c4 | 8 | - | `0x66495c4  lea rcx,[rbp+0x768]` | - | [V] |
| 0x66495cb | 16 | read 16 bytes rcx | `0x66495cb  movups xmm0,[rcx]` | read 16 bytes rcx | [V] |
| 0x66495ce | 16 | write 16 bytes r14 | `0x66495ce  movups [r14],xmm0` | write 16 bytes r14 | [V] |
| 0x66495d2 | 5 | jump 0x664B8BD | `0x66495d2  jmp 0x664B8BD` | jump to 0x664b8bd | [V] |
| 0x66495d7 | 16 | write 16 bytes r14 | `0x66495d7  movups [r14],xmm0` | write 16 bytes r14 | [V] |
| 0x66495db | 8 | read rbp+0x770 | `0x66495db  mov rcx,[rbp+0x770]` | read rbp+0x770 | [V] |
| 0x66495e2 | 8 | - | `0x66495e2  test rcx,rcx` | - | [V] |
| 0x66495e5 | 2 | - | `0x66495e5  je 0x664B8A6` | branch to 0x664b8a6 | [V] |
| 0x66495eb | 4 | read+write rcx+8 | `0x66495eb  lock inc dword ptr [rcx+8]` | shared_ptr refcount adjust (read+write rcx+8) | [V] |
| 0x66495ef | 8 | read rbp+0x770 | `0x66495ef  mov rcx,[rbp+0x770]` | read rbp+0x770 | [V] |
| 0x66495f6 | 5 | jump 0x664B8A8 | `0x66495f6  jmp 0x664B8A8` | jump to 0x664b8a8 | [V] |
| 0x66495fb | 8 | - | `0x66495fb  add r8,rax` | - | [V] |
| 0x66495fe | 8 | - | `0x66495fe  lea r9,[rax+rcx]` | - | [V] |
| 0x6649602 | 8 | - | `0x6649602  cmp r8,r9` | - | [V] |
| 0x6649605 | 2 | - | `0x6649605  jae short 0x6649641` | - | [V] |
| 0x6649607 | 4 | - | `0x6649607  sub r8d,eax` | - | [V] |
| 0x664960a | 4 | - | `0x664960a  shr r8d,4` | - | [V] |
| 0x664960e | - | - | `0x664960e  mov [rbp+0x7C0],r8w` | - | [V] |
| 0x6649616 | 1 | write rbp+0x7c2 | `0x6649616  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x664961d | 8 | - | `0x664961d  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x6649624 | 8 | - | `0x6649624  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x664962b | - | - | `0x664962b  mov rcx,r15` | - | [V] |
| 0x664962e | 5 | call 0x5679DB0 | `0x664962e  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x6649633 | - | - | `0x6649633  nop` | - | [V] |
| 0x6649634 | 8 | read rbp+0x48 | `0x6649634  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x6649638 | 4 | - | `0x6649638  movzx edx,word ptr [rbp+0x52]` | - | [V] |
| 0x664963c | - | - | `0x664963c  mov ecx,edx` | - | [V] |
| 0x664963e | 8 | - | `0x664963e  shl ecx,4` | - | [V] |
| 0x6649641 | 16 | read 16 bytes rdi+0x8c | `0x6649641  movups xmm0,[rdi+0x8C]` | read 16 bytes rdi+0x8c | [V] |
| 0x6649648 | 16 | write 16 bytes rbp+0x220 | `0x6649648  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x664964f | 8 | write rbp+0x5a0 | `0x664964f  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x664965a | - | - | `0x664965a  mov [rbp+0x5A8],r14` | - | [V] |
| 0x6649661 | - | - | `0x6649661  mov r8,rax` | - | [V] |
| 0x6649664 | 4 | - | `0x6649664  test dx,dx` | - | [V] |
| 0x6649667 | 2 | - | `0x6649667  je short 0x664968B` | - | [V] |
| 0x6649669 | 8 | read 0x129f8320 | `0x6649669  mov r9,[0x129F8320]` | read 0x129f8320 | [V] |
| 0x6649670 | 4 | - | `0x6649670  xor r8d,r8d` | - | [V] |
| 0x6649673 | 8 | read rax+r8 | `0x6649673  mov r10,[rax+r8]` | read rax+r8 | [V] |
| 0x6649677 | - | read r10+0x28 | `0x6649677  cmp [r10+0x28],r9` | read r10+0x28 (compare) | [V] |
| 0x664967b | 2 | - | `0x664967b  je short 0x6649688` | - | [V] |
| 0x664967d | 8 | - | `0x664967d  add r8,0x10` | - | [V] |
| 0x6649681 | 8 | - | `0x6649681  cmp rcx,r8` | - | [V] |
| 0x6649684 | 2 | - | `0x6649684  jne short 0x6649673` | - | [V] |
| 0x6649686 | 2 | jump short | `0x6649686  jmp short 0x66496CE` | jump to 0x66496ce | [V] |
| 0x6649688 | 8 | - | `0x6649688  add r8,rax` | - | [V] |
| 0x664968b | 8 | - | `0x664968b  lea r9,[rax+rcx]` | - | [V] |
| 0x664968f | 8 | - | `0x664968f  cmp r8,r9` | - | [V] |
| 0x6649692 | 2 | - | `0x6649692  jae short 0x66496CE` | - | [V] |
| 0x6649694 | 4 | - | `0x6649694  sub r8d,eax` | - | [V] |
| 0x6649697 | 4 | - | `0x6649697  shr r8d,4` | - | [V] |
| 0x664969b | - | - | `0x664969b  mov [rbp+0x7C0],r8w` | - | [V] |
| 0x66496a3 | 1 | write rbp+0x7c2 | `0x66496a3  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x66496aa | 8 | - | `0x66496aa  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x66496b1 | 8 | - | `0x66496b1  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x66496b8 | - | - | `0x66496b8  mov rcx,r15` | - | [V] |
| 0x66496bb | 5 | call 0x5679DB0 | `0x66496bb  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x66496c0 | - | - | `0x66496c0  nop` | - | [V] |
| 0x66496c1 | 8 | read rbp+0x48 | `0x66496c1  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x66496c5 | 4 | - | `0x66496c5  movzx edx,word ptr [rbp+0x52]` | - | [V] |
| 0x66496c9 | - | - | `0x66496c9  mov ecx,edx` | - | [V] |
| 0x66496cb | 8 | - | `0x66496cb  shl ecx,4` | - | [V] |
| 0x66496ce | 8 | read 8 bytes rdi+0x9c | `0x66496ce  movsd xmm0,[rdi+0x9C]` | read 8 bytes rdi+0x9c | [V] |
| 0x66496d6 | 16 | write 16 bytes rbp+0x220 | `0x66496d6  movups [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x66496dd | 8 | write rbp+0x5a0 | `0x66496dd  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x66496e8 | - | - | `0x66496e8  mov [rbp+0x5A8],r14` | - | [V] |
| 0x66496ef | - | - | `0x66496ef  mov r8,rax` | - | [V] |
| 0x66496f2 | 4 | - | `0x66496f2  test dx,dx` | - | [V] |
| 0x66496f5 | 2 | - | `0x66496f5  je short 0x6649719` | - | [V] |
| 0x66496f7 | 8 | read 0x129f8328 | `0x66496f7  mov r9,[0x129F8328]` | read 0x129f8328 | [V] |
| 0x66496fe | 4 | - | `0x66496fe  xor r8d,r8d` | - | [V] |
| 0x6649701 | 8 | read rax+r8 | `0x6649701  mov r10,[rax+r8]` | read rax+r8 | [V] |
| 0x6649705 | - | read r10+0x28 | `0x6649705  cmp [r10+0x28],r9` | read r10+0x28 (compare) | [V] |
| 0x6649709 | 2 | - | `0x6649709  je short 0x6649716` | - | [V] |
| 0x664970b | 8 | - | `0x664970b  add r8,0x10` | - | [V] |
| 0x664970f | 8 | - | `0x664970f  cmp rcx,r8` | - | [V] |
| 0x6649712 | 2 | - | `0x6649712  jne short 0x6649701` | - | [V] |
| 0x6649714 | 2 | jump short | `0x6649714  jmp short 0x664975C` | jump to 0x664975c | [V] |
| 0x6649716 | 8 | - | `0x6649716  add r8,rax` | - | [V] |
| 0x6649719 | 8 | - | `0x6649719  lea r9,[rax+rcx]` | - | [V] |
| 0x664971d | 8 | - | `0x664971d  cmp r8,r9` | - | [V] |
| 0x6649720 | 2 | - | `0x6649720  jae short 0x664975C` | - | [V] |
| 0x6649722 | 4 | - | `0x6649722  sub r8d,eax` | - | [V] |
| 0x6649725 | 4 | - | `0x6649725  shr r8d,4` | - | [V] |
| 0x6649729 | - | - | `0x6649729  mov [rbp+0x7C0],r8w` | - | [V] |
| 0x6649731 | 1 | write rbp+0x7c2 | `0x6649731  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x6649738 | 8 | - | `0x6649738  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x664973f | 8 | - | `0x664973f  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x6649746 | - | - | `0x6649746  mov rcx,r15` | - | [V] |
| 0x6649749 | 5 | call 0x5679DB0 | `0x6649749  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x664974e | - | - | `0x664974e  nop` | - | [V] |
| 0x664974f | 8 | read rbp+0x48 | `0x664974f  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x6649753 | 4 | - | `0x6649753  movzx edx,word ptr [rbp+0x52]` | - | [V] |
| 0x6649757 | - | - | `0x6649757  mov ecx,edx` | - | [V] |
| 0x6649759 | 8 | - | `0x6649759  shl ecx,4` | - | [V] |
| 0x664975c | 16 | read 16 bytes rdi+0xa4 | `0x664975c  movups xmm0,[rdi+0xA4]` | read 16 bytes rdi+0xa4 | [V] |
| 0x6649763 | 16 | write 16 bytes rbp+0x220 | `0x6649763  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x664976a | 8 | write rbp+0x5a0 | `0x664976a  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x6649775 | - | - | `0x6649775  mov [rbp+0x5A8],r14` | - | [V] |
| 0x664977c | - | - | `0x664977c  mov r8,rax` | - | [V] |
| 0x664977f | 4 | - | `0x664977f  test dx,dx` | - | [V] |
| 0x6649782 | 2 | - | `0x6649782  je short 0x66497A6` | - | [V] |
| 0x6649784 | 8 | read 0x129f8330 | `0x6649784  mov r9,[0x129F8330]` | read 0x129f8330 | [V] |
| 0x664978b | 4 | - | `0x664978b  xor r8d,r8d` | - | [V] |
| 0x664978e | 8 | read rax+r8 | `0x664978e  mov r10,[rax+r8]` | read rax+r8 | [V] |
| 0x6649792 | - | read r10+0x28 | `0x6649792  cmp [r10+0x28],r9` | read r10+0x28 (compare) | [V] |
| 0x6649796 | 2 | - | `0x6649796  je short 0x66497A3` | - | [V] |
| 0x6649798 | 8 | - | `0x6649798  add r8,0x10` | - | [V] |
| 0x664979c | 8 | - | `0x664979c  cmp rcx,r8` | - | [V] |
| 0x664979f | 2 | - | `0x664979f  jne short 0x664978E` | - | [V] |
| 0x66497a1 | 2 | jump short | `0x66497a1  jmp short 0x66497E9` | jump to 0x66497e9 | [V] |
| 0x66497a3 | 8 | - | `0x66497a3  add r8,rax` | - | [V] |
| 0x66497a6 | 8 | - | `0x66497a6  lea r9,[rax+rcx]` | - | [V] |
| 0x66497aa | 8 | - | `0x66497aa  cmp r8,r9` | - | [V] |
| 0x66497ad | 2 | - | `0x66497ad  jae short 0x66497E9` | - | [V] |
| 0x66497af | 4 | - | `0x66497af  sub r8d,eax` | - | [V] |
| 0x66497b2 | 4 | - | `0x66497b2  shr r8d,4` | - | [V] |
| 0x66497b6 | - | - | `0x66497b6  mov [rbp+0x7C0],r8w` | - | [V] |
| 0x66497be | 1 | write rbp+0x7c2 | `0x66497be  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x66497c5 | 8 | - | `0x66497c5  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x66497cc | 8 | - | `0x66497cc  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x66497d3 | - | - | `0x66497d3  mov rcx,r15` | - | [V] |
| 0x66497d6 | 5 | call 0x5679DB0 | `0x66497d6  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x66497db | - | - | `0x66497db  nop` | - | [V] |
| 0x66497dc | 8 | read rbp+0x48 | `0x66497dc  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x66497e0 | 4 | - | `0x66497e0  movzx edx,word ptr [rbp+0x52]` | - | [V] |
| 0x66497e4 | - | - | `0x66497e4  mov ecx,edx` | - | [V] |
| 0x66497e6 | 8 | - | `0x66497e6  shl ecx,4` | - | [V] |
| 0x66497e9 | 16 | read 16 bytes rdi+0xb4 | `0x66497e9  movups xmm0,[rdi+0xB4]` | read 16 bytes rdi+0xb4 | [V] |
| 0x66497f0 | 16 | write 16 bytes rbp+0x220 | `0x66497f0  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x66497f7 | 8 | write rbp+0x5a0 | `0x66497f7  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x6649802 | - | - | `0x6649802  mov [rbp+0x5A8],r14` | - | [V] |
| 0x6649809 | - | - | `0x6649809  mov r8,rax` | - | [V] |
| 0x664980c | 4 | - | `0x664980c  test dx,dx` | - | [V] |
| 0x664980f | 2 | - | `0x664980f  je short 0x6649837` | - | [V] |
| 0x6649811 | 8 | read 0x129f8348 | `0x6649811  mov r9,[0x129F8348]` | read 0x129f8348 | [V] |
| 0x6649818 | 4 | - | `0x6649818  xor r8d,r8d` | - | [V] |
| 0x664981b | 8 | read rax+r8 | `0x664981b  mov r10,[rax+r8]` | read rax+r8 | [V] |
| 0x664981f | - | read r10+0x28 | `0x664981f  cmp [r10+0x28],r9` | read r10+0x28 (compare) | [V] |
| 0x6649823 | 2 | - | `0x6649823  je short 0x6649834` | - | [V] |
| 0x6649825 | 8 | - | `0x6649825  add r8,0x10` | - | [V] |
| 0x6649829 | 8 | - | `0x6649829  cmp rcx,r8` | - | [V] |
| 0x664982c | 2 | - | `0x664982c  jne short 0x664981B` | - | [V] |
| 0x664982e | - | - | `0x664982e  mov dx,1` | - | [V] |
| 0x6649832 | 2 | jump short | `0x6649832  jmp short 0x664987A` | jump to 0x664987a | [V] |
| 0x6649834 | 8 | - | `0x6649834  add r8,rax` | - | [V] |
| 0x6649837 | 8 | - | `0x6649837  lea r9,[rax+rcx]` | - | [V] |
| 0x664983b | 8 | - | `0x664983b  cmp r8,r9` | - | [V] |
| 0x664983e | 2 | - | `0x664983e  jae short 0x664987A` | - | [V] |
| 0x6649840 | 4 | - | `0x6649840  sub r8d,eax` | - | [V] |
| 0x6649843 | 4 | - | `0x6649843  shr r8d,4` | - | [V] |
| 0x6649847 | - | - | `0x6649847  mov [rbp+0x7C0],r8w` | - | [V] |
| 0x664984f | 1 | write rbp+0x7c2 | `0x664984f  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x6649856 | 8 | - | `0x6649856  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x664985d | 8 | - | `0x664985d  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x6649864 | - | - | `0x6649864  mov rcx,r15` | - | [V] |
| 0x6649867 | 5 | call 0x5679DB0 | `0x6649867  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x664986c | - | - | `0x664986c  nop` | - | [V] |
| 0x664986d | 8 | read rbp+0x48 | `0x664986d  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x6649871 | 4 | - | `0x6649871  movzx edx,word ptr [rbp+0x52]` | - | [V] |
| 0x6649875 | - | - | `0x6649875  mov ecx,edx` | - | [V] |
| 0x6649877 | 8 | - | `0x6649877  shl ecx,4` | - | [V] |
| 0x664987a | 4 | read 4 bytes rdi+0xcc | `0x664987a  movss xmm0,[rdi+0xCC]` | read 4 bytes rdi+0xcc | [V] |
| 0x6649882 | 8 | read 8 bytes rdi+0xc4 | `0x6649882  movsd xmm1,[rdi+0xC4]` | read 8 bytes rdi+0xc4 | [V] |
| 0x664988a | 8 | write 8 bytes rbp+0x220 | `0x664988a  movsd [rbp+0x220],xmm1` | write 8 bytes rbp+0x220 | [V] |
| 0x6649892 | 4 | write 4 bytes rbp+0x228 | `0x6649892  movss [rbp+0x228],xmm0` | default = 1.0f | [V] |
| 0x664989a | 4 | write rbp+0x22c | `0x664989a  mov dword ptr [rbp+0x22C],0` | - | [V] |
| 0x66498a4 | 8 | write rbp+0x5a0 | `0x66498a4  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x66498af | - | - | `0x66498af  mov [rbp+0x5A8],r14` | - | [V] |
| 0x66498b6 | - | - | `0x66498b6  mov r8,rax` | - | [V] |
| 0x66498b9 | 4 | - | `0x66498b9  test dx,dx` | - | [V] |
| 0x66498bc | 2 | - | `0x66498bc  je short 0x66498E0` | - | [V] |
| 0x66498be | 8 | read 0x129f8350 | `0x66498be  mov rdx,[0x129F8350]` | read 0x129f8350 | [V] |
| 0x66498c5 | - | - | `0x66498c5  mov r9,rcx` | - | [V] |
| 0x66498c8 | - | - | `0x66498c8  mov r8,rax` | - | [V] |
| 0x66498cb | 8 | read r8 | `0x66498cb  mov r10,[r8]` | read r8 | [V] |
| 0x66498ce | - | read r10+0x28 | `0x66498ce  cmp [r10+0x28],rdx` | read r10+0x28 (compare) | [V] |
| 0x66498d2 | 2 | - | `0x66498d2  je short 0x66498E0` | - | [V] |
| 0x66498d4 | 8 | - | `0x66498d4  add r8,0x10` | - | [V] |
| 0x66498d8 | 8 | - | `0x66498d8  add r9,0xFFFFFFFFFFFFFFF0` | - | [V] |
| 0x66498dc | 2 | - | `0x66498dc  jne short 0x66498CB` | - | [V] |
| 0x66498de | 2 | jump short | `0x66498de  jmp short 0x6649915` | jump to 0x6649915 | [V] |
| 0x66498e0 | 8 | - | `0x66498e0  add rcx,rax` | - | [V] |
| 0x66498e3 | 8 | - | `0x66498e3  cmp r8,rcx` | - | [V] |
| 0x66498e6 | 2 | - | `0x66498e6  jae short 0x6649915` | - | [V] |
| 0x66498e8 | 4 | - | `0x66498e8  sub r8d,eax` | - | [V] |
| 0x66498eb | 4 | - | `0x66498eb  shr r8d,4` | - | [V] |
| 0x66498ef | - | - | `0x66498ef  mov [rbp+0x7C0],r8w` | - | [V] |
| 0x66498f7 | 1 | write rbp+0x7c2 | `0x66498f7  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x66498fe | 8 | - | `0x66498fe  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x6649905 | 8 | - | `0x6649905  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x664990c | - | - | `0x664990c  mov rcx,r15` | - | [V] |
| 0x664990f | 5 | call 0x5679DB0 | `0x664990f  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x6649914 | - | - | `0x6649914  nop` | - | [V] |
| 0x6649915 | 8 | - | `0x6649915  lea r12,[rdi+0x78]` | - | [V] |
| 0x6649919 | 8 | read r12 | `0x6649919  mov rax,[r12]` | read r12 | [V] |
| 0x664991d | 8 | read rax+0x40 | `0x664991d  mov rcx,[rax+0x40]` | read rax+0x40 | [V] |
| 0x6649921 | 4 | - | `0x6649921  xor eax,eax` | - | [V] |
| 0x6649923 | - | - | `0x6649923  cmp byte ptr [rcx+0x1AD],0` | - | [V] |
| 0x664992a | 1 | - | `0x664992a  sete al` | - | [V] |
| 0x664992d | - | - | `0x664992d  cmp byte ptr [rcx+0x1AE],0` | - | [V] |
| 0x6649934 | 8 | - | `0x6649934  lea edx,[rax+4]` | - | [V] |
| 0x6649937 | 4 | - | `0x6649937  movzx edx,dl` | - | [V] |
| 0x664993a | 4 | - | `0x664993a  cmovne edx,eax` | - | [V] |
| 0x664993d | 8 | - | `0x664993d  lea eax,[rdx+0x10]` | - | [V] |
| 0x6649940 | - | - | `0x6649940  cmp byte ptr [rcx+0x1AF],0` | - | [V] |
| 0x6649947 | 4 | - | `0x6649947  movzx eax,al` | - | [V] |
| 0x664994a | 4 | - | `0x664994a  cmovne eax,edx` | - | [V] |
| 0x664994d | 4 | - | `0x664994d  movzx ecx,byte ptr [rcx+0x1AC]` | - | [V] |
| 0x6649954 | 4 | - | `0x6649954  test cl,0xFB` | - | [V] |
| 0x6649957 | 2 | - | `0x6649957  jne short 0x6649961` | - | [V] |
| 0x6649959 | 4 | - | `0x6649959  or al,0x40` | - | [V] |
| 0x664995b | - | - | `0x664995b  mov cx,0x500` | - | [V] |
| 0x664995f | 2 | jump short | `0x664995f  jmp short 0x6649963` | jump to 0x6649963 | [V] |
| 0x6649961 | 4 | - | `0x6649961  xor ecx,ecx` | - | [V] |
| 0x6649963 | 8 | read rbp+0x58 | `0x6649963  mov rdx,[rbp+0x58]` | read rbp+0x58 | [V] |
| 0x6649967 | 4 | - | `0x6649967  movzx r10d,word ptr [rbp+0x62]` | - | [V] |
| 0x664996c | - | - | `0x664996c  mov r8d,r10d` | - | [V] |
| 0x664996f | 4 | - | `0x664996f  shl r8d,4` | - | [V] |
| 0x6649973 | 8 | - | `0x6649973  lea r8,[r8+r8*2]` | - | [V] |
| 0x6649977 | - | - | `0x6649977  mov r9,rdx` | - | [V] |
| 0x664997a | 8 | - | `0x664997a  test r10,r10` | - | [V] |
| 0x664997d | 2 | - | `0x664997d  je short 0x66499A1` | - | [V] |
| 0x664997f | 8 | read 0x129f8318 | `0x664997f  mov r10,[0x129F8318]` | read 0x129f8318 | [V] |
| 0x6649986 | - | - | `0x6649986  mov r11,r8` | - | [V] |
| 0x6649989 | - | - | `0x6649989  mov r9,rdx` | - | [V] |
| 0x664998c | 8 | read r9 | `0x664998c  mov rsi,[r9]` | read r9 | [V] |
| 0x664998f | - | read rsi+0x28 | `0x664998f  cmp [rsi+0x28],r10` | read rsi+0x28 (compare) | [V] |
| 0x6649993 | 2 | - | `0x6649993  je short 0x66499A1` | - | [V] |
| 0x6649995 | 8 | - | `0x6649995  add r9,0x30` | - | [V] |
| 0x6649999 | 8 | - | `0x6649999  add r11,0xFFFFFFFFFFFFFFD0` | - | [V] |
| 0x664999d | 2 | - | `0x664999d  jne short 0x664998C` | - | [V] |
| 0x664999f | 2 | jump short | `0x664999f  jmp short 0x6649A10` | jump to 0x6649a10 | [V] |
| 0x66499a1 | 8 | - | `0x66499a1  add r8,rdx` | - | [V] |
| 0x66499a4 | 8 | - | `0x66499a4  cmp r9,r8` | - | [V] |
| 0x66499a7 | 2 | - | `0x66499a7  jae short 0x6649A10` | - | [V] |
| 0x66499a9 | 8 | - | `0x66499a9  lea r8,[rdi+8]` | - | [V] |
| 0x66499ad | 4 | - | `0x66499ad  sub r9d,edx` | - | [V] |
| 0x66499b0 | 4 | - | `0x66499b0  shr r9d,4` | - | [V] |
| 0x66499b4 | 4 | - | `0x66499b4  imul edx,r9d,0xFFFFAAAB` | - | [V] |
| 0x66499bb | - | - | `0x66499bb  mov [rbp+0x5A0],dx` | - | [V] |
| 0x66499c2 | 1 | write rbp+0x5a2 | `0x66499c2  mov byte ptr [rbp+0x5A2],1` | - | [V] |
| 0x66499c9 | 4 | - | `0x66499c9  movzx eax,al` | - | [V] |
| 0x66499cc | 4 | - | `0x66499cc  movzx ecx,cx` | - | [V] |
| 0x66499cf | 4 | - | `0x66499cf  or ecx,eax` | - | [V] |
| 0x66499d1 | - | - | `0x66499d1  mov [rbp+0x220],cx` | - | [V] |
| 0x66499d8 | 4 | write rbp+0x224 | `0x66499d8  mov dword ptr [rbp+0x224],0` | - | [V] |
| 0x66499e2 | 1 | write rbp+0x228 | `0x66499e2  mov byte ptr [rbp+0x228],0` | - | [V] |
| 0x66499e9 | 1 | write rbp+0x22c | `0x66499e9  mov byte ptr [rbp+0x22C],1` | - | [V] |
| 0x66499f0 | 4 | write rsp+0x20 | `0x66499f0  mov dword ptr [rsp+0x20],0` | - | [V] |
| 0x66499f8 | 8 | - | `0x66499f8  lea rcx,[rbp+0x10]` | - | [V] |
| 0x66499fc | 8 | - | `0x66499fc  lea rdx,[rbp+0x5A0]` | - | [V] |
| 0x6649a03 | 8 | - | `0x6649a03  lea r9,[rbp+0x220]` | - | [V] |
| 0x6649a0a | 5 | call 0xBCABA00 | `0x6649a0a  call 0xBCABA00` | call sub_bcaba00 (helper) | [V] |
| 0x6649a0f | - | - | `0x6649a0f  nop` | - | [V] |
| 0x6649a10 | 8 | read 0x129f9350 | `0x6649a10  mov eax,[0x129F9350]` | read 0x129f9350 | [V] |
| 0x6649a16 | 8 | read 0x128767c8 | `0x6649a16  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x6649a1c | - | - | `0x6649a1c  mov rdx,gs:[0x58]` | - | [V] |
| 0x6649a25 | 8 | read rdx+rcx*8 | `0x6649a25  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x6649a29 | 4 | - | `0x6649a29  cmp eax,[rcx+4]` | - | [V] |
| 0x6649a2f | 2 | - | `0x6649a2f  jg 0x664F493` | branch to 0x664f493 | [V] |
| 0x6649a35 | 16 | read 16 bytes rbx+0x3e0 | `0x6649a35  movups xmm0,[rbx+0x3E0]` | read 16 bytes rbx+0x3e0 | [V] |
| 0x6649a3c | 16 | write 16 bytes rbp+0x220 | `0x6649a3c  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x6649a43 | 8 | write rbp+0x5a0 | `0x6649a43  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x6649a4e | - | - | `0x6649a4e  mov [rbp+0x5A8],r14` | - | [V] |
| 0x6649a55 | 8 | read rbp+0x48 | `0x6649a55  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x6649a59 | 4 | - | `0x6649a59  movzx r8d,word ptr [rbp+0x52]` | - | [V] |
| 0x6649a5e | - | - | `0x6649a5e  mov edx,r8d` | - | [V] |
| 0x6649a61 | 8 | - | `0x6649a61  shl edx,4` | - | [V] |
| 0x6649a64 | - | - | `0x6649a64  mov rcx,rax` | - | [V] |
| 0x6649a67 | 4 | - | `0x6649a67  test r8d,r8d` | - | [V] |
| 0x6649a6a | 2 | - | `0x6649a6a  je short 0x6649A8E` | - | [V] |
| 0x6649a6c | 8 | read 0x129f9348 | `0x6649a6c  mov r8,[0x129F9348]` | read 0x129f9348 | [V] |
| 0x6649a73 | - | - | `0x6649a73  mov r9,rdx` | - | [V] |
| 0x6649a76 | - | - | `0x6649a76  mov rcx,rax` | - | [V] |
| 0x6649a79 | 8 | read rcx | `0x6649a79  mov r10,[rcx]` | read rcx | [V] |
| 0x6649a7c | - | read r10+0x28 | `0x6649a7c  cmp [r10+0x28],r8` | read r10+0x28 (compare) | [V] |
| 0x6649a80 | 2 | - | `0x6649a80  je short 0x6649A8E` | - | [V] |
| 0x6649a82 | 8 | - | `0x6649a82  add rcx,0x10` | - | [V] |
| 0x6649a86 | 8 | - | `0x6649a86  add r9,0xFFFFFFFFFFFFFFF0` | - | [V] |
| 0x6649a8a | 2 | - | `0x6649a8a  jne short 0x6649A79` | - | [V] |
| 0x6649a8c | 2 | jump short | `0x6649a8c  jmp short 0x6649AC0` | jump to 0x6649ac0 | [V] |
| 0x6649a8e | 8 | - | `0x6649a8e  add rdx,rax` | - | [V] |
| 0x6649a91 | 8 | - | `0x6649a91  cmp rcx,rdx` | - | [V] |
| 0x6649a94 | 2 | - | `0x6649a94  jae short 0x6649AC0` | - | [V] |
| 0x6649a96 | 4 | - | `0x6649a96  sub ecx,eax` | - | [V] |
| 0x6649a98 | 8 | - | `0x6649a98  shr ecx,4` | - | [V] |
| 0x6649a9b | - | - | `0x6649a9b  mov [rbp+0x7C0],cx` | - | [V] |
| 0x6649aa2 | 1 | write rbp+0x7c2 | `0x6649aa2  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x6649aa9 | 8 | - | `0x6649aa9  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x6649ab0 | 8 | - | `0x6649ab0  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x6649ab7 | - | - | `0x6649ab7  mov rcx,r15` | - | [V] |
| 0x6649aba | 5 | call 0x5679DB0 | `0x6649aba  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x6649abf | - | - | `0x6649abf  nop` | - | [V] |
| 0x6649ac0 | 8 | read 0x129f9360 | `0x6649ac0  mov eax,[0x129F9360]` | read 0x129f9360 | [V] |
| 0x6649ac6 | 8 | read 0x128767c8 | `0x6649ac6  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x6649acc | - | - | `0x6649acc  mov rdx,gs:[0x58]` | - | [V] |
| 0x6649ad5 | 8 | read rdx+rcx*8 | `0x6649ad5  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x6649ad9 | 4 | - | `0x6649ad9  cmp eax,[rcx+4]` | - | [V] |
| 0x6649adf | 2 | - | `0x6649adf  jg 0x664F505` | branch to 0x664f505 | [V] |
| 0x6649ae5 | - | - | `0x6649ae5  cmp byte ptr [rdi+0x88],0` | - | [V] |
| 0x6649aec | 2 | - | `0x6649aec  jne short 0x6649AF3` | - | [V] |
| 0x6649aee | 16 | - | `0x6649aee  xorps xmm0,xmm0` | - | [V] |
| 0x6649af1 | 2 | jump short | `0x6649af1  jmp short 0x6649AFB` | jump to 0x6649afb | [V] |
| 0x6649af3 | 4 | read 4 bytes 0xeec8060 | `0x6649af3  movss xmm0,[0xEEC8060]` | read 4 bytes 0xeec8060 | [V] |
| 0x6649afb | 16 | - | `0x6649afb  shufps xmm0,xmm0,0` | - | [V] |
| 0x6649aff | 16 | write 16 bytes rbp+0x220 | `0x6649aff  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x6649b06 | 8 | write rbp+0x5a0 | `0x6649b06  mov qword ptr [rbp+0x5A0],1` | - | [V] |
| 0x6649b11 | - | - | `0x6649b11  mov [rbp+0x5A8],r14` | - | [V] |
| 0x6649b18 | 8 | read rbp+0x48 | `0x6649b18  mov rax,[rbp+0x48]` | read rbp+0x48 | [V] |
| 0x6649b1c | 4 | - | `0x6649b1c  movzx r8d,word ptr [rbp+0x52]` | - | [V] |
| 0x6649b21 | - | - | `0x6649b21  mov edx,r8d` | - | [V] |
| 0x6649b24 | 8 | - | `0x6649b24  shl edx,4` | - | [V] |
| 0x6649b27 | - | - | `0x6649b27  mov rcx,rax` | - | [V] |
| 0x6649b2a | 4 | - | `0x6649b2a  test r8d,r8d` | - | [V] |
| 0x6649b2d | 2 | - | `0x6649b2d  je short 0x6649B51` | - | [V] |
| 0x6649b2f | 8 | read 0x129f9358 | `0x6649b2f  mov r8,[0x129F9358]` | read 0x129f9358 | [V] |
| 0x6649b36 | - | - | `0x6649b36  mov r9,rdx` | - | [V] |
| 0x6649b39 | - | - | `0x6649b39  mov rcx,rax` | - | [V] |
| 0x6649b3c | 8 | read rcx | `0x6649b3c  mov r10,[rcx]` | read rcx | [V] |
| 0x6649b3f | - | read r10+0x28 | `0x6649b3f  cmp [r10+0x28],r8` | read r10+0x28 (compare) | [V] |
| 0x6649b43 | 2 | - | `0x6649b43  je short 0x6649B51` | - | [V] |
| 0x6649b45 | 8 | - | `0x6649b45  add rcx,0x10` | - | [V] |
| 0x6649b49 | 8 | - | `0x6649b49  add r9,0xFFFFFFFFFFFFFFF0` | - | [V] |
| 0x6649b4d | 2 | - | `0x6649b4d  jne short 0x6649B3C` | - | [V] |
| 0x6649b4f | 2 | jump short | `0x6649b4f  jmp short 0x6649B83` | jump to 0x6649b83 | [V] |
| 0x6649b51 | 8 | - | `0x6649b51  add rdx,rax` | - | [V] |
| 0x6649b54 | 8 | - | `0x6649b54  cmp rcx,rdx` | - | [V] |
| 0x6649b57 | 2 | - | `0x6649b57  jae short 0x6649B83` | - | [V] |
| 0x6649b59 | 4 | - | `0x6649b59  sub ecx,eax` | - | [V] |
| 0x6649b5b | 8 | - | `0x6649b5b  shr ecx,4` | - | [V] |
| 0x6649b5e | - | - | `0x6649b5e  mov [rbp+0x7C0],cx` | - | [V] |
| 0x6649b65 | 1 | write rbp+0x7c2 | `0x6649b65  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x6649b6c | 8 | - | `0x6649b6c  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x6649b73 | 8 | - | `0x6649b73  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x6649b7a | - | - | `0x6649b7a  mov rcx,r15` | - | [V] |
| 0x6649b7d | 5 | call 0x5679DB0 | `0x6649b7d  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x6649b82 | - | - | `0x6649b82  nop` | - | [V] |
| 0x6649b83 | 8 | read rdi | `0x6649b83  mov r9,[rdi]` | read rdi | [V] |
| 0x6649b86 | 8 | - | `0x6649b86  lea rcx,[rbp+0x7C0]` | - | [V] |
| 0x6649b8d | 8 | - | `0x6649b8d  lea r8,[rbp+0x10]` | - | [V] |
| 0x6649b91 | 8 | read rbp+0x8a0 | `0x6649b91  mov rdx,[rbp+0x8A0]` | read rbp+0x8a0 | [V] |
| 0x6649b98 | 5 | call 0xBBD7F70 | `0x6649b98  call 0xBBD7F70` | call sub_bbd7f70 (registry emplace) | [V] |
| 0x6649b9d | - | - | `0x6649b9d  nop` | - | [V] |
| 0x6649b9e | - | - | `0x6649b9e  cmp byte ptr [rbp+0x818],0` | - | [V] |
| 0x6649ba5 | 2 | - | `0x6649ba5  je 0x664C2A1` | branch to 0x664c2a1 | [V] |
| 0x6649bab | 8 | read rdi | `0x6649bab  mov rax,[rdi]` | read rdi | [V] |
| 0x6649bae | 4 | - | `0x6649bae  movzx r8d,byte ptr [rax+0x39]` | - | [V] |
| 0x6649bb3 | 8 | - | `0x6649bb3  lea rcx,[rbp+0x740]` | - | [V] |
| 0x6649bba | - | - | `0x6649bba  mov rdx,r12` | - | [V] |
| 0x6649bbd | 5 | call 0x66B2B30 | `0x6649bbd  call 0x66B2B30` | call sub_66b2b30 (entity registry emplace (shared Nametag/Cracks helper)) | [V] |
| 0x6649bc2 | - | - | `0x6649bc2  nop` | - | [V] |
| 0x6649bc3 | 1 | write rbp+0x744 | `0x6649bc3  mov byte ptr [rbp+0x744],0xF` | - | [V] |
| 0x6649bca | - | - | `0x6649bca  cmp byte ptr [rdi+0xE0],0` | - | [V] |
| 0x6649bd1 | 2 | - | `0x6649bd1  je short 0x6649BEC` | - | [V] |
| 0x6649bd3 | 1 | write rbp+0x754 | `0x6649bd3  mov byte ptr [rbp+0x754],1` | - | [V] |
| 0x6649bda | 16 | read 16 bytes rdi+0xd0 | `0x6649bda  movups xmm0,[rdi+0xD0]` | read 16 bytes rdi+0xd0 | [V] |
| 0x6649be1 | 16 | write 16 bytes rbp+0x758 | `0x6649be1  movups [rbp+0x758],xmm0` | write 16 bytes rbp+0x758 | [V] |
| 0x6649be8 | - | - | `0x6649be8  mov al,1` | - | [V] |
| 0x6649bea | 2 | jump short | `0x6649bea  jmp short 0x6649BFA` | jump to 0x6649bfa | [V] |
| 0x6649bec | 4 | - | `0x6649bec  movzx eax,byte ptr [rbp+0x754]` | - | [V] |
| 0x6649bf3 | 16 | read 16 bytes rbp+0x758 | `0x6649bf3  movups xmm0,[rbp+0x758]` | read 16 bytes rbp+0x758 | [V] |
| 0x6649bfa | 4 | write rbp+0x768 | `0x6649bfa  mov dword ptr [rbp+0x768],0xFFFFFFE0` | - | [V] |
| 0x6649c04 | 8 | write rbp+0x76c | `0x6649c04  mov qword ptr [rbp+0x76C],0` | - | [V] |
| 0x6649c0f | 4 | read 4 bytes rdi+0x58 | `0x6649c0f  movss xmm2,[rdi+0x58]` | read 4 bytes rdi+0x58 | [V] |
| 0x6649c14 | 8 | read 8 bytes rdi+0x5c | `0x6649c14  movsd xmm1,[rdi+0x5C]` | read 8 bytes rdi+0x5c | [V] |
| 0x6649c19 | 8 | read 8 bytes rdi+0x18 | `0x6649c19  movsd xmm3,[rdi+0x18]` | read 8 bytes rdi+0x18 | [V] |
| 0x6649c1e | 4 | read 4 bytes rdi+0x1c | `0x6649c1e  movss xmm4,[rdi+0x1C]` | read 4 bytes rdi+0x1c | [V] |
| 0x6649c23 | 4 | write 4 bytes rbp+0x5a0 | `0x6649c23  movss [rbp+0x5A0],xmm3` | write 4 bytes rbp+0x5a0 | [V] |
| 0x6649c2b | 4 | write 4 bytes rbp+0x5a4 | `0x6649c2b  movss [rbp+0x5A4],xmm4` | write 4 bytes rbp+0x5a4 | [V] |
| 0x6649c33 | 16 | read 16 bytes rdi+0x20 | `0x6649c33  movups xmm4,[rdi+0x20]` | read 16 bytes rdi+0x20 | [V] |
| 0x6649c37 | 16 | write 16 bytes rbp+0x5a8 | `0x6649c37  movups [rbp+0x5A8],xmm4` | write 16 bytes rbp+0x5a8 | [V] |
| 0x6649c3e | 16 | read 16 bytes rdi+0x30 | `0x6649c3e  movups xmm5,[rdi+0x30]` | read 16 bytes rdi+0x30 | [V] |
| 0x6649c42 | 16 | write 16 bytes rbp+0x5b8 | `0x6649c42  movups [rbp+0x5B8],xmm5` | write 16 bytes rbp+0x5b8 | [V] |
| 0x6649c49 | 16 | read 16 bytes rdi+0x40 | `0x6649c49  movups xmm6,[rdi+0x40]` | read 16 bytes rdi+0x40 | [V] |
| 0x6649c4d | 16 | write 16 bytes rbp+0x5c8 | `0x6649c4d  movups [rbp+0x5C8],xmm6` | write 16 bytes rbp+0x5c8 | [V] |
| 0x6649c54 | 8 | read 8 bytes rdi+0x50 | `0x6649c54  movsd xmm7,[rdi+0x50]` | read 8 bytes rdi+0x50 | [V] |
| 0x6649c59 | 8 | write 8 bytes rbp+0x5d8 | `0x6649c59  movsd [rbp+0x5D8],xmm7` | write 8 bytes rbp+0x5d8 | [V] |
| 0x6649c61 | 1 | write rbp+0x5e0 | `0x6649c61  mov byte ptr [rbp+0x5E0],0` | - | [V] |
| 0x6649c68 | - | - | `0x6649c68  cmp byte ptr [rbp+0x818],0` | - | [V] |
| 0x6649c6f | 2 | - | `0x6649c6f  je 0x664F714` | branch to 0x664f714 | [V] |
| 0x6649c75 | 8 | - | `0x6649c75  lea rcx,[rbp+0x768]` | - | [V] |
| 0x6649c7c | 8 | read rdi+0xe4 | `0x6649c7c  mov si,[rdi+0xE4]` | read rdi+0xe4 | [V] |
| 0x6649c83 | 8 | read rbp+0x750 | `0x6649c83  mov edx,[rbp+0x750]` | read rbp+0x750 | [V] |
| 0x6649c89 | - | - | `0x6649c89  mov [rbp+0x234],edx` | - | [V] |
| 0x6649c8f | 16 | read 16 bytes rbp+0x740 | `0x6649c8f  movups xmm8,[rbp+0x740]` | read 16 bytes rbp+0x740 | [V] |
| 0x6649c97 | 16 | write 16 bytes rbp+0x224 | `0x6649c97  movups [rbp+0x224],xmm8` | write 16 bytes rbp+0x224 | [V] |
| 0x6649c9f | - | - | `0x6649c9f  mov [rbp+0x238],al` | - | [V] |
| 0x6649ca5 | 16 | write 16 bytes rbp+0x23c | `0x6649ca5  movups [rbp+0x23C],xmm0` | write 16 bytes rbp+0x23c | [V] |
| 0x6649cac | 16 | read 16 bytes rcx | `0x6649cac  movups xmm0,[rcx]` | read 16 bytes rcx | [V] |
| 0x6649caf | 16 | read 16 bytes rcx+0x10 | `0x6649caf  movups xmm8,[rcx+0x10]` | read 16 bytes rcx+0x10 | [V] |
| 0x6649cb4 | 16 | read 16 bytes rcx+0x1f | `0x6649cb4  movups xmm9,[rcx+0x1F]` | read 16 bytes rcx+0x1f | [V] |
| 0x6649cb9 | 16 | write 16 bytes rbp+0x24c | `0x6649cb9  movups [rbp+0x24C],xmm0` | write 16 bytes rbp+0x24c | [V] |
| 0x6649cc0 | 16 | write 16 bytes rbp+0x25c | `0x6649cc0  movups [rbp+0x25C],xmm8` | write 16 bytes rbp+0x25c | [V] |
| 0x6649cc8 | 16 | write 16 bytes rbp+0x26b | `0x6649cc8  movups [rbp+0x26B],xmm9` | write 16 bytes rbp+0x26b | [V] |
| 0x6649cd0 | 4 | write 4 bytes rbp+0x27c | `0x6649cd0  movss [rbp+0x27C],xmm2` | write 4 bytes rbp+0x27c | [V] |
| 0x6649cd8 | 16 | - | `0x6649cd8  movlhps xmm1,xmm3` | - | [V] |
| 0x6649cdb | 16 | write 16 bytes rbp+0x280 | `0x6649cdb  movups [rbp+0x280],xmm1` | write 16 bytes rbp+0x280 | [V] |
| 0x6649ce2 | 16 | write 16 bytes rbp+0x290 | `0x6649ce2  movups [rbp+0x290],xmm4` | write 16 bytes rbp+0x290 | [V] |
| 0x6649ce9 | 16 | write 16 bytes rbp+0x2a0 | `0x6649ce9  movups [rbp+0x2A0],xmm5` | write 16 bytes rbp+0x2a0 | [V] |
| 0x6649cf0 | 16 | write 16 bytes rbp+0x2b0 | `0x6649cf0  movups [rbp+0x2B0],xmm6` | write 16 bytes rbp+0x2b0 | [V] |
| 0x6649cf7 | 16 | - | `0x6649cf7  movlps [rbp+0x2C0],xmm7` | - | [V] |
| 0x6649cfe | 1 | write rbp+0x2c8 | `0x6649cfe  mov byte ptr [rbp+0x2C8],0` | - | [V] |
| 0x6649d05 | 8 | read rbp+0x10 | `0x6649d05  mov rax,[rbp+0x10]` | read rbp+0x10 | [V] |
| 0x6649d09 | - | - | `0x6649d09  mov [rbp+0x2D0],rax` | - | [V] |
| 0x6649d10 | 8 | - | `0x6649d10  lea rcx,[rbp+0x2D8]` | - | [V] |
| 0x6649d17 | - | - | `0x6649d17  mov rdx,r15` | - | [V] |
| 0x6649d1a | 5 | call 0xE869FF0 | `0x6649d1a  call 0xE869FF0` | call sub_e869ff0 (transform copy packet (4x16 bytes + 2 qwords)) | [V] |
| 0x6649d1f | - | - | `0x6649d1f  nop` | - | [V] |
| 0x6649d20 | 8 | read rbp+0x90 | `0x6649d20  mov rax,[rbp+0x90]` | read rbp+0x90 | [V] |
| 0x6649d27 | - | - | `0x6649d27  mov [rbp+0x350],rax` | - | [V] |
| 0x6649d2e | 8 | write rbp+0x90 | `0x6649d2e  mov qword ptr [rbp+0x90],0` | - | [V] |
| 0x6649d39 | - | - | `0x6649d39  mov [rbp+0x358],si` | - | [V] |
| 0x6649d40 | 16 | read 16 bytes rbp+0x7c0 | `0x6649d40  movaps xmm0,[rbp+0x7C0]` | read 16 bytes rbp+0x7c0 | [V] |
| 0x6649d47 | 16 | read 16 bytes rbp+0x7d0 | `0x6649d47  movaps xmm1,[rbp+0x7D0]` | read 16 bytes rbp+0x7d0 | [V] |
| 0x6649d4e | 8 | write rbp+0x7c8 | `0x6649d4e  mov qword ptr [rbp+0x7C8],0` | - | [V] |
| 0x6649d59 | 16 | write 16 bytes rbp+0x360 | `0x6649d59  movups [rbp+0x360],xmm0` | write 16 bytes rbp+0x360 | [V] |
| 0x6649d60 | 16 | - | `0x6649d60  xorps xmm0,xmm0` | - | [V] |
| 0x6649d63 | 16 | write 16 bytes rbp+0x7d0 | `0x6649d63  movaps [rbp+0x7D0],xmm0` | write 16 bytes rbp+0x7d0 | [V] |
| 0x6649d6a | 16 | write 16 bytes rbp+0x370 | `0x6649d6a  movups [rbp+0x370],xmm1` | write 16 bytes rbp+0x370 | [V] |
| 0x6649d71 | 8 | read rbp+0x7e0 | `0x6649d71  mov rax,[rbp+0x7E0]` | read rbp+0x7e0 | [V] |
| 0x6649d78 | - | - | `0x6649d78  mov [rbp+0x380],rax` | - | [V] |
| 0x6649d7f | 1 | write rbp+0x398 | `0x6649d7f  mov byte ptr [rbp+0x398],0xFF` | - | [V] |
| 0x6649d86 | 4 | - | `0x6649d86  movzx eax,byte ptr [rbp+0x7F8]` | - | [V] |
| 0x6649d8d | 8 | - | `0x6649d8d  cmp rax,3` | - | [V] |
| 0x6649d91 | 2 | - | `0x6649d91  ja 0x664C025` | branch to 0x664c025 | [V] |
| 0x6649d97 | 8 | - | `0x6649d97  lea rcx,[rbp+0x388]` | - | [V] |
| 0x6649d9e | 8 | - | `0x6649d9e  lea rdx,[0xF2BF38C]` | jump-table / string base 0xf2bf38c | [V] |
| 0x6649da5 | 8 | read 4 bytes rdx+rax*4 (jump table) | `0x6649da5  movsxd r8,[rdx+rax*4]` | read 4 bytes rdx+rax*4 (jump table entry) | [V] |
| 0x6649da9 | 8 | - | `0x6649da9  add r8,rdx` | - | [V] |
| 0x6649dac | 2 | jump r8 | `0x6649dac  jmp r8` | indirect jump via jump table (r8) | [V] |
| 0x6649daf | 8 | read rbp+0x7e8 | `0x6649daf  mov rcx,[rbp+0x7E8]` | read rbp+0x7e8 | [V] |
| 0x6649db6 | - | - | `0x6649db6  mov [rbp+0x388],rcx` | - | [V] |
| 0x6649dbd | 5 | jump 0x664BF56 | `0x6649dbd  jmp 0x664BF56` | jump to 0x664bf56 | [V] |
| 0x6649dc2 | 4 | - | `0x6649dc2  xor ecx,ecx` | - | [V] |
| 0x6649dc4 | 5 | jump 0x664ABF5 | `0x6649dc4  jmp 0x664ABF5` | jump to 0x664abf5 | [V] |
| 0x6649dc9 | 8 | - | `0x6649dc9  add r15,8` | - | [V] |
| 0x6649dcd | 8 | - | `0x6649dcd  add r12,r15` | - | [V] |
| 0x6649dd0 | 8 | - | `0x6649dd0  lea r8,[0xF51E3D7]` | jump-table / string base 0xf51e3d7 | [V] |
| 0x6649dd7 | - | - | `0x6649dd7  mov r9d,0x17` | - | [V] |
| 0x6649ddd | - | - | `0x6649ddd  mov rcx,r15` | - | [V] |
| 0x6649de0 | - | - | `0x6649de0  mov rdx,r12` | - | [V] |
| 0x6649de3 | 5 | call 0xE93BF00 | `0x6649de3  call 0xE93BF00` | call sub_e93bf00 (string ends-with compare (fullscreen_cube_overlay)) | [V] |
| 0x6649de8 | 8 | - | `0x6649de8  cmp rax,r12` | - | [V] |
| 0x6649deb | 1 | - | `0x6649deb  setne cl` | - | [V] |
| 0x6649dee | 8 | - | `0x6649dee  sub rax,r15` | - | [V] |
| 0x6649df1 | 8 | - | `0x6649df1  cmp rax,0xFFFFFFFFFFFFFFFF` | - | [V] |
| 0x6649df5 | 1 | - | `0x6649df5  setne r12b` | - | [V] |
| 0x6649df9 | 4 | - | `0x6649df9  and r12b,cl` | - | [V] |
| 0x6649dfc | 8 | read rbp+0x238 | `0x6649dfc  mov rax,[rbp+0x238]` | read rbp+0x238 | [V] |
| 0x6649e03 | 8 | - | `0x6649e03  cmp rax,0x10` | - | [V] |
| 0x6649e07 | 2 | - | `0x6649e07  jb short 0x6649E41` | - | [V] |
| 0x6649e09 | 8 | read rbp+0x220 | `0x6649e09  mov rcx,[rbp+0x220]` | read rbp+0x220 | [V] |
| 0x6649e10 | 8 | - | `0x6649e10  lea rdx,[rax+1]` | - | [V] |
| 0x6649e14 | 8 | - | `0x6649e14  cmp rdx,0x1000` | - | [V] |
| 0x6649e1b | 2 | - | `0x6649e1b  jb short 0x6649E3C` | - | [V] |
| 0x6649e1d | 8 | read rcx-8 | `0x6649e1d  mov r8,[rcx-8]` | read rcx-8 | [V] |
| 0x6649e21 | 8 | - | `0x6649e21  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0x6649e25 | 8 | - | `0x6649e25  sub rcx,r8` | - | [V] |
| 0x6649e28 | 8 | - | `0x6649e28  cmp rcx,0x20` | - | [V] |
| 0x6649e2c | 2 | - | `0x6649e2c  jae 0x664EF5A` | branch to 0x664ef5a | [V] |
| 0x6649e32 | 8 | - | `0x6649e32  add rax,0x28` | - | [V] |
| 0x6649e36 | - | - | `0x6649e36  mov rdx,rax` | - | [V] |
| 0x6649e39 | - | - | `0x6649e39  mov rcx,r8` | - | [V] |
| 0x6649e3c | 5 | call 0xE935700 | `0x6649e3c  call 0xE935700` | call sub_e935700 (free) | [V] |
| 0x6649e41 | 8 | read rdi | `0x6649e41  mov rax,[rdi]` | read rdi | [V] |
| 0x6649e44 | 4 | - | `0x6649e44  movzx r8d,byte ptr [rax+0x39]` | - | [V] |
| 0x6649e49 | 8 | - | `0x6649e49  lea rcx,[rbp+0x740]` | - | [V] |
| 0x6649e50 | - | - | `0x6649e50  mov rdx,r14` | - | [V] |
| 0x6649e53 | 5 | call 0x66B2B30 | `0x6649e53  call 0x66B2B30` | call sub_66b2b30 (entity registry emplace (shared Nametag/Cracks helper)) | [V] |
| 0x6649e58 | - | - | `0x6649e58  mov rax,0xC58E8376A835167E` | - | [V] |
| 0x6649e62 | 8 | - | `0x6649e62  cmp rsi,rax` | - | [V] |
| 0x6649e65 | 2 | - | `0x6649e65  je short 0x6649E8F` | - | [V] |
| 0x6649e67 | - | - | `0x6649e67  mov rax,0xD8B3C5186B8CA065` | - | [V] |
| 0x6649e71 | 8 | - | `0x6649e71  cmp rsi,rax` | - | [V] |
| 0x6649e74 | 2 | - | `0x6649e74  je short 0x6649E8F` | - | [V] |
| 0x6649e76 | - | - | `0x6649e76  mov rax,0x3372F51E15C9A9A` | - | [V] |
| 0x6649e80 | 8 | - | `0x6649e80  cmp rsi,rax` | - | [V] |
| 0x6649e83 | 2 | - | `0x6649e83  je short 0x6649E8F` | - | [V] |
| 0x6649e85 | 4 | write rbp+0x870 | `0x6649e85  mov dword ptr [rbp+0x870],0` | - | [V] |
| 0x6649e8f | 8 | read rbp+0x740 | `0x6649e8f  mov eax,[rbp+0x740]` | read rbp+0x740 | [V] |
| 0x6649e95 | - | - | `0x6649e95  mov [rbp+0x1E8],eax` | - | [V] |
| 0x6649e9b | 1 | write rbp+0x580 | `0x6649e9b  mov byte ptr [rbp+0x580],0` | - | [V] |
| 0x6649ea2 | 8 | read rdi+0x108 | `0x6649ea2  mov rax,[rdi+0x108]` | read rdi+0x108 | [V] |
| 0x6649ea9 | 8 | read rax+0x40 | `0x6649ea9  mov r15,[rax+0x40]` | read rax+0x40 | [V] |
| 0x6649ead | 8 | read r15+0xe0 | `0x6649ead  mov r14,[r15+0xE0]` | read r15+0xe0 | [V] |
| 0x6649eb4 | - | - | `0x6649eb4  cmp qword ptr [r15+0xE8],0x10` | - | [V] |
| 0x6649ebc | 2 | - | `0x6649ebc  jb short 0x6649EC7` | - | [V] |
| 0x6649ebe | 8 | read r15+0xd0 | `0x6649ebe  mov r15,[r15+0xD0]` | read r15+0xd0 | [V] |
| 0x6649ec5 | 2 | jump short | `0x6649ec5  jmp short 0x6649ECE` | jump to 0x6649ece | [V] |
| 0x6649ec7 | 8 | - | `0x6649ec7  add r15,0xD0` | - | [V] |
| 0x6649ece | 16 | - | `0x6649ece  xorps xmm0,xmm0` | - | [V] |
| 0x6649ed1 | 16 | write 16 bytes rbp+0x140 | `0x6649ed1  movaps [rbp+0x140],xmm0` | write 16 bytes rbp+0x140 | [V] |
| 0x6649ed8 | 8 | - | `0x6649ed8  test r14,r14` | - | [V] |
| 0x6649edb | - | - | `0x6649edb  js 0x664F047` | - | [V] |
| 0x6649ee1 | 8 | - | `0x6649ee1  cmp r14,0x10` | - | [V] |
| 0x6649ee5 | - | - | `0x6649ee5  mov [rbp-0x20],r12d` | - | [V] |
| 0x6649ee9 | 2 | - | `0x6649ee9  jae short 0x6649EF9` | - | [V] |
| 0x6649eeb | 8 | - | `0x6649eeb  lea r12,[rbp+0x140]` | - | [V] |
| 0x6649ef2 | - | - | `0x6649ef2  mov ebx,0xF` | - | [V] |
| 0x6649ef7 | 2 | jump short | `0x6649ef7  jmp short 0x6649F6C` | jump to 0x6649f6c | [V] |
| 0x6649ef9 | - | - | `0x6649ef9  mov rdx,r14` | - | [V] |
| 0x6649efc | 8 | - | `0x6649efc  or rdx,0xF` | - | [V] |
| 0x6649f00 | 8 | - | `0x6649f00  cmp rdx,0x17` | - | [V] |
| 0x6649f04 | - | - | `0x6649f04  mov ebx,0x16` | - | [V] |
| 0x6649f09 | 4 | - | `0x6649f09  cmovae rbx,rdx` | - | [V] |
| 0x6649f0d | 8 | read 0x1233e1a8 | `0x6649f0d  mov rcx,[0x1233E1A8]` | read 0x1233e1a8 | [V] |
| 0x6649f14 | 8 | read rcx | `0x6649f14  mov rax,[rcx]` | read rcx | [V] |
| 0x6649f17 | 8 | read rax+8 | `0x6649f17  mov rax,[rax+8]` | read rax+8 | [V] |
| 0x6649f1b | 8 | - | `0x6649f1b  cmp rdx,0xFFF` | - | [V] |
| 0x6649f22 | 2 | - | `0x6649f22  jb short 0x6649F4C` | - | [V] |
| 0x6649f24 | 8 | - | `0x6649f24  lea r12,[rbx+0x28]` | - | [V] |
| 0x6649f28 | - | - | `0x6649f28  mov rdx,r12` | - | [V] |
| 0x6649f2b | 8 | call qword | `0x6649f2b  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x6649f31 | 8 | - | `0x6649f31  test rax,rax` | - | [V] |
| 0x6649f34 | 2 | - | `0x6649f34  je 0x664EDA9` | branch to 0x664eda9 | [V] |
| 0x6649f3a | - | - | `0x6649f3a  mov r12,rax` | - | [V] |
| 0x6649f3d | 8 | - | `0x6649f3d  add r12,0x27` | - | [V] |
| 0x6649f41 | 8 | - | `0x6649f41  and r12,0xFFFFFFFFFFFFFFE0` | - | [V] |
| 0x6649f45 | - | - | `0x6649f45  mov [r12-8],rax` | - | [V] |
| 0x6649f4a | 2 | jump short | `0x6649f4a  jmp short 0x6649F65` | jump to 0x6649f65 | [V] |
| 0x6649f4c | 8 | - | `0x6649f4c  lea r13,[rbx+1]` | - | [V] |
| 0x6649f50 | - | - | `0x6649f50  mov rdx,r13` | - | [V] |
| 0x6649f53 | 8 | call qword | `0x6649f53  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x6649f59 | - | - | `0x6649f59  mov r12,rax` | - | [V] |
| 0x6649f5c | 8 | - | `0x6649f5c  test rax,rax` | - | [V] |
| 0x6649f5f | 2 | - | `0x6649f5f  je 0x664EDBC` | branch to 0x664edbc | [V] |
| 0x6649f65 | - | - | `0x6649f65  mov [rbp+0x140],r12` | - | [V] |
| 0x6649f6c | - | - | `0x6649f6c  mov [rbp+0x150],r14` | - | [V] |
| 0x6649f73 | - | - | `0x6649f73  mov [rbp+0x158],rbx` | - | [V] |
| 0x6649f7a | - | - | `0x6649f7a  mov rcx,r12` | - | [V] |
| 0x6649f7d | - | - | `0x6649f7d  mov rdx,r15` | - | [V] |
| 0x6649f80 | - | - | `0x6649f80  mov r8,r14` | - | [V] |
| 0x6649f83 | 5 | call 0xEEC6EC0 | `0x6649f83  call 0xEEC6EC0` | call sub_eec6ec0 (memcpy helper) | [V] |
| 0x6649f88 | 1 | write r12+r14 | `0x6649f88  mov byte ptr [r12+r14],0` | - | [V] |
| 0x6649f8d | - | - | `0x6649f8d  mov al,1` | - | [V] |
| 0x6649f8f | - | - | `0x6649f8f  mov [rbp+0x598],eax` | - | [V] |
| 0x6649f95 | - | - | `0x6649f95  mov rax,0x1E171F0477EAD280` | - | [V] |
| 0x6649f9f | 8 | - | `0x6649f9f  cmp rsi,rax` | - | [V] |
| 0x6649fa2 | 2 | - | `0x6649fa2  jle short 0x6649FCE` | - | [V] |
| 0x6649fa4 | - | - | `0x6649fa4  mov rax,0x1E171F0477EAD281` | - | [V] |
| 0x6649fae | 8 | - | `0x6649fae  cmp rsi,rax` | - | [V] |
| 0x6649fb1 | 2 | - | `0x6649fb1  je short 0x6649FF6` | - | [V] |
| 0x6649fb3 | - | - | `0x6649fb3  mov rax,0x2404F172C5EAB109` | - | [V] |
| 0x6649fbd | 8 | - | `0x6649fbd  cmp rsi,rax` | - | [V] |
| 0x6649fc0 | 2 | - | `0x6649fc0  je short 0x6649FF6` | - | [V] |
| 0x6649fc2 | - | - | `0x6649fc2  mov rax,0x66A1990A3561111B` | - | [V] |
| 0x6649fcc | 2 | jump short | `0x6649fcc  jmp short 0x6649FE7` | jump to 0x6649fe7 | [V] |
| 0x6649fce | - | - | `0x6649fce  mov rax,0xDB99DF931C70EBAB` | - | [V] |
| 0x6649fd8 | 8 | - | `0x6649fd8  cmp rsi,rax` | - | [V] |
| 0x6649fdb | 2 | - | `0x6649fdb  je short 0x6649FF6` | - | [V] |
| 0x6649fdd | - | - | `0x6649fdd  mov rax,0xEB01AFA8A054432F` | - | [V] |
| 0x6649fe7 | 8 | - | `0x6649fe7  cmp rsi,rax` | - | [V] |
| 0x6649fea | 2 | - | `0x6649fea  je short 0x6649FF6` | - | [V] |
| 0x6649fec | 4 | write rbp+0x598 | `0x6649fec  mov dword ptr [rbp+0x598],0` | - | [V] |
| 0x6649ff6 | 8 | read rbp+0x150 | `0x6649ff6  mov rax,[rbp+0x150]` | read rbp+0x150 | [V] |
| 0x6649ffd | 8 | read rbp+0x158 | `0x6649ffd  mov r14,[rbp+0x158]` | read rbp+0x158 | [V] |
| 0x664a004 | 8 | - | `0x664a004  cmp r14,0x10` | - | [V] |
| 0x664a008 | 2 | - | `0x664a008  jb short 0x664A013` | - | [V] |
| 0x664a00a | 8 | read rbp+0x140 | `0x664a00a  mov rcx,[rbp+0x140]` | read rbp+0x140 | [V] |
| 0x664a011 | 2 | jump short | `0x664a011  jmp short 0x664A01A` | jump to 0x664a01a | [V] |
| 0x664a013 | 8 | - | `0x664a013  lea rcx,[rbp+0x140]` | - | [V] |
| 0x664a01a | 8 | - | `0x664a01a  cmp rax,0x23` | - | [V] |
| 0x664a01e | - | - | `0x664a01e  mov r8d,0x23` | - | [V] |
| 0x664a024 | 4 | - | `0x664a024  cmovb r8,rax` | - | [V] |
| 0x664a028 | 8 | - | `0x664a028  lea rdx,[0xF51FE2B]` | jump-table / string base 0xf51fe2b | [V] |
| 0x664a02f | 1 | - | `0x664a02f  sete bl` | - | [V] |
| 0x664a032 | 5 | call 0xEEC6EB0 | `0x664a032  call 0xEEC6EB0` | call sub_eec6eb0 (shader load helper) | [V] |
| 0x664a037 | 4 | - | `0x664a037  test eax,eax` | - | [V] |
| 0x664a039 | 1 | - | `0x664a039  sete r15b` | - | [V] |
| 0x664a03d | 4 | - | `0x664a03d  and r15b,bl` | - | [V] |
| 0x664a040 | 4 | - | `0x664a040  movzx eax,byte ptr [rdi+0xDC]` | - | [V] |
| 0x664a047 | 4 | - | `0x664a047  xor r9d,r9d` | - | [V] |
| 0x664a04a | - | - | `0x664a04a  mov r8,0x8E31F9DB7CE887B7` | - | [V] |
| 0x664a054 | - | - | `0x664a054  mov r10,0x72BE7BFDEE2D2411` | - | [V] |
| 0x664a05e | 8 | - | `0x664a05e  cmp rsi,r8` | - | [V] |
| 0x664a061 | 2 | - | `0x664a061  je short 0x664A09F` | - | [V] |
| 0x664a063 | - | - | `0x664a063  cmp byte ptr [rdi+0xDD],0` | - | [V] |
| 0x664a06a | 2 | - | `0x664a06a  jne short 0x664A09F` | - | [V] |
| 0x664a06c | 8 | - | `0x664a06c  cmp rsi,r10` | - | [V] |
| 0x664a06f | 1 | - | `0x664a06f  sete cl` | - | [V] |
| 0x664a072 | 8 | read rbp+0x598 | `0x664a072  mov edx,[rbp+0x598]` | read rbp+0x598 | [V] |
| 0x664a078 | 4 | - | `0x664a078  or dl,al` | - | [V] |
| 0x664a07a | 4 | - | `0x664a07a  or dl,cl` | - | [V] |
| 0x664a07c | 4 | - | `0x664a07c  or dl,r15b` | - | [V] |
| 0x664a07f | 2 | - | `0x664a07f  je short 0x664A086` | - | [V] |
| 0x664a081 | 4 | - | `0x664a081  xor r9d,r9d` | - | [V] |
| 0x664a084 | 2 | jump short | `0x664a084  jmp short 0x664A09F` | jump to 0x664a09f | [V] |
| 0x664a086 | 8 | read rbp+0x8a0 | `0x664a086  mov rax,[rbp+0x8A0]` | read rbp+0x8a0 | [V] |
| 0x664a08d | 8 | read rax+0x70 | `0x664a08d  mov eax,[rax+0x70]` | read rax+0x70 | [V] |
| 0x664a090 | 4 | - | `0x664a090  xor eax,1` | - | [V] |
| 0x664a093 | 4 | - | `0x664a093  or eax,[rbp+0x1E8]` | - | [V] |
| 0x664a099 | 1 | - | `0x664a099  sete r9b` | - | [V] |
| 0x664a09d | 4 | - | `0x664a09d  xor eax,eax` | - | [V] |
| 0x664a09f | 8 | - | `0x664a09f  cmp rsi,r8` | - | [V] |
| 0x664a0a2 | 1 | - | `0x664a0a2  setne cl` | - | [V] |
| 0x664a0a5 | 8 | read rbp+0x8a0 | `0x664a0a5  mov rdx,[rbp+0x8A0]` | read rbp+0x8a0 | [V] |
| 0x664a0ac | - | - | `0x664a0ac  cmp dword ptr [rdx+0x70],1` | - | [V] |
| 0x664a0b0 | 1 | - | `0x664a0b0  sete r8b` | - | [V] |
| 0x664a0b4 | 4 | - | `0x664a0b4  or al,r9b` | - | [V] |
| 0x664a0b7 | 4 | - | `0x664a0b7  xor al,1` | - | [V] |
| 0x664a0b9 | 4 | - | `0x664a0b9  and al,r8b` | - | [V] |
| 0x664a0bc | 8 | - | `0x664a0bc  cmp rsi,r10` | - | [V] |
| 0x664a0bf | 1 | - | `0x664a0bf  setne r13b` | - | [V] |
| 0x664a0c3 | 4 | - | `0x664a0c3  and r13b,al` | - | [V] |
| 0x664a0c6 | 4 | - | `0x664a0c6  and r13b,cl` | - | [V] |
| 0x664a0c9 | 8 | - | `0x664a0c9  lea eax,[r13*2]` | - | [V] |
| 0x664a0d1 | 4 | - | `0x664a0d1  movzx eax,al` | - | [V] |
| 0x664a0d4 | - | - | `0x664a0d4  mov ebx,r9d` | - | [V] |
| 0x664a0d7 | 4 | - | `0x664a0d7  test r9b,r9b` | - | [V] |
| 0x664a0da | - | - | `0x664a0da  mov r9d,1` | - | [V] |
| 0x664a0e0 | 4 | - | `0x664a0e0  cmove r9d,eax` | - | [V] |
| 0x664a0e4 | 8 | - | `0x664a0e4  lea rcx,[rbp+0x5A0]` | - | [V] |
| 0x664a0eb | - | - | `0x664a0eb  mov r8,rdi` | - | [V] |
| 0x664a0ee | 5 | call 0xBBD46C0 | `0x664a0ee  call 0xBBD46C0` | call sub_bbd46c0 (registry emplace) | [V] |
| 0x664a0f3 | - | - | `0x664a0f3  nop` | - | [V] |
| 0x664a0f4 | - | - | `0x664a0f4  cmp byte ptr [rbp+0x628],1` | - | [V] |
| 0x664a0fb | 2 | - | `0x664a0fb  jne 0x664EB99` | branch to 0x664eb99 | [V] |
| 0x664a101 | 16 | - | `0x664a101  xorps xmm0,xmm0` | - | [V] |
| 0x664a104 | 16 | write 16 bytes rbp+0x1a0 | `0x664a104  movaps [rbp+0x1A0],xmm0` | write 16 bytes rbp+0x1a0 | [V] |
| 0x664a10b | 4 | - | `0x664a10b  xor r14d,r14d` | - | [V] |
| 0x664a10e | - | - | `0x664a10e  cmp byte ptr [rdi+0xDC],1` | - | [V] |
| 0x664a115 | 2 | - | `0x664a115  jne 0x664A268` | branch to 0x664a268 | [V] |
| 0x664a11b | - | - | `0x664a11b  cmp byte ptr [rdi+0x1A0],3` | - | [V] |
| 0x664a122 | 4 | write rbp+0x7b8 | `0x664a122  mov dword ptr [rbp+0x7B8],0` | - | [V] |
| 0x664a12c | 4 | write rbp+0x7bc | `0x664a12c  mov dword ptr [rbp+0x7BC],0` | - | [V] |
| 0x664a136 | 2 | - | `0x664a136  jne 0x664A27C` | branch to 0x664a27c | [V] |
| 0x664a13c | - | - | `0x664a13c  mov r12b,r15b` | - | [V] |
| 0x664a13f | 8 | read rdi+0x188 | `0x664a13f  mov eax,[rdi+0x188]` | read rdi+0x188 | [V] |
| 0x664a145 | - | - | `0x664a145  mov [rbp+0x7BC],eax` | - | [V] |
| 0x664a14b | 8 | read rdi+0x18c | `0x664a14b  mov eax,[rdi+0x18C]` | read rdi+0x18c | [V] |
| 0x664a151 | - | - | `0x664a151  mov [rbp+0x7B8],eax` | - | [V] |
| 0x664a157 | 8 | read rbp+0x8a0 | `0x664a157  mov rax,[rbp+0x8A0]` | read rbp+0x8a0 | [V] |
| 0x664a15e | 8 | read rax+0x48 | `0x664a15e  mov r14,[rax+0x48]` | read rax+0x48 | [V] |
| 0x664a162 | 8 | read 0x1233e1a8 | `0x664a162  mov rcx,[0x1233E1A8]` | read 0x1233e1a8 | [V] |
| 0x664a169 | 8 | read rcx | `0x664a169  mov rax,[rcx]` | read rcx | [V] |
| 0x664a16c | 8 | read rax+8 | `0x664a16c  mov rax,[rax+8]` | read rax+8 | [V] |
| 0x664a170 | - | - | `0x664a170  mov edx,0x30` | - | [V] |
| 0x664a175 | 8 | call qword | `0x664a175  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664a17b | - | - | `0x664a17b  nop` | - | [V] |
| 0x664a17c | - | - | `0x664a17c  mov r15,rax` | - | [V] |
| 0x664a17f | 8 | - | `0x664a17f  test rax,rax` | - | [V] |
| 0x664a182 | 2 | - | `0x664a182  je 0x664EDCC` | branch to 0x664edcc | [V] |
| 0x664a188 | 16 | read 16 bytes 0xf5c6ae8 | `0x664a188  movups xmm0,[0xF5C6AE8]` | read 16 bytes 0xf5c6ae8 | [V] |
| 0x664a18f | 16 | write 16 bytes r15+0x10 | `0x664a18f  movups [r15+0x10],xmm0` | write 16 bytes r15+0x10 | [V] |
| 0x664a194 | 16 | read 16 bytes 0xf5c6ad8 | `0x664a194  movups xmm0,[0xF5C6AD8]` | read 16 bytes 0xf5c6ad8 | [V] |
| 0x664a19b | 16 | write 16 bytes r15 | `0x664a19b  movups [r15],xmm0` | write 16 bytes r15 | [V] |
| 0x664a19f | 1 | write r15+0x20 | `0x664a19f  mov byte ptr [r15+0x20],0` | - | [V] |
| 0x664a1a4 | 8 | read rbp+0x7bc | `0x664a1a4  mov eax,[rbp+0x7BC]` | read rbp+0x7bc | [V] |
| 0x664a1aa | - | - | `0x664a1aa  mov [rbp+0x220],eax` | - | [V] |
| 0x664a1b0 | 8 | read rbp+0x7b8 | `0x664a1b0  mov eax,[rbp+0x7B8]` | read rbp+0x7b8 | [V] |
| 0x664a1b6 | - | - | `0x664a1b6  mov [rbp+0x224],eax` | - | [V] |
| 0x664a1bc | 16 | read 16 bytes 0xf275e70 | `0x664a1bc  movaps xmm0,[0xF275E70]` | read 16 bytes 0xf275e70 | [V] |
| 0x664a1c3 | 16 | write 16 bytes rbp+0x228 | `0x664a1c3  movups [rbp+0x228],xmm0` | write 16 bytes rbp+0x228 | [V] |
| 0x664a1ca | - | - | `0x664a1ca  mov [rbp+0x238],r15` | - | [V] |
| 0x664a1d1 | 8 | write rbp+0x240 | `0x664a1d1  mov qword ptr [rbp+0x240],0` | - | [V] |
| 0x664a1dc | 8 | write rbp+0x248 | `0x664a1dc  mov qword ptr [rbp+0x248],0x20` | - | [V] |
| 0x664a1e7 | 8 | write rbp+0x250 | `0x664a1e7  mov qword ptr [rbp+0x250],0x2F` | - | [V] |
| 0x664a1f2 | 8 | - | `0x664a1f2  lea rdx,[rbp+0x10]` | - | [V] |
| 0x664a1f6 | 8 | - | `0x664a1f6  lea r8,[rbp+0x220]` | - | [V] |
| 0x664a1fd | - | - | `0x664a1fd  mov rcx,r14` | - | [V] |
| 0x664a200 | 5 | call 0x5AB9970 | `0x664a200  call 0x5AB9970` | call sub_5ab9970 (texture/render-target create) | [V] |
| 0x664a205 | - | - | `0x664a205  nop` | - | [V] |
| 0x664a206 | 16 | read 16 bytes rbp+0x10 | `0x664a206  movaps xmm0,[rbp+0x10]` | read 16 bytes rbp+0x10 | [V] |
| 0x664a20a | 16 | - | `0x664a20a  xorps xmm1,xmm1` | - | [V] |
| 0x664a20d | 16 | write 16 bytes rbp+0x10 | `0x664a20d  movaps [rbp+0x10],xmm1` | write 16 bytes rbp+0x10 | [V] |
| 0x664a211 | 16 | write 16 bytes rbp+0x1a0 | `0x664a211  movaps [rbp+0x1A0],xmm0` | write 16 bytes rbp+0x1a0 | [V] |
| 0x664a218 | 8 | read rbp+0x250 | `0x664a218  mov rax,[rbp+0x250]` | read rbp+0x250 | [V] |
| 0x664a21f | 8 | - | `0x664a21f  cmp rax,0x10` | - | [V] |
| 0x664a223 | - | - | `0x664a223  mov r15d,r12d` | - | [V] |
| 0x664a226 | 2 | - | `0x664a226  jb short 0x664A260` | - | [V] |
| 0x664a228 | 8 | read rbp+0x238 | `0x664a228  mov rcx,[rbp+0x238]` | read rbp+0x238 | [V] |
| 0x664a22f | 8 | - | `0x664a22f  lea rdx,[rax+1]` | - | [V] |
| 0x664a233 | 8 | - | `0x664a233  cmp rdx,0x1000` | - | [V] |
| 0x664a23a | 2 | - | `0x664a23a  jb short 0x664A25B` | - | [V] |
| 0x664a23c | 8 | read rcx-8 | `0x664a23c  mov r8,[rcx-8]` | read rcx-8 | [V] |
| 0x664a240 | 8 | - | `0x664a240  add rcx,0xFFFFFFFFFFFFFFF8` | - | [V] |
| 0x664a244 | 8 | - | `0x664a244  sub rcx,r8` | - | [V] |
| 0x664a247 | 8 | - | `0x664a247  cmp rcx,0x20` | - | [V] |
| 0x664a24b | 2 | - | `0x664a24b  jae 0x664EF5A` | branch to 0x664ef5a | [V] |
| 0x664a251 | 8 | - | `0x664a251  add rax,0x28` | - | [V] |
| 0x664a255 | - | - | `0x664a255  mov rdx,rax` | - | [V] |
| 0x664a258 | - | - | `0x664a258  mov rcx,r8` | - | [V] |
| 0x664a25b | 5 | call 0xE935700 | `0x664a25b  call 0xE935700` | call sub_e935700 (free) | [V] |
| 0x664a260 | - | - | `0x664a260  mov r14d,0x1C` | - | [V] |
| 0x664a266 | 2 | jump short | `0x664a266  jmp short 0x664A27C` | jump to 0x664a27c | [V] |
| 0x664a268 | 4 | write rbp+0x7b8 | `0x664a268  mov dword ptr [rbp+0x7B8],0` | - | [V] |
| 0x664a272 | 4 | write rbp+0x7bc | `0x664a272  mov dword ptr [rbp+0x7BC],0` | - | [V] |
| 0x664a27c | - | - | `0x664a27c  mov [rbp+0x87F],r15b` | - | [V] |
| 0x664a283 | 4 | read 4 bytes rdi+0x134 | `0x664a283  movss xmm0,[rdi+0x134]` | read 4 bytes rdi+0x134 | [V] |
| 0x664a28b | 16 | - | `0x664a28b  shufps xmm0,xmm0,0` | - | [V] |
| 0x664a28f | 16 | write 16 bytes rbp+0x220 | `0x664a28f  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x664a296 | 8 | write rbp+0x10 | `0x664a296  mov qword ptr [rbp+0x10],1` | - | [V] |
| 0x664a29e | 8 | - | `0x664a29e  lea rax,[rbp+0x220]` | - | [V] |
| 0x664a2a5 | - | - | `0x664a2a5  mov [rbp+0x18],rax` | - | [V] |
| 0x664a2a9 | 8 | read rbp+0x5d8 | `0x664a2a9  mov rax,[rbp+0x5D8]` | read rbp+0x5d8 | [V] |
| 0x664a2b0 | 4 | - | `0x664a2b0  movzx r8d,word ptr [rbp+0x5E2]` | - | [V] |
| 0x664a2b8 | - | - | `0x664a2b8  mov edx,r8d` | - | [V] |
| 0x664a2bb | 8 | - | `0x664a2bb  shl edx,4` | - | [V] |
| 0x664a2be | - | - | `0x664a2be  mov rcx,rax` | - | [V] |
| 0x664a2c1 | 4 | - | `0x664a2c1  test r8d,r8d` | - | [V] |
| 0x664a2c4 | 2 | - | `0x664a2c4  je short 0x664A2E8` | - | [V] |
| 0x664a2c6 | 8 | read 0x129f8388 | `0x664a2c6  mov r8,[0x129F8388]` | read 0x129f8388 | [V] |
| 0x664a2cd | - | - | `0x664a2cd  mov r9,rdx` | - | [V] |
| 0x664a2d0 | - | - | `0x664a2d0  mov rcx,rax` | - | [V] |
| 0x664a2d3 | 8 | read rcx | `0x664a2d3  mov r10,[rcx]` | read rcx | [V] |
| 0x664a2d6 | - | read r10+0x28 | `0x664a2d6  cmp [r10+0x28],r8` | read r10+0x28 (compare) | [V] |
| 0x664a2da | 2 | - | `0x664a2da  je short 0x664A2E8` | - | [V] |
| 0x664a2dc | 8 | - | `0x664a2dc  add rcx,0x10` | - | [V] |
| 0x664a2e0 | 8 | - | `0x664a2e0  add r9,0xFFFFFFFFFFFFFFF0` | - | [V] |
| 0x664a2e4 | 2 | - | `0x664a2e4  jne short 0x664A2D3` | - | [V] |
| 0x664a2e6 | 2 | jump short | `0x664a2e6  jmp short 0x664A31B` | jump to 0x664a31b | [V] |
| 0x664a2e8 | 8 | - | `0x664a2e8  add rdx,rax` | - | [V] |
| 0x664a2eb | 8 | - | `0x664a2eb  cmp rcx,rdx` | - | [V] |
| 0x664a2ee | 2 | - | `0x664a2ee  jae short 0x664A31B` | - | [V] |
| 0x664a2f0 | 4 | - | `0x664a2f0  sub ecx,eax` | - | [V] |
| 0x664a2f2 | 8 | - | `0x664a2f2  shr ecx,4` | - | [V] |
| 0x664a2f5 | - | - | `0x664a2f5  mov [rbp+0x7C0],cx` | - | [V] |
| 0x664a2fc | 1 | write rbp+0x7c2 | `0x664a2fc  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x664a303 | 8 | - | `0x664a303  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x664a30a | 8 | - | `0x664a30a  lea r8,[rbp+0x10]` | - | [V] |
| 0x664a30e | 8 | - | `0x664a30e  lea rcx,[rbp+0x5A8]` | - | [V] |
| 0x664a315 | 5 | call 0x5679DB0 | `0x664a315  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x664a31a | - | - | `0x664a31a  nop` | - | [V] |
| 0x664a31b | 4 | - | `0x664a31b  or bl,r13b` | - | [V] |
| 0x664a31e | - | - | `0x664a31e  mov [rbp-0x1C],ebx` | - | [V] |
| 0x664a321 | 4 | - | `0x664a321  cmp bl,1` | - | [V] |
| 0x664a324 | 2 | - | `0x664a324  jne short 0x664A375` | - | [V] |
| 0x664a326 | 8 | read 0x129f9370 | `0x664a326  mov eax,[0x129F9370]` | read 0x129f9370 | [V] |
| 0x664a32c | 8 | read 0x128767c8 | `0x664a32c  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x664a332 | - | - | `0x664a332  mov rdx,gs:[0x58]` | - | [V] |
| 0x664a33b | 8 | read rdx+rcx*8 | `0x664a33b  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x664a33f | 4 | - | `0x664a33f  cmp eax,[rcx+4]` | - | [V] |
| 0x664a345 | 2 | - | `0x664a345  jg 0x664F33D` | branch to 0x664f33d | [V] |
| 0x664a34b | 8 | read rbp+0x898 | `0x664a34b  mov rcx,[rbp+0x898]` | read rbp+0x898 | [V] |
| 0x664a352 | 8 | read rcx+0x430 | `0x664a352  mov rax,[rcx+0x430]` | read rcx+0x430 | [V] |
| 0x664a359 | 8 | - | `0x664a359  test rax,rax` | - | [V] |
| 0x664a35c | 2 | - | `0x664a35c  je short 0x664A381` | - | [V] |
| 0x664a35e | - | - | `0x664a35e  cmp byte ptr [rax],1` | - | [V] |
| 0x664a361 | 2 | - | `0x664a361  jne short 0x664A381` | - | [V] |
| 0x664a363 | 8 | read rcx+0x440 | `0x664a363  mov rax,[rcx+0x440]` | read rcx+0x440 | [V] |
| 0x664a36a | - | - | `0x664a36a  mov ebx,0xC0` | - | [V] |
| 0x664a36f | 8 | - | `0x664a36f  add rbx,[rax+0x18]` | - | [V] |
| 0x664a373 | 2 | jump short | `0x664a373  jmp short 0x664A3AD` | jump to 0x664a3ad | [V] |
| 0x664a375 | - | - | `0x664a375  and byte ptr [rbp+0x744],0xF7` | - | [V] |
| 0x664a37c | 5 | jump 0x664A549 | `0x664a37c  jmp 0x664A549` | jump to 0x664a549 | [V] |
| 0x664a381 | 8 | read 0x129fb168 | `0x664a381  mov eax,[0x129FB168]` | read 0x129fb168 | [V] |
| 0x664a387 | 8 | read 0x128767c8 | `0x664a387  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x664a38d | - | - | `0x664a38d  mov rdx,gs:[0x58]` | - | [V] |
| 0x664a396 | 8 | read rdx+rcx*8 | `0x664a396  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x664a39a | 8 | - | `0x664a39a  lea rbx,[0x129FB158]` | jump-table / string base 0x129fb158 | [V] |
| 0x664a3a1 | 4 | - | `0x664a3a1  cmp eax,[rcx+4]` | - | [V] |
| 0x664a3a7 | 2 | - | `0x664a3a7  jg 0x664F5EF` | branch to 0x664f5ef | [V] |
| 0x664a3ad | 16 | - | `0x664a3ad  xorps xmm0,xmm0` | - | [V] |
| 0x664a3b0 | 16 | write 16 bytes rbp+0x220 | `0x664a3b0  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x664a3b7 | 8 | read rbx+8 | `0x664a3b7  mov rax,[rbx+8]` | read rbx+8 | [V] |
| 0x664a3bb | 8 | - | `0x664a3bb  test rax,rax` | - | [V] |
| 0x664a3be | 2 | - | `0x664a3be  je short 0x664A409` | - | [V] |
| 0x664a3c0 | 4 | read+write rax+8 | `0x664a3c0  lock inc dword ptr [rax+8]` | shared_ptr refcount adjust (read+write rax+8) | [V] |
| 0x664a3c4 | 8 | read rbp+0x228 | `0x664a3c4  mov r15,[rbp+0x228]` | read rbp+0x228 | [V] |
| 0x664a3cb | 16 | read 16 bytes rbx | `0x664a3cb  movups xmm0,[rbx]` | read 16 bytes rbx | [V] |
| 0x664a3ce | 16 | write 16 bytes rbp+0x220 | `0x664a3ce  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x664a3d5 | 8 | - | `0x664a3d5  test r15,r15` | - | [V] |
| 0x664a3d8 | 2 | - | `0x664a3d8  je short 0x664A41E` | - | [V] |
| 0x664a3da | 4 | read+write r15+8 | `0x664a3da  lock dec dword ptr [r15+8]` | shared_ptr refcount adjust (read+write r15+8) | [V] |
| 0x664a3df | 2 | - | `0x664a3df  jne short 0x664A41E` | - | [V] |
| 0x664a3e1 | 8 | read r15 | `0x664a3e1  mov rax,[r15]` | read r15 | [V] |
| 0x664a3e4 | 8 | read rax | `0x664a3e4  mov rax,[rax]` | read rax | [V] |
| 0x664a3e7 | - | - | `0x664a3e7  mov rcx,r15` | - | [V] |
| 0x664a3ea | 8 | call qword | `0x664a3ea  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664a3f0 | 4 | read+write r15+0xc | `0x664a3f0  lock dec dword ptr [r15+0xC]` | shared_ptr refcount adjust (read+write r15+0xc) | [V] |
| 0x664a3f5 | 2 | - | `0x664a3f5  jne short 0x664A41E` | - | [V] |
| 0x664a3f7 | 8 | read r15 | `0x664a3f7  mov rax,[r15]` | read r15 | [V] |
| 0x664a3fa | 8 | read rax+8 | `0x664a3fa  mov rax,[rax+8]` | read rax+8 | [V] |
| 0x664a3fe | - | - | `0x664a3fe  mov rcx,r15` | - | [V] |
| 0x664a401 | 8 | call qword | `0x664a401  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664a407 | 2 | jump short | `0x664a407  jmp short 0x664A41E` | jump to 0x664a41e | [V] |
| 0x664a409 | 8 | read rbx | `0x664a409  mov rax,[rbx]` | read rbx | [V] |
| 0x664a40c | - | - | `0x664a40c  mov [rbp+0x220],rax` | - | [V] |
| 0x664a413 | 8 | write rbp+0x228 | `0x664a413  mov qword ptr [rbp+0x228],0` | - | [V] |
| 0x664a41e | 4 | write rsp+0x28 | `0x664a41e  mov dword ptr [rsp+0x28],0` | - | [V] |
| 0x664a426 | 1 | write rsp+0x20 | `0x664a426  mov byte ptr [rsp+0x20],1` | - | [V] |
| 0x664a42b | 8 | - | `0x664a42b  lea r8,[0x129F9368]` | jump-table / string base 0x129f9368 | [V] |
| 0x664a432 | 8 | - | `0x664a432  lea rcx,[rbp+0x5A0]` | - | [V] |
| 0x664a439 | 8 | - | `0x664a439  lea rdx,[rbp+0x10]` | - | [V] |
| 0x664a43d | 8 | - | `0x664a43d  lea r15,[rbp+0x220]` | - | [V] |
| 0x664a444 | - | - | `0x664a444  mov r9,r15` | - | [V] |
| 0x664a447 | 5 | call 0xBCAC390 | `0x664a447  call 0xBCAC390` | call sub_bcac390 (registry get/emplace by name) | [V] |
| 0x664a44c | - | - | `0x664a44c  nop` | - | [V] |
| 0x664a44d | 8 | read rbp+0x898 | `0x664a44d  mov rbx,[rbp+0x898]` | read rbp+0x898 | [V] |
| 0x664a454 | 8 | read rbp+0x228 | `0x664a454  mov r12,[rbp+0x228]` | read rbp+0x228 | [V] |
| 0x664a45b | 8 | - | `0x664a45b  test r12,r12` | - | [V] |
| 0x664a45e | 2 | - | `0x664a45e  je short 0x664A491` | - | [V] |
| 0x664a460 | 4 | read+write r12+8 | `0x664a460  lock dec dword ptr [r12+8]` | shared_ptr refcount adjust (read+write r12+8) | [V] |
| 0x664a466 | 2 | - | `0x664a466  jne short 0x664A491` | - | [V] |
| 0x664a468 | 8 | read r12 | `0x664a468  mov rax,[r12]` | read r12 | [V] |
| 0x664a46c | 8 | read rax | `0x664a46c  mov rax,[rax]` | read rax | [V] |
| 0x664a46f | - | - | `0x664a46f  mov rcx,r12` | - | [V] |
| 0x664a472 | 8 | call qword | `0x664a472  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664a478 | 4 | read+write r12+0xc | `0x664a478  lock dec dword ptr [r12+0xC]` | shared_ptr refcount adjust (read+write r12+0xc) | [V] |
| 0x664a47e | 2 | - | `0x664a47e  jne short 0x664A491` | - | [V] |
| 0x664a480 | 8 | read r12 | `0x664a480  mov rax,[r12]` | read r12 | [V] |
| 0x664a484 | 8 | read rax+8 | `0x664a484  mov rax,[rax+8]` | read rax+8 | [V] |
| 0x664a488 | - | - | `0x664a488  mov rcx,r12` | - | [V] |
| 0x664a48b | 8 | call qword | `0x664a48b  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664a491 | 8 | read 0x129f9380 | `0x664a491  mov eax,[0x129F9380]` | read 0x129f9380 | [V] |
| 0x664a497 | 8 | read 0x128767c8 | `0x664a497  mov ecx,[0x128767C8]` | read 0x128767c8 | [V] |
| 0x664a49d | - | - | `0x664a49d  mov rdx,gs:[0x58]` | - | [V] |
| 0x664a4a6 | 8 | read rdx+rcx*8 | `0x664a4a6  mov rcx,[rdx+rcx*8]` | read rdx+rcx*8 | [V] |
| 0x664a4aa | 4 | - | `0x664a4aa  cmp eax,[rcx+4]` | - | [V] |
| 0x664a4b0 | 2 | - | `0x664a4b0  jg 0x664F3AF` | branch to 0x664f3af | [V] |
| 0x664a4b6 | 16 | read 16 bytes rbx+0x3e0 | `0x664a4b6  movups xmm0,[rbx+0x3E0]` | read 16 bytes rbx+0x3e0 | [V] |
| 0x664a4bd | 16 | write 16 bytes rbp+0x220 | `0x664a4bd  movaps [rbp+0x220],xmm0` | write 16 bytes rbp+0x220 | [V] |
| 0x664a4c4 | 8 | write rbp+0x10 | `0x664a4c4  mov qword ptr [rbp+0x10],1` | - | [V] |
| 0x664a4cc | - | - | `0x664a4cc  mov [rbp+0x18],r15` | - | [V] |
| 0x664a4d0 | 8 | read rbp+0x5d8 | `0x664a4d0  mov rax,[rbp+0x5D8]` | read rbp+0x5d8 | [V] |
| 0x664a4d7 | 4 | - | `0x664a4d7  movzx r8d,word ptr [rbp+0x5E2]` | - | [V] |
| 0x664a4df | - | - | `0x664a4df  mov edx,r8d` | - | [V] |
| 0x664a4e2 | 8 | - | `0x664a4e2  shl edx,4` | - | [V] |
| 0x664a4e5 | - | - | `0x664a4e5  mov rcx,rax` | - | [V] |
| 0x664a4e8 | 4 | - | `0x664a4e8  test r8d,r8d` | - | [V] |
| 0x664a4eb | 2 | - | `0x664a4eb  je short 0x664A50F` | - | [V] |
| 0x664a4ed | 8 | read 0x129f9378 | `0x664a4ed  mov r8,[0x129F9378]` | read 0x129f9378 | [V] |
| 0x664a4f4 | - | - | `0x664a4f4  mov r9,rdx` | - | [V] |
| 0x664a4f7 | - | - | `0x664a4f7  mov rcx,rax` | - | [V] |
| 0x664a4fa | 8 | read rcx | `0x664a4fa  mov r10,[rcx]` | read rcx | [V] |
| 0x664a4fd | - | read r10+0x28 | `0x664a4fd  cmp [r10+0x28],r8` | read r10+0x28 (compare) | [V] |
| 0x664a501 | 2 | - | `0x664a501  je short 0x664A50F` | - | [V] |
| 0x664a503 | 8 | - | `0x664a503  add rcx,0x10` | - | [V] |
| 0x664a507 | 8 | - | `0x664a507  add r9,0xFFFFFFFFFFFFFFF0` | - | [V] |
| 0x664a50b | 2 | - | `0x664a50b  jne short 0x664A4FA` | - | [V] |
| 0x664a50d | 2 | jump short | `0x664a50d  jmp short 0x664A542` | jump to 0x664a542 | [V] |
| 0x664a50f | 8 | - | `0x664a50f  add rdx,rax` | - | [V] |
| 0x664a512 | 8 | - | `0x664a512  cmp rcx,rdx` | - | [V] |
| 0x664a515 | 2 | - | `0x664a515  jae short 0x664A542` | - | [V] |
| 0x664a517 | 4 | - | `0x664a517  sub ecx,eax` | - | [V] |
| 0x664a519 | 8 | - | `0x664a519  shr ecx,4` | - | [V] |
| 0x664a51c | - | - | `0x664a51c  mov [rbp+0x7C0],cx` | - | [V] |
| 0x664a523 | 1 | write rbp+0x7c2 | `0x664a523  mov byte ptr [rbp+0x7C2],1` | - | [V] |
| 0x664a52a | 8 | - | `0x664a52a  lea rdx,[rbp+0x7C0]` | - | [V] |
| 0x664a531 | 8 | - | `0x664a531  lea r8,[rbp+0x10]` | - | [V] |
| 0x664a535 | 8 | - | `0x664a535  lea rcx,[rbp+0x5A8]` | - | [V] |
| 0x664a53c | 5 | call 0x5679DB0 | `0x664a53c  call 0x5679DB0` | call sub_5679db0 (registry component set (rcx=&slot, rdx=&{index,flag=1}, r8=&rbp+0x5a0)) | [V] |
| 0x664a541 | - | - | `0x664a541  nop` | - | [V] |
| 0x664a542 | 1 | write rbp+0x744 | `0x664a542  mov byte ptr [rbp+0x744],0xF` | - | [V] |
| 0x664a549 | 8 | read rdi | `0x664a549  mov r9,[rdi]` | read rdi | [V] |
| 0x664a54c | 8 | - | `0x664a54c  lea rcx,[rbp+0x7C0]` | - | [V] |
| 0x664a553 | 8 | - | `0x664a553  lea r8,[rbp+0x5A0]` | - | [V] |
| 0x664a55a | 8 | read rbp+0x8a0 | `0x664a55a  mov rdx,[rbp+0x8A0]` | read rbp+0x8a0 | [V] |
| 0x664a561 | 5 | call 0xBBD7F70 | `0x664a561  call 0xBBD7F70` | call sub_bbd7f70 (registry emplace) | [V] |
| 0x664a566 | - | - | `0x664a566  nop` | - | [V] |
| 0x664a567 | - | - | `0x664a567  cmp byte ptr [rbp+0x818],1` | - | [V] |
| 0x664a56e | 2 | - | `0x664a56e  jne 0x664EB5B` | branch to 0x664eb5b | [V] |
| 0x664a574 | - | - | `0x664a574  cmp byte ptr [rdi+0x164],1` | - | [V] |
| 0x664a57b | 2 | - | `0x664a57b  jne short 0x664A592` | - | [V] |
| 0x664a57d | 1 | write rbp+0x754 | `0x664a57d  mov byte ptr [rbp+0x754],1` | - | [V] |
| 0x664a584 | 16 | read 16 bytes rdi+0x154 | `0x664a584  movups xmm0,[rdi+0x154]` | read 16 bytes rdi+0x154 | [V] |
| 0x664a58b | 16 | write 16 bytes rbp+0x758 | `0x664a58b  movups [rbp+0x758],xmm0` | write 16 bytes rbp+0x758 | [V] |
| 0x664a592 | 8 | - | `0x664a592  lea rcx,[rbp+0x220]` | - | [V] |
| 0x664a599 | - | - | `0x664a599  mov r8d,0x358` | - | [V] |
| 0x664a59f | 4 | - | `0x664a59f  xor edx,edx` | - | [V] |
| 0x664a5a1 | 5 | call 0xEEC6ED0 | `0x664a5a1  call 0xEEC6ED0` | call sub_eec6ed0 (memset/set helper (0x358 bytes)) | [V] |
| 0x664a5a6 | 16 | read 16 bytes rbp+0x7c0 | `0x664a5a6  movaps xmm0,[rbp+0x7C0]` | read 16 bytes rbp+0x7c0 | [V] |
| 0x664a5ad | 16 | read 16 bytes rbp+0x7d0 | `0x664a5ad  movaps xmm1,[rbp+0x7D0]` | read 16 bytes rbp+0x7d0 | [V] |
| 0x664a5b4 | 8 | write rbp+0x7c8 | `0x664a5b4  mov qword ptr [rbp+0x7C8],0` | - | [V] |
| 0x664a5bf | 16 | write 16 bytes rbp+0x10 | `0x664a5bf  movaps [rbp+0x10],xmm0` | write 16 bytes rbp+0x10 | [V] |
| 0x664a5c3 | 16 | - | `0x664a5c3  xorps xmm0,xmm0` | - | [V] |
| 0x664a5c6 | 16 | write 16 bytes rbp+0x7d0 | `0x664a5c6  movaps [rbp+0x7D0],xmm0` | write 16 bytes rbp+0x7d0 | [V] |
| 0x664a5cd | 16 | write 16 bytes rbp+0x20 | `0x664a5cd  movaps [rbp+0x20],xmm1` | write 16 bytes rbp+0x20 | [V] |
| 0x664a5d1 | 8 | read rbp+0x7e0 | `0x664a5d1  mov rax,[rbp+0x7E0]` | read rbp+0x7e0 | [V] |
| 0x664a5d8 | - | - | `0x664a5d8  mov [rbp+0x30],rax` | - | [V] |
| 0x664a5dc | 1 | write rbp+0x48 | `0x664a5dc  mov byte ptr [rbp+0x48],0xFF` | - | [V] |
| 0x664a5e0 | 4 | - | `0x664a5e0  movzx eax,byte ptr [rbp+0x7F8]` | - | [V] |
| 0x664a5e7 | 8 | - | `0x664a5e7  cmp rax,3` | - | [V] |
| 0x664a5eb | 2 | - | `0x664a5eb  ja 0x664C370` | branch to 0x664c370 | [V] |
| 0x664a5f1 | 8 | - | `0x664a5f1  lea rcx,[rbp+0x38]` | - | [V] |
| 0x664a5f5 | 8 | - | `0x664a5f5  lea rdx,[0xF2BF36C]` | jump-table / string base 0xf2bf36c | [V] |
| 0x664a5fc | 8 | read 4 bytes rdx+rax*4 (jump table) | `0x664a5fc  movsxd r8,[rdx+rax*4]` | read 4 bytes rdx+rax*4 (jump table entry) | [V] |
| 0x664a600 | 8 | - | `0x664a600  add r8,rdx` | - | [V] |
| 0x664a603 | 2 | jump r8 | `0x664a603  jmp r8` | indirect jump via jump table (r8) | [V] |
| 0x664a606 | 8 | read rbp+0x7e8 | `0x664a606  mov rcx,[rbp+0x7E8]` | read rbp+0x7e8 | [V] |
| 0x664a60d | - | - | `0x664a60d  mov [rbp+0x38],rcx` | - | [V] |
| 0x664a611 | 5 | jump 0x664C36D | `0x664a611  jmp 0x664C36D` | jump to 0x664c36d | [V] |
| 0x664a616 | 8 | - | `0x664a616  lea rdx,[rbp+0x7E8]` | - | [V] |
| 0x664a61d | 16 | read 16 bytes rdx | `0x664a61d  movups xmm0,[rdx]` | read 16 bytes rdx | [V] |
| 0x664a620 | 16 | write 16 bytes rcx | `0x664a620  movups [rcx],xmm0` | write 16 bytes rcx | [V] |
| 0x664a623 | 5 | jump 0x664C36D | `0x664a623  jmp 0x664C36D` | jump to 0x664c36d | [V] |
| 0x664a628 | 16 | write 16 bytes rcx | `0x664a628  movups [rcx],xmm0` | write 16 bytes rcx | [V] |
| 0x664a62b | 8 | read rbp+0x7f0 | `0x664a62b  mov rcx,[rbp+0x7F0]` | read rbp+0x7f0 | [V] |
| 0x664a632 | 8 | - | `0x664a632  test rcx,rcx` | - | [V] |
| 0x664a635 | 2 | - | `0x664a635  je 0x664C35C` | branch to 0x664c35c | [V] |
| 0x664a63b | 4 | read+write rcx+8 | `0x664a63b  lock inc dword ptr [rcx+8]` | shared_ptr refcount adjust (read+write rcx+8) | [V] |
| 0x664a63f | 8 | read rbp+0x7f0 | `0x664a63f  mov rcx,[rbp+0x7F0]` | read rbp+0x7f0 | [V] |
| 0x664a646 | 5 | jump 0x664C35E | `0x664a646  jmp 0x664C35E` | jump to 0x664c35e | [V] |
| 0x664a64b | 4 | - | `0x664a64b  xor ecx,ecx` | - | [V] |
| 0x664a64d | 8 | read rax+0x1b0 | `0x664a64d  mov rax,[rax+0x1B0]` | read rax+0x1b0 | [V] |
| 0x664a654 | - | - | `0x664a654  mov [rbp+0x740],rax` | - | [V] |
| 0x664a65b | 8 | read rbp+0x748 | `0x664a65b  mov r15,[rbp+0x748]` | read rbp+0x748 | [V] |
| 0x664a662 | - | - | `0x664a662  mov [rbp+0x748],rcx` | - | [V] |
| 0x664a669 | 8 | - | `0x664a669  test r15,r15` | - | [V] |
| 0x664a66c | 2 | - | `0x664a66c  je short 0x664A69B` | - | [V] |
| 0x664a66e | 4 | read+write r15+8 | `0x664a66e  lock dec dword ptr [r15+8]` | shared_ptr refcount adjust (read+write r15+8) | [V] |
| 0x664a673 | 2 | - | `0x664a673  jne short 0x664A69B` | - | [V] |
| 0x664a675 | 8 | read r15 | `0x664a675  mov rax,[r15]` | read r15 | [V] |
| 0x664a678 | 8 | read rax | `0x664a678  mov rax,[rax]` | read rax | [V] |
| 0x664a67b | - | - | `0x664a67b  mov rcx,r15` | - | [V] |
| 0x664a67e | 8 | call qword | `0x664a67e  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664a684 | 4 | read+write r15+0xc | `0x664a684  lock dec dword ptr [r15+0xC]` | shared_ptr refcount adjust (read+write r15+0xc) | [V] |
| 0x664a689 | 2 | - | `0x664a689  jne short 0x664A69B` | - | [V] |
| 0x664a68b | 8 | read r15 | `0x664a68b  mov rax,[r15]` | read r15 | [V] |
| 0x664a68e | 8 | read rax+8 | `0x664a68e  mov rax,[rax+8]` | read rax+8 | [V] |
| 0x664a692 | - | - | `0x664a692  mov rcx,r15` | - | [V] |
| 0x664a695 | 8 | call qword | `0x664a695  call qword ptr [0xF99FFA0]` | indirect call via [0xf99ffa0] (sub_eea6040 thunk) | [V] |
| 0x664a69b | 8 | read r13+0x3b8 | `0x664a69b  mov r8,[r13+0x3B8]` | read r13+0x3b8 | [V] |
| 0x664a6a2 | 8 | read rbp+0x8a0 | `0x664a6a2  mov rax,[rbp+0x8A0]` | read rbp+0x8a0 | [V] |
| 0x664a6a9 | 8 | read rax | `0x664a6a9  mov rdx,[rax]` | read rax | [V] |
| 0x664a6ac | - | - | `0x664a6ac  mov [rsp+0x20],ebx` | - | [V] |
| 0x664a6b0 | 4 | write rsp+0x30 | `0x664a6b0  mov dword ptr [rsp+0x30],0` | - | [V] |
| 0x664a6b8 | 4 | write rsp+0x28 | `0x664a6b8  mov dword ptr [rsp+0x28],0` | - | [V] |
| 0x664a6c0 | 8 | - | `0x664a6c0  lea rcx,[rbp+0x10]` | - | [V] |
| 0x664a6c4 | 8 | - | `0x664a6c4  lea r9,[rbp+0x740]` | - | [V] |
| 0x664a6cb | 5 | call 0x66A0F60 | `0x664a6cb  call 0x66A0F60` | call sub_66a0f60 (mesh binding (rcx=&rbp+0x10, r9=&rbp+0x740)) | [V] |
| 0x664a6d0 | - | - | `0x664a6d0  nop` | - | [V] |
| 0x664a6d1 | 4 | - | `0x664a6d1  xor esi,1` | - | [V] |
| 0x664a6d4 | - | - | `0x664a6d4  cmp byte ptr [rdi+0x20],1` | - | [V] |
| 0x664a6d8 | 2 | - | `0x664a6d8  jne 0x664A8ED` | branch to 0x664a8ed | [V] |
| 0x664a6de | 8 | read 8 bytes r12 | `0x664a6de  movsd xmm0,[r12]` | read 8 bytes r12 | [V] |
| 0x664a6e4 | 8 | write 8 bytes rbp+0x7c0 | `0x664a6e4  movsd [rbp+0x7C0],xmm0` | write 8 bytes rbp+0x7c0 | [V] |
| 0x664a6ec | 4 | read 4 bytes r12+8 | `0x664a6ec  movss xmm0,[r12+8]` | read 4 bytes r12+8 | [V] |
| 0x664a6f3 | 4 | write 4 bytes rbp+0x7c8 | `0x664a6f3  movss [rbp+0x7C8],xmm0` | default = 1.0f | [V] |
| 0x664a6fb | 16 | read 16 bytes r12+0xc | `0x664a6fb  movups xmm6,[r12+0xC]` | read 16 bytes r12+0xc | [V] |
| 0x664a701 | 16 | write 16 bytes rbp+0x7cc | `0x664a701  movups [rbp+0x7CC],xmm6` | write 16 bytes rbp+0x7cc | [V] |
| 0x664a708 | 16 | read 16 bytes r12+0x1c | `0x664a708  movups xmm7,[r12+0x1C]` | read 16 bytes r12+0x1c | [V] |
| 0x664a70e | 16 | write 16 bytes rbp+0x7dc | `0x664a70e  movups [rbp+0x7DC],xmm7` | write 16 bytes rbp+0x7dc | [V] |
| 0x664a715 | 16 | read 16 bytes r12+0x2c | `0x664a715  movups xmm8,[r12+0x2C]` | read 16 bytes r12+0x2c | [V] |
| 0x664a71b | 16 | write 16 bytes rbp+0x7ec | `0x664a71b  movups [rbp+0x7EC],xmm8` | write 16 bytes rbp+0x7ec | [V] |
| 0x664a723 | 4 | read 4 bytes r12+0x3c | `0x664a723  movss xmm9,[r12+0x3C]` | read 4 bytes r12+0x3c | [V] |
| 0x664a72a | 4 | write 4 bytes rbp+0x7fc | `0x664a72a  movss [rbp+0x7FC],xmm9` | write 4 bytes rbp+0x7fc | [V] |
| 0x664a733 | 1 | write rbp+0x800 | `0x664a733  mov byte ptr [rbp+0x800],0` | - | [V] |
| 0x664a73a | 8 | read rdi+0x22 | `0x664a73a  mov di,[rdi+0x22]` | read rdi+0x22 | [V] |
| 0x664a73e | 4 | write rbp+0x224 | `0x664a73e  mov dword ptr [rbp+0x224],8` | - | [V] |
| 0x664a748 | 1 | write rbp+0x228 | `0x664a748  mov byte ptr [rbp+0x228],7` | - | [V] |
| 0x664a74f | - | - | `0x664a74f  mov [rbp+0x22C],esi` | - | [V] |
| 0x664a755 | 2 | write rbp+0x230 | `0x664a755  mov word ptr [rbp+0x230],0x101` | - | [V] |
| 0x664a75e | 1 | write rbp+0x232 | `0x664a75e  mov byte ptr [rbp+0x232],4` | - | [V] |
| 0x664a765 | 4 | write rbp+0x234 | `0x664a765  mov dword ptr [rbp+0x234],0` | - | [V] |
| 0x664a76f | 1 | write rbp+0x238 | `0x664a76f  mov byte ptr [rbp+0x238],0` | - | [V] |
| 0x664a776 | 16 | - | `0x664a776  xorps xmm10,xmm10` | - | [V] |
| 0x664a77a | 16 | write 16 bytes rbp+0x23c | `0x664a77a  movups [rbp+0x23C],xmm10` | write 16 bytes rbp+0x23c | [V] |
| 0x664a782 | 4 | write rbp+0x24c | `0x664a782  mov dword ptr [rbp+0x24C],0xFFFFFFE0` | - | [V] |
| 0x664a78c | 4 | - | `0x664a78c  movd xmm0,[0xF07C974]` | - | [V] |
| 0x664a794 | 8 | - | `0x664a794  movq [rbp+0x250],xmm0` | - | [V] |
| 0x664a79c | 1 | write rbp+0x258 | `0x664a79c  mov byte ptr [rbp+0x258],8` | - | [V] |
| 0x664a7a3 | 8 | write rbp+0x25c | `0x664a7a3  mov qword ptr [rbp+0x25C],0` | - | [V] |
| 0x664a7ae | 4 | write rbp+0x264 | `0x664a7ae  mov dword ptr [rbp+0x264],0` | - | [V] |
| 0x664a7b8 | 1 | write rbp+0x268 | `0x664a7b8  mov byte ptr [rbp+0x268],8` | - | [V] |
| 0x664a7bf | 8 | write rbp+0x26c | `0x664a7bf  mov qword ptr [rbp+0x26C],0` | - | [V] |
| 0x664a7ca | 8 | write rbp+0x272 | `0x664a7ca  mov qword ptr [rbp+0x272],0` | - | [V] |
| 0x664a7d5 | 1 | write rbp+0x27a | `0x664a7d5  mov byte ptr [rbp+0x27A],0xFF` | - | [V] |
| 0x664a7dc | 8 | read rbp+0x5a0 | `0x664a7dc  mov rax,[rbp+0x5A0]` | read rbp+0x5a0 | [V] |
| 0x664a7e3 | - | - | `0x664a7e3  mov [rbp+0x280],rax` | - | [V] |
| 0x664a7ea | 8 | - | `0x664a7ea  lea rcx,[rbp+0x288]` | - | [V] |
| 0x664a7f1 | - | - | `0x664a7f1  mov rdx,r14` | - | [V] |
| 0x664a7f4 | 5 | call 0xE869FF0 | `0x664a7f4  call 0xE869FF0` | call sub_e869ff0 (transform copy packet (4x16 bytes + 2 qwords)) | [V] |
| 0x664a7f9 | - | - | `0x664a7f9  nop` | - | [V] |
| 0x664a7fa | 8 | - | `0x664a7fa  lea rax,[rbp+0x224]` | - | [V] |
| 0x664a801 | 8 | - | `0x664a801  lea r10,[rbp+0x280]` | - | [V] |
| 0x664a808 | 8 | read rbp+0x620 | `0x664a808  mov rcx,[rbp+0x620]` | read rbp+0x620 | [V] |
| 0x664a80f | - | - | `0x664a80f  mov [rbp+0x300],rcx` | - | [V] |
| 0x664a816 | 8 | write rbp+0x620 | `0x664a816  mov qword ptr [rbp+0x620],0` | - | [V] |
| 0x664a821 | 8 | - | `0x664a821  lea r9,[rbp+0x308]` | - | [V] |
| 0x664a828 | 8 | read 8 bytes rbp+0x7c0 | `0x664a828  movsd xmm0,[rbp+0x7C0]` | read 8 bytes rbp+0x7c0 | [V] |
| 0x664a830 | 8 | write 8 bytes rbp+0x308 | `0x664a830  movsd [rbp+0x308],xmm0` | write 8 bytes rbp+0x308 | [V] |
| 0x664a838 | 4 | read 4 bytes rbp+0x7c8 | `0x664a838  movss xmm0,[rbp+0x7C8]` | read 4 bytes rbp+0x7c8 | [V] |
| 0x664a840 | 4 | write 4 bytes rbp+0x310 | `0x664a840  movss [rbp+0x310],xmm0` | default = 1.0f | [V] |
| 0x664a848 | 16 | write 16 bytes rbp+0x314 | `0x664a848  movups [rbp+0x314],xmm6` | write 16 bytes rbp+0x314 | [V] |
| 0x664a84f | 16 | write 16 bytes rbp+0x324 | `0x664a84f  movups [rbp+0x324],xmm7` | write 16 bytes rbp+0x324 | [V] |
| 0x664a856 | 16 | write 16 bytes rbp+0x334 | `0x664a856  movups [rbp+0x334],xmm8` | write 16 bytes rbp+0x334 | [V] |
| 0x664a85e | 4 | write 4 bytes rbp+0x344 | `0x664a85e  movss [rbp+0x344],xmm9` | write 4 bytes rbp+0x344 | [V] |
| 0x664a867 | 1 | write rbp+0x348 | `0x664a867  mov byte ptr [rbp+0x348],0` | - | [V] |
| 0x664a86e | 8 | - | `0x664a86e  lea r8,[rbp+0x350]` | - | [V] |
| 0x664a875 | - | - | `0x664a875  mov [rbp+0x350],di` | - | [V] |
| 0x664a87c | 8 | - | `0x664a87c  lea rdx,[rbp+0x358]` | - | [V] |
| 0x664a883 | 16 | read 16 bytes rbp+0x10 | `0x664a883  movaps xmm0,[rbp+0x10]` | read 16 bytes rbp+0x10 | [V] |
| 0x664a887 | 16 | read 16 bytes rbp+0x20 | `0x664a887  movaps xmm1,[rbp+0x20]` | read 16 bytes rbp+0x20 | [V] |
| 0x664a88b | 8 | write rbp+0x18 | `0x664a88b  mov qword ptr [rbp+0x18],0` | - | [V] |
| 0x664a893 | 16 | write 16 bytes rbp+0x358 | `0x664a893  movups [rbp+0x358],xmm0` | write 16 bytes rbp+0x358 | [V] |
| 0x664a89a | 16 | write 16 bytes rbp+0x20 | `0x664a89a  movaps [rbp+0x20],xmm10` | write 16 bytes rbp+0x20 | [V] |
| 0x664a89f | 16 | write 16 bytes rbp+0x368 | `0x664a89f  movups [rbp+0x368],xmm1` | write 16 bytes rbp+0x368 | [V] |
| 0x664a8a6 | 8 | read rbp+0x30 | `0x664a8a6  mov rcx,[rbp+0x30]` | read rbp+0x30 | [V] |
| 0x664a8aa | - | - | `0x664a8aa  mov [rbp+0x378],rcx` | - | [V] |
| 0x664a8b1 | 1 | write rbp+0x390 | `0x664a8b1  mov byte ptr [rbp+0x390],0xFF` | - | [V] |
| 0x664a8b8 | 4 | - | `0x664a8b8  movzx ecx,byte ptr [rbp+0x48]` | - | [V] |
| 0x664a8bc | 8 | - | `0x664a8bc  cmp rcx,3` | - | [V] |
| 0x664a8c0 | 2 | - | `0x664a8c0  ja 0x664E344` | branch to 0x664e344 | [V] |
| 0x664a8c6 | 8 | - | `0x664a8c6  lea r11,[rbp+0x380]` | - | [V] |
| 0x664a8cd | 8 | - | `0x664a8cd  lea rsi,[0xF2BF32C]` | jump-table / string base 0xf2bf32c | [V] |
| 0x664a8d4 | 8 | read 4 bytes rsi+rcx*4 (jump table) | `0x664a8d4  movsxd rdi,[rsi+rcx*4]` | read 4 bytes rsi+rcx*4 (jump table entry) | [V] |
| 0x664a8d8 | 8 | - | `0x664a8d8  add rdi,rsi` | - | [V] |
| 0x664a8db | 2 | jump rdi | `0x664a8db  jmp rdi` | - | [V] |
| 0x664a8dd | 8 | read rbp+0x38 | `0x664a8dd  mov r11,[rbp+0x38]` | read rbp+0x38 | [V] |
| 0x664a8e1 | - | - | `0x664a8e1  mov [rbp+0x380],r11` | - | [V] |
| 0x664a8e8 | 5 | jump 0x664E33E | `0x664a8e8  jmp 0x664E33E` | jump to 0x664e33e | [V] |
| 0x664a8ed | 4 | read 4 bytes r12+0x38 | `0x664a8ed  movss xmm6,[r12+0x38]` | read 4 bytes r12+0x38 | [V] |
| 0x664a8f4 | 4 | read 4 bytes r12+0x30 | `0x664a8f4  movss xmm8,[r12+0x30]` | read 4 bytes r12+0x30 | [V] |
| 0x664a8fb | 4 | read 4 bytes r12+0x34 | `0x664a8fb  movss xmm7,[r12+0x34]` | read 4 bytes r12+0x34 | [V] |
| 0x664a902 | 8 | read 8 bytes r12 | `0x664a902  movsd xmm0,[r12]` | read 8 bytes r12 | [V] |
| 0x664a908 | 8 | write 8 bytes rbp+0x7c0 | `0x664a908  movsd [rbp+0x7C0],xmm0` | write 8 bytes rbp+0x7c0 | [V] |
| 0x664a910 | 4 | read 4 bytes r12+8 | `0x664a910  movss xmm0,[r12+8]` | read 4 bytes r12+8 | [V] |
| 0x664a917 | 4 | write 4 bytes rbp+0x7c8 | `0x664a917  movss [rbp+0x7C8],xmm0` | default = 1.0f | [V] |
| 0x664a91f | 16 | read 16 bytes r12+0xc | `0x664a91f  movups xmm9,[r12+0xC]` | read 16 bytes r12+0xc | [V] |
| 0x664a925 | 16 | write 16 bytes rbp+0x7cc | `0x664a925  movups [rbp+0x7CC],xmm9` | write 16 bytes rbp+0x7cc | [V] |
| 0x664a92d | 16 | read 16 bytes r12+0x1c | `0x664a92d  movups xmm10,[r12+0x1C]` | read 16 bytes r12+0x1c | [V] |
| 0x664a933 | 16 | write 16 bytes rbp+0x7dc | `0x664a933  movups [rbp+0x7DC],xmm10` | write 16 bytes rbp+0x7dc | [V] |
| 0x664a93b | 4 | read 4 bytes r12+0x2c | `0x664a93b  movss xmm11,[r12+0x2C]` | read 4 bytes r12+0x2c | [V] |
| 0x664a942 | 4 | write 4 bytes rbp+0x7ec | `0x664a942  movss [rbp+0x7EC],xmm11` | write 4 bytes rbp+0x7ec | [V] |
| 0x664a94b | 4 | write 4 bytes rbp+0x7f0 | `0x664a94b  movss [rbp+0x7F0],xmm8` | write 4 bytes rbp+0x7f0 | [V] |
| 0x664a954 | 4 | write 4 bytes rbp+0x7f4 | `0x664a954  movss [rbp+0x7F4],xmm7` | write 4 bytes rbp+0x7f4 | [V] |
| 0x664a95c | 4 | write 4 bytes rbp+0x7f8 | `0x664a95c  movss [rbp+0x7F8],xmm6` | write 4 bytes rbp+0x7f8 | [V] |
| 0x664a964 | 4 | read 4 bytes r12+0x3c | `0x664a964  movss xmm12,[r12+0x3C]` | read 4 bytes r12+0x3c | [V] |
| 0x664a96b | 4 | write 4 bytes rbp+0x7fc | `0x664a96b  movss [rbp+0x7FC],xmm12` | write 4 bytes rbp+0x7fc | [V] |
| 0x664a974 | 1 | write rbp+0x800 | `0x664a974  mov byte ptr [rbp+0x800],0` | - | [V] |
| 0x664a97b | 8 | read rdi+0x22 | `0x664a97b  mov di,[rdi+0x22]` | read rdi+0x22 | [V] |
| 0x664a97f | 4 | write rbp+0x224 | `0x664a97f  mov dword ptr [rbp+0x224],8` | - | [V] |
| 0x664a989 | 1 | write rbp+0x228 | `0x664a989  mov byte ptr [rbp+0x228],7` | - | [V] |
| 0x664a990 | - | - | `0x664a990  mov [rbp+0x22C],esi` | - | [V] |
| 0x664a996 | 2 | write rbp+0x230 | `0x664a996  mov word ptr [rbp+0x230],0x101` | - | [V] |
| 0x664a99f | 1 | write rbp+0x232 | `0x664a99f  mov byte ptr [rbp+0x232],4` | - | [V] |
| 0x664a9a6 | 4 | write rbp+0x234 | `0x664a9a6  mov dword ptr [rbp+0x234],0` | - | [V] |
| 0x664a9b0 | 1 | write rbp+0x238 | `0x664a9b0  mov byte ptr [rbp+0x238],0` | - | [V] |
| 0x664a9b7 | 16 | - | `0x664a9b7  xorps xmm13,xmm13` | - | [V] |
| 0x664a9bb | 16 | write 16 bytes rbp+0x23c | `0x664a9bb  movups [rbp+0x23C],xmm13` | write 16 bytes rbp+0x23c | [V] |
| 0x664a9c3 | 4 | write rbp+0x24c | `0x664a9c3  mov dword ptr [rbp+0x24C],0xFFFFFFE0` | - | [V] |
| 0x664a9cd | 4 | - | `0x664a9cd  movd xmm0,[0xF07C974]` | - | [V] |
| 0x664a9d5 | 8 | - | `0x664a9d5  movq [rbp+0x250],xmm0` | - | [V] |
| 0x664a9dd | 1 | write rbp+0x258 | `0x664a9dd  mov byte ptr [rbp+0x258],8` | - | [V] |
| 0x664a9e4 | 8 | write rbp+0x25c | `0x664a9e4  mov qword ptr [rbp+0x25C],0` | - | [V] |
| 0x664a9ef | 4 | write rbp+0x264 | `0x664a9ef  mov dword ptr [rbp+0x264],0` | - | [V] |
| 0x664a9f9 | 1 | write rbp+0x268 | `0x664a9f9  mov byte ptr [rbp+0x268],8` | - | [V] |
| 0x664aa00 | 8 | write rbp+0x26c | `0x664aa00  mov qword ptr [rbp+0x26C],0` | - | [V] |
| 0x664aa0b | 8 | write rbp+0x272 | `0x664aa0b  mov qword ptr [rbp+0x272],0` | - | [V] |
| 0x664aa16 | 1 | write rbp+0x27a | `0x664aa16  mov byte ptr [rbp+0x27A],0xFF` | - | [V] |
| 0x664aa1d | 4 | write 4 bytes rbp+0x27c | `0x664aa1d  movss [rbp+0x27C],xmm8` | write 4 bytes rbp+0x27c | [V] |
| 0x664aa26 | 4 | write 4 bytes rbp+0x280 | `0x664aa26  movss [rbp+0x280],xmm7` | write 4 bytes rbp+0x280 | [V] |
| 0x664aa2e | 4 | write 4 bytes rbp+0x284 | `0x664aa2e  movss [rbp+0x284],xmm6` | write 4 bytes rbp+0x284 | [V] |
| 0x664aa36 | 8 | read rbp+0x5a0 | `0x664aa36  mov rax,[rbp+0x5A0]` | read rbp+0x5a0 | [V] |
| 0x664aa3d | - | - | `0x664aa3d  mov [rbp+0x288],rax` | - | [V] |
| 0x664aa44 | 8 | - | `0x664aa44  lea rcx,[rbp+0x290]` | - | [V] |
| 0x664aa4b | - | - | `0x664aa4b  mov rdx,r14` | - | [V] |
| 0x664aa4e | 5 | call 0xE869FF0 | `0x664aa4e  call 0xE869FF0` | call sub_e869ff0 (transform copy packet (4x16 bytes + 2 qwords)) | [V] |
| 0x664aa53 | - | - | `0x664aa53  nop` | - | [V] |
| 0x664aa54 | 8 | - | `0x664aa54  lea rax,[rbp+0x224]` | - | [V] |
| 0x664aa5b | 8 | - | `0x664aa5b  lea r10,[rbp+0x27C]` | - | [V] |
| 0x664aa62 | 8 | - | `0x664aa62  lea r11,[rbp+0x288]` | - | [V] |
| 0x664aa69 | 8 | read rbp+0x620 | `0x664aa69  mov rcx,[rbp+0x620]` | read rbp+0x620 | [V] |
| 0x664aa70 | - | - | `0x664aa70  mov [rbp+0x308],rcx` | - | [V] |
| 0x664aa77 | 8 | write rbp+0x620 | `0x664aa77  mov qword ptr [rbp+0x620],0` | - | [V] |
| 0x664aa82 | 8 | - | `0x664aa82  lea r9,[rbp+0x310]` | - | [V] |
| 0x664aa89 | 8 | read 8 bytes rbp+0x7c0 | `0x664aa89  movsd xmm0,[rbp+0x7C0]` | read 8 bytes rbp+0x7c0 | [V] |
| 0x664aa91 | 8 | write 8 bytes rbp+0x310 | `0x664aa91  movsd [rbp+0x310],xmm0` | write 8 bytes rbp+0x310 | [V] |
| 0x664aa99 | 4 | read 4 bytes rbp+0x7c8 | `0x664aa99  movss xmm0,[rbp+0x7C8]` | read 4 bytes rbp+0x7c8 | [V] |
| 0x664aaa1 | 4 | write 4 bytes rbp+0x318 | `0x664aaa1  movss [rbp+0x318],xmm0` | default = 1.0f | [V] |
| 0x664aaa9 | 16 | write 16 bytes rbp+0x31c | `0x664aaa9  movups [rbp+0x31C],xmm9` | write 16 bytes rbp+0x31c | [V] |
| 0x664aab1 | 16 | write 16 bytes rbp+0x32c | `0x664aab1  movups [rbp+0x32C],xmm10` | write 16 bytes rbp+0x32c | [V] |
| 0x664aab9 | 4 | write 4 bytes rbp+0x33c | `0x664aab9  movss [rbp+0x33C],xmm11` | write 4 bytes rbp+0x33c | [V] |
| 0x664aac2 | 4 | write 4 bytes rbp+0x340 | `0x664aac2  movss [rbp+0x340],xmm8` | write 4 bytes rbp+0x340 | [V] |
| 0x664aacb | 4 | write 4 bytes rbp+0x344 | `0x664aacb  movss [rbp+0x344],xmm7` | write 4 bytes rbp+0x344 | [V] |
| 0x664aad3 | 4 | write 4 bytes rbp+0x348 | `0x664aad3  movss [rbp+0x348],xmm6` | write 4 bytes rbp+0x348 | [V] |
| 0x664aadb | 4 | write 4 bytes rbp+0x34c | `0x664aadb  movss [rbp+0x34C],xmm12` | write 4 bytes rbp+0x34c | [V] |
| 0x664aae4 | 1 | write rbp+0x350 | `0x664aae4  mov byte ptr [rbp+0x350],0` | - | [V] |
| 0x664aaeb | 8 | - | `0x664aaeb  lea r8,[rbp+0x358]` | - | [V] |
| 0x664aaf2 | - | - | `0x664aaf2  mov [rbp+0x358],di` | - | [V] |
| 0x664aaf9 | 8 | - | `0x664aaf9  lea rdx,[rbp+0x360]` | - | [V] |
| 0x664ab00 | 16 | read 16 bytes rbp+0x10 | `0x664ab00  movaps xmm0,[rbp+0x10]` | read 16 bytes rbp+0x10 | [V] |
| 0x664ab04 | 8 | write rbp+0x18 | `0x664ab04  mov qword ptr [rbp+0x18],0` | - | [V] |
| 0x664ab0c | 16 | write 16 bytes rbp+0x360 | `0x664ab0c  movups [rbp+0x360],xmm0` | write 16 bytes rbp+0x360 | [V] |
| 0x664ab13 | 16 | read 16 bytes rbp+0x20 | `0x664ab13  movaps xmm0,[rbp+0x20]` | read 16 bytes rbp+0x20 | [V] |
| 0x664ab17 | 16 | write 16 bytes rbp+0x20 | `0x664ab17  movaps [rbp+0x20],xmm13` | write 16 bytes rbp+0x20 | [V] |
| 0x664ab1c | 16 | write 16 bytes rbp+0x370 | `0x664ab1c  movups [rbp+0x370],xmm0` | write 16 bytes rbp+0x370 | [V] |
| 0x664ab23 | 8 | read rbp+0x30 | `0x664ab23  mov rcx,[rbp+0x30]` | read rbp+0x30 | [V] |
| 0x664ab27 | - | - | `0x664ab27  mov [rbp+0x380],rcx` | - | [V] |
| 0x664ab2e | 1 | write rbp+0x398 | `0x664ab2e  mov byte ptr [rbp+0x398],0xFF` | - | [V] |
| 0x664ab35 | 4 | - | `0x664ab35  movzx ecx,byte ptr [rbp+0x48]` | - | [V] |
| 0x664ab39 | 8 | - | `0x664ab39  cmp rcx,3` | - | [V] |
| 0x664ab3d | 2 | - | `0x664ab3d  ja 0x664E3A4` | branch to 0x664e3a4 | [V] |
| 0x664ab43 | 8 | - | `0x664ab43  lea rsi,[rbp+0x388]` | - | [V] |
| 0x664ab4a | 8 | - | `0x664ab4a  lea rdi,[0xF2BF31C]` | jump-table / string base 0xf2bf31c | [V] |
| 0x664ab51 | 8 | read 4 bytes rdi+rcx*4 (jump table) | `0x664ab51  movsxd rbx,[rdi+rcx*4]` | read 4 bytes rdi+rcx*4 (jump table entry) | [V] |
| 0x664ab55 | 8 | - | `0x664ab55  add rbx,rdi` | - | [V] |
| 0x664ab58 | 2 | jump rbx | `0x664ab58  jmp rbx` | - | [V] |
| 0x664ab5a | 8 | read rbp+0x38 | `0x664ab5a  mov rsi,[rbp+0x38]` | read rbp+0x38 | [V] |
| 0x664ab5e | - | - | `0x664ab5e  mov [rbp+0x388],rsi` | - | [V] |
| 0x664ab65 | 5 | jump 0x664E39E | `0x664ab65  jmp 0x664E39E` | jump to 0x664e39e | [V] |
| 0x664ab6a | - | - | `0x664ab6a  mov r9d,edx` | - | [V] |
| 0x664ab6d | 4 | - | `0x664ab6d  and r9d,0xFFFFFFFE` | - | [V] |
| 0x664ab71 | 8 | - | `0x664ab71  lea r10,[rax+0x10]` | - | [V] |
| 0x664ab75 | 4 | - | `0x664ab75  xor ecx,ecx` | - | [V] |
| 0x664ab77 | 4 | - | `0x664ab77  xor r8d,r8d` | - | [V] |
| 0x664ab7a | 8 | - | `0x664ab7a  shl rcx,4` | - | [V] |
| 0x664ab7e | 16 | read 16 bytes r10-0x10 | `0x664ab7e  movups xmm0,[r10-0x10]` | read 16 bytes r10-0x10 | [V] |
| 0x664ab83 | 16 | write 16 bytes rbp+rcx+0x5a0 | `0x664ab83  movups [rbp+rcx+0x5A0],xmm0` | write 16 bytes rbp+rcx+0x5a0 | [V] |
| 0x664ab8b | 8 | read rbp+0x620 | `0x664ab8b  mov rcx,[rbp+0x620]` | read rbp+0x620 | [V] |
| 0x664ab92 | 8 | - | `0x664ab92  inc rcx` | - | [V] |
| 0x664ab95 | - | - | `0x664ab95  mov [rbp+0x620],rcx` | - | [V] |
| 0x664ab9c | 8 | - | `0x664ab9c  shl rcx,4` | - | [V] |
| 0x664aba0 | 16 | read 16 bytes r10 | `0x664aba0  movups xmm0,[r10]` | read 16 bytes r10 | [V] |
| 0x664aba4 | 16 | write 16 bytes rbp+rcx+0x5a0 | `0x664aba4  movups [rbp+rcx+0x5A0],xmm0` | write 16 bytes rbp+rcx+0x5a0 | [V] |
| 0x664abac | 8 | read rbp+0x620 | `0x664abac  mov rcx,[rbp+0x620]` | read rbp+0x620 | [V] |
| 0x664abb3 | 8 | - | `0x664abb3  inc rcx` | - | [V] |
| 0x664abb6 | - | - | `0x664abb6  mov [rbp+0x620],rcx` | - | [V] |
| 0x664abbd | 8 | - | `0x664abbd  add r8,2` | - | [V] |
| 0x664abc1 | 8 | - | `0x664abc1  add r10,0x20` | - | [V] |
| 0x664abc5 | 8 | - | `0x664abc5  cmp r9,r8` | - | [V] |
| 0x664abc8 | 2 | - | `0x664abc8  jne short 0x664AB7A` | - | [V] |
| 0x664abca | 4 | - | `0x664abca  test dl,1` | - | [V] |
| 0x664abcd | 2 | - | `0x664abcd  je short 0x664ABF5` | - | [V] |
| 0x664abcf | 8 | - | `0x664abcf  shl r8,4` | - | [V] |
| 0x664abd3 | 8 | - | `0x664abd3  shl rcx,4` | - | [V] |
| 0x664abd7 | 16 | read 16 bytes rax+r8 | `0x664abd7  movups xmm0,[rax+r8]` | read 16 bytes rax+r8 | [V] |
| 0x664abdc | 16 | write 16 bytes rbp+rcx+0x5a0 | `0x664abdc  movups [rbp+rcx+0x5A0],xmm0` | write 16 bytes rbp+rcx+0x5a0 | [V] |
| 0x664abe4 | 8 | read rbp+0x620 | `0x664abe4  mov rcx,[rbp+0x620]` | read rbp+0x620 | [V] |
| 0x664abeb | 8 | - | `0x664abeb  inc rcx` | - | [V] |
| 0x664abee | - | - | `0x664abee  mov [rbp+0x620],rcx` | - | [V] |
| 0x664abf5 | 8 | - | `0x664abf5  lea rax,[rbp+0x628]` | - | [V] |
| 0x664abfc | 8 | read rsi+0x2c0 | `0x664abfc  mov rdx,[rsi+0x2C0]` | read rsi+0x2c0 | [V] |
| 0x664ac03 | 4 | read rdx+0x28 | `0x664ac03  mov r9d,[rdx+0x28]` | read rdx+0x28 | [V] |
| 0x664ac07 | 8 | - | `0x664ac07  test r9,r9` | - | [V] |
| 0x664ac0a | 2 | - | `0x664ac0a  je 0x664ACA1` | branch to 0x664aca1 | [V] |
| 0x664ac10 | 8 | read rbp+0x6a8 | `0x664ac10  mov r8,[rbp+0x6A8]` | read rbp+0x6a8 | [V] |
| 0x664ac17 | 8 | read rdx+0x40 | `0x664ac17  mov rdx,[rdx+0x40]` | read rdx+0x40 | [V] |
| 0x664ac1b | 4 | - | `0x664ac1b  cmp r9d,1` | - | [V] |
| 0x664ac1f | 2 | - | `0x664ac1f  jne short 0x664AC26` | - | [V] |
| 0x664ac21 | 4 | - | `0x664ac21  xor r10d,r10d` | - | [V] |
| 0x664ac24 | 2 | jump short | `0x664ac24  jmp short 0x664AC88` | jump to 0x664ac88 | [V] |
| 0x664ac26 | - | - | `0x664ac26  mov r15,rbx` | - | [V] |
| 0x664ac29 | - | - | `0x664ac29  mov r11d,r9d` | - | [V] |
| 0x664ac2c | 4 | - | `0x664ac2c  and r11d,0xFFFFFFFE` | - | [V] |
| 0x664ac30 | 8 | - | `0x664ac30  lea rbx,[rdx+0x10]` | - | [V] |
| 0x664ac34 | 4 | - | `0x664ac34  xor r10d,r10d` | - | [V] |
| 0x664ac37 | 8 | - | `0x664ac37  shl r8,4` | - | [V] |
| 0x664ac3b | 16 | read 16 bytes rbx-0x10 | `0x664ac3b  movups xmm0,[rbx-0x10]` | read 16 bytes rbx-0x10 | [V] |
| 0x664ac3f | 16 | write 16 bytes rax+r8 | `0x664ac3f  movups [rax+r8],xmm0` | write 16 bytes rax+r8 | [V] |
| 0x664ac44 | 8 | read rbp+0x6a8 | `0x664ac44  mov r8,[rbp+0x6A8]` | read rbp+0x6a8 | [V] |
| 0x664ac4b | 8 | - | `0x664ac4b  inc r8` | - | [V] |
| 0x664ac4e | - | - | `0x664ac4e  mov [rbp+0x6A8],r8` | - | [V] |
| 0x664ac55 | 8 | - | `0x664ac55  shl r8,4` | - | [V] |
| 0x664ac59 | 16 | read 16 bytes rbx | `0x664ac59  movups xmm0,[rbx]` | read 16 bytes rbx | [V] |
| 0x664ac5c | 16 | write 16 bytes rax+r8 | `0x664ac5c  movups [rax+r8],xmm0` | write 16 bytes rax+r8 | [V] |
| 0x664ac61 | 8 | read rbp+0x6a8 | `0x664ac61  mov r8,[rbp+0x6A8]` | read rbp+0x6a8 | [V] |
| 0x664ac68 | 8 | - | `0x664ac68  inc r8` | - | [V] |
| 0x664ac6b | - | - | `0x664ac6b  mov [rbp+0x6A8],r8` | - | [V] |
| 0x664ac72 | 8 | - | `0x664ac72  add r10,2` | - | [V] |
| 0x664ac76 | 8 | - | `0x664ac76  add rbx,0x20` | - | [V] |
| 0x664ac7a | 8 | - | `0x664ac7a  cmp r11,r10` | - | [V] |
| 0x664ac7d | 2 | - | `0x664ac7d  jne short 0x664AC37` | - | [V] |
| 0x664ac7f | 4 | - | `0x664ac7f  test r9b,1` | - | [V] |
| 0x664ac83 | - | - | `0x664ac83  mov rbx,r15` | - | [V] |
| 0x664ac86 | 2 | - | `0x664ac86  je short 0x664ACA1` | - | [V] |
| 0x664ac88 | 8 | - | `0x664ac88  shl r10,4` | - | [V] |
| 0x664ac8c | 8 | - | `0x664ac8c  shl r8,4` | - | [V] |
| 0x664ac90 | 16 | read 16 bytes rdx+r10 | `0x664ac90  movups xmm0,[rdx+r10]` | read 16 bytes rdx+r10 | [V] |
| 0x664ac95 | 16 | write 16 bytes rax+r8 | `0x664ac95  movups [rax+r8],xmm0` | write 16 bytes rax+r8 | [V] |
| 0x664ac9a | 4 | - | `0x664ac9a  inc qword ptr [rbp+0x6A8]` | - | [V] |
| 0x664aca1 | 8 | read rsi+0x2c8 | `0x664aca1  mov rdx,[rsi+0x2C8]` | read rsi+0x2c8 | [V] |
| 0x664aca8 | 8 | read rdx+0x40 | `0x664aca8  mov rdx,[rdx+0x40]` | read rdx+0x40 | [V] |
| 0x664acac | 4 | read 4 bytes rdx | `0x664acac  movss xmm0,[rdx]` | read 4 bytes rdx | [V] |
| 0x664acb0 | 4 | write 4 bytes rbp+0x6b0 | `0x664acb0  movss [rbp+0x6B0],xmm0` | default = 1.0f | [V] |
| 0x664acb8 | 8 | write rbp+0x90 | `0x664acb8  mov qword ptr [rbp+0x90],0` | - | [V] |
| 0x664acc3 | - | - | `0x664acc3  mov rdx,0xFFFFFFFFFFFFFFF` | - | [V] |
| 0x664accd | 8 | - | `0x664accd  test rcx,rcx` | - | [V] |
| 0x664acd0 | 2 | - | `0x664acd0  je 0x664AD64` | branch to 0x664ad64 | [V] |
| 0x664acd6 | - | - | `0x664acd6  mov r8,rcx` | - | [V] |
| 0x664acd9 | 8 | - | `0x664acd9  and r8,rdx` | - | [V] |
| 0x664acdc | 8 | - | `0x664acdc  cmp r8,1` | - | [V] |
| 0x664ace0 | 2 | - | `0x664ace0  jne short 0x664ACE7` | - | [V] |
| 0x664ace2 | 4 | - | `0x664ace2  xor r8d,r8d` | - | [V] |
| 0x664ace5 | 2 | jump short | `0x664ace5  jmp short 0x664AD4F` | jump to 0x664ad4f | [V] |
| 0x664ace7 | 8 | - | `0x664ace7  dec rcx` | - | [V] |
| 0x664acea | 8 | - | `0x664acea  and rcx,rdx` | - | [V] |
| 0x664aced | 8 | - | `0x664aced  inc rcx` | - | [V] |
| 0x664acf0 | - | - | `0x664acf0  mov r9,rcx` | - | [V] |
| 0x664acf3 | 8 | - | `0x664acf3  and r9,0xFFFFFFFFFFFFFFFE` | - | [V] |
| 0x664acf7 | 8 | - | `0x664acf7  lea r14,[rbp+0x5A0]` | - | [V] |
| 0x664acfe | 4 | - | `0x664acfe  xor r8d,r8d` | - | [V] |
| 0x664ad01 | 8 | - | `0x664ad01  shl r8,4` | - | [V] |
| 0x664ad05 | 16 | read 16 bytes r14 | `0x664ad05  movups xmm1,[r14]` | read 16 bytes r14 | [V] |
| 0x664ad09 | 16 | write 16 bytes rbp+r8+0x10 | `0x664ad09  movups [rbp+r8+0x10],xmm1` | variant copy store 16 bytes [rbp+r8+0x10] | [V] |
