#include <rdecommon.h>
#include "functions.h"
#include "matrix.h"
#include "vector.h"
#include "quaternion.h"

namespace func {

	//============================================================
	CVector3f		World::World_X_Axis;
	CVector3f		World::World_Y_Axis;
	CVector3f		World::World_Z_Axis;
	//============================================================

#define DEGREE_LIMIT			90.0f

	Quaternion::Quaternion()
	{
		setIdentity();
	}

	Quaternion::Quaternion(float32 _w, float32 _x, float32 _y, float32 _z)
		: w(_w), x(_x), y(_y), z(_z), accumPitchDegrees(0.0f)
	{
	}

	Quaternion::Quaternion(const Quaternion& q)
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
		accumPitchDegrees = q.accumPitchDegrees;
	}

	void Quaternion::set(float32 _w, float32 _x, float32 _y, float32 _z, float32 accum)
	{
		w = _w;
		x = _x;
		y = _y;
		z = _z;
		accumPitchDegrees = accum;
	}

	void Quaternion::setIdentity()
	{
		w = 1.0f;
		x = y = z = 0.0f;
		accumPitchDegrees = 0.0f;
	}

	void Quaternion::FromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees)
	{
		Matrix3f32 m;
		func::FromEulerHeadPitchRoll(m, headDegrees, pitchDegrees, rollDegrees);
		FromMatrix3(m);
	}

#define M(row,col)  m[(col*3)+row]
	void Quaternion::FromMatrix3(const Matrix3f32& m)
	{
		// Creates a quaternion from a rotation matrix. 
		// The algorithm used is from Allan and Mark Watt's "Advanced 
		// Animation and Rendering Techniques" (ACM Press 1992).

		float32 s = 0.0f;
		float32 q[4] = { 0.0f };
		float32 trace = M(0, 0) + M(1, 1) + M(2, 2);

		if (trace > 0.0f)
		{
			s = sqrtf(trace + 1.0f);
			q[3] = s * 0.5f;
			s = 0.5f / s;
			q[0] = (M(1, 2) - M(2, 1)) * s;
			q[1] = (M(2, 0) - M(0, 2)) * s;
			q[2] = (M(0, 1) - M(1, 0)) * s;
		}
		else
		{
			int32 nxt[3] = { 1, 2, 0 };
			int32 i = 0, j = 0, k = 0;

			if (M(1, 1) > M(0, 0))
				i = 1;

			if (M(2, 2) > M(i, i))
				i = 2;

			j = nxt[i];
			k = nxt[j];
			s = sqrtf((M(i, i) - (M(j, j) + M(k, k))) + 1.0f);

			q[i] = s * 0.5f;
			s = 0.5f / s;
			q[3] = (M(j, k) - M(k, j)) * s;
			q[j] = (M(i, j) + M(j, i)) * s;
			q[k] = (M(i, k) + M(k, i)) * s;
		}

		x = q[0], y = q[1], z = q[2], w = q[3];
	}
