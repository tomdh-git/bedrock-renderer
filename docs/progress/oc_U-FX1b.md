# Unit U-FX1b — FullscreenEffect visitor body decode (tag 7), listing lines 825..1700

## Source
- Listing: docs/data/listings/effect_visitor_666aca0_667191c.txt, lines 825..1700 (RVA 0x666bc55 .. 0x666cced)
- Convention: r15 = description base (saved slot [rbp+0x668], restored at line 1181); r14 = desc+0x18 value until clobbered; register holding description pointer re-verified per use.
- [V] = seen in listing; [I] = inferred; [?] = unknown.

## NEXT
Resume at listing line 825 (RVA 0x666bc55). Next block to write: lines 825..864.

### lines 825..864 (0x666bc55..0x666bd3a)

Tail of the [rbp+0x2D8] switch: if the byte > 3 branch to default (0x666BD77), otherwise index the jump table at 0xF2BF500 (cases 0..2) and fall into case-3/default handling; each case copies a 0x58-byte record into the output struct ([rbp+0x138]/[rbp+0x140]) and stores a tag byte at [rbp+0x148]. All memory here is stack ([rbp+...]); no description field reads, no calls.

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 825 | 0x666bc55 | `jmp short 0x666BCA3` | branch to merge point after switch epilogue [V] |
| 826 | 0x666bc57 | `nop [rax+rax]` | padding nop [V] |
| 827 | 0x666bc60 | `cmp ecx,2` | compare switch value to 2 [V] |
| 828 | 0x666bc63 | `jne short 0x666BCA9` | branch if value != 2 (toward case-3 path) [V] |
| 829 | 0x666bc65 | `mov rcx,[rbp+0x5E0]` | stack read into rcx [V] |
| 830 | 0x666bc6c | `mov [rbp+0xC8],rcx` | stack write [V] |
| 831 | 0x666bc73 | `jmp short 0x666BCA3` | branch to merge point [V] |
| 832 | 0x666bc75 | `mov rcx,[rbp+0x5F0]` | stack read into rcx [V] |
| 833 | 0x666bc7c | `mov qword ptr [rbp+0x5F0],0` | stack write zero [V] |
| 834 | 0x666bc87 | `movaps xmm0,[rbp+0x5E0]` | stack read 16 bytes into xmm0 [V] |
| 835 | 0x666bc8e | `movaps [rbp+0x5E0],xmm6` | stack write zero xmm [V] |
| 836 | 0x666bc95 | `movups [rbp+0xC8],xmm0` | stack write 16 bytes [V] |
| 837 | 0x666bc9c | `mov [rbp+0xD8],rcx` | stack write [V] |
| 838 | 0x666bca3 | `mov [rbp+0x108],al` | store tag byte al [V] |
| 839 | 0x666bca9 | `movaps xmm0,[rbp+0x2A0]` | stack read 16 bytes into xmm0 [V] |
| 840 | 0x666bcb0 | `movaps xmm1,[rbp+0x2B0]` | stack read 16 bytes into xmm1 [V] |
| 841 | 0x666bcb7 | `mov qword ptr [rbp+0x2A8],0` | stack write zero [V] |
| 842 | 0x666bcc2 | `movups [rbp+0x110],xmm0` | stack write 16 bytes [V] |
| 843 | 0x666bcc9 | `movaps [rbp+0x2B0],xmm6` | stack write zero xmm [V] |
| 844 | 0x666bcd0 | `movups [rbp+0x120],xmm1` | stack write 16 bytes [V] |
| 845 | 0x666bcd7 | `mov rax,[rbp+0x2C0]` | stack read into rax [V] |
| 846 | 0x666bcde | `mov [rbp+0x130],rax` | stack write [V] |
| 847 | 0x666bce5 | `mov byte ptr [rbp+0x148],0xFF` | stack write tag byte 0xFF [V] |
| 848 | 0x666bcec | `movzx eax,byte ptr [rbp+0x2D8]` | stack read switch byte into eax [V] |
| 849 | 0x666bcf3 | `cmp rax,3` | compare switch value to 3 [V] |
| 850 | 0x666bcf7 | `ja short 0x666BD77` | branch if >3 to default case [V] |
| 851 | 0x666bcf9 | `lea rdx,[0xF2BF500]` | jump-table base address [V] |
| 852 | 0x666bd00 | `movsxd rcx,[rdx+rax*4]` | jump table entry read (signed dword) [V] |
| 853 | 0x666bd04 | `add rcx,rdx` | compute jump target [V] |
| 854 | 0x666bd07 | `jmp rcx` | indirect branch via jump table (targets [?]) [V] |
| 855 | 0x666bd09 | `mov rcx,[rbp+0x2C8]` | case-0 source pointer read [V] |
| 856 | 0x666bd10 | `mov [rbp+0x138],rcx` | output struct field write [V] |
| 857 | 0x666bd17 | `jmp short 0x666BD71` | branch to common tail [V] |
| 858 | 0x666bd19 | `lea rcx,[rbp+0x2C8]` | case-1 source address [V] |
| 859 | 0x666bd20 | `movups xmm0,[rcx]` | read 16 bytes from source [V] |
| 860 | 0x666bd23 | `lea rcx,[rbp+0x88]` | output struct address [V] |
| 861 | 0x666bd2a | `movups [rcx+0xB0],xmm0` | write 16 bytes to output+0xB0 [V] |
| 862 | 0x666bd31 | `jmp short 0x666BD71` | branch to common tail [V] |
| 863 | 0x666bd33 | `lea rcx,[rbp+0x88]` | output struct address [V] |
| 864 | 0x666bd3a | `movups [rcx+0xB0],xmm6` | case-2 default: write zero xmm to output+0xB0 [V] |

Branches/exits in phase: 0x666BCA3 (line 825,831), 0x666BCA9 (828), 0x666BD77 (850), jump table indirect (854, targets 0x666BD09/0x666BD19/0x666BD33/0x666BD77), 0x666BD71 (857,862). No exit of the tag-7 body in this phase. No description field reads; no calls.

### lines 865..904 (0x666bd41..0x666be18)

Default switch case: on non-null [rbp+0x2D0] (rcx) increment its refcount ([rcx+8]), copy the source record at [rbp+0x2C8] (fields +0x28->[rbp+0x138], +0x18->[rbp+0x140]+0xC8, 16 bytes) into the output struct and store tag al at [rbp+0x148]; then zero a nested block ([rbp-0x10],[rbp-8],[rbp+0x5C3..]) and call 0xE869FF0 to init the [rbp+0x478] output struct, with refcount inc on non-null [rbp+0x90]. All stack memory ([rbp+...]); no description field reads.

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 865 | 0x666bd41 | `mov rcx,[rbp+0x2D0]` | stack read candidate pointer into rcx [V] |
| 866 | 0x666bd48 | `test rcx,rcx` | test candidate null [V] |
| 867 | 0x666bd4b | `je short 0x666BD5A` | branch if null to zero path [V] |
| 868 | 0x666bd4d | `lock inc dword ptr [rcx+8]` | refcount inc on candidate [rcx+8] read/write [V] |
| 869 | 0x666bd51 | `mov rcx,[rbp+0x2D0]` | re-read candidate pointer [V] |
| 870 | 0x666bd58 | `jmp short 0x666BD5C` | branch to store [V] |
| 871 | 0x666bd5a | `xor ecx,ecx` | zero path: ecx=0 (null candidate) [V] |
| 872 | 0x666bd5c | `mov rdx,[rbp+0x2C8]` | source record pointer read [V] |
| 873 | 0x666bd63 | `mov [rbp+0x138],rdx` | output struct field write [V] |
| 874 | 0x666bd6a | `mov [rbp+0x140],rcx` | output struct field write (candidate or 0) [V] |
| 875 | 0x666bd71 | `mov [rbp+0x148],al` | store tag byte [V] |
| 876 | 0x666bd77 | `lea rdx,[rbp+0x2C8]` | source record address [V] |
| 877 | 0x666bd7e | `mov rax,[rdx+0x28]` | read source+0x28 (8 bytes) into rax [V] |
| 878 | 0x666bd82 | `lea rcx,[rbp+0x88]` | output struct address [V] |
| 879 | 0x666bd89 | `mov [rcx+0xD8],rax` | write output+0xD8 [V] |
| 880 | 0x666bd90 | `movups xmm0,[rdx+0x18]` | read source+0x18 (16 bytes) into xmm0 [V] |
| 881 | 0x666bd94 | `movups [rcx+0xC8],xmm0` | write output+0xC8 [V] |
| 882 | 0x666bd9b | `mov qword ptr [rbp-0x10],0` | stack write zero [V] |
| 883 | 0x666bda3 | `mov dword ptr [rbp-8],0` | stack write zero [V] |
| 884 | 0x666bdaa | `lea rax,[rbp+0x5C3]` | address of nested init buffer [V] |
| 885 | 0x666bdb1 | `mov qword ptr [rax+6],0` | write zero [rax+6] [V] |
| 886 | 0x666bdb9 | `mov qword ptr [rax],0` | write zero [rax] [V] |
| 887 | 0x666bdc0 | `mov rax,[rbp]` | stack read into rax [V] |
| 888 | 0x666bdc4 | `mov [rbp+0x3F0],rax` | stack write [V] |
| 889 | 0x666bdcb | `lea rcx,[rbp+0x3F8]` | address for call arg [V] |
| 890 | 0x666bdd2 | `lea rdx,[rbp+8]` | address for call arg [V] |
| 891 | 0x666bdd6 | `call 0xE869FF0` | call 0xE869FF0 (init nested struct) [V] |
| 892 | 0x666bddb | `nop` | padding nop [V] |
| 893 | 0x666bddc | `mov rax,[rbp+0x80]` | stack read into rax [V] |
| 894 | 0x666bde3 | `mov [rbp+0x470],rax` | stack write [V] |
| 895 | 0x666bdea | `mov qword ptr [rbp+0x80],0` | stack write zero [V] |
| 896 | 0x666bdf5 | `lea rax,[rbp+0x478]` | nested struct address [V] |
| 897 | 0x666bdfc | `movups [rax],xmm6` | write zero xmm to nested struct [V] |
| 898 | 0x666bdff | `mov rax,[rbp+0x90]` | stack read candidate into rax [V] |
| 899 | 0x666be06 | `test rax,rax` | test candidate null [V] |
| 900 | 0x666be09 | `je short 0x666BE20` | branch if null [V] |
| 901 | 0x666be0b | `lock inc dword ptr [rax+8]` | refcount inc on candidate [rax+8] read/write [V] |
| 902 | 0x666be0f | `mov rax,[rbp+0x90]` | re-read candidate [V] |
| 903 | 0x666be16 | `jmp short 0x666BE22` | branch to store [V] |
| 904 | 0x666be18 | `nop [rax+rax]` | padding nop [V] |

Branches: 0x666BD5A (867), 0x666BD5C (870), 0x666BE20 (900), 0x666BE22 (903). Call: 0xE869FF0 (891). No exit of the tag-7 body. No description field reads; no other calls.

### lines 905..944 (0x666be20..0x666bef3)

Continues building the [rbp+0x478] nested output struct: stores candidate pointers [rbp+0x88]/[rbp+0x98] with refcount incs on non-null [rbp+0x90] and [rbp+0xA0], copies 16-byte blocks from [rbp+0xA8]/[rbp+0xB8], then switches on tag byte [rbp+0x108]: ==0 copies [rbp+0xC8..0xF8] to [rbp+0x4B8..0x4E8], !=0 and ==1 goes to 0x666BF05, >1 falls to 0x666BEF0. All stack memory; no description field reads, no calls.

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 905 | 0x666be20 | `xor eax,eax` | null path: eax=0 [V] |
| 906 | 0x666be22 | `mov rcx,[rbp+0x88]` | stack read into rcx [V] |
| 907 | 0x666be29 | `mov [rbp+0x478],rcx` | nested struct field write [V] |
| 908 | 0x666be30 | `mov [rbp+0x480],rax` | nested struct field write (ptr or 0) [V] |
| 909 | 0x666be37 | `lea rax,[rbp+0x478]` | nested struct address [V] |
| 910 | 0x666be3e | `movups [rax+0x10],xmm6` | write zero xmm to nested+0x10 [V] |
| 911 | 0x666be42 | `mov rax,[rbp+0xA0]` | stack read candidate into rax [V] |
| 912 | 0x666be49 | `test rax,rax` | test candidate null [V] |
| 913 | 0x666be4c | `je short 0x666BE60` | branch if null [V] |
| 914 | 0x666be4e | `lock inc dword ptr [rax+8]` | refcount inc on candidate [rax+8] read/write [V] |
| 915 | 0x666be52 | `mov rax,[rbp+0xA0]` | re-read candidate [V] |
| 916 | 0x666be59 | `jmp short 0x666BE62` | branch to store [V] |
| 917 | 0x666be5b | `nop [rax+rax]` | padding nop [V] |
| 918 | 0x666be60 | `xor eax,eax` | null path: eax=0 [V] |
| 919 | 0x666be62 | `mov rcx,[rbp+0x98]` | stack read into rcx [V] |
| 920 | 0x666be69 | `mov [rbp+0x488],rcx` | nested struct field write [V] |
| 921 | 0x666be70 | `mov [rbp+0x490],rax` | nested struct field write (ptr or 0) [V] |
| 922 | 0x666be77 | `movups xmm0,[rbp+0xA8]` | stack read 16 bytes into xmm0 [V] |
| 923 | 0x666be7e | `movups [rbp+0x498],xmm0` | stack write 16 bytes [V] |
| 924 | 0x666be85 | `movups xmm0,[rbp+0xB8]` | stack read 16 bytes into xmm0 [V] |
| 925 | 0x666be8c | `movups [rbp+0x4A8],xmm0` | stack write 16 bytes [V] |
| 926 | 0x666be93 | `mov byte ptr [rbp+0x4F8],0xFF` | stack write tag byte 0xFF [V] |
| 927 | 0x666be9a | `movzx eax,byte ptr [rbp+0x108]` | stack read tag byte into eax [V] |
| 928 | 0x666bea1 | `movzx ecx,al` | zero-extend tag [V] |
| 929 | 0x666bea4 | `cmp ecx,1` | compare tag to 1 [V] |
| 930 | 0x666bea7 | `jg short 0x666BEF0` | branch if tag > 1 [V] |
| 931 | 0x666bea9 | `test ecx,ecx` | test tag == 0 [V] |
| 932 | 0x666beab | `jne short 0x666BF05` | branch if tag != 0 (i.e. tag==1 path) [V] |
| 933 | 0x666bead | `movups xmm0,[rbp+0xC8]` | stack read 16 bytes into xmm0 [V] |
| 934 | 0x666beb4 | `movups xmm1,[rbp+0xD8]` | stack read 16 bytes into xmm1 [V] |
| 935 | 0x666bebb | `movups xmm2,[rbp+0xE8]` | stack read 16 bytes into xmm2 [V] |
| 936 | 0x666bec2 | `movups xmm3,[rbp+0xF8]` | stack read 16 bytes into xmm3 [V] |
| 937 | 0x666bec9 | `movups [rbp+0x4B8],xmm0` | stack write 16 bytes [V] |
| 938 | 0x666bed0 | `movups [rbp+0x4C8],xmm1` | stack write 16 bytes [V] |
| 939 | 0x666bed7 | `movups [rbp+0x4D8],xmm2` | stack write 16 bytes [V] |
| 940 | 0x666bede | `movups [rbp+0x4E8],xmm3` | stack write 16 bytes [V] |
| 941 | 0x666bee5 | `jmp short 0x666BF33` | branch to merge point [V] |
| 942 | 0x666bee7 | `nop [rax+rax]` | padding nop [V] |
| 943 | 0x666bef0 | `cmp ecx,2` | compare tag to 2 [V] |
| 944 | 0x666bef3 | `jne short 0x666BF39` | branch if tag != 2 [V] |

