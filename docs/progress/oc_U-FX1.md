# Unit U-FX1 — FullscreenEffect visitor body decode (tag 7)

## Source
- Listing: docs/data/listings/effect_visitor_666aca0_667191c.txt, lines 475..1700 (RVA 0x666b5cd .. 0x666cced)
- Context: docs/functions/effect_descriptions.md section on FullscreenEffect
- Convention: r15 = description (set at listing line 20 `mov r15,[r8]`, confirmed [V]); description pointer also loaded into other registers (r14 at line 522 `mov r14,[r15+0x18]` [V]). Register holding description pointer re-verified per use below.
- [V] = seen in listing; [I] = inferred.

## Block 2 — lines 536..596 (RVA 0x666b711 .. 0x666b891)

Field reads of description:
| Line | RVA | Instruction | Reg+offset | Size | Dest | Tag |
|------|-----|-------------|------------|------|------|-----|
| (none — reads [r12], [rbp+0x3E0], [rax], stack slots; no r15/description field read in this block) | — | — | — | — | — | — |

Branches / exits / calls:
| Line | RVA | Instruction | Target / kind | Tag |
|------|-----|-------------|---------------|-----|
| 536 | 0x666b711 | `mov rdi,[r12]` | r12 read | — |
| 537 | 0x666b715 | `mov rax,[rbp+0x3E0]` | stack read | — |
| 538 | 0x666b71c | `movaps [rbp+0x3F0],xmm6` | — | — |
| 539 | 0x666b723 | `mov rcx,[rax+8]` | rax+0x8 read | — |
| 540 | 0x666b72a | `test rcx,rcx` | — | — |
| 541 | 0x666b72c | `je short 0x666B780` | branch | — |
| 542 | 0x666b72c | `lock inc dword ptr [rcx+8]` | rcx+0x8 read/write | — |
| 543 | 0x666b730 | `mov rsi,[rbp+0x3F8]` | stack read | — |
| 544 | 0x666b737 | `movups xmm0,[rax]` | rax read | — |
| 545 | 0x666b741 | `test rsi,rsi` | — | — |
| 546 | 0x666b744 | `je short 0x666B795` | branch | — |
| 547 | 0x666b746 | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 549 | 0x666b74c | `mov rax,[rsi]` | rsi read | — |
| 550 | 0x666b74f | `mov rax,[rax]` | rax read | — |
| 551 | 0x666b752 | `mov rcx,rsi` | — | — |
| 552 | 0x666b755 | `call qword ptr [0xF99FFA0]` | call | — |
| 553 | 0x666b75b | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 554 | 0x666b75f | `jne short 0x666B795` | branch | — |
| 555 | 0x666b761 | `mov rax,[rsi]` | rsi read | — |
| 556 | 0x666b764 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 557 | 0x666b768 | `mov rcx,rsi` | — | — |
| 558 | 0x666b76b | `call qword ptr [0xF99FFA0]` | call | — |
| 559 | 0x666b771 | `jmp short 0x666B795` | branch | — |
| 561 | 0x666b780 | `mov rax,[rax]` | rax read | — |
| 562 | 0x666b783 | `mov [rbp+0x3F0],rax` | — | — |
| 563 | 0x666b78a | `mov qword ptr [rbp+0x3F8],0` | — | — |
| 564 | 0x666b795 | `mov rax,[rbp+0x3F0]` | stack read | — |
| 565 | 0x666b79c | `mov rax,[rax+0x18]` | rax+0x18 read | — |
| 566 | 0x666b7a0 | `mov rax,[rax]` | rax read | — |
| 567 | 0x666b7a3 | `mov [rbp+0x340],rax` | — | — |
| 568 | 0x666b7aa | `mov r8,[rdi]` | rdi read | — |
| 569 | 0x666b7ad | `mov rdx,[rax+0x170]` | rax+0x170 read | — |
| 570 | 0x666b7b4 | `lea rcx,[rbp+0x348]` | — | — |
| 571 | 0x666b7bb | `call 0xE86B370` | call 0xE86B370 | — |
| 573 | 0x666b7c1 | `mov [rbp+0x3C0],rdi` | — | — |
| 574 | 0x666b7c8 | `mov rsi,[rbp+0x3F8]` | stack read | — |
| 575 | 0x666b7cf | `test rsi,rsi` | — | — |
| 576 | 0x666b7d2 | `je short 0x666B800` | branch | — |
| 577 | 0x666b7d4 | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 579 | 0x666b7da | `mov rax,[rsi]` | rsi read | — |
| 580 | 0x666b7dd | `mov rax,[rax]` | rax read | — |
| 581 | 0x666b7e0 | `mov rcx,rsi` | — | — |
| 582 | 0x666b7e3 | `call qword ptr [0xF99FFA0]` | call | — |
| 583 | 0x666b7e9 | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 585 | 0x666b7ef | `mov rax,[rsi]` | rsi read | — |
| 586 | 0x666b7f2 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 587 | 0x666b7f6 | `mov rcx,rsi` | — | — |
| 588 | 0x666b7f9 | `call qword ptr [0xF99FFA0]` | call | — |
| 590 | 0x666b800 | `mov rax,[rbp+0x388]` | stack read | — |
| 591 | 0x666b807 | `movzx r8d,word ptr [rbp+0x392]` | stack read | — |
| 592 | 0x666b80f | `mov ecx,r8d` | — | — |
| 593 | 0x666b812 | `shl ecx,4` | — | — |
| 594 | 0x666b815 | `lea rdx,[rcx+rcx*2]` | — | — |
| 595 | 0x666b819 | `mov rcx,rax` | — | — |
| 597 | 0x666b81f | `je short 0x666B850` | branch | — |
| 598 | 0x666b821 | `mov r8,[0x129FA0E8]` | absolute read | — |
| 599 | 0x666b828 | `mov r9,rdx` | — | — |
| 600 | 0x666b82b | `mov rcx,rax` | — | — |
| 601 | 0x666b82e | `xchg ax,ax` | — | — |
| 602 | 0x666b830 | `mov r10,[rcx]` | rcx read | — |
| 603 | 0x666b833 | `cmp [r10+0x28],r8` | r10+0x28 read | — |
| 604 | 0x666b837 | `je short 0x666B850` | branch | — |
| 605 | 0x666b839 | `add rcx,0x30` | — | — |
| 606 | 0x666b83d | `add r9,0xFFFFFFFFFFFFFFD0` | — | — |
| 607 | 0x666b841 | `jne short 0x666B830` | branch | — |
| 608 | 0x666b843 | `jmp short 0x666B891` | branch | — |
| 610 | 0x666b850 | `add rdx,rax` | — | — |
| 611 | 0x666b853 | `cmp rcx,rdx` | — | — |
| 612 | 0x666b856 | `jae short 0x666B891` | branch | — |
| 613 | 0x666b858 | `lea r8,[r14+8]` | r14+8 (addr gen; r14=desc+0x18) | — |
| 614 | 0x666b85c | `sub ecx,eax` | — | — |
| 615 | 0x666b85e | `shr ecx,4` | — | — |
| 616 | 0x666b861 | `imul eax,ecx,0xFFFFAAAB` | — | — |
| 617 | 0x666b867 | `mov [rbp],ax` | — | — |
| 618 | 0x666b86b | `mov byte ptr [rbp+2],1` | — | — |
| 619 | 0x666b86f | `mov byte ptr [rbp+0x3FC],0` | — | — |
| 620 | 0x666b876 | `mov dword ptr [rsp+0x20],0` | — | — |
| 621 | 0x666b87e | `lea rcx,[rbp+0x340]` | — | — |
| 622 | 0x666b885 | `mov rdx,rbp` | — | — |
| 623 | 0x666b888 | `mov r9,r13` | — | — |
| 624 | 0x666b88b | `call 0xBCABA00` | call 0xBCABA00 | — |
| 626 | 0x666b891 | `movss xmm0,[r14+0x20]` | r14+0x20 = desc+0x18+0x20 = desc+0x38 | 4 | xmm0 | [V] |
| 627 | 0x666b897 | `movsd xmm1,[r14+0x18]` | r14+0x18 = desc+0x18+0x18 = desc+0x30 | 8 | xmm1 | [V] |
| 628 | 0x666b89d | `movsd [rbp+0x3F0],xmm1` | — | — | — |
| 629 | 0x666b8a5 | `movss [rbp+0x3F8],xmm0` | — | — | — |
| 630 | 0x666b8ad | `mov dword ptr [rbp+0x3FC],0` | — | — | — |

Description register check: r15 still holds description. r14 = desc+0x18 (line 522), used at lines 613, 626, 627.

## Block 3 — lines 631..692 (RVA 0x666b8b7 .. 0x666b9b2)

Field reads of description:
| Line | RVA | Instruction | Reg+offset | Size | Dest | Tag |
|------|-----|-------------|------------|------|------|-----|
| 633 | 0x666b8c3 | `mov rax,[rbp+0x378]` | stack read | — | — | — |
| 634 | 0x666b8ca | `movzx r8d,word ptr [rbp+0x382]` | stack read | — | — | — |
| 640 | 0x666b8e0 | `mov r8,[0x129FA0F8]` | absolute read | — | — | — |
| 644 | 0x666b8f0 | `mov r10,[rcx]` | rcx read | — | — | — |
| 645 | 0x666b8f3 | `cmp [r10+0x28],r8` | r10+0x28 read | — | — | — |
| 657 | 0x666b91d | `mov [rbp+0x1D0],cx` | — | — | — |
| 664 | 0x666b942 | `mov rsi,[r14]` | r14 read (r14=desc+0x18) → desc+0x18 value | 8 | rsi | [V] |
| 665 | 0x666b945 | `mov rax,[rsi+0x60]` | rsi+0x60 read | 8 | rax | [V][I] (rsi = desc+0x18 field) |
| 666 | 0x666b949 | `sub rax,[rsi+0x58]` | rsi+0x58 read | 8 | rax | [V][I] |
| 691 | 0x666b9b2 | `mov rax,[r15+8]` | r15+8 = desc+0x8 | 8 | rax | [V] |

