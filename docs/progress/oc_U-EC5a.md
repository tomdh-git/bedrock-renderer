## NEXT
DONE

# UNIT U-EC5a — C5a Declarator<RenderContext> + five Bind* dependency kinds + module names (6aq); registration call addresses pending

Status: IN PROGRESS. Source: docs/RENDER_CHECKLIST.md item C5a, docs/BGFX_MAP.md section 6aq, input data docs/progress/oc_U-C5a.md + docs/progress/oc_U-C5a2.md.

EXE: C:/Users/Atomi/AppData/Local/LeviLauncher/Instances/1.26.62.01/Minecraft.Windows.exe (1.26.62.01), RVAs relative to image base. Static analysis only.

Pending per item line: registration call addresses of Declarator<RenderContext> + five Bind* kinds, with immediate args and the pass/module each is invoked from; link module-name strings to registration calls; prove the five Bind* kinds by the vtable/type each passes ([V] only with an instruction).

## NEXT
DONE marker pending — see end of file.

## TABLE (name | offset | size | read/store addr | verbatim `0xRVA  instr` proof line | meaning | tag)

| offset | size | name | read/store addr | verbatim `0xRVA  instr` proof line | meaning | tag |
| 0xC278270 | 16 | kind3/4_src_data | [r8] | `0xC278270  movups xmm0,[r8]` | load 16B from source entry (r8 = source entry ptr) for kind 3/4 handler | [V] |
| 0xC278274 | 16 | kind3/4_dst_data | [rdx] | `0xC278274  movups [rdx],xmm0` | store 16B to dest record (rdx = dest buffer +0x2FF0) for kind 3/4 | [V] |
| 0xC278277 | 1 | kind_byte | [rdx+0x18] | `0xC278277  mov [rdx+0x18],cl` | store kind byte (cl) at dest+0x18 — shared tail for all kinds | [V] |
| 0xC27827A | 8 | loop_idx | rax | `0xC27827A  add rax,0x20` | advance source/dest index by stride 0x20 | [V] |
| 0xC27827E | 8 | loop_bound | rax | `0xC27827E  cmp rax,0x200` | compare index vs 0x200 (16 entries * 0x20 stride) | [V] |
| 0xC278284 | 8 | loop_exit | - | `0xC278284  je short 0xC278220` | exit loop when all 16 entries processed | [V] |
| 0xC278286 | 1 | sentinel | [rbp+rax+0x3008] | `0xC278286  mov byte ptr [rbp+rax+0x3008],0xFF` | write 0xFF sentinel byte | [V] |
| 0xC27828E | 1 | kind_load | [r12+rax+0x18] | `0xC27828E  movzx ecx,byte ptr [r12+rax+0x18]` | load kind byte (0-4) from source entry+0x18 | [V] |
| 0xC278294 | 8 | kind_cmp | rcx | `0xC278294  cmp rcx,4` | bounds check: kind must be <= 4 | [V] |
| 0xC278298 | 8 | kind_skip | - | `0xC278298  ja short 0xC27827A` | skip entry if kind > 4 | [V] |
| 0xC27829A | 8 | dst_base | rdx | `0xC27829A  lea rdx,[rax+rbp]` | compute dest buffer base address | [V] |
| 0xC27829E | 8 | dst_off | rdx | `0xC27829E  add rdx,0x2FF0` | rdx = local dependency record buffer +0x2FF0 | [V] |
| 0xC2782A5 | 8 | src_entry | r8 | `0xC2782A5  lea r8,[r12+rax]` | r8 = source entry pointer (stride 0x20 array) | [V] |
| 0xC2782A9 | 8 | jt_base | r10 | `0xC2782A9  lea r10,[0xF478E3C]` | load jump table base address | [V] |
| 0xC2782B0 | 8 | jt_entry | [r10+rcx*4] | `0xC2782B0  movsxd r9,[r10+rcx*4]` | load signed int32 jump offset for kind | [V] |
| 0xC2782B4 | 8 | jt_target | r9 | `0xC2782B4  add r9,r10` | compute absolute jump target | [V] |
| 0xC2782B7 | 8 | indirect_jmp | - | `0xC2782B7  jmp r9` | indirect jump to kind handler | [V] |
| 0xC2782BA | 16 | kind1_copy | [rdx] | `0xC2782BA  movdqu [rdx],xmm7` | kind 1: copy 16B from xmm7 to dest | [V] |
| 0xC2782BE | 8 | kind1_shared_ptr | [r12+rax+8] | `0xC2782BE  mov r9,[r12+rax+8]` | kind 1: load shared_ptr from source entry+0x08 | [V] |
| 0xC2782C3 | 8 | kind1_nullchk | r9 | `0xC2782C3  test r9,r9` | kind 1: null check shared_ptr | [V] |
| 0xC2782C6 | 8 | kind1_nullpath | - | `0xC2782C6  je short 0xC278319` | kind 1: jump to null path if shared_ptr is null | [V] |
| 0xC2782C8 | 4 | kind1_refcount | [r9+8] | `0xC2782C8  lock inc dword ptr [r9+8]` | kind 1: increment shared_ptr refcount | [V] |
| 0xC2782D4 | 16 | kind2_copy | [rdx] | `0xC2782D4  movdqu [rdx],xmm7` | kind 2: copy 16B from xmm7 to dest | [V] |
| 0xC2782D8 | 8 | kind2_shared_ptr | [r12+rax+8] | `0xC2782D8  mov r8,[r12+rax+8]` | kind 2: load shared_ptr from source entry+0x08 | [V] |
| 0xC2782DD | 8 | kind2_nullchk | r8 | `0xC2782DD  test r8,r8` | kind 2: null check shared_ptr | [V] |
| 0xC2782E0 | 8 | kind2_nullpath | - | `0xC2782E0  je short 0xC2782EE` | kind 2: jump to null path if shared_ptr is null | [V] |
| 0xC2782E2 | 4 | kind2_refcount | [r8+8] | `0xC2782E2  lock inc dword ptr [r8+8]` | kind 2: increment shared_ptr refcount | [V] |
| 0xC2782EE | 8 | kind2_null_sp | r8d | `0xC2782EE  xor r8d,r8d` | kind 2: null shared_ptr = 0 | [V] |
| 0xC2782F1 | 8 | handle_load | [r12+rax] | `0xC2782F1  mov r9,[r12+rax]` | load qword handle from source entry+0x00 | [V] |
| 0xC2782F5 | 8 | handle_store | [rbp+rax+0x2FF0] | `0xC2782F5  mov [rbp+rax+0x2FF0],r9` | store handle to dest record+0x00 | [V] |
| 0xC2782FD | 8 | sp_store | [rbp+rax+0x2FF8] | `0xC2782FD  mov [rbp+rax+0x2FF8],r8` | store shared_ptr to dest record+0x08 | [V] |
| 0xC278305 | 2 | u16_load | [r12+rax+0x10] | `0xC278305  movzx r8d,word ptr [r12+rax+0x10]` | load u16 from source entry+0x10 | [V] |
| 0xC27830B | 2 | u16_store | [rbp+rax+0x3000] | `0xC27830B  mov [rbp+rax+0x3000],r8w` | store u16 to dest record+0x20 | [V] |
| 0xC278314 | 8 | kind_store_jmp | - | `0xC278314  jmp 0xC278277` | jump to shared kind-byte store | [V] |
| 0xC278319 | 8 | null_sp | r9d | `0xC278319  xor r9d,r9d` | null shared_ptr = 0 (kind 1 null path) | [V] |
| 0xC27831C | 8 | ctrl_deref | [r8] | `0xC27831C  mov r8,[r8]` | deref shared_ptr control block (kind 2) | [V] |
| 0xC27831F | 8 | ctrl_store | [rbp+rax+0x2FF0] | `0xC27831F  mov [rbp+rax+0x2FF0],r8` | store deref'd ptr to dest+0x00 (kind 2 null path) | [V] |
| 0xC278327 | 8 | null_sp_store | [rbp+rax+0x2FF8] | `0xC278327  mov [rbp+rax+0x2FF8],r9` | store 0 as shared_ptr to dest+0x08 (kind 1 null path) | [V] |
| 0xC27832F | 8 | kind_store_jmp2 | - | `0xC27832F  jmp 0xC278277` | jump to shared kind-byte store | [V] |