Branches: 0x666BE60 (913), 0x666BE62 (916), 0x666BEF0 (930), 0x666BF05 (932), 0x666BF33 (941), 0x666BF39 (944). No exit of the tag-7 body. No description field reads; no calls.

### lines 945..984 (0x666bef5..0x666bfe5)

Tag==1 case moves [rbp+0xD8] (nulling the source) into [rbp+0x4B8/0x4C8] and clears [rbp+0xC8]; then copies [rbp+0x110]/[rbp+0x120] to [rbp+0x500/0x510], stores [rbp+0x130] at [rbp+0x520] and tag byte 0xFF at [rbp+0x538]. Second switch on tag byte [rbp+0x148]: >3 branches to 0x666C00F, else jump table at 0xF2BF510 copies either [rbp+0x138] or ([rbp+0x88]+0xB0) into the output, defaulting to zeroing [rbp+0x478]+0xB0; then refcount inc on non-null [rbp+0x140]. All stack memory; no description field reads, no calls.

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 945 | 0x666bef5 | `mov rcx,[rbp+0xC8]` | stack read into rcx [V] |
| 946 | 0x666befc | `mov [rbp+0x4B8],rcx` | nested struct field write [V] |
| 947 | 0x666bf03 | `jmp short 0x666BF33` | branch to merge point [V] |
| 948 | 0x666bf05 | `mov rcx,[rbp+0xD8]` | stack read into rcx [V] |
| 949 | 0x666bf0c | `mov qword ptr [rbp+0xD8],0` | stack write zero (consume source) [V] |
| 950 | 0x666bf17 | `movups xmm0,[rbp+0xC8]` | stack read 16 bytes into xmm0 [V] |
| 951 | 0x666bf1e | `movups [rbp+0xC8],xmm6` | stack write zero xmm (consume source) [V] |
| 952 | 0x666bf25 | `movups [rbp+0x4B8],xmm0` | nested struct field write [V] |
| 953 | 0x666bf2c | `mov [rbp+0x4C8],rcx` | nested struct field write [V] |
| 954 | 0x666bf33 | `mov [rbp+0x4F8],al` | store tag byte [V] |
| 955 | 0x666bf39 | `movups xmm0,[rbp+0x110]` | stack read 16 bytes into xmm0 [V] |
| 956 | 0x666bf40 | `movups xmm1,[rbp+0x120]` | stack read 16 bytes into xmm1 [V] |
| 957 | 0x666bf47 | `mov qword ptr [rbp+0x118],0` | stack write zero [V] |
| 958 | 0x666bf52 | `movups [rbp+0x500],xmm0` | stack write 16 bytes [V] |
| 959 | 0x666bf59 | `movups [rbp+0x120],xmm6` | stack write zero xmm [V] |
| 960 | 0x666bf60 | `movups [rbp+0x510],xmm1` | stack write 16 bytes [V] |
| 961 | 0x666bf67 | `mov rax,[rbp+0x130]` | stack read into rax [V] |
| 962 | 0x666bf6e | `mov [rbp+0x520],rax` | stack write [V] |
| 963 | 0x666bf75 | `mov byte ptr [rbp+0x538],0xFF` | stack write tag byte 0xFF [V] |
| 964 | 0x666bf7c | `movzx eax,byte ptr [rbp+0x148]` | stack read switch byte into eax [V] |
| 965 | 0x666bf83 | `cmp rax,3` | compare switch value to 3 [V] |
| 966 | 0x666bf87 | `ja 0x666C00F` | branch if >3 to default case (near jump) [V] |
| 967 | 0x666bf8d | `lea rdx,[0xF2BF510]` | jump-table base address [V] |
| 968 | 0x666bf94 | `movsxd rcx,[rdx+rax*4]` | jump table entry read (signed dword) [V] |
| 969 | 0x666bf98 | `add rcx,rdx` | compute jump target [V] |
| 970 | 0x666bf9b | `jmp rcx` | indirect branch via jump table (targets [?]) [V] |
| 971 | 0x666bf9d | `mov rcx,[rbp+0x138]` | case-0 source pointer read [V] |
| 972 | 0x666bfa4 | `mov [rbp+0x528],rcx` | output struct field write [V] |
| 973 | 0x666bfab | `jmp short 0x666C009` | branch to common tail [V] |
| 974 | 0x666bfad | `lea rcx,[rbp+0x88]` | case-1 source address [V] |
| 975 | 0x666bfb4 | `movups xmm0,[rcx+0xB0]` | read source+0xB0 (16 bytes) into xmm0 [V] |
| 976 | 0x666bfbb | `lea rcx,[rbp+0x478]` | output struct address [V] |
| 977 | 0x666bfc2 | `movups [rcx+0xB0],xmm0` | write output+0xB0 [V] |
| 978 | 0x666bfc9 | `jmp short 0x666C009` | branch to common tail [V] |
| 979 | 0x666bfcb | `lea rcx,[rbp+0x478]` | case-2 default output address [V] |
| 980 | 0x666bfd2 | `movups [rcx+0xB0],xmm6` | write zero xmm to output+0xB0 [V] |
| 981 | 0x666bfd9 | `mov rcx,[rbp+0x140]` | stack read candidate into rcx [V] |
| 982 | 0x666bfe0 | `test rcx,rcx` | test candidate null [V] |
| 983 | 0x666bfe3 | `je short 0x666BFF2` | branch if null [V] |
| 984 | 0x666bfe5 | `lock inc dword ptr [rcx+8]` | refcount inc on candidate [rcx+8] read/write [V] |

Branches: 0x666BF33 (947), 0x666C00F (966), jump table indirect (970, targets 0x666BF9D/0x666BFAD/0x666BFBC/0x666C00F), 0x666C009 (973,978), 0x666BFF2 (983). No exit of the tag-7 body (0x666C00F/0x666C009 are within this listing range). No description field reads; no calls.

### lines 985..1024 (0x666bfe9..0x666c0e8)

Tail of second switch: stores [rbp+0x138]/[rbp+0x140] at [rbp+0x528/0x530] and tag al at [rbp+0x538], then copies [rbp+0x88]+0xD8/0xC8 to [rbp+0x478]+0xD8/0xC8; initializes a descriptor block at [rbp+0x478] (dword 0 at 0x560, type byte 0x0F at 0x564, dword 0 at 0x568, word 0 at 0x56C, byte 2 at 0x56E, dword 0 at 0x570, byte 0 at 0x574, zero xmm at 0x100, [rbp-8] at 0x118, [rbp-0x10] at 0x110, byte 8 at 0x594, qword 0 at 0x598, dword 0 at 0x5A0, byte 8 at 0x5A4, [rbp+0x5D0] byte at [rdx+0x13D], [rbp+0x5C0] xmm at [rdx+0x12D], byte 0xFF at 0x5B6). Then computes r12+0x10+0x9D0 and calls 0x5ABA5C0, result into rbx (r12+0x10 meaning [?]).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 985 | 0x666bfe9 | `mov rcx,[rbp+0x140]` | re-read candidate (non-null path) [V] |
| 986 | 0x666bff0 | `jmp short 0x666BFF4` | branch to store [V] |
| 987 | 0x666bff2 | `xor ecx,ecx` | null path: ecx=0 [V] |
| 988 | 0x666bff4 | `mov rdx,[rbp+0x138]` | stack read into rdx [V] |
| 989 | 0x666bffb | `mov [rbp+0x528],rdx` | output struct field write [V] |
| 990 | 0x666c002 | `mov [rbp+0x530],rcx` | output struct field write [V] |
| 991 | 0x666c009 | `mov [rbp+0x538],al` | store tag byte [V] |
| 992 | 0x666c00f | `lea rcx,[rbp+0x88]` | source record address [V] |
| 993 | 0x666c016 | `mov rax,[rcx+0xD8]` | read source+0xD8 (8 bytes) into rax [V] |
| 994 | 0x666c01d | `lea rdx,[rbp+0x478]` | destination address [V] |
| 995 | 0x666c024 | `mov [rdx+0xD8],rax` | write dest+0xD8 [V] |
| 996 | 0x666c02b | `movups xmm0,[rcx+0xC8]` | read source+0xC8 (16 bytes) into xmm0 [V] |
| 997 | 0x666c032 | `movups [rdx+0xC8],xmm0` | write dest+0xC8 [V] |
| 998 | 0x666c039 | `mov dword ptr [rbp+0x560],0` | descriptor field write dword 0 [V] |
| 999 | 0x666c043 | `mov byte ptr [rbp+0x564],0xF` | descriptor field write type byte 0x0F [V] |
| 1000 | 0x666c04a | `mov dword ptr [rbp+0x568],0` | descriptor field write dword 0 [V] |
| 1001 | 0x666c054 | `mov word ptr [rbp+0x56C],0` | descriptor field write word 0 [V] |
| 1002 | 0x666c05d | `mov byte ptr [rbp+0x56E],2` | descriptor field write byte 2 [V] |
| 1003 | 0x666c064 | `mov dword ptr [rbp+0x570],0` | descriptor field write dword 0 [V] |
| 1004 | 0x666c06e | `mov byte ptr [rbp+0x574],0` | descriptor field write byte 0 [V] |
| 1005 | 0x666c075 | `movups [rdx+0x100],xmm6` | write zero xmm to dest+0x100 [V] |
| 1006 | 0x666c07c | `mov eax,[rbp-8]` | stack read into eax [V] |
| 1007 | 0x666c07f | `mov [rdx+0x118],eax` | write dest+0x118 [V] |
| 1008 | 0x666c085 | `mov rax,[rbp-0x10]` | stack read into rax [V] |
| 1009 | 0x666c089 | `mov [rdx+0x110],rax` | write dest+0x110 [V] |
| 1010 | 0x666c090 | `mov byte ptr [rbp+0x594],8` | descriptor field write byte 8 [V] |
| 1011 | 0x666c097 | `mov qword ptr [rbp+0x598],0` | descriptor field write qword 0 [V] |
| 1012 | 0x666c0a2 | `mov dword ptr [rbp+0x5A0],0` | descriptor field write dword 0 [V] |
| 1013 | 0x666c0ac | `mov byte ptr [rbp+0x5A4],8` | descriptor field write byte 8 [V] |
| 1014 | 0x666c0b3 | `movzx eax,byte ptr [rbp+0x5D0]` | stack read byte into eax [V] |
| 1015 | 0x666c0ba | `mov [rdx+0x13D],al` | write dest+0x13D [V] |
| 1016 | 0x666c0c0 | `movups xmm0,[rbp+0x5C0]` | stack read 16 bytes into xmm0 [V] |
| 1017 | 0x666c0c7 | `movups [rdx+0x12D],xmm0` | write dest+0x12D [V] |
| 1018 | 0x666c0ce | `mov byte ptr [rbp+0x5B6],0xFF` | descriptor field write byte 0xFF [V] |
| 1019 | 0x666c0d5 | `mov rcx,[r12+0x10]` | r12+0x10 read (r12 meaning [?]) [V][?] |
| 1020 | 0x666c0da | `mov eax,0x9D0` | constant 0x9D0 [V] |
| 1021 | 0x666c0df | `add rcx,rax` | compute target address [V] |
| 1022 | 0x666c0e2 | `call 0x5ABA5C0` | call 0x5ABA5C0 [V] |
| 1023 | 0x666c0e7 | `nop` | padding nop [V] |
| 1024 | 0x666c0e8 | `mov rbx,rax` | call result into rbx [V] |

Branches: 0x666BFF4 (986). Call: 0x5ABA5C0 (1022). No exit of the tag-7 body. No description field reads confirmed (r12+0x10 provenance [?]); no other calls.

### lines 1025..1064 (0x666c0eb..0x666c1d3)

