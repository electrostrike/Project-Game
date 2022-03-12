#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Surface* windowSurface = NULL;
SDL_Surface* currentSurface = NULL;

bool quit = 0;
SDL_Event e;

SDL_Surface* loadSurface(string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        cout << "Unable to load image: " << path.c_str() << "\n";
        cout << "Error: " << IMG_GetError() << "\n";
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, windowSurface->format, 0);
        if (optimizedSurface == NULL)
        {
            cout << "Unable to optimized image: " << path.c_str() << "\n";
            cout << "Error: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize\n";
        cout << "Error: " << SDL_GetError() << "\n";
        return 0;
    }
    else
    {
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "Window could not be created\n";
            cout << "Error: " << SDL_GetError() << "\n";
            return 0;
        }
        else
        {
            if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
            {
                cout << "SDL_image could not initialize\n";
                cout << "Error: " << IMG_GetError() << "\n";
            }
        }
        windowSurface = SDL_GetWindowSurface(window);
    }
    return 1;
}

bool loadMedia()
{
    currentSurface = loadSurface("image/homescreen_800x600.png");
    if (currentSurface == NULL)
    {
        cout << "Failed to load image\n";
        return 0;
    }
    return 1;
}

void close()
{
    SDL_FreeSurface(windowSurface);
    windowSurface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    IMG_Quit();
}

int main(int argc, char* argv[])
{
    if (!init())
    {
        cout << "Failed to initialize\n";
    }
    else
    {
        if (!loadMedia())
        {
            cout << "Failed to load media\n";
        }
        else
        {
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                        quit = 1;
                }
                SDL_BlitSurface(currentSurface, NULL, windowSurface, NULL);
                SDL_UpdateWindowSurface(window);
            }
        }
    }
    close();
    return 0;
}
