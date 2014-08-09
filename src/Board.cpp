#include <iomanip>
#include <string>
#include "Board.h"
#include "Pipe.h"
#include "Log.h"

using namespace std;

const int Board::x_offset = 227;
const int Board::y_offset = 35;
const int Board::slotSize = 48;
const int Board::lines = BOARD_LINES;
const int Board::columns = BOARD_COLUMNS;

Board::Board (SDL_Surface* s, SDL_Rect* c, SDL_Surface* back, SDL_Surface* pipe1, SDL_Surface* pipe2, TTF_Font *f)
{
    screen = s;
    coordinates = c;
    background = back;
    pipes_sprite1 = pipe1;
    pipes_sprite2 = pipe2;
    font = f;
    starting_time = SDL_GetTicks();
    score = 0;
    flow_started = false;
    game_over = false;

    for (int line = 0; line < lines; line++) {
        for (int column = 0; column < columns; column++) {
            slots[line][column] = NULL;
        }
    }

    // blocked positions
    for(int i = 0; i < BLOCKED_POSITIONS; i++) {
        int column, line;

        do {
            column = rand() % BOARD_COLUMNS;
            line   = rand() % BOARD_LINES;
        } while(slots[line][column]);

        Pipe* pipe = new Pipe(pipes_sprite1, pipes_sprite2, false, false, false, false);
        pipe->block();

        slots[line][column] = pipe;
    }


    for (int p = 0; p < POOL_SIZE; p++) {
        pool[p] = new Pipe(pipes_sprite1, pipes_sprite2);
    }

    LOG(logDEBUG) << "Created Board";
}

void Board::mouseClick (int x, int y)
{
    int x_min = x_offset, x_max = x_min + (lines * slotSize);
    int y_min = y_offset, y_max = y_min + (columns * slotSize);

    // Check limits
    if (x >= x_min && x <= x_max && y >= y_min && y <= y_max) {
        int line = (x - x_min) / slotSize;
        int column = (y - y_min) / slotSize;
        Pipe **pipe = &slots[line][column];

        if (*pipe) {
            if ((*pipe)->isBlocked())
                return;

            delete *pipe;

            // loses points for replacing pipe
            addScore(-10);
        }

        // Get top of the pool
        *pipe = pool[0];
        rotatePool();
    }
}

void Board::rotatePool (void)
{
    for (int p = 0; p < POOL_SIZE - 1; p++) {
        pool[p] = pool[p + 1];
    }

    pool[POOL_SIZE - 1] = new Pipe(pipes_sprite1, pipes_sprite2);
}

SDL_Rect Board::getSlotScreenPosition (int line, int column)
{
    SDL_Rect pos;

    pos.x = (line * slotSize) + x_offset;
    pos.y = (column * slotSize) + y_offset;

    return pos;
}

Pipe* Board::getPipe(int column, int line) {
    if(column >= BOARD_COLUMNS || column < 0 ||
       line >= BOARD_LINES || line < 0) {
       return NULL;
    } else {
        return slots[column][line];
    }
}

Pipe* Board::getCurrentPipe() {
    return getPipe(current_pipe_column, current_pipe_line);
}

Pipe* Board::getNextPipe(const int direction, int *column, int *line, int *flow) {
    *column = current_pipe_column;
    *line = current_pipe_line;

    switch(direction) {
        case FLOW_TOP:
            *line -= 1;
            *flow = FLOW_DOWN;
            break;
        case FLOW_RIGHT:
            *column += 1;
            *flow = FLOW_LEFT;
            break;
        case FLOW_DOWN:
            *line += 1;
            *flow = FLOW_TOP;
            break;
        case FLOW_LEFT:
            *column -= 1;
            *flow = FLOW_RIGHT;
            break;
    };

    return getPipe(*column, *line);
}

void Board::Update() {
    updatePipes();
    updateStartingFlow();
    updateNextPipe();
}

void Board::updatePipes() {
    for (int l = 0; l < lines; l++) {
        for (int c = 0; c < columns; c++) {
            if (slots[l][c] != NULL) {
                slots[l][c]->Update();
            }
        }
    }
}

void Board::updateStartingFlow() {
    if (flow_started == false && SDL_GetTicks() - starting_time > INITIAL_DELAY) {
        if (slots[INITIAL_COLUMN][INITIAL_LINE] != NULL) {
            current_pipe_column = INITIAL_COLUMN;
            current_pipe_line = INITIAL_LINE;
            startCurrentPipeFlow(FLOW_LEFT);
            flow_started = true;
        } else {
            gameOver("No starting pipe");
        }
    }
}

void Board::updateNextPipe() {
    if (flow_started == true && getCurrentPipe()->isFlowFinished()) {
        int flow_direction = getCurrentPipe()->getFlowTurnPosition();
        int next_flow;
        int column, line, flow;

        getNextPipe(flow_direction, &column, &line, &flow);
        current_pipe_column = column;
        current_pipe_line = line;
        next_flow = flow;

        // game over if has no next pipe or the next pipe does not have the next_flow entry
        if (getCurrentPipe() == NULL || !getCurrentPipe()->hasFlowEntry(next_flow)) {
            gameOver("No next pipe NULL or next pipe has no flow entry for " + next_flow);
        } else {
            startCurrentPipeFlow(next_flow);
        }
    } else if(flow_started == true && getCurrentPipe()->isFlowHalf()) {
        int next_flow_direction = calculateNextFlowDirection();

        if(next_flow_direction > 0) {
            getCurrentPipe()->setFlowTurnPosition(next_flow_direction);
        } else {
            gameOver("No next flow direction");
        }
    }
}

