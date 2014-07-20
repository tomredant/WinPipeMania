#include "Pipe.h"

Pipe::Pipe(SDL_Surface *sprite_param, SDL_Surface *alt_sprite_param, bool top_param, bool right_param, bool down_param, bool left_param)
{
    init(sprite_param, alt_sprite_param, top_param, right_param, down_param, left_param);
}

Pipe::Pipe(SDL_Surface *sprite_param, SDL_Surface *alt_sprite_param)
{
    bool t = rand() & 0x1;
    bool r = rand() & 0x1;
    bool d = rand() & 0x1;
    bool l = rand() & 0x1;
    init(sprite_param, alt_sprite_param, t, r, d, l);
}

void Pipe::init(SDL_Surface *sprite_param, SDL_Surface *alt_sprite_param, bool top_param, bool right_param, bool down_param, bool left_param)
{
    sprite = sprite_param;
    alt_sprite = alt_sprite_param;


    top = top_param;
    right = right_param;
    down = down_param;
    left = left_param;

    sprite_position.w = sprite_position.h = SIZE;

    flow = false;
    flowed_pixels = time = 0;

    // Sets up the sprites position based on the pipe openings
    if(top == true && right == true && down == true && left == true) {
        sprite_position.x = 0;
        sprite_position.y = 0;
    } else if(top == true && right == true && down == true) {
        sprite_position.x = SIZE * 4;
        sprite_position.y = 0;
    } else if(top == true && right == true && left == true) {
        sprite_position.x = SIZE * 3;
        sprite_position.y = 0;
    } else if(top == true && down == true && left == true) {
        sprite_position.x = SIZE * 2;
        sprite_position.y = 0;
    } else if(right == true && down == true && left == true) {
        sprite_position.x = SIZE;
        sprite_position.y = 0;
    } else if(top == true && right == true) {
        sprite_position.x = SIZE;
        sprite_position.y = SIZE;
    } else if(top == true && down == true) {
        sprite_position.x = SIZE * 3;
        sprite_position.y = SIZE;
    } else if(top == true && left == true) {
        sprite_position.x = SIZE * 2;
        sprite_position.y = SIZE;
    } else if(right == true && down == true) {
        sprite_position.x = SIZE * 5;
        sprite_position.y = 0;
    } else if(right == true && left == true) {
        sprite_position.x = SIZE * 4;
        sprite_position.y = SIZE;
    } else if(down == true && left == true) {
        sprite_position.x = 0;
        sprite_position.y = SIZE;
    } else if(top == true) {
        sprite_position.x = SIZE * 2;
        sprite_position.y = SIZE * 2;
    } else if(right == true) {
        sprite_position.x = SIZE * 5;
        sprite_position.y = SIZE;
    } else if(down == true) {
        sprite_position.x = SIZE;
        sprite_position.y = SIZE * 2;
    } else if(left == true) {
        sprite_position.x = 0;
        sprite_position.y = SIZE * 2;
    } else {
        sprite_position.x = SIZE * 5;
        sprite_position.y = SIZE * 2;
    }
}

void Pipe::Draw(SDL_Surface* surface, SDL_Rect* position) {
    SDL_Rect rect;
    rect.x = position->x;
    rect.y = position->y + 23;
    rect.w = flowed_pixels;
    rect.h = 2;

    // draws the pipe
    SDL_BlitSurface(alt_sprite, &sprite_position, surface, position);

    // draws the pipe flow
    SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 255, 0, 0));
}

void Pipe::Update() {
  if(flowed_pixels < SIZE && flow == true) {
    unsigned int current_time = SDL_GetTicks();

    if(current_time > time + FLOW_SPEED) {
      flowed_pixels += 1;
      time = current_time;
    }
  }
}

void Pipe::StartFlow() {
    if(flow == false) {
        flow = true;
        time = SDL_GetTicks();
    }
}
