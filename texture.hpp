#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>

#include <stb_truetype.h>

void InitGlyphTexture();
void CleanUpGlyphTexture();

SDL_Texture *CreateTextureFromCodePoint(SDL_Renderer *renderer,
                                        const stbtt_fontinfo &info,
                                        wchar_t &codepoint, const float &scale,
                                        int &advance, SDL_Rect &dst);

SDL_Texture *CreateTextureFromIndex(SDL_Renderer *renderer,
                                    const stbtt_fontinfo &info,
                                    const int &index, const float &scale,
                                    const SDL_Color &color, int &advance,
                                    SDL_Rect &dst);
#endif