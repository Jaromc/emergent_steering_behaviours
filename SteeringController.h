#pragma once

#include "Vector2.h"
#include "Bot.h"
#include "World.h"

enum class BLEND_TYPE
{
   SEEK,
   FLEE
};

Vector2f getBlendedSteering(Bot *bot, const World &world, BLEND_TYPE blend);