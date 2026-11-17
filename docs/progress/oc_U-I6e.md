## NEXT: 0xbc864df - End of SSR module body (sub_bc82ad0) ANALYSIS COMPLETE

# UNIT U-I6e: SSR module body sub_bc82ad0 [0xbc82ad0..0xbc864df)

Checklist I6d in docs/RENDER_CHECKLIST.md; strings/sites in docs/progress/oc_U-I6c.md.

---

## Phase Table (instruction-complete, from docs/listings/L_bc82ad0.txt)

| Range | Description |
|---|---|
| 0xbc82ad0..0xbc82c2c | Prologue: push rbp/r15-r12/rsi/rdi/rbx, sub rsp 0x938, set rbp=rsp+0x80, save xmm6-xmm15 to [rbp+0x810..0x8A0], init guard [rbp+0x808]=-2, save args: r9->r14, r8->[rbp+0x768], rdx->[rbp+0x760], rcx->[rbp+0x670] |
| 0xbc82c2d..0xbc82d1c | ScreenSpaceReflections binding: load string "ScreenSpaceReflections" (0xF54E7B3) to [rbp+0x6B0], len 0x16 to [rbp+0x6B8], setup args for 0x567C8B0 call at 0xbc82c6c (r8=0x12AE1988, rdx=[rbp+0x770]), then refcount inc/dec on returned objects via [0xF99FFA0] thunk |
| 0xbc82d1c..0xbc82e43 | Version/feature gate chain: 10 sequential cmp/jg checks (0xbc82d1c, 0xbc82d41, 0xbc82d66, 0xbc82d8b, 0xbc82db0, 0xbc82dd5, 0xbc82dfa, 0xbc82e1f, 0xbc82e44, 0xbc8319f) reading globals at 0x12AE19A8..0x12AE1A28 via TLS slot [0x128767C8], each jumping to cold registration blocks at 0xBC84D0D..0xBC8509D |
| 0xbc82e44..0xbc8319e | Parameter load from input structs: r14 (SSR config) fields at +8,+0x10,+0xC,+0x18,+0x20,+0x40,+0x24,+0x50 -> [rbp+0x450,0x440,0x460,0x470,0x664,0x668,0x300,0x668]; rbx (camera/view) matrices at +0x18..+0x88 -> [rbp+0x430,0x4A0..0x4D0]; call 0xAB49C0 at 0xbc82ed4 with [rbp+0x4A0] |
| 0xbc831a5..0xbc833d2 | More version gates (6 checks: 0x12AE1A28..0x12AE1A78) + setup of descriptor arrays at [rbp+0x3D8..0x3FA, 0x328..0x372] from stack args [rbp+0x968..0x980] and globals 0x12AE1A40..0x12AE1A70; conditional call 0x56BA620 at 0xbc8337f if byte at [rbp+0x980+0x10]==1 |
| 0xbc833d3..0xbc834b7 | Resource binding sequence: init [rbp+0x484..0x498], call 0x5698290 twice (0xbc83433, 0xbc83466), call 0x56BA620 at 0xbc83499, store results to [rbp+0x670] (output context), load [rbp+0x690+0x18] -> [rbp+0x6B0], call 0xE86B370 at 0xbc834e8 |
| 0xbc834ee..0xbc837a0 | Shader parameter math: divss/mulss on xmm11,xmm8 at 0xbc834ef-0xbc8351b; three nearly identical resource lookup loops (0xbc83547-0xbc835bd, 0xbc835be-0xbc8367d, 0xbc8367e-0xbc8378d) each calling 0x5679DB0 with computed indices; SSE vector ops 0xbc83691-0xbc83706 computing screen-space coords into [rbp+0x770..0x77C] |
| 0xbc837a1..0xbc83f60 | Descriptor array population: five resource slots loaded from [rbp+0x930,0x940,0x938,0x300,0x940] into [rbp+0x770..0x7B8] with 0x5679DB0 calls; final setup for 0xBC88560 call at 0xbc83f52 with 10 stack args (pass descriptors, textures, samplers) |
| 0xbc83f61..0xbc843cb | Main SSR pass execution: call 0xBC88560 at 0xbc83f52; string buffer grow check 0xbc83f69-0xbc83fa7 calling 0xE935700; conditional FSR/DLSS path (byte [r14+0x3C]==1) at 0xbc83fac-0xbc843cb with two nearly identical blocks (0xbc83fb2-0xbc841ab and 0xbc841f0-0xbc843cb) each allocating string "FillGaps" / "GappedFill", calling 0xBC8A240, then buffer grow check |
| 0xbc843cc..0xbc84a53 | SSRGetReflectedColor pass: alloc string "SSRGetReflectedColor" (0xF563D37) at 0xbc847d3, copy matrices from rbx/r14 to [rbp+0x160..0x274], pack handle bits at 0xbc84835-0xbc8486c, call 0xBC88560 at 0xbc849ed, buffer grow check 0xbc84a0f-0xbc84a54 |
| 0xbc84a54..0xbc84b34 | Epilogue/refcount cleanup: dec refs on [rbp+0x698] and [rbp+0x980+8] via [0xF99FFA0] thunk; restore xmm6-xmm15, add rsp 0x938, pop rbx/rdi/rsi/r12-r15/rbp, ret |
| 0xbc84b35..0xbc8558a | Cold registration blocks (18x): each checks a global at 0x12AE18D8..0x12AE1B50 for 0xFFFFFFFF, if so calls 0xE938CB0, then registers a pass/uniform via 0x76AD00 (passes: SSRRayMarch 0xbc84b86, SSRRayMarchHZB 0xbc84bda, SSRFillGaps 0xbc84c2e, SSRGetReflectedColor 0xbc84c82) or 0x79580 (uniforms: SSRTemporalAccumulationParams 0xbc84d2d, SSRFadingParamsAndThickness 0xbc84d98, SSRRoughnessCutoffParams 0xbc84e0a, plus 14 more), each followed by 0xE935740 (pass body) and 0xE938D70 (cleanup), then jmp back to main flow |
| 0xbc8558b..0xbc864df | FNV-1a hash computation + uniform registration fallback: 12 identical hash loops (0xbc85857-0xbc858db, 0xbc858ff-0xbc85983, ..., 0xbc86449-0xbc864bb) computing FNV-1a of strings at [rbp+0x4A0/0x6B0/0x770] into globals 0x12AE19A0..0x12AE1AC0, calling 0x73150 and 0xE938D70, then jmp back to main flow; final alloc/registration at 0xbc8558b-0xbc85735 for "ExtendFillGaps"/"DownsampleGappedFill" calling 0x7D7890, 0x9B250, 0xE935740 |

