#version 330 core
out vec4 fragColor;
in vec3 fragCoord;

uniform vec3 iResolution; 
uniform float iTime;

#define _SnowflakeAmount 100	// Number of snowflakes
#define _BlizardFactor 0.2		// Fury of the storm !

vec2 uv;

float rnd(float x)
{
    return fract(sin(dot(vec2(x+47.49,38.2467/(x+2.3)), vec2(12.9898, 78.233)))* (43758.5453));
}

float drawCircle(vec2 center, float radius)
{
    return 1.0 - smoothstep(0.0, radius, length(uv - center));
}


void main(){
    uv = fragCoord.xy / iResolution.x;
    uv=(uv+vec2(1.0))*0.5;
    uv.y-=0.01;
    uv.y*=0.7;
    //uv.x*=1.5;
    
    fragColor = vec4(0.808, 0.89, 0.918, 0.0);
    //fragColor=vec4(uv,1.0,1.0);
    float j;
    
    for(int i=0; i<_SnowflakeAmount; i++)
    {
        j = float(i);
        float speed = 0.3+rnd(cos(j))*(0.7+0.5*cos(j/(float(_SnowflakeAmount)*0.25)));
        vec2 center = vec2((0.25-uv.y)*_BlizardFactor+rnd(j)+0.1*cos(iTime+sin(j)), mod(sin(j)-speed*(iTime*1.5*(0.1+_BlizardFactor)), 0.65));
        fragColor += vec4(0.9*drawCircle(center, 0.001+speed*0.022));
        
    }
}