#include "Texture.hpp"
#include "Button.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

TTF_Font* font = NULL;
SDL_Color textColor = {255, 255, 255};

Texture scoreText, levelText, linesText;
SDL_Rect textClip5 = {0, 0, TEXT_PIXEL * 5, TEXT_PIXEL};

Texture nextText;
SDL_Rect textClip4 = {0, 0, TEXT_PIXEL * 4, TEXT_PIXEL};

Texture totalScore;
SDL_Rect textClip7 = {0, 0, TEXT_PIXEL * 7, TEXT_PIXEL};

Texture totalLines, totalLevel, blockType[7], drought;
SDL_Rect textClip3 = {0, 0, TEXT_PIXEL * 3, TEXT_PIXEL};
int blockCount[7], droughtCount;

SDL_Rect clipHomeScreen = {0, 0, WIDTH, HEIGHT};
Texture homeScreen;

SDL_Rect clipPlayButton = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
Button play(PLAY_BUTTON_X, PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
Texture playButton;

SDL_Rect clipHowToPlayButton = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
Button howToPlay(HOW_TO_PLAY_BUTTON_X, HOW_TO_PLAY_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT);
Texture howToPlayButton;

SDL_Rect clipSettings = {0, 0, WIDTH / 2, HEIGHT / 2};
Texture settings;

Tetromino curPiece, nextPiece, tmpPiece;

Board board;

int moveTime, linesCleared, linesCap, lines, score, startLevel, level, curRNG, nextRNG;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "Unable to initialize SDL\n";
        cout << "Error: " << SDL_GetError() << "\n";
        return 0;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled\n";
		}
        window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "Unable to initialize Window\n";
            cout << "Error: " << SDL_GetError() << "\n";
            return 0;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            int IMGFlag = IMG_INIT_PNG;
            if (!(IMG_Init(IMGFlag) & IMGFlag))
            {
                cout << "Unable to initialize SDL_image\n";
                cout << "Error: " << IMG_GetError() << "\n";
                return 0;
            }
            if (TTF_Init() == -1)
            {
                cout << "Unable to initialize SDL_ttf\n";
                cout << "Error: " << TTF_GetError() << "\n";
                return 0;
            }
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                cout << "SDL_mixer could not initialize\n";
                cout << "Error: " << Mix_GetError() << "\n";
                return 0;
            }
        }
    }
    return 1;
}

void loadMedia()
{
    homeScreen.LoadTexture("image/homescreen.png", renderer);
    playButton.LoadTexture("image/playbutton.png", renderer);
    howToPlayButton.LoadTexture("image/howtoplaybutton.png", renderer);
    settings.LoadTexture("image/settings.png", renderer);

    font = TTF_OpenFont("font/PressStart2P-vaV7.ttf", 28);
    nextText.LoadText("NEXT", textColor, font, renderer);
    scoreText.LoadText("SCORE", textColor, font, renderer);
    levelText.LoadText("LEVEL", textColor, font, renderer);
    linesText.LoadText("LINES", textColor, font, renderer);
}

void close()
{
    homeScreen.Free();
    playButton.Free();
    howToPlayButton.Free();
    settings.Free();

    TTF_CloseFont(font);
    font = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}

// NTSC randomizer
int roll(int preRNG)
{
    int curRNG = rand() % 7;
    if (curRNG == preRNG)
        curRNG = rand() % 7;
    return curRNG;
}

