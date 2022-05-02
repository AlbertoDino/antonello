#include <rde_common/lib.h>
#include "builtmodels.h"

using namespace oglElements;

namespace rex {

	oglElements::gl_vertexObject Cube::cube;

	const oglElements::gl_vertexObject& Cube::getModel()
	{
		if (cube.VAO != 0) return cube;

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


		mesher.create(&cube, GL_TRIANGLES);

		return cube;
	}

	oglElements::gl_vertexObject Rectangle::rectangle;

	const oglElements::gl_vertexObject& Rectangle::getModel()
	{
		if (rectangle.VAO != 0) return rectangle;

		rectangle.drawMode = GL_TRIANGLES;
		rectangle.count = 6;

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

		float32 vTexts[] = { 1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f };

		glGenVertexArrays(1, &rectangle.VAO);
		glGenBuffers(1, &rectangle.VBO);
		//glGenBuffers(1, &draw->vertexObject.CBO);
		glGenBuffers(1, &rectangle.UVO);


		glBindVertexArray(rectangle.VAO);

		// for add buffer ..
		glBindBuffer(GL_ARRAY_BUFFER, rectangle.VBO);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vector3f), &vVerts[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);

		// for uv buffer ..
		glBindBuffer(GL_ARRAY_BUFFER, rectangle.UVO);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vector2f), &vTexts[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, NULL);


		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return rectangle;
	}

	oglElements::gl_vertexObject Sphere::sphere;



	const oglElements::gl_vertexObject& Sphere::getModel(float32 fRadius, int32 sectors, int32 stacks)
	{
		if (sphere.VAO != 0) return sphere;

		const float PI = acos(-1);

		float32 x, y, z, xy;							   // vertex position
		float32 nx, ny, nz, lengthInv = 1.0f / fRadius;    // normal
		float32 s, t;

		float32 sectorStep = 2 * PI / sectors;
		float32 stackStep = PI / stacks;
		float32 sectorAngle, stackAngle;

		oglElements::TriangleMesh mesh;
		for (int i = 0; i <= stacks; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
			xy = fRadius * cosf(stackAngle);             // r * cos(u)
			z = fRadius * sinf(stackAngle);              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for (int j = 0; j <= sectors; ++j)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
				glm::vec3 vertex = { x, y, z };

				// normalized vertex normal
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				glm::vec3 normal = { nx, ny, nz };

				// vertex tex coord between [0, 1]
				s = (float)j / sectors;
				t = (float)i / stacks;
				glm::vec2 uv = { s, t };

				mesh.addVertex(vertex, normal, uv);
				
			}
		}

		

		// indices
		//  k1--k1+1
		//  |  / |
		//  | /  |
		//  k2--k2+1
		unsigned int k1, k2;
		for (int i = 0; i < stacks; ++i)
		{
			k1 = i * (sectors + 1);     // beginning of current stack
			k2 = k1 + sectors + 1;      // beginning of next stack

			for (int j = 0; j < sectors; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding 1st and last stacks
				if (i != 0)
				{
					mesh.addIndex(k1, k2, k1 + 1);   // k1---k2---k1+1
				}

				if (i != (stacks - 1))
				{
					mesh.addIndex(k1 + 1, k2, k2 + 1); // k1+1---k2---k2+1
				}
			}
		}

		mesh.computeTangents();
		mesh.create(&sphere, GL_TRIANGLES);
		return sphere;
	
	}


}

