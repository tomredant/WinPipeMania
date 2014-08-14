#include "Controller.h"
#include "Board.h"
#include "Log.h"

Controller::Controller(SDL_Surface* s, SDL_Rect* c, SDL_Surface* back, SDL_Surface* pipe1, SDL_Surface* pipe2, TTF_Font *f)
{
    screen = s;
    coordinates = c;
    background = back;
    pipes_sprite1 = pipe1;
    pipes_sprite2 = pipe2;
    font = f;

    startGame();
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
    case STATE_IN_PROGRESS:
        if(board->isGameOver()) {
            game_state = STATE_GAME_OVER;
        } else {
            board->Update();
        }
        break;
    }
}

void Controller::Draw() {
    board->Draw();
}

void Controller::startGame() {
    board = new Board(screen, coordinates, background, pipes_sprite1, pipes_sprite2, font);
    game_state = STATE_IN_PROGRESS;
}
