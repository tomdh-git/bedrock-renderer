## NEXT
Step 1 complete: ripscan on 0xF2BE100..0xF2BE200 and insert-task slot addresses. Found 3 ripscan hits, all false positives (mid-instruction). No actual `lea reg,[0xF2BE...]` instructions found. Two candidate functions analyzed (0xDA35990, 0xACD5B30) - neither is the FrameBuilder vtable constructor. Vtable at 0xF2BE1F8 is a sub-vtable of 0xF2BE1C0 (offset 0x38 = slot 7). Need to find the true constructor that installs 0xF2BE1F8 via `lea rax,[vtable]` + `mov [rcx],rax`. Continue with broader search for vtable installation patterns.

## Step 1: ripscan Results (0xF2BE100..0xF2BE200 + insert-task slots)

### Addresses Scanned
8-byte aligned: 0xF2BE100, 0xF2BE108, 0xF2BE110, 0xF2BE118, 0xF2BE120, 0xF2BE128, 0xF2BE130, 0xF2BE138, 0xF2BE140, 0xF2BE148, 0xF2BE150, 0xF2BE158, 0xF2BE160, 0xF2BE168, 0xF2BE170, 0xF2BE178, 0xF2BE180, 0xF2BE188, 0xF2BE190, 0xF2BE198, 0xF2BE1A0, 0xF2BE1A8, 0xF2BE1B0, 0xF2BE1B8, 0xF2BE1C0, 0xF2BE1C8, 0xF2BE1D0, 0xF2BE1D8, 0xF2BE1E0, 0xF2BE1E8, 0xF2BE1F0, 0xF2BE1F8, 0xF2BE200
Insert-task slots: 0xF2BE1F8, 0xF2BE200, 0xF2BE208, 0xF2BE210, 0xF2BE218, 0xF2BE220, 0xF2BE228, 0xF2BE230, 0xF2BE238

### ripscan Hits (3 total)

| Target Address | Hit Location | Containing Function | Actual Instruction at Hit |
|----------------|--------------|---------------------|---------------------------|
| 0xF2BE108 | 0x5E3DF24 | sub_5E3DD30 | `loopne 0x5E3DF27` (1-byte relative jump, mid-instruction) |
| 0xF2BE1C0 | 0xDA35BF5 | sub_DA35990 | `mov dword ptr [rbp+0x188], 0` (RBP-relative store) |
| 0xF2BE200 | 0xACD5B74 | sub_ACD5B30 | `mov [rsi+0x45E], al` (RSI-relative store) |

**All other addresses: no hits.**

### Critical Finding
**No actual `lea reg,[0xF2BE...]` instructions found.** The three ripscan hits are false positives from the scanner's brute-force disp32 matching against instruction bytes that happen to contain the target address as immediate data, not as RIP-relative LEA targets.

Comprehensive scan of entire `.text` section for `lea reg,[rip+disp32]` targeting F2BE range (0xF2BE100–0xF2BE238): **Zero matches.**

The F2BE range resides in `.rdata` and contains a linked list of runtime heap pointers. Code accesses this through register-indirect addressing (base pointer loaded once, then traversed), not direct RIP-relative references.

## Step 2: Vtable Structure (from rdis vt)

### Vtable at 0xF2BE100 (Primary/Base)
32+ slots starting at 0xF2BE100. Key slots:
- 0xF2BE1C0 (slot 24): sub_6639A80 - matches 0xF2BE1C0 slot 0
- 0xF2BE1F8 (slot 31): sub_668ACC0 - matches 0xF2BE1C0 slot 7

### Vtable at 0xF2BE1C0 (FrameBuilder Insert-Task Vtable)
16 function slots + non-code data:
| Slot | Offset | Function | Description |
|------|--------|----------|-------------|
| 0 | +0x00 | sub_6639A80 | Base vfunc |
| 1 | +0x08 | sub_6639A90 | Base vfunc |
| 2 | +0x10 | sub_661EDC0 | Base vfunc |
| 3 | +0x18 | sub_660EBE0 | Base vfunc |
| 4 | +0x20 | sub_660ECB0 | Base vfunc |
| 5 | +0x28 | sub_660ECC0 | Base vfunc |
| 6 | +0x30 | sub_6610A60 | Base vfunc |
| 7 | +0x38 | sub_668ACC0 | Insert-task base |
| 8 | +0x40 | sub_6685F30 | Insert-task offset calc |
| 9 | +0x48 | sub_6674050 | **Insert Editor** |
| 10 | +0x50 | sub_666AA00 | **Insert Effect** |
| 11 | +0x58 | sub_6664760 | **Insert UI** |
| 12 | +0x60 | sub_6655DE0 | **Insert Sky** |
| 13 | +0x68 | sub_66466E0 | **Insert Item** |
| 14 | +0x70 | sub_6640AE0 | **Insert Light** |
| 15 | +0x78 | sub_768F0 | ret |

