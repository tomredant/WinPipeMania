#ifndef BUTTON_H
#define BUTTON_H

#include "Text.h"


class Button
{
    public:
        Button (Text *t, int c, int _size, int _hover_size);
        bool mouseInBoundary (int x, int y);
        void Draw ();
        int getCode ();
    protected:
    private:
        Text *text;
        char *str;
        int code, size, hover_size;
};

#endif // BUTTON_H
