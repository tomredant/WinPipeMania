#ifdef __cplusplus
    #include <cstdlib>
    #include <ctime>
#else
    #include <stdlib.h>
    #include <time.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Board.h"
#include "Pipe.h"
#include "Log.h"

#define FRAMES_PER_SECOND 25

const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main ( int argc, char** argv )
{
    /* seed pseudo random numbers generator */
    srand(time(NULL));

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // initialize TTF library
    if ( TTF_Init() < 0 ) {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s \n", TTF_GetError());
        return EXIT_FAILURE;
    }

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1024, 768, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // load an image
    SDL_Surface* background = IMG_Load("background.png");
    if (!background)
    {
        printf("Unable to load background: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface* pipes_sprite = IMG_Load("pipes.png");
    if (!pipes_sprite)
    {
        printf("Unable to load pipesSprite: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface* pipes_sprite_2 = IMG_Load("pipes2.png");
    if (!pipes_sprite_2)
    {
        printf("Unable to load pipesSprite2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    TTF_Font *font = TTF_OpenFont(FONT_PATH, 20);
    if (!font) {
        printf("Unable to load font: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - background->w) / 2;
    dstrect.y = (screen->h - background->h) / 2;

    LOG(logINFO) << "Game started !";

    Board board = Board(screen, &dstrect, background, pipes_sprite, pipes_sprite_2, font);

    // program main loop
    bool done = false;
    unsigned int ticks_now, next_game_tick = SDL_GetTicks();
    while (!done)
    {
        board.Update();

        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }

            case SDL_MOUSEBUTTONDOWN:
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    board.mouseClick(x, y);
                    break;
                }
            }

            // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        board.Draw();
        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);

        // sleep until next frame
        next_game_tick += SKIP_TICKS;
        ticks_now = SDL_GetTicks();
        SDL_Delay(( next_game_tick > ticks_now ) ? next_game_tick - ticks_now : 0);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(background);
    SDL_FreeSurface(pipes_sprite);
    SDL_FreeSurface(pipes_sprite_2);
    TTF_CloseFont(font);

    // all is well ;)
    printf("Exited cleanly\n");
    return EXIT_SUCCESS;
}
