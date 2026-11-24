## NEXT
DONE

## FILES
- docs/progress/oc_U-EX1.bc60d10.md (this result file, created)
- src/client/features/render/native/bgfx/EncoderImpl_discard.cpp (created, first line `// LIFT 0xbc60d10 size 0x1fc 1.26.62.01 bgfx::EncoderImpl::discard`)
- src/client/features/render/native/bgfx/EncoderImpl_discard.h (created, layout constants and static_asserts plus the declaration)
- docs/functions/bc60d10.md (edited: 'Reversed source (complete)' section replaced with a complete tag-free version citing every instruction range and quoting both calls verbatim; Purpose instruction count corrected to 91 [V])

## LIFTCHECK
LIFTCHECK OK 0xbc60d10

## UNRESOLVED CALL
none

## TOOL REQUESTS
peinfo.py | PE section map + RVAs of [0xF08EF70] rodata, [0xF99FFA0] gadget pointer, [0x12ADF800] g_allocator storage, and instruction encodings at the call sites | confirmed the rodata 16 bytes, that [0xF99FFA0] holds sub_eea6040 (jmp rax gadget), and the exact bytes of both call instructions (throwaway, in %TEMP%\opencode, not in the repo)
checkban.py | locate the regex false positive that made liftcheck flag the source (\[I\] under /i matches [i] array indexes) | throwaway, in %TEMP%\opencode, not in the repo

CLOSES? YES
