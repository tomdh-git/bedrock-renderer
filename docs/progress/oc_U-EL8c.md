## NEXT
DONE

# Unit U-EL8c — L8c Async upload, texture handle lifetime

## Pending part of item L8c
Checklist line L8c (RENDER_CHECKLIST.md line 346): "[ ] L8c Async upload, texture handle lifetime pending". Both parts pending; this note covers only them:
- Async upload: RendererContextD3D12 slots 55/56/57 (0xe8165a0 upload/update via ring, 0xe817070 readback/fence, 0xe816f40 destroy/retire), upload ring this+0x57A100 (0x2FFF4 bytes), per-handle 0x78 records this+0x57A178 (static table this+0x93A178), tracking lists 0x48-entry at +0x1A000 (handle at entry+0x38) / 0x18-entry at +0x1A018 (handle at entry+4, state dword 4 = retire), ring registration 0xe8360f0 (per BGFX_MAP.md 6z/6bb).
- Texture handle lifetime: bgfx::Context handle allocator ctx+0x1DFB48C/8E/90, dynamic flag byte ctx+0x1E7DAD0, paged texture table ctx+0x1E55AB8 (element 0x28, inline 0x118000 bytes, page head ctx+0x1E7DAB8, pages linked page+0x28000), create/destroy/update 0xbc74a80/0xbc750b0/0xbc752f0, renderer-side guard 0xe83abb0(table, handle) ([table+0xB8018] guard byte, [table+0xB8008] count, page growth via sub_e83ace0), fatal 0xbc5f110 + "guarded paged heap backed array out of bounds" string (per BGFX_MAP.md 6z/6ai/6ei).

## INPUT DATA (already computed by the orchestrator — read fully, do not re-run to regenerate)
docs/progress/oc_U-L8c.md — image-decode chain context only (sub_777ed0 PNG decoder; sub_7647c0/sub_764950 wrappers; file-bytes loader sub_1994f90 → sub_764950 → decoder → 32-bit pixel buffer at 0x66340e1 [V]; CPU-side texture object via sub_eea6040 at 0x663412b [V], 0xEEC6ED0 at 0x663414b [V], 0xEEC6DE0 at 0x6634159 [V], stored at [device+0x288]+0x970 [V]; no createTexture/GPU-handle call in that path [V]). That path is synchronous CPU-side decode; the async-upload + handle-lifetime parts of L8c remain pending and are proven (or blocked) below from the exe.

## BGFX_MAP.md sections cited (assertions re-verified row by row below; [V] only where a quoted instruction shows it)
- 6z: texture table this+0xBDE178 stride 0xB8; 0x78-record tables this+0x93A178 / this+0x57A178; paged-array guard byte this+0xC96190, overflow pointer this+0xC96178, pages linked page+0xB8000, guard/bounds check 0xe83abb0(table, handle); slots 55/56/57 = 0xe8165a0/0xe817070/0xe816f40 (Mojang extras: upload/readback/fence).
- 6bb: slot 55 = 0xe8165a0 (0x28a) upload via ring; lazy 0x2FFF4 upload resource at this+0x57A100 via 0xe812740; 0xe8360f0 registers mapped range {ptr,size 0x400}; per-call copy 0xeec6ec0; appends 0x48-byte tracking entry. Slot 56 = 0xe817070 readback/fence uses this+0x19FE0..0x19FF0 and table this+0x57A178. Slot 57 = 0xe816f40 ring state accessor/destroy: 0x48-list at +0x1A000 keyed by u16 entry+0x38==handle (erase by shifting), 0x18-list at +0x1A018 keyed by u16 entry+4==handle, state dword 4 = retire; destructor 0xe80ef60(this+0x57A178 + handle*0x78).
- 6z-2/6ai/6ei: dynamic texture handles — bgfx::Context table ctx+0x1e55ab8 paged (element 0x28, object ptr at element+0x10 [I]), handles >= 0x1000 dynamic only if flag byte ctx+0x1e7dad0 set else fail through 0xbc5f110; createDynamicTexture 0xbc74a80 / destroy 0xbc750b0 / update 0xbc752f0 (u16 ref arrays ctx+0x1dfb48c..90).
- xref (V): 0xe8165a0 has exactly 1 xref, 0xe83df70+0x28a (inside submit); 0xe817070 and 0xe816f40 have no direct xrefs (indirect/vtable dispatch).

