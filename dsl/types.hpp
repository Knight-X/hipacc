//
// Copyright (c) 2013, University of Erlangen-Nuremberg
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#ifndef __TYPES_HPP__
#define __TYPES_HPP__

namespace hipacc {

#if defined __clang__
typedef char                char4   __attribute__ ((ext_vector_type(4)));
typedef short int           short4  __attribute__ ((ext_vector_type(4)));
typedef int                 int4    __attribute__ ((ext_vector_type(4)));
typedef long int            long4   __attribute__ ((ext_vector_type(4)));
typedef unsigned char       uchar4  __attribute__ ((ext_vector_type(4)));
typedef unsigned short int  ushort4 __attribute__ ((ext_vector_type(4)));
typedef unsigned int        uint4   __attribute__ ((ext_vector_type(4)));
typedef unsigned long int   ulong4  __attribute__ ((ext_vector_type(4)));
typedef float               float4  __attribute__ ((ext_vector_type(4)));
typedef double              double4 __attribute__ ((ext_vector_type(4)));
typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
#define ATTRIBUTES inline
#define MAKE_VEC_F(NEW_TYPE, BASIC_TYPE, RET_TYPE) \
    MAKE_COPS(NEW_TYPE, BASIC_TYPE)
#define MAKE_VEC_I(NEW_TYPE, BASIC_TYPE, RET_TYPE) \
    MAKE_VEC_F(NEW_TYPE, BASIC_TYPE, RET_TYPE)
#elif defined __GNUC__
typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
#define ATTRIBUTES inline
#define MAKE_VEC_F(NEW_TYPE, BASIC_TYPE, RET_TYPE) \
    MAKE_TYPE(NEW_TYPE, BASIC_TYPE) \
    MAKE_COPS(NEW_TYPE, BASIC_TYPE) \
    MAKE_VOPS_A(NEW_TYPE, BASIC_TYPE, RET_TYPE)
#define MAKE_VEC_I(NEW_TYPE, BASIC_TYPE, RET_TYPE) \
    MAKE_VEC_F(NEW_TYPE, BASIC_TYPE, RET_TYPE) \
    MAKE_VOPS_I(NEW_TYPE, BASIC_TYPE, RET_TYPE)
#else
#error "Only Clang, and gcc compilers supported!"
#endif


// vector type definition
#define MAKE_TYPE(NEW_TYPE, BASIC_TYPE) \
_Pragma("pack(1)") \
struct NEW_TYPE { \
    BASIC_TYPE x, y, z, w; \
    void operator=(BASIC_TYPE b) { \
        x = b; y = b; z = b; w = b; \
    } \
}; \
typedef struct NEW_TYPE NEW_TYPE;


// custom operators
#define MAKE_COPS(NEW_TYPE, BASIC_TYPE) \
static ATTRIBUTES NEW_TYPE make_##NEW_TYPE(BASIC_TYPE x, BASIC_TYPE y, BASIC_TYPE z, BASIC_TYPE w) { \
    NEW_TYPE t; t.x = x; t.y = y; t.z = z; t.w = w; return t; \
} \
static ATTRIBUTES NEW_TYPE make_##NEW_TYPE(BASIC_TYPE s) \
{ \
    return make_##NEW_TYPE(s, s, s, s); \
} \
 \
 /* min */ \
 \
ATTRIBUTES BASIC_TYPE min(BASIC_TYPE a, BASIC_TYPE b) { \
    return (a < b ? a : b); \
} \
 \
ATTRIBUTES NEW_TYPE min(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); \
} \
 \
ATTRIBUTES NEW_TYPE min(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(min(a.x, b), min(a.y, b), min(a.z, b), min(a.w, b)); \
} \
 \
ATTRIBUTES NEW_TYPE min(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(min(a, b.x), min(a, b.y), min(a, b.z), min(a, b.w)); \
} \
 \
 /* max */ \
 \
ATTRIBUTES BASIC_TYPE max(BASIC_TYPE a, BASIC_TYPE b) { \
    return (a > b ? a : b); \
} \
 \
ATTRIBUTES NEW_TYPE max(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); \
} \
 \
ATTRIBUTES NEW_TYPE max(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(max(a.x, b), max(a.y, b), max(a.z, b), max(a.w, b)); \
} \
 \
ATTRIBUTES NEW_TYPE max(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(max(a, b.x), max(a, b.y), max(a, b.z), max(a, b.w)); \
}


