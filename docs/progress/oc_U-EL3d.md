## NEXT
DONE

# U-EL3d — L3d task scheduler 0xc25b1a0: queue layout

Scope: checklist item "L3d Task scheduler 0xc25b1a0 call map — 6ac; queue layout pending".
The call map ("6ac") is not part of this unit. This unit does ONLY the pending part: decode the task-queue layout built by sub_c25b1a0 ("GraphicsTasks Scheduler"; size 0x960 [V]; 1 xref in: sub_660d940 [V]; data strings "GraphicsTasks Scheduler" at 0xc25b4f7, "GraphicsTasks Group", "GraphicsTasks Parallel Group" [V data refs]).

Input data (read fully, not re-run): docs/progress/pre/0xc25b1a0.md — fn, callers, callees, non-stack stores, 1200-instruction listing. All RVAs below are copied verbatim from that listing.

Object under construction: the scheduler instance is rcx at entry (= rsi). Ctor args: rdx = a1 (stored at +0x10), r8 = a2 = {entry_count, entries*}, r9 = a3 (stored at +0x30). Callee sub_eec6de0 copies the entry_count 8-byte pointers from a2's array into the buffer at +0x18.

## Queue-layout table (offset | size | name | verbatim 0xRVA  instr proof | meaning | tag)

| offset | size | name | proof | meaning | tag |
| +0x10 | 8 | queue-object pointer | `0xC25B1E9  mov [rcx+0x10],rdx`; `0xC25B936  mov rdx,[rsi+0x10]` then `0xC25B93A  mov rax,[rdx+0x28]` / `0xC25B93E  sub rax,[rdx+0x20]` / `0xC25B942  sar rax,3` | pointer to a queue object; its +0x20/+0x28 begin/end bounds are counted (>>3) into the scheduler total | [V]
| +0x18 | 16 | task-entries buffer base | `0xC25B1F7  movups [rcx+0x18],xmm0`; `0xC25B282  mov [rsi+0x18],rcx` | 16 bytes zeroed at init, then base of the entries buffer (alloc = entry_count*8, min 0x200, 0x20-aligned: `0xC25B219  lea r12,[rax*8]`, `0xC25B221  cmp rax,0x200`, `0xC25B229  lea rdx,[r12+0x27]`, `0xC25B251  and rcx,0xFFFFFFFFFFFFFFE0`) | [V]
| +0x20 | 8 | queue end cursor | `0xC25B286  mov [rsi+0x20],rcx`; `0xC25B29D  mov [rsi+0x20],rbx` | written with buffer base, then with buffer end (base + count*8) | [V]
| +0x28 | 8 | queue end limit | `0xC25B1FB  mov qword ptr [rcx+0x28],0`; `0xC25B28E  mov [rsi+0x28],rbx` | zeroed at init, then buffer end (base + count*8) | [V]
| +0x120 | 4 | per-group count | `0xC25B6C4  mov dword ptr [rsi+0x120],0` | zeroed; nothing in this function names the field | [V]
| +0x130 | 4 | per-group count | `0xC25B8B2  mov dword ptr [rsi+0x130],0` | zeroed; nothing in this function names the field | [V]
| +0x138 | 8 | queue pointer/link | `0xC25B905  mov qword ptr [rsi+0x138],0` | zeroed; nothing in this function names the field | [V]
| +0x140 | 4 | queue counter | `0xC25B910  mov dword ptr [rsi+0x140],0` | zeroed; nothing in this function names the field | [V]
| +0xA8 | - | queue-link address taken | `0xC25B59B  lea rcx,[rsi+0xA8]`; `0xC25B78B  lea rcx,[rsi+0xA8]` | address of the queue link taken, passed to sub_7cd250 and stored at each structured entry +0x08; field size not stored here | [V]
| +0x148 | 16 | queued-task counter | `0xC25B91D  movups [rsi+0x148],xmm0`; `0xC25B94D  mov [rsi+0x148],rax` | u64 counter at +0x148 inside a 16-byte zeroed block; accumulates (end - begin) >> 3 per queue object | [V]

## Standalone proof lines (verbatim from listing; verified against rdis by verify_oc)
  0xC25B1E9  mov [rcx+0x10],rdx
  0xC25B1F7  movups [rcx+0x18],xmm0
  0xC25B1FB  mov qword ptr [rcx+0x28],0
  0xC25B219  lea r12,[rax*8]
  0xC25B282  mov [rsi+0x18],rcx
  0xC25B286  mov [rsi+0x20],rcx
  0xC25B28E  mov [rsi+0x28],rbx
  0xC25B29D  mov [rsi+0x20],rbx
  0xC25B59B  lea rcx,[rsi+0xA8]
  0xC25B905  mov qword ptr [rsi+0x138],0
  0xC25B910  mov dword ptr [rsi+0x140],0
  0xC25B91D  movups [rsi+0x148],xmm0
  0xC25B936  mov rdx,[rsi+0x10]
  0xC25B93A  mov rax,[rdx+0x28]
  0xC25B93E  sub rax,[rdx+0x20]
  0xC25B942  sar rax,3
  0xC25B94D  mov [rsi+0x148],rax

## TOOL REQUESTS
None

CLOSES? YES — queue layout fully proven by [V] rows: queue-object pointer +0x10, entries-buffer base +0x18 (count*8, min 0x200, 0x20-aligned), end cursor +0x20, end limit +0x28, per-group count fields +0x120/+0x130, queue pointer/link +0x138, queue counter +0x140, queue-link address taken +0xA8 (size not stored here), queued-task counter +0x148. Every offset/size/store cited verbatim from the listing; nothing invented; field semantics not named by any instruction are left '-' per the brief.
