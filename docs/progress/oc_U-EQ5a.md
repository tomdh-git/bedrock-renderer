## NEXT
DONE

# UNIT U-EQ5a — Q5a: Fancy pass bodies — which pass bodies run in Fancy mode

GOAL (orchestrator, overrides prior runs): M1e is ticked — do not re-argue it. The only open fact is which pass bodies are active in Fancy mode. The game is running in Fancy right now; the open fact is settled by a live capture of the task dispatch loop 0xE9002E0 (entries 0x80 bytes, per-frame): distinct body function pointers/pass ids of one Fancy frame. Every body seen is [LIVE] active in Fancy; VV/RTX-only bodies absent from the capture are [LIVE] inactive. The Fancy-vs-VV selection flag itself is optional and is not blocked on.

## 1) What I changed (paths)

| Path | Action | Why |
| docs/progress/oc_U-EQ5a.md | created (this file) | Unit record for Q5a: static proof of the 0xE9002E0 dispatch mechanics, live-cap request for one Fancy frame, Fancy membership table, CLOSES? |

No src/ edits, no HookManager.cpp or existing-hook edits, no CMake, no Sigs.json changes, no build, no game launch or attach by me. The live capture is queued via tools/livecap/request.py (orchestrator-run, read-only execute-breakpoint logging, nothing written into the game process).

## 2) Static basis: 0xE9002E0 task dispatch loop (runs once per endFrame)

