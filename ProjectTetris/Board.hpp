#ifndef BOARD_HPP
#define BOARD_HPP

#include "Texture.hpp"
#include "Tetromino.hpp"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

const int BLOCK_POS_X = 180;
const int BLOCK_POS_Y = 45;

const int FRAME = 17; // ceil(1000 / 60)
const int gravity[] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1};
const int points[] = {0, 40, 100, 300, 1200};

class Board
{
    public:
        Board();
        ~Board();

        void Init();
        void DrawBoard(SDL_Renderer* renderer);
        void DrawTetromino(SDL_Renderer* renderer);
        void DrawGameOver(SDL_Renderer* renderer);
        void DrawBlockCount(SDL_Renderer* renderer);

        bool InBoard(int x, int y);
        bool ValidMove(Tetromino tt);
        bool GameOver(Tetromino tt);
        void Unite(Tetromino tt);
        int ClearLines();

    private:
        int board[BOARD_WIDTH][BOARD_HEIGHT]; // I - J - L - O - S - T - Z
};

#endif // BOARD_HPP
