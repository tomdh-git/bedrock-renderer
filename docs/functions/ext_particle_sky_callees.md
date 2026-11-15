# Callee dossiers for the Particle (0x67417f0) and Clouds (0x67375a0) extractors (agent ext-particle-sky)

Tags [V] read in disassembly, [I] inferred, [?] unknown. Idioms (ID-STR, ID-SP, ID-STATIC, ID-FNV, ID-MAPFIND) are defined in docs/functions/67417f0.md.

## 0x56D55E0 (49 instr) - setUniformMat4ByHash [V]
`UniformSlotResult* f(UniformBlock* ub /*rcx*/, UniformSlotResult* out /*rdx, returned in rax*/, const u64* hash /*r8*/, const mat4* m /*r9*/)`.
```cpp
alignas(16) mat4 tmp = *m;                     // 4 x movups -> [rsp+0x30..0x60]
Span<vec4> sp{1, &tmp};                         // [rsp+0x20]=1, [rsp+0x28]=&tmp   (NOTE: count 1 with a 64-byte payload is the span contract of 0x56d56a0, i.e. one mat4)
// scan ub->uniforms (+0x30 pointer array, stride 0x10, count u16 at +0x3A) for entry with [entry+0x28] == *hash
if (found) { out->idx = (pos-begin)>>4 (u16 [out]); out->flag = 1 ([out+2]); 0x56d56a0(ub, out, &sp); }   // matrix writer sibling of 0x5679db0
else out->flag = 0;
return out;
```
Used by the Clouds extractor for PrevWorld (d+0x40). The writer 0x56d56a0 is the 4x4 variant of 0x5679db0 (same (ub, slot*, span*) signature) [I].

## 0x5ABA5C0 (71 instr) - per-thread pass queue getter [V]
`PassQueue* f(PassQueueRegistry* this /*rcx = F->renderer + 0x9D0*/)`.
```cpp
void* p = 0x9bd4a0(&this->tls /*this+0xA0*/);          // thread-local slot lookup (current thread)
if (p) return (char*)p + 0x10;
Node* n = alloc(0x8C8);                                  // allocator slot [[g]+8]; failure -> 0x9bc830
n->prev = n->next = n;  n->payload /*+0x10*/ = 0;        // intrusive list node, payload = PassQueue (0x8B8 bytes)
if (!this->factory /*+0x38*/) 0xeec59e0();               // std::bad_function_call
this->factory->vcall[+0x10](&n->payload);                // constructs the queue for this thread
0x9bd6d0(&this->tls, n);                                 // register the node for the current thread
mtx_lock(this+0x50) (0xeec59f0; fail -> _Throw_C_error(5)); if (this->+0x9C == 0x7fffffff) { =0x7ffffffe; _Throw_C_error(6) }
n->prev = this->+0x48 (tail); n->next = &this->+0x40 (head sentinel); tail->next = n; this->+0x48 = n;     // push_back into the global list
mtx_unlock(this+0x50) (0xeec5a10);  return &n->payload;
```
So `Q` in the extractors is a lazily created per-thread queue; all thread queues are linked at renderer+0x9D0+0x40 and drained later [V link, I drain].

## Pool vector grow helpers [V]
All four are MSVC `std::vector<T>::_Emplace_reuse_realloc(this /*rcx*/, where /*rdx*/, value /*r8*/)`: new capacity = max(size+1, cap + cap/2) clamped to max_size, big allocations (>=0x1000) use the 0x20-aligned raw-pointer-at-[-8] form, old storage freed with the sized delete, `0x9bc830` = bad_alloc, `0x75740`/`0x75b60` = length_error, `0xeec6ec0`/`0xeec6de0` = memcpy of the two halves.
| rva | instr | T | size | notes |
|---|---|---|---|---|
| 0x6760E60 | 124 | uint8_t | 1 | `where` = end iterator (rdx); the new byte is NOT written (callers only use the new index = `~begin + end` after the call); grows by `size+1` |
| 0x5ABA6D0 | 137 | PassRecord | 0xC8 | trivially copyable: 2 x memcpy + new element copied from `r8` with `0xeec6ec0(.., 0xC8)`; division by 0xC8 is the `imul 0x8f5c28f5c28f5c29` |
| 0x6760710 | 202 | UniformSet | 0x88 | `{u64 mat /*+0*/; UniformBlock copy /*+8..+0x7F*/; handle /*+0x80*/}`: elements are copy-constructed with 0xE869FF0 (UniformBlock copy) and the +0x80 handle is MOVED (source zeroed) in each of the four move paths (0x6760864/0x67608bb/0x676091c/0x676096b); division by 0x88 is `imul 0xf0f0f0f0f0f0f0f1` |
| 0x6760A80 | 225 | StateRecord | 0x58 | trivially copyable (moves of 0x10-byte chunks); division by 0x58 is `imul 0x2e8ba2e8ba2e8ba3` |
Pool index formulas in the extractors: `((end-begin)>>3) * inverse` = index of the last element: 0xFFFF8BA3 (/0x58), 0xFFFF8E39 (/0x48), 0xFFFFF0F1 (/0x88), 0xFFFFAAAB (/0xC with >>2) - consistent with the sizes above [V].

