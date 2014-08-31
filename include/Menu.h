#ifndef MENU_H
#define MENU_H

#include <list>

#include <SDL/SDL.h>
#include "Text.h"
#include "Button.h"

class Menu
{
    public:
        Menu(SDL_Surface *screen);
        void addButton (Button *button);
        void addText (Text *text);

        void Draw ();
        void Draw (Text *text);

        /*! Input a mouse click */
        int mouseClick (int x, int y);
    protected:
    private:
        SDL_Surface *screen, *fadeSurface;
        std::list<Button*> buttons;
        std::list<Text*> texts;
};

#endif // MENU_H
