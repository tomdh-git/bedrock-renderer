# Atlas UV application (0x6bfa6d0, 0x6bfa9d0) and the atlas JSON parser (0x4e1a0a0), 1.26.62.01 [V disassembly, roles I]

## 0x6bfa6d0 (size 0x2be): apply atlas entries to a block-texture list
`void apply(const vector<TexEntry>* rcx /*stride 0x90*/, Ctx* rdx, Obj* r8, shared_ptr* r9)`.
1. Clears r8+0xE8 (a vector<Owned*>): for each non-null element calls 0x4de9de0 on element+0xB0; then destroys each 0x368-byte object (dtor 0x5440320, free size 0x368) and sets end = begin.
2. For each TexEntry e (0x90 bytes): name std::string at e+0x60 (SSO cap at +0x78), atlas index i32 at e+0x5C, flag byte e+0x88, variant index i32 e+0x84. Atlas lookup `A = 0x4e17890(ctx[+0x18], &name)` (default empty atlas object when ctx+0x18 is null).
3. A+0x28/+0x30 = vector of 0x18-byte atlas slots, slot = {begin, end, ...} of 0x60-byte UV records. idx = e+0x5C: if idx < 0 or idx >= slotCount (= (end-begin)/0x18): if A's name is the 7-character placeholder (7 bytes compared with two rdata dwords) log "Texture %s is missing from atlas textures" through 0xda490 (level 3, category 0x20), else call 0x6bfa9d0, which logs "Texture %s is using an invalid atlas index %i for the expected UV count %i" through 0x3d0730 once logging is enabled (static logger at rip+0xbcc74ff). Valid idx: if e+0x88 == 1 pick UV record number (e+0x84 if in range else 0) else apply every record; each application = 0x6bfaba0(&ctx{rdx, r8, r9, &e+0x1F0 field}, e, &uvRecord).
3 outputs: UV records are 0x60 bytes each; slot table is 0x18 bytes each. [I] semantic names.

## 0x4e1a0a0 (size 0x1f52): atlas description JSON parse (callers 0x4e198d0, 0x4e1cbb0)
Strings [V]: texture_atlas, padding, num_mip_levels, default_leather_color, default_horse_leather_color, texture_name, texture_data, textures, quad, mip_fade_amount, mip_fade_color, additive; errors "failed to read texture_name in atlas file %s", "Expecting \"%s\" to be a JSON object.", "Missing textures \"%s\"." So it reads terrain_texture.json / item_texture.json style files: per atlas a name, padding, mip count, per texture entry the UV variants. Not read line by line [?].

## Correction of the earlier lead list
0x5752d50 (0x28f0 bytes; callers 0x15ac010, 0x5755bc0) is NOT an atlas builder: its strings are inventory item-renderer bindings (#item_id_aux, #charged_item, #item_custom_color, #armor_trim_material, #banner_patterns, ..., InventoryItemRenderer::_onItemChanged) plus the atlas texture names it selects for compass, clock, lodestone and recovery compass items (atlas.items, atlas.terrain, textures/items/*_atlas).
Still not found: the stitching code that builds the atlas image and calls the texture creation chain of 8b9f1c0.md.
