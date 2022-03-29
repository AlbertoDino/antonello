#pragma once


using namespace func;

namespace oglElements {

	enum e_PerspectiveType { ftNone, ftFrustum, ftOrtho };

	class Perspective {

	private:
		CMatrix4f32 			projMatrix;
		e_PerspectiveType		type;
	public:

		Vector2f				facScreenToView;
		Coord2i					screenSize;
		Vector2f				perspectiveSize;


		Perspective();
		~Perspective();

		Perspective(const Perspective&);
		Perspective& operator=(const Perspective& other);


		void	setScreenSize(int width, int height);
		// Calculates the corners of the Perspective and sets the projection matrix.
		// Set Perspective Matrix Projection
		void	setFrustum(float fFov, float fAspect, float fNear, float fFar);

		// Calculates the corners of the Perspective and sets the projection matrix.
		// Orthographics Matrix Projection  
		void	setOrthographic(float32 xMin, float32 xMax, float32 yMin, float32 yMax, float32 zMin, float32 zMax);
		void	setOrthographic(int orthoWidth, int orthoHeigth);

		int	getOrtoScreen_X(int x) const;
		int	getOrtoScreen_Y(int y) const;

		void	getMatrix(CMatrix4f32& dst) const;
		e_PerspectiveType getType() const;
		const CMatrix4f32* getProjection() const;
	};
}