#pragma once
#include "drawobjects.h"

namespace oglElements {

	class  Mesh {
	public:
        Mesh() = default;

        virtual ~Mesh();

        bool loadFromFile(const std::string & filepath);

        void add_vertex(const Vertex& vertex);

        void add_vertex_index(unsigned int vertex_idx);

        std::vector<unsigned int> get_vertex_indices();

        void create(DrawElementObject* pElement);

	private:

		VertexIndexBuffer vertexBuffer;
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> VertexIndices;

	};


}
