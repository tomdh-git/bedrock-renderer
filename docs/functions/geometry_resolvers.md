# Dossier: DrawItemGeometry construction helpers (1.26.62.01, static, extractors-core). Tags [V]/[I]/[?]

All operate on `DrawItemGeometry` (src/sdk/mc/deps/minecraft_renderer/framebuilder/DrawItem.h, 0x58 bytes): +0x00 head (= **frameCtx), +0x08/+0x10/+0x18 vertex-stream vector {begin,end,cap} of 0x28-byte DrawItemVertexStream, +0x20 vertex count, +0x28 index-ref variant storage (0x10), +0x38 variant tag, +0x40 startIndex, +0x48 indexCount, +0x50 frameCtx.

## 0x675D320 (71 instr) - frame resource tracker getter [V]
`Tracker* get(Registry* rcx)`: looks `rcx+0xA0` up with 0x9BD4A0 (per-thread/owner node); if found returns node+0x10. Else allocates a 0x100-byte node through the allocator at 0x1233E1A8 (vcall +8), self-links {node,node+8}, node+0x10 = 0, calls `[rcx+0x38]->vfunc2(&tracker)` (initialiser callback), inserts it with 0x9BD6D0 and, under the mutex at rcx+0x50 (0xEEC59F0 lock / 0xEEC5A10 unlock; rcx+0x9C == 0x7FFFFFFF -> throw), links the node into the intrusive list at rcx+0x40/+0x48. Returns node+0x10. In the geometry helpers it is called as `get(frameCtx->+0x50 ... +8)` i.e. on (geometry+0x50)+8.
## 0xC2AE240 (217 instr) - tracker set insert [V]
`pair<iterator,bool> insert(HashSet* rcx, out* rdx, const shared_ptr<Res>* r8)`: MSVC `unordered_set<shared_ptr<Res>>` (+0 max_load_factor float, +8 list sentinel, +0x10 list end, +0x18 size, +0x28 bucket vector, +0x40 mask, +0x48 bucket count). Hash = u16 at `*(Res*)->+0x18 -> +0x00` (if that object's byte +2 == 0xFF -> throw 0xB432E0 (valueless)); bucket = hash & mask; equality 0xBCE15D0; if found returns {it,false}; else allocates a 0x20 node, copies the shared_ptr (lock inc [ctrl+8]), grows/rehashes through 0x56D5140 when load factor exceeded (float const rva 0xEEE6700), links into list and bucket, size++ and returns {it,true}. Used on `tracker+0x50` (set of kept-alive resources, keyed by their u16 handle).
## 0xC2ADAC0 (78 instr) - addVertexStream [V]
`void add(DrawItemGeometry* rcx, const StreamRef* rdx (variant: 0x18 storage + tag byte +0x18), u32 r8d startVertex, u64 r9 vertexCount)`: if the stream vector is empty store r9 into +0x20 (vertex count); if end == cap -> grow path 0xC2ADBD0; element: variant storage copied by tag (0 qword at +0, 1 = 16 bytes + 8? (copy 0x18 default), 2 = shared_ptr {ptr, ctrl} with lock inc [ctrl+8]), tag byte at +0x18, startVertex at +0x20, end += 0x28. If the source tag == 2 the shared object is also inserted into the tracker: `0x675D430(get(geometry+0x50 + 8) + 0xA0, &tmp, src)`. Tag > 2 -> 0x1166E0 (bad variant).
## 0xC2ADFD0 (180 instr) - IndexRef assign (variant visit) [V]
`void assign(u64 rcx = source alternative index + 1, IndexRef** rdx, const IndexRefStorage* r8)`; jump table 0xF47A5A0: 0 = source valueless: release dest shared_ptr when dest tag 3, tag = 0xFF; 1 = source tag 0 (none): release, tag = 0; 2 = source tag 1 (pointer): copy qword, tag 1; 3 = source tag 2 (id, 16 bytes): copy 16 bytes, tag 2; 4 = source tag 3 (shared_ptr): copy {ptr, ctrl} (lock inc [ctrl+8]), tag 3; all cases first drop the destination's shared_ptr when its previous tag was 3. Callers pass ecx = 4 with tag 3.
## 0x66B2730 (160 instr) - shared-buffer geometry constructor [V]
`DrawItemGeometry* make(out rcx, frameCtx rdx, const shared_ptr<VB>* r8, const shared_ptr<IB>* r9, [rbp+0x50] u64 vertexCount, [rbp+0x58] u64 indexCount, [rbp+0x60] u32 startIndex)`: out[0] = **frameCtx; +0x08..+0x27 = 0; +0x38 = 0; +0x40 = 0; +0x48 = 0; +0x50 = frameCtx; stream = {vb ptr, vb ctrl (inc)}, tag 2 -> `addVertexStream(out, &stream, 0, vertexCount)`; index = {ib ptr, ib ctrl (inc)}, tag 3 -> assign(4, &out+0x28, &idx); out+0x40 = startIndex; out+0x48 = indexCount; if the index tag is 3 also `insert(get(out->+0x50 + 8) + 0x50, &tmp, &idx)` (tracker set); drops the temporaries. Called from 0x678C4C0 (mesh+0x40 == 1 case) and from the UI/Editor/Particle/Gameface extractors.

## 0xC2AA290 (983 instr) - QuadIndexBuffer::ensure(this, u32 indexCount) [V structure, [I] GPU-object details]
`this` = shared quad-index-buffer cache (the `meshRef` passed to 0x66A0F60 / 0x678C4C0): +0x08 owner (context), +0x18/+0x20 16-byte key, +0x28 bool is32 (capacity >= 0xFFFF), +0x30/+0x38/+0x40 CPU index vector {begin,end,cap}, +0x48 current IndexBuffer object*, +0x50 its shared_ptr control block, +0x58 u32 capacity, +0x60 critical section (0xE943170 lock .. 0xE943194 unlock).
```
if (indexCount <= this->cap) return;            // 0xc2aa2bd: cmp edx,[rcx+0x58]; jbe -> 0xc2ab224 (unlock/return)
lock(this+0x60);  release key handle if +0x20 flag (0xe3295f0 / 0xe32a220);
cap = this->cap ? this->cap : 1; while (cap < indexCount) cap *= 2;  this->cap = cap;  this->is32 = cap >= 0xFFFF;
// fill the CPU vector with the quad pattern, k = quad number, stride 6 indices, 4 vertices per quad:
for (k = 0, base = 0; ...; ++k, base += 4)  idx[6k..6k+5] = { base+1, base+2, base, base, base+2, base+3 };   // u32 when is32 else u16, count = cap/4*6 ([V] stores 0xc2aa43d..0xc2aa4a2 and 0xc2aa569..0xc2aa5d7; 0xc2aa650/0xc2aa6d0 are SIMD fill paths for the monotonic ramp used when the pattern is not quads (vector 0xeee1a10 / 0xf441430 constants))
swap into this+0x30; allocate the GPU object (0x28-byte index-buffer record with vtables rva 0xF0F9C60 / 0xF0F9C80), upload through the renderer, store this+0x48 = object, this+0x50 = its shared control block; unlock.
```
Throws: allocation failure -> 0x78ED0 / 0x9BC830; vector bounds -> 0xC2AB287.
## 0xC29A1D0 (514 instr) - bindVertexStreams for a named vertex layout [V structure, [?] the lookup key semantics]
`void bind(ProgramLayout* rcx, const Name* rdx, const u64* r8 /*key*/, DrawItemGeometry* r9, PassRecord** [rbp+0xE0])`: copies the pass name string (**passRecord + 0x128 via 0x76A8A0), walks the layout list at `[**passRecord + 0x290, +0x298)` (0x20-byte records), binary-searches the sorted 0x18-byte {u64,u64,u64} key vector at rcx+0x60..0x68 with key {*r8, name, r9}; if absent computes a stream mask with 0xC2981F0; the 32-bit mask (low 16 = vertex streams, high 16 = second set) is walked bit by bit (tzcnt): for each set bit i with a live resource `table[i]` ({ptr, ctrl}, validity byte +0x10 == 1) it calls `0xC2ADAC0(geometry, {ptr, ctrl, tag 2}, 0, rbx[+0x30])` (addVertexStream); the high-half pass uses the layout vector at rcx+0x18/+0x20 (0x50-byte records) and the FNV-1a (basis 0xCBF29CE484222325, prime 0x100000001B3) hashed static string at rva 0xF847A07 to look up through 0xBCAC390. Thread-safe statics at 0x129441AC / 0x129CFEAC / 0x12AEBFC0.
## 0x66A0F60 (265 instr) - instruction-complete source [V]
```
DrawItemGeometry* make(DrawItemGeometry* out /*rcx*/, FrameCtx** ctx /*rdx*/, QuadIndexBuffer* qib /*r8*/, const SharedPair* mat /*r9*/, u32 count /*[rbp+0x60]*/, u32 start /*[rbp+0x68]*/, u32 extra /*[rbp+0x70]*/) {
    Obj* o = mat->ptr ? mat->ptr->+0x18 : nullptr;
    if (!o || o->byte(+0x28) != 2) {                       // empty geometry
        out[0] = **ctx; out->+0x38 = 0; out->+0x40 = 0; out->+0x48 = 0; out->+0x08..+0x27 = 0; out->+0x50 = ctx;
        release(mat->ctrl);  return out;
    }
    QuadIndexBuffer::ensure(qib, count);                    // 0xC2AA290
    out = {**ctx, streams{}, tag 0, start 0, count 0, ctx};
    // one vertex stream: the material's resource {o->+0, o->+8}, kind 2 (shared)
    addVertexStream(out, {o->ptr, o->ctrl, tag 2}, 0, ?);   // 0xC2ADAC0 (r9 = vertexCount from the stack tail)
    n = extra ? extra : ((qib->mode == 0) ? (count >> 1 & ~1) * 3 : (mode == 1 ? count : error 0x1166E0));   // 0x66a11a2..0x66a11d9: indices per quad set
    index = {qib->+0x48, qib->+0x50 ctrl (inc)}, tag 3;   IndexRef::assign(4, &out->+0x28, &index);   // 0xC2ADFD0
    out->+0x40 = start(edi); out->+0x48 = n(rsi);
    if (index tag == 3) insert(get(out->+0x50 + 8) + 0x50, &tmp, &index);    // 0xC2AE240 on the tracker set
    release temporaries; return out;
}
```
## 0x678C4C0 (531 instr) - source [V]
```
void build(DrawItemGeometry* out, FrameCtx** ctx, QuadIndexBuffer* qib /*r8*/, PassRecord* pr /*r9*/, const ChunkDrawListEntry* e /*[rbp+0xc0]*/) {
    out = {**ctx, streams{}, tag 0, 0, 0, ctx};
    if (e->variant == 1) {
        rec = (char*)e->mA + (u8)e->+0x10 * 0x50;                                   // 0x50-byte stream-layout records
        bindVertexStreams(rec, name{0x48c1c16a03cad660.., len 0xb}, out, pr, ...);   // 0xC29A1D0 with the temporary string
        if (e->indexIsId) { QuadIndexBuffer::ensure(qib, *(u32*)(rec + 0x48)); idx = {qib+0x48, qib+0x50}; assign(4,&out+0x28,&idx); }
        else             { direct IndexRef from e->mB + (u8)e->+0x10*0x18 (shared) ; assign }
        out->+0x40 = e->mStartIndex; out->+0x48 = e->mIndexCount;
    } else if (e->variant == 0) {
        if (e->mCount >> 32) throw;  mesh = (Mesh*)e->mA;
        if (e->indexIsId) QuadIndexBuffer::ensure(qib, (u32)e->mCount);
        idx = e->indexIsId ? {qib+0x48, qib+0x50} : {*(e->mB+0x48)... shared pair};
        if (mesh->byte(+0x40) == 1) {                          // two vertex streams
            addVertexStream(out, {mesh+0x48, mesh+0x50, tag 2}, 0, count);  addVertexStream(out, {mesh+0x60, mesh+0x68, tag 2}, 0, count);
            assign(4, &out+0x28, idx tag 3); out->+0x40 = e->mStartIndex; out->+0x48 = e->mIndexCount; track idx in set;
        } else {                                               // one stream: 0x66B2730
            make(out, ctx, {mesh+0x48, mesh+0x50}, idx, /*vertexCount*/ e->mCount, /*indexCount*/ e->mIndexCount, /*start*/ e->mStartIndex);
        }
    } else throw 0x1166E0;
}
```
(Branch order and temporaries [V] from 0x678c62b..0x678cc55; the exact shared_ptr temp shuffling is not reproduced, ref-count behaviour is: lock inc on copy, lock dec [+8] -> vcall[0], lock dec [+0xC] -> vcall[8] on release.)
