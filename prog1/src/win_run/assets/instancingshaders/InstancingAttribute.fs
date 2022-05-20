#version 330

out vec4 vFragColor;

uniform sampler2D u_TO1;
uniform sampler2D u_TO2;
uniform sampler2D u_TO3;
uniform sampler2D u_TO4;
uniform sampler2D u_TO5;


smooth in vec2 o_vTexCoord;
flat  in int  o_TOIndex;


void main()
{
   int index=o_TOIndex;   
   vec4 color=vec4(0,0,0,0);
   
	switch(index)
	{
	case 0: color=texture(u_TO1, o_vTexCoord); break;
	case 1: color=texture(u_TO2, o_vTexCoord); break;
	case 2: color=texture(u_TO3, o_vTexCoord); break;	
	case 3: color=texture(u_TO4, o_vTexCoord); break;
	case 4: color=texture(u_TO5, o_vTexCoord); break;
	case 10: color=texture(u_TO2, o_vTexCoord); break;
	case 15: color=texture(u_TO3, o_vTexCoord); break;
	
	}
  
   vFragColor = color; 

}