Branches / exits / calls:
| Line | RVA | Instruction | Target / kind | Tag |
|------|-----|-------------|---------------|-----|
| 631 | 0x666b8b7 | `mov qword ptr [rbp],1` | — | — |
| 632 | 0x666b8bf | `mov [rbp+8],r13` | — | — |
| 635 | 0x666b8d2 | `mov edx,r8d` | — | — |
| 636 | 0x666b8d5 | `shl edx,4` | — | — |
| 637 | 0x666b8d8 | `mov rcx,rax` | — | — |
| 638 | 0x666b8db | `test r8d,r8d` | — | — |
| 639 | 0x666b8de | `je short 0x666B910` | branch | — |
| 641 | 0x666b8e7 | `mov r9,rdx` | — | — |
| 642 | 0x666b8ea | `mov rcx,rax` | — | — |
| 643 | 0x666b8ed | `nop [rax]` | — | — |
| 646 | 0x666b8f7 | `je short 0x666B910` | branch | — |
| 647 | 0x666b8f9 | `add rcx,0x10` | — | — |
| 648 | 0x666b8fd | `add r9,0xFFFFFFFFFFFFFFF0` | — | — |
| 649 | 0x666b901 | `jne short 0x666B8F0` | branch | — |
| 650 | 0x666b903 | `jmp short 0x666B942` | branch | — |
| 652 | 0x666b910 | `add rdx,rax` | — | — |
| 653 | 0x666b913 | `cmp rcx,rdx` | — | — |
| 654 | 0x666b916 | `jae short 0x666B942` | branch | — |
| 655 | 0x666b918 | `sub ecx,eax` | — | — |
| 656 | 0x666b91a | `shr ecx,4` | — | — |
| 658 | 0x666b924 | `mov byte ptr [rbp+0x1D2],1` | — | — |
| 659 | 0x666b92b | `lea rcx,[rbp+0x348]` | — | — |
| 660 | 0x666b932 | `lea rdx,[rbp+0x1D0]` | — | — |
| 661 | 0x666b939 | `mov r8,rbp` | — | — |
| 662 | 0x666b93c | `call 0x5679DB0` | call 0x5679DB0 | — |
| 667 | 0x666b94d | `shr rax,2` | — | — |
| 668 | 0x666b951 | `imul eax,0xAAAAAAAB` | — | — |
| 669 | 0x666b957 | `test eax,eax` | — | — |
| 670 | 0x666b959 | `je short 0x666B985` | branch | — |
| 671 | 0x666b95b | `mov rdx,[rbp+0x340]` | stack read | — |
| 672 | 0x666b962 | `mov eax,0x250` | — | — |
| 673 | 0x666b967 | `add rdx,rax` | — | — |
| 674 | 0x666b96a | `mov rcx,r13` | — | — |
| 675 | 0x666b96d | `xor r8d,r8d` | — | — |
| 676 | 0x666b970 | `call 0xBBD7C70` | call 0xBBD7C70 | — |
| 678 | 0x666b976 | `mov rcx,rsi` | — | — |
| 679 | 0x666b979 | `mov rdx,r13` | — | — |
| 680 | 0x666b97c | `call 0x4DEDD00` | call 0x4DEDD00 | — |
| 682 | 0x666b982 | `mov rsi,[r14]` | r14 read (desc+0x18) | — | — |
| 684 | 0x666b987 | `cmp byte ptr [rsi+0x1D4],0` | rsi+0x1D4 = desc+0x18+0x1D4 = desc+0x1EC | 1 | — | [V][I] |
| 686 | 0x666b990 | `mov edi,[rsi+0x1D0]` | rsi+0x1D0 = desc+0x18+0x1D0 = desc+0x1E8 | 4 | edi | [V][I] |
| 687 | 0x666b996 | `movaps [rbp+0x330],xmm6` | — | — | — |
| 688 | 0x666b99d | `movaps [rbp+0x320],xmm6` | — | — | — |
| 689 | 0x666b9a4 | `movaps [rbp+0x310],xmm6` | — | — | — |
| 690 | 0x666b9ab | `movaps [rbp+0x300],xmm6` | — | — | — |
| 693 | 0x666b9b9 | `je short 0x666BA10` | branch | — |
| 694 | 0x666b9bb | `lock inc dword ptr [rax+8]` | rax+0x8 read/write | — |
| 695 | 0x666b9bf | `mov rsi,[rbp+0x308]` | stack read | — |
| 696 | 0x666b9c6 | `movups xmm0,[r15]` | r15+0x00 = desc+0x00 | 16 | xmm0 | [V] |
| 697 | 0x666b9ca | `movaps [rbp+0x300],xmm0` | — | — | — |
| 698 | 0x666b9d1 | `test rsi,rsi` | — | — |
| 699 | 0x666b9d4 | `je short 0x666BA25` | branch | — |
| 700 | 0x666b9d6 | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 702 | 0x666b9dc | `mov rax,[rsi]` | rsi read | — |
| 703 | 0x666b9df | `mov rax,[rax]` | rax read | — |
| 704 | 0x666b9e2 | `mov rcx,rsi` | — | — |
| 705 | 0x666b9e5 | `call qword ptr [0xF99FFA0]` | call | — |
| 706 | 0x666b9eb | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 708 | 0x666b9f1 | `mov rax,[rsi]` | rsi read | — |
| 709 | 0x666b9f4 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 710 | 0x666b9f8 | `mov rcx,rsi` | — | — |
| 711 | 0x666b9fb | `call qword ptr [0xF99FFA0]` | call | — |
| 712 | 0x666ba01 | `jmp short 0x666BA25` | branch | — |
| 714 | 0x666ba10 | `mov rax,[r15]` | r15+0x00 = desc+0x00 | 8 | rax | [V] |
| 715 | 0x666ba13 | `mov [rbp+0x300],rax` | — | — | — |
| 716 | 0x666ba1a | `mov qword ptr [rbp+0x308],0` | — | — | — |
| 717 | 0x666ba25 | `movups xmm0,[r14+0x24]` | r14+0x24 = desc+0x18+0x24 = desc+0x3C | 16 | xmm0 | [V][I] |
| 718 | 0x666ba2a | `shufps xmm0,xmm0,0x4E` | — | — | — |
| 719 | 0x666ba2e | `movaps [rbp+0x320],xmm0` | — | — | — |
| 720 | 0x666ba35 | `mov dword ptr [rbp+0x5E0],0x3F800000` | — | — | — |
| 721 | 0x666ba3f | `lea rax,[rbp+0x5E4]` | — | — | — |
| 722 | 0x666ba46 | `movups [rax],xmm6` | — | — | — |
| 723 | 0x666ba49 | `mov dword ptr [rbp+0x5F4],0x3F800000` | — | — | — |
| 724 | 0x666ba53 | `movups [rax+0x14],xmm6` | — | — | — |
| 725 | 0x666ba57 | `mov dword ptr [rbp+0x608],0x3F800000` | — | — | — |
| 726 | 0x666ba61 | `movups [rax+0x28],xmm6` | — | — | — |
| 727 | 0x666ba65 | `mov dword ptr [rbp+0x61C],0x3F800000` | — | — | — |
| 728 | 0x666ba6f | `mov byte ptr [rbp+0x620],0` | — | — | — |
| 729 | 0x666ba76 | `mov rax,[r14]` | r14 read (desc+0x18) | 8 | rax | [V] |
| 730 | 0x666ba79 | `movaps [rbp-0x20],xmm6` | — | — | — |
| 731 | 0x666ba7d | `mov rcx,[rax+0x1B0]` | rax+0x1B0 read | 8 | rcx | [V][I] (rax = desc+0x18 field) |
| 733 | 0x666ba87 | `je short 0x666BA8D` | branch | — |
| 734 | 0x666ba89 | `movzx ecx,word ptr [rcx+0x10]` | rcx+0x10 read | 2 | ecx | [V][I] |
| 735 | 0x666ba8d | `mov rcx,[rax+0x1B8]` | rax+0x1B8 read | 8 | rcx | [V][I] |
| 737 | 0x666ba97 | `je short 0x666BAB0` | branch | — |
| 738 | 0x666ba99 | `lock inc dword ptr [rcx+8]` | rcx+0x8 read/write | — |
| 739 | 0x666ba9d | `mov rcx,[rax+0x1B8]` | rax+0x1B8 read | 8 | rcx | [V][I] |
| 741 | 0x666baa6 | `nop [rax+rax]` | — | — | — |
| 742 | 0x666bab0 | `xor ecx,ecx` | — | — | — |
| 743 | 0x666bab2 | `mov rax,[rax+0x1B0]` | rax+0x1B0 read | 8 | rax | [V][I] |
| 744 | 0x666bab9 | `mov [rbp-0x20],rax` | — | — | — |
| 745 | 0x666babd | `mov rsi,[rbp-0x18]` | stack read | — |
| 746 | 0x666bac1 | `mov [rbp-0x18],rcx` | — | — | — |
| 747 | 0x666bac5 | `test rsi,rsi` | — | — | — |
| 748 | 0x666bac8 | `je short 0x666BB00` | branch | — |
| 749 | 0x666baca | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 751 | 0x666bad0 | `mov rax,[rsi]` | rsi read | — |
| 752 | 0x666bad3 | `mov rax,[rax]` | rax read | — |
| 753 | 0x666bad6 | `mov rcx,rsi` | — | — |
| 755 | 0x666badf | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 756 | 0x666bae3 | `jne short 0x666BB00` | branch | — |
| 757 | 0x666bae5 | `mov rax,[rsi]` | rsi read | — |
| 758 | 0x666bae8 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 759 | 0x666baec | `mov rcx,rsi` | — | — |
| 760 | 0x666baef | `call qword ptr [0xF99FFA0]` | call | — |
| 762 | 0x666bb00 | `mov r8,[rbx+0x3B8]` | rbx+0x3B8 read | — |
| 763 | 0x666bb07 | `mov rdx,[r12]` | r12 read | — |
| 764 | 0x666bb0b | `mov [rsp+0x20],edi` | — | — |
| 765 | 0x666bb0f | `mov dword ptr [rsp+0x30],0` | — | — |
| 766 | 0x666bb17 | `mov dword ptr [rsp+0x28],0` | — | — |
| 767 | 0x666bb1f | `lea rcx,[rbp+0x2A0]` | — | — |
| 768 | 0x666bb26 | `lea r9,[rbp-0x20]` | — | — |
| 769 | 0x666bb2a | `call 0x66A0F60` | call 0x66A0F60 | — |
| 771 | 0x666bb30 | `mov rax,[rbp+0x340]` | stack read | — |
| 772 | 0x666bb37 | `mov [rbp],rax` | — | — |
| 773 | 0x666bb3b | `lea rcx,[rbp+8]` | — | — |
| 774 | 0x666bb3f | `lea rdx,[rbp+0x348]` | — | — |
| 775 | 0x666bb46 | `call 0xE869FF0` | call 0xE869FF0 | — |
| 777 | 0x666bb4c | `mov rax,[rbp+0x3C0]` | stack read | — |
| 778 | 0x666bb53 | `mov [rbp+0x80],rax` | — | — |
| 779 | 0x666bb5a | `mov qword ptr [rbp+0x3C0],0` | — | — |
| 780 | 0x666bb65 | `lea rax,[rbp+0x88]` | — | — |
| 781 | 0x666bb6c | `movups [rax],xmm6` | — | — | — |
| 782 | 0x666bb6f | `mov rax,[rbp+0x308]` | stack read | — |
| 783 | 0x666bb76 | `test rax,rax` | — | — |
| 784 | 0x666bb79 | `je short 0x666BB90` | branch | — |
| 785 | 0x666bb7b | `lock inc dword ptr [rax+8]` | rax+0x8 read/write | — |
| 786 | 0x666bb7f | `mov rax,[rbp+0x308]` | stack read | — |
| 787 | 0x666bb86 | `jmp short 0x666BB92` | branch | — |
| 789 | 0x666bb90 | `xor eax,eax` | — | — |
| 790 | 0x666bb92 | `mov rcx,[rbp+0x300]` | stack read | — |
| 791 | 0x666bb99 | `mov [rbp+0x88],rcx` | — | — |
| 792 | 0x666bba0 | `mov [rbp+0x90],rax` | — | — |
| 793 | 0x666bba7 | `lea rax,[rbp+0x88]` | — | — |
| 794 | 0x666bbae | `movups [rax+0x10],xmm6` | — | — | — |
| 795 | 0x666bbb2 | `mov rax,[rbp+0x318]` | stack read | — |
| 796 | 0x666bbb9 | `test rax,rax` | — | — |
| 797 | 0x666bbbc | `je short 0x666BBD0` | branch | — |
| 798 | 0x666bbbe | `lock inc dword ptr [rax+8]` | rax+0x8 read/write | — |
| 799 | 0x666bbc2 | `mov rax,[rbp+0x318]` | stack read | — |
| 800 | 0x666bbc9 | `jmp short 0x666BBD2` | branch | — |
| 802 | 0x666bbd0 | `xor eax,eax` | — | — |
| 803 | 0x666bbd2 | `mov rcx,[rbp+0x310]` | stack read | — |
| 804 | 0x666bbd9 | `mov [rbp+0x98],rcx` | — | — |
| 805 | 0x666bbe0 | `mov [rbp+0xA0],rax` | — | — |
| 806 | 0x666bbe7 | `movaps xmm0,[rbp+0x320]` | stack read | — |
| 807 | 0x666bbee | `movups [rbp+0xA8],xmm0` | — | — | — |
| 808 | 0x666bbf5 | `movaps xmm0,[rbp+0x330]` | stack read | — |
| 809 | 0x666bbfc | `movups [rbp+0xB8],xmm0` | — | — | — |
| 810 | 0x666bc03 | `mov byte ptr [rbp+0x108],0xFF` | — | — | — |
| 811 | 0x666bc0a | `movzx eax,byte ptr [rbp+0x620]` | stack read | — |
| 812 | 0x666bc11 | `movzx ecx,al` | — | — |
| 813 | 0x666bc14 | `cmp ecx,1` | — | — |
| 814 | 0x666bc17 | `jg short 0x666BC60` | branch | — |
| 815 | 0x666bc19 | `test ecx,ecx` | — | — |
| 817 | 0x666bc1d | `movaps xmm0,[rbp+0x5E0]` | stack read | — |
| 818 | 0x666bc24 | `movaps xmm1,[rbp+0x5F0]` | stack read | — |
| 819 | 0x666bc2b | `movaps xmm2,[rbp+0x600]` | stack read | — |
| 820 | 0x666bc32 | `movaps xmm3,[rbp+0x610]` | stack read | — |
| 821 | 0x666bc39 | `movups [rbp+0xC8],xmm0` | — | — | — |
| 822 | 0x666bc40 | `movups [rbp+0xD8],xmm1` | — | — | — |
| 823 | 0x666bc47 | `movups [rbp+0xE8],xmm2` | — | — | — |
| 824 | 0x666bc4e | `movups [rbp+0xF8],xmm3` | — | — | — |
| 825 | 0x666bc55 | `jmp short 0x666BCA3` | branch | — |
| 827 | 0x666bc57 | `nop [rax+rax]` | — | — | — |
| 828 | 0x666bc60 | `cmp ecx,2` | — | — |
| 829 | 0x666bc63 | `jne short 0x666BCA9` | branch | — |
| 830 | 0x666bc65 | `mov rcx,[rbp+0x5E0]` | stack read | — |
| 831 | 0x666bc6c | `mov [rbp+0xC8],rcx` | — | — | — |
| 832 | 0x666bc73 | `jmp short 0x666BCA3` | branch | — |
| 833 | 0x666bc75 | `mov rcx,[rbp+0x5F0]` | stack read | — |
| 834 | 0x666bc7c | `mov qword ptr [rbp+0x5F0],0` | — | — | — |
| 835 | 0x666bc87 | `movaps xmm0,[rbp+0x5E0]` | stack read | — |
| 836 | 0x666bc8e | `movaps [rbp+0x5E0],xmm6` | — | — | — |
| 837 | 0x666bc95 | `movups [rbp+0xC8],xmm0` | — | — | — |
| 838 | 0x666bc9c | `mov [rbp+0xD8],rcx` | — | — | — |
| 839 | 0x666bca3 | `mov [rbp+0x108],al` | — | — | — |
| 840 | 0x666bca9 | `movaps xmm0,[rbp+0x2A0]` | stack read | — |
| 841 | 0x666bcb0 | `movaps xmm1,[rbp+0x2B0]` | stack read | — |
| 842 | 0x666bcb7 | `mov qword ptr [rbp+0x2A8],0` | — | — | — |
| 843 | 0x666bcc2 | `movups [rbp+0x110],xmm0` | — | — | — |
| 844 | 0x666bcc9 | `movaps [rbp+0x2B0],xmm6` | — | — | — |
| 845 | 0x666bcd0 | `movups [rbp+0x120],xmm1` | — | — | — |
| 846 | 0x666bcd7 | `mov rax,[rbp+0x2C0]` | stack read | — |
| 847 | 0x666bcde | `mov [rbp+0x130],rax` | — | — | — |
| 848 | 0x666bce5 | `mov byte ptr [rbp+0x148],0xFF` | — | — | — |
| 849 | 0x666bcec | `movzx eax,byte ptr [rbp+0x2D8]` | stack read | — |
| 850 | 0x666bcf3 | `cmp rax,3` | — | — |
| 851 | 0x666bcf7 | `ja short 0x666BD77` | branch | — |
| 852 | 0x666bcf9 | `lea rdx,[0xF2BF500]` | absolute lea | — |
| 853 | 0x666bd00 | `movsxd rcx,[rdx+rax*4]` | jump table read | — |
| 854 | 0x666bd04 | `add rcx,rdx` | — | — |
| 855 | 0x666bd07 | `jmp rcx` | indirect branch | — |
| 856 | 0x666bd09 | `mov rcx,[rbp+0x2C8]` | stack read | — |
| 857 | 0x666bd10 | `mov [rbp+0x138],rcx` | — | — | — |
| 858 | 0x666bd17 | `jmp short 0x666BD71` | branch | — |
| 859 | 0x666bd19 | `lea rcx,[rbp+0x2C8]` | — | — |
| 860 | 0x666bd20 | `movups xmm0,[rcx]` | rcx read | — |
| 861 | 0x666bd23 | `lea rcx,[rbp+0x88]` | — | — |
| 862 | 0x666bd2a | `movups [rcx+0xB0],xmm0` | — | — | — |
| 863 | 0x666bd31 | `jmp short 0x666BD71` | branch | — |
| 864 | 0x666bd33 | `lea rcx,[rbp+0x88]` | — | — |
| 865 | 0x666bd3a | `movups [rcx+0xB0],xmm6` | — | — | — |
| 866 | 0x666bd41 | `mov rcx,[rbp+0x2D0]` | stack read | — |
| 867 | 0x666bd48 | `test rcx,rcx` | — | — |
| 868 | 0x666bd4b | `je short 0x666BD5A` | branch | — |
| 869 | 0x666bd4d | `lock inc dword ptr [rcx+8]` | rcx+0x8 read/write | — |
| 870 | 0x666bd51 | `mov rcx,[rbp+0x2D0]` | stack read | — |
| 871 | 0x666bd58 | `jmp short 0x666BD5C` | branch | — |
| 872 | 0x666bd5a | `xor ecx,ecx` | — | — |
| 873 | 0x666bd5c | `mov rdx,[rbp+0x2C8]` | stack read | — |
| 874 | 0x666bd63 | `mov [rbp+0x138],rdx` | — | — | — |
| 875 | 0x666bd6a | `mov [rbp+0x140],rcx` | — | — | — |
| 876 | 0x666bd71 | `mov [rbp+0x148],al` | — | — | — |
| 877 | 0x666bd77 | `lea rdx,[rbp+0x2C8]` | — | — |
| 878 | 0x666bd7e | `mov rax,[rdx+0x28]` | rdx+0x28 = [rbp+0x2C8]+0x28 read | 8 | rax | stack |
| 881 | 0x666bd90 | `movups xmm0,[rdx+0x18]` | rdx+0x18 = [rbp+0x2C8]+0x18 read | 16 | xmm0 | stack |
| 882 | 0x666bd94 | `movups [rcx+0xC8],xmm0` | — | — | — |
| 883 | 0x666bd9b | `mov qword ptr [rbp-0x10],0` | — | — | — |
| 884 | 0x666bda3 | `mov dword ptr [rbp-8],0` | — | — | — |
| 885 | 0x666bdaa | `lea rax,[rbp+0x5C3]` | — | — |
| 886 | 0x666bdb1 | `mov qword ptr [rax+6],0` | — | — | — |
| 887 | 0x666bdb9 | `mov qword ptr [rax],0` | — | — | — |
| 888 | 0x666bdc0 | `mov rax,[rbp]` | stack read | — |
| 889 | 0x666bdc4 | `mov [rbp+0x3F0],rax` | — | — | — |
| 890 | 0x666bdcb | `lea rcx,[rbp+0x3F8]` | — | — |
| 891 | 0x666bdd2 | `lea rdx,[rbp+8]` | — | — |
| 892 | 0x666bdd6 | `call 0xE869FF0` | call 0xE869FF0 | — |
| 894 | 0x666bddc | `mov rax,[rbp+0x80]` | stack read | — |
| 895 | 0x666bde3 | `mov [rbp+0x470],rax` | — | — | — |
| 896 | 0x666bdea | `mov qword ptr [rbp+0x80],0` | — | — | — |
| 897 | 0x666bdf5 | `lea rax,[rbp+0x478]` | — | — |
| 898 | 0x666bdfc | `movups [rax],xmm6` | — | — | — |
| 899 | 0x666bdff | `mov rax,[rbp+0x90]` | stack read | — |
| 900 | 0x666be06 | `test rax,rax` | — | — |
| 901 | 0x666be09 | `je short 0x666BE20` | branch | — |
| 902 | 0x666be0b | `lock inc dword ptr [rax+8]` | rax+0x8 read/write | — |
| 903 | 0x666be0f | `mov rax,[rbp+0x90]` | stack read | — |
| 904 | 0x666be16 | `jmp short 0x666BE22` | branch | — |
| 905 | 0x666be18 | `nop [rax+rax]` | — | — | — |
| 906 | 0x666be20 | `xor eax,eax` | — | — |
| 907 | 0x666be22 | `mov rcx,[rbp+0x88]` | stack read | — |
| 908 | 0x666be29 | `mov [rbp+0x478],rcx` | — | — | — |
| 909 | 0x666be30 | `mov [rbp+0x480],rax` | — | — | — |
| 910 | 0x666be37 | `lea rax,[rbp+0x478]` | — | — |
| 911 | 0x666be3e | `movups [rax+0x10],xmm6` | — | — | — |
| 912 | 0x666be42 | `mov rax,[rbp+0xA0]` | stack read | — |
| 913 | 0x666be49 | `test rax,rax` | — | — |
| 914 | 0x666be4c | `je short 0x666BE60` | branch | — |
| 915 | 0x666be4e | `lock inc dword ptr [rax+8]` | rax+0x8 read/write | — |
| 916 | 0x666be52 | `mov rax,[rbp+0xA0]` | stack read | — |
| 917 | 0x666be59 | `jmp short 0x666BE62` | branch | — |
| 918 | 0x666be5b | `nop [rax+rax]` | — | — | — |
| 919 | 0x666be60 | `xor eax,eax` | — | — |
| 920 | 0x666be62 | `mov rcx,[rbp+0x98]` | stack read | — |
| 921 | 0x666be69 | `mov [rbp+0x488],rcx` | — | — | — |
| 922 | 0x666be70 | `mov [rbp+0x490],rax` | — | — | — |
| 923 | 0x666be77 | `movups xmm0,[rbp+0xA8]` | stack read | — |
| 924 | 0x666be7e | `movups [rbp+0x498],xmm0` | — | — | — |
| 925 | 0x666be85 | `movups xmm0,[rbp+0xB8]` | stack read | — |
| 926 | 0x666be8c | `movups [rbp+0x4A8],xmm0` | — | — | — |
| 927 | 0x666be93 | `mov byte ptr [rbp+0x4F8],0xFF` | — | — | — |
| 928 | 0x666be9a | `movzx eax,byte ptr [rbp+0x108]` | stack read | — |
| 929 | 0x666bea1 | `movzx ecx,al` | — | — |
| 930 | 0x666bea4 | `cmp ecx,1` | — | — |
| 931 | 0x666bea7 | `jg short 0x666BEF0` | branch | — |
| 932 | 0x666bea9 | `test ecx,ecx` | — | — |
| 933 | 0x666beab | `jne short 0x666BF05` | branch | — |
| 934 | 0x666bead | `movups xmm0,[rbp+0xC8]` | stack read | — |
| 935 | 0x666beb4 | `movups xmm1,[rbp+0xD8]` | stack read | — |
| 936 | 0x666bebb | `movups xmm2,[rbp+0xE8]` | stack read | — |
| 937 | 0x666bec2 | `movups xmm3,[rbp+0xF8]` | stack read | — |
| 938 | 0x666bec9 | `movups [rbp+0x4B8],xmm0` | — | — | — |
| 939 | 0x666bed0 | `movups [rbp+0x4C8],xmm1` | — | — | — |
| 940 | 0x666bed7 | `movups [rbp+0x4D8],xmm2` | — | — | — |
| 941 | 0x666bede | `movups [rbp+0x4E8],xmm3` | — | — | — |
| 943 | 0x666bee7 | `nop [rax+rax]` | — | — |
| 944 | 0x666bef0 | `cmp ecx,2` | — | — |
| 945 | 0x666bef3 | `jne short 0x666BF39` | branch | — |
| 946 | 0x666bef5 | `mov rcx,[rbp+0xC8]` | stack read | — |
| 947 | 0x666befc | `mov [rbp+0x4B8],rcx` | — | — | — |
| 948 | 0x666bf03 | `jmp short 0x666BF33` | branch | — |
| 949 | 0x666bf05 | `mov rcx,[rbp+0xD8]` | stack read | — |
| 950 | 0x666bf0c | `mov qword ptr [rbp+0xD8],0` | — | — | — |
| 951 | 0x666bf17 | `movups xmm0,[rbp+0xC8]` | stack read | — |
| 952 | 0x666bf1e | `movups [rbp+0xC8],xmm6` | — | — | — |
| 953 | 0x666bf25 | `movups [rbp+0x4B8],xmm0` | — | — | — |
| 954 | 0x666bf2c | `mov [rbp+0x4C8],rcx` | — | — | — |
| 955 | 0x666bf33 | `mov [rbp+0x4F8],al` | — | — | — |
| 956 | 0x666bf39 | `movups xmm0,[rbp+0x110]` | stack read | — |
| 957 | 0x666bf40 | `movups xmm1,[rbp+0x120]` | stack read | — |
| 958 | 0x666bf47 | `mov qword ptr [rbp+0x118],0` | — | — | — |
| 959 | 0x666bf52 | `movups [rbp+0x500],xmm0` | — | — | — |
| 960 | 0x666bf59 | `movups [rbp+0x120],xmm6` | — | — | — |
| 961 | 0x666bf60 | `movups [rbp+0x510],xmm1` | — | — | — |
| 962 | 0x666bf67 | `mov rax,[rbp+0x130]` | stack read | — |
| 963 | 0x666bf6e | `mov [rbp+0x520],rax` | — | — | — |
| 964 | 0x666bf75 | `mov byte ptr [rbp+0x538],0xFF` | — | — | — |
| 965 | 0x666bf7c | `movzx eax,byte ptr [rbp+0x148]` | stack read | — |
| 966 | 0x666bf83 | `cmp rax,3` | — | — |
| 967 | 0x666bf87 | `ja 0x666C00F` | branch | — |
| 968 | 0x666bf8d | `lea rdx,[0xF2BF510]` | absolute lea | — |
| 969 | 0x666bf94 | `movsxd rcx,[rdx+rax*4]` | jump table read | — |
| 970 | 0x666bf98 | `add rcx,rdx` | — | — |
| 971 | 0x666bf9b | `jmp rcx` | indirect branch | — |
| 972 | 0x666bf9d | `mov rcx,[rbp+0x138]` | stack read | — |
| 973 | 0x666bfa4 | `mov [rbp+0x528],rcx` | — | — | — |
| 974 | 0x666bfab | `jmp short 0x666C009` | branch | — |
| 975 | 0x666bfad | `lea rcx,[rbp+0x88]` | — | — |
| 976 | 0x666bfb4 | `movups xmm0,[rcx+0xB0]` | rcx+0xB0 read | — |
| 977 | 0x666bfbb | `lea rcx,[rbp+0x478]` | — | — |
| 978 | 0x666bfc2 | `movups [rcx+0xB0],xmm0` | — | — | — |
| 979 | 0x666bfc9 | `jmp short 0x666C009` | branch | — |
| 980 | 0x666bfcb | `lea rcx,[rbp+0x478]` | — | — |
| 981 | 0x666bfd2 | `movups [rcx+0xB0],xmm6` | — | — | — |
| 982 | 0x666bfd9 | `mov rcx,[rbp+0x140]` | stack read | — |
| 983 | 0x666bfe0 | `test rcx,rcx` | — | — |
| 984 | 0x666bfe3 | `je short 0x666BFF2` | branch | — |
| 985 | 0x666bfe5 | `lock inc dword ptr [rcx+8]` | rcx+0x8 read/write | — |
| 986 | 0x666bfe9 | `mov rcx,[rbp+0x140]` | stack read | — |
| 987 | 0x666bff0 | `jmp short 0x666BFF4` | branch | — |
| 988 | 0x666bff2 | `xor ecx,ecx` | — | — |
| 989 | 0x666bff4 | `mov rdx,[rbp+0x138]` | stack read | — |
| 990 | 0x666bffb | `mov [rbp+0x528],rdx` | — | — | — |
| 991 | 0x666c002 | `mov [rbp+0x530],rcx` | — | — | — |
| 992 | 0x666c009 | `mov [rbp+0x538],al` | — | — | — |
| 993 | 0x666c00f | `lea rcx,[rbp+0x88]` | — | — |
| 994 | 0x666c016 | `mov rax,[rcx+0xD8]` | rcx+0xD8 read | — |
| 995 | 0x666c01d | `lea rdx,[rbp+0x478]` | — | — |
| 996 | 0x666c024 | `mov [rdx+0xD8],rax` | — | — | — |
| 997 | 0x666c02b | `movups xmm0,[rcx+0xC8]` | rcx+0xC8 read | — |
| 998 | 0x666c032 | `movups [rdx+0xC8],xmm0` | — | — | — |
| 999 | 0x666c039 | `mov dword ptr [rbp+0x560],0` | — | — | — |
| 1000 | 0x666c043 | `mov byte ptr [rbp+0x564],0xF` | — | — | — |
| 1001 | 0x666c04a | `mov dword ptr [rbp+0x568],0` | — | — | — |
| 1002 | 0x666c054 | `mov word ptr [rbp+0x56C],0` | — | — | — |
| 1003 | 0x666c05d | `mov byte ptr [rbp+0x56E],2` | — | — | — |
| 1005 | 0x666c06e | `mov byte ptr [rbp+0x574],0` | — | — | — |
| 1006 | 0x666c075 | `movups [rdx+0x100],xmm6` | — | — | — |
| 1007 | 0x666c07c | `mov eax,[rbp-8]` | stack read | — |
| 1008 | 0x666c07f | `mov [rdx+0x118],eax` | — | — | — |
| 1009 | 0x666c085 | `mov rax,[rbp-0x10]` | stack read | — |
| 1010 | 0x666c089 | `mov [rdx+0x110],rax` | — | — | — |
| 1011 | 0x666c090 | `mov byte ptr [rbp+0x594],8` | — | — | — |
| 1012 | 0x666c097 | `mov qword ptr [rbp+0x598],0` | — | — | — |
| 1013 | 0x666c0a2 | `mov dword ptr [rbp+0x5A0],0` | — | — | — |
| 1014 | 0x666c0ac | `mov byte ptr [rbp+0x5A4],8` | — | — | — |
| 1015 | 0x666c0b3 | `movzx eax,byte ptr [rbp+0x5D0]` | stack read | — |
| 1016 | 0x666c0ba | `mov [rdx+0x13D],al` | — | — | — |
| 1017 | 0x666c0c0 | `movups xmm0,[rbp+0x5C0]` | stack read | — |
| 1018 | 0x666c0c7 | `movups [rdx+0x12D],xmm0` | — | — | — |
| 1019 | 0x666c0ce | `mov byte ptr [rbp+0x5B6],0xFF` | — | — | — |
| 1020 | 0x666c0d5 | `mov rcx,[r12+0x10]` | r12+0x10 read | — |
| 1021 | 0x666c0da | `mov eax,0x9D0` | — | — |
| 1022 | 0x666c0df | `add rcx,rax` | — | — |
| 1023 | 0x666c0e2 | `call 0x5ABA5C0` | call 0x5ABA5C0 | — |
| 1025 | 0x666c0e8 | `mov rbx,rax` | — | — |
| 1026 | 0x666c0eb | `movaps [rbp+0x280],xmm6` | — | — | — |
| 1027 | 0x666c0f2 | `movaps [rbp+0x270],xmm6` | — | — | — |
| 1028 | 0x666c0f9 | `movaps [rbp+0x260],xmm6` | — | — | — |
| 1029 | 0x666c100 | `movaps [rbp+0x250],xmm6` | — | — | — |
| 1030 | 0x666c107 | `movaps [rbp+0x240],xmm6` | — | — | — |
| 1031 | 0x666c10e | `movaps [rbp+0x230],xmm6` | — | — | — |
| 1032 | 0x666c115 | `movaps [rbp+0x220],xmm6` | — | — | — |
| 1033 | 0x666c11c | `movaps [rbp+0x210],xmm6` | — | — | — |
| 1034 | 0x666c123 | `movaps [rbp+0x200],xmm6` | — | — | — |
| 1035 | 0x666c12a | `movaps [rbp+0x1F0],xmm6` | — | — | — |
| 1036 | 0x666c131 | `movaps [rbp+0x1E0],xmm6` | — | — | — |
| 1037 | 0x666c138 | `movaps [rbp+0x1D0],xmm6` | — | — | — |
| 1038 | 0x666c13f | `mov qword ptr [rbp+0x290],0` | — | — | — |
| 1039 | 0x666c14a | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1040 | 0x666c151 | `mov rax,[rcx]` | rcx read | — |
| 1041 | 0x666c154 | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1042 | 0x666c158 | `mov dl,0x4A` | — | — |
| 1043 | 0x666c15a | `call qword ptr [0xF99FFA0]` | call | — |
| 1045 | 0x666c161 | `mov [rbp+0x670],al` | — | — | — |
| 1046 | 0x666c167 | `mov rdx,[rbx+0x758]` | rbx+0x758 read | — |
| 1047 | 0x666c16e | `cmp rdx,[rbx+0x760]` | rbx+0x760 read | — |
| 1048 | 0x666c175 | `je 0x666C200` | branch | — |
| 1049 | 0x666c17b | `lea rcx,[rbp+0x560]` | — | — |
| 1050 | 0x666c182 | `mov eax,[rcx+0x10]` | rcx+0x10 read | — |
| 1051 | 0x666c185 | `mov [rdx+0x10],eax` | — | — | — |
| 1052 | 0x666c188 | `movups xmm0,[rcx]` | rcx read | — |
| 1053 | 0x666c18b | `movups [rdx],xmm0` | — | — | — |
| 1054 | 0x666c18e | `movzx eax,byte ptr [rbp+0x574]` | stack read | — |
| 1055 | 0x666c195 | `mov [rdx+0x14],al` | — | — | — |
| 1056 | 0x666c198 | `movss xmm0,[rbp+0x578]` | stack read | — |
| 1057 | 0x666c1a0 | `movss [rdx+0x18],xmm0` | — | — | — |
| 1058 | 0x666c1a5 | `movss xmm0,[rbp+0x57C]` | stack read | — |
| 1059 | 0x666c1ad | `movss [rdx+0x1C],xmm0` | — | — | — |
| 1060 | 0x666c1b2 | `movss xmm0,[rbp+0x580]` | stack read | — |
| 1061 | 0x666c1ba | `movss [rdx+0x20],xmm0` | — | — | — |
| 1062 | 0x666c1bf | `movss xmm0,[rbp+0x584]` | stack read | — |
| 1063 | 0x666c1c7 | `movss [rdx+0x24],xmm0` | — | — | — |
| 1064 | 0x666c1cc | `lea rax,[rbp+0x478]` | — | — |
| 1065 | 0x666c1d3 | `movups xmm0,[rax+0x110]` | rax+0x110 read | — |
| 1066 | 0x666c1da | `movups xmm1,[rax+0x120]` | rax+0x120 read | — |
| 1067 | 0x666c1e1 | `movups xmm2,[rax+0x12F]` | rax+0x12F read | — |
| 1068 | 0x666c1e8 | `movups [rdx+0x28],xmm0` | — | — | — |
| 1069 | 0x666c1ec | `movups [rdx+0x38],xmm1` | — | — | — |
| 1070 | 0x666c1f0 | `movups [rdx+0x47],xmm2` | — | — | — |
| 1071 | 0x666c1f4 | `add qword ptr [rbx+0x758],0x58` | rbx+0x758 read/write | — |
| 1073 | 0x666c1fe | `xchg ax,ax` | — | — |
| 1074 | 0x666c200 | `lea rcx,[rbx+0x750]` | — | — |
| 1075 | 0x666c207 | `lea r8,[rbp+0x560]` | — | — |
| 1076 | 0x666c20e | `call 0x6760A80` | call 0x6760A80 | — |
| 1078 | 0x666c214 | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1079 | 0x666c21b | `mov rax,[rcx]` | rcx read | — |
| 1080 | 0x666c21e | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1081 | 0x666c222 | `movzx edx,byte ptr [rbp+0x670]` | stack read | — |
| 1082 | 0x666c229 | `call qword ptr [0xF99FFA0]` | call | — |
| 1084 | 0x666c230 | `mov eax,[rbx+0x758]` | rbx+0x758 read | — |
| 1085 | 0x666c236 | `sub eax,[rbx+0x750]` | rbx+0x750 read | — |
| 1086 | 0x666c23c | `shr eax,3` | — | — |
| 1087 | 0x666c23f | `imul eax,0xFFFF8BA3` | — | — |
| 1088 | 0x666c245 | `dec eax` | — | — |
| 1089 | 0x666c247 | `mov [rbp+0x1FC],ax` | — | — | — |
| 1090 | 0x666c24e | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1091 | 0x666c255 | `mov rax,[rcx]` | rcx read | — |
| 1092 | 0x666c258 | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1093 | 0x666c25c | `mov dl,0x4A` | — | — |
| 1094 | 0x666c25e | `call qword ptr [0xF99FFA0]` | call | — |
| 1096 | 0x666c265 | `mov edx,eax` | — | — |
| 1097 | 0x666c267 | `mov rax,r12` | r12 read | — |
| 1098 | 0x666c26a | `mov r12,r14` | r14 read (desc+0x18) | — |
| 1099 | 0x666c26d | `mov r14,[rbx+0x878]` | rbx+0x878 read | — |
| 1100 | 0x666c274 | `cmp r14,[rbx+0x880]` | rbx+0x880 read | — |
| 1101 | 0x666c27b | `je short 0x666C2A0` | branch | — |
| 1102 | 0x666c27d | `inc r14` | — | — |
| 1103 | 0x666c280 | `mov [rbx+0x878],r14` | rbx+0x878 write | — |
| 1104 | 0x666c287 | `mov r14,r12` | — | — |
| 1105 | 0x666c28a | `mov r12,rax` | — | — |
| 1106 | 0x666c28d | `jmp 0x666C44A` | branch | — |
| 1108 | 0x666c2a0 | `mov r15,r14` | r15 = r14 (desc+0x18 VALUE copied into r15; r15 NO LONGER holds description base!) | [I] |
| 1109 | 0x666c2a3 | `sub r15,[rbx+0x870]` | rbx+0x870 read | — |
| 1110 | 0x666c2aa | `mov rcx,0x7FFFFFFFFFFFFFFF` | — | — |
| 1111 | 0x666c2b4 | `cmp r15,rcx` | — | — |
| 1112 | 0x666c2b7 | `mov [rbp+0x670],dl` | — | — | — |
| 1113 | 0x666c2bd | `je 0x6670A94` | branch exit | — |
| 1114 | 0x666c2c3 | `lea r8,[r15+1]` | — | — |
| 1115 | 0x666c2c7 | `mov r13,r15` | — | — |
| 1116 | 0x666c2ca | `shr r13,1` | — | — |
| 1117 | 0x666c2cd | `mov rax,r13` | — | — |
| 1118 | 0x666c2d0 | `xor rax,rcx` | — | — |
| 1119 | 0x666c2d3 | `add r13,r15` | — | — |
| 1120 | 0x666c2d6 | `cmp r13,r8` | — | — |
| 1121 | 0x666c2d9 | `mov [rbp+0x658],r8` | — | — | — |
| 1122 | 0x666c2e0 | `cmovbe r13,r8` | — | — |
| 1123 | 0x666c2e4 | `cmp r15,rax` | — | — |
| 1124 | 0x666c2e7 | `cmova r13,rcx` | — | — |
| 1125 | 0x666c2eb | `test r13,r13` | — | — |
| 1126 | 0x666c2ee | `je 0x666C3A9` | branch exit | — |
| 1127 | 0x666c2f4 | `cmp r13,0x1000` | — | — |
| 1128 | 0x666c2fb | `jb short 0x666C349` | branch | — |
| 1129 | 0x666c2fd | `cmp r13,0xFFFFFFFFFFFFFFD9` | — | — |
| 1130 | 0x666c301 | `jae 0x6670C3B` | branch exit | — |
| 1131 | 0x666c307 | `lea rdi,[r13+0x27]` | — | — |
| 1132 | 0x666c30b | `mov rcx,[0x1233E1A8]` | absolute read | — |
| 1133 | 0x666c312 | `mov rax,[rcx]` | rcx read | — |
| 1135 | 0x666c319 | `mov rdx,rdi` | — | — |
| 1136 | 0x666c31c | `call qword ptr [0xF99FFA0]` | call | — |
| 1138 | 0x666c323 | `mov rsi,rax` | — | — |
| 1139 | 0x666c326 | `test rax,rax` | — | — |
| 1140 | 0x666c329 | `je 0x666C838` | branch exit | — |
| 1141 | 0x666c32f | `mov rax,rsi` | — | — |
| 1142 | 0x666c332 | `add rsi,0x27` | — | — |
| 1143 | 0x666c336 | `and rsi,0xFFFFFFFFFFFFFFE0` | — | — |
| 1144 | 0x666c33a | `mov [rsi-8],rax` | — | — | — |
| 1145 | 0x666c33e | `cmp r14,[rbx+0x878]` | rbx+0x878 read | — |
| 1146 | 0x666c345 | `jne short 0x666C372` | branch | — |
| 1147 | 0x666c347 | `jmp short 0x666C3B4` | branch | — |
| 1149 | 0x666c349 | `mov rcx,[0x1233E1A8]` | absolute read | — |
| 1150 | 0x666c350 | `mov rax,[rcx]` | rcx read | — |
| 1151 | 0x666c353 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1152 | 0x666c357 | `mov rdx,r13` | — | — |
| 1153 | 0x666c35a | `call qword ptr [0xF99FFA0]` | call | — |
| 1154 | 0x666c360 | `nop` | — | — |
| 1155 | 0x666c361 | `mov rsi,rax` | — | — |
| 1156 | 0x666c364 | `test rax,rax` | — | — |
| 1157 | 0x666c367 | `je short 0x666C3A0` | branch | — |
| 1158 | 0x666c369 | `cmp r14,[rbx+0x878]` | rbx+0x878 read | — |
| 1159 | 0x666c370 | `je short 0x666C3B4` | branch | — |
| 1160 | 0x666c372 | `lea rdi,[rsi+r15]` | r15 read (desc+0x18 value) | — |
| 1161 | 0x666c376 | `inc rdi` | — | — |
| 1162 | 0x666c379 | `mov rdx,[rbx+0x870]` | rbx+0x870 read | — |
| 1163 | 0x666c380 | `mov r8,r14` | — | — |
| 1164 | 0x666c383 | `sub r8,rdx` | — | — |
| 1165 | 0x666c386 | `mov rcx,rsi` | — | — |
| 1166 | 0x666c389 | `call 0xEEC6DE0` | call 0xEEC6DE0 | — |
| 1167 | 0x666c38e | `mov r8,[rbx+0x878]` | rbx+0x878 read | — |
| 1168 | 0x666c395 | `sub r8,r14` | — | — |
| 1169 | 0x666c398 | `mov rcx,rdi` | — | — |
| 1170 | 0x666c39b | `mov rdx,r14` | — | — |
| 1171 | 0x666c39e | `jmp short 0x666C3C4` | branch | — |
| 1173 | 0x666c3a0 | `mov rcx,r13` | — | — |
| 1174 | 0x666c3a3 | `call 0x9BC830` | call 0x9BC830 | — |
| 1175 | 0x666c3a8 | `nop` | — | — |
| 1176 | 0x666c3a9 | `xor esi,esi` | — | — |
| 1177 | 0x666c3ab | `cmp r14,[rbx+0x878]` | rbx+0x878 read | — |
| 1178 | 0x666c3b2 | `jne short 0x666C372` | branch | — |
| 1179 | 0x666c3b4 | `mov rdx,[rbx+0x870]` | rbx+0x870 read | — |
| 1180 | 0x666c3bb | `sub r14,rdx` | — | — |
| 1181 | 0x666c3be | `mov rcx,rsi` | — | — |
| 1182 | 0x666c3c1 | `mov r8,r14` | — | — |
| 1183 | 0x666c3c4 | `call 0xEEC6DE0` | call 0xEEC6DE0 | — |
| 1184 | 0x666c3c9 | `mov r15,[rbp+0x668]` | r15 = [rbp+0x668] (description base RESTORED) | [V] |
| 1185 | 0x666c3d0 | `mov rcx,[rbx+0x870]` | rbx+0x870 read | — |
| 1186 | 0x666c3d7 | `test rcx,rcx` | — | — |
| 1187 | 0x666c3da | `mov r14,r12` | r14 = r12 | — |
| 1188 | 0x666c3dd | `je short 0x666C413` | branch | — |
| 1189 | 0x666c3df | `mov rdx,[rbx+0x880]` | rbx+0x880 read | — |
| 1190 | 0x666c3e6 | `sub rdx,rcx` | — | — |
| 1191 | 0x666c3e9 | `cmp rdx,0x1000` | — | — |
| 1192 | 0x666c3f0 | `jb short 0x666C40E` | branch | — |
| 1193 | 0x666c3f2 | `mov rax,[rcx-8]` | rcx-0x8 read | — |
| 1194 | 0x666c3f6 | `add rcx,0xFFFFFFFFFFFFFFF8` | — | — |
| 1195 | 0x666c3fa | `sub rcx,rax` | — | — |
| 1197 | 0x666c401 | `jae 0x6670A7A` | branch exit | — |
| 1198 | 0x666c407 | `add rdx,0x27` | — | — |
| 1199 | 0x666c40b | `mov rcx,rax` | — | — |
| 1200 | 0x666c40e | `call 0xE935700` | call 0xE935700 | — |
| 1201 | 0x666c413 | `mov [rbx+0x870],rsi` | rbx+0x870 write | — |
| 1202 | 0x666c41a | `mov rax,[rbp+0x658]` | stack read | — |
| 1203 | 0x666c421 | `add rax,rsi` | — | — |
| 1204 | 0x666c424 | `mov [rbx+0x878],rax` | rbx+0x878 write | — |
| 1205 | 0x666c42b | `add r13,rsi` | — | — |
| 1206 | 0x666c42e | `mov [rbx+0x880],r13` | rbx+0x880 write | — |
| 1207 | 0x666c435 | `mov r12,[rbp+0x650]` | stack read | — |
| 1208 | 0x666c43c | `lea r13,[rbp+0x3F0]` | — | — |
| 1209 | 0x666c443 | `movzx edx,byte ptr [rbp+0x670]` | stack read | — |
| 1210 | 0x666c44a | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1211 | 0x666c451 | `mov rax,[rcx]` | rcx read | — |
| 1212 | 0x666c454 | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1213 | 0x666c458 | `call qword ptr [0xF99FFA0]` | call | — |
| 1215 | 0x666c45f | `mov eax,[rbx+0x870]` | rbx+0x870 read | — |
| 1216 | 0x666c465 | `not eax` | — | — |
| 1217 | 0x666c467 | `add eax,[rbx+0x878]` | rbx+0x878 read | — |
| 1218 | 0x666c46d | `mov [rbp+0x1E4],ax` | — | — | — |
| 1219 | 0x666c474 | `lea rcx,[rbx+0x780]` | — | — |
| 1220 | 0x666c47b | `lea rdx,[rbp+0x500]` | — | — |
| 1221 | 0x666c482 | `call 0x675F3B0` | call 0x675F3B0 | — |
| 1223 | 0x666c488 | `mov qword ptr [rbp+0x1D0],0x5004` | — | — | — |
| 1224 | 0x666c493 | `mov eax,[rbx+0x788]` | rbx+0x788 read | — |
| 1225 | 0x666c499 | `sub eax,[rbx+0x780]` | rbx+0x780 read | — |
| 1226 | 0x666c49f | `shr eax,3` | — | — |
| 1227 | 0x666c4a2 | `imul eax,0xFFFF8BA3` | — | — |
| 1228 | 0x666c4a8 | `dec eax` | — | — |
| 1229 | 0x666c4aa | `mov [rbp+0x1F8],ax` | — | — | — |
| 1230 | 0x666c4b1 | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1231 | 0x666c4b8 | `mov rax,[rcx]` | rcx read | — |
| 1232 | 0x666c4bb | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1233 | 0x666c4bf | `mov dl,0x4A` | — | — |
| 1234 | 0x666c4c1 | `call qword ptr [0xF99FFA0]` | call | — |
| 1236 | 0x666c4c7 | `mov [rbp+0x670],al` | — | — | — |
| 1237 | 0x666c4cd | `lea rcx,[rbx+0x648]` | — | — |
| 1238 | 0x666c4d4 | `lea rdx,[rbp+0x4B8]` | — | — |
| 1239 | 0x666c4db | `call 0x675FB30` | call 0x675FB30 | — |
| 1241 | 0x666c4e1 | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1242 | 0x666c4e8 | `mov rax,[rcx]` | rcx read | — |
| 1243 | 0x666c4eb | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1244 | 0x666c4ef | `movzx edx,byte ptr [rbp+0x670]` | stack read | — |
| 1245 | 0x666c4f6 | `call qword ptr [0xF99FFA0]` | call | — |
| 1248 | 0x666c4fd | `mov eax,[rbx+0x650]` | rbx+0x650 read | — |
| 1249 | 0x666c503 | `sub eax,[rbx+0x648]` | rbx+0x648 read | — |
| 1250 | 0x666c509 | `shr eax,3` | — | — |
| 1251 | 0x666c50c | `imul eax,0xFFFF8E39` | — | — |
| 1252 | 0x666c512 | `dec eax` | — | — |
| 1253 | 0x666c514 | `mov [rbp+0x212],ax` | — | — | — |
| 1254 | 0x666c51b | `lea rcx,[rbx+0x720]` | — | — |
| 1255 | 0x666c522 | `lea rdx,[rbp+0x478]` | — | — |
| 1256 | 0x666c529 | `call 0x67D7410` | call 0x67D7410 | — |
| 1259 | 0x666c535 | `sub eax,[rbx+0x720]` | rbx+0x720 read | — |
| 1260 | 0x666c53b | `shr eax,6` | — | — |
| 1261 | 0x666c53e | `dec eax` | — | — |
| 1262 | 0x666c540 | `mov [rbp+0x200],ax` | — | — | — |
| 1263 | 0x666c547 | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1264 | 0x666c54e | `mov rax,[rcx]` | rcx read | — |
| 1265 | 0x666c551 | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1266 | 0x666c555 | `mov dl,0x4A` | — | — |
| 1267 | 0x666c557 | `call qword ptr [0xF99FFA0]` | call | — |
| 1269 | 0x666c55e | `mov [rbp+0x670],al` | — | — | — |
| 1270 | 0x666c564 | `mov rsi,[rbx+0x770]` | rbx+0x770 read | — |
| 1271 | 0x666c56b | `cmp rsi,[rbx+0x778]` | rbx+0x778 read | — |
| 1272 | 0x666c572 | `je short 0x666C5C0` | branch | — |
| 1273 | 0x666c574 | `mov rax,[rbp+0x3F0]` | stack read | — |
| 1274 | 0x666c57b | `mov [rsi],rax` | — | — | — |
| 1275 | 0x666c57e | `lea rcx,[rsi+8]` | — | — |
| 1276 | 0x666c582 | `lea rdx,[rbp+0x3F8]` | — | — |
| 1277 | 0x666c589 | `call 0xE869FF0` | call 0xE869FF0 | — |
| 1279 | 0x666c58f | `mov rax,[rbp+0x470]` | stack read | — |
| 1280 | 0x666c596 | `mov [rsi+0x80],rax` | — | — | — |
| 1281 | 0x666c59d | `mov qword ptr [rbp+0x470],0` | — | — | — |
| 1282 | 0x666c5a8 | `add qword ptr [rbx+0x770],0x88` | rbx+0x770 read/write | — |
| 1283 | 0x666c5b3 | `jmp short 0x666C5D6` | branch | — |
| 1285 | 0x666c5b5 | `nop [rax+rax]` | — | — | — |
| 1286 | 0x666c5c0 | `mov rcx,rbx` | — | — |
| 1287 | 0x666c5c3 | `add rcx,0x768` | — | — |
| 1288 | 0x666c5ca | `mov rdx,rsi` | — | — |
| 1289 | 0x666c5cd | `mov r8,r13` | — | — |
| 1290 | 0x666c5d0 | `call 0x6760710` | call 0x6760710 | — |
| 1292 | 0x666c5d5 | `nop` | — | — |
| 1293 | 0x666c5d6 | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1294 | 0x666c5dd | `mov rax,[rcx]` | rcx read | — |
| 1295 | 0x666c5e0 | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1296 | 0x666c5e4 | `movzx edx,byte ptr [rbp+0x670]` | stack read | — |
| 1297 | 0x666c5eb | `call qword ptr [0xF99FFA0]` | call | — |
| 1299 | 0x666c5f1 | `nop` | — | — |
| 1300 | 0x666c5f2 | `mov qword ptr [rbp+0x1D0],0x2017004` | — | — | — |
| 1301 | 0x666c5fd | `mov eax,[rbx+0x770]` | rbx+0x770 read | — |
| 1302 | 0x666c603 | `sub eax,[rbx+0x768]` | rbx+0x768 read | — |
| 1303 | 0x666c609 | `shr eax,3` | — | — |
| 1304 | 0x666c60c | `imul eax,0xFFFFF0F1` | — | — |
| 1305 | 0x666c612 | `dec eax` | — | — |
| 1306 | 0x666c614 | `mov [rbp+0x1FA],ax` | — | — | — |
| 1307 | 0x666c61b | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1308 | 0x666c622 | `mov rax,[rcx]` | rcx read | — |
| 1309 | 0x666c625 | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1310 | 0x666c629 | `mov dl,0x4A` | — | — |
| 1311 | 0x666c62b | `call qword ptr [0xF99FFA0]` | call | — |
| 1313 | 0x666c631 | `nop` | — | — |
| 1314 | 0x666c632 | `mov [rbp+0x670],al` | — | — | — |
| 1315 | 0x666c638 | `mov rdx,[rbx+8]` | rbx+8 read | — |
| 1316 | 0x666c63c | `cmp rdx,[rbx+0x10]` | rbx+0x10 read | — |
| 1317 | 0x666c640 | `je short 0x666C670` | branch | — |
| 1318 | 0x666c642 | `mov r8d,0xC8` | — | — |
| 1319 | 0x666c648 | `mov rcx,rdx` | — | — |
| 1321 | 0x666c652 | `call 0xEEC6EC0` | call 0xEEC6EC0 | — |
| 1322 | 0x666c657 | `add qword ptr [rbx+8],0xC8` | rbx+8 read/write | — |
| 1323 | 0x666c65f | `jmp short 0x666C680` | branch | — |
| 1325 | 0x666c661 | `nop [rax+rax]` | — | — | — |
| 1326 | 0x666c670 | `mov rcx,rbx` | — | — |
| 1327 | 0x666c673 | `lea r8,[rbp+0x1D0]` | — | — |
| 1328 | 0x666c67a | `call 0x5ABA6D0` | call 0x5ABA6D0 | — |
| 1330 | 0x666c67f | `nop` | — | — |
| 1331 | 0x666c680 | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1332 | 0x666c687 | `mov rax,[rcx]` | rcx read | — |
| 1333 | 0x666c68a | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1334 | 0x666c68e | `movzx edx,byte ptr [rbp+0x670]` | stack read | — |
| 1335 | 0x666c695 | `call qword ptr [0xF99FFA0]` | call | — |
| 1337 | 0x666c69b | `nop` | — | — |
| 1338 | 0x666c69c | `mov rcx,r13` | — | — |
| 1339 | 0x666c69f | `call 0x674A1D0` | call 0x674A1D0 | — |
| 1340 | 0x666c6a4 | `mov rcx,rbp` | — | — |
| 1341 | 0x666c6a7 | `call 0x674A1D0` | call 0x674A1D0 | — |
| 1342 | 0x666c6ac | `cmp byte ptr [rbp+0x2D8],3` | stack read | — |
| 1343 | 0x666c6b3 | `jne short 0x666C6F0` | branch | — |
| 1344 | 0x666c6b5 | `mov rsi,[rbp+0x2D0]` | stack read | — |
| 1345 | 0x666c6bc | `test rsi,rsi` | — | — |
| 1346 | 0x666c6bf | `je short 0x666C6F0` | branch | — |
| 1347 | 0x666c6c1 | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 1348 | 0x666c6c5 | `jne short 0x666C6F0` | branch | — |
| 1349 | 0x666c6c7 | `mov rax,[rsi]` | rsi read | — |
| 1350 | 0x666c6ca | `mov rax,[rax]` | rax read | — |
| 1351 | 0x666c6cd | `mov rcx,rsi` | — | — |
| 1352 | 0x666c6d0 | `call qword ptr [0xF99FFA0]` | call | — |
| 1353 | 0x666c6d6 | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 1354 | 0x666c6da | `jne short 0x666C6F0` | branch | — |
| 1355 | 0x666c6dc | `mov rax,[rsi]` | rsi read | — |
| 1356 | 0x666c6df | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1357 | 0x666c6e3 | `mov rcx,rsi` | — | — |
| 1358 | 0x666c6e6 | `call qword ptr [0xF99FFA0]` | call | — |
| 1360 | 0x666c6ec | `nop [rax]` | — | — | — |
| 1361 | 0x666c6f0 | `mov rdi,[rbp+0x2A8]` | stack read | — |
| 1362 | 0x666c6f7 | `test rdi,rdi` | — | — |
| 1363 | 0x666c6fa | `je short 0x666C760` | branch | — |
| 1364 | 0x666c6fc | `mov rbx,[rbp+0x2B0]` | stack read | — |
| 1365 | 0x666c703 | `jmp short 0x666C714` | branch | — |
| 1367 | 0x666c705 | `nop [rax+rax]` | — | — | — |
| 1368 | 0x666c710 | `add rdi,0x28` | — | — |
| 1369 | 0x666c714 | `cmp rdi,rbx` | — | — |
| 1370 | 0x666c717 | `je short 0x666C760` | branch | — |
| 1371 | 0x666c719 | `cmp byte ptr [rdi+0x18],2` | rdi+0x18 read | — |
| 1372 | 0x666c71d | `jne short 0x666C710` | branch | — |
| 1373 | 0x666c71f | `mov rsi,[rdi+8]` | rdi+8 read | — |
| 1374 | 0x666c723 | `test rsi,rsi` | — | — |
| 1375 | 0x666c726 | `je short 0x666C710` | branch | — |
| 1376 | 0x666c728 | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 1377 | 0x666c72c | `jne short 0x666C710` | branch | — |
| 1378 | 0x666c72e | `mov rax,[rsi]` | rsi read | — |
| 1379 | 0x666c731 | `mov rax,[rax]` | rax read | — |
| 1380 | 0x666c734 | `mov rcx,rsi` | — | — |
| 1381 | 0x666c737 | `call qword ptr [0xF99FFA0]` | call | — |
| 1383 | 0x666c741 | `jne short 0x666C710` | branch | — |
| 1384 | 0x666c743 | `mov rax,[rsi]` | rsi read | — |
| 1385 | 0x666c746 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1386 | 0x666c74a | `mov rcx,rsi` | — | — |
| 1387 | 0x666c74d | `call qword ptr [0xF99FFA0]` | call | — |
| 1388 | 0x666c753 | `jmp short 0x666C710` | branch | — |
| 1390 | 0x666c755 | `nop [rax+rax]` | — | — | — |
| 1391 | 0x666c760 | `cmp byte ptr [rbp+0x620],1` | stack read | — |
| 1392 | 0x666c767 | `mov rbx,[rbp+0x648]` | stack read | — |
| 1393 | 0x666c76e | `jne short 0x666C7B0` | branch | — |
| 1394 | 0x666c770 | `mov rcx,[rbp+0x5E0]` | stack read | — |
| 1395 | 0x666c777 | `test rcx,rcx` | — | — |
| 1396 | 0x666c77a | `je short 0x666C7B0` | branch | — |
| 1397 | 0x666c77c | `mov rdx,[rbp+0x5F0]` | stack read | — |
| 1398 | 0x666c783 | `sub rdx,rcx` | — | — |
| 1399 | 0x666c786 | `cmp rdx,0x1000` | — | — |
| 1400 | 0x666c78d | `jb short 0x666C7AB` | branch | — |
| 1401 | 0x666c78f | `mov rax,[rcx-8]` | rcx-0x8 read | — |
| 1402 | 0x666c793 | `add rcx,0xFFFFFFFFFFFFFFF8` | — | — |
| 1403 | 0x666c797 | `sub rcx,rax` | — | — |
| 1404 | 0x666c79a | `cmp rcx,0x20` | — | — |
| 1405 | 0x666c79e | `jae 0x6670A7A` | branch exit | — |
| 1406 | 0x666c7a4 | `or rdx,0x27` | — | — |
| 1407 | 0x666c7a8 | `mov rcx,rax` | — | — |
| 1408 | 0x666c7ab | `call 0xE935700` | call 0xE935700 | — |
| 1409 | 0x666c7b0 | `mov rsi,[rbp+0x318]` | stack read | — |
| 1410 | 0x666c7b7 | `test rsi,rsi` | — | — |
| 1411 | 0x666c7ba | `je short 0x666C7F0` | branch | — |
| 1412 | 0x666c7bc | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 1413 | 0x666c7c0 | `jne short 0x666C7F0` | branch | — |
| 1414 | 0x666c7c2 | `mov rax,[rsi]` | rsi read | — |
| 1415 | 0x666c7c5 | `mov rax,[rax]` | rax read | — |
| 1416 | 0x666c7c8 | `mov rcx,rsi` | — | — |
| 1417 | 0x666c7cb | `call qword ptr [0xF99FFA0]` | call | — |
| 1418 | 0x666c7d1 | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 1419 | 0x666c7d5 | `jne short 0x666C7F0` | branch | — |
| 1420 | 0x666c7d7 | `mov rax,[rsi]` | rsi read | — |
| 1421 | 0x666c7da | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1422 | 0x666c7de | `mov rcx,rsi` | — | — |
| 1423 | 0x666c7e1 | `call qword ptr [0xF99FFA0]` | call | — |
| 1425 | 0x666c7e7 | `nop [rax+rax]` | — | — | — |
| 1426 | 0x666c7f0 | `mov rsi,[rbp+0x308]` | stack read | — |
| 1427 | 0x666c7f7 | `test rsi,rsi` | — | — |
| 1428 | 0x666c7fa | `je 0x666B700` | branch exit | — |
| 1429 | 0x666c800 | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 1430 | 0x666c804 | `jne 0x666B700` | branch exit | — |
| 1431 | 0x666c80a | `mov rax,[rsi]` | rsi read | — |
| 1432 | 0x666c80d | `mov rax,[rax]` | rax read | — |
| 1433 | 0x666c810 | `mov rcx,rsi` | — | — |
| 1434 | 0x666c813 | `call qword ptr [0xF99FFA0]` | call | — |
| 1435 | 0x666c819 | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 1436 | 0x666c81d | `jne 0x666B700` | branch exit | — |
| 1437 | 0x666c823 | `mov rax,[rsi]` | rsi read | — |
| 1438 | 0x666c826 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1439 | 0x666c82a | `mov rcx,rsi` | — | — |
| 1440 | 0x666c82d | `call qword ptr [0xF99FFA0]` | call | — |
| 1441 | 0x666c833 | `jmp 0x666B700` | branch exit | — |
| 1443 | 0x666c838 | `mov rcx,rdi` | — | — |
| 1446 | 0x666c840 | `nop` | — | — |
| 1447 | 0x666c841 | `jmp 0x666C32F` | branch exit | — |
| 1448 | 0x666c846 | `mov rsi,[rbp+0x3E8]` | stack read | — |
| 1449 | 0x666c84d | `test rsi,rsi` | — | — |
| 1450 | 0x666c850 | `jne 0x666FB88` | branch exit | — |
| 1451 | 0x666c856 | `jmp 0x6670032` | branch exit | — |
| 1452 | 0x666c85b | `mov rax,[rsi]` | rsi read | — |
| 1453 | 0x666c85e | `mov rax,[rax+0x18]` | rax+0x18 read | — |
| 1454 | 0x666c862 | `mov rbx,[rax]` | rax read | — |
| 1455 | 0x666c865 | `test rbx,rbx` | — | — |
| 1456 | 0x666c868 | `je 0x666FB78` | branch exit | — |
| 1457 | 0x666c86e | `mov r14,[r12]` | r12 read | — |
| 1458 | 0x666c872 | `mov rax,[rbp+0x630]` | stack read | — |
| 1459 | 0x666c879 | `xorps xmm0,xmm0` | — | — |
| 1460 | 0x666c87c | `movaps [rbp+0x3F0],xmm0` | — | — | — |
| 1461 | 0x666c883 | `mov rcx,[rax+8]` | rax+0x8 read | — |
| 1462 | 0x666c887 | `test rcx,rcx` | — | — |
| 1463 | 0x666c88a | `je 0x666CF20` | branch exit | — |
| 1464 | 0x666c890 | `lock inc dword ptr [rcx+8]` | rcx+0x8 read/write | — |
| 1465 | 0x666c894 | `mov rsi,[rbp+0x3F8]` | stack read | — |
| 1466 | 0x666c89b | `movups xmm0,[rax]` | rax read | — |
| 1467 | 0x666c89e | `movaps [rbp+0x3F0],xmm0` | — | — | — |
| 1468 | 0x666c8a5 | `test rsi,rsi` | — | — |
| 1469 | 0x666c8a8 | `je 0x666CF35` | branch exit | — |
| 1470 | 0x666c8ae | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 1471 | 0x666c8b2 | `jne 0x666CF35` | branch exit | — |
| 1472 | 0x666c8b8 | `mov rax,[rsi]` | rsi read | — |
| 1473 | 0x666c8bb | `mov rax,[rax]` | rax read | — |
| 1474 | 0x666c8be | `mov rcx,rsi` | — | — |
| 1475 | 0x666c8c1 | `call qword ptr [0xF99FFA0]` | call | — |
| 1476 | 0x666c8c7 | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 1477 | 0x666c8cb | `jne 0x666CF35` | branch exit | — |
| 1478 | 0x666c8d1 | `mov rax,[rsi]` | rsi read | — |
| 1479 | 0x666c8d4 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1480 | 0x666c8d8 | `mov rcx,rsi` | — | — |
| 1481 | 0x666c8db | `call qword ptr [0xF99FFA0]` | call | — |
| 1482 | 0x666c8e1 | `jmp 0x666CF35` | branch exit | — |
| 1484 | 0x666c8e6 | `mov rax,[rax]` | rax read | — |
| 1485 | 0x666c8e9 | `mov rax,[rax+0x18]` | rax+0x18 read | — |
| 1486 | 0x666c8ed | `mov rdi,[rax]` | rax read | — |
| 1487 | 0x666c8f0 | `test rdi,rdi` | — | — |
| 1488 | 0x666c8f3 | `je 0x666EEBE` | branch exit | — |
| 1489 | 0x666c8f9 | `mov eax,[0x129FA150]` | absolute read | — |
| 1490 | 0x666c8ff | `mov ecx,[0x128767C8]` | absolute read | — |
| 1491 | 0x666c905 | `mov rdx,gs:[0x58]` | gs read | — |
| 1492 | 0x666c90e | `mov rcx,[rdx+rcx*8]` | rdx+rcx*8 read | — |
| 1493 | 0x666c912 | `cmp eax,[rcx+4]` | rcx+4 read | — |
| 1494 | 0x666c918 | `jg 0x6670E44` | branch exit | — |
| 1495 | 0x666c91e | `mov eax,[0x129FA160]` | absolute read | — |
| 1496 | 0x666c924 | `mov ecx,[0x128767C8]` | absolute read | — |
| 1497 | 0x666c92a | `mov rdx,gs:[0x58]` | gs read | — |
| 1498 | 0x666c933 | `mov rcx,[rdx+rcx*8]` | rdx+rcx*8 read | — |
| 1499 | 0x666c937 | `cmp eax,[rcx+4]` | rcx+4 read | — |
| 1500 | 0x666c93d | `jg 0x6670EB6` | branch exit | — |
| 1501 | 0x666c943 | `mov eax,[0x129FA170]` | absolute read | — |
| 1502 | 0x666c949 | `mov ecx,[0x128767C8]` | absolute read | — |
| 1503 | 0x666c94f | `mov rdx,gs:[0x58]` | gs read | — |
| 1504 | 0x666c958 | `mov rcx,[rdx+rcx*8]` | rdx+rcx*8 read | — |
| 1505 | 0x666c95c | `cmp eax,[rcx+4]` | rcx+4 read | — |
| 1507 | 0x666c968 | `mov [rbp+0x668],r15` | save description base r15 to stack | — |
| 1508 | 0x666c96f | `mov edi,[r15+0x84]` | r15+0x84 = desc+0x84 | 4 | edi | [V] |
| 1509 | 0x666c976 | `mov r15,[r12]` | r15 = r12 (r15 NO LONGER holds description base!) | [V] |
| 1510 | 0x666c97a | `mov rax,[rbp+0x5C0]` | stack read | — |
| 1511 | 0x666c981 | `xorps xmm0,xmm0` | — | — |
| 1512 | 0x666c984 | `movaps [rbp+0x3F0],xmm0` | — | — | — |
| 1513 | 0x666c98b | `mov rcx,[rax+8]` | rax+0x8 read | — |
| 1514 | 0x666c98f | `test rcx,rcx` | — | — |
| 1515 | 0x666c992 | `mov [rbp+0x648],rbx` | — | — | — |
| 1516 | 0x666c999 | `je 0x666D254` | branch exit | — |
| 1517 | 0x666c99f | `lock inc dword ptr [rcx+8]` | rcx+0x8 read/write | — |
| 1518 | 0x666c9a3 | `mov rsi,[rbp+0x3F8]` | stack read | — |
| 1519 | 0x666c9aa | `movups xmm0,[rax]` | rax read | — |
| 1520 | 0x666c9ad | `movaps [rbp+0x3F0],xmm0` | — | — | — |
| 1521 | 0x666c9b4 | `test rsi,rsi` | — | — |
| 1522 | 0x666c9b7 | `je 0x666D269` | branch exit | — |
| 1523 | 0x666c9bd | `lock dec dword ptr [rsi+8]` | rsi+0x8 read/write | — |
| 1524 | 0x666c9c1 | `jne 0x666D269` | branch exit | — |
| 1525 | 0x666c9c7 | `mov rax,[rsi]` | rsi read | — |
| 1526 | 0x666c9ca | `mov rax,[rax]` | rax read | — |
| 1527 | 0x666c9cd | `mov rcx,rsi` | — | — |
| 1528 | 0x666c9d0 | `call qword ptr [0xF99FFA0]` | call | — |
| 1529 | 0x666c9d6 | `lock dec dword ptr [rsi+0xC]` | rsi+0xC read/write | — |
| 1530 | 0x666c9da | `jne 0x666D269` | branch exit | — |
| 1531 | 0x666c9e0 | `mov rax,[rsi]` | rsi read | — |
| 1532 | 0x666c9e3 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1533 | 0x666c9e7 | `mov rcx,rsi` | — | — |
| 1534 | 0x666c9ea | `call qword ptr [0xF99FFA0]` | call | — |
| 1535 | 0x666c9f0 | `jmp 0x666D269` | branch exit | — |
| 1537 | 0x666c9f5 | `mov rcx,[0x1233E1A8]` | absolute read | — |
| 1538 | 0x666c9fc | `mov rax,[rcx]` | rcx read | — |
| 1539 | 0x666c9ff | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1540 | 0x666ca03 | `mov rdx,r15` | r15 read (= r12 now, not description) | — |
| 1541 | 0x666ca06 | `call qword ptr [0xF99FFA0]` | call | — |
| 1543 | 0x666ca0c | `nop` | — | — |
| 1544 | 0x666ca0d | `mov r14,rax` | — | — |
| 1545 | 0x666ca10 | `test rax,rax` | — | — |
| 1546 | 0x666ca13 | `jne short 0x666CA21` | branch | — |
| 1547 | 0x666ca15 | `mov rcx,r15` | r15 read (= r12) | — |
| 1548 | 0x666ca18 | `call 0x9BC830` | call 0x9BC830 | — |
| 1550 | 0x666ca1e | `xor r14d,r14d` | — | — |
| 1551 | 0x666ca21 | `mov [r14+rbx],r13b` | — | — | — |
| 1552 | 0x666ca25 | `movups [r14+rbx+4],xmm6` | — | — | — |
| 1553 | 0x666ca2b | `cmp rdi,[rsi+0x338]` | rsi+0x338 read | — |
| 1554 | 0x666ca32 | `je short 0x666CA62` | branch | — |
| 1555 | 0x666ca34 | `add rbx,r14` | — | — |
| 1556 | 0x666ca37 | `add rbx,0x14` | — | — |
| 1557 | 0x666ca3b | `mov rdx,[rsi+0x330]` | rsi+0x330 read | — |
| 1558 | 0x666ca42 | `mov r8,rdi` | — | — |
| 1559 | 0x666ca45 | `sub r8,rdx` | — | — |
| 1560 | 0x666ca48 | `mov rcx,r14` | — | — |
| 1561 | 0x666ca4b | `call 0xEEC6DE0` | call 0xEEC6DE0 | — |
| 1562 | 0x666ca50 | `mov r8,[rsi+0x338]` | rsi+0x338 read | — |
| 1563 | 0x666ca57 | `sub r8,rdi` | — | — |
| 1564 | 0x666ca5a | `mov rcx,rbx` | — | — |
| 1565 | 0x666ca5d | `mov rdx,rdi` | — | — |
| 1566 | 0x666ca60 | `jmp short 0x666CA72` | branch | — |
| 1567 | 0x666ca62 | `mov rdx,[rsi+0x330]` | rsi+0x330 read | — |
| 1569 | 0x666ca6c | `mov rcx,r14` | — | — |
| 1570 | 0x666ca6f | `mov r8,rdi` | — | — |
| 1571 | 0x666ca72 | `call 0xEEC6DE0` | call 0xEEC6DE0 | — |
| 1572 | 0x666ca77 | `mov rcx,[rsi+0x330]` | rsi+0x330 read | — |
| 1573 | 0x666ca7e | `test rcx,rcx` | — | — |
| 1574 | 0x666ca81 | `je short 0x666CAB7` | branch | — |
| 1575 | 0x666ca83 | `mov rdx,[rsi+0x340]` | rsi+0x340 read | — |
| 1576 | 0x666ca8a | `sub rdx,rcx` | — | — |
| 1577 | 0x666ca8d | `cmp rdx,0x1000` | — | — |
| 1578 | 0x666ca94 | `jb short 0x666CAB2` | branch | — |
| 1579 | 0x666ca96 | `mov rax,[rcx-8]` | rcx-0x8 read | — |
| 1580 | 0x666ca9a | `add rcx,0xFFFFFFFFFFFFFFF8` | — | — |
| 1581 | 0x666ca9e | `sub rcx,rax` | — | — |
| 1582 | 0x666caa1 | `cmp rcx,0x20` | — | — |
| 1583 | 0x666caa5 | `jae 0x6670A7A` | branch exit | — |
| 1584 | 0x666caab | `add rdx,0x27` | — | — |
| 1585 | 0x666caaf | `mov rcx,rax` | — | — |
| 1586 | 0x666cab2 | `call 0xE935700` | call 0xE935700 | — |
| 1587 | 0x666cab7 | `mov [rsi+0x330],r14` | rsi+0x330 write | — |
| 1588 | 0x666cabe | `mov rax,[rbp+0x648]` | stack read | — |
| 1589 | 0x666cac5 | `lea rax,[rax+rax*4]` | — | — |
| 1590 | 0x666cac9 | `lea rax,[r14+rax*4]` | — | — |
| 1591 | 0x666cacd | `mov [rsi+0x338],rax` | rsi+0x338 write | — |
| 1592 | 0x666cad4 | `lea rax,[r12+r12*4]` | — | — |
| 1593 | 0x666cad8 | `lea rax,[r14+rax*4]` | — | — |
| 1594 | 0x666cadc | `mov [rsi+0x340],rax` | rsi+0x340 write | — |
| 1595 | 0x666cae3 | `movzx r8d,byte ptr [rbp+0x670]` | stack read | — |
| 1596 | 0x666caeb | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1597 | 0x666caf2 | `mov rax,[rcx]` | rcx read | — |
| 1598 | 0x666caf5 | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1599 | 0x666caf9 | `mov edx,r8d` | — | — |
| 1600 | 0x666cafc | `call qword ptr [0xF99FFA0]` | call | — |
| 1602 | 0x666cb02 | `nop` | — | — |
| 1603 | 0x666cb03 | `mov rax,0x400000000000000` | — | — |
| 1604 | 0x666cb0d | `mov [rbp+0x3F0],rax` | — | — | — |
| 1605 | 0x666cb14 | `mov eax,[rsi+0x338]` | rsi+0x338 read | — |
| 1606 | 0x666cb1a | `sub eax,[rsi+0x330]` | rsi+0x330 read | — |
| 1607 | 0x666cb20 | `shr eax,2` | — | — |
| 1608 | 0x666cb23 | `imul eax,0xFFFFCCCD` | — | — |
| 1609 | 0x666cb29 | `dec eax` | — | — |
| 1610 | 0x666cb2b | `mov [rbp+0x474],ax` | — | — | — |
| 1611 | 0x666cb32 | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1612 | 0x666cb39 | `mov rax,[rcx]` | rcx read | — |
| 1613 | 0x666cb3c | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1614 | 0x666cb40 | `mov dl,0x4A` | — | — |
| 1615 | 0x666cb42 | `call qword ptr [0xF99FFA0]` | call | — |
| 1617 | 0x666cb48 | `mov [rbp+0x670],al` | — | — | — |
| 1618 | 0x666cb4e | `mov rax,[rsi+8]` | rsi+8 read | — |
| 1619 | 0x666cb52 | `cmp rax,[rsi+0x10]` | rsi+0x10 read | — |
| 1620 | 0x666cb56 | `je short 0x666CB77` | branch | — |
| 1621 | 0x666cb58 | `lea rdx,[rbp+0x3F0]` | — | — |
| 1622 | 0x666cb5f | `mov r8d,0xC8` | — | — |
| 1623 | 0x666cb65 | `mov rcx,rax` | — | — |
| 1624 | 0x666cb68 | `call 0xEEC6EC0` | call 0xEEC6EC0 | — |
| 1625 | 0x666cb6d | `add qword ptr [rsi+8],0xC8` | rsi+8 read/write | — |
| 1626 | 0x666cb75 | `jmp short 0x666CB8A` | branch | — |
| 1628 | 0x666cb77 | `lea r8,[rbp+0x3F0]` | — | — |
| 1629 | 0x666cb7e | `mov rcx,rsi` | — | — |
| 1631 | 0x666cb84 | `call 0x5ABA6D0` | call 0x5ABA6D0 | — |
| 1633 | 0x666cb89 | `nop` | — | — |
| 1634 | 0x666cb8a | `mov rcx,[0x1233E1B0]` | absolute read | — |
| 1635 | 0x666cb91 | `mov rax,[rcx]` | rcx read | — |
| 1636 | 0x666cb94 | `mov rax,[rax+0x10]` | rax+0x10 read | — |
| 1637 | 0x666cb98 | `movzx edx,byte ptr [rbp+0x670]` | stack read | — |
| 1638 | 0x666cb9f | `call qword ptr [0xF99FFA0]` | call | — |
| 1640 | 0x666cba5 | `nop` | — | — |
| 1641 | 0x666cba6 | `jmp 0x6670032` | branch exit | — |
| 1643 | 0x666cbab | `mov rcx,[0x1233E1A8]` | absolute read | — |
| 1644 | 0x666cbb2 | `mov rax,[rcx]` | rcx read | — |
| 1645 | 0x666cbb5 | `mov rax,[rax+8]` | rax+0x8 read | — |
| 1646 | 0x666cbb9 | `mov rdx,r12` | r12 read | — |
| 1647 | 0x666cbbc | `call qword ptr [0xF99FFA0]` | call | — |
| 1649 | 0x666cbc2 | `nop` | — | — |
| 1650 | 0x666cbc3 | `mov r14,rax` | — | — |
| 1651 | 0x666cbc6 | `test rax,rax` | — | — |
| 1652 | 0x666cbc9 | `jne short 0x666CBD7` | branch | — |
| 1653 | 0x666cbcb | `mov rcx,r12` | — | — |
| 1654 | 0x666cbce | `call 0x9BC830` | call 0x9BC830 | — |
| 1656 | 0x666cbd3 | `nop` | — | — |
| 1657 | 0x666cbd4 | `xor r14d,r14d` | — | — |
| 1658 | 0x666cbd7 | `lea rax,[r14+r13]` | — | — |
| 1659 | 0x666cbdb | `xorps xmm0,xmm0` | — | — |
| 1660 | 0x666cbde | `movups [r14+r13],xmm0` | — | — | — |
| 1661 | 0x666cbe3 | `mov rcx,[rbx+8]` | rbx+8 read | — |
| 1662 | 0x666cbe7 | `test rcx,rcx` | — | — |
| 1663 | 0x666cbea | `je short 0x666CBF0` | branch | — |
| 1664 | 0x666cbec | `lock inc dword ptr [rcx+8]` | rcx+0x8 read/write | — |
| 1665 | 0x666cbf0 | `mov rcx,[rbx]` | rbx read | — |
| 1666 | 0x666cbf3 | `mov [rax],rcx` | — | — | — |
| 1667 | 0x666cbf6 | `mov rcx,[rbx+8]` | rbx+8 read | — |
| 1668 | 0x666cbfa | `mov [rax+8],rcx` | — | — | — |
| 1669 | 0x666cbfe | `mov rcx,[rbx+0x50]` | rbx+0x50 read | — |
| 1670 | 0x666cc02 | `mov [rax+0x50],rcx` | — | — | — |
| 1671 | 0x666cc06 | `movups xmm0,[rbx+0x10]` | rbx+0x10 read | — |
| 1672 | 0x666cc0a | `movups xmm1,[rbx+0x20]` | rbx+0x20 read | — |
| 1673 | 0x666cc0e | `movups xmm2,[rbx+0x30]` | rbx+0x30 read | — |
| 1674 | 0x666cc12 | `movups xmm3,[rbx+0x40]` | rbx+0x40 read | — |
| 1675 | 0x666cc16 | `movups [rax+0x40],xmm3` | — | — | — |
| 1676 | 0x666cc1a | `movups [rax+0x30],xmm2` | — | — | — |
| 1677 | 0x666cc1e | `movups [rax+0x20],xmm1` | — | — | — |
| 1678 | 0x666cc22 | `movups [rax+0x10],xmm0` | — | — | — |
| 1679 | 0x666cc26 | `mov rdi,[rsi+0x78]` | rsi+0x78 read | — |
| 1680 | 0x666cc2a | `mov rax,[rsi+0x80]` | rsi+0x80 read | — |
| 1681 | 0x666cc31 | `cmp r15,rax` | r15 read (= r12) | — |
| 1682 | 0x666cc34 | `je 0x666CD29` | branch exit | — |
| 1683 | 0x666cc3a | `cmp rdi,r15` | r15 read (= r12) | — |
| 1684 | 0x666cc3d | `je short 0x666CCAC` | branch | — |
| 1685 | 0x666cc3f | `xorps xmm0,xmm0` | — | — |
| 1686 | 0x666cc42 | `mov rax,r14` | — | — |
| 1687 | 0x666cc45 | `jmp short 0x666CC93` | branch | — |
| 1689 | 0x666cc47 | `nop [rax+rax]` | — | — | — |
| 1691 | 0x666cc53 | `mov [rax],rcx` | — | — | — |
| 1692 | 0x666cc56 | `mov rcx,[rdi+8]` | rdi+8 read | — |
| 1693 | 0x666cc5a | `mov [rax+8],rcx` | — | — | — |
| 1694 | 0x666cc5e | `movups xmm1,[rdi+0x10]` | rdi+0x10 read | — |
| 1695 | 0x666cc62 | `movups xmm2,[rdi+0x20]` | rdi+0x20 read | — |
| 1696 | 0x666cc66 | `movups xmm3,[rdi+0x30]` | rdi+0x30 read | — |
| 1697 | 0x666cc6a | `movups xmm4,[rdi+0x40]` | rdi+0x40 read | — |
| 1698 | 0x666cc6e | `movups [rax+0x10],xmm1` | — | — | — |
| 1699 | 0x666cc72 | `movups [rax+0x20],xmm2` | — | — | — |
| 1700 | 0x666cc76 | `movups [rax+0x30],xmm3` | — | — | — |

