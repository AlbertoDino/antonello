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

		mesher.vertex(CVector3f{ fRadius, fRadius, fRadius },
			CVector3f{ 0.0f, fRadius, 0.0f },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ fRadius, fRadius, -fRadius },
			CVector3f{ 0.0f, fRadius, 0.0f },
			CVector2f{ fRadius, 0.0f });

		mesher.vertex(CVector3f{ -fRadius, fRadius, -fRadius },
			CVector3f{ 0.0f, fRadius, 0.0f },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ fRadius, fRadius, fRadius },
			CVector3f{ 0.0f, fRadius, 0.0f },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ -fRadius, fRadius, -fRadius },
			CVector3f{ 0.0f, fRadius, 0.0f },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ fRadius, fRadius, fRadius },
			CVector3f{ 0.0f, fRadius, 0.0f },
			CVector2f{ 0.0f, fRadius });

		////////////////////////////////////////////
		// Bottom of cube

		mesher.vertex(CVector3f{ -fRadius, -fRadius, -fRadius },
			CVector3f{ 0.0f, -fRadius, 0.0f },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ fRadius, -fRadius, -fRadius },
			CVector3f{ 0.0f, -fRadius, 0.0f },
			CVector2f{ fRadius, 0.0f });

		mesher.vertex(CVector3f{ fRadius, -fRadius, fRadius },
			CVector3f{ 0.0f, -fRadius, 0.0f },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ -fRadius, -fRadius, fRadius },
			CVector3f{ 0.0f, -fRadius, 0.0f },
			CVector2f{ 0.0f, fRadius });

		mesher.vertex(CVector3f{ -fRadius, -fRadius, -fRadius },
			CVector3f{ 0.0f, -fRadius, 0.0f },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ fRadius, -fRadius, fRadius },
			CVector3f{ 0.0f, -fRadius, 0.0f },
			CVector2f{ fRadius, fRadius });

		///////////////////////////////////////////
		// Left side of cube

		mesher.vertex(CVector3f{ -fRadius, fRadius, fRadius },
			CVector3f{ -fRadius, 0.0f, 0.0f },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ -fRadius, fRadius, -fRadius },
			CVector3f{ -fRadius, 0.0f, 0.0f },
			CVector2f{ fRadius, 0.0f });

		mesher.vertex(CVector3f{ -fRadius, -fRadius, -fRadius },
			CVector3f{ -fRadius, 0.0f, 0.0f },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ -fRadius, fRadius, fRadius },
			CVector3f{ -fRadius, 0.0f, 0.0f },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ -fRadius, -fRadius, -fRadius },
			CVector3f{ -fRadius, 0.0f, 0.0f },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ -fRadius, -fRadius, fRadius },
			CVector3f{ -fRadius, 0.0f, 0.0f },
			CVector2f{ 0.0f, fRadius });

		// Right side of cube
		mesher.vertex(CVector3f{ fRadius, -fRadius, -fRadius },
			CVector3f{ fRadius, 0.0f, 0.0f },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ fRadius, fRadius, -fRadius },
			CVector3f{ fRadius, 0.0f, 0.0f },
			CVector2f{ fRadius, 0.0f });

		mesher.vertex(CVector3f{ fRadius, fRadius, fRadius },
			CVector3f{ fRadius, 0.0f, 0.0f },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ fRadius, fRadius, fRadius },
			CVector3f{ fRadius, 0.0f, 0.0f },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ fRadius, -fRadius, fRadius },
			CVector3f{ fRadius, 0.0f, 0.0f },
			CVector2f{ 0.0f, fRadius });

		mesher.vertex(CVector3f{ fRadius, -fRadius, -fRadius },
			CVector3f{ fRadius, 0.0f, 0.0f },
			CVector2f{ 0.0f, 0.0f });

		// Front and Back
		// Front
		mesher.vertex(CVector3f{ fRadius, -fRadius, fRadius },
			CVector3f{ 0.0f, 0.0f, fRadius },
			CVector2f{ fRadius, 0.0f });

		mesher.vertex(CVector3f{ fRadius, fRadius, fRadius },
			CVector3f{ 0.0f, 0.0f, fRadius },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ -fRadius, fRadius, fRadius },
			CVector3f{ 0.0f, 0.0f, fRadius },
			CVector2f{ 0.0f, fRadius });

		mesher.vertex(CVector3f{ -fRadius, fRadius, fRadius },
			CVector3f{ 0.0f, 0.0f, fRadius },
			CVector2f{ 0.0f, fRadius });

		mesher.vertex(CVector3f{ -fRadius, -fRadius, fRadius },
			CVector3f{ 0.0f, 0.0f, fRadius },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ fRadius, -fRadius, fRadius },
			CVector3f{ 0.0f, 0.0f, fRadius },
			CVector2f{ fRadius, 0.0f });

		// Back
		mesher.vertex(CVector3f{ fRadius, -fRadius, -fRadius },
			CVector3f{ 0.0f, 0.0f, -fRadius },
			CVector2f{ fRadius, 0.0f });

		mesher.vertex(CVector3f{ -fRadius, -fRadius, -fRadius },
			CVector3f{ 0.0f, 0.0f, -fRadius },
			CVector2f{ 0.0f, 0.0f });

		mesher.vertex(CVector3f{ -fRadius, fRadius, -fRadius },
			CVector3f{ 0.0f, 0.0f,  -fRadius },
			CVector2f{ 0.0f, fRadius });

		mesher.vertex(CVector3f{ -fRadius, fRadius, fRadius },
			CVector3f{ 0.0f, 0.0f,  -fRadius },
			CVector2f{ 0.0f, fRadius });

		mesher.vertex(CVector3f{ fRadius, fRadius, -fRadius },
			CVector3f{ 0.0f, 0.0f,  -fRadius },
			CVector2f{ fRadius, fRadius });

		mesher.vertex(CVector3f{ fRadius, -fRadius, -fRadius },
			CVector3f{ 0.0f, 0.0f,  -fRadius },
			CVector2f{ fRadius, 0.0f });


		mesher.create(cube, GL_TRIANGLES);

		return cube;
	}

	oglElements::DrawArrayObjectWithTexture* Rectangle::rectangle = 0;

	oglElements::DrawArrayObjectWithTexture* Rectangle::getModel()
	{
		if (rectangle != 0) return rectangle;

		rectangle = new oglElements::DrawArrayObjectWithTexture();

		rectangle->vertexObject.drawMode = GL_TRIANGLES;
		rectangle->vertexObject.count = 6;

		float32 fRadius = 1.0f;

		float32 vVerts[] = {
			fRadius, 0, 0,
			fRadius, fRadius, 0,
			0, fRadius, 0,
			0, fRadius, 0,
			0, 0, 0,
			fRadius,0, 0 };

		float32 vNormals[] = {
			0.0f, 0.0f, fRadius,
			0.0f, 0.0f, fRadius,
			0.0f, 0.0f, fRadius,
			0.0f, 0.0f, fRadius,
			0.0f, 0.0f, fRadius,
			0.0f, 0.0f, fRadius };


		glm::vec4 colors[6] = {
			glm::vec4(1,1,1,1),
			glm::vec4(1,1,1,1),
			glm::vec4(1,1,1,1),
			glm::vec4(1,1,1,1),
			glm::vec4(1,1,1,1),
			glm::vec4(1,1,1,1)
		};

		float32 vTexts[] = { 1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f };

		glGenVertexArrays(1, &rectangle->vertexObject.VAO);
		glGenBuffers(1, &rectangle->vertexObject.VBO);
		//glGenBuffers(1, &draw->vertexObject.CBO);
		glGenBuffers(1, &rectangle->vertexObject.UVO);


		glBindVertexArray(rectangle->vertexObject.VAO);

		// for vertex buffer ..
		glBindBuffer(GL_ARRAY_BUFFER, rectangle->vertexObject.VBO);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vector3f), &vVerts[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);


		// for uv buffer ..
		glBindBuffer(GL_ARRAY_BUFFER, rectangle->vertexObject.UVO);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vector2f), &vTexts[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, NULL);


		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return rectangle;
	}

}

