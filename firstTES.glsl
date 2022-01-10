#version 450 core
layout(triangles,equal_spacing,cw) in;
in TCS_COLOR{
    vec4 color;
}in_color[];

out TES_COLOR{
    vec4 color;
}out_color;

void main(void)
{   
    out_color.color = (gl_TessCoord.x * in_color[0].color + /* Interpolation */
                     gl_TessCoord.y * in_color[1].color +
                     gl_TessCoord.z * in_color[2].color );
    gl_Position=(gl_TessCoord.x*gl_in[0].gl_Position+
                gl_TessCoord.y*gl_in[1].gl_Position+
                gl_TessCoord.z*gl_in[2].gl_Position);
}