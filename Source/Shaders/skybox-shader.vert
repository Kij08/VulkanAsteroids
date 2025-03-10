#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout( push_constant ) uniform constants
{
	mat4 modelMatrix;
    float Ka;
    float Kd;
    float Ks;
} PushConstants;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColour;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = ubo.proj * ubo.view * PushConstants.modelMatrix * vec4(inPosition, 1.0);
    fragColour = inColour;
    fragTexCoord = inTexCoord;
}