// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)
//
// This source file is built upon source code from the OBJ-Loader
// repo by Bly7 at https://github.com/Bly7/OBJ-Loader

#include "Model3D.h"

namespace Forradia
{
    Model3D::~Model3D()
    {
        loadedMeshes.clear();
    }

    bool Model3D::LoadFile(std::string Path)
    {
        if (Path.substr(Path.size() - 4, 4) != ".obj")
            return false;

        std::ifstream file(Path);

        if (!file.is_open())
            return false;

        loadedMeshes.clear();
        loadedVertices.clear();
        loadedIndices.clear();

        std::vector<Vector3> Positions;
        std::vector<Vector2> TCoords;
        std::vector<Vector3> Normals;
        std::vector<Vertex> Vertices;
        std::vector<unsigned int> Indices;
        std::vector<std::string> MeshMatNames;
        bool listening = false;
        std::string meshname;
        Mesh tempMesh;
        std::string curline;

        while (std::getline(file, curline))
        {
            if (FirstToken(curline) == "o" || FirstToken(curline) == "g" ||
                curline[0] == 'g')
            {
                if (!listening)
                {
                    listening = true;

                    if (FirstToken(curline) == "o" || FirstToken(curline) == "g")
                        meshname = Tail(curline);
                    else
                        meshname = "unnamed";
                }
                else
                {
                    if (!Indices.empty() && !Vertices.empty())
                    {
                        tempMesh = Mesh(Vertices, Indices);
                        tempMesh.meshName = meshname;
                        loadedMeshes.push_back(tempMesh);
                        Vertices.clear();
                        Indices.clear();
                        meshname.clear();
                        meshname = Tail(curline);
                    }
                    else
                    {
                        if (FirstToken(curline) == "o" || FirstToken(curline) == "g")
                            meshname = Tail(curline);
                        else
                            meshname = "unnamed";
                    }
                }
            }

            if (FirstToken(curline) == "v")
            {
                std::vector<std::string> spos;
                Vector3 vpos;
                Split(Tail(curline), &spos, " ");
                vpos.x = std::stof(spos[0]);
                vpos.y = std::stof(spos[1]);
                vpos.z = std::stof(spos[2]);
                Positions.push_back(vpos);
            }

            if (FirstToken(curline) == "vt")
            {
                std::vector<std::string> stex;
                Vector2 vtex;
                Split(Tail(curline), &stex, " ");
                vtex.x = std::stof(stex[0]);
                vtex.y = std::stof(stex[1]);
                TCoords.push_back(vtex);
            }

            if (FirstToken(curline) == "vn")
            {
                std::vector<std::string> snor;
                Vector3 vnor;
                Split(Tail(curline), &snor, " ");
                vnor.x = std::stof(snor[0]);
                vnor.y = std::stof(snor[1]);
                vnor.z = std::stof(snor[2]);
                Normals.push_back(vnor);
            }

            if (FirstToken(curline) == "f")
            {
                std::vector<Vertex> vVerts;
                GenVerticesFromRawOBJ(&vVerts, Positions, TCoords, Normals, curline);

                for (unsigned int i = 0; i < vVerts.size(); i++)
                {
                    Vertices.push_back(vVerts[i]);
                    loadedVertices.push_back(vVerts[i]);
                }

                std::vector<unsigned int> iIndices;
                VertexTriangluation(&iIndices, vVerts);

                for (unsigned int i = 0; i < iIndices.size(); i++)
                {
                    unsigned int indnum =
                        (unsigned int)((Vertices.size()) - vVerts.size()) + iIndices[i];
                    Indices.push_back(indnum);
                    indnum = (unsigned int)((loadedVertices.size()) - vVerts.size()) +
                        iIndices[i];
                    loadedIndices.push_back(indnum);
                }
            }

            if (FirstToken(curline) == "usemtl")
            {
                MeshMatNames.push_back(Tail(curline));

                if (!Indices.empty() && !Vertices.empty())
                {
                    tempMesh = Mesh(Vertices, Indices);
                    tempMesh.meshName = meshname;
                    int i = 2;

                    while (1)
                    {
                        tempMesh.meshName = meshname + "_" + std::to_string(i);

                        for (auto& m : loadedMeshes)
                            if (m.meshName == tempMesh.meshName)
                                continue;
                        break;
                    }

                    loadedMeshes.push_back(tempMesh);
                    Vertices.clear();
                    Indices.clear();
                }
            }

            if (FirstToken(curline) == "mtllib")
            {
                std::vector<std::string> temp;
                Split(Path, &temp, "/");
                std::string pathtomat = Path.substr(0, Path.length() - 4) + ".mtl";
                LoadMaterials(pathtomat);
            }
        }

        if (!Indices.empty() && !Vertices.empty())
        {
            tempMesh = Mesh(Vertices, Indices);
            tempMesh.meshName = meshname;
            loadedMeshes.push_back(tempMesh);
        }

        file.close();

        for (unsigned int i = 0; i < MeshMatNames.size(); i++)
        {
            std::string matname = MeshMatNames[i];

            for (unsigned int j = 0; j < loadedMaterials.size(); j++)
            {
                if (loadedMaterials[j].name == matname)
                {
                    loadedMeshes[i].meshMaterial = loadedMaterials[j];
                    break;
                }
            }
        }

        if (loadedMeshes.empty() && loadedVertices.empty() && loadedIndices.empty())
            return false;
        else
            return true;
    }

