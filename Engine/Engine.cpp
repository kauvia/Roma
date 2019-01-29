#include "Engine.h"

int Engine::SCREEN_WIDTH = 1000;
int Engine::SCREEN_HEIGHT = 700;
int Engine::SCREEN_X = 100;
int Engine::SCREEN_Y = 0;

//Window to render to
SDL_Window *Engine::gWindow = nullptr;
//Window renderer
SDL_Renderer *Engine::gRenderer = nullptr;
//Global font
TTF_Font *Engine::gFont = nullptr;
//Event handler
SDL_Event Engine::e;
//Rectangles
SDL_Rect gRect;

// test entities

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
    // INIT TEST FOR ENTITIES

    return success;
}

bool Engine::loadMedia()
{
    bool success = true;
    return success;
}

void Engine::Update(){

};

void Engine::Render()
{
    //clear screen
    SDL_SetRenderDrawColor(gRenderer, 40, 60, 120, 255);
    SDL_RenderClear(gRenderer);

    //render your stuffs here

    gRect = {100, 100, 125, 250}; //ONLY NEED ONE SDLRECT
    SDL_SetRenderDrawColor(gRenderer, 200, 175, 20, 255);
    SDL_RenderFillRect(gRenderer, &gRect);
    //

    // this renders all
    SDL_RenderPresent(gRenderer);
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
        Entity testEnt(100, 100, 10, 10);
        Entity testEnt2(255, 255, 10, 10);

        int v;
        int w;
        int x;
        int y;
        // end entities

        while (!quit)
        {
            auto start = std::chrono::system_clock::now();

            while (SDL_PollEvent(&e) != 0)
            {
                //user quits
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }

            Engine::Update();

            v = rand() % 3 - 1;
            w = rand() % 3 - 1;
            x = rand() % 3 - 1;
            y = rand() % 3 - 1;
            testEnt.update(v, w);
            testEnt2.update(x, y);

            //AKTUALLY RENDER();

            //clear screen
            SDL_SetRenderDrawColor(gRenderer, 40, 60, 120, 255);
            SDL_RenderClear(gRenderer);

            //render your stuffs here

            testEnt.render(gRenderer, gRect);
            testEnt2.render(gRenderer, gRect);

            // gRect = {100, 100, 125, 250}; //ONLY NEED ONE SDLRECT
            // SDL_SetRenderDrawColor(gRenderer, 200, 175, 20, 255);
            // SDL_RenderFillRect(gRenderer, &gRect);
            //

            // this renders all
            SDL_RenderPresent(gRenderer);

            auto end = std::chrono::system_clock::now();

            std::chrono::duration<double> elapsed_seconds = end - start;
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);

            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << " fps: " << 1 / elapsed_seconds.count() << "fps\n";
        }
        return quit;
    }
};

void Engine::closeEngine()
{
    //Free loaded images

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
};
