#include <rde_common/lib.h>
#include "builtmodels.h"

using namespace oglElements;

namespace rex {

	oglElements::DrawArrayObject* Cube::cube = 0; 

	oglElements::DrawArrayObject* Cube::getModel()
	{
		if (cube != 0) return cube;

		cube = new oglElements::DrawArrayObject();

		ArrayMesh mesher;

		float32 fRadius = 1.0f;
		/////////////////////////////////////////////
		// Top of cube

		mesher.vertex(	CVector3f{ fRadius, fRadius, fRadius },
						CVector3f{ 0.0f, fRadius, 0.0f },
						CVector2f{ fRadius, fRadius } );

		mesher.vertex(	CVector3f{ fRadius, fRadius, -fRadius },
						CVector3f{ 0.0f, fRadius, 0.0f },
						CVector2f{ fRadius, 0.0f });

		mesher.vertex(	CVector3f{ -fRadius, fRadius, -fRadius },
						CVector3f{ 0.0f, fRadius, 0.0f },
						CVector2f{ 0.0f, 0.0f });

		mesher.vertex(	CVector3f{ fRadius, fRadius, fRadius },
						CVector3f{ 0.0f, fRadius, 0.0f },
						CVector2f{ fRadius, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, fRadius, -fRadius },
						CVector3f{ 0.0f, fRadius, 0.0f },
						CVector2f{ 0.0f, 0.0f });

		mesher.vertex(	CVector3f{ fRadius, fRadius, fRadius },
						CVector3f{ 0.0f, fRadius, 0.0f },
						CVector2f{ 0.0f, fRadius });

		////////////////////////////////////////////
		// Bottom of cube

		mesher.vertex(	CVector3f{ -fRadius, -fRadius, -fRadius },
						CVector3f{ 0.0f, -fRadius, 0.0f },
						CVector2f{ 0.0f, 0.0f });
		
		mesher.vertex(	CVector3f{ fRadius, -fRadius, -fRadius },
						CVector3f{ 0.0f, -fRadius, 0.0f },
						CVector2f{ fRadius, 0.0f });

		mesher.vertex(	CVector3f{ fRadius, -fRadius, fRadius },
						CVector3f{ 0.0f, -fRadius, 0.0f },
						CVector2f{ fRadius, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, -fRadius, fRadius },
						CVector3f{ 0.0f, -fRadius, 0.0f },
						CVector2f{ 0.0f, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, -fRadius, -fRadius },
						CVector3f{ 0.0f, -fRadius, 0.0f },
						CVector2f{ 0.0f, 0.0f });

		mesher.vertex(	CVector3f{ fRadius, -fRadius, fRadius },
						CVector3f{ 0.0f, -fRadius, 0.0f },
						CVector2f{ fRadius, fRadius });

		///////////////////////////////////////////
		// Left side of cube

		mesher.vertex(	CVector3f{ -fRadius, fRadius, fRadius },
						CVector3f{ -fRadius, 0.0f, 0.0f },
						CVector2f{ fRadius, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, fRadius, -fRadius },
						CVector3f{ -fRadius, 0.0f, 0.0f },
						CVector2f{ fRadius, 0.0f });

		mesher.vertex(	CVector3f{ -fRadius, -fRadius, -fRadius },
						CVector3f{ -fRadius, 0.0f, 0.0f },
						CVector2f{ 0.0f, 0.0f });

		mesher.vertex(	CVector3f{ -fRadius, fRadius, fRadius },
						CVector3f{ -fRadius, 0.0f, 0.0f },
						CVector2f{ fRadius, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, -fRadius, -fRadius },
						CVector3f{ -fRadius, 0.0f, 0.0f },
						CVector2f{ 0.0f, 0.0f });

		mesher.vertex(	CVector3f{ -fRadius, -fRadius, fRadius },
						CVector3f{ -fRadius, 0.0f, 0.0f },
						CVector2f{ 0.0f, fRadius });

		// Right side of cube
		mesher.vertex(	CVector3f{ fRadius, -fRadius, -fRadius },
						CVector3f{ fRadius, 0.0f, 0.0f },
						CVector2f{ 0.0f, 0.0f });

		mesher.vertex(	CVector3f{ fRadius, fRadius, -fRadius },
						CVector3f{ fRadius, 0.0f, 0.0f },
						CVector2f{ fRadius, 0.0f });

		mesher.vertex(	CVector3f{ fRadius, fRadius, fRadius },
						CVector3f{ fRadius, 0.0f, 0.0f },
						CVector2f{ fRadius, fRadius });

		mesher.vertex(	CVector3f{ fRadius, fRadius, fRadius },
						CVector3f{ fRadius, 0.0f, 0.0f },
						CVector2f{ fRadius, fRadius });

		mesher.vertex(	CVector3f{ fRadius, -fRadius, fRadius },
						CVector3f{ fRadius, 0.0f, 0.0f },
						CVector2f{ 0.0f, fRadius });

		mesher.vertex(	CVector3f{ fRadius, -fRadius, -fRadius },
						CVector3f{ fRadius, 0.0f, 0.0f },
						CVector2f{ 0.0f, 0.0f });

		// Front and Back
		// Front
		mesher.vertex(	CVector3f{ fRadius, -fRadius, fRadius },
						CVector3f{ 0.0f, 0.0f, fRadius },
						CVector2f{ fRadius, 0.0f });

		mesher.vertex(	CVector3f{ fRadius, fRadius, fRadius },
						CVector3f{ 0.0f, 0.0f, fRadius },
						CVector2f{ fRadius, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, fRadius, fRadius },
						CVector3f{ 0.0f, 0.0f, fRadius },
						CVector2f{ 0.0f, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, fRadius, fRadius },
						CVector3f{ 0.0f, 0.0f, fRadius },
						CVector2f{ 0.0f, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, -fRadius, fRadius },
						CVector3f{ 0.0f, 0.0f, fRadius },
						CVector2f{ 0.0f, 0.0f });

		mesher.vertex(	CVector3f{ fRadius, -fRadius, fRadius },
						CVector3f{ 0.0f, 0.0f, fRadius },
						CVector2f{ fRadius, 0.0f });

		// Back
		mesher.vertex(	CVector3f{ fRadius, -fRadius, -fRadius },
						CVector3f{ 0.0f, 0.0f, -fRadius },
						CVector2f{ fRadius, 0.0f });

		mesher.vertex(	CVector3f{ -fRadius, -fRadius, -fRadius },
						CVector3f{ 0.0f, 0.0f, -fRadius },
						CVector2f{ 0.0f, 0.0f });

		mesher.vertex(	CVector3f{ -fRadius, fRadius, -fRadius },
						CVector3f{ 0.0f, 0.0f,  -fRadius },
						CVector2f{ 0.0f, fRadius });

		mesher.vertex(	CVector3f{ -fRadius, fRadius, fRadius },
						CVector3f{ 0.0f, 0.0f,  -fRadius },
						CVector2f{ 0.0f, fRadius });

		mesher.vertex(	CVector3f{ fRadius, fRadius, -fRadius },
						CVector3f{ 0.0f, 0.0f,  -fRadius },
						CVector2f{ fRadius, fRadius });

		mesher.vertex(	CVector3f{ fRadius, -fRadius, -fRadius },
						CVector3f{ 0.0f, 0.0f,  -fRadius },
						CVector2f{ fRadius, 0.0f });

		
		mesher.create(cube,GL_TRIANGLES);

		return cube;
	}
}

