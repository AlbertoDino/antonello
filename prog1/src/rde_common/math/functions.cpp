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
		return IsEqual(val1,val2,f_EPSILON);
	}

	bool8 IsEqual(float32 val1, float32 val2, float32 fEpsilon)
	{
		//if (val1 < 0 && val2>0) return false;
		//if (val2 < 0 && val1>0) return false;

		return (fabs(val1 - val2) < fEpsilon);
	}

	float32 Color255To1(float32 x) { return  (float32)(x * FROM255TO1); }
	float32 Color1To255(float32 x) { return  (float32)(x / FROM255TO1); }

	uint32 CreateIdFromPointer(void* p)
	{
		uint32* me_int = (uint32*)&p;
		uint32 id = *me_int;

		byte m_ID[4];

		m_ID[0] = (id >> 24) & 0xFF;
		m_ID[1] = (id >> 16) & 0xFF;
		m_ID[2] = (id >> 8) & 0xFF;
		m_ID[3] = id & 0xFF;

		//### WARNING
		//attualmente non riesco a leggere il canale alpha (sempre a 1) per cui mi devo accontentare di 3 byte
		//e non posso usare il trick di passare il puntatore
		m_ID[3] = 255;//Id & 0xFF; 						
		uint32 add = 0;
		add = (add << 8) + (m_ID[0]);
		add = (add << 8) + (m_ID[1]);
		add = (add << 8) + (m_ID[2]);
		add = (add << 8) + (m_ID[3]);
		return add;
	}

	void ColorFromUID(uint32 id, Vector4f& color)
	{
		byte    m_colorb[4];
		m_colorb[0] = (id >> 24) & 0xFF;
		m_colorb[1] = (id >> 16) & 0xFF;
		m_colorb[2] = (id >> 8) & 0xFF;
		m_colorb[3] = id & 0xFF;

		color[0] = Color255To1(m_colorb[0]);
		color[1] = Color255To1(m_colorb[1]);
		color[2] = Color255To1(m_colorb[2]);
		color[3] = Color255To1(m_colorb[3]);
	}

	void Zero(Vector3f& v)
	{
		v[0] = 0; v[1] = 0; v[2] = 0;
	}

	void  vCopy(Vector3f& dst, const Vector3f& src)
	{
		memcpy(dst, src, sizeof(Vector3f));
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

	void vSet(Vector3f& v, const Vector3f& b)
	{
		v[0] = b[0]; v[1] = b[1]; v[2] = b[2];
	}


	void  vSet(Vector4f& v, const Vector4f& b)
	{
		v[0] = b[0]; v[1] = b[1]; v[2] = b[2]; v[3] = b[3];
	}

	void  vCopy(Vector4f& dst, const Vector4f& src)
	{
		memcpy(dst, src, sizeof(Vector4f));
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