int Board::calculateNextFlowDirection() {
    if(possibleNextFlowDirection(FLOW_TOP, FLOW_DOWN)) {
        return FLOW_TOP;
    }

    if(possibleNextFlowDirection(FLOW_RIGHT, FLOW_LEFT)) {
        return FLOW_RIGHT;
    }

    if(possibleNextFlowDirection(FLOW_DOWN, FLOW_TOP)) {
        return FLOW_DOWN;
    }

    if(possibleNextFlowDirection(FLOW_LEFT, FLOW_RIGHT)) {
        return FLOW_LEFT;
    }

    // if couldn't find anything, turn to the first possible one
    Pipe* pipe = getCurrentPipe();

    if(pipe->hasFlowEntry(FLOW_TOP) && pipe->getFlowStartPosition() != FLOW_TOP) {
        return FLOW_TOP;
    } else if(pipe->hasFlowEntry(FLOW_RIGHT) && pipe->getFlowStartPosition() != FLOW_RIGHT) {
        return FLOW_RIGHT;
    } else if(pipe->hasFlowEntry(FLOW_DOWN) && pipe->getFlowStartPosition() != FLOW_DOWN) {
        return FLOW_DOWN;
    } else if(pipe->hasFlowEntry(FLOW_LEFT) && pipe->getFlowStartPosition() != FLOW_LEFT) {
        return FLOW_LEFT;
    }

    return 0;
}

bool Board::possibleNextFlowDirection(int outgoing_flow, int incoming_flow) {
    Pipe* pipe = getCurrentPipe();
    Pipe* next_pipe;
    int column, line, flow;

    if (pipe->hasFlowEntry(outgoing_flow) && pipe->getFlowStartPosition() != outgoing_flow) {
        next_pipe = getNextPipe(outgoing_flow, &column, &line, &flow);

        if(next_pipe && next_pipe->hasFlowEntry(incoming_flow)) {
            return true;
        }
    }

    return false;
}

void Board::drawText (const char *text, SDL_Color color, int x, int y, SDL_Surface *screen)
{
    SDL_Rect rect = { x, y, 0, 0 };
    SDL_Surface *TTF_Message = TTF_RenderText_Solid (font, text, color);

    if (TTF_Message) {
        if (SDL_BlitSurface(TTF_Message, NULL, screen, &rect))
            LOG(logERROR) << "Could not write text: " << TTF_GetError() << "";
    }
    else {
        LOG(logERROR) << "Could not write text: " << TTF_GetError() << "";
    }

    SDL_FreeSurface(TTF_Message);
}

void Board::drawCronometer ()
{
    SDL_Color color = { 0xFF }; // red text
    std::ostringstream out;
    int time_left = starting_time - SDL_GetTicks() + INITIAL_DELAY;

    if (time_left < 0)
        time_left = 0;

    out << "0:" << std::setfill('0') << std::setw(2) << time_left / 1000;

    drawText(out.str().c_str(), color, CRON_OFFSET_X, CRON_OFFSET_Y, screen);
}

void Board::drawScore ()
{
    SDL_Color color = { 0xFF }; // red text
    std::ostringstream out;

    out << score;

    drawText("Score", color, SCORE_LABEL_OFFSET_X, SCORE_LABEL_OFFSET_Y, screen);
    drawText(out.str().c_str(), color, SCORE_OFFSET_X, SCORE_OFFSET_Y, screen);
}

void Board::Draw ()
{
    // Draw background
    SDL_BlitSurface(background, 0, screen, coordinates);

    // Draw all board pipes
    for (int l = 0; l < lines; l++) {
        for (int c = 0; c < columns; c++) {
            // if != NULL we have a pipe to draw
            if (slots[l][c] != NULL) {
                SDL_Rect pos = getSlotScreenPosition(l, c);

                slots[l][c]->Draw(screen, &pos, isPipeConnected(l, c));
            }
        }
    }

    // Draw pool pipes
    SDL_Rect pos;
    pos.x = POOL_OFFSET_X;
    pos.y = POOL_OFFSET_Y;

    for (int p = POOL_SIZE - 1; p > 0; p--, pos.y += POOL_SPACING) {
        pool[p]->Draw(screen, &pos, false);
    }

    pos.y = POOL_TOP_Y;
    pool[0]->Draw(screen, &pos, false);

    drawCronometer();
    drawScore();
}

bool Board::isPipeConnected(int col, int line) {
    if(col == INITIAL_COLUMN && line == INITIAL_LINE) {
        return true;
    }

    Pipe* current = getPipe(col, line);
    Pipe* pipe;

    // connects on top?
    pipe = getPipe(col, line - 1);
    if(current->hasFlowEntry(FLOW_TOP) && pipe && pipe->hasFlowEntry(FLOW_DOWN)) {
        return true;
    }

    // connects on right?
    pipe = getPipe(col + 1, line);
    if(current->hasFlowEntry(FLOW_RIGHT) && pipe && pipe->hasFlowEntry(FLOW_LEFT)) {
        return true;
    }

    // connects on down?
    pipe = getPipe(col, line + 1);
    if(current->hasFlowEntry(FLOW_DOWN) && pipe && pipe->hasFlowEntry(FLOW_TOP)) {
        return true;
    }

    // connects on left?
    pipe = getPipe(col - 1, line);
    if(current->hasFlowEntry(FLOW_LEFT) && pipe && pipe->hasFlowEntry(FLOW_RIGHT)) {
        return true;
    }

    return false;
}

void Board::startCurrentPipeFlow(int direction) {
    getCurrentPipe()->StartFlow(direction);
    addScore(100);
}

void Board::addScore(int points) {
    score += points;

    if(score < 0)
        score = 0;
}

void Board::gameOver(string reason) {
    LOG(logINFO) << "Game over ! " << reason;
    game_over = true;
}

bool Board::gameOver() {
    return game_over;
}
