
#pragma once
#include "CommonExternal.h"
#include "../engine/Aliases.h"
#include "../engine/iEngine.h"

namespace Forradia
{

class cModelGraphics
{

public:

    cModelGraphics(iEngine& engine) : Engine(engine) {}

    // ---- Drawing operations ----

    inline void DrawModel(std::string ModelName, float X, float Y, float Z, float Rotation, float SpecificScaling)
    {
        DrawModel(GetId(ModelName), X, Y, Z, Rotation, SpecificScaling);
    }

    inline void DrawModel(int ModelNameId, float X, float Y, float Z, float Rotation, float SpecificScaling)
    {

        glTranslatef(X, Y, Z);
        glRotatef(Rotation, 0, 1.0f, 0.0);
        glTranslatef(-X, -Y, -Z);

        glBegin(GL_TRIANGLES);

        auto& Model = Engine.ModelLoader.Models[ModelNameId];

        for (auto& Mesh : Model.LoadedMeshes)
        {
            glColor4f(Mesh.MeshMaterial.Kd.X, Mesh.MeshMaterial.Kd.Y, Mesh.MeshMaterial.Kd.Z, 1.0f);

            for (auto& Vector : Mesh.Vertices)
            {
                auto XVec = X + ModelScaling * Vector.Position.X * SpecificScaling;
                auto YVec = Y + ModelScaling * Vector.Position.Y * SpecificScaling;
                auto ZVec = Z + ModelScaling * Vector.Position.Z * SpecificScaling;

                glVertex3f(XVec, YVec, ZVec);
            }
        }

        glEnd();

        glTranslatef(X, Y, Z);
        glRotatef(-Rotation, 0, 1.0f, 0.0);
        glTranslatef(-X, -Y, -Z);
    }

private:

    iEngine& Engine;

    float ModelScaling = 0.1f;
};

}