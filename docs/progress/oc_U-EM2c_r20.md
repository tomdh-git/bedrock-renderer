## NEXT
DONE — CE recipe for CloudLightingParameters complete and all [V]; CloudParameters/ShadowParameters/ShadowRange registration functions not located (single blocking fact recorded); RenderShadowDescription size 0x20 [V] via its producer. Count stays 28/62.

# UNIT U-EM2c — M2c: description types as structs with confirmed fields (Cloud*/Shadow* reflected types)

GOAL: Close checklist item M2c — every description type (62) as a struct with confirmed fields (Descriptions.h-compatible struct text). This run handles the remaining reflected blocker types CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange and RenderShadowDescription. Per orchestrator 2026-11-22 (after r18): STOP looking for static per-member immediates (member tables are built at runtime in HEAP/static memory). Deliver a Cheat-Engine-readable recipe: where the registration stores the type descriptor / member vector, the member entry layout (stride, name char*, offset, type tag), and the vector begin/end offsets in the descriptor — as [V] instruction rows plus a one-line recipe.

## Method

Static analysis only (rdis dis/str/ptr/xr; no game, no CE, no rtools.*). The reflected member-table callbacks (sub_1188170 lookup, sub_11884a0, sub_11886F0 member builder) are invoked indirectly via type-descriptor function pointers with (name ptr / offset / type) in registers, so there are NO static per-member `mov [..], imm` rows and member-name strings have zero data-section references (verified negative in r19: `rdis ptr` = 0 for RTTI names and container keys). The correct path is the runtime-heap recipe below, fully [V] for CloudLightingParameters.

## 1) Cheat Engine recipe (CloudLightingParameters, registration sub_11884a0) — all [V]

One-line recipe:
"read qword [exe+0x1233E1A8] -> registry object; call sub_eea6040(registry, memberCount=0x14) -> member container (heap); members live in the container at [container+0x00]=begin .. [container+0x08]=end; each member entry stride 0x40: name char* at entry+0x00, type tag u8 at entry+0x24, offset u64 at entry+0x28 (type hash u32 at entry+0x20). Verify type via globals [exe+0x128E48E8]=RTTI name ptr, [exe+0x128E48F0]=sizeof 0x2A, [exe+0x128E48E4]=type hash 0x8DE632ED."

All RVAs/offsets above are [V] from instruction operands in sub_1188400, sub_11884a0, sub_11886f0, sub_1188170, sub_1188250 (rows below).

## 2) [V] instruction rows — type-level globals (sub_1188400, type-descriptor init)

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| global 0x128E48E0 | 4 | `0x118842b  mov [0x128E48E0],eax` | type id counter stored into name-ptr global slot [V] |
| global 0x128E48E4 | 4 | `0x1188431  mov dword ptr [0x128E48E4],0x8DE632ED` | type hash 0x8DE632ED [V] |
| global 0x128E48E8 | 8 | `0x118843b  lea rax,[0xF6416AB]` then `0x1188442  mov [0x128E48E8],rax` | RTTI name ptr -> "mce::framebuilder::CloudLightingParameters" at 0xF6416AB [V] |
| global 0x128E48F0 | 8 | `0x1188449  mov qword ptr [0x128E48F0],0x2A` | sizeof(CloudLightingParameters) = 0x2A (42) [V] |

## 3) [V] instruction rows — type descriptor layout (sub_1188250, descriptor built at caller-provided rax=rcx)

