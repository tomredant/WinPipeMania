#include <iomanip>
#include <string>
#include "Board.h"
#include "Pipe.h"
#include "Log.h"
#include <QObject>
using namespace std;

const int Board::x_offset = 227;
const int Board::y_offset = 35;
const int Board::slotSize = 48;
const int Board::lines = BOARD_LINES;
const int Board::columns = BOARD_COLUMNS;

Board::Board (SDL_Surface* s, SDL_Rect* c, SDL_Surface* pipe1, SDL_Surface* pipe2)
{
    screen = s;
    coordinates = c;
    pipes_sprite1 = pipe1;
    pipes_sprite2 = pipe2;
    timer = INITIAL_TIMER;
    last_ticks = 0;

    score_font_size = SCORE_FONT_SIZE;

    cronometer_text = new Text(screen, CRON_OFFSET_X, CRON_OFFSET_Y, 20);
    score_label_text = new Text(screen, SCORE_LABEL_OFFSET_X, SCORE_LABEL_OFFSET_Y, 20);
    score_value_text = new Text(screen, SCORE_OFFSET_X, SCORE_OFFSET_Y, score_font_size);
    game_over_text = new Text(screen, GAME_OVER_OFFSET_X, GAME_OVER_OFFSET_Y, 30);
    play_again = new Text(screen, PLAY_AGAIN_OFFSET_X, PLAY_AGAIN_OFFSET_Y, 20);

    // Game board positions
    for (int line = 0; line < lines; line++) {
        for (int column = 0; column < columns; column++) {
            mySlots[line][column] = NULL;
        }
    }

    // blocked positions
    for(int i = 0; i < BLOCKED_POSITIONS; i++) {
        int column, line;

        do {
            column = rand() % BOARD_COLUMNS;
            line   = rand() % BOARD_LINES;
        } while(mySlots[line][column]);

        blockPosition(column, line);
    }

    // make sure the middle line has at least 2 blocks
    while(countMiddleRowBlocks() < 2) {
        blockPosition(rand() % BOARD_COLUMNS, INITIAL_LINE);
    }

    // Pool
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
        Pipe **pipe = &mySlots[line][column];

        if (*pipe) {
            if ((*pipe)->isBlocked())
                return;

            delete *pipe;

            // loses points for replacing pipe
            addScore(-10);
        }

        // Get top of the pool
        *pipe = pool[0];
        cronometer_started = true;
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
        return mySlots[column][line];
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
    updateCronometer();
    updateScore();
    updatePipes();
    updateStartingFlow();
    updateNextPipe();
}

void Board::updateCronometer() {
    if(cronometer_started) {
        int current_ticks = SDL_GetTicks();

        // decreases every second
        if (current_ticks > last_ticks + 1000) {
            timer -= 1;
            last_ticks = current_ticks;
        }

        if (timer < 0)
            timer = 0;
    }
}

void Board::updateScore() {
    if(score_font_size > SCORE_FONT_SIZE) {
        // initializes the timer
        if(!score_timer) {
            score_timer = SDL_GetTicks();
        }

        int current_time = SDL_GetTicks();

        if(current_time > score_timer + 50) {
          score_font_size -= 3;
          score_timer = current_time;
        }
    }
}

void Board::updatePipes() {
    for (int l = 0; l < lines; l++) {
        for (int c = 0; c < columns; c++) {
            if (mySlots[l][c] != NULL) {
                mySlots[l][c]->Update();
            }
        }
    }
}

void Board::updateStartingFlow() {
    if (flow_started == false && timer == 0) {
        Pipe *pipe = mySlots[INITIAL_COLUMN][INITIAL_LINE];
        if (pipe && pipe->hasFlowEntry(FLOW_LEFT)) {
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
       if (current_pipe_column == FINAL_COLUMN && current_pipe_line == FINAL_LINE && getCurrentPipe()->getFlowTurnPosition() == FLOW_RIGHT && getCurrentPipe()->hasFlowEntry(FLOW_RIGHT)) {
            successfulGameOver();
            return;
        }

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

    if(current_pipe_column == FINAL_COLUMN && current_pipe_line == FINAL_LINE) {
        return FLOW_RIGHT;
    } else if(pipe->hasFlowEntry(FLOW_TOP) && pipe->getFlowStartPosition() != FLOW_TOP) {
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

void Board::drawCronometer ()
{
    std::ostringstream out;
    out << "0:" << std::setfill('0') << std::setw(2) << timer;
    cronometer_text->Draw(out.str().c_str());
}

void Board::drawScore ()
{
    std::ostringstream out;
    out << score;
    score_label_text->Draw(QObject::tr("Score").toStdString().c_str());
    score_value_text->Draw(out.str().c_str(), score_font_size);
}

void Board::drawGameOver() {
    if (game_over_success) {
        game_over_text->Draw(QObject::tr("CONGRATULATIONS!").toStdString().c_str());
    } else {
        game_over_text->Draw(QObject::tr("GAME OVER!").toStdString().c_str());
    }

    play_again->Draw(QObject::tr("PLAY AGAIN ?").toStdString().c_str());
}

void Board::Draw ()
{
    // Draw all board pipes
    for (int l = 0; l < lines; l++) {
        for (int c = 0; c < columns; c++) {
            // if != NULL we have a pipe to draw
            if (mySlots[l][c] != NULL) {
                SDL_Rect pos = getSlotScreenPosition(l, c);

                mySlots[l][c]->Draw(screen, &pos, isPipeConnected(l, c));
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

    if (game_over) {
        drawGameOver();
    }
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
    score_font_size = SCORE_FONT_SIZE + 20;

    if(score < 0)
        score = 0;
}

void Board::gameOver(string reason) {
    LOG(logINFO) << "Game over ! " << reason;
    game_over = true;
}

void Board::successfulGameOver() {
    LOG(logINFO) << "Successful Game over !";
    game_over = true;
    game_over_success = true;
}

bool Board::isGameOver() {
    return game_over;
}

void Board::startGame ()
{
    score = 0;
    game_over = game_over_success = flow_started = cronometer_started = false;
    starting_time = SDL_GetTicks();
}

int Board::countMiddleRowBlocks() {
    int count = 0;

    for(int i = 0; i < columns; i++) {
        if(mySlots[i][INITIAL_LINE]) {
            count++;
        }
    }

    return count;
}

void Board::blockPosition(int column, int line) {
    // never block first and last positions
    if((line == INITIAL_LINE && column == INITIAL_COLUMN) ||
       line == FINAL_LINE && column == FINAL_COLUMN) {
        return;
    }

    Pipe* pipe = new Pipe(pipes_sprite1, pipes_sprite2, false, false, false, false);
    pipe->block();

    mySlots[column][line] = pipe;
}
