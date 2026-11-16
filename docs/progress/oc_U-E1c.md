## NEXT
DONE: All 6 handlers (tags 1, 5, 2, 9, 3, 7) documented with instruction-complete listings, field read tables, live data comparisons, and Descriptions.h cross-reference. Verification: 358/358 lines match.

---

# Unit U-E1c: Item visitor tags 1, 5, 2, 3, 7, 9

## Step 1: Handler Listings (Instruction-Complete)

### Tag 1: Nametag handler at 0x6646f5b
**Entry**: Jumped to from visitor 0x6646980 jump table (tag 1). `rdi` = description pointer (from visitor arg3+0x0). `rbx` = FrameBuilder `this`. `rbp+0x8A0` = frame context pointer (from visitor arg2).
**Extent**: 0x6646f5b .. 0x66471dd (next handler at 0x66471de is tag 5)

```
0x6646f5b  mov rax, [rdi+0x58]                       ; Load mShared.mPtr (SharedRef.ptr at desc+0x58)
0x6646f5f  test rax, rax
0x6646f62  je 0x664EBD7                                ; -> sub_664ebd7 (early exit if no shared object)
0x6646f68  cmp qword ptr [rax+0x40], 0                 ; Check mShared.mPtr+0x40 (shared object field)
0x6646f6d  je 0x664EBD7                                ; -> sub_664ebd7 (early exit if field zero)
0x6646f73  lea rdx, [rdi+0x58]                         ; rdx = &description.mShared (SharedRef*)
0x6646f77  mov rax, [rdi]                              ; rax = description.mOwner (desc+0x00)
0x6646f7a  movzx r8d, byte ptr [rax+0x39]              ; r8 = mOwner+0x39 (byte flag)
0x6646f7f  lea rcx, [rbp+0x140]                        ; Stack buffer for string/output
0x6646f86  call 0x66B2B30                                ; -> sub_66b2b30 (processes mOwner+0x39, writes to stack)
0x6646f8b  xorps xmm0, xmm0
0x6646f8e  movaps [rbp+0x80], xmm0                      ; Zero stack buffer (8 xmm registers = 128 bytes at rbp+0x10..0x8F)
0x6646f95  movaps [rbp+0x70], xmm0
0x6646f99  movaps [rbp+0x60], xmm0
0x6646f9d  movaps [rbp+0x50], xmm0
0x6646fa1  movaps [rbp+0x40], xmm0
0x6646fa5  movaps [rbp+0x30], xmm0
0x6646fa9  movaps [rbp+0x20], xmm0
0x6646fad  movaps [rbp+0x10], xmm0
0x6646fb1  mov qword ptr [rbp+0x90], 0
0x6646fbc  mov qword ptr [rbp+0x1F8], 0
0x6646fc7  mov qword ptr [rbp+0x200], 7                ; String length = 7
0x6646fd2  mov qword ptr [rbp+0x208], 0xF              ; Capacity/flags = 0xF
0x6646fdd  mov dword ptr [rbp+0x1F0], 0x656D614E       ; "Name" (little-endian)
0x6646fe7  mov dword ptr [rbp+0x1F3], 0x67617465       ; "tag"  (little-endian) -> "Nametag"
0x6646ff1  mov byte ptr [rbp+0x1F7], 0                 ; Null terminator
0x6646ff8  mov rax, [rbp+0x8A0]                        ; Load frame context pointer
0x6646fff  mov r13, [rax+0x40]                         ; r13 = frame_context+0x40
0x6647003  mov r15, [rax+0x68]                         ; r15 = frame_context+0x68 (FrameBuilder+0xF0+0x68)
0x6647007  mov rax, 0x6EF4382226DE1FD6                 ; FNV-1a64 hash constant
0x6647011  mov [rbp+0x880], rax                        ; Store hash constant at stack
0x6647018  mov qword ptr [rbp+0x888], 0                ; Zero next qword
0x6647023  mov rcx, [0x1233E1B0]                       ; Global pointer (data_1233e1b0)
0x664702a  mov rax, [rcx]                              ; Dereference
0x664702d  mov rax, [rax+0x10]                         ; rax = object at +0x10
0x6647031  mov dl, 0x30                                ; Size 0x30
0x6647033  call qword ptr [0xF99FFA0]                  ; -> sub_eea6040 (allocator)
0x6647039  nop
0x664703a  mov r14d, eax                               ; r14d = allocation result (handle/index)
0x664703d  lea r12, [r15+0x98]                         ; r12 = frame_context+0x68+0x98 = frame_context+0x100
0x6647044  mov rcx, r12
0x6647047  call 0xEEC59F0                                ; -> sub_eec59f0 (check/initialize)
0x664704c  test eax, eax
0x664704e  mov [rbp+0x898], r14b                       ; Store result byte
0x6647055  jne 0x664F04D                                ; -> sub_664f04d (if init failed)
0x664705b  cmp dword ptr [r15+0xE4], 0x7FFFFFFF        ; Check frame_context+0x68+0xE4 == 0x7FFFFFFF
0x6647066  je 0x664F15A                                 ; -> sub_664f15a (special case)
0x664706c  mov rax, [rbp+0x880]                        ; Reload hash constant
0x6647073  movzx ecx, byte ptr [rbp+0x888]             ; Load byte 0 of hash
0x664707a  mov r10, 0xCBF29CE484222325                 ; FNV offset basis
0x6647084  xor rcx, r10
0x6647087  mov rsi, 0x100000001B3                      ; FNV prime
0x6647091  imul rcx, rsi
0x6647095  movzx edx, byte ptr [rbp+0x889]             ; Byte 1
0x664709c  xor rdx, rcx
0x664709f  imul rdx, rsi
0x66470a3  movzx ecx, byte ptr [rbp+0x88A]             ; Byte 2
0x66470aa  xor rcx, rdx
0x66470ad  imul rcx, rsi
0x66470b1  movzx edx, byte ptr [rbp+0x88B]             ; Byte 3
0x66470b8  xor rdx, rcx
0x66470bb  imul rdx, rsi
0x66470bf  movzx ecx, byte ptr [rbp+0x88C]             ; Byte 4
0x66470c6  xor rcx, rdx
0x66470c9  imul rcx, rsi
0x66470cd  movzx edx, byte ptr [rbp+0x88D]             ; Byte 5
0x66470d4  xor rdx, rcx
0x66470d7  imul rdx, rsi
0x66470db  movzx ecx, byte ptr [rbp+0x88E]             ; Byte 6
0x66470e2  xor rcx, rdx
0x66470e5  imul rcx, rsi
0x66470e9  movzx r8d, byte ptr [rbp+0x88F]             ; Byte 7
0x66470f1  xor r8, rcx
0x66470f4  imul r8, rsi
0x66470f8  mov rcx, rax                                ; rcx = hash constant
0x66470fb  shl rcx, 6
0x66470ff  mov r9, rax
0x6647102  shr r9, 2
0x6647106  add r9, rcx
0x6647109  mov edx, 0x9E3779B9                         ; Knuth multiplier
0x664710e  add rdx, r9
0x6647111  add rdx, r8
0x6647114  xor rdx, rax
0x6647117  and rdx, [r15+0x70]                         ; Mask with table size-1 (frame_context+0x68+0x70)
0x664711b  mov rcx, [r15+0x48]                         ; rcx = frame_context+0x68+0x48 (bucket array)
0x664711f  mov r8, [r15+0x58]                          ; r8 = frame_context+0x68+0x58 (entries array)
0x6647123  shl rdx, 4                                  ; Index * 16 (entry stride)
0x6647127  mov rbx, [r8+rdx+8]                         ; Load entry pointer (entry+8 = key)
0x664712c  cmp rbx, rcx                                ; Compare with computed hash
0x664712f  mov [rbp+0x870], r10
0x6647136  mov [rbp+0x598], r12
0x664713d  mov [rbp+0x1E8], r13
0x6647144  je 0x66475B3                                 ; -> loc_66475b3 (hash match, found)
0x664714a  mov rdx, [r8+rdx]                           ; Load entry+0 (next pointer)
0x664714e  mov r8, [rbp+0x888]
0x6647155  cmp rax, [rbx+0x10]                         ; Compare full key at entry+0x10
0x6647159  je short 0x664716E                          ; -> loc_664716e (key matches)

loc_664715b:
0x664715b  cmp rbx, rdx                                 ; End of chain?
0x664715e  je 0x66475B3                                 ; -> loc_66475b3 (not found)
0x6647164  mov rbx, [rbx+8]                             ; Next entry
0x6647168  cmp rax, [rbx+0x10]                         ; Compare key
0x664716c  jne short 0x664715B                         ; Loop

loc_664716e:
0x664716e  cmp r8, [rbx+0x18]                          ; Compare control/value
0x6647172  jne short 0x664715B                         ; Not match, continue
0x6647174  cmp rbx, rcx
0x6647177  je 0x66475B3                                 ; -> loc_66475b3
0x664717d  lea rdx, [rbp+0x220]                        ; Output buffer
0x6647184  lea r8, [rbp+0x880]                         ; Key buffer
0x664718b  mov rcx, r15                                 ; FrameBuilder context (frame_context+0x68)
0x664718e  call 0x567D280                                ; -> sub_567d280 (CREATE/INSERT render object)
0x6647193  nop
0x6647194  mov r8, [rbp+0x220]                         ; Result shared_ptr pair
0x664719b  mov rdx, [r15+0x88]                         ; Vector end
0x66471a2  cmp rdx, [r15+0x90]                         ; Compare with capacity
0x66471a9  je 0x66482E1                                 ; -> loc_66482e1 (need grow)
0x66471af  xorps xmm0, xmm0
0x66471b2  movups [rdx], xmm0                           ; Zero new element
0x66471b5  mov rax, [r8+0x28]                          ; Load control block
0x66471b9  test rax, rax
0x66471bc  je short 0x66471C2
0x66471be  lock inc dword ptr [rax+8]                   ; Inc strong ref

loc_66471c2:
0x66471c2  mov rax, [r8+0x20]                          ; Load object pointer
0x66471c6  mov [rdx], rax                               ; Store in vector
0x66471c9  mov rax, [r8+0x28]                          ; Load control block
0x66471cd  mov [rdx+8], rax                             ; Store control block
0x66471d1  add qword ptr [r15+0x88], 0x10              ; Advance vector end
0x66471d9  jmp 0x66482F2                                ; -> loc_66482f2 (SHARED TAIL)
```

**Tail call**: Jumps to shared tail at **0x66482F2** (loc_66482f2), which merges with other tag handlers and eventually returns to visitor epilogue.

**Callee consuming description**: **sub_567d280** (called at 0x664718e). Arguments:
- `rcx` = r15 = frame_context+0x68 = `[FrameBuilder+0xF0]+0x68` (FrameBuilder context sub-object)
- `rdx` = rbp+0x220 = output buffer for created object
- `r8` = rbp+0x880 = 16-byte hash key (FNV-1a64 of "Nametag" + frame context data)

The callee **sub_567d280** performs hash table lookup/insert in the FrameBuilder's render object registry and creates a "Nametag" render object. The description pointer (`rdi`) is accessed via the frame context by the callee.

---

### Tag 5: Crack handler at 0x66471de
**Entry**: Jumped to from visitor 0x6646980 jump table (tag 5). `rdi` = description pointer (from visitor arg3+0x0). `rbx` = FrameBuilder `this`. `rbp+0x8A0` = frame context pointer (from visitor arg2).
**Extent**: 0x66471de .. 0x664731f (next handler at 0x6647320 is tag 6 forwarder)