Zeroes a large stack region ([rbp+0x1D0..0x280] via xmm6 stores, [rbp+0x290] via qword 0), then reads global pointer [0x1233E1B0]->[rax]->[rax+0x10] and calls qword ptr [0xF99FFA0] with dl=0x4A, storing al at [rbp+0x670] (flag/version byte). If rbx+0x758 != rbx+0x760, copies the descriptor block at [rbp+0x560] (xmm at +0x00, dword at +0x10, byte at +0x14, floats at +0x18/+0x1C/+0x20/+0x24) into the rbx object at rbx+0x758 and advances rbx+0x758 by 0x58. rbx = result of earlier call 0x5ABA5C0 (object buffer).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1025 | 0x666c0eb | `movaps [rbp+0x280],xmm6` | stack write zero xmm [V] |
| 1026 | 0x666c0f2 | `movaps [rbp+0x270],xmm6` | stack write zero xmm [V] |
| 1027 | 0x666c0f9 | `movaps [rbp+0x260],xmm6` | stack write zero xmm [V] |
| 1028 | 0x666c100 | `movaps [rbp+0x250],xmm6` | stack write zero xmm [V] |
| 1029 | 0x666c107 | `movaps [rbp+0x240],xmm6` | stack write zero xmm [V] |
| 1030 | 0x666c10e | `movaps [rbp+0x230],xmm6` | stack write zero xmm [V] |
| 1031 | 0x666c115 | `movaps [rbp+0x220],xmm6` | stack write zero xmm [V] |
| 1032 | 0x666c11c | `movaps [rbp+0x210],xmm6` | stack write zero xmm [V] |
| 1033 | 0x666c123 | `movaps [rbp+0x200],xmm6` | stack write zero xmm [V] |
| 1034 | 0x666c12a | `movaps [rbp+0x1F0],xmm6` | stack write zero xmm [V] |
| 1035 | 0x666c131 | `movaps [rbp+0x1E0],xmm6` | stack write zero xmm [V] |
| 1036 | 0x666c138 | `movaps [rbp+0x1D0],xmm6` | stack write zero xmm [V] |
| 1037 | 0x666c13f | `mov qword ptr [rbp+0x290],0` | stack write zero [V] |
| 1038 | 0x666c14a | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1039 | 0x666c151 | `mov rax,[rcx]` | global->first field read [V] |
| 1040 | 0x666c154 | `mov rax,[rax+0x10]` | read rax+0x10 (vtable-ish pointer) [V] |
| 1041 | 0x666c158 | `mov dl,0x4A` | set dl=0x4A (arg) [V] |
| 1042 | 0x666c15a | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1043 | 0x666c160 | `nop` | padding nop [V] |
| 1044 | 0x666c161 | `mov [rbp+0x670],al` | store call result byte at [rbp+0x670] [V] |
| 1045 | 0x666c167 | `mov rdx,[rbx+0x758]` | rbx object write cursor read [V] |
| 1046 | 0x666c16e | `cmp rdx,[rbx+0x760]` | compare cursor to end [rbx+0x760] read [V] |
| 1047 | 0x666c175 | `je 0x666C200` | branch if buffer full (near jump) [V] |
| 1048 | 0x666c17b | `lea rcx,[rbp+0x560]` | source descriptor block address [V] |
| 1049 | 0x666c182 | `mov eax,[rcx+0x10]` | read source+0x10 (dword) [V] |
| 1050 | 0x666c185 | `mov [rdx+0x10],eax` | write dest+0x10 [V] |
| 1051 | 0x666c188 | `movups xmm0,[rcx]` | read source+0x00 (16 bytes) [V] |
| 1052 | 0x666c18b | `movups [rdx],xmm0` | write dest+0x00 [V] |
| 1053 | 0x666c18e | `movzx eax,byte ptr [rbp+0x574]` | stack read byte [V] |
| 1054 | 0x666c195 | `mov [rdx+0x14],al` | write dest+0x14 [V] |
| 1055 | 0x666c198 | `movss xmm0,[rbp+0x578]` | stack read float [V] |
| 1056 | 0x666c1a0 | `movss [rdx+0x18],xmm0` | write dest+0x18 float [V] |
| 1057 | 0x666c1a5 | `movss xmm0,[rbp+0x57C]` | stack read float [V] |
| 1058 | 0x666c1ad | `movss [rdx+0x1C],xmm0` | write dest+0x1C float [V] |
| 1059 | 0x666c1b2 | `movss xmm0,[rbp+0x580]` | stack read float [V] |
| 1060 | 0x666c1ba | `movss [rdx+0x20],xmm0` | write dest+0x20 float [V] |
| 1061 | 0x666c1bf | `movss xmm0,[rbp+0x584]` | stack read float [V] |
| 1062 | 0x666c1c7 | `movss [rdx+0x24],xmm0` | write dest+0x24 float [V] |
| 1063 | 0x666c1cc | `lea rax,[rbp+0x478]` | nested struct address [V] |
| 1064 | 0x666c1d3 | `movups xmm0,[rax+0x110]` | read rax+0x110 (16 bytes) [V] |

Branches: 0x666C200 (1047). Call: qword ptr [0xF99FFA0] (1042). No exit of the tag-7 body (0x666C200 is within range). No description field reads (all reads are stack [rbp+...] or rbx object). No other calls.

### lines 1065..1104 (0x666c1d3..0x666c287)

Writes remaining descriptor fields (xmm at dest+0x28/+0x38/+0x47), advances rbx+0x758 by 0x58; if buffer was full (je path) calls 0x6760A80 with rcx=[rbx+0x750], r8=[rbp+0x560] to grow the object buffer. Then a second global call sequence: reads [0x1233E1B0]->[rax]->[rax+0x10], calls qword ptr [0xF99FFA0] with dl=[rbp+0x670], stores edx. Finally begins an object-slot rotation: rax=r12; r12=r14; r14=[rbx+0x878]; compares r14 (slot cursor) to [rbx+0x880] (slot end). r15 still holds description base (untouched this phase).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1065 | 0x666c1d3 | `movups xmm0,[rax+0x110]` | read rax+0x110 (16 bytes) into xmm0 [V] |
| 1066 | 0x666c1da | `movups xmm1,[rax+0x120]` | read rax+0x120 (16 bytes) into xmm1 [V] |
| 1067 | 0x666c1e1 | `movups xmm2,[rax+0x12F]` | read rax+0x12F (16 bytes) into xmm2 [V] |
| 1068 | 0x666c1e8 | `movups [rdx+0x28],xmm0` | write dest+0x28 [V] |
| 1069 | 0x666c1ec | `movups [rdx+0x38],xmm1` | write dest+0x38 [V] |
| 1070 | 0x666c1f0 | `movups [rdx+0x47],xmm2` | write dest+0x47 [V] |
| 1071 | 0x666c1f4 | `add qword ptr [rbx+0x758],0x58` | rbx+0x758 read/write, advance cursor by 0x58 [V] |
| 1072 | 0x666c1fc | `jmp short 0x666C214` | branch past full-buffer path [V] |
| 1073 | 0x666c1fe | `xchg ax,ax` | padding nop [V] |
| 1074 | 0x666c200 | `lea rcx,[rbx+0x750]]` | buffer base address [V] |
| 1075 | 0x666c207 | `lea r8,[rbp+0x560]]` | source descriptor block address [V] |
| 1076 | 0x666c20e | `call 0x6760A80` | call 0x6760A80 (grow buffer) [V] |
| 1077 | 0x666c213 | `nop` | padding nop [V] |
| 1078 | 0x666c214 | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1079 | 0x666c21b | `mov rax,[rcx]` | global->first field read [V] |
| 1080 | 0x666c21e | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1081 | 0x666c222 | `movzx edx,byte ptr [rbp+0x670]` | stack read flag byte into edx [V] |
| 1082 | 0x666c229 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1083 | 0x666c22f | `nop` | padding nop [V] |
| 1084 | 0x666c230 | `mov eax,[rbx+0x758]` | rbx object cursor read [V] |
| 1085 | 0x666c236 | `sub eax,[rbx+0x750]` | cursor minus buffer base [rbx+0x750] read [V] |
| 1086 | 0x666c23c | `shr eax,3` | divide by 8 [V] |
| 1087 | 0x666c23f | `imul eax,0xFFFF8BA3` | multiply by magic [V] |
| 1088 | 0x666c245 | `dec eax` | [V] |
| 1089 | 0x666c247 | `mov [rbp+0x1FC],ax` | stack write count [V] |
| 1090 | 0x666c24e | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1091 | 0x666c255 | `mov rax,[rcx]` | global->first field read [V] |
| 1092 | 0x666c258 | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1093 | 0x666c25c | `mov dl,0x4A` | set dl=0x4A [V] |
| 1094 | 0x666c25e | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1095 | 0x666c264 | `nop` | padding nop [V] |
| 1096 | 0x666c265 | `mov edx,eax` | [V] |
| 1097 | 0x666c267 | `mov rax,r12` | r12 read [V] |
| 1098 | 0x666c26a | `mov r12,r14` | r14 read, r12=r14 [V] |
| 1099 | 0x666c26d | `mov r14,[rbx+0x878]` | rbx+0x878 read into r14 (slot cursor) [V] |
| 1100 | 0x666c274 | `cmp r14,[rbx+0x880]` | compare cursor to slot end [rbx+0x880] read [V] |
| 1101 | 0x666c27b | `je short 0x666C2A0` | branch if cursor == end [V] |
| 1102 | 0x666c27d | `inc r14` | advance cursor [V] |
| 1103 | 0x666c280 | `mov [rbx+0x878],r14` | rbx+0x878 write (store cursor) [V] |
| 1104 | 0x666c287 | `mov r14,r12` | r12 read, r14=r12 [V] |

Branches: 0x666C214 (1072), 0x666C2A0 (1101). Calls: 0x6760A80 (1076), qword ptr [0xF99FFA0] (1082, 1094). No exit of the tag-7 body (targets within range). No description field reads; r15 still = description base [rbp+0x668].

### lines 1105..1144 (0x666c28a..0x666c33a)

If slot cursor != end, advance/store cursor ([rbx+0x878]) and jump to 0x666C44A. Else (cursor == end) r15 is REPURPOSED from description base to a buffer offset (r14-[rbx+0x870]); guards reject huge/negative sizes (exits to 0x6670A94 and 0x6670C3B, both out of this listing range), computes a clamped size r13, and if non-zero and within [0x1000, 0xFFFFFFD9) allocates via qword ptr [0xF99FFA0] (rcx=[0x1233E1A8]->[rax+8], rdx=size+0x27 aligned to 0x20) and stores the original size at [rsi-8]. Exits to 0x666C838 on alloc failure (within range, line 1426). r15 no longer holds description base (restored at line 1181).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1105 | 0x666c28a | `mov r12,rax` | rax read, r12=rax [V] |
| 1106 | 0x666c28d | `jmp 0x666C44A` | branch to common tail (within range, line 1207) [V] |
| 1107 | 0x666c292 | `nop [rax+rax]` | padding nop [V] |
| 1108 | 0x666c2a0 | `mov r15,r14` | r15 = r14 (slot cursor); r15 NO LONGER description base [V][I] |
| 1109 | 0x666c2a3 | `sub r15,[rbx+0x870]` | r15 = buffer offset; rbx+0x870 read [V] |
| 1110 | 0x666c2aa | `mov rcx,0x7FFFFFFFFFFFFFFF` | sentinel max [V] |
| 1111 | 0x666c2b4 | `cmp r15,rcx` | compare offset to sentinel [V] |
| 1112 | 0x666c2b7 | `mov [rbp+0x670],dl` | stack write dl [V] |
| 1113 | 0x666c2bd | `je 0x6670A94` | EXIT of tag-7 body if offset == sentinel (out of range) [V] |
| 1114 | 0x666c2c3 | `lea r8,[r15+1]` | [V] |
| 1115 | 0x666c2c7 | `mov r13,r15` | [V] |
| 1116 | 0x666c2ca | `shr r13,1` | [V] |
| 1117 | 0x666c2cd | `mov rax,r13` | [V] |
| 1118 | 0x666c2d0 | `xor rax,rcx` | [V] |
| 1119 | 0x666c2d3 | `add r13,r15` | [V] |
| 1120 | 0x666c2d6 | `cmp r13,r8` | [V] |
| 1121 | 0x666c2d9 | `mov [rbp+0x658],r8` | stack write [V] |
| 1122 | 0x666c2e0 | `cmovbe r13,r8` | clamp size [V] |
| 1123 | 0x666c2e4 | `cmp r15,rax` | [V] |
| 1124 | 0x666c2e7 | `cmova r13,rcx` | clamp size [V] |
| 1125 | 0x666c2eb | `test r13,r13` | test size zero [V] |
| 1126 | 0x666c2ee | `je 0x666C3A9` | branch if size == 0 (within range, line 1176) [V] |
| 1127 | 0x666c2f4 | `cmp r13,0x1000` | compare size to 0x1000 [V] |
| 1128 | 0x666c2fb | `jb short 0x666C349` | branch if small alloc path (within range, line 1149) [V] |
| 1129 | 0x666c2fd | `cmp r13,0xFFFFFFFFFFFFFFD9` | compare size to max [V] |
| 1130 | 0x666c301 | `jae 0x6670C3B` | EXIT of tag-7 body if size too large (out of range) [V] |
| 1131 | 0x666c307 | `lea rdi,[r13+0x27]` | size + 0x27 [V] |
| 1132 | 0x666c30b | `mov rcx,[0x1233E1A8]` | absolute read of global pointer [V] |
| 1133 | 0x666c312 | `mov rax,[rcx]` | global->first field read [V] |
| 1134 | 0x666c315 | `mov rax,[rax+8]` | read rax+0x8 (allocator fn ptr) [V] |
| 1135 | 0x666c319 | `mov rdx,rdi` | size arg [V] |
| 1136 | 0x666c31c | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (allocate) [V] |
| 1137 | 0x666c322 | `nop` | padding nop [V] |
| 1138 | 0x666c323 | `mov rsi,rax` | alloc result into rsi [V] |
| 1139 | 0x666c326 | `test rax,rax` | test alloc success [V] |
| 1140 | 0x666c329 | `je 0x666C838` | branch on alloc failure (within range, line 1426) [V] |
| 1141 | 0x666c32f | `mov rax,rsi` | [V] |
| 1142 | 0x666c332 | `add rsi,0x27` | adjust pointer [V] |
| 1143 | 0x666c336 | `and rsi,0xFFFFFFFFFFFFFFE0` | align down to 0x20 [V] |
| 1144 | 0x666c33a | `mov [rsi-8],rax` | store original size at [rsi-8] [V] |

Branches: 0x666C44A (1106), 0x6670A94 EXIT (1113), 0x666C3A9 (1126), 0x666C349 (1128), 0x6670C3B EXIT (1130), 0x666C838 (1140). Call: qword ptr [0xF99FFA0] (1136). No description field reads (r15 repurposed as offset).

### lines 1145..1184 (0x666c349..0x666c3c4)

