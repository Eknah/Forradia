
#pragma once
#include "cVertex.h"
#include "cMaterial.h"

namespace Forradia
{

class cMesh
{

public:

    cMesh() {}
    cMesh(std::vector<cVertex>& vertices, std::vector<unsigned int>& indices) : Vertices(vertices), Indices(indices) {}

    std::string MeshName;
    std::vector<cVertex> Vertices;
    std::vector<unsigned int> Indices;
    cMaterial MeshMaterial;
};

}
