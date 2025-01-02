#pragma once
#include "EngineShaderResources.h"
#include "Mesh.h"
#include "EngineMaterial.h"

// ���� : �������� �ּҴ���
//        Draw�� �ϴ� �ִ� �̳༮�� ������� �Ұ��̴�.
class URenderUnit
{
public:
	// constrcuter destructer
	URenderUnit();
	~URenderUnit();

	// �Ž�(��ü) 
	std::shared_ptr<UMesh> Mesh;
	// ��Ƽ����(�Ǻ�)
	std::shared_ptr<UEngineMaterial> Material;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayOut;

	ENGINEAPI void SetMesh(std::string_view _Name);
	ENGINEAPI void SetMaterial(std::string_view _Name);

	//void SetInputAssembler1();
	//void SetInputAssembler1();

	ENGINEAPI virtual void Render(class UEngineCamera* _Camera, float _DeltaTime);

private:
	UEngineConstantBufferRes Res;

	void InputLayOutCreate();
};

