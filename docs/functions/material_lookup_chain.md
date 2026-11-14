# Material lookup chain: name -> MaterialInstance* (1.26.62.01, static [V])

Header: src/sdk/mc/deps/minecraft_renderer/renderer/MaterialResource.h.

1. Caller (group visitor, terrain builder, ...) builds Key16 + std::string_view name + Span<Define> defines and calls `ResourceCache::get` 0x675e440 (docs/functions/675e440.md). Result `shared_ptr<Holder>` in `[out]`.
2. Holder = shared_ptr<Resource> {Resource*, ctrl}. Visitor test [V 0x66e76e0..0x66e771d]: `Resource* r = holder.ptr; if (!r) skip; if (r->requested != 1) skip`.
3. `MaterialSlot* s = r->+0x18` (0x66e7742); `MaterialInstance* inst = s->+0x00` (0x66e7746, r15). This is what 6hf calls "material = {MaterialInstance*, UniformBlock}": the MaterialInstance pointer is the first member.
4. The slot is filled by the async job: loadAsync 0xbcbf730 -> Job::run 0xbcc06a0 -> 0xe86b730 (`slot->material = repo.load(name,key,reloaded)` via 0xc2919d0; `slot->instance = new MaterialInstance(material, defines)` ctor 0xbcd1be0, then dependency resolve). Job pump: processPending 0x6622610 (6hj).
5. The materials.index.json reader 0xc26caa0 (6dr) only builds the name list/material-set objects; it is not on the per-draw lookup path.
Until the job has run, `r->mSlot` is null/zeroed and the visitors fall through (the ready test uses `requested`, not slot).

MaterialPtr (SDK, shared_ptr<void>) [I]: the shared_ptr<Resource> of the Holder (16 bytes {ptr, ctrl}); the old "RenderMaterialInfo" label in 6dr is the Resource/MaterialSlot pair. Not verified against a game-side MaterialPtr ctor [?].
