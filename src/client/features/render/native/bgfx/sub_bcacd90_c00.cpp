// LIFT 0xbcacd90 size 0x4f7b 1.26.62.01 sub_bcacd90
// CHUNK 0xbcacd90..0xbcae56d
#include "client/features/render/native/Lift.h"
#include "client/features/render/native/bgfx/sub_bcacd90_c00.h"

#include <cstdint>
#include <intrin.h>

namespace native::bgfx {
namespace {

// Lift-set callees (already lifted by their own units).
extern "C" void sub_5679db0(void* uniform_array, void* index_record, void* data_record); // 0x5679db0  UniformBlock::setUniform
extern "C" float sub_eec7000(float x);   // 0xeec7000  (unclassified float helper; neighbour 0xeec6de0 is lift)
extern "C" double sub_eec7430(double x);  // 0xeec7430  (unclassified double helper; neighbour 0xeec6de0 is lift)

// Indirect thunk through data slot 0xF9A8F28 (loaded at 0xbcad350 / 0xbcad362): float (*)(float,float).
inline float call_f9a8f28(float a, float b) {
    using Fn = float (*)(float, float);
    Fn fn = *reinterpret_cast<Fn*>(RewriteRegistry::imageBase() + 0xF9A8F28);
    return fn(a, b);
}

} // namespace

static inline void sub_bcacd90_chunk00(ChunkState_bcacd90_c00& s) {
    std::uint8_t* rbp = reinterpret_cast<std::uint8_t*>(s.frame_base);
    const std::uintptr_t base = RewriteRegistry::imageBase();

    // Live float registers carried across the chunk (rbp frame spills).
    float xmm6 = 0.0f, xmm7 = 0.0f, xmm8 = 0.0f, xmm9 = 0.0f;
    (void)s.r8_current_slot; (void)s.r9_remaining; (void)s.rdx_slot_base;
    (void)s.r12_scratch; (void)s.r13_scratch; (void)s.r14_scratch; (void)s.r15_scratch;

    // Helpers.
    auto gate = [&](std::uintptr_t slot, std::uintptr_t fail) -> bool {
        const int limit = *reinterpret_cast<const int*>(base + slot);
        const int idx = *reinterpret_cast<const int*>(base + 0x128767C8);
        std::uint8_t* tls = reinterpret_cast<std::uint8_t*>(__readgsqword(0x58));
        std::uint8_t* frame = *reinterpret_cast<std::uint8_t**>(tls + (std::uintptr_t)idx * 8);
        const int counter = *reinterpret_cast<const int*>(frame + 4);
        if (limit > counter) { s.branch = fail; return true; }
        return false;
    };
    auto try_insert = [&](std::uintptr_t keySlot) {
        std::uint8_t* owner = *reinterpret_cast<std::uint8_t**>(rbp + 0x1018);
        std::uint8_t* arrBase = *reinterpret_cast<std::uint8_t**>(owner + 0x38);
        const unsigned count = *reinterpret_cast<const std::uint16_t*>(owner + 0x42);
        void* key = *reinterpret_cast<void**>(base + keySlot);
        std::uintptr_t p = reinterpret_cast<std::uintptr_t>(arrBase);
        const std::uintptr_t end = p + (std::uintptr_t)count * 0x10;
        bool found = false;
        if (count != 0) {
            for (unsigned k = 0; k < count; ++k, p += 0x10) {
                void* entry = *reinterpret_cast<void**>(p);
                if (*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(entry) + 0x28) == key) { found = true; break; }
            }
        }
        if (!found) return;                 // exhausted (0xbcad10d / 0xbcad1ef / ...)
        if (p >= end) return;               // count==0 / jae skip
        const unsigned index = (unsigned)((p - reinterpret_cast<std::uintptr_t>(arrBase)) >> 4);
        *reinterpret_cast<std::uint16_t*>(rbp) = (std::uint16_t)index;
        *reinterpret_cast<std::uint8_t*>(rbp + 2) = 1;
        *reinterpret_cast<std::uint64_t*>(rbp + 0x310) = 1;
        *reinterpret_cast<void**>(rbp + 0x318) = rbp + 0xA80;
        sub_5679db0(owner + 8, rbp, rbp + 0x310);
    };

