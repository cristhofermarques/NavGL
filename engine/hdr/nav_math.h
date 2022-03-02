#ifndef NAV_MATH_H
#define NAV_MATH_H

#include<math.h>

#define GBIT( value, bitIdx)( value & (1 << bitIdx))
#define ABIT( value, bitIdx)( value |= (1 << bitIdx))
#define DBIT( value, bitIdx)( value &= ~(1 << bitIdx))


typedef struct { int x, y;} VecI2;
typedef struct { float x, y;} Vec2;

#define VEC2( x, y) { x, y}

#define AV2( a, b) a.x += b.x; a.y += b.y;
#define SV2( a, b) a.x -= b.x; a.y -= b.y;
#define MV2( a, b) a.x *= b.x; a.y *= b.y;
#define DV2( a, b) a.x /= b.x; a.y /= b.y;

#define ASV2( a, b) a.x += b; a.y += b;
#define SSV2( a, b) a.x -= b; a.y -= b;
#define MSV2( a, b) a.x *= b; a.y *= b;
#define DSV2( a, b) a.x /= b; a.y /= b;


#define LENV2( a) (float) sqrt( a.x * a.x + a.y * a.y)
#define NORMV2( a){ float len = LENV2( a); DTSV2( a, len);}
#define ABSV2( a) a.x = (float)fabs(a.x); a.y = (float)fabs(a.y);
#define DOTV2( a, b) (a.x * b.x + a.y * b.y)
#define CROSSV2( a, b)( a.x * b.y - a.y * b.x)


typedef struct { int x, y, z;} VecI3;
typedef struct { float x, y, z;} Vec3;

#define VEC3( x, y, z) { x, y, z}

#define ASV3( a, b) a.x += b; a.y += b; a.z += b;
#define SSV3( a, b) a.x -= b; a.y -= b; a.z -= b;
#define MSV3( a, b) a.x *= b; a.y *= b; a.z *= b;
#define DSV3( a, b) a.x /= b; a.y /= b; a.z /= b;

#define AV3( a, b) a.x += b.x; a.y += b.y; a.z += b.z;
#define SV3( a, b) a.x -= b.x; a.y -= b.y; a.z -= b.z;
#define MV3( a, b) a.x *= b.x; a.y *= b.y; a.z *= b.z;
#define DV3( a, b) a.x /= b.x; a.y /= b.y; a.z /= b.z;

#define LENV3( a) (float)sqrt( a.x * a.x + a.y * a.y + a.z * a.z)
#define NORMV3( a) { float len = LENV3( a); DTSV3( a, len);}
#define ABSV3( a) a.x = (float)fabs(a.x); a.y = (float)fabs(a.y); a.z = (float)fabs(a.z);
#define DOTV3( a, b) (a.x * b.x + a.y * b.y + a.z * b.z)
#define CROSSV3( a, b) { a.y * b.z - z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x}

typedef struct { float v[4][4];} Mat4;

#define IDM4( m) \
    m.v[0][0] = 1.0f; m.v[0][1] = 0.0f; m.v[0][2] = 0.0f; m.v[0][3] = 0.0f;\
    m.v[1][0] = 0.0f; m.v[1][1] = 1.0f; m.v[1][2] = 0.0f; m.v[1][3] = 0.0f;\
    m.v[2][0] = 0.0f; m.v[2][1] = 0.0f; m.v[2][2] = 1.0f; m.v[2][3] = 0.0f;\
    m.v[3][0] = 0.0f; m.v[3][1] = 0.0f; m.v[3][2] = 0.0f; m.v[3][3] = 1.0f;
    


#define PERSPM4( mat, fov, aspect, near, far)\
    IDM4( mat);\
    mat.v[0][0] = 1.0f / ( aspect * tan( fov / 2));\
    mat.v[1][1] = 1.0f / tan( fov / 2);\
    mat.v[2][2] = -( far + near / far - near);\
    mat.v[2][3] =  ( 2 * far * near / far - near);\
    mat.v[3][2] =  -1;


#define ORTHOM4( mat, left, right, top, bottom, near, far)\
    IDM4( mat);\
    mat.v[0][0] = 2.0f / ( right - left);\
    mat.v[0][3] = -( ( right + left) / ( right - left));\
    mat.v[1][1] = 2.0f / ( top - bottom);\
    mat.v[1][3] = -( ( top + bottom) / ( top - bottom));\
    mat.v[2][2] = -2.0f / (far - near);\
    mat.v[2][3] = -( ( far + near) / ( far - near));\
    mat.v[3][3] = 1.0f;

#endif