#ifndef TETROMINO_HPP
#define TETROMINO_HPP
#include "Texture.hpp"

using namespace std;

const int BLOCK_PIXEL = 30;

class Tetromino
{
    public:
        Tetromino(); // piece initialize at queue
        ~Tetromino();
        void Move(int _x, int _y); // move piece from queue to board

        void Init(int _block, int _rotation, int _x, int _y);
        void Draw(SDL_Renderer* renderer);

        void MoveLeft();
        void MoveRight();
        void MoveDown();
        void RotateCW(); // rotate right
        void RotateCCW(); // rotate left

        // public variables for easy access
        int block; //I - J - L - O - S - T - Z
        int x;
        int y;
        int rotation; //0 - 90 - 180 - 270
        bool piece[4][4][4]; //Rotation - Y (Row) - X (Column)

    private:
};

#endif // TETROMINO_HPP
