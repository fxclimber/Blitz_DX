#pragma once
#include "EngineResources.h"

#include "ThirdParty/DirectxTex/Inc/DirectXTex.h"

// 설명 :
class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineTexture();
	ENGINEAPI ~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path)
	{
		UEnginePath EnginePath = UEnginePath(_Path);

		std::string FileName = EnginePath.GetFileName();

		return Load(FileName, _Path);
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = ToUpperName(_Name);

		if (true == Contains(UpperName))
		{
			MSGASSERT("이미 로드한 텍스처를 도 로드하려고 했습니다." + UpperName);
			return nullptr;
		}

		std::shared_ptr<UEngineTexture> NewTexture = MakeRes(_Name, _Path);
		NewTexture->ResLoad();
		return NewTexture;
	}

	ID3D11ShaderResourceView* GetSRV()
	{
		return SRV.Get();
	}

protected:

private:
	ENGINEAPI void ResLoad();

	Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D = nullptr; // 로드한 텍스처
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV = nullptr; // 텍스처를 쉐이더 세팅할수 있는권한
};
