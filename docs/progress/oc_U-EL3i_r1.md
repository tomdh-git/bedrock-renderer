## NEXT
DONE

# UNIT U-EL3i — L3i drawutils pass-declaration templates (178 signatures) — 6aq; per-pass bodies
# Checklist item C5b (docs/RENDER_CHECKLIST.md), docs/BGFX_MAP.md section 6aq.
# Pending part (this unit): per-pass bodies of the drawutils template instantiations.
# Previously decoded [V] (oc_U-EC5b.md, NOT repeated here): sub_5667860 (field-copy body, offsets
# 0x0..0xC4/0xD4/0xE4/0x100/0xE8/0xF0/0xF8/0x108/0x110), sub_5667c80 (+0x118/+0x128 clears),
# sub_5667e70 (+0x168 state check), sub_5668ac0 (pass-name hash helper).
# This unit decodes the two named pending bodies from verbatim rdis listings (re-checked by verify_oc):
# sub_5667fe0 [0x5667fe0..0x56684f5], size 0x515, called from sub_55f1450 (VV builder) and sub_56a06a0;
# sub_56685c0 [0x56685c0..0x5668a0b], size 0x466, called from sub_55f1450.
# Signatures (from prologue/arg setup, [V]): sub_5667fe0(rcx=rsi=pass dest a0, rdx=rdi=declarator a1,
# r8d->desc words, r9d->desc words); sub_56685c0(rcx=rsi=a0 Declarator, rdx=rbx=a1 name source {ptr,size},
# r8=r14=a2 ptr, r9=rdi=a3 {byte@+8, qword@+0}).

## ANSWER TABLE (offset | size | read/store address | verbatim `0xRVA  instr` proof | meaning | tag)
# One row per distinct offset; all sites listed. Sizes from the instruction. No input-data paste.

sub_5667fe0 — declares 3 render targets (Color0/Color1/Color2) via sub_5698290 and stores hash+node
pairs into the pass dest [rsi]; lazy FNV-1 name hashes cached in globals 0x129CA3A0/B0/C0:
| pass+0x00 | 8 | [0x129CA3C0]->[rsi+0x0] | `0x566811a  mov rcx,[0x129CA3C0]` `0x5668121  mov [rsi],rcx` | pass+0 = Color2 name hash | [V] |
| pass+0x08 | 8 | rax=sub_5698290(Color2)->[rsi+0x8] | `0x5668115  call 0x5698290` `0x5668124  mov [rsi+8],rax` | pass+8 = Color2 declare-node result | [V] |
| pass+0x12 | 1 | imm 0->[rsi+0x12] | `0x5668128  mov byte ptr [rsi+0x12],0` | pass+0x12 flag byte = 0 | [V] |
| pass+0x18 | 8 | [0x129CA3B0]->[rsi+0x18] | `0x56680ed  mov r12,[0x129CA3B0]` `0x566812c  mov [rsi+0x18],r12` | pass+0x18 = Color1 name hash | [V] |
| pass+0x20 | 8 | r14=sub_5698290(Color1)->[rsi+0x20] | `0x56680ea  mov r14,rax` `0x5668130  mov [rsi+0x20],r14` | pass+0x20 = Color1 declare-node result | [V] |
| pass+0x2A | 1 | imm 0->[rsi+0x2A] | `0x5668134  mov byte ptr [rsi+0x2A],0` | pass+0x2A flag byte = 0 | [V] |
| pass+0x30 | 8 | [0x129CA3A0]->[rsi+0x30] | `0x56680bd  mov r15,[0x129CA3A0]` `0x5668138  mov [rsi+0x30],r15` | pass+0x30 = Color0 name hash | [V] |
| pass+0x38 | 8 | rbx=sub_5698290(Color0)->[rsi+0x38] | `0x56680ba  mov rbx,rax` `0x566813c  mov [rsi+0x38],rbx` | pass+0x38 = Color0 declare-node result | [V] |
| pass+0x42 | 1 | imm 0->[rsi+0x42] | `0x5668140  mov byte ptr [rsi+0x42],0` | pass+0x42 flag byte = 0 | [V] |
| desc+0x00 | 2 | r14w(arg r8d)->[rbp-0x18] | `0x566809b  mov [rbp-0x18],r14w` | descriptor word0 = width/width-arg | [V] |
| desc+0x02 | 2 | bx(arg r9d)->[rbp-0x16] | `0x56680a0  mov [rbp-0x16],bx` | descriptor word2 = height/height-arg | [V] |
| desc+0x04 | 4 | imm 0x1C/0x0A/0x0C->[rbp-0x14/-0x5C/-0x3C] | `0x56680a4  mov dword ptr [rbp-0x14],0x1C` `0x56680d4  mov dword ptr [rbp-0x5C],0xA` `0x5668104  mov dword ptr [rbp-0x3C],0xC` | descriptor format: Color0=0x1C, Color1=0x0A, Color2=0x0C (D3D12 id [I]) | [V] |
| desc+0x08 | 2 | imm 0->[rbp-0x10] | `0x5668087  mov word ptr [rbp-0x10],0` | descriptor word8 = 0 | [V] |
| desc+0x0C | 4 | imm 0->[rbp-0xC] | `0x566807c  mov dword ptr [rbp-0xC],0` | descriptor dword12 = 0 | [V] |
| desc+0x10 | 1 | imm 0->[rbp-8] | `0x5668083  mov byte ptr [rbp-8],0` | descriptor byte16 = 0 | [V] |
| desc+0x14 | 8 | imm 0x300000001->[rbp-4] | `0x566808d  mov rax,0x300000001` `0x5668097  mov [rbp-4],rax` | descriptor qword20 = 0x300000001 | [V] |
| declare | - | sub_5698290(rcx=rdi=declarator, rdx=rdi, r8=&desc) x3 | `0x56680b5  call 0x5698290` `0x56680e5  call 0x5698290` `0x5668115  call 0x5698290` | 3 target declarations (Color0/1/2), results rbx/r14/rax | [V] |
| global 0x129ca3a0 | 8 | rcx=FNV-1("Color0")->[0x129CA3A0] | `0x566816f  lea rdx,[0xF7E41CA]` `"Color0"` `0x5668359  mov [0x129CA3A0],rcx` | lazy pass-name hash Color0 [V store; string shown [V]] | [V] |
| global 0x129ca3b0 | 8 | rcx=FNV-1("Color1")->[0x129CA3B0] | `0x56681d2  lea rdx,[0xF7DDEC4]` `"Color1"` `0x5668420  mov [0x129CA3B0],rcx` | lazy pass-name hash Color1 | [V] |
| global 0x129ca3c0 | 8 | rdx=FNV-1("Color2")->[0x129CA3C0] | `0x5668235  lea rdx,[0xF7D9C07]` `"Color2"` `0x56684d4  mov [0x129CA3C0],rdx` | lazy pass-name hash Color2 | [V] |

