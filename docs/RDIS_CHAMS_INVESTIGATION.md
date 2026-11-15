# Actor selection for chams: what rdis found by itself (1.26.62.01)

Method: used only rdis (`decide`, `gates`, `path`, `needs`, `flow`, `callers`, `sum`, `fn`) and compared with the hand-derived memory/notes afterwards. Labels: **[tool]** = read from rdis output or the disassembly it points at; **[matches notes]** = independently equal to an earlier hand finding; **[new]** = not in earlier notes.

## 1. The lever: `DataDrivenRendererV2::tryAddActor` = rva 0x6ebb280
- Found by the Sigs.json signature; `sigcheck` says it has exactly 1 match (ok).
- `callers`: one caller, `0x53e1160`. `decide`: that caller branches on the returned byte at `0x53e1b73` (a decision point). [tool, matches notes]
- Argument roles from the code [tool]: a0 = renderer `this` (reads `[a0+8]` = lookup map, pushes into vectors at `[a0+0x38]` and `[a0+0x50]`), a1 = Actor* (three virtual calls through `[actor]+0x1E0/+0xF8/+0x178`), a2 = pointer to the actor-renderer shared_ptr (its first 8 bytes are FNV-1a hashed for the map lookup at `[a0+8]`), a3 byte = shadow context. This equals the existing hook signature `(self, Actor*, renderer, uint8_t shadow)` in `ActorFilterHook.cpp`. [matches notes]
- It returns false when: `[a0+8]==0`, a2 null/empty, the renderer key is not in the map, actor virtual slot 60 (`+0x1E0`) returns true, or slot 31 (`+0xF8`) is true and `sub_3d56910(actor+8, 0x77)` is false. [new: the actor-side virtual predicates (slots 60, 31, 47) are an alternative place to make an actor "not batchable" without hooking tryAddActor itself; not tested at runtime]
- The caller `0x53e1160` computes a2 as the result of `sub_5951530(this, &out, virtual-call(actor, +0x290|+0x228|...))`, gated by `*(*(a0+0x10)+0x38) != 0` and `out != 0`. [tool]

`decide` cannot say what each outcome does here: the call is in a loop and both outcomes rejoin shared code, so no call is exclusively gated by the branch. By hand the not-taken side appends to a 16-byte-element vector (the fallback list). This is a stated limit of `decide`, not a finding about the game.

## 2. Body draws: the push chain from the notes, re-derived
- `callers 0x66d0a00` = `0x6646980` only. [matches notes]
- `path 0x66d0a00 -> 0x66c98e0` (P): `0x66d0a00 -> 0x66b2de0 (site 0x66d36d9) -> 0x66c98e0 (site 0x66b4644)`, every edge proven, with the gate lists printed. [tool; the intermediate hop 0x66b2de0 is not in the notes]
- `gates 0x66c98e0 0x66cac61` (the item push): exactly one gate, `*(ret@66ca5c9+0x8) != *(ret@66ca5c9+0x10)`, i.e. the list object returned by the call at `0x66ca5c9` (the notes' `0x5ABA5C0` map lookup, return address `0x66CA5CE`) has `end != cap`: the vector has room, so push happens in place. This independently reproduces the notes' "LO = return value of the lookup, [LO+8]=end, [LO+0x10]=cap" fact. [matches notes]

## 3. Where a view id / identity channel could be (not conclusive)
- The body task `0x568d750` passes `*u16(*(a0+0x90)+0x8)` (a 16-bit value at record+8, same shape as the notes' "p1+8 = view id (word)") as the third argument to `0xbcc38e0`. `flow 0xbcc38e0 a2` shows it is never compared or indexed on the way: it is stored into a stack frame and passed to indirect calls (bgfx encoder/submit API through function pointers) and to `0xbcc3b90/0xbcc3fa0/0xbcc4150`. [tool]
- Reading of `flow`: a field that is only carried (stored, passed unchanged) between the insert and the consumer is exactly the "carrier" shape the +1000 trick needs. rdis cannot see past the indirect calls, so whether the consumer indexes with it (which would make +1000 break) is **unknown statically**; the notes' pitfall "offset must stay within the fixed view-id cap" is consistent with an index into a fixed table. The decisive test needs the runtime: one observation of the value at the indirect call target (Cheat Engine), not more static work.

## 4. Recommendation
Keep the verified design from memory (`bluey-chams-body-link`: hash of the 0xC8-byte item at push, looked up at the body task), because every link of it is now independently reproducible with `path`/`gates`. The view-id method remains a hypothesis; to test it: (1) `contradict` on the consumer functions once the carrying field is pinned to a struct offset (not run yet; `flow` above only covered `0xbcc38e0` and its direct callees), (2) read the value live at the indirect call in `0xbcc3fa0`, (3) check what table it indexes there.

## 5. What this exercise says about the tools
- Worked: `sigcheck`, `decide`, `callers`, `path`+`gates` (reproduced three hand facts exactly), `flow` (found the carrier shape).
- Gaps: `decide` inside loops; no memory/heap model so the vtable of `*(a0+0x88)` stays unknown; indirect calls end every flow; actor virtual slot meanings (60/31/47) are not named (no RTTI), they need the vtable of the real Actor class (`vslot 60` lists implementers across vtables).
