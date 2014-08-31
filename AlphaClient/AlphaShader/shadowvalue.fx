////////////////////////////////////////////////////////////////////////////////
// Filename: shadow.fx
////////////////////////////////////////////////////////////////////////////////


//////////////
// MATRICES //
//////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
matrix lightViewMatrix;
matrix lightProjectionMatrix;


//////////////
// TEXTURES //
//////////////
Texture2D depthMapTexture;

///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleTypeClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState SampleTypeWrap
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
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
    float4 lightViewPosition : TEXCOORD1;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType ShadowVertexShader(VertexInputType input)
{
    PixelInputType output;
    
	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    
	// Calculate the position of the vertice as viewed by the light source.
    output.lightViewPosition = mul(input.position, worldMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, lightViewMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, lightProjectionMatrix);

	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
	// Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ShadowPixelShader(PixelInputType input) : SV_Target
{
	float bias;
	float2 projectTexCoord;
	float depthValue;
	float lightDepthValue;
    float lightIntensity;
	float4 textureColor;


	// Set the bias value for fixing the floating point precision issues.
	bias = 0.001f;

	// Calculate the projected texture coordinates.
	projectTexCoord.x =  input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;

	// Determine if the projected coordinates are in the 0 to 1 range.  If so then this pixel is in the view of the light.
	if((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		// Sample the shadow map depth value from the depth texture using the sampler at the projected texture coordinate location.
		depthValue = depthMapTexture.Sample(SampleTypeClamp, projectTexCoord).r;

		// Calculate the depth of the light.
		lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;

		// Subtract the bias from the lightDepthValue.
		lightDepthValue = lightDepthValue - bias;

		// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
		// If the light is in front of the object then light the pixel, if not then shadow this pixel since an object (occluder) is casting a shadow on it.
		if(lightDepthValue < depthValue)
		{
		   return float4(1.0, 1.0, 1.0, 1.0);
		}
	}

	return float4(0.0, 0.0, 0.0, 0.0);
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 ShadowTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, ShadowVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, ShadowPixelShader()));
        SetGeometryShader(NULL);
    }
}