// vector operators for all data types
#define MAKE_VOPS_A(NEW_TYPE, BASIC_TYPE, RET_TYPE) \
 \
 /* binary operator: add */ \
 \
ATTRIBUTES NEW_TYPE operator+(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); \
} \
ATTRIBUTES NEW_TYPE operator+(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x + b, a.y + b, a.z + b, a.w + b); \
} \
ATTRIBUTES NEW_TYPE operator+(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a + b.x, a + b.y, a + b.z, a + b.w); \
} \
ATTRIBUTES void operator+=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; \
} \
ATTRIBUTES void operator+=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x += b, a.y += b, a.z += b, a.w += b; \
} \
 \
 /* binary operator: subtract */ \
 \
ATTRIBUTES NEW_TYPE operator-(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); \
} \
ATTRIBUTES NEW_TYPE operator-(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x - b, a.y - b, a.z - b, a.w - b); \
} \
ATTRIBUTES NEW_TYPE operator-(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a - b.x, a - b.y, a - b.z, a - b.w); \
} \
ATTRIBUTES void operator-=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; \
} \
ATTRIBUTES void operator-=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x -= b, a.y -= b, a.z -= b, a.w -= b; \
} \
 \
 /* binary operator: multiply */ \
 \
ATTRIBUTES NEW_TYPE operator*(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); \
} \
ATTRIBUTES NEW_TYPE operator*(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x * b, a.y * b, a.z * b, a.w * b); \
} \
ATTRIBUTES NEW_TYPE operator*(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a * b.x, a * b.y, a * b.z, a * b.w); \
} \
ATTRIBUTES void operator*=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; \
} \
ATTRIBUTES void operator*=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x *= b, a.y *= b, a.z *= b, a.w *= b; \
} \
 \
 /* binary operator: divide */ \
 \
ATTRIBUTES NEW_TYPE operator/(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); \
} \
ATTRIBUTES NEW_TYPE operator/(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x / b, a.y / b, a.z / b, a.w / b); \
} \
ATTRIBUTES NEW_TYPE operator/(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a / b.x, a / b.y, a / b.z, a / b.w); \
} \
ATTRIBUTES void operator/=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x /= b.x; a.y /= b.y; a.z /= b.z; a.w /= b.w; \
} \
ATTRIBUTES void operator/=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x /= b, a.y /= b, a.z /= b, a.w /= b; \
} \
 \
 /* unary operator: plus */ \
 \
ATTRIBUTES NEW_TYPE operator+(NEW_TYPE a) { \
    return make_##NEW_TYPE(+a.x, +a.y, +a.z, +a.w); \
} \
 \
 /* unary operator: minus */ \
 \
ATTRIBUTES NEW_TYPE operator-(NEW_TYPE a) { \
    return make_##NEW_TYPE(-a.x, -a.y, -a.z, -a.w); \
} \
 \
 /* relational operator: greater-than */ \
 \
ATTRIBUTES RET_TYPE operator>(NEW_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w); \
} \
ATTRIBUTES RET_TYPE operator>(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##RET_TYPE(a.x > b, a.y > b, a.z > b, a.w > b); \
} \
ATTRIBUTES RET_TYPE operator>(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a > b.x, a > b.y, a > b.z, a > b.w); \
} \
 \
 /* relational operator: less-than */ \
 \
ATTRIBUTES RET_TYPE operator<(NEW_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w); \
} \
ATTRIBUTES RET_TYPE operator<(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##RET_TYPE(a.x < b, a.y < b, a.z < b, a.w < b); \
} \
ATTRIBUTES RET_TYPE operator<(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a < b.x, a < b.y, a < b.z, a < b.w); \
} \
 \
 /* relational operator: greater-than or equal-to */ \
 \
ATTRIBUTES RET_TYPE operator>=(NEW_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w); \
} \
ATTRIBUTES RET_TYPE operator>=(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##RET_TYPE(a.x >= b, a.y >= b, a.z >= b, a.w >= b); \
} \
ATTRIBUTES RET_TYPE operator>=(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a >= b.x, a >= b.y, a >= b.z, a >= b.w); \
} \
 \
 /* relational operator: less-than or equal-to */ \
 \
ATTRIBUTES RET_TYPE operator<=(NEW_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w); \
} \
ATTRIBUTES RET_TYPE operator<=(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##RET_TYPE(a.x <= b, a.y <= b, a.z <= b, a.w <= b); \
} \
ATTRIBUTES RET_TYPE operator<=(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a <= b.x, a <= b.y, a <= b.z, a <= b.w); \
} \
 \
 /* equality operator: equal */ \
 \
