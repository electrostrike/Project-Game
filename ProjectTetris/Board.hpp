#ifndef BOARD_HPP
#define BOARD_HPP

#include "Texture.hpp"
#include "Tetromino.hpp"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

const int BLOCK_COUNT_X = 180;
const int BLOCK_COUNT_Y = 45;

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
