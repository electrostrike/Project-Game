#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Texture.hpp"

const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;

const int PLAY_BUTTON_X = 300;
const int PLAY_BUTTON_Y = 300;

const int HOW_TO_PLAY_BUTTON_X = 300;
const int HOW_TO_PLAY_BUTTON_Y = 450;

class Button
{
    public:
        Button();
        Button(int x, int y, int w, int h);
        ~Button();
        int buttonSprite; // Mouse Out - Mouse Over - Mouse Down - Mouse Up
        void RenderButton(SDL_Renderer* renderer, Texture buttonTexture, SDL_Rect* clip);
        void HandleEvent(SDL_Event* e);

    private:
        int cur_x;
        int cur_y;
        int width;
        int height;
};

#endif // BUTTON_HPP
