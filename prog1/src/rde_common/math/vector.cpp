#include <rdecommon.h>
#include "functions.h"

#include "vector.h"

namespace func {

/*
========================================================================
CVector2f
========================================================================
*/

	CVector2f::CVector2f()
	{
		init();
	}

	CVector2f::CVector2f(const CVector2f& _v)
	{
		(*this) = _v;
	}

	CVector2f::CVector2f(float32 _x, float32 _y)
	{
		data[0] = _x;
		data[1] = _y;
	}

	void CVector2f::init()
	{
		data[0] = 0; data[1] = 0;
	}

	CVector2f& CVector2f::operator=(const CVector2f& a)
	{
		data[0] = a[0];
		data[1] = a[1];
		return *this;
	}

	float32 CVector2f::operator[](const int32 _i) const
	{
		return data[_i];
	}

	float32& CVector2f::operator[](const int32 _i)
	{
		return data[_i];
	}

/*
========================================================================
CVector3f
========================================================================
*/

	CVector3f::CVector3f()
	{

	}

	CVector3f::CVector3f(bool8 init)
	{
		Clear();
	}

	CVector3f::CVector3f(const CVector3f& _v)
	{
		memcpy(data, _v.data, sizeof(Vector3f));
	}



	CVector3f::CVector3f(const Vector3f& _e)
	{
		memcpy(data, _e, sizeof(Vector3f));
	}

	CVector3f::CVector3f(const float32 _x)
	{
		data[0] = data[1] = data[2] = _x;
	}

	CVector3f::CVector3f(const float32 _x, const float32 _y, const float32 _z)
	{
		data[0] = _x;
		data[1] = _y;
		data[2] = _z;
	}

	void CVector3f::Set(float32 e)
	{
		data[0] = e;
		data[1] = e;
		data[2] = e;
	}

	void CVector3f::Set(const float32 _x, const float32 _y, const float32 _z)
	{
		data[0] = _x;
		data[1] = _y;
		data[2] = _z;
	}

	float32	CVector3f::Dot(const CVector3f& _e) const
	{
		return  data[0] * _e[0] + data[1] * _e[1] + data[2] * _e[2];
	}

	CVector3f CVector3f::Cross(const CVector3f& _e) const
	{
		return CVector3f(data[1] * _e[2] - data[2] * _e[1], data[2] * _e[0] - data[0] * _e[2], data[0] * _e[1] - data[1] * _e[0]);
	}

	CVector3f& CVector3f::Cross(const CVector3f& _p, const CVector3f& _q)
	{
		data[0] = _p[1] * _q[2] - _q[1] * _p[2];
		data[1] = _p[2] * _q[0] - _q[2] * _p[0];
		data[2] = _p[0] * _q[1] - _q[0] * _p[1];
		return *this;
	}

