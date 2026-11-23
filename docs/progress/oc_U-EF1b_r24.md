## NEXT
DONE

# oc U-EF1b — VV pass vtable/execute-body chain for the 6 remaining F1b passes (checklist F1b, BGFX_MAP 6ar)

Source: Minecraft.Windows.exe 1.26.62.01, RVAs relative to image base. Static analysis only (rdis disassembly). Builder: sub_55f1450 [0x55f1450..0x563f594) [V preflight].

Pending passes (order per ORCHESTRATOR 2026-11-22):
1. FullScreenOverlayObjects  2. FullScreenOverlayTransparent  3. WaitOnUpscalingOutput  4. ClearStencil/WaterSurfaceStencil  5. ClearGBuffer/ScenePrepass  6. TransparentDegamma

Method per pass (ORCHESTRATOR 2026-11-22): name-string xref -> declare helper -> helper's first `lea rax,[rip+vtable]` / `mov [rcx],rax` (vtable stored into new pass object) -> vt that RVA -> slot1 -> `lea r8` -> execute body -> resources read/written as [V] rows. One pass fully before the next; rows written as I go.

6 other passes already have [V] rows (per oc_U-EF1b_r20: vtables 0xF25C790/0xF25C940/0xF25C890/0xF25CA70/0xF43EA70/0xF25C830 with slot-1 installer thunks tail-jumping 0xBC61560). Do not redo them. CLOSES? YES only when all 12 passes have [V] resource rows.

## Reference chain — the `slot1 -> lea r8 -> execute body` pattern (done passes, contrast) [V rdis]

vtable 0xF25C790 slot1 = sub_568B9E0 (installer thunk) tail-jumping 0xBC61560 to body 0x568BCD0 [V]:
| offset | size | read/store address | instr | meaning |
| vt0xF25C790+0x8 | 8 | [body] | `0x568ba60  lea r8,[0x568bcd0]` | load execute-body address into r8 | [V] |
| vt0xF25C790+0x8j | - | [rsi] | `0x568ba70  jmp 0xbc61560` | tail-jump installer | [V] |

Installer 0xBC61560 stores the installed body into the pass object [V]:
| pass+0x100 | 8 | [rsi+0x100] | `0xbc61645  mov [rsi+0x100],r8` | store installed body pointer | [V] |
| pass+0x108 | 8 | [rsi+0x108] | `0xbc6164c  mov [rsi+0x108],r9` | store pass `this` | [V] |

## Pass 1 — FullScreenOverlayObjects (name string RVA 0x562EF35) [V]

Name built inline in builder (name-first descriptor object, name at +0x0). `0xF546B7A` = "FullScreenOverla" [V PE byte check + rdis `0x56104c0  movups xmm7,[0xF546baa]`]. Builder code [V listing]:
| fso+0x0 | 16 | [rsi] | `0x562ef3d  movupd [rsi],xmm7` | store 16B name prefix "FullScreenOverla" at object+0x0 | [V] |
| fso+0x10 | 8 | [rsi+0x10] | `0x562ef4b  mov [rsi+0x10],rax` | store "yObjects" at object+0x10 | [V] |
| fso+0x18 | 1 | [rsi+0x18] | `0x562ef4f  mov byte ptr [rsi+0x18],0` | null-terminate name | [V] |

Result name = "FullScreenOverlayObjects" [V].

Declare helper call [V listing]:
| fso+0x0h | - | [rbp+0x1a48] | `0x562ee0f  call 0xbb66e20` | declare helper 0xBB66E20 | [V] |
| fso+0x0s | - | [0xF5342CB] | `0x562ef87  lea r9,[0xF5342cb]` / `0x562ef8e  call 0x9d6d0` | string "FullScreenOverlayTransparent" copy helper 0x9D6D0 | [V] |

Vtable / slot1 / body: the builder does NOT install an installer vtable for FullScreenOverlayObjects — no `lea rax,[rip+installer-vtable]` / `mov [object],rax` store was found in its declaration code. No `lea r8` installer thunk -> execute body reachable. [V negative result]

Resource rows: none derived (no execute body located). [V negative result]

## Pass 2 — FullScreenOverlayTransparent (name string RVA 0x562EF87 / 0x562F100) [V]

