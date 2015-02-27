
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
	float3 col : COLOR0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 col : COLOR0;
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

	output.col = input.col;
	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PixelMain(PixelInputType input) : SV_Target
{
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	return float4(input.col, 0.0);
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 TextureTechnique
{
	pass pass0
	{
		SetVertexShader(CompileShader(vs_3_0, VertexMain()));
		SetPixelShader(CompileShader(ps_3_0, PixelMain()));
	}
}