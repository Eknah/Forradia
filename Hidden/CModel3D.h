#pragma once
#include "CMath3D.h"
#include "CAlgorithmsVectors.h"
#include "CAlgorithmsStrings.h"
namespace Forradia
{

class CModel3D : public CVectorAlgorithms, CAlgorithmsStrings
{

public:
    CModel3D() {}

    ~CModel3D()
    {
        LoadedMeshes.clear();
    }

    inline bool LoadFile(String Path)
    {
        if (Path.substr(Path.size() - 4, 4) != ".obj")
            return false;
        std::ifstream file(Path);
        if (!file.is_open())
            return false;
        LoadedMeshes.clear();
        LoadedVertices.clear();
        LoadedIndices.clear();
        std::vector<CVector3> Positions;
        std::vector<CVector2> TCoords;
        std::vector<CVector3> Normals;
        std::vector<CVertex> Vertices;
        std::vector<unsigned int> Indices;
        std::vector<std::string> MeshMatNames;
        bool listening = false;
        String meshname;
        CMesh tempMesh;
        String curline;
        while (std::getline(file, curline))
        {
            if (FirstToken(curline) == "o" || FirstToken(curline) == "g" || curline[0] == 'g')
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
                        tempMesh = CMesh(Vertices, Indices);
                        tempMesh.MeshName = meshname;
                        LoadedMeshes.push_back(tempMesh);
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
                std::vector<String> spos;
                CVector3 vpos;
                Split(Tail(curline), spos, " ");
                vpos.X = std::stof(spos[0]);
                vpos.Y = std::stof(spos[1]);
                vpos.Z = std::stof(spos[2]);
                Positions.push_back(vpos);
            }
            if (FirstToken(curline) == "vt")
            {
                std::vector<String> stex;
                CVector2 vtex;
                Split(Tail(curline), stex, " ");
                vtex.X = std::stof(stex[0]);
                vtex.Y = std::stof(stex[1]);
                TCoords.push_back(vtex);
            }
            if (FirstToken(curline) == "vn")
            {
                std::vector<String> snor;
                CVector3 vnor;
                Split(Tail(curline), snor, " ");
                vnor.X = std::stof(snor[0]);
                vnor.Y = std::stof(snor[1]);
                vnor.Z = std::stof(snor[2]);
                Normals.push_back(vnor);
            }
            if (FirstToken(curline) == "f")
            {
                std::vector<CVertex> vVerts;
                GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);
                for (int i = 0; i < int(vVerts.size()); i++)
                {
                    Vertices.push_back(vVerts[i]);
                    LoadedVertices.push_back(vVerts[i]);
                }
                std::vector<unsigned int> iIndices;
                VertexTriangluation(iIndices, vVerts);
                for (int i = 0; i < int(iIndices.size()); i++)
                {
                    unsigned int indnum = (unsigned int)((Vertices.size()) - vVerts.size()) + iIndices[i];
                    Indices.push_back(indnum);
                    indnum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
                    LoadedIndices.push_back(indnum);
                }
            }
            if (FirstToken(curline) == "usemtl")
            {
                MeshMatNames.push_back(Tail(curline));
                if (!Indices.empty() && !Vertices.empty())
                {
                    tempMesh = CMesh(Vertices, Indices);
                    tempMesh.MeshName = meshname;
                    int i = 2;
                    while (1) {
                        tempMesh.MeshName = meshname + "_" + std::to_string(i);
                        for (auto& m : LoadedMeshes)
                            if (m.MeshName == tempMesh.MeshName)
                                continue;
                        break;
                    }

                    LoadedMeshes.push_back(tempMesh);
                    Vertices.clear();
                    Indices.clear();
                }
            }
            if (FirstToken(curline) == "mtllib")
            {

                std::vector<String> temp;
                Split(Path, temp, "/");
                String pathtomat = Path.substr(0, Path.length() - 4) + ".mtl";
                LoadMaterials(pathtomat);
            }
        }
        if (!Indices.empty() && !Vertices.empty())
        {
            tempMesh = CMesh(Vertices, Indices);
            tempMesh.MeshName = meshname;
            LoadedMeshes.push_back(tempMesh);
        }
        file.close();
        for (int i = 0; i < MeshMatNames.size(); i++)
        {
            String matname = MeshMatNames[i];
            for (int j = 0; j < LoadedMaterials.size(); j++)
            {
                if (LoadedMaterials[j].Name == matname)
                {
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

    std::vector<CMesh> LoadedMeshes;
    std::vector<CVertex> LoadedVertices;
    std::vector<unsigned int> LoadedIndices;
    std::vector<CMaterial> LoadedMaterials;

private:
    inline void GenVerticesFromRawOBJ(std::vector<CVertex>& oVerts, const std::vector<CVector3>& iPositions, const std::vector<CVector2>& iTCoords, const std::vector<CVector3>& iNormals, String icurline)
    {
        std::vector<String> sface, svert;
        CVertex vVert;
        Split(Tail(icurline), sface, " ");
        bool noNormal = false;
        for (int i = 0; i < int(sface.size()); i++)
        {
            int vtype;

            Split(sface[i], svert, "/");

            if (svert.size() == 1)
            {
                vtype = 1;
            }

            if (svert.size() == 2)
            {
                vtype = 2;
            }

            if (svert.size() == 3)
            {
                if (svert[1] != "")
                {
                    vtype = 4;
                }
                else
                {
                    vtype = 3;
                }
            }

            switch (vtype)
            {
            case 1:
            {
                vVert.Position = GetElement(iPositions, svert[0]);
                vVert.TextureCoordinate = CVector2(0, 0);
                noNormal = true;
                oVerts.push_back(vVert);
                break;
            }
            case 2:
            {
                vVert.Position = GetElement(iPositions, svert[0]);
                vVert.TextureCoordinate = GetElement(iTCoords, svert[1]);
                noNormal = true;
                oVerts.push_back(vVert);
                break;
            }
            case 3:
            {
                vVert.Position = GetElement(iPositions, svert[0]);
                vVert.TextureCoordinate = CVector2(0, 0);
                vVert.Normal = GetElement(iNormals, svert[2]);
                oVerts.push_back(vVert);
                break;
            }
            case 4:
            {
                vVert.Position = GetElement(iPositions, svert[0]);
                vVert.TextureCoordinate = GetElement(iTCoords, svert[1]);
                vVert.Normal = GetElement(iNormals, svert[2]);
                oVerts.push_back(vVert);
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
            CVector3 A = oVerts[0].Position - oVerts[1].Position;
            CVector3 B = oVerts[2].Position - oVerts[1].Position;

            CVector3 Normal = Math3D.Cross(A, B);

            for (int i = 0; i < int(oVerts.size()); i++)
            {
                oVerts[i].Normal = Normal;
            }
        }
    }
    inline void VertexTriangluation(std::vector<unsigned int>& oIndices, const std::vector<CVertex>& iVerts)
    {
        if (iVerts.size() < 3)
        {
            return;
        }
        if (iVerts.size() == 3)
        {
            oIndices.push_back(0);
            oIndices.push_back(1);
            oIndices.push_back(2);
            return;
        }

        std::vector<CVertex> tVerts = iVerts;

        while (true)
        {
            for (int i = 0; i < int(tVerts.size()); i++)
            {
                CVertex pPrev;
                if (i == 0)
                {
                    pPrev = tVerts[tVerts.size() - 1];
                }
                else
                {
                    pPrev = tVerts[i - 1];
                }

                CVertex pCur = tVerts[i];

                CVertex pNext;
                if (i == tVerts.size() - 1)
                {
                    pNext = tVerts[0];
                }
                else
                {
                    pNext = tVerts[i + 1];
                }

                if (tVerts.size() == 3)
                {
                    for (int j = 0; j < int(tVerts.size()); j++)
                    {
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
                if (tVerts.size() == 4)
                {
                    for (int j = 0; j < int(iVerts.size()); j++)
                    {
                        if (iVerts[j].Position == pCur.Position)
                            oIndices.push_back(j);
                        if (iVerts[j].Position == pPrev.Position)
                            oIndices.push_back(j);
                        if (iVerts[j].Position == pNext.Position)
                            oIndices.push_back(j);
                    }

                    CVector3 tempVec;
                    for (int j = 0; j < int(tVerts.size()); j++)
                    {
                        if (tVerts[j].Position != pCur.Position
                                && tVerts[j].Position != pPrev.Position
                                && tVerts[j].Position != pNext.Position)
                        {
                            tempVec = tVerts[j].Position;
                            break;
                        }
                    }

                    for (int j = 0; j < int(iVerts.size()); j++)
                    {
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

                float angle = Math3D.AngleBetween(pPrev.Position - pCur.Position, pNext.Position - pCur.Position) * (180 / 3.14159265359);
                if (angle <= 0 && angle >= 180)
                    continue;

                bool inTri = false;
                for (int j = 0; j < int(iVerts.size()); j++)
                {
                    if (InTriangle(iVerts[j].Position, pPrev.Position, pCur.Position, pNext.Position)
                            && iVerts[j].Position != pPrev.Position
                            && iVerts[j].Position != pCur.Position
                            && iVerts[j].Position != pNext.Position)
                    {
                        inTri = true;
                        break;
                    }
                }
                if (inTri)
                    continue;

                for (int j = 0; j < int(iVerts.size()); j++)
                {
                    if (iVerts[j].Position == pCur.Position)
                        oIndices.push_back(j);
                    if (iVerts[j].Position == pPrev.Position)
                        oIndices.push_back(j);
                    if (iVerts[j].Position == pNext.Position)
                        oIndices.push_back(j);
                }

                for (int j = 0; j < int(tVerts.size()); j++)
                {
                    if (tVerts[j].Position == pCur.Position)
                    {
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
    inline bool LoadMaterials(String path)
    {
        if (path.substr(path.size() - 4, path.size()) != ".mtl")
            return false;


        std::ifstream file(path);

        if (!file.is_open())
            return false;

        CMaterial tempMaterial;

        bool listening = false;

        String curline;
        while (std::getline(file, curline))
        {
            if (FirstToken(curline) == "newmtl")
            {
                if (!listening)
                {
                    listening = true;

                    if (curline.size() > 7)
                    {
                        tempMaterial.Name = Tail(curline);
                    }
                    else
                    {
                        tempMaterial.Name = "none";
                    }
                }
                else
                {

                    LoadedMaterials.push_back(tempMaterial);

                    tempMaterial = CMaterial();

                    if (curline.size() > 7)
                    {
                        tempMaterial.Name = Tail(curline);
                    }
                    else
                    {
                        tempMaterial.Name = "none";
                    }
                }
            }
            if (FirstToken(curline) == "Ka")
            {
                std::vector<String> temp;
                Split(Tail(curline), temp, " ");

                if (temp.size() != 3)
                    continue;

                tempMaterial.Ka.X = std::stof(temp[0]);
                tempMaterial.Ka.Y = std::stof(temp[1]);
                tempMaterial.Ka.Z = std::stof(temp[2]);
            }
            if (FirstToken(curline) == "Kd")
            {
                std::vector<String> temp;
                Split(Tail(curline), temp, " ");

                if (temp.size() != 3)
                    continue;

                tempMaterial.Kd.X = std::stof(temp[0]);
                tempMaterial.Kd.Y = std::stof(temp[1]);
                tempMaterial.Kd.Z = std::stof(temp[2]);
            }
            if (FirstToken(curline) == "Ks")
            {
                std::vector<String> temp;
                Split(Tail(curline), temp, " ");

                if (temp.size() != 3)
                    continue;

                tempMaterial.Ks.X = std::stof(temp[0]);
                tempMaterial.Ks.Y = std::stof(temp[1]);
                tempMaterial.Ks.Z = std::stof(temp[2]);
            }
            if (FirstToken(curline) == "Ns")
            {
                tempMaterial.Ns = std::stof(Tail(curline));
            }
            if (FirstToken(curline) == "Ni")
            {
                tempMaterial.Ni = std::stof(Tail(curline));
            }
            if (FirstToken(curline) == "d")
            {
                tempMaterial.D = std::stof(Tail(curline));
            }
            if (FirstToken(curline) == "illum")
            {
                tempMaterial.Illum = std::stoi(Tail(curline));
            }
            if (FirstToken(curline) == "map_Ka")
            {
                tempMaterial.MapKa = Tail(curline);
            }
            if (FirstToken(curline) == "map_Kd")
            {
                tempMaterial.MapKd = Tail(curline);
            }
            if (FirstToken(curline) == "map_Ks")
            {
                tempMaterial.MapKs = Tail(curline);
            }
            if (FirstToken(curline) == "map_Ns")
            {
                tempMaterial.MapNs = Tail(curline);
            }
            if (FirstToken(curline) == "map_d")
            {
                tempMaterial.MapD = Tail(curline);
            }
            if (FirstToken(curline) == "map_Bump" || FirstToken(curline) == "map_bump" || FirstToken(curline) == "bump")
            {
                tempMaterial.MapBump = Tail(curline);
            }
        }


        LoadedMaterials.push_back(tempMaterial);

        if (LoadedMaterials.empty())
            return false;
        else
            return true;
    }

    template <class T>
    inline const T& GetElement(const std::vector<T>& elements, String& index)
    {
        auto idx = std::stoi(index);

        if (idx < 0)
            idx = int(elements.size()) + idx;
        else
            idx--;

        return elements[idx];
    }

    CMath3D Math3D;

};

}
