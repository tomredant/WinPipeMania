#include <Pipe.h>
#include <Log.h>

const int Pipe::pipe_size_middle = (PIPE_SIZE / 2);
const int Pipe::pipe_size_middle_start = Pipe::pipe_size_middle - 1;

Pipe::Pipe(SDL_Surface *sprite_param, SDL_Surface *alt_sprite_param, bool top_param, bool right_param, bool down_param, bool left_param)
{
    init(sprite_param, alt_sprite_param, top_param, right_param, down_param, left_param);
}

Pipe::Pipe(SDL_Surface *sprite_param, SDL_Surface *alt_sprite_param)
{
    bool t = rand() & 0x1;
    bool r = rand() & 0x1;
    bool d = rand() & 0x1;
    bool l = rand() & 0x1;

    init(sprite_param, alt_sprite_param, t, r, d, l);
}

void Pipe::init(SDL_Surface *sprite_param, SDL_Surface *alt_sprite_param, bool top_param, bool right_param, bool down_param, bool left_param)
{
    sprite = sprite_param;
    alt_sprite = alt_sprite_param;

    top = top_param;
    right = right_param;
    down = down_param;
    left = left_param;

    sprite_position.w = sprite_position.h = PIPE_SIZE;

    flow = false;
    flowed_pixels = time = 0;

    // Sets up the sprites position based on the pipe openings
    if(top == true && right == true && down == true && left == true) {
        sprite_position.x = 0;
        sprite_position.y = 0;
    } else if(top == true && right == true && down == true) {
        sprite_position.x = PIPE_SIZE * 4;
        sprite_position.y = 0;
    } else if(top == true && right == true && left == true) {
        sprite_position.x = PIPE_SIZE * 3;
        sprite_position.y = 0;
    } else if(top == true && down == true && left == true) {
        sprite_position.x = PIPE_SIZE * 2;
        sprite_position.y = 0;
    } else if(right == true && down == true && left == true) {
        sprite_position.x = PIPE_SIZE;
        sprite_position.y = 0;
    } else if(top == true && right == true) {
        sprite_position.x = PIPE_SIZE;
        sprite_position.y = PIPE_SIZE;
    } else if(top == true && down == true) {
        sprite_position.x = PIPE_SIZE * 3;
        sprite_position.y = PIPE_SIZE;
    } else if(top == true && left == true) {
        sprite_position.x = PIPE_SIZE * 2;
        sprite_position.y = PIPE_SIZE;
    } else if(right == true && down == true) {
        sprite_position.x = PIPE_SIZE * 5;
        sprite_position.y = 0;
    } else if(right == true && left == true) {
        sprite_position.x = PIPE_SIZE * 4;
        sprite_position.y = PIPE_SIZE;
    } else if(down == true && left == true) {
        sprite_position.x = 0;
        sprite_position.y = PIPE_SIZE;
    } else if(top == true) {
        sprite_position.x = PIPE_SIZE * 2;
        sprite_position.y = PIPE_SIZE * 2;
    } else if(right == true) {
        sprite_position.x = PIPE_SIZE * 5;
        sprite_position.y = PIPE_SIZE;
    } else if(down == true) {
        sprite_position.x = PIPE_SIZE;
        sprite_position.y = PIPE_SIZE * 2;
    } else if(left == true) {
        sprite_position.x = 0;
        sprite_position.y = PIPE_SIZE * 2;
    } else {
        sprite_position.x = PIPE_SIZE * 5;
        sprite_position.y = PIPE_SIZE * 2;
    }

    LOG(logDEBUG) << "Created a new Pipe: top " << top << " down " << down << " left " << left << " right " << right;
}

void Pipe::Draw(SDL_Surface* surface, SDL_Rect* position, bool connected) {
    SDL_Surface *s;

    if(connected) {
        s = alt_sprite;
    } else {
        s = sprite;
    }

    // draws the pipe
    SDL_BlitSurface(s, &sprite_position, surface, position);

    unsigned int rgb = SDL_MapRGB(surface->format, 255, 0, 0);


    if (flow) {
        // first half flow
        SDL_Rect rect = FirstFlowRect(position, flow_start_position);
        SDL_FillRect(surface, &rect, rgb);

        // second half flow
        if (flowed_pixels >= PIPE_SIZE / 2) {
            rect = LastFlowRect(position, flow_turn_position);
            SDL_FillRect(surface, &rect, rgb);
        }
    }
}