---

## Strings Referenced (RVA, text, site, callee after)

| String RVA | Text | Referencing Instruction (site) | Callee After |
|---|---|---|---|
| 0xF54E7B3 | "ScreenSpaceReflections" | 0xbc82c2d lea rax,[0xF54E7B3] | 0x567C8B0 (0xbc82c6c) |
| 0xF5B111F | "SSRRayMarch" | 0xbc84b7c lea r8,[0xF5B111F] | 0x76AD00 (0xbc84b86) |
| 0xF7CE38A | "SSRRayMarchHZB" | 0xbc84bd0 lea r8,[0xF7CE38A] | 0x76AD00 (0xbc84bda) |
| 0xF54C98F | "SSRFillGaps" | 0xbc84c1d lea r8,[0xF54C98F] | 0x76AD00 (0xbc84c2e) |
| 0xF563D37 | "SSRGetReflectedColor" | 0xbc84c71 lea r8,[0xF563D37] | 0x76AD00 (0xbc84c82) |
| 0xF550D9E | "SSRRayMarchingParams" | 0xbc84d2d lea rdx,[0xF550D9E] | 0x79580 (0xbc84d37) |
| 0xF547C22 | "SSRFadingParamsAndThickness" | 0xbc84d98 lea rdx,[0xF547C22] | 0x79580 (0xbc84da9) |
| 0xF550DB3 | "SSRRoughnessCutoffParams" | 0xbc84e0a lea rdx,[0xF550DB3] | 0x79580 (0xbc84e1b) |
| 0xF550D40 | "SSRTemporalAccumulationParams" | 0xbc84e7c lea rdx,[0xF550D40] | 0x79580 (0xbc84e8d) |
| 0xF544CBC | (unidentified, likely SSR uniform) | 0xbc84eee lea rdx,[0xF544CBC] | 0x79580 (0xbc84eff) |
| 0xF5BBFAF | (unidentified, likely SSR uniform) | 0xbc84f60 lea rdx,[0xF5BBFAF] | 0x79580 (0xbc84f71) |
| 0xF60CFD8 | (unidentified, likely SSR uniform) | 0xbc84fd2 lea rdx,[0xF60CFD8] | 0x79580 (0xbc84fe3) |
| 0xF5DE7ED | (unidentified, likely SSR uniform) | 0xbc85044 lea rdx,[0xF5DE7ED] | 0x79580 (0xbc85055) |
| 0xF5639F3 | (unidentified, likely SSR uniform) | 0xbc85128 lea rdx,[0xF5639F3] | 0x79580 (0xbc85139) |
| 0xF5ADE08 | (unidentified, likely SSR uniform) | 0xbc8519a lea rdx,[0xF5ADE08] | 0x79580 (0xbc851ab) |
| 0xF5A62A0 | (unidentified, likely SSR uniform) | 0xbc8520c lea rdx,[0xF5A62A0] | 0x79580 (0xbc8521d) |
| 0xF547D3A | (unidentified, likely SSR uniform) | 0xbc8527e lea rdx,[0xF547D3A] | 0x79580 (0xbc8528f) |
| 0xF56EC49 | (unidentified, likely SSR uniform) | 0xbc852f0 lea rdx,[0xF56EC49] | 0x79580 (0xbc85301) |
| 0xF7E41CA | (unidentified, likely tonemap uniform) | 0xbc85362 lea rdx,[0xF7E41CA] | 0x79580 (0xbc85373) |
| 0xF56ECF5 | (unidentified, likely SSR uniform) | 0xbc853d1 lea rdx,[0xF56ECF5] | 0x79580 (0xbc853e2) |
| 0xF54F41B | (unidentified, likely SSR uniform) | 0xbc85443 lea rdx,[0xF54F41B] | 0x79580 (0xbc85454) |
| 0xF530C94 | (unidentified, likely SSR uniform) | 0xbc854b5 lea rdx,[0xF530C94] | 0x79580 (0xbc854c6) |
| 0xF53C810 | (unidentified, likely SSR uniform) | 0xbc85527 lea rdx,[0xF53C810] | 0x79580 (0xbc85538) |
| 0xF5A15B7 | "FillGaps" | 0xbc8414b movups xmm0,[0xF5A15B7] | 0xBC8A240 (0xbc841a5) |
| 0xF563D37 | "SSRGetReflectedColor" | 0xbc847d3 movups xmm0,[0xF563D37] | 0xBC88560 (0xbc849ed) |
| 0xF5BAC48 | "ExtendFillGaps" (partial) | 0xbc85625 movzx eax,word ptr [0xF5BAC48] | 0x7D7890 (0xbc8567b) |
| 0xF5BAC4A | (continuation) | 0xbc85636 movzx eax,byte ptr [0xF5BAC4A] | 0x7D7890 (0xbc8567b) |

