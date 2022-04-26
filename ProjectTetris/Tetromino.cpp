#include "Tetromino.hpp"

Tetromino::Tetromino()
{

}

Tetromino::~Tetromino()
{

}

void Tetromino::Init(int _block, int _rotation, int _x, int _y)
{
    block = _block;
    rotation = _rotation;
    x = _x;
    y = _y;
    for (int rotation = 0; rotation < 4; rotation++)
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                piece[rotation][i][j] = 0;
    switch (block)
    {
        case 0: // I
            piece[0][0][1] = piece[0][1][1] = piece[0][2][1] = piece[0][3][1] = 1;  // 0000
                                                                                    // 1111
                                                                                    // 0000
                                                                                    // 0000

            piece[1][2][0] = piece[1][2][1] = piece[1][2][2] = piece[1][2][3] = 1;  // 0010
                                                                                    // 0010
                                                                                    // 0010
                                                                                    // 0010

            piece[2][0][2] = piece[2][1][2] = piece[2][2][2] = piece[2][3][2] = 1;  // 0000
                                                                                    // 0000
                                                                                    // 1111
                                                                                    // 0000

            piece[3][1][0] = piece[3][1][1] = piece[3][1][2] = piece[3][1][3] = 1;  // 0100
                                                                                    // 0100
                                                                                    // 0100
                                                                                    // 0100

            break;

        case 1: // J
            piece[0][0][1] = piece[0][0][2] = piece[0][1][2] = piece[0][2][2] = 1;  // 0000
                                                                                    // 1000
                                                                                    // 1110
                                                                                    // 0000

            piece[1][2][1] = piece[1][1][1] = piece[1][1][2] = piece[1][1][3] = 1;  // 0000
                                                                                    // 0110
                                                                                    // 0100
                                                                                    // 0100

            piece[2][0][2] = piece[2][1][2] = piece[2][2][2] = piece[2][2][3] = 1;  // 0000
                                                                                    // 0000
                                                                                    // 1110
                                                                                    // 0010

            piece[3][1][1] = piece[3][1][2] = piece[3][1][3] = piece[3][0][3] = 1;  // 0000
                                                                                    // 0100
                                                                                    // 0100
                                                                                    // 1100

            break;

        case 2: // L
            piece[0][2][1] = piece[0][2][2] = piece[0][1][2] = piece[0][0][2] = 1;  // 0000
                                                                                    // 0010
                                                                                    // 1110
                                                                                    // 0000

            piece[1][2][3] = piece[1][1][3] = piece[1][1][2] = piece[1][1][1] = 1;  // 0000
                                                                                    // 0100
                                                                                    // 0100
                                                                                    // 0110

            piece[2][0][3] = piece[2][0][2] = piece[2][1][2] = piece[2][2][2] = 1;  // 0000
                                                                                    // 0000
                                                                                    // 1110
                                                                                    // 1000

            piece[3][0][1] = piece[3][1][1] = piece[3][1][2] = piece[3][1][3] = 1;  // 0000
                                                                                    // 1100
                                                                                    // 0100
                                                                                    // 0100

            break;

        case 3: // O
            piece[0][1][1] = piece[0][2][1] = piece[0][1][2] = piece[0][2][2] = 1;  // 0000
                                                                                    // 0110
                                                                                    // 0110
                                                                                    // 0000

            piece[1][1][1] = piece[1][2][1] = piece[1][1][2] = piece[1][2][2] = 1;  // 0000
                                                                                    // 0110
                                                                                    // 0110
                                                                                    // 0000

            piece[2][1][1] = piece[2][2][1] = piece[2][1][2] = piece[2][2][2] = 1;  // 0000
                                                                                    // 0110
                                                                                    // 0110
                                                                                    // 0000

            piece[3][1][1] = piece[3][2][1] = piece[3][1][2] = piece[3][2][2] = 1;  // 0000
                                                                                    // 0110
                                                                                    // 0110
                                                                                    // 0000

            break;

        case 4: // S
            piece[0][0][2] = piece[0][1][2] = piece[0][1][1] = piece[0][2][1] = 1;  // 0000
                                                                                    // 0110
                                                                                    // 1100
                                                                                    // 0000

            piece[1][1][1] = piece[1][1][2] = piece[1][2][2] = piece[1][2][3] = 1;  // 0000
                                                                                    // 0100
                                                                                    // 0110
                                                                                    // 0010

            piece[2][2][2] = piece[2][1][2] = piece[2][1][3] = piece[2][0][3] = 1;  // 0000
                                                                                    // 0000
                                                                                    // 0110
                                                                                    // 1100

            piece[3][1][3] = piece[3][1][2] = piece[3][0][2] = piece[3][0][1] = 1;  // 0000
                                                                                    // 1000
                                                                                    // 1100
                                                                                    // 0100

            break;

        case 5: // T
            piece[0][1][1] = piece[0][0][2] = piece[0][1][2] = piece[0][2][2] = 1;  // 0000
                                                                                    // 0100
                                                                                    // 1110
                                                                                    // 0000

            piece[1][2][2] = piece[1][1][1] = piece[1][1][2] = piece[1][1][3] = 1;  // 0000
                                                                                    // 0100
                                                                                    // 0110
                                                                                    // 0100

            piece[2][1][3] = piece[2][0][2] = piece[2][1][2] = piece[2][2][2] = 1;  // 0000
                                                                                    // 0000
                                                                                    // 1110
                                                                                    // 0100

            piece[3][0][2] = piece[3][1][1] = piece[3][1][2] = piece[3][1][3] = 1;  // 0000
                                                                                    // 0100
                                                                                    // 1100
                                                                                    // 0100

            break;

        case 6: // Z
            piece[0][0][1] = piece[0][1][1] = piece[0][1][2] = piece[0][2][2] = 1;  // 0000
                                                                                    // 1100
                                                                                    // 0110
                                                                                    // 0000

            piece[1][2][1] = piece[1][2][2] = piece[1][1][2] = piece[1][1][3] = 1;  // 0000
                                                                                    // 0010
                                                                                    // 0110
                                                                                    // 0100

            piece[2][2][3] = piece[2][1][3] = piece[2][1][2] = piece[2][0][2] = 1;  // 0000
                                                                                    // 0000
                                                                                    // 1100
                                                                                    // 0110

            piece[3][0][3] = piece[3][0][2] = piece[3][1][2] = piece[3][1][1] = 1;  // 0000
                                                                                    // 0100
                                                                                    // 1100
                                                                                    // 1000

            break;
    }
}