    // ---- prologue 0xbcacd90..0xbcacdf6 ----
    // 0xbcacd90  push rbp  (and r15/r14/r13/r12/rsi/rdi/rbx)
    // 0xbcacd9c  mov eax,0x1028 ; 0xbcacda1 call 0xE9E7970 (__chkstk, boundary crt) ; 0xbcacda6 sub rsp,rax ; 0xbcacda9 lea rbp,[rsp+0x80]
    // 0xbcacdb1  movaps [rbp+0xF90],xmm9 ; 0xbcacdb9 [rbp+0xF80],xmm8 ; 0xbcacdc1 [rbp+0xF70],xmm7 ; 0xbcacdc8 [rbp+0xF60],xmm6
    // 0xbcacdcf  mov qword ptr [rbp+0xF58],-2
    // 0xbcacdda  mov [rbp+0xF30],r9 (remaining count)
    // 0xbcacde1  mov [rbp+0xA60],r8 (current slot ptr)
    // 0xbcacde8  mov [rbp+0xF38],rdx (slot base)
    // 0xbcacdef  mov [rbp+0xF40],rcx (a0)
    // Frame is provided by the assembled function; rbp = s.frame_base. chkstk is the compiler probe.
    (void)base;

    // ---- availability gates 1..13  0xbcacdf6..0xbcacfd7 ----
    // 0xbcacdf6..0xbcace15
    if (gate(0x12AE23E8, 0xBCAF698)) return;
    // 0xbcace1b..0xbcace3a
    if (gate(0x12AE23F8, 0xBCAF70A)) return;
    // 0xbcace40..0xbcace5f
    if (gate(0x12AE2408, 0xBCAF77C)) return;
    // 0xbcace65..0xbcace84
    if (gate(0x12AE2418, 0xBCAF7EE)) return;
    // 0xbcace8a..0xbcacea9
    if (gate(0x12AE2428, 0xBCAF860)) return;
    // 0xbcaceaf..0xbcacece
    if (gate(0x12AE2438, 0xBCAF8D2)) return;
    // 0xbcaced4..0xbcacef3
    if (gate(0x12AE2448, 0xBCAF944)) return;
    // 0xbcacef9..0xbcacf18
    if (gate(0x12AE2458, 0xBCAF9B6)) return;
    // 0xbcacf1e..0xbcacf3d
    if (gate(0x12AE2468, 0xBCAFA28)) return;
    // 0xbcacf43..0xbcacf62
    if (gate(0x12AE2478, 0xBCAFA9A)) return;
    // 0xbcacf68..0xbcacf87
    if (gate(0x12AE2488, 0xBCAFB0C)) return;
    // 0xbcacf8d..0xbcacfac
    if (gate(0x12AE2498, 0xBCAFB7E)) return;
    // 0xbcacfb2..0xbcacfd1
    if (gate(0x12AE24A8, 0xBCAFBF0)) return;