    void Model3D::GenVerticesFromRawOBJ(std::vector<Vertex>* oVerts,
        const std::vector<Vector3>& iPositions,
        const std::vector<Vector2>& iTCoords,
        const std::vector<Vector3>& iNormals,
        std::string icurline)
    {
        std::vector<std::string> sface, svert;
        Vertex vVert;
        Split(Tail(icurline), &sface, " ");
        bool noNormal = false;

        for (unsigned int i = 0; i < sface.size(); i++)
        {
            int vtype;

            Split(sface[i], &svert, "/");

            if (svert.size() == 1)
                vtype = 1;

            if (svert.size() == 2)
                vtype = 2;

            if (svert.size() == 3)
            {
                if (svert[1] != "")
                    vtype = 4;
                else
                    vtype = 3;
            }

            switch (vtype)
            {
            case 1:
            {
                vVert.position = GetElement(iPositions, svert[0]);
                vVert.textureCoordinate = Vector2(0, 0);
                noNormal = true;
                oVerts->push_back(vVert);

                break;
            }
            case 2:
            {
                vVert.position = GetElement(iPositions, svert[0]);
                vVert.textureCoordinate = GetElement(iTCoords, svert[1]);
                noNormal = true;
                oVerts->push_back(vVert);

                break;
            }
            case 3:
            {
                vVert.position = GetElement(iPositions, svert[0]);
                vVert.textureCoordinate = Vector2(0, 0);
                vVert.normal = GetElement(iNormals, svert[2]);
                oVerts->push_back(vVert);

                break;
            }
            case 4:
            {
                vVert.position = GetElement(iPositions, svert[0]);
                vVert.textureCoordinate = GetElement(iTCoords, svert[1]);
                vVert.normal = GetElement(iNormals, svert[2]);
                oVerts->push_back(vVert);

                break;
            }
            default:
            {
                break;
            }
            }
        }

        if (noNormal)
        {
            Vector3 A = (*oVerts)[0].position - (*oVerts)[1].position;
            Vector3 B = (*oVerts)[2].position - (*oVerts)[1].position;

            Vector3 Normal = math3D.Cross(A, B);

            for (unsigned int i = 0; i < oVerts->size(); i++)
                (*oVerts)[i].normal = Normal;
        }
    }

    void Model3D::VertexTriangluation(std::vector<unsigned int>* oIndices,
        const std::vector<Vertex>& iVerts)
    {
        if (iVerts.size() < 3)
            return;

        if (iVerts.size() == 3)
        {
            oIndices->push_back(0);
            oIndices->push_back(1);
            oIndices->push_back(2);

            return;
        }

        std::vector<Vertex> tVerts = iVerts;

        while (true)
        {
            for (unsigned int i = 0; i < tVerts.size(); i++)
            {
                Vertex pPrev;

                if (i == 0)
                    pPrev = tVerts[tVerts.size() - 1];
                else
                    pPrev = tVerts[i - 1];

                Vertex pCur = tVerts[i];
                Vertex pNext;

                if (i == tVerts.size() - 1)
                    pNext = tVerts[0];
                else
                    pNext = tVerts[i + 1];

                if (tVerts.size() == 3)
                {
                    for (unsigned int j = 0; j < tVerts.size(); j++)
                    {
                        if (iVerts[j].position == pCur.position)
                            oIndices->push_back(j);
                        if (iVerts[j].position == pPrev.position)
                            oIndices->push_back(j);
                        if (iVerts[j].position == pNext.position)
                            oIndices->push_back(j);
                    }

                    tVerts.clear();

                    break;
                }
                if (tVerts.size() == 4)
                {
                    for (unsigned int j = 0; j < iVerts.size(); j++)
                    {
                        if (iVerts[j].position == pCur.position)
                            oIndices->push_back(j);
                        if (iVerts[j].position == pPrev.position)
                            oIndices->push_back(j);
                        if (iVerts[j].position == pNext.position)
                            oIndices->push_back(j);
                    }

                    Vector3 tempVec;
                    for (unsigned int j = 0; j < tVerts.size(); j++)
                    {
                        if (tVerts[j].position != pCur.position &&
                            tVerts[j].position != pPrev.position &&
                            tVerts[j].position != pNext.position)
                        {
                            tempVec = tVerts[j].position;
                            break;
                        }
                    }

                    for (unsigned int j = 0; j < iVerts.size(); j++)
                    {
                        if (iVerts[j].position == pPrev.position)
                            oIndices->push_back(j);
                        if (iVerts[j].position == pNext.position)
                            oIndices->push_back(j);
                        if (iVerts[j].position == tempVec)
                            oIndices->push_back(j);
                    }

                    tVerts.clear();
                    break;
                }

                float angle = math3D.AngleBetween(pPrev.position - pCur.position,
                    pNext.position - pCur.position) *
                    (180.0f / 3.14159265359f);

                if (angle <= 0 && angle >= 180)
                    continue;

                bool inTri = false;

                for (unsigned int j = 0; j < iVerts.size(); j++)
                {
                    if (InTriangle(iVerts[j].position, pPrev.position, pCur.position,
                        pNext.position) &&
                        iVerts[j].position != pPrev.position &&
                        iVerts[j].position != pCur.position &&
                        iVerts[j].position != pNext.position)
                    {
                        inTri = true;
                        break;
                    }
                }

                if (inTri)
                    continue;

                for (unsigned int j = 0; j < iVerts.size(); j++)
                {
                    if (iVerts[j].position == pCur.position)
                        oIndices->push_back(j);
                    if (iVerts[j].position == pPrev.position)
                        oIndices->push_back(j);
                    if (iVerts[j].position == pNext.position)
                        oIndices->push_back(j);
                }

                for (unsigned int j = 0; j < tVerts.size(); j++)
                {
                    if (tVerts[j].position == pCur.position)
                    {
                        tVerts.erase(tVerts.begin() + j);
                        break;
                    }
                }

                i = -1;
            }

            if (oIndices->size() == 0)
                break;
            if (tVerts.size() == 0)
                break;
        }
    }

