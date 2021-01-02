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
#include "Log.h"
#include "Controller.h"
#include <QFile>
#include <QDir>
#define FRAMES_PER_SECOND 25

const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
#undef main
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
    QFile backgroundPath(":/background.gif");
    QString backgroundPathTemp = QDir::temp().absolutePath() + "/" + backgroundPath.fileName().split("/").last();
    backgroundPath.copy(backgroundPathTemp);
    SDL_Surface* background = IMG_Load(backgroundPathTemp.toUtf8());
    if (!background)
    {
        printf("Unable to load background: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    QFile pipesPath(":/pipes.gif");
    QString pipesPathTemp = QDir::temp().absolutePath() + "/" + pipesPath.fileName().split("/").last();
    pipesPath.copy(pipesPathTemp);
    SDL_Surface* pipes_sprite = IMG_Load(pipesPathTemp.toUtf8());
    if (!pipes_sprite)
    {
        printf("Unable to load pipesSprite: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    QFile pipes2Path(":/pipes2.gif");
    QString pipes2PathTemp = QDir::temp().absolutePath() + "/" + pipes2Path.fileName().split("/").last();
    pipes2Path.copy(pipes2PathTemp);
    SDL_Surface* pipes_sprite_2 = IMG_Load(pipes2PathTemp.toUtf8());
    if (!pipes_sprite_2)
    {
        printf("Unable to load pipesSprite2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    QFile splashPath(":/kct_logo.gif");
    QString splashPathTemp = QDir::temp().absolutePath() + "/" + splashPath.fileName().split("/").last();
    splashPath.copy(splashPathTemp);
    SDL_Surface* splash = IMG_Load(splashPathTemp.toUtf8());
    if (!splash)
    {
        printf("Unable to load kct logo: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - background->w) / 2;
    dstrect.y = (screen->h - background->h) / 2;

    LOG(logINFO) << "Game started !";

    Controller controller = Controller(screen, &dstrect, background, pipes_sprite, pipes_sprite_2, splash);

    // program main loop
    bool done = false;
    unsigned int ticks_now, next_game_tick = SDL_GetTicks();
    while (!done)
    {
        controller.Update();

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
                    if(event.button.button == SDL_BUTTON_LEFT) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        controller.mouseClick(x, y);
                        break;
                    }
                }
            }

            // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        controller.Draw();
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

    // all is well ;)
    printf("Exited cleanly\n");
    return EXIT_SUCCESS;
}
