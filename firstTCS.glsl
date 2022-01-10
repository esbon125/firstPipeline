#version 450 core
in VS_COLOR{
    vec4 color;
}in_color[];

out TCS_COLOR{
vec4 color;
}out_color[];

layout (vertices=3) out;
void main(void)
{
if(gl_InvocationID==0)
{
    gl_TessLevelInner[0]=5.0;
    gl_TessLevelOuter[0]=5.0;
    gl_TessLevelOuter[1]=5.0;
    gl_TessLevelOuter[2]=5.0;
}
gl_out[gl_InvocationID].gl_Position=gl_in[gl_InvocationID].gl_Position;
out_color[gl_InvocationID].color=in_color[gl_InvocationID].color;
}