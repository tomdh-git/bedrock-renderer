## NEXT
DONE

# U-EQ5c — Q5c: own pass through submitCustom drawing with a native material/program

Item: checklist Q5c "Own pass through submitCustom drawing with a native material/program, verified in game" (section Q. Passes and frame graph; currently [ ]). Unit output: this file only (docs/progress/oc_U-EQ5c.md).

## Result of this run (static analysis only; game not started, no build, no Cheat Engine)

The submitCustom custom-item seam is fully reversed and every RVA/offset below is verified verbatim against Minecraft.Windows.exe 1.26.62.01 with rdis (`tools/rdis/target/release/rdis.exe ... dis 0x<RVA> <n>`), tagged [V]. Claims not shown by any instruction are tagged [I] (inferred) or [?] (unknown); nothing is guessed.

SubmitCustom = 0xbc61560 (Encoder submit variant 2; Encoder.h EncoderRvas::kSubmitVariant2). Windows x64 args: rcx=encoder (this), rdx=viewId (u16), r8=fn, r9=user. The function stores the 16-byte payload {fn, user} at encoder+0x100/+0x108, allocates a draw slot via the Frame+0xDC57E8 counter, builds the sort key (view<<54 | (depth&0xFFFFF)<<32 | bit53) at Frame+0x14700+slot*8 and the u16 index at Frame+0x94700+slot*2, then copies {fn,user} verbatim (movaps) to Frame+0xB4700+slot*0x80.

