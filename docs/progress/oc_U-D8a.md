# oc_U-D8a — UIMesh description consumer 0x674a3a0 (UI tag 2)

Brief: docs/OPENCODE_BRIEF.md. Static analysis only; exe Minecraft.Windows.exe 1.26.62.01; RVAs image-relative.
RenderUIMeshDescription is in src/sdk/mc/deps/minecraft_renderer/framebuilder/Descriptions.h (READ ONLY, not edited): size 0xA8; +0x00/+0x08/+0x10 qwords; mRefs[4] SharedRef at +0x18..+0x57; mRefCount u64 at +0x58; +0x60/+0x68 qwords; +0x70 float; +0x78 qword; mFlags80[6] at +0x80..+0x85; mValue86 u16 at +0x86; DescVariantRef storage at +0x88 (tag u8 at +0xA0).
OPEN items: qwords +0x00/+0x08/+0x10/+0x60/+0x68/+0x78 have no semantic names; forwarded to 0x674a3a0 whose stack-argument slots were not re-mapped. This unit maps the slots and the callee's use of each.

## NEXT
Run tools/sigs/verify_oc.py on this file to confirm every quoted instruction. Remaining uncertainty: exact semantic (mesh ptr vs texture ref vs transform) for desc+0x78, desc+0x68, desc+0x00, desc+0x08, desc+0x60; which uniform name each vec4/float feeds (uniform-name static not yet resolved).

## CALLER SIDE [V] — UIMesh case 0x6664bd6 (tag 2) in docs/data/listings/ui_visitor_6664a00_6668510.txt, calls 0x674A3A0 at 0x6664f4a with r8d=0 (non-text path)
Dispatch state: r8 = description ptr (kept in r9 at 0x6664a59 `mov r9,[r8]`), rdx = frame context -> r14 (0x6664a53 `mov r14,rdx`), rcx = BgfxFrameBuilder -> r13 (0x6664a56 `mov r13,rcx`). NOTE: r13/r14 are REASSIGNED inside the case to desc fields, but the REGISTER args at the call use values set BEFORE reassignment (rcx=BgfxFrameBuilder at 0x6664e91, rdx=rdi where rdi=r14=frame context at 0x6664e94/0x6664f44). The STACK args use the REASSIGNED values (r13=desc+0x00, r14=desc+0x08).

Mode bytes (0x6664bd6..0x6664c03): mode = +0x83 ? 2 : (+0x82 ? 1 : +0x84):
  0x6664bd6  movzx ecx,byte ptr [r9+0x82]
  0x6664bde  movzx r12d,byte ptr [r9+0x83]
  0x6664be6  movzx edx,byte ptr [r9+0x84]
  0x6664bee  test cl,cl
  0x6664bf0  mov r8d,1
  0x6664bf6  cmove r8d,edx
  0x6664bfa  test r12b,r12b
  0x6664bfd  mov r10d,2
  0x6664c03  cmove r10d,r8d        ; r10d = uiMeshMode (dword stack arg)
Register args at call 0x6664f4a:
  0x6664e91  mov rcx,r13           ; rcx = BgfxFrameBuilder (set at 0x6664a56, NOT reassigned before call)
  0x6664e94  mov rdi,r14           ; rdi = r14 = frame context (set at 0x6664a53, NOT reassigned before call)
  0x6664f44  mov rdx,rdi           ; rdx = frame context (2nd register arg)
  0x6664f47  xor r8d,r8d           ; r8d = 0 -> text-path flag = 0 -> NON-TEXT path at callee 0x674a67e
  ; r9 = desc + 0x86 (0x6664eb8 `add r9,0x86`) = 4th register arg, points at mValue86/u16 area [? why]
