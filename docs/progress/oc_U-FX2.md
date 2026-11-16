# Unit U-FX2 — FullscreenEffect visitor (0x666aca0) — exact listing interpretation

Source listing: docs/data/listings/effect_visitor_666aca0_667191c.txt
Range interpreted: lines 1700..2950 (RVA 0x666ccf2 .. ~0x666e473)
Visitor head context: 0x666ae72 `mov rax,[r15+0x78]`; call 0x66B2B30; body entry 0x666B5CF (listing line 476).

## Register determination (from lines 1..700) [V]
- Line 20: `mov r15,[r8]` → r15 = effect instance object.
- Line 105: `mov rax,[r15+0x78]` → rax = description pointer D = [r15+0x78] (description base).
- Line 111: `lea r12,[r15+0x78]` → r12 = &D (address of description-pointer field); passed as rdx to call 0x66B2B30 (line 116).
- Line 117: `mov rax,[r15+0x78]` → rax = D again.
- Line 120: `mov rdi,[rax+0x40]` → rdi = D+0x40 (a field OF the description), confirming rax = D.
- Line 121: `jmp 0x666B5CF` → body entry.
- Body: rsi = D = [r15+0x78] (description base) — evidenced by rsi+0x78/0x80/0x88 field accesses from line 1747 and explicit reload `mov rsi,[r15+0x78]` at line 2124.

## Description base register in body: rsi (D = [r15+0x78]); rax = D on entry.
## r15 = effect instance (NOT description). r12 = &D field.
## Tags: [V] = seen in disassembly (cite RVA); [I] = inferred.

## Block 1: listing lines 1701..1765 (RVA 0x666ccf2 .. 0x666cdc0)

Description-field reads (base rsi = description base D):
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 1747 | 0x666cd95 | `mov rdi,[rsi+0x78]` | rsi+0x78 | 8B | rdi |
| 1750 | 0x666cda2 | `mov r13,[rsi+0x80]` | rsi+0x80 | 8B | r13 |

