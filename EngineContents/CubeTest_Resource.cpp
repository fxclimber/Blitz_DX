#include "PreCompile.h"
#include "CubeTest_Core.h"
#include "CubeTest_Renderer.h"

#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include <EngineCore/EngineTexture.h>



void UCubeTest_Core::ResourceSetting()
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
		// uv Material 
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("CubeTestMaterial");
		Mat->SetVertexShader("CubeTestShaderUV.hlsl");
		Mat->SetPixelShader("CubeTestShaderUV.hlsl");
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

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyCollisionDebugMaterial");
		Mat->SetVertexShader("EngineDebugCollisionShader.fx");
		Mat->SetPixelShader("EngineDebugCollisionShader.fx");
		// ������ ȭ�鿡 ������ ������ �̳༮�� ���� ������ ����.
		Mat->SetDepthStencilState("CollisionDebugDepth");
		Mat->SetRasterizerState("CollisionDebugRas");
	}


};



