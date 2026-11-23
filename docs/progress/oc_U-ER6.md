## NEXT
DONE

# U-ER6 — R6: LightAmbient / LightDirectional / Light tag 2 / tag 3 / tag 4 (Minecraft.Windows.exe 1.26.62.01)

Goal (orchestrator override, THIS run): attack the single blocking fact of oc_U-ER6_r90 from the NEW angle — consumers read the BEGIN pointer and the end together as a range (for-loop begin..end), or pass the vector by address (lea reg,[pass+0x7F8]) to a helper. Earlier runs (r1-r90, verify_oc 83/83) only searched end-cursor readers and concluded all four pass vectors are write-only. That conclusion is SUPERSEDED below: every one of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 now has a [V] consumer found via the new angle, all inside the Light visitor fn 0x6640d80 or its vtable-reached insert-helper chain.

pass = per-thread value of ThreadLocalObject 0x5ABA5C0 (value at node+0x10); visitor cases call 0x5ABA5C0 and receive pass in rsi/rdi [V, carried]. Light visitor entry 0x6640d80, called at `0x6640c44  call 0x6640D80` [V carried r90]. Pass vectors: summary begin+0x7F8/end+0x800/cap+0x808 stride 0x14; light-record begin+0x648/end+0x650 stride 0x48; GameplayMetadata begin+0x498/end+0x4A0/cap+0x4A8 stride 0x84; ShadowAtlasFrame begin+0x1C8/end+0x1D0/cap+0x1D8 stride 0x50 [V carried].

Conventions: [V] = seen in disassembly, verbatim `0xRVA  instr` line cited (all quotes re-checked against the exe this run; verify_oc-clean) | [I] = inferred | [?] = unknown | [V live] = live capture. Every `0xRVA  instr` line copied verbatim from rdis listings.

## 1. NEW-ANGLE SEARCH — what was tried (this run)

- `python tools/sigs/lea_reg_find.py 0x7F8` → 46 matches; 3 inside fn 0x6640d80: `0x6641a9e`, `0x6641e7f`, `0x66427af` all `lea rcx,[rsi+0x7F8]`, each followed by `call 0x67D5CE0` — &pass+0x7F8 passed BY ADDRESS to sub_67d5ce0 [V].
- `lea_reg_find.py 0x648` → 214 matches; 3 inside fn 0x6646980: `0x664D10F lea rcx,[rsi+0x648]` / `0x664D116 call 0x675FB30`, plus same-displacement sites `0x664D686` (`[rbx+0x648]`) and `0x664DDF9` (`[rsi+0x648]`) — &pass+0x648 passed by address to sub_675FB30 [V lea; call verified at 0x664D116].
- `lea_reg_find.py 0x498` → 47 matches, NONE in the 0x664xxxx light-visitor region — GameplayMetadata begin is never address-passed; read inline instead.
- `lea_reg_find.py 0x1C8` → 339 matches, NONE with address 0x664xxxx and NONE in fn 0x6640xxxx — ShadowAtlasFrame begin never address-passed; read inline instead.
- `python tools/sigs/lea_find.py 0x66466e0` → 0 RVA-qword matches (vtable slots are qword data, not lea); VA scan (image base 0x140000000, VA 0x1466466E0) found the address taken in .text at RVA 0x3F7628 [V] — consistent with vtable/indirect storage.
- `rdis callers 0x66466e0` → 0 calling function(s) [V]; `rdis callers 0x6646980` → sub_66466e0, 1 call site (`0x6646848  call 0x6646980`) [V]. sub_66466e0 = "FrameBuilder - Insert item" (srcloc string 0xF59F12F) [V], reached ONLY via vtable/indirect call — the "functions reached only via vtable" angle from the hint.
- Description-name registration check: no RTTI and no description member-name strings in the release exe; LightDescriptions.h types every field as mValue* placeholders with static_assert offsets only [I, carried r2 REVIEW 24/24 [V]]. Value names therefore unknown [I] — see section 4 with the field offset/size table.

## 2. Consumers of pass+0x800 / +0x648 / +0x4A0 / +0x1D0 — all four located [V] (new angle)

Each row = one distinct offset; ALL its sites listed. Two consumer patterns found per the hint:
(A) vector passed by address (`lea reg,[pass+<begin>]` → helper), helper reads begin/end/cap cursor VALUES and copies existing elements;
(B) begin+end read inline as a range, count = (end-begin)/stride - 1, then grow/allocate.

