#pragma once

namespace oglElements {

	class Vertex {
	public:
		Vertex() : Pos(), Normal() {}

		Vertex(const glm::vec3& pos, const glm::vec3& normal)
			: Pos(pos), Normal(normal)
		{
		}

		Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2 &uv)
			: Pos(pos), Normal(normal), UV (uv)
		{
		}

		~Vertex() = default;

		glm::vec3 Pos;
		glm::vec3 Normal;
		glm::vec2 UV;
	};

}