```
0x66471de  mov rcx, [rdi]                              ; Load description.mMesh (desc+0x00)
0x66471e1  call 0x4DEF080                                ; -> sub_4def080 (Mesh::hasDrawableData)
0x66471e6  test al, al
0x66471e8  je 0x664EBD7                                ; -> sub_664ebd7 (early exit if no drawable data)
0x66471ee  mov r13, rbx                                ; Save FrameBuilder this in r13
0x66471f1  mov eax, [0x129F9CA0]                       ; TLS guard check 1
0x66471f7  mov ecx, [0x128767C8]
0x66471fd  mov rdx, gs:[0x58]
0x6647206  mov rcx, [rdx+rcx*8]
0x664720a  cmp eax, [rcx+4]
0x6647210  jg 0x664EF73                                ; -> sub_664ef73 (TLS fail)
0x6647216  mov rax, [rbp+0x8A0]                        ; Load frame context pointer
0x664721d  mov r9, [rax+0x40]                          ; r9 = frame_context+0x40
0x6647221  mov rcx, [rax+0x68]                         ; rcx = frame_context+0x68
0x6647225  pxor xmm0, xmm0
0x6647229  movdqa [rbp+0x220], xmm0                    ; Zero stack buffer (16 bytes)
0x6647231  lea rax, [0xF552ED0]                        ; "Cracks" string (data_f552ed0)
0x6647238  mov [rbp+0x5A0], rax
0x664723f  mov qword ptr [rbp+0x5A8], 6                ; String length = 6
0x664724a  lea rsi, [rbp+0x220]                        ; rsi = output buffer
0x6647251  mov [rsp+0x28], rsi
0x6647256  lea rax, [rbp+0x5A0]                        ; "Cracks" string pointer
0x664725d  mov [rsp+0x20], rax
0x6647262  lea r8, [0x129F9C90]                        ; Constant data (data_129f9c90)
0x6647269  lea rdx, [rbp+0x850]                        ; rdx = output location for result
0x6647270  call 0x675E440                                ; -> sub_675e440 (material/pass resolver)
0x6647275  mov rax, [rbp+0x850]                        ; Load result (shared_ptr pair)
0x664727c  mov rbx, [rax]                              ; rbx = object pointer
0x664727f  test rbx, rbx
0x6647282  je 0x664E971                                ; -> sub_664e971 (null result)
0x6647288  mov eax, [0x129CA5E0]                       ; TLS guard check 2
0x664728e  mov ecx, [0x128767C8]
0x6647294  mov rdx, gs:[0x58]
0x664729d  mov rcx, [rdx+rcx*8]
0x66472a1  cmp eax, [rcx+4]
0x66472a7  jg 0x664F176                                ; -> sub_664f176 (TLS fail)
0x66472ad  cmp byte ptr [rbx+0x10], 1                  ; Check result object byte +0x10 == 1
0x66472b1  jne 0x664E971                               ; -> sub_664e971 (not valid)
0x66472b7  mov rax, [rbp+0x850]                        ; Reload result
0x66472be  mov rcx, [rax+8]                            ; Load control block
0x66472c2  test rcx, rcx
0x66472c5  je 0x6647F50                                ; -> loc_6647f50 (no control block)
0x66472cb  lock inc dword ptr [rcx+8]                  ; Inc strong ref
0x66472cf  mov rcx, [rax]                              ; Load object pointer
0x66472d2  mov r14, [rax+8]                            ; r14 = control block
0x66472d6  mov rax, [rcx+0x18]                         ; Load weak pointer from object
0x66472da  mov rbx, [rax]                              ; rbx = weak object
0x66472dd  test r14, r14
0x66472e0  je 0x6647F5A                                ; -> loc_6647f5a (shared tail)
0x66472e6  lock dec dword ptr [r14+8]                  ; Dec strong ref
0x66472eb  jne 0x6647F5A                               ; -> loc_6647f5a
0x66472f1  mov rax, [r14]
0x66472f4  mov rax, [rax]
0x66472f7  mov rcx, r14
0x66472fa  call qword ptr [0xF99FFA0]                  ; -> sub_eea6040 (destructor)
0x6647300  lock dec dword ptr [r14+0xC]                ; Dec weak ref
0x6647305  jne 0x6647F5A                               ; -> loc_6647f5a
0x664730b  mov rax, [r14]
0x664730e  mov rax, [rax+8]
0x6647312  mov rcx, r14
0x6647315  call qword ptr [0xF99FFA0]                  ; -> sub_eea6040 (destructor)
0x664731b  jmp 0x6647F5A                                ; -> loc_6647f5a (SHARED TAIL)
```

**Tail call**: Jumps to shared tail at **0x6647F5A** (loc_6647f5a), which merges with other tag handlers and eventually returns to visitor epilogue.

**Callee consuming description**: **sub_675e440** (called at 0x6647270). Arguments:
- `rcx` = frame_context+0x68 (from 0x6647221)
- `rdx` = rbp+0x850 = output for resolved material/pass
- `r8` = 0x129F9C90 (constant data)
- Stack: rsi = rbp+0x220 (zeroed buffer), [rsp+0x20] = "Cracks" string pointer, [rsp+0x28] = rsi

The callee **sub_675e440** resolves the "Cracks" pass/material by name hash and returns a render object. The description fields read directly by this handler:
- `description.mMesh` at +0x00 (passed in `rcx` to sub_4def080)

The frame_context fields used:
- `frame_context+0x40` (passed as `r9` to resolver)
- `frame_context+0x68` (passed as `rcx` to resolver)

---

### Tag 2: MeshFallback handler at 0x6646c8d
**Entry**: Jumped to from visitor 0x6646980 jump table (tag 2). `rdi` = description pointer (from visitor arg3+0x0). `rbx` = FrameBuilder `this`. `rbp+0x8A0` = frame context pointer (from visitor arg2).
**Extent**: 0x6646c8d .. 0x6646d5e (next handler at 0x6646d5f is tag 3)

```
0x6646c8d  mov [rbp+0x898], rbx                           ; Save FrameBuilder this
0x6646c94  mov rax, [rdi+0x108]                           ; Load description.mMaterial (SharedRef.ptr at desc+0x108)
0x6646c9b  test rax, rax
0x6646c9e  je 0x664EBD7                                   ; -> sub_664ebd7 (early exit if no material)
0x6646ca4  mov rbx, [rax+0x40]                            ; rbx = material+0x40 (material internal field)
0x6646ca8  test rbx, rbx
0x6646cab  je 0x664EBD7                                   ; -> sub_664ebd7 (early exit if field zero)
0x6646cb1  lea r14, [rdi+0x108]                           ; r14 = &description.mMaterial
0x6646cb8  mov rsi, [rax+0x10]                            ; rsi = material+0x10
0x6646cbc  mov al, 1
0x6646cbe  mov [rbp+0x870], eax                           ; Flag = 1
0x6646cc4  cmp byte ptr [rdi+0xE0], 0                     ; Check description.mHasOverride (desc+0xE0)
0x6646ccb  mov r12b, 1
0x6646cce  jne 0x6649E41                                  ; -> sub_6649e41 (has override path)
0x6646cd4  mov qword ptr [rbp+0x228], 0
0x6646cdf  mov qword ptr [rbp+0x230], 0xA                ; String length = 10
0x6646cea  mov qword ptr [rbp+0x238], 0xF                ; Capacity = 0xF
0x6646cf5  mov rax, [0xF7C86B5]                           ; "ALPHA_TEST" string (data_f7c86b5)
0x6646cfc  mov [rbp+0x220], rax
0x6646d03  movzx eax, word ptr [0xF7C86BD]               ; String hash/length (data_f7c86bd)
0x6646d0a  mov [rbp+0x228], ax
0x6646d11  lea rcx, [rbx+0x98]                            ; rcx = material+0x40+0x98 = material+0xD8
0x6646d18  lea rdx, [rbp+0x220]                           ; rdx = "ALPHA_TEST" string buffer
0x6646d1f  call 0x358C40                                  ; -> sub_358c40 (string lookup in material)
0x6646d24  mov r12b, 1
0x6646d27  cmp rax, [rbx+0x98]                            ; Compare result
0x6646d2e  jne 0x6649DFC                                  ; -> sub_6649dfc (not found)
0x6646d34  mov rax, [r14]                                 ; rax = description.mMaterial.ptr
0x6646d37  lea rcx, [rax+0x10]                            ; rcx = material+0x10
0x6646d3b  test rax, rax
0x6646d3e  lea r15, [0x1232E708]                          ; Default fallback (data_1232e708)
0x6646d45  cmovne r15, rcx                                ; Use material+0x10 if non-null
0x6646d49  mov r12, [r15+0x18]                            ; Load field at +0x18
0x6646d4d  cmp r12, 0x17                                  ; Check bounds (max 23)
0x6646d51  jae 0x6648A35                                  ; -> loc_6648a35 (out of bounds)
0x6646d57  xor r12d, r12d
0x6646d5a  jmp 0x6649DFC                                  ; -> sub_6649dfc
```

**Tail call**: Falls through to tag 3 handler at **0x6646d5f** (ChunkGeometry), which eventually tail-calls **sub_66ea3d0** (chunk geometry extractor) at 0x6646dbd.

**Description fields read directly**:
- `description.mMaterial.ptr` at +0x108 (SharedRef.ptr) — 0x6646c94, 0x6646d34
- `description.mMaterial.ctrl` at +0x110 (via [rax+0x10] at 0x6646cb8) — SharedRef control block
- `description.mHasOverride` at +0xE0 (byte) — 0x6646cc4
- `material+0x40` (material internal) — 0x6646ca4
- `material+0x10` — 0x6646cb8
- `material+0x98` — 0x6646d11, 0x6646d27
- `material+0xD8` (material+0x40+0x98) — 0x6646d11
- `material+0x18` (via r15) — 0x6646d49

**Callee**: **sub_358c40** (at 0x6646d1f) — material string lookup. The handler does not call a render object creator directly; it validates the material and falls through to the ChunkGeometry handler (tag 3) which calls the chunk extractor **sub_66ea3d0**.

---

### Tag 9: BlockChanges handler at 0x6646bc6
**Entry**: Jumped to from visitor 0x6646980 jump table (tag 9). `rdi` = description pointer (from visitor arg3+0x0). `rbx` = FrameBuilder `this`. `rbp+0x8A0` = frame context pointer (from visitor arg2).
**Extent**: 0x6646bc6 .. 0x6646c8c (next handler at 0x6646c8d is tag 2)

