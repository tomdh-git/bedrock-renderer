# Dossier: sub_bc3c6b0 — BgfxFrameBuilder slot 0 validate-and-clear

**RVA:** 0xbc3c6b0
**Size:** 0xcb bytes ([0xbc3c6b0, 0xbc3c77b))
**Version:** Minecraft.Windows.exe 1.26.62.01
**Region:** bgfx / D0 (depth 3)
**Checklist:** X1.bc3c6b0 LIFT sub_bc3c6b0 (0xbc3c6b0, 0xcb bytes, depth 3, D0, 0 callees in set)

## Signature guess

`void sub_bc3c6b0(unsigned __int64 mode /*rcx*/, unsigned __int64 /*rdx*/, BgfxFrameBuilderSlot0* fb /*r8*/, void* a3 /*r9*/)`

The function returns void: no path writes a deterministic value to rax before `ret`.

## Register / argument map at entry

- rcx = `mode` — compared against 1; only `== 1` proceeds (0xbc3c6b6 / 0xbc3c6ba).
- rdx — never read.
- r8 = `fb` — pointer to the frame-builder slot block; copied to rsi at 0xbc3c6c0 (used as `self`).
- r9 = `a3` — forwarded as the 4th argument to `sub_e935700`.

Stack frame: `sub rsp,0x28`; one stack store at `[rsp+0x20]` on the error path (0xbc3c761). No other stack usage.

## Phases

### 0xbc3c6b0..0xbc3c6c0 — prologue + mode check
`push rsi; push rdi; sub rsp,0x28; cmp rcx,1; jne 0xBC3C75A`
- `if (mode != 1) return;` — fallthrough to epilogue at 0xbc3c75a.

### 0xbc3c6c0..0xbc3c6f4 — slot block setup + first branch
`mov rsi,r8; mov rcx,[r8+0x60]; test rcx,rcx; je short 0xBC3C70B; mov rdx,[rsi+0x70]; sub rdx,rcx; cmp rdx,0x1000; jb short 0xBC3C6F4`
- `self = fb;`
- `if (self->field_0x60 != nullptr) {`
  - `slot_size = self->field_0x70 - self->field_0x60;`
  - `if (slot_size >= 0x1000) {` (large path)

### 0xbc3c6f4..0xbc3c700 — first call (large path)
`lea rdi,[rsi+0x60]; call 0xE935700`
- `sub_e935700(*(field_0x60 - 8), slot_size + 0x27, self, a3);` — 0xbc3c6f8 `call 0xE935700`
- `self->field_0x60 = nullptr; self->field_0x70 = nullptr;` — 0xbc3c6fd..0xbc3c703: `xorps xmm0,xmm0; movups [rdi],xmm0; mov qword ptr [rdi+0x10],0`

### 0xbc3c6dc..0xbc3c6f1 — large-path guard checks
`mov rax,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,rax; cmp rcx,0x20; jae short 0xBC3C761; add rdx,0x27; mov rcx,rax`
- `chunk = *(uint64_t*)(field_0x60 - 8);`
- `guard = (field_0x60 - 8) - chunk; if (guard >= 0x20) goto error;`
- `arg0 = chunk; arg1 = slot_size + 0x27;`

### 0xbc3c70b..0xbc3c746 — second slot field + second branch
`mov rax,[rsi+0x50]; cmp rax,0x10; jb short 0xBC3C746; mov rcx,[rsi+0x38]; lea rdx,[rax+1]; cmp rdx,0x1000; jb short 0xBC3C741`
- `if (self->field_0x50 >= 0x10) {`
  - `slot_ptr = self->field_0x38;`
  - `size_plus1 = self->field_0x50 + 1;`
  - `if (size_plus1 >= 0x1000) {` (large path)

### 0xbc3c726..0xbc3c741 — second call (large path)
`mov r8,[rcx-8]; add rcx,0xFFFFFFFFFFFFFFF8; sub rcx,r8; cmp rcx,0x20; jae short 0xBC3C761; add rax,0x28; mov rdx,rax; mov rcx,r8; call 0xE935700`
- `chunk = *(uint64_t*)(slot_ptr - 8);`
- `guard = (slot_ptr - 8) - chunk; if (guard >= 0x20) goto error;`
- `sub_e935700(chunk, field_0x50 + 0x28, chunk, a3);` — 0xbc3c741 `call 0xE935700`

### 0xbc3c741 (small path) — second call
At 0xbc3c741 (reached via `jb` from 0xbc3c724): `sub_e935700(slot_ptr, field_0x50 + 1, self, a3);`

