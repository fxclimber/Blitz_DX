#include "PreCompile.h"
#include "RenderUnit.h"
#include "EngineEnums.h"
#include "Renderer.h"

URenderUnit::URenderUnit()
{
}

URenderUnit::~URenderUnit()
{
}



//}

//void URenderer::ShaderResSetting()
//{
//	{
//		FTransform& RendererTrans = GetTransformRef();
//		D3D11_MAPPED_SUBRESOURCE Data = {};
//		// �� �����͸� ����ϴ� ������ ������ ��� ����
//		// ��� �׷���ī��� �� �׷���ī�忡 �ִ� ������� �����ؾ� ��.
//		UEngineCore::GetDevice().GetContext()->Map(TransformConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//		// Data.pData �׷���ī��� ����� �ּҰ�.
//		if (nullptr == Data.pData)
//		{
//			MSGASSERT("�׷���ī�尡 ������ �ź��߽��ϴ�.");
//		}
//		memcpy_s(Data.pData, sizeof(FTransform), &RendererTrans, sizeof(FTransform));
//		UEngineCore::GetDevice().GetContext()->Unmap(TransformConstBuffer.Get(), 0);
//
//		// ���� ������۸� 
//		ID3D11Buffer* ArrPtr[16] = { TransformConstBuffer.Get() };
//		UEngineCore::GetDevice().GetContext()->VSSetConstantBuffers(0, 1, ArrPtr);
//	}
//
//	{
//		D3D11_MAPPED_SUBRESOURCE Data = {};
//		// �� �����͸� ����ϴ� ������ ������ ��� ����
//		// ��� �׷���ī��� �� �׷���ī�忡 �ִ� ������� �����ؾ� ��.
//		UEngineCore::GetDevice().GetContext()->Map(UVValue.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//		// Data.pData �׷���ī��� ����� �ּҰ�.
//		if (nullptr == Data.pData)
//		{
//			MSGASSERT("�׷���ī�尡 ������ �ź��߽��ϴ�.");
//		}
//		memcpy_s(Data.pData, sizeof(FUVValue), &UVValueData, sizeof(FUVValue));
//		UEngineCore::GetDevice().GetContext()->Unmap(UVValue.Get(), 0);
//
//		// ���� ������۸� 
//		ID3D11Buffer* ArrPtr[16] = { UVValue.Get() };
//		UEngineCore::GetDevice().GetContext()->VSSetConstantBuffers(2, 1, ArrPtr);
//	}
//
//	{
//		D3D11_MAPPED_SUBRESOURCE Data = {};
//		// �� �����͸� ����ϴ� ������ ������ ��� ����
//		// ��� �׷���ī��� �� �׷���ī�忡 �ִ� ������� �����ؾ� ��.
//		UEngineCore::GetDevice().GetContext()->Map(SpriteConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//		// Data.pData �׷���ī��� ����� �ּҰ�.
//		if (nullptr == Data.pData)
//		{
//			MSGASSERT("�׷���ī�尡 ������ �ź��߽��ϴ�.");
//		}
//		memcpy_s(Data.pData, sizeof(FSpriteData), &SpriteData, sizeof(FSpriteData));
//		UEngineCore::GetDevice().GetContext()->Unmap(SpriteConstBuffer.Get(), 0);
//
//		// ���� ������۸� 
//		ID3D11Buffer* ArrPtr[16] = { SpriteConstBuffer.Get() };
//		UEngineCore::GetDevice().GetContext()->VSSetConstantBuffers(1, 1, ArrPtr);
//	}
//
//
//
//
//	ID3D11ShaderResourceView* ArrSRV[16] = { Texture->GetSRV() };
//	UEngineCore::GetDevice().GetContext()->PSSetShaderResources(0, 1, ArrSRV);
//
//	ID3D11SamplerState* ArrSMP[16] = { SamplerState.Get() };
//	UEngineCore::GetDevice().GetContext()->PSSetSamplers(0, 1, ArrSMP);
//}
//
//void URenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
//{
//	FTransform& CameraTrans = _Camera->GetTransformRef();
//	FTransform& RendererTrans = GetTransformRef();
//
//	// �������� ���� �� ������Ʈ�� �� ���ù޾Ұ�
//	RendererTrans.View = CameraTrans.View;
//	RendererTrans.Projection = CameraTrans.Projection;
//	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;
//
//	if (nullptr == Mesh)
//	{
//		MSGASSERT("�Ž��� ���õ��� �ʾƼ� �������� �Ҽ� �����ϴ�.");
//		return;
//	}
//
//	ShaderResSetting();
//	InputAssembler1Setting();
//	VertexShaderSetting();
//	InputAssembler2Setting();
//	RasterizerSetting();
//	PixelShaderSetting();
//	OutPutMergeSetting();
//
//	// �ε��� ���۸� ���ؼ� �׸��ڴ�.
//	UEngineCore::GetDevice().GetContext()->DrawIndexed(6, 0, 0);
//
//	// UEngineCore::GetDevice().GetContext()->DrawIndexedInstanced(6, 0, 0);
//
//}
//
//
////
////void URenderer::InputAssembler1Init()
////{
////	std::vector<EngineVertex> Vertexs;
////	Vertexs.resize(4);
////
////	Vertexs[0] = EngineVertex{ FVector(-0.5f, 0.5f, -0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
////	Vertexs[1] = EngineVertex{ FVector(0.5f, 0.5f, -0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
////	Vertexs[2] = EngineVertex{ FVector(-0.5f, -0.5f, -0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
////	Vertexs[3] = EngineVertex{ FVector(0.5f, -0.5f, -0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };
////
////	D3D11_BUFFER_DESC BufferInfo = {0};
////
////	BufferInfo.ByteWidth = sizeof(EngineVertex) * static_cast<int>(Vertexs.size());
////	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
////	BufferInfo.CPUAccessFlags = 0;
////	BufferInfo.Usage = D3D11_USAGE_DEFAULT;
////
////	D3D11_SUBRESOURCE_DATA Data; // �ʱⰪ �־��ִ� �뵵�� ����ü
////	Data.pSysMem = &Vertexs[0];
////
////	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, &Data, VertexBuffer.GetAddressOf()))
////	{
////		MSGASSERT("���ؽ� ���� ������ �����߽��ϴ�.");
////		return;
////	}
////}
//
//void URenderer::InputAssembler1Setting()
//{
//	Mesh->GetVertexBuffer()->Setting();
//	UEngineCore::GetDevice().GetContext()->IASetInputLayout(InputLayOut.Get());
//	//UINT VertexSize = sizeof(EngineVertex);
//	//// �� ���ؽ� ���۰� 10��¥���ε� 3��° ���ؽ� ���� ��������.
//	//UINT Offset = 0;
//	//ID3D11Buffer* ArrBuffer[1];
//	//ArrBuffer[0] = VertexBuffer.Get();
//	//UEngineCore::GetDevice().GetContext()->IASetVertexBuffers(0, 1, ArrBuffer, &VertexSize, &Offset);
//}
//
//void URenderer::InputAssembler1LayOut()
//{
//	std::vector<D3D11_INPUT_ELEMENT_DESC> InputLayOutData;
//
//	{
//		D3D11_INPUT_ELEMENT_DESC Desc;
//		Desc.SemanticName = "POSITION";
//		Desc.InputSlot = 0;
//		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//		Desc.AlignedByteOffset = 0;
//		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
//
//		// �ν��Ͻ��� �����Ҷ� �̾߱� �ϰڽ��ϴ�.
//		Desc.SemanticIndex = 0;
//		Desc.InstanceDataStepRate = 0;
//		InputLayOutData.push_back(Desc);
//	}
//
//
//	{
//		D3D11_INPUT_ELEMENT_DESC Desc;
//		Desc.SemanticName = "TEXCOORD";
//		Desc.InputSlot = 0;
//		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//		Desc.AlignedByteOffset = 16;
//		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
//
//		Desc.SemanticIndex = 0;
//		Desc.InstanceDataStepRate = 0;
//		InputLayOutData.push_back(Desc);
//	}
//
//
//
//
//	{
//		D3D11_INPUT_ELEMENT_DESC Desc;
//		Desc.SemanticName = "COLOR";
//		Desc.InputSlot = 0;
//		Desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
//		Desc.AlignedByteOffset = 32;
//		Desc.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
//
//		Desc.SemanticIndex = 0;
//		Desc.InstanceDataStepRate = 0;
//		InputLayOutData.push_back(Desc);
//	}
//
//
//  �����ϰ� ��ǲ���̾ƿ��� 
//  ���ؽ����ۿ� ���ؽ����̴��� ���ļ� ������ �Ѵ�.
//	// ���̴����� � ��ǲ���̾ƿ��� ����ϴ��� �˷���.
//	HRESULT Result = UEngineCore::GetDevice().GetDevice()->CreateInputLayout(
//		&InputLayOutData[0],
//		static_cast<unsigned int>(InputLayOutData.size()),
//		VSShaderCodeBlob->GetBufferPointer(),
//		VSShaderCodeBlob->GetBufferSize(),
//		&InputLayOut);
//
//	if (S_OK != Result)
//	{
//		MSGASSERT("��ǲ ���̾ƿ� ������ �����߽��ϴ�");
//	}
//}
//
//
//void URenderer::VertexShaderInit()
//{
//	UEngineDirectory CurDir;
//	CurDir.MoveParentToDirectory("EngineShader");
//	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");
//
//	std::string Path = File.GetPathToString();
//	std::wstring WPath = UEngineString::AnsiToUnicode(Path);
//
//	std::string version = "vs_5_0";
//	int Flag0 = 0;
//	int Flag1 = 0;
//
//#ifdef _DEBUG
//	Flag0 = D3D10_SHADER_DEBUG;
//#endif
//
//	// ����� ����ְ� �ɰ��̴�.
//	// ���� �������ٰ��ϴ� �ϴµ� �������� �����ϴ�.
//	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
//
//	D3DCompileFromFile(
//		WPath.c_str(),
//		nullptr, // Define TEST ������ ��ó���⸦ ������.
//		nullptr,
//		"VertexToWorld",
//		version.c_str(),
//		Flag0,
//		Flag1,
//		&VSShaderCodeBlob,
//		&VSErrorCodeBlob
//	);
//
//	if (nullptr == VSShaderCodeBlob)
//	{
//		std::string ErrString = reinterpret_cast<char*>(VSErrorCodeBlob->GetBufferPointer());
//		MSGASSERT("���̴� �ڵ� �߰����忡�� �����߽��ϴ�\n" + ErrString);
//		return;
//	}
//
//	HRESULT Result = UEngineCore::GetDevice().GetDevice()->CreateVertexShader(
//		VSShaderCodeBlob->GetBufferPointer(),
//		VSShaderCodeBlob->GetBufferSize(),
//		nullptr,
//		&VertexShader
//	);
//
//	if (S_OK != Result)
//	{
//		MSGASSERT("���ؽ� ���̴� ������ �����߽��ϴ�.");
//	}
//
//	InputAssembler1LayOut();
//}
//
//void URenderer::VertexShaderSetting()
//{
//	UEngineCore::GetDevice().GetContext()->VSSetShader(VertexShader.Get(), nullptr, 0);
//}
//
//void URenderer::RasterizerInit()
//{
//	D3D11_RASTERIZER_DESC Desc = {};
//	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
//	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
//	UEngineCore::GetDevice().GetDevice()->CreateRasterizerState(&Desc, &RasterizerState);
//
//
//
//}
//
//
//void URenderer::RasterizerSetting()
//{
//	UEngineCore::GetDevice().GetContext()->RSSetState(RasterizerState.Get());
//}