---

## Callees in Order (direct calls only, from listing)

| RVA | Function | Context |
|---|---|---|
| 0x567C8B0 | Uniform/parameter binding helper | ScreenSpaceReflections setup |
| 0xF99FFA0 | Refcount thunk (via [0xF99FFA0]) | Multiple: inc/dec on returned objects |
| 0xAB49C0 | Unknown (matrix/compute helper) | Called with [rbp+0x4A0] |
| 0x56BA620 | Resource binding / descriptor helper | Called 3x: 0xbc8337f, 0xbc83499, 0xbc840f1 |
| 0x5698290 | Resource binding variant | Called 2x: 0xbc83433, 0xbc83466 |
| 0xE86B370 | Shader resource binding | Called 4x: 0xbc834e8, 0xbc84049, 0xbc8425b, 0xbc8453f |
| 0x5679DB0 | Descriptor table update | Called 9x in loops: 0xbc835b8, 0xbc83678, 0xbc83788, 0xbc838e8, 0xbc839ac, 0xbc83a54, 0xbc840f1, 0xbc842fe, 0xbc845f8 |
| 0xBC88560 | SSR pass execute / draw submission | Called 2x: 0xbc83f52, 0xbc849ed |
| 0xE935700 | String buffer grow | Called 4x: 0xbc83fa2, 0xbc841eb, 0xbc843c7, 0xbc84a4f |
| 0xBC8A240 | FSR/DLSS pass setup | Called 2x: 0xbc841a5, 0xbc84381 |
| 0xE935740 | Pass body registration | Called 20+ times in cold blocks |
| 0xE938D70 | Pass cleanup / finalize | Called 20+ times in cold blocks |
| 0xE938CB0 | Pass/uniform initialization check | Called 18x in cold blocks |
| 0x76AD00 | Pass registration with hash | Called 4x: SSRRayMarch, SSRRayMarchHZB, SSRFillGaps, SSRGetReflectedColor |
| 0x79580 | Uniform registration helper | Called 22x for SSR/tonemap uniforms |
| 0x73150 | String hash / uniform finalize | Called 12x in FNV-1a fallback blocks |
| 0x7D7890 | String allocation / registration | Called 2x: 0xbc8567b, 0xbc856ff |
| 0x9B250 | String buffer finalize | Called 2x: 0xbc8570c, 0xbc85718 |
| 0x9BC830 | Error / allocation failure handler | Called 2x: 0xbc84b3a, 0xbc84b4a |

