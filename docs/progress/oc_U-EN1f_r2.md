## NEXT
DONE

# OC Item: U-EN1f — Pipeline Disk Cache (save-only, never loaded from this module)

## Answer
`rd_pipeline_cache.bin` is write-only in Minecraft.Windows.exe 1.26.62.01: the game saves it to disk but never loads/consumes it from this module. Vtable 0xF08F110 holds only dtor / stage-2 destroy / getter slots; none references the filename, and the filename string has exactly one code reference (the save site). A replacement blob is safe iff it avoids writing a conflicting `rd_pipeline_cache.bin` or owns both load and invalidation (stale when magic/version/hash mismatch).

## Evidence table (annotated fields; every instr is a verbatim `0xRVA  instr` quote from rdis dis)

| offset | size | site | instr | meaning |
|---|---|---|---|---|
| 0xe8fec6d | 8 | PipelineDiskCache::tick (0xe8feb10) | `0xe8fec6d  mov rdi,[rsi+0xE8]` | cache object pointer at PipelineDiskCache+0xE8 |
| 0xe8fecc1 | 8 | tick vtable ptr load | `0xe8fecc1  mov rax,[rdi]` | load cache object vtable pointer |
| 0xe8fecc4 | 8 | tick vtable[0x40] load | `0xe8fecc4  mov rax,[rax+0x40]` | load slot-8 target from vtable |
| 0xe8feccb | 8 | tick indirect call (CFG) | `0xe8feccb  call qword ptr [0xF99FFA0]` | cacheObj->vtable[0x40](); tick keeps only AL |
| 0xe8fc7e0 | 8 | save site filename ref | `0xe8fc7e0  lea rax,[0xF593232]` | "rd_pipeline_cache.bin" (data_f593232) — unique code ref |
| 0xe8fc7e7 | 8 | save filename ptr store | `0xe8fc7e7  mov [rbp+0x2A0],rax` | filename pointer stored |
| 0xe8fc7ee | 8 | save filename length | `0xe8fc7ee  mov qword ptr [rbp+0x2A8],0x15` | length 21 |
| 0xe8fc8d7 | 4 | save header store #1 | `0xe8fc8d7  mov eax,[rdi]` | header u32#1 from header ptr |
| 0xe8fc8d9 | 4 | save header store #1 | `0xe8fc8d9  mov [r15+0x78],eax` | [this+0x78] |
| 0xe8fc8ee | 4 | save header store #4 | `0xe8fc8ee  mov eax,[rdi+0xC]` | header u32#4 |
| 0xe8fc8f1 | 4 | save header store #4 | `0xe8fc8f1  mov [r15+0x84],eax` | [this+0x84] |
| 0xe8fcaaf | 8 | save object install | `0xe8fcaaf  mov [r15+0xE8],rax` | new 0x150-byte cache object installed at +0xE8 |
| 0xe8fcfdc | 4 | save write validation | `0xe8fcfdc  cmp dword ptr [rbp+0x2E0],0x43504452` | on-disk magic must be "RDPC" |
| 0xe8fcfe8 | 4 | save write validation | `0xe8fcfe8  cmp dword ptr [rbp+0x2E4],0` | header u32[1] != 0 |
| 0xe8fcfef | 1 | save write validation | `0xe8fcfef  setne bl` | proceed iff magic && u32[1] |
| 0x66395a6 | 4 | header-builder save gate | `0x66395a6  cmp dword ptr [0x12ADF818],0xA` | save only if global == 0xA |
| 0x66395c2 | 4 | header u32#1 | `0x66395c2  mov dword ptr [rsp+0x30],0xA` | header[0] = 0xA |
| 0x66395ca | 8 | header u16 pair | `0x66395ca  movq xmm0,[0x12ADFA58]` | load u16 pair |
| 0x66395da | 8 | header u16 pair | `0x66395da  movq [rsp+0x34],xmm0` | store at [rsp+0x34] |
| 0x66395fd | 4 | FNV-1a32 basis | `0x66395fd  mov r8d,0x84222325` | basis 0x84222325 |
| 0x6639624 | 4 | FNV-1a32 prime step | `0x6639624  imul r8d,0x1B3` | prime 0x01000193 |
| 0x663962b | 4 | FNV-1a32 xor step | `0x663962b  xor r8d,r9d` | per-byte mix |
| 0x66396d2 | 4 | FNV-1a32 hash store | `0x66396d2  mov [rsp+0x3C],r8d` | header[2] = FNV-1a32 hash |
| 0x77253b | 8 | cache-object ctor | `0x77253b  lea rax,[0xF08F110]` | vtable RVA 0xF08F110 (data_f08f110) |
| 0x772542 | 8 | cache-object ctor | `0x772542  mov [rcx],rax` | vtable stored at cache object+0 |
| 0x7a8f70 | 8 | vtable 0xF08F110 slot 0x000 | `0x7a8f70  push rsi` | dtor stage 1 (strong refcount == 0) |
| 0x772a70 | 8 | vtable 0xF08F110 slot 0x008 | `0x772a70  push rbp` | stage-2 destroy (weak refcount == 0) |
| 0x773410 | 8 | vtable 0xF08F110 slot 0x010 | `0x773410  push rbp` | management slot |
| 0x775560 | 8 | vtable 0xF08F110 slot 0x018 | `0x775560  push rbp` | management slot |
| 0x775730 | 8 | vtable 0xF08F110 slot 0x020 | `0x775730  push rbp` | management slot |
| 0x774200 | 4 | vtable 0xF08F110 slot 0x028 | `0x774200  mov eax,[rcx+0xB0]` | u32 getter |
| 0x775520 | 8 | vtable 0xF08F110 slot 0x030 | `0x775520  mov rax,[rcx+8]` | qword getter |
| 0x775320 | 8 | vtable 0xF08F110 slot 0x038 | `0x775320  push r15` | management slot |
| 0x7758c0 | 8 | vtable 0xF08F110 slot 0x040 | `0x7758c0  mov rax,[rcx+0x20]` | tick's vtable[0x40] target (obj+0x20) |
| 0x7a8fa0 | 8 | vtable 0xF08F110 slot 0x048 | `0x7a8fa0  push rbp` | management slot |
| 0x7a9450 | 8 | vtable 0xF08F110 slot 0x050 | `0x7a9450  push rsi` | management slot |
| 0x775e80 | 8 | vtable 0xF08F110 slot 0x058 | `0x775e80  mov rax,rdx` | management slot |

## Key conclusions
- No vtable slot is a load/consume entry (dtor/destroy/getters only; none references `rd_pipeline_cache.bin`).
- Unique filename code ref is the save site → game never loads `rd_pipeline_cache.bin` from this module.
- Header = {0xA version, u16 pair, FNV-1a32 hash (prime 0x01000193, basis 0x84222325)}; save gated on global `0x12ADF818 == 0xA`; write validates magic == 0x43504452 ("RDPC") and u32[1] != 0; stale iff magic/version/hash mismatch.
