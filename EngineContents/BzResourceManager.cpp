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



}
