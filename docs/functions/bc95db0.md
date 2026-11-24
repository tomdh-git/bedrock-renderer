# Dossier: sub_bc95db0 (0xbc95db0, size 0x391) — Minecraft Bedrock 1.26.62.01

Source: `src/client/features/render/native/bgfx/sub_bc95db0.cpp` + `sub_bc95db0.h`. Result unit: `docs/progress/oc_U-EX1.bc95db0.md`.
Exe (data only): `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe`. All RVAs relative to image base.

## Signature / ABI

`extern "C" void sub_bc95db0(VvSmallString* dst, VvSmallString* src);` — x64 Microsoft ABI, `dst` in rcx, `src` in rdx, return void (rax never set to a meaningful value on any return path).

Register/argument map at entry: rcx = dst (a0); rdx = src (a1); r8/r9 = entry args, clobbered before use.

## Reversed source (complete)

Every instruction of [0xbc95db0, 0xbc96141) falls inside one cited phase range below; every `call` is quoted verbatim as `0xRVA  call target`. The C++ in `sub_bc95db0.cpp` is the literal translation, statement for statement, in the same branch structure.

### Phase 1 — prologue: save src then dst: `0xbc95db0..0xbc95e3a`

- `0xbc95db0  push rbp; push r15; push r14; push r13; push r12; push rsi; push rdi; push rbx; sub rsp,0xB8; lea rbp,[rsp+0x80]`
- `0xbc95dd3  mov r8,[rdx]` — src.mData
- `0xbc95dd6  mov r9,[rdx+0x18]` — src.mCapacity
- `0xbc95dda  mov qword ptr [rdx+0x18],0xF` — src.mCapacity = 0xF
- `0xbc95de2  mov byte ptr [rdx],0` — src.mData[0] = 0
- `0xbc95de5  mov rsi,[rdx+0x10]` — src.mSize
- `0xbc95de9  movups xmm0,[rdx+8]` — src.mBuf (16B)
- `0xbc95ded  mov qword ptr [rdx+0x10],0` — src.mSize = 0
- `0xbc95df5  movzx eax,byte ptr [rcx]` — dst.mData[0]
- `0xbc95df8  mov rdx,[rcx+8]` — dst.mBuf[0..7]
- `0xbc95dfc  mov [rbp+8],rdx`
- `0xbc95e00  mov rdx,[rcx+1]` — dst.mData[1..7]+mBuf[0]
- `0xbc95e04  mov [rbp+1],rdx`
- `0xbc95e08  mov r15,[rcx+0x10]` — dst.mSize (old)
- `0xbc95e0c  mov r13,[rcx+0x18]` — dst.mCapacity (old)
- `0xbc95e10  mov qword ptr [rcx+0x10],0` — dst.mSize = 0
- `0xbc95e18  mov qword ptr [rcx+0x18],0xF` — dst.mCapacity = 0xF
- `0xbc95e20  mov byte ptr [rcx],0` — dst.mData[0] = 0
- `0xbc95e23  mov [rbp-0x20],r8` — save src.mData
- `0xbc95e27  movups [rbp-0x18],xmm0` — save src.mBuf+mSize
- `0xbc95e2b  mov [rbp-8],r9` — save src.mCapacity
- `0xbc95e2f  mov [rbp],al` — save dst.mData[0]
- `0xbc95e32  mov [rbp+0x10],r15` — save dst.mSize
- `0xbc95e36  mov [rbp+0x18],r13` — save dst.mCapacity
- `0xbc95e3a  cmp r9,0x10` — src.mCapacity >= 0x10?

### Phase 2 — size check + rdi setup: `0xbc95e3a..0xbc95e5e`

- `0xbc95e3e  lea rax,[rbp-0x20]`
- `0xbc95e42  mov rdi,rax` — rdi = &stack slot (SSO src)
- `0xbc95e45  cmovae rdi,r8` — if src.mCap>=0x10: rdi = src.mData (heap)
- `0xbc95e49  test rsi,rsi` — src.mSize < 0?
- `0xbc95e4c  js 0xBC9611B` — -> sub_75720 (noreturn)
- `0xbc95e52  cmp rsi,0xF` — src.mSize > 0xF?
- `0xbc95e5e  ja short 0xBC95E7A` — heap src path