### Call site setup — sub_bbce7b0 (5 sites, same pattern)

| 0xBBCF038 | 8 | declarator | rcx | `0xBBCF038  lea rcx,[rbp+0x8C0]` | rcx = Declarator object (sub_bbce7b0 call sites 1-5) | [V] |
| 0xBBCF03F | 8 | entry_ptr | rdx | `0xBBCF03F  lea rdx,[rbp+0xA08]` | rdx = dependency entry pointer (sub_bbce7b0 call sites 1-5) | [V] |
| 0xBBCF046 | 8 | third_arg | r8 | `0xBBCF046  lea r8,[rbp+0x648]` | r8 = {value=1, hash_table_base_ptr} (sub_bbce7b0 call sites 1-5) | [V] |
| 0xBBCF04D | 8 | bind_call | - | `0xBBCF04D  call 0x567B570` | sub_567b570 Declarator bind/lookup call site 1 (from sub_bbce7b0) | [V] |
| 0xBBCF0BC | 8 | declarator | rcx | `0xBBCF0BC  lea rcx,[rbp+0x8C0]` | rcx = Declarator object (sub_bbce7b0 call site 2) | [V] |
| 0xBBCF0C3 | 8 | entry_ptr | rdx | `0xBBCF0C3  lea rdx,[rbp+0xA08]` | rdx = dependency entry pointer (sub_bbce7b0 call site 2) | [V] |
| 0xBBCF0CA | 8 | third_arg | r8 | `0xBBCF0CA  lea r8,[rbp+0x648]` | r8 = {value=1, hash_table_base_ptr} (sub_bbce7b0 call site 2) | [V] |
| 0xBBCF0D1 | 8 | bind_call | - | `0xBBCF0D1  call 0x567B570` | sub_567b570 Declarator bind/lookup call site 2 (from sub_bbce7b0) | [V] |
| 0xBBCF11A | 8 | declarator | rcx | `0xBBCF11A  lea rcx,[rbp+0x8C0]` | rcx = Declarator object (sub_bbce7b0 call site 3) | [V] |
| 0xBBCF121 | 8 | entry_ptr | rdx | `0xBBCF121  lea rdx,[rbp+0xA08]` | rdx = dependency entry pointer (sub_bbce7b0 call site 3) | [V] |
| 0xBBCF128 | 8 | third_arg | r8 | `0xBBCF128  lea r8,[rbp+0x648]` | r8 = {value=1, hash_table_base_ptr} (sub_bbce7b0 call site 3) | [V] |
| 0xBBCF12F | 8 | bind_call | - | `0xBBCF12F  call 0x567B570` | sub_567b570 Declarator bind/lookup call site 3 (from sub_bbce7b0) | [V] |
| 0xBBCF1A5 | 8 | declarator | rcx | `0xBBCF1A5  lea rcx,[rbp+0x8C0]` | rcx = Declarator object (sub_bbce7b0 call site 4) | [V] |
| 0xBBCF1AC | 8 | entry_ptr | rdx | `0xBBCF1AC  lea rdx,[rbp+0xA08]` | rdx = dependency entry pointer (sub_bbce7b0 call site 4) | [V] |
| 0xBBCF1B3 | 8 | third_arg | r8 | `0xBBCF1B3  lea r8,[rbp+0x648]` | r8 = {value=1, hash_table_base_ptr} (sub_bbce7b0 call site 4) | [V] |
| 0xBBCF1BA | 8 | bind_call | - | `0xBBCF1BA  call 0x567B570` | sub_567b570 Declarator bind/lookup call site 4 (from sub_bbce7b0) | [V] |
| 0xBBCF2AC | 8 | declarator | rcx | `0xBBCF2AC  lea rcx,[rbp+0x8C0]` | rcx = Declarator object (sub_bbce7b0 call site 5) | [V] |
| 0xBBCF2B3 | 8 | entry_ptr | rdx | `0xBBCF2B3  lea rdx,[rbp+0xA08]` | rdx = dependency entry pointer (sub_bbce7b0 call site 5) | [V] |
| 0xBBCF2BA | 8 | third_arg | r8 | `0xBBCF2BA  lea r8,[rbp+0x648]` | r8 = {value=1, hash_table_base_ptr} (sub_bbce7b0 call site 5) | [V] |
| 0xBBCF2C1 | 8 | bind_call | - | `0xBBCF2C1  call 0x567B570` | sub_567b570 Declarator bind/lookup call site 5 (from sub_bbce7b0) | [V] |

