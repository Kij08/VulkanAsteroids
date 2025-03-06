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
layout(location = 3) in vec3 inSurfaceNormal;

layout(location = 0) out vec3 fragColour;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 surfaceNormal;
layout(location = 3) out float Ka;
layout(location = 4) out float Kd;
layout(location = 5) out float Ks;
layout(location = 6) out vec3 fragPos;

void main() {
    gl_Position = ubo.proj * ubo.view * PushConstants.modelMatrix * vec4(inPosition, 1.0);
    fragColour = inColour;
    fragTexCoord = inTexCoord;
    surfaceNormal = inSurfaceNormal;
    Ka = PushConstants.Ka;
    Kd = PushConstants.Kd;
    Ks = PushConstants.Ks;
    fragPos = vec3(PushConstants.modelMatrix * vec4(inPosition, 1.0)); //Multiply by model matrix to get in world coords
}