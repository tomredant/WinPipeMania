#include "Menu.h"
#include "Log.h"

Menu::Menu(SDL_Surface *s)
{
    screen = s;
    current_option = MENU_START_GAME;

    start_menu = new Text(screen, START_MENU_OFFSET_X, START_MENU_OFFSET_Y, 30);
    exit_menu = new Text(screen, EXIT_MENU_OFFSET_X, EXIT_MENU_OFFSET_Y, 30);
}

int Menu::mouseClick (int x, int y) {
    if(captureClick(start_menu, x, y)) {
        LOG(logDEBUG) << "Start menu event";
        return MENU_START_GAME;
    } else if(captureClick(exit_menu, x, y)) {
        LOG(logDEBUG) << "Exit menu event";
        return MENU_EXIT;
    } else {
        LOG(logDEBUG) << "No events match";
        return 0;
    }
}

void Menu::Draw() {
    start_menu->Draw("START GAME");
    exit_menu->Draw("EXIT");
}

bool Menu::captureClick(Text *text, int x, int y) {
    LOG(logDEBUG) << "Menu click: (x,y)," << x << "," << y << " | Rect (x,y,w,h)" << text->getRect()->x << "," << text->getRect()->y << "," << (text->getRect()->x + text->getRect()->w) << "," << (text->getRect()->y + text->getRect()->h);
    return (x >= text->getRect()->x && x <= (text->getRect()->x + text->getRect()->w)) && (y >= text->getRect()->y && y <= (text->getRect()->y + text->getRect()->h));
}
