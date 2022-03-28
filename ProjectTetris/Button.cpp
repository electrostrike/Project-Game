#include "Button.hpp"

Button::Button()
{
    buttonSprite = 0;
    cur_x = 0;
    cur_y = 0;
    width = 0;
    height = 0;
}

Button::Button(int x, int y, int w, int h)
{
    buttonSprite = 0;
    cur_x = x;
    cur_y = y;
    width = w;
    height = h;
}

Button::~Button()
{
    buttonSprite = 0;
    cur_x = 0;
    cur_y = 0;
    width = 0;
    height = 0;
}

void Button::RenderButton(SDL_Renderer* renderer, Texture buttonTexture, SDL_Rect* clip)
{
    buttonTexture.RenderTexture(renderer, cur_x, cur_y, clip);
}

void Button::HandleEvent(SDL_Event* e)
{
     if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < cur_x || x > cur_x + width || y < cur_y || y > cur_y + height) // outside the button
        {
            buttonSprite = 0;
        }
        else // inside the button
        {
            if (e->type == SDL_MOUSEMOTION)
                buttonSprite = 1;
            if (e->type == SDL_MOUSEBUTTONDOWN)
                buttonSprite = 2;
        }
    }
}
