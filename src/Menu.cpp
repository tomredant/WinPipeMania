#include "Menu.h"
#include "Button.h"
#include "Log.h"

Menu::Menu (SDL_Surface *s)
{
    screen = s;
    fadeSurface = SDL_CreateRGBSurface(0, screen->w, screen->h, 32, 0, 0, 0, 0);
}

void Menu::addButton (Button *button)
{
    buttons.push_back(button);
}

void Menu::addText (Text *text)
{
    texts.push_back(text);
}

int Menu::mouseClick (int x, int y)
{
    // test all buttons
    for (std::list<Button*>::iterator it = buttons.begin(); it != buttons.end(); it++) {
        Button *button = *it;

        // button clicked ?
        if (button->mouseInBoundary(x, y)) {
            return button->getOption();
        }
    }

    return 0;
}

// draw all buttons
void Menu::Draw ()
{
    // set background opacity
    SDL_SetAlpha(fadeSurface, SDL_RLEACCEL | SDL_SRCALPHA, 128);
    SDL_BlitSurface(fadeSurface, 0, screen, 0);

    // draw Text objects
    for (std::list<Text*>::iterator it = texts.begin(); it != texts.end(); it++) {
        Text *text = *it;
        text->Draw();
    }

    // draw Button objects
    for (std::list<Button*>::iterator it = buttons.begin(); it != buttons.end(); it++) {
        Button *button = *it;
        button->Draw();
    }
}

void Menu::Draw (Text *text)
{
    Draw();
    text->Draw();
}