string toString(int x, int n)
{
    string res = "";
    for (int i = 0; i < n; i++)
    {
        res += char(x % 10 + '0');
        x /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

void progress()
{
    SDL_Delay(100);

    board.Unite(curPiece);
    linesCleared = board.ClearLines();
    lines += linesCleared;
    score += points[linesCleared] * (level + 1);
    if (level == startLevel)
    {
        if (lines >= linesCap)
            level++;
    }
    else
    {
        if (lines >= linesCap + (level - startLevel) * 10)
            level++;
    }

    curPiece = nextPiece;
    curPiece.Move(-9, -4);

    curRNG = nextRNG;
    nextRNG = roll(curRNG);
    nextPiece.Init(nextRNG, 0, 12, 3);
    if (curRNG == 0)
        droughtCount = 0;
    else
        droughtCount++;

    moveTime = SDL_GetTicks();
}

void showBoard()
{
    board.DrawBoard(renderer);
    board.DrawTetromino(renderer);
    curPiece.Draw(renderer);
    nextPiece.Draw(renderer);
}

void showBoardGameOver()
{
    board.DrawBoard(renderer);
    board.DrawGameOver(renderer);
}

void showText()
{
    nextText.RenderTexture(renderer, TEXT_POS_X, 80, &textClip4);

    scoreText.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y, &textClip5);
    totalScore.LoadText(toString(score, 7), textColor, font, renderer);
    totalScore.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + TEXT_PIXEL + 1, &textClip7);

    linesText.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + 100, &textClip5);
    totalLines.LoadText(toString(lines, 3), textColor, font, renderer);
    totalLines.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + 100 + TEXT_PIXEL + 1, &textClip3);

    levelText.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + 200, &textClip5);
    totalLevel.LoadText(toString(level, 3), textColor, font, renderer);
    totalLevel.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + 200 + TEXT_PIXEL + 1, &textClip3);
}