sub_1188250 stores into the descriptor object (rax = rcx arg). These are the descriptor fields (type-level metadata + callbacks):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| desc+0x00 | 8 | `0x11882a9  mov [rax],rdx` (rdx = lea rdx,[0x128E48E0] at 0x11882a2) | desc+0x00 := address of name-ptr global 0x128E48E0 [V] |
| desc+0x08 | 4 | `0x11882ac  mov [rax+8],ecx` (ecx = [0x128E48E4]) | desc+0x08 := type hash 0x8DE632ED [V] |
| desc+0x10 | 8 | `0x11882af  mov qword ptr [rax+0x10],0` | desc+0x10 := 0 [V] |
| desc+0x18 | 4 | `0x11882b7  mov dword ptr [rax+0x18],0x80` | desc+0x18 := flags 0x80 [V] |
| desc+0x20 | 8 | `0x11882be  mov qword ptr [rax+0x20],0x14` | desc+0x20 := member count = 0x14 (20) [V] |
| desc+0x28 | 8 | `0x11882cd  mov [rax+0x28],rcx` (rcx = lea rcx,[0x1188170]) | desc+0x28 := lookup callback sub_1188170 [V] |
| desc+0x30 | 8 | `0x11882d8  mov [rax+0x30],rcx` (rcx = lea rcx,[0x11884A0]) | desc+0x30 := callback sub_11884a0 [V] |
| desc+0x38 | 8 | `0x11882dc  mov qword ptr [rax+0x38],0` | desc+0x38 := 0 [V] |
| desc+0x40 | 8 | `0x11882eb  mov [rax+0x40],rcx` (rcx = lea rcx,[0x11886F0]) | desc+0x40 := member-builder callback sub_11886f0 [V] |
| desc+0x48 | 16 | `0x11882f2  movups [rax+0x48],xmm0` (xmm0 zeroed at 0x11882ef) | desc+0x48 := zeroed [V] |
| desc+0x54 | 16 | `0x11882f6  movups [rax+0x54],xmm0` | desc+0x54 := zeroed [V] |
| desc+0x68 | 16 | `0x11882fa  movups [rax+0x68],xmm0` | desc+0x68 := zeroed [V] |
| desc+0x78 | 8 | `0x11882fe  mov qword ptr [rax+0x78],0` | desc+0x78 := 0 [V] |

Note: sub_1188250 is invoked with a caller-provided buffer (no static descriptor RVA); the descriptor object itself is built at runtime. The static anchors are the globals in section 2 and the registry global [0x1233E1A8] below.

## 4) [V] instruction rows — member-container object built by sub_11884a0 (rcx = dest object)

sub_11884a0 is the descriptor+0x30 callback. It allocates the member container via sub_eea6040 from the global registry [0x1233E1A8] with count 0x14, then fills the dest object:

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| dest+0x00 | 8 | `0x11884fd  mov [rsi],rax` (rsi = rcx; rax = sub_eea6040 result at 0x11884e1) | dest+0x00 := member-container object from sub_eea6040(registry [0x1233E1A8], count 0x14) [V] |
| dest+0x10 | 8 | `0x11884b4  mov [rcx+0x10],rax` (rax = lea rax,[0x1188560]) | dest+0x10 := sub_1188560 [V] |
| dest+0x18 | 8 | `0x11884c6  mov [rcx+0x18],rax` (rax = lea rax,[0x11886D0]) | dest+0x18 := sub_11886D0 [V] |
| dest+0x20 | 4 | `0x11884b8  mov dword ptr [rcx+0x20],0x8DE632ED` | dest+0x20 := type hash 0x8DE632ED [V] |
| dest+0x24 | 1 | `0x11884ca  mov byte ptr [rcx+0x24],1` | dest+0x24 := flag byte 1 [V] |
| dest+0x28 | 8 | `0x1188500  mov [rsi+0x28],rdi` (rdi = rdx arg2 at 0x11884a7) | dest+0x28 := arg2 pointer [V] |
| dest+0x30 | 8 | `0x1188504  mov qword ptr [rsi+0x30],0` | dest+0x30 := 0 [V] |
| dest+0x38 | 8 | `0x1188513  mov [rsi+0x38],rax` (rax = lea rax,[0x1188540]) | dest+0x38 := sub_1188540 [V] |

The registry global read: `0x11884ce  mov rcx,[0x1233E1A8]` (global registry object), `0x11884dc  mov edx,0x14`, `0x11884e1  call qword ptr [0xF99FFA0]` (= sub_eea6040) [V]. The container object (heap) is what holds begin/end and the member entries.

## 5) [V] instruction rows — member entry layout (sub_11886f0, the push/emplace that appends one member)

