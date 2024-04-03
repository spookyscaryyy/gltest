#version 330 core
out vec4 FragColor;
in vec2 tex_coords;

uniform sampler2D screen_tex;

void main()
{
    FragColor = vec4(texture(screen_tex, tex_coords).rgb, 1.0);
}