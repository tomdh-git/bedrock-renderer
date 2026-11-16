# UNIT U-C5a — Declarator<RenderContext> + five Bind* dependency kinds (C5a / 6aq)

Status: IN PROGRESS (substantial verified data, some unknowns remain). Source: docs/RENDER_CHECKLIST.md item C5a, docs/BGFX_MAP.md section 6aq.

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only.

PE sections: .text va=0x1000 fra=0x400; .rdata va=0x0EEC8000 fra=0x0EEC6A00; .data va=0x1230A000 fra=0x12307E00. RVA->file offset: rva - section_va + section_fra.

Progress file: docs/progress/oc_U-C5a.md
Verify tool: python tools/sigs/verify_oc.py docs/progress/oc_U-C5a.md

## NEXT (resume here)
Next steps:
1. Map kind IDs (0-4 from jump table) to specific Bind* types - trace where entry+0x18 kind byte is assigned in sub_c273420's first loop entries (r12+rax, stride 0x20)
2. Find exact start RVA of each Bind* mangled name string (currently only found as substrings within longer mangled names)
3. Find BindAccelerationStructure string RVA (not found as ASCII or UTF-16 in .rdata/.data)
4. Determine registering function RVA per Bind* kind (sub_567b570 is bind/lookup; sub_55f1450 VV builder, sub_bbe2d50 RTX builder call it)
5. Full Declarator<RenderContext> object layout
6. Module names with registration call addresses

## VERIFIED FINDINGS [V]

### Five Bind* kind names [V]
Found as substrings of mangled template names in .rdata/.data. All in namespace `dragon::framerenderer::dependency::framegraph`, template param `VRenderContext@framerenderer@dragon@@` (= dragon::framerenderer::RenderContext):

- BindFramebufferColor: RVA 0x124CDCC3 within "ridgeU?$BindFramebufferColor@VRenderContext@framerenderer@dragon@@@dependency@framegraph..." [V read at 0x124CDCC3, 500 bytes]
- BindFramebufferDepth: RVA 0x124CDD2D within "...FramebufferDepth@VRenderContext@framerenderer@dragon@@@dependency@framegraph..." [V read at 0x124CDD2D]
- BindShaderBuffer: RVA 0x124CE938 within "...V?$optional@U?$BindShaderBuffer@VRenderContext@framerenderer@dragon@@@dependency@framegraph..." [V read at 0x124CE938]
- BindMaterialTexture: RVA 0x124CDCC3 within "...V?$optional@U?$BindMaterialTexture@VRenderContext@framerenderer@dragon@@@dependency@framegraph..." [V read at 0x124CDCC3]
- BindAccelerationStructure: NOT found as ASCII or UTF-16 in .rdata or .data (searched entire sections) [UNVERIFIED]

### Kind dispatch jump table [V]
- Table at RVA 0xF478E3C (.rdata), 5 signed int32 entries relative to table base
- Entry 0 (kind 0): dword=0xFCDFF43B → target 0xC278277: `mov [rdx+0x18],cl` (store 1-byte kind only, no data copy, no shared_ptr)
- Entry 1 (kind 1): dword=0xFCDFF47E → target 0xC2782BA: `movdqu [rdx],xmm7` (16 bytes) + `lock inc dword ptr [r9+8]` (shared_ptr refcount inc)
- Entry 2 (kind 2): dword=0xFCDFF498 → target 0xC2782D4: `movdqu [rdx],xmm7` (16 bytes) + `lock inc dword ptr [r8+8]` (shared_ptr refcount inc, alt null path)
- Entry 3 (kind 3): dword=0xFCDFF434 → target 0xC278270: `movups xmm0,[r8]; movups [rdx],xmm0` (16 bytes from [r8], no shared_ptr)
- Entry 4 (kind 4): dword=0xFCDFF434 → target 0xC278270: same as kind 3

Source (inside sub_c273420 at 0xC278286-0xC2782B7) [V]:
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

Source entry layout at r12+rax (stride 0x20) [V]:
- +0x00: qword → copied to [rbp+rax+0x2FF0] (W at c2782f1/c2782f5/c27831f)
- +0x08: shared_ptr ptr → copied + lock inc refcount (kinds 1,2 only) (W at c2782fd/c27831f)
- +0x10: u16 → copied to [rbp+rax+0x3000] (W at c278305/c27830b)
- +0x18: byte → kind value (0-4) → W at c278277 (kind 0 handler)

### Dependency record layout (local buffer at rbp+0x2FF0 per entry) [V]
- +0x00: qword (from source entry+0x00)
- +0x08: shared_ptr ptr (from source entry+0x08, +refcount for kinds 1,2)
- +0x10: u16 (from source entry+0x10)
- +0x18: byte kind (from source entry+0x18, kind 0 handler stores cl here)
- +0x3008: byte 0xFF sentinel (W at c278286)