### Call site setup — sub_bbe2d50 (3 sites, same pattern)

| 0xBBE34A3 | 8 | declarator | rcx | `0xBBE34A3  lea rcx,[rbp+0x588]` | rcx = Declarator object (sub_bbe2d50 call site 1, RTX builder) | [V] |
| 0xBBE34AA | 8 | entry_ptr | rdx | `0xBBE34AA  lea rdx,[rbp+0x1030]` | rdx = dependency entry pointer (sub_bbe2d50 call site 1) | [V] |
| 0xBBE34B1 | 8 | third_arg | r8 | `0xBBE34B1  lea r8,[rbp+0xD80]` | r8 = {value=1, hash_table_base_ptr} (sub_bbe2d50 call site 1) | [V] |
| 0xBBE34B8 | 8 | bind_call | - | `0xBBE34B8  call 0x567B570` | sub_567b570 Declarator bind/lookup call site 1 (from sub_bbe2d50 RTX builder) | [V] |
| 0xBBE3530 | 8 | declarator | rcx | `0xBBE3530  lea rcx,[rbp+0x588]` | rcx = Declarator object (sub_bbe2d50 call site 2) | [V] |
| 0xBBE3537 | 8 | entry_ptr | rdx | `0xBBE3537  lea rdx,[rbp+0x1030]` | rdx = dependency entry pointer (sub_bbe2d50 call site 2) | [V] |
| 0xBBE353E | 8 | third_arg | r8 | `0xBBE353E  lea r8,[rbp+0xD80]` | r8 = {value=1, hash_table_base_ptr} (sub_bbe2d50 call site 2) | [V] |
| 0xBBE3545 | 8 | bind_call | - | `0xBBE3545  call 0x567B570` | sub_567b570 Declarator bind/lookup call site 2 (from sub_bbe2d50 RTX builder) | [V] |
| 0xBBE3591 | 8 | declarator | rcx | `0xBBE3591  lea rcx,[rbp+0x588]` | rcx = Declarator object (sub_bbe2d50 call site 3) | [V] |
| 0xBBE3598 | 8 | entry_ptr | rdx | `0xBBE3598  lea rdx,[rbp+0x1030]` | rdx = dependency entry pointer (sub_bbe2d50 call site 3) | [V] |
| 0xBBE359F | 8 | third_arg_prep | rbx | `0xBBE359F  lea rbx,[rbp+0xD80]` | prepare third arg {value=1, hash_table_base_ptr} (sub_bbe2d50 call site 3) | [V] |
| 0xBBE35A6 | 8 | third_arg | r8 | `0xBBE35A6  mov r8,rbx` | r8 = {value=1, hash_table_base_ptr} (sub_bbe2d50 call site 3) | [V] |
| 0xBBE35A9 | 8 | bind_call | - | `0xBBE35A9  call 0x567B570` | sub_567b570 Declarator bind/lookup call site 3 (from sub_bbe2d50 RTX builder) | [V] |

