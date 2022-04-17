#ifndef BOARD_HPP
#define BOARD_HPP

#include "Texture.hpp"
#include "Tetromino.hpp"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int SQUARE = 30; // = HEIGHT / BOARD_HEIGHT

class Board
{
    public:
        Board();
        ~Board();
        void DrawBoard(SDL_Renderer* renderer);
        void DrawTetromino(SDL_Renderer* renderer);
        bool InBoard(int x, int y);
        bool ValidMove(Tetromino tt);
        void Unite(Tetromino tt);
        bool GameOver(Tetromino tt);

    private:
        int board[BOARD_WIDTH][BOARD_HEIGHT]; // I - J - L - O - S - T - Z
};

#endif // BOARD_HPP