//void URenderer::InputAssembler2Init()
//{
//	std::vector<unsigned int> Indexs;
//
//	Indexs.push_back(0);
//	Indexs.push_back(1);
//	Indexs.push_back(2);
//
//	Indexs.push_back(1);
//	Indexs.push_back(3);
//	Indexs.push_back(2);
//
//
//	D3D11_BUFFER_DESC BufferInfo = { 0 };
//	BufferInfo.ByteWidth = sizeof(unsigned int) * static_cast<int>(Indexs.size());
//	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	BufferInfo.CPUAccessFlags = 0;
//	BufferInfo.Usage = D3D11_USAGE_DEFAULT;
//	D3D11_SUBRESOURCE_DATA Data;
//	Data.pSysMem = &Indexs[0];
//	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, &Data, &IndexBuffer))
//	{
//		MSGASSERT("�ε��� ���� ������ �����߽��ϴ�.");
//		return;
//	}
//}

//void URenderer::InputAssembler2Setting()
//{

	// Mesh->GetIndexBuffer()->Setting();

	// int Offset = 0;
	//// DXGI_FORMAT_R8_UINT; <= �������� �Ʋ���.
	//// DXGI_FORMAT_R16_UINT; <= �������� �Ʋ���.
	//UEngineCore::GetDevice().GetContext()->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, Offset);

	// UEngineCore::GetDevice().GetContext()->IASetPrimitiveTopology(Topology);
