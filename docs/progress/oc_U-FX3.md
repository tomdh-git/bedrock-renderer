# Unit U-FX3 progress — FullscreenEffect visitor body (listing lines 2950..4250)

## Source
- Listing: docs/data/listings/effect_visitor_666aca0_667191c.txt (each line `0xRVA  instruction`)
- Target range: listing lines 2950..4250
- Context (brief): FullscreenEffect visitor head 0x666ae72 `mov rax,[r15+0x78]`, call 0x66B2B30, body from 0x666b5cf at listing line 475.

## Register analysis from lines 1..700 [V]
- Line 15 `movzx eax,byte ptr [r8+8]`: tag byte at [r8+8] drives jump table (lines 16-24).
- Line 20 `mov r15,[r8]`: r15 = [r8].
- Line 105 (0x666ae72) `mov rax,[r15+0x78]`: **rax = description pointer** ([V] listing line 105).
- Line 108 `cmp qword ptr [rax+0x40],0`: description+0x40 checked.
- Line 111 `lea r12,[r15+0x78]`: **r12 = address of the description-pointer slot** (r15+0x78); [r12] = description pointer value.
- Line 117 `mov rax,[r15+0x78]`: rax = description pointer again [V].
- Line 120 `mov rdi,[rax+0x40]`: rdi = description->field 0x40 (sub-pointer) [V].
- Body from line 475 (0x666b5cf): line 489 `mov rax,[r12]` reloads description pointer into rax [V]; line 535 `mov rdi,[r12]` reloads description pointer into rdi (overwriting the field_0x40 sub-pointer) [V].
- **Conclusion: in the body the description pointer is held via r12 (= slot address r15+0x78; [r12] = pointer), loaded into rax (line 489) and rdi (line 535). r15 holds [r8] (object containing the description pointer at +0x78); reads [r15+0x10]/[r15+0x18] at lines 521-522 are NOT description reads (r15 is the outer object).**

## NEXT
Continue appending tables for listing lines 2950..4250 (blocks remaining after this append), then state where tag-7 body ends (exit/epilogue jump).

## Block 1 — listing lines 2950..3010 (61 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 2950 | 0x666E453 | `js short 0x666E45C` | — | branch exit 0x666E45C |
| 2 | 2951 | 0x666E455 | `cvtsi2ss xmm2,rsi` | — | |
| 3 | 2952 | 0x666E45A | `jmp short 0x666E473` | — | branch exit 0x666E473 |
| 4 | 2953 | 0x666E45C | `mov rcx,rsi` | — | |
| 5 | 2954 | 0x666E45F | `shr rcx,1` | — | |
| 6 | 2955 | 0x666E462 | `mov edx,esi` | — | |
| 7 | 2956 | 0x666E464 | `and edx,1` | — | |
| 8 | 2957 | 0x666E467 | `or rdx,rcx` | — | |
| 9 | 2958 | 0x666E46A | `cvtsi2ss xmm2,rdx` | — | |
| 10 | 2959 | 0x666E46F | `addss xmm2,xmm2` | — | |
| 11 | 2960 | 0x666E473 | `movaps xmm3,xmm0` | — | |
| 12 | 2961 | 0x666E476 | `divss xmm3,xmm1` | — | |
| 13 | 2962 | 0x666E47A | `ucomiss xmm3,xmm1` | — | |
| 14 | 2963 | 0x666E47D | `jbe 0x666FBCA` | — | branch exit 0x666FBCA |
| 15 | 2964 | 0x666E483 | `divss xmm0,xmm1` | — | |
| 16 | 2965 | 0x666E487 | `call 0xEEC73F0` | — | call 0xEEC73F0 |
| 17 | 2966 | 0x666E48C | `cvttss2si rax,xmm0` | — | |
| 18 | 2967 | 0x666E491 | `mov rcx,rax` | — | |
| 19 | 2968 | 0x666E494 | `subss xmm0,[0xEEE6700]` | — | |
| 20 | 2969 | 0x666E49C | `cvttss2si rdx,xmm0` | — | |
| 21 | 2970 | 0x666E4A1 | `sar rcx,0x3F` | — | |
| 22 | 2971 | 0x666E4A5 | `and rdx,rcx` | — | |
| 23 | 2972 | 0x666E4A8 | `or rdx,rax` | — | |
| 24 | 2973 | 0x666E4AB | `cmp rdx,9` | — | |
| 25 | 2974 | 0x666E4AF | `mov eax,8` | — | |
| 26 | 2975 | 0x666E4B4 | `cmovae rax,rdx` | — | |
| 27 | 2976 | 0x666E4B8 | `cmp rsi,rax` | — | |
| 28 | 2977 | 0x666E4BB | `jae short 0x666E4DA` | — | branch exit 0x666E4DA |
| 29 | 2978 | 0x666E4BD | `lea rcx,[rsi*8]` | — | |
| 30 | 2979 | 0x666E4C5 | `cmp rcx,rax` | — | |
| 31 | 2980 | 0x666E4C8 | `cmovbe rcx,rax` | — | |
| 32 | 2981 | 0x666E4CC | `cmp rsi,0x200` | — | |
| 33 | 2982 | 0x666E4D3 | `cmovae rcx,rax` | — | |
| 34 | 2983 | 0x666E4D7 | `mov rsi,rcx` | — | |
| 35 | 2984 | 0x666E4DA | `lea rcx,[rbp+0x5E0]` | — | |
| 36 | 2985 | 0x666E4E1 | `mov rdx,rsi` | — | |
| 37 | 2986 | 0x666E4E4 | `call 0x77D80` | — | call 0x77D80 |
| 38 | 2988 | 0x666E4EA | `mov rcx,[rbp+0x610]` | — | |
| 39 | 2989 | 0x666E4F1 | `and rcx,rdi` | — | |
| 40 | 2990 | 0x666E4F4 | `mov rax,[rbp+0x5E8]` | — | |
| 41 | 2991 | 0x666E4FB | `mov rdx,[rbp+0x5F8]` | — | |
| 42 | 2992 | 0x666E502 | `shl rcx,4` | — | |
| 43 | 2993 | 0x666E506 | `mov rbx,[rdx+rcx+8]` | — | |
| 44 | 2994 | 0x666E50B | `cmp rbx,rax` | — | |
| 45 | 2995 | 0x666E50E | `je 0x666FBCA` | — | branch exit 0x666FBCA |
| 46 | 2996 | 0x666E514 | `mov rsi,[r14+0x20]` | — | |
| 47 | 2997 | 0x666E518 | `cmp qword ptr [r14+0x28],0x10` | — | |
| 48 | 2998 | 0x666E51D | `jb short 0x666E531` | — | branch exit 0x666E531 |
| 49 | 2999 | 0x666E51F | `mov rax,[rbp+0x658]` | — | |
| 50 | 3000 | 0x666E526 | `mov rax,[rax+0x10]` | — | |
| 51 | 3001 | 0x666E52A | `mov [rbp+0x660],rax` | — | |
| 52 | 3002 | 0x666E531 | `mov r15,[rdx+rcx]` | — | |
| 53 | 3003 | 0x666E535 | `test rsi,rsi` | — | |
| 54 | 3004 | 0x666E538 | `je short 0x666E57D` | — | branch exit 0x666E57D |
| 55 | 3005 | 0x666E53A | `cmp rsi,[rbx+0x20]` | [rbx+0x20] qword → compare against rsi | |
| 56 | 3007 | 0x666E540 | `cmp qword ptr [rbx+0x28],0x10` | [rbx+0x28] qword | |
| 57 | 3008 | 0x666E545 | `jb short 0x666E54D` | — | branch exit 0x666E54D |
| 58 | 3009 | 0x666E547 | `mov rdx,[rbx+0x10]` | [rbx+0x10] qword → rdx | |
| 59 | 3010 | 0x666E54D | `lea rdx,[rbx+0x10]` | — | |

**Description-field reads in this block:** none directly off the description pointer (description pointer not yet loaded into r12/r15 in this block; rbx reads are off a chain object, [I] not description). Branch exits: 0x666E45C, 0x666E473, 0x666FBCA, 0x666E4DA, 0x666E531, 0x666E57D, 0x666E54D. Calls: 0xEEC73F0 (line 2965), 0x77D80 (line 2986).

## Block 2 — listing lines 3011..3070 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3011 | 0x666E54D | `lea rdx,[rbx+0x10]` | — | |
| 2 | 3012 | 0x666E551 | `mov rcx,[rbp+0x660]` | — | |
| 3 | 3013 | 0x666E558 | `mov r8,rsi` | — | |
| 4 | 3014 | 0x666E55B | `call 0xEEC6EB0` | — | call 0xEEC6EB0 |
| 5 | 3015 | 0x666E560 | `test eax,eax` | — | |
| 6 | 3016 | 0x666E562 | `je 0x666FBC0` | — | branch exit 0x666FBC0 |
| 7 | 3017 | 0x666E568 | `cmp rbx,r15` | — | |
| 8 | 3018 | 0x666E56B | `je short 0x666E58D` | — | branch exit 0x666E58D |
| 9 | 3019 | 0x666E56D | `mov rbx,[rbx+8]` | [rbx+8] qword → rbx | |
| 10 | 3020 | 0x666E571 | `cmp rsi,[rbx+0x20]` | [rbx+0x20] qword → compare vs rsi | |
| 11 | 3021 | 0x666E575 | `je short 0x666E540` | — | branch exit 0x666E540 |
| 12 | 3022 | 0x666E577 | `jmp short 0x666E568` | — | branch exit 0x666E568 |
| 13 | 3023 | 0x666E579 | `mov rbx,[rbx+8]` | [rbx+8] qword → rbx | |
| 14 | 3024 | 0x666E57D | `cmp qword ptr [rbx+0x20],0` | [rbx+0x20] qword | |
| 15 | 3025 | 0x666E582 | `je 0x666FBC0` | — | branch exit 0x666FBC0 |
| 16 | 3026 | 0x666E588 | `cmp rbx,r15` | — | |
| 17 | 3027 | 0x666E58B | `jne short 0x666E579` | — | branch exit 0x666E579 |
| 18 | 3028 | 0x666E58D | `mov rax,rbx` | — | |
| 19 | 3029 | 0x666E590 | `jmp 0x666FBC3` | — | branch exit 0x666FBC3 |
| 20 | 3030 | 0x666E595 | `xor ecx,ecx` | — | |
| 21 | 3031 | 0x666E597 | `mov rdx,[rbp+0x1F8]` | — | |
| 22 | 3032 | 0x666E59E | `mov [rbp+0x558],rdx` | — | |
| 23 | 3033 | 0x666E5A5 | `mov [rbp+0x560],rcx` | — | |
| 24 | 3034 | 0x666E5AC | `mov [rbp+0x568],al` | — | |
| 25 | 3035 | 0x666E5B2 | `mov rax,[rbp+0x220]` | — | |
| 26 | 3036 | 0x666E5B9 | `mov [rbp+0x580],rax` | — | |
| 27 | 3037 | 0x666E5C0 | `movaps xmm0,[rbp+0x210]` | — | |
| 28 | 3038 | 0x666E5C7 | `movups [rbp+0x570],xmm0` | — | |
| 29 | 3039 | 0x666E5CE | `lea rdx,[rbp+0x588]` | — | |
| 30 | 3040 | 0x666E5D5 | `mov [rbp+0x588],si` | — | |
| 31 | 3041 | 0x666E5DC | `mov ecx,0x9D0` | — | |
| 32 | 3042 | 0x666E5E1 | `add rcx,[r12+0x10]` | [r12+0x10] qword → rcx | |
| 33 | 3043 | 0x666E5E6 | `mov [rsp+0x30],rdi` | — | |
| 34 | 3044 | 0x666E5EB | `mov [rsp+0x28],r10` | — | |
| 35 | 3045 | 0x666E5F0 | `mov [rsp+0x20],r11` | — | |
| 36 | 3046 | 0x666E5F5 | `call 0x67EAB80` | — | call 0x67EAB80 |
| 37 | 3048 | 0x666E5FB | `lea r14,[rbp+0x3F0]` | — | |
| 38 | 3049 | 0x666E602 | `mov rcx,r14` | — | |
| 39 | 3050 | 0x666E605 | `call 0x66A6470` | — | call 0x66A6470 |
| 40 | 3051 | 0x666E60A | `cmp byte ptr [rbp+0x208],3` | — | |
| 41 | 3052 | 0x666E611 | `jne short 0x666E64A` | — | branch exit 0x666E64A |
| 42 | 3053 | 0x666E613 | `mov rsi,[rbp+0x200]` | — | |
| 43 | 3054 | 0x666E61A | `test rsi,rsi` | — | |
| 44 | 3055 | 0x666E61D | `je short 0x666E64A` | — | branch exit 0x666E64A |
| 45 | 3056 | 0x666E61F | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 46 | 3057 | 0x666E623 | `jne short 0x666E64A` | — | branch exit 0x666E64A |
| 47 | 3058 | 0x666E625 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 48 | 3059 | 0x666E628 | `mov rax,[rax]` | [rax] qword → rax | |
| 49 | 3060 | 0x666E62B | `mov rcx,rsi` | — | |
| 50 | 3061 | 0x666E62E | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 51 | 3062 | 0x666E634 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 52 | 3063 | 0x666E638 | `jne short 0x666E64A` | — | branch exit 0x666E64A |
| 53 | 3064 | 0x666E63A | `mov rax,[rsi]` | [rsi] qword → rax | |
| 54 | 3065 | 0x666E63D | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 55 | 3066 | 0x666E641 | `mov rcx,rsi` | — | |
| 56 | 3067 | 0x666E644 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 57 | 3068 | 0x666E64A | `mov rbx,[rbp+0x1D8]` | — | |
| 58 | 3069 | 0x666E651 | `test rbx,rbx` | — | |
| 59 | 3070 | 0x666E654 | `je short 0x666E6A5` | — | branch exit 0x666E6A5 |

**Description-field reads in this block:** line 3042 `add rcx,[r12+0x10]` reads [r12+0x10] qword → rcx [V]; r12 at this point still holds the slot address r15+0x78 (from head line 111), NOT yet the description pointer — so [r12+0x10] is [slot+0x10] = [r15+0x88], [I] not a description-field read until r12 is overwritten at line 3115 `mov r12,[r12]`. All rbx/rsi reads here are chain/refcount objects, not description. Branch exits: 0x666FBC0, 0x666E58D, 0x666E540, 0x666E568, 0x666E579, 0x666FBC3, 0x666E64A, 0x666E6A5. Calls: 0xEEC6EB0 (3014), 0x66A6470 (3050), 0x67EAB80 (3046), qword ptr [0xF99FFA0] (3061, 3067).

## Block 3 — listing lines 3071..3130 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3071 | 0x666E656 | `mov r15,[rbp+0x1E0]` | — | |
| 2 | 3072 | 0x666E65D | `jmp short 0x666E664` | — | branch exit 0x666E664 |
| 3 | 3074 | 0x666E660 | `add rbx,0x28` | — | |
| 4 | 3075 | 0x666E664 | `cmp rbx,r15` | — | |
| 5 | 3076 | 0x666E667 | `je short 0x666E6A5` | — | branch exit 0x666E6A5 |
| 6 | 3077 | 0x666E669 | `cmp byte ptr [rbx+0x18],2` | [rbx+0x18] byte | |
| 7 | 3078 | 0x666E66D | `jne short 0x666E660` | — | branch exit 0x666E660 |
| 8 | 3079 | 0x666E66F | `mov rsi,[rbx+8]` | [rbx+8] qword → rsi | |
| 9 | 3080 | 0x666E673 | `test rsi,rsi` | — | |
| 10 | 3081 | 0x666E676 | `je short 0x666E660` | — | branch exit 0x666E660 |
| 11 | 3082 | 0x666E678 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 12 | 3083 | 0x666E67C | `jne short 0x666E660` | — | branch exit 0x666E660 |
| 13 | 3084 | 0x666E67E | `mov rax,[rsi]` | [rsi] qword → rax | |
| 14 | 3085 | 0x666E681 | `mov rax,[rax]` | [rax] qword → rax | |
| 15 | 3086 | 0x666E684 | `mov rcx,rsi` | — | |
| 16 | 3087 | 0x666E687 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 17 | 3088 | 0x666E68D | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 18 | 3089 | 0x666E691 | `jne short 0x666E660` | — | branch exit 0x666E660 |
| 19 | 3090 | 0x666E693 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 20 | 3091 | 0x666E696 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 21 | 3092 | 0x666E69A | `mov rcx,rsi` | — | |
| 22 | 3093 | 0x666E69D | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 23 | 3094 | 0x666E6A3 | `jmp short 0x666E660` | — | branch exit 0x666E660 |
| 24 | 3095 | 0x666E6A5 | `cmp byte ptr [rbp+0x380],1` | — | |
| 25 | 3096 | 0x666E6AC | `mov rsi,[rbp+0x668]` | — | |
| 26 | 3097 | 0x666E6B3 | `jne short 0x666E6F5` | — | branch exit 0x666E6F5 |
| 27 | 3098 | 0x666E6B5 | `mov rcx,[rbp+0x340]` | — | |
| 28 | 3099 | 0x666E6BC | `test rcx,rcx` | — | |
| 29 | 3100 | 0x666E6BF | `je short 0x666E6F5` | — | branch exit 0x666E6F5 |
| 30 | 3101 | 0x666E6C1 | `mov rdx,[rbp+0x350]` | — | |
| 31 | 3102 | 0x666E6C8 | `sub rdx,rcx` | — | |
| 32 | 3103 | 0x666E6CB | `cmp rdx,0x1000` | — | |
| 33 | 3104 | 0x666E6D2 | `jb short 0x666E6F0` | — | branch exit 0x666E6F0 |
| 34 | 3105 | 0x666E6D4 | `mov rax,[rcx-8]` | [rcx-8] qword → rax | |
| 35 | 3106 | 0x666E6D8 | `add rcx,0xFFFFFFFFFFFFFFF8` | — | |
| 36 | 3107 | 0x666E6DC | `sub rcx,rax` | — | |
| 37 | 3108 | 0x666E6DF | `cmp rcx,0x20` | — | |
| 38 | 3109 | 0x666E6E3 | `jae 0x6670A7A` | — | branch exit 0x6670A7A |
| 39 | 3110 | 0x666E6E9 | `or rdx,0x27` | — | |
| 40 | 3111 | 0x666E6ED | `mov rcx,rax` | — | |
| 41 | 3112 | 0x666E6F0 | `call 0xE935700` | — | call 0xE935700 |
| 42 | 3113 | 0x666E6F5 | `mov r15d,[rsi+0x84]` | [rsi+0x84] dword → r15d | |
| 43 | 3114 | 0x666E6FC | `mov r13,r12` | — | |
| 44 | 3115 | 0x666E6FF | `mov r12,[r12]` | **[r12] qword → r12: r12 becomes the DESCRIPTION POINTER [V]** (was slot address r15+0x78) | |
| 45 | 3116 | 0x666E703 | `mov rax,[rbp+0x5C0]` | — | |
| 46 | 3117 | 0x666E70A | `xorps xmm0,xmm0` | — | |
| 47 | 3118 | 0x666E70D | `movaps [rbp+0x3F0],xmm0` | — | |
| 48 | 3119 | 0x666E714 | `mov rcx,[rax+8]` | [rax+8] qword → rcx | |
| 49 | 3120 | 0x666E718 | `test rcx,rcx` | — | |
| 50 | 3121 | 0x666E71B | `je short 0x666E764` | — | branch exit 0x666E764 |
| 51 | 3122 | 0x666E71D | `lock inc dword ptr [rcx+8]` | [rcx+8] dword | |
| 52 | 3123 | 0x666E721 | `mov rsi,[rbp+0x3F8]` | — | |
| 53 | 3124 | 0x666E728 | `movups xmm0,[rax]` | [rax] qword → xmm0 | |
| 54 | 3125 | 0x666E72B | `movaps [rbp+0x3F0],xmm0` | — | |
| 55 | 3126 | 0x666E732 | `test rsi,rsi` | — | |
| 56 | 3127 | 0x666E735 | `je short 0x666E779` | — | branch exit 0x666E779 |
| 57 | 3128 | 0x666E737 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 58 | 3129 | 0x666E73B | `jne short 0x666E779` | — | branch exit 0x666E779 |
| 59 | 3130 | 0x666E73D | `mov rax,[rsi]` | [rsi] qword → rax | |

