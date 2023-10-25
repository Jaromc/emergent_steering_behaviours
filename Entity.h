#pragma once

#include "Vector2.h"

class Entity
{
public:
   Entity(const Vector2f& pos, float mass, float maxSpeed, float maxForce);
   ~Entity(){}

   void addForce(const Vector2f& force);
   virtual void update(double dt);

   const Vector2f& getVelocity() const {return _velocity;}
   const Vector2f& getPosition() const {return _position;}
   const Vector2f& getHeading() const {return _heading;}
   const Vector2f& getFacing()const {return _facing;}
   float getMaxSpeed() const {return _maxSpeed;}
   float getMaxForce() const {return _maxForce;}
   float getRadius() const {return _radius;}
   void setPosition(const Vector2f& pos) {_position = pos;}
private:
   void addFriction();
private:
   Vector2f _position;
   float _rotation;

   float _radius = 20.0f;
   float _mass = 1.f;
   float _maxSpeed = 1.f;
   float _maxForce = 1.f;
   Vector2f _facing = Vector2f();
   Vector2f _force = Vector2f();
   Vector2f _velocity = Vector2f();
   Vector2f _acceleration = Vector2f();
   Vector2f _heading = Vector2f();
};