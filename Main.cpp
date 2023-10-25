#define SDL_MAIN_HANDLED

#include "Bot.h"
#include "Params.h"
#include "Vector2.h"
#include "Matrix.h"
#include "World.h"
#include "SteeringController.h"
#include <memory>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <array>
#include <SDL2/SDL.h>

void drawBot(SDL_Renderer *renderer, const Entity &bot, Uint8 r, Uint8 g, Uint8 b)
{
   Vector2f pos = bot.getPosition();
   Vector2f facing = bot.getFacing();
   Matrix2 mat;
   float rot = atan2(facing.y, facing.x);

   mat.setRotation(rot);
   mat.setTranslation(pos);
   Vector2f tri[4];
   tri[0].x = -5;
   tri[0].y = 5;
   tri[1].x = -5;
   tri[1].y = -5;
   tri[2].x = 10;
   tri[2].y = 0;
   tri[3].x = -5;
   tri[3].y = 5;

   tri[0] = mat.transform(tri[0]);
   tri[1] = mat.transform(tri[1]);
   tri[2] = mat.transform(tri[2]);
   tri[3] = mat.transform(tri[3]);

   const std::vector< SDL_Vertex > verts =
    {
        { SDL_FPoint{ tri[0].x, tri[0].y }, SDL_Color{ r, g, b, 255 }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ tri[1].x, tri[1].y }, SDL_Color{ r, g, b, 255 }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ tri[2].x, tri[2].y }, SDL_Color{ r, g, b, 255 }, SDL_FPoint{ 0 }, },
    };
    SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
}

void main()
{
   if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
   {
      SDL_Log("SDL_Init failed (%s)", SDL_GetError());
      return;
   }

   SDL_Window *window = NULL;
   SDL_Renderer *renderer = NULL;

   if (SDL_CreateWindowAndRenderer(Params::getInstance()->windowX, Params::getInstance()->windowY,
      0, &window, &renderer) < 0) 
   {
      SDL_Log("SDL_CreateWindowAndRenderer failed (%s)", SDL_GetError());
      SDL_Quit();
      return;
   }

   SDL_SetWindowTitle(window, "App");

   srand (time(NULL));


   World world;


   Vector2f playerStartPos(10,10);
   world.setPlayer(std::move(std::make_unique<Bot>(playerStartPos, 0.01f, 10.f, 1000.f)));
   
   //create bots
   for (int i = 0; i < 30; ++i)
   {
      Vector2f startPosA(rand() % Params::getInstance()->windowX,
                      rand() % Params::getInstance()->windowY);

      world.addBot(std::move(std::make_unique<Bot>(startPosA, 0.01f, 10.f, 1000.f)));
   }

   auto now = std::chrono::steady_clock::now();
   auto last = now;

   BLEND_TYPE blendType = BLEND_TYPE::SEEK;
   while (1) 
   {
      last = now;
      now = std::chrono::steady_clock::now();
      double dt = std::chrono::duration<double>(now-last).count();

      int finished = 0;
      SDL_Event event;
      while (SDL_PollEvent(&event)) 
      {
         if (event.type == SDL_QUIT) 
         {
               finished = 1;
               break;
         }
         else if (event.type == SDL_KEYDOWN)
         {
            switch(event.key.keysym.sym)
            {
               case SDLK_ESCAPE:
               {
                  finished = 1;
                  break;
               }
               case SDLK_1:
               {
                  blendType = BLEND_TYPE::SEEK;
                  break;
               }
               case SDLK_2:
               {
                  blendType = BLEND_TYPE::FLEE;
                  break;
               }
            }
         }
      }

      const Uint8* keystates = SDL_GetKeyboardState(NULL);

      Vector2f playerforce;
      if(keystates[SDL_SCANCODE_W])
      {
         playerforce.y -= 1;
      }
      if(keystates[SDL_SCANCODE_A])
      {
         playerforce.x -= 1;
      }
      if(keystates[SDL_SCANCODE_S])
      {
         playerforce.y += 1;
      }
      if(keystates[SDL_SCANCODE_D])
      {
         playerforce.x += 1;
      }

      playerforce = playerforce.getNormalise() * 20;

      world.getPlayer()->addForce(playerforce);
      world.getPlayer()->update(dt);

      if (finished) 
      {
         break;
      }

      //update bots
      for(auto &bot : world.getBots())
      {
         Vector2f steeringForce = getBlendedSteering(bot.get(), world, blendType);
         bot->addForce(steeringForce);
         bot->update(dt);
      }

      //render to screen
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      for(auto &bot : world.getBots())
      {
         drawBot(renderer, *bot, 255, 0, 0);
      }

      drawBot(renderer, *world.getPlayer(), 0, 0, 255);

      SDL_RenderPresent(renderer);
   }

   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);

   SDL_Quit();
}