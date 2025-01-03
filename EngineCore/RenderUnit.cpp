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
//		// 이 데이터를 사용하는 랜더링 랜더링 잠깐 정지
//		// 잠깐 그래픽카드야 멈 그래픽카드에 있는 상수버퍼 수정해야 해.
//		UEngineCore::GetDevice().GetContext()->Map(TransformConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//		// Data.pData 그래픽카드와 연결된 주소값.
//		if (nullptr == Data.pData)
//		{
//			MSGASSERT("그래픽카드가 수정을 거부했습니다.");
//		}
//		memcpy_s(Data.pData, sizeof(FTransform), &RendererTrans, sizeof(FTransform));
//		UEngineCore::GetDevice().GetContext()->Unmap(TransformConstBuffer.Get(), 0);
//
//		// 같은 상수버퍼를 
//		ID3D11Buffer* ArrPtr[16] = { TransformConstBuffer.Get() };
//		UEngineCore::GetDevice().GetContext()->VSSetConstantBuffers(0, 1, ArrPtr);
//	}
//
//	{
//		D3D11_MAPPED_SUBRESOURCE Data = {};
//		// 이 데이터를 사용하는 랜더링 랜더링 잠깐 정지
//		// 잠깐 그래픽카드야 멈 그래픽카드에 있는 상수버퍼 수정해야 해.
//		UEngineCore::GetDevice().GetContext()->Map(UVValue.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//		// Data.pData 그래픽카드와 연결된 주소값.
//		if (nullptr == Data.pData)
//		{
//			MSGASSERT("그래픽카드가 수정을 거부했습니다.");
//		}
//		memcpy_s(Data.pData, sizeof(FUVValue), &UVValueData, sizeof(FUVValue));
//		UEngineCore::GetDevice().GetContext()->Unmap(UVValue.Get(), 0);
//
//		// 같은 상수버퍼를 
//		ID3D11Buffer* ArrPtr[16] = { UVValue.Get() };
//		UEngineCore::GetDevice().GetContext()->VSSetConstantBuffers(2, 1, ArrPtr);
//	}
//
//	{
//		D3D11_MAPPED_SUBRESOURCE Data = {};
//		// 이 데이터를 사용하는 랜더링 랜더링 잠깐 정지
//		// 잠깐 그래픽카드야 멈 그래픽카드에 있는 상수버퍼 수정해야 해.
//		UEngineCore::GetDevice().GetContext()->Map(SpriteConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);
//
//		// Data.pData 그래픽카드와 연결된 주소값.
//		if (nullptr == Data.pData)
//		{
//			MSGASSERT("그래픽카드가 수정을 거부했습니다.");
//		}
//		memcpy_s(Data.pData, sizeof(FSpriteData), &SpriteData, sizeof(FSpriteData));
//		UEngineCore::GetDevice().GetContext()->Unmap(SpriteConstBuffer.Get(), 0);
//
//		// 같은 상수버퍼를 
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
//	// 랜더러는 월드 뷰 프로젝트를 다 세팅받았고
//	RendererTrans.View = CameraTrans.View;
//	RendererTrans.Projection = CameraTrans.Projection;
//	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;
//
//	if (nullptr == Mesh)
//	{
//		MSGASSERT("매쉬가 세팅되지 않아서 랜더링을 할수 없습니다.");
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
//	// 인덱스 버퍼를 통해서 그리겠다.
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
////	D3D11_SUBRESOURCE_DATA Data; // 초기값 넣어주는 용도의 구조체
////	Data.pSysMem = &Vertexs[0];
////
////	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, &Data, VertexBuffer.GetAddressOf()))
////	{
////		MSGASSERT("버텍스 버퍼 생성에 실패했습니다.");
////		return;
////	}
////}
//
//void URenderer::InputAssembler1Setting()
//{
//	Mesh->GetVertexBuffer()->Setting();
//	UEngineCore::GetDevice().GetContext()->IASetInputLayout(InputLayOut.Get());
//	//UINT VertexSize = sizeof(EngineVertex);
//	//// 이 버텍스 버퍼가 10개짜리인데 3번째 버텍스 부터 세팅해줘.
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
//		// 인스턴싱을 설명할때 이야기 하겠습니다.
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
//  유일하게 인풋레이아웃만 
//  버텍스버퍼와 버텍스쉐이더가 합쳐서 만들어야 한다.
//	// 쉐이더에서 어떤 인풋레이아웃을 사용하는지 알려줘.
//	HRESULT Result = UEngineCore::GetDevice().GetDevice()->CreateInputLayout(
//		&InputLayOutData[0],
//		static_cast<unsigned int>(InputLayOutData.size()),
//		VSShaderCodeBlob->GetBufferPointer(),
//		VSShaderCodeBlob->GetBufferSize(),
//		&InputLayOut);
//
//	if (S_OK != Result)
//	{
//		MSGASSERT("인풋 레이아웃 생성에 실패했습니다");
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
//	// 행렬을 집어넣게 될것이다.
//	// 조금 느려진다고하는 하는데 느낀적은 없습니다.
//	Flag0 |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
//
//	D3DCompileFromFile(
//		WPath.c_str(),
//		nullptr, // Define TEST 등으로 전처리기를 넣을수.
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
//		MSGASSERT("쉐이더 코드 중간빌드에서 실패했습니다\n" + ErrString);
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
//		MSGASSERT("버텍스 쉐이더 생성에 실패했습니다.");
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
//		MSGASSERT("인덱스 버퍼 생성에 실패했습니다.");
//		return;
//	}
//}

//void URenderer::InputAssembler2Setting()
//{

	// Mesh->GetIndexBuffer()->Setting();

	// int Offset = 0;
	//// DXGI_FORMAT_R8_UINT; <= 옛날에는 아꼈다.
	//// DXGI_FORMAT_R16_UINT; <= 옛날에는 아꼈다.
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
//		nullptr, // Define TEST 등으로 전처리기를 넣을수.
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
//		MSGASSERT("쉐이더 코드 중간빌드에서 실패했습니다\n" + ErrString);
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
//		MSGASSERT("픽셀 쉐이더 생성에 실패했습니다.");
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
//	// 배열 넣어줄수 있다. 
//	// 0번이면 sv_target0
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
//		MSGASSERT("존재하지 않는 매쉬를 세팅할수 없습니다.\n");
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
//		MSGASSERT("존재하지 않는 Blend를 세팅할수 없습니다.\n");
//	}
//}

void URenderUnit::MaterialResourcesCheck()
{
	if (nullptr == Material)
	{
		MSGASSERT("존재하지 않는 머티리얼의 리소스를 체크할 수 없습니다.");
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
		MSGASSERT("존재하지 않는 매쉬를 세팅하려고 했습니다.");
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
		MSGASSERT("존재하지 않는 머티리얼을를 세팅하려고 했습니다.");
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
	// 잇풋어셈블러 

	// 쉐이더 리소스

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
	// 랜더타겟이라는 것을 바뀔겁니다.
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