# UNIT U-B7b — D3D12 state transition helper 0xe82d960 + tracker entries (BGFX_MAP 6ae)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Header named in unit: src/sdk/mc/deps/bgfx/d3d12/D3D12Context.h (struct TrackerEntry + TrackerOffsets + CreateTexture call-site note, lines 162-186).
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.
Raw artifacts: docs/progress/oc_U-B7b_listing_utf8.txt (rdis dis 0xe82d960 800), oc_U-B7b_callers.txt (xref.py callers), oc_U-B7b_descscan2_rax_utf8.txt (descscan2 --reg rax), oc_U-B7b_eea6040_utf8.txt (the import thunk).

## NEXT
Resume at: run `python tools/sigs/verify_oc.py docs/progress/oc_U-B7b.md` to validate every quoted `0xRVA  instr` line; then finalize unit.

## (1) `rdis fn 0xe82d960` size; argument registers at entry + first ~50 instructions

`rdis fn 0xe82d960` → `sub_e82d960 [0xe82d960..0xe82dcb9) size 0x359 19 xrefs in` ([V] rdis fn output).

Signature guess (from CreateTexture call-site in header line 149 and entry register map):
`void transition(Tracker* t, ID3D12GraphicsCommandList* list, u16 handle, u32 newState)` — 0xe82d960.
- rcx = arg1 = Tracker* t → saved to r14
- rdx = arg2 = ID3D12GraphicsCommandList* list → saved to rsi
- r8  = arg3 = u16 handle → zero-extended to ebx
- r9  = arg4 = u32 newState → saved to edi and ebp

First ~50 instructions (quoted verbatim from listing):
```
e82d960  push r15                                     
e82d962  push r14                                     
e82d964  push rsi                                     
e82d965  push rdi                                     
e82d966  push rbp                                     
e82d967  push rbx                                     
e82d968  sub rsp,0x48                                 
e82d96c  mov rax,[0x1230A0C0]                          ; stack cookie
e82d973  xor rax,rsp                                  
e82d976  mov [rsp+0x40],rax                           
e82d97b  cmp r8w,0xFFFF                                ; handle 0xFFFF -> skip
e82d980  je 0xE82DC8A                                  ; -> loc_e82dc8a (return)
e82d986  mov edi,r9d                                   ; edi = newState (arg4)
e82d989  mov ebp,r8d                                   ; ebp = newState copy
e82d98c  mov rsi,rdx                                   ; rsi = list (arg2)
e82d98f  mov r14,rcx                                   ; r14 = tracker t (arg1)
e82d992  lea r15,[rcx+8]                               ; r15 = &t->states
e82d996  movzx ebx,r8w                                 ; ebx = handle (arg3, zero-extended)
e82d99a  mov rcx,r15                                  
e82d99d  mov rdx,rbx                                  
e82d9a0  call 0xE83AED0                                ; tracker entry lookup -> rax = entry*
e82d9a5  cmp byte ptr [rax+8],0                        ; entry->tracked == 0?
e82d9a9  je short 0xE82DA05                            ; -> first-use tail call 0xe83b0e0
e82d9ab  mov rcx,r15                                  
e82d9ae  mov rdx,rbx                                  
e82d9b1  call 0xE83AED0                                ; reload entry*
e82d9b6  cmp [rax+4],edi                               ; entry->currentState == newState?
e82d9b9  jne short 0xE82DA36                           ; -> transition path
e82d9bb  cmp edi,8                                     ; newState == UNORDERED_ACCESS?
e82d9be  jne 0xE82DC8A                                 ; -> return, no barrier
e82d9c4  mov rdi,[r14]                                 ; rdi = t->textureTable (for UAV barrier resource lookup)
e82d9c7  mov rcx,rdi                                  
e82d9ca  mov rdx,rbx                                  
e82d9cd  call 0xE83ABB0                                ; guarded paged-array bounds/helper
e82d9d2  cmp ebx,0x1000                                ; handle >= 0x1000 -> overflow page walk
...
loc_e82da05:  ; first-use (entry->tracked==0)
e82da20  mov edx,ebp                                   ; edx = newState
e82da22  mov r8d,edi                                   ; r8d = newState
e82da25  add rsp,0x48
e82da29  pop rbx
e82da2a  pop rbp
e82da2b  pop rdi
e82da2c  pop rsi
e82da2d  pop r14          ; 2-byte REX pop, spans e82da2d-e82da2e (no instr starts at e82da2e)
e82da2f  pop r15          ; 2-byte REX pop, next instr at e82da31
e82da31  jmp 0xE83B0E0                                 ; firstUse(t, handle, newState) - no barrier
loc_e82da36:  ; transition (currentState != newState)
e82da41  mov ebp,[rax+4]                               ; ebp = old currentState
e82da4f  mov [rax+4],edi                               ; entry->currentState = newState
...
loc_e82dc6d:  ; barrier emission (both transition and UAV paths merge here)
e82dc6d  mov rax,[rsi]                                 ; rax = command-list vtable ptr
e82dc70  mov rax,[rax+0xD0]                            ; rax = vtable[0xD0] = ResourceBarrier
e82dc77  lea r8,[rsp+0x20]                             ; r8 = &barrier desc
e82dc7c  mov rcx,rsi                                   ; rcx = list (this)
e82dc7f  mov edx,1                                     ; edx = NumBarriers = 1
e82dc84  call qword ptr [0xF99FFA0]                    ; import thunk -> jmp rax -> ResourceBarrier(list,1,&barrier)
loc_e82dc8a:  ; epilog / return
e82dc8a  mov rax,[rsp+0x40]                            
e82dc8f  xor rax,rsp                                  
e82dc92  mov rcx,[0x1230A0C0]                          
e82dc99  cmp rcx,rax                                  
e82dc9c  jne short 0xE82DCAB                           ; stack-cookie fail -> 0xe951550
e82dc9e  add rsp,0x48                                  
e82dca2  pop rbx                                      
e82dca3  pop rbp                                      
e82dca4  pop rdi                                      
e82dca5  pop rsi                                      
e82dca6  pop r14                                      
e82dca8  pop r15                                      
e82dcaa  ret                                           
```

