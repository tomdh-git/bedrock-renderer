# Dossier: MaterialPass::findVariant (0xbcc7ce0), 1.26.62.01 [V disassembly, roles I]

Called by submitGeometry's tail 0xbcc3b90 (then Encoder::submit 0xbc60740 with the found program) and 16 other pass bodies (0x56d3170, 0x56d5ed0, 0xbc0b240, 0xbc5bad0, 0xbc96950, 0xbc973e0, 0xbc97bc0, 0xbca85e0, 0xbca9770, 0xbcaaac0, 0xbcb7590, 0xbcc39b0 ...). This is the runtime (pass, flags) -> program selection.

Signature: `Optional<Variant>* findVariant(Optional<Variant>* out /*rdx*/ , MaterialPass* pass /*rcx, kept in rdi*/, const DefineMap* defines /*r8*/)`; returns out. out = {u32 +0 = variant dword {u16 program, bit16 valid}, u64 +8 = pointer to variant data (node+0x20), u8 +0x10 engaged}.
```
u64 mask;
if (defines->size /*+0x10*/ != 0) {
    mask = flagMask(pass->flagTable /*[pass+0x40]*/, span{count=(pass+0x50-pass+0x48)/8, data=pass+0x48}, &pass->flagDefs /*pass+0x60*/, defines);   // 0xe879eb0, may return 0 -> not found
    if (!mask) { out->engaged = 0; return out; }
} else {
    mask = pass->defaultMask /*+0xA0*/;  if (!mask) { out->engaged = 0; return out; }
}
u64 h = fnv1a_64(8 bytes of mask, little-endian, byte by byte);          // offset 0xcbf29ce484222325, prime 0x100000001b3
node = pass->variants /*unordered_map<u64 mask, Node>: sentinel +0x108, buckets +0x118, bucket mask +0x130*/.find(h & mask130, key == mask);   // key at node+0x10
if (!node) out->engaged = 0; else { out->dword = node->+0x1C; out->ptr = node + 0x20; out->engaged = 1; }
```
Consumer (0xbcc3b90) [V]: `valid = byte at out+2` (bit 16 of the dword), `program = u16 out+0`; if valid and program != 0xFFFF it increments the matrix counter and calls Encoder::submit(program, ...). Variant node +0x1C = the {u16 handle, valid bit 16} stored by initFromMaterial (bcc7f20.md), so the lookup returns the bgfx program created at material load.
Open [?]: 0xe879eb0 (0x568 bytes) turns the define map into the u64 flag mask (per-flag FNV-1 64 name lookup in the pass flag table via 0xe87b920); its body is read only to the point of the name hashing. The static key passed by submitGeometry (rip+0x6e1ec5a) is presumably an empty define map (default mask path) [?].

## Addendum: the "mask" builder 0xe879eb0 and its helpers (read in full this pass) [V flow, I names]
Correction: the u64 keying the variant map is an opaque variant id (the pointer stored as element of the span at pass+0x48..+0x50), not a bit mask. FNV-1a over its 8 bytes is only the bucket hash.
`u64 selectVariantId(const FlagTable* table /*rcx: material default flag map: sentinel +8, nodes key +0x10 / value +0x30*/, Span<VariantRec*> variants /*rdx: {count, data}*/, const Map* passFlags /*r8 = pass+0x60*/, const Map* defines /*r9*/)`:
1. merged = copy of table's (name -> value) map (0x49b1a0 per node).
2. for each (k,v) of passFlags: if k is in merged, merged[k] = v (find 0x1336d0, assign 0x9d6d0).
3. for each (k,v) of defines: 0xe87b920(table, k, v) validates the pair (name present in the table, value among its allowed values; 0x1e0 bytes, hashed lookup + string compares 0xeec6eb0) - failure returns 0 (no variant); a valid pair is applied to merged only if k is not fixed by passFlags [I].
4. return the first variant record p in `variants` for which 0xe879c60(p, merged) is true (0x24b bytes: every (name,value) of merged that also exists in p's own flag map must be equal; absent names are ignored), else 0.
findVariant then looks the id up in pass+0x108 map (hash FNV-1a 64 of the 8 id bytes). Default (no defines): id = pass+0xA0.
Variant axes in the file format (6ap) = the flag name/allowed-value table; each material variant record = one flag assignment map; the pass owns the id -> {program} map. Header: MaterialPassLayout.h (mask wording there = variant id).
