## NEXT
REGISTERED in C:\Users\Atomi\.config\opencode\opencode.json (2026-11-15, user approved). Takes effect after opencode restarts (not done while units were running).

# rtools MCP server (written by the orchestrator; the opencode unit U-TOOL-MCP produced nothing)
- Server: tools/rtools-mcp/server.ts (stdio, bun). Tools: dis, fn, callers, callees, str, stores, casewalk, jt, verify, preflight, livedec. Output is capped at 12000 chars with a truncation note; arguments with shell metacharacters are rejected; rvas must look like 0x1234.
- Test: `bun run tools/rtools-mcp/client_test.ts` lists the tools, calls dis and verify (passed: 11 tools, dis ok, verify 35/35 on oc_U-D5h.md).
- Registration snippet for C:\Users\Atomi\.config\opencode\opencode.json (merge into the existing object):
```json
"mcp": { "rtools": { "type": "local", "command": ["bun", "run", "C:/Users/Atomi/Desktop/BlueySenseV2/tools/rtools-mcp/server.ts"], "enabled": true } }
```
