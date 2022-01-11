#include <stdio.h>
#include <GL/glew.h>
#include "GL/glut.h"
#include <math.h>
#define DIM 512

GLuint rendering_program;
GLuint vertex_array_object;


char *textFileRead(char *fn) {
 
    FILE *fp;
    char *content = NULL;
 
    int count=0;
 
    if (fn != NULL) {
        fp = fopen(fn,"rt");
 
        if (fp != NULL) {
 
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);
 
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}


GLuint compile_shaders(void)
{
 GLuint vertex_shader;
 GLuint fragment_shader;
 GLuint program;
 GLuint tes_shader;
 GLuint tcs_shader;
 GLuint geometry_shader;

//Source for control shader
 const GLchar * tcs_shader_source=textFileRead("firstTCS.glsl");
//Source for evaluation shader
 const GLchar * tes_shader_source=textFileRead("firstTES.glsl");
//Source code for vertex shader
  const GLchar * vertex_shader_source=textFileRead("firstVertex.glsl");

 const GLchar * fragment_shader_source=textFileRead("firstFragment.glsl");

const GLchar *geometry_shader_source=textFileRead("firstGeometry.glsl");

vertex_shader=glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertex_shader,1,&vertex_shader_source,NULL);
glCompileShader(vertex_shader);

fragment_shader=glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragment_shader,1,&fragment_shader_source,NULL);
glCompileShader(fragment_shader);

tcs_shader=glCreateShader(GL_TESS_CONTROL_SHADER);
glShaderSource(tcs_shader,1,&tcs_shader_source,NULL);
glCompileShader(tcs_shader);

tes_shader=glCreateShader(GL_TESS_EVALUATION_SHADER);
glShaderSource(tes_shader,1,&tes_shader_source,NULL);
glCompileShader(tes_shader);

geometry_shader=glCreateShader(GL_GEOMETRY_SHADER);
glShaderSource(geometry_shader,1,&geometry_shader_source,NULL);
glCompileShader(geometry_shader);

program=glCreateProgram();
glAttachShader(program,vertex_shader);
glAttachShader(program,fragment_shader);
glAttachShader(program,tes_shader);
glAttachShader(program,tcs_shader);
glAttachShader(program,geometry_shader);
glLinkProgram(program);
glUseProgram(program);

/*GLint status;
glGetProgramiv(program,GL_INFO_LOG_LENGTH,&status);
printf("%d\n",status);

GLchar infolog[1024];GLint length;
glGetProgramInfoLog(program,1024,&length,infolog);
FILE *infologFile=fopen("infolog.txt","w");
int i=0;
while(infolog[i]!='\0')
{
    putc(infolog[i], infologFile);
}
*/

glDeleteShader(vertex_shader);
glDeleteShader(fragment_shader);
glDeleteShader(tes_shader);
glDeleteShader(tcs_shader);
glDeleteShader(geometry_shader);
return program;
}

void startup()
{
glCreateVertexArrays(1,&vertex_array_object);
glBindVertexArray(vertex_array_object);
}

void shutdown()
{
glDeleteVertexArrays(1,&vertex_array_object);
glDeleteProgram(rendering_program);
}

void display()
{  
    double currentTime=glutGet(GLUT_ELAPSED_TIME);
    
    glClearColor(1.0f , 0.f , 0.f , 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    

    glUseProgram(rendering_program);
    
    GLfloat attrib[]={  (float)(sin(currentTime))*0.5f,
                        (float)(cos(currentTime))*0.6f,
                        0.f,0.f };
GLfloat color[]={  0.f,(float)(cos(currentTime))*0.5f+0.5f,
                        (float)(sin(currentTime))*0.5f+0.5f,0.f };                        

    glVertexAttrib4fv(0,attrib);
    glVertexAttrib4fv(1,color);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    glPatchParameteri(GL_PATCH_VERTICES,3);
    glPointSize(5.0f);
    glDrawArrays(GL_PATCHES,0,3);
    glutPostRedisplay();
    glutSwapBuffers();
    return;
}

int main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitWindowSize(DIM, DIM);
glutCreateWindow("First Pipeline");
glewInit();
rendering_program=compile_shaders();
startup();
shutdown();
glutDisplayFunc(display);
GLenum err=glGetError();
if(err!=0)
{
printf("%d\n",err);}
glutMainLoop();

  return 0;
}