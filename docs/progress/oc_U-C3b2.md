# UNIT U-C3b2 — FNV-1a 64 task-kind hashing (checklist C3b, BGFX_MAP 6ad)

Source exe: C:\Users\Atomi\AppData\Local\LeviLauncher\Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01). RVAs relative to image base.
Tags: [V] = seen in disassembly (cite RVA), [I] = inferred, [?] = unknown. Nothing invented.

## NEXT
Step 1: find the hash function: `tools/rdis/target/release/rdis.exe "C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe" imm 0xcbf29ce484222325` and `imm 0x100000001b3` (list sites), pick the task-kind hasher (see BGFX_MAP 6ad for names UseAlphaRewrite, LightWorldSpaceDirection).

## Step 1: Hash function sites [V]
Ran imm searches for FNV-1a 64 constants:
- offset_basis 0xcbf29ce484222325: 11612 hits across many functions
- prime 0x100000001b3: 7339 hits across many functions

Key co-occurrence sites (both constants in same function):
- 0x76d50 (sub_76d50): hash table lookup with FNV-1a 64 over 4-byte key at [r8]
- 0x772e0 (sub_772e0): hash table init/resize with FNV-1a 64 over 16-byte key at [rax+0x10]
- 0xb1ef0 (sub_b1ef0): similar hash table lookup with 4-byte key
- 0xed020 (sub_ed020): hash table remove with 8-byte key
- **0x66a02d0 (sub_66a02d0): FNV-1a 64 over variable-length string (std::string {ptr,len}) — 129 xrefs [V]**

Per BGFX_MAP 6ad and 6ez: "0x66a02d0 is FNV-1a 64 of a string (static, 62.01) [V]. The helper called 72 times by the ItemInHand extractor (and in many extractors/handlers) computes `h = 0xcbf29ce484222325; for each byte: h ^= b; h *= 0x100000001b3` over a `std::string` {char*, len}: **FNV-1a 64**."

Callers of 0x66a02d0 [V from rdis callers]:
- sub_6646980 (Item visitor) — 1 site
- sub_666aca0 — 2 sites
- **sub_6698e30 (ItemInHand extractor) — 72 sites [V]**
- sub_66ea3d0 (terrain extractor) — 36 sites
- sub_6745440 (Weather extractor) — 9 sites
- sub_674a3a0 (UI renderer) — 9 sites

This is the **task-kind hasher** — it hashes uniform/texture names (UseAlphaRewrite, LightWorldSpaceDirection, etc.) to 64-bit task kinds.

## Step 2: Listing of the hash function 0x66a02d0 [V]

```
0x66a02d0  push rbp
0x66a02d1  push r15
0x66a02d3  push r14
0x66a02d5  push r13
0x66a02d7  push r12
0x66a02d9  push rsi
0x66a02da  push rdi
0x66a02db  push rbx
0x66a02dc  sub rsp,0x88
0x66a02e3  lea rbp,[rsp+0x80]
0x66a02eb  mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE
0x66a02f3  mov r11,r8                    ; r8 = string pointer (std::string*)
0x66a02f6  mov rsi,rcx                   ; rcx = output u64*
0x66a02f9  mov r8,[rdx+8]                ; rdx = string object, r8 = string length
0x66a02fd  mov rdi,0x100000001B3         ; FNV prime
0x66a0307  test r8,r8
0x66a030a  je short 0x66A032A
0x66a030c  mov rax,[rdx]                 ; rax = string data pointer
0x66a030f  mov ecx,r8d
0x66a0312  and ecx,3
0x66a0315  cmp r8,4
0x66a0319  jae short 0x66A0339
0x66a031b  mov rdx,0xCBF29CE484222325    ; FNV offset_basis
0x66a0325  xor r9d,r9d
0x66a0328  jmp short 0x66A0391

; ... (short string handling) ...

0x66a0339  and r8,0xFFFFFFFFFFFFFFFC     ; align length to 4
0x66a033d  mov rdx,0xCBF29CE484222325    ; FNV offset_basis
0x66a0347  xor r9d,r9d
0x66a034a  nop [rax+rax]

0x66a0350  movzx r10d,byte ptr [rax+r9]  ; load 4 bytes
0x66a0355  xor r10,rdx
0x66a0358  imul r10,rdi
0x66a035c  movzx edx,byte ptr [rax+r9+1]
0x66a0362  xor rdx,r10
0x66a0365  imul rdx,rdi
0x66a0369  movzx r10d,byte ptr [rax+r9+2]
0x66a036f  xor r10,rdx
0x66a0372  imul r10,rdi
0x66a0376  movzx edx,byte ptr [rax+r9+3]
0x66a037c  xor rdx,r10
0x66a037f  imul rdx,rdi
0x66a0383  add r9,4
0x66a0387  cmp r8,r9
0x66a038a  jne short 0x66A0350

0x66a038c  test rcx,rcx
0x66a038f  je short 0x66A03B7

0x66a0391  add rax,r9                    ; remainder bytes
0x66a0394  xor r8d,r8d
0x66a0397  mov r9,rdx

0x66a03a0  movzx edx,byte ptr [rax+r8]   ; process 1 byte at a time
0x66a03a5  xor rdx,r9
0x66a03a8  imul rdx,rdi
0x66a03ac  inc r8
0x66a03af  mov r9,rdx
0x66a03b2  cmp rcx,r8
0x66a03b5  jne short 0x66A03A0

0x66a03b7  mov [rsi],rdx                 ; store result to output
```

