#include "Controller.h"
#include "Board.h"
#include "Log.h"

Controller::Controller(SDL_Surface* s, SDL_Rect* c, SDL_Surface* back, SDL_Surface* pipe1, SDL_Surface* pipe2, SDL_Surface *s2)
{
    screen = s;
    coordinates = c;
    background = back;
    pipes_sprite1 = pipe1;
    pipes_sprite2 = pipe2;
    game_state = STATE_SPLASH_SCREEN;
    splashScreen = new Splash(screen, s2);
}

void Controller::mouseClick (int x, int y) {
    switch(game_state) {
    case STATE_IN_PROGRESS:
        board->mouseClick(x, y);
        break;
    }
}

void Controller::Update() {
    switch(game_state) {
    case STATE_SPLASH_SCREEN:
        if (splashScreen->Update())
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
    // background
    SDL_BlitSurface(background, 0, screen, coordinates);

    switch(game_state) {
    case STATE_SPLASH_SCREEN:
        splashScreen->Draw();
        break;
    case STATE_IN_PROGRESS:
        board->Draw();
        break;
    case STATE_GAME_OVER:
        board->Draw();
        break;
    }
}

void Controller::startGame()
{
    board = new Board(screen, coordinates, pipes_sprite1, pipes_sprite2);
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
