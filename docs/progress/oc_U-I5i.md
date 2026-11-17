## NEXT: Step 2: Get disassembly of 0xE87AC0 and check 0xF9A8C78 global pointer, then check BGFX_MAP.md for texture creation API.

# UNIT U-I5i: Glyph Atlas Texture Creation

## Step 1: Disassembly of 0xE84070 (font object creation) - COMPLETE

### Key CALL sites in 0xE84070:
| RVA | Instruction | Callee | Notes |
|-----|-------------|--------|-------|
| 0xE840B6 | call qword ptr [0xF99FFA0] | allocator (0x11) | Initial alloc |
| 0xE840D5 | call qword ptr [0xF99FFA0] | allocator (0x20) | Primary font object |
| 0xE84230 | call 0xEEC6EC0 | string copy | Font name copy |
| 0xE84275 | call qword ptr [0xF99FFA0] | allocator (0x38) | **Secondary texture object** |
| 0xE8436C | call 0xEEC6EC0 | string copy | |
| 0xE8441A | call r8 ([0xF99FFA0]) | allocator | |
| 0xE8444D | call r8 ([0xF99FFA0]) | allocator | |
| 0xE8447B | call 0xEEC6EC0 | string copy | |
| 0xE84514 | call qword ptr [0xF99FFA0] | allocator | |
| 0xE8453F | call qword ptr [0xF99FFA0] | allocator | |
| 0xE84573 | call 0xEEC6EC0 | string copy | |
| 0xE8460F | call qword ptr [0xF99FFA0] | allocator | |
| 0xE8463A | call qword ptr [0xF99FFA0] | allocator | |
| 0xE8466E | call 0xEEC6EC0 | string copy | |
| 0xE84795 | call qword ptr [0xF99FFA0] | allocator | |
| 0xE847C0 | call qword ptr [0xF99FFA0] | allocator | |
| 0xE847F4 | call 0xEEC6EC0 | string copy | |
| 0xE8488E | call qword ptr [0xF99FFA0] | allocator | |
| 0xE848BA | call qword ptr [0xF99FFA0] | allocator | |
| 0xE848F0 | call 0xEEC6EC0 | string copy | |
| 0xE84983 | call qword ptr [0xF99FFA0] | allocator | |
| 0xE849AF | call qword ptr [0xF99FFA0] | allocator | |
| 0xE849E1 | call 0xEEC6EC0 | string copy | |
| 0xE84A62 | call 0x18718D0 | **KEY: Resource registration** | With font name string |
| 0xE84AB1 | call 0xE87AC0 | **KEY: Texture setup?** | After string setup |
| 0xE84B2E | call 0xE935700 | release/destroy | Cleanup |
| 0xE84DA1 | call qword ptr [0xF9A8C78] | **KEY: Final callback** | End of function |

## Step 1b: Caller of 0xE84070
- **0xE82E00** (font init entry) - 4 call sites with "DefaultFont", "RuneFont", "UIFont", "UnicodeFont", "SmoothFontLatin"

## Step 1c: Analysis of 0x18718D0 (resource registration) - COMPLETE
Function size 0x2000 (8KB). Key observations:
- Tree traversal (RB-tree based on left/right child pointers at offsets 0x19, 0x20, 0x28)
- Reference counting via calls to allocator [0xF99FFA0] (sub_eea6040) for cleanup
- Calls **0x186DAC0** at 0x1871AB7 with font data (rdi = font object, rsi = destination)
- Lock cmpxchg at 0x1871A09 for thread synchronization
- String pointer at 0xEFCA680 and callback at 0x873D0

## Step 2: Analyze 0xE87AC0 (texture setup callee)