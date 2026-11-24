#include "client/features/render/native/Lift.h"

// Forces the lift framework templates to compile (checklist X0d): a pure function, a function with a footprint and a boundary call, and a void function. Nothing is registered or installed.
static uint32_t liftTestPure(uint32_t a, uint32_t b) {
    return a + b;
}
static native::Footprint liftTestFootprint(uint32_t* out, uint32_t v) {
    return {{out, sizeof(uint32_t)}};
}
static const native::Boundary<void*, size_t> liftTestAlloc("native::selftest");
static void liftTestWriter(uint32_t* out, uint32_t v) {
    *out = v;
    (void)liftTestAlloc;
}

static RewriteEntry gLiftTestPureEntry("Native::selftest.pure", "Native::selftest.pure", 0, reinterpret_cast<void*>(&native::Thunk<&liftTestPure, &gLiftTestPureEntry, nullptr>::call));
static RewriteEntry gLiftTestWriterEntry("Native::selftest.writer", "Native::selftest.writer", 0, reinterpret_cast<void*>(&native::Thunk<&liftTestWriter, &gLiftTestWriterEntry, &liftTestFootprint>::call));