Small-alloc path (from line 1128): allocate r13 bytes via qword ptr [0xF99FFA0] (rcx=[0x1233E1A8]->[rax+8]); on failure jump to 0x666C3A0 (call 0x9BC830) or 0x666C3A9 (esi=0). On success, copy old buffer content ([rbx+0x870]..[rbx+0x878]) into the new allocation via call 0xEEC6DE0, then call 0xEEC6DE0 again to link/set the new buffer end. r15 is still the buffer offset (not description base); r14 = slot cursor [rbx+0x878].

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1145 | 0x666c349 | `mov rcx,[0x1233E1A8]` | absolute read of global pointer [V] |
| 1146 | 0x666c350 | `mov rax,[rcx]` | global->first field read [V] |
| 1147 | 0x666c353 | `mov rax,[rax+8]` | read rax+0x8 (allocator fn ptr) [V] |
| 1148 | 0x666c357 | `mov rdx,r13` | size arg [V] |
| 1149 | 0x666c35a | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (allocate) [V] |
| 1150 | 0x666c360 | `nop` | padding nop [V] |
| 1151 | 0x666c361 | `mov rsi,rax` | alloc result into rsi [V] |
| 1152 | 0x666c364 | `test rax,rax` | test alloc success [V] |
| 1153 | 0x666c367 | `je short 0x666C3A0` | branch on alloc failure (within range, line 1168) [V] |
| 1154 | 0x666c369 | `cmp r14,[rbx+0x878]` | compare cursor to end [rbx+0x878] read [V] |
| 1155 | 0x666c370 | `je short 0x666C3B4` | branch if cursor == end (within range, line 1174) [V] |
| 1156 | 0x666c372 | `lea rdi,[rsi+r15]` | new buffer + old offset [r15 = offset] [V] |
| 1157 | 0x666c376 | `inc rdi` | [V] |
| 1158 | 0x666c379 | `mov rdx,[rbx+0x870]` | rbx+0x870 read (buffer base) [V] |
| 1159 | 0x666c380 | `mov r8,r14` | [V] |
| 1160 | 0x666c383 | `sub r8,rdx` | copy length [V] |
| 1161 | 0x666c386 | `mov rcx,rsi` | dest [V] |
| 1162 | 0x666c389 | `call 0xEEC6DE0` | call 0xEEC6DE0 (memmove/copy) [V] |
| 1163 | 0x666c38e | `mov r8,[rbx+0x878]` | rbx+0x878 read (cursor) [V] |
| 1164 | 0x666c395 | `sub r8,r14` | [V] |
| 1165 | 0x666c398 | `mov rcx,rdi` | dest [V] |
| 1166 | 0x666c39b | `mov rdx,r14` | src [V] |
| 1167 | 0x666c39e | `jmp short 0x666C3C4` | branch to second copy call (within range, line 1178) [V] |
| 1168 | 0x666c3a0 | `mov rcx,r13` | failure path arg [V] |
| 1169 | 0x666c3a3 | `call 0x9BC830` | call 0x9BC830 (likely free/abort) [V] |
| 1170 | 0x666c3a8 | `nop` | padding nop [V] |
| 1171 | 0x666c3a9 | `xor esi,esi` | esi=0 (null result) [V] |
| 1172 | 0x666c3ab | `cmp r14,[rbx+0x878]` | [rbx+0x878] read [V] |
| 1173 | 0x666c3b2 | `jne short 0x666C372` | branch to copy path (within range, line 1156) [V] |
| 1174 | 0x666c3b4 | `mov rdx,[rbx+0x870]` | rbx+0x870 read (buffer base) [V] |
| 1175 | 0x666c3bb | `sub r14,rdx` | offset [V] |
| 1176 | 0x666c3be | `mov rcx,rsi` | dest [V] |
| 1177 | 0x666c3c1 | `mov r8,r14` | length [V] |
| 1178 | 0x666c3c4 | `call 0xEEC6DE0` | call 0xEEC6DE0 (memmove/copy) [V] |

Branches: 0x666C3A0 (1153), 0x666C3B4 (1155), 0x666C3C4 (1167), 0x666C372 (1173). Calls: qword ptr [0xF99FFA0] (1149), 0xEEC6DE0 (1162, 1178), 0x9BC830 (1169). No exit of the tag-7 body (all targets within range). No description field reads (r15 is offset).

### lines 1185..1224 (0x666c3c9..0x666c488)

