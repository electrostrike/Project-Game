#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "Texture.hpp"

using namespace std;

class Tetromino
{
    public:
        Tetromino(int block);
        void Draw(SDL_Renderer* renderer);
        void MoveLeft();
        void MoveRight();
        void MoveDown();
        void RotateCW();
        void RotateCCW();

    private:
        int cur_block; //I - J - L - O - S - T - Z
        int cur_x;
        int cur_y;
        int cur_rotation; //0 - 90 - 180 - 270
        bool cur_piece[4][4][4]; //Rotation - Y (Row) - X (Column)
};

#endif // TETROMINO_HPP