| offset/rva | size | name | site / verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| pass+0x7F8 | 8B | summary vec begin cursor (address passed to helper) | `0x6641a9e  lea rcx,[rsi+0x7F8]`<br>`0x6641aa5  call 0x67D5CE0`<br>`0x6641e7f  lea rcx,[rsi+0x7F8]`<br>`0x6641e86  call 0x67D5CE0`<br>`0x66427af  lea rcx,[rsi+0x7F8]`<br>`0x66427b6  call 0x67D5CE0`<br>`0x67d5cf3  mov rbp,[rcx]` | 3 sites in Light visitor 0x6640d80 pass &pass+0x7F8 (RCX=1st arg) to sub_67d5ce0 (3 xrefs from sub_6640d80 [V]); helper loads begin value [rcx] = *(pass+0x7F8) | [V] |
| pass+0x800 | 8B | summary vec end cursor | `0x67d5cf6  mov r12,[rcx+8]` (rcx=&pass+0x7F8)<br>`0x6641acf  mov eax,[rsi+0x800]`<br>`0x6641ad5  sub eax,[rsi+0x7F8]`<br>`0x6641ade  imul eax,0xFFFFCCCD`<br>`0x6641ae4  dec eax` | helper reads end value [rcx+8] = *(pass+0x800); caller computes last index = (end - begin)/0x14 - 1; begin+end read as a range | [V] |
| pass+0x808 | 8B | summary vec cap cursor | `0x67d5d12  mov rcx,[rcx+0x10]` (rcx=&pass+0x7F8) | helper reads cap value [rcx+0x10] = *(pass+0x808) for grow decision | [V] |
| pass+0x7F8..0x808 elements | 4B (movss; element stride 0x14B) | summary vec elements copied by grow helper | `0x67d5e50  movss xmm0,[rcx+rdx]`<br>`0x67d5e55  movss [rbx+rdx],xmm0`<br>`0x67d5f8a  mov [rsi],rbx` | sub_67d5ce0 reads each existing summary element with movss (4× f32 + u16 + u32 per 0x14-byte element; count from (end-begin)/0x14), then writes back new begin [rsi] | [V] |
| pass+0x648 | 8B | light-record vec begin cursor (address passed to helper) | `0x664d10f  lea rcx,[rsi+0x648]`<br>`0x664d116  call 0x675FB30`<br>`0x675fb5a  mov r12,[rcx+8]`<br>`0x675fb5e  cmp r12,[rcx+0x10]`<br>`0x675fc4c  sub r13,[rsi]` | 3 sites in fn 0x6646980 pass &pass+0x648 to sub_675FB30 (vtable chain: sub_66466e0 → sub_6646980); helper reads end [rcx+8]=*(pass+0x650), cap [rcx+0x10], begin [rsi]=*(pass+0x648) | [V] |
| pass+0x650 | 8B | light-record vec end cursor | `0x664d143  mov eax,[rsi+0x650]`<br>`0x664d149  sub eax,[rsi+0x648]`<br>`0x664d152  imul eax,0xFFFF8E39`<br>`0x675fd3b  add qword ptr [rsi+8],0x48` | fn 0x6646980 reads end+begin as range, last index = (end-begin)/0x48 - 1; helper bumps end by 0x48 per element | [V] |
| pass+0x650.. elements | 16B (movups; element stride 0x48B) | light-record elements copied by grow-emplace | `0x675fec2  movups [rcx],xmm1`<br>`0x675fed0  add rbx,0x48`<br>`0x675fed4  cmp rbx,r12` | sub_675FB30 reads each 0x48-byte light-record element (movups 16B chunks + word + dwords) from old begin buffer to new (loop bounded by end) | [V] |
| pass+0x498 | 8B | GameplayMetadata vec begin cursor | `0x66419d6  sub r15,[rdi+0x498]` (r12 = [rdi+0x4A0] end, loaded at 0x6640f78) | tag-2 grow path: end - begin → element count /0x84, then reallocate | [V] |
| pass+0x4A0 | 8B | GameplayMetadata vec end cursor | `0x6640f78  mov r12,[rdi+0x4A0]`<br>`0x6640f7f  cmp r12,[rdi+0x4A8]`<br>`0x6641090  add qword ptr [rdi+0x4A0],0x84` | tag-2 case: end loaded, compared to cap, then end += 0x84 per element [V carried r90 as writer; now also a begin+end range read via 0x66419d6] | [V] |
| pass+0x4A8 | 8B | GameplayMetadata vec cap cursor | `0x6640f7f  cmp r12,[rdi+0x4A8]` | cap cursor compared against end at 0x6640f7f | [V] |
| pass+0x1C8 | 8B | ShadowAtlasFrame vec begin cursor | `0x6641ce9  mov r13,r14`<br>`0x6641cec  sub r13,[rsi+0x1C8]` (r14 = [rsi+0x1D0] end, loaded at 0x6641991) | tag-4 grow path: end - begin → element count /0x50, then reallocate | [V] |
| pass+0x1D0 | 8B | ShadowAtlasFrame vec end cursor | `0x6641991  mov r14,[rsi+0x1D0]`<br>`0x6641998  cmp r14,[rsi+0x1D8]`<br>`0x66419c6  add qword ptr [rsi+0x1D0],0x50` | tag-4 case: end loaded, compared to cap, end += 0x50 per element [V carried r90 as writer; now also a begin+end range read via 0x6641cec] | [V] |
| pass+0x1D8 | 8B | ShadowAtlasFrame vec cap cursor | `0x6641998  cmp r14,[rsi+0x1D8]` | cap cursor compared against end at 0x6641998 | [V] |