r15 = description base RESTORED from save slot [rbp+0x668]. Then buffer bookkeeping on the rbx object: if [rbx+0x870] non-null, check free space [rbx+0x880]-[rbx+0x870]; if <0x1000 jump to call 0xE935700, else validate preceding allocation size ([rcx-8]...) and EXIT to 0x6670A7A if invalid (out of range). Sets [rbx+0x870]=rsi (new base), [rbx+0x878]=[rbp+0x658]+rsi, [rbx+0x880]=r13+rsi. Rotates r12=[rbp+0x650], r13=[rbp+0x3F0], edx=[rbp+0x670], calls global chain + qword ptr [0xF99FFA0], computes not(eax)+[rbx+0x878] -> [rbp+0x1E4], calls 0x675F3B0 (rcx=[rbx+0x780], rdx=[rbp+0x500]), stores qword 0x5004 at [rbp+0x1D0].

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1185 | 0x666c3c9 | `mov r15,[rbp+0x668]` | r15 = description base RESTORED from save slot [V] |
| 1186 | 0x666c3d0 | `mov rcx,[rbx+0x870]` | rbx+0x870 read (buffer base) [V] |
| 1187 | 0x666c3d7 | `test rcx,rcx` | test base null [V] |
| 1188 | 0x666c3da | `mov r14,r12` | r14=r12 [V] |
| 1189 | 0x666c3dd | `je short 0x666C413` | branch if base null (within range, line 1202) [V] |
| 1190 | 0x666c3df | `mov rdx,[rbx+0x880]` | rbx+0x880 read (buffer end) [V] |
| 1191 | 0x666c3e6 | `sub rdx,rcx` | free space [V] |
| 1192 | 0x666c3e9 | `cmp rdx,0x1000` | compare free to 0x1000 [V] |
| 1193 | 0x666c3f0 | `jb short 0x666C40E` | branch if not enough free (within range, line 1197) [V] |
| 1194 | 0x666c3f2 | `mov rax,[rcx-8]` | read preceding allocation size [rcx-8] [V] |
| 1195 | 0x666c3f6 | `add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 [V] |
| 1196 | 0x666c3fa | `sub rcx,rax` | [V] |
| 1197 | 0x666c3fd | `cmp rcx,0x20` | compare to 0x20 [V] |
| 1198 | 0x666c401 | `jae 0x6670A7A` | EXIT of tag-7 body if invalid (out of range) [V] |
| 1199 | 0x666c407 | `add rdx,0x27` | [V] |
| 1200 | 0x666c40b | `mov rcx,rax` | [V] |
| 1201 | 0x666c40e | `call 0xE935700` | call 0xE935700 [V] |
| 1202 | 0x666c413 | `mov [rbx+0x870],rsi` | rbx+0x870 write (new buffer base) [V] |
| 1203 | 0x666c41a | `mov rax,[rbp+0x658]` | stack read [V] |
| 1204 | 0x666c421 | `add rax,rsi` | [V] |
| 1205 | 0x666c424 | `mov [rbx+0x878],rax` | rbx+0x878 write (new cursor) [V] |
| 1206 | 0x666c42b | `add r13,rsi` | [V] |
| 1207 | 0x666c42e | `mov [rbx+0x880],r13` | rbx+0x880 write (new end) [V] |
| 1208 | 0x666c435 | `mov r12,[rbp+0x650]` | stack read into r12 [V] |
| 1209 | 0x666c43c | `lea r13,[rbp+0x3F0]` | [V] |
| 1210 | 0x666c443 | `movzx edx,byte ptr [rbp+0x670]` | stack read byte into edx [V] |
| 1211 | 0x666c44a | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1212 | 0x666c451 | `mov rax,[rcx]` | global->first field read [V] |
| 1213 | 0x666c454 | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1214 | 0x666c458 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1215 | 0x666c45e | `nop` | padding nop [V] |
| 1216 | 0x666c45f | `mov eax,[rbx+0x870]` | rbx+0x870 read [V] |
| 1217 | 0x666c465 | `not eax` | [V] |
| 1218 | 0x666c467 | `add eax,[rbx+0x878]` | rbx+0x878 read [V] |
| 1219 | 0x666c46d | `mov [rbp+0x1E4],ax` | stack write [V] |
| 1220 | 0x666c474 | `lea rcx,[rbx+0x780]` | rbx object sub-buffer [V] |
| 1221 | 0x666c47b | `lea rdx,[rbp+0x500]` | stack address [V] |
| 1222 | 0x666c482 | `call 0x675F3B0` | call 0x675F3B0 [V] |
| 1223 | 0x666c487 | `nop` | padding nop [V] |
| 1224 | 0x666c488 | `mov qword ptr [rbp+0x1D0],0x5004` | stack write qword 0x5004 [V] |

Branches: 0x666C413 (1189), 0x666C40E (1193), 0x6670A7A EXIT (1198). Calls: 0xE935700 (1201), qword ptr [0xF99FFA0] (1214), 0x675F3B0 (1222). Description register: r15 restored to description base at line 1185 ([rbp+0x668] save slot); no description field reads otherwise.

### lines 1225..1264 (0x666c493..0x666c551)

Computes counts from rbx object sub-buffers: (([rbx+0x788]-[rbx+0x780])>>3)*magic-1 -> [rbp+0x1F8]; (([rbx+0x650]-[rbx+0x648])>>3)*magic-1 -> [rbp+0x212]; (([rbx+0x728]-[rbx+0x720])>>6)-1 -> [rbp+0x200]. Interleaved global calls qword ptr [0xF99FFA0] (dl=0x4A then dl=[rbp+0x670], storing al at [rbp+0x670]), call 0x675FB30 (rcx=[rbx+0x648], rdx=[rbp+0x4B8]) and call 0x67D7410 (rcx=[rbx+0x720], rdx=[rbp+0x478]). r15 still = description base; r12=[rbp+0x650], r13=[rbp+0x3F0] addr.

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1225 | 0x666c493 | `mov eax,[rbx+0x788]` | rbx+0x788 read [V] |
| 1226 | 0x666c499 | `sub eax,[rbx+0x780]` | rbx+0x780 read [V] |
| 1227 | 0x666c49f | `shr eax,3` | [V] |
| 1228 | 0x666c4a2 | `imul eax,0xFFFF8BA3` | magic multiply [V] |
| 1229 | 0x666c4a8 | `dec eax` | [V] |
| 1230 | 0x666c4aa | `mov [rbp+0x1F8],ax` | stack write count [V] |
| 1231 | 0x666c4b1 | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1232 | 0x666c4b8 | `mov rax,[rcx]` | global->first field read [V] |
| 1233 | 0x666c4bb | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1234 | 0x666c4bf | `mov dl,0x4A` | [V] |
| 1235 | 0x666c4c1 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1236 | 0x666c4c7 | `mov [rbp+0x670],al` | stack write flag byte [V] |
| 1237 | 0x666c4cd | `lea rcx,[rbx+0x648]` | rbx object sub-buffer [V] |
| 1238 | 0x666c4d4 | `lea rdx,[rbp+0x4B8]` | stack address [V] |
| 1239 | 0x666c4db | `call 0x675FB30` | call 0x675FB30 [V] |
| 1240 | 0x666c4e0 | `nop` | padding nop [V] |
| 1241 | 0x666c4e1 | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1242 | 0x666c4e8 | `mov rax,[rcx]` | global->first field read [V] |
| 1243 | 0x666c4eb | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1244 | 0x666c4ef | `movzx edx,byte ptr [rbp+0x670]` | stack read byte into edx [V] |
| 1245 | 0x666c4f6 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1246 | 0x666c4fc | `nop` | padding nop [V] |
| 1247 | 0x666c4fd | `mov eax,[rbx+0x650]` | rbx+0x650 read [V] |
| 1248 | 0x666c503 | `sub eax,[rbx+0x648]` | rbx+0x648 read [V] |
| 1249 | 0x666c509 | `shr eax,3` | [V] |
| 1250 | 0x666c50c | `imul eax,0xFFFF8E39` | magic multiply [V] |
| 1251 | 0x666c512 | `dec eax` | [V] |
| 1252 | 0x666c514 | `mov [rbp+0x212],ax` | stack write count [V] |
| 1253 | 0x666c51b | `lea rcx,[rbx+0x720]` | rbx object sub-buffer [V] |
| 1254 | 0x666c522 | `lea rdx,[rbp+0x478]` | stack address [V] |
| 1255 | 0x666c529 | `call 0x67D7410` | call 0x67D7410 [V] |
| 1256 | 0x666c52e | `nop` | padding nop [V] |
| 1257 | 0x666c52f | `mov eax,[rbx+0x728]` | rbx+0x728 read [V] |
| 1258 | 0x666c535 | `sub eax,[rbx+0x720]` | rbx+0x720 read [V] |
| 1259 | 0x666c53b | `shr eax,6` | [V] |
| 1260 | 0x666c53e | `dec eax` | [V] |
| 1261 | 0x666c540 | `mov [rbp+0x200],ax` | stack write count [V] |
| 1262 | 0x666c547 | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1263 | 0x666c54e | `mov rax,[rcx]` | global->first field read [V] |
| 1264 | 0x666c551 | `mov rax,[rax+0x10]` | read rax+0x10 [V] |

Branches: none. Calls: qword ptr [0xF99FFA0] (1235, 1245), 0x675FB30 (1239), 0x67D7410 (1255). No exit of the tag-7 body. No description field reads; r15 still = description base.

### lines 1265..1304 (0x666c555..0x666c622)

Global call qword ptr [0xF99FFA0] (dl=0x4A) storing al at [rbp+0x670]. If rbx+0x770 != rbx+0x778, copies [rbp+0x3F0] (qword; stack copy of desc+0x38 from earlier block) to [rsi], calls 0xE869FF0 (rcx=rsi+8, rdx=[rbp+0x3F8]) to copy a 16-byte struct, stores [rbp+0x470] at [rsi+0x80], zeroes [rbp+0x470], advances rbx+0x770 by 0x88. Else (buffer full) calls 0x6760710 (rcx=[rbx+0x768], rdx=rsi, r8=r13) to grow. Then another global call qword ptr [0xF99FFA0] (dl=[rbp+0x670]), stores qword 0x2017004 at [rbp+0x1D0], computes (([rbx+0x770]-[rbx+0x768])>>3)*magic-1 -> [rbp+0x1FA]. r15 still = description base (untouched).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1265 | 0x666c555 | `mov dl,0x4A` | [V] |
| 1266 | 0x666c557 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1267 | 0x666c55d | `nop` | padding nop [V] |
| 1268 | 0x666c55e | `mov [rbp+0x670],al` | stack write flag byte [V] |
| 1269 | 0x666c564 | `mov rsi,[rbx+0x770]` | rbx+0x770 read (slot cursor) [V] |
| 1270 | 0x666c56b | `cmp rsi,[rbx+0x778]` | compare to slot end [rbx+0x778] read [V] |
| 1271 | 0x666c572 | `je short 0x666C5C0` | branch if full (within range, line 1284) [V] |
| 1272 | 0x666c574 | `mov rax,[rbp+0x3F0]` | stack read (copy of desc+0x38) [V] |
| 1273 | 0x666c57b | `mov [rsi],rax` | write to slot entry [V] |
| 1274 | 0x666c57e | `lea rcx,[rsi+8]` | slot entry+8 [V] |
| 1275 | 0x666c582 | `lea rdx,[rbp+0x3F8]` | stack address (copy of desc+0x30) [V] |
| 1276 | 0x666c589 | `call 0xE869FF0` | call 0xE869FF0 [V] |
| 1277 | 0x666c58e | `nop` | padding nop [V] |
| 1278 | 0x666c58f | `mov rax,[rbp+0x470]` | stack read [V] |
| 1279 | 0x666c596 | `mov [rsi+0x80],rax` | write slot entry+0x80 [V] |
| 1280 | 0x666c59d | `mov qword ptr [rbp+0x470],0` | stack write zero [V] |
| 1281 | 0x666c5a8 | `add qword ptr [rbx+0x770],0x88` | rbx+0x770 read/write, advance by 0x88 [V] |
| 1282 | 0x666c5b3 | `jmp short 0x666C5D6` | branch past grow path (within range, line 1290) [V] |
| 1283 | 0x666c5b5 | `nop [rax+rax]` | padding nop [V] |
| 1284 | 0x666c5c0 | `mov rcx,rbx` | [V] |
| 1285 | 0x666c5c3 | `add rcx,0x768` | [V] |
| 1286 | 0x666c5ca | `mov rdx,rsi` | [V] |
| 1287 | 0x666c5cd | `mov r8,r13` | r13 read ([rbp+0x3F0] addr) [V] |
| 1288 | 0x666c5d0 | `call 0x6760710` | call 0x6760710 (grow slot) [V] |
| 1289 | 0x666c5d5 | `nop` | padding nop [V] |
| 1290 | 0x666c5d6 | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1291 | 0x666c5dd | `mov rax,[rcx]` | global->first field read [V] |
| 1292 | 0x666c5e0 | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1293 | 0x666c5e4 | `movzx edx,byte ptr [rbp+0x670]` | stack read byte into edx [V] |
| 1294 | 0x666c5eb | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1295 | 0x666c5f1 | `nop` | padding nop [V] |
| 1296 | 0x666c5f2 | `mov qword ptr [rbp+0x1D0],0x2017004` | stack write qword 0x2017004 [V] |
| 1297 | 0x666c5fd | `mov eax,[rbx+0x770]` | rbx+0x770 read [V] |
| 1298 | 0x666c603 | `sub eax,[rbx+0x768]` | rbx+0x768 read [V] |
| 1299 | 0x666c609 | `shr eax,3` | [V] |
| 1300 | 0x666c60c | `imul eax,0xFFFFF0F1` | magic multiply [V] |
| 1301 | 0x666c612 | `dec eax` | [V] |
| 1302 | 0x666c614 | `mov [rbp+0x1FA],ax` | stack write count [V] |
| 1303 | 0x666c61b | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1304 | 0x666c622 | `mov rax,[rcx]` | global->first field read [V] |

Branches: 0x666C5C0 (1271), 0x666C5D6 (1282). Calls: qword ptr [0xF99FFA0] (1266, 1294), 0xE869FF0 (1276), 0x6760710 (1288). No exit of the tag-7 body (targets within range). No description field reads in this phase; r15 still = description base.

### lines 1305..1344 (0x666c625..0x666c6d0)

Global call qword ptr [0xF99FFA0] (dl=0x4A) storing al at [rbp+0x670]. If rbx+8 != rbx+0x10, calls 0xEEC6EC0 (rcx=[rbx+8], rdx=[rbp+0x1D0], r8d=0xC8) and advances rbx+8 by 0xC8; else calls 0x5ABA6D0 (rcx=rbx, r8=[rbp+0x1D0]) to grow. Then another global call qword ptr [0xF99FFA0] (dl=[rbp+0x670]), calls 0x674A1D0 twice (rcx=r13=[rbp+0x3F0] addr, then rcx=rbp). Then if byte [rbp+0x2D8] == 3 and [rbp+0x2D0] non-null, decrements refcount [rsi+8]; if it reaches zero, destroys the object via two calls qword ptr [0xF99FFA0] ([rsi] then [rax+8]). r15 still = description base (untouched).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1305 | 0x666c625 | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1306 | 0x666c629 | `mov dl,0x4A` | [V] |
| 1307 | 0x666c62b | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1308 | 0x666c631 | `nop` | padding nop [V] |
| 1309 | 0x666c632 | `mov [rbp+0x670],al` | stack write flag byte [V] |
| 1310 | 0x666c638 | `mov rdx,[rbx+8]` | rbx+8 read [V] |
| 1311 | 0x666c63c | `cmp rdx,[rbx+0x10]` | compare to rbx+0x10 read [V] |
| 1312 | 0x666c640 | `je short 0x666C670` | branch if full (within range, line 1320) [V] |
| 1313 | 0x666c642 | `mov r8d,0xC8` | size arg 0xC8 [V] |
| 1314 | 0x666c648 | `mov rcx,rdx` | src/ptr [V] |
| 1315 | 0x666c64b | `lea rdx,[rbp+0x1D0]` | stack address [V] |
| 1316 | 0x666c652 | `call 0xEEC6EC0` | call 0xEEC6EC0 [V] |
| 1317 | 0x666c657 | `add qword ptr [rbx+8],0xC8` | rbx+8 read/write, advance by 0xC8 [V] |
| 1318 | 0x666c65f | `jmp short 0x666C680` | branch past grow path (within range, line 1324) [V] |
| 1319 | 0x666c661 | `nop [rax+rax]` | padding nop [V] |
| 1320 | 0x666c670 | `mov rcx,rbx` | [V] |
| 1321 | 0x666c673 | `lea r8,[rbp+0x1D0]` | stack address [V] |
| 1322 | 0x666c67a | `call 0x5ABA6D0` | call 0x5ABA6D0 (grow) [V] |
| 1323 | 0x666c67f | `nop` | padding nop [V] |
| 1324 | 0x666c680 | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1325 | 0x666c687 | `mov rax,[rcx]` | global->first field read [V] |
| 1326 | 0x666c68a | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1327 | 0x666c68e | `movzx edx,byte ptr [rbp+0x670]` | stack read byte into edx [V] |
| 1328 | 0x666c695 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1329 | 0x666c69b | `nop` | padding nop [V] |
| 1330 | 0x666c69c | `mov rcx,r13` | r13 read ([rbp+0x3F0] addr) [V] |
| 1331 | 0x666c69f | `call 0x674A1D0` | call 0x674A1D0 [V] |
| 1332 | 0x666c6a4 | `mov rcx,rbp` | [V] |
| 1333 | 0x666c6a7 | `call 0x674A1D0` | call 0x674A1D0 [V] |
| 1334 | 0x666c6ac | `cmp byte ptr [rbp+0x2D8],3` | stack read compare to 3 [V] |
| 1335 | 0x666c6b3 | `jne short 0x666C6F0` | branch if != 3 (within range, line 1348) [V] |
| 1336 | 0x666c6b5 | `mov rsi,[rbp+0x2D0]` | stack read into rsi [V] |
| 1337 | 0x666c6bc | `test rsi,rsi` | test null [V] |
| 1338 | 0x666c6bf | `je short 0x666C6F0` | branch if null (within range, line 1348) [V] |
| 1339 | 0x666c6c1 | `lock dec dword ptr [rsi+8]` | refcount dec [rsi+8] read/write [V] |
| 1340 | 0x666c6c5 | `jne short 0x666C6F0` | branch if not zero (within range, line 1348) [V] |
| 1341 | 0x666c6c7 | `mov rax,[rsi]` | rsi read [V] |
| 1342 | 0x666c6ca | `mov rax,[rax]` | rax read [V] |
| 1343 | 0x666c6cd | `mov rcx,rsi` | [V] |
| 1344 | 0x666c6d0 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 1) [V] |

Branches: 0x666C670 (1312), 0x666C680 (1318), 0x666C6F0 (1335, 1338, 1340). Calls: qword ptr [0xF99FFA0] (1307, 1328, 1344), 0xEEC6EC0 (1316), 0x5ABA6D0 (1322), 0x674A1D0 (1331, 1333). No exit of the tag-7 body (targets within range). No description field reads; r15 still = description base.

### lines 1345..1384 (0x666c6d6..0x666c777)

Continues object destroy: refcount dec [rsi+0xC]; if zero calls qword ptr [0xF99FFA0] via [rax+8] (destroy part 2). Then iterates a heap list [rbp+0x2A8..0x2B0] in 0x28-byte strides; for each entry with byte [rdi+0x18]==2, takes rsi=[rdi+8], refcount dec [rsi+8], and if zero destroys via two calls qword ptr [0xF99FFA0] ([rsi] then [rax+8]). Then if byte [rbp+0x620]==1: rbx=[rbp+0x648], rcx=[rbp+0x5E0], test rcx null. r15 still = description base (untouched).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1345 | 0x666c6d6 | `lock dec dword ptr [rsi+0xC]` | refcount dec [rsi+0xC] read/write [V] |
| 1346 | 0x666c6da | `jne short 0x666C6F0` | branch if not zero (within range, line 1352) [V] |
| 1347 | 0x666c6dc | `mov rax,[rsi]` | rsi read [V] |
| 1348 | 0x666c6df | `mov rax,[rax+8]` | rax+0x8 read [V] |
| 1349 | 0x666c6e3 | `mov rcx,rsi` | [V] |
| 1350 | 0x666c6e6 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 2) [V] |
| 1351 | 0x666c6ec | `nop [rax]` | padding nop [V] |
| 1352 | 0x666c6f0 | `mov rdi,[rbp+0x2A8]` | stack read list head into rdi [V] |
| 1353 | 0x666c6f7 | `test rdi,rdi` | test null [V] |
| 1354 | 0x666c6fa | `je short 0x666C760` | branch if empty (within range, line 1380) [V] |
| 1355 | 0x666c6fc | `mov rbx,[rbp+0x2B0]` | stack read list end into rbx [V] |
| 1356 | 0x666c703 | `jmp short 0x666C714` | branch to loop cond (within range, line 1359) [V] |
| 1357 | 0x666c705 | `nop [rax+rax]` | padding nop [V] |
| 1358 | 0x666c710 | `add rdi,0x28` | advance list entry by 0x28 [V] |
| 1359 | 0x666c714 | `cmp rdi,rbx` | compare to end [V] |
| 1360 | 0x666c717 | `je short 0x666C760` | branch if done (within range, line 1380) [V] |
| 1361 | 0x666c719 | `cmp byte ptr [rdi+0x18],2` | read entry+0x18 byte, compare to 2 [V] |
| 1362 | 0x666c71d | `jne short 0x666C710` | skip if != 2 (within range, line 1358) [V] |
| 1363 | 0x666c71f | `mov rsi,[rdi+8]` | read entry+8 object ptr into rsi [V] |
| 1364 | 0x666c723 | `test rsi,rsi` | test null [V] |
| 1365 | 0x666c726 | `je short 0x666C710` | skip if null (within range, line 1358) [V] |
| 1366 | 0x666c728 | `lock dec dword ptr [rsi+8]` | refcount dec [rsi+8] read/write [V] |
| 1367 | 0x666c72c | `jne short 0x666C710` | skip if not zero (within range, line 1358) [V] |
| 1368 | 0x666c72e | `mov rax,[rsi]` | rsi read [V] |
| 1369 | 0x666c731 | `mov rax,[rax]` | rax read [V] |
| 1370 | 0x666c734 | `mov rcx,rsi` | [V] |
| 1371 | 0x666c737 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 1) [V] |
| 1372 | 0x666c73d | `lock dec dword ptr [rsi+0xC]` | refcount dec [rsi+0xC] read/write [V] |
| 1373 | 0x666c741 | `jne short 0x666C710` | skip if not zero (within range, line 1358) [V] |
| 1374 | 0x666c743 | `mov rax,[rsi]` | rsi read [V] |
| 1375 | 0x666c746 | `mov rax,[rax+8]` | rax+0x8 read [V] |
| 1376 | 0x666c74a | `mov rcx,rsi` | [V] |
| 1377 | 0x666c74d | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 2) [V] |
| 1378 | 0x666c753 | `jmp short 0x666C710` | continue loop (within range, line 1358) [V] |
| 1379 | 0x666c755 | `nop [rax+rax]` | padding nop [V] |
| 1380 | 0x666c760 | `cmp byte ptr [rbp+0x620],1` | stack read compare to 1 [V] |
| 1381 | 0x666c767 | `mov rbx,[rbp+0x648]` | stack read into rbx [V] |
| 1382 | 0x666c76e | `jne short 0x666C7B0` | branch if != 1 (within range, line 1393) [V] |
| 1383 | 0x666c770 | `mov rcx,[rbp+0x5E0]` | stack read into rcx [V] |
| 1384 | 0x666c777 | `test rcx,rcx` | test null [V] |

Branches: 0x666C6F0 (1346), 0x666C760 (1354, 1360), 0x666C714 (1356), 0x666C710 (1362, 1365, 1367, 1373, 1378), 0x666C7B0 (1382). Calls: qword ptr [0xF99FFA0] (1350, 1371, 1377). No exit of the tag-7 body (targets within range). No description field reads; r15 still = description base.

### lines 1385..1424 (0x666c77a..0x666c81d)

If rcx ([rbp+0x5E0]) non-null and [rbp+0x5F0]-[rbp+0x5E0] > 0x1000, validate preceding size ([rcx-8]...) and EXIT to 0x6670A7A if invalid (out of range); else call 0xE935700 with rdx|0x27. Then destroy object [rbp+0x318] (refcount dec [rsi+8]; if zero, destroy via two calls qword ptr [0xF99FFA0]: [rsi] then [rax+8]). Then if [rbp+0x308] non-null, destroy it and EXIT by jumping back to function start 0x666B700 (loop restart — leaves the tag-7 body, before line 825) on refcount-decrement paths. r15 still = description base (untouched).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1385 | 0x666c77a | `je short 0x666C7B0` | branch if rcx null (within range, line 1398) [V] |
| 1386 | 0x666c77c | `mov rdx,[rbp+0x5F0]` | stack read into rdx [V] |
| 1387 | 0x666c783 | `sub rdx,rcx` | size [V] |
| 1388 | 0x666c786 | `cmp rdx,0x1000` | compare to 0x1000 [V] |
| 1389 | 0x666c78d | `jb short 0x666C7AB` | branch if <= 0x1000 (within range, line 1397) [V] |
| 1390 | 0x666c78f | `mov rax,[rcx-8]` | read preceding allocation size [rcx-8] [V] |
| 1391 | 0x666c793 | `add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 [V] |
| 1392 | 0x666c797 | `sub rcx,rax` | [V] |
| 1393 | 0x666c79a | `cmp rcx,0x20` | compare to 0x20 [V] |
| 1394 | 0x666c79e | `jae 0x6670A7A` | EXIT of tag-7 body if invalid (out of range) [V] |
| 1395 | 0x666c7a4 | `or rdx,0x27` | [V] |
| 1396 | 0x666c7a8 | `mov rcx,rax` | [V] |
| 1397 | 0x666c7ab | `call 0xE935700` | call 0xE935700 [V] |
| 1398 | 0x666c7b0 | `mov rsi,[rbp+0x318]` | stack read object ptr into rsi [V] |
| 1399 | 0x666c7b7 | `test rsi,rsi` | test null [V] |
| 1400 | 0x666c7ba | `je short 0x666C7F0` | branch if null (within range, line 1414) [V] |
| 1401 | 0x666c7bc | `lock dec dword ptr [rsi+8]` | refcount dec [rsi+8] read/write [V] |
| 1402 | 0x666c7c0 | `jne short 0x666C7F0` | branch if not zero (within range, line 1414) [V] |
| 1403 | 0x666c7c2 | `mov rax,[rsi]` | rsi read [V] |
| 1404 | 0x666c7c5 | `mov rax,[rax]` | rax read [V] |
| 1405 | 0x666c7c8 | `mov rcx,rsi` | [V] |
| 1406 | 0x666c7cb | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 1) [V] |
| 1407 | 0x666c7d1 | `lock dec dword ptr [rsi+0xC]` | refcount dec [rsi+0xC] read/write [V] |
| 1408 | 0x666c7d5 | `jne short 0x666C7F0` | branch if not zero (within range, line 1414) [V] |
| 1409 | 0x666c7d7 | `mov rax,[rsi]` | rsi read [V] |
| 1410 | 0x666c7da | `mov rax,[rax+8]` | rax+0x8 read [V] |
| 1411 | 0x666c7de | `mov rcx,rsi` | [V] |
| 1412 | 0x666c7e1 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 2) [V] |
| 1413 | 0x666c7e7 | `nop [rax+rax]` | padding nop [V] |
| 1414 | 0x666c7f0 | `mov rsi,[rbp+0x308]` | stack read object ptr into rsi [V] |
| 1415 | 0x666c7f7 | `test rsi,rsi` | test null [V] |
| 1416 | 0x666c7fa | `je 0x666B700` | EXIT of tag-7 body: jump to function start 0x666B700 (before line 825) if null [V] |
| 1417 | 0x666c800 | `lock dec dword ptr [rsi+8]` | refcount dec [rsi+8] read/write [V] |
| 1418 | 0x666c804 | `jne 0x666B700` | EXIT of tag-7 body: jump to function start if not zero [V] |
| 1419 | 0x666c80a | `mov rax,[rsi]` | rsi read [V] |
| 1420 | 0x666c80d | `mov rax,[rax]` | rax read [V] |
| 1421 | 0x666c810 | `mov rcx,rsi` | [V] |
| 1422 | 0x666c813 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 1) [V] |
| 1423 | 0x666c819 | `lock dec dword ptr [rsi+0xC]` | refcount dec [rsi+0xC] read/write [V] |
| 1424 | 0x666c81d | `jne 0x666B700` | EXIT of tag-7 body: jump to function start if not zero [V] |