// }



//void URenderer::PixelShaderInit()
//{
//	UEngineDirectory CurDir;
//	CurDir.MoveParentToDirectory("EngineShader");
//	UEngineFile File = CurDir.GetFile("EngineSpriteShader.fx");
//
//	std::string Path = File.GetPathToString();
//	std::wstring WPath = UEngineString::AnsiToUnicode(Path);
//	std::string version = "ps_5_0";
//
//	int Flag0 = 0;
//	int Flag1 = 0;
//
//#ifdef _DEBUG
//	Flag0 = D3D10_SHADER_DEBUG;
//#endif
//
//	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
//
//	D3DCompileFromFile(
//		WPath.c_str(),
//		nullptr, // Define TEST ������ ��ó���⸦ ������.
//		nullptr,
//		"PixelToWorld",
//		version.c_str(),
//		Flag0,
//		Flag1,
//		&PSShaderCodeBlob,
//		&PSErrorCodeBlob
//	);
//
//	if (nullptr == PSShaderCodeBlob)
//	{
//		std::string ErrString = reinterpret_cast<char*>(PSErrorCodeBlob->GetBufferPointer());
//		MSGASSERT("���̴� �ڵ� �߰����忡�� �����߽��ϴ�\n" + ErrString);
//		return;
//	}
//
//	HRESULT Result = UEngineCore::GetDevice().GetDevice()->CreatePixelShader(
//		PSShaderCodeBlob->GetBufferPointer(),
//		PSShaderCodeBlob->GetBufferSize(),
//		nullptr,
//		&PixelShader
//	);
//
//	if (S_OK != Result)
//	{
//		MSGASSERT("�ȼ� ���̴� ������ �����߽��ϴ�.");
//	}
//}
//
//void URenderer::PixelShaderSetting()
//{
//	UEngineCore::GetDevice().GetContext()->PSSetShader(PixelShader.Get(), nullptr, 0);
//}
//
//void URenderer::OutPutMergeSetting()
//{
//	if (nullptr != Blend)
//	{
//		Blend->Setting();
//	}
//
//	// �迭 �־��ټ� �ִ�. 
//	// 0���̸� sv_target0
//	ID3D11RenderTargetView* RTV = UEngineCore::GetDevice().GetRTV();
//
//	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
//	ArrRtv[0] = RTV; // SV_Target0
//
//	UEngineCore::GetDevice().GetContext()->OMSetRenderTargets(1, &ArrRtv[0], nullptr);
//}
//
//void URenderer::SetSpriteData(UEngineSprite* _Sprite, size_t _Index)
//{
//	SpriteData = _Sprite->GetSpriteData(_Index);
//}
//
//void URenderer::AddUVPlusValue(float4 _Value)
//{
//	UVValueData.PlusUVValue += _Value;
//}
//
//void URenderer::SetMesh(std::string_view _Name)
//{
//	std::shared_ptr<UMesh> FindMesh = UMesh::Find<UMesh>(_Name);
//
//	Mesh = FindMesh.get();
//
//	if (nullptr == Mesh)
//	{
//		MSGASSERT("�������� �ʴ� �Ž��� �����Ҽ� �����ϴ�.\n");
//	}
//}
//
//void URenderer::SetBlend(std::string_view _Name)
//{
//	std::shared_ptr<UEngineBlend> FindBlend = UEngineBlend::Find<UEngineBlend>(_Name);
//
//	Blend = FindBlend.get();
//
//	if (nullptr == Blend)
//	{
//		MSGASSERT("�������� �ʴ� Blend�� �����Ҽ� �����ϴ�.\n");
//	}
//}

