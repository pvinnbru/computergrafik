#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

out vec4 fragmentColor;

void main(){
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
    fragmentColor = vec4(1, 0, 0, 1); 
}