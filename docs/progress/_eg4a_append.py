import io
lines = [l.rstrip("\n") for l in io.open("docs/progress/_eg4a_proofs.txt", encoding="utf-8")]
lines = [l for l in lines if not l.startswith("0xe80f387")]
note = io.open("docs/progress/oc_U-EG4a.md", encoding="utf-8").read()
app = "\n## Appendix — verify_oc proof lines (verbatim rdis output; the `0xRVA  instr` lines quoted in the tables above, one per address, for tools/sigs/verify_oc.py)\n\n```\n" + "\n".join(lines) + "\n```\n"
io.open("docs/progress/oc_U-EG4a.md", "w", encoding="utf-8").write(note.rstrip("\n") + "\n" + app)
print("appended", len(lines), "proof lines")
