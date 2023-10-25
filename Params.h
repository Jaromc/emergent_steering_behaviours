#pragma once
#include <string>

class Params
{
  private:
    static Params* instancePtr;

    Params();
    bool init(const std::string &filename);
  public:
    Params(const Params& obj) = delete; 
  
    static Params* getInstance()
    {
      if (instancePtr == nullptr) 
      {
        instancePtr = new Params(); 

        return instancePtr; 
      }
      else
      {
        return instancePtr;
      }
    }

    float neighbourTagRadius = 100;
    float wallWeight = 0.8;
    float evadeWeight = 0.4;
    float wanderWeight = 0.1; 
    float separationWeight = 0.8;
    float separationForce = 50.f;
    float alignmentWeight = 0.2;
    float cohesionWeight = 0.1;
    float feelerLength = 50;
    float feelerAngle = 0.785f;

    float panicDistance = 200.0;
    float wanderRate = 0.5;
    float wanderDistance = 100;
    float wanderRadius = 10;
    int windowX = 800;
    int windowY = 600;
};