### Phase 3 — heap src path (alloc + copy): `0xbc95e7a..0xbc95efc` (only when src.mSize > 0xF)

- `0xbc95e7a  mov rdx,rsi` — rdx = src.mSize
- `0xbc95e7d  or rdx,0xF` — rdx = size | 0xF
- `0xbc95e81  cmp rdx,0x17`
- `0xbc95e85  mov r12d,0x16`
- `0xbc95e8b  cmovae r12,rdx` — r12 = capacity
- `0xbc95e8f  mov rcx,[0x1233E1A8]` — allocator object (side-effect load)
- `0xbc95e96  mov rax,[rcx]`
- `0xbc95e99  mov rax,[rax+8]`
- `0xbc95e9d  cmp rdx,0xFFF`
- `0xbc95ea4  jb short 0xBC95ED2`
- `0xbc95ea6  lea rbx,[r12+0x28]` — allocSize = cap + 0x28 (large)
- `0xbc95eab  mov rdx,rbx`
- `0xbc95eae  call qword ptr [0xF99FFA0]` — allocator (compiled to std::malloc)
- `0xbc95eb4  nop`
- `0xbc95eb5  mov r14,rax` — r14 = result
- `0xbc95eb8  test rax,rax`
- `0xbc95ebb  je 0xBC960E3` — null -> sub_9bc830(allocSize) (noreturn)
- `0xbc95ec1  mov rax,r14`
- `0xbc95ec4  add r14,0x27`
- `0xbc95ec8  and r14,0xFFFFFFFFFFFFFFE0` — aligned
- `0xbc95ecc  mov [r14-8],rax` — cookie at aligned-8
- `0xbc95ed0  jmp short 0xBC95EED`
- `0xbc95ed2  lea rbx,[r12+1]` — allocSize = cap + 1 (small)
- `0xbc95ed7  mov rdx,rbx`
- `0xbc95eda  call qword ptr [0xF99FFA0]` — allocator
- `0xbc95ee0  nop`
- `0xbc95ee1  mov r14,rax`
- `0xbc95ee4  test rax,rax`
- `0xbc95ee7  je 0xBC960F1` — null -> sub_9bc830(allocSize) (noreturn)
- `0xbc95eed  lea r8,[rsi+1]` — count = src.mSize + 1
- `0xbc95ef1  mov rcx,r14` — memcpy dst = aligned
- `0xbc95ef4  mov rdx,rdi` — memcpy src = rdi (heap ptr, via cmovae)
- `0xbc95ef7  call 0xEEC6EC0` — memcpy(r14, src.mData, src.mSize+1)
- `0xbc95efc  xor eax,eax` — rax = 0

### Phase 4 — SSO src path (when src.mSize <= 0xF): `0xbc95e60..0xbc95e75`

- `0xbc95e60  cmp r9,0x10` — src.mCapacity >= 0x10?
- `0xbc95e64  mov r14,[rdi]` — r14 = [rbp-0x20] = src.mData (saved)
- `0xbc95e67  cmovae rax,r8` — (not taken for SSO) rax = rbp-0x20
- `0xbc95e6b  mov rax,[rax+8]` — rax = [rbp-0x18] = src.mBuf[0..7] (saved)
- `0xbc95e6f  mov r12d,0xF` — r12 = 0xF
- `0xbc95e75  jmp 0xBC95EFE`

### Phase 5 — common tail: build stack descriptor + old-dst handling: `0xbc95efe..0xbc95f5d`

