#include "sdk.h"

Vector3 SDK::GetBoneWithRotation(uintptr_t mesh, int id)
{
	int IsCached = driver.read<int>(mesh + 0x650);
	auto BoneTransform = driver.read<FTransform>(driver.read<uintptr_t>(mesh + 0x10 * IsCached + 0x608) + 0x60 * id);
	
	FTransform ComponentToWorld = driver.read<FTransform>(mesh + 0x230);

	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(BoneTransform.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

struct CamewaDescwipsion
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
	char Useless[0x18];
};

CamewaDescwipsion GetViewPoint()
{
	CamewaDescwipsion ViewPoint;

	auto location_pointer = driver.read<uintptr_t>(LocalPtrs::Gworld + 0x110);
	auto rotation_pointer = driver.read<uintptr_t>(LocalPtrs::Gworld + 0x120);

	struct FNRot
	{
		double a;
		char pad_0008[24];
		double b;
		char pad_0028[424];
		double c;
	}fnRot;

	fnRot.a = driver.read<double>(rotation_pointer);
	fnRot.b = driver.read<double>(rotation_pointer + 0x20);
	fnRot.c = driver.read<double>(rotation_pointer + 0x1d0);

	ViewPoint.Location = driver.read<Vector3>(location_pointer);
	ViewPoint.Rotation.x = asin(fnRot.c) * (180.0 / M_PI);
	ViewPoint.Rotation.y = ((atan2(fnRot.a * -1, fnRot.b) * (180.0 / M_PI)) * -1) * -1;
	ViewPoint.FieldOfView = driver.read<float>((uintptr_t)LocalPtrs::PlayerController + 0x394) * 90.f;

	return ViewPoint;
}

Vector3 SDK::ProjectWorldToScreen(Vector3 WorldLocation)
{

	CamewaDescwipsion ViewPoint = GetViewPoint();
	D3DMATRIX tempMatrix = Matrix(ViewPoint.Rotation);
	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	Vector3 vDelta = WorldLocation - ViewPoint.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;
	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(ViewPoint.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(ViewPoint.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
}



