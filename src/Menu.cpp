#include "Menu.h"
#include "Log.h"

Menu::Menu(SDL_Surface *s)
{
    screen = s;
    current_option = MENU_START_GAME;

    start_menu = new Text(screen, START_MENU_OFFSET_X, START_MENU_OFFSET_Y, MENU_SIZE);
    exit_menu = new Text(screen, EXIT_MENU_OFFSET_X, EXIT_MENU_OFFSET_Y, MENU_SIZE);
}

int Menu::mouseClick (int x, int y) {
    if(mouseInBoundary(start_menu, x, y)) {
        LOG(logDEBUG) << "Start menu event";
        return MENU_START_GAME;
    } else if(mouseInBoundary(exit_menu, x, y)) {
        LOG(logDEBUG) << "Exit menu event";
        return MENU_EXIT;
    } else {
        LOG(logDEBUG) << "No events match";
        return 0;
    }
}

void Menu::Draw() {
    drawMenu(start_menu, "START GAME");
    drawMenu(exit_menu, "EXIT");
}

void Menu::drawMenu(Text *menu_entry, const char *text) {
    int x, y, menu_size;
    SDL_GetMouseState(&x, &y);

    if(mouseInBoundary(menu_entry, x, y)) {
        menu_size = MENU_HOVER_SIZE;
    } else {
        menu_size = MENU_SIZE;
    }

    menu_entry->Draw(text, menu_size);
}

bool Menu::mouseInBoundary(Text *text, int x, int y) {
    return (x >= text->getRect()->x && x <= (text->getRect()->x + text->getRect()->w)) && (y >= text->getRect()->y && y <= (text->getRect()->y + text->getRect()->h));
}