Name string `0xF5342CB` = "FullScreenOverlayTransparent" (28 chars) [V PE byte check]. Builder code [V listing]:
| fst+0x0a | - | [0xF5342CB] | `0x562ef87  lea r9,[0xF5342cb]` | load name-string address | [V] |
| fst+0x0b | - | [0xF5342CB] | `0x562f100  lea r9,[0xF5342cb]` | same string, second declaration site | [V] |
| fst+0x0c | - | - | `0x562ef8e  call 0x9d6d0` / `0x562f107  call 0x9d6d0` | string-copy helper into descriptor | [V] |

Vtable reference: builder builds name-first descriptor object; no installer-vtable store found. Region references `0x562f33f  lea rcx,[0xF25c1f0]` — descriptor vtable 0xF25C1F0 whose slot1 = 0x56B6650 is a clone ctor, not an installer (see reference table).

Slot1 / body: NOT REACHED — no install-vtable -> slot1 `lea r8` -> body chain. [V negative result]

Resource rows: none derived. [V negative result]

## Pass 3 — WaitOnUpscalingOutput (name string RVA 0x562D068) [V]

Name string: `0xF524D34` = "WaitOnUpscalingO..." plus immediate `0x74757074754F676E` = "ngOutput" [V PE byte check]. Builder code [V listing]:
| wuo+0x0 | 16 | [rsi] | `0x562d06f  movups [rsi],xmm0` | store 16B name "WaitOnUpscalingO" at object+0x0 | [V] |
| wuo+0xd | 8 | [rsi+0xd] | `0x562d07c  mov [rsi+0xd],rax` | store "ngOutput" at object+0xd | [V] |
| wuo+0x15 | 1 | [rsi+0x15] | `0x562d080  mov byte ptr [rsi+0x15],0` | null-terminate name | [V] |

Result name = "WaitOnUpscalingOutput" (21 chars) [V].

Pass object + vtable store [V listing]:
| wuo+0x0v | 8 | [rsi] | `0x562d18e  mov [rsi],rax` | STORE vtable pointer 0xF25C610 at pass object +0x0 | [V] |

So pass-object vtable = **0xF25C610** [V]. vtable 0xF25C610 dump [V raw PE read]:
| vt0xF25C610+0x0 | 8 | slot0 = 0x56cb9a0 | clone ctor (`lea rax,[0xF25c610]`/`mov [rdi],rax`) | [V] |
| vt0xF25C610+0x8 | 8 | slot1 = 0x76920 | [V] |

Slot1 of vtable 0xF25C610 [V rdis]:
| wuo+0x8s | - | [eax] | `0x76920  xor eax,eax` | slot1 returns 0 | [V] |
| wuo+0x8sj | - | - | `0x76922  ret` | | [V] |

Conclusion: slot1 = `xor eax,eax; ret`, NOT a `lea r8` installer thunk. No execute body reached via this vtable; no body-level resource rows. [V negative result]

Object field writes after vtable store [V listing] (config fields, not body resources):
| wuo+0x8 | 4 | [rsi+8] | `0x562d191  mov dword ptr [rsi+8],0x3f800000` | write float 1.0 field | [V] |
| wuo+0x1c | 4 | [rsi+0x1c] | `0x562d19e  mov dword ptr [rsi+0x1c],0x3f800000` | write float 1.0 field | [V] |

## Pass 4 — ClearStencil/WaterSurfaceStencil (name string RVA 0x560B04A) [V]

Name string `0xF66C679` = "[ClearStencil][W..." [V PE byte check]. Builder code [V listing]:
| css+0x0 | 16 | [rdi] | `0x560b051  movups [rdi],xmm0` | store name "[ClearStencil][W..." at object+0x0 | [V] |
| css+0x10 | 16 | [rdi+0x10] | `0x560b046  movups [rdi+0x10],xmm0` | store name part at object+0x10 | [V] |
| css+0x1f | 4 | [rdi+0x1f] | `0x560b054  mov dword ptr [rdi+0x1f],0x5d6c6963` | store "]" | [V] |
| css+0x23 | 1 | [rdi+0x23] | `0x560b05b  mov byte ptr [rdi+0x23],0` | null-terminate | [V] |

Result name = "[ClearStencil][WaterSurfaceStencil]" [V].

Declare helper call [V listing]:
| css+0x0h | - | [rbp+0x27a0] | `0x560b077  call 0x56685c0` | helper sub_56685C0 (rcx=ctx, rdx=name object) | [V] |

