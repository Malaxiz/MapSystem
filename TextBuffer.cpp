#include "TextBuffer.h"

TextBuffer::TextBuffer(int x, int y, std::string Text, SDL_Surface* Surf_Destination, TTF_Font* Font, SDL_Color Color) :
    x(x), y(y), Text(Text), Surf_Destination(Surf_Destination), Font(Font), Color(Color)
{
}
