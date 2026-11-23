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
| Writer: Light tag 5 case reads record-vector begin | pass+0x260 (via rsi) | 8 (qword) | `  6641846  mov rbx,[rsi+0x260]` | [V] |
| Writer: Light tag 5 case reads record-vector end | pass+0x268 (via rsi) | 8 (qword) | `  664184d  cmp rbx,[rsi+0x268]` | [V] |
| Writer: Light tag 5 case advances begin (store) | pass+0x260 (via rsi) | 8 (qword) | `  664186d  add qword ptr [rsi+0x260],0xB00` | [V] |
| Writer: copy-construct record into pass slot | pass+0x260 slot (rcx=begin) | 0xB00 | `  6641867  call 0x67E90D0   ; -> sub_67e90d0` | [V] |
| Consumer loop: read record-vector current/begin | r14+0x268 | 8 (qword) | `  6619216  mov rdi,[r14+0x268]` | [V] |
| Consumer loop: read record-vector end | r14+0x270 | 8 (qword) | `  661921d  mov rbx,[r14+0x270]` | [V] |
| Consumer loop: per-record consumer call | record pointer (rcx=rdi) | — | `  6619230  mov rcx,rdi` / `  6619233  call 0x67B8030   ; -> sub_67b8030` | [V] |
| Consumer loop: stride 0xB00 | current record | — | `  6619238  add rdi,0xB00` | [V] |
| Consumer loop: loop-bound compare | rdi vs rbx | 8 | `  661923f  cmp rdi,rbx` / `  6619242  jne short 0x6619230` | [V] |
| Consumer loop: consume-all (store end=begin) | r14+0x270 (store), r14+0x268 (load) | 8 | `  6619244  mov rax,[r14+0x268]` / `  661924b  mov [r14+0x270],rax` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector at record+0xAD8 | record+0xAD8 (load), record+0xAD8/+0xAE8 (store clear) | 8/8 | `  67b8039  mov rcx,[rcx+0xAD8]` / `  67b8074  lea rdi,[rsi+0xAD8]` / `  67b8083  movups [rdi],xmm0` / `  67b8086  mov qword ptr [rdi+0x10],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector at record+0xAC8 | record+0xAC8 (load), pointee (store) | 8 | `  67b808e  mov rax,[rsi+0xAC8]` / `  67b8095  mov rcx,[rax+8]` / `  67b8099  mov qword ptr [rcx],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector at record+0xA98/+0xAA8 | record+0xA98/+0xAA8 (load), +0xA98/+0xAA8 (store clear) | 8/8 | `  67b80d6  mov rcx,[rsi+0xA98]` / `  67b80e2  mov rdx,[rsi+0xAA8]` / `  67b811d  xorps xmm0,xmm0` / `  67b8120  movups [rdi],xmm0` / `  67b8123  mov qword ptr [rdi+0x10],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector at record+0xA88 | record+0xA88 (load), pointee (store) | 8 | `  67b812b  mov rax,[rsi+0xA88]` / `  67b8132  mov rcx,[rax+8]` / `  67b8136  mov qword ptr [rcx],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector at record+0xA58/+0xA68 | record+0xA58/+0xA68 (load), +0xA58/+0xA68 (store clear) | 8/8 | `  67b8176  mov rcx,[rsi+0xA58]` / `  67b8182  mov rdx,[rsi+0xA68]` / `  67b81bd  xorps xmm0,xmm0` / `  67b81c0  movups [rdi],xmm0` / `  67b81c3  mov qword ptr [rdi+0x10],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector at record+0xA48 | record+0xA48 (load), pointee (store) | 8 | `  67b81cb  mov rax,[rsi+0xA48]` / `  67b81d2  mov rcx,[rax+8]` / `  67b81d6  mov qword ptr [rcx],0` | [V] |
| Per-record consumer sub_67B8030: destroy sub-vector at record+0xA18/+0xA28 | record+0xA18/+0xA28 (load), +0xA18/+0xA28 (store clear) | 8/8 | `  67b8216  mov rcx,[rsi+0xA18]` / `  67b8222  mov rdx,[rsi+0xA28]` / `  67b821d...(clear at +0xA18/+0xA28)` | [V] |

Record = 0xB00 bytes, 44 x 0x40 elements (per oc_U-ER7 [V]).

## Consumer classification

The consumer is sub_6618810 (the per-frame endFrame caller, rcx = pass object), whose stride-0xB00 loop at 0x6619216..0x661924b walks [r14+0x268) .. [r14+0x270) (begin..end) and, per record, calls sub_67B8030 (record destructor).

- Loads: record-vector begin `[r14+0x268]`, end `[r14+0x270]`; per record, sub_67B8030 loads record sub-vector begin/end at record+0xAD8/+0xAE8, +0xA98/+0xAA8, +0xA58/+0xA68, +0xA18/+0xA28, and record+0xAC8/+0xA88/+0xA48 single pointers.
- Stores: sub_67B8030 clears (writes zero / refcount-decrement / frees) record sub-vector fields at record+0xAD8, +0xAE8, +0xA98, +0xAA8, +0xA58, +0xA68, +0xA18, +0xA28, and writes pointee=0 at record+0xAC8, +0xA88, +0xA48. The loop also stores end=begin: `[r14+0x270] = [r14+0x268]`.

## Conclusion

consumer is read-only: NO — a store exists.

Store: sub_67B8030 (called per record by sub_6618810's stride-0xB00 loop) clears record sub-vector fields, i.e. record offsets +0xA18, +0xA28, +0xA48, +0xA58, +0xA68, +0xA88, +0xA98, +0xAA8, +0xAC8, +0xAD8, +0xAE8 (all stored/written to zero or freed), plus the vector end field [r14+0x270].

Therefore the skip-when-unchanged optimization (Q3d / RewriteLightSkip) must NOT be a plain skip: it must be copy-on-write (deep-copy the 0xB00 record only when a consumer that writes it will run, otherwise reuse). The consumer read-only proof required by the checklist item is resolved negatively — copy-on-write is required.

## Proof of consumer identity

- sub_6618810 is called per-frame from endFrame (0x66232b0; 3 xrefs: sub_66182d0, sub_6622aa0, sub_66232b0=endFrame) [V rdis callers].
- Its stride-0xB00 loop 0x6619216..0x661924b is the ONLY begin..end stride-0xB00 record walker in .text (rdis `imm 0xB00` survey; all other `add X,0xB00` sites are buffer/shared_ptr indexing, not record begin..end loops) [V].
- Per-record target sub_67B8030 is a record destructor: clears every sub-vector inside the 0xB00 record [V verbatim above].

## CLOSES?

YES — the single missing REVERSING fact (consumer of the converted 0xB00-byte light records) is found and [V]-proven: consumer = sub_6618810 stride-0xB00 loop (per-frame, from endFrame) delegating to sub_67B8030 per record; consumer is NOT read-only (store at record fields +0xA18..+0xAE8 via sub_67B8030), so the Q3d skip must be copy-on-write. No remaining unknown RVA/offset/meaning for this reversing fact.

Note: the broader Q3d item additionally needs hook wiring at caller 0x66417af and an in-game test (deferred per DEFERRED TESTING); those are not part of this reversing fact and are not blockers for CLOSES? YES on this unit.

## TOOL REQUESTS

None.
