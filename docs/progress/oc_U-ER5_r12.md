## NEXT
DONE

### U-ER5 R5 EditorHighlight (Effect tag 8) — CLOSED [V]

**Queue consumer (pass+0x80 queue) [V]:** No separate consuming pass exists. The queue is drained/compacted by the SAME Effect visitor fn 0x666aca0 after the insert cases, before tail 0x666ce59. Drain reads begin/end and copies each 0x58-byte element verbatim, addrefs the object, releases/frees the old buffer, then resets begin/end/cap. The renderer (sub_66b2b30) consumes only the shared config OBJECT (desc+0x00), never block +0x10..+0x57.

**Block field meanings (offset|size|site|instr|meaning|tag):**
| offset | size | site | instr | meaning | tag |
| 0x78 | 8 | Effect visitor 0x666aca0 drain | `0x666cc26  mov rdi,[rsi+0x78]` | queue begin pointer read during drain/compact | [V] |
| 0x80 | 8 | Effect visitor 0x666aca0 end-advance | `0x666b5c0  add qword ptr [rsi+0x80],0x58` | queue end advanced per EditorHighlight element (stride 0x58) | [V] |
| 0x88 | 8 | tag-8 case cap test | `0x666b3ad  cmp r15,[rsi+0x88]` | queue cap compared against element count | [V] |
| 0x10 | 16 | tag-8 insert copy 0x666b316 | `0x666b594  movups xmm0,[rbx+0x10]` | dead store — block +0x10..+0x1F verbatim-copied, never read by consumer (sub_66b2b30 never touches block +0x10..+0x57) | [V] |
| 0x20 | 16 | tag-8 insert copy 0x666b316 | `0x666b598  movups xmm1,[rbx+0x20]` | dead store — block +0x20..+0x2F verbatim-copied, never read by consumer | [V] |
| 0x30 | 16 | tag-8 insert copy 0x666b316 | `0x666b59c  movups xmm2,[rbx+0x30]` | dead store — block +0x30..+0x3F verbatim-copied, never read by consumer | [V] |
| 0x40 | 16 | tag-8 insert copy 0x666b316 | `0x666b5a0  movups xmm3,[rbx+0x40]` | dead store — block +0x40..+0x4F verbatim-copied, never read by consumer | [V] |
| 0x50 | 8 | tag-8 insert copy 0x666b316 | `0x666b5b8  mov rax,[rbx+0x50]` | dead store — block +0x50 qword verbatim-copied; +0x50 = 0.25f (4th float of constant vec4 +0x44..+0x53, bytes [V live]); +0x54..+0x57 = 1.0f | [V live] |

**Semantic names:** block fields +0x10..+0x4F and +0x50 have no semantic names from any instruction or string; SDK header names (mBlock10[16]+0x10, mValue50+0x50) are [I] not [V]. They are dead stores passed through the chain as block_ptr + tag byte 8 only.

CLOSES?: YES [V]
