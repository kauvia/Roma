#include "Engine.h"

int Engine::SCREEN_WIDTH = 800;
int Engine::SCREEN_HEIGHT = 600;
int Engine::SCREEN_X = 100;
int Engine::SCREEN_Y = 100;

//Window to render to
SDL_Window *Engine::gWindow = nullptr;
//Window renderer
SDL_Renderer *Engine::gRenderer = nullptr;
//Global font
TTF_Font *Engine::gFont = nullptr;
//Event handler
SDL_Event Engine::e;

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::Initialize(const char *windowTitle)
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SCREEN_X, SCREEN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                //Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
}
//////////////////////////////////////

// TESTINGS
LTexture gEntityTexture;
class Entity
{
  public:
    static const int ENTITY_WIDTH = 200;
    static const int ENTITY_HEIGHT = 200;

    static const int ENTITY_VEL = 1;

    Entity(int x, int y);

    void handleEvent(SDL_Event &e);
    void move();
    void render();

  private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};

Entity::Entity(int x, int y)
{
    mPosX = x;
    mPosY = y;

    mVelX = 0;
    mVelY = 0;
}

void Entity::handleEvent(SDL_Event &e)
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= ENTITY_VEL;
            break;
        case SDLK_DOWN:
            mVelY += ENTITY_VEL;
            break;
        case SDLK_LEFT:
            mVelX -= ENTITY_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += ENTITY_VEL;
            break;
        }
    }
    //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += ENTITY_VEL;
            break;
        case SDLK_DOWN:
            mVelY -= ENTITY_VEL;
            break;
        case SDLK_LEFT:
            mVelX += ENTITY_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= ENTITY_VEL;
            break;
        }
    }
}

void Entity::move()
{
    //Move the dot left or right
    mPosX += mVelX;
    //Move the dot up or down
    mPosY += mVelY;
}

void Entity::render()
{
    gEntityTexture.render(mPosX, mPosY);
};

////////////////////////////
bool Engine::loadMedia()
{
    bool success = true;
    if (!gEntityTexture.loadFromFile("../planet.png", gRenderer))
    {
        printf("Failed to load planet texture!\n");
        success = false;
    }
    printf("planet loaded\n");
    return success;
}

void Engine::Update(){

};

void Engine::Render()
{
}

bool Engine::runLoop()
{
    //Load Media
    if (!Engine::loadMedia())
    {
        printf("failed to load media!\n");
    }
    else
    {
        bool quit = false;

        // the entities get loaded here?!
        Entity entity(200, 200);

        SDL_Rect wall;
        wall.x = 100;
        wall.y = 40;
        wall.w = 50;
        wall.h = 200;

        // end entities

        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                //user quits
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            Engine::Update();
            //clear screen
            SDL_SetRenderDrawColor(gRenderer, 40, 60, 120, 255);
            SDL_RenderClear(gRenderer);

            //render your stuffs here
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

            SDL_RenderDrawRect(gRenderer, &wall);
            entity.render();
            //         printf("rendering entity\n");
            //        std::cout << &gRenderer << std::endl;
            //Update the screen(s)
            SDL_RenderPresent(gRenderer);
        }
        return quit;
    }
};

void Engine::closeEngine()
{
    //Free loaded images
    gEntityTexture.free();
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
};
