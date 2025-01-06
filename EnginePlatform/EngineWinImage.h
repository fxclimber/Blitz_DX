#pragma once
#include <Windows.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/Object.h>

class UEngineWinImage : public UObject
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineWinImage();
	ENGINEAPI ~UEngineWinImage();

	// delete Function
	UEngineWinImage(const UEngineWinImage& _Other) = delete;
	UEngineWinImage(UEngineWinImage&& _Other) noexcept = delete;
	UEngineWinImage& operator=(const UEngineWinImage& _Other) = delete;
	UEngineWinImage& operator=(UEngineWinImage&& _Other) noexcept = delete;

	// void Load(std::string_view _Path);
	ENGINEAPI HDC GetDC()
	{
		return ImageDC;
	}
	
	// 이미 만들어진 DC를 통해서 이미지를 만드는 타입
	ENGINEAPI void Create(HDC _DC)
	{
		ImageDC = _DC;
	}

	ENGINEAPI void Create(UEngineWinImage* _TargetImage, FVector _Scale);

	// bit블릿은 크기 조절아됩니다. 
	ENGINEAPI void CopyToBit(UEngineWinImage* _TargetImage,
		const FTransform& _Trans);

	// 트랜스 페어런츠 블릿을 사용한다.
	// 색깔제외도 되고 이미지 일부분만 처리하는 것도 된다.
	// 이미지의 어느 부분을 그릴지 정확하게 표현하기 위해서
	// 트랜스 폼이 하나더 필요합니다.
	ENGINEAPI void CopyToTrans(UEngineWinImage* _TargetImage,
		const FTransform& _RenderTrans, 
		const FTransform& _LTImageTrans,
		UColor _Color = UColor(255, 0, 255, 0));

	ENGINEAPI void CopyToAlpha(UEngineWinImage* _TargetImage,
		const FTransform& _RenderTrans,
		const FTransform& _LTImageTrans,
		unsigned char _Alpha);


	ENGINEAPI void Load(UEngineWinImage* _TargetImage, std::string_view _Path);

	// 이미지 크기를 리턴
	ENGINEAPI FVector GetImageScale() const
	{
		return { Info.bmWidth, Info.bmHeight };
	}

	ENGINEAPI UColor GetColor(FVector _Point, UColor _DefaultColor = UColor::WHITE)
	{
		return GetColor(_Point.ConvertToPoint(), _DefaultColor);
	}

	ENGINEAPI UColor GetColor(FIntPoint _Point, UColor _DefaultColor);

protected:

private:
	// BMP 이미지 파일 그 자체에요
	// FVector Size;
	HDC ImageDC = nullptr;
	HBITMAP hBitMap = nullptr;

	// 이미지 정보 얻어오기
	BITMAP Info;
};

