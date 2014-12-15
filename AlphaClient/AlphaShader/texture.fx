////////////////////////////////////////////////////////////////////////////////
// Filename: texture.fx
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////

float4x4 matWorld;
float4x4 matView;
float4x4 matProject;
float4x4 matWorldViewProject;

float4 ambient;
float4 lightDirection;

sampler2D textureSampler:TEXTURE0 = 
sampler_state
{
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
	BorderColor = 0;
};

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
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
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

//	 Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
	output.normal = input.normal;
	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PixelMain(PixelInputType input) : SV_Target
{
	float4 textureColor;
	
	float lightIntensity = saturate(dot(input.normal, lightDirection));
	lightIntensity = saturate(lightIntensity + ambient);
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = tex2D(textureSampler, input.tex);
	textureColor = textureColor * lightIntensity;

    return textureColor;
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