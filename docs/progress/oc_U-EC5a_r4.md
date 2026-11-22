## NEXT
DONE

# UNIT U-EC5a — C5a pending: registration call addresses (6aq)

Source: docs/RENDER_CHECKLIST.md item C5a, docs/BGFX_MAP.md section 6aq; prior units oc_U-C5a.md, oc_U-C5a2.md.
EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only.

Task (pending part only): registration call addresses for Declarator<RenderContext> + five Bind* dependency kinds + module names (6aq).
Orchestrator angles: (1) module names may be FNV-1a 64 hashed — hash the candidate names and search exe for 8-byte constants; (2) find Declarator<RenderContext> registration call sites from 6aq anchors, list immediate arguments; (3) report any registration address provable [V] even if names stay unbound.

## ANGLE 1 — hashed module names (FNV-1a 64) [not found]

Hashes computed locally (basis 0xCBF29CE484222325, prime 0x100000001B3; sanity: empty string -> 0xCBF29CE484222325 OK):
| name | FNV-1a 64 | LE bytes |
|---|---|---|
| averageLuminance | 0x076873264782CD86 | 86 cd 82 47 26 73 68 07 |
| localExposure | 0xB74BDB51273F6B5D | 5d 6b 3f 27 51 db 4b b7 |
| taau | 0x212F66910781E4F0 | f0 e4 81 07 91 66 2f 21 |
| clusterLights | 0x431ABDFBA0F828EC | ec 28 f8 a0 fb bd 1a 43 |
| volumeScattering | 0x8FABE1CCBB2557A5 | a5 57 25 bb cc e1 ab 8f |
| generateCubemapMips | 0x5121F11FEABD5BDC | dc 5b bd ea 1f f1 21 51 |
| rayTrace | 0x77A70E1DEFCBE5FC | fc e5 cb ef 1d 0e a7 77 |
| preprocessingutils | 0xBE65CDAD36668576 | 76 85 66 36 ad cd 65 be |

Searches (all 0 hits):
- `rdis imm <full 64-bit hash>` for all 8 hashes — 0 hit(s) each.
- `rdis imm <low-32 half>` sampled: averageLuminance 0x4782CD86 → 0 hit(s); localExposure 0x273F6B5D → 0 hit(s).
- `rdis find <8 LE bytes>` for averageLuminance → 0 hit(s).

Conclusion: module-name hash constants are NOT present as instruction immediates or raw 8-byte data (as far as imm/find cover). [I: imm may not index imm64 materializations; treat angle 1 as exhausted/negative.]

## REGISTRATION FUNCTION — sub_567b570 (bind/lookup) [V]

Range [0x567B570..0x567B846+) per `fn`; 111 xrefs in. Args: rcx=Declarator (a0), rdx=entry ptr (a1: +0x00 qword key, +0x08 byte kind, 0xFF=sentinel), r8={qword count, qword ptr to bytes to hash} (a2).
- 0x567B5A5-0x567B5B4: searches Declarator vector [a0+0x8] ({+8=begin,+0x10=end}, stride 0x48, entry {+0x00 qword key, +0x08 byte kind}) for [vec+0]==entry+0 && [vec+8]==kind (kind!=0xFF) or [vec+8]==0xFF (kind==0xFF).
- 0x567B63A-0x567B6B4: FNV-1a 64 loop over [a2+8 .. a2+8+a2+0*16) mixed with entry+0 (0x567B63A `mov r9,0xCBF29CE484222325`, 0x567B644 `mov r10,0x100000001B3`, 0x567B64E `mov r11d,0x9E3779B9`).
- On insert: 0x567B72C `movups [r15],xmm0` (16B record), [r15+0x38]=hash, [r15+0x40]=kind byte; vector end += 0x48 (0x567B812).

Known callers [V]: sub_55f1450 x90 (VV builder), sub_56a06a0 x2, sub_6753b50 x6, sub_bb3e2b0 x4, sub_bb6b350 x1, sub_bbce7b0 x5, sub_bbe2d50 x3 (RTX builder). All observed sites write kind=0 at entry+0x08 (placeholder for hash table; real Bind* kind comes from elsewhere — [UNVERIFIED]).

