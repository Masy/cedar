//
// Created by masy on 23.02.20.
//
// Re-mappings of some OpenGL constants for Cedar so you don't need to include glad.h if you need some constants.
//

#ifndef TALESOFCATVENTURE_GLCONSTANTS_H
#define TALESOFCATVENTURE_GLCONSTANTS_H

#define CEDAR_ZERO 0x0000
#define CEDAR_NONE CEDAR_ZERO

#define CEDAR_ONE 0x0001

/*
 * Base Internal formats
 */
#define CEDAR_RED 0x1903
#define CEDAR_RG 0x8227
#define CEDAR_RGB 0x1907
#define CEDAR_RGBA 0x1908
#define CEDAR_DEPTH_COMPONENT 0x1902
#define CEDAR_STENCIL_INDEX 0x1901
#define CEDAR_DEPTH_STENCIL 0x84F9

/*
 * Generic sized internal formats
 */
// 8 Bit
#define CEDAR_R8 0x8229
#define CEDAR_RG8 0x822B
#define CEDAR_RGB8 0x8051
#define CEDAR_RGBA8 0x8058

#define CEDAR_R8_SNORM 0x8F94
#define CEDAR_RG8_SNORM 0x8F95
#define CEDAR_RGB8_SNORM 0x8F96
#define CEDAR_RGBA8_SNORM 0x8F97

// 16 Bit
#define CEDAR_R16 0x822A
#define CEDAR_RG16 0x822C
#define CEDAR_RGB16 0x8054
#define CEDAR_RGBA16 0x805B

#define CEDAR_R16_SNORM 0x8F98
#define CEDAR_RG16_SNORM 0x8F99
#define CEDAR_RGB16_SNORM 0x8F9A
#define CEDAR_RGBA16_SNORM 0x8F9B

// Depth
#define CEDAR_DEPTH_COMPONENT16 0x81A5
#define CEDAR_DEPTH_COMPONENT24 0x81A6
#define CEDAR_DEPTH_COMPONENT32 0x81A7

// Stencil
#define CEDAR_STENCIL_INDEX1 0x8D46
#define CEDAR_STENCIL_INDEX4 0x8D47
#define CEDAR_STENCIL_INDEX8 0x8D48
#define CEDAR_STENCIL_INDEX16 0x8D49

// Depth & Stencil
#define CEDAR_DEPTH24_STENCIL8 0x88F0

/*
 * Specific sized internal formats
 */

// 8 Bit Unsigned Integer
#define CEDAR_R8UI 0x8283
#define CEDAR_RG8UI 0x8288
#define CEDAR_RGB8UI 0x8D7D
#define CEDAR_RGBA8UI 0x8D7C

// 8 Bit Signed Integer
#define CEDAR_R8I 0x8231
#define CEDAR_RG8I 0x8237
#define CEDAR_RGB8I 0x8D8F
#define CEDAR_RGBA8I 0x8D8E

// 16 Bit Unsigned Integer
#define CEDAR_R16UI 0x8234
#define CEDAR_RG16UI 0x823A
#define CEDAR_RGB16UI 0x8D77
#define CEDAR_RGBA16UI 0x8D76

// 16 Bit Signed Integer
#define CEDAR_R16I 0x8233
#define CEDAR_RG16I 0x8239
#define CEDAR_RGB16I 0x8D89
#define CEDAR_RGBA16I 0x8D88

// 16 Bit Float
#define CEDAR_R16F 0x822D
#define CEDAR_RG16F 0x822F
#define CEDAR_RGB16F 0x881B
#define CEDAR_RGBA16F 0x881A

// 32 Bit Unsigned Integer
#define CEDAR_R32UI 0x8236
#define CEDAR_RG32UI 0x823C
#define CEDAR_RGB32UI 0x8D71
#define CEDAR_RGBA32UI 0x8D70

// 32 Bit Signed Integer
#define CEDAR_R32I 0x8235
#define CEDAR_RG32I 0x823B
#define CEDAR_RGB32I 0x8D83
#define CEDAR_RGBA32I 0x8D82

// 32 Bit Float
#define CEDAR_R32F 0x822E
#define CEDAR_RG32F 0x8230
#define CEDAR_RGB32F 0x8815
#define CEDAR_RGBA32F 0x8814

// Depth
#define CEDAR_DEPTH_COMPONENT32F 0x8CAC

// Depth & Stencil
#define CEDAR_DEPTH32F_STENCIL8 0x8CAD

/*
 * Data Types
 */
#define CEDAR_UNSIGNED_BYTE 0x1401
#define CEDAR_BYTE 0x1400
#define CEDAR_UNSIGNED_SHORT 0x1403
#define CEDAR_SHORT 0x1402
#define CEDAR_UNSIGNED_INT 0x1405
#define CEDAR_INT 0x1404
#define CEDAR_FLOAT 0x1406