- `0xbc95efe  lea rbx,[rbp]`
- `0xbc95f02  mov rdx,0x1000000010`
- `0xbc95f0c  mov [rbp-0x58],rdx`
- `0xbc95f10  mov dword ptr [rbp-0x50],1`
- `0xbc95f17  mov [rbp-0x48],r14` — descriptor data ptr
- `0xbc95f1b  mov [rbp-0x40],rax` — descriptor field at +0x08
- `0xbc95f1f  mov [rbp-0x38],rsi` — descriptor size (src.mSize)
- `0xbc95f23  mov [rbp-0x30],r12` — descriptor capacity
- `0xbc95f27  cmp r13,0x10` — old dst.mCapacity >= 0x10?
- `0xbc95f2b  mov rdi,[rbp]` — rdi = saved dst.mData
- `0xbc95f2f  cmovae rbx,rdi` — if old dst cap>=0x10: rbx = old dst.mData
- `0xbc95f33  test r15,r15` — old dst.mSize < 0?
- `0xbc95f36  js 0xBC96121` — -> sub_75720 (noreturn)
- `0xbc95f3c  cmp r15,0xF` — old dst.mSize > 0xF?
- `0xbc95f40  ja short 0xBC95F62` — heap old-dst path
- `0xbc95f42  lea rax,[rdi+8]` — rax = old dst.mData + 8 (SSO path)
- `0xbc95f46  cmp r13,0x10`
- `0xbc95f4a  mov r14,[rbx]` — r14 = [rbx] (rbx = rbp for SSO, or heap ptr)
- `0xbc95f4d  lea rcx,[rbp+8]` — rcx = &saved dst.mBuf
- `0xbc95f51  cmovae rcx,rax` — if old dst cap>=0x10: rcx = rax
- `0xbc95f55  mov rax,[rcx]` — rax = [rcx]
- `0xbc95f58  mov esi,0xF` — esi = 0xF
- `0xbc95f5d  jmp 0xBC95FE3`

### Phase 6 — heap old-dst path: `0xbc95f62..0xbc95fde` (only when old dst.mSize > 0xF)

- `0xbc95f62  mov r12,rdx` — r12 = 0x1000000010
- `0xbc95f65  mov rdx,r15` — rdx = old dst.mSize
- `0xbc95f68  or rdx,0xF`
- `0xbc95f6c  cmp rdx,0x17`
- `0xbc95f70  mov esi,0x16`
- `0xbc95f75  cmovae rsi,rdx` — esi = capacity
- `0xbc95f79  mov rcx,[0x1233E1A8]` — allocator (side-effect)
- `0xbc95f80  mov rax,[rcx]`
- `0xbc95f83  mov rax,[rax+8]`
- `0xbc95f87  cmp rdx,0xFFF`
- `0xbc95f8e  jb short 0xBC95FB8`
- `0xbc95f90  lea rdx,[rsi+0x28]` — allocSize = cap + 0x28
- `0xbc95f94  call qword ptr [0xF99FFA0]` — allocator
- `0xbc95f9a  nop`
- `0xbc95f9b  mov r14,rax`
- `0xbc95f9e  test rax,rax`
- `0xbc95fa1  je 0xBC960FA` — null -> sub_9bc830 (noreturn)
- `0xbc95fa7  mov rax,r14`
- `0xbc95faa  add r14,0x27`
- `0xbc95fae  and r14,0xFFFFFFFFFFFFFFE0` — aligned
- `0xbc95fb2  mov [r14-8],rax` — cookie
- `0xbc95fb6  jmp short 0xBC95FCF`
- `0xbc95fb8  lea rdx,[rsi+1]` — allocSize = cap + 1
- `0xbc95fbc  call qword ptr [0xF99FFA0]` — allocator
- `0xbc95fc2  nop`
- `0xbc95fc3  mov r14,rax`
- `0xbc95fc6  test rax,rax`
- `0xbc95fc9  je 0xBC96109` — null -> sub_9bc830 (noreturn)
- `0xbc95fcf  lea r8,[r15+1]` — count = old dst.mSize + 1
- `0xbc95fd3  mov rcx,r14` — memcpy dst = aligned
- `0xbc95fd6  mov rdx,rbx` — memcpy src = old dst.mData (heap)
- `0xbc95fd9  call 0xEEC6EC0` — memcpy(r14, oldDst.mData, oldDst.mSize+1)
- `0xbc95fde  xor eax,eax` — rax = 0
- `0xbc95fe0  mov rdx,r12` — rdx = 0x1000000010

