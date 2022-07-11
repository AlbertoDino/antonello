#pragma once
#include "matrix.h"

namespace func {

	class CVector2i
	{
	public:
		Vector2i data;

		CVector2i();
		CVector2i(int32 i);
		CVector2i(const CVector2i& _v);
		CVector2i(int32 _x, int32 _y);

		void init();

		CVector2i& operator=	(const CVector2i& a);
		int32	   operator[]	(const int32 _i) const;
		int32&     operator[]	(const int32 _i);
	};

	class CVector3i
	{
	public:
		Vector3i data;

		CVector3i();
		CVector3i(int32 i);
		CVector3i(const CVector3i& _v);
		CVector3i(int32 _x, int32 _y, int32 _z);

		void init();

		CVector3i& operator=	(const CVector3i& a);
		int32	   operator[]	(const int32 _i) const;
		int32& operator[]	(const int32 _i);
	};


	class CVector2f
	{
	public:
		Vector2f	data;

		CVector2f();
		CVector2f(const CVector2f& _v);
		CVector2f(float32 _x, float32 _y);

		void init();

		CVector2f&	operator=	(const CVector2f& a);
		float32		operator[]	(const int32 _i) const;
		float32&	operator[]	(const int32 _i);
	};

	class CVector3f
	{
	public:
		Vector3f	data;

		CVector3f();
		CVector3f(const CVector3f& _v);
		CVector3f(bool8 init);

		explicit	CVector3f(const Vector3f& _e);
		explicit	CVector3f(const float32 _x);
		explicit	CVector3f(float32 _x, float32 _y, float32 _z);

		void		Set(float32 e);
		void		Set(float32 _x, float32 _y, float32 _z);
		float32		Dot(const CVector3f& _e) const;
		CVector3f	Cross(const CVector3f& _e) const;
		CVector3f&  Cross(const CVector3f& _p, const CVector3f& _q);
		float32		LengthSquared() const;
		float32		Length() const;
		
		void		Normalize();
		void		Rotate(const CVector3f& u, const CVector3f& v, float32 angle);
		void		Clear();

		CVector3f& operator=	(const Vector3f& a);
		CVector3f& operator=	(const CVector3f& a);
		CVector3f& operator=	(float32 value);

		bool8		operator==	(const CVector3f& _v);
		float32&    operator[]	(const int32 _i);
		float32		operator[]	(const int32 _i) const;
		CVector3f	operator-	() const;
		CVector3f	operator*	(const CVector3f& _e) const;
		CVector3f	operator*	(const float32 _e) const;
		CVector3f&  operator*=	(const float32 _e);
		CVector3f&  operator*=	(const CVector3f& _e);
		CVector3f	operator/	(const float32 _e) const;
		CVector3f&  operator/=	(const CVector3f& _e);
		CVector3f	operator+	(const CVector3f& _e) const;
		CVector3f&  operator+=	(const CVector3f& _e);
		CVector3f	operator-	(const CVector3f& _e) const;
		CVector3f&  operator-=	(const CVector3f& _e);
	};

	class CVector4f
	{
	public:
		Vector4f	data;

		CVector4f();
		CVector4f(const float32 _x, const float32 _y, const float32 _z, const float32 _w);
		explicit CVector4f(const Vector4f& _v);

		void	Set(float32 v);
		void	Set(const float32 _x, const float32 _y, const float32 _z, const float32 _w);
		void	Normalize();
		void	Multiply(const CMatrix4f32& matrix, const CVector4f& v);

		float32	  operator[]	(const int32 _i) const;
		float32&  operator[]	(const int32 _i);
	};
}
