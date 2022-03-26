
#include "CommonExternal.h"
#include "F_ModelGraphics.h"
#include "../core/F_Engine.h"

namespace Forradia
{

void F_ModelGraphics::DrawModel(std::string ModelName, float X, float Y, float Z, float Rotation, float SpecificScaling)
{
    DrawModel(GetId(ModelName), X, Y, Z, Rotation, SpecificScaling);
}

void F_ModelGraphics::DrawModel(int ModelNameId, float X, float Y, float Z, float Rotation, float SpecificScaling)
{

    glTranslatef(X, Y, Z);
    glRotatef(Rotation, 0, 1.0f, 0.0);
    glTranslatef(-X, -Y, -Z);

    glBegin(GL_TRIANGLES);

    auto& Model = Engine.ModelLoader.Models[ModelNameId];

    for (auto& Mesh : Model.LoadedMeshes)
    {
        glColor4f(Mesh.MeshMaterial.Kd.X, Mesh.MeshMaterial.Kd.Y, Mesh.MeshMaterial.Kd.Z, 1.0f);

        for (auto& Vec : Mesh.Vertices)
        {
            auto XVec = X + ModelScaling * Vec.Position.X * SpecificScaling;
            auto YVec = Y + ModelScaling * Vec.Position.Y * SpecificScaling;
            auto ZVec = Z + ModelScaling * Vec.Position.Z * SpecificScaling;

            glVertex3f(XVec, YVec, ZVec);
        }
    }

    glEnd();

    glTranslatef(X, Y, Z);
    glRotatef(-Rotation, 0, 1.0f, 0.0);
    glTranslatef(-X, -Y, -Z);
}

}
