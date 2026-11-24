#pragma once
#include "client/features/render/rewrite/RewriteRegistry.h"
#include "client/features/render/rewrite/RewriteVerify.h"
#include "sdk/SigManager.h"

// The lift framework (docs/RENDER_NATIVE_SPEC.md sections 3, 6, 8; checklist item X0d).
//
// A lifted function is a plain C++ function with the original's exact x64 signature. LIFT_FN ties it to the game's function:
//
//     static Footprint myFootprint(Encoder* self, uint16_t view) { return {{self, 0x6B0}, {frameOf(self), 0x40}}; }
//     LIFT_FN(EncoderSubmit, "bgfx::EncoderImpl::submit", 0xBC60740, EncoderSubmit_lifted, &myFootprint);   // footprint = nullptr for a pure function
//
// The entry joins the rewrite registry (RewriteRegistry, modes Off / Shadow / Verify / On, BS_REWRITE="bgfx::EncoderImpl::submit=verify"):
//   Off     the original runs
//   On      only the lifted function runs (Native mode)
//   Shadow  differential run, divergence counted and logged
//   Verify  differential run, the first divergence ends the process (fail fast)
// Differential run (spec section 8, V2): snapshot the footprint, run the ORIGINAL while recording every boundary call, restore the footprint, run the LIFTED function with the boundary calls
// served from the recording (target, argument bytes and order are compared), compare the footprint and the return value byte for byte, then put the original's post-state back.
//
// LIMITS stated honestly: the footprint must cover every byte the function AND the lifted functions it calls write (an undeclared write is neither compared nor undone: it would happen twice).
// Code whose effects other threads or the GPU observe at the same instant is not covered by V2 (spec section 8; use the thread-model proof and the whole-frame verify).
//
// Calls out of lifted code go to other lifted functions directly (plain C++ calls) or through a native::Boundary (the game's own function, listed in docs/data/native_boundary.tsv). Nothing else.
namespace native {

struct Region {
    void* ptr;
    size_t size;
};
using Footprint = std::vector<Region>;

// The recording of one differential run, thread-local like RewriteBusy.
struct BoundaryTape {
    enum class Mode : uint8_t { Idle, Record, Replay };
    struct Call {
        const void* id;
        std::vector<uint8_t> args;
        uint64_t ret;
    };
    Mode mode = Mode::Idle;
    std::vector<Call> calls;
    size_t cursor = 0;
    static BoundaryTape*& current() {
        static thread_local BoundaryTape* tape = nullptr;
        return tape;
    }
};

// A call into the game's own code that stays original. Resolved through Sigs.json (fatal when missing). Arguments must be trivially copyable, the result at most 8 bytes.
template <typename R, typename... A>
struct Boundary {
    const char* symbol;
    mutable uintptr_t address = 0;
    explicit constexpr Boundary(const char* sym) : symbol(sym) {}

    R operator()(A... a) const {
        if (address == 0)
            address = SigManager::get(symbol);
        auto fn = reinterpret_cast<R (*)(A...)>(address);
        BoundaryTape* tape = BoundaryTape::current();
        if (tape == nullptr || tape->mode == BoundaryTape::Mode::Idle)
            return fn(a...);
        static_assert((std::is_trivially_copyable_v<A> && ...), "boundary arguments must be trivially copyable");
        static_assert(std::is_void_v<R> || sizeof(R) <= 8, "boundary result must fit 8 bytes");
        std::vector<uint8_t> bytes;
        auto pack = [&bytes](const auto& v) {
            const uint8_t* p = reinterpret_cast<const uint8_t*>(&v);
            bytes.insert(bytes.end(), p, p + sizeof(v));
        };
        (pack(a), ...);
        if (tape->mode == BoundaryTape::Mode::Record) {
            uint64_t ret = 0;
            if constexpr (std::is_void_v<R>) {
                fn(a...);
            } else {
                R r = fn(a...);
                std::memcpy(&ret, &r, sizeof(R));
            }
            tape->calls.push_back({this, std::move(bytes), ret});
            return value(ret);
        }
        if (tape->cursor >= tape->calls.size() || tape->calls[tape->cursor].id != this || tape->calls[tape->cursor].args != bytes)
            Logger::fatal("[native] boundary call {} differs from the original's sequence at call #{} (lifted code made a call the original did not, or with other arguments)", symbol, tape->cursor);
        return value(tape->calls[tape->cursor++].ret);
    }

private:
    static R value(uint64_t ret) {
        if constexpr (!std::is_void_v<R>) {
            R r;
            std::memcpy(&r, &ret, sizeof(R));
            return r;
        }
    }
};

template <auto Lifted, RewriteEntry* E, auto Foot>
struct Thunk;

template <typename R, typename... A, R (*Lifted)(A...), RewriteEntry* E, auto Foot>
struct Thunk<Lifted, E, Foot> {
    static R call(A... a) {
        E->calls.fetch_add(1, std::memory_order_relaxed);
        const RewriteMode mode = E->current();
        if (mode == RewriteMode::Off || RewriteBusy::depth > 0)
            return E->template original<&call>()(a...);
        if (mode == RewriteMode::On)
            return Lifted(a...);
        return differential(mode, a...);
    }

