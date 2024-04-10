#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 fragCoord;

uniform mat4 transform;

void main(){
    fragCoord = vec3(transform * vec4(aPos, 1.0));   
    gl_Position = vec4(fragCoord, 1.0);
}