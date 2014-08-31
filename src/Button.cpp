#include "Button.h"

Button::Button (Text *t, eMenuOptions option, int _size, int _hover_size)
{
    text = t;
    mOption = option;
    size = _size;
    hover_size = _hover_size;
}

void Button::Draw ()
{
    int x, y, menu_size = size;

    SDL_GetMouseState(&x, &y);

    if (mouseInBoundary(x, y)) {
        menu_size = hover_size;
    }

    text->Draw(menu_size);
}

bool Button::mouseInBoundary (int x, int y)
{
    return (x >= text->getRect()->x && x <= (text->getRect()->x + text->getRect()->w)) && (y >= text->getRect()->y && y <= (text->getRect()->y + text->getRect()->h));
}

eMenuOptions Button::getOption ()
{
    return mOption;
}
