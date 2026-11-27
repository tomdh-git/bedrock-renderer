// LIFT 0xbc76e80 size 0x36f 1.26.62.01 bgfx destroy-queue drain/notify

#include "client/features/render/native/bgfx/sub_bc76e80.h"

#include <cstddef>
#include <cstdint>
#include "client/features/render/native/Lift.h"

namespace native::bgfx {

namespace {

// sub_eea6040 is a vendor boundary thunk (docs/data/native_boundary.tsv row:

// "0xeea6040 vendor thunk via data slot 0xF99FFA0 (loader-resolved)"). The original

// does `call qword ptr [0xF99FFA0]` three times; read the pointer from the slot at

// every call, exactly as the instruction does, and call it with the same arguments.

using Eea6040Fn = void* (*)(void* iface, void* arg2, std::size_t size, std::uint32_t arg4);

inline Eea6040Fn eea6040_thunk() {
    return reinterpret_cast<Eea6040Fn>(
        *reinterpret_cast<std::uintptr_t*>(
            RewriteRegistry::imageBase() + kBc76e80ThunkSlotRva));
}

inline void* eea6040_iface() {
    return *reinterpret_cast<void**>(
        RewriteRegistry::imageBase() + kBc76e80AllocatorGlobalRva);
}

// movsx reg, byte : sign-extend one byte, exactly as the disassembly does. [V]

inline int64_t Bc76e80SignExtend8(uint8_t b) {
    return static_cast<int64_t>(static_cast<int8_t>(b));
}

} // namespace


void sub_bc76e80(Bc76e80Queue* queue, uint64_t key) {
    // 0xbc76e80..0xbc76e9b: prologue; A = queue->buckets, B = queue->bucketsEnd,

    // nbuckets = (B - A) >> 3

    //   0xbc76e80  push r15

    //   0xbc76e82  push r14

    //   0xbc76e84  push r13

    //   0xbc76e86  push r12

    //   0xbc76e88  push rsi

    //   0xbc76e89  push rdi

    //   0xbc76e8a  push rbp

    //   0xbc76e8b  push rbx

    //   0xbc76e8c  sub rsp,0x38

    //   0xbc76e90  mov rax,[rcx+0x20]

    //   0xbc76e94  mov r8,[rcx+0x28]

    //   0xbc76e98  sub r8,rax

    //   0xbc76e9b  shr r8,3

    void** A = queue->buckets;
    void** B = queue->bucketsEnd;
    uint64_t nbuckets =
        (reinterpret_cast<uintptr_t>(B) - reinterpret_cast<uintptr_t>(A)) >> 3;

    // 0xbc76e9f..0xbc76f09: mix key bytes 0..5 (each sign-extended) with 0x1003F

    //   0xbc76e9f  movsx r9,dl

    //   0xbc76ea3  mov r10d,edx

    //   0xbc76ea6  shr r10d,8

    //   0xbc76eaa  movsx r10,r10b

    //   0xbc76eae  imul r9,0x1003F

    //   0xbc76eb5  add r9,r10

    //   0xbc76eb8  mov r10d,edx

    //   0xbc76ebb  shr r10d,0x10

    //   0xbc76ebf  movsx r10,r10b

    //   0xbc76ec3  imul r9,0x1003F

    //   0xbc76eca  add r9,r10

    //   0xbc76ecd  mov r10d,edx

    //   0xbc76ed0  shr r10d,0x18

    //   0xbc76ed4  movsx r10,r10b

    //   0xbc76ed8  imul r9,0x1003F

    //   0xbc76edf  add r9,r10

    //   0xbc76ee2  mov r10,rdx

    //   0xbc76ee5  shr r10,0x20

    //   0xbc76ee9  movsx r10,r10b

    //   0xbc76eed  imul r9,0x1003F

    //   0xbc76ef4  add r9,r10

    //   0xbc76ef7  mov r10,rdx

    //   0xbc76efa  shr r10,0x28

    //   0xbc76efe  movsx r10,r10b

    //   0xbc76f02  imul r9,0x1003F

    //   0xbc76f09  add r9,r10

    uint64_t acc = Bc76e80SignExtend8(static_cast<uint8_t>(key));
    acc = acc * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(key >> 8));
    acc = acc * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(key >> 16));
    acc = acc * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(key >> 24));
    acc = acc * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(key >> 32));
    acc = acc * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(key >> 40));

    // 0xbc76f0c..0xbc76f1e: bucket index = (nbuckets - 2) & (acc * 0x1007E0F81)

    //   0xbc76f0c  mov r10,0x1007E0F81

    //   0xbc76f16  imul r10,r9

    //   0xbc76f1a  add r8,0xFFFFFFFFFFFFFFFE

    //   0xbc76f1e  and r8,r10

    uint64_t idx = (nbuckets - 2) & (acc * kBc76e80HashMix);

    // 0xbc76f21..0xbc76f4e: walk the chain buckets[idx] .. buckets[idx+1)

    //   0xbc76f21  mov rsi,[rax+r8*8]

    //   0xbc76f25  mov rax,[rax+r8*8+8]

    //   0xbc76f2a  cmp rsi,rax

    //   0xbc76f2d  je 0xBC771DE

    //   0xbc76f40  cmp [rsi],rdx

    //   0xbc76f43  je short 0xBC76F53

    //   0xbc76f45  mov rsi,[rsi+0x10]

    //   0xbc76f49  cmp rsi,rax

    //   0xbc76f4c  jne short 0xBC76F40

    //   0xbc76f4e  jmp 0xBC771DE

    Bc76e80Entry* node = reinterpret_cast<Bc76e80Entry*>(A[idx]);
    Bc76e80Entry* sentinel = reinterpret_cast<Bc76e80Entry*>(A[idx + 1]);
    if (node == sentinel) {
        return; // 0xbc76f2d -> epilogue (rax = sentinel; ignored by all callers)

    }
    for (;;) {
        if (node->key == key) { // 0xbc76f40

            break;              // 0xbc76f43 -> found

        }
        node = node->next;      // 0xbc76f45

        if (node == sentinel) { // 0xbc76f49

            return;             // 0xbc76f4c not taken -> 0xbc76f4e -> epilogue

        }
    }

    // 0xbc76f53..0xbc76f7f: found. ebp = node->value; P = queue->begin; Q = queue->end;

    // C = queue->cap; needBytes = (((Q - P) >> 4) + 1) << 4; room if P + needBytes <= C

    //   0xbc76f53  mov ebp,[rsi+8]

    //   0xbc76f56  mov r9,[rcx]

    //   0xbc76f59  mov rax,[rcx+8]

    //   0xbc76f60  sub r15,r9

    //   0xbc76f63  mov r8,r15

    //   0xbc76f66  sar r8,4

    //   0xbc76f6a  inc r8

    //   0xbc76f6d  mov r14,r8

    //   0xbc76f70  shl r14,4

    //   0xbc76f74  lea r11,[r9+r14]

    //   0xbc76f78  mov r10,[rcx+0x10]

    //   0xbc76f7c  cmp r11,r10

    //   0xbc76f7f  jbe 0xBC7700F

    uint64_t value = node->value;
    uint64_t* P = queue->begin;
    uint64_t* Q = queue->end;
    uint64_t* C = queue->cap;
    uint64_t oldSize = reinterpret_cast<uintptr_t>(Q) - reinterpret_cast<uintptr_t>(P);
    uint64_t need = (oldSize >> 4) + 1;
    uint64_t needBytes = need << 4;
    uint64_t* buffer = P;
    uint64_t growBytes = ((need >> 1) + need) << 4;
    if (reinterpret_cast<uintptr_t>(P) + needBytes > reinterpret_cast<uintptr_t>(C)) {
        // 0xbc76f85..0xbc76f99: growBytes = (((need >> 1) + need) << 4);

        // grow only if even 1.5x does not fit: P + growBytes > C

        //   0xbc76f85  mov rbx,r8

        //   0xbc76f88  shr rbx,1

        //   0xbc76f8b  add rbx,r8

        //   0xbc76f8e  shl rbx,4

        //   0xbc76f92  lea r8,[r9+rbx]

        //   0xbc76f96  cmp r8,r10

        //   0xbc76f99  jbe short 0xBC7700F

        if (reinterpret_cast<uintptr_t>(P) + growBytes > reinterpret_cast<uintptr_t>(C)) {
            // 0xbc76f9b..0xbc76fe6: allocate growBytes via the data-slot thunk;

            // r12 = key; interface = *[0x12ADF800]; null interface -> buffer = 0

            //   0xbc76f9b  mov r12,rdx

            //   0xbc76f9e  mov rdx,[0x12ADF800]

            //   0xbc76fa5  test rdx,rdx

            //   0xbc76fa8  je short 0xBC77014

            //   0xbc76faa  mov rax,[rdx]

            //   0xbc76fad  mov rax,[rax+8]      ; vtable[1] load: value never used (dead read)

            //   0xbc76fc8  xor edx,edx

            //   0xbc76fca  mov r8,rbx

            //   0xbc76fcd  xor r9d,r9d

            //   0xbc76fd0  call qword ptr [0xF99FFA0]

            void* g = eea6040_iface();
            void* nb = nullptr;
            if (g != nullptr) {
                // 0xbc76fd0  call qword ptr [0xF99FFA0]

                nb = eea6040_thunk()(g, nullptr, growBytes, 0u);
            }
            buffer = reinterpret_cast<uint64_t*>(nb);

            // 0xbc76fe8..0xbc77003: copy [P, Q) as 16-byte records to [buffer, ...)

            //   0xbc76fe8  mov r8,rdi

            //   0xbc76feb  mov rdx,r12

            //   0xbc76fee  xchg ax,ax

            //   0xbc76ff0  movups xmm0,[r9]

            //   0xbc76ff4  movups [r8],xmm0

            //   0xbc76ff8  add r9,0x10

            //   0xbc76ffc  add r8,0x10

            //   0xbc77000  cmp r9,rax

            //   0xbc77003  jne short 0xBC76FF0

            for (uint64_t* s = P, *d = buffer; s != Q; s += 2, d += 2) {
                d[0] = s[0];
                d[1] = s[1];
            }

            // 0xbc77005..0xbc7705f: free the old record array (if any) via the thunk

            //   0xbc77005  mov r9,[rcx]

            //   0xbc77008  test r9,r9

            //   0xbc7700b  jne short 0xBC77023

            //   0xbc7700d  jmp short 0xBC77062

            //   0xbc77023  mov r8,[0x12ADF800]

            //   0xbc7702a  test r8,r8

            //   0xbc7702d  je short 0xBC77062

            //   0xbc7702f  mov rax,[r8]

            //   0xbc77032  mov rax,[rax+8]      ; vtable[1] load: dead read

            //   0xbc7704a  mov rcx,r8

            //   0xbc7704d  mov rdx,r9

            //   0xbc77050  xor r8d,r8d

            //   0xbc77053  xor r9d,r9d

            //   0xbc77056  call qword ptr [0xF99FFA0]

            //   0xbc7705c  mov rdx,r12

            //   0xbc7705f  mov rcx,r13

            if (P != nullptr) {
                void* g = eea6040_iface();
                if (g != nullptr) {
                    // 0xbc77056  call qword ptr [0xF99FFA0]

                    eea6040_thunk()(g, P, 0, 0u);
                }
            }
        }
    }

    // 0xbc77062..0xbc77073: install new array bounds; rax = new end

    //   0xbc77062  mov [rcx],rdi

    //   0xbc77065  add r15,rdi

    //   0xbc77068  mov [rcx+8],r15

    //   0xbc7706c  add rbx,rdi

    //   0xbc7706f  mov [rcx+0x10],rbx

    //   0xbc77073  mov rax,r15

    queue->begin = buffer;
    uint64_t* newEnd =
        reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(buffer) + oldSize);
    queue->end = newEnd;
    queue->cap =
        reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(buffer) + growBytes);

    // 0xbc77076..0xbc770a3: shift [buffer, newEnd) right by one record (room at front)

    //   0xbc77076  mov r8,rdi

    //   0xbc77079  cmp rdi,rax

    //   0xbc7707c  je short 0xBC770A8

    //   0xbc77090  movups xmm0,[rax-0x10]

    //   0xbc77094  add rax,0xFFFFFFFFFFFFFFF0

    //   0xbc77098  movups [r8],xmm0

    //   0xbc7709c  add r8,0xFFFFFFFFFFFFFFF0

    //   0xbc770a0  cmp rax,rdi

    //   0xbc770a3  jne short 0xBC77090

    if (newEnd != buffer) {
        uint64_t* s = newEnd;
        uint64_t* d = newEnd;
        for (;;) {
            d[0] = s[-2];
            d[1] = s[-1];
            s -= 2;
            d -= 2;
            if (s == buffer) {
                break;
            }
        }
    }

    // 0xbc770a5..0xbc770b2: reload P = buffer; end += one record; insert { key, value } at front

    //   0xbc770a5  mov r8,[rcx]

    //   0xbc770a8  add r8,r14

    //   0xbc770ab  mov [rcx+8],r8

    //   0xbc770af  mov [rdi],rdx

    //   0xbc770b2  mov [rdi+8],ebp

    queue->end =
        reinterpret_cast<uint64_t*>(reinterpret_cast<uintptr_t>(buffer) + oldSize + 16);
    buffer[0] = key;
    buffer[1] = value;

    // 0xbc770b5..0xbc770c7: re-read bucket-array bounds and the drained node's key/next

    //   0xbc770b5  mov rdx,[rcx+0x20]

    //   0xbc770b9  mov r8,[rcx+0x28]

    //   0xbc770bd  sub r8,rdx

    //   0xbc770c0  sar r8,3

    //   0xbc770c4  mov r9,[rsi]

    //   0xbc770c7  mov rax,[rsi+0x10]

    A = queue->buckets;
    B = queue->bucketsEnd;
    nbuckets = (reinterpret_cast<uintptr_t>(B) - reinterpret_cast<uintptr_t>(A)) >> 3;
    Bc76e80Entry* next = node->next;

    // 0xbc770cb..0xbc77162: mix node->key bytes 0..7; idx2 = (nbuckets - 2) & (acc2 * mix)

    //   0xbc770cb  movsx r10,r9b

    //   0xbc770cf  mov r11d,r9d

    //   0xbc770d2  shr r11d,8

    //   0xbc770d6  movsx r11,r11b

    //   0xbc770da  imul r10,0x1003F

    //   0xbc770e1  add r10,r11

    //   0xbc770e4  mov r11d,r9d

    //   0xbc770e7  shr r11d,0x10

    //   0xbc770eb  movsx r11,r11b

    //   0xbc770ef  imul r10,0x1003F

    //   0xbc770f6  add r10,r11

    //   0xbc770f9  mov r11d,r9d

    //   0xbc770fc  shr r11d,0x18

    //   0xbc77100  movsx r11,r11b

    //   0xbc77104  imul r10,0x1003F

    //   0xbc7710b  add r10,r11

    //   0xbc7710e  mov r11,r9

    //   0xbc77111  shr r11,0x20

    //   0xbc77115  movsx r11,r11b

    //   0xbc77119  imul r10,0x1003F

    //   0xbc77120  add r10,r11

    //   0xbc77123  mov r11,r9

    //   0xbc77126  shr r11,0x28

    //   0xbc7712a  movsx r11,r11b

    //   0xbc7712e  imul r10,0x1003F

    //   0xbc77135  add r10,r11

    //   0xbc77138  mov r11,r9

    //   0xbc7713b  shr r11,0x30

    //   0xbc7713f  movsx r11,r11b

    //   0xbc77143  imul r10,0x1003F

    //   0xbc7714a  add r10,r11

    //   0xbc7714d  sar r9,0x38

    //   0xbc77151  imul r10,0x1003F

    //   0xbc77158  add r10,r9

    uint64_t acc2 = Bc76e80SignExtend8(static_cast<uint8_t>(node->key));
    acc2 = acc2 * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(node->key >> 8));
    acc2 = acc2 * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(node->key >> 16));
    acc2 = acc2 * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(node->key >> 24));
    acc2 = acc2 * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(node->key >> 32));
    acc2 = acc2 * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(node->key >> 40));
    acc2 = acc2 * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(node->key >> 48));
    acc2 = acc2 * kBc76e80HashMul + Bc76e80SignExtend8(static_cast<uint8_t>(node->key >> 56));
    uint64_t idx2 = (nbuckets - 2) & (acc2 * kBc76e80HashMix);

    // 0xbc77170..0xbc7717e: unlink node from every bucket whose head is node,

    // walking bucket indices down; stops at the first bucket whose head differs

    //   0xbc77170  cmp [rdx+r8*8],rsi

    //   0xbc77174  jne short 0xBC77180

    //   0xbc77176  mov [rdx+r8*8],rax

    //   0xbc7717a  sub r8,1

    //   0xbc7717e  jae short 0xBC77170

    for (uint64_t b = idx2;;) {
        if (reinterpret_cast<Bc76e80Entry*>(A[b]) != node) {
            break;
        }
        A[b] = reinterpret_cast<void*>(next);
        if (b == 0) {
            break;
        }
        --b;
    }

    // 0xbc77180..0xbc7719e: doubly-linked-list unlink of the node

    //   0xbc77180  mov rdx,[rsi+0x18]

    //   0xbc77184  test rdx,rdx

    //   0xbc77187  je short 0xBC77191

    //   0xbc77189  mov r8,[rsi+0x10]

    //   0xbc7718d  mov [rdx+0x10],r8

    //   0xbc77191  test rax,rax

    //   0xbc77194  je short 0xBC7719E

    //   0xbc77196  mov rdx,[rsi+0x18]

    //   0xbc7719a  mov [rax+0x18],rdx

    Bc76e80Entry* prev = node->prev;
    if (prev != nullptr) {
        prev->next = next;
    }
    if (next != nullptr) {
        next->prev = prev;
    }

    // 0xbc7719e..0xbc771d7: free the node via the data-slot thunk

    //   0xbc7719e  mov rdx,[0x12ADF800]

    //   0xbc771a5  test rdx,rdx

    //   0xbc771a8  je short 0xBC771DA

    //   0xbc771aa  mov rax,[rdx]

    //   0xbc771ad  mov rax,[rax+8]      ; vtable[1] load: dead read

    //   0xbc771c2  mov rdi,rcx

    //   0xbc771c5  mov rcx,rdx

    //   0xbc771c8  mov rdx,rsi

    //   0xbc771cb  xor r8d,r8d

    //   0xbc771ce  xor r9d,r9d

    //   0xbc771d1  call qword ptr [0xF99FFA0]

    //   0xbc771d7  mov rcx,rdi

    void* g = eea6040_iface();
    if (g != nullptr) {
        // 0xbc771d1  call qword ptr [0xF99FFA0]

        eea6040_thunk()(g, node, 0, 0u);
    }

    // 0xbc771da..0xbc771ee: count-- and epilogue

    //   0xbc771da  dec qword ptr [rcx+0x18]

    //   0xbc771de  add rsp,0x38

    //   0xbc771e2  pop rbx

    //   0xbc771e3  pop rbp

    //   0xbc771e4  pop rdi

    //   0xbc771e5  pop rsi

    //   0xbc771e6  pop r12

    //   0xbc771e8  pop r13

    //   0xbc771ea  pop r14

    //   0xbc771ec  pop r15

    //   0xbc771ee  ret

    queue->count -= 1;
}

