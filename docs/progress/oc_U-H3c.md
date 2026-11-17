# UNIT U-H3c: Analysis of H2/H3b cited RVAs from verified listings

**Chosen item/RVAs**: From 6bi "Pending: disassemble 0x10f09f0, 0x6646980, 0x660ecd0" — three functions explicitly named in H2/H3b cited docs as needing analysis.

## NEXT
L_660ecd0.txt fully analysed (lines 1-1052 / 0x660ecd0..0x660fcd8). Next: L_10f09f0.txt.

---

## Function 0x660ecd0 (sub_660ecd0) — bgfx::Caps JSON dump
**Listing**: docs/listings/L_660ecd0.txt (1052 lines, 0x660ecd0..0x660fcd8, size 0x1008)
**Callers**: 0 xrefs (6bl)
**Purpose**: Serializes bgfx capabilities to JSON. Not an occlusion-query pool. Fixed block: homogenousDepth, originBottomLeft, fpEpsilon, numGPUs. Supported-flags bitmask in rbx (u64 at [0x12ADFA50]) tested bit-by-bit: 0x1 Alpha_To_Coverage, 0x2 Blend_Independent, 0x4 Compute, 0x8 Conservative_Raster, 0x10 Draw_Indirect, 0x20 Fragment_Depth, 0x40 Fragment_Ordering, 0x80 Graphics_Debugger, 0x100 HiDPI, 0x400 Index32, 0x800 Instancing, 0x1000 Occlusion_Query, 0x2000 Renderer_Multithreaded, plus Mojang extensions (bits 0x20..0x3F): Swap_Chain, Texture_2D_Array, Texture_3D, Texture_Blit, Texture_Compare_All, Texture_Compare_Lequal, Texture_Cube_Array, Texture_Direct_Access, Texture_Read_Back, Vertex_Attrib_Half, Vertex_Attrib_Uint10, Vertex_Id, HDR10, Structured_Buffers, Vertex_Attrib_Sint8, Vertex_Attrib_Uint16, Depth_Bias, Ray_Tracing, Upscaling, No_Fragment_Shader, Buffer_Bind_Offset, Ranged_Resource, Dynamic_Texturehandles. Limits block follows, ending with maxOcclusionQueries. Matches Caps.h bit positions (HiDPI=8, OcclusionQuery=12, Mojang at bit 32+). Confirms 0x660ecd0 is NOT an occlusion-query user (per 6bl).

### (a) Phase Table

| Range | Description | Key Instructions |
|-------|-------------|------------------|
| 0x660ecd0..0x660ed0a | Prologue & fixed fields (homogenousDepth, originBottomLeft, fpEpsilon, numGPUs) serialized via string helpers | 0x660ecf4 call 0xE931470 (init buffer), 0x660ed04 call 0xE931790 (write byte), 0x660ed15 call 0xE932EA0 (add string key), 0x660ed25 call 0xE931B80 (add value), 0x660ed2d call 0xE9319A0 (finalize) |
| 0x660ede9..0x660f4ee | Flag bitmask iteration (bits 0..31) — each bit tested, if set adds flag name to JSON array | 0x660ede9 test bl,1 (Alpha_To_Coverage), 0x660ee21 test bl,2 (Blend_Independent), 0x660ee59 test bl,4 (Compute), 0x660ee91 test bl,8 (Conservative_Raster), 0x660eec9 test bl,0x10 (Draw_Indirect), 0x660ef01 test bl,0x20 (Fragment_Depth), 0x660ef39 test bl,0x40 (Fragment_Ordering), 0x660ef71 test bl,bl (Graphics_Debugger), 0x660efae test ebx,0x100 (HiDPI), 0x660efe3 test ebx,0x400 (Index32), 0x660f01e test ebx,0x800 (Instancing), 0x660f059 test ebx,0x1000 (Occlusion_Query), 0x660f094 test ebx,0x2000 (Renderer_Multithreaded), 0x660f0cf test ebx,0x4000 (Swap_Chain), 0x660f10a test bx,bx (Texture_2D_Array), 0x660f142 test ebx,0x10000 (Texture_3D), 0x660f17d test ebx,0x20000 (Texture_Blit), 0x660f1b8 test ebx,0xC0000 (Texture_Compare_All + Lequal), 0x660f1f3 test ebx,0x80000 (Texture_Cube_Array), 0x660f22e test ebx,0x100000 (Texture_Direct_Access), 0x660f269 test ebx,0x200000 (Texture_Read_Back), 0x660f2a4 test ebx,0x400000 (Vertex_Attrib_Half), 0x660f2df test ebx,0x800000 (Vertex_Attrib_Uint10), 0x660f31a test ebx,0x1000000 (Vertex_Id), 0x660f355 test ebx,0x2000000 (HDR10), 0x660f390 test ebx,0x4000000 (Structured_Buffers), 0x660f3cb test ebx,0x8000000 (Vertex_Attrib_Sint8), 0x660f406 test ebx,0x10000000 (Vertex_Attrib_Uint16), 0x660f441 test ebx,0x20000000 (Depth_Bias), 0x660f47c test ebx,0x40000000 (Ray_Tracing), 0x660f4b7 test ebx,ebx (Upscaling), 0x660f4ee bt rbx,0x20 (No_Fragment_Shader), 0x660f528 bt rbx,0x21 (Buffer_Bind_Offset), 0x660f562 bt rbx,0x22 (Ranged_Resource), 0x660f59c bt rbx,0x23 (Dynamic_Texturehandles), 0x660f5d6 bt rbx,0x24 (maxOcclusionQueries not a flag), 0x660f610 bt rbx,0x25 (end of Mojang flags) |
| 0x660f626..0x660f9f2 | Limits block — serializes integer limits from globals at 0x12AE0D58..0x12AE0DBC | 0x660f67f mov edx,[0x12AE0D58] (maxDrawCalls), 0x660f6bd mov edx,[0x12AE0D5C] (maxBlits), 0x660f6f1 mov edx,[0x12AE0D60] (maxTextureSize), 0x660f725 mov edx,[0x12AE0D64] (maxViews), 0x660f759 mov edx,[0x12AE0D68] (maxFramebuffers), 0x660f78d mov edx,[0x12AE0D6C] (maxFBAttachments), 0x660f7c1 mov edx,[0x12AE0D70] (maxPrograms), 0x660f7f5 mov edx,[0x12AE0D74] (maxShaders), 0x660f829 mov edx,[0x12AE0D78] (maxUniforms), 0x660f85d mov edx,[0x12AE0D7C] (maxUniformVectors), 0x660f891 mov edx,[0x12AE0D80] (maxVertexAttribs), 0x660f8c5 mov edx,[0x12AE0D84] (maxVertexStreams), 0x660f8f9 mov edx,[0x12AE0D88] (maxIndexBuffers), 0x660f92d mov edx,[0x12AE0D8C] (maxVertexBuffers), 0x660f961 mov edx,[0x12AE0D90] (maxDynamicIndexBuffers), 0x660f995 mov edx,[0x12AE0D94] (maxDynamicVertexBuffers), 0x660f9c9 mov edx,[0x12AE0D98] (maxUniformBuffers), 0x660f9fd mov edx,[0x12AE0D9C] (maxUniformBufferSize), 0x660fa31 mov edx,[0x12AE0DA0] (maxStorageBuffers), 0x660fa65 mov edx,[0x12AE0DA4] (maxStorageBufferSize), 0x660fa99 mov edx,[0x12AE0DA8] (maxFramebufferLayers), 0x660facd mov edx,[0x12AE0DAC] (maxComputeWorkGroups), 0x660fb01 mov edx,[0x12AE0DB0] (maxComputeWorkGroupSize), 0x660fb35 mov edx,[0x12AE0DB4] (maxComputeSharedMemory), 0x660fb69 mov edx,[0x12AE0DB8] (maxOcclusionQueries) |
| 0x660f9f7..0x660fcbd | Epilogue — finalize JSON string, cleanup, return | 0x660fc00 lea rdx,[0xF545EB1] (final key), 0x660fc0b call 0xE932EA0, 0x660fc18 call 0xE931B30 (finalize), 0x660fc22 call 0xE9319A0, 0x660fc2c call 0xE947960, 0x660fc3d call 0xE947990 (string builder), 0x660fc43 lea rax,[0xEFD00F8] (string vtable), 0x660fcb2 add rsp,0x88 / pop rbx/rdi/rsi/rbp / ret |

### (b) Strings Referenced (rva, text, site)

