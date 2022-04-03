#include <rdecommon.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "shader.h"
#include "renderingelement.h"
#include "vertex.h"
#include "vertexindexbuffer.h"
#include "drawobjects.h"
#include "mesh.h"

namespace oglElements {

    Mesh::~Mesh()
    {
    }

    bool Mesh::loadFromFile(const std::string& filepath)
    {
        const uint32_t cMeshImportFlags =
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_SortByPType |
            aiProcess_GenSmoothNormals |
            aiProcess_GenUVCoords |
            aiProcess_OptimizeMeshes |
            aiProcess_ValidateDataStructure;

        Assimp::Importer Importer;

        const aiScene* pScene = Importer.ReadFile(filepath.c_str(),
            cMeshImportFlags);

        if (pScene && pScene->HasMeshes())
        {
            VertexIndices.clear();
            Vertices.clear();

            auto* mesh = pScene->mMeshes[0];

            for (uint32_t i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex vh;
                vh.Pos = { mesh->mVertices[i].x, mesh->mVertices[i].y ,mesh->mVertices[i].z };
                vh.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y ,mesh->mNormals[i].z };
                if (mesh->HasTextureCoords(0)) {
                    aiVector3D uv = mesh->mTextureCoords[0][i];
                    vh.UV = { uv.x,uv.y };
                }

                add_vertex(vh);
            }

            for (size_t i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];

                for (size_t j = 0; j < face.mNumIndices; j++)
                    add_vertex_index(face.mIndices[j]);
            }

            return true;
        }
        return false;
    }

    void Mesh::add_vertex(const Vertex& vertex)
    {
        Vertices.push_back(vertex);
    }

    void Mesh::add_vertex_index(unsigned int vertex_idx)
    {
        VertexIndices.push_back(vertex_idx);
    }

    std::vector<unsigned int> Mesh::get_vertex_indices()
    {
        return std::vector<unsigned int>();
    }

    void Mesh::create(DrawElementObject* pElement)
    {
        vertexBuffer.create_buffers(&pElement->vertexObject, GL_TRIANGLES, Vertices, VertexIndices);
    }

    void Mesh::create(DrawElementTextured* pElement)
    {
        vertexBuffer.create_buffers(&pElement->vertexObject, GL_TRIANGLES, Vertices, VertexIndices);
    }

}