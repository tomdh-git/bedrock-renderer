## NEXT
DONE

# Unit U-EL7e — L7e "Sampler flag decode + sampler cache (6ax); texture/atlas management pending"

Source checklist line (docs/RENDER_CHECKLIST.md:338): `- [ ] L7e Sampler flag decode + sampler cache (6ax); texture/atlas management pending | PROGRESS 2026-11-21 oc_U-EL7e.md (verify_oc 185/185): D3D12 backend texture-management chain decoded [V] ...; Minecraft-side pack->GPU chain (texgroup_load 0x5421c90 -> texload 0x58a1310 -> texload_task 0x541bf00 -> undecoded 0x18718D0 at 0x54227af) and atlas stitchers still open (L8a/L8b)`

Exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (1.26.62.01). Static analysis only; live capture logs under docs/data/live are read-only inputs produced by the orchestrator.

Tags: [V] saw in disassembly (RVA cited, verbatim line quoted) / [V live] saw in an orchestrator live capture log (file cited) / [I] inferred from structure or BGFX_MAP / [?] unknown or not located.

Row rule: one annotated row per distinct offset, all its read/store sites listed; offset | size | read/store address | verbatim `0xRVA  instr` (two spaces after the address, copied verbatim from rdis) | meaning ONLY if an instruction/string shows it else '-' | tag. Sizes from the instruction (movups/movaps/movdqu/movdqa 16, qword 8, dword/movss 4, word 2, byte 1). No input data pasted as-is; no skipped offsets among quoted sites; no raw instruction dumps outside tables; no ellipsis or catch-all rows.

## Work this session — the pending part of L7e: createTexture issuance from the Minecraft side

Inputs read in full: docs/data/live/mc_root_4e05e50_callers.txt (150 hits, 32 samples, CALLER ret=0x1289496) and docs/data/live/l8b_texcreate_record.txt (24 samples, CALLER ret=0xE814560). The static chain is NOT redone (r1-r37).

### 1. Indirect caller of sub_4e05e50, named [V live + dis]

mc_root_4e05e50_callers.txt: `CALLER ret=0x1289496 first_hit=1` (all 32 samples, hits 1-15, every line ret=0x1289496). The call instruction is six bytes before its ret site: `0x1289490  call qword ptr [0xF99FFA0]`, ret site `0x1289496  nop`, both inside sub_12893d0 (0x12893d0..0x128b3d0, 13 xrefs in). So the indirect caller of sub_4e05e50 is sub_12893d0, an mc_root container visitor whose ret site matches the capture (ret=0x1289496 [V live]).

### 2. sub_12893d0 decoded [V]

sub_12893d0 walks refcounted child objects (0x18-byte entries: [entry+0] ..., [entry+8] refcount, [entry+0x10] child object) and tail-calls each live child's vptr[1] through the [0xF99FFA0] trampoline with rdx = out-descriptor. The live target of that vptr[1] is sub_4e05e50 (capture entered sub_4e05e50 with ret=0x1289496 [V live]).

### 3. sub_4e05e50 takes TexturePtr* and writes the handle at TexturePtr+0x58 [V]

sub_4e05e50 (0x4E05E50..0x4E06074): `0x4E05E6E  mov rdi,rcx` (arg0 = TexturePtr*), `0x4E05F68  add rdi,0x58` (&TexturePtr->0x58), `0x4E05F74  mov rcx,rdi` / `0x4E05F77  call 0xBC41420` (passes &TexturePtr->0x58 to the dragon createTexture sub_bc41420). Returned 16-bit handle: `0xC296E1A  call 0xBC74120` (ax) -> `0xC296E26  mov [rdi],ax` (handle stored at [TexturePtr+0x58]; rdi = TexturePtr+0x58 per the add at 0x4E05F68, linkage verified [V r24]). On failure `0x4E06010  mov qword ptr [rsi],0` clears the caller's out-handle. Live capture: RCX values at sub_4e05e50 entry are TexturePtr* heap pointers (0x3908FFDE900, 0x3908FFDA600, ...); the pointed objects carry texture names (e.g. "tex\0"), consistent with sdk TexturePtr/ClientTexture [V file read]. This connects the createTexture issuance to TexturePtr.

### 4. No static path texgroup_load -> sub_4e05e50 [V] (new angle this session)