    // ---- first slot region  0xbcacfd7..0xbcad4dd ----
    // 0xbcacfd7..0xbcad10d
    std::uint8_t* p1050 = *reinterpret_cast<std::uint8_t**>(rbp + 0x1050);
    std::uint8_t* p1038 = *reinterpret_cast<std::uint8_t**>(rbp + 0x1038);
    std::uint8_t* r15 = *reinterpret_cast<std::uint8_t**>(rbp + 0x1020);
    *reinterpret_cast<void**>(rbp + 0xA68) = *reinterpret_cast<std::uint8_t**>(p1038 + 8);
    *reinterpret_cast<void**>(rbp + 0xA70) = *reinterpret_cast<std::uint8_t**>(p1050 + 8);
    xmm6 = sub_eec7000(*reinterpret_cast<float*>(r15 + 0x28));       // 0xbcad002..0xbcad00d
    double d38 = sub_eec7430((double)*reinterpret_cast<float*>(r15 + 0x38)); // 0xbcad010..0xbcad01a
    xmm7 = (r15[0] != 0) ? *reinterpret_cast<float*>(base + 0xEEC8060) : 0.0f; // 0xbcad01f..0xbcad030
    xmm8 = static_cast<float>(d38);                                 // 0xbcad033
    std::uint8_t* r14 = *reinterpret_cast<std::uint8_t**>(rbp + 0x1018); // 0xbcad038
    float m1 = (r15[0x34] != 0) ? *reinterpret_cast<float*>(base + 0xEEC8060) : 0.0f; // 0xbcad03f..0xbcad046
    xmm8 = xmm8 * *reinterpret_cast<float*>(base + 0xF35EBD0);     // 0xbcad052
    *reinterpret_cast<void**>(rbp + 0xF50) = r14 + 8;              // 0xbcad05b..0xbcad05f
    *reinterpret_cast<float*>(rbp + 0xA80) = (float)*reinterpret_cast<int*>(r15 + 8); // 0xbcad066
    *reinterpret_cast<float*>(rbp + 0xA84) = xmm6;                  // 0xbcad06e
    *reinterpret_cast<float*>(rbp + 0xA88) = m1;                    // 0xbcad076
    *reinterpret_cast<std::uint32_t*>(rbp + 0xA8C) = 0;             // 0xbcad07e
    try_insert(0x12AE2410);                                         // 0xbcad088..0xbcad108

    // 0xbcad10d..0xbcad1ef
    const unsigned char b1030 = rbp[0x1030];                          // 0xbcad10d
    double d30 = sub_eec7430((double)*reinterpret_cast<float*>(r15 + 0x30)); // 0xbcad114..0xbcad124
    xmm9 = *reinterpret_cast<float*>(r15 + 0x3C);                   // 0xbcad11a
    double d2c = sub_eec7430((double)*reinterpret_cast<float*>(r15 + 0x2C)); // 0xbcad12c..0xbcad136
    const float k0 = *reinterpret_cast<float*>(base + 0xF152830);
    const float k1 = *reinterpret_cast<float*>(base + 0xF152830 + 4);
    *reinterpret_cast<float*>(rbp + 0xA80) = static_cast<float>(d2c) * k0; // 0xbcad13b..0xbcad149
    *reinterpret_cast<float*>(rbp + 0xA84) = static_cast<float>(d30) * k1;
    *reinterpret_cast<float*>(rbp + 0xA88) = xmm8;                  // 0xbcad150
    *reinterpret_cast<float*>(rbp + 0xA8C) = xmm9;                  // 0xbcad159
    try_insert(0x12AE2420);                                         // 0xbcad162..0xbcad1dc

    // 0xbcad1ef..0xbcad2c4
    float sel0 = (b1030 != 0) ? *reinterpret_cast<float*>(base + 0xEEC8060) : 0.0f; // 0xbcad1ef..0xbcad1f8
    const unsigned char b1060 = rbp[0x1060];                          // 0xbcad200
    float v4 = (float)*reinterpret_cast<int*>(r15 + 4);             // 0xbcad207..0xbcad20a
    *reinterpret_cast<float*>(rbp + 0xA80) = v4;                     // 0xbcad210
    *reinterpret_cast<float*>(rbp + 0xA84) = xmm7;                  // 0xbcad218
    *reinterpret_cast<float*>(rbp + 0xA88) = sel0;                   // 0xbcad220
    *reinterpret_cast<std::uint32_t*>(rbp + 0xA8C) = 0;             // 0xbcad228
    try_insert(0x12AE2460);                                         // 0xbcad232..0xbcad2a0
    float sel1 = (b1060 != 0) ? *reinterpret_cast<float*>(base + 0xEEC8060) : 0.0f; // 0xbcad2b3..0xbcad2bc

    // 0xbcad2c4..0xbcad344
    *reinterpret_cast<float*>(rbp + 0xA80) = sel1;                   // 0xbcad2c4..0xbcad2c8 movaps (4 floats)
    *reinterpret_cast<float*>(rbp + 0xA84) = sel1;
    *reinterpret_cast<float*>(rbp + 0xA88) = sel1;
    *reinterpret_cast<float*>(rbp + 0xA8C) = sel1;
    try_insert(0x12AE2470);                                         // 0xbcad33b

