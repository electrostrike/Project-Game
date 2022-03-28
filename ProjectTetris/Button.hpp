#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Texture.hpp"

class Button
{
    public:
        Button();
        Button(int x, int y, int w, int h);
        ~Button();
        void RenderButton(SDL_Renderer* renderer, Texture buttonTexture, SDL_Rect* clip);
        void HandleEvent(SDL_Event* e);

    private:
        int buttonSprite; // Mouse Out - Mouse Over - Mouse Down - Mouse Up
        int cur_x;
        int cur_y;
        int width;
        int height;
};

#endif // BUTTON_HPP
