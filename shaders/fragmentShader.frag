#version 460

in vec3 fragNormal;
out vec4 fragColor;

void main() {
    vec3 color = (fragNormal * 0.5) + 0.5;
    fragColor = vec4(color, 1.0);
}