void URenderUnit::MaterialResourcesCheck()
{
	if (nullptr == Material)
	{
		MSGASSERT("�������� �ʴ� ��Ƽ������ ���ҽ��� üũ�� �� �����ϴ�.");
		return;
	}

	{
		UEngineShaderResources& Vs = Material->GetVertexShader()->ShaderResources;
		Resources[EShaderType::VS] = Material->GetVertexShader()->ShaderResources;
	}

	{
		UEngineShaderResources& Ps = Material->GetPixelShader()->ShaderResources;
		Resources[EShaderType::PS] = Material->GetPixelShader()->ShaderResources;
	}

	if (nullptr != ParentRenderer)
	{
		for (EShaderType i = EShaderType::VS; i < EShaderType::MAX; i = static_cast<EShaderType>(static_cast<int>(i) + 1))
		{
			if (false == Resources.contains(i))
			{
				continue;
			}

			FTransform& Ref = ParentRenderer->GetTransformRef();
			Resources[i].ConstantBufferLinkData("FTransform", Ref);
		}

	}
}

void URenderUnit::ConstantBufferLinkData(std::string_view _Name, void* _Data)
{
	for (EShaderType i = EShaderType::VS; i < EShaderType::MAX; i = static_cast<EShaderType>(static_cast<int>(i) + 1))
	{
		if (false == Resources.contains(i))
		{
			continue;
		}

		if (false == Resources[i].IsConstantBuffer(_Name))
		{
			continue;
		}

		Resources[i].ConstantBufferLinkData(_Name, _Data);
	}
}

