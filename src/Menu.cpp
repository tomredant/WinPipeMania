#include "Menu.h"
#include "Button.h"
#include "Log.h"

void Menu::addButton (Button *button)
{
    buttons.push_back(button);
}

int Menu::mouseClick (int x, int y)
{
    // test all buttons
    for (std::list<Button*>::iterator it = buttons.begin(); it != buttons.end(); it++) {
        Button *button = *it;

        // button clicked ?
        if (button->mouseInBoundary(x, y)) {
            return button->getCode();
        }
    }

    return 0;
}

// draw all buttons
void Menu::Draw ()
{
    for (std::list<Button*>::iterator it = buttons.begin(); it != buttons.end(); it++) {
        Button *button = *it;

        button->Draw();
    }
}
