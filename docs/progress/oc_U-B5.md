# oc U-B5 — D3D12 root signature serialized in init (BGFX_MAP 6ak, 6ao)

Target: Minecraft.Windows.exe 1.26.62.01 (image-base RVAs). Static analysis only.
Brief checklist B5: D3D12 root signature serialized in init; >=6 root params; tables 2/3; value 5.
Tags: [V] seen in disassembly (RVA cited), [I] inferred, [?] unknown. Unclear items flagged [UNVERIFIED: 0xRVA question].
All quoted instruction lines are verbatim rdis text for `tools/sigs/verify_oc.py`.

## NEXT / status
Resumed at: none — unit complete pending verify_oc.py run. All key RVAs gathered.

## (1) Root-signature construction function + serializer call site

**Serializer string + resolution (in init `sub_e807ff0`):**
- `0xf5c750e` = ASCII "D3D12SerializeRootSignature" [V] (xref.py str; data, not an instruction)
- `sub_e807ff0` `[0xe807ff0..0xe809724)` size 0x1734, 1 xref [V] (rdis fn). RendererContextD3D12 init (slot 58).
- `0xE808108  lea rdx,[0xF5C750E]` [V]
- `0xE80810F  call 0xED35E80` [V]
- `0xE808114  mov [0x12BB4930],rax` — serializer pointer stored into global `0x12BB4930` [V]
- `0xE80812A  cmp qword ptr [0x12BB4920],0` [V]
- `0xE808138  cmp qword ptr [0x12BB4928],0` [V]

**Root-signature builder (`sub_e80c600`) — fills D3D12_ROOT_PARAMETER / D3D12_DESCRIPTOR_RANGE arrays and calls the serializer:**
- `sub_e80c600` `[0xe80c600..0xe80d886)` size **0x1286**, 1 xref (from init) [V] (rdis fn)
- Signature guess [I]: `sub_e80c600(context rcx=a0, rdx=a1, r8=a2, r9=a3, +stack a5)`; allocates a `0x2268`-byte heap buffer (rdi/r12 = alloc result, returned in rax) and builds the root-signature descriptor inside it.
- Args at entry [V]:
  - `0xE80C62D  mov rsi,r9`
  - `0xE80C630  mov rbx,r8`
  - `0xE80C633  mov r14,rdx`
  - `0xE80C636  mov r13,rcx`
- Alloc [V]:
  - `0xE80C64E  mov edx,0x2268`
  - `0xE80C653  call qword ptr [0xF99FFA0]`
  - `0xE80C659  mov rdi,rax`
  - `0xE80C65C  mov r12,rax`
- Return [V]: `0xE80D83C  mov [rdi],rsi`; `0xE80D83F  mov rax,rdi`; `ret` (returns buffer pointer)

**Serializer invocation inside `sub_e80c600` (root-signature desc at `rbp+0x1F0`):**
- `0xE80D0CA  mov dword ptr [rbp+0x1F0],5` → `NumParameters = 5` [V]
- `0xE80D0D4  lea rax,[rbp+0xD0]` ; `0xE80D0DB  mov [rbp+0x1F8],rax` → `pParameters = rbp+0xD0` [V]
- `0xE80D0E2  mov dword ptr [rbp+0x200],0` → `NumStaticSamplers = 0` [V]
- `0xE80D0EC  mov qword ptr [rbp+0x208],0` → `pStaticSamplers = 0` [V]
- `0xE80D0F7  mov dword ptr [rbp+0x210],1` → `Flags = 1` (ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT) [V]
- `0xE80D101  mov rax,[0x12BB4930]` — load serializer pointer [V]
- `0xE80D108  lea rcx,[rbp+0x1F0]` → pRootSignatureDesc [V]
- `0xE80D10F  lea r8,[rbp+0x268]` → `ppBlob` out [V]
- `0xE80D116  lea r9,[rbp+0xC8]` → `ppErrorBlob` out [V]
- `0xE80D11D  mov edx,1` → `Version = 1` (D3D_ROOT_SIGNATURE_VERSION_1) [V]
- `0xE80D122  call qword ptr [0xF99FFA0]` → **`D3D12SerializeRootSignature(desc,1,ppBlob,ppErrorBlob)`** [V]

