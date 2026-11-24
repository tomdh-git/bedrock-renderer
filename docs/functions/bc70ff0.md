# Dossier: sub_bc70ff0 (0xbc70ff0, size 0xf1, 1.26.62.01)

Source: `src/client/features/render/native/bgfx/sub_bc70ff0.cpp` + `sub_bc70ff0.h`.
Exe: `C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe` (image-base RVAs).
Disassembly basis: `rdis.exe <exe> dis 0xbc70ff0 0xf1` — one straight-line block, no branches, no jumps inside the range; `ret` at 0xbc710e0, then padding + the next function at 0xbc710f0.

## Signature (from prologue stores, [V])
`void sub_bc70ff0(RenderContext* ctx, std::uint16_t dx, std::uint32_t d32, std::uint64_t q64);`
x64 Microsoft ABI: rcx = ctx ('this'), rdx = dx (only low 16 bits used), r8 = d32 (low 32 bits), r9 = q64 (all 64 bits). Return void: rax is never written before `ret` (dead).

## Register / argument map
| Register | Argument | Meaning | Stored at |
|---|---|---|---|
| rcx | ctx | render context ('this') | rsi = rcx at 0xbc71004; ctx+0x1C0 at 0xbc7101a ([rbp-0x18]) |
| rdx | dx | u16 record field | [rbp-0xC] at 0xbc71007, read at 0xbc7106b |
| r8 | d32 | u32 record field | [rbp-0x10] at 0xbc7100f, read at 0xbc71090 |
| r9 | q64 | u64 record field | [rbp-0x20] at 0xbc7100b, read at 0xbc710b5 |

Stack frame: `sub rsp,0x40`, `rbp = rsp+0x40`. [rbp-8] gets stack cookie 0xFFFFFFFFFFFFFFFE at 0xbc70ffc (dead store, never read back). Locals: [rbp-0xC] dx, [rbp-0x20] r9, [rbp-0x10] r8d, [rbp-0x18] lockPtr, [rbp-9] tag byte 0x13.

## Phases (0xbc70ff0..0xbc710e1, instruction-complete)

### 0xbc70ff0..0xbc71023 — prologue + lock construct
Pushes rbp/rsi/rdi, `sub rsp,0x40`, `lea rbp,[rsp+0x40]`, stack cookie store (dead). Spills args: `mov [rbp-0xC],dx`, `mov [rbp-0x20],r9`, `mov [rbp-0x10],r8d`. `add rcx,0x1C0`; `mov [rbp-0x18],rcx` (lock address). `mov rsi,rcx` (save this).

`0xbc7101e  call 0xEBDBF10` — `sub_ebdbf10(lockPtr)`; constructs the lock subobject at ctx+0x1C0 (sets 4 vtable pointers at +0x00/+0x08/+0x10/+0x18, inits subobject at +0x20, returns this in rax — dead) [V 0xebdbf30..0xebdbf97].

C-like: `void* lockPtr = (uint8_t*)ctx + 0x1C0; sub_ebdbf10(lockPtr);`

### 0xbc71023..0xbc7104e — load state, tag byte, first append
`mov rdi,[rsi+0x1CFD0C8]` — st = ctx->cmdPost. `mov byte ptr [rbp-9],0x13` — tag. `mov eax,[rdi+0xDC5818]` — count = st->postCursor. `lea rcx,[rdi+rax]; add rcx,0xDC5820` — dest = st->postData + count. `lea rdx,[rbp-9]; mov r8d,1`.

`0xbc71049  call 0xEBCE390` — `sub_ebce390(st->postData + count, &tag, 1)` — copies 1 byte (memcpy-like tail to sub_eec6ec0).

C-like:
```
CmdPostState* st = ctx->cmdPost;
std::uint8_t tag = 0x13;
std::uint32_t count = st->postCursor;
sub_ebce390(st->postData + count, &tag, 1u);
```

### 0xbc7104e..0xbc7107a — align-2 cursor, append u16
`lea rsi,[rdi+0xDC5820]` (st->postData base, reused for the rest). `mov ecx,[rdi+0xDC5818]` — cursor reloaded. `and ecx,0xFFFFFFFE; add ecx,2` — count = (count & ~1) + 2. `mov [rdi+0xDC5818],ecx` — store. `add rcx,rsi` — dest = st->postData + count. `lea rdx,[rbp-0xC]; mov r8d,2`.

`0xbc71075  call 0xEBCE390` — `sub_ebce390(st->postData + count, &dx, 2)`.