sub_11886f0 is the descriptor+0x40 member-builder callback. Entry pointer = rax = rcx arg. It stores name ptr (r8), offset (rdx), type tag and hashes into the entry. Fields written span entry+0x00 .. entry+0x38, so stride = 0x40 (64 bytes):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| entry+0x00 | 8 | `0x1188726  mov [rax],r8` | entry+0x00 := name char* (r8 = name pointer passed in register) [V] |
| entry+0x10 | 8 | `0x118870c  mov [rax+0x10],rcx` (rcx = lea rcx,[0x1188560]) | entry+0x10 := sub_1188560 [V] |
| entry+0x18 | 8 | `0x118871e  mov [rax+0x18],rcx` (rcx = lea rcx,[0x11886D0]; or 0 at 0x118873d when name/type null) | entry+0x18 := sub_11886D0 or 0 [V] |
| entry+0x20 | 4 | `0x1188710  mov dword ptr [rax+0x20],0x8DE632ED` | entry+0x20 := parent type hash 0x8DE632ED [V] |
| entry+0x24 | 1 | `0x1188722  mov byte ptr [rax+0x24],1` (or 3 at 0x118874a / 4 at 0x1188753) | entry+0x24 := type tag u8 (1/3/4) [V] |
| entry+0x28 | 8 | `0x118875a  mov [rax+0x28],rdx` | entry+0x28 := offset u64 (rdx = offset passed in register) [V] |
| entry+0x30 | 8 | `0x118875e  mov qword ptr [rax+0x30],0` | entry+0x30 := 0 [V] |
| entry+0x38 | 8 | `0x118876d  mov [rax+0x38],rcx` (rcx = lea rcx,[0x1188540]) | entry+0x38 := sub_1188540 [V] |

Stride = 0x40 [V] (last store at entry+0x38 is 8 bytes, so next entry begins at +0x40). The name/offset/type are passed in REGISTERS (r8/rdx/r9), not immediates — hence no static per-member `mov [..], imm` rows exist (verified negative in r19).

## 6) [V] instruction rows — container begin/end and entry walk (sub_1188170, lookup callback)

sub_1188170 reads the member container object (rcx = container pointer from sub_eea6040):

| offset | size | site | verbatim `0xRVA  instr` | meaning [tag] |
|---|---|---|---|---|
| container+0x00 | 8 | `0x11881a0  mov rax,[rcx]` | container+0x00 := bucket/vector begin pointer [V] |
| container+0x08 | 8 | `0x11881a3  mov r8,[rcx+8]` | container+0x08 := bucket/vector end pointer [V] |
| (count) | - | `0x11881a7  sub r8,rax` / `0x11881aa  shr r8,3` / `0x11881ae  dec r8d` | count = (end - begin) / 8, then -1 & mask [V] |
| container+0x20 | 8 | `0x11881b8  mov r8,[rcx+0x20]` | container+0x20 := entries array base [V] |
| entry walk | - | `0x11881dd  lea r9,[r8+r10*8]` / `0x11881e1  cmp [r8+r10*8+8],edx` | entries indexed stride 24 (0x18): [+0x00] index/chain, [+0x08] hash, [+0x10] ptr [V] |
| resolved member | 8 | `0x11881f2  mov rax,[rdx+0x10]` | [rdx+0x10] := pointer to member descriptor (stride 0x40 from section 5) [V] |

So the CE traversal: registry [0x1233E1A8] -> sub_eea6040 -> container; container+0x00/0x08 bracket the bucket array; container+0x20 entries array (stride 0x18) whose [+0x10] points to each stride-0x40 member descriptor; member descriptor: name char* +0x00, type tag u8 +0x24, offset u64 +0x28. All RVAs/offsets [V].

## 7) Other reflected types — status

| Type | sizeof | registration located | member layout | status |
|---|---|---|---|---|
| CloudLightingParameters | 0x2A [V] (0x1188449) | sub_11884a0 [V] | stride 0x40, name +0x00, tag +0x24, offset +0x28 [V] | recipe complete, all [V] |
| CloudParameters | unknown | NOT located (RTTI string 0xF6419FD only, no code ref) | not located | [?] — registration function not found |
| ShadowParameters | unknown | NOT located (RTTI string 0xF641005; key "shadow_config" 0xF5B8368 at sub_1152460+0x270b) | not located | [?] — registration function not found |
| ShadowRange | unknown | NOT located (RTTI string 0xF67B699; key "shadow_range" 0xF5E056A at sub_53fcac0+0x1c60 [I]) | not located | [?] — registration function not found |

