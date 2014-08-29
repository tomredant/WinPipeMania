#ifndef MENU_H
#define MENU_H

#include <list>

#include <SDL/SDL.h>
#include "Text.h"
#include "Button.h"

#define MENU_START_GAME 1
#define MENU_EXIT 2

#define MENU_PLAY_AGAIN_YES 1
#define MENU_PLAY_AGAIN_NO 2

#define START_MENU_OFFSET_X 450
#define START_MENU_OFFSET_Y 300
#define EXIT_MENU_OFFSET_X 530
#define EXIT_MENU_OFFSET_Y 350

#define PLAY_AGAIN_YES_OFFSET_X 400
#define PLAY_AGAIN_YES_OFFSET_Y 400
#define PLAY_AGAIN_NO_OFFSET_X 400
#define PLAY_AGAIN_NO_OFFSET_Y 450

#define MENU_SIZE 30
#define MENU_HOVER_SIZE 40

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
