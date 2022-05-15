#pragma once

namespace func {

	extern void Normalize(Plane& plane);	
	extern float32 DegreeToRadiant(float32 degree);
	extern float32 RadiantToDegree(float32 radians);
	extern int32 ToInt(float32 fval);
	extern bool8 IsEqual(float32 val1, float32 val2);
	extern bool8 IsEqual(float32 val1, float32 val2, float32 fEpsilon);
	extern float32 Color255To1(float32 x); 
	extern float32 Color1To255(float32 x);
	extern uint32 CreateIdFromPointer(void* p);
	extern void ColorFromUID(uint32 id, Vector4f& color);

	// Vector3f
	extern void	 Zero(Vector3f& v);
	extern void  vCopy(Vector3f& dst, const Vector3f& src);
	extern void	 vCross(Vector3f& v, const Vector3f& p, const Vector3f& q);
	extern void	 vMultiply(Vector3f& v, float32 f);
	extern void	 vSum(Vector3f& dst, const Vector3f& vec1, const Vector3f& vec2);
	extern void	 vSet(Vector3f& v, float32 x, float32 y, float32 z);
	extern void	 vSet(Vector3f& v, const Vector3f& b);

	// Vector4f
	extern void	 vSet(Vector4f &v, float32 x, float32 y, float32 z, float32 w);
	extern void	 vSet(Vector4f& v, const Vector4f& b);
	extern void  vCopy(Vector4f& dst, const Vector4f& src);

	//Matrix3f32
	extern void FromEulerHeadPitchRoll(Matrix3f32& m, float32 headDegrees, float32 pitchDegrees, float32 rollDegrees);

}