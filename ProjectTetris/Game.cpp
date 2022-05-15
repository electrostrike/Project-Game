#include "Game.hpp"

Game::Game()
{

}

Game::~Game()
{
    Close();
}

bool Game::Init()
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

void Game::Close()
{
    homeScreen.Free();
    playButton.Free();
    settingsButton.Free();
    settingsScreen.Free();

    TTF_CloseFont(font);
    font = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    Mix_FreeMusic(bgm);
    bgm = NULL;
    Mix_FreeChunk(moveTetromino);
    moveTetromino = NULL;
    Mix_FreeChunk(dropTetromino);
    dropTetromino = NULL;
    Mix_FreeChunk(clearNormal);
    clearNormal = NULL;
    Mix_FreeChunk(clearTetris);
    clearTetris = NULL;
    Mix_FreeChunk(levelUp);
    levelUp = NULL;
    Mix_FreeChunk(gameOver);
    gameOver = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

SDL_Renderer* Game::_renderer()
{
    return renderer;
}

string Game::ToString(int x, int n)
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

int Game::Roll(int curRNG)
{
    int nextRNG = rand() % 7;
    if (nextRNG == curRNG)
        nextRNG = rand() % 7;
    return nextRNG;
}

void Game::LoadMedia()
{
    homeScreen.LoadTexture("image/screen_home.png", renderer);
    playButton.LoadTexture("image/button_play.png", renderer);
    settingsButton.LoadTexture("image/button_settings.png", renderer);
    settingsScreen.LoadTexture("image/screen_settings.png", renderer);

    font = TTF_OpenFont("font/PressStart2P-vaV7.ttf", 28);
    if (font == NULL)
    {
        cout << "Failed to load font\n";
        cout << "SDL_ttf error: " << TTF_GetError() << "\n";
    }

    nextText.LoadText("NEXT", textColor, font, renderer);
    scoreText.LoadText("SCORE", textColor, font, renderer);
    levelText.LoadText("LEVEL", textColor, font, renderer);
    linesText.LoadText("LINES", textColor, font, renderer);

    bgm = Mix_LoadMUS("sfx/bgm.mp3");
    if (bgm == NULL)
    {
        cout << "Failed to load music\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
    }
    moveTetromino = Mix_LoadWAV("sfx/tetromino_move.mp3");
    if (moveTetromino == NULL)
    {
        cout << "Failed to load hitsound\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
    }
    dropTetromino = Mix_LoadWAV("sfx/tetromino_drop.mp3");
    if (dropTetromino == NULL)
    {
        cout << "Failed to load hitsound\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
    }
    clearNormal = Mix_LoadWAV("sfx/clear_normal.mp3");
    if (clearNormal == NULL)
    {
        cout << "Failed to load hitsound\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
    }
    clearTetris = Mix_LoadWAV("sfx/clear_tetris.mp3");
    if (clearTetris == NULL)
    {
        cout << "Failed to load hitsound\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
    }
    levelUp = Mix_LoadWAV("sfx/level_up.mp3");
    if (levelUp == NULL)
    {
        cout << "Failed to load hitsound\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
    }
    gameOver = Mix_LoadWAV("sfx/game_over.mp3");
    if (gameOver == NULL)
    {
        cout << "Failed to load hitsound\n";
        cout << "SDL_mixer error: " << Mix_GetError() << "\n";
    }
}

void Game::RenderBoard()
{
    board.DrawBoard(renderer);
    board.DrawTetromino(renderer);
    curPiece.Draw(renderer);
    nextPiece.Draw(renderer);
}

void Game::RenderText()
{
    nextText.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y - 150, &textClip4);

    scoreText.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y, &textClip5);
    scoreNum.LoadText(ToString(score, 7), textColor, font, renderer);
    scoreNum.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + TEXT_PIXEL + 1, &textClip7);

    linesText.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + 100, &textClip5);
    linesNum.LoadText(ToString(lines, 3), textColor, font, renderer);
    linesNum.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + 100 + TEXT_PIXEL + 1, &textClip3);

    levelText.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + 200, &textClip5);
    levelNum.LoadText(ToString(level, 3), textColor, font, renderer);
    levelNum.RenderTexture(renderer, TEXT_POS_X, TEXT_POS_Y + 200 + TEXT_PIXEL + 1, &textClip3);
}

