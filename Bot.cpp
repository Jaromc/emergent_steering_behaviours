#include "Bot.h"
#include "Params.h"

Bot::Bot(const Vector2f& pos, float mass, float maxSpeed, float maxForce) :
   Entity(pos, mass, maxSpeed, maxForce)
{
   
}

void Bot::update(double dt)
{
   Entity::update(dt);
}