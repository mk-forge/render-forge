#version 460

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

out vec3 worldNor;
out vec3 viewDir;
out vec3 pos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 viewPosition;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    pos = (modelMatrix * vec4(vp, 1.0)).xyz;
    worldNor = normalize(transpose(inverse(mat3(modelMatrix))) * vn);
    viewDir = normalize(viewPosition - pos);
}