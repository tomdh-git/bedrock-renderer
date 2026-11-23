## NEXT
DONE

UNIT: U-EQ2c — Close checklist item Q2c "Frame::sort (0xc280010/0xc280ca0) replaced by a radix sort on the 64-bit key; order-identical (stable), timed".
Target: Minecraft.Windows.exe 1.26.62.01 (image-base RVAs). Static analysis only: no game launch, no build, no commit.

Nomenclature caveat: the item line says "Frame::sort", but 0xc280010/0xc280ca0 are the dragon frame-graph generator's final-step std sorts, not bgfx::Frame::sort (0xbc61e20, which already radix-sorts per docs/progress/oc_U-A6c.md). xref proves 0xc273420 calls 0xc280010, 0xc280ca0 calls 0xc280010, 0xc2809a0 calls 0xc280ca0 [V: xref.py callers]. Both functions decoded below with verbatim rdis quotes.

(1) What exists on disk now (paths)

Created:
- docs/progress/oc_U-EQ2c.md — this file.
- src/sdk/radix_sort.h — NEW header: stable radix sort on u64 keys (LSD counting sort, 8 passes), order-identical to std::stable_sort on the same key, timed wrapper radixSortTimed, fail-fast preconditions, no null guards/SEH, header-only C++17.
- tools/radix_sort_selftest.cpp — NEW standalone host self-test: compares radix sort output element-wise with std::stable_sort over empty, single, all-equal, sorted, reverse, shuffled and duplicate-heavy inputs, plus a timing run; documents its compile command; not compiled here (no host toolchain in this sandbox).
- docs/functions/c280ca0.md — NEW dossier for the stable_sort driver half of the pair (docs/functions/c280010.md already covers the insertion sort half).

Edited: none.

(2) What is being replaced — decoded from the disassembly

Every instruction quote below is verbatim from rdis on Minecraft.Windows.exe 1.26.62.01 (verify_oc clean). Records are 0x80 bytes; the sort key is the signed u64 at record+0x78.

| offset | size | read/store address | `0xRVA  instr` | meaning | tag |
| 0xc280130 | 8 | sorted-prefix record+0x78 (sort key read) | `0xc280130  cmp rdx,[rdi+0x78]` | 0xc280010 insertion sort: pivot key compared against the prefix record's key at +0x78 | [V] |
| 0xc280855 | 8 | destination record+0x78 (sort key write) | `0xc280855  mov [rdi+0x78],rax` | 0xc280010 insertion sort: pivot key stored back at record+0x78 | [V] |
| 0xc2801c2 | 4 | shared_ptr control block+0x8 (refcount write) | `0xc2801c2  lock dec dword ptr [rbp+8]` | 0xc280010 record shift: releases the moved record's shared_ptr refcount — records are moved, not copied | [V] |
| 0xc280cdd | 5 | - (call) | `0xc280cdd  call 0xC280010` | 0xc280ca0 stable_sort driver: insertion-sorts each 0x20-element chunk (0x1000 bytes: 0xc280cd3 add r15,0x1000) | [V] |
| 0xc28105c | 5 | - (jmp) | `0xc28105c  jmp 0xC280010` | 0xc280ca0 driver: count < 0x21 (0xc280cb6 cmp r8,0x21) sorts the whole range with insertion sort | [V] |
| 0xc280d60 | 8 | buffer run+0x78 (merge key read) | `0xc280d60  mov r14,[r10+0x78]` | 0xc280ca0 stable_sort merge: buffer-run key read at +0x78 | [V] |
| 0xc280d64 | 8 | input run+0x78 (merge key read) | `0xc280d64  cmp r14,[r15+0x78]` | 0xc280ca0 stable_sort merge: keys at +0x78 compared (jge keeps run order on equal keys) | [V] |
| 0xc280d78 | 8 | output record+0x0 (store) | `0xc280d78  mov [rax],r12` | 0xc280ca0 merge: first qword of the relocated record stored | [V] |
| 0xc280d9e | 4 | source record+0x40 (write) | `0xc280d9e  mov qword ptr [r10+0x40],0` | 0xc280ca0 merge: source slot field zeroed after the record move — single shared_ptr owner, refcount untouched | [V] |
| 0xc280df8 | 8 | merged record+0x78 (write) | `0xc280df8  mov [rax+0x78],r14` | 0xc280ca0 merge: relocated record's key stored at +0x78 | [V] |

