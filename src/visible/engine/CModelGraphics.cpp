#include "CommonExternal.h"
#include "CModelGraphics.h"
#include "../hidden/CEngine.h"

namespace Forradia
{

void CModelGraphics::DrawModel(std::string modelName, float x, float y, float z, float rotation, float specificScaling)
{
    DrawModel(GetId(modelName), x, y, z, rotation, specificScaling);
}

void CModelGraphics::DrawModel(int modelNameHash, float x, float y, float z, float rotation, float specificScaling)
{
    glDisable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glTranslatef(x, y, z);
    glRotatef(rotation, 0, 1.0f, 0.0);
    glTranslatef(-x, -y, -z);
    glBegin(GL_TRIANGLES);

    auto& model = Engine.ModelLoader.Models[modelNameHash];

    for (auto& mesh : model.LoadedMeshes)
    {
        GLfloat matColorD[3] = { mesh.MeshMaterial.Kd.X, mesh.MeshMaterial.Kd.Y, mesh.MeshMaterial.Kd.Z };
        glColor4f(matColorD[0], matColorD[1], matColorD[2], 1.0f);

        for (auto& vec : mesh.Vertices)
        {
            auto xvec = x + ModelScaling * vec.Position.X * specificScaling;
            auto yvec = y + ModelScaling * vec.Position.Y * specificScaling;
            auto zvec = z + ModelScaling * vec.Position.Z * specificScaling;

            glVertex3f(xvec, yvec, zvec);
        }
    }

    glColor3f(1, 1, 1);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glTranslatef(x, y, z);
    glRotatef(-rotation, 0, 1.0f, 0.0);
    glTranslatef(-x, -y, -z);
}

}
