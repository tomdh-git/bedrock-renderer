## NEXT
DONE - all artifacts written; `python tools/sigs/liftcheck.py 0xbc5f7b0` printed LIFTCHECK OK 0xbc5f7b0; blocked by UNRESOLVED CALLs; CLOSES? NO.

UNIT U-EX1.bc5f7b0 — LIFT sub_bc5f7b0 (0xbc5f7b0, 0x11e bytes, depth 4, D0, 1 callee in set: 0xbc76380; callees outside set per data file: 0xe951550). Result: blocked.

## Function (from the disassembly, all [V])
sub 0xbc5f7b0 "D3D12 submit RTX override", span [0xbc5f7b0, 0xbc5f8ce), size 0x11e, 82 instructions, 6 direct call sites. Listing: %TEMP%/opencode/bc5f7b0_listing.txt (rdis dis 0xbc5f7b0 200).
Signature: rcx = a0 (uintptr_t*, [rcx+0x0] read and written), edx = arg (uint32_t carried in ebx), return eax = ebx (uint32_t). x64 Microsoft ABI.

## Calls (verbatim quotes)
0xbc5f80b  call 0xEBCE5E0      -> UNRESOLVED CALL (not in CALLEES list {0xbc76380}; docs/data/native_boundary.tsv missing)
0xbc5f832  call 0xEBCE5E0      -> UNRESOLVED CALL (same)
0xbc5f854  call 0xEBCE570      -> UNRESOLVED CALL (same)
0xbc5f86e  call 0xBC76380      -> resolved: Bc76380_lifted (lift set, native symbol; eax consumed after both calls: 0xbc5f873 mov ebp,eax; 0xbc5f885 mov ebx,eax; 0xbc5f8af mov eax,ebx)
0xbc5f880  call 0xBC76380      -> resolved: Bc76380_lifted
0xbc5f8c8  call 0xE951550      -> UNRESOLVED CALL (callees_outside_set per data file; no boundary wrapper; cookie-fail path, int3 follows)

## Semantics
*(unsigned char*)*a0 == 0x5B ('[') ?
  no: *a0 += 3; return arg.   (jne 0xbc5f7df -> 0xBC5F89B, cookie, ret ebx=arg)
  yes: pairA={0xF847A07,0}; lenA=EBCE5E0(0xF59FECD,0x7FFFFFFF); if(lenA) pairA={0xF59FECD,lenA};
       pairB={0xF847A07,0}; lenB=EBCE5E0(*a0+1,0x7FFFFFFF); if(lenB) pairB={*a0+1,lenB};
       cmp=EBCE570(&pairB,&pairA,2);
       cmp==0: *a0 += 3; return arg.   (0xbc5f894 add r15,3; 0xbc5f898 mov [rsi],r15)
       cmp!=0: eax1=Bc76380_lifted(&savedPtr, counter|0x3B, arg&0xF, flags); ebp=eax1;
               eax2=Bc76380_lifted(&savedPtr, counter|0x6D, arg, flags); ebx=eax2;
               ebx=(ebx&0xFFFFFF00)|(((ebx<<4)|(ebp&0xF))&0xFF); *a0 = *a0 + 1; return packed ebx.
       counter upper bytes and flags (r9d, never set) are clobbered by the unresolved calls: unknowable statically.
cookie check: if ([0x1230A0C0] != [rsp+0x48]^rsp) { call 0xE951550(cookie); int3; } else ret ebx.

## FILES
- docs/progress/oc_U-EX1.bc5f7b0.md (this file)
- docs/functions/bc5f7b0.md (dossier: analysis + 'Reversed source (complete)')
- src/client/features/render/native/bgfx/sub_bc5f7b0.h (layout constants, static_asserts, signature, Bc76380_lifted declaration)
- src/client/features/render/native/bgfx/sub_bc5f7b0.cpp (LIFT marker, body, LIFT_FN registry entry)

## UNRESOLVED CALL
- 0xEBCE5E0 at `0xbc5f80b  call 0xEBCE5E0` (rcx=0xF59FECD, edx=0x7FFFFFFF, eax tested) and at `0xbc5f832  call 0xEBCE5E0` (rcx=rdi=*a0+1, edx=0x7FFFFFFF, eax tested). Target not in CALLEES list (only 0xbc76380); docs/data/native_boundary.tsv does not exist; no wrapper invented.
- 0xEBCE570 at `0xbc5f854  call 0xEBCE570` (rcx=&[rsp+0x20], rdx=&[rsp+0x30], r8d=2, eax -> je branch at 0xbc5f85b). Same status.
- 0xE951550 at `0xbc5f8c8  call 0xE951550` (rcx = stack cookie value; noreturn; 0xbc5f8cd int3 follows). Same status; listed as callees_outside_set in docs/data/native_functions.tsv.

## LIFTCHECK
LIFTCHECK OK 0xbc5f7b0

CLOSES? NO - UNRESOLVED CALL: `0xbc5f80b  call 0xEBCE5E0` (also `0xbc5f832  call 0xEBCE5E0`, `0xbc5f854  call 0xEBCE570`, `0xbc5f8c8  call 0xE951550`); none of 0xEBCE5E0/0xEBCE570/0xE951550 are in the CALLEES list (only 0xbc76380) and docs/data/native_boundary.tsv does not exist, so no sanctioned call target exists and the lift cannot be completed.
