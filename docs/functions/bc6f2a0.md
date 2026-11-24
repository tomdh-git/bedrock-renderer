# Dossier: bgfx destroy-handle enqueue (cmd 0x1C) (0xbc6f2a0)

## Mechanical facts
- [V] Size 0xbb bytes, 1 block, proven extent, 3 xrefs in (rdis).
- [V] Signature (inferred): `void enqueueDestroyA(Context* ctx /*rcx*/, u16 handle /*dx*/)`.
- [V] Callees: `0xebdbf10` (lock, arg `ctx+0x1C0`), `0xebce390` x2 (append bytes), `0xebdbf20` (unlock).

## Behavior [V]
1. Locks `ctx+0x1C0`.
2. `Frame* f = ctx->fillFrame /* [ctx+0x1CFD0C8] */`.
3. Pushes handle into Frame tail list: `f->listA[idx++] = handle` where `idx = f->countA` at `f+0xE47828` (u16), data array at `f+0xE45828` (u16[idx]).
4. Appends post-command to `f->cmdPost` (`cursor u32 at f+0xE05820`, data at `f+0xE05828`): byte `0x1C`, aligns cursor to even +2, appends `u16 handle`, cursor += 2.
5. Unlocks.

## A4-A8 relevance
- [V] Concrete API-thread resource-destroy queueing primitive: handle recorded in a per-frame handle list and a post-cmd opcode+payload emitted for render-thread consumption. Paired with `0xbc6f800` (opcode 0x1D, list/count at +0xE498AC/+0xE478AC).

## Verification
- Static: `rdis sum/dis 0xbc6f2a0`. Source: src/client/features/render/native/bgfx/sub_bc6f2a0.cpp (`// LIFT 0xbc6f2a0 size 0xbb 1.26.62.01 sub_bc6f2a0`).

## Reversed source (complete)

// void sub_bc6f2a0(Context* ctx /*rcx*/, u16 handle /*dx*/) -> void   (exe 0xbc6f2a0..0xbc6f35b, size 0xbb)

// 0xbc6f2a0..0xbc6f2c9
stackCookie = 0xFFFFFFFFFFFFFFFEULL;              // 0xbc6f2ac  mov qword ptr [rbp-8],0xFFFFFFFFFFFFFFFE
handleSlot = handle;                               // 0xbc6f2b4  mov esi,edx / 0xbc6f2b9  mov [rbp-0xC],dx
opcode = 0x1C;                                     // 0xbc6f2f1  mov byte ptr [rbp-9],0x1C
lockPtr = &ctx->bgfxLock;                          // 0xbc6f2bd  add rcx,0x1C0 / 0xbc6f2c4  mov [rbp-0x18],rcx
sub_ebdbf10(lockPtr);                              // 0xbc6f2c8  call 0xEBDBF10   ; lock
//      0xbc6f2c8  call 0xEBDBF10

// 0xbc6f2c9..0xbc6f2ea
Frame* f = ctx->fillFrame;                         // 0xbc6f2cd  mov rax,[rdi+0x1CFD0C8]
std::uint16_t idx = f->handleListCount;            // 0xbc6f2d4  movzx ecx,word ptr [rax+0xE47828]
f->handleList[idx] = handleSlot;                   // 0xbc6f2db  mov [rax+rcx*2+0xE45828],si
f->handleListCount = (u16)(idx + 1);               // 0xbc6f2e3  inc word ptr [rax+0xE47828]

// 0xbc6f2ea..0xbc6f311
f = ctx->fillFrame;                                // 0xbc6f2ea  mov rsi,[rdi+0x1CFD0C8] (reloaded after lock)
cursor0 = f->cmdPostCursor;                        // 0xbc6f2f5  mov eax,[rsi+0xE05820]
sub_ebce390(f->cmdPostData + cursor0, &opcode, 1);  // dst = f+0xE05828+cursor0, src = &opcode, size = 1
//      0xbc6f2fb  lea rcx,[rsi+rax] / 0xbc6f2ff  add rcx,0xE05828 / 0xbc6f306  lea rdx,[rbp-9] / 0xbc6f30a  mov r8d,1
//      0xbc6f310  call 0xEBCE390

