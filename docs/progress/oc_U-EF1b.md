## NEXT
DONE

# oc U-EF1b — VV pass in/out resources from builder 0x55f1450 (checklist F1b pending part)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only.
Input data: docs/progress/oc_U-F1b.md, docs/progress/oc_U-F1b2.md (50 pass-declaration call sites, argument setup).
Pending item from checklist F1b: in/out resources per pass still pending.
This note extracts every distinct memory offset accessed in the call-site argument-setup instructions,
with size from the instruction, all call sites listed, and verbatim instr proof lines from the input data.
No offsets skipped.

## In/Out Resource Offsets — Table

| offset | size | read/store address | verbatim instr line | meaning |
|---|---|---|---|---|
| 0x3260 | 8 | [rbp+0x3260] | `0x55f1fc0  mov rcx,[rbp+0x3260]`<br>`0x55f1fdd  mov rcx,[rbp+0x3260]`<br>`0x55ff2b4  mov rcx,[rbp+0x3260]`<br>`0x55ff2e7  mov rcx,[rbp+0x3260]`<br>`0x55ff30c  mov rcx,[rbp+0x3260]`<br>`0x560b6ad  mov rcx,[rbp+0x3260]`<br>`0x560bcfc  mov rcx,[rbp+0x3260]`<br>`0x5610bb8  mov rcx,[rbp+0x3260]`<br>`0x5611a07  mov rcx,[rbp+0x3260]`<br>`0x5613b81  mov rcx,[rbp+0x3260]`<br>`0x5616719  mov rcx,[rbp+0x3260]`<br>`0x561ce09  mov rcx,[rbp+0x3260]`<br>`0x561e3a9  mov rcx,[rbp+0x3260]`<br>`0x561fd99  mov rcx,[rbp+0x3260]`<br>`0x5622aa8  mov rcx,[rbp+0x3260]`<br>`0x5625574  mov rcx,[rbp+0x3260]`<br>`0x562b142  mov rcx,[rbp+0x3260]`<br>`0x562cbf9  mov rcx,[rbp+0x3260]`<br>`0x562e4d2  mov rcx,[rbp+0x3260]`<br>`0x562e650  mov rcx,[rbp+0x3260]`<br>`0x563280d  mov rcx,[rbp+0x3260]`<br>`0x5632afd  mov rcx,[rbp+0x3260]`<br>`0x5633348  mov rcx,[rbp+0x3260]` | - |
| 0x27A0 | 8 | [rbp+0x27A0] | `0x55f1fd6  lea r8,[rbp+0x27A0]`<br>`0x55f2922  lea rcx,[rbp+0x27A0]`<br>`0x55f644a  lea rcx,[rbp+0x27A0]`<br>`0x55f67ad  lea rcx,[rbp+0x27A0]`<br>`0x560cc1a  lea rcx,[rbp+0x27A0]`<br>`0x5614190  lea rcx,[rbp+0x27A0]`<br>`0x561be7c  lea rcx,[rbp+0x27A0]`<br>`0x5621b30  lea rcx,[rbp+0x27A0]`<br>`0x5613b88  lea rdx,[rbp+0x27A0]`<br>`0x5616720  lea rdx,[rbp+0x27A0]`<br>`0x561ce10  lea rdx,[rbp+0x27A0]`<br>`0x561e3b0  lea rdx,[rbp+0x27A0]`<br>`0x561fda0  lea rdx,[rbp+0x27A0]`<br>`0x5622aaf  lea rdx,[rbp+0x27A0]`<br>`0x562b149  lea rdx,[rbp+0x27A0]` | - |
| 0x2C00 | 8 | [rbp+0x2C00] | `0x55f1fb9  lea r8,[rbp+0x2C00]`<br>`0x560cc0e  lea rax,[rbp+0x2C00]`<br>`0x562e4dc  lea r8,[rbp+0x2C00]`<br>`0x5633352  lea r8,[rbp+0x2C00]` | - |
| 0x1EF4 | 8 | [rbp+0x1EF4] | `0x55ff2be  lea r8,[rbp+0x1EF4]`<br>`0x562cc03  lea r8,[rbp+0x1EF4]` | - |
| 0x1C40 | 8 | [rbp+0x1C40] | `0x55ff2f1  lea r8,[rbp+0x1C40]`<br>`0x55ff316  lea r8,[rbp+0x1C40]`<br>`0x562557e  lea r8,[rbp+0x1C40]` | - |
| 0x2440 | 8 | [rbp+0x2440] | `0x560b6b7  lea r8,[rbp+0x2440]`<br>`0x5611a11  lea r8,[rbp+0x2440]`<br>`0x5632817  lea r8,[rbp+0x2440]`<br>`0x5632b07  lea r8,[rbp+0x2440]` | - |
| 0x1EA0 | 8 | [rbp+0x1EA0] | `0x560bd06  lea r8,[rbp+0x1EA0]` | - |
| 0x2848 | 8 | [rbp+0x2848] | `0x5610bbf  lea rdx,[rbp+0x2848]` | - |
| 0x2EF0 | 8 | [rbp+0x2EF0] | `0x560cc21  lea r9,[rbp+0x2EF0]`<br>`0x5610bcc  lea r9,[rbp+0x2EF0]`<br>`0x5614197  lea r9,[rbp+0x2EF0]`<br>`0x5616d31  lea r9,[rbp+0x2EF0]`<br>`0x561be83  lea r9,[rbp+0x2EF0]`<br>`0x5621b37  lea r9,[rbp+0x2EF0]` | - |
| 0x3200 | 8 | [rbp+0x3200] | `0x562f7fb  mov [rbp+0x3200],rcx`<br>`0x563102b  mov [rbp+0x3200],rcx` | - |
| rsp+0x38 | 8 | [rsp+0x38] | `0x5610b96  mov [rsp+0x38],rax` | - |
| rsp+0x30 | 8 | [rsp+0x30] | `0x5610ba2  mov [rsp+0x30],rax` | - |
| rsp+0x20 | 8 | [rsp+0x20] | `0x560cc15  mov [rsp+0x20],rax`<br>`0x5610bae  mov [rsp+0x20],rax` | - |
| rsp+0x28 | 1 | [rsp+0x28] | `0x5610bb3  mov byte ptr [rsp+0x28],1` | flag byte = 1 |
| 0x25F0 | 8 | [rbp+0x25F0] | `0x562e65a  lea r8,[rbp+0x25F0]` | - |
| 0x2100 | 8 | [rbp+0x2100] | `0x5634604  lea rcx,[rbp+0x2100]` | - |

## CLOSES?

NO — blocking fact: input data (oc_U-F1b2.md) gives argument-setup instructions per call site but does not decode the helper function signatures (sub_5667860, sub_5689800, sub_5698290, sub_5693680, sub_5694510, sub_5695960, sub_5696540, sub_5697650, sub_5684660), so the semantic in/out resource IDs (which bind slot is input vs output, texture vs buffer vs framebuffer) cannot be proven from the instruction lines alone. The table above proves which stack/struct offsets are read or written at each declaration call site (16 distinct offsets, all [V] by quoted instr), but not what resource each offset names.

## TOOL REQUESTS

- None yet
