#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Board.h"

#define STATE_IN_PROGRESS 1
#define STATE_GAME_OVER 2

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
        Controller (SDL_Surface *s, SDL_Rect *c, SDL_Surface *back, SDL_Surface *pipe1, SDL_Surface *pipe2, TTF_Font *font);

        /*! Input a mouse click */
        void mouseClick (int x, int y);

        /*! Updates the game data. */
        void Update ();

        /*! Draw elements. */
        void Draw ();
    protected:
    private:
        SDL_Surface *screen, *background, *pipes_sprite1, *pipes_sprite2;
        SDL_Rect *coordinates;
        TTF_Font *font;

        Board *board;
        int game_state;

        void startGame();
};

#endif // BOARD_H