// 0xbc6f311..0xbc6f32a
aligned = (cursor0 & 0xFFFFFFFEu) + 2u;            // 0xbc6f31d  mov ecx,[rsi+0xE05820] / 0xbc6f323  and ecx,0xFFFFFFFE / 0xbc6f326  add ecx,2
f->cmdPostCursor = aligned;                        // 0xbc6f329  mov [rsi+0xE05820],ecx

// 0xbc6f32a..0xbc6f343
sub_ebce390(f->cmdPostData + aligned, &handleSlot, 2);  // dst = f+0xE05828+aligned, src = &handleSlot, size = 2
//      0xbc6f32f  add rcx,rax / 0xbc6f332  lea rdx,[rbp-0xC] / 0xbc6f336  mov r8d,2
//      0xbc6f33c  call 0xEBCE390
f->cmdPostCursor = aligned + 2u;                   // 0xbc6f342  add dword ptr [rsi+0xE05820],2

// 0xbc6f343..0xbc6f35b
sub_ebdbf20(lockPtr);                              // 0xbc6f349  mov rcx,[rbp-0x18] / 0xbc6f34d  call 0xEBDBF20 ; unlock
//      0xbc6f352  nop / 0xbc6f353  add rsp,0x40 / 0xbc6f357  pop rdi / 0xbc6f358  pop rsi / 0xbc6f359  pop rbp / 0xbc6f35a  ret

## Struct fields touched (offset, size, direction, meaning, instruction)
| struct | offset | size | R/W | meaning | instruction |
| Context | 0x1C0 | 4 | R (address taken) | lock field; &ctx->bgfxLock passed to lock/unlock | 0xbc6f2bd / 0xbc6f349 |
| Context | 0x1CFD0C8 | 8 | R | Frame* fillFrame | 0xbc6f2cd / 0xbc6f2ea |
| Frame | 0xE47828 | 2 | R/W | handle-list count | 0xbc6f2d4 / 0xbc6f2e3 |
| Frame | 0xE45828 | 2 | W | handleList[count] = handle | 0xbc6f2db |
| Frame | 0xE05820 | 4 | R/W | cmd-post cursor | 0xbc6f2f5 / 0xbc6f31d / 0xbc6f329 / 0xbc6f342 |
| Frame | 0xE05828 | 1 | W | cmdPost[cursor] = 0x1C | 0xbc6f2fb .. 0xbc6f306 |
| Frame | 0xE05828 + aligned | 2 | W | cmdPost[aligned..aligned+1] = handle (u16 LE) | 0xbc6f32f .. 0xbc6f33c |

## Calls (target, call site, target class)
| target | call sites | target class |
| 0xebdbf10 | 0xbc6f2c8 `0xbc6f2c8  call 0xEBDBF10` | lift (native_boundary.tsv) — forward-declared native::sub_ebdbf10, called directly |
| 0xebce390 | 0xbc6f310 `0xbc6f310  call 0xEBCE390`, 0xbc6f33c `0xbc6f33c  call 0xEBCE390` | lift (native_boundary.tsv) — forward-declared native::sub_ebce390, called directly; entry 0xEBCE390 is a 5-byte jmp-forwarder to 0xEEC6EC0 |
| 0xebdbf20 | 0xbc6f34d `0xbc6f34d  call 0xEBDBF20` | lift (native_boundary.tsv) — forward-declared native::sub_ebdbf20, called directly |

## Ownership / threading
[V] docs/BGFX_MAP.md line 479: 0xbc6f2a0 is one of the per-resource destroy functions called while draining; this function lock/unlocks ctx+0x1C0 around the per-frame handle list and cmd-post mutations (API-thread render queue primitive, paired with 0xbc6f800 opcode 0x1D).