Branches: 0x666C7B0 (1385), 0x666C7AB (1389), 0x6670A7A EXIT (1394), 0x666C7F0 (1400, 1402, 1408), 0x666B700 EXIT (1416, 1418, 1424 — function restart, before line 825). Calls: 0xE935700 (1397), qword ptr [0xF99FFA0] (1406, 1412, 1422). No description field reads; r15 still = description base.

### lines 1425..1464 (0x666c823..0x666c8d1)

Finishes destroy of [rbp+0x308] (destroy part 2 via [rax+8]) then EXIT jmp 0x666B700 (function restart — leaves tag-7 body). At 0x666C838 (alloc-failure target from line 1140): call 0x9BC830, jmp 0x666C32F. Then a new path: rsi=[rbp+0x3E8]; if non-null EXIT to 0x666FB88 or 0x6670032 (out of range). Else rax=[rsi]->[rax+0x18], rbx=[rax] (heap object); if rbx null EXIT 0x666FB78. r14=[r12]; rax=[rbp+0x630]; zero [rbp+0x3F0]; rcx=[rax+8]; if rcx null EXIT 0x666CF20, else refcount inc [rcx+8]. rsi=[rbp+0x3F8]; copy [rax] (16 bytes) to [rbp+0x3F0]; if rsi null EXIT 0x666CF35; else refcount dec [rsi+8], destroy if zero, refcount dec [rsi+0xC]. r15 still = description base (untouched).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1425 | 0x666c823 | `mov rax,[rsi]` | rsi read [V] |
| 1426 | 0x666c826 | `mov rax,[rax+8]` | rax+0x8 read [V] |
| 1427 | 0x666c82a | `mov rcx,rsi` | [V] |
| 1428 | 0x666c82d | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 2) [V] |
| 1429 | 0x666c833 | `jmp 0x666B700` | EXIT of tag-7 body: jump to function start 0x666B700 (before line 825) [V] |
| 1430 | 0x666c838 | `mov rcx,rdi` | [V] |
| 1431 | 0x666c83b | `call 0x9BC830` | call 0x9BC830 [V] |
| 1432 | 0x666c840 | `nop` | padding nop [V] |
| 1433 | 0x666c841 | `jmp 0x666C32F` | jump back within range (line 1141) [V] |
| 1434 | 0x666c846 | `mov rsi,[rbp+0x3E8]` | stack read into rsi [V] |
| 1435 | 0x666c84d | `test rsi,rsi` | test null [V] |
| 1436 | 0x666c850 | `jne 0x666FB88` | EXIT of tag-7 body (out of range) if non-null [V] |
| 1437 | 0x666c856 | `jmp 0x6670032` | EXIT of tag-7 body (out of range) [V] |
| 1438 | 0x666c85b | `mov rax,[rsi]` | rsi read [V] |
| 1439 | 0x666c85e | `mov rax,[rax+0x18]` | rax+0x18 read into rax [V] |
| 1440 | 0x666c862 | `mov rbx,[rax]` | rax read into rbx (heap object) [V] |
| 1441 | 0x666c865 | `test rbx,rbx` | test null [V] |
| 1442 | 0x666c868 | `je 0x666FB78` | EXIT of tag-7 body (out of range) if null [V] |
| 1443 | 0x666c86e | `mov r14,[r12]` | r12 read into r14 [V] |
| 1444 | 0x666c872 | `mov rax,[rbp+0x630]` | stack read into rax [V] |
| 1445 | 0x666c879 | `xorps xmm0,xmm0` | xmm0=0 [V] |
| 1446 | 0x666c87c | `movaps [rbp+0x3F0],xmm0` | stack write zero xmm [V] |
| 1447 | 0x666c883 | `mov rcx,[rax+8]` | rax+0x8 read into rcx [V] |
| 1448 | 0x666c887 | `test rcx,rcx` | test null [V] |
| 1449 | 0x666c88a | `je 0x666CF20` | EXIT of tag-7 body (out of range) if null [V] |
| 1450 | 0x666c890 | `lock inc dword ptr [rcx+8]` | refcount inc [rcx+8] read/write [V] |
| 1451 | 0x666c894 | `mov rsi,[rbp+0x3F8]` | stack read into rsi [V] |
| 1452 | 0x666c89b | `movups xmm0,[rax]` | rax read 16 bytes into xmm0 [V] |
| 1453 | 0x666c89e | `movaps [rbp+0x3F0],xmm0` | stack write 16 bytes [V] |
| 1454 | 0x666c8a5 | `test rsi,rsi` | test null [V] |
| 1455 | 0x666c8a8 | `je 0x666CF35` | EXIT of tag-7 body (out of range) if null [V] |
| 1456 | 0x666c8ae | `lock dec dword ptr [rsi+8]` | refcount dec [rsi+8] read/write [V] |
| 1457 | 0x666c8b2 | `jne 0x666CF35` | EXIT of tag-7 body (out of range) if not zero [V] |
| 1458 | 0x666c8b8 | `mov rax,[rsi]` | rsi read [V] |
| 1459 | 0x666c8bb | `mov rax,[rax]` | rax read [V] |
| 1460 | 0x666c8be | `mov rcx,rsi` | [V] |
| 1461 | 0x666c8c1 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 1) [V] |
| 1462 | 0x666c8c7 | `lock dec dword ptr [rsi+0xC]` | refcount dec [rsi+0xC] read/write [V] |
| 1463 | 0x666c8cb | `jne 0x666CF35` | EXIT of tag-7 body (out of range) if not zero [V] |
| 1464 | 0x666c8d1 | `mov rax,[rsi]` | rsi read (destroy part 2) [V] |

Branches: 0x666B700 EXIT (1429 — function restart), 0x666C32F (1433), 0x666FB88 EXIT (1436), 0x6670032 EXIT (1437), 0x666FB78 EXIT (1442), 0x666CF20 EXIT (1449), 0x666CF35 EXIT (1455, 1457, 1463). Calls: qword ptr [0xF99FFA0] (1428, 1461), 0x9BC830 (1431). No description field reads; r15 still = description base.

### lines 1465..1504 (0x666c8e6..0x666c9bd)

Destroy part 2 via pointer chase [rax]->[rax+0x18]->rdi; if rdi null EXIT 0x666EEBE. Three stack-canary/guard checks read [0x129FA150], [0x129FA160], [0x129FA170] and compare each against gs:[0x58] TLS slot [rcx+4], EXITing to 0x6670E44/0x6670EB6/0x6670F28 on failure (all out of range). Then stores description base r15 to [rbp+0x668], reads DESCRIPTION FIELD [r15+0x84] (4 bytes) into edi, then CLOBBERS r15=[r12] (r15 no longer description base). rax=[rbp+0x5C0]; zero [rbp+0x3F0]; rcx=[rax+8]; if null EXIT 0x666D254 else refcount inc [rcx+8]; [rbp+0x648]=rbx; rsi=[rbp+0x3F8]; copy [rax] (16 bytes) to [rbp+0x3F0]; if rsi null EXIT 0x666D269 else refcount dec [rsi+8].

DESCRIPTION FIELD READ in this phase: line 1489 `mov edi,[r15+0x84]` — offset 0x84, size 4, dest edi, base r15=description base [V].

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1465 | 0x666c8e6 | `mov rax,[rax]` | rax read [V] |
| 1466 | 0x666c8e9 | `mov rax,[rax+0x18]` | rax+0x18 read into rax [V] |
| 1467 | 0x666c8ed | `mov rdi,[rax]` | rax read into rdi [V] |
| 1468 | 0x666c8f0 | `test rdi,rdi` | test null [V] |
| 1469 | 0x666c8f3 | `je 0x666EEBE` | EXIT of tag-7 body (out of range) if null [V] |
| 1470 | 0x666c8f9 | `mov eax,[0x129FA150]` | absolute read of global [V] |
| 1471 | 0x666c8ff | `mov ecx,[0x128767C8]` | absolute read of global TLS index [V] |
| 1472 | 0x666c905 | `mov rdx,gs:[0x58]` | TLS slot read [V] |
| 1473 | 0x666c90e | `mov rcx,[rdx+rcx*8]` | TLS entry read [V] |
| 1474 | 0x666c912 | `cmp eax,[rcx+4]` | canary compare [rcx+4] read [V] |
| 1475 | 0x666c918 | `jg 0x6670E44` | EXIT of tag-7 body (out of range) on fail [V] |
| 1476 | 0x666c91e | `mov eax,[0x129FA160]` | absolute read of global [V] |
| 1477 | 0x666c924 | `mov ecx,[0x128767C8]` | absolute read of global TLS index [V] |
| 1478 | 0x666c92a | `mov rdx,gs:[0x58]` | TLS slot read [V] |
| 1479 | 0x666c933 | `mov rcx,[rdx+rcx*8]` | TLS entry read [V] |
| 1480 | 0x666c937 | `cmp eax,[rcx+4]` | canary compare [rcx+4] read [V] |
| 1481 | 0x666c93d | `jg 0x6670EB6` | EXIT of tag-7 body (out of range) on fail [V] |
| 1482 | 0x666c943 | `mov eax,[0x129FA170]` | absolute read of global [V] |
| 1483 | 0x666c949 | `mov ecx,[0x128767C8]` | absolute read of global TLS index [V] |
| 1484 | 0x666c94f | `mov rdx,gs:[0x58]` | TLS slot read [V] |
| 1485 | 0x666c958 | `mov rcx,[rdx+rcx*8]` | TLS entry read [V] |
| 1486 | 0x666c95c | `cmp eax,[rcx+4]` | canary compare [rcx+4] read [V] |
| 1487 | 0x666c962 | `jg 0x6670F28` | EXIT of tag-7 body (out of range) on fail [V] |
| 1488 | 0x666c968 | `mov [rbp+0x668],r15` | save description base to slot [V] |
| 1489 | 0x666c96f | `mov edi,[r15+0x84]` | DESCRIPTION FIELD READ: desc+0x84, size 4, dest edi [V] |
| 1490 | 0x666c976 | `mov r15,[r12]` | r15 clobbered = [r12]; r15 NO LONGER description base [V] |
| 1491 | 0x666c97a | `mov rax,[rbp+0x5C0]` | stack read into rax [V] |
| 1492 | 0x666c981 | `xorps xmm0,xmm0` | xmm0=0 [V] |
| 1493 | 0x666c984 | `movaps [rbp+0x3F0],xmm0` | stack write zero xmm [V] |
| 1494 | 0x666c98b | `mov rcx,[rax+8]` | rax+0x8 read into rcx [V] |
| 1495 | 0x666c98f | `test rcx,rcx` | test null [V] |
| 1496 | 0x666c992 | `mov [rbp+0x648],rbx` | stack write [V] |
| 1497 | 0x666c999 | `je 0x666D254` | EXIT of tag-7 body (out of range) if null [V] |
| 1498 | 0x666c99f | `lock inc dword ptr [rcx+8]` | refcount inc [rcx+8] read/write [V] |
| 1499 | 0x666c9a3 | `mov rsi,[rbp+0x3F8]` | stack read into rsi [V] |
| 1500 | 0x666c9aa | `movups xmm0,[rax]` | rax read 16 bytes into xmm0 [V] |
| 1501 | 0x666c9ad | `movaps [rbp+0x3F0],xmm0` | stack write 16 bytes [V] |
| 1502 | 0x666c9b4 | `test rsi,rsi` | test null [V] |
| 1503 | 0x666c9b7 | `je 0x666D269` | EXIT of tag-7 body (out of range) if null [V] |
| 1504 | 0x666c9bd | `lock dec dword ptr [rsi+8]` | refcount dec [rsi+8] read/write [V] |