Description register check: r15 = r12 (not description base). Description base saved at [rbp+0x668] (line 1507). No description field reads in this block (only rdi, rax).

## END OF RANGE (line 1700)

## Summary of description (r15) field reads in lines 475..1700
| Line | RVA | Instruction | Reg+offset | Size | Dest | Tag | Notes |
|------|-----|-------------|------------|------|------|-----|-------|
| 521 | 0x666b6cf | `mov rax,[r15+0x10]` | r15+0x10 | 8 | rax | [V] | desc[0x10] |
| 522 | 0x666b6d3 | `mov r14,[r15+0x18]` | r15+0x18 | 8 | r14 | [V] | r14 = desc+0x18 |
| 613 | 0x666b858 | `lea r8,[r14+8]` | r14+8 = desc+0x20 | — | r8 | [V][I] | r14=desc+0x18 |
| 626 | 0x666b891 | `movss xmm0,[r14+0x20]` | r14+0x20 = desc+0x38 | 4 | xmm0 | [V][I] | |
| 627 | 0x666b897 | `movsd xmm1,[r14+0x18]` | r14+0x18 = desc+0x30 | 8 | xmm1 | [V][I] | |
| 664 | 0x666b942 | `mov rsi,[r14]` | r14+0x00 = desc+0x18 | 8 | rsi | [V][I] | |
| 665 | 0x666b945 | `mov rax,[rsi+0x60]` | desc+0x18+0x60=desc+0x78 | 8 | rax | [V][I] | |
| 666 | 0x666b949 | `sub rax,[rsi+0x58]` | desc+0x18+0x58=desc+0x70 | 8 | rax | [V][I] | |
| 684 | 0x666b987 | `cmp byte ptr [rsi+0x1D4],0` | desc+0x18+0x1D4=desc+0x1EC | 1 | — | [V][I] | |
| 686 | 0x666b990 | `mov edi,[rsi+0x1D0]` | desc+0x18+0x1D0=desc+0x1E8 | 4 | edi | [V][I] | |
| 691 | 0x666b9b2 | `mov rax,[r15+8]` | r15+8 = desc+0x8 | 8 | rax | [V] | |
| 696 | 0x666b9c6 | `movups xmm0,[r15]` | r15+0x00 = desc+0x00 | 16 | xmm0 | [V] | |
| 714 | 0x666ba10 | `mov rax,[r15]` | r15+0x00 = desc+0x00 | 8 | rax | [V] | |
| 717 | 0x666ba25 | `movups xmm0,[r14+0x24]` | desc+0x18+0x24=desc+0x3C | 16 | xmm0 | [V][I] | |
| 729 | 0x666ba76 | `mov rax,[r14]` | desc+0x18 | 8 | rax | [V][I] | |
| 731 | 0x666ba7d | `mov rcx,[rax+0x1B0]` | (rax=desc+0x18)+0x1B0=desc+0x1C8 | 8 | rcx | [V][I] | |
| 734 | 0x666ba89 | `movzx ecx,word ptr [rcx+0x10]` | desc+0x1C8+0x10=desc+0x1D8 | 2 | ecx | [V][I] | |
| 735 | 0x666ba8d | `mov rcx,[rax+0x1B8]` | desc+0x18+0x1B8=desc+0x1D0 | 8 | rcx | [V][I] | |
| 739 | 0x666ba9d | `mov rcx,[rax+0x1B8]` | desc+0x18+0x1B8=desc+0x1D0 | 8 | rcx | [V][I] | dup of 735 |
| 743 | 0x666bab2 | `mov rax,[rax+0x1B0]` | desc+0x18+0x1B0=desc+0x1C8 | 8 | rax | [V][I] | dup of 731 |
| 1508 | 0x666c96f | `mov edi,[r15+0x84]` | r15+0x84 = desc+0x84 | 4 | edi | [V] | before r15 reassigned at 1509 |

