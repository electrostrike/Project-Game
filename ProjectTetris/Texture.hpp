#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <cstring>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

class Texture
{
    public:
        Texture();
        ~Texture();

        void LoadTexture(string path, SDL_Renderer* renderer);
        void RenderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip);

    private:
        SDL_Texture* texture;
        int width;
        int height;
};

#endif // TEXTURE_HPP
