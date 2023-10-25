#include "Entity.h"

Entity::Entity(const Vector2f& pos, float mass, float maxSpeed, float maxForce):
   _position(pos), _mass(mass), _maxSpeed(maxSpeed), _maxForce(maxForce)
{

}

void Entity::addForce(const Vector2f& force)
{
   _force += force;
}

void Entity::addFriction()
{
	Vector2f staticFriction = -_velocity * 0.05f;//friction coeficent	
	addForce(staticFriction);
}

void Entity::update(double dt)
{
   addFriction();

   //cap force
   if (_force.length() > _maxForce)
   {
      _force = _force.getNormalise();
      _force = _force * _maxForce;
   }

   //calculate accel
   _acceleration = _force / _mass;

   //update pos
   _position += ((_velocity * dt) + (_acceleration * (dt * dt)) * 0.5f);
   
   //update vel
   _velocity += _acceleration * dt;

   //cap vel
   if (_velocity.length() > _maxForce)
   {
      _velocity = _velocity.getNormalise();
      _velocity = _velocity * _maxSpeed;
   }

   if (_velocity.lengthSq() > 0.0)
   {
      _facing = _velocity.getNormalise();
   }

   _force = Vector2f(0.f,0.f);
}