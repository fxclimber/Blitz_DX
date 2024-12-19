
// #include ""



// 쉐이더에 만든 함수는 거의 대부분 최대한의 쓰레드 효율로
// 동시에 실행된다.

// Vertex[6]

// for
// Vertex[i] * world

// 그래픽 쓰레드1
// 동시에 된다 => Vertex[0] * world Vertex[0] * world Vertex[0] * world Vertex[0] * world Vertex[0] * world Vertex[0] * world

// 여기 들어올 점을 정의내려 줄수 있습니다.
// HLSL입니다. 쉐이더에서 C++이 아닙니다.
// 여기에 쳐지는 코드는 쉐이더 언어로 쳐야 합니다.
// Shader 7.0 12
// Shader 5.0 11 <= 선생님 버전

// 어그냥 C++인데?
// 시맨틱을 붙여줘야 합니다.
// 내가 이 점의 컬러에요
// 포지션이에요

//#define TEST
//#ifdef TEST
//#else
//#endif

struct EngineVertex
{
    float4 COLOR : COLOR;
    float4 POSITION : POSITION;

};

// 버텍스 쉐이더는 무조건 리턴값이 있어야 합니다.
// 인풋어셈블러2로 넘길 값을 리턴해줘야하는데.
// 이때도 규칙이 있습니다.

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION;
    float4 COLOR : COLOR;
};

// 버텍스쉐이더를 다 만들었다.
VertexShaderOutPut VertexToWorld(EngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
	// _Vertex 0.5, 0.5
    OutPut.SVPOSITION = _Vertex.POSITION;
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}