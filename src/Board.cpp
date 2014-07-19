#include "Board.h"
#include "Pipe.h"

Board::Board (SDL_Surface* back, SDL_Surface* pipe1, SDL_Surface* pipe2)
{
    background = back;
    pipes_sprite1 = pipe1;
    pipes_sprite2 = pipe2;

    for (int line = 0; line < 14; line++) {
        for (int column = 0; column < 14; column++) {
            slots[line][column] = NULL;
        }
    }
}

void Board::mouseClick (int x, int y)
{
    // TODO
    // Determine slot based on mouse click x y
    // board offset = 227, 35
    // Put pipe in slot. Remeber to delete old one before

    int x_min = 227, x_max = x_min + (14 * 48);
    int y_min = 35, y_max = y_min + (14 * 48);

    // Check limits
    if (x >= x_min && x <= x_max && y >= y_min && y <= y_max) {
        int line = (x - x_min) / 48;
        int column = (y - y_min) / 48;
        Pipe **pipe = &slots[line][column];

        if (*pipe)
            delete *pipe;

        *pipe = new Pipe(pipes_sprite1, true, true, true, true);
    }
}

SDL_Rect Board::getSlotScreenPosition (int line, int column)
{
    int x_offset = 227, y_offset = 35;
    SDL_Rect pos;

    pos.x = (line * 48) + x_offset;
    pos.y = (column * 48) + y_offset;

    return pos;
}

void Board::Draw (SDL_Surface* screen, SDL_Rect* coordinates)
{
    // Draw background
    SDL_BlitSurface(background, 0, screen, coordinates);

    // Draw all the pipes
    for (int l = 0; l < 14; l++) {
        for (int c = 0; c < 14; c++) {
            // if != NULL we have a pipe to draw
            if (slots[l][c] != NULL) {
                SDL_Rect pos = getSlotScreenPosition(l, c);
                slots[l][c]->Draw(screen, &pos);
            }
        }
    }
}