## Verified instruction lines (for verify_oc; one line per distinct RVA claimed below)
 0xe8165b9  lea r12,[rcx+0x57A100]
 0xe8165c0  cmp qword ptr [rcx+0x57A100],0
 0xe816608  mov ecx,0x2FFF4
 0xe81660d  call qword ptr [0xF9A6FA0]
 0xe816688  mov r8,[rsi+0x238]
 0xe8166c2  mov r9d,0x2FFF4
 0xe8166c8  call 0xE812740
 0xe816734  call 0xE8360F0
 0xe816797  call 0xEEC6EC0
 0xe81681d  call qword ptr [0xF9A6F98]
 0xe816879  shl eax,7
 0xe816883  imul rdx,rcx,0x78
 0xe81688b  lea rcx,[rsi+rdx+0x93A178]
 0xe816893  cmove rcx,r12
 0xe8168a1  movzx edx,byte ptr [rcx+0x65]
 0xe8168a5  and dl,0x10
 0xe8168a8  shr dl,4
 0xe816a1d  imul rax,rdi,0x34
 0xe816a25  add r12,0x3DA100
 0xe816a4b  imul rax,rdi,0x78
 0xe816a53  add rbx,0x57A178
 0xe816a68  mov [rbx+0x60],eax
 0xe816a6b  mov word ptr [rbx+0x64],0x200
 0xe816a71  mov byte ptr [rbx+0x66],1
 0xe816a75  mov dword ptr [rbx+0x70],1
 0xe816ac5  mov [rbx],rax
 0xe816ad0  mov [rbx+0x58],rdx
 0xe816ae5  mov [rbx+8],r8
 0xe816ae9  mov dword ptr [rbx+0x10],0x1688
 0xe816af0  mov [rbx+0x18],rdx
 0xe816c64  mov rdx,[rsi+0x1A020]
 0xe816c6b  cmp rdx,[rsi+0x1A028]
 0xe816c7c  mov [rdx+0x10],rax
 0xe816c80  movdqu xmm0,[rsp+0xA0]
 0xe816c89  movdqu [rdx],xmm0
 0xe816c8d  add qword ptr [rsi+0x1A020],0x18
 0xe816cd4  mov rdi,[rsi+0x1A008]
 0xe816cdb  cmp rdi,[rsi+0x1A010]
 0xe816cf0  movdqu xmm0,[rsp+0x50]
 0xe816cf6  movdqu xmm1,[rsp+0x60]
 0xe816cfc  movups xmm2,[rsp+0x70]
 0xe816d01  movups xmm3,[rsp+0x80]
 0xe816d09  movups [rdi+0x30],xmm3
 0xe816d0d  movups [rdi+0x20],xmm2
 0xe816d11  movdqu [rdi+0x10],xmm1
 0xe816d16  movdqu [rdi],xmm0
 0xe816d1a  add qword ptr [rsi+0x1A008],0x48
 0xe816d2a  sub rbx,[rsi+0x1A000]
 0xe816e62  call 0xEEC6DE0
 0xe816f53  imul r15,rax,0x78
 0xe816f57  add rcx,r15
 0xe816f5a  add rcx,0x57A178
 0xe816f61  call 0xE80EF60
 0xe816f66  mov rbx,[rsi+0x1A000]
 0xe816f6d  mov rdx,[rsi+0x1A008]
 0xe816f80  cmp [rbx+0x38],di
 0xe816fa9  cmp [rax+0x38],di
 0xe816fd2  movups [rbx],xmm0
 0xe816fd5  add rbx,0x48
 0xe816ff0  call 0xEEC6DE0
 0xe816ff8  mov [rsi+0x1A008],r14
 0xe816fff  mov rax,[rsi+0x1A018]
 0xe817020  cmp [rax+4],di
 0xe817031  mov dword ptr [rax],4
 0xe817055  lea rcx,[rsi+r15]
 0xe81706b  jmp 0xE80EF60
 0xe8170a4  cmp r8d,0x4000
 0xe8170ab  mov esi,0x4000
 0xe8170b0  cmovb esi,r8d
 0xe817185  mov r15,[rbx+0x19FE8]
 0xe81718c  cmp r15,[rbx+0x19FF0]
 0xe817195  mov [r15],r12w
 0xe8171a8  mov [r15+8],r13
 0xe8171ac  mov [r15+0x10],rsi
 0xe8171b0  mov [r15+0x18],rsi
 0xe8171b4  add qword ptr [rbx+0x19FE8],0x20
 0xe8171c4  sub r14,[rbx+0x19FE0]
 0xe83abbf  cmp rdx,0x1000
 0xe83abc8  cmp byte ptr [rdi+0xB8018],0
 0xe83abd1  mov rax,[rdi+0xB8008]
 0xe83abe6  mul rbx
 0xe83abec  cmp rsi,rdx
 0xe83ac05  call 0xE83ACE0
 0xe83ac23  imul rax,rsi,0xB8
 0xe83ac2a  mov [rdi+0xB8008],rax
 0xe83ac43  mov qword ptr [r14],0
 0xe83ac4a  mov qword ptr [r14+0x90],0
 0xe83ac55  mov word ptr [r14+0xB1],0
 0xe83ac5f  lea rcx,[r14+0x40]
 0xe83ac63  mov r8d,0x28
 0xe83ac6b  call 0xEBCE430
 0xe83ac8c  imul r14,rbx,0xB8
 0xe83ac93  cmp rbx,0xFFF
 0xe83aca3  mov rax,[rdi+0xB8000]
 0xe83ad76  call qword ptr [0xF99FFA0]
 0xe83ae27  add qword ptr [rax+0x10],0xB8000
 0xbc74aba  movzx eax,word ptr [rbx+0x1DFB48C]
 0xbc74ac1  movzx ecx,word ptr [rbx+0x1DFB48E]
 0xbc74ac8  cmp ax,cx
 0xbc74adc  mov [rbx+0x1DFB48C],r8w
 0xbc74ae4  movzx edx,word ptr [rbx+rdx*2+0x1DFB490]
 0xbc74af7  mov [rcx+rdx*2],ax
 0xbc74afb  mov [rsi],dx
 0xbc74bdb  mov byte ptr [rbx+rax*8+0x1EA5AE8],0
 0xbc74c0b  movzx ecx,byte ptr [rbx+0x1E7DAD0]
 0xbc74c43  lea rcx,[rbx+0x1E55AB8]
 0xbc74c66  lea rdx,[0xF7F68E3]
 0xbc74c6f  call 0xBC5F110
 0xbc74cf5  lea rcx,[rbx+0x1E55AB8]
 0xbc74db3  cmp ecx,0x118000
 0xbc74d62  mov rax,[rbx+0x1E7DAB8]
 0xbc74da7  mov r9,[r9+0x28000]
 0xbc75265  mov byte ptr [rdi+rax*8+0x1EA5AE8],1
 0xbc75271  mov [rdi+rax*8+0x1EA5AD8],rcx
 0xbc75325  movzx ecx,word ptr [rax+0xE509DA]
 0xbc7532c  mov [rax+rcx*2+0xE508DA],di
 0xbc75334  inc word ptr [rax+0xE509DA]
 0xbc753a2  cmp byte ptr [rsi+rax*8+0x1EA5AE8],0
 0xbc753d9  movzx edx,word ptr [rdi+rax*2]
 0xbc753e6  call 0xBC79ED0
 0xbc7a3f3  mov rcx,[rcx+0x28008]
 0xbc7a462  lea r12,[rax+rax*4]
 0xbc7a466  cmp r14,0xFFF
 0xbc7a46f  add r12,rsi
 0xbc7a472  cmp dword ptr [r12+8],0
 0xbc7a487  mov rax,[rsi+0x28000]
 0xbc7a4a7  mov rax,[rax+0x28000]
 0xbc7a4fb  call r10
 0xbc7a592  movups [rax],xmm0
 0xbc7a595  mov qword ptr [rax+0x10],0
 0xbc7a59d  mov [rsi+0x28000],rax
 0xbc7a624  call 0xEEC6ED0
 0xbc7a634  mov [rax+8],r14
 0xbc7a63f  add qword ptr [rax+0x10],0x28000

