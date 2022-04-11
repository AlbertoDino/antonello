#pragma once

typedef unsigned char		byte;		// 8 bits
typedef unsigned short		word;		// 16 bits
typedef unsigned int		dword;		// 32 bits
typedef unsigned long		ulong;

typedef char				char8;
typedef signed char			int8;
typedef unsigned char		uint8;
typedef unsigned char		bool8;
typedef short int			int16;
typedef unsigned short int	uint16;
typedef int					int32;
typedef unsigned int		uint32;
typedef long long			int64;
typedef unsigned long long	uint64;
typedef float				float32;
typedef double				float64;
typedef long double			float64l;



//****************************************************************************
// kVectors


typedef ulong		Vector2u[2];
typedef float32		Vector2f[2];
typedef float32		Vector3f[3];
typedef float64		Vector3d[3];
typedef int32		Vector2i[2];
typedef int32		Vector3i[3];
typedef byte		Vector3b[3];
typedef byte		Vector4b[4];
typedef float32		Vector4f[4];
typedef int32		Vector4i[4];
typedef int32		Vector5i[5];
typedef float32		Vector5f[5];
typedef Vector4f	Color;
typedef float32		Vector6f[6];
typedef float32		Vector12f[12];
typedef float32		Plane[4];
typedef uint32		Rectui[4];
typedef int32		Vector6i[6];
typedef byte		Coord2b[2];
typedef int32		Coord2i[2];
typedef int32		Recti[4];
typedef long		Rectl[4];

struct t_char
{
	char8* data;
	int32		len;
};

//****************************************************************************
// Matrix

typedef float32		Matrix3f32[9];		// A 3 x 3 matrix, column major (floats) - OpenGL Style
typedef float64		Matrix3f64[9];

typedef float32		Matrix4f32[16];		// A 4 X 4 matrix, column major (floats) - OpenGL style
typedef float64		Matrix4d64[16];		// A 4 x 4 matrix, column major (doubles) - OpenGL style

//****************************************************************************
// Quaternion
//					[w][x][y][z]
typedef float32		Quaternionf32[4];
typedef float64		Quaternionf64[4];