Branches: 0x666EEBE EXIT (1469), 0x6670E44 EXIT (1475), 0x6670EB6 EXIT (1481), 0x6670F28 EXIT (1487), 0x666D254 EXIT (1497), 0x666D269 EXIT (1503). No calls. r15 = description base until line 1489, clobbered at 1490.

### lines 1505..1544 (0x666c9c1..0x666ca5d)

Continues destroy of rsi (destroy part 2 via [rax+8]) then EXIT jmp 0x666D269. Else allocates via qword ptr [0xF99FFA0] (rcx=[0x1233E1A8]->[rax+8], rdx=r15 — r15 is now [r12], a size/count, NOT description base) into r14; if null call 0x9BC830 and r14=0. Writes r13b at [r14+rbx], zero xmm at [r14+rbx+4]. Then compares rdi vs [rsi+0x338]; if equal jump 0x666CA62, else rbx += r14 + 0x14, rdx=[rsi+0x330], r8=rdi-rdx, rcx=r14, call 0xEEC6DE0 (copy). Then r8=[rsi+0x338]-rdi, rcx=rbx, rdx=rdi. (rsi is the [rbp+0x3F8] stack copy of desc+0x30 from the earlier block; [rsi+0x330]/[rsi+0x338] are reads through that pointer [I].)

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1505 | 0x666c9c1 | `jne 0x666D269` | EXIT of tag-7 body (out of range) if not zero [V] |
| 1506 | 0x666c9c7 | `mov rax,[rsi]` | rsi read [V] |
| 1507 | 0x666c9ca | `mov rax,[rax]` | rax read [V] |
| 1508 | 0x666c9cd | `mov rcx,rsi` | [V] |
| 1509 | 0x666c9d0 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 1) [V] |
| 1510 | 0x666c9d6 | `lock dec dword ptr [rsi+0xC]` | refcount dec [rsi+0xC] read/write [V] |
| 1511 | 0x666c9da | `jne 0x666D269` | EXIT of tag-7 body (out of range) if not zero [V] |
| 1512 | 0x666c9e0 | `mov rax,[rsi]` | rsi read [V] |
| 1513 | 0x666c9e3 | `mov rax,[rax+8]` | rax+0x8 read [V] |
| 1514 | 0x666c9e7 | `mov rcx,rsi` | [V] |
| 1515 | 0x666c9ea | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (destroy part 2) [V] |
| 1516 | 0x666c9f0 | `jmp 0x666D269` | EXIT of tag-7 body (out of range) [V] |
| 1517 | 0x666c9f5 | `mov rcx,[0x1233E1A8]` | absolute read of global pointer [V] |
| 1518 | 0x666c9fc | `mov rax,[rcx]` | global->first field read [V] |
| 1519 | 0x666c9ff | `mov rax,[rax+8]` | read rax+0x8 (allocator fn ptr) [V] |
| 1520 | 0x666ca03 | `mov rdx,r15` | r15 read ([r12], size arg, NOT description base) [V] |
| 1521 | 0x666ca06 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (allocate) [V] |
| 1522 | 0x666ca0c | `nop` | padding nop [V] |
| 1523 | 0x666ca0d | `mov r14,rax` | alloc result into r14 [V] |
| 1524 | 0x666ca10 | `test rax,rax` | test null [V] |
| 1525 | 0x666ca13 | `jne short 0x666CA21` | branch if alloc succeeded (within range, line 1530) [V] |
| 1526 | 0x666ca15 | `mov rcx,r15` | [V] |
| 1527 | 0x666ca18 | `call 0x9BC830` | call 0x9BC830 (likely free/abort) [V] |
| 1528 | 0x666ca1d | `nop` | padding nop [V] |
| 1529 | 0x666ca1e | `xor r14d,r14d` | r14=0 [V] |
| 1530 | 0x666ca21 | `mov [r14+rbx],r13b` | write byte [V] |
| 1531 | 0x666ca25 | `movups [r14+rbx+4],xmm6` | write zero xmm [V] |
| 1532 | 0x666ca2b | `cmp rdi,[rsi+0x338]` | [rsi+0x338] read (rsi=desc+0x30 copy [I]) [V][I] |
| 1533 | 0x666ca32 | `je short 0x666CA62` | branch if equal (within range, line 1546) [V] |
| 1534 | 0x666ca34 | `add rbx,r14` | [V] |
| 1535 | 0x666ca37 | `add rbx,0x14` | [V] |
| 1536 | 0x666ca3b | `mov rdx,[rsi+0x330]` | [rsi+0x330] read (rsi=desc+0x30 copy [I]) [V][I] |
| 1537 | 0x666ca42 | `mov r8,rdi` | [V] |
| 1538 | 0x666ca45 | `sub r8,rdx` | [V] |
| 1539 | 0x666ca48 | `mov rcx,r14` | [V] |
| 1540 | 0x666ca4b | `call 0xEEC6DE0` | call 0xEEC6DE0 (memmove/copy) [V] |
| 1541 | 0x666ca50 | `mov r8,[rsi+0x338]` | [rsi+0x338] read [V][I] |
| 1542 | 0x666ca57 | `sub r8,rdi` | [V] |
| 1543 | 0x666ca5a | `mov rcx,rbx` | [V] |
| 1544 | 0x666ca5d | `mov rdx,rdi` | [V] |

Branches: 0x666D269 EXIT (1505, 1511, 1516), 0x666CA21 (1525), 0x666CA62 (1533). Calls: qword ptr [0xF99FFA0] (1509, 1515, 1521), 0x9BC830 (1527), 0xEEC6DE0 (1540). No description field reads directly (r15 clobbered; rsi is desc+0x30 stack copy [I]).

### lines 1545..1584 (0x666ca62..0x666cb20)

call 0xEEC6DE0 (rcx=r14, r8=rdi-[rsi+0x330]) to copy. Then buffer management on rsi (the [rbp+0x3F8] stack copy of desc+0x30 [I]): if [rsi+0x330] non-null, check free space [rsi+0x340]-[rsi+0x330]; if <0x1000 call 0xE935700, else validate preceding size ([rcx-8]) and EXIT 0x6670A7A if invalid (out of range). Set [rsi+0x330]=r14; [rsi+0x338]=r14+([rbp+0x648]*5)*4; [rsi+0x340]=r14+(r12*5)*4 where r12=[rbp+0x650]. Then movzx r8d,byte [rbp+0x670], global call qword ptr [0xF99FFA0] (dl=r8d), store double 2.0 (0x400000000000000) at [rbp+0x3F0], eax=([rsi+0x338]-[rsi+0x330])>>2. r15 = [r12] (size/count), NOT description base.

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1545 | 0x666ca62 | `mov rdx,[rsi+0x330]` | [rsi+0x330] read (rsi=desc+0x30 copy [I]) [V][I] |
| 1546 | 0x666ca69 | `sub rdi,rdx` | [V] |
| 1547 | 0x666ca6c | `mov rcx,r14` | [V] |
| 1548 | 0x666ca6f | `mov r8,rdi` | [V] |
| 1549 | 0x666ca72 | `call 0xEEC6DE0` | call 0xEEC6DE0 (memmove/copy) [V] |
| 1550 | 0x666ca77 | `mov rcx,[rsi+0x330]` | [rsi+0x330] read [V][I] |
| 1551 | 0x666ca7e | `test rcx,rcx` | test null [V] |
| 1552 | 0x666ca81 | `je short 0x666CAB7` | branch if null (within range, line 1565) [V] |
| 1553 | 0x666ca83 | `mov rdx,[rsi+0x340]` | [rsi+0x340] read [V][I] |
| 1554 | 0x666ca8a | `sub rdx,rcx` | free space [V] |
| 1555 | 0x666ca8d | `cmp rdx,0x1000` | compare to 0x1000 [V] |
| 1556 | 0x666ca94 | `jb short 0x666CAB2` | branch if not enough free (within range, line 1562) [V] |
| 1557 | 0x666ca96 | `mov rax,[rcx-8]` | read preceding allocation size [rcx-8] [V] |
| 1558 | 0x666ca9a | `add rcx,0xFFFFFFFFFFFFFFF8` | rcx -= 8 [V] |
| 1559 | 0x666ca9e | `sub rcx,rax` | [V] |
| 1560 | 0x666caa1 | `cmp rcx,0x20` | compare to 0x20 [V] |
| 1561 | 0x666caa5 | `jae 0x6670A7A` | EXIT of tag-7 body if invalid (out of range) [V] |
| 1562 | 0x666caab | `add rdx,0x27` | [V] |
| 1563 | 0x666caaf | `mov rcx,rax` | [V] |
| 1564 | 0x666cab2 | `call 0xE935700` | call 0xE935700 [V] |
| 1565 | 0x666cab7 | `mov [rsi+0x330],r14` | [rsi+0x330] write [V][I] |
| 1566 | 0x666cabe | `mov rax,[rbp+0x648]` | stack read into rax [V] |
| 1567 | 0x666cac5 | `lea rax,[rax+rax*4]` | rax = [rbp+0x648]*5 [V] |
| 1568 | 0x666cac9 | `lea rax,[r14+rax*4]` | [rsi+0x338] = r14 + rax*4 [V] |
| 1569 | 0x666cacd | `mov [rsi+0x338],rax` | [rsi+0x338] write [V][I] |
| 1570 | 0x666cad4 | `lea rax,[r12+r12*4]` | rax = r12*5 [V] |
| 1571 | 0x666cad8 | `lea rax,[r14+rax*4]` | [rsi+0x340] = r14 + rax*4 [V] |
| 1572 | 0x666cadc | `mov [rsi+0x340],rax` | [rsi+0x340] write [V][I] |
| 1573 | 0x666cae3 | `movzx r8d,byte ptr [rbp+0x670]` | stack read byte into r8d [V] |
| 1574 | 0x666caeb | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1575 | 0x666caf2 | `mov rax,[rcx]` | global->first field read [V] |
| 1576 | 0x666caf5 | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1577 | 0x666caf9 | `mov edx,r8d` | [V] |
| 1578 | 0x666cafc | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1579 | 0x666cb02 | `nop` | padding nop [V] |
| 1580 | 0x666cb03 | `mov rax,0x400000000000000` | constant double 2.0 bit pattern [V] |
| 1581 | 0x666cb0d | `mov [rbp+0x3F0],rax` | stack write qword [V] |
| 1582 | 0x666cb14 | `mov eax,[rsi+0x338]` | [rsi+0x338] read [V][I] |
| 1583 | 0x666cb1a | `sub eax,[rsi+0x330]` | [rsi+0x330] read [V][I] |
| 1584 | 0x666cb20 | `shr eax,2` | [V] |

Branches: 0x666CAB7 (1552), 0x666CAB2 (1556), 0x6670A7A EXIT (1561). Calls: 0xEEC6DE0 (1549), 0xE935700 (1564), qword ptr [0xF99FFA0] (1578). No direct description field reads (reads via rsi=desc+0x30 copy [I]); r15 NOT description base (it is [r12], a size).

### lines 1585..1624 (0x666cb23..0x666cbcb)

imul eax,0xFFFFCCCD; dec eax; [rbp+0x474]=ax (count). Global call qword ptr [0xF99FFA0] (dl=0x4A) storing al at [rbp+0x670]. rax=[rsi+8] (rsi=desc+0x30 copy [I]); if [rsi+8] != [rsi+0x10], call 0xEEC6EC0 (rcx=[rsi+8], rdx=[rbp+0x3F0], r8d=0xC8) and advance [rsi+8] by 0xC8; else call 0x5ABA6D0 (rcx=rsi, rdx=[rbp+0x3F0]) to grow. Then global call qword ptr [0xF99FFA0] (dl=[rbp+0x670]) and EXIT jmp 0x6670032 (out of range). Else (fall-through target 0x666CBAB): allocate via qword ptr [0xF99FFA0] (rcx=[0x1233E1A8]->[rax+8], rdx=r12) into r14; if null branch 0x666CBD7 else rcx=r12. r15 = [r12] (size), NOT description base.

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1585 | 0x666cb23 | `imul eax,0xFFFFCCCD` | magic multiply [V] |
| 1586 | 0x666cb29 | `dec eax` | [V] |
| 1587 | 0x666cb2b | `mov [rbp+0x474],ax` | stack write count [V] |
| 1588 | 0x666cb32 | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1589 | 0x666cb39 | `mov rax,[rcx]` | global->first field read [V] |
| 1590 | 0x666cb3c | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1591 | 0x666cb40 | `mov dl,0x4A` | [V] |
| 1592 | 0x666cb42 | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1593 | 0x666cb48 | `mov [rbp+0x670],al` | stack write flag byte [V] |
| 1594 | 0x666cb4e | `mov rax,[rsi+8]` | [rsi+8] read (rsi=desc+0x30 copy [I]) [V][I] |
| 1595 | 0x666cb52 | `cmp rax,[rsi+0x10]` | [rsi+0x10] read [V][I] |
| 1596 | 0x666cb56 | `je short 0x666CB77` | branch if equal/grow path (within range, line 1603) [V] |
| 1597 | 0x666cb58 | `lea rdx,[rbp+0x3F0]` | stack address [V] |
| 1598 | 0x666cb5f | `mov r8d,0xC8` | size arg 0xC8 [V] |
| 1599 | 0x666cb65 | `mov rcx,rax` | [rsi+8] value [V] |
| 1600 | 0x666cb68 | `call 0xEEC6EC0` | call 0xEEC6EC0 [V] |
| 1601 | 0x666cb6d | `add qword ptr [rsi+8],0xC8` | [rsi+8] read/write, advance by 0xC8 [V][I] |
| 1602 | 0x666cb75 | `jmp short 0x666CB8A` | branch past grow path (within range, line 1608) [V] |
| 1603 | 0x666cb77 | `lea r8,[rbp+0x3F0]` | stack address [V] |
| 1604 | 0x666cb7e | `mov rcx,rsi` | rsi read [V][I] |
| 1605 | 0x666cb81 | `mov rdx,rax` | [V] |
| 1606 | 0x666cb84 | `call 0x5ABA6D0` | call 0x5ABA6D0 (grow) [V] |
| 1607 | 0x666cb89 | `nop` | padding nop [V] |
| 1608 | 0x666cb8a | `mov rcx,[0x1233E1B0]` | absolute read of global pointer [V] |
| 1609 | 0x666cb91 | `mov rax,[rcx]` | global->first field read [V] |
| 1610 | 0x666cb94 | `mov rax,[rax+0x10]` | read rax+0x10 [V] |
| 1611 | 0x666cb98 | `movzx edx,byte ptr [rbp+0x670]` | stack read byte into edx [V] |
| 1612 | 0x666cb9f | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 [V] |
| 1613 | 0x666cba5 | `nop` | padding nop [V] |
| 1614 | 0x666cba6 | `jmp 0x6670032` | EXIT of tag-7 body (out of range) [V] |
| 1615 | 0x666cbab | `mov rcx,[0x1233E1A8]` | absolute read of global pointer [V] |
| 1616 | 0x666cbb2 | `mov rax,[rcx]` | global->first field read [V] |
| 1617 | 0x666cbb5 | `mov rax,[rax+8]` | read rax+0x8 (allocator fn ptr) [V] |
| 1618 | 0x666cbb9 | `mov rdx,r12` | r12 read (size arg) [V] |
| 1619 | 0x666cbbc | `call qword ptr [0xF99FFA0]` | indirect call via IAT slot 0xF99FFA0 (allocate) [V] |
| 1620 | 0x666cbc2 | `nop` | padding nop [V] |
| 1621 | 0x666cbc3 | `mov r14,rax` | alloc result into r14 [V] |
| 1622 | 0x666cbc6 | `test rax,rax` | test null [V] |
| 1623 | 0x666cbc9 | `jne short 0x666CBD7` | branch if alloc succeeded (within range, line 1629) [V] |
| 1624 | 0x666cbcb | `mov rcx,r12` | r12 read [V] |

