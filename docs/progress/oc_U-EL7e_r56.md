## NEXT
DONE

# U-EL7e — L7e sampler flag decode + sampler cache (6ax); texture/atlas management pending

## Scope of this step
Prior units decoded the D3D12 texture-management chain [V] (texture record table this+0xBDE178 stride 0xB8; createTexture 0xe8143c0, updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840, override/get/destroy 0xe815c30..0xe815fbf, destructor 0xe80f290, blit 0xe818bc0/blitSetup 0xe819750) and the createTexture issuance chain live through the bgfx command-byte-14 dispatcher (sub_bc73770 writes cmd 0x0E -> dispatcher -> createTexture 0xe8143c0; wrappers 0xbc73bf0/0xbc73ed0/0xbc74120; dragon entries 0xc296b50/0xc297000/0xc2a3d90/0xbc63c80; dragon entry 0xc296b50 <- 0xBC41B3E <- sub_bc41420; handle store [texture_obj+0x00] at 0xc296e26). The MC-side entry sub_4e05e50 (0x4E05E50) was captured live (mc_root_4e05e50_callers.txt, CALLER ret=0x1289496) but the static link into it went through [0xF99FFA0], which r37 showed is a read-only .rdata initializer = trampoline sub_eea6040 (`jmp rax`), not sub_4e05e50, with no writer.

Pending part (per r37): decode what rax holds at sub_eea6040's `jmp rax`, i.e. resolve the [0xF99FFA0] indirect target.

## Verified: [0xF99FFA0] trampoline and the observed call site

| offset | size | site | instr | meaning |
| 0xEEA6040 | 2 | 0xEEA6040 | `0xEEA6040  jmp rax` | sub_eea6040 entry = `jmp rax` trampoline; the indirect target is held in rax, not stored in [0xF99FFA0] [V] |
| 0xF99FFA0 | 8 | 0xEEA6060 | `0xEEA6060  jmp qword ptr [0xF99FFA0]` | [0xF99FFA0] is read-only .rdata; rdis resolves data_f99ffa0 = sub_eea6040, so this jumps to the `jmp rax` trampoline [V] |
| 0x1289486 | 4 | 0x1289486 | `0x1289486  mov rax,[rcx]` | rax = vtable pointer of the object at [r13+0x10] (set by 0x128947d `mov rcx,[r13+0x10]`) [V] |
| 0x1289489 | 4 | 0x1289489 | `0x1289489  mov rax,[rax+8]` | rax = vtable[1] = the real indirect target jumped to by sub_eea6040 (`jmp rax`) [V] |
| 0x1289490 | 6 | 0x1289490 | `0x1289490  call qword ptr [0xF99FFA0]` | indirect call through the trampoline; falls through to 0x1289496 (`nop`) [V] |

## Live-capture correlation
docs/data/live/mc_root_4e05e50_callers.txt line 3: `CALLER ret=0x1289496 first_hit=1` for the sub_4e05e50 (0x4E05E50) entry capture [V live]. The call at 0x1289490 returns to 0x1289496, so 0x1289490 is exactly the observed call site that enters sub_4e05e50, with rax = vtable[1] of object [r13+0x10] = sub_4e05e50 at runtime [V][V live].

## What this resolves / what remains open
Resolved [V]: sub_eea6040 is the `jmp rax` trampoline (0xEEA6040 `jmp rax`); [0xF99FFA0] holds its address (read-only .rdata, no writer); the observed live caller of sub_4e05e50 is the trampoline call at 0x1289490 returning to 0x1289496; rax at that call = vtable[1] of object [r13+0x10] (0x1289486 `mov rax,[rcx]` / 0x1289489 `mov rax,[rax+8]`).

Still open (single blocking fact): sub_4e05e50 is the dynamic target of a virtual call — rax = vtable[1] of object [r13+0x10] — and static analysis cannot bind vtable[1] to sub_4e05e50 without the object's dynamic type. [0xF99FFA0] holds the trampoline address, not sub_4e05e50, so the static texgroup_load(0x5421c90)/texload(0x58a1310) -> sub_4e05e50 link remains unproven statically. A live vtable read of object [r13+0x10], or a livecap at 0xEEA6040 reading rax (request rejected: 4 requests already pending; retry next unit), would settle it.

## CLOSES?
NO — single blocking fact: vtable[1] of object [r13+0x10] at the trampoline call 0x1289490 cannot be statically bound to sub_4e05e50 (dynamic object type); the [0xF99FFA0] trampoline target lives in rax. Everything below sub_4e05e50 (sub_bc41420 -> dragon 0xc296b50 -> wrapper 0xbc73bf0 -> sub_bc73770 cmd 0x0E -> dispatcher -> createTexture 0xe8143c0) and the handle store [texture_obj+0x00] at 0xc296e26 remain proven [V]/[V live].

## TOOL REQUESTS
None (no helper scripts written; livecapture at 0xEEA6040 to read rax is needed but could not be queued — 4 pending — retry next unit).