void showBlockCount()
{
    board.DrawBlockCount(renderer);
    for (int i = 0; i < 7; i++)
    {
        blockType[i].LoadText(toString(blockCount[i], 3), textColor, font, renderer);
        blockType[i].RenderTexture(renderer, BLOCK_POS_X, BLOCK_POS_Y + 70 * i, &textClip3);
    }
    drought.LoadText(toString(droughtCount, 3), textColor, font, renderer);
    drought.RenderTexture(renderer, BLOCK_POS_X, BLOCK_POS_Y + 70 * 7, &textClip3);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (!init())
    {
        cout << "Failed to initialize\n";
    }
    else
    {
        loadMedia();
        bool quitHome = 0;
        SDL_Event eHome;
        while (!quitHome)
        {
            while (SDL_PollEvent(&eHome) != 0)
            {
                if (eHome.type == SDL_QUIT)
                    quitHome = 1;
                if (eHome.type == SDL_MOUSEBUTTONDOWN)
                {
                    play.HandleEvent(&eHome);
                    howToPlay.HandleEvent(&eHome);
                }
            }

            // load homescreen
            SDL_RenderClear(renderer);
            homeScreen.RenderTexture(renderer, 0, 0, &clipHomeScreen);
            playButton.RenderTexture(renderer, PLAY_BUTTON_X + 10, PLAY_BUTTON_Y + 10, &clipPlayButton);
            howToPlayButton.RenderTexture(renderer, HOW_TO_PLAY_BUTTON_X + 10, HOW_TO_PLAY_BUTTON_Y + 10, &clipHowToPlayButton);
            SDL_RenderPresent(renderer);

            // play screen
            if (play.buttonSprite == 2)
            {
                // playing
                board.Init();
                bool quitGame = 0;
                SDL_Event eGame;
                moveTime = SDL_GetTicks();

                for (int i = 0; i < 7; i++)
                    blockCount[i] = 0;
                startLevel = level = 18;
                score = 0;
                lines = 0;
                linesCap = min(startLevel * 10 + 10, max(100, startLevel * 10 - 50));

                curRNG = rand() % 7;
                nextRNG = roll(curRNG);
                if (curRNG == 0)
                    droughtCount = 0;
                else
                    droughtCount = 1;

                curPiece.Init(curRNG, 0, 12, 3);
                nextPiece.Init(nextRNG, 0, 12, 3);
                curPiece.Move(-9, -4);

                while (!quitGame)
                {
                    while (SDL_PollEvent(&eGame) != 0)
                    {
                        if (eGame.type == SDL_QUIT)
                        {
                            quitGame = 1;
                            quitHome = 1;
                            play.buttonSprite = 0;
                        }
                        if (eGame.type == SDL_KEYDOWN)
                        {
                            switch (eGame.key.keysym.sym)
                            {
                                case SDLK_ESCAPE:
                                {
                                    quitGame = 1;
                                    play.buttonSprite = 0;
                                    break;
                                }

                                case SDLK_DOWN:
                                {
                                    tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                                    tmpPiece.MoveDown();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.MoveDown();
                                    else
                                    {
                                        if (board.GameOver(curPiece))
                                        {
                                            board.Unite(curPiece);
                                            quitGame = 1;
                                        }
                                        else
                                            progress();
                                    }
                                    break;
                                }

                                case SDLK_LEFT:
                                {
                                    tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                                    tmpPiece.MoveLeft();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.MoveLeft();
                                    break;
                                }

                                case SDLK_RIGHT:
                                {
                                    tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                                    tmpPiece.MoveRight();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.MoveRight();
                                    break;
                                }

                                case SDLK_x:
                                {
                                    tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                                    tmpPiece.RotateCW();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.RotateCW();
                                    break;
                                }

                                case SDLK_z:
                                {
                                    tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                                    tmpPiece.RotateCCW();
                                    if (board.ValidMove(tmpPiece))
                                        curPiece.RotateCCW();
                                    break;
                                }
                            }
                        }
                    }

                    SDL_RenderClear(renderer);
                    showBoard();
                    showText();
                    showBlockCount();
                    SDL_RenderPresent(renderer);

                    if (SDL_GetTicks() > moveTime)
                    {
                        moveTime += FRAME * gravity[min(29, level)];
                        tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                        tmpPiece.MoveDown();
                        if (board.ValidMove(tmpPiece))
                            curPiece.MoveDown();
                        else
                        {
                            if (board.GameOver(curPiece))
                            {
                                board.Unite(curPiece);
                                quitGame = 1;
                            }
                            else
                            {
                                progress();
                            }
                        }
                    }
                }

                // game over
                if (play.buttonSprite == 2)
                {
                    bool returnToMenu = 0;
                    while (!returnToMenu)
                    {
                        while (SDL_PollEvent(&eGame) != 0)
                        {
                            if (eGame.type == SDL_QUIT)
                            {
                                quitGame = 1;
                                quitHome = 1;
                                returnToMenu = 1;
                                play.buttonSprite = 0;
                            }

                            if (eGame.type == SDL_KEYDOWN)
                            {
                                if (eGame.key.keysym.sym == SDLK_ESCAPE)
                                {
                                    quitGame = 1;
                                    returnToMenu = 1;
                                    play.buttonSprite = 0;
                                    board.~Board();
                                }
                            }
                        }

                        SDL_RenderClear(renderer);
                        showBoardGameOver();
                        showText();
                        showBlockCount();
                        SDL_RenderPresent(renderer);
                    }
                }
            }

            // how to play screen
            if (howToPlay.buttonSprite == 2)
            {
                bool quitHTP = 0;
                SDL_Event eHTP;
                while (!quitHTP)
                {
                    while (SDL_PollEvent(&eHTP) != 0)
                    {
                        if (eHTP.type == SDL_KEYDOWN)
                        {
                            if (eHTP.key.keysym.sym == SDLK_ESCAPE)
                                quitHTP = 1, howToPlay.buttonSprite = 0;
                        }
                        if (eHTP.type == SDL_QUIT)
                            quitHTP = 1, quitHome = 1;
                    }

                    SDL_RenderClear(renderer);
                    homeScreen.RenderTexture(renderer, 0, 0, &clipHomeScreen);
                    settings.RenderTexture(renderer, WIDTH / 4, HEIGHT / 4, &clipSettings);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }
    close();
    return 0;
}
