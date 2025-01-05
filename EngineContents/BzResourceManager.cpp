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
		// Create Material 
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("BzDefault");
		Mat->SetVertexShader("BlitzShaderDefault.hlsl");
		Mat->SetPixelShader("BlitzShaderDefault.hlsl");
	}
	{
		//std::shared_ptr<UEngineMaterial> MatSprite = UEngineMaterial::Create("EngineSprite");
		//MatSprite->SetVertexShader("EngineSpriteShader.fx");
		//MatSprite->SetPixelShader("EngineSpriteShader.fx");
	}





}
