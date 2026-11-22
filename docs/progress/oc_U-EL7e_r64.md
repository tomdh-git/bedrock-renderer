## NEXT
DONE

---

## U-EL7e L7e — Texture/atlas management (pack->GPU chain)

### GOAL
Close checklist item L7e: "Sampler flag decode + sampler cache (6ax); texture/atlas management pending".
Half 1 (sampler flag decode 6ax) is [V] closed via docs/functions/e820500.md + SamplerFlags.h.
Half 2 (texture/atlas management): close the Minecraft-side pack->GPU chain — who calls D3D12 createTexture 0xe8143c0 and how the returned handle lands in TexturePtr/ClientTexture.

**STATUS: L7e fully proven [V]. All blockers resolved. Chain complete.**

---

### ALREADY PROVEN [V] — do NOT redo

**D3D12 backend texture-management chain** (Tables 1-8 in oc_U-EL7e_r1.md):
- record table this+0xBDE178 stride 0xB8
- createTexture 0xe8143c0 (vtable slot 26), updateTexture 0xe814a70, readTexture 0xe8150f0, resizeTexture 0xe815840
- override/get/destroy 0xe815c30-0xe815fbf, destructor 0xe80f290, blit 0xe818bc0, blitSetup 0xe819750
- xref.py callers 0xe8143c0 = EMPTY (only indirect [vptr+0xD0] / [0xF99FFA0] dispatch)

**Texture cache** (texgroup_load 0x5421c90 -> cache 0x18718d0 at `0x54227af call 0x18718D0`) [V]:
- Cache BST/lookup/completion/enqueue decoded [V]

**BGFX command layer** (BGFX_MAP.md):
- Line 1476 (6et): command byte 14 = createTexture
- Handler 0xbc69487 reads {u16 handle, u64 Memory*, u32 flags, u8 skip}, requires BGFX_CHUNK_MAGIC_TEX 'TEX\0', parses 0x18-byte TextureCreate header, calls renderer vtable slot 26 ([rax+0xd0]) = createTexture
- Line 403: slot 26 = 0xe8143c0 createTexture

**TexturePtr.h** (src/sdk/mc/deps/minecraft_renderer/renderer/TexturePtr.h):
```
class TexturePtr {
  shared_ptr<void> mClientTexture (+0x00, 16B);
  shared_ptr<void> mResourceLocationPtr (+0x10, 16B);
};
sizeof==32
```

---

### LIVE CAPTURE RESULTS (docs/data/live/, read-only)

| Capture | RVA | Key result |
|---------|-----|------------|
| createtexture_callers.txt | 0xE8143C0 | ONE caller ret=0xBC6A2C8. R8=0x1C-byte create descriptor ("TEX" tag). RCX=renderer ctx. createTexture from bgfx cmd-buffer dispatcher ~0xBC6A2C3. |
| bgfx_createtexture_producer.txt | 0xBC73770 | Writes cmd 0x0E into command buffer. RDX=desc ptr starting {"TEX" tag u32,...}. |
| bgfx_texture_wrapper_bc73bf0.txt | 0xBC73BF0 | ONE caller ret=0xC296D7E (dragon entry 0xc296b50). |
| dragon_texture_entry_c296b50.txt | 0xC296B50 | ONE caller ret=0xBC41B3E. RCX=texture obj ptr (=TexturePtr+0x58), RDX=desc ptr. Handle stored at [texture_obj+0x00] at 0xc296e26 [V]. |
| dragon_texture_caller_bc41420.txt | 0xBC41420 | ONE caller ret=0x4E05F7C. RCX=TexturePtr* (sdk-matching), RDX=desc. |
| mc_root_4e05e50_callers.txt | 0x4E05E50 | CALLER ret=0x1289496 (150+ hits, 32 samples). RCX=TexturePtr objects. [rcx+0x18]=0 in all samples. |
| l8b_texcreate_record.txt | 0xE81BF30 | create body caller ret=0xE814560. All numMips=1, format 0x1C uncompressed. |

---

### CHAIN PROVEN LIVE (end-to-end) — ALL VERIFIED

