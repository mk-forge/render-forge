#version 460

in vec3 fragmentLocalPosition;
uniform samplerCube skyCube;
out vec4 fragColor;

void main() {
    fragColor = texture(skyCube, fragmentLocalPosition);
}