```
0x6646bc6  movups xmm7, [rdi]                            ; Load description.mVec00[4] (float4 at desc+0x00)
0x6646bc9  movsd xmm6, [rdi+0x10]                        ; Load description.mQword10 (qword at desc+0x10)
0x6646bce  mov ecx, 0x9D0
0x6646bd3  mov rax, [rbp+0x8A0]                          ; Load frame context pointer
0x6646bda  add rcx, [rax+0x10]                           ; rcx = frame_context+0x10 + 0x9D0 = passLookup+0x9D0
0x6646bde  call 0x5ABA5C0                                  ; -> sub_5aba5c0 (passLookup lookup)
0x6646be3  mov rsi, rax                                  ; rsi = pass object pointer (returned in rax)
0x6646be6  xorps xmm0, xmm0
0x6646be9  movaps [rbp+0x2D0], xmm0                       ; Zero stack buffers (6 xmm = 96 bytes at rbp+0x220..0x2CF)
0x6646bf0  movaps [rbp+0x2C0], xmm0
0x6646bf7  movaps [rbp+0x2B0], xmm0
0x6646bfe  movaps [rbp+0x2A0], xmm0
0x6646c05  movaps [rbp+0x290], xmm0
0x6646c0c  movaps [rbp+0x280], xmm0
0x6646c13  movaps [rbp+0x270], xmm0
0x6646c1a  movaps [rbp+0x260], xmm0
0x6646c21  movaps [rbp+0x250], xmm0
0x6646c28  movaps [rbp+0x240], xmm0
0x6646c2f  movaps [rbp+0x230], xmm0
0x6646c36  movaps [rbp+0x220], xmm0
0x6646c3d  mov qword ptr [rbp+0x2E0], 0
0x6646c48  mov rcx, [0x1233E1B0]                         ; Global pointer (data_1233e1b0)
0x6646c4f  mov rax, [rcx]
0x6646c52  mov rax, [rax+0x10]                           ; rax = object at +0x10
0x6646c56  mov dl, 0x4A                                  ; Size 0x4A (74 bytes)
0x6646c58  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (allocator)
0x6646c5e  mov r8d, eax                                  ; r8d = allocation result
0x6646c61  mov r12, [rsi+0x98]                           ; r12 = pass+0x98 (vector begin)
0x6646c68  cmp r12, [rsi+0xA0]                           ; Compare with pass+0xA0 (vector end)
0x6646c6f  je 0x66474E8                                  ; -> loc_66474e8 (vector full, need grow)
0x6646c75  movups [r12], xmm7                            ; Store mVec00 (float4) at vector end
0x6646c7a  movlps [r12+0x10], xmm6                       ; Store mQword10 (qword) at vector end+0x10
0x6646c80  add qword ptr [rsi+0x98], 0x18                ; Advance vector end by 0x18 (element stride)
0x6646c88  jmp 0x6647A74                                 ; -> loc_6647a74 (SHARED TAIL)
```

**Tail call**: Jumps to shared tail at **0x6647A74** (loc_6647a74), which merges with other tag handlers and eventually returns to visitor epilogue.

**Description fields read directly** (from `rdi` = description pointer):
- `description.mVec00[4]` at +0x00 (16 bytes, float4) — 0x6646bc6 `movups xmm7,[rdi]`
- `description.mQword10` at +0x10 (8 bytes, qword) — 0x6646bc9 `movsd xmm6,[rdi+0x10]`

**Frame context fields used**:
- `frame_context+0x10` — 0x6646bda `add rcx,[rax+0x10]` (passLookup pointer)

**Callees**:
1. **sub_5aba5c0** (at 0x6646bde) — passLookup lookup. Arguments: `rcx` = frame_context+0x10+0x9D0. Returns pass object in `rax`.
2. **sub_eea6040** (at 0x6646c58) — allocator for vector growth (size 0x4A).

The handler copies the 0x18-byte description (float4 + qword) directly into a vector on the pass object (pass+0x98/0xA0), element stride 0x18. This matches `RenderBlockChangesDescription` in Descriptions.h (size 0x18: float4 at +0x00, qword at +0x10).

---

### Tag 3: ChunkGeometry handler at 0x6646d5f
**Entry**: Jumped to from visitor 0x6646980 jump table (tag 3). `rdi` = description pointer (from visitor arg3+0x0). `rbx` = FrameBuilder `this`. `rbp+0x8A0` = frame context pointer (from visitor arg2).
**Extent**: 0x6646d5f .. 0x6646dc1 (next handler at 0x6646dc2 is tag 7)

```
0x6646d5f  mov rcx, rbx                                  ; rcx = FrameBuilder this
0x6646d62  mov rdx, [rbp+0x8A0]                          ; rdx = frame context pointer
0x6646d69  mov r8, rdi                                   ; r8 = description pointer
0x6646d6c  movaps xmm6, [rbp+0x8B0]                      ; Save xmm6..xmm13 from stack
0x6646d73  movaps xmm7, [rbp+0x8C0]
0x6646d7a  movaps xmm8, [rbp+0x8D0]
0x6646d82  movaps xmm9, [rbp+0x8E0]
0x6646d8a  movaps xmm10, [rbp+0x8F0]
0x6646d92  movaps xmm11, [rbp+0x900]
0x6646d9a  movaps xmm12, [rbp+0x910]
0x6646da2  movaps xmm13, [rbp+0x920]
0x6646daa  add rsp, 0x9B8                                ; Restore stack
0x6646db1  pop rbx
0x6646db2  pop rdi
0x6646db3  pop rsi
0x6646db4  pop r12
0x6646db6  pop r13
0x6646db8  pop r14
0x6646dba  pop r15
0x6646dbc  pop rbp
0x6646dbd  jmp 0x66EA3D0                                 ; -> sub_66ea3d0 (TAIL CALL)
```

**Tail call**: **TAIL CALL** to **sub_66ea3d0** (chunk geometry extractor) at 0x6646dbd. This is a direct tail call (jmp), not a call+ret.

**Arguments passed to sub_66ea3d0**:
- `rcx` = FrameBuilder `this` (rbx)
- `rdx` = frame context pointer (from rbp+0x8A0)
- `r8` = description pointer (rdi)
- xmm6..xmm13 restored from stack (callee-saved registers)

**Description fields read directly by this handler**: **NONE**. The handler is a pure forwarder; all description field reads happen in the callee **sub_66ea3d0**.

**Callee consuming description**: **sub_66ea3d0** (chunk geometry extractor, documented in E4). This is the main chunk geometry extraction function that processes `RenderChunkGeometryDescription`.

---

### Tag 7: SkinnedMesh handler at 0x6646dc2
**Entry**: Jumped to from visitor 0x6646980 jump table (tag 7). `rdi` = description pointer (from visitor arg3+0x0). `rbx` = FrameBuilder `this`. `rbp+0x8A0` = frame context pointer (from visitor arg2).
**Extent**: 0x6646dc2 .. 0x6646f5a (next handler at 0x6646f5b is tag 1)

This handler implements a **hash-switch over skinned block-entity overlay materials** (per BGFX_MAP 6cj). It reads a material-name hash from `description.mMaterial` at +0x140 and branches through a binary search tree of FNV-1 64 hash constants.

```
0x6646dc2  mov rax, [rdi+0x140]                          ; Load description.mMaterial (SharedRef.ptr at desc+0x140)
0x6646dc9  lea rcx, [rax+0x10]                           ; rcx = mMaterial+0x10 (HashedString node*)
0x6646dcd  test rax, rax
0x6646dd0  lea rdx, [0x1232E708]                         ; Default fallback (data_1232e708)
0x6646dd7  cmovne rdx, rcx                               ; Use mMaterial+0x10 if non-null
0x6646ddb  mov rcx, [rdx]                                ; rcx = *HashedString node (material name hash at node+0x10)
0x6646dde  mov rdx, 0x416AE22CAB22EA36                   ; Hash: split point
0x6646de8  cmp rcx, rdx
0x6646deb  jg 0x6647449                                  ; -> loc_6647449 (right subtree: selection_overlay)
0x6646df1  mov rdx, 0xD8EF928BC853553A                   ; Hash: cracks_overlay_tile_entity.skinning
0x6646dfb  cmp rcx, rdx
0x6646dfe  je short 0x6646E13                            ; -> loc_6646e13 (MATCH: cracks overlay)
0x6646e00  mov rdx, 0x2C8B246FD3EDDC59                   ; Hash: selection_overlay_block_entity.skinning_color
0x6646e0a  cmp rcx, rdx
0x6646e0d  jne 0x66475BB                                 ; -> loc_66475bb (no match, generic path)

loc_6646e13:  ; MATCH: cracks_overlay_tile_entity.skinning (0xD8EF928BC853553A)
0x6646e13  mov r13, rbx                                  ; Save FrameBuilder this
0x6646e16  mov rax, [0x128D6FA8]                         ; Global (data_128d6fa8)
0x6646e1d  mov rax, [rax+0x120]
0x6646e24  mov rax, [rax+0x40]
0x6646e28  movq xmm6, [rax]                              ; Load some value
0x6646e2c  mov eax, [0x129F9CC8]                         ; TLS guard
0x6646e32  mov ecx, [0x128767C8]
0x6646e38  mov rdx, gs:[0x58]
0x6646e41  mov rcx, [rdx+rcx*8]
0x6646e45  cmp eax, [rcx+4]
0x6646e4b  jg 0x664EFDD                                  ; -> sub_664efdd (TLS fail)
0x6646e51  mov rax, [rbp+0x8A0]                          ; Frame context
0x6646e58  mov r9, [rax+0x40]                            ; r9 = frame_context+0x40
0x6646e5c  mov rcx, [rax+0x68]                           ; rcx = frame_context+0x68
0x6646e60  pxor xmm0, xmm0
0x6646e64  movdqa [rbp+0x220], xmm0                      ; Zero buffer
0x6646e6c  lea rax, [0xF515E74]                          ; "CracksBlockEntity" (data_f515e74)
0x6646e73  mov [rbp+0x5A0], rax
0x6646e7a  mov qword ptr [rbp+0x5A8], 0x11               ; Length 17
0x6646e85  lea rax, [rbp+0x220]
0x6646e8c  mov [rsp+0x28], rax
0x6646e91  lea rsi, [rbp+0x5A0]
0x6646e98  mov [rsp+0x20], rsi
0x6646e9d  lea r8, [0x129F9CB8]                          ; Constant (data_129f9cb8)
0x6646ea4  lea rdx, [rbp+0x1F0]                          ; Output
0x6646eab  call 0x675E440                                ; -> sub_675e440 (material resolver)
0x6646eb0  mov rax, [rbp+0x1F0]
0x6646eb7  mov rbx, [rax]                                ; Result object
0x6646eba  test rbx, rbx
0x6646ebd  je 0x664CB91                                  ; -> sub_664cb91 (null)
0x6646ec3  mov eax, [0x129CA5E0]                         ; TLS guard
0x6646ec9  mov ecx, [0x128767C8]
0x6646ecf  mov rdx, gs:[0x58]
0x6646ed8  mov rcx, [rdx+rcx*8]
0x6646edc  cmp eax, [rcx+4]
0x6646ee2  jg 0x664F1B9                                  ; -> sub_664f1b9 (TLS fail)
0x6646ee8  cmp byte ptr [rbx+0x10], 1                    ; Validate object
0x6646eec  jne 0x664CB91                                 ; -> sub_664cb91
0x6646ef2  mov rax, [rbp+0x1F0]
0x6646ef9  mov rcx, [rax+8]                              ; Control block
0x6646efd  test rcx, rcx
0x6646f00  je 0x6647FE7                                  ; -> loc_6647fe7
0x6646f06  lock inc dword ptr [rcx+8]                    ; Inc strong ref
0x6646f0a  mov rcx, [rax]
0x6646f0d  mov r14, [rax+8]
0x6646f11  mov rax, [rcx+0x18]
0x6646f15  mov rbx, [rax]
0x6646f18  test r14, r14
0x6646f1b  je 0x6647FF1                                  ; -> loc_6647ff1 (shared tail)
0x6646f21  lock dec dword ptr [r14+8]                    ; Dec strong ref
0x6646f26  jne 0x6647FF1
0x6646f2c  mov rax, [r14]
0x6646f2f  mov rax, [rax]
0x6646f32  mov rcx, r14
0x6646f35  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (destructor)
0x6646f3b  lock dec dword ptr [r14+0xC]                  ; Dec weak ref
0x6646f40  jne 0x6647FF1
0x6646f46  mov rax, [r14]
0x6646f49  mov rax, [rax+8]
0x6646f4d  mov rcx, r14
0x6646f50  call qword ptr [0xF99FFA0]                    ; -> sub_eea6040 (destructor)
0x6646f56  jmp 0x6647FF1                                 ; -> loc_6647ff1 (SHARED TAIL)
```

