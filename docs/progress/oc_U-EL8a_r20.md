# U-EL8a — L8a Texture group / ClientTexture / BedrockTexture / TexturePtr pack -> GPU path

**Output file:** docs/progress/oc_U-EL8a.md (fresh; no `_rN` suffix)
**Prior attempts:** oc_U-EL8a_r1..r19 read. r19 overclaimed CLOSES YES but the TexturePtr handle write was never proven. Orchestrator review: CLOSES NO; single blocking fact = MC_obj->TexturePtr handle write missing.

**Static chain:** NOT redone (issuance chain already proven [V] + [V live]).

---

## Proven issuance chain

texgroup_load/texload (r1, CPU-only) create CPU texture objects + queue them as "Deferred Texture Transactions"
-> endFrame `0x66232b0` calls flush `0x6632bf0` at `0x66244e7`/`0x66264e6` [BGFX_MAP.md 6dv]
-> `0x6632bf0` runs texture jobs through `0x12893d0` then job->vtbl[1] run + vtbl[0] delete [BGFX_MAP.md 6ev]
-> sub_12893d0 [`0x12893d0`..`~0x128b3c0`] iterates the deferred-texture job vector (stride 0x18; element+0x00 = shared_ptr, element+0x10 = MC_obj texture object): addrefs `[r13+8]` refcount, then:

```
0x128947d  mov rcx,[r13+0x10]    ; rcx = MC_obj = job+0x10
0x1289486  mov rax,[rcx]
0x1289489  mov rax,[rax+8]        ; vtbl[1] = job run
0x128948d  mov rdx,rbx            ; rdx = &[rbp-0x20]
0x1289490  call qword ptr [0xF99FFA0]   ; indirect/CFG call -> sub_4e05e50
-> returns to 0x1289496 nop      [V live: mc_root_4e05e50_callers.txt CALLER ret=0x1289496]
```

-> sub_4e05e50(rcx=MC_obj) -> createTexture [proven end-to-end].

---

## Answer table — TexturePtr handle write (the open question)

| # | Offset | Size | Site | Instruction | Meaning |
|---|--------|------|------|-------------|---------|
| 1 | `0x128947d` | 8 | sub_12893d0 deferred-job loop (element+0x10 = MC_obj) | `0x128947d  mov rcx,[r13+0x10]` | rcx = MC_obj texture object passed as job run arg |
| 2 | `0x4e05eb0` | 8 | sub_4e05e50 | `0x4e05eb0  mov rcx,[rdi+8]` | read TexturePtr mClientTexture shared_ptr @ MC_obj+0x8 |
| 3 | `0x4e05ec1` | 8 | sub_4e05e50 | `0x4e05ec1  mov [rbp+0x40],rcx` | mClientTexture copied to stack slot mClientTexture_storage |
| 4 | `0x4e05f70` | 8 | sub_4e05e50 | `0x4e05f70  lea r8,[rbp+0x40]` | address of mClientTexture_storage passed as out-param (r8) |
| 5 | `0x4e05f77` | 8 | sub_4e05e50 | `0x4e05f77  call 0xBC41420` | sub_bc41420(dragon_obj, &desc_out, &mClientTexture_storage) |
| 6 | `0xbc41454` | 8 | sub_bc41420 prologue | `0xbc41454  mov rbx,r8` | rbx = &mClientTexture_storage (TexturePtr storage addr) |
| 7 | `0xbc42e63` | 8 | sub_bc41420 | `0xbc42e63  mov [rbx-8],rax` | writes success flag [rbp+0x38], NOT [rbx]/mClientTexture, NOT MC_obj+0x8 |
| 8 | `0xc296e26` | 2 | dragon entry / sub_c296b50 | `0xc296e26  mov [rdi],ax` | GPU handle stored INTERNAL at dragon texture object+0x00 |
| 9 | `0x4e06010` | 8 | sub_4e05e50 | `0x4e06010  mov qword ptr [rsi],0` | null output; no handle returned to the TexturePtr |

Additional verified sites:
- `0x1289486  mov rax,[rcx]`, `0x1289489  mov rax,[rax+8]` — vtbl[1] run-function load in sub_12893d0.
- `0x4e05f52  cmp qword ptr [rbp+0x40],0` — null mClientTexture short-circuits to null output.
- `0x4e05fcf  cmp byte ptr [rbp+0x38],1` — sub_4e05e50 checks the success flag written by sub_bc41420.
- `0x4e0604b  mov rax,rsi` — sub_4e05e50 returns the (null) output pointer.
- `0xc296e99  movzx eax,word ptr [rdi]` — handle readback from dragon object+0x00 (0xFFFF = failure).
- createTexture issuance: `0xBC6A2B1  mov rax,[rax+0xD0]` (vtable slot 26 = createTexture `0xe8143c0`), `0xBC6A2C2  call qword ptr [0xF99FFA0]` (CFG thunk, ret=`0xBC6A2C8`, single caller [createtexture_callers.txt]); producer `0xbc73aaa  mov byte ptr [rbp+0x2C],0xE` (cmd 0x0E).

sub_4e05e50 NEVER stores `[rbp+0x40]` back to `MC_obj+0x8` (TexturePtr mClientTexture) — verified from the full listing: no `[rbp+0x40]->[rdi+8]` store after the call. sub_bc41420 has no `a0` (MC_obj) and never writes `[rbx]`/mClientTexture; its only rbx-relative write is the success flag at `[rbx-8]`. Handle does not reach TexturePtr/ClientTexture.

**SDK headers** (read-only, NOT pending): TexturePtr.h 32B `{mClientTexture shared_ptr +0x00, mResourceLocationPtr shared_ptr +0x10}`; BedrockTexture.h 48B three shared_ptr; ClientTexture.h empty carrier; TextureGroup.h stub. `src/sdk/` dir does not exist in repo.

---

## CLOSES?

**CLOSES? = NO**

**Single blocking fact:** The GPU handle returned by createTexture is stored only in the INTERNAL dragon texture object at `[object+0x00]` (`0xc296e26  mov [rdi],ax`) and is NEVER written to any TexturePtr/ClientTexture/BedrockTexture field. TexturePtr `mClientTexture` (`MC_obj+0x8`) is read (`0x4e05eb0  mov rcx,[rdi+8]`) and its address passed as out-param (`0x4e05f70  lea r8,[rbp+0x40]`) to sub_bc41420, but sub_4e05e50 never stores `[rbp+0x40]` back to `MC_obj+0x8`, and sub_bc41420 never writes to `[rbx]`/`MC_obj+0x8`. The handle does not reach TexturePtr/ClientTexture.

---

## NEXT

DONE — issue fully investigated; issuance chain proven, TexturePtr handle write proven ABSENT, CLOSES? = NO with single blocking fact documented.