**Description-field reads in this block:** line 3115 `mov r12,[r12]` — [r12] qword → r12 makes r12 the description pointer [V]; after this, [r12+...] reads are description-field reads. Line 3113 `mov r15d,[rsi+0x84]` reads [rsi+0x84] dword where rsi=[rbp+0x668] [V] but rsi here is a heap object [I] (not the description). All rbx/rsi/rax reads are refcount/chain objects, not description. Branch exits: 0x666E664, 0x666E6A5, 0x666E660, 0x666E6F5, 0x666E6F0, 0x6670A7A, 0x666E764, 0x666E779. Calls: qword ptr [0xF99FFA0] (3087, 3093), 0xE935700 (3112).

## Block 4 — listing lines 3131..3190 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3131 | 0x666E740 | `mov rax,[rax]` | [rax] qword → rax | |
| 2 | 3132 | 0x666E743 | `mov rcx,rsi` | — | |
| 3 | 3133 | 0x666E746 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 4 | 3134 | 0x666E74C | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 5 | 3135 | 0x666E750 | `jne short 0x666E779` | — | branch exit 0x666E779 |
| 6 | 3136 | 0x666E752 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 7 | 3137 | 0x666E755 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 8 | 3138 | 0x666E759 | `mov rcx,rsi` | — | |
| 9 | 3139 | 0x666E75C | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 10 | 3140 | 0x666E762 | `jmp short 0x666E779` | — | branch exit 0x666E779 |
| 11 | 3141 | 0x666E764 | `mov rax,[rax]` | [rax] qword → rax | |
| 12 | 3142 | 0x666E767 | `mov [rbp+0x3F0],rax` | — | |
| 13 | 3143 | 0x666E76E | `mov qword ptr [rbp+0x3F8],0` | — | |
| 14 | 3144 | 0x666E779 | `mov rax,[rbp+0x3F0]` | — | |
| 15 | 3145 | 0x666E780 | `mov rax,[rax+0x18]` | [rax+0x18] qword → rax | |
| 16 | 3146 | 0x666E784 | `mov rax,[rax]` | [rax] qword → rax | |
| 17 | 3147 | 0x666E787 | `mov [rbp],rax` | — | |
| 18 | 3148 | 0x666E78B | `lea rbx,[rbp+8]` | — | |
| 19 | 3149 | 0x666E78F | `mov r8,[r12]` | **[r12] qword → r8: description+0x0 read [V]** | |
| 20 | 3150 | 0x666E793 | `mov rdx,[rax+0x170]` | [rax+0x170] qword → rdx | |
| 21 | 3151 | 0x666E79A | `mov rcx,rbx` | — | |
| 22 | 3152 | 0x666E79D | `call 0xE86B370` | — | call 0xE86B370 |
| 23 | 3153 | 0x666E7A2 | `nop` | — | |
| 24 | 3154 | 0x666E7A3 | `mov [rbp+0x80],r12` | — | |
| 25 | 3155 | 0x666E7AA | `mov rsi,[rbp+0x3F8]` | — | |
| 26 | 3156 | 0x666E7B1 | `test rsi,rsi` | — | |
| 27 | 3157 | 0x666E7B4 | `je short 0x666E7E1` | — | branch exit 0x666E7E1 |
| 28 | 3158 | 0x666E7B6 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 29 | 3159 | 0x666E7BA | `jne short 0x666E7E1` | — | branch exit 0x666E7E1 |
| 30 | 3160 | 0x666E7BC | `mov rax,[rsi]` | [rsi] qword → rax | |
| 31 | 3161 | 0x666E7BF | `mov rax,[rax]` | [rax] qword → rax | |
| 32 | 3162 | 0x666E7C2 | `mov rcx,rsi` | — | |
| 33 | 3163 | 0x666E7C5 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 34 | 3164 | 0x666E7CB | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 35 | 3165 | 0x666E7CF | `jne short 0x666E7E1` | — | branch exit 0x666E7E1 |
| 36 | 3166 | 0x666E7D1 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 37 | 3167 | 0x666E7D4 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 38 | 3168 | 0x666E7D8 | `mov rcx,rsi` | — | |
| 39 | 3169 | 0x666E7DB | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 40 | 3170 | 0x666E7E1 | `mov rax,[rbp+0x48]` | — | |
| 41 | 3171 | 0x666E7E5 | `movzx r8d,word ptr [rbp+0x52]` | — | |
| 42 | 3172 | 0x666E7EA | `mov ecx,r8d` | — | |
| 43 | 3173 | 0x666E7ED | `shl ecx,4` | — | |
| 44 | 3174 | 0x666E7F0 | `lea rdx,[rcx+rcx*2]` | — | |
| 45 | 3175 | 0x666E7F4 | `mov rcx,rax` | — | |
| 46 | 3176 | 0x666E7F7 | `test r8,r8` | — | |
| 47 | 3177 | 0x666E7FA | `je short 0x666E825` | — | branch exit 0x666E825 |
| 48 | 3178 | 0x666E7FC | `mov r8,[0x129FA148]` | — | |
| 49 | 3179 | 0x666E803 | `mov r9,rdx` | — | |
| 50 | 3180 | 0x666E806 | `mov rcx,rax` | — | |
| 51 | 3181 | 0x666E809 | `nop [rax]` | — | |
| 52 | 3182 | 0x666E810 | `mov r10,[rcx]` | [rcx] qword → r10 | |
| 53 | 3183 | 0x666E813 | `cmp [r10+0x28],r8` | [r10+0x28] qword | |
| 54 | 3184 | 0x666E817 | `je short 0x666E825` | — | branch exit 0x666E825 |
| 55 | 3185 | 0x666E819 | `add rcx,0x30` | — | |
| 56 | 3186 | 0x666E81D | `add r9,0xFFFFFFFFFFFFFFD0` | — | |
| 57 | 3187 | 0x666E821 | `jne short 0x666E810` | — | branch exit 0x666E810 |
| 58 | 3188 | 0x666E823 | `jmp short 0x666E873` | — | branch exit 0x666E873 |
| 59 | 3189 | 0x666E825 | `add rdx,rax` | — | |
| 60 | 3190 | 0x666E828 | `cmp rcx,rdx` | — | |

**Description-field reads in this block:** line 3149 `mov r8,[r12]` reads [r12+0x0] qword → r8 [V] (r12 = description pointer). Line 3150 `mov rdx,[rax+0x170]` where rax=[rbp+0x3F0] chain load [I], not description. Line 3145 `mov rax,[rax+0x18]` is a vtable/chain read [I]. All other reads are stack/heap chain objects. Branch exits: 0x666E779, 0x666E7E1, 0x666E825, 0x666E810, 0x666E873. Calls: 0xE86B370 (3152), qword ptr [0xF99FFA0] (3133, 3139, 3163, 3169).

## Block 5 — listing lines 3191..3250 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3191 | 0x666E82B | `jae short 0x666E873` | — | branch exit 0x666E873 |
| 2 | 3192 | 0x666E82D | `sub ecx,eax` | — | |
| 3 | 3193 | 0x666E82F | `shr ecx,4` | — | |
| 4 | 3194 | 0x666E832 | `imul eax,ecx,0xFFFFAAAB` | — | |
| 5 | 3195 | 0x666E838 | `mov [rbp+0x1D0],ax` | — | |
| 6 | 3196 | 0x666E83F | `mov byte ptr [rbp+0x1D2],1` | — | |
| 7 | 3197 | 0x666E846 | `mov byte ptr [rbp+0x3FC],0` | — | |
| 8 | 3198 | 0x666E84D | `mov dword ptr [rsp+0x20],0` | — | |
| 9 | 3199 | 0x666E855 | `mov rcx,rbp` | — | |
| 10 | 3200 | 0x666E858 | `lea rdx,[rbp+0x1D0]` | — | |
| 11 | 3201 | 0x666E85F | `lea r9,[rbp+0x3F0]` | — | |
| 12 | 3202 | 0x666E866 | `mov r8,[rbp+0x670]` | — | |
| 13 | 3203 | 0x666E86D | `call 0xBCABA00` | — | call 0xBCABA00 |
| 14 | 3204 | 0x666E872 | `nop` | — | |
| 15 | 3205 | 0x666E873 | `mov rax,[rbp+0x668]` | — | |
| 16 | 3206 | 0x666E87A | `movups xmm0,[rax+0x18]` | [rax+0x18] 16 bytes → xmm0 (rax=[rbp+0x668] heap object [I]) | |
| 17 | 3207 | 0x666E87E | `movaps [rbp+0x3F0],xmm0` | — | |
| 18 | 3208 | 0x666E885 | `mov qword ptr [rbp+0x1D0],1` | — | |
| 19 | 3209 | 0x666E890 | `mov [rbp+0x1D8],r14` | — | |
| 20 | 3210 | 0x666E897 | `mov rax,[rbp+0x38]` | — | |
| 21 | 3211 | 0x666E89B | `movzx edx,word ptr [rbp+0x42]` | — | |
| 22 | 3212 | 0x666E89F | `mov ecx,edx` | — | |
| 23 | 3214 | 0x666E8A4 | `mov r8,rax` | — | |
| 24 | 3215 | 0x666E8A7 | `test edx,edx` | — | |
| 25 | 3216 | 0x666E8A9 | `je short 0x666E8DC` | — | branch exit 0x666E8DC |
| 26 | 3217 | 0x666E8AB | `mov r9,[0x129FA158]` | — | |
| 27 | 3218 | 0x666E8B2 | `xor r8d,r8d` | — | |
| 28 | 3220 | 0x666E8C0 | `mov r10,[rax+r8]` | [rax+r8] qword → r10 | |
| 29 | 3221 | 0x666E8C4 | `cmp [r10+0x28],r9` | [r10+0x28] qword | |
| 30 | 3222 | 0x666E8C8 | `je short 0x666E8D9` | — | branch exit 0x666E8D9 |
| 31 | 3223 | 0x666E8CA | `add r8,0x10` | — | |
| 32 | 3224 | 0x666E8CE | `cmp rcx,r8` | — | |
| 33 | 3225 | 0x666E8D1 | `jne short 0x666E8C0` | — | branch exit 0x666E8C0 |
| 34 | 3226 | 0x666E8D3 | `mov dx,1` | — | |
| 35 | 3227 | 0x666E8D7 | `jmp short 0x666E91F` | — | branch exit 0x666E91F |
| 36 | 3228 | 0x666E8D9 | `add r8,rax` | — | |
| 37 | 3229 | 0x666E8DC | `lea r9,[rax+rcx]` | — | |
| 38 | 3230 | 0x666E8E0 | `cmp r8,r9` | — | |
| 39 | 3231 | 0x666E8E3 | `jae short 0x666E91F` | — | branch exit 0x666E91F |
| 40 | 3232 | 0x666E8E5 | `sub r8d,eax` | — | |
| 41 | 3233 | 0x666E8E8 | `shr r8d,4` | — | |
| 42 | 3234 | 0x666E8EC | `mov [rbp+0x340],r8w` | — | |
| 43 | 3235 | 0x666E8F4 | `mov byte ptr [rbp+0x342],1` | — | |
| 44 | 3236 | 0x666E8FB | `lea rdx,[rbp+0x340]` | — | |
| 45 | 3237 | 0x666E902 | `lea r8,[rbp+0x1D0]` | — | |
| 46 | 3238 | 0x666E909 | `mov rcx,rbx` | — | |
| 47 | 3239 | 0x666E90C | `call 0x5679DB0` | — | call 0x5679DB0 |
| 48 | 3240 | 0x666E911 | `nop` | — | |
| 49 | 3241 | 0x666E912 | `mov rax,[rbp+0x38]` | — | |
| 50 | 3242 | 0x666E916 | `movzx edx,word ptr [rbp+0x42]` | — | |
| 51 | 3243 | 0x666E91A | `mov ecx,edx` | — | |
| 52 | 3244 | 0x666E91C | `shl ecx,4` | — | |
| 53 | 3245 | 0x666E91F | `movaps xmm0,[0xEF40DE0]` | — | |
| 54 | 3246 | 0x666E926 | `movaps [rbp+0x3F0],xmm0` | — | |
| 55 | 3247 | 0x666E92D | `mov qword ptr [rbp+0x1D0],1` | — | |
| 56 | 3248 | 0x666E938 | `mov [rbp+0x1D8],r14` | — | |
| 57 | 3249 | 0x666E93F | `mov r8,rax` | — | |
| 58 | 3250 | 0x666E942 | `test dx,dx` | — | |

**Description-field reads in this block:** none directly off description pointer r12; line 3206 `movups xmm0,[rax+0x18]` where rax=[rbp+0x668] (heap object [I], not description). Branch exits: 0x666E873, 0x666E8DC, 0x666E8D9, 0x666E8C0, 0x666E91F, 0x666E8A9. Calls: 0xBCABA00 (3203), 0x5679DB0 (3239).

