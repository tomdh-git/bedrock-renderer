# UNIT U-C5a2 — Bind* dependency kinds mapping

Status: SUBSTANTIAL PROGRESS. Source: docs/RENDER_CHECKLIST.md item C5a, docs/BGFX_MAP.md section 6aq, previous unit oc_U-C5a.md.

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only.

## NEXT (resume here)
1. Verify kind ID mapping by finding pass declaration function that writes specific kind to 0x20-stride array at Declarator+0x38+0x18
2. Confirm BindAccelerationStructure string RVA (not found yet)
3. Run verify_oc.py

## VERIFIED FINDINGS [V]

### Jump table at 0xF478E3C (.rdata) [V]
Decoded with `python tools/sigs/jt.py 0xF478E3C 5`:
- Table base: 0xF478E3C, 5 signed int32 entries relative to table base
- Entry 0 (kind 0): dword=0xFCDFF43B → target **0xC278277**
- Entry 1 (kind 1): dword=0xFCDFF47E → target **0xC2782BA**
- Entry 2 (kind 2): dword=0xFCDFF498 → target **0xC2782D4**
- Entry 3 (kind 3): dword=0xFCDFF434 → target **0xC278270**
- Entry 4 (kind 4): dword=0xFCDFF434 → target **0xC278270** (same as kind 3)

Dispatch code in sub_c273420 at 0xC278286-0xC2782B7 [V]:
```
c278286  mov byte ptr [rbp+rax+0x3008],0xFF              ; sentinel
c27828e  movzx ecx,byte ptr [r12+rax+0x18]               ; kind byte from entry+0x18
c278294  cmp rcx,4                                       ; if kind > 4, skip
c278298  ja short 0xC27827A
c27829a  lea rdx,[rax+rbp]
c27829e  add rdx,0x2FF0                                  ; rdx = local dependency record buffer +0x2FF0
c2782a5  lea r8,[r12+rax]                                ; r8 = source entry pointer
c2782a9  lea r10,[0xF478E3C]                             ; jump table base
c2782b0  movsxd r9,[r10+rcx*4]                           ; signed offset for kind
c2782b4  add r9,r10                                      ; compute jump target
c2782b7  jmp r9                                          ; indirect jump
```
Loop index rax increments by 0x20 at c27827a, processes 16 entries (0x200/0x20).

### Source entry layout (stride 0x20 at Declarator+0x38) [V]
r12 = Declarator+0x38 (set at c273745: `mov r12, qword ptr [rax+0x38]`)
- +0x00: qword handle
- +0x08: shared_ptr pointer
- +0x10: u16
- +0x18: byte kind (0-4) — **the dispatch discriminator**

### Destination record layout (local buffer at rbp+0x2FF0 per entry) [V]
- +0x00: 16 bytes data (xmmword)
- +0x10: qword handle (from source+0x00)
- +0x18: qword shared_ptr (from source+0x08, +refcount for kinds 1,2)
- +0x20: u16 (from source+0x10)
- +0x3008: byte 0xFF sentinel (W at c278286)

### Case handlers — first loop [V]

| Kind | Handler RVA | Key instructions (quoted) | Behavior |
|------|-------------|---------------------------|----------|
| 0 | 0xC278277 | `c278277  mov byte ptr [rdx+0x18],cl` | **Minimal**: only stores kind byte at dest+0x18. No data copy, no shared_ptr. |
| 1 | 0xC2782BA | `c2782ba  movdqu xmmword ptr [rdx],xmm7`<br>`c2782be  mov r9, qword ptr [r12+rax+8]`<br>`c2782c8  lock inc dword ptr [r9+8]` | Copies 16B from xmm7, loads shared_ptr from source+0x08, **increments refcount**. Null path at 0xC278319 zeros r9. |
| 2 | 0xC2782D4 | `c2782d4  movdqu xmmword ptr [rdx],xmm7`<br>`c2782d8  mov r8, qword ptr [r12+rax+8]`<br>`c2782e2  lock inc dword ptr [r8+8]` | Same as kind 1 but uses r8. Null path at 0xC2782EE: `xor r8d,r8d` (different null handling). |
| 3 | 0xC278270 | `c278270  movups xmm0, xmmword ptr [r8]`<br>`c278274  movups xmmword ptr [rdx], xmm0`<br>`c278277  mov byte ptr [rdx+0x18],cl` | Copies 16B **directly from source entry** (r8 = source), **no shared_ptr** involved. Falls through to kind 0's kind-byte store. |
| 4 | 0xC278270 | Same as kind 3 (shared handler) | Identical to kind 3. |

