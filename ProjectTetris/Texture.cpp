#include "Texture.hpp"

Texture::Texture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    Texture::Free();
}

void Texture::LoadTexture(string path, SDL_Renderer* renderer)
{
    Texture::Free();
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

void Texture::Free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::LoadText(string text, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer)
{
    Texture::Free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        cout << "Unable to render text surface\n";
        cout << "Error: " << TTF_GetError();
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == NULL )
        {
            cout << "Unable to create texture from rendered text\n";
            cout << "SDL Error: " << SDL_GetError() << "\n";
        }
        else
        {
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
}
