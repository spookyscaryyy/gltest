#version 330 core

#define NR_POINT_LIGHTS 4
#define NR_DIFFUSE_TEX 10
#define NR_SPECULAR_TEX 10

struct Material {
    sampler2D tex_diffuse[NR_DIFFUSE_TEX];
    sampler2D tex_specular[NR_SPECULAR_TEX];
    float shininess;
};

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct EnvLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
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


uniform EnvLight sun;
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight flashlight;
uniform Material material;


in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;

out vec4 FragColor;
/*
vec3 calc_spot_light(SpotLight light, vec3 normal, vec3 pos, vec3 view_dir);
vec3 calc_spot_light(SpotLight light, vec3 normal, vec3 pos, vec3 view_dir)
{
    float distance = length(light.position - pos);
    float theta = dot(view_dir, light.direction);
    float epsilon = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);

    float diff = max(dot(normal, view_dir), 0.0);
    vec3 reflect_dir = reflect(-view_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, tex_coords)));
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, tex_coords)));
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    return (attenuation * (ambient + intensity * (diffuse + specular)));

}
vec3 calc_point_light(PointLight light, vec3 normal, vec3 pos, vec3 view_dir); 
vec3 calc_point_light(PointLight light, vec3 normal, vec3 pos, vec3 view_dir)
{
    float distance = length(light.position - pos);
    float diff = max(dot(normal, view_dir), 0.0);
    vec3 reflect_dir = reflect(-view_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, tex_coords)));
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, tex_coords)));
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    return (attenuation * (ambient + diffuse + specular));
}

vec3 calc_env_light(EnvLight light, vec3 normal, vec3 view_dir);
vec3 calc_env_light(EnvLight light, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(-light.direction);
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex_coords));
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, tex_coords)));
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, tex_coords)));
    return (ambient + diffuse + specular);
}
*/
void main()
{
    vec3 norm = normalize(normal);
    vec3 view_dir = normalize(-frag_pos);

    //vec3 result = calc_env_light(sun, norm, view_dir);

    //for (int i = 0; i < NR_POINT_LIGHTS; i++)
    //{
    //    result += calc_point_light(point_lights[i], norm, frag_pos, view_dir);
    //}

    //result += calc_spot_light(flashlight, norm, frag_pos, view_dir);

    FragColor = texture(material.tex_diffuse[0], tex_coords);
    //FragColor = vec4(result, 1.0);
}
