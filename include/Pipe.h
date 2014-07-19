#ifndef PIPE_H
#define PIPE_H

#include <SDL.h>

#define WIDTH  48
#define HEIGHT 48

class Pipe
{
    public:
        /*
            Creates a new Pipe.

            SDL_Surface* - the pipe sprite
            SDL_Surface* - the alternative pipe sprite
            bool - pipe connection top
            bool - pipe connection right
            bool - pipe connection down
            bool - pipe connection left
        */
        Pipe(SDL_Surface*, SDL_Surface*, bool, bool, bool, bool);

        /*
            Draws this pipe.

            SDL_Surface* - the surface to draw this into
            SDL_Rect* - the coordinates to draw this into
        */
        void Draw(SDL_Surface*, SDL_Rect*);
    protected:
    private:
      // the pipe sprite image
      SDL_Surface *sprite;

      // the alternative pipe sprite image
      SDL_Surface *alt_sprite;

      // the pipe image position in the sprite
      SDL_Rect sprite_position;

      // which sides are open to connection in this pipe
      bool top, right, down, left;
};

#endif // PIPE_H