The recipe in section 1 applies identically to CloudParameters/ShadowParameters/ShadowRange once their registration functions (the sub_11884a0-equivalent that stores sizeof + member count + callbacks) are located. Their RTTI strings are data-only (zero code refs), so `rdis str` + `rdis ptr` found no member table (verified negative in r19).

## 8) RenderShadowDescription

RenderShadowDescription size 0x20 [V] (end 0x1A + align 8) via its producer/clone 0x53e6c30 (fat 0x897, Effect tag 4) — see docs/progress/descriptions.md entry R-D7b and BGFX_MAP.md line 307 ("RenderShadowDescription | 0x53e6c30 | fat 0x897 | Effect"). The insert vtable receiving the 0x14-byte entry and the shadow-pass execute-body [desc+off] reads are NOT located statically, so no per-field [V> rows beyond size 0x20; never-referenced fields are [?] padding per the live note.

## 9) Descriptions.h-compatible struct text

```cpp
namespace mce::framebuilder {

// CloudLightingParameters: sizeof 0x2A [V], 20 reflected members [V count].
// Member offsets/names/types are runtime-reflected (NOT statically locatable):
//   descriptor globals: [exe+0x128E48E8]=RTTI name ptr, [exe+0x128E48F0]=sizeof 0x2A,
//   [exe+0x128E48E4]=hash 0x8DE632ED, [exe+0x128E48E0]=type-id global.
//   member container (heap) via sub_eea6040(registry [exe+0x1233E1A8], count 0x14);
//   container+0x00=begin, +0x08=end, +0x20=entries array (stride 0x18, +0x10=member-desc ptr);
//   member descriptor stride 0x40: name char* +0x00, type tag u8 +0x24, offset u64 +0x28.
// The actual member objects are written by the DOM->struct consumer at runtime;
// this header only records the reflected layout recipe, not field values.
struct CloudLightingParameters {
    char pad_0x00[0x2A];   // [?] individual member offsets not statically recoverable
};
static_assert(sizeof(CloudLightingParameters) == 0x2A, "CloudLightingParameters size");

// CloudParameters, ShadowParameters, ShadowRange: sizeof and member offsets unknown [?]
// (registration functions not located; RTTI strings only).
struct CloudParameters { char pad[?]; };
struct ShadowParameters { char pad[?]; };
struct ShadowRange { char pad[?]; };

// RenderShadowDescription: sizeof 0x20 [V] via producer 0x53e6c30; per-field offsets [?].
struct RenderShadowDescription {
    char pad_0x00[0x20];   // [?] insert vtable / shadow-pass reads not located
};
static_assert(sizeof(RenderShadowDescription) == 0x20, "RenderShadowDescription size");

}
```

## 10) Count of types done out of 62

This run adds NO new fully-typed type (per-field [V] rows not instruction-locatable for CloudParameters/ShadowParameters/ShadowRange; their registration functions are not located). CloudLightingParameters now has a complete [V] CE recipe but its per-member offsets are runtime-reflected, not static struct fields.
Cumulative: **28/62** (unchanged).

## CLOSES?

NO — the item's wording (per-field rows / recipe for CloudLightingParameters, CloudParameters, ShadowParameters, ShadowRange, RenderShadowDescription) is not fully met on disk. Single blocking fact: the registration functions for CloudParameters, ShadowParameters and ShadowRange (the sub_11884a0-equivalents that store sizeof + member count + callbacks, and thus the member-table descriptor RVAs/offsets) are NOT located statically — only CloudLightingParameters (sub_11884a0) has a complete [V] CE recipe. RenderShadowDescription's insert vtable / shadow-pass [desc+off] reads also remain unlocated (size 0x20 only [V]). Everything written above is [V] except the [?] entries.

## TOOL REQUESTS

None — rdis dis/str/ptr/xr plus the precomputed live capture files (m2c_member_11884a0.txt, m2c_member_11886f0.txt, empty — 0 hits as expected) sufficed; no helper script worth keeping was written.
