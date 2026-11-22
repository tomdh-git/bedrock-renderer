## NEXT
DONE

# oc_U-ER10 — R10 UIMesh (UI tag 2): true size (>= 0x90), sub-objects at +0x18 and +0x88

## Scope (from the checklist line)
Pending parts of R10: (1) true size (>= 0x90); (2) sub-object at +0x18; (3) sub-object at +0x88.
Explicitly untouched, out of scope for this unit: Gameface (UI tag 0), HudIcon (UI tag 1), UIImGui (UI tag 4).

## Input data (read fully, not regenerated)
- docs/functions/668c3c0.md — RenderUIMeshDescription constructor 0x668c3c0 dossier (D2, static)
- docs/functions/4c96140.md — thin insert clone 0x4C96140 (UI vslot 0x368, tag 2)
- docs/data/listings/ui_visitor_6664a00_6668510.txt — UI group visitor 0x6664A00, tag-2 case 0x6664BD6..0x6664F4A (inline, calls renderer 0x674A3A0)
- docs/progress/descriptions.md — R10 entry (ctor-writes layout, size 0xA8)
- docs/progress/re_uimesh.md — UIMesh clone/ctor/consumer summary
- docs/data/producer_fields.txt — UIMesh producer section (noisy; stores beyond +0xA8 are other locals in big producer frames, per BGFX_MAP 6id)
- src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h — RenderUIMeshDescription static_asserts
- rdis dis of 0x668c3c0 (ctor) and 0x6664bd6 (visitor case) — every verbatim line below matches rdis output exactly (confirmed via tools/sigs/verify_oc.py by delegate.py check)

## Method
UI visitor case 2 (head 0x6664bd6): description pointer is r9 (set at function entry 0x6664a59 `mov r9,[r8]`, tag dispatch jumps into the case with r9 = desc). Ctor 0x668c3c0: this in rsi, returns rsi. All sizes below come from the instruction (movups/movaps 16B, movss 4B, qword mov 8B, word 2B, byte 1B). One row per distinct offset, all sites merged into the row; no offset duplicated.

## Field map (UIMesh description, UI tag 2)