## Block 6 — listing lines 3251..3310 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3251 | 0x666E945 | `je short 0x666E975` | — | branch exit 0x666E975 |
| 2 | 3252 | 0x666E947 | `mov rdx,[0x129FA168]` | — | |
| 3 | 3253 | 0x666E94E | `mov r9,rcx` | — | |
| 4 | 3254 | 0x666E951 | `mov r8,rax` | — | |
| 5 | 3256 | 0x666E960 | `mov r10,[r8]` | [r8] qword → r10 | |
| 6 | 3257 | 0x666E963 | `cmp [r10+0x28],rdx` | [r10+0x28] qword | |
| 7 | 3258 | 0x666E967 | `je short 0x666E975` | — | branch exit 0x666E975 |
| 8 | 3259 | 0x666E969 | `add r8,0x10` | — | |
| 9 | 3260 | 0x666E96D | `add r9,0xFFFFFFFFFFFFFFF0` | — | |
| 10 | 3261 | 0x666E971 | `jne short 0x666E960` | — | branch exit 0x666E960 |
| 11 | 3262 | 0x666E973 | `jmp short 0x666E9AA` | — | branch exit 0x666E9AA |
| 12 | 3263 | 0x666E975 | `add rcx,rax` | — | |
| 13 | 3264 | 0x666E978 | `cmp r8,rcx` | — | |
| 14 | 3265 | 0x666E97B | `jae short 0x666E9AA` | — | branch exit 0x666E9AA |
| 15 | 3266 | 0x666E97D | `sub r8d,eax` | — | |
| 16 | 3267 | 0x666E980 | `shr r8d,4` | — | |
| 17 | 3268 | 0x666E984 | `mov [rbp+0x340],r8w` | — | |
| 18 | 3269 | 0x666E98C | `mov byte ptr [rbp+0x342],1` | — | |
| 19 | 3270 | 0x666E993 | `lea rdx,[rbp+0x340]` | — | |
| 20 | 3271 | 0x666E99A | `lea r8,[rbp+0x1D0]` | — | |
| 21 | 3272 | 0x666E9A1 | `mov rcx,rbx` | — | |
| 22 | 3273 | 0x666E9A4 | `call 0x5679DB0` | — | call 0x5679DB0 |
| 23 | 3274 | 0x666E9A9 | `nop` | — | |
| 24 | 3275 | 0x666E9AA | `mov rax,[rbp+0x668]` | — | |
| 25 | 3276 | 0x666E9B1 | `mov rsi,[rax+0x78]` | **[rax+0x78] qword → rsi: description pointer reloaded [V]** (rax=[rbp+0x668] [I] holds outer object; its +0x78 is the description pointer slot per head pattern r15+0x78) | |
| 26 | 3277 | 0x666E9B5 | `mov rax,[rsi+0x60]` | **[rsi+0x60] qword → rax: description+0x60 read [V]** | |
| 27 | 3278 | 0x666E9B9 | `sub rax,[rsi+0x58]` | **[rsi+0x58] qword → sub from rax [V]** | |
| 28 | 3279 | 0x666E9BD | `shr rax,2` | — | |
| 29 | 3280 | 0x666E9C1 | `imul eax,0xAAAAAAAB` | — | |
| 30 | 3281 | 0x666E9C7 | `test eax,eax` | — | |
| 31 | 3282 | 0x666E9C9 | `je short 0x666E9FF` | — | branch exit 0x666E9FF |
| 32 | 3283 | 0x666E9CB | `mov edx,0x250` | — | |
| 33 | 3284 | 0x666E9D0 | `add rdx,[rbp]` | — | |
| 34 | 3285 | 0x666E9D4 | `lea rcx,[rbp+0x3F0]` | — | |
| 35 | 3286 | 0x666E9DB | `xor r8d,r8d` | — | |
| 36 | 3287 | 0x666E9DE | `call 0xBBD7C70` | — | call 0xBBD7C70 |
| 37 | 3288 | 0x666E9E3 | `nop` | — | |
| 38 | 3289 | 0x666E9E4 | `lea rdx,[rbp+0x3F0]` | — | |
| 39 | 3290 | 0x666E9EB | `mov rcx,rsi` | — | |
| 40 | 3291 | 0x666E9EE | `call 0x4DEDD00` | — | call 0x4DEDD00 |
| 41 | 3292 | 0x666E9F3 | `nop` | — | |
| 42 | 3293 | 0x666E9F4 | `mov rax,[rbp+0x668]` | — | |
| 43 | 3294 | 0x666E9FB | `mov rsi,[rax+0x78]` | **[rax+0x78] qword → rsi: description pointer reloaded [V]** | |
| 44 | 3295 | 0x666E9FF | `xor r14d,r14d` | — | |
| 45 | 3296 | 0x666EA02 | `cmp byte ptr [rsi+0x1D4],0` | **[rsi+0x1D4] byte → compare vs 0 [V]** | |
| 46 | 3297 | 0x666EA09 | `je short 0x666EA12` | — | branch exit 0x666EA12 |
| 47 | 3298 | 0x666EA0B | `mov r14d,[rsi+0x1D0]` | **[rsi+0x1D0] dword → r14d [V]** | |
| 48 | 3299 | 0x666EA12 | `movaps xmm0,[rbp+0x2A0]` | — | |
| 49 | 3300 | 0x666EA19 | `movaps xmm1,[rbp+0x2B0]` | — | |
| 50 | 3301 | 0x666EA20 | `movaps xmm2,[rbp+0x2C0]` | — | |
| 51 | 3302 | 0x666EA27 | `movaps xmm3,[rbp+0x2D0]` | — | |
| 52 | 3303 | 0x666EA2E | `movaps [rbp+0x340],xmm0` | — | |
| 53 | 3304 | 0x666EA35 | `movaps [rbp+0x350],xmm1` | — | |
| 54 | 3305 | 0x666EA3C | `movaps [rbp+0x360],xmm2` | — | |
| 55 | 3306 | 0x666EA43 | `movaps [rbp+0x370],xmm3` | — | |
| 56 | 3307 | 0x666EA4A | `mov byte ptr [rbp+0x380],0` | — | |
| 57 | 3308 | 0x666EA51 | `xorps xmm0,xmm0` | — | |
| 58 | 3309 | 0x666EA54 | `movaps [rbp+0x3D0],xmm0` | — | |
| 59 | 3310 | 0x666EA5B | `mov rax,[rsi+0x1B0]` | **[rsi+0x1B0] qword → rax: description+0x1B0 read [V]** | |

**Description-field reads in this block (rsi = description pointer):** line 3276 `mov rsi,[rax+0x78]` reloads description pointer into rsi [V]; line 3277 `mov rax,[rsi+0x60]` reads desc+0x60 qword → rax [V]; line 3278 `sub rax,[rsi+0x58]` reads desc+0x58 qword [V]; line 3296 `cmp byte ptr [rsi+0x1D4],0` reads desc+0x1D4 byte [V]; line 3298 `mov r14d,[rsi+0x1D0]` reads desc+0x1D0 dword → r14d [V]; line 3310 `mov rax,[rsi+0x1B0]` reads desc+0x1B0 qword → rax [V]. Branch exits: 0x666E975, 0x666E960, 0x666E9AA, 0x666E9FF, 0x666EA12. Calls: 0x5679DB0 (3273), 0xBBD7C70 (3287), 0x4DEDD00 (3291).

## Block 7 — listing lines 3311..3370 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3311 | 0x666EA62 | `test rax,rax` | — | |
| 2 | 3312 | 0x666EA65 | `je short 0x666EA6B` | — | branch exit 0x666EA6B |
| 3 | 3313 | 0x666EA67 | `movzx eax,word ptr [rax+0x10]` | [rax+0x10] word → eax (rax=[rsi+0x1B0] heap ptr [I]) | |
| 4 | 3314 | 0x666EA6B | `mov rax,[rsi+0x1B8]` | **[rsi+0x1B8] qword → rax: description+0x1B8 read [V]** | |
| 5 | 3315 | 0x666EA72 | `test rax,rax` | — | |
| 6 | 3316 | 0x666EA75 | `je short 0x666EA84` | — | branch exit 0x666EA84 |
| 7 | 3317 | 0x666EA77 | `lock inc dword ptr [rax+8]` | [rax+8] dword | |
| 8 | 3318 | 0x666EA7B | `mov rax,[rsi+0x1B8]` | **[rsi+0x1B8] qword → rax: description+0x1B8 read again [V]** | |
| 9 | 3319 | 0x666EA82 | `jmp short 0x666EA86` | — | branch exit 0x666EA86 |
| 10 | 3320 | 0x666EA84 | `xor eax,eax` | — | |
| 11 | 3321 | 0x666EA86 | `mov rcx,[rsi+0x1B0]` | **[rsi+0x1B0] qword → rcx: description+0x1B0 read again [V]** | |
| 12 | 3322 | 0x666EA8D | `mov [rbp+0x3D0],rcx` | — | |
| 13 | 3323 | 0x666EA94 | `mov rsi,[rbp+0x3D8]` | — | (note: rsi overwritten — no longer description pointer) |
| 14 | 3324 | 0x666EA9B | `mov [rbp+0x3D8],rax` | — | |
| 15 | 3325 | 0x666EAA2 | `test rsi,rsi` | — | |
| 16 | 3326 | 0x666EAA5 | `je short 0x666EAD2` | — | branch exit 0x666EAD2 |
| 17 | 3327 | 0x666EAA7 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 18 | 3328 | 0x666EAAB | `jne short 0x666EAD2` | — | branch exit 0x666EAD2 |
| 19 | 3329 | 0x666EAAD | `mov rax,[rsi]` | [rsi] qword → rax | |
| 20 | 3330 | 0x666EAB0 | `mov rax,[rax]` | [rax] qword → rax | |
| 21 | 3331 | 0x666EAB3 | `mov rcx,rsi` | — | |
| 22 | 3332 | 0x666EAB6 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 23 | 3333 | 0x666EABC | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 24 | 3334 | 0x666EAC0 | `jne short 0x666EAD2` | — | branch exit 0x666EAD2 |
| 25 | 3335 | 0x666EAC2 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 26 | 3336 | 0x666EAC5 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 27 | 3337 | 0x666EAC9 | `mov rcx,rsi` | — | |
| 28 | 3338 | 0x666EACC | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 29 | 3339 | 0x666EAD2 | `mov rax,[rbp+0x648]` | — | |
| 30 | 3340 | 0x666EAD9 | `mov r8,[rax+0x3B8]` | [rax+0x3B8] qword → r8 (rax=[rbp+0x648] heap obj [I]) | |
| 31 | 3341 | 0x666EAE0 | `mov rdx,[r13]` | — | |
| 32 | 3342 | 0x666EAE4 | `mov [rsp+0x20],r14d` | — | |
| 33 | 3343 | 0x666EAE9 | `mov dword ptr [rsp+0x30],0` | — | |
| 34 | 3344 | 0x666EAF1 | `mov dword ptr [rsp+0x28],0` | — | |
| 35 | 3345 | 0x666EAF9 | `lea rcx,[rbp+0x1D0]` | — | |
| 36 | 3346 | 0x666EB00 | `lea r9,[rbp+0x3D0]` | — | |
| 37 | 3347 | 0x666EB07 | `call 0x66A0F60` | — | call 0x66A0F60 |
| 38 | 3348 | 0x666EB0C | `nop` | — | |
| 39 | 3349 | 0x666EB0D | `add r15d,0xFFFFFFE0` | — | |
| 40 | 3350 | 0x666EB11 | `mov rax,[rbp+0x668]` | — | |
| 41 | 3351 | 0x666EB18 | `mov si,[rax+0x80]` | [rax+0x80] word → si (rax=[rbp+0x668] [I], not description) | |
| 42 | 3352 | 0x666EB1F | `movlps [rbp+0x3F4],xmm7` | — | |
| 43 | 3353 | 0x666EB26 | `movss [rbp+0x3FC],xmm6` | — | |
| 44 | 3354 | 0x666EB2E | `mov dword ptr [rbp+0x404],2` | — | |
| 45 | 3355 | 0x666EB38 | `mov byte ptr [rbp+0x408],7` | — | |
| 46 | 3356 | 0x666EB3F | `mov dword ptr [rbp+0x40C],0` | — | |
| 47 | 3357 | 0x666EB49 | `mov word ptr [rbp+0x410],1` | — | |
| 48 | 3358 | 0x666EB52 | `mov byte ptr [rbp+0x412],2` | — | |
| 49 | 3359 | 0x666EB59 | `mov dword ptr [rbp+0x414],0` | — | |
| 50 | 3360 | 0x666EB63 | `mov byte ptr [rbp+0x418],0` | — | |
| 51 | 3361 | 0x666EB6A | `xorps xmm0,xmm0` | — | |
| 52 | 3362 | 0x666EB6D | `movups [rbp+0x41C],xmm0` | — | |
| 53 | 3363 | 0x666EB74 | `mov [rbp+0x42C],r15d` | — | |
| 54 | 3364 | 0x666EB7B | `mov qword ptr [rbp+0x430],0` | — | |
| 55 | 3365 | 0x666EB86 | `mov byte ptr [rbp+0x438],8` | — | |
| 56 | 3366 | 0x666EB8D | `mov qword ptr [rbp+0x43C],0` | — | |
| 57 | 3367 | 0x666EB98 | `mov dword ptr [rbp+0x444],0` | — | |
| 58 | 3368 | 0x666EBA2 | `mov byte ptr [rbp+0x448],8` | — | |
| 59 | 3369 | 0x666EBA9 | `mov qword ptr [rbp+0x44C],0` | — | |
| 60 | 3370 | 0x666EBB4 | `mov qword ptr [rbp+0x452],0` | — | |

**Description-field reads in this block (rsi = description pointer until line 3323):** line 3313 `movzx eax,word ptr [rax+0x10]` where rax=[rsi+0x1B0] — indirect read of heap obj at desc+0x1B0 then its +0x10 [I]; line 3314 `mov rax,[rsi+0x1B8]` reads desc+0x1B8 qword → rax [V]; line 3318 `mov rax,[rsi+0x1B8]` reads desc+0x1B8 again [V]; line 3321 `mov rcx,[rsi+0x1B0]` reads desc+0x1B0 qword → rcx [V]. Line 3351 `mov si,[rax+0x80]` where rax=[rbp+0x668] — stack/local object [I], not description. Line 3323 `mov rsi,[rbp+0x3D8]` clobbers rsi — description pointer no longer in rsi after this. Branch exits: 0x666EA6B, 0x666EA84, 0x666EA86, 0x666EAD2. Calls: qword ptr [0xF99FFA0] (3332, 3338), 0x66A0F60 (3347).

## Block 8 — listing lines 3371..3430 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3371 | 0x666EBBF | `mov byte ptr [rbp+0x45A],0xFF` | — | |
| 2 | 3372 | 0x666EBC6 | `mov rax,[rbp]` | — | |
| 3 | 3373 | 0x666EBCA | `mov [rbp+0x460],rax` | — | |
| 4 | 3374 | 0x666EBD1 | `lea rcx,[rbp+0x468]` | — | |
| 5 | 3375 | 0x666EBD8 | `mov rdx,rbx` | — | |
| 6 | 3376 | 0x666EBDB | `call 0xE869FF0` | — | call 0xE869FF0 |
| 7 | 3377 | 0x666EBE0 | `nop` | — | |
| 8 | 3378 | 0x666EBE1 | `mov rax,[rbp+0x80]` | — | |
| 9 | 3379 | 0x666EBE8 | `mov [rbp+0x4E0],rax` | — | |
| 10 | 3380 | 0x666EBEF | `mov qword ptr [rbp+0x80],0` | — | |
| 11 | 3381 | 0x666EBFA | `mov byte ptr [rbp+0x528],0xFF` | — | |
| 12 | 3382 | 0x666EC01 | `movzx eax,byte ptr [rbp+0x380]` | — | |
| 13 | 3383 | 0x666EC08 | `movzx ecx,al` | — | |
| 14 | 3384 | 0x666EC0E | `cmp ecx,1` | — | |
| 15 | 3385 | 0x666EC15 | `lea r10,[rbp+0x404]` | — | |
| 16 | 3386 | 0x666EC1C | `lea r11,[rbp+0x460]` | — | |
| 17 | 3387 | 0x666EC1E | `jg short 0x666EC5C` | — | branch exit 0x666EC5C |
| 18 | 3388 | 0x666EC20 | `jne short 0x666EC71` | — | branch exit 0x666EC71 |
| 19 | 3390 | 0x666EC22 | `movaps xmm0,[rbp+0x340]` | — | |
| 20 | 3391 | 0x666EC29 | `movaps xmm1,[rbp+0x350]` | — | |
| 21 | 3392 | 0x666EC30 | `movaps xmm2,[rbp+0x360]` | — | |
| 22 | 3393 | 0x666EC37 | `movaps xmm3,[rbp+0x370]` | — | |
| 23 | 3394 | 0x666EC3E | `movups [rbp+0x4E8],xmm0` | — | |
| 24 | 3395 | 0x666EC45 | `movups [rbp+0x4F8],xmm1` | — | |
| 25 | 3396 | 0x666EC4C | `movups [rbp+0x508],xmm2` | — | |
| 26 | 3397 | 0x666EC53 | `movups [rbp+0x518],xmm3` | — | |
| 27 | 3398 | 0x666EC5A | `jmp short 0x666ECA2` | — | branch exit 0x666ECA2 |
| 28 | 3399 | 0x666EC5C | `cmp ecx,2` | — | |
| 29 | 3400 | 0x666EC5F | `jne short 0x666ECA8` | — | branch exit 0x666ECA8 |
| 30 | 3401 | 0x666EC61 | `mov rcx,[rbp+0x340]` | — | |
| 31 | 3402 | 0x666EC68 | `mov [rbp+0x4E8],rcx` | — | |
| 32 | 3403 | 0x666EC6F | `jmp short 0x666ECA2` | — | branch exit 0x666ECA2 |
| 33 | 3404 | 0x666EC71 | `mov rcx,[rbp+0x350]` | — | |
| 34 | 3405 | 0x666EC78 | `mov qword ptr [rbp+0x350],0` | — | |
| 35 | 3406 | 0x666EC83 | `movaps xmm0,[rbp+0x340]` | — | |
| 36 | 3407 | 0x666EC8A | `xorps xmm1,xmm1` | — | |
| 37 | 3408 | 0x666EC8D | `movaps [rbp+0x340],xmm1` | — | |
| 38 | 3409 | 0x666EC94 | `movups [rbp+0x4E8],xmm0` | — | |
| 39 | 3410 | 0x666EC9B | `(bad)` | — | |
| 40 | 3411 | 0x666EC9C | `mov [rbp+0x4F8],ecx` | — | |
| 41 | 3412 | 0x666ECA2 | `mov [rbp+0x528],al` | — | |
| 42 | 3413 | 0x666ECA8 | `lea r9,[rbp+0x4E8]` | — | |
| 43 | 3414 | 0x666ECAF | `lea r8,[rbp+0x530]` | — | |
| 44 | 3415 | 0x666ECB6 | `movaps xmm0,[rbp+0x1D0]` | — | |
| 45 | 3416 | 0x666ECBD | `movaps xmm1,[rbp+0x1E0]` | — | |
| 46 | 3417 | 0x666ECC4 | `mov qword ptr [rbp+0x1D8],0` | — | |
| 47 | 3418 | 0x666ECCF | `movups [rbp+0x530],xmm0` | — | |
| 48 | 3419 | 0x666ECD6 | `xorps xmm0,xmm0` | — | |
| 49 | 3420 | 0x666ECD9 | `movaps [rbp+0x1E0],xmm0` | — | |
| 50 | 3421 | 0x666ECE0 | `movups [rbp+0x540],xmm1` | — | |
| 51 | 3422 | 0x666ECE7 | `mov rax,[rbp+0x1F0]` | — | |
| 52 | 3423 | 0x666ECEE | `mov [rbp+0x550],rax` | — | |
| 53 | 3424 | 0x666ECF5 | `mov byte ptr [rbp+0x568],0xFF` | — | |
| 54 | 3425 | 0x666ECFC | `movzx eax,byte ptr [rbp+0x208]` | — | |
| 55 | 3426 | 0x666ED03 | `cmp rax,3` | — | |
| 56 | 3427 | 0x666ED07 | `ja short 0x666ED79` | — | branch exit 0x666ED79 |
| 57 | 3428 | 0x666ED09 | `lea rcx,[0xF2BF4E0]` | — | |
| 58 | 3429 | 0x666ED10 | `movsxd rdx,[rcx+rax*4]` | — | |
| 59 | 3430 | 0x666ED14 | `add rdx,rcx` | — | |

**Description-field reads in this block:** none directly off the description pointer (r12/rsi description not read here; all reads are stack locals [rbp+...]). Branch exits: 0x666EC5C, 0x666EC71, 0x666EC5A, 0x666EC5C, 0x666ECA8, 0x666ECA2, 0x666ED79. Calls: 0xE869FF0 (3376).