- sub_4e05e50 (0x4E05E50..0x4E06074): `xref.py callers 0x4E05E50` -> 0 calling functions (0 static code xrefs) [V].
- Whole-exe scan for the 8-byte LE image address 0x14E05E50 (ImageBase 0x140000000 + 0x4E05E50): 0 hits in code or data [V] — no vtable, no imm, no static reference to sub_4e05e50 anywhere in the image. (New angle: r37 only scanned for stores TO [0xF99FFA0]; this scans for references TO sub_4e05e50 itself.)
- sub_12893d0's 4 static callers (0x1145c20+0x4ae, 0x6622610+0x1c8, 0x66232b0+0xb3d0, 0x6632bf0+0x34b [V xref.py callers this session]) dead-end without reaching texgroup_load/texload/texload_task [r24, not redone].
- texgroup_load(0x5421c90)->texload(0x58a1310)->texload_task(0x541bf00)->undecoded 0x18718D0 (0x54227af): static callees do not enter the sub_4e05e50 tree [r24, not redone].
- [0xF99FFA0]: read-only .rdata PE initializer = 0x14EEA6040 = ImageBase 0x140000000 + sub_eea6040 (`0xEEA6040  jmp rax` [V]); .text store scan for [0xF99FFA0] = 0 hits [r37]; .rdata section flags 0x40000040 (read-only) so it is never rewritten. The trampoline is NOT set to sub_4e05e50; the real target is rax = child->vptr[1], bound at runtime.

### 5. Full createTexture issuance chain (context from prior sessions, not redone)