### Vtable at 0xF2BE1F8 (Sub-vtable, starts at slot 7 of 0xF2BE1C0)
| Slot | Offset | Function | Description |
|------|--------|----------|-------------|
| 0 | +0x00 | sub_668ACC0 | (was 0xF2BE1C0 slot 7) |
| 1 | +0x08 | sub_6685F30 | (was slot 8) |
| 2 | +0x10 | sub_6674050 | **Insert Editor** (was slot 9) |
| 3 | +0x18 | sub_666AA00 | **Insert Effect** (was slot 10) |
| 4 | +0x20 | sub_6664760 | **Insert UI** (was slot 11) |
| 5 | +0x28 | sub_6655DE0 | **Insert Sky** (was slot 12) |
| 6 | +0x30 | sub_66466E0 | **Insert Item** (was slot 13) |
| 7 | +0x38 | sub_6640AE0 | **Insert Light** (was slot 14) |
| 8 | +0x40 | sub_768F0 | ret (was slot 15) |

**Conclusion**: The "insert-task vtable" documented at 0xF2BE1F8 is a sub-vtable starting at offset 0x38 (slot 7) of the larger FrameBuilder vtable at 0xF2BE1C0. The constructor we seek installs either 0xF2BE1C0 (primary) or 0xF2BE1F8 (sub-vtable) into the object's vptr.

## Step 3: Analysis of ripscan Hit Functions

### Function 0xDA35990 (contains hit at 0xDA35BF5 for 0xF2BE1C0)
```
sub_DA35990 [0xDA35990..0xDA364EB) size 0xB5B
Arguments: RCX=object, RDX=param
Returns: RAX=object pointer
```

**Key characteristics:**
- Allocates memory via `sub_EEA6040` (allocator at [0xF99FFA0]) - two allocations: 0x30 bytes and 0xD8 bytes
- Stores vtable pointers at `[rbp+0x10]` = 0x11D3D80, `[rbp+0x18]` = 0x11D3EF0, `[rbp+0x38]` = 0x11D3D60
- Magic cookie 0x6C5D863C at `[rbp+0x20]`
- Complex initialization with multiple xmm register stores
- **No reference to 0xF2BE1C0 or 0xF2BE1F8 in any store**
- **0 callers** (rdis xr returns none)

**Verdict**: NOT the FrameBuilder constructor. Appears to be a different class constructor (possibly network/message related given string "-invalid-request", "Error", "interactive-tool-*").

### Function 0xACD5B30 (contains hit at 0xACD5B74 for 0xF2BE200)
```
sub_ACD5B30 [0xACD5B30..0xACD5C63) size 0x133
Arguments: RCX=entity?, RDX=param
Returns: AL=boolean
```

**Key characteristics:**
- Calls sub_2C2BC60, sub_2965A50, sub_2965950, sub_3D56A10, sub_C2FAB0, sub_2FA310
- String references: "SpawnedByNight", "Elder"
- Stores result at `[rsi+0x45E]` (single byte)
- **No allocation, no vtable stores**
- **0 callers**

**Verdict**: NOT a constructor. Entity/spawn logic function.

## Step 4: Cross-Reference Analysis

### Vtable and Function Xrefs (rdis xr)
All return **0 xrefs**:
- 0xF2BE1F8 (vtable) - 0 xrefs
- 0x668ACC0, 0x6685F30, 0x6674050, 0x666AA00, 0x6664760, 0x6655DE0, 0x66466E0, 0x6640AE0 (all insert-task functions) - 0 xrefs each

**Interpretation**: All invoked indirectly through vtable dispatch. No direct calls, no address-taken references in code.

## [UNVERIFIED: 0xF2BE1C0 question]
The vtable at 0xF2BE1C0 (primary FrameBuilder vtable) has no code references either. How is it installed? The constructor must exist but uses a pattern not caught by ripscan (e.g., loads vtable address from a global pointer, or computes it via arithmetic, or the vtable pointer is passed as argument).

