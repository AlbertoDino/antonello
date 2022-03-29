#pragma once

namespace oglElements {

	class Vertex {
	public:
		Vertex() : Pos(), Normal() {}

		Vertex(const glm::vec3& pos, const glm::vec3& normal)
			: Pos(pos), Normal(normal)
		{
		}

		~Vertex() = default;

		glm::vec3 Pos;
		glm::vec3 Normal;
	};

}