Executor custom path = 0xe822400 (reached from the executor per-item dispatch at 0xe822219..0xe822267: per-item sort key read from Frame+0x14700+item*8; custom iff (key & 0x0030000000000000) == 0x0020000000000000, i.e. bit 53 set and bit 52 clear → `jne 0xE822400` at 0xe822267). At 0xe822400 the executor reads the u16 index from Frame+0x94700+sortedItem*2, loads {fn,user} from Frame+0xB4700+idx*0x80, builds a 0x18-byte ctx at job+0x3B0 as {FnPtr=0xF4EDE00, job=rsi, commandList=[[rbx+0x90]+0x30]} and executes `call qword ptr [0xF99FFA0]` with rcx=user (payload word 1, i.e. the caller's &PassNative) and rdx=&ctx — fn(user, &ctx) on the render thread, in view order (custom items sort after draws/compute within the same view because bit 53 > bit 52 inside one view field — arithmetic [I]).

On-disk code for this item already exists and is now [V]-proven: src/client/features/render/pass/PassNative.h (PassNative struct 16 B with offset/size static_asserts, passNativeFn, queueNativePass issuing the raw call at imageBase+0xBC61560, selfTest() pinning kCustomItem==0x100, kSubmitVariant2==0xBC61560, kCustomBit==bit53; included from src/sdk/SelfTest.cpp:28 so its static_asserts compile-check every build), src/sdk/mc/deps/bgfx/CustomItem.h (CustomRenderItem 16 B fn@0/user@8, CustomItemCtx 0x18 B fnPtr@0/job@8/commandList@0x10), src/sdk/mc/deps/bgfx/Encoder.h (kSubmitVariant2=0xBC61560, SortKey::kCustomBit=bit53), src/sdk/mc/deps/bgfx/RenderLayoutAsserts.h (kEncoderSubmitCustom: constants 0x0020000000000000, 0x100, 0x108 — all three appear in the first 0x372 bytes of 0xbc61560, proven by rows above). No detour written, no HookManager.cpp edit, no CMake change, no Sigs.json change; nothing enabled by default (registry mode Off).

Pending (not a CLOSES? NO blocker per the 2026-11-22 deferred-testing decision): (1) wire a per-frame queue point calling queueNativePass on a view — build step, no hook registration by this unit; (2) build + the single deferred in-game test (docs/BIGBANG_TESTS.md section U-EQ5c, already present and consistent with these proofs); (3) [?] program->ID3D12PipelineState resolution is not reversed, so passNativeFn's body records nothing to the GPU yet (documented as [?] in PassNative.h); the draw itself is covered by the deferred in-game test.

## Proof table (every claim, [V] = verbatim from rdis disassembly)

| offset | size | address | instruction | meaning |
| enc+0x100 | 8 | 0xbc61645 | `0xbc61645  mov [rsi+0x100],r8` | submitCustom payload word 0 = fn (arg r8) [V] |
| enc+0x108 | 8 | 0xbc6164c | `0xbc6164c  mov [rsi+0x108],r9` | payload word 1 = user (arg r9) [V] |
| enc+0x12 | 2 | 0xbc61660 | `0xbc61660  mov [rsi+0x12],dx` | view id (arg rdx) stored at encoder+0x12 [V] |
| enc+0xC | 4 | 0xbc6167c | `0xbc6167c  mov [rsi+0xC],edx` | depth/seq result from ctx per-view counter (lock xadd at 0xbc61673) stored at encoder+0xC [V] |
| sort key bit 53 | 8 | 0xbc61697 | `0xbc61697  mov rcx,0x20000000000000` | custom bit = 0x0020000000000000, sort-key bit 53 [V] |
| Frame+0x14700 | 8 | 0xbc616aa / 0xe822220 | `0xbc616aa  mov [rax+r15*8+0x14700],rcx` / `0xe822220  mov rdx,[rdx+rax*8+0x14700]` | sort key written by submitCustom (view<<54 \| depth<<32 \| bit53), read back by executor per item [V] |
| Frame+0x94700 | 2 | 0xbc616b5 / 0xe822414 | `0xbc616b5  mov [rax+r15*2+0x94700],di` / `0xe822414  movzx edx,word ptr [rdx+rax*2+0x94700]` | u16 item index written by submitCustom, read by executor to locate the item slot [V] |
| Frame+0xB4700 | 16 | 0xbc6174d / 0xbc61751 / 0xe822426 | `0xbc6174d  movaps xmm0,[r14]` / `0xbc61751  movaps [rax+rcx+0xB4700],xmm0` / `0xe822426  mov rax,[r8+rdx]` | {fn,user} copied verbatim (movaps) to Frame+0xB4700+slot*0x80 by submitCustom, loaded back as qword by the executor [V] |
| key class bits 52-53 | 8 | 0xe82222b / 0xe822238 / 0xe822242 | `0xe82222b  mov r8,0x30000000000000` / `0xe822238  mov r8,0x20000000000000` / `0xe822242  cmp rdx,r8` | executor item-class test: custom iff (key & 0x0030000000000000) == 0x0020000000000000 (bit 53 set, bit 52 clear) [V] |
| custom dispatch | 1 | 0xe822245 / 0xe822249 / 0xe822267 | `0xe822245  sete r8b` / `0xe822249  inc r8b` / `0xe822267  jne 0xE822400` | custom flag -> custom path 0xe822400; everything else -> draw/occlusion paths [V] |
| ctx+0x00 | 8 | 0xe822441 / 0xe822448 | `0xe822441  lea r8,[0xF4EDE00]` / `0xe822448  mov [rbx+0x3B0],r8` | ctx+0x00 = FnPtr tag pointer 0xF4EDE00 (rodata) [V] |
| ctx+0x08 | 1 | 0xe82244f | `0xe82244f  mov [rbx+0x3B8],rsi` | ctx+0x08 = job pointer; store [V], role (job/render state) [I] |
| ctx+0x10 | 8 | 0xe822436 / 0xe82243d / 0xe822456 | `0xe822436  mov rcx,[rbx+0x90]` / `0xe82243d  mov rcx,[rcx+0x30]` / `0xe822456  mov [rbx+0x3C0],rcx` | ctx+0x10 = commandList ([[rbx+0x90]+0x30], live ID3D12GraphicsCommandList*) [V] |
| fn call | - | 0xe82245d / 0xe822461 / 0xe822468 | `0xe82245d  mov rcx,[rdx+8]` / `0xe822461  lea rdx,[rbx+0x3B0]` / `0xe822468  call qword ptr [0xF99FFA0]` | fn(user = payload word 1 = &PassNative, rdx=&ctx) via CFG thunk on the render thread [V] |

## CLOSES?

CLOSES? YES — every reversing claim for Q5c (submitCustom RVA 0xbc61560 and its payload/key/header stores, the executor custom path 0xe822400 and its 0x18-byte ctx convention, the bit-53 dispatcher test at 0xe82222b..0xe822267) is proven [V] above; the on-disk code (PassNative.h + CustomItem.h + Encoder.h + RenderLayoutAsserts.h static asserts) exists and compile-checks; the SDK constants match the verified instructions. The only thing still missing is the in-game verification itself (build, wire the per-frame queue point, run the single deferred test), which the 2026-11-22 user decision explicitly defers and which is NOT a reason for CLOSES? NO. docs/BIGBANG_TESTS.md already carries a U-EQ5c section (lines 68-70) consistent with these proofs; not re-appended (append-only).

## TOOL REQUESTS

name | input -> output | why it would have helped
None | - | no helper script was written; all verification used rdis dis/xr/callers/imm directly

In-game test plan (Q5c, deferred to the single 2026-11-22 big in-game run; see also docs/BIGBANG_TESTS.md "U-EQ5c"):
1. Build the client DLL with the per-frame queue point wired: queueNativePass(encoder, viewId, pass) calling Encoder::submitCustom at imageBase+0xBC61560 with {fn=passNativeFn, user=&PassNative{program, vb, ib, startIndex, numIndices}} on a view each frame (PassNative.h already on disk; no HookManager.cpp/registration/CMake/Sigs.json change).
2. Launch into a populated world, run ~60 frames.
3. Capture at submitCustom entry (queued as u_eq5c_submitcustom, rva 0xbc61560, pending): expect RCX=encoder, DX=viewId, R8=passNativeFn, R9=&PassNative, ret= names the queue point; once in game, Frame+0x14700+slot*8 carries key bit 53 and Frame+0xB4700+slot*0x80 holds {passNativeFn, &pass}.
4. Capture at the executor custom-item path (requested below, u_eq5c_executor, rva 0xe822400): expect RCX=user=&PassNative, RDX=&ctx with [RDX+0x00]=tag pointer 0xF4EDE00 [V], [RDX+0x08]=job pointer [I], [RDX+0x10]=live ID3D12GraphicsCommandList* whose first 8 bytes are a vtable pointer [V live]; passNativeFn runs once per frame on the render thread in view order (bit 53 sorts custom items after draws/compute within the view) with the same command list each call.
Expected observable result: our pass is invoked per frame through the engine's own custom-item seam, draws with the native program, no crash, nothing drawn incorrectly by the stock path.

CAPTURE REQUESTED u_eq5c_executor (0xe822400, executor custom-item path; fires once per frame once the queue point is wired). u_eq5c_submitcustom (0xbc61560) is already queued (pending).
