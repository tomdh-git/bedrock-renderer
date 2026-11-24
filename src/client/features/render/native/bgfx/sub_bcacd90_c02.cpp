// LIFT 0xbcacd90 size 0x4f7b 1.26.62.01 sub_bcacd90
// CHUNK 0xbcafd5f..0xbcb153c

// chunk state documented in docs/functions/bcacd90.md section 'Chunk state'
struct ChunkState_bcacd90_c02 {
    void* r8_current_slot;
    unsigned long long r9_remaining;
    void* rdx_slot_base;
    void* rbp_frame_base;
    void* r12_scratch;
    void* r13_scratch;
    void* r14_scratch;
    void* r15_scratch;
};

static inline void sub_bcacd90_chunk02(ChunkState_bcacd90_c02& s) {
    // 0xbcafd5f..0xbcafd75
    // lea rdx,[0xF557C84] "ColorGrading_Contrast_Midtones"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580
    (void)s;
    // 0xbcafd76..0xbcafd91
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcafda0..0xbcafdb8
    // jae loc_bcb10f2; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb114e
    // 0xbcafdb8..0xbcafdbf
    // lea rcx,[0x12AE22F8]; call sub_e938cb0
    // 0xbcafdc4..0xbcafdd1
    // cmp dword ptr [0x12AE22F8],0xFFFFFFFF; jne sub_bcad571
    // 0xbcafdd1..0xbcafde7
    // lea rdx,[0xF5427FA] "ColorGrading_Contrast_Shadows"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcafde8..0xbcafe03
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcafe0e..0xbcafe2a
    // jae loc_bcb11a9; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb1205
    // 0xbcafe2a..0xbcafe31
    // lea rcx,[0x12AE2308]; call sub_e938cb0
    // 0xbcafe36..0xbcafe43
    // cmp dword ptr [0x12AE2308],0xFFFFFFFF; jne sub_bcad596
    // 0xbcafe43..0xbcafe59
    // lea rdx,[0xF54604B] "ColorGrading_Saturation_Highlights"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcafe5a..0xbcafe75
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcafe80..0xbcafe9c
    // jae loc_bcb1260; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb12bc
    // 0xbcafe9c..0xbcafea3
    // lea rcx,[0x12AE2318]; call sub_e938cb0
    // 0xbcafea8..0xbcafeb5
    // cmp dword ptr [0x12AE2318],0xFFFFFFFF; jne sub_bcad5bb
    // 0xbcafeb5..0xbcafecb
    // lea rdx,[0xF557CC0] "ColorGrading_Saturation_Midtones"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcafecb..0xbcafee7
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcafef2..0xbcaff0e
    // jae loc_bcb1317; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb1373
    // 0xbcaff0e..0xbcaff15
    // lea rcx,[0x12AE2328]; call sub_e938cb0
    // 0xbcaff1a..0xbcaff27
    // cmp dword ptr [0x12AE2328],0xFFFFFFFF; jne sub_bcad5e0
    // 0xbcaff27..0xbcaff3d
    // lea rdx,[0xF542834] "ColorGrading_Saturation_Shadows"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcaff3e..0xbcaff59
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcaff64..0xbcaff80
    // jae loc_bcb13ce; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb142a
    // 0xbcaff80..0xbcaff87
    // lea rcx,[0x12AE2338]; call sub_e938cb0
    // 0xbcaff8c..0xbcaff99
    // cmp dword ptr [0x12AE2338],0xFFFFFFFF; jne sub_bcad605
    // 0xbcaff99..0xbcaffaf
    // lea rdx,[0xF54606E] "ColorGrading_Gain_Highlights"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcaffb0..0xbcaffcb
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcaffd6..0xbcafff2
    // jae loc_bcb1485; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb14e1
    // 0xbcafff2..0xbcafff9
    // lea rcx,[0x12AE2348]; call sub_e938cb0
    // 0xbcafffe..0xbcb000b
    // cmp dword ptr [0x12AE2348],0xFFFFFFFF; jne sub_bcad62a
    // 0xbcb000b..0xbcb0021
    // lea rdx,[0xF557CE1] "ColorGrading_Gain_Midtones"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb0022..0xbcb003d
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb0048..0xbcb0064
    // jae loc_bcb153c; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb1598
    // 0xbcb0064..0xbcb006b
    // lea rcx,[0x12AE2358]; call sub_e938cb0
    // 0xbcb0070..0xbcb007d
    // cmp dword ptr [0x12AE2358],0xFFFFFFFF; jne sub_bcad64f
    // 0xbcb007d..0xbcb0093
    // lea rdx,[0xF542854] "ColorGrading_Gain_Shadows"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb0094..0xbcb00af
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb00ba..0xbcb00d6
    // jae loc_bcb15f3; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb164f
    // 0xbcb00d6..0xbcb00dd
    // lea rcx,[0x12AE2368]; call sub_e938cb0
    // 0xbcb00e2..0xbcb00ef
    // cmp dword ptr [0x12AE2368],0xFFFFFFFF; jne sub_bcad674
    // 0xbcb00ef..0xbcb0105
    // lea rdx,[0xF54602C] "ColorGrading_Offset_Highlights"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb0106..0xbcb0121
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb012c..0xbcb0148
    // jae loc_bcb16aa; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb1706
    // 0xbcb0148..0xbcb014f
    // lea rcx,[0x12AE2378]; call sub_e938cb0
    // 0xbcb0154..0xbcb0161
    // cmp dword ptr [0x12AE2378],0xFFFFFFFF; jne sub_bcad699
    // 0xbcb0161..0xbcb0177
    // lea rdx,[0xF557CA3] "ColorGrading_Offset_Midtones"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb0178..0xbcb0193
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb019e..0xbcb01ba
    // jae loc_bcb1761; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb17bd
    // 0xbcb01ba..0xbcb01c1
    // lea rcx,[0x12AE2388]; call sub_e938cb0
    // 0xbcb01c6..0xbcb01d3
    // cmp dword ptr [0x12AE2388],0xFFFFFFFF; jne sub_bcad6be
    // 0xbcb01d3..0xbcb01e9
    // lea rdx,[0xF542818] "ColorGrading_Offset_Shadows"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb01ea..0xbcb0205
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb0210..0xbcb022c
    // jae loc_bcb1818; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb1874
    // 0xbcb022c..0xbcb0233
    // lea rcx,[0x12AE2398]; call sub_e938cb0
    // 0xbcb0238..0xbcb0245
    // cmp dword ptr [0x12AE2398],0xFFFFFFFF; jne sub_bcad6e3
    // 0xbcb0245..0xbcb025b
    // lea rdx,[0xF54608B] "ColorGrading_Gamma_Highlights"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb025c..0xbcb0277
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb0282..0xbcb029e
    // jae loc_bcb18cf; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb192b
    // 0xbcb029e..0xbcb02a5
    // lea rcx,[0x12AE23A8]; call sub_e938cb0
    // 0xbcb02aa..0xbcb02b7
    // cmp dword ptr [0x12AE23A8],0xFFFFFFFF; jne sub_bcad708
    // 0xbcb02b7..0xbcb02cd
    // lea rdx,[0xF557CFC] "ColorGrading_Gamma_Midtones"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb02ce..0xbcb02e9
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb02f4..0xbcb0310
    // jae loc_bcb1986; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb19e2
    // 0xbcb0310..0xbcb0317
    // lea rcx,[0x12AE23B8]; call sub_e938cb0
    // 0xbcb031c..0xbcb0329
    // cmp dword ptr [0x12AE23B8],0xFFFFFFFF; jne sub_bcad72d
    // 0xbcb0329..0xbcb033f
    // lea rdx,[0xF54286E] "ColorGrading_Gamma_Shadows"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb0340..0xbcb035b
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb0366..0xbcb0382
    // jae loc_bcb1a3d; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb1a99
    // 0xbcb0382..0xbcb0389
    // lea rcx,[0x12AE23C8]; call sub_e938cb0
    // 0xbcb038e..0xbcb039b
    // cmp dword ptr [0x12AE23C8],0xFFFFFFFF; jne sub_bcad752
    // 0xbcb039b..0xbcb03b1
    // lea rdx,[0xF605A7B] "ColorGrading_Misc"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb03b2..0xbcb03cd
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb03d8..0xbcb03f4
    // jae loc_bcb1af4; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb1b50
    // 0xbcb03f4..0xbcb03fb
    // lea rcx,[0x12AE23D8]; call sub_e938cb0
    // 0xbcb0400..0xbcb040d
    // cmp dword ptr [0x12AE23D8],0xFFFFFFFF; jne sub_bcad777
    // 0xbcb040d..0xbcb0423
    // lea rdx,[0xF7DA6CD] "ColorGrading_Misc2"; lea r12,[rbp+0xA80]; mov rcx,r12; call sub_79580; nop
    // 0xbcb0424..0xbcb043f
    // mov rdx,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov r12,[rbp+0xA80]; test rdx,rdx; je
    // 0xbcb044a..0xbcb0466
    // jae loc_bcb1bab; mov rcx,0xCBF29CE484222325; xor r8d,r8d; jmp loc_bcb1c07
    // 0xbcb0466..0xbcb046d
    // lea rcx,[0x12AE24B8]; call sub_e938cb0
    // 0xbcb0472..0xbcb047f
    // cmp dword ptr [0x12AE24B8],0xFFFFFFFF; jne sub_bcae726
    // 0xbcb047f..0xbcb0495
    // lea rdx,[0xF58CE4E] "CustomExposureCompensation"; lea rbx,[rbp+0xA80]; mov rcx,rbx; call sub_79580; nop
    // 0xbcb0496..0xbcb04b1
    // mov r8,[rbp+0xA90]; cmp qword ptr [rbp+0xA98],0x10; jb; mov rbx,[rbp+0xA80]; test r8,r8; je
    // 0xbcb04b7..0xbcb04e3
    // mov eax,r8d; and eax,3; mov rcx,0x100000001B3; cmp r8,4; jae loc_bcb1c6e; mov rdx,0xCBF29CE484222325; xor r9d,r9d; jmp loc_bcb1cc0
    // 0xbcb04e3..0xbcb04ea
    // lea rcx,[0x129C13C0]; call sub_e938cb0
    // 0xbcb04ef..0xbcb04fc
    // cmp dword ptr [0x129C13C0],0xFFFFFFFF; jne sub_bcae5ce
    // 0xbcb04fc..0xbcb0503
    // lea rcx,[0x4E05030]; call sub_e935740
    // 0xbcb0508..0xbcb050f
    // lea rcx,[0x129C13C0]; call sub_e938d70
    // 0xbcb0514..0xbcb0519
    // jmp sub_bcae5ce
    // 0xbcb0519..0xbcb051e
    // call sub_75b60
    // 0xbcb051e..0xbcb0528
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0774
    // 0xbcb052d..0xbcb0537
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb081d
    // 0xbcb053c..0xbcb0546
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb08c6
    // 0xbcb054b..0xbcb0555
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb096f
    // 0xbcb055a..0xbcb0564
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0a18
    // 0xbcb0569..0xbcb0573
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0ac1
    // 0xbcb0578..0xbcb0582
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0b6a
    // 0xbcb0587..0xbcb0591
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0c13
    // 0xbcb0596..0xbcb05a0
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0cbc
    // 0xbcb05a5..0xbcb05af
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0d65
    // 0xbcb05b4..0xbcb05be
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0e0e
    // 0xbcb05c3..0xbcb05cd
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0eb7
    // 0xbcb05d2..0xbcb05dc
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb0f60
    // 0xbcb05e1..0xbcb05eb
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1009
    // 0xbcb05f0..0xbcb05fa
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb10c0
    // 0xbcb05ff..0xbcb0609
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1177
    // 0xbcb060e..0xbcb0618
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb122e
    // 0xbcb061d..0xbcb0627
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb12e5
    // 0xbcb062c..0xbcb0636
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb139c
    // 0xbcb063b..0xbcb0645
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1453
    // 0xbcb064a..0xbcb0654
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb150a
    // 0xbcb0659..0xbcb0663
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb15c1
    // 0xbcb0668..0xbcb0672
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1678
    // 0xbcb0677..0xbcb0681
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb172f
    // 0xbcb0686..0xbcb0690
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb17e6
    // 0xbcb0695..0xbcb069f
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb189d
    // 0xbcb06a4..0xbcb06ae
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1954
    // 0xbcb06b3..0xbcb06bd
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1a0b
    // 0xbcb06c2..0xbcb06cc
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1ac2
    // 0xbcb06d1..0xbcb06db
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1b79
    // 0xbcb06e0..0xbcb06ea
    // mov rcx,0xCBF29CE484222325; jmp loc_bcb1c30
    // 0xbcb06ef..0xbcb070a
    // and rdx,0xFFFFFFFFFFFFFFFC; mov rcx,0xCBF29CE484222325; xor r8d,r8d; mov r9,0x100000001B3
    // 0xbcb070a..0xbcb0746
    // loop: movzx r10d,byte ptr [r14+r8]; xor r10,rcx; imul r10,r9; ...; add r8,4; cmp rdx,r8; jne
    // 0xbcb0746..0xbcb0774
    // test rax,rax; je; add r14,r8; xor edx,edx; mov r8,0x100000001B3; mov r9,rcx; loop tail
    // 0xbcb0774..0xbcb0793
    // mov [0x12AE23E0],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE23E8]; call sub_e938d70; jmp sub_bcace1b
    // 0xbcb0798..0xbcb07b3
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,0x100000001B3
    // 0xbcb07b3..0xbcb07ef
    // loop (second param)
    // 0xbcb07ef..0xbcb081d
    // test rax,rax; je; tail loop
    // 0xbcb081d..0xbcb083c
    // mov [0x12AE23F0],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE23F8]; call sub_e938d70; jmp sub_bcace40
    // 0xbcb0841..0xbcb085c
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb085c..0xbcb0898
    // loop (third param)
    // 0xbcb0898..0xbcb08c6
    // test rax,rax; je; tail
    // 0xbcb08c6..0xbcb08e5
    // mov [0x12AE2400],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2408]; call sub_e938d70; jmp sub_bcace65
    // 0xbcb08ea..0xbcb0905
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0905..0xbcb0941
    // loop (fourth param)
    // 0xbcb0941..0xbcb096f
    // test rax,rax; je; tail
    // 0xbcb096f..0xbcb098e
    // mov [0x12AE2410],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2418]; call sub_e938d70; jmp sub_bcace8a
    // 0xbcb0993..0xbcb09ae
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb09ae..0xbcb09ea
    // loop (fifth param)
    // 0xbcb09ea..0xbcb0a18
    // test rax,rax; je; tail
    // 0xbcb0a18..0xbcb0a37
    // mov [0x12AE2420],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2428]; call sub_e938d70; jmp sub_bcaceaf
    // 0xbcb0a3c..0xbcb0a57
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0a57..0xbcb0a93
    // loop (sixth param)
    // 0xbcb0a93..0xbcb0ac1
    // test rax,rax; je; tail
    // 0xbcb0ac1..0xbcb0ae0
    // mov [0x12AE2430],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2438]; call sub_e938d70; jmp sub_bcaced4
    // 0xbcb0ae5..0xbcb0b00
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0b00..0xbcb0b3c
    // loop (seventh param)
    // 0xbcb0b3c..0xbcb0b6a
    // test rax,rax; je; tail
    // 0xbcb0b6a..0xbcb0b89
    // mov [0x12AE2440],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2448]; call sub_e938d70; jmp sub_bcacef9
    // 0xbcb0b8e..0xbcb0ba9
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0ba9..0xbcb0be5
    // loop (eighth param)
    // 0xbcb0be5..0xbcb0c13
    // test rax,rax; je; tail
    // 0xbcb0c13..0xbcb0c32
    // mov [0x12AE2450],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2458]; call sub_e938d70; jmp sub_bcaf11e? 
    // 0xbcb0c37..0xbcb0c52
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0c52..0xbcb0c8e
    // loop (ninth param)
    // 0xbcb0c8e..0xbcb0cbc
    // test rax,rax; je; tail
    // 0xbcb0cbc..0xbcb0cdb
    // mov [0x12AE2460],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2468]; call sub_e938d70; jmp ...
    // 0xbcb0ce0..0xbcb0cfb
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0cfb..0xbcb0d37
    // loop (tenth param)
    // 0xbcb0d37..0xbcb0d65
    // test rax,rax; je; tail
    // 0xbcb0d65..0xbcb0d84
    // mov [0x12AE2470],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2478]; call sub_e938d70; jmp ...
    // 0xbcb0d89..0xbcb0da4
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0da4..0xbcb0de0
    // loop (eleventh param)
    // 0xbcb0de0..0xbcb0e0e
    // test rax,rax; je; tail
    // 0xbcb0e0e..0xbcb0e2d
    // mov [0x12AE2480],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2488]; call sub_e938d70; jmp ...
    // 0xbcb0e32..0xbcb0e4d
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0e4d..0xbcb0e89
    // loop (twelfth param)
    // 0xbcb0e89..0xbcb0eb7
    // test rax,rax; je; tail
    // 0xbcb0eb7..0xbcb0ed6
    // mov [0x12AE2490],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE2498]; call sub_e938d70; jmp ...
    // 0xbcb0edb..0xbcb0ef6
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0ef6..0xbcb0f32
    // loop (thirteenth param)
    // 0xbcb0f32..0xbcb0f60
    // test rax,rax; je; tail
    // 0xbcb0f60..0xbcb0f7f
    // mov [0x12AE24A0],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE24A8]; call sub_e938d70; jmp ...
    // 0xbcb0f84..0xbcb0f9f
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb0f9f..0xbcb0fdb
    // loop (fourteenth param)
    // 0xbcb0fdb..0xbcb1009
    // test rax,rax; je; tail
    // 0xbcb1009..0xbcb1028
    // mov [0x12AE24B0],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE24B8]; call sub_e938d70; jmp ...
    // 0xbcb102d..0xbcb1048
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb1048..0xbcb1084
    // loop (fifteenth param)
    // 0xbcb1084..0xbcb10c0
    // test rax,rax; je; tail
    // 0xbcb10c0..0xbcb10df
    // mov [0x12AE24C0],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,[0x12AE24C8]; call sub_e938d70; jmp ...
    // 0xbcb10e4..0xbcb10ff
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb10ff..0xbcb113b
    // loop (sixteenth param)
    // 0xbcb113b..0xbcb1177
    // test rax,rax; je; tail -> loc_bcb1177
    // 0xbcb1177..0xbcb1196
    // mov [0x12AE23E0]? ... ; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,...; call sub_e938d70; jmp sub_bcace1b
    // 0xbcb119b..0xbcb11b6
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb11b6..0xbcb11f2
    // loop
    // 0xbcb11f2..0xbcb122e
    // test rax,rax; je; tail -> loc_bcb122e
    // 0xbcb122e..0xbcb124d
    // mov [...],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,...; call sub_e938d70; jmp ...
    // 0xbcb1252..0xbcb126d
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb126d..0xbcb12a9
    // loop
    // 0xbcb12a9..0xbcb12e5
    // test rax,rax; je; tail -> loc_bcb12e5
    // 0xbcb12e5..0xbcb1304
    // mov [...],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,...; call sub_e938d70; jmp ...
    // 0xbcb1309..0xbcb1324
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb1324..0xbcb1360
    // loop
    // 0xbcb1360..0xbcb139c
    // test rax,rax; je; tail -> loc_bcb139c
    // 0xbcb139c..0xbcb13bb
    // mov [...],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,...; call sub_e938d70; jmp ...
    // 0xbcb13c0..0xbcb13db
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb13db..0xbcb1417
    // loop
    // 0xbcb1417..0xbcb1453
    // test rax,rax; je; tail -> loc_bcb1453
    // 0xbcb1453..0xbcb1472
    // mov [...],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,...; call sub_e938d70; jmp ...
    // 0xbcb1477..0xbcb1492
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
    // 0xbcb1492..0xbcb14ce
    // loop
    // 0xbcb14ce..0xbcb150a
    // test rax,rax; je; tail -> loc_bcb150a
    // 0xbcb150a..0xbcb1529
    // mov [...],rcx; lea rcx,[rbp+0xA80]; call sub_73150; lea rcx,...; call sub_e938d70; jmp ...
    // 0xbcb152e..0xbcb153c
    // and rdx,...; mov rcx,...; xor r8d,r8d; mov r9,...
}

