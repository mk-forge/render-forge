#version 460

in vec2 uv;
uniform sampler2D textureSampler;
out vec4 fragColor;

void main() {
    fragColor = texture(textureSampler, uv);
}