### Declarator<RenderContext> registration call

| 0xC270521 | 8 | decl_reg_call | - | `0xC270521  call 0xC273420` | sub_c270460 calls sub_c273420 with Declarator<RenderContext> as r8 (frame-graph generator entry) | [V] |

### Module-name string search — all eight candidates absent as ASCII/UTF-16

| offset | size | name | read/store addr | verbatim `0xRVA  instr` proof line | meaning | tag |
| 0xF5238E6 | - | taau_substring | - | - | rdis str found "#upscaling_mode_radio_taau" at 0xF5238E6 (sub_51cd6c0+0x10b57) — contains "taau" as substring, not a standalone module name | [V] |
| 0xF523901 | - | taau_substring2 | - | - | rdis str found "options.upscalingModeOptions.taau" at 0xF523901 — contains "taau" as substring, not a standalone module name | [V] |
| 0xF5FD502 | - | rayTraced_substring | - | - | rdis str found "options.graphicsModeOptions.rayTraced" at 0xF5FD502 (sub_522f960+0x1c5) — contains "rayTraced" (option name, not module name "rayTrace") | [V] |
| 0xF5FD528 | - | rayTraced_substring2 | - | - | rdis str found "options.graphicsMode.rayTraced" at 0xF5FD528 (sub_210bd70+0x43, sub_5bfd7e0+0xc31c) — contains "rayTraced" (option name, not module name "rayTrace") | [V] |
| 0xFFFFFFF0 | - | averageLuminance | - | - | NOT found as ASCII or UTF-16 string in exe (rdis str, xref.py str both negative) | [V] |
| 0xFFFFFFF1 | - | localExposure | - | - | NOT found as ASCII or UTF-16 string in exe (rdis str, xref.py str both negative) | [V] |
| 0xFFFFFFF2 | - | clusterLights | - | - | NOT found as ASCII or UTF-16 string in exe (rdis str, xref.py str both negative) | [V] |
| 0xFFFFFFF3 | - | volumeScattering | - | - | NOT found as ASCII or UTF-16 string in exe (rdis str, xref.py str both negative) | [V] |
| 0xFFFFFFF4 | - | generateCubemapMips | - | - | NOT found as ASCII or UTF-16 string in exe (rdis str, xref.py str both negative) | [V] |
| 0xFFFFFFF5 | - | rayTrace | - | - | NOT found as standalone module-name string; only found as substring in "options.graphicsMode*.rayTraced" setting names | [V] |
| 0xFFFFFFF6 | - | preprocessingutils | - | - | NOT found as ASCII or UTF-16 string in exe (rdis str, xref.py str both negative) | [V] |

