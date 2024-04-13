#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;


void main()
{    
    vec4 c1=texture(texture_diffuse1, TexCoords);
    vec4 c2=texture(texture_specular1, TexCoords);
    //c1=mix(c1,vec4(TexCoords,1.0,1.0),0.8);
    c1.a=1.0;
    FragColor = c1;
    //FragColor=c1;
    //FragColor = vec4(TexCoords,1.0,1.0);
    //FragColor=vec4(1.0);
}