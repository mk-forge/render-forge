#version 460

in vec2 vt_out;
uniform sampler2D textureSampler;
out vec4 fragColor;

void main() {
    fragColor = texture(textureSampler, vt_out);
}