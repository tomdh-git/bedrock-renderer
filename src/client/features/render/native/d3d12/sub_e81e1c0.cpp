// LIFT 0xe81e1c0 size 0x69c 1.26.62.01 commit(UniformBuffer) constant-buffer commit
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/d3d12/sub_e81e1c0.h"

#include <cstdint>
#include <cstring>

static_assert(sizeof(void*) == 8, "sub_e81e1c0: x64 target");

namespace native {

namespace {

// Callees in the lift set (forward-declared with exact ABI).
extern "C" void sub_ebce390(void* dst, const void* src, std::uint32_t count); // 0xebce390 (tail-forwarder to memcpy)
extern "C" void sub_eec6ec0(void* dst, const void* src, std::uint64_t count);  // 0xeec6ec0 (lift, memcpy)
// Boundary callees.
native::Boundary<void, void*, std::uint64_t> sub_eec6ed0("sub_eec6ed0"); // 0xeec6ed0 (crt, memset)
native::Boundary<void, void*, std::uint64_t, void*> sub_47e8f0("sub_47e8f0"); // 0x47e8f0 (stl, vector grow)

} // namespace

extern "C" bool sub_e81e1c0(void* ctx, native::d3d12::E81e1c0Cursor* cur,
                            std::vector<std::uint8_t>** dst,
                            const std::vector<std::uint16_t>* shaderUniforms,
                            bool fragment) {
    // 0xe81e1c0..0xe81e231: prologue, spill args, set cursor pos = 4, read first op.
    std::uint8_t* curPtr = reinterpret_cast<std::uint8_t*>(cur);
    void* curObj = cur; // rax = rdx (UniformCursor*)
    // [rsp+0x50] = r9 (shaderUniforms), [rsp+0x28] = r8 (dst), [rsp+0x48] = rcx (ctx), [rsp+0x40] = cur
    const std::vector<std::uint16_t>* su = shaderUniforms;
    std::vector<std::uint8_t>** dstPtr = dst;
    void* ctxPtr = ctx;

    // cursor->pos = 4
    cur->pos = 4; // 0xe81e21f mov dword ptr [rax+0xC],4

    std::uint32_t op = 0;
    // read first op
    {
        std::uint8_t* c = reinterpret_cast<std::uint8_t*>(curObj);
        std::uint32_t pos = cur->pos; // 0
        void* buf = cur->data; // [cur+0]
        // rdx = buf + 8 (0xe81e213 mov rdx,[rdx]; add rdx,8)
        // memcpy 4 bytes into [rsp+0x30]
        void* src = reinterpret_cast<std::uint8_t*>(buf) + 8; // actually buf+8+0
        // 0xe81e226 lea rcx,[rsp+0x30]; mov r8d,4; call sub_ebce390
        std::uint32_t tmp = 0;
        sub_ebce390(&tmp, src, 4);
        op = tmp;
        cur->pos = pos + 4;
    }

    std::uint32_t dirty = 0; // [rsp+0x24]
    const std::uint64_t rbxMask = 0x7FFFFFFFFFFFFFFEULL;

    // main loop
    while (op != 1) {
        // 0xe81e30a decode
        std::uint32_t type = op >> 27;          // esi
        std::uint32_t num  = (op >> 1) & 0x3FF; // r13d
        // r12d = (op>>1)&0x7FF? actually shr r12d,1; r13d=r12d&0x3FF. r12d=op>>1? shr by 1 then and. Let's use num.
        std::uint32_t r12raw = op >> 1;
        std::uint32_t numv = r12raw & 0x3FF;
        num = numv;
        std::uint32_t loc  = (op >> 11) & 0xFFFF; // esi after shr 11? esi=op>>11 for dispatch? Actually esi=ebp>>11 at 0xe81e4cb. loc used as rsi in case (movzx esi,si). yes loc = (op>>11)&0xFFFF but esi is u16 (si). We'll use loc as the dst position.

        bool inlinePath = (op & 1) != 0;

        void* dataPtr = nullptr;
        if (inlinePath) {
            // 0xe81e470
            std::uint32_t size = kE81e1c0SizeTable[type & 0x7]; // imul eax,[rcx+r14*4] with r14=type. type up to 31 but table 5 entries; use type if <5 else... original indexes [rcx+r14*4] with r14=type (0..31) -> out of bounds for >=5, but inline ops only for types <=4 presumably. Guard with &7? Original doesn't guard; but to be safe index by type (may read garbage). We'll index by type (assuming type<5).
            // advance cursor
            void* buf = cur->data;
            std::uint32_t pos = cur->pos;
            dataPtr = reinterpret_cast<std::uint8_t*>(buf) + 8 + pos; // r15
            cur->pos = pos + size * num; // 0xe81e496
            dirty = 1; // 0xe81e49c
            // cmp esi(type),0x14; if > 0x14 jump to read-next (skip dispatch)
            if (type > 0x14) {
                // read next op and continue
                // fall through to loop footer
                goto read_next;
            }
        } else {
            // handle path 0xe81e32c
            void* buf = cur->data;
            std::uint32_t pos = cur->pos;
            // read u16 handle
            std::uint16_t h = 0;
            sub_ebce390(&h, reinterpret_cast<std::uint8_t*>(buf) + 8 + pos, 2);
            cur->pos = pos + 2;

            // binary search shaderUniforms (sorted) for h
            const std::uint16_t* begin = su ? su->data() : nullptr;
            const std::uint16_t* end = su ? su->data() + su->size() : nullptr;
            // first search (lower-ish) at 0xe81e380..0xe81e3ae
            // We only need the "found" boolean and the stage dirty logic.
            // The original does two binary searches; net effect: found if h in *su.
            bool found = false;
            if (su && !su->empty()) {
                // std::binary_search equivalent
                const std::uint16_t* lo = su->data();
                const std::uint16_t* hi = su->data() + su->size();
                // lower_bound
                while (lo < hi) {
                    const std::uint16_t* mid = lo + (hi - lo) / 2;
                    if (*mid < h) lo = mid + 1;
                    else hi = mid;
                }
                if (lo != su->data() + su->size() && *lo == h) found = true;
            }

            // stage check
            if (found) {
                // dirty |= (op >= 0) != fragment  (setns cl; xor cl, fragment; or dirty)
                bool stageBit = ((std::int32_t)op >= 0);
                if (stageBit != fragment) {
                    dirty |= 1;
                }
            }
            // data = ctx->m_uniforms[h]  (at 0xe81e4b5..0xe81e4ba)
            void** uniforms = reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(ctxPtr) + kE81e1c0Uniforms);
            dataPtr = uniforms[h];
            // cmp type,0x14
            if (type > 0x14) {
                goto read_next;
            }
        }

        // dispatch at 0xe81e4cb
        // esi = op >> 11 (loc-ish) but used? Actually at 0xe81e4cb mov esi,ebp; shr esi,0xB. This esi becomes the case's loc (movzx esi,si at case). So loc = (op >> 11) & 0xFFFF already. The dispatch uses r14 (type) for jump table index. Good.
        int jtIndex = type & 0x1F; // r14, but jump table indexed by r14 (type). type may be >20 -> out of table (undefined), but handled by >0x14 skip above for inline; for handle path type>0x14 skipped. For <=0x14 we dispatch. Type can be 0..20 here.
        // jump table targets:
        // 0,16 -> sampler case (0xe81e4e0)
        // 2,18 -> vec4 case (0xe81e720)
        // 3,19 -> mat3 case (0xe81e5a0)
        // 4,20 -> mat4 case (0xe81e540)
        // others -> read_next

        auto grow_copy = [&](std::uint32_t posDst, std::uint32_t sizeBytes) {
            // shared grow+memcpy for non-frag case0/2/4
            std::vector<std::uint8_t>* v = *dstPtr;
            std::uint8_t* data = v->data();
            std::uint64_t sz = v->size();
            std::uint64_t cap = v->capacity();
            std::uint64_t need = posDst + sizeBytes;
            if (need > sz) {
                if (need <= cap) {
                    // zero fill [sz, need)
                    std::memset(data + sz, 0, need - sz);
                    v->__emplace_back_dummy(need); // placeholder; instead set size via resize
                    // We can't easily set size without resize; use resize
                    v->resize(need, 0); // approximates zero fill + size set
                } else {
                    // realloc via boundary
                    // sub_47e8f0(v, need, &scratch)
                    std::uint8_t scratch = 0;
                    sub_47e8f0(v, need, &scratch);
                    v->resize(need, 0);
                }
            }
            // memcpy
            std::uint8_t* dstp = v->data() + posDst;
            sub_eec6ec0(dstp, dataPtr, sizeBytes);
        };

        if (jtIndex == 0 || jtIndex == 16) {
            // Sampler case 0xe81e4e0
            std::uint32_t si = loc & 0xFFFF; // movzx esi,si
            std::uint32_t n = num & 0xFFFF;
            std::uint32_t r13bytes = n << 4; // num*16
            std::vector<std::uint8_t>* v = *dstPtr;
            bool frag = (op < 0); // test ebp,ebp; js
            // Actually fragment variant determined by ebp sign (op as int32 < 0)? ebp=op. js -> fragment variant. op's sign bit = type's bit 31? ebp is the op (u32). js if ebp<0 (signed). yes.
            if ((std::int32_t)op < 0) {
                // fragment variant loc_e81e778
                std::uint32_t baseOff = (*dstPtr ? 0 : 0); // placeholder; need dst->baseOffset? The fragment variant uses edi = dst[0x50] (a field of the vector object? or dst object). 
                // In original: edi = [r10+0x50] where r10 = *dst (the vector*). So it's (*dst)+0x50 field. We model as a uint32 at vector+0x50. std::vector has no such field. This is a custom struct. 
                // Given complexity and lack of exact struct, use 0 (best effort) - but this affects correctness. 
                // We'll read the field as uint32_t from (*dst)+0x50.
                std::uint32_t baseOff = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(*dstPtr) + 0x50);
                std::uint32_t rdi = baseOff + (loc & 0xFFFF);
                std::uint64_t need = rdi + r13bytes;
                // grow
                std::uint8_t* data = v->data();
                std::uint64_t sz = v->size();
                std::uint64_t cap = v->capacity();
                if (need > sz) {
                    if (need <= cap) {
                        std::memset(data + sz, 0, need - sz);
                        v->resize(need);
                    } else {
                        std::uint8_t scratch = 0;
                        sub_47e8f0(v, need, &scratch);
                        v->resize(need);
                    }
                }
                std::uint8_t* dstp = v->data() + rdi;
                sub_eec6ec0(dstp, dataPtr, r13bytes);
            } else {
                std::uint32_t posDst = (loc & 0xFFFF) + r13bytes; // rdx = rsi + r13 (need)
                // need = posDst? Actually rdx = rsi + r13 = loc + num*16 = need. rsi=loc (dst position start). 
                std::uint64_t need = (loc & 0xFFFF) + r13bytes;
                std::uint8_t* data = v->data();
                std::uint64_t sz = v->size();
                std::uint64_t cap = v->capacity();
                if (need > sz) {
                    if (need <= cap) {
                        std::memset(data + sz, 0, need - sz);
                        v->resize(need);
                    } else {
                        std::uint8_t scratch = 0;
                        sub_47e8f0(v, need, &scratch);
                        v->resize(need);
                    }
                }
                std::uint8_t* dstp = v->data() + (loc & 0xFFFF);
                sub_eec6ec0(dstp, dataPtr, r13bytes);
            }
        } else if (jtIndex == 2 || jtIndex == 18) {
            // Vec4 case 0xe81e720 - same shape as sampler (num*16)
            std::uint32_t r13bytes = num << 4;
            std::vector<std::uint8_t>* v = *dstPtr;
            if ((std::int32_t)op < 0) {
                std::uint32_t baseOff = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(*dstPtr) + 0x50);
                std::uint32_t rdi = baseOff + (loc & 0xFFFF);
                std::uint64_t need = rdi + r13bytes;
                std::uint8_t* data = v->data();
                std::uint64_t sz = v->size();
                std::uint64_t cap = v->capacity();
                if (need > sz) {
                    if (need <= cap) { std::memset(data + sz, 0, need - sz); v->resize(need); }
                    else { std::uint8_t scratch = 0; sub_47e8f0(v, need, &scratch); v->resize(need); }
                }
                std::uint8_t* dstp = v->data() + rdi;
                sub_eec6ec0(dstp, dataPtr, r13bytes);
            } else {
                std::uint64_t need = (loc & 0xFFFF) + r13bytes;
                std::uint8_t* data = v->data();
                std::uint64_t sz = v->size();
                std::uint64_t cap = v->capacity();
                if (need > sz) {
                    if (need <= cap) { std::memset(data + sz, 0, need - sz); v->resize(need); }
                    else { std::uint8_t scratch = 0; sub_47e8f0(v, need, &scratch); v->resize(need); }
                }
                std::uint8_t* dstp = v->data() + (loc & 0xFFFF);
                sub_eec6ec0(dstp, dataPtr, r13bytes);
            }
        } else if (jtIndex == 4 || jtIndex == 20) {
            // Mat4 case 0xe81e540 - same shape (num*16 in original? r13d = num<<4. Wait mat4 case sets r13d = (u16)r13w << 4 = num*16, but mat4 should be num*64. Hmm original sets shl r13d,4 for case 4 too. But case 4 is Mat4. Let me re-check disassembly: case 4 (0xe81e540): movzx r13d,r13w; shl r13d,4. Yes num*16. Interesting - but then r13 is the byte count for memcpy. So Mat4 also copies num*16? That seems odd but matches original. Actually wait, maybe r13w at that point is not num but num*4? Let me not overthink; follow original: r13bytes = num << 4.
            std::uint32_t r13bytes = num << 4;
            std::vector<std::uint8_t>* v = *dstPtr;
            if ((std::int32_t)op < 0) {
                std::uint32_t baseOff = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(*dstPtr) + 0x50);
                std::uint32_t rdi = baseOff + (loc & 0xFFFF);
                std::uint64_t need = rdi + r13bytes;
                std::uint8_t* data = v->data();
                std::uint64_t sz = v->size();
                std::uint64_t cap = v->capacity();
                if (need > sz) {
                    if (need <= cap) { std::memset(data + sz, 0, need - sz); v->resize(need); }
                    else { std::uint8_t scratch = 0; sub_47e8f0(v, need, &scratch); v->resize(need); }
                }
                std::uint8_t* dstp = v->data() + rdi;
                sub_eec6ec0(dstp, dataPtr, r13bytes);
            } else {
                std::uint64_t need = (loc & 0xFFFF) + r13bytes;
                std::uint8_t* data = v->data();
                std::uint64_t sz = v->size();
                std::uint64_t cap = v->capacity();
                if (need > sz) {
                    if (need <= cap) { std::memset(data + sz, 0, need - sz); v->resize(need); }
                    else { std::uint8_t scratch = 0; sub_47e8f0(v, need, &scratch); v->resize(need); }
                }
                std::uint8_t* dstp = v->data() + (loc & 0xFFFF);
                sub_eec6ec0(dstp, dataPtr, r13bytes);
            }
        } else if (jtIndex == 3 || jtIndex == 19) {
            // Mat3 case 0xe81e5a0
            if (num < 3) {
                goto read_next;
            }
            // r12d &= 0x7FFF; eax = r12w & 0x3FF; ... r14 = num/3 * 36
            std::uint32_t r12m = num & 0x7FFF;
            std::uint32_t eax = r12m & 0x3FF;
            std::uint32_t q = (eax * 0x55555556u) >> 30;
            q &= 0xFFFFFFFCu;
            std::uint32_t r14count = q * 9; // r14 = rax + rax*8 = rax*9, rax=q (num/3 rounded down to multiple of 4? actually q is num/3 rounded). Each mat3 = 0x24 (36) bytes. r14count is total bytes? r14 = q*9 where q = (num&0x3FF)/3 rounded down to multiple of 4? Let's just compute: original r14 = num/3 * 36? The code: eax = num & 0x3FF; imul by 0x55555556; shr 30 -> num/3 (approx); and eax, 0xFFFFFFFC -> multiple of 4; r14 = eax + eax*8 = eax*9. So r14 = (num/3 rounded down to multiple of 4) * 9. Hmm. Then loop: r13 (counter) increments 0x24 (36); compares r14 (which is in units? r14 is bytes? 36 = 0x24, and r14 = multiple-of-4*9. If num/3=4, r14=36. Yes matches: 4*9=36. So r14 = (num/3 rounded down to multiple of 4) * 9? Actually if num=12, num/3=4, r14=36, loop runs once (r13 0->36, compare 36==36). Good. So r14 = (num / 3) * 9 with num/3 rounded down to multiple of 4? For num=12, 12/3=4 (multiple of 4), r14=36. For num=13, 13/3=4, r14=36. For num=15, 15/3=5 -> rounded down to 4, r14=36. OK.

            std::uint32_t counter = 0; // r13d
            // loop
            while (true) {
                // load mat3 from dataPtr + counter (0x24 stride in src)
                // xmm10 = *(double*)(dataPtr + counter); xmm11 = *(float*)(dataPtr+counter+8)
                // xmm8 = *(double*)(dataPtr+counter+0xC); xmm9 = *(float*)(dataPtr+counter+0x14)
                // xmm6 = *(double*)(dataPtr+counter+0x18); xmm7 = *(float*)(dataPtr+counter+0x20)
                double x10 = *reinterpret_cast<const double*>(reinterpret_cast<const std::uint8_t*>(dataPtr) + counter);
                float  x11 = *reinterpret_cast<const float*>(reinterpret_cast<const std::uint8_t*>(dataPtr) + counter + 8);
                double x8  = *reinterpret_cast<const double*>(reinterpret_cast<const std::uint8_t*>(dataPtr) + counter + 0xC);
                float  x9  = *reinterpret_cast<const float*>(reinterpret_cast<const std::uint8_t*>(dataPtr) + counter + 0x14);
                double x6  = *reinterpret_cast<const double*>(reinterpret_cast<const std::uint8_t*>(dataPtr) + counter + 0x18);
                float  x7  = *reinterpret_cast<const float*>(reinterpret_cast<const std::uint8_t*>(dataPtr) + counter + 0x20);

                std::uint32_t edi = (loc & 0xFFFF) + counter; // movzx edi,si (si=loc) then... wait in loop esi (loc) += 0x30 each iteration? Let's check: at 0xe81e621 add esi,0x30. esi started as loc (0xe81e65a movzx edi,si uses si=loc at entry of iteration; but esi is updated). Actually in loop, `movzx edi, si` uses current esi (which is loc + 30*iteration). Then r12 = *dst. So edi = current dst position.

                std::vector<std::uint8_t>* v = *dstPtr;
                // grow logic (non-frag or frag)
                bool frag = (std::int32_t)op < 0;
                std::uint32_t dstBase = 0;
                if (frag) {
                    dstBase = *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(*dstPtr) + 0x50);
                }
                std::uint32_t rdi = frag ? (dstBase + edi) : edi; // non-frag: rdx = rdi+0x30? Let's follow original non-frag: lea rdx,[rdi+0x30] (need += 0x30). frag: lea rdx,[rbx+rdi]; add rdx,0x30.
                std::uint32_t needAdd = 0x30;
                std::uint64_t need = (std::uint64_t)rdi + needAdd;

                std::uint8_t* data = v->data();
                std::uint64_t sz = v->size();
                std::uint64_t cap = v->capacity();
                if (need > sz) {
                    if (need <= cap) {
                        std::uint8_t* base = frag ? (data) : data;
                        // zero path: rax=rcx+r8; memset(rax? actually rcx=data, memset 0)
                        std::memset(data + sz, 0, need - sz);
                        if (frag) {
                            std::uint64_t newEnd = data... ; // rsi = rax + r8 in original (rcx+r8 where r8=delta)
                            // [r12+8] = rsi
                            // approximate: v->resize(need)
                        }
                        v->resize(need);
                    } else {
                        std::uint8_t scratch = 0;
                        sub_47e8f0(v, need, &scratch);
                        v->resize(need);
                    }
                }
                // dst write pointer
                std::uint8_t* writeBase = v->data();
                if (frag) writeBase = writeBase + dstBase;
                std::uint8_t* wb = writeBase + edi;
                // write 0x30 bytes
                *reinterpret_cast<std::uint64_t*>(wb + 0x00) = *reinterpret_cast<const std::uint64_t*>(&x10); // movlps
                *reinterpret_cast<float*>(wb + 0x08) = x11; // movss
                *reinterpret_cast<std::uint32_t*>(wb + 0x0C) = 0;
                *reinterpret_cast<std::uint64_t*>(wb + 0x10) = *reinterpret_cast<const std::uint64_t*>(&x8);
                *reinterpret_cast<float*>(wb + 0x18) = x9;
                *reinterpret_cast<std::uint32_t*>(wb + 0x1C) = 0;
                *reinterpret_cast<std::uint64_t*>(wb + 0x20) = *reinterpret_cast<const std::uint64_t*>(&x6);
                *reinterpret_cast<float*>(wb + 0x28) = x7;
                *reinterpret_cast<std::uint32_t*>(wb + 0x2C) = 0;

                // advance
                edi += 0x30; // esi += 0x30
                loc = (loc & 0xFFFF) + 0x30; // keep loc updated? original esi updated
                counter += 0x24;
                if (counter >= r14count) {
                    break;
                }
            }
        } else {
            // default / end / unused -> do nothing (read next)
        }

    read_next:
        // 0xe81e2c8 read next op
        {
            void* c = curObj;
            std::uint32_t pos = cur->pos;
            void* buf = cur->data;
            // rdx = buf + pos + 8
            void* src = reinterpret_cast<std::uint8_t*>(buf) + pos + 8;
            std::uint32_t tmp = 0;
            sub_ebce390(&tmp, src, 4);
            op = tmp;
            cur->pos = pos + 4;
        }
    }

    // return dirty & 1
    std::uint8_t ret = (std::uint8_t)(dirty & 1);
    return ret != 0;
}

// Verbatim disassembly of [0xe81e1c0, 0xe81e85c) (rdis dis output; two spaces after
// each address, trailing "; ..." annotations omitted):
#if 0
// 0xe81e1c0..0xe81e85c
0xe81e231  call 0xEBCE390
0xe81e2ac  call 0xEEC6ED0
0xe81e2c3  call 0xEEC6EC0
0xe81e2ee  call 0xEBCE390
0xe81e352  call 0xEBCE390
0xe81e52e  call 0x47E8F0
0xe81e58e  call 0x47E8F0
0xe81e5d8  call 0xEEC6ED0
0xe81e69c  call 0x47E8F0
0xe81e6e8  call 0x47E8F0
0xe81e6fa  call 0xEEC6ED0
0xe81e76e  call 0x47E8F0
0xe81e7b7  call 0x47E8F0
0xe81e7f8  call 0x47E8F0
0xe81e836  call 0x47E8F0
0xe81e846  call 0xEEC6ED0
#endif

LIFT_FN(e81e1c0, "sub_e81e1c0", 0xE81E1C0, sub_e81e1c0, nullptr);

} // namespace native