	float32 CVector3f::LengthSquared() const
	{
		return (data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]);
	}

	float32 CVector3f::Length() const
	{
		return sqrt(LengthSquared());
	}



	void CVector3f::Normalize()
	{
		Vector2f lookup;
		float32 len = Length();
		lookup[1] = 1.0f;
		lookup[0] = 1.0f / len;
		len = lookup[IsEqual(len, 0.0f)];
		data[0] *= len; data[1] *= len; data[2] *= len;
	}

	void	CVector3f::Rotate(const CVector3f& u, const CVector3f& v, float32 angle)
	{
		CMatrix4f32 rm;
		CVector4f vec4(u[0], u[1], u[2], 1.0f);
		CVector4f result;
		rm.Rotate(angle, v[0], v[1], v[2]);
		result.Multiply(rm, vec4);
		Set(result[0], result[1], result[2]);
	}

	void	CVector3f::Clear()
	{
		memset(data, 0, sizeof(Vector3f));
	}

	CVector3f& CVector3f::operator=	(const Vector3f& a)
	{
		data[0] = a[0];
		data[1] = a[1];
		data[2] = a[2];
		return *this;
	}

	CVector3f& CVector3f::operator=(const CVector3f& a)
	{
		data[0] = a[0];
		data[1] = a[1];
		data[2] = a[2];
		return *this;
	}

	CVector3f& CVector3f::operator=	(float32 value) {
		data[0] = value;
		data[1] = value;
		data[2] = value;
		return *this;
	}


	bool8 CVector3f::operator==(const CVector3f& _v)
	{
		return IsEqual(data[0], _v[0]) && IsEqual(data[1], _v[1]) && IsEqual(data[2], _v[2]);
	}

	float32& CVector3f::operator[](const int32 _i)
	{
		return data[_i];
	}

	float32 CVector3f::operator[](const int32 _i) const
	{
		return data[_i];
	}

	CVector3f CVector3f::operator-() const
	{
		return CVector3f(-data[0], -data[1], -data[2]);
	}

	CVector3f CVector3f::operator*(const CVector3f& _e) const
	{
		return CVector3f(data[0] * _e[0], data[1] * _e[1], data[2] * _e[2]);
	}

	CVector3f CVector3f::operator*(const float32 _e) const
	{
		return CVector3f(data[0] * _e, data[1] * _e, data[2] * _e);
	}

	CVector3f& CVector3f::operator*=(const float32 _e)
	{
		data[0] *= _e;
		data[1] *= _e;
		data[2] *= _e;
		return *this;
	}

	CVector3f& CVector3f::operator*=(const CVector3f& _e)
	{
		data[0] *= _e[0];
		data[1] *= _e[1];
		data[2] *= _e[2];
		return *this;
	}

	CVector3f CVector3f::operator/(const float32 _e) const
	{
		float32 inva = 1.0f / _e;
		return CVector3f(data[0] * inva, data[1] * inva, data[2] * inva);
	}

	CVector3f& CVector3f::operator/=(const CVector3f& _e)
	{
		data[0] /= _e[0];
		data[1] /= _e[1];
		data[2] /= _e[2];
		return *this;
	}

	CVector3f CVector3f::operator+(const CVector3f& _e) const
	{
		return CVector3f(data[0] + _e[0], data[1] + _e[1], data[2] + _e[2]);
	}

	CVector3f& CVector3f::operator+=(const CVector3f& _e)
	{
		data[0] += _e[0];
		data[1] += _e[1];
		data[2] += _e[2];
		return *this;
	}

	CVector3f CVector3f::operator-(const CVector3f& _e) const
	{
		return CVector3f(data[0] - _e[0], data[1] - _e[1], data[2] - _e[2]);
	}

	CVector3f& CVector3f::operator-=(const CVector3f& _e)
	{
		data[0] -= _e[0];
		data[1] -= _e[1];
		data[2] -= _e[2];
		return *this;
	}

/*
========================================================================
CVector4f
========================================================================
*/


	CVector4f::CVector4f()
	{
	}

	CVector4f::CVector4f(const float32 _x, const float32 _y, const float32 _z, const float32 _w)
	{
		Set(_x, _y, _z, _w);
	}

	CVector4f::CVector4f(const Vector4f& _v)
	{
		memcpy(data, _v, sizeof(Vector4f));
	}

	void CVector4f::Set(float32 v)
	{
		data[0] = v;
		data[1] = v;
		data[2] = v;
		data[3] = v;
	}

	void CVector4f::Set(const float32 _x, const float32 _y, const float32 _z, const float32 _w)
	{
		data[0] = _x;
		data[1] = _y;
		data[2] = _z;
		data[3] = _w;
	}

	void CVector4f::Normalize()
	{
		// Here we calculate the magnitude of the normal to the plane (point A B C)
		// Remember that (A, B, C) is that same thing as the normal's (X, Y, Z).
		// To calculate magnitude you use the equation:  magnitude = sqrt( x^2 + y^2 + z^2)
		float32 magnitude = (float32)sqrt(data[0] * data[0] +
			data[1] * data[1] +
			data[2] * data[2]);
		// Then we divide the plane's values by it's magnitude.
		// This makes it easier to work with.
		data[0] /= magnitude;
		data[1] /= magnitude;
		data[2] /= magnitude;
		data[3] /= magnitude;
	}

	void	CVector4f::Multiply(const CMatrix4f32& matrix, const CVector4f& v)
	{
		data[0] = matrix[0] * v[0] + matrix[4] * v[1] + matrix[8] * v[2] + matrix[12] * v[3];
		data[1] = matrix[1] * v[0] + matrix[5] * v[1] + matrix[9] * v[2] + matrix[13] * v[3];
		data[2] = matrix[2] * v[0] + matrix[6] * v[1] + matrix[10] * v[2] + matrix[14] * v[3];
		data[3] = matrix[3] * v[0] + matrix[7] * v[1] + matrix[11] * v[2] + matrix[15] * v[3];
	}

	float32	 CVector4f::operator[]	(const int32 _i) const
	{
		return data[_i];
	}

	float32& CVector4f::operator[]	(const int32 _i)
	{
		return data[_i];
	}

}