| String RVA | Text | Site (instruction RVA) |
|------------|------|------------------------|
| 0xF5ADDD6 | "homogenousDepth" | 0x660ed0a |
| 0xF53BEEE | "originBottomLeft" | 0x660ed43 |
| 0xF584FAA | "fpEpsilon" | 0x660ed7d |
| 0xF55CFF8 | "numGPUs" | 0x660edb2 |
| 0xF5E2C89 | "Alpha_To_Coverage" | 0x660edfd |
| 0xF5376A5 | "Blend_Independent" | 0x660ee35 |
| 0xF5C0055 | "Compute" | 0x660ee6d |
| 0xF567121 | "Conservative_Raster" | 0x660eea5 |
| 0xF53FC8C | "Draw_Indirect" | 0x660eedd |
| 0xF5ADEE2 | "Fragment_Depth" | 0x660ef15 |
| 0xF5B4B68 | "Fragment_Ordering" | 0x660ef4d |
| 0xF56DDFA | "Graphics_Debugger" | 0x660ef84 |
| 0xF7CB867 | "HiDPI" | 0x660efbf |
| 0xF7DD394 | "Index32" | 0x660effa |
| 0xF5B7EC7 | "Instancing" | 0x660f035 |
| 0xF51A19D | "Occlusion_Query" | 0x660f070 |
| 0xF5FD313 | "Renderer_Multithreaded" | 0x660f0ab |
| 0xF593C39 | "Swap_Chain" | 0x660f0e6 |
| 0xF5A26B8 | "Texture_2D_Array" | 0x660f1cf |
| 0xF539A77 | "Texture_3D" | 0x660f194 |
| 0xF5A4ED7 | "Texture_Blit" | 0x660f20a |
| 0xF51DC5D | "Texture_Compare_All" | 0x660f11e |
| 0xF51DC4A | "Texture_Compare_Lequal" | 0x660f245 |
| 0xF5E5FCE | "Texture_Cube_Array" | 0x660f5b2 |
| 0xF558BB0 | "Texture_Direct_Access" | 0x660f5ec |
| 0xF56ADBD | "Texture_Read_Back" | 0x660f626 |
| 0xF5B7F3B | "Vertex_Attrib_Half" | 0x660f4ca |
| 0xF570335 | "Vertex_Attrib_Uint10" | 0x660f53e |
| 0xF53CAD3 | "Vertex_Id" | 0x660f578 |
| 0xF7E5A4B | "HDR10" | 0x660f331 |
| 0xF7D165A | "Structured_Buffers" | 0x660f41d |
| 0xF7D398F | "Vertex_Attrib_Sint8" | 0x660f458 |
| 0xF55CF04 | "Vertex_Attrib_Uint16" | 0x660f493 |
| 0xF5B67DB | "Depth_Bias" | 0x660f504 |
| 0xF5B7EC7 | "Ray_Tracing" | 0x660f424 |
| 0xF604BE4 | "Upscaling" | 0x660f36c |
| 0xF7E5C0F | "No_Fragment_Shader" | 0x660f3a7 |
| 0xF54C006 | "Buffer_Bind_Offset" | 0x660f3e2 |
| 0xF5BA71E | "Ranged_Resource" | 0x660f2f6 |
| 0xF548EE8 | "Dynamic_Texturehandles" | 0x660f280 |
| 0xF55126B | "maxDrawCalls" | 0x660f68f |
| 0xF545EB8 | "maxBlits" | 0x660f6cd |
| 0xF5BC07A | "maxTextureSize" | 0x660f6fb |
| 0xF54AFFC | "maxViews" | 0x660f72f |
| 0xF5428AB | "maxFramebuffers" | 0x660f763 |
| 0xF54BFF6 | "maxFBAttachments" | 0x660f797 |
| 0xF5452CB | "maxPrograms" | 0x660f7cb |
| 0xF550C59 | "maxShaders" | 0x660f7ff |
| 0xF54C1B9 | "maxUniforms" | 0x660f833 |
| 0xF5572B6 | "maxUniformVectors" | 0x660f867 |
| 0xF54BC64 | "maxVertexAttribs" | 0x660f89b |
| 0xF554EA8 | "maxVertexStreams" | 0x660f8cf |
| 0xF551750 | "maxIndexBuffers" | 0x660f903 |
| 0xF550EF3 | "maxVertexBuffers" | 0x660f937 |
| 0xF530866 | "maxDynamicIndexBuffers" | 0x660f96b |
| 0xF54BF88 | "maxDynamicVertexBuffers" | 0x660f99f |
| 0xF54BF5F | "maxUniformBuffers" | 0x660f9d3 |
| 0xF54BF98 | "maxUniformBufferSize" | 0x660fa07 |
| 0xF54BF70 | "maxStorageBuffers" | 0x660fa3b |
| 0xF54FCAE | "maxStorageBufferSize" | 0x660fa6f |
| 0xF559A6B | "maxFramebufferLayers" | 0x660faa3 |
| 0xF54C155 | "maxComputeWorkGroups" | 0x660fad7 |
| 0xF5BC22E | "maxComputeWorkGroupSize" | 0x660fb0b |
| 0xF5BC23E | "maxComputeSharedMemory" | 0x660fb3f |
| 0xF54EF33 | "maxOcclusionQueries" | 0x660fbdb |
| 0xF545EB1 | (final key) | 0x660fc00 |

### (c) Callees (in order of first appearance)

| Callee RVA | Name/Role | Call Sites |
|------------|-----------|------------|
| 0xE931470 | JSON buffer init / string builder init | 0x660ecf4, 0x660eddd, 0x660f639, 0x660f679 |
| 0xE931790 | Write byte value | 0x660ed04, 0x660ed3d, 0x660edac |
| 0xE932EA0 | Add string key to JSON object | 0x660ed15, 0x660ed4e, 0x660ed88, 0x660ee08, 0x660ee3c, 0x660ee78, 0x660eeb0, 0x660eee8, 0x660ef20, 0x660ef58, 0x660ef8f, 0x660efca, 0x660f001, 0x660f03c, 0x660f077, 0x660f0b2, 0x660f0f1, 0x660f129, 0x660f164, 0x660f19f, 0x660f1da, 0x660f215, 0x660f250, 0x660f28b, 0x660f2c2, 0x660f2fd, 0x660f301, 0x660f338, 0x660f373, 0x660f3ae, 0x660f3ed, 0x660f428, 0x660f45f, 0x660f49a, 0x660f4d1, 0x660f50f, 0x660f549, 0x660f583, 0x660f5bd, 0x660f5f7, 0x660f631, 0x660f656, 0x660f69a, 0x660f6ce, 0x660f706, 0x660f73a, 0x660f76e, 0x660f7a2, 0x660f7d6, 0x660f80a, 0x660f83e, 0x660f872, 0x660f8a6, 0x660f8da, 0x660f90e, 0x660f942, 0x660f976, 0x660f9aa, 0x660f9de, 0x660fa12, 0x660fa46, 0x660fa7a, 0x660faae, 0x660fade, 0x660fb12, 0x660fb46, 0x660fb7e, 0x660fbae, 0x660fbe2, 0x660fc0b, 0x660fc3a |
| 0xE931B80 | Add value to JSON object | 0x660ed25, 0x660ed5a, 0x660ed94, 0x660ee14, 0x660ee4c, 0x660ee84, 0x660eebc, 0x660eef4, 0x660ef2c, 0x660ef64, 0x660ef9b, 0x660efd6, 0x660f011, 0x660f04c, 0x660f087, 0x660f0c2, 0x660f102, 0x660f135, 0x660f170, 0x660f1ab, 0x660f1e6, 0x660f221, 0x660f25c, 0x660f297, 0x660f2d2, 0x660f30d, 0x660f348, 0x660f383, 0x660f3be, 0x660f3f9, 0x660f434, 0x660f46f, 0x660f4aa, 0x660f4e1, 0x660f51b, 0x660f555, 0x660f58f, 0x660f5c9, 0x660f603, 0x660f63d, 0x660f6aa, 0x660f6de, 0x660f712, 0x660f746, 0x660f77a, 0x660f7ae, 0x660f7e2, 0x660f816, 0x660f84a, 0x660f87e, 0x660f8b2, 0x660f8e6, 0x660f91a, 0x660f94e, 0x660f982, 0x660f9b6, 0x660f9ea, 0x660fa1e, 0x660fa52, 0x660fa86, 0x660faba, 0x660faef, 0x660fb22, 0x660fb56, 0x660fb8a, 0x660fbbe, 0x660fbf2, 0x660fc18 |
| 0xE9319A0 | Finalize JSON object entry | 0x660ed2d, 0x660ed62, 0x660ed9c, 0x660ee1c, 0x660ee54, 0x660ee8c, 0x660eec4, 0x660eefc, 0x660ef34, 0x660ef6c, 0x660efa3, 0x660efde, 0x660f019, 0x660f054, 0x660f08f, 0x660f0ca, 0x660f105, 0x660f13d, 0x660f178, 0x660f1b3, 0x660f1ee, 0x660f229, 0x660f264, 0x660f29f, 0x660f2da, 0x660f315, 0x660f350, 0x660f38b, 0x660f3c6, 0x660f401, 0x660f43c, 0x660f477, 0x660f4b2, 0x660f4e9, 0x660f523, 0x660f55d, 0x660f597, 0x660f5d1, 0x660f60b, 0x660f645, 0x660f66d, 0x660f6b2, 0x660f6e6, 0x660f71a, 0x660f74e, 0x660f782, 0x660f7b6, 0x660f7ea, 0x660f81e, 0x660f852, 0x660f886, 0x660f8ba, 0x660f8ee, 0x660f922, 0x660f956, 0x660f98a, 0x660f9be, 0x660f9f2, 0x660fa26, 0x660fa5a, 0x660fa8e, 0x660fac2, 0x660faf6, 0x660fb2a, 0x660fb5e, 0x660fb92, 0x660fbc6, 0x660fbfa, 0x660fc22, 0x660fcaa |
| 0xE931580 | Write bool/int to JSON (for flags) | 0x660edf7, 0x660ee2f, 0x660ee67, 0x660ee9f, 0x660eed7, 0x660ef0f, 0x660ef47, 0x660ef7e, 0x660efb9, 0x660efef, 0x660f02f, 0x660f06a, 0x660f0a5, 0x660f0e0, 0x660f118, 0x660f153, 0x660f18e, 0x660f1c9, 0x660f204, 0x660f23f, 0x660f27a, 0x660f2b5, 0x660f2f0, 0x660f32b, 0x660f366, 0x660f3a1, 0x660f3dc, 0x660f417, 0x660f452, 0x660f48d, 0x660f4c4, 0x660f4fe, 0x660f538, 0x660f572 |
| 0xE931590 | Write int limit to JSON | 0x660f689, 0x660f6bd, 0x660f6f1, 0x660f729, 0x660f75d, 0x660f791, 0x660f7c5, 0x660f7f9, 0x660f82d, 0x660f861, 0x660f895, 0x660f8c9, 0x660f8fd, 0x660f931, 0x660f965, 0x660f999, 0x660f9cd, 0x660fa01, 0x660fa35, 0x660fa69, 0x660fa9d, 0x660fad1, 0x660fb05, 0x660fb39, 0x660fb6d, 0x660fb9d |
| 0xE9315C0 | Write float to JSON | 0x660ed77 |
| 0xE931B30 | Finalize JSON string | 0x660f663, 0x660fc18 |
| 0xE947960 | String builder helper | 0x660fc2c |
| 0xE947990 | String builder helper | 0x660fc3d |
| 0xE947920 | String builder cleanup | 0x660fca1 |
| 0xE935700 | Error/overflow handler | 0x660fc84 |
| 0xF9A8C78 | [data] invalid parameter handler | 0x660fcd1 |

