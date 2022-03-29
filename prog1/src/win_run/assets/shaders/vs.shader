#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat4 mvpMatrix;
uniform vec4 color;
uniform vec3 lightPosition;

out vec3 WorldPos;
out vec3 Normal;
out vec3 LightPosition;
out vec4 Color;

void main()
{
  Color = color;
  WorldPos = vec3(mvpMatrix * vec4(aPosition, 1.0));
  LightPosition = vec3(mvpMatrix * vec4(lightPosition, 1.0));
  Normal = aNormal;

  gl_Position = mvpMatrix * vec4(aPosition, 1.0f);

}