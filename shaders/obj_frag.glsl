#version 330 core
struct Material {
    sampler2D emissive;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutoff;
    float outer_cutoff;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;

out vec4 FragColor;


void main()
{
    vec3 result;
    vec3 light_dir = normalize(-frag_pos);

    // flashlight
    float theta = dot(light_dir, vec3(0,0,1));
    float epsilon = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);

    // attenuation
    float distance = length(frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));

    // diffuse
    vec3 norm = normalize(normal);
    //vec3 light_dir = normalize(-light.direction);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, tex_coords)));

    // specular
    vec3 view_dir = normalize(-frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, tex_coords)));
    result = attenuation * (ambient + intensity * (diffuse + specular));

    // emissive
    vec3 emissive = vec3(0.0);
    if (texture(material.specular, tex_coords).rgb == vec3(0.0))
    {
        emissive = vec3(texture(material.emissive, tex_coords));
    }

    result += emissive;
    FragColor = vec4(result, 1.0);
}