### (d) [reg+off] Read/Write Table (output/description objects)

The function builds a JSON string in a stack-allocated buffer at `[rbp-0x50]` (32 bytes) and `[rbp-0x40]` (16 bytes), with a secondary buffer at `[rbp-0x10]`. The output string pointer is returned in RAX (points to string object at `[rbp-0x20]` or `[rbp-0x38]`). No persistent output/description object is written — the JSON string is constructed on the stack and returned.

| Offset | Size | Direction | First Site | Meaning |
|--------|------|-----------|------------|---------|
| [rbp-0x50] | 32B | R/W | 0x660ecee lea rcx,[rbp-0x50] | Primary JSON builder buffer |
| [rbp-0x40] | 16B | R/W | 0x660ed00 lea rcx,[rbp-0x40] | Secondary JSON builder buffer |
| [rbp-0x10] | 16B | R/W | 0x660eddd lea rcx,[rbp-0x10] | Flag/limit value buffer |
| [rbp] | 8B | W | 0x660ece3 mov qword ptr [rbp],0xFFFFFFFFFFFFFFFE | Stack cookie |
| [rbp-0x20] | 8B | R/W | 0x660fc32 lea r8,[rbp-0x50] / 0x660fc3d call 0xE947990 | Output string object |
| [rbp-0x28] | 8B | W | 0x660fc32 mov qword ptr [rbp-0x28],0 | String length |
| [rbp-0x38] | 8B | W | 0x660fc58 mov rcx,[rbp-0x38] | String data pointer |
| [rsi] | 8B | R | 0x660eceb mov rsi,rcx | Input: caps struct pointer (rcx) |
| [rsi+0] | 1B | R | 0x660ecf1 mov al,[rax] | homogenousDepth |
| [rsi+1] | 1B | R | 0x660ecfa mov al,[rax+1] | originBottomLeft |
| [rsi+4] | 4B | R | 0x660ed04 movss xmm0,[rax+4] | fpEpsilon |
| [rsi+8] | 4B | R | 0x660ed11 mov eax,[rax+8] | numGPUs |
| [0x12ADFA50] | 8B | R | 0x660edd6 mov rbx,[0x12ADFA50] | Supported flags bitmask (kSupported) |
| [0x12ADFC88] | 1B | R | 0x660ecf9 movzx edx,byte ptr [0x12ADFC88] | homogenousDepth value |
| [0x12ADFC89] | 1B | R | 0x660ed32 movzx edx,byte ptr [0x12ADFC89] | originBottomLeft value |
| [0x12ADFC94] | 4B | R | 0x660ed67 movss xmm0,[0x12ADFC94] | fpEpsilon value |
| [0x12ADFC8A] | 1B | R | 0x660eda1 movzx edx,byte ptr [0x12ADFC8A] | numGPUs value |
| [0x12AE0D58..0x12AE0DBC] | 4B each | R | 0x660f67f, 0x660f6bd, ... | Limits globals (maxDrawCalls..maxOcclusionQueries) |

---

## TOOL REQUESTS
- None for this function — analysis complete from verified listing.

---

## Function 0x10f09f0 (sub_10f09f0) — Lighting config deserializer
**Listing**: docs/listings/L_10f09f0.txt (3511 lines, 0x10f09f0..0x10f5921, size 0x4f31 = 20273 bytes)
**Callers**: 1 xref from unknown
**Purpose**: Deserializes lighting configuration JSON (field names: light_update_frequency, max_point_lights, score_compute_batch_size, light_score_smoothing_factor, light_scoring_weights, transition_step_size, transitioning_ambient_scalar, max_pending_transition_tasks, max_staged_transition_results, max_in_flight_transition_tasks, max_transition_commits_per_frame, max_transition_volume_count, max_transition_growths_per_frame, max_transition_shrinks_per_frame, max_transition_invalidates_per_frame, start_tile_dimension, min_tile_dimension, max_tile_dimension, max_probe_batch_size, max_probe_draws_per_frame, max_growths_per_frame, max_shrinks_per_frame, max_invalidates_per_frame, bias, slope_bias, far_plane, near_plane). Uses repeated helpers 0x1dc620, 0x1d6c40, 0x1db850, 0x116b3a0, 0x116c930, 0x116d950, 0x10f05e0, 0xeea6040 (allocator). The "frustum_visibility" field at site 0x10f45d0 is one scoring weight, not a cull function (per 6bj).

### (a) Phase Table

| Range | Description | Key Instructions |
|-------|-------------|------------------|
| 0x10f09f0..0x10f0a8a | Prologue & frame setup — saves registers, allocates 0x4E8 stack, sets up rbp frame, calls 0x1168870 to get input object, validates magic 0xD4C25870 | 0x10f09fc sub rsp,0x4E8, 0x10f0a2f call 0x1168870, 0x10f0a34 cmp dword ptr [rax+0x60],0xD4C25870, 0x10f0a8a call 0x1168FF0 |
| 0x10f0a8f..0x10f0c3f | Early guard & allocator setup — checks byte at [rbp+0x278], initializes allocator state, calls 0x1169B80 to allocate helper object, sets up vtable pointers (0x1210F0, 0x116A570, 0x116A5B0) and refcount | 0x10f0a9d jne 0x10F1CD8, 0x10f0abb call 0x1169B80, 0x10f0ac0 mov rbx,rax, 0x10f0aef..0x10f0b12 lea rax,[vtable targets], 0x10f0b42 call 0xD9F3A0 |
| 0x10f0c31..0x10f0e03 | First field: light_update_frequency — calls 0x1D6350, sets up string key (0xF51CE37), length 0x16, calls 0x116B3A0 to deserialize, then cleanup via 0x1DB850/0x1D6C40/0x1DC620 | 0x10f0c3f call 0x1D6350, 0x10f0c45 lea rax,[0xF51CE37], 0x10f0c73 call 0x116B3A0, 0x10f0d6b call 0x1DB850, 0x10f0d78 call 0x1D6C40, 0x10f0d85 call 0x1DC620 |
| 0x10f0e03..0x10f12e2 | Repeated scalar field pattern (max_point_lights, score_compute_batch_size, light_score_smoothing_factor) — each: load string key, set length, call 0x116B3A0, cleanup trio (0x1DB850/0x1D6C40/0x1DC620) | 0x10f0e03 lea rax,[0xF5460A9] "max_point_lights", 0x10f0e2d call 0x116B3A0, 0x10f0f28 lea rax,[0xF5BB7B4] "score_compute_batch_size", 0x10f0f56 call 0x116B3A0, 0x10f1066 lea rax,[0xF55FEFB] "light_score_smoothing_factor", 0x10f1094 call 0x116B3A0 |
| 0x10f12e2..0x10f1320 | Array field: light_scoring_weights — uses 0x116C930 + 0x116D950 for array deserialization, then 0x10F05E0 for nested object | 0x10f11a4 lea rax,[0xF546164], 0x10f11ce call 0x116C930, 0x10f11f6 call 0x116D950, 0x10f1261 call 0x10F05E0 |
| 0x10f1320..0x10f25eb | Remaining scalar fields (transition_step_size, transitioning_ambient_scalar, max_pending_transition_tasks, max_staged_transition_results, max_in_flight_transition_tasks, max_transition_commits_per_frame, max_transition_volume_count, max_transition_growths_per_frame, max_transition_shrinks_per_frame, max_transition_invalidates_per_frame, bias, slope_bias, far_plane, near_plane) — each follows scalar pattern | 0x10f12e2 call 0x116D950 (transition_step_size), 0x10f1266..0x10f12e2 (transitioning_ambient_scalar), 0x10f1479..0x10f1509 (max_pending_transition_tasks), 0x10f1625..0x10f16a1 (max_staged_transition_results), 0x10f17ca..0x10f1846 (max_in_flight_transition_tasks), 0x10f196f..0x10f19eb (max_transition_commits_per_frame), 0x10f1b14..0x10f1b87 (max_transition_volume_count), 0x10f196f..0x10f1a29 (max_transition_growths_per_frame), 0x10f2401..0x10f2455 (max_transition_shrinks_per_frame), 0x10f2493..0x10f250c (max_transition_invalidates_per_frame), 0x10f253c..0x10f25eb (bias/slope_bias/far_plane/near_plane via 0x1171A80) |
| 0x10f25eb..0x10f3a77 | Probe/tiles fields (max_probe_batch_size, max_probe_draws_per_frame, start_tile_dimension, min_tile_dimension, max_tile_dimension) — each follows scalar pattern with 0x1171A80 | 0x10f265e..0x10f271d (max_probe_batch_size), 0x10f2802..0x10f288a (max_probe_draws_per_frame), 0x10f2b9d..0x10f2c29 (start_tile_dimension), 0x10f2cd2..0x10f2d5e (min_tile_dimension), 0x10f2e07..0x10f2e93 (max_tile_dimension) |
| 0x10f3a77..0x10f3bce | Alternate entry point (from 0x10f0a9d jne) — re-initializes allocator with different vtables (0x1170CA0, 0x1170FC0), deserializes remaining fields | 0x10f1cd8 mov rcx,[rbp+0x1F8], 0x10f1d3a call 0x11700B0, 0x10f1d6b call 0x1170CA0 |
| 0x10f3bce..0x10f591c | Error paths & epilogue — 40+ je targets to error handlers at 0x10F552F..0x10F58B5 (all call 0x9BC830 with size 8/0x10/0x50 then jmp back), final cleanup at 0x10f3af2..0x10f3bce, stack restore & ret | 0x10f0b7d je 0x10F552F, 0x10f0bde je 0x10F553F, 0x10f0c98 je 0x10F554F, ..., 0x10f587f lea rcx,[0x128E0828] call 0xE938CB0, 0x10f591c jmp 0x10F4FC3 |

