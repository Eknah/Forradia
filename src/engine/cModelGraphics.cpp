// Copyright (C) 2022  Andreas Åkerberg
// This code is licensed under MIT license (see LICENSE for details)

#include "cModelGraphics.h"

namespace Forradia {

void cModelGraphics::DrawModel(std::string ModelName, float X, float Y, float Z,
                        float Rotation, float SpecificScaling) const {
    DrawModel(GetId(ModelName), X, Y, Z, Rotation, SpecificScaling);
  }

void cModelGraphics::DrawModel(int ModelNameId, float X, float Y, float Z,
                        float Rotation, float SpecificScaling) const {
    glTranslatef(X, Y, Z);
    glRotatef(Rotation, 0, 1.0f, 0.0);
    glTranslatef(-X, -Y, -Z);

    glBegin(GL_TRIANGLES);

    auto &Model = engine.modelLoader.models[ModelNameId];

    for (auto &Mesh : Model.loadedMeshes) {
      glColor4f(Mesh.meshMaterial.kd.x, Mesh.meshMaterial.kd.y,
                Mesh.meshMaterial.kd.z, 1.0f);

      for (auto &Vector : Mesh.vertices) {
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

}  // namespace Forradia