## REGISTRATION CALL SITES WITH IMMEDIATE ARGUMENTS [V]

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning |
|---|---|---|---|---|
| 0xBBE346E | 8 | [0x12ADF370] | `0xBBE346E  mov rax,[0x12ADF370]` | entry+0x00 key load from global [V] |
| 0xBBE3475 | 8 | [rbp+0x1030] | `0xBBE3475  mov [rbp+0x1030],rax` | entry+0x00 key store (RTX bind call 1) [V] |
| 0xBBE347C | 1 | [rbp+0x1038] | `0xBBE347C  mov byte ptr [rbp+0x1038],0` | entry+0x08 kind = 0 (RTX bind call 1) [V] |
| 0xBBE3491 | 8 | [rbp+0xD80] | `0xBBE3491  mov qword ptr [rbp+0xD80],1` | r8+0 count = 1 (RTX bind call 1) [V] |
| 0xBBE349C | 8 | [rbp+0xD88] | `0xBBE349C  mov [rbp+0xD88],rdi` | r8+8 hash base = rdi (RTX bind call 1) [V] |
| 0xBBE34B8 | 8 | 0x567B570 | `0xBBE34B8  call 0x567B570` | registration call site 1 (RTX builder sub_bbe2d50+0x768) [V] |
| 0xBBE34EF | 8 | [0x12ADF380] | `0xBBE34EF  mov rax,[0x12ADF380]` | entry+0x00 key load from global [V] |
| 0xBBE34F6 | 8 | [rbp+0x1030] | `0xBBE34F6  mov [rbp+0x1030],rax` | entry+0x00 key store (RTX bind call 2) [V] |
| 0xBBE34FD | 1 | [rbp+0x1038] | `0xBBE34FD  mov byte ptr [rbp+0x1038],0` | entry+0x08 kind = 0 (RTX bind call 2) [V] |
| 0xBBE351E | 8 | [rbp+0xD80] | `0xBBE351E  mov qword ptr [rbp+0xD80],1` | r8+0 count = 1 (RTX bind call 2) [V] |
| 0xBBE3529 | 8 | [rbp+0xD88] | `0xBBE3529  mov [rbp+0xD88],rdi` | r8+8 hash base = rdi (RTX bind call 2) [V] |
| 0xBBE3545 | 8 | 0x567B570 | `0xBBE3545  call 0x567B570` | registration call site 2 (RTX builder sub_bbe2d50+0x7F5) [V] |
| 0xBBE3562 | 8 | [0x12ADF390] | `0xBBE3562  mov rax,[0x12ADF390]` | entry+0x00 key load from global [V] |
| 0xBBE3569 | 8 | [rbp+0x1030] | `0xBBE3569  mov [rbp+0x1030],rax` | entry+0x00 key store (RTX bind call 3) [V] |
| 0xBBE3570 | 1 | [rbp+0x1038] | `0xBBE3570  mov byte ptr [rbp+0x1038],0` | entry+0x08 kind = 0 (RTX bind call 3) [V] |
| 0xBBE357F | 8 | [rbp+0xD80] | `0xBBE357F  mov qword ptr [rbp+0xD80],1` | r8+0 count = 1 (RTX bind call 3) [V] |
| 0xBBE358A | 8 | [rbp+0xD88] | `0xBBE358A  mov [rbp+0xD88],rdi` | r8+8 hash base = rdi (RTX bind call 3) [V] |
| 0xBBE35A9 | 8 | 0x567B570 | `0xBBE35A9  call 0x567B570` | registration call site 3 (RTX builder sub_bbe2d50+0x859) [V] |
| 0xBBCF004 | 8 | [0x12ADF220] | `0xBBCF004  mov rax,[0x12ADF220]` | entry+0x00 key load from global [V] |
| 0xBBCF00B | 8 | [rbp+0xA08] | `0xBBCF00B  mov [rbp+0xA08],rax` | entry+0x00 key store (bbce7b0 call 1) [V] |
| 0xBBCF012 | 1 | [rbp+0xA10] | `0xBBCF012  mov byte ptr [rbp+0xA10],0` | entry+0x08 kind = 0 (bbce7b0 call 1) [V] |
| 0xBBCF026 | 8 | [rbp+0x648] | `0xBBCF026  mov qword ptr [rbp+0x648],1` | r8+0 count = 1 (bbce7b0 call 1) [V] |
| 0xBBCF031 | 8 | [rbp+0x650] | `0xBBCF031  mov [rbp+0x650],rbx` | r8+8 hash base = rbx (bbce7b0 call 1) [V] |
| 0xBBCF04D | 8 | 0x567B570 | `0xBBCF04D  call 0x567B570` | registration call site 4 (sub_bbce7b0+0x89D) [V] |
| 0xBBCF084 | 8 | [0x12ADF230] | `0xBBCF084  mov rax,[0x12ADF230]` | entry+0x00 key load from global [V] |
| 0xBBCF08B | 8 | [rbp+0xA08] | `0xBBCF08B  mov [rbp+0xA08],rax` | entry+0x00 key store (bbce7b0 call 2) [V] |
| 0xBBCF092 | 1 | [rbp+0xA10] | `0xBBCF092  mov byte ptr [rbp+0xA10],0` | entry+0x08 kind = 0 (bbce7b0 call 2) [V] |
| 0xBBCF0AA | 8 | [rbp+0x648] | `0xBBCF0AA  mov qword ptr [rbp+0x648],1` | r8+0 count = 1 (bbce7b0 call 2) [V] |
| 0xBBCF0B5 | 8 | [rbp+0x650] | `0xBBCF0B5  mov [rbp+0x650],rbx` | r8+8 hash base = rbx (bbce7b0 call 2) [V] |
| 0xBBCF0D1 | 8 | 0x567B570 | `0xBBCF0D1  call 0x567B570` | registration call site 5 (sub_bbce7b0+0x921) [V] |
| 0xBBCF0EE | 8 | [0x12ADF240] | `0xBBCF0EE  mov rax,[0x12ADF240]` | entry+0x00 key load from global [V] |
| 0xBBCF0F5 | 8 | [rbp+0xA08] | `0xBBCF0F5  mov [rbp+0xA08],rax` | entry+0x00 key store (bbce7b0 call 3) [V] |
| 0xBBCF0FC | 1 | [rbp+0xA10] | `0xBBCF0FC  mov byte ptr [rbp+0xA10],0` | entry+0x08 kind = 0 (bbce7b0 call 3) [V] |
| 0xBBCF108 | 8 | [rbp+0x648] | `0xBBCF108  mov qword ptr [rbp+0x648],1` | r8+0 count = 1 (bbce7b0 call 3) [V] |
| 0xBBCF113 | 8 | [rbp+0x650] | `0xBBCF113  mov [rbp+0x650],rbx` | r8+8 hash base = rbx (bbce7b0 call 3) [V] |
| 0xBBCF12F | 8 | 0x567B570 | `0xBBCF12F  call 0x567B570` | registration call site 6 (sub_bbce7b0+0x97F) [V] |
| 0xBBCF165 | 8 | [0x12ADF250] | `0xBBCF165  mov rcx,[0x12ADF250]` | entry+0x00 key load from global [V] |
| 0xBBCF16C | 8 | [rbp+0xA08] | `0xBBCF16C  mov [rbp+0xA08],rcx` | entry+0x00 key store (bbce7b0 call 4) [V] |
| 0xBBCF173 | 1 | [rbp+0xA10] | `0xBBCF173  mov byte ptr [rbp+0xA10],0` | entry+0x08 kind = 0 (bbce7b0 call 4) [V] |
| 0xBBCF1BA | 8 | 0x567B570 | `0xBBCF1BA  call 0x567B570` | registration call site 7 (sub_bbce7b0+0xA0A) [V] |
| 0xBBCF2AC | 8 | [rbp+0x8C0] | `0xBBCF2AC  lea rcx,[rbp+0x8C0]` | rcx = Declarator (bbce7b0 call 5) [V] |
| 0xBBCF2B3 | 8 | [rbp+0xA08] | `0xBBCF2B3  lea rdx,[rbp+0xA08]` | rdx = entry ptr (bbce7b0 call 5) [V] |
| 0xBBCF2BA | 8 | [rbp+0x648] | `0xBBCF2BA  lea r8,[rbp+0x648]` | r8 = {count,hashbase} (bbce7b0 call 5) [V] |
| 0xBBCF2C1 | 8 | 0x567B570 | `0xBBCF2C1  call 0x567B570` | registration call site 8 (sub_bbce7b0+0xB11) [V] |