## 0x675F3B0 (446 instr) - PassQueue pool 0x780 push: `vector<DrawGeometry>::push_back(T&&)` [V]
`void f(vector<DrawGeometry>* v /*rcx = Q+0x780*/, DrawGeometry* x /*rdx, MOVED from*/)`; whole body is inside the thread-flag scope `t = vcall([[g]+0x10])(0x4a) ... vcall(...)(t)` (0x675f3e7 / 0x675fa60).
Element `DrawGeometry`, size 0x58 [V layout from the move code]:
```cpp
struct DrawGeometry {                 // 0x58, identical to the first 0x58 bytes the extractor builds at [rbp+0x310]
    SharedPtr   a;                    // +0x00 {ptr, ctrl}: ctrl at +8 is zeroed in the source (moved)
    SharedPtr   b;                    // +0x10 {ptr, ctrl}: both words moved (source zeroed 0x10 bytes at +0x10)
    uint64_t    q20;                  // +0x20 copied
    Variant4    stream;               // +0x28..+0x37 payload (16 bytes), tag u8 at +0x38 (0xFF = empty), see below
    uint8_t     pad39[7];
    uint8_t     tail[0x18];           // +0x40: 16 bytes copied + +0x50 qword copied
};
```
Variant4 move/copy by tag (jump table 0xf2bfa..., 4 entries): 0 -> 8-byte copy; 1 and 2 -> 16-byte copy; 3 -> 16 bytes zeroed then {ptr,ctrl} copied with `lock inc [ctrl+8]` (shared retain). This is the DrawItemGeometry that 0x66A0F60 builds (docs/functions/geometry_resolvers.md). Growth: `_Emplace_reuse_realloc` form inline (capacity max(size+1, size*1.5), `imul 0x2e8ba2e8ba2e8ba3` = /0x58, big alloc >= 0x1000 bytes, relocation moves each element, then destroys the old ones: tag 3 releases its shared ctrl at +0x30 (ID-SP), and for the 0x28-vector in a (+8/+0x10 begin/end, stride 0x28, tag u8 +0x18 == 2 -> ID-SP of [elem+8]) - so `b` is a `vector<Binding>` (begin +8? see ordering in 0x66A0F60), `a` is the shared pair [?]). [V code, I names]

## 0x675FB30 (416 instr) - PassQueue pool 0x648 push: `vector<TransformVariant>::push_back(T&&)` [V]
Element `TransformVariant`, size 0x48: tag u8 at +0x40 (0xFF = empty):
- tag 0: 16 floats copied dword by dword (`mat4`, +0x00..+0x3F) - the extractor's local `[rbp+0x4b0]` tag-0 payload (d+0x00..0x3F, copy at 0x6737d8a);
- tag 1: 0x18 bytes MOVED (source zeroed): `std::vector<mat4>` {begin,end,cap} - the extractor frees `[rbp+0x4b0]` (big-alloc rule, `or rdx,0x27`) when `[rbp+0x4f0]==1` after the push; so tag 1 = instance transform array;
- tag 2: one 8-byte value (pointer/handle).
Growth path inline (`imul 0x8e38e38e38e38e39` = /0x48, max 0x38e38e38e38e38e, big alloc >= 0x39 elements), the element destructor for tag 1 frees the vector storage. Executed under the same thread-flag scope (0x4a). [V code; I names]