    bool Model3D::LoadMaterials(std::string path)
    {
        if (path.substr(path.size() - 4, path.size()) != ".mtl")
            return false;

        std::ifstream file(path);

        if (!file.is_open())
            return false;

        Material tempMaterial;

        bool listening = false;

        std::string curline;

        while (std::getline(file, curline))
        {
            if (FirstToken(curline) == "newmtl")
            {
                if (!listening)
                {
                    listening = true;

                    if (curline.size() > 7)
                        tempMaterial.name = Tail(curline);
                    else
                        tempMaterial.name = "none";
                }
                else
                {
                    loadedMaterials.push_back(tempMaterial);

                    tempMaterial = Material();

                    if (curline.size() > 7)
                        tempMaterial.name = Tail(curline);
                    else
                        tempMaterial.name = "none";
                }
            }

            if (FirstToken(curline) == "Ka")
            {
                std::vector<std::string> temp;
                Split(Tail(curline), &temp, " ");

                if (temp.size() != 3)
                    continue;

                tempMaterial.ka.x = std::stof(temp[0]);
                tempMaterial.ka.y = std::stof(temp[1]);
                tempMaterial.ka.z = std::stof(temp[2]);
            }

            if (FirstToken(curline) == "Kd")
            {
                std::vector<std::string> temp;
                Split(Tail(curline), &temp, " ");

                if (temp.size() != 3)
                    continue;

                tempMaterial.kd.x = std::stof(temp[0]);
                tempMaterial.kd.y = std::stof(temp[1]);
                tempMaterial.kd.z = std::stof(temp[2]);
            }

            if (FirstToken(curline) == "Ks")
            {
                std::vector<std::string> temp;
                Split(Tail(curline), &temp, " ");

                if (temp.size() != 3)
                    continue;

                tempMaterial.ks.x = std::stof(temp[0]);
                tempMaterial.ks.y = std::stof(temp[1]);
                tempMaterial.ks.z = std::stof(temp[2]);
            }

            if (FirstToken(curline) == "Ns")
                tempMaterial.ns = std::stof(Tail(curline));

            if (FirstToken(curline) == "Ni")
                tempMaterial.ni = std::stof(Tail(curline));

            if (FirstToken(curline) == "d")
                tempMaterial.d = std::stof(Tail(curline));

            if (FirstToken(curline) == "illum")
                tempMaterial.illum = std::stoi(Tail(curline));

            if (FirstToken(curline) == "map_Ka")
                tempMaterial.mapKa = Tail(curline);

            if (FirstToken(curline) == "map_Kd")
                tempMaterial.mapKd = Tail(curline);

            if (FirstToken(curline) == "map_Ks")
                tempMaterial.mapKs = Tail(curline);

            if (FirstToken(curline) == "map_Ns")
                tempMaterial.mapNs = Tail(curline);

            if (FirstToken(curline) == "map_d")
                tempMaterial.mapD = Tail(curline);

            if (FirstToken(curline) == "map_Bump" ||
                FirstToken(curline) == "map_bump" || FirstToken(curline) == "bump")
                tempMaterial.mapBump = Tail(curline);
        }

        loadedMaterials.push_back(tempMaterial);

        if (loadedMaterials.empty())
            return false;
        else
            return true;
    }
}