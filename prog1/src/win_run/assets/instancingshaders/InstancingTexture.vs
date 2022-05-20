#version 330

in vec4 i_vVertex;
in vec2 i_vTexCoord;

#define MAX_INSTANCE 128

uniform mat4 u_MVP[MAX_INSTANCE];
uniform int  u_Texture[MAX_INSTANCE];


smooth out vec2 o_vTexCoord;
flat  out int  o_TOIndex;

void main(){

   o_vTexCoord=i_vTexCoord;
   o_TOIndex=u_Texture[gl_InstanceID];
   gl_Position=u_MVP[gl_InstanceID]*i_vVertex;
   
}