## 0x67450A0 (152 instr) - DrawArgs assembler (particle) [V]
`void f(const ArgCtx* ctx /*rcx*/, DrawArgs* out /*rdx*/)`, ctx = { DrawGeometry* geom /*[+0] moved from*/, const Desc* d /*[+8]*/, UniformSet* mat /*[+0x10]: {Material2* m2; UniformBlock ub (+8..); handle at +0x80}*/, const DrawState* st /*[+0x18]*/ } (the particle builds ctx at [rbp+0x630]: {&drawRes, d, &mat, &ds}).
```cpp
struct DrawArgs {                       // 0x190 bytes; in the particle extractor this is [rbp+0x168..0x2f8]
    DrawState   state;                  // +0x00 : copy of *st (0x57 bytes: dword +0, byte +0x14 ... unaligned copies 0x28/0x38/0x47)
    Material2*  m2;                     // +0x60 : mat->m2   ([rbx])
    UniformBlock ub;                    // +0x68 : copy-ctor 0xE869FF0(&out->ub, &mat->ub /*rbx+8*/)  (0x78 bytes)
    void*       ubHandle;               // +0xE0 : moved from mat+0x80 (source zeroed)
    TransformVariant xf;                // +0xE8 : tag 0 = identity mat4 (1.0f at +0xE8,+0xFC,+0x110,+0x124), tag byte +0x128 = 0
    uint16_t    flags;                  // +0x130 : d+0x94 (u16)  <- NEW desc field
    DrawGeometry geom;                  // +0x138: moved from *ctx->geom (a: 0x10 with ctrl zeroed, b: 0x10 moved, q +0x20 copied, variant at +0x28 by tag (0 copy 8; 1,2 copy 16; 3 retain shared), tag byte at +0x170, tail 0x18 at +0x178)
};
```
The local identity temp (at [rbp-0x50], tag byte [rbp-0x10]) is freed with the big-alloc rule only when its tag == 1 (never here). In the particle extractor the DrawArgs fields therefore sit at: state 0x168, m2 0x1c8, ub 0x1d0, ubHandle 0x248, xf 0x250 (tag 0x290), flags 0x298, geom 0x2a0 (tag 0x2d8, tail 0x2e0). [V]

## 0x67B5F30 (101 instr) - DrawItem (forward) builder [V]
`DrawItem* f(DrawItem* out /*rcx*/, const TransformVariant* xf /*rdx*/, UniformSet* u /*r8: {m2; ub; handle at +0x80}*/, const DrawState* st /*r9*/, const vec3* v /*[rsp+0x60]*/)`, returns out. Layout of DrawItem (0x13C? size to +0x139):
`+0x00 vec3 (from v) ; +0x10 DrawState copy (0x57 bytes: dword +0x10 .. byte +0x24, floats +0x28..0x34, 0x28/0x38/0x47 chunks to +0x57+0x10) ; +0x70 m2 ; +0x78 UniformBlock copy (0xE869FF0 from u+8) ; +0xF0 handle (moved from u+0x80) ; +0xF8 TransformVariant copy of *xf by tag (0: 16 floats, 2: u64, 1: 0x18 bytes MOVED, source zeroed) ; tag byte +0x138`.
## 0x67B6130 (94 instr) - DrawItem (prepass) builder [V]
Same as 0x67B5F30 without the leading vec3: DrawState copy lands at +0x04 (dword +0x14 / 16 bytes +0x04 / byte +0x18 / floats +0x1C..0x28 / chunks +0x2C..0x5A), m2 at +0x68, UniformBlock copy at +0x70, handle at +0xE8, TransformVariant at +0xF0, tag byte at +0x130 (size 0x131 -> 0x138). Called as `0x67b6130(out, xf, u, st)` (4 args).
Both are pure packing functions; the particle extractor passes `xf = &rbp+0x250` (identity variant of DrawArgs), `u = &rbp+0x1c8` (DrawArgs.m2/ub/handle), `st = &rbp+0x168` (DrawArgs.state) and the forward variant additionally `{0,0,0}` at [rbp+0x560] as the leading vec3.

