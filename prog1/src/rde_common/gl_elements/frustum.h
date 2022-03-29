#pragma once


namespace oglElements {

	class Frustum {
	protected:
		Plane		planes[6];
	public:

		Frustum();
		~Frustum();

		//http://www.crownandcutlass.com/features/technicaldetails/frustum.html

		void	calculateFrom(const func::CMatrix4f32& view, const func::CMatrix4f32& proj);
		bool8	isBoxInFrustrum(float32 x, float32 y, float32 z, float32 x2, float32 y2, float32 z2) const;
		bool8	isSphereInFrustrum(float32 x, float32 y, float32 z, float32 radius) const;

	};

}
