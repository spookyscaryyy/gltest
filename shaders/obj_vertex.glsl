#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 alight_pos;

out vec3 normal;
out vec3 frag_pos;
out vec3 light_pos;

void main()
{
    gl_Position = projection * view * model *  vec4(aPos, 1.0);
    frag_pos = vec3(view * model * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(view * model))) * aNormal;
    light_pos = vec3(view * vec4(alight_pos, 1.0));
}
