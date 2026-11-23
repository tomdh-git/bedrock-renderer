## NEXT
DONE

# Unit U-EQ3d — consumer of converted 0xB00-byte light records at pass+0x260/+0x268

## Goal (from orchestrator, this run)

Single missing REVERSING fact: the consumer of the converted 0xB00-byte light records stored at pass+0x260/+0x268 (begin/end of the record vector, stride 0xB00). Find it, classify each record access as load/store, conclude read-only or store-exists. Result file: docs/progress/oc_U-EQ3d.md (no other file).

## Method

- Verified the writer (Light visitor tag 5, case 0x66417af) verbatim:
  - `mov rbx,[rsi+0x260]` / `cmp rbx,[rsi+0x268]` = read begin/end [V]
  - `call 0x67E90D0` copy-constructs the 0xB00 record into the slot [V]
  - `add qword ptr [rsi+0x260],0xB00` = advance begin [V]
- Searched the whole .text for stride-0xB00 (rdis `imm 0xB00`) and intersected `rdis fld 0x260 --r` / `fld 0x268 --r` listings for functions reading both offsets with one register. All `rbp`-stack hits discarded; non-stack candidates disassembled (sub_55f1450, sub_3e3fc0, sub_b67d6c0/b6c5ff0, sub_c04be30, sub_961b970/99afdd0, sub_9b0ea70, sub_bbe2d50, sub_eac3520, sub_c0a050) — none is a begin..end stride-0xB00 record consumer.
- The unique begin..end stride-0xB00 record walker is inside sub_6618810 (called per-frame from endFrame 0x66232b0, rcx=pass object). Per record it calls sub_67B8030.

## Answer table

| name | rva or offset | size | verbatim `0xRVA  instr` proof line | tag |
|---|---|---|---|---|
| Writer: Light tag 5 case reads record-vector begin | pass+0x260 (via rsi) | 8 (qword) | `0x6641846  mov rbx,[rsi+0x260]` | [V] |
| Writer: Light tag 5 case reads record-vector end | pass+0x268 (via rsi) | 8 (qword) | `0x664184d  cmp rbx,[rsi+0x268]` | [V] |
| Writer: Light tag 5 case advances begin (store) | pass+0x260 (via rsi) | 8 (qword) | `0x664186d  add qword ptr [rsi+0x260],0xB00` | [V] |
| Writer: copy-construct record into pass slot | pass+0x260 slot (rcx=begin) | 0xB00 | `0x6641867  call 0x67E90D0` | [V] |
| Consumer loop: read record-vector current/begin | object+0x268 (via r14) | 8 (qword) | `0x6619216  mov rdi,[r14+0x268]` | [V] |
| Consumer loop: read record-vector end | object+0x270 (via r14) | 8 (qword) | `0x661921d  mov rbx,[r14+0x270]` | [V] |
| Consumer loop: per-record consumer call | record pointer (rcx=rdi) | — | `0x6619230  mov rcx,rdi` / `0x6619233  call 0x67B8030` | [V] |
| Consumer loop: stride 0xB00 | current record | — | `0x6619238  add rdi,0xB00` | [V] |
| Consumer loop: loop-bound compare | current vs end | 8 | `0x661923f  cmp rdi,rbx` / `0x6619242  jne short 0x6619230` | [V] |
| Consumer loop: consume-all (store end=begin) | object+0x270 (store), object+0x268 (load) | 8 | `0x6619244  mov rax,[r14+0x268]` / `0x661924b  mov [r14+0x270],rax` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector record+0xAD8/+0xAE8 | record+0xAD8/+0xAE8 (store clear) | 8/8 | `0x67b8074  lea rdi,[rsi+0xAD8]` / `0x67b8083  movups [rdi],xmm0` / `0x67b8086  mov qword ptr [rdi+0x10],0` | [V] |
| Per-record consumer sub_67B8030: clear *(record+0xAC8)+0 | record+0xAC8 pointee (store) | 8 | `0x67b808e  mov rax,[rsi+0xAC8]` / `0x67b8095  mov rcx,[rax+8]` / `0x67b8099  mov qword ptr [rcx],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector record+0xA98/+0xAA8 | record+0xA98/+0xAA8 (store clear) | 8/8 | `0x67b80d6  mov rcx,[rsi+0xA98]` / `0x67b80e2  mov rdx,[rsi+0xAA8]` / `0x67b8120  movups [rdi],xmm0` / `0x67b8123  mov qword ptr [rdi+0x10],0` | [V] |
| Per-record consumer sub_67B8030: clear *(record+0xA88)+0 | record+0xA88 pointee (store) | 8 | `0x67b812b  mov rax,[rsi+0xA88]` / `0x67b8132  mov rcx,[rax+8]` / `0x67b8136  mov qword ptr [rcx],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector record+0xA58/+0xA68 | record+0xA58/+0xA68 (store clear) | 8/8 | `0x67b8176  mov rcx,[rsi+0xA58]` / `0x67b8182  mov rdx,[rsi+0xA68]` / `0x67b81c0  movups [rdi],xmm0` / `0x67b81c3  mov qword ptr [rdi+0x10],0` | [V] |
| Per-record consumer sub_67B8030: clear *(record+0xA48)+0 | record+0xA48 pointee (store) | 8 | `0x67b81cb  mov rax,[rsi+0xA48]` / `0x67b81d2  mov rcx,[rax+8]` / `0x67b81d6  mov qword ptr [rcx],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector record+0xA18/+0xA28 | record+0xA18/+0xA28 (store clear) | 8/8 | `0x67b8216  mov rcx,[rsi+0xA18]` / `0x67b8222  mov rdx,[rsi+0xA28]` / `0x67b8260  movups [rdi],xmm0` / `0x67b8263  mov qword ptr [rdi+0x10],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector record+0x9D8/+0x9E8 | record+0x9D8/+0x9E8 (store clear) | 8/8 | `0x67b82b6  mov rcx,[rsi+0x9D8]` / `0x67b82c2  mov rdx,[rsi+0x9E8]` / `0x67b8300  movups [rdi],xmm0` / `0x67b8303  mov qword ptr [rdi+0x10],0` | [V] |

