#pragma once
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/EngineVertexBuffer.h>


//EngineVertex.h 가 FEngineVertex구조체 갖고있음

class UBlitzMeshGenerator : public UEngineResources
{
public:
	UBlitzMeshGenerator();
	~UBlitzMeshGenerator();

	void MakeSquare();
	void MakeCube();
	void MakeCylinder(const float _bottomRadius, const float _topRadius, float _height, int _sliceCount);

protected:

private:
	//std::shared_ptr<UMesh> Mesh;//이거 변수를 리턴하려면 스태틱쓸수없어? 


};