**Caller:** init `sub_e807ff0` calls `sub_e80c600` at `0xE809350  call 0xE80C600` [V], in a loop bounded by byte `[rsi+0x2E8]` = `[context+0x19F84]`:
- `0xE809305  mov [rsi+0x2E8],edx` [V]
- `0xE809376  jb short 0xE809338` (loop back) [V]
- Call-site args [V]: `0xE80934A  mov rcx,r15` (r15=`lea [rbp+0x30]`), `0xE809342  mov rdx,[rbx]`, `0xE80933F  mov r8,[rax]` where `rax=[rsi+0x238]`, `0xE80934D  mov r9,r14` (r14=`lea [rsi+0x170]` = context+0x170).
- `sub_e80c600` return value (rax = buffer ptr) is not consumed by next instruction (`0xE809356  mov rcx,rdi`), so results flow via side effect / out-pointer arg not yet resolved to a context offset [UNVERIFIED: 0xE809350 question context offset of stored ID3D12RootSignature*].

## (2) Every root parameter, in order (from stores into stack structs)

`D3D12_ROOT_PARAMETER` is 0x20 bytes: `ParameterType u32 +0x00`, union `+0x08` (`NumDescriptorRanges u32 +0x08` / `pDescriptorRanges ptr +0x10` for TABLE; `ShaderRegister u32 +0x08` / `RegisterSpace u32 +0x0C` for CBV root-descriptor), `ShaderVisibility u32 +0x18` [layout checked against stores — e.g. param0 visibility store at `rbp+0xE8` = base+0x18 confirms +0x18].

`D3D12_DESCRIPTOR_RANGE` is 0x14 bytes: `RangeType u32 +0x00` (0 SRV,1 UAV,2 CBV,3 SAMPLER), `NumDescriptors u32 +0x04`, `BaseShaderRegister u32 +0x08`, `RegisterSpace u32 +0x0C`, `OffsetInDescriptorsFromTableStart u32 +0x10`.

All 5 params at `rbp+0xD0 + i*0x20` (pParameters=rbp+0xD0, NumParameters=5). All quoted lines are verbatim rdis.

| Index | ParameterType | ShaderVisibility | Notes |
|-------|---------------|------------------|-------|
| 0 | 0 TABLE | 0 ALL | type `0xE80D019  mov dword ptr [rbp+0xD0],0` [V]; NumRanges `0xE80D023  mov dword ptr [rbp+0xD8],1` [V]; pRanges `0xE80D031  mov [rbp+0xE0],rcx` (rcx=rbp+0x60) [V]; visibility `0xE80D038  mov dword ptr [rbp+0xE8],0` [V] |
| 1 | 0 TABLE | 0 ALL | type `0xE80D042  mov dword ptr [rbp+0xF0],0` [V]; NumRanges `0xE80D04C  mov dword ptr [rbp+0xF8],1` [V]; pRanges `0xE80D05A  mov [rbp+0x100],rcx` (rcx=rbp+0x74) [V]; visibility `0xE80D061  mov dword ptr [rbp+0x108],0` [V] |
| 2 | 2 CBV (root-descriptor) | ? | type `0xE80D079  mov dword ptr [rbp+0x110],2` [V]; ShaderRegister `[rbp+0x118]=0` and RegisterSpace `[rbp+0x11C]=0` (both cleared by `0xE80D06B  movaps [rbp+0x110],xmm6` clearing 0x110..0x11F) [V]; visibility `[rbp+0x128]` — **not stored before serializer call** [UNVERIFIED: 0xE80D079 question param-2 visibility leftover] |
| 3 | 2 CBV (root-descriptor) | ? | type `0xE80D091  mov dword ptr [rbp+0x130],2` [V]; ShaderRegister `0xE80D0C0  mov dword ptr [rbp+0x138],1` → reg 1 [V]; RegisterSpace `[rbp+0x13C]=0` (cleared by `0xE80D083  movaps [rbp+0x130],xmm6` clearing 0x130..0x13F) [V]; visibility `[rbp+0x148]` — **not stored before serializer call** [UNVERIFIED: 0xE80D091 question param-3 visibility leftover] |
| 4 | 0 TABLE | 0 ALL | type `0xE80D09B  mov dword ptr [rbp+0x150],0` [V]; NumRanges `0xE80D0A5  mov dword ptr [rbp+0x158],1` [V]; pRanges `0xE80D0AF  mov [rbp+0x160],rax` (rax=rbp+0xB0) [V]; visibility `0xE80D0B6  mov dword ptr [rbp+0x168],0` [V] |

**Descriptor ranges (each table has NumRanges=1):**