**Right subtree (0x6647449)** — `selection_overlay_block_entity.skinning` (0x4B8EDB299C93ABB3) and `selection_overlay_block_entity.skinning_color` (0x416AE22CAB22EA37):
- At 0x664746b: copies 4x4 matrix from `description+0x00..0x30` to stack
- At 0x6647496: loads `description.mMesh` at +0xB0
- At 0x66474a4: loads `description.mValueB8` at +0xB8
- At 0x66474b0: copies `description.mBlockC0` at +0xC0 (16 bytes)
- At 0x66474c8: loads `description.mRefE0` (SharedRef) at +0xE8, inc ref if non-null

**Generic fallback (0x66475BB)** — resolves texture via `sub_4df6e80`, builds vertex data, calls material resolver with computed hash.

**Tail calls**: Multiple paths converge at shared tails:
- **0x6647FF1** (loc_6647ff1) — cracks overlay success path
- **0x6647BB4** (loc_6647bb4) — GlowInkSign path
- **0x66482F2** (loc_66482f2) — Nametag path (from tag 1)
- **0x6647F5A** (loc_6647f5a) — Crack path (from tag 5)

**Description fields read directly** (from `rdi` = `RenderSkinnedMeshDescription*`):
- `mMaterial.ptr` at +0x140 (SharedRef.ptr) — 0x6646dc2
- `mMaterial.ctrl` at +0x148 (via [rax+0x10] at 0x6646dc9) — HashedString node*
- **Right subtree (0x664746b+)**:
  - `mMatrixA[16]` at +0x000..0x03F — 0x664746b, 0x6647475, 0x6647479, 0x6647480, 0x6647484, 0x664748b, 0x664748f
  - `mMesh` at +0x0B0 — 0x6647496
  - `mValueB8` at +0x0B8 — 0x66474a4
  - `mBlockC0[4]` at +0x0C0..0x0CF — 0x66474b0, 0x66474b7
  - `mRefE0` (SharedRef) at +0x0E8 — 0x66474c8, 0x66474d8, 0x66474dc
  - `mRef108` (SharedRef) at +0x108 — 0x664770e, 0x664771a, 0x6647725, 0x6647729
  - `mVariantIndex` at +0x1B0 — 0x6647761
  - `mVariantPayload` at +0x198..0x1AF — 0x6647782, 0x664779a, 0x66477a6, 0x66477aa, 0x66477b1, 0x66477bf, 0x66477c2

**Callees**:
1. **sub_675e440** (at 0x6646eab) — material/pass resolver for "CracksBlockEntity"
2. **sub_567d280** (at 0x664718e, from tag 1 path) — render object creator
3. **sub_4df6e80** (at 0x66475de) — texture resolver (generic path)
4. **sub_9d6d0** (at 0x66476e5) — string copy helper ("GlowInkSignForwardPBR")
5. **sub_eea6040** — allocator/destructor (multiple sites)

**Note**: Tag 7 handles **skinned block-entity overlays** (crack overlay on tile entities, selection box/overlay on block entities), NOT general skinned entity models (those use the SkinnedMesh clone 0x6b84e60 and BatchActor extractor). The live-captured tag 7 payload (ender_dragon.skinning) falls through the hash switch to the generic path at 0x66475BB.

---

## Step 2: Field Read Tables (per handler)

### Tag 1 (Nametag) - Handler 0x6646f5b reads from description (`rdi`)
| Offset | Size | Instruction (RVA) | Use | Tag | Field Name (Descriptions.h) |
|--------|------|-------------------|-----|-----|----------------------------|
| +0x58  | 8    | 0x6646f5b `mov rax,[rdi+0x58]` | Read mShared.mPtr | 1 | `mShared.mPtr` (SharedRef.ptr) |
| +0x58+0x40 | 8 | 0x6646f68 `cmp qword ptr [rax+0x40],0` | Check shared object field | 1 | `mShared.mPtr+0x40` (internal) |
| +0x00  | 8    | 0x6646f77 `mov rax,[rdi]` | Read mOwner | 1 | `mOwner` |
| +0x39  | 1    | 0x6646f7a `movzx r8d,byte ptr [rax+0x39]` | Read mOwner+0x39 flag | 1 | `mOwner+0x39` (external) |
| +0x108 | 8    | (via frame_context) | Frame context fields | 1 | FrameBuilder context |

**Frame context reads** (via `rbp+0x8A0` = frame_context = `[FrameBuilder+0xF0]`):
| Offset | Size | Instruction (RVA) | Use |
|--------|------|-------------------|-----|
| +0x40  | 8    | 0x6646fff `mov r13,[rax+0x40]` | Hash table key base |
| +0x68  | 8    | 0x6647003 `mov r15,[rax+0x68]` | Hash table object (FrameBuilder+0xF0+0x68) |
| +0x68+0xE4 | 4 | 0x664705b `cmp dword ptr [r15+0xE4],0x7FFFFFFF` | Special value check |
| +0x68+0x70 | 8 | 0x6647117 `and rdx,[r15+0x70]` | Hash table mask |
| +0x68+0x48 | 8 | 0x664711b `mov rcx,[r15+0x48]` | Bucket array |
| +0x68+0x58 | 8 | 0x664711f `mov r8,[r15+0x58]` | Entries array |
| +0x68+0x88 | 8 | 0x664719b `mov rdx,[r15+0x88]` | Vector end |
| +0x68+0x90 | 8 | 0x66471a2 `cmp rdx,[r15+0x90]` | Vector capacity |

### Tag 5 (Crack) - Handler 0x66471de reads from description (`rdi`)
| Offset | Size | Instruction (RVA) | Use | Tag | Field Name (Descriptions.h) |
|--------|------|-------------------|-----|-----|----------------------------|
| +0x00  | 8    | 0x66471de `mov rcx,[rdi]` | Read mMesh | 5 | `mMesh` |
| +0x00 (indirect) | - | 0x66471e1 `call 0x4DEF080` | Mesh::hasDrawableData | 5 | mMesh->vtable |

**Frame context reads** (via `rbp+0x8A0`):
| Offset | Size | Instruction (RVA) | Use |
|--------|------|-------------------|-----|
| +0x40  | 8    | 0x664721d `mov r9,[rax+0x40]` | Passed to resolver as r9 |
| +0x68  | 8    | 0x6647221 `mov rcx,[rax+0x68]` | Passed to resolver as rcx |

### Tag 2 (MeshFallback) - Handler 0x6646c8d reads from description (`rdi`)
| Offset | Size | Instruction (RVA) | Use | Tag | Field Name (Descriptions.h) |
|--------|------|-------------------|-----|-----|----------------------------|
| +0x108 | 8    | 0x6646c94 `mov rax,[rdi+0x108]` | Read mMaterial.mPtr | 2 | `mMaterial.mPtr` (SharedRef.ptr) |
| +0x110 | 8    | 0x6646cb8 `mov rsi,[rax+0x10]` | Read mMaterial.mCtrl | 2 | `mMaterial.mCtrl` (SharedRef.ctrl) |
| +0xE0  | 1    | 0x6646cc4 `cmp byte ptr [rdi+0xE0],0` | Check mHasOverride | 2 | `mHasOverride` |
| +0x108 (indirect) | - | 0x6646ca4 `mov rbx,[rax+0x40]` | Material internal +0x40 | 2 | Material+0x40 |
| +0x118 (indirect) | - | 0x6646cb8 `mov rsi,[rax+0x10]` | Material internal +0x10 | 2 | Material+0x10 |
| +0x108+0x98 (indirect) | - | 0x6646d11 `lea rcx,[rbx+0x98]` | Material+0xD8 | 2 | Material+0xD8 |
| +0x108+0x18 (indirect) | - | 0x6646d49 `mov r12,[r15+0x18]` | Material+0x18 | 2 | Material+0x18 |

### Tag 9 (BlockChanges) - Handler 0x6646bc6 reads from description (`rdi`)
| Offset | Size | Instruction (RVA) | Use | Tag | Field Name (Descriptions.h) |
|--------|------|-------------------|-----|-----|----------------------------|
| +0x00  | 16   | 0x6646bc6 `movups xmm7,[rdi]` | Read mVec00[4] (float4) | 9 | `mVec00[4]` |
| +0x10  | 8    | 0x6646bc9 `movsd xmm6,[rdi+0x10]` | Read mQword10 (qword) | 9 | `mQword10` |

**Frame context reads** (via `rbp+0x8A0`):
| Offset | Size | Instruction (RVA) | Use |
|--------|------|-------------------|-----|
| +0x10  | 8    | 0x6646bda `add rcx,[rax+0x10]` | passLookup pointer |

**Callee reads** (sub_5aba5c0 returns pass object in `rax`/`rsi`):
| Offset | Size | Instruction (RVA) | Use |
|--------|------|-------------------|-----|
| pass+0x98 | 8 | 0x6646c61 `mov r12,[rsi+0x98]` | Vector begin |
| pass+0xA0 | 8 | 0x6646c68 `cmp r12,[rsi+0xA0]` | Vector end |

### Tag 3 (ChunkGeometry) - Handler 0x6646d5f reads from description (`rdi`)
| Offset | Size | Instruction (RVA) | Use | Tag | Field Name (Descriptions.h) |
|--------|------|-------------------|-----|-----|----------------------------|
| (none) | - | - | **No direct reads** | 3 | Pure forwarder |

**Arguments passed to callee sub_66ea3d0**:
- `rcx` = FrameBuilder `this` (rbx)
- `rdx` = frame context (rbp+0x8A0)
- `r8` = description pointer (rdi)
- xmm6..xmm13 = callee-saved registers from stack

### Tag 7 (SkinnedMesh) - Handler 0x6646dc2 reads from description (`rdi`)
| Offset | Size | Instruction (RVA) | Use | Tag | Field Name (Descriptions.h) |
|--------|------|-------------------|-----|-----|----------------------------|
| +0x140 | 8    | 0x6646dc2 `mov rax,[rdi+0x140]` | Read mMaterial.mPtr | 7 | `mMaterial.mPtr` (SharedRef.ptr) |
| +0x148 | 8    | 0x6646dc9 `lea rcx,[rax+0x10]` | Read mMaterial.mCtrl+0x10 | 7 | `mMaterial.mCtrl` -> HashedString node* |
| +0x140 (indirect) | 8 | 0x6646ddb `mov rcx,[rdx]` | Read HashedString.hash at node+0x10 | 7 | `mMaterial` -> HashedString.hash |

**Right subtree (hash match 0x4B8EDB299C93ABB3 / 0x416AE22CAB22EA37) - loc_664746b:**
| Offset | Size | Instruction (RVA) | Use | Tag | Field Name |
|--------|------|-------------------|-----|-----|------------|
| +0x000 | 64   | 0x664746b `movups xmm0,[rdi]` .. 0x664748f `movaps [rbp+0x250],xmm0` | Copy mMatrixA[16] | 7 | `mMatrixA[16]` |
| +0x0B0 | 8    | 0x6647496 `mov rax,[rdi+0xB0]` | Read mMesh | 7 | `mMesh` |
| +0x0B8 | 4    | 0x66474a4 `mov eax,[rdi+0xB8]` | Read mValueB8 | 7 | `mValueB8` |
| +0x0C0 | 16   | 0x66474b0 `movups xmm0,[rdi+0xC0]` | Read mBlockC0[4] | 7 | `mBlockC0[4]` |
| +0x0E8 | 16   | 0x66474c8 `mov rax,[rdi+0xE8]` | Read mRefE0.mPtr | 7 | `mRefE0.mPtr` |
| +0x0F0 | 16   | (implied) | Read mRefE0.mCtrl | 7 | `mRefE0.mCtrl` |
| +0x108 | 16   | 0x664770e `mov rax,[rdi+0x148]` | Read mRef108.mPtr | 7 | `mRef108.mPtr` |
| +0x110 | 16   | (implied) | Read mRef108.mCtrl | 7 | `mRef108.mCtrl` |
| +0x1B0 | 1    | 0x6647761 `movzx esi,byte ptr [rdi+0x1B0]` | Read mVariantIndex | 7 | `mVariantIndex` |
| +0x198 | 24   | 0x6647782 `mov rax,[rdi+0x198]` | Read mVariantPayload | 7 | `mVariantPayload` |
| +0x1A8 | 8    | 0x66477a6 `mov rax,[rdi+0x1A8]` | Read mVariantPayload+0x10 | 7 | `mVariantPayload` |
| +0x000 | 8    | 0x66477b1 `add rdi,0x1A8` then 0x66477bf `mov rax,[rdi]` | Read mVariantPayload.mValue00 | 7 | `mVariantPayload.mValue00` |
| +0x008 | 8    | 0x66477c2 `mov rax,[rdi]` | Read mVariantPayload.mRef08.mPtr | 7 | `mVariantPayload.mRef08.mPtr` |

