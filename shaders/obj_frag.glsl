#version 330 core
struct Material {
    sampler2D emissive;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

in vec3 normal;
in vec3 frag_pos;
in vec3 light_pos;
in vec2 tex_coords;

out vec4 FragColor;


void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));

    // diffuse
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, tex_coords)));

    // specular
    vec3 view_dir = normalize(-frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, tex_coords)));

    // emissive
    vec3 emissive = vec3(0.0);
    if (texture(material.specular, tex_coords).rgb == vec3(0.0))
    {
        emissive = vec3(texture(material.emissive, tex_coords));
    }

    vec3 result = ambient + diffuse + specular + emissive;
    FragColor = vec4(result, 1.0);
}
