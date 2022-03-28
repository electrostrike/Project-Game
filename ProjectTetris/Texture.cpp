#include "Texture.hpp"

Texture::Texture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    if (texture != NULL)
    {
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::LoadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* loadedTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        cout << "Unable to load image: " << path.c_str() << "\n";
        cout << "Error: " << IMG_GetError() << "\n";
    }
    else
    {
        loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (loadedTexture == NULL)
        {
            cout << "Unable to create texture from surface: " << path.c_str() << "\n";
            cout << "Error: " << SDL_GetError() << "\n";
        }
        else
        {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    texture = loadedTexture;
}

void Texture::RenderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderRect = {x, y, width, height};
    if (clip != NULL)
    {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }
    SDL_RenderCopy(renderer, texture, NULL, &renderRect);
}