Control flow summary:
- handle == 0xFFFF → return (e82d97b/980), no tracker, no barrier.
- entry->tracked == 0 → tail-call `firstUse 0xe83b0e0(t, handle, newState)` (e82da31), sets initialState+currentState=newState, no barrier.
- entry->currentState == newState:
  - newState != 8 → return, no barrier (e82d9bb/9be).
  - newState == 8 → UAV barrier (type 2), resource only, no before/after change.
- else → TRANSITION barrier (type 0): currentState updated to newState, barrier {type 0, resource, subresource 0xFFFFFFFF, before=old, after=new}.

## (2) Tracker entry layout — fields read/written on the entry

Source: header `TrackerEntry` (12 bytes, lines 169-175) + `descscan2.py --start 0xe82d960 --end 0xe82dcb9 --reg rax --events` + listing.

| Offset | Size | Direction | Meaning | Evidence (RVA) | Tag |
|--------|------|-----------|---------|----------------|-----|
| +0x00 | u32 | W (on first use) | `initialState`, written same value as current on first use via `firstUse 0xe83b0e0(t,handle,newState)` | header line 170; first-use tail call e82da31 with edx=r8d=newState | [V static header] / [I exact write site inside 0xe83b0e0 not re-verified here] |
| +0x04 | u32 | R/W | `currentState` (D3D12_RESOURCE_STATES) | R: `cmp [rax+4],edi` e82d9b6; R: `mov ebp,[rax+4]` e82da41; W: `mov [rax+4],edi` e82da4f | [V] |
| +0x08 | u8 | R | `tracked` flag (0 = not yet tracked) | R: `cmp byte ptr [rax+8],0` e82d9a5 | [V] |
| +0x0C | u8[3] | — | pad | never accessed | [?] |

`descscan2` (rax-tracked) read map corroborates: `+0x004 dword cmp @e82d9b6`, `+0x008 byte cmp @e82d9a5`, `+0x0d0 qword mov @e82dc70` (the latter is the command-list vtable load, not tracker). GAPS 0x9-0xd0 unread because rax is reassigned to the texture-record resource pointer mid-function, so descscan's single-register model can't attribute tracker +0x0 writes here — those come from `0xe83b0e0` (firstUse) which is outside this function's body. [I]

