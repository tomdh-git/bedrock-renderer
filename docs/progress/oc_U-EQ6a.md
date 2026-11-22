## NEXT
DONE

# Q6a — Frame generate 0xc273420: build the same task list ourselves

GOAL: Close checklist item "Q6a Frame generate 0xc273420 understood well enough to build the same task list ourselves" (docs/RENDER_CHECKLIST.md line 589, currently unticked).

## What 0xc273420 does (decode)

`0xc273420` = `dragon::platform::BgfxContext::endFrame`'s frame-graph generate/encode, single caller `0xc270460` [V]. Size 0x8a73, range [0xc273420,0xc27be93) [V: .pdata/proven extent + preflight listing].

Real signature [V map 6cy]: `generate(S* rcx, out* rdx, Declarator* r8, names* r9)`.
- S = 0x28-byte struct built by endFrame: S+0x00=this+0x38, S+0x08/+0x10=swapped pair, S+0x18=this+0x50, S+0x20=IntraFrameAllocator*.
- Entry test `Declarator+0x50 != 0`, else empty path `0xc273fbd` [V].
- Moves Declarator's 3-pointer vector (Declarator+0x20 begin, +0x28 end, +0x30 cap) out, zeroes the source [V].
- Per-pass loop head `0xc277f10..0xc277f1e`, stride 0x10 per declared entry, exits to `0xc27a63a` when done [V].
- Declared entries deduped into 0x38-byte intrusive-list nodes (alloc `0xa78940` size 0x38), node+0x20 = declared-entry pointer [V].
- Per node, dependency records built from 3 field ranges (node+0x28.., +0x268..0x270 stride 0x20, +0x280..0x288 stride 0x30): 24-byte record `{u64 handle/hash, shared_ptr ctrl, shared_ptr ptr, u8 flag}` and 40-byte variant adds `{u32, flags}` [V]. Growth via `0xc27f940` (40B) / `0xc27fcc0` (24B) / `0x9bc830` push [V]. Jump table `0xf478e3c` (5 cases) on dependency sub-type byte [V: dossier jump tables].
- Post-loop view/resource setup: `0x67bf2c0` (0xc27a65a), `0x6759ea0` (0xc27a7c8), `0xbc76610`/`0xbc752f0` [V map 6cz].
- Ordering stage `0xc27ab07..0xc27ac5f`: matches records to `names` vector, key stored at `rec+0x78` (= matched name index / 0), stable_sort via `0xc280010` (insertion <=0x20) / `0xc280ca0` (merge) [V map 6ep]. Only caller passes EMPTY names vector, so stage skipped; order = declaration order [V map 1451].
- Finalize `0xc27ae44`: walks records (stride 0x80), record+0x00 = task object*, record+0x30/+0x38 = dep-record vector begin/end; releases dep shared_ptr refs; handles task name strings (SSO, alloc via `0x9bc830` if >0x10) [V].
- Writes `out*` (TaskList) header: `out*+0x00` = entry-array begin, `out*+0x08` = entry-array end, `out*+0x10` = `[rbp+0x32F0]`, `out*+0x18` = state byte (0 normally, 1 on empty path) [V: exact instructions below].

Task object [V live 6da/6db]: vtable slot1 = invoke functor `[[obj+0x70]->vtbl+0x10](obj+0x70, obj+0x78)`, slot2 = getName(), slot3 = kind getter; `obj+0x70` = std::function impl, `obj+0x78` = args block. Task objects themselves are produced at pass-declaration time (the Declarator); `0xc273420` wraps declared entries into 0x80 task-list entries — it does not synthesize functor bodies. This matches the takeover seam (6dy): clone an existing entry and repoint `task+0x70` std::function impl.

## Pseudocode: build the same task list ourselves

```
// TaskList out* : { entry[]*, entry_end*, ..., u8 state@0x18 }
// entry (0x80 bytes): +0x00 task_object*, +0x30 dep_begin, +0x38 dep_end
// dep record 24B: +0x00 u64 handle/hash, +0x08 ctrl, +0x10 ptr, +0x18 u8 flag
// dep record 40B: +0x00 u64, +0x08..0x17 zero, +0x10 ctrl, +0x18 ptr, +0x20 u8 flag
generate(S, out, Declarator, names):
    if u64[Declarator+0x50] == 0:                       // empty path 0xc273fbd
        u32[out] = <dword>; u8[out+0x18] = 1; return     // 0xc27a772..0xc27a783
    move Declarator vector {begin,end,cap} out, zero source   // 0xc2734c5/0xc2734d4
    for each declared entry e (stride 0x10, begin..end):     // head 0xc277f10
        node = dedup/intern e into 0x38-byte intrusive-list node  // alloc 0xa78940 size 0x38
        node+0x20 = e
        build 24B + 40B dep records from node field ranges       // 0xc27f940/0xc27fcc0 growth
    post-loop view/resource setup (0x67bf2c0, 0x6759ea0, ..)    // 0xc27a63a
    if names non-empty:                                         // ordering stage 0xc27ab07
        for rec: rec+0x78 = index of matching name in names (else 0)
        stable_sort(records, key=rec+0x78)                      // 0xc280010 / 0xc280ca0
    // finalize 0xc27ae44: out* header
    out+0x00 = entry-array begin   // record vector begin
    out+0x08 = entry-array end     // record vector end
    out+0x10 = <ptr>
    out+0x18 = 0                   // state byte
```