#if 0
0xbcafd70  call 0x79580
0xbcafdbf  call 0xE938CB0
0xbcafde2  call 0x79580
0xbcafe31  call 0xE938CB0
0xbcafe54  call 0x79580
0xbcafea3  call 0xE938CB0
0xbcafec6  call 0x79580
0xbcaff15  call 0xE938CB0
0xbcaff38  call 0x79580
0xbcaff87  call 0xE938CB0
0xbcaffaa  call 0x79580
0xbcafff9  call 0xE938CB0
0xbcb001c  call 0x79580
0xbcb006b  call 0xE938CB0
0xbcb008e  call 0x79580
0xbcb00dd  call 0xE938CB0
0xbcb0100  call 0x79580
0xbcb014f  call 0xE938CB0
0xbcb0172  call 0x79580
0xbcb01c1  call 0xE938CB0
0xbcb01e4  call 0x79580
0xbcb0233  call 0xE938CB0
0xbcb0256  call 0x79580
0xbcb02a5  call 0xE938CB0
0xbcb02c8  call 0x79580
0xbcb0317  call 0xE938CB0
0xbcb033a  call 0x79580
0xbcb0389  call 0xE938CB0
0xbcb03ac  call 0x79580
0xbcb03fb  call 0xE938CB0
0xbcb041e  call 0x79580
0xbcb046d  call 0xE938CB0
0xbcb0490  call 0x79580
0xbcb04ea  call 0xE938CB0
0xbcb0503  call 0xE935740
0xbcb050f  call 0xE938D70
0xbcb0519  call 0x75B60
0xbcb0782  call 0x73150
0xbcb078e  call 0xE938D70
0xbcb082b  call 0x73150
0xbcb0837  call 0xE938D70
0xbcb08d4  call 0x73150
0xbcb08e0  call 0xE938D70
0xbcb097d  call 0x73150
0xbcb0989  call 0xE938D70
0xbcb0a26  call 0x73150
0xbcb0a32  call 0xE938D70
0xbcb0acf  call 0x73150
0xbcb0adb  call 0xE938D70
0xbcb0b78  call 0x73150
0xbcb0b84  call 0xE938D70
0xbcb0c21  call 0x73150
0xbcb0c2d  call 0xE938D70
0xbcb0cca  call 0x73150
0xbcb0cd6  call 0xE938D70
0xbcb0d73  call 0x73150
0xbcb0d7f  call 0xE938D70
0xbcb0e1c  call 0x73150
0xbcb0e28  call 0xE938D70
0xbcb0ec5  call 0x73150
0xbcb0ed1  call 0xE938D70
0xbcb0f6e  call 0x73150
0xbcb0f7a  call 0xE938D70
0xbcb1017  call 0x73150
0xbcb1023  call 0xE938D70
0xbcb10ce  call 0x73150
0xbcb10da  call 0xE938D70
0xbcb1185  call 0x73150
0xbcb1191  call 0xE938D70
0xbcb123c  call 0x73150
0xbcb1248  call 0xE938D70
0xbcb12f3  call 0x73150
0xbcb12ff  call 0xE938D70
0xbcb13aa  call 0x73150
0xbcb13b6  call 0xE938D70
0xbcb1461  call 0x73150
0xbcb146d  call 0xE938D70
0xbcb1518  call 0x73150
0xbcb1524  call 0xE938D70
#endif
