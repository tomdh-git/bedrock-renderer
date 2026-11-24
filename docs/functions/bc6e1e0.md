# sub_0xbc6e1e0 — Scene/HUD view-setup task

## Source location
- `src/client/features/render/native/bgfx/sub_bc6e1e0.cpp` (first line `// LIFT 0xbc6e1e0 size 0x177 1.26.62.01 sub_bc6e1e0`)
- `src/client/features/render/native/bgfx/sub_bc6e1e0.h`

## Identity [V]
- RVA/size: `0xbc6e1e0`, size `0x177` → `[0xbc6e1e0, 0xbc6e357)`; last instruction `ret` at `0xbc6e348`, then `/GS` fail path at `0xbc6e349..0xbc6e356`; `0xbc6e360` starts the next function (not part of this unit).
- Depth 4, milestone 1, region bgfx, status D0. Row in docs/data/native_functions.tsv line 1069; root caller `0xbcc3190` (Scene/HUD view-setup task chain).
- Disassembly source: `tools/rdis/target/release/rdis.exe <exe> dis 0xbc6e1e0 800`; range verified instruction-complete in the reversed source below (every instruction start in `[0xbc6e1e0, 0xbc6e357)` lies inside a cited `// 0xA..0xB` range).

## Signature (exact x64 Microsoft ABI)
`uint32_t sub_bc6e1e0(ViewContext* ctx, uint32_t arg2, uint16_t arg3, void* arg4, uint16_t arg5);`
- rcx = ctx (ViewContext*): `[rcx+0x00]` pointer to render object; `[rcx+0x6AC]` entry-index byte.
- edx = arg2 (uint32_t): header bit field (bits 27..31) and sign-extended table index.
- r8 = arg3 (uint16_t in low bits): header bits 11..26 and multiplier low operand.
- r9 = arg4 (void*): source pointer for the second copy.
- 5th home slot ([rsp+0x28] at entry, read as `[rsp+0xB0]` after prologue) = arg5 (uint16_t): header bit 1 and multiplier high operand.
- Return eax = entry size after the appends (updated `ViewEntry::size`).

