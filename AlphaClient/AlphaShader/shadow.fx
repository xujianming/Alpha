////////////////////////////////////////////////////////////////////////////////
// Filename: shadow.fx
////////////////////////////////////////////////////////////////////////////////


//////////////
// MATRICES //
//////////////
float4x4 matWorld;
float4x4 matView;
float4x4 matProject;
float4x4 matWorldViewProject;
matrix lightViewMatrix;
matrix lightProjectionMatrix;


//////////////
// TEXTURES //
//////////////



/////////////
// GLOBALS //
/////////////
float4 ambient;
float4 diffuse;
float3 lightPos;


///////////////////
// SAMPLE STATES //
///////////////////
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

sampler2D depthMapSampler:TEXTURE1 =
sampler_state 
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
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
	float3 lightPos : TEXCOORD2;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType VertexMain(VertexInputType input)
{
    PixelInputType output;
	float4 worldPosition;
    
	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1;
	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, matWorldViewProject);
    
	// Calculate the position of the vertice as viewed by the light source.
	output.lightViewPosition = mul(input.position, matWorld);
    output.lightViewPosition = mul(output.lightViewPosition, lightViewMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, lightProjectionMatrix);

	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)matWorld);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

    // Calculate the position of the vertex in the world.
	worldPosition = mul(input.position, matWorld);

    // Determine the light position based on the position of the light and the position of the vertex in the world.
    output.lightPos = lightPos.xyz - worldPosition.xyz;

    // Normalize the light position vector.
    output.lightPos = normalize(output.lightPos);

	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 PixelMain(PixelInputType input) : SV_Target
{
	float bias;
    float4 color;
	float2 projectTexCoord;
	float depthValue;
	float lightDepthValue;
    float lightIntensity;
	float4 textureColor;


	// Set the bias value for fixing the floating point precision issues.
	bias = 0.01f;

	// Set the default output color to the ambient light value for all pixels.
	color = ambient;

	// Calculate the projected texture coordinates.
	projectTexCoord.x =  input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;

	// Determine if the projected coordinates are in the 0 to 1 range.  If so then this pixel is in the view of the light.
	if((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		// Sample the shadow map depth value from the depth texture using the sampler at the projected texture coordinate location.
		depthValue = tex2D(depthMapSampler, projectTexCoord).r;

		// Calculate the depth of the light.
		lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;

		// Subtract the bias from the lightDepthValue.
		lightDepthValue = lightDepthValue - bias;

		// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
		// If the light is in front of the object then light the pixel, if not then shadow this pixel since an object (occluder) is casting a shadow on it.
		if(lightDepthValue < depthValue)
		{
		    // Calculate the amount of light on this pixel.
			lightIntensity = saturate(dot(input.normal, input.lightPos));

		    if(lightIntensity > 0.0f)
			{
				// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
				color += (diffuse * lightIntensity);

				// Saturate the final light color.
				color = saturate(color);
			}
		}
	}

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = tex2D(textureSampler, input.tex);

	// Combine the light and texture color.
	color = color * textureColor;

    return color;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 ShadowTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_3_0, VertexMain()));
        SetPixelShader(CompileShader(ps_3_0, PixelMain()));
        SetGeometryShader(NULL);
    }
}