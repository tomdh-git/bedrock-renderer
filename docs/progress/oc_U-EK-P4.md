## NEXT
DONE

# Unit U-EK-P4 — bgfx core concepts: Frame, View, RenderItem, Caps

Goal (K-P4, docs/RENDER_CHECKLIST.md line 423):
"bgfx core concepts: Frame, View, RenderItem, Caps (Mojang fork changes slowly) — BGFX_MAP 6e, 6j; audit 6ek fixed Frame.h view structs (stride 0x140); header +0x38/+0x40 fields still unverified"

Scope of this unit (the pending part only): verify the two 0x80-byte draw-header fields at offsets +0x38 (m_uniformEnd) and +0x40 (m_startIndex) of `bgfx::RenderDrawHeader` (src/sdk/mc/deps/bgfx/Frame.h), written by EncoderImpl::submit 0xbc60740 (local draw header at this+0x40; rbx = rsi+0x40 at 0xbc607bb) and copied verbatim to the submit Frame at Frame+0xB4700+idx*0x80, and read by the D3D12 draw executor 0xe821120 from that Frame location.

Already established by earlier units (not re-proven here): view struct stride 0x140 fixed by audit 6ek (Frame.h kViewStructs=0x200, kViewStructStride=0x140, [V static 6q/6ek]); Caps decoded in BGFX_MAP 6j (globals 0x12adfa50/0x12ae0d58, live values); Frame table offsets (view remap +0x00, view structs at +0x200, draw headers +0xB4700 stride 0x80, sort keys +0x14700, item count +0xDC57E8, backbuffer +0xDC5808, frame counter +0xE746D8) [V 6e/6ek].

Disassembly base: tools/rdis on Minecraft.Windows.exe 1.26.62.01. Listings saved at:
docs/progress/oc_U-EK-P4_bc60740_dis.txt (EncoderImpl::submit 0xbc60740)
docs/progress/oc_U-EK-P4_e82a140_dis.txt (executor uniform range check ~0xe82a140)
docs/progress/oc_U-EK-P4_e82cae0_dis.txt (executor indexed append ~0xe82cd21)

## Verbatim proof lines (each checked against rdis dis output of the exe)

0xbc607bb  lea rbx,[rsi+0x40]                  ; rsi = EncoderImpl this; rbx = m_draw header base (this+0x40)
0xbc60852  mov r11,[rcx+0xDC57E0]              ; rcx = EncoderImpl this; [this] = Frame*, Frame+0xDC57E0 = uniform buffer ptr table
0xbc60865  mov r11d,[r11+4]                    ; UniformBuffer->pos = running uniform end for this draw's uniform slot
0xbc60869  mov [rsi+0x698],r11d                ; EncoderImpl m_uniformEnd (this+0x698) = that pos
0xbc609b2  mov rax,[rsi+0x694]                 ; qword load of encoder m_uniformBegin/m_uniformEnd pair (this+0x694/0x698)
0xbc609b9  mov [rsi+0x74],rax                  ; qword store to draw header +0x34/+0x38 (this+0x74 = draw+0x34)
0xbc60ae0  movaps xmm0,[rbx+0x40]              ; 16B load of draw header +0x40..+0x4F (startIndex..numVertices) from encoder's draw
0xbc60ae4  movaps [rax+rcx+0xB4740],xmm0       ; stored verbatim into Frame draw header +0x40 (rax = Frame*, rcx = idx<<7)
0xbc60af7  movaps xmm3,[rbx+0x30]              ; 16B load of draw header +0x30..+0x3F (rgba/scissor/uniformBegin/uniformEnd)
0xbc60afb  movaps [rax+rcx+0xB4730],xmm3       ; stored verbatim into Frame draw header +0x30 (covers +0x38 uniformEnd)
0xbc60b84  xorps xmm0,xmm0                     ; zero vector for the draw clear
0xbc60b92  movaps [rsi+0x80],xmm0              ; 16B zero store at draw header +0x40..+0x4F (startIndex cleared to 0)
0xbc60d4c  movaps [rcx+0x80],xmm0              ; same 16B zero store in the discard path (sub 0xbc60d10, rcx = this)
0xe82a147  mov r8d,[r12+0x34]                  ; executor: draw.m_uniformBegin (r12 = draw header pointer, = [job+0xF0])
0xe82a155  mov edx,[r12+0x38]                  ; executor: draw.m_uniformEnd
0xe82a18b  mov edx,[r12+0x38]                  ; executor: draw.m_uniformEnd (second reach of the range check)
0xe82a19e  cmp r8d,edx                         ; begin < end test for the uniform range
0xe82a1a1  setb al
0xe82a1a4  mov [rbx+0x21C],edx                 ; job->uniformEnd = draw.m_uniformEnd
0xe82cd21  mov eax,[rcx+0x40]                  ; executor: draw.m_startIndex (rcx = draw header pointer)
0xe82cd24  mov [rdi+0x78],eax                  ; stored to batch record +0x78 (DrawRecordIndexed startIndex, consumed by flush 0xe81b720)