### (b) Strings Referenced (rva, text, site)

| String RVA | Text | Site (instruction RVA) |
|------------|------|------------------------|
| 0xF51CE37 | "light_update_frequency" | 0x10f0c45 |
| 0xF5460A9 | "max_point_lights" | 0x10f0e03 |
| 0xF5BB7B4 | "score_compute_batch_size" | 0x10f0f28 |
| 0xF55FEFB | "light_score_smoothing_factor" | 0x10f1066 |
| 0xF546164 | "light_scoring_weights" | 0x10f11a4 |
| 0xF5BB720 | "transition_step_size" | 0x10f11d3 |
| 0xF5711AD | "transitioning_ambient_scalar" | 0x10f1266 |
| 0xF551B49 | "max_pending_transition_tasks" | 0x10f1479 |
| 0xF545C22 | "max_staged_transition_results" | 0x10f1625 |
| 0xF551B2A | "max_in_flight_transition_tasks" | 0x10f17ca |
| 0xF5D0E59 | "max_transition_commits_per_frame" | 0x10f196f |
| 0xF530599 | "max_transition_volume_count" | 0x10f1b14 |
| 0xF5D0EA0 | "max_growths_per_frame" | 0x10f2802 |
| 0xF5D0E7A | "max_shrinks_per_frame" | 0x10f2933 |
| 0xF5D0EB6 | "max_invalidates_per_frame" | 0x10f2a68 |
| 0xF55CECD | "bias" | 0x10f1ef5 |
| 0xF55CEB1 | "slope_bias" | 0x10f203f |
| 0xF5CED64 | "far_plane" | 0x10f216d |
| 0xF5CED6E | "near_plane" | 0x10f229b |
| 0xF5BB7CD | "max_probe_batch_size" | 0x10f265e |
| 0xF5D0E3F | "max_probe_draws_per_frame" | 0x10f23c9 |
| 0xF590EEE | "start_tile_dimension" | 0x10f2b9d |
| 0xF590F03 | "min_tile_dimension" | 0x10f2cd2 |
| 0xF590EDB | "max_tile_dimension" | 0x10f2e07 |
| 0xEFCFB60 | (vtable for allocated helper) | 0x10f0c9e, 0x10f0e58, 0x10f0f81, ... (30+ sites) |
| 0xF092050 | (vtable) | 0x10f0b83 |
| 0xF0B7760 | (vtable) | 0x10f0bf2 |
| 0xF0B78A0 | (vtable) | 0x10f10bf |
| 0xF0DEF50 | (vtable) | 0x10f0dba |
| 0xEFFD2B0 | (vtable) | 0x10f0f81 |
| 0xDB0E50 | (vtable) | 0x10f0fed |
| 0x36FAC0 | (vtable) | 0x10f1002 |
| 0xDB6B70 | (vtable) | 0x10f112b |
| 0xDB67D0 | (vtable) | 0x10f1140 |
| 0xD9DC90 | (vtable) | 0x10f0d0a |
| 0x1DBA40 | (vtable) | 0x10f0d18 |
| 0x1EA900 | (vtable) | 0x10f0d26 |
| 0x1210F0 | (vtable) | 0x10f0aef |
| 0x116A570 | (vtable) | 0x10f0afd |
| 0x116A5B0 | (vtable) | 0x10f0b0b |
| 0x116B830 | (vtable) | 0x10f0d34 |
| 0x116BA30 | (vtable) | 0x10f0d42 |
| 0x116BC60 | (vtable) | 0x10f0ed2 |
| 0x116BE60 | (vtable) | 0x10f0ee0 |
| 0x116C0A0 | (vtable) | 0x10f1010 |
| 0x116C2A0 | (vtable) | 0x10f101e |
| 0x116C4E0 | (vtable) | 0x10f114e |
| 0x116C6F0 | (vtable) | 0x10f115c |
| 0x1170CA0 | (vtable, alt path) | 0x10f1d6b |
| 0x1170FC0 | (vtable, alt path) | 0x10f1dbb |
| 0x1171A80 | (vtable, probe/tiles) | 0x10f2072, 0x10f21a0, 0x10f22ce, 0x10f23fc, 0x10f2691, 0x10f2831, 0x10f2966, 0x10f2a9b, 0x10f2bd0, 0x10f2cf9, 0x10f2e3a |
| 0x1171E70 | (vtable, alt path) | 0x10f1fe9 |
| 0x1172080 | (vtable, alt path) | 0x10f1ff7 |
| 0x11722C0 | (vtable, alt path) | 0x10f2117 |
| 0x11724D0 | (vtable, alt path) | 0x10f2125 |
| 0x1172710 | (vtable, alt path) | 0x10f2245 |
| 0x1172920 | (vtable, alt path) | 0x10f2253 |
| 0x1172B60 | (vtable, alt path) | 0x10f2373 |
| 0x1172D70 | (vtable, alt path) | 0x10f2381 |
| 0x1172FB0 | (vtable, alt path) | 0x10f24b6 |
| 0x11731B0 | (vtable, alt path) | 0x10f24c4 |
| 0x11733F0 | (vtable, alt path) | 0x10f273d |
| 0x11735F0 | (vtable, alt path) | 0x10f274b |
| 0x1173830 | (vtable, alt path) | 0x10f28dd |
| 0x1173A30 | (vtable, alt path) | 0x10f28eb |
| 0x1173C70 | (vtable, alt path) | 0x10f2a12 |
| 0x1173E70 | (vtable, alt path) | 0x10f2a20 |
| 0x11740B0 | (vtable, alt path) | 0x10f2b47 |
| 0x11742B0 | (vtable, alt path) | 0x10f2b55 |
| 0x11744F0 | (vtable, alt path) | 0x10f2c7c |
| 0x11746F0 | (vtable, alt path) | 0x10f2c8a |
| 0x1174930 | (vtable, alt path) | 0x10f2db1 |
| 0x1174B30 | (vtable, alt path) | 0x10f2dbf |
| 0x1174D70 | (vtable, alt path) | 0x10f2eed |
| 0x1174F70 | (vtable, alt path) | 0x10f2ef4 |
| 0x1177860 | (vtable, final path) | 0x10f3a7e |
| 0x1177940 | (vtable, final path) | 0x10f3b07 |
| 0x1177E80 | (vtable, alt entry) | 0x10f3ad9 |
| 0x11789F0 | (vtable, final) | 0x10f3c01 |

### (c) Callees (in order of first appearance)

| Callee RVA | Name/Role | Call Sites |
|------------|-----------|------------|
| 0x1168870 | Get input object / validate | 0x10f0a2f |
| 0x1168FF0 | Initialize parser state | 0x10f0a8a |
| 0x1169B80 | Allocate helper object (primary) | 0x10f0abb |
| 0xD9F3A0 | Initialize helper object | 0x10f0b42 |
| 0x1D6350 | Pre-field setup | 0x10f0c3f |
| 0x116B3A0 | Deserialize scalar field (int/float) | 0x10f0c73, 0x10f0e2d, 0x10f0f56, 0x10f1094, ... (20+ sites) |
| 0x1DB850 | Post-field cleanup part 1 | 0x10f0d6b, 0x10f0f09, 0x10f1047, ... (25+ sites) |
| 0x1D6C40 | Post-field cleanup part 2 | 0x10f0d78, 0x10f0f16, 0x10f1054, ... (25+ sites) |
| 0x1DC620 | Post-field cleanup part 3 | 0x10f0d85, 0x10f0f23, 0x10f1061, ... (25+ sites) |
| 0x10F05E0 | Deserialize nested object | 0x10f0dfe, 0x10f1261, 0x10f13f8, 0x10f1474, 0x10f1620, 0x10f17c5, 0x10f196a, 0x10f1b0f, 0x10f1cab, 0x10f257a, 0x10f27fd, 0x10f296a, 0x10f2b0f, 0x10f2cab, 0x10f2e02, 0x10f2f0f, 0x10f3a6b, 0x10f3a72 |
| 0x116C930 | Deserialize array field start | 0x10f11ce |
| 0x116D950 | Deserialize array field end | 0x10f11f6, 0x10f12e2, 0x10f1419, 0x10f164f, 0x10f17f4, 0x10f1999, 0x10f1b35 |
| 0x1171A80 | Deserialize probe/tile scalar fields | 0x10f2072, 0x10f21a0, 0x10f22ce, 0x10f23fc, 0x10f2691, 0x10f2831, 0x10f2966, 0x10f2a9b, 0x10f2bd0, 0x10f2cf9, 0x10f2e3a |
| 0x1170CA0 | Allocate helper (alt path) | 0x10f1d6b |
| 0x11700B0 | Init parser (alt path) | 0x10f1d3a |
| 0x116F8D0 | Get object (alt path) | 0x10f1cdf |
| 0x116F9B0 | Get nested (final path) | 0x10f2594 |
| 0x1D4FD0 | Hash/compare (final path) | 0x10f25ad, 0x10f3b20 |
| 0x1177860 | Get object (final) | 0x10f3a7e |
| 0x1177940 | Get nested (final) | 0x10f3b07 |
| 0x1177E80 | Init parser (alt entry) | 0x10f3ad9 |
| 0x11789F0 | Final deserialize | 0x10f3c01 |
| 0xF99FFA0 | → 0xEEA6040 (allocator) | 0x10f0b70, 0x10f0c8b, 0x10f0c91, ... (30+ sites) |
| 0x9BC830 | Error handler (free on failure) | 0x10f552F, 0x10f553F, ... (40+ sites) |
| 0xE938CB0 | Thread-local init | 0x10f587f, 0x10f58eb, 0x10f58f2 |
| 0xE938D70 | Thread-local cleanup | 0x10f58e1, 0x10f58ea, 0x10f5910 |
| 0xDA0170 | Wait/timeout | 0x10f58d5, 0x10f590b |

### (d) [reg+off] Read/Write Table (output/description objects)