## Block 9 — listing lines 3431..3490 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3431 | 0x666ED17 | `jmp rdx` | — | indirect branch exit (target in rdx) |
| 2 | 3432 | 0x666ED19 | `mov rcx,[rbp+0x1F8]` | — | |
| 3 | 3433 | 0x666ED20 | `mov [rbp+0x558],rcx` | — | |
| 4 | 3434 | 0x666ED27 | `jmp short 0x666ED73` | — | branch exit 0x666ED73 |
| 5 | 3435 | 0x666ED29 | `lea rcx,[rbp+0x1F8]` | — | |
| 6 | 3436 | 0x666ED30 | `movups xmm0,[rcx]` | — | |
| 7 | 3437 | 0x666ED33 | `movups [rdi+0x164],xmm0` | — | |
| 8 | 3438 | 0x666ED3A | `jmp short 0x666ED73` | — | branch exit 0x666ED73 |
| 9 | 3439 | 0x666ED3C | `movups [rdi+0x164],xmm0` | — | |
| 10 | 3440 | 0x666ED43 | `mov rcx,[rbp+0x200]` | — | |
| 11 | 3441 | 0x666ED4A | `test rcx,rcx` | — | |
| 12 | 3442 | 0x666ED4D | `je short 0x666ED5C` | — | branch exit 0x666ED5C |
| 13 | 3443 | 0x666ED4F | `lock inc dword ptr [rcx+8]` | [rcx+8] dword | |
| 14 | 3444 | 0x666ED53 | `mov rcx,[rbp+0x200]` | — | |
| 15 | 3445 | 0x666ED5A | `jmp short 0x666ED5E` | — | branch exit 0x666ED5E |
| 16 | 3446 | 0x666ED5C | `xor ecx,ecx` | — | |
| 17 | 3447 | 0x666ED5E | `mov rdx,[rbp+0x1F8]` | — | |
| 18 | 3448 | 0x666ED65 | `mov [rbp+0x558],rdx` | — | |
| 19 | 3449 | 0x666ED6C | `mov [rbp+0x560],rcx` | — | |
| 20 | 3450 | 0x666ED73 | `mov [rbp+0x568],al` | — | |
| 21 | 3451 | 0x666ED79 | `mov rax,[rbp+0x220]` | — | |
| 22 | 3452 | 0x666ED80 | `mov [rbp+0x580],rax` | — | |
| 23 | 3453 | 0x666ED87 | `movaps xmm0,[rbp+0x210]` | — | |
| 24 | 3454 | 0x666ED8E | `movups [rbp+0x570],xmm0` | — | |
| 25 | 3455 | 0x666ED95 | `lea rdx,[rbp+0x588]` | — | |
| 26 | 3456 | 0x666ED9C | `mov [rbp+0x588],si` | — | |
| 27 | 3457 | 0x666EDA3 | `mov ecx,0x9D0` | — | |
| 28 | 3458 | 0x666EDA8 | `add rcx,[r13+0x10]` | [r13+0x10] qword → rcx (r13=r12=description pointer [V] set at line 3114-3115; so **description+0x10 read [V]** — [I] that r13 still holds description pointer) | |
| 29 | 3459 | 0x666EDAC | `mov [rsp+0x30],rdi` | — | |
| 30 | 3460 | 0x666EDB1 | `mov [rsp+0x28],r10` | — | |
| 31 | 3461 | 0x666EDB6 | `mov [rsp+0x20],r11` | — | |
| 32 | 3462 | 0x666EDBB | `call 0x67EAB80` | — | call 0x67EAB80 |
| 33 | 3463 | 0x666EDC0 | `nop` | — | |
| 34 | 3464 | 0x666EDC1 | `lea rcx,[rbp+0x3F0]` | — | |
| 35 | 3465 | 0x666EDC8 | `call 0x66A6470` | — | call 0x66A6470 |
| 36 | 3466 | 0x666EDCD | `cmp byte ptr [rbp+0x208],3` | — | |
| 37 | 3467 | 0x666EDD4 | `jne short 0x666EE0D` | — | branch exit 0x666EE0D |
| 38 | 3468 | 0x666EDD6 | `mov rsi,[rbp+0x200]` | — | |
| 39 | 3469 | 0x666EDDD | `test rsi,rsi` | — | |
| 40 | 3470 | 0x666EDE0 | `je short 0x666EE0D` | — | branch exit 0x666EE0D |
| 41 | 3471 | 0x666EDE2 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 42 | 3472 | 0x666EDE6 | `jne short 0x666EE0D` | — | branch exit 0x666EE0D |
| 43 | 3473 | 0x666EDE8 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 44 | 3474 | 0x666EDEB | `mov rax,[rax]` | [rax] qword → rax | |
| 45 | 3475 | 0x666EDEE | `mov rcx,rsi` | — | |
| 46 | 3476 | 0x666EDF1 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 47 | 3477 | 0x666EDF7 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 48 | 3478 | 0x666EDFB | `jne short 0x666EE0D` | — | branch exit 0x666EE0D |
| 49 | 3479 | 0x666EDFD | `mov rax,[rsi]` | [rsi] qword → rax | |
| 50 | 3480 | 0x666EE00 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 51 | 3481 | 0x666EE04 | `mov rcx,rsi` | — | |
| 52 | 3482 | 0x666EE07 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 53 | 3483 | 0x666EE0D | `mov rdi,[rbp+0x1D8]` | — | |
| 54 | 3484 | 0x666EE14 | `test rdi,rdi` | — | |
| 55 | 3485 | 0x666EE17 | `je short 0x666EE75` | — | branch exit 0x666EE75 |
| 56 | 3486 | 0x666EE19 | `mov rbx,[rbp+0x1E0]` | — | |
| 57 | 3487 | 0x666EE20 | `jmp short 0x666EE34` | — | branch exit 0x666EE34 |
| 58 | 3489 | 0x666EE30 | `add rdi,0x28` | — | |
| 59 | 3490 | 0x666EE34 | `cmp rdi,rbx` | — | |

**Description-field reads in this block:** line 3458 `add rcx,[r13+0x10]` reads [r13+0x10] qword → rcx [V]; r13 was set = r12 at line 3114 and r12 = description pointer at line 3115 [V], so [r13+0x10] = description+0x10 [I] (r13 not clobbered between). All rsi/rcx reads are refcount chain objects. Branch exits: 0x666ED73 (jmp rdx indirect), 0x666ED5C, 0x666ED5E, 0x666ED73, 0x666EE0D, 0x666EE75, 0x666EE34. Calls: 0x67EAB80 (3462), 0x66A6470 (3465), qword ptr [0xF99FFA0] (3476, 3482).

## Block 10 — listing lines 3491..3550 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3491 | 0x666EE37 | `je short 0x666EE75` | — | branch exit 0x666EE75 |
| 2 | 3492 | 0x666EE39 | `cmp byte ptr [rdi+0x18],2` | [rdi+0x18] byte | |
| 3 | 3493 | 0x666EE3D | `jne short 0x666EE30` | — | branch exit 0x666EE30 |
| 4 | 3494 | 0x666EE3F | `mov rsi,[rdi+8]` | [rdi+8] qword → rsi | |
| 5 | 3495 | 0x666EE43 | `test rsi,rsi` | — | |
| 6 | 3496 | 0x666EE46 | `je short 0x666EE30` | — | branch exit 0x666EE30 |
| 7 | 3497 | 0x666EE48 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 8 | 3498 | 0x666EE4C | `jne short 0x666EE30` | — | branch exit 0x666EE30 |
| 9 | 3499 | 0x666EE4E | `mov rax,[rsi]` | [rsi] qword → rax | |
| 10 | 3500 | 0x666EE51 | `mov rax,[rax]` | [rax] qword → rax | |
| 11 | 3501 | 0x666EE54 | `mov rcx,rsi` | — | |
| 12 | 3502 | 0x666EE57 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 13 | 3503 | 0x666EE5D | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 14 | 3504 | 0x666EE61 | `jne short 0x666EE30` | — | branch exit 0x666EE30 |
| 15 | 3505 | 0x666EE63 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 16 | 3506 | 0x666EE66 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 17 | 3507 | 0x666EE6A | `mov rcx,rsi` | — | |
| 18 | 3508 | 0x666EE6D | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 19 | 3509 | 0x666EE73 | `jmp short 0x666EE30` | — | branch exit 0x666EE30 |
| 20 | 3510 | 0x666EE75 | `cmp byte ptr [rbp+0x380],1` | — | |
| 21 | 3511 | 0x666EE7C | `jne short 0x666EEBE` | — | branch exit 0x666EEBE |
| 22 | 3512 | 0x666EE7E | `mov rcx,[rbp+0x340]` | — | |
| 23 | 3513 | 0x666EE85 | `test rcx,rcx` | — | |
| 24 | 3514 | 0x666EE88 | `je short 0x666EEBE` | — | branch exit 0x666EEBE |
| 25 | 3515 | 0x666EE8A | `mov rdx,[rbp+0x350]` | — | |
| 26 | 3516 | 0x666EE91 | `sub rdx,rcx` | — | |
| 27 | 3517 | 0x666EE94 | `cmp rdx,0x1000` | — | |
| 28 | 3518 | 0x666EE9B | `jb short 0x666EEB9` | — | branch exit 0x666EEB9 |
| 29 | 3519 | 0x666EE9D | `mov rax,[rcx-8]` | [rcx-8] qword → rax | |
| 30 | 3520 | 0x666EEA1 | `add rcx,0xFFFFFFFFFFFFFFF8` | — | |
| 31 | 3521 | 0x666EEA5 | `sub rcx,rax` | — | |
| 32 | 3522 | 0x666EEA8 | `cmp rcx,0x20` | — | |
| 33 | 3523 | 0x666EEAC | `jae 0x6670A7A` | — | branch exit 0x6670A7A |
| 34 | 3524 | 0x666EEB2 | `or rdx,0x27` | — | |
| 35 | 3525 | 0x666EEB6 | `mov rcx,rax` | — | |
| 36 | 3526 | 0x666EEB9 | `call 0xE935700` | — | call 0xE935700 |
| 37 | 3527 | 0x666EEBE | `mov rsi,[rbp+0x5C8]` | — | |
| 38 | 3528 | 0x666EEC5 | `test rsi,rsi` | — | |
| 39 | 3529 | 0x666EEC8 | `jne 0x666FB88` | — | branch exit 0x666FB88 |
| 40 | 3530 | 0x666EECE | `jmp 0x6670032` | — | branch exit 0x6670032 |
| 41 | 3531 | 0x666EED3 | `mov rax,[rax]` | [rax] qword → rax | |
| 42 | 3532 | 0x666EED6 | `mov [rbp+0x3F0],rax` | — | |
| 43 | 3533 | 0x666EEDD | `mov qword ptr [rbp+0x3F8],0` | — | |
| 44 | 3534 | 0x666EEE8 | `mov rax,[rbp+0x3F0]` | — | |
| 45 | 3535 | 0x666EEEF | `mov rax,[rax+0x18]` | [rax+0x18] qword → rax | |
| 46 | 3536 | 0x666EEF3 | `mov rax,[rax]` | [rax] qword → rax | |
| 47 | 3537 | 0x666EEF6 | `mov [rbp],rax` | — | |
| 48 | 3538 | 0x666EEFA | `lea rbx,[rbp+8]` | — | |
| 49 | 3539 | 0x666EEFE | `mov r8,[r14]` | — | |
| 50 | 3540 | 0x666EF01 | `mov rdx,[rax+0x170]` | [rax+0x170] qword → rdx | |
| 51 | 3541 | 0x666EF08 | `mov rcx,rbx` | — | |
| 52 | 3542 | 0x666EF0B | `call 0xE86B370` | — | call 0xE86B370 |
| 53 | 3543 | 0x666EF10 | `nop` | — | |
| 54 | 3544 | 0x666EF11 | `mov [rbp+0x80],r14` | — | |
| 55 | 3545 | 0x666EF18 | `mov rsi,[rbp+0x3F8]` | — | |
| 56 | 3546 | 0x666EF1F | `test rsi,rsi` | — | |
| 57 | 3547 | 0x666EF22 | `je short 0x666EF4F` | — | branch exit 0x666EF4F |
| 58 | 3548 | 0x666EF24 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 59 | 3549 | 0x666EF28 | `jne short 0x666EF4F` | — | branch exit 0x666EF4F |
| 60 | 3550 | 0x666EF2A | `mov rax,[rsi]` | [rsi] qword → rax | |

**Description-field reads in this block:** none directly off description pointer r12/r13. Line 3540 `mov rdx,[rax+0x170]` where rax=[rbp+0x3F0] chain load [I], not description. Branch exits: 0x666EE75, 0x666EE30, 0x666EEBE, 0x666EEB9, 0x666FB88, 0x6670032, 0x666EF4F. Calls: qword ptr [0xF99FFA0] (3502, 3508), 0xE935700 (3526), 0xE86B370 (3542).

## Block 11 — listing lines 3551..3610 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3551 | 0x666EF2D | `mov rax,[rax]` | [rax] qword → rax | |
| 2 | 3552 | 0x666EF30 | `mov rcx,rsi` | — | |
| 3 | 3553 | 0x666EF33 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 4 | 3554 | 0x666EF39 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 5 | 3555 | 0x666EF3D | `jne short 0x666EF4F` | — | branch exit 0x666EF4F |
| 6 | 3556 | 0x666EF3F | `mov rax,[rsi]` | [rsi] qword → rax | |
| 7 | 3557 | 0x666EF42 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 8 | 3558 | 0x666EF46 | `mov rcx,rsi` | — | |
| 9 | 3559 | 0x666EF49 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 10 | 3560 | 0x666EF4F | `mov rax,[rbp+0x668]` | — | |
| 11 | 3561 | 0x666EF56 | `mov r9,[rax]` | [rax] qword → r9 (rax=[rbp+0x668] [I]) | |
| 12 | 3562 | 0x666EF59 | `lea rcx,[rbp+0x1D0]` | — | |
| 13 | 3563 | 0x666EF60 | `mov r8,rbp` | — | |
| 14 | 3564 | 0x666EF63 | `mov rdx,r15` | — | |
| 15 | 3565 | 0x666EF66 | `call 0xBBD7F70` | — | call 0xBBD7F70 |
| 16 | 3566 | 0x666EF6B | `nop` | — | |
| 17 | 3567 | 0x666EF6C | `cmp byte ptr [rbp+0x228],0` | — | |
| 18 | 3568 | 0x666EF73 | `je 0x66708EE` | — | branch exit 0x66708EE |
| 19 | 3569 | 0x666EF79 | `mov rax,[rbp+0x668]` | — | |
| 20 | 3570 | 0x666EF80 | `lea r9,[rax+8]` | — | |
| 21 | 3571 | 0x666EF84 | `lea rax,[rbp+0x3E0]` | — | |
| 22 | 3572 | 0x666EF8B | `mov [rsp+0x20],rax` | — | |
| 23 | 3573 | 0x666EF90 | `mov dword ptr [rsp+0x28],0` | — | |
| 24 | 3574 | 0x666EF98 | `lea r8,[0x129F8318]` | — | |
| 25 | 3575 | 0x666EF9F | `mov rcx,rbp` | — | |
| 26 | 3576 | 0x666EFA2 | `lea rdx,[rbp+0x3F0]` | — | |
| 27 | 3577 | 0x666EFA9 | `call 0xBCAB8F0` | — | call 0xBCAB8F0 |
| 28 | 3578 | 0x666EFAD | `nop` | — | |
| 29 | 3579 | 0x666EFAF | `mov eax,[0x128767C8]` | — | |
| 30 | 3580 | 0x666EFB5 | `mov rcx,gs:[0x58]` | — | |
| 31 | 3581 | 0x666EFBE | `mov rax,[rcx+rax*8]` | — | |
| 32 | 3582 | 0x666EFC2 | `mov eax,[rax+4]` | — | |
| 33 | 3583 | 0x666EFC8 | `cmp dword ptr [rbp+0x670],1` | — | |
| 34 | 3584 | 0x666EFCF | `jne 0x666F2EB` | — | branch exit 0x666F2EB |
| 35 | 3585 | 0x666EFD5 | `cmp [0x129F9280],eax` | — | |
| 36 | 3586 | 0x666EFDB | `jg 0x6671603` | — | branch exit 0x6671603 |
| 37 | 3587 | 0x666EFE1 | `mov rcx,[rbp+0x648]` | — | |
| 38 | 3588 | 0x666EFE8 | `add rcx,0x430` | — | |
| 39 | 3589 | 0x666EFEF | `call 0x66A0820` | — | call 0x66A0820 |
| 40 | 3590 | 0x666EFF4 | `lea rsi,[rbp+0x3F0]` | — | |
| 41 | 3591 | 0x666EFFB | `mov rcx,rsi` | — | |
| 42 | 3592 | 0x666EFFE | `mov rdx,rax` | — | |
| 43 | 3593 | 0x666F001 | `call 0x6692D10` | — | call 0x6692D10 |
| 44 | 3594 | 0x666F006 | `nop` | — | |
| 45 | 3595 | 0x666F007 | `mov dword ptr [rsp+0x28],0` | — | |
| 46 | 3596 | 0x666F00F | `mov byte ptr [rsp+0x20],1` | — | |
| 47 | 3597 | 0x666F014 | `lea r8,[0x129F9278]` | — | |
| 48 | 3598 | 0x666F01B | `mov rcx,rbp` | — | |
| 49 | 3599 | 0x666F01E | `lea rdx,[rbp+0x340]` | — | |
| 50 | 3600 | 0x666F025 | `mov r9,rsi` | — | |
| 51 | 3601 | 0x666F028 | `call 0xBCAC390` | — | call 0xBCAC390 |
| 52 | 3602 | 0x666F02D | `nop` | — | |
| 53 | 3603 | 0x666F02E | `lea rcx,[rbp+0x3F0]` | — | |
| 54 | 3604 | 0x666F035 | `call 0x7E6D0` | — | call 0x7E6D0 |
| 55 | 3605 | 0x666F03A | `jmp 0x666F327` | — | branch exit 0x666F327 |
| 56 | 3606 | 0x666F03F | `mov rdi,0xCBF29CE484222325` | — | |
| 57 | 3607 | 0x666F049 | `jmp 0x666F0D5` | — | branch exit 0x666F0D5 |
| 58 | 3608 | 0x666F04E | `mov rdx,r12` | — | |
| 59 | 3609 | 0x666F051 | `and rdx,0xFFFFFFFFFFFFFFFC` | — | |
| 60 | 3610 | 0x666F055 | `mov rdi,0xCBF29CE484222325` | — | |

