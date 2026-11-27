# CP14 Wiring — daemon one-line call

The daemon (Kotlin) should invoke the finish handler exactly as follows:

```
python tools/ctx/finish.py <item_id>
```

Where `<item_id>` is the unit identifier in the `X<wave>.<rva>[.c<chunk>]` format, e.g.:
- `X7.8f21d0` (whole function at 0x8f21d0)
- `X4.66ad570` (whole function at 0x66ad570)
- `X1.bc82ad0.c02` (chunk 2 of function at 0xbc82ad0, range 0xbc85abd..0xbc864bb)

The item_id maps to the progress file `docs/progress/oc_U-EX<item_id>.md`.

The tool prints exactly ONE verdict line to stdout:
- `VERDICT close` — gate passes, no unresolved calls (includes placeholder CLOSES? NO and full CLOSES? YES)
- `VERDICT retry: <one-line problem>` — gate fails; full error written to `docs/progress/hints/<item_id>.txt`
- `VERDICT resolve` — gate passes but `## UNRESOLVED CALL` has content; `resolve_unresolved.py` has been run

Exit code is always 0 (the verdict line carries the result). The daemon should parse the first word after `VERDICT `.

No checklist ticking is performed by this tool.