void Game::RenderBlockCount()
{
    board.DrawBlockCount(renderer);
    for (int i = 0; i < 7; i++)
    {
        block[i].LoadText(ToString(blockCount[i], 3), textColor, font, renderer);
        block[i].RenderTexture(renderer, BLOCK_COUNT_X, BLOCK_COUNT_Y + 70 * i, &textClip3);
    }
    drought.LoadText(ToString(droughtCount, 3), textColor, font, renderer);
    drought.RenderTexture(renderer, BLOCK_COUNT_X, BLOCK_COUNT_Y + 70 * 7, &textClip3);
}

void Game::RenderGameOver()
{
    board.DrawBoard(renderer);
    board.DrawGameOver(renderer);
}

void Game::Progress()
{
    SDL_Delay(100);

    board.Unite(curPiece);
    linesCleared = board.ClearLines();
    if (linesCleared > 0)
    {
        if (linesCleared == 4)
        {
            if (playHitsound)
                Mix_PlayChannel(-1, clearTetris, 0);
        }
        else
        {
            if (playHitsound)
                Mix_PlayChannel(-1, clearNormal, 0);
        }
        lines += linesCleared;
        score += points[linesCleared] * (level + 1);
        if (level == startLevel)
        {
            if (lines >= linesCap)
            {
                if (playHitsound)
                    Mix_PlayChannel(-1, levelUp, 0);
                level++;
            }
        }
        else
        {
            if (lines >= linesCap + (level - startLevel) * 10)
            {
                if (playHitsound)
                    Mix_PlayChannel(-1, levelUp, 0);
                level++;
            }
        }
    }

    curPiece = nextPiece;
    curPiece.Move(-9, -4);

    curRNG = nextRNG;
    nextRNG = Roll(curRNG);
    blockCount[curRNG]++;
    nextPiece.Init(nextRNG, 0, 12, 3);
    if (curRNG == 0)
        droughtCount = 0;
    else
        droughtCount++;

    moveTime = SDL_GetTicks();
}

void Game::Run()
{
    if (!Init())
    {
        cout << "Failed to initialize";
        return;
    }

    srand(time(NULL));
    LoadMedia();
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = 1;
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                play.HandleEvent(&e);
                settings.HandleEvent(&e);
            }
        }

        SDL_RenderClear(renderer);
        homeScreen.RenderTexture(renderer, 0, 0, &clipHomeScreen);
        playButton.RenderTexture(renderer, PLAY_BUTTON_X + 10, PLAY_BUTTON_Y + 10, &clipPlayButton);
        settingsButton.RenderTexture(renderer, HOW_TO_PLAY_BUTTON_X + 10, HOW_TO_PLAY_BUTTON_Y + 10, &clipSettingsButton);
        SDL_RenderPresent(renderer);

        if (play.buttonSprite == 2)
            RunGame();
        else if (settings.buttonSprite == 2)
            RunSettings();
    }
}

