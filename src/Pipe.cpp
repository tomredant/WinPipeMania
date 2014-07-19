#include "Pipe.h"

Pipe::Pipe(SDL_Surface *sprite_param, SDL_Surface *alt_sprite_param, bool top_param, bool right_param, bool down_param, bool left_param)
{
    sprite = sprite_param;
    alt_sprite = alt_sprite_param;


    top = top_param;
    right = right_param;
    down = down_param;
    left = left_param;

    sprite_position.w = WIDTH;
    sprite_position.h = HEIGHT;

    // Sets up the sprites position based on the pipe openings
    if(top == true && right == true && down == true && left == true) {
        sprite_position.x = 0;
        sprite_position.y = 0;
    } else if(top == true && right == true && down == true) {
        sprite_position.x = WIDTH * 4;
        sprite_position.y = 0;
    } else if(top == true && right == true && left == true) {
        sprite_position.x = WIDTH * 3;
        sprite_position.y = 0;
    } else if(top == true && down == true && left == true) {
        sprite_position.x = WIDTH * 2;
        sprite_position.y = 0;
    } else if(right == true && down == true && left == true) {
        sprite_position.x = WIDTH;
        sprite_position.y = 0;
    } else if(top == true && right == true) {
        sprite_position.x = WIDTH;
        sprite_position.y = HEIGHT;
    } else if(top == true && down == true) {
        sprite_position.x = WIDTH * 3;
        sprite_position.y = HEIGHT;
    } else if(top == true && left == true) {
        sprite_position.x = WIDTH * 2;
        sprite_position.y = HEIGHT;
    } else if(right == true && down == true) {
        sprite_position.x = WIDTH * 5;
        sprite_position.y = 0;
    } else if(right == true && left == true) {
        sprite_position.x = WIDTH * 4;
        sprite_position.y = HEIGHT;
    } else if(down == true && left == true) {
        sprite_position.x = 0;
        sprite_position.y = HEIGHT;
    } else if(top == true) {
        sprite_position.x = WIDTH * 2;
        sprite_position.y = HEIGHT * 2;
    } else if(right == true) {
        sprite_position.x = WIDTH * 5;
        sprite_position.y = HEIGHT;
    } else if(down == true) {
        sprite_position.x = WIDTH;
        sprite_position.y = HEIGHT * 2;
    } else if(left == true) {
        sprite_position.x = 0;
        sprite_position.y = HEIGHT * 2;
    }
}

void Pipe::Draw(SDL_Surface* surface, SDL_Rect* position) {
    SDL_BlitSurface(sprite, &sprite_position, surface, position);
}
