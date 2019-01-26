#ifndef ROMA_ENGINE
#define ROMA_ENGINE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>

class Engine
{
  public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    static int SCREEN_X;
    static int SCREEN_Y;

    Engine();
    ~Engine();

    bool Initialize(const char *windowTitle);

    void Update();
    void Render();

    bool runLoop();
    void closeEngine();

  private:
    static SDL_Window *gWindow;
    static SDL_Renderer *gRenderer;
    static TTF_Font *gFont;
    static SDL_Event e;
};

#endif