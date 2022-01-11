#version 450 core
in GEOM_COLOR
{
    vec4 color;
}in_color;
out vec4 color;
void main(void)
{
   color=in_color.color;
}