C-like:
```
count = st->postCursor = (st->postCursor & ~1u) + 2u;
sub_ebce390(st->postData + count, &dx, 2u);
```

### 0xbc7107a..0xbc7109f — align-4-ish cursor, append u32
`mov ecx,[rdi+0xDC5818]` — cursor reloaded. `add ecx,5; and ecx,0xFFFFFFFC` — count = (count + 5) & ~3. `mov [rdi+0xDC5818],ecx` — store. `add rcx,rsi`. `lea rdx,[rbp-0x10]; mov r8d,4`.

`0xbc7109a  call 0xEBCE390` — `sub_ebce390(st->postData + count, &d32, 4)`.

C-like:
```
count = st->postCursor = (st->postCursor + 5u) & ~3u;
sub_ebce390(st->postData + count, &d32, 4u);
```

### 0xbc7109f..0xbc710c8 — align-8 cursor, append u64, advance cursor by 8
`mov eax,[rdi+0xDC5818]` — cursor reloaded. `add eax,0xB; and eax,0xFFFFFFF8` — count = (count + 0xB) & ~7. `mov [rdi+0xDC5818],eax` — store. `add rsi,rax` — dest = st->postData + count. `lea rdx,[rbp-0x20]; mov r8d,8; mov rcx,rsi`.

`0xbc710c2  call 0xEBCE390` — `sub_ebce390(st->postData + count, &q64, 8)`. `add dword ptr [rdi+0xDC5818],8` — cursor += 8.

C-like:
```
count = st->postCursor = (st->postCursor + 0xBu) & ~7u;
sub_ebce390(st->postData + count, &q64, 8u);
st->postCursor = count + 8u;
```

### 0xbc710c8..0xbc710e1 — lock destroy + epilogue
`mov rcx,[rbp-0x18]` — lockPtr. `0xbc710d3  call 0xEBDBF20` — `sub_ebdbf20(lockPtr)`; destroys the lock subobject. `add rsp,0x40; pop rdi; pop rsi; pop rbp; ret`.

C-like: `sub_ebdbf20(lockPtr);` (return void).

## Struct fields touched
| Struct | Offset | Size | Dir | Meaning | Tag |
|---|---|---|---|---|---|
| RenderContext | 0x1CFD0C8 | 8 | R | cmdPost pointer [V 0xbc71023] | [V] |
| CmdPostState | 0xDC5818 | 4 | R/W | postCursor append counter [V 0xbc7102e/0xbc71056/0xbc7107b/0xbc710a0 R; 0xbc71062/0xbc71087/0xbc710ac W; 0xbc710c8 RMW] | [V] |
| CmdPostState | 0xDC5820 | 8 | R | postData buffer base pointer [V 0xbc7104f] | [V] |
| buffer at postData+cursor | variable | 1/2/4/8 | W | appended tagged record bytes [V 0xbc71049/0xbc71075/0xbc7109a/0xbc710c2] | [V] |
| RenderContext | 0x1C0 | 0x29 | W (via callee) | lock subobject: sub_ebdbf10 writes vtables +0x00..+0x18 + init at +0x20; sub_ebdbf20 tears down [V 0xebdbf30..0xebdbf97] | [V] (via lift callee) |

## Callees
| RVA | Symbol | Class | Call sites in 0xbc70ff0 | Tag |
|---|---|---|---|---|
| 0xEBDBF10 | sub_ebdbf10(void* lock) | lift (native_functions.tsv depth-0 root; native_boundary.tsv `lift`) | 0xbc7101e | [V] |
| 0xEBCE390 | sub_ebce390(void* dst, const void* src, std::uint32_t size) | lift (same); entry `jmp 0xEEC6EC0` (memcpy-like byte copy) | 0xbc71049, 0xbc71075, 0xbc7109a, 0xbc710c2 | [V] |
| 0xEBDBF20 | sub_ebdbf20(void* lock) | lift (same) | 0xbc710d3 | [V] |

All callees are classified `lift`, not boundary: forward-declared in sub_bc70ff0.h with their exe names and called directly (same convention as sub_bc6f800/sub_bc6f2a0). No UNRESOLVED CALL.

## OPEN questions
- Real C++ class names of RenderContext / CmdPostState are unknown; the header uses layout overlays with the exact offsets observed in the disassembly (no object is instantiated).
- High-level meaning of the posted record (tag 0x13 + u16/u32/u64 fields) is unknown; the lift is byte-exact regardless.
- sub_ebdbf10/sub_ebdbf20 precise semantics inferred from their bodies (construct/destruct the lock subobject) [I]; confirmed by the identical usage pattern in sub_bc6f800/sub_bc6f2a0; their own lift units will define them.