void Tetromino::Draw(SDL_Renderer *renderer)
{
    //set color
    switch (block)
    {
        case 0: // I
            SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0xff, 0xff);
            break;

        case 1: // J
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
            break;

        case 2: // L
            SDL_SetRenderDrawColor(renderer, 0xff, 0x7f, 0x00, 0xff);
            break;

        case 3: // O
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);
            break;

        case 4: // S
            SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
            break;

        case 5: // T
            SDL_SetRenderDrawColor(renderer, 0x80, 0x00, 0x80, 0xff);
            break;

        case 6: // Z
            SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
            break;

    }

    //fill color
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (piece[rotation][i][j])
            {
                SDL_Rect rect{(x + i) * 30 + 1 + 250, (y + j) * 30 + 1, 30 - 1, 30 - 1};
                SDL_RenderFillRect(renderer, &rect);
            }
}

void Tetromino::MoveLeft()
{
    x--;
}

void Tetromino::MoveRight()
{
    x++;
}

void Tetromino::MoveDown()
{
    y++;
}

void Tetromino::RotateCW() //rotate right
{
    rotation++;
    if (rotation == 4)
        rotation = 0;
}

void Tetromino::RotateCCW() // rotate left
{
    rotation--;
    if (rotation == -1)
        rotation = 3;
}

void Tetromino::Move(int _x, int _y)
{
    x += _x;
    y += _y;
}
