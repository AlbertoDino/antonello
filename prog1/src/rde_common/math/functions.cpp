#include "..\header\rdecommon.h"
#include "functions.h"

namespace func {

	const float Snapper = 3 << 22;

	union UFloatInt {
		int i;
		float f;
	};

	//============================================================

	void Normalize(Plane& plane)
	{
		// Here we calculate the magnitude of the normal to the plane (point A B C)
		// Remember that (A, B, C) is that same thing as the normal's (X, Y, Z).
		// To calculate magnitude you use the equation:  magnitude = sqrt( x^2 + y^2 + z^2)
		float magnitude = (float)sqrt(plane[0] * plane[0] +
			plane[1] * plane[1] +
			plane[2] * plane[2]);
		// Then we divide the plane's values by it's magnitude.
		// This makes it easier to work with.
		plane[0] /= magnitude;
		plane[1] /= magnitude;
		plane[2] /= magnitude;
		plane[3] /= magnitude;
	}

	float32 DegreeToRadiant(float32 degree)
	{
		return (float32)(degree * DEGREES_TO_RADIANT);
	}

	float32 RadiantToDegree(float32 radians)
	{
		return (radians * RADIANT_TO_DEGREE);
	}

	void Identity(Matrix4f32& m)
	{
		static Matrix4f32	identity = { 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };
		memcpy(m, identity, sizeof(Matrix4f32));
	}

#define A(row,col)  m[(col<<2)+row]
	void Set(Matrix4f32& m,float32 c00, float32 c01, float32 c02, float32 c03, float32 c10, float32 c11, float32 c12, float32 c13, float32 c20, float32 c21, float32 c22, float32 c23, float32 c30, float32 c31, float32 c32, float32 c33)
	{
		A(0, 0) = c00;
		A(0, 1) = c01;
		A(0, 2) = c02;
		A(0, 3) = c03;

		A(1, 0) = c10;
		A(1, 1) = c11;
		A(1, 2) = c12;
		A(1, 3) = c13;

		A(2, 0) = c20;
		A(2, 1) = c21;
		A(2, 2) = c22;
		A(2, 3) = c23;

		A(3, 0) = c30;
		A(3, 1) = c31;
		A(3, 2) = c32;
		A(3, 3) = c33;
	}
#undef A

	void MakeOrthographicMatrix(Matrix4f32 &ortho, float32 xMin, float32 xMax, float32 yMin, float32 yMax, float32 zMin, float32 zMax)
	{
		Identity(ortho);

		ortho[0] = 2.0f / (xMax - xMin);
		ortho[5] = 2.0f / (yMax - yMin);
		ortho[10] = -2.0f / (zMax - zMin);
		ortho[12] = -((xMax + xMin) / (xMax - xMin));
		ortho[13] = -((yMax + yMin) / (yMax - yMin));
		ortho[14] = -((zMax + zMin) / (zMax - zMin));
		ortho[15] = 1.0f;
	}

	void Translate(Matrix4f32& m, const Vector3f& v)
	{
		Identity(m);
		m[12] = v[0]; m[13] = v[1]; m[14] = v[2];
	}

	int32 ToInt(float32 fval) 
	{
		func::UFloatInt& fi = *(func::UFloatInt*)&fval;
		fi.f += func::Snapper;
		return ((fi.i) & 0x007fffff) - 0x00400000;
	}

	bool8 IsEqual(float32 val1, float32 val2)
	{
		return (fabs(val1 - val2) < f_EPSILON);
	}

	bool8 IsEqual(float32 val1, float32 val2, float32 fEpsilon)
	{
		return (fabs(val1 - val2) < fEpsilon);
	}

	void Zero(Vector3f& v)
	{
		v[0] = 0; v[1] = 0; v[2] = 0;
	}

	void vCross(Vector3f& v, const Vector3f& p, const Vector3f& q)
	{
		v[0] = p[1] * q[2] - q[1] * p[2];
		v[1] = p[2] * q[0] - q[2] * p[0];
		v[2] = p[0] * q[1] - q[0] * p[1];
	}

	void vMultiply(Vector3f& v, float32 f)
	{
		v[0] *= f; v[1] *= f; v[2] *= f;
	}

	void vSum(Vector3f& dst, const Vector3f& vec1, const Vector3f& vec2)
	{
		dst[0] = vec1[0] + vec2[0]; dst[1] = vec1[1] + vec2[1]; dst[2] = vec1[2] + vec2[2];
	}

	void vSet(Vector3f& v, float32 x, float32 y, float32 z) 
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
	}

	void vSet(Vector4f& v, float32 x, float32 y, float32 z, float32 w)
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
	}

#define A33(row,col)  m[(col*3)+row]

	void FromEulerHeadPitchRoll(Matrix3f32& m, float32 headDegrees, float32 pitchDegrees, float32 rollDegrees)
	{
		// Constructs a rotation matrix based on a Euler Transform.
		// We use the popular NASA standard airplane convention of 
		// heading-pitch-roll (i.e., RzRxRy).

		headDegrees = DegreeToRadiant(headDegrees);
		pitchDegrees = DegreeToRadiant(pitchDegrees);
		rollDegrees = DegreeToRadiant(rollDegrees);

		float32 cosH = cosf(headDegrees);
		float32 cosP = cosf(pitchDegrees);
		float32 cosR = cosf(rollDegrees);
		float32 sinH = sinf(headDegrees);
		float32 sinP = sinf(pitchDegrees);
		float32 sinR = sinf(rollDegrees);


		A33(0, 0) = cosR * cosH - sinR * sinP * sinH;
		A33(0, 1) = sinR * cosH + cosR * sinP * sinH;
		A33(0, 2) = -cosP * sinH;

		A33(1, 0) = -sinR * cosP;
		A33(1, 1) = cosR * cosP;
		A33(1, 2) = sinP;

		A33(2, 0) = cosR * sinH + sinR * sinP * cosH;
		A33(2, 1) = sinR * sinH - cosR * sinP * cosH;
		A33(2, 2) = cosP * cosH;
	}

#undef A33

}