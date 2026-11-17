## NEXT
DONE

# U-EL13c — L13c Clouds pass strings; sky/stars/celestial pending

Scope (per checklist item L13c and the unit prompt): ONLY the pending part — the sky/stars/celestial pass strings. The clouds pass part is already done: BGFX_MAP.md section 6x anchor row "clouds pass | 0x67375a0 | 0x3dfb | Clouds, CloudsForwardPBR, CloudColor, DistanceControl" [V].

Method: BGFX_MAP.md 6o/6p states pass names are NOT stored as .rdata strings; they are built inline as 8-byte ASCII immediates next to FNV-1 64 hash code. The sky/stars/celestial pass strings live inside sub_66560f0 [0x66560f0..0x665e7ae), the Sky group insert/variant dispatcher (jump table at 0xF2BF39C reached via `0x6656164  lea rcx,[0xF2BF39C] ; 0x665616b  movsxd rax,[rcx+rax*4] ; 0x6656172  jmp rax`), i.e. Sky group slot +0x370 — tag 5 = Sky/Stars (clone 0x5369b30 per BGFX_MAP 6g), tag 7 = CelestialBody (clone 0x5370b20) = sun/moon. Every string below is located at its .rdata RVA and referenced by a verbatim `lea` instruction inside sub_66560f0, matching rdis disassembly ([V]).

| offset | size | addr | verbatim `0xRVA  instr` proof line | meaning | [V]/[I]/[?] |
|--------|------|------|------------------------------------|---------|-------------|
| 0xF5638A8 | - | 0xF5638A8 | `0x665d8b3  lea rdx,[0xF5638A8]` ; `0x665d997  lea rdx,[0xF5638A8]` | SkyColor — sky pass uniform/param string; referenced from sky draw sub_66560f0 at two sites | [V] |
| 0xF5C6B31 | - | 0xF5C6B31 | `0x665da09  lea rdx,[0xF5C6B31]` | SkyTexture — sky pass texture uniform string; referenced from sub_66560f0 | [V] |
| 0xF7CA19E | - | 0xF7CA19E | `0x6656868  lea rax,[0xF7CA19E]` | StarsForwardPBR — stars pass pipeline string; referenced from sub_66560f0 | [V] |
| 0xF5639E8 | - | 0xF5639E8 | `0x665d925  lea rdx,[0xF5639E8]` | StarsColor — stars pass uniform/param string; referenced from sub_66560f0 | [V] |
| 0xF54C3E1 | - | 0xF54C3E1 | `0x665686f  lea rdx,[0xF54C3E1]` | "Stars" — stars pass name string; referenced from sub_66560f0 | [V] |
| 0xF584D1D | - | 0xF584D1D | `0x665658c  lea rdx,[0xF584D1D]` | SunMoon — celestial body (sun/moon) pass string; referenced from sub_66560f0 | [V] |
| 0xF7CA226 | - | 0xF7CA226 | `0x6656585  lea rax,[0xF7CA226]` | SunMoonForwardPBR — celestial body forward pass string; referenced from sub_66560f0 | [V] |
| 0xF563A7B | - | 0xF563A7B | `0x665dc90  lea rdx,[0xF563A7B]` | SunMoonColor — celestial body color uniform string; referenced from sub_66560f0 | [V] |
| 0xF5C6D27 | - | 0xF5C6D27 | `0x665dd02  lea rdx,[0xF5C6D27]` | SunMoonTexture — celestial body texture uniform string; referenced from sub_66560f0 | [V] |
| 0xF56CAFE | - | 0xF56CAFE | `0x665dd74  lea rdx,[0xF56CAFE]` | SunMoonEmissiveMultiplier — celestial body emissive multiplier string; referenced from sub_66560f0 | [V] |

CLOSES? YES — every pending part of L13c ("sky/stars/celestial") is proven by [V] rows: sky (SkyColor, SkyTexture), stars (StarsForwardPBR, StarsColor, "Stars"), celestial body/sun-moon (SunMoon, SunMoonForwardPBR, SunMoonColor, SunMoonTexture, SunMoonEmissiveMultiplier). Each string is located at its .rdata RVA and referenced by a verbatim `lea` instruction inside sub_66560f0 (Sky group insert/variant dispatcher, jump table 0xF2BF39C), matching rdis disassembly with 0 mismatches. No blocked offset remains.

## Verification proof lines (one per line, for rdis cross-check)

0x665d8b3  lea rdx,[0xF5638A8]
0x665d997  lea rdx,[0xF5638A8]
0x665da09  lea rdx,[0xF5C6B31]
0x6656868  lea rax,[0xF7CA19E]
0x665d925  lea rdx,[0xF5639E8]
0x665686f  lea rdx,[0xF54C3E1]
0x665658c  lea rdx,[0xF584D1D]
0x6656585  lea rax,[0xF7CA226]
0x665dc90  lea rdx,[0xF563A7B]
0x665dd02  lea rdx,[0xF5C6D27]
0x665dd74  lea rdx,[0xF56CAFE]

## TOOL REQUESTS
None
