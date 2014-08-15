#ifndef SPLASH_H
#define SPLASH_H

#define SPLASH_SCREEN_FADE 1000

class Splash
{
    public:
        Splash(SDL_Surface *screen_surface, SDL_Surface *picture);
        virtual ~Splash();
        bool Update();
        void Draw();
    protected:
    private:
        SDL_Surface *screen, *splash, *fadeSurface;
        int stage;
        int starting_time;
        int splashAlpha;
};

#endif // SPLASH_H
