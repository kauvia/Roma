#ifndef ROMA_TEXTURE
#define ROMA_TEXTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stdio.h>
#include <string>

class LTexture
{
  public:
    //init
    LTexture();
    //dealloc mem
    ~LTexture();
    //img loader frm path
    bool loadFromFile(std::string path, SDL_Renderer *gRenderer); //grenderer???
    //img from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor,TTF_Font *gFont, SDL_Renderer *gRenderer);
    //dealloc texture
    void free();
    //color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    //blending
    void setBlendMode(SDL_BlendMode blending);
    //aplha modulation
    void setAlpha(Uint8 alpha);
    //render texture at a given point       MOSTO IMPORTANTO
    void render(int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0, SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE, SDL_Renderer *gRenderer = nullptr);
    //getters
    int getWidth();
    int getHeight();

  private:
    //the actual hardware texture
    static SDL_Texture *mTexture;
    //img dimensions
    int mWidth;
    int mHeight;
};

#endif