### 0xbc3c746..0xbc3c760 — reset + epilogue
`mov qword ptr [rsi+0x48],0; mov qword ptr [rsi+0x50],0xF; mov byte ptr [rsi+0x38],0; add rsp,0x28; pop rdi; pop rsi; ret`
- `self->field_0x48 = 0; self->field_0x50 = 0xF; *(uint8_t*)&self->field_0x38 = 0; return;`

### 0xbc3c761..0xbc3c77b — error path
`mov qword ptr [rsp+0x20],0; xor ecx,ecx; xor edx,edx; xor r8d,r8d; xor r9d,r9d; call qword ptr [0xF9A8C78]; int3`
- `indirect = *(uintptr_t*)(imageBase + 0xF9A8C78); indirect(0,0,0,0);` then `int3` (noreturn).

## Struct fields touched (base = `self` = `BgfxFrameBuilderSlot0*`)

| Offset | Size | R/W | Direction | Instruction | Meaning | Tag |
|---|---|---|---|---|---|---|
| 0x60 | 8 | R | read field_0x60 | 0xbc3c6c3 `mov rcx,[r8+0x60]` | slot begin pointer | [V] |
| 0x60 | 8 | R | read via [ptr-8] | 0xbc3c6dc `mov rax,[rcx-8]` | chunk size before slot begin | [V] |
| 0x60 | 16 | W | write field_0x60+0x0 | 0xbc3c700 `movups [rdi],xmm0` | zero field_0x60 + 8 pad bytes | [V] |
| 0x70 | 8 | R | read field_0x70 | 0xbc3c6cc `mov rdx,[rsi+0x70]` | slot end pointer | [V] |
| 0x70 | 8 | W | write field_0x70 | 0xbc3c703 `mov [rdi+0x10],0` | clear slot end | [V] |
| 0x50 | 8 | R | read field_0x50 | 0xbc3c70b `mov rax,[rsi+0x50]` | size field | [V] |
| 0x50 | 8 | W | write field_0x50 | 0xbc3c74e `mov [rsi+0x50],0xF` | reset size to 0xF | [V] |
| 0x38 | 8 | R | read field_0x38 | 0xbc3c715 `mov rcx,[rsi+0x38]` | slot pointer | [V] |
| 0x38 | 8 | R | read via [ptr-8] | 0xbc3c726 `mov r8,[rcx-8]` | chunk before slot pointer | [V] |
| 0x38 | 1 | W | write field_0x38 byte | 0xbc3c756 `mov byte [rsi+0x38],0` | clear low byte of slot pointer | [V] |
| 0x48 | 8 | W | write field_0x48 | 0xbc3c746 `mov [rsi+0x48],0` | clear field_0x48 | [V] |
| stack [rsp+0x20] | 8 | W | stack store | 0xbc3c761 `mov [rsp+0x20],0` | error-path arg home slot | [V] |
| data 0xF9A8C78 | 8 | R | indirect call target | 0xbc3c774 `call [0xF9A8C78]` | function pointer | [V] |

## Callees

- `sub_e935700` (0xe935700): direct call x2 (0xbc3c6f8, 0xbc3c741). It is a thunk: `jmp sub_392960` @0xe935700. Extent "heuristic(no .pdata entry)". Appears in NEITHER docs/data/native_functions.tsv NOR docs/data/native_boundary.tsv → **UNRESOLVED CALL**.
- `call qword ptr [0xF9A8C78]` (0xbc3c774): indirect-global via data address 0xF9A8C78. Not in native_boundary.tsv, native_unresolved_indirect.tsv, or native_boundary_candidates.tsv → **UNRESOLVED CALL**.
- callees_in_set: none (per docs/progress/_d_U-EX1.bc3c6b0.txt).

## Reversed source (complete)

