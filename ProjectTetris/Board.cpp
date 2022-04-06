#include "Board.hpp"

Board::Board()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            board[i][j] = -1;
}

Board::~Board()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            board[i][j] = -1;
}

void Board::DrawBoard(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect rect{0, 0, 800, 600};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0xDC, 0xDC, 0xDC, 0xFF);
    for (int i = 0; i <= BOARD_WIDTH; i++)
        SDL_RenderDrawLine(renderer, 250 + i * 30, 0, 250 + i * 30, 600);
    for (int j = 0; j <= BOARD_HEIGHT; j++)
        SDL_RenderDrawLine(renderer, 250, j * 30, 550, j * 30);
}

void Board::DrawTetromino(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
        {
            switch (board[x][y])
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
            SDL_Rect rect{x * 30 + 250 + 1, y * 30 + 1, 30 - 1, 30 - 1};
            SDL_RenderFillRect(renderer, &rect);
        }
}
