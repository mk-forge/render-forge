#version 460

in vec3 worldNor;
in vec3 viewDir;
in vec3 pos;
out vec4 fragColor;

struct Light {
    int type;
    vec3 position;
    vec3 color;
    vec3 direction;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    float cutoff;
    float outerCutoff;
};

struct Material {
    float ambient;
    float diffuse;
    float specular;
};

uniform Light lights[6];
uniform Material materials[1];

void main() {
    vec3 norm = normalize(worldNor);
    vec3 ambient = vec3(0.1) * materials[0].ambient;
    vec3 light = ambient;

    for (int i = 0; i < 6; i++) {
        if (lights[i].type == 3) continue;

        vec3 direction;
        float attenuation = 1.0;

        if (lights[i].type == 0) {
            direction = normalize(lights[i].direction);
        } else {
            direction = normalize(lights[i].position - pos);
            float distance = length(lights[i].position - pos);
            attenuation = 1.0 / (lights[i].constantAttenuation + lights[i].linearAttenuation * distance + lights[i].quadraticAttenuation * (distance * distance));
        }

        if (lights[i].type == 2) {
            float theta = dot(direction, normalize(-lights[i].direction));
            float epsilon = lights[i].cutoff - lights[i].outerCutoff;
            float intensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);
            attenuation *= intensity;
        }

        float diff = max(dot(norm, direction), 0.0) * materials[0].diffuse;
        vec3 objectColor = vec3(0.385, 0.647, 0.812);

        light += diff * objectColor * lights[i].color * attenuation;
    }

    fragColor = vec4(light, 1.0);
}