// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "AlgorithmsStrings.h"
#include "AlgorithmsVectors.h"
#include "Math3D.h"
#include "Mesh.h"

namespace Forradia
{

    class Model3D : public AlgorithmsVectors, AlgorithmsStrings
    {
    public:
        Model3D() {}

        ~Model3D();

        bool LoadFile(std::string path);

        std::vector<Mesh> loadedMeshes;
        std::vector<Vertex> loadedVertices;
        std::vector<unsigned int> loadedIndices;
        std::vector<Material> loadedMaterials;

    private:
        void GenVerticesFromRawOBJ(std::vector<Vertex>* oVerts,
            const std::vector<Vector3>& iPositions,
            const std::vector<Vector2>& iTCoords,
            const std::vector<Vector3>& iNormals,
            std::string icurline);

        void VertexTriangluation(std::vector<unsigned int>* oIndices,
            const std::vector<Vertex>& iVerts);

        bool LoadMaterials(std::string path);

        template <class T>
        const T& GetElement(const std::vector<T>& elements,
            const std::string& index);

        Math3D math3D;
    };

    template <class T>
    const T& Model3D::GetElement(const std::vector<T>& elements,
        const std::string& index)
    {
        unsigned int idx = std::stoi(index);

        if (idx < 0)
            idx = elements.size() + idx;
        else
            idx--;

        return elements[idx];
    }

}