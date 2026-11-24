## NEXT
DONE

## CALLEE RESOLUTION (done)
Function 0xe875790 size 0x8e4 ends at 0xe876074 (ret 0xe876011, int3 0xe876073).
Reference exe: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe
rdis callees 0xe875790 (direct calls):
  sub_9bc830 x3, sub_e935700 x1, sub_eec5850 x2, sub_eec6eb0 x4, sub_eec73f0 x1
  strings: 0xe876040 "unordered_map/set too long", 0xe87604d "invalid hash bucket count"
Indirect data-slot calls (not in `callees`): [0xF99FFA0]=sub_eea6040 vendor alloc; [0xF9A8C78]=_invoke_watson.

Classification (verified by disassembling each target + peimports):
- 0xeec6eb0 = jmp [0xF9A8A90] = VCRUNTIME140!memcmp -> CRT intrinsic, call memcmp directly.
- 0xeec73f0 = jmp [0xF9A8E08] = api-ms-win-crt-math!ceilf -> CRT intrinsic, call ceilf directly (NOT floorf).
- 0xeec5850 = jmp [0xF9A7320] = MSVCP140!std::_Xlength_error -> forward-declare sub_eec5850 (boundary lift), call.
- 0xe935700 = jmp 0x392960 = game deallocate (reads allocator global [0x1233E1A8]) -> forward-declare sub_e935700 (boundary lift), call.
- 0x9bc830 = real game operator new / _callnewh (push rsi; sub rsp,0x20; cmp [0x128D7FA8]) -> boundary alloc, call via wrapper.
- [0xF99FFA0] = sub_eea6040 vendor alloc (operator new) -> read slot ptr, call as fn ptr.
- [0xF9A8C78] = _invoke_watson -> read slot ptr, call as fn ptr.
Orchestrator callees_outside_set=0x9bc830 ONLY (boundary). => NO UNRESOLVED CALL.

liftcheck.py validates ONLY: dossier 'Reversed source' clean; source first-line marker+size; no stub/TODO/UNRESOLVED/incomplete; LIFT_FN present; static_assert present; full instruction coverage of [rva,rva+size) via cited `// 0xA..0xB` ranges or verbatim quotes; every call instruction quoted verbatim `0xRVA  call ...`; verify_oc mismatch=0. It does NOT validate call targets vs any set.

## FILES
- docs/functions/e875790.md (create: analysis + 'Reversed source (complete)')
- src/client/features/render/native/d3d12/sub_e875790.cpp (new lift, first line LIFT marker, full verbatim listing in #if 0)
- src/client/features/render/native/d3d12/sub_e875790.h (new header: layout consts + static_asserts + signature + lift-callee decls)

## SEMANTICS (final, hand-traced over full 583-insn listing)
MSVC std::unordered_map<std::string, mapped(0x18)>::_Try_emplace style. rcx=this(map*), rdx=out{pair<Node*,bool>}, r8=key std::string* (by-value), r9=r14=mapped value ptr(0x18).
Inline FNV-1a 64 hash of key over its chars (offset 0xCBF29CE484222325, prime 0x100000001B3, 4-way unroll) -> r13.
map layout: +0x08 _Myhead sentinel node*, +0x10 size_t _Mysize (elem count), +0x18 vec._Myfirst, +0x20 vec._Mylast, +0x28 vec._Myend, +0x30 _Mask (bucket count-1), +0x38 _MaxBprime(float).
Bucket = hash & mask; vec = this+0x18 (bucket ptr array); bucket[i] = {Node* _Next @+0, Node* _Prev @+8}. this+0x08 = sentinel; empty-bucket _Next==sentinel, _Prev==&sentinel.
Find loop (0xe8758ac..0xe875930): walk node=_Next; compare stored key node+0x10 (std::string) to key; match -> *out={node,0}, return. Hits also update list sentinel position.
Miss: if size == 0x38E38E38E38E38E (_Xlength) -> throw at 0xe876040. Node = vendor_alloc(0x48) via [0xF99FFA0] (null -> operator new 0x9BC830 retry). Move key std::string into node+0x10 (resets src to empty SSO: size=0,cap=0xF,buf[0]=0). Move 0x18 mapped value into node+0x30 (memcpy 16+8, zeroes src). size++ ; ratio = (size+?)/maxload: actually (float)(this._Mysize)/_MaxBprime compared; if ceil(size/maxload) > bucket_count -> rehash to new prime power-of-two count.
Rehash: compute needed = max(8, ceil((size)/maxload)), round up to power-of-two prime via bsr; allocate new bucket array (aligned 0x20, with 8-byte header), free old via sub_e935700 (boundary lift); rebuild buckets by re-hashing every node (inline FNV over each node's key), re-splice each node into its new bucket preserving the global doubly-linked order. Node itself (rbx) is already linked into global list at its position.
Insert: splice new node rbx into global list before current first, update bucket _Next/_Prev, *out={node,1}, return.
All 12 call sites: 4x 0xEEC6EB0 (memcmp, key compare), 1x 0xEEC73F0 (ceilf), 2x 0xEEC5850 (_Xlength_error), 1x 0xE935700 (dealloc), 3x 0x9BC830 (operator new fallback), 2x indirect [0xF99FFA0] (vendor alloc), 1x indirect [0xF9A8C78] (_invoke_watson, invalid-bucket-count fatal).
No boundary/SEH/null-guard beyond what exe does. fail-fast: alloc-null goes to 0x9BC830 loop; invalid bucket count -> _invoke_watson; length -> _Xlength_error.

## NEXT
DONE

## FILES
- docs/functions/e875790.md
- src/client/features/render/native/d3d12/sub_e875790.cpp
- src/client/features/render/native/d3d12/sub_e875790.h

## LIFTCHECK
LIFTCHECK OK 0xe875790

## UNRESOLVED CALL
none

CLOSES? YES