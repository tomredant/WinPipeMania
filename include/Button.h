#ifndef BUTTON_H
#define BUTTON_H

#include "Defines.h"
#include "Text.h"

class Button
{
    public:
        Button (Text *t, eMenuOptions option, int _size, int _hover_size);
        bool mouseInBoundary (int x, int y);
        void Draw ();
        eMenuOptions getOption ();
    protected:
    private:
        Text *text;
        char *str;
        int size, hover_size;
        eMenuOptions mOption;
};

#endif // BUTTON_H
