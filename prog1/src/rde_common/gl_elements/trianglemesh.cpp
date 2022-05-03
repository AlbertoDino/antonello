#include <rdecommon.h>
#include "vertex.h"
#include "vertexindexbuffer.h"
#include "..\math\functions.h"
#include "..\math\vector.h"
#include "trianglemesh.h"

namespace oglElements {



	TriangleMesh::TriangleMesh() : indexCount(0)
	{
	}

	void TriangleMesh::addVertex(const glm::vec3& v, const glm::vec3& n, const glm::vec2& t) {
		Vertex vertex;
		vertex.Pos = v;
		vertex.Normal = n;
		vertex.UV = t;

		vertices.push_back(vertex);
	}

	void TriangleMesh::addIndex(GLuint i1, GLuint i2, GLuint i3)
	{
		indexes.push_back(i1);
		indexes.push_back(i2);
		indexes.push_back(i3);
	}

	void TriangleMesh::computeTangents()
	{
		for (unsigned int i = 0; i < indexes.size(); i += 3) {
			Vertex& v0 = vertices[indexes[i]];
			Vertex& v1 = vertices[indexes[i + 1]];
			Vertex& v2 = vertices[indexes[i + 2]];

			glm::vec3 Edge1 = v1.Pos - v0.Pos;
			glm::vec3 Edge2 = v2.Pos - v0.Pos;

			float DeltaU1 = v1.UV.x - v0.UV.x;
			float DeltaV1 = v1.UV.y - v0.UV.y;
			float DeltaU2 = v2.UV.x - v0.UV.x;
			float DeltaV2 = v2.UV.y - v0.UV.y;

			float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

			glm::vec3 Tangent, Bitangent;

			Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
			Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
			Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

			Bitangent.x = f * (-DeltaU2 * Edge1.x + DeltaU1 * Edge2.x);
			Bitangent.y = f * (-DeltaU2 * Edge1.y + DeltaU1 * Edge2.y);
			Bitangent.z = f * (-DeltaU2 * Edge1.z + DeltaU1 * Edge2.z);

			v0.Tangent += Tangent;
			v1.Tangent += Tangent;
			v2.Tangent += Tangent;
		}

		// See "Going Further"
		for (unsigned int i = 0; i < vertices.size(); i ++)
		{
			/*
			glm::vec3& n = vertices[i].Normal;
			glm::vec3& t = vertices[i].Tangent;
			glm::vec3& b = vertices[i].BitTangent;

			// Gram-Schmidt orthogonalize
			t = glm::normalize(t - n * glm::dot(n, t));

			// Calculate handedness
			if (glm::dot(glm::cross(n, t), b) < 0.0f) {
				t = t * -1.0f;
			}
			*/
			glm::normalize(vertices[i].Tangent);
		}
	}

	void TriangleMesh::create(gl_vertexObject* vertexObject, GLenum drawmode)
	{
		vertexObject->drawMode = drawmode;
		vertexObject->count = indexes.size();

		glGenVertexArrays(1, &vertexObject->VAO);
		glBindVertexArray(vertexObject->VAO);

		// VBO
		glGenBuffers(1, &vertexObject->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexObject->VBO);
		glBufferData(GL_ARRAY_BUFFER
			, sizeof(Vertex) * vertices.size()
			, vertices.data()
			, GL_STATIC_DRAW);

		// IBO
		glGenBuffers(1, &vertexObject->IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexObject->IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER
			, sizeof(GLuint) * indexes.size()
			, indexes.data()
			, GL_STATIC_DRAW);

		//Shader Attribute location
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Pos));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, BitTangent));

		glBindVertexArray(0);
	}

}