Registers holding description pointer:
- r15 = description base (lines 475-1107, 1184-1508); reassigned to r14 value at 1108 then restored at 1184; reassigned to r12 at 1509.
- r14 = desc+0x18 (line 522) until line 1098/1104/1187.

Open: r14 typo at line 627 summary to fix; block ends at line 1700 mid-instruction-sequence (next line would be 1701 `movups [rax+0x40],xmm4`).


## Block 1 — lines 475..535 (RVA 0x666b5cf .. 0x666b704)

Field reads of description:
| Line | RVA | Instruction | Reg+offset | Size | Dest | Tag |
|------|-----|-------------|------------|------|------|-----|
| 521 | 0x666b6cf | `mov rax,[r15+0x10]` | r15+0x10 | 8 | rax | [V] |
| 522 | 0x666b6d3 | `mov r14,[r15+0x18]` | r15+0x18 | 8 | r14 | [V] |

Branches / exits / calls:
| Line | RVA | Instruction | Target / kind | Tag |
|------|-----|-------------|---------------|-----|
| 475 | 0x666b5cf | `mov qword ptr [rbp+0x3F8],0` | (store to stack) | — |
| 476 | 0x666b5da | `mov qword ptr [rbp+0x400],0xA` | (store to stack) | — |
| 477 | 0x666b5e5 | `mov qword ptr [rbp+0x408],0xF` | (store to stack) | — |
| 478 | 0x666b5f0 | `mov rax,[0xF7C86B5]` | (read absolute) | — |
| 479 | 0x666b5f7 | `mov [rbp+0x3F0],rax` | (store to stack) | — |
| 480 | 0x666b5fe | `movzx eax,word ptr [0xF7C86BD]` | (read absolute) | — |
| 481 | 0x666b605 | `mov [rbp+0x3F8],ax` | (store to stack) | — |
| 482 | 0x666b60c | `lea rcx,[rdi+0x98]` | rdi+0x98 (addr gen) | — |
| 483 | 0x666b613 | `lea rdx,[rbp+0x3F0]` | (addr gen) | — |
| 484 | 0x666b61a | `call 0x358C40` | call 0x358C40 | — |
| 485 | 0x666b61f | `mov sil,1` | — | — |
| 486 | 0x666b622 | `cmp rax,[rdi+0x98]` | rdi+0x98 read | — |
| 487 | 0x666b629 | `jne 0x666D8A2` | branch exit | — |
| 488 | 0x666b62f | `mov rdi,rbx` | — | — |
| 489 | 0x666b632 | `mov rax,[r12]` | r12 read | — |
| 490 | 0x666b636 | `lea rcx,[rax+0x10]` | rax+0x10 (addr gen) | — |
| 491 | 0x666b63a | `test rax,rax` | — | — |
| 492 | 0x666b63d | `lea rsi,[0x1232E708]` | (lea absolute) | — |
| 493 | 0x666b644 | `cmovne rsi,rcx` | — | — |
| 494 | 0x666b648 | `mov rbx,[rsi+0x18]` | rsi+0x18 read | — |
| 495 | 0x666b64c | `cmp rbx,0x17` | — | — |
| 496 | 0x666b650 | `jae 0x666CF0C` | branch exit | — |
| 497 | 0x666b656 | `xor esi,esi` | — | — |
| 498 | 0x666b658 | `jmp 0x666D89F` | branch exit | — |
| 521-525 | 0x666b6cf-0x666b6de | `mov rax,[r15+0x10] / mov r14,[r15+0x18] / shl rax,6 / add rax,r14 / mov [rbp+0x660],rax` | range end = desc[0x10]<<6 + desc[0x18] | [V] |
| 533 | 0x666b704 | `cmp r14,[rbp+0x660]` | r14 vs desc-derived end | — |
| 534 | 0x666b70b | `je 0x666C846` | branch exit | — |

Description register check: r15 holds description at this point (set line 20, still valid). r14 = desc+0x18 (line 522).
