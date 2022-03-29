#pragma once


namespace func {


	class CMatrix4f32 {
	public:
		Matrix4f32 data;

		CMatrix4f32();
		CMatrix4f32(const CMatrix4f32& m);
		CMatrix4f32(const Matrix4f32& m);

		float32  get(int32 row, int32 col) const;

		CMatrix4f32& operator=(const CMatrix4f32& m);
		CMatrix4f32& operator*=(const CMatrix4f32& m);
		CMatrix4f32 operator*(const CMatrix4f32& m) const;
		float32& operator[] (std::size_t idx);
		float32 operator[] (std::size_t idx) const;

		void Identity();
		void Set(float32	c00, float32 c01, float32 c02, float32 c03,
			float32	c10, float32 c11, float32 c12, float32 c13,
			float32	c20, float32 c21, float32 c22, float32 c23,
			float32	c30, float32 c31, float32 c32, float32 c33);
		void MakeOrthographicMatrix(float32 xMin, float32 xMax, float32 yMin, float32 yMax, float32 zMin, float32 zMax);
		void Translate(const Vector3f& v);
		void Rotate(float32 angleRadiant, float32 x, float32 y, float32 z);
		void Scale(const Vector3f& v);
		void LookAt(const Vector3f& eye, const Vector3f& center, const Vector3f& up);
	};

}