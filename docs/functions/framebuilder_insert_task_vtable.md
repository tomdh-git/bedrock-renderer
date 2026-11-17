# FrameBuilder insert-task vtable (found by U-I5e, verified by `rdis vt 0xF2BE1F8`, 1.26.62.01)
rdata 0xF2BE1F8 (inside a larger vtable; slots before it start near 0xF2BE1C0 per `rdis vt`), slots:
| slot | off | function | size | string passed to sub_2FE330 |
|---|---|---|---|---|
| 0 | +0x00 | sub_668acc0 | 0xe5 | - |
| 1 | +0x08 | sub_6685f30 | 0xe (`mov rcx,[rcx+0x28]`) | - |
| 2 | +0x10 | sub_6674050 | 0x214 | "FrameBuilder - Insert editor" (0xF55F87E), table 0xF2BE338 |
| 3 | +0x18 | sub_666aa00 | 0x218 | "FrameBuilder - Insert effect" (0xF540E58), table 0xF2BE318 |
| 4 | +0x20 | sub_6664760 | 0x218 | "FrameBuilder - Insert UI" (0xF7CB7C5), table 0xF2BE2F8; calls sub_6664a00 at 0x66648C8 |
| 5 | +0x28 | sub_6655de0 | 0x28e | "FrameBuilder - Insert sky" (0xF51B8A2), table 0xF2BE2D8 |
| 6 | +0x30 | sub_66466e0 | 0x218 | "FrameBuilder - Insert item" (0xF59F12F), table 0xF2BE2B8 |
| 7 | +0x38 | sub_6640ae0 | 0x214 | "FrameBuilder - Insert light" (0xF53AEA6), table 0xF2BE298 |
| 8 | +0x40 | sub_768f0 | 1 | ret |
Other sub_2FE330 callers: 0x660B1A0 "FrameBuilder - Insert" (0xF52E07A, table 0xF2BDAD0), 0x66232B0 "FrameBuilder - End frame wait for render" (0xF56F675, table 0xF2BE278), 0xE71330 and 0xE9AED0 (also "FrameBuilder - Insert").
Each task function has the same shape (lea string / movups [0xF0BCBF8] / lea table into [rsp+0x28] / call 0x2FE330), see oc_U-I5e.md. The vtable itself has 0 rip/imm xrefs (constructor not found); the data table at 0xF2BE2F8 holds one code pointer at +0x60 (sub_67ED670).
Source: docs/progress/oc_U-I5e.md.