// 0xbc3c6b0  push rsi
// 0xbc3c6b1  push rdi
// 0xbc3c6b2  sub rsp,0x28
// 0xbc3c6b6  cmp rcx,1
// 0xbc3c6ba  jne 0xBC3C75A
if (mode != kBc3c6b0ModeRequired) return;   // -> 0xbc3c75a add rsp,0x28 / pop rdi / pop rsi / ret
// 0xbc3c6c0  mov rsi,r8
BgfxFrameBuilderSlot0* self = fb;
// 0xbc3c6c3  mov rcx,[r8+0x60]
// 0xbc3c6c7  test rcx,rcx
// 0xbc3c6ca  je short 0xBC3C70B
if (self->field_0x60 != nullptr) {
// 0xbc3c6cc  mov rdx,[rsi+0x70]
// 0xbc3c6d0  sub rdx,rcx
// 0xbc3c6d3  cmp rdx,0x1000
  uint64_t slot_size = self->field_0x70 - self->field_0x60;
// 0xbc3c6da  jb short 0xBC3C6F4
  if (slot_size >= kBc3c6b0SlotSizeLarge) {
// 0xbc3c6dc  mov rax,[rcx-8]
// 0xbc3c6e0  add rcx,0xFFFFFFFFFFFFFFF8
// 0xbc3c6e4  sub rcx,rax
// 0xbc3c6e7  cmp rcx,0x20
// 0xbc3c6eb  jae short 0xBC3C761
    uint64_t chunk = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(self->field_0x60) - 8);
    uint64_t guard = (reinterpret_cast<uintptr_t>(self->field_0x60) - 8) - chunk;
    if (guard >= kBc3c6b0GuardGap) goto bc3c6b0_error;
// 0xbc3c6ed  add rdx,0x27
// 0xbc3c6f1  mov rcx,rax
    uint64_t arg0 = chunk;
    uint64_t arg1 = slot_size + kBc3c6b0Size1Bias;
  } else {
    uint64_t arg0 = reinterpret_cast<uint64_t>(self->field_0x60);
    uint64_t arg1 = slot_size;
  }
// 0xbc3c6f4  lea rdi,[rsi+0x60]
// 0xbc3c6f8  call 0xE935700
  sub_e935700(arg0, arg1, self, a3);
// 0xbc3c6fd  xorps xmm0,xmm0
// 0xbc3c700  movups [rdi],xmm0
// 0xbc3c703  mov qword ptr [rdi+0x10],0
  self->field_0x60 = nullptr;
  self->field_0x70 = nullptr;
}
// 0xbc3c70b  mov rax,[rsi+0x50]
// 0xbc3c70f  cmp rax,0x10
// 0xbc3c713  jb short 0xBC3C746
if (self->field_0x50 >= kBc3c6b0Slot2Small) {
// 0xbc3c715  mov rcx,[rsi+0x38]
  void* slot_ptr = self->field_0x38;
// 0xbc3c719  lea rdx,[rax+1]
  uint64_t size_plus1 = self->field_0x50 + 1;
// 0xbc3c71d  cmp rdx,0x1000
// 0xbc3c724  jb short 0xBC3C741
  if (size_plus1 >= kBc3c6b0SlotSizeLarge) {
// 0xbc3c726  mov r8,[rcx-8]
// 0xbc3c72a  add rcx,0xFFFFFFFFFFFFFFF8
// 0xbc3c72e  sub rcx,r8
// 0xbc3c731  cmp rcx,0x20
// 0xbc3c735  jae short 0xBC3C761
    uint64_t chunk = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(slot_ptr) - 8);
    uint64_t guard = (reinterpret_cast<uintptr_t>(slot_ptr) - 8) - chunk;
    if (guard >= kBc3c6b0GuardGap) goto bc3c6b0_error;
// 0xbc3c737  add rax,0x28
// 0xbc3c73b  mov rdx,rax
// 0xbc3c73e  mov rcx,r8
    uint64_t arg0 = chunk;
    uint64_t arg1 = self->field_0x50 + kBc3c6b0Size2Bias;
    uint64_t arg2 = chunk;
  } else {
    uint64_t arg0 = reinterpret_cast<uint64_t>(slot_ptr);
    uint64_t arg1 = size_plus1;
    uint64_t arg2 = reinterpret_cast<uint64_t>(self);
  }
// 0xbc3c741  call 0xE935700
  sub_e935700(arg0, arg1, reinterpret_cast<void*>(arg2), a3);
}
// 0xbc3c746  mov qword ptr [rsi+0x48],0
self->field_0x48 = 0;
// 0xbc3c74e  mov qword ptr [rsi+0x50],0xF
self->field_0x50 = kBc3c6b0ResetSize;
// 0xbc3c756  mov byte ptr [rsi+0x38],0
*reinterpret_cast<uint8_t*>(&self->field_0x38) = 0;
return;
bc3c6b0_error:
// 0xbc3c761  mov qword ptr [rsp+0x20],0
// 0xbc3c76a  xor ecx,ecx
// 0xbc3c76c  xor edx,edx
// 0xbc3c76e  xor r8d,r8d
// 0xbc3c771  xor r9d,r9d
// 0xbc3c774  call qword ptr [0xF9A8C78]
// 0xbc3c77a  int3
  uintptr_t* fn_ptr = reinterpret_cast<uintptr_t*>(RewriteRegistry::imageBase() + 0xF9A8C78);
  using IndirectFn = void (*)(uint64_t, uint64_t, uint64_t, uint64_t);
  IndirectFn indirect = reinterpret_cast<IndirectFn>(*fn_ptr);
  indirect(0, 0, 0, 0);
  __assume(false);   // original executes int3 here (noreturn)

