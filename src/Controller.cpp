#include "Controller.h"
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
    // Create start menu
    startMenu = new Menu();
    startMenu->addButton(new Button("START GAME", new Text(screen, START_MENU_OFFSET_X, START_MENU_OFFSET_Y, MENU_SIZE), MENU_START_GAME, MENU_SIZE, MENU_HOVER_SIZE));
    startMenu->addButton(new Button("EXIT", new Text(screen, EXIT_MENU_OFFSET_X, EXIT_MENU_OFFSET_Y, MENU_SIZE), MENU_EXIT, MENU_SIZE, MENU_HOVER_SIZE));

    // Create end Menu
    endMenu = new Menu();
    endMenu->addButton(new Button("YES", new Text(screen, PLAY_AGAIN_YES_OFFSET_X, PLAY_AGAIN_YES_OFFSET_Y, MENU_SIZE), MENU_PLAY_AGAIN_YES, MENU_SIZE, MENU_HOVER_SIZE));
    endMenu->addButton(new Button("NO", new Text(screen, PLAY_AGAIN_NO_OFFSET_X, PLAY_AGAIN_NO_OFFSET_Y, MENU_SIZE), MENU_PLAY_AGAIN_NO, MENU_SIZE, MENU_HOVER_SIZE));
}

void Controller::mouseClick (int x, int y) {
    switch(game_state) {
    case STATE_MENU:
        switch(startMenu->mouseClick(x, y)) {
        case MENU_START_GAME:
            changeState(STATE_IN_PROGRESS);
            break;
        case MENU_EXIT:
            exit(0);
            break;
        }
        break;
    case STATE_IN_PROGRESS:
        board->mouseClick(x, y);
        break;
    case STATE_GAME_OVER:
        switch(endMenu->mouseClick(x, y)) {
        case MENU_PLAY_AGAIN_YES:
            changeState(STATE_IN_PROGRESS);
            break;
        case MENU_PLAY_AGAIN_NO:
            exit(0);
            break;
        }
        break;
    }
}

void Controller::Update() {
    switch(game_state) {
    case STATE_SPLASH_SCREEN:
        if (splashScreen->Update())
            changeState(STATE_MENU);
        break;
    case STATE_IN_PROGRESS:
        if(board->isGameOver()) {
            changeState(STATE_GAME_OVER);
        } else {
            board->Update();
        }
    case STATE_GAME_OVER:
        board->Update();
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
    case STATE_MENU:
        startMenu->Draw();
        break;
    case STATE_IN_PROGRESS:
        board->Draw();
        break;
    case STATE_GAME_OVER:
        board->Draw();
        endMenu->Draw();
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