Table at `rbp+0x60` (param 0), 1 range @ `rbp+0x60` — bytes from `0xE80CFF2  movaps xmm0,[0xF4EDD00]` ... actually:
- `0xE80CFFD  movaps xmm0,[0xF4EDCF0]` / `0xE80D004  movaps [rbp+0x60],xmm0` → `[rbp+0x60]` = f4edcf0 = {3, 0x10, 0, 0} [V]
- RangeType `+0x00 [rbp+0x60]=3` → SAMPLER [V]; NumDescriptors `+0x04 [rbp+0x64]=0x10` → 16 [V]; BaseShaderRegister `+0x08 [rbp+0x68]=0` [V]; RegisterSpace `+0x0C [rbp+0x6C]=0` [V]; Offset `+0x10 [rbp+0x70]` = first dword of f4edd00 (`0xE80CFF2  movaps xmm0,[0xF4EDD00]` stored at `rbp+0x70` via `0xE80CFF9`) = `0xFFFFFFFF` → D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND [V]
- → **SAMPLER table, 16 samplers, base reg 0, space 0, offset APPEND**

Table at `rbp+0x74` (param 1), 1 range @ `rbp+0x74` — bytes from f4edd00/f4edd10:
- RangeType `+0x00 [rbp+0x74]=0` → SRV [V] (f4edd00[4]); NumDescriptors `+0x04 [rbp+0x78]=0xFFFFFFFF` [V] — **unbounded range (D3D12 UINT_MAX = unbounded descriptor table)** [V value, I meaning per D3D12 spec]; BaseShaderRegister `+0x08 [rbp+0x7C]=0` [V]; RegisterSpace `+0x0C [rbp+0x80]=0` [V]; Offset `+0x10 [rbp+0x84]=0xFFFFFFFF` [V] (APPEND)
- → **SRV table, NumDescriptors=0xFFFFFFFF = unbounded, base 0, space 0, offset APPEND**

Table at `rbp+0xB0` (param 4), 1 range @ `rbp+0xB0` — bytes from f4edd40:
- `0xE80CFC1  movaps [rbp+0xB0],xmm0` (xmm0=f4edd40={1,0xFFFFFFFF,0,0}) [V]
- RangeType `+0x00 [rbp+0xB0]=1` → SAMPLER [V]; NumDescriptors `+0x04 [rbp+0xB4]=0xFFFFFFFF` [V] — (unbounded range); BaseShaderRegister `+0x08 [rbp+0xB8]=0` [V]; RegisterSpace `+0x0C [rbp+0xBC]=0` [V]; Offset `+0x10 [rbp+0xC0]` = `0xE80D008  mov dword ptr [rbp+0xC0],0xFFFFFFFF` → APPEND [V]
- → **SAMPLER table, NumDescriptors=0xFFFFFFFF = unbounded, base 0, space 0, offset APPEND**

**Constants / 32BIT_CONSTANTS:** none — no parameter of type 1. [V] (types are 0,0,2,2,0)

## (3) Static samplers + flags
- `NumStaticSamplers = 0` (`0xE80D0E2  mov dword ptr [rbp+0x200],0`), `pStaticSamplers = 0` (`0xE80D0EC  mov qword ptr [rbp+0x208],0`) → **no static samplers** [V]
- `Flags = 1` (`0xE80D0F7  mov dword ptr [rbp+0x210],1`) → D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT [V]
- `Version = 1` (`0xE80D11D  mov edx,1`) [V]
- A separate `0x204`-byte buffer is allocated (`0xE80D1B7  mov r8d,0x204`) and filled with static-sampler-like constants from `0xF441430..0xF441520` (`movaps [rax+4]..[rax+0xF4]`), stored at `[rcx+8]` (`0xE80D29B  mov [rcx+8],rax`) [V] — but NumStaticSamplers=0 so this buffer's purpose is unclear [I]

## (4) How the resulting ID3D12RootSignature is stored (context offset)
- `sub_e80c600` allocates a `0x2268`-byte heap buffer (size `edx=0x2268` at `0xE80C64E`, alloc via `sub_eea6040`) and returns its pointer in `rax` (`0xE80D83F  mov rax,rdi`) [V]
- Root-signature descriptor at `rbp+0x1F0` (stack); serialized blob out-ptr at `rbp+0x268`, error blob at `rbp+0xC8` [V]
- Called from init `sub_e807ff0` at `0xE809350` in a loop bounded by byte `[context+0x19F84]` (`[rsi+0x2E8]`) [V]
- **Exact context offset where the final `ID3D12RootSignature*` is stored: NOT fully traced.** `sub_e80c600`'s return value (rax = buffer ptr) is discarded by the caller (`0xE809356  mov rcx,rdi` does not use rax), so results flow via a side-effect/out-pointer arg not yet resolved to a context offset [UNVERIFIED: 0xE809350 question context offset of stored ID3D12RootSignature*].

