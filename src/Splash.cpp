#include <SDL/SDL.h>
#include "Splash.h"

Splash::Splash(SDL_Surface *screen_surface, SDL_Surface *picture)
{
    screen = screen_surface;
    splash = picture;
    stage = 0;
    starting_time = SDL_GetTicks();
    fadeSurface = SDL_CreateRGBSurface(0, screen->w, screen->h, 32, 0, 0, 0, 0);
}

Splash::~Splash()
{
    SDL_FreeSurface(fadeSurface);
}

bool Splash::Update ()
{
    int ticksNow = SDL_GetTicks();
    bool ret = false;
    int alpha = SDL_ALPHA_OPAQUE;

    // Stays the same amount of time in each stage
    if (ticksNow >= starting_time + SPLASH_SCREEN_FADE) {
        stage++;
        starting_time = SDL_GetTicks();
    }

    // Fading in
    if (stage == 0) {
        alpha = 255 - ((ticksNow - starting_time) / (SPLASH_SCREEN_FADE / 255));
    }
    // Static image
    else if (stage == 1) {
        alpha = SDL_ALPHA_TRANSPARENT;
    }
    // Fading out
    else if (stage == 2) {
        alpha = (ticksNow - starting_time) / (SPLASH_SCREEN_FADE / 255);
    }
    // Finished
    else {
        stage = 0;
        ret = true;
    }

    // Adapter
    if (alpha < 0) alpha = 0;
    if (alpha > 255) alpha = 255;

    splashAlpha = alpha;

    return ret;
}

void Splash::Draw ()
{
    SDL_SetAlpha(fadeSurface, SDL_RLEACCEL | SDL_SRCALPHA, splashAlpha);
    SDL_BlitSurface(splash, 0, screen, 0);
    SDL_BlitSurface(fadeSurface, 0, screen, 0);
}