## 0x67E8020 (323 instr) / 0x67E8900 (287 instr) / 0x67E5F00 (304 instr) - PassQueue::submit (the ID-PUSH of the extractors as functions) [V]
All three: `Q = 0x5aba5c0(R /*rcx = F->renderer + 0x9D0*/)`, record `rec` (0xC8 bytes, zeroed 12 xmm + qword at [rbp+0x60]) on the stack, then the same ordered pool pushes, each wrapped in the thread-flag scope (`t = vcall([[g]+0x10])(0x4a) ... vcall(t)`), each patching one 16-bit pool index into `rec` and OR-ing a bit pattern into `rec.flags` (qword at +0):
1. geometry: `0x675f3b0(Q+0x780, geom /*rdx, moved*/)`, rec.w+0x28 = idx
2. u16: push `*flags /*r8*/` into Q+0x8a0 (grow 0x1ef6f90), rec.w+0x10 = idx
3. transform: `0x675fb30(Q+0x648, xf /*r9*/)`, rec.flags = 0x2001001, rec.w+0x42 = idx
4. uniform set: element {[u+0] m2, UniformBlock copy (0xE869FF0 from u+8) at +8, handle moved from u+0x80} into Q+0x768 (grow 0x6760710), rec.flags |= 0x2003001, rec.w+0x2a = idx
Then per function:
- **0x67E8020 (particle forward)** args `(R, geom, u16* flags, xf, UniformSet* u /*[rbp+0xd0]*/, DrawState* st /*[rbp+0xd8]*/, vec3* v /*[rbp+0xe0]*/)`: byte pool Q+0x2d0 (rec.flags = 0x4000000002003001, rec.w+0x8c), byte pool Q+0x390 (rec.w+0x7c), state pool Q+0x750 (0x58 elements, copy of *st; rec.flags = 0x4040000002007001, rec.w+0x2c), byte pool Q+0x828 (rec.w+0x1a), vec3 pool Q+0x678 (12 bytes from *v; rec.flags = 0x4040000002807021, rec.w+0x3e), then rec appended to Q+8 (memcpy 0xC8, grow 0x5aba6d0).
- **0x67E8900 (particle prepass)** same without the vec3: flags 0x2003001 -> byte pools Q+0x2d0 (+0x34), Q+0x390 (+0x24) -> 0x4040000002003001 -> state pool Q+0x750 (+0x2c(-0x2c)) -> final flags 0x4040000002007003; extra byte pool and no Q+0x678.
- **0x67E5F00 (clouds object path, C7)** args `(R, geom, flags, xf, UniformSet* u, vec3* v /*[rbp+0xd8]*/, DrawState* st /*[rbp+0xe0]*/, ObjBlock* o /*[rbp+0xe8]*/)`: u (flags |= 0x2003001), vec3 pool Q+0x678, state pool Q+0x750 (flags 0x2807001), byte pool Q+0x828, byte pool Q+0x468 (index -> rec.w+0x12), `0x678d690(.., o)` (object registration [?]), final flags 0x200042807021, rec appended.
So the per-draw record is: {flags qword; u16 index fields +0x10 u16Pool, +0x1a byte828, +0x28 geom, +0x2a uniformSet, +0x2c state, +0x3e vec3, +0x42 xf, +0x7c byteA, +0x8c byteB, ...} = the `PassRecord` consumed by the pass drain (docs/FRAME_CALLGRAPH.md). The extractors' inline ID-PUSH blocks (clouds C4/C5/C6) are the same sequence with different pool sets and flag words: C4/C5 end at 0x2887021 / 0x100002807021 (pools 0x6d8, 0x480); C6 ends at 0x10200002807021 (pools 0x468/0x470 and 0x3c0/0x3c8). The bits of `flags` are the OR of "which pools are present" [I]; exact meaning of each bit is not decoded.

## 0x4DEDD00 (113 instr) - Mesh::bind(mesh, const VertexFormat* fmt) [V structure, I names]
`void f(Mesh* m /*rcx*/, const MeshFormatBlock* fmt /*rdx, 0x70 bytes*/)`.
```cpp
SharedPtr owner;                                   // weak_ptr<...>::lock of {m->+0x40, m->+0x48} (cmpxchg-increment of strong count [ctrl+8] unless 0)
if (!(owner = m->weakOwner.lock())) return;        // 0x4dedd2c / 0x4dedd6a -> release path
u32 itemCount = (m->+0x60 - m->+0x58) / 12;        // imul 0xaaaaaaab
m->+0x1d0 = itemCount | (1ull << 32);              // {u32 count, u32 valid=1}: the "instance count" every extractor reads (+0x1d0/+0x1d4)
u64 n = (m->+0xa8 - m->+0xa0) >> 2;  if (n >> 32) throw length_error (0xeec6d80);
m->+0x10 = (u32)n;
memcpy(m->+0x1d8, fmt, 0x6E);                      // VertexFmt block (+0x1d8 0x20 bytes, +0x1f8 u32, ... to +0x246): the particle copies +0x1d8 (0x20) and +0x1f8 (u32) back out
0x4deadd0(&m->+0x50, &m->+0x1d8, &m->+0x248 /*vertex byte vector*/, &m->+0x14, &tmpA /*rbp-0x48*/, &tmpB /*rbp-0x18*/);   // build/upload with two empty optionals (tag bytes zeroed)
0x4decc10(&m->+0x50);                              // finalize
if (m->+0x38 == 0) 0x4de88b0(m, owner.ptr, &{0,0});   // register the mesh with its owner on first bind
release owner (ID-SP)
```
## 0x66ADAA0 (167 instr) - VertexAttribTable from a vertex format [V]
`AttribTable* f(AttribTable* out /*rcx, returned*/, const VertexFmtDesc* d /*rdx*/)`:
```cpp
out->count /*+0x78*/ = 0; out->u16 /*+0x80*/ = d->u16_20;
for (bit = 0; bit < 15; ++bit) if (d->mask /*u16 +0*/ >> bit & 1) {
    n = 0x5ac26d0(d, bit);                                   // component count / type query
    type = jumptable(bit) -> {0:Position(skip? r9=0,r13=0), 4, 0xd, 0x12, 0xf, 1, 0xe, 0x13 (sets r9=1: record skipped), 0xb, 2, 0xa, 8, 0xc} // bgfx-style attribute id (u8)
    comps = (n-1 < 8) ? n : 0;                               // r12
    stride/flags: static-guard (0xc321e06) caches one global byte from [[0xc213d92]+0x31] (0xb432e0 on failure); (bit==9 || bit==0) ? (globalFlag & d->u8_22 ? tableByte[bit] (at 0x8bc82c3+bit) : 3) : tableByte[bit];
    norm/asInt bits from n (n in {7,8} -> 0; else bit<=14 ? byte of 0x0001010101010000 >> ((bit-7)*8) : 1)
    if (r9) continue;                                         // type 0x13 is not emitted
    if no record with the same `type` byte exists in out->recs[0..count)   // 6-byte records scanned (0x66adc60)
        out->recs[count++] = { u8 type, u8 comps, u16 d->u16_2[bit] (+2+2*bit), u8 strideOrFmt, u8 flags };
}
return out;
```
Record = 6 bytes at `out + 6*i`, count at `out+0x78`, u16 at `out+0x80`; matches the particle extractor's `[rbp+0x38]` (count) / `[rbp+0x40]` (u16) and the 6-byte copy loops of P9. [V]

