#ifndef BOARD_H
#define BOARD_H

#include <SDL/SDL.h>
#include <string>

#include "Defines.h"
#include "Pipe.h"
#include "Text.h"

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
        Board (SDL_Surface *s, SDL_Rect *c, SDL_Surface *pipe1, SDL_Surface *pipe2);

        /*! Input a mouse click */
        void mouseClick (int x, int y);

        /*! Get slot root position based on his line and column */
        SDL_Rect getSlotScreenPosition (int line, int column);

        /*! Updates the board data */
        void Update ();

        /*! Draw board and pipes on screen */
        void Draw ();

        /*! Returns if the game finished. */
        bool isGameOver();

        void startGame();
        void stopGame();

        Text* getGameOverText ();

        void setLevel (eLevel level);
    protected:
    private:
        SDL_Surface *screen, *pipes_sprite1, *pipes_sprite2;
        SDL_Rect *coordinates;
        Pipe *slots[BOARD_LINES][BOARD_COLUMNS];
        Pipe *pool[POOL_SIZE];

        // the current pipe flowing
        int current_pipe_line, current_pipe_column;

        // Flags if the game finished
        bool game_over, game_over_success;

        // the time the game started
        int starting_time;

        // game score
        int score, score_font_size, score_timer;

        // the starting timer
        int timer, last_ticks;

        // flags if the flow has started
        bool flow_started, cronometer_started;

        eLevel m_level;

        static const int x_offset, y_offset;
        static const int slotSize;
        static const int lines, columns;

        Text *cronometer_text, *score_label_text, *score_value_text, *game_over_text;

        void drawCronometer ();
        void drawScore ();
        void drawText (const char *text, SDL_Color color, int x, int y, SDL_Surface *screen);

        void rotatePool (void);

        void updateCronometer();
        void updateScore();
        void updatePipes (eLevel level);
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

        /*
            Successful game over logic.
        */
        void successfulGameOver();

        int countMiddleRowBlocks();
        void blockPosition(int column, int line);
};

#endif // BOARD_H
