#include "Board.hpp"

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init()
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
        SDL_RenderDrawLine(renderer, 250 + i * BLOCK_PIXEL, 0, 250 + i * BLOCK_PIXEL, 600);
    for (int j = 0; j <= BOARD_HEIGHT; j++)
        SDL_RenderDrawLine(renderer, 250, j * BLOCK_PIXEL, 550, j * BLOCK_PIXEL);
}

void Board::DrawGameOver(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xDC, 0xDC, 0xDC, 0xFF);
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            if (board[i][j] != -1)
            {
                SDL_Rect rect{i * BLOCK_PIXEL + 250 + 1, j * BLOCK_PIXEL + 1, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
}

void Board::DrawTetromino(SDL_Renderer* renderer)
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
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

                default:
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
                    break;
            }
            SDL_Rect rect{i * BLOCK_PIXEL + 250 + 1, j * BLOCK_PIXEL + 1, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
            SDL_RenderFillRect(renderer, &rect);
        }
}

void Board::DrawBlockCount(SDL_Renderer* renderer)
{
    SDL_Rect rect;

    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0xff, 0xff); // I
    rect = {BLOCK_POS_X - 40, BLOCK_POS_Y - 5, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff); // J
    rect = {BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 70, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0xff, 0x7f, 0x00, 0xff); // L
    rect = {BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 140, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff); // O
    rect = {BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 210, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff); // S
    rect = {BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 280, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0x80, 0x00, 0x80, 0xff); // T
    rect = {BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 350, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff); // Z
    rect = {BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 420, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
    SDL_RenderFillRect(renderer, &rect);


    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0xff, 0xff); // I drought
    rect = {BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 490, BLOCK_PIXEL - 1, BLOCK_PIXEL - 1};
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderDrawLine(renderer, BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 490, BLOCK_POS_X - 40 + BLOCK_PIXEL - 1, BLOCK_POS_Y - 5 + 490 + BLOCK_PIXEL - 1);
    SDL_RenderDrawLine(renderer, BLOCK_POS_X - 40, BLOCK_POS_Y - 5 + 490 + BLOCK_PIXEL - 1, BLOCK_POS_X - 40 + BLOCK_PIXEL - 1, BLOCK_POS_Y - 5 + 490);
}

bool Board::InBoard(int x, int y)
{
    return (x >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT);
}

bool Board::ValidMove(Tetromino tt)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (InBoard(i + tt.x, j + tt.y) && board[i + tt.x][j + tt.y] != -1 && tt.piece[tt.rotation][i][j] != 0)
                return 0;
            if (tt.piece[tt.rotation][i][j] != 0 && !InBoard(i + tt.x, j + tt.y))
                return 0;
        }
    return 1;
}

void Board::Unite(Tetromino tt)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (tt.piece[tt.rotation][i][j])
                board[i + tt.x][j + tt.y] = tt.block;
}

int Board::ClearLines()
{
    int linesCleared = 0;
    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
        bool filled = 1;
        for (int i = 0; i < BOARD_WIDTH; i++)
            if (board[i][j] == -1)
                filled = 0;
        if (filled)
        {
            linesCleared++;
            for (int y = j; y > 0; y--)
                for (int x = 0; x < BOARD_WIDTH; x++)
                    board[x][y] = board[x][y - 1];
            for (int x = 0; x < BOARD_WIDTH; x++)
                board[x][0] = -1;
        }
    }
    return linesCleared;
}

bool Board::GameOver(Tetromino tt)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (InBoard(i + tt.x, j + tt.y) && board[i + tt.x][j + tt.y] != -1 && tt.piece[tt.rotation][i][j] != 0)
                return 1;
    return 0;
}