Vtable reference: inside sub_56685C0, first `lea rax,[rip+vtable]` [V rdis]:
| css+0x0v | - | [rbp+0x140] | `0x566866c  lea rax,[0xF25c520]` | load descriptor vtable address 0xF25C520 | [V] |
| css+0x0vs | - | [rbp+0x140] | `0x5668673  mov [rbp+0x140],rax` | store 0xF25C520 into local descriptor field | [V] |

So ClearStencil/WaterSurfaceStencil uses descriptor vtable **0xF25C520** [V]. vtable 0xF25C520 dump [V raw PE read]:
| vt0xF25C520+0x8 | 8 | slot1 = 0x56c7360 | [V] |

Slot1 of vtable 0xF25C520 [V rdis]:
| css+0x8s | - | [rax] | `0x56c7363  lea rdx,[0xF25c520]` | slot1 loads SAME vtable (self-reference) | [V] |
| css+0x8ss | - | [rax] | `0x56c736a  mov [rax],rdx` | store vtable into cloned object | [V] |

Conclusion: slot1 = self-referencing clone ctor, NOT a `lea r8` installer thunk. No execute body reached; no body-level resource rows. [V negative result]

Resource rows: none derived. [V negative result]

## Pass 5 — ClearGBuffer/ScenePrepass (name string RVA 0x55FF65B) [V]

Name string `0xF640F15` = "[ClearGBuffer][ScenePrepass]" [V PE byte check]. Builder code [V listing]:
| cgb+0x0 | 16 | [rdi] | `0x55ff662  movups [rdi],xmm0` | store name "[ClearGBuffer]" at object+0x0 | [V] |
| cgb+0xc | 16 | [rdi+0xc] | `0x55ff657  movups [rdi+0xc],xmm0` | store name part at object+0xc | [V] |
| cgb+0x1c | 1 | [rdi+0x1c] | `0x55ff665  mov byte ptr [rdi+0x1c],0` | null-terminate | [V] |

Result name = "[ClearGBuffer][ScenePrepass]" [V].

Declare helper call [V listing]:
| cgb+0x0h | - | [rbp+0x27a0] | `0x55ff6a5  call 0x56a8bb0` | helper sub_56A8BB0 (rcx=ctx, rdx=name object) | [V] |

Vtable reference: inside sub_56A8BB0, first `lea rax,[rip+vtable]` [V rdis]:
| cgb+0x0v | - | [rbp+0x280] | `0x56a8f0d  lea rcx,[0xF25bee0]` | load descriptor vtable address 0xF25BEE0 | [V] |
| cgb+0x0vs | - | [rbp+0x280] | `0x56a8f14  mov [rbp+0x280],rcx` | store 0xF25BEE0 into local descriptor field | [V] |

So ClearGBuffer/ScenePrepass uses descriptor vtable **0xF25BEE0** [V]. vtable 0xF25BEE0 dump [V raw PE read]:
| vt0xF25BEE0+0x0 | 8 | slot0 = 0x56ad460 | clone ctor | [V] |
| vt0xF25BEE0+0x8 | 8 | slot1 = 0x56ad630 | clone ctor | [V] |

Slot1 of vtable 0xF25BEE0 [V rdis]:
| cgb+0x8s | - | [rax] | `0x56ad633  lea rdx,[0xF25bee0]` | slot1 loads SAME vtable (self-reference) | [V] |
| cgb+0x8ss | - | [rax] | `0x56ad63a  mov [rax],rdx` | store vtable into cloned object | [V] |

Conclusion: slot1 = self-referencing clone ctor, NOT a `lea r8` installer thunk. No execute body reached; no body-level resource rows. [V negative result]

Resource rows: none derived. [V negative result]

## Pass 6 — TransparentDegamma (name string RVA 0x5610E82) [V]

Name string `0xF60D9BC` = "TransparentDegamma" [V PE byte check]. Builder code [V listing]:
| td+0x0x | 16 | [0xF546baa] | `0x56104c0  movups xmm7,[0xF546baa]` | load 16B "RasterizedObject" (task-hint "xmm7=[0xF546BAA]") | [V] |
| td+0x0s | 16 | [rsi] | `0x5610e45  movups [rsi],xmm7` | store loaded bytes into object | [V] |
| td+0x0n | - | [0xF60d9bc] | `0x5610e82  lea r9,[0xF60d9bc]` | load "TransparentDegamma" string address | [V] |
| td+0x0c | - | - | `0x5610e89  call 0x9d6d0` | string-copy helper into descriptor | [V] |

