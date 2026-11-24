// LIFT 0xbc62040 size 0xb72 1.26.62.01 sub_bc62040
#include "client/features/render/native/bgfx/sub_bc62040.h"

#include "client/features/render/native/Lift.h"

#include <cstdint>
#include <cstring>
#include <intrin.h>

namespace native {

namespace {

// 0xE9E7970: stack probe (__chkstk-style); eax = requested size (0x2028), returns the
// allocated/rounded size in rax; then `sub rsp,rax`. crt row in native_boundary.tsv [V].
// Called at 0xbc62051. Boundary so the call is recorded/replayed in differential runs.
native::Boundary<std::uintptr_t, std::uintptr_t> sub_e9e7970("sub_e9e7970");

// 0xE951550: stack-cookie failure (__report_gsfailure style), noreturn; rcx = cookie ^ rsp.
// crt row in native_boundary.tsv [V]. Called at 0xbc62bac when the cookie check fails.
native::Boundary<void, std::uintptr_t> sub_e951550("sub_e951550");

// One radix counting-sort pass over n (u64 key, u16 word) pairs.
// Mirrors the listing's per-pass structure: memset counters, pairwise count loop that
// also tracks the sorted flag cl = AND(each element <= the next over all adjacent pairs), then
// (unless already sorted) a group-of-4 exclusive prefix scan and a pairwise distribute
// plus an odd tail. Returns true when the input was already sorted (data left in place,
// caller skips the distribute) and false when a distribute was performed.
template <typename Digit>
bool radix_pass(std::uint64_t* src, std::uint64_t* dst,
                std::uint16_t* srcWords, std::uint16_t* dstWords,
                std::uint32_t count, Digit digit, std::uint32_t* counters)
{
    // 0xEBCE430  call  (memset counters[2048], 0, 0x2000)  -> std::memset
    std::memset(counters, 0, kCounterBytes);

    bool sorted = true;
    if (count != 0) {
        std::uint64_t prev = src[0];
        std::uint32_t idx = 0;
        const std::uint32_t limit = count & ~1u;
        // pairwise count loop (listing: two elements per iteration, bin both, track cl)
        for (; idx < limit; idx += 2u) {
            const std::uint64_t a = src[idx];
            const std::uint32_t ba = digit(a);
            ++counters[ba];
            sorted = sorted && (prev <= a);
            const std::uint64_t b = src[idx + 1u];
            const std::uint32_t bb = digit(b);
            ++counters[bb];
            sorted = sorted && (a <= b);
            prev = b;
        }
        if (count & 1u) {
            const std::uint32_t ba = digit(src[idx]);
            ++counters[ba];
            sorted = sorted && (prev <= src[idx]);
        }
    }
    if (sorted) {
        return true;   // already sorted: data stays where it is, skip distribute
    }

    // group-of-4 exclusive prefix scan over counters[0..2047]
    std::uint32_t carry = 0;
    for (std::uint32_t g = 0; g < kCounterBins; g += 4u) {
        const std::uint32_t c0 = counters[g];     counters[g]     = carry; carry += c0;
        const std::uint32_t c1 = counters[g + 1]; counters[g + 1] = carry; carry += c1;
        const std::uint32_t c2 = counters[g + 2]; counters[g + 2] = carry; carry += c2;
        const std::uint32_t c3 = counters[g + 3]; counters[g + 3] = carry; carry += c3;
    }

    // pairwise distribute plus odd tail
    std::uint32_t idx = 0;
    const std::uint32_t limit = count & ~1u;
    for (; idx < limit; idx += 2u) {
        const std::uint64_t a = src[idx];
        const std::uint32_t ba = digit(a);
        const std::uint32_t pos = counters[ba]++;
        dst[pos] = a;
        dstWords[pos] = srcWords[idx];
        const std::uint64_t b = src[idx + 1u];
        const std::uint32_t bb = digit(b);
        const std::uint32_t pos2 = counters[bb]++;
        dst[pos2] = b;
        dstWords[pos2] = srcWords[idx + 1u];
    }
    if (count & 1u) {
        const std::uint64_t a = src[idx];
        const std::uint32_t ba = digit(a);
        const std::uint32_t pos = counters[ba]++;
        dst[pos] = a;
        dstWords[pos] = srcWords[idx];
    }
    return false;
}

std::uint32_t sub_bc62040_footprint(std::uint64_t* keys, std::uint64_t* workKeys,
                                    std::uint16_t* words, std::uint16_t* workWords,
                                    std::uint32_t count)
{
    // Writes: keys, workKeys, words, workWords each `count` elements wide [V].
    return {
        {keys, static_cast<std::size_t>(count) * 8u},
        {workKeys, static_cast<std::size_t>(count) * 8u},
        {words, static_cast<std::size_t>(count) * 2u},
        {workWords, static_cast<std::size_t>(count) * 2u},
    };
}

} // namespace

extern "C" void sub_bc62040(std::uint64_t* keys, std::uint64_t* workKeys,
                            std::uint16_t* words, std::uint16_t* workWords,
                            std::uint32_t count)
{
    // 0xbc62040..0xbc62bb2  full function coverage
    std::uintptr_t cookieSlot;
    const std::uintptr_t cookieStored =
        *reinterpret_cast<std::uintptr_t*>(kGblCookie) ^ reinterpret_cast<std::uintptr_t>(&cookieSlot);
    std::uint32_t counters[2048];

    //   0xbc62051  call 0xE9E7970   ; stack probe, eax = 0x2028, then sub rsp,rax
    (void)sub_e9e7970(kStackSize);

    // cookie stored at [rsp+0x2020] = [0x1230A0C0] ^ rsp (modeled by cookieSlot above)

    //   0xbc62090  test ebp,ebp / je 0xBC62A8F  : count == 0 goes straight to epilogue
    if (count == 0) goto L_epilogue;

    // ---- Pass A: key & 0x7FF, keys -> workKeys (sorted -> epilogue, data in keys) ----
    //   0xbc6208b  call 0xEBCE430   ; memset counters
    if (radix_pass(keys, workKeys, words, workWords, count,
                   [](std::uint64_t k) { return k & kMaskA; }, counters)) {
        goto L_epilogue;
    }

    // ---- Pass B: (key>>9)&0x1FFC, workKeys -> keys (sorted -> fixup: data in workKeys) ----
    //   0xbc6223e  call 0xEBCE430   ; memset counters
    if (radix_pass(workKeys, keys, workWords, words, count,
                   [](std::uint64_t k) { return (k >> 9) & kMaskB; }, counters)) {
        goto L_fixup;
    }

    // ---- Pass C: (key>>22)&0x7FF, keys -> workKeys (sorted -> epilogue, data in keys) ----
    //   0xbc623e9  call 0xEBCE430   ; memset counters
    if (radix_pass(keys, workKeys, words, workWords, count,
                   [](std::uint64_t k) { return (k >> 22) & kMaskC; }, counters)) {
        goto L_epilogue;
    }

    // ---- Pass D: (key>>33)&0x7FF, workKeys -> keys (sorted -> fixup: data in workKeys) ----
    //   0xbc6259b  call 0xEBCE430   ; memset counters
    if (radix_pass(workKeys, keys, workWords, words, count,
                   [](std::uint64_t k) { return (k >> 33) & kMaskD; }, counters)) {
        goto L_fixup;
    }

    // ---- Pass E: (key>>44)&0x7FF, keys -> workKeys (sorted -> epilogue, data in keys) ----
    //   0xbc6274b  call 0xEBCE430   ; memset counters
    if (radix_pass(keys, workKeys, words, workWords, count,
                   [](std::uint64_t k) { return (k >> 44) & kMaskE; }, counters)) {
        goto L_epilogue;
    }

    // ---- Pass F: key>>55, workKeys -> keys ----
    //   0xbc628fb  call 0xEBCE430   ; memset counters
    if (!radix_pass(workKeys, keys, workWords, words, count,
                    [](std::uint64_t k) { return k >> kShiftF; }, counters)) {
        goto L_epilogue;   // not sorted: distributed to keys, done
    }
    goto L_fixup;          // sorted: data in workKeys, fixup copy back to keys

L_fixup:
    //   0xbc62997  call 0xEBCE390   ; memcpy(keys, workKeys, count*8)
    std::memcpy(keys, workKeys, static_cast<std::size_t>(count) * 8u);
    //   0xbc62997  call 0xEBCE390   ; memcpy(words, workWords, count*2)
    std::memcpy(words, workWords, static_cast<std::size_t>(count) * 2u);
    goto L_epilogue;

L_epilogue:
    // stack cookie check: [0x1230A0C0] == (cookieStored ^ &cookieSlot)
    //   0xbc62bac  call 0xE951550   ; noreturn on mismatch; 0xbc62bb1.. int3 (unreachable)
    if (*reinterpret_cast<std::uintptr_t*>(kGblCookie) !=
        (cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot))) {
        sub_e951550(cookieStored ^ reinterpret_cast<std::uintptr_t>(&cookieSlot));
        __assume(false);   // `0xbc62bb1  int3` (noreturn, unreachable)
    }
    // add rsp,0x2028; pop rbx,rbp,rdi,rsi,r12,r13,r14,r15; ret
}

LIFT_FN(bc62040, "sub_bc62040", 0xBC62040, sub_bc62040, sub_bc62040_footprint);

} // namespace native
