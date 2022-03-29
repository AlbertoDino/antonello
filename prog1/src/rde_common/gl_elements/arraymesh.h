#pragma once

namespace oglElements {


	class ArrayMesh {
	public:
		ArrayMesh();
		~ArrayMesh();

		void vertex3f(const float32 x, const float32 y, const float32 z);

		void create(DrawArrayObject* pElement);


		//glm::vec3 Color = { 1.0f, 0.0f, 0.0f };
		//float Roughness = 0.2f;
		//float Metallic = 0.1f;

	private:
		VertexIndexBuffer vertexBuffer;
		std::vector<Vertex> Vertices;

	};

}