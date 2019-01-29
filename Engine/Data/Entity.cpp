#include "Entity.h"

Entity::Entity() //constructor
{
}

void Entity::initialize(float x, float y, int w, int h, int r, int g, int b)
{
    // Init the position and height/width
    posX = x;
    posY = y;
    width = w;
    height = h;

    //Init the velocity
    velX = 0;
    velY = 0;

    colR = r;
    colG = g;
    colB = b;
}

void Entity::move(float x, float y)
{
    posX += x;
    posY += y;
}

void Entity::update(float x, float y)
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
    SDL_SetRenderDrawColor(gRenderer, colR, colG, colB, 255);

    //Draw em
    SDL_RenderFillRect(gRenderer, &gRect);
}

Entity::~Entity()
{
}