---

## [reg+off] Reads/Writes into Output/Description Objects

| Offset (from base) | Size | Direction | First Site (RVA) | Meaning (if visible) | Base Register |
|---|---|---|---|---|---|
| [rbp+0x670] | 8 | W | 0xbc82b55 | Input context pointer (rcx arg) | rbp |
| [rbp+0x760] | 8 | W | 0xbc82b55 | Input rdx (SSR config ptr?) | rbp |
| [rbp+0x768] | 8 | W | 0xbc82b4e | Input r8 (camera/view ptr?) | rbp |
| [rbp+0x950] | 8 | R | 0xbc82c15 | Stack arg 5 (pass descriptor?) | rbp |
| [rbp+0x948] | 8 | R | 0xbc82c1c | Stack arg 4 | rbp |
| [rbp+0x6B0] | 8 | W | 0xbc82c34 | "ScreenSpaceReflections" string ptr | rbp |
| [rbp+0x6B8] | 8 | W | 0xbc82c3b | String length (0x16) | rbp |
| [rbp+0x770] | 16 | W | 0xbc82c65 | Output of 0x567C8B0 (uniform handle?) | rbp |
| [rbp+0x690] | 16 | W | 0xbc82c79 | Copied from [rax] (bound resource) | rbp |
| [rbp+0x698] | 8 | W | 0xbc82c8d | Refcounted object pointer | rbp |
| [rbp+0x450] | 4 | W | 0xbc82e54 | SSR config float (from r14+8) | rbp |
| [rbp+0x440] | 8 | W | 0xbc82e62 | SSR config double (from r14+0x10) | rbp |
| [rbp+0x460] | 4 | W | 0xbc82e72 | SSR config float (from r14+0xC) | rbp |
| [rbp+0x470] | 8 | W | 0xbc82e80 | SSR config double (from r14+0x18) | rbp |
| [rbp+0x664] | 4 | W | 0xbc82e8d | SSR config float (from r14+0x20) | rbp |
| [rbp+0x668] | 4 | W | 0xbc82e9b | SSR config float (from r14+0x40) | rbp |
| [rbp+0x300] | 8 | W | 0xbc82ea9 | SSR config double (from r14+0x24) | rbp |
| [rbp+0x430] | 4 | W | 0xbc82eb9 | Camera param (from rbx+0x18) | rbp |
| [rbp+0x4A0] | 16 | W | 0xbc8309f | View matrix row 0 (from rbx+0x58) | rbp |
| [rbp+0x4B0] | 16 | W | 0xbc830aa | View matrix row 1 (from rbx+0x68) | rbp |
| [rbp+0x4C0] | 16 | W | 0xbc830b5 | View matrix row 2 (from rbx+0x78) | rbp |
| [rbp+0x4D0] | 16 | W | 0xbc830c3 | View matrix row 3 (from rbx+0x88) | rbp |
| [rbp+0x4E0] | 16 | W | 0xbc830ce | Proj matrix row 0 (from rbx+0x18) | rbp |
| [rbp+0x4F0] | 16 | W | 0xbc830fc | Proj matrix row 1 (from rbx+0x28) | rbp |
| [rbp+0x500] | 16 | W | 0xbc83103 | Proj matrix row 2 (from rbx+0x38) | rbp |
| [rbp+0x510] | 16 | W | 0xbc8310e | Proj matrix row 3 (from rbx+0x48) | rbp |
| [rbp+0x3D8] | 8 | W | 0xbc83292 | Descriptor ptr (from 0x12AE1A40) | rbp |
| [rbp+0x328] | 8 | W | 0xbc832d9 | Descriptor ptr (from 0x12AE1A50) | rbp |
| [rbp+0x340] | 8 | W | 0xbc832fd | Descriptor ptr (from [rdx+8]) | rbp |
| [rbp+0x350] | 8 | W | 0xbc8330b | Descriptor ptr (from 0x12AE1A60) | rbp |
| [rbp+0x368] | 8 | W | 0xbc83336 | Descriptor ptr (from [rcx+8]) | rbp |
| [rbp+0x6B0] | 8 | W | 0xbc834c6 | Re-written: resource from [rbp+0x690+0x18] | rbp |
| [rbp+0x484] | 4 | W | 0xbc833eb | Computed shader param (divss/mulss result) | rbp |
| [rbp+0x770..0x77C] | 16 | W | 0xbc83534 | Computed screen-space coords (xmm11) | rbp |
| [rbp+0x7B0] | 8 | W | 0xbc83532 | Descriptor count (1) | rbp |
| [rbp+0x7B8] | 8 | W | 0xbc83539 | Ptr to [rbp+0x770] | rbp |
| [rbp+0x7E0] | 2 | W | 0xbc83598 | Computed resource index | rbp |
| [rbp+0x7E2] | 1 | W | 0xbc835a0 | Index valid flag | rbp |
| [rbp+0x388] | 8 | W | 0xbc83385 | Resource handle from 0x56BA620 | rbp |
| [rbp+0x400] | 8 | W | 0xbc8347a | Resource handle from 0x5698290 | rbp |
| [rbp+0x418] | 8 | W | 0xbc83440 | Resource handle from 0x5698290 | rbp |
| [rbp+0x670] | 16 | W | 0xbc834ad | Output context written (rcx, rax) | rbp |
| [rbp+0x690] | 8 | W | 0xbc834c3 | Re-read resource ptr | rbp |
| [rbp+0x730] | 8 | W | 0xbc83503 | Resource ptr copy | rbp |
| [rbp+0x160..0x274] | 200+ | W | 0xbc847f3 | SSRGetReflectedColor pass descriptor (matrices, handle bits, params) | rbp |
| [rbp+0x6B0] | 8 | W | 0xbc84027 | Re-written for 2nd pass | rbp |
| [rbp+0x6B8] | 8 | W | 0xbc84035 | Arg for 0xE86B370 | rbp |
| [rbp+0x7B0..0x7BF] | 16 | W | 0xbc84065 | Pass descriptor for 2nd 0xBC88560 | rbp |

