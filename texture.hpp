#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <stb_truetype.h>

void InitGlyphTexture();
void CleanUpGlyphTexture();

struct GlyphTextureInfo {
  SDL_Texture *texture;
  int advance;
  SDL_Rect dest;
};

GlyphTextureInfo CreateTextureFromCodePoint(SDL_Renderer *renderer,
                                        const stbtt_fontinfo &info,
                                        const int &codepoint, const float &scale);

GlyphTextureInfo CreateTextureFromIndex(SDL_Renderer *renderer,
                                    const stbtt_fontinfo &info,
                                    const int &index, const float &scale);
#endif