struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

// 버텍스 쉐이더는 무조건 리턴값이 있어야 합니다.
// 인풋어셈블러2로 넘길 값을 리턴해줘야하는데.
// 이때도 규칙이 있습니다.

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 UV : TEXCOORD; // 
    float4 COLOR : COLOR;
};

// 상수버퍼를 사용하겠다.
cbuffer FTransform : register(b0)
{
	// transformupdate는 
	// 아래의 값들을 다 적용해서
	// WVP를 만들어내는 함수이다.
	// 변환용 벨류
    float4 Scale;
    float4 Rotation;
    float4 Qut;
    float4 Location;

	// 릴리에티브 로컬
    float4 RelativeScale;
    float4 RelativeRotation;
    float4 RelativeQut;
    float4 RelativeLocation;

	// 월드
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuat;
    float4 WorldLocation;

    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 LocationMat;
    float4x4 RevolveMat;
    float4x4 ParentMat;
    float4x4 LocalWorld;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};

// 상수버퍼는 아무것도 세팅해주지 않으면 기본값이 0으로 채워집니다.
cbuffer FSpriteData : register(b1)
{
    float4 CuttingPos;
    float4 CuttingSize;
    float4 Pivot; // 0.5 0.0f
};

cbuffer FUVValue : register(b2)
{
    float4 PlusUVValue;
};

// 버텍스쉐이더를 다 만들었다.
VertexShaderOutPut VertexToWorld(EngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
    
    // SVPOSITION 초기화
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);

    // UV 초기화
    OutPut.UV.x = (_Vertex.UV.x * CuttingSize.x) + CuttingPos.x;
    OutPut.UV.y = (_Vertex.UV.y * CuttingSize.y) + CuttingPos.y;
    OutPut.UV.z = 0.0f; // UV.z 초기화
    OutPut.UV.w = 1.0f; // UV.w 초기화
    //OutPut.UV.x += PlusUVValue.x;
    //OutPut.UV.y += PlusUVValue.y;

    // COLOR 초기화
    OutPut.COLOR = _Vertex.COLOR;

    return OutPut;
}


// 상수버퍼는 아무것도 세팅해주지 않으면 기본값이 0으로 채워집니다.
cbuffer MatColor : register(b1)
{
    float4 Albedo;
};


struct OutTargetColor
{
    float4 Target0 : SV_Target0; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 Target1 : SV_Target1; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 Target2 : SV_Target2; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 Target3 : SV_Target3; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 Target4 : SV_Target4; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 Target5 : SV_Target5; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 Target6 : SV_Target6; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 Target7 : SV_Target7; // 뷰포트행렬이 곱해지는 포지션입니다.
};


// 텍스처 1장과 
Texture2D ImageTexture : register(t0);
// 샘플러 1개가 필요합니다.
SamplerState ImageSampler : register(s0);

// 이미지를 샘플링해서 이미지를 보이게 만들고
float4 PixelToWorld(VertexShaderOutPut _Vertex) : SV_Target0
{
	
	// ImageTexture.Load({0,0));
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
    return Color;
	
	// return float4(1.0f, 0.0f, 0.0f, 1.0f);
};
