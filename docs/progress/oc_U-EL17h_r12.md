## NEXT
DONE

| offset | size | site | instr | meaning |
|--------|------|------|-------|---------|
| 0x5b7201b | 8 | sub_5b72000 | `0x5b7201b  mov rax,[rcx]` | load vtable ptr of options object (rcx = this from [rbp+0x58] in caller sub_895830) |
| 0x5b7201e | 8 | sub_5b72000 | `0x5b7201e  mov rax,[rax+0xD8]` | load vtable[0xD8] = get-option-by-id |
| 0x5b7202a | 4 | sub_5b72000 | `0x5b7202a  mov r8d,0x243` | set id argument = 0x243 (upscaling_percentage) |
| 0x5b72030 | call | sub_5b72000 | `0x5b72030  call qword ptr [0xF99FFA0]` | call vtable[0xD8] via thunk data_f99ffa0=sub_eea6040 (jmp rax) |
| 0x5b72053 | 4 | sub_5b72000 | `0x5b72053  mov edi,[rax+0x18]` | read upscaling_percentage option value field [opt+0x18] into edi |
| 0x5b7212a | 4 | sub_5b72000 | `0x5b7212a  mov edx,edi` | set upscaling_percentage value as 2nd arg |
| 0x5b7212c | call | sub_5b72000 | `0x5b7212c  call qword ptr [0xF99FFA0]` | call vtable[0xC0] of [rsi+0x1A40] with edx = upscaling_percentage |
| 0x89605c | call | sub_895830 | `0x89605c  call 0x5B72000` | caller sub_895830 invokes sub_5b72000 with rcx=[rbp+0x58] |
| 0x5b71f56 | 4 | sub_5b71f40 | `0x5b71f56  mov r8d,0x243` | second 0x243 reader: sets id arg before vtable[0xD8] call at 0x5b71f5c |
| 0x5b71f5c | call | sub_5b71f40 | `0x5b71f5c  call qword ptr [0xF99FFA0]` | calls vtable[0xD8] via thunk; then calls sub_d1720 on result |
| 0x246 | - | - | `-` | 0x246 reader via vtable[0xD8] NOT FOUND (imm 0x246 scan: only registration/WebRTC/SSL, no vtable[0xD8] call) |
| 0x1BB8 | 4 | sub_5b0b628 | `0x5b0b68d  mov [r13+0x1BB8],eax` | alt 0x243 reader caches upscaling_percentage to [r13+0x1BB8], consumer not yet found |
| 0x14 | - | - | `-` | store to [elem+0x14] not yet traced from any option reader |
| 0x1F0 | - | - | `-` | descriptor/ctx +0x1F0 store not yet traced from any option reader |

CLOSES? NO — 0x246 (targetResolution) reader via vtable[0xD8] not found; upscaling_percentage (0x243) reader sub_5b72000 passes value to vtable[0xC0] of [rsi+0x1A40] but not yet traced to [elem+0x14] or +0x1F0; endFrame indirect caller chain (ret=0x8890E4) to array1 builder to option read not yet connected.
