#pragma once
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/EngineVertexBuffer.h>


//EngineVertex.h 가 FEngineVertex구조체 갖고있음

class UBlitzMeshGenerator : public UEngineResources
{
public:
	UBlitzMeshGenerator();
	~UBlitzMeshGenerator();

	static std::shared_ptr<class UMesh> MakeSquare();
	static std::shared_ptr<class UMesh> MakeCube();
	static std::shared_ptr<class UMesh> MakeCylinder(const float _bottomRadius, const float _topRadius, float _height, int _sliceCount);

protected:

private:
	//std::shared_ptr<UMesh> Mesh;//이거 변수를 리턴하려면 스태틱쓸수없어? 


};

