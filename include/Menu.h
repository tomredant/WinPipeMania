#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>
#include "Text.h"

#define MENU_START_GAME 1
#define MENU_EXIT 2

#define START_MENU_OFFSET_X 450
#define START_MENU_OFFSET_Y 300
#define EXIT_MENU_OFFSET_X 530
#define EXIT_MENU_OFFSET_Y 350

#define MENU_SIZE 30
#define MENU_HOVER_SIZE 40

class Menu
{
    public:
        Menu(SDL_Surface *s);
        void Draw();

        /*! Input a mouse click */
        int mouseClick (int x, int y);
    protected:
    private:
        SDL_Surface *screen;

        Text *start_menu, *exit_menu;

        int current_option;

        bool mouseInBoundary(Text *text, int x, int y);
        void drawMenu(Text *menu_entry, const char *text);
};

#endif // MENU_H