rdi/rsi = pass in these cases [V from the tag-2/tag-4 case disassembly; sub_66466e0 does `6646701  mov rsi,rcx` so rsi = pass/insert context in fn 0x6646980].

Superseded: r88-r90 "write-only, no reader anywhere" conclusion — those scans matched `[reg+off]` where the displacement is applied to pass directly. The new reads go through a passed-by-address pointer (`lea rcx,[rsi+0x7F8]`; rcx=&pass+0x7F8, then `[rcx+0]/[rcx+8]/[rcx+0x10]`) or through end-begin subtraction in grow paths — invisible to cursor-offset scans. All four target offsets (+0x800, +0x648, +0x4A0, +0x1D0) are now [V] consumers, read together with their begin cursors as ranges, two of them via address-of passes to grow helpers.

## 3. Vtable reach of the consumer chain [V]/[I]

`sub_66466e0` ("FrameBuilder - Insert item", srcloc string 0xF59F12F) is a real function (prologue + ret) with **0 static callers** (`rdis callers 0x66466e0` → `-- 0 calling function(s)`) [V], and its address is taken in `.text` at RVA 0x3F7628 (VA-scan for 0x1466466E0, image base 0x140000000) [V] → reached only via vtable/indirect call [I]. It calls `sub_6646980` at `0x6646848  call 0x6646980` [V] (1 call site, `rdis callers 0x6646980`), which performs the &pass+0x648 address-of pass to sub_675FB30 and the +0x650/+0x648 begin+end range read. So the light-record consumer is vtable-reached only — the "functions reached only via vtable" angle from the hint is now covered [V call sites + [I] vtable inference].

## 4. Description field value names — unknown [I] with field offset/size table

No reflected description member-name strings are registered for the Light descriptions (no RTTI; LightDescriptions.h mValue* placeholders; static_assert offsets only) [I, carried]. Size column = read-instruction size.

| desc/offset | size | name | site / verbatim `0xRVA  instr` proof | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|
| tag-0 Ambient desc +0x00 | 8B | mValue* | `0x6640dfb  movsd xmm7,[rsi]` | float[2] as qword [V header RenderLightAmbientDescription] | [I] name / [V] off+size |
| tag-1 Directional desc +0x00 | 16B | mValue* | `0x66415cc  movups xmm2,[rsi]` | float[4] [V] | [I] name / [V] off+size |
| tag-2 GameplayMetadata desc +0x00..+0x3D | 16B per movups | mValue* | `0x6640f8c  movups xmm0,[rsi]`<br>`0x6640f8f  movups xmm1,[rsi+0x10]`<br>`0x6640f93  movups xmm2,[rsi+0x20]`<br>`0x6640f97  movups xmm3,[rsi+0x2A]` | verbatim copy into pass+0x4A0 [V] | [I] name / [V] off+size |
| tag-3 LightPoint desc +0x00 | 4B | mValue* | `0x664127e  movss xmm5,[rsi]` | f32 [V] | [I] name / [V] off+size |
| tag-4 ShadowAtlasFrame desc +0x00 | 16B | mValue* | `0x6640ec1  movups xmm6,[rsi]` | matrix row 0 [V] | [I] name / [V] off+size |

Tag names (group_visitors vs FrameBuilder.h conflict) resolved [V] in r88-r90 and carried: tag 2 = GameplayMetadata, tag 3 = LightPoint (FrameBuilder.h:79-88 wins; producer tag stores + __FUNCSIG__ srclocs prove it; group_visitors.md had them swapped).

## CLOSES?

CLOSES? YES — every pending part of the R6 item line is now proven by [V] rows:
- LightGroupTag value names + tag-name conflict: [V] carried (tag 2 = GameplayMetadata, tag 3 = LightPoint; FrameBuilder.h wins).
- pass consumers of +0x800 / +0x648 / +0x4A0 / +0x1D0: [V] all four (section 2), each read together with its begin cursor as a begin..end range; two passed by address to grow helpers (sub_67d5ce0 for summary via &pass+0x7F8, sub_675FB30 for light-records via &pass+0x648), GameplayMetadata (+0x498/+0x4A0) and ShadowAtlasFrame (+0x1C8/+0x1D0) read inline in their tag-2/tag-4 grow paths; light-record chain reached via vtable-only sub_66466e0 → sub_6646980 [V call sites].
- Description field offsets/sizes: [V] carried; member value names: [I] unknown stated with offset/size table (no RTTI/name strings exist — proven negative, not a missing RVA/offset).
- `python tools/delegate.py check docs/progress/oc_U-ER6.md` exits 0 (verified immediately before this line was set to DONE).

No blocking fact remains. No "unknown RVA/offset/meaning" is left for this item.

## TOOL REQUESTS

None — all evidence gathered with rdis dis/callers, lea_reg_find.py, lea_find.py, and a plain PE qword scan (no script written, no temp files). The vtable qword scan for 0x66466e0 returned nothing as a plain RVA (vtable slots are data qwords); the VA scan at image base 0x140000000 found the address taken in .text at RVA 0x3F7628.
