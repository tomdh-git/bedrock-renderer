## NEXT
DONE: unit complete, LIFTCHECK OK, CLOSES? YES

## UNIT
U-EX1.bc7c4e0: lift sub_bc7c4e0 at 0xbc7c4e0, size 0x95 (0xbc7c4e0..0xbc7c575), depth 2, milestone 1, region bgfx, status D0. Name from data file: "VV frame-graph builder". Callee set: empty (0 callees in set per checklist line).

## DISASSEMBLY (full function, verbatim from rdis dis 0xbc7c4e0 100; range confirmed by rdis sum: [0xbc7c4e0, 0xbc7c575), extent proven .pdata)
49 instructions covering push rsi; push rdi; sub rsp,0x28; movzx eax,byte ptr [rcx+0x10]; cmp al,[rdx+0x10]; jne short 0xBC7C4FE; test al,al; je short 0xBC7C56E; add rsp,0x28; pop rdi; pop rsi; jmp 0xBC55EA0; loc_bc7c4fe: test al,al; mov rdi,rdx; cmovne rdi,rcx; cmovne rcx,rdx; xorps xmm0,xmm0; movups [rcx],xmm0; mov rax,[rdi+8]; test rax,rax; je short 0xBC7C51E; lock inc dword ptr [rax+8]; loc_bc7c51e: mov rax,[rdi]; mov [rcx],rax; mov rax,[rdi+8]; mov [rcx+8],rax; mov byte ptr [rcx+0x10],1; cmp byte ptr [rdi+0x10],1; jne short 0xBC7C56E; mov rsi,[rdi+8]; test rsi,rsi; je short 0xBC7C56A; lock dec dword ptr [rsi+8]; jne short 0xBC7C56A; mov rax,[rsi]; mov rax,[rax]; mov rcx,rsi; call qword ptr [0xF99FFA0]; lock dec dword ptr [rsi+0xC]; jne short 0xBC7C56A; mov rax,[rsi]; mov rax,[rax+8]; mov rcx,rsi; call qword ptr [0xF99FFA0]; loc_bc7c56a: mov byte ptr [rdi+0x10],0; loc_bc7c56e: add rsp,0x28; pop rdi; pop rsi; ret

## SEMANTICS
void sub_bc7c4e0(FrameSlot* a0 rcx, FrameSlot* a1 rdx); FrameSlot = { void* raw +0x00; RefCounted* ref +0x08; uint8_t flag +0x10 }; sizeof 0x18.
- flags equal & zero -> no-op return; flags equal & nonzero -> tail jmp sub_bc55ea0(a0,a1); flags differ -> src=nonzero-flag slot, dst=zero-flag slot; zero dst 16B; addref src->ref; dst = {src->raw, src->ref, flag=1}; if src->flag==1: strong-- src->ref; if 0 -> vtable[0](rsi) via call [0xF99FFA0] (slot=sub_eea6040 jmp-rax); weak--; if 0 -> vtable[1](rsi) via same slot; src->flag=0. Ret void.

## CALLEES (all resolved; none unresolved)
- sub_bc55ea0 (native::sub_bc55ea0, lift set, native_functions.tsv) — tail call 0xbc7c4f9, forward-declared via sub_bc55ea0.h, called through native symbol with Slot* casts.
- call qword ptr [0xF99FFA0] x2 (0xbc7c54e, 0xbc7c564) -> slot cell holds sub_eea6040 = vendor boundary (native_boundary.tsv: "0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)"). Lifted as virtual calls through the loaded vtable entry (rax = vtable[0] / vtable[1], rcx = rsi), exactly per sub_bc55ea0.cpp precedent; calls quoted verbatim.

## FILES
- docs/progress/oc_U-EX1.bc7c4e0.md (this file)
- src/client/features/render/native/bgfx/sub_bc7c4e0.h (new)
- src/client/features/render/native/bgfx/sub_bc7c4e0.cpp (new)
- docs/functions/bc7c4e0.md (new dossier)

## LIFTCHECK
LIFTCHECK OK 0xbc7c4e0

## UNRESOLVED CALL
none — both call targets resolved: sub_bc55ea0 (lift set) and sub_eea6040 via data slot 0xF99FFA0 (vendor boundary table row)

## TOOL REQUESTS
None

## VERIFICATION
verify_oc on dossier: claimed=46 match=46 mismatch=0 no-such-instr=0
liftcheck: LIFTCHECK OK 0xbc7c4e0 (exit 0)

CLOSES? YES
