#pragma once

#include "Entity.h"
#include "Vector2.h"

class Bot : public Entity
{
   public:
      Bot(const Vector2f& pos, float mass, float maxSpeed, float maxForce);
      ~Bot(){}

      void update(double dt) override;

   private:
};