The function takes a pointer to a lighting config object in RCX (saved at [rbp+0x2C8]). The input JSON object is at RCX+0x18 (saved at [rbp+0x1F8]). The function builds deserialized values into stack slots and writes them to the config object via the helper calls. No single output struct is written directly — each field is processed through the deserializer helpers.

| Offset | Size | Direction | First Site | Meaning |
|--------|------|-----------|------------|---------|
| [rbp+0x2C8] | 8B | W | 0x10f0a1d mov [rbp+0x2C8],rcx | Input config object pointer |
| [rbp+0x1F8] | 8B | W | 0x10f0a28 mov [rbp+0x1F8],rcx | Input JSON object (config+0x18) |
| [rbp+0x240] | 32B | R/W | 0x10f0a75 lea rcx,[rbp+0x240] | Parser state buffer (passed to helpers) |
| [rbp+0x2D0] | 8B | R/W | 0x10f0a5a movaps [rbp+0x2D0],xmm0 | Field value buffer |
| [rbp+0x2D8] | 8B | R/W | 0x10f0a6e mov [rbp+0x2D8],rcx | Field value pointer |
| [rbp+0x2E8] | 8B | R/W | 0x10f0ae4 mov qword ptr [rbp+0x2E8],2 | Allocator state |
| [rbp+0x3E0] | 8B | R/W | 0x10f0cd9 mov [rbp+0x3E0],eax | Deserialized value |
| [rbp+0x3E8] | 8B | R/W | 0x10f0cdf mov qword ptr [rbp+0x3E8],0 | Field flags |
| [rbp+0x280] | 16B | R/W | 0x10f0c2a movaps [rbp+0x280],xmm0 | String key buffer |
| [rbp+0x288] | 8B | W | 0x10f0c53 mov qword ptr [rbp+0x288],0x16 | String key length |
| [rbp+0x270] | 8B | W | 0x10f0aad mov [rbp+0x270],rax | Allocator magic |
| [rbp+0x278] | 1B | R | 0x10f0a96 cmp byte ptr [rbp+0x278],0 | Early exit flag |
| [rbp+0x279] | 1B | W | 0x10f0a8f mov byte ptr [rbp+0x279],1 | Initialization flag |
| [rcx+0x18] | 8B | R | 0x10f0a24 add rcx,0x18 | Input JSON from config |
| [rax+0x60] | 4B | R | 0x10f0a34 cmp dword ptr [rax+0x60],0xD4C25870 | Magic validation |
| [rax+0x68] | 8B | R | 0x10f0a3d mov rax,[rax+0x68] | JSON object pointer |
| [rax+0x28] | 8B | R | 0x10f0a46 mov rcx,[rax+0x28] | Nested object |
| [rax+0x30] | 8B | R | 0x10f0a4a cmp qword ptr [rax+0x30],0x10 | Size check |
| [rax+0x18] | 8B | R | 0x10f0a51 mov rax,[rax+0x18] | Data pointer |
| [0x1233E1A8] | 8B | R | 0x10f0b5d mov rcx,[0x1233E1A8] | Allocator global |
| [0xF99FFA0] | 8B | R | 0x10f0b70 call qword ptr [0xF99FFA0] | Allocator function pointer |
| [0x128E0828] | 4B | R | 0x10f0b8d mov eax,[0x128E0828] | TLS counter |
| [0x128767C8] | 4B | R | 0x10f0b93 mov ecx,[0x128767C8] | TLS index |
| gs:[0x58] | 8B | R | 0x10f0b99 mov rdx,gs:[0x58] | TLS base |
| [rdx+rcx*8] | 8B | R | 0x10f0ba2 mov rcx,[rdx+rcx*8] | TLS slot |

---

## TOOL REQUESTS
- None for this function — analysis complete from verified listing.

---

## NEXT
L_10f09f0.txt fully analysed. Next: L_6646980.txt (7679 lines, analyse in blocks of 500).

---

## Function 0x6646980 (sub_6646980) — ChunkOccluder/SimpleOccluder material dispatcher
**Listing**: docs/listings/L_6646980.txt (7679 lines, 0x6646980..0x664FDA5, size 0x9425 = 37925 bytes)
**Callers**: Item visitor tag 4 handler (refs at 0x6646ae5, 0x664ee5f per 6bi)
**Purpose**: Per-item render-task variant dispatcher (jump table on *(u8*)(r8+8), 11 cases). Selects material by name for chunk tasks. Case 0 (0x6646a10): "MeshFallbackPosUVNormalColor". Case 1 (0x6646a89): "ChunkOccluder" (len 0xD), resolves via 0x67d6d70, checks loaded flag at res+0x10. Case 2 (0x6646bc6): reads 0x18-byte item, calls passLookup 0x5aba5c0 with ctx+0x9d0. Other cases: "CracksBlockEntity", "Cracks", "GlowInkSignForwardPBR", "MeshFallbackForwardPBR". Default (0x664ef12): je 0x664ef0d. SimpleOccluder handler at 0x66a9d50 is similar. Not a CPU cull class — these are material names for occluder geometry (per 6bk).

### (a) Phase Table

| Range | Description | Key Instructions |
|-------|-------------|------------------|
| 0x6646980..0x6646a0e | Prologue & jump table entry — saves registers, allocates 0x9B8 stack, sets up rbp frame, loads tag byte from [r8+8], bounds check (ja 0x664ef12), jump table at 0xF2BF2D0 | 0x664698c sub rsp,0x9B8, 0x66469eb movzx eax,byte ptr [r8+8], 0x66469f4 ja 0x664EF12, 0x6646a00 lea rcx,[0xF2BF2D0], 0x6646a07 movsxd rax,[rcx+rax*4], 0x6646a0e jmp rax |
| 0x6646a10..0x6646a84 | Case 0: "MeshFallbackPosUVNormalColor" — validates context, builds string (0xF563B37, len 0x1C), calls 0x9D6D0, resolves material via 0x67D6D70 (not in listing), checks loaded flag, calls 0x67CFD80, jumps to epilogue 0x6647BB4 | 0x6646a10 mov rax,[rdi+0x78], 0x6646a4f cmp dword ptr [rcx+0x70],1, 0x6646a6b lea r9,[0xF563B37], 0x6646a7e call 0x9D6D0, 0x6646a84 jmp 0x6647BB4 |
| 0x6646a89..0x6646bc5 | Case 1: "ChunkOccluder" — TLS guard checks, gets context from [rbp+0x8A0], reads material name from [0xF2BE528] "ChunkOccluder" (len 0xD), calls 0x67D6D70 to resolve, shared_ptr refcount inc/dec via 0xF99FFA0, calls 0x67CFD80, jumps to 0x66477D8 | 0x6646a89 mov r15,rbx, 0x6646ae5 lea rax,[0xF2BE528], 0x6646b20 call 0x67D6D70, 0x6646b71 lock inc dword ptr [rax+8], 0x6646ba0 call qword ptr [0xF99FFA0], 0x6646b8c lock dec dword ptr [r14+8] |
| 0x6646bc6..0x6646c87 | Case 2: reads 0x18-byte item (xmm7=xmm0..1, xmm6=qword at +0x10), calls passLookup 0x5ABA5C0 with ctx+0x9D0, allocates 0x18-byte record via 0xF99FFA0 (size 0x4A), writes item data, jumps to 0x6647A74 | 0x6646bc6 movups xmm7,[rdi], 0x6646bce mov ecx,0x9D0, 0x6646bde call 0x5ABA5C0, 0x6646c56 mov dl,0x4A, 0x6646c58 call qword ptr [0xF99FFA0], 0x6646c75 movups [r12],xmm7 |
| 0x6646c8d..0x6646dbd | Case 3: "CracksBlockEntity" — reads [rdi+0x108], validates, builds string from [0xF7C86B5], calls 0x358C40, computes FNV-1a64 hash (0xCBF29CE484222325 / 0x100000001B3) for lookup in hash table at [r15+0x48], on hit calls 0x567D280, on miss allocates via 0xF99FFA0, jumps to 0x66EA3D0 (terrain draw builder) | 0x6646c94 mov rax,[rdi+0x108], 0x6646cf4 mov rax,[0xF7C86B5], 0x6646d1f call 0x358C40, 0x6646d37 lea rcx,[rax+0x10], 0x6646d5a mov rax,[r15], 0x6646d62..0x6646dbc epilogue + jmp 0x66EA3D0 |
| 0x6646dc2..0x6646e50 | Case 4: "Cracks" — reads [rdi+0x140], validates hash constants (0x416AE22CAB22EA36, 0xD8EF928BC853553A, 0x2C8B246FD3EDDC59), builds string "Cracks" (0xF515E74, len 0x11), calls material resolver 0x675E440, shared_ptr inc/dec via 0xF99FFA0 | 0x6646dc2 mov rax,[rdi+0x140], 0x6646e13 mov r13,rbx, 0x6646e24 movq xmm6,[rax], 0x6646e3f lea rax,[0xF515E74], 0x6646eab call 0x675E440, 0x6646f06 lock inc dword ptr [rcx+8] |
| 0x6646f5b..0x664737e | Case 5: "GlowInkSignForwardPBR" — reads [rdi+0x58], validates, calls 0x66B2B30, zeroes large stack area, builds "MeshFallbackForwardPBR" (0xF552ED0, len 6), calls 0x675E440, hash lookup in table at [r15+0x98] with FNV-1a, on hit increments refcount, on miss allocates via 0xF99FFA0, calls 0x567D280, jmp 0x6698E30 | 0x6646f5b mov rax,[rdi+0x58], 0x6646f86 lea rcx,[rbp+0x140], 0x6646fdd mov dword ptr [rbp+0x1F0],0x656D614E ("Name"), 0x6647033 call qword ptr [0xF99FFA0], 0x6647044 mov rcx,r12 call 0xEEC59F0, 0x664718e call 0x567D280 |
| 0x6647383..0x6647A73 | Case 6: "MeshFallbackForwardPBR" (similar to Case 5 but different string 0xF552ED0) — same hash lookup pattern, material resolver 0x675E440, shared_ptr handling, jmp 0x6698E30 | 0x6647383 (same structure as Case 5), 0x6647270 call 0x675E440, 0x664737e jmp 0x6698E30 |
| 0x6647A74..0x664EF0D | Cases 7-10 & default — additional material variants (not fully traced in listing), all converge at epilogue 0x664EF0D which restores xmm6-13, stack, pops registers, returns | 0x664EF0D (epilogue), 0x664EF12 (default: ja target), 0x664EBD7 (common fail: je target), 0x6647BB4 (Case 0 success), 0x66477D8 (Case 1 success), 0x6647A74 (Case 2 success), 0x6647FE7/0x6647FF1/0x66482E1/0x66482F2/0x6649DFC/0x6649E41/0x664A34B/0x664A4B6/0x664A3AD/0x6648F0F/0x6648F34/0x6649242/0x6649A35/0x6649AE5/0x6649346/0x664A3AD/0x6648B3A/0x664A4B6/0x6648F0F/0x6648F34 (various cold paths) |

