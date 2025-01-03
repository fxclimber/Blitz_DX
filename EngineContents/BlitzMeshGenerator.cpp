#include "PreCompile.h"
#include "BlitzMeshGenerator.h"
#include <EngineCore/Mesh.h>
#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineVertexBuffer.h>
#include <EngineCore/EngineIndexBuffer.h>



UBlitzMeshGenerator::UBlitzMeshGenerator()
{
}

UBlitzMeshGenerator::~UBlitzMeshGenerator()
{
}

void UBlitzMeshGenerator::MakeSquare()
{
	std::vector<FEngineVertex> vertexes;
	vertexes.resize(4);
	vertexes[0] = FEngineVertex{ FVector(-0.5f, 0.5f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
	vertexes[1] = FEngineVertex{ FVector(0.5f, 0.5f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
	vertexes[2] = FEngineVertex{ FVector(-0.5f, -0.5f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
	vertexes[3] = FEngineVertex{ FVector(0.5f, -0.5f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };
	UEngineVertexBuffer::Create("Plane", vertexes);

	std::vector<unsigned int> Indices;
	Indices.resize(6);
	Indices.push_back(0);
	Indices.push_back(1);
	Indices.push_back(2);
	Indices.push_back(1);
	Indices.push_back(3);
	Indices.push_back(2);
	UEngineIndexBuffer::Create("Plane", Indices);

	UMesh::Create("plane");


}

void UBlitzMeshGenerator::MakeCube()
{
}

void UBlitzMeshGenerator::MakeCylinder(const float _bottomRadius, const float _topRadius, float _height, int _sliceCount)
{
}

