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

	// �ؽ��ĵ� �ε� -------------------------------------------------------
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image");// �������� �߰� 
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);//�ؽ��ĵ� ���� �ε� 
		}
	}
	// ��Ÿ���� �о���̷��� 
	UEngineSprite::CreateSpriteToMeta("Player.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("TileMap.png", ".sdata");


	{// ������ �и��� ��������Ʈ 
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image/Tevi");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}
	//-----------------------
	// ��������Ʈ�������� �ӽ�, �����ϼ��� ����,�����Ұ� 

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
		// ������ ȭ�鿡 ������ ������ �̳༮�� ���� ������ ����.
		Mat->SetDepthStencilState("CollisionDebugDepth");
		Mat->SetRasterizerState("CollisionDebugRas");
	}









}