/*
 * Texture Targets
 */
// Normal textures
#define CEDAR_TEXTURE_1D 0x0DE0
#define CEDAR_TEXTURE_1D_ARRAY 0x8C18
#define CEDAR_TEXTURE_2D 0x0DE1
#define CEDAR_TEXTURE_2D_MULTISAMPLE 0x9100
#define CEDAR_TEXTURE_RECTANGLE 0x84F5
#define CEDAR_TEXTURE_2D_ARRAY 0x8C1A
#define CEDAR_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#define CEDAR_TEXTURE_3D 0x806F
#define CEDAR_TEXTURE_CUBE_MAP 0x8513
#define CEDAR_TEXTURE_CUBE_MAP_ARRAY 0x9009
#define CEDAR_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define CEDAR_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define CEDAR_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define CEDAR_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define CEDAR_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define CEDAR_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A

// Proxy textures
#define CEDAR_PROXY_TEXTURE_1D 0x8063
#define CEDAR_PROXY_TEXTURE_1D_ARRAY 0x8C19
#define CEDAR_PROXY_TEXTURE_2D 0x8064
#define CEDAR_PROXY_TEXTURE_2D_MULTISAMPLE 0x9101
#define CEDAR_PROXY_TEXTURE_RECTANGLE 0x84F7
#define CEDAR_PROXY_TEXTURE_2D_ARRAY 0x8C1B
#define CEDAR_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define CEDAR_PROXY_TEXTURE_3D 0x8070
#define CEDAR_PROXY_TEXTURE_CUBE_MAP 0x851B
#define CEDAR_PROXY_TEXTURE_CUBE_MAP_ARRAY 0x900B

/*
 * Texture Parameters
 */
#define CEDAR_DEPTH_STENCIL_TEXTURE_MODE 0x90EA;
#define CEDAR_TEXTURE_BASE_LEVEL 0x813C
#define CEDAR_TEXTURE_BORDER_COLOR 0x1004
#define CEDAR_TEXTURE_COMPARE_MODE 0x884C
#define CEDAR_TEXTURE_COMPARE_FUNC 0x884D
#define CEDAR_TEXTURE_LOD_BIAS 0x8501
#define CEDAR_TEXTURE_MIN_LOD 0x813A
#define CEDAR_TEXTURE_MAX_LOD 0x813B
#define CEDAR_TEXTURE_MAG_FILTER 0x2800
#define CEDAR_TEXTURE_MIN_FILTER 0x2801
#define CEDAR_TEXTURE_MAX_LEVEL 0x813D
#define CEDAR_TEXTURE_SWIZZLE_R 0x8E42
#define CEDAR_TEXTURE_SWIZZLE_G 0x8E43
#define CEDAR_TEXTURE_SWIZZLE_B 0x8E44
#define CEDAR_TEXTURE_SWIZZLE_A 0x8E45
#define CEDAR_TEXTURE_SWIZZLE_RGBA 0x8E46
#define CEDAR_TEXTURE_WRAP_S 0x2802
#define CEDAR_TEXTURE_WRAP_T 0x2803
#define CEDAR_TEXTURE_WRAP_R 0x8072

/*
 * Comparative Functions
 */
#define CEDAR_ALWAYS 0x0200
#define CEDAR_NEVER 0x0207
#define CEDAR_EQUAL 0x0202
#define CEDAR_LEQUAL 0x0203
#define CEDAR_GEQUAL 0x0206
#define CEDAR_NOTEQUAL 0x0205
#define CEDAR_LESS 0x0201
#define CEDAR_GREATER 0x0204

/*
 * Comparative Modes
 */
#define CEDAR_COMPARE_REF_TO_TEXTURE 0x884E

/*
 * Texture Filter
 */
#define CEDAR_NEAREST 0x2600
#define CEDAR_LINEAR 0x2601
#define CEDAR_NEAREST_MIPMAP_NEAREST 0x2700
#define CEDAR_LINEAR_MIPMAP_NEAREST 0x2701
#define CEDAR_NEAREST_MIPMAP_LINEAR 0x2702
#define CEDAR_LINEAR_MIPMAP_LINEAR 0x2703

/*
 * Texture Wrap Modes
 */
#define CEDAR_REPEAT 0x2901
#define CEDAR_MIRRORED_REPEAT 0x8370
#define CEDAR_CLAMP_TO_BORDER 0x812D
#define CEDAR_CLAMP_TO_EDGE 0x812F
#define CEDAR_MIRROR_CLAMP_TO_EDGE 0x8743

/*
 * Shader types
 */
#define CEDAR_VERTEX_SHADER 0x8B31
#define CEDAR_GEOMETRY_SHADER 0x8DD9
#define CEDAR_FRAGMENT_SHADER 0x8B30
#define CEDAR_COMPUTE_SHADER 0x91B9

#endif //TALESOFCATVENTURE_GLCONSTANTS_H
