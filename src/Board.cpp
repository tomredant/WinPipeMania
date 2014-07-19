#include "Board.h"
#include "Pipe.h"

const int Board::x_offset = 227;
const int Board::y_offset = 35;
const int Board::lines = 14;
const int Board::columns = 14;
const int Board::slotSize = 48;

Board::Board (SDL_Surface* back, SDL_Surface* pipe1, SDL_Surface* pipe2)
{
    background = back;
    pipes_sprite1 = pipe1;
    pipes_sprite2 = pipe2;

    for (int line = 0; line < lines; line++) {
        for (int column = 0; column < columns; column++) {
            slots[line][column] = NULL;
        }
    }
}

void Board::mouseClick (int x, int y)
{
    int x_min = x_offset, x_max = x_min + (lines * slotSize);
    int y_min = y_offset, y_max = y_min + (columns * slotSize);

    // Check limits
    if (x >= x_min && x <= x_max && y >= y_min && y <= y_max) {
        int line = (x - x_min) / slotSize;
        int column = (y - y_min) / slotSize;
        Pipe **pipe = &slots[line][column];

        if (*pipe)
            delete *pipe;

        *pipe = new Pipe(pipes_sprite1, true, true, true, true);
    }
}

SDL_Rect Board::getSlotScreenPosition (int line, int column)
{
    SDL_Rect pos;

    pos.x = (line * slotSize) + x_offset;
    pos.y = (column * slotSize) + y_offset;

    return pos;
}

void Board::Draw (SDL_Surface* screen, SDL_Rect* coordinates)
{
    // Draw background
    SDL_BlitSurface(background, 0, screen, coordinates);

    // Draw all the pipes
    for (int l = 0; l < lines; l++) {
        for (int c = 0; c < columns; c++) {
            // if != NULL we have a pipe to draw
            if (slots[l][c] != NULL) {
                SDL_Rect pos = getSlotScreenPosition(l, c);
                slots[l][c]->Draw(screen, &pos);
            }
        }
    }
}
