cbuffer ViewConstants : register(b0)
{
	float4x4 viewMatrix;
	float4x4 viewProjectionMatrix;
};

cbuffer LightConstants : register(b2)
{
    float3 lightDir;
    float _pad;
    float3 lightColor;
    float lightBrightness;
};

// same size as ViewConstants so that we can switch it out in the DepthRendering shader to render shadowmaps
cbuffer ShadowConstants : register(b3)
{
    float4x4 lightViewMatrix;
    float4x4 lightViewProjectionMatrix;
};