**Description-field reads in this block:** none directly off description pointer r12; line 3608 `mov rdx,r12` copies description pointer but no field read yet. Branch exits: 0x666EF4F, 0x66708EE, 0x666F2EB, 0x6671603, 0x666F327, 0x666F0D5. Calls: qword ptr [0xF99FFA0] (3553, 3559), 0xBBD7F70 (3565), 0xBCAB8F0 (3577), 0x66A0820 (3589), 0x6692D10 (3593), 0xBCAC390 (3601), 0x7E6D0 (3604).

## Block 12 — listing lines 3611..3670 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3611 | 0x666F05F | `xor ecx,ecx` | — | |
| 2 | 3612 | 0x666F061 | `mov r8,0x100000001B3` | — | |
| 3 | 3613 | 0x666F06B | `movzx r9d,byte ptr [r13+rcx]` | — | |
| 4 | 3614 | 0x666F071 | `xor r9,rdi` | — | |
| 5 | 3615 | 0x666F074 | `imul r9,r8` | — | |
| 6 | 3616 | 0x666F078 | `movzx r10d,byte ptr [r13+rcx+1]` | — | |
| 7 | 3617 | 0x666F07E | `xor r10,r9` | — | |
| 8 | 3618 | 0x666F081 | `imul r10,r8` | — | |
| 9 | 3619 | 0x666F085 | `movzx r9d,byte ptr [r13+rcx+2]` | — | |
| 10 | 3620 | 0x666F08B | `xor r9,r10` | — | |
| 11 | 3621 | 0x666F08E | `imul r9,r8` | — | |
| 12 | 3622 | 0x666F092 | `movzx edi,byte ptr [r13+rcx+3]` | — | |
| 13 | 3623 | 0x666F098 | `xor rdi,r9` | — | |
| 14 | 3624 | 0x666F09B | `imul rdi,r8` | — | |
| 15 | 3625 | 0x666F09F | `add rcx,4` | — | |
| 16 | 3626 | 0x666F0A3 | `cmp rdx,rcx` | — | |
| 17 | 3627 | 0x666F0A6 | `jne short 0x666F06B` | — | branch exit 0x666F06B |
| 18 | 3628 | 0x666F0A8 | `test rax,rax` | — | |
| 19 | 3629 | 0x666F0AB | `je short 0x666F0D5` | — | branch exit 0x666F0D5 |
| 20 | 3630 | 0x666F0AD | `add rcx,r13` | — | |
| 21 | 3631 | 0x666F0B0 | `xor edx,edx` | — | |
| 22 | 3632 | 0x666F0B2 | `mov r8,0x100000001B3` | — | |
| 23 | 3633 | 0x666F0BC | `mov r9,rdi` | — | |
| 24 | 3634 | 0x666F0BF | `movzx edi,byte ptr [rcx+rdx]` | — | |
| 25 | 3635 | 0x666F0C3 | `xor rdi,r9` | — | |
| 26 | 3636 | 0x666F0C6 | `imul rdi,r8` | — | |
| 27 | 3637 | 0x666F0CA | `inc rdx` | — | |
| 28 | 3638 | 0x666F0CD | `mov r9,rdi` | — | |
| 29 | 3639 | 0x666F0D0 | `cmp rax,rdx` | — | |
| 30 | 3640 | 0x666F0D3 | `jne short 0x666F0BF` | — | branch exit 0x666F0BF |
| 31 | 3641 | 0x666F0D5 | `mov rcx,[rbp+0x610]` | — | |
| 32 | 3642 | 0x666F0DC | `and rcx,rdi` | — | |
| 33 | 3643 | 0x666F0DF | `mov rax,[rbp+0x5E8]` | — | |
| 34 | 3644 | 0x666F0E6 | `mov rdx,[rbp+0x5F8]` | — | |
| 35 | 3645 | 0x666F0ED | `shl rcx,4` | — | |
| 36 | 3646 | 0x666F0F1 | `mov rsi,[rdx+rcx+8]` | — | |
| 37 | 3647 | 0x666F0F6 | `cmp rsi,rax` | — | |
| 38 | 3648 | 0x666F0F9 | `je short 0x666F156` | — | branch exit 0x666F156 |
| 39 | 3649 | 0x666F0FB | `mov rbx,[rdx+rcx]` | — | |
| 40 | 3650 | 0x666F0FF | `test r12,r12` | — | |
| 41 | 3651 | 0x666F102 | `je short 0x666F143` | — | branch exit 0x666F143 |
| 42 | 3652 | 0x666F104 | `cmp r12,[rsi+0x20]` | [rsi+0x20] qword | |
| 43 | 3653 | 0x666F108 | `jne short 0x666F12E` | — | branch exit 0x666F12E |
| 44 | 3654 | 0x666F10A | `cmp qword ptr [rsi+0x28],0x10` | [rsi+0x28] qword | |
| 45 | 3655 | 0x666F10F | `jb short 0x666F117` | — | branch exit 0x666F117 |
| 46 | 3656 | 0x666F111 | `mov rdx,[rsi+0x10]` | [rsi+0x10] qword → rdx | |
| 47 | 3657 | 0x666F115 | `jmp short 0x666F11B` | — | branch exit 0x666F11B |
| 48 | 3658 | 0x666F117 | `lea rdx,[rsi+0x10]` | — | |
| 49 | 3659 | 0x666F11B | `mov rcx,r13` | — | |
| 50 | 3660 | 0x666F11E | `mov r8,r12` | — | |
| 51 | 3661 | 0x666F121 | `call 0xEEC6EB0` | — | call 0xEEC6EB0 |
| 52 | 3662 | 0x666F126 | `test eax,eax` | — | |
| 53 | 3663 | 0x666F128 | `je 0x666FC88` | — | branch exit 0x666FC88 |
| 54 | 3664 | 0x666F12E | `cmp rsi,rbx` | — | |
| 55 | 3665 | 0x666F131 | `je short 0x666F153` | — | branch exit 0x666F153 |
| 56 | 3666 | 0x666F133 | `mov rsi,[rsi+8]` | [rsi+8] qword → rsi | |
| 57 | 3667 | 0x666F137 | `cmp r12,[rsi+0x20]` | [rsi+0x20] qword | |
| 58 | 3668 | 0x666F13B | `je short 0x666F10A` | — | branch exit 0x666F10A |
| 59 | 3669 | 0x666F13D | `jmp short 0x666F12E` | — | branch exit 0x666F12E |
| 60 | 3670 | 0x666F13F | `mov rsi,[rsi+8]` | [rsi+8] qword → rsi | |

**Description-field reads in this block:** none directly off description pointer r12; r12 is compared against chain objects [rsi+0x20], [rsi+0x28] [V] (rsi = chain bucket head, not description). Branch exits: 0x666F06B, 0x666F0D5, 0x666F0BF, 0x666F156, 0x666F143, 0x666F12E, 0x666F117, 0x666F11B, 0x666FC88, 0x666F153, 0x666F10A. Calls: 0xEEC6EB0 (3661).

## Block 13 — listing lines 3671..3730 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3671 | 0x666F143 | `cmp qword ptr [rsi+0x20],0` | [rsi+0x20] qword | |
| 2 | 3672 | 0x666F148 | `je 0x666FC88` | — | branch exit 0x666FC88 |
| 3 | 3673 | 0x666F14E | `cmp rsi,rbx` | — | |
| 4 | 3674 | 0x666F151 | `jne short 0x666F13F` | — | branch exit 0x666F13F |
| 5 | 3675 | 0x666F153 | `mov rax,rsi` | — | |
| 6 | 3676 | 0x666F156 | `mov rcx,[rbp+0x5F0]` | — | |
| 7 | 3677 | 0x666F15D | `mov rdx,0x3333333333333333` | — | |
| 8 | 3678 | 0x666F167 | `cmp rcx,rdx` | — | |
| 9 | 3679 | 0x666F16A | `je 0x66711EC` | — | branch exit 0x66711EC |
| 10 | 3680 | 0x666F170 | `inc rcx` | — | |
| 11 | 3681 | 0x666F173 | `js short 0x666F17F` | — | branch exit 0x666F17F |
| 12 | 3682 | 0x666F175 | `xorps xmm0,xmm0` | — | |
| 13 | 3683 | 0x666F178 | `cvtsi2ss xmm0,rcx` | — | |
| 14 | 3684 | 0x666F17D | `jmp short 0x666F197` | — | branch exit 0x666F197 |
| 15 | 3685 | 0x666F17F | `mov rdx,rcx` | — | |
| 16 | 3686 | 0x666F182 | `shr rdx,1` | — | |
| 17 | 3687 | 0x666F185 | `and ecx,1` | — | |
| 18 | 3688 | 0x666F188 | `or rcx,rdx` | — | |
| 19 | 3689 | 0x666F18B | `xorps xmm0,xmm0` | — | |
| 20 | 3690 | 0x666F18E | `cvtsi2ss xmm0,rcx` | — | |
| 21 | 3691 | 0x666F193 | `addss xmm0,xmm0` | — | |
| 22 | 3692 | 0x666F197 | `movss xmm1,[rbp+0x5E0]` | — | |
| 23 | 3693 | 0x666F19F | `mov rsi,[rbp+0x618]` | — | |
| 24 | 3694 | 0x666F1A6 | `test rsi,rsi` | — | |
| 25 | 3695 | 0x666F1A9 | `js short 0x666F1B2` | — | branch exit 0x666F1B2 |
| 26 | 3696 | 0x666F1AB | `cvtsi2ss xmm2,rsi` | — | |
| 27 | 3697 | 0x666F1B0 | `jmp short 0x666F1C9` | — | branch exit 0x666F1C9 |
| 28 | 3698 | 0x666F1B2 | `mov rcx,rsi` | — | |
| 29 | 3699 | 0x666F1B5 | `shr rcx,1` | — | |
| 30 | 3700 | 0x666F1B8 | `mov edx,esi` | — | |
| 31 | 3701 | 0x666F1BA | `and edx,1` | — | |
| 32 | 3702 | 0x666F1BD | `or rdx,rcx` | — | |
| 33 | 3703 | 0x666F1C0 | `cvtsi2ss xmm2,rdx` | — | |
| 34 | 3704 | 0x666F1C5 | `addss xmm2,xmm2` | — | |
| 35 | 3705 | 0x666F1C9 | `movaps xmm3,xmm0` | — | |
| 36 | 3706 | 0x666F1CC | `divss xmm3,xmm2` | — | |
| 37 | 3707 | 0x666F1D0 | `ucomiss xmm3,xmm1` | — | |
| 38 | 3708 | 0x666F1D3 | `jbe 0x666FC25` | — | branch exit 0x666FC25 |
| 39 | 3709 | 0x666F1D9 | `divss xmm0,xmm1` | — | |
| 40 | 3710 | 0x666F1DD | `call 0xEEC73F0` | — | call 0xEEC73F0 |
| 41 | 3711 | 0x666F1E2 | `cvttss2si rax,xmm0` | — | |
| 42 | 3712 | 0x666F1E7 | `mov rcx,rax` | — | |
| 43 | 3713 | 0x666F1EA | `subss xmm0,[0xEEE6700]` | — | |
| 44 | 3714 | 0x666F1F2 | `cvttss2si rdx,xmm0` | — | |
| 45 | 3715 | 0x666F1F7 | `sar rcx,0x3F` | — | |
| 46 | 3716 | 0x666F1FB | `and rdx,rcx` | — | |
| 47 | 3717 | 0x666F1FE | `or rdx,rax` | — | |
| 48 | 3718 | 0x666F201 | `cmp rdx,9` | — | |
| 49 | 3719 | 0x666F205 | `mov eax,8` | — | |
| 50 | 3720 | 0x666F20A | `cmovae rax,rdx` | — | |
| 51 | 3721 | 0x666F20E | `cmp rsi,rax` | — | |
| 52 | 3722 | 0x666F211 | `jae short 0x666F230` | — | branch exit 0x666F230 |
| 53 | 3723 | 0x666F213 | `lea rcx,[rsi*8]` | — | |
| 54 | 3724 | 0x666F21B | `cmp rcx,rax` | — | |
| 55 | 3725 | 0x666F21E | `cmovbe rcx,rax` | — | |
| 56 | 3726 | 0x666F222 | `cmp rsi,0x200` | — | |
| 57 | 3727 | 0x666F229 | `cmovae rcx,rax` | — | |
| 58 | 3728 | 0x666F22D | `mov rsi,rcx` | — | |
| 59 | 3729 | 0x666F230 | `lea rcx,[rbp+0x5E0]` | — | |
| 60 | 3730 | 0x666F237 | `mov rdx,rsi` | — | |

**Description-field reads in this block:** none directly off description pointer r12/r13. Branch exits: 0x666FC88, 0x666F13F, 0x66711EC, 0x666F17F, 0x666F197, 0x666F1B2, 0x666F1C9, 0x666FC25, 0x666F230. Calls: 0xEEC73F0 (3710).

## Block 14 — listing lines 3731..3790 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3731 | 0x666F23A | `call 0x77D80` | — | call 0x77D80 |
| 2 | 3733 | 0x666F240 | `mov rcx,[rbp+0x610]` | — | |
| 3 | 3734 | 0x666F247 | `and rcx,rdi` | — | |
| 4 | 3735 | 0x666F24A | `mov rax,[rbp+0x5E8]` | — | |
| 5 | 3736 | 0x666F251 | `mov rdx,[rbp+0x5F8]` | — | |
| 6 | 3737 | 0x666F258 | `shl rcx,4` | — | |
| 7 | 3738 | 0x666F25C | `mov rbx,[rdx+rcx+8]` | — | |
| 8 | 3739 | 0x666F261 | `cmp rbx,rax` | — | |
| 9 | 3740 | 0x666F264 | `je 0x666FC25` | — | branch exit 0x666FC25 |
| 10 | 3741 | 0x666F26A | `mov rsi,[r14+0x20]` | — | |
| 11 | 3742 | 0x666F26E | `cmp qword ptr [r14+0x28],0x10` | — | |
| 12 | 3743 | 0x666F273 | `jb short 0x666F287` | — | branch exit 0x666F287 |
| 13 | 3744 | 0x666F275 | `mov rax,[rbp+0x658]` | — | |
| 14 | 3745 | 0x666F27C | `mov rax,[rax+0x10]` | — | |
| 15 | 3746 | 0x666F280 | `mov [rbp+0x660],rax` | — | |
| 16 | 3747 | 0x666F287 | `mov r15,[rdx+rcx]` | — | |
| 17 | 3748 | 0x666F28B | `test rsi,rsi` | — | |
| 18 | 3749 | 0x666F28E | `je short 0x666F2DC` | — | branch exit 0x666F2DC |
| 19 | 3750 | 0x666F290 | `cmp rsi,[rbx+0x20]` | [rbx+0x20] qword | |
| 20 | 3751 | 0x666F294 | `jne short 0x666F2BA` | — | branch exit 0x666F2BA |
| 21 | 3752 | 0x666F296 | `cmp qword ptr [rbx+0x28],0x10` | [rbx+0x28] qword | |
| 22 | 3753 | 0x666F29B | `jb short 0x666F2A3` | — | branch exit 0x666F2A3 |
| 23 | 3754 | 0x666F29D | `mov rdx,[rbx+0x10]` | [rbx+0x10] qword → rdx | |
| 24 | 3755 | 0x666F2A1 | `jmp short 0x666F2A7` | — | branch exit 0x666F2A7 |
| 25 | 3756 | 0x666F2A3 | `lea rdx,[rbx+0x10]` | — | |
| 26 | 3757 | 0x666F2A7 | `mov rcx,[rbp+0x660]` | — | |
| 27 | 3758 | 0x666F2AE | `mov r8,rsi` | — | |
| 28 | 3759 | 0x666F2B1 | `call 0xEEC6EB0` | — | call 0xEEC6EB0 |
| 29 | 3760 | 0x666F2B6 | `test eax,eax` | — | |
| 30 | 3761 | 0x666F2B8 | `je short 0x666F2E3` | — | branch exit 0x666F2E3 |
| 31 | 3762 | 0x666F2BA | `cmp rbx,r15` | — | |
| 32 | 3763 | 0x666F2BD | `je 0x666FC1B` | — | branch exit 0x666FC1B |
| 33 | 3764 | 0x666F2C3 | `mov rbx,[rbx+8]` | [rbx+8] qword → rbx | |
| 34 | 3765 | 0x666F2C7 | `cmp rsi,[rbx+0x20]` | [rbx+0x20] qword | |
| 35 | 3766 | 0x666F2CB | `je short 0x666F296` | — | branch exit 0x666F296 |
| 36 | 3767 | 0x666F2CD | `jmp short 0x666F2BA` | — | branch exit 0x666F2BA |
| 37 | 3768 | 0x666F2CF | `cmp rbx,r15` | — | |
| 38 | 3769 | 0x666F2D2 | `je 0x666FC1B` | — | branch exit 0x666FC1B |
| 39 | 3770 | 0x666F2D8 | `mov rbx,[rbx+8]` | [rbx+8] qword → rbx | |
| 40 | 3771 | 0x666F2DC | `cmp qword ptr [rbx+0x20],0` | [rbx+0x20] qword | |
| 41 | 3772 | 0x666F2E1 | `jne short 0x666F2CF` | — | branch exit 0x666F2CF |
| 42 | 3773 | 0x666F2E3 | `mov rax,[rbx]` | [rbx] qword → rax | |
| 43 | 3774 | 0x666F2E6 | `jmp 0x666FC1E` | — | branch exit 0x666FC1E |
| 44 | 3775 | 0x666F2EB | `cmp [0x129F9290],eax` | — | |
| 45 | 3776 | 0x666F2F1 | `jg 0x6671675` | — | branch exit 0x6671675 |
| 46 | 3777 | 0x666F2F7 | `mov rax,[rbp+0x668]` | — | |
| 47 | 3778 | 0x666F2FE | `movups xmm0,[rax+0x64]` | [rax+0x64] 16 bytes → xmm0 (rax=[rbp+0x668] [I], not description) | |
| 48 | 3779 | 0x666F302 | `movaps [rbp+0x3F0],xmm0` | — | |
| 49 | 3780 | 0x666F309 | `lea r8,[0x129F9288]` | — | |
| 50 | 3781 | 0x666F310 | `mov rcx,rbp` | — | |
| 51 | 3782 | 0x666F313 | `lea rdx,[rbp+0x340]` | — | |
| 52 | 3783 | 0x666F31A | `lea r9,[rbp+0x3F0]` | — | |
| 53 | 3784 | 0x666F321 | `call 0x66A0EC0` | — | call 0x66A0EC0 |
| 54 | 3785 | 0x666F326 | `nop` | — | |
| 55 | 3786 | 0x666F327 | `mov rax,[rbp+0x668]` | — | |
| 56 | 3787 | 0x666F32E | `movups xmm0,[rax+0x18]` | [rax+0x18] 16 bytes → xmm0 (rax=[rbp+0x668] [I]) | |
| 57 | 3788 | 0x666F332 | `movaps [rbp+0x340],xmm0` | — | |
| 58 | 3789 | 0x666F339 | `movups xmm1,[rax+0x28]` | [rax+0x28] 16 bytes → xmm1 [I] | |
| 59 | 3790 | 0x666F33D | `movaps [rbp+0x350],xmm1` | — | |