Signature: `void fnv1a64(u64* out, std::string* str)` — computes FNV-1a 64 of string data into `*out`.

## Step 3: Where hash results are stored into task records [V]

### BatchActor extractor 0x66d9af0 [V]
- Called from Item visitor 0x6646980 (variant 10) [V]
- Callees include: **0x66a02d0 (via 0x19932c0 — XXH64, NOT FNV-1a)** and uniform binding helpers
- At 0x66dfc63: constructs `std::string` for "UseAlphaRewrite" at [rbp+0x4A0], calls 0x79580 (string ctor)
- At 0x66dfc96: loads FNV constants (0xcbf29ce484222325, 0x100000001b3) into registers
- At 0x66dfe03: calls 0x66a02d0 (FNV-1a 64) indirectly — **stores hash to [0x129F9128]** [V from ripscan]
- At 0x66e0860: calls 0x73150 with the hash at [0x129F9128], then 0xE938D70 to release string guard

### Task record storage at 0x66dc900 [V]
```
0x66dc900  mov rcx,rax
0x66dc903  test r8d,r8d
0x66dc906  je short 0x66DC938
0x66dc908  mov r8,[0x129F9128]          ; load FNV-1a hash of "UseAlphaRewrite"
0x66dc90f  mov r9,rdx
0x66dc912  mov rcx,rax
0x66dc915  nop [rax+rax]

loc_66dc920:  ; from 66dc931
0x66dc920  mov r10,[rcx]                ; iterate task records (0x10 stride)
0x66dc923  cmp [r10+0x28],r8            ; compare task kind hash at record+0x28
0x66dc927  je short 0x66DC938           ; found existing task kind
0x66dc929  add rcx,0x10
0x66dc92d  add r9,0xFFFFFFFFFFFFFFF0
0x66dc931  jne short 0x66DC920
```
Task record stride = **0x10 bytes** [V]. Task kind hash stored at **record+0x28** [V].

### Task record layout (inferred from 0x66dc900 and 0x66dc970) [V/I]
- `+0x00`: next pointer (linked list)
- `+0x08`: prev pointer or count
- `+0x10`: task data pointer
- `+0x20`: flags/type
- `+0x28`: **u64 task kind hash (FNV-1a 64 of uniform name)** [V]
- `+0x30`: task function pointer (std::function impl at +0x70 per BGFX_MAP 1267)

### Queue/dispatch: dragon::tasks::GraphicsTasks [V]
- `0xc270460` (BgfxContext::endFrame) calls `0xc273420` (frame graph generate) which calls `0xe9002e0` (task dispatch) [V]
- `0xe9002e0` iterates task list (0x80-byte entries per BGFX_MAP 1267) [V]
- At `0xe900460`: task vtable at `[r12]` — slot 0x18 = task execute function [V]
- Task vtable `0xf4f20c0` slot 2 = `0xe901dc0` (task execute) [V]
- Task execute `0xe901dc0` reads task data, calls render passes via `0xbc76030` etc. [V]

### Task kind hashes observed [V from BGFX_MAP 6ad]
- `0x481CF7B16E204CF8` = fnv1a("UseAlphaRewrite") — actor-body draw tasks (~5 per actor)
- `0x48603E36F5CE3EB2` = fnv1a("LightWorldSpaceDirection") — light tasks
- More: hash every uniform name from extractor strings (TintedAlphaTestEnabled, MetalnessUniform, EmissiveUniform, RoughnessUniform, SubsurfaceUniform, PBRTextureFlags, ActorFPEpsilon, DitheringEnabledToggle, MultiplicativeTintColor, UVScale, GlintColor, UseAlphaRewrite, PrevBones, PrevWorld, MERSTexture, NormalTexture, MatTexture1, MatTexture2) with FNV-1a 64

[UNVERIFIED: 0x66dc900 exact task record struct size and all fields — need stores.py on listing]
[UNVERIFIED: 0xe9002e0 task list base address and capacity — need to trace r12/rdx origin]

## Verification
- verify_oc.py on this file pending

## TOOL REQUESTS
- `stores.py` on 0x66dc900 listing to confirm task record field offsets
- `casewalk.py` on 0xe9002e0 to map task dispatch control flow
- Better ripscan for data refs to 0x129F9128/0x129F91E8/0x129F91F0/0x129F9200/0x129C13C0/0x129F9190 (static hash storage slots)