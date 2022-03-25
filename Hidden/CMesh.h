#pragma once
#include "CVertex.h"
#include "CMaterial.h"
namespace Forradia
{
class CMesh
{

public:
    CMesh() {}
    CMesh(std::vector<CVertex>& vertices, std::vector<unsigned int>& indices) : Vertices(vertices), Indices(indices) {}

    std::string MeshName;
    std::vector<CVertex> Vertices;
    std::vector<unsigned int> Indices;
    CMaterial MeshMaterial;
};
}