## [UNVERIFIED: 0xF2BE1F8 question]  
The sub-vtable at 0xF2BE1F8 is at offset 0x38 within 0xF2BE1C0. A derived class constructor might install 0xF2BE1F8 specifically (for a subobject), or the primary constructor installs 0xF2BE1C0 and the sub-vtable is used via offset. Need to find which.

## NEXT STEPS
1. Search for `mov [reg], rax` preceded by `lea rax, [rip+disp32]` where disp32 resolves to 0xF2BE1C0 or 0xF2BE1F8 - the classic vtable install pattern
2. Scan for functions that call the allocator (sub_EEA6040) AND store a vtable pointer at offset 0
3. Check if vtable address is loaded from a global variable (e.g., `mov rax, [0xXXXXXX]` where the global contains 0xF2BE1C0)
4. Look at FrameBuilder-related strings to find owning class: "FrameBuilder - Insert editor" (0xF55F87E), "FrameBuilder - Insert effect" (0xF540E58), "FrameBuilder - Insert UI" (0xF7CB7C5), "FrameBuilder - Insert sky" (0xF51B8A2), "FrameBuilder - Insert item" (0xF59F12F), "FrameBuilder - Insert light" (0xF53AEA6)

## TOOL REQUESTS
- Search for vtable install pattern: `lea rax, [rip+...]` followed by `mov [rcx], rax` or `mov [rdi], rax` etc.
- Find all callers of allocator sub_EEA6040 ([0xF99FFA0])
- Search for global pointers to 0xF2BE1C0 / 0xF2BE1F8 in .data/.rdata
- Find functions referencing FrameBuilder strings

## Step 5: Global Vtable Pointer Search (rdis str)

**Result**: No references found to 0xF2BE1C0 or 0xF2BE1F8 in .data/.rdata sections.
- rdis str 0xF2BE1C0: No output (treats as function, shows garbage)
- rdis str 0xF2BE1F8: No output (treats as function, shows garbage)

**Critical Note**: The rdis vt/str commands appear to be treating the vtable addresses as function entry points rather than data structures. The output shows garbage instructions (sbb, add [rax+...], in eax,dx, (bad)), suggesting these are NOT valid code entry points. This may indicate:
1. The vtable addresses are in .rdata (data section) not .text (code section)
2. rdis vt/str is not the correct tool for vtable analysis
3. The earlier vtable analysis in this document (Step 2) may have come from a different tool/run

## Step 6: FrameBuilder String References

From earlier analysis (confirmed):
- 6 individual insert functions (slots 7-14): sub_6674050, sub_666AA00, sub_6664760, sub_6655DE0, sub_66466E0, sub_6640AE0 - all have 0 callers (vtable dispatch)
- 7 dispatcher functions using "FrameBuilder - Insert" string: sub_E71330, sub_E9AED0, sub_1127330, sub_15A6880, sub_1F44D80, sub_4C85D70, sub_4C85F30
- Frame end function: sub_66232B0 (0 callers, likely thread entry)

## Step 7: Allocator Analysis

- sub_EEA6040 at [0xF99FFA0] is a 5-byte trampoline: jmp rax + int3
- Actual allocator code at 0xEEA6070 has 5 callers:
  1. sub_7F050 (1 call site)
  2. sub_A7820 (1 call site)
  3. sub_A95D0 (1 call site)
  4. sub_B9350 (1 call site)
  5. sub_BA1F0 (1 call site)

**Next**: Analyze these 5 callers for vtable installation patterns (mov [rcx], rax with 0xF2BE1C0/0xF2BE1F8)

## [UNVERIFIED: rdis vt discrepancy]
The vtable structure in Step 2 shows valid function pointers, but direct rdis vt/str on 0xF2BE1C0/0xF2BE1F8 shows garbage. This suggests the vtable analysis may have used a different method or the addresses are data-only (in .rdata) not code.

## NEXT STEPS
1. Complete analysis of 5 allocator callers for vtable install pattern
2. If no constructor found there, trace dispatcher call chains (sub_E6FD30, sub_4C988F0, etc.)
3. Examine sub_66232B0 (Frame end function) as potential object creator
4. Consider searching for vtables via RTTI or type_info structures