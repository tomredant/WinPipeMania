#include "Text.h"
#include "Log.h"

Text::Text(SDL_Surface *s, int x, int y, int f_size)
{
    screen = s;
    rect = { x, y, 0, 0 };
    color = { 0xFF };
    font_size = f_size;

    font = TTF_OpenFont(FONT_PATH, font_size);
}

Text::~Text() {
    TTF_CloseFont(font);
}

SDL_Rect* Text::getRect() {
    return &rect;
}

void Text::Draw(const char *text) {
    int w, h;
    TTF_SizeText(font, text, &w, &h);
    rect.w = w;
    rect.h = h;

    SDL_Surface *TTF_Message = TTF_RenderText_Solid (font, text, color);

    if (TTF_Message) {
        if (SDL_BlitSurface(TTF_Message, NULL, screen, &rect))
            LOG(logERROR) << "Could not write text: " << TTF_GetError() << "";
    } else {
        LOG(logERROR) << "Could not write text: " << TTF_GetError() << "";
    }

    SDL_FreeSurface(TTF_Message);
}