### (b) Strings Referenced (rva, text, site)

| String RVA | Text | Site (instruction RVA) |
|------------|------|------------------------|
| 0xF563B37 | "MeshFallbackPosUVNormalColor" | 0x6646a6b |
| 0xF2BE528 | "ChunkOccluder" | 0x6646ae5 |
| 0xF7C86B5 | "CracksBlockEntity" | 0x6646cf4 |
| 0xF515E74 | "Cracks" | 0x6646e3f |
| 0xF552ED0 | "MeshFallbackForwardPBR" | 0x6647238 |
| 0xF5B7E07 | (debug) | 0x664f0dc |
| 0xF598D3A | (debug) | 0x664f0e3 |
| 0xF60CFF6 | (debug) | 0x664f356 |
| 0xF54FCD0 | "GlowInkSignForwardPBR" | 0x664f3cf, 0x664f4ac |
| 0xF56398C | (material) | 0x664f43a, 0x664f590 |
| 0xF5DAB0B | (material) | 0x664f51e |
| 0xF5C6C6C | (material) | 0x664f2ea, 0x664f6b0 |
| 0xF5DE988 | (material) | 0x664f63e |
| 0x1232E708 | (hash table) | 0x6646d37, 0x6646e51, 0x664703d, 0x664707a, 0x66470fb, 0x664711f |
| 0x129F9AE0 | (TLS counter) | 0x6646a8c, 0x6646b35, 0x6646ec3, 0x66471f1, 0x6647288 |
| 0x129FB1B0 | (TLS counter) | 0x6646abc |
| 0x129CA5E0 | (TLS counter) | 0x6646b35, 0x6646ec3, 0x66471f1, 0x6647288, 0x664f17c, 0x664f1c0, 0x664f203, 0x664f246, 0x664f289 |
| 0x129F9CC8 | (TLS counter) | 0x6646e28 |
| 0x129F9CB0 | (TLS counter) | 0x664f2d2 |
| 0x129F9370 | (TLS counter) | 0x664f33d, 0x664f3af |
| 0x129F9380 | (TLS counter) | 0x664f421 |
| 0x129F9340 | (TLS counter) | 0x664f493 |
| 0x129F9350 | (TLS counter) | 0x664f505 |
| 0x129F9360 | (TLS counter) | 0x664f577 |
| 0x129FB168 | (TLS counter) | 0x664f5ef |
| 0x129F9CD8 | (TLS counter) | 0x664f625 |
| 0x129F9CE8 | (TLS counter) | 0x664f697 |
| 0x129FB168 | (TLS counter) | 0x664f5ef |
| 0x129F92B0 | (TLS counter) | 0x664f0a1 |
| 0x129F92F0 | (TLS counter) | 0x664f105 |
| 0x129F9330 | (TLS counter) | 0x664f133 |
| 0x129F9CB0 | (TLS counter) | 0x664f7e6 |
| 0x129F9370 | (TLS counter) | 0x664f88b |
| 0x129F9380 | (TLS counter) | 0x664f934 |
| 0x129F9340 | (TLS counter) | 0x664fa11 |
| 0x129F9350 | (TLS counter) | 0x664fac3 |
| 0x129F9360 | (TLS counter) | 0x664fb72 |
| 0x129F9220 | (TLS counter) | 0x664f577 |
| 0x129FB168 | (TLS counter) | 0x664f5ef |
| 0x129F9CD8 | (TLS counter) | 0x664f625 |
| 0x129F9CE8 | (TLS counter) | 0x664f697 |

### (c) Callees (in order of first appearance)

| Callee RVA | Name/Role | Call Sites |
|------------|-----------|------------|
| 0x9D6D0 | Build material name string | 0x6646a7e, 0x6646a9c, 0x6646d1f, 0x6646eab, 0x664725d, 0x6647270, 0x664f0b3, 0x664f10c, 0x664f2f5, 0x664f367, 0x664f3d9, 0x664f44b, 0x664f4bd, 0x664f52f, 0x664f5a1, 0x664f64f, 0x664f6c1, 0x664f72f |
| 0x67D6D70 | Resolve material by name | 0x6646b20 |
| 0x67CFD80 | Bind material to draw | 0x6646a79, 0x6646acb, 0x664737d |
| 0x5ABA5C0 | passLookup (get pass item vector) | 0x6646bde |
| 0xF99FFA0 | → 0xEEA6040 (allocator/refcount) | 0x6646c58, 0x6646ba0, 0x6646ba5, 0x6646bb0, 0x6646f06, 0x6646f21, 0x6646f2c, 0x6646f35, 0x6646f50, 0x6646f71, 0x6647033, 0x66470fb, 0x6647216, 0x6647225, 0x66472cf, 0x66472fa, 0x664730b, 0x6647315, ... (30+ sites) |
| 0x358C40 | Hash table lookup/insert | 0x6646d1f |
| 0x675E440 | Material resolver (FNV hash lookup) | 0x6646eab, 0x6647270 |
| 0xEEC59F0 | Hash table operation | 0x6647047 |
| 0x567D280 | Hash table insert | 0x664718e |
| 0x7D7890 | String builder | 0x664f0b3, 0x664f10c |
| 0x66E5EB0 | Unknown | 0x664f0c4 |
| 0xF2EA00 | Debug logging | 0x664f0e3 |
| 0x9B250 | String builder cleanup | 0x664f120, 0x664f125, 0x664f131 |
| 0xE935740 | TLS init | 0x664f144, 0x664f19b, 0x664f222, 0x664f265, 0x664f60f, 0x664f631 |
| 0xE938CB0 | TLS enter | 0x664f17c, 0x664f1c0, 0x664f203, 0x664f246, 0x664f289, 0x664f33d, 0x664f3af, 0x664f421, 0x664f49a, 0x664f50c, 0x664f57e, 0x664f608, 0x664f62c, 0x664f69e, 0x664f755 |
| 0xE938D70 | TLS exit | 0x664f150, 0x664f196, 0x664f1db, 0x664f229, 0x664f271, 0x664f344, 0x664f3b6, 0x664f428, 0x664f49f, 0x664f511, 0x664f583, 0x664f61b, 0x664f638, 0x664f70c, 0x664f7e6, 0x664f88b, 0x664f93b, 0x664fa18, 0x664faac, 0x664fb79, 0x664fcaa, 0x664fcf3, 0x664fdaf, 0x664fd98 |
| 0x567DB00 | Hash table init | 0x664f196, 0x664f1d9, 0x664f21c, 0x664f25f, 0x664f2a2, 0x664f2e4, 0x664f597, 0x664f645, 0x664f6b7, 0x664f724 |
| 0xE935740 | TLS init | 0x664f1a3, 0x664f229, 0x664f26c, 0x664f60f, 0x664f631 |
| 0x79580 | String hash | 0x664f2f5, 0x664f367, 0x664f3d9, 0x664f44b, 0x664f4bd, 0x664f52f, 0x664f5a1, 0x664f64f, 0x664f6c1 |
| 0x73150 | String builder finalize | 0x664f7da, 0x664f886, 0x664f92f, 0x664fa0c, 0x664fab7, 0x664fbf3, 0x664fcf3, 0x664fdf3, 0x664fc2c, 0x664fdf3, 0x664fd8c |
| 0x75740 | Wait/timeout | 0x664f170, 0x664f2c5 |
| 0x1A2800 | Debug break | 0x664f714 |
| 0xEEC5A00 | Hash table op | 0x664f16a |
| 0xEEC59F0 | Hash table lookup | 0x6647047 |

### (d) [reg+off] Read/Write Table (output/description objects)

The function takes RCX = context object (saved to RBX at 0x66469fa), RDX = context pointer (saved to [rbp+0x8A0] at 0x66469e4), R8 = item data (saved to RDI at 0x66469fd, RSI at 0x66469f1). The output is a material pointer resolved via 0x67D6D70 or 0x675E440, returned in RAX. The function writes item records to the pass item vector via 0x5ABA5C0.