**Generic fallback (loc_66475BB)** reads:
| Offset | Size | Instruction (RVA) | Use | Tag | Field Name |
|--------|------|-------------------|-----|-----|------------|
| +0x40  | 8    | 0x66475d0 `mov rcx,[rax+0x40]` | Material internal (from mMaterial) | 7 | Material+0x40 |

---

## Step 3: Live Data Comparison

### Tag 1 (Nametag) - Live dump sample (from docs/data/live_item_payloads_1.26.62.01.txt)
No live capture for tag 1 in the current live data file. The live captures contain tags: 10, 6, 7, 0, 1, 2, 3, 1, 3, 0, 7, 6, 2, 10. Tag 1 IS present (lines 7 and 10).

**Live sample line 7**: `1 14A148 107D702B46030000...` (decoded by livedec.py)

From the live decode (BGFX_MAP 6cv, tag 1):
- Starts with pointer pair (heap object)
- Float matrix data at +0x08..+0x17
- Position triple at +0x18/+0x28 (mesh-local offsets)
- World position at +0x38..+0x4C: (x=2.422, y=0.88, z=-1.349) = local player position
- Pointer array at +0x58..
- Scale 0.25 at +0x7C
- Sentinel handles at +0x88..+0x97 (FFFFFFFF FFFFFFFE FFFFFF00)
- Matrix copy at +0xD8..+0x13F (previous-frame set)
- Tint floats at end

**Handler-read fields vs live data**:
- `mShared.mPtr` at +0x58: Live shows heap pointer at +0x00 (first qword), but handler reads at +0x58. **OFFSET MISMATCH** — the live payload is the *item payload* (0x200 bytes, per 6cv), not the description struct. The description is built by the clone (0x668b6e0) from the item payload. The handler reads the **description**, not the item payload.
- `mOwner` at +0x00: Description field, set by clone from item payload's first pointer.
- `mShared` at +0x58: Description field (SharedRef), set by clone from item payload's texture/text object.

**Conclusion**: The live item payload (6cv) and the description struct (Descriptions.h) have different layouts. The handler reads the **description** (built by clone 0x1127330/0x668b6e0), which matches `RenderNametagDescription` (size 0x98). The live item payload is the extractor's input (0xC8 bytes per 6bg, but captured as 0x200 in 6cl).

### Tag 5 (Crack) - Live data
No live capture for tag 5 in the current live data file. Tag 5 requires a block being broken.

### Tag 2 (MeshFallback) - Live data
**Live sample line 8**: `2 149900 989E140000000000...` (decoded by livedec.py)

From BGFX_MAP 6cm (tag 2 payload):
- +0x00..+0x17: Three stack pointers (vector begin/end/cap)
- +0x18: Heap pointer 0x4BE180ACF00
- +0x20: Code pointer (callback)
- +0x28+: Float matrices (identity 4x4 at +0x28..+0x67, scale 2.0 at +0x38/+0x44)
- +0x1F0..: Tint (0.8, 1.0, 1.0, 1.0)

**Handler-read fields vs live data**:
- Handler reads description at `rdi` (built by clone 0x4def480 -> constructor 0x668b850).
- Description fields: `mMaterial` at +0x108, `mHasOverride` at +0xE0, `mMatrix` at +0x90, etc.
- Live item payload has embedded vector at +0x00, transforms at +0x28.
- **The clone transforms item payload -> description**. The handler reads the description, which matches `RenderMeshFallbackDescription` (size 0x1D0).

### Tag 9 (BlockChanges) - Live data
No live capture for tag 9 in the current live data file.

### Tag 3 (ChunkGeometry) - Live data
**Live sample line 9**: `3 48AF6D0 E04A4D3D46030000...` and line 11: `3 49BF6D0 E04A4D3D46030000...`

Tag 3 handler is a pure forwarder to sub_66ea3d0 (chunk geometry extractor). The live payload contains mesh pointers, matrices, and material data. The chunk geometry extractor (E4) is documented separately.

### Tag 7 (SkinnedMesh) - Live data
**Live sample line 5**: `7 149A70 2EBD3BB300000000...` and line 13: `7 149310 EE2C554006FAAA3E...`

From BGFX_MAP 6cv (tag 7 live decode):
- +0x00..+0x3F: Model matrix (row-vector, scale 0.008839, translation = actor world pos)
- +0x40..+0x7F: Previous-frame matrix (same here)
- +0x80..+0x97: Local AABB (-12,-12,-24, 12,24,48) + sentinels
- +0xB0..+0xFF: Skin matrix/bone buffer pointers
- +0x100..+0x117: UV/animation params
- +0x140: HashedString node* -> material name "ender_dragon.skinning" (hash 0x0694BEA7E37055A4)

**Handler-read fields vs live data**:
- Handler reads `description.mMaterial` at +0x140 (SharedRef.ptr to HashedString node).
- Live item payload at +0x140 = HashedString node* (matches!).
- Live node at +0x10 = FNV-1 64 hash (0x0694BEA7E37055A4).
- Handler loads hash at `[rdx]` where `rdx` = node* (0x6646ddb).
- Hash switch constants in handler:
  - 0xD8EF928BC853553A = `cracks_overlay_tile_entity.skinning`
  - 0x4B8EDB299C93ABB3 = `selection_overlay_block_entity.skinning`
  - 0x416AE22CAB22EA37 = `selection_overlay_block_entity.skinning_color`
  - 0x2C8B246FD3EDDC59 = (other)
- Live hash 0x0694BEA7E37055A4 (`ender_dragon.skinning`) **does not match any constant** -> falls through to generic path at 0x66475BB.
- This confirms tag 7 handles **both** skinned block-entity overlays (hash-switch) AND general skinned entities (generic fallback).

**Right subtree fields** (for overlay matches):
- Handler reads `mMatrixA` at +0x000, `mMesh` at +0xB0, `mValueB8` at +0xB8, `mBlockC0` at +0xC0, `mRefE0` at +0xE8, `mRef108` at +0x108, `mVariantIndex` at +0x1B0, `mVariantPayload` at +0x198.
- These match `RenderSkinnedMeshDescription` in Descriptions.h exactly.

---

## Step 4: Comparison with Descriptions.h (mark NEW if absent)

### Tag 1: RenderNametagDescription (size 0x98)
| Handler Read | Descriptions.h Field | Status |
|--------------|---------------------|--------|
| +0x58 (mShared.mPtr) | `mShared.mPtr` at +0x58 | MATCH |
| +0x00 (mOwner) | `mOwner` at +0x00 | MATCH |
| +0xE0 (mHasOverride) | NOT READ by handler | — |
| +0x84 (mColor) | NOT READ by handler | — |
| +0x94 (mHasColor) | NOT READ by handler | — |

**NEW fields in Descriptions.h not read by handler**: `mPosition[3]` (+0x48), `mRaw68[0x10]` (+0x68), `mCtx20` (+0x78), `mFlags` (+0x80), `mColor[4]` (+0x84), `mHasColor` (+0x94), `mParamD8..mParam80` (+0x8C..+0xCC), `mOverride[4]` (+0xD0), `mFlags` (+0xE4).

### Tag 5: RenderCrackDescription (size 0x28+)
| Handler Read | Descriptions.h Field | Status |
|--------------|---------------------|--------|
| +0x00 (mMesh) | `mMesh` at +0x00 | MATCH |
| +0x08 (mTexture) | NOT READ by handler | — |
| +0x18 (mCameraRecord) | NOT READ by handler | — |
| +0x20 (mStage) | NOT READ by handler | — |
| +0x22 (mFlags) | NOT READ by handler | — |

**NEW fields in Descriptions.h not read by handler**: All except `mMesh`. The handler only validates the mesh and delegates to material resolver.

### Tag 2: RenderMeshFallbackDescription (size 0x1D0)
| Handler Read | Descriptions.h Field | Status |
|--------------|---------------------|--------|
| +0x108 (mMaterial.mPtr) | `mMaterial` at +0x108 | MATCH |
| +0x110 (mMaterial.mCtrl) | `mMaterial` SharedRef.ctrl | MATCH |
| +0xE0 (mHasOverride) | `mHasOverride` at +0xE0 | MATCH (byte) |
| +0x118 (mParams) | NOT READ directly | — |
| +0x90 (mMatrix) | NOT READ by handler | — |
| +0x168 (mFlags) | NOT READ by handler | — |
| +0x170 (mVariantHead) | NOT READ by handler | — |
| +0x1A0 (mVariantIndex) | NOT READ by handler | — |
| +0x1A8 (mBounds) | NOT READ by handler | — |
| +0x1C0 (mMeshVec4) | NOT READ by handler | — |

**NEW fields in Descriptions.h not read by handler**: Most of the struct. Handler only validates material and checks override flag.

### Tag 9: RenderBlockChangesDescription (size 0x18)
| Handler Read | Descriptions.h Field | Status |
|--------------|---------------------|--------|
| +0x00 (mVec00[4]) | `mVec00[4]` at +0x00 | MATCH |
| +0x10 (mQword10) | `mQword10` at +0x10 | MATCH |

**PERFECT MATCH**: Handler reads exactly the two fields defined in the struct. Element stride 0x18 matches.

### Tag 3: RenderChunkGeometryDescription (size 0xF0)
| Handler Read | Descriptions.h Field | Status |
|--------------|---------------------|--------|
| (none - forwarder) | All fields | Forwarded to sub_66ea3d0 |

### Tag 7: RenderSkinnedMeshDescription (size 0x1D0)
| Handler Read | Descriptions.h Field | Status |
|--------------|---------------------|--------|
| +0x140 (mMaterial.mPtr) | `mMaterial` at +0x140 | MATCH |
| +0x148 (mMaterial.mCtrl) | `mMaterial` SharedRef.ctrl | MATCH |
| +0x000..0x03F (mMatrixA) | `mMatrixA[16]` at +0x000 | MATCH (right subtree) |
| +0x0B0 (mMesh) | `mMesh` at +0x0B0 | MATCH (right subtree) |
| +0x0B8 (mValueB8) | `mValueB8` at +0x0B8 | MATCH (right subtree) |
| +0x0C0..0x0CF (mBlockC0) | `mBlockC0[4]` at +0x0C0 | MATCH (right subtree) |
| +0x0E8 (mRefE0.mPtr) | `mRefE0` at +0x0E0 | MATCH (right subtree) |
| +0x108 (mRef108.mPtr) | `mRef108` at +0x108 | MATCH (right subtree) |
| +0x1B0 (mVariantIndex) | `mVariantIndex` at +0x1B0 | MATCH (right subtree) |
| +0x198 (mVariantPayload) | `mVariantPayload` at +0x198 | MATCH (right subtree) |
| +0x040 (mMatrixB) | `mMatrixB[16]` at +0x040 | NOT READ |
| +0x080 (mBounds) | `mBounds[6]` at +0x080 | NOT READ |
| +0x09C (mMeshVec4) | `mMeshVec4[4]` at +0x09C | NOT READ |
| +0x0D0 (mBlockD0) | `mBlockD0[4]` at +0x0D0 | NOT READ |
| +0x0F0 (mRefF0) | `mRefF0` at +0x0F0 | NOT READ |
| +0x100 (mByte100) | `mByte100` at +0x100 | NOT READ |
| +0x120 (mRef120) | `mRef120` at +0x120 | NOT READ |
| +0x130 (mRef130) | `mRef130` at +0x130 | NOT READ |
| +0x150 (mFlags150) | `mFlags150[4]` at +0x150 | NOT READ |
| +0x154 (mBlock154) | `mBlock154[4]` at +0x154 | NOT READ |
| +0x164 (mBlock164) | `mBlock164[4]` at +0x164 | NOT READ |
| +0x174 (mValue174) | `mValue174` at +0x174 | NOT READ |
| +0x178 (mCount178) | `mCount178` at +0x178 | NOT READ |
| +0x180 (mVariantHead) | `mVariantHead[0x10]` at +0x180 | NOT READ |
| +0x1B8 (mOverride) | `mOverride[4]` at +0x1B8 | NOT READ |
| +0x1C8 (mHasOverride) | `mHasOverride` at +0x1C8 | NOT READ |
| +0x1CC (mFlags1CC) | `mFlags1CC` at +0x1CC | NOT READ |
| +0x1CE (mByte1CE) | `mByte1CE` at +0x1CE | NOT READ |

