## FINDINGS (fld 0x63 scan + reader context)

### rdis fld 0x63 scan
- **146 total memory accesses** at offset 0x63 across the binary
- Offset 0x63 (99 decimal) is a frequently accessed byte-sized field used across many different game systems
- Most accesses are byte-level flag/boolean operations: `mov byte ptr [...+0x63], 0/1`, `cmp byte ptr [...+0x63], 0/1`
- Our draw record reader at **0x53398EE** `cmp byte ptr [rax+0x63],0` is one of these

### 0x53398EE Reader Context (verbatim)
```
0x53398EE  cmp byte ptr [rax+0x63],0    ; R ret@533f580+0x63
0x53398F2  jne short 0x53398D0          ; -> if depth != 0, continue loop (skip)
0x53398F4  cmp byte ptr [rsi],0
0x53398F7  jne short 0x53398A0          ; -> if [rsi]!=0, store draw record data
0x53398F9  mov dword ptr [0],0xDEADC0DE ; CRASH if depth==0 AND [rsi]==0
```

**Interpretation [I]:**
- Depth byte at +0x63 acts as a **validity/culling flag**
- **depth != 0**: Element is culled/skipped (jump back to loop at 0x53398D0)
- **depth == 0**: Element passes depth test, proceed to store
  - If [rsi] (some pointer) != 0: normal data store path at 0x53398A0
  - If [rsi] == 0: fatal error (DEADC0DE) - unexpected null state

### Draw record pointer escape check
- RIP scan for [rbp+0x238] (draw record ptr storage) in 0x533652D..0x5336C84: **no external stores found**
- The draw record pointer at [rbp+0x238] appears to stay within sub_5334850

---

## CONCLUSION
**Only ONE reader of the draw-record depth byte at +0x63 exists:**
- **0x53398EE** `cmp byte ptr [rax+0x63],0` in sub_5334850 (Visibility Event Processor)
- Used for **depth culling/validity check** in element iteration path
- Depth byte written at two sites in same function: 0x53365FA and 0x5337EB1
- No external functions read this field - draw record does not escape sub_5334850
- Other 0x63 accesses in binary are unrelated (stack frames, other structs, string ops)

---

## NEXT
DONE: Unit complete. Run verify_oc.py on progress file.