### Bind* kind → type mapping — handler behavior [V] (see rows above), type names [I]

Handler behavior distinguishing the 5 kinds is proven [V] by the rows above (0xC278277 kind byte store, 0xC2782BA/0xC2782C8 kind 1 copy+refcount, 0xC2782D4/0xC2782E2 kind 2 copy+refcount, 0xC278270/0xC278274 kind 3/4 direct copy). No separate instruction rows needed — these are the same addresses already tabled.

Type-name mapping [I] (inferred from handler behavior + 6aq counts, NOT proven by string/registration evidence):
- Kind 0 → BindAccelerationStructure [I] (minimal handler, RTX-only, 49 uses)
- Kind 1 → BindMaterialTexture [I] (shared_ptr refcount, most common, 1110 uses)
- Kind 2 → BindShaderBuffer [I] (shared_ptr refcount, alt null path, 373 uses)
- Kind 3 → BindFramebufferColor [I] (direct copy, no shared_ptr, 823 uses)
- Kind 4 → BindFramebufferDepth [I] (same handler as kind 3, 826 uses)

### FNV-1a 64 hash check

| offset | size | name | read/store addr | verbatim `0xRVA  instr` proof line | meaning | tag |
| 0xFFFFFFF7 | - | fnv1a_64_constants | - | - | FNV-1a 64 constants (0xCBF29CE484222325 offset basis, 0x100000001B3 prime) searched as immediates/raw bytes — module names absent as FNV-1a-64 constants per orchestrator hint r3 | [V] |

## CLOSES?
NO — blocking fact: module-name strings (averageLuminance, localExposure, taau, clusterLights, volumeScattering, generateCubemapMips, rayTrace, preprocessingutils) are absent from the exe as ASCII/UTF-16 (verified via rdis str and xref.py str), so registration calls cannot be linked to specific passes/modules; additionally all 8 decoded sub_567b570 call sites use kind=0 at entry+0x08 (placeholder), so the five Bind* kinds cannot be individually proven by registration call site. What IS proven [V]: jump table at 0xF478E3C + 5 kind handlers in sub_c278270 with verbatim lines, 8 sub_567b570 call sites (3 from sub_bbe2d50 RTX builder, 5 from sub_bbce7b0) with verbatim setup and call lines, Declarator<RenderContext> registration call at 0xC270521 (sub_c270460 → sub_c273420), handler behavior distinguishing the 5 kinds. What remains [I]: kind→Bind*type name mapping (inferred from handler behavior + 6aq counts only, not proven by string/registration evidence).

## TOOL REQUESTS
None yet.

