#ifndef ROMA_ENTITY
#define ROMA_ENTITY

#include <SDL2/SDL.h>

#include <iostream>
#include <stdio.h>


class Entity
{
public:


  float dispX;
  float dispY;
  float mult;

  bool isAlive;
  float energy;

  Entity(float x, float y, int h, int w);
  ~Entity();

  void move(int x,int y);

  void update(int x, int y);
  void render(SDL_Renderer* gRenderer,SDL_Rect gRrect);

private:
  float posX;
  float posY;

  int height;
  int width;

  float velX;
  float velY;
};

#endif