    static std::vector<std::vector<uint8_t>> snapshot(const Footprint& fp) {
        std::vector<std::vector<uint8_t>> s;
        s.reserve(fp.size());
        for (const Region& r : fp)
            s.emplace_back(static_cast<const uint8_t*>(r.ptr), static_cast<const uint8_t*>(r.ptr) + r.size);
        return s;
    }
    static void restore(const Footprint& fp, const std::vector<std::vector<uint8_t>>& s) {
        for (size_t i = 0; i < fp.size(); ++i)
            std::memcpy(fp[i].ptr, s[i].data(), fp[i].size);
    }

    static R differential(RewriteMode mode, A... a) {
        RewriteBusy::Scope busy;
        Footprint fp;
        if constexpr (!std::is_null_pointer_v<decltype(Foot)>)
            fp = Foot(a...);
        const auto pre = snapshot(fp);
        BoundaryTape tape;
        tape.mode = BoundaryTape::Mode::Record;
        BoundaryTape::current() = &tape;
        // original on the real memory
        auto runOriginal = [&]() -> R { return E->template original<&call>()(a...); };
        auto runLifted = [&]() -> R { return Lifted(a...); };
        if constexpr (std::is_void_v<R>) {
            runOriginal();
            BoundaryTape::current() = nullptr;
            const auto postOriginal = snapshot(fp);
            restore(fp, pre);
            tape.mode = BoundaryTape::Mode::Replay;
            tape.cursor = 0;
            BoundaryTape::current() = &tape;
            runLifted();
            BoundaryTape::current() = nullptr;
            finish(mode, fp, postOriginal, tape);
            E->evaluated.fetch_add(1, std::memory_order_relaxed);
        } else {
            const R original = runOriginal();
            BoundaryTape::current() = nullptr;
            const auto postOriginal = snapshot(fp);
            restore(fp, pre);
            tape.mode = BoundaryTape::Mode::Replay;
            tape.cursor = 0;
            BoundaryTape::current() = &tape;
            const R lifted = runLifted();
            BoundaryTape::current() = nullptr;
            finish(mode, fp, postOriginal, tape);
            if constexpr (std::is_trivially_copyable_v<R>)
                RewriteVerify::compareValue(*E, mode, "return value", original, lifted);
            E->evaluated.fetch_add(1, std::memory_order_relaxed);
            return original;
        }
    }

    // compare the lifted run's footprint with the original's, then put the original's state back
    static void finish(RewriteMode mode, const Footprint& fp, const std::vector<std::vector<uint8_t>>& postOriginal, const BoundaryTape& tape) {
        const size_t recorded = tape.calls.size();
        if (tape.cursor != recorded)
            RewriteVerify::compare(*E, mode, "boundary call count", &tape.cursor, &recorded, sizeof(size_t));
        const auto postLifted = snapshot(fp);
        for (size_t i = 0; i < fp.size(); ++i)
            RewriteVerify::compare(*E, mode, "footprint region", postOriginal[i].data(), postLifted[i].data(), fp[i].size);
        restore(fp, postOriginal);
    }
};

} // namespace native

// Registers a lifted function: ID = C++ identifier suffix, NAME = registry key and Sigs.json symbol, RVA = 1.26.62.01 address (checked at install), LIFTED = the lifted function,
// FOOTPRINT = &function returning native::Footprint with the same arguments, or nullptr for a pure function.
#define LIFT_FN(ID, NAME, RVA, LIFTED, FOOTPRINT)                                                                                                \
    static RewriteEntry gLiftEntry_##ID(NAME, NAME, RVA, reinterpret_cast<void*>(&::native::Thunk<&LIFTED, &gLiftEntry_##ID, FOOTPRINT>::call)); \
    static const RewriteReg gLiftReg_##ID(gLiftEntry_##ID)
