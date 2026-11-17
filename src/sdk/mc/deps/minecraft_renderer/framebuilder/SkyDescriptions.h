#pragma once

// Sky visitor 0x66560f0 (1.26.62.01): field layouts of the Sky-group descriptions, limited to offsets that the exe reads at a quoted
// instruction (docs/functions/66560f0_sky_visitor.md; every RVA below was re-checked with rdis dis). These are READ-VIEWS: a member exists
// only where a read was seen, the gaps are explicit pad members with NO meaning. The full producer-side layouts (sizes, other fields) stay in
// Descriptions.h (RenderCubemapDescription, RenderLegacyCubemapDescription, RenderSkyAmbientSamplesDescription, RenderVolumetricFogDescription).
// Stars (tag 6), Sky (tag 5), CelestialBody (tag 7) and EndSky (tag 3) are added from docs/functions/66560f0_sky_cases.md (case bodies decoded from
// listings docs/data/listings/sky_*.txt). Atmosphere (tag 0), Clouds (tag 1) and Weather (tag 9) are covered by the last three structs (1 and 9 are read in their tail-call targets).


namespace mce::framebuilder::skyvis {

// Cubemap (Sky tag 2, case head 0x66562d5). [rdi] is the first qword. The head dereferences it: lock inc word [[rdi]+0x10] (0x6656306) and
// movzx byte [[rdi]+0x12] (0x665630c) with test al,1 / je exit (0x6656311..0x6656313). So +0x10 / +0x12 below are fields of the OBJECT the
// description's first qword points to (not of the description).
struct CubemapTextureObjectReads {
    uint8_t mPad00[0x10];
    uint16_t mWord10;   // +0x10 lock inc (0x6656306)
    uint8_t mByte12;    // +0x12 bit 0 tested, 0 => the case exits to 0x665d154 (0x665630c..0x6656313)
};
static_assert(offsetof(CubemapTextureObjectReads, mWord10) == 0x10);
static_assert(offsetof(CubemapTextureObjectReads, mByte12) == 0x12);

// Cubemap description reads. The shared body 0x6659615..0x665aee8 is reached from the head by je 0x6659615 (0x6656441) / jmp 0x665961f.
struct CubemapDescriptionReads {
    void* mTexture;               // +0x00 mov r14,[rdi] (0x66562d5); mov r9,[rdi] (0x665973d)
    uint8_t mPad08[8];            // +0x08 only address-taken (lea rcx,[rdi+8] 0x66597ba; lea r8,[rdi+8] 0x6659d7c), not read here
    float mBlock10[16];           // +0x10..+0x4F lea r9,[rdi+0x10] (0x665a205); four movups xmm6..9 at +0x10/+0x20/+0x30/+0x40 (0x665a22a..0x665a24d)
    uint16_t mWord50;             // +0x50 mov di,[rdi+0x50] (0x665a261); mov r15w,[rdi+0x50] (0x665a448)
    uint8_t mByte52;              // +0x52 cmp byte [rdi+0x52],1 (0x665a220)
};
// +0x52 is tested before the block copy: cmp byte [rdi+0x52],1 (0x665a220); jne 0x665a411 is the second shape of the same copy (0x665a411..0x665a448).
static_assert(offsetof(CubemapDescriptionReads, mTexture) == 0x00);
static_assert(offsetof(CubemapDescriptionReads, mBlock10) == 0x10);
static_assert(offsetof(CubemapDescriptionReads, mWord50) == 0x50);
static_assert(offsetof(CubemapDescriptionReads, mByte52) == 0x52);

// LegacyCubemap (Sky tag 4, case head 0x66561cc; material strings 0x6656241 / 0x6656af3). Reads inside the shared body 0x6659615..0x665aee8.
struct LegacyCubemapDescriptionReads {
    uint8_t mPad00[0x18];
    const float* mMatrixPtr;      // +0x18 mov rax,[rdi+0x18] (0x66599be, 0x6659ba5); movups [rax],[rax+0x10],[rax+0x20],[rax+0x30] -> four vec4 (0x66599c2..0x66599e4)
    uint64_t mPtr20;              // +0x20 mov r9,[rdi+0x20] (0x6658d63): data argument of uniform "CubemapRotation" (0x56D55E0)
    float mValue28;               // +0x28 movss xmm1,[rdi+0x28] (0x6658dc8) -> [rbp+0x340], uniform "CloudRenderDistanceAndCloudHeight"
    int16_t mWord2C;              // +0x2C movsx eax,word [rdi+0x2C] (0x6658dc0), cvtsi2ss -> [rbp+0x344]
    uint8_t mPad2E[2];
    uint64_t mVec30;              // +0x30 movsd xmm0,[rdi+0x30] (0x6659b9b), taken when byte +0x3E == 0
    uint32_t mValue38;            // +0x38 movss xmm1,[rdi+0x38] (0x6659ba0)
    uint16_t mWord3C;             // +0x3C mov di,[rdi+0x3C] (0x6659a05); mov r14w,[rdi+0x3C] (0x6659bec)
    uint8_t mByte3E;              // +0x3E movzx eax,byte [rdi+0x3E] (0x66599a8, case head 0x6656221 too); test al,al / je 0x6659b9b
    uint8_t mByte3F;              // +0x3F cmp byte [rdi+0x3F],1 (0x66599b4); jne 0x6659edd
};
static_assert(offsetof(LegacyCubemapDescriptionReads, mMatrixPtr) == 0x18);
static_assert(offsetof(LegacyCubemapDescriptionReads, mPtr20) == 0x20);
static_assert(offsetof(LegacyCubemapDescriptionReads, mValue28) == 0x28);
static_assert(offsetof(LegacyCubemapDescriptionReads, mWord2C) == 0x2C);
static_assert(offsetof(LegacyCubemapDescriptionReads, mVec30) == 0x30);
static_assert(offsetof(LegacyCubemapDescriptionReads, mValue38) == 0x38);
static_assert(offsetof(LegacyCubemapDescriptionReads, mWord3C) == 0x3C);
static_assert(offsetof(LegacyCubemapDescriptionReads, mByte3E) == 0x3E);
static_assert(offsetof(LegacyCubemapDescriptionReads, mByte3F) == 0x3F);

// SkyAmbientSamples (Sky tag 10, case head 0x6656983, body 0x665708b..0x665803c, exit jmp 0x665d124 at 0x6657ff4).
struct SkyAmbientSamplesDescriptionReads {
    uint16_t mWord00;             // +0x00 movzx ebx,word [rdi] (0x6656983) -> [rbp+0x1E0]
    uint8_t mPad02[6];
    void* mPtr08;                 // +0x08 mov r14,[rdi+8] (0x665708b) -> [rbp+0x1E8]
    void* mCtrl10;                // +0x10 mov rax,[rdi+0x10] (0x6656997); null => 0x6657088, else lock inc [rax+8] (0x66569a4) and r12=[rdi+0x10] (0x66569a8) -> [rbp+0x1F0] (0x6657096)
};
static_assert(offsetof(SkyAmbientSamplesDescriptionReads, mWord00) == 0x00);
static_assert(offsetof(SkyAmbientSamplesDescriptionReads, mPtr08) == 0x08);
static_assert(offsetof(SkyAmbientSamplesDescriptionReads, mCtrl10) == 0x10);
static_assert(sizeof(SkyAmbientSamplesDescriptionReads) == 0x18);

// VolumetricFog (Sky tag 8, head 0x66569b1): the visitor copies the description wholesale into a 0x58-byte record (0x66569c1..0x66569fc, 0x6656a03).
struct VolumetricFogDescriptionReads {
    uint16_t mWord00;             // +0x00 movzx r13d,word [rdi] (0x6656a03) -> [rbp+0x1E0]
    uint8_t mPad02[2];
    float mBlock04[16];           // +0x04..+0x43 movups at +0x04/+0x14/+0x24/+0x34 (0x66569d7..0x66569e3)
    float mBlock44[4];            // +0x44 movups xmm0,[rdi+0x44] (0x66569cc)
    uint32_t mQword54[2];         // +0x54 (8 bytes, 4-aligned) mov rax,[rdi+0x54] (0x66569c1) -> [rbp+0x234]
};
static_assert(offsetof(VolumetricFogDescriptionReads, mBlock04) == 0x04);
static_assert(offsetof(VolumetricFogDescriptionReads, mBlock44) == 0x44);
static_assert(offsetof(VolumetricFogDescriptionReads, mQword54) == 0x54);

// Stars (Sky tag 6, case head 0x6656812; body 0x6657558/0x66585b4..0x6658cd3; every [rdi+off] below re-checked with rdis dis). The head itself reads no
// description field. Uniform name of the +0x08 block: "StarsColor" (cold initialiser 0x665D90C).
struct StarsDescriptionReads {
    void* mMesh;                  // +0x00 mov r15,[rdi] (0x6658638); mov rax,[rdi] (0x6658792): mesh object (its +0x58/+0x60, +0x1B0/+0x1B8, +0x1D0/+0x1D4 are read)
    float mStarsColor08[4];       // +0x08 movups xmm0,[rdi+8] (0x66586b9) -> [rbp+0x340], set as uniform "StarsColor"
    float mMatrix18[16];          // +0x18 movups at +0x18/+0x28/+0x38 (0x6658750..0x665876a), movsd at +0x48 (0x665874b) and +0x50 (0x6658779) -> [rbp+0x4E0..0x518]
    uint16_t mWord58;             // +0x58 movzx r15d,word [rdi+0x58] (0x665878d)
};
static_assert(offsetof(StarsDescriptionReads, mMesh) == 0x00);
static_assert(offsetof(StarsDescriptionReads, mStarsColor08) == 0x08);
static_assert(offsetof(StarsDescriptionReads, mMatrix18) == 0x18);
static_assert(offsetof(StarsDescriptionReads, mWord58) == 0x58);

// Sky (Sky tag 5, case head 0x66566ee, material "Sky" 0xF51B964, no PBR variant seen; body 0x6658445..0x66585af, 0x66590aa..0x6659322).
// NOTE: this is NOT the 0xB0 RenderSkyDescription layout of Descriptions.h; that layout is what the tag-3 (EndSky) case reads, see EndSkyDescriptionReads.
struct SkyDescriptionReads {
    void* mMesh;                  // +0x00 mov r14,[rdi] (0x66584c3); mov rcx,[rdi] (0x66591b8)
    float mSkyColor08[4];         // +0x08 movups xmm0,[rdi+8] (0x66590f6) -> [rbp+0x340], uniform "SkyColor" (cold initialiser 0x665D89A)
    float mFogColor18[4];         // +0x18 movups xmm0,[rdi+0x18] (0x665854f) -> [rbp+0x340], uniform "FogColor" (cold initialiser 0x665D828)
    float mMatrix28[16];          // +0x28 movups at +0x28/+0x38/+0x48/+0x58 (0x665917c..0x665919f) -> [rbp+0x120..0x15F], byte [rbp+0x160]=0
    uint16_t mWord68;             // +0x68 mov r14w,[rdi+0x68] (0x66591b3) -> [rbp+0x470] (0x66592cb)
};
static_assert(offsetof(SkyDescriptionReads, mMesh) == 0x00);
static_assert(offsetof(SkyDescriptionReads, mSkyColor08) == 0x08);
static_assert(offsetof(SkyDescriptionReads, mFogColor18) == 0x18);
static_assert(offsetof(SkyDescriptionReads, mMatrix28) == 0x28);
static_assert(offsetof(SkyDescriptionReads, mWord68) == 0x68);

// CelestialBody (Sky tag 7, case head 0x6656516, materials "SunMoon" 0xF584D1D / "SunMoonForwardPBR" 0xF7CA226; own body copy 0x66596a1..0x6659ed8,
// frame-ctx [rsi+0x70]==2 variant 0x665b736..).
struct CelestialBodyDescriptionReads {
    void* mMesh;                  // +0x00 mov r9,[rdi] (0x665973d); mov r8,[rdi] (0x6659754); mov rax,[rdi] (0x6659ea0)
    uint8_t mPad08[0x10];         // +0x08 address taken only (lea rcx,[rdi+8] 0x66597ba; lea r8,[rdi+8] 0x6659d7c): sampler "SunMoonTexture" data, not dereferenced here
    float mSunMoonColor18[4];     // +0x18 movups xmm6,[rdi+0x18] (0x6656516), stored to [rbp+0x340] (0x66598a7), uniform "SunMoonColor"
    float mMatrix28[16];          // +0x28 movups +0x28/+0x38/+0x48 (0x6659e5e..0x6659e74), movsd +0x58 (0x6659e59) and +0x60 (0x6659e87); the ctx==2 copy reads 16 B at +0x58 (0x665b859)
    uint16_t mWord68;             // +0x68 movzx r15d,word [rdi+0x68] (0x6659e9b); movzx r13d,... (0x665b78a)
    uint8_t mPad6A[2];
    uint32_t mFlags6C;            // +0x6C test dword [rdi+0x6C],0xFFFFFFFD (0x66597a8)
    uint8_t mSkip70;              // +0x70 cmp byte [rdi+0x70],0; jne 0x665D154 (0x6656525), only when frame ctx [rsi+0x70] is not 1 or 2
    uint8_t mPad71[0xF];
    float mEmissive80;            // +0x80 movss xmm0,[rdi+0x80] (0x6659dba), uniform "SunMoonEmissiveMultiplier"
};
static_assert(offsetof(CelestialBodyDescriptionReads, mMesh) == 0x00);
static_assert(offsetof(CelestialBodyDescriptionReads, mSunMoonColor18) == 0x18);
static_assert(offsetof(CelestialBodyDescriptionReads, mMatrix28) == 0x28);
static_assert(offsetof(CelestialBodyDescriptionReads, mWord68) == 0x68);
static_assert(offsetof(CelestialBodyDescriptionReads, mFlags6C) == 0x6C);
static_assert(offsetof(CelestialBodyDescriptionReads, mSkip70) == 0x70);
static_assert(offsetof(CelestialBodyDescriptionReads, mEmissive80) == 0x80);

// EndSky (Sky tag 3, case head 0x665649c, materials "EndSky" 0xF51B961 / "EndSkyForwardPBR" 0xF7CA148; resolve 0x6656be0..0x6656d46; body 0x66587cf..0x6658b0b,
// 0x6658e44..0x66590a5, joined by the fall-through at 0x6658ff5). This is the Descriptions.h RenderSkyDescription layout (0xB0).
struct EndSkyDescriptionReads {
    void* mMesh;                  // +0x00 mov r15,[rdi] (0x665884d); mov rax,[rdi] (0x6658eb8)
    uint8_t mPad08[0x10];         // +0x08 address taken only (lea r8,[rdi+8] 0x6658a13): sampler "SkyTexture" data
    uint16_t mWord18;             // +0x18 movzx r15d,word [rdi+0x18] (0x6658eb3) -> [rbp+0x470] (0x66594ec)
    uint8_t mPad1A[2];
    float mSkyColor1C[4];         // +0x1C movups xmm0,[rdi+0x1C] (0x6658915) -> [rbp+0x340], uniform "SkyColor"
    float mMatrix2C[16];          // +0x2C movups +0x2C/+0x3C/+0x4C/+0x5C (0x6658e80..0x6658ea1) -> [rbp+0x170..0x1AF], byte [rbp+0x1B0]=0
    float mUv0Transform6C[16];    // +0x6C lea r9,[rdi+0x6C] (0x66589a3) data of uniform "UV0Transform"; 0x40-byte extent is [I] (ends at +0xAC)
    float mMinSkyLuminanceAC;     // +0xAC movss xmm0,[rdi+0xAC] (0x6658aa1), splat, uniform "MinimumSkyLuminance", only when frame ctx [rsi+0x70]==1
};
static_assert(offsetof(EndSkyDescriptionReads, mMesh) == 0x00);
static_assert(offsetof(EndSkyDescriptionReads, mWord18) == 0x18);
static_assert(offsetof(EndSkyDescriptionReads, mSkyColor1C) == 0x1C);
static_assert(offsetof(EndSkyDescriptionReads, mMatrix2C) == 0x2C);
static_assert(offsetof(EndSkyDescriptionReads, mUv0Transform6C) == 0x6C);
static_assert(offsetof(EndSkyDescriptionReads, mMinSkyLuminanceAC) == 0xAC);
static_assert(sizeof(EndSkyDescriptionReads) == 0xB0);


// Atmosphere (Sky tag 0, head 0x6656174, body 0x6656d4b..0x6656f96, then pass-object push 0x6656fb8 into the shared record code 0x6657237.. -> exit 0x6657ff4).
// Listing docs/data/listings/sky_atmosphere_6656d4b_6657090.txt; the whole description (0x138 bytes) is copied into a record, so these are copy reads.
struct AtmosphereDescriptionReads {
    uint16_t mWord00;             // +0x00 movzx r9d,word [rdi] (0x6656174)
    uint8_t mPad02[2];
    uint32_t mDword04;            // +0x04 mov r8d,[rdi+4] (0x6656df4)
    float mVec08[2];              // +0x08 movsd xmm2,[rdi+8] (0x6656e04); the float at +0x0C is also read alone (movss 0x6656dff)
    float mValue10;               // +0x10 movss xmm2,[rdi+0x10] (0x6656e11); stored value = max([+0x10]-[+0x0C], [0xEEC8060]) (0x6656e16..0x6656e26)
    float mBlock14[32];           // +0x14 eight movups at +0x14/+0x24/+0x34/+0x44/+0x54/+0x64/+0x74/+0x84 (0x6656e2e..0x6656e7b)
    float mVec94[2];              // +0x94 movsd xmm1,[rdi+0x94] (0x6656e89)
    float mValue9C;               // +0x9C movss xmm1,[rdi+0x9C] (0x6656e99)
    uint8_t mByteA0;              // +0xA0 movzx r8d,byte [rdi+0xA0] (0x6656ea9)
    uint8_t mPadA1[3];
    float mBlockA4[12];           // +0xA4 movups at +0xA4/+0xB4/+0xC4 (0x6656178..0x6656194, head)
    uint8_t mPadD4[4];
    void* mPtrD8;                 // +0xD8 mov rcx,[rdi+0xD8] (0x6656d4d)
    void* mCtrlE0;                // +0xE0 mov rax,[rdi+0xE0] (0x66561ac); non-null => lock inc [rax+8] (0x66561bc)
    float mVecE8[2];              // +0xE8 movsd (0x6656d62); +0xEC movss (0x6656d6a)
    float mVecF0[2];              // +0xF0 movsd xmm11,[rdi+0xF0] (0x6656eb8)
    float mVecF8[2];              // +0xF8 movsd xmm1,[rdi+0xF8] (0x6656eca)
    float mVec100[3];             // +0x100 movsd (0x6656d84), +0x104 movsd (0x6656d96)
    float mBlock10C[4];           // +0x10C movups xmm1,[rdi+0x10C] (0x6656dad)
    float mVec11C[2];             // +0x11C movsd xmm8,[rdi+0x11C] (0x6656dbb)
    float mValue124;              // +0x124 movss xmm10,[rdi+0x124] (0x6656dcd)
    float mBlock128[4];           // +0x128 movups xmm1,[rdi+0x128] (0x6656de6)
};
static_assert(offsetof(AtmosphereDescriptionReads, mDword04) == 0x04);
static_assert(offsetof(AtmosphereDescriptionReads, mVec08) == 0x08);
static_assert(offsetof(AtmosphereDescriptionReads, mValue10) == 0x10);
static_assert(offsetof(AtmosphereDescriptionReads, mBlock14) == 0x14);
static_assert(offsetof(AtmosphereDescriptionReads, mVec94) == 0x94);
static_assert(offsetof(AtmosphereDescriptionReads, mValue9C) == 0x9C);
static_assert(offsetof(AtmosphereDescriptionReads, mByteA0) == 0xA0);
static_assert(offsetof(AtmosphereDescriptionReads, mBlockA4) == 0xA4);
static_assert(offsetof(AtmosphereDescriptionReads, mPtrD8) == 0xD8);
static_assert(offsetof(AtmosphereDescriptionReads, mCtrlE0) == 0xE0);
static_assert(offsetof(AtmosphereDescriptionReads, mVecE8) == 0xE8);
static_assert(offsetof(AtmosphereDescriptionReads, mVecF0) == 0xF0);
static_assert(offsetof(AtmosphereDescriptionReads, mVecF8) == 0xF8);
static_assert(offsetof(AtmosphereDescriptionReads, mVec100) == 0x100);
static_assert(offsetof(AtmosphereDescriptionReads, mBlock10C) == 0x10C);
static_assert(offsetof(AtmosphereDescriptionReads, mVec11C) == 0x11C);
static_assert(offsetof(AtmosphereDescriptionReads, mValue124) == 0x124);
static_assert(offsetof(AtmosphereDescriptionReads, mBlock128) == 0x128);
static_assert(sizeof(AtmosphereDescriptionReads) == 0x138);

// Clouds (Sky tag 1, tail-called 0x67375A0 with rbx=r8=description; reads re-checked with rdis, 0x6737880..0x6737ddf).
struct CloudsDescriptionReads {
    float mMatrixA[16];           // +0x00 movups +0x00/+0x10/+0x20 (0x6737d8a..0x6737d9f), movss +0x30 (0x6737daa), +0x34 (0x6737db7), movsd +0x38 (0x6737dc4)
    float mMatrixB[16];           // +0x40 lea r9,[rbx+0x40] (0x6737ae2): address only, extent [I] from Descriptions.h
    void* mMesh;                  // +0x80 mov r14,[rbx+0x80] (0x6737880)
    float mColor88[4];            // +0x88 movups xmm0,[rbx+0x88] (0x6737943)
    uint8_t mByte98;              // +0x98 movzx eax,byte [rbx+0x98] (0x6737b1a)
    uint8_t mPad99;
    uint8_t mByte9A;              // +0x9A movzx eax,byte [rbx+0x9A] (0x6737aaa)
    uint8_t mPad9B;
    float mValue9C;               // +0x9C movss xmm0,[rbx+0x9C] (0x67379f7)
    uint16_t mWordA0;             // +0xA0 movzx edi,word [rbx+0xA0] (0x6737dd8)
};
static_assert(offsetof(CloudsDescriptionReads, mMatrixB) == 0x40);
static_assert(offsetof(CloudsDescriptionReads, mMesh) == 0x80);
static_assert(offsetof(CloudsDescriptionReads, mColor88) == 0x88);
static_assert(offsetof(CloudsDescriptionReads, mByte98) == 0x98);
static_assert(offsetof(CloudsDescriptionReads, mByte9A) == 0x9A);
static_assert(offsetof(CloudsDescriptionReads, mValue9C) == 0x9C);
static_assert(offsetof(CloudsDescriptionReads, mWordA0) == 0xA0);

// Weather (Sky tag 9, tail-called 0x6745440; description saved to [rbp+0x5F8] (0x674547b) and reloaded into rsi (0x6745b11)).
struct WeatherDescriptionReads {
    void* mMesh;                  // +0x00 mov r15,[rsi] (0x6745b18)
    uint8_t mPad08[8];
    float mMatrix10[16];          // +0x10 movups +0x10/+0x20/+0x30 (0x6746679..0x674668f), movsd +0x40 (0x6746674), movsd +0x48 (0x67466a2)
    uint8_t mSamplers50[0x30];    // +0x50/+0x60/+0x70 lea r8 (0x6746411, 0x67464bc, 0x67464ab): sampler data, address only; 0x10 each is [I]
    int32_t mValue80;             // +0x80 cvtsi2ss xmm0,dword [rsi+0x80] (0x67465c8)
    uint32_t mDword84;            // +0x84 mov edi,[r8+0x84] (0x6745482)
    float mUniforms88[40];        // +0x88 ten vec4 at +0x88,+0x98,+0xA8,+0xB8,+0xC8,+0xD8,+0xE8,+0xF8,+0x108,+0x118 (0x6745d7a..0x6746291, +0x98 at 0x6746335)
    uint16_t mWord128;            // +0x128 movzx esi,word [rsi+0x128] (0x67466b9)
};
static_assert(offsetof(WeatherDescriptionReads, mMatrix10) == 0x10);
static_assert(offsetof(WeatherDescriptionReads, mSamplers50) == 0x50);
static_assert(offsetof(WeatherDescriptionReads, mValue80) == 0x80);
static_assert(offsetof(WeatherDescriptionReads, mDword84) == 0x84);
static_assert(offsetof(WeatherDescriptionReads, mUniforms88) == 0x88);
static_assert(offsetof(WeatherDescriptionReads, mWord128) == 0x128);


}  // namespace mce::framebuilder::skyvis