Tracker-level (not per-entry) context from header `TrackerOffsets` (lines 176-185): kTextureTable=0x00 (ptr to texture table, used for the resource lookup), kStates=0x08 (paged array of TrackerEntry), kEntriesPerPage=0x1000, kPageBytes=0xC000, kTouchedList=0xC028 (u16 handles first-used since reset, appended by 0xe83b0e0).

Resource pointer (read from the texture record via the tracker's texture table, same paged walk as createTexture): `mov rax,[rcx]` at e82dc33/e82dc5c → stored `[rsp+0x28]` as the barrier's `pResource`. [V]

Barrier description built on the stack (rsp+0x20..rsp+0x38), direction W:
- [rsp+0x20] u32 = barrier type: 0 (TRANSITION, e82dc36 path) or 2 (UAV, e82dc5f path) [V]
- [rsp+0x28] u64 = pResource (ID3D12Resource*) [V]
- [rsp+0x30] u32 = Subresource = 0xFFFFFFFF (e82dc44) [V]
- [rsp+0x34] u32 = StateBefore (old currentState, ebp) — transition only (e82dc4c) [V]
- [rsp+0x38] u32 = StateAfter (newState, edi) (e82dc50) [V]

## (3) State mapping to D3D12_RESOURCE_STATES

The function does NOT hardcode most D3D12_RESOURCE_STATES values; `newState` is the caller-supplied 4th arg (edi). The only state-Enum immediate compared inside 0xe82d960 (range e82d960..e82dcb9) is:

| Immediate | Compared at | Meaning | D3D12_RESOURCE_STATES name | Tag |
|-----------|-------------|---------|----------------------------|-----|
| 8 | `cmp edi,8` e82d9bb | special-case: when current==newState==8 emit a UAV barrier instead of a transition | `0x8 D3D12_RESOURCE_STATE_UNORDERED_ACCESS` | [V] |

The following values do NOT appear as immediates within 0xe82d960 (confirmed by scanning the full function range e82d960..e82dcb9); they are supplied by callers via `newState`:
- `0x1 D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER` — [V absent; caller-supplied]
- `0x4 D3D12_RESOURCE_STATE_RENDER_TARGET` — [V absent; caller-supplied]
- `0x10 D3D12_RESOURCE_STATE_DEPTH_WRITE` — [V absent; caller-supplied]
- `0x80 D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE` — [V absent; caller-supplied]
- `0x400 D3D12_RESOURCE_STATE_COPY_DEST` — [V absent; caller-supplied]

Note: the `0x400`/`0x10`/`0x80` hits elsewhere in the 800-instruction listing (e82e3c6, e82e4a7, e82e7c4) lie beyond e82dcb9 (i.e. in the functions following 0xe82d960) and are NOT part of this unit.

UAV special case (state 8): if `entry->currentState == newState == 8`, no state change is stored; a type-2 UAV barrier `{type 2, resource}` is emitted (e82dc5f sets [rsp+0x20]=2). Otherwise (current != new) a type-0 TRANSITION barrier is emitted with before=old, after=new. [V]

## (4) Where the barrier is emitted; batching

Emission site (both transition and UAV paths converge at loc_e82dc6d):
```
e82dc6d  mov rax,[rsi]                                 ; rax = command-list object's vtable pointer
e82dc70  mov rax,[rax+0xD0]                            ; rax = vtable[0xD0] = ResourceBarrier
e82dc77  lea r8,[rsp+0x20]                             ; r8 = &D3D12_RESOURCE_BARRIER desc
e82dc7c  mov rcx,rsi                                   ; rcx = ID3D12GraphicsCommandList* (this)
e82dc7f  mov edx,1                                     ; edx = NumBarriers = 1
e82dc84  call qword ptr [0xF99FFA0]                    ; import thunk
```

The thunk at 0xF99FFA0 resolves to `sub_eea6040` which is a single `jmp rax` (0xeea6040: `jmp rax`), i.e. a tail-call that transfers to `rax` = vtable[0xD0] with rcx/list, rdx=1, r8=&barrier still in place. So the effective call is `ResourceBarrier(list, NumBarriers=1, &barrier)`. [V]

Slot identification: vtable byte offset 0xD0 = index 26 counting from the vtable start (includes IUnknown's QueryInterface/AddRef/Release at 0,1,2). The header independently asserts `list vtbl +0xD0 = ResourceBarrier(1, &barrier)` (D3D12Context.h line 167, [V static]). Observed offset 0xD0 at e82dc70 [V]. The canonical D3D12GraphicsCommandList slot number beyond offset 0xD0 is not re-derived here. [UNVERIFIED: 0xe82d960 exact canonical vtable slot index for ResourceBarrier beyond observed offset 0xD0]

Batching: `edx = 1` (NumBarriers=1) at e82dc7f on every emission. This function emits exactly ONE barrier per invocation; it does NOT batch multiple barriers internally. Callers invoke it once per resource that needs a transition (submit/draw/executor loops may call repeatedly). [V]

## (5) Callers (`xref.py callers 0xe82d960`, first 15 with identification)

`xref.py callers 0xe82d960` returned 11 direct callers. (`rdis fn` reported "19 xrefs in"; the remaining 8 are indirect/vtable/thunk references not resolved by xref.py callers — [UNVERIFIED: 0xe82d960 whether those 8 are additional indirect call sites].)

| # | Caller RVA | Size | Identification | Evidence | Tag |
|---|------------|------|----------------|----------|-----|
| 1 | 0xe80f680 | 0x196 | D3D12 submit RTX override | frame_path_functions.tsv L842 "D3D12 submit RTX override" | [V] |
| 2 | 0xe8143c0 | 0x2e1 | createTexture (vtable slot 26) | D3D12Context.h line 149 calls 0xe82d960; BGFX_MAP / header | [V] |
| 3 | 0xe814a70 | 0x674 | updateTexture (vtable slot 28) | BGFX_MAP.md L404; d3d12_vtable L29 | [V] |
| 4 | 0xe8150f0 | 0x498 | readTexture (vtable slot 30) | BGFX_MAP.md L405; d3d12_vtable L31 | [V] |
| 5 | 0xe8176a0 | 0xeb | setFrameBufferAttachments (slot 40) | D3D12Context.h L26 | [V] |
| 6 | 0xe817880 | 0x37b | createWindowFrameBuffer (slot 39) | D3D12Context.h L25 | [V] |
| 7 | 0xe818bc0 | 0xb87 | blit (slot 51) | BGFX_MAP.md L411; d3d12_vtable L52 | [V] |
| 8 | 0xe820910 | 0x80c | clear / RT transitions | BGFX_MAP.md L79; frame_path_functions.tsv L857 | [V] |
| 9 | 0xe821120 | 0xc3c3 | draw executor item loop | D3D12Context.h L14 | [V] |
| 10 | 0xe82e230 | 0x4d91 | submit (slot 50) | D3D12Context.h L12 | [V] |
| 11 | 0xe8403d0 | 0xaa5b | RTX/DLSS (slot 64, root-signature caller) | D3D12Context.h RtxRootSignature (callers 0xe83d440 + 0xe8403d0) | [V] |

Open questions / UNVERIFIED:
- [UNVERIFIED: 0xe82d960] canonical D3D12GraphicsCommandList vtable slot index for ResourceBarrier beyond observed byte offset 0xD0.
- [UNVERIFIED: 0xe82d960] the 8 xrefs not returned as direct callers by xref.py (indirect/vtable/thunk call sites).
- [UNVERIFIED: 0xe83b0e0] exact field writes (initialState vs currentState) inside firstUse; header asserts both set to newState on first use.
- Tracker +0x0 initialState write site within 0xe82d960 could not be attributed by descscan2 because rax is reassigned to the texture-record pointer; it occurs in 0xe83b0e0.

## Verification artifacts
- docs/progress/oc_U-B7b_listing_utf8.txt — `rdis ... dis 0xe82d960 800`
- docs/progress/oc_U-B7b_callers.txt — `python tools/sigs/xref.py callers 0xe82d960`
- docs/progress/oc_U-B7b_descscan2_rax_utf8.txt — `python tools/sigs/descscan2.py --start 0xe82d960 --end 0xe82dcb9 --reg rax --events`
- docs/progress/oc_U-B7b_eea6040_utf8.txt — `rdis ... dis 0xeea6040 80` (import thunk = `jmp rax`)

Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-B7b.md` (next step).
