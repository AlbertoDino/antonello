#pragma once

namespace func {

	class World {
	public:
		static  CVector3f		World_X_Axis;
		static  CVector3f		World_Y_Axis;
		static  CVector3f		World_Z_Axis;
	};

	class Quaternion {
	
	public:
		Quaternion();
		Quaternion(float32 _w, float32 _x, float32 _y, float32 _z);
		Quaternion(const Quaternion& q);

		void set(float32 _w, float32 _x, float32 _y, float32 _z,float32 accum);
		void setIdentity();

		void		FromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
		void		FromMatrix3(const Matrix3f32& m);
		void		FromAxisAngle(const CVector3f& axis, float degrees);
		void		Angle(const CVector3f& angles);
		void		Normalize();

		void		ToAxisAngle(CVector3f& axis, float& degrees) const;
		void		ToMatrix4(CMatrix4f32& mat) const;
		void		ToMatrix3x4(float32(*matrix)[4]) const;

		void		RotateAsCamera(const CVector3f& rotation, float32 elpase, float32 epsilon);
		void		Rotate(const CVector3f& rotation, float32 elapse);

		//Some useful (normalized) quaternions 
		//http://www.ogre3d.org/tikiwiki/Quaternion+and+Rotation+Primer

		void		SetTurned_90_AxeX();
		void		SetTurned_90_AxeY();
		void		SetTurned_90_AxeZ();
		void		SetTurned_Less90_AxeX();
		void		SetTurned_Less90_AxeY();
		void		SetTurned_Less90_AxeZ();

		void		Multiply(Vector3f& out, const Vector3f& rhs) const;

		Quaternion  operator*(const Quaternion& rhs) const;		
		Quaternion  operator*(float32 scalar) const;
		Quaternion& operator*=(const Quaternion& rhs);
		Quaternion& operator*=(float32 scalar);
		Quaternion& operator=(const Quaternion& rhs);

		static float32		Dot(const Quaternion& x, const Quaternion& y);
		static Quaternion	Mix(const Quaternion& x, const Quaternion& y, float32 t);
		static Quaternion	Slerp(Quaternion& a, Quaternion b, float32 t);


		float32				w, x, y, z;
		float32				accumPitchDegrees;
	};

}
