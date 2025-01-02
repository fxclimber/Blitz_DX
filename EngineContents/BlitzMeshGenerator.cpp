#include "PreCompile.h"
#include "BlitzMeshGenerator.h"
#include <EngineCore/Mesh.h>
#include <EngineBase/EngineMath.h>




UBlitzMeshGenerator::UBlitzMeshGenerator()
{
}

UBlitzMeshGenerator::~UBlitzMeshGenerator()
{
}

std::shared_ptr<UMesh> UBlitzMeshGenerator::MakeSquare()
{
	std::vector<float4> position;
	std::vector<float4> color;
	std::vector<float4> normal;
	std::vector<float4> texcoord;

	std::vector<FEngineVertex> vertex;
	vertex.resize(4);







	return std::shared_ptr<UMesh>();
}

std::shared_ptr<UMesh> UBlitzMeshGenerator::MakeCube()
{
	return std::shared_ptr<UMesh>();
}

std::shared_ptr<UMesh> UBlitzMeshGenerator::MakeCylinder(const float _bottomRadius, const float _topRadius, float _height, int _sliceCount)
{
	return std::shared_ptr<UMesh>();
}