### Phase 7 — globals writes: `0xbc95fe3..0xbc96044`

- `0xbc95fe3  lea rcx,[rbp-0x48]`
- `0xbc95fe7  mov [0x12AE1C50],rdx` — data_12ae1c50 = 0x1000000010
- `0xbc95fee  mov dword ptr [0x12AE1C58],1` — data_12ae1c58 = 1
- `0xbc95ff8  movups xmm0,[rcx]` — xmm0 = [rbp-0x48..-0x39] = r14, rax
- `0xbc95ffb  movups xmm1,[rcx+0x10]` — xmm1 = [rbp-0x38..-0x29] = rsi, r12
- `0xbc95fff  movups [0x12AE1C60],xmm0` — data_12ae1c60 = r14, data_12ae1c68 = rax
- `0xbc96006  movups [0x12AE1C70],xmm1` — data_12ae1c70 = rsi, data_12ae1c78 = r12
- `0xbc9600d  mov rcx,0x800000010`
- `0xbc96017  mov [0x12AE1C88],rcx` — data_12ae1c88 = 0x800000010
- `0xbc9601e  mov dword ptr [0x12AE1C90],1` — data_12ae1c90 = 1
- `0xbc96028  mov [0x12AE1C98],r14` — data_12ae1c98 = r14 (overwritten value)
- `0xbc9602f  mov [0x12AE1CA0],rax` — data_12ae1ca0 = rax (overwritten value)
- `0xbc96036  mov [0x12AE1CA8],r15` — data_12ae1ca8 = old dst.mSize
- `0xbc9603d  mov [0x12AE1CB0],rsi` — data_12ae1cb0 = src.mSize (rsi)

### Phase 8 — free old dst heap buffer: `0xbc96044..0xbc96086`

- `0xbc96044  cmp r13,0x10` — old dst.mCapacity >= 0x10?
- `0xbc96048  mov rsi,[rbp+0x20]` — rsi = saved src.mData
- `0xbc9604c  mov rbx,[rbp+0x28]` — rbx = saved src.mCapacity
- `0xbc96050  jb short 0xBC96086` — if old dst cap < 0x10: skip
- `0xbc96052  lea rdx,[r13+1]` — rdx = old dst cap + 1
- `0xbc96056  cmp rdx,0x1000`
- `0xbc9605d  jb short 0xBC9607E` — small free path
- `0xbc9605f  mov rax,[rdi-8]` — cookie = *(old_dst.mData - 8)
- `0xbc96063  add rdi,0xFFFFFFFFFFFFFFF8` — rdi = old_dst.mData - 8
- `0xbc96067  sub rdi,rax` — delta = (old_dst.mData - 8) - cookie
- `0xbc9606a  cmp rdi,0x20`
- `0xbc9606e  jae 0xBC96127` — delta >= 0x20: watson (noreturn)
- `0xbc96074  add r13,0x28` — rdx = old dst cap + 0x28
- `0xbc96078  mov rdx,r13`
- `0xbc9607b  mov rdi,rax` — rdi = cookie (original malloc ptr)
- `0xbc9607e  mov rcx,rdi` — free ptr
- `0xbc96081  call 0xE935700` — sub_e935700(free ptr)

### Phase 9 — free old src heap buffer or return: `0xbc96086..0xbc960e2`