sub_56685c0 — builds one declaration entry at [rbp-0x50] (name {ptr,size} from a1, user ptr a2, word 4),
stages a 16-byte value block from *a3 at [rbp+0x50], registers via sub_5699580, destroys temporaries:
| entry-0x50 | 16 | name {ptr,size}->[rbp-0x50] | `0x5668775  movaps xmm0,[rbp+0x110]` `0x5668787  movaps [rbp-0x50],xmm0` | entry+0x00 = name pointer + size | [V] |
| entry-0x40 | 16 | zero->[rbp-0x40] | `0x5668783  movaps [rbp-0x40],xmm1` | entry+0x10 zero block | [V] |
| entry-0x30 | 8 | a2 ptr->[rbp+0x130]->[rbp-0x30] | `0x5668655  mov [rbp+0x130],r14` `0x56687b0  mov rax,[rax]` `0x56687b3  mov [rbp-0x30],rax` | entry+0x18 user pointer = arg a2 | [V] |
| entry-0x28 | 2 | imm 4->[rbp+0x138]->[rbp-0x28] | `0x566865c  mov word ptr [rbp+0x138],4` `0x56687a8  movzx ecx,word ptr [rax+8]` `0x56687ac  mov [rbp-0x28],cx` | entry+0x20 word = 4 | [V] |
| stage+0x50 | 16 | *[rdi]=*a3+0x0->[rbp+0x50] | `0x56686fb  mov r8,[rdi]` `0x5668722  movups xmm1,[r8]` `0x5668726  movups [rbp+0xA0],xmm1` `0x5668850  movups xmm0,[r15]` `0x5668854  movaps [rbp+0x50],xmm0` | 16-byte value block from a3+0x0 | [V] |
| stage+0x140 | 8 | vtable 0xF25C520->[rbp+0x140] | `0x566866c  lea rax,[0xF25C520]` `0x5668673  mov [rbp+0x140],rax` | staged object vtable = 0xF25C520 | [V] |
| stage+0x148 | 4 | imm 0x3F800000->[rbp+0x148] | `0x566867a  mov dword ptr [rbp+0x148],0x3F800000` | staged object float field = 1.0 | [V] |
| stage+0x14C | 1 | r15b=byte [r9+8]=a3+8->[rbp+0x14C] | `0x56685ee  movzx r15d,byte ptr [r9+8]` `0x5668684  mov [rbp+0x14C],r15b` | staged object byte = a3+8 | [V] |
| regcall | - | sub_5699580(rcx=rsi=Declarator, rdx=&entry-0x50, r8=0) | `0x5668858  lea rdx,[rbp-0x50]` `0x566885c  mov rcx,rsi` `0x566885f  xor r8d,r8d` `0x5668862  call 0x5699580` | register the declaration entry | [V] |
| rel+vtable+8 | - | call [0xF99FFA0] (sub_eea6040) x4 | `0x56687e4  call qword ptr [0xF99FFA0]` `0x5668807  call qword ptr [0xF99FFA0]` `0x56688d1  call qword ptr [0xF99FFA0]` `0x566894b  call qword ptr [0xF99FFA0]` | release/dtor of temporaries via CFG thunk | [V] |
| heap-free | - | call 0xE935700 x4 | `0x56688a2  call 0xE935700` `0x5668919  call 0xE935700` `0x5668998  call 0xE935700` `0x56689f6  call 0xE935700` | heap frees of temporaries | [V] |

## CLOSES?
NO — per-pass bodies are proven [V] for sub_5667fe0 and sub_56685c0 (added to the oc_U-EC5b.md sample
sub_5667860/sub_5667c80/sub_5667e70/sub_5668ac0), but the item requires the bodies of ALL the
sub_566xxxx/sub_567xxxx/sub_568xxxx drawutils instantiations called from sub_55f1450 and
sub_bbe2d50. Per docs/data/inventory_L6_graph.tsv the builder calls ~50 further functions
(e.g. 0x5668d90, 0x5669ae0, 0x5669cf0, 0x566a450, 0x566a880, 0x567c110, 0x567c3f0, 0x56894c0,
0x5689800, 0x568ad40, 0x5693680, 0x56a06a0, 0x56c1fa0...) none of which are decoded. Blocking fact:
remaining per-pass template bodies not decoded; no [V] rows exist for them.

## TOOL REQUESTS
rdis.exe dis | exe -> verbatim instr listings of sub_5667fe0/sub_56685c0 | rows above copied from listings; no custom script needed, verify_oc re-checks every quoted line against the exe
