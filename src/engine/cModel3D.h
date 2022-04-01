// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "cAlgorithmsStrings.h"
#include "cAlgorithmsVectors.h"
#include "cMath3D.h"
#include "cMesh.h"

namespace Forradia {

class cModel3D : public cAlgorithmsVectors, cAlgorithmsStrings {
 public:
  cModel3D() {}

  ~cModel3D();

  bool LoadFile(std::string Path);

  std::vector<cMesh> LoadedMeshes;
  std::vector<cVertex> LoadedVertices;
  std::vector<unsigned int> LoadedIndices;
  std::vector<cMaterial> LoadedMaterials;

 private:
  void GenVerticesFromRawOBJ(std::vector<cVertex> *oVerts,
                                    const std::vector<cVector3> &iPositions,
                                    const std::vector<cVector2> &iTCoords,
                                    const std::vector<cVector3> &iNormals,
                                    std::string icurline);

  void VertexTriangluation(std::vector<unsigned int> *oIndices,
                                  const std::vector<cVertex> &iVerts);

  bool LoadMaterials(std::string path);

  template <class T>
  const T &GetElement(const std::vector<T> &elements,
                             const std::string &index);

  cMath3D Math3D;
};

template <class T>
const T &cModel3D::GetElement(const std::vector<T> &elements,
                           const std::string &index) {
  unsigned int idx = std::stoi(index);

  if (idx < 0)
    idx = elements.size() + idx;
  else
    idx--;

  return elements[idx];
}

}  // namespace Forradia
