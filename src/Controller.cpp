#include "Controller.h"
#include "Board.h"
#include "Log.h"

Controller::Controller(SDL_Surface* s, SDL_Rect* c, SDL_Surface* back, SDL_Surface* pipe1, SDL_Surface* pipe2, TTF_Font *f, SDL_Surface *s2)
{
    screen = s;
    coordinates = c;
    background = back;
    pipes_sprite1 = pipe1;
    pipes_sprite2 = pipe2;
    font = f;
    splash = s2;
    starting_time = SDL_GetTicks();
    game_state = STATE_SPLASH_SCREEN;
    fadeSurface = SDL_CreateRGBSurface(0, screen->w, screen->h, 32, 0, 0, 0, 0);
    board = new Board(screen, coordinates, background, pipes_sprite1, pipes_sprite2, font);
}

void Controller::mouseClick (int x, int y) {
    switch(game_state) {
    case STATE_IN_PROGRESS:
        board->mouseClick(x, y);
        break;
    }
}

bool Controller::updateSplash ()
{
    static int stage = 0;
    int ticksNow = SDL_GetTicks();
    bool ret = false;
    int alpha = SDL_ALPHA_OPAQUE;

    // Stays the same amount of time in each stage
    if (ticksNow >= starting_time + SPLASH_SCREEN_FADE) {
        stage++;
        starting_time = SDL_GetTicks();
    }

    // Fading in
    if (stage == 0) {
        alpha = 255 - ((ticksNow - starting_time) / (SPLASH_SCREEN_FADE / 255));
    }
    // Static image
    else if (stage == 1) {
        alpha = SDL_ALPHA_TRANSPARENT;
    }
    // Fading out
    else if (stage == 2) {
        alpha = (ticksNow - starting_time) / (SPLASH_SCREEN_FADE / 255);
    }
    // Finished
    else {
        stage = 0;
        ret = true;
    }

    // Adapter
    if (alpha < 0) alpha = 0;
    if (alpha > 255) alpha = 255;

    splashAlpha = alpha;

    return ret;
}

void Controller::Update() {
    switch(game_state) {
    case STATE_SPLASH_SCREEN:
        if (updateSplash())
            changeState(STATE_IN_PROGRESS);
        break;
    case STATE_IN_PROGRESS:
        if(board->isGameOver()) {
            changeState(STATE_GAME_OVER);
        } else {
            board->Update();
        }
        break;
    }
}

void Controller::Draw() {
    switch(game_state) {
    case STATE_SPLASH_SCREEN:
        drawSplash();
        break;
    case STATE_IN_PROGRESS:
        board->Draw();
        break;
    }
}

void Controller::drawSplash ()
{
    SDL_SetAlpha(fadeSurface, SDL_RLEACCEL | SDL_SRCALPHA, splashAlpha);
    SDL_BlitSurface(splash, 0, screen, 0);
    SDL_BlitSurface(fadeSurface, 0, screen, 0);
}

void Controller::startGame()
{
    board->startGame();
}

void Controller::changeState (gameState new_state)
{
    if (new_state == STATE_IN_PROGRESS && game_state != STATE_IN_PROGRESS) {
        startGame();
    }

    LOG(logINFO) << "Switching state from " << game_state << " to " << new_state;

    game_state = new_state;
}