#undef M

	void Quaternion::FromAxisAngle(const CVector3f& axis, float degrees)
	{
		float32 sinAngle;
		degrees = func::DegreeToRadiant(degrees) * 0.5f;
		sinAngle = sinf(degrees);

		x = (axis[0] * sinAngle);
		y = (axis[1] * sinAngle);
		z = (axis[2] * sinAngle);
		w = cosf(degrees);
	}

	void Quaternion::Angle(const CVector3f& angles)
	{
		float32		angle;
		float32		sr, sp, sy, cr, cp, cy;

		// FIXME: rescale the inputs to 1/2 angle
		angle = angles[2] * 0.5f;
		sy = sin(angle);
		cy = cos(angle);
		angle = angles[1] * 0.5f;
		sp = sin(angle);
		cp = cos(angle);
		angle = angles[0] * 0.5f;
		sr = sin(angle);
		cr = cos(angle);

		x = sr * cp * cy - cr * sp * sy; // X
		y = cr * sp * cy + sr * cp * sy; // Y
		z = cr * cp * sy - sr * sp * cy; // Z
		w = cr * cp * cy + sr * sp * sy; // W
	}

	void Quaternion::Normalize()
	{
		float32 len = x * x + y * y + z * z + w * w;
		if (len <= 0.0f)
		{
			x = 0;
			y = 0;
			z = 0;
			w = 1;
		}
		else
		{
			float32 oneOverLen = 1.0f / len;
			x *= oneOverLen;
			y *= oneOverLen;
			z *= oneOverLen;
			w *= oneOverLen;
		}
	}

	void Quaternion::ToAxisAngle(CVector3f& axis, float& degrees) const
	{
		// Converts this quaternion to an axis and an angle.

		float32 sinHalfThetaSq = 1.0f - w * w;

		// Guard against numerical imprecision and identity quaternions.
		if (sinHalfThetaSq <= 0.0f)
		{
			axis[0] = 1.0f, axis[1] = axis[2] = 0.0f;
			degrees = 0.0f;
		}
		else
		{
			float32 invSinHalfTheta = 1.0f / sqrtf(sinHalfThetaSq);

			axis[0] = x * invSinHalfTheta;
			axis[1] = y * invSinHalfTheta;
			axis[2] = z * invSinHalfTheta;
			degrees = func::RadiantToDegree(2.0f * acosf(w));
		}
	}

	void Quaternion::ToMatrix4(CMatrix4f32& mat) const
	{
		float32 x2 = x * x;
		float32 y2 = y * y;
		float32 z2 = z * z;
		float32 xy = x * y;
		float32 xz = x * z;
		float32 yz = y * z;
		float32 wx = w * x;
		float32 wy = w * y;
		float32 wz = w * z;

		mat.Set(1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
			2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Quaternion::ToMatrix3x4(float32(*matrix)[4]) const
	{
		matrix[0][0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
		matrix[1][0] = 2.0f * x * y + 2.0f * w * z;
		matrix[2][0] = 2.0f * x * z - 2.0f * w * y;

		matrix[0][1] = 2.0f * x * y - 2.0f * w * z;
		matrix[1][1] = 1.0f - 2.0f * x * x - 2.0f * z * z;
		matrix[2][1] = 2.0f * y * z + 2.0f * w * x;

		matrix[0][2] = 2.0f * x * z + 2.0f * w * y;
		matrix[1][2] = 2.0f * y * z - 2.0f * w * x;
		matrix[2][2] = 1.0f - 2.0f * x * x - 2.0f * y * y;
	}

	void Quaternion::RotateAsCamera(const CVector3f& rotation, float32 elpase, float32 epsilon)
	{
		float32	yaw = rotation[0] * elpase;
		float32	pitc = rotation[1] * elpase;
		//float32	roll = _vRotation[2] * _elapsetime;


		accumPitchDegrees += pitc;

		if (accumPitchDegrees > DEGREE_LIMIT)
		{
			pitc = DEGREE_LIMIT - (accumPitchDegrees - pitc);
			accumPitchDegrees = DEGREE_LIMIT;
		}

		if (accumPitchDegrees < -DEGREE_LIMIT)
		{
			pitc = -DEGREE_LIMIT - (accumPitchDegrees - pitc);
			accumPitchDegrees = -DEGREE_LIMIT;
		}

		Quaternion rot;

		// Rotate camera about the world y axis.
		// Note the order the quaternions are multiplied. That is important!
		if (!IsEqual(yaw, 0.0f, epsilon))
		{
			rot.FromAxisAngle(World::World_Y_Axis,yaw);
			(*this) = (*this) * rot;
		}

		// Rotate camera about its local x axis.
		// Note the order the quaternions are multiplied. That is important!
		if (!IsEqual(pitc, 0.0f, epsilon))
		{
			rot.FromAxisAngle(World::World_X_Axis, pitc);
			(*this) = rot * (*this);
		}
	}

	void Quaternion::Rotate(const CVector3f& rotation, float32 elapse)
	{
		float32	heading = rotation[0] * elapse;
		float32	pitc = rotation[1] * elapse;
		float32	roll = rotation[2] * elapse;

		static float32 degree_limit = 90.0f;

		accumPitchDegrees += pitc;

		if (accumPitchDegrees > degree_limit) {
			pitc = degree_limit - (accumPitchDegrees - pitc);
			accumPitchDegrees = degree_limit;
		}

		if (accumPitchDegrees < -degree_limit) {
			pitc = -degree_limit - (accumPitchDegrees - pitc);
			accumPitchDegrees = -degree_limit;
		}

		Quaternion rot;

		// Rotate camera about the world y axis.
		// Note the order the quaternions are multiplied. That is important!
		if (!IsEqual(heading, 0.0f, f_EPSILON)) {
			rot.FromAxisAngle(World::World_Y_Axis, heading);
			(*this) = rot * (*this);
		}

		// Rotate camera about its local x axis.
		// Note the order the quaternions are multiplied. That is important!
		if (!IsEqual(pitc, 0.0f, f_EPSILON)) {
			rot.FromAxisAngle(World::World_X_Axis, pitc);
			(*this) = rot * (*this);
		}
	}

	void Quaternion::SetTurned_90_AxeX()
	{
		w = sqrt(0.5f);
		x = sqrt(0.5f);
		y = 0.0f;
		z = 0.0f;
	}

	void Quaternion::SetTurned_90_AxeY()
	{
		w = sqrt(0.5f);
		x = 0.0f;
		y = sqrt(0.5f);
		z = 0.0f;
	}

	void Quaternion::SetTurned_90_AxeZ()
	{
		w = sqrt(0.5f);
		x = 0.0f;
		y = 0.0f;
		z = sqrt(0.5f);
	}

	void Quaternion::SetTurned_Less90_AxeX()
	{
		w = sqrt(0.5f);
		x = -sqrt(0.5f);
		y = 0.0f;
		z = 0.0f;
	}

	void Quaternion::SetTurned_Less90_AxeY()
	{
		w = sqrt(0.5f);
		x = 0.0f;
		y = -sqrt(0.5f);
		z = 0.0f;
	}

	void Quaternion::SetTurned_Less90_AxeZ()
	{
		w = sqrt(0.5f);
		x = 0.0f;
		y = 0.0f;
		z = -sqrt(0.5f);
	}

	void Quaternion::Multiply(Vector3f& out, const Vector3f& rhs) const
	{
		Vector3f uv, uuv, q;
		q[0] = x;
		q[1] = y;
		q[2] = z;

		func::vCross(uv, q, rhs);
		func::vCross(uuv, q, uv);

		func::vMultiply(uv, (2 * w));
		func::vMultiply(uuv, 2);

		func::vSum(out, rhs, uv);
		func::vSum(out, out, uuv);
	}

	Quaternion Quaternion::operator*(const Quaternion& rhs) const
	{
		Quaternion tmp(*this);
		tmp *= rhs;
		return tmp;
	}

	Quaternion Quaternion::operator*(float32 scalar) const
	{
		Quaternion tmp(*this);
		tmp *= scalar;
		return tmp;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& rhs)
	{
		Quaternion tmp(
			(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z), //w
			(w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y), //x
			(w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x), //y
			(w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w));//z
		*this = tmp;
		return *this;
	}

	Quaternion& Quaternion::operator*=(float32 scalar)
	{
		w *= scalar, x *= scalar, y *= scalar, z *= scalar;
		return *this;
	}

	Quaternion& Quaternion::operator=(const Quaternion& rhs)
	{
		this->w = rhs.w;
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		this->accumPitchDegrees = rhs.accumPitchDegrees;
		return *this;
	}

	float32 Quaternion::Dot(const Quaternion& q1, const Quaternion& q2)
	{
		return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	}

	Quaternion Quaternion::Mix(const Quaternion& x, const Quaternion& y, float32 t)
	{
		if (t <= 0.0f) return x;
		if (t >= 1.0f) return y;
		Quaternion out;
		float fCos = Dot(x, y);
		Quaternion y2(y);
		if (fCos < 0.0f)
		{
			y2.x = -y.x;
			y2.y = -y.y;
			y2.z = -y.z;
			y2.w = -y.w;

			fCos = -fCos;
		}

		float k0, k1;

		if (fCos > 0.9999f)
		{
			k0 = 1.0f - t;
			k1 = 0.0f + t;
		}
		else
		{
			float32 fSin = sqrt(1.0f - fCos * fCos);
			float32 fAngle = atan2(fSin, fCos);
			float32 fOneOverSin = 1.0f / fSin;

			k0 = sin((1.0f - t) * fAngle) * fOneOverSin;
			k1 = sin((0.0f + t) * fAngle) * fOneOverSin;

		}

		out.w = k0 * x.w + k1 * y2.w;
		out.x = k0 * x.x + k1 * y2.x;
		out.y = k0 * x.y + k1 * y2.y;
		out.z = k0 * x.z + k1 * y2.z;

		return out;
	}

	Quaternion Quaternion::Slerp(Quaternion& a, Quaternion b, float32 t)
	{
		// Smoothly interpolates from quaternion 'a' to quaternion 'b' using
		// spherical linear interpolation.
		// 
		// Both quaternions must be unit length and represent absolute rotations.
		// In particular quaternion 'b' must not be relative to quaternion 'a'.
		// If 'b' is relative to 'a' make 'b' an absolute rotation by: b = a * b.
		// 
		// The interpolation parameter 't' is in the range [0,1]. When t = 0 the
		// resulting quaternion will be 'a'. When t = 1 the resulting quaternion
		// will be 'b'.
		//
		// The algorithm used is adapted from Allan and Mark Watt's "Advanced
		// Animation and Rendering Techniques" (ACM Press 1992).

		Quaternion result;
		float32 omega = 0.0f;
		float32 cosom = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		float32 sinom = 0.0f;
		float32 scale0 = 0.0f;
		float32 scale1 = 0.0f;

		if ((1.0f + cosom) > f_EPSILON)
		{
			// 'a' and 'b' quaternions are not opposite each other.

			if ((1.0f - cosom) > f_EPSILON)
			{
				// Standard case - slerp.
				omega = acosf(cosom);
				sinom = sinf(omega);
				scale0 = sinf((1.0f - t) * omega) / sinom;
				scale1 = sinf(t * omega) / sinom;
			}
			else
			{
				// 'a' and 'b' quaternions are very close so lerp instead.
				scale0 = 1.0f - t;
				scale1 = t;
			}

			result.x = scale0 * a.x + scale1 * b.x;
			result.y = scale0 * a.y + scale1 * b.y;
			result.z = scale0 * a.z + scale1 * b.z;
			result.w = scale0 * a.w + scale1 * b.w;
		}
		else
		{
			// 'a' and 'b' quaternions are opposite each other.

			result.x = -b.y;
			result.y = b.x;
			result.z = -b.w;
			result.w = b.z;

			scale0 = sinf((1.0f - t) - HALF_PI);
			scale1 = sinf(t * HALF_PI);

			result.x = scale0 * a.x + scale1 * result.x;
			result.y = scale0 * a.y + scale1 * result.y;
			result.z = scale0 * a.z + scale1 * result.z;
			result.w = scale0 * a.w + scale1 * result.w;
		}

		return result;
	}

}