#ifndef GAME_HPP
#define GAME_HPP

#include "Texture.hpp"
#include "Button.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"

const int FRAME = 17; // ceil(1000 / 60)
const int gravity[] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};
const int points[] = {0, 40, 100, 300, 1200};

class Game
{
    public:
        Game();
        ~Game();

        SDL_Renderer* _renderer();

        void LoadMedia();

        void Run();
        void RunGame();
        void RunSettings();
        void Progress();

        void RenderBoard();
        void RenderText();
        void RenderGameOver();
        void RenderBlockCount();

        string ToString(int x, int n);
        int Roll(int curRNG);

        bool Init();
        void Close();

    private:
        //Window
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Color textColor = {255, 255, 255};

        //Main Menu
        bool quit = 0;
        SDL_Rect clipHomeScreen = {0, 0, WIDTH, HEIGHT};
        SDL_Rect clipPlayButton = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
        SDL_Rect clipSettingsButton = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
        SDL_Rect clipSettingsScreen = {0, 0, WIDTH - HOW_TO_PLAY_X * 2, HEIGHT - HOW_TO_PLAY_Y * 2};
        Texture homeScreen, settingsScreen, playButton, settingsButton;
        Button play = {PLAY_BUTTON_X, PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};
        Button settings = {HOW_TO_PLAY_BUTTON_X, HOW_TO_PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};

        //Game UI
        SDL_Rect textClip5 = {0, 0, TEXT_PIXEL * 5, TEXT_PIXEL};
        SDL_Rect textClip4 = {0, 0, TEXT_PIXEL * 4, TEXT_PIXEL};
        SDL_Rect textClip7 = {0, 0, TEXT_PIXEL * 7, TEXT_PIXEL};
        SDL_Rect textClip3 = {0, 0, TEXT_PIXEL * 3, TEXT_PIXEL};
        Texture scoreText, linesText, levelText, nextText;
        Texture scoreNum, linesNum, levelNum;
        Texture block[7], drought;

        //Game
        Tetromino curPiece, nextPiece, tmpPiece;
        int blockCount[7], droughtCount, moveTime, linesCleared, linesCap, lines, score, startLevel, level, curRNG, nextRNG;
        bool playMusic, playHitsound;
        Board board;

        //SFX
        Mix_Music* bgm;
        Mix_Chunk* moveTetromino;
        Mix_Chunk* dropTetromino;
        Mix_Chunk* clearNormal;
        Mix_Chunk* clearTetris;
        Mix_Chunk* levelUp;
        Mix_Chunk* gameOver;
};

#endif // GAME_HPP