---

## Gaps / UNVERIFIED

- [UNVERIFIED: 0xbc82ed4] Exact purpose of 0xAB49C0 call with [rbp+0x4A0] - matrix transform?
- [UNVERIFIED: 0xbc834e8] 0xE86B370 argument mapping - shader binding layout?
- [UNVERIFIED: 0xbc83f52] 0xBC88560 stack argument layout (10 args at rsp+0x20..0x58) - full descriptor structure?
- [UNVERIFIED: 0xbc849ed] 0xBC88560 second call argument layout - SSRGetReflectedColor pass?
- [UNVERIFIED: 0xbc841a5] 0xBC8A240 argument layout - FSR/DLSS pass setup?
- [UNVERIFIED: 0xF544CBC..0xF53C810] 14 uniform string texts in cold blocks - not cross-referenced to known uniform names
- [UNVERIFIED: 0x12AE18D8..0x12AE1B50] Global version/feature flags - exact meaning per offset
- [UNVERIFIED: 0xF99FFA0] Thunk target - resolves to 0xEEA6040 (refcount dec) but CFG jmp obscures
- [UNVERIFIED: r14/rbx input struct layouts] Offsets +8,+0x10,+0xC,+0x18,+0x20,+0x40,+0x24,+0x50 and rbx+0x18..+0x88 meanings inferred only

---

## TOOL REQUESTS

1. **structure_analyzer** | input: listing file + known offsets -> output: C struct definitions for r14 (SSRConfig), rbx (CameraView), rbp frame layout | would replace manual offset tracking across 3000+ lines
2. **cold_block_summarizer** | input: listing ranges 0xbc84b35-0xbc8558a, 0xbc8558b-0xbc864df -> output: unified table of all cold registration blocks with string, hash, target global, callee sequence | 36 near-identical blocks analyzed by hand
3. **string_resolver** | input: string RVAs from listing (0xF544CBC..0xF53C810) -> output: actual string texts | currently "unidentified" for 14 uniforms; need exe string dump
## ORCHESTRATOR: resolved the 14 "unidentified" uniform strings (read from the exe file bytes at the RVA, 2026-11-16)
0xF544CBC UnitPlaneExtents | 0xF5BBFAF ScreenSize | 0xF60CFD8 CameraData | 0xF5DE7ED ViewportScale | 0xF5639F3 RasterColor | 0xF5ADE08 GbufferDepth | 0xF5A62A0 GbufferNormal | 0xF547D3A GbufferRoughness | 0xF56EC49 PreviousReflectionBuffer | 0xF7E41CA Color0 | 0xF56ECF5 HiZBuffer | 0xF54F41B HiZViewportDimensionsAndBufferDimensions | 0xF530C94 HiZMipCount | 0xF53C810 ScreenSpaceRayOffset
(sites are the `lea rdx,[..]` listed above, each followed by the 0x79580 uniform registration call.)
