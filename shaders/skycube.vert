#version 460

layout(location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 fragmentLocalPosition;

void main() {
    mat4 viewNoTranslation = mat4(mat3(viewMatrix));
    vec4 pos = projectionMatrix * viewNoTranslation * vec4(vp, 1.0);
    gl_Position = pos.xyww;
    fragmentLocalPosition = vp;
}