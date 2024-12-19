#pragma once
#include "SceneComponent.h"

struct EngineVertex
{
	float4 COLOR;
	float4 POSITION;
};

// 설명 :
class URenderer : public USceneComponent
{
	friend class ULevel;

public:
	// constrcuter destructer
	ENGINEAPI URenderer();
	ENGINEAPI ~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;

protected:
	ENGINEAPI void BeginPlay() override;

private:
	virtual void Render(float _DeltaTime);

public:
	ID3D11Buffer* VertexBuffer = nullptr;
	void InputAssembler1Init();
	void InputAssembler1Setting();

	// 점에 행렬곱해주는(변형시키는 단계) 단계입니다.
	// 그걸 내가 코딩해서 다 짜줘야한다.
	// HLSL이라는 인터프린터 언어를 이용해서 내가 새로운 언어를 배워서 다 짜야합니다.

	ID3DBlob* ShaderCodeBlob = nullptr;
	ID3DBlob* ErrorCodeBlob = nullptr; // 중간 컴파일 결과물
	ID3D11VertexShader* VertexShader = nullptr;
	void VertexShaderInit();
	void VertexShaderSetting();
};