    // 0xbcad344..0xbcad4dd  (two indirect [0xF9A8F28] calls + arithmetic)
    float q40 = *reinterpret_cast<float*>(r15 + 0x40);              // 0xbcad344
    float q44 = *reinterpret_cast<float*>(r15 + 0x44);              // 0xbcad34a
    xmm6 = call_f9a8f28(q44, q40);                                 // 0xbcad350..0xbcad359
    float q4c = *reinterpret_cast<float*>(r15 + 0x4C);              // 0xbcad362
    float r0 = call_f9a8f28(q4c, q40);                             // 0xbcad368
    float q48 = *reinterpret_cast<float*>(r15 + 0x48);              // 0xbcad370
    float t3 = r0 * q48;                                            // 0xbcad379
    float t4 = xmm6 - t3;                                           // 0xbcad380
    float t6 = xmm6 * q48;                                          // 0xbcad384
    t6 = t6 - t3;                                                   // 0xbcad388
    float t4d = t4 / t6;                                            // 0xbcad38c
    float t2 = r0 * t4d;                                            // 0xbcad390..0xbcad393
    float t0 = r0 - t2;                                             // 0xbcad397
    float q50 = *reinterpret_cast<float*>(r15 + 0x50);              // 0xbcad39b
    *reinterpret_cast<float*>(rbp + 0xA80) = q40;                   // 0xbcad3a1
    *reinterpret_cast<float*>(rbp + 0xA84) = t4d;                   // 0xbcad3a9
    *reinterpret_cast<float*>(rbp + 0xA88) = t0;                    // 0xbcad3b1
    *reinterpret_cast<float*>(rbp + 0xA8C) = q50;                   // 0xbcad3b9
    try_insert(0x12AE2490);                                         // 0xbcad440
    float q54 = *reinterpret_cast<float*>(r15 + 0x54);              // 0xbcad453
    *reinterpret_cast<float*>(rbp + 0xA80) = q54;                   // 0xbcad459
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA84) = 0;             // 0xbcad461
    *reinterpret_cast<std::uint32_t*>(rbp + 0xA8C) = 0;             // 0xbcad46c
    try_insert(0x12AE24A0);                                         // 0xbcad4d8

    // ---- availability gates 14..31  0xbcad4dd..0xbcad777 ----
    if (gate(0x12AE22C8, 0xBCAFC62)) return;
    if (gate(0x12AE22D8, 0xBCAFCD4)) return;
    if (gate(0x12AE22E8, 0xBCAFD46)) return;
    if (gate(0x12AE22F8, 0xBCAFDB8)) return;
    if (gate(0x12AE2308, 0xBCAFE2A)) return;
    if (gate(0x12AE2318, 0xBCAFE9C)) return;
    if (gate(0x12AE2328, 0xBCAFF0E)) return;
    if (gate(0x12AE2338, 0xBCAFF80)) return;
    if (gate(0x12AE2348, 0xBCAFFF2)) return;
    if (gate(0x12AE2358, 0xBCB0064)) return;
    if (gate(0x12AE2368, 0xBCB00D6)) return;
    if (gate(0x12AE2378, 0xBCB0148)) return;
    if (gate(0x12AE2388, 0xBCB01BA)) return;
    if (gate(0x12AE2398, 0xBCB022C)) return;
    if (gate(0x12AE23A8, 0xBCB029E)) return;
    if (gate(0x12AE23B8, 0xBCB0310)) return;
    if (gate(0x12AE23C8, 0xBCB0382)) return;
    if (gate(0x12AE23D8, 0xBCB03F4)) return;

    // ---- ColorGrading builders  0xbcad777..0xbcae56d ----
    std::uint8_t* rbx = *reinterpret_cast<std::uint8_t**>(rbp + 0x1028); // 0xbcad777

    // 0xbcad777..0xbcad845  (CG builder 0: Clear color)
    float g14 = (float)(int)(signed char)rbx[0x14];                   // 0xbcad782..0xbcad786
    float g18 = *reinterpret_cast<float*>(rbx + 0x18);                // 0xbcad78a
    float g1c = (float)(int)(signed char)rbx[0x1C];                   // 0xbcad77e..0xbcad78f
    *reinterpret_cast<float*>(rbp + 0xA80) = g14;                     // 0xbcad793
    *reinterpret_cast<float*>(rbp + 0xA84) = g18;                     // 0xbcad79b
    *reinterpret_cast<float*>(rbp + 0xA88) = g1c;                     // 0xbcad7a3
    *reinterpret_cast<std::uint32_t*>(rbp + 0xA8C) = 0;               // 0xbcad7ab
    try_insert(0x12AE22C0);                                           // 0xbcad7b5..0xbcad832

    // 0xbcad845..0xbcad92b  (CG builder 1)
    unsigned char s0 = rbx[0];                                         // 0xbcad845
    unsigned char s8 = rbx[8];                                         // 0xbcad848
    unsigned char s9 = rbx[9];                                         // 0xbcad84d
    unsigned char sf4 = rbx[0xF4];                                     // 0xbcad852
    unsigned char m1b = (unsigned char)((sf4 & s0) & rbx[0x44]);      // 0xbcad863..0xbcad869
    float v28 = *reinterpret_cast<float*>(rbx + 0x28);                // 0xbcad86d
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x20); // 0xbcad87e..0xbcad883
    *reinterpret_cast<float*>(rbp + 0xA88) = v28;                     // 0xbcad88b
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m1b;               // 0xbcad893
    try_insert(0x12AE22D0);                                           // 0xbcad89b..0xbcad912

    // 0xbcad92b..0xbcad9eb  (CG builder 2)
    unsigned char m2b = (unsigned char)((sf4 & s8) & rbx[0x45]);      // 0xbcad92b..0xbcad931
    float v34 = *reinterpret_cast<float*>(rbx + 0x34);                // 0xbcad934
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x2C); // 0xbcad945
    *reinterpret_cast<float*>(rbp + 0xA88) = v34;                     // 0xbcad952
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m2b;               // 0xbcad95a
    try_insert(0x12AE22E0);                                           // 0xbcad9d2

    // 0xbcad9eb..0xbcadaab  (CG builder 3)
    unsigned char m3b = (unsigned char)((sf4 & s9) & rbx[0x46]);     // 0xbcad9eb..0xbcadeae
    float v40 = *reinterpret_cast<float*>(rbx + 0x40);                // 0xbcad9f1
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x38); // 0xbcada02
    *reinterpret_cast<float*>(rbp + 0xA88) = v40;                     // 0xbcada0f
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m3b;               // 0xbcada17
    try_insert(0x12AE22F0);                                           // 0xbcada92

    // 0xbcadaab..0xbcadb7b  (CG builder 4)
    unsigned char sf5 = rbx[0xF5];                                    // 0xbcadaab
    unsigned char edi = rbx[0x71];                                     // 0xbcadab3
    unsigned char r15b = rbx[0x72];                                   // 0xbcadab7
    unsigned char m4 = (unsigned char)((sf5 & s0) & rbx[0x70]);      // 0xbcadabc..0xbcadac2
    float v54 = *reinterpret_cast<float*>(rbx + 0x54);                // 0xbcadac6
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x4C); // 0xbcadad7
    *reinterpret_cast<float*>(rbp + 0xA88) = v54;                     // 0xbcadae4
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m4;               // 0xbcadaec
    try_insert(0x12AE2300);                                           // 0xbcadb62

    // 0xbcadb7b..0xbcadc3b  (CG builder 5)
    unsigned char m5 = (unsigned char)((sf5 & s8) & edi);            // 0xbcadb7b..0xbcadb81
    float v60 = *reinterpret_cast<float*>(rbx + 0x60);                // 0xbcadb84
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x58); // 0xbcadb95
    *reinterpret_cast<float*>(rbp + 0xA88) = v60;                     // 0xbcadba2
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m5;               // 0xbcadbaa
    try_insert(0x12AE2310);                                           // 0xbcadc22

    // 0xbcadc3b..0xbcadcfb  (CG builder 6)
    unsigned char m6b = (unsigned char)((sf5 & s9) & r15b);          // 0xbcadc3b..0xbcadc3e
    float v6c = *reinterpret_cast<float*>(rbx + 0x6C);                // 0xbcadc41
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x64); // 0xbcadc52
    *reinterpret_cast<float*>(rbp + 0xA88) = v6c;                     // 0xbcadc5f
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m6b;               // 0xbcadc67
    try_insert(0x12AE2320);                                           // 0xbcadce2

    // 0xbcadcfb..0xbcadddb  (CG builder 7)
    unsigned char sf6 = rbx[0xF6];                                    // 0xbcadcfb
    unsigned char edi7 = rbx[0x99];                                   // 0xbcadd03
    unsigned char r15b7 = rbx[0x9A];                                  // 0xbcadd0a
    unsigned char m7b = (unsigned char)((sf6 & s0) & rbx[0x98]);     // 0xbcadd12..0xbcadd18
    float v7c = *reinterpret_cast<float*>(rbx + 0x7C);                // 0xbcadd1f
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x74); // 0xbcadd30
    *reinterpret_cast<float*>(rbp + 0xA88) = v7c;                     // 0xbcadd3d
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m7b;              // 0xbcadd45
    try_insert(0x12AE2330);                                           // 0xbcaddc2

    // 0xbcadddb..0xbcadeab  (CG builder 8)
    unsigned char m8b = (unsigned char)((sf6 & s8) & edi7);          // 0xbcadddb..0xbcadde1
    float v88 = *reinterpret_cast<float*>(rbx + 0x88);                // 0xbcadde4
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x80); // 0xbcadde8? 0xbcadde4..0xbcaddf3
    *reinterpret_cast<float*>(rbp + 0xA88) = v88;                     // 0xbcade08
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m8b;              // 0xbcade10
    try_insert(0x12AE2340);                                           // 0xbcade92

    // 0xbcadeab..0xbcadf6b  (CG builder 9)
    unsigned char m9b = (unsigned char)((sf6 & s9) & r15b7);         // 0xbcadeab..0xbcadeae
    float v94 = *reinterpret_cast<float*>(rbx + 0x94);                // 0xbcadeb1
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x8C); // 0xbcadec5
    *reinterpret_cast<float*>(rbp + 0xA88) = v94;                     // 0xbcaded5
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m9b;              // 0xbcadedd
    try_insert(0x12AE2350);                                           // 0xbcadf52

    // 0xbcadf6b..0xbcae04b  (CG builder 10)
    unsigned char sf7 = rbx[0xF7];                                    // 0xbcadf6b
    unsigned char edi10 = rbx[0xC1];                                  // 0xbcadf73
    unsigned char r15b10 = rbx[0xC2];                                 // 0xbcadf7a
    unsigned char m10 = (unsigned char)((sf7 & s0) & rbx[0xC0]);     // 0xbcadf82..0xbcadf88
    float vA4 = *reinterpret_cast<float*>(rbx + 0xA4);                // 0xbcadf8f
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0x9C); // 0xbcadfa3
    *reinterpret_cast<float*>(rbp + 0xA88) = vA4;                     // 0xbcadfb3
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m10;              // 0xbcadfbb
    try_insert(0x12AE2360);                                           // 0xbcae032

    // 0xbcae04b..0xbcae11b  (CG builder 11)
    unsigned char m11 = (unsigned char)((sf7 & s8) & edi10);         // 0xbcae04b..0xbcae051
    float vB0 = *reinterpret_cast<float*>(rbx + 0xB0);                // 0xbcae054
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0xA8); // 0xbcae068
    *reinterpret_cast<float*>(rbp + 0xA88) = vB0;                     // 0xbcae078
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m11;              // 0xbcae080
    try_insert(0x12AE2370);                                           // 0xbcae102

    // 0xbcae11b..0xbcae1db  (CG builder 12)
    unsigned char m12 = (unsigned char)((sf7 & s9) & r15b10);        // 0xbcae11b..0xbcae11e
    float vBC = *reinterpret_cast<float*>(rbx + 0xBC);                // 0xbcae121
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0xB4); // 0xbcae135
    *reinterpret_cast<float*>(rbp + 0xA88) = vBC;                     // 0xbcae145
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m12;              // 0xbcae14d
    try_insert(0x12AE2380);                                           // 0xbcae1c2

    // 0xbcae1db..0xbcae2bb  (CG builder 13)
    unsigned char sf8 = rbx[0xF8];                                    // 0xbcae1db
    unsigned char edi13 = rbx[0xE9];                                  // 0xbcae1e3
    unsigned char r15b13 = rbx[0xEA];                                 // 0xbcae1ea
    unsigned char m13 = (unsigned char)((s0 & sf8) & rbx[0xE8]);     // 0xbcae1f2..0xbcae1f5
    float vCC = *reinterpret_cast<float*>(rbx + 0xCC);                // 0xbcae1fc
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0xC4); // 0xbcae210
    *reinterpret_cast<float*>(rbp + 0xA88) = vCC;                     // 0xbcae220
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m13;              // 0xbcae228
    try_insert(0x12AE2390);                                           // 0xbcae2a2

    // 0xbcae2bb..0xbcae385  (CG builder 14)
    unsigned char m14 = (unsigned char)((s8 & sf8) & edi13);         // 0xbcae2bb..0xbcae2be
    float vD8 = *reinterpret_cast<float*>(rbx + 0xD8);                // 0xbcae2c1
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0xD0); // 0xbcae2d5
    *reinterpret_cast<float*>(rbp + 0xA88) = vD8;                     // 0xbcae2e5
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m14;              // 0xbcae2ed
    *reinterpret_cast<void**>(rbp + 0x318) = rbp + 0xA80;            // 0xbcae300..0xbcae307
    try_insert(0x12AE23A0);                                           // 0xbcae372

    // 0xbcae385..0xbcae445  (CG builder 15)
    unsigned char m15 = (unsigned char)((s9 & sf8) & r15b13);        // 0xbcae385..0xbcae388
    float vE4 = *reinterpret_cast<float*>(rbx + 0xE4);                // 0xbcae38b
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA80) = *reinterpret_cast<std::uint64_t*>(rbx + 0xDC); // 0xbcae39f
    *reinterpret_cast<float*>(rbp + 0xA88) = vE4;                     // 0xbcae3af
    *reinterpret_cast<float*>(rbp + 0xA8C) = (float)m15;              // 0xbcae3b7
    // 0xbcae3d7  rdi = [rbp+0x1020] (reload)
    try_insert(0x12AE23B0);                                           // 0xbcae432

    // 0xbcae445..0xbcae4f9  (CG builder 16)
    float vEC = *reinterpret_cast<float*>(rbx + 0xEC);                // 0xbcae445
    float v04 = *reinterpret_cast<float*>(rbx + 4);                   // 0xbcae44d
    float v0C = *reinterpret_cast<float*>(rbx + 0xC);                 // 0xbcae452
    float v48 = *reinterpret_cast<float*>(rbx + 0x48);                // 0xbcae457
    *reinterpret_cast<float*>(rbp + 0xA80) = v48;                     // 0xbcae45c
    *reinterpret_cast<float*>(rbp + 0xA84) = v04;                     // 0xbcae464
    *reinterpret_cast<float*>(rbp + 0xA88) = v0C;                     // 0xbcae46c
    *reinterpret_cast<float*>(rbp + 0xA8C) = vEC;                     // 0xbcae474
    try_insert(0x12AE23C0);                                           // 0xbcae4e6

    // 0xbcae4f9..0xbcae56d  (final builder of this chunk; sub_5679db0 call at 0xbcae58e is in chunk 2)
    int sv = (int)(signed char)rbx[0xF9];                             // 0xbcae4f9
    float v0 = (float)sv;                                             // 0xbcae501..0xbcae504
    *reinterpret_cast<float*>(rbp + 0xA80) = v0;                      // 0xbcae509
    *reinterpret_cast<std::uint64_t*>(rbp + 0xA84) = 0;               // 0xbcae511
    *reinterpret_cast<std::uint32_t*>(rbp + 0xA8C) = 0;               // 0xbcae51c
    *reinterpret_cast<std::uint64_t*>(rbp + 0x310) = 1;               // 0xbcae526
    *reinterpret_cast<void**>(rbp + 0x318) = rbp + 0xA80;            // 0xbcae531
    // search loop 0xbcae538..0xbcae56b: scan [owner+0x38] for entry->[0x28]==[0x12AE23D0]
    std::uint8_t* owner2 = *reinterpret_cast<std::uint8_t**>(rbp + 0x1018);
    std::uint8_t* sbase = *reinterpret_cast<std::uint8_t**>(owner2 + 0x38);
    unsigned cnt2 = *reinterpret_cast<const std::uint16_t*>(owner2 + 0x42);
    void* key2 = *reinterpret_cast<void**>(base + 0x12AE23D0);
    std::uintptr_t p2 = reinterpret_cast<std::uintptr_t>(sbase);
    const std::uintptr_t end2 = p2 + (std::uintptr_t)cnt2 * 0x10;
    bool found2 = false;
    if (cnt2 != 0) {
        for (unsigned k = 0; k < cnt2; ++k, p2 += 0x10) {
            void* entry = *reinterpret_cast<void**>(p2);
            if (*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(entry) + 0x28) == key2) { found2 = true; break; }
        }
    }
    // 0xbcae565 add rdx,rax ; 0xbcae568 cmp r8,rdx ; 0xbcae56b jae 0xBCAE593
    // (insert continues at 0xbcae56d in chunk 2 when the slot is present)
    (void)found2; (void)p2; (void)end2;
    // falls through to chunk 2 at 0xbcae56d
}