| Name | Size | RVA | Read/store site | Verbatim `0xRVA  instr` | Meaning | Tag |
| mValue00 | 8B | 0x00 | this+0x00 ctor; r9+0x00 visitor | `0x668c42f  mov [rsi],rcx`<br>`0x6664eb1  mov r13,[r9]` | qword field; visitor passes it as renderer argument | [V] |
| mValue08 | 8B | 0x08 | this+0x08 ctor; r9+0x08 visitor | `0x668c432  mov [rsi+8],r8`<br>`0x6664eb4  mov r14,[r9+8]` | qword field | [V] |
| mValue10 | 8B | 0x10 | this+0x10 ctor; r9+0x10 visitor | `0x668c436  mov [rsi+0x10],rax`<br>`0x6664ea9  mov r15,[r9+0x10]` | qword field | [V] |
| mRefs[4] array | 16B | 0x18 | this+0x18/+0x28/+0x38/+0x48 ctor; r9+0x18 base, +0x28/+0x30 element 1 visitor | `0x668c43a  lea rax,[rsi+0x18]`<br>`0x668c445  movups [rsi+0x18],xmm1`<br>`0x668c449  movups [rsi+0x28],xmm1`<br>`0x668c44d  movups [rsi+0x38],xmm1`<br>`0x668c451  movups [rsi+0x48],xmm1`<br>`0x6664c3b  lea rax,[r9+0x18]`<br>`0x6664e97  mov r12,[r9+0x28]`<br>`0x6664c68  mov r15,[r9+0x30]` | inline array of 4 shared_ptr pairs (+0x18..+0x57 = 64B); ctor zeroes each 16B slot with movups; visitor loads array base and element-1 ptr (+0x28) / ctrl (+0x30) | [V] |
| mRefCount | 8B | 0x58 | this+0x58 ctor; r9+0x58 visitor | `0x668c455  mov qword ptr [rsi+0x58],0`<br>`0x6664c3f  cmp qword ptr [r9+0x58],2` | u64 count of valid mRefs; ctor inits 0; visitor cmp against 2 picks the submit path | [V] |
| mValue60 | 8B | 0x60 | this+0x60 ctor; r9+0x60 visitor | `0x668c45d  mov [rsi+0x60],r13`<br>`0x6664c2b  mov r11,[r9+0x60]` | qword field | [V] |
| mValue68 | 8B | 0x68 | this+0x68 ctor; r9+0x68 visitor | `0x668c461  mov [rsi+0x68],r12`<br>`0x6664c2f  mov rdx,[r9+0x68]` | qword field | [V] |
| mValue70 | 4B | 0x70 | this+0x70 ctor; r9+0x70 visitor | `0x668c465  movss [rsi+0x70],xmm0`<br>`0x6664c25  movss xmm0,[r9+0x70]` | float field | [V] |
| pad | 4B | 0x74 | — | - | implicit padding after the +0x70 float store; no instruction touches +0x74 | [?] |
| mValue78 | 8B | 0x78 | this+0x78 ctor; r9+0x78 visitor | `0x668c46a  mov [rsi+0x78],r15`<br>`0x6664ead  mov r12,[r9+0x78]` | qword field | [V] |
| mFlags80[0] | 1B | 0x80 | this+0x80 ctor; r9+0x80 visitor | `0x668c46e  mov [rsi+0x80],r14b`<br>`0x6664c33  movzx edi,byte ptr [r9+0x80]` | flag byte | [V] |
| mFlags80[1] | 1B | 0x81 | this+0x81 ctor; r9+0x81 visitor | `0x668c475  mov [rsi+0x81],dil`<br>`0x6664c1d  movzx r8d,byte ptr [r9+0x81]` | flag byte | [V] |
| mFlags80[2] | 1B | 0x82 | this+0x82 ctor; r9+0x82 visitor | `0x668c47c  mov [rsi+0x82],r11b`<br>`0x6664bd6  movzx ecx,byte ptr [r9+0x82]` | flag byte; visitor mode computation | [V] |
| mFlags80[3] | 1B | 0x83 | this+0x83 ctor; r9+0x83 visitor | `0x668c483  mov [rsi+0x83],r10b`<br>`0x6664bde  movzx r12d,byte ptr [r9+0x83]` | flag byte; visitor mode computation | [V] |
| mFlags80[4] | 1B | 0x84 | this+0x84 ctor; r9+0x84 visitor | `0x668c491  mov [rsi+0x84],al`<br>`0x6664be6  movzx edx,byte ptr [r9+0x84]` | flag byte; visitor mode computation | [V] |
| mFlags80[5] | 1B | 0x85 | this+0x85 ctor; r9+0x85 visitor | `0x668c49e  mov [rsi+0x85],al`<br>`0x6664c15  movzx esi,byte ptr [r9+0x85]` | flag byte | [V] |
| mValue86 | 2B | 0x86 | this+0x86 ctor; visitor forms &desc+0x86 | `0x668c4a7  mov [rsi+0x86],ax`<br>`0x6664eb8  add r9,0x86` | u16 field; visitor computes &desc+0x86 and passes it to renderer | [V] |
| mVariantStorage88 | 24B | 0x88 | this+0x88 ctor cases; r9+0x88 visitor | `0x668c4ae  lea rax,[rsi+0x88]`<br>`0x668c4e2  mov [rsi+0x88],rax`<br>`0x668c554  lea rax,[rsi+0x88]`<br>`0x668c55b  mov [rax],rdi`<br>`0x6664c07  lea rbx,[r9+0x88]` | DescVariantRef storage base (+0x88..+0x9F); case 0 stores inline qword at +0x88, case 1 stores heap-block ptr at +0x88; visitor passes base to renderer | [V] |
| variant alt0 SharedRef | 16B | 0x90 | this+0x90 ctor case 0 | `0x668c4e9  lea rax,[rsi+0x90]`<br>`0x668c4f3  movups [rsi+0x90],xmm0`<br>`0x668c50f  mov [rax],rcx` | variant case 0: zeroed 16B slot then SharedRef ptr stored at +0x90 | [V] |
| variant alt0 ctrl | 8B | 0x98 | this+0x98 ctor case 0 | `0x668c515  mov [rsi+0x98],rax` | variant case 0: SharedRef control pointer stored at +0x98 | [V] |
| mVariantTag | 1B | 0xA0 | this+0xA0 ctor default + cases | `0x668c4b9  mov byte ptr [rsi+0xA0],0xFF`<br>`0x668c5ac  mov [rsi+0xA0],r14b` | variant tag; ctor default 0xFF = empty; cases write the real tag | [V] |