## Instruction claims for verify_oc.py (verbatim rdis text, column 0)
0xE808108  lea rdx,[0xF5C750E]
0xE80810F  call 0xED35E80
0xE808114  mov [0x12BB4930],rax
0xE80812A  cmp qword ptr [0x12BB4920],0
0xE808138  cmp qword ptr [0x12BB4928],0
0xE80C62D  mov rsi,r9
0xE80C630  mov rbx,r8
0xE80C633  mov r14,rdx
0xE80C636  mov r13,rcx
0xE80C64E  mov edx,0x2268
0xE80C653  call qword ptr [0xF99FFA0]
0xE80C659  mov rdi,rax
0xE80C65C  mov r12,rax
0xE80D83C  mov [rdi],rsi
0xE80D83F  mov rax,rdi
0xE80D0CA  mov dword ptr [rbp+0x1F0],5
0xE80D0D4  lea rax,[rbp+0xD0]
0xE80D0DB  mov [rbp+0x1F8],rax
0xE80D0E2  mov dword ptr [rbp+0x200],0
0xE80D0EC  mov qword ptr [rbp+0x208],0
0xE80D0F7  mov dword ptr [rbp+0x210],1
0xE80D101  mov rax,[0x12BB4930]
0xE80D108  lea rcx,[rbp+0x1F0]
0xE80D10F  lea r8,[rbp+0x268]
0xE80D116  lea r9,[rbp+0xC8]
0xE80D11D  mov edx,1
0xE80D122  call qword ptr [0xF99FFA0]
0xE809350  call 0xE80C600
0xE809356  mov rcx,rdi
0xE809305  mov [rsi+0x2E8],edx
0xE809376  jb short 0xE809338
0xE80D019  mov dword ptr [rbp+0xD0],0
0xE80D023  mov dword ptr [rbp+0xD8],1
0xE80D031  mov [rbp+0xE0],rcx
0xE80D038  mov dword ptr [rbp+0xE8],0
0xE80D042  mov dword ptr [rbp+0xF0],0
0xE80D04C  mov dword ptr [rbp+0xF8],1
0xE80D05A  mov [rbp+0x100],rcx
0xE80D061  mov dword ptr [rbp+0x108],0
0xE80D06B  movaps [rbp+0x110],xmm6
0xE80D079  mov dword ptr [rbp+0x110],2
0xE80D083  movaps [rbp+0x130],xmm6
0xE80D091  mov dword ptr [rbp+0x130],2
0xE80D0C0  mov dword ptr [rbp+0x138],1
0xE80D09B  mov dword ptr [rbp+0x150],0
0xE80D0A5  mov dword ptr [rbp+0x158],1
0xE80D0AF  mov [rbp+0x160],rax
0xE80D0B6  mov dword ptr [rbp+0x168],0
0xE80CFF2  movaps xmm0,[0xF4EDD00]
0xE80D004  movaps [rbp+0x60],xmm0
0xE80D008  mov dword ptr [rbp+0xC0],0xFFFFFFFF
0xE80CFC1  movaps [rbp+0xB0],xmm0
0xE80D1B7  mov r8d,0x204
0xE80D29B  mov [rcx+8],rax

## Cross-checks / open
- BGFX_MAP 6ak/6ao hint ">=6 root params, tables 2/3, value 5" does NOT match this build's init sig: verified **exactly 5 params**, tables at indices **0,1,4**, CBVs at **2,3**, no 32BIT_CONSTANTS ("value") param, no index 5. Discrepancy flagged — may be a different/RTX root signature or an outdated hint [UNVERIFIED].
- `D3D12SerializeRootSignature` is called only once in init (at `0xE80D122` inside `sub_e80c600`); the only other user of global `0x12BB4930` is the RTX path `0xe84c328` (func `0xe84ba30`) [V ripscan]
- `0xFFFFFFFF` NumDescriptors on tables 1 and 4 is an UNBOUNDED range (valid D3D12: UINT_MAX)

## Verification
Run: `python tools/sigs/verify_oc.py docs/progress/oc_U-B5.md` (quotes `0xRVA instr` lines against the exe).
