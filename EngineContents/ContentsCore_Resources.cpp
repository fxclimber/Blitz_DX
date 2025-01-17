#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineGraphicDevice.h>
#include <EngineCore/EngineVertex.h>
#include <EngineCore/EngineIndexBuffer.h>
#include <EngineCore/Mesh.h>
#include <EngineCore/EngineBlend.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>

#include <EnginePlatform/EngineThread.h>



void UContentsCore::MyGSetting()
{


	int Count = 24;
	{
		std::vector<FEngineVertex> Vertexs = {
			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f },  {1.0f, 0.0f, 0.0f, 1.f} }, //»¡°­
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f} },
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f} },

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f },  {1.0f, 0.0f, 1.0f, 1.0f} }, //¸¶Á¨Å¸
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.f} }, //µÞ¸é »¡°­
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f }, {1.0f, 0.0f, 0.0f, 1.f}},
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 0.0f, 1.f}},

			FEngineVertex{ FVector(0.0f, 0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 1.0f, 1.0f} }, //µÞ¸é ¸¶Á¨Å¸
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,{1.0f, 0.0f, 1.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } , {1.0f, 0.0f, 1.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f} }, //¾Õ¸é ³ë¶û
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}},
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f}},
			FEngineVertex{ FVector(0.0f, 0.0f, -0.5f), {0.0f , 1.0f } , {0.0f, 1.0f, 0.0f, 1.0f}},

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f} }, //
			FEngineVertex{ FVector(-0.5f, 0.0f, 0.0f), {0.0f , 1.0f } , {1.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } ,  {1.0f, 1.0f, 0.0f, 1.0f}},

			FEngineVertex{ FVector(0.0f, -0.7f, 0.0f), {0.0f , 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.5f, 0.0f, 0.0f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f} },
			FEngineVertex{ FVector(0.0f, 0.0f, 0.5f), {0.0f , 1.0f } ,  {0.0f, 1.0f, 0.0f, 1.0f} },
		};
		UEngineVertexBuffer::Create("Test", Vertexs);
	}

	{
		std::vector<unsigned int> Indexs;

		for (int i = 0; i < Count; i++)
		{
			Indexs.push_back(i);
		}

		UEngineIndexBuffer::Create("Test", Indexs);
	}

	{
		UMesh::Create("Test");
	}

	{
		UEngineDirectory CurDir;
		CurDir.MoveParentToDirectory("ContentsShader");

		std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

		for (size_t i = 0; i < ShaderFiles.size(); i++)
		{
			UEngineShader::ReflectionCompile(ShaderFiles[i]);
		}
	}

	// ·Îµù¿ë ¸®¼Ò½º
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("Test");
		Mat->SetVertexShader("TestShader2.fx");
		Mat->SetPixelShader("TestShader2.fx");
	}







}
