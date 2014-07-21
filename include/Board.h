#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include "Pipe.h"

#define BOARD_LINES 14
#define BOARD_COLUMNS 14

#define POOL_SIZE 5

#define POOL_OFFSET_X 944
#define POOL_OFFSET_Y 38
#define POOL_SPACING 61
#define POOL_TOP_x 944
#define POOL_TOP_Y 312

class Board
{
    public:
        /**
            s Screen surface
            c Screen coordinates to draw into
            back Backgound image
            pipe1 Pipes PNG 1
            pipe2 Pipes PNG 2
        */
        Board (SDL_Surface *s, SDL_Rect *c, SDL_Surface *back, SDL_Surface *pipe1, SDL_Surface *pipe2);

        /*! Input a mouse click */
        void mouseClick (int x, int y);

        /*! Get slot root position based on his line and column */
        SDL_Rect getSlotScreenPosition (int line, int column);

        /*! Updates the board data */
        void Update ();

        /*! Draw board and pipes on screen */
        void Draw ();
    protected:
    private:
        void rotatePool (void);
        SDL_Surface *screen, *background, *pipes_sprite1, *pipes_sprite2;
        SDL_Rect *coordinates;
        Pipe *slots[BOARD_LINES][BOARD_COLUMNS];
        Pipe *pool[POOL_SIZE];

        // the time the game started
        int starting_time;

        static const int x_offset, y_offset;
        static const int slotSize;
        static const int lines, columns;
};

#endif // BOARD_H
