#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.hpp"
#include "Button.hpp"
#include "Tetromino.hpp"
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;

const int DEFAULT_X = 0;
const int DEFAULT_Y = 0;

const int PLAY_BUTTON_X = 300;
const int PLAY_BUTTON_Y = 300;

const int HOW_TO_PLAY_BUTTON_X = 300;
const int HOW_TO_PLAY_BUTTON_Y = 450;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Rect clipHomeScreen = {DEFAULT_X, DEFAULT_Y, WIDTH, HEIGHT};
Texture homeScreen;

SDL_Rect clipPlayButton = {DEFAULT_X, DEFAULT_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
Button play(PLAY_BUTTON_X, PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
Texture playButton;

SDL_Rect clipHowToPlayButton = {DEFAULT_X, DEFAULT_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
Button howToPlay(HOW_TO_PLAY_BUTTON_X, HOW_TO_PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
Texture howToPlayButton;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Unable to initialize SDL\n";
        cout << "Error: " << SDL_GetError() << "\n";
        return 0;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled\n";
		}
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "Unable to initialize Window\n";
            cout << "Error: " << SDL_GetError() << "\n";
            return 0;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            int IMGFlag = IMG_INIT_PNG;
            if (!(IMG_Init(IMGFlag) & IMGFlag))
            {
                cout << "Unable to initialize SDL_image\n";
                cout << "Error: " << IMG_GetError() << "\n";
                return 0;
            }

        }
    }
    return 1;
}

bool loadMedia()
{
    homeScreen.LoadTexture("image/homescreen.png", renderer);
    playButton.LoadTexture("image/playbutton.png", renderer);
    howToPlayButton.LoadTexture("image/howtoplaybutton.png", renderer);
    return 1;
}

void close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
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
            bool quit = 0;
            SDL_Event e;
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                        quit = 1;
                }
                SDL_RenderClear(renderer);
                homeScreen.RenderTexture(renderer, DEFAULT_X, DEFAULT_Y, &clipHomeScreen);
                playButton.RenderTexture(renderer, PLAY_BUTTON_X, PLAY_BUTTON_Y, &clipPlayButton);
                howToPlayButton.RenderTexture(renderer, HOW_TO_PLAY_BUTTON_X, HOW_TO_PLAY_BUTTON_Y, &clipHowToPlayButton);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}
