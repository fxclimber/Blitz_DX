#pragma once
#include "EngineConstantBuffer.h"
#include <EngineBase/Object.h>
#include "EngineTexture.h"
#include "EngineSampler.h"

class UEngineShaderRes
{
public:
	std::string Name;
	EShaderType ShaderType = EShaderType::MAX;
	UINT BindIndex = 0;
};

class UEngineConstantBufferRes : public UEngineShaderRes
{
public:
	void* Data = nullptr; // 자신에게 세팅될 데이터는 스스로 가지고 있을 것이다.
	UINT BufferSize;
	std::shared_ptr<UEngineConstantBuffer> Res;

	void Setting()
	{
		if (nullptr != Data)
		{
			Name;
			Res->ChangeData(Data, BufferSize);
		}

		Res->Setting(ShaderType, BindIndex);
	}
};

class UEngineTextureRes : public UEngineShaderRes
{
public:
	UEngineTexture* Res;

	void Setting()
	{
		Res->Setting(ShaderType, BindIndex);
	}
};

class UEngineSamplerRes : public UEngineShaderRes
{
public:
	std::shared_ptr<UEngineSampler> Res;

	void Setting()
	{
		Res->Setting(ShaderType, BindIndex);
	}

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
	// 이녀석은 복사를 직접적으로 해볼것이다.
	//UEngineShaderResources(const UEngineShaderResources& _Other) = delete;
	//UEngineShaderResources(UEngineShaderResources&& _Other) noexcept = delete;
	//UEngineShaderResources& operator=(const UEngineShaderResources& _Other) = delete;
	//UEngineShaderResources& operator=(UEngineShaderResources&& _Other) noexcept = delete;

	void CreateSamplerRes(std::string_view _Name, UEngineSamplerRes _Res);

	void CreateTextureRes(std::string_view _Name, UEngineTextureRes _Res);

	void CreateConstantBufferRes(std::string_view _Name, UEngineConstantBufferRes Res);

	template<typename DataType>
	void ConstantBufferLinkData(std::string_view _Name, DataType& Data)
	{
		ConstantBufferLinkData(_Name, reinterpret_cast<void*>(&Data));
	}

	void ConstantBufferLinkData(std::string_view _Name, void* Data);

	void SamplerSetting(std::string_view _Name, std::string_view _ResName);
	void TextureSetting(std::string_view _Name, std::string_view _ResName);
	void TextureSetting(std::string_view _Name, std::shared_ptr<UEngineTexture> _Texture);

	void TextureSetting(std::string_view _Name, UEngineTexture* _Texture);

	bool IsSampler(std::string_view _Name);
	bool IsTexture(std::string_view _Name);
	bool IsConstantBuffer(std::string_view _Name);
	void Setting();

protected:

private:
	std::map<std::string, UEngineConstantBufferRes> ConstantBufferRes;
	std::map<std::string, UEngineTextureRes> TextureRes;
	std::map<std::string, UEngineSamplerRes> SamplerRes;
	// std::map<std::string, UEngineConstantBufferRes> ConstantBufferSetters;

};

