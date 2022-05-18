// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "ModelGraphics.h"

namespace Forradia
{
    void ModelGraphics::DrawModel(std::string ModelName, float X, float Y, float Z, float Rotation, float SpecificScaling, float opacity) const
    {
        DrawModel(GetId(ModelName), X, Y, Z, Rotation, SpecificScaling, opacity);
    }

    void ModelGraphics::DrawModel(int ModelNameId, float X, float Y, float Z, float Rotation, float SpecificScaling, float opacity) const
    {

        glTranslatef(X, Y, Z);
        glRotatef(Rotation, 0, 1.0f, 0.0);
        glTranslatef(-X, -Y, -Z);

        glBegin(GL_TRIANGLES);

        auto& Model = e.modelLoader.models.at(ModelNameId);

        for (auto& Mesh : Model.loadedMeshes)
        {
            glColor4f(Mesh.meshMaterial.kd.x, Mesh.meshMaterial.kd.y,
                Mesh.meshMaterial.kd.z, opacity);
            //        glColor4f(Mesh.meshMaterial.kd.x, Mesh.meshMaterial.kd.z,
            //                  Mesh.meshMaterial.kd.y, Opacity);

            for (auto& Vector : Mesh.vertices)
            {
                auto XVec = X + modelScaling * Vector.position.x * SpecificScaling;
                auto YVec = Y + modelScaling * Vector.position.y * SpecificScaling;
                auto ZVec = Z + modelScaling * Vector.position.z * SpecificScaling;

                glVertex3f(XVec, YVec, ZVec);
            }
        }

        glEnd();

        glTranslatef(X, Y, Z);
        glRotatef(-Rotation, 0, 1.0f, 0.0);
        glTranslatef(-X, -Y, -Z);
    }
}