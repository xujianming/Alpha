
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
matrix lightViewMatrix;
matrix lightProjectionMatrix;

Texture2D shaderTexture;
Texture2D depthMapTexture;
Texture3D JitterMapTexture;

float4 ambientColor;
float4 diffuseColor;
float3 lightPosition;
float4 FilterSize;
float4 JitterScale;

#define JITTER_SAMPLES 8
#define bias 0.001
SamplerState SampleClamp
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState SampleWrap
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState JitterSample
{
	Filter = MIN_MAG_MIP_POINT;
    AddressU = Wrap;
    AddressV = Wrap;
};

struct VertexInputType
{
    float4 position: POSITION;
    float2 tex: TEXCOORD0;
    float3 normal: NORMAL;
};

struct PixelInputType
{
    float4 position: SV_POSITION;
    float2 tex: TEXCOORD0;
    float3 normal: NOMAL;
    float4 lightViewPos: TECOORD1;
    float3 lightPos: TEXCOORD2;
};

PixelInputType ShadowVertexShader(VertexInputType input)
{
	PixelInputType output;
	
	input.position.w = 1.0;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.lightViewPos = mul(input.position, worldMatrix);
	output.lightViewPos = mul(output.lightViewPos, lightViewMatrix);
	output.lightViewPos = mul(output.lightViewPos, lightProjectionMatrix);

	output.tex = input.tex;
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	
	float4 worldPosition;
	worldPosition = mul(input.position, worldMatrix);
	
	output.lightPos = lightPosition.xyz - worldPosition.xyz;
	output.lightPos = normalize(output.lightPos);

	return output;
}

float4 ShadowPixelShader(PixelInputType input): SV_Target
{
	float2 projectTexCoord;
	projectTexCoord.x = input.lightViewPos.x / input.lightViewPos.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.lightViewPos.y / input.lightViewPos.w / 2.0f + 0.5f;

	float shadow = 0;
	float3 jitterCoord = float3(projectTexCoord.xy, 0);

	
	float fsize = JITTER_SAMPLES * FilterSize.w;


	float4 offset;                           
	float cnt = 0;

	float2 smCoord;
	for (int i = 0; i < 4; i ++)
	{
		offset = JitterMapTexture.SampleLevel(JitterSample, jitterCoord, 0);
		jitterCoord.z += 2.0 / JITTER_SAMPLES / JITTER_SAMPLES;

		smCoord = projectTexCoord.xy;
		shadow += depthMapTexture.SampleLevel(SampleClamp, smCoord, 0).r;

		smCoord = projectTexCoord.xy;
		shadow += depthMapTexture.SampleLevel(SampleClamp, smCoord, 0).r;

		cnt += 2;
	}
	//if (offset.x <= JitterMapTexture.SampleLevel(JitterSample, jitterCoord, 0).x)
	//	return float4(0, 0, 0, 0);
	float lightIntensity = saturate(dot(input.normal, input.lightPos));

		for (int i = 0; i < JITTER_SAMPLES * JITTER_SAMPLES / 2 - 4; i ++)
		{
			offset = JitterMapTexture.SampleLevel(JitterSample, jitterCoord, 0);
		//	if (offset.x > 0 || offset.y > 0 || offset.z > 0 || offset.w > 0)
		//	return float4(0, 0, 0, 0);
			jitterCoord.z += 2.0 / JITTER_SAMPLES / JITTER_SAMPLES;

			smCoord = projectTexCoord.xy;
			shadow += depthMapTexture.SampleLevel(SampleClamp, smCoord, 0).r;

			smCoord = projectTexCoord.xy;
			shadow += depthMapTexture.SampleLevel(SampleClamp, smCoord, 0).r;

			cnt += 2;
		}
	
//	if (shadow != cnt && shadow != 0)
//		return float4(0, 0, 0, 0);
	float4 color = ambientColor;

//	if (lightIntensity > 0)
		color += lightIntensity * diffuseColor * (1 - depthMapTexture.SampleLevel(SampleClamp, input.position.xy, 0).r);

//	if (lightIntensity > 0)
//		color += lightIntensity * diffuseColor * (shadow / cnt);


	color = saturate(color);
	
	float4 texCol = shaderTexture.Sample(SampleWrap, input.tex);
	color = color * texCol;
	return color;
}

technique10 ShadowTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, ShadowVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, ShadowPixelShader()));
        SetGeometryShader(NULL);
    }
}