Stack args at call (writer slots [rsp+0x20..0xA0], listing lines 242-264; map 1:1 to callee [rbp+0xE80..0xF00]):
  0x6664f08  mov [rsp+0x20],r14            ; desc +0x08 qword      -> callee [rbp+0xE80]
  0x6664f03  mov [rsp+0x28],r12            ; desc +0x78 qword      -> callee [rbp+0xE88]
  0x6664efe  mov [rsp+0x30],r15            ; desc +0x10 qword      -> callee [rbp+0xE90]
  0x6664ef9  mov [rsp+0x38],r13            ; desc +0x00 qword      -> callee [rbp+0xE98]
  0x6664ef4  mov [rsp+0x40],rax            ; rax = lea [r9+0x18] (0x6664c3b) = desc +0x18 mRefs array address -> callee [rbp+0xEA0]
  0x6664eef  mov [rsp+0x48],r10            ; r10 = lea [rbp+0x400] = &zeroed16 local (&mRefs[1] SharedRef by-ref) -> callee [rbp+0xEA8]
  0x6664f3a  mov [rsp+0x50],al             ; desc +0x80 byte (flag) -> callee [rbp+0xEB0]
  0x6664ee3  mov [rsp+0x58],r11            ; desc +0x60 qword (r11=[r9+0x60] at 0x6664c2b) -> callee [rbp+0xEB8]
  0x6664ede  mov [rsp+0x60],rdx            ; desc +0x68 qword (rdx=[r9+0x68] at 0x6664c2f) -> callee [rbp+0xEC0]
  0x6664f3e  movss [rsp+0x68],xmm0         ; desc +0x70 float (xmm0=[r9+0x70] at 0x6664c25) -> callee [rbp+0xEC8]
  0x6664f2e  mov [rsp+0x70],r8b            ; desc +0x81 byte (r8b=[r9+0x81] at 0x6664c1d) -> callee [rbp+0xED0]
  0x6664f2a  mov [rsp+0x78],al             ; desc +0x83 byte (mode bit) -> callee [rbp+0xED8]
  0x6664f1c  mov [rsp+0x80],al             ; desc +0x82 byte (mode bit) -> callee [rbp+0xEE0]
  0x6664f0d  mov [rsp+0x88],sil            ; desc +0x85 byte (esi=[r9+0x85] at 0x6664c15) -> callee [rbp+0xEE8]
  0x6664ed6  mov [rsp+0x90],r10d           ; uiMeshMode dword -> callee [rbp+0xEF0]
  0x6664ece  mov [rsp+0x98],rbx            ; rbx = lea [rbp+0x1E0] (&zeroed16 SharedRef by-ref) -> callee [rbp+0xEF8]
  0x6664ebf  mov [rsp+0xA0],rbx            ; rbx = lea [r9+0x88] (0x6664c07) = desc +0x88 DescVariantRef storage address -> callee [rbp+0xF00]
Note: 0x6664c58 `jb 0x6664E7C` when mRefCount < 2 takes cold path: &mRefs[1] arg becomes {0,0} (0x6664e82-0x6664e85 zero [rbp+0x400..0x408], 0x6664e8e `xor r15d,r15d`).

Pseudocode of caller setup:
  uiMeshMode = desc->mValue83 ? 2 : (desc->mValue82 ? desc->mValue84 : 1);
  call 0x674a3a0(bgfxBuilder=rcx, frameCtx=rdx, textPathFlag=0, r9=desc+0x86,
                 stack: desc+0x08, desc+0x78, desc+0x10, desc+0x00, &desc+0x18(mRefs), &mRefs[1],
                 desc+0x80, desc+0x60, desc+0x68, desc+0x70(float), desc+0x81, desc+0x83, desc+0x82, desc+0x85,
                 uiMeshMode, &zeroed16, &desc+0x88(variant))

## CALLEE SIDE 0x674a3a0 [V] — prologue and register/stack arg load
  0x674a3cd  mov [rbp+0x788],r9            ; save r9 = desc+0x86
  0x674a3d4  mov r12d,r8d                  ; r12d = text-path flag = 0 (UIMesh -> non-text)
  0x674a3d7  mov rsi,rdx                   ; rsi = frame context
  0x674a3da  mov r13,rcx                   ; r13 = BgfxFrameBuilder
  0x674a3dd  mov rax,[rbp+0xE98]           ; rax = desc+0x00
  0x674a3e4  mov rbx,[rbp+0xE88]           ; rbx = desc+0x78
  0x674a4c3  movzx edi,byte ptr [rbp+0xED0] ; edi = desc+0x81 byte ("alt" flag)
  0x674a4ca  mov r15,[rbp+0xEB8]           ; r15 = desc+0x60
  0x674a4d1  mov r14,[rbp+0xE80]           ; r14 = desc+0x08
  0x674a4df  test r12d,r12d
  0x674a4e2  je 0x674A67E                  ; r12d==0 -> NON-TEXT path