void Pipe::Update() {
  if(flowed_pixels < PIPE_SIZE && flow == true) {
    int current_time = SDL_GetTicks();

    if(current_time > time + FLOW_SPEED) {
      flowed_pixels += 2;
      time = current_time;
    }
  }
}

bool Pipe::isBlocked (void)
{
    // if it has flow then its blocked
    return flow;
}

bool Pipe::hasFlowEntry(int entry) {
    return (entry == FLOW_TOP && top) ||
           (entry == FLOW_RIGHT && right) ||
           (entry == FLOW_DOWN && down) ||
           (entry == FLOW_LEFT && left);
}

void Pipe::StartFlow(int start_position) {
    if(flow == false) {
        flow = true;
        flow_start_position = start_position;
        flow_turn_position = 0;
        time = SDL_GetTicks();
    }
}

SDL_Rect Pipe::FirstFlowRect(SDL_Rect* position, unsigned int flow_start) {
    SDL_Rect rect;

    rect.x = rect.y = rect.w = rect.h = 0;

    // makes it go only halfway
    int max_flowed_pixels = flowed_pixels <= Pipe::pipe_size_middle ? flowed_pixels : Pipe::pipe_size_middle;

    if(flow_start == FLOW_TOP) {
        rect.x = position->x + Pipe::pipe_size_middle_start;
        rect.y = position->y;
        rect.w = FLOW_LENGTH;
        rect.h = max_flowed_pixels;
    } else if(flow_start == FLOW_RIGHT) {
        rect.x = (position->x + PIPE_SIZE) - max_flowed_pixels;
        rect.y = position->y + Pipe::pipe_size_middle_start;
        rect.w = PIPE_SIZE - (PIPE_SIZE - max_flowed_pixels);
        rect.h = FLOW_LENGTH;
    } else if(flow_start == FLOW_DOWN) {
        rect.x = position->x + Pipe::pipe_size_middle_start;
        rect.y = (position->y + PIPE_SIZE) - max_flowed_pixels;
        rect.w = FLOW_LENGTH;
        rect.h = PIPE_SIZE - (PIPE_SIZE - max_flowed_pixels);
    } else if(flow_start == FLOW_LEFT) {
        rect.x = position->x;
        rect.y = position->y + Pipe::pipe_size_middle_start;
        rect.w = max_flowed_pixels;
        rect.h = FLOW_LENGTH;
    }

    return rect;
}

SDL_Rect Pipe::LastFlowRect(SDL_Rect* position, unsigned int flow_end) {
    SDL_Rect rect;

    rect.x = rect.y = rect.w = rect.h = 0;

    // makes it go only halfway
    int max_flowed_pixels = flowed_pixels - Pipe::pipe_size_middle;

    if(flow_end == FLOW_TOP) {
        rect.x = position->x + Pipe::pipe_size_middle_start;
        rect.y = (position->y + pipe_size_middle) - max_flowed_pixels;
        rect.w = FLOW_LENGTH;
        rect.h = PIPE_SIZE - (PIPE_SIZE - max_flowed_pixels);
    } else if(flow_end == FLOW_RIGHT) {
        rect.x = position->x + Pipe::pipe_size_middle;
        rect.y = position->y + Pipe::pipe_size_middle_start;
        rect.w = max_flowed_pixels;
        rect.h = FLOW_LENGTH;
    } else if(flow_end == FLOW_DOWN) {
        rect.x = position->x + Pipe::pipe_size_middle_start;
        rect.y = position->y + pipe_size_middle;
        rect.w = FLOW_LENGTH;
        rect.h = max_flowed_pixels;
    } else if(flow_end == FLOW_LEFT) {
        rect.x = (position->x + pipe_size_middle) - max_flowed_pixels;
        rect.y = position->y + Pipe::pipe_size_middle_start;
        rect.w = pipe_size_middle - (pipe_size_middle - max_flowed_pixels);
        rect.h = FLOW_LENGTH;
    }

    return rect;
}

bool Pipe::isFlowFinished() {
    return flowed_pixels == PIPE_SIZE;
}

int Pipe::getFlowStartPosition() {
    return flow_start_position;
}

int Pipe::getFlowTurnPosition() {
    return flow_turn_position;
}

void Pipe::setFlowTurnPosition(int direction) {
    flow_turn_position = direction;
}
