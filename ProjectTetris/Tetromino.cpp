#include "Tetromino.hpp"

void Tetromino::Init(int block)
{
    cur_rotation = 0;
    cur_x = 0;
    cur_y = 0;
    cur_block = block;
    for (int rotation = 0; rotation < 4; rotation++)
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                cur_piece[rotation][y][x] = 0;
    switch (block)
    {
        case 0: // I
            cur_piece[0][1][0] = cur_piece[0][1][1] = cur_piece[0][1][2] = cur_piece[0][1][3] = 1;  // 0000
                                                                                                    // 1111
                                                                                                    // 0000
                                                                                                    // 0000

            cur_piece[1][0][2] = cur_piece[1][1][2] = cur_piece[1][2][2] = cur_piece[1][3][2] = 1;  // 0010
                                                                                                    // 0010
                                                                                                    // 0010
                                                                                                    // 0010

            cur_piece[2][2][0] = cur_piece[2][2][1] = cur_piece[2][2][2] = cur_piece[2][2][3] = 1;  // 0000
                                                                                                    // 0000
                                                                                                    // 1111
                                                                                                    // 0000

            cur_piece[3][0][1] = cur_piece[3][1][1] = cur_piece[3][2][1] = cur_piece[3][3][1] = 1;  // 0100
                                                                                                    // 0100
                                                                                                    // 0100
                                                                                                    // 0100

            break;

        case 1: // J
            cur_piece[0][1][0] = cur_piece[0][2][0] = cur_piece[0][2][1] = cur_piece[0][2][2] = 1;  // 0000
                                                                                                    // 1000
                                                                                                    // 1110
                                                                                                    // 0000

            cur_piece[1][1][2] = cur_piece[1][1][1] = cur_piece[1][2][1] = cur_piece[1][3][1] = 1;  // 0000
                                                                                                    // 0110
                                                                                                    // 0100
                                                                                                    // 0100

            cur_piece[2][2][0] = cur_piece[2][2][1] = cur_piece[2][2][2] = cur_piece[2][3][2] = 1;  // 0000
                                                                                                    // 0000
                                                                                                    // 1110
                                                                                                    // 0010

            cur_piece[3][1][1] = cur_piece[3][2][1] = cur_piece[3][3][1] = cur_piece[3][3][0] = 1;  // 0000
                                                                                                    // 0100
                                                                                                    // 0100
                                                                                                    // 1100

            break;

        case 2: // L
            cur_piece[0][1][2] = cur_piece[0][2][2] = cur_piece[0][2][1] = cur_piece[0][2][0] = 1;  // 0000
                                                                                                    // 0010
                                                                                                    // 1110
                                                                                                    // 0000

            cur_piece[1][3][2] = cur_piece[1][3][1] = cur_piece[1][2][1] = cur_piece[1][1][1] = 1;  // 0000
                                                                                                    // 0100
                                                                                                    // 0100
                                                                                                    // 0110

            cur_piece[2][3][0] = cur_piece[2][2][0] = cur_piece[2][2][1] = cur_piece[2][2][2] = 1;  // 0000
                                                                                                    // 0000
                                                                                                    // 1110
                                                                                                    // 1000

            cur_piece[3][1][0] = cur_piece[3][1][1] = cur_piece[3][2][1] = cur_piece[3][3][1] = 1;  // 0000
                                                                                                    // 1100
                                                                                                    // 0100
                                                                                                    // 0100

            break;

        case 3: // O
            cur_piece[0][1][1] = cur_piece[0][1][2] = cur_piece[0][2][1] = cur_piece[0][2][2] = 1;  // 0000
                                                                                                    // 0110
                                                                                                    // 0110
                                                                                                    // 0000

            cur_piece[1][1][1] = cur_piece[1][1][2] = cur_piece[1][2][1] = cur_piece[1][2][2] = 1;  // 0000
                                                                                                    // 0110
                                                                                                    // 0110
                                                                                                    // 0000

            cur_piece[2][1][1] = cur_piece[2][1][2] = cur_piece[2][2][1] = cur_piece[2][2][2] = 1;  // 0000
                                                                                                    // 0110
                                                                                                    // 0110
                                                                                                    // 0000

            cur_piece[3][1][1] = cur_piece[3][1][2] = cur_piece[3][2][1] = cur_piece[3][2][2] = 1;  // 0000
                                                                                                    // 0110
                                                                                                    // 0110
                                                                                                    // 0000

            break;

        case 4: // S
            cur_piece[0][2][0] = cur_piece[0][2][1] = cur_piece[0][1][1] = cur_piece[0][1][2] = 1;  // 0000
                                                                                                    // 0110
                                                                                                    // 1100
                                                                                                    // 0000

            cur_piece[1][1][1] = cur_piece[1][2][1] = cur_piece[1][2][2] = cur_piece[1][3][2] = 1;  // 0000
                                                                                                    // 0100
                                                                                                    // 0110
                                                                                                    // 0010

            cur_piece[2][2][2] = cur_piece[2][2][1] = cur_piece[2][3][1] = cur_piece[2][3][0] = 1;  // 0000
                                                                                                    // 0000
                                                                                                    // 0110
                                                                                                    // 1100

            cur_piece[3][3][1] = cur_piece[3][2][1] = cur_piece[3][2][0] = cur_piece[3][1][0] = 1;  // 0000
                                                                                                    // 1000
                                                                                                    // 1100
                                                                                                    // 0100

            break;

        case 5: // T
            cur_piece[0][1][1] = cur_piece[0][2][0] = cur_piece[0][2][1] = cur_piece[0][2][2] = 1;  // 0000
                                                                                                    // 0100
                                                                                                    // 1110
                                                                                                    // 0000

            cur_piece[1][2][2] = cur_piece[1][1][1] = cur_piece[1][2][1] = cur_piece[1][3][1] = 1;  // 0000
                                                                                                    // 0100
                                                                                                    // 0110
                                                                                                    // 0100

            cur_piece[2][3][1] = cur_piece[2][2][0] = cur_piece[2][2][1] = cur_piece[2][2][2] = 1;  // 0000
                                                                                                    // 0000
                                                                                                    // 1110
                                                                                                    // 0100

            cur_piece[3][2][0] = cur_piece[3][1][1] = cur_piece[3][2][1] = cur_piece[3][3][1] = 1;  // 0000
                                                                                                    // 0100
                                                                                                    // 1100
                                                                                                    // 0100

            break;

        case 6: // Z
            cur_piece[0][1][0] = cur_piece[0][1][1] = cur_piece[0][2][1] = cur_piece[0][2][2] = 1;  // 0000
                                                                                                    // 1100
                                                                                                    // 0110
                                                                                                    // 0000

            cur_piece[1][1][2] = cur_piece[1][2][2] = cur_piece[1][2][1] = cur_piece[1][3][1] = 1;  // 0000
                                                                                                    // 0010
                                                                                                    // 0110
                                                                                                    // 0100

            cur_piece[2][3][2] = cur_piece[2][3][1] = cur_piece[2][2][1] = cur_piece[2][2][0] = 1;  // 0000
                                                                                                    // 0000
                                                                                                    // 1100
                                                                                                    // 0110

            cur_piece[3][3][0] = cur_piece[3][2][0] = cur_piece[3][2][1] = cur_piece[3][1][1] = 1;  // 0000
                                                                                                    // 0100
                                                                                                    // 1100
                                                                                                    // 1000

            break;
    }
}

void Tetromino::Draw(SDL_Renderer *renderer)
{
    //set color
    switch (cur_block)
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
    for (auto y = 0; y < 4; y++)
        for (auto x = 0; x < 4; x++)
            if (cur_piece[cur_rotation][y][x])
            {
                SDL_Rect rect{/*x, y, w, h*/};
                SDL_RenderFillRect(renderer, &rect);
            }
}

void Tetromino::MoveLeft()
{
    cur_x++;
}

void Tetromino::MoveRight()
{
    cur_x--;
}

void Tetromino::MoveDown()
{
    cur_y++;
}

void Tetromino::RotateCW() //rotate right
{
    cur_rotation++;
    if (cur_rotation == 4)
        cur_rotation = 0;
}

void Tetromino::RotateCCW() // rotate left
{
    cur_rotation--;
    if (cur_rotation == -1)
        cur_rotation = 3;
}

