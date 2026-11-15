# Dossier: bgfx destroy-handle enqueue (cmd 0x1C) (0xbc6f2a0)

## Mechanical facts
- [V] Size 0xbb bytes, 1 block, proven extent, 3 xrefs in (rdis).
- [V] Signature (inferred): `void enqueueDestroyA(Context* ctx /*rcx*/, u16 handle /*dx*/)`.
- [V] Callees: `0xebdbf10` (lock, arg `ctx+0x1C0`), `0xebce390` x2 (append bytes), `0xebdbf20` (unlock).

## Behavior [V]
1. Locks `ctx+0x1C0`.
2. `Frame* f = ctx->fillFrame /* [ctx+0x1CFD0C8] */`.
3. Pushes handle into Frame tail list: `f->listA[idx++] = handle` where `idx = f->countA` at `f+0xE47828` (u16), data array at `f+0xE45828` (u16[idx]).
4. Appends post-command to `f->cmdPost` (`cursor u32 at f+0xE05820`, data at `f+0xE05828`): byte `0x1C`, aligns cursor to even +2, appends `u16 handle`, cursor += 2.
5. Unlocks.

## A4-A8 relevance
- [V] Concrete API-thread resource-destroy queueing primitive: handle recorded in a per-frame handle list and a post-cmd opcode+payload emitted for render-thread consumption. Paired with `0xbc6f800` (opcode 0x1D, list/count at +0xE498AC/+0xE478AC).

## Verification
- Static: `rdis sum/dis 0xbc6f2a0`.