#if 0
0xbcacd90  push rbp
0xbcacda1  call 0xE9E7970                                ; -> sub_e9e7970
0xbcad008  call 0xEEC7000                                ; -> sub_eec7000
0xbcad01a  call 0xEEC7430                                ; -> sub_eec7430
0xbcad108  call 0x5679DB0                                ; -> sub_5679db0
0xbcad124  call 0xEEC7430                                ; -> sub_eec7430
0xbcad136  call 0xEEC7430                                ; -> sub_eec7430
0xbcad1dc  call 0x5679DB0                                ; -> sub_5679db0
0xbcad2a0  call 0x5679DB0                                ; -> sub_5679db0
0xbcad33b  call 0x5679DB0                                ; -> sub_5679db0
0xbcad357  call rdi
0xbcad368  call rdi
0xbcad440  call 0x5679DB0                                ; -> sub_5679db0
0xbcad4d8  call 0x5679DB0                                ; -> sub_5679db0
0xbcad832  call 0x5679DB0                                ; -> sub_5679db0
0xbcad912  call 0x5679DB0                                ; -> sub_5679db0
0xbcad9d2  call 0x5679DB0                                ; -> sub_5679db0
0xbcada92  call 0x5679DB0                                ; -> sub_5679db0
0xbcadb62  call 0x5679DB0                                ; -> sub_5679db0
0xbcadc22  call 0x5679DB0                                ; -> sub_5679db0
0xbcadce2  call 0x5679DB0                                ; -> sub_5679db0
0xbcaddc2  call 0x5679DB0                                ; -> sub_5679db0
0xbcade92  call 0x5679DB0                                ; -> sub_5679db0
0xbcadf52  call 0x5679DB0                                ; -> sub_5679db0
0xbcae032  call 0x5679DB0                                ; -> sub_5679db0
0xbcae102  call 0x5679DB0                                ; -> sub_5679db0
0xbcae1c2  call 0x5679DB0                                ; -> sub_5679db0
0xbcae2a2  call 0x5679DB0                                ; -> sub_5679db0
0xbcae372  call 0x5679DB0                                ; -> sub_5679db0
0xbcae432  call 0x5679DB0                                ; -> sub_5679db0
0xbcae4e6  call 0x5679DB0                                ; -> sub_5679db0
0xbcae56b  jae short 0xBCAE593
#endif

LIFT_FN(sub_bcacd90, "VV frame-graph builder", 0xbcacd90, &sub_bcacd90_chunk00, nullptr);

} // namespace native::bgfx