**Description-field reads in this block:** none directly off description pointer r12; reads at line 3778 `movups xmm0,[rax+0x64]` and line 3787 `movups xmm0,[rax+0x18]` use rax=[rbp+0x668], a local/heap object [I], not the description. Branch exits: 0x666FC25, 0x666F287, 0x666F2DC, 0x666F2BA, 0x666F2A3, 0x666F2A7, 0x666F2E3, 0x666FC1B, 0x666F296, 0x666F2CF, 0x666FC1E, 0x6671675. Calls: 0x77D80 (3731), 0xEEC6EB0 (3759), 0x66A0EC0 (3784).

## Block 15 — listing lines 3791..3850 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3791 | 0x666F344 | `movups xmm2,[rax+0x38]` | [rax+0x38] 16 bytes → xmm2 [I] (rax=[rbp+0x668]) | |
| 2 | 3792 | 0x666F348 | `movaps [rbp+0x360],xmm2` | — | |
| 3 | 3793 | 0x666F34F | `movups xmm3,[rax+0x48]` | [rax+0x48] 16 bytes → xmm3 [I] | |
| 4 | 3794 | 0x666F353 | `movaps [rbp+0x370],xmm3` | — | |
| 5 | 3795 | 0x666F35A | `mov byte ptr [rbp+0x380],0` | — | |
| 6 | 3796 | 0x666F361 | `cmp byte ptr [rbp+0x228],0` | — | |
| 7 | 3797 | 0x666F368 | `je 0x66715F7` | — | branch exit 0x66715F7 |
| 8 | 3798 | 0x666F36E | `mov si,[rax+0x88]` | [rax+0x88] word → si [I] | |
| 9 | 3799 | 0x666F375 | `movups [rbp+0x3F8],xmm0` | — | |
| 10 | 3800 | 0x666F37C | `movups [rbp+0x408],xmm1` | — | |
| 11 | 3801 | 0x666F383 | `movups [rbp+0x418],xmm2` | — | |
| 12 | 3802 | 0x666F38A | `movups [rbp+0x428],xmm3` | — | |
| 13 | 3803 | 0x666F391 | `mov byte ptr [rbp+0x438],0` | — | |
| 14 | 3804 | 0x666F398 | `movups xmm0,[rbp+0x2A0]` | — | |
| 15 | 3805 | 0x666F39F | `movups [rbp+0x440],xmm0` | — | |
| 16 | 3806 | 0x666F3A6 | `mov eax,[rbp+0x2B0]` | — | |
| 17 | 3807 | 0x666F3AC | `mov [rbp+0x450],eax` | — | |
| 18 | 3808 | 0x666F3B2 | `movzx eax,byte ptr [rbp+0x2B4]` | — | |
| 19 | 3809 | 0x666F3B9 | `mov [rbp+0x454],al` | — | |
| 20 | 3810 | 0x666F3BF | `movups xmm0,[rbp+0x2B8]` | — | |
| 21 | 3811 | 0x666F3C6 | `movups [rbp+0x458],xmm0` | — | |
| 22 | 3812 | 0x666F3CD | `movups xmm0,[rbp+0x2C8]` | — | |
| 23 | 3813 | 0x666F3D4 | `movups [rbp+0x468],xmm0` | — | |
| 24 | 3814 | 0x666F3DB | `movups xmm0,[rbp+0x2D8]` | — | |
| 25 | 3815 | 0x666F3E2 | `movups [rbp+0x478],xmm0` | — | |
| 26 | 3816 | 0x666F3E9 | `movups xmm0,[rbp+0x2E7]` | — | |
| 27 | 3817 | 0x666F3F0 | `movups [rbp+0x487],xmm0` | — | |
| 28 | 3818 | 0x666F3F7 | `mov rax,[rbp]` | — | |
| 29 | 3819 | 0x666F3FB | `mov [rbp+0x498],rax` | — | |
| 30 | 3820 | 0x666F402 | `lea rcx,[rbp+0x4A0]` | — | |
| 31 | 3821 | 0x666F409 | `mov rdx,rbx` | — | |
| 32 | 3822 | 0x666F40C | `call 0xE869FF0` | — | call 0xE869FF0 |
| 33 | 3823 | 0x666F411 | `nop` | — | |
| 34 | 3824 | 0x666F412 | `lea rax,[rbp+0x3F8]` | — | |
| 35 | 3825 | 0x666F419 | `lea r10,[rbp+0x440]` | — | |
| 36 | 3826 | 0x666F420 | `lea r9,[rbp+0x498]` | — | |
| 37 | 3827 | 0x666F427 | `mov rcx,[rbp+0x80]` | — | |
| 38 | 3828 | 0x666F42E | `mov [rbp+0x518],rcx` | — | |
| 39 | 3829 | 0x666F435 | `mov qword ptr [rbp+0x80],0` | — | |
| 40 | 3830 | 0x666F440 | `lea r8,[rbp+0x520]` | — | |
| 41 | 3831 | 0x666F447 | `mov [rbp+0x520],si` | — | |
| 42 | 3833 | 0x666F44E | `lea rdx,[rbp+0x528]` | — | |
| 43 | 3834 | 0x666F455 | `movaps xmm0,[rbp+0x1D0]` | — | |
| 44 | 3835 | 0x666F45C | `movaps xmm1,[rbp+0x1E0]` | — | |
| 45 | 3836 | 0x666F463 | `mov qword ptr [rbp+0x1D8],0` | — | |
| 46 | 3837 | 0x666F46E | `movups [rbp+0x528],xmm0` | — | |
| 47 | 3838 | 0x666F475 | `xorps xmm0,xmm0` | — | |
| 48 | 3839 | 0x666F478 | `movaps [rbp+0x1E0],xmm0` | — | |
| 49 | 3840 | 0x666F47F | `movups [rbp+0x538],xmm1` | — | |
| 50 | 3841 | 0x666F486 | `mov rcx,[rbp+0x1F0]` | — | |
| 51 | 3842 | 0x666F48D | `mov [rbp+0x548],rcx` | — | |
| 52 | 3843 | 0x666F494 | `mov byte ptr [rbp+0x560],0xFF` | — | |
| 53 | 3844 | 0x666F49B | `movzx ecx,byte ptr [rbp+0x208]` | — | |
| 54 | 3845 | 0x666F4A2 | `cmp rcx,3` | — | |
| 55 | 3846 | 0x666F4A6 | `ja 0x66707BD` | — | branch exit 0x66707BD |
| 56 | 3847 | 0x666F4AC | `lea r11,[rbp+0x550]` | — | |
| 57 | 3848 | 0x666F4B3 | `lea rsi,[0xF2BF4C0]` | — | |
| 58 | 3849 | 0x666F4BA | `movsxd rbx,[rsi+rcx*4]` | — | |
| 59 | 3850 | 0x666F4BE | `add rbx,rsi` | — | |

**Description-field reads in this block:** none directly off description pointer r12; reads at lines 3791-3798 use rax=[rbp+0x668] (local object [I], not description). Branch exits: 0x66715F7, 0x66707BD. Calls: 0xE869FF0 (3822).

## Block 16 — listing lines 3851..3910 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3851 | 0x666F4C1 | `jmp rbx` | — | indirect branch exit (target in rbx) |
| 2 | 3854 | 0x666F4D6 | `xor ecx,ecx` | — | |
| 3 | 3855 | 0x666F4D8 | `mov rdx,[rbp+0x368]` | — | |
| 4 | 3856 | 0x666F4DF | `mov [rbp+0x550],rdx` | — | |
| 5 | 3857 | 0x666F4E6 | `mov [rbp+0x558],rcx` | — | |
| 6 | 3858 | 0x666F4ED | `mov [rbp+0x560],al` | — | |
| 7 | 3859 | 0x666F4F3 | `mov rax,[rbp+0x390]` | — | |
| 8 | 3860 | 0x666F4FA | `mov [rbp+0x578],rax` | — | |
| 9 | 3861 | 0x666F501 | `movaps xmm0,[rbp+0x380]` | — | |
| 10 | 3862 | 0x666F508 | `movups [rbp+0x568],xmm0` | — | |
| 11 | 3863 | 0x666F50F | `mov ecx,0x9D0` | — | |
| 12 | 3864 | 0x666F514 | `add rcx,[r12+0x10]` | **[r12+0x10] qword → rcx: description+0x10 read [V]** (r12 = description pointer since line 3115) | |
| 13 | 3865 | 0x666F519 | `call 0x5ABA5C0` | — | call 0x5ABA5C0 |
| 14 | 3867 | 0x666F51E | `nop` | — | |
| 15 | 3868 | 0x666F51F | `mov rsi,rax` | — | |
| 16 | 3869 | 0x666F522 | `lea rdx,[rbp+0x528]` | — | |
| 17 | 3870 | 0x666F529 | `xorps xmm0,xmm0` | — | |
| 18 | 3871 | 0x666F52C | `movups [rbp+0xB8],xmm0` | — | |
| 19 | 3872 | 0x666F533 | `movups [rbp+0xA8],xmm0` | — | |
| 20 | 3873 | 0x666F53A | `movups [rbp+0x98],xmm0` | — | |
| 21 | 3874 | 0x666F541 | `movups [rbp+0x88],xmm0` | — | |
| 22 | 3875 | 0x666F548 | `movups [rbp+0x78],xmm0` | — | |
| 23 | 3876 | 0x666F54C | `movups [rbp+0x68],xmm0` | — | |
| 24 | 3877 | 0x666F550 | `movups [rbp+0x58],xmm0` | — | |
| 25 | 3878 | 0x666F554 | `movups [rbp+0x48],xmm0` | — | |
| 26 | 3879 | 0x666F558 | `movups [rbp+0x38],xmm0` | — | |
| 27 | 3880 | 0x666F560 | `movups [rbp+0x28],xmm0` | — | |
| 28 | 3881 | 0x666F564 | `movups [rbp+0x18],xmm0` | — | |
| 29 | 3882 | 0x666F568 | `lea rcx,[rax+0x780]` | [rax+0x780] lea (rax=rsi=[rbp+0x668] after call [I]) | |
| 30 | 3883 | 0x666F56F | `call 0x675F3B0` | — | call 0x675F3B0 |
| 31 | 3884 | 0x666F574 | `nop` | — | |
| 32 | 3885 | 0x666F575 | `mov qword ptr [rbp],0x1000` | — | |
| 33 | 3886 | 0x666F57D | `mov eax,[rsi+0x788]` | **[rsi+0x788] dword → eax [V]** (rsi=return of call 0x5ABA5C0 [I] — [I] whether rsi is description; treated as not-description unless proven) | |
| 34 | 3887 | 0x666F583 | `sub eax,[rsi+0x780]` | **[rsi+0x780] dword → sub from eax [V]** | |
| 35 | 3888 | 0x666F589 | `shr eax,3` | — | |
| 36 | 3889 | 0x666F58C | `imul eax,0xFFFF8BA3` | — | |
| 37 | 3890 | 0x666F592 | `dec eax` | — | |
| 38 | 3891 | 0x666F594 | `mov [rbp+0x28],ax` | — | |
| 39 | 3892 | 0x666F598 | `mov rcx,[0x1233E1B0]` | — | |
| 40 | 3893 | 0x666F59F | `mov rax,[rcx]` | [rcx] qword → rax | |
| 41 | 3894 | 0x666F5A2 | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 42 | 3895 | 0x666F5A6 | `mov dl,0x4A` | — | |
| 43 | 3896 | 0x666F5A8 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 44 | 3897 | 0x666F5AE | `nop` | — | |
| 45 | 3898 | 0x666F5AE | `mov [rbp+0x670],al` | — | |
| 46 | 3899 | 0x666F5B5 | `mov rbx,[rsi+0x770]` | **[rsi+0x770] qword → rbx [V]** | |
| 47 | 3900 | 0x666F5BC | `cmp rbx,[rsi+0x778]` | **[rsi+0x778] qword [V]** | |
| 48 | 3901 | 0x666F5C3 | `je short 0x666F602` | — | branch exit 0x666F602 |
| 49 | 3902 | 0x666F5C5 | `mov rax,[rbp+0x4A0]` | — | |
| 50 | 3903 | 0x666F5CC | `mov [rbx],rax` | — | |
| 51 | 3904 | 0x666F5CF | `lea rcx,[rbx+8]` | — | |
| 52 | 3905 | 0x666F5D3 | `mov rdx,rdi` | — | |
| 53 | 3906 | 0x666F5D6 | `call 0xE869FF0` | — | call 0xE869FF0 |
| 54 | 3907 | 0x666F5DB | `nop` | — | |
| 55 | 3908 | 0x666F5DC | `mov rax,[rbp+0x520]` | — | |
| 56 | 3909 | 0x666F5E3 | `mov [rbx+0x80],rax` | — | |
| 57 | 3910 | 0x666F5EA | `mov qword ptr [rbp+0x520],0` | — | |

**Description-field reads in this block:** line 3864 `add rcx,[r12+0x10]` reads description+0x10 qword → rcx [V] (r12 = description pointer). Lines 3886-3900 read [rsi+0x788], [rsi+0x780], [rsi+0x770], [rsi+0x778] where rsi = return of call 0x5ABA5C0 [I] — [I] whether rsi is the description; flagged as description-candidate reads only if rsi is confirmed = description elsewhere. Branch exits: 0x666F4C1 (jmp rbx indirect), 0x66707BD, 0x666F602. Calls: 0x5ABA5C0 (3865), 0x675F3B0 (3883), qword ptr [0xF99FFA0] (3896), 0xE869FF0 (3906).

## Block 17 — listing lines 3911..3970 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3911 | 0x666F5F5 | `add qword ptr [rsi+0x770],0x88` | **[rsi+0x770] qword read-modify-write [V]** | |
| 2 | 3912 | 0x666F600 | `jmp short 0x666F619` | — | branch exit 0x666F619 |
| 3 | 3913 | 0x666F602 | `lea r8,[rbp+0x4A0]` | — | |
| 4 | 3914 | 0x666F609 | `lea rcx,[rsi+0x768]` | lea [rsi+0x768] (address only, not a read) [V] | |
| 5 | 3915 | 0x666F610 | `mov rdx,rbx` | — | |
| 6 | 3916 | 0x666F613 | `call 0x6760710` | — | call 0x6760710 |
| 7 | 3917 | 0x666F618 | `nop` | — | |
| 8 | 3918 | 0x666F619 | `mov rcx,[0x1233E1B0]` | — | |
| 9 | 3919 | 0x666F620 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 10 | 3920 | 0x666F623 | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 11 | 3921 | 0x666F627 | `movzx edx,byte ptr [rbp+0x670]` | — | |
| 12 | 3922 | 0x666F62E | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 13 | 3923 | 0x666F634 | `nop` | — | |
| 14 | 3924 | 0x666F635 | `mov eax,[rsi+0x770]` | **[rsi+0x770] dword → eax [V]** | |
| 15 | 3925 | 0x666F63B | `sub eax,[rsi+0x768]` | **[rsi+0x768] dword → sub from eax [V]** | |
| 16 | 3926 | 0x666F641 | `shr eax,3` | — | |
| 17 | 3927 | 0x666F644 | `imul eax,0xFFFFF0F1` | — | |
| 18 | 3928 | 0x666F64A | `dec eax` | — | |
| 19 | 3929 | 0x666F64C | `mov [rbp+0x2A],ax` | — | |
| 20 | 3930 | 0x666F650 | `mov rcx,[0x1233E1B0]` | — | |
| 21 | 3931 | 0x666F657 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 22 | 3932 | 0x666F65A | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 23 | 3933 | 0x666F65E | `mov dl,0x4A` | — | |
| 24 | 3934 | 0x666F660 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 25 | 3935 | 0x666F666 | `nop` | — | |
| 26 | 3936 | 0x666F667 | `mov [rbp+0x670],al` | — | |
| 27 | 3937 | 0x666F66D | `lea r8,[rbp+0x448]` | — | |
| 28 | 3938 | 0x666F674 | `mov rdx,[rsi+0x758]` | **[rsi+0x758] qword → rdx [V]** | |
| 29 | 3939 | 0x666F67B | `cmp rdx,[rsi+0x760]` | **[rsi+0x760] qword [V]** | |
| 30 | 3940 | 0x666F682 | `je short 0x666F6F8` | — | branch exit 0x666F6F8 |
| 31 | 3941 | 0x666F684 | `lea rax,[rbp+0x470]` | — | |
| 32 | 3942 | 0x666F68B | `mov ecx,[r8+0x10]` | [r8+0x10] dword → ecx (r8=[rbp+0x448] local [I]) | |
| 33 | 3943 | 0x666F68F | `mov [rdx+0x10],ecx` | — | |
| 34 | 3944 | 0x666F692 | `movups xmm0,[r8]` | — | |
| 35 | 3945 | 0x666F696 | `movups [rdx],xmm0` | — | |
| 36 | 3946 | 0x666F699 | `movzx ecx,byte ptr [rbp+0x45C]` | — | |
| 37 | 3947 | 0x666F6A0 | `mov [rdx+0x14],cl` | — | |
| 38 | 3948 | 0x666F6A3 | `movss xmm0,[rbp+0x460]` | — | |
| 39 | 3949 | 0x666F6AB | `movss [rdx+0x18],xmm0` | — | |
| 40 | 3950 | 0x666F6B0 | `movss xmm0,[rbp+0x464]` | — | |
| 41 | 3951 | 0x666F6B8 | `movss [rdx+0x1C],xmm0` | — | |
| 42 | 3952 | 0x666F6BD | `movss xmm0,[rbp+0x468]` | — | |
| 43 | 3953 | 0x666F6C5 | `movss [rdx+0x20],xmm0` | — | |
| 44 | 3954 | 0x666F6CA | `movss xmm0,[rbp+0x46C]` | — | |
| 45 | 3955 | 0x666F6D2 | `movss [rdx+0x24],xmm0` | — | |
| 46 | 3956 | 0x666F6D7 | `movups xmm0,[rax]` | — | |
| 47 | 3957 | 0x666F6DA | `movups xmm1,[rax+0x10]` | — | |
| 48 | 3958 | 0x666F6DE | `movups xmm2,[rax+0x1F]` | — | |
| 49 | 3959 | 0x666F6E2 | `movups [rdx+0x28],xmm0` | — | |
| 50 | 3960 | 0x666F6E6 | `movups [rdx+0x38],xmm1` | — | |
| 51 | 3961 | 0x666F6EA | `movups [rdx+0x47],xmm2` | — | |
| 52 | 3962 | 0x666F6EE | `add qword ptr [rsi+0x758],0x58` | **[rsi+0x758] qword read-modify-write [V]** | |
| 53 | 3963 | 0x666F6F6 | `jmp short 0x666F705` | — | branch exit 0x666F705 |
| 54 | 3964 | 0x666F6F8 | `lea rcx,[rsi+0x750]` | lea [rsi+0x750] (address only) [V] | |
| 55 | 3965 | 0x666F6FF | `call 0x6760A80` | — | call 0x6760A80 |
| 56 | 3966 | 0x666F704 | `nop` | — | |
| 57 | 3967 | 0x666F705 | `mov rcx,[0x1233E1B0]` | — | |
| 58 | 3968 | 0x666F70C | `mov rax,[rcx]` | [rcx] qword → rax | |
| 59 | 3969 | 0x666F70F | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 60 | 3970 | 0x666F713 | `movzx edx,byte ptr [rbp+0x670]` | — | |

