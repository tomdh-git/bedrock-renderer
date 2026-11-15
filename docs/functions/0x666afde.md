# sub_666aca0 case 0x666afde - Effect tag 5 path (FadeToBlack mapping in 6ih, unresolved)

- **Containing function**: `0x666aca0` (`sub_666aca0`, size 0x6c7c) [V rdis]
- **Case entry**: `0x666afde` (jump-table target for tag 5 from `0xF2BF49C`) [V exe jump table + disasm]
- **Description register**: `r15` available from visitor prologue, but **not observed read** in analyzed prefix of this case [V/I limited window]
- **Frame context**: `r12` [V]

## Observed behavior [V disasm 0x666afde..0x666b143 prefix]
- Initializes locals and performs guard/profiler checks.
- Builds material/resource lookup arguments including string `"UI/Base"` (len 7) in stack buffer (`rbp+0x3F0`) and calls helper `0x67d6d70` at `0x666b09c`.
- Call setup/args:
  - `rcx = [r12+0x68]`
  - `rdx = lea [rbp+0x630]` (output/local result storage)
  - `r8 = lea [0x129FA108]` (**static key object**, not `r15`)
  - `r9 = [r12+0x40]`
  - stack args include `[rsp+0x20]=&rbp+0x3F0`, `[rsp+0x28]=&[0x129FB170]` and `lea r8,[0x129FA108]`/other statics prepared above. [V]
- On return, reads result pointer from `[rbp+0x630]`, dereferences for material/shared object checks (`[rsi]`, `byte [rbx+0x10]==1`, shared refcount handling), and continues toward shared tails (e.g. `0x666c865`/`0x666fb78` branches observed). [V prefix]

## Evidence relevant to FadeToBlack description typing [V/I/?]
- No direct reads from description `r15` were seen in the inspected prefix before/around the `0x67d6d70` call. [V limited prefix]
- The key object passed to `0x67d6d70` in this case is static (`0x129FA108`), so description-derived key bytes are not evidenced here even though `0x67d6d70` itself hashes `key+0x08..+0x0F`. [V]
- Prior 6ih attribution of description field hashing to this case/callee pairing is contradicted at this callsite and should be audited. [V contradiction]

## Open points [?]
- Actual FadeToBlack description producer/clone, required fields, minimum size, and defaults remain unidentified.
- Whether description `r15` is consumed later in this case's untraced tail/body or by pass consumers only.
- Correct semantic label for tag 5 path relative to FadeToBlack (mapping retained from existing docs but not independently proven by strings in this pass). [?]
