#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Pipe.h>

int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1024, 768, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* background = IMG_Load("background.png");
    if (!background)
    {
        printf("Unable to load background: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* pipes_sprite = IMG_Load("pipes.png");
    if (!pipes_sprite)
    {
        printf("Unable to load pipesSprite: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* pipes_sprite_2 = IMG_Load("pipes2.png");
    if (!pipes_sprite_2)
    {
        printf("Unable to load pipesSprite2: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - background->w) / 2;
    dstrect.y = (screen->h - background->h) / 2;

    // the test pipe
    SDL_Rect pipe_position;
    pipe_position.w = 48;
    pipe_position.h = 48;
    pipe_position.x = 0;
    pipe_position.y = 0;

    Pipe pipe = Pipe(pipes_sprite, &pipe_position, true, true, true, true);

    SDL_Rect mouse_position;

    // program main loop
    bool done = false;
    while (!done)
    {
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

                    mouse_position.x = x;
                    mouse_position.y = y;

                    break;
                }
            }

            // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        SDL_BlitSurface(background, 0, screen, &dstrect);
        pipe.Draw(screen, &mouse_position);
        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(background);
    SDL_FreeSurface(pipes_sprite);
    SDL_FreeSurface(pipes_sprite_2);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