## Reversed source (complete)

```cpp
// LIFT 0xbc70ff0 size 0xf1 1.26.62.01 sub_bc70ff0
#include "client/features/render/native/bgfx/sub_bc70ff0.h"
#include "client/features/render/native/Lift.h"

#include <cstddef>
#include <cstdint>

namespace native {

static_assert(offsetof(RenderContext, cmdPost) == 0x1CFD0C8,
              "sub_bc70ff0: RenderContext::cmdPost must be at +0x1CFD0C8");
static_assert(offsetof(CmdPostState, postCursor) == 0xDC5818,
              "sub_bc70ff0: CmdPostState::postCursor must be at +0xDC5818");
static_assert(offsetof(CmdPostState, postData) == 0xDC5820,
              "sub_bc70ff0: CmdPostState::postData must be at +0xDC5820");

void sub_bc70ff0(RenderContext* ctx, std::uint16_t dx, std::uint32_t d32, std::uint64_t q64)
{
    // 0xbc70ff0..0xbc71023: prologue; spill args; lock = ctx + 0x1C0; sub_ebdbf10(lock)
    //   0xbc70ff0  push rbp        0xbc70ff1  push rsi        0xbc70ff2  push rdi
    //   0xbc70ff3  sub rsp,0x40    0xbc70ff7  lea rbp,[rsp+0x40]
    //   0xbc70ffc  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE   ; dead stack cookie, not reproduced
    //   0xbc71004  mov rsi,rcx     0xbc71007  mov [rbp-0xC],dx    0xbc7100b  mov [rbp-0x20],r9
    //   0xbc7100f  mov [rbp-0x10],r8d  0xbc71013  add rcx,0x1C0   0xbc7101a  mov [rbp-0x18],rcx
    //   0xbc7101e  call 0xEBDBF10    ; sub_ebdbf10(lock)  [`0xbc7101e  call 0xEBDBF10`]
    void* lockPtr = reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(ctx) + 0x1C0);
    sub_ebdbf10(lockPtr);                                         // 0xbc7101e  call 0xEBDBF10   ; lock

    // 0xbc71023..0xbc7104e: st = ctx->cmdPost; tag = 0x13; append 1 byte at st->postData + st->postCursor
    //   0xbc71023  mov rdi,[rsi+0x1CFD0C8]   0xbc7102a  mov byte ptr [rbp-9],0x13
    //   0xbc7102e  mov eax,[rdi+0xDC5818]    0xbc71034  lea rcx,[rdi+rax]   0xbc71038  add rcx,0xDC5820
    //   0xbc7103f  lea rdx,[rbp-9]           0xbc71043  mov r8d,1           0xbc71049  call 0xEBCE390   [`0xbc71049  call 0xEBCE390`]
    CmdPostState* st = ctx->cmdPost;                               // 0xbc71023  mov rdi,[rsi+0x1CFD0C8]
    std::uint8_t tag = 0x13;                                       // 0xbc7102a  mov byte ptr [rbp-9],0x13
    std::uint32_t count = st->postCursor;                          // 0xbc7102e  mov eax,[rdi+0xDC5818]
    sub_ebce390(st->postData + count, &tag, 1u);                   // 0xbc71049  call 0xEBCE390   dst=postData+count, src=&tag, size=1   [`0xbc71049  call 0xEBCE390`]

    // 0xbc7104e..0xbc7107a: count = (count & ~1) + 2; store; append 2 bytes of dx
    //   0xbc7104e  nop                      0xbc7104f  lea rsi,[rdi+0xDC5820]
    //   0xbc71056  mov ecx,[rdi+0xDC5818]   0xbc7105c  and ecx,0xFFFFFFFE   0xbc7105f  add ecx,2
    //   0xbc71062  mov [rdi+0xDC5818],ecx   0xbc71068  add rcx,rsi          0xbc7106b  lea rdx,[rbp-0xC]
    //   0xbc7106f  mov r8d,2                0xbc71075  call 0xEBCE390       [`0xbc71075  call 0xEBCE390`]
    count = st->postCursor = (st->postCursor & ~1u) + 2u;          // 0xbc71056..0xbc71062
    sub_ebce390(st->postData + count, &dx, 2u);                    // 0xbc71075  call 0xEBCE390   dst=postData+count, src=&dx, size=2   [`0xbc71075  call 0xEBCE390`]

    // 0xbc7107a..0xbc7109f: count = (count + 5) & ~3; store; append 4 bytes of d32
    //   0xbc7107a  nop                      0xbc7107b  mov ecx,[rdi+0xDC5818]
    //   0xbc71081  add ecx,5                0xbc71084  and ecx,0xFFFFFFFC   0xbc71087  mov [rdi+0xDC5818],ecx
    //   0xbc7108d  add rcx,rsi              0xbc71090  lea rdx,[rbp-0x10]   0xbc71094  mov r8d,4
    //   0xbc7109a  call 0xEBCE390           [`0xbc7109a  call 0xEBCE390`]
    count = st->postCursor = (st->postCursor + 5u) & ~3u;          // 0xbc7107b..0xbc71087
    sub_ebce390(st->postData + count, &d32, 4u);                   // 0xbc7109a  call 0xEBCE390   dst=postData+count, src=&d32, size=4   [`0xbc7109a  call 0xEBCE390`]

    // 0xbc7109f..0xbc710c8: count = (count + 0xB) & ~7; store; append 8 bytes of q64; cursor += 8
    //   0xbc7109f  nop                      0xbc710a0  mov eax,[rdi+0xDC5818]
    //   0xbc710a6  add eax,0xB              0xbc710a9  and eax,0xFFFFFFF8   0xbc710ac  mov [rdi+0xDC5818],eax
    //   0xbc710b2  add rsi,rax              0xbc710b5  lea rdx,[rbp-0x20]   0xbc710b9  mov r8d,8
    //   0xbc710bf  mov rcx,rsi              0xbc710c2  call 0xEBCE390       [`0xbc710c2  call 0xEBCE390`]
    //   0xbc710c7  nop                      0xbc710c8  add dword ptr [rdi+0xDC5818],8
    count = st->postCursor = (st->postCursor + 0xBu) & ~7u;        // 0xbc710a0..0xbc710ac
    sub_ebce390(st->postData + count, &q64, 8u);                   // 0xbc710c2  call 0xEBCE390   dst=postData+count, src=&q64, size=8   [`0xbc710c2  call 0xEBCE390`]
    st->postCursor = count + 8u;                                   // 0xbc710c8  add dword ptr [rdi+0xDC5818],8

    // 0xbc710c8..0xbc710e1: sub_ebdbf20(lock); epilogue; ret (void)
    //   0xbc710cf  mov rcx,[rbp-0x18]   0xbc710d3  call 0xEBDBF20   ; sub_ebdbf20(lock)  [`0xbc710d3  call 0xEBDBF20`]
    //   0xbc710d8  nop                  0xbc710d9  add rsp,0x40     0xbc710dd  pop rdi
    //   0xbc710de  pop rsi              0xbc710df  pop rbp          0xbc710e0  ret
    sub_ebdbf20(lockPtr);                                          // 0xbc710d3  call 0xEBDBF20   ; unlock
}

static native::Footprint sub_bc70ff0Footprint(RenderContext* ctx, std::uint16_t, std::uint32_t, std::uint64_t)
{
    native::Footprint fp;
    if (ctx == nullptr) return fp;
    CmdPostState* st = ctx->cmdPost;
    if (st == nullptr) return fp;
    fp.push_back({reinterpret_cast<void*>(&st->postCursor), sizeof(st->postCursor)}); // written at 0xbc71062/0xbc71087/0xbc710ac/0xbc710c8
    std::uint32_t c0 = st->postCursor;
    std::uint32_t c1 = (c0 & ~1u) + 2u;
    std::uint32_t c2 = (c1 + 5u) & ~3u;
    std::uint32_t c3 = (c2 + 0xBu) & ~7u;
    std::uint32_t end = c3 + 8u;                                     // final cursor value after 0xbc710c8
    if (st->postData != nullptr && end > c0)
        fp.push_back({st->postData + c0, end - c0});                 // appended bytes at 0xbc71049/0xbc71075/0xbc7109a/0xbc710c2
    fp.push_back({reinterpret_cast<std::uint8_t*>(ctx) + 0x1C0, 0x29}); // lock subobject written by sub_ebdbf10/sub_ebdbf20 [V 0xebdbf30..0xebdbf97]
    return fp;
}

LIFT_FN(sub_bc70ff0, "native::sub_bc70ff0", 0xbc70ff0, sub_bc70ff0, sub_bc70ff0Footprint);

} // namespace native
```
