#include "PreCompile.h"
#include "EngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_Debug.lib")
#else
#pragma comment(lib, "DirectXTex_Release.lib")
#endif

UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
}

void UEngineTexture::ResLoad()
{
	UEngineFile File = Path;

	std::string Str = File.GetPathToString();
	std::string Ext = File.GetExtension();
	std::wstring wLoadPath = UEngineString::AnsiToUnicode(Str.c_str());
	std::string UpperExt = UEngineString::ToUpper(Ext.c_str());

	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage ImageData;

	if (UpperExt == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wLoadPath.c_str(), DirectX::DDS_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT("DDS 파일 로드에 실패했습니다.");
			return;
		}
	}
	else if (UpperExt == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wLoadPath.c_str(), DirectX::TGA_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT("TGA 파일 로드에 실패했습니다.");
			return;
		}
	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(wLoadPath.c_str(), DirectX::WIC_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT(UpperExt + "파일 로드에 실패했습니다.");
			return;
		}
	}

	if (S_OK != DirectX::CreateShaderResourceView(
		UEngineCore::Device.GetDevice(),
		ImageData.GetImages(),
		ImageData.GetImageCount(),
		ImageData.GetMetadata(),
		SRV.GetAddressOf()
	))
	{
		MSGASSERT(UpperExt + "쉐이더 리소스 뷰 생성에 실패했습니다..");
		return;
	}
}