**Description-field reads in this block (rsi = description-candidate since line 3868):** line 3911 `add qword ptr [rsi+0x770],0x88` RMW desc+0x770 [V]; line 3924 `mov eax,[rsi+0x770]` reads desc+0x770 dword → eax [V]; line 3925 `sub eax,[rsi+0x768]` reads desc+0x768 dword [V]; line 3938 `mov rdx,[rsi+0x758]` reads desc+0x758 qword → rdx [V]; line 3939 `cmp rdx,[rsi+0x760]` reads desc+0x760 qword [V]; line 3962 `add qword ptr [rsi+0x758],0x58` RMW desc+0x758 [V]. Lines 3914/3964 are lea (address computation only, no read). Branch exits: 0x666F619, 0x666F602, 0x666F6F8, 0x666F705. Calls: 0x6760710 (3916), qword ptr [0xF99FFA0] (3922, 3934), 0x6760A80 (3965).

## Block 18 — listing lines 3971..4030 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 3971 | 0x666F71A | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 2 | 3972 | 0x666F720 | `nop` | — | |
| 3 | 3973 | 0x666F721 | `mov qword ptr [rbp],0x7000` | — | |
| 4 | 3974 | 0x666F729 | `mov eax,[rsi+0x758]` | **[rsi+0x758] dword → eax [V]** | |
| 5 | 3975 | 0x666F72F | `sub eax,[rsi+0x750]` | **[rsi+0x750] dword → sub from eax [V]** | |
| 6 | 3976 | 0x666F735 | `shr eax,3` | — | |
| 7 | 3977 | 0x666F738 | `imul eax,0xFFFF8BA3` | — | |
| 8 | 3978 | 0x666F73E | `dec eax` | — | |
| 9 | 3979 | 0x666F740 | `mov [rbp+0x2C],ax` | — | |
| 10 | 3980 | 0x666F744 | `mov rcx,[0x1233E1B0]` | — | |
| 11 | 3981 | 0x666F74B | `mov rax,[rcx]` | [rcx] qword → rax | |
| 12 | 3982 | 0x666F74E | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 13 | 3983 | 0x666F752 | `mov dl,0x4A` | — | |
| 14 | 3984 | 0x666F754 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 15 | 3985 | 0x666F75A | `nop` | — | |
| 16 | 3986 | 0x666F75B | `mov [rbp+0x670],al` | — | |
| 17 | 3987 | 0x666F761 | `mov rdx,[rsi+0x8A8]` | **[rsi+0x8A8] qword → rdx [V]** | |
| 18 | 3988 | 0x666F768 | `cmp rdx,[rsi+0x8B0]` | **[rsi+0x8B0] qword [V]** | |
| 19 | 3989 | 0x666F76F | `je short 0x666F785` | — | branch exit 0x666F785 |
| 20 | 3990 | 0x666F771 | `movzx eax,word ptr [rbp+0x440]` | — | |
| 21 | 3991 | 0x666F778 | `mov [rdx],ax` | — | |
| 22 | 3992 | 0x666F77B | `add qword ptr [rsi+0x8A8],2` | **[rsi+0x8A8] qword RMW [V]** | |
| 23 | 3993 | 0x666F783 | `jmp short 0x666F799` | — | branch exit 0x666F799 |
| 24 | 3994 | 0x666F785 | `lea r8,[rbp+0x440]` | — | |
| 25 | 3995 | 0x666F78C | `lea rcx,[rsi+0x8A0]` | lea [rsi+0x8A0] (address only) [V] | |
| 26 | 3996 | 0x666F793 | `call 0x1EF6F90` | — | call 0x1EF6F90 |
| 27 | 3997 | 0x666F798 | `nop` | — | |
| 28 | 3998 | 0x666F799 | `mov rcx,[0x1233E1B0]` | — | |
| 29 | 3999 | 0x666F7A0 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 30 | 4000 | 0x666F7A3 | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 31 | 4001 | 0x666F7A7 | `movzx edx,byte ptr [rbp+0x670]` | — | |
| 32 | 4002 | 0x666F7AE | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 33 | 4003 | 0x666F7B4 | `nop` | — | |
| 34 | 4004 | 0x666F7B5 | `mov eax,[rsi+0x8A8]` | **[rsi+0x8A8] dword → eax [V]** | |
| 35 | 4005 | 0x666F7BB | `sub eax,[rsi+0x8A0]` | **[rsi+0x8A0] dword → sub from eax [V]** | |
| 36 | 4006 | 0x666F7C1 | `shr eax,1` | — | |
| 37 | 4007 | 0x666F7C3 | `dec eax` | — | |
| 38 | 4008 | 0x666F7C5 | `mov [rbp+0x10],ax` | — | |
| 39 | 4009 | 0x666F7C9 | `mov rcx,[0x1233E1B0]` | — | |
| 40 | 4010 | 0x666F7D0 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 41 | 4011 | 0x666F7D3 | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 42 | 4012 | 0x666F7D7 | `mov dl,0x4A` | — | |
| 43 | 4013 | 0x666F7D9 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 44 | 4014 | 0x666F7DF | `mov [rbp+0x670],al` | — | |
| 45 | 4015 | 0x666F7E5 | `lea rdx,[rbp+0x3F8]` | — | |
| 46 | 4016 | 0x666F7EC | `mov rcx,rsi` | — | |
| 47 | 4017 | 0x666F7EF | `add rcx,0x648` | — | |
| 48 | 4018 | 0x666F7F6 | `call 0x675FB30` | — | call 0x675FB30 |
| 49 | 4019 | 0x666F7FB | `nop` | — | |
| 50 | 4020 | 0x666F7FC | `mov rcx,[0x1233E1B0]` | — | |
| 51 | 4021 | 0x666F803 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 52 | 4022 | 0x666F806 | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 53 | 4023 | 0x666F80A | `movzx edx,byte ptr [rbp+0x670]` | — | |
| 54 | 4024 | 0x666F811 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 55 | 4025 | 0x666F817 | `nop` | — | |
| 56 | 4026 | 0x666F818 | `mov eax,[rsi+0x650]` | **[rsi+0x650] dword → eax [V]** | |
| 57 | 4027 | 0x666F81E | `sub eax,[rsi+0x648]` | **[rsi+0x648] dword → sub from eax [V]** | |
| 58 | 4028 | 0x666F824 | `shr eax,3` | — | |
| 59 | 4029 | 0x666F827 | `imul eax,0xFFFF8E39` | — | |
| 60 | 4030 | 0x666F82D | `dec eax` | — | |

**Description-field reads in this block (rsi = description-candidate):** line 3974 `mov eax,[rsi+0x758]` reads desc+0x758 dword [V]; line 3975 `sub eax,[rsi+0x750]` reads desc+0x750 dword [V]; line 3987 `mov rdx,[rsi+0x8A8]` reads desc+0x8A8 qword → rdx [V]; line 3988 `cmp rdx,[rsi+0x8B0]` reads desc+0x8B0 qword [V]; line 3992 `add qword ptr [rsi+0x8A8],2` RMW desc+0x8A8 [V]; line 4004 `mov eax,[rsi+0x8A8]` reads desc+0x8A8 dword [V]; line 4005 `sub eax,[rsi+0x8A0]` reads desc+0x8A0 dword [V]; line 4018 `call 0x675FB30` with rcx=rsi+0x648 — passes desc+0x648 address [V]; line 4026 `mov eax,[rsi+0x650]` reads desc+0x650 dword [V]; line 4027 `sub eax,[rsi+0x648]` reads desc+0x648 dword [V]. Branch exits: 0x666F785, 0x666F799. Calls: qword ptr [0xF99FFA0] (3971, 3984, 4002, 4013, 4024), 0x1EF6F90 (3996), 0x675FB30 (4018).

## Block 19 — listing lines 4031..4090 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 4031 | 0x666F82F | `mov [rbp+0x42],ax` | — | |
| 2 | 4032 | 0x666F833 | `mov rcx,[0x1233E1B0]` | — | |
| 3 | 4033 | 0x666F83A | `mov rax,[rcx]` | [rcx] qword → rax | |
| 4 | 4034 | 0x666F83D | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 5 | 4035 | 0x666F841 | `mov dl,0x4A` | — | |
| 6 | 4036 | 0x666F843 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 7 | 4037 | 0x666F849 | `nop` | — | |
| 8 | 4038 | 0x666F84A | `mov edx,eax` | — | |
| 9 | 4039 | 0x666F84C | `mov rbx,[rsi+0x500]` | **[rsi+0x500] qword → rbx [V]** | |
| 10 | 4040 | 0x666F853 | `cmp rbx,[rsi+0x508]` | **[rsi+0x508] qword [V]** | |
| 11 | 4041 | 0x666F85A | `je short 0x666F86B` | — | branch exit 0x666F86B |
| 12 | 4042 | 0x666F85C | `inc rbx` | — | |
| 13 | 4043 | 0x666F85F | `mov [rsi+0x500],rbx` | — | |
| 14 | 4044 | 0x666F866 | `jmp 0x666F9DA` | — | branch exit 0x666F9DA |
| 15 | 4045 | 0x666F86B | `mov r13,rbx` | — | |
| 16 | 4046 | 0x666F86E | `sub r13,[rsi+0x4F8]` | **[rsi+0x4F8] qword → sub from r13 [V]** | |
| 17 | 4047 | 0x666F875 | `mov rax,0x7FFFFFFFFFFFFFFF` | — | |
| 18 | 4048 | 0x666F87F | `cmp r13,rax` | — | |
| 19 | 4049 | 0x666F882 | `mov [rbp+0x670],dl` | — | |
| 20 | 4050 | 0x666F888 | `je 0x667118C` | — | branch exit 0x667118C |
| 21 | 4051 | 0x666F88E | `lea r12,[r13+1]` | — | |
| 22 | 4052 | 0x666F892 | `mov rdi,r13` | — | |
| 23 | 4053 | 0x666F895 | `shr rdi,1` | — | |
| 24 | 4054 | 0x666F898 | `mov rcx,rdi` | — | |
| 25 | 4055 | 0x666F89B | `xor rcx,rax` | — | |
| 26 | 4056 | 0x666F89E | `add rdi,r13` | — | |
| 27 | 4057 | 0x666F8A1 | `cmp rdi,r12` | — | |
| 28 | 4058 | 0x666F8A4 | `cmovbe rdi,r12` | — | |
| 29 | 4059 | 0x666F8A8 | `cmp r13,rcx` | — | |
| 30 | 4060 | 0x666F8AB | `cmova rdi,rax` | — | |
| 31 | 4061 | 0x666F8AF | `test rdi,rdi` | — | |
| 32 | 4062 | 0x666F8B2 | `je short 0x666F929` | — | branch exit 0x666F929 |
| 33 | 4063 | 0x666F8B4 | `cmp rdi,0x1000` | — | |
| 34 | 4064 | 0x666F8BB | `jb short 0x666F900` | — | branch exit 0x666F900 |
| 35 | 4065 | 0x666F8BD | `cmp rdi,0xFFFFFFFFFFFFFFD9` | — | |
| 36 | 4066 | 0x666F8C1 | `jae 0x66715FD` | — | branch exit 0x66715FD |
| 37 | 4067 | 0x666F8C7 | `lea r15,[rdi+0x27]` | — | |
| 38 | 4068 | 0x666F8CB | `mov rcx,[0x1233E1A8]` | — | |
| 39 | 4069 | 0x666F8D2 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 40 | 4070 | 0x666F8D5 | `mov rax,[rax+8]` | [rax+0x8] qword → rax | |
| 41 | 4071 | 0x666F8D9 | `mov rdx,r15` | — | |
| 42 | 4072 | 0x666F8DC | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 43 | 4074 | 0x666F8E3 | `mov r14,rax` | — | |
| 44 | 4075 | 0x666F8E6 | `test rax,rax` | — | |
| 45 | 4076 | 0x666F8E9 | `je 0x6670A6C` | — | branch exit 0x6670A6C |
| 46 | 4077 | 0x666F8EF | `mov rax,r14` | — | |
| 47 | 4078 | 0x666F8F2 | `add r14,0x27` | — | |
| 48 | 4079 | 0x666F8F6 | `and r14,0xFFFFFFFFFFFFFFE0` | — | |
| 49 | 4080 | 0x666F8FA | `mov [r14-8],rax` | — | |
| 50 | 4081 | 0x666F8FE | `jmp short 0x666F92C` | — | branch exit 0x666F92C |
| 51 | 4082 | 0x666F900 | `mov rcx,[0x1233E1A8]` | — | |
| 52 | 4083 | 0x666F907 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 53 | 4084 | 0x666F90A | `mov rax,[rax+8]` | [rax+0x8] qword → rax | |
| 54 | 4085 | 0x666F90E | `mov rdx,rdi` | — | |
| 55 | 4086 | 0x666F911 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 56 | 4087 | 0x666F917 | `nop` | — | |
| 57 | 4088 | 0x666F918 | `mov r14,rax` | — | |
| 58 | 4089 | 0x666F91B | `test rax,rax` | — | |
| 59 | 4090 | 0x666F91E | `jne short 0x666F92C` | — | branch exit 0x666F92C |

**Description-field reads in this block (rsi = description-candidate):** line 4039 `mov rbx,[rsi+0x500]` reads desc+0x500 qword → rbx [V]; line 4040 `cmp rbx,[rsi+0x508]` reads desc+0x508 qword [V]; line 4046 `sub r13,[rsi+0x4F8]` reads desc+0x4F8 qword [V]. Branch exits: 0x666F86B, 0x666F9DA, 0x666F929, 0x666F900, 0x66715FD, 0x6670A6C, 0x666F92C. Calls: qword ptr [0xF99FFA0] (4036, 4072, 4086).