The driver's merge passes are driven by 0xc281e50 (calls at 0xc281162, 0xc2811a9, 0xc2811c4) with doubling run size (0xc2811ae shl r12,3); the temp buffer is freed by 0xc27ed70 at 0xc2811ed and leftover shared_ptr control blocks are released via lock dec + [0xF99FFA0] at 0xc2811fb / 0xc28120a / 0xc281220 [V]. std::stable_sort is stable by the C++ standard guarantee [I: language guarantee; the merge mechanism is shown above].

(3) The replacement — src/sdk/radix_sort.h

API: radixSortByOffset<0x78>(records, count) sorts the pass records by the key at +0x78; radixSortTimed(records, count, keyOf) returns steady_clock nanoseconds.

Why order-identical: both radixSort (LSD counting sort with stable backwards placement) and std::stable_sort are stable on the same key (the u64 at record+0x78), so equal keys keep input order in both and the full output is identical [I: stability argument; the self-test below proves it empirically once compiled and run].

Why move-safe: records are relocated bitwise with the source slot zeroed after every move, so a shared_ptr-owning record lives in exactly one slot with its refcount untouched — identical end state to the game's own merge, which relocates with movups stores and zeroes source fields (0xc280d72/0xc280d9e/0xc280df8 above) [V for the game's move; [I] for the equivalence claim].

Integration point (not wired): 0xc273420's final step, which currently calls 0xc280010 (xref-verified [V]) through the 0xc280ca0 driver. Replace the std pair with one radixSortByOffset<0x78> call there. CMake is untouched — adding the header to a build target is outside this unit's permissions.

(4) Self-test — tools/radix_sort_selftest.cpp

Standalone host test (no game deps). Compares radixSortByOffset<0x78> output with std::stable_sort element-wise over: empty, single, all-equal keys, sorted keys with reverse seq, reverse keys, all-distinct shuffled, and 60 randomized duplicate-heavy cases (n up to 4096); checks sortedness and seq stability; prints a timing comparison on 2'000'000 records (radix vs std::stable_sort). Exits 0 printing PASS only on full match.

Remaining step: compile (cl /EHsc /O2 /Fe:radix_sort_selftest.exe tools/radix_sort_selftest.cpp from the repo root) and run it; it must print PASS and exit 0. No host compiler exists in this static-analysis sandbox, so the test exists on disk but has not been executed.

(5) Remaining steps after the self-test passes

1. Wire radixSortByOffset<0x78> into 0xc273420's final step in place of the 0xc280010/0xc280ca0 pair, and add the header to the project (CMake change — outside this unit's permissions).
2. Build the game and confirm the exe no longer dispatches pass ordering to 0xc280010/0xc280ca0; compare a captured sorted task list with the old std order (order-identical) and time the sort with radixSortTimed.

CLOSES?: NO — the item wording ("replaced by a radix sort on the 64-bit key; order-identical (stable); timed") is not met by what exists on disk now. Blocking fact: under static-only rules the game cannot be built or launched, so nothing is integrated into the exe — 0xc273420 still calls 0xc280010 and the std pair still lives at 0xc280010/0xc280ca0; the radix sort header and self-test exist on disk but are unwired and unproven in the game.

## TOOL REQUESTS

tools/radix_sort_selftest.cpp | record generator + std::stable_sort comparison + timing | would have been compiled and run to prove order-identical; no host compiler in this sandbox, so it ships as code with a documented compile command instead.

None other.
