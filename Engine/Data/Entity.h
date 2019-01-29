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

  Entity();
  ~Entity();

  void initialize(float x, float y, int w, int h, int r, int g, int b);

  void move(float x,float y);

  void update(float x, float y);
  void render(SDL_Renderer* gRenderer,SDL_Rect gRrect);

private:
  float posX;
  float posY;

  int width;
  int height;

  float velX;
  float velY;

  int colR;
  int colG;
  int colB;
};

#endif