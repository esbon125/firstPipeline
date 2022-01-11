#version 450 core
layout (triangles) in;
layout (triangle_strip,max_vertices=3) out;

in TES_COLOR{
vec4 color;
}in_color[];

out GEOM_COLOR{
vec4 color;
}out_color;

void main(void)
{
    int i;
    for(i=0;i<gl_in.length();i++)
    {
    gl_Position=gl_in[i].gl_Position;
    out_color.color=in_color[i].color;
    EmitVertex();    
    }

 EndPrimitive();
}