////////////////////////////////////////////////////////////////////////////////
// Filename: depth.fx
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////

float4x4 matWorld;
float4x4 matView;
float4x4 matProject;
float4x4 matWorldViewProject;

//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 depthPosition : COLOR0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType VertexMain(VertexInputType input)
{
    PixelInputType output;
    
    
	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1;
	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, matWorldViewProject);

	// Store the position value in a second input value for depth value calculations.
	output.depthPosition = output.position;
	
	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PixelMain(PixelInputType input) : SV_Target
{
	float depthValue;
	float4 color;
	
	
	// Get the depth value of the pixel by dividing the Z pixel depth by the homogeneous W coordinate.
	depthValue = input.depthPosition.z / input.depthPosition.w;

	color = float4(depthValue, depthValue, depthValue, 1.0f);

	return color;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 DepthTechnique
{
    pass pass0
    {
		SetVertexShader(CompileShader(vs_3_0, VertexMain()));
		SetPixelShader(CompileShader(ps_3_0, PixelMain()));
        SetGeometryShader(NULL);
    }
}