## Register/argument map and phases
`// 0xbc6e1e0..0xbc6e208`: prologue (pushes r15,r14,r13,r12,rsi,rdi,rbp,rbx; `sub rsp,0x48`); saves `rsi=r9`, `edi=edx`, `r14d = *(uint16_t*)[rsp+0xB0]`; /GS cookie: `cookie = *[0x141230A0C0]`, `guardSlot = cookie ^ rsp`, stored at `[rsp+0x40]`.
`// 0xbc6e20d..0xbc6e225`: `obj = *ctx`; `arrayBase = *(uintptr_t*)(obj + 0xDC57E0)`; `index = ctx->entryIndex`; `entryPtr = arrayBase[index]`; `capacity = entryPtr->size@0`... i.e. `capacity = *(uint32_t*)entryPtr`, `size = *(uint32_t*)(entryPtr+4)` — the dynamic entry block `{capacity@0, size@4, payload@8}`.
`// 0xbc6e228..0xbc6e232`: headroom check `(uint32)(capacity - size) > 0x10000` → `ja 0xBC6E2AA` skips the grow.
`// 0xbc6e234..0xbc6e28a`: grow path: `newCapacity = align16(capacity + 0x10000F)` (min 0x10000); `allocator = *[0x1412ADF800]`; if non-zero: `newPtr = (*(void**)[0x14F99FFA0])(allocator, entryPtr, newCapacity | 8, 0, 0, 0)` — indirect call through data slot `[0xF99FFA0]` (rdis annotation `[data_f99ffa0] = sub_eea6040`); `arrayBase[index] = newPtr`. If allocator is null: `*(uint32_t*)0 = capacity` (the original's null-deref crash path) and `arrayBase[index] = 0`. Then reload `entryPtr`, `capacity`, `size` from memory after the possible move.
`// 0xbc6e2aa..0xbc6e2c4`: header dword `hdr = 1 | (arg5<<1) | (arg3<<11) | (arg2<<27)` stored at stack temp `[rsp+0x3C]`.
`// 0xbc6e2c8..0xbc6e2f1`: if `(uint32)(size + 4) < capacity`: `sub_ebce390(entry + 8 + size, &hdrSlot, 4, 0)` then `size += 4` (`*(uint32_t*)(entryPtr+4) = size`).
`// 0xbc6e2f4..0xbc6e320`: `count = (uint32)arg5 * (int32)table[(int32)arg2]` (table at `[0x14F441930]`); if `(uint32)(size + count) < capacity`: `sub_ebce390(entry + 8 + size, arg4, count, 0)` then `size += count`.
`// 0xbc6e324..0xbc6e348`: /GS verify: if `*[0x141230A0C0] ^ rsp != guardSlot` → `0xbc6e349..0xbc6e356`: `sub_e951550(cookie)` then `int3`; else epilogue + `ret` (eax == size).

## Struct fields touched [V]
| struct | field | offset | R/W | instruction |
|---|---|---|---|---|
| ViewContext | objectBase | +0x00 | R | 0xbc6e20d `mov rax,[rcx]` |
| ViewContext | entryIndex | +0x6AC | R | 0xbc6e217 `movzx r12d,byte ptr [rcx+0x6AC]` |
| render object | entry-array base ptr | +0xDC57E0 | R | 0xbc6e210 `mov r15,[rax+0xDC57E0]`, 0xbc6e293 |
| entry-pointer array | slot[index] | index*8 | R/W | 0xbc6e21f, 0xbc6e28c, 0xbc6e2a1 |
| ViewEntry | capacity | +0x00 | R/W | 0xbc6e223, 0xbc6e28a `mov [rax],ebp`, 0xbc6e2a5 |
| ViewEntry | size | +0x04 | R/W | 0xbc6e225, 0xbc6e2eb, 0xbc6e2ee+`mov [rbx+4],eax`, 0xbc6e320 `add [rbx+4],r14d` |
| ViewEntry | payload base | +0x08 | W | 0xbc6e2d1..0xbc6e2e4, 0xbc6e310..0xbc6e31b (via sub_ebce390) |
| stack | header temp | [rsp+0x3C] | W | 0xbc6e2c4 `mov [rsp+0x3C],ecx` |
| stack | /GS cookie guard | [rsp+0x40] | W/R | 0xbc6e208, 0xbc6e324 |
| global | /GS cookie | [0x141230A0C0] | R | 0xbc6e1fe, 0xbc6e32c |
| global | allocator ptr | [0x1412ADF800] | R | 0xbc6e23d |
| data slot | realloc fn ptr | [0x14F99FFA0] | R | 0xbc6e250..0xbc6e27a |
| table | sizeTable[(int32)arg2] | [0x14F441930] | R | 0xbc6e2fe |
| *(null) | — | 0x00000000 | W | 0xbc6e28a `mov [rax],ebp` (allocator==null crash path of the original; no guard added) |

## Callees [V]
- `0xbc6e27a  call qword ptr [0xF99FFA0]` — indirect through data slot; slot contents = `sub_eea6040` per rdis annotation `[data_f99ffa0] = sub_eea6040`; signature `(allocator, ptr, newSize, 0, 0, 0) -> newPtr`. **NOT in docs/data/native_functions.tsv and NOT in docs/data/native_boundary.tsv → UNRESOLVED CALL** (see unit result file).
- `0xbc6e2e4  call 0xEBCE390` and `0xbc6e31b  call 0xEBCE390` — `sub_ebce390(dst, src, count, flags)`, memcpy-like; return value unused. **NOT in either table → UNRESOLVED CALL** (see unit result file).
- `0xbc6e351  call 0xE951550` — `sub_e951550(cookie)`, boundary class crt [V: docs/data/native_boundary.tsv line 467].

## OPEN questions
- sub_ebce390 (0xEBCE390) and sub_eea6040 (via slot [0xF99FFA0]) are not classified in either table, so their exact types/origin are unknown; they are called exactly as the disassembly shows (same arguments, same order).

## Reversed source (complete)

// LIFT 0xbc6e1e0 size 0x177 1.26.62.01 sub_bc6e1e0
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bc6e1e0.h"

#include <cstdint>
#include <intrin.h>

namespace native::bgfx {

// Read-only globals ([V] from the disassembly; RVAs, image base 0x140000000,
// Minecraft Windows 1.26.62.01):
//   [0x1230A0C0]  /GS cookie                       -> 0x141230A0C0
//   [0x12ADF800]  allocator object pointer          -> 0x1412ADF800
//   [0xF99FFA0]   data slot holding sub_eea6040     -> 0x14F99FFA0
//   [0xF441930]   int32 multiplier table            -> 0x14F441930
constexpr uintptr_t kCookiePtr = 0x141230A0C0ULL;
constexpr uintptr_t kAllocatorPtr = 0x1412ADF800ULL;
constexpr uintptr_t kReallocSlot = 0x14F99FFA0ULL;
constexpr uintptr_t kSizeTable = 0x14F441930ULL;

// 0xEBCE390 sub_ebce390(dst, src, count, flags) — memcpy-like callee, called at
//   0xbc6e2e4  call 0xEBCE390
//   0xbc6e31b  call 0xEBCE390
extern "C" void* sub_ebce390(void* dst, const void* src, uint32_t count, uint32_t flags);

// 0xE951550 sub_e951550(cookie) — boundary crt: /GS cookie-failure path
extern "C" void sub_e951550(uintptr_t cookie);

// Layout assertions (full set in sub_bc6e1e0.h; repeated here so liftcheck sees them).
static_assert(offsetof(ViewContext, objectBase) == 0x00, "sub_0xbc6e1e0: ViewContext objectBase at +0x00");
static_assert(offsetof(ViewContext, entryIndex) == 0x6AC, "sub_0xbc6e1e0: ViewContext entryIndex at +0x6AC");
static_assert(offsetof(ViewEntry, capacity) == 0x00, "sub_0xbc6e1e0: ViewEntry capacity at +0x00");
static_assert(offsetof(ViewEntry, size) == 0x04, "sub_0xbc6e1e0: ViewEntry size at +0x04");
static_assert(offsetof(ViewEntry, payload) == 0x08, "sub_0xbc6e1e0: ViewEntry payload at +0x08");

uint32_t sub_bc6e1e0(ViewContext* ctx, uint32_t arg2, uint16_t arg3, void* arg4, uint16_t arg5) {
    // 0xbc6e1e0..0xbc6e208: prologue + /GS cookie guard setup
    //   0xbc6e1fe  mov rax,[0x1230A0C0]
    //   0xbc6e205  xor rax,rsp
    //   0xbc6e208  mov [rsp+0x40],rax
    uintptr_t cookie = *reinterpret_cast<uintptr_t*>(kCookiePtr);
    uintptr_t guardSlot = cookie ^ reinterpret_cast<uintptr_t>(&guardSlot);

    // 0xbc6e20d..0xbc6e225: resolve the dynamic entry arrayBase[ctx->entryIndex]
    //                      = { capacity@0, size@4 } [V]
    //   0xbc6e20d  mov rax,[rcx]
    //   0xbc6e210  mov r15,[rax+0xDC57E0]
    //   0xbc6e217  movzx r12d,byte ptr [rcx+0x6AC]
    //   0xbc6e21f  mov rbx,[r15+r12*8]
    //   0xbc6e223  mov ebp,[rbx]
    //   0xbc6e225  mov eax,[rbx+4]
    uintptr_t obj = ctx->objectBase;
    uintptr_t arrayBase = *reinterpret_cast<uintptr_t*>(obj + kRenderObject_entryArrayPtr);
    uint32_t index = ctx->entryIndex;
    uintptr_t entryPtr = reinterpret_cast<uintptr_t*>(arrayBase)[index];
    uint32_t capacity = *reinterpret_cast<uint32_t*>(entryPtr);
    uint32_t size = *reinterpret_cast<uint32_t*>(entryPtr + 4);

    // 0xbc6e228..0xbc6e232: if ((uint32)(capacity - size) > 0x10000) there is
    //                      enough headroom, skip the grow [V]
    //   0xbc6e228  mov edx,ebp
    //   0xbc6e22a  sub edx,eax
    //   0xbc6e22c  cmp edx,0x10000
    //   0xbc6e232  ja short 0xBC6E2AA
    if ((capacity - size) <= 0x10000u) {
        // 0xbc6e234..0xbc6e247: newCapacity = align16(capacity + 0x10000F) (min 0x10000);
        //                      load the allocator pointer [V]
        //   0xbc6e234  add ebp,0x10000F
        //   0xbc6e23a  and ebp,0xFFFFFFF0
        //   0xbc6e23d  mov rdx,[0x12ADF800]
        //   0xbc6e244  test rdx,rdx
        uint32_t newCapacity = (capacity + 0x10000Fu) & 0xFFFFFFF0u;
        uintptr_t allocator = *reinterpret_cast<uintptr_t*>(kAllocatorPtr);

        if (allocator != 0) {
            // 0xbc6e249..0xbc6e286: newPtr = (*[0xF99FFA0])(allocator, entryPtr,
            //                      newCapacity | 8, 0, 0, 0) [V]
            //   0xbc6e250  mov rax,[rdx]
            //   0xbc6e253  mov rax,[rax+8]
            //   0xbc6e27a  call qword ptr [0xF99FFA0]
            using ReallocFn = void* (*)(void*, void*, uint32_t, uint32_t, uint32_t, uint32_t);
            ReallocFn reallocFn =
                reinterpret_cast<ReallocFn>(*reinterpret_cast<uintptr_t*>(kReallocSlot));
            entryPtr = reinterpret_cast<uintptr_t>(
                reallocFn(reinterpret_cast<void*>(allocator), reinterpret_cast<void*>(entryPtr),
                          newCapacity | 8u, 0u, 0u, 0u));
            // 0xbc6e28c  mov [r15+r12*8],rax
            reinterpret_cast<uintptr_t*>(arrayBase)[index] = entryPtr;
        } else {
            // 0xbc6e288  xor eax,eax
            // 0xbc6e28a  mov [rax],ebp          (write through null - the original's crash path)
            // 0xbc6e28c  mov [r15+r12*8],rax    (rax == 0)
            *reinterpret_cast<uint32_t*>(0) = capacity;
            reinterpret_cast<uintptr_t*>(arrayBase)[index] = 0;
        }

        // 0xbc6e290..0xbc6e2a7: reload entry pointer, capacity, size after
        //                      the possible move [V]
        //   0xbc6e290  mov rax,[rcx]
        //   0xbc6e293  mov rax,[rax+0xDC57E0]
        //   0xbc6e29a  movzx ecx,byte ptr [rcx+0x6AC]
        //   0xbc6e2a1  mov rbx,[rax+rcx*8]
        //   0xbc6e2a5  mov ebp,[rbx]
        //   0xbc6e2a7  mov eax,[rbx+4]
        obj = ctx->objectBase;
        arrayBase = *reinterpret_cast<uintptr_t*>(obj + kRenderObject_entryArrayPtr);
        entryPtr = reinterpret_cast<uintptr_t*>(arrayBase)[index];
        capacity = *reinterpret_cast<uint32_t*>(entryPtr);
        size = *reinterpret_cast<uint32_t*>(entryPtr + 4);
    }

    // 0xbc6e2aa..0xbc6e2c4: packed header dword = 1 | (arg5<<1) | (arg3<<11) | (arg2<<27)
    //   0xbc6e2aa  mov ecx,edi
    //   0xbc6e2ac  shl ecx,0x1B
    //   0xbc6e2af  movzx edx,r8w
    //   0xbc6e2b3  shl edx,0xB
    //   0xbc6e2b6  or edx,ecx
    //   0xbc6e2b8  movzx r14d,r14w
    //   0xbc6e2bc  lea ecx,[r14+r14]
    //   0xbc6e2c0  or ecx,edx
    //   0xbc6e2c2  inc ecx
    //   0xbc6e2c4  mov [rsp+0x3C],ecx
    uint32_t hdr = (uint32_t{arg5} * 2u) | (uint32_t{arg3} << 11) | (uint32_t{arg2} << 27);
    ++hdr;
    uint32_t hdrSlot = hdr;   // [rsp+0x3C]

    // 0xbc6e2c8..0xbc6e2cd: if ((uint32)(size + 4) >= capacity) skip the write
    //   0xbc6e2c8  lea ecx,[rax+4]
    //   0xbc6e2cb  cmp ecx,ebp
    //   0xbc6e2cd  jae short 0xBC6E2F4
    if ((size + 4u) < capacity) {
        // 0xbc6e2cf..0xbc6e2e4: sub_ebce390(entry + 8 + size, &hdrSlot, 4, 0)
        //   0xbc6e2cf  mov eax,eax
        //   0xbc6e2d1  lea rcx,[rbx+rax]
        //   0xbc6e2d5  add rcx,8
        //   0xbc6e2d9  lea rdx,[rsp+0x3C]
        //   0xbc6e2de  mov r8d,4
        //   0xbc6e2e4  call 0xEBCE390
        sub_ebce390(reinterpret_cast<void*>(entryPtr + 8 + size), &hdrSlot, 4u, 0u);
        // 0xbc6e2e9..0xbc6e2f1: size += 4 [V]
        //   0xbc6e2e9  mov ebp,[rbx]
        //   0xbc6e2eb  mov eax,[rbx+4]
        //   0xbc6e2ee  add eax,4
        //   0xbc6e2f1  mov [rbx+4],eax
        capacity = *reinterpret_cast<uint32_t*>(entryPtr);
        size = *reinterpret_cast<uint32_t*>(entryPtr + 4);
        size += 4u;
        *reinterpret_cast<uint32_t*>(entryPtr + 4) = size;
    }

    // 0xbc6e2f4..0xbc6e2fe: count = (uint32)arg5 * sizeTable[(int32)arg2] [V]
    //   0xbc6e2f4  movsxd rcx,edi
    //   0xbc6e2f7  lea rdx,[0xF441930]
    //   0xbc6e2fe  imul r14d,[rdx+rcx*4]
    int32_t mult = reinterpret_cast<int32_t*>(kSizeTable)[(int32_t)arg2];
    uint32_t count = uint32_t{arg5} * uint32_t{mult};

    // 0xbc6e303..0xbc6e309: if ((uint32)(size + count) >= capacity) skip the write
    //   0xbc6e303  lea ecx,[r14+rax]
    //   0xbc6e307  cmp ecx,ebp
    //   0xbc6e309  jae short 0xBC6E324
    if ((size + count) < capacity) {
        // 0xbc6e30b..0xbc6e31b: sub_ebce390(entry + 8 + size, arg4, count, 0)
        //   0xbc6e30b  mov r8d,r14d
        //   0xbc6e30e  mov eax,eax
        //   0xbc6e310  lea rcx,[rbx+rax]
        //   0xbc6e314  add rcx,8
        //   0xbc6e318  mov rdx,rsi
        //   0xbc6e31b  call 0xEBCE390
        sub_ebce390(reinterpret_cast<void*>(entryPtr + 8 + size), arg4, count, 0u);
        // 0xbc6e320  add [rbx+4],r14d   -> size += count
        size += count;
        *reinterpret_cast<uint32_t*>(entryPtr + 4) = size;
    }

    // 0xbc6e324..0xbc6e336: /GS cookie verification [V]
    //   0xbc6e324  mov rax,[rsp+0x40]
    //   0xbc6e329  xor rax,rsp
    //   0xbc6e32c  mov rcx,[0x1230A0C0]
    //   0xbc6e333  cmp rcx,rax
    //   0xbc6e336  jne short 0xBC6E349
    if ((*reinterpret_cast<uintptr_t*>(kCookiePtr) ^ reinterpret_cast<uintptr_t>(&guardSlot)) != cookie) {
        // 0xbc6e349..0xbc6e356: cookie-failure path [V]
        //   0xbc6e349  mov rcx,[rsp+0x40]
        //   0xbc6e34e  xor rcx,rsp
        //   0xbc6e351  call 0xE951550
        //   0xbc6e356  int3
        sub_e951550(cookie);
        __assume(false);
    }
    // 0xbc6e338..0xbc6e348: epilogue + ret; eax == size [V]
    //   0xbc6e348  ret
    return size;
}

LIFT_FN(sub_bc6e1e0, "sub_bc6e1e0", 0xbc6e1e0, sub_bc6e1e0, nullptr);

} // namespace native::bgfx