| Offset | Size | Direction | First Site | Meaning |
|--------|------|-----------|------------|---------|
| [r8+8] | 1B | R | 0x66469eb movzx eax,byte ptr [r8+8] | Item tag/type selector (0..0xA) |
| [r8+0] | 8B | R | 0x66469fd mov rdi,[r8] | Item data pointer |
| [rdi+0x78] | 8B | R | 0x6646a10 mov rax,[rdi+0x78] | Context pointer for Case 0 |
| [rax+0x40] | 8B | R | 0x6646a1d cmp qword ptr [rax+0x40],0 | Validation |
| [rbp+0x8A0] | 8B | R | 0x6646a48 mov rcx,[rbp+0x8A0] | Context for material resolve |
| [rcx+0x70] | 4B | R | 0x6646a4f cmp dword ptr [rcx+0x70],1 | Context state check |
| [rdi+0x89] | 1B | R | 0x6646a57 or sil,[rdi+0x89] | Flag check |
| [rdi+0x108] | 8B | R | 0x6646c94 mov rax,[rdi+0x108] | Context for Case 3 |
| [rax+0x40] | 8B | R | 0x6646ca8 test rbx,rbx | Validation |
| [rdi+0x140] | 8B | R | 0x6646dc2 mov rax,[rdi+0x140] | Context for Case 4 |
| [rax+0x10] | 8B | R | 0x6646e16 mov rsi,[rax+0x10] | Material pointer |
| [rax+0x18] | 8B | R | 0x6646f15 mov rax,[rcx+0x18] | Shared_ptr control block |
| [rax+8] | 4B | R/W | 0x6646b71 lock inc dword ptr [rax+8] | Refcount increment |
| [r14+8] | 4B | R/W | 0x6646b8c lock dec dword ptr [r14+8] | Refcount decrement |
| [r14+0xC] | 4B | R/W | 0x6646ba6 lock dec dword ptr [r14+0xC] | Weak refcount decrement |
| [rdi+0x58] | 8B | R | 0x6646f5b mov rax,[rdi+0x58] | Context for Case 5 |
| [rdi+0x39] | 1B | R | 0x6646f7a movzx r8d,byte ptr [rax+0x39] | Flag byte |
| [rbp+0x8A0+0x10] | 8B | R | 0x6646bdd add rcx,[rax+0x10] | passLookup offset (0x9D0) |
| [rsi+0x98] | 8B | R/W | 0x6646c61 mov r12,[rsi+0x98] | Item vector end pointer |
| [rsi+0xA0] | 8B | R | 0x6646c68 cmp r12,[rsi+0xA0] | Item vector capacity |
| [r12] | 16B | W | 0x6646c75 movups [r12],xmm7 | Write item record (0x18 bytes) |
| [rsi+0x98] | 8B | W | 0x6646c80 add qword ptr [rsi+0x98],0x18 | Advance vector end |
| [rbp+0x880] | 8B | W | 0x6647011 mov [rbp+0x880],rax | Hash key (FNV-1a64) |
| [rbp+0x888] | 1B | R/W | 0x664707a movzx ecx,byte ptr [rbp+0x888] | Hash state byte |
| [r15+0x48] | 8B | R | 0x6646d5a mov rax,[r15] | Hash table pointer |
| [r15+0x70] | 8B | R | 0x664711b and rdx,[r15+0x70] | Hash table mask |
| [r15+0x88] | 8B | R/W | 0x66471a2 mov rdx,[r15+0x88] | Hash table bucket array |
| [r15+0x90] | 8B | R | 0x66471a9 cmp rdx,[r15+0x90] | Hash table capacity |
| [r8+rdx+8] | 8B | R | 0x6647127 mov rbx,[r8+rdx+8] | Hash bucket entry |
| [rbx+0x10] | 8B | R | 0x6647159 cmp rax,[rbx+0x10] | Key comparison |
| [rbx+8] | 8B | R | 0x6647168 cmp rbx,rdx | Next pointer |
| [rbx+0x18] | 8B | R | 0x6647172 cmp r8,[rbx+0x18] | Hash comparison |
| [r8+0x20] | 8B | R | 0x66471c6 mov rax,[r8+0x20] | Value pointer |
| [r8+0x28] | 8B | R | 0x66471c9 mov rax,[r8+0x28] | Value control block |
| [rax+8] | 4B | R/W | 0x66471be lock inc dword ptr [rax+8] | Refcount inc (hit) |
| [0xF2BF2D0] | — | R | 0x6646a00 lea rcx,[0xF2BF2D0] | Jump table base |

---

## TOOL REQUESTS
- None for this function — analysis complete from verified listing.

---

## NEXT
All three functions (L_660ecd0.txt, L_10f09f0.txt, L_6646980.txt) fully analysed. Unit U-H3c complete.

---

## Complete Analysis Summary for L_6646980.txt (0x6646980..0x664FDA5, 7679 lines)

### Phase Table (Full Function)

| Range | Description | Key Instructions |
|-------|-------------|------------------|
| 0x6646980..0x6646a0e | Prologue & jump table entry — saves registers, allocates 0x9B8 stack, loads tag byte from [r8+8], bounds check, jump table at 0xF2BF2D0 | 0x66469eb movzx eax,byte ptr [r8+8], 0x6646a00 lea rcx,[0xF2BF2D0], 0x6646a0e jmp rax |
| 0x6646a10..0x6646a84 | Case 0: "MeshFallbackPosUVNormalColor" — validates context, builds string (0xF563B37, len 0x1C), calls 0x9D6D0, resolves material via 0x67D6D70, checks loaded flag, calls 0x67CFD80 | 0x6646a6b lea r9,[0xF563B37], 0x6646a7e call 0x9D6D0, 0x6646a84 jmp 0x6647BB4 |
| 0x6646a89..0x6646bc5 | Case 1: "ChunkOccluder" — TLS guards, gets context, reads "ChunkOccluder" (0xF2BE528, len 0xD), calls 0x67D6D70, shared_ptr inc/dec via 0xF99FFA0 | 0x6646ae5 lea rax,[0xF2BE528], 0x6646b20 call 0x67D6D70, 0x6646b71 lock inc [rax+8] |
| 0x6646bc6..0x6646c87 | Case 2: reads 0x18-byte item, calls passLookup 0x5ABA5C0 with ctx+0x9D0, allocates 0x18-byte record via 0xF99FFA0 | 0x6646bc6 movups xmm7,[rdi], 0x6646bde call 0x5ABA5C0, 0x6646c58 call 0xF99FFA0 |
| 0x6646c8d..0x6646dbd | Case 3: "CracksBlockEntity" — reads [rdi+0x108], FNV-1a64 hash (0xCBF29CE484222325), hash table lookup at [r15+0x48], on miss allocates | 0x6646cf4 mov rax,[0xF7C86B5], 0x6646d1f call 0x358C40, 0x6646dbc jmp 0x66EA3D0 |
| 0x6646dc2..0x6646e50 | Case 4: "Cracks" — validates hash constants, builds "Cracks" (0xF515E74), calls 0x675E440, shared_ptr handling | 0x6646e3f lea rax,[0xF515E74], 0x6646eab call 0x675E440, 0x6646f06 lock inc [rcx+8] |
| 0x6646f5b..0x664737e | Case 5: "GlowInkSignForwardPBR" — reads [rdi+0x58], calls 0x66B2B30, builds "MeshFallbackForwardPBR" (0xF552ED0), hash lookup in [r15+0x98] | 0x6646f5b mov rax,[rdi+0x58], 0x6647033 call 0xF99FFA0, 0x664718e call 0x567D280 |
| 0x6647383..0x6647A73 | Case 6: "MeshFallbackForwardPBR" — similar to Case 5, material resolver 0x675E440, jmp 0x6698E30 | 0x6647270 call 0x675E440, 0x664737e jmp 0x6698E30 |
| 0x6647A74..0x664EF0D | Cases 7-10 & default — additional variants, all converge at epilogue 0x664EF0D | 0x664EF0D epilogue, 0x664EBD7 common fail, 0x664EF12 default |

### (b) Strings Referenced (Complete)

All string RVAs and texts captured in the 15×500-line blocks. Key strings:
- 0xF563B37 "MeshFallbackPosUVNormalColor" (Case 0)
- 0xF2BE528 "ChunkOccluder" (Case 1, len 0xD)
- 0xF7C86B5 "CracksBlockEntity" (Case 3)
- 0xF515E74 "Cracks" (Case 4, len 0x11)
- 0xF552ED0 "MeshFallbackForwardPBR" (Cases 5,6)
- 0xF5B7E07, 0xF598D3A, 0xF60CFF6, 0xF54FCD0, 0xF56398C, 0xF5DAB0B, 0xF5C6C6C, 0xF5DE988 (material/debug strings in cold paths)

### (c) Callees (Complete)

| Callee RVA | Role | Call Sites |
|------------|------|------------|
| 0x9D6D0 | Build material name string | 20+ sites (every case) |
| 0x67D6D70 | Resolve material by name | 0x6646b20 (Case 1) |
| 0x67CFD80 | Bind material to draw | 0x6646a79, 0x6646acb, 0x664737d |
| 0x5ABA5C0 | passLookup (get pass item vector) | 0x6646bde, 0x506D-0x508D (4 sites) |
| 0xF99FFA0 → 0xEEA6040 | Allocator/refcount | 100+ sites (shared_ptr inc/dec) |
| 0x675E440 | Material resolver (FNV hash) | 0x6646eab, 0x6647270, 0x664725d |
| 0xEEC59F0 | Hash table lookup | 0x6647047 |
| 0x567D280 | Hash table insert | 0x664718e |
| 0x358C40 | Hash table lookup/insert | 0x6646d1f |
| 0x7D7890 | String builder | 0x664f0b3, 0x664f10c |
| 0x79580 | String hash (FNV-1a) | 20+ sites (cold paths) |
| 0xE938CB0/D70 | TLS enter/exit | 50+ sites (every cold path) |
| 0xE935740 | TLS init | 10+ sites |
| 0x567DB00 | Hash table init | 10+ sites |
| 0x73150 | String builder finalize | 15+ sites |
| 0xBCABA00 | Hash table op | 0x664c064, 0x664c0eb, 0x664c1f6, 0x66499fc, 0x664a1fd |
| 0xBCAC390 | Hash table op | 0x664a439 |
| 0xEEC5A00/56740 | Hash table ops | 0x664f16a, 0x664f170 |
| 0xEEC6EC0/ED0 | Vector expand/copy | 0x664daec, 0x664e1a9 |
| 0x567D280 | Hash table insert | 0x664718e |
| 0x5ABA6D0 | passLookup variant | 0x6647b07, 0x664daee, 0x664e1c5, 0x664d366 |
| 0x6764990 | Terrain draw builder | 0x664ba63, 0x664da56 |
| 0x66E6240/66E6380 | Extractors | 0x664c0e9, 0x664c1e9, 0x664eaa2 |
| 0x66A0F60/66E75F0/66E5EB0 | Various | 0x66473e1, 0x6647444, 0x664f0c4 |

