struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};


struct Input
{
    float4 SVPOSITION : SV_POSITION; 
    float4 UV : TEXCOORD; 
    float4 COLOR : COLOR;
};

Texture2D bz_texture0 : register(t0);
SamplerState bz_sampler : register(s0);


// 상수버퍼를 사용하겠다.
cbuffer FTransform : register(b0)
{

    float4 Scale;
    float4 Rotation;
    float4 Qut;
    float4 Location;

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

Input CubeTest_VS(EngineVertex _Vertex)
{
    Input OutPut;
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
    OutPut.UV = _Vertex.UV;
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}

cbuffer FBzColor : register(b0)
{
    float4 Albedo;
};

float4 CubeTest_PS(Input _Vertex) : SV_Target0
{
    float UVScale = 1;
    float2 scaledUV = _Vertex.UV.xy * UVScale; // UVScale은 float2 타입으로 반복 횟수를 설정
    float4 texColor = bz_texture0.Sample(bz_sampler, frac(scaledUV));
    float4 multColor = 1; //{        1, 0.6, 0, 1};
    float4 finalColor = texColor * multColor;
    
    return finalColor;
};

// 수정필수
//float4 CubeTest_PS(Input _Vertex) : SV_Target0
//{
//    // UV 범위를 정규화
//    float2 uv = frac(_Vertex.UV.xy);

//    float4 color;
//    if (uv.x < 0.25 && uv.y > 0.75)        // UV 셀 0
//        color = float4(1, 0, 0, 1); // 빨강
//    else if (uv.x >= 0.25 && uv.x < 0.5 && uv.y > 0.75) // UV 셀 1
//        color = float4(0, 1, 0, 1); // 초록
//    else if (uv.x >= 0.5 && uv.x < 0.75 && uv.y > 0.75) // UV 셀 2
//        color = float4(0, 0, 1, 1); // 파랑
//    else if (uv.x >= 0.75 && uv.x <= 1.0 && uv.y > 0.75) // UV 셀 3
//        color = float4(1, 1, 0, 1); // 노랑
//    else if (uv.x < 0.25 && uv.y <= 0.75 && uv.y > 0.5)  // UV 셀 4
//        color = float4(0.5, 0, 0.5, 1); // 보라
//    else if (uv.x >= 0.25 && uv.x < 0.5 && uv.y <= 0.75 && uv.y > 0.5) // UV 셀 5
//        color = float4(0, 1, 1, 1); // 하늘색
//    else
//        color = float4(1, 1, 1, 1); // 기본 흰색 (예외 처리)

//    return color;
//};
