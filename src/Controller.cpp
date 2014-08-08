#include "Controller.h"
#include "Board.h"
#include "Log.h"

Controller::Controller(SDL_Surface* s, SDL_Rect* c, SDL_Surface* back, SDL_Surface* pipe1, SDL_Surface* pipe2, TTF_Font *f)
{
    board = new Board(s, c, back, pipe1, pipe2, f);
}

void Controller::mouseClick (int x, int y) {
    board->mouseClick(x, y);
}

void Controller::Update() {
    board->Update();
}

void Controller::Draw() {
    board->Draw();
}
