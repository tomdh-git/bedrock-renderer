## NEXT
DONE — liftcheck OK, verify_oc 36/36 match, no unresolved calls.

Disassembly of [0x56ae910, 0x56ae989) (size 0x79) captured from rdis dis 0x56ae910 80:
- 0x56ae910 push rsi / 0x56ae911 sub rsp,0x30 / 0x56ae915 cmp byte ptr [rcx+0x40],1 / 0x56ae919 jne short 0x56AE969
- 0x56ae91b mov rax,[rcx] / 0x56ae91e test rax,rax / 0x56ae921 je short 0x56AE969
- 0x56ae923 mov rdx,[rcx+0x10] / 0x56ae927 sub rdx,rax / 0x56ae92a cmp rdx,0x1000 / 0x56ae931 jb short 0x56AE950
- 0x56ae933 mov r8,[rax-8] / 0x56ae937 add rax,0xFFFFFFFFFFFFFFF8 / 0x56ae93b sub rax,r8 / 0x56ae93e cmp rax,0x20 / 0x56ae942 jae short 0x56AE96F
- 0x56ae944 mov rsi,rcx / 0x56ae947 or rdx,0x27 / 0x56ae94b mov rax,r8 / 0x56ae94e jmp short 0x56AE953
- 0x56ae950 mov rsi,rcx / 0x56ae953 mov rcx,rax / 0x56ae956 call 0xE935700
- 0x56ae95b xorps xmm0,xmm0 / 0x56ae95e movups [rsi],xmm0 / 0x56ae961 mov qword ptr [rsi+0x10],0
- 0x56ae969 add rsp,0x30 / 0x56ae96d pop rsi / 0x56ae96e ret
- 0x56ae96f mov qword ptr [rsp+0x20],0 / 0x56ae978 xor ecx,ecx / 0x56ae97a xor edx,edx / 0x56ae97c xor r8d,r8d / 0x56ae97f xor r9d,r9d / 0x56ae982 call qword ptr [0xF9A8C78] / 0x56ae988 int3

Callees: sub_e935700 (0xe935700, lift set, native_functions.tsv line 1620, forward-declared, called directly); call qword ptr [0xF9A8C78] (_invoke_watson via IAT data slot, hard rule 69, read slot at call time, noreturn).
Object layout: +0x00 vtable (read), +0x10 some_ptr (read+write to 0), +0x40 flag byte (read ==1), +0x00..+0x18 zeroed (24 bytes).
Returns void*: sub_e935700's result on main paths; rax==0 on vtable==0 path; rax undefined on flag!=1 path.

## FILES
- docs/progress/oc_U-EX5.56ae910.md (this file)
- src/client/features/render/native/passes/sub_56ae910.h
- src/client/features/render/native/passes/sub_56ae910.cpp
- docs/functions/56ae910.md

## LIFTCHECK
LIFTCHECK OK 0x56ae910

## UNRESOLVED CALL
none

## TOOL REQUESTS
none

CLOSES? YES