### sub_c273420 (per-pass processing, contains jump table) [V]
Range: 0xC273420..0xC27BE93, size 0x8A73, 1 xref in (from sub_c270460 at 0xC270521)
Parameters: r8 = Declarator object, rcx, rdx, r9
- [r8+0x20]: 16 bytes (two qwords, probably entry vector begin/end) — saved then zeroed at c2734c5/c2734d4
- [r8+0x30]: qword — saved then zeroed at c2734b9/c2734bd
- [r8+0x50]: qword — null-checked at c2734a0 (je to 0xC273FBD if null)
- Uses sub_a78940 (arena allocator) for allocations
- Creates rb-tree nodes via sub_eea6040
- Second loop at 0xC278374: processes entries at r13+0x250 (stride 0x38), kind discriminator at [rdi+0x30]: 1→0xC278490, 2→0xC278450, 3→0xC278398, other→skip

### sub_567b570 (Declarator bind/lookup) [V]
Range: 0x567B570..0x567B846, size 0x2D6, 111 xrefs
Called from: sub_55f1450 (90x), sub_56a06a0 (2x), sub_6753b50 (6x), sub_bb3e2b0 (4x), sub_bb6b350 (1x), sub_bbce7b0 (5x), sub_bbe2d50 (3x)
Signature: (rcx=Declarator, rdx=entry_ptr, r8={value,hash_table_base_ptr})
- Searches vector at [rcx+0x8] ({+8=begin, +0x10=end}, stride 0x48 entries {+0x00 qword hash, +0x08 byte kind})
- On miss: computes FNV-1a 64 hash (0xCBF29CE484222325 / 0x100000001B3), inserts into hash table
- Hash table entry (0x48 bytes): +0x00 16 bytes data, +0x10 qword, +0x18 qword, +0x20 qword, +0x28 qword, +0x30 byte 0, +0x38 qword, +0x40 byte kind (from entry+8) [V at 0x567B80A-0x567B80F]

### Call pattern at sub_567b570 call sites [V]
Every observed call site sets up a stack entry:
```
mov rax, [0x129Cxxxx]  ; entry+0x00 = qword from global
mov [rbp+0x2EF0], rax
mov byte ptr [rbp+0x2EF8], 0  ; entry+0x08 = kind = 0
...
mov qword ptr [rbp+0x2C00], 1  ; 3rd arg [r8+0] = 1
lea rax, [rbp+0x27A0]           ; 3rd arg [r8+8] = hash table base
mov [rbp+0x2C08], rax
lea rcx, [rbp+0x1DD8]           ; Declarator
lea rdx, [rbp+0x2EF0]           ; entry pointer
lea r8, [rbp+0x2C00]            ; 3rd arg
call 0x567B570
```
ALL observed call sites use kind=0 at entry+0x08. [UNVERIFIED: whether any call site uses non-zero kind]

### VV builder [V]
- sub_55f1450 (0x55F1450..0x563F594, size 0x2000+): calls sub_9d6d0 x66 (string copier), sub_567b570 x90 (bind/lookup), many sub_566xxxx/sub_567xxxx/sub_568xxxx (pass declaration functions)
- sub_9d6d0 (0x9D6D0..0x9D83E): general string builder/copier, 25,597 xrefs — NOT registration-specific
- At 0x55F383D: `lea r9,[0xF55A70A] "Shadow Cascades"; call 0x9D6D0` — builds pass name string

### RTX builder [V]
- sub_bbe2d50 (0xBBE2D50..0xBBF62CF, size 0x1357F): RTX frame builder/main pass declaration function per 6aq
- Calls sub_567b570 3 times at 0xBBE34B8, 0xBBE3545, 0xBBE35A9 — all with kind=0 at entry+0x08

### sub_bbce7b0 [V]
Range: 0xBBCE7B0..0xBBD16C3, size 0x2F13, calls sub_567b570 5x at 0xBBF004D, 0xBBF00D1, 0xBBF012F, 0xBBF01BA, 0xBBF02C1

### 6aq context (BGFX_MAP.md, NOT instruction-verified yet)
- Pass declaration functions: templates over Declarator<RenderContext> in dragon::framerenderer::drawutils
- 178 distinct drawutils::<fn>(Declarator<framerenderer::RenderContext>&, ...) signatures
- Counts: BindMaterialTexture x1110, BindFramebufferDepth x826, BindFramebufferColor x823, BindShaderBuffer x373, BindAccelerationStructure x49 (RTX only)
- Module passes: averageLuminance, localExposure, taau, clusterLights, volumeScattering, generateCubemapMips, rayTrace, fidelityfx::fsr1::_FSR1Draw; framerenderer::preprocessingutils
- Renderer-resource roots: FancyFrameRendererResources, VibrantVisualsFrameRendererResources, RTXMinecraftFrameRendererResources

## NOT YET DETERMINED [UNVERIFIED]
- Mapping of kind IDs (0-4) to specific Bind* types
- Exact start RVA of each Bind* mangled name string (only found as substrings)
- Registering function RVA per Bind* kind
- Full Declarator<RenderContext> object layout (partial: +0x20, +0x30, +0x50, +0xA10, +0xA78)
- Module names with registration call addresses
- BindAccelerationStructure string RVA

## TOOL REQUESTS
- A tool to search for strings across all PE sections with context (current rdis str shows empty content; had to read PE directly via PowerShell)
- A tool to dump raw bytes at an RVA (would have sped up string and jump table reading)
- None written yet