Description-traversal reads via rdi (rdi = [rsi+0x78] = desc field 0x78 → sub-object) [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 1723 | 0x666cd40 | `mov rcx,[rdi]` | [rdi] | 8B | rcx |
| 1725 | 0x666cd46 | `mov rcx,[rdi+8]` | rdi+8 | 8B | rcx |
| 1727 | 0x666cd4e | `movups xmm1,[rdi+0x10]` | rdi+0x10 | 16B | xmm1 |
| 1728 | 0x666cd52 | `movups xmm2,[rdi+0x20]` | rdi+0x20 | 16B | xmm2 |
| 1729 | 0x666cd56 | `movups xmm3,[rdi+0x30]` | rdi+0x30 | 16B | xmm3 |
| 1730 | 0x666cd5a | `movups xmm4,[rdi+0x40]` | rdi+0x40 | 16B | xmm4 |
| 1735 | 0x666cd6e | `mov rcx,[rdi+0x50]` | rdi+0x50 | 8B | rcx |
| 1742 | 0x666cd86 | `mov rcx,[rdi+8]` | rdi+8 | 8B | rcx |
| 1757 | 0x666cdb9 | `mov r15,[rdi+8]` | rdi+8 | 8B | r15 |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 1710 | 0x666cd15 | `je short 0x666CD95` | 0x666CD95 | branch exit |
| 1714 | 0x666cd21 | `je short 0x666CCD0` | 0x666CCD0 | branch |
| 1716 | 0x666cd27 | `jmp short 0x666CCD0` | 0x666CCD0 | branch |
| 1718 | 0x666cd2c | `je short 0x666CD99` | 0x666CD99 | branch exit |
| 1721 | 0x666cd34 | `jmp short 0x666CD83` | 0x666CD83 | branch |
| 1740 | 0x666cd81 | `je short 0x666CD95` | 0x666CD95 | branch exit |
| 1744 | 0x666cd8d | `je short 0x666CD40` | 0x666CD40 | branch |
| 1746 | 0x666cd93 | `jmp short 0x666CD40` | 0x666CD40 | branch |
| 1749 | 0x666cd9c | `je 0x666CE2C` | 0x666CE2C | branch exit |
| 1752 | 0x666cdac | `jne short 0x666CDB9` | 0x666CDB9 | branch |
| 1753 | 0x666cdae | `jmp short 0x666CDF5` | 0x666CDF5 | branch |
| 1756 | 0x666cdb7 | `je short 0x666CDF1` | 0x666CDF1 | branch |
| 1759 | 0x666cdc0 | `je short 0x666CDB0` | 0x666CDB0 | branch |

Calls in block 1: none.
Block note: remaining lines are writes to copy buffer [rcx+..], pointer arithmetic (add r15/rcx/rdi/rax 0x58), compares, and a lock-inc refcount — none are description-field reads.

## Block 2: listing lines 1761..1825 (RVA 0x666cdc0 .. 0x666cee5)

Description-field reads (base rsi = description base D):
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 1773 | 0x666cdf1 | `mov rdi,[rsi+0x78]` | rsi+0x78 | 8B | rdi |
| 1774 | 0x666cdf5 | `mov rdx,[rsi+0x88]` | rsi+0x88 | 8B | rdx |
| 1802 | 0x666ce78 | `mov eax,[rsi+0x80]` | rsi+0x80 | 4B | eax |
| 1803 | 0x666ce7e | `sub eax,[rsi+0x78]` | rsi+0x78 | 4B | eax |
| 1814 | 0x666ceaf | `mov rax,[rsi+8]` | rsi+8 | 8B | rax |
| 1815 | 0x666ceb3 | `cmp rax,[rsi+0x10]` | rsi+0x10 | 8B | flags |

Description-traversal reads via rdi (rdi = [rsi+0x78] → sub-object) [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 1762 | 0x666cdc9 | `mov rax,[r15]` | [r15] (r15 = rdi+8 sub-obj ref) | 8B | rax |
| 1763 | 0x666cdcc | `mov rax,[rax]` | [rax] | 8B | rax |
| 1768 | 0x666cddf | `mov rax,[r15]` | [r15] | 8B | rax |
| 1769 | 0x666cde2 | `mov rax,[rax+8]` | rax+8 | 8B | rax |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 1761 | 0x666cddd | `jne short 0x666CDB0` | 0x666CDB0 | branch |
| 1765 | 0x666cdd2 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 1767 | 0x666cddd | `jne short 0x666CDB0` | 0x666CDB0 | branch |
| 1772 | 0x666cdef | `jmp short 0x666CDB0` | 0x666CDB0 | branch |
| 1777 | 0x666ce06 | `jb short 0x666CE24` | 0x666CE24 | branch |
| 1782 | 0x666ce17 | `jae 0x6670A7A` | 0x6670A7A | branch exit |
| 1786 | 0x666ce27 | `call 0xE935700` | 0xE935700 | call |
| 1799 | 0x666ce6a | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 1812 | 0x666cea3 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 1816 | 0x666ceb7 | `je short 0x666CED8` | 0x666CED8 | branch |
| 1820 | 0x666cec9 | `call 0xEEC6EC0` | 0xEEC6EC0 | call |
| 1822 | 0x666ced6 | `jmp short 0x666CEEB` | 0x666CEEB | branch |
| 1826 | 0x666cee5 | `call 0x5ABA6D0` | 0x5ABA6D0 | call |

Block note: lines 1787-1792 write rsi+0x78/rsi+0x80/rsi+0x88 (description fields, writes not reads); line 1788 reads [rbp+0x648] (not description); remaining lines are arithmetic/writes — none are additional description-field reads.

## Block 3: listing lines 1827..1890 (RVA 0x666ceeb .. 0x666d025)

Description-field reads (base rsi = description base D):
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 1835 | 0x666cf0c | `cmp qword ptr [rsi+0x20],0x10` | rsi+0x20 | 8B | flags |
| 1837 | 0x666cf17 | `mov rsi,[rsi+8]` | rsi+8 | 8B | rsi |

[I] CLOBBER: line 1837 overwrites rsi (=description base) with [rsi+8]; rsi is NOT the description base after line 1837. Line 1853 clobbers rsi again (`mov rsi,[rbp+0x3F8]`) → rsi = refcounted object, not description.

Description-traversal / other reads (not description base rsi) [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest | Note |
|------|-----|----------------------|------------|------|------|------|
| 1843 | 0x666cf3c | `mov rax,[rax+0x18]` | rax+0x18 | 8B | rax | rax = [rbp+0x3F0] chain |
| 1847 | 0x666cf51 | `mov r8,[r14]` | [r14] | 8B | r8 | r14 = copy-dest buffer |
| 1848 | 0x666cf54 | `mov rdx,[rax+0x170]` | rax+0x170 | 8B | rdx | |
| 1869 | 0x666cfa8 | `mov r9,[r15]` | [r15] | 8B | r9 | r15 = sub-object |
| 1881 | 0x666cfe1 | `movss xmm0,[r15+8]` | r15+8 | 4B | xmm0 | r15 = sub-object |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 1832 | 0x666cef5 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 1834 | 0x666cf07 | `jmp 0x6670032` | 0x6670032 | branch exit |
| 1836 | 0x666cf11 | `jb 0x666D86C` | 0x666D86C | branch |
| 1838 | 0x666cf1b | `jmp 0x666D870` | 0x666D870 | branch |
| 1850 | 0x666cf5e | `call 0xE86B370` | 0xE86B370 | call |
| 1855 | 0x666cf75 | `je short 0x666CFA2` | 0x666CFA2 | branch |
| 1857 | 0x666cf7b | `jne short 0x666CFA2` | 0x666CFA2 | branch |
| 1863 | 0x666cf90 | `jne short 0x666CFA2` | 0x666CFA2 | branch |
| 1868 | 0x666cfa2 | `jmp short 0x666CFA2` | 0x666CFA2 | branch |
| 1873 | 0x666cfb6 | `call 0xBBD7F70` | 0xBBD7F70 | call |
| 1880 | 0x666cfdb | `jg 0x6670FE9` | 0x6670FE9 | branch exit |

Block note: lines 1840,1841,1845,1852,1882-1886 are writes; lines 1842,1844,1858-1867 read rax/rsi chain objects (rsi here is refcounted object, not description base); remaining lines are arithmetic/global reads — none are additional description-base field reads.

## Block 4: listing lines 1891..1955 (RVA 0x666d028 .. 0x666d0f6)

Description-field reads (base rsi = description base D): NONE — rsi was clobbered at line 1837 (`mov rsi,[rsi+8]`) and line 1853 (`mov rsi,[rbp+0x3F8]`), so rsi is not the description base in this block. Reads here are r15 sub-object fields + rbp locals + globals, not description fields.

Description-traversal reads via r15 (r15 = sub-object) [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 1919 | 0x666d090 | `movups xmm0,[r15+0xC]` | r15+0xC | 16B | xmm0 |
| 1921 | 0x666d09c | `movups xmm1,[r15+0x1C]` | r15+0x1C | 16B | xmm1 |
| 1923 | 0x666d0a8 | `movups xmm2,[r15+0x2C]` | r15+0x2C | 16B | xmm2 |
| 1925 | 0x666d0b4 | `movups xmm3,[r15+0x3C]` | r15+0x3C | 16B | xmm3 |
| 1928 | 0x666d0c7 | `movzx eax,word ptr [r15+0x4C]` | r15+0x4C | 2B | eax |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 1893 | 0x666d02b | `je short 0x666D055` | 0x666D055 | branch |
| 1900 | 0x666d047 | `je short 0x666D055` | 0x666D055 | branch |
| 1903 | 0x666d051 | `jne short 0x666D040` | 0x666D040 | branch |
| 1904 | 0x666d053 | `jmp short 0x666D083` | 0x666D083 | branch |
| 1907 | 0x666d05b | `jae short 0x666D083` | 0x666D083 | branch |
| 1915 | 0x666d07d | `call 0x5679DB0` | 0x5679DB0 | call |
| 1918 | 0x666d08a | `jne 0x666FB78` | 0x666FB78 | branch exit |

Block note: lines 1898-1899 read [rcx]/[r10+0x28] in a local lookup loop (rcx = rbp-local, not description base); lines 1929-1932, 1944-1955 are stack (rbp) reads/writes; remaining lines are writes/arithmetic — none are description-base field reads.

## Block 5: listing lines 1956..2020 (RVA 0x666d0f9 .. 0x666d2e2)

Description-field reads (base rsi = description base D): NONE — rsi holds a refcounted object (clobbered at line 1853), not the description base. Reads here are rbp locals, r15 sub-object, rbp+0x668 (=effect instance, stored at line 527), globals — none are description-base field reads.

Other reads [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest | Note |
|------|-----|----------------------|------------|------|------|------|
| 1956 | 0x666d19b | `mov rax,[rbp+0x1D0]` | [rbp+0x1D0] | 8B | rax | stack local |
| 1963 | 0x666d1bc | `mov rax,[rbp+0x250]` | [rbp+0x250] | 8B | rax | stack local |
| 1966 | 0x666d1d5 | `movaps xmm0,[rbp+0x340]` | [rbp+0x340] | 16B | xmm0 | stack local |
| 1967 | 0x666d1dc | `movaps xmm1,[rbp+0x350]` | [rbp+0x350] | 16B | xmm1 | stack local |
| 1972 | 0x666d203 | `mov rax,[rbp+0x360]` | [rbp+0x360] | 8B | rax | stack local |
| 1975 | 0x666d218 | `movzx eax,byte ptr [rbp+0x378]` | [rbp+0x378] | 1B | eax | stack local |
| 1980 | 0x666d237 | `movsxd r8,[rdx+rax*4]` | [rdx+rax*4] (global table 0xF2BF4F0) | 4B | r8 | global jump-table |
| 1983 | 0x666d241 | `mov rcx,[rbp+0x368]` | [rbp+0x368] | 8B | rcx | stack local (jump target) |
| 1994 | 0x666d27f | `mov r8,[r15]` | [r15] | 8B | r8 | r15 = sub-object |
| 1995 | 0x666d282 | `mov rdx,[rax+0x170]` | rax+0x170 | 8B | rdx | |
| 2015 | 0x666d2d0 | `mov r11,[rbp+0x668]` | [rbp+0x668] | 8B | r11 | = effect instance (r15 stored line 527) |
| 2018 | 0x666d2e2 | `mov rax,[rbp+0x48]` | [rbp+0x48] | 8B | rax | stack local |
| 2019 | 0x666d2e6 | `movzx r8d,word ptr [rbp+0x52]` | [rbp+0x52] | 2B | r8d | stack local |

Refcounted-object reads (rsi = object, NOT description base) [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 2005 | 0x666d2ab | `mov rax,[rsi]` | [rsi] | 8B | rax |
| 2006 | 0x666d2ae | `mov rax,[rax]` | [rax] | 8B | rax |
| 2011 | 0x666d2c0 | `mov rax,[rsi]` | [rsi] | 8B | rax |
| 2012 | 0x666d2c3 | `mov rax,[rax+8]` | rax+8 | 8B | rax |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 1961 | 0x666d1b6 | `call 0xE869FF0` | 0xE869FF0 | call |
| 1977 | 0x666d223 | `ja 0x666F4F3` | 0x666F4F3 | branch exit |
| 1982 | 0x666d23e | `jmp r8` | (computed) | indirect branch |
| 1985 | 0x666d24f | `jmp 0x666F4ED` | 0x666F4ED | branch |
| 2002 | 0x666d2a3 | `je short 0x666D2D0` | 0x666D2D0 | branch |
| 2004 | 0x666d2a9 | `jne short 0x666D2D0` | 0x666D2D0 | branch |
| 2008 | 0x666d2b4 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2010 | 0x666d2be | `jne short 0x666D2D0` | 0x666D2D0 | branch |
| 2014 | 0x666d2ca | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |

Block note: lines 2003, 2009 are lock-dec writes on refcounted object; remaining lines are stack writes/arithmetic — none are description-base field reads.

## Block 6: listing lines 2021..2087 (RVA 0x666d2ee .. 0x666d40c)

Description-field reads (base rsi = description base D): NONE — rsi holds a refcounted object (clobbered line 1853), not the description base. Reads here are rbp locals, r11 = effect instance ([rbp+0x668], stored line 527), globals — none are description-base field reads.

Other reads [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest | Note |
|------|-----|----------------------|------------|------|------|------|
| 2030 | 0x666d310 | `mov r10,[rcx]` | [rcx] | 8B | r10 | local lookup loop |
| 2031 | 0x666d313 | `cmp [r10+0x28],r8` | [r10+0x28] | 8B | flags | local lookup loop |
| 2050 | 0x666d36d | `mov r8,[rbp+0x670]` | [rbp+0x670] | 8B | r8 | stack local |
| 2054 | 0x666d37a | `movups xmm0,[r11+0x18]` | r11+0x18 | 16B | xmm0 | r11 = effect instance (NOT description base) |
| 2058 | 0x666d398 | `mov rax,[rbp+0x38]` | [rbp+0x38] | 8B | rax | stack local |
| 2059 | 0x666d39c | `movzx edx,word ptr [rbp+0x42]` | [rbp+0x42] | 2B | edx | stack local |
| 2068 | 0x666d3c0 | `mov r10,[rax+r8]` | [rax+r8] | 8B | r10 | local lookup loop |
| 2069 | 0x666d3c4 | `cmp [r10+0x28],r9` | [r10+0x28] | 8B | flags | local lookup loop |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2025 | 0x666d2fb | `je short 0x666D325` | 0x666D325 | branch |
| 2032 | 0x666d317 | `je short 0x666D325` | 0x666D325 | branch |
| 2035 | 0x666d321 | `jne short 0x666D310` | 0x666D310 | branch |
| 2036 | 0x666d323 | `jmp short 0x666D37A` | 0x666D37A | branch |
| 2039 | 0x666d32b | `jae short 0x666D37A` | 0x666D37A | branch |
| 2051 | 0x666d36d | `call 0xBCABA00` | 0xBCABA00 | call |
| 2064 | 0x666d3aa | `je short 0x666D3DC` | 0x666D3DC | branch |
| 2070 | 0x666d3c8 | `je short 0x666D3D9` | 0x666D3D9 | branch |
| 2073 | 0x666d3d1 | `jne short 0x666D3C0` | 0x666D3C0 | branch |
| 2075 | 0x666d3d7 | `jmp short 0x666D41F` | 0x666D41F | branch |
| 2079 | 0x666d3e3 | `jae short 0x666D41F` | 0x666D41F | branch |
| 2087 | 0x666d40c | `call 0x5679DB0` | 0x5679DB0 | call |

Block note: lines 2043-2046, 2056-2057, 2082-2083 are writes; remaining lines arithmetic/global reads — none are description-base field reads.

## Block 7: listing lines 2088..2150 (RVA 0x666d412 .. 0x666d543)

Description-field reads (base rsi = description base D):
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 2124 | 0x666d4b1 | `mov rsi,[r15+0x78]` | r15+0x78 (r15=effect instance → loads description pointer into rsi) | 8B | rsi |
| 2125 | 0x666d4b5 | `mov rax,[rsi+0x60]` | rsi+0x60 | 8B | rax |
| 2126 | 0x666d4b9 | `sub rax,[rsi+0x58]` | rsi+0x58 | 8B | rax |
| 2142 | 0x666d4fb | `mov rsi,[r15+0x78]` | r15+0x78 (re-loads description pointer into rsi) | 8B | rsi |
| 2144 | 0x666d502 | `cmp byte ptr [rsi+0x1D4],0` | rsi+0x1D4 | 1B | flags |
| 2146 | 0x666d50b | `mov r14d,[rsi+0x1D0]` | rsi+0x1D0 | 4B | r14d |

[V] rsi re-established as description base D at lines 2124 and 2142 (r15 = effect instance, [rbp+0x668] stored line 527).

Other reads [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest | Note |
|------|-----|----------------------|------------|------|------|------|
| 2089 | 0x666d412 | `mov rax,[rbp+0x38]` | [rbp+0x38] | 8B | rax | stack local |
| 2090 | 0x666d416 | `movzx edx,word ptr [rbp+0x42]` | [rbp+0x42] | 2B | edx | stack local |
| 2093 | 0x666d41f | `movaps xmm0,[0xEF40DC0]` | [0xEF40DC0] (global const) | 16B | xmm0 | global |
| 2100 | 0x666d447 | `mov rdx,[0x129FA168]` | [0x129FA168] (global) | 8B | rdx | global |
| 2104 | 0x666d460 | `mov r10,[r8]` | [r8] | 8B | r10 | local lookup loop |
| 2105 | 0x666d463 | `cmp [r10+0x28],rdx` | [r10+0x28] | 8B | flags | local lookup loop |
| 2132 | 0x666d4d0 | `add rdx,[rbp]` | [rbp] | 8B | rdx | stack local |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2099 | 0x666d445 | `je short 0x666D475` | 0x666D475 | branch |
| 2106 | 0x666d467 | `je short 0x666D475` | 0x666D475 | branch |
| 2109 | 0x666d471 | `jne short 0x666D460` | 0x666D460 | branch |
| 2110 | 0x666d473 | `jmp short 0x666D4AA` | 0x666D4AA | branch |
| 2113 | 0x666d47b | `jae short 0x666D4AA` | 0x666D4AA | branch |
| 2121 | 0x666d4a4 | `call 0x5679DB0` | 0x5679DB0 | call |
| 2130 | 0x666d4c9 | `je short 0x666D4FF` | 0x666D4FF | branch |
| 2135 | 0x666d4de | `call 0xBBD7C70` | 0xBBD7C70 | call |

Block note: lines 2094-2096, 2116-2117 are writes; lines 2147-2148 are stack writes; remaining lines arithmetic — none are additional description-base field reads (rsi not yet read as base between 2126 and 2142).

## Block 8: listing lines 2151..2174 (RVA 0x666d54a .. 0x666d5d2)

Description-field reads (base rsi = description base D):
| Line | RVA | Instruction (quoted) | Field read | Size | Dest |
|------|-----|----------------------|------------|------|------|
| 2158 | 0x666d55b | `mov rax,[rsi+0x1B0]` | rsi+0x1B0 | 8B | rax |
| 2161 | 0x666d567 | `movzx eax,word ptr [rax+0x10]` | rax+0x10 (rax=[rsi+0x1B0]) | 2B | eax |
| 2162 | 0x666d56b | `mov rax,[rsi+0x1B8]` | rsi+0x1B8 | 8B | rax |
| 2166 | 0x666d57b | `mov rax,[rsi+0x1B8]` | rsi+0x1B8 | 8B | rax |
| 2169 | 0x666d586 | `mov rcx,[rsi+0x1B0]` | rsi+0x1B0 | 8B | rcx |

[I] CLOBBER: line 2171 `mov rsi,[rbp+0x638]` overwrites rsi (=description base) with a stack value; rsi is NOT the description base after line 2171.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2160 | 0x666d565 | `je short 0x666D56B` | 0x666D56B | branch |
| 2164 | 0x666d575 | `je short 0x666D584` | 0x666D584 | branch |
| 2167 | 0x666d582 | `jmp short 0x666D586` | 0x666D586 | branch |
| 2174 | 0x666d5a2 | `je short 0x666D5D2` | 0x666D5D2 | branch |

Calls in block 8: none.

Block note: lines 2157, 2170, 2172 are stack writes; lines 2159-2163, 2165, 2168 are register/test/inc — none are additional description-base field reads.

## Block 9: listing lines 2175..2238 (RVA 0x666d5a7 .. 0x666d73d)

Description-field reads (base rsi = description base D): NONE — rsi = refcounted object ([rbp+0x638], clobbered line 2171), not the description base. Reads here are rbp locals, r15+0x80, refcounted-object [rsi] — none are description-base field reads.

Other reads [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest | Note |
|------|-----|----------------------|------------|------|------|------|
| 2177 | 0x666d5ad | `mov rax,[rsi]` | [rsi] | 8B | rax | rsi = refcounted object |
| 2178 | 0x666d5b0 | `mov rax,[rax]` | [rax] | 8B | rax | |
| 2183 | 0x666d5c2 | `mov rax,[rsi]` | [rsi] | 8B | rax | rsi = refcounted object |
| 2184 | 0x666d5c5 | `mov rax,[rax+8]` | rax+8 | 8B | rax | |
| 2187 | 0x666d5d2 | `mov rax,[rbp+0x648]` | [rbp+0x648] | 8B | rax | stack local |
| 2188 | 0x666d5d9 | `mov r8,[rax+0x3B8]` | [rax+0x3B8] | 8B | r8 | |
| 2189 | 0x666d5e0 | `mov rdx,[r12]` | [r12] | 8B | rdx | |
| 2198 | 0x666d610 | `mov si,[r15+0x80]` | r15+0x80 | 2B | si | r15 = ? (effect instance/sub-object), not description base |
| 2219 | 0x666d6be | `mov rax,[rbp]` | [rbp] | 8B | rax | stack local |
| 2225 | 0x666d6d9 | `mov rax,[rbp+0x80]` | [rbp+0x80] | 8B | rax | stack local |
| 2229 | 0x666d6f9 | `movzx eax,byte ptr [rbp+0x380]` | [rbp+0x380] | 1B | eax | stack local |
| 2235 | 0x666d70c | `movaps xmm0,[rbp+0x340]` | [rbp+0x340] | 16B | xmm0 | stack local |
| 2236 | 0x666d713 | `movaps xmm1,[rbp+0x350]` | [rbp+0x350] | 16B | xmm1 | stack local |
| 2237 | 0x666d71a | `movaps xmm2,[rbp+0x360]` | [rbp+0x360] | 16B | xmm2 | stack local |
| 2238 | 0x666d721 | `movaps xmm3,[rbp+0x370]` | [rbp+0x370] | 16B | xmm3 | stack local |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2176 | 0x666d5ab | `jne short 0x666D5D2` | 0x666D5D2 | branch |
| 2180 | 0x666d5b6 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2182 | 0x666d5c0 | `jne short 0x666D5D2` | 0x666D5D2 | branch |
| 2186 | 0x666d5cc | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2195 | 0x666d607 | `call 0x66A0F60` | 0x66A0F60 | call |
| 2223 | 0x666d6d3 | `call 0xE869FF0` | 0xE869FF0 | call |
| 2232 | 0x666d706 | `jg short 0x666D746` | 0x666D746 | branch |
| 2234 | 0x666d70a | `jne short 0x666D75B` | 0x666D75B | branch |

Block note: lines 2175, 2181 are lock-dec writes on refcounted object; lines 2190-2192, 2199-2218, 2220, 2226-2228 are stack writes; remaining lines arithmetic — none are description-base field reads.

## Block 10: listing lines 2239..2300 (RVA 0x666d728 .. 0x666d88b)

Description-field reads (base rsi = description base D): NONE — rsi = refcounted object (clobbered line 2171; line 2293 `add rsi,8` pointer arithmetic on it), not the description base. Reads here are rbp locals, globals — none are description-base field reads.

Other reads [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest | Note |
|------|-----|----------------------|------------|------|------|------|
| 2246 | 0x666d74b | `mov rcx,[rbp+0x340]` | [rbp+0x340] | 8B | rcx | stack local |
| 2249 | 0x666d75b | `mov rcx,[rbp+0x350]` | [rbp+0x350] | 8B | rcx | stack local |
| 2251 | 0x666d76d | `movaps xmm0,[rbp+0x340]` | [rbp+0x340] | 16B | xmm0 | stack local |
| 2262 | 0x666d7b5 | `movaps xmm0,[rbp+0x1D0]` | [rbp+0x1D0] | 16B | xmm0 | stack local |
| 2263 | 0x666d7bc | `movaps xmm1,[rbp+0x1E0]` | [rbp+0x1E0] | 16B | xmm1 | stack local |
| 2269 | 0x666d7e6 | `mov rax,[rbp+0x1F0]` | [rbp+0x1F0] | 8B | rax | stack local |
| 2272 | 0x666d7fb | `movzx eax,byte ptr [rbp+0x208]` | [rbp+0x208] | 1B | eax | stack local |
| 2276 | 0x666d813 | `movsxd rdx,[rcx+rax*4]` | [rcx+rax*4] (global table 0xF2BF4D0) | 4B | rdx | global jump-table |
| 2279 | 0x666d81c | `mov rcx,[rbp+0x1F8]` | [rbp+0x1F8] | 8B | rcx | stack local (jump target) |
| 2283 | 0x666d833 | `movups xmm0,[rcx]` | [rbp+0x1F8] | 16B | xmm0 | stack local |
| 2287 | 0x666d84c | `mov rcx,[rbp+0x200]` | [rbp+0x200] | 8B | rcx | stack local |
| 2291 | 0x666d860 | `mov rcx,[rbp+0x200]` | [rbp+0x200] | 8B | rcx | stack local |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2243 | 0x666d744 | `jmp short 0x666D78C` | 0x666D78C | branch |
| 2245 | 0x666d749 | `jne short 0x666D792` | 0x666D792 | branch |
| 2248 | 0x666d759 | `jmp short 0x666D78C` | 0x666D78C | branch |
| 2274 | 0x666d806 | `ja 0x666E5B2` | 0x666E5B2 | branch exit |
| 2278 | 0x666d81a | `jmp rdx` | (computed) | indirect branch |
| 2281 | 0x666d82a | `jmp 0x666E5AC` | 0x666E5AC | branch |
| 2285 | 0x666d840 | `jmp 0x666E5AC` | 0x666E5AC | branch |
| 2289 | 0x666d856 | `je 0x666E595` | 0x666E595 | branch exit |
| 2292 | 0x666d867 | `jmp 0x666E597` | 0x666E597 | branch |
| 2299 | 0x666d886 | `call 0xE93BF00` | 0xE93BF00 | call |

Block note: lines 2239-2242, 2247, 2250, 2253-2256, 2264-2268, 2270-2271 are writes; lines 2284, 2286 are writes; remaining lines arithmetic/global reads — none are description-base field reads.

## Block 11: listing lines 2301..2360 (RVA 0x666d88b .. 0x666d96c)

Description-field reads (base rsi = description base D): NONE — rsi = refcounted object (line 2293 `add rsi,8`), clobbered, not the description base. Reads here are rbp locals, r12, [rcx+0x1AD/0x1AE/0x1AF/0x1AC] where rcx=[rax+0x40] (sub-object) — none are description-base field reads.

Other reads [I]:
| Line | RVA | Instruction (quoted) | Field read | Size | Dest | Note |
|------|-----|----------------------|------------|------|------|------|
| 2307 | 0x666d8a2 | `mov rax,[rbp+0x408]` | [rbp+0x408] | 8B | rax | stack local |
| 2310 | 0x666d8af | `mov rcx,[rbp+0x3F0]` | [rbp+0x3F0] | 8B | rcx | stack local |
| 2314 | 0x666d8c3 | `mov r8,[rcx-8]` | [rcx-8] | 8B | r8 | heap header |
| 2323 | 0x666d8e7 | `mov rax,[r12]` | [r12] | 8B | rax | |
| 2326 | 0x666d8f0 | `mov rcx,[rax+0x40]` | rax+0x40 | 8B | rcx | sub-object |
| 2332 | 0x666d912 | `movzx eax,byte ptr [rcx+0x1AD]` | rcx+0x1AD | 1B | eax | sub-object field |
| 2344 | 0x666d934 | `movzx edx,byte ptr [rcx+0x1AE]` | rcx+0x1AE | 1B | edx | sub-object field |
| 2351 | 0x666d94a | `movzx edx,byte ptr [rcx+0x1AF]` | rcx+0x1AF | 1B | edx | sub-object field |
| 2358 | 0x666d962 | `movzx ecx,byte ptr [rcx+0x1AC]` | rcx+0x1AC | 1B | ecx | sub-object field |

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2309 | 0x666d8ad | `jb short 0x666D8E7` | 0x666D8E7 | branch |
| 2313 | 0x666d8c1 | `jb short 0x666D8E2` | 0x666D8E2 | branch |
| 2318 | 0x666d8d2 | `jae 0x6670A7A` | 0x6670A7A | branch exit |
| 2322 | 0x666d8e2 | `call 0xE935700` | 0xE935700 | call |
| 2325 | 0x666d8ee | `je short 0x666D8F6` | 0x666D8F6 | branch |
| 2327 | 0x666d8f4 | `jmp short 0x666D8F8` | 0x666D8F8 | branch |
| 2334 | 0x666d91b | `je short 0x666D926` | 0x666D926 | branch |
| 2336 | 0x666d920 | `jne short 0x666D930` | 0x666D930 | branch |
| 2338 | 0x666d924 | `jmp short 0x666D928` | 0x666D928 | branch |
| 2340 | 0x666d928 | `jmp short 0x666D928` | 0x666D928 | branch |
| 2342 | 0x666d932 | `jmp short 0x666D932` | 0x666D932 | branch |
| 2346 | 0x666d93c | `je short 0x666D944` | 0x666D944 | branch |
| 2348 | 0x666d940 | `jne short 0x666D94A` | 0x666D94A | branch |
| 2353 | 0x666d954 | `je short 0x666D95C` | 0x666D95C | branch |
| 2355 | 0x666d958 | `jne short 0x666D962` | 0x666D962 | branch |
| 2360 | 0x666d96c | `je short 0x666D977` | 0x666D977 | branch |

Calls in block 11: one (0xE935700). Block note: lines 2329-2331, 2341, 2350, 2357 are writes; remaining lines arithmetic — none are description-base field reads.

## Block 12: listing lines 2361..2420 (RVA 0x666D971 .. 0x666DA9F)

Description-field reads (base rsi = description base D): NONE — rsi is clobbered (line 2171) and never reloaded as D; no description-base register exists in this block. Reads here are via rbp locals, globals [0x129F92xx], r15 (=&D_slot address after line 2404, NOT description base) — none are description-base field reads.

[I] Excluded (base register not verified as description base):
- Line 2371 `mov eax,[rax+0x70]`: rax=[rbp+0x650]=&D_slot address → reads effect-instance field [r15_base+0xE8], NOT a description field.
- Line 2416-2419 `mov rax,[r12]` / `mov rax,[rax+0x40]`: r12 (=&D_slot set line 111) is not verified as still holding &D_slot here; base register r12 not verified as description base → not counted as description-field read.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2361 | 0x666d971 | `je short 0x666D97D` | 0x666D97D | branch exit |
| 2363 | 0x666d975 | `jne short 0x666D98B` | 0x666D98B | branch |
| 2366 | 0x666d97b | `jmp short 0x666D97F` | 0x666D97F | branch |
| 2378 | 0x666d9ba | `jg 0x6670D0A` | 0x6670D0A | branch exit |
| 2381 | 0x666d9cf | `jne 0x666DA92` | 0x666DA92 | branch |
| 2388 | 0x666d9fb | `jg 0x6670F9A` | 0x6670F9A | branch exit |
| 2405 | 0x666da5d | `jb short 0x666DA62` | 0x666DA62 | branch |
| 2408 | 0x666da65 | `js 0x6670FE4` | 0x6670FE4 | branch exit |
| 2410 | 0x666da6f | `ja short 0x666DAA1` | 0x666DAA1 | branch |
| 2415 | 0x666da8d | `jmp 0x666DB78` | 0x666DB78 | branch |
| 2418 | 0x666da99 | `je short 0x666DAF4` | 0x666DAF4 | branch |
| 2420 | 0x666da9f | `jmp short 0x666DAF6` | 0x666DAF6 | branch |

Calls in block 12: none.
Block note: lines 2362-2377, 2379-2386, 2389-2404, 2406-2407, 2409, 2411-2414 are compares/tests/arithmetic/locals/globals; line 2380 `mov [rbp+0x668],r15` stores effect instance; line 2480 (next block) `mov r13,[r15+0x40]` reads effect-instance field via r15=&D_slot — none are description-base field reads.

## Block 13: listing lines 2421..2480 (RVA 0x666DAA1 .. 0x666DBBA)

Description-field reads (base rsi = description base D): NONE — no description-base register exists (rsi = refcounted object / stack locals, clobbered line 2171). Reads here are rbp locals, globals, heap-header, refcounted-object [rsi] — none are description-base field reads.

[I] Excluded (base register not verified as description base): line 2450-2453 `mov rax,[r12]` / `mov rdi,[rax+0x40]` — same double-deref pattern as line 2416-2419; r12 not verified as description base at this point → not counted. Line 2480 `mov r13,[r15+0x40]`: r15=&D_slot (reloaded line 2404) → reads effect-instance field, NOT a description field.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2430 | 0x666dac4 | `jb short 0x666DB3C` | 0x666DB3C | branch |
| 2435 | 0x666dadd | `je 0x6670A2E` | 0x6670A2E | branch exit |
| 2440 | 0x666daf2 | `jmp short 0x666DB55` | 0x666DB55 | branch |
| 2449 | 0x666db20 | `je 0x666FC9E` | 0x666FC9E | branch exit |
| 2452 | 0x666db2d | `je 0x666DDD1` | 0x666DDD1 | branch |
| 2454 | 0x666db37 | `jmp 0x666DDD3` | 0x666DDD3 | branch |
| 2460 | 0x666db4f | `je 0x6671913` | 0x6671913 | branch exit |
| 2475 | 0x666dba1 | `jb short 0x666DBAC` | 0x666DBAC | branch |
| 2477 | 0x666dbb3 | `jmp short 0x666DBB3` | 0x666DBB3 | branch |

Calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2433 | 0x666dad4 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2447 | 0x666db18 | `call 0x9B020` | 0x9B020 | call |
| 2457 | 0x666db43 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2472 | 0x666db93 | `call 0x9B020` | 0x9B020 | call |
| 2473 | 0x666db73 | `call 0xEEC6EC0` | 0xEEC6EC0 | call |

Block note: lines 2421-2429, 2431-2432, 2436-2439, 2441-2446, 2448, 2451, 2455-2456, 2458-2459, 2461-2471, 2474, 2476, 2478-2479 are arithmetic/locals/alloc-header writes; line 2480 `mov r13,[r15+0x40]` reads effect-instance field via r15=&D_slot — none are description-base field reads.

## Block 14: listing lines 2481..2540 (RVA 0x666DBBE .. 0x666DCEB)

Description-field reads (base rsi = description base D): NONE — rsi holds an allocation result (`mov rsi,rax` line 2493 from `call qword ptr [0xF99FFA0]`) then a stack-local buffer (`lea rsi,[rbp+0x300]` line 2615 block 16 / here `lea rsi,[rbp+0x300]` line 2515); not the description base. No description-base register exists in this block.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2495 | 0x666dbff | `je 0x66709B7` | 0x66709B7 | branch exit |
| 2514 | 0x666dc65 | `je short 0x666DC98` | 0x666DC98 | branch |
| 2525 | 0x666dc96 | `jne short 0x666DC80` | 0x666DC80 | branch |
| 2527 | 0x666dca7 | `jb short 0x666DCB2` | 0x666DCB2 | branch |
| 2530 | 0x666dcb0 | `jmp short 0x666DCB9` | 0x666DCB9 | branch |

Calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2491 | 0x666dbf2 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2509 | 0x666dc52 | `call 0x76B30` | 0x76B30 | call |
| 2521 | 0x666dc8a | `call 0xAA840` | 0xAA840 | call |
| 2539 | 0x666dce6 | `call 0x66A02D0` | 0x66A02D0 | call |

Block note: lines 2481-2490, 2492-2508, 2510-2513, 2516-2524, 2526-2538 are alloc-header writes, size/pointer arithmetic, stack stores — none are description-base field reads.

## Block 15: listing lines 2541..2600 (RVA 0x666DCEC .. 0x666DE01)

Description-field reads (base rsi = description base D): NONE — rsi holds an allocation result (`mov rsi,rax` line 2599) or stack-local `[rbp+0x630]` (line 2553); not the description base. No description-base register exists in this block.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2556 | 0x666dd61 | `jg 0x667105B` | 0x667105B | branch exit |
| 2557 | 0x666dd3c | `je 0x666E197` | 0x666E197 | branch exit |
| 2564 | 0x666dd6b | `jne 0x666E197` | 0x666E197 | branch exit |
| 2567 | 0x666dd78 | `je 0x666E111` | 0x666E111 | branch exit |
| 2574 | 0x666dd93 | `je 0x666E11B` | 0x666E11B | branch exit |
| 2576 | 0x666ddb6 | `jne 0x666E11B` | 0x666E11B | branch exit |
| 2588 | 0x666ddcc | `jmp 0x666E11B` | 0x666E11B | branch |

Calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2550 | 0x666dd1b | `call 0x67CFD80` | 0x67CFD80 | call |
| 2581 | 0x666ddac | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2587 | 0x666ddc6 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2597 | 0x666ddf7 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |

Block note: lines 2541-2549, 2552, 2554-2555, 2558-2563, 2565-2566, 2568-2573, 2575, 2577-2580, 2582-2586, 2589-2596, 2598-2600 are refcount-inc/dec, stack stores, alloc-size setup, global reads — none are description-base field reads.

## Block 16: listing lines 2601..2660 (RVA 0x666DE04 .. 0x666DF42)

Description-field reads (base rsi = description base D): NONE — rsi holds an allocation result (`mov rsi,rax` lines 2613, 2643 from calls); not the description base. No description-base register exists in this block.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2601 | 0x666de04 | `je 0x66709F3` | 0x66709F3 | branch exit |
| 2617 | 0x666de6b | `jb short 0x666DEA5` | 0x666DEA5 | branch |
| 2621 | 0x666de7f | `jb short 0x666DEA0` | 0x666DEA0 | branch |
| 2626 | 0x666de90 | `jae 0x6670A7A` | 0x6670A7A | branch exit |
| 2633 | 0x666deaf | `je 0x666DFDF` | 0x666DFDF | branch |
| 2644 | 0x666deeb | `je 0x6670A03` | 0x6670A03 | branch exit |

Calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2612 | 0x666de51 | `call 0x358C40` | 0x358C40 | call |
| 2630 | 0x666dea0 | `call 0xE935700` | 0xE935700 | call |
| 2641 | 0x666dee1 | `call r8` | r8 (= [0xF99FFA0]) | call |

Block note: lines 2602-2611, 2614-2616, 2618-2620, 2622-2625, 2627-2629, 2631-2632, 2634-2640, 2642-2660 are object init, size compares, alloc-header writes, global reads — none are description-base field reads.

## Block 17: listing lines 2661..2720 (RVA 0x666DF49 .. 0x666E076)

Description-field reads (base rsi = description base D): NONE — rsi holds an allocation result (`mov rsi,rax` lines 2666, 2701); not the description base. No description-base register exists in this block.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2668 | 0x666df62 | `je 0x6670A1E` | 0x6670A1E | branch exit |
| 2681 | 0x666dfaf | `jb short 0x666DFB5` | 0x666DFB5 | branch |
| 2684 | 0x666dfb8 | `je 0x666E102` | 0x666E102 | branch |
| 2688 | 0x666dfc8 | `jae 0x666E2F7` | 0x666E2F7 | branch exit |
| 2691 | 0x666dfda | `jmp 0x666E356` | 0x666E356 | branch |
| 2703 | 0x666e015 | `je 0x6670A41` | 0x6670A41 | branch exit |

Calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2664 | 0x666df55 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2699 | 0x666e00b | `call r8` | r8 (= [0xF99FFA0]) | call |

Block note: lines 2661-2663, 2665, 2667, 2669-2680, 2682-2683, 2685-2687, 2689-2690, 2692-2698, 2700, 2702-2720 are hash init, object init, size compares, alloc-header writes — none are description-base field reads.

## Block 18: listing lines 2721..2780 (RVA 0x666E07A .. 0x666E18C)

Description-field reads (base rsi = description base D): NONE — rsi holds an allocation result (`mov rsi,rax` line 2724) or stack-local `[rbp+0x3F8]` (line 2764); not the description base. No description-base register exists in this block.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2726 | 0x666e08c | `je 0x6670A5C` | 0x6670A5C | branch exit |
| 2738 | 0x666e0d2 | `jb short 0x666E0D8` | 0x666E0D8 | branch |
| 2741 | 0x666e0db | `je 0x666F03F` | 0x666F03F | branch |
| 2745 | 0x666e0eb | `jae 0x666F04E` | 0x666F04E | branch exit |
| 2748 | 0x666e0fd | `jmp 0x666F0AD` | 0x666F0AD | branch |
| 2750 | 0x666e10c | `jmp 0x666E37E` | 0x666E37E | branch |
| 2755 | 0x666e11e | `je short 0x666E197` | 0x666E197 | branch exit |
| 2762 | 0x666e13b | `je 0x666EED3` | 0x666EED3 | branch |
| 2767 | 0x666e156 | `je 0x666EEE8` | 0x666EEE8 | branch |
| 2769 | 0x666e163 | `jne 0x666EEE8` | 0x666EEE8 | branch |

Calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2722 | 0x666e07f | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2774 | 0x666e172 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2780 | 0x666e18c | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |

Block note: lines 2721, 2723, 2725, 2727-2737, 2739-2740, 2742-2747, 2749, 2751-2754, 2756-2761, 2763, 2765-2766, 2768, 2770-2773, 2775-2779 are alloc-header writes, refcount inc/dec, stack stores, hash/free chains — none are description-base field reads.

## Block 19: listing lines 2781..2840 (RVA 0x666E192 .. 0x666E295)

Description-field reads (base rsi = description base D): NONE — rsi holds stack-local `[rbp+0x638]` (line 2782), `[rax]` (line 2818), or `rdi` (line 2828); not the description base. No description-base register exists in this block.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2784 | 0x666e1a1 | `je short 0x666E1CE` | 0x666E1CE | branch |
| 2787 | 0x666e1a7 | `jne short 0x666E1CE` | 0x666E1CE | branch |
| 2792 | 0x666e1bc | `jne short 0x666E1CE` | 0x666E1CE | branch |
| 2799 | 0x666e1d8 | `je short 0x666E21C` | 0x666E21C | branch |
| 2803 | 0x666e1eb | `jb short 0x666E209` | 0x666E209 | branch |
| 2808 | 0x666e1fc | `jae 0x6670A7A` | 0x6670A7A | branch exit |
| 2819 | 0x666e234 | `je short 0x666E261` | 0x666E261 | branch |
| 2830 | 0x666e25f | `jne short 0x666E240` | 0x666E240 | branch |
| 2836 | 0x666e27d | `jb 0x6670032` | 0x6670032 | branch exit |
| 2840 | 0x666e295 | `jb 0x667002D` | 0x667002D | branch exit |

Calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2790 | 0x666e1b2 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2796 | 0x666e1c8 | `call qword ptr [0xF99FFA0]` | [0xF99FFA0] | call |
| 2809 | 0x666e209 | `call 0xE935700` | 0xE935700 | call |
| 2824 | 0x666e247 | `call 0x9B250` | 0x9B250 | call |
| 2827 | 0x666e254 | `call 0xE935700` | 0xE935700 | call |
| 2833 | 0x666e26d | `call 0xE935700` | 0xE935700 | call |

Block note: lines 2781, 2783, 2785-2789, 2791-2795, 2797-2798, 2800-2802, 2804-2807, 2810-2818, 2820-2823, 2825-2826, 2828-2829, 2831-2835, 2837-2839 are refcount dec/free, buffer-size compares, object-chain walks, stack stores — none are description-base field reads. Line 2900 `mov rsi,[rdx+rcx+8]` (next block) loads rsi from a buffer array — not description base.

## Block 20: listing lines 2841..2900 (RVA 0x666E29B .. 0x666E39A)

Description-field reads (base rsi = description base D): NONE — rsi loaded from buffer array `[rdx+rcx+8]` (line 2900); r13+rcx is a hash-table buffer; no description-base register exists in this block.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2845 | 0x666e2aa | `jae 0x6670A7A` | 0x6670A7A | branch exit |
| 2853 | 0x666e2cc | `jmp 0x666F4ED` | 0x666F4ED | branch |
| 2858 | 0x666e2e1 | `je 0x666F4D6` | 0x666F4D6 | branch |
| 2861 | 0x666e2f2 | `jmp 0x666F4D8` | 0x666F4D8 | branch |
| 2881 | 0x666e34f | `jne short 0x666E314` | 0x666E314 | branch |
| 2883 | 0x666e354 | `je short 0x666E37E` | 0x666E37E | branch |
| 2894 | 0x666e37c | `jne short 0x666E368` | 0x666E368 | branch |

Calls in block 20: none.
Block note: lines 2841-2844, 2846-2849, 2850-2852, 2854-2857, 2859-2860, 2862-2880, 2882, 2884-2893, 2895-2900 are buffer-pointer arithmetic, FNV-1a hash loop over r13 buffer, stack stores — none are description-base field reads.

## Block 21: listing lines 2901..2950 (RVA 0x666E39F .. 0x666E453)

Description-field reads (base rsi = description base D): NONE — rsi holds a hash-table node pointer walked via `[rsi+8]` (lines 2920, 2926) or stack-local `[rbp+0x618]` (line 2948); [rsi+0x20]/[rsi+0x28]/[rsi+0x10] reads are hash-table node fields, NOT description fields. No description-base register exists in this block.

Branch exits / calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2902 | 0x666e3a2 | `je short 0x666E400` | 0x666E400 | branch |
| 2905 | 0x666e3ab | `je short 0x666E3F1` | 0x666E3F1 | branch |
| 2908 | 0x666e3b8 | `jb short 0x666E3C0` | 0x666E3C0 | branch |
| 2911 | 0x666e3be | `jmp short 0x666E3C4` | 0x666E3C4 | branch |
| 2917 | 0x666e3d1 | `je 0x666FC88` | 0x666FC88 | branch exit |
| 2919 | 0x666e3da | `je short 0x666E3FD` | 0x666E3FD | branch |
| 2922 | 0x666e3e4 | `je short 0x666E3B3` | 0x666E3B3 | branch |
| 2923 | 0x666e3e6 | `jmp short 0x666E3D7` | 0x666E3D7 | branch |
| 2925 | 0x666e3eb | `je short 0x666E3FD` | 0x666E3FD | branch |
| 2926 | 0x666e3ed | `jmp short 0x666E3E8` | 0x666E3E8 | branch |
| 2927 | 0x666e3f6 | `jne short 0x666E3E8` | 0x666E3E8 | branch |
| 2929 | 0x666e3f8 | `jmp 0x666FC88` | 0x666FC88 | branch exit |
| 2934 | 0x666e414 | `je 0x6671102` | 0x6671102 | branch exit |
| 2937 | 0x666e41d | `js short 0x666E429` | 0x666E429 | branch |
| 2939 | 0x666e427 | `jmp short 0x666E441` | 0x666E441 | branch |
| 2950 | 0x666e453 | `js short 0x666E45C` | 0x666E45C | branch |
| 2952 | 0x666e45a | `jmp short 0x666E473` | 0x666E473 | branch |

Calls:
| Line | RVA | Instruction (quoted) | Target | Kind |
|------|-----|----------------------|--------|------|
| 2915 | 0x666e3ca | `call 0xEEC6EB0` | 0xEEC6EB0 | call |

Block note: lines 2901, 2903-2904, 2906-2907, 2909-2910, 2912-2914, 2916, 2918, 2921, 2924, 2927-2928, 2930-2933, 2935-2936, 2938, 2940-2949, 2951 are hash-node compares, string compare call setup, float conversion, stack locals — none are description-base field reads.

## NEXT
Interpretation complete: listing lines 1701..2950 (blocks 1-21) fully covered in docs/progress/oc_U-FX2.md. Description-field reads occur only in blocks 1-8 (lines 1747-1792 via rsi=D [I], and 2124-2169 via rsi=D [V]); blocks 9-21 (lines 2175-2950) report NONE because rsi (the only body description-base register) is clobbered at line 2171 and never reloaded as D after line 2142.

