#ifndef PIPE_H
#define PIPE_H

#include <SDL/SDL.h>

#define PIPE_SIZE 48
#define FLOW_LENGTH 2

// 1 pixel every 125 miliseconds to fill the SIZE in 6 seconds
#define FLOW_SPEED 125

// flow start points
#define FLOW_TOP    1
#define FLOW_RIGHT  2
#define FLOW_DOWN   3
#define FLOW_LEFT   4

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
            bool - is this pipe connected to another pipe?
        */
        void Draw(SDL_Surface*, SDL_Rect*, bool);

        /*
            Updates the pipe draw data.
        */
        void Update();

        /*
            Starts flowing water through this pipe.

            int - the flow start position.
        */
        void StartFlow(int);

        /*! Return false if pipe cannot be changed anymore */
        bool isBlocked (void);

        /*
            Checks if the flow of this pipe has already finished.
        */
        bool isFlowFinished();

        /*
            Checks if this pipe has a flow entry for the given parameter.
        */
        bool hasFlowEntry(int);

        /*
            Gets the flow start position.
        */
        int getFlowStartPosition();

        /*
            Gets the flow turn position.
        */
        int getFlowTurnPosition();

        /*
            Sets the flow turn position for this pipe.
        */
        void setFlowTurnPosition(int);

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

        // toggles water flowing for this pipe
        bool flow;

        // the flow start/turn position
        int flow_start_position, flow_turn_position;

        // the number of pixels the water has already flowed
        int flowed_pixels;

        // time control
        int time;

        // the point in which the pipe is in its half
        static const int pipe_size_middle;

        // the point in which starts the pipe size middle
        static const int pipe_size_middle_start;

        // initializes the pipe
        void init(SDL_Surface*, SDL_Surface*, bool, bool, bool, bool);

        /*
            Builds an SDL_Rect to draw the initial flow.

            unsigned int - the starting flow position.
        */
        SDL_Rect FirstFlowRect(SDL_Rect*, unsigned int);

        /*
            Builds an SDL_Rect to draw the last flow.

            unsigned int - the endflow position.
        */
        SDL_Rect LastFlowRect(SDL_Rect*, unsigned int);
};

#endif // PIPE_H
