#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(loaction = 1) in vec3 vertexColor;

out vec3 fragmentColor;
uniform mat4 matrix;

void main()
{
    gl_Position = matrix * vec4(vertexPosition_modelspace, 1);

}