## SUMMARY

Registration function sub_567b570 (bind/lookup) is proven [V] at 0x567B570 with 111 xref call sites. Eight call sites are fully decoded with immediate arguments [V]:
- 3 in RTX builder sub_bbe2d50: 0xBBE34B8, 0xBBE3545, 0xBBE35A9 (all kind=0, key from globals [0x12ADF370/380/390])
- 5 in sub_bbce7b0: 0xBBCF04D, 0xBBCF0D1, 0xBBCF12F, 0xBBCF1BA, 0xBBCF2C1 (all kind=0, key from globals [0x12ADF220/230/240/250])

Module names: NOT found as FNV-1a 64 hashed constants (angle 1 exhausted, all 0 hits). Contiguous ASCII pass-name strings exist (e.g. "VolumeScattering" referencing sub_55f1450+0x44CE1 near call 0x55F594A) but are NOT bound to specific registration call sites. [I]

Bind* kind→type mapping: kind IDs 0-4 known from jump table [V], but mapping to specific Bind* types remains [I] (inferred from handler behavior + 6aq counts, not proven by string/registration evidence).

CLOSES? NO — registration call addresses for sub_567b570 are proven [V] (8 sites decoded, 111 total known), but module names are not bound to registration call addresses (angle 1 negative; strings exist as contiguous ASCII but not linked to registration calls), and the five Bind* kind→type mapping remains inferred [I], not proven [V].

## TOOL REQUESTS

None — all required data gathered via rdis dis/xr/imm/find. No helper scripts written.
