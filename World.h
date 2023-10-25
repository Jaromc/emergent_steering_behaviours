#pragma once

#include "Entity.h"
#include "Bot.h"
#include <memory>
#include <vector>

class World
{
public:
   void setPlayer(std::unique_ptr<Entity> &&player) {_player.swap(player);}
   void addBot(std::unique_ptr<Bot> &&bot) {bots.push_back(std::move(bot));}

   Entity* getPlayer() const {return _player.get();}
   const std::vector<std::unique_ptr<Bot>>& getBots() const {return bots;}
private:
   std::vector<std::unique_ptr<Bot>> bots;
   std::unique_ptr<Entity> _player;
};