ATTRIBUTES RET_TYPE operator==(NEW_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w); \
} \
ATTRIBUTES RET_TYPE operator==(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##RET_TYPE(a.x == b, a.y == b, a.z == b, a.w == b); \
} \
ATTRIBUTES RET_TYPE operator==(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a == b.x, a == b.y, a == b.z, a == b.w); \
} \
 \
 /* equality operator: not equal */ \
 \
ATTRIBUTES RET_TYPE operator!=(NEW_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w); \
} \
ATTRIBUTES RET_TYPE operator!=(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##RET_TYPE(a.x != b, a.y != b, a.z != b, a.w != b); \
} \
ATTRIBUTES RET_TYPE operator!=(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a != b.x, a != b.y, a != b.z, a != b.w); \
} \
 \
 /* logical operator: and */ \
 \
ATTRIBUTES RET_TYPE operator&&(NEW_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a.x && b.x, a.y && b.y, a.z && b.z, a.w && b.w); \
} \
ATTRIBUTES RET_TYPE operator&&(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##RET_TYPE(a.x && b, a.y && b, a.z && b, a.w && b); \
} \
ATTRIBUTES RET_TYPE operator&&(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a && b.x, a && b.y, a && b.z, a && b.w); \
} \
 \
 /* logical operator: or */ \
 \
ATTRIBUTES RET_TYPE operator||(NEW_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a.x || b.x, a.y || b.y, a.z || b.z, a.w || b.w); \
} \
ATTRIBUTES RET_TYPE operator||(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##RET_TYPE(a.x || b, a.y || b, a.z || b, a.w || b); \
} \
ATTRIBUTES RET_TYPE operator||(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##RET_TYPE(a || b.x, a || b.y, a || b.z, a || b.w); \
} \
 \
 /* logical unary operator: not */ \
 \
ATTRIBUTES RET_TYPE operator!(NEW_TYPE a) { \
    return make_##RET_TYPE(!a.x, !a.y, !a.z, !a.w); \
} \
 \
 /* operator: comma */ \
 \
ATTRIBUTES NEW_TYPE operator,(NEW_TYPE a, NEW_TYPE b) { \
    return b; \
} \
ATTRIBUTES BASIC_TYPE operator,(NEW_TYPE a, BASIC_TYPE b) { \
    return b; \
} \
ATTRIBUTES NEW_TYPE operator,(BASIC_TYPE a, NEW_TYPE b) { \
    return b; \
}


// vector operators for integer data types only
#define MAKE_VOPS_I(NEW_TYPE, BASIC_TYPE, RET_TYPE) \
 \
 /* binary operator: remainder */ \
 \
ATTRIBUTES NEW_TYPE operator%(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w); \
} \
ATTRIBUTES NEW_TYPE operator%(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x % b, a.y % b, a.z % b, a.w % b); \
} \
ATTRIBUTES NEW_TYPE operator%(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a % b.x, a % b.y, a % b.z, a % b.w); \
} \
ATTRIBUTES void operator%=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x %= b.x; a.y %= b.y; a.z %= b.z; a.w %= b.w; \
} \
ATTRIBUTES void operator%=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x %= b, a.y %= b, a.z %= b, a.w %= b; \
} \
 \
 /* unary operator: post- and pre-increment */ \
 \
ATTRIBUTES NEW_TYPE operator++(NEW_TYPE a) { \
    return make_##NEW_TYPE(++a.x, ++a.y, ++a.z, ++a.w); \
} \
ATTRIBUTES NEW_TYPE operator++(NEW_TYPE a, int) { \
    return make_##NEW_TYPE(a.x++, a.y++, a.z++, a.w++); \
} \
 \
 /* unary operator: post- and pre-decrement */ \
 \
ATTRIBUTES NEW_TYPE operator--(NEW_TYPE a) { \
    return make_##NEW_TYPE(--a.x, --a.y, --a.z, --a.w); \
} \
ATTRIBUTES NEW_TYPE operator--(NEW_TYPE a, int) { \
    return make_##NEW_TYPE(a.x--, a.y--, a.z--, a.w--); \
} \
 \
 /* bitwise operator: and */ \
 \