Note: dumping the 16 bytes at 0xF546BAA yields ASCII "RasterizedObject" — it is a NAME string, not a vtable [V PE byte check + rdis].

Declare helper call [V listing]:
| td+0x0h | - | [rbp+0x2ef0] | `0x5610ee1  call 0x56876f0` | helper sub_56876F0 | [V] |

Vtable reference: sub_5684660 (pass-declaration helper for this name region), first `lea rax,[rip+vtable]` [V rdis]:
| td+0x0v | - | [rbp+0x560] | `0x568472e  lea rax,[0xF25b670]` | load descriptor vtable address 0xF25B670 | [V] |
| td+0x0vs | - | [rbp+0x560] | `0x5684735  mov [rbp+0x560],rax` | store 0xF25B670 into local descriptor field | [V] |

So TransparentDegamma uses descriptor vtable **0xF25B670** [V]. vtable 0xF25B670 dump [V raw PE read]:
| vt0xF25B670+0x0 | 8 | slot0 = 0x5690930 | clone ctor | [V] |
| vt0xF25B670+0x8 | 8 | slot1 = 0x5690930 | clone ctor | [V] |

Slot1 of vtable 0xF25B670 [V rdis]:
| td+0x8s | - | [rax] | `0x5690933  lea rdx,[0xF25b670]` | slot1 loads SAME vtable (self-reference) | [V] |
| td+0x8ss | - | [rax] | `0x569093a  mov [rax],rdx` | store vtable into cloned object | [V] |

Conclusion: slot1 = self-referencing clone ctor, NOT a `lea r8` installer thunk. No execute body reached; no body-level resource rows. [V negative result]

Resource rows: none derived. [V negative result]

## Reference table — slot1 of every vtable referenced by the 6 pending passes

| pass | vtable RVA | how located | slot1 RVA | slot1 is `lea r8` installer? | execute body |
|---|---|---|---|---|---|
| FullScreenOverlayObjects | - | none (name-only descriptor) | - | no | not found |
| FullScreenOverlayTransparent | 0xF25C1F0 | `0x562f33f  lea rcx,[0xF25c1f0]` | 0x56b6650 | no (clone ctor) | not found |
| WaitOnUpscalingOutput | 0xF25C610 | `0x562d187 lea rax,[0xF25c610]` / `0x562d18e mov [rsi],rax` | 0x76920 | no (`xor eax,eax;ret`) | not found |
| ClearStencil/WaterSurfaceStencil | 0xF25C520 | `0x566866c lea rax,[0xF25c520]` | 0x56c7360 | no (clone ctor) | not found |
| ClearGBuffer/ScenePrepass | 0xF25BEE0 | `0x56a8f0d lea rcx,[0xF25bee0]` | 0x56ad630 | no (clone ctor) | not found |
| TransparentDegamma | 0xF25B670 | `0x568472e lea rax,[0xF25b670]` | 0x5690930 | no (clone ctor) | not found |

Contrast: done-pass installer vtable 0xF25C790 -> slot1 `0x568ba60  lea r8,[0x568bcd0]` -> body 0x568BCD0 [V]. None of the 6 pending passes install such a vtable: their builder-installed vtables are descriptor vtables (slot0/slot1 = self-referencing clone ctor, or slot1 = return 0).

## Resource rows

No execute body was located for any of the 6 pending passes, so no body-level resource reads/writes could be derived. The only verified memory accesses are the descriptor/object field writes listed per pass above (name stores, vtable-pointer stores, float-field stores), all [V]. Named in/out resources (textures/render targets read or written by the pass bodies) are not statically decodable from the builder.

## CLOSES?
NO — blocking fact: for all 6 pending passes the builder installs a DESCRIPTOR vtable (0xF25C1F0, 0xF25C610, 0xF25C520, 0xF25BEE0, 0xF25B670) whose slot1 is a self-referencing clone ctor or `xor eax,eax;ret` (verified by raw vtable dump + rdis disassembly), NOT the `lea r8` installer thunk that tail-jumps 0xBC61560 to an execute body (that chain exists only for the 6 already-done passes, e.g. vtable 0xF25C790 -> body 0x568BCD0). Therefore no execute body and no body-level resource reads/writes are statically reachable for these 6 passes, so not all 12 passes have [V] resource rows. Resolving this requires the frame-graph pass-task construction (0xc273420 / task dispatch 0xe9002e0), outside the builder-helper method.

## TOOL REQUESTS
- None
