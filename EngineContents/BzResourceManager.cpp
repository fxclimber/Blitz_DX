#include "PreCompile.h"
#include "BzCore.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include <EngineCore/EngineTexture.h>
#include "MyCustomRenderer.h"


void UBzCore::ResourceSetting()
{

	{
		// shader project name
		UEngineDirectory CurDir;
		CurDir.MoveParentToDirectory("ContentsShader");
		// shader extension
		std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

		for (size_t i = 0; i < ShaderFiles.size(); i++)
		{
			UEngineShader::ReflectionCompile(ShaderFiles[i]);
		}
	}

	{
		// default Material 
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("BzDefault");
		Mat->SetVertexShader("BlitzShaderDefault.hlsl");
		Mat->SetPixelShader("BlitzShaderDefault.hlsl");
	}
	{
		// uv Material 
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("BzUV");
		Mat->SetVertexShader("BzShaderUV.hlsl");
		Mat->SetPixelShader("BzShaderUV.hlsl");
	}

	// 텍스쳐들 로드 -------------------------------------------------------
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image");// 내부폴더 추가 
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);//텍스쳐들 전부 로드 
		}
	}
	// 메타정보 읽어들이려고 
	UEngineSprite::CreateSpriteToMeta("Player.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("TileMap.png", ".sdata");


	{// 폴더별 분리된 스프라이트 
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Tevi");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}
	//-----------------------
	// 스프라이트렌더러용 임시, 로직완성후 삭제,변경할것 

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/TileSet");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyMaterial");
		Mat->SetVertexShader("TestShader.fx");
		Mat->SetPixelShader("TestShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyCollisionDebugMaterial");
		Mat->SetVertexShader("EngineDebugCollisionShader.fx");
		Mat->SetPixelShader("EngineDebugCollisionShader.fx");
		// 언제나 화면에 나오는 누구도 이녀석의 앞을 가릴수 없어.
		Mat->SetDepthStencilState("CollisionDebugDepth");
		Mat->SetRasterizerState("CollisionDebugRas");
	}









}
