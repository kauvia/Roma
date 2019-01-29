#include "Entity.h"

Entity::Entity(float x, float y, int h, int w) //constructor
{
    // Init the position and height/width
    posX = x;
    posY = y;
    height = h;
    width = w;

    //Init the velocity
    velX = 0;
    velY = 0;
}

void Entity::move(int x, int y)
{
    posX += x;
    posY += y;
}

void Entity::update(int x, int y)
{
    Entity::move(x, y);

    // DISPX and Y RELATIVE TO USER     make center????
    dispX = posX;
    dispY = posY;
}

void Entity::render(SDL_Renderer *gRenderer, SDL_Rect gRect)
{
    //Define rectangle
    gRect = {dispX,
             dispY,
             width,
             height};
    //Apply color
    SDL_SetRenderDrawColor(gRenderer, 200, 175, 35, 255);
    //Draw em
    SDL_RenderFillRect(gRenderer, &gRect);
}

Entity::~Entity()
{
}