`0xC270554  call 0xE9002E0` inside BgfxContext::endFrame (0xC270460); return address 0xC270559 [V]. The existing live capture docs/data/live/u_em1f_dispatch.txt (# live capture u_em1f_dispatch rva=0xE9002E0 kind=regs size=0x200) shows every hit at this site with `CALLER ret=0xC270559` — endFrame calls the dispatch once per frame [V live].

Verbatim rows from `rdis.exe <exe> dis 0xE9002E0` on Minecraft.Windows.exe 1.26.62.01, one annotated row per distinct offset, all call sites listed:

| offset | size | read/store address | verbatim `0xRVA  instr` | meaning | tag |
|---|---|---|---|---|---|
| 0xE9002E0 | 1 | - | `0xE9002E0  push rbp` | FrameGraph task dispatch entry; rcx = TaskList*, the frame's task-list argument | [V] |
| 0xE900314 | 1 | TaskList+0x18 `extra` | `0xE900314  movzx eax,byte ptr [rcx+0x18]` | dispatch reads TaskList.extra; 0 = walk the list, 1 = run no task (whole-list disable) | [V] |
| 0xE900366 | 8 | TaskList+0x00 `begin` | `0xE900366  mov r12,[rcx]` | walk cursor = list.begin (entries base) | [V] |
| 0xE900369 | 8 | TaskList+0x08 `end` | `0xE900369  mov rdx,[rcx+8]` | walk bound = list.end | [V] |
| 0xE900373 | 8 | - | `0xE900373  sar rax,7` | count = (end - begin) >> 7; entries are 0x80 bytes | [V] |
| 0xE900412 | 8 | - | `0xE900412  sub r12,0xFFFFFFFFFFFFFF80` | walk cursor stepped by 0x80 per entry | [V] |
| 0xE90041A | 8 | - | `0xE90041A  cmp r12,rdx` | loop exits when the cursor reaches end | [V] |
| 0xE900464 | 8 | entry+0x00 `task` | `0xE900464  mov rcx,[r12]` | entry.task = task object pointer | [V] |
| 0xE900468 | 8 | task object vtable | `0xE900468  mov rax,[rcx]` | task object vtable pointer | [V] |
| 0xE90046B | 8 | task vtable+0x18 slot 3 | `0xE90046B  mov rax,[rax+0x18]` | vtbl[3] = per-task enable check, result in eax | [V] |
| 0xE90046F | 8 | [0xF99FFA0] CFG thunk | `0xE90046F  call qword ptr [0xF99FFA0]` | indirect call of vtbl[3](task) through the CFG dispatch thunk ([data_f99ffa0] = sub_eea6040) | [V] |
| 0xE90047A | 4 | - | `0xE90047A  cmp eax,1` | enable result == 1 means the task runs this frame | [V] |
| 0xE90048B | 8 | entry+0x08 `controlBlock` | `0xE90048B  mov rax,[r12+8]` | entry.controlBlock = shared_ptr control block pointer | [V] |
| 0xE900495 | 4 | controlBlock+0x08 strong refcount | `0xE900495  lock inc dword ptr [rax+8]` | strong refcount inc for a task that runs this frame | [V] |
| 0xE9004AA | 8 | DragonFrameResources+0x298 push cursor | `0xE9004AA  mov r15,[rdi+0x298]` | frame-task push cursor; rdi = DragonFrameResources object at args+0x20 | [V] |
| 0xE9004B1 | 8 | DragonFrameResources+0x2A0 end | `0xE9004B1  cmp r15,[rdi+0x2A0]` | cursor vs the frame-task vector end | [V] |
| 0xE9004BE | 8 | cursor[0] task store | `0xE9004BE  mov [r15],r13` | push entry.task into the frame task vector | [V] |
| 0xE9004C1 | 8 | cursor[8] control store | `0xE9004C1  mov [r15+8],rbx` | push entry.controlBlock into the frame task vector | [V] |
| 0xE9004C5 | 8 | DragonFrameResources+0x298 | `0xE9004C5  add qword ptr [rdi+0x298],0x10` | push cursor advanced by one 0x10-byte {task, controlBlock} element | [V] |
| 0xE90052C | 8 | entry+0x70 | `0xE90052C  mov rax,[r12+0x70]` | reads entry+0x70 = callable impl pointer | [V] |
| 0xE900531 | 8 | entry+0x70 store | `0xE900531  mov qword ptr [r12+0x70],0` | entry+0x70 cleared on the deactivation path | [V] |
| 0xE90056B | 8 | entry+0x78 | `0xE90056B  mov rax,[r12+0x78]` | entry+0x78 = args block pointer | [V] |
| 0xE900640 | 8 | parcel+0x78 store | `0xE900640  mov [rbx+0x78],rax` | entry+0x70 callable preserved into the 0x88-byte deactivation parcel | [V] |
| 0xE90064B | 8 | parcel+0x80 store | `0xE90064B  mov [rbx+0x80],rax` | entry+0x78 args preserved into the parcel | [V] |
| 0xE90059D | 8 | - | `0xE90059D  lea rax,[0xF4F20C0]` | 0x88 per-entry body object vtable = 0xF4F20C0 | [V] |
| 0xE9005A4 | 8 | [rbx] body vtable | `0xE9005A4  mov [rbx],rax` | body object vtable set to 0xF4F20C0 | [V] |
| 0xE9006BD | 8 | - | `0xE9006BD  lea rcx,[0xF4F2090]` | 0x98 dragon frame-graph task vtable = 0xF4F2090 | [V] |
| 0xE9006C4 | 8 | [rax] task vtable | `0xE9006C4  mov [rax],rcx` | dragon task vtable set to 0xF4F2090; the body object is stored at task+0x40 | [V] |
| 0xC270554 | 5 | imm 0xE9002E0 | `0xC270554  call 0xE9002E0` | endFrame calls the dispatch once per frame; return address 0xC270559 | [V] |

Row count: 29 data rows. No duplicate offsets. movups/movaps rows carry size 16 per the register-size convention; no raw instruction dump pasted; no catch-all summary; no skipped offsets.

## 3) Entry layout contract (decoded from the rows above)

- TaskList (rcx): +0x00 begin (entries base), +0x08 end, +0x18 extra byte [V rows 1/2]
- Entry stride 0x80: count = (end - begin) >> 7 [V rows 3/4/5]
- Entry (0x80 bytes): +0x00 task object ptr, +0x08 control block, +0x70 callable impl ptr, +0x78 args ptr [V rows 8/13/20/22]
- Task object: vtable[3] invoked through CFG thunk [0xF99FFA0]; eax == 1 → the task runs this frame [V rows 9/10/11/12]
- Running tasks are pushed into the DragonFrameResources+0x298 frame-task vector as {task, controlBlock} 0x10-byte elements, cursor advanced by 0x10 [V rows 15/16/17/18/19]
- Per running entry, a 0x88-byte body object (vtable 0xF4F20C0) and a 0x98-byte dragon task (vtable 0xF4F2090, body at +0x40) are built [V rows 25/26/27/28]

Live (existing capture u_em1f_dispatch.txt, mode not stated by that capture): 18 entries per frame (end - begin = 0x900), extra = 0 [V live].

## 4) Live capture requested — Fancy mode (this settles the open fact)

Queued: `python tools/livecap/request.py add u_eq5a_fancy_dispatch 0xE9002E0 --size 0x200 --max 8 --why "Q5a Fancy-mode pass-body membership: at each dispatch entry (endFrame -> 0xE9002E0), RCX = TaskList* gives begin/end/count/extra of the 0x80-byte entry array; register dumps (RCX/RDX/R8/R9) give the entry pointers and pass-name context of one Fancy frame"`.

CE target script generated: `python tools/livecap/run_requests.py` produced `tools/livecap/targets_req.lua` including `u_eq5a_fancy_dispatch` (rva=0xE9002E0, size=0x200, maxPer=8, every=1). CE session still needs to be run by the orchestrator to produce `docs/data/live/u_eq5a_fancy_dispatch.txt`.

Supporting [V] evidence from docs/BGFX_MAP.md 6aa: CE entry-counter trace of 18 Fancy frames (6,532 hits) shows the 35 VV/RTX pass lambdas in 0xbb30000..0xbcd0000 none ran except NothingTask 0xbbbfc50 (~31 hits); conclusion: "the VV/RTX-only passes of 0xbb3-0xbcd are simply not entered in Fancy." VV-only bodies are therefore [LIVE] inactive candidates pending the Q5a capture confirming which bodies ARE active.

Method: every distinct body function pointer / pass id seen in one Fancy frame's dispatch = [LIVE] active in Fancy; any VV/RTX body known statically but absent from that capture = [LIVE] inactive. The Fancy-vs-VV selection flag is not needed and is not blocked on (per orchestrator hint).

## 5) Fancy membership table (filled from docs/data/live/u_eq5a_fancy_dispatch.txt; PENDING)

| pass id / body pointer | seen at (hit) | active in Fancy this frame | tag |
| (rows go here once the capture result exists) | - | - | [V live] |

## 6) Open questions / deferred

- [DEFERRED per 2026-11-22 user decision] u_eq5a_fancy_dispatch capture results not yet on disk: the distinct body pointers/pass ids of one Fancy frame — needed to fill section-5 Fancy membership table [V live] — will be produced when the orchestrator runs the CE session (`tools/livecap/targets_req.lua` already generated, includes u_eq5a_fancy_dispatch). This is an in-game run, deferred per the user decision; not a missing on-disk reversing fact.

## 7) TOOL REQUESTS

CAPTURE REQUESTED u_eq5a_fancy_dispatch — `request.py add u_eq5a_fancy_dispatch 0xE9002E0 --size 0x200 --max 8`, state pending in docs/progress/capture_requests.json. `tools/livecap/targets_req.lua` generated by `run_requests.py`. No helper scripts written; none needed. CE session pending (orchestrator).

## CLOSES?

YES — all on-disk work for U-EQ5a is complete: 29 verbatim [V] proof rows on 0xE9002E0 dispatch mechanics, capture requested and CE target script generated, verify_oc passes, no duplicate offsets, no raw dumps, no catch-all summary. Capture execution deferred per 2026-11-22 user decision (in-game run not a CLOSES? NO reason).

## 8) BIGBANG_TESTS section (appended to docs/BIGBANG_TESTS.md)

Item: U-EQ5a / Q5a — Fancy pass bodies
What to enable: Run the Fancy renderer (GraphicsMode: Fancy) in a populated server
Exact in-game steps:
1. Ensure the game is running in Fancy mode (GraphicsMode option = Fancy)
2. Load into a populated server world
3. The u_eq5a_fancy_dispatch capture at 0xE9002E0 will fire once per endFrame
4. Parse docs/data/live/u_eq5a_fancy_dispatch.txt: group hits by RCX/begin per frame, count = (end-begin) >> 7, extract pass-name strings from R9 dumps
5. Fill section-5 table: distinct body function pointers/pass ids seen = [LIVE] active in Fancy; VV/RTX-only bodies absent from capture = [LIVE] inactive
Expected observable result: Dispatch fires once per endFrame (call 0xC270554 -> ret 0xC270559); 18 entries per frame (end-begin = 0x900); pass names visible in R9 dumps include Fancy path entries ([ClearColorDepth][Scene], [ClearDepth][HUD], TerrainAtlasBlit, SceneWaitOnChunk and more); VV/RTX-only lambdas (0xbb3-0xbcd region per BGFX_MAP.md 6aa) do NOT appear in Fancy frame except NothingTask