Branches: 0x666CB77 (1596), 0x666CB8A (1602), 0x6670032 EXIT (1614), 0x666CBD7 (1623). Calls: qword ptr [0xF99FFA0] (1592, 1612, 1619), 0xEEC6EC0 (1600), 0x5ABA6D0 (1606). Reads via rsi=desc+0x30 copy [I] at [rsi+8]/[rsi+0x10]; no direct description field reads; r15 NOT description base (it is [r12], a size).

### lines 1625..1664 (0x666cbcc..0x666cc5e)

If alloc failed (r14=0): call 0x9BC830. rax=r14+r13; zero [r14+r13] (16 bytes). If [rbx+8] non-null refcount inc [rcx+8]; copy a 0x58-byte record from rbx ([rbx],[rbx+8],[rbx+0x50],[rbx+0x10..0x40]) into rax (r14+r13) with refcount bump on [rbx+8]. Then rdi=[rsi+0x78] (rsi=desc+0x30 copy [I]), rax=[rsi+0x80]; if r15==rax jump 0x666CD29; if rdi==r15 jump 0x666CCAC; else xmm0=0, rax=r14, jmp 0x666CC93 (copy loop over 0x58-byte records until rdi==r15). r15 = [r12] (set at line 1490), NOT description base.

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1625 | 0x666cbcb | `mov rcx,r12` | r12 read [V] |
| 1626 | 0x666cbce | `call 0x9BC830` | call 0x9BC830 (likely free/abort) [V] |
| 1627 | 0x666cbd3 | `nop` | padding nop [V] |
| 1628 | 0x666cbd4 | `xor r14d,r14d` | r14=0 [V] |
| 1629 | 0x666cbd7 | `lea rax,[r14+r13]` | dest = r14+r13 [V] |
| 1630 | 0x666cbdb | `xorps xmm0,xmm0` | xmm0=0 [V] |
| 1631 | 0x666cbde | `movups [r14+r13],xmm0` | zero dest 16 bytes [V] |
| 1632 | 0x666cbe3 | `mov rcx,[rbx+8]` | [rbx+8] read [V] |
| 1633 | 0x666cbe7 | `test rcx,rcx` | test null [V] |
| 1634 | 0x666cbea | `je short 0x666CBF0` | branch if null (within range, line 1636) [V] |
| 1635 | 0x666cbec | `lock inc dword ptr [rcx+8]` | refcount inc [rcx+8] read/write [V] |
| 1636 | 0x666cbf0 | `mov rcx,[rbx]` | [rbx] read into rcx [V] |
| 1637 | 0x666cbf3 | `mov [rax],rcx` | write dest [V] |
| 1638 | 0x666cbf6 | `mov rcx,[rbx+8]` | [rbx+8] read into rcx [V] |
| 1639 | 0x666cbfa | `mov [rax+8],rcx` | write dest+8 [V] |
| 1640 | 0x666cbfe | `mov rcx,[rbx+0x50]` | [rbx+0x50] read into rcx [V] |
| 1641 | 0x666cc02 | `mov [rax+0x50],rcx` | write dest+0x50 [V] |
| 1642 | 0x666cc06 | `movups xmm0,[rbx+0x10]` | [rbx+0x10] read 16 bytes [V] |
| 1643 | 0x666cc0a | `movups xmm1,[rbx+0x20]` | [rbx+0x20] read 16 bytes [V] |
| 1644 | 0x666cc0e | `movups xmm2,[rbx+0x30]` | [rbx+0x30] read 16 bytes [V] |
| 1645 | 0x666cc12 | `movups xmm3,[rbx+0x40]` | [rbx+0x40] read 16 bytes [V] |
| 1646 | 0x666cc16 | `movups [rax+0x40],xmm3` | write dest+0x40 [V] |
| 1647 | 0x666cc1a | `movups [rax+0x30],xmm2` | write dest+0x30 [V] |
| 1648 | 0x666cc1e | `movups [rax+0x20],xmm1` | write dest+0x20 [V] |
| 1649 | 0x666cc22 | `movups [rax+0x10],xmm0` | write dest+0x10 [V] |
| 1650 | 0x666cc26 | `mov rdi,[rsi+0x78]` | [rsi+0x78] read into rdi (rsi=desc+0x30 copy [I]) [V][I] |
| 1651 | 0x666cc2a | `mov rax,[rsi+0x80]` | [rsi+0x80] read into rax [V][I] |
| 1652 | 0x666cc31 | `cmp r15,rax` | compare r15 ([r12], size) to rax [V] |
| 1653 | 0x666cc34 | `je 0x666CD29` | branch if equal (within range) [V] |
| 1654 | 0x666cc3a | `cmp rdi,r15` | compare rdi to r15 [V] |
| 1655 | 0x666cc3d | `je short 0x666CCAC` | branch if equal (within range) [V] |
| 1656 | 0x666cc3f | `xorps xmm0,xmm0` | xmm0=0 [V] |
| 1657 | 0x666cc42 | `mov rax,r14` | rax=r14 [V] |
| 1658 | 0x666cc45 | `jmp short 0x666CC93` | branch to copy loop (within range) [V] |
| 1659 | 0x666cc47 | `nop [rax+rax]` | padding nop [V] |
| 1660 | 0x666cc50 | `mov rcx,[rdi]` | [rdi] read into rcx [V] |
| 1661 | 0x666cc53 | `mov [rax],rcx` | write dest [V] |
| 1662 | 0x666cc56 | `mov rcx,[rdi+8]` | [rdi+8] read into rcx [V] |
| 1663 | 0x666cc5a | `mov [rax+8],rcx` | write dest+8 [V] |
| 1664 | 0x666cc5e | `movups xmm1,[rdi+0x10]` | [rdi+0x10] read 16 bytes [V] |

Branches: 0x666CBF0 (1634), 0x666CD29 (1653), 0x666CCAC (1655), 0x666CC93 (1658). Call: 0x9BC830 (1626). Reads via rsi=desc+0x30 copy [I] at [rsi+0x78]/[rsi+0x80]; no direct description field reads; r15 NOT description base.

### lines 1665..1700 (0x666cc62..0x666cced) — FINAL (end of requested range)

Copy loop body: copies [rdi+0x20..0x40] (xmm2/xmm3/xmm4) to rax+0x10..0x40, [rdi+0x50] to rax+0x50, advances rax/rdi by 0x58, loops until rdi==r15 then jumps 0x666CCA5. At 0x666CC93 writes xmm0 (zero) to [rax], reads [rdi+8]; if null jump 0x666CC50 else `inc dword ptr [rcx+8]` (refcount inc) and loop (line 1682 `(bad)` is a disassembly artifact). At 0x666CCA5: rax=[rsi+0x80] (rsi=desc+0x30 copy [I]); if r15==rax jump 0x666CD95 (beyond this listing range); else rcx=r14+r13+0x58, xmm0=0, jmp 0x666CD17 (beyond range). Then a second copy loop reads [r15], [r15+8], [r15+0x10..0x40] into xmm1..xmm4 (r15=[r12], a size/count, NOT description base). No calls. No exit of the tag-7 body itself, but branches 0x666CD95/0x666CD17 leave the decoded listing range (body continues past line 1700).

| line | 0xRVA | instruction | note |
|------|-------|-------------|------|
| 1665 | 0x666cc62 | `movups xmm2,[rdi+0x20]` | [rdi+0x20] read 16 bytes [V] |
| 1666 | 0x666cc66 | `movups xmm3,[rdi+0x30]` | [rdi+0x30] read 16 bytes [V] |
| 1667 | 0x666cc6a | `movups xmm4,[rdi+0x40]` | [rdi+0x40] read 16 bytes [V] |
| 1668 | 0x666cc6e | `movups [rax+0x10],xmm1` | write dest+0x10 [V] |
| 1669 | 0x666cc72 | `movups [rax+0x20],xmm2` | write dest+0x20 [V] |
| 1670 | 0x666cc76 | `movups [rax+0x30],xmm3` | write dest+0x30 [V] |
| 1671 | 0x666cc7a | `movups [rax+0x40],xmm4` | write dest+0x40 [V] |
| 1672 | 0x666cc7e | `mov rcx,[rdi+0x50]` | [rdi+0x50] read into rcx [V] |
| 1673 | 0x666cc82 | `mov [rax+0x50],rcx` | write dest+0x50 [V] |
| 1674 | 0x666cc86 | `add rax,0x58` | advance dest by 0x58 [V] |
| 1675 | 0x666cc8a | `add rdi,0x58` | advance src by 0x58 [V] |
| 1676 | 0x666cc8e | `cmp rdi,r15` | compare src to end r15 [V] |
| 1677 | 0x666cc91 | `je short 0x666CCA5` | branch if done (within range) [V] |
| 1678 | 0x666cc93 | `movups [rax],xmm0` | write zero xmm to dest [V] |
| 1679 | 0x666cc96 | `mov rcx,[rdi+8]` | [rdi+8] read into rcx [V] |
| 1680 | 0x666cc9a | `test rcx,rcx` | test null [V] |
| 1681 | 0x666cc9d | `je short 0x666CC50` | branch if null (within range) [V] |
| 1682 | 0x666cc9f | `(bad)` | disassembly artifact (part of refcount inc sequence) [V] |
| 1683 | 0x666cca0 | `inc dword ptr [rcx+8]` | refcount inc [rcx+8] read/write [V] |
| 1684 | 0x666cca3 | `jmp short 0x666CC50` | branch to loop top (within range) [V] |
| 1685 | 0x666cca5 | `mov rax,[rsi+0x80]` | [rsi+0x80] read into rax [V][I] |
| 1686 | 0x666ccac | `cmp r15,rax` | compare r15 ([r12], size) to rax [V] |
| 1687 | 0x666ccaf | `je 0x666CD95` | branch to beyond-listing-range target [V] |
| 1688 | 0x666ccb5 | `lea rcx,[r14+r13]` | [V] |
| 1689 | 0x666ccb9 | `add rcx,0x58` | [V] |
| 1690 | 0x666ccbd | `xorps xmm0,xmm0` | xmm0=0 [V] |
| 1691 | 0x666ccc0 | `jmp short 0x666CD17` | branch to beyond-listing-range target [V] |
| 1692 | 0x666ccc2 | `nop [rax+rax]` | padding nop [V] |
| 1693 | 0x666ccd0 | `mov rdx,[r15]` | [r15] read (r15=[r12], NOT description base) [V] |
| 1694 | 0x666ccd3 | `mov [rcx],rdx` | write [V] |
| 1695 | 0x666ccd6 | `mov rdx,[r15+8]` | [r15+8] read [V] |
| 1696 | 0x666ccda | `mov [rcx+8],rdx` | write [V] |
| 1697 | 0x666ccde | `movups xmm1,[r15+0x10]` | [r15+0x10] read 16 bytes [V] |
| 1698 | 0x666cce3 | `movups xmm2,[r15+0x20]` | [r15+0x20] read 16 bytes [V] |
| 1699 | 0x666cce8 | `movups xmm3,[r15+0x30]` | [r15+0x30] read 16 bytes [V] |
| 1700 | 0x666cced | `movups xmm4,[r15+0x40]` | [r15+0x40] read 16 bytes [V] (END of requested range) |

Branches: 0x666CCA5 (1677), 0x666CC50 (1681, 1684), 0x666CD95 (1687, beyond range), 0x666CD17 (1691, beyond range). No calls. No direct description field reads (r15=[r12], not description base; reads via rsi=desc+0x30 copy [I]). Requested range COMPLETE at line 1700 / RVA 0x666cced.

## NEXT
COMPLETE: all listing lines 825..1700 (RVA 0x666bc55..0x666cced) written to docs/progress/oc_U-FX1b.md. No further blocks pending. (Tag-7 body continues past line 1700; exits observed include jumps to function start 0x666B700 and out-of-range targets 0x6670A94/0x6670C3B/0x6670A7A/0x666B700/0x666FB88/0x6670032/0x666FB78/0x666CF20/0x666CF35/0x666EEBE/0x6670E44/0x6670EB6/0x6670F28/0x666D254/0x666D269/0x6670032.)





