## Size proof — R10 part 1: true size (>= 0x90) [V]
Highest constructor write is the variant-tag byte at +0xA0 (`0x668c4b9  mov byte ptr [rsi+0xA0],0xFF`), so the object extent ends at 0xA1. Alignment to 8 gives true size **0xA8**, which is >= 0x90 [V ctor lines]. The ctor writes every initialized byte 0x00..0xA0; the only holes are pad (0x74..0x77 after the float store), uninitialized variant storage until a variant case writes it (0x88..+0x9F, default tag 0xFF = empty), and tail pad 0xA1..0xA7 — none of these are description fields [V ctor lines; pad meaning -].
Cross-check: `Descriptions.h` static_assert(sizeof(RenderUIMeshDescription) == 0xA8) and offsetof asserts at +0x18/+0x58/+0x60/+0x70/+0x78/+0x80/+0x86/+0x88/+0xA0 match the ctor extent [V file]. producer_fields.txt UIMesh stores beyond +0xA8 (up to +0x3A0) are other locals in the big producer frames (BGFX_MAP 6id noisy-store note), not description bytes [I].
This resolves the BGFX_MAP 6ih contradiction ("sub-objects at +0x18/+0x88, size >= 0x90"): size is 0xA8 >= 0x90 and both sub-objects are proven below.

## Sub-object at +0x18 — R10 part 2 [V]
mRefs[4]: inline array of 4 shared_ptr pairs at +0x18..+0x57 with count u64 at +0x58. The ctor zeroes all four slots (movups at +0x18/+0x28/+0x38/+0x48) and inits +0x58 = 0; the visitor takes the array base (`0x6664c3b  lea rax,[r9+0x18]`) and reads element 1 — ptr at +0x28 (`0x6664e97  mov r12,[r9+0x28]`) and ctrl at +0x30 (`0x6664c68  mov r15,[r9+0x30]`, then a strong ref is taken on the ctrl object). Proven by table rows +0x18 and +0x58, all [V].

## Sub-object at +0x88 — R10 part 3 [V]
DescVariantRef storage: 0x18 bytes at +0x88..+0x9F plus tag u8 at +0xA0. The ctor takes the base (`0x668c4ae  lea rax,[rsi+0x88]`), case 0 stores an inline qword at +0x88 then a SharedRef {ptr +0x90, ctrl +0x98}, case 1 allocs a 0x20 heap block and stores its ptr at +0x88, and the default leaves tag 0xFF = empty (`0x668c4b9  mov byte ptr [rsi+0xA0],0xFF`). The visitor passes the variant base to the renderer (`0x6664c07  lea rbx,[r9+0x88]`, passed as a 0x674A3A0 argument). Proven by table rows +0x88/+0x90/+0x98/+0xA0, all [V].

## Gameface / HudIcon / UIImGui
Untouched per the item line. Their visitor cases exist in the same listing (Gameface 0x6664a6c -> jmp 0x66ade80, HudIcon 0x6664d51, UIImGui 0x6664aab) and are deliberately not decoded here.

## CLOSES?
CLOSES? YES — every pending part of R10 is proven by [V] rows: true size 0xA8 (>= 0x90) via ctor extent ending at the write byte +0xA0, aligned to 0xA8 (corroborated by header static_asserts); sub-object at +0x18 = inline mRefs[4] shared_ptr array (ctor zeroing + visitor base and element-1 reads); sub-object at +0x88 = DescVariantRef storage (ctor lea and case stores, tag at +0xA0; visitor passes base to 0x674A3A0). Gameface, HudIcon, UIImGui are excluded by the item line itself (untouched). No blocking fact.

## TOOL REQUESTS
None — existing tools only: rdis.exe dis (verbatim lines), python tools/sigs/verify_oc.py, python tools/delegate.py check.