## Block 20 — listing lines 4091..4150 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 4091 | 0x666F929 | `xor r14d,r14d` | — | |
| 2 | 4092 | 0x666F92C | `cmp rbx,[rsi+0x500]` | **[rsi+0x500] qword [V]** | |
| 3 | 4093 | 0x666F933 | `je short 0x666F963` | — | branch exit 0x666F963 |
| 4 | 4095 | 0x666F935 | `lea r15,[r14+r13]` | — | |
| 5 | 4096 | 0x666F939 | `inc r15` | — | |
| 6 | 4097 | 0x666F93C | `mov rdx,[rsi+0x4F8]` | **[rsi+0x4F8] qword → rdx [V]** | |
| 7 | 4099 | 0x666F943 | `mov r8,rbx` | — | |
| 8 | 4100 | 0x666F946 | `sub r8,rdx` | — | |
| 9 | 4101 | 0x666F949 | `mov rcx,r14` | — | |
| 10 | 4102 | 0x666F94C | `call 0xEEC6DE0` | — | call 0xEEC6DE0 |
| 11 | 4104 | 0x666F951 | `mov r8,[rsi+0x500]` | **[rsi+0x500] qword → r8 [V]** | |
| 12 | 4105 | 0x666F958 | `sub r8,rbx` | — | |
| 13 | 4106 | 0x666F95B | `mov rcx,r15` | — | |
| 14 | 4107 | 0x666F95E | `mov rdx,rbx` | — | |
| 15 | 4108 | 0x666F961 | `jmp short 0x666F973` | — | branch exit 0x666F973 |
| 16 | 4109 | 0x666F963 | `mov rdx,[rsi+0x4F8]` | **[rsi+0x4F8] qword → rdx [V]** | |
| 17 | 4110 | 0x666F96A | `sub rbx,rdx` | — | |
| 18 | 4111 | 0x666F96D | `mov rcx,r14` | — | |
| 19 | 4112 | 0x666F970 | `mov r8,rbx` | — | |
| 20 | 4113 | 0x666F973 | `call 0xEEC6DE0` | — | call 0xEEC6DE0 |
| 21 | 4114 | 0x666F978 | `mov rcx,[rsi+0x4F8]` | **[rsi+0x4F8] qword → rcx [V]** | |
| 22 | 4115 | 0x666F97F | `test rcx,rcx` | — | |
| 23 | 4116 | 0x666F982 | `je short 0x666F9B8` | — | branch exit 0x666F9B8 |
| 24 | 4117 | 0x666F984 | `mov rdx,[rsi+0x508]` | **[rsi+0x508] qword → rdx [V]** | |
| 25 | 4118 | 0x666F98B | `sub rdx,rcx` | — | |
| 26 | 4119 | 0x666F98E | `cmp rdx,0x1000` | — | |
| 27 | 4120 | 0x666F995 | `jb short 0x666F9B3` | — | branch exit 0x666F9B3 |
| 28 | 4121 | 0x666F997 | `mov rax,[rcx-8]` | [rcx-8] qword → rax | |
| 29 | 4122 | 0x666F99B | `add rcx,0xFFFFFFFFFFFFFFF8` | — | |
| 30 | 4123 | 0x666F99F | `sub rcx,rax` | — | |
| 31 | 4124 | 0x666F9A2 | `cmp rcx,0x20` | — | |
| 32 | 4125 | 0x666F9A6 | `jae 0x6670A7A` | — | branch exit 0x6670A7A |
| 33 | 4126 | 0x666F9AC | `add rdx,0x27` | — | |
| 34 | 4127 | 0x666F9B0 | `mov rcx,rax` | — | |
| 35 | 4128 | 0x666F9B3 | `call 0xE935700` | — | call 0xE935700 |
| 36 | 4129 | 0x666F9B8 | `mov [rsi+0x4F8],r14` | — | |
| 37 | 4130 | 0x666F9BF | `add r12,r14` | — | |
| 38 | 4131 | 0x666F9C2 | `mov [rsi+0x500],r12` | — | |
| 39 | 4132 | 0x666F9C9 | `add rdi,r14` | — | |
| 40 | 4133 | 0x666F9CC | `mov [rsi+0x508],rdi` | — | |
| 41 | 4134 | 0x666F9D3 | `movzx edx,byte ptr [rbp+0x670]` | — | |
| 42 | 4135 | 0x666F9DA | `mov rcx,[0x1233E1B0]` | — | |
| 43 | 4136 | 0x666F9E1 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 44 | 4137 | 0x666F9E4 | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 45 | 4138 | 0x666F9E8 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 46 | 4139 | 0x666F9EE | `nop` | — | |
| 47 | 4140 | 0x666F9EF | `mov rax,0x8002007001` | — | |
| 48 | 4141 | 0x666F9F9 | `mov [rbp],rax` | — | |
| 49 | 4142 | 0x666FA0F | `mov eax,[rsi+0x4F8]` | **[rsi+0x4F8] dword → eax [V]** | |
| 50 | 4143 | 0x666FA03 | `not eax` | — | |
| 51 | 4144 | 0x666FA05 | `add eax,[rsi+0x500]` | **[rsi+0x500] dword → add to eax [V]** | |
| 52 | 4145 | 0x666FA0B | `mov [rbp+0x5E],ax` | — | |
| 53 | 4146 | 0x666FA0F | `mov rcx,[0x1233E1B0]` | — | |
| 54 | 4147 | 0x666FA16 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 55 | 4148 | 0x666FA19 | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 56 | 4149 | 0x666FA1D | `mov dl,0x4A` | — | |
| 57 | 4150 | 0x666FA1F | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |

**Description-field reads in this block (rsi = description-candidate):** line 4092 `cmp rbx,[rsi+0x500]` reads desc+0x500 [V]; line 4097 `mov rdx,[rsi+0x4F8]` reads desc+0x4F8 qword → rdx [V]; line 4101 `mov r8,[rsi+0x500]` reads desc+0x500 qword → r8 [V]; line 4109 `mov rdx,[rsi+0x4F8]` reads desc+0x4F8 [V]; line 4114 `mov rcx,[rsi+0x4F8]` reads desc+0x4F8 [V]; line 4117 `mov rdx,[rsi+0x508]` reads desc+0x508 [V]; line 4142 `mov eax,[rsi+0x4F8]` reads desc+0x4F8 dword → eax [V]; line 4144 `add eax,[rsi+0x500]` reads desc+0x500 dword [V]. Branch exits: 0x666F963, 0x666F973, 0x666F9B8, 0x666F9B3, 0x6670A7A. Calls: 0xEEC6DE0 (4102, 4113), 0xE935700 (4128), qword ptr [0xF99FFA0] (4138, 4150).

## Block 21 — listing lines 4151..4210 (60 lines)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 4151 | 0x666FA25 | `nop` | — | |
| 2 | 4152 | 0x666FA26 | `mov [rbp+0x670],al` | — | |
| 3 | 4153 | 0x666FA2C | `mov rax,[rsi+8]` | **[rsi+8] qword → rax [V]** (rsi=description-candidate) | |
| 4 | 4154 | 0x666FA30 | `cmp rax,[rsi+0x10]` | **[rsi+0x10] qword [V]** | |
| 5 | 4155 | 0x666FA34 | `je short 0x666FA51` | — | branch exit 0x666FA51 |
| 6 | 4156 | 0x666FA36 | `mov rdx,rbp` | — | |
| 7 | 4157 | 0x666FA39 | `mov r8d,0xC8` | — | |
| 8 | 4158 | 0x666FA3F | `mov rcx,rax` | — | |
| 9 | 4159 | 0x666FA42 | `call 0xEEC6EC0` | — | call 0xEEC6EC0 |
| 10 | 4160 | 0x666FA47 | `add qword ptr [rsi+8],0xC8` | **[rsi+8] qword RMW [V]** | |
| 11 | 4161 | 0x666FA4F | `jmp short 0x666FA60` | — | branch exit 0x666FA60 |
| 12 | 4162 | 0x666FA51 | `mov r8,rbp` | — | |
| 13 | 4163 | 0x666FA54 | `mov rcx,rsi` | — | |
| 14 | 4164 | 0x666FA57 | `mov rdx,rax` | — | |
| 15 | 4165 | 0x666FA5A | `call 0x5ABA6D0` | — | call 0x5ABA6D0 |
| 16 | 4166 | 0x666FA5F | `nop` | — | |
| 17 | 4167 | 0x666FA60 | `mov rcx,[0x1233E1B0]` | — | |
| 18 | 4168 | 0x666FA67 | `mov rax,[rcx]` | [rcx] qword → rax | |
| 19 | 4169 | 0x666FA6A | `mov rax,[rax+0x10]` | [rax+0x10] qword → rax | |
| 20 | 4170 | 0x666FA6E | `movzx edx,byte ptr [rbp+0x670]` | — | |
| 21 | 4171 | 0x666FA75 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 22 | 4172 | 0x666FA7B | `nop` | — | |
| 23 | 4173 | 0x666FA7C | `lea rcx,[rbp+0x3F0]` | — | |
| 24 | 4174 | 0x666FA83 | `call 0x66E5B10` | — | call 0x66E5B10 |
| 25 | 4175 | 0x666FA88 | `cmp byte ptr [rbp+0x2E0],1` | — | |
| 26 | 4176 | 0x666FA8F | `jne short 0x666FAD1` | — | branch exit 0x666FAD1 |
| 27 | 4177 | 0x666FA91 | `mov rcx,[rbp+0x2A0]` | — | |
| 28 | 4178 | 0x666FA98 | `test rcx,rcx` | — | |
| 29 | 4179 | 0x666FA9B | `je short 0x666FAD1` | — | branch exit 0x666FAD1 |
| 30 | 4180 | 0x666FA9D | `mov rdx,[rbp+0x2B0]` | — | |
| 31 | 4181 | 0x666FAA4 | `sub rdx,rcx` | — | |
| 32 | 4182 | 0x666FAA7 | `cmp rdx,0x1000` | — | |
| 33 | 4183 | 0x666FAAE | `jb short 0x666FACC` | — | branch exit 0x666FACC |
| 34 | 4184 | 0x666FAB0 | `mov rax,[rcx-8]` | [rcx-8] qword → rax | |
| 35 | 4185 | 0x666FAB4 | `add rcx,0xFFFFFFFFFFFFFFF8` | — | |
| 36 | 4186 | 0x666FAB8 | `sub rcx,rax` | — | |
| 37 | 4187 | 0x666FABB | `cmp rcx,0x20` | — | |
| 38 | 4188 | 0x666FABF | `jae 0x6670A7A` | — | branch exit 0x6670A7A |
| 39 | 4189 | 0x666FAC5 | `or rdx,0x27` | — | |
| 40 | 4190 | 0x666FAC9 | `mov rcx,rax` | — | |
| 41 | 4191 | 0x666FACC | `call 0xE935700` | — | call 0xE935700 |
| 42 | 4192 | 0x666FAD1 | `cmp byte ptr [rbp+0x398],1` | — | |
| 43 | 4193 | 0x666FAD8 | `jne 0x666FB78` | — | branch exit 0x666FB78 |
| 44 | 4194 | 0x666FADE | `cmp byte ptr [rbp+0x378],3` | — | |
| 45 | 4195 | 0x666FAE5 | `jne short 0x666FB1E` | — | branch exit 0x666FB1E |
| 46 | 4196 | 0x666FAE7 | `mov rsi,[rbp+0x370]` | — | (rsi clobbered — no longer description pointer) |
| 47 | 4197 | 0x666FAEE | `test rsi,rsi` | — | |
| 48 | 4198 | 0x666FAF1 | `je short 0x666FB1E` | — | branch exit 0x666FB1E |
| 49 | 4199 | 0x666FAF3 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 50 | 4200 | 0x666FAF7 | `jne short 0x666FB1E` | — | branch exit 0x666FB1E |
| 51 | 4201 | 0x666FAF9 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 52 | 4202 | 0x666FAFC | `mov rax,[rax]` | [rax] qword → rax | |
| 53 | 4203 | 0x666FAFF | `mov rcx,rsi` | — | |
| 54 | 4204 | 0x666FB02 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 55 | 4205 | 0x666FB08 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 56 | 4206 | 0x666FB0C | `jne short 0x666FB1E` | — | branch exit 0x666FB1E |
| 57 | 4207 | 0x666FB0E | `mov rax,[rsi]` | [rsi] qword → rax | |
| 58 | 4208 | 0x666FB11 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 59 | 4209 | 0x666FB15 | `mov rcx,rsi` | — | |
| 60 | 4210 | 0x666FB18 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |

**Description-field reads in this block:** line 4153 `mov rax,[rsi+8]` reads desc+8 qword → rax [V]; line 4154 `cmp rax,[rsi+0x10]` reads desc+0x10 qword [V]; line 4160 `add qword ptr [rsi+8],0xC8` RMW desc+8 [V]. Line 4196 `mov rsi,[rbp+0x370]` clobbers rsi — description pointer no longer in rsi after this. Branch exits: 0x666FA51, 0x666FA60, 0x666FAD1, 0x666FACC, 0x6670A7A, 0x666FB78, 0x666FB1E. Calls: 0xEEC6EC0 (4159), 0x5ABA6D0 (4165), qword ptr [0xF99FFA0] (4171, 4204, 4210), 0x66E5B10 (4174), 0xE935700 (4191).

## Block 22 — listing lines 4211..4259 (49 lines; end of range)

| # | Line | RVA | Instruction (quoted) | Description-field read (reg+offset, size from mnemonic → dest) | Branch exit / call with RVA |
|---|------|-----|----------------------|----------------------------------------------------------------|-----------------------------|
| 1 | 4211 | 0x666FB1E | `mov rdi,[rbp+0x348]` | — | |
| 2 | 4212 | 0x666FB25 | `test rdi,rdi` | — | |
| 3 | 4213 | 0x666FB28 | `je short 0x666FB78` | — | branch exit 0x666FB78 |
| 4 | 4214 | 0x666FB2A | `mov rbx,[rbp+0x350]` | — | |
| 5 | 4215 | 0x666FB31 | `jmp short 0x666FB37` | — | branch exit 0x666FB37 |
| 6 | 4216 | 0x666FB33 | `add rdi,0x28` | — | |
| 7 | 4217 | 0x666FB37 | `cmp rdi,rbx` | — | |
| 8 | 4218 | 0x666FB3A | `je short 0x666FB78` | — | branch exit 0x666FB78 |
| 9 | 4219 | 0x666FB3C | `cmp byte ptr [rdi+0x18],2` | [rdi+0x18] byte | |
| 10 | 4220 | 0x666FB40 | `jne short 0x666FB33` | — | branch exit 0x666FB33 |
| 11 | 4221 | 0x666FB42 | `mov rsi,[rdi+8]` | [rdi+8] qword → rsi | |
| 12 | 4222 | 0x666FB46 | `test rsi,rsi` | — | |
| 13 | 4223 | 0x666FB49 | `je short 0x666FB33` | — | branch exit 0x666FB33 |
| 14 | 4224 | 0x666FB4B | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 15 | 4225 | 0x666FB4F | `jne short 0x666FB33` | — | branch exit 0x666FB33 |
| 16 | 4226 | 0x666FB51 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 17 | 4227 | 0x666FB54 | `mov rax,[rax]` | [rax] qword → rax | |
| 18 | 4228 | 0x666FB57 | `mov rcx,rsi` | — | |
| 19 | 4229 | 0x666FB5A | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 20 | 4230 | 0x666FB60 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 21 | 4231 | 0x666FB64 | `jne short 0x666FB33` | — | branch exit 0x666FB33 |
| 22 | 4232 | 0x666FB66 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 23 | 4233 | 0x666FB69 | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 24 | 4234 | 0x666FB6D | `mov rcx,rsi` | — | |
| 25 | 4235 | 0x666FB70 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 26 | 4236 | 0x666FB76 | `jmp short 0x666FB33` | — | branch exit 0x666FB33 |
| 27 | 4237 | 0x666FB78 | `mov rsi,[rbp+0x638]` | — | |
| 28 | 4238 | 0x666FB7F | `test rsi,rsi` | — | |
| 29 | 4239 | 0x666FB82 | `je 0x6670032` | — | branch exit 0x6670032 |
| 30 | 4240 | 0x666FB88 | `lock dec dword ptr [rsi+8]` | [rsi+8] dword | |
| 31 | 4241 | 0x666FB8C | `jne 0x6670032` | — | branch exit 0x6670032 |
| 32 | 4242 | 0x666FB92 | `mov rax,[rsi]` | [rsi] qword → rax | |
| 33 | 4243 | 0x666FB95 | `mov rax,[rax]` | [rax] qword → rax | |
| 34 | 4244 | 0x666FB98 | `mov rcx,rsi` | — | |
| 35 | 4245 | 0x666FB9B | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 36 | 4246 | 0x666FBA1 | `lock dec dword ptr [rsi+0xC]` | [rsi+0xC] dword | |
| 37 | 4247 | 0x666FBA5 | `jne 0x6670032` | — | branch exit 0x6670032 |
| 38 | 4248 | 0x666FBAB | `mov rax,[rsi]` | [rsi] qword → rax | |
| 39 | 4249 | 0x666FBAE | `mov rax,[rax+0x8]` | [rax+0x8] qword → rax | |
| 40 | 4250 | 0x666FBB2 | `mov rcx,rsi` | — | |
| 41 | 4251 | 0x666FBB5 | `call qword ptr [0xF99FFA0]` | — | call qword ptr [0xF99FFA0] |
| 42 | 4252 | 0x666FBBB | `jmp 0x6670032` | — | **branch exit 0x6670032 — tag-7 body epilogue jump [V]** |

**Description-field reads in this block:** none directly off description pointer r12; rsi was clobbered at line 4196 so no description reads here. All reads are chain/refcount objects.

## Where the tag-7 body ends [V]
The body (entered at 0x666b5cf, listing line 475) runs through this whole range and exits via `jmp 0x6670032` at listing line 4252 (RVA 0x666FBBB). Line 4252 `jmp 0x6670032` is the tag-7 body epilogue exit jump [V]. Note: 0x6670032 is also the common exit target used by multiple guard branches earlier in the body (e.g. lines 3016, 3025, 3530). Instructions after line 4252 (0x666FBC0..., 0x666FBE3...) are cold-path targets, not sequential continuation of the body.

## Summary of description-pointer registers in the body [V]
- r12 = description pointer after line 3115 `mov r12,[r12]` (before that r12 held slot address r15+0x78 from head line 111).
- rsi = description pointer reloaded at lines 3276/3294 `mov rsi,[rax+0x78]` (rax=[rbp+0x668]); clobbered at line 4196 `mov rsi,[rbp+0x370]`.
- Description-field reads confirmed [V] off r12/rsi: +0x0 (line 3149), +0x10 (lines 3042[I-slot], 3458, 3864, 4154), +0x58 (3278), +0x60 (3277), +0x84 (3113), +0x1B0 (3310, 3321), +0x1B8 (3314, 3318), +0x1D0 (3298), +0x1D4 (3296), +0x4F8 (4046, 4097, 4109, 4114, 4142), +0x500 (4039, 4040[cmp], 4092[cmp], 4101, 4144), +0x508 (4040[cmp], 4117), +0x648 (4027), +0x650 (4026), +0x648+0x650 via call 0x675FB30 (4018), +0x750 (3975), +0x758 (3938, 3962 RMW, 3974), +0x760 (3939), +0x768 (lea only 3914), +0x770 (3899, 3911 RMW, 3924), +0x778 (3900), +0x780 (3887), +0x788 (3886), +0x8A0 (4005), +0x8A8 (3987, 3992 RMW, 4004), +0x8B0 (3988), +8 (4153, 4160 RMW), +0x10 (4154). All [I] tags on rsi/r12 being the description rest on r12 being set from [r12] at line 3115 where r12=r15+0x78 slot (head line 111), matching head's `mov rax,[r15+0x78]` description load.

## Status
- Lines 1..700 register analysis: DONE
- Lines 2950..4250 tables: DONE (blocks 1-22, lines 2950-4259)
- docs/progress/oc_U-FX3.md: complete; no other file edited.

## NEXT
Unit complete. Awaiting orchestrator review.





















