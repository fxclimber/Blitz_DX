#pragma once
#include "EngineConstantBuffer.h"

class UEngineConstantBufferRes
{
public:
	void* Data; // 자신에게 세팅될 데이터는 스스로 가지고 있을 것이다.
	UINT BufferSize;
	std::shared_ptr<UEngineConstantBuffer> Res;
};

// Render가 2개 만들었다.
// Renderer1
// 빨갛게 그리고 싶다.
// 
// Renderer2
// 노랗게 그리고 싶어.

// 설명 : 애가 쉐이더를 검색해서 
// 각 랜더러마다 세팅해야할 값이 다르죠?
// 이녀석의 역할을 크게 2가지 입니다.

// 쉐이더가 가지고 있는 건 만들어야할 쉐이더 리소스를 보관하는 역할
// 랜더러가 가지고 있는 건 그렇게 해서 조사된 리소스들의 데이터를 보관하는 역할로 가지고 있을 겁니다.
class UEngineShaderResources
{
	// 

public:
	// constrcuter destructer
	UEngineShaderResources();
	~UEngineShaderResources();

	// delete Function
	UEngineShaderResources(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources(UEngineShaderResources&& _Other) noexcept = delete;
	UEngineShaderResources& operator=(const UEngineShaderResources& _Other) = delete;
	UEngineShaderResources& operator=(UEngineShaderResources&& _Other) noexcept = delete;

	void CreateConstantBufferRes(std::string_view Name, UEngineConstantBufferRes Res);

protected:

private:
	std::map<std::string, UEngineConstantBufferRes> ConstantBufferRess;
	// std::map<std::string, UEngineConstantBufferRes> TextureSetters;
	// std::map<std::string, UEngineConstantBufferRes> ConstantBufferSetters;
	// std::map<std::string, UEngineConstantBufferRes> ConstantBufferSetters;

};

