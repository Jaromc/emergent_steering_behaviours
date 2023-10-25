#include "SteeringController.h"
#include "Params.h"
#include "Matrix.h"
#include "CollisionDetection.h"
#include <array>
#include <cstdlib>
#include <iostream>
namespace
{
   float randf(float max)
   {
      return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1) * max;
   }

   float randNom(float max)
   {
      return randf(max) - randf(max);
   }
}

Vector2f flee(Bot *bot, const Vector2f& enemyPosition)
{
   Vector2f direction = bot->getPosition() - enemyPosition;
   float distance = direction.length();

   if (distance > Params::getInstance()->panicDistance)
   {
      //not enough distance to start panicking
      return Vector2f(0,0);
   }

   return direction.getNormalise() * bot->getMaxSpeed();
}

Vector2f seek(Bot *bot, const Vector2f& targetPosition)
{
   Vector2f direction = targetPosition - bot->getPosition();
   float distance = direction.length();

   return direction.getNormalise() * bot->getMaxSpeed();
}

Vector2f separation(Bot *bot, const std::vector<Bot*> &neighbours)
{
   if (neighbours.empty())
   {
      return Vector2f(0,0);
   }

   Vector2f sep(0,0);
   for (const auto* n : neighbours)
	{
		Vector2f distance = bot->getPosition() - n->getPosition();
      float length = distance.length();
      //use a greater force the closer they are
      sep += (distance.getNormalise() * Params::getInstance()->separationForce) / length;
	}

   return sep;
}

Vector2f alignment(Bot *bot, const std::vector<Bot*> &neighbours)
{
   if (neighbours.empty())
   {
      return Vector2f(0,0);
   }

	Vector2f avHeading(0,0);
	for (const auto* n : neighbours)
	{
		avHeading += n->getHeading();
	}

   avHeading /= static_cast<float>(neighbours.size());
	return avHeading;
}

Vector2f cohesion(Bot *bot, const std::vector<Bot*> &neighbours)
{
   if (neighbours.empty())
   {
      return Vector2f(0,0);
   }

	Vector2f com(0,0);
	for (const auto* n : neighbours)
	{
		com += n->getPosition();
	}

   com /= static_cast<float>(neighbours.size());
   return seek(bot, com);
}

Vector2f wander(Bot *bot)
{
   //create an initial wander target
   Vector2f target = bot->getVelocity().getNormalise() * Params::getInstance()->wanderDistance;
   target += bot->getPosition();

   //create a wander circle that will be attached to the end of the target.
   //This gives the bot a gradual wander.

   //rotate by a small amount
   float rot = atan2(bot->getFacing().y, bot->getFacing().x);
   float wander_angle = rot + (randNom(0.1f) * Params::getInstance()->wanderRate);

   //create a random target within a wander circle in local space
   Vector2f offset;
   offset.x = Params::getInstance()->wanderRadius * static_cast<float>(cos(wander_angle));
   offset.y = Params::getInstance()->wanderRadius * static_cast<float>(sin(wander_angle));

   //final target
   target += offset;

   return seek(bot, target);
}

Vector2f wallAvoidance(Bot *bot)
{
   //create three feelers in front of the bot.
	//one is set at 0 degrees and the other two are pointing out from the center
   std::array<Vector2f, 3> feelers;
   feelers[0] = bot->getVelocity().getNormalise();

   Matrix2 mat;
   mat.setRotation(Params::getInstance()->feelerAngle);
   feelers[1] = mat.transform(feelers[0]);
   mat.setRotation(-Params::getInstance()->feelerAngle);
	feelers[2] = mat.transform(feelers[0]);

   feelers[0] *= Params::getInstance()->feelerLength;
   feelers[1] *= Params::getInstance()->feelerLength;
   feelers[2] *= Params::getInstance()->feelerLength;

   feelers[0] += bot->getPosition();
   feelers[1] += bot->getPosition();
   feelers[2] += bot->getPosition();

   Vector2f force(0,0);
   auto checkWall = [&](const Vector2f &a, const Vector2f &b)
   {
      for(const auto &feeler : feelers)
      {
         auto result = lineSegmentLineSegment(a, b, bot->getPosition(), feeler);
         if (result.collision)
         {
            force += result.contactNormal * result.depth;
         }
      }
   };

   Vector2f window(static_cast<float>(Params::getInstance()->windowX),
      static_cast<float>(Params::getInstance()->windowY));
   checkWall({0.f, 0.f}, {window.x, 0.f});
   checkWall({window.x, 0.f}, {window.x, window.y});
   checkWall({window.x, window.y}, {0.f, window.y});
   checkWall({0.f, window.y}, {0.f,0.f});

   return force * bot->getMaxForce();
}

std::vector<Bot*> tagNeighbours(Bot *bot, const std::vector<std::unique_ptr<Bot>> &bots)
{
   std::vector<Bot*> neighbours;
	for(auto &n : bots)
	{
		if (n.get() == bot)
      {
         continue;
      }

      Vector2f dist = n->getPosition() - bot->getPosition();
      float range = Params::getInstance()->neighbourTagRadius + n->getRadius();

      if (dist.length() < range)
      {
         neighbours.push_back(n.get());
      }
	}

   return neighbours;
}

bool accumulateForce(Bot *bot, const Vector2f &forceToAdd, Vector2f &runningTotal)
{
	//calculate how much steering force the bot has used so far
	float magnitude = runningTotal.length();

	//calculate how much steering force remains
	float magnitudeRemaining = bot->getMaxForce() - magnitude;

	//return if there is no more force left to use
	if (magnitudeRemaining <= 0.0f)
		return false;

	//calculate the magnitude of the force we want to add
	float magnitudeToAdd = forceToAdd.length();

	//if the force to add is less than the remaining steering force then add it to the total
	//else add as much of the force to the total force as possible
	if (magnitudeToAdd >= magnitudeRemaining)
	{
		runningTotal += forceToAdd.getNormalise() * magnitudeRemaining;
      return false;
	}

   runningTotal += forceToAdd;

	return true;
}


Vector2f getBlendedSteering(Bot *bot, const World &world, BLEND_TYPE blend)
{
   Vector2f totalForce(0.0f, 0.0f);
   //These actions are listed in order of importance.
   Vector2f newForce = wallAvoidance(bot) * Params::getInstance()->wallWeight;
   if (accumulateForce(bot, newForce, totalForce) == false)
   {
      return totalForce;
   }

   if (blend == BLEND_TYPE::SEEK)
   {
      newForce = seek(bot, world.getPlayer()->getPosition()) *
         Params::getInstance()->evadeWeight;
      if (accumulateForce(bot, newForce, totalForce) == false)
      {
         return totalForce;
      }
   }
   else
   {
      newForce = flee(bot, world.getPlayer()->getPosition()) *
         Params::getInstance()->evadeWeight;
      if (accumulateForce(bot, newForce, totalForce) == false)
      {
         return totalForce;
      }
   }

   newForce = wander(bot)* Params::getInstance()->wanderWeight;
   if (accumulateForce(bot, newForce, totalForce) == false)
   {
      return totalForce;
   }

   std::vector<Bot*> neighbours = tagNeighbours(bot, world.getBots());
   newForce = separation(bot, neighbours) * Params::getInstance()->separationWeight;
   if (accumulateForce(bot, newForce, totalForce) == false)
   {
      std:: cout << 1 << std::endl;
      return totalForce;
   }

   newForce = cohesion(bot, neighbours) * Params::getInstance()->cohesionWeight;
   if (accumulateForce(bot, newForce, totalForce) == false)
   {
      return totalForce;
   }

   return totalForce;
}