## CALLEE NON-TEXT PATH [V] — desc field consumption
desc+0x78 (rbx): null-tested, gates use of desc+0x08; stored to [rbp+0x918] texture/SharedRef slot:
  0x674a6a3  test rbx,rbx
  0x674a6a6  je 0x674A7F5
  0x674a6d1  mov r15,r14                   ; desc+0x78 != 0 -> r15 = desc+0x08 (overwrites desc+0x60)
  0x674aa1e  mov [rbp+0x918],rbx           ; desc+0x78 stored to [rbp+0x918] (passed as texture/SharedRef param to 0x5679DB0/0xbcaba00 sites)
desc+0x08 (r14 -> r15): read as 16-byte movups block, set as uniform vec4:
  0x674a9ff  mov rax,r15                   ; rax = r15 = desc+0x08
  0x674aa09  movups xmm0,[rax]             ; read desc+0x08..+0x17 as 16-byte block
  0x674aa0c  movaps [rbp+0xC10],xmm0       ; store to uniform scratch
desc+0x00 (rax): desc+0x10 byte flag checked, desc+0x00..+0x0F read as movups (conditional on desc+0x10==1):
  0x674a478  cmp byte ptr [rax+0x10],1     ; [desc+0x10] == 1?
  0x674a485  movups xmm0,[rax]             ; read desc+0x00..+0x0F as 16-byte block
  0x674a488  movups [rbp+0x8A8],xmm0       ; store to local
desc+0x60 ([rbp+0xEB8]): loaded as r15, then re-loaded at 0x674c00a and read as 16-byte movups uniform vec4:
  0x674c00a  mov r15,[rbp+0xEB8]           ; r15 = desc+0x60
  0x674cdbc  movups xmm0,[r15]             ; read desc+0x60..+0x67 as 16-byte block
  0x674cdc0  movaps [rbp+0xC10],xmm0       ; store to uniform scratch -> 0x5679DB0 setUniform
desc+0x68 ([rbp+0xEC0]): passed as r9 (4th arg) to texture/material binder 0x66A0EC0:
  0x674c1d3  mov r9,[rbp+0xEC0]            ; r9 = desc+0x68
  0x674c1f6  call 0x66A0EC0                ; texture/material binding (r8=static table, rcx=&[rbp+0xB68], rdx=&[rbp+0xC10], r9=desc+0x68)
desc+0x70 ([rbp+0xEC8]): float scalar, broadcast and set as uniform:
  0x674b411  movss xmm0,[rbp+0xEC8]        ; load desc+0x70 float
  0x674b419  shufps xmm0,xmm0,0            ; broadcast to all lanes
  0x674b41d  movaps [rbp+0xC10],xmm0
  0x674b4b5  call 0x5679DB0                ; UniformBlock::setUniform (desc+0x70 float uniform)
Material (NOT from description; hardcoded literal):
  0x674a708  lea rax,[0xF2BE5C8]           ; "UI/Glint" (0x674a708)
  0x674a747  call 0x67D6D70                ; material lookup "UI/Glint"
  0x674c0e8  cmp byte ptr [rbp+0xEB0],0    ; desc+0x80 flag: !=0 -> "UI/Sprite" path
  0x674c147  lea rax,[0xF2BE5E8]           ; "UI/Sprite" (0x674c147)
  0x674c186  call 0x67D6D70                ; material lookup "UI/Sprite"
Flag bytes:
  0x674a4c3  movzx edi,byte ptr [rbp+0xED0] ; desc+0x81 ("alt" flag)
  0x674c201  movzx eax,byte ptr [rbp+0xED8] ; desc+0x83
  0x674c227  movzx ecx,byte ptr [rbp+0xEE0] ; desc+0x82
  0x674c0e8  cmp byte ptr [rbp+0xEB0],0    ; desc+0x80
  0x674b559  cmp byte ptr [rbp+0xEE8],0    ; desc+0x85
