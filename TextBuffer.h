#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextBuffer
{
public:
    TextBuffer(int x, int y, std::string Text, SDL_Surface* Surf_Destination, TTF_Font* Font, SDL_Color Color);

    int x, y;
    std::string Text;
    SDL_Surface* Surf_Destination;
    TTF_Font* Font;
    SDL_Color Color;
};

#endif // TEXTBUFFER_H