## 0xBBD7C70 (179 instr) - VertexFormat from a material's input list [V structure, I names]
`VertexFmtDesc* f(VertexFmtDesc* out /*rcx*/, const MaterialInputs* in /*rdx: std::list at [in+8], sentinel node*/, bool packed /*r8b*/)`. Callers pass `in = m2 + 0x250`.
- Starts with three default sub-blocks (0x22 bytes each: u16 mask 0, 16 x u16 = 0xFFFF offsets, u16 stride, byte flag 1, ...); `packed` clears the flag byte of block 0 (`[rsp+0x54]=0`).
- If the list has a node with byte +0x10 == 0 and +0x11 == 0 (the "position" entry): `5ac2420(&blk0, 0)` gives its byte size; offset cursor `r12 = (size+3)&~3`, stride word set, mask bit0.
- For every list node: byte +0x10 kind (jump table 0xc..: kinds 0-7) and byte +0x11 enabled: derives the attribute bit (kind 0 -> 3? no: kind->bit via table 0x3868c55 for kinds in 0x13F mask, 1->1, 2->2, 3->... 8->8), skips if already present in the mask, otherwise stores the running offset in `blk0.offset[bit]` (u16 at [rsp+bit*2+0x34]), advances the cursor by `5ac2420(.., bit)` rounded to 4 and ORs the bit into the mask (u16 at [rsp+0x32]).
- Unknown kind (>7 or not in table) -> output zero/0xFFFF "invalid" default (0xbbd7ec3).
- Copies the three blocks to `out` (+0x00, +0x24, +0x48 style 0x22/0x26-byte records, total 0x6E bytes = the block memcpy'd into Mesh+0x1d8 by 0x4DEDD00).
Used by both extractors as `0xbbd7c70(&tmp, m2+0x250, 0)` before `Mesh::bind`.

## 0xC2A8C70 (262 instr) - AttribTable -> VertexLayout (bgfx VertexLayout::add/end + hash) [V]
`VertexLayout* f(VertexLayout* out /*rcx -> rsi*/, const AttribTable* t /*rdx -> rdi*/)`:
```cpp
static-guard (0xc2a8c9c .. cold 0xc2a9065: builds a static std::map<u8 type, int> from 0x31d1.. tables and 0xc2a9120)
uint16_t attrs[0x13] filled 0xFF, offsets[0x13] = 0, stride = 0; hash = 0;      // 0xebce430 = memset (0x26 bytes each)
copy t->recs (6-byte {u8 type,u8 comps,u16 off,u8 num,u8 flags}) to a local array, 0xc2a96c0 = sort by (u16 at +2), then for each record:
    pad stride up to rec.off (error if gap >= 0x100 -> length_error path 0xc2a903a);
    look up `type` in the static map (red-black tree walk at 0xc2a8e41, key byte +0x1c, value int +0x20) -> attribIndex (unknown -> out->valid = 0, return);
    attrs[attribIndex] = ((num-1)&3) | ((encodedFmt&7)<<3) | ((flags&1)<<7) | ((encodedFmt<5)<<8);   // bgfx VertexLayout attribute packing
    offsets[attribIndex] = stride;  stride += bytesPerComponent[encodedFmt][num-1]   (table indexed [fmt*8 + num - 1])
final: stride pad to t->u16_0x80;  MurmurHash2-style hash (multiplier 0x5bd1e995) over attrs[0x13], offsets[0x13] and stride, via 0xbc76610 (hash-update) -> out->hash
out->hash (+0), stride (+4 u16), offsets/attrs copied to +0x10..0x4F, out->valid (+0x54) = 1
```
This is bgfx::VertexLayout (size 0x54 + valid byte); the particle extractor uses `[rbp+0xBC]` (= out->valid, out based at rbp+0x68) as the "layout is usable" check in P8. [V]

## 0x67D6D70 (307 instr) - getOrLoadMaterial(cache, out, key, fr40, name, defines) [V]
`void f(MatCache* mc /*rcx*/, SharedPtr<MatHolder>* out /*rdx*/, const Key16* key /*r8*/, Frame2* fr40 /*r9 = F+0x40*/, const StrView* name /*[rsp+0x20]: {ptr,len}*/, const Defines* defines /*[rsp+0x28]*/)`.
It is exactly the inlined sequence of the particle extractor (P4-P6): thread flag scope (`0x30`), `recursive_mutex` lock at mc+0x98 / recursion guard mc+0xE4, ID-MAPFIND of `key` in mc->map (+0x40), stale-list push + erase (0x567d280 / 0x567cf50 / 0x567d9f0), create-or-get `Entry` (0x567d280), allocate the shared MatHolder when empty (0x20 bytes, strong 1 / weak 1), `en->requested = 1` (+0x30), and if the holder's Material (`*holder`) is missing or `material->+0x10 == 0` (not loaded; static guard 0xc1f3654 -> 0x567db00) builds `LoadRequest(name, copy-of-defines (0xaa710), 0, {}, 0)` (0x67d0420), moves it twice (0x567e2b0), sets `request.reloaded = erasedFlag` ([rbp+0x158]) and submits `0xbcc0ee0(fb40-or-r9?, &result, &request)` (the job-system variant of 0xbcbf730), swaps the result into `en->mat`, and returns `*out = {en->mat, retain en->ctrl}` (copy of the shared pair at en+0x20/+0x28). Unlock 0xeec5a10, restore the thread flag.
So `[rbp+0xf0]` in the clouds extractor is `SharedPtr<MatHolder>`; `r14 = holder`, `r15 = *holder = Material*`, `Material->+0x10` = loaded flag (==1 required), `Material->+0x18` = shared_ptr slot whose first word points to the `Material2*` used for `+0x170` (uniform layout) and `+0x250` (vertex inputs). [V]

## 0x6693850 mesh-object cache get-or-create (Clouds F+0x75 path) [V structure, I naming]
Signature: `shared_pair 0x6693850(F, mesh, cache /*fb+0x1b0*/)`, returns {obj, ctrl}.
- Locks cache mutex (cache+0x40 = fb+0x1f0) via 0xeec59f0; recursion guard cache+0x8c (set 0x7ffffffe on the throw path 0x669438e); unlock 0xeec5a00. [V]
- Key = {-1, u16 0, mesh}; hash = FNV of mesh ptr combined with 0x49ebb282d911588e / 0xe4436b5eaa412655, bucket mask via [cache+0x30]. [V]
- HIT: if byte [F->+0x10 +0xa88]==1, copy qword [..+0xa80] to [obj+0x270]; unlock; return [node+0x28]. [V]
- MISS: alloc 0x278-byte object (0x9bc830, size check at 0x942ee), zero, MeshData::clear 0x4df0440, default 0xFFFF format fields, build from mesh with 0x4de83f0/0x4de8170/0x4dea990, conditional 0x6693320 when [obj+0x1e0]!=0 and [obj+0x1e4]; alloc 0x30-byte node {key, mesh, obj} at node+0x28 = obj; insert with load-factor rehash (inc [cache+0x10] at 0x6694272, growth 0x6694266); failure cold blocks 0x6694384/0x669438e (_Throw_C_error 5/6), 0x66942ee/0x66942fe alloc fail. [V ranges, I rehash detail]
- Status: OPEN for exact rehash arithmetic (0x6693fc0..0x6694272 not line-by-line transcribed); semantics sufficient for the Clouds caller.

## Coverage notes
- 0x66B2730 and 0x66A0F60 are decoded by extractors-core (docs/functions/geometry_resolvers.md); not duplicated here. [V]
- 0x678d690 (called from 0x67e5f00), 0x9bd4a0/0x9bd6d0 (tls registry): not decoded. OPEN.
- Sky cases (stars, celestial, cubemap, end sky, volumetric fog) in 0x66560f0 area: not started. OPEN.

## 0x678d690 vector<Rec60>::push_back(const Rec60&) inside thread-flag scope 0x4a [V]
rcx = vector {begin,end,cap}, rdx = const Rec60*. Prologue: fn at [[rip+0xbbb0af6]] vtbl+0x10 called with dl=0x4a (thread-flag scope enter; result in r8b saved at rbp-1, restored at scope exit 0x678dc0e..0x678dc36).
Rec60 (0x60 bytes), copy-constructed (shared_ptr copies = `lock inc [ctrl+8]`):
```
+0x00 shared_ptr<A> {ptr,ctrl}   +0x10 16 raw bytes   +0x20 u16
+0x28 shared_ptr<B>              +0x38 shared_ptr<C>  +0x48 shared_ptr<D>
+0x58 u64 raw
```
Fast path (end != cap): construct at end, end += 0x60. Slow path 0x678d788: count = bytes/0x60 via sar5 * 0xAAAAAAAAAAAAAAAB; newcap = max(count+1, count+count/2) clamped to max 0x2aaaaaaaaaaaaaa (else throw "vector too long" 0x75740); alloc via allocator vtbl+8 (size*0x60, >=0x2b elems uses big-alloc 0x20-aligned with raw ptr at [-8]); construct new elem at index, then move/copy old elements (loop add 0x60, 0x678d948/0x678da17/0x678dae8), destroy old via 0x673cef0 (0x678dba3), free, set begin/end/cap. [V shape, I per-element move vs copy: copies with refcount inc then old destroyed]
Caller semantics: appends one record (pass-record-like bundle of 4 shared resources) to a per-thread list.

## 0x9bd570 / 0x9bd4a0 / 0x9bd6d0 TLS registry slots [V]
- 0x9bd570(idx): `tls = gs:[0x58][tlsIndexA]`; if byte [tls+0xcd8]==0 lazily init (set 1, construct vector at tls+0xcb8 via 0x9bc910, register dtor atexit 0xe9432f8); vector of u64 slots at [tls+0xcc0..0xcc8]; if idx >= size: resize to idx+1 via 0x2fb470 (with 0x9bd1e0 guard object + 0xeec5a10 release); returns &slots[idx]. Lazy per-thread array of pointers indexed by registry id.
- 0x9bd4a0(reg*) = getter: static-init guard (compare tls-init counter [rcx+4] against static; 0xe938cb0/0xe938d70 header/footer, init 0x9bde00); returns *0x9bd570(reg->id /*[rcx]*/). 
- 0x9bd6d0(reg*, value) = setter: same guard, `*0x9bd570(reg->id) = value`.
So Particle/Clouds queue lookup via these = per-thread slot read/write keyed by registry id. Semantics complete.

## 0x6693850 rehash + insert tail, 0x6693fc0..0x6694290 [V]
Container is MSVC unordered_map = doubly linked list + bucket array: sentinel [map+8], size [map+0x10], buckets [map+0x18] stride 16 {first,last}, mask [map+0x30].
Node key at +0x10: {u64 mesh +0x10, u16 +0x18, u64 +0x20}; list links +0/+8.
- 0x6693fc8: after growing bucket array (mask set at 6693fc0/fc4), walk list from sentinel->next (6693fcc), for each node recompute hash (6694015..669412e): h1=fnv1a64(bytes 0x10..0x17), h1+=0x9e3779b9; h2=fnv1a64(bytes 0x18,0x19); h=(h1 ^ ((h1>>2)+(h1<<6)+h2... ) per ID-FNV/MAPFIND; third fnv over bytes 0x20..0x27 combined same way; bucket = h & mask.
- Bucket empty (0x66941d0): first=last=node. Else scan bucket for equal key (key compare 0x6694150..0x669416a) and splice node next to the equal group (0x6693fe0 / 0x6694199 / 0x66941de relinking via prev/next swaps) or at bucket end.
- 0x669420a..0x6694272: find insert position for the NEW node (hash in r13, &mask) in its bucket: bucket empty -> insert before sentinel (r15=sentinel at 0x6694266); else first equal key (0x6694238..0x6694263) or bucket last (0x669425e); link before it, ++size ([map+0x10], 0x6694272), set bucket first/last (0x6694284..). 
6693850 now fully transcribed: DONE.

## Stars: 0x6658ffc..0x6659700 and 0x665a0cf..0x665af0b, statement level [V]
Layout note: the three material paths (Stars -> 0x66585c9, Sky/SunMoon -> 0x66587e4 -> 0x665a0cf) are compiler-duplicated copies of ONE source shape; only the material name, desc offsets and DrawState constants differ.
A. Stars base draw (0x6658ffc..0x6659340): DrawState filled as in S4 but with first dword +0x344 = 0 for the PBR-less twin (6 in the base pass: 0x6658b8e); then `rbp+0x3a0 = state material`, UB copy 0xe869ff0(&rbp+0x3a8, r13=owner), `xf = [rbp+0xd0]` moved to +0x420, tag byte rbp+0x468=0xff; variant byte rbp+0x1b0 (0/1/2) selects the 0x40-byte payload copy: tag0 copies four xmm from rbp+0x170..0x1a0 -> +0x428..0x458; tag1 (0x66594ec) generic; tag2 copies qword rbp+0x170 -> +0x428.
B. PBR twin (0x66590aa..0x66592c4), run only when `mode==1 && !byte[desc+0x3e]` (0x6658d81): (1) feature-scan table rbp+0x88 (16-byte entries, u16 count at +0x92) for the static key, hit -> 0x5679db0(rbx, {u16 idx,1}, {1,r15}); second scan same table with second static key -> 0x5679db0 again; (2) 0x66a08b0(&rbp+0x50); (3) copy desc blocks +0x28/+0x38/+0x48/+0x58 (4xvec4) -> rbp+0x120..0x150 (xmm6..9), byte rbp+0x160=0, r14w=u16 desc+0x68; (4) mesh header 0x4de9fa0(mesh=[desc], out=rbp+0x170); (5) 0x66a6190(out=rbp+0x4e0, rdx=[rsi], r8=rbp+0x170); (6) DrawState constants identical to A but +0x34c=1,+0x350 u16=1,+0x352=2,+0x354=0,+0x358=0, +0x35c..0x377 zero, +0x378=8,+0x37c=0,+0x384=0,+0x388=8,+0x38c/+0x392=0,+0x39a=0xff; +0x3a0=state, UB copy, xf move, 4xvec4 payload (+0x428..0x458 = xmm6..9), +0x468=0, +0x470=u16 r14w; (7) the 0x66a6190 object moved to +0x478 (0x20 + 0x18 payload, +0x4e8=0 +0x4f0=0), +0x4b0=0xff; (8) switch on byte rbp+0x518 (jump table 0x6659328, cases 0..3) -> +0x4a0 payload pair -> 0x665a8e5.
C. Sky/SunMoon path 0x665a0cf..0x665a8e5: material pair -> rbp+0x50 = *[mat+0x18]; 0xe86b370(&rbp+0x58, [mat+0x170], r8=[owner]); stash owner at rbp+0xd0; feature-table scan (rbp+0x98, 0x30-byte entries, u16 count +0xa2) -> index*0xAAAB trick -> 0xbcaba00(&rbp+0x50, &{idx,1}, rdi, &{5,0,0,1}, 0) (0x665a1da); 0x56d55e0(&rbp+0x58, &tmp, name, r9=desc+0x10) (0x665a21a); if byte desc+0x52==1: copy desc+0x10..0x4f (4 vec4) to rbp+0x4e0..0x510, byte rbp+0x520=0, di=u16 desc+0x50, 0x66a6190(&rbp+0x1e0, [rsi], rbx+0x358) (0x665a279), DrawState (dword6? here +0x34c=2), UB copy, payload move, tail 0x665c269; else 0x665a411 second shape ending 0x665a5cf/0x665c38a, geometry via 0x66a0f60 (0x665a653), final 0x665a70d UB copy, join 0x665b624.
D. Shared push tail "SKY-PUSH" 0x665a8e5..0x665aef6 == ID-PUSH of docs/functions/67417f0.md: `byte rbp+0x4b0=tag; copy qword rbp+0x530 -> +0x4c8, vec4 rbp+0x520 -> +0x4b8; Q = 0x5aba5c0(F->+0x10 + 0x9d0)`; zero 0x1e8..0x2a8; `0x675f3b0(Q+0x780, &rbp+0x478)` (DrawGeometry); header qword 0x1000 at rbp+0x1e0; index word at rbp+0x208 = ((Q[0x788]-Q[0x780])>>3 * 0xffff8ba3) - 1 (division by 0x58); thread flag scope dl=0x4a -> rbp+0x540; push u16 rbp+0x470 into pool Q+0x8a0 (0x1ef6f90 grow), push UniformSet (qword rbp+0x3a0 + UB 0xe869ff0 + qword +0x80=rbp+0x420) into Q+0x768 (stride 0x88, grow 0x6760710), State (0x6760a80, Q+0x750 stride 0x58), TransformVariant (0x6760e60 x2, Q+0x648), record 0xC8 copy into Q+8 vector (0xeec6ec0 / grow 0x5aba6d0), thread scope exit with saved byte, then destroy DrawArgs locals: 0x66a9ad0(&rbp+0x340), variant-3 shared_ptr at rbp+0x510, loop shared_ptr release over vector at rbp+0x4e8..0x4f0 (stride 0x28, tag byte +0x18==2), 0x1751590(&rbp+0x170) (mesh header dtor), optional string free (rbp+0x160==1, big-alloc form), exit 0x665aee8 -> 0x665d124 (common epilogue).
Status: Stars DONE at statement level; byte-exact field copies of the 0x40-byte payload variants and the 0x665c269/0x665c38a/0x665b624 joins are listed by destination only -> NOT instruction-complete; OPEN: those three joins (~300 instr) plus helper tails (4de9fa0 0x4dea2b4.., e86b370 0xe86b43a.., bcaba00 body). Sky (0x66574d8) and SunMoon (0x665935d) reuse C/D with the Material "Sky"/"SunMoon(ForwardPBR)" and desc offsets from RenderSkyDescription / RenderCelestialBodyDescription (Descriptions.h lines 845/852).