## Struct layout (asserted in src/client/features/render/native/bgfx/sub_bc3c6b0.h)

struct BgfxFrameBuilderSlot0 {
    char pad_0x00[0x38];
    void* field_0x38;        // +0x38
    char pad_0x40[0x8];
    uint64_t field_0x48;     // +0x48
    uint64_t field_0x50;     // +0x50
    char pad_0x58[0x8];
    void* field_0x60;        // +0x60
    char pad_0x68[0x8];
    void* field_0x70;        // +0x70
};
static_assert(sizeof(BgfxFrameBuilderSlot0) == 0x78);
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x38) == 0x38);
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x48) == 0x48);
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x50) == 0x50);
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x60) == 0x60);
static_assert(offsetof(BgfxFrameBuilderSlot0, field_0x70) == 0x70);

## Ownership / threading

No threading model information available statically. The function mutates fields of the caller-owned slot block in place. V2 footprint: the full `BgfxFrameBuilderSlot0` object (0x78 bytes). Callers: 10 functions (sub_bbdd780, sub_bbe2a30, sub_bc3c150, sub_bc3c280, sub_bc3c430 x3, sub_bc41420, sub_bc42110, sub_bc45990, sub_c2965e0, sub_c296860) [V rdis callers].

## OPEN questions

- sub_e935700 / sub_392960: neither lifted nor boundary; argument types and semantics unknown. Declared as `extern "C" void sub_e935700(uint64_t, uint64_t, void*, void*)` matching register usage. [UNRESOLVED CALL]
- call qword ptr [0xF9A8C78]: target symbol unknown; indirect through absolute data address. [UNRESOLVED CALL]

## Verbatim instruction listing (for verify_oc)

0xbc3c6b0  push rsi
0xbc3c6b1  push rdi
0xbc3c6b2  sub rsp,0x28
0xbc3c6b6  cmp rcx,1
0xbc3c6ba  jne 0xBC3C75A
0xbc3c6c0  mov rsi,r8
0xbc3c6c3  mov rcx,[r8+0x60]
0xbc3c6c7  test rcx,rcx
0xbc3c6ca  je short 0xBC3C70B
0xbc3c6cc  mov rdx,[rsi+0x70]
0xbc3c6d0  sub rdx,rcx
0xbc3c6d3  cmp rdx,0x1000
0xbc3c6da  jb short 0xBC3C6F4
0xbc3c6dc  mov rax,[rcx-8]
0xbc3c6e0  add rcx,0xFFFFFFFFFFFFFFF8
0xbc3c6e4  sub rcx,rax
0xbc3c6e7  cmp rcx,0x20
0xbc3c6eb  jae short 0xBC3C761
0xbc3c6ed  add rdx,0x27
0xbc3c6f1  mov rcx,rax
0xbc3c6f4  lea rdi,[rsi+0x60]
0xbc3c6f8  call 0xE935700
0xbc3c6fd  xorps xmm0,xmm0
0xbc3c700  movups [rdi],xmm0
0xbc3c703  mov qword ptr [rdi+0x10],0
0xbc3c70b  mov rax,[rsi+0x50]
0xbc3c70f  cmp rax,0x10
0xbc3c713  jb short 0xBC3C746
0xbc3c715  mov rcx,[rsi+0x38]
0xbc3c719  lea rdx,[rax+1]
0xbc3c71d  cmp rdx,0x1000
0xbc3c724  jb short 0xBC3C741
0xbc3c726  mov r8,[rcx-8]
0xbc3c72a  add rcx,0xFFFFFFFFFFFFFFF8
0xbc3c72e  sub rcx,r8
0xbc3c731  cmp rcx,0x20
0xbc3c735  jae short 0xBC3C761
0xbc3c737  add rax,0x28
0xbc3c73b  mov rdx,rax
0xbc3c73e  mov rcx,r8
0xbc3c741  call 0xE935700
0xbc3c746  mov qword ptr [rsi+0x48],0
0xbc3c74e  mov qword ptr [rsi+0x50],0xF
0xbc3c756  mov byte ptr [rsi+0x38],0
0xbc3c75a  add rsp,0x28
0xbc3c75e  pop rdi
0xbc3c75f  pop rsi
0xbc3c760  ret
0xbc3c761  mov qword ptr [rsp+0x20],0
0xbc3c76a  xor ecx,ecx
0xbc3c76c  xor edx,edx
0xbc3c76e  xor r8d,r8d
0xbc3c771  xor r9d,r9d
0xbc3c774  call qword ptr [0xF9A8C78]
0xbc3c77a  int3