Record = 0xB00 bytes, 44 x 0x40 elements (per oc_U-ER7 [V]). The consumer object base r14 corresponds to the pass object (endFrame passes rcx=pass); writer's rsi is pass+8, so writer's "+0x260/+0x268" == consumer's "+0x268/+0x270" — same logical record vector, observed through different register bases [structure].

## Consumer classification

The consumer is sub_6618810 (the per-frame endFrame caller, rcx = pass object), whose stride-0xB00 loop at 0x6619216..0x661924b walks [object+0x268) .. [object+0x270) (begin..end) and, per record, calls sub_67B8030 (record destructor).

- Loads: record-vector begin `[object+0x268]`, end `[object+0x270]`; per record, sub_67B8030 loads record sub-vector begin/end at record+0xAD8/+0xAE8, +0xA98/+0xAA8, +0xA58/+0xA68, +0xA18/+0xA28, +0x9D8/+0x9E8, and record+0xAC8/+0xA88/+0xA48/+0xA08/+0x9C8 single pointers.
- Stores: sub_67B8030 clears (writes zero / refcount-decrement / frees) record sub-vector fields at record+0xAD8, +0xAE8, +0xA98, +0xAA8, +0xA58, +0xA68, +0xA18, +0xA28, +0x9D8, +0x9E8, and writes pointee=0 at record+0xAC8, +0xA88, +0xA48, +0xA08, +0x9C8. The loop also stores end=begin: `[object+0x270] = [object+0x268]`.

## Conclusion

consumer is read-only: NO — a store exists.

Store: sub_67B8030 (called per record by sub_6618810's stride-0xB00 loop) clears record sub-vector fields, i.e. record offsets +0x9C8, +0x9D8, +0x9E8, +0xA08, +0xA18, +0xA28, +0xA48, +0xA58, +0xA68, +0xA88, +0xA98, +0xAA8, +0xAC8, +0xAD8, +0xAE8 (all stored/written to zero or freed), plus the vector end field [object+0x270].

Therefore the skip-when-unchanged optimization (Q3d / RewriteLightSkip) must NOT be a plain skip: it must be copy-on-write (deep-copy the 0xB00 record only when a writing consumer will run, otherwise reuse). The consumer read-only proof required by the checklist item is resolved negatively — copy-on-write is required.

## Proof of consumer identity

- sub_6618810 is called per-frame from endFrame (0x66232b0; 3 xrefs: sub_66182d0, sub_6622aa0, sub_66232b0=endFrame) [V rdis callers].
- Its stride-0xB00 loop 0x6619216..0x661924b is the ONLY begin..end stride-0xB00 record walker in .text (rdis `imm 0xB00` survey; all other `add X,0xB00` sites are buffer/shared_ptr indexing, not record begin..end loops) [V].
- Per-record target sub_67B8030 is a record destructor: clears every sub-vector inside the 0xB00 record [V verbatim above].

## CLOSES?

YES — the single missing REVERSING fact (consumer of the converted 0xB00-byte light records) is found and [V]-proven: consumer = sub_6618810 stride-0xB00 loop (per-frame, from endFrame) delegating to sub_67B8030 per record; consumer is NOT read-only (store at record fields +0x9C8..+0xAE8 via sub_67B8030), so the Q3d skip must be copy-on-write. No remaining unknown RVA/offset/meaning for this reversing fact.

Note: the broader Q3d item additionally needs hook wiring at caller 0x66417af and an in-game test (deferred per DEFERRED TESTING); those are not part of this reversing fact and are not blockers for CLOSES? YES on this unit.

## TOOL REQUESTS

None.
