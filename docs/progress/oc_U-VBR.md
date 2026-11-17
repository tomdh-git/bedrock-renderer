## NEXT: Find Encoder vtable in .rdata near RTTI structures at 0x12804480, 0x12861AC0, 0x12861F04 — the setter (bgfx::Encoder::setVertexBuffer) is likely a virtual function accessed via vtable

# UNIT U-VBR: Find WRITER of bgfx Encoder vertex-buffer range table pointer at Encoder+0x680

## Background from oc_U-A12b.md (checklist A12b):
- Four submit variants identified: 0xBC60740, 0xBC61140, 0xBC61560, 0xBC618E0
- All four ONLY READ [rsi+0x680] (e.g., 0xbc60b4f mov r8,[rsi+0x680]) and clear dirty flag +0x688 (0xbc60aab)
- NONE of them WRITE to Encoder+0x680
- The actual setter (bgfx::Encoder::setVertexBuffer) that fills Encoder+0x680 is NOT among these four callers
- 0xBC60F10 is the CONSUMER that reads Encoder+0x680 and writes Frame+0x8B4778 (SideTable: 0x41 entries of {Binding*, count})

## Method per brief:
1. Use `rdis fld 0x680` and `rdis fld 0x688` (filter by functions inside RVA 0xBB0000..0xBD0000 and 0xE80000..0xE90000, and by presence of store `mov [reg+0x680],` or `mov byte ptr [reg+0x688],1`)
2. Use `python tools/sigs/descscan2.py <fn rva>` on candidates
3. Candidate functions: callers of the four submit variants and bgfx Encoder::setVertexBuffer / setIndexBuffer / setInstanceDataBuffer API wrappers near them

## Progress so far:
- Found callers of the four submit variants using rdis callers:
  - 0xBC60740: 11 callers (sub_569a3a0, sub_56ad350, sub_56ad810, sub_bcc39b0, sub_bcc3b90, sub_bcc3e50, sub_bcc3fa0, sub_bcc4150, sub_bcc4b90, sub_c270330, sub_c295d50)
  - 0xBC61140: 12 callers (sub_56d3170, sub_56d5ed0, sub_bc0b240, sub_bc5bad0, sub_bc96950, sub_bc973e0, sub_bc97bc0, sub_bca85e0, sub_bca9770, sub_bcaaac0, sub_bcb7590, sub_bcc4990)
  - 0xBC61560: 6 callers (sub_568b9e0, sub_5699be0, sub_56c85c0, sub_56ca260, sub_56d0cd0, sub_bc04270)
  - 0xBC618E0: 1 caller (sub_bcc4b90)
- sub_bcc4b90 appears as caller for both 0xBC60740 and 0xBC618E0 (possible dispatcher)
- Disassembled 0xBC60740 - it's a resource allocation/submission function with spinlock, type dispatch, bit packing, hash, vector copy
- 0xBC60740 READS [rsi+0x680] and [rsi+0x688] but does NOT write them
- 0xBC60D10 (Encoder::reset/discard) clears encoder state, sets dirty flag +0x688=1, reads Encoder+0x680 but does NOT write it
- Encoder+0x680 read in reset at 0xbc60e65: `mov rdi,[rsi+0x680]` then processed in loop

## Key findings from subagents:

### fld 0x680 (first 200 of 4073 total, 1618 writes):
- Total accesses: 4,073 (1,618 writes)
- Most common: stack-relative `rbp+0x680` (local variables)
- Also register-relative: `rsi+0x680`, `rdi+0x680`, `rbx+0x680` (class/struct fields via this pointer)
- Access types: vector (movaps/movups), qword, dword, word, byte, lea
- Constants written: 0x11, 0xF, 0x13, 0x15, 0, 1, 0xFFFC
- [UNVERIFIED: Need to filter for functions in 0xBB0000..0xBD0000 and 0xE80000..0xE90000 with STORES to [reg+0x680]]

### fld 0x688 (first 200 of 2620 total, 1178 writes):
- Total accesses: 2,620 (1,178 writes)
- Strong byte-level boolean pattern: `cmp byte ptr [...] 1` and `mov byte ptr [...] 0/1` — strongly suggests a **boolean dirty flag**
- Qword writes with constants: 0x1F, 0xF, 0xFFFFFFFFFFFFFFFF, 0x14 — likely state flags/bitmasks
- Register moves: frequent `mov rax, [rbp+0x688]` and `mov [rbp+0x688], rax`
- SSE operations: `movups [rbp+0x688], xmm0/6`
- [UNVERIFIED: Need to filter for functions in 0xBB0000..0xBD0000 and 0xE80000..0xE90000 with STORES byte ptr [reg+0x688], 1]

