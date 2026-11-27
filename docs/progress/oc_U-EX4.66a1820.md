## NEXT
DONE

Unit U-EX4.66a1820: lift 0x66a1820 (size 0x36 bytes, "Item group visitor", depth 1, D0, framebuilder) — complete, LIFTCHECK OK.

Analysis (all [V] from `rdis dis 0x66a1820 0x36`, [0x66a1820, 0x66a1856)):
- 0x66a1820 sub rsp,0x28; 0x66a1824 mov rax,[rdx]; 0x66a1827 cmp rax,0xFFFFFFFFFFFFFFFF; 0x66a182b je short 0x66A1850 -> fail if a1[0] == -1 (nothing written)
- 0x66a182d mov rdx,[rdx+8]; 0x66a1831 mov [rcx],rax; 0x66a1834 mov [rcx+8],rdx -> copy pair a1->a0
- 0x66a1838 test rdx,rdx; 0x66a183b setne dl; 0x66a183e test rax,rax; 0x66a1841 sete al; 0x66a1844 or al,dl; 0x66a1846 je short 0x66a1850 -> fail if a1[0] != 0 && a1[1] == 0, else return rcx
- 0x66a1848 mov rax,rcx; 0x66a184b add rsp,0x28; 0x66a184f ret
- 0x66a1850 call 0x78ED0 -> sub_78ed0 (class crt boundary, docs/data/native_boundary.tsv line 11; noreturn thunk at 0x78ed0: call qword ptr [0xF9A8CF0] then int3 padding); RCX = a0 at both call sites
- 0x66a1855 int3 (unreachable)
Callees: none in the lift set; 0x78ed0 is boundary `crt`, called via native::Boundary<void, std::uintptr_t> sub_78ed0("sub_78ed0") with RCX = a0 — same wrapper precedent as sub_bc5e120 (0xbc5e1d6 call 0x78ED0). No UNRESOLVED CALLs. No null guards/SEH added (original has none).

Signature lifted: uint64_t* sub_66a1820(uint64_t* a0, uint64_t* a1) (RCX=a0 out pair, RDX=a1 source pair, RAX=a0).

## FILES
- src/client/features/render/native/framebuilder/sub_66a1820.h (new: layout constants kPairOffset0/kPairOffset8/kPairSize, PairU64 layout, static_asserts, signature)
- src/client/features/render/native/framebuilder/sub_66a1820.cpp (new: // LIFT 0x66a1820 size 0x36 1.26.62.01 sub_66a1820, lifted body, boundary wrapper, verbatim #if 0 quote block, footprint, LIFT_FN registry entry)
- docs/functions/66a1820.md (new: dossier with Reversed source (complete), struct fields, callees, ownership/threading, version anchors)
- docs/progress/oc_U-EX4.66a1820.md (this file)
No other files created or edited.

## LIFTCHECK
LIFTCHECK OK 0x66a1820

## UNRESOLVED CALL
none

CLOSES? YES