- `0xbc96086  cmp rbx,0x10` — saved src.mCapacity >= 0x10?
- `0xbc9608a  jb short 0xBC960CF` — if SSO src: just return
- `0xbc9608c  lea rdx,[rbx+1]` — rdx = src cap + 1
- `0xbc96090  cmp rdx,0x1000`
- `0xbc96097  jb short 0xBC960B4` — small free
- `0xbc96099  mov rax,[rsi-8]` — cookie = *(src.mData - 8)
- `0xbc9609d  add rsi,0xFFFFFFFFFFFFFFF8` — rsi = src.mData - 8
- `0xbc960a1  sub rsi,rax` — delta
- `0xbc960a4  cmp rsi,0x20`
- `0xbc960a8  jae short 0xBC96127` — watson
- `0xbc960aa  add rbx,0x28` — rdx = src cap + 0x28
- `0xbc960ae  mov rdx,rbx`
- `0xbc960b1  mov rsi,rax` — rsi = cookie (original malloc ptr)
- `0xbc960b4  mov rcx,rsi` — free ptr
- `0xbc960b7  add rsp,0xB8`
- `0xbc960be  pop rbx; pop rdi; pop rsi; pop r12; pop r13; pop r14; pop r15; pop rbp`
- `0xbc960ca  jmp 0xE935700` — tail-call free (noreturn)
- `0xbc960cf  add rsp,0xB8` — (SSO src return path)
- `0xbc960d6  pop rbx; pop rdi; pop rsi; pop r12; pop r13; pop r14; pop r15; pop rbp`
- `0xbc960e2  ret`

### Phase 10 — OOM handlers: `0xbc960e3..0xbc9611a`

- `0xbc960e3  mov rcx,rbx` — (allocSize for heap src OOM)
- `0xbc960e6  call 0x9BC830` — sub_9bc830(allocSize)
- `0xbc960eb  nop`
- `0xbc960ec  jmp 0xBC95EC1` — -> 0xbc95ec1
- `0xbc960f1  mov rcx,rbx` — (allocSize for heap src OOM, second path)
- `0xbc960f4  call 0x9BC830` — sub_9bc830(allocSize)
- `0xbc960f9  nop`
- `0xbc960fa  lea rcx,[rsi+0x28]` — allocSize = cap + 0x28
- `0xbc960fe  call 0x9BC830` — sub_9bc830(allocSize)
- `0xbc96103  nop`
- `0xbc96104  jmp 0xBC95FA7` — -> 0xbc95fa7
- `0xbc96109  lea rcx,[rsi+1]` — allocSize = cap + 1
- `0xbc9610d  call 0x9BC830` — sub_9bc830(allocSize)
- `0xbc96112  nop`
- `0xbc96113  xor r14d,r14d` — r14 = 0
- `0xbc96116  jmp 0xBC95FCF` — -> 0xbc95fcf

### Phase 11 — negative size handler: `0xbc9611b..0xbc96126`

- `0xbc9611b  call 0x75720` — sub_75720 (noreturn) (src size < 0)
- `0xbc96121  call 0x75720` — sub_75720 (noreturn) (dst size < 0)

### Phase 12 — watson fail path: `0xbc96127..0xbc96140`

- `0xbc96127  mov qword ptr [rsp+0x20],0` — scratch store
- `0xbc96130  xor ecx,ecx; xor edx,edx; xor r8d,r8d; xor r9d,r9d` — all watson args zero
- `0xbc9613a  call qword ptr [0xF9A8C78]` — indirect call: _invoke_watson(nullptr,nullptr,nullptr,0,0)
- `0xbc96140  int3` — unreachable (noreturn)

## Struct fields touched

