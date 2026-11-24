# Function dossier: sub_bca92f0 (0xbca92f0)

Version: 1.26.62.01. Region: bgfx. Milestone: D0. Depth: 2.
Source: `src/client/features/render/native/bgfx/sub_bca92f0.cpp` + header `sub_bca92f0.h`.

## Signature

`extern "C" void sub_bca92f0(Builder* self);` — x64 Microsoft ABI, rcx = this (Builder*), returns void.
The function is a temp-buffer releaser: it releases two heap buffers (buffer A at +0x00/+0x10/+0x18, buffer B at +0x98/+0xA8/+0xB0), releases a shared RefCounted at +0x28 (strong then weak refcount drop), releases an owned RefCounted at +0x88 (unless it is the inline object at +0x50), and zeroes all buffer fields. On a heap-guard failure it calls an import-slot fail handler then int3 (noreturn).

## Register / argument map

- rcx = `this` (Builder*), copied to rsi at 0xbca92f6.
- rdx = scratch: holds `cap_b + 1` / `cap_a + 1` (dead inside callee), then `flag` (setne result, 0 or 1) at 0xbca936e, clobbered by thunk calls.
- r8 = heap block base `[buf - 8]` on the guard path.
- All other registers are scratch / restored by the epilogue.

## Disassembly phases

// 0xbca92f0..0xbca9306: prologue; load cap_b at +0xB0; if cap_b < 0x10 skip to buffer-A phase.
`0xbca92f0  push rsi`
`0xbca92f1  push rdi`
`0xbca92f2  sub rsp,0x28`
`0xbca92f6  mov rsi,rcx`
`0xbca92f9  mov rax,[rcx+0xB0]`   ; R a0+0xB0
`0xbca9300  cmp rax,0x10`
`0xbca9304  jb short 0xBCA933E`   ; -> loc_bca933e

// 0xbca9306..0xbca9339: buffer B release. rcx = buf_b (+0x98); if cap_b + 1 < 0x1000 call sub_e935700(buf_b),
// else compute heap block base [buf_b-8], guard >= 0x20, call sub_e935700([buf_b-8]).
`0xbca9306  mov rcx,[rsi+0x98]`   ; R a0+0x98
`0xbca930d  lea rdx,[rax+1]`      ; R *(a0+0xB0)+0x1
`0xbca9311  cmp rdx,0x1000`
`0xbca9318  jb short 0xBCA9339`   ; -> loc_bca9339
`0xbca931a  mov r8,[rcx-8]`       ; R *(a0+0x98)-0x8
`0xbca931e  add rcx,0xFFFFFFFFFFFFFFF8`
`0xbca9322  sub rcx,r8`
`0xbca9325  cmp rcx,0x20`
`0xbca9329  jae 0xBCA9411`        ; -> loc_bca9411 (heap-guard fail)
`0xbca932f  add rax,0x28`         ; dead size
`0xbca9333  mov rdx,rax`
`0xbca9336  mov rcx,r8`
`0xbca9339  call 0xE935700`       ; -> sub_e935700

// 0xbca933e..0xbca935b: reset buffer B fields: size_b=0, cap_b=0xF, buf_b=0.
`0xbca933e  mov qword ptr [rsi+0xA8],0`   ; W a0+0xA8
`0xbca9349  mov qword ptr [rsi+0xB0],0xF` ; W a0+0xB0
`0xbca9354  mov byte ptr [rsi+0x98],0`    ; W a0+0x98

// 0xbca935b..0xbca937e: obj_a release. rcx = obj_a (+0x88); if nonzero, flag = (obj_a != &this+0x50),
// dead vtable reads, call sub_eea6040(obj_a, flag), obj_a = 0.
`0xbca935b  mov rcx,[rsi+0x88]`   ; R a0+0x88
`0xbca9362  test rcx,rcx`
`0xbca9365  je short 0xBCA9389`   ; -> loc_bca9389
`0xbca9367  lea rax,[rsi+0x50]`   ; R a0+0x50
`0xbca936b  cmp rcx,rax`
`0xbca936e  setne dl`
`0xbca9371  mov rax,[rcx]`        ; R *(a0+0x88)+0x0  (dead: call target is the IAT slot)
`0xbca9374  mov rax,[rax+0x20]`   ; R *(*(a0+0x88)+0x0)+0x20  (dead)
`0xbca9378  call qword ptr [0xF99FFA0]`   ; [data_f99ffa0] = sub_eea6040  (rcx = obj_a, rdx = flag)
`0xbca937e  mov qword ptr [rsi+0x88],0`   ; W a0+0x88

