#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.hpp"
#include "Button.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Rect clipHomeScreen = {0, 0, WIDTH, HEIGHT};
Texture homeScreen;

SDL_Rect clipPlayButton = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
Button play(PLAY_BUTTON_X, PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
Texture playButton;

SDL_Rect clipHowToPlayButton = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
Button howToPlay(HOW_TO_PLAY_BUTTON_X, HOW_TO_PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
Texture howToPlayButton;

SDL_Rect clipSettings = {0, 0, WIDTH / 2, HEIGHT / 2};
Texture settings;

Board board;

const int FRAME = 17;
int level = 0;
int gravity[] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};

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

void loadMedia()
{
    homeScreen.LoadTexture("image/homescreen.png", renderer);
    playButton.LoadTexture("image/playbutton.png", renderer);
    howToPlayButton.LoadTexture("image/howtoplaybutton.png", renderer);
    settings.LoadTexture("image/settings.png", renderer);
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
    srand(time(NULL));
    if (!init())
    {
        cout << "Failed to initialize\n";
    }
    else
    {
        loadMedia();
        bool quitHome = 0;
        SDL_Event eHome;
        while (!quitHome)
        {
            while (SDL_PollEvent(&eHome) != 0)
            {
                if (eHome.type == SDL_QUIT)
                    quitHome = 1;
                if (eHome.type == SDL_MOUSEBUTTONDOWN)
                {
                    play.HandleEvent(&eHome);
                    howToPlay.HandleEvent(&eHome);
                }
            }

            // load homescreen
            SDL_RenderClear(renderer);
            homeScreen.RenderTexture(renderer, 0, 0, &clipHomeScreen);
            playButton.RenderTexture(renderer, PLAY_BUTTON_X + 10, PLAY_BUTTON_Y + 10, &clipPlayButton);
            howToPlayButton.RenderTexture(renderer, HOW_TO_PLAY_BUTTON_X + 10, HOW_TO_PLAY_BUTTON_Y + 10, &clipHowToPlayButton);
            SDL_RenderPresent(renderer);

            // play screen
            if (play.buttonSprite == 2)
            {
                // playing
                level = 18;
                bool quitGame = 0;
                SDL_Event eGame;
                Tetromino curPiece = rand() % 7;
                curPiece.MoveToBoard();
                Tetromino nextPiece = rand() % 7;
                int moveTime = SDL_GetTicks();
                while (!quitGame)
                {
                    while (SDL_PollEvent(&eGame) != 0)
                    {
                        if (eGame.type == SDL_QUIT)
                        {
                            quitGame = 1;
                            quitHome = 1;
                            play.buttonSprite = 0;
                        }
                        if (eGame.type == SDL_KEYDOWN)
                        {
                            switch (eGame.key.keysym.sym)
                            {
                                case SDLK_ESCAPE:
                                {
                                    quitGame = 1;
                                    play.buttonSprite = 0;
                                    board.~Board();
                                    break;
                                }

                                case SDLK_DOWN:
                                {
                                    Tetromino tmpPiece = curPiece;
                                    tmpPiece.MoveDown();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.MoveDown();
                                    else
                                    {
                                        if (board.GameOver(curPiece))
                                            quitGame = 1;
                                        else
                                        {
                                            SDL_Delay(100);
                                            board.Unite(curPiece);
                                            board.ClearLines();
                                            curPiece = nextPiece;
                                            curPiece.MoveToBoard();
                                            nextPiece = rand() % 7;
                                            moveTime = SDL_GetTicks();
                                        }
                                    }
                                    break;
                                }

                                case SDLK_LEFT:
                                {
                                    Tetromino tmpPiece = curPiece;
                                    tmpPiece.MoveLeft();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.MoveLeft();
                                    break;
                                }

                                case SDLK_RIGHT:
                                {
                                    Tetromino tmpPiece = curPiece;
                                    tmpPiece.MoveRight();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.MoveRight();
                                    break;
                                }

                                case SDLK_x:
                                {
                                    Tetromino tmpPiece = curPiece;
                                    tmpPiece.RotateCW();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.RotateCW();
                                    break;
                                }

                                case SDLK_z:
                                {
                                    Tetromino tmpPiece = curPiece;
                                    tmpPiece.RotateCCW();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.RotateCCW();
                                    break;
                                }
                            }
                        }
                    }

                    SDL_RenderClear(renderer);
                    board.DrawBoard(renderer);
                    board.DrawTetromino(renderer);
                    curPiece.Draw(renderer);
                    nextPiece.Draw(renderer);
                    SDL_RenderPresent(renderer);

                    if (SDL_GetTicks() > moveTime)
                    {
                        moveTime += FRAME * gravity[level];
                        Tetromino tmpPiece = curPiece;
                        tmpPiece.MoveDown();
                        if (board.ValidMove(tmpPiece))
                            curPiece.MoveDown();
                        else
                        {
                            if (board.GameOver(curPiece))
                                quitGame = 1;
                            else
                            {
                                SDL_Delay(100);
                                board.Unite(curPiece);
                                board.ClearLines();
                                curPiece = nextPiece;
                                curPiece.MoveToBoard();
                                nextPiece = rand() % 7;
                                moveTime = SDL_GetTicks();
                            }
                        }
                    }
                }

                // game over
                if (play.buttonSprite == 2)
                {
                    bool returnToMenu = 0;
                    while (!returnToMenu)
                    {
                        while (SDL_PollEvent(&eGame) != 0)
                        {
                            if (eGame.type == SDL_QUIT)
                            {
                                quitGame = 1;
                                quitHome = 1;
                                returnToMenu = 1;
                                play.buttonSprite = 0;
                            }
                            if (eGame.type == SDL_KEYDOWN)
                            {
                                if (eGame.key.keysym.sym == SDLK_ESCAPE)
                                {
                                    quitGame = 1;
                                    returnToMenu = 1;
                                    play.buttonSprite = 0;
                                    board.~Board();
                                }
                            }
                        }
                        SDL_RenderClear(renderer);
                        board.DrawBoard(renderer);
                        board.DrawGameOver(renderer);
                        SDL_RenderPresent(renderer);
                    }
                }
            }

            // how to play screen
            if (howToPlay.buttonSprite == 2)
            {
                bool quitHTP = 0;
                SDL_Event eHTP;
                while (!quitHTP)
                {
                    while (SDL_PollEvent(&eHTP) != 0)
                    {
                        if (eHTP.type == SDL_KEYDOWN)
                        {
                            if (eHTP.key.keysym.sym == SDLK_ESCAPE)
                                quitHTP = 1, howToPlay.buttonSprite = 0;
                        }
                        if (eHTP.type == SDL_QUIT)
                            quitHTP = 1, quitHome = 1;
                    }

                    SDL_RenderClear(renderer);
                    homeScreen.RenderTexture(renderer, 0, 0, &clipHomeScreen);
                    settings.RenderTexture(renderer, WIDTH / 4, HEIGHT / 4, &clipSettings);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }
    close();
    return 0;
}