Variant storage (desc+0x88 -> r14; tag at desc+0xA0 = [r14+0x18]):
  0x674b4e6  mov r14,[rbp+0xF00]           ; r14 = desc+0x88 (DescVariantRef storage)
  0x674b53a  movzx eax,byte ptr [r14+0x18]  ; [desc+0xA0] = variant tag
  0x674b53f  cmp rax,3
  0x674b543  ja 0x674E428
  0x674b549  lea rcx,[0xF2BFC90]           ; table 0xf2bfc90
  0x674b550  movsxd rax,[rcx+rax*4]        ; jump table on variant tag (0->0x674b559 1->0x674b9b2 2->0x674b71a 3->0x674b85d)
Payload args passed to 0x67B9C90 (record-kind switch at 0x674b550):
  0x674b4fb  mov [rbp+0x810],rcx           ; [rbp+0x810] = desc+0x86 (from [rbp+0x788])
  0x674b502  mov [rbp+0x818],rax           ; [rbp+0x818] = desc+0x10 (from [rbp+0xE90])
  0x674b510  mov [rbp+0x820],rax           ; [rbp+0x820] = &uiMeshMode ([rbp+0xEF0])
  0x674b517  mov [rbp+0x828],r13           ; [rbp+0x828] = BgfxFrameBuilder (r13=[rbp+0xC08])
  0x674b525  mov [rbp+0x830],rax           ; [rbp+0x830] = &record ([rbp+0x890])
  0x674b52c  mov [rbp+0x838],r15           ; [rbp+0x838] = desc+0x08 or desc+0x60 (r15)
  0x674b533  mov [rbp+0x840],r12           ; [rbp+0x840] = 0

## FIELD SEMANTIC SUMMARY (tags)
- desc+0x00: read as 16-byte movups block (0x674a485); desc+0x10 byte flag (0x674a478). [V read]. Semantics [?]: data block (transform row / color), NOT a mesh pointer (read as data, not dereferenced).
- desc+0x08: read as 16-byte movups uniform vec4 (0x674aa09); stored to payload [rbp+0x838]. [V read]. Semantics [?]: transform row or color.
- desc+0x10: byte flag checked (0x674a478); passed as payload arg [rbp+0x818]. [V read]. Semantics [?]: mode/flag.
- desc+0x60: read as 16-byte movups uniform vec4 (0x674cdbc). [V read]. Semantics [?]: transform row or color.
- desc+0x68: passed to texture/material binder 0x66A0EC0 (0x674c1d3). [V read]. Semantics [?]: likely texture reference / material param.
- desc+0x70: float scalar uniform via 0x5679DB0 (0x674b411). [V read]. Semantics [?]: opacity / scale.
- desc+0x78: null-tested pointer (0x674a6a3); stored to [rbp+0x918] texture/SharedRef slot. [V read]. Semantics [?]: mesh pointer or texture ref.
- desc+0x80..+0x85: flag bytes controlling material selection (UI/Glint vs UI/Sprite) and record fields [V read]. Semantics [?].
- desc+0x86: passed as payload arg [rbp+0x810] [V read]. Semantics [?].
- desc+0x88: variant storage; tag at +0xA0 switched at 0x674b53a [V read]. Semantics [?]: variant payload (alt0={u64,SharedRef}, alt1=heap ptr, etc.).

## MATERIAL
- Non-text path default: "UI/Glint" via 0x67D6D70 (0x674a708 literal) [V].
- If desc+0x80 != 0: "UI/Sprite" via 0x67D6D70 (0x674c147/0x674c283 literal) [V]. Material is NOT read from any description qword.

## VERIFICATION
verify_oc.py: not yet run on this file. All quoted instruction lines above are from rdis output (UTF-16 -> utf8) and match the listings in docs/data/listings/ui_visitor_6664a00_6668510.txt (caller) and live rdis of 0x674a3a0 (callee).

## TOOL REQUESTS
None yet.