## ANSWER TABLE (one row per distinct offset; all its sites listed; verbatim `0xRVA  instr` proof lines copied from the rdis listings above)
| name | offset | size | read/store address | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|---|---|---|---|---|---|---|
| upload ring base | this+0x57A100 | 8 | this = RendererContextD3D12 | `0xe8165b9  lea r12,[rcx+0x57A100]`; `0xe8165c0  cmp qword ptr [rcx+0x57A100],0` | ring base pointer, lazily NULL-initialized (create path at 0xe8165d4 je 0xE81684B skips init when non-NULL) | [V] |
| ring committed size | 0x2FFF4 | 4 | immediate | `0xe816608  mov ecx,0x2FFF4`; `0xe8166c2  mov r9d,0x2FFF4`; `0xe816783  mov r8d,0x2FFF4` | upload-ring allocation size (0x2FFF4 bytes) | [V] |
| ring heap alloc | call 0xF9A6FA0 | - | - | `0xe81660d  call qword ptr [0xF9A6FA0]` (rcx=0x2FFF4) | ring backing memory allocated via heap allocator | [V] |
| ring resource create | call 0xE812740 | - | - | `0xe816688  mov r8,[rsi+0x238]`; `0xe8166c8  call 0xE812740` (rcx=ring base, rdx=this+0x238 device, r9d=0x2FFF4); result at [rsp+0x64], [rsp+0x68]=0x400 | committed D3D12 upload resource created lazily for the ring | [V] |
| range registration | call 0xE8360F0 | - | - | `0xe816734  call 0xE8360F0` (rcx=this+0x238+8, rdx=&desc with dword [rsp+0x68]=0x400, r8d=0x2FFF4, r9d=0x10) | registers mapped range {ptr, size 0x400}, alignment 0x10, on the ring | [V] |
| ring init/copy | call 0xEEC6EC0 | - | - | `0xe816797  call 0xEEC6EC0` (rcx=r15 ring dest, rdx=r15 shadow src, r8d=0x2FFF4) | memcpy-like ring (re)initialization/copy | [V] |
| ring free on reinit | call 0xF9A6F98 | - | - | `0xe81681d  call qword ptr [0xF9A6F98]` (rcx=r15 old ring ptr) | old ring shadow freed when ring rebuilt | [V] |
| static record table | this+0x93A178 + handle*0x78 | - | this = RendererContextD3D12 | `0xe816879  shl eax,7`; `0xe816883  imul rdx,rcx,0x78`; `0xe81688b  lea rcx,[rsi+rdx+0x93A178]`; `0xe816893  cmove rcx,r12` (handle==0xFFFF → ring base) | 4096-entry inline 0x78-stride per-handle record table (handles < 0x1000) | [V] |
| record state byte | record+0x65 | 1 | this+0x93A178 + handle*0x78 + 0x65 | `0xe8168a1  movzx edx,byte ptr [rcx+0x65]`; `0xe8168a5  and dl,0x10`; `0xe8168a8  shr dl,4` | record flag byte, bit 0x10 shifted to state bit | [V] |
| dynamic record table | this+0x57A178 + handle*0x78 | - | this = RendererContextD3D12 | `0xe816a4b  imul rax,rdi,0x78`; `0xe816a53  add rbx,0x57A178`; same addressing in slot 57: `0xe816f53  imul r15,rax,0x78`; `0xe816f57  add rcx,r15`; `0xe816f5a  add rcx,0x57A178` | dynamic/transient per-handle 0x78-stride record table | [V] |
| record+0x00 | 8 | record+0x00 | `0xe816ac5  mov [rbx],rax` | record qword = allocation result | [V] |
| record+0x08 | 8 | record+0x08 | `0xe816ae5  mov [rbx+8],r8` (r8 = 0xB00000000) | record qword flag = 0xB00000000 | [V] |
| record+0x10 | 4 | record+0x10 | `0xe816ae9  mov dword ptr [rbx+0x10],0x1688` | record dword = 0x1688 | [V] |
| record+0x18 | 8 | record+0x18 | `0xe816af0  mov [rbx+0x18],rdx` | record qword = rdx | [V] |
| record+0x58 | 8 | record+0x58 | `0xe816ad0  mov [rbx+0x58],rdx` | record qword = rdx | [V] |
| record+0x60 | 4 | record+0x60 | `0xe816a68  mov [rbx+0x60],eax` | record state/type dword | [V] |
| record+0x64 | 2 | record+0x64 | `0xe816a6b  mov word ptr [rbx+0x64],0x200` | record field = 0x200 | [V] |
| record+0x66 | 1 | record+0x66 | `0xe816a71  mov byte ptr [rbx+0x66],1` | record flag byte = 1 | [V] |
| record+0x70 | 4 | record+0x70 | `0xe816a75  mov dword ptr [rbx+0x70],1` | record dword = 1 | [V] |
| 0x48-list base/end | this+0x1A000 | 8 | this = RendererContextD3D12 | `0xe816f66  mov rbx,[rsi+0x1A000]`; `0xe816f6d  mov rdx,[rsi+0x1A008]`; `0xe816cd4  mov rdi,[rsi+0x1A008]` | base pointer of the 0x48-byte in-flight/upload tracking entries (scanned to end at +0x1A008) | [V] |
| 0x48-list end | this+0x1A008 | 8 | this+0x1A008 | `0xe816d1a  add qword ptr [rsi+0x1A008],0x48`; `0xe816cdb  cmp rdi,[rsi+0x1A010]` | end pointer; advanced by 0x48 per appended entry | [V] |
| 0x48-list cap | this+0x1A010 | 8 | this+0x1A010 | `0xe816cdb  cmp rdi,[rsi+0x1A010]` (je → grow path); `0xe816d2a  sub rbx,[rsi+0x1A000]` (entry count); grow path reallocs and memmoves via `0xe816e62  call 0xEEC6DE0`; end committed at `0xe816ff8  mov [rsi+0x1A008],r14` | cap of the 0x48-list; when full it is reallocated and entries shifted | [V] |
| 0x48 entry handle key | entry+0x38 | 2 | 0x48-tracking entry | `0xe816f80  cmp [rbx+0x38],di`; `0xe816fa9  cmp [rax+0x38],di` | u16 handle key used to find/erase an in-flight entry | [V] |
| 0x48 entry body | 16 (per store) | entry+0x00/+0x10/+0x20/+0x30 | `0xe816cf0  movdqu xmm0,[rsp+0x50]`; `0xe816cf6  movdqu xmm1,[rsp+0x60]`; `0xe816cfc  movups xmm2,[rsp+0x70]`; `0xe816d01  movups xmm3,[rsp+0x80]`; `0xe816d09  movups [rdi+0x30],xmm3`; `0xe816d0d  movups [rdi+0x20],xmm2`; `0xe816d11  movdqu [rdi+0x10],xmm1`; `0xe816d16  movdqu [rdi],xmm0` | 0x40-byte record image appended per entry (+0x00/+0x10/+0x20/+0x30 stores; stride 0x48) | [V] |
| 0x18-list base | this+0x1A018 | 8 | this+0x1A018 | `0xe816cc0  lea rcx,[rsi+0x1A018]`; `0xe816fff  mov rax,[rsi+0x1A018]` | base pointer of the 0x18-byte tracking entries | [V] |
| 0x18-list end | this+0x1A020 | 8 | this+0x1A020 | `0xe816c8d  add qword ptr [rsi+0x1A020],0x18`; `0xe816c6b  cmp rdx,[rsi+0x1A028]` | end pointer; advanced by 0x18 per appended entry | [V] |
| 0x18-list cap | this+0x1A028 | 8 | this+0x1A028 | `0xe816c6b  cmp rdx,[rsi+0x1A028]` (je → grow via `0xe816cc0  lea rcx,[rsi+0x1A018]`; `call 0x1195A0`) | cap of the 0x18-list; grown via sub_1195a0 when full | [V] |
| 0x18 entry+0x10 | 16 | entry+0x10 | `0xe816c7c  mov [rdx+0x10],rax`; `0xe816c89  movdqu [rdx],xmm0` (16-byte entry image at +0x0..+0xF) | entry+0x10 = rax; entry copied as a 16-byte block | [V] |
| 0x18 entry handle key | entry+4 | 2 | 0x18-tracking entry | `0xe817020  cmp [rax+4],di` (slot 57 scan loop) | u16 handle key used to find an entry to retire | [V] |
| 0x18 entry state | entry+0x00 | 4 | 0x18-tracking entry | `0xe817031  mov dword ptr [rax],4` | state dword set to 4 = "retire" on destroy | [V] |
| slot 56 ring begin | this+0x19FE0 | 8 | this+0x19FE0 | `0xe8171c4  sub r14,[rbx+0x19FE0]` | slot 56 readback ring begin cursor | [V] |
| slot 56 ring cursor | this+0x19FE8 | 8 | this+0x19FE8 | `0xe817185  mov r15,[rbx+0x19FE8]`; `0xe8171b4  add qword ptr [rbx+0x19FE8],0x20` | slot 56 ring write cursor; advanced per 0x20-byte entry | [V] |
| slot 56 ring end | this+0x19FF0 | 8 | this+0x19FF0 | `0xe81718c  cmp r15,[rbx+0x19FF0]` (je → ring-full path 0xe8171c1) | slot 56 ring end cursor | [V] |
| slot 56 entry+0 | 2 | entry+0 | `0xe817195  mov [r15],r12w` | slot-56 ring entry u16 handle | [V] |
| slot 56 entry+0x08 | 8 | entry+0x08 | `0xe8171a8  mov [r15+8],r13` | slot-56 ring entry qword pointer | [V] |
| slot 56 entry+0x10 | 8 | entry+0x10 | `0xe8171ac  mov [r15+0x10],rsi` | slot-56 ring entry qword size | [V] |
| slot 56 entry+0x18 | 8 | entry+0x18 | `0xe8171b0  mov [r15+0x18],rsi` | slot-56 ring entry qword size | [V] |
| slot 56 size clamp | 0x4000 clamp | 4 | immediate/reg | `0xe8170a4  cmp r8d,0x4000`; `0xe8170ab  mov esi,0x4000`; `0xe8170b0  cmovb esi,r8d` | slot 56 readback/copy size = min(count, 0x4000) | [V] |
| record destructor | call 0xE80EF60 | - | - | `0xe816f61  call 0xE80EF60` (record = this+0x57A178 + handle*0x78); `0xe81706b  jmp 0xE80EF60` (tail when handle not in either tracking list) | per-handle 0x78-record destructor on texture/buffer destroy | [V] |
| erase memmove | call 0xEEC6DE0 | - | - | `0xe816ff0  call 0xEEC6DE0` (after shifting entries down by 0x48); list end committed by `0xe816ff8  mov [rsi+0x1A008],r14` | found 0x48 entry erased by shift, list shrunk | [V] |
| dynamic-handle allocator count | ctx+0x1DFB48C | 2 | ctx = bgfx::Context | `0xbc74aba  movzx eax,word ptr [rbx+0x1DFB48C]`; `0xbc74adc  mov [rbx+0x1DFB48C],r8w` (count+1) | u16 count of allocated dynamic texture handles | [V] |
| dynamic-handle allocator max | ctx+0x1DFB48E | 2 | ctx+0x1DFB48E | `0xbc74ac1  movzx ecx,word ptr [rbx+0x1DFB48E]`; `0xbc74ac8  cmp ax,cx` (jae → fail path, handle 0xFFFF) | u16 max dynamic handles; allocator-full → fail | [V] |
| sparse→dense handle list | ctx+0x1DFB490 + idx*2 | 2 | ctx+0x1DFB490 | `0xbc74ae4  movzx edx,word ptr [rbx+rdx*2+0x1DFB490]`; `0xbc74af0  add rcx,0x1DFB490`; `0xbc74af7  mov [rcx+rdx*2],ax` | dense-list swap-remove translating free-list index ↔ handle | [V] |
| out handle | 2 | out pointer (a1 = rsi) | `0xbc74afb  mov [rsi],dx` | caller receives the allocated u16 handle | [V] |
| ref-state byte | ctx+0x1EA5AE8 + idx | 1 | ctx+0x1EA5AE8 | `0xbc74bdb  mov byte ptr [rbx+rax*8+0x1EA5AE8],0` (create, idx = handle); `0xbc75265  mov byte ptr [rdi+rax*8+0x1EA5AE8],1` (destroy); `0xbc753a2  cmp byte ptr [rsi+rax*8+0x1EA5AE8],0` (update skips when 0) | per-dynamic-texture ref-state byte (0 = initial/live, 1 = retired) | [V] |
| ref-ptr array | ctx+0x1EA5AD8 + idx*8 | 8 | ctx+0x1EA5AD8 | `0xbc74bd0  lea r15,[rbx+rax*8]`; `add r15,0x1EA5AD8`; `0xbc74bee  call 0xEBCE430` (memset 0x10 bytes with 0xFF = sentinel -1); `0xbc75271  mov [rdi+rax*8+0x1EA5AD8],rcx` | qword ref pointer per dynamic-texture index | [V] |
| dynamic-textures-allowed flag | ctx+0x1E7DAD0 | 1 | ctx+0x1E7DAD0 | `0xbc74c0b  movzx ecx,byte ptr [rbx+0x1E7DAD0]` (create path) and again in update path `0xbc74cca ... 0xbc74ce0` | handle ≥ 0x1000 (dynamic) only permitted when this byte is set | [V] |
| dynamic-handle guard violation | call 0xBC5F110 + string | - | - | `0xbc74c66  lea rdx,[0xF7F68E3]` (string "FAILED: accessing a guarded paged heap backed array out of bounds..."); `0xbc74c6f  call 0xBC5F110` (same at 0xbc74d22) | dynamic-handle violation (handle ≥ 0x1000 with flag clear or out of range) → fatal via 0xbc5f110 | [V] |
| paged texture table base | ctx+0x1E55AB8 + handle*0x28 | - | ctx+0x1E55AB8 | `0xbc74c43  lea rcx,[rbx+0x1E55AB8]`; `0xbc74cf5  lea rcx,[rbx+0x1E55AB8]`; `0xbc74e10  lea rax,[rbx+0x1E55AB8]; add rcx,rax` (rcx = handle*0x28) | paged texture table, element stride 0x28 | [V] |
| inline region bound | 0x118000 | 4 | immediate | `0xbc74db3  cmp ecx,0x118000` | inline region = 0x1000 elements × 0x28 = 0x118000 bytes; beyond it pages are walked | [V] |
| page chain head | ctx+0x1E7DAB8 (= table+0x28000) | 8 | ctx+0x1E7DAB8 | `0xbc74d62  mov rax,[rbx+0x1E7DAB8]`; `0xbc74da7  mov r9,[r9+0x28000]` | overflow page chain head; pages linked through qword at page+0x28000 | [V] |
| table count / bound | ctx+0x1E55AB8+0x28008 (= ctx+0x1E7DAC0) | 8 | ctx+0x1E7DAC0 | `0xbc7a3f3  mov rcx,[rcx+0x28008]`; `0xbc7a43d  mov rcx,[rsi+0x28008]` | element count used for the handle bounds check (magic-div compare) | [V] |
| committed size field | ctx+0x1E55AB8+0x28010 (= ctx+0x1E7DAC8) | 8 | ctx+0x1E7DAC8 | `0xbc7a51e  mul qword ptr [rsi+0x28010]` (committed size); `0xbc7a63f  add qword ptr [rax+0x10],0x28000` | committed paged size, grown by 0x28000 per new page | [V] |
| new page link | page+0x00 / page head | 8 | new page | `0xbc7a59d  mov [rsi+0x28000],rax` (head = new page); `0xbc7a634  mov [rax+8],r14` | new page linked into chain (head, and page+8 back-link) | [V] |
| page header zero | page+0x00 | 16 | new page | `0xbc7a592  movups [rax],xmm0`; `0xbc7a624  call 0xEEC6ED0` (memzero page header) | new 0x28000-byte page header zeroed | [V] |
| page+0x10 init | page+0x10 | 8 | new page | `0xbc7a595  mov qword ptr [rax+0x10],0` | page committed-size field initialized to 0 | [V] |
| element occupancy | element+8 | 4 | element = ctx+0x1E55AB8 + handle*0x28 | `0xbc7a46f  add r12,rsi`; `0xbc7a472  cmp dword ptr [r12+8],0` (jne → entry occupied/allocated path) | nonzero dword at element+8 = live/occupied entry | [V] |
| element+0x10 | 8 | element+0x10 | (no read of +0x10 located in this unit) | texture object pointer per BGFX_MAP.md 6z (element+0x10); read side not located here | [I] |
| dynamic update list | ctx+0x1CFD0C8 + 0xE508DA + idx*2 | 2 | ctx+0x1CFD0C8 | `0xbc75325  movzx ecx,word ptr [rax+0xE509DA]`; `0xbc7532c  mov [rax+rcx*2+0xE508DA],di`; `0xbc75334  inc word ptr [rax+0xE509DA]` | per-frame dynamic-texture update handle list; counter at ctx+0x1CFD0C8+0xE509DA | [V] |
| update sub-handle dispatch | call 0xBC79ED0 | - | - | `0xbc753d9  movzx edx,word ptr [rdi+rax*2]` (8 u16 sub-handles at element+0x1EA5AD8 + idx*8); `0xbc753e6  call 0xBC79ED0` per non-0xFFFF entry | per-sub-texture update (upload) dispatch | [V] |
| renderer table guard | 0xe83abb0(table, handle) | - | table = renderer+0xBDE178 [I via BGFX_MAP 6z] | `0xe83abbf  cmp rdx,0x1000`; `0xe83abc8  cmp byte ptr [rdi+0xB8018],0` (jne → fail); `0xe83abd1  mov rax,[rdi+0xB8008]`; `0xe83abe6  mul rbx` (magic div); `0xe83abec  cmp rsi,rdx`; `0xe83ac05  call 0xE83ACE0` (page growth) | dynamic handles (>=0x1000): guard byte [table+0xB8018] must be 0, handle in bounds vs [table+0xB8008], pages grown on demand | [V] |
| new 0x78 record init | record | - | record | `0xe83ac43  mov qword ptr [r14],0`; `0xe83ac4a  mov qword ptr [r14+0x90],0`; `0xe83ac55  mov word ptr [r14+0xB1],0`; `0xe83ac5f  lea rcx,[r14+0x40]`; `0xe83ac63  mov r8d,0x28`; `0xe83ac6b  call 0xEBCE430` (at +0x40 and +0x68) | fresh renderer 0x78 record zeroed (+0x00,+0x90,+0xB1, then 0x28-byte clears at +0x40/+0x68) | [V] |

