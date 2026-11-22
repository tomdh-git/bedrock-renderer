## NEXT
DONE — A12b setter located: 0xBC6E360 writes Encoder+0x680 (0xbc6e3da) and dirty flag +0x688 (0xbc6e533); CLOSES? YES

UNIT U-EA12b — A12b ranged vertex-buffer binds: setter filling Encoder+0x680 (was the open half of the item; the RTX skinning range check 0xe83f1d0 was already found under 6ei).

Input data (read-only): docs/progress/oc_U-A12b.md — the four callers of 0xBC60F10 (0xBC60740/0xBC61140/0xBC61560/0xBC618E0) are Encoder::submit variants that only READ Encoder+0x680 (mov r8,[rsi+0x680] at 0xbc60b4f/0xbc613d8/0xbc6178f/0xbc61b8a) and clear dirty flag +0x688; none write +0x680 [V]. 0xBC60F10 reads Encoder+0x680 into Frame+0x8B4778 SideTable (0x41 x {Binding*, count}, u32 used at +0x410) — consumer, not setter. BGFX_MAP.md has no Encoder setVertexBuffer RVA (only D3D12 setVertexBuffers 0xe81b4d0).

METHOD (static, exe only; no tools.rtools.*): rdis fld 0x680 --w / --r over all of .text (1618 accesses). No write to [reg+0x680] exists anywhere in 0xbc60000-0xbc62000; the only non-zero pointer store to [reg+0x680] tied to the encoder object is in 0xBC6E360. Verbatim proof lines below were copied from rdis dis output and re-checked against the exe.

FINDING — setter = 0xBC6E360 (sub_bc6e360; 1 xref in: 0xbcc3486 call 0xBC6E360 inside sub_bcc3190; at the call rcx=rsi=encoder this, dl=byte [rax+4] = stream index checked <=5, r9d=0x1C=28 count-ish, stack supplies record base/stride/count):
- 0xbc6e38b mov rax,[rcx+0x680]; test rax,rax; jne skip — setter itself reads Encoder+0x680 (table ptr) first
- lazy alloc: rcx=[0x12ADF800] (bx::AllocatorI global, slot 1 = realloc); mov r8d,0x418 (0x41 entries x 0x10 + u32 used @+0x410); call qword ptr [0xF99FFA0] (sub_eea6040) -> r14 = new table; call 0xEEC6ED0(memset(table,0,0x410))
- 0xbc6e3da mov [rbx+0x680],r14 — THE WRITE OF ENCODER+0x680 (qword table pointer); 0xbc6e3e1 mov dword ptr [r14+0x410],0 (table.used = 0)
- entry[stream] at r13 = table + stream*0x10: 0xbc6e4a7 mov [r13],r14 (entry.data); 0xbc6e4ab mov [r13+8],rbp (entry.count = start+count); per-range loop grows the entry.data array of 0x14-byte records; 0xbc6e4d7 inc dword ptr [r8+0x410] (table.used++)
- 0xbc6e533 mov byte ptr [rbx+0x688],1 — sets dirty flag +0x688 = 1
- also tags RenderBind slot[stream]: 0xbc6e402 mov word ptr [rbx+rdx*4+0x14A],0; 0xbc6e40c mov byte ptr [rbx+rdx*4+0x153],6 (tag 6 = vertex buffer)
Sibling same-pattern functions ([I] context only, not proven to touch the submit encoder's +0x680): 0xBC6E550 writes [rbx+0x680] at 0xbc6e5ca with slot tag 8 at +0x153; 0xBC6E9A0 writes [rbx+0x680] at 0xbc6ea1e. Zeroing stores [rdi+0x680]=0 at 0xbc641dd (sub_bc63c80) and 0xbc66840 (sub_bc660a0, view/other object per docs/functions/0xbc660a0.md) are cleanup, not the setter.

RESULT TABLE (name | offset | size | verbatim `0xRVA  instr` proof | meaning | tag):
| Encoder+0x680 vertex-buffer range table pointer (store) | +0x680 | 8 (qword) | `0xbc6e3da  mov [rbx+0x680],r14` | 0xBC6E360 lazily allocates the 0x418-byte table and stores its pointer here; table = 0x41 x {Binding* @+0, u64 count @+8} + u32 used @+0x410, the table 0xBC60F10 reads at 0xbc60b4f | [V]
| Encoder+0x688 vertex-buffer ranges dirty flag | +0x688 | 1 (byte) | `0xbc6e533  mov byte ptr [rbx+0x688],1` | Setter sets dirty = 1 (submit/reset consume and clear it) | [V]
| RenderBind slot[stream] u16 field @+0xA | +0x14A + stream*0x14 | 2 (word) | `0xbc6e402  mov word ptr [rbx+rdx*4+0x14A],0` | Slot field cleared per stream | [V]
| RenderBind slot[stream] type tag byte @+0x13 | +0x153 + stream*0x14 | 1 (byte) | `0xbc6e40c  mov byte ptr [rbx+rdx*4+0x153],6` | Tag 6 = vertex buffer | [V]
| Table entry[stream].data (Binding* ptr) | table+0 (entry) | 8 | `0xbc6e4a7  mov [r13],r14` | r13 = table + stream*0x10; entry data pointer = allocated array of 0x14-byte range records | [V]
| Table entry[stream].count (u64) | table+8 (entry) | 8 | `0xbc6e4ab  mov [r13+8],rbp` | Entry count = start+count; ranged binds appended per stream | [V]
| Table used count | table+0x410 | 4 (dword) | `0xbc6e3e1  mov dword ptr [r14+0x410],0` | `0xbc6e4d7  inc dword ptr [r8+0x410]` | Initialized to 0 at allocation, incremented per range written | [V]

ANSWER: The setter filling the encoder vertex-buffer range table is the bgfx::Encoder::setVertexBuffer-style fn **0xBC6E360** (Encoder* this = rcx; stream index u8 = dl; ranges via array/stack args), sole call site `0xbcc3486  call 0xBC6E360` in sub_bcc3190. It writes Encoder+0x680 (proven at 0xbc6e3da), sets dirty flag Encoder+0x688 = 1 (proven at 0xbc6e533), and fills the 0x41 x {Binding*, count} table with per-range 0x14 records — exactly the table consumed by 0xBC60F10 at 0xbc60b4f into Frame+0x8B4778 SideTables. Storage side (6fe) and setter side are both decoded.

CLOSES? YES — every pending part of A12b is proven by [V] rows above: the setter filling Encoder+0x680 is found and verified; the RTX skinning range check (0xe83f1d0, 6ei) was already found. No blocking fact remains.
