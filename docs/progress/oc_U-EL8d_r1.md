## NEXT
DONE

# Unit U-EL8d — Render targets and their formats (L8d)

## INPUT DATA
docs/progress/oc_U-L8d.md — texture upload / ClientTexture creation path from PNG decode chain (sub_6632fd0 -> sub_1994f90 -> PNG decoder -> pixel buffer -> texture object -> device texture slot). All instruction lines below are copied verbatim from that file (rdis-disassembled, [V]).

## Context
sub_6632fd0 [0x6632fd0..0x663430f] decodes "look_up_tables.png" via sub_1994f90 (0x66340e1 [V]), allocates a texture object via sub_eea6040 (0x663412b [V]), zeroes it via 0xEEC6ED0 (0x663414b [V]), copies decoded pixels into it via 0xEEC6DE0 (0x6634159 [V]), then stores the object into the device texture slot at [device+0x288] (device = [rbp+0x6F8] [V], rsi = [rax+0x288] at 0x6634165 [V]). The format/dim value ebx = [rbp-0x3C] is stored at slot +0x60 and +0x980, but the write that sets [rbp-0x3C] is not visible in this path (OPEN in oc_U-L8d.md), and no instruction or string identifies which DXGI format it is or that this texture is a render target.

## Verified instruction lines (for verify_oc)

 0x6634165  mov rsi,[rax+0x288]
 0x663416c  mov ebx,[rbp-0x3C]
 0x6634176  mov [rsi+0x970],r14
 0x663419e  mov [rsi+0x978],rdi
 0x66341a5  mov [rsi+0x980],ebx
 0x66341ab  mov [rsi+0x58],r14
 0x66341af  mov [rsi+0x60],ebx

## Texture slot fields (object stored at [device+0x288]; all sites listed per offset)

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|+0x58|8|0x66341ab|`0x66341ab  mov [rsi+0x58],r14`|texture object pointer (r14 = newly allocated object)|[V]|
|+0x60|4|0x66341af|`0x66341af  mov [rsi+0x60],ebx`|format/dim value (ebx = [rbp-0x3C])|[V]|
|+0x970|8|0x6634176|`0x6634176  mov [rsi+0x970],r14`|texture object pointer, replaces old slot value (old freed at 0x6634190)|[V]|
|+0x978|8|0x663419e|`0x663419e  mov [rsi+0x978],rdi`|texture byte size|[V]|
|+0x980|4|0x66341a5|`0x66341a5  mov [rsi+0x980],ebx`|format/dim value (ebx = [rbp-0x3C])|[V]|

## Format value source (not proven)

| [rbp-0x3C] | 4 | 0x663416c | `0x663416c  mov ebx,[rbp-0x3C]` | format/dim local read; write to [rbp-0x3C] not visible in sub_6632fd0 | [?] |

## Device slot base (on the device/ctx object)

| +0x288 | 8 | 0x6634165 | `0x6634165  mov rsi,[rax+0x288]` | device texture slot object base (rax = [rbp+0x6F8] = device/ctx)|[V]|

## CLOSES?
NO — the format/dim stores at +0x60 and +0x980 are proven [V], but the value that lands there ([rbp-0x3C] <- ?) is never written in the decoded path, and no instruction or string identifies which DXGI format it is or that this texture is a render target. Single blocking fact: the write to [rbp-0x3C] (format/dim source) and the DXGI format identity are not proven by any [V] row, so no render target format is established.
