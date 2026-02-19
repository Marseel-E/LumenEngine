#include <metal_stdlib>

using namespace metal;

struct VertexIn {
	float4 position [[attribute(0)]];
	float4 color [[attribute(1)]];
	float2 uv [[attribute(2)]];
	float2 padding; // padding
};

struct VertexOut {
	float4 position [[position]];
	float4 color;
	float2 uv;
};

struct CameraData {
	float4x4 viewProjection;
};

vertex VertexOut vertexMain(uint vertexID [[vertex_id]], 
							constant VertexIn* vertices [[buffer(0)]],
							constant CameraData& camera [[buffer(1)]]) {
	VertexOut out;

	VertexIn v = vertices[vertexID];

	out.position = camera.viewProjection * v.position;
	
	out.color = v.color;
	out.uv = v.uv;

	return out;
};

fragment float4 fragmentMain(VertexOut in [[stage_in]],
							 texture2d<float> textureMap [[texture(0)]],
							 sampler textureSampler [[sampler(0)]])
{
	float4 textureColor = textureMap.sample(textureSampler, in.uv);
	
	return textureColor * in.color;
};