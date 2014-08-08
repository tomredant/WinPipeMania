#ifndef BOARD_H
#define BOARD_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include "Pipe.h"

#define BOARD_LINES 14
#define BOARD_COLUMNS 14

#define POOL_SIZE 5

#define POOL_OFFSET_X 944
#define POOL_OFFSET_Y 38
#define POOL_SPACING 61
#define POOL_TOP_x 944
#define POOL_TOP_Y 312

#define INITIAL_DELAY 10000
#define INITIAL_COLUMN 0
#define INITIAL_LINE   7

#define CRON_OFFSET_X 80
#define CRON_OFFSET_Y 80

#define SCORE_LABEL_OFFSET_X 65
#define SCORE_LABEL_OFFSET_Y 480
#define SCORE_OFFSET_X 65
#define SCORE_OFFSET_Y 500

using namespace std;

class Board
{
    public:
        /**
            s Screen surface
            c Screen coordinates to draw into
            back Backgound image
            pipe1 Pipes PNG 1
            pipe2 Pipes PNG 2
        */
        Board (SDL_Surface *s, SDL_Rect *c, SDL_Surface *back, SDL_Surface *pipe1, SDL_Surface *pipe2, TTF_Font *font);

        /*! Input a mouse click */
        void mouseClick (int x, int y);

        /*! Get slot root position based on his line and column */
        SDL_Rect getSlotScreenPosition (int line, int column);

        /*! Updates the board data */
        void Update ();

        /*! Draw board and pipes on screen */
        void Draw ();
    protected:
    private:
        SDL_Surface *screen, *background, *pipes_sprite1, *pipes_sprite2;
        SDL_Rect *coordinates;
        TTF_Font *font;
        Pipe *slots[BOARD_LINES][BOARD_COLUMNS];
        Pipe *pool[POOL_SIZE];

        // the current pipe flowing
        int current_pipe_line, current_pipe_column;

        // Flags if there is a game in progress
        bool game_in_progress;

        // the time the game started
        int starting_time;

        // game score
        int score;

        // flags if the flow has started
        bool flow_started;

        static const int x_offset, y_offset;
        static const int slotSize;
        static const int lines, columns;

        void drawCronometer ();
        void drawScore ();
        void drawText (const char *text, SDL_Color color, int x, int y, SDL_Surface *screen);

        void rotatePool (void);

        void updatePipes();
        void updateStartingFlow();
        void updateNextPipe();

        /*
            Calculates where the next flow direction should be.
        */
        int calculateNextFlowDirection();

        /*
            Checks if the next Pipe will work with the required entry flow.

            int - the flow exiting the current pipe
            int - the flow incoming the next pipe
        */
        bool possibleNextFlowDirection(int, int);

        /*
            Gets the pipe for the given column/line..
        */
        Pipe* getPipe(int, int);

        /*
            Gets the current pipe.
        */
        Pipe* getCurrentPipe();

        /*
            Gets the next pipe column/line/flow for the given direction.
        */
        Pipe* getNextPipe(const int direction, int *column, int *line, int *flow);

        /*
            Checks if the pipe is connected to another pipe.

            int - the pipe col
            int - the pipe line
        */
        bool isPipeConnected(int, int);

        /*
            Start flowing the current pipe.

            int - the flow starting direction.
        */
        void startCurrentPipeFlow(int);

        /*
            Adds points to the score.

            int - the points to add.
        */
        void addScore(int);

        /*
            Game over logic.
        */
        void gameOver(string);
};

#endif // BOARD_H
