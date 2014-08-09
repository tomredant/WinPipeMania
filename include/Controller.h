#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Board.h"

#define SPLASH_SCREEN_FADE 1000

enum gameState {
    STATE_SPLASH_SCREEN,
    STATE_MENU,
    STATE_IN_PROGRESS,
    STATE_GAME_OVER,
};

class Controller
{
    public:
        /**
            s Screen surface
            c Screen coordinates to draw into
            back Backgound image
            pipe1 Pipes PNG 1
            pipe2 Pipes PNG 2
        */
        Controller (SDL_Surface *s, SDL_Rect *c, SDL_Surface *back, SDL_Surface *pipe1, SDL_Surface *pipe2, TTF_Font *font, SDL_Surface *splash);

        /*! Input a mouse click */
        void mouseClick (int x, int y);

        /*! Updates the game data. */
        void Update ();

        /*! Draw elements. */
        void Draw ();
    protected:
    private:
        SDL_Surface *screen, *background, *pipes_sprite1, *pipes_sprite2, *fadeSurface, *splash;
        SDL_Rect *coordinates;
        TTF_Font *font;

        Board *board;
        int game_state;
        int starting_time;
        int splashAlpha;

        void startGame();
        void changeState (gameState new_state);
        void drawSplash ();
        bool updateSplash();
};

#endif // BOARD_H