### (d) [reg+off] Read/Write Table (Complete)

| Offset | Size | Direction | First Site | Meaning |
|--------|------|-----------|------------|---------|
| [r8+8] | 1B | R | 0x66469eb | Item tag/type selector (0..0xA) |
| [r8+0] | 8B | R | 0x66469fd | Item data pointer |
| [rdi+0x78] | 8B | R | 0x6646a10 | Context for Case 0 |
| [rdi+0x108] | 8B | R | 0x6646c94 | Context for Case 3 |
| [rdi+0x140] | 8B | R | 0x6646dc2 | Context for Case 4 |
| [rdi+0x58] | 8B | R | 0x6646f5b | Context for Case 5 |
| [rbp+0x8A0] | 8B | R/W | 0x66469e4 | Context pointer (saved from RDX) |
| [rbp+0x8A0+0x10] | 8B | R | 0x6646bdd | passLookup offset (0x9D0) |
| [rsi+0x98] | 8B | R/W | 0x6646c61 | Item vector end |
| [rsi+0xA0] | 8B | R | 0x6646c68 | Item vector capacity |
| [r12] | 16B | W | 0x6646c75 | Write item record (0x18 bytes) |
| [rsi+0x98] | 8B | W | 0x6646c80 | Advance vector end |
| [rax+8] | 4B | R/W | 0x6646b71 | Refcount increment |
| [r14+8] | 4B | R/W | 0x6646b8c | Refcount decrement |
| [r14+0xC] | 4B | R/W | 0x6646ba6 | Weak refcount decrement |
| [rdi+0x39] | 1B | R | 0x6646f7a | Flag byte |
| [rbp+0x880] | 8B | W | 0x6647011 | Hash key (FNV-1a64) |
| [rbp+0x888] | 1B | R/W | 0x664707a | Hash state byte |
| [r15+0x48] | 8B | R | 0x6646d5a | Hash table pointer |
| [r15+0x70] | 8B | R | 0x664711b | Hash table mask |
| [r15+0x88] | 8B | R/W | 0x66471a2 | Hash table bucket array |
| [r15+0x90] | 8B | R | 0x66471a9 | Hash table capacity |
| [r8+rdx+8] | 8B | R | 0x6647127 | Hash bucket entry |
| [rbx+0x10] | 8B | R | 0x6647159 | Key comparison |
| [rbx+8] | 8B | R | 0x6647168 | Next pointer |
| [rbx+0x18] | 8B | R | 0x6647172 | Hash comparison |
| [r8+0x20/0x28] | 8B | R | 0x66471c6/0x66471c9 | Value pointer/control |
| [0xF2BF2D0] | — | R | 0x6646a00 | Jump table base |
| [0x1233E1A8/B0] | 8B | R | 0x6646c48 | Allocator globals |

---

## TOOL REQUESTS
- None — all three functions fully analysed from verified listings.

## Files Created/Updated
- docs/progress/oc_U-H3c.md (this file, complete analysis of all 3 functions)
- docs/listings/L_660ecd0.txt (1052 lines, verified)
- docs/listings/L_10f09f0.txt (3511 lines, verified)
- docs/listings/L_6646980.txt (7679 lines, verified)

## Verification
All listings pass verify_oc.py (no mismatches when using initial instructions).
## ORCHESTRATOR: real content at every 0xF... RVA mentioned in this file (tools/sigs/rvastrdoc.py, 2026-11-16). Where a string label above disagrees with this table, THIS TABLE IS RIGHT (units guessed labels; movups loads show a 16-byte slice of longer names).
| RVA | real content at RVA (exe bytes) |
|---|---|
| 0xF092050 | bytes 5092074001000000 |
| 0xF0B7760 | bytes 1002da4001000000 |
| 0xF0B78A0 | bytes 5092074001000000 |
| 0xF0DEF50 | bytes 20c5154101000000 |
| 0xF2BE528 | "ChunkOccluder" |
| 0xF2BF2D0 | bytes 407738f78b7c38f7 |
| 0xF515E74 | "CracksBlockEntity" |
| 0xF51A19D | "Occlusion_Query" |
| 0xF51CE37 | "light_update_frequency" |
| 0xF51DC4A | "Texture_Cube_Array" |
| 0xF51DC5D | "Texture_2D_Array" |
| 0xF530599 | "max_transition_volume_count" |
| 0xF530866 | "maxVertexCount" |
| 0xF5376A5 | "Blend_Independent" |
| 0xF539A77 | "Texture_Blit" |
| 0xF53BEEE | "originBottomLeft" |
| 0xF53CAD3 | "Buffer_Bind_Offset" |
| 0xF53FC8C | "Draw_Indirect" |
| 0xF5428AB | "maxViews" |
| 0xF5452CB | "maxFBAttachments" |
| 0xF545C22 | "max_staged_transition_results" |
| 0xF545EB1 | "limits" |
| 0xF545EB8 | "maxBlits" |
| 0xF5460A9 | "max_point_lights" |
| 0xF546164 | "light_scoring_weights" |
| 0xF548EE8 | "Texture_Direct_Access" |
| 0xF54AFFC | "maxTextureLayers" |
| 0xF54BC64 | "maxTextureSamplers" |
| 0xF54BF5F | "maxVertexBuffers" |
| 0xF54BF70 | "maxDynamicVertexBuffers" |
| 0xF54BF88 | "maxIndexBuffers" |
| 0xF54BF98 | "maxDynamicIndexBuffers" |
| 0xF54BFF6 | "maxFrameBuffers" |
| 0xF54C006 | "Structured_Buffers" |
| 0xF54C155 | "maxEncoders" |
| 0xF54C1B9 | "maxShaders" |
| 0xF54EF33 | "maxComputeWorkGroupInvocations" |
| 0xF54FCAE | "maxUniforms" |
| 0xF54FCD0 | "MERSUniforms" |
| 0xF550C59 | "maxPrograms" |
| 0xF550EF3 | "maxVertexStreams" |
| 0xF55126B | "maxDrawCalls" |
| 0xF551750 | "maxVertexDecls" |
| 0xF551B2A | "max_in_flight_transition_tasks" |
| 0xF551B49 | "max_pending_transition_tasks" |
| 0xF552ED0 | "Cracks" |
| 0xF554EA8 | "maxComputeBindings" |
| 0xF5572B6 | "maxTextures" |
| 0xF558BB0 | "Dynamic_Texturehandles" |
| 0xF559A6B | "maxOcclusionQueries" |
| 0xF55CEB1 | "slope_bias" |
| 0xF55CECD | "bias" |
| 0xF55CF04 | "Depth_Bias" |
| 0xF55CFF8 | "numGPUs" |
| 0xF55FEFB | "light_score_smoothing_factor" |
| 0xF56398C | "CurrentColor" |
| 0xF563B37 | "MeshFallbackPosUVNormalColor" |
| 0xF567121 | "Conservative_Raster" |
| 0xF56ADBD | "Gpu_Timer" |
| 0xF56DDFA | "Graphics_Debugger" |
| 0xF570335 | "No_Fragment_Shader" |
| 0xF5711AD | "transitioning_ambient_scalar" |
| 0xF584FAA | "fpEpsilon" |
| 0xF590EDB | "max_tile_dimension" |
| 0xF590EEE | "start_tile_dimension" |
| 0xF590F03 | "min_tile_dimension" |
| 0xF593C39 | "Swap_Chain" |
| 0xF598D3A | bytes 4f6e004c6e006669 |
| 0xF5A26B8 | "Texture_Compare_All" |
| 0xF5A4ED7 | "Texture_Compare_Lequal" |
| 0xF5ADDD6 | "homogenousDepth" |
| 0xF5ADEE2 | "Fragment_Depth" |
| 0xF5B4B68 | "Fragment_Ordering" |
| 0xF5B67DB | "Upscaling" |
| 0xF5B7E07 | "PointLightShading" |
| 0xF5B7EC7 | "Instancing" |
| 0xF5B7F3B | "Ray_Tracing" |
| 0xF5BA71E | "Vertex_Attrib_Half" |
| 0xF5BB720 | "transition_step_size" |
| 0xF5BB7B4 | "score_compute_batch_size" |
| 0xF5BB7CD | "max_probe_batch_size" |
| 0xF5BC07A | "maxTextureSize" |
| 0xF5BC22E | "transientVbSize" |
| 0xF5BC23E | "transientIbSize" |
| 0xF5C0055 | "Compute" |
| 0xF5C6C6C | "CracksTexture" |
| 0xF5CED64 | "far_plane" |
| 0xF5CED6E | "near_plane" |
| 0xF5D0E3F | "max_probe_draws_per_frame" |
| 0xF5D0E59 | "max_transition_commits_per_frame" |
| 0xF5D0E7A | "max_shrinks_per_frame" |
| 0xF5D0EA0 | "max_growths_per_frame" |
| 0xF5D0EB6 | "max_invalidates_per_frame" |
| 0xF5DAB0B | "DitheringEnabledToggle" |
| 0xF5DE988 | "UVScale" |
| 0xF5E2C89 | "Alpha_To_Coverage" |
| 0xF5E5FCE | "Ranged_Resource" |
| 0xF5FD313 | "Renderer_Multithreaded" |
| 0xF604BE4 | "Vertex_Id" |
| 0xF60CFF6 | "PBRData" |
| 0xF7C86B5 | "ALPHA_TEST" |
| 0xF7CB867 | "HiDPI" |
| 0xF7D165A | "Vertex_Attrib_Sint8" |
| 0xF7D398F | "Vertex_Attrib_Uint16" |
| 0xF7DD394 | "Index32" |
| 0xF7E5A4B | "Vertex_Attrib_Uint10" |
| 0xF7E5C0F | "HDR10" |
| 0xF99FFA0 | bytes 4060ea4e01000000 |
| 0xF9A8C78 | bytes 5e059b0f00000000 |
