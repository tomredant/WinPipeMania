#ifndef PIPE_H
#define PIPE_H

#include <SDL.h>

class Pipe
{
    public:
        /*
            Creates a new Pipe.

            SDL_Surface* - the pipe sprite
            SDL_Rect* - the pipe image position in the sprite
            bool - pipe connection left
            bool - pipe connection right
            bool - pipe connection up
            bool - pipe connection down
        */
        Pipe(SDL_Surface*, bool, bool, bool, bool);

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

      // the pipe image position in the sprite
      SDL_Rect sprite_position;

      // which sides are open to connection in this pipe
      bool left, right, top, down;
};

#endif // PIPE_H
