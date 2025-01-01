// 정점 구조체 정의
struct vertexShaderInput
{
    float4 POSITION : POSITION; // 위치 데이터
    //float4 UV : TEXCOORD; // UV 데이터 (사용하지 않음)
    float4 COLOR : COLOR; // 색상 데이터
};
// 정점 셰이더 출력 구조체
struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // 클립 공간 위치
    float4 COLOR : COLOR; // 색상 데이터
};
// 상수 버퍼 정의
cbuffer FTransform : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Location;
    float4x4 ScaleMat;
    float4x4 RotationMat;
    float4x4 LocationMat;
    float4x4 RevoleMat;
    float4x4 ParentMat;
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 WVP;
};
// 수정된 정점 셰이더
VertexShaderOutPut TestToVertex(vertexShaderInput _Vertex)
{
    VertexShaderOutPut OutPut;
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
		
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}
// 픽셀 셰이더 정의
float4 PixelToWorld(VertexShaderOutPut _Vertex) : SV_Target0
{
    //return _Vertex.COLOR;
    return float4(1, 1, 0, 1);
}