void URenderUnit::SetTexture(std::string_view _Name, std::string_view _ResName)
{
	for (EShaderType i = EShaderType::VS; i < EShaderType::MAX; i = static_cast<EShaderType>(static_cast<int>(i) + 1))
	{
		if (false == Resources.contains(i))
		{
			continue;
		}

		if (false == Resources[i].IsTexture(_Name))
		{
			continue;
		}

		Resources[i].TextureSetting(_Name, _ResName);
	}
}

void URenderUnit::SetSampler(std::string_view _Name, std::string_view _ResName)
{
	for (EShaderType i = EShaderType::VS; i < EShaderType::MAX; i = static_cast<EShaderType>(static_cast<int>(i) + 1))
	{
		if (false == Resources.contains(i))
		{
			continue;
		}

		if (false == Resources[i].IsSampler(_Name))
		{
			continue;
		}

		Resources[i].SamplerSetting(_Name, _ResName);
	}
}

void URenderUnit::SetMesh(std::string_view _Name)
{
	Mesh = UMesh::Find<UMesh>(_Name);

	if (nullptr == Mesh)
	{
		MSGASSERT("�������� �ʴ� �Ž��� �����Ϸ��� �߽��ϴ�.");
	}

	if (nullptr != Material)
	{
		InputLayOutCreate();
	}
}

void URenderUnit::SetMaterial(std::string_view _Name)
{
	Material = UEngineMaterial::Find<UEngineMaterial>(_Name);

	if (nullptr == Material)
	{
		MSGASSERT("�������� �ʴ� ��Ƽ�������� �����Ϸ��� �߽��ϴ�.");
	}

	MaterialResourcesCheck();

	// UEngineConstantBufferRes Res;

	if (nullptr != Mesh)
	{
		InputLayOutCreate();

	}


}

void URenderUnit::Render(class UEngineCamera* _Camera, float _DeltaTime)
{
	// ��ǲ������� 

	// ���̴� ���ҽ�

	//	ShaderResSetting();

	//for (std::pair<EShaderType, UEngineShaderResources>& ShaderRes : Resources)
	//{
	//	UEngineShaderResources& Res = ShaderRes.second;
	//	Res.Setting();
	//}


	for (std::pair<const EShaderType, UEngineShaderResources>& Pair : Resources)
	{
		Pair.second.Setting();
	}

	//	InputAssembler1Setting();
	Mesh->GetVertexBuffer()->Setting();

	//	VertexShaderSetting();
	Material->GetVertexShader()->Setting();

	//	InputAssembler2Setting();
	Mesh->GetIndexBuffer()->Setting();
	Material->PrimitiveTopologySetting();

	UEngineCore::GetDevice().GetContext()->IASetInputLayout(InputLayOut.Get());

	//	RasterizerSetting();
	Material->GetRasterizerState()->Setting();

	//	PixelShaderSetting();
	Material->GetPixelShader()->Setting();

	//	OutPutMergeSetting();
	// ����Ÿ���̶�� ���� �ٲ�̴ϴ�.
	Material->GetBlend()->Setting();
	ID3D11RenderTargetView* RTV = UEngineCore::GetDevice().GetRTV();
	ID3D11RenderTargetView* ArrRtv[16] = { 0 };
	ArrRtv[0] = RTV; // SV_Target0
	UEngineCore::GetDevice().GetContext()->OMSetRenderTargets(1, &ArrRtv[0], nullptr);

	UEngineCore::GetDevice().GetContext()->DrawIndexed(Mesh->GetIndexBuffer()->GetIndexCount(), 0, 0);
}

void URenderUnit::InputLayOutCreate()
{
	Microsoft::WRL::ComPtr<ID3DBlob> Blob = Material->GetVertexShader()->GetShaderCodeBlob();

	UEngineInputLayOutInfo* InfoPtr = Mesh->GetVertexBuffer()->GetInfoPtr();

	HRESULT Result = UEngineCore::GetDevice().GetDevice()->CreateInputLayout(
		&InfoPtr->InputLayOutData[0],
		static_cast<unsigned int>(InfoPtr->InputLayOutData.size()),
		Blob->GetBufferPointer(),
		Blob->GetBufferSize(),
		&InputLayOut);

	int a = 0;
}