void Game::RunGame()
{
    board.Init();
    bool quitGame = 0;
    SDL_Event e;
    moveTime = SDL_GetTicks();

    for (int i = 0; i < 7; i++)
        blockCount[i] = 0;
    startLevel = level = 0;
    score = 0;
    lines = 0;
    linesCap = min(startLevel * 10 + 10, max(100, startLevel * 10 - 50));

    curRNG = rand() % 7;
    nextRNG = Roll(curRNG);
    blockCount[curRNG]++;
    if (curRNG == 0)
        droughtCount = 0;
    else
        droughtCount = 1;

    curPiece.Init(curRNG, 0, 12, 3);
    nextPiece.Init(nextRNG, 0, 12, 3);
    curPiece.Move(-9, -4);

    playMusic = playHitsound = 1;
    Mix_PlayMusic(bgm, -1);

    while (!quitGame)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                Mix_HaltMusic();
                quitGame = 1;
                quit = 1;
                play.buttonSprite = 0;
                break;
            }
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        Mix_HaltMusic();
                        quitGame = 1;
                        play.buttonSprite = 0;
                        break;
                    }

                    case SDLK_m:
                    {
                        if (playMusic)
                        {
                            playMusic = 0;
                            Mix_HaltMusic();
                        }
                        else
                        {
                            playMusic = 1;
                            Mix_PlayMusic(bgm, -1);
                        }
                    }

                    case SDLK_n:
                    {
                        if (playHitsound)
                            playHitsound = 0;
                        else
                            playHitsound = 1;
                    }

                    case SDLK_DOWN:
                    {
                        tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                        tmpPiece.MoveDown();
                        if (board.ValidMove(tmpPiece))
                        {
                            if (playHitsound)
                                Mix_PlayChannel(-1, moveTetromino, 0);
                            curPiece.MoveDown();
                        }
                        else
                        {
                            if (board.GameOver(curPiece))
                            {
                                if (playHitsound)
                                    Mix_PlayChannel(-1, gameOver, 0);
                                board.Unite(curPiece);
                                quitGame = 1;
                            }
                            else
                            {
                                if (playHitsound)
                                    Mix_PlayChannel(-1, dropTetromino, 0);
                                Progress();
                            }
                        }
                        break;
                    }

                    case SDLK_SPACE:
                    {
                        tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                        while (1)
                        {
                            tmpPiece.MoveDown();
                            if (board.ValidMove(tmpPiece))
                                curPiece.MoveDown();
                            else
                                break;
                        }
                        if (board.GameOver(curPiece))
                        {
                            if (playHitsound)
                                Mix_PlayChannel(-1, gameOver, 0);
                            board.Unite(curPiece);
                            quitGame = 1;
                        }
                        else
                        {
                            Progress();
                            if (playHitsound)
                                Mix_PlayChannel(-1, dropTetromino, 0);
                        }
                        break;
                    }

                    case SDLK_LEFT:
                    {
                        tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                        tmpPiece.MoveLeft();
                        if (board.ValidMove(tmpPiece))
                        {
                            if (playHitsound)
                                Mix_PlayChannel(-1, moveTetromino, 0);
                            curPiece.MoveLeft();
                        }
                        break;
                    }

                    case SDLK_RIGHT:
                    {
                        tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                        tmpPiece.MoveRight();
                        if (board.ValidMove(tmpPiece))
                        {
                            if (playHitsound)
                                Mix_PlayChannel(-1, moveTetromino, 0);
                            curPiece.MoveRight();
                        }
                        break;
                    }

                    case SDLK_x:
                    {
                        tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                        tmpPiece.RotateCW();
                        if (board.ValidMove(tmpPiece))
                        {
                            if (playHitsound)
                                Mix_PlayChannel(-1, moveTetromino, 0);
                            curPiece.RotateCW();
                        }
                        break;
                    }

                    case SDLK_z:
                    {
                        tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
                        tmpPiece.RotateCCW();
                        if (board.ValidMove(tmpPiece))
                        {
                            if (playHitsound)
                                Mix_PlayChannel(-1, moveTetromino, 0);
                            curPiece.RotateCCW();
                        }
                        break;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        RenderBoard();
        RenderText();
        RenderBlockCount();
        SDL_RenderPresent(renderer);

        if (SDL_GetTicks() > moveTime)
        {
            moveTime += FRAME * gravity[min(29, level)];
            tmpPiece.Init(curPiece.block, curPiece.rotation, curPiece.x, curPiece.y);
            tmpPiece.MoveDown();
            if (board.ValidMove(tmpPiece))
            {
                //Mix_PlayChannel(-1, moveTetromino, 0);
                curPiece.MoveDown();
            }
            else
            {
                if (board.GameOver(curPiece))
                {
                    if (playHitsound)
                        Mix_PlayChannel(-1, gameOver, 0);
                    board.Unite(curPiece);
                    quitGame = 1;
                }
                else
                {
                    if (playHitsound)
                        Mix_PlayChannel(-1, dropTetromino, 0);
                    Progress();
                }
            }
        }
    }

    // game over
    if (play.buttonSprite == 2)
    {
        Mix_HaltMusic();
        bool returnToMenu = 0;
        while (!returnToMenu)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quitGame = 1;
                    quit = 1;
                    returnToMenu = 1;
                    play.buttonSprite = 0;
                }

                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quitGame = 1;
                        returnToMenu = 1;
                        play.buttonSprite = 0;
                    }
                }
            }

            SDL_RenderClear(renderer);
            RenderGameOver();
            RenderText();
            RenderBlockCount();
            SDL_RenderPresent(renderer);
        }
    }
}

void Game::RunSettings()
{
    bool quitSettings = 0;
    SDL_Event e;
    while (!quitSettings)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quitSettings = 1;
                    settings.buttonSprite = 0;
                }
            }
            if (e.type == SDL_QUIT)
            {
                quitSettings = 1;
                quit = 1;
                settings.buttonSprite = 0;
            }
        }

        SDL_RenderClear(renderer);
        homeScreen.RenderTexture(renderer, 0, 0, &clipHomeScreen);
        settingsScreen.RenderTexture(renderer, HOW_TO_PLAY_X + 10, HOW_TO_PLAY_Y, &clipSettingsScreen);
        SDL_RenderPresent(renderer);
    }
}
