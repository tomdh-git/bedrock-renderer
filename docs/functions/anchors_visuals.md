# Visual anchors: shadows, particles, weather, clouds (1.26.62.01, static [V])

Each row: function, `xref.py sig` signature (wildcarded prologue, tool checks uniqueness over .text), size, and every distinct string the function references (xref.py strs). Roles: docs/functions/group_visitors.md (Effect tag 2, Sky tags 1/9) and 6x.

## 0x53fcac0 Cascaded shadow set build (I1a/L11a)
- signature: `53fcac0 55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC 28 03 00 00 48 8D AC 24 ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? FE FF FF FF 48 89 8D ?? ??`
- strings: near; has_static_geometry; has_dynamic_geometry; bias; slope_bias; resolution; light_quantization_steps; range; update_frequency; update_offset; pcf_width; Shadow Parameters; normal_offset_strength; shadow_range; shadow_chunk_radius; max_shadow_frustum_radius; max_shadow_distance; cloud_shadow_pcf_width; cloud_shadow_contribution; cloud_shadow_quantization_steps; sun_shadows; moon_shadows; cloud_shadows; directional_light_dynamic_shadow; cascades; medium; high; ultra

## 0x543c950 Cascade-count validation (I1a/L11a)
- signature: `543c950 55 41 57 41 56 41 54 56 57 53 48 81 EC D0 00 00 00 48 8D AC 24 ?? ?? ?? ?? 48 C7 45 48 FE FF FF FF 41 0F B6 80 ??`
- strings: Total number of cascades in all cascade sets ({}) must be under MaxTotalCascades ({}).; max_shadow_distance must be less than or equal to the view area distance defined by shadow_chunk_rad

## 0x67417f0 Particle extractor, Effect tag 2 (I3/L13a)
- signature: `67417f0 55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC 58 07 00 00 48 8D AC 24 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? FE FF FF FF 4C 89 C7 48 89 D6`
- strings: ParticleForwardPBR; ParticlePrepass; Particle; PointLightShading; ParticleTexture; FogAndDistanceControl; MERSUniforms; PBRTextureFlags; MERSTexture; NormalTexture

## 0x6745440 Weather renderer, Sky tag 9 (I4a/L13b)
- signature: `6745440 55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC B8 06 00 00 48 8D AC 24 ?? ?? ?? ?? 0F 29 BD ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? FE FF FF FF 48 89 8D ??`
- strings: WeatherForwardPBR; Weather; NoVariety; PointLightShading; FogAndDistanceControl; WeatherTexture; OcclusionTexture; HeightTexture; LightingTexture; PrevPositionBaseOffset; PrevPositionForwardOffset; PositionBaseOffset; PositionForwardOffset; ViewPosition; UVOffsetAndScale; Velocity; Dimensions; OcclusionHeightOffset

## 0x67375a0 Clouds renderer, Sky tag 1 (I4b/L13c, partial)
- signature: `67375a0 55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC 28 06 00 00 48 8D AC 24 ?? ?? ?? ?? 0F 29 B5 ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? FE FF FF FF 4C 89 C3 48 89`
- strings: Clouds; CloudsForwardPBR; CloudColor; DistanceControl; PrevWorld
