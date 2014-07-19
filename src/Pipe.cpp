#include "Pipe.h"

Pipe::Pipe(SDL_Surface *sprite_param, SDL_Rect *sprite_position_param, bool left_param, bool right_param, bool top_param, bool down_param)
{
    sprite = sprite_param;
    sprite_position = sprite_position_param;

    left = left_param;
    right = right_param;
    top = top_param;
    down = down_param;
}