ATTRIBUTES NEW_TYPE operator&(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x & b.x, a.y & b.y, a.z & b.z, a.w & b.w); \
} \
ATTRIBUTES NEW_TYPE operator&(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x & b, a.y & b, a.z & b, a.w & b); \
} \
ATTRIBUTES NEW_TYPE operator&(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a & b.x, a & b.y, a & b.z, a & b.w); \
} \
ATTRIBUTES void operator&=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x &= b.x; a.y &= b.y; a.z &= b.z; a.w &= b.w; \
} \
ATTRIBUTES void operator&=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x &= b, a.y &= b, a.z &= b, a.w &= b; \
} \
 \
 /* bitwise operator: or */ \
 \
ATTRIBUTES NEW_TYPE operator|(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x | b.x, a.y | b.y, a.z | b.z, a.w | b.w); \
} \
ATTRIBUTES NEW_TYPE operator|(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x | b, a.y | b, a.z | b, a.w | b); \
} \
ATTRIBUTES NEW_TYPE operator|(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a | b.x, a | b.y, a | b.z, a | b.w); \
} \
ATTRIBUTES void operator|=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x |= b.x; a.y |= b.y; a.z |= b.z; a.w |= b.w; \
} \
ATTRIBUTES void operator|=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x |= b, a.y |= b, a.z |= b, a.w |= b; \
} \
 \
 /* bitwise operator: exclusive or */ \
 \
ATTRIBUTES NEW_TYPE operator^(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x ^ b.x, a.y ^ b.y, a.z ^ b.z, a.w ^ b.w); \
} \
ATTRIBUTES NEW_TYPE operator^(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x ^ b, a.y ^ b, a.z ^ b, a.w ^ b); \
} \
ATTRIBUTES NEW_TYPE operator^(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a ^ b.x, a ^ b.y, a ^ b.z, a ^ b.w); \
} \
ATTRIBUTES void operator^=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x ^= b.x; a.y ^= b.y; a.z ^= b.z; a.w ^= b.w; \
} \
ATTRIBUTES void operator^=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x ^= b, a.y ^= b, a.z ^= b, a.w ^= b; \
} \
 \
 /* bitwise operator: not */ \
 \
ATTRIBUTES NEW_TYPE operator~(NEW_TYPE a) { \
    return make_##NEW_TYPE(~a.x, ~a.y, ~a.z, ~a.w); \
} \
 \
 /* operator: right-shift */ \
 \
ATTRIBUTES NEW_TYPE operator>>(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x >> b.x, a.y >> b.y, a.z >> b.z, a.w >> b.w); \
} \
ATTRIBUTES NEW_TYPE operator>>(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x >> b, a.y >> b, a.z >> b, a.w >> b); \
} \
ATTRIBUTES NEW_TYPE operator>>(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a >> b.x, a >> b.y, a >> b.z, a >> b.w); \
} \
ATTRIBUTES void operator>>=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x >>= b.x; a.y >>= b.y; a.z >>= b.z; a.w >>= b.w; \
} \
ATTRIBUTES void operator>>=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x >>= b, a.y >>= b, a.z >>= b, a.w >>= b; \
} \
 \
 /* operator: left-shift */ \
 \
ATTRIBUTES NEW_TYPE operator<<(NEW_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a.x << b.x, a.y << b.y, a.z << b.z, a.w << b.w); \
} \
ATTRIBUTES NEW_TYPE operator<<(NEW_TYPE a, BASIC_TYPE b) { \
    return make_##NEW_TYPE(a.x << b, a.y << b, a.z << b, a.w << b); \
} \
ATTRIBUTES NEW_TYPE operator<<(BASIC_TYPE a, NEW_TYPE b) { \
    return make_##NEW_TYPE(a << b.x, a << b.y, a << b.z, a << b.w); \
} \
ATTRIBUTES void operator<<=(NEW_TYPE &a, NEW_TYPE b) { \
    a.x <<= b.x; a.y <<= b.y; a.z <<= b.z; a.w <<= b.w; \
} \
ATTRIBUTES void operator<<=(NEW_TYPE a, BASIC_TYPE b) { \
    a.x <<= b, a.y <<= b, a.z <<= b, a.w <<= b; \
}


MAKE_VEC_I(char4,     char,     char4)
MAKE_VEC_I(uchar4,    uchar,    char4)
MAKE_VEC_I(short4,    short,    short4)
MAKE_VEC_I(ushort4,   ushort,   short4)
MAKE_VEC_I(int4,      int,      int4)
MAKE_VEC_I(uint4,     uint,     int4)
MAKE_VEC_I(long4,     long,     long4)
MAKE_VEC_I(ulong4,    ulong,    long4)
MAKE_VEC_F(float4,    float,    int4)
MAKE_VEC_F(double4,   double,   long4)

}

#endif // __TYPES_HPP__