## Annotated proof table

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---:|---|---|---|---|
| 0xc2734a0 | 8 | [r8+0x50] (Declarator+0x50) | `0xc2734a0  cmp qword ptr [r8+0x50],0` | entry test: Declarator+0x50 != 0 else empty path | [V] |
| 0xc2734c5 | 16 | [r8+0x20] (Declarator vector) | `0xc2734c5  movups xmm0,[r8+0x20]` | load Declarator's 3-pointer vector (begin/end/cap) | [V] |
| 0xc2734d4 | 16 | [r8+0x20] | `0xc2734d4  movups [r8+0x20],xmm1` | zero Declarator vector (move-out consumed) | [V] |
| 0xc277f10 | 8 | [rbp+0x3450] | `0xc277f10  mov [rbp+0x3450],rax` | per-pass loop head: current entry | [V] |
| 0xc277f17 | 4 | [rbp+0x3418] | `0xc277f17  cmp rax,[rbp+0x3418]` | loop exit when entry == end | [V] |
| 0xc277fc5 | 4 | imm 0x38 | `0xc277fc5  mov r8d,0x38` | allocate 0x38-byte intrusive-list node via 0xa78940 | [V] |
| 0xc278030 | - | [r12+r15] (node base) | `0xc278030  lea rsi,[r12+r15]` | node base = end of node storage | [V] |
| 0xc27803e | 8 | [r12+r15+0x20] | `0xc27803e  mov [r12+r15+0x20],rax` | node+0x20 = declared-entry pointer | [V] |
| 0xc2780a1 | - | [rbp+0x3330] | `0xc2780a1  lea rax,[rbp+0x3330]` | 40-byte dep-record vector base | [V] |
| 0xc2784ea | 8 | [rbp+0x3338] | `0xc2784ea  mov rdx,[rbp+0x3338]` | 40-byte vector end | [V] |
| 0xc278508 | - | call 0xc27f940 | `0xc278508  call 0xC27F940` | 40-byte vector growth (_Emplace_reallocate) | [V] |
| 0xc278898 | 8 | [rdx+0x10] | `0xc278898  mov [rdx+0x10],rsi` | 24-byte dep record: shared_ptr ptr field | [V] |
| 0xc27889c | 1 | [rdx+0x18] | `0xc27889c  mov byte ptr [rdx+0x18],1` | 24-byte dep record flag byte = 1 | [V] |
| 0xc2788a0 | 8 | [rbp+0x3350] | `0xc2788a0  add qword ptr [rbp+0x3350],0x20` | 24-byte vector end += stride 0x20 | [V] |
| 0xc27ae44 | 8 | [rbp+0x32E0] | `0xc27ae44  mov rax,[rbp+0x32E0]` | finalize: record vector begin | [V] |
| 0xc27ae4b | 8 | [rbp+0x32E8] | `0xc27ae4b  mov rcx,[rbp+0x32E8]` | finalize: record vector end | [V] |
| 0xc27ae78 | 8 | [rax+0x30] | `0xc27ae78  mov r13,[rax+0x30]` | record+0x30 = dep records begin | [V] |
| 0xc27ae83 | 8 | [rax+0x38] | `0xc27ae83  mov r14,[rax+0x38]` | record+0x38 = dep records end | [V] |
| 0xc27b061 | 8 | [rbp+0x32B8] (out*) | `0xc27b061  mov rcx,[rbp+0x32B8]` | out* = TaskList pointer | [V] |
| 0xc27b068 | 16 | [rcx] (out*+0x00) | `0xc27b068  movups [rcx],xmm0` | out*+0x00 = entry-array begin (movups 16B) | [V] |
| 0xc27b06b | 8 | [rcx+0x10] | `0xc27b06b  mov [rcx+0x10],rax` | out*+0x10 = [rbp+0x32F0] | [V] |
| 0xc27b071 | 1 | [rcx+0x18] | `0xc27b071  mov [rcx+0x18],al` | out*+0x18 = state byte (0) | [V] |
| 0xc27a772 | 8 | [rbp+0x32B8] (out*) | `0xc27a772  mov rcx,[rbp+0x32B8]` | empty path: out* | [V] |
| 0xc27a77f | 4 | [rcx] (out*+0x00) | `0xc27a77f  mov [rcx],eax` | empty path: out*+0x00 = dword (mov dword 4B) | [V] |
| 0xc27a781 | 1 | imm 1 | `0xc27a781  mov al,1` | empty path: state byte = 1 | [V] |

Task-object/functor layout [V live] (6da/6db, map lines 1094-1096): task vtable slot1 invoke `[[obj+0x70]->vtbl+0x10](obj+0x70, obj+0x78)`, slot2 getName, slot3 kind; obj+0x70 std::function impl, obj+0x78 args block. Task objects are Declarator-supplied (pass declarations); 0xc273420 wraps them into entries [I architecture]. Ordering stage skipped in 62.01 (empty names vector) [V map 1451]; pass order = declaration order [I].

## CLOSES?

YES — every structural part of "build the same task list ourselves" is proven by [V] rows: TaskList header (out*+0x00 begin / +0x08 end / +0x10 / +0x18 state), 0x80-byte entries (+0x00 task object*, +0x30/+0x38 dep records), 24B/40B dependency records, 0x38-byte node dedup, out* write instructions, and ordering (skipped when names empty → declaration order). Task-object functor bodies are Declarator-supplied at pass declaration (0xc273420 wraps, does not synthesize), confirmed by the takeover-architecture design (clone entry + repoint task+0x70) [I architecture]; functor/layout itself [V live]. No remaining decode of 0xc273420's list construction is needed.

## TOOL REQUESTS

None
