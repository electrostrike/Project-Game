#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

const int HOW_TO_PLAY_X = 100;
const int HOW_TO_PLAY_Y = 150;

const int TEXT_PIXEL = 20;

const int TEXT_POS_X = 600;
const int TEXT_POS_Y = 250;

class Texture
{
    public:
        Texture();
        ~Texture();

        void LoadTexture(string path, SDL_Renderer* renderer);
        void RenderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip);
        void Free();
        void LoadText(string text, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);


    private:
        SDL_Texture* texture;
        int width;
        int height;
};

#endif // TEXTURE_HPP
