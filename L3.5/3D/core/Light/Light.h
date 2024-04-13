#pragma once
#include "L1/Lib/Math/math.h"
struct DirLight {
    math::vec3 direction;
	
    math::vec3 ambient;
    math::vec3 diffuse;
    math::vec3 specular;
    DirLight(){
        direction={0,-1,0};//向下
        ambient={0.05f, 0.05f, 0.05f};
        diffuse={0.4f, 0.4f, 0.4f};
        specular={0.5f, 0.5f, 0.5f};
    }
};

struct PointLight {
    math::vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    math::vec3 ambient;
    math::vec3 diffuse;
    math::vec3 specular;
    PointLight(){
        position={0,0,0};
        constant=1.f;
        linear=0.09f;
        quadratic=0.32f;
        ambient={0.05f, 0.05f, 0.05f};
        diffuse={0.8f, 0.8f, 0.8f};
        specular={1.0f, 1.0f, 1.0f};
    }
};

struct SpotLight {
    math::vec3 position;
    math::vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    math::vec3 ambient;
    math::vec3 diffuse;
    math::vec3 specular;
    SpotLight(){
        position={0,0,0};
        direction={0,-1,0};
        cutOff=cosf(glm::radians(12.5f));
        outerCutOff=cosf(glm::radians(15.f));
        constant=1.f;
        linear=0.09f;
        quadratic=0.32f;
        ambient={0.0f, 0.0f, 0.0f};
        diffuse={0.8f, 0.8f, 0.8f};
        specular={1.0f, 1.0f, 1.0f};
    }   
};
struct LightData{
    DirLight dir_light;
    PointLight point_light;
    SpotLight spot_light;
};