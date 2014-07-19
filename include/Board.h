#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include "Pipe.h"

class Board
{
    public:
        Board(SDL_Surface*, SDL_Surface*, SDL_Surface*);
        void mouseClick(int x, int y);
        SDL_Rect getSlotScreenPosition(int line, int column);
        void Draw (SDL_Surface* screen, SDL_Rect* coordinates);
    protected:
    private:
        SDL_Surface *background, *pipes_sprite1, *pipes_sprite2;
        Pipe *slots[14][14];
};

#endif // BOARD_H
