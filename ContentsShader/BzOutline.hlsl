struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 NORMAL : NORMAL;
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

cbuffer FBzColor : register(b0)
{
    float4 Albedo;
};


Input Line_VS(EngineVertex _Vertex)
{
    Input OutPut;
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
    OutPut.UV = _Vertex.UV;
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}

Input Outline_VS(EngineVertex _Vertex)
{
    Input OutPut;

    // 월드 변환 적용 후, NORMAL 방향으로 확장
    float4 worldPos = mul(_Vertex.POSITION, World);
    worldPos.xyz += _Vertex.NORMAL.xyz * 0.15f; // 외곽선 확장

    // 뷰-투영 변환 적용
    OutPut.SVPOSITION = mul(worldPos, View);
    OutPut.SVPOSITION = mul(OutPut.SVPOSITION, Projection);

    OutPut.UV = _Vertex.UV;
    OutPut.COLOR = _Vertex.COLOR;

    return OutPut;
}
float4 Outline_PS(Input _Vertex) : SV_Target
{
    float UVScale = 10;
    float2 scaledUV = _Vertex.UV.xy * UVScale;
    float4 texColor = bz_texture0.Sample(bz_sampler, frac(scaledUV));
    float4 multColor = { 1, 0.6, 0, 1 };
    float4 finalColor = texColor * multColor;
    
    return finalColor;
}