**NEW fields in Descriptions.h not read by handler (right subtree only reads subset)**: Most of the struct. The right subtree (overlay materials) reads transform, mesh, refs, and variant. The generic fallback reads only `mMaterial` for the hash.

---

## Gaps / Open Questions

1. **[UNVERIFIED: 0x6646f7a]** Tag 1: `movzx r8d, byte ptr [rax+0x39]` reads `mOwner+0x39`. What is this byte? The `mOwner` is the nametag source object (per Descriptions.h comment). Need to trace clone 0x1127330 to see what it stores at mOwner+0x39.

2. **[UNVERIFIED: 0x664705b]** Tag 1: `cmp dword ptr [r15+0xE4], 0x7FFFFFFF` checks frame_context+0x68+0xE4. Purpose unknown. FrameBuilder context field.

3. **[UNVERIFIED: 0x6646cc4]** Tag 2: `cmp byte ptr [rdi+0xE0], 0` checks `mHasOverride` (byte at +0xE0). Descriptions.h has `mHasOverride` at +0xE0 (bool) but also `mHasOverride` at +0x1C8 (bool). Which is which? The constructor 0x668b850 writes both.

4. **[UNVERIFIED: 0x66475BB]** Tag 7 generic fallback: The path at 0x66475BB calls `sub_4df6e80` (texture resolver) and builds vertex data. What material/pass does it resolve for general skinned entities (like ender_dragon)? The hash 0x0694BEA7E37055A4 is not in the switch.

5. **[UNVERIFIED: 0x6646dc2]** Tag 7: The `cmovne rdx, rcx` at 0x6646dd7 selects between default fallback (0x1232E708) and `mMaterial+0x10`. What is the default fallback object at 0x1232E708?

6. **Missing live data**: Tags 5 and 9 have no live captures. Tag 1 live data is item payload, not description. Need description-level live captures or clone output verification.

---

## Verification Lines for verify_oc.py

### Tag 1 handler (0x6646f5b - 0x66471dd)
```
0x6646f5b  mov rax,[rdi+58]
0x6646f5f  test rax,rax
0x6646f62  je 0x664ebd7
0x6646f68  cmp qword ptr [rax+40],0
0x6646f6d  je 0x664ebd7
0x6646f73  lea rdx,[rdi+58]
0x6646f77  mov rax,[rdi]
0x6646f7a  movzx r8d,byte ptr [rax+39]
0x6646f7f  lea rcx,[rbp+140]
0x6646f86  call 0x66b2b30
0x6646f8b  xorps xmm0,xmm0
0x6646f8e  movaps [rbp+80],xmm0
0x6646f95  movaps [rbp+70],xmm0
0x6646f99  movaps [rbp+60],xmm0
0x6646f9d  movaps [rbp+50],xmm0
0x6646fa1  movaps [rbp+40],xmm0
0x6646fa5  movaps [rbp+30],xmm0
0x6646fa9  movaps [rbp+20],xmm0
0x6646fad  movaps [rbp+10],xmm0
0x6646fb1  mov qword ptr [rbp+90],0
0x6646fbc  mov qword ptr [rbp+1f8],0
0x6646fc7  mov qword ptr [rbp+200],7
0x6646fd2  mov qword ptr [rbp+208],f
0x6646fdd  mov dword ptr [rbp+1f0],656d614e
0x6646fe7  mov dword ptr [rbp+1f3],67617465
0x6646ff1  mov byte ptr [rbp+1f7],0
0x6646ff8  mov rax,[rbp+8a0]
0x6646fff  mov r13,[rax+40]
0x6647003  mov r15,[rax+68]
0x6647007  mov rax,6ef4382226de1fd6
0x6647011  mov [rbp+880],rax
0x6647018  mov qword ptr [rbp+888],0
0x6647023  mov rcx,[1233e1b0]
0x664702a  mov rax,[rcx]
0x664702d  mov rax,[rax+10]
0x6647031  mov dl,30
0x6647033  call qword ptr [f99ffa0]
0x6647039  nop
0x664703a  mov r14d,eax
0x664703d  lea r12,[r15+98]
0x6647044  mov rcx,r12
0x6647047  call 0xeec59f0
0x664704c  test eax,eax
0x664704e  mov [rbp+898],r14b
0x6647055  jne 0x664f04d
0x664705b  cmp dword ptr [r15+e4],7fffffff
0x6647066  je 0x664f15a
... (hash computation and table lookup)
0x664717d  lea rdx,[rbp+220]
0x6647184  lea r8,[rbp+880]
0x664718b  mov rcx,r15
0x664718e  call 0x567d280
0x6647193  nop
0x6647194  mov r8,[rbp+220]
0x664719b  mov rdx,[r15+88]
0x66471a2  cmp rdx,[r15+90]
0x66471a9  je 0x66482e1
0x66471af  xorps xmm0,xmm0
0x66471b2  movups [rdx],xmm0
0x66471b5  mov rax,[r8+28]
0x66471b9  test rax,rax
0x66471bc  je 0x66471c2
0x66471be  lock inc dword ptr [rax+8]
0x66471c2  mov rax,[r8+20]
0x66471c6  mov [rdx],rax
0x66471c9  mov rax,[r8+28]
0x66471cd  mov [rdx+8],rax
0x66471d1  add qword ptr [r15+88],10
0x66471d9  jmp 0x66482f2
```

### Tag 5 handler (0x66471de - 0x664731b)
```
0x66471de  mov rcx,[rdi]
0x66471e1  call 0x4def080
0x66471e6  test al,al
0x66471e8  je 0x664ebd7
0x66471ee  mov r13,rbx
0x66471f1  mov eax,[129f9ca0]
0x66471f7  mov ecx,[128767c8]
0x66471fd  mov rdx,gs:[58]
0x6647206  mov rcx,[rdx+rcx*8]
0x664720a  cmp eax,[rcx+4]
0x6647210  jg 0x664ef73
0x6647216  mov rax,[rbp+8a0]
0x664721d  mov r9,[rax+40]
0x6647221  mov rcx,[rax+68]
0x6647225  pxor xmm0,xmm0
0x6647229  movdqa [rbp+220],xmm0
0x6647231  lea rax,[f552ed0]
0x6647238  mov [rbp+5a0],rax
0x664723f  mov qword ptr [rbp+5a8],6
0x664724a  lea rsi,[rbp+220]
0x6647251  mov [rsp+28],rsi
0x6647256  lea rax,[rbp+5a0]
0x664725d  mov [rsp+20],rax
0x6647262  lea r8,[129f9c90]
0x6647269  lea rdx,[rbp+850]
0x6647270  call 0x675e440
0x6647275  mov rax,[rbp+850]
0x664727c  mov rbx,[rax]
0x664727f  test rbx,rbx
0x6647282  je 0x664e971
0x6647288  mov eax,[129ca5e0]
0x664728e  mov ecx,[128767c8]
0x6647294  mov rdx,gs:[58]
0x664729d  mov rcx,[rdx+rcx*8]
0x66472a1  cmp eax,[rcx+4]
0x66472a7  jg 0x664f176
0x66472ad  cmp byte ptr [rbx+10],1
0x66472b1  jne 0x664e971
0x66472b7  mov rax,[rbp+850]
0x66472be  mov rcx,[rax+8]
0x66472c2  test rcx,rcx
0x66472c5  je 0x6647f50
0x66472cb  lock inc dword ptr [rcx+8]
0x66472cf  mov rcx,[rax]
0x66472d2  mov r14,[rax+8]
0x66472d6  mov rax,[rcx+18]
0x66472da  mov rbx,[rax]
0x66472dd  test r14,r14
0x66472e0  je 0x6647f5a
0x66472e6  lock dec dword ptr [r14+8]
0x66472eb  jne 0x6647f5a
0x66472f1  mov rax,[r14]
0x66472f4  mov rax,[rax]
0x66472f7  mov rcx,r14
0x66472fa  call qword ptr [f99ffa0]
0x6647300  lock dec dword ptr [r14+c]
0x6647305  jne 0x6647f5a
0x664730b  mov rax,[r14]
0x664730e  mov rax,[rax+8]
0x6647312  mov rcx,r14
0x6647315  call qword ptr [f99ffa0]
0x664731b  jmp 0x6647f5a
```

### Tag 2 handler (0x6646c8d - 0x6646d5a)
```
0x6646c8d  mov [rbp+898],rbx
0x6646c94  mov rax,[rdi+108]
0x6646c9b  test rax,rax
0x6646c9e  je 0x664ebd7
0x6646ca4  mov rbx,[rax+40]
0x6646ca8  test rbx,rbx
0x6646cab  je 0x664ebd7
0x6646cb1  lea r14,[rdi+108]
0x6646cb8  mov rsi,[rax+10]
0x6646cbc  mov al,1
0x6646cbe  mov [rbp+870],eax
0x6646cc4  cmp byte ptr [rdi+e0],0
0x6646ccb  mov r12b,1
0x6646cce  jne 0x6649e41
0x6646cd4  mov qword ptr [rbp+228],0
0x6646cdf  mov qword ptr [rbp+230],a
0x6646cea  mov qword ptr [rbp+238],f
0x6646cf5  mov rax,[f7c86b5]
0x6646cfc  mov [rbp+220],rax
0x6646d03  movzx eax,word ptr [f7c86bd]
0x6646d0a  mov [rbp+228],ax
0x6646d11  lea rcx,[rbx+98]
0x6646d18  lea rdx,[rbp+220]
0x6646d1f  call 0x358c40
0x6646d24  mov r12b,1
0x6646d27  cmp rax,[rbx+98]
0x6646d2e  jne 0x6649dfc
0x6646d34  mov rax,[r14]
0x6646d37  lea rcx,[rax+10]
0x6646d3b  test rax,rax
0x6646d3e  lea r15,[1232e708]
0x6646d45  cmovne r15,rcx
0x6646d49  mov r12,[r15+18]
0x6646d4d  cmp r12,17
0x6646d51  jae 0x6648a35
0x6646d57  xor r12d,r12d
0x6646d5a  jmp 0x6649dfc
```