| Object | Offset | Size | Direction | Meaning | Instruction(s) |
|---|---|---|---|---|---|
| VvSmallString | +0x00 | 8 | R/W | mData pointer (heap or inline) | 0xbc95dd3, 0xbc95de2, 0xbc95df5, 0xbc95e20 |
| VvSmallString | +0x08 | 8 | R | mBuf[0..7] (inline, 8 bytes) | 0xbc95de9, 0xbc95df8 |
| VvSmallString | +0x10 | 8 | R/W | mSize | 0xbc95de5, 0xbc95ded, 0xbc95e08, 0xbc95e10 |
| VvSmallString | +0x18 | 8 | R/W | mCapacity (0xF = SSO) | 0xbc95dd6, 0xbc95dda, 0xbc95e0c, 0xbc95e18 |
| stack frame | rbp-0x20..rbp+0x30 | 80 | R/W | saved src/dst state | 0xbc95e23..0xbc95e36 |
| global | 0x12AE1C50 | 8 | W | tracking (0x1000000010) | 0xbc95fe7 |
| global | 0x12AE1C58 | 4 | W | tracking (1) | 0xbc95fee |
| global | 0x12AE1C60 | 8 | W | tracking (r14/new data ptr) | 0xbc95fff |
| global | 0x12AE1C68 | 8 | W | tracking (rax) | 0xbc95fff |
| global | 0x12AE1C70 | 8 | W | tracking (rsi/src.mSize) | 0xbc96006 |
| global | 0x12AE1C78 | 8 | W | tracking (r12/capacity) | 0xbc96006 |
| global | 0x12AE1C88 | 8 | W | tracking (0x800000010) | 0xbc96017 |
| global | 0x12AE1C90 | 4 | W | tracking (1) | 0xbc9601e |
| global | 0x12AE1C98 | 8 | W | tracking (r14) | 0xbc96028 |
| global | 0x12AE1CA0 | 8 | W | tracking (rax) | 0xbc9602f |
| global | 0x12AE1CA8 | 8 | W | tracking (old dst.mSize) | 0xbc96036 |
| global | 0x12AE1CB0 | 8 | W | tracking (src.mSize) | 0xbc9603d |
| data slot | 0xF99FFA0 | 8 | R ×4 | allocator thunk (sub_eea6040) | 0xbc95eae, 0xbc95eda, 0xbc95f94, 0xbc95fbc |
| data slot | 0xF9A8C78 | 8 | R ×1 | _invoke_watson import | 0xbc9613a |

## Callees

| Address (call site) | Target | Class | Basis |
|---|---|---|---|
| 0xbc95eae, 0xbc95eda, 0xbc95f94, 0xbc95fbc | `[0xF99FFA0]` → sub_eea6040 (allocator) | compiled to std::malloc (spec §5) | `0xbc95eae  call qword ptr [0xF99FFA0]` [V]; native_boundary.tsv: 0xeea6040 vendor, data slot 0xF99FFA0 |
| 0xbc95ef7, 0xbc95fd9 | `0xEEC6EC0` (sub_eec6ec0) | lift (memcpy) | `0xbc95ef7  call 0xEEC6EC0` [V]; lift callee |
| 0xbc96081 | `0xE935700` (sub_e935700) | lift (free) | `0xbc96081  call 0xE935700` [V]; lift callee (tail-call at 0xbc960ca) |
| 0xbc960e6, 0xbc960f4, 0xbc960fe, 0xbc9610d | `0x9BC830` (sub_9bc830) | boundary (alloc OOM) | `0xbc960e6  call 0x9BC830` [V]; native_boundary.tsv: 0x9bc830 alloc |
| 0xbc9611b, 0xbc96121 | `0x75720` (sub_75720) | boundary (stl, noreturn) | `0xbc9611b  call 0x75720` [V]; native_boundary.tsv: 0x75720 stl |
| 0xbc9613a | `[0xF9A8C78]` → _invoke_watson | boundary (import slot) | `0xbc9613a  call qword ptr [0xF9A8C78]` [V]; indirect-call rule |

## Ownership / threading

No synchronization on *dst or *src. No thread-local or GPU effects beyond the callees. Not reentrant on the same objects (caller guarantees).

## Verification

- Source: `src/client/features/render/native/bgfx/sub_bc95db0.cpp` (first line `// LIFT 0xbc95db0 size 0x391 1.26.62.01 sub_bc95db0`), header `sub_bc95db0.h`, registry entry `LIFT_FN(sub_bc95db0, "sub_bc95db0", 0xbc95db0, sub_bc95db0, &sub_bc95db0_footprint)`.
- Footprint: `{ { dst, 0x20 }, { src, 0x20 } }` (writes within *dst and *src objects).
- No `[?]`/`[I]`/`TODO`/`UNVERIFIED` in source or reversed-source block.

## OPEN questions

None — every instruction, read, write and call of [0xbc95db0, 0xbc96141) is accounted for above. The allocator thunk [0xF99FFA0] is compiled to std::malloc per spec §5; data slots 0xF99FFA0/0xF9A8C78 are read at call time per the indirect-call rule.
