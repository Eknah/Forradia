#pragma once
namespace Forradia
{

    class CObject
	{

	public:
        CObject(std::string objectTypeName, bool randomScaling = True);

        void UseOn(std::unique_ptr<CObject>& other);

		int ObjectType = 0;
		float Rotation = 0.0f;
		float Scaling = 1.0f;

	private:
		void TransformInto(String objectName);

	};

}