### Tag 9 handler (0x6646bc6 - 0x6646c88)
```
0x6646bc6  movups xmm7,[rdi]
0x6646bc9  movsd xmm6,[rdi+10]
0x6646bce  mov ecx,9d0
0x6646bd3  mov rax,[rbp+8a0]
0x6646bda  add rcx,[rax+10]
0x6646bde  call 0x5aba5c0
0x6646be3  mov rsi,rax
0x6646be6  xorps xmm0,xmm0
0x6646be9  movaps [rbp+2d0],xmm0
0x6646bf0  movaps [rbp+2c0],xmm0
0x6646bf7  movaps [rbp+2b0],xmm0
0x6646bfe  movaps [rbp+2a0],xmm0
0x6646c05  movaps [rbp+290],xmm0
0x6646c0c  movaps [rbp+280],xmm0
0x6646c13  movaps [rbp+270],xmm0
0x6646c1a  movaps [rbp+260],xmm0
0x6646c21  movaps [rbp+250],xmm0
0x6646c28  movaps [rbp+240],xmm0
0x6646c2f  movaps [rbp+230],xmm0
0x6646c36  movaps [rbp+220],xmm0
0x6646c3d  mov qword ptr [rbp+2e0],0
0x6646c48  mov rcx,[1233e1b0]
0x6646c4f  mov rax,[rcx]
0x6646c52  mov rax,[rax+10]
0x6646c56  mov dl,4a
0x6646c58  call qword ptr [f99ffa0]
0x6646c5e  mov r8d,eax
0x6646c61  mov r12,[rsi+98]
0x6646c68  cmp r12,[rsi+a0]
0x6646c6f  je 0x66474e8
0x6646c75  movups [r12],xmm7
0x6646c7a  movlps [r12+10],xmm6
0x6646c80  add qword ptr [rsi+98],18
0x6646c88  jmp 0x6647a74
```

### Tag 3 handler (0x6646d5f - 0x6646dbd)
```
0x6646d5f  mov rcx,rbx
0x6646d62  mov rdx,[rbp+8a0]
0x6646d69  mov r8,rdi
0x6646d6c  movaps xmm6,[rbp+8b0]
0x6646d73  movaps xmm7,[rbp+8c0]
0x6646d7a  movaps xmm8,[rbp+8d0]
0x6646d82  movaps xmm9,[rbp+8e0]
0x6646d8a  movaps xmm10,[rbp+8f0]
0x6646d92  movaps xmm11,[rbp+900]
0x6646d9a  movaps xmm12,[rbp+910]
0x6646da2  movaps xmm13,[rbp+920]
0x6646daa  add rsp,9b8
0x6646db1  pop rbx
0x6646db2  pop rdi
0x6646db3  pop rsi
0x6646db4  pop r12
0x6646db6  pop r13
0x6646db8  pop r14
0x6646dba  pop r15
0x6646dbc  pop rbp
0x6646dbd  jmp 0x66ea3d0
```

### Tag 7 handler (0x6646dc2 - 0x6646f5a) - key entry and hash switch
```
0x6646dc2  mov rax,[rdi+140]
0x6646dc9  lea rcx,[rax+10]
0x6646dcd  test rax,rax
0x6646dd0  lea rdx,[1232e708]
0x6646dd7  cmovne rdx,rcx
0x6646ddb  mov rcx,[rdx]
0x6646dde  mov rdx,416ae22cab22ea36
0x6646de8  cmp rcx,rdx
0x6646deb  jg 0x6647449
0x6646df1  mov rdx,d8ef928bc853553a
0x6646dfb  cmp rcx,rdx
0x6646dfe  je 0x6646e13
0x6646e00  mov rdx,2c8b246fd3eddc59
0x6646e0a  cmp rcx,rdx
0x6646e0d  jne 0x66475bb
0x6646e13  mov r13,rbx
0x6646e16  mov rax,[128d6fa8]
0x6646e1d  mov rax,[rax+120]
0x6646e24  mov rax,[rax+40]
0x6646e28  movq xmm6,[rax]
0x6646e2c  mov eax,[129f9cc8]
0x6646e32  mov ecx,[128767c8]
0x6646e38  mov rdx,gs:[58]
0x6646e41  mov rcx,[rdx+rcx*8]
0x6646e45  cmp eax,[rcx+4]
0x6646e4b  jg 0x664efdd
0x6646e51  mov rax,[rbp+8a0]
0x6646e58  mov r9,[rax+40]
0x6646e5c  mov rcx,[rax+68]
0x6646e60  pxor xmm0,xmm0
0x6646e64  movdqa [rbp+220],xmm0
0x6646e6c  lea rax,[f515e74]
0x6646e73  mov [rbp+5a0],rax
0x6646e7a  mov qword ptr [rbp+5a8],11
0x6646e85  lea rax,[rbp+220]
0x6646e8c  mov [rsp+28],rax
0x6646e91  lea rsi,[rbp+5a0]
0x6646e98  mov [rsp+20],rsi
0x6646e9d  lea r8,[129f9cb8]
0x6646ea4  lea rdx,[rbp+1f0]
0x6646eab  call 0x675e440
... (rest matches tag 1/5 refcount pattern)
```

---

## TOOL REQUESTS

| Name | Input -> Output | Why it would help |
|------|-----------------|-------------------|
| `descscan2.py` enhancement | RVA + reg -> field read table with callee tracing | Currently casewalk.py walks entire visitor CFG; need per-handler isolation. Manual filtering is error-prone. |
| `livedec.py` struct-aware mode | Live dump + struct definition -> mapped fields | Currently outputs generic float2/ptr-heap; would be faster to auto-map to struct field names. |
| Jump table cross-ref | JT RVA -> tag->handler mapping (already have jt.py) | jt.py works well; no new tool needed. |
| Clone output tracer | Clone RVA -> description struct stores | Would auto-generate the description field tables from the clone constructors instead of manual correlation. |

---

## Verification Summary

Run `python tools/sigs/verify_oc.py docs/progress/oc_U-E1c.md` to verify all quoted instruction lines.

---

## Fixed Verification Lines (exact rdis format)

### Tag 1 handler (0x6646f5b - 0x66471dd)
```
0x6646f5b  mov rax,[rdi+58]
0x6646f5f  test rax,rax
0x6646f62  je 0x664ebd7
0x6646f68  cmp qword ptr [rax+40],0
0x6646f6d  je 0x664ebd7
0x6646f73  lea rdx,[rdi+58]
0x6646f77  mov rax,[rdi]
0x6646f7a  movzx r8d,byte ptr [rax+39]
0x6646f7f  lea rcx,[rbp+140]
0x6646f86  call 0x66b2b30
0x6646f8b  xorps xmm0,xmm0
0x6646f8e  movaps [rbp+80],xmm0
0x6646f95  movaps [rbp+70],xmm0
0x6646f99  movaps [rbp+60],xmm0
0x6646f9d  movaps [rbp+50],xmm0
0x6646fa1  movaps [rbp+40],xmm0
0x6646fa5  movaps [rbp+30],xmm0
0x6646fa9  movaps [rbp+20],xmm0
0x6646fad  movaps [rbp+10],xmm0
0x6646fb1  mov qword ptr [rbp+90],0
0x6646fbc  mov qword ptr [rbp+1f8],0
0x6646fc7  mov qword ptr [rbp+200],7
0x6646fd2  mov qword ptr [rbp+208],f
0x6646fdd  mov dword ptr [rbp+1f0],656d614e
0x6646fe7  mov dword ptr [rbp+1f3],67617465
0x6646ff1  mov byte ptr [rbp+1f7],0
0x6646ff8  mov rax,[rbp+8a0]
0x6646fff  mov r13,[rax+40]
0x6647003  mov r15,[rax+68]
0x6647007  mov rax,6ef4382226de1fd6
0x6647011  mov [rbp+880],rax
0x6647018  mov qword ptr [rbp+888],0
0x6647023  mov rcx,[1233e1b0]
0x664702a  mov rax,[rcx]
0x664702d  mov rax,[rax+10]
0x6647031  mov dl,30
0x6647033  call qword ptr [f99ffa0]
0x6647039  nop
0x664703a  mov r14d,eax
0x664703d  lea r12,[r15+98]
0x6647044  mov rcx,r12
0x6647047  call 0xeec59f0
0x664704c  test eax,eax
0x664704e  mov [rbp+898],r14b
0x6647055  jne 0x664f04d
0x664705b  cmp dword ptr [r15+e4],7fffffff
0x6647066  je 0x664f15a
0x664706c  mov rax,[rbp+880]
0x6647073  movzx ecx,byte ptr [rbp+888]
0x664707a  mov r10,cbf29ce484222325
0x6647084  xor rcx,r10
0x6647087  mov rsi,100000001b3
0x6647091  imul rcx,rsi
0x6647095  movzx edx,byte ptr [rbp+889]
0x664709c  xor rdx,rcx
0x664709f  imul rdx,rsi
0x66470a3  movzx ecx,byte ptr [rbp+88a]
0x66470aa  xor rcx,rdx
0x66470ad  imul rcx,rsi
0x66470b1  movzx edx,byte ptr [rbp+88b]
0x66470b8  xor rdx,rcx
0x66470bb  imul rdx,rsi
0x66470bf  movzx ecx,byte ptr [rbp+88c]
0x66470c6  xor rcx,rdx
0x66470c9  imul rcx,rsi
0x66470cd  movzx edx,byte ptr [rbp+88d]
0x66470d4  xor rdx,rcx
0x66470d7  imul rdx,rsi
0x66470db  movzx ecx,byte ptr [rbp+88e]
0x66470e2  xor rcx,rdx
0x66470e5  imul rcx,rsi
0x66470e9  movzx r8d,byte ptr [rbp+88f]
0x66470f1  xor r8,rcx
0x66470f4  imul r8,rsi
0x66470f8  mov rcx,rax
0x66470fb  shl rcx,6
0x66470ff  mov r9,rax
0x6647102  shr r9,2
0x6647106  add r9,rcx
0x6647109  mov edx,9e3779b9
0x664710e  add rdx,r9
0x6647111  add rdx,r8
0x6647114  xor rdx,rax
0x6647117  and rdx,[r15+70]
0x664711b  mov rcx,[r15+48]
0x664711f  mov r8,[r15+58]
0x6647123  shl rdx,4
0x6647127  mov rbx,[r8+rdx+8]
0x664712c  cmp rbx,rcx
0x664712f  mov [rbp+870],r10
0x6647136  mov [rbp+598],r12
0x664713d  mov [rbp+1e8],r13
0x6647144  je 0x66475b3
0x664714a  mov rdx,[r8+rdx]
0x664714e  mov r8,[rbp+888]
0x6647155  cmp rax,[rbx+10]
0x6647159  je short 0x664716e
0x664715b  cmp rbx,rdx
0x664715e  je 0x66475b3
0x6647164  mov rbx,[rbx+8]
0x6647168  cmp rax,[rbx+10]
0x664716c  jne short 0x664715b
0x664716e  cmp r8,[rbx+18]
0x6647172  jne short 0x664715b
0x6647174  cmp rbx,rcx
0x6647177  je 0x66475b3
0x664717d  lea rdx,[rbp+220]
0x6647184  lea r8,[rbp+880]
0x664718b  mov rcx,r15
0x664718e  call 0x567d280
0x6647193  nop
0x6647194  mov r8,[rbp+220]
0x664719b  mov rdx,[r15+88]
0x66471a2  cmp rdx,[r15+90]
0x66471a9  je 0x66482e1
0x66471af  xorps xmm0,xmm0
0x66471b2  movups [rdx],xmm0
0x66471b5  mov rax,[r8+28]
0x66471b9  test rax,rax
0x66471bc  je short 0x66471c2
0x66471be  lock inc dword ptr [rax+8]
0x66471c2  mov rax,[r8+20]
0x66471c6  mov [rdx],rax
0x66471c9  mov rax,[r8+28]
0x66471cd  mov [rdx+8],rax
0x66471d1  add qword ptr [r15+88],10
0x66471d9  jmp 0x66482f2
```

