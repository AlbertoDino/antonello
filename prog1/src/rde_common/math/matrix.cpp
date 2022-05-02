#include <rdecommon.h>
#include "functions.h"
#include "matrix.h"

namespace func {

	CMatrix3f32::CMatrix3f32() {
		identity();
	}

	CMatrix3f32& CMatrix3f32::operator=(const CMatrix3f32& m)
	{
		memcpy(data, m.data, sizeof(Matrix3f32));
		return *this;
	}

	void CMatrix3f32::identity()
	{
		static Matrix3f32	identity = { 1.0f, 0.0f, 0.0f, 
				0.0f, 1.0f, 0.0f, 
				0.0f, 0.0f, 1.0f
				 };
		memcpy(data, identity, sizeof(Matrix3f32));
	}

	CMatrix4f32::CMatrix4f32()
	{
		Identity();
	}

	CMatrix4f32::CMatrix4f32(const CMatrix4f32& m)
	{
		memcpy(data, m.data, sizeof(Matrix4f32));
	}

	CMatrix4f32::CMatrix4f32(const Matrix4f32& m)
	{
		memcpy(data, m, sizeof(Matrix4f32));
	}

	float32 CMatrix4f32::get(int32 row, int32 col) const
	{
		return data[(col << 2) + row];
	}

	CMatrix4f32& CMatrix4f32::operator=(const CMatrix4f32& m)
	{
		memcpy(data, m.data, sizeof(Matrix4f32));
		return *this;
	}

#define A(row,col)  data[(col<<2)+row]
#define B(row,col)  m.data[(col<<2)+row]
#define P(row,col)  p[(col<<2)+row]
	CMatrix4f32& CMatrix4f32::operator*=(const CMatrix4f32& m)
	{
		Matrix4f32 p;
		for (int i = 0; i < 4; i++) {
			float ai0 = A(i, 0), ai1 = A(i, 1), ai2 = A(i, 2), ai3 = A(i, 3);
			P(i, 0) = ai0 * B(0, 0) + ai1 * B(1, 0) + ai2 * B(2, 0) + ai3 * B(3, 0);
			P(i, 1) = ai0 * B(0, 1) + ai1 * B(1, 1) + ai2 * B(2, 1) + ai3 * B(3, 1);
			P(i, 2) = ai0 * B(0, 2) + ai1 * B(1, 2) + ai2 * B(2, 2) + ai3 * B(3, 2);
			P(i, 3) = ai0 * B(0, 3) + ai1 * B(1, 3) + ai2 * B(2, 3) + ai3 * B(3, 3);
		}
		memcpy(data, &p, sizeof(Matrix4f32));
		return *this;
	}
#undef P
#undef B
#undef A

	CMatrix4f32 CMatrix4f32::operator*(const CMatrix4f32& m) const
	{
		CMatrix4f32 tmp(*this);
		tmp *= m;
		return tmp;
	}

	float32& CMatrix4f32::operator[](std::size_t idx)
	{
		return data[idx];
	}

	float32 CMatrix4f32::operator[](std::size_t idx) const
	{
		return data[idx];
	}

	void CMatrix4f32::Identity()
	{
		static Matrix4f32	identity = { 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };
		memcpy(data, identity, sizeof(Matrix4f32));

	}

#define A(row,col)  data[(col<<2)+row]
	void CMatrix4f32::Set(float32 c00, float32 c01, float32 c02, float32 c03, float32 c10, float32 c11, float32 c12, float32 c13, float32 c20, float32 c21, float32 c22, float32 c23, float32 c30, float32 c31, float32 c32, float32 c33)
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

	void CMatrix4f32::MakeOrthographicMatrix(float32 xMin, float32 xMax, float32 yMin, float32 yMax, float32 zMin, float32 zMax)
	{
		Identity();

		data[0] = 2.0f / (xMax - xMin);
		data[5] = 2.0f / (yMax - yMin);
		data[10] = -2.0f / (zMax - zMin);
		data[12] = -((xMax + xMin) / (xMax - xMin));
		data[13] = -((yMax + yMin) / (yMax - yMin));
		data[14] = -((zMax + zMin) / (zMax - zMin));
		data[15] = 1.0f;
	}


	void CMatrix4f32::Translate(const Vector3f& v)
	{
		Identity();
		data[12] = v[0]; data[13] = v[1]; data[14] = v[2];
	}

#define A(row,col)  data[(col<<2)+row]
	void CMatrix4f32::Rotate(float32 angleRadiant, float32 x, float32 y, float32 z)
	{
		float32 mag, s, c;
		float32 xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

		s = float32(sin(angleRadiant));
		c = float32(cos(angleRadiant));

		mag = float32(sqrt(x * x + y * y + z * z));

		// Identity matrix
		if (mag == 0.0f) {
			Identity();
			return;
		}

		// Rotation matrix is normalized
		x /= mag;
		y /= mag;
		z /= mag;

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * s;
		ys = y * s;
		zs = z * s;
		one_c = 1.0f - c;

		A(0, 0) = (one_c * xx) + c;
		A(0, 1) = (one_c * xy) - zs;
		A(0, 2) = (one_c * zx) + ys;
		A(0, 3) = 0.0f;

		A(1, 0) = (one_c * xy) + zs;
		A(1, 1) = (one_c * yy) + c;
		A(1, 2) = (one_c * yz) - xs;
		A(1, 3) = 0.0f;

		A(2, 0) = (one_c * zx) - ys;
		A(2, 1) = (one_c * yz) + xs;
		A(2, 2) = (one_c * zz) + c;
		A(2, 3) = 0.0f;

		A(3, 0) = 0.0f;
		A(3, 1) = 0.0f;
		A(3, 2) = 0.0f;
		A(3, 3) = 1.0f;
	}
#undef A

	void CMatrix4f32::Scale(const Vector3f& v)
	{
		Identity();
		data[0] = v[0];
		data[5] = v[1];
		data[10] = v[2];
	}

#define A(row,col)  data[(col<<2)+row]
	void CMatrix4f32::LookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up)
	{
		glm::vec3 e, c, u;

		e.x = eye[0];
		e.y = eye[1];
		e.z = eye[2];

		c.x = center[0];
		c.y = center[1];
		c.z = center[2];

		u.x = up[0];
		u.y = up[1];
		u.z = up[2];

		glm::vec3  f = glm::normalize(c - e);
		u = glm::normalize(u);
		glm::vec3  s = glm::normalize(glm::cross(f, u));
		u = cross(s, f);

		glm::mat4x4 Result(1);
		A(0,0) = s.x;
		A(1,0) = s.y;
		A(2,0) = s.z;
		A(0,1) = u.x;
		A(1,1) = u.y;
		A(2,1) = u.z;
		A(0,2) = -f.x;
		A(1,2) = -f.y;
		A(2,2) = -f.z;
		A(3,0) = -glm::dot(s, e);
		A(3,1) = -glm::dot(u, e);
		A(3,2) = glm::dot(f, e);

	}
#undef A

	const CMatrix3f32& CMatrix4f32::getNormalMatrix() {
		// Extract a rotation matrix from a 4x4 matrix
		// Extracts the rotation matrix (3x3) from a 4x4 matrix
		static CMatrix3f32 dst;
		memcpy(dst.data, data, sizeof(float) * 3); // X column
		memcpy(dst.data + 3, data + 4, sizeof(float) * 3); // Y column
		memcpy(dst.data + 6, data + 8, sizeof(float) * 3); // Z column
		return dst;
	}

}