// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#pragma once
#include <string>
#include <vector>
#include "CommonExternal.h"
#include "cAlgorithmsStrings.h"
#include "cAlgorithmsVectors.h"
#include "cMath3D.h"
#include "cMesh.h"

namespace Forradia {

class cModel3D : public cVectorAlgorithms, cAlgorithmsStrings {
 public:
  cModel3D() {}

  ~cModel3D() { LoadedMeshes.clear(); }

  inline bool LoadFile(std::string Path) {
    if (Path.substr(Path.size() - 4, 4) != ".obj")
      return false;

    std::ifstream file(Path);

    if (!file.is_open())
      return false;

    LoadedMeshes.clear();
    LoadedVertices.clear();
    LoadedIndices.clear();

    std::vector<cVector3> Positions;
    std::vector<cVector2> TCoords;
    std::vector<cVector3> Normals;
    std::vector<cVertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<std::string> MeshMatNames;
    bool listening = false;
    std::string meshname;
    cMesh tempMesh;
    std::string curline;

    while (std::getline(file, curline)) {
      if (FirstToken(curline) == "o" || FirstToken(curline) == "g" ||
          curline[0] == 'g') {
        if (!listening) {
          listening = true;

          if (FirstToken(curline) == "o" || FirstToken(curline) == "g")
            meshname = Tail(curline);
          else
            meshname = "unnamed";
        } else {
          if (!Indices.empty() && !Vertices.empty()) {
            tempMesh = cMesh(Vertices, Indices);
            tempMesh.MeshName = meshname;
            LoadedMeshes.push_back(tempMesh);
            Vertices.clear();
            Indices.clear();
            meshname.clear();
            meshname = Tail(curline);
          } else {
            if (FirstToken(curline) == "o" || FirstToken(curline) == "g")
              meshname = Tail(curline);
            else
              meshname = "unnamed";
          }
        }
      }

      if (FirstToken(curline) == "v") {
        std::vector<std::string> spos;
        cVector3 vpos;
        Split(Tail(curline), &spos, " ");
        vpos.X = std::stof(spos[0]);
        vpos.Y = std::stof(spos[1]);
        vpos.Z = std::stof(spos[2]);
        Positions.push_back(vpos);
      }

      if (FirstToken(curline) == "vt") {
        std::vector<std::string> stex;
        cVector2 vtex;
        Split(Tail(curline), &stex, " ");
        vtex.X = std::stof(stex[0]);
        vtex.Y = std::stof(stex[1]);
        TCoords.push_back(vtex);
      }

      if (FirstToken(curline) == "vn") {
        std::vector<std::string> snor;
        cVector3 vnor;
        Split(Tail(curline), &snor, " ");
        vnor.X = std::stof(snor[0]);
        vnor.Y = std::stof(snor[1]);
        vnor.Z = std::stof(snor[2]);
        Normals.push_back(vnor);
      }

      if (FirstToken(curline) == "f") {
        std::vector<cVertex> vVerts;
        GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);

        for (int i = 0; i < int(vVerts.size()); i++) {
          Vertices.push_back(vVerts[i]);
          LoadedVertices.push_back(vVerts[i]);
        }

        std::vector<unsigned int> iIndices;
        VertexTriangluation(iIndices, vVerts);

        for (int i = 0; i < int(iIndices.size()); i++) {
          unsigned int indnum =
              (unsigned int)((Vertices.size()) - vVerts.size()) + iIndices[i];
          Indices.push_back(indnum);
          indnum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) +
                   iIndices[i];
          LoadedIndices.push_back(indnum);
        }
      }

      if (FirstToken(curline) == "usemtl") {
        MeshMatNames.push_back(Tail(curline));

        if (!Indices.empty() && !Vertices.empty()) {
          tempMesh = cMesh(Vertices, Indices);
          tempMesh.MeshName = meshname;
          int i = 2;

          while (1) {
            tempMesh.MeshName = meshname + "_" + std::to_string(i);

            for (auto &m : LoadedMeshes)
              if (m.MeshName == tempMesh.MeshName)
                continue;
            break;
          }

          LoadedMeshes.push_back(tempMesh);
          Vertices.clear();
          Indices.clear();
        }
      }

      if (FirstToken(curline) == "mtllib") {
        std::vector<std::string> temp;
        Split(Path, &temp, "/");
        std::string pathtomat = Path.substr(0, Path.length() - 4) + ".mtl";
        LoadMaterials(pathtomat);
      }
    }

    if (!Indices.empty() && !Vertices.empty()) {
      tempMesh = cMesh(Vertices, Indices);
      tempMesh.MeshName = meshname;
      LoadedMeshes.push_back(tempMesh);
    }

    file.close();

    for (unsigned int i = 0; i < MeshMatNames.size(); i++) {
      std::string matname = MeshMatNames[i];

      for (unsigned int j = 0; j < LoadedMaterials.size(); j++) {
        if (LoadedMaterials[j].Name == matname) {
          LoadedMeshes[i].MeshMaterial = LoadedMaterials[j];
          break;
        }
      }
    }