### str "Encoder":
- "maxEncoders" at sub_660ecd0+0xe07
- "powerEfficientEncoder" at sub_e9c4030+0x523
- bgfx::Encoder mangled names at 0x12804480, 0x12861ac0, 0x12861f04 (no code refs, likely RTTI in .rdata)

### str "vertex":
- Shader paths: entity.vertex, uv_selection_overlay.vertex, selection_box.vertex, banner.vertex, renderchunk.vertex
- "Gameface vertex buffer" at sub_1f3ee50+0x22d, sub_1f3ee50+0x377
- "Full screen quad vertex buffer" at sub_c270ea0+0x6d, sub_c271150+0x60
- "Our skinning vertex buffer is asking for a range that will e..." at sub_e83f1d0+0x9e0
- "vertexShader" at multiple locations
- "mc-vertex-stream-packing" at sub_26473a0+0x385c

### str "setVertexBuffer", "setIndexBuffer", "setInstanceDataBuffer", "bindVertexBuffer":
- NOT FOUND

## Latest Findings (2026-11-16):

### 1. Analyzed sub_bc5fce0 (0xBC5FCE0) - Vertex/Index Buffer Processing
- Processes vertex/index buffers, calls allocator and sub_ebce390
- **NO writes to Encoder+0x680 or Encoder+0x688**
- This is a buffer setup/validation function, not the setter

### 2. Analyzed Consumer 0xBC60F10 in Detail
- Allocates 0x418-byte SideTable (0x41 entries of {Binding*, count}) at Frame+0x8B4778
- Checks Encoder+0x410 (some state field)
- **Does NOT read Encoder+0x680** — it builds its own table from encoder state
- This is the downstream consumer that packs vertex buffer bindings for GPU submission

### 3. sub_ebce390 - Core Consumer Utility
- **169 callers** found, many in target RVA ranges (0xBB0000..0xBD0000 and 0xE80000..0xE90000)
- This is a widely-used utility for processing vertex buffer ranges

### 4. bgfx::Encoder Mangled Names (RTTI in .rdata)
- Found at: 0x12804480, 0x12861AC0, 0x12861F04
- No code references — these are RTTI structures in data section
- **Vtable likely nearby in .rdata section**

### 5. Vtable Search
- **No vtable found** at 0xBC60000 or 0xE80000 (code sections)
- Vtable for Encoder must be in .rdata near the RTTI structures

### 6. String Searches
- "setVertexBuffer" — NOT FOUND
- "setIndexBuffer" — NOT FOUND
- "setInstanceDataBuffer" — NOT FOUND
- "bindVertexBuffer" — NOT FOUND
- The setter is almost certainly a **virtual function** accessed via vtable

### 7. Critical Gap
- **Still NO function found that WRITES to Encoder+0x680**
- All analyzed functions (submit variants, reset, consumer, buffer processing) only READ +0x680
- The setter (bgfx::Encoder::setVertexBuffer) is the missing writer

## STATUS UPDATE (2026-11-16 16:05):
- **Progress file last updated:** 2026-11-16 (with Latest Findings section)
- **RVA filtering NOT YET DONE:** The `rdis fld 0x680 --w` and `rdis fld 0x688 --w` outputs need to be filtered by function RVA ranges (0xBB0000..0xBD0000 and 0xE80000..0xE90000). This requires the game executable to run `rdis` against. The game executable is not in this repository (only build tools like `bs2pack.exe` are present).
- **Facts DB available:** `tools/rdis/names/Debug.facts.jsonl` (updated 12:00 PM), `ninja-Release.facts.jsonl` (12:06 PM), `release.facts.jsonl`, `1.26.62.01.facts.jsonl`
- **rdis binary built:** `tools/rdis/target/release/rdis.exe` (built 4:00 PM)
- **Key blocker:** Still NO writer to Encoder+0x680 found. The setter is likely a virtual function accessed via vtable in .rdata.

## Next Steps:
1. **BLOCKER:** Obtain the game executable (likely named `Debug.exe`, `release.exe`, or versioned like `1.26.62.01.exe`) to run `rdis fld 0x680 --w --max 5000` and `rdis fld 0x688 --w --max 5000`, then filter results for functions in target RVA ranges
2. **HIGH PRIORITY:** Search .rdata section near 0x12804480, 0x12861AC0, 0x12861F04 for Encoder vtable — this is the most promising path to find the virtual `setVertexBuffer` setter
3. Once vtable found, locate `setVertexBuffer` virtual function slot and trace its implementation
4. Examine the 169 callers of sub_ebce390 in target ranges for potential setters
5. Disassemble 0xBC60D10 (reset/discard) to understand full encoder state management

## TOOL REQUESTS:
- Need a way to filter fld output by function RVA range (current fld output is unfiltered, 4000+ lines)
- Need fld --w output filtered by RVA range
- Need ability to search/dump .rdata section for vtable structures near known RTTI addresses
- rdis fld command needs `--fn-range START END` filter option (not yet implemented)