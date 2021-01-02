#ifndef TEXT_H
#define TEXT_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define FONT_PATH ":/batmfa__.ttf"

class Text
{
    public:
        Text(SDL_Surface *s, int x, int y, int f_size);
        virtual ~Text();

        void Draw(const char *text);
        void Draw(const char *text, int size);
        void setFontSize(int size);

        SDL_Rect* getRect();
    protected:
    private:
        SDL_Surface *screen;
        TTF_Font *font;
        SDL_Color color;

        // text position
        SDL_Rect rect;

        void setupFont();

        int font_size;
};

#endif // TEXT_H
