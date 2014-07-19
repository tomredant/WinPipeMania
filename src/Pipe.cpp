#include "Pipe.h"

Pipe::Pipe(SDL_Surface *sprite_param, bool left_param, bool right_param, bool top_param, bool down_param)
{
    sprite = sprite_param;

    left = left_param;
    right = right_param;
    top = top_param;
    down = down_param;

    // TODO - Use params to set sprite_position
    sprite_position.w = sprite_position.h = 48;
    sprite_position.x = sprite_position.y = 0;
}

void Pipe::Draw (SDL_Surface* surface, SDL_Rect *position) {
    SDL_BlitSurface(sprite, &sprite_position, surface, position);
}