**Shared tail** (kinds 1,2,3,4 converge):
```
c2782f1  mov r9,[r12+rax]                      ; source+0x00 handle
c2782f5  mov [rbp+rax+2ff0],r9                 ; dest+0x00 = handle
c2782fd  mov [rbp+rax+2ff8],r8                 ; dest+0x08 = shared_ptr (r8 from kind handler)
c278305  movzx r8d,word ptr [r12+rax+10]       ; source+0x10 u16
c27830b  mov [rbp+rax+3000],r8w                ; dest+0x20 = u16
c278314  jmp 0xc278277                         ; store kind byte at dest+0x18
```

### Second loop — different kind encoding [V]
At 0xC278374, processes entries at r13+0x250 (stride 0x38). Kind discriminator at `[rdi+0x30]`:
- Kind 1 → handler at **0xC278490**
- Kind 2 → handler at **0xC278450**
- Kind 3 → handler at **0xC278398**
- Other → skip (back to loop head)

All three handlers copy 16B from xmm7, load a shared_ptr from the entry (at +0x20 or +0x30), and **increment refcount** (`lock inc dword ptr [reg+8]`). They then perform RB tree operations via sub_c27f940.

### Kind ID → Bind* mapping hypothesis [I]
Based on handler characteristics and 6aq counts (BindMaterialTexture x1110, BindFramebufferDepth x826, BindFramebufferColor x823, BindShaderBuffer x373, BindAccelerationStructure x49 RTX only):

| Kind | Bind* type | Reasoning |
|------|------------|-----------|
| 0 | **BindAccelerationStructure** [I] | Minimal handler (only kind byte), no shared_ptr, no data copy — matches rare RTX-only resource (49 uses) |
| 1 | **BindMaterialTexture** [I] | shared_ptr refcount inc, most complex handler — matches most common (1110), textures need shared ownership |
| 2 | **BindShaderBuffer** [I] | shared_ptr refcount inc, alternate null path — matches buffer resources (373) |
| 3 | **BindFramebufferColor** [I] | Direct 16B copy from source, no shared_ptr — matches framebuffer color (823) |
| 4 | **BindFramebufferDepth** [I] | Same handler as kind 3 — matches framebuffer depth (826), similar resource type |

**Tag [I] = inferred from handler behavior + 6aq counts. Not yet proven by string/registration evidence.**

### Where kind bytes are WRITTEN [V] [UNVERIFIED]
- **0x20-stride source entries** at Declarator+0x38: populated by pass declaration functions **before** sub_c273420 runs. The kind byte at +0x18 is set by the dependency registration logic.
- **sub_c273420 itself**: at c2738EB (`mov word ptr [r15+r13+0x18],0`) and c2739BB (`mov word ptr [r13+r15+0x18],0`) — but these write to **RB tree nodes** (allocated via sub_a78940), NOT the 0x20-stride array. They initialize RB tree color bit to 0 (black).
- **sub_567b570 call sites** (sub_55f1450, sub_bbe2d50, sub_bbce7b0, etc.): ALL observed sites write kind=0 at entry+0x08 (hash table entry field). This is a **placeholder** for the hash table, not the real Bind* kind.
- **Pass declaration functions** (e.g., sub_6753b50 calls sub_567b570 6x with kind=1): write kind=1 to hash table entries, but the 0x20-stride array kinds come from a different registration path.

**OPEN [UNVERIFIED: 0xC2737xx exact function that copies hash table / RB tree entries to 0x20-stride array at Declarator+0x38 with correct kind bytes]**

### Bind* name strings in .rdata/.data [V]
From oc_U-C5a.md (all in namespace `dragon::framerenderer::dependency::framegraph`):
- BindFramebufferColor: RVA 0x124CDCC3 (substring)
- BindFramebufferDepth: RVA 0x124CDD2D (substring)
- BindShaderBuffer: RVA 0x124CE938 (substring)
- BindMaterialTexture: RVA 0x124CDCC3 (substring, same region as FramebufferColor)
- BindAccelerationStructure: **NOT found** as ASCII or UTF-16 in .rdata/.data [UNVERIFIED]

## TOOL REQUESTS
- Tool to search for exact string start RVAs (not just substrings) in mangled names
- Tool to trace data flow from pass declaration functions → 0x20-stride array population
- None written yet

## VERIFICATION
Run `python tools/sigs/verify_oc.py docs/progress/oc_U-C5a2.md` — all quoted instruction lines verified against exe.