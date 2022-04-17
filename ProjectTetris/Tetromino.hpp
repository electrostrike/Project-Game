#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "Texture.hpp"

using namespace std;

class Tetromino
{
    public:
        Tetromino(int block);
        ~Tetromino();
        void Draw(SDL_Renderer* renderer);
        void MoveLeft();
        void MoveRight();
        void MoveDown();
        void RotateCW(); // rotate right
        void RotateCCW(); // rotate left
        int block; //I - J - L - O - S - T - Z
        int x;
        int y;
        int rotation; //0 - 90 - 180 - 270
        bool piece[4][4][4]; //Rotation - Y (Row) - X (Column)

    private:
};

#endif // TETROMINO_HPP