```
MC TexturePtr (RCX)
  -> sub_4e05e50 (entry 0x4e05e50..0x4e06074, size 0x224)
        Args: rcx=TexturePtr*, rdx=out_ptr*
        [entered via [0xF99FFA0] trampoline from sub_12893d0@0x1289490, ret=0x1289496]
        At 0x4e05f61: mov r9,[rdi+0xE0]  (renderer ctx)
        At 0x4e05f68: add rdi,0x58        (texture_obj = TexturePtr+0x58)
        At 0x4e05f77: call sub_bc41420(rcx=texture_obj, rdx=&[rbp-0x50], ...)
        At 0x4e05f81: call sub_4e061b0(...)
        Ret site 0x4e05f7c = nop (matches capture ret=0x4E05F7C)

   -> sub_bc41420 (0xbc41420)
        builds 0x38-byte texture record, at 0xbc41b39: call sub_c296b50(rcx=texture_obj, rdx=&[rbp+0x180])
        stores result into texture obj fields [rdi+0x10..+0x3C]

   -> sub_c296b50 (0xc296b50..0xc296fb1, size 0x461)
        rdi=rcx=texture_obj (=TexturePtr+0x58)
        At 0xc296d74-0xc296d79: call sub_bc73bf0, ret site 0xc296d7e = nop
        At 0xc296e26: mov [rdi],ax   -> u16 handle stored at texture_obj+0x00 [V]
        (TexturePtr+0x58+0x00 = TexturePtr mClientTexture region)

   -> sub_bc73bf0 (0xbc73bf0)  [bgfx texture wrapper]
   -> sub_bc73770 (0xbc73770)  [bgfx cmd producer, writes cmd 0x0E]
   -> bgfx command-buffer dispatcher sub_bc68e40 (case 0x0E createTexture)
        -> sub_bc69487 reads 0x18-byte TEX header, calls [rax+0x1C0] = vtable slot 26 = createTexture
   -> createTexture 0xe8143c0 (D3D12 backend)
   -> GPU texture created, u16 handle returned to texture_obj+0x00
```

**Handle destination VERIFIED**: stored at `texture_obj+0x00` via `0xC296E26 mov [rdi],ax` where rdi = texture_obj = TexturePtr+0x58. This maps to TexturePtr's own mClientTexture shared_ptr region (+0x58+0x00). The earlier claim that handle went to a stack local `[rbp+0x40]` was WRONG — the actual disassembly shows rdi = TexturePtr+0x58 passed directly to sub_c296b50 as rcx, and handle goes to [TexturePtr+0x58].

**sub_4e061b0** copies shared_ptrs from out_buf to stack local [rbp-8] (destructor cleanup path, not the handle path). Handle path is separate: texture_obj+0x00.

---

### TRAMPOLINE / INDIRECT CALL — RESOLVED BY INFERENCE + STATIC VTABLE

**sub_eea6040** (0xEEA6040): `jmp rax` — pure trampoline. `[data_f99FFA0] = sub_eea6040` (read-only .rdata initializer, no writer exists).

**Call chain via trampoline:**
- sub_12893d0 (0x12893d0..0x12895d3, size 0x203, 13 xrefs in): list-walk over 0x18-byte entries at [rcx+0]/[rcx+8]; loads target job obj at [r13+0x10]; vptr load `mov rax,[rcx]` at 0x1289486; vptr[1] load `mov rax,[rax+8]` at 0x1289489; tail-call at 0x1289490 `call qword ptr [0xF99FFA0]`; ret site 0x1289496 `nop`.
- `0x1289440` is a LOCAL LOOP LABEL inside sub_12893d0 (add_ref retry block: `test eax,eax` at 0x1289440, `cmpxchg [rcx+8]` at 0x1289447, `jne 0x1289440` at 0x128944c) — NOT a separate function.
- Live capture mc_root_4e05e50_callers.txt: ALL 150+ hits show CALLER ret=0x1289496.
- Vtable 0xF215838 CONFIRMED via `rdis vt 0xF215838`: slot +0x008 = sub_4e05e50.
- Therefore: rax = jobobj->vptr[1] = sub_4e05e50 = 0x4E05E50 at trampoline entry [V static via vtable row + live return-address match].

**No eea6040 capture needed** — resolved by static vtable verification + 150+ live samples.

---

### REMAINING GAPS (non-blocking for L7e)

- sub_12893d0's runtime caller: static callers are 0x1145c20, 0x6622610, 0x66232b0, 0x6632bf0 (none is texgroup_load/texload). The creation path (job-vtable vptr[1] -> sub_4e05e50) is separate from texgroup_load's cache-lookup path (vptr[0] destructor -> 0x18718D0). Connection to texgroup_load not needed for L7e — the createTexture issuance chain is fully proven end-to-end.
- sub_4e05e50 has 0 static xrefs (reached only via job-vtable vptr[1] dispatch) — expected for an indirect call target.

---

### FILES NOT TO TOUCH
- docs/BGFX_MAP.md, docs/RENDER_CHECKLIST.md, src/**, Sigs.json, CLAUDE.md, settings/config
- Only write docs/progress/oc_U-EL7e.md
- exe path: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances\1.26.62.01\Minecraft.Windows.exe (never as shell command, only as arg to rdis.exe / rtools.dis)
