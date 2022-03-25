#pragma once
namespace Forradia
{
class CMesh
{

public:
    CMesh() {}
    CMesh(std::vector<CVertex>& vertices, std::vector<unsigned int>& indices) : Vertices(vertices), Indices(indices) {}

    String MeshName;
    List<CVertex> Vertices;
    List<unsigned int> Indices;
    CMaterial MeshMaterial;
};
}
