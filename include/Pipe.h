#ifndef PIPE_H
#define PIPE_H

#include <SDL.h>

#define SIZE 48

// 1 pixel every 125 miliseconds to fill the SIZE in 6 seconds
#define FLOW_SPEED 125

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

        /*! Creates a randomized Pipe object */
        Pipe(SDL_Surface*, SDL_Surface*);

        /*
            Draws this pipe.

            SDL_Surface* - the surface to draw this into
            SDL_Rect* - the coordinates to draw this into
        */
        void Draw(SDL_Surface*, SDL_Rect*);

        /*
            Updates the pipe draw data.
        */
        void Update();

        /*
            Starts flowing water through this pipe.
        */
        void StartFlow();
    protected:
    private:
      void init(SDL_Surface*, SDL_Surface*, bool, bool, bool, bool);

      // the pipe sprite image
      SDL_Surface *sprite;

      // the alternative pipe sprite image
      SDL_Surface *alt_sprite;

      // the pipe image position in the sprite
      SDL_Rect sprite_position;

      // which sides are open to connection in this pipe
      bool top, right, down, left;

      // toggles water flowing for this pipe
      bool flow;

      // the number of pixels the water has already flowed
      unsigned int flowed_pixels;

      // time control
      unsigned int time;
};

#endif // PIPE_H
