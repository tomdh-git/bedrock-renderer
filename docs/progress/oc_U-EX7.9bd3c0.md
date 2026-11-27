## NEXT
DONE - lift complete, LIFTCHECK OK, CLOSES? NO due to unresolved callees

## FILES
docs/functions/9bd3c0.md
src/client/features/render/native/helpers/sub_9bd3c0.h
src/client/features/render/native/helpers/sub_9bd3c0.cpp

## LIFTCHECK
LIFTCHECK OK 0x9bd3c0

## UNRESOLVED CALL
0x9bd230 — caller 0x9bd400 `call 0x9BD230` — callee not in native_functions.tsv (lift set) nor native_boundary.tsv; native_boundary_candidates.tsv line 171: class '?' (unclassified). Forward-declared as `extern "C" std::uintptr_t sub_9bd230(void*, std::uint32_t)` per call site ABI (RCX=&g_128d7fc0, RDX=a0->field0, returns RAX forwarded).
0x9bde00 — caller 0x9bd422 `call 0x9BDE00` — callee not in native_functions.tsv nor native_boundary.tsv; native_boundary_candidates.tsv line 172: class '?' (unclassified). Forward-declared as `extern "C" void sub_9bde00(void)` per call site (no register setup before call, return ignored).

CLOSES? NO — two unresolved callees (0x9bd230, 0x9bde00) neither in lift set nor native_boundary.tsv (boundary_candidates: '?')