    if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
      return false;
    else
      return true;
  }

  std::vector<cMesh> LoadedMeshes;
  std::vector<cVertex> LoadedVertices;
  std::vector<unsigned int> LoadedIndices;
  std::vector<cMaterial> LoadedMaterials;

 private:
  inline void GenVerticesFromRawOBJ(std::vector<cVertex> &oVerts,
                                    const std::vector<cVector3> &iPositions,
                                    const std::vector<cVector2> &iTCoords,
                                    const std::vector<cVector3> &iNormals,
                                    std::string icurline) {
    std::vector<std::string> sface, svert;
    cVertex vVert;
    Split(Tail(icurline), &sface, " ");
    bool noNormal = false;

    for (int i = 0; i < int(sface.size()); i++) {
      int vtype;

      Split(sface[i], &svert, "/");

      if (svert.size() == 1)
        vtype = 1;

      if (svert.size() == 2)
        vtype = 2;

      if (svert.size() == 3) {
        if (svert[1] != "")
          vtype = 4;
        else
          vtype = 3;
      }

      switch (vtype) {
      case 1: {
        vVert.Position = GetElement(iPositions, svert[0]);
        vVert.TextureCoordinate = cVector2(0, 0);
        noNormal = true;
        oVerts.push_back(vVert);

        break;
      }
      case 2: {
        vVert.Position = GetElement(iPositions, svert[0]);
        vVert.TextureCoordinate = GetElement(iTCoords, svert[1]);
        noNormal = true;
        oVerts.push_back(vVert);

        break;
      }
      case 3: {
        vVert.Position = GetElement(iPositions, svert[0]);
        vVert.TextureCoordinate = cVector2(0, 0);
        vVert.Normal = GetElement(iNormals, svert[2]);
        oVerts.push_back(vVert);

        break;
      }
      case 4: {
        vVert.Position = GetElement(iPositions, svert[0]);
        vVert.TextureCoordinate = GetElement(iTCoords, svert[1]);
        vVert.Normal = GetElement(iNormals, svert[2]);
        oVerts.push_back(vVert);

        break;
      }
      default: {
        break;
      }
      }
    }

    if (noNormal) {
      cVector3 A = oVerts[0].Position - oVerts[1].Position;
      cVector3 B = oVerts[2].Position - oVerts[1].Position;

      cVector3 Normal = Math3D.Cross(A, B);

      for (int i = 0; i < int(oVerts.size()); i++)
        oVerts[i].Normal = Normal;
    }
  }
  inline void VertexTriangluation(std::vector<unsigned int> &oIndices,
                                  const std::vector<cVertex> &iVerts) {
    if (iVerts.size() < 3)
      return;

    if (iVerts.size() == 3) {
      oIndices.push_back(0);
      oIndices.push_back(1);
      oIndices.push_back(2);

      return;
    }

    std::vector<cVertex> tVerts = iVerts;

    while (true) {
      for (int i = 0; i < int(tVerts.size()); i++) {
        cVertex pPrev;

        if (i == 0)
          pPrev = tVerts[tVerts.size() - 1];
        else
          pPrev = tVerts[i - 1];

        cVertex pCur = tVerts[i];
        cVertex pNext;

        if (i == tVerts.size() - 1)
          pNext = tVerts[0];
        else
          pNext = tVerts[i + 1];

        if (tVerts.size() == 3) {
          for (int j = 0; j < int(tVerts.size()); j++) {
            if (iVerts[j].Position == pCur.Position)
              oIndices.push_back(j);
            if (iVerts[j].Position == pPrev.Position)
              oIndices.push_back(j);
            if (iVerts[j].Position == pNext.Position)
              oIndices.push_back(j);
          }

          tVerts.clear();

          break;
        }
        if (tVerts.size() == 4) {
          for (int j = 0; j < int(iVerts.size()); j++) {
            if (iVerts[j].Position == pCur.Position)
              oIndices.push_back(j);
            if (iVerts[j].Position == pPrev.Position)
              oIndices.push_back(j);
            if (iVerts[j].Position == pNext.Position)
              oIndices.push_back(j);
          }

          cVector3 tempVec;
          for (int j = 0; j < int(tVerts.size()); j++) {
            if (tVerts[j].Position != pCur.Position &&
                tVerts[j].Position != pPrev.Position &&
                tVerts[j].Position != pNext.Position) {
              tempVec = tVerts[j].Position;
              break;
            }
          }

          for (int j = 0; j < int(iVerts.size()); j++) {
            if (iVerts[j].Position == pPrev.Position)
              oIndices.push_back(j);
            if (iVerts[j].Position == pNext.Position)
              oIndices.push_back(j);
            if (iVerts[j].Position == tempVec)
              oIndices.push_back(j);
          }

          tVerts.clear();
          break;
        }

        float angle = Math3D.AngleBetween(pPrev.Position - pCur.Position,
                                          pNext.Position - pCur.Position) *
                      (180.0f / 3.14159265359f);

        if (angle <= 0 && angle >= 180)
          continue;

        bool inTri = false;

        for (int j = 0; j < int(iVerts.size()); j++) {
          if (InTriangle(iVerts[j].Position, pPrev.Position, pCur.Position,
                         pNext.Position) &&
              iVerts[j].Position != pPrev.Position &&
              iVerts[j].Position != pCur.Position &&
              iVerts[j].Position != pNext.Position) {
            inTri = true;
            break;
          }
        }

        if (inTri)
          continue;

        for (int j = 0; j < int(iVerts.size()); j++) {
          if (iVerts[j].Position == pCur.Position)
            oIndices.push_back(j);
          if (iVerts[j].Position == pPrev.Position)
            oIndices.push_back(j);
          if (iVerts[j].Position == pNext.Position)
            oIndices.push_back(j);
        }

        for (int j = 0; j < int(tVerts.size()); j++) {
          if (tVerts[j].Position == pCur.Position) {
            tVerts.erase(tVerts.begin() + j);
            break;
          }
        }

        i = -1;
      }

      if (oIndices.size() == 0)
        break;
      if (tVerts.size() == 0)
        break;
    }
  }
  inline bool LoadMaterials(std::string path) {
    if (path.substr(path.size() - 4, path.size()) != ".mtl")
      return false;

    std::ifstream file(path);

    if (!file.is_open())
      return false;

    cMaterial tempMaterial;

    bool listening = false;

    std::string curline;

    while (std::getline(file, curline)) {
      if (FirstToken(curline) == "newmtl") {
        if (!listening) {
          listening = true;

          if (curline.size() > 7)
            tempMaterial.Name = Tail(curline);
          else
            tempMaterial.Name = "none";
        }
        else {
          LoadedMaterials.push_back(tempMaterial);

          tempMaterial = cMaterial();

          if (curline.size() > 7)
            tempMaterial.Name = Tail(curline);
          else
            tempMaterial.Name = "none";
        }
      }

      if (FirstToken(curline) == "Ka") {
        std::vector<std::string> temp;
        Split(Tail(curline), &temp, " ");

        if (temp.size() != 3)
          continue;

        tempMaterial.Ka.X = std::stof(temp[0]);
        tempMaterial.Ka.Y = std::stof(temp[1]);
        tempMaterial.Ka.Z = std::stof(temp[2]);
      }

      if (FirstToken(curline) == "Kd") {
        std::vector<std::string> temp;
        Split(Tail(curline), &temp, " ");

        if (temp.size() != 3)
          continue;

        tempMaterial.Kd.X = std::stof(temp[0]);
        tempMaterial.Kd.Y = std::stof(temp[1]);
        tempMaterial.Kd.Z = std::stof(temp[2]);
      }

      if (FirstToken(curline) == "Ks") {
        std::vector<std::string> temp;
        Split(Tail(curline), &temp, " ");

        if (temp.size() != 3)
          continue;

        tempMaterial.Ks.X = std::stof(temp[0]);
        tempMaterial.Ks.Y = std::stof(temp[1]);
        tempMaterial.Ks.Z = std::stof(temp[2]);
      }

      if (FirstToken(curline) == "Ns")
        tempMaterial.Ns = std::stof(Tail(curline));

      if (FirstToken(curline) == "Ni")
        tempMaterial.Ni = std::stof(Tail(curline));

      if (FirstToken(curline) == "d")
        tempMaterial.D = std::stof(Tail(curline));

      if (FirstToken(curline) == "illum")
        tempMaterial.Illum = std::stoi(Tail(curline));

      if (FirstToken(curline) == "map_Ka")
        tempMaterial.MapKa = Tail(curline);

      if (FirstToken(curline) == "map_Kd")
        tempMaterial.MapKd = Tail(curline);

      if (FirstToken(curline) == "map_Ks")
        tempMaterial.MapKs = Tail(curline);

      if (FirstToken(curline) == "map_Ns")
        tempMaterial.MapNs = Tail(curline);

      if (FirstToken(curline) == "map_d")
        tempMaterial.MapD = Tail(curline);

      if (FirstToken(curline) == "map_Bump" ||
          FirstToken(curline) == "map_bump" || FirstToken(curline) == "bump")
        tempMaterial.MapBump = Tail(curline);
    }

    LoadedMaterials.push_back(tempMaterial);

    if (LoadedMaterials.empty())
      return false;
    else
      return true;
  }

  template <class T>
  inline const T &GetElement(const std::vector<T> &elements,
                             std::string &index) {
    auto idx = std::stoi(index);

    if (idx < 0)
      idx = int(elements.size()) + idx;
    else
      idx--;

    return elements[idx];
  }

  cMath3D Math3D;
};

}  // namespace Forradia