#if 0
// Verbatim log of every call instruction in [0xbc76e80, 0xbc771ef) (rdis dis output,

// two spaces after the address):

0xbc76fd0  call qword ptr [0xF99FFA0]
0xbc77056  call qword ptr [0xF99FFA0]
0xbc771d1  call qword ptr [0xF99FFA0]
#endif
// UNRESOLVED CALL = none: every call goes through data slot 0xF99FFA0 to sub_eea6040,

// a vendor boundary (docs/data/native_boundary.tsv row 506).


// Layout assertions (full set in sub_bc76e80.h; repeated here so liftcheck sees them).

static_assert(offsetof(Bc76e80Record, key) == 0x00, "bc76e80: record key at +0x00");
static_assert(offsetof(Bc76e80Record, value) == 0x08, "bc76e80: record value at +0x08");
static_assert(sizeof(Bc76e80Record) == 0x10, "bc76e80: record stride 0x10");
static_assert(offsetof(Bc76e80Queue, buckets) == 0x20, "bc76e80: queue buckets at +0x20");
static_assert(offsetof(Bc76e80Queue, bucketsEnd) == 0x28, "bc76e80: queue bucketsEnd at +0x28");

LIFT_FN(sub_bc76e80, "sub_bc76e80", 0xbc76e80, sub_bc76e80, nullptr);

} // namespace native::bgfx