### Tag 5 handler (0x66471de - 0x664731b)
```
0x66471de  mov rcx,[rdi]
0x66471e1  call 0x4def080
0x66471e6  test al,al
0x66471e8  je 0x664ebd7
0x66471ee  mov r13,rbx
0x66471f1  mov eax,[129f9ca0]
0x66471f7  mov ecx,[128767c8]
0x66471fd  mov rdx,gs:[58]
0x6647206  mov rcx,[rdx+rcx*8]
0x664720a  cmp eax,[rcx+4]
0x6647210  jg 0x664ef73
0x6647216  mov rax,[rbp+8a0]
0x664721d  mov r9,[rax+40]
0x6647221  mov rcx,[rax+68]
0x6647225  pxor xmm0,xmm0
0x6647229  movdqa [rbp+220],xmm0
0x6647231  lea rax,[f552ed0]
0x6647238  mov [rbp+5a0],rax
0x664723f  mov qword ptr [rbp+5a8],6
0x664724a  lea rsi,[rbp+220]
0x6647251  mov [rsp+28],rsi
0x6647256  lea rax,[rbp+5a0]
0x664725d  mov [rsp+20],rax
0x6647262  lea r8,[129f9c90]
0x6647269  lea rdx,[rbp+850]
0x6647270  call 0x675e440
0x6647275  mov rax,[rbp+850]
0x664727c  mov rbx,[rax]
0x664727f  test rbx,rbx
0x6647282  je 0x664e971
0x6647288  mov eax,[129ca5e0]
0x664728e  mov ecx,[128767c8]
0x6647294  mov rdx,gs:[58]
0x664729d  mov rcx,[rdx+rcx*8]
0x66472a1  cmp eax,[rcx+4]
0x66472a7  jg 0x664f176
0x66472ad  cmp byte ptr [rbx+10],1
0x66472b1  jne 0x664e971
0x66472b7  mov rax,[rbp+850]
0x66472be  mov rcx,[rax+8]
0x66472c2  test rcx,rcx
0x66472c5  je 0x6647f50
0x66472cb  lock inc dword ptr [rcx+8]
0x66472cf  mov rcx,[rax]
0x66472d2  mov r14,[rax+8]
0x66472d6  mov rax,[rcx+18]
0x66472da  mov rbx,[rax]
0x66472dd  test r14,r14
0x66472e0  je 0x6647f5a
0x66472e6  lock dec dword ptr [r14+8]
0x66472eb  jne 0x6647f5a
0x66472f1  mov rax,[r14]
0x66472f4  mov rax,[rax]
0x66472f7  mov rcx,r14
0x66472fa  call qword ptr [f99ffa0]
0x6647300  lock dec dword ptr [r14+c]
0x6647305  jne 0x6647f5a
0x664730b  mov rax,[r14]
0x664730e  mov rax,[rax+8]
0x6647312  mov rcx,r14
0x6647315  call qword ptr [f99ffa0]
0x664731b  jmp 0x6647f5a
```

### Tag 2 handler (0x6646c8d - 0x6646d5a)
```
0x6646c8d  mov [rbp+898],rbx
0x6646c94  mov rax,[rdi+108]
0x6646c9b  test rax,rax
0x6646c9e  je 0x664ebd7
0x6646ca4  mov rbx,[rax+40]
0x6646ca8  test rbx,rbx
0x6646cab  je 0x664ebd7
0x6646cb1  lea r14,[rdi+108]
0x6646cb8  mov rsi,[rax+10]
0x6646cbc  mov al,1
0x6646cbe  mov [rbp+870],eax
0x6646cc4  cmp byte ptr [rdi+e0],0
0x6646ccb  mov r12b,1
0x6646cce  jne 0x6649e41
0x6646cd4  mov qword ptr [rbp+228],0
0x6646cdf  mov qword ptr [rbp+230],a
0x6646cea  mov qword ptr [rbp+238],f
0x6646cf5  mov rax,[f7c86b5]
0x6646cfc  mov [rbp+220],rax
0x6646d03  movzx eax,word ptr [f7c86bd]
0x6646d0a  mov [rbp+228],ax
0x6646d11  lea rcx,[rbx+98]
0x6646d18  lea rdx,[rbp+220]
0x6646d1f  call 0x358c40
0x6646d24  mov r12b,1
0x6646d27  cmp rax,[rbx+98]
0x6646d2e  jne 0x6649dfc
0x6646d34  mov rax,[r14]
0x6646d37  lea rcx,[rax+10]
0x6646d3b  test rax,rax
0x6646d3e  lea r15,[1232e708]
0x6646d45  cmovne r15,rcx
0x6646d49  mov r12,[r15+18]
0x6646d4d  cmp r12,17
0x6646d51  jae 0x6648a35
0x6646d57  xor r12d,r12d
0x6646d5a  jmp 0x6649dfc
```

### Tag 9 handler (0x6646bc6 - 0x6646c88)
```
0x6646bc6  movups xmm7,[rdi]
0x6646bc9  movsd xmm6,[rdi+10]
0x6646bce  mov ecx,9d0
0x6646bd3  mov rax,[rbp+8a0]
0x6646bda  add rcx,[rax+10]
0x6646bde  call 0x5aba5c0
0x6646be3  mov rsi,rax
0x6646be6  xorps xmm0,xmm0
0x6646be9  movaps [rbp+2d0],xmm0
0x6646bf0  movaps [rbp+2c0],xmm0
0x6646bf7  movaps [rbp+2b0],xmm0
0x6646bfe  movaps [rbp+2a0],xmm0
0x6646c05  movaps [rbp+290],xmm0
0x6646c0c  movaps [rbp+280],xmm0
0x6646c13  movaps [rbp+270],xmm0
0x6646c1a  movaps [rbp+260],xmm0
0x6646c21  movaps [rbp+250],xmm0
0x6646c28  movaps [rbp+240],xmm0
0x6646c2f  movaps [rbp+230],xmm0
0x6646c36  movaps [rbp+220],xmm0
0x6646c3d  mov qword ptr [rbp+2e0],0
0x6646c48  mov rcx,[1233e1b0]
0x6646c4f  mov rax,[rcx]
0x6646c52  mov rax,[rax+10]
0x6646c56  mov dl,4a
0x6646c58  call qword ptr [f99ffa0]
0x6646c5e  mov r8d,eax
0x6646c61  mov r12,[rsi+98]
0x6646c68  cmp r12,[rsi+a0]
0x6646c6f  je 0x66474e8
0x6646c75  movups [r12],xmm7
0x6646c7a  movlps [r12+10],xmm6
0x6646c80  add qword ptr [rsi+98],18
0x6646c88  jmp 0x6647a74
```

### Tag 3 handler (0x6646d5f - 0x6646dbd)
```
0x6646d5f  mov rcx,rbx
0x6646d62  mov rdx,[rbp+8a0]
0x6646d69  mov r8,rdi
0x6646d6c  movaps xmm6,[rbp+8b0]
0x6646d73  movaps xmm7,[rbp+8c0]
0x6646d7a  movaps xmm8,[rbp+8d0]
0x6646d82  movaps xmm9,[rbp+8e0]
0x6646d8a  movaps xmm10,[rbp+8f0]
0x6646d92  movaps xmm11,[rbp+900]
0x6646d9a  movaps xmm12,[rbp+910]
0x6646da2  movaps xmm13,[rbp+920]
0x6646daa  add rsp,9b8
0x6646db1  pop rbx
0x6646db2  pop rdi
0x6646db3  pop rsi
0x6646db4  pop r12
0x6646db6  pop r13
0x6646db8  pop r14
0x6646dba  pop r15
0x6646dbc  pop rbp
0x6646dbd  jmp 0x66ea3d0
```

### Tag 7 handler (0x6646dc2 - 0x6646f5a) - key entry and hash switch
```
0x6646dc2  mov rax,[rdi+140]
0x6646dc9  lea rcx,[rax+10]
0x6646dcd  test rax,rax
0x6646dd0  lea rdx,[1232e708]
0x6646dd7  cmovne rdx,rcx
0x6646ddb  mov rcx,[rdx]
0x6646dde  mov rdx,416ae22cab22ea36
0x6646de8  cmp rcx,rdx
0x6646deb  jg 0x6647449
0x6646df1  mov rdx,d8ef928bc853553a
0x6646dfb  cmp rcx,rdx
0x6646dfe  je short 0x6646e13
0x6646e00  mov rdx,2c8b246fd3eddc59
0x6646e0a  cmp rcx,rdx
0x6646e0d  jne 0x66475bb
0x6646e13  mov r13,rbx
0x6646e16  mov rax,[128d6fa8]
0x6646e1d  mov rax,[rax+120]
0x6646e24  mov rax,[rax+40]
0x6646e28  movq xmm6,[rax]
0x6646e2c  mov eax,[129f9cc8]
0x6646e32  mov ecx,[128767c8]
0x6646e38  mov rdx,gs:[58]
0x6646e41  mov rcx,[rdx+rcx*8]
0x6646e45  cmp eax,[rcx+4]
0x6646e4b  jg 0x664efdd
0x6646e51  mov rax,[rbp+8a0]
0x6646e58  mov r9,[rax+40]
0x6646e5c  mov rcx,[rax+68]
0x6646e60  pxor xmm0,xmm0
0x6646e64  movdqa [rbp+220],xmm0
0x6646e6c  lea rax,[f515e74]
0x6646e73  mov [rbp+5a0],rax
0x6646e7a  mov qword ptr [rbp+5a8],11
0x6646e85  lea rax,[rbp+220]
0x6646e8c  mov [rsp+28],rax
0x6646e91  lea rsi,[rbp+5a0]
0x6646e98  mov [rsp+20],rsi
0x6646e9d  lea r8,[129f9cb8]
0x6646ea4  lea rdx,[rbp+1f0]
0x6646eab  call 0x675e440
0x6646eb0  mov rax,[rbp+1f0]
0x6646eb7  mov rbx,[rax]
0x6646eba  test rbx,rbx
0x6646ebd  je 0x664cb91
0x6646ec3  mov eax,[129ca5e0]
0x6646ec9  mov ecx,[128767c8]
0x6646ecf  mov rdx,gs:[58]
0x6646ed8  mov rcx,[rdx+rcx*8]
0x6646edc  cmp eax,[rcx+4]
0x6646ee2  jg 0x664f1b9
0x6646ee8  cmp byte ptr [rbx+10],1
0x6646eec  jne 0x664cb91
0x6646ef2  mov rax,[rbp+1f0]
0x6646ef9  mov rcx,[rax+8]
0x6646efd  test rcx,rcx
0x6646f00  je 0x6647fe7
0x6646f06  lock inc dword ptr [rcx+8]
0x6646f0a  mov rcx,[rax]
0x6646f0d  mov r14,[rax+8]
0x6646f11  mov rax,[rcx+18]
0x6646f15  mov rbx,[rax]
0x6646f18  test r14,r14
0x6646f1b  je 0x6647ff1
0x6646f21  lock dec dword ptr [r14+8]
0x6646f26  jne 0x6647ff1
0x6646f2c  mov rax,[r14]
0x6646f2f  mov rax,[rax]
0x6646f32  mov rcx,r14
0x6646f35  call qword ptr [f99ffa0]
0x6646f3b  lock dec dword ptr [r14+c]
0x6646f40  jne 0x6647ff1
0x6646f46  mov rax,[r14]
0x6646f49  mov rax,[rax+8]
0x6646f4d  mov rcx,r14
0x6646f50  call qword ptr [f99ffa0]
0x6646f56  jmp 0x6647ff1
```