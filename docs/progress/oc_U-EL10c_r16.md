## NEXT
DONE

# Unit U-EL10c — L10c viewport and render-resolution selection, dynamic resolution pending
Output file: docs/progress/oc_U-EL10c.md (only file for this unit).
Must run `python tools/delegate.py check docs/progress/oc_U-EL10c.md` (exit 0), then set line after "## NEXT" to DONE.

GOAL (verbatim from item line): close "L10c viewport and render-resolution selection, dynamic resolution pending". Do ONLY the pending part: who writes [elem+0x14] (the divisor float in endFrame's ratio computation `ratio = 1.0f / [elem+0x14]`) and link it to upscaling_percentage / options.targetResolution.

METHOD: static analysis of Minecraft.Windows.exe 1.26.62.01 (image-relative RVAs). Every quoted `0xRVA  instr` re-verified with rdis against the exe. Input data read in full: docs/progress/oc_U-Eratio.md, docs/progress/oc_U-EL17h_r6.md, docs/progress/oc_U-EL17h_r7.md, docs/functions/66232b0.md (endFrame dossier), docs/data/listings/_tmp_fn_66232b0.txt (endFrame listing), docs/data/listings/_tmp_67c73d0.txt (struct-copy), docs/progress/hints/L10c.txt (orchestrator r3/r4/r5 + 2026-11-22 CORRECTION), docs/progress/hints/L17h.txt. Live data: grep docs/data/live/*.txt for RVAs 0x66232b0/0x6625094/0x6624da7/0x67c791f/0xbc8d34e/0x566cb20/0xEEC8060/0x10c1dc3 — zero hits; no live capture names any L10c/L17h RVA.

------------------------------------------------------------
VERIFIED [V] findings (disassembly of the exe)

A) [0xEEC8060] is a read-only constant 1.0f — NO store exists (supersedes render-width-global theory):
   - Live read bytes 00 00 80 3F = 1.0f; page PAGE_READONLY; neighbours +0x68/+0x70 are double constants.
   - endFrame reads it: `0x6624da7 movss xmm6,[0xEEC8060]` and `0x6625077 movss xmm7,[0xEEC8060]`. ~4403 read-refs, ZERO static stores (rdis imm 0xEEC8060 = 0 hits, no movabs, no data pointer at 0xEEC8060).

B) endFrame argument layout [V from prologue]:
   - `0x66232fa mov [rbp+0x1998],rdx`   ; rdx = endFrame 2nd arg object (stored)
   - `0x6623301 mov [rbp+0x19D0],rcx`   ; rcx = this = BgfxFrameBuilder (stored)
   - endFrame reads `this+0x28`, `this+0xF0`, `this+0x898`; rdx object fields +0x38/+0x40/+0x50/+0x58.

C) endFrame element loop reads [elem+0x14] as ratio divisor [V]:
   - `0x6625046 mov rcx,[rbp+0x1998]`     ; rcx = rdx object
   - `0x662504d mov r15,[rcx+0x38]`       ; r15 = array1 start = [rdx+0x38]
   - `0x6625051 mov rcx,[rcx+0x40]`       
   - `0x6625055 mov [rbp+0x19A0],rcx`     ; array1 end = [rdx+0x40]
   - `0x6625077 movss xmm7,[0xEEC8060]`   ; xmm7 = 1.0f
   - `0x6625083 cmp r15,[rbp+0x19A0]`     ; loop exit vs array1 end
   - `0x6625090 movaps xmm8,xmm7`
   - `0x6625094 divss xmm8,[r15+0x14]`    ; ratio = 1.0f / [elem+0x14]  <-- THE RATIO
   - `0x6625898 add r15,0x208`            ; stride 0x208
   - `0x662589f cmp r15,[rbp+0x19A0]`
   - `0x66258a6 jne 0x6625090`
   - Array1 elements are 0x208-stride; [rdx+0x38]..[rdx+0x40] are POINTERS to array start/end (qword fields).

D) Second element loop (rdi) also reads [elem+0x14] [V]:
   - `0x66258e3 mov rax,[rbp+0x1998]`     ; rax = rdx object
   - `0x66258ea mov rdi,[rax+0x50]`       ; rdi = array2 start = [rdx+0x50]
   - `0x66258ee mov r8,[rax+0x58]`         ; r8  = array2 end   = [rdx+0x58]
   - `0x6625900 mov [rbp+0x19A8],r8`
   - `0x662595b add rdi,0x208`            ; stride 0x208
   - `0x662596f cmp rdi,r8`
   - `0x66259e1 movaps xmm6,xmm7`
   - `0x66259e4 divss xmm6,[rdi+0x14]`    ; ratio = 1.0f / [elem+0x14] (2nd loop)
   Both loops read [elem+0x14] from arrays owned by the rdx object (endFrame's 2nd arg).

E) sub_566cb20 writes element+0x14 via 16-byte movups block copy covering +0x8..0x17 [V]:
   - `566cb38 mov rsi,rdx`                ; rsi = src = 2nd param
   - `566cb3b mov r10,rcx`                ; r10 = dst = 1st param
   - `566cb43 movups xmm1,[rdx+8]`        ; R src+0x8..0x17 (covers +0x14)
   - `566cb5a movups [rcx+8],xmm1`        ; W dst+0x8..0x17 (covers +0x14)  <-- element+0x14 write
   - Size: movups = 16 bytes. Source register xmm1 originates from `movups xmm1,[rdx+8]` = descriptor/src+0x14.

F) sub_566cb20 also writes element+0x1F0 [V]:
   - `566d04a movss xmm0,[rsi+0x1F0]`
   - `566d052 movss [rdx+0x1F0],xmm0`

G) sub_67c73d0 struct-copy writes ctx+0x1F0 [V]:
   - `0x67c7917 movss xmm0,[rsi+0x1F0]`
   - `0x67c791f movss [rdx+0x1F0],xmm0`   ; WRITES ctx+0x1F0, rdx=ctx=r15
   - Called from endFrame at `0x662def4 call 0x67C73D0` (setup: `0x662deea lea rcx,[rbx-0x2B0]`, `0x662def1 mov rdx,r13`)

H) TAAU reads ctx+0x1F0 [V]:
   - `0xbc8d34e movups xmm0,[r13+0x1F0]`
   - `0xbc8d36d mulps xmm0,xmm1`          ; ratio * dims

I) sub_10c1ad0 writes heap descriptor+0x1F0 from settings-computed value [V]:
   - `0x10c1dc4 movups [r12+0x1F0],xmm4`  ; r12=[rcx+0x40]=descriptor obj; xmm4 computed from settings
   - sub_10c1ad0 reads settings by index: `call qword ptr [0xF99FFA0]` with r8d=0xFD/0xFE/0x100/0x101, reading `movss xmm7/8/9,[rax+0x18]` (float value at +0x18 of settings value object)
   - sub_10c1ad0 does NOT write descriptor+0x14 (writes +0xD8/+0xDC/+0xF8/+0x120..+0x244/+0x1F0/+0x1F4/+0x200/+0x204, but NOT +0x14)

J) Settings registration [V]:
   - `0x5b3e799 movups xmm0,[0xF5E13CC]`  ; "upscaling_percentage" content; default `0x5b3e835 mov dword ptr [rsp+0x30],0x32` (=50)
   - `0x5b3ead0 movups xmm0,[0xF5850DE]`  ; "options.targetResolution" content; default `0x5b3eb0c mov dword ptr [rsp+0x30],1` (=1)
   - Both registered via sub_9C4220/sub_5BC0530; strings have no direct code refs (table-registered)
   - L17h UPDATE: upscaling_percentage = option id 0x243, targetResolution = id 0x246. sub_10c1ad0 reads ids 0xFD/0xFE/0x100/0x101 — NOT the upscaling reader.

------------------------------------------------------------
EVIDENCE TABLE (offset | size | site | verbatim `0xRVA  instr` proof | meaning | tag)

| 0xEEC8060 read-only 1.0f | 4 | data_eec8060 | `0x6624da7  movss xmm6,[0xEEC8060]` | [V live] bytes 00 00 80 3F = 1.0f; PAGE_READONLY; NO store exists | [V] [V live] |
| 0xEEC8060 read #2 | 4 | endFrame 0x66232b0 | `0x6625077  movss xmm7,[0xEEC8060]` | endFrame loop reads render 1.0f into xmm7 | [V] |
| endFrame arg rdx stored | 8 | endFrame prologue | `0x66232fa  mov [rbp+0x1998],rdx` | rdx = endFrame 2nd arg object (array owner) | [V] |
| endFrame arg rcx stored | 8 | endFrame prologue | `0x6623301  mov [rbp+0x19D0],rcx` | rcx = this = BgfxFrameBuilder | [V] |
| array1 start = [rdx+0x38] | 8 | endFrame 0x66232b0 | `0x662504d  mov r15,[rcx+0x38]` | r15 = element array1 start = [rdx+0x38] | [V] |
| array1 end = [rdx+0x40] | 8 | endFrame 0x66232b0 | `0x6625055  mov [rbp+0x19A0],rcx` | array1 end bound = [rdx+0x40] | [V] |
| ratio numerator load | 4 | endFrame 0x66232b0 | `0x6625077  movss xmm7,[0xEEC8060]` | xmm7 = 1.0f (ratio numerator) | [V] |
| ratio computation divss | 4 | endFrame 0x66232b0 | `0x6625094  divss xmm8,[r15+0x14]` | ratio = 1.0f / [elem+0x14]; r15 iterates array1 stride 0x208 | [V] |
| loop stride add | 8 | endFrame 0x66232b0 | `0x6625898  add r15,0x208` | r15 steps by 0x208 per element | [V] |
| array2 start = [rdx+0x50] | 8 | endFrame 0x66232b0 | `0x66258ea  mov rdi,[rax+0x50]` | rdi = element array2 start = [rdx+0x50] | [V] |
| array2 end = [rdx+0x58] | 8 | endFrame 0x66232b0 | `0x66258ee  mov r8,[rax+0x58]` | r8 = array2 end bound = [rdx+0x58] | [V] |
| ratio divss #2 (array2) | 4 | endFrame 0x66232b0 | `0x66259e4  divss xmm6,[rdi+0x14]` | ratio = 1.0f / [elem+0x14] (2nd loop, rdi stride 0x208) | [V] |
| sub_566cb20 src param | 8 | sub_566cb20 | `566cb38  mov rsi,rdx` | rsi = src descriptor (2nd param) | [V] |
| sub_566cb20 dst param | 8 | sub_566cb20 | `566cb3b  mov r10,rcx` | r10 = dst element (1st param) | [V] |
| sub_566cb20 +0x8 block load | 16 | sub_566cb20 | `566cb43  movups xmm1,[rdx+8]` | load src+0x8..0x17 (covers +0x14); xmm1 = source of dst+0x14 store | [V] |
| sub_566cb20 +0x8 block store | 16 | sub_566cb20 | `566cb5a  movups [rcx+8],xmm1` | WRITE dst+0x8..0x17 (covers element+0x14); size 16 (movups) | [V] |
| sub_566cb20 +0x1F0 load | 4 | sub_566cb20 | `566d04a  movss xmm0,[rsi+0x1F0]` | load descriptor+0x1F0 | [V] |
| sub_566cb20 +0x1F0 store | 4 | sub_566cb20 | `566d052  movss [rdx+0x1F0],xmm0` | WRITE element+0x1F0 | [V] |
| sub_67c73d0 +0x1F0 load | 4 | struct-copy 0x67C73D0 | `0x67c7917  movss xmm0,[rsi+0x1F0]` | load source(r13)+0x1F0 | [V] |
| ctx+0x1F0 write | 4 | struct-copy 0x67C73D0 | `0x67c791f  movss [rdx+0x1F0],xmm0` | WRITE ctx+0x1F0; rdx=ctx=r15 | [V] |
| struct-copy call from endFrame | 5 | endFrame 0x66232b0 | `0x662def4  call 0x67C73D0` | endFrame invokes struct-copy per element | [V] |
| TAAU ctx+0x1F0 read | 16 | TAAU 0xbc8cfd0 | `0xbc8d34e  movups xmm0,[r13+0x1F0]` | ctx+0x1F0 read as render/display ratio | [V] |
| sub_10c1ad0 descriptor+0x1F0 write | 16 | sub_10c1ad0 | `0x10c1dc4  movups [r12+0x1F0],xmm4` | WRITE heap descriptor+0x1F0; xmm4 computed from settings get-by-index r8d=0xFD/0xFE/0x100/0x101 | [V] |
| sub_10c1ad0 settings read | - | sub_10c1ad0 | `call qword ptr [0xF99FFA0]` with r8d=0xFD/0xFE/0x100/0x101 | settings get-by-index; reads float at [rax+0x18] | [V] |
| upscaling_percentage registration | 16 | Options ctor 0x5b0c1b0 | `0x5b3e799  movups xmm0,[0xF5E13CC]` | registers upscaling_percentage (default 50=0x32); computes NO ratio | [V] |
| options.targetResolution registration | 16 | Options ctor 0x5b0c1b0 | `0x5b3ead0  movups xmm0,[0xF5850DE]` | registers options.targetResolution (default 1); computes NO ratio | [V] |

------------------------------------------------------------
HOP-BY-HOP BACKWARD TRACE from [elem+0x14] (per orchestrator r14 instruction)

Hop 0 (the read): endFrame reads [elem+0x14] at `0x6625094 divss xmm8,[r15+0x14]` where r15 iterates array1 ([rdx+0x38]..[rdx+0x40], stride 0x208). Array1 is owned by rdx = endFrame's 2nd argument object. [V]

Hop 1 (who writes array1 element+0x14): sub_566cb20 writes element+0x14 at `566cb5a movups [rcx+8],xmm1` (16-byte movups block covering +0x8..0x17). Source register xmm1 = `566cb43 movups xmm1,[rdx+8]` (descriptor/src+0x14). BUT: sub_566cb20's 7 endFrame call sites write to passLookup-descriptor element arrays (0x2B0-stride at call site `0x662abef call 0x566CB20` with rcx=[rsi+0x50]=passLookup cursor) and stack template [rbp+0x170] — NOT to array1 ([rdx+0x38..0x40]). Array1 is a separate 0x208-stride array in the rdx object. [V for the instruction; ? for whether it targets array1]

Hop 2 (who writes array1 itself): array1 ([rdx+0x38]..[rdx+0x40]) is a field pair (start/end pointers) in rdx = endFrame's 2nd argument object. rdx is passed INTO endFrame by its caller. endFrame 0x66232b0 has NO direct callers (BgfxFrameBuilder vtable slot 18, indirect call only). The caller that builds rdx's array1 and its element+0x14 values is upstream of endFrame and not statically reachable. [?]

Hop 3 (descriptor+0x14 source for sub_566cb20 block copy): sub_566cb20's block copy source is `566cb43 movups xmm1,[rdx+8]` where rdx = sub_566cb20's 2nd param (descriptor/src base). The descriptor's +0x14 is read but NOT written by sub_10c1ad0 (which writes +0xD8..+0x244 incl. +0x1F0 but NOT +0x14). Who writes descriptor+0x14 is not located. [?]

Hop 4 (settings link): sub_10c1ad0 reads settings by FIXED INDEX r8d=0xFD/0xFE/0x100/0x101 (via `call qword ptr [0xF99FFA0]` = get-option-by-id vtable[0xD8]), reading float at [rax+0x18]. L17h UPDATE: upscaling_percentage = id 0x243, targetResolution = id 0x246 — so 0xFD/0xFE/0x100/0x101 is NOT the upscaling reader. No index↔name mapping exists in the binary. The name-based readers sub_5b0c1b0 ("upscaling_percentage" @0x5b3e799) and sub_51cd6c0 ("upscaling_percentage" @0x51de12b) store results at object+0x1BB8, not at descriptor+0x14 or array1+0x14. [I]

------------------------------------------------------------
CLOSES? — NO

Single blocking fact:
The ratio IS computed inside endFrame at `0x6625094 divss xmm8,[r15+0x14]` (1.0f / [elem+0x14]), and the full propagation chain to ctx+0x1F0 → TAAU is proven [V]. However, [elem+0x14] is read from array1 ([rdx+0x38]..[rdx+0x40]) which is owned by rdx = endFrame's 2nd argument object — built by endFrame's CALLER, which is not statically reachable (endFrame has no direct callers; vtable slot 18 indirect call only). sub_566cb20's `566cb5a movups [rcx+8],xmm1` writes element+0x14 to passLookup arrays (0x2B0-stride), NOT to array1. sub_10c1ad0 writes descriptor+0x1F0 from settings (r8d=0xFD/0xFE/0x100/0x101) but does NOT write descriptor+0x14, and upscaling_percentage (id 0x243) / targetResolution (id 0x246) are NOT among the indices sub_10c1ad0 reads. No index↔name mapping exists to connect them. Until the array1 element+0x14 writer (upstream of endFrame) and its link to upscaling_percentage/targetResolution are proven by [V] rows, CLOSES? cannot be YES.

------------------------------------------------------------
TOOL REQUESTS: None — all evidence gathered with rdis.exe and precomputed listings; no new scripts written. A livecap write-watch on array1 element+0x14 (or on the rdx object's +0x38/+0x40 fields) while changing upscaling_percentage in video options is still needed to close this item, but no function-entry RVA for the array1 builder was identified statically so no request was queued.
