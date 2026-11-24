## NEXT
DONE

## UNIT
U-EX1.bc45130 | 0xbc45130 size 0x161 depth 4 milestone 1 region bgfx status D0 | name "VV frame-graph builder" | callees outside set: 0x75720 (stl boundary), 0x9bc830 (alloc boundary) | callees in lift set: none | extent [0xbc45130, 0xbc45291)

## FINDINGS (all [V] from rdis dis/fn/sum of the exe, bytes verified against the file)
- Function copies a small-string object (same struct for src=rdx and dst=rcx): +0x00 16-byte header, +0x10 u64, +0x18 data pointer / inline base, +0x28 u64 size, +0x30 u64 capacity, +0x38 u32, +0x3C u16, +0x40 u8 valid flag. dst->mValid=0 at entry; if src->mValid!=1 return dst (dst keeps mValid=0). Copies header(16B)+mField10; zeroes dst+0x18..+0x37.
- if ((int64_t)size < 0) → call 0x75720(dst), noreturn (nop+int3 after).
- if (size > 0xF unsigned) → heap path: capacity = max(0x16, size|0xF); alloc size = (size|0xF < 0xFFF) ? capacity+1 : capacity+0x28; call qword ptr [0xF99FFA0] (rcx = *(uintptr_t*)0x1233E1A8 allocator handle, rdx = allocSize) = imported CRT allocator sub_eea6040 ("malloc"); on NULL → call 0x9BC830(dst), noreturn. On success: aligned=(p+0x27)&~0x1F; *(void**)(aligned-8)=p; dst->mData=aligned; dst->mSize=size; dst->mCapacity=capacity; size++; memcpy(dst->mData, srcData, size+1).
- else SSO path: dst->mSize=size; dst->mCapacity=0xF; memcpy(&dst->mData, srcData, 16).
- Tail (both paths): dst->mField3C=src->mField3C (u16); dst->mField38=src->mField38 (u32); dst->mValid=1; return dst.
- Dead/unique instructions: mov rax,[rcx]; mov rax,[rax+8] at 0xbc451d4/d7 (vtable-slot load, value unused — the call is the IAT slot call). int3 at 0xbc45290 is function-extent padding.
- Calls inside [0xbc45130, 0xbc45291): 0xbc451ec call [0xF99FFA0]; 0xbc45214 call [0xF99FFA0]; 0xbc4523f call 0xEEC6EC0; 0xbc45271 call 0x9BC830; 0xbc4527c call 0x9BC830; 0xbc4528a call 0x75720. All quoted verbatim in source + dossier.
- 0x75720 → native_boundary.tsv: stl; 0x9bc830 → alloc. Both declared extern "C" __declspec(noreturn) void (void*) following the sub_bc44b40 precedent (identical call fingerprint in-tree, liftcheck-clean). sub_eea6040 ([0xF99FFA0]) and sub_eec6ec0 are CRT/library intrinsics (std::malloc / std::memcpy), per sub_bc44b40.cpp precedent.
- UNRESOLVED CALL = none.

## FILES
- docs/progress/oc_U-EX1.bc45130.md (this file)
- src/client/features/render/native/bgfx/sub_bc45130.h (new: FbSsoString layout + static_asserts, signature)
- src/client/features/render/native/bgfx/sub_bc45130.cpp (new: lifted source, LIFT marker, LIFT_FN)
- docs/functions/bc45130.md (new: dossier with Reversed source (complete))

## LIFTCHECK
LIFTCHECK OK 0xbc45130

## UNRESOLVED CALL
none

CLOSES? YES
