# U-D8b: UI ImGui description (tag 4) fields + Gameface flag byte semantics

Started: 2026-11-15. Exe: 1.26.62.01 (image-relative RVAs). Static analysis only.

## NEXT
Resume at: Task A step 1 — disassemble UI visitor head 0x6664a00 (rdis) to find the tag-4 case via jump table 0xF2BF468, then run casewalk.py from the case head with the description register.

---

## Task A: UI ImGui (tag 4) case walk

### A.1 Jump table / dispatch
[V] `0x6664a44 movzx eax,byte ptr [r8+8]` — tag byte read from description+8.
[V] `0x6664a47 cmp rax,4` — max tag = 4 (5 cases: 0..4).
[V] table 0xF2BF468 — 5 entries (0x6664a6c 0x6664d51 0x6664bd6 0x6664c83 0x6664aab per ui_editor_descriptions.md).
[V] case 4 head = 0x6664aab (UI ImGui).

### A.2 Producer / stores
[?]

### A.3 Every read of the description in the tag-4 case
[?]

## Task B: Gameface flag bytes (0x66ade80)

### B.1 Flag byte -> branch
[?]

## TOOL REQUESTS
[?]