// 0xbca9389..0xbca93bd: shared release. rdi = shared (+0x28); if nonzero: lock dec strong; if ==0,
// dead vtable reads, call sub_eea6040(shared, flag), lock dec weak; if ==0,
// dead vtable reads, call sub_eea6040(shared, flag).
`0xbca9389  mov rdi,[rsi+0x28]`   ; R a0+0x28
`0xbca938d  test rdi,rdi`
`0xbca9390  je short 0xBCA93BD`   ; -> loc_bca93bd
`0xbca9392  lock dec dword ptr [rdi+8]`   ; W *(a0+0x28)+0x8
`0xbca9396  jne short 0xBCA93BD`  ; -> loc_bca93bd
`0xbca9398  mov rax,[rdi]`        ; R *(a0+0x28)+0x0  (dead)
`0xbca939b  mov rax,[rax]`        ; R *(*(a0+0x28)+0x0)+0x0  (dead)
`0xbca939e  mov rcx,rdi`
`0xbca93a1  call qword ptr [0xF99FFA0]`   ; [data_f99ffa0] = sub_eea6040  (rcx = shared, rdx = flag)
`0xbca93a7  lock dec dword ptr [rdi+0xC]` ; W *(a0+0x28)+0xC
`0xbca93ab  jne short 0xBCA93BD`  ; -> loc_bca93bd
`0xbca93ad  mov rax,[rdi]`        ; R *(a0+0x28)+0x0  (dead)
`0xbca93b0  mov rax,[rax+8]`      ; R *(*(a0+0x28)+0x0)+0x8  (dead)
`0xbca93b4  mov rcx,rdi`
`0xbca93b7  call qword ptr [0xF99FFA0]`   ; [data_f99ffa0] = sub_eea6040  (rcx = shared, rdx = flag)

// 0xbca93bd..0xbca93f2: buffer A release. rax = cap_a (+0x18); if cap_a < 0x10 skip to reset.
// rcx = buf_a (+0x00); if cap_a + 1 < 0x1000 call sub_e935700(buf_a), else compute heap block base,
// guard >= 0x20, call sub_e935700([buf_a-8]).
`0xbca93bd  mov rax,[rsi+0x18]`   ; R a0+0x18
`0xbca93c1  cmp rax,0x10`
`0xbca93c5  jb short 0xBCA93F7`   ; -> loc_bca93f7
`0xbca93c7  mov rcx,[rsi]`        ; R a0+0x0
`0xbca93ca  lea rdx,[rax+1]`      ; R *(a0+0x18)+0x1
`0xbca93ce  cmp rdx,0x1000`
`0xbca93d5  jb short 0xBCA93F2`   ; -> loc_bca93f2
`0xbca93d7  mov r8,[rcx-8]`       ; R *(a0+0x0)-0x8
`0xbca93db  add rcx,0xFFFFFFFFFFFFFFF8`
`0xbca93df  sub rcx,r8`
`0xbca93e2  cmp rcx,0x20`
`0xbca93e6  jae short 0xBCA9411`  ; -> loc_bca9411 (heap-guard fail)
`0xbca93e8  add rax,0x28`         ; dead size
`0xbca93ec  mov rdx,rax`
`0xbca93ef  mov rcx,r8`
`0xbca93f2  call 0xE935700`       ; -> sub_e935700

// 0xbca93f7..0xbca9410: reset buffer A fields: size_a=0, cap_a=0xF, buf_a=0; epilogue + ret.
`0xbca93f7  mov qword ptr [rsi+0x10],0`   ; W a0+0x10
`0xbca93ff  mov qword ptr [rsi+0x18],0xF` ; W a0+0x18
`0xbca9407  mov byte ptr [rsi],0`         ; W a0+0x0
`0xbca940a  add rsp,0x28`
`0xbca940e  pop rdi`
`0xbca940f  pop rsi`
`0xbca9410  ret`

// 0xbca9411..0xbca942b: heap-guard failure (noreturn). zero stack args, call import-slot [0xF9A8C78](0,0,0,0),
// int3 (trap).
`0xbca9411  mov qword ptr [rsp+0x20],0`
`0xbca941a  xor ecx,ecx`
`0xbca941c  xor edx,edx`
`0xbca941e  xor r8d,r8d`
`0xbca9421  xor r9d,r9d`
`0xbca9424  call qword ptr [0xF9A8C78]`   ; [data_f9a8c78]
`0xbca942a  int3`

## Reversed source (complete)

See `src/client/features/render/native/bgfx/sub_bca92f0.cpp` (first line: `// LIFT 0xbca92f0 size 0x13b 1.26.62.01 sub_bca92f0`) and its header `sub_bca92f0.h`. Every instruction of [0xbca92f0, 0xbca942b) is covered by a `// 0xA..0xB` range comment beside the corresponding C++ statement; every `call` is quoted verbatim as `0xRVA  call ...` (two spaces). The source contains no placeholder tags.

## Struct fields touched

| Offset | Size | Direction | Meaning | Tag |
|--------|------|-----------|---------|-----|
| Builder+0x00 | 8 | W | buf_a pointer cleared to 0 | [V] `0xbca9407  mov byte ptr [rsi],0` |
| Builder+0x10 | 8 | W | size_a written 0 | [V] `0xbca93f7  mov qword ptr [rsi+0x10],0` |
| Builder+0x18 | 8 | R/W | cap_a read, written 0xF | [V] `0xbca93bd  mov rax,[rsi+0x18]` / `0xbca93ff  mov qword ptr [rsi+0x18],0xF` |
| Builder+0x28 | 8 | R/W | shared RefCounted* read; strong@+0x8 lock-dec, weak@+0xC lock-dec | [V] `0xbca9389  mov rdi,[rsi+0x28]` / `0xbca9392  lock dec dword ptr [rdi+8]` / `0xbca93a7  lock dec dword ptr [rdi+0xC]` |
| Builder+0x50 | 8 | R | address of inline object compared with obj_a | [V] `0xbca9367  lea rax,[rsi+0x50]` / `0xbca936b  cmp rcx,rax` |
| Builder+0x88 | 8 | R/W | obj_a RefCounted* read, compared, released via sub_eea6040, cleared to 0 | [V] `0xbca935b  mov rcx,[rsi+0x88]` / `0xbca937e  mov qword ptr [rsi+0x88],0` |
| Builder+0x98 | 8 | R/W | buf_b pointer read, cleared to 0 | [V] `0xbca9306  mov rcx,[rsi+0x98]` / `0xbca9354  mov byte ptr [rsi+0x98],0` |
| Builder+0xA8 | 8 | W | size_b written 0 | [V] `0xbca933e  mov qword ptr [rsi+0xA8],0` |
| Builder+0xB0 | 8 | R/W | cap_b read, written 0xF | [V] `0xbca92f9  mov rax,[rcx+0xB0]` / `0xbca9349  mov qword ptr [rsi+0xB0],0xF` |

Dead reads (results unused, call target is the IAT slot, not the vtable): Builder+0x88's vtable at +0x00 (`0xbca9371`, `0xbca9398`, `0xbca93ad`) and vtable slots at +0x0 / +0x8 / +0x20 (`0xbca9374`, `0xbca939b`, `0xbca93b0`).

## Callees

| Address | Class | Role | Tag |
|---------|-------|------|-----|
| 0xe935700 | lift (auto-unresolved->lift, `jmp 0x392960` forwarder) | sized deallocator entry; called with rcx = pointer to free | [V] `0xbca9339  call 0xE935700`, `0xbca93f2  call 0xE935700` |
| [0xF99FFA0] | vendor (data slot 0xF99FFA0 = sub_eea6040) | refcounted object releaser; called via `call qword ptr [0xF99FFA0]` | [V] `0xbca9378`, `0xbca93a1`, `0xbca93b7` `call qword ptr [0xF99FFA0]` |
| [0xF9A8C78] | crt (import slot) | heap-guard fail handler; called with (0,0,0,0), followed by int3 | [V] `0xbca9424  call qword ptr [0xF9A8C78]` |

All callees are either lift-set functions (called directly by native symbol) or boundary/data-slot imports (called via `native::Boundary`). No unresolved calls.

## OPEN questions

None. Every instruction, branch, call target, and field offset is accounted for in the disassembly.