## Answer table (one row per distinct pending offset; all sites listed)

| name | offset | size | read/store address | verbatim `0xRVA  instr` proof line(s) | meaning | tag |
| draw header +0x38 | draw+0x38 | 16 (movaps 16B chunk read at draw+0x30 covering +0x30..+0x3F); 8 (mov qword store at draw+0x34 covering +0x34..+0x3B); 4 (mov dword loads) | write: EncoderImpl m_draw+0x34 via rsi (= this+0x74), source pair this+0x694/this+0x698 (this+0x698 = UniformBuffer->pos, stored by 0xbc60869 from [UniformBuffer+4] via 0xbc60852/0xbc60865); copy read: draw+0x30..+0x3F via rbx (rbx = this+0x40, m_draw base, 0xbc607bb) stored to Frame+0xB4700+idx*0x80+0x30; executor read: Frame+0xB4700+idx*0x80+0x38 via r12 (= [job+0xF0]) | 0xbc609b9  mov [rsi+0x74],rax ; 0xbc609b2  mov rax,[rsi+0x694] ; 0xbc60869  mov [rsi+0x698],r11d ; 0xbc60af7  movaps xmm3,[rbx+0x30] ; 0xbc60afb  movaps [rax+rcx+0xB4730],xmm3 ; 0xe82a155  mov edx,[r12+0x38] ; 0xe82a18b  mov edx,[r12+0x38] ; 0xe82a147  mov r8d,[r12+0x34] ; 0xe82a19e  cmp r8d,edx ; 0xe82a1a1  setb al ; 0xe82a1a4  mov [rbx+0x21C],edx | m_uniformEnd: end of this draw's uniform range — executor tests [r12+0x34] < [r12+0x38] (0xe82a19e cmp / 0xe82a1a1 setb) and copies [r12+0x38] to job+0x21C (0xe82a1a4); [r12+0x38] = UniformBuffer->pos for this draw's uniform index | [V] |
| encoder uniform-end source | encoder+0x698 | 4 (mov dword store) | EncoderImpl m_uniformEnd via rsi (= this+0x698), loaded from UniformBuffer->pos (+4 of the UniformBuffer object at Frame+0xDC57E0[this+0x6AC*8]) | 0xbc60852  mov r11,[rcx+0xDC57E0] ; 0xbc60865  mov r11d,[r11+4] ; 0xbc60869  mov [rsi+0x698],r11d | source value stored into draw+0x38: the encoder's running uniform-buffer end position for this draw's uniform slot | [V] |
| draw header +0x40 | draw+0x40 | 16 (movaps 16B zero-init store at draw+0x40..+0x4F and 16B load of draw+0x40 in submit's verbatim copy); 4 (mov dword load by executor) | write (zero-init): draw+0x40 via rsi (= this+0x80) at end of submit, 0xbc60b92 (xorps zero at 0xbc60b84); same zeroing in discard 0xbc60d4c; copy read: draw+0x40 via rbx (0xbc607bb) stored to Frame+0xB4700+idx*0x80+0x40; executor read: draw+0x40 via rcx (= [job+0xF0]) stored to batch record +0x78 (0xe82cd24), the start-index field consumed by the draw flush 0xe81b720 | 0xbc60ae0  movaps xmm0,[rbx+0x40] ; 0xbc60ae4  movaps [rax+rcx+0xB4740],xmm0 ; 0xbc60b92  movaps [rsi+0x80],xmm0 ; 0xbc60b84  xorps xmm0,xmm0 ; 0xbc60d4c  movaps [rcx+0x80],xmm0 ; 0xe82cd21  mov eax,[rcx+0x40] ; 0xe82cd24  mov [rdi+0x78],eax | m_startIndex: carried verbatim into the Frame draw header by submit; zero-initialized at end of submit (startIndex = 0 after submit); executor stores it to batch record +0x78 → DrawIndexedInstanced start-index argument path | [V] |

CLOSES? YES — both pending parts of K-P4 are now [V]-proven: +0x38 (m_uniformEnd) has a write (0xbc609b9 qword store from the encoder uniform state whose +0x698 dword = UniformBuffer->pos set at 0xbc60869), a verbatim carry into the Frame draw header (0xbc60af7/0xbc60afb) and executor reads as the uniform-end bound of the begin<end range check (0xe82a155/0xe82a18b vs job+0x21C, stored at 0xe82a1a4); +0x40 (m_startIndex) has a read in submit's verbatim draw copy (0xbc60ae0 movaps [rbx+0x40] → stored at Frame header +0x40 by 0xbc60ae4), a zero-init write at end of submit (0xbc60b92 movaps, xorps at 0xbc60b84; same zeroing in discard 0xbc60d4c) and an executor read stored to batch record +0x78 (0xe82cd21/0xe82cd24). No pending offset remains; nothing is inferred.
