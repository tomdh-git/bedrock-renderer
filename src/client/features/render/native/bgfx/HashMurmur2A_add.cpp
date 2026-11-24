// LIFT 0xbc76610 size 0x1dc 1.26.62.01 bx::HashMurmur2A::add(data, len)
#include "client/features/render/native/bgfx/HashMurmur2A_add.h"

#include <cstdint>
#include <cstring>

#include "client/features/render/native/Lift.h"

namespace native::bgfx {

// Layout assertions for the struct offsets the lifted body reads/writes
// (same constants as HashMurmur2A_add.h; asserted here too per liftcheck).
static_assert(offsetof(HashMurmur2A, m_hash) == 0x00, "bc76610: m_hash at +0x00");
static_assert(offsetof(HashMurmur2A, m_tail) == 0x04, "bc76610: m_tail at +0x04");
static_assert(offsetof(HashMurmur2A, m_nbytesInTail) == 0x08, "bc76610: m_nbytesInTail at +0x08");
static_assert(offsetof(HashMurmur2A, m_nbytes) == 0x0C, "bc76610: m_nbytes at +0x0C");
static_assert(sizeof(HashMurmur2A) == 0x10, "bc76610: HashMurmur2A state is 0x10 bytes");


namespace {

// MurmurHash2A 32-bit mixer constant, immediate 0x5BD1E995 at
// 0xbc76683, 0xbc76693, 0xbc766c0, 0xbc766d0, 0xbc76700, 0xbc76710,
// 0xbc76724, 0xbc76735, 0xbc767ac, 0xbc767bc.
static constexpr uint32_t kHashMurmur2AMul = 0x5BD1E995u;

// Mix one 4-byte block into the running hash, in place:
//   k *= 0x5BD1E995; k ^= k >> 24; k *= 0x5BD1E995;
//   hash *= 0x5BD1E995; hash ^= k;
// Mirrors the instruction pairs imul/shr/xor/imul/imul/xor at the addresses above.
static inline void mixHash(uint32_t& hash, uint32_t k)
{
    k *= kHashMurmur2AMul;
    k ^= k >> 24;
    k *= kHashMurmur2AMul;
    hash *= kHashMurmur2AMul;
    hash ^= k;
}

// 32-bit little-endian read at p, exactly as the original's dword reads
// (imul ecx,[rdx],0x5BD1E995 / imul ecx,[rdx+4],0x5BD1E995). x64 allows
// unaligned dword reads, so this is a single 4-byte read at the given address.
static inline uint32_t readDword(const uint8_t* p)
{
    uint32_t v;
    std::memcpy(&v, p, 4);
    return v;
}

} // namespace

extern "C" void HashMurmur2A_add(HashMurmur2A* self, const void* data, uint32_t len)
{
    // 0xbc76610..0xbc7661e
    //   0xbc76610  push rsi
    //   0xbc76611  push rbx
    //   0xbc76612  mov rax,rcx          rax = this
    //   0xbc76615  test dl,3            data pointer low two bits (alignment)
    //   0xbc76618  jne 0xBC767E2        unaligned data -> tail-call clone at 0xbc767f0
    HashMurmur2A* const self_ = self;
    const uint8_t* const ptr0 = reinterpret_cast<const uint8_t*>(data);
    const bool unaligned = (reinterpret_cast<uintptr_t>(data) & 3u) != 0u;
    if (unaligned)
    {
        // 0xbc767e2  mov rcx,rax
        // 0xbc767e5  pop rbx
        //   0xbc767e6  pop rsi
        //   0xbc767e7  jmp 0xBC767F0
        // Tail-call to the unaligned-data clone at 0xbc767f0. The clone is a
        // verbatim copy of this same body: identical state reads/writes in the
        // same order, no calls, same pop/pop/ret epilogue (0xbc769af..0xbc769b1),
        // and it returns to this function's caller directly. Running the shared
        // body below is therefore behaviorally identical for both alignment
        // paths; there is no call to resolve here.
    }

    // 0xbc7661e  add [rax+0xC],r8d      m_nbytes += len
    self_->m_nbytes += len;

    // 0xbc76622  test r8d,r8d
    //   0xbc76625  je 0xBC767DF         len == 0 -> return
    if (len == 0u)
        return;

    // 0xbc7662b  mov r9d,[rax]          hash = m_hash
    //   0xbc7662e  mov r10d,[rax+4]     tail = m_tail
    //   0xbc76632  mov r11d,[rax+8]     count = m_nbytesInTail
    //   0xbc76636  jmp short 0xBC7664F  -> loop head L1
    //   0xbc76638  nop [rax+rax]        unreached alignment pad inside the function
    uint32_t hash = self_->m_hash;
    uint32_t tail = self_->m_tail;
    uint32_t count = self_->m_nbytesInTail;
    const uint8_t* ptr = ptr0;
    uint32_t rem = len;

// 0xbc7664f..0xbc76663   loop head L1
//   0xbc7664f  cmp r8d,4              ; setge cl     rem >= 4
//   0xbc76656  test r11d,r11d         ; sete bl      count == 0
//   0xbc7665c  and bl,cl
//   0xbc7665e  cmp bl,1
//   0xbc76661  je short 0xBC766B6     rem >= 4 && count == 0 -> DIRECT
L1:
    if (rem >= 4u && count == 0u)
        goto DIRECT;

    // 0xbc76663..0xbc76683   fill the tail word byte by byte, little-endian
    //   0xbc76663  movzx esi,byte ptr [rdx]
    //   0xbc76666  lea ecx,[r11*8]          shift = count * 8 (only CL is used by shl)
    //   0xbc7666e  shl esi,cl
    //   0xbc76670  or esi,r10d
    //   0xbc76673  mov [rax+4],esi          m_tail = tail | (*ptr << (count*8))
    //   0xbc76676  inc r11d
    //   0xbc76679  mov [rax+8],r11d         m_nbytesInTail = count + 1
    //   0xbc7667d  cmp r11d,4
    //   0xbc76681  jne short 0xBC76640      count+1 != 4 -> loop bottom BOTTOM
    tail = tail | (static_cast<uint32_t>(*ptr) << (count * 8u));
    self_->m_tail = tail;
    count++;
    self_->m_nbytesInTail = count;
    if (count != 4u)
        goto BOTTOM;
    goto MIX;

// 0xbc76683..0xbc766b6   mix the full tail word into the hash, then reset tail/count
MIX:
    //   0xbc76683  imul ecx,esi,0x5BD1E995
    //   0xbc76689  mov r10d,ecx
    //   0xbc7668c  shr r10d,0x18
    //   0xbc76690  xor r10d,ecx
    //   0xbc76693  imul ecx,r10d,0x5BD1E995
    //   0xbc7669a  imul r9d,0x5BD1E995
    //   0xbc766a1  xor r9d,ecx
    //   0xbc766a4  mov [rax],r9d          m_hash = hash
    //   0xbc766a7  mov qword ptr [rax+4],0   m_tail = 0; m_nbytesInTail = 0
    //   0xbc766af  xor esi,esi
    //   0xbc766b1  xor r11d,r11d
    //   0xbc766b4  jmp short 0xBC76640    -> loop bottom BOTTOM
    mixHash(hash, tail);
    self_->m_hash = hash;
    tail = 0u;
    count = 0u;
    self_->m_tail = 0u;
    self_->m_nbytesInTail = 0u;
    goto BOTTOM;

// 0xbc76640..0xbc7664f   loop bottom: advance pointer, drop remaining byte count
//   0xbc76640  inc rdx
//   0xbc76643  mov r10d,esi           register copy of tail
//   0xbc76646  dec r8d
//   0xbc76649  je 0xBC767DF           rem == 0 -> return
BOTTOM:
    ptr++;
    rem--;
    if (rem == 0u)
        return;
    goto L1;

// 0xbc766b6..0xbc766c0   DIRECT: rem >= 4 and count == 0
DIRECT:
    //   0xbc766b6  lea r11d,[r8-4]
    //   0xbc766ba  test r11b,4
    //   0xbc766be  jne short 0xBC766EB  (rem - 4) & 4 != 0 -> LOOP8
    {
        uint32_t rem4 = rem - 4u;      // r11d
        if ((rem4 & 4u) != 0u)
            goto LOOP8;                // r8d still = rem
        // 0xbc766c0..0xbc766e8   mix one dword from the data
        //   0xbc766c0  imul ecx,[rdx],0x5BD1E995
        //   0xbc766c6  mov r8d,ecx
        //   0xbc766c9  shr r8d,0x18
        //   0xbc766cd  xor r8d,ecx
        //   0xbc766d0  imul ecx,r8d,0x5BD1E995
        //   0xbc766d7  imul r9d,0x5BD1E995
        //   0xbc766de  xor r9d,ecx
        //   0xbc766e1  mov [rax],r9d      m_hash = hash
        //   0xbc766e4  add rdx,4
        //   0xbc766e8  mov r8d,r11d       rem = rem4
        uint32_t k = readDword(ptr);
        mixHash(hash, k);
        self_->m_hash = hash;
        ptr += 4;
        rem = rem4;
    }

// 0xbc766eb..0xbc76758   LOOP8: mix two dwords per iteration. The bottom check uses
//   the pre-subtraction remaining (cmp r8d,0xB / jg), so for rem == 12 the second
//   iteration reads a dword 4 bytes past the end of the caller's buffer - the
//   original does exactly that (bounded over-read, then the wrapped remainder
//   exits through the rem >= 4 branch in TAIL_BYTE).
LOOP8:
    //   0xbc766eb  cmp r11d,4
    //   0xbc766ef  jb short 0xBC7675A   rem < 4 -> tail finalization TAIL_FINAL
    if (rem < 4u)
        goto TAIL_FINAL;

    //   0xbc76700  imul ecx,[rdx],0x5BD1E995      mix *ptr
    //   0xbc76706  mov r11d,ecx
    //   0xbc76709  shr r11d,0x18
    //   0xbc7670d  xor r11d,ecx
    //   0xbc76710  imul ecx,r11d,0x5BD1E995
    //   0xbc76717  imul r9d,0x5BD1E995
    //   0xbc7671e  xor r9d,ecx
    //   0xbc76721  mov [rax],r9d          m_hash = hash
    //   0xbc76724  imul ecx,[rdx+4],0x5BD1E995    mix *(ptr+4)
    //   0xbc7672b  mov r11d,ecx
    //   0xbc7672e  shr r11d,0x18
    //   0xbc76732  xor r11d,ecx
    //   0xbc76735  imul ecx,r11d,0x5BD1E995
    //   0xbc7673c  imul r9d,0x5BD1E995
    //   0xbc76743  xor r9d,ecx
    //   0xbc76746  mov [rax],r9d          m_hash = hash
    //   0xbc76749  add rdx,8
    //   0xbc7674d  lea r11d,[r8-8]
    //   0xbc76751  cmp r8d,0xB          pre-subtraction remaining vs 11
    //   0xbc76755  mov r8d,r11d
    //   0xbc76758  jg short 0xBC76700   old rem > 11 -> another iteration
    {
        uint32_t k = readDword(ptr);
        mixHash(hash, k);
        self_->m_hash = hash;
    }
    {
        uint32_t k = readDword(ptr + 4);
        mixHash(hash, k);
        self_->m_hash = hash;
    }
    {
        uint32_t old = rem;
        ptr += 8;
        rem -= 8;
        if (old > 11u)
            goto LOOP8;
    }
    goto TAIL_FINAL;

// 0xbc7675a..0xbc7677b   TAIL_FINAL: rem == 0 -> return, else start the byte tail
TAIL_FINAL:
    //   0xbc7675a  test r11d,r11d
    //   0xbc7675d  je 0xBC767DF         rem == 0 -> return
    //   0xbc76763  xor r8d,r8d          count = 0
    //   0xbc76766  jmp short 0xBC7677B
    if (rem == 0u)
        return;
    count = 0u;
    goto TAIL_BYTE;

// 0xbc7677b..0xbc7678c   TAIL_BYTE head
//   0xbc7677b  cmp r11d,4             ; setge cl      rem >= 4
//   0xbc76782  test r8d,r8d           ; sete bl       count == 0
//   0xbc76788  test cl,bl
//   0xbc7678a  jne short 0xBC767DF    rem >= 4 && count == 0 -> return
//            (taken only on the wrapped-remainder pathology, e.g. len == 12)
TAIL_BYTE:
    if (rem >= 4u && count == 0u)
        return;

    // 0xbc7678c..0xbc767ac   fill the tail byte by byte
    //   0xbc7678c  movzx esi,byte ptr [rdx]
    //   0xbc7678f  lea ecx,[r8*8]
    //   0xbc76797  shl esi,cl
    //   0xbc76799  or esi,r10d
    //   0xbc7679c  mov [rax+4],esi          m_tail = tail | (*ptr << (count*8))
    //   0xbc7679f  inc r8d
    //   0xbc767a2  mov [rax+8],r8d         m_nbytesInTail = count + 1
    //   0xbc767a6  cmp r8d,4
    //   0xbc767aa  jne short 0xBC76770    count+1 != 4 -> bottom2 BOTTOM2
    tail = tail | (static_cast<uint32_t>(*ptr) << (count * 8u));
    self_->m_tail = tail;
    count++;
    self_->m_nbytesInTail = count;
    if (count != 4u)
        goto BOTTOM2;
    goto MIX_TAIL;

// 0xbc767ac..0xbc767e1   MIX_TAIL: mix the tail word into the hash, reset, -> BOTTOM2
MIX_TAIL:
    //   0xbc767ac  imul ecx,esi,0x5BD1E995
    //   0xbc767b2  mov r8d,ecx
    //   0xbc767b5  shr r8d,0x18
    //   0xbc767b9  xor r8d,ecx
    //   0xbc767bc  imul ecx,r8d,0x5BD1E995
    //   0xbc767c3  imul r9d,0x5BD1E995
    //   0xbc767ca  xor r9d,ecx
    //   0xbc767cd  mov [rax],r9d          m_hash = hash
    //   0xbc767d0  mov qword ptr [rax+4],0   m_tail = 0; m_nbytesInTail = 0
    //   0xbc767d8  xor esi,esi
    //   0xbc767da  xor r8d,r8d
    //   0xbc767dd  jmp short 0xBC76770    -> BOTTOM2
    mixHash(hash, tail);
    self_->m_hash = hash;
    tail = 0u;
    count = 0u;
    self_->m_tail = 0u;
    self_->m_nbytesInTail = 0u;
    goto BOTTOM2;

// 0xbc76770..0xbc7677b   BOTTOM2: advance pointer, drop remaining byte count
//   0xbc76770  inc rdx
//   0xbc76773  mov r10d,esi           register copy of tail
//   0xbc76776  dec r11d
//   0xbc76779  je short 0xBC767DF     rem == 0 -> return
BOTTOM2:
    ptr++;
    rem--;
    if (rem == 0u)
        return;
    goto TAIL_BYTE;

// 0xbc767df..0xbc767e1   epilogue
    //   0xbc767df  pop rbx
    //   0xbc767e0  pop rsi
    //   0xbc767e1  ret
    return;
}

LIFT_FN(HashMurmur2A_add, "bx::HashMurmur2A::add(data, len)", 0xbc76610, HashMurmur2A_add, nullptr);

} // namespace native::bgfx
