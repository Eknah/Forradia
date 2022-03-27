
#pragma once
#include "F_Vertex.h"
#include "F_Material.h"

namespace Forradia
{

class F_Mesh
{

public:

    F_Mesh() {}
    F_Mesh(std::vector<F_Vertex>& vertices, std::vector<unsigned int>& indices) : Vertices(vertices), Indices(indices) {}

    std::string MeshName;
    std::vector<F_Vertex> Vertices;
    std::vector<unsigned int> Indices;
    F_Material MeshMaterial;
};

}
