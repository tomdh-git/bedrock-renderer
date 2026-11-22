## NEXT
DONE

# UNIT U-EC4a — DragonFrameResources object size + constructor (endFrame 0xe9002e0)

Goal (pending part only): C4a checklist — the DFR vector fields +0x290/+0x298/+0x2A0 (begin/end/capacity of vector<shared_ptr<Task>>, 0x10 stride, push stores {task*,ctrl} then `add qword ptr [rdi+0x298],0x10`) are proven [V] in oc_U-EC4a_r1/r2; the "remaining fields" +0x08/+0x0C/+0x10/+0x18 are proven NOT DragonFrameResources fields (taskList/shared_ptr fields: rdi=taskList until `0xe900483  mov rdi,[r15+0x20]`). What remains pending: DragonFrameResources OBJECT SIZE and CONSTRUCTOR.

## Register discipline (proven)
0xe9002e0(taskList* rcx, args* rdx); r15=rdx at `0xe90032a  mov r15,rdx`, rdi=rcx=taskList at `0xe90032d  mov rdi,rcx`, rdi reassigned to DragonFrameResources at `0xe900483  mov rdi,[r15+0x20]` (r15=args, so rdi=args+0x20=DFR*). Every `[rdi+off]` from 0xe900483 on is DFR; endFrame touches DFR only at +0x290/+0x298/+0x2A0 and performs no DFR allocation, memset, or constructor call.

## Answer table (pending part: object size + constructor)
| name | rva/offset | size | verbatim `0xRVA  instr` proof | meaning | tag |
|---|---|---|---|---|---|
| DragonFrameResources object size (lower bound) | +0x2A0 | 8 | `0xe900add  mov [rdi+0x2A0],rax` | highest DFR field accessed in endFrame (+0x2A0 accessed as qword = vector capacity end) → DFR object size ≥ 0x2A8; exact total size not shown by any instruction | [I] |
| DragonFrameResources constructor | - | - | - | not found: no function in .text zero-inits the three vector slots {+0x290,+0x298,+0x2A0} as an empty vector; full fld sweep of all writes to those locations (9507+7132+9164 sites) shows only 0xe9002e0 maintaining an existing vector; DFR has no vtable/RTTI (the only "DragonFrame" string in the binary, at 0xf8326b0, is the EH decorated name of endFrame, not class RTTI) | [?] |
| DragonFrameResources object size (exact) | - | - | - | DFR is embedded at owner+0x268 (owner = FrameContext+0x18, FrameContext = *(BgfxFrameBuilder+0x28)) and passed into endFrame by reference; no instruction reveals the object's total size; size lower bound ≥0x2A8 only | [?] |

## New angles tried — all failed
- `rdis fld 0x290/0x298/0x2A0 --w` over the whole image (uncapped): correlated every function writing all three slots — none initializes them as an empty vector {(0,0,0) or (ptr,ptr,ptr)} except 0xe9002e0 itself. The (0,0xF)-pattern functions (sub_ab220, sub_227600, sub_228710, sub_7a7e0, sub_321e50, sub_15304c0, sub_15784e0) are other objects: their +0x2A0 is a byte or end=0xF, incompatible with DFR's push-at-[end] semantics; sub_17a7a0 swaps triplets, sub_2a2370/sub_2a2780 splice intrusive lists, sub_1310ad0 uses a 0x7FFFFFFFFFFFFFFF sentinel.
- `rdis fld 0x4F8/0x500/0x508 --w` (owner-relative DFR slots at owner+0x268): no function zero-inits all three as an empty vector either (sub_1507f60, sub_15c9090, sub_1662830 show the same foreign (0,0xF) class).
- `rdis struct 0xe9002e0`: no struct layout recovered.
- `rdis find` for "DragonFrameResources" ASCII: 0 hits (code section); `xref str "DragonFrame"` finds only the decorated endFrame name at 0xf8326b0 (referenced by .rdata qword at 0xf4788f0+8) → no class RTTI, DFR non-polymorphic, no vtable/ctor-via-vtable route.
- livemem: no static global anchor to a live owner or DFR instance (BgfxContext global @0x12ae1748 → 0x49c80010040 is passed as rcx to endFrame; DFR arrives as a separate rdx reference and is never stored back to Context; closure/owner are per-frame) → live instance hunt not feasible.
- oc_U-C4a2 owner-constructor chain (FrameContext/owner/BgfxFrameBuilder constructors) remains blocked.

## CLOSES?
NO. The pending parts are not proven by [V] rows: DragonFrameResources exact object size (only the lower bound ≥0x2A8 [I]) and the constructor (none found). Single blocking fact: DFR is passed into endFrame/0xe9002e0 by reference (args+0x20 → rdi at `0xe900483  mov rdi,[r15+0x20]`); endFrame contains no DFR allocation, memset, or constructor call, no .text function initializes DFR's three vector slots or reveals the object's total size, and the owner-object constructor chain is blocked.

## TOOL REQUESTS
None.