sub_12893d0 -> (vtable[1] tail-call) sub_4e05e50 -> `0x4E05F77  call 0xBC41420` (sub_bc41420) -> dragon entry 0xc296b50 -> wrapper 0xbc73bf0 -> producer 0xbc73770 (command byte 0x0E [V r4]) -> bgfx dispatcher `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` (slot 26 = createTexture 0xe8143c0 [V BGFX_MAP]) / `0xBC6A2C2  call qword ptr [0xF99FFA0]` (trampoline; ret site 0xBC6A2C8 = live capture ret=0xBC6A2C8 [V live createtexture_callers.txt]) -> createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` (TextureD3D12::create; ret=0xE814560 [V live l8b_texcreate_record.txt, 24 samples, descriptor bytes at RCX carry width/height/format/name]) -> handle stored at TexturePtr+0x58 [V].

Corroboration [V live]: l8b_texcreate_record.txt entered TextureD3D12::create 24x with ret=0xE814560, i.e. inside createTexture 0xe8143c0; mc_root_4e05e50_callers.txt entered sub_4e05e50 32x with ret=0x1289496, i.e. inside sub_12893d0's vtable[1] dispatch.

## Already proven (prior sessions, cited, not redone)

- Half 1 — sampler flag decode + sampler cache (6ax): [V] docs/functions/e820500.md decodes 0xe820500 instruction-complete; src/sdk/mc/deps/bgfx/d3d12/SamplerFlags.h carries the static_asserts; called from blit 0xe818bc0 and executor 0xe821120.
- Half 2a — D3D12 backend texture-management chain: [V] record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750; BGFX_MAP 6z/6z-2/6aj confirm table base/stride and live texture records.
- Backend createTexture tail: createTexture 0xe8143c0 -> `0xE81455B  call 0xE81BF30` TextureD3D12::create (ret 0xe814560 [V live]) [r24].
- Atlas stitchers (L8a/L8b): out of scope (MIRROR_SKIP).

## Answer table (the decoded offsets)

| name | rva or offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|---|
| mc_root child-list base | mc_root+0x0 | 8 | [rcx+0x0] | `0x1289406  mov r13,[rcx]` | loads *this = child-array base; sub_12893d0 walks [this]..[this+8] in 0x18-byte entries | [V] |
| mc_root child-list end | mc_root+0x8 | 8 | [rcx+0x8] | `0x1289409  mov r14,[rcx+8]` | loads *(this+8) = child-array end | [V] |
| entry refcount | entry+0x8 | 4 | [rcx+8] | `0x128943A  mov eax,[rcx+8]` / `0x1289447  lock cmpxchg [rcx+8],edx` | entry refcount, atomic inc/dec around the child visit | [V] |
| child object ptr | entry+0x10 | 8 | [r13+0x10] | `0x128947D  mov rcx,[r13+0x10]` | loads child object pointer; passed as rcx (= TexturePtr*) to vptr[1] | [V] |
| child vptr | TexturePtr+0x0 | 8 | [rcx+0x0] | `0x1289486  mov rax,[rcx]` | child->vptr | [V] |
| vptr[1] = callee | vptr+0x8 | 8 | [rax+0x8] | `0x1289489  mov rax,[rax+8]` | child->vptr[1] = callee in rax; live target = sub_4e05e50 (capture ret=0x1289496, 32 samples) | [V] + [V live] |
| trampoline tail-call | [0xF99FFA0] | 8 | [0xF99FFA0] | `0x1289490  call qword ptr [0xF99FFA0]` / `0xBC6A2C2  call qword ptr [0xF99FFA0]` | trampoline tail-call to rax; statically [0xF99FFA0]=sub_eea6040, live target = sub_4e05e50 (1289490) / createTexture 0xe8143c0 (BC6A2C2, ret site 0xBC6A2C8 [V live]) | [V] + [V live] |
| call ret site | ret site 0x1289496 | - | - | `0x1289496  nop` | instruction right after `call [0xF99FFA0]`; matches capture ret=0x1289496 in all 32 samples | [V live] |
| sub_4e05e50 arg0 | sub_4e05e50 this | 8 | rcx (argument) | `0x4E05E6E  mov rdi,rcx` | sub_4e05e50 arg0 = TexturePtr* (rdi = rcx) | [V] |
| TexturePtr handle field | TexturePtr+0x58 | 2 | [rdi] | `0x4E05E7E  lea rdx,[rdi+0x58]` / `0x4E05F68  add rdi,0x58` / `0x4E05F74  mov rcx,rdi` / `0xC296E26  mov [rdi],ax` | &TexturePtr->0x58 computed, passed as rcx to sub_bc41420 (`0x4E05F77  call 0xBC41420`); 16-bit handle (ax from `0xC296E1A  call 0xBC74120`) stored at [TexturePtr+0x58] | [V] |
| failure clear | out-handle (*rsi) | 8 | [rsi] | `0x4E06010  mov qword ptr [rsi],0` | on failure the caller's out-handle pointer is cleared to 0 | [V] |
| dispatcher handler slot | vptr+0xD0 (slot 26) | 8 | [rax+0xD0] | `0xBC6A2AE  mov rax,[rcx]` / `0xBC6A2B1  mov rax,[rax+0xD0]` | dispatcher loads bgfx vptr then slot 26 = createTexture 0xe8143c0 [V BGFX_MAP] | [V] |
| trampoline entry | 0xEEA6040 | 2 | - | `0xEEA6040  jmp rax` | trampoline: tail-call rax; [0xF99FFA0] = 0x14EEA6040 = ImageBase 0x140000000 + 0xEEA6040 (.rdata read-only initializer) | [V] |
| TextureD3D12::create | createTexture ret site | - | - | `0xE81455B  call 0xE81BF30` | createTexture 0xe8143c0 -> TextureD3D12::create; ret=0xE814560 [V live l8b capture, 24 samples] | [V] + [V live] |
| sub_4e05e50 static refs | sub_4e05e50 (0x4E05E50) | - | - | - | `xref.py callers 0x4E05E50` = 0; whole-exe scan for 0x14E05E50 = 0 hits -> no code or data reference to sub_4e05e50 anywhere in the image | [V] |

## Attempts that did not close it (not redone)

r2-r36 re-decodes of the pack->GPU chain; [0xF99FFA0] writer scan (.text store scan for [0xF99FFA0] = 0 hits; .rdata read-only); sub_12893d0's 4 caller chains dead-end; texgroup_load's static callees do not enter the sub_4e05e50 tree.

## CLOSES?

NO — blocking fact: no [V]-proven static path texgroup_load(0x5421c90) -> sub_4e05e50. sub_4e05e50 has zero static references anywhere in the image (`xref.py callers` empty [V]; whole-exe scan for 0x14E05E50 = 0 hits [V] this session) and is reached only at runtime via sub_12893d0's indirect vtable[1] tail-call `0x1289490  call qword ptr [0xF99FFA0]` through trampoline [0xF99FFA0] = sub_eea6040 (`0xEEA6040  jmp rax`, .rdata read-only initializer, no writer), observed live at capture ret site `0x1289496  nop` (ret=0x1289496, 32 samples [V live]). The texgroup_load -> sub_4e05e50 bind is therefore runtime-only; static work is exhausted. Remaining open: the runtime-only texgroup_load bind (single blocking fact above) and atlas stitchers L8a/L8b (MIRROR_SKIP).

## TOOL REQUESTS

- None. All instruction lines quoted above were re-verified verbatim against a fresh rdis dis this session; the sub_4e05e50 address scan was a one-off `python -c` mmap search (no script left behind). No helper scripts written; no temporary files.