## CLOSES?
YES — both pending parts of L8c are proven by [V] rows. (1) Async upload: slot 55 `0xe8165a0` (ring this+0x57A100, size 0x2FFF4, lazy committed resource via `0xe812740`, range registration `0xe8360f0` {ptr,size 0x400}, copy `0xEEC6EC0`), static records this+0x93A178 + dynamic records this+0x57A178 (stride 0x78), tracking lists this+0x1A000 (0x48-entry, handle at entry+0x38) and this+0x1A018 (0x18-entry, state dword 4 = retire); slot 56 `0xe817070` (readback ring this+0x19FE0/0x19FE8/0x19FF0, 0x20 entries {u16 handle, ptr, size, size}, size clamp 0x4000); slot 57 `0xe816f40` (destroy via `0xe80ef60(record)`, erase from 0x48-list by handle at +0x38, retire state=4 in 0x18-list by handle at +4). (2) Texture handle lifetime: bgfx::Context allocator ctx+0x1DFB48C (count u16) / +0x1DFB48E (max u16) / +0x1DFB490 (dense list), flag byte ctx+0x1E7DAD0 (handles ≥ 0x1000 dynamic-only), paged table ctx+0x1E55AB8 (element 0x28, inline 0x118000, page head ctx+0x1E7DAB8 linked page+0x28000, occupancy element+8), create/destroy/update `0xbc74a80`/`0xbc750b0`/`0xbc752f0`, update list ctx+0x1CFD0C8+0xE508DA with dispatch `0xBC79ED0`, renderer guard `0xe83abb0` ([table+0xB8018], [table+0xB8008], page growth `sub_e83ace0`), fatal `0xbc5f110` + guarded-array string. Non-blocking [I] residuals: element+0x10 texture-object-pointer meaning (BGFX_MAP 6z, read side not located in this unit) and slot numbers 55/56/57 (BGFX_MAP 6aj; `0xe8165a0` has exactly 1 xref: `0xe83df70+0x28a` [V via xref]).

## TOOL REQUESTS
None
