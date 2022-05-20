#version 330

in vec4 i_vVertex;
in vec3 i_vNormal;
in vec2 i_vTexCoord;
in ivec4 i_vTextureIndex;
in vec4 i_vInstancePosition;


uniform mat4 u_MVP;

smooth out vec2 o_vTexCoord;
flat  out int  o_TOIndex;

void main(){

   o_vTexCoord=i_vTexCoord;
   o_TOIndex=i_vTextureIndex[0];
   gl_Position= u_MVP * (i_vVertex+i_vInstancePosition);
   
}