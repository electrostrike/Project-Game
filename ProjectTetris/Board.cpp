#include "Board.hpp"

Board::Board()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            board[i][j] = -1;
}

Board::~Board()
{

}

void Board::DrawBoard(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect rect{0, 0, 800, 600};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0xDC, 0xDC, 0xDC, 0xFF);
    for (int i = 0; i <= BOARD_WIDTH; i++)
        SDL_RenderDrawLine(renderer, 250 + i * SQUARE, 0, 250 + i * SQUARE, 600);
    for (int j = 0; j <= BOARD_HEIGHT; j++)
        SDL_RenderDrawLine(renderer, 250, j * SQUARE, 550, j * SQUARE);
}

void Board::DrawTetromino(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 20; j++)
        {
            switch (board[i][j])
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
            SDL_Rect rect{i * SQUARE + 250 + 1, j * SQUARE + 1, SQUARE - 1, SQUARE - 1};
            SDL_RenderFillRect(renderer, &rect);
        }
}

bool Board::ValidMove(Tetromino tt)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (board[i + tt.x][j + tt.y] != -1 && tt.piece[tt.rotation][i][j] != 0)
                return 0;
            if (tt.piece[tt.rotation][i][j] != 0 && (i + tt.x < 0 || i + tt.x >= BOARD_WIDTH || j + tt.y >= BOARD_HEIGHT))
                return 0;
        }
    return 1;
}

bool Board::GameOver(Tetromino tt)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i + tt.x][j + tt.y] != -1 && tt.piece[